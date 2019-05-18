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
#include "dbWallpaperVideo.h"
#include "dbWallpaperGraph.h"

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

	CTabLayoutUI * m_pLiveMainTab;			// LiveProject LiveMain容器
	COptionUI * m_pLiveHomeOpt;				// LiveProject LiveHome选项卡
	COptionUI * m_pLiveWallpaperOpt;		// LiveProject LiveWallpaper选项卡
	COptionUI * m_pLiveVideoOpt;			// LiveProject LiveVideo选项卡
	COptionUI * m_pLiveAudioOpt;			// LiveProject LiveAudio选项卡
	COptionUI * m_pLiveAlbumOpt;			// LiveProject LiveAlbum选项卡
	COptionUI * m_pLiveShotOpt;				// LiveProject LiveShot选项卡
	COptionUI * m_pLiveAIOpt;				// LiveProject LiveAI选项卡
	COptionUI * m_pSettingsOpt;				// LiveProject Settings选项卡
	COptionUI * m_pAboutOpt;				// LiveProject About选项卡

	COptionUI * m_pLiveWallVideoOpt;		// LiveWall 视频选项卡
	COptionUI * m_pLiveWallGraphOpt;		// LiveWall 图形选项卡
	CButtonUI * m_pLiveWallAddBtn;			// LiveWall 添加按钮
	CButtonUI * m_pLiveWallDelBtn;			// LiveWall 删除按钮
	CButtonUI * m_pLiveWallModBtn;			// LiveWall 修改按钮
	CEditUI * m_pLiveWallSearchEdt;			// LiveWall 查询栏
	CButtonUI * m_pLiveWallSearchBtn;		// LiveWall 查询按钮
	CTileLayoutUI * m_pLiveWallContextLst;	// LiveWall 内容列表
	CButtonUI * m_pLiveWallPreBtn;			// LiveWall 上一次按钮
	CButtonUI * m_pLiveWallNextBtn;			// LiveWall 下一次按钮
	CButtonUI * m_pLiveWallPlayBtn;			// LiveWall 播放按钮
	CButtonUI * m_pLiveWallPauseBtn;		// LiveWall 暂停按钮

private:
	HMENU m_hMenu;					// LiveProject 菜单栏小图标句柄
	NOTIFYICONDATA m_nid;			// LiveProject 菜单栏小图标参数

	bool m_bWallVideoMod;			// LiveWall 修改按钮单击状态(视频)(默认false)
	bool m_bWallGraphMod;			// LiveWall 修改按钮单击状态(图形)(默认false)

public:
	CDBWallpaperVideo m_pDBWallpaperVideo;
	CDBWallpaperGraph m_pDBWallpaperGraph;
	vector<S_WALLVIDEO> m_vecWallVideoInfo;
	vector<S_WALLGRAPH> m_vecWallGraphInfo;

protected:
	void AddOnceVideoContext(S_WALLVIDEO* pVideoInfo);			// LiveProject 添加一个墙纸内容
	void AddOnceVideoShotCut(S_WALLVIDEO* pVideoInfo);			// LiveProject 添加一个视频快照
	void PlayOnceVideoContext(S_WALLVIDEO* pVideoInfo);			// LiveProject 播放一个墙纸内容
	void StopOnceVideoContext();								// LiveProject 停止一个墙纸内容
	void AddOnceGraphContext(S_WALLGRAPH* pGraphInfo);			// LiveProject 添加一个图形内容
	void AddOnceGraphShotcut(S_WALLGRAPH* pGraphInfo);			// LiveProject 添加一个图形快照
	void PlayOnceGraphContext(S_WALLGRAPH* pGraphInfo);			// LiveProject 播放一个图形内容
	void StopOnceGraphContext();								// LiveProject 停止一个图形内容
	void GenerateGUID(char* chGUID, size_t nSize);				// LiveProject 生成GUID
	BOOL ReStartProcess(const char* pStrArr);					// LiveProject 进程ReStart
	void RecordVideoConfigFile(S_WALLVIDEO* pVideoInfo);		// LiveProject 记录墙纸配置文件

public:
	CPaintManagerUI & GetPaintManager();

public:
	void ConstructExtra();			// LiveProject 构造函数(extra)
	void InitMenuShow();			// LiveProject 初始化菜单显示
	void InitWindowSharp();			// LiveProject 初始化窗口
	void InitControls();			// LiveProject 初始化控件
	void InitDataBase();			// LiveProject 初始化数据库(sqlite3)
	void InitSearch();				// LiveProject 初始化查询

public:
	LRESULT OnUserMessageMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallVideoInsert(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallVideoDelete(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallVideoSearch(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallVideoAddItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallVideoAddShot(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT	OnUserMessageWallGraphInsert(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallGraphDelete(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallGraphSearch(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallGraphAddItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallGraphAddShot(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	static DWORD CALLBACK OnGetWallVideoShotProcess(LPVOID lpParameter);							// LiveProject 获取视频壁纸快照进程(1st帧)

public:
	static DWORD CALLBACK OnSearchWallVideoProcess(LPVOID lpParameter);
	static DWORD CALLBACK OnSearchWallGraphProcess(LPVOID lpParameter);
	static int OnSearchWallVideoCallback(void *data, int argc, char **argv, char **azColName);
	static int OnSearchWallGraphCallback(void* data, int argc, char** argv, char** azColName);

public:
	void OnLButtonClickedOverBtn();					// LiveProject 单击置顶按钮事件响应
	void OnLButtonClickedCancelOverBtn();			// LiveProject 单击取消置顶按钮事件响应
	void OnLButtonClickedMinBtn();					// LiveProject 单击最小化按钮事件响应
	void OnLButtonClickedMaxBtn();					// LiveProject 单击最大化按钮事件响应
	void OnLButtonClickedRestoreBtn();				// LiveProject 单击还原按钮事件响应
	void OnLButtonClickedCloseBtn();				// LiveProject 单击关闭按钮事件响应

	void OnLButtonClickedLiveWallVideoOption();		// LiveProject 单机视频壁纸视频选项卡
	void OnLButtonClickedLiveWallGraphOption();		// LiveProject 单击视频壁纸图形选项卡

	void OnLButtonClickedLiveWallAddBtn();			// LiveWallpaper 单击添加视频壁纸按钮事件响应
	void OnLButtonClickedLiveWallModBtn();			// LiveWallpaper 单击修改视频壁纸按钮事件响应
	void OnLButtonClickedLiveWallDelBtn();			// LiveWallpaper 单击删除视频壁纸按钮事件响应
	void OnLButtonClickedLiveWallSearchBtn();		// LiveWallpaper 单击查询视频壁纸按钮事件响应

	void OnLButtonClickedOtherEvent(CControlUI*);	// LiveProject 单击事件响应(其他事件)...
};

// Variable Extern
extern CFrameMain* g_pFrameMain;

#endif // !__FRAMEMAIN_H_

