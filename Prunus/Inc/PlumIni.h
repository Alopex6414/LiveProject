/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumIni.h
* @brief	This Program is PlumIni DLL Project.
* @author	Alopex/Helium
* @version	v1.03a
* @date		2018-01-17	v1.00a	alopex	Create Project.
* @date		2018-07-30	v1.02a	alopex	Add Call Mode.
* @date		2018-10-23	v1.03a	alopex	Alter Call Method.
*/
#pragma once

#ifndef __PLUMINI_H_
#define __PLUMINI_H_

//Include Plum Common Header File
#include "PlumCommon.h"

//Macro Definition
#ifdef	PRUNUS_EXPORTS
#define PLUMINI_API	__declspec(dllexport)
#else
#define PLUMINI_API	__declspec(dllimport)
#endif

#define PLUMINI_CALLMETHOD	__stdcall

//Class Definition
class PLUMINI_API CPlumIni
{
public:
	CPlumIni();
	~CPlumIni();

	static bool PLUMINI_CALLMETHOD PlumIniReadStringKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, char* pStrDefault, char** ppStrValue);
	static bool PLUMINI_CALLMETHOD PlumIniReadIntKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, int nDefault, int* pValue);
	static bool PLUMINI_CALLMETHOD PlumIniWriteStringKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, char* pStrValue);
	static bool PLUMINI_CALLMETHOD PlumIniWriteIntKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, int nValue);
};

#endif