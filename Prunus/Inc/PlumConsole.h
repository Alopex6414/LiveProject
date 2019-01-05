/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumConsole.h
* @brief	This Program is PlumConsole DLL Project.
* @notes	Console控制台调试
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
	HANDLE m_hConsole;							//Console Handle 控制台句柄
	CONSOLE_SCREEN_BUFFER_INFO m_sConsoleInfo;	//Console Infomation 控制台信息

public:
	CPlumConsole();								//PlumConsole 构造函数
	virtual ~CPlumConsole();					//PlumConsole 析构函数

	//访问
	HANDLE PLUMCONSOLE_CALLMETHOD PlumConsoleGetHandle(void) const;	//PlumConsole 访问控制台句柄

	//简单
	void PLUMCONSOLE_CALLMETHOD PlumConsoleSetConsoleTitle(LPCWSTR lpcszTitle);			//PlumConsole 设置控制台标题
	void PLUMCONSOLE_CALLMETHOD PlumConsoleSetCursorPosition(COORD Coord);				//PlumConsole 设置光标位置

	void PLUMCONSOLE_CALLMETHOD PlumConsoleGetScreenBufferInfo(void);						//PlumConsole 获取控制台缓冲区信息

	//初始化
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleInit(LPCWSTR lpcszTitle = L"Console");								//PlumConsole Init~(初始化Console)
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleInit(COORD Coord, LPCWSTR lpcszTitle = L"Console");				//PlumConsole Init~(初始化Console)<Console窗口位置/大小>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleInit(int nWidth, int nHeight, LPCWSTR lpcszTitle = L"Console");	//PlumConsole Init~(初始化Console)<Console窗口位置/大小>

	//清空
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleClear(void);			//PlumConsole Clear(清空Console)<Console窗口清空>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleClearLine(int Y);		//PlumConsole Clear(清空Console Line)<Console清空一行>

	//输出
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWrite(const void* lpcszStr);															//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWrite(const void* lpcszStr, int nSize);												//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWrite(const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);				//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWrite(const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);	//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLine(const void* lpcszStr);														//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLine(const void* lpcszStr, int nSize);											//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLine(const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);			//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLine(const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteEx(int X, int Y, const void* lpcszStr);											//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize);								//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);						//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);			//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr);										//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, int nSize);							//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);					//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);		//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteInt(int nNumber, WORD wTextColor, bool bIsUnderLine = false);						//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteFloat(float fNumber, WORD wTextColor, bool bIsUnderLine = false);					//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteDouble(double dNumber, WORD wTextColor, bool bIsUnderLine = false);				//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineInt(int nNumber, WORD wTextColor, bool bIsUnderLine = false);					//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineFloat(float fNumber, WORD wTextColor, bool bIsUnderLine = false);				//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineDouble(double dNumber, WORD wTextColor, bool bIsUnderLine = false);			//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteNormal(LPCSTR lpcstr, ...);					//PlumConsole Write~(输出Console)<输出文本到控制台><标准模式>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineNormal(LPCSTR lpcstr, ...);				//PlumConsole Write~(输出Console)<输出文本到控制台><标准模式>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteRepeat(int Y, LPCSTR lpcstr, ...);			//PlumConsole Write~(输出Console)<输出文本到控制台><重复模式>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteLineRepeat(int Y, LPCSTR lpcstr, ...);		//PlumConsole Write~(输出Console)<输出文本到控制台><重复模式>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteA(const void* lpcszStr);						//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteA(const void* lpcszStr, int nSize);			//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteW(const void* lpcszStr);						//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PLUMCONSOLE_CALLMETHOD PlumConsoleWriteW(const void* lpcszStr, int nSize);			//PlumConsole Write~(输出Console)<输出文本到控制台>

};

#endif