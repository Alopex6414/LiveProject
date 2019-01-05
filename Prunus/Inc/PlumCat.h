/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumCat.h
* @brief	This Program is PlumCat DLL Project.
* @author	alopex
* @version	v1.01a
* @date		2018-07-02	v1.00a	alopex	Create Project.
* @date		2018-10-23	v1.01a	alopex	Alter Call Method.
*/
#pragma once

#ifndef __PLUMCAT_H_
#define __PLUMCAT_H_

//Include Windows Header File
#include <WinSock2.h>
#include <HttpExt.h>
#include <windef.h>
#include <wincrypt.h>
#include <nb30.h>

//Include C/C++ Run Header File
#include <stdio.h>
#include <stdlib.h>

//Include Crypt File
#include "PlumCipherA.h"
#include "PlumCrypt.h"
#include "PlumPack.h"

//Include Common Library
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "netapi32.lib")

//Macro Definition
#ifdef	PRUNUS_EXPORTS
#define PLUMCAT_API	__declspec(dllexport)
#else
#define PLUMCAT_API	__declspec(dllimport)
#endif

#define PLUMCAT_CALLMETHOD	__stdcall

//Struct Definition

//Class Definition
class PLUMCAT_API CPlumCat
{
private:
	CHAR m_chMAC[MAX_PATH];

protected:
	UCHAR PLUMCAT_CALLMETHOD PlumCatGetMAC();

public:
	UCHAR PLUMCAT_CALLMETHOD PlumCatGetMAC(UCHAR chMAC[6]);

public:
	CPlumCat();
	~CPlumCat();

	virtual void PLUMCAT_CALLMETHOD PlumCatEnCryptMAC(const char* pFile);
	virtual void PLUMCAT_CALLMETHOD PlumCatEnCryptMACByPath(const char* pPath);
	virtual BOOL PLUMCAT_CALLMETHOD PlumCatDeCryptMAC(const char* pFile);
	virtual BOOL PLUMCAT_CALLMETHOD PlumCatDeCryptMACbyPath(const char* pPath);

	virtual void PLUMCAT_CALLMETHOD PlumCatEnCryptMAC(char* pMAC, int nSize, const char* pFile);
	virtual void PLUMCAT_CALLMETHOD PlumCatEnCryptMACByPath(char* pMAC, int nSize, const char* pPath);

};


#endif // !__PLUMCAT_H_

