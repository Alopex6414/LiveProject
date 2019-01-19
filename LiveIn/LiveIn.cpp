/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveIn.cpp
* @brief	This Program is LiveIn Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-05
*/
#include "LiveIn.h"

// CLiveIn��

//----------------------------------------------
// @Function:	CLiveIn()
// @Purpose: CLiveIn���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
CLiveIn::CLiveIn() :m_nIsUseLog(0), m_nIsShowAdapter(0), m_nIsShowFps(0), m_nSpriteNum(0), m_fTimeSum(0.0f), m_bSpriteRender(false)
{
	m_pDirectGraphicsMain = NULL;
	m_pDirectGraphics3DMain = NULL;
	m_pDirectSprite = NULL;
	m_pCerasusfpsMain = NULL;
	m_pResourceManager = NULL;
	m_pSakuraDialog = NULL;

	m_nStarPosX = 0;
	m_nStarPosY = 0;
	m_nStarWidth = 0;
	m_nStarHeight = 0;
	m_vecStarArray.clear();

	memset(m_chPacketRes_bk_00, 0, sizeof(m_chPacketRes_bk_00));
	memset(m_chPacketRes_title_00, 0, sizeof(m_chPacketRes_title_00));
	memset(m_chPacketRes_title_01, 0, sizeof(m_chPacketRes_title_01));
	memset(m_chPacketRes_title_02, 0, sizeof(m_chPacketRes_title_02));
	memset(m_chPacketRes_wait_00, 0, sizeof(m_chPacketRes_wait_00));
	memset(m_chPacketRes_wait_01, 0, sizeof(m_chPacketRes_wait_01));
	memset(m_chPacketRes_login_00, 0, sizeof(m_chPacketRes_login_00));
	memset(m_chPacketRes_account_00, 0, sizeof(m_chPacketRes_account_00));
	memset(m_chPacketRes_sprite_00, 0, sizeof(m_chPacketRes_sprite_00));
}

//----------------------------------------------
// @Function:	~CLiveIn()
// @Purpose: CLiveIn��������
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
CLiveIn::~CLiveIn()
{
	SAFE_DELETE(m_pSakuraDialog);
	SAFE_DELETE(m_pResourceManager);
	SAFE_DELETE(m_pCerasusfpsMain);
	SAFE_DELETE(m_pDirectSprite);
	SAFE_DELETE(m_pDirectGraphics3DMain);
	SAFE_DELETE(m_pDirectGraphicsMain);
}

