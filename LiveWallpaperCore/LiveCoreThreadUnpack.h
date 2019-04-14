/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCoreThreadUnpack.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-14
*/
#pragma once

#ifndef __LIVECORETHREADUNPACK_H_
#define __LIVECORETHREADUNPACK_H_

// Include Common Header File
#include "Common.h"

// Class Definition
class CLiveCoreThreadUnpack : public CPlumThreadBase
{
public:
	CLiveCoreThreadUnpack();
	~CLiveCoreThreadUnpack();
	virtual void WINAPI PlumThreadRun();

};

extern char g_chDefaultVideoAddress[MAX_PATH];
extern char g_chDefaultVideoDirector[MAX_PATH];
extern char g_chDefaultVideoUnpack[MAX_PATH];

#endif // !__LIVECORETHREADUNPACK_H_
