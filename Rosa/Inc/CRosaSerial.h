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

#define SERIALPORT_COMM_INPUT_BUFFER_SIZE	4096	// 串口通信输入缓冲区大小
#define SERIALPORT_COMM_OUTPUT_BUFFER_SIZE	4096	// 串口通信输出缓冲区大小

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
	CHAR chPort[MAX_PATH];	// 串口号
	DWORD dwBaudRate;		// 串口波特率
	BYTE byDataBits;		// 串口数据位
	BYTE byStopBits;		// 串口停止位
	BYTE byCheckBits;		// 串口校验位
}S_SERIALPORT_PROPERTY, *LPS_SERIALPORT_PROPERTY;

//Class Definition
class ROSASERIAL_API CRosaSerial
{
private:
	HANDLE m_hCOM;			// CRosaSerial SerialPort Handle(串口句柄)
	HANDLE m_hListenThread;	// CRosaSerial SerialPort Listen Thread Handle(串口监听线程句柄)

private:
	OVERLAPPED m_ovWrite;	// CRosaSerial OverLapped Write
	OVERLAPPED m_ovRead;	// CRosaSerial OverLapped Read
	OVERLAPPED m_ovWait;	// CRosaSerial OverLapped Wait

public:
	volatile bool m_bOpen;	// CRosaSerial Open Flag(串口打开标志)
	volatile bool m_bRecv;	// CRosaSerial Recv Flag(串口接收标志)

public:
	CRITICAL_SECTION m_csCOMSync;	// CRosaSerial Critical Section Sync(串口异步接收临界区)

public:
	map<int, string> m_mapEnumCOM;	// CRosaSerial Enum SerialPort Map(串口枚举列表)

// 串口数据
public:
	unsigned char m_chSendBuf[SERIALPORT_COMM_INPUT_BUFFER_SIZE];
	unsigned char m_chRecvBuf[SERIALPORT_COMM_OUTPUT_BUFFER_SIZE];
	DWORD m_dwSendCount;
	DWORD m_dwRecvCount;

public:
	void ROSASERIAL_CALLMODE EnumSerialPort();	// CRosaSerial 枚举串口

protected:
	bool ROSASERIAL_CALLMODE CRosaSerialCreate(const char* szPort);						// CRosaSerial 打开串口(串口名称)
	bool ROSASERIAL_CALLMODE CRosaSerialConfig(S_SERIALPORT_PROPERTY sCommProperty);	// CRosaSerial 配置串口

protected:
	bool ROSASERIAL_CALLMODE CRosaSerialInit(S_SERIALPORT_PROPERTY sCommProperty);		// CRosaSerial 初始化串口
	bool ROSASERIAL_CALLMODE CRosaSerialInitListen();									// CRosaSerial 初始化串口监听
	void ROSASERIAL_CALLMODE CRosaSerialClose();										// CRosaSerial 关闭串口
	void ROSASERIAL_CALLMODE CRosaSerialCloseListen();									// CRosaSerial 关闭串口监听

public:
	CRosaSerial();			// CRosaSerial 构造函数
	~CRosaSerial();			// CRosaSerial 析构函数

	bool ROSASERIAL_CALLMODE CRosaSerialGetStatus() const;			// CRosaSerial 获取串口状态
	bool ROSASERIAL_CALLMODE CRosaSerialGetRecv() const;			// CRosaSerial 获取接收标志
	void ROSASERIAL_CALLMODE CRosaSerialSetRecv(bool bRecv);		// CRosaSerial 设置接收标志

	void ROSASERIAL_CALLMODE CRosaSerialSetSendBuf(unsigned char* pBuff, int nSize, DWORD& dwSendCount);	// CRosaSerial 设置发送缓冲
	void ROSASERIAL_CALLMODE CRosaSerialGetRecvBuf(unsigned char* pBuff, int nSize, DWORD& dwRecvCount);	// CRosaSerial 获取接收缓冲

	bool ROSASERIAL_CALLMODE CRosaSerialOpenPort(S_SERIALPORT_PROPERTY sCommProperty);	// CRosaSerial 打开串口
	void ROSASERIAL_CALLMODE CRosaSerialClosePort();									// CRosaSerial 关闭串口

	bool ROSASERIAL_CALLMODE OnTranslateBuffer();										// CRosaSerial 串口发送数据
	static unsigned int CALLBACK OnReceiveBuffer(LPVOID lpParameters);	// CRosaSerial 串口接收线程

};

#endif // !__ROSASERIAL_H_

