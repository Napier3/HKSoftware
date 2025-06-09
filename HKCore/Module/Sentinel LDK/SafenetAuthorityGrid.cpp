//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��


#include "stdafx.h"
#include "SafenetAuthorityGrid.h"
#include "../XLanguage/XLanguageMngr.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSafenetAuthorityGrid::CSafenetAuthorityGrid()
{
	//��ʼ������

	//��ʼ����Ա����
	m_bUseEnable = TRUE;
}

CSafenetAuthorityGrid::~CSafenetAuthorityGrid()
{

}


void CSafenetAuthorityGrid::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(SAFENET_AUTHORITY_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSafenetAuthorityGrid::InitGridTitle()
{
#ifdef NOT_USE_XLANGUAGE
	CString astrGridTitle[SAFENET_AUTHORITY_COLS] = {_T("���"),_T("ѡ��"),_T("����"),_T("ID")
#else
	CString astrGridTitle[SAFENET_AUTHORITY_COLS] = {/*_T("���")*/g_sLangTxt_Index
		,/*_T("ѡ��")*/g_sLangTxt_Select
		,/*_T("����")*/g_sLangTxt_Name
		,_T("ID")
#endif
		};
	int iGridWidth[SAFENET_AUTHORITY_COLS]={50,60,100, 60};

	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, SAFENET_AUTHORITY_COLS);
}

void CSafenetAuthorityGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CSafenetAuthority *pAuthority = (CSafenetAuthority*)pData;

	Show_Index(pAuthority, nRow, SAFENET_AUTHORITY_COL_INDEX);

	if (m_bUseEnable)
	{
		Show_Check(pAuthority, nRow, SAFENET_AUTHORITY_COL_SEL, (long*)&pAuthority->m_nEnable);
	}
	else
	{
		if (pAuthority->m_nEnable)
		{
			Show_StaticString(pAuthority, nRow, SAFENET_AUTHORITY_COL_SEL, _T("*"));
		}
		else
		{
			Show_StaticString(pAuthority, nRow, SAFENET_AUTHORITY_COL_SEL, _T(""));
		}
	}

	Show_StaticString(pAuthority, nRow, SAFENET_AUTHORITY_COL_NAME, &pAuthority->m_strName);
	Show_StaticString(pAuthority, nRow, SAFENET_AUTHORITY_COL_ID, &pAuthority->m_strID);

	nRow++;
}
