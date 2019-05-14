/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCore.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-13
*/
#pragma once

#ifndef __LIVECORE_H_
#define __LIVECORE_H_

// Include Common Header File
#include "Common.h"

// Include LiveCore Header File
#include "LiveCoreLog.h"
#include "LiveCoreThread.h"
#include "LiveCoreThread2.h"
#include "LiveCoreThreadWait.h"
#include "LiveCoreThreadUnpack.h"
#include "LiveCoreThreadMonitor.h"

// Class Definition
class CLiveCore
{
private:
	DirectGraphics* m_pMainGraphics;				// DirectX 渲染类实例
	CCerasusfps* m_pMainfps;						// DirectX 帧速率

private:
	IDirect3DDevice9* m_pD3D9Device;				// DirectX 绘制设备
	IDirect3DSurface9* m_pD3D9Surface;				// DirectX 绘制表面

private:
	int	m_nDeskTopWidth;							// Desktop 宽度
	int m_nDeskTopHeight;							// Desktop 高度

public:
	int m_nVideoWidth;								// Video 宽度
	int m_nVideoHeight;								// Video 高度
	int m_nVideoFreq;								// Video 频率

public:
	int m_nLiveCoreMode;							// LiveCore 模式: 0~组合模式 1~分离模式
	int m_nLiveCoreShowGraphics;					// LiveCore 显示: 0~不显示显卡型号(fps) 1~显示显卡型号(fps)
	int m_nLiveCoreShowGraphicsFont;				// LiveCore 显示字体大小
	int m_nLiveCoreWallpaperMode;					// LiveCore 屏幕分辨率模式: 0~填充 1~适应 2~拉伸 3~平铺 4~居中
	int m_nLiveCoreWallpaperAudioMode;				// LiveCore 音频播放模式: 0~不播放音频 1~播放音频
	int m_nLiveCoreLogProcess;						// LiveCore 日志记录: 0~不记录过程 1~记录过程
	int m_nLiveCoreVideoMode;						// LiveCore 动态壁纸视频模式: 0~启用默认视频 1~启用选择视频
	char m_chLiveCoreVideoName[MAX_PATH];			// LiveCore 动态壁纸默认视频名称
	char m_chLiveCoreVideoAddress[MAX_PATH];		// LiveCore 动态壁纸视频地址

protected:
	CLiveCoreThread g_cLiveCoreThread;
	CPlumThread* g_pPlumThread;

	CLiveCoreThread2 g_cLiveCoreThread2;
	CPlumThread* g_pPlumThread2;

	CLiveCoreThreadWait m_LiveCoreWait;
	CPlumThread* m_pPlumWait;

	CLiveCoreThreadUnpack m_LiveCoreUnpack;
	CPlumThread* m_pPlumUnpack;

	CLiveCoreThreadMonitor g_cLiveCoreMonitor;
	CPlumThread* g_pPlumMonitor;

public:
	CLiveCore();						// CLiveCore 构造
	~CLiveCore();						// CLiveCore 析构

	BOOL	CLiveCoreInit();			// CLiveCore 初始化
	void	CLiveCoreRelease();			// CLiveCore 释放

	void	CLiveCoreUpdate();			// CLiveCore 刷新
	void	CLiveCoreRender();			// CLiveCore 渲染

protected:
	void	AnalyzeConfigFile();																						// CLiveCore 分析配置文件
	void	RecordConfigFile();																							// CLiveCore 记录配置文件
	void	SetChildWindow(HWND);																						// CLiveCore 设置桌面子窗口
	BOOL	AnalyzeVideoInfo(HWND hWnd, const char* pVideoPath, int* pWidth, int* pHeight, int* pFreq);					// CLiveCore 分析视频信息

public:
	BOOL	Restart(const char* pStrArr);																				// CLiveCore Restart进程

};

extern CLiveCore* g_pLiveCore;

extern CRITICAL_SECTION g_csDecode;
extern volatile bool g_bDecodeFlag;

extern CRITICAL_SECTION g_csWait;
extern volatile bool g_bWaitFlag;

extern bool g_bReStart;
extern bool g_bMonitorFlag;

extern unsigned char* g_pArrayY;
extern unsigned char* g_pArrayU;
extern unsigned char* g_pArrayV;

extern char g_chDefaultVideoAddress[MAX_PATH];
extern char g_chDefaultVideoDirector[MAX_PATH];
extern char g_chDefaultVideoUnpack[MAX_PATH];

#endif // !__LIVECORE_H_
