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
	static void LiveInLogExWrite(LPCSTR file, LONG line, LPCSTR lpcstr, ...);			// CLiveInLogEx (~д����־����)
	static void LiveInLogExWriteLine(LPCSTR file, LONG line, LPCSTR lpcstr, ...);		// CLiveInLogEx (~д����־����)(����)

public:
	static void LiveInLogExCreateLogFilePath();											// CLiveInLogEx (~������־�ļ�·��)
	static void LiveInLogExGetLogFilePath(char* pStr, int nSize);						// CLiveInLogEx (~��ȡ��־�ļ�·��)

protected:
	static void LiveInLogExGetComputerName();											// CLiveInLogEx (~��ȡ���������)
	static void LiveInLogExGetUserName();												// CLiveInLogEx (~��ȡ�û�����)
	static void LiveInLogExGetWindowsVersion();											// CLiveInLogEx (~��ȡWindows�汾)

};

#endif // !__LIVEINLOG_H_

