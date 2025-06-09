// SerialBaudRateComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialBaudRateComboBox.h"


// CSerialBaudRateComboBox

IMPLEMENT_DYNAMIC(CSerialBaudRateComboBox, CComboBox)

CSerialBaudRateComboBox::CSerialBaudRateComboBox()
{

}

CSerialBaudRateComboBox::~CSerialBaudRateComboBox()
{
}


BEGIN_MESSAGE_MAP(CSerialBaudRateComboBox, CSerialBaseComboBox)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CSerialBaudRateComboBox 消息处理程序



int CSerialBaudRateComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSerialBaseComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CSerialBaudRateComboBox::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL b = CSerialBaseComboBox::Create(dwStyle, rect, pParentWnd, nID);

	return b;
}

void CSerialBaudRateComboBox::PreSubclassWindow()
{
	InitBaudRateString();

	CSerialBaseComboBox::PreSubclassWindow();
}

void CSerialBaudRateComboBox::InitBaudRateString()
{
	long nIndex = AddString(_T("1200"));
	SetItemData(nIndex, 1200);

	nIndex = AddString(_T("2400"));
	SetItemData(nIndex, 2400);

	nIndex = AddString(_T("4800"));
	SetItemData(nIndex, 4800);

	nIndex = AddString(_T("9600"));
	SetItemData(nIndex, 9600);

	nIndex = AddString(_T("19200"));
	SetItemData(nIndex, 19200);

	SetSelect(9600);
}
