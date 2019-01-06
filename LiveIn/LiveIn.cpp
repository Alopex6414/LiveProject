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
CLiveIn::CLiveIn() :m_nIsUseLog(0), m_nIsShowAdapter(0), m_nIsShowFps(0)
{
	m_pDirectGraphicsMain = NULL;
	m_pDirectGraphics3DMain = NULL;
	m_pCerasusfpsMain = NULL;
	m_pResourceManager = NULL;
	m_pSakuraDialog = NULL;

	memset(m_chPacketRes_bk_00, 0, sizeof(m_chPacketRes_bk_00));
	memset(m_chPacketRes_title_00, 0, sizeof(m_chPacketRes_title_00));
	memset(m_chPacketRes_title_01, 0, sizeof(m_chPacketRes_title_01));
	memset(m_chPacketRes_title_02, 0, sizeof(m_chPacketRes_title_02));
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

	// SakuraControl ��ʼ��
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_TITLE_00, 32, 32, 256, 64);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_TITLE_01, 32, 96, 256, 32);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_TITLE_02, 32, 448, 256, 32);

	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_TITLE_00, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 0);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_TITLE_01, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 1);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_TITLE_02, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 2);

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
			hr2 = m_pDirectGraphicsMain->DirectGraphicsReset();

			// �����豸
			m_pSakuraDialog->OnReset();
			hr2 = m_pDirectGraphics3DMain->DirectGraphics3DInitVertex3DBase(6);
		}

	}
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

	return TRUE;
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
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextFormat(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f));
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
	m_pCerasusfpsMain->CCerasusfpsDrawfps(g_hWnd, DIRECTFONT_FORMAT_BOTTOMRIGHT, D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f));		// Direct3D ����fps
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
	sUnitEx.rcUnit.top = 32;
	sUnitEx.rcUnit.bottom = 96;
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
	sUnitEx.rcUnit.top = 96;
	sUnitEx.rcUnit.bottom = 128;
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
	sUnitEx.rcUnit.top = 448;
	sUnitEx.rcUnit.bottom = 480;
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

//CDXSampleCore �ؼ��¼��ص����� 
void __stdcall CLiveInSakuraGUIEvent(UINT nEvent, int nControlID, CSakuraControl * pControl, void * pUserContext)
{

}
