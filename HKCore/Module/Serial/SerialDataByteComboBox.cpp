// SerialDataByteComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialDataByteComboBox.h"
#include "SerialGlobalDefine.h"

// CSerialDataByteComboBox

IMPLEMENT_DYNAMIC(CSerialDataByteComboBox, CComboBox)

CSerialDataByteComboBox::CSerialDataByteComboBox()
{

}

CSerialDataByteComboBox::~CSerialDataByteComboBox()
{
}


BEGIN_MESSAGE_MAP(CSerialDataByteComboBox, CSerialBaseComboBox)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CSerialDataByteComboBox 消息处理程序



int CSerialDataByteComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSerialBaseComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CSerialDataByteComboBox::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL b = CSerialBaseComboBox::Create(dwStyle, rect, pParentWnd, nID);

	return b;
}

void CSerialDataByteComboBox::PreSubclassWindow()
{
	InitDataByteByteString();

	CSerialBaseComboBox::PreSubclassWindow();
}

void CSerialDataByteComboBox::InitDataByteByteString()
{
	long nIndex = AddString(_T("5"));
	SetItemData(nIndex, 5);

	nIndex = AddString(_T("6"));
	SetItemData(nIndex, 6);

	nIndex = AddString(_T("7"));
	SetItemData(nIndex, 7);

	nIndex = AddString(_T("8"));
	SetItemData(nIndex, 8);

	SetSelect(7);
}
