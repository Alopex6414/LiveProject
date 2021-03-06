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

// CLiveIn类

//----------------------------------------------
// @Function:	CLiveIn()
// @Purpose: CLiveIn构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
CLiveIn::CLiveIn() :m_nIsUseLog(0), m_nIsShowAdapter(0), m_nIsShowFps(0), m_nSpriteNum(0), m_fTimeSum(0.0f), m_bSpriteRender(false)
{
	m_pDirectGraphicsMain = NULL;
	m_pDirectGraphics3DMain = NULL;
	m_pDirectSprite = NULL;
	m_pDirectInput = NULL;
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
// @Purpose: CLiveIn析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
CLiveIn::~CLiveIn()
{
	SAFE_DELETE(m_pSakuraDialog);
	SAFE_DELETE(m_pResourceManager);
	SAFE_DELETE(m_pCerasusfpsMain);
	SAFE_DELETE(m_pDirectInput);
	SAFE_DELETE(m_pDirectSprite);
	SAFE_DELETE(m_pDirectGraphics3DMain);
	SAFE_DELETE(m_pDirectGraphicsMain);
}

//----------------------------------------------
// @Function:	CLiveInInit()
// @Purpose: CLiveIn初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
BOOL CLiveIn::CLiveInInit()
{
	HRESULT hr;
	IDirect3DDevice9* pD3D9Device = NULL;

	// CLiveIn 读取配置文件信息
	BOOL bRet = FALSE;
	bRet = CLiveInReadConfigFile();
	if (!bRet)
	{
		MessageBox(g_hWnd, _T("LiveIn读取配置文件失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "LiveIn应用程序开启.");
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "LiveIn读取lua文件成功.m_nIsUseLog=%d,m_nIsShowAdapter=%d,m_nIsShowFps=%d.", m_nIsUseLog, m_nIsShowAdapter, m_nIsShowFps);

	// DirectGraphics 初始化
	m_pDirectGraphicsMain = new DirectGraphics();
	hr = m_pDirectGraphicsMain->Create(g_hWnd, true, USER_WINDOWWIDTH, USER_WINDOWHEIGHT);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "Direct3D初始化失败!返回值hr=%l.", hr);
		MessageBox(g_hWnd, _T("Direct3D初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "Direct3D初始化成功!");

	hr = m_pDirectGraphicsMain->Create2(20);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectFont初始化失败!返回值hr=%l.", hr);
		MessageBox(g_hWnd, _T("DirectFont初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectFont初始化成功!");

	pD3D9Device = m_pDirectGraphicsMain->GetDevice();		// DirectX设备指针

	// DirectGraphics3D 初始化
	m_pDirectGraphics3DMain = new DirectGraphics3D(pD3D9Device);
	hr = m_pDirectGraphics3DMain->CreateBase(6);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectGraphics3D初始化失败!返回值hr=%l.", hr);
		MessageBox(g_hWnd, _T("DirectGraphics3D初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectGraphics3D初始化成功!");

	// DirectInput 初始化
	m_pDirectInput = new DirectInput();
	hr = m_pDirectInput->Create(g_hWnd, g_hInstance, InputDevice_KeyBoard, InputCoopFlags_ForeGround_Exclusive);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectInput初始化失败!返回值hr=%l.", hr);
		MessageBox(g_hWnd, _T("DirectInput初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectInput初始化成功!");

	// Cerasusfps 初始化
	m_pCerasusfpsMain = new CCerasusfps(pD3D9Device);
	hr = m_pCerasusfpsMain->Create(20);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "Cerasusfps初始化失败!返回值hr=%l.", hr);
		MessageBox(g_hWnd, _T("Cerasusfps初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "Cerasusfps初始化成功!");

	// CLiveIn 加载资源文件
	CLiveInLoadPacketFile();

	// DirectSprite 初始化
	m_pDirectSprite = new DirectSprite(pD3D9Device);
	hr = m_pDirectSprite->Create(m_chPacketRes_sprite_00, sizeof(m_chPacketRes_sprite_00), 32, 32);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectSprite初始化失败!返回值hr=%l.", hr);
		MessageBox(g_hWnd, _T("DirectSprite初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectSprite初始化成功!");

	CLiveInSetSpriteArea(0, 0, 320, 480);
	CLiveInInitSprite();

	// SakuraResourceManager 初始化
	m_pResourceManager = new CSakuraResourceManager();
	m_pResourceManager->OnCreate(pD3D9Device);

	S_CS_UNIT_EX_PARA sUnitEx_bk_00 = { 0 };
	CLiveInAddPacketResBK00(sUnitEx_bk_00);

	// SakuraDialog 初始化
	m_pSakuraDialog = new CSakuraDialog();
	m_pSakuraDialog->OnCreate(m_pResourceManager, sUnitEx_bk_00);
	m_pSakuraDialog->SetLocation(0, 0);
	m_pSakuraDialog->SetSize(USER_WINDOWWIDTH, USER_WINDOWHEIGHT);
	m_pSakuraDialog->SetCallback(CLiveInSakuraGUIEvent, this);

	// SakuraResourceManager 资源载入
	S_CS_UNIT_EX_PARA sUnitEx_title_00 = { 0 };
	CLiveInAddPacketResTITLE00(sUnitEx_title_00);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_title_00);

	S_CS_UNIT_EX_PARA sUnitEx_title_01 = { 0 };
	CLiveInAddPacketResTITLE01(sUnitEx_title_01);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_title_01);

	S_CS_UNIT_EX_PARA sUnitEx_title_02 = { 0 };
	CLiveInAddPacketResTITLE02(sUnitEx_title_02);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_title_02);

	S_CS_UNIT_EX_PARA sUnitEx_wait_010 = { 0 };
	CLiveInAddPacketResWAIT01_0(sUnitEx_wait_010);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_010);

	S_CS_UNIT_EX_PARA sUnitEx_wait_011 = { 0 };
	CLiveInAddPacketResWAIT01_1(sUnitEx_wait_011);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_011);

	S_CS_UNIT_EX_PARA sUnitEx_wait_012 = { 0 };
	CLiveInAddPacketResWAIT01_2(sUnitEx_wait_012);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_012);

	S_CS_UNIT_EX_PARA sUnitEx_wait_013 = { 0 };
	CLiveInAddPacketResWAIT01_3(sUnitEx_wait_013);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_013);

	S_CS_UNIT_EX_PARA sUnitEx_wait_000 = { 0 };
	CLiveInAddPacketResWAIT00_0(sUnitEx_wait_000);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_000);

	S_CS_UNIT_EX_PARA sUnitEx_wait_001 = { 0 };
	CLiveInAddPacketResWAIT00_1(sUnitEx_wait_001);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_001);

	S_CS_UNIT_EX_PARA sUnitEx_wait_002 = { 0 };
	CLiveInAddPacketResWAIT00_2(sUnitEx_wait_002);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_002);

	S_CS_UNIT_EX_PARA sUnitEx_wait_003 = { 0 };
	CLiveInAddPacketResWAIT00_3(sUnitEx_wait_003);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_003);

	S_CS_UNIT_EX_PARA sUnitEx_wait_004 = { 0 };
	CLiveInAddPacketResWAIT00_4(sUnitEx_wait_004);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_wait_004);

	// 登陆按钮资源
	S_CS_UNIT_EX_PARA sUnitEx_login_00 = { 0 };
	CLiveInAddPacketResLOGIN00(sUnitEx_login_00);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_login_00);

	// 账户背景资源
	S_CS_UNIT_EX_PARA sUnitEx_account_00 = { 0 };
	CLiveInAddPacketResACCOUNT00(sUnitEx_account_00);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_account_00);

	// SakuraControl 初始化
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
// @Purpose: CLiveIn释放
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInRelease()
{
	SAFE_DELETE(m_pSakuraDialog);
	SAFE_DELETE(m_pResourceManager);
	SAFE_DELETE(m_pCerasusfpsMain);
	SAFE_DELETE(m_pDirectInput);
	SAFE_DELETE(m_pDirectSprite);
	SAFE_DELETE(m_pDirectGraphics3DMain);
	SAFE_DELETE(m_pDirectGraphicsMain);

	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "LiveIn应用程序结束.");
}

