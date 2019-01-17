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
#include "LiveIntype.h"

// Class Definition
class CLiveIn
{
private:
	DirectGraphics * m_pDirectGraphicsMain;			// DirectX ��Ⱦ��ʵ��
	DirectGraphics3D * m_pDirectGraphics3DMain;		// DirectX ��Ⱦ��ʵ��(3D)
	DirectSprite * m_pDirectSprite;					// DirectX ��Ⱦ����

private:
	CCerasusfps * m_pCerasusfpsMain;				// DirectX fpsʵ��

public:
	CSakuraResourceManager * m_pResourceManager;	// Sakura ��Դ������
	CSakuraDialog * m_pSakuraDialog;				// Sakura ����

private:
	int m_nIsUseLog;			// CLiveIn �Ƿ�������־�ļ���¼
	int m_nIsShowAdapter;		// CLiveIn �Ƿ���ʾ�Կ��ͺ�
	int m_nIsShowFps;			// CLiveIn �Ƿ���ʾFps
	int m_nSpriteNum;			// CLiveIn ����������

	float m_fTimeSum;			// CLiveIn ��ʽ����ʱ���ۻ�
	bool m_bSpriteRender;		// CLiveIn ��������Ⱦ״̬

	char m_chPacketRes_bk_00[8192];					// CLiveIn ����bk_00��Դ(��ɫ����)
	char m_chPacketRes_title_00[8192];				// CLiveIn ����title_00��Դ(LiveProject)
	char m_chPacketRes_title_01[8192];				// CLiveIn ����title_01��Դ(�饤�֥ץ�������)
	char m_chPacketRes_title_02[8192];				// CLiveIn ����title_02��Դ(��Ȩ)
	char m_chPacketRes_wait_00[4096];				// CLiveIn ����wait_00��Դ(������)
	char m_chPacketRes_wait_01[8192];				// CLiveIn ����wait_01��Դ(���Ժ�...)
	char m_chPacketRes_login_00[8192];				// CLiveIn ��ťlogin_00��Դ(��¼)
	char m_chPacketRes_account_00[32768];			// CLiveIn ����account_00��Դ(�˻�)
	char m_chPacketRes_sprite_00[4096];				// CLiveIn ����sprite_00��Դ(����)

private:
	int m_nStarPosX;			// CLiveIn ��������--X
	int m_nStarPosY;			// CLiveIn ��������--Y
	int m_nStarWidth;			// CLiveIn ��������--���
	int m_nStarHeight;			// CLiveIn ��������--�߶�

	vector<TLIVEINSTAR>	m_vecStarArray;				// CLiveIn ������������

protected:
	void CLiveDrawAdapter();	// CLiveIn �����Կ���Ϣ
	void CLiveDrawfps();		// CLiveIn ����fps

	void CLiveInAddPacketResBK00(CUUintEx& sUnitEx);			// CLiveIn ���ر���bk_00��Դ�ṹ
	void CLiveInAddPacketResTITLE00(CUUintEx& sUnitEx);			// CLiveIn ���ر���title_00��Դ�ṹ
	void CLiveInAddPacketResTITLE01(CUUintEx& sUnitEx);			// CLiveIn ���ر���title_01��Դ�ṹ
	void CLiveInAddPacketResTITLE02(CUUintEx& sUnitEx);			// CLiveIn ���ر���title_02��Դ�ṹ
	void CLiveInAddPacketResWAIT01_0(CUUintEx& sUnitEx);		// CLiveIn ���ر���wait_01��Դ�ṹ(���Ժ�)
	void CLiveInAddPacketResWAIT01_1(CUUintEx& sUnitEx);		// CLiveIn ���ر���wait_01��Դ�ṹ(���Ժ�.)
	void CLiveInAddPacketResWAIT01_2(CUUintEx& sUnitEx);		// CLiveIn ���ر���wait_01��Դ�ṹ(���Ժ�..)
	void CLiveInAddPacketResWAIT01_3(CUUintEx& sUnitEx);		// CLiveIn ���ر���wait_01��Դ�ṹ(���Ժ�...)
	void CLiveInAddPacketResWAIT00_0(CUUintEx& sUnitEx);		// CLiveIn ���ر���wait_00��Դ�ṹ(��)
	void CLiveInAddPacketResWAIT00_1(CUUintEx& sUnitEx);		// CLiveIn ���ر���wait_00��Դ�ṹ(��)
	void CLiveInAddPacketResWAIT00_2(CUUintEx& sUnitEx);		// CLiveIn ���ر���wait_00��Դ�ṹ(��)
	void CLiveInAddPacketResWAIT00_3(CUUintEx& sUnitEx);		// CLiveIn ���ر���wait_00��Դ�ṹ(��)
	void CLiveInAddPacketResWAIT00_4(CUUintEx& sUnitEx);		// CLiveIn ���ر���wait_00��Դ�ṹ(��)
	void CLiveInAddPacketResLOGIN00(CUUintEx& sUnitEx);			// CLiveIn ���ذ�ťlogin_00��Դ(��¼)
	void CLiveInAddPacketResACCOUNT00(CUUintEx& sUnitEx);		// CLiveIn ���ر���account_00��Դ(�˻�)

public:
	CLiveIn();					// CLiveIn ����
	~CLiveIn();					// CLiveIn ����

	BOOL CLiveInInit();			// CLiveIn ��ʼ��
	void CLiveInRelease();		// CLiveIn �ͷ�

	void CLiveInUpdate();		// CLiveIn ˢ��
	void CLiveInRender();		// CLiveIn ��Ⱦ

	void CLiveInStartUpdate(float fDeltaTime);					// CLiveIn ��ʼ����ˢ��

protected:
	BOOL CLiveInReadConfigFile();	// CLiveIn ��ȡ�����ļ�
	BOOL CLiveInLoadPacketFile();	// CLiveIn ���ط���ļ�

	void CLiveInSetSpriteArea(int nX, int nY, int nWidth, int nHeight);		// CLiveIn �������ӳ�������
	void CLiveInInitSprite();												// CLiveIn ��ʼ������ϵͳ

	void CLiveInUpdateSprite();		// CLiveIn ˢ������
	void CLiveInRenderSprite();		// CLiveIn ��Ⱦ����

};

extern void __stdcall CLiveInSakuraGUIEvent(UINT nEvent, int nControlID, CSakuraControl * pControl, void * pUserContext);

#endif // !__LIVEIN_H_

