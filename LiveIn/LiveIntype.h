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
	float fAlpha;		//����Alphaֵ
	int nMoveDirect;	//�����ƶ�����
	int nRotateDirect;	//������ת����
	float fFallSpeed;	//���������ٶ�
	float fMoveSpeed;	//�����ƶ��ٶ�
	float fRotateSpeed;	//������ת�ٶ�
	DirectSpriteTransformPara sTransformPara;	//���ӱ任����
}TLIVEINSTAR, *LPTLIVEINSTAR;

#endif // !__LIVEINTYPE_H_

