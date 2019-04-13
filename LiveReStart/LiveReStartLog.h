/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveReStartLog.h
* @brief	This Program is LiveReStart Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-06
*/
#pragma once

#ifndef __LIVERESTARTLOG_H_
#define __LIVERESTARTLOG_H_

// Include Plum Common Header File
#include "PlumCommon.h"

// Class Definition
class CLiveReStartLog
{
public:
	static void LiveReStartLogExWrite(LPCSTR file, LONG line, LPCSTR lpcstr, ...);			// CLiveReStartLogEx (~写入日志内容)
	static void LiveReStartLogExWriteLine(LPCSTR file, LONG line, LPCSTR lpcstr, ...);		// CLiveReStartLogEx (~写入日志内容)(换行)

public:
	static void LiveReStartLogExCreateLogFilePath();										// CLiveReStartLogEx (~创建日志文件路径)
	static void LiveReStartLogExGetLogFilePath(char* pStr, int nSize);						// CLiveReStartLogEx (~获取日志文件路径)

protected:
	static void LiveReStartLogExGetComputerName();											// CLiveReStartLogEx (~获取计算机名称)
	static void LiveReStartLogExGetUserName();												// CLiveReStartLogEx (~获取用户名称)
	static void LiveReStartLogExGetWindowsVersion();										// CLiveReStartLogEx (~获取Windows版本)

};

#endif // !__LiveReStartLOG_H_

