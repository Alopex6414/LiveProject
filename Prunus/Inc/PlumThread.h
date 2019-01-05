/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumThread.h
* @brief	This Program is PlumThread DLL Project.
* @author	Alopex/Helium
* @version	v1.02a
* @date		2018-1-14	v1.00a	alopex	Create Project.
* @date		2018-7-20	v1.01a	alopex	Modify Call Mode.
* @date		2018-10-23	v1.02a	alopex	Alter Call Method.
*/
#pragma once

#ifndef __PLUMTHREAD_H_
#define __PLUMTHREAD_H_

//Include Plum Common Header File
#include "PlumCommon.h"

//Macro Definition
#ifdef PRUNUS_EXPORTS
#define PLUMTHREAD_API	__declspec(dllexport)
#else
#define PLUMTHREAD_API	__declspec(dllimport)
#endif

#define PLUMTHREAD_CALLMETHOD	__stdcall

//Class Definition
//CPlumThreadBase����
class PLUMTHREAD_API CPlumThreadBase
{
private:

public:
	CPlumThreadBase();													//����
	virtual ~CPlumThreadBase();											//����
	virtual void PLUMTHREAD_CALLMETHOD PlumThreadRun() = 0;				//���麯��
};

//CPlumThread������
class PLUMTHREAD_API CPlumThread :public CPlumThreadBase
{
private:
	HANDLE m_hThread;													//�߳̾��
	DWORD m_dwThreadID;													//�̺߳�
	volatile bool m_bThreadRun;											//�߳�����
	CPlumThreadBase* m_pThreadBase;										//�̻߳���ָ��

private:
	static DWORD PLUMTHREAD_CALLMETHOD PlumThreadProc(LPVOID pThreadPara);//�̴߳�����(��̬)

public:
	CPlumThread();														//����
	~CPlumThread();														//����
	CPlumThread(CPlumThreadBase* pThreadBase);							//����

	DWORD PLUMTHREAD_CALLMETHOD PlumThreadGetID() const;								//�߳�ID��ȡ

	virtual bool PLUMTHREAD_CALLMETHOD PlumThreadInit(bool bSuspend = false);			//�̳߳�ʼ��(����:true)
	virtual void PLUMTHREAD_CALLMETHOD PlumThreadSetPriority(int nPriority);			//�߳��������ȼ�(THREAD_PRIORITY_ABOVE_NORMAL)
	virtual void PLUMTHREAD_CALLMETHOD PlumThreadRun();									//�߳�����(��д)
	virtual void PLUMTHREAD_CALLMETHOD PlumThreadJoin(int nTimeOut = -1);				//�̵߳ȴ�����
	virtual void PLUMTHREAD_CALLMETHOD PlumThreadResume();								//�ָ̻߳�
	virtual void PLUMTHREAD_CALLMETHOD PlumThreadSuspend();								//�̹߳���
	virtual bool PLUMTHREAD_CALLMETHOD PlumThreadTerminate(DWORD dwExitCode);			//�߳���ֹ
	virtual void PLUMTHREAD_CALLMETHOD PlumThreadExit();								//�߳��˳�
};

#endif