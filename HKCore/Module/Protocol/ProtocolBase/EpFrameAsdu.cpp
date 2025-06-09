// EpFrameAsdu.cpp: implementation of the CEpFrameAsdu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpFrameAsdu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpFrameAsdu::CEpFrameAsdu(CEpFrameBase *pHead, CEpFrameBase *pTail)
{ 
	m_pHead = NULL;
	m_pTail = NULL;
	SetHeadAndTail(pHead, pTail);
	m_pBbDataSet = NULL;
}

CEpFrameAsdu::~CEpFrameAsdu()
{
	if (m_pHead != NULL)
	{
		delete m_pHead;
		m_pHead = NULL;
	}

	if (m_pTail != NULL)
	{
		delete m_pTail;
		m_pTail = NULL;
	}

	m_pBbDataSet = NULL;
}

void CEpFrameAsdu::SetHeadAndTail(CEpFrameBase *pHead, CEpFrameBase *pTail)
{
	m_pHead = pHead;
	m_pTail = pTail;

}


void CEpFrameAsdu::AppendToDetail(CExBaseList *pList)
{
	if (m_pHead != NULL)
	{
		pList->Append(m_pHead);
	}

	pList->Append(this);

	if (m_pTail != NULL)
	{
		pList->Append(m_pTail);
	}
}


DWORD CEpFrameAsdu::Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	Ep_BeginParseFrame(pBufferPos);

	long nLenHead = 0;
	long nLenOwn = 0;
	long nLenTail = 0;

	if (m_pHead != NULL)
	{
		nLenHead = m_pHead->Parse(pBufferPos, pDetailList);

		if (nLenHead < 0)
		{
			return -1;
		}
	}

	nLenOwn = ParseOwn(pBufferPos, pDetailList);

	if (m_pTail != NULL)
	{
		nLenTail = m_pTail->Parse(pBufferPos, pDetailList);
	}

	long nLen = 0;
	BYTE *pFrameBuffer = NULL;

	Ep_GetParseFrameBuffer(pBufferPos, &pFrameBuffer, &nLen);
	CopyBuffer(pFrameBuffer, nLen);

	if (m_pBbDataSet != NULL)
	{
		m_pBbDataSet->m_dwDataType = pBufferPos->pDatas->m_nDeviceDataType;
	}

	InitBbDataSet();

	return nLen;
}

CEpByteBlockDataSet* CEpFrameAsdu::InitBbDataSet(CExBaseList *pDetailList)
{
	if (m_pBbDataSet == NULL)
	{
		m_pBbDataSet = new CEpByteBlockDataSet();
		pDetailList->AddNewChild(m_pBbDataSet);
	}

	return m_pBbDataSet;
}

CEpByteBlockData* CEpFrameAsdu::AddDataToDataSet(long nIndex)
{
	ASSERT (m_pBbDataSet != NULL);
	CEpByteBlockData *pData = m_pBbDataSet->AddNewData(nIndex);

	return pData;
}

CEpByteBlock* CEpFrameAsdu::AddNewByteBlockToDataSet(const CString &strID, long nLen, long nIndex)
{
	ASSERT(m_pBbDataSet != NULL);
	ASSERT (m_pBbDataSet->m_pCurrData != NULL);

	CEpByteBlock *pNew = AddNewByteBlock(m_pBbDataSet->m_pCurrData, strID, nLen, nIndex);
//	pNew->AddBbInfor(g_strEpAsduTime, tm, -1, -1);
	return pNew;
// 
// 	CEpByteBlock *pNew = new CEpByteBlock();
// 	pNew->m_strID = strID;
// 	pNew->m_strName = strID;
// 	pNew->m_nIndex = nIndex;
// 	pNew->m_nLength = nLen;
// 	m_pBbDataSet->AddNewChild(pNew);
// 	return pNew;
}

