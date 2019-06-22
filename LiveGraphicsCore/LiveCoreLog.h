/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCoreLog.h
* @brief	This Program is LiveGraphicsCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-06-22
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
	static void LiveCoreLogExWrite(LPCSTR file, LONG line, LPCSTR lpcstr, ...);			// CLiveCoreLogEx (~写入日志内容)
	static void LiveCoreLogExWriteLine(LPCSTR file, LONG line, LPCSTR lpcstr, ...);		// CLiveCoreLogEx (~写入日志内容)(换行)

public:
	static void LiveCoreLogExCreateLogFilePath();										// CLiveCoreLogEx (~创建日志文件路径)
	static void LiveCoreLogExGetLogFilePath(char* pStr, int nSize);						// CLiveCoreLogEx (~获取日志文件路径)

protected:
	static void LiveCoreLogExGetComputerName();											// CLiveCoreLogEx (~获取计算机名称)
	static void LiveCoreLogExGetUserName();												// CLiveCoreLogEx (~获取用户名称)
	static void LiveCoreLogExGetWindowsVersion();										// CLiveCoreLogEx (~获取Windows版本)
};

#endif // !__LIVECORELOG_H_
