#include "StdAfx.h"
#include "SclIEDGrid.h"
#include "SclIED.h"

const int g_nSclImportCols = 6;
CString g_astrSclImportTitle[g_nSclImportCols] = {_T("���"),_T("ѡ��"),_T("IED����"),_T("IED��ʶ"),_T("IP��ַ"),_T("�豸�ͺ�")};
const int g_iSclImportWidth[g_nSclImportCols]={50,50,150 ,80 ,100,100 };

CSclIEDGrid::CSclIEDGrid()
{
	m_nAdjustBeginCol = 1;
}

CSclIEDGrid::~CSclIEDGrid()
{
}

void CSclIEDGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CSclIEDGrid::InitGridTitle()
{
// 	if (m_pDatas == NULL)
// 	{
// 		SetColumnCount(1);
// 		SetRowCount(1);
// 		return;
// 	}

	long nCols = 1;
	const CString *pstrTitle = NULL;
	const int *pnWidth = NULL;

	nCols = g_nSclImportCols;
	pstrTitle = g_astrSclImportTitle;
	pnWidth = g_iSclImportWidth;

	SetColumnCount(nCols);
	CExBaseListGrid::InitGridTitle(pstrTitle, pnWidth, nCols);
}

void CSclIEDGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	switch (nClassID)
	{
	case SCLCLASSID_SCLIED:
		ShowData_Ied(pData, nRow);
		break;
	}

	nRow++;
}

void CSclIEDGrid::ShowData_Ied(CExBaseObject *pObj,int nRow)
{
	CSclIED *pSclIed = (CSclIED *)pObj;
	//_T("���")
	Show_Index(pObj, nRow, 0);

	//_T("ѡ��")
	Show_Check(pObj, nRow, 1, &(pSclIed->m_nChoose));

	//_T("IED����")
	Show_StaticString(pObj, nRow, 2, &(pSclIed->m_strName));

	//_T("IED��ʶ")
	Show_StaticString(pObj, nRow, 3, &(pSclIed->m_strID));

	//_T("IP��ַ")
	Show_StaticString(pObj, nRow, 4, &(pSclIed->m_strIP));

	//_T("�豸�ͺ�")
	Show_StaticString(pObj, nRow, 5, &(pSclIed->m_strDevType));


}

void CSclIEDGrid::ShowDatas(CExBaseList *pDatas)
{
	CExBaseListGrid::ShowDatas(pDatas);
}
