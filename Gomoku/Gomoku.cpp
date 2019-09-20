/************************************************
	这是一个五子棋小游戏程序
	实现功能:
	1.描绘棋盘
	2.落子
	3.判定
	4.两种模式？
*************************************************/

// Gomoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define X 480
#define Y 480

int board[15][15] = {0};

#if 0
void DrawBoard()
{
	setbkcolor(BROWN);
	cleardevice();	//刷新才能更改背景颜色
	setlinecolor(BLACK);
	for (int i = 50; i < X; i += 50)
	{
		for (int j = 50; j < Y; j += 50)
		{
			line(i, j, X - 50, j);
			line(i, j, i, Y - 50);
		}
	}
}
#endif

void GameInit()
{
	initgraph(X + 160, Y);

	//加载背景
	loadimage(NULL, L"wood.jpg");

	//加载音乐
	mciSendString(L"open bkmusic.mp3", 0, 0, 0);
	mciSendString(L"play bkmusic.mp3", 0, 0, 0);

	setlinecolor(BLACK);
	for (int i = 30; i < X; i += 30)
	{
		for (int j = 30; j < Y; j += 30)
		{
			line(i, j, X - 30, j);
			line(i, j, i, Y - 30);
		}
	}

	line(X, 0, X, Y);
	line(X + 1, 0, X + 1, Y);
	line(X + 2, 0, X + 2, Y);

	outtextxy(X + 45, 100, L"玩家1: 黑棋");
	outtextxy(X + 45, 150, L"玩家2: 白棋");
}

int GameOver(int a, int b)
{
	int i, j, t;
	int count = 0, count1 = 0;

	if (board[a][b] != 0)
	{
		t = board[a][b];
	}
	else
	{
		return 0;
	}

	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			if (board[i][j] != 0)
			{
				count++;
			}
		}
	}

	//横向判断
	for (i = - 4; i < 5; i++)
	{
		if (count1 == 5)
		{
			break;
		}

		if (board[a+i][b] == t)
		{
			count1++;
		}
		else
		{
			count1 = 0;
		}
	}

	//纵向判断
	for (j = - 4; j < 5; j++)
	{
		if (count1 == 5)
		{
			break;
		}

		if (board[a][b+j] == t)
		{
			count1++;
		}
		else
		{
			count1 = 0;
		}
	}

	//正斜向判断
	for (int i = -4; i < 5; i++)
	{
		if (count1 == 5)
		{
			break;
		}

		j = i;
		if (board[a + i][b + j] == t)
		{
			count1++;
		}
		else
		{
			count1 = 0;
		}
	}

	//反斜向判断
	for (int i = -4; i < 5; i++)
	{
		if (count1 == 5)
		{
			break;
		}

		j = -i;
		if (board[a + i][b + j] == t)
		{
			count1++;
		}
		else
		{
			count1 = 0;
		}
	}

	if (count1 == 5)
	{
		return t;
	}
	else
	{
		if (count == 225)
		{
			return 3;
		}
		else
		{
			return 0;
		}
	}
}

void PlayChess()
{
	MOUSEMSG m;
	int x, y;
	int	a = 0, b = 0;
	int flag = 0;

	while (1)
	{
		m = GetMouseMsg();

		for (int i = 1; i <= 15; i++)
		{
			for (int j = 1; j <= 15; j++)
			{
				if (abs(m.x - i * 30) < 15 && abs(m.y - j * 30) < 15)
				{
					x = i * 30;
					y = j * 30;
					a = i - 1;
					b = j - 1;
				}
			}
		}

		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (board[a][b] != 0)
			{
				PlaySound(L"error.wav", NULL, SND_FILENAME | SND_ASYNC);
				continue;
			}

			if (flag % 2 == 0)
			{
				setfillcolor(BLACK);
				fillcircle(x, y, 10);
				board[a][b] = 1;
			}
			else
			{
				setfillcolor(WHITE);
				fillcircle(x, y, 10);
				board[a][b] = 2;
			}
			//solidcircle(x, y, 10);

			flag++;
		}

		switch (GameOver(a, b))
		{
		case 0: 
			break;
		case 1:
			outtextxy(X + 45, 200, L"黑棋胜利");
			outtextxy(X + 45, 250, L"游戏结束");
			//MessageBox(NULL, L"黑棋胜利", L"游戏结束", MB_OK);
			Sleep(700);
			exit(0);
			break;
		case 2:
			outtextxy(X + 45, 200, L"白棋胜利");
			outtextxy(X + 45, 250, L"游戏结束");
			//MessageBox(NULL, L"白棋胜利", L"游戏结束", MB_OK);
			Sleep(700);
			exit(0);
			break;
		case 3: 
			outtextxy(X + 45, 200, L"棋盘已满，平局");
			outtextxy(X + 45, 250, L"游戏结束");
			//MessageBox(NULL, L"棋盘已满，平局", L"游戏结束", MB_OK);
			Sleep(700);
			exit(0);;
			break;
		}
	}
}

int main()
{
	GameInit();
	PlayChess();
	while (1)
	{	
	}
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
