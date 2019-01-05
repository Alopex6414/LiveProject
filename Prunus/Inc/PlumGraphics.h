/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumGraphics.h
* @brief	This Program is PlumGraphics DLL Project.
* @author	Alopex/Helium
* @version	v1.02a
* @date		2017-12-28	v1.00a	alopex	Create Project.
* @date		2018-07-25	v1.01a	alopex	Add Call Mode.
* @date		2018-10-23	v1.02a	alopex	Alter Call Method.
*/
#pragma once

#ifndef __PLUMGRAPHICS_H_
#define __PLUMGRAPHICS_H_

//Include Plum Common Header File
#include "PlumCommon.h"

//Macro Definition
#ifdef	PRUNUS_EXPORTS
#define PLUMGRAPHICS_API	__declspec(dllexport)
#else
#define PLUMGRAPHICS_API	__declspec(dllimport)
#endif

#define PLUMGRAPHICS_CALLMETHOD	__stdcall

//Macro Pointer
#define SAFE_DELETE(Pointer)	{if(Pointer){delete(Pointer);(Pointer) = NULL;}}
#define SAFE_DELETE_ARRAY(Pointer) {if(Pointer){delete[](Pointer);(Pointer) = NULL;}}

//Struct Definition
struct PlumPoint
{
	int X;
	int Y;
	PlumPoint(int x, int y): X(x), Y(y) {}
};

//Enum Definition
enum PlumPenType
{
	PlumPen_Solid = 0,		//实线
	PlumPen_Dash = 1,		//虚线
	PlumPen_Dot = 2,		//点线
	PlumPen_DashDot = 3,	//点划线
	PlumPen_DashDotDot = 4,	//点点划线
};

//Class Definition
class PLUMGRAPHICS_API CPlumGraphics
{
private:
	HWND m_hWnd;			//PlumGraphics GDI Window Handle(GDI窗口句柄)
	RECT m_sRect;			//PlumGraphics GDI Draw Area Size(GDI窗口绘制区域大小)

public:
	CPlumGraphics();					//PlumGraphics Construction Function(GDI构造函数)
	virtual ~CPlumGraphics();			//PlumGraphics Destruction Function(GDI析构函数)

	//构造
	CPlumGraphics(HWND hWnd, RECT sRect);			//PlumGraphics Construction Function(GDI构造函数)

	//控制
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsSetHandle(HWND hWnd);	//PlumGraphics Set Handle(GDI设置窗口句柄)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsSetRect(RECT sRect);	//PlumGraphics Set Rect(GDI设置窗口区域)

	//访问
	virtual HWND PLUMGRAPHICS_CALLMETHOD PlumGraphicsGetHandle(void) const;	//PlumGraphics Get Handle(GDI获取窗口句柄)
	virtual RECT PLUMGRAPHICS_CALLMETHOD PlumGraphicsGetRect(void) const;	//PlumGraphics Get Rect(GDI获取窗口区域)

	//绘制
	//直线
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawLine(int nStartX, int nStartY, int nEndX, int nEndY);														//PlumGraphics Draw Line(GDI绘制直线)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawLine(PlumPoint sStart, PlumPoint sEnd);																	//PlumGraphics Draw Line(GDI绘制直线)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawLine(PlumPoint sStart, PlumPoint sEnd, PlumPenType ePenType, int nWidth, COLORREF crColor);				//PlumGraphics Draw Line(GDI绘制直线)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawLineOnOriginal(int nStartX, int nStartY, int nEndX, int nEndY);											//PlumGraphics Draw Line(GDI绘制直线)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawLineOnOriginal(PlumPoint sStart, PlumPoint sEnd);															//PlumGraphics Draw Line(GDI绘制直线)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawLineOnOriginal(PlumPoint sStart, PlumPoint sEnd, PlumPenType ePenType, int nPenWidth, COLORREF crColor);	//PlumGraphics Draw Line(GDI绘制直线)

	//矩形
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawRectangle(int nX, int nY, int nWidth, int nHeight);														//PlumGraphics Draw Rectangle(GDI绘制矩形)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawRectangle(RECT sRect);																						//PlumGraphics Draw Rectangle(GDI绘制矩形)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawRectangle(RECT sRect, PlumPenType ePenType, int nWidth, COLORREF crColor);									//PlumGraphics Draw Rectangle(GDI绘制矩形)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawRectangle(RECT sRect, PlumPenType ePenType, int nWidth, COLORREF crColorPen, COLORREF crColorBrush);		//PlumGraphics Draw Rectangle(GDI绘制矩形)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawRectangleOnOriginal(int nX, int nY, int nWidth, int nHeight);												//PlumGraphics Draw Rectangle(GDI绘制矩形)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawRectangleOnOriginal(RECT sRect);																			//PlumGraphics Draw Rectangle(GDI绘制矩形)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawRectangleOnOriginal(RECT sRect, PlumPenType ePenType, int nPenWidth, COLORREF crPenColor);					//PlumGraphics Draw Rectangle(GDI绘制矩形)
	virtual void PLUMGRAPHICS_CALLMETHOD PlumGraphicsDrawRectangleOnOriginal(RECT sRect, PlumPenType ePenType, int nPenWidth, COLORREF crPenColor, COLORREF crBrushColor);	//PlumGraphics Draw Rectangle(GDI绘制矩形)

};


#endif