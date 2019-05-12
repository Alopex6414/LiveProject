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

	COptionUI * m_pLiveWallVideoOpt;		// LiveWall ��Ƶѡ�
	COptionUI * m_pLiveWallGraphOpt;		// LiveWall ͼ��ѡ�
	CButtonUI * m_pLiveWallAddBtn;			// LiveWall ��Ӱ�ť
	CButtonUI * m_pLiveWallDelBtn;			// LiveWall ɾ����ť
	CButtonUI * m_pLiveWallModBtn;			// LiveWall �޸İ�ť
	CEditUI * m_pLiveWallSearchEdt;			// LiveWall ��ѯ��
	CButtonUI * m_pLiveWallSearchBtn;		// LiveWall ��ѯ��ť
	CTileLayoutUI * m_pLiveWallContextLst;	// LiveWall �����б�

private:
	HMENU m_hMenu;					// LiveProject �˵���Сͼ����
	NOTIFYICONDATA m_nid;			// LiveProject �˵���Сͼ�����

	bool m_bWallVideoMod;			// LiveWall �޸İ�ť����״̬(Ĭ��false)

public:
	CDBWallpaperVideo m_pDBWallpaperVideo;
	vector<S_WALLVIDEO> m_vecWallVideoInfo;

protected:
	void AddOnceVideoContext(S_WALLVIDEO* pVideoInfo);			// LiveProject ���һ��ǽֽ����
	void PlayOnceVideoContext(S_WALLVIDEO* pVideoInfo);			// LiveProject ����һ��ǽֽ����
	void StopOnceVideoContext();								// LiveProject ֹͣһ��ǽֽ����
	void GenerateGUID(char* chGUID, size_t nSize);				// LiveProject ����GUID
	BOOL ReStartProcess(const char* pStrArr);					// LiveProject ����ReStart
	void RecordVideoConfigFile(S_WALLVIDEO* pVideoInfo);		// LiveProject ��¼ǽֽ�����ļ�

public:
	CPaintManagerUI & GetPaintManager();

public:
	void ConstructExtra();			// LiveProject ���캯��(extra)
	void InitMenuShow();			// LiveProject ��ʼ���˵���ʾ
	void InitWindowSharp();			// LiveProject ��ʼ������
	void InitControls();			// LiveProject ��ʼ���ؼ�
	void InitDataBase();			// LiveProject ��ʼ�����ݿ�(sqlite3)
	void InitSearch();				// LiveProject ��ʼ����ѯ

public:
	LRESULT OnUserMessageMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallVideoInsert(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallVideoDelete(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallVideoSearch(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallVideoAddItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	static DWORD CALLBACK OnGetWallVideoShotProcess(LPVOID lpParameter);							// LiveProject ��ȡ��Ƶ��ֽ���ս���(1st֡)

public:
	static DWORD CALLBACK OnSearchWallVideoProcess(LPVOID lpParameter);
	static int OnSearchWallVideoCallback(void *data, int argc, char **argv, char **azColName);

public:
	void OnLButtonClickedOverBtn();					// LiveProject �����ö���ť�¼���Ӧ
	void OnLButtonClickedCancelOverBtn();			// LiveProject ����ȡ���ö���ť�¼���Ӧ
	void OnLButtonClickedMinBtn();					// LiveProject ������С����ť�¼���Ӧ
	void OnLButtonClickedMaxBtn();					// LiveProject ������󻯰�ť�¼���Ӧ
	void OnLButtonClickedRestoreBtn();				// LiveProject ������ԭ��ť�¼���Ӧ
	void OnLButtonClickedCloseBtn();				// LiveProject �����رհ�ť�¼���Ӧ

	void OnLButtonClickedLiveWallAddBtn();			// LiveWallpaper ���������Ƶ��ֽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallModBtn();			// LiveWallpaper �����޸���Ƶ��ֽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallDelBtn();			// LiveWallpaper ����ɾ����Ƶ��ֽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallSearchBtn();		// LiveWallpaper ������ѯ��Ƶ��ֽ��ť�¼���Ӧ

	void OnLButtonClickedOtherEvent(CControlUI*);	// LiveProject �����¼���Ӧ(�����¼�)...
};

// Variable Extern
extern CFrameMain* g_pFrameMain;

#endif // !__FRAMEMAIN_H_

