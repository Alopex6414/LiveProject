/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameAI.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "frameAI.h"

// frameAI UI¿‡

CFrameAIUI::CFrameAIUI()
{
	CDialogBuilder builder;
	CContainerUI* pframeAIUI = static_cast<CContainerUI*>(builder.Create(_T("frame\\frameAI.xml"), (UINT)0));

	if (pframeAIUI)
	{
		this->Add(pframeAIUI);
	}
	else
	{
		this->RemoveAll();
		return;
	}

}
