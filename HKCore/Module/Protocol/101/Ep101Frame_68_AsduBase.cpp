#include "StdAfx.h"

#include "Ep101Frame_68_AsduBase.h"

//////////////////////////////////////////////////////////////////////////
//
CEp101Frame_68_AsduBase::CEp101Frame_68_AsduBase(CEpFrameBase *pHead, CEpFrameBase *pTail)
		:CEpFrameAsdu(pHead, pTail)
{
	m_byteType = 0;
	m_byteVSQ = 0;

	m_byteCOT = 0; 
	m_byteAddr = 0;

	m_nSQ = 0; 
	m_nCount = 0; 

}

CEp101Frame_68_AsduBase::~CEp101Frame_68_AsduBase()
{

}

DWORD CEp101Frame_68_AsduBase::ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	BYTE *pBuffer = Ep_GetEpBufferCurr(pBufferPos);
	long nPos = Ep_GetEpFramePos(pBufferPos);
	long nPosOld = nPos;

	//Type
	if (pBufferPos->bAddDetail)
	{
		AddNewByteBlock(pDetailList, g_strEpAsduType, 1, nPos);
	}

	nPos++;

	//VSQ
	AddVsqByteBlock(pDetailList, g_strEpAsduVSQ,  1, nPos, pBuffer[1], pBufferPos->bAddDetail);
	nPos++;


	if (pBufferPos->nProtocol == EPPROTOCOL_101)
	{
		//COT
		AddCotByteBlock(pDetailList, g_strEpAsduCOT,  1, nPos, pBuffer[2], pBufferPos->bAddDetail);
		nPos++;
		
		//ADDR
		if (pBufferPos->bAddDetail)
		{
			AddNewByteBlock(pDetailList, g_strEpAsduAddr, 1, nPos);
		}

		nPos++;
	}
	else
	{
		//COT
		AddCotByteBlock(pDetailList, g_strEpAsduCOT,  2, nPos, pBuffer[2], pBufferPos->bAddDetail);
		nPos += 2;

		//ADDR
		if (pBufferPos->bAddDetail)
		{
			AddNewByteBlock(pDetailList, g_strEpAsduAddr, 2, nPos);
		}

		nPos += 2;
	}

	return Ep_OffsetEpBufferCurr(pBufferPos, nPos - nPosOld);
}

BOOL CEp101Frame_68_AsduBase::Match(PEPBUFFERPOS pBufferPos)
{
	ASSERT (FALSE);
	return FALSE;
}

DWORD CEp101Frame_68_AsduBase::Produce(PEPBUFFERPOS pBufferPos)
{
	return 0;
}

void CEp101Frame_68_AsduBase::AddAsduByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteValue, BOOL bAddDetail)
{
	m_byteType = byteValue;

	if (bAddDetail)
	{
		CEpByteBlock *pByteBlock = AddNewByteBlock(pDetailList, strID, nLen, nIndex);
		pByteBlock->AddBbInfor(g_strEpAsduType, m_nSQ, 7);
	}
}

void CEp101Frame_68_AsduBase::AddVsqByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteVsq, BOOL bAddDetail)
{
	m_nSQ = (byteVsq & 0x80) >> 7;
	m_nCount = byteVsq & 0x7F;

	if (bAddDetail)
	{
		CEpByteBlock *pByteBlock = AddNewByteBlock(pDetailList, strID, nLen, nIndex);
		pByteBlock->AddBbInfor(g_strEpSQ, m_nSQ, 7);
		pByteBlock->AddBbInfor(g_strEpCount, m_nCount, 6, 0);
	}
}

void CEp101Frame_68_AsduBase::AddCotByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteCot, BOOL bAddDetail)
{
	m_byteCOT = byteCot;

	if (bAddDetail)
	{
		CEpByteBlock *pByteBlock = AddNewByteBlock(pDetailList, strID, nLen, nIndex);
		pByteBlock->AddBbInfor(g_strEpAsduCOT, m_byteCOT, 0);
	}
}

void CEp101Frame_68_AsduBase::AddSIQByteBlockToDataSet(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteSIQ, BOOL bAddDetail)
{
	if (!bAddDetail)
	{
		return;
	}

	ASSERT(m_pBbDataSet != NULL);
	ASSERT (m_pBbDataSet->m_pCurrData != NULL);

	CEpByteBlock *pNew = new CEpByteBlockSIQ(byteSIQ);
	pNew->m_strID = strID;
	pNew->m_strName = strID;
	pNew->m_nIndex = nIndex;
	pNew->m_nLength = nLen;
	m_pBbDataSet->m_pCurrData->AddNewChild(pNew);
// 	return pNew;
}

CEpByteBlockData_101_Yx* CEp101Frame_68_AsduBase::AddNewYxByteBlockToDataSet(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex)
{
	CEpByteBlockData_101_Yx *pNew = new CEpByteBlockData_101_Yx(0);
	pNew->m_strID = strID;
	pNew->m_strName = strID;
	pNew->m_nIndex = nIndex;
	pNew->m_nLength = nLen;
	pDetailList->AddNewChild(pNew);
	return pNew;
}