/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameAbout.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "frameAbout.h"

// frameAbout UI¿‡

CFrameAboutUI::CFrameAboutUI(CPaintManagerUI* pManager)
{
	CDialogBuilder builder;
	CContainerUI* pframeAboutUI = static_cast<CContainerUI*>(builder.Create(_T("frame\\frameAbout.xml"), NULL, NULL, pManager));

	if (pframeAboutUI)
	{
		this->Add(pframeAboutUI);
	}
	else
	{
		this->RemoveAll();
		return;
	}

}
