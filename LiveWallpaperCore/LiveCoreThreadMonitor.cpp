/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCoreThreadMonitor.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-14
*/
#include "LiveCoreThreadMonitor.h"

//------------------------------------------------------------------
// @Function:	 CLiveCoreThreadMonitor()
// @Purpose: CLiveCoreThreadMonitor构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThreadMonitor::CLiveCoreThreadMonitor() :
	m_bProcess(false)
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveCoreThreadMonitor()
// @Purpose: CLiveCoreThreadMonitor析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThreadMonitor::~CLiveCoreThreadMonitor()
{
}

//------------------------------------------------------------------
// @Function:	 PlumThreadRun()
// @Purpose: PlumThreadRun线程运行
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void __stdcall CLiveCoreThreadMonitor::PlumThreadRun()
{
	while (!g_bMonitorFlag)
	{
		if (!m_bProcess)
		{
			if (CPlumProcess::PlumProcessIsProcessExistExW(L"LiveCorePre.dll"))
			{
				m_bProcess = true;
			}
		}
		else
		{
			if (!CPlumProcess::PlumProcessIsProcessExistExW(L"LiveCorePre.dll"))
			{
				m_bProcess = false;
				g_bMonitorFlag = true;
			}
		}
	}
}
