// XLanguageTextWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "XLanguageWndInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CXLanguageWndInterface::CXLanguageWndInterface()
{
	m_pWndRef = NULL;
}

CXLanguageWndInterface::~CXLanguageWndInterface()
{
	
}

void CXLanguageWndInterface::CalXLangWndAdj(CRect &rcOrigin, long &nCalWidth) 
{
	xlang_CalXLangWndAdj(m_pWndRef, rcOrigin, nCalWidth);
}

BOOL CXLanguageWndInterface::InitByLanguageID(const CString &strLanguageID, CWnd *pWnd)
{
	m_pWndRef = pWnd;
	m_strLanguageID = strLanguageID;
	CString strText;

	if (!xlang_GetLgugStr(m_strLanguageID, strText))
	{
		if (xlang_IsInLanguageEditState())
		{
			pWnd->SetWindowText(strText);
			return TRUE;
		}
	}
	else
	{
		pWnd->SetWindowText(strText);
		return TRUE;
	}

	return FALSE;
}

void CXLanguageWndInterface::MoveWindow(const CRect &rcWnd)
{
	ASSERT (m_pWndRef != NULL);
	m_pWndRef->MoveWindow(rcWnd, TRUE);
	m_pWndRef->Invalidate(FALSE);
}

void xlang_CalXLangWndAdj(CWnd *pWnd, CRect &rcOrigin, long &nCalWidth)
{
	pWnd->GetWindowRect(rcOrigin);
	//	CWnd *pParent = pWnd->GetParent();

	CFont *pFont = pWnd->GetFont();
	LOGFONT lf;
	CFont *pOldFont = NULL;
	CDC *pDC = pWnd->GetDC();

	if (pFont != NULL)
	{
		pFont->GetLogFont(&lf);
		pOldFont = pDC->SelectObject(pFont);
	}
	
	CString strText;
	pWnd->GetWindowText(strText);
	CRect rc(0, 0, 0, 0);
	pDC->DrawText(strText, &rc, DT_CALCRECT | DT_LEFT);
	nCalWidth = rc.Width();
	nCalWidth += 2;

	if (pFont != NULL)
	{
		pDC->SelectObject(pOldFont);
	}

	pWnd->ReleaseDC(pDC);
}

void xlang_MoveWindowTo(CWnd *pParent, CWnd *pWndFrom, CWnd *pWndTo)
{
	CRect rc;
	pWndTo->GetWindowRect(&rc);
	pParent->ScreenToClient(&rc);
	pWndFrom->MoveWindow(rc);
}


//////////////////////////////////////////////////////////////////////////
//
CXLanguageWndAlign::CXLanguageWndAlign()
{
	m_nWndCount = 0;
	m_nWndArrayLen = 10;
	m_pdwWndArray = new ULONG[m_nWndArrayLen];
	m_pParentWnd = NULL;
}

CXLanguageWndAlign::CXLanguageWndAlign(CWnd *pParentWnd)
{
	m_nWndCount = 0;
	m_nWndArrayLen = 10;
	m_pdwWndArray = new ULONG[m_nWndArrayLen];
	m_pParentWnd = pParentWnd;
}

CXLanguageWndAlign::~CXLanguageWndAlign()
{
	delete []m_pdwWndArray;
}


void CXLanguageWndAlign::AddWnd(CWnd *pWnd)
{
	if (m_nWndCount == m_nWndArrayLen)
	{
		ResizeWndArray(10);
	}

	m_pdwWndArray[m_nWndCount] = (DWORD)pWnd;
	m_nWndCount++;
}

void CXLanguageWndAlign::AlignLeft()
{
	if (m_nWndCount <= 1)
	{
		return;
	}

	CRect *pRcBuf = new CRect[m_nWndCount];
	long nIndex = 0;
	long nLeft = 0;
	
	for (nIndex=0; nIndex<m_nWndCount; nIndex++)
	{
		((CWnd*)m_pdwWndArray[nIndex])->GetWindowRect(&pRcBuf[nIndex]);
		m_pParentWnd->ScreenToClient(&pRcBuf[nIndex]);
		nLeft = min(nLeft, pRcBuf[nIndex].left);
	}

	for (nIndex=0; nIndex<m_nWndCount; nIndex++)
	{
		pRcBuf[nIndex].right += nLeft - pRcBuf[nIndex].left;
		pRcBuf[nIndex].left = nLeft;
		((CWnd*)m_pdwWndArray[nIndex])->MoveWindow(pRcBuf[nIndex]);
	}

	delete []pRcBuf;
}

