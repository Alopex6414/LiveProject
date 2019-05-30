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

// LiveWall -- Type of PlayStates
typedef enum
{
	Play = 0,
	Pause = 1,
}E_WALLPLAYSTATES;

// LiveWall -- Type of PlayMode
typedef enum
{
	Random	= 0,
	Loop	= 1,
	Repeat	= 2,
	Order	= 3,
}E_WALLPLAYMODE;

// LiveWall -- Type of Video...
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
	char chVideoShot[4096];	// ��Ƶ����(4KB)
}S_WALLVIDEO, *LPS_WALLVIDEO;

// LiveWall -- Type of Graph...
typedef struct
{
	int nNumber;			// ͼ�����(4)
	int nReserved;			// �����ֶ�(4)
	char chGraphName[64];	// ͼ������(64)
	char chGraphAuthor[64];	// ͼ������(64)
	char chGraphID[128];	// ͼ��ID(128)
	char chGraphPath[256];	// ͼ��·��(256)
	char chReserved1[256];	// �����ֶ�1(256)
	char chReserved2[256];	// �����ֶ�2(256)
	char chGraphShot[4096];	// ͼ�ο���(4KB)
}S_WALLGRAPH, *LPS_WALLGRAPH;

#endif // !__TYPES_H_

