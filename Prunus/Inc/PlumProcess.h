/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumProcess.h
* @brief	This Program is PlumProcess DLL Project.
* @author	Alopex/Helium
* @version	v1.02a
* @date		2018-1-30	v1.00a	alopex	Create Project.
* @date		2018-7-13	v1.01a	alopex	Add Static Function.
* @date		2018-10-23	v1.02a	alopex	Alter Call Method.
*/
#pragma once

#ifndef __PLUMPROCESS_H_
#define __PLUMPROCESS_H_

//Include Plum Common Header File
#include "PlumCommon.h"

//Macro Definition
#ifdef PRUNUS_EXPORTS
#define PLUMPROCESS_API	__declspec(dllexport)
#else
#define PLUMPROCESS_API	__declspec(dllimport)
#endif

#define PLUMPROCESS_CALLMETHOD __stdcall

//Class Definition
class PLUMPROCESS_API CPlumProcess
{
private:
	DWORD m_dwProcessID;	//进程ID
	DWORD m_dwThreadID;		//线程ID
	HANDLE m_hProcess;		//进程句柄
	HANDLE m_hThread;		//线程句柄

public:
	static BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessExA(const char* strProcessName);		//PlumProcess启动进程(进程名称)(ASCII)
	static BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessExW(const wchar_t* strProcessName);	//PlumProcess启动进程(进程名称)(Unicode)
	static BOOL PLUMPROCESS_CALLMETHOD PlumProcessIsProcessExistExA(const char* strProcessName);	//PlumProcess检测进程是否存在(进程名称)(ASCII)
	static BOOL PLUMPROCESS_CALLMETHOD PlumProcessIsProcessExistExW(const wchar_t* strProcessName);	//PlumProcess检测进程是否存在(进程名称)(Unicode)

public:
	CPlumProcess();			//构造
	~CPlumProcess();		//析构

	virtual DWORD PLUMPROCESS_CALLMETHOD PlumProcessGetProcessID(void) const;					//获取进程ID
	virtual DWORD PLUMPROCESS_CALLMETHOD PlumProcessGetThreadID(void) const;					//获取线程ID
	virtual HANDLE PLUMPROCESS_CALLMETHOD PlumProcessGetProcessHandle(void) const;				//获取进程句柄
	virtual HANDLE PLUMPROCESS_CALLMETHOD PlumProcessGetThreadHandle(void) const;				//获取线程句柄

	virtual void PLUMPROCESS_CALLMETHOD PlumProcessSetProcessID(DWORD dwProcessID);				//设置进程ID(不可用)
	virtual void PLUMPROCESS_CALLMETHOD PlumProcessSetThreadID(DWORD dwThreadID);				//获取线程ID(不可用)

	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessA(const char* strProcessName);			//PlumProcess启动进程(进程名称)(ASCII)
	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessW(const wchar_t* strProcessName);		//PlumProcess启动进程(进程名称)(Unicode)
	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessNoCloseA(const char* strProcessName);	//PlumProcess启动进程不关闭进程线程句柄(进程名称)(ASCII)
	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessNoCloseW(const wchar_t* strProcessName);	//PlumProcess启动进程不关闭进程线程句柄(进程名称)(Unicode)

	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessA(const char* strProcessName, const char* strProcessCmd);		//PlumProcess启动进程(进程名称)(命令行)(ASCII)
	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessNoCloseA(const char* strProcessName, const char* strProcessCmd);	//PlumProcess启动进程(进程名称)(命令行)(ASCII)

	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessIsProcessExistA(const char* strProcessName);		//PlumProcess检测进程是否存在(进程名称)(ASCII)
	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessIsProcessExistW(const wchar_t* strProcessName);	//PlumProcess检测进程是否存在(进程名称)(Unicode)
};

#endif // !__PLUMPROCESS_H_
