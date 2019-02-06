#include "frameMain.h"
/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameMain.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "Common.h"
#include "defineMain.h"

// CFrameMain类(LiveProject主窗口)
CFrameMain* g_pFrameMain = nullptr;

//----------------------------------------------
// @Function:	GetWindowClassName()
// @Purpose: CFrameMain获取窗口类名
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LPCTSTR CFrameMain::GetWindowClassName() const
{
	return _T("LiveProject");
}

//----------------------------------------------
// @Function:	GetClassStyle()
// @Purpose: CFrameMain获取窗口样式
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
UINT CFrameMain::GetClassStyle() const
{
	return CS_DBLCLKS;
}

//----------------------------------------------
// @Function:	Notify()
// @Purpose: CFrameMain窗口消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_pCloseBtn)
		{
			OnLButtonClickedCloseBtn();
		}
		else if (msg.pSender == m_pRestoreBtn)
		{
			OnLButtonClickedRestoreBtn();
		}
		else if (msg.pSender == m_pMaxBtn)
		{
			OnLButtonClickedMaxBtn();
		}
		else if (msg.pSender == m_pMinBtn)
		{
			OnLButtonClickedMinBtn();
		}
		else if (msg.pSender == m_pOverBtn)
		{
			OnLButtonClickedOverBtn();
		}
		else if (msg.pSender == m_pCancelOverBtn)
		{
			OnLButtonClickedCancelOverBtn();
		}
		else if (msg.pSender == m_pLiveWallAddBtn)
		{
			OnLButtonClickedLiveWallAddBtn();
		}
		else if (msg.pSender == m_pLiveWallModBtn)
		{
			OnLButtonClickedLiveWallModBtn();
		}
		else if (msg.pSender == m_pLiveWallDelBtn)
		{
			OnLButtonClickedLiveWallDelBtn();
		}

	}
	else if (msg.sType == _T("selectchanged"))
	{
		if (msg.pSender == m_pLiveHomeOpt)
		{
			m_pLiveMainTab->SelectItem(1);
		}
		else if (msg.pSender == m_pLiveWallpaperOpt)
		{
			m_pLiveMainTab->SelectItem(2);
		}
		else if (msg.pSender == m_pLiveVideoOpt)
		{
			m_pLiveMainTab->SelectItem(3);
		}
		else if (msg.pSender == m_pLiveAudioOpt)
		{
			m_pLiveMainTab->SelectItem(4);
		}
		else if (msg.pSender == m_pLiveAlbumOpt)
		{
			m_pLiveMainTab->SelectItem(5);
		}
		else if (msg.pSender == m_pLiveShotOpt)
		{
			m_pLiveMainTab->SelectItem(6);
		}
		else if (msg.pSender == m_pLiveAIOpt)
		{
			m_pLiveMainTab->SelectItem(7);
		}
		else if (msg.pSender == m_pSettingsOpt)
		{
			m_pLiveMainTab->SelectItem(8);
		}
		else if (msg.pSender == m_pAboutOpt)
		{
			m_pLiveMainTab->SelectItem(9);
		}

	}

}

//----------------------------------------------
// @Function:	HandleMessage()
// @Purpose: CFrameMain处理窗口消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	switch (uMsg)
	{
	case WM_CREATE:
		lRes = OnCreate(uMsg, wParam, lParam, bHandled);
		break;
	case WM_LBUTTONDOWN:
		lRes = OnLButtonDown(uMsg, wParam, lParam, bHandled);
		break;
	case WM_CLOSE:
		lRes = OnClose(uMsg, wParam, lParam, bHandled);
		break;
	case WM_TIMER:
		lRes = OnTimer(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCACTIVATE:
		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCCALCSIZE:
		lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCPAINT:
		lRes = OnNcPaint(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCHITTEST:
		lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled);
		break;
	case WM_SIZE:
		lRes = OnSize(uMsg, wParam, lParam, bHandled);
		break;
	case WM_GETMINMAXINFO:
		lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled);
		break;
	case WM_SYSCOMMAND:
		lRes = OnSysCommand(uMsg, wParam, lParam, bHandled);
		break;
	/*
	 *	User Message
	 */
	case WM_USER_MESSAGE_MENU:
		lRes = OnUserMessageMenu(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLVIDEO_INSERT:
		lRes = OnUserMessageWallVideoInsert(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLVIDEO_SEARCH:
		lRes = OnUserMessageWallVideoSearch(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLVIDEO_ADDITEM:
		lRes = OnUserMessageWallVideoAddItem(uMsg, wParam, lParam, bHandled);
		break;
	default:
		bHandled = FALSE;
		break;
	}

	if (bHandled)
	{
		return lRes;
	}

	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}

	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

//----------------------------------------------
// @Function:	OnCreate()
// @Purpose: CFrameMain窗口创建消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	m_PaintManager.Init(m_hWnd);

	g_pFrameMain = this;

	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("frame\\frameMain.xml"), (UINT)0, &cb, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");

	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);   // 添加控件等消息响应，这样消息就会传达到duilib的消息循环，我们可以在Notify函数里做消息处理

	ConstructExtra();
	InitMenuShow();
	InitWindowSharp();
	InitControls();
	InitDataBase();
	InitSearch();

	return 0;
}

