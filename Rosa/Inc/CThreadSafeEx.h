/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CThreadSafeEx.h
* @brief	This File is CThreadSafeEx File.
* @author	alopex
* @version	v1.00a
* @date		2018-10-08	v1.00a	alopex	Create This File.
*/
#pragma once

#ifndef __THREADSAFEEX_H_
#define __THREADSAFEEX_H_

#include <Windows.h>

class CThreadSafeEx
{
private:
	CRITICAL_SECTION m_CriticalSection;

public:
	CRITICAL_SECTION* GetCriticalSection();

public:
	CThreadSafeEx();
	~CThreadSafeEx();

	void Enter();
	void Leave();
};

#endif // !__THREADSAFEEX_H_

