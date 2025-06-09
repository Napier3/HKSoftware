//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GridCharElement.cpp  CGridTestMacrosFile


#include "stdafx.h"
#include "GridTestMacrosFile.h"
#include "..\XLanguage\XLanguageResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CGridTestMacrosFile::CGridTestMacrosFile()
{
	//初始化属性

	//初始化成员变量
	m_nAdjustBeginCol = 1;
}

CGridTestMacrosFile::~CGridTestMacrosFile()
{

}


void CGridTestMacrosFile::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);

	SetColumnCount(TESTMCACROFILE_COLS);

	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CGridTestMacrosFile::InitGridTitle()
{
	CString astrSclIecCfgTitleGIn[TESTMCACROFILE_COLS] = 
	{g_sLangTxt_Index/*_T("编号")*/
	,g_sLangTxt_Name/*_T("名称")*/
	,g_sLangTxt_TestInstSel/*_T("测试仪选择")*/
	,g_sLangTxt_TestFctnFile/*_T("测试功能标准文件")*/
	,g_sLangTxt_CommunStraFile/*_T("通讯标准文件")*/};

	int iSclIecCfgWidthGin[TESTMCACROFILE_COLS]={40,100,100,100,120};

	CExBaseListGrid::InitGridTitle(astrSclIecCfgTitleGIn, iSclIecCfgWidthGin, TESTMCACROFILE_COLS);
}

void CGridTestMacrosFile::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CTestMacrosFile *pMacroFile = (CTestMacrosFile*)pData;

	Show_Index(pMacroFile, nRow, TESTMCACROFILE_COL_INDEX);
	Show_StaticString(pMacroFile, nRow, TESTMCACROFILE_COL_NAME, &pMacroFile->m_strName);
	Show_ComboBox(pMacroFile, nRow, TESTMCACROFILE_COL_APPID, pMacroFile->P_ActiveMacroTestID());
	Show_StaticString(pMacroFile, nRow, TESTMCACROFILE_COL_MACROFILE, pMacroFile->P_File());
	Show_StaticString(pMacroFile, nRow, TESTMCACROFILE_COL_CMMFILE, pMacroFile->P_CmmFile());

	nRow++;
}


void CGridTestMacrosFile::FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd)//填充comboList cell
{
	CGridCell *pCell = GetCell(nRow, nCol);
	ASSERT(pCell != NULL);
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA )pCell->lParam;
	ASSERT(pVCellData != NULL);
	CExBaseList *pExBaseList = pVCellData->pExBaseList;

	if (pExBaseList != NULL)
	{
		CComboBox *pComboBox = (CComboBox *)cltWnd;
		ASSERT(pComboBox != NULL);

		pComboBox->ResetContent();

		if (is_exgrid_cmb_set_add_empty(pExBaseList))
		{
			pComboBox->AddString(_T(""));
			pComboBox->SetItemDataPtr(0, NULL);
		}

		CExBaseObject *pObj = NULL;
		POS pos = pExBaseList->GetHeadPosition();

		while (pos != NULL)
		{
			pObj = pExBaseList->GetNext(pos);

			if (pObj->GetClassID() == TMCLASSID_CTESTMACROCONFIG)
			{
				pObj->InsertComboBox(pComboBox);
			}
		}
	}
}
