/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCore.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-13
*/
#include "LiveCore.h"

#pragma warning (disable:4996)

// CLiveCore类
CLiveCore* g_LiveCore = nullptr;						// LiveCore 实例

CRITICAL_SECTION g_csDecode;							// LiveCore 视频解码Cirtical
volatile bool g_bDecodeFlag = false;					// LiveCore 视频解码标志

CRITICAL_SECTION g_csWait;								// LiveCore 默认视频Cirtical
volatile bool g_bWaitFlag = false;						// LiveCore 默认视频标志

bool g_bReStart = false;								// LiveCore 重启标志
bool g_bMonitorFlag = false;							// LiveCore 监视标志

char g_chDefaultVideoAddress[MAX_PATH] = { 0 };			// LiveCore 默认视频地址
char g_chDefaultVideoDirector[MAX_PATH] = { 0 };		// LiveCore 默认视频路径
char g_chDefaultVideoUnpack[MAX_PATH] = { 0 };			// LiveCore 拆包视频路径

unsigned char* g_pArrayY = NULL;						// LiveCore YUV图像Y帧指针
unsigned char* g_pArrayU = NULL;						// LiveCore YUV图像U帧指针
unsigned char* g_pArrayV = NULL;						// LiveCore YUV图像V帧指针

//----------------------------------------------
// @Function:	CLiveCore()
// @Purpose: CLiveCore构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
CLiveCore::CLiveCore() :
	m_pMainGraphics(NULL),
	m_pD3D9Device(NULL),
	m_pD3D9Surface(NULL),
	m_nDeskTopWidth(0),
	m_nDeskTopHeight(0),
	m_nVideoWidth(0),
	m_nVideoHeight(0),
	m_nVideoFreq(0),
	m_nLiveCoreMode(0),
	m_nLiveCoreShowGraphics(0),
	m_nLiveCoreShowGraphicsFont(0),
	m_nLiveCoreWallpaperMode(0),
	m_nLiveCoreWallpaperAudioMode(0),
	m_nLiveCoreLogProcess(0),
	m_nLiveCoreVideoMode(0)
{
	g_pPlumThread = nullptr;
	g_pPlumThread2 = nullptr;
	m_pPlumWait = nullptr;
	m_pPlumUnpack = nullptr;
	g_pPlumMonitor = nullptr;

	g_LiveCore = this;

	memset(m_chLiveCoreVideoName, 0, MAX_PATH);
	memset(m_chLiveCoreVideoAddress, 0, MAX_PATH);
}

//----------------------------------------------
// @Function:	~CLiveCore()
// @Purpose: CLiveCore析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
CLiveCore::~CLiveCore()
{
	SAFE_DELETE(m_pMainGraphics);
}

