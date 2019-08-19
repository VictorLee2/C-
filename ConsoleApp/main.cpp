/*
	�ļ����ƣ�main.cpp
	�ļ�������
		������С��Ϸ������̨���������easyx win32 mfc qt
*/

#include <stdio.h>		//��׼�������
#include <stdlib.h>		//system("cls")ˢ�¿���̨
#include <conio.h>		//getch()���ܼ��̵�����
#include <graphics.h>	//ͼ�����
#include <mmsystem.h>	//
#pragma comment(lib, "winmm.lib")

#define X 8
#define Y 8

//��ʼ����ά���飬1����ǽ��0����յأ�4�����������ڵأ�3����Ŀ�ĵأ�5��ʾ����
//���Ӻ�Ŀ�ĵ��غ� 4+3�������Ŀ�ĵ��غ� 5+3
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
			//printf("%d ", map[i][j]);	//����
			//����
			switch (map[i][j])
			{
				/*
				case 0:printf("  "); break;
				case 1:printf("��"); break;
				case 3:printf("��"); break;
				case 4:printf("��"); break;
				case 5:printf("��"); break;
				case 7:printf("��"); break;
				case 8:printf("��"); break;
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

//����Ϸ
void GamePlay()
{
	int r, e; //r�˵��±�
	int flag; //�ҵ��ı�־���ҵ���ֱ���˳�ѭ��
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
	key = _getch();	//��getchar()�����𣬾�Ϊ���ռ���������ַ�����ͬ����getchar()���л���������Ҫ���س����������룬ͬʱ��ʾ����(�������ʾ���ַ�)
	
	switch (key)
	{
	case 72:	//�ϣ�W
		//�˵�ǰ���ǿյػ����˵�ǰ����Ŀ�ĵ�
		if(map[r - 1][e] == 0 || map[r - 1][e] == 3)
		{
			map[r - 1][e] += 5;		//��������λ��
			map[r][e] -= 5;			//ԭ����λ�ø�ԭ
		}
		//�˵�ǰ�������ӻ����˵�ǰ����[����+Ŀ�ĵ�]
		else if (map[r - 1][e] == 4 || map[r - 1][e] == 7)
		{
			//�˵�ǰ���ǰ���ǿյػ���Ŀ�ĵ�
			if (map[r - 2][e] == 0 || map[r - 2][e] == 3)
			{
				map[r - 2][e] += 4;	//����������λ��
				map[r - 1][e] += 1;	//�����뿪λ�ã���������λ��
				map[r][e] -= 5;		//ԭ����λ�ø�ԭ
			}
		}
		break;
	case 80:	//�£�S
		//�˵�ǰ���ǿյػ����˵�ǰ����Ŀ�ĵ�
		if (map[r + 1][e] == 0 || map[r + 1][e] == 3)
		{
			map[r + 1][e] += 5;		//��������λ��
			map[r][e] -= 5;			//ԭ����λ�ø�ԭ
		}
		//�˵�ǰ�������ӻ����˵�ǰ����[����+Ŀ�ĵ�]
		else if (map[r + 1][e] == 4 || map[r + 1][e] == 7)
		{
			//�˵�ǰ���ǰ���ǿյػ���Ŀ�ĵ�
			if (map[r + 2][e] == 0 || map[r + 2][e] == 3)
			{
				map[r + 2][e] += 4;	//����������λ��
				map[r + 1][e] += 1;	//�����뿪λ�ã���������λ��
				map[r][e] -= 5;		//ԭ����λ�ø�ԭ
			}
		}
		break;
	case 75:	//��A
		//�˵�ǰ���ǿյػ����˵�ǰ����Ŀ�ĵ�
		if (map[r][e - 1] == 0 || map[r][e - 1] == 3)
		{
			map[r][e - 1] += 5;		//��������λ��
			map[r][e] -= 5;			//ԭ����λ�ø�ԭ
		}
		//�˵�ǰ�������ӻ����˵�ǰ����[����+Ŀ�ĵ�]
		else if (map[r][e - 1] == 4 || map[r][e - 1] == 7)
		{
			//�˵�ǰ���ǰ���ǿյػ���Ŀ�ĵ�
			if (map[r][e - 2] == 0 || map[r][e - 2] == 3)
			{
				map[r][e - 2] += 4;	//����������λ��
				map[r][e - 1] += 1;	//�����뿪λ�ã���������λ��
				map[r][e] -= 5;		//ԭ����λ�ø�ԭ
			}
		}
		break;
	case 77:	//�ң�D
		//�˵�ǰ���ǿյػ����˵�ǰ����Ŀ�ĵ�
		if (map[r][e + 1] == 0 || map[r][e + 1] == 3)
		{
			map[r][e + 1] += 5;		//��������λ��
			map[r][e] -= 5;			//ԭ����λ�ø�ԭ
		}
		//�˵�ǰ�������ӻ����˵�ǰ����[����+Ŀ�ĵ�]
		else if (map[r][e + 1] == 4 || map[r][e + 1] == 7)
		{
			//�˵�ǰ���ǰ���ǿյػ���Ŀ�ĵ�
			if (map[r][e + 2] == 0 || map[r][e + 2] == 3)
			{
				map[r][e + 2] += 4;	//����������λ��
				map[r][e + 1] += 1;	//�����뿪λ�ã���������λ��
				map[r][e] -= 5;		//ԭ����λ�ø�ԭ
			}
		}
		break;
	}
	/*********************************************************
	1.�������ʲô���ģ� ��ά�����Ԫ��ֵ
		�ı���漴Ϊ�ı�Ԫ��
	2.64��Ԫ���Ƿ�Ҫ�ı䣿 ����
		ֻ�ı��˺�����һ���ƶ�Ŀ�ĵأ��������ӵ�Ŀ�ĵأ���Ԫ��
	3.ʲôʱ��ȥ�ı�Ԫ�أ�
		������ʱ��ȥ�ı� ��charʵ��
	4.����һ���ᶯ�� ��һ��������ǽ��������ǽ�ķ����ƶ�����
		1.�˵�ǰ���ǿյ�					yes
		2.�˵�ǰ����Ŀ�ĵ�					yes
		3.�˵�ǰ����ǽ						no
		4.�˵�ǰ�������� 
			4.1���ӵ�ǰ���ǿյ�				yes
			4.2���ӵ�ǰ����Ŀ�ĵ�			yes
			4.3���ӵ�ǰ����ǽ				no
			4.4���ӵ�ǰ��������				no
			4.5���ӵ�ǰ����[����+Ŀ�ĵ�]	no
		5.�˵�ǰ����[����+Ŀ�ĵ�]
			5.1[����+Ŀ�ĵ�]ǰ���ǿյ�		yes
			5.2[����+Ŀ�ĵ�]ǰ����Ŀ�ĵ�	yes
			5.3[����+Ŀ�ĵ�]ǰ����ǽ		no
			5.4[����+Ŀ�ĵ�]ǰ��������		no
			5.5[����+Ŀ�ĵ�]ǰ����[����+Ŀ�ĵ�]no

		�����ƶ����������д����ʵ��
		�������ƶ�����������ùܣ�����no����������Ժ���
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
	���Ĵ���
	��ͼ�ν���⣺
	easyx
	win32
	mfc
	qt
*/

