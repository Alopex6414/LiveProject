/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameSpace.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "frameSpace.h"

// frameSpace UI¿‡

CFrameSpaceUI::CFrameSpaceUI(CPaintManagerUI* pManager)
{
	CDialogBuilder builder;
	CContainerUI* pframeSpaceUI = static_cast<CContainerUI*>(builder.Create(_T("frame\\frameSpace.xml"), NULL, NULL, pManager));

	if (pframeSpaceUI)
	{
		this->Add(pframeSpaceUI);
	}
	else
	{
		this->RemoveAll();
		return;
	}

}
