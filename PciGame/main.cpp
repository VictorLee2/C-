/************************************
	�ļ����ƣ�main.cpp
	�ļ�������ʵ��һ��ƴͼ��Ϸ
	���ߣ�Victor Lee

	1.����˼·������
	2.ͼ�ν����ѧϰ
	3.��ϰ�﷨
************************************/

#include <stdio.h>
#include <time.h>
#include <graphics.h>	//�������⣺easyx �������� ͼ�ν���
#include <mmsystem.h>	//��ý���豸�ӿ�
#pragma comment(lib, "winmm.lib")

#define X 5
#define Y 5

int map[X][Y];
int arr[X*Y];
IMAGE img[X*Y];
IMAGE image, final;

//��Ϸ�ĳ�ʼ������
void GameInit()
{
	mciSendString(L"open start.mp3 alias BGM", 0, 0, 0);
	mciSendString(L"play BGM", 0, 0, 0);

	//��ʼ����ά����
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			map[i][j] = i * Y + j;
		}
	}

	//����ͼƬ
	loadimage(&image, L"ramon2.jpg", 500, 600);

	//�и�ͼƬ
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

	//���������
	//����һ��Ԫ�ظ���ΪX*Y��һά����
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
				pos = rand() % length;	//����0~23�������
				map[i][j] = arr[pos];	//ȡһά������±�Ϊ�������������Ԫ��ֵ������Ӧ�Ķ�ά����Ԫ��
				for (int k = pos; k < length - 1; k++)	//��һά�������������
				{
					arr[k] = arr[k + 1];	//������ȥ��Ԫ�غ����ֵ������ǰ����
				}
				length--;
			}
			else
			{
				map[i][j] = arr[X*Y-1];	//���һ���ǿհף����������Ϊ24
			}
		}
	}
}

void DrawMap()
{
	BeginBatchDraw();	//��ֹ��˸
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			putimage(i*100, j*120, &img[map[i][j]]);
		}
	}

	//����
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
	//1.�������

	//�õ��հ�ͼƬ��Ӧ��Ԫ�ص��±� r0, c0
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

	//�õ����ͼƬ��Ӧ��Ԫ�ص��±� r, c
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
	//2.�ж��Ƿ����
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

	//��ά���� 0-24�ź���
	//������Ϸ������

	return 0;
}

/*
	IMAGE image;	//���һ��ͼƬ
	loadimage(&image, L"ramon1.jpg", 500, 600);	//��ֵ
	putimage(0, 0, &image);	//��ָ�����������һ��ͼƬ
*/