/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameHome.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "frameHome.h"

// frameHome UI¿‡

CFrameHomeUI::CFrameHomeUI(CPaintManagerUI* pManager)
{
	CDialogBuilder builder;
	CContainerUI* pframeHomeUI = static_cast<CContainerUI*>(builder.Create(_T("frame\\frameHome.xml"), NULL, NULL, pManager));

	if (pframeHomeUI)
	{
		this->Add(pframeHomeUI);
	}
	else
	{
		this->RemoveAll();
		return;
	}

}
