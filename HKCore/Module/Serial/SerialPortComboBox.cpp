// SerialPortComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialPortComboBox.h"
#include "SerialGlobalDefine.h"

// CSerialPortComboBox

IMPLEMENT_DYNAMIC(CSerialPortComboBox, CComboBox)

CSerialPortComboBox::CSerialPortComboBox()
{
   m_nPortCount = 16;
}

CSerialPortComboBox::~CSerialPortComboBox()
{
}


BEGIN_MESSAGE_MAP(CSerialPortComboBox, CSerialBaseComboBox)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CSerialPortComboBox 消息处理程序



int CSerialPortComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSerialBaseComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CSerialPortComboBox::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL b = CSerialBaseComboBox::Create(dwStyle, rect, pParentWnd, nID);

	return b;
}

void CSerialPortComboBox::PreSubclassWindow()
{
	InitPortByteString();

	CSerialBaseComboBox::PreSubclassWindow();
}

void CSerialPortComboBox::InitPortByteString()
{
	long nIndex = 0;
	CString strText;
	long nItem = 0;
	
	for (nIndex=1; nIndex <= m_nPortCount; nIndex++)
	{
		strText.Format(_T("COM %d"), nIndex);
		nItem = AddString(strText);
		SetItemData(nItem, nIndex);
	}
}

void CSerialPortComboBox::SetPortCount(long nCount)
{
	m_nPortCount = nCount;
	ResetContent();
	
	InitPortByteString();
}

