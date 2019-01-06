/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveInlog.h
* @brief	This Program is LiveIn Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-06
*/
#pragma once

#ifndef __LIVEINLOG_H_
#define __LIVEINLOG_H_

// Include Plum Common Header File
#include "PlumCommon.h"

// Class Definition
class CLiveInLog
{
public:
	static void LiveInLogExWrite(LPCSTR file, LONG line, LPCSTR lpcstr, ...);			// CLiveInLogEx (~写入日志内容)
	static void LiveInLogExWriteLine(LPCSTR file, LONG line, LPCSTR lpcstr, ...);		// CLiveInLogEx (~写入日志内容)(换行)

public:
	static void LiveInLogExCreateLogFilePath();											// CLiveInLogEx (~创建日志文件路径)
	static void LiveInLogExGetLogFilePath(char* pStr, int nSize);						// CLiveInLogEx (~获取日志文件路径)

protected:
	static void LiveInLogExGetComputerName();											// CLiveInLogEx (~获取计算机名称)
	static void LiveInLogExGetUserName();												// CLiveInLogEx (~获取用户名称)
	static void LiveInLogExGetWindowsVersion();											// CLiveInLogEx (~获取Windows版本)

};

#endif // !__LIVEINLOG_H_

