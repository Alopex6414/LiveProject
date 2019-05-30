/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		dbWallpaperGraph.h
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#pragma once

#ifndef __DBWALLPAPERGRAPH_H_
#define __DBWALLPAPERGRAPH_H_

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
typedef int(*LPDBWALLGRAPHSEEKCALLBACK)(void*, int, char**, char**);

// Class Definition
class CDBWallpaperGraph
{
private:
	char m_chFile[MAX_PATH];

public:
	CDBWallpaperGraph();
	~CDBWallpaperGraph();

	int Create();
	int Insert(S_WALLGRAPH* pWallGraphInfo);
	int Update(S_WALLGRAPH* pWallGraphInfo, const char* szPrimaryKey);
	int Delete(const char* szPrimaryKey);
	int Select(LPDBWALLGRAPHSEEKCALLBACK pfunc);
	int Select(LPDBWALLGRAPHSEEKCALLBACK pfunc, const char* szGraphName);

};

#endif // !__DBWALLPAPERGRAPH_H_

