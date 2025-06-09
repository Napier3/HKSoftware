#include "StdAfx.h"
#include "XLangFilesGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CXLangFilesGrid::CXLangFilesGrid()
{

}


CXLangFilesGrid::~CXLangFilesGrid(void)
{
	
}

void CXLangFilesGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(2);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CXLangFilesGrid::InitGridTitle()
{
	CString cTempStr[2]={_T("序号")	,_T("文件名")};
	int iWidth[2]={60,200};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, 2);
}

void CXLangFilesGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{

}

 void CXLangFilesGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
 {
	 m_pMngr = (CXLangFolderMngr*)pDatas;

	 //显示所有文件列表，汇总所有资源文件
	 InitGridRows();

	 //遍历所有语言，显示资源文件
	 CXLangFolder *pFolder = NULL;
	 POS pos = m_pMngr->GetHeadPosition();
	 long nCol = 2;

	 while (pos != NULL)
	 {
		 pFolder = (CXLangFolder *)m_pMngr->GetNext(pos);
		 InsertColumn(pFolder->m_strName);
		 SetColumnWidth(nCol, 200);
		 ShowDatas(pFolder, nCol);
		 nCol++;
	 }
 }

 //显示所有文件列表，汇总所有资源文件
 void CXLangFilesGrid::InitGridRows()
 {
	 long nRows = m_pMngr->m_oAllFile.GetCount();
	 SetRowCount(nRows+1);
	 POS posFile = m_pMngr->m_oAllFile.GetHeadPosition();
	 CXLangFile *pFile = NULL;
	 long nIndex = 1;

	 while (posFile != NULL)
	 {
		 pFile = (CXLangFile*)m_pMngr->m_oAllFile.GetNext(posFile);
		 Show_Index(pFile, nIndex, XLANGFILE_COL_ID_INDEX);
		 Show_StaticString(pFile, nIndex, XLANGFILE_COL_ID_FILE, &pFile->m_strName);
		 nIndex++;
	 }
 }

 void CXLangFilesGrid::ShowDatas(CExBaseList *pDatas, long nCol)
 {
	 CXLangFolder *pFolder = (CXLangFolder *)pDatas;
	 POS posFile = pFolder->GetHeadPosition();
	 CXLangFile *pFile = NULL;
	 long nIndex = 1;

	 while (posFile != NULL)
	 {
		 pFile = (CXLangFile *)pFolder->GetNext(posFile);
		 nIndex = m_pMngr->m_oAllFile.FindLangFileIndex(pFile->m_strID);

		 ASSERT (nIndex >= 0);
		 Show_StaticString(pFile, nIndex+1, nCol, &pFile->m_strName);
	 }
 }