//----------------------------------------------
// @Function:	CLiveCoreInit()
// @Purpose: CLiveCore初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
BOOL CLiveCore::CLiveCoreInit()
{
	HRESULT hr;

	// get desktop window resolution...
	m_nDeskTopWidth = GetSystemMetrics(SM_CXSCREEN);
	m_nDeskTopHeight = GetSystemMetrics(SM_CYSCREEN);

	// analyze config file...
	AnalyzeConfigFile();
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Analyze Config File. Para:LiveCoreMode=%d, Para:LiveCoreShowGraphics=%d, Para:LiveCoreShowGraphicsFont=%d, "\
																"Para:LiveCoreWallpaperMode=%d, Para:LiveCoreWallpaperAudioMode=%d, Para:LiveCoreLogProcess=%d.", m_nLiveCoreMode, m_nLiveCoreShowGraphics, m_nLiveCoreShowGraphicsFont, m_nLiveCoreWallpaperMode, m_nLiveCoreWallpaperAudioMode, m_nLiveCoreLogProcess);
	// record config file...
	RecordConfigFile();

	// check LiveProject process exist...
	if (m_nLiveCoreMode == 0)
	{
		if (!CPlumProcess::PlumProcessIsProcessExistExA("LiveProject.exe"))
		{
			CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Can not find LiveProject.exe Process.");
			return FALSE;
		}
	}

	// initialize critical section...
	InitializeCriticalSection(&g_csWait);

	// whether to enable the default video...
	if (m_nLiveCoreVideoMode == 0)
	{
		char* pTemp = NULL;

		// get default video path...
		GetModuleFileNameA(NULL, g_chDefaultVideoDirector, MAX_PATH);
		pTemp = strrchr(g_chDefaultVideoDirector, '\\');
		if (pTemp)* pTemp = '\0';
		strcat_s(g_chDefaultVideoDirector, "\\data\\");

		memcpy_s(g_chDefaultVideoAddress, MAX_PATH, g_chDefaultVideoDirector, MAX_PATH);
		strcat_s(g_chDefaultVideoAddress, m_chLiveCoreVideoName);

		// start wait for decrypt...
		g_bWaitFlag = true;

		// start waiting process...
		m_pPlumWait = new CPlumThread(&m_LiveCoreWait);
		m_pPlumWait->PlumThreadInit();
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Start Wait Thread.");

		// start unpacking process...
		m_pPlumUnpack = new CPlumThread(&m_LiveCoreUnpack);
		m_pPlumUnpack->PlumThreadInit();
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Start Unpack Thread.");

		// waiting for process execution...
		m_pPlumUnpack->PlumThreadJoin();
		if (m_pPlumUnpack)
		{
			m_pPlumUnpack->PlumThreadExit();
			SAFE_DELETE(m_pPlumUnpack);
			CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Unpack Thread Exit.");
		}

		ZeroMemory(m_chLiveCoreVideoAddress, MAX_PATH);
		memcpy_s(m_chLiveCoreVideoAddress, MAX_PATH, g_chDefaultVideoUnpack, MAX_PATH);

		EnterCriticalSection(&g_csWait);
		g_bWaitFlag = false;
		LeaveCriticalSection(&g_csWait);

		// waiting for process execution...
		m_pPlumWait->PlumThreadJoin();
		if (m_pPlumWait)
		{
			m_pPlumWait->PlumThreadExit();
			SAFE_DELETE(m_pPlumWait);
			CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Wait Thread Exit.");
		}
	}

	// turn on thread monitor...
	g_pPlumMonitor = new CPlumThread(&g_cLiveCoreMonitor);
	g_pPlumMonitor->PlumThreadInit();
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Start Monitor Thread.");

	// perform a separate desktop icon applet...
	if (!CPlumProcess::PlumProcessStartProcessExA("LiveCorePre.dll"))
	{
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Fail Run Monitor PreProcess.");
		return FALSE;
	}

	// waiting for process execution...
	g_pPlumMonitor->PlumThreadJoin();
	if (g_pPlumMonitor)
	{
		g_pPlumMonitor->PlumThreadExit();
		SAFE_DELETE(g_pPlumMonitor);
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Monitor Thread Exit.");
	}

	// set live wallpaper window...
	SetChildWindow(g_hWnd);
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Set Window Handle.");

	// initialize Graphics...
	m_pMainGraphics = new DirectGraphics();
	hr = m_pMainGraphics->DirectGraphicsInit(g_hWnd, true, m_nDeskTopWidth, m_nDeskTopHeight);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("Direct3D初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Fail Init Direct3D Graphics.");
		return FALSE;
	}
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Init Direct3D Graphics.");

	// whether to display the graphics card model and frame rate (Debug Mode)...
	if (m_nLiveCoreShowGraphics != 0)
	{
		// initialize font...
		hr = m_pMainGraphics->DirectGraphicsFontInit(m_nLiveCoreShowGraphicsFont);
		if (FAILED(hr))
		{
			MessageBox(g_hWnd, _T("Direct3DFont初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
			CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Fail Init Direct3D Font.");
			return FALSE;
		}
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Init Direct3D Font.");
	}

	m_pD3D9Device = m_pMainGraphics->DirectGraphicsGetDevice();			// get D3D9 graphics device

	// analyze video information...
	if (!AnalyzeVideoInfo(g_hWnd, m_chLiveCoreVideoAddress, &m_nVideoWidth, &m_nVideoHeight, &m_nVideoFreq))
	{
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Fail Analyze Video Infomation.");
		return FALSE;
	}
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Analyze Video Infomation.");
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Para:VideoWidth=%d, Para:VideoHeight=%d, Para:VideoFreq=%d.", m_nVideoWidth, m_nVideoHeight, m_nVideoFreq);

	if (m_nVideoFreq == 0)
	{
		m_nVideoFreq = 60;	// fps!=0
	}

	// initialize Surface...
	hr = m_pD3D9Device->CreateOffscreenPlainSurface(m_nVideoWidth, m_nVideoHeight, (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'), D3DPOOL_DEFAULT, &m_pD3D9Surface, NULL);
	if (hr)
	{
		MessageBox(g_hWnd, L"Direct3DSurface初始化失败!", L"错误", MB_OK | MB_ICONERROR);
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Fail Init Direct3D Surface.");
		return FALSE;
	}
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Init Direct3D Surface.");

	// initialize fps...
	if (m_nLiveCoreShowGraphics != 0)
	{
		m_pMainfps = new CCerasusfps(m_pD3D9Device);
		m_pMainfps->CCerasusfpsInit(m_nLiveCoreShowGraphicsFont, (LPWSTR)_T("Consolas"));
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Init Cerasus fps.");
	}

	// initialize critical section...
	InitializeCriticalSection(&g_csDecode);
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Init Critical Section.");

	g_pPlumThread = new CPlumThread(&g_cLiveCoreThread);
	g_pPlumThread->PlumThreadInit();
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Init Decode Video Thread.");

	// play video & audio...
	if (m_nLiveCoreWallpaperAudioMode != 0)
	{
		g_pPlumThread2 = new CPlumThread(&g_cLiveCoreThread2);
		g_pPlumThread2->PlumThreadInit();
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Init Decode Audio Thread.");
	}

	return TRUE;
}

//----------------------------------------------
// @Function:	CLiveCoreRelease()
// @Purpose: CLiveCore释放
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::CLiveCoreRelease()
{
}

//----------------------------------------------
// @Function:	CLiveCoreUpdate()
// @Purpose: CLiveCore刷新
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::CLiveCoreUpdate()
{
}

//----------------------------------------------
// @Function:	CLiveCoreRender()
// @Purpose: CLiveCore渲染
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::CLiveCoreRender()
{
}

//----------------------------------------------
// @Function:	AnalyzeConfigFile()
// @Purpose: CLiveCore分析配置文件
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::AnalyzeConfigFile()
{
	char chFile[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	// analyze file path...
	CPlumFile* pFile = new CPlumFile();
	pFile->PlumFileGetModuleFileNameA(chFile, MAX_PATH);

	pTemp = strrchr(chFile, '\\');
	if (pTemp)* pTemp = '\0';
	strcat_s(chFile, "\\config\\LiveCore.cfg");

	// analyze config info...
	char chArray[MAX_PATH] = { 0 };
	int nValue = 0;

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREMODE", "LiveCore_Mode", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreMode = nValue;																							// LiveCore模式: 0~组合模式 1~分离模式

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_Graphics", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreShowGraphics = nValue;																					// LiveCore显示: 0~不显示显卡型号(fps) 1~显示显卡型号(fps)

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_GraphicsFont", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreShowGraphicsFont = nValue;																				// LiveCore显示字体大小

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreWallpaperMode = nValue;																					// LiveCore屏幕分辨率模式: 0~填充 1~适应 2~拉伸 3~平铺 4~居中

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Audio", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreWallpaperAudioMode = nValue;																				// LiveCore音频播放模式: 0~不播放音频 1~播放音频

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORELOGMODE", "LiveCore_Log_Process", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreLogProcess = nValue;																						// LiveCore日志记录: 0~不记录过程 1~记录过程

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Mode", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreVideoMode = nValue;																						// LiveCore动态壁纸视频模式: 0~启用默认视频 1~启用选择视频

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Name", 0, chArray, MAX_PATH, chFile);
	memcpy_s(m_chLiveCoreVideoName, MAX_PATH, chArray, MAX_PATH);														// LiveCore动态壁纸默认视频名称

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Address", 0, chArray, MAX_PATH, chFile);
	memcpy_s(m_chLiveCoreVideoAddress, MAX_PATH, chArray, MAX_PATH);													// LiveCore动态壁纸视频地址

	// safe delete object...
	SAFE_DELETE(pFile);
}

//----------------------------------------------
// @Function:	RecordConfigFile()
// @Purpose: CLiveCore记录配置文件
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::RecordConfigFile()
{
	char chFile[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	// analyze file path...
	CPlumFile* pFile = new CPlumFile();
	pFile->PlumFileGetModuleFileNameA(chFile, MAX_PATH);

	pTemp = strrchr(chFile, '\\');
	if (pTemp)* pTemp = '\0';
	strcat_s(chFile, "\\config\\LiveCore.cfg");

	// record window handle...
	char chArrValue[MAX_PATH] = { 0 };
	memset(chArrValue, 0, MAX_PATH);
	itoa((int)g_hWnd, chArrValue, 10);
	WritePrivateProfileStringA("LIVECOREWINDOW", "LiveCore_Window_Handle", chArrValue, chFile);

	// safe delete object...
	SAFE_DELETE(pFile);
}

//----------------------------------------------
// @Function:	SetChildWindow()
// @Purpose: CLiveCore设置桌面子窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::SetChildWindow(HWND hChildWindow)
{
	HWND hDeskTop = NULL;
	HWND hShellDefView = NULL;
	HWND hSysListView32 = NULL;
	HWND hTemp = NULL;
	DWORD dwReturn = 0;

	hDeskTop = FindWindowEx(GetDesktopWindow(), NULL, L"Progman", L"Program Manager");
	hShellDefView = FindWindowEx(hDeskTop, NULL, L"SHELLDLL_DefView", 0);

	if (hShellDefView == NULL)
	{
		hTemp = FindWindowEx(GetDesktopWindow(), NULL, L"WorkerW", 0);
		while (hTemp != NULL)
		{
			hShellDefView = FindWindowEx(hTemp, NULL, L"SHELLDLL_DefView", 0);
			if (hShellDefView != NULL) break;
			hTemp = FindWindowEx(GetDesktopWindow(), hTemp, L"WorkerW", 0);
		}
	}

	hSysListView32 = FindWindowEx(hShellDefView, NULL, L"SysListView32", L"FolderView");
	SetParent(hChildWindow, hDeskTop);
}

//----------------------------------------------
// @Function:	AnalyzeVideoInfo()
// @Purpose: CLiveCore分析视频信息
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
BOOL CLiveCore::AnalyzeVideoInfo(HWND hWnd, const char* pVideoPath, int* pWidth, int* pHeight, int* pFreq)
{
	AVFormatContext* pFormatCtx;
	AVCodecContext* pCodecCtx;
	AVCodec* pCodec;

	av_register_all();//注册所有组件
	pFormatCtx = avformat_alloc_context();//初始化一个AVFormatContext

	// 打开输入的视频文件
	if (avformat_open_input(&pFormatCtx, pVideoPath, NULL, NULL) != 0)
	{
		MessageBox(hWnd, L"打开文件失败!", L"错误", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// 获取视频文件信息
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		MessageBox(hWnd, L"无法读取文件信息!", L"错误", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	int VideoIndex = -1;

	for (int i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			VideoIndex = i;
			break;
		}
	}

	if (VideoIndex == -1)
	{
		MessageBox(hWnd, L"未读取到视频信息!", L"错误", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	pCodecCtx = pFormatCtx->streams[VideoIndex]->codec;

	//查找解码器
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		MessageBox(hWnd, L"未查找到解码器!", L"错误", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//打开解码器
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		MessageBox(hWnd, L"无法打开解码器!", L"错误", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	*pWidth = pCodecCtx->width;
	*pHeight = pCodecCtx->height;
	*pFreq = pCodecCtx->framerate.num;

	avcodec_close(pCodecCtx);
	avformat_free_context(pFormatCtx);

	return TRUE;
}
