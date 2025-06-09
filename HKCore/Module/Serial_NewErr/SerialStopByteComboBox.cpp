// SerialStopByteComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialStopByteComboBox.h"
#include "SerialGlobalDefine.h"
#include "..\..\Module\API\MathApi.h"

// CSerialStopByteComboBox

IMPLEMENT_DYNAMIC(CSerialStopByteComboBox, CComboBox)

CSerialStopByteComboBox::CSerialStopByteComboBox()
{

}

CSerialStopByteComboBox::~CSerialStopByteComboBox()
{
}


BEGIN_MESSAGE_MAP(CSerialStopByteComboBox, CSerialBaseComboBox)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CSerialStopByteComboBox 消息处理程序



int CSerialStopByteComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSerialBaseComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CSerialStopByteComboBox::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL b = CSerialBaseComboBox::Create(dwStyle, rect, pParentWnd, nID);

	return b;
}

void CSerialStopByteComboBox::PreSubclassWindow()
{
	InitStopByteByteString();

	CSerialBaseComboBox::PreSubclassWindow();
}

void CSerialStopByteComboBox::InitStopByteByteString()
{
	long nIndex = AddString(SERIAL_STOPBYTE_STRING_1);
	SetItemData(nIndex, 0);

	nIndex = AddString(SERIAL_STOPBYTE_STRING_15);
	SetItemData(nIndex, 1);

	nIndex = AddString(SERIAL_STOPBYTE_STRING_2);
	SetItemData(nIndex, 2);

}

void CSerialStopByteComboBox::SetSelect(float fStopBit)
{
	long nData = -1;

	if( math_IsEqual(fStopBit, 1.0f) )
	{
		nData = 0;
	}
	else if(math_IsEqual(fStopBit, 1.5f) )
	{
		nData = 1;
	}
	else if(math_IsEqual(fStopBit, 2.0f) )
	{
		nData = 2;
	}

	CSerialBaseComboBox::SetSelect(nData);
}

BOOL CSerialStopByteComboBox::GetSelect(float &fData)
{
	long nData = 0;

	if (!CSerialBaseComboBox::GetSelect(nData))
	{
		return FALSE;
	}

	BOOL bTrue = TRUE;

	switch (nData)
	{
	case 0:
		fData = 1.0f;
		break;
	case 1:
		fData = 1.5f;
		break;
	case 2:
		fData = 2.0f;
		break;
	default:
		bTrue = FALSE;
		break;
	}

	return bTrue;
}

