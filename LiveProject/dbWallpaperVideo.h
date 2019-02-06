/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		dbWallpaperVideo.h
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#pragma once

#ifndef __DBWALLPAPERVIDEO_H_
#define __DBWALLPAPERVIDEO_H_

// Include Windows Header File
#include <Windows.h>

// Include C/C++ Running Header File
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <mmreg.h>
#include <wchar.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>

// Include Sqlite3(Database) Header File
#include "sqlite3.h"

// Include Prunus(C/C++ Win32) Library Header File
#include "PlumCommon.h"
#include "PlumLog.h"
#include "PlumLogEx.h"
#include "PlumPath.h"

// Include Types Header File
#include "types.h"

// Callback Definition
typedef int(*LPDBWALLVIDEOSEEKCALLBACK)(void*, int, char**, char**);

// Class Definition
class CDBWallpaperVideo
{
private:
	char m_chFile[MAX_PATH];

public:
	CDBWallpaperVideo();
	~CDBWallpaperVideo();

	int Create();
	int Insert(S_WALLVIDEO* pWallVideoInfo);
	int Update(S_WALLVIDEO* pWallVideoInfo, const char* szPrimaryKey);
	int Delete(const char* szPrimaryKey);
	int Select(LPDBWALLVIDEOSEEKCALLBACK pfunc);

};

#endif // !__DBWALLPAPERVIDEO_H_

