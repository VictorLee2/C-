/**************************************
	文件名称：main.cpp
	文件描述：
		微信的群发助手
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
	//提前复制好需要发送的内容
	//ctrv+v 先按下Ctrl，再按下V，弹起V，弹起Ctrl
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
	//QQ 窗口句柄（窗口的身份证）
	int errortimes = 0;

	while (errortimes < 4)
	{
		HWND hwnd;		//hwnd = (HWND)0x000208A2; QQ窗口句柄，每次打开窗口值会变，不建议
		hwnd = FindWindow(L"TXGuiFoundation", L"QQ");	//类名称和标题查找窗口的函数
		HWND fronthwnd = GetForegroundWindow();	//获取活动窗口句柄

		if (hwnd != fronthwnd)
		{
			if (!SetForegroundWindow(hwnd))
			{
				printf("找不到QQ窗口,请确保您已经登录!\n");
			}
		}
		if (errortimes == 0)
		{
			PressKey(VK_TAB);	//联系人
			PressKey(VK_TAB);	//好友
		}

		//PressKey(VK_DOWN);	
		PressKey(VK_RETURN);	//选定好友

		PressKey(VK_DOWN);		//选择分组
		PressKey(VK_RETURN);	//选定分组

		//循环开始？
		PressKey(VK_DOWN);		//选择好友
		PressKey(VK_RETURN);	//打开对话框

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
	1.反应时间的问题
	2.TAB 发送一个消息 用一次 down enter
	3.代码
	*/
	//keybd_event四个参数：
		//1.模拟什么键
		//2.？
		//3.模拟这个键的什么动作 0 按下 KEYECENTF_KEYUP 弹起
		//4.？
	//先确保QQ窗口为活动窗口
	//SetForegroundWindow(hwnd);