//----------------------------------------------
// @Function:	CLiveInUpdate()
// @Purpose: CLiveIn刷新
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInUpdate()
{
	HRESULT hr;
	IDirect3DSurface9* pD3D9Surface = NULL;

	// DirectGraphics 测试设备协作级别
	hr = m_pDirectGraphicsMain->TestCooperativeLevel();
	if (hr != S_OK)
	{
		if (hr == D3DERR_DEVICELOST)	// DirectX 设备丢失
		{
			return;
		}

		if (hr == D3DERR_DEVICENOTRESET)	// DirectX 设备重置
		{
			HRESULT hr2;

			// 丢失设备
			hr2 = m_pCerasusfpsMain->Reset();
			hr2 = m_pDirectGraphics3DMain->Reset();
			m_pSakuraDialog->OnLost();
			m_pDirectSprite->Reset();
			hr2 = m_pDirectGraphicsMain->Reset();

			// 重置设备
			m_pSakuraDialog->OnReset();
			hr2 = m_pDirectGraphics3DMain->CreateBase(6);
			hr2 = m_pDirectSprite->Create(m_chPacketRes_sprite_00, sizeof(m_chPacketRes_sprite_00), 32, 32);
		}

	}

	m_fTimeSum += g_fDeltaTime;	// 程式时间累积

	CLiveInStartUpdate(g_fDeltaTime);

}

