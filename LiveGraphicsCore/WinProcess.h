/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		WinProcess.h
* @brief	This Program is LiveGraphicsCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-06-22
*/
#pragma once

#ifndef __WINPROCESS_H_
#define __WINPROCESS_H_

//Include Header File
#include "WinUtilities.h"

//Include Resource File
#include "resource.h"

//Macro Definition
#ifndef USER_WINDOWWIDTH
#define USER_WINDOWWIDTH	1920							//窗口宽度
#endif

#ifndef USER_WINDOWHEIGHT
#define USER_WINDOWHEIGHT	1080							//窗口高度
#endif

#ifndef USER_WINDOWTITLE
#define USER_WINDOWTITLE	L"LiveGraphicsCore"				//窗口标题名称
#endif

#ifndef USER_WINDOWICON
#define USER_WINDOWICON		(WORD)IDI_ICON					//窗口标题图标
#endif

//Variable Definition
extern float g_fLastTime;
extern float g_fCurrentTime;
extern float g_fDeltaTime;

//Function Definition
extern WndPara* SetWindowParameterCallBack(void);
extern BOOL InitWindowExtraCallBack(void);
extern void ReleaseWindowExtraCallBack(void);
extern void Direct3DRenderCallBack(void);

#endif // !__WINPROCESS_H_