/************************************
	文件名称：main.cpp
	文件描述：实现一个拼图游戏
	作者：Victor Lee

	1.程序思路的培养
	2.图形界面的学习
	3.复习语法
************************************/

#include <stdio.h>
#include <time.h>
#include <graphics.h>	//第三方库：easyx 第三方库 图形界面
#include <mmsystem.h>	//多媒体设备接口
#pragma comment(lib, "winmm.lib")

#define X 5
#define Y 5

int map[X][Y];
int arr[X*Y];
IMAGE img[X*Y];
IMAGE image, final;

//游戏的初始化函数
void GameInit()
{
	mciSendString(L"open start.mp3 alias BGM", 0, 0, 0);
	mciSendString(L"play BGM", 0, 0, 0);

	//初始化二维数组
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			map[i][j] = i * Y + j;
		}
	}

	//加载图片
	loadimage(&image, L"ramon2.jpg", 500, 600);

	//切割图片
	SetWorkingImage(&image);

	for (int x = 0; x < X; x++)
	{
		for (int y = 0; y < Y; y++)
		{
			getimage(&img[x*Y+y], x*100, y*120, 100, 120);
		}
	}

	SetWorkingImage(NULL);

	loadimage(&img[X*Y-1], L"0.jpg", 100, 120);

	//产生随机数
	//创建一个元素个数为X*Y的一维数组
	int pos = 0; 
	int length = X*Y-1;
	srand((unsigned int)time(NULL));

	for (int i = 0; i < X*Y; i++)
	{
		arr[i] = i;
	}

	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			if (length > 0)
			{
				pos = rand() % length;	//产生0~23的随机数
				map[i][j] = arr[pos];	//取一维数组的下标为产生的随机数的元素值赋给对应的二维数组元素
				for (int k = pos; k < length - 1; k++)	//对一维数组进行重排序
				{
					arr[k] = arr[k + 1];	//将给出去的元素后面的值依次向前递推
				}
				length--;
			}
			else
			{
				map[i][j] = arr[X*Y-1];	//最后一定是空白，故随机长度为24
			}
		}
	}
}

void DrawMap()
{
	BeginBatchDraw();	//防止闪烁
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			putimage(i*100, j*120, &img[map[i][j]]);
		}
	}

	//画线
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	for (int i = 0; i < X+1; i++)
	{
		line(0, i * 120, 500, i * 120);
		line(i * 100, 0, i * 100, 600);
	}
	EndBatchDraw();
}

void PlayGame()
{
	//1.用鼠标点击

	//得到空白图片对应的元素的下标 r0, c0
	int r0, c0, flag = 0;
	for (r0 = 0; r0 < X; r0++)
	{
		for (c0 = 0; c0 < Y; c0++)
		{
			if (map[r0][c0] == 24)
			{
				flag = 1;
				break;
			}
		}
		if (flag)
		{
			break;
		}
	}

	//得到点击图片对应的元素的下标 r, c
	int r, c;
	MOUSEMSG msg = { 0 };
	msg = GetMouseMsg();

	switch (msg.uMsg)
	{
	case WM_LBUTTONDOWN:
		r = msg.x / 100;
		c = msg.y / 120;
		if ((r == r0 && c == c0 - 1) || (r == r0 && c == c0 + 1) ||
			(r == r0 - 1 && c == c0) || (r == r0 + 1 && c == c0))
		{
			PlaySound(L"click.wav", NULL, SND_ASYNC | SND_FILENAME);
			int t;
			t = map[r][c];
			map[r][c] = map[r0][c0];
			map[r0][c0] = t;
		}
		break;
	}

	int count = 0;
	//2.判断是否完成
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			if (map[i][j] == i * Y + j)
			{
				count++;
			}
		}
	}
	if (count == 25)
	{
		loadimage(&final, L"success.jpg", 200, 100);
		putimage(150, 250, &final);
		system("pause");
		exit(1);
	}
}

int main()
{
	initgraph(500, 600);
	GameInit();
	while (1)
	{
		DrawMap();
		PlayGame();
	}

	//二维数组 0-24排好序
	//进入游戏，打乱

	return 0;
}

/*
	IMAGE image;	//存放一张图片
	loadimage(&image, L"ramon1.jpg", 500, 600);	//赋值
	putimage(0, 0, &image);	//在指定的坐标输出一张图片
*/