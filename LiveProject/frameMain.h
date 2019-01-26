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
	CButtonUI * m_pCloseBtn;		// LiveProject 关闭按钮
	CButtonUI * m_pRestoreBtn;		// LiveProject 还原按钮
	CButtonUI * m_pMaxBtn;			// LiveProject 最大化按钮
	CButtonUI * m_pMinBtn;			// LiveProject 最小化按钮
	CButtonUI * m_pOverBtn;			// LiveProject 置顶按钮
	CButtonUI * m_pCancelOverBtn;	// LiveProject 取消置顶按钮

	COptionUI * m_pLiveWallpaperOpt;		// LiveProject LiveWallpaper选项卡
	COptionUI * m_pLiveVideoOpt;			// LiveProject LiveVideo选项卡
	COptionUI * m_pLiveAudioOpt;			// LiveProject LiveAudio选项卡
	COptionUI * m_pLiveAlbumOpt;			// LiveProject LiveAlbum选项卡
	COptionUI * m_pLiveShotOpt;				// LiveProject LiveShot选项卡
	COptionUI * m_pLiveAIOpt;				// LiveProject LiveAI选项卡

public:
	void ConstructExtra();			// LiveProject 构造函数(extra)
	void InitControls();			// LiveProject 初始化控件

public:


public:
	void OnLButtonClickedOverBtn();					// LiveProject 单击置顶按钮事件响应
	void OnLButtonClickedCancelOverBtn();			// LiveProject 单击取消置顶按钮事件响应
	void OnLButtonClickedMinBtn();					// LiveProject 单击最小化按钮事件响应
	void OnLButtonClickedMaxBtn();					// LiveProject 单击最大化按钮事件响应
	void OnLButtonClickedRestoreBtn();				// LiveProject 单击还原按钮事件响应
	void OnLButtonClickedCloseBtn();				// LiveProject 单击关闭按钮事件响应

};

#endif // !__FRAMEMAIN_H_

