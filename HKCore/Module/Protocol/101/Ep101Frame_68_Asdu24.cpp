#include "StdAfx.h"

#include "Ep101Frame_68_Asdu24.h"
#include "EpProtocol101.h"

//////////////////////////////////////////////////////////////////////////
//
CEp101Frame_68_Asdu24::CEp101Frame_68_Asdu24(CEpFrameBase *pHead, CEpFrameBase *pTail)
		:CEp101Frame_68_AsduBase(pHead, pTail)
{
	m_strID = _T("101_ASDU_24");
	m_strName = m_strID;
}

CEp101Frame_68_Asdu24::~CEp101Frame_68_Asdu24()
{

}

DWORD CEp101Frame_68_Asdu24::ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	CEp101Frame_68_AsduBase::ParseOwn(pBufferPos, pDetailList);

	BYTE *pBuffer = Ep_GetEpBufferCurr(pBufferPos);
	long nPos = 0;
	long nIndex = 0;
	long nODDR = 0;
	long nSPI=0, nBL=0, nSB=0, nNT=0, nIV=0;
	BYTE byteValue = 0;
	long nYcIndex = 0;
	long nSQ = m_nSQ;
	long nCount = m_nCount;
	float fValue = 0;
	long nLen = 0;




	CEpDeviceDatas *pDatas = pBufferPos->pDatas;
	//pDatas->nDataCount = m_nCount;
	pDatas->m_nDeviceDataType = EP_DEVICE_DATA_YC;

	if (nSQ == 0)
	{// 不连续测量值
		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			if (pBufferPos->bAddDetail)
			{
				InitBbDataSet(pDetailList);
			}

			nLen = Ep101_GetODDRValue(pBuffer+nPos, pBufferPos->nODDRLen, nODDR);

			if (pBufferPos->bAddDetail)
			{
				AddDataToDataSet(nODDR);
				AddNewByteBlockToDataSet(g_strEpAsduInfOAddr, pBufferPos->nODDRLen, nPos);
			}

			//nODDR -= pProtocol->m_nYcAddr;
			nPos  += pBufferPos->nODDRLen;
			nLen = Ep101_GetIEEE754Value(pBuffer+nPos, fValue);
			//nYcIndex = nIndex + nODDR;

			if (pBufferPos->bAddDetail)
			{
				AddNewFloatByteBlockToDataSet(g_strEpFloat, nLen, nPos, fValue, pBufferPos->bAddDetail);
			}


			nPos += nLen;

			if (pBufferPos->bAddDetail)
			{
				AddNewQDSByteBlockToDataSet(g_strEpQDS, 1, nPos, *(pBuffer+nPos), pBufferPos->bAddDetail);
			}

			nPos ++;
			CEpY4Data *pData = pDatas->AddY4Data(nODDR, fValue);
// 
// 			pYcData[nIndex].nDataAddr = nODDR;
// 			pYcData[nIndex].fValue = fValue;

			//tm;
			Ep101_GetCP56Time2aValue(pBuffer+nPos, pData->m_tm);

			if (pBufferPos->bAddDetail)
			{
				AddNewTimeByteBlockToDataSet(g_strEpAsduTime, 7, nPos, pData->m_tm);
			}

			nPos += 7;
		}
	}
	else
	{//
		nLen = Ep101_GetODDRValue(pBuffer, pBufferPos->nODDRLen, nODDR);

		if (pBufferPos->bAddDetail)
		{
			AddNewByteBlock(pDetailList, g_strEpAsduInfOAddr, pBufferPos->nODDRLen, nPos);
		}

		//nODDR -= pProtocol->m_nYcAddr;
		nPos  += pBufferPos->nODDRLen;

		// 不连续测量值
		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			if (pBufferPos->bAddDetail)
			{
				InitBbDataSet(pDetailList);
			}

			nLen = Ep101_GetIEEE754Value(pBuffer+nPos, fValue);
			//nYcIndex = nIndex + nODDR;

			if (pBufferPos->bAddDetail)
			{
				AddDataToDataSet(nODDR+nIndex);
				AddNewFloatByteBlockToDataSet(g_strEpFloat, nLen, nPos, fValue, pBufferPos->bAddDetail);
			}

			nPos += nLen;

			if (pBufferPos->bAddDetail)
			{
				AddNewQDSByteBlockToDataSet(g_strEpQDS, 1, nPos, *(pBuffer+nPos), pBufferPos->bAddDetail);
			}

			CEpY4Data *pData = pDatas->AddY4Data(nODDR+nIndex, byteValue);
// 			pYcData[nIndex].nDataAddr = nODDR+nIndex;
// 			pYcData[nIndex].fValue = fValue;

			// tm;
			Ep101_GetCP56Time2aValue(pBuffer+nPos, pData->m_tm);

			if (pBufferPos->bAddDetail)
			{
				AddNewTimeByteBlockToDataSet(g_strEpAsduTime, 7, nPos, pData->m_tm);
			}

			nPos += 7;
		}	
	}

	return Ep_OffsetEpBufferCurr(pBufferPos, nPos);
}

BOOL CEp101Frame_68_Asdu24::Match(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);

	if (*pRcvBuffer == 0x24)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

DWORD CEp101Frame_68_Asdu24::Produce(PEPBUFFERPOS pBufferPos)
{
	return 0;
}
