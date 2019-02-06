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
	int nNumber;			// 视频序号(4)
	int nReserved;			// 保留字段(4)
	char chVideoName[64];	// 视频名称(64)
	char chVideoAuthor[64];	// 视频作者(64)
	char chVideoTime[64];	// 视频时间(64)
	char chVideoID[128];	// 视频ID(128)
	char chVideoPath[256];	// 视频路径(256)
	char chReserved1[256];	// 保留字段1(256)
	char chReserved2[256];	// 保留字段2(256)
	char chVideoShot[4194304];	// 视频快照(4MB)
}S_WALLVIDEO, *LPS_WALLVIDEO;

#endif // !__TYPES_H_