//----------------------------------------------
// @Function:	CLiveInRender()
// @Purpose: CLiveIn渲染
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInRender()
{
	IDirect3DDevice9* pD3D9Device = NULL;
	RECT Rect;

	GetClientRect(g_hWnd, &Rect);
	pD3D9Device = m_pDirectGraphicsMain->GetDevice();

	// DirectX 开始绘制
	m_pDirectGraphicsMain->Begin();

	// 渲染模式:Alpha混合设置
	pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);					// Alpha混合开启

	// 渲染模式:纹理混合设置
	pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);

	m_pDirectGraphics3DMain->LightDisable();			// 渲染光源关闭
	m_pDirectGraphics3DMain->Setting();					// 渲染状态设置
	m_pDirectGraphics3DMain->AlphaDisable();			// Alpha混合关闭

	m_pSakuraDialog->OnRender();	// 绘制Sakura

	if (m_bSpriteRender)			// 渲染粒子系统
	{
		CLiveInRenderSprite();
	}

	if (m_nIsShowAdapter != 0)
	{
		CLiveDrawAdapter();			// 绘制显卡型号
	}
	
	if (m_nIsShowFps != 0)
	{
		CLiveDrawfps();				// 绘制fps
	}

	// DirectX 结束绘制
	m_pDirectGraphicsMain->End();
}

