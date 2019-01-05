/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumPath.h
* @brief	This Program is PlumPath DLL Project.
* @author	Alopex/Helium
* @version	v1.02a
* @date		2018-01-18	v1.00a	alopex	Create Project.
* @date		2018-07-10	v1.01a	alopex	Add Function.
* @date		2018-10-23	v1.02a	alopex	Alter Call Method.
*/
#pragma once

#ifndef __PLUMPATH_H_
#define __PLUMPATH_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Run Header File
#include <stdio.h>
#include <stdlib.h>

//Include ATL Header File
#include <atlconv.h>

//Macro Definition
#ifdef	PRUNUS_EXPORTS
#define PLUMPATH_API	__declspec(dllexport)
#else
#define PLUMPATH_API	__declspec(dllimport)
#endif

#define PLUMPATH_CALLMETHOD	__stdcall

//Class Definition
class PLUMPATH_API CPlumPath
{
private:
	static BOOL PLUMPATH_CALLMETHOD PlumPathConvertA2W(const char* szArr, const wchar_t* wszArr, int nSize);
	static BOOL PLUMPATH_CALLMETHOD PlumPathConvertW2A(const wchar_t* wszArr, const char* szArr, int nSize);

public:
	CPlumPath();
	~CPlumPath();

	static BOOL PLUMPATH_CALLMETHOD PlumPathGetModulePathA(const char* szArr, int nSize);
	static BOOL PLUMPATH_CALLMETHOD PlumPathGetModulePathW(const wchar_t* wszArr, int nSize);
	static BOOL PLUMPATH_CALLMETHOD PlumPathGetLocalPathA(const char* szArr, int nSize);
	static BOOL PLUMPATH_CALLMETHOD PlumPathGetLocalPathW(const wchar_t* wszArr, int nSize);
	static BOOL PLUMPATH_CALLMETHOD PlumPathGetParentPathA(const char* szArr, int nSize, int nDeep);
	static BOOL PLUMPATH_CALLMETHOD PlumPathGetParentPathW(const wchar_t* wszArr, int nSize, int nDeep);
};

#endif