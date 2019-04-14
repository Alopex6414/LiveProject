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
CRITICAL_SECTION g_csDecode;							// LiveCore 视频解码Cirtical
volatile bool g_bDecodeFlag = false;					// LiveCore 视频解码标志

CRITICAL_SECTION g_csWait;								// LiveCore 默认视频Cirtical
volatile bool g_bWaitFlag = false;						// LiveCore 默认视频标志

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
	m_pDirectGraphicsMain(NULL),
	m_nDeskTopWidth(0),
	m_nDeskTopHeight(0),
	m_nLiveCoreMode(0),
	m_nLiveCoreShowGraphics(0),
	m_nLiveCoreShowGraphicsFont(0),
	m_nLiveCoreWallpaperMode(0),
	m_nLiveCoreWallpaperAudioMode(0),
	m_nLiveCoreLogProcess(0),
	m_nLiveCoreVideoMode(0)
{
	m_pPlumWait = nullptr;
	m_pPlumUnpack = nullptr;

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
	SAFE_DELETE(m_pDirectGraphicsMain);
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
