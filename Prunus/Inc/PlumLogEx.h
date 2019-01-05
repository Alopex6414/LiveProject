/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumLogEx.h
* @brief	This Program is PlumLogEx DLL Project.
* @author	Alopex/Helium
* @version	v1.02a
* @date		2018-10-22	v1.00a	alopex	Create Project.
* @date		2018-10-23	v1.01a	alopex	Alter Call Method.
* @date		2018-12-05	v1.02a	alopex	Alter Bugs File Name & Print Line.
*/
#pragma once

#ifndef __PLUMLOGEX_H_
#define __PLUMLOGEX_H_

//Include Plum Common Header File
#include "PlumCommon.h"

//Macro Definition
#ifdef	PRUNUS_EXPORTS
#define PLUMLOGEX_API	__declspec(dllexport)
#else
#define PLUMLOGEX_API	__declspec(dllimport)
#endif

#define PLUMLOGEX_CALLMETHOD	__stdcall

#define PLUMLOGEX(file, line, Str)	CPlumLogEx::PlumLogExWriteLine(file, line, Str)

//Class Definition
class PLUMLOGEX_API CPlumLogEx
{
public:
	CPlumLogEx();			// CPlumLogEx (~构造函数)
	~CPlumLogEx();			// CPlumLogEx (~析构函数)

public:
	static void PLUMLOGEX_CALLMETHOD PlumLogExWrite(LPCSTR file, LONG line, LPCSTR lpcstr, ...);			// CPlumLogEx (~写入日志内容)
	static void PLUMLOGEX_CALLMETHOD PlumLogExWriteLine(LPCSTR file, LONG line, LPCSTR lpcstr, ...);		// CPlumLogEx (~写入日志内容)(换行)

public:
	static void PLUMLOGEX_CALLMETHOD PlumLogExCreateLogFilePath();											// CPlumLogEx (~创建日志文件路径)
	static void PLUMLOGEX_CALLMETHOD PlumLogExGetLogFilePath(char* pStr, int nSize);						// CPlumLogEx (~获取日志文件路径)

protected:
	static void PLUMLOGEX_CALLMETHOD PlumLogExGetComputerName();											// CPlumLogEx (~获取计算机名称)
	static void PLUMLOGEX_CALLMETHOD PlumLogExGetUserName();												// CPlumLogEx (~获取用户名称)
	static void PLUMLOGEX_CALLMETHOD PlumLogExGetWindowsVersion();											// CPlumLogEx (~获取Windows版本)

};


#endif // !__PLUMLOGEX_H_