//----------------------------------------------
// @Function:	CLiveInInit()
// @Purpose: CLiveIn��ʼ��
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
BOOL CLiveIn::CLiveInInit()
{
	HRESULT hr;
	IDirect3DDevice9* pD3D9Device = NULL;

	// CLiveIn ��ȡ�����ļ���Ϣ
	BOOL bRet = FALSE;
	bRet = CLiveInReadConfigFile();
	if (!bRet)
	{
		MessageBox(g_hWnd, _T("LiveIn��ȡ�����ļ�ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "LiveInӦ�ó�����.");
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "LiveIn��ȡlua�ļ��ɹ�.m_nIsUseLog=%d,m_nIsShowAdapter=%d,m_nIsShowFps=%d.", m_nIsUseLog, m_nIsShowAdapter, m_nIsShowFps);

	// DirectGraphics ��ʼ��
	m_pDirectGraphicsMain = new DirectGraphics();
	hr = m_pDirectGraphicsMain->DirectGraphicsInit(g_hWnd, true, USER_WINDOWWIDTH, USER_WINDOWHEIGHT);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "Direct3D��ʼ��ʧ��!����ֵhr=%l.", hr);
		MessageBox(g_hWnd, _T("Direct3D��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "Direct3D��ʼ���ɹ�!");

	hr = m_pDirectGraphicsMain->DirectGraphicsFontInit(20);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectFont��ʼ��ʧ��!����ֵhr=%l.", hr);
		MessageBox(g_hWnd, _T("DirectFont��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectFont��ʼ���ɹ�!");

	pD3D9Device = m_pDirectGraphicsMain->DirectGraphicsGetDevice();		// DirectX�豸ָ��

	// DirectGraphics3D ��ʼ��
	m_pDirectGraphics3DMain = new DirectGraphics3D(pD3D9Device);
	hr = m_pDirectGraphics3DMain->DirectGraphics3DInitVertex3DBase(6);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectGraphics3D��ʼ��ʧ��!����ֵhr=%l.", hr);
		MessageBox(g_hWnd, _T("DirectGraphics3D��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectGraphics3D��ʼ���ɹ�!");

	// Cerasusfps ��ʼ��
	m_pCerasusfpsMain = new CCerasusfps(pD3D9Device);
	hr = m_pCerasusfpsMain->CCerasusfpsInit(20);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "Cerasusfps��ʼ��ʧ��!����ֵhr=%l.", hr);
		MessageBox(g_hWnd, _T("Cerasusfps��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "Cerasusfps��ʼ���ɹ�!");

	// CLiveIn ������Դ�ļ�
	CLiveInLoadPacketFile();

	// DirectSprite ��ʼ��
	m_pDirectSprite = new DirectSprite(pD3D9Device);
	hr = m_pDirectSprite->DirectSpriteInit(m_chPacketRes_sprite_00, sizeof(m_chPacketRes_sprite_00), 32, 32);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectSprite��ʼ��ʧ��!����ֵhr=%l.", hr);
		MessageBox(g_hWnd, _T("DirectSprite��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectSprite��ʼ���ɹ�!");

	CLiveInSetSpriteArea(0, 0, 320, 480);
	CLiveInInitSprite();

	// SakuraResourceManager ��ʼ��
	m_pResourceManager = new CSakuraResourceManager();
	m_pResourceManager->OnCreate(pD3D9Device);

	CUUintEx sUnitEx_bk_00 = { 0 };
	CLiveInAddPacketResBK00(sUnitEx_bk_00);

	// SakuraDialog ��ʼ��
	m_pSakuraDialog = new CSakuraDialog();
	m_pSakuraDialog->OnCreate(m_pResourceManager, sUnitEx_bk_00);
	m_pSakuraDialog->SetLocation(0, 0);
	m_pSakuraDialog->SetSize(USER_WINDOWWIDTH, USER_WINDOWHEIGHT);
	m_pSakuraDialog->SetCallback(CLiveInSakuraGUIEvent, this);

	// SakuraResourceManager ��Դ����
	CUUintEx sUnitEx_title_00 = { 0 };
	CLiveInAddPacketResTITLE00(sUnitEx_title_00);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_title_00);

	CUUintEx sUnitEx_title_01 = { 0 };
	CLiveInAddPacketResTITLE01(sUnitEx_title_01);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_title_01);

	CUUintEx sUnitEx_title_02 = { 0 };
	CLiveInAddPacketResTITLE02(sUnitEx_title_02);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_title_02);

	CUUintEx sUnitEx_wait_010 = { 0 };
	CLiveInAddPacketResWAIT01_0(sUnitEx_wait_010);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_010);

	CUUintEx sUnitEx_wait_011 = { 0 };
	CLiveInAddPacketResWAIT01_1(sUnitEx_wait_011);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_011);

	CUUintEx sUnitEx_wait_012 = { 0 };
	CLiveInAddPacketResWAIT01_2(sUnitEx_wait_012);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_012);

	CUUintEx sUnitEx_wait_013 = { 0 };
	CLiveInAddPacketResWAIT01_3(sUnitEx_wait_013);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_013);

	CUUintEx sUnitEx_wait_000 = { 0 };
	CLiveInAddPacketResWAIT00_0(sUnitEx_wait_000);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_000);

	CUUintEx sUnitEx_wait_001 = { 0 };
	CLiveInAddPacketResWAIT00_1(sUnitEx_wait_001);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_001);

	CUUintEx sUnitEx_wait_002 = { 0 };
	CLiveInAddPacketResWAIT00_2(sUnitEx_wait_002);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_002);

	CUUintEx sUnitEx_wait_003 = { 0 };
	CLiveInAddPacketResWAIT00_3(sUnitEx_wait_003);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_003);

	CUUintEx sUnitEx_wait_004 = { 0 };
	CLiveInAddPacketResWAIT00_4(sUnitEx_wait_004);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_004);

	// ��½��ť��Դ
	CUUintEx sUnitEx_login_00 = { 0 };
	CLiveInAddPacketResLOGIN00(sUnitEx_login_00);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_login_00);

	// �˻�������Դ
	CUUintEx sUnitEx_account_00 = { 0 };
	CLiveInAddPacketResACCOUNT00(sUnitEx_account_00);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_account_00);

	// SakuraControl ��ʼ��
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_TITLE_00, 32, 64, 256, 64);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_TITLE_01, 32, 128, 256, 32);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_TITLE_02, 32, 432, 256, 32);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_WAIT_010, 134, 233, 52, 14);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_WAIT_011, 134, 233, 52, 14);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_WAIT_012, 134, 233, 52, 14);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_WAIT_013, 134, 233, 52, 14);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_WAIT_001, 0, 250, 11, 11);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_WAIT_002, 0, 250, 11, 11);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_WAIT_003, 0, 250, 11, 11);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_WAIT_004, 0, 250, 11, 11);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_WAIT_005, 0, 250, 11, 11);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_ACCOUNT_00, 120, 200, 80, 110);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_LOGIN_00, 70, 360, 180, 40);

	m_pSakuraDialog->AddButton(SID_SAKURABUTTON_LOGIN_00, NULL, 70, 360, 180, 40, 0U, true);

	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_TITLE_00, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 0);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_TITLE_01, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 1);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_TITLE_02, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 2);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_WAIT_010, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 3);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_WAIT_011, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 4);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_WAIT_012, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 5);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_WAIT_013, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 6);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_WAIT_001, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 7);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_WAIT_002, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 8);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_WAIT_003, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 9);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_WAIT_004, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 10);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_WAIT_005, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 11);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_LOGIN_00, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 12);
	m_pSakuraDialog->AddTextureEx(SID_SAKURABUTTON_LOGIN_00, SAKURA_CONTROL_BUTTON, 0, SAKURA_STATE_NORMAL, 12);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_ACCOUNT_00, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 13);

	m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_011)->SetVisible(false);
	m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_012)->SetVisible(false);
	m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_013)->SetVisible(false);
	m_pSakuraDialog->GetButton(SID_SAKURABUTTON_LOGIN_00)->SetVisible(false);

	return TRUE;
}

//----------------------------------------------
// @Function:	CLiveInRelease()
// @Purpose: CLiveIn�ͷ�
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInRelease()
{
	SAFE_DELETE(m_pSakuraDialog);
	SAFE_DELETE(m_pResourceManager);
	SAFE_DELETE(m_pCerasusfpsMain);
	SAFE_DELETE(m_pDirectSprite);
	SAFE_DELETE(m_pDirectGraphics3DMain);
	SAFE_DELETE(m_pDirectGraphicsMain);

	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "LiveInӦ�ó������.");
}

