#include "StdAfx.h"

#include "Ep101Frame_68_Asdu2E.h"
#include "EpProtocol101.h"

//////////////////////////////////////////////////////////////////////////
//
CEp101Frame_68_Asdu2E::CEp101Frame_68_Asdu2E(CEpFrameBase *pHead, CEpFrameBase *pTail)
		:CEp101Frame_68_AsduBase(pHead, pTail)
{
	m_strID = _T("101_ASDU_2E");
	m_strName = m_strID;
}

CEp101Frame_68_Asdu2E::~CEp101Frame_68_Asdu2E()
{

}

DWORD CEp101Frame_68_Asdu2E::ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	CEp101Frame_68_AsduBase::ParseOwn(pBufferPos, pDetailList);

	BYTE *pBuffer = Ep_GetEpBufferCurr(pBufferPos);
	long nPos = 0;
	long nIndex = 0;
	long nODDR = 0;
	long nSPI=0, nBL=0, nSB=0, nNT=0, nIV=0;
	BYTE byteValue = 0;
	long nYxIndex = 0;
	long nSQ = m_nSQ;
	long nCount = m_nCount;




	CEpDeviceDatas *pDatas = pBufferPos->pDatas;
	//pDatas->nDataCount = m_nCount;
	pDatas->m_nDeviceDataType = EP_DEVICE_DATA_YX;

	if (nSQ == 0)
	{// 不连续单点信息
		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			if (pBufferPos->bAddDetail)
			{
				InitBbDataSet(pDetailList);
			}

			Ep101_GetODDRValue(pBuffer+nPos, pBufferPos->nODDRLen, nODDR);

			if (pBufferPos->bAddDetail)
			{
				AddDataToDataSet(nODDR);
				AddNewByteBlockToDataSet(g_strEpAsduInfOAddr, pBufferPos->nODDRLen, nPos);
			}

			//nODDR -= pProtocol->m_nYxAddr;
			nPos  += pBufferPos->nODDRLen;
			
			byteValue = *(pBuffer+nPos);
			//nYxIndex = nIndex + nODDR;
			Ep101_GetSIQValue(byteValue, nSPI, nBL, nSB, nNT, nIV);

			if (pBufferPos->bAddDetail)
			{
				AddSIQByteBlockToDataSet(pDetailList, g_strEpAsduSIQ, 1, nPos, byteValue, pBufferPos->bAddDetail);
			}

			nPos++;	
			CEpY4Data *pData = pDatas->AddY4Data(nODDR, byteValue);

// 			p->nDataAddr = nODDR;
// 			p->fValue = byteValue;
			//
			// tm;
			Ep101_GetCP56Time2aValue(pBuffer+nPos, pData->m_tm);

			if (pBufferPos->bAddDetail)
			{
				AddNewTimeByteBlockToDataSet(g_strEpAsduTime, 7, nPos, pData->m_tm);
			}

			nPos += 7;
		}
	}
	else
	{// 连续单点信息
		Ep101_GetODDRValue(pBuffer, pBufferPos->nODDRLen, nODDR);

		if (pBufferPos->bAddDetail)
		{
			AddNewByteBlock(pDetailList, g_strEpAsduInfOAddr, pBufferPos->nODDRLen, nPos);
		}

		//nODDR -= pProtocol->m_nYxAddr;
		nPos  += pBufferPos->nODDRLen;

		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			if (pBufferPos->bAddDetail)
			{
				InitBbDataSet(pDetailList);
			}

			byteValue = *(pBuffer+nPos);
			//nYxIndex = nIndex + nODDR;
			Ep101_GetSIQValue(byteValue, nSPI, nBL, nSB, nNT, nIV);

			if (pBufferPos->bAddDetail)
			{
				AddDataToDataSet(nODDR+nIndex);
				AddSIQByteBlockToDataSet(pDetailList, g_strEpAsduSIQ, 1, nPos, byteValue, pBufferPos->bAddDetail);
			}

			nPos++;

			CEpY4Data *pData = pDatas->AddY4Data(nODDR, byteValue);
// 			p->fValue = byteValue;
// 			p->nDataAddr = nODDR;
		}
	}

	return Ep_OffsetEpBufferCurr(pBufferPos, nPos);
}

BOOL CEp101Frame_68_Asdu2E::Match(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);

	if (*pRcvBuffer == 0x2E)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

DWORD CEp101Frame_68_Asdu2E::Produce(PEPBUFFERPOS pBufferPos)
{
	return 0;
}
