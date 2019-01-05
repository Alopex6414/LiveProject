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

#define SOB_IP_LENGTH				128             //IP��ַ����

#define SOB_TCP_SEND_BUFFER			32*1024			//TCP���ͻ���32K
#define SOB_TCP_RECV_BUFFER			32*1024			//TCP���ջ���32K
#define SOB_UDP_RECV_BUFFER			32*1024			//UDP���ջ���32K

#define SOB_DEFAULT_TIMEOUT_SEC		5				//Ĭ�ϵĳ�ʱʱ��
#define SOB_DEFAULT_MAX_CLIENT		10				//Ĭ�Ϸ�������������

#define SOB_RET_OK					1				//����
#define SOB_RET_FAIL				0				//����
#define SOB_RET_TIMEOUT				-1				//��ʱ
#define SOB_RET_CLOSE				-2				//�Ͽ�

//Struct Definition
typedef struct
{
	SOCKET Socket;
	SOCKADDR_IN SocketAddr;
}S_CLIENTINFO, *LPS_CLIENTINFO;

//Callback Definition
typedef unsigned(__stdcall *HANDLE_ACCEPT_THREAD)(void*);		//������������̺߳���
typedef void(__stdcall *HANDLE_ACCEPT_CALLBACK)(SOCKADDR_IN* pRemoteAddr, SOCKET s, DWORD dwUser);		//������������̺߳���

//Class Definition
class ROSASOCKET_API CRosaSocket
{
public:
	CRosaSocket();			// CRosaSocket ���캯��
	~CRosaSocket();		// CRosaSocket ��������

public:
	static void CRosaSocketLibInit();			// CRosaSocket ��ʼSocket����
	static void CRosaSocketLibRelease();		// CRosaSocket ����Socket����

private:
	SOCKET CreateTCPSocket();					// CRosaSocket ����TCP�׽���
	SOCKET CreateUDPSocket();					// CRosaSocket ����UDP�׽���

// ���ó�Ա����
public:
	void ROSASOCKET_CALLMODE CRosaSocketSetRecvTimeOut(UINT uiMSec);			// CRosaSocket ���ý��ճ�ʱʱ��
	void ROSASOCKET_CALLMODE CRosaSocketSetSendTimeOut(UINT uiMSec);			// CRosaSocket ���÷��ͳ�ʱʱ��
	void ROSASOCKET_CALLMODE CRosaSocketSetRecvBufferSize(UINT uiByte);		// CRosaSocket ���ý������鳤��
	void ROSASOCKET_CALLMODE CRosaSocketSetSendBufferSize(UINT uiByte);		// CRosaSocket ���÷������鳤��

	SOCKET ROSASOCKET_CALLMODE CRosaSocketGetRawSocket() const;				// CRosaSocket ��ȡSocket���
	bool ROSASOCKET_CALLMODE CRosaSocketAttachRawSocket(SOCKET s, bool bIsConnected);	// CRosaSocket ��Socket�׽���
	void ROSASOCKET_CALLMODE CRosaSocketDettachRawSocket();					// CRosaSocket ����Socket�׽���

	const char* ROSASOCKET_CALLMODE CRosaSocketGetRemoteIP() const;			// CRosaSocket ��ȡԶ��IP��ַ(ASCII)
	const wchar_t* ROSASOCKET_CALLMODE CRosaSocketGetRemoteIPW() const;		// CRosaSocket ��ȡԶ��IP��ַ(Unicode)
	ULONG ROSASOCKET_CALLMODE CRosaSocketGetRemoteIPUL() const;				// CRosaSocket ��ȡԶ��IP��ַ(ULONG)
	USHORT ROSASOCKET_CALLMODE CRosaSocketGetRemotePort() const;				// CRosaSocket ��ȡԶ�̶˿ں�
	bool ROSASOCKET_CALLMODE CRosaSocketIsConnected() const;					// CRosaSocket ��ȡ����״̬(�ͻ���)
	void ROSASOCKET_CALLMODE CRosaSocketDestory();								// CRosaSocket ɾ��SocketBase��

// TCP����˳�Ա����
public:
	bool ROSASOCKET_CALLMODE CRosaSocketBindOnPort(USHORT uPort);	// CRosaSocket �󶨷���˶˿�
	bool ROSASOCKET_CALLMODE CRosaSocketListen();					// CRosaSocket ��������˶˿�
	bool ROSASOCKET_CALLMODE CRosaSocketAccept(HANDLE_ACCEPT_THREAD pThreadFunc, HANDLE_ACCEPT_CALLBACK pCallback, DWORD dwUser, BOOL* pExitFlag = NULL, USHORT nLoopTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);	// CRosaSocket ���տͻ�����������

	int ROSASOCKET_CALLMODE CRosaSocketSendOnce(SOCKET Socket, char* pSendBuffer, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);										// CRosaSocket ���ͻ�������(����ȫ������)
	int ROSASOCKET_CALLMODE CRosaSocketSendBuffer(SOCKET Socket, char* pSendBuffer, UINT uiBufferSize, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);					// CRosaSocket ���ͻ�������(����һ������)
	int ROSASOCKET_CALLMODE CRosaSocketRecvOnce(SOCKET Socket, char* pRecvBuffer, UINT uiBufferSize, UINT& uiRecv, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);		// CRosaSocket ���ջ�������(����ȫ������)
	int ROSASOCKET_CALLMODE CRosaSocketRecvBuffer(SOCKET Socket, char* pRecvBuffer, UINT uiBufferSize, UINT uiRecvSize, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);	// CRosaSocket ���ջ�������(����һ������)