//----------------------------------------------
// @Function:	CLiveInUpdate()
// @Purpose: CLiveInˢ��
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInUpdate()
{
	HRESULT hr;
	IDirect3DSurface9* pD3D9Surface = NULL;

	// DirectGraphics �����豸Э������
	hr = m_pDirectGraphicsMain->DirectGraphicsTestCooperativeLevel();
	if (hr != S_OK)
	{
		if (hr == D3DERR_DEVICELOST)	// DirectX �豸��ʧ
		{
			return;
		}

		if (hr == D3DERR_DEVICENOTRESET)	// DirectX �豸����
		{
			HRESULT hr2;

			// ��ʧ�豸
			hr2 = m_pCerasusfpsMain->CCerasusfpsReset();
			hr2 = m_pDirectGraphics3DMain->DirectGraphics3DReset();
			m_pSakuraDialog->OnLost();
			m_pDirectSprite->DirectSpriteReset();
			hr2 = m_pDirectGraphicsMain->DirectGraphicsReset();

			// �����豸
			m_pSakuraDialog->OnReset();
			hr2 = m_pDirectGraphics3DMain->DirectGraphics3DInitVertex3DBase(6);
			hr2 = m_pDirectSprite->DirectSpriteInit(m_chPacketRes_sprite_00, sizeof(m_chPacketRes_sprite_00), 32, 32);
		}

	}

	m_fTimeSum += g_fDeltaTime;	// ��ʽʱ���ۻ�

	CLiveInStartUpdate(g_fDeltaTime);

}

//----------------------------------------------
// @Function:	CLiveInRender()
// @Purpose: CLiveIn��Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInRender()
{
	IDirect3DDevice9* pD3D9Device = NULL;
	RECT Rect;

	GetClientRect(g_hWnd, &Rect);
	pD3D9Device = m_pDirectGraphicsMain->DirectGraphicsGetDevice();

	// DirectX ��ʼ����
	m_pDirectGraphicsMain->DirectGraphicsBegin();

	// ��Ⱦģʽ:Alpha�������
	pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);					// Alpha��Ͽ���

	// ��Ⱦģʽ:����������
	pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);

	m_pDirectGraphics3DMain->DirectGraphics3DRenderStateLightDisable();			// ��Ⱦ��Դ�ر�
	m_pDirectGraphics3DMain->DirectGraphics3DRenderStateSetting();				// ��Ⱦ״̬����
	m_pDirectGraphics3DMain->DirectGraphics3DRenderStateAlphaDisable();			// Alpha��Ϲر�

	m_pSakuraDialog->OnRender();	// ����Sakura

	if (m_bSpriteRender)			// ��Ⱦ����ϵͳ
	{
		CLiveInRenderSprite();
	}

	if (m_nIsShowAdapter != 0)
	{
		CLiveDrawAdapter();			// �����Կ��ͺ�
	}
	
	if (m_nIsShowFps != 0)
	{
		CLiveDrawfps();				// ����fps
	}

	// DirectX ��������
	m_pDirectGraphicsMain->DirectGraphicsEnd();
}

