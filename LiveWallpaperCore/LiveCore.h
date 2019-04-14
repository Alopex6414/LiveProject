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

// Class Definition
class CLiveCore
{
private:
	DirectGraphics* m_pDirectGraphicsMain;			// DirectX 渲染类实例

private:
	int	m_nDeskTopWidth;							// Desktop 宽度
	int m_nDeskTopHeight;							// Desktop 高度

private:
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
	CRITICAL_SECTION m_csDecode;					// LiveCore 视频解码Cirtical
	volatile bool m_bDecodeFlag;					// LiveCore 视频解码标志

	CRITICAL_SECTION m_csWait;						// LiveCore 默认视频Cirtical
	volatile bool g_bWaitFlag;						// LiveCore 默认视频标志


public:
	CLiveCore();						// CLiveCore 构造
	~CLiveCore();						// CLiveCore 析构

	BOOL	CLiveCoreInit();			// CLiveCore 初始化
	void	CLiveCoreRelease();			// CLiveCore 释放

	void	CLiveCoreUpdate();			// CLiveCore 刷新
	void	CLiveCoreRender();			// CLiveCore 渲染

protected:
	void	AnalyzeConfigFile();		// CLiveCore 分析配置文件
	void	RecordConfigFile();			// CLiveCore 记录配置文件


};

#endif // !__LIVECORE_H_
