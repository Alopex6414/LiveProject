/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Alopex/Helium
*     All rights reserved.
*
* @file		WinProcess.cpp
* @brief	This Program is WinProcess DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2017-11-29
*/
#include "WinProcess.h"
#include "WinUtilities.h"

#include "LiveCore.h"

CLiveCore g_LiveCore;

float g_fLastTime = 0.0f;
float g_fCurrentTime = 0.0f;
float g_fDeltaTime = 0.0f;

//------------------------------------------------------------------
// @Function:	 SetWindowParameterCallBack(void)
// @Purpose: WinMain���ô�����ز����ص�����
// @Since: v1.00a
// @Para: None
// @Return: WndPara*
//------------------------------------------------------------------
WndPara* SetWindowParameterCallBack(void)
{
	WndPara* pWindowParameter = new WndPara;
	pWindowParameter->nWndWidth = USER_WINDOWWIDTH;//���ڿ��
	pWindowParameter->nWndHeight = USER_WINDOWHEIGHT;//���ڸ߶�
	pWindowParameter->lpszTitle = USER_WINDOWTITLE;//���ڱ�������
	pWindowParameter->wIcon = USER_WINDOWICON;//���ڱ���ͼ��
	return pWindowParameter;
}

//------------------------------------------------------------------
// @Function:	 InitWindowExtraCallBack(void)
// @Purpose: WinMain��ʼ������������ݻص�����(DirectX ��ʼ��)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL InitWindowExtraCallBack(void)
{
	return g_LiveCore.CLiveCoreInit();
}

//------------------------------------------------------------------
// @Function:	 ReleaseWindowExtraCallBack(void)
// @Purpose: WinMain�ͷŴ���������ݻص�����(DirectX �ͷ�)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void ReleaseWindowExtraCallBack(void)
{
	g_LiveCore.CLiveCoreRelease();
}

//------------------------------------------------------------------
// @Function:	 Direct3DRenderCallBack(void)
// @Purpose: Direct3D��Ⱦ��ػص�����(DirectX ��Ⱦ)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void Direct3DRenderCallBack(void)
{
	float fDeltaTime = 1.0f / g_LiveCore.m_nVideoFreq;

	g_fLastTime = (float)timeGetTime()*0.001f;

	g_LiveCore.CLiveCoreUpdate();
	g_LiveCore.CLiveCoreRender();

	g_fCurrentTime = (float)timeGetTime()*0.001f;
	g_fDeltaTime = g_fCurrentTime - g_fLastTime;
	
	if (g_fDeltaTime < fDeltaTime)
	{
		Sleep((DWORD)((fDeltaTime - g_fDeltaTime) * 1000.0f));
	}
}