//----------------------------------------------
// @Function:	CLiveInStartUpdate(float fDeltaTime)
// @Purpose: CLiveIn��ʼ����ˢ��
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInStartUpdate(float fDeltaTime)
{
	static float fTimeSum = 0.0f;

	fTimeSum += fDeltaTime;		// ����ʱ���ۼ�...

	if (fTimeSum < 0.5f)		// ��ʼʱ��0.0s~0.5sʱ���ֺ�ɫ��Ļ,Alphaͨ��ֵΪ0.0f
	{
		m_pSakuraDialog->GetDialogGraphics()->CCerasusUnitGetAlpha() = 0.0f;	// ����Alphaͨ��ֵΪ0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Logo Alphaͨ��ֵΪ0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_01)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Logo2 Alphaͨ��ֵΪ0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_02)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Coypright Alphaͨ��ֵΪ0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_010)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Wait Alphaͨ��ֵΪ0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_011)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 1.0f;		// Wait Alphaͨ��ֵΪ1.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_012)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 1.0f;		// Wait Alphaͨ��ֵΪ1.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_013)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 1.0f;		// Wait Alphaͨ��ֵΪ1.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Wait Alphaͨ��ֵΪ0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Wait Alphaͨ��ֵΪ0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Wait Alphaͨ��ֵΪ0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Wait Alphaͨ��ֵΪ0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Wait Alphaͨ��ֵΪ0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_LOGIN_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Login Alphaͨ��ֵΪ0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_ACCOUNT_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;	// Account Alphaͨ��ֵΪ0.0f

		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateZ() = -160.0f;	// Logo Z������Ϊ-120
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_01)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateZ() = -160.0f;	// Logo2 Z������Ϊ-120
	}
	else if (fTimeSum < 1.5f)	// ��ʼʱ��0.5s~1.5sʱ��������,Alphaͨ��ֵ����
	{
		CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetDialogGraphics()->CCerasusUnitGetAlpha(), 1.0f, 0.02f);		// ����Alphaͨ��ֵ��0.0f������1.0f,�����ٶ�0.02f,����50֡
	}
	else if (fTimeSum < 2.5f)	// ��ʼʱ��1.5s~2.5sʱ��������,logo������Զ����,��Ȩ��Ϣ����
	{
		CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateZ(), -160.0f, 0.0f, -0.8f);
		CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 1.0f, 0.05f);
		CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_02)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 1.0f, 0.02f);

		if (fTimeSum >= 2.0f)
		{
			CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_01)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateZ(), -160.0f, 0.0f, -0.8f);
			CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_01)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 1.0f, 0.05f);
		}

	}
	else if (fTimeSum < 3.0f)	// ��ʼʱ��2.5s~3.0sʱ�������Ժ�����
	{
		CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_010)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 1.0f, 0.05f);
	}
	else if(fTimeSum < 12.0f)	// ��ʼʱ��3.0s~8.0sʱ�ȴ�������Դ
	{
		// ���Ժ�...�ȴ������л�
		static int nCount = 0;
		static float fTimeSwitch = 0.0f;

		fTimeSwitch += fDeltaTime;
		if (fTimeSwitch >= 0.5f)
		{
			fTimeSwitch = 0.0f;
			nCount++;
			if (nCount > 3)
			{
				nCount = 0;
			}
		}

		switch (nCount)
		{
			case 0:
			{
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_010)->SetVisible(true);
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_011)->SetVisible(false);
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_012)->SetVisible(false);
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_013)->SetVisible(false);
				break;
			}
			case 1:
			{
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_010)->SetVisible(false);
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_011)->SetVisible(true);
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_012)->SetVisible(false);
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_013)->SetVisible(false);
				break;
			}
			case 2:
			{
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_010)->SetVisible(false);
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_011)->SetVisible(false);
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_012)->SetVisible(true);
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_013)->SetVisible(false);
				break;
			}
			case 3:
			{
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_010)->SetVisible(false);
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_011)->SetVisible(false);
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_012)->SetVisible(false);
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_013)->SetVisible(true);
				break;
			}
			default:
				break;
		}

		// ����ǡ�ȴ�����
		static bool bStarFinish = false;		// bStarFinish=true, ����Ƕ����Ѿ����; bStarFinish=false, ����Ƕ�����δ���
		static bool bStarOrder = true;			// bStarOrder=true, ����Ǵ������ȼ����˶�; bStarOrder=false, ����Ǵ��е��ұ��ȼ����˶�
		static int nStarCount = 0;				// nStarCount �����м����������
		static float fTimeInterval = 0.0f;		// fTimeInterval ������˶�ʱ����

		fTimeInterval += fDeltaTime;
		if (fTimeInterval >= 0.1f)
		{
			fTimeInterval = 0.0f;

			if (bStarOrder)
			{
				nStarCount++;
				if (nStarCount >= 5)
				{
					nStarCount = 5;
					if (bStarFinish == true)
					{
						bStarFinish = false;
						bStarOrder = false;
					}
				}
			}
			else
			{
				nStarCount--;
				if (nStarCount <= 1)
				{
					nStarCount = 1;
					if (bStarFinish == true)
					{
						nStarCount = 0;
						bStarFinish = false;
						bStarOrder = true;
					}
				}

			}
			
		}

		if (bStarOrder)
		{
			if (nStarCount >= 1)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX(), 0.0f, 179.0f, -0.4f);
				CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 1.0f, 0.2f);
			}

			if (nStarCount >= 2)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX(), 0.0f, 166.0f, -0.4f);
				CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 1.0f, 0.2f);
			}

			if (nStarCount >= 3)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX(), 0.0f, 153.0f, -0.4f);
				CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 1.0f, 0.2f);
			}

			if (nStarCount >= 4)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX(), 0.0f, 139.0f, -0.4f);
				CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 1.0f, 0.2f);
			}

			if (nStarCount >= 5)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX(), 0.0f, 126.0f, -0.4f);
				CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 1.0f, 0.2f);
			}

			// �ж�����Ƕ����Ƿ����
			if(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX() >= 126.0f)
			{
				bStarFinish = true;
			}
		}
		else
		{
			if (nStarCount <= 5)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX(), 179.0f, 320.0f, -0.4f);
				CCerasusAlgorithm::Linear_Decrease(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 0.0f, 0.05f);
			}

			if (nStarCount <= 4)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX(), 166.0f, 320.0f, -0.4f);
				CCerasusAlgorithm::Linear_Decrease(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 0.0f, 0.05f);
			}

			if (nStarCount <= 3)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX(), 153.0f, 320.0f, -0.4f);
				CCerasusAlgorithm::Linear_Decrease(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 0.0f, 0.05f);
			}

			if (nStarCount <= 2)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX(), 139.0f, 320.0f, -0.4f);
				CCerasusAlgorithm::Linear_Decrease(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 0.0f, 0.05f);
			}

			if (nStarCount <= 1)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX(), 126.0f, 320.0f, -0.4f);
				CCerasusAlgorithm::Linear_Decrease(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 0.0f, 0.05f);
			}

			// �ж�����Ƕ����Ƿ����
			if (m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX() >= 320.0f)
			{
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateX() = 0.0f;

				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;

				bStarFinish = true;
			}

		}

	}
	else if(fTimeSum < 15.0f)
	{
		// ������ȴ��������ɼ�
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_010)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_011)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_012)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_013)->SetVisible(false);

		// ��������Ƕ������ɼ�
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->SetVisible(false);

		CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_ACCOUNT_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 1.0f, 0.02f);

		if (fTimeSum >= 13.0f)
		{
			CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_LOGIN_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha(), 0.6f, 0.02f);
		}

		if (m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_LOGIN_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() >= 0.6f)
		{
			m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_LOGIN_00)->SetVisible(false);
			m_pSakuraDialog->GetButton(SID_SAKURABUTTON_LOGIN_00)->SetVisible(true);
		}

	}
	else
	{
		// ��Ⱦ���ӿ�ʼ
		m_bSpriteRender = true;

		// ˢ����Ⱦ����
		CLiveInUpdateSprite();
	}

}

