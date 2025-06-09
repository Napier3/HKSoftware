//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GridCharElement.cpp  CGridCharTestLine


#include "stdafx.h"
#include "GridCharTestLine.h"

#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGridCharTestLine::CGridCharTestLine()
{
	//��ʼ������

	//��ʼ����Ա����
}

CGridCharTestLine::~CGridCharTestLine()
{

}


void CGridCharTestLine::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(CHARTESTLINE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CGridCharTestLine::InitGridTitle()
{
	CString astrTitle[CHARTESTLINE_COLS] = {g_sLangTxt_Index/*_T("���")*/,g_sLangTxt_EdgeType/*_T("����")*/,g_sLangTxt_Location/*_T("λ��")*/,g_sLangTxt_RotationAngle/*_T("��ת�Ƕ�")*/,g_sLangTxt_CustomAngle/*_T("�Զ����߽Ƕ�")*/};

	int iWidth[CHARTESTLINE_COLS]={40,60, 60, 80,100};

	CExBaseListGrid::InitGridTitle(astrTitle, iWidth, CHARTESTLINE_COLS);
}

void CGridCharTestLine::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCharElementTestLine *pTestLine = (CCharElementTestLine*)pData;

	if(pData->GetClassID() != CHARCLASSID_CCHARELEMENTTESTLINE)
	{
		return;
	}

	Show_Index(pTestLine, nRow, CHARTESTLINE_COL_INDEX);
	Show_StaticString(pTestLine, nRow, CHARTESTLINE_COL_TYPE, &pTestLine->m_strType);
	Show_Double(pTestLine, nRow, CHARTESTLINE_COL_POS,&pTestLine->m_fPos, FALSE);
	Show_Double(pTestLine, nRow, CHARTESTLINE_COL_ROTATEANGLE, &pTestLine->m_fRotateAngle, FALSE);
	Show_StaticString(pTestLine, nRow, CHARTESTLINE_COL_ANGLEDEF, &pTestLine->m_strAngleDef);

// 	Show_Long(pElement, nRow, CHARTESTLINE_COL_POINTS, &pElement->m_nTestPoints);
// 	Show_StaticString(pElement, nRow, CHARTESTLINE_COL_DETAIL, pElement->ReturnXml());

	nRow++;
}

void  CGridCharTestLine::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{

}
