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
	DWORD m_dwProcessID;	//����ID
	DWORD m_dwThreadID;		//�߳�ID
	HANDLE m_hProcess;		//���̾��
	HANDLE m_hThread;		//�߳̾��

public:
	static BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessExA(const char* strProcessName);		//PlumProcess��������(��������)(ASCII)
	static BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessExW(const wchar_t* strProcessName);	//PlumProcess��������(��������)(Unicode)
	static BOOL PLUMPROCESS_CALLMETHOD PlumProcessIsProcessExistExA(const char* strProcessName);	//PlumProcess�������Ƿ����(��������)(ASCII)
	static BOOL PLUMPROCESS_CALLMETHOD PlumProcessIsProcessExistExW(const wchar_t* strProcessName);	//PlumProcess�������Ƿ����(��������)(Unicode)

public:
	CPlumProcess();			//����
	~CPlumProcess();		//����

	virtual DWORD PLUMPROCESS_CALLMETHOD PlumProcessGetProcessID(void) const;					//��ȡ����ID
	virtual DWORD PLUMPROCESS_CALLMETHOD PlumProcessGetThreadID(void) const;					//��ȡ�߳�ID
	virtual HANDLE PLUMPROCESS_CALLMETHOD PlumProcessGetProcessHandle(void) const;				//��ȡ���̾��
	virtual HANDLE PLUMPROCESS_CALLMETHOD PlumProcessGetThreadHandle(void) const;				//��ȡ�߳̾��

	virtual void PLUMPROCESS_CALLMETHOD PlumProcessSetProcessID(DWORD dwProcessID);				//���ý���ID(������)
	virtual void PLUMPROCESS_CALLMETHOD PlumProcessSetThreadID(DWORD dwThreadID);				//��ȡ�߳�ID(������)

	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessA(const char* strProcessName);			//PlumProcess��������(��������)(ASCII)
	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessW(const wchar_t* strProcessName);		//PlumProcess��������(��������)(Unicode)
	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessNoCloseA(const char* strProcessName);	//PlumProcess�������̲��رս����߳̾��(��������)(ASCII)
	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessNoCloseW(const wchar_t* strProcessName);	//PlumProcess�������̲��رս����߳̾��(��������)(Unicode)

	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessA(const char* strProcessName, const char* strProcessCmd);		//PlumProcess��������(��������)(������)(ASCII)
	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessStartProcessNoCloseA(const char* strProcessName, const char* strProcessCmd);	//PlumProcess��������(��������)(������)(ASCII)

	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessIsProcessExistA(const char* strProcessName);		//PlumProcess�������Ƿ����(��������)(ASCII)
	virtual BOOL PLUMPROCESS_CALLMETHOD PlumProcessIsProcessExistW(const wchar_t* strProcessName);	//PlumProcess�������Ƿ����(��������)(Unicode)
};

#endif // !__PLUMPROCESS_H_
