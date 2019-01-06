/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveIn.h
* @brief	This Program is LiveIn Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-05
*/
#pragma once

#ifndef __LIVEIN_H_
#define __LIVEIN_H_

// Include Common Header File
#include "Common.h"

// Include LiveIn Header File
#include "LiveInlog.h"
#include "LiveInres.h"

// Class Definition
class CLiveIn
{
private:
	DirectGraphics * m_pDirectGraphicsMain;			// DirectX ��Ⱦ��ʵ��
	DirectGraphics3D * m_pDirectGraphics3DMain;		// DirectX ��Ⱦ��ʵ��(3D)

private:
	CCerasusfps * m_pCerasusfpsMain;				// DirectX fpsʵ��

public:
	CSakuraResourceManager * m_pResourceManager;	// Sakura ��Դ������
	CSakuraDialog* m_pSakuraDialog;					// Sakura ����

private:
	int m_nIsUseLog;			// CLiveIn �Ƿ�������־�ļ���¼
	int m_nIsShowAdapter;		// CLiveIn �Ƿ���ʾ�Կ��ͺ�
	int m_nIsShowFps;			// CLiveIn �Ƿ���ʾFps

	char m_chPacketRes_bk_00[8192];					// CLiveIn ����bk_00��Դ(��ɫ����)
	char m_chPacketRes_title_00[8192];				// CLiveIn ����title_00��Դ(LiveProject)
	char m_chPacketRes_title_01[8192];				// CLiveIn ����title_01��Դ(�饤�֥ץ���������)
	char m_chPacketRes_title_02[8192];				// CLiveIn ����title_02��Դ(��Ȩ)

protected:
	void CLiveDrawAdapter();	// CLiveIn �����Կ���Ϣ
	void CLiveDrawfps();		// CLiveIn ����fps

	void CLiveInAddPacketResBK00(CUUintEx& sUnitEx);			// CLiveIn ���ر���bk_00��Դ�ṹ
	void CLiveInAddPacketResTITLE00(CUUintEx& sUnitEx);			// CLiveIn ���ر���title_00��Դ�ṹ
	void CLiveInAddPacketResTITLE01(CUUintEx& sUnitEx);			// CLiveIn ���ر���title_01��Դ�ṹ
	void CLiveInAddPacketResTITLE02(CUUintEx& sUnitEx);			// CLiveIn ���ر���title_02��Դ�ṹ

public:
	CLiveIn();					// CLiveIn ����
	~CLiveIn();					// CLiveIn ����

	BOOL CLiveInInit();			// CLiveIn ��ʼ��
	void CLiveInRelease();		// CLiveIn �ͷ�

	void CLiveInUpdate();		// CLiveIn ˢ��
	void CLiveInRender();		// CLiveIn ��Ⱦ

protected:
	BOOL CLiveInReadConfigFile();	// CLiveIn ��ȡ�����ļ�
	BOOL CLiveInLoadPacketFile();	// CLiveIn ���ط���ļ�

};

extern void __stdcall CLiveInSakuraGUIEvent(UINT nEvent, int nControlID, CSakuraControl * pControl, void * pUserContext);

#endif // !__LIVEIN_H_
