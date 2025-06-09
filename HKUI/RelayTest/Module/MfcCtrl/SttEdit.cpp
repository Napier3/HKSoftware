// SttEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "SttEdit.h"


// CSttEdit

IMPLEMENT_DYNAMIC(CSttEdit, CEdit)

CSttEdit::CSttEdit()
{

}

CSttEdit::~CSttEdit()
{
}


BEGIN_MESSAGE_MAP(CSttEdit, CEdit)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CSttEdit 消息处理程序



void CSttEdit::OnKillFocus(CWnd* pNewWnd)
{
	CString strValue1;

	if (m_pRefData != NULL)
	{
		strValue1 = m_pRefData->m_strValue;
	}

	SaveData();

	CEdit::OnKillFocus(pNewWnd);

	if (m_pRefData != NULL)
	{
		if (m_pRefData->m_strValue != strValue1)
		{
			OnSttDataChanged();
		}
	}

}

void CSttEdit::ShowData()
{
	if (m_pRefData == NULL)
	{
		return;
	}

	SetWindowText(m_pRefData->m_strValue);
}

void CSttEdit::SaveData()
{
	if (m_pRefData == NULL)
	{
		return;
	}

	GetWindowText(m_pRefData->m_strValue);
}

