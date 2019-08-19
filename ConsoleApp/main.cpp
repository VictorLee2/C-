/*
	文件名称：main.cpp
	文件描述：
		推箱子小游戏，控制台，界面程序，easyx win32 mfc qt
*/

#include <stdio.h>		//标准输入输出
#include <stdlib.h>		//system("cls")刷新控制台
#include <conio.h>		//getch()接受键盘的输入
#include <graphics.h>	//图像输出
#include <mmsystem.h>	//
#pragma comment(lib, "winmm.lib")

#define X 8
#define Y 8

//初始化二维数组，1代表墙，0代表空地，4代表箱子所在地，3代表目的地，5表示人物
//箱子和目的地重合 4+3，人物和目的地重合 5+3
int map[X][Y] = {
	{ 1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,1,0,0,1 },
	{ 1,0,1,0,1,4,3,1 },
	{ 1,0,0,0,0,4,3,1 },
	{ 1,0,1,0,1,4,3,1 },
	{ 1,0,0,0,1,0,0,1 },
	{ 1,1,1,1,1,5,0,1 },
	{ 0,0,0,0,1,1,1,1 } };

IMAGE leader, box, gbox, target, blank, wall, success;

void GamePrint()
{
	int count = 0;
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			if (map[i][j] == 4)
			{
				count++;
			}
			//printf("%d ", map[i][j]);	//数字
			//符号
			switch (map[i][j])
			{
				/*
				case 0:printf("  "); break;
				case 1:printf("■"); break;
				case 3:printf("☆"); break;
				case 4:printf("□"); break;
				case 5:printf("♂"); break;
				case 7:printf("★"); break;
				case 8:printf("♂"); break;
				*/
			case 0:
				putimage(j * 50, i * 50, &blank); break;
			case 1:
				putimage(j * 50, i * 50, &wall); break;
			case 3:
				putimage(j * 50, i * 50, &target); break;
			case 4:
				putimage(j * 50, i * 50, &box); break;
			case 5:
				putimage(j * 50, i * 50, &leader); break;
			case 7:
				putimage(j * 50, i * 50, &gbox); break;
			case 8:
				putimage(j * 50, i * 50, &leader); break;
			}
		}
		printf("\n");
	}
	if (count == 0)
	{
		putimage(0, 150, &success);
		system("pause");
		exit(0);
	}
}

