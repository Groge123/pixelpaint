#include <graphics.h>
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h>

#define BKCOLOR WHITE
#define COLORNUM 10
#define MAX_WIDTH 720
#define MAX_HEIGHT 480


void InitLine();
void Initinterface();
void Draw();
void InitColor();
void ClearZone();
void CreatWindow();
void Instruction();
void ShowLine(ExMessage msg);
void Redraw();
void Print();

class SelectZone
{
public:
	int x1;
	int y1;
	int x2;
	int y2;

public:
	COLORREF rgb;

};

int PixelSum[MAX_WIDTH / 10][MAX_HEIGHT / 10];
COLORREF PixelColor[MAX_WIDTH / 10][MAX_HEIGHT / 10];
SelectZone color[COLORNUM];   //颜色
COLORREF CurrentColor;
int lastevent;
int flag = 0;

int main()
{
	initgraph(MAX_WIDTH, MAX_HEIGHT, EX_NOMINIMIZE);
	setbkcolor(BKCOLOR);
	cleardevice();
	InitColor();
	Initinterface();
	while (1)
	{

		BeginBatchDraw();

		Draw();
		EndBatchDraw();
	}

	getchar();
}

void Print()
{
	for (int i = 0; i < MAX_WIDTH / 10; i++)
	{
		for (int j = 0; j < MAX_HEIGHT / 10; j++)
		{
			/*if(PixelSum[i][j] = 0)*/
			{
				printf("%d ", PixelSum[i][j]);
			}
		}
		printf("\n");
	}
}

void InitLine()
{
	for (int i = 0; i < 72; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			setlinecolor(BLACK);
			line(i * 10, j * 10 + 80, MAX_WIDTH, j * 10 + 80);
			line(i * 10, j * 10 + 80, i * 10, MAX_HEIGHT);
		}
	}
}

//初始化界面
void Initinterface()
{
	memset(&PixelSum, 0, sizeof(PixelSum));
	memset(&PixelColor, 0, sizeof(PixelColor));
	InitLine();
	settextcolor(RED);
	for (int i = 0; i < 10; i++)
	{


		printf("%d\n", color[i].rgb);
		setfillcolor(color[i].rgb);
		fillrectangle(300 + i * 20, 20, 300 + (i + 1) * 20, 20 + 20);
	}

	//
	settextstyle(16, 8, "微软雅黑");
	settextcolor(RGB(0, 100, 255));
	//
	
	rectangle(20, 5, 120, 30);

	outtextxy(25, 8, "clear the zone");
	//
	rectangle(20, 35, 120, 60);
	outtextxy(50, 39, "news");
	///
	settextcolor(RGB(50, 100, 100));
	outtextxy(300, 0, "select your color:");
	//
	setfillcolor(WHITE);
	fillcircle(620, 40, 25);
	settextstyle(20, 10,"行书");
	settextcolor(BLUE);
	outtextxy(610, 30, "㊣");
	setfillcolor(RED);
	solidrectangle(700, 10, MAX_WIDTH, 50);
}
//设置画笔颜色
void InitColor()
{
	color[0].rgb = RGB(0, 0, 0);       //黑色☆㊣
	color[1].rgb = RGB(41, 36, 33);    //灰色
	color[2].rgb = RGB(128, 128, 105);
	color[3].rgb = RGB(255, 0, 0);
	color[4].rgb = RGB(255, 127, 80);
	color[5].rgb = RGB(255, 245, 238);
	color[6].rgb = RGB(255, 255, 0);
	color[7].rgb = RGB(0, 255, 255);
	color[8].rgb = RGB(237, 145, 33);
	color[9].rgb = RGB(3, 168, 158);
	color[10].rgb = RGB(255, 192, 203);
}

