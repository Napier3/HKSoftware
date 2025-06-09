#include "stdafx.h"
#include "UISftRsltWndMacEdit.h"
#include "../GuideBook/GbDataTypeMngr.h"
#include <locale.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CUISftRsltWndMacEdit::CUISftRsltWndMacEdit()
{
	m_pResultWndInterface = NULL;
}

CUISftRsltWndMacEdit::~CUISftRsltWndMacEdit()
{

}

BEGIN_MESSAGE_MAP(CUISftRsltWndMacEdit, CMacEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, &CUISftRsltWndMacEdit::OnEnChange)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, &CUISftRsltWndMacEdit::OnEnKillfocus)
END_MESSAGE_MAP()


void CUISftRsltWndMacEdit::OnEnChange()
{
	OnEnKillfocus();
}

void CUISftRsltWndMacEdit::OnEnKillfocus()
{
	CString strData = GetMacText();

	if (m_pResultWndInterface != NULL)
	{
		m_pResultWndInterface->OnResultDataChanged(strData);
	}
}