//----------------------------------------------
// @Function:	CLiveInReadConfigFile()
// @Purpose: CLiveIn��ȡ�����ļ���Ϣ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
BOOL CLiveIn::CLiveInReadConfigFile()
{
	char chFile[MAX_PATH] = { 0 };

	strcpy_s(chFile, "config\\LiveIn.lua");

	CConvallariaLua* lua = new CConvallariaLua(chFile);		// lua script ʵ����
	BOOL bRet = FALSE;

	bRet = lua->ConvallariaLua_Init();	// lua script ��ʼ��
	if (!bRet)
	{
		SAFE_DELETE(lua);
		return FALSE;
	}

	lua->ConvallariaLua_GetGlobal_Int("LiveIn_Use_Log", m_nIsUseLog);					// ��ȡ�Ƿ���־��¼
	lua->ConvallariaLua_GetGlobal_Int("LiveIn_Show_Adapter", m_nIsShowAdapter);			// ��ȡ�Ƿ���ʾ�Կ�
	lua->ConvallariaLua_GetGlobal_Int("LiveIn_Show_Fps", m_nIsShowFps);					// ��ȡ�Ƿ���ʾfps
	lua->ConvallariaLua_GetGlobal_Int("LiveIn_Sprite_Num", m_nSpriteNum);				// ��ȡ����ϵͳ����

	SAFE_DELETE(lua);
	return TRUE;
}

//----------------------------------------------
// @Function:	CLiveInLoadPacketFile()
// @Purpose: CLiveIn���ط���ļ�����
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
BOOL CLiveIn::CLiveInLoadPacketFile()
{
	char chPacket[MAX_PATH] = { 0 };

	CPlumPath::PlumPathGetLocalPathA(chPacket, sizeof(chPacket));
	strcat_s(chPacket, "\\pak\\LiveIn.pak");

	CPlumPack packet;

	// ������Դ(bk_00.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "bk_00.png", m_chPacketRes_bk_00, sizeof(m_chPacketRes_bk_00));

	// ������Դ(title_00.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "title_00.png", m_chPacketRes_title_00, sizeof(m_chPacketRes_title_00));

	// ������Դ(title_01.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "title_01.png", m_chPacketRes_title_01, sizeof(m_chPacketRes_title_01));

	// ������Դ(title_02.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "title_02.png", m_chPacketRes_title_02, sizeof(m_chPacketRes_title_02));

	// ������Դ(wait_00.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "wait_00.png", m_chPacketRes_wait_00, sizeof(m_chPacketRes_wait_00));

	// ������Դ(wait_01.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "wait_01.png", m_chPacketRes_wait_01, sizeof(m_chPacketRes_wait_01));

	// ������Դ(login_00.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "login_00.png", m_chPacketRes_login_00, sizeof(m_chPacketRes_login_00));

	// ������Դ(account_00.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "avatar_00.png", m_chPacketRes_account_00, sizeof(m_chPacketRes_account_00));
	
	// ������Դ(sprite_00.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "sprite_00.png", m_chPacketRes_sprite_00, sizeof(m_chPacketRes_sprite_00));

	return TRUE;
}

//----------------------------------------------
// @Function:	CLiveInSetSpriteArea()
// @Purpose: CLiveIn�������ӳ�������
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInSetSpriteArea(int nX, int nY, int nWidth, int nHeight)
{
	m_nStarPosX = nX;
	m_nStarPosY = nY;
	m_nStarWidth = nWidth;
	m_nStarHeight = nHeight;
}

//----------------------------------------------
// @Function:	CLiveInInitSprite()
// @Purpose: CLiveIn��ʼ������ϵͳ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInInitSprite()
{
	// ��ʼ�����������
	srand(GetTickCount());

	// ��ʼ������ϵͳ--����״̬
	for (int i = 0; i < m_nSpriteNum; ++i)
	{
		TLIVEINSTAR tStar = { 0 };

		tStar.fAlpha = (float)(0.5f + ((rand() % 101) * 1.0f / 200.0f));																		// ����Alpha: (0.5f~1.0f)
		tStar.fFallSpeed = (float)(m_nStarHeight * 1.0f / 5.0f + ((rand() % 100) * 1.0f / 200.0f) * m_nStarHeight);								// ���������ٶ�
		tStar.fMoveSpeed = (float)(((rand() % 100) * 1.0f / 500.0f) * m_nStarWidth);															// �����ƶ��ٶ�
		tStar.fRotateSpeed = (float)(D3DX_PI * 1.0f / 5.0f + ((rand() % 100) * 1.0f / 200.0f) * D3DX_PI);										// ������ת�ٶ�
		tStar.nMoveDirect = rand() % 2;																											// �����ƶ�����: (0~�� 1~��)
		tStar.nRotateDirect = rand() % 2;																										// ������ת����: (0~�� 1~��)
		tStar.sTransformPara.sTranslatePara.fTranslateX = (float)(m_nStarPosX + m_nStarWidth * 0.1f + (rand() % m_nStarWidth) * 0.9f);			// ����X����: (x~x+width)
		tStar.sTransformPara.sTranslatePara.fTranslateY = (float)(m_nStarPosY + rand() % m_nStarHeight - m_nStarHeight);						// ����Y���: (y~y+height)
		tStar.sTransformPara.sScalePara.fScaleX = (float)(0.2f + ((rand() % 80) * 1.0f / 100.0f));												// ��������任ϵ��: (0.2f~1.0f)
		tStar.sTransformPara.sScalePara.fScaleY = tStar.sTransformPara.sScalePara.fScaleX;														// ��������任ϵ��: (0.2f~1.0f)
		tStar.sTransformPara.sRotatePara.fRotateZ = (float)(((rand() % 100) * 1.0f / 600.0f) * D3DX_PI);										// ������ת�任ϵ��: (Arc:0~Pi/6)

		m_vecStarArray.push_back(tStar);
	}

}

