/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveGraphics.h
* @brief	This Program is LiveGraphicsCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-06-22
*/
#pragma once

#ifndef __LIVEGRAPHICS_H_
#define __LIVEGRAPHICS_H_

// Include Common Header File
#include "Common.h"

// Class Definition
class CLiveGraphics
{
private:

public:
	CLiveGraphics();
	~CLiveGraphics();

	BOOL CLiveGraphicsInit();
	void CLiveGraphicsRelease();

	void CLiveGraphicsUpdate();
	void CLiveGraphicsRender();

};

#endif // !__LIVEGRAPHICS_H_