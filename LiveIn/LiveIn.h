/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveIn.h
* @brief	This Program is LiveIn Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-05
*/
#pragma once

#ifndef __LIVEIN_H_
#define __LIVEIN_H_

// Include Common Header File
#include "Common.h"

// Include LiveIn Header File
#include "LiveInlog.h"

// Class Definition
class CLiveIn
{
private:
	DirectGraphics * m_pDirectGraphicsMain;			// DirectX 渲染类实例
	DirectGraphics3D * m_pDirectGraphics3DMain;		// DirectX 渲染类实例(3D)

private:
	CCerasusfps * m_pCerasusfpsMain;				// DirectX fps实例

public:
	CSakuraResourceManager * m_pResourceManager;	// Sakura 资源管理器
	CSakuraDialog* m_pSakuraDialog;					// Sakura 窗口

private:
	int m_nIsUseLog;			// CLiveIn 是否启用日志文件记录
	int m_nIsShowAdapter;		// CLiveIn 是否显示显卡型号
	int m_nIsShowFps;			// CLiveIn 是否显示Fps

	char m_chPacketRes_bk_00[8192];					// CLiveIn 背景bk_00资源(灰色背景)
	char m_chPacketRes_title_00[8192];				// CLiveIn 背景title_00资源(LiveProject)
	char m_chPacketRes_title_01[8192];				// CLiveIn 背景title_01资源(ライブプロジェクト)
	char m_chPacketRes_title_02[8192];				// CLiveIn 背景title_02资源(版权)

protected:
	void CLiveDrawAdapter();	// CLiveIn 绘制显卡信息
	void CLiveDrawfps();		// CLiveIn 绘制fps

	void CLiveInAddPacketResBK00(CUUintEx& sUnitEx);			// CLiveIn 加载背景bk_00资源结构
	void CLiveInAddPacketResTITLE00(CUUintEx& sUnitEx);			// CLiveIn 加载背景title_00资源结构
	void CLiveInAddPacketResTITLE01(CUUintEx& sUnitEx);			// CLiveIn 加载背景title_01资源结构
	void CLiveInAddPacketResTITLE02(CUUintEx& sUnitEx);			// CLiveIn 加载背景title_02资源结构

public:
	CLiveIn();					// CLiveIn 构造
	~CLiveIn();					// CLiveIn 析构

	BOOL CLiveInInit();			// CLiveIn 初始化
	void CLiveInRelease();		// CLiveIn 释放

	void CLiveInUpdate();		// CLiveIn 刷新
	void CLiveInRender();		// CLiveIn 渲染

protected:
	BOOL CLiveInReadConfigFile();	// CLiveIn 读取配置文件
	BOOL CLiveInLoadPacketFile();	// CLiveIn 加载封包文件

};

extern void __stdcall CLiveInSakuraGUIEvent(UINT nEvent, int nControlID, CSakuraControl * pControl, void * pUserContext);

#endif // !__LIVEIN_H_

