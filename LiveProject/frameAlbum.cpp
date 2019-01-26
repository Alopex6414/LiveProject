/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameAlbum.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "frameAlbum.h"

// frameAlbum UI¿‡

CFrameAlbumUI::CFrameAlbumUI()
{
	CDialogBuilder builder;
	CContainerUI* pframeAlbumUI = static_cast<CContainerUI*>(builder.Create(_T("frame\\frameAlbum.xml"), (UINT)0));

	if (pframeAlbumUI)
	{
		this->Add(pframeAlbumUI);
	}
	else
	{
		this->RemoveAll();
		return;
	}

}
