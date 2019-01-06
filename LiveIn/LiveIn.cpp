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
CLiveIn::CLiveIn() :m_nIsUseLog(0), m_nIsShowAdapter(0), m_nIsShowFps(0)
{
	m_pDirectGraphicsMain = NULL;
	m_pDirectGraphics3DMain = NULL;
	m_pCerasusfpsMain = NULL;
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
			// 丢失设备
			m_pCerasusfpsMain->CCerasusfpsReset();
			m_pDirectGraphics3DMain->DirectGraphics3DReset();
			m_pDirectGraphicsMain->DirectGraphicsReset();

			// 重置设备
			m_pDirectGraphics3DMain->DirectGraphics3DInitVertex3DBase(6);
		}

	}
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
	m_pCerasusfpsMain->CCerasusfpsDrawfps(g_hWnd);		// Direct3D 绘制fps
}
