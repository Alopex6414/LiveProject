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
	static void LiveReStartLogExWrite(LPCSTR file, LONG line, LPCSTR lpcstr, ...);			// CLiveReStartLogEx (~д����־����)
	static void LiveReStartLogExWriteLine(LPCSTR file, LONG line, LPCSTR lpcstr, ...);		// CLiveReStartLogEx (~д����־����)(����)

public:
	static void LiveReStartLogExCreateLogFilePath();										// CLiveReStartLogEx (~������־�ļ�·��)
	static void LiveReStartLogExGetLogFilePath(char* pStr, int nSize);						// CLiveReStartLogEx (~��ȡ��־�ļ�·��)

protected:
	static void LiveReStartLogExGetComputerName();											// CLiveReStartLogEx (~��ȡ���������)
	static void LiveReStartLogExGetUserName();												// CLiveReStartLogEx (~��ȡ�û�����)
	static void LiveReStartLogExGetWindowsVersion();										// CLiveReStartLogEx (~��ȡWindows�汾)

};

#endif // !__LiveReStartLOG_H_

