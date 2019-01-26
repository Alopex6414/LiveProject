/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameWallpaper.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "frameWallpaper.h"

// frameWallpaper UI¿‡

CFrameWallpaperUI::CFrameWallpaperUI()
{
	CDialogBuilder builder;
	CContainerUI* pframeWallpaperUI = static_cast<CContainerUI*>(builder.Create(_T("frame\\frameWallpaper.xml"), (UINT)0));

	if (pframeWallpaperUI)
	{
		this->Add(pframeWallpaperUI);
	}
	else
	{
		this->RemoveAll();
		return;
	}

}
