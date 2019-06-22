/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		WinMain.cpp
* @brief	This Program is LiveGraphicsCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-06-22
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
	int nResult;
	HRESULT hr;

	// start livecore process...
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "LiveWallpaperCore Process Commond Line: %s", lpCmdLine);

	// check process exist...
	HANDLE hMutex;
	hMutex = CreateMutex(NULL, TRUE, L"LiveWallpaperCore");
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			// process already exist...(exit)[-1]...
			CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Process Already Exist! Return Value=-1!");
			return -1;
		}
	}

	// windows application...
	hr = InitWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow, (LPCALLBACKSETWNDPARAFUNC)(&SetWindowParameterCallBack), (LPCALLBACKINITWNDEXTRAFUNC)(&InitWindowExtraCallBack));
	if (FAILED(hr))
	{
		// function initialization failed...(exit)[-1]...
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Initializa Failed! Return Value=-1!");
		return -1;
	}

	Msg = WinMainLoop((LPCALLBACKDIRECT3DRENDERFUNC)(&Direct3DRenderCallBack), (LPCALLBACKRELEASEWNDEXTRAFUNC)(&ReleaseWindowExtraCallBack));

	return Msg;
}