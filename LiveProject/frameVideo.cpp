/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameVideo.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "frameVideo.h"

// frameVideo UI¿‡

CFrameVideoUI::CFrameVideoUI()
{
	CDialogBuilder builder;
	CContainerUI* pframeVideoUI = static_cast<CContainerUI*>(builder.Create(_T("frame\\frameVideo.xml"), (UINT)0));

	if (pframeVideoUI)
	{
		this->Add(pframeVideoUI);
	}
	else
	{
		this->RemoveAll();
		return;
	}

}
