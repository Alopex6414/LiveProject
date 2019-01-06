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

#include "LiveIn.h"

// Variable
CLiveIn g_cLiveIn;

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
	return g_cLiveIn.CLiveInInit();
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
	g_cLiveIn.CLiveInRelease();
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
	g_cLiveIn.CLiveInUpdate();
	g_cLiveIn.CLiveInRender();
}