void Draw()
{
	ExMessage msg;
	/*msg = getmessage(EX_MOUSE);*/
	while (peekmessage(&msg, EX_MOUSE))
	{
		int i = 0;
		//按下鼠标并移动->绘画
		int x = msg.x / 10;
		int y = msg.y / 10;
		if (msg.message == WM_MOUSEMOVE&&lastevent)
		{
			if (msg.y > 80)
			{
				printf("x=%d  y=%d\n", msg.x, msg.y);
				lastevent = 1;
				setfillcolor(CurrentColor);
				printf("color=%d \n", color[i].rgb);
				fillrectangle(x * 10, y * 10, x * 10 + 10, y * 10 + 10);
				PixelSum[x][y] = 1;
				PixelColor[x][y] = CurrentColor;
			}
			else lastevent = 0;
		}
		//按下鼠标绘画
		if (msg.message == WM_LBUTTONDOWN)
		{
			
			if (msg.y > 80)
			{
				printf("x=%d  y=%d\n", msg.x, msg.y);
				lastevent = 1;
				
				
				setfillcolor(CurrentColor);
				printf("color=%d \n", color[i].rgb);
				fillrectangle(x * 10, y * 10, x * 10 + 10, y * 10 + 10);
				PixelSum[x][y] = 1;
				PixelColor[x][y] = CurrentColor;
				Print();
			}

			//select function
			else if (msg.x > 300 && msg.x < 500 && msg.y>20 && msg.y < 40)
			{
				printf("x=%d  y=%d\n", msg.x, msg.y);
				i = (msg.x - 300) / 20;
				CurrentColor = color[i].rgb;

			}

			//clear function
			else if (msg.x > 20 && msg.x < 120 && msg.y>5 && msg.y < 30)
			{
				printf("clear function are executed!\n");
				ClearZone();
			}

			else if (msg.x > 20 && msg.x < 120 && msg.y>25 && msg.y < 60)
			{
				CreatWindow();
			}
			
			else if (pow(msg.x - 620, 2) + pow(msg.y - 40, 2) <= 25 * 25)
			{
				Instruction();
			}
			ShowLine(msg);
			

			
		}
		if (msg.message == WM_LBUTTONUP)
		{
			if (msg.y > 80)
			{
				lastevent = 0;
			}
		}
	}
	
}


void ShowLine(ExMessage msg)
{

	if (msg.x > 700 && msg.x < MAX_WIDTH && msg.y>10 && msg.y < 50)
	{
		printf("showline are executed");
		flag++;
		
	}
	setfillcolor(RED);
	if (flag % 2 == 0&&flag!=0)
	{
		clearrectangle(0, 80, MAX_WIDTH, MAX_HEIGHT);
		Redraw();
	}
	else
	{
		setfillcolor(BLUE);
		InitLine();
	}
	solidrectangle(700, 10, MAX_WIDTH, 50);
}

void Redraw()
{
	for (int i = 0; i < MAX_WIDTH / 10; i++)
	{
		for (int j = 0; j < MAX_HEIGHT / 10; j++)
		{
			if (PixelSum[i][j]==1)
			{
				setfillcolor(PixelColor[i][j]);
				solidrectangle(i * 10, j * 10, i * 10 + 10,  j * 10 + 10);
			}
		}
	}
}

void Instruction()
{
	if (MessageBox(NULL, "select your language \nleft is english \nright is chinese", "instruction", MB_YESNO) == IDYES)
	{
		MessageBox(NULL, "The top color version can choose the color you like to paint, the default color is black, the current color is less, and more colors will be added later. You can click through the mouse pixel by pixel, and you can drag the mouse to draw.", "instruction", MB_YESNO);
	}
	else {
		MessageBox(NULL, "上方的颜色版可以选择你喜欢的颜色进行绘画，默认颜色是黑色，当前的颜色较少，后续会添加更多的颜色。你可以通过鼠标一个像素点地点击，也可以拖动鼠标进行绘画。", "instruction", MB_YESNO);
	}
}

void ClearZone()
{
	clearrectangle(0, 80, MAX_WIDTH, MAX_HEIGHT);
	Initinterface();
}

void CreatWindow()
{
	MessageBox(NULL, "in development", "draw", MB_OK | MB_ICONQUESTION);
}