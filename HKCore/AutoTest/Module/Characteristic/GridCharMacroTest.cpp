//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GridCharElement.cpp  CGridCharMacroTest


#include "stdafx.h"
#include "GridCharMacroTest.h"

#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGridCharMacroTest::CGridCharMacroTest()
{
	//��ʼ������

	//��ʼ����Ա����
}

CGridCharMacroTest::~CGridCharMacroTest()
{

}


void CGridCharMacroTest::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(CHARMACROTEST_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CGridCharMacroTest::InitGridTitle()
{
	CString astrSclIecCfgTitleGIn[CHARMACROTEST_COLS] = {g_sLangTxt_Index/*_T("���")*/,g_sLangTxt_EdgeType/*_T("����")*/,g_sLangTxt_CordnPtn/*_T("����ģʽ")*/,g_sLangTxt_TestFctnSel/*_T("���Թ���ѡ��")*/
	,_T("bx-id"),_T("ey-id"),_T("setx-id"),_T("sety-id")
	,_T("ex-id"),_T("ey-id"),_T("actx-id"), _T("acty-id")};

	int iSclIecCfgWidthGin[CHARMACROTEST_COLS]={40,80,80, 100,80,80,80,80,80,80,80,80 };

	CExBaseListGrid::InitGridTitle(astrSclIecCfgTitleGIn, iSclIecCfgWidthGin, CHARMACROTEST_COLS);
}

void CGridCharMacroTest::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCharElement *pElement = (CCharElement*)pData;

	Show_Index(pElement, nRow, CHARMACROTEST_COL_INDEX);
	Show_StaticString(pElement, nRow, CHARMACROTEST_COL_TYPE, &pElement->m_strName);

// 	Show_Long(pElement, nRow, CHARMACROTEST_COL_POINTS, &pElement->m_nTestPoints);
// 	Show_StaticString(pElement, nRow, CHARMACROTEST_COL_DETAIL, pElement->ReturnXml());

	nRow++;
}

void  CGridCharMacroTest::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{

}
