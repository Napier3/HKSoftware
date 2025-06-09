#include "StdAfx.h"
#include "EpByteBlock.h"


CEpByteBlock::CEpByteBlock(void)
{
	m_bUseData = FALSE;
	m_nData = 0;
}


CEpByteBlock::~CEpByteBlock(void)
{
	
}

void CEpByteBlock::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	BYTE *pByte = (BYTE*)dwParam;
	CString strText = Ep_GetFrameAnalyseString(m_strID);
	CString strTemp;
	strText += _T(":   ");

	for (long nIndex=0; nIndex<m_nLength; nIndex++)
	{
		strText.AppendFormat(_T("%02X "), *(pByte+m_nIndex+nIndex));
	}
	
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strText, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