//----------------------------------------------
// @Function:	CLiveInUpdateSprite()
// @Purpose: CLiveInˢ������
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInUpdateSprite()
{
	for (auto iter = m_vecStarArray.begin(); iter != m_vecStarArray.end(); ++iter)
	{
		iter->sTransformPara.sTranslatePara.fTranslateY += iter->fFallSpeed * 0.0167f;

		if (iter->sTransformPara.sTranslatePara.fTranslateY > m_nStarHeight * 1.0f
			|| iter->sTransformPara.sTranslatePara.fTranslateX < m_nStarWidth * 0.0f
			|| iter->sTransformPara.sTranslatePara.fTranslateX > m_nStarWidth * 1.0f)
		{
			iter->fAlpha = (float)(0.5f + ((rand() % 101) * 1.0f / 200.0f));																		// ����Alpha: (0.5f~1.0f)
			iter->fFallSpeed = (float)(m_nStarHeight * 1.0f / 5.0f + ((rand() % 100) * 1.0f / 200.0f) * m_nStarHeight);								// ���������ٶ�
			iter->fMoveSpeed = (float)(((rand() % 100) * 1.0f / 500.0f) * m_nStarWidth);															// �����ƶ��ٶ�
			iter->fRotateSpeed = (float)(D3DX_PI * 1.0f / 5.0f + ((rand() % 100) * 1.0f / 200.0f) * D3DX_PI);										// ������ת�ٶ�
			iter->nMoveDirect = rand() % 2;																											// �����ƶ�����: (0~�� 1~��)
			iter->nRotateDirect = rand() % 2;																										// ������ת����: (0~�� 1~��)
			iter->sTransformPara.sTranslatePara.fTranslateX = (float)(m_nStarPosX + m_nStarWidth * 0.1f + (rand() % m_nStarWidth) * 0.9f);			// ����X����: (x~x+width)
			iter->sTransformPara.sTranslatePara.fTranslateY = (float)(m_nStarPosY + rand() % m_nStarHeight - m_nStarHeight);						// ����Y���: (y~y+height)
			iter->sTransformPara.sScalePara.fScaleX = (float)(0.2f + ((rand() % 80) * 1.0f / 100.0f));												// ��������任ϵ��: (0.2f~1.0f)
			iter->sTransformPara.sScalePara.fScaleY = iter->sTransformPara.sScalePara.fScaleX;														// ��������任ϵ��: (0.2f~1.0f)
			iter->sTransformPara.sRotatePara.fRotateZ = (float)(((rand() % 100) * 1.0f / 600.0f) * D3DX_PI);										// ������ת�任ϵ��: (Arc:0~Pi/6)
		}

		if (iter->sTransformPara.sTranslatePara.fTranslateY > m_nStarHeight * 0.8f)
		{
			iter->fAlpha -= 0.05f;
			if (iter->fAlpha <= 0.5f)
			{
				iter->fAlpha = 0.5f;
			}
		}

		if (iter->nMoveDirect == 0)
		{
			iter->sTransformPara.sTranslatePara.fTranslateX += iter->fMoveSpeed * 0.0167f;
		}
		else
		{
			iter->sTransformPara.sTranslatePara.fTranslateX -= iter->fMoveSpeed * 0.0167f;
		}

		if (iter->nRotateDirect == 0)
		{
			iter->sTransformPara.sRotatePara.fRotateZ += iter->fRotateSpeed * 0.0167f;
		}
		else
		{
			iter->sTransformPara.sRotatePara.fRotateZ -= iter->fRotateSpeed * 0.0167f;
		}

	}

}

//----------------------------------------------
// @Function:	CLiveInUpdateSprite()
// @Purpose: CLiveIn��Ⱦ����
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInRenderSprite()
{
	m_pDirectSprite->DirectSpriteBegin();

	for(auto iter = m_vecStarArray.begin(); iter != m_vecStarArray.end(); ++iter)
	{
		DirectSpriteDrawPara sDrawPara = { 0 };
		SetRect(&sDrawPara.SpriteRect, 0, 0, 21, 20);
		sDrawPara.SpriteCenter = D3DXVECTOR3(10.0f, 11.0f, 0.0f);
		sDrawPara.SpritePosition = D3DXVECTOR3(iter->sTransformPara.sTranslatePara.fTranslateX, iter->sTransformPara.sTranslatePara.fTranslateY, 0.0f);
		sDrawPara.SpriteColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, iter->fAlpha);
		m_pDirectSprite->DirectSpriteDrawTransform(&sDrawPara, iter->sTransformPara, iter->sTransformPara.sTranslatePara.fTranslateY, m_nStarPosY);
	}

	m_pDirectSprite->DirectSpriteEnd();
}

//----------------------------------------------
// @Function:	CLiveDrawAdapter()
// @Purpose: CLiveIn�����Կ���Ϣ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveDrawAdapter()
{
	RECT Rect;

	GetClientRect(g_hWnd, &Rect);

	// Direct3D �����Կ���Ϣ
	Rect.top += 0;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextAdapterType(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));

	// Direct3D ������Ļ�ֱ���
	Rect.top += 20;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextScreen(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

	// Direct3D ���ƻ���ģ��
	Rect.top += 20;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextFormat(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));
}

