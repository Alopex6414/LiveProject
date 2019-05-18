/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		dbWallpaperGraph.cpp
* @brief	This Program is LiveProject Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-20
*/
#include "dbWallpaperGraph.h"

// dbWallpaperGraph 动态壁纸数据库表

CDBWallpaperGraph::CDBWallpaperGraph()
{
	memset(m_chFile, 0, sizeof(m_chFile));

	CPlumPath::PlumPathGetLocalPathA(m_chFile, sizeof(m_chFile));
	strcat_s(m_chFile, "\\db\\LiveProject.db");
}

CDBWallpaperGraph::~CDBWallpaperGraph()
{
}

int CDBWallpaperGraph::Create()
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	char* sql;

	// open database...
	rc = sqlite3_open(m_chFile, &db);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return rc;
	}

	// create table...
	sql = (char*)"CREATE TABLE WALLPAPERGRAPH" \
		"("  \
		"NNUMBER		INT," \
		"NRESERVED		INT," \
		"CHGRAPHNAME	CHAR(64)," \
		"CHGRAPHAUTHOR  CHAR(64)," \
		"CHGRAPHID      CHAR(128)," \
		"CHGRAPHPATH    CHAR(256)	PRIMARY KEY		NOT NULL," \
		"CHRESERVED1    CHAR(256)," \
		"CHRESERVED2    CHAR(256)," \
		"CHGRAPHSHOT    CHAR(4096)" \
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

int CDBWallpaperGraph::Insert(S_WALLGRAPH* pWallGraphInfo)
{
	sqlite3* db;
	char* zErrMsg = 0;
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
	sprintf_s(chsql, "INSERT INTO WALLPAPERGRAPH" \
		"(" \
		"NNUMBER, " \
		"NRESERVED, " \
		"CHGRAPHNAME, " \
		"CHGRAPHAUTHOR, " \
		"CHGRAPHID, " \
		"CHGRAPHPATH, " \
		"CHRESERVED1, " \
		"CHRESERVED2, " \
		"CHGRAPHSHOT" \
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
		"'%s'" \
		");",
		pWallGraphInfo->nNumber,
		pWallGraphInfo->nReserved,
		pWallGraphInfo->chGraphName,
		pWallGraphInfo->chGraphAuthor,
		pWallGraphInfo->chGraphID,
		pWallGraphInfo->chGraphPath,
		pWallGraphInfo->chReserved1,
		pWallGraphInfo->chReserved2,
		pWallGraphInfo->chGraphShot);

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

int CDBWallpaperGraph::Update(S_WALLGRAPH* pWallGraphInfo, const char* szPrimaryKey)
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	char chsql[16384] = { 0 };

	// open database...
	rc = sqlite3_open(m_chFile, &db);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return rc;
	}

	// update table...
	sprintf_s(chsql, "UPDATE WALLPAPERGRAPH SET " \
		"NNUMBER = %d, " \
		"NRESERVED = %d, " \
		"CHGRAPHNAME = '%s', " \
		"CHGRAPHAUTHOR = '%s', " \
		"CHGRAPHID = '%s', " \
		"CHGRAPHPATH = '%s', " \
		"CHRESERVED1 = '%s', " \
		"CHRESERVED2 = '%s', " \
		"CHGRAPHSHOT = '%s' " \
		"WHERE CHGRAPHPATH = '%s';",
		pWallGraphInfo->nNumber,
		pWallGraphInfo->nReserved,
		pWallGraphInfo->chGraphName,
		pWallGraphInfo->chGraphAuthor,
		pWallGraphInfo->chGraphID,
		pWallGraphInfo->chGraphPath,
		pWallGraphInfo->chReserved1,
		pWallGraphInfo->chReserved2,
		pWallGraphInfo->chGraphShot,
		szPrimaryKey);

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

int CDBWallpaperGraph::Delete(const char* szPrimaryKey)
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	char chsql[16384] = { 0 };

	// open database...
	rc = sqlite3_open(m_chFile, &db);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return rc;
	}

	// delete table...
	sprintf_s(chsql, "DELETE FROM WALLPAPERGRAPH WHERE CHGRAPHPATH = '%s';", szPrimaryKey);

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

int CDBWallpaperGraph::Select(LPDBWALLGRAPHSEEKCALLBACK pfunc)
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	char* sql;

	// open database...
	rc = sqlite3_open(m_chFile, &db);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return rc;
	}

	// seek table...
	sql = (char*)"SELECT * FROM WALLPAPERGRAPH;";

	// execute sql...
	rc = sqlite3_exec(db, sql, pfunc, 0, &zErrMsg);
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

int CDBWallpaperGraph::Select(LPDBWALLGRAPHSEEKCALLBACK pfunc, const char* szGraphName)
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	char chsql[16384] = { 0 };

	// open database...
	rc = sqlite3_open(m_chFile, &db);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return rc;
	}

	// seek table...
	sprintf_s(chsql, "SELECT * FROM WALLPAPERGRAPH WHERE CHGRAPHNAME LIKE '%%%s%%';", szGraphName);

	// execute sql...
	rc = sqlite3_exec(db, chsql, pfunc, 0, &zErrMsg);
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
