#include "StdAfx.h"
#include "PpPackageDetail.h"
#include "RBbData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpPackageDetail::CPpPackageDetail(CExBaseObject *pChannel)
{
	m_pChannel = pChannel;
#ifdef UNICODE
	m_pVariables = new CBbVariables(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariablesKey);
#else
	m_pVariables = new CBbVariables(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariablesKey));
#endif
	m_pDataInterface = NULL;
	m_nBeginTime = 0;
	m_nTimeout = 30000;
	m_bUsed = FALSE;
	m_bRecord = FALSE;
	m_bDelete = FALSE;
	m_pPkgBufPos = NULL;
}

CPpPackageDetail::~CPpPackageDetail(void)
{
	DeleteAll();

	if (m_pVariables != NULL)
	{
		delete m_pVariables;
		m_pVariables = NULL;
	}

	if (m_pDataInterface != NULL)
	{
		delete m_pDataInterface;
		m_pDataInterface = NULL;
	}
}

BOOL CPpPackageDetail::CanDelete()
{
	if (m_bUsed)
	{
		{
			return TRUE;
		}
	}
	else if ( IsTimeout())
	{
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

void CPpPackageDetail::GetVariablesString(CString &strVariables)
{
	if (m_pVariables != NULL)
	{
		m_pVariables->GetVariablesString(strVariables);
	}

	if (m_pDataInterface != NULL)
	{
		m_pDataInterface->GetVariablesString(strVariables);
	}
}

void CPpPackageDetail::AddDvmValue(const CString &strName, const CString &strID, const CString &strValue)
{
	CDvmValue *pNew = new CDvmValue();
	pNew->m_strID = strID;
#ifdef _DVM_VALUE_USE_CHAR_
#ifdef UNICODE
	wcscpy(pNew->m_strValue, strValue);
#else
	wcscpy(pNew->m_strValue, strValue.AllocSysString());
#endif
#else
	pNew->m_strValue = strValue;
#endif
	pNew->m_strName = strName;
	m_oDvmValues.AddTail(pNew);
}

void CPpPackageDetail::GetPpDataBufferPos(CExBaseObject *pPpData, long &nBeginPos, long &nEndPos)
{
	UINT nClassID = pPpData->GetClassID();
	nBeginPos = 0;
	nEndPos = -1;

	switch (nClassID)
	{
	case PPCLASSID_BYTEBLOCK:
	case PPCLASSID_RBYTEBLOCK:
	case PPCLASSID_WBYTEBLOCK:
		GetByteBlockBufferPos((CByteBlock*)pPpData, nBeginPos, nEndPos);
		break;
// 	case PPCLASSID_BYTEBLOCK:
// 		GetByteBlockBufferPos((CByteBlock*)pPpData, nBeginPos, nEndPos);
// 		break;
	case PPCLASSID_BBDATA:
	case PPCLASSID_RBBDATA:
	case PPCLASSID_WBBDATA:
		{
			CByteBlock *pFirst = NULL;
			CByteBlock *pLast = NULL;
			((CBbData*)pPpData)->GetFirstAndLastByteBlock(&pFirst, &pLast);
			GetByteBlockBufferPos(pFirst, pLast, nBeginPos, nEndPos);
		}
		break;
	case PPCLASSID_DATABYTEBLOCK:
	case PPCLASSID_RDATABYTEBLOCK:
	case PPCLASSID_WDATABYTEBLOCK:
		GetByteBlockBufferPos((CByteBlock*)pPpData, nBeginPos, nEndPos);
		break;
	default:
		break;
	}
}

void CPpPackageDetail::GetByteBlockBufferPos(CByteBlock *pByteBlock, long &nBeginPos, long &nEndPos)
{
	GetByteBlockBufferPos((CExBaseList*)this, pByteBlock, nBeginPos, nEndPos);
}

void CPpPackageDetail::GetByteBlockBufferPos(CByteBlock *pFirst, CByteBlock *pLast, long &nBeginPos, long &nEndPos)
{
	long nTemp = 0;
	GetByteBlockBufferPos(pFirst, nBeginPos, nTemp);
	nTemp = 0;
	GetByteBlockBufferPos(pLast, nTemp, nEndPos);
}

BOOL CPpPackageDetail::GetByteBlockBufferPos(CExBaseList *pList, CByteBlock *pByteBlock, long &nBeginPos, long &nEndPos)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (PpIsByteBlock(nClassID))
		{
			if (p == pByteBlock)
			{
				nEndPos = nBeginPos + pByteBlock->GetByteBlockLength2() - 1;
				bTrue = TRUE;
				break;
			}
			else
			{
				nBeginPos += ((CByteBlock*)p)->GetByteBlockLength2();
			}
		}
		else if (PpIsByteBlocks(nClassID))
		{
			bTrue = GetByteBlockBufferPos((CExBaseList*)p, pByteBlock, nBeginPos, nEndPos);
		}

		if (bTrue)
		{
			break;
		}
	}

	return bTrue;
}

void CPpPackageDetail::GetAllByteBlocks(CExBaseList *pDestList)
{
	GetAllByteBlocks(this, pDestList);
}

long CPpPackageDetail::GetTotalLen()
{
	CExBaseList list;
	GetAllByteBlocks(&list);

	POS pos = list.GetHeadPosition();
	CByteBlock *pByteBlock = NULL;
	long nLength = 0;

	while (pos != NULL)
	{
		pByteBlock = (CByteBlock *)list.GetNext(pos);
		nLength += pByteBlock->GetByteBlockLength2();
	}

	list.RemoveAll();

	return nLength;
}

long CPpPackageDetail::GetPkgCurrBufVal(long nOffset)
{
	if (m_pPkgBufPos == NULL)
	{
		return 0;
	}

	int iCurrentPos = GetTotalLen();
	int iPos = iCurrentPos + nOffset;
	long nVal = 0;

	if (iCurrentPos >= m_pPkgBufPos->nBuffer1BeginPos && iCurrentPos <= m_pPkgBufPos->nBuffer1EndPos)
	{// 游标位于第一段缓冲区
		if (iPos <= m_pPkgBufPos->nBuffer1EndPos)
		{// 第一段缓冲区足够使用
			nVal = m_pPkgBufPos->pBuffer[iPos];
		}
		else
		{// 第一段缓冲区不够使用
			int iTemp = iPos - m_pPkgBufPos->nBuffer1EndPos;

			if (iTemp <= m_pPkgBufPos->nBuffer2EndPos)
			{// 如果长度超过第二段缓冲区数据，则认为该字节块数据对应2进制流数据不够
				nVal = m_pPkgBufPos->pBuffer[iTemp];
			}
		}
	}
	else if (iCurrentPos >= m_pPkgBufPos->nBuffer2BeginPos && iCurrentPos <= m_pPkgBufPos->nBuffer2EndPos)
	{// 游标位于第二段缓冲区
		if (iPos <= m_pPkgBufPos->nBuffer2EndPos)
		{// 第二段缓冲区足够使用
			nVal = m_pPkgBufPos->pBuffer[iPos];
		}
	}

	return nVal;
}

void CPpPackageDetail::GetAllByteBlocks(CExBaseList *pSrcList, CExBaseList *pDestList)
{
	POS pos = pSrcList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pSrcList->GetNext(pos);
		nClassID = p->GetClassID(); 
		
		if ( PpIsByteBlock(nClassID) )
		{
			pDestList->AddTail(p);
		}
		else if (nClassID == PPCLASSID_WBBDATA || nClassID == PPCLASSID_RBBDATA)
		{
			GetAllByteBlocks((CExBaseList*)p, pDestList);
		}
	}
}

