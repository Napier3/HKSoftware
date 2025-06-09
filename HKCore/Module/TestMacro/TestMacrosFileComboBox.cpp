// TestMacrosFileComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "TestMacrosFileComboBox.h"
#include "TestMacrosFileMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTestMacrosFileComboBox::CTestMacrosFileComboBox()
{
	
}


CTestMacrosFileComboBox::~CTestMacrosFileComboBox()
{
	
}

void CTestMacrosFileComboBox::ShowTestMacrosFiles()
{
	m_pList = CTestMacrosFileMngr::g_pTestMacrosFileMngr;;
	//m_bAddEmptyString = TRUE;
	ShowBaseList();
}

void CTestMacrosFileComboBox::ShowBaseList()
{
	ResetContent();
// 
// 	if (m_bAddEmptyString)
// 	{
// 		long nIndex = AddString(_T(""));
// 		SetItemDataPtr(nIndex, NULL);
// 	}

	CTestMacrosFile *p = NULL;
	POS pos = m_pList->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CTestMacrosFile*)m_pList->GetNext(pos);
		
		if (p->m_nEnable == 1)
		{
			AddObj(p);
		}
	}
}