//----------------------------------------------
// @Function:	OnLButtonDown()
// @Purpose: CFrameMain窗口鼠标左键单击消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = FALSE;
	return 0;
}

//----------------------------------------------
// @Function:	OnClose()
// @Purpose: CFrameMain窗口关闭消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	// 菜单栏小图标删除
	Shell_NotifyIcon(NIM_DELETE, &m_nid);

	// 清理资源

	bHandled = FALSE;
	return 0;
}

//----------------------------------------------
// @Function:	OnTimer()
// @Purpose: CFrameMain窗口定时器触发消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	return LRESULT();
}

//----------------------------------------------
// @Function:	OnNcActivate()
// @Purpose: CFrameMain窗口激活消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	if (::IsIconic(*this))
	{
		bHandled = FALSE;
	}

	return (wParam == 0) ? TRUE : FALSE;
}

//----------------------------------------------
// @Function:	OnNcCalcSize()
// @Purpose: CFrameMain窗口改变尺寸消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	return 0;
}

//----------------------------------------------
// @Function:	OnNcPaint()
// @Purpose: CFrameMain窗口重绘消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	return 0;
}

//----------------------------------------------
// @Function:	OnNcHitTest()
// @Purpose: CFrameMain窗口点击消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	POINT pt; 
	pt.x = GET_X_LPARAM(lParam); 
	pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if (!::IsZoomed(*this)) 
	{
		RECT rcSizeBox = m_PaintManager.GetSizeBox();
		if (pt.y < rcClient.top + rcSizeBox.top) 
		{
			if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
			return HTTOP;
		}
		else if (pt.y > rcClient.bottom - rcSizeBox.bottom) 
		{
			if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
		if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
	}

	RECT rcCaption = m_PaintManager.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right && pt.y >= rcCaption.top && pt.y < rcCaption.bottom) 
	{
		CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 && _tcscmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 && _tcscmp(pControl->GetClass(), DUI_CTR_TEXT) != 0)
		{
			return HTCAPTION;
		}

	}

	return HTCLIENT;
}

//----------------------------------------------
// @Function:	OnSize()
// @Purpose: CFrameMain窗口尺寸改变响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	SIZE szRoundCorner = m_PaintManager.GetRoundCorner();

	if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0)) 
	{
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}

	bHandled = FALSE;
	return 0;
}

//----------------------------------------------
// @Function:	OnGetMinMaxInfo()
// @Purpose: CFrameMain获取窗口最大最小信息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
	lpMMI->ptMaxPosition.x = rcWork.left;
	lpMMI->ptMaxPosition.y = rcWork.top;
	lpMMI->ptMaxSize.x = rcWork.right;
	lpMMI->ptMaxSize.y = rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

//----------------------------------------------
// @Function:	OnSysCommand()
// @Purpose: CFrameMain获取窗口系统消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
	if (wParam == SC_CLOSE) 
	{
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}

	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(*this) != bZoomed) 
	{
		if (!bZoomed) 
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
			if (pControl) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
			if (pControl) pControl->SetVisible(true);
		}
		else 
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
			if (pControl) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
			if (pControl) pControl->SetVisible(false);
		}
	}
	return lRes;
}

