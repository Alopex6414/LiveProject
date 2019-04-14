/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCoreThreadWait.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-14
*/
#include "LiveCoreThreadWait.h"

//------------------------------------------------------------------
// @Function:	 CLiveCoreThreadWait()
// @Purpose: CLiveCoreThreadWait构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThreadWait::CLiveCoreThreadWait()
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveCoreThreadWait()
// @Purpose: CLiveCoreThreadWait析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThreadWait::~CLiveCoreThreadWait()
{
}

//------------------------------------------------------------------
// @Function:	 PlumThreadRun()
// @Purpose: CLiveCoreThreadWait线程运行
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void __stdcall CLiveCoreThreadWait::PlumThreadRun()
{
	m_cLiveCoreWait.LiveCoreWaitInit();

	while (true)	// 这里需要添加退出等待的条件...
	{
		m_cLiveCoreWait.LiveCoreWaitUpdate();
		m_cLiveCoreWait.LiveCoreWaitRender();

		if (m_cLiveCoreWait.m_bUnpackStop)
		{
			if (m_cLiveCoreWait.m_bSakuraStop)
			{
				break;
			}
		}

		EnterCriticalSection(&g_csWait);
		if (!g_bWaitFlag)
		{
			m_cLiveCoreWait.m_bUnpackStop = true;
			//LeaveCriticalSection(&g_csWait);
			//break;
		}
		LeaveCriticalSection(&g_csWait);
	}

}