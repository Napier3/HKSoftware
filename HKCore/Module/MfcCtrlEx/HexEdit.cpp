// HexEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "HexEdit.h"


// CHexEdit

IMPLEMENT_DYNAMIC(CHexEdit, CMFCMaskedEdit)

CHexEdit::CHexEdit()
{

}

CHexEdit::~CHexEdit()
{
}


BEGIN_MESSAGE_MAP(CHexEdit, CMFCMaskedEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CHexEdit 消息处理程序

void CHexEdit::Init(long nLength)
{
	CString strMask=_T("  "), strInputTemplate = _T("0x"), strText2=_T("0x");
	long nIndex = 0;

	for (nIndex=0; nIndex<nLength; nIndex++)
	{
		strMask = strMask + _T("AA");//字母加数字
		strInputTemplate = strInputTemplate + _T("__");
		strText2 = strText2 + _T("00");
	}

	EnableMask((LPCTSTR)strMask, // The mask string
		(LPCTSTR)strInputTemplate, // Literal, "_" char = character entry
		_T('0')); // Backspace replace char
	SetValidChars(_T("1234567890ABCDEFabcdef")); // Valid string characters


	SetWindowText(strText2);
	m_nLength *= 2;
}

void CHexEdit::InitEx(long nLength)
{
	CString strMask=_T("  "), strInputTemplate = _T("0x"), strText2=_T("0x");
	long nIndex = 0;

	for (nIndex=0; nIndex<nLength; nIndex++)
	{
		strMask = strMask + _T("A");
		strInputTemplate = strInputTemplate + _T("_");
		strText2 = strText2 + _T("0");
	}

	EnableMask((LPCTSTR)strMask, // The mask string
		(LPCTSTR)strInputTemplate, // Literal, "_" char = character entry
		_T('0')); // Backspace replace char
	SetValidChars(_T("1234567890ABCDEFabcdef")); // Valid string characters


	SetWindowText(strText2);
	m_nLength = nLength;
}

// 
// void CHexEdit::SetValue(DWORD dwValue)
// {
// 	CString strText;
// 	CString strFormat(_T("0x%0%dX"), m_nLength);
// 	strText.Format(strFormat, dwValue);
// 	SetWindowText(strText);
// }

void CHexEdit::SetValue(DWORD dwValue)
{
	char pszHex[20];
	ValueToHex(dwValue, pszHex);
	SetWindowText(CString(pszHex));
}

void CHexEdit::GetValue(DWORD &dwValue)
{
	BYTE byteValue[10];
	char *pszHex = NULL;
	CString strHex;
	GetWindowText(strHex);
	long nLen = strHex.GetLength();

	if (nLen % 2 == 1)
	{
		strHex = _T("0") + strHex;
	}

	CString_to_char(strHex, &pszHex);
	
	nLen = HexToValue(pszHex, byteValue);

	if (nLen > 4)
	{
		nLen = 4;
	}

	long nIndex = 0;
	dwValue = 0;

	for (nIndex=0; nIndex<nLen; nIndex++)
	{
		dwValue = dwValue * 256 + byteValue[nIndex];
	}

	delete pszHex;
}

void CHexEdit::SetValue(WORD wValue)
{
	char pszHex[20];
	ValueToHex(wValue, pszHex);
	SetWindowText(CString(pszHex));
}

void CHexEdit::GetValue(WORD &wValue)
{
	DWORD dwValue = 0;
	GetValue(dwValue);
	wValue = (WORD)dwValue;
}

void CHexEdit::SetValue(BYTE byteValue)
{
	char pszHex[20];
	ValueToHex(byteValue, pszHex);
	SetWindowText(CString(pszHex));
}

void CHexEdit::GetValue(BYTE &byteValue)
{
	DWORD dwValue = 0;
	GetValue(dwValue);
	byteValue = (BYTE)dwValue;
}

void CHexEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if ('a' <= nChar && nChar <= 'z')
	{
		nChar += 'A' - 'a';
	}

	CMFCMaskedEdit::OnChar(nChar, nRepCnt, nFlags);
}
