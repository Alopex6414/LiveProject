/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCoreThreadMonitor.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-14
*/
#pragma once

#ifndef __LIVECORETHREADMONITOR_H_
#define	__LIVECORETHREADMONITOR_H_

// Include Common Header File
#include "Common.h"

// Class Definition
class CLiveCoreThreadMonitor : public CPlumThreadBase
{
private:
	bool m_bProcess;

public:
	CLiveCoreThreadMonitor();
	~CLiveCoreThreadMonitor();
	virtual void WINAPI PlumThreadRun();

};

extern bool g_bMonitorFlag;

#endif // !__LIVECORETHREADMONITOR_H_
