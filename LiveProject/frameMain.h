/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameMain.h
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#pragma once

#ifndef __FRAMEMAIN_H_
#define __FRAMEMAIN_H_

// Include Frame Window Common Header File
#include "CommonWnd.h"

// Class Definition
class CFrameMain : public CWindowWnd, public INotifyUI
{
public:
	virtual LPCTSTR GetWindowClassName() const;
	virtual UINT GetClassStyle() const;
	virtual void Notify(TNotifyUI& msg);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	CPaintManagerUI m_PaintManager;

public:
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	CButtonUI * m_pCloseBtn;		// LiveProject �رհ�ť
	CButtonUI * m_pRestoreBtn;		// LiveProject ��ԭ��ť
	CButtonUI * m_pMaxBtn;			// LiveProject ��󻯰�ť
	CButtonUI * m_pMinBtn;			// LiveProject ��С����ť
	CButtonUI * m_pOverBtn;			// LiveProject �ö���ť
	CButtonUI * m_pCancelOverBtn;	// LiveProject ȡ���ö���ť

	COptionUI * m_pLiveWallpaperOpt;
	COptionUI * m_pLiveVideoOpt;
	COptionUI * m_pLiveAudioOpt;
	COptionUI * m_pLiveAlbumOpt;
	COptionUI * m_pLiveShotOpt;
	COptionUI * m_pLiveAIOpt;

public:
	void ConstructExtra();			// LiveProject ���캯��extra
	void InitControls();			// LiveProject ��ʼ���ؼ�

public:


public:
	void OnLButtonClickedMinBtn();					// LiveProject ������С����ť�¼���Ӧ
	void OnLButtonClickedMaxBtn();					// LiveProject ������󻯰�ť�¼���Ӧ
	void OnLButtonClickedRestoreBtn();				// LiveProject ������ԭ��ť�¼���Ӧ
	void OnLButtonClickedCloseBtn();				// LiveProject �����رհ�ť�¼���Ӧ

};

#endif // !__FRAMEMAIN_H_

