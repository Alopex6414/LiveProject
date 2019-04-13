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
	int	m_nDeskTopWidth;							// Desktop ���
	int m_nDeskTopHeight;							// Desktop �߶�

private:
	static int m_nLiveCoreMode;								// LiveCore ģʽ: 0~���ģʽ 1~����ģʽ
	static int m_nLiveCoreShowGraphics;						// LiveCore ��ʾ: 0~����ʾ�Կ��ͺ�(fps) 1~��ʾ�Կ��ͺ�(fps)
	static int m_nLiveCoreShowGraphicsFont;					// LiveCore ��ʾ�����С
	static int m_nLiveCoreWallpaperMode;					// LiveCore ��Ļ�ֱ���ģʽ: 0~��� 1~��Ӧ 2~���� 3~ƽ�� 4~����
	static int m_nLiveCoreWallpaperAudioMode;				// LiveCore ��Ƶ����ģʽ: 0~��������Ƶ 1~������Ƶ
	static int m_nLiveCoreLogProcess;						// LiveCore ��־��¼: 0~����¼���� 1~��¼����
	static int m_nLiveCoreVideoMode;						// LiveCore ��̬��ֽ��Ƶģʽ: 0~����Ĭ����Ƶ 1~����ѡ����Ƶ
	static char m_chLiveCoreVideoName[MAX_PATH];			// LiveCore ��̬��ֽĬ����Ƶ����
	static char m_chLiveCoreVideoAddress[MAX_PATH];			// LiveCore ��̬��ֽ��Ƶ��ַ

public:
	static void	CLiveCoreSetCmdLine(LPSTR lpCmdLine);					// LiveCore ���������в���(��Ƶ��ַ)

public:
	CLiveCore();						// CLiveCore ����
	~CLiveCore();						// CLiveCore ����

	BOOL	CLiveCoreInit();			// CLiveCore ��ʼ��
	void	CLiveCoreRelease();			// CLiveCore �ͷ�

	void	CLiveCoreUpdate();			// CLiveCore ˢ��
	void	CLiveCoreRender();			// CLiveCore ��Ⱦ


};

#endif // !__LIVECORE_H_
