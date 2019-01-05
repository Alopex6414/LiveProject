/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumCipherA.h
* @brief	This Program is PlumCipherA DLL Project.
* @author	Alopex/Helium
* @version	v1.01a
* @date		2017-12-13	v1.00a	alopex	Create Project.
* @date		2018-10-23	v1.01a	alopex	Alter Call Method.
*/
#pragma once

#ifndef __PLUMCIPHERA_H_
#define __PLUMCIPHERA_H_

//Include Plum Common Header File
#include "PlumCommon.h"

//Macro Definition
#ifdef	PRUNUS_EXPORTS
#define PLUMCRYPT_API	__declspec(dllexport)
#else
#define PLUMCRYPT_API	__declspec(dllimport)
#endif

#define PLUMCRYPT_CALLMETHOD	__stdcall

//Class Definition
class PLUMCRYPT_API CPlumCipherA
{
private:
	unsigned char m_cSBox[256];
	unsigned char m_cInvSBox[256];
	unsigned char m_cExMatrix[11][4][4];

public:
	CPlumCipherA();														//构造
	~CPlumCipherA();													//析构

	CPlumCipherA(unsigned char* Key);									//构造

	void PLUMCRYPT_CALLMETHOD KeyExMatrix(unsigned char* Key, unsigned char Ex[][4][4]);
	unsigned char PLUMCRYPT_CALLMETHOD FFMul(unsigned char Var1, unsigned char Var2);

	void PLUMCRYPT_CALLMETHOD SubBytes(unsigned char* pState);
	void PLUMCRYPT_CALLMETHOD ShiftRows(unsigned char State[][4]);
	void PLUMCRYPT_CALLMETHOD MixColumns(unsigned char State[][4]);
	void PLUMCRYPT_CALLMETHOD AddRoundKey(unsigned char* pState, unsigned char* pK);
	
	void PLUMCRYPT_CALLMETHOD InvSubBytes(unsigned char* pState);
	void PLUMCRYPT_CALLMETHOD InvShiftRows(unsigned char State[][4]);
	void PLUMCRYPT_CALLMETHOD InvMixColumns(unsigned char State[][4]);
	
	void PLUMCRYPT_CALLMETHOD EnCipher(const unsigned char* pSrc, unsigned char* pDest);	//加密数组Array[4][4]	
	void PLUMCRYPT_CALLMETHOD DeCipher(const unsigned char* pSrc, unsigned char* pDest);	//解密数组Array[4][4]
	void PLUMCRYPT_CALLMETHOD EnCrypt(const void* pSrc, void* pDest, int nLen);				//加密数组
	void PLUMCRYPT_CALLMETHOD DeCrypt(const void* pSrc, void* pDest, int nLen);				//解密数组
};

#endif