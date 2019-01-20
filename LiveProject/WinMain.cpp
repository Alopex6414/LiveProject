/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		WinMain.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-19
*/
#include "WinMain.h"

/*
** WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nCmdShow)
** Purpose:  ����������
** Para: IN HINSTANCE hInstance			// ����ʵ�����(Win32)
** Para: IN HINSTANCE hPrevInstance		// ����ʵ�����(Win16)
** Para: IN LPSTR lpCmdLine				// ���������в�������<char*[]>
** Para: IN int nCmdShow				// ���������в�������<int>
** Return: INT Msg						// ����ֵ(��Ϣ����)
*/
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return -1;

	CFrameMain cMainFrame;
	cMainFrame.Create(NULL, _T("LiveProject"), WS_POPUP, WS_EX_WINDOWEDGE);
	cMainFrame.CenterWindow();
	cMainFrame.ShowModal();

	::CoUninitialize();

	return 0;
}