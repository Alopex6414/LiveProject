/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameAudio.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "frameAudio.h"

// frameAudio UI¿‡

CFrameAudioUI::CFrameAudioUI(CPaintManagerUI* pManager)
{
	CDialogBuilder builder;
	CContainerUI* pframeAudioUI = static_cast<CContainerUI*>(builder.Create(_T("frame\\frameAudio.xml"), NULL, NULL, pManager));

	if (pframeAudioUI)
	{
		this->Add(pframeAudioUI);
	}
	else
	{
		this->RemoveAll();
		return;
	}

}
