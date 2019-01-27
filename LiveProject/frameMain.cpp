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

// CFrameMain��(LiveProject������)

//----------------------------------------------
// @Function:	GetWindowClassName()
// @Purpose: CFrameMain��ȡ��������
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
// @Purpose: CFrameMain��ȡ������ʽ
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
// @Purpose: CFrameMain������Ϣ��Ӧ
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

	}

}

//----------------------------------------------
// @Function:	HandleMessage()
// @Purpose: CFrameMain��������Ϣ��Ӧ
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
// @Purpose: CFrameMain���ڴ�����Ϣ��Ӧ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	m_PaintManager.Init(m_hWnd);

	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("frame\\frameMain.xml"), (UINT)0, &cb, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");

	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);   // ��ӿؼ�����Ϣ��Ӧ��������Ϣ�ͻᴫ�ﵽduilib����Ϣѭ�������ǿ�����Notify����������Ϣ����

	ConstructExtra();
	InitControls();

	return 0;
}

//----------------------------------------------
// @Function:	OnLButtonDown()
// @Purpose: CFrameMain����������������Ϣ��Ӧ
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
// @Purpose: CFrameMain���ڹر���Ϣ��Ӧ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = FALSE;
	return 0;
}

//----------------------------------------------
// @Function:	OnTimer()
// @Purpose: CFrameMain���ڶ�ʱ��������Ϣ��Ӧ
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
// @Purpose: CFrameMain���ڼ�����Ϣ��Ӧ
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
// @Purpose: CFrameMain���ڸı�ߴ���Ϣ��Ӧ
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
// @Purpose: CFrameMain�����ػ���Ϣ��Ӧ
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
// @Purpose: CFrameMain���ڵ����Ϣ��Ӧ
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
// @Purpose: CFrameMain���ڳߴ�ı���Ӧ
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
// @Purpose: CFrameMain��ȡ���������С��Ϣ��Ӧ
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
// @Purpose: CFrameMain��ȡ����ϵͳ��Ϣ��Ӧ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
LRESULT CFrameMain::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
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
// @Function:	ConstructExtra()
// @Purpose: CFrameMain���캯��extra
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::ConstructExtra()
{
}

//----------------------------------------------
// @Function:	InitControls()
// @Purpose: CFrameMain��ʼ���ؼ�
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

}

//----------------------------------------------
// @Function:	OnLButtonClickedOverBtn()
// @Purpose: CFrameMain�����������ö���ť
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
// @Purpose: CFrameMain����������ȡ���ö���ť
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
// @Purpose: CFrameMain������������С����ť
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
// @Purpose: CFrameMain������������󻯰�ť
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
// @Purpose: CFrameMain������������ԭ��ť
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
// @Purpose: CFrameMain�����������رհ�ť
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedCloseBtn()
{
	::PostMessageA(this->GetHWND(), WM_CLOSE, (WPARAM)0, (LPARAM)0);
}
