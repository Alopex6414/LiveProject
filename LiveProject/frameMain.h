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
	CButtonUI * m_pLiveWallPreBtn;			// LiveWall ��һ�ΰ�ť
	CButtonUI * m_pLiveWallNextBtn;			// LiveWall ��һ�ΰ�ť
	CButtonUI * m_pLiveWallPlayBtn;			// LiveWall ���Ű�ť
	CButtonUI * m_pLiveWallPauseBtn;		// LiveWall ��ͣ��ť
	//CButtonUI * m_pLiveWallStopBtn;			// LiveWall ֹͣ��ť
	CButtonUI * m_pLiveWallRandomBtn;		// LiveWall ������Ű�ť
	CButtonUI * m_pLiveWallLoopBtn;			// LiveWall ѭ�����Ű�ť
	CButtonUI * m_pLiveWallRepeatBtn;		// LiveWall �ظ����Ű�ť
	CButtonUI * m_pLiveWallOrderBtn;		// LiveWall ˳�򲥷Ű�ť

private:
	HMENU m_hMenu;					// LiveProject �˵���Сͼ����
	NOTIFYICONDATA m_nid;			// LiveProject �˵���Сͼ�����

	bool m_bWallVideoMod;			// LiveWall �޸İ�ť����״̬(��Ƶ)(Ĭ��false)
	bool m_bWallGraphMod;			// LiveWall �޸İ�ť����״̬(ͼ��)(Ĭ��false)

	E_WALLPLAYSTATES	m_ePlayStates;		// LiveWall ����״̬
	E_WALLPLAYMODE		m_ePlayMode;		// LiveWall ����ģʽ
	int	m_nPlayNo;							// LiveWall �������

public:
	CDBWallpaperVideo m_pDBWallpaperVideo;
	CDBWallpaperGraph m_pDBWallpaperGraph;
	vector<S_WALLVIDEO> m_vecWallVideoInfo;
	vector<S_WALLGRAPH> m_vecWallGraphInfo;

protected:
	void AddOnceVideoContext(S_WALLVIDEO* pVideoInfo);			// LiveProject ���һ��ǽֽ����
	void AddOnceVideoShotCut(S_WALLVIDEO* pVideoInfo);			// LiveProject ���һ����Ƶ����
	void PlayOnceVideoContext(S_WALLVIDEO* pVideoInfo);			// LiveProject ����һ��ǽֽ����
	void StopOnceVideoContext();								// LiveProject ֹͣһ��ǽֽ����
	void AddOnceGraphContext(S_WALLGRAPH* pGraphInfo);			// LiveProject ���һ��ͼ������
	void AddOnceGraphShotcut(S_WALLGRAPH* pGraphInfo);			// LiveProject ���һ��ͼ�ο���
	void PlayOnceGraphContext(S_WALLGRAPH* pGraphInfo);			// LiveProject ����һ��ͼ������
	void StopOnceGraphContext();								// LiveProject ֹͣһ��ͼ������
	void GenerateGUID(char* chGUID, size_t nSize);				// LiveProject ����GUID
	BOOL ReStartProcess(const char* pStrArr);					// LiveProject ����ReStart
	void RecordVideoConfigFile(S_WALLVIDEO* pVideoInfo);		// LiveProject ��¼ǽֽ�����ļ�
	void ShowLiveWallPlayStates(E_WALLPLAYSTATES ePlayStates);	// LiveProject ����״̬��ťͼ����ʾ
	void ShowLiveWallPlayMode(E_WALLPLAYMODE ePlayMode);		// LiveProject ����ģʽ��ťͼ����ʾ

public:
	CPaintManagerUI & GetPaintManager();

public:
	void ConstructExtra();			// LiveProject ���캯��(extra)
	void InitMenuShow();			// LiveProject ��ʼ���˵���ʾ
	void InitWindowSharp();			// LiveProject ��ʼ������
	void InitControls();			// LiveProject ��ʼ���ؼ�
	void InitDataBase();			// LiveProject ��ʼ�����ݿ�(sqlite3)
	void InitSearch();				// LiveProject ��ʼ����ѯ

	void AnalyzeConfigFile();		// LiveProject ���������ļ�
	void RecordConfigFile();		// LiveProject ��¼�����ļ�

public:
	LRESULT OnUserMessageMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserMessageWallVideoReStart(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
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
	static DWORD CALLBACK OnGetWallVideoShotProcess(LPVOID lpParameter);							// LiveProject ��ȡ��Ƶ��ֽ���ս���(1st֡)

public:
	static DWORD CALLBACK OnSearchWallVideoProcess(LPVOID lpParameter);
	static DWORD CALLBACK OnSearchWallGraphProcess(LPVOID lpParameter);
	static int OnSearchWallVideoCallback(void *data, int argc, char **argv, char **azColName);
	static int OnSearchWallGraphCallback(void* data, int argc, char** argv, char** azColName);

public:
	void OnLButtonClickedOverBtn();					// LiveProject �����ö���ť�¼���Ӧ
	void OnLButtonClickedCancelOverBtn();			// LiveProject ����ȡ���ö���ť�¼���Ӧ
	void OnLButtonClickedMinBtn();					// LiveProject ������С����ť�¼���Ӧ
	void OnLButtonClickedMaxBtn();					// LiveProject ������󻯰�ť�¼���Ӧ
	void OnLButtonClickedRestoreBtn();				// LiveProject ������ԭ��ť�¼���Ӧ
	void OnLButtonClickedCloseBtn();				// LiveProject �����رհ�ť�¼���Ӧ

	void OnLButtonClickedLiveWallVideoOption();		// LiveProject ������Ƶ��ֽ��Ƶѡ�
	void OnLButtonClickedLiveWallGraphOption();		// LiveProject ������Ƶ��ֽͼ��ѡ�

	void OnLButtonClickedLiveWallAddBtn();			// LiveWallpaper ���������Ƶ��ֽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallModBtn();			// LiveWallpaper �����޸���Ƶ��ֽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallDelBtn();			// LiveWallpaper ����ɾ����Ƶ��ֽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallSearchBtn();		// LiveWallpaper ������ѯ��Ƶ��ֽ��ť�¼���Ӧ

	void OnLButtonClickedLiveWallPreBtn();			// LiveWallpaper ����������һ����Ƶ��ֽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallNextBtn();			// LiveWallpaper ����������һ����Ƶ��ֽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallPlayBtn();			// LiveWallpaper �������ŵ�ǰ��Ƶ��ֽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallPauseBtn();		// LiveWallpaper ������ͣ��ǰ��Ƶ��ֽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallRandomBtn();		// LiveWallpaper �����������ģʽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallLoopBtn();			// LiveWallpaper ����ѭ������ģʽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallRepeatBtn();		// LiveWallpaper �����ظ�����ģʽ��ť�¼���Ӧ
	void OnLButtonClickedLiveWallOrderBtn();		// LiveWallpaper ����˳�򲥷�ģʽ��ť�¼���Ӧ

	void OnLButtonClickedOtherEvent(CControlUI*);	// LiveProject �����¼���Ӧ(�����¼�)...
};

// Variable Extern
extern CFrameMain* g_pFrameMain;

#endif // !__FRAMEMAIN_H_

