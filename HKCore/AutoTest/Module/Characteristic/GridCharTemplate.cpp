//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GridCharElement.cpp  CGridCharTemplate


#include "stdafx.h"
#include "GridCharTemplate.h"

#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGridCharTemplate::CGridCharTemplate()
{
	//��ʼ������

	//��ʼ����Ա����
}

CGridCharTemplate::~CGridCharTemplate()
{

}


void CGridCharTemplate::InitGrid()
{
	m_nAdjustBeginCol = -1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(CHARTEMPLATE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CGridCharTemplate::InitGridTitle()
{
	CString astrTitle[CHARTEMPLATE_COLS] = {g_sLangTxt_Index/*_T("���")*/,g_sLangTxt_Name/*_T("����")*/,_T("ID"),g_sLangTxt_CoordinateSystem/*_T("����ϵ")*/};

	int iWidth[CHARTEMPLATE_COLS]={50,120,80, 80};

	CExBaseListGrid::InitGridTitle(astrTitle, iWidth, CHARTEMPLATE_COLS);
}

void CGridCharTemplate::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCharacteristic *pCharTemplate = (CCharacteristic*)pData;

	Show_Index(pCharTemplate, nRow, CHARTEMPLATE_COL_INDEX);
	Show_String(pCharTemplate, nRow, CHARTEMPLATE_COL_NAME, &pCharTemplate->m_strName, EndEditCell_String_Name);
	Show_String(pCharTemplate, nRow, CHARTEMPLATE_COL_ID, &pCharTemplate->m_strID, EndEditCell_String_ID);
	Show_StaticString(pCharTemplate, nRow, CHARTEMPLATE_COL_AXIS,&pCharTemplate->m_strAxis);
	
	nRow++;
}
