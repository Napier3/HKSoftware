// SerialCheckComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialCheckComboBox.h"
#include "SerialGlobalDefine.h"

// CSerialCheckComboBox

IMPLEMENT_DYNAMIC(CSerialCheckComboBox, CComboBox)

CSerialCheckComboBox::CSerialCheckComboBox()
{

}

CSerialCheckComboBox::~CSerialCheckComboBox()
{
}


BEGIN_MESSAGE_MAP(CSerialCheckComboBox, CSerialBaseComboBox)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CSerialCheckComboBox 消息处理程序



int CSerialCheckComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSerialBaseComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CSerialCheckComboBox::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL b = CSerialBaseComboBox::Create(dwStyle, rect, pParentWnd, nID);

	return b;
}

void CSerialCheckComboBox::PreSubclassWindow()
{
	InitCheckByteString();

	CSerialBaseComboBox::PreSubclassWindow();
}

void CSerialCheckComboBox::InitCheckByteString()
{
	long nIndex = AddString(_T("无校验"));
	SetItemData(nIndex, 0);

	nIndex = AddString(_T("奇校验"));
	SetItemData(nIndex, 1);

	nIndex = AddString(_T("偶校验"));
	SetItemData(nIndex, 2);

	SetSelect(0);
}

void CSerialCheckComboBox::SetSelectByIDString(const CString &strCheckByteID)
{
	long nCheckByte = 0;
	
	if (strCheckByteID == SERIAL_CHECKBYTE_STRING_NONE)
	{
		nCheckByte = SERIAL_CHECKBYTE_NONE;
	}
	else if (strCheckByteID == SERIAL_CHECKBYTE_STRING_ODD)
	{
		nCheckByte = SERIAL_CHECKBYTE_ODD;
	}
	else if (strCheckByteID == SERIAL_CHECKBYTE_STRING_EVEN)
	{
		nCheckByte = SERIAL_CHECKBYTE_EVEN;
	}
	
	SetSelect(nCheckByte);
}