//----------------------------------------------
// @Function:	CLiveInStartUpdate(float fDeltaTime)
// @Purpose: CLiveIn开始场景刷新
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInStartUpdate(float fDeltaTime)
{
	static float fTimeSum = 0.0f;

	fTimeSum += fDeltaTime;		// 运行时间累加...

	if (fTimeSum < 0.5f)		// 开始时间0.0s~0.5s时保持黑色屏幕,Alpha通道值为0.0f
	{
		m_pSakuraDialog->GetDialogGraphics()->GetAlpha() = 0.0f;	// 背景Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;		// Logo Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_01)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;		// Logo2 Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_02)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;		// Coypright Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_010)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;		// Wait Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_011)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 1.0f;		// Wait Alpha通道值为1.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_012)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 1.0f;		// Wait Alpha通道值为1.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_013)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 1.0f;		// Wait Alpha通道值为1.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;		// Wait Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;		// Wait Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;		// Wait Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;		// Wait Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;		// Wait Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_LOGIN_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;		// Login Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_ACCOUNT_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;	// Account Alpha通道值为0.0f

		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateZ() = -160.0f;	// Logo Z轴坐标为-120
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_01)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateZ() = -160.0f;	// Logo2 Z轴坐标为-120
	}
	else if (fTimeSum < 1.5f)	// 开始时间0.5s~1.5s时背景渐变,Alpha通道值增加
	{
		CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetDialogGraphics()->GetAlpha(), 1.0f, 0.02f);		// 背景Alpha通道值从0.0f递增到1.0f,递增速度0.02f,持续50帧
	}
	else if (fTimeSum < 2.5f)	// 开始时间1.5s~2.5s时背景不变,logo字体由远到近,版权信息出现
	{
		CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateZ(), -160.0f, 0.0f, -0.8f);
		CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 1.0f, 0.05f);
		CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_02)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 1.0f, 0.02f);

		if (fTimeSum >= 2.0f)
		{
			CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_01)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateZ(), -160.0f, 0.0f, -0.8f);
			CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_01)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 1.0f, 0.05f);
		}

	}
	else if (fTimeSum < 3.0f)	// 开始时间2.5s~3.0s时出现请稍候字样
	{
		CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_010)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 1.0f, 0.05f);
	}
	else if(fTimeSum < 12.0f)	// 开始时间3.0s~8.0s时等待加载资源
	{
		// 请稍候...等待字体切换
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

		// 五角星★等待动画
		static bool bStarFinish = false;		// bStarFinish=true, 五角星动画已经完成; bStarFinish=false, 五角星动画暂未完成
		static bool bStarOrder = true;			// bStarOrder=true, 五角星从左到中匀减速运动; bStarOrder=false, 五角星从中到右边匀加速运动
		static int nStarCount = 0;				// nStarCount 代表中间五角星数量
		static float fTimeInterval = 0.0f;		// fTimeInterval 五角星运动时间间隔

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
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX(), 0.0f, 179.0f, -0.4f);
				CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 1.0f, 0.2f);
			}

			if (nStarCount >= 2)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX(), 0.0f, 166.0f, -0.4f);
				CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 1.0f, 0.2f);
			}

			if (nStarCount >= 3)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX(), 0.0f, 153.0f, -0.4f);
				CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 1.0f, 0.2f);
			}

			if (nStarCount >= 4)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX(), 0.0f, 139.0f, -0.4f);
				CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 1.0f, 0.2f);
			}

			if (nStarCount >= 5)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX(), 0.0f, 126.0f, -0.4f);
				CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 1.0f, 0.2f);
			}

			// 判断五角星动画是否完成
			if(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX() >= 126.0f)
			{
				bStarFinish = true;
			}
		}
		else
		{
			if (nStarCount <= 5)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX(), 179.0f, 320.0f, -0.4f);
				CCerasusAlgorithm::Linear_Decrease(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 0.0f, 0.05f);
			}

			if (nStarCount <= 4)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX(), 166.0f, 320.0f, -0.4f);
				CCerasusAlgorithm::Linear_Decrease(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 0.0f, 0.05f);
			}

			if (nStarCount <= 3)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX(), 153.0f, 320.0f, -0.4f);
				CCerasusAlgorithm::Linear_Decrease(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 0.0f, 0.05f);
			}

			if (nStarCount <= 2)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX(), 139.0f, 320.0f, -0.4f);
				CCerasusAlgorithm::Linear_Decrease(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 0.0f, 0.05f);
			}

			if (nStarCount <= 1)
			{
				CCerasusAlgorithm::Quadratic_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX(), 126.0f, 320.0f, -0.4f);
				CCerasusAlgorithm::Linear_Decrease(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 0.0f, 0.05f);
			}

			// 判断五角星动画是否完成
			if (m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX() >= 320.0f)
			{
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateX() = 0.0f;

				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;
				m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() = 0.0f;

				bStarFinish = true;
			}

		}

	}
	else if(fTimeSum < 15.0f)
	{
		// 设置请等待字样不可见
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_010)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_011)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_012)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_013)->SetVisible(false);

		// 设置五角星动画不可见
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_001)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_002)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_003)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_004)->SetVisible(false);
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_WAIT_005)->SetVisible(false);

		CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_ACCOUNT_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 1.0f, 0.02f);

		if (fTimeSum >= 13.0f)
		{
			CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_LOGIN_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 0.6f, 0.02f);
		}

		if (m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_LOGIN_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha() >= 0.6f)
		{
			m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_LOGIN_00)->SetVisible(false);
			m_pSakuraDialog->GetButton(SID_SAKURABUTTON_LOGIN_00)->SetVisible(true);
		}

	}
	else
	{
		// 渲染粒子开始
		m_bSpriteRender = true;

		// 刷新渲染粒子
		CLiveInUpdateSprite();

		// 小彩蛋...
		m_pDirectInput->GetDeviceState(InputDevice_KeyBoard);
		
		if (m_pDirectInput->KeyBoardIsDown(DIK_LEFT))		// 方向键左键"←"按下
		{
			// Surface向左旋转...
			m_pSakuraDialog->GetDialogGraphics()->GetRotateZ() += D3DX_PI * 0.01f;

			for (auto iter = m_pSakuraDialog->GetControls().begin(); iter != m_pSakuraDialog->GetControls().end(); ++iter)
			{
				(*iter)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetRotateZ() += D3DX_PI * 0.01f;
			}

		}
		if (m_pDirectInput->KeyBoardIsDown(DIK_RIGHT))	// 方向键右键"→"按下
		{
			// Surface向右旋转...
			m_pSakuraDialog->GetDialogGraphics()->GetRotateZ() -= D3DX_PI * 0.01f;

			for (auto iter = m_pSakuraDialog->GetControls().begin(); iter != m_pSakuraDialog->GetControls().end(); ++iter)
			{
				(*iter)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetRotateZ() -= D3DX_PI * 0.01f;
			}

		}
		if (m_pDirectInput->KeyBoardIsDown(DIK_UP))		// 方向键上键"↑"按下
		{
			// Surface远离屏幕...
			m_pSakuraDialog->GetDialogGraphics()->GetTranslateZ() += 0.2f;
			if (m_pSakuraDialog->GetDialogGraphics()->GetTranslateZ() >= 0.0f)	// 不要离开摄像机视野
			{
				m_pSakuraDialog->GetDialogGraphics()->GetTranslateZ() = 0.0f;
			}

			for (auto iter = m_pSakuraDialog->GetControls().begin(); iter != m_pSakuraDialog->GetControls().end(); ++iter)
			{
				(*iter)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateZ() += 0.2f;
				if ((*iter)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateZ() >= 0.0f)	// 不要离开摄像机视野
				{
					(*iter)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateZ() = 0.0f;
				}
			}

		}
		if (m_pDirectInput->KeyBoardIsDown(DIK_DOWN))		// 方向键下键"↓"按下
		{
			// Surface靠近屏幕...
			m_pSakuraDialog->GetDialogGraphics()->GetTranslateZ() -= 0.2f;

			for (auto iter = m_pSakuraDialog->GetControls().begin(); iter != m_pSakuraDialog->GetControls().end(); ++iter)
			{
				(*iter)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateZ() -= 0.2f;
			}

		}
		if (m_pDirectInput->KeyBoardIsDown(DIK_SPACE))		// 空格键Space按下
		{
			// Surface恢复正常...
			m_pSakuraDialog->GetDialogGraphics()->GetRotateZ() = 0.0f;
			m_pSakuraDialog->GetDialogGraphics()->GetTranslateZ() = 0.0f;

			for (auto iter = m_pSakuraDialog->GetControls().begin(); iter != m_pSakuraDialog->GetControls().end(); ++iter)
			{
				(*iter)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetRotateZ() = 0.0f;
				(*iter)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetTranslateZ() = 0.0f;
			}

		}


	}

}

