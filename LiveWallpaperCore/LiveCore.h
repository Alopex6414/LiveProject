/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCore.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-13
*/
#pragma once

#ifndef __LIVECORE_H_
#define __LIVECORE_H_

// Include Common Header File
#include "Common.h"

// Include LiveCore Header File
#include "LiveCoreLog.h"
#include "LiveCoreThreadWait.h"
#include "LiveCoreThreadUnpack.h"
#include "LiveCoreThreadMonitor.h"

// Class Definition
class CLiveCore
{
private:
	DirectGraphics* m_pMainGraphics;				// DirectX ��Ⱦ��ʵ��
	CCerasusfps* m_pMainfps;						// DirectX ֡����

private:
	IDirect3DDevice9* m_pD3D9Device;				// DirectX �����豸
	IDirect3DSurface9* m_pD3D9Surface;				// DirectX ���Ʊ���

private:
	int	m_nDeskTopWidth;							// Desktop ���
	int m_nDeskTopHeight;							// Desktop �߶�

	int m_nVideoWidth;								// Video ���
	int m_nVideoHeight;								// Video �߶�
	int m_nVideoFreq;								// Video Ƶ��

private:
	int m_nLiveCoreMode;							// LiveCore ģʽ: 0~���ģʽ 1~����ģʽ
	int m_nLiveCoreShowGraphics;					// LiveCore ��ʾ: 0~����ʾ�Կ��ͺ�(fps) 1~��ʾ�Կ��ͺ�(fps)
	int m_nLiveCoreShowGraphicsFont;				// LiveCore ��ʾ�����С
	int m_nLiveCoreWallpaperMode;					// LiveCore ��Ļ�ֱ���ģʽ: 0~��� 1~��Ӧ 2~���� 3~ƽ�� 4~����
	int m_nLiveCoreWallpaperAudioMode;				// LiveCore ��Ƶ����ģʽ: 0~��������Ƶ 1~������Ƶ
	int m_nLiveCoreLogProcess;						// LiveCore ��־��¼: 0~����¼���� 1~��¼����
	int m_nLiveCoreVideoMode;						// LiveCore ��̬��ֽ��Ƶģʽ: 0~����Ĭ����Ƶ 1~����ѡ����Ƶ
	char m_chLiveCoreVideoName[MAX_PATH];			// LiveCore ��̬��ֽĬ����Ƶ����
	char m_chLiveCoreVideoAddress[MAX_PATH];		// LiveCore ��̬��ֽ��Ƶ��ַ

protected:
	CLiveCoreThreadWait m_LiveCoreWait;
	CPlumThread* m_pPlumWait;

	CLiveCoreThreadUnpack m_LiveCoreUnpack;
	CPlumThread* m_pPlumUnpack;

	CLiveCoreThreadMonitor g_cLiveCoreMonitor;
	CPlumThread* g_pPlumMonitor;

public:
	CLiveCore();						// CLiveCore ����
	~CLiveCore();						// CLiveCore ����

	BOOL	CLiveCoreInit();			// CLiveCore ��ʼ��
	void	CLiveCoreRelease();			// CLiveCore �ͷ�

	void	CLiveCoreUpdate();			// CLiveCore ˢ��
	void	CLiveCoreRender();			// CLiveCore ��Ⱦ

protected:
	void	AnalyzeConfigFile();																						// CLiveCore ���������ļ�
	void	RecordConfigFile();																							// CLiveCore ��¼�����ļ�
	void	SetChildWindow(HWND);																						// CLiveCore ���������Ӵ���
	BOOL	AnalyzeVideoInfo(HWND hWnd, const char* pVideoPath, int* pWidth, int* pHeight, int* pFreq);					// CLiveCore ������Ƶ��Ϣ


};

extern CRITICAL_SECTION g_csDecode;
extern volatile bool g_bDecodeFlag;

extern CRITICAL_SECTION g_csWait;
extern volatile bool g_bWaitFlag;

extern bool g_bReStart;
extern bool g_bMonitorFlag;

extern unsigned char* g_pArrayY;
extern unsigned char* g_pArrayU;
extern unsigned char* g_pArrayV;

extern char g_chDefaultVideoAddress[MAX_PATH];
extern char g_chDefaultVideoDirector[MAX_PATH];
extern char g_chDefaultVideoUnpack[MAX_PATH];

#endif // !__LIVECORE_H_
