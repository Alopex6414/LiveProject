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

// CFrameMain��(LiveProject������)
CFrameMain* g_pFrameMain = nullptr;

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
	/*
	 *	User Message
	 */
	case WM_USER_MESSAGE_MENU:
		lRes = OnUserMessageMenu(uMsg, wParam, lParam, bHandled);
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

	g_pFrameMain = this;

	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("frame\\frameMain.xml"), (UINT)0, &cb, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");

	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);   // ��ӿؼ�����Ϣ��Ӧ��������Ϣ�ͻᴫ�ﵽduilib����Ϣѭ�������ǿ�����Notify����������Ϣ����

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
	// �˵���Сͼ��ɾ��
	Shell_NotifyIcon(NIM_DELETE, &m_nid);

	// ������Դ

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
// @Function:	AddOnceWallVideoContext()
// @Purpose: CFrameMain���һ��ǽֽ����
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
// @Purpose: CFrameMain���һ��ǽֽ����
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
// @Purpose: CFrameMain����һ��ǽֽ����
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::PlayOnceVideoContext(S_WALLVIDEO * pVideoInfo)
{
}

//----------------------------------------------
// @Function:	StopOnceVideoContext()
// @Purpose: CFrameMainֹͣһ��ǽֽ����
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::StopOnceVideoContext()
{
}

//----------------------------------------------
// @Function:	AddOnceGraphContext()
// @Purpose: CFrameMain���һ��ͼ������
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
// @Purpose: CFrameMain���һ��ͼ�ο���
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::AddOnceGraphShotcut(S_WALLGRAPH* pGraphInfo)
{
}

//----------------------------------------------
// @Function:	PlayOnceGraphContext()
// @Purpose: CFrameMain����һ��ͼ������
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::PlayOnceGraphContext(S_WALLGRAPH* pGraphInfo)
{
}

//----------------------------------------------
// @Function:	StopOnceGraphContext()
// @Purpose: CFrameMainֹͣһ��ͼ������
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::StopOnceGraphContext()
{
}

//----------------------------------------------
// @Function:	GenerateGUID()
// @Purpose: CFrameMain����GUID
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
// @Purpose: CFrameMain����ReStart
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
// @Purpose: CFrameMain���̼�¼��Ƶ�����ļ�
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
	WritePrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Address", pVideoInfo->chVideoPath, chFile);

	// safe delete object...
	SAFE_DELETE(pFile);
}

//----------------------------------------------
// @Function:	GetPaintManager()
// @Purpose: CFrameMain��ȡ���ƾ��
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
// @Purpose: CFrameMain���캯��extra
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
}

//----------------------------------------------
// @Function:	InitMenuShow()
// @Purpose: CFrameMain��ʼ���˵���ʾ
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
// @Purpose: CFrameMain��ʼ��������״
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

}

//----------------------------------------------
// @Function:	InitDataBase()
// @Purpose: CFrameMain��ʼ�����ݿ�
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
// @Purpose: CFrameMain��ʼ����ѯ
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
// @Purpose: CFrameMain�˵����û���Ϣ
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

//----------------------------------------------
// @Function:	OnUserMessageWallVideoInsert()
// @Purpose: CFrameMain�����Ƶ������Ϣ
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
// @Purpose: CFrameMainɾ����Ƶ������Ϣ
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
// @Purpose: CFrameMain��ѯ��Ƶ������Ϣ
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
// @Purpose: CFrameMain�б����һ����Ƶ��Ϣ
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
// @Purpose: CFrameMain�б����һ����Ƶ����
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
// @Purpose: CFrameMain���ͼ��������Ϣ
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
// @Purpose: CFrameMainɾ��ͼ��������Ϣ
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
// @Purpose: CFrameMain��ѯͼ��������Ϣ
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
// @Purpose: CFrameMain���һ��ͼ��������Ϣ
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
// @Purpose: CFrameMain���ͼ�ο���
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
// @Function:	OnGetWallVideoShotProcess()
// @Purpose: CFrameMain��ȡ��Ƶ��ֽ���ս���
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
	av_register_all();//ע���������
	pFormatCtx = avformat_alloc_context();//��ʼ��һ��AVFormatContext

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
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, Packet);//����һ֡ѹ������
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
	pFormatCtx2 = avformat_alloc_context();//��ʼ��һ��AVFormatContext

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
// @Purpose: CFrameMain��ѯ��Ƶ�����߳�
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
// @Purpose: CFrameMain��ѯͼ�������߳�
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
// @Purpose: CFrameMain��ѯ��Ƶ���ݻص�����
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
// @Purpose: CFrameMain��ѯͼ�����ݻص�����
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
	//::PostMessageA(this->GetHWND(), WM_CLOSE, (WPARAM)0, (LPARAM)0);
	::ShowWindow(this->GetHWND(), SW_HIDE);
}

//---------------------------------------------------
// @Function:	OnLButtonClickedLiveWallVideoOption()
// @Purpose: CFrameMain������������Ƶ��ֽ��Ƶѡ�
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
// @Purpose: CFrameMain������������Ƶ��ֽͼ��ѡ�
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
// @Purpose: CFrameMain���������������Ƶ��ť
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
		file.lpstrFilter = _T("�����ļ�\0*.mp4;*.mkv;*.wmv;*.mov;*.avi;*.asf;*.rmvb;*.flv\0" \
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
		file.lpstrFilter = _T("�����ļ�\0*.png;*.jpg;*.bmp\0" \
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
// @Purpose: CFrameMain�����������޸���Ƶ��ť
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallModBtn()
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

//----------------------------------------------
// @Function:	OnLButtonClickedLiveWallDelBtn()
// @Purpose: CFrameMain����������ɾ����Ƶ��ť
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallDelBtn()
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

//----------------------------------------------
// @Function:	OnLButtonClickedLiveWallSearchBtn()
// @Purpose: CFrameMain������������ѯ��Ƶ��ť
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedLiveWallSearchBtn()
{
	::PostMessageA(this->GetHWND(), WM_USER_MESSAGE_WALLVIDEO_SEARCH, (WPARAM)0, (LPARAM)0);
}

//----------------------------------------------
// @Function:	OnLButtonClickedOtherEvent()
// @Purpose: CFrameMain���������������¼���Ӧ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CFrameMain::OnLButtonClickedOtherEvent(CControlUI* pSender)
{
	// �����Ƿ��ǵ���LiveWall��Ƶ�б��пؼ�(Mod)...
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
					RecordVideoConfigFile(&m_vecWallVideoInfo.at(i));	// record video config file...
					ReStartProcess("LiveWallpaperCore.exe");
					//Sleep(1);
				}
			}
		}
	}


}
