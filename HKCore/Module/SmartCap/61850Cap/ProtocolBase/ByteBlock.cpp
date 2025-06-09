#include "StdAfx.h"
#include "ByteBlock.h"


CByteBlock::CByteBlock(void)
{
	m_bUseData = FALSE;
	m_nData = 0;
}


CByteBlock::~CByteBlock(void)
{
	
}

void CByteBlock::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	BYTE *pByte = (BYTE*)dwParam;
	CString strText = m_strID;
	//CString strText = _GetFrameAnalyseString(m_strID);
	CString strTemp;
	strText += _T(":   ");

	for (long nIndex=0; nIndex<m_nLength; nIndex++)
	{
		strText.AppendFormat(_T("%02X "), *(pByte+m_nIndex+nIndex));
	}
	
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strText, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

//////////////////////////////////////////////////////////////////////////
//CByteBlocks
CByteBlocks::CByteBlocks()
{
	
}

CByteBlocks::~CByteBlocks()
{

}

void CByteBlocks::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{

}


CByteBlock* CByteBlocks::AddNewByteBlock(const CString &strID, long nLen, long nIndex)
{
	CByteBlock *pNew = new CByteBlock();
	pNew->m_strID = strID;
	pNew->m_strName = strID;
	pNew->m_nIndex = nIndex;
	pNew->m_nLength = nLen;
	AddNewChild(pNew);
	m_pCurrByteBlock = pNew;
	return pNew;
}

CByteBlock* CByteBlocks::AddByteBlockByValue(const CString &strID, BYTE val, long nIndex)
{
	CByteBlock *pNew = AddNewByteBlock(strID, 1, nIndex);
	pNew->AddBbInfor(strID, val, -1, -1);
	return pNew;
}

CByteBlock* CByteBlocks::AddByteBlockByValue(const CString &strID, short val, long nIndex)
{
	CByteBlock *pNew = AddNewByteBlock(strID, 2, nIndex);
	pNew->AddBbInfor(strID, val);
	return pNew;
}

CByteBlock* CByteBlocks::AddByteBlockByValue(const CString &strID, WORD val, long nIndex)
{
	CByteBlock *pNew = AddNewByteBlock(strID, 2, nIndex);
	pNew->AddBbInfor(strID, val);
	return pNew;
}

CByteBlock* CByteBlocks::AddByteBlockByValue(const CString &strID, DWORD val, long nIndex)
{
	CByteBlock *pNew = AddNewByteBlock(strID, 4, nIndex);
	pNew->AddBbInfor(strID, val);
	return pNew;
}

CByteBlock* CByteBlocks::AddByteBlockByValue(const CString &strID, long val, long nIndex)
{
	CByteBlock *pNew = AddNewByteBlock(strID, 4, nIndex);
	pNew->AddBbInfor(strID, val);
	return pNew;
}

CByteBlock* CByteBlocks::AddByteBlockByValue(const CString &strID, long val, long nLen, long nIndex)
{
	CByteBlock *pNew = AddNewByteBlock(strID, nLen, nIndex);
	pNew->AddBbInfor(strID, val);
	return pNew;
}

CByteBlock* CByteBlocks::AddByteBlockByValue(const CString &strID, float val, long nIndex)
{
	CByteBlock *pNew = AddNewByteBlock(strID, 4, nIndex);
	pNew->AddBbInfor(strID, val);
	return pNew;
}

CByteBlock* CByteBlocks::AddByteBlockByValue(const CString &strID, double val, long nIndex)
{
	CByteBlock *pNew = AddNewByteBlock(strID, 8, nIndex);
	pNew->AddBbInfor(strID, val);
	return pNew;
}

CByteBlock* CByteBlocks::AddByteBlockByValue(const CString &strID, const CString &val, long nLen, long nIndex)
{
	CByteBlock *pNew = AddNewByteBlock(strID, nLen, nIndex);
	pNew->AddBbInfor(strID, val);
	return pNew;
}

CByteBlock* CByteBlocks::AddByteBlockByValue_MAC(const CString &strID, BYTE *val, long nIndex)
{
	CByteBlock *pNew = AddNewByteBlock(strID, 6, nIndex);
	CString strMac;
	strMac.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"), val[0], val[1], val[2], val[3], val[4], val[5]);
	pNew->AddBbInfor(strID, strMac);
	return pNew;
}

//////////////////////////////////////////////////////////////////////////
//添加集合块

void CByteBlocks::AppendToDetail(CExBaseList *pList)
{
	pList->Append(this);
}

CByteBlocks* CByteBlocks::AddNewByteBlocks(const CString &strID)
{
	m_pCurrByteBlock = NULL;
	m_pCurrByteBlocks = new CByteBlocks();
	m_pCurrByteBlocks->m_strID = strID;
	m_pCurrByteBlocks->m_strName = strID;
	AddNewChild(m_pCurrByteBlocks);
	return m_pCurrByteBlocks;
}

CByteBlock* CByteBlocks::AddNewByteBlockEx(const CString &strID, long nLen, long nIndex)
{
	ASSERT(m_pCurrByteBlocks != NULL);
	m_pCurrByteBlock = m_pCurrByteBlocks->AddNewByteBlock(strID, nLen, nIndex);
	return m_pCurrByteBlock;
}

