//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GridCharElement.cpp  CGridCharTemplate


#include "stdafx.h"
#include "GridCharTemplate.h"

#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGridCharTemplate::CGridCharTemplate()
{
	//初始化属性

	//初始化成员变量
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
	CString astrTitle[CHARTEMPLATE_COLS] = {g_sLangTxt_Index/*_T("编号")*/,g_sLangTxt_Name/*_T("名称")*/,_T("ID"),g_sLangTxt_CoordinateSystem/*_T("坐标系")*/};

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
