/**************************************
	�ļ����ƣ�main.cpp
	�ļ�������
		΢�ŵ�Ⱥ������
***************************************/
#include <stdio.h>
#include <Windows.h>

void PressKey(BYTE vkey)
{
	keybd_event(vkey, 0, 0, 0);
	Sleep(50);
	keybd_event(vkey, 0, KEYEVENTF_KEYUP, 0);
	Sleep(50);
}

void SendMessagel()
{
	//��ǰ���ƺ���Ҫ���͵�����
	//ctrv+v �Ȱ���Ctrl���ٰ���V������V������Ctrl
	keybd_event(VK_CONTROL, 0, 0, 0);
	Sleep(50);
	keybd_event(0x56, 0, 0, 0);
	Sleep(50);
	keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
	Sleep(50);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	Sleep(50);

	PressKey(VK_RETURN);
	PressKey(VK_ESCAPE);
}

int main()
{
	//QQ ���ھ�������ڵ����֤��
	int errortimes = 0;

	while (errortimes < 4)
	{
		HWND hwnd;		//hwnd = (HWND)0x000208A2; QQ���ھ����ÿ�δ򿪴���ֵ��䣬������
		hwnd = FindWindow(L"TXGuiFoundation", L"QQ");	//�����ƺͱ�����Ҵ��ڵĺ���
		HWND fronthwnd = GetForegroundWindow();	//��ȡ����ھ��

		if (hwnd != fronthwnd)
		{
			if (!SetForegroundWindow(hwnd))
			{
				printf("�Ҳ���QQ����,��ȷ�����Ѿ���¼!\n");
			}
		}
		if (errortimes == 0)
		{
			PressKey(VK_TAB);	//��ϵ��
			PressKey(VK_TAB);	//����
		}

		//PressKey(VK_DOWN);	
		PressKey(VK_RETURN);	//ѡ������

		PressKey(VK_DOWN);		//ѡ�����
		PressKey(VK_RETURN);	//ѡ������

		//ѭ����ʼ��
		PressKey(VK_DOWN);		//ѡ�����
		PressKey(VK_RETURN);	//�򿪶Ի���

		HWND curhwnd = GetForegroundWindow();
		if (hwnd != curhwnd)
		{
			errortimes = 0;
			SendMessagel();
		}
		else
		{
			errortimes++;
			continue;
		}	
	}
	return 0;
}

/*
	1.��Ӧʱ�������
	2.TAB ����һ����Ϣ ��һ�� down enter
	3.����
	*/
	//keybd_event�ĸ�������
		//1.ģ��ʲô��
		//2.��
		//3.ģ���������ʲô���� 0 ���� KEYECENTF_KEYUP ����
		//4.��
	//��ȷ��QQ����Ϊ�����
	//SetForegroundWindow(hwnd);