CByteBlock* CByteBlocks::AddByteBlockByValueEx(const CString &strID, BYTE val, long nIndex)
{
	ASSERT(m_pCurrByteBlocks != NULL);
	m_pCurrByteBlock = m_pCurrByteBlocks->AddByteBlockByValue(strID, val, nIndex);
	return m_pCurrByteBlock;
}

CByteBlock* CByteBlocks::AddByteBlockByValueEx(const CString &strID, short val, long nIndex)
{
	ASSERT(m_pCurrByteBlocks != NULL);
	m_pCurrByteBlock = m_pCurrByteBlocks->AddByteBlockByValue(strID, val, nIndex);
	return m_pCurrByteBlock;
}

CByteBlock* CByteBlocks::AddByteBlockByValueEx(const CString &strID, WORD val, long nIndex)
{
	ASSERT(m_pCurrByteBlocks != NULL);
	m_pCurrByteBlock = m_pCurrByteBlocks->AddByteBlockByValue(strID, val, nIndex);
	return m_pCurrByteBlock;
}

CByteBlock* CByteBlocks::AddByteBlockByValueEx(const CString &strID, long val, long nIndex)
{
	ASSERT(m_pCurrByteBlocks != NULL);
	m_pCurrByteBlock = m_pCurrByteBlocks->AddByteBlockByValue(strID, val, nIndex);
	return m_pCurrByteBlock;
}

CByteBlock* CByteBlocks::AddByteBlockByValueEx(const CString &strID, long val, long nLen, long nIndex)
{
	ASSERT(m_pCurrByteBlocks != NULL);
	m_pCurrByteBlock = m_pCurrByteBlocks->AddByteBlockByValue(strID, val, nLen, nIndex);
	return m_pCurrByteBlock;
}

CByteBlock* CByteBlocks::AddByteBlockByValueEx(const CString &strID, DWORD val, long nIndex)
{
	ASSERT(m_pCurrByteBlocks != NULL);
	m_pCurrByteBlock = m_pCurrByteBlocks->AddByteBlockByValue(strID, val, nIndex);
	return m_pCurrByteBlock;
}

CByteBlock* CByteBlocks::AddByteBlockByValueEx(const CString &strID, float val, long nIndex)
{
	ASSERT(m_pCurrByteBlocks != NULL);
	m_pCurrByteBlock = m_pCurrByteBlocks->AddByteBlockByValue(strID, val, nIndex);
	return m_pCurrByteBlock;
}

CByteBlock* CByteBlocks::AddByteBlockByValueEx(const CString &strID, double val, long nIndex)
{
	ASSERT(m_pCurrByteBlocks != NULL);
	m_pCurrByteBlock = m_pCurrByteBlocks->AddByteBlockByValue(strID, val, nIndex);
	return m_pCurrByteBlock;
}

CByteBlock* CByteBlocks::AddByteBlockByValueEx(const CString &strID, const CString &val, long nLen, long nIndex)
{
	ASSERT(m_pCurrByteBlocks != NULL);
	m_pCurrByteBlock = m_pCurrByteBlocks->AddByteBlockByValue(strID, val, nLen, nIndex);
	return m_pCurrByteBlock;
}

CByteBlock* CByteBlocks::AddByteBlockByValueEx_MAC(const CString &strID, BYTE *val, long nIndex)
{
	ASSERT(m_pCurrByteBlocks != NULL);
	m_pCurrByteBlock = m_pCurrByteBlocks->AddByteBlockByValue_MAC(strID, val, nIndex);
	return m_pCurrByteBlock;
}

//////////////////////////////////////////////////////////////////////////
//为当前块添加信息
CBbInffor* CByteBlocks::AddBbInfor(const CString &strID, BYTE val, long nDxBegin, long nDxEnd)
{
	ASSERT (m_pCurrByteBlock != NULL);
	return m_pCurrByteBlock->AddBbInfor(strID, val, nDxBegin, nDxEnd);
}

CBbInffor* CByteBlocks::AddBbInfor(const CString &strID, short val, long nDxBegin, long nDxEnd)
{
	ASSERT (m_pCurrByteBlock != NULL);
	return m_pCurrByteBlock->AddBbInfor(strID, val, nDxBegin, nDxEnd);
}

CBbInffor* CByteBlocks::AddBbInfor(const CString &strID, long val, long nDxBegin, long nDxEnd)
{
	ASSERT (m_pCurrByteBlock != NULL);
	return m_pCurrByteBlock->AddBbInfor(strID, val, nDxBegin, nDxEnd);
}

CBbInffor* CByteBlocks::AddBbInfor(const CString &strID, float val, long nDxBegin, long nDxEnd)
{
	ASSERT (m_pCurrByteBlock != NULL);
	return m_pCurrByteBlock->AddBbInfor(strID, val, nDxBegin, nDxEnd);
}

CBbInffor* CByteBlocks::AddBbInfor(const CString &strID, double val, long nDxBegin, long nDxEnd)
{
	ASSERT (m_pCurrByteBlock != NULL);
	return m_pCurrByteBlock->AddBbInfor(strID, val, nDxBegin, nDxEnd);
}

CBbInffor* CByteBlocks::AddBbInfor(const CString &strID, const CString &val)
{
// 	CBbInffor *pInfor = new CBbInffor(strID, val);
	return m_pCurrByteBlock->AddBbInfor(strID, val);
//	return pInfor;
}
