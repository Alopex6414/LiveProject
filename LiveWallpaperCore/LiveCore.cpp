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

// CLiveCore��
CLiveCore* g_pLiveCore = nullptr;						// LiveCore ʵ��

CRITICAL_SECTION g_csDecode;							// LiveCore ��Ƶ����Cirtical
volatile bool g_bDecodeFlag = false;					// LiveCore ��Ƶ�����־

CRITICAL_SECTION g_csWait;								// LiveCore Ĭ����ƵCirtical
volatile bool g_bWaitFlag = false;						// LiveCore Ĭ����Ƶ��־

bool g_bReStart = false;								// LiveCore ������־
bool g_bMonitorFlag = false;							// LiveCore ���ӱ�־

char g_chDefaultVideoAddress[MAX_PATH] = { 0 };			// LiveCore Ĭ����Ƶ��ַ
char g_chDefaultVideoDirector[MAX_PATH] = { 0 };		// LiveCore Ĭ����Ƶ·��
char g_chDefaultVideoUnpack[MAX_PATH] = { 0 };			// LiveCore �����Ƶ·��

unsigned char* g_pArrayY = NULL;						// LiveCore YUVͼ��Yָ֡��
unsigned char* g_pArrayU = NULL;						// LiveCore YUVͼ��Uָ֡��
unsigned char* g_pArrayV = NULL;						// LiveCore YUVͼ��Vָ֡��

//----------------------------------------------
// @Function:	CLiveCore()
// @Purpose: CLiveCore���캯��
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
	m_nVideoFreq(60),
	m_nLiveCoreMode(0),
	m_nLiveCoreShowGraphics(0),
	m_nLiveCoreShowGraphicsFont(0),
	m_nLiveCoreWallpaperMode(0),
	m_nLiveCoreWallpaperAudioMode(0),
	m_nLiveCoreLogProcess(0),
	m_nLiveCorePlayMode(0),
	m_nLiveCoreVideoMode(0)
{
	g_pPlumThread = nullptr;
	g_pPlumThread2 = nullptr;
	m_pPlumWait = nullptr;
	m_pPlumUnpack = nullptr;
	g_pPlumMonitor = nullptr;

	g_pLiveCore = this;

	memset(m_chLiveCoreVideoName, 0, MAX_PATH);
	memset(m_chLiveCoreVideoAddress, 0, MAX_PATH);
}

