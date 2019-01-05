/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CRosaSocket.h
* @brief	This File is RosaSocket Project.
* @author	alopex
* @version	v1.00a
* @date		2018-10-08	v1.00a	alopex	Create This File.
*/
#pragma once

#ifndef __CROSASOCKET_H__
#define __CROSASOCKET_H__

//Include WinSock2 Header File
#include <WinSock2.h>

//Include C/C++ Header File
#include <iostream>
#include <map>
#include <vector>

//Include WinSock2 Library
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

//Macro Definition
#ifdef  ROSA_EXPORTS
#define ROSASOCKET_API	__declspec(dllexport)
#else
#define ROSASOCKET_API	__declspec(dllimport)
#endif

#define ROSASOCKET_CALLMODE	__stdcall

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#define _WINSOCKAPI_

#define SOB_IP_LENGTH				128             //IP地址长度

#define SOB_TCP_SEND_BUFFER			32*1024			//TCP发送缓冲32K
#define SOB_TCP_RECV_BUFFER			32*1024			//TCP接收缓冲32K
#define SOB_UDP_RECV_BUFFER			32*1024			//UDP接收缓冲32K

#define SOB_DEFAULT_TIMEOUT_SEC		5				//默认的超时时间
#define SOB_DEFAULT_MAX_CLIENT		10				//默认服务端最大连接数

#define SOB_RET_OK					1				//正常
#define SOB_RET_FAIL				0				//错误
#define SOB_RET_TIMEOUT				-1				//超时
#define SOB_RET_CLOSE				-2				//断开

//Struct Definition
typedef struct
{
	SOCKET Socket;
	SOCKADDR_IN SocketAddr;
}S_CLIENTINFO, *LPS_CLIENTINFO;

//Callback Definition
typedef unsigned(__stdcall *HANDLE_ACCEPT_THREAD)(void*);		//定义接受连接线程函数
typedef void(__stdcall *HANDLE_ACCEPT_CALLBACK)(SOCKADDR_IN* pRemoteAddr, SOCKET s, DWORD dwUser);		//定义接受连接线程函数

//Class Definition
class ROSASOCKET_API CRosaSocket
{
public:
	CRosaSocket();			// CRosaSocket 构造函数
	~CRosaSocket();		// CRosaSocket 析构函数

public:
	static void CRosaSocketLibInit();			// CRosaSocket 初始Socket环境
	static void CRosaSocketLibRelease();		// CRosaSocket 清理Socket环境

private:
	SOCKET CreateTCPSocket();					// CRosaSocket 创建TCP套接字
	SOCKET CreateUDPSocket();					// CRosaSocket 创建UDP套接字

// 公用成员函数
public:
	void ROSASOCKET_CALLMODE CRosaSocketSetRecvTimeOut(UINT uiMSec);			// CRosaSocket 设置接收超时时长
	void ROSASOCKET_CALLMODE CRosaSocketSetSendTimeOut(UINT uiMSec);			// CRosaSocket 设置发送超时时长
	void ROSASOCKET_CALLMODE CRosaSocketSetRecvBufferSize(UINT uiByte);		// CRosaSocket 设置接收数组长度
	void ROSASOCKET_CALLMODE CRosaSocketSetSendBufferSize(UINT uiByte);		// CRosaSocket 设置发送数组长度

	SOCKET ROSASOCKET_CALLMODE CRosaSocketGetRawSocket() const;				// CRosaSocket 获取Socket句柄
	bool ROSASOCKET_CALLMODE CRosaSocketAttachRawSocket(SOCKET s, bool bIsConnected);	// CRosaSocket 绑定Socket套接字
	void ROSASOCKET_CALLMODE CRosaSocketDettachRawSocket();					// CRosaSocket 分离Socket套接字

	const char* ROSASOCKET_CALLMODE CRosaSocketGetRemoteIP() const;			// CRosaSocket 获取远端IP地址(ASCII)
	const wchar_t* ROSASOCKET_CALLMODE CRosaSocketGetRemoteIPW() const;		// CRosaSocket 获取远端IP地址(Unicode)
	ULONG ROSASOCKET_CALLMODE CRosaSocketGetRemoteIPUL() const;				// CRosaSocket 获取远端IP地址(ULONG)
	USHORT ROSASOCKET_CALLMODE CRosaSocketGetRemotePort() const;				// CRosaSocket 获取远程端口号
	bool ROSASOCKET_CALLMODE CRosaSocketIsConnected() const;					// CRosaSocket 获取连接状态(客户端)
	void ROSASOCKET_CALLMODE CRosaSocketDestory();								// CRosaSocket 删除SocketBase类

// TCP服务端成员函数
public:
	bool ROSASOCKET_CALLMODE CRosaSocketBindOnPort(USHORT uPort);	// CRosaSocket 绑定服务端端口
	bool ROSASOCKET_CALLMODE CRosaSocketListen();					// CRosaSocket 监听服务端端口
	bool ROSASOCKET_CALLMODE CRosaSocketAccept(HANDLE_ACCEPT_THREAD pThreadFunc, HANDLE_ACCEPT_CALLBACK pCallback, DWORD dwUser, BOOL* pExitFlag = NULL, USHORT nLoopTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);	// CRosaSocket 接收客户端连接请求

