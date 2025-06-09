// DrawPage.cpp: implementation of the CDrawPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawPage::CDrawPage()
{

}

CDrawPage::~CDrawPage()
{
	m_listChild.RemoveAll();
}

void CDrawPage::GetDrawVariables(CDrawBaseObjectList& oList)
{
}

void CDrawPage::SetDrawVariables(CDrawBaseObjectList& oList)
{
	m_listChild.RemoveAll();
	void* pos = oList.GetHeadPosition();
	
	while (pos != NULL)
	{
		CDrawVariable* pVariable = (CDrawVariable*)m_listChild.GetHead();
		m_listChild.RemoveAll();
	}
}
