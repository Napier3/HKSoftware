#pragma once

#include "..\GridBase\ExBaseListGrid.h"

#define DVM_ANLS_COL_INDEX       0
#define DVM_ANLS_COL_NAME        1
#define DVM_ANLS_COL_KEYS          2
#define DVM_ANLS_COL_STXML    3

#define DVM_ANLS_COLS        4


class CDvmAnlsDatasetGrid : public CExBaseListGrid
{
public:
	CDvmAnlsDatasetGrid();
	virtual ~CDvmAnlsDatasetGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

protected:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	CString InitDataKey(CExBaseObject *pExBaseObject);

public:

};

// 
// class CDvmAnlsTempGrid : public CExBaseListGrid
// {
// public:
// 	CDvmAnlsTempGrid();
// 	virtual ~CDvmAnlsTempGrid();
// 
// 	virtual void InitGrid();
// 	virtual void InitGridTitle();
// 
// protected:
// 	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
// };