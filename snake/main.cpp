/*****************************************
	�ļ����ƣ�main.cpp
	�ļ�������̰����
	ͼ�ν���⣺
		easyx win32 mfc qt duilib cocos unity ue�ȵ�
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <graphics.h>

#define N 100	//�ߵ�������
#define SIZE 10	//�ߵĿ��
//�ṹ��

enum Ch{ up = 72, down = 80, left = 75, right = 77 };

struct Coor
{
	int x;
	int y;
};

//̰����: �� ʳ��
struct Snake
{
	int n;		//��ǰ�м���
	struct Coor szb[N];//����
	Ch ch;		//����
};

struct Food
{
	struct Coor fzb;
	bool eat;
};

struct Snake snake;
struct Food food;

void GameInit()
{
	//��ʼ��һ������
	initgraph(640, 480);

	snake.n = 3;
	snake.ch = right;
	snake.szb[0].x = 100;
	snake.szb[0].y = 100;
	snake.szb[1].x = 90;
	snake.szb[1].y = 100;
	snake.szb[2].x = 80;
	snake.szb[2].y = 100;

	srand((unsigned int)time(NULL));
	food.fzb.x = rand() % 64 * 10 + 5;
	food.fzb.y = rand() % 48 * 10 + 5;
}

//������
void DrawSnake(int k)
{
	//system("cls");
	cleardevice();

	for (int i = 0; i < snake.n; i++)
	{
		//printf("��%d���ߵ�����: %d %d\n", i, snake.szb[i].x, snake.szb[i].y);

		//��Բ
		//circle(snake.szb[i].x, snake.szb[i].y, 5);
		//������
		setfillcolor(GREEN);
		fillrectangle(snake.szb[i].x, snake.szb[i].y, snake.szb[i].x + SIZE, snake.szb[i].y + SIZE);
	}
	setfillcolor(RED);
	if (k == 3)
	{
		fillcircle(food.fzb.x, food.fzb.y, 10);
	}
	else
	{
		fillcircle(food.fzb.x, food.fzb.y, 5);
	}
}

void Move()
{
	for (int i = snake.n - 1; i > 0; i--)
	{
		snake.szb[i].x = snake.szb[i - 1].x;
		snake.szb[i].y = snake.szb[i - 1].y;
	}

	switch (snake.ch)
	{
	case up:
		snake.szb[0].y -= SIZE;
		break;
	case down:
		snake.szb[0].y += SIZE;
		break;
	case left:
		snake.szb[0].x -= SIZE;
		break;
	case right:
		snake.szb[0].x += SIZE;
		break;
	}
}

int Snakemove(int k)
{
	//����������Ĺ�ʵ����������ֵ���Σ��Ų��������˸���
	if (k == 0)
	{
		Move();
		k++;
	}
	Move();

	return k;
}

//�ı䷽��
void ChangeCh()
{
	char key;
	key = _getch();	//���ռ��̵�����

	switch (key)
	{
	case up:
		if (down != snake.ch)
		{
			snake.ch = up;
		}
		break;
	case down: 
		if (up != snake.ch)
		{
			snake.ch = down;
		}
		break;
	case left:
		if (right != snake.ch)
		{
			snake.ch = left;
		}
		break;
	case right: 
		if (left != snake.ch)
		{
			snake.ch = right;
		}
		break;
	}
}

void CreateFood(int k)
{
	//1.ʳ��������ߵĹ����
	//2.ʳ�ﲻ�������غ�
	int flag;

	while (1)
	{
		flag = 0;
		if (k != 3)
		{
			food.fzb.x = rand() % 64 * 10 + 5;
			food.fzb.y = rand() % 48 * 10 + 5;
		}
		else
		{
			food.fzb.x = (rand() % 62 + 1) * 10 + 5;
			food.fzb.y = (rand() % 46 + 1) * 10 + 5;
		}
		
		for (int i = 0; i < snake.n; i++)
		{
			if (snake.szb[i].x + 5 == food.fzb.x && snake.szb[i].y + 5 == food.fzb.y)
			{
				flag = 1;
				break;
			}
		}

		if (flag)
		{
			continue;
		}
		else
		{
			food.eat = false;
			break;
		}
	}
}

int EatFood(int k)
{
	if (snake.szb[0].x + 5 == food.fzb.x && snake.szb[0].y + 5 == food.fzb.y)
	{
		if (k == 3)
		{
			snake.n += 2;
			k = 0;
		}
		else
		{
			snake.n++;
			k++;
		}
		food.eat = true;
	}

	return k;
}

int GameOver()
{
	//ײǽ
	if (snake.szb[0].x < 0 || snake.szb[0].x > 640 || snake.szb[0].y < 0 || snake.szb[0].y > 480)
	{
		return 1;
	}

	//�Ե��Լ�
	for (int i = snake.n - 1; i > 0; i--)
	{
		if (snake.szb[0].x == snake.szb[i].x && snake.szb[0].y == snake.szb[i].y)
		{
			return 1;
		}
	}
}

int main()
{
	int x = 0;
	int k = 1;
	GameInit();
	while (1)
	{
		//kbhit()�����������̵����룬�з���1��û�з���0
		while (!_kbhit())
		{
			if (food.eat == true)
			{
				CreateFood(k);
			}
			k = Snakemove(k);	//�ȸ�ֵ
			DrawSnake(k);	//�ٻ���(������������ӳ���ʱ���Ͻ���˸�����)	
			Sleep(100);
			if (GameOver())
			{
				x = 1;
				break;
			}
			k = EatFood(k);
		}
		if (x == 1)
		{
			break;
		}
		ChangeCh();	
	}
	
	return 0;
}
