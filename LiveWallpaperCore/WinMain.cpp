/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		WinMain.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-05
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
int WINAPI WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nCmdShow)
{
	int Msg;
	HRESULT hr;

	HANDLE hMutex;
	hMutex = CreateMutex(NULL, TRUE, L"LiveWallpaperCore");
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			return -1;
		}
	}

	hr = InitWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow, (LPCALLBACKSETWNDPARAFUNC)(&SetWindowParameterCallBack), (LPCALLBACKINITWNDEXTRAFUNC)(&InitWindowExtraCallBack));
	if (FAILED(hr))
	{
		return -1;
	}

	Msg = WinMainLoop((LPCALLBACKDIRECT3DRENDERFUNC)(&Direct3DRenderCallBack), (LPCALLBACKRELEASEWNDEXTRAFUNC)(&ReleaseWindowExtraCallBack));

	return Msg;
}