void CXLanguageWndAlign::AlignRight()
{
	if (m_nWndCount <= 1)
	{
		return;
	}

	CRect *pRcBuf = new CRect[m_nWndCount];
	long nIndex = 0;
	long nRight = 0;

	for (nIndex=0; nIndex<m_nWndCount; nIndex++)
	{
		((CWnd*)m_pdwWndArray[nIndex])->GetWindowRect(&pRcBuf[nIndex]);
		m_pParentWnd->ScreenToClient(&pRcBuf[nIndex]);
		nRight = max(nRight, pRcBuf[nIndex].right);
	}

	for (nIndex=0; nIndex<m_nWndCount; nIndex++)
	{
		pRcBuf[nIndex].left += nRight - pRcBuf[nIndex].right;
		pRcBuf[nIndex].right = nRight;
		((CWnd*)m_pdwWndArray[nIndex])->MoveWindow(pRcBuf[nIndex]);
	}

	delete []pRcBuf;
}

void CXLanguageWndAlign::AlignTop()
{

}

void CXLanguageWndAlign::AlignBottom()
{

}

void CXLanguageWndAlign::Reset()
{
	m_nWndCount = 0;
}

void CXLanguageWndAlign::MoveToLeft(long nGap)
{
	if (m_nWndCount == 0)
	{
		return;
	}

	CRect *pRcBuf = new CRect[m_nWndCount];
	long nIndex = 0;
	long nLeft = nGap;


	for (nIndex=0; nIndex<m_nWndCount; nIndex++)
	{
		((CWnd*)m_pdwWndArray[nIndex])->GetWindowRect(&pRcBuf[nIndex]);
		m_pParentWnd->ScreenToClient(&pRcBuf[nIndex]);
	}

	for (nIndex=0; nIndex<m_nWndCount; nIndex++)
	{
		pRcBuf[nIndex].right += nLeft - pRcBuf[nIndex].left;
		pRcBuf[nIndex].left = nLeft;
		((CWnd*)m_pdwWndArray[nIndex])->MoveWindow(pRcBuf[nIndex]);
	}

	delete []pRcBuf;
}

void CXLanguageWndAlign::MoveToRight(long nGap)
{
	if (m_nWndCount == 0)
	{
		return;
	}

	CRect *pRcBuf = new CRect[m_nWndCount];
	long nIndex = 0;
	CRect rcClient;
	m_pParentWnd->GetClientRect(&rcClient);
	long nRight = rcClient.right - nGap;

	for (nIndex=0; nIndex<m_nWndCount; nIndex++)
	{
		((CWnd*)m_pdwWndArray[nIndex])->GetWindowRect(&pRcBuf[nIndex]);
		m_pParentWnd->ScreenToClient(&pRcBuf[nIndex]);
	}

	for (nIndex=0; nIndex<m_nWndCount; nIndex++)
	{
		pRcBuf[nIndex].left += nRight - pRcBuf[nIndex].right;
		pRcBuf[nIndex].right = nRight;
		((CWnd*)m_pdwWndArray[nIndex])->MoveWindow(pRcBuf[nIndex]);
	}

	delete []pRcBuf;
}

void CXLanguageWndAlign::MoveToTop(long nGap)
{
	
}

void CXLanguageWndAlign::MoveToBottom(long nGap)
{

}

void CXLanguageWndAlign::ResizeWndArray(long nAdd)
{
	long nLen = m_nWndArrayLen + nAdd;
	DWORD *pdwBuffer = new DWORD[nLen];
	ZeroMemory(pdwBuffer, nLen * sizeof(DWORD));
	DWORD *pTemp = m_pdwWndArray;
	memcpy(pdwBuffer, m_pdwWndArray, m_nWndArrayLen * sizeof(DWORD));
	m_nWndArrayLen = nLen;
	m_pdwWndArray = pdwBuffer;
	delete []pTemp;
}

