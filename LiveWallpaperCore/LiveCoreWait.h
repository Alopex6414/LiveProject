/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCoreWait.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-14
*/
#pragma once

#ifndef __LIVECOREWAIT_H_
#define	__LIVECOREWAIT_H_

// Include Common Header File
#include "Common.h"

// Include Resource Header File
#include "resource.h"

// Macro Definition
#define LIVECOREWAIT_DLG_WIDTH	640
#define LIVECOREWAIT_DLG_HEIGHT	480
#define LIVECOREWAIT_PARTICLE_NUMBER	1000

#define LIVECOREWAIT_CALLMODE	__stdcall

// Type Definition
typedef struct
{
	float fAlpha;										// ����Alphaֵ
	int nMoveDirect;									// �����ƶ�����
	int nRotateDirect;									// ������ת����
	float fFallSpeed;									// ���������ٶ�
	float fMoveSpeed;									// �����ƶ��ٶ�
	float fRotateSpeed;									// ������ת�ٶ�
	S_DX_SPRITE_TRANSFORM_PARA sTransformPara;			// ���ӱ任����
}TLiveCoreSakura, * LPTLiveCoreSakura;

// Class Definition
class CLiveCoreWait
{
private:
	DirectGraphics*		m_pLiveWaitGraphics;
	DirectGraphics2D*	m_pLiveWaitGraphics2D;
	DirectTexture*		m_pLiveWaitTexture;
	DirectSprite*		m_pLiveWaitSprite;

private:
	HWND m_hWnd;
	TCHAR m_tcTexturePath[MAX_PATH];
	TCHAR m_tcSpritePath[MAX_PATH];

	bool m_bShow;

private:
	int m_nSakuraPosX;									// ��������--X
	int m_nSakuraPosY;									// ��������--Y
	int m_nSakuraWidth;									// ��������--���
	int m_nSakuraHeight;								// ��������--�߶�

	TLiveCoreSakura m_arrSakura[LIVECOREWAIT_PARTICLE_NUMBER];			// ӣ������

public:
	int m_nSakuraCount;									// ���Ӽ���
	bool m_bUnpackStop;									// ����߳�ֹͣ
	bool m_bSakuraStop;									// ������Ⱦֹͣ

protected:
	BOOL LIVECOREWAIT_CALLMODE LiveCoreWait_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);
	BOOL LIVECOREWAIT_CALLMODE LiveCoreWait_Texture_GetPath(LPCSTR szFile);
	BOOL LIVECOREWAIT_CALLMODE LiveCoreWait_Sprite_GetPath(LPCSTR szFile);

public:
	CLiveCoreWait();
	~CLiveCoreWait();

	BOOL LIVECOREWAIT_CALLMODE LiveCoreWaitInit();
	void LIVECOREWAIT_CALLMODE LiveCoreWaitUpdate();
	void LIVECOREWAIT_CALLMODE LiveCoreWaitRender();
	void LIVECOREWAIT_CALLMODE LiveCoreWaitShowWindow();

	void LIVECOREWAIT_CALLMODE LiveCoreWaitSetSakura(int nX, int nY, int nWidth, int nHeight);
	void LIVECOREWAIT_CALLMODE LiveCoreWaitInitSakura();
	void LIVECOREWAIT_CALLMODE LiveCoreWaitUpdateSakura();
	void LIVECOREWAIT_CALLMODE LiveCoreWaitRenderSakura();

	void LIVECOREWAIT_CALLMODE LiveCoreWaitSakuraSetFlag(bool bStop);

public:
	static LRESULT LiveCoreWaitProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

};

#endif // !__LIVECOREWAIT_H_

