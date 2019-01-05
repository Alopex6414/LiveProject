/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CThreadSafe.h
* @brief	This File is CThreadSafe File.
* @author	alopex
* @version	v1.00a
* @date		2018-10-08	v1.00a	alopex	Create This File.
*/
#pragma once

#ifndef __THREADSAFE_H_
#define __THREADSAFE_H_

//Include Windows Header File
#include <Windows.h>

//Class Definition
class CThreadSafe
{
private:
	CRITICAL_SECTION* m_pCriticalSection;
	bool m_bThreadSafe;

public:
	CThreadSafe(const CRITICAL_SECTION* pCriticalSection, const bool bThreadSafe = true);
	~CThreadSafe();
};

#endif // !__THREADSAFE_H_