//----------------------------------------------
// @Function:	~CLiveCore()
// @Purpose: CLiveCore��������
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
// @Purpose: CLiveCore��ʼ��
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
	hr = m_pMainGraphics->Create(g_hWnd, true, m_nDeskTopWidth, m_nDeskTopHeight);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("Direct3D��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Fail Init Direct3D Graphics.");
		return FALSE;
	}
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Init Direct3D Graphics.");

	// whether to display the graphics card model and frame rate (Debug Mode)...
	if (m_nLiveCoreShowGraphics != 0)
	{
		// initialize font...
		hr = m_pMainGraphics->Create2(m_nLiveCoreShowGraphicsFont);
		if (FAILED(hr))
		{
			MessageBox(g_hWnd, _T("Direct3DFont��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
			CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Fail Init Direct3D Font.");
			return FALSE;
		}
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Init Direct3D Font.");
	}

	m_pD3D9Device = m_pMainGraphics->GetDevice();			// get D3D9 graphics device

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
		MessageBox(g_hWnd, L"Direct3DSurface��ʼ��ʧ��!", L"����", MB_OK | MB_ICONERROR);
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Fail Init Direct3D Surface.");
		return FALSE;
	}
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Init Direct3D Surface.");

	// initialize fps...
	if (m_nLiveCoreShowGraphics != 0)
	{
		m_pMainfps = new CCerasusfps(m_pD3D9Device);
		m_pMainfps->Create(m_nLiveCoreShowGraphicsFont, (LPWSTR)_T("Consolas"));
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
// @Purpose: CLiveCore�ͷ�
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::CLiveCoreRelease()
{
	// delete critical section...
	DeleteCriticalSection(&g_csWait);
	DeleteCriticalSection(&g_csDecode);

	SAFE_DELETE_ARRAY(g_pArrayY);
	SAFE_DELETE_ARRAY(g_pArrayU);
	SAFE_DELETE_ARRAY(g_pArrayV);

	if (m_nLiveCoreWallpaperAudioMode != 0)
	{
		if (g_pPlumThread2)
		{
			g_pPlumThread2->PlumThreadExit();
			SAFE_DELETE(g_pPlumThread2);
		}
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Decode Audio Thread Exit.");
	}

	if (g_pPlumThread)
	{
		g_pPlumThread->PlumThreadExit();
		SAFE_DELETE(g_pPlumThread);
	}
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Decode Video Thread Exit.");

	SAFE_DELETE(m_pMainfps);
	SAFE_DELETE(m_pMainGraphics);

	if (m_nLiveCoreVideoMode == 0)
	{
		//LiveCoreCleanUp(g_chDefaultVideoUnpack);
	}

	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Process Exit.");
}

//----------------------------------------------
// @Function:	CLiveCoreUpdate()
// @Purpose: CLiveCoreˢ��
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::CLiveCoreUpdate()
{
	D3DLOCKED_RECT Rect;

	if (g_bDecodeFlag)
	{
		HRESULT hr;

		if (!g_bActive)
		{
			Sleep(50);
		}

		EnterCriticalSection(&g_csDecode);
		hr = m_pMainGraphics->TestCooperativeLevel();
		if (hr != S_OK)
		{
			CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Direct3D Lost Device!");
			if (hr == D3DERR_DEVICELOST)
			{
				LeaveCriticalSection(&g_csDecode);
				return;
			}

			if (hr == D3DERR_DEVICENOTRESET)
			{
				IDirect3DSurface9* pD3D9BackBuffer = NULL;

				if (m_nLiveCoreShowGraphics != 0)
				{
					hr = m_pMainfps->Reset();
				}

				hr = m_pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &pD3D9BackBuffer);
				SAFE_RELEASE(pD3D9BackBuffer);
				SAFE_RELEASE(m_pD3D9Surface);

				hr = m_pMainGraphics->Reset();

				hr = m_pD3D9Device->CreateOffscreenPlainSurface(m_nVideoWidth, m_nVideoHeight, (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'), D3DPOOL_DEFAULT, &m_pD3D9Surface, NULL);
				CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Direct3D Reset Device!");
			}
		}

		m_pD3D9Surface->LockRect(&Rect, 0, 0);
		for (int i = 0; i < m_nVideoHeight; ++i)
		{
			memcpy((BYTE*)(Rect.pBits) + i * Rect.Pitch, (BYTE*)g_pArrayY + i * m_nVideoWidth, m_nVideoWidth);
		}
		for (int i = 0; i < m_nVideoHeight / 2; ++i)
		{
			memcpy((BYTE*)(Rect.pBits) + Rect.Pitch * m_nVideoHeight + (Rect.Pitch / 2) * i, (BYTE*)g_pArrayV + i * m_nVideoWidth / 2, m_nVideoWidth / 2);
		}
		for (int i = 0; i < m_nVideoHeight / 2; ++i)
		{
			memcpy((BYTE*)(Rect.pBits) + Rect.Pitch * m_nVideoHeight + Rect.Pitch * m_nVideoHeight / 4 + (Rect.Pitch / 2) * i, (BYTE*)g_pArrayU + i * m_nVideoWidth / 2, m_nVideoWidth / 2);
		}
		m_pD3D9Surface->UnlockRect();

		g_bReStart = true;
		g_bDecodeFlag = false;

		if (m_nLiveCoreLogProcess)
		{
			CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Direct3D Update One frame.");
		}

		LeaveCriticalSection(&g_csDecode);
	}

}

//----------------------------------------------
// @Function:	CLiveCoreRender()
// @Purpose: CLiveCore��Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveCore::CLiveCoreRender()
{
	IDirect3DSurface9* pD3D9BackBuffer = NULL;
	RECT SrcRect;
	RECT DestRect;

	if (g_bReStart)
	{
		m_pMainGraphics->Begin();

		SrcRect.left = 0;
		SrcRect.top = 0;
		SrcRect.right = m_nVideoWidth;
		SrcRect.bottom = m_nVideoHeight;

		if (m_nLiveCoreWallpaperMode == 0) // ���ģʽ
		{
			DestRect.left = 0;
			DestRect.top = 0;
			DestRect.right = m_nDeskTopWidth;
			DestRect.bottom = m_nDeskTopHeight;
		}
		else if (m_nLiveCoreWallpaperMode == 1) // ��Ӧģʽ
		{
			float fVideoRate = 0.0f;
			float fScreenRate = 0.0f;

			fVideoRate = (float)m_nVideoWidth / (float)m_nVideoHeight;
			fScreenRate = (float)m_nDeskTopWidth / (float)m_nDeskTopHeight;

			if (fVideoRate >= fScreenRate)
			{
				DestRect.left = 0;
				DestRect.right = m_nDeskTopWidth;
				DestRect.top = (int)(((float)m_nDeskTopHeight - (float)m_nDeskTopWidth / fVideoRate) / 2.0f);
				DestRect.bottom = DestRect.top + (int)((float)m_nDeskTopWidth / fVideoRate);
			}
			else
			{
				DestRect.left = (int)(((float)m_nDeskTopWidth - (float)m_nDeskTopHeight * fVideoRate) / 2.0f);
				DestRect.right = DestRect.left + (int)((float)m_nDeskTopHeight * fVideoRate);
				DestRect.top = 0;
				DestRect.bottom = m_nDeskTopHeight;
			}
		}
		else if (m_nLiveCoreWallpaperMode == 2)	// ����ģʽ
		{
			float fVideoRate = 0.0f;
			float fScreenRate = 0.0f;

			fVideoRate = (float)m_nVideoWidth / (float)m_nVideoHeight;
			fScreenRate = (float)m_nDeskTopWidth / (float)m_nDeskTopHeight;

			if (fVideoRate >= fScreenRate)
			{
				DestRect.left = (int)(((float)m_nDeskTopWidth - (float)m_nDeskTopHeight * fVideoRate) / 2.0f);
				DestRect.right = DestRect.left + (int)((float)m_nDeskTopHeight * fVideoRate);
				DestRect.top = 0;
				DestRect.bottom = m_nDeskTopHeight;
			}
			else
			{
				DestRect.left = 0;
				DestRect.right = m_nDeskTopWidth;
				DestRect.top = (int)(((float)m_nDeskTopHeight - (float)m_nDeskTopWidth / fVideoRate) / 2.0f);
				DestRect.bottom = DestRect.top + (int)((float)m_nDeskTopWidth / fVideoRate);
			}
		}
		else if (m_nLiveCoreWallpaperMode == 3)	// ƽ��ģʽ(��δ���)
		{
			DestRect.left = 0;
			DestRect.top = 0;
			DestRect.right = m_nDeskTopWidth;
			DestRect.bottom = m_nDeskTopHeight;
		}
		else if (m_nLiveCoreWallpaperMode == 4)	// ����ģʽ(ԭʼ�ߴ�)
		{
			if (m_nDeskTopWidth >= m_nVideoWidth && m_nDeskTopHeight >= m_nVideoHeight)
			{
				DestRect.left = (m_nDeskTopWidth - m_nVideoWidth) >> 1;
				DestRect.top = (m_nDeskTopHeight - m_nVideoHeight) >> 1;
				DestRect.right = DestRect.left + m_nVideoWidth;
				DestRect.bottom = DestRect.top + m_nVideoHeight;
			}
		}

		m_pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &pD3D9BackBuffer);
		m_pD3D9Device->StretchRect(m_pD3D9Surface, &SrcRect, pD3D9BackBuffer, &DestRect, D3DTEXF_NONE);

		if (m_nLiveCoreShowGraphics != 0)
		{
			m_pMainfps->CalculateFps();
			m_pMainfps->DrawFps(g_hWnd, DX_FONT_FORMAT_TOPRIGHT, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
			m_pMainGraphics->Draw(g_hWnd);
		}

		m_pMainGraphics->End();
		SAFE_RELEASE(pD3D9BackBuffer);

		EnterCriticalSection(&g_csDecode);
		if (m_nLiveCoreLogProcess)
		{
			CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Direct3D Render One frame.");
		}
		LeaveCriticalSection(&g_csDecode);

	}

}

//----------------------------------------------
// @Function:	AnalyzeConfigFile()
// @Purpose: CLiveCore���������ļ�
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
	m_nLiveCoreMode = nValue;																							// LiveCoreģʽ: 0~���ģʽ 1~����ģʽ

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_Graphics", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreShowGraphics = nValue;																					// LiveCore��ʾ: 0~����ʾ�Կ��ͺ�(fps) 1~��ʾ�Կ��ͺ�(fps)

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_GraphicsFont", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreShowGraphicsFont = nValue;																				// LiveCore��ʾ�����С

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreWallpaperMode = nValue;																					// LiveCore��Ļ�ֱ���ģʽ: 0~��� 1~��Ӧ 2~���� 3~ƽ�� 4~����

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Audio", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreWallpaperAudioMode = nValue;																				// LiveCore��Ƶ����ģʽ: 0~��������Ƶ 1~������Ƶ

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORELOGMODE", "LiveCore_Log_Process", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreLogProcess = nValue;																						// LiveCore��־��¼: 0~����¼���� 1~��¼����

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Mode", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	m_nLiveCoreVideoMode = nValue;																						// LiveCore��̬��ֽ��Ƶģʽ: 0~����Ĭ����Ƶ 1~����ѡ����Ƶ

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Name", 0, chArray, MAX_PATH, chFile);
	memcpy_s(m_chLiveCoreVideoName, MAX_PATH, chArray, MAX_PATH);														// LiveCore��̬��ֽĬ����Ƶ����

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Address", 0, chArray, MAX_PATH, chFile);
	memcpy_s(m_chLiveCoreVideoAddress, MAX_PATH, chArray, MAX_PATH);													// LiveCore��̬��ֽ��Ƶ��ַ

	// safe delete object...
	SAFE_DELETE(pFile);
}

//----------------------------------------------
// @Function:	RecordConfigFile()
// @Purpose: CLiveCore��¼�����ļ�
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
// @Purpose: CLiveCore���������Ӵ���
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
// @Purpose: CLiveCore������Ƶ��Ϣ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
BOOL CLiveCore::AnalyzeVideoInfo(HWND hWnd, const char* pVideoPath, int* pWidth, int* pHeight, int* pFreq)
{
	AVFormatContext* pFormatCtx;
	AVCodecContext* pCodecCtx;
	AVCodec* pCodec;

	av_register_all();//ע���������
	pFormatCtx = avformat_alloc_context();//��ʼ��һ��AVFormatContext

	// ���������Ƶ�ļ�
	if (avformat_open_input(&pFormatCtx, pVideoPath, NULL, NULL) != 0)
	{
		MessageBox(hWnd, L"���ļ�ʧ��!", L"����", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// ��ȡ��Ƶ�ļ���Ϣ
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		MessageBox(hWnd, L"�޷���ȡ�ļ���Ϣ!", L"����", MB_OK | MB_ICONERROR);
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
		MessageBox(hWnd, L"δ��ȡ����Ƶ��Ϣ!", L"����", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	pCodecCtx = pFormatCtx->streams[VideoIndex]->codec;

	//���ҽ�����
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		MessageBox(hWnd, L"δ���ҵ�������!", L"����", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//�򿪽�����
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		MessageBox(hWnd, L"�޷��򿪽�����!", L"����", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	*pWidth = pCodecCtx->width;
	*pHeight = pCodecCtx->height;
	*pFreq = pCodecCtx->framerate.num;

	avcodec_close(pCodecCtx);
	avformat_free_context(pFormatCtx);

	return TRUE;
}

//----------------------------------------------
// @Function:	Restart(const char* pStrArr)
// @Purpose: CLiveCore Restart����
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
BOOL CLiveCore::Restart(const char* pStrArr)
{
	BOOL bResult;

	STARTUPINFOA si = { 0 };
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(STARTUPINFOA);
	GetStartupInfoA(&si);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi = { 0 };
	ZeroMemory(&pi, sizeof(pi));

	char chProcessPath[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	GetModuleFileNameA(NULL, chProcessPath, MAX_PATH);
	pTemp = strrchr(chProcessPath, '\\');
	if (pTemp)* pTemp = '\0';
	strcat_s(chProcessPath, "\\");
	strcat_s(chProcessPath, "LiveReStart.exe");

	CHAR chCmdLine[MAX_PATH] = { 0 };
	strcat_s(chCmdLine, chProcessPath);
	strcat_s(chCmdLine, " ");
	strcat_s(chCmdLine, pStrArr);

	bResult = CreateProcessA(chProcessPath, chCmdLine, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	if (bResult)
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	return bResult;
}
