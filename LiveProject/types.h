/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		types.h
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#pragma once

#ifndef __TYPES_H_
#define __TYPES_H_

// Struct & Enum Types Definitions.
typedef struct
{
	int nNumber;			// ��Ƶ���(4)
	int nReserved;			// �����ֶ�(4)
	char chVideoName[64];	// ��Ƶ����(64)
	char chVideoAuthor[64];	// ��Ƶ����(64)
	char chVideoTime[64];	// ��Ƶʱ��(64)
	char chVideoID[128];	// ��ƵID(128)
	char chVideoPath[256];	// ��Ƶ·��(256)
	char chReserved1[256];	// �����ֶ�1(256)
	char chReserved2[256];	// �����ֶ�2(256)
	char chVideoShot[4194304];	// ��Ƶ����(4MB)
}S_WALLVIDEO, *LPS_WALLVIDEO;

#endif // !__TYPES_H_

