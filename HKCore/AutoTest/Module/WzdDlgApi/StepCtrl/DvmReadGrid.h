#pragma once
#include "WzdDlgStyleGrid.h"

class CDvmReadGrid : public CWzdDlgStyleGrid
{
public:
	enum{
		Ain,
		FileDir,
		Normal,
		Journal
	};
	long m_nType;

protected:
	void InitGridTitle_Ain();
	void InitGridTitle_FileDir();
	void InitGridTitle_Normal();
	void InitGridTitle_Journal();

	void ShowData_Ain(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	void ShowData_FileDir(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	void ShowData_Normal(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	void ShowData_Journal(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);

	CString mms_GetDAName(tagDA *pDA);
	CString mms_GetDADataType(tagDA *pDA);
	CString mms_GetDAPath(tagDA *pDA);
	CString mms_GetDAUnit(tagDA *pDA);
	long GetSubDACol(ST_CHAR *pmmsDAName, long nPos);
	void ShowAinText(long nRow, tagDA *pSubDA, long nPos);
public:
	CDvmReadGrid();
	virtual ~CDvmReadGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
};