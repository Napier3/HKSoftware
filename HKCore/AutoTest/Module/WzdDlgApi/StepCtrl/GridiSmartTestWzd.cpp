#include "StdAfx.h"
#include "GridiSmartTestWzd.h"
#include "../StepDlg/WzdFile.h"

CGridiSmartTestWzd::CGridiSmartTestWzd(void)
{
}

CGridiSmartTestWzd::~CGridiSmartTestWzd(void)
{
}

void CGridiSmartTestWzd::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(RECORD_TABLE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CGridiSmartTestWzd::InitGridTitle()
{
	CString astrGridTitle[RECORD_TABLE_COLS] = {_T("ÐòºÅ"),_T("×°ÖÃÃèÊö"),_T("×°ÖÃÐÍºÅ"),_T("¼ìÑéÊ±¼ä")};
	int iGridWidth[RECORD_TABLE_COLS]={50, 230, 230, 230};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, RECORD_TABLE_COLS);
}

void CGridiSmartTestWzd::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);
	CWzdFile *pFileData = (CWzdFile*)pData; 
 	if (pFileData == NULL)
 	{
 		return;
 	}
 
 	Show_Index(pFileData->m_pFile, nRow, 0);	 //ÐòºÅ
 	Show_StaticString(pFileData->m_pFile, nRow, 1, &pFileData->m_strFileName);	  //
	Show_StaticString(pFileData->m_pFile, nRow, 2, &pFileData->m_strFileType);	  //

	SYSTEMTIME time = pFileData->m_tmYun;
	TCHAR szDateTime[256] = {0};
    _stprintf(szDateTime, _T("%02d-%02d-%02d %02d:%02d:%02d"), time.wYear,time.wMonth,
              time.wDay, time.wHour, time.wMinute, time.wSecond);
    CString str = szDateTime;
	Show_StaticString(pFileData->m_pFile, nRow, 3, &str);

	//CString strPath = pFileData->m_strName;
	//int p = strPath.Find(_T("Workspace"));
	//if(p != -1)
	//{
	//	strPath = strPath.Right(strPath.GetLength() - p - 9);
	//	strPath.Replace(pFileData->m_strID, _T(""));
	//	Show_StaticString(pFileData->m_pFile, nRow, 4, &strPath);
	//}

	nRow++;
}

void CGridiSmartTestWzd::ShowDatas(CExBaseList *pDataList, BOOL bInsertRow)
{
	if (pDataList == NULL)
	{
		SetRowCount(1);
		return;
	}

	POS pos = pDataList->GetHeadPosition();
	int nRowIndex = 1;
	CExBaseObject *pObj = NULL;
	long nCalRows = pDataList->GetCount() + 1;
	SetRowCount(nCalRows, bInsertRow);

	while (pos != NULL)
	{
		pObj = pDataList->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bInsertRow);
	AfterShowDatas(1, bInsertRow);
	
	//SortTextItems(SORT_TABLE_COLS, false);
}
