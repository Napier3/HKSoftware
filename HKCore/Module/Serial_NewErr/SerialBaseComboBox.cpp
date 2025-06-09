// SerialCheckComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialBaseComboBox.h"

// CSerialCheckComboBox

CSerialBaseComboBox::CSerialBaseComboBox()
{

}

CSerialBaseComboBox::~CSerialBaseComboBox()
{
}

// CSerialCheckComboBox 消息处理程序



void CSerialBaseComboBox::SetSelect(const CString &strValue)
{
	long nCount = GetCount();
	long nIndex = 0;
	long nIndexFind = -1;
	CString strText;

	for (nIndex=0;  nIndex<nCount; nIndex++)
	{
		GetLBText(nIndex, strText);

		if (strText == strValue)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	SetCurSel(nIndexFind);
}

void CSerialBaseComboBox::SetSelect(long nValue)
{
	long nCount = GetCount();
	long nIndex = 0;
	long nIndexFind = -1;

	for (nIndex=0;  nIndex<nCount; nIndex++)
	{
		if (GetItemData(nIndex) == nValue)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	SetCurSel(nIndexFind);
}

BOOL CSerialBaseComboBox::GetSelect(CString &strText)
{
	long nSel = GetCurSel();

	if (nSel != CB_ERR)
	{
		GetLBText(nSel, strText);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CSerialBaseComboBox::GetSelect(long &nData)
{
	long nSel = GetCurSel();

	if (nSel != CB_ERR)
	{
		nData = GetItemData(nSel);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