//----------------------------------------------
// @Function:	CLiveDrawfps()
// @Purpose: CLiveIn����fps
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveDrawfps()
{
	m_pCerasusfpsMain->CCerasusfpsGetfps();				// Direct3D ���ƾ�̬��Ϣ
	m_pCerasusfpsMain->CCerasusfpsDrawfps(g_hWnd, DIRECTFONT_FORMAT_BOTTOMRIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		// Direct3D ����fps
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResBK00()
// @Purpose: CLiveIn���ر���bk_00��Դ�ṹ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResBK00(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 512;
	sUnitEx.nTextureHeight = 512;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_bk_00;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_bk_00);
	sUnitEx.rcUnit.left = 0;
	sUnitEx.rcUnit.right = USER_WINDOWWIDTH;
	sUnitEx.rcUnit.top = 0;
	sUnitEx.rcUnit.bottom = USER_WINDOWHEIGHT;
	sUnitEx.rcUnitTex.left = 0;
	sUnitEx.rcUnitTex.right = 320;
	sUnitEx.rcUnitTex.top = 0;
	sUnitEx.rcUnitTex.bottom = 480;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResTITLE00()
// @Purpose: CLiveIn���ر���title_00��Դ�ṹ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResTITLE00(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 256;
	sUnitEx.nTextureHeight = 64;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_title_00;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_title_00);
	sUnitEx.rcUnit.left = 32;
	sUnitEx.rcUnit.right = 288;
	sUnitEx.rcUnit.top = 64;
	sUnitEx.rcUnit.bottom = 128;
	sUnitEx.rcUnitTex.left = 0;
	sUnitEx.rcUnitTex.right = 256;
	sUnitEx.rcUnitTex.top = 0;
	sUnitEx.rcUnitTex.bottom = 64;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResTITLE01()
// @Purpose: CLiveIn���ر���title_01��Դ�ṹ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResTITLE01(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 256;
	sUnitEx.nTextureHeight = 32;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_title_01;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_title_01);
	sUnitEx.rcUnit.left = 32;
	sUnitEx.rcUnit.right = 288;
	sUnitEx.rcUnit.top = 128;
	sUnitEx.rcUnit.bottom = 160;
	sUnitEx.rcUnitTex.left = 0;
	sUnitEx.rcUnitTex.right = 256;
	sUnitEx.rcUnitTex.top = 0;
	sUnitEx.rcUnitTex.bottom = 32;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResTITLE02()
// @Purpose: CLiveIn���ر���title_02��Դ�ṹ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResTITLE02(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 256;
	sUnitEx.nTextureHeight = 32;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_title_02;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_title_02);
	sUnitEx.rcUnit.left = 32;
	sUnitEx.rcUnit.right = 288;
	sUnitEx.rcUnit.top = 432;
	sUnitEx.rcUnit.bottom = 464;
	sUnitEx.rcUnitTex.left = 0;
	sUnitEx.rcUnitTex.right = 256;
	sUnitEx.rcUnitTex.top = 0;
	sUnitEx.rcUnitTex.bottom = 32;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT01_0()
// @Purpose: CLiveIn���ر���wait_01��Դ�ṹ(���Ժ�)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT01_0(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 128;
	sUnitEx.nTextureHeight = 128;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_wait_01;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_wait_01);
	sUnitEx.rcUnit.left = 134;
	sUnitEx.rcUnit.right = 186;
	sUnitEx.rcUnit.top = 233;
	sUnitEx.rcUnit.bottom = 247;
	sUnitEx.rcUnitTex.left = 0;
	sUnitEx.rcUnitTex.right = 52;
	sUnitEx.rcUnitTex.top = 1;
	sUnitEx.rcUnitTex.bottom = 15;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT01_1()
// @Purpose: CLiveIn���ر���wait_01��Դ�ṹ(���Ժ�.)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT01_1(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 128;
	sUnitEx.nTextureHeight = 128;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_wait_01;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_wait_01);
	sUnitEx.rcUnit.left = 134;
	sUnitEx.rcUnit.right = 186;
	sUnitEx.rcUnit.top = 233;
	sUnitEx.rcUnit.bottom = 247;
	sUnitEx.rcUnitTex.left = 0;
	sUnitEx.rcUnitTex.right = 52;
	sUnitEx.rcUnitTex.top = 16;
	sUnitEx.rcUnitTex.bottom = 30;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT01_2()
// @Purpose: CLiveIn���ر���wait_01��Դ�ṹ(���Ժ�..)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT01_2(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 128;
	sUnitEx.nTextureHeight = 128;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_wait_01;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_wait_01);
	sUnitEx.rcUnit.left = 134;
	sUnitEx.rcUnit.right = 186;
	sUnitEx.rcUnit.top = 233;
	sUnitEx.rcUnit.bottom = 247;
	sUnitEx.rcUnitTex.left = 0;
	sUnitEx.rcUnitTex.right = 52;
	sUnitEx.rcUnitTex.top = 31;
	sUnitEx.rcUnitTex.bottom = 45;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT01_3()
// @Purpose: CLiveIn���ر���wait_01��Դ�ṹ(���Ժ�...)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT01_3(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 128;
	sUnitEx.nTextureHeight = 128;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_wait_01;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_wait_01);
	sUnitEx.rcUnit.left = 134;
	sUnitEx.rcUnit.right = 186;
	sUnitEx.rcUnit.top = 233;
	sUnitEx.rcUnit.bottom = 247;
	sUnitEx.rcUnitTex.left = 0;
	sUnitEx.rcUnitTex.right = 52;
	sUnitEx.rcUnitTex.top = 46;
	sUnitEx.rcUnitTex.bottom = 60;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT00_0()
// @Purpose: CLiveIn���ر���wait_00��Դ�ṹ(�����)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT00_0(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 128;
	sUnitEx.nTextureHeight = 32;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_wait_00;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_wait_00);
	sUnitEx.rcUnit.left = 0;
	sUnitEx.rcUnit.right = 11;
	sUnitEx.rcUnit.top = 250;
	sUnitEx.rcUnit.bottom = 261;
	sUnitEx.rcUnitTex.left = 1;
	sUnitEx.rcUnitTex.right = 12;
	sUnitEx.rcUnitTex.top = 0;
	sUnitEx.rcUnitTex.bottom = 11;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT00_1()