	int ROSASOCKET_CALLMODE CRosaSocketSendOnce(SOCKET Socket, char* pSendBuffer, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);										// CRosaSocket 发送缓冲数据(发送全部数据)
	int ROSASOCKET_CALLMODE CRosaSocketSendBuffer(SOCKET Socket, char* pSendBuffer, UINT uiBufferSize, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);					// CRosaSocket 发送缓冲数据(发送一定数据)
	int ROSASOCKET_CALLMODE CRosaSocketRecvOnce(SOCKET Socket, char* pRecvBuffer, UINT uiBufferSize, UINT& uiRecv, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);		// CRosaSocket 接收缓冲数据(接收全部数据)
	int ROSASOCKET_CALLMODE CRosaSocketRecvBuffer(SOCKET Socket, char* pRecvBuffer, UINT uiBufferSize, UINT uiRecvSize, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);	// CRosaSocket 接收缓冲数据(接收一定数据)

	USHORT ROSASOCKET_CALLMODE CRosaSocketGetConnectMaxCount() const;																									// CRosaSocket 获取最大连接数量
	int& ROSASOCKET_CALLMODE CRosaSocketGetConnectCount();																										// CRosaSocket 获取当前连接的数量
	map<int, HANDLE>& ROSASOCKET_CALLMODE CRosaSocketGetConnectMap();																									// CRosaSocket 获取当前连接的Map																									// CRosaSocket 获取当前连接状态Map

	void ROSASOCKET_CALLMODE CRosaSocketSetConnectMaxCount(USHORT sMaxCount);																							// CRosaSocket 设置最大连接数量
	void ROSASOCKET_CALLMODE CRosaSocketSetConnectCount(int nAcceptCount);																								// CRosaSocket 设置当前连接数量

// TCP客户端成员函数
public:
	bool ROSASOCKET_CALLMODE CRosaSocketConnect(const char* pcRemoteIP = NULL, USHORT sPort = 0, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);						// CRosaSocket 发送服务器连接请求
	bool ROSASOCKET_CALLMODE CRosaSocketReConnect();																													// CRosaSocket 尝试重新连接服务器
	void ROSASOCKET_CALLMODE CRosaSocketDisConnect();																													// CRosaSocket 断开与服务器的连接

	int ROSASOCKET_CALLMODE CRosaSocketSendOnce(char* pSendBuffer, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);														// CRosaSocket 发送缓冲数据(发送全部数据)
	int ROSASOCKET_CALLMODE CRosaSocketSendBuffer(char* pSendBuffer, UINT uiBufferSize, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);									// CRosaSocket 发送缓冲数据(发送一定数据)
	int ROSASOCKET_CALLMODE CRosaSocketRecvOnce(char* pRecvBuffer, UINT uiBufferSize, UINT& uiRecv, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);						// CRosaSocket 接收缓冲数据(接收全部数据)
	int ROSASOCKET_CALLMODE CRosaSocketRecvBuffer(char* pRecvBuffer, UINT uiBufferSize, UINT uiRecvSize, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);				// CRosaSocket 接收缓冲数据(接收一定数据)

// UDP成员函数
public:
	bool ROSASOCKET_CALLMODE CRosaSocketUDPBindOnPort(const char* pcRemoteIP, UINT uiPort);																							// CRosaSocket 绑定端口(UDP)

	int ROSASOCKET_CALLMODE CRosaSocketUDPSendBuffer(const char* pcIP, SHORT sPort, char* pBuffer, UINT uiBufferSize, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);					// CRosaSocket 发送数据缓冲(UDP)
	int ROSASOCKET_CALLMODE CRosaSocketUDPRecvBuffer(char* pBuffer, UINT uiBufferSize, UINT& uiRecv, char* pcIP, USHORT& uPort, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);			// CRosaSocket 接收数据缓冲(UDP)

// 其他函数
public:
	static bool ResolveAddressToIp(const char* pcAddress, char* pcIp);			// CRosaSocket 网址转换为IP地址
	static void GetLocalIPAddr();												// CRosaSocket 获取本地IP地址
	void ROSASOCKET_CALLMODE GetLocalIPPort();														// CRosaSocket 获取本地端口号

	static const char* GetLocalIP();
	static USHORT GetLocalPort();
	static void SetLocalIP(const char* pLocalIP, int nSize);
	static void SetLocalPort(USHORT sLocalPort);

// 公用成员
private:
	SOCKET m_socket;				// CRosaSocket Socket套接字
	WSAEVENT m_SocketWriteEvent;	// CRosaSocket Socket发送事件
	WSAEVENT m_SocketReadEvent;		// CRosaSocket Socket获取事件

	char m_pcRemoteIP[SOB_IP_LENGTH];			// CRosaSocket 远程端IP地址
	USHORT m_sRemotePort;						// CRosaSocket 远程端端口号

	char m_pcHostIP[SOB_IP_LENGTH];				// CRosaSocket 本地IP地址
	USHORT m_sHostPort;							// CRosaSocket 本地端口号

	wchar_t m_pwcRemoteIP[SOB_IP_LENGTH];

public:
	int m_nLastWSAError;			// CRosaSocket WSA错误代码

// TCP服务端成员
private:
	map<int, HANDLE> m_mapAccept;	// CRosaSocket 服务端连接线程
	int m_nAcceptCount;				// CRosaSocket 服务端连接数量
	USHORT m_sMaxCount;				// CRosaSocket 服务端最大连接数

// TCP客户端成员
private:
	bool m_bIsConnected;			// CRosaSocket Socket连接状态

// UDP成员
private:


// 其他成员
private:
	static char m_pcLocalIP[SOB_IP_LENGTH];			// CRosaSocket 本机IP地址
	static USHORT m_sLocalPort;						// CRosaSocket 本机端口号

};


#endif // !__CSOCKETBASE_H__
