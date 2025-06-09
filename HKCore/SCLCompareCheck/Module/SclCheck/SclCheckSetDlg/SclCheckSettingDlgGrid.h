#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"

#define IDC_GRID_VIRLOOP_DLG_CTRL   41010


class CSclDlgSetGridBase : public CExBaseListGrid
{
public:
	CSclDlgSetGridBase();
	virtual ~CSclDlgSetGridBase();

public:
	virtual void InitGrid();
	virtual void ShowDatas(CExBaseList *pDatas);

	virtual CDataType* FindDataType(const CString &strDataType);

protected:
	UINT m_nOldSclIecCfgClassID;

};

class CSclCheckSettingDlgGrid : public CSclDlgSetGridBase
{
public:
	CSclCheckSettingDlgGrid();
	virtual ~CSclCheckSettingDlgGrid();

public:

	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	void ShowData_CheckType(CExBaseList *pCheckObjec,int nRow);
	void ShowData_SchemaCheckType(CExBaseList *pCheckObjec,int nRow);

	void ShowData_AddFile(CExBaseList *pAddTempsFile,int nRow);
	void ShowData_DataType(CExBaseList *pDataType,int nRow);
};

class CSclImportDlgGrid : public CSclDlgSetGridBase
{
public:
	CSclImportDlgGrid();
	virtual ~CSclImportDlgGrid();

public:

	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	void ShowData_ImportPathType(CExBaseList *pSinglePath,int nRow);
};

