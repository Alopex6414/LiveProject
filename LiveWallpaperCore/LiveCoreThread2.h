/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCoreThread2.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-14
*/
#pragma once

#ifndef __LIVECORETHREAD2_H_
#define __LIVECORETHREAD2_H_

// Include Common Header File
#include "Common.h"

// Class Definition
class CLiveCoreThread2 : public CPlumThreadBase
{
public:
	CLiveCoreThread2();
	~CLiveCoreThread2();
	virtual void WINAPI PlumThreadRun();
};

#endif // !__LIVECORETHREAD2_H_