//玩游戏
void GamePlay()
{
	int r, e; //r人的下标
	int flag; //找到的标志，找到便直接退出循环
	for (int i = 0; i < X; i++)
	{
		flag = 0;
		for (int j = 0; j < Y; j++)
		{
			if (map[i][j] == 5 || map[i][j] == 8)
			{
				r = i;
				e = j;
				flag = 1;
				break;
			}
		}
		if (flag)
		{
			break;
		}
	}

	char key;
	key = _getch();	//和getchar()的区别，均为接收键盘输入的字符，不同的是getchar()具有缓冲区，需要按回车键结束输入，同时显示回文(输出所显示的字符)
	
	switch (key)
	{
	case 72:	//上，W
		//人的前面是空地或者人的前面是目的地
		if(map[r - 1][e] == 0 || map[r - 1][e] == 3)
		{
			map[r - 1][e] += 5;		//人来到新位置
			map[r][e] -= 5;			//原来的位置复原
		}
		//人的前面是箱子或者人的前面是[箱子+目的地]
		else if (map[r - 1][e] == 4 || map[r - 1][e] == 7)
		{
			//人的前面的前面是空地或者目的地
			if (map[r - 2][e] == 0 || map[r - 2][e] == 3)
			{
				map[r - 2][e] += 4;	//箱子来到新位置
				map[r - 1][e] += 1;	//箱子离开位置，人来到新位置
				map[r][e] -= 5;		//原来的位置复原
			}
		}
		break;
	case 80:	//下，S
		//人的前面是空地或者人的前面是目的地
		if (map[r + 1][e] == 0 || map[r + 1][e] == 3)
		{
			map[r + 1][e] += 5;		//人来到新位置
			map[r][e] -= 5;			//原来的位置复原
		}
		//人的前面是箱子或者人的前面是[箱子+目的地]
		else if (map[r + 1][e] == 4 || map[r + 1][e] == 7)
		{
			//人的前面的前面是空地或者目的地
			if (map[r + 2][e] == 0 || map[r + 2][e] == 3)
			{
				map[r + 2][e] += 4;	//箱子来到新位置
				map[r + 1][e] += 1;	//箱子离开位置，人来到新位置
				map[r][e] -= 5;		//原来的位置复原
			}
		}
		break;
	case 75:	//左，A
		//人的前面是空地或者人的前面是目的地
		if (map[r][e - 1] == 0 || map[r][e - 1] == 3)
		{
			map[r][e - 1] += 5;		//人来到新位置
			map[r][e] -= 5;			//原来的位置复原
		}
		//人的前面是箱子或者人的前面是[箱子+目的地]
		else if (map[r][e - 1] == 4 || map[r][e - 1] == 7)
		{
			//人的前面的前面是空地或者目的地
			if (map[r][e - 2] == 0 || map[r][e - 2] == 3)
			{
				map[r][e - 2] += 4;	//箱子来到新位置
				map[r][e - 1] += 1;	//箱子离开位置，人来到新位置
				map[r][e] -= 5;		//原来的位置复原
			}
		}
		break;
	case 77:	//右，D
		//人的前面是空地或者人的前面是目的地
		if (map[r][e + 1] == 0 || map[r][e + 1] == 3)
		{
			map[r][e + 1] += 5;		//人来到新位置
			map[r][e] -= 5;			//原来的位置复原
		}
		//人的前面是箱子或者人的前面是[箱子+目的地]
		else if (map[r][e + 1] == 4 || map[r][e + 1] == 7)
		{
			//人的前面的前面是空地或者目的地
			if (map[r][e + 2] == 0 || map[r][e + 2] == 3)
			{
				map[r][e + 2] += 4;	//箱子来到新位置
				map[r][e + 1] += 1;	//箱子离开位置，人来到新位置
				map[r][e] -= 5;		//原来的位置复原
			}
		}
		break;
	}
	/*********************************************************
	1.界面根据什么来的？ 二维数组的元素值
		改变界面即为改变元素
	2.64个元素是否都要改变？ 不是
		只改变人和其下一个移动目的地（包括箱子的目的地）的元素
	3.什么时候去改变元素？
		按键的时候去改变 用char实现
	4.按键一定会动吗？ 不一定，碰到墙并继续往墙的方向移动不行
		1.人的前面是空地					yes
		2.人的前面是目的地					yes
		3.人的前面是墙						no
		4.人的前面是箱子 
			4.1箱子的前面是空地				yes
			4.2箱子的前面是目的地			yes
			4.3箱子的前面是墙				no
			4.4箱子的前面是箱子				no
			4.5箱子的前面是[箱子+目的地]	no
		5.人的前面是[箱子+目的地]
			5.1[箱子+目的地]前面是空地		yes
			5.2[箱子+目的地]前面是目的地	yes
			5.3[箱子+目的地]前面是墙		no
			5.4[箱子+目的地]前面是箱子		no
			5.5[箱子+目的地]前面是[箱子+目的地]no

		可以移动的情况，编写代码实现
		不可以移动的情况，不用管，上述no的情况均可以忽略
	*********************************************************/
}

int main()
{
	initgraph(400, 400);
	loadimage(&leader, "leader.jpg", 50, 50);
	loadimage(&box, "box.jpg", 50, 50);
	loadimage(&gbox, "gbox.jpg", 50, 50);
	loadimage(&target, "target.jpg", 50, 50);
	loadimage(&blank, "blank.jpg", 50, 50);
	loadimage(&wall, "wall.jpg", 50, 50);
	loadimage(&success, "success.jpg", 400, 100);

	mciSendString("open music.mp3", 0, 0, 0);
	mciSendString("play music.mp3 notify", 0, 0, 0);	

	while (1)
	{
		GamePrint();
		GamePlay();
	}
	return 0;
}

/*
	核心代码
	加图形界面库：
	easyx
	win32
	mfc
	qt
*/

