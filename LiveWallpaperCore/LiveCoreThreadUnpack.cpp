/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCoreThreadUnpack.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-14
*/
#include "LiveCoreThreadUnpack.h"

//------------------------------------------------------------------
// @Function:	 CLiveCoreThreadUnpack()
// @Purpose: CLiveCoreThreadUnpack构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThreadUnpack::CLiveCoreThreadUnpack()
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveCoreThreadUnpack()
// @Purpose: CLiveCoreThreadUnpack析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThreadUnpack::~CLiveCoreThreadUnpack()
{
}

//------------------------------------------------------------------
// @Function:	 PlumThreadRun()
// @Purpose: CLiveCoreThreadUnpack线程运行
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void __stdcall CLiveCoreThreadUnpack::PlumThreadRun()
{
	CPlumPack* pUnPacker = new CPlumPack();

	int nUnpackSize = 0;
	int nUnpackCount = 0;

	pUnPacker->PlumUnPackFilePackerA((const char*)g_chDefaultVideoAddress, (const char*)g_chDefaultVideoDirector, &nUnpackSize, &nUnpackCount, g_chDefaultVideoUnpack, MAX_PATH);

	delete pUnPacker;
}
