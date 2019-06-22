/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		WinProcess.cpp
* @brief	This Program is LiveGraphicsCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-06-22
*/
#include "WinProcess.h"
#include "WinUtilities.h"

float g_fLastTime = 0.0f;
float g_fCurrentTime = 0.0f;
float g_fDeltaTime = 0.0f;

//------------------------------------------------------------------
// @Function:	 SetWindowParameterCallBack(void)
// @Purpose: WinMain设置窗口相关参数回调函数
// @Since: v1.00a
// @Para: None
// @Return: WndPara*
//------------------------------------------------------------------
WndPara* SetWindowParameterCallBack(void)
{
	WndPara* pWindowParameter = new WndPara;
	pWindowParameter->nWndWidth = USER_WINDOWWIDTH;//窗口宽度
	pWindowParameter->nWndHeight = USER_WINDOWHEIGHT;//窗口高度
	pWindowParameter->lpszTitle = USER_WINDOWTITLE;//窗口标题名称
	pWindowParameter->wIcon = USER_WINDOWICON;//窗口标题图标
	return pWindowParameter;
}

//------------------------------------------------------------------
// @Function:	 InitWindowExtraCallBack(void)
// @Purpose: WinMain初始化窗口相关内容回调函数(DirectX 初始化)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL InitWindowExtraCallBack(void)
{
	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 ReleaseWindowExtraCallBack(void)
// @Purpose: WinMain释放窗口相关内容回调函数(DirectX 释放)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void ReleaseWindowExtraCallBack(void)
{
}

//------------------------------------------------------------------
// @Function:	 Direct3DRenderCallBack(void)
// @Purpose: Direct3D渲染相关回调函数(DirectX 渲染)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void Direct3DRenderCallBack(void)
{
	g_fLastTime = (float)timeGetTime() * 0.001f;
	g_fCurrentTime = (float)timeGetTime() * 0.001f;
	g_fDeltaTime = g_fCurrentTime - g_fLastTime;
}