/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveInType.h
* @brief	This Program is LiveIn Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-17
*/
#pragma once

#ifndef __LIVEINTYPE_H_
#define __LIVEINTYPE_H_

// Include Common Header File
#include "Common.h"

// LiveIn Type Definition
typedef struct
{
	float fAlpha;		//粒子Alpha值
	int nMoveDirect;	//粒子移动方向
	int nRotateDirect;	//粒子旋转方向
	float fFallSpeed;	//粒子下落速度
	float fMoveSpeed;	//粒子移动速度
	float fRotateSpeed;	//粒子旋转速度
	S_DX_SPRITE_TRANSFORM_PARA sTransformPara;	//粒子变换参数
}TLIVEINSTAR, *LPTLIVEINSTAR;

#endif // !__LIVEINTYPE_H_