//----------------------------------------------
// @Function:	CLiveInReadConfigFile()
// @Purpose: CLiveIn读取配置文件信息
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
BOOL CLiveIn::CLiveInReadConfigFile()
{
	char chFile[MAX_PATH] = { 0 };

	strcpy_s(chFile, "config\\LiveIn.lua");

	CConvallariaLua* lua = new CConvallariaLua(chFile);		// lua script 实例化
	BOOL bRet = FALSE;

	bRet = lua->ConvallariaLua_Init();	// lua script 初始化
	if (!bRet)
	{
		SAFE_DELETE(lua);
		return FALSE;
	}

	lua->ConvallariaLua_GetGlobal_Int("LiveIn_Use_Log", m_nIsUseLog);					// 获取是否日志记录
	lua->ConvallariaLua_GetGlobal_Int("LiveIn_Show_Adapter", m_nIsShowAdapter);			// 获取是否显示显卡
	lua->ConvallariaLua_GetGlobal_Int("LiveIn_Show_Fps", m_nIsShowFps);					// 获取是否显示fps
	lua->ConvallariaLua_GetGlobal_Int("LiveIn_Sprite_Num", m_nSpriteNum);				// 获取粒子系统数量

	SAFE_DELETE(lua);
	return TRUE;
}

//----------------------------------------------
// @Function:	CLiveInLoadPacketFile()
// @Purpose: CLiveIn加载封包文件分析
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

	// 加载资源(bk_00.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "bk_00.png", m_chPacketRes_bk_00, sizeof(m_chPacketRes_bk_00));

	// 加载资源(title_00.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "title_00.png", m_chPacketRes_title_00, sizeof(m_chPacketRes_title_00));

	// 加载资源(title_01.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "title_01.png", m_chPacketRes_title_01, sizeof(m_chPacketRes_title_01));

	// 加载资源(title_02.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "title_02.png", m_chPacketRes_title_02, sizeof(m_chPacketRes_title_02));

	// 加载资源(wait_00.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "wait_00.png", m_chPacketRes_wait_00, sizeof(m_chPacketRes_wait_00));

	// 加载资源(wait_01.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "wait_01.png", m_chPacketRes_wait_01, sizeof(m_chPacketRes_wait_01));

	// 加载资源(login_00.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "login_00.png", m_chPacketRes_login_00, sizeof(m_chPacketRes_login_00));

	// 加载资源(account_00.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "avatar_00.png", m_chPacketRes_account_00, sizeof(m_chPacketRes_account_00));
	
	// 加载资源(sprite_00.png)
	packet.PlumUnPackOneFileStoreInMemoryA(chPacket, "sprite_00.png", m_chPacketRes_sprite_00, sizeof(m_chPacketRes_sprite_00));

	return TRUE;
}