CEpByteBlock* CEpFrameAsdu::AddNewAddrByteBlockToDataSet(const CString &strID, long nLen, long nIndex)
{
	ASSERT(m_pBbDataSet != NULL);
	ASSERT (m_pBbDataSet->m_pCurrData != NULL);

	CEpByteBlock *pNew = AddNewByteBlock(m_pBbDataSet->m_pCurrData, strID, nLen, nIndex);
	pNew->SetData(m_pBbDataSet->m_pCurrData->m_nItemIndex);
	return pNew;
// 
// 	CEpByteBlock *pNew = new CEpByteBlock();
// 	pNew->m_strID = strID;
// 	pNew->m_strName = strID;
// 	pNew->m_nIndex = nIndex;
// 	pNew->m_nLength = nLen;
// 	m_pBbDataSet->AddNewChild(pNew);
// 	return pNew;
}

CEpByteBlock* CEpFrameAsdu::AddNewTimeByteBlockToDataSet(const CString &strID, long nLen, long nIndex, EPTIME64 &tm)
{
	ASSERT(m_pBbDataSet != NULL);
	ASSERT(m_pBbDataSet->m_pCurrData != NULL);

	CEpByteBlock *pNew = AddNewByteBlock(m_pBbDataSet->m_pCurrData, strID, nLen, nIndex);
	pNew->AddBbInfor(g_strEpAsduTime, tm, -1, -1);
	return pNew;
}

CEpByteBlock* CEpFrameAsdu::AddNewQDSByteBlockToDataSet(const CString &strID, long nLen, long nIndex, BYTE byteValue, BOOL bAddDetail)
{
	ASSERT(m_pBbDataSet != NULL);
	ASSERT(m_pBbDataSet->m_pCurrData != NULL);

	CEpByteBlockQDS *pNew = new CEpByteBlockQDS(byteValue, bAddDetail);
	pNew->m_strID = strID;
	pNew->m_strName = strID;
	pNew->m_nIndex = nIndex;
	pNew->m_nLength = nLen;
	m_pBbDataSet->m_pCurrData->AddNewChild(pNew);

	return pNew;
}

CEpByteBlock* CEpFrameAsdu::AddNewFloatByteBlockToDataSet(const CString &strID, long nLen, long nIndex, float fValue, BOOL bAddDetail)
{
	ASSERT(m_pBbDataSet != NULL);
	ASSERT(m_pBbDataSet->m_pCurrData != NULL);

	CEpByteBlockFloat *pNew = new CEpByteBlockFloat(fValue, bAddDetail);
	pNew->m_strID = strID;
	pNew->m_strName = strID;
	pNew->m_nIndex = nIndex;
	pNew->m_nLength = nLen;
	m_pBbDataSet->m_pCurrData->AddNewChild(pNew);
	return pNew;
}

CEpByteBlock* CEpFrameAsdu::AddNewQOSByteBlockToDataSet(const CString &strID, long nLen, long nIndex, BYTE byteValue, BOOL bAddDetail)
{
	ASSERT(m_pBbDataSet != NULL);
	ASSERT(m_pBbDataSet->m_pCurrData != NULL);

	CEpByteBlockQOS *pNew = new CEpByteBlockQOS(byteValue, bAddDetail);
	pNew->m_strID = strID;
	pNew->m_strName = strID;
	pNew->m_nIndex = nIndex;
	pNew->m_nLength = nLen;
	m_pBbDataSet->m_pCurrData->AddNewChild(pNew);
	return pNew;
}

CEpByteBlock* CEpFrameAsdu::AddNewQOIByteBlockToDataSet(const CString &strID, long nLen, long nIndex, BYTE byteValue, BOOL bAddDetail)
{
	ASSERT(m_pBbDataSet != NULL);
	ASSERT(m_pBbDataSet->m_pCurrData != NULL);

	CEpByteBlockQOI *pNew = new CEpByteBlockQOI(byteValue, bAddDetail);
	pNew->m_strID = strID;
	pNew->m_strName = strID;
	pNew->m_nIndex = nIndex;
	pNew->m_nLength = nLen;
	m_pBbDataSet->m_pCurrData->AddNewChild(pNew);

	return pNew;
}
