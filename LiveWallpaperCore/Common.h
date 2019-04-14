/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		Common.h
* @brief	This Program is LiveWallpaper Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-13
*/
#pragma once

#ifndef __COMMON_H_
#define __COMMON_H_

// Include Windows Header File
#include <Windows.h>

// Include CommCtrl Header File
#include <CommCtrl.h>

// Include C/C++ Running Header File
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <mmreg.h>
#include <wchar.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>

// Include Cerasus(DirectX) Library Header File
#include "DirectCommon.h"
#include "DirectGraphics.h"
#include "DirectGraphics2D.h"
#include "DirectGraphics3D.h"
#include "DirectInput.h"
#include "DirectSound.h"
#include "DirectShow.h"
#include "DirectMesh.h"
#include "DirectTexture.h"
#include "DirectSurface.h"
#include "DirectSprite.h"
#include "DirectFont.h"

#include "CerasusAlgorithm.h"
#include "Cerasusfps.h"
#include "CerasusUnit.h"

#include "SakuraUICommon.h"
#include "SakuraBlend.h"
#include "SakuraElement.h"
#include "SakuraControl.h"
#include "SakuraStatic.h"
#include "SakuraButton.h"
#include "SakuraDialog.h"
#include "SakuraCheckBox.h"
#include "SakuraResource.h"

// Include Prunus(C/C++ Win32) Library Header File
#include "PlumCommon.h"
#include "PlumConsole.h"
#include "PlumCipherA.h"
#include "PlumCrypt.h"
#include "PlumPack.h"
#include "PlumFile.h"
#include "PlumGraphics.h"
#include "PlumIni.h"
#include "PlumLog.h"
#include "PlumLogEx.h"
#include "PlumPath.h"
#include "PlumProcess.h"
#include "PlumThread.h"

// Include Convallaria(Script) Library Header File
#include "ConvallariaLua.h"

// Include Window Basic Header File
#include "WinProcess.h"
#include "WinUtilities.h"

// Include ffmpeg Library Header File
extern "C"
{
	#include "libavcodec\avcodec.h"  
	#include "libavformat\avformat.h"  
	#include "libavutil\channel_layout.h"  
	#include "libavutil\common.h"  
	#include "libavutil\imgutils.h"  
	#include "libswscale\swscale.h"   
	#include "libavutil\imgutils.h"      
	#include "libavutil\opt.h"         
	#include "libavutil\mathematics.h"      
	#include "libavutil\samplefmt.h"   
	#include "libswresample/swresample.h"
};

// Include ffmpeg Dynamic Link Library
#pragma comment(lib, "avcodec.lib")  
#pragma comment(lib, "avformat.lib")  
#pragma comment(lib, "avdevice.lib")  
#pragma comment(lib, "avfilter.lib")  
#pragma comment(lib, "avutil.lib")  
#pragma comment(lib, "postproc.lib")  
#pragma comment(lib, "swresample.lib")  
#pragma comment(lib, "swscale.lib")

// Include SDL Library Header File
extern "C"
{
	#include "SDL.h"
	#include "SDL_thread.h"
}

// Include SDL Dynamic Link Library
#pragma comment(lib, "SDL2.lib")

// Inlcude Cerasus(DirectX) Dynamic Link Library
#pragma comment(lib, "Cerasus.lib")

// Include Prunus(C/C++ Win32) Dynamic Link Library
#pragma comment(lib, "Prunus.lib")

// Include Convallaria(Script) Dynamic Link Library
#pragma comment(lib, "Convallaria.lib")

#endif // !__COMMON_H_