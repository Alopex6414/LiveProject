/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		frameCallbackEx.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "frameCallbackEx.h"

CControlUI * CDialogBuilderCallbackEx::CreateControl(LPCTSTR pstrClass)
{
	if (_tcscmp(pstrClass, _T("frameSpace")) == 0)
	{
		return new CFrameSpaceUI();
	}

	if (_tcscmp(pstrClass, _T("frameHome")) == 0)
	{
		return new CFrameHomeUI();
	}

	if (_tcscmp(pstrClass, _T("frameWallpaper")) == 0)
	{
		return new CFrameWallpaperUI(&(g_pFrameMain->GetPaintManager()));
	}

	if (_tcscmp(pstrClass, _T("frameVideo")) == 0)
	{
		return new CFrameVideoUI();
	}

	if (_tcscmp(pstrClass, _T("frameAudio")) == 0)
	{
		return new CFrameAudioUI();
	}

	if (_tcscmp(pstrClass, _T("frameAlbum")) == 0)
	{
		return new CFrameAlbumUI();
	}

	if (_tcscmp(pstrClass, _T("frameShot")) == 0)
	{
		return new CFrameShotUI();
	}

	if (_tcscmp(pstrClass, _T("frameAI")) == 0)
	{
		return new CFrameAIUI();
	}

	if (_tcscmp(pstrClass, _T("frameSettings")) == 0)
	{
		return new CFrameSettingsUI();
	}

	if (_tcscmp(pstrClass, _T("frameAbout")) == 0)
	{
		return new CFrameAboutUI();
	}

	return nullptr;
}
