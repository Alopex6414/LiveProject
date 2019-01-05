/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CRosaSerial.h
* @brief	This File is RosaSerial Header File.
* @author	alopex
* @version	v1.00a
* @date		2018-09-17	v1.00a	alopex	Create This File.
*/
#pragma once

#ifndef __ROSASERIAL_H_
#define __ROSASERIAL_H_

//Include Window Header File
#include <Windows.h>

//Include C/C++ Header File
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
#include <map>
#include <vector>
#include <process.h>

//Include C/C++ Library
#pragma comment(lib, "WinMM.lib")

using namespace std;

//Macro Definition
#ifdef  ROSA_EXPORTS
#define ROSASERIAL_API	__declspec(dllexport)
#else
#define ROSASERIAL_API	__declspec(dllimport)
#endif

#define ROSASERIAL_CALLMODE	__stdcall

#define SERIALPORT_COMM_INPUT_BUFFER_SIZE	4096	// ����ͨ�����뻺������С
#define SERIALPORT_COMM_OUTPUT_BUFFER_SIZE	4096	// ����ͨ�������������С

//Template Release
template<class T>
void SafeDelete(T*& t)
{
	if (nullptr != t)
	{
		delete t;
		t = nullptr;
	}
}

template<class T>
void SafeDeleteArray(T*& t)
{
	if (nullptr != t)
	{
		delete[] t;
		t = nullptr;
	}
}

template<class T>
void SafeRelease(T*& t)
{
	if (nullptr != t)
	{
		t->Release();
		t = nullptr;
	}
}

//Struct Definition
typedef struct
{
	CHAR chPort[MAX_PATH];	// ���ں�
	DWORD dwBaudRate;		// ���ڲ�����
	BYTE byDataBits;		// ��������λ
	BYTE byStopBits;		// ����ֹͣλ
	BYTE byCheckBits;		// ����У��λ
}S_SERIALPORT_PROPERTY, *LPS_SERIALPORT_PROPERTY;

//Class Definition
class ROSASERIAL_API CRosaSerial
{
private:
	HANDLE m_hCOM;			// CRosaSerial SerialPort Handle(���ھ��)
	HANDLE m_hListenThread;	// CRosaSerial SerialPort Listen Thread Handle(���ڼ����߳̾��)

private:
	OVERLAPPED m_ovWrite;	// CRosaSerial OverLapped Write
	OVERLAPPED m_ovRead;	// CRosaSerial OverLapped Read
	OVERLAPPED m_ovWait;	// CRosaSerial OverLapped Wait

public:
	volatile bool m_bOpen;	// CRosaSerial Open Flag(���ڴ򿪱�־)
	volatile bool m_bRecv;	// CRosaSerial Recv Flag(���ڽ��ձ�־)

public:
	CRITICAL_SECTION m_csCOMSync;	// CRosaSerial Critical Section Sync(�����첽�����ٽ���)

public:
	map<int, string> m_mapEnumCOM;	// CRosaSerial Enum SerialPort Map(����ö���б�)

// ��������
public:
	unsigned char m_chSendBuf[SERIALPORT_COMM_INPUT_BUFFER_SIZE];
	unsigned char m_chRecvBuf[SERIALPORT_COMM_OUTPUT_BUFFER_SIZE];
	DWORD m_dwSendCount;
	DWORD m_dwRecvCount;

public:
	void ROSASERIAL_CALLMODE EnumSerialPort();	// CRosaSerial ö�ٴ���

protected:
	bool ROSASERIAL_CALLMODE CRosaSerialCreate(const char* szPort);						// CRosaSerial �򿪴���(��������)
	bool ROSASERIAL_CALLMODE CRosaSerialConfig(S_SERIALPORT_PROPERTY sCommProperty);	// CRosaSerial ���ô���

protected:
	bool ROSASERIAL_CALLMODE CRosaSerialInit(S_SERIALPORT_PROPERTY sCommProperty);		// CRosaSerial ��ʼ������
	bool ROSASERIAL_CALLMODE CRosaSerialInitListen();									// CRosaSerial ��ʼ�����ڼ���
	void ROSASERIAL_CALLMODE CRosaSerialClose();										// CRosaSerial �رմ���
	void ROSASERIAL_CALLMODE CRosaSerialCloseListen();									// CRosaSerial �رմ��ڼ���

public:
	CRosaSerial();			// CRosaSerial ���캯��
	~CRosaSerial();			// CRosaSerial ��������

	bool ROSASERIAL_CALLMODE CRosaSerialGetStatus() const;			// CRosaSerial ��ȡ����״̬
	bool ROSASERIAL_CALLMODE CRosaSerialGetRecv() const;			// CRosaSerial ��ȡ���ձ�־
	void ROSASERIAL_CALLMODE CRosaSerialSetRecv(bool bRecv);		// CRosaSerial ���ý��ձ�־

	void ROSASERIAL_CALLMODE CRosaSerialSetSendBuf(unsigned char* pBuff, int nSize, DWORD& dwSendCount);	// CRosaSerial ���÷��ͻ���
	void ROSASERIAL_CALLMODE CRosaSerialGetRecvBuf(unsigned char* pBuff, int nSize, DWORD& dwRecvCount);	// CRosaSerial ��ȡ���ջ���

	bool ROSASERIAL_CALLMODE CRosaSerialOpenPort(S_SERIALPORT_PROPERTY sCommProperty);	// CRosaSerial �򿪴���
	void ROSASERIAL_CALLMODE CRosaSerialClosePort();									// CRosaSerial �رմ���

	bool ROSASERIAL_CALLMODE OnTranslateBuffer();										// CRosaSerial ���ڷ�������
	static unsigned int CALLBACK OnReceiveBuffer(LPVOID lpParameters);	// CRosaSerial ���ڽ����߳�

};

#endif // !__ROSASERIAL_H_