	USHORT ROSASOCKET_CALLMODE CRosaSocketGetConnectMaxCount() const;																									// CRosaSocket ��ȡ�����������
	int& ROSASOCKET_CALLMODE CRosaSocketGetConnectCount();																										// CRosaSocket ��ȡ��ǰ���ӵ�����
	map<int, HANDLE>& ROSASOCKET_CALLMODE CRosaSocketGetConnectMap();																									// CRosaSocket ��ȡ��ǰ���ӵ�Map																									// CRosaSocket ��ȡ��ǰ����״̬Map

	void ROSASOCKET_CALLMODE CRosaSocketSetConnectMaxCount(USHORT sMaxCount);																							// CRosaSocket ���������������
	void ROSASOCKET_CALLMODE CRosaSocketSetConnectCount(int nAcceptCount);																								// CRosaSocket ���õ�ǰ��������

// TCP�ͻ��˳�Ա����
public:
	bool ROSASOCKET_CALLMODE CRosaSocketConnect(const char* pcRemoteIP = NULL, USHORT sPort = 0, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);						// CRosaSocket ���ͷ�������������
	bool ROSASOCKET_CALLMODE CRosaSocketReConnect();																													// CRosaSocket �����������ӷ�����
	void ROSASOCKET_CALLMODE CRosaSocketDisConnect();																													// CRosaSocket �Ͽ��������������

	int ROSASOCKET_CALLMODE CRosaSocketSendOnce(char* pSendBuffer, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);														// CRosaSocket ���ͻ�������(����ȫ������)
	int ROSASOCKET_CALLMODE CRosaSocketSendBuffer(char* pSendBuffer, UINT uiBufferSize, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);									// CRosaSocket ���ͻ�������(����һ������)
	int ROSASOCKET_CALLMODE CRosaSocketRecvOnce(char* pRecvBuffer, UINT uiBufferSize, UINT& uiRecv, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);						// CRosaSocket ���ջ�������(����ȫ������)
	int ROSASOCKET_CALLMODE CRosaSocketRecvBuffer(char* pRecvBuffer, UINT uiBufferSize, UINT uiRecvSize, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);				// CRosaSocket ���ջ�������(����һ������)

// UDP��Ա����
public:
	bool ROSASOCKET_CALLMODE CRosaSocketUDPBindOnPort(const char* pcRemoteIP, UINT uiPort);																							// CRosaSocket �󶨶˿�(UDP)

	int ROSASOCKET_CALLMODE CRosaSocketUDPSendBuffer(const char* pcIP, SHORT sPort, char* pBuffer, UINT uiBufferSize, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);					// CRosaSocket �������ݻ���(UDP)
	int ROSASOCKET_CALLMODE CRosaSocketUDPRecvBuffer(char* pBuffer, UINT uiBufferSize, UINT& uiRecv, char* pcIP, USHORT& uPort, USHORT nTimeOutSec = SOB_DEFAULT_TIMEOUT_SEC);			// CRosaSocket �������ݻ���(UDP)

// ��������
public:
	static bool ResolveAddressToIp(const char* pcAddress, char* pcIp);			// CRosaSocket ��ַת��ΪIP��ַ
	static void GetLocalIPAddr();												// CRosaSocket ��ȡ����IP��ַ
	void ROSASOCKET_CALLMODE GetLocalIPPort();														// CRosaSocket ��ȡ���ض˿ں�

	static const char* GetLocalIP();
	static USHORT GetLocalPort();
	static void SetLocalIP(const char* pLocalIP, int nSize);
	static void SetLocalPort(USHORT sLocalPort);

// ���ó�Ա
private:
	SOCKET m_socket;				// CRosaSocket Socket�׽���
	WSAEVENT m_SocketWriteEvent;	// CRosaSocket Socket�����¼�
	WSAEVENT m_SocketReadEvent;		// CRosaSocket Socket��ȡ�¼�

	char m_pcRemoteIP[SOB_IP_LENGTH];			// CRosaSocket Զ�̶�IP��ַ
	USHORT m_sRemotePort;						// CRosaSocket Զ�̶˶˿ں�

	char m_pcHostIP[SOB_IP_LENGTH];				// CRosaSocket ����IP��ַ
	USHORT m_sHostPort;							// CRosaSocket ���ض˿ں�

	wchar_t m_pwcRemoteIP[SOB_IP_LENGTH];

public:
	int m_nLastWSAError;			// CRosaSocket WSA�������

// TCP����˳�Ա
private:
	map<int, HANDLE> m_mapAccept;	// CRosaSocket ����������߳�
	int m_nAcceptCount;				// CRosaSocket �������������
	USHORT m_sMaxCount;				// CRosaSocket ��������������

// TCP�ͻ��˳�Ա
private:
	bool m_bIsConnected;			// CRosaSocket Socket����״̬

// UDP��Ա
private:


// ������Ա
private:
	static char m_pcLocalIP[SOB_IP_LENGTH];			// CRosaSocket ����IP��ַ
	static USHORT m_sLocalPort;						// CRosaSocket �����˿ں�

};


#endif // !__CSOCKETBASE_H__
