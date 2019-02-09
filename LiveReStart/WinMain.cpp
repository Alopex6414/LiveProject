/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		WinMain.cpp
* @brief	This Program is LiveReStart Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-19
*/
#include "WinMain.h"

/*
** WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nCmdShow)
** Purpose:  窗口主函数
** Para: IN HINSTANCE hInstance			// 窗口实例句柄(Win32)
** Para: IN HINSTANCE hPrevInstance		// 窗口实例句柄(Win16)
** Para: IN LPSTR lpCmdLine				// 窗口命令行参数数组<char*[]>
** Para: IN int nCmdShow				// 窗口命令行参数数量<int>
** Return: INT Msg						// 返回值(消息参数)
*/
int WINAPI WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nCmdShow)
{
	int nResult = 0;

	// start restart process...
	CLiveReStartLog::LiveReStartLogExWriteLine(__FILE__, __LINE__, "ReStart Process: %s", lpCmdLine);

	// check commond lines...
	nResult = strcmp(lpCmdLine, "");
	if (nResult == 0)
	{
		// no commond lines...(exit)[1]...
		CLiveReStartLog::LiveReStartLogExWriteLine(__FILE__, __LINE__, "Process Exception Exit! Return Value=1, No CmdLine Parameter!");
		return 1;
	}

	// check process exist...
	while (true)
	{
		if (!CPlumProcess::PlumProcessIsProcessExistExA(lpCmdLine))
		{
			CLiveReStartLog::LiveReStartLogExWriteLine(__FILE__, __LINE__, "Check Process Status: Process Exit.");
			Sleep(100);
			break;
		}

		CLiveReStartLog::LiveReStartLogExWriteLine(__FILE__, __LINE__, "Check Process Status: Process Exist.");
		Sleep(100);
	}

	// restart process...
	BOOL bResult;

	bResult = CPlumProcess::PlumProcessStartProcessExA(lpCmdLine);
	if (!bResult)
	{
		// can not restart process!...(exit)[2]...
		CLiveReStartLog::LiveReStartLogExWriteLine(__FILE__, __LINE__, "Process Exception Exit! Return Value=2, Can not ReStart Process!");
		return 2;
	}

	// restart process normal exit...(exit)[0]...
	CLiveReStartLog::LiveReStartLogExWriteLine(__FILE__, __LINE__, "Process Exit! Return Value=0.");

	return 0;
}