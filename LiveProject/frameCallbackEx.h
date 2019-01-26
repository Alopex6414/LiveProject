/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameCallbackEx.h
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#pragma once

#ifndef __FRAMECALLBACKEX_H_
#define __FRAMECALLBACKEX_H_

// Include Common Header File
#include "Common.h"

// Class Definition
class CDialogBuilderCallbackEx : public IDialogBuilderCallback
{
private:

public:
	CControlUI * CreateControl(LPCTSTR pstrClass);

};

#endif // !__FRAMECALLBACKEX_H_

