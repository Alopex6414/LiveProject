/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumPack.h
* @brief	This Program is PlumPack DLL Project.
* @author	Alopex/Helium
* @version	v1.04a
* @date		2017-12-16	v1.00a	alopex	Create Project.
* @date		2017-12-23	v1.01a	alopex	Add Function UnPack to Memory.
* @date		2018-01-16	v1.02a	alopex	Add For PackerMaker Function.
* @date		2018-07-05	v1.03a	alopex	Add Function Crypt Cat Function.
* @date		2018-10-23	v1.04a	alopex	Alter Call Method.
*/
#pragma once

#ifndef __PLUMPACK_H_
#define __PLUMPACK_H_

//Include Plum Common Header File
#include "PlumCommon.h"

//Include Crypt File
#include "PlumCipherA.h"
#include "PlumCrypt.h"

//Macro Definition
#ifdef	PRUNUS_EXPORTS
#define PLUMPACK_API	__declspec(dllexport)
#else
#define PLUMPACK_API	__declspec(dllimport)
#endif

#define PLUMPACK_CALLMETHOD	__stdcall

//Struct Definition
typedef struct
{
	char cFileName[24];
	char cCodeAuthor[8];
	DWORD dwFileAllNum;
	DWORD dwFileAllSize;
} PlumPackInfo;

//Class Definition
class PLUMPACK_API CPlumPack
{
private:
	CPlumCrypt* m_pCryptArr;
	int m_nArrSize;


public:
	CPlumPack();
	virtual ~CPlumPack();

	//访问
	virtual void PLUMPACK_CALLMETHOD PlumGetArray(CPlumCrypt** ppCryptArr, int* pArrSize) const;

	//AES Pack(AES封包/解包)
	virtual void PLUMPACK_CALLMETHOD PlumPackFileA(const char* pSrcArr[], int nArrSize, const char* pDest);
	virtual void PLUMPACK_CALLMETHOD PlumPackFileA(const char* pSrcArr[], int nArrSize, const char* pDest, DWORD* pLuckyArr);
	virtual void PLUMPACK_CALLMETHOD PlumUnPackFileA(const char* pSrc, const char* pDest);
	virtual void PLUMPACK_CALLMETHOD PlumUnPackFileA(const char* pSrc);

	virtual void PLUMPACK_CALLMETHOD PlumPackFileExtractFromMemoryA(const void * pArray, int nSize, const char * pDest, DWORD * pLuckyArr);
	virtual void PLUMPACK_CALLMETHOD PlumUnPackFileStoreInMemoryA(const char * pSrc, const void * pValArr, DWORD dwValSize);
	virtual void PLUMPACK_CALLMETHOD PlumUnPackOneFileStoreInMemoryA(const char * pSrc, const char * pFileName, const void * pValArr, DWORD dwValSize);

	//AES Packer(PackerMaker)
	virtual void PLUMPACK_CALLMETHOD PlumPackFilePackerA(const char* pSrcArr[], int nArrSize, const char* pDest, int* pCount);
	virtual void PLUMPACK_CALLMETHOD PlumPackFilePackerA(const char* pSrcArr[], int nArrSize, const char* pDest, DWORD* pLuckyArr, int* pCount);
	virtual void PLUMPACK_CALLMETHOD PlumUnPackFilePackerA(const char* pSrc, const char* pDest, int* pSize, int* pCount);
};

#endif