//----------------------------------------------
// @Function:	AddOnceWallVideoContext()
// @Purpose: CFrameMain添加一个墙纸内容
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::AddOnceVideoContext(S_WALLVIDEO* pVideoInfo)
{
	CHorizontalLayoutUI* pHorizontal = new CHorizontalLayoutUI();

	// ContainerUI
	CContainerUI* pContainer = new CContainerUI();

	pContainer->SetFloat(true);
	pContainer->SetAttribute(_T("pos"), _T("0,0,0,0"));
	pContainer->SetFixedWidth(192);
	pContainer->SetFixedHeight(167);
	pContainer->SetBkImage(_T("res\\videobk.png"));
	pHorizontal->Add(pContainer);

	// TextUI
	CTextUI* pText = new CTextUI();
	CDuiString strText = _T("");

	USES_CONVERSION;
	strText.Format(_T("%s"), A2T(pVideoInfo->chVideoName));

	pText->SetFloat(true);
	pText->SetAttribute(_T("pos"), _T("0,167,0,0"));
	pText->SetFixedWidth(192);
	pText->SetFixedHeight(24);
	pText->SetFont(2);
	pText->SetAttribute(_T("align"), _T("center"));
	pText->SetTextColor(0xFF363636);
	pText->SetText(strText.GetData());
	pHorizontal->Add(pText);

	m_pLiveWallContextLst->Add(pHorizontal);
}

//----------------------------------------------
// @Function:	GenerateGUID()
// @Purpose: CFrameMain生成GUID
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::GenerateGUID(char * chGUID, size_t nSize)
{
	GUID guid;

	if (S_OK == ::CoCreateGuid(&guid))
	{
		sprintf_s(chGUID, nSize, "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X", guid.Data1
			, guid.Data2
			, guid.Data3
			, guid.Data4[0], guid.Data4[1]
			, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
			, guid.Data4[6], guid.Data4[7]);
	}

}

//----------------------------------------------
// @Function:	GetPaintManager()
// @Purpose: CFrameMain获取绘制句柄
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
CPaintManagerUI & CFrameMain::GetPaintManager()
{
	return m_PaintManager;
}

//----------------------------------------------
// @Function:	ConstructExtra()
// @Purpose: CFrameMain构造函数extra
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::ConstructExtra()
{
	m_hMenu = NULL;
	memset(&m_nid, 0, sizeof(m_nid));
}

//----------------------------------------------
// @Function:	InitMenuShow()
// @Purpose: CFrameMain初始化菜单显示
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::InitMenuShow()
{
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->GetHWND();
	m_nid.uID = IDI_ICON;
	m_nid.hIcon = ::LoadIcon(CPaintManagerUI::GetInstance(), MAKEINTRESOURCE(IDI_ICON));
	m_nid.uCallbackMessage = WM_USER_MESSAGE_MENU;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
	_tcscpy(m_nid.szTip, _T("LiveProject"));
	Shell_NotifyIcon(NIM_ADD, &m_nid);

	m_hMenu = ::CreatePopupMenu();
	AppendMenu(m_hMenu, MF_STRING, ID_MAIN_RESTART, _T("ReStart"));
	AppendMenu(m_hMenu, MF_STRING, ID_MAIN_EXIT, _T("Exit"));

}

//----------------------------------------------
// @Function:	InitWindowSharp()
// @Purpose: CFrameMain初始化窗口形状
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::InitWindowSharp()
{
	// change windows style ~ Areo
	::SetClassLongA(this->GetHWND(), GCL_STYLE, ::GetClassLongA(this->GetHWND(), GCL_STYLE) | CS_DROPSHADOW);
}

//----------------------------------------------
// @Function:	InitControls()
// @Purpose: CFrameMain初始化控件
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::InitControls()
{
	// title buttons
	m_pCloseBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("closebtn")));
	m_pRestoreBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("restorebtn")));
	m_pMaxBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("maxbtn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("minbtn")));
	m_pOverBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("overbtn")));
	m_pCancelOverBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("canceloverbtn")));

	// menu options
	m_pLiveMainTab = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("maintab")));
	m_pLiveHomeOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livehomeopt")));
	m_pLiveWallpaperOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livewallopt")));
	m_pLiveVideoOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livevideoopt")));
	m_pLiveAudioOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("liveaudioopt")));
	m_pLiveAlbumOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livealbumopt")));
	m_pLiveShotOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("liveshotopt")));
	m_pLiveAIOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("liveaiopt")));
	m_pSettingsOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("settingsopt")));
	m_pAboutOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("aboutopt")));

	// livewall menu...
	m_pLiveWallVideoOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livewallvideoopt")));
	m_pLiveWallGraphOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livewallgraphopt")));
	m_pLiveWallAddBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewalladdbtn")));
	m_pLiveWallDelBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewalldelbtn")));
	m_pLiveWallModBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewallmodbtn")));

	// livewall context...
	m_pLiveWallContextLst = static_cast<CTileLayoutUI*>(m_PaintManager.FindControl(_T("livewallcontextlst")));

}

