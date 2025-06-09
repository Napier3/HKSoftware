#include "stdafx.h"
#include "GuideBook\Script/GbScript_GlobalDefine.h"
#include "TestAppEditGrid.h"
#include "XLanguageResourceAts_AutoTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestAppEditGrid::CTestAppEditGrid(void)
{
	m_nAdjustBeginCol = 0;
	m_pTestAppDefine = NULL;

}

CTestAppEditGrid::~CTestAppEditGrid(void)
{
}

void CTestAppEditGrid::InitGrid()
{
	SetListMode(TRUE);
	SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(1);
	SetColumnCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);

	InitGridTitle();

	ResetScrollBars();
}

void CTestAppEditGrid::InitGridTitle()
{
	CString strTitle[20];
	int iWidth[20];
	long nIndex = 1;
	strTitle[0] = g_sLangTxt_SerNumber;
	iWidth[0] = 80;
	//ASSERT (m_pTestAppDefine != NULL);
	long nCount =  1;

	if (m_pTestAppDefine != NULL)
	{
		nCount = m_pTestAppDefine->GetCount() +1;
		POS pos = m_pTestAppDefine->GetHeadPosition();
		CDvmData *pData = NULL;
		SetColumnCount(nCount);

		while (pos != NULL)
		{
			pData = (CDvmData *)m_pTestAppDefine->GetNext(pos);
			strTitle[nIndex] = pData->m_strName;
			iWidth[nIndex] = 80;
			nIndex++;

			if (nIndex >= 20)
			{
				ASSERT (FALSE);
				break;
			}
		}
	}

	//SetRowCount(nCount);

	CExBaseListGrid::InitGridTitle(strTitle, iWidth, nCount);
}

void CTestAppEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pTestApp = (CDvmData*)pData;
	CDvmValue *pValue = NULL;

	Show_Index(pTestApp, nRow, 0);
	long nCol = 1;
	POS pos = m_pTestAppDefine->GetHeadPosition();
	CDvmData *pDef = NULL;

	while (pos != NULL)
	{
		pDef = (CDvmData *)m_pTestAppDefine->GetNext(pos);

		if (pDef == NULL)
		{
			break;
		}

		pValue = (CDvmValue *)pTestApp->FindByID(pDef->m_strID);

		if (pValue != NULL)
		{
			Show_String(pValue, nRow, nCol, &pValue->m_strValue);
		}
		else
		{
			Show_StaticString(pValue, nRow, nCol, m_strEmptyString);
		}	

		nCol++;
	}

	nRow++;
}