// @Purpose: CLiveIn���ر���wait_00��Դ�ṹ(�����)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT00_1(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 128;
	sUnitEx.nTextureHeight = 32;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_wait_00;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_wait_00);
	sUnitEx.rcUnit.left = 0;
	sUnitEx.rcUnit.right = 11;
	sUnitEx.rcUnit.top = 250;
	sUnitEx.rcUnit.bottom = 261;
	sUnitEx.rcUnitTex.left = 13;
	sUnitEx.rcUnitTex.right = 24;
	sUnitEx.rcUnitTex.top = 0;
	sUnitEx.rcUnitTex.bottom = 11;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT00_2()
// @Purpose: CLiveIn���ر���wait_00��Դ�ṹ(�����)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT00_2(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 128;
	sUnitEx.nTextureHeight = 32;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_wait_00;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_wait_00);
	sUnitEx.rcUnit.left = 0;
	sUnitEx.rcUnit.right = 11;
	sUnitEx.rcUnit.top = 250;
	sUnitEx.rcUnit.bottom = 261;
	sUnitEx.rcUnitTex.left = 25;
	sUnitEx.rcUnitTex.right = 36;
	sUnitEx.rcUnitTex.top = 0;
	sUnitEx.rcUnitTex.bottom = 11;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT00_3()
// @Purpose: CLiveIn���ر���wait_00��Դ�ṹ(�����)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT00_3(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 128;
	sUnitEx.nTextureHeight = 32;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_wait_00;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_wait_00);
	sUnitEx.rcUnit.left = 0;
	sUnitEx.rcUnit.right = 11;
	sUnitEx.rcUnit.top = 250;
	sUnitEx.rcUnit.bottom = 261;
	sUnitEx.rcUnitTex.left = 37;
	sUnitEx.rcUnitTex.right = 48;
	sUnitEx.rcUnitTex.top = 0;
	sUnitEx.rcUnitTex.bottom = 11;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT00_4()
// @Purpose: CLiveIn���ر���wait_00��Դ�ṹ(�����)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT00_4(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 128;
	sUnitEx.nTextureHeight = 32;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_wait_00;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_wait_00);
	sUnitEx.rcUnit.left = 0;
	sUnitEx.rcUnit.right = 11;
	sUnitEx.rcUnit.top = 250;
	sUnitEx.rcUnit.bottom = 261;
	sUnitEx.rcUnitTex.left = 50;
	sUnitEx.rcUnitTex.right = 61;
	sUnitEx.rcUnitTex.top = 0;
	sUnitEx.rcUnitTex.bottom = 11;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResLOGIN00()
// @Purpose: CLiveIn���ذ�ťlogin_00��Դ(��¼)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResLOGIN00(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 512;
	sUnitEx.nTextureHeight = 512;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_login_00;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_login_00);
	sUnitEx.rcUnit.left = 70;
	sUnitEx.rcUnit.right = 250;
	sUnitEx.rcUnit.top = 360;
	sUnitEx.rcUnit.bottom = 400;
	sUnitEx.rcUnitTex.left = 0;
	sUnitEx.rcUnitTex.right = 180;
	sUnitEx.rcUnitTex.top = 0;
	sUnitEx.rcUnitTex.bottom = 40;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResACCOUNT00()
// @Purpose: CLiveIn���ر���account_00��Դ(�˻�)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResACCOUNT00(CUUintEx & sUnitEx)
{
	sUnitEx.nTextureWidth = 512;
	sUnitEx.nTextureHeight = 512;
	sUnitEx.nScreenWidth = USER_WINDOWWIDTH;
	sUnitEx.nScreenHeight = USER_WINDOWHEIGHT;
	sUnitEx.fUnitAlpha = 1.0f;
	sUnitEx.pTextureArr = m_chPacketRes_account_00;
	sUnitEx.nTextureArrSize = sizeof(m_chPacketRes_account_00);
	sUnitEx.rcUnit.left = 120;
	sUnitEx.rcUnit.right = 200;
	sUnitEx.rcUnit.top = 200;
	sUnitEx.rcUnit.bottom = 310;
	sUnitEx.rcUnitTex.left = 0;
	sUnitEx.rcUnitTex.right = 80;
	sUnitEx.rcUnitTex.top = 0;
	sUnitEx.rcUnitTex.bottom = 110;

	//����任
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//ȡ���任
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//ͶӰ�任
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//�ӿڱ任
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//CDXSampleCore �ؼ��¼��ص����� 
void __stdcall CLiveInSakuraGUIEvent(UINT nEvent, int nControlID, CSakuraControl * pControl, void * pUserContext)
{
	switch (nEvent)
	{
	case EVENT_BUTTON_CLICKED:
		{
			if (nControlID == SID_SAKURABUTTON_LOGIN_00)
			{
				::PostMessageA(g_hWnd, WM_CLOSE, (WPARAM)0, (LPARAM)0);
			}

		}
		break;
	case EVENT_COMBOBOX_SELECTION_CHANGED:
		break;
	case EVENT_RADIOBUTTON_CHANGED:
		break;
	case EVENT_CHECKBOX_CHANGED:
		break;
	case EVENT_SLIDER_VALUE_CHANGED:
		break;
	case EVENT_EDITBOX_STRING:
		break;
	case EVENT_EDITBOX_CHANGE:
		break;
	case EVENT_LISTBOX_ITEM_DBLCLK:
		break;
	case EVENT_LISTBOX_SELECTION:
		break;
	case EVENT_LISTBOX_SELECTION_END:
		break;
	default:
		break;
	}

}
