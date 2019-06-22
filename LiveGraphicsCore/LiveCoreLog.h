/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCoreLog.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-13
*/
#pragma once

#ifndef __LIVECORELOG_H_
#define __LIVECORELOG_H_

// Include Plum Common Header File
#include "PlumCommon.h"

// Class Definition
class CLiveCoreLog
{
public:
	static void LiveCoreLogExWrite(LPCSTR file, LONG line, LPCSTR lpcstr, ...);			// CLiveCoreLogEx (~д����־����)
	static void LiveCoreLogExWriteLine(LPCSTR file, LONG line, LPCSTR lpcstr, ...);		// CLiveCoreLogEx (~д����־����)(����)

public:
	static void LiveCoreLogExCreateLogFilePath();										// CLiveCoreLogEx (~������־�ļ�·��)
	static void LiveCoreLogExGetLogFilePath(char* pStr, int nSize);						// CLiveCoreLogEx (~��ȡ��־�ļ�·��)

protected:
	static void LiveCoreLogExGetComputerName();											// CLiveCoreLogEx (~��ȡ���������)
	static void LiveCoreLogExGetUserName();												// CLiveCoreLogEx (~��ȡ�û�����)
	static void LiveCoreLogExGetWindowsVersion();										// CLiveCoreLogEx (~��ȡWindows�汾)
};

#endif // !__LIVECORELOG_H_
