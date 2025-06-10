#include "stdafx.h"
#include "StringCmpBlocks.h"

CStringCmpBlocks::CStringCmpBlocks()
{
	m_pStringRef = NULL;
}

CStringCmpBlocks::~CStringCmpBlocks()
{
}

void CStringCmpBlocks::Draw(CDC *pDC, CRect rc, UINT nFormat, COLORREF crMatch/*=RGB(0,0,0)*/ , COLORREF crUnmatch/*=RGB(255,0,255)*/)
{
	POS pos = GetHeadPosition();
	CStringCmpBlock *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		rc.left += p->Draw(pDC, rc, nFormat, crMatch, crUnmatch);
	}
}

CStringCmpBlock* CStringCmpBlocks::AddNew(int nBegin, int nLen, BYTE bCmpState, CString *pStr)
{
    CStringCmpBlock *pStringCmpBlock = new CStringCmpBlock();
	pStringCmpBlock->m_nBeginPos  = nBegin;
	pStringCmpBlock->m_nLength    =nLen;
	pStringCmpBlock->m_nCmpState  =bCmpState;
	pStringCmpBlock->m_pStringRef =pStr;
	AddTail(pStringCmpBlock);

	return pStringCmpBlock;
}

long CStringCmpBlocks::GetAllBlocksByState(CStringCmpBlocks &listBlks, UINT nCmpState)
{
	if (nCmpState == CMPSTATE_UNMATCH)
	{
		nCmpState = 0xff;
	}

	POS pos = GetHeadPosition();
	CStringCmpBlock *pBlk = NULL;

	while (pos != NULL)
	{
		pBlk = GetNext(pos);

		if (pBlk->m_nCmpState == nCmpState)
		{
			listBlks.AddTail(pBlk);
		}
	}

	return listBlks.GetCount();
}

void CStringCmpBlocks::Log(UINT nCmpState)
{
	if (nCmpState == CMPSTATE_UNMATCH)
	{
		nCmpState = 0xff;
	}

	POS pos = GetHeadPosition();
	CStringCmpBlock *pBlk = NULL;
	CString strLog;

	while (pos != NULL)
	{
		pBlk = GetNext(pos);

		if (nCmpState == pBlk->m_nCmpState)
		{
            strLog += pBlk->GetString();
		}
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, strLog);
}
