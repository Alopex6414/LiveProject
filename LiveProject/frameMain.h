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

	CTabLayoutUI * m_pLiveMainTab;			// LiveProject LiveMain����
	COptionUI * m_pLiveHomeOpt;				// LiveProject LiveHomeѡ�
	COptionUI * m_pLiveWallpaperOpt;		// LiveProject LiveWallpaperѡ�
	COptionUI * m_pLiveVideoOpt;			// LiveProject LiveVideoѡ�
	COptionUI * m_pLiveAudioOpt;			// LiveProject LiveAudioѡ�
	COptionUI * m_pLiveAlbumOpt;			// LiveProject LiveAlbumѡ�
	COptionUI * m_pLiveShotOpt;				// LiveProject LiveShotѡ�
	COptionUI * m_pLiveAIOpt;				// LiveProject LiveAIѡ�
	COptionUI * m_pSettingsOpt;				// LiveProject Settingsѡ�
	COptionUI * m_pAboutOpt;				// LiveProject Aboutѡ�

	CContainerUI * m_pLiveHomeCtr;			// LiveProject LiveHome����

	CVerticalLayoutUI * m_pSplitLineVtl;	// LiveProject ����ָ���

public:
	void ConstructExtra();			// LiveProject ���캯��(extra)
	void InitControls();			// LiveProject ��ʼ���ؼ�

public:


public:
	void OnLButtonClickedOverBtn();					// LiveProject �����ö���ť�¼���Ӧ
	void OnLButtonClickedCancelOverBtn();			// LiveProject ����ȡ���ö���ť�¼���Ӧ
	void OnLButtonClickedMinBtn();					// LiveProject ������С����ť�¼���Ӧ
	void OnLButtonClickedMaxBtn();					// LiveProject ������󻯰�ť�¼���Ӧ
	void OnLButtonClickedRestoreBtn();				// LiveProject ������ԭ��ť�¼���Ӧ
	void OnLButtonClickedCloseBtn();				// LiveProject �����رհ�ť�¼���Ӧ

};

#endif // !__FRAMEMAIN_H_