//----------------------------------------------
// @Function:	CLiveInSetSpriteArea()
// @Purpose: CLiveIn设置粒子出现区域
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
// @Purpose: CLiveIn初始化粒子系统
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInInitSprite()
{
	// 初始化随机数种子
	srand(GetTickCount());

	// 初始化粒子系统--粒子状态
	for (int i = 0; i < m_nSpriteNum; ++i)
	{
		TLIVEINSTAR tStar = { 0 };

		tStar.fAlpha = (float)(0.5f + ((rand() % 101) * 1.0f / 200.0f));																		// 粒子Alpha: (0.5f~1.0f)
		tStar.fFallSpeed = (float)(m_nStarHeight * 1.0f / 5.0f + ((rand() % 100) * 1.0f / 200.0f) * m_nStarHeight);								// 粒子下落速度
		tStar.fMoveSpeed = (float)(((rand() % 100) * 1.0f / 500.0f) * m_nStarWidth);															// 粒子移动速度
		tStar.fRotateSpeed = (float)(D3DX_PI * 1.0f / 5.0f + ((rand() % 100) * 1.0f / 200.0f) * D3DX_PI);										// 粒子旋转速度
		tStar.nMoveDirect = rand() % 2;																											// 粒子移动方向: (0~左 1~右)
		tStar.nRotateDirect = rand() % 2;																										// 粒子旋转方向: (0~左 1~右)
		tStar.sTransformPara.sTranslatePara.fTranslateX = (float)(m_nStarPosX + m_nStarWidth * 0.1f + (rand() % m_nStarWidth) * 0.9f);			// 粒子X坐标: (x~x+width)
		tStar.sTransformPara.sTranslatePara.fTranslateY = (float)(m_nStarPosY + rand() % m_nStarHeight - m_nStarHeight);						// 粒子Y左边: (y~y+height)
		tStar.sTransformPara.sScalePara.fScaleX = (float)(0.2f + ((rand() % 80) * 1.0f / 100.0f));												// 粒子拉伸变换系数: (0.2f~1.0f)
		tStar.sTransformPara.sScalePara.fScaleY = tStar.sTransformPara.sScalePara.fScaleX;														// 粒子拉伸变换系数: (0.2f~1.0f)
		tStar.sTransformPara.sRotatePara.fRotateZ = (float)(((rand() % 100) * 1.0f / 600.0f) * D3DX_PI);										// 粒子旋转变换系数: (Arc:0~Pi/6)

		m_vecStarArray.push_back(tStar);
	}

}

