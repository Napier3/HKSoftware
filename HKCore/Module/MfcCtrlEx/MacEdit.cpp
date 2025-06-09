// MacEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "MacEdit.h"


// CMacEdit

IMPLEMENT_DYNAMIC(CMacEdit, CMFCMaskedEdit)

CMacEdit::CMacEdit()
{

}

CMacEdit::~CMacEdit()
{
}


BEGIN_MESSAGE_MAP(CMacEdit, CMFCMaskedEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CMacEdit 消息处理程序

void CMacEdit::Init()
{
	CString strMask=_T("  "), strInputTemplate = _T("0x"), strText2=_T("0x");
	long nIndex = 0;

	strMask = _T("AA AA AA AA AA AA");
	strInputTemplate = _T("__-__-__-__-__-__");
	strText2 = _T("FF-FF-FF-FF-FF-FF");

	EnableMask((LPCTSTR)strMask, // The mask string
		(LPCTSTR)strInputTemplate, // Literal, "_" char = character entry
		_T('0')); // Backspace replace char
	SetValidChars(_T("1234567890ABCDEFabcdef")); // Valid string characters
	SetWindowText(strText2);
}

void CMacEdit::GetMacAddr(CString &strMac)
{
	CString strText;
	GetWindowText(strText);
	char pszMac[40];
	char pszMacDest[40];
	CString_to_char(strText, pszMac);
	long nLen = strlen(pszMac);
	long nIndex = 0;
	long nIndexDest = 0;

	for (nIndex=0; nIndex<nLen; nIndex+=2)
	{
		if (pszMac[nIndex+2] == '-')
		{
			pszMacDest[nIndexDest++] = pszMac[nIndex];
			pszMacDest[nIndexDest++] = pszMac[nIndex+1];
			pszMacDest[nIndexDest++] = pszMac[nIndex+2];
		}
		else
		{
			pszMacDest[nIndexDest++] = pszMac[nIndex];
			pszMacDest[nIndexDest++] = pszMac[nIndex+1];
			pszMacDest[nIndexDest++] = '-';
		}
	}

	if (nIndexDest > 0)
	{
		nIndexDest--;
	}

	pszMacDest[nIndexDest] = '\0';
	strMac = pszMacDest;
}

void CMacEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if ('a' <= nChar && nChar <= 'z')
	{
		nChar += 'A' - 'a';
	}

	CMFCMaskedEdit::OnChar(nChar, nRepCnt, nFlags);
}

CString CMacEdit::GetMacText()
{
	CString strText;
	GetWindowText(strText);
	CString strMac;
	long nLen = strText.GetLength();
	long nIndex = 0;

	for (nIndex=0; nIndex<nLen-2; nIndex+=2)
	{
		strMac += strText.Mid(nIndex, 2);
		strMac += _T("-");
	}

	strMac += strText.Mid(nIndex, 2);

	return strMac;
}

