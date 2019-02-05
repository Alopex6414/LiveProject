/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameShot.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "frameShot.h"

// frameShot UI¿‡

CFrameShotUI::CFrameShotUI(CPaintManagerUI* pManager)
{
	CDialogBuilder builder;
	CContainerUI* pframeShotUI = static_cast<CContainerUI*>(builder.Create(_T("frame\\frameShot.xml"), NULL, NULL, pManager));

	if (pframeShotUI)
	{
		this->Add(pframeShotUI);
	}
	else
	{
		this->RemoveAll();
		return;
	}

}