//----------------------------------------------
// @Function:	CLiveInUpdateSprite()
// @Purpose: CLiveIn刷新粒子
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
			iter->fAlpha = (float)(0.5f + ((rand() % 101) * 1.0f / 200.0f));																		// 粒子Alpha: (0.5f~1.0f)
			iter->fFallSpeed = (float)(m_nStarHeight * 1.0f / 5.0f + ((rand() % 100) * 1.0f / 200.0f) * m_nStarHeight);								// 粒子下落速度
			iter->fMoveSpeed = (float)(((rand() % 100) * 1.0f / 500.0f) * m_nStarWidth);															// 粒子移动速度
			iter->fRotateSpeed = (float)(D3DX_PI * 1.0f / 5.0f + ((rand() % 100) * 1.0f / 200.0f) * D3DX_PI);										// 粒子旋转速度
			iter->nMoveDirect = rand() % 2;																											// 粒子移动方向: (0~左 1~右)
			iter->nRotateDirect = rand() % 2;																										// 粒子旋转方向: (0~左 1~右)
			iter->sTransformPara.sTranslatePara.fTranslateX = (float)(m_nStarPosX + m_nStarWidth * 0.1f + (rand() % m_nStarWidth) * 0.9f);			// 粒子X坐标: (x~x+width)
			iter->sTransformPara.sTranslatePara.fTranslateY = (float)(m_nStarPosY + rand() % m_nStarHeight - m_nStarHeight);						// 粒子Y左边: (y~y+height)
			iter->sTransformPara.sScalePara.fScaleX = (float)(0.2f + ((rand() % 80) * 1.0f / 100.0f));												// 粒子拉伸变换系数: (0.2f~1.0f)
			iter->sTransformPara.sScalePara.fScaleY = iter->sTransformPara.sScalePara.fScaleX;														// 粒子拉伸变换系数: (0.2f~1.0f)
			iter->sTransformPara.sRotatePara.fRotateZ = (float)(((rand() % 100) * 1.0f / 600.0f) * D3DX_PI);										// 粒子旋转变换系数: (Arc:0~Pi/6)
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
// @Purpose: CLiveIn渲染粒子
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInRenderSprite()
{
	m_pDirectSprite->Begin();

	for(auto iter = m_vecStarArray.begin(); iter != m_vecStarArray.end(); ++iter)
	{
		S_DX_SPRITE_DRAW_PARA sDrawPara = { 0 };
		SetRect(&sDrawPara.SpriteRect, 0, 0, 21, 20);
		sDrawPara.SpriteCenter = D3DXVECTOR3(10.0f, 11.0f, 0.0f);
		sDrawPara.SpritePosition = D3DXVECTOR3(iter->sTransformPara.sTranslatePara.fTranslateX, iter->sTransformPara.sTranslatePara.fTranslateY, 0.0f);
		sDrawPara.SpriteColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, iter->fAlpha);
		m_pDirectSprite->DrawTransform(&sDrawPara, iter->sTransformPara, iter->sTransformPara.sTranslatePara.fTranslateY, m_nStarPosY);
	}

	m_pDirectSprite->End();
}

