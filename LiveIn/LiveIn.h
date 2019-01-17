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
#include "LiveInres.h"
#include "LiveIntype.h"

// Class Definition
class CLiveIn
{
private:
	DirectGraphics * m_pDirectGraphicsMain;			// DirectX 渲染类实例
	DirectGraphics3D * m_pDirectGraphics3DMain;		// DirectX 渲染类实例(3D)
	DirectSprite * m_pDirectSprite;					// DirectX 渲染粒子

private:
	CCerasusfps * m_pCerasusfpsMain;				// DirectX fps实例

public:
	CSakuraResourceManager * m_pResourceManager;	// Sakura 资源管理器
	CSakuraDialog * m_pSakuraDialog;				// Sakura 窗口

private:
	int m_nIsUseLog;			// CLiveIn 是否启用日志文件记录
	int m_nIsShowAdapter;		// CLiveIn 是否显示显卡型号
	int m_nIsShowFps;			// CLiveIn 是否显示Fps
	int m_nSpriteNum;			// CLiveIn 粒子星数量

	float m_fTimeSum;			// CLiveIn 程式运行时间累积
	bool m_bSpriteRender;		// CLiveIn 粒子星渲染状态

	char m_chPacketRes_bk_00[8192];					// CLiveIn 背景bk_00资源(灰色背景)
	char m_chPacketRes_title_00[8192];				// CLiveIn 背景title_00资源(LiveProject)
	char m_chPacketRes_title_01[8192];				// CLiveIn 背景title_01资源(ライブプロジェクト)
	char m_chPacketRes_title_02[8192];				// CLiveIn 背景title_02资源(版权)
	char m_chPacketRes_wait_00[4096];				// CLiveIn 背景wait_00资源(★★★★★)
	char m_chPacketRes_wait_01[8192];				// CLiveIn 背景wait_01资源(请稍侯...)
	char m_chPacketRes_login_00[8192];				// CLiveIn 按钮login_00资源(登录)
	char m_chPacketRes_account_00[32768];			// CLiveIn 背景account_00资源(账户)
	char m_chPacketRes_sprite_00[4096];				// CLiveIn 粒子sprite_00资源(粒子)

private:
	int m_nStarPosX;			// CLiveIn 粒子坐标--X
	int m_nStarPosY;			// CLiveIn 粒子坐标--Y
	int m_nStarWidth;			// CLiveIn 粒子区域--宽度
	int m_nStarHeight;			// CLiveIn 粒子区域--高度

	vector<TLIVEINSTAR>	m_vecStarArray;				// CLiveIn 粒子数组向量

protected:
	void CLiveDrawAdapter();	// CLiveIn 绘制显卡信息
	void CLiveDrawfps();		// CLiveIn 绘制fps

	void CLiveInAddPacketResBK00(CUUintEx& sUnitEx);			// CLiveIn 加载背景bk_00资源结构
	void CLiveInAddPacketResTITLE00(CUUintEx& sUnitEx);			// CLiveIn 加载背景title_00资源结构
	void CLiveInAddPacketResTITLE01(CUUintEx& sUnitEx);			// CLiveIn 加载背景title_01资源结构
	void CLiveInAddPacketResTITLE02(CUUintEx& sUnitEx);			// CLiveIn 加载背景title_02资源结构
	void CLiveInAddPacketResWAIT01_0(CUUintEx& sUnitEx);		// CLiveIn 加载背景wait_01资源结构(请稍候)
	void CLiveInAddPacketResWAIT01_1(CUUintEx& sUnitEx);		// CLiveIn 加载背景wait_01资源结构(请稍候.)
	void CLiveInAddPacketResWAIT01_2(CUUintEx& sUnitEx);		// CLiveIn 加载背景wait_01资源结构(请稍候..)
	void CLiveInAddPacketResWAIT01_3(CUUintEx& sUnitEx);		// CLiveIn 加载背景wait_01资源结构(请稍候...)
	void CLiveInAddPacketResWAIT00_0(CUUintEx& sUnitEx);		// CLiveIn 加载背景wait_00资源结构(★)
	void CLiveInAddPacketResWAIT00_1(CUUintEx& sUnitEx);		// CLiveIn 加载背景wait_00资源结构(★)
	void CLiveInAddPacketResWAIT00_2(CUUintEx& sUnitEx);		// CLiveIn 加载背景wait_00资源结构(★)
	void CLiveInAddPacketResWAIT00_3(CUUintEx& sUnitEx);		// CLiveIn 加载背景wait_00资源结构(★)
	void CLiveInAddPacketResWAIT00_4(CUUintEx& sUnitEx);		// CLiveIn 加载背景wait_00资源结构(★)
	void CLiveInAddPacketResLOGIN00(CUUintEx& sUnitEx);			// CLiveIn 加载按钮login_00资源(登录)
	void CLiveInAddPacketResACCOUNT00(CUUintEx& sUnitEx);		// CLiveIn 加载背景account_00资源(账户)

public:
	CLiveIn();					// CLiveIn 构造
	~CLiveIn();					// CLiveIn 析构

	BOOL CLiveInInit();			// CLiveIn 初始化
	void CLiveInRelease();		// CLiveIn 释放

	void CLiveInUpdate();		// CLiveIn 刷新
	void CLiveInRender();		// CLiveIn 渲染

	void CLiveInStartUpdate(float fDeltaTime);					// CLiveIn 开始场景刷新

protected:
	BOOL CLiveInReadConfigFile();	// CLiveIn 读取配置文件
	BOOL CLiveInLoadPacketFile();	// CLiveIn 加载封包文件

	void CLiveInSetSpriteArea(int nX, int nY, int nWidth, int nHeight);		// CLiveIn 设置粒子出现区域
	void CLiveInInitSprite();												// CLiveIn 初始化粒子系统

	void CLiveInUpdateSprite();		// CLiveIn 刷新粒子
	void CLiveInRenderSprite();		// CLiveIn 渲染粒子

};

extern void __stdcall CLiveInSakuraGUIEvent(UINT nEvent, int nControlID, CSakuraControl * pControl, void * pUserContext);

#endif // !__LIVEIN_H_