//----------------------------------------------
// @Function:	InitDataBase()
// @Purpose: CFrameMain初始化数据库
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::InitDataBase()
{
	m_pDBWallpaperVideo.Create();
}

//----------------------------------------------
// @Function:	InitSearch()
// @Purpose: CFrameMain初始化查询
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::InitSearch()
{
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_SEARCH, (WPARAM)0, (LPARAM)0);
}

//----------------------------------------------
// @Function:	OnUserMessageMenu()
// @Purpose: CFrameMain菜单栏用户消息
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	switch (lParam)
	{
	case WM_RBUTTONDOWN:
		{
			POINT pt;
			int nRet;

			GetCursorPos(&pt);
			::SetForegroundWindow(this->GetHWND());
			
			nRet = TrackPopupMenu(m_hMenu, TPM_RETURNCMD, pt.x, pt.y, NULL, this->GetHWND(), NULL);
			if (nRet == ID_MAIN_RESTART)
			{

			}
			if (nRet == ID_MAIN_EXIT)
			{
				::PostMessageA(this->GetHWND(), WM_CLOSE, (WPARAM)0, (LPARAM)0);
			}
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			::ShowWindow(this->GetHWND(), SW_SHOW);
		}
		break;
	default:
		break;
	}

	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageWallVideoInsert()
// @Purpose: CFrameMain添加视频数据信息
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageWallVideoInsert(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	S_WALLVIDEO* pMsg = reinterpret_cast<S_WALLVIDEO*>(wParam);

	// add video name...
	char* pTemp = NULL;
	char* pTemp2 = NULL;

	pTemp = strrchr(pMsg->chVideoPath, '\\');
	if (pTemp != NULL)
	{
		pTemp2 = strrchr(pTemp, '.');
		if (pTemp2 != NULL)
		{
			char* pArray = pMsg->chVideoName;

			for (char* point = ++pTemp; point != pTemp2; )
			{
				*pArray++ = *point++;
			}
		}
		else
		{
			strcpy_s(pMsg->chVideoName, ++pTemp);
		}
	}
	else
	{
		strcpy_s(pMsg->chVideoName, pMsg->chVideoPath);
	}

	// add video id...
	GenerateGUID(pMsg->chVideoID, sizeof(pMsg->chVideoID));

	// insert data...
	m_pDBWallpaperVideo.Insert(pMsg);

	// search data...
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_SEARCH, (WPARAM)0, (LPARAM)0);

	// delete resources...
	SAFE_DELETE(pMsg);

	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageWallVideoSearch()
// @Purpose: CFrameMain查询视频数据信息
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageWallVideoSearch(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	// clear vector...
	m_vecWallVideoInfo.clear();

	// select data...
	m_pDBWallpaperVideo.Select(OnSearchWallVideoCallback);

	// clear context...
	m_pLiveWallContextLst->RemoveAll();

	// new thread show...
	HANDLE hThread = NULL;
	DWORD dwThreadID = 0;

	hThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(&CFrameMain::OnSearchWallVideoProcess), NULL, 0, &dwThreadID);
	::CloseHandle(hThread);

	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageWallVideoAddItem()
// @Purpose: CFrameMain列表添加一条视频信息
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageWallVideoAddItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	S_WALLVIDEO* pMsg = reinterpret_cast<S_WALLVIDEO*>(wParam);
	AddOnceVideoContext(pMsg);
	return 0;
}

//----------------------------------------------
// @Function:	OnSearchWallVideoProcess()
// @Purpose: CFrameMain查询视频数据线程
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
DWORD CFrameMain::OnSearchWallVideoProcess(LPVOID lpParameter)
{
	for (auto iter = g_pFrameMain->m_vecWallVideoInfo.begin(); iter != g_pFrameMain->m_vecWallVideoInfo.end(); ++iter)
	{
		::PostMessageA(g_pFrameMain->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_ADDITEM, (WPARAM)((LPVOID)(&(*iter))), (LPARAM)0);
	}

	return 0;
}