//----------------------------------------------
// @Function:	CLiveDrawAdapter()
// @Purpose: CLiveIn绘制显卡信息
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveDrawAdapter()
{
	RECT Rect;

	GetClientRect(g_hWnd, &Rect);

	// Direct3D 绘制显卡信息
	Rect.top += 0;
	m_pDirectGraphicsMain->DrawAdapterType(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));

	// Direct3D 绘制屏幕分辨率
	Rect.top += 20;
	m_pDirectGraphicsMain->DrawScreenInfo(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

	// Direct3D 绘制缓冲模板
	Rect.top += 20;
	m_pDirectGraphicsMain->DrawFormatInfo(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));
}

//----------------------------------------------
// @Function:	CLiveDrawfps()
// @Purpose: CLiveIn绘制fps
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveDrawfps()
{
	m_pCerasusfpsMain->CalculateFps();				// Direct3D 绘制静态信息
	m_pCerasusfpsMain->DrawFps(g_hWnd, DX_FONT_FORMAT_BOTTOMRIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		// Direct3D 绘制fps
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResBK00()
// @Purpose: CLiveIn加载背景bk_00资源结构
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResBK00(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResTITLE00()
// @Purpose: CLiveIn加载背景title_00资源结构
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResTITLE00(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResTITLE01()
// @Purpose: CLiveIn加载背景title_01资源结构
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResTITLE01(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResTITLE02()
// @Purpose: CLiveIn加载背景title_02资源结构
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResTITLE02(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT01_0()
// @Purpose: CLiveIn加载背景wait_01资源结构(请稍候)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT01_0(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT01_1()
// @Purpose: CLiveIn加载背景wait_01资源结构(请稍候.)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT01_1(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT01_2()
// @Purpose: CLiveIn加载背景wait_01资源结构(请稍候..)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT01_2(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT01_3()
// @Purpose: CLiveIn加载背景wait_01资源结构(请稍候...)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT01_3(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT00_0()
// @Purpose: CLiveIn加载背景wait_00资源结构(五角星)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT00_0(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT00_1()
// @Purpose: CLiveIn加载背景wait_00资源结构(五角星)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT00_1(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT00_2()
// @Purpose: CLiveIn加载背景wait_00资源结构(五角星)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT00_2(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT00_3()
// @Purpose: CLiveIn加载背景wait_00资源结构(五角星)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT00_3(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResWAIT00_4()
// @Purpose: CLiveIn加载背景wait_00资源结构(五角星)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResWAIT00_4(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResLOGIN00()
// @Purpose: CLiveIn加载按钮login_00资源(登录)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResLOGIN00(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResACCOUNT00()
// @Purpose: CLiveIn加载背景account_00资源(账户)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInAddPacketResACCOUNT00(S_CS_UNIT_EX_PARA& sUnitEx)
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

	//世界变换
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sUnitEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sUnitEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_WINDOWHEIGHT * 0.5f));

	//投影变换
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_WINDOWWIDTH * 1.0f / USER_WINDOWHEIGHT);
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sUnitEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_WINDOWHEIGHT * 0.5f);

	//视口变换
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_WINDOWWIDTH;
	sUnitEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_WINDOWHEIGHT;
}

//CDXSampleCore 控件事件回调函数 
void __stdcall CLiveInSakuraGUIEvent(UINT nEvent, int nControlID, CSakuraControl * pControl, void * pUserContext)
{
	switch (nEvent)
	{
	case EVENT_BUTTON_CLICKED:
		{
			if (nControlID == SID_SAKURABUTTON_LOGIN_00)
			{
				CPlumProcess::PlumProcessStartProcessExA("LiveProject.exe");
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
