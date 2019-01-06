/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		ConvallariaLua.h
* @brief	This Program is C/C++ -- Lua Script Project.
* @author	alopex
* @version	v1.02a
* @date		2018-08-27	v1.00a alopex Create this file.
* @date		2018-08-30	v1.01a alopex Add function.
* @date		2018-09-02	v1.02a alopex Add function.
*/
#pragma once

#ifndef __CONVALLARIALUA_H_
#define __CONVALLARIALUA_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Running Header File
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <mmreg.h>
#include <wchar.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>

#include <iostream>

//Include Lua Common Header File
#include "lua.hpp"

//Include Lua Library
#pragma comment(lib, "liblua")

//Macro Definition
#ifdef CONVALLARIA_EXPORTS
#define CONVALLARIA_API	__declspec(dllexport)
#else
#define CONVALLARIA_API	__declspec(dllimport)
#endif

#define CONVALLARIA_CALLMETHOD	__stdcall

//Class Definition
class CONVALLARIA_API CConvallariaLua
{
private:
	lua_State * L;

private:
	char m_chFile[MAX_PATH];
	char m_chPath[MAX_PATH];

public:
	CConvallariaLua(const char* szFile);			//CConvallariaLua Construction(���캯��)
	~CConvallariaLua();								//CConvallariaLua Destruction(��������)

	lua_State* CONVALLARIA_CALLMETHOD CConvallariaLua_GetLua() const;		//CConvallariaLua Get Lua(��ȡLua�����)

	// Init
	BOOL CONVALLARIA_CALLMETHOD ConvallariaLua_Init();						//CConvallariaLua Initialize(��ʼ������)

	// Global
	void CONVALLARIA_CALLMETHOD ConvallariaLua_GetGlobal_Int(const char* szVar, int& nValue);							//CConvallariaLua Get Global Int(��ȡȫ������)
	void CONVALLARIA_CALLMETHOD ConvallariaLua_GetGlobal_Long(const char* szVar, long& lValue);							//CConvallariaLua Get Global Long(��ȡȫ�ֳ�����)
	void CONVALLARIA_CALLMETHOD ConvallariaLua_GetGlobal_LongLong(const char* szVar, long long& llValue);				//CConvallariaLua Get Global Long(��ȡȫ�ֳ�������)
	void CONVALLARIA_CALLMETHOD ConvallariaLua_GetGlobal_Float(const char* szVar, float& fValue);						//CConvallariaLua Get Global Float(��ȡȫ�ָ�����)
	void CONVALLARIA_CALLMETHOD ConvallariaLua_GetGlobal_Double(const char* szVar, double& dValue);						//CConvallariaLua Get Global Double(��ȡȫ��˫����)
	void CONVALLARIA_CALLMETHOD ConvallariaLua_GetGlobal_String(const char* szVar, const char* pStr, int nSize);		//CConvallariaLua Get Global String(��ȡȫ���ַ���)

	// Table
	void CONVALLARIA_CALLMETHOD ConvallariaLua_GetTable_String(const char* szVar1, const char* szVar2, const char* pStr, int nSize);			//CConvallariaLua Get Table String(��ȡ���ַ���)

	// Function
	void CONVALLARIA_CALLMETHOD ConvallariaLua_CallFunc(const char* szVar, int nMessageID, LPVOID pTransBuf, int nTransSize, LPVOID pRecevBuf, int nRecevSize);			// CConvallariaLua Call Function(����lua����)<��չ><API>

};

#endif // !__CONVALLARIALUA_H_
