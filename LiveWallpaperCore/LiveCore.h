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

// Class Definition
class CLiveCore
{
private:
	DirectGraphics* m_pDirectGraphicsMain;			// DirectX ��Ⱦ��ʵ��

private:
	int	m_nDeskTopWidth;							// Desktop ����
	int m_nDeskTopHeight;							// Desktop �߶�

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
	CRITICAL_SECTION m_csDecode;					// LiveCore ��Ƶ����Cirtical
	volatile bool m_bDecodeFlag;					// LiveCore ��Ƶ�����־

	CRITICAL_SECTION m_csWait;						// LiveCore Ĭ����ƵCirtical
	volatile bool g_bWaitFlag;						// LiveCore Ĭ����Ƶ��־


public:
	CLiveCore();						// CLiveCore ����
	~CLiveCore();						// CLiveCore ����

	BOOL	CLiveCoreInit();			// CLiveCore ��ʼ��
	void	CLiveCoreRelease();			// CLiveCore �ͷ�

	void	CLiveCoreUpdate();			// CLiveCore ˢ��
	void	CLiveCoreRender();			// CLiveCore ��Ⱦ

protected:
	void	AnalyzeConfigFile();		// CLiveCore ���������ļ�
	void	RecordConfigFile();			// CLiveCore ��¼�����ļ�


};

#endif // !__LIVECORE_H_