//----------------------------------------------
// @Function:	OnSearchWallVideoCallback()
// @Purpose: CFrameMain查询视频数据回调函数
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
int CFrameMain::OnSearchWallVideoCallback(void * data, int argc, char ** argv, char ** azColName)
{
	S_WALLVIDEO sVideoInfo = { 0 };

	sVideoInfo.nNumber = atoi(*argv);
	sVideoInfo.nReserved = atoi(*(argv + 1));
	strcpy_s(sVideoInfo.chVideoName, *(argv + 2));
	strcpy_s(sVideoInfo.chVideoAuthor, *(argv + 3));
	strcpy_s(sVideoInfo.chVideoTime, *(argv + 4));
	strcpy_s(sVideoInfo.chVideoID, *(argv + 5));
	strcpy_s(sVideoInfo.chVideoPath, *(argv + 6));
	strcpy_s(sVideoInfo.chReserved1, *(argv + 7));
	strcpy_s(sVideoInfo.chReserved2, *(argv + 8));
	strcpy_s(sVideoInfo.chVideoShot, *(argv + 9));

	g_pFrameMain->m_vecWallVideoInfo.push_back(sVideoInfo);

	return 0;
}

//----------------------------------------------
// @Function:	OnLButtonClickedOverBtn()
// @Purpose: CFrameMain鼠标左键单击置顶按钮
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedOverBtn()
{
	::SetWindowPos(this->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	m_pOverBtn->SetVisible(false);
	m_pCancelOverBtn->SetVisible(true);
}

//----------------------------------------------
// @Function:	OnLButtonClickedCancelOverBtn()
// @Purpose: CFrameMain鼠标左键单击取消置顶按钮
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedCancelOverBtn()
{
	::SetWindowPos(this->GetHWND(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	m_pOverBtn->SetVisible(true);
	m_pCancelOverBtn->SetVisible(false);
}

//----------------------------------------------
// @Function:	OnLButtonClickedMinBtn()
// @Purpose: CFrameMain鼠标左键单击最小化按钮
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedMinBtn()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

//----------------------------------------------
// @Function:	OnLButtonClickedMaxBtn()
// @Purpose: CFrameMain鼠标左键单击最大化按钮
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedMaxBtn()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
}

//----------------------------------------------
// @Function:	OnLButtonClickedRestoreBtn()
// @Purpose: CFrameMain鼠标左键单击还原按钮
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedRestoreBtn()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
}

//----------------------------------------------
// @Function:	OnLButtonClickedCloseBtn()
// @Purpose: CFrameMain鼠标左键单击关闭按钮
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedCloseBtn()
{
	//::PostMessageA(this->GetHWND(), WM_CLOSE, (WPARAM)0, (LPARAM)0);
	::ShowWindow(this->GetHWND(), SW_HIDE);
}

//----------------------------------------------
// @Function:	OnLButtonClickedLiveWallAddBtn()
// @Purpose: CFrameMain鼠标左键单击添加视频按钮
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallAddBtn()
{
	OPENFILENAME file;
	WCHAR strfile[MAX_PATH] = { 0 };

	ZeroMemory(&file, sizeof(OPENFILENAME));

	file.lStructSize = sizeof(OPENFILENAME);
	file.lpstrFilter = _T(	"所有文件\0*.*\0" \
							"MP4\0*.mp4\0" \
							"WMV\0*.wmv\0" \
							"MOV\0*.mov\0" \
							"AVI\0*.avi\0" \
							"ASF\0*.asf\0" \
							"RMVB\0*.rmvb\0" \
							"\0");
	file.nFilterIndex = 1;
	file.lpstrFile = strfile;
	file.nMaxFile = sizeof(strfile);
	file.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

	if (GetOpenFileName(&file))
	{
		S_WALLVIDEO* pVideoInfo = new S_WALLVIDEO();

		USES_CONVERSION;
		memset(pVideoInfo, 0, sizeof(S_WALLVIDEO));
		strcpy_s(pVideoInfo->chVideoPath, T2A(strfile));
		::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_INSERT, (WPARAM)((LPVOID)(pVideoInfo)), (LPARAM)0);
	}

}

//----------------------------------------------
// @Function:	OnLButtonClickedLiveWallModBtn()
// @Purpose: CFrameMain鼠标左键单击修改视频按钮
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallModBtn()
{
}

//----------------------------------------------
// @Function:	OnLButtonClickedLiveWallDelBtn()
// @Purpose: CFrameMain鼠标左键单击删除视频按钮
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallDelBtn()
{
}
