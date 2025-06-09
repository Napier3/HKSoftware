#include "StdAfx.h"
#include "XTFTempGrid.h"
#include "..\..\Module\KeyDb\XMatchObject.h"
#include "XTFFuncBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CXTFTmplGrid
CXtfTempGrid::CXtfTempGrid()
{
	m_nAdjustBeginCol = 0;
}


CXtfTempGrid::~CXtfTempGrid(void)
{

}

void CXtfTempGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(3);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CXtfTempGrid::InitGridTitle()
{
	CString cTempStr[3]={_T("ÐòºÅ"),_T("Ä£°å"),_T("×ÓÄ£°å")};
	int iWidth[3]={60,320, 320};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, 3);
}	

void CXtfTempGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	CXTFFuncBase *pFuncBase = (CXTFFuncBase*)pData;

	if (KTFCLASSID_CXFUNCBASE != nClassID)
	{
		return;
	}

	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pFuncBase->m_strName);

	ASSERT (pFuncBase->m_pTemplate != NULL);

	if (pFuncBase->m_pTemplate != NULL)
	{
		Show_StaticString(pData, nRow, 2, pFuncBase->m_pTemplate->m_strName);
	}

	nRow++;
}

