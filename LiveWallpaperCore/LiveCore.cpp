/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCore.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-13
*/
#include "LiveCore.h"

// CLiveCore��
int CLiveCore::m_nLiveCoreMode = 0;
int CLiveCore::m_nLiveCoreShowGraphics = 0;
int CLiveCore::m_nLiveCoreShowGraphicsFont = 0;
int CLiveCore::m_nLiveCoreWallpaperMode = 0;
int CLiveCore::m_nLiveCoreWallpaperAudioMode = 0;
int CLiveCore::m_nLiveCoreLogProcess = 0;
int CLiveCore::m_nLiveCoreVideoMode = 0;
char CLiveCore::m_chLiveCoreVideoName[MAX_PATH] = { 0 };
char CLiveCore::m_chLiveCoreVideoAddress[MAX_PATH] = { 0 };

//----------------------------------------------
// @Function:	CLiveCoreSetCmdLine()
// @Purpose: CLiveCore���������в���
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::CLiveCoreSetCmdLine(LPSTR lpCmdLine)
{
	memset(m_chLiveCoreVideoAddress, 0, MAX_PATH);
	memcpy_s(m_chLiveCoreVideoAddress, MAX_PATH, lpCmdLine, strlen(lpCmdLine));
}

//----------------------------------------------
// @Function:	CLiveCore()
// @Purpose: CLiveCore���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
CLiveCore::CLiveCore() :
	m_pDirectGraphicsMain(NULL),
	m_nDeskTopWidth(0),
	m_nDeskTopHeight(0)
{
}

//----------------------------------------------
// @Function:	~CLiveCore()
// @Purpose: CLiveCore��������
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
CLiveCore::~CLiveCore()
{
	SAFE_DELETE(m_pDirectGraphicsMain);
}

//----------------------------------------------
// @Function:	CLiveCoreInit()
// @Purpose: CLiveCore��ʼ��
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
BOOL CLiveCore::CLiveCoreInit()
{
	HRESULT hr;

	// ��ȡ���洰�ڷֱ���
	m_nDeskTopWidth = GetSystemMetrics(SM_CXSCREEN);
	m_nDeskTopHeight = GetSystemMetrics(SM_CYSCREEN);

	return TRUE;
}

//----------------------------------------------
// @Function:	CLiveCoreRelease()
// @Purpose: CLiveCore�ͷ�
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::CLiveCoreRelease()
{
}

//----------------------------------------------
// @Function:	CLiveCoreUpdate()
// @Purpose: CLiveCoreˢ��
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::CLiveCoreUpdate()
{
}

//----------------------------------------------
// @Function:	CLiveCoreRender()
// @Purpose: CLiveCore��Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::CLiveCoreRender()
{
}
