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
		else if (msg.pSender == m_pLiveWallSearchBtn)
		{
			OnLButtonClickedLiveWallSearchBtn();
		}
		else if (msg.pSender == m_pLiveWallPreBtn)
		{
			OnLButtonClickedLiveWallPreBtn();
		}
		else if (msg.pSender == m_pLiveWallNextBtn)
		{
			OnLButtonClickedLiveWallNextBtn();
		}
		else if (msg.pSender == m_pLiveWallPlayBtn)
		{
			OnLButtonClickedLiveWallPlayBtn();
		}
		else if (msg.pSender == m_pLiveWallPauseBtn)
		{
			OnLButtonClickedLiveWallPauseBtn();
		}
		else if (msg.pSender == m_pLiveWallStopBtn)
		{
			OnLButtonClickedLiveWallStopBtn();
		}
		else if (msg.pSender == m_pLiveWallRandomBtn)
		{
			OnLButtonClickedLiveWallRandomBtn();
		}
		else if (msg.pSender == m_pLiveWallLoopBtn)
		{
			OnLButtonClickedLiveWallLoopBtn();
		}
		else if (msg.pSender == m_pLiveWallRepeatBtn)
		{
			OnLButtonClickedLiveWallRepeatBtn();
		}
		else if (msg.pSender == m_pLiveWallOrderBtn)
		{
			OnLButtonClickedLiveWallOrderBtn();
		}
		else if (msg.pSender == m_pLiveWallControlBtn)
		{
			OnLButtonClickedLiveWallControlBtn();
		}
		else
		{
			OnLButtonClickedOtherEvent(msg.pSender);
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
		else if (msg.pSender == m_pLiveWallVideoOpt)
		{
			OnLButtonClickedLiveWallVideoOption();
		}
		else if (msg.pSender == m_pLiveWallGraphOpt)
		{
			OnLButtonClickedLiveWallGraphOption();
		}
		else if (msg.pSender == m_pLiveSettingHomeOpt)
		{
			OnLButtonClickedLiveSettingHomeOption();
		}
		else if (msg.pSender == m_pLiveSettingWallOpt)
		{
			OnLButtonClickedLiveSettingWallOption();
		}
		else if (msg.pSender == m_pLiveSettingVideoOpt)
		{
			OnLButtonClickedLiveSettingVideoOption();
		}
		else if (msg.pSender == m_pLiveSettingAudioOpt)
		{
			OnLButtonClickedLiveSettingAudioOption();
		}
		else if (msg.pSender == m_pLiveSettingAlbumOpt)
		{
			OnLButtonClickedLiveSettingAlbumOption();
		}
		else if (msg.pSender == m_pLiveSettingShotOpt)
		{
			OnLButtonClickedLiveSettingShotOption();
		}
		else if (msg.pSender == m_pLiveSettingAIOpt)
		{
			OnLButtonClickedLiveSettingAIOption();
		}

	}
	else if (msg.sType == _T("textchanged"))
	{
		if (msg.pSender == m_pLiveWallSearchEdt)
		{
			OnLButtonClickedLiveWallSearchBtn();
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
	case WM_USER_MESSAGE_WALLVIDEO_RESTART:
		lRes = OnUserMessageWallVideoReStart(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLVIDEO_INSERT:
		lRes = OnUserMessageWallVideoInsert(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLVIDEO_DELETE:
		lRes = OnUserMessageWallVideoDelete(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLVIDEO_SEARCH:
		lRes = OnUserMessageWallVideoSearch(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLVIDEO_ADDITEM:
		lRes = OnUserMessageWallVideoAddItem(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLVIDEO_ADDSHOT:
		lRes = OnUserMessageWallVideoAddShot(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLGRAPH_INSERT:
		lRes = OnUserMessageWallGraphInsert(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLGRAPH_DELETE:
		lRes = OnUserMessageWallGraphDelete(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLGRAPH_SEARCH:
		lRes = OnUserMessageWallGraphSearch(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLGRAPH_ADDITEM:
		lRes = OnUserMessageWallGraphAddItem(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_WALLGRAPH_ADDSHOT:
		lRes = OnUserMessageWallGraphAddShot(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_SETTINGHOME_SEARCH:
		lRes = OnUserMessageSettingHomeSearch(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_SETTINGWALL_SEARCH:
		lRes = OnUserMessageSettingWallSearch(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_SETTINGVIDEO_SEARCH:
		lRes = OnUserMessageSettingVideoSearch(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_SETTINGAUDIO_SEARCH:
		lRes = OnUserMessageSettingAudioSearch(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_SETTINGALBUM_SEARCH:
		lRes = OnUserMessageSettingAlbumSearch(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_SETTINGSHOT_SEARCH:
		lRes = OnUserMessageSettingShotSearch(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_SETTINGAI_SEARCH:
		lRes = OnUserMessageSettingAISearch(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_SETTINGWALL_GETCONFIG:
		lRes = OnUserMessageSettingWallGetConfig(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_MESSAGE_SETTINGWALL_SETCONFIG:
		lRes = OnUserMessageSettingWallSetConfig(uMsg, wParam, lParam, bHandled);
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
	RecordConfigFile();
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

	pContainer->SetName(_T("videobk"));
	pContainer->SetFloat(true);
	pContainer->SetAttribute(_T("pos"), _T("0,0,0,0"));
	pContainer->SetFixedWidth(192);
	pContainer->SetFixedHeight(167);
	pContainer->SetBkImage(_T("res\\videobk.png"));
	pHorizontal->Add(pContainer);

	// ButtonUI -- Play
	CButtonUI* pPlayBtn = new CButtonUI();

	pPlayBtn->SetName(_T("play"));
	pPlayBtn->SetFloat(true);
	pPlayBtn->SetAttribute(_T("pos"), _T("81,61,0,0"));
	pPlayBtn->SetFixedWidth(24);
	pPlayBtn->SetFixedHeight(24);
	pPlayBtn->SetVisible(true);
	pPlayBtn->SetAttribute(_T("normalimage"), _T("file='res\\playbuttons.png' source='0,0,24,24'"));
	pPlayBtn->SetAttribute(_T("hotimage"), _T("file='res\\playbuttons.png' source='0,24,24,48'"));
	pPlayBtn->SetAttribute(_T("pushedimage"), _T("file='res\\playbuttons.png' source='0,48,24,72'"));
	pHorizontal->Add(pPlayBtn);

	// ButtonUI -- UnChecked
	CButtonUI* pUnCheckedBtn = new CButtonUI();

	pUnCheckedBtn->SetName(_T("unchecked"));
	pUnCheckedBtn->SetFloat(true);
	pUnCheckedBtn->SetAttribute(_T("pos"), _T("2,0,0,0"));
	pUnCheckedBtn->SetFixedWidth(24);
	pUnCheckedBtn->SetFixedHeight(24);
	pUnCheckedBtn->SetVisible(false);
	pUnCheckedBtn->SetAttribute(_T("normalimage"), _T("file='res\\uncheckedbuttons.png' source='0,0,24,24'"));
	pUnCheckedBtn->SetAttribute(_T("hotimage"), _T("file='res\\uncheckedbuttons.png' source='0,24,24,48'"));
	pUnCheckedBtn->SetAttribute(_T("pushedimage"), _T("file='res\\uncheckedbuttons.png' source='0,48,24,72'"));
	pHorizontal->Add(pUnCheckedBtn);

	// ButtonUI -- Checked
	CButtonUI* pCheckedBtn = new CButtonUI();

	pCheckedBtn->SetName(_T("checked"));
	pCheckedBtn->SetFloat(true);
	pCheckedBtn->SetAttribute(_T("pos"), _T("2,0,0,0"));
	pCheckedBtn->SetFixedWidth(24);
	pCheckedBtn->SetFixedHeight(24);
	pCheckedBtn->SetVisible(false);
	pCheckedBtn->SetAttribute(_T("normalimage"), _T("file='res\\checkedbuttons.png' source='0,0,24,24'"));
	pCheckedBtn->SetAttribute(_T("hotimage"), _T("file='res\\checkedbuttons.png' source='0,24,24,48'"));
	pCheckedBtn->SetAttribute(_T("pushedimage"), _T("file='res\\checkedbuttons.png' source='0,48,24,72'"));
	pHorizontal->Add(pCheckedBtn);

	// TextUI
	CTextUI* pText = new CTextUI();
	CDuiString strText = _T("");

	USES_CONVERSION;
	strText.Format(_T("%s"), A2T(pVideoInfo->chVideoName));

	pText->SetName(_T("videoname"));
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
// @Function:	AddOnceVideoShotCut()
// @Purpose: CFrameMain添加一个墙纸快照
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::AddOnceVideoShotCut(S_WALLVIDEO* pVideoInfo)
{
	char chVideoPath[256] = { 0 };

	CPlumPath::PlumPathGetLocalPathA(chVideoPath, sizeof(chVideoPath));
	strcat_s(chVideoPath, "\\data\\");
	strcat_s(chVideoPath, pVideoInfo->chVideoName);
	strcat_s(chVideoPath, ".jpg");

	for (int i = 0; i < m_pLiveWallContextLst->GetCount(); ++i)
	{
		CHorizontalLayoutUI* pHorizontal = static_cast<CHorizontalLayoutUI*>(m_pLiveWallContextLst->GetItemAt(i));

		if (pHorizontal != NULL)
		{
			CContainerUI* pContainer = static_cast<CContainerUI*>(pHorizontal->FindSubControl(_T("videobk")));		// find video back image...
			CTextUI* pText = static_cast<CTextUI*>(pHorizontal->FindSubControl(_T("videoname")));					// find video name...

			USES_CONVERSION;

			if (!strcmp(T2A(pText->GetText().GetData()), pVideoInfo->chVideoName))
			{
				pContainer->SetBkImage(A2T(chVideoPath));
			}
		}
	}

}

//----------------------------------------------
// @Function:	PlayOnceVideoContext()
// @Purpose: CFrameMain播放一个墙纸内容
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::PlayOnceVideoContext(S_WALLVIDEO * pVideoInfo)
{
}

//----------------------------------------------
// @Function:	StopOnceVideoContext()
// @Purpose: CFrameMain停止一个墙纸内容
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::StopOnceVideoContext()
{
}

//----------------------------------------------
// @Function:	AddOnceGraphContext()
// @Purpose: CFrameMain添加一个图形内容
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::AddOnceGraphContext(S_WALLGRAPH* pGraphInfo)
{
	CHorizontalLayoutUI* pHorizontal = new CHorizontalLayoutUI();

	// ContainerUI
	CContainerUI* pContainer = new CContainerUI();

	pContainer->SetName(_T("graphbk"));
	pContainer->SetFloat(true);
	pContainer->SetAttribute(_T("pos"), _T("0,0,0,0"));
	pContainer->SetFixedWidth(192);
	pContainer->SetFixedHeight(167);
	pContainer->SetBkImage(_T("res\\imagebk.png"));
	pHorizontal->Add(pContainer);

	// ButtonUI -- Play
	CButtonUI* pPlayBtn = new CButtonUI();

	pPlayBtn->SetName(_T("play"));
	pPlayBtn->SetFloat(true);
	pPlayBtn->SetAttribute(_T("pos"), _T("81,61,0,0"));
	pPlayBtn->SetFixedWidth(24);
	pPlayBtn->SetFixedHeight(24);
	pPlayBtn->SetVisible(true);
	pPlayBtn->SetAttribute(_T("normalimage"), _T("file='res\\playbuttons.png' source='0,0,24,24'"));
	pPlayBtn->SetAttribute(_T("hotimage"), _T("file='res\\playbuttons.png' source='0,24,24,48'"));
	pPlayBtn->SetAttribute(_T("pushedimage"), _T("file='res\\playbuttons.png' source='0,48,24,72'"));
	pHorizontal->Add(pPlayBtn);

	// ButtonUI -- UnChecked
	CButtonUI* pUnCheckedBtn = new CButtonUI();

	pUnCheckedBtn->SetName(_T("unchecked"));
	pUnCheckedBtn->SetFloat(true);
	pUnCheckedBtn->SetAttribute(_T("pos"), _T("2,0,0,0"));
	pUnCheckedBtn->SetFixedWidth(24);
	pUnCheckedBtn->SetFixedHeight(24);
	pUnCheckedBtn->SetVisible(false);
	pUnCheckedBtn->SetAttribute(_T("normalimage"), _T("file='res\\uncheckedbuttons.png' source='0,0,24,24'"));
	pUnCheckedBtn->SetAttribute(_T("hotimage"), _T("file='res\\uncheckedbuttons.png' source='0,24,24,48'"));
	pUnCheckedBtn->SetAttribute(_T("pushedimage"), _T("file='res\\uncheckedbuttons.png' source='0,48,24,72'"));
	pHorizontal->Add(pUnCheckedBtn);

	// ButtonUI -- Checked
	CButtonUI* pCheckedBtn = new CButtonUI();

	pCheckedBtn->SetName(_T("checked"));
	pCheckedBtn->SetFloat(true);
	pCheckedBtn->SetAttribute(_T("pos"), _T("2,0,0,0"));
	pCheckedBtn->SetFixedWidth(24);
	pCheckedBtn->SetFixedHeight(24);
	pCheckedBtn->SetVisible(false);
	pCheckedBtn->SetAttribute(_T("normalimage"), _T("file='res\\checkedbuttons.png' source='0,0,24,24'"));
	pCheckedBtn->SetAttribute(_T("hotimage"), _T("file='res\\checkedbuttons.png' source='0,24,24,48'"));
	pCheckedBtn->SetAttribute(_T("pushedimage"), _T("file='res\\checkedbuttons.png' source='0,48,24,72'"));
	pHorizontal->Add(pCheckedBtn);

	// TextUI
	CTextUI* pText = new CTextUI();
	CDuiString strText = _T("");

	USES_CONVERSION;
	strText.Format(_T("%s"), A2T(pGraphInfo->chGraphName));

	pText->SetName(_T("graphname"));
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
// @Function:	AddOnceGraphShotcut()
// @Purpose: CFrameMain添加一个图形快照
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::AddOnceGraphShotcut(S_WALLGRAPH* pGraphInfo)
{
}

//----------------------------------------------
// @Function:	PlayOnceGraphContext()
// @Purpose: CFrameMain播放一个图形内容
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::PlayOnceGraphContext(S_WALLGRAPH* pGraphInfo)
{
}

//----------------------------------------------
// @Function:	StopOnceGraphContext()
// @Purpose: CFrameMain停止一个图形内容
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::StopOnceGraphContext()
{
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
// @Function:	ReStartProcess()
// @Purpose: CFrameMain进程ReStart
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
BOOL CFrameMain::ReStartProcess(const char * pStrArr)
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
	if (pTemp) *pTemp = '\0';
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

//------------------------------------------------------------
// @Function:	RecordVideoConfigFile(S_WALLVIDEO* pVideoInfo)
// @Purpose: CFrameMain进程记录视频配置文件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------
void CFrameMain::RecordVideoConfigFile(S_WALLVIDEO* pVideoInfo)
{
	char chFile[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	// record file path...
	CPlumFile* pFile = new CPlumFile();
	pFile->PlumFileGetModuleFileNameA(chFile, MAX_PATH);

	pTemp = strrchr(chFile, '\\');
	if (pTemp)* pTemp = '\0';
	strcat_s(chFile, "\\config\\LiveCore.cfg");

	// analyze config info...
	char chArray[MAX_PATH] = { 0 };
	int nValue = 0;

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWINDOW", "LiveCore_Window_Handle", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	::PostMessageA((HWND)nValue, WM_CLOSE, (WPARAM)0, (LPARAM)0);

	// record config info...
	if (pVideoInfo != nullptr)
	{
		WritePrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Address", pVideoInfo->chVideoPath, chFile);
	}

	// safe delete object...
	SAFE_DELETE(pFile);
}

//----------------------------------------------
// @Function:	ShowLiveWallPlayStates()
// @Purpose: CFrameMain播放状态按钮图形显示
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::ShowLiveWallPlayStates(E_WALLPLAYSTATES ePlayStates)
{
	switch (ePlayStates)
	{
	case Play:
		m_pLiveWallPlayBtn->SetVisible(true);
		m_pLiveWallPauseBtn->SetVisible(false);
		break;
	case Pause:
		m_pLiveWallPlayBtn->SetVisible(false);
		m_pLiveWallPauseBtn->SetVisible(true);
		break;
	default:
		break;
	}

}

//----------------------------------------------
// @Function:	ShowLiveWallPlayMode()
// @Purpose: CFrameMain播放模式按钮图形显示
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::ShowLiveWallPlayMode(E_WALLPLAYMODE ePlayMode)
{
	switch (ePlayMode)
	{
	case Random:
		m_pLiveWallRandomBtn->SetVisible(true);
		m_pLiveWallLoopBtn->SetVisible(false);
		m_pLiveWallRepeatBtn->SetVisible(false);
		m_pLiveWallOrderBtn->SetVisible(false);
		break;
	case Loop:
		m_pLiveWallRandomBtn->SetVisible(false);
		m_pLiveWallLoopBtn->SetVisible(true);
		m_pLiveWallRepeatBtn->SetVisible(false);
		m_pLiveWallOrderBtn->SetVisible(false);
		break;
	case Repeat:
		m_pLiveWallRandomBtn->SetVisible(false);
		m_pLiveWallLoopBtn->SetVisible(false);
		m_pLiveWallRepeatBtn->SetVisible(true);
		m_pLiveWallOrderBtn->SetVisible(false);
		break;
	case Order:
		m_pLiveWallRandomBtn->SetVisible(false);
		m_pLiveWallLoopBtn->SetVisible(false);
		m_pLiveWallRepeatBtn->SetVisible(false);
		m_pLiveWallOrderBtn->SetVisible(true);
		break;
	default:
		break;
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

	m_bWallVideoMod = false;
	m_bWallGraphMod = false;
	m_bWallShowControl = false;

	m_ePlayStates = Play;
	m_ePlayMode = Random;
	m_nPlayNo = 0;

	::srand((unsigned int)time(NULL));
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
	m_pLiveWallSearchEdt = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("livewallsearchedt")));
	m_pLiveWallSearchBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewallsearchbtn")));

	// livewall context...
	m_pLiveWallContextLst = static_cast<CTileLayoutUI*>(m_PaintManager.FindControl(_T("livewallcontextlst")));

	// livewall control...
	m_pLiveWallPreBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewallprebtn")));
	m_pLiveWallNextBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewallnextbtn")));
	m_pLiveWallPlayBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewallplaybtn")));
	m_pLiveWallPauseBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewallpausebtn")));
	m_pLiveWallStopBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewallstopbtn")));
	m_pLiveWallRandomBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewallrandombtn")));
	m_pLiveWallLoopBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewallloopbtn")));
	m_pLiveWallRepeatBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewallrepeatbtn")));
	m_pLiveWallOrderBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewallorderbtn")));
	m_pLiveWallControlBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("livewallcontrolbtn")));

	// livesetting menu...
	m_pLiveSettingHomeOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livesettinghomeopt")));
	m_pLiveSettingWallOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livesettingwallpaperopt")));
	m_pLiveSettingVideoOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livesettingvideoopt")));
	m_pLiveSettingAudioOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livesettingaudioopt")));
	m_pLiveSettingAlbumOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livesettingalbumopt")));
	m_pLiveSettingShotOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livesettingshotopt")));
	m_pLiveSettingAIOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("livesettingaiopt")));

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
	m_pDBWallpaperGraph.Create();
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
// @Function:	AnalyzeConfigFile()
// @Purpose: CFrameMain分析配置文件
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::AnalyzeConfigFile()
{
}

//----------------------------------------------
// @Function:	RecordConfigFile()
// @Purpose: CFrameMain记录配置文件
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::RecordConfigFile()
{
	char chFile[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	// analyze file path...
	CPlumFile* pFile = new CPlumFile();
	pFile->PlumFileGetModuleFileNameA(chFile, MAX_PATH);

	pTemp = strrchr(chFile, '\\');
	if (pTemp)* pTemp = '\0';
	strcat_s(chFile, "\\config\\LiveProject.cfg");

	// record window handle...
	char chArrValue[MAX_PATH] = { 0 };
	memset(chArrValue, 0, MAX_PATH);
	itoa((int)(this->GetHWND()), chArrValue, 10);
	WritePrivateProfileStringA("LIVEPROJECTWINDOW", "LiveProject_Window_Handle", chArrValue, chFile);

	// safe delete object...
	SAFE_DELETE(pFile);
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
				ReStartProcess("LiveProject.exe");
				::PostMessageA(this->GetHWND(), WM_CLOSE, (WPARAM)0, (LPARAM)0);
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

//-----------------------------------------------------------------------
// @Function:	OnUserMessageWallVideoReStart()
// @Purpose: CFrameMain关闭WallVideo消息(LiveWallpaperCore -> LiveProjec)
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
LRESULT CFrameMain::OnUserMessageWallVideoReStart(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nSize = 0;
	int number = 0;

	nSize = m_vecWallVideoInfo.size();
	if (nSize == 0)
	{
		return -1;
	}

	switch (m_ePlayMode)
	{
	case Random:
	{
		number = rand() % nSize;
		RecordVideoConfigFile(&m_vecWallVideoInfo.at(number));
		break;
	}
	case Loop:
	{
		if (wParam == 1)
		{
			number = m_nPlayNo - 1;
			if (number < 0)
			{
				number = nSize - 1;
			}
			m_nPlayNo = number;
			RecordVideoConfigFile(&m_vecWallVideoInfo.at(number));
		}
		else
		{
			number = m_nPlayNo + 1;
			if (number >= nSize)
			{
				number = 0;
			}
			m_nPlayNo = number;
			RecordVideoConfigFile(&m_vecWallVideoInfo.at(number));
		}
		break;
	}
	case Repeat:
	{
		number = m_nPlayNo;
		RecordVideoConfigFile(&m_vecWallVideoInfo.at(number));
		break;
	}
	case Order:
	{
		if (wParam == 1)
		{
			number = m_nPlayNo - 1;
			if (number < 0)
			{
				number = 0;
				m_nPlayNo = number;
				RecordVideoConfigFile(&m_vecWallVideoInfo.at(number));
				goto EXIT;
			}
			m_nPlayNo = number;
			RecordVideoConfigFile(&m_vecWallVideoInfo.at(number));
		}
		else
		{
			number = m_nPlayNo + 1;
			if (number >= nSize)
			{
				number = nSize - 1;
				m_nPlayNo = number;
				RecordVideoConfigFile(&m_vecWallVideoInfo.at(number));
				goto EXIT;
			}
			m_nPlayNo = number;
			RecordVideoConfigFile(&m_vecWallVideoInfo.at(number));
		}
		break;
	}
	default:
		break;
	}

	ReStartProcess("LiveWallpaperCore.exe");

EXIT:
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
// @Function:	OnUserMessageWallVideoDelete()
// @Purpose: CFrameMain删除视频数据信息
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageWallVideoDelete(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	S_WALLVIDEO* pMsg = reinterpret_cast<S_WALLVIDEO*>(wParam);

	// delete data...
	m_pDBWallpaperVideo.Delete(pMsg->chVideoPath);

	// search data...
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_SEARCH, (WPARAM)0, (LPARAM)0);

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
	CDuiString csSearch = _T("");

	USES_CONVERSION;
	csSearch = m_pLiveWallSearchEdt->GetText();
	m_pDBWallpaperVideo.Select(OnSearchWallVideoCallback, T2A(csSearch.GetData()));

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
// @Function:	OnUserMessageWallVideoAddShot()
// @Purpose: CFrameMain列表添加一条视频快照
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageWallVideoAddShot(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	S_WALLVIDEO* pMsg = reinterpret_cast<S_WALLVIDEO*>(wParam);
	AddOnceVideoShotCut(pMsg);
	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageWallGraphInsert()
// @Purpose: CFrameMain添加图形数据信息
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageWallGraphInsert(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	S_WALLGRAPH* pMsg = reinterpret_cast<S_WALLGRAPH*>(wParam);

	// add graph name...
	char* pTemp = NULL;
	char* pTemp2 = NULL;

	pTemp = strrchr(pMsg->chGraphPath, '\\');
	if (pTemp != NULL)
	{
		pTemp2 = strrchr(pTemp, '.');
		if (pTemp2 != NULL)
		{
			char* pArray = pMsg->chGraphName;

			for (char* point = ++pTemp; point != pTemp2; )
			{
				*pArray++ = *point++;
			}
		}
		else
		{
			strcpy_s(pMsg->chGraphName, ++pTemp);
		}
	}
	else
	{
		strcpy_s(pMsg->chGraphName, pMsg->chGraphPath);
	}

	// add graph id...
	GenerateGUID(pMsg->chGraphID, sizeof(pMsg->chGraphID));

	// insert data...
	m_pDBWallpaperGraph.Insert(pMsg);

	// search data...
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLGRAPH_SEARCH, (WPARAM)0, (LPARAM)0);

	// delete resources...
	SAFE_DELETE(pMsg);

	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageWallGraphDelete()
// @Purpose: CFrameMain删除图形数据信息
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageWallGraphDelete(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	S_WALLGRAPH* pMsg = reinterpret_cast<S_WALLGRAPH*>(wParam);

	// delete data...
	m_pDBWallpaperGraph.Delete(pMsg->chGraphPath);

	// search data...
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLGRAPH_SEARCH, (WPARAM)0, (LPARAM)0);

	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageWallGraphSearch()
// @Purpose: CFrameMain查询图形数据信息
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageWallGraphSearch(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// clear vector...
	m_vecWallGraphInfo.clear();

	// select data...
	CDuiString csSearch = _T("");

	USES_CONVERSION;
	csSearch = m_pLiveWallSearchEdt->GetText();
	m_pDBWallpaperGraph.Select(OnSearchWallGraphCallback, T2A(csSearch.GetData()));

	// clear context...
	m_pLiveWallContextLst->RemoveAll();

	// new thread show...
	HANDLE hThread = NULL;
	DWORD dwThreadID = 0;

	hThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(&CFrameMain::OnSearchWallGraphProcess), NULL, 0, &dwThreadID);
	::CloseHandle(hThread);

	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageWallGraphAddItem()
// @Purpose: CFrameMain添加一条图形数据信息
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageWallGraphAddItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	S_WALLGRAPH* pMsg = reinterpret_cast<S_WALLGRAPH*>(wParam);
	AddOnceGraphContext(pMsg);
	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageWallGraphAddShot()
// @Purpose: CFrameMain添加图形快照
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageWallGraphAddShot(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	S_WALLGRAPH* pMsg = reinterpret_cast<S_WALLGRAPH*>(wParam);
	AddOnceGraphShotcut(pMsg);
	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageSettingHomeSearch()
// @Purpose: CFrameMain设置主页响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageSettingHomeSearch(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CVerticalLayoutUI* pVertical = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("livesettingcontent")));
	if (pVertical != NULL)
	{
		pVertical->RemoveAll();
	}
	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageSettingWallSearch()
// @Purpose: CFrameMain设置壁纸响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageSettingWallSearch(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CVerticalLayoutUI* pVertical = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("livesettingcontent")));
	if (pVertical != NULL)
	{
		pVertical->RemoveAll();

		// ContainerUI -- Title
		CContainerUI* pContainer = new CContainerUI();

		pContainer->SetName(_T("title"));
		pContainer->SetFloat(true);
		pContainer->SetAttribute(_T("pos"), _T("50,20,0,0"));
		pContainer->SetFixedWidth(200);
		pContainer->SetFixedHeight(24);
		pContainer->SetBkImage(_T("res\\livewallcfgtitle.png"));
		pVertical->Add(pContainer);

		// ButtonUI -- Save
		CButtonUI* pSaveB = new CButtonUI();

		pSaveB->SetName(_T("save"));
		pSaveB->SetFloat(true);
		pSaveB->SetAttribute(_T("pos"), _T("280,20,0,0"));
		pSaveB->SetFixedWidth(24);
		pSaveB->SetFixedHeight(24);
		pSaveB->SetVisible(true);
		pSaveB->SetToolTip(_T("save"));
		pSaveB->SetAttribute(_T("normalimage"), _T("file='res\\savebuttons.png' source='0,0,24,24'"));
		pSaveB->SetAttribute(_T("hotimage"), _T("file='res\\savebuttons.png' source='0,24,24,48'"));
		pSaveB->SetAttribute(_T("pushedimage"), _T("file='res\\savebuttons.png' source='0,48,24,72'"));
		pVertical->Add(pSaveB);

		// ButtonUI -- Refresh
		CButtonUI* pRefreshB = new CButtonUI();

		pRefreshB->SetName(_T("refresh"));
		pRefreshB->SetFloat(true);
		pRefreshB->SetAttribute(_T("pos"), _T("310,20,0,0"));
		pRefreshB->SetFixedWidth(24);
		pRefreshB->SetFixedHeight(24);
		pRefreshB->SetVisible(true);
		pRefreshB->SetToolTip(_T("refresh"));
		pRefreshB->SetAttribute(_T("normalimage"), _T("file='res\\refreshbuttons.png' source='0,0,24,24'"));
		pRefreshB->SetAttribute(_T("hotimage"), _T("file='res\\refreshbuttons.png' source='0,24,24,48'"));
		pRefreshB->SetAttribute(_T("pushedimage"), _T("file='res\\refreshbuttons.png' source='0,48,24,72'"));
		pVertical->Add(pRefreshB);

		// ContainerUI -- Mode
		CContainerUI* pMode = new CContainerUI();

		pMode->SetName(_T("mode"));
		pMode->SetFloat(true);
		pMode->SetAttribute(_T("pos"), _T("80,60,0,0"));
		pMode->SetFixedWidth(142);
		pMode->SetFixedHeight(16);
		pMode->SetBkImage(_T("res\\livewallcfgmode.png"));
		pVertical->Add(pMode);

		// ButtonUI -- Combine
		CButtonUI* pCombineB_uc = new CButtonUI();

		pCombineB_uc->SetName(_T("btncombine_uc"));
		pCombineB_uc->SetFloat(true);
		pCombineB_uc->SetAttribute(_T("pos"), _T("120,98,0,0"));
		pCombineB_uc->SetFixedWidth(16);
		pCombineB_uc->SetFixedHeight(16);
		pCombineB_uc->SetVisible(false);
		pCombineB_uc->SetAttribute(_T("normalimage"), _T("file='res\\radiobutton_unchecked.png' source='0,0,16,16'"));
		pCombineB_uc->SetAttribute(_T("hotimage"), _T("file='res\\radiobutton_unchecked.png' source='0,16,16,32'"));
		pCombineB_uc->SetAttribute(_T("pushedimage"), _T("file='res\\radiobutton_unchecked.png' source='0,32,16,48'"));
		pVertical->Add(pCombineB_uc);

		CButtonUI* pCombineB_c = new CButtonUI();

		pCombineB_c->SetName(_T("btncombine_c"));
		pCombineB_c->SetFloat(true);
		pCombineB_c->SetAttribute(_T("pos"), _T("120,98,0,0"));
		pCombineB_c->SetFixedWidth(16);
		pCombineB_c->SetFixedHeight(16);
		pCombineB_c->SetVisible(true);
		pCombineB_c->SetAttribute(_T("normalimage"), _T("file='res\\radiobutton_checked.png' source='0,0,16,16'"));
		pCombineB_c->SetAttribute(_T("hotimage"), _T("file='res\\radiobutton_checked.png' source='0,16,16,32'"));
		pCombineB_c->SetAttribute(_T("pushedimage"), _T("file='res\\radiobutton_checked.png' source='0,32,16,48'"));
		pVertical->Add(pCombineB_c);

		// ContainerUI -- Combine
		CContainerUI* pCombineC = new CContainerUI();

		pCombineC->SetName(_T("txtcombine"));
		pCombineC->SetFloat(true);
		pCombineC->SetAttribute(_T("pos"), _T("140,100,0,0"));
		pCombineC->SetFixedWidth(71);
		pCombineC->SetFixedHeight(13);
		pCombineC->SetBkImage(_T("res\\livewallcfgtxtcombine.png"));
		pVertical->Add(pCombineC);

		// ButtonUI -- Alone
		CButtonUI* pAloneB_uc = new CButtonUI();

		pAloneB_uc->SetName(_T("btnalone_uc"));
		pAloneB_uc->SetFloat(true);
		pAloneB_uc->SetAttribute(_T("pos"), _T("120,138,0,0"));
		pAloneB_uc->SetFixedWidth(16);
		pAloneB_uc->SetFixedHeight(16);
		pAloneB_uc->SetVisible(true);
		pAloneB_uc->SetAttribute(_T("normalimage"), _T("file='res\\radiobutton_unchecked.png' source='0,0,16,16'"));
		pAloneB_uc->SetAttribute(_T("hotimage"), _T("file='res\\radiobutton_unchecked.png' source='0,16,16,32'"));
		pAloneB_uc->SetAttribute(_T("pushedimage"), _T("file='res\\radiobutton_unchecked.png' source='0,32,16,48'"));
		pVertical->Add(pAloneB_uc);

		CButtonUI* pAloneB_c = new CButtonUI();

		pAloneB_c->SetName(_T("btnalone_c"));
		pAloneB_c->SetFloat(true);
		pAloneB_c->SetAttribute(_T("pos"), _T("120,138,0,0"));
		pAloneB_c->SetFixedWidth(16);
		pAloneB_c->SetFixedHeight(16);
		pAloneB_c->SetVisible(false);
		pAloneB_c->SetAttribute(_T("normalimage"), _T("file='res\\radiobutton_checked.png' source='0,0,16,16'"));
		pAloneB_c->SetAttribute(_T("hotimage"), _T("file='res\\radiobutton_checked.png' source='0,16,16,32'"));
		pAloneB_c->SetAttribute(_T("pushedimage"), _T("file='res\\radiobutton_checked.png' source='0,32,16,48'"));
		pVertical->Add(pAloneB_c);

		// ContainerUI -- Alone
		CContainerUI* pAlone = new CContainerUI();

		pAlone->SetName(_T("txtalone"));
		pAlone->SetFloat(true);
		pAlone->SetAttribute(_T("pos"), _T("140,140,0,0"));
		pAlone->SetFixedWidth(45);
		pAlone->SetFixedHeight(13);
		pAlone->SetBkImage(_T("res\\livewallcfgtxtalone.png"));
		pVertical->Add(pAlone);

		// ContainerUI -- Line1
		CContainerUI* pLine1 = new CContainerUI();

		pLine1->SetName(_T("line1"));
		pLine1->SetFloat(true);
		pLine1->SetAttribute(_T("pos"), _T("84,190,0,0"));
		pLine1->SetFixedWidth(600);
		pLine1->SetFixedHeight(1);
		pLine1->SetBkImage(_T("res\\line.png"));
		pVertical->Add(pLine1);

		// ContainerUI -- Show
		CContainerUI* pShow = new CContainerUI();

		pShow->SetName(_T("show"));
		pShow->SetFloat(true);
		pShow->SetAttribute(_T("pos"), _T("80,210,0,0"));
		pShow->SetFixedWidth(127);
		pShow->SetFixedHeight(19);
		pShow->SetBkImage(_T("res\\livewallcfgshow.png"));
		pVertical->Add(pShow);

		// ButtonUI -- Graphics
		CButtonUI* pGraphicsB_uc = new CButtonUI();

		pGraphicsB_uc->SetName(_T("btngraphics_uc"));
		pGraphicsB_uc->SetFloat(true);
		pGraphicsB_uc->SetAttribute(_T("pos"), _T("120,248,0,0"));
		pGraphicsB_uc->SetFixedWidth(16);
		pGraphicsB_uc->SetFixedHeight(16);
		pGraphicsB_uc->SetVisible(true);
		pGraphicsB_uc->SetAttribute(_T("normalimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,0,16,16'"));
		pGraphicsB_uc->SetAttribute(_T("hotimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,16,16,32'"));
		pGraphicsB_uc->SetAttribute(_T("pushedimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pGraphicsB_uc);

		CButtonUI* pGraphicsB_c = new CButtonUI();

		pGraphicsB_c->SetName(_T("btngraphics_c"));
		pGraphicsB_c->SetFloat(true);
		pGraphicsB_c->SetAttribute(_T("pos"), _T("120,248,0,0"));
		pGraphicsB_c->SetFixedWidth(16);
		pGraphicsB_c->SetFixedHeight(16);
		pGraphicsB_c->SetVisible(false);
		pGraphicsB_c->SetAttribute(_T("normalimage"), _T("file='res\\checkedbuttons_s.png' source='0,0,16,16'"));
		pGraphicsB_c->SetAttribute(_T("hotimage"), _T("file='res\\checkedbuttons_s.png' source='0,16,16,32'"));
		pGraphicsB_c->SetAttribute(_T("pushedimage"), _T("file='res\\checkedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pGraphicsB_c);

		// ContainerUI -- Graphics
		CContainerUI* pGraphicsC = new CContainerUI();

		pGraphicsC->SetName(_T("txtgraphics"));
		pGraphicsC->SetFloat(true);
		pGraphicsC->SetAttribute(_T("pos"), _T("140,250,0,0"));
		pGraphicsC->SetFixedWidth(298);
		pGraphicsC->SetFixedHeight(16);
		pGraphicsC->SetBkImage(_T("res\\livewallcfgtxtgraphics.png"));
		pVertical->Add(pGraphicsC);

		// ButtonUI -- Font
		CButtonUI* pFontB_uc = new CButtonUI();

		pFontB_uc->SetName(_T("btnfont_uc"));
		pFontB_uc->SetFloat(true);
		pFontB_uc->SetAttribute(_T("pos"), _T("120,278,0,0"));
		pFontB_uc->SetFixedWidth(16);
		pFontB_uc->SetFixedHeight(16);
		pFontB_uc->SetVisible(true);
		pFontB_uc->SetAttribute(_T("normalimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,0,16,16'"));
		pFontB_uc->SetAttribute(_T("hotimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,16,16,32'"));
		pFontB_uc->SetAttribute(_T("pushedimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pFontB_uc);

		CButtonUI* pFontB_c = new CButtonUI();

		pFontB_c->SetName(_T("btnfont_c"));
		pFontB_c->SetFloat(true);
		pFontB_c->SetAttribute(_T("pos"), _T("120,278,0,0"));
		pFontB_c->SetFixedWidth(16);
		pFontB_c->SetFixedHeight(16);
		pFontB_c->SetVisible(false);
		pFontB_c->SetAttribute(_T("normalimage"), _T("file='res\\checkedbuttons_s.png' source='0,0,16,16'"));
		pFontB_c->SetAttribute(_T("hotimage"), _T("file='res\\checkedbuttons_s.png' source='0,16,16,32'"));
		pFontB_c->SetAttribute(_T("pushedimage"), _T("file='res\\checkedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pFontB_c);

		// ContainerUI -- Font
		CContainerUI* pFontC = new CContainerUI();

		pFontC->SetName(_T("txtfont"));
		pFontC->SetFloat(true);
		pFontC->SetAttribute(_T("pos"), _T("140,280,0,0"));
		pFontC->SetFixedWidth(186);
		pFontC->SetFixedHeight(15);
		pFontC->SetBkImage(_T("res\\livewallcfgtxtfont.png"));
		pVertical->Add(pFontC);

		// EditUI -- Font
		CEditUI* pFontE = new CEditUI();

		pFontE->SetName(_T("edtfont"));
		pFontE->SetFloat(true);
		pFontE->SetAttribute(_T("pos"), _T("340,276,0,0"));
		pFontE->SetAttribute(_T("textpadding"), _T("5,1,5,1"));
		pFontE->SetFixedWidth(50);
		pFontE->SetFixedHeight(24);
		pFontE->SetMaxChar(2);
		pFontE->SetTextColor(0xFF000000);
		pFontE->SetNativeEditBkColor(0xFFF5F5F5);
		pFontE->SetFont(0);
		pFontE->SetReadOnly(false);
		pFontE->SetAttribute(_T("normalimage"), _T("file='res\\shortedits.png' source='0,0,50,24'"));
		pFontE->SetAttribute(_T("hotimage"), _T("file='res\\shortedits.png' source='0,24,50,48'"));
		pFontE->SetAttribute(_T("pushedimage"), _T("file='res\\shortedits.png' source='0,24,50,48'"));
		pVertical->Add(pFontE);

		// ContainerUI -- Line2
		CContainerUI* pLine2 = new CContainerUI();

		pLine2->SetName(_T("line2"));
		pLine2->SetFloat(true);
		pLine2->SetAttribute(_T("pos"), _T("84,330,0,0"));
		pLine2->SetFixedWidth(600);
		pLine2->SetFixedHeight(1);
		pLine2->SetBkImage(_T("res\\line.png"));
		pVertical->Add(pLine2);

		// ContainerUI -- Display
		CContainerUI* pDisplay = new CContainerUI();

		pDisplay->SetName(_T("display"));
		pDisplay->SetFloat(true);
		pDisplay->SetAttribute(_T("pos"), _T("80,350,0,0"));
		pDisplay->SetFixedWidth(136);
		pDisplay->SetFixedHeight(19);
		pDisplay->SetBkImage(_T("res\\livewallcfgdisplay.png"));
		pVertical->Add(pDisplay);

		// ButtonUI -- Fill
		CButtonUI* pFillB_uc = new CButtonUI();

		pFillB_uc->SetName(_T("btnfill_uc"));
		pFillB_uc->SetFloat(true);
		pFillB_uc->SetAttribute(_T("pos"), _T("120,388,0,0"));
		pFillB_uc->SetFixedWidth(16);
		pFillB_uc->SetFixedHeight(16);
		pFillB_uc->SetVisible(false);
		pFillB_uc->SetAttribute(_T("normalimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,0,16,16'"));
		pFillB_uc->SetAttribute(_T("hotimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,16,16,32'"));
		pFillB_uc->SetAttribute(_T("pushedimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pFillB_uc);

		CButtonUI* pFillB_c = new CButtonUI();

		pFillB_c->SetName(_T("btnfill_c"));
		pFillB_c->SetFloat(true);
		pFillB_c->SetAttribute(_T("pos"), _T("120,388,0,0"));
		pFillB_c->SetFixedWidth(16);
		pFillB_c->SetFixedHeight(16);
		pFillB_c->SetVisible(true);
		pFillB_c->SetAttribute(_T("normalimage"), _T("file='res\\checkedbuttons_s.png' source='0,0,16,16'"));
		pFillB_c->SetAttribute(_T("hotimage"), _T("file='res\\checkedbuttons_s.png' source='0,16,16,32'"));
		pFillB_c->SetAttribute(_T("pushedimage"), _T("file='res\\checkedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pFillB_c);

		// ContainerUI -- Fill
		CContainerUI* pFillC = new CContainerUI();

		pFillC->SetName(_T("txtfill"));
		pFillC->SetFloat(true);
		pFillC->SetAttribute(_T("pos"), _T("140,390,0,0"));
		pFillC->SetFixedWidth(16);
		pFillC->SetFixedHeight(12);
		pFillC->SetBkImage(_T("res\\livewallcfgtxtfill.png"));
		pVertical->Add(pFillC);

		// ButtonUI -- Adapt
		CButtonUI* pAdaptB_uc = new CButtonUI();

		pAdaptB_uc->SetName(_T("btnadapt_uc"));
		pAdaptB_uc->SetFloat(true);
		pAdaptB_uc->SetAttribute(_T("pos"), _T("120,428,0,0"));
		pAdaptB_uc->SetFixedWidth(16);
		pAdaptB_uc->SetFixedHeight(16);
		pAdaptB_uc->SetVisible(true);
		pAdaptB_uc->SetAttribute(_T("normalimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,0,16,16'"));
		pAdaptB_uc->SetAttribute(_T("hotimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,16,16,32'"));
		pAdaptB_uc->SetAttribute(_T("pushedimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pAdaptB_uc);

		CButtonUI* pAdaptB_c = new CButtonUI();

		pAdaptB_c->SetName(_T("btnadapt_c"));
		pAdaptB_c->SetFloat(true);
		pAdaptB_c->SetAttribute(_T("pos"), _T("120,428,0,0"));
		pAdaptB_c->SetFixedWidth(16);
		pAdaptB_c->SetFixedHeight(16);
		pAdaptB_c->SetVisible(false);
		pAdaptB_c->SetAttribute(_T("normalimage"), _T("file='res\\checkedbuttons_s.png' source='0,0,16,16'"));
		pAdaptB_c->SetAttribute(_T("hotimage"), _T("file='res\\checkedbuttons_s.png' source='0,16,16,32'"));
		pAdaptB_c->SetAttribute(_T("pushedimage"), _T("file='res\\checkedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pAdaptB_c);

		// ContainerUI -- Adapt
		CContainerUI* pAdaptC = new CContainerUI();

		pAdaptC->SetName(_T("txtadapt"));
		pAdaptC->SetFloat(true);
		pAdaptC->SetAttribute(_T("pos"), _T("140,430,0,0"));
		pAdaptC->SetFixedWidth(50);
		pAdaptC->SetFixedHeight(15);
		pAdaptC->SetBkImage(_T("res\\livewallcfgtxtadapt.png"));
		pVertical->Add(pAdaptC);

		// ButtonUI -- Stretch
		CButtonUI* pStretchB_uc = new CButtonUI();

		pStretchB_uc->SetName(_T("btnstretch_uc"));
		pStretchB_uc->SetFloat(true);
		pStretchB_uc->SetAttribute(_T("pos"), _T("120,468,0,0"));
		pStretchB_uc->SetFixedWidth(16);
		pStretchB_uc->SetFixedHeight(16);
		pStretchB_uc->SetVisible(true);
		pStretchB_uc->SetAttribute(_T("normalimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,0,16,16'"));
		pStretchB_uc->SetAttribute(_T("hotimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,16,16,32'"));
		pStretchB_uc->SetAttribute(_T("pushedimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pStretchB_uc);

		CButtonUI* pStretchB_c = new CButtonUI();

		pStretchB_c->SetName(_T("btnstretch_c"));
		pStretchB_c->SetFloat(true);
		pStretchB_c->SetAttribute(_T("pos"), _T("120,468,0,0"));
		pStretchB_c->SetFixedWidth(16);
		pStretchB_c->SetFixedHeight(16);
		pStretchB_c->SetVisible(false);
		pStretchB_c->SetAttribute(_T("normalimage"), _T("file='res\\checkedbuttons_s.png' source='0,0,16,16'"));
		pStretchB_c->SetAttribute(_T("hotimage"), _T("file='res\\checkedbuttons_s.png' source='0,16,16,32'"));
		pStretchB_c->SetAttribute(_T("pushedimage"), _T("file='res\\checkedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pStretchB_c);

		// ContainerUI -- Stretch
		CContainerUI* pStretchC = new CContainerUI();

		pStretchC->SetName(_T("txtstretch"));
		pStretchC->SetFloat(true);
		pStretchC->SetAttribute(_T("pos"), _T("140,470,0,0"));
		pStretchC->SetFixedWidth(53);
		pStretchC->SetFixedHeight(13);
		pStretchC->SetBkImage(_T("res\\livewallcfgtxtstretch.png"));
		pVertical->Add(pStretchC);

		// ButtonUI -- Tile
		CButtonUI* pTileB_uc = new CButtonUI();

		pTileB_uc->SetName(_T("btntile_uc"));
		pTileB_uc->SetFloat(true);
		pTileB_uc->SetAttribute(_T("pos"), _T("120,508,0,0"));
		pTileB_uc->SetFixedWidth(16);
		pTileB_uc->SetFixedHeight(16);
		pTileB_uc->SetVisible(true);
		pTileB_uc->SetAttribute(_T("normalimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,0,16,16'"));
		pTileB_uc->SetAttribute(_T("hotimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,16,16,32'"));
		pTileB_uc->SetAttribute(_T("pushedimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pTileB_uc);

		CButtonUI* pTileB_c = new CButtonUI();

		pTileB_c->SetName(_T("btntile_c"));
		pTileB_c->SetFloat(true);
		pTileB_c->SetAttribute(_T("pos"), _T("120,508,0,0"));
		pTileB_c->SetFixedWidth(16);
		pTileB_c->SetFixedHeight(16);
		pTileB_c->SetVisible(false);
		pTileB_c->SetAttribute(_T("normalimage"), _T("file='res\\checkedbuttons_s.png' source='0,0,16,16'"));
		pTileB_c->SetAttribute(_T("hotimage"), _T("file='res\\checkedbuttons_s.png' source='0,16,16,32'"));
		pTileB_c->SetAttribute(_T("pushedimage"), _T("file='res\\checkedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pTileB_c);

		// ContainerUI -- Tile
		CContainerUI* pTileC = new CContainerUI();

		pTileC->SetName(_T("txttile"));
		pTileC->SetFloat(true);
		pTileC->SetAttribute(_T("pos"), _T("140,510,0,0"));
		pTileC->SetFixedWidth(23);
		pTileC->SetFixedHeight(13);
		pTileC->SetBkImage(_T("res\\livewallcfgtxttile.png"));
		pVertical->Add(pTileC);

		// ButtonUI -- Center
		CButtonUI* pCenterB_uc = new CButtonUI();

		pCenterB_uc->SetName(_T("btncenter_uc"));
		pCenterB_uc->SetFloat(true);
		pCenterB_uc->SetAttribute(_T("pos"), _T("120,548,0,0"));
		pCenterB_uc->SetFixedWidth(16);
		pCenterB_uc->SetFixedHeight(16);
		pCenterB_uc->SetVisible(true);
		pCenterB_uc->SetAttribute(_T("normalimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,0,16,16'"));
		pCenterB_uc->SetAttribute(_T("hotimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,16,16,32'"));
		pCenterB_uc->SetAttribute(_T("pushedimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pCenterB_uc);

		CButtonUI* pCenterB_c = new CButtonUI();

		pCenterB_c->SetName(_T("btncenter_c"));
		pCenterB_c->SetFloat(true);
		pCenterB_c->SetAttribute(_T("pos"), _T("120,548,0,0"));
		pCenterB_c->SetFixedWidth(16);
		pCenterB_c->SetFixedHeight(16);
		pCenterB_c->SetVisible(false);
		pCenterB_c->SetAttribute(_T("normalimage"), _T("file='res\\checkedbuttons_s.png' source='0,0,16,16'"));
		pCenterB_c->SetAttribute(_T("hotimage"), _T("file='res\\checkedbuttons_s.png' source='0,16,16,32'"));
		pCenterB_c->SetAttribute(_T("pushedimage"), _T("file='res\\checkedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pCenterB_c);

		// ContainerUI -- Center
		CContainerUI* pCenterC = new CContainerUI();

		pCenterC->SetName(_T("txtcenter"));
		pCenterC->SetFloat(true);
		pCenterC->SetAttribute(_T("pos"), _T("140,550,0,0"));
		pCenterC->SetFixedWidth(53);
		pCenterC->SetFixedHeight(13);
		pCenterC->SetBkImage(_T("res\\livewallcfgtxtcenter.png"));
		pVertical->Add(pCenterC);

		// ContainerUI -- Line3
		/*CContainerUI* pLine3 = new CContainerUI();

		pLine3->SetName(_T("line3"));
		pLine3->SetFloat(true);
		pLine3->SetAttribute(_T("pos"), _T("84,540,0,0"));
		pLine3->SetFixedWidth(600);
		pLine3->SetFixedHeight(1);
		pLine3->SetBkImage(_T("res\\line.png"));
		pVertical->Add(pLine3);*/

		// ContainerUI -- Audio
		CContainerUI* pAudio = new CContainerUI();

		pAudio->SetName(_T("audio"));
		pAudio->SetFloat(true);
		pAudio->SetAttribute(_T("pos"), _T("384,350,0,0"));
		pAudio->SetFixedWidth(133);
		pAudio->SetFixedHeight(19);
		pAudio->SetBkImage(_T("res\\livewallcfgaudio.png"));
		pVertical->Add(pAudio);

		// ButtonUI -- Audio
		CButtonUI* pAudioB_uc = new CButtonUI();

		pAudioB_uc->SetName(_T("btnaudio_uc"));
		pAudioB_uc->SetFloat(true);
		pAudioB_uc->SetAttribute(_T("pos"), _T("424,388,0,0"));
		pAudioB_uc->SetFixedWidth(16);
		pAudioB_uc->SetFixedHeight(16);
		pAudioB_uc->SetVisible(true);
		pAudioB_uc->SetAttribute(_T("normalimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,0,16,16'"));
		pAudioB_uc->SetAttribute(_T("hotimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,16,16,32'"));
		pAudioB_uc->SetAttribute(_T("pushedimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pAudioB_uc);

		CButtonUI* pAudioB_c = new CButtonUI();

		pAudioB_c->SetName(_T("btnaudio_c"));
		pAudioB_c->SetFloat(true);
		pAudioB_c->SetAttribute(_T("pos"), _T("424,388,0,0"));
		pAudioB_c->SetFixedWidth(16);
		pAudioB_c->SetFixedHeight(16);
		pAudioB_c->SetVisible(false);
		pAudioB_c->SetAttribute(_T("normalimage"), _T("file='res\\checkedbuttons_s.png' source='0,0,16,16'"));
		pAudioB_c->SetAttribute(_T("hotimage"), _T("file='res\\checkedbuttons_s.png' source='0,16,16,32'"));
		pAudioB_c->SetAttribute(_T("pushedimage"), _T("file='res\\checkedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pAudioB_c);

		// ContainerUI -- Audio
		CContainerUI* pAudioC = new CContainerUI();

		pAudioC->SetName(_T("txtaudio"));
		pAudioC->SetFloat(true);
		pAudioC->SetAttribute(_T("pos"), _T("444,390,0,0"));
		pAudioC->SetFixedWidth(103);
		pAudioC->SetFixedHeight(13);
		pAudioC->SetBkImage(_T("res\\livewallcfgtxtaudio.png"));
		pVertical->Add(pAudioC);

		// ContainerUI -- Logs
		CContainerUI* pLogs = new CContainerUI();

		pLogs->SetName(_T("logs"));
		pLogs->SetFloat(true);
		pLogs->SetAttribute(_T("pos"), _T("384,430,0,0"));
		pLogs->SetFixedWidth(120);
		pLogs->SetFixedHeight(19);
		pLogs->SetBkImage(_T("res\\livewallcfglogs.png"));
		pVertical->Add(pLogs);

		// ButtonUI -- Logs
		CButtonUI* pLogsB_uc = new CButtonUI();

		pLogsB_uc->SetName(_T("btnlogs_uc"));
		pLogsB_uc->SetFloat(true);
		pLogsB_uc->SetAttribute(_T("pos"), _T("424,468,0,0"));
		pLogsB_uc->SetFixedWidth(16);
		pLogsB_uc->SetFixedHeight(16);
		pLogsB_uc->SetVisible(true);
		pLogsB_uc->SetAttribute(_T("normalimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,0,16,16'"));
		pLogsB_uc->SetAttribute(_T("hotimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,16,16,32'"));
		pLogsB_uc->SetAttribute(_T("pushedimage"), _T("file='res\\uncheckedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pLogsB_uc);

		CButtonUI* pLogsB_c = new CButtonUI();

		pLogsB_c->SetName(_T("btnlogs_c"));
		pLogsB_c->SetFloat(true);
		pLogsB_c->SetAttribute(_T("pos"), _T("424,468,0,0"));
		pLogsB_c->SetFixedWidth(16);
		pLogsB_c->SetFixedHeight(16);
		pLogsB_c->SetVisible(false);
		pLogsB_c->SetAttribute(_T("normalimage"), _T("file='res\\checkedbuttons_s.png' source='0,0,16,16'"));
		pLogsB_c->SetAttribute(_T("hotimage"), _T("file='res\\checkedbuttons_s.png' source='0,16,16,32'"));
		pLogsB_c->SetAttribute(_T("pushedimage"), _T("file='res\\checkedbuttons_s.png' source='0,32,16,48'"));
		pVertical->Add(pLogsB_c);

		// ContainerUI -- Logs
		CContainerUI* pLogsC = new CContainerUI();

		pLogsC->SetName(_T("txtlogs"));
		pLogsC->SetFloat(true);
		pLogsC->SetAttribute(_T("pos"), _T("444,470,0,0"));
		pLogsC->SetFixedWidth(92);
		pLogsC->SetFixedHeight(16);
		pLogsC->SetBkImage(_T("res\\livewallcfgtxtlogs.png"));
		pVertical->Add(pLogsC);

		// Send Message Update...
		::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_SETTINGWALL_GETCONFIG, (WPARAM)0, (LPARAM)0);
	}
	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageSettingVideoSearch()
// @Purpose: CFrameMain设置视频响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageSettingVideoSearch(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CVerticalLayoutUI* pVertical = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("livesettingcontent")));
	if (pVertical != NULL)
	{
		pVertical->RemoveAll();
	}
	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageSettingAudioSearch()
// @Purpose: CFrameMain设置音频响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageSettingAudioSearch(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CVerticalLayoutUI* pVertical = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("livesettingcontent")));
	if (pVertical != NULL)
	{
		pVertical->RemoveAll();
	}
	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageSettingAlbumSearch()
// @Purpose: CFrameMain设置相簿响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageSettingAlbumSearch(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CVerticalLayoutUI* pVertical = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("livesettingcontent")));
	if (pVertical != NULL)
	{
		pVertical->RemoveAll();
	}
	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageSettingShotSearch()
// @Purpose: CFrameMain设置快照响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageSettingShotSearch(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CVerticalLayoutUI* pVertical = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("livesettingcontent")));
	if (pVertical != NULL)
	{
		pVertical->RemoveAll();
	}
	return 0;
}

//----------------------------------------------
// @Function:	OnUserMessageSettingAISearch()
// @Purpose: CFrameMain设置AI响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnUserMessageSettingAISearch(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CVerticalLayoutUI* pVertical = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("livesettingcontent")));
	if (pVertical != NULL)
	{
		pVertical->RemoveAll();
	}
	return 0;
}

//-------------------------------------------------
// @Function:	OnUserMessageSettingWallGetConfig()
// @Purpose: CFrameMain获取配置文件信息
// @Since: v1.00a
// @Para: None
// @Return: None
//-------------------------------------------------
LRESULT CFrameMain::OnUserMessageSettingWallGetConfig(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	char chFile[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	int nLiveCoreMode = 0;
	int nLiveCoreShowGraphics = 0;
	int nLiveCoreShowGraphicsFont = 0;
	int nLiveCoreWallpaperMode = 0;
	int nLiveCoreWallpaperAudioMode = 0;
	int nLiveCoreLogProcess = 0;

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
	nLiveCoreMode = nValue;																							// LiveCore模式: 0~组合模式 1~分离模式

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_Graphics", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	nLiveCoreShowGraphics = nValue;																					// LiveCore显示: 0~不显示显卡型号(fps) 1~显示显卡型号(fps)

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_GraphicsFont", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	nLiveCoreShowGraphicsFont = nValue;																				// LiveCore显示字体大小

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	nLiveCoreWallpaperMode = nValue;																					// LiveCore屏幕分辨率模式: 0~填充 1~适应 2~拉伸 3~平铺 4~居中

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Audio", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	nLiveCoreWallpaperAudioMode = nValue;																				// LiveCore音频播放模式: 0~不播放音频 1~播放音频

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORELOGMODE", "LiveCore_Log_Process", 0, chArray, MAX_PATH, chFile);
	nValue = atoi(chArray);
	nLiveCoreLogProcess = nValue;																						// LiveCore日志记录: 0~不记录过程 1~记录过程

	// safe delete object...
	SAFE_DELETE(pFile);

	// show configure...
	if (m_pSettingsOpt->IsSelected())
	{
		if (m_pLiveSettingWallOpt->IsSelected())
		{
			CVerticalLayoutUI* pVertical = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("livesettingcontent")));
			if (pVertical != NULL)
			{
				CButtonUI* pCombineB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btncombine_uc")));
				CButtonUI* pCombineB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btncombine_c")));
				CButtonUI* pAloneB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnalone_uc")));
				CButtonUI* pAloneB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnalone_c")));
				CButtonUI* pGraphicsB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btngraphics_uc")));
				CButtonUI* pGraphicsB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btngraphics_c")));
				CButtonUI* pFontB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnfont_uc")));
				CButtonUI* pFontB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnfont_c")));
				CButtonUI* pFillB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnfill_uc")));
				CButtonUI* pFillB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnfill_c")));
				CButtonUI* pAdaptB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnadapt_uc")));
				CButtonUI* pAdaptB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnadapt_c")));
				CButtonUI* pStretchB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnstretch_uc")));
				CButtonUI* pStretchB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnstretch_c")));
				CButtonUI* pTileB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btntile_uc")));
				CButtonUI* pTileB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btntile_c")));
				CButtonUI* pCenterB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btncenter_uc")));
				CButtonUI* pCenterB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btncenter_c")));
				CButtonUI* pAudioB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnaudio_uc")));
				CButtonUI* pAudioB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnaudio_c")));
				CButtonUI* pLogsB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnlogs_uc")));
				CButtonUI* pLogsB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnlogs_c")));
				CEditUI* pFontE = static_cast<CEditUI*>(pVertical->FindSubControl(_T("edtfont")));

				// switch mode...
				if (nLiveCoreMode == 0)
				{
					pCombineB_uc->SetVisible(false);
					pCombineB_c->SetVisible(true);
					pAloneB_uc->SetVisible(true);
					pAloneB_c->SetVisible(false);
				}
				else if (nLiveCoreMode == 1)
				{
					pCombineB_uc->SetVisible(true);
					pCombineB_c->SetVisible(false);
					pAloneB_uc->SetVisible(false);
					pAloneB_c->SetVisible(true);
				}

				// switch graphics...
				if (nLiveCoreShowGraphics == 0)
				{
					pGraphicsB_uc->SetVisible(true);
					pGraphicsB_c->SetVisible(false);
					pFontB_uc->SetVisible(true);
					pFontB_c->SetVisible(false);
					pFontE->SetEnabled(false);
				}
				else if (nLiveCoreShowGraphics == 1)
				{
					pGraphicsB_uc->SetVisible(false);
					pGraphicsB_c->SetVisible(true);
					pFontB_uc->SetVisible(false);
					pFontB_c->SetVisible(true);
					pFontE->SetEnabled(true);
				}

				CDuiString strFont;
				strFont.Format(_T("%d"), nLiveCoreShowGraphicsFont);
				pFontE->SetText(strFont);

				// switch display...
				if (nLiveCoreWallpaperMode == 0)
				{
					pFillB_uc->SetVisible(false);
					pFillB_c->SetVisible(true);
					pAdaptB_uc->SetVisible(true);
					pAdaptB_c->SetVisible(false);
					pStretchB_uc->SetVisible(true);
					pStretchB_c->SetVisible(false);
					pTileB_uc->SetVisible(true);
					pTileB_c->SetVisible(false);
					pCenterB_uc->SetVisible(true);
					pCenterB_c->SetVisible(false);
				}
				else if (nLiveCoreWallpaperMode == 1)
				{
					pFillB_uc->SetVisible(true);
					pFillB_c->SetVisible(false);
					pAdaptB_uc->SetVisible(false);
					pAdaptB_c->SetVisible(true);
					pStretchB_uc->SetVisible(true);
					pStretchB_c->SetVisible(false);
					pTileB_uc->SetVisible(true);
					pTileB_c->SetVisible(false);
					pCenterB_uc->SetVisible(true);
					pCenterB_c->SetVisible(false);
				}
				else if (nLiveCoreWallpaperMode == 2)
				{
					pFillB_uc->SetVisible(true);
					pFillB_c->SetVisible(false);
					pAdaptB_uc->SetVisible(true);
					pAdaptB_c->SetVisible(false);
					pStretchB_uc->SetVisible(false);
					pStretchB_c->SetVisible(true);
					pTileB_uc->SetVisible(true);
					pTileB_c->SetVisible(false);
					pCenterB_uc->SetVisible(true);
					pCenterB_c->SetVisible(false);
				}
				else if (nLiveCoreWallpaperMode == 3)
				{
					pFillB_uc->SetVisible(true);
					pFillB_c->SetVisible(false);
					pAdaptB_uc->SetVisible(true);
					pAdaptB_c->SetVisible(false);
					pStretchB_uc->SetVisible(true);
					pStretchB_c->SetVisible(false);
					pTileB_uc->SetVisible(false);
					pTileB_c->SetVisible(true);
					pCenterB_uc->SetVisible(true);
					pCenterB_c->SetVisible(false);
				}
				else if (nLiveCoreWallpaperMode == 4)
				{
					pFillB_uc->SetVisible(true);
					pFillB_c->SetVisible(false);
					pAdaptB_uc->SetVisible(true);
					pAdaptB_c->SetVisible(false);
					pStretchB_uc->SetVisible(true);
					pStretchB_c->SetVisible(false);
					pTileB_uc->SetVisible(true);
					pTileB_c->SetVisible(false);
					pCenterB_uc->SetVisible(false);
					pCenterB_c->SetVisible(true);
				}

				// switch audio...
				if (nLiveCoreWallpaperAudioMode == 0)
				{
					pAudioB_uc->SetVisible(true);
					pAudioB_c->SetVisible(false);
				}
				else if (nLiveCoreWallpaperAudioMode == 1)
				{
					pAudioB_uc->SetVisible(false);
					pAudioB_c->SetVisible(true);
				}

				// switch logs...
				if (nLiveCoreLogProcess == 0)
				{
					pLogsB_uc->SetVisible(true);
					pLogsB_c->SetVisible(false);
				}
				else if (nLiveCoreLogProcess == 1)
				{
					pLogsB_uc->SetVisible(false);
					pLogsB_c->SetVisible(true);
				}

			}
		}
	}

	return 0;
}

//-------------------------------------------------
// @Function:	OnUserMessageSettingWallSetConfig()
// @Purpose: CFrameMain设置配置文件信息
// @Since: v1.00a
// @Para: None
// @Return: None
//-------------------------------------------------
LRESULT CFrameMain::OnUserMessageSettingWallSetConfig(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	char chFile[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	// record configure...
	if (m_pSettingsOpt->IsSelected())
	{
		if (m_pLiveSettingWallOpt->IsSelected())
		{
			CVerticalLayoutUI* pVertical = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("livesettingcontent")));
			if (pVertical != NULL)
			{
				CButtonUI* pCombineB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btncombine_uc")));
				CButtonUI* pCombineB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btncombine_c")));
				CButtonUI* pAloneB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnalone_uc")));
				CButtonUI* pAloneB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnalone_c")));
				CButtonUI* pGraphicsB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btngraphics_uc")));
				CButtonUI* pGraphicsB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btngraphics_c")));
				CButtonUI* pFontB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnfont_uc")));
				CButtonUI* pFontB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnfont_c")));
				CButtonUI* pFillB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnfill_uc")));
				CButtonUI* pFillB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnfill_c")));
				CButtonUI* pAdaptB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnadapt_uc")));
				CButtonUI* pAdaptB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnadapt_c")));
				CButtonUI* pStretchB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnstretch_uc")));
				CButtonUI* pStretchB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnstretch_c")));
				CButtonUI* pTileB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btntile_uc")));
				CButtonUI* pTileB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btntile_c")));
				CButtonUI* pCenterB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btncenter_uc")));
				CButtonUI* pCenterB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btncenter_c")));
				CButtonUI* pAudioB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnaudio_uc")));
				CButtonUI* pAudioB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnaudio_c")));
				CButtonUI* pLogsB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnlogs_uc")));
				CButtonUI* pLogsB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnlogs_c")));
				CEditUI* pFontE = static_cast<CEditUI*>(pVertical->FindSubControl(_T("edtfont")));

				// analyze file path...
				CPlumFile* pFile = new CPlumFile();
				pFile->PlumFileGetModuleFileNameA(chFile, MAX_PATH);

				pTemp = strrchr(chFile, '\\');
				if (pTemp)* pTemp = '\0';
				strcat_s(chFile, "\\config\\LiveCore.cfg");

				// record mode...
				if (pCombineB_c->IsVisible())
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "0");
					WritePrivateProfileStringA("LIVECOREMODE", "LiveCore_Mode", chArrValue, chFile);
				}
				else
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "1");
					WritePrivateProfileStringA("LIVECOREMODE", "LiveCore_Mode", chArrValue, chFile);
				}

				// record graphics...
				if (pGraphicsB_c->IsVisible())
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "1");
					WritePrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_Graphics", chArrValue, chFile);
				}
				else
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "0");
					WritePrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_Graphics", chArrValue, chFile);
				}

				// record font...
				if (pFontB_c->IsVisible())
				{
					CDuiString strfont = pFontE->GetText();
					int nfont = _ttoi(strfont.GetData());
					if (nfont > 0 && nfont < 100)
					{
						char chArrValue[MAX_PATH] = { 0 };
						memset(chArrValue, 0, MAX_PATH);
						sprintf_s(chArrValue, "%d", nfont);
						WritePrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_GraphicsFont", chArrValue, chFile);
					}
				}

				// record display...
				if (pFillB_c->IsVisible())
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "0");
					WritePrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", chArrValue, chFile);
				}
				else if (pAdaptB_c->IsVisible())
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "1");
					WritePrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", chArrValue, chFile);
				}
				else if (pStretchB_c->IsVisible())
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "2");
					WritePrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", chArrValue, chFile);
				}
				else if (pTileB_c->IsVisible())
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "3");
					WritePrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", chArrValue, chFile);
				}
				else if (pCenterB_c->IsVisible())
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "4");
					WritePrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", chArrValue, chFile);
				}

				// record audio...
				if (pAudioB_c->IsVisible())
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "1");
					WritePrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Audio", chArrValue, chFile);
				}
				else
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "0");
					WritePrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Audio", chArrValue, chFile);
				}

				// record logs...
				if (pLogsB_c->IsVisible())
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "1");
					WritePrivateProfileStringA("LIVECORELOGMODE", "LiveCore_Log_Process", chArrValue, chFile);
				}
				else
				{
					char chArrValue[MAX_PATH] = { 0 };
					memset(chArrValue, 0, MAX_PATH);
					strcpy_s(chArrValue, "0");
					WritePrivateProfileStringA("LIVECORELOGMODE", "LiveCore_Log_Process", chArrValue, chFile);
				}

				// safe delete object...
				SAFE_DELETE(pFile);

			}
		}
	}

	return 0;
}

//----------------------------------------------
// @Function:	OnGetWallVideoShotProcess()
// @Purpose: CFrameMain获取视频壁纸快照进程
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
DWORD CFrameMain::OnGetWallVideoShotProcess(LPVOID lpParameter)
{
	S_WALLVIDEO* pVideoInfo = static_cast<S_WALLVIDEO*>(lpParameter);
	char chVideoPath[256] = { 0 };

	AVFormatContext* pFormatCtx;
	AVCodecContext* pCodecCtx;
	AVCodec* pCodec;
	AVFrame* pFrame;
	AVFrame* pFrameYUV;

	// copy the video path, so that we can use it next...
	memcpy_s(chVideoPath, sizeof(chVideoPath), pVideoInfo->chVideoPath, sizeof(pVideoInfo->chVideoPath));

	// ffmpeg capture video shot...
	av_register_all();//注册所有组件
	pFormatCtx = avformat_alloc_context();//初始化一个AVFormatContext

	// open input video file...
	if (avformat_open_input(&pFormatCtx, chVideoPath, NULL, NULL) != 0)
	{
		return -1;
	}

	// get input video information...
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		return -2;
	}

	// check input video codec types...
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
		return -3;
	}

	pCodecCtx = pFormatCtx->streams[VideoIndex]->codec;

	// search for input video codec...
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		return -4;
	}

	// open the codec...
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		return -5;
	}

	// capture one frame...
	uint8_t* OutBuffer;
	AVPacket* Packet;

	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();

	OutBuffer = (uint8_t*)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));
	avpicture_fill((AVPicture*)pFrameYUV, OutBuffer, AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);
	Packet = (AVPacket*)av_malloc(sizeof(AVPacket));
	av_dump_format(pFormatCtx, 0, chVideoPath, 0);

	// read one frame...
	int ret;
	int got_picture;
	int y_size;
	struct SwsContext* img_convert_ctx;

	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

	while (av_read_frame(pFormatCtx, Packet) >= 0)
	{
		if (Packet->stream_index == VideoIndex)
		{
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, Packet);//解码一帧压缩数据
			if (ret < 0)
			{
				return -6;
			}
			if (got_picture)
			{
				sws_scale(img_convert_ctx, (const uint8_t * const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
				y_size = pCodecCtx->width * pCodecCtx->height;
				av_free_packet(Packet);
				break;
			}
		}
		
		av_free_packet(Packet);
	}

	// convert yuv to jpeg...
	AVFormatContext* pFormatCtx2;
	AVOutputFormat* fmt;
	AVStream* video_st;
	AVCodecContext* pCodecCtx2;
	AVCodec* pCodec2;

	AVPacket pkt;
	int y_size2;
	int got_picture2 = 0;

	int ret2 = 0;

	char chOutPath[256] = { 0 };

	CPlumPath::PlumPathGetLocalPathA(chOutPath, sizeof(chOutPath));
	strcat_s(chOutPath, "\\data\\");
	strcat_s(chOutPath, pVideoInfo->chVideoName);
	strcat_s(chOutPath, ".jpg");

	// new a av format context...
	pFormatCtx2 = avformat_alloc_context();//初始化一个AVFormatContext

	// guess format...
	fmt = av_guess_format("mjpeg", NULL, NULL);
	pFormatCtx2->oformat = fmt;

	if (avio_open(&pFormatCtx2->pb, chOutPath, AVIO_FLAG_READ_WRITE) < 0)
	{
		return -7;
	}


	video_st = avformat_new_stream(pFormatCtx2, 0);
	if (video_st == NULL) 
	{
		return -8;
	}

	pCodecCtx2 = video_st->codec;
	pCodecCtx2->codec_id = fmt->video_codec;
	pCodecCtx2->codec_type = AVMEDIA_TYPE_VIDEO;
	pCodecCtx2->pix_fmt = AV_PIX_FMT_YUVJ420P;

	pCodecCtx2->width = pCodecCtx->width;
	pCodecCtx2->height = pCodecCtx->height;

	pCodecCtx2->time_base.num = 1;
	pCodecCtx2->time_base.den = 25;

	av_dump_format(pFormatCtx2, 0, chOutPath, 1);

	pCodec2 = avcodec_find_encoder(pCodecCtx2->codec_id);

	if (!pCodec2) 
	{
		return -9;
	}

	if (avcodec_open2(pCodecCtx2, pCodec2, NULL) < 0) 
	{
		return -10;
	}

	// write header...
	avformat_write_header(pFormatCtx2, NULL);

	y_size2 = pCodecCtx2->width * pCodecCtx2->height;
	av_new_packet(&pkt, y_size2 * 3);

	// encode...
	ret2 = avcodec_encode_video2(pCodecCtx2, &pkt, pFrameYUV, &got_picture2);

	if (ret2 < 0) 
	{
		return -11;
	}

	if (got_picture2 == 1) 
	{
		pkt.stream_index = video_st->index;
		ret2 = av_write_frame(pFormatCtx2, &pkt);
	}

	av_free_packet(&pkt);
	
	av_write_trailer(pFormatCtx2);

	if (video_st) 
	{
		avcodec_close(video_st->codec);
	}
	avio_close(pFormatCtx2->pb);
	avformat_free_context(pFormatCtx2);

	// add once shotcut...
	//::PostMessageA(g_pFrameMain->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_ADDSHOT, (WPARAM)(lpParameter), (LPARAM)0);

	// release resources...
	sws_freeContext(img_convert_ctx);

	av_frame_free(&pFrameYUV);
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);

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
// @Function:	OnSearchWallGraphProcess()
// @Purpose: CFrameMain查询图形数据线程
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
DWORD CFrameMain::OnSearchWallGraphProcess(LPVOID lpParameter)
{
	for (auto iter = g_pFrameMain->m_vecWallGraphInfo.begin(); iter != g_pFrameMain->m_vecWallGraphInfo.end(); ++iter)
	{
		::PostMessageA(g_pFrameMain->GetHWND(), WM_USER_MESSAGE_WALLGRAPH_ADDITEM, (WPARAM)((LPVOID)(&(*iter))), (LPARAM)0);
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
// @Function:	OnSearchWallGraphCallback()
// @Purpose: CFrameMain查询图形数据回调函数
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
int CFrameMain::OnSearchWallGraphCallback(void* data, int argc, char** argv, char** azColName)
{
	S_WALLGRAPH sGraphInfo = { 0 };

	sGraphInfo.nNumber = atoi(*argv);
	sGraphInfo.nReserved = atoi(*(argv + 1));
	strcpy_s(sGraphInfo.chGraphName, *(argv + 2));
	strcpy_s(sGraphInfo.chGraphAuthor, *(argv + 3));
	strcpy_s(sGraphInfo.chGraphID, *(argv + 4));
	strcpy_s(sGraphInfo.chGraphPath, *(argv + 5));
	strcpy_s(sGraphInfo.chReserved1, *(argv + 6));
	strcpy_s(sGraphInfo.chReserved2, *(argv + 7));
	strcpy_s(sGraphInfo.chGraphShot, *(argv + 8));

	g_pFrameMain->m_vecWallGraphInfo.push_back(sGraphInfo);

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

//---------------------------------------------------
// @Function:	OnLButtonClickedLiveWallVideoOption()
// @Purpose: CFrameMain鼠标左键单击视频壁纸视频选项卡
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallVideoOption()
{
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_SEARCH, (WPARAM)0, (LPARAM)0);
}

//---------------------------------------------------
// @Function:	OnLButtonClickedLiveWallGraphOption()
// @Purpose: CFrameMain鼠标左键单击视频壁纸图形选项卡
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallGraphOption()
{
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLGRAPH_SEARCH, (WPARAM)0, (LPARAM)0);
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
	// select option is video...
	if (m_pLiveWallVideoOpt->IsSelected())
	{
		// if mod now video file, then return...
		if (m_bWallVideoMod)
		{
			return;
		}

		// add new video file...
		OPENFILENAME file;
		WCHAR strfile[100 * MAX_PATH] = { 0 };	// support for max 100 files
		WCHAR strpath[MAX_PATH] = { 0 };
		WCHAR strname[MAX_PATH] = { 0 };
		TCHAR* p = NULL;
		int nLen = 0;

		USES_CONVERSION;

		ZeroMemory(&file, sizeof(OPENFILENAME));

		file.lStructSize = sizeof(OPENFILENAME);
		file.lpstrFilter = _T("所有文件\0*.mp4;*.mkv;*.wmv;*.mov;*.avi;*.asf;*.rmvb;*.flv\0" \
			"MP4\0*.mp4\0" \
			"MKV\0*.mkv\0" \
			"WMV\0*.wmv\0" \
			"MOV\0*.mov\0" \
			"AVI\0*.avi\0" \
			"ASF\0*.asf\0" \
			"RMVB\0*.rmvb\0" \
			"FLV\0*.flv\0"\
			"\0");
		file.nFilterIndex = 1;
		file.lpstrFile = strfile;
		file.nMaxFile = sizeof(strfile);
		file.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

		if (GetOpenFileName(&file))
		{
			lstrcpyn(strpath, strfile, file.nFileOffset);
			strpath[file.nFileOffset] = '\0';
			nLen = lstrlen(strpath);

			if (strpath[nLen - 1] != '\\')
			{
				lstrcat(strpath, _T("\\"));
			}

			p = strfile + file.nFileOffset;

			while (*p)
			{
				ZeroMemory(strname, sizeof(strname));
				lstrcat(strname, strpath);
				lstrcat(strname, p);

				char chOriginFile[MAX_PATH] = { 0 };
				char chOriginName[MAX_PATH] = { 0 };
				char* pTemp = NULL;

				strcpy_s(chOriginFile, T2A(strname));
				pTemp = strrchr(chOriginFile, '\\');
				strcpy_s(chOriginName, ++pTemp);

				bool bRepeat = false;

				for (auto iter = m_vecWallVideoInfo.begin(); iter != m_vecWallVideoInfo.end(); ++iter)
				{
					if (!strcmp(iter->chVideoPath, T2A(strname)))
					{
						bRepeat = true;
						break;
					}
				}

				if (!bRepeat)
				{
					S_WALLVIDEO sVideoInfo = { 0 };

					memset(&sVideoInfo, 0, sizeof(sVideoInfo));
					strcpy_s(sVideoInfo.chVideoPath, T2A(strname));

					// add video name...
					char* pTemp = NULL;
					char* pTemp2 = NULL;

					pTemp = strrchr(sVideoInfo.chVideoPath, '\\');
					if (pTemp != NULL)
					{
						pTemp2 = strrchr(pTemp, '.');
						if (pTemp2 != NULL)
						{
							char* pArray = sVideoInfo.chVideoName;

							for (char* point = ++pTemp; point != pTemp2; )
							{
								*pArray++ = *point++;
							}
						}
						else
						{
							strcpy_s(sVideoInfo.chVideoName, ++pTemp);
						}
					}
					else
					{
						strcpy_s(sVideoInfo.chVideoName, sVideoInfo.chVideoPath);
					}

					// add video id...
					GenerateGUID(sVideoInfo.chVideoID, sizeof(sVideoInfo.chVideoID));

					// add video shot...
					//HANDLE hThread = NULL;
					//DWORD dwThreadID = 0;

					//hThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(&CFrameMain::OnGetWallVideoShotProcess), (LPVOID)(&sVideoInfo), 0, &dwThreadID);
					//::CloseHandle(hThread);

					// insert data...
					m_pDBWallpaperVideo.Insert(&sVideoInfo);
				}

				p += lstrlen(p) + 1;
			}

			// search data...
			::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_SEARCH, (WPARAM)0, (LPARAM)0);
		}
	}
	else
	{
		// if mod now graph file, then return...
		if (m_bWallGraphMod)
		{
			return;
		}

		// add new graph file...
		OPENFILENAME file;
		WCHAR strfile[100 * MAX_PATH] = { 0 };	// support for max 100 files
		WCHAR strpath[MAX_PATH] = { 0 };
		WCHAR strname[MAX_PATH] = { 0 };
		TCHAR* p = NULL;
		int nLen = 0;

		USES_CONVERSION;

		ZeroMemory(&file, sizeof(OPENFILENAME));

		file.lStructSize = sizeof(OPENFILENAME);
		file.lpstrFilter = _T("所有文件\0*.png;*.jpg;*.bmp\0" \
			"PNG\0*.png\0" \
			"JPG\0*.jpg\0" \
			"BMP\0*.bmp\0" \
			"\0");
		file.nFilterIndex = 1;
		file.lpstrFile = strfile;
		file.nMaxFile = sizeof(strfile);
		file.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

		if (GetOpenFileName(&file))
		{
			lstrcpyn(strpath, strfile, file.nFileOffset);
			strpath[file.nFileOffset] = '\0';
			nLen = lstrlen(strpath);

			if (strpath[nLen - 1] != '\\')
			{
				lstrcat(strpath, _T("\\"));
			}

			p = strfile + file.nFileOffset;

			while (*p)
			{
				ZeroMemory(strname, sizeof(strname));
				lstrcat(strname, strpath);
				lstrcat(strname, p);

				char chOriginFile[MAX_PATH] = { 0 };
				char chOriginName[MAX_PATH] = { 0 };
				char* pTemp = NULL;

				strcpy_s(chOriginFile, T2A(strname));
				pTemp = strrchr(chOriginFile, '\\');
				strcpy_s(chOriginName, ++pTemp);

				bool bRepeat = false;

				for (auto iter = m_vecWallGraphInfo.begin(); iter != m_vecWallGraphInfo.end(); ++iter)
				{
					if (!strcmp(iter->chGraphPath, T2A(strname)))
					{
						bRepeat = true;
						break;
					}
				}

				if (!bRepeat)
				{
					S_WALLGRAPH sGraphInfo = { 0 };

					memset(&sGraphInfo, 0, sizeof(sGraphInfo));
					strcpy_s(sGraphInfo.chGraphPath, T2A(strname));

					// add graph name...
					char* pTemp = NULL;
					char* pTemp2 = NULL;

					pTemp = strrchr(sGraphInfo.chGraphPath, '\\');
					if (pTemp != NULL)
					{
						pTemp2 = strrchr(pTemp, '.');
						if (pTemp2 != NULL)
						{
							char* pArray = sGraphInfo.chGraphName;

							for (char* point = ++pTemp; point != pTemp2; )
							{
								*pArray++ = *point++;
							}
						}
						else
						{
							strcpy_s(sGraphInfo.chGraphName, ++pTemp);
						}
					}
					else
					{
						strcpy_s(sGraphInfo.chGraphName, sGraphInfo.chGraphPath);
					}

					// add graph id...
					GenerateGUID(sGraphInfo.chGraphID, sizeof(sGraphInfo.chGraphID));

					// insert data...
					m_pDBWallpaperGraph.Insert(&sGraphInfo);
				}

				p += lstrlen(p) + 1;
			}

			// search data...
			::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLGRAPH_SEARCH, (WPARAM)0, (LPARAM)0);
		}
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
	// select option is video...
	if (m_pLiveWallVideoOpt->IsSelected())
	{
		// search for all checkbox...
		if (!m_bWallVideoMod)
		{
			m_bWallVideoMod = true;
		}
		else
		{
			m_bWallVideoMod = false;
		}

		for (int i = 0; i < m_pLiveWallContextLst->GetCount(); ++i)
		{
			CHorizontalLayoutUI* pHorizontal = static_cast<CHorizontalLayoutUI*>(m_pLiveWallContextLst->GetItemAt(i));

			if (pHorizontal != NULL)
			{
				CButtonUI* pPlayBtn = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("play")));
				CButtonUI* pUnChecked = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("unchecked")));
				CButtonUI* pChecked = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("checked")));

				if (m_bWallVideoMod == true)
				{
					pPlayBtn->SetVisible(false);	// do not show play
					pUnChecked->SetVisible(true);	// show mod checkbox
					pChecked->SetVisible(false);
				}
				else
				{
					pPlayBtn->SetVisible(true);		// show play button
					pUnChecked->SetVisible(false);	// do not show checkbox
					pChecked->SetVisible(false);
				}
			}
		}

	}
	else
	{
		// search for all checkbox...
		if (!m_bWallGraphMod)
		{
			m_bWallGraphMod = true;
		}
		else
		{
			m_bWallGraphMod = false;
		}

		for (int i = 0; i < m_pLiveWallContextLst->GetCount(); ++i)
		{
			CHorizontalLayoutUI* pHorizontal = static_cast<CHorizontalLayoutUI*>(m_pLiveWallContextLst->GetItemAt(i));

			if (pHorizontal != NULL)
			{
				CButtonUI* pPlayBtn = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("play")));
				CButtonUI* pUnChecked = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("unchecked")));
				CButtonUI* pChecked = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("checked")));

				if (m_bWallGraphMod == true)
				{
					pPlayBtn->SetVisible(false);	// do not show play
					pUnChecked->SetVisible(true);	// show mod checkbox
					pChecked->SetVisible(false);
				}
				else
				{
					pPlayBtn->SetVisible(true);		// show play button
					pUnChecked->SetVisible(false);	// do not show checkbox
					pChecked->SetVisible(false);
				}
			}

		}

	}

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
	// select option is video...
	if (m_pLiveWallVideoOpt->IsSelected())
	{
		// if mod now video file, then return...
		if (!m_bWallVideoMod)
		{
			return;
		}

		// delete now video file...
		for (int i = 0; i < m_pLiveWallContextLst->GetCount(); ++i)
		{
			CHorizontalLayoutUI* pHorizontal = static_cast<CHorizontalLayoutUI*>(m_pLiveWallContextLst->GetItemAt(i));

			if (pHorizontal != NULL)
			{
				CButtonUI* pChecked = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("checked")));
				CTextUI* pVideoName = static_cast<CTextUI*>(pHorizontal->FindSubControl(_T("videoname")));

				if (pChecked->IsVisible() == true)
				{
					CDuiString csText = pVideoName->GetText();

					USES_CONVERSION;

					for (auto iter = m_vecWallVideoInfo.begin(); iter != m_vecWallVideoInfo.end(); ++iter)
					{
						if (!strcmp(T2A(csText.GetData()), iter->chVideoName))
						{
							m_pDBWallpaperVideo.Delete(iter->chVideoPath);
							break;
						}
					}
				}
			}
		}

		// recover flag...
		m_bWallVideoMod = false;

		// search data...
		::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_SEARCH, (WPARAM)0, (LPARAM)0);
	}
	else
	{
		// if mod now graph file, then return...
		if (!m_bWallGraphMod)
		{
			return;
		}

		// delete now graph file...
		for (int i = 0; i < m_pLiveWallContextLst->GetCount(); ++i)
		{
			CHorizontalLayoutUI* pHorizontal = static_cast<CHorizontalLayoutUI*>(m_pLiveWallContextLst->GetItemAt(i));

			if (pHorizontal != NULL)
			{
				CButtonUI* pChecked = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("checked")));
				CTextUI* pGraphName = static_cast<CTextUI*>(pHorizontal->FindSubControl(_T("graphname")));

				if (pChecked->IsVisible() == true)
				{
					CDuiString csText = pGraphName->GetText();

					USES_CONVERSION;

					for (auto iter = m_vecWallGraphInfo.begin(); iter != m_vecWallGraphInfo.end(); ++iter)
					{
						if (!strcmp(T2A(csText.GetData()), iter->chGraphName))
						{
							m_pDBWallpaperGraph.Delete(iter->chGraphPath);
							break;
						}
					}
				}
			}
		}

		// recover flag...
		m_bWallGraphMod = false;

		// search data...
		::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLGRAPH_SEARCH, (WPARAM)0, (LPARAM)0);
	}

}

//----------------------------------------------
// @Function:	OnLButtonClickedLiveWallSearchBtn()
// @Purpose: CFrameMain鼠标左键单击查询视频按钮
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallSearchBtn()
{
	// select option is video...
	if (m_pLiveWallVideoOpt->IsSelected())
	{
		::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_SEARCH, (WPARAM)0, (LPARAM)0);
	}
	else
	{
		::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLGRAPH_SEARCH, (WPARAM)0, (LPARAM)0);
	}
	
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveWallPreBtn()
// @Purpose: CFrameMain单击播放上一次视频壁纸按钮事件响应
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallPreBtn()
{
	// the last frame...
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_RESTART, (WPARAM)1, (LPARAM)0);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveWallNextBtn()
// @Purpose: CFrameMain单击播放下一次视频壁纸按钮事件响应
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallNextBtn()
{
	// the next frame...
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_RESTART, (WPARAM)0, (LPARAM)0);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveWallPlayBtn()
// @Purpose: CFrameMain单击播放当前视频壁纸按钮事件响应
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallPlayBtn()
{
	if (m_vecWallVideoInfo.size() > 0)
	{
		m_nPlayNo = 0;
		RecordVideoConfigFile(&m_vecWallVideoInfo.at(0));	// record video config file...
		ReStartProcess("LiveWallpaperCore.exe");
	}

	m_ePlayStates = Pause;
	ShowLiveWallPlayStates(m_ePlayStates);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveWallPauseBtn()
// @Purpose: CFrameMain单击暂停当前视频壁纸按钮事件响应
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallPauseBtn()
{
	if (m_vecWallVideoInfo.size() > 0)
	{
		m_nPlayNo = 0;
		RecordVideoConfigFile(&m_vecWallVideoInfo.at(0));	// record video config file...
	}

	m_ePlayStates = Play;
	ShowLiveWallPlayStates(m_ePlayStates);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveWallPauseBtn()
// @Purpose: CFrameMain单击暂停当前视频壁纸按钮事件响应
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallStopBtn()
{
	RecordVideoConfigFile(nullptr);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveWallRandomBtn()
// @Purpose: CFrameMain单击随机播放模式按钮事件响应
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallRandomBtn()
{
	m_ePlayMode = Loop;
	ShowLiveWallPlayMode(m_ePlayMode);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveWallLoopBtn()
// @Purpose: CFrameMain单击循环播放模式按钮事件响应
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallLoopBtn()
{
	m_ePlayMode = Repeat;
	ShowLiveWallPlayMode(m_ePlayMode);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveWallRepeatBtn()
// @Purpose: CFrameMain单击重复播放模式按钮事件响应
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallRepeatBtn()
{
	m_ePlayMode = Order;
	ShowLiveWallPlayMode(m_ePlayMode);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveWallOrderBtn()
// @Purpose: CFrameMain单击顺序播放模式按钮事件响应
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallOrderBtn()
{
	m_ePlayMode = Random;
	ShowLiveWallPlayMode(m_ePlayMode);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveWallControlBtn()
// @Purpose: CFrameMain单击控制模式按钮事件响应
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallControlBtn()
{
	if (!m_bWallShowControl)
	{
		m_bWallShowControl = true;
		m_pLiveWallAddBtn->SetVisible(true);
		m_pLiveWallDelBtn->SetVisible(true);
		m_pLiveWallModBtn->SetVisible(true);
	}
	else
	{
		m_bWallShowControl = false;
		m_pLiveWallAddBtn->SetVisible(false);
		m_pLiveWallDelBtn->SetVisible(false);
		m_pLiveWallModBtn->SetVisible(false);
	}
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveSettingHomeOption()
// @Purpose: CFrameMain单击设置主页选项卡
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveSettingHomeOption()
{
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_SETTINGHOME_SEARCH, (WPARAM)0, (LPARAM)0);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveSettingWallOption()
// @Purpose: CFrameMain单击设置壁纸选项卡
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveSettingWallOption()
{
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_SETTINGWALL_SEARCH, (WPARAM)0, (LPARAM)0);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveSettingVideoOption()
// @Purpose: CFrameMain单击设置视频选项卡
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveSettingVideoOption()
{
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_SETTINGVIDEO_SEARCH, (WPARAM)0, (LPARAM)0);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveSettingAudioOption()
// @Purpose: CFrameMain单击设置音频选项卡
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveSettingAudioOption()
{
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_SETTINGAUDIO_SEARCH, (WPARAM)0, (LPARAM)0);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveSettingAlbumOption()
// @Purpose: CFrameMain单击设置相簿选项卡
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveSettingAlbumOption()
{
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_SETTINGALBUM_SEARCH, (WPARAM)0, (LPARAM)0);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveSettingShotOption()
// @Purpose: CFrameMain单击设置快照选项卡
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveSettingShotOption()
{
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_SETTINGSHOT_SEARCH, (WPARAM)0, (LPARAM)0);
}

//-----------------------------------------------------
// @Function:	OnLButtonClickedLiveSettingAIOption()
// @Purpose: CFrameMain单击设置AI选项卡
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------
void CFrameMain::OnLButtonClickedLiveSettingAIOption()
{
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_SETTINGAI_SEARCH, (WPARAM)0, (LPARAM)0);
}

//----------------------------------------------
// @Function:	OnLButtonClickedOtherEvent()
// @Purpose: CFrameMain鼠标左键单击其他事件响应
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedOtherEvent(CControlUI* pSender)
{
	// LiveWallpaper Selected...
	if (m_pLiveWallpaperOpt->IsSelected())
	{
		// select option is video...
		if (m_pLiveWallVideoOpt->IsSelected())
		{
			// 查找是否是单击LiveWall视频列表中控件(Mod)...
			if (m_bWallVideoMod == true)
			{
				for (int i = 0; i < m_pLiveWallContextLst->GetCount(); ++i)
				{
					CHorizontalLayoutUI* pHorizontal = static_cast<CHorizontalLayoutUI*>(m_pLiveWallContextLst->GetItemAt(i));

					if (pHorizontal != NULL)
					{
						CButtonUI* pUnChecked = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("unchecked")));
						CButtonUI* pChecked = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("checked")));

						if (pSender == pUnChecked)
						{
							pUnChecked->SetVisible(false);
							pChecked->SetVisible(true);
						}

						if (pSender == pChecked)
						{
							pUnChecked->SetVisible(true);
							pChecked->SetVisible(false);
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < m_pLiveWallContextLst->GetCount(); ++i)
				{
					CHorizontalLayoutUI* pHorizontal = static_cast<CHorizontalLayoutUI*>(m_pLiveWallContextLst->GetItemAt(i));

					if (pHorizontal != NULL)
					{
						CButtonUI* pPlayBtn = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("play")));		// play buttons for playing video wallpapaer...

						if (pSender == pPlayBtn)
						{
							m_nPlayNo = i;
							RecordVideoConfigFile(&m_vecWallVideoInfo.at(i));	// record video config file...
							ReStartProcess("LiveWallpaperCore.exe");
							//Sleep(1);
						}
					}
				}
			}
		}
		else
		{
			// 查找是否是单击LiveWall视频列表中控件(Mod)...
			if (m_bWallGraphMod == true)
			{
				for (int i = 0; i < m_pLiveWallContextLst->GetCount(); ++i)
				{
					CHorizontalLayoutUI* pHorizontal = static_cast<CHorizontalLayoutUI*>(m_pLiveWallContextLst->GetItemAt(i));

					if (pHorizontal != NULL)
					{
						CButtonUI* pUnChecked = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("unchecked")));
						CButtonUI* pChecked = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("checked")));

						if (pSender == pUnChecked)
						{
							pUnChecked->SetVisible(false);
							pChecked->SetVisible(true);
						}

						if (pSender == pChecked)
						{
							pUnChecked->SetVisible(true);
							pChecked->SetVisible(false);
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < m_pLiveWallContextLst->GetCount(); ++i)
				{
					CHorizontalLayoutUI* pHorizontal = static_cast<CHorizontalLayoutUI*>(m_pLiveWallContextLst->GetItemAt(i));

					if (pHorizontal != NULL)
					{
						CButtonUI* pPlayBtn = static_cast<CButtonUI*>(pHorizontal->FindSubControl(_T("play")));		// play buttons for playing video wallpapaer...

						if (pSender == pPlayBtn)
						{
							//RecordVideoConfigFile(&m_vecWallVideoInfo.at(i));	// record video config file...
							//ReStartProcess("LiveWallpaperCore.exe");
							//Sleep(1);
						}
					}
				}
			}
		}
	}
	else if (m_pSettingsOpt->IsSelected())	// LiveSetting Selected...
	{
		if (m_pLiveSettingWallOpt->IsSelected())
		{
			CVerticalLayoutUI* pVertical = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("livesettingcontent")));
			
			if (pVertical != NULL)
			{
				CButtonUI* pCombineB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btncombine_uc")));
				CButtonUI* pCombineB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btncombine_c")));
				CButtonUI* pAloneB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnalone_uc")));
				CButtonUI* pAloneB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnalone_c")));
				CButtonUI* pGraphicsB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btngraphics_uc")));
				CButtonUI* pGraphicsB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btngraphics_c")));
				CButtonUI* pFontB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnfont_uc")));
				CButtonUI* pFontB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnfont_c")));
				CButtonUI* pFillB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnfill_uc")));
				CButtonUI* pFillB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnfill_c")));
				CButtonUI* pAdaptB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnadapt_uc")));
				CButtonUI* pAdaptB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnadapt_c")));
				CButtonUI* pStretchB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnstretch_uc")));
				CButtonUI* pStretchB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnstretch_c")));
				CButtonUI* pTileB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btntile_uc")));
				CButtonUI* pTileB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btntile_c")));
				CButtonUI* pCenterB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btncenter_uc")));
				CButtonUI* pCenterB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btncenter_c")));
				CButtonUI* pAudioB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnaudio_uc")));
				CButtonUI* pAudioB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnaudio_c")));
				CButtonUI* pLogsB_uc = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnlogs_uc")));
				CButtonUI* pLogsB_c = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("btnlogs_c")));
				CButtonUI* pSaveB = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("save")));
				CButtonUI* pRefreshB = static_cast<CButtonUI*>(pVertical->FindSubControl(_T("refresh")));
				CEditUI* pFontE = static_cast<CEditUI*>(pVertical->FindSubControl(_T("edtfont")));

				if (pSender == pCombineB_uc)
				{
					pCombineB_uc->SetVisible(false);
					pCombineB_c->SetVisible(true);
					pAloneB_uc->SetVisible(true);
					pAloneB_c->SetVisible(false);
				}

				if (pSender == pAloneB_uc)
				{
					pCombineB_uc->SetVisible(true);
					pCombineB_c->SetVisible(false);
					pAloneB_uc->SetVisible(false);
					pAloneB_c->SetVisible(true);
				}

				if (pSender == pGraphicsB_uc)
				{
					pGraphicsB_uc->SetVisible(false);
					pGraphicsB_c->SetVisible(true);
				}

				if (pSender == pGraphicsB_c)
				{
					pGraphicsB_uc->SetVisible(true);
					pGraphicsB_c->SetVisible(false);
				}

				if (pSender == pFontB_uc)
				{
					pFontB_uc->SetVisible(false);
					pFontB_c->SetVisible(true);
					pFontE->SetEnabled(true);
				}

				if (pSender == pFontB_c)
				{
					pFontB_uc->SetVisible(true);
					pFontB_c->SetVisible(false);
					pFontE->SetEnabled(false);
				}

				if (pSender == pFillB_uc)
				{
					pFillB_uc->SetVisible(false);
					pFillB_c->SetVisible(true);
					pAdaptB_uc->SetVisible(true);
					pAdaptB_c->SetVisible(false);
					pStretchB_uc->SetVisible(true);
					pStretchB_c->SetVisible(false);
					pTileB_uc->SetVisible(true);
					pTileB_c->SetVisible(false);
					pCenterB_uc->SetVisible(true);
					pCenterB_c->SetVisible(false);
				}

				if (pSender == pAdaptB_uc)
				{
					pFillB_uc->SetVisible(true);
					pFillB_c->SetVisible(false);
					pAdaptB_uc->SetVisible(false);
					pAdaptB_c->SetVisible(true);
					pStretchB_uc->SetVisible(true);
					pStretchB_c->SetVisible(false);
					pTileB_uc->SetVisible(true);
					pTileB_c->SetVisible(false);
					pCenterB_uc->SetVisible(true);
					pCenterB_c->SetVisible(false);
				}

				if (pSender == pStretchB_uc)
				{
					pFillB_uc->SetVisible(true);
					pFillB_c->SetVisible(false);
					pAdaptB_uc->SetVisible(true);
					pAdaptB_c->SetVisible(false);
					pStretchB_uc->SetVisible(false);
					pStretchB_c->SetVisible(true);
					pTileB_uc->SetVisible(true);
					pTileB_c->SetVisible(false);
					pCenterB_uc->SetVisible(true);
					pCenterB_c->SetVisible(false);
				}

				if (pSender == pTileB_uc)
				{
					pFillB_uc->SetVisible(true);
					pFillB_c->SetVisible(false);
					pAdaptB_uc->SetVisible(true);
					pAdaptB_c->SetVisible(false);
					pStretchB_uc->SetVisible(true);
					pStretchB_c->SetVisible(false);
					pTileB_uc->SetVisible(false);
					pTileB_c->SetVisible(true);
					pCenterB_uc->SetVisible(true);
					pCenterB_c->SetVisible(false);
				}

				if (pSender == pCenterB_uc)
				{
					pFillB_uc->SetVisible(true);
					pFillB_c->SetVisible(false);
					pAdaptB_uc->SetVisible(true);
					pAdaptB_c->SetVisible(false);
					pStretchB_uc->SetVisible(true);
					pStretchB_c->SetVisible(false);
					pTileB_uc->SetVisible(true);
					pTileB_c->SetVisible(false);
					pCenterB_uc->SetVisible(false);
					pCenterB_c->SetVisible(true);
				}

				if (pSender == pAudioB_uc)
				{
					pAudioB_uc->SetVisible(false);
					pAudioB_c->SetVisible(true);
				}

				if (pSender == pAudioB_c)
				{
					pAudioB_uc->SetVisible(true);
					pAudioB_c->SetVisible(false);
				}

				if (pSender == pLogsB_uc)
				{
					pLogsB_uc->SetVisible(false);
					pLogsB_c->SetVisible(true);
				}

				if (pSender == pLogsB_c)
				{
					pLogsB_uc->SetVisible(true);
					pLogsB_c->SetVisible(false);
				}

				if (pSender == pSaveB)
				{
					::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_SETTINGWALL_SETCONFIG, (WPARAM)0, (LPARAM)0);
				}

				if (pSender == pRefreshB)
				{
					::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_SETTINGWALL_GETCONFIG, (WPARAM)0, (LPARAM)0);
				}

			}
		}
	}

}
