/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumConsole.h
* @brief	This Program is PlumConsole DLL Project.
* @notes	Console����̨����
* @author	Alopex/Helium
* @version	v1.05a
* @date		2017-12-23	v1.00a	alopex	Create Project.
* @date		2018-07-02	v1.02a	alopex	Add Common Header File.
* @date		2018-07-03	v1.03a	alopex	Add Call Mode.
* @date		2018-07-03	v1.04a	alopex	Update Common Header File.
* @date		2018-10-23	v1.05a	alopex	Alter Call Method.
*/
#pragma once

#ifndef __PLUMCONSOLE_H_
#define __PLUMCONSOLE_H_

//Include Plum Common Header File
#include "PlumCommon.h"

//Macro Definition
#ifdef	PRUNUS_EXPORTS
#define PLUMCONSOLE_API	__declspec(dllexport)
#else
#define PLUMCONSOLE_API	__declspec(dllimport)
#endif

#define PLUMCONSOLE_CALLMETHOD	__stdcall

//About Console Output Color
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_RED	(WORD)(FOREGROUND_RED	| FOREGROUND_INTENSITY)
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_GREEN	(WORD)(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_BLUE	(WORD)(FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_PINK	(WORD)(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_YELLOW	(WORD)(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_CYAN	(WORD)(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_WHITE	(WORD)(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)

#define CONSOLE_TEXTCOLOR_DARKNESS_RED		(WORD)(FOREGROUND_RED)
#define CONSOLE_TEXTCOLOR_DARKNESS_GREEN	(WORD)(FOREGROUND_GREEN)
#define CONSOLE_TEXTCOLOR_DARKNESS_BLUE		(WORD)(FOREGROUND_BLUE)
#define CONSOLE_TEXTCOLOR_DARKNESS_PINK		(WORD)(FOREGROUND_RED | FOREGROUND_BLUE)
#define CONSOLE_TEXTCOLOR_DARKNESS_YELLOW	(WORD)(FOREGROUND_RED | FOREGROUND_GREEN)
#define CONSOLE_TEXTCOLOR_DARKNESS_CYAN		(WORD)(FOREGROUND_GREEN | FOREGROUND_BLUE)
#define CONSOLE_TEXTCOLOR_DARKNESS_WHITE	(WORD)(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

//Class Definition
class PLUMCONSOLE_API CPlumConsole
{
private:
	HANDLE m_hConsole;							//Console Handle ����̨���
	CONSOLE_SCREEN_BUFFER_INFO m_sConsoleInfo;	//Console Infomation ����̨��Ϣ

public:
	CPlumConsole();								//PlumConsole ���캯��
	virtual ~CPlumConsole();					//PlumConsole ��������

	//����
	HANDLE PLUMCONSOLE_CALLMETHOD PlumConsoleGetHandle(void) const;	//PlumConsole ���ʿ���̨���

	//��
	void PLUMCONSOLE_CALLMETHOD PlumConsoleSetConsoleTitle(LPCWSTR lpcszTitle);			//PlumConsole ���ÿ���̨����
	void PLUMCONSOLE_CALLMETHOD PlumConsoleSetCursorPosition(COORD Coord);				//PlumConsole ���ù��λ��

	void PLUMCONSOLE_CALLMETHOD PlumConsoleGetScreenBufferInfo(void);						//PlumConsole ��ȡ����̨��������Ϣ

	//��ʼ��
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleInit(LPCWSTR lpcszTitle = L"Console");								//PlumConsole Init~(��ʼ��Console)
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleInit(COORD Coord, LPCWSTR lpcszTitle = L"Console");				//PlumConsole Init~(��ʼ��Console)<Console����λ��/��С>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleInit(int nWidth, int nHeight, LPCWSTR lpcszTitle = L"Console");	//PlumConsole Init~(��ʼ��Console)<Console����λ��/��С>

	//���
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleClear(void);			//PlumConsole Clear(���Console)<Console�������>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleClearLine(int Y);		//PlumConsole Clear(���Console Line)<Console���һ��>

	//���
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWrite(const void* lpcszStr);															//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWrite(const void* lpcszStr, int nSize);												//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWrite(const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);				//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWrite(const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);	//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLine(const void* lpcszStr);														//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLine(const void* lpcszStr, int nSize);											//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLine(const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);			//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLine(const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteEx(int X, int Y, const void* lpcszStr);											//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize);								//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);						//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);			//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr);										//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, int nSize);							//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);					//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);		//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteInt(int nNumber, WORD wTextColor, bool bIsUnderLine = false);						//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteFloat(float fNumber, WORD wTextColor, bool bIsUnderLine = false);					//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteDouble(double dNumber, WORD wTextColor, bool bIsUnderLine = false);				//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineInt(int nNumber, WORD wTextColor, bool bIsUnderLine = false);					//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineFloat(float fNumber, WORD wTextColor, bool bIsUnderLine = false);				//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineDouble(double dNumber, WORD wTextColor, bool bIsUnderLine = false);			//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteNormal(LPCSTR lpcstr, ...);					//PlumConsole Write~(���Console)<����ı�������̨><��׼ģʽ>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineNormal(LPCSTR lpcstr, ...);				//PlumConsole Write~(���Console)<����ı�������̨><��׼ģʽ>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteRepeat(int Y, LPCSTR lpcstr, ...);			//PlumConsole Write~(���Console)<����ı�������̨><�ظ�ģʽ>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineRepeat(int Y, LPCSTR lpcstr, ...);		//PlumConsole Write~(���Console)<����ı�������̨><�ظ�ģʽ>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteA(const void* lpcszStr);						//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteA(const void* lpcszStr, int nSize);			//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteW(const void* lpcszStr);						//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteW(const void* lpcszStr, int nSize);			//PlumConsole Write~(���Console)<����ı�������̨>

};

#endif