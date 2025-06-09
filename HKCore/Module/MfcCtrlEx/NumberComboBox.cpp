// NumberComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "NumberComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNumberComboBox

IMPLEMENT_DYNAMIC(CNumberComboBox, CComboBox)

CNumberComboBox::CNumberComboBox()
{
	m_nDefault = 0;
}

CNumberComboBox::~CNumberComboBox()
{
}


BEGIN_MESSAGE_MAP(CNumberComboBox, CComboBox)
END_MESSAGE_MAP()



// CNumberComboBox 消息处理程序

long CNumberComboBox::GetNumber()
{
	long nSel = GetCurSel();

	if (nSel == CB_ERR)
	{
		return m_nDefault;
	}
	else
	{
		return GetItemData(nSel);
	}
}

long CNumberComboBox::GetNumber(long &nNumber)
{
	nNumber = GetNumber();
	return nNumber;
}

void CNumberComboBox::SelNumber(long nNumber)
{
	CString strNumber;
	long nIndex = 0;
	long i = 0;
	long nCount = GetCount();
	long nSelIndex = -1;

	for (i = 0; i < nCount; i++)
	{
		nIndex = GetItemData(i);
		
		if (nIndex == nNumber)
		{
			nSelIndex = i;
			break;
		}
	}

	if (nSelIndex == -1)
	{
		nSelIndex = 0;
	}

	SetCurSel(nSelIndex);
}

void CNumberComboBox::InitNumbers(long nBegin, long nEnd, long nDefault)
{
	m_nDefault = nDefault;
	CString strNumber;
	long nIndex = 0;
	long i = 0;

	for (i = nBegin; i <= nEnd; i++)
	{
		strNumber.Format(_T("%d"), i);
		nIndex = AddString(strNumber);
		SetItemData(nIndex, i);
	}

	SelNumber(nDefault);
}

