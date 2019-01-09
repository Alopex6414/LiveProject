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
CLiveIn::CLiveIn() :m_nIsUseLog(0), m_nIsShowAdapter(0), m_nIsShowFps(0), m_fTimeSum(0.0f)
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
	hr = m_pDirectGraphicsMain->DirectGraphicsInit(g_hWnd, true, USER_WINDOWWIDTH, USER_WINDOWHEIGHT);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "Direct3D初始化失败!返回值hr=%l.", hr);
		MessageBox(g_hWnd, _T("Direct3D初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "Direct3D初始化成功!");

	hr = m_pDirectGraphicsMain->DirectGraphicsFontInit(20);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectFont初始化失败!返回值hr=%l.", hr);
		MessageBox(g_hWnd, _T("DirectFont初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectFont初始化成功!");

	pD3D9Device = m_pDirectGraphicsMain->DirectGraphicsGetDevice();		// DirectX设备指针

	// DirectGraphics3D 初始化
	m_pDirectGraphics3DMain = new DirectGraphics3D(pD3D9Device);
	hr = m_pDirectGraphics3DMain->DirectGraphics3DInitVertex3DBase(6);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectGraphics3D初始化失败!返回值hr=%l.", hr);
		MessageBox(g_hWnd, _T("DirectGraphics3D初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "DirectGraphics3D初始化成功!");

	// Cerasusfps 初始化
	m_pCerasusfpsMain = new CCerasusfps(pD3D9Device);
	hr = m_pCerasusfpsMain->CCerasusfpsInit(20);
	if (FAILED(hr))
	{
		if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "Cerasusfps初始化失败!返回值hr=%l.", hr);
		MessageBox(g_hWnd, _T("Cerasusfps初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (m_nIsUseLog != 0) CLiveInLog::LiveInLogExWriteLine(__FILE__, __LINE__, "Cerasusfps初始化成功!");

	// CLiveIn 加载资源文件
	CLiveInLoadPacketFile();

	// SakuraResourceManager 初始化
	m_pResourceManager = new CSakuraResourceManager();
	m_pResourceManager->OnCreate(pD3D9Device);

	CUUintEx sUnitEx_bk_00 = { 0 };
	CLiveInAddPacketResBK00(sUnitEx_bk_00);

	// SakuraDialog 初始化
	m_pSakuraDialog = new CSakuraDialog();
	m_pSakuraDialog->OnCreate(m_pResourceManager, sUnitEx_bk_00);
	m_pSakuraDialog->SetLocation(0, 0);
	m_pSakuraDialog->SetSize(USER_WINDOWWIDTH, USER_WINDOWHEIGHT);
	m_pSakuraDialog->SetCallback(CLiveInSakuraGUIEvent, this);

	// SakuraResourceManager 资源载入
	CUUintEx sUnitEx_title_00 = { 0 };
	CLiveInAddPacketResTITLE00(sUnitEx_title_00);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_title_00);

	CUUintEx sUnitEx_title_01 = { 0 };
	CLiveInAddPacketResTITLE01(sUnitEx_title_01);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_title_01);

	CUUintEx sUnitEx_title_02 = { 0 };
	CLiveInAddPacketResTITLE02(sUnitEx_title_02);
	m_pSakuraDialog->SetTextrueExRes(&sUnitEx_title_02);

	// SakuraControl 初始化
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_TITLE_00, 32, 64, 256, 64);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_TITLE_01, 32, 128, 256, 32);
	m_pSakuraDialog->AddUnit(SID_SAKURAUNIT_TITLE_02, 32, 432, 256, 32);

	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_TITLE_00, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 0);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_TITLE_01, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 1);
	m_pSakuraDialog->AddTextureEx(SID_SAKURAUNIT_TITLE_02, SAKURA_CONTROL_UNIT, 0, SAKURA_STATE_NORMAL, 2);

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
	hr = m_pDirectGraphicsMain->DirectGraphicsTestCooperativeLevel();
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
			hr2 = m_pCerasusfpsMain->CCerasusfpsReset();
			hr2 = m_pDirectGraphics3DMain->DirectGraphics3DReset();
			m_pSakuraDialog->OnLost();
			hr2 = m_pDirectGraphicsMain->DirectGraphicsReset();

			// 重置设备
			m_pSakuraDialog->OnReset();
			hr2 = m_pDirectGraphics3DMain->DirectGraphics3DInitVertex3DBase(6);
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
	pD3D9Device = m_pDirectGraphicsMain->DirectGraphicsGetDevice();

	// DirectX 开始绘制
	m_pDirectGraphicsMain->DirectGraphicsBegin();

	// 渲染模式:Alpha混合设置
	pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);					// Alpha混合开启

	// 渲染模式:纹理混合设置
	pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);

	m_pDirectGraphics3DMain->DirectGraphics3DRenderStateLightDisable();			// 渲染光源关闭
	m_pDirectGraphics3DMain->DirectGraphics3DRenderStateSetting();				// 渲染状态设置
	m_pDirectGraphics3DMain->DirectGraphics3DRenderStateAlphaDisable();			// Alpha混合关闭

	m_pSakuraDialog->OnRender();	// 绘制Sakura

	if (m_nIsShowAdapter != 0)
	{
		CLiveDrawAdapter();			// 绘制显卡型号
	}
	
	if (m_nIsShowFps != 0)
	{
		CLiveDrawfps();				// 绘制fps
	}

	// DirectX 结束绘制
	m_pDirectGraphicsMain->DirectGraphicsEnd();
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
		m_pSakuraDialog->GetDialogGraphics()->CCerasusUnitGetAlpha() = 0.0f;	// 背景Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Logo Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_01)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Logo2 Alpha通道值为0.0f
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_02)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetAlpha() = 0.0f;		// Coypright Alpha通道值为0.0f
	
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_00)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateZ() = -160.0f;	// Logo Z轴坐标为-120
		m_pSakuraDialog->GetUnit(SID_SAKURAUNIT_TITLE_01)->GetElements().at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->CCerasusUnitGetTranslateZ() = -160.0f;	// Logo2 Z轴坐标为-120
	}
	else if (fTimeSum < 1.5f)	// 开始时间0.5s~1.5s时背景渐变,Alpha通道值增加
	{
		CCerasusAlgorithm::Linear_Increase(m_pSakuraDialog->GetDialogGraphics()->CCerasusUnitGetAlpha(), 1.0f, 0.02f);		// 背景Alpha通道值从0.0f递增到1.0f,递增速度0.02f,持续50帧
	}
	else if (fTimeSum < 2.5f)
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

	return TRUE;
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
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextAdapterType(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));

	// Direct3D 绘制屏幕分辨率
	Rect.top += 20;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextScreen(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

	// Direct3D 绘制缓冲模板
	Rect.top += 20;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextFormat(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));
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
	m_pCerasusfpsMain->CCerasusfpsGetfps();				// Direct3D 绘制静态信息
	m_pCerasusfpsMain->CCerasusfpsDrawfps(g_hWnd, DIRECTFONT_FORMAT_BOTTOMRIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		// Direct3D 绘制fps
}

//----------------------------------------------
// @Function:	CLiveInAddPacketResBK00()
// @Purpose: CLiveIn加载背景bk_00资源结构
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

}
