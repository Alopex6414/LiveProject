/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCoreThread.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-14
*/
#pragma once

#ifndef __LIVECORETHREAD_H_
#define __LIVECORETHREAD_H_

// Include Common Header File
#include "Common.h"

// Class Definition
class CLiveCoreThread : public CPlumThreadBase
{
public:
	CLiveCoreThread();
	~CLiveCoreThread();
	virtual void WINAPI PlumThreadRun();

};

#endif // !__LIVECORETHREAD_H_
