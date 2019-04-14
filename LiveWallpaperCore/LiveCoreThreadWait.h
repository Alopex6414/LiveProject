/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCoreThreadWait.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-14
*/
#pragma once

#ifndef __LIVECORETHREADWAIT_H_
#define __LIVECORETHREADWAIT_H_

// Include Common Header File
#include "Common.h"

// Class Definition
class CLiveCoreThreadWait : public CPlumThreadBase
{
private:
	CLiveCoreWait m_cLiveCoreWait;

public:
	CLiveCoreThreadWait();
	~CLiveCoreThreadWait();
	virtual void WINAPI PlumThreadRun();

};

#endif // !__LIVECORETHREADWAIT_H_

