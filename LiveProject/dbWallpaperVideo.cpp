/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		dbWallpaperVideo.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "dbWallpaperVideo.h"

// dbWallpaperVideo ��̬��ֽ���ݿ��

CDBWallpaperVideo::CDBWallpaperVideo()
{
	memset(m_chFile, 0, sizeof(m_chFile));

	CPlumPath::PlumPathGetLocalPathA(m_chFile, sizeof(m_chFile));
	strcat_s(m_chFile, "\\db\\LiveProject.db");
}

CDBWallpaperVideo::~CDBWallpaperVideo()
{
}

int CDBWallpaperVideo::Create()
{
	sqlite3* db;
	char *zErrMsg = 0;
	int rc;
	char *sql;

	// open database...
	rc = sqlite3_open(m_chFile, &db);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return rc;
	}

	// create table...
	sql = (char*)"CREATE TABLE WALLPAPERVIDEO" \
		"("  \
		"NNUMBER		INT," \
		"NRESERVED		INT," \
		"CHVIDEONAME	CHAR(64)," \
		"CHVIDEOAUTHOR  CHAR(64)," \
		"CHVIDEOTIME    CHAR(64)," \
		"CHVIDEOID      CHAR(128)," \
		"CHVIDEOPATH    CHAR(256)	PRIMARY KEY		NOT NULL," \
		"CHRESERVED1    CHAR(256)," \
		"CHRESERVED2    CHAR(256)," \
		"CHVIDEOSHOT    CHAR(4096)" \
		");";

	// execute sql...
	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if (rc != SQLITE_OK) 
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return rc;
	}

	// close database...
	sqlite3_close(db);

	return 0;
}

int CDBWallpaperVideo::Insert(S_WALLVIDEO * pWallVideoInfo)
{
	sqlite3* db;
	char *zErrMsg = 0;
	int rc;
	char chsql[16384] = { 0 };

	// open database...
	rc = sqlite3_open(m_chFile, &db);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return rc;
	}

	// insert table...
	sprintf_s(chsql, "INSERT INTO WALLPAPERVIDEO" \
		"(" \
		"NNUMBER, " \
		"NRESERVED, " \
		"CHVIDEONAME, " \
		"CHVIDEOAUTHOR, " \
		"CHVIDEOTIME, " \
		"CHVIDEOID, " \
		"CHVIDEOPATH, " \
		"CHRESERVED1, " \
		"CHRESERVED2, " \
		"CHVIDEOSHOT" \
		") " \
		"VALUES" \
		"(" \
		"%d, " \
		"%d, " \
		"'%s', " \
		"'%s', " \
		"'%s', " \
		"'%s', " \
		"'%s', " \
		"'%s', " \
		"'%s', " \
		"'%s'" \
		");",
		pWallVideoInfo->nNumber,
		pWallVideoInfo->nReserved,
		pWallVideoInfo->chVideoName,
		pWallVideoInfo->chVideoAuthor,
		pWallVideoInfo->chVideoTime,
		pWallVideoInfo->chVideoID,
		pWallVideoInfo->chVideoPath,
		pWallVideoInfo->chReserved1,
		pWallVideoInfo->chReserved2,
		pWallVideoInfo->chVideoShot);

	// execute sql...
	rc = sqlite3_exec(db, chsql, NULL, 0, &zErrMsg);
	if (rc != SQLITE_OK) 
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return rc;
	}

	// close database...
	sqlite3_close(db);

	return 0;
}
