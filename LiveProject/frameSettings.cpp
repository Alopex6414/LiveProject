/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameSettings.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "frameSettings.h"

// frameSettings UI¿‡

CFrameSettingsUI::CFrameSettingsUI(CPaintManagerUI* pManager)
{
	CDialogBuilder builder;
	CContainerUI* pframeSettingsUI = static_cast<CContainerUI*>(builder.Create(_T("frame\\frameSettings.xml"), NULL, NULL, pManager));

	if (pframeSettingsUI)
	{
		this->Add(pframeSettingsUI);
	}
	else
	{
		this->RemoveAll();
		return;
	}

}
