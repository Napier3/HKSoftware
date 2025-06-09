#include "StdAfx.h"

#include "Ep101Frame_68_Asdu30.h"
#include "EpProtocol101.h"

//////////////////////////////////////////////////////////////////////////
//
CEp101Frame_68_Asdu30::CEp101Frame_68_Asdu30(CEpFrameBase *pHead, CEpFrameBase *pTail)
		:CEp101Frame_68_AsduBase(pHead, pTail)
{
	m_strID = _T("101_ASDU_30");
	m_strName = m_strID;
}

CEp101Frame_68_Asdu30::~CEp101Frame_68_Asdu30()
{

}

DWORD CEp101Frame_68_Asdu30::ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	CEp101Frame_68_AsduBase::ParseOwn(pBufferPos, pDetailList);

	BYTE *pBuffer = Ep_GetEpBufferCurr(pBufferPos);
	long nPos = 0;
	long nIndex = 0;
	long nODDR = 0;
	long nSPI=0, nBL=0, nSB=0, nNT=0, nIV=0;
	BYTE byteValue = 0;
	long nYtIndex = 0;
	long nSQ = m_nSQ;
	long nCount = m_nCount;
	long nLen = 0;
	float fValue = 0;



	CEpDeviceDatas *pDatas = pBufferPos->pDatas;
	//pDatas->nDataCount = m_nCount;
	pDatas->m_nDeviceDataType = EP_DEVICE_DATA_YT;

	if (nSQ == 0)
	{// 不连续遥调值
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

			//nODDR -= pProtocol->m_nYtAddr;
			nPos  += pBufferPos->nODDRLen;
			//pData = (CEpDeviceData101Yt *)pYtDataNode->GetData(nODDR);
			
// 			if (pData != NULL && pData->m_nUsed)
// 			{
// 				//TRACE("不连续 fValue(%d) = %.3f;  \n",  nIndex, fValue);
// 				nLen = Ep101_GetNormalizationValue(pBuffer, fValue, pData->m_fMin, pData->m_fMax);
// 				//InsertYtDataToDB(m_nCaptureID, m_pYtData[iODDR].nDataID, fValue, strTime);
// 			}
// 			else
// 			{
// 				nLen = Ep101_GetNormalizationValue(pBuffer, fValue, -32768, 32768);
// 			}

// 			pYtData[nIndex].nDataAddr = nODDR;
			nLen = Ep101_GetNormalizationValue(pBuffer+nPos, fValue, -32768, 32768);
			CEpY4Data *pData = pDatas->AddY4Data(nODDR, fValue);


			if (pBufferPos->bAddDetail)
			{
				AddNewFloatByteBlockToDataSet(g_strEpFloat, nLen, nPos, fValue, pBufferPos->bAddDetail);
			}

			nPos += nLen;


			if (pBufferPos->bAddDetail)
			{
				AddNewQOSByteBlockToDataSet(g_strEpQOS, 1, nPos, *(pBuffer+nPos), pBufferPos->bAddDetail);
			}

			nPos += 1;
		}
	}
	else
	{// 连续单点信息
		Ep101_GetODDRValue(pBuffer, pBufferPos->nODDRLen, nODDR);

		if (pBufferPos->bAddDetail)
		{
			AddNewByteBlock(pDetailList, g_strEpAsduInfOAddr, pBufferPos->nODDRLen, nPos);
		}

		//nODDR -= pProtocol->m_nYtAddr;
		nPos  += pBufferPos->nODDRLen;

		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			if (pBufferPos->bAddDetail)
			{
				InitBbDataSet(pDetailList);
			}

			nYtIndex = nIndex + nODDR;

// 			pYtData[nIndex].nDataAddr = nODDR;
			nLen = Ep101_GetNormalizationValue(pBuffer+nPos, fValue, -32768, 32768);
			CEpY4Data *pData = pDatas->AddY4Data(nYtIndex, byteValue);

			if (pBufferPos->bAddDetail)
			{
				AddDataToDataSet(nYtIndex);
				AddNewFloatByteBlockToDataSet(g_strEpFloat, nLen, nPos, fValue, pBufferPos->bAddDetail);
			}

			nPos += nLen;


			if (pBufferPos->bAddDetail)
			{
				AddNewQOSByteBlockToDataSet(g_strEpQOS, 1, nPos, *(pBuffer+nPos), pBufferPos->bAddDetail);
			}

			nPos += 1;
		}
	}

	return Ep_OffsetEpBufferCurr(pBufferPos, nPos);
}

BOOL CEp101Frame_68_Asdu30::Match(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);

	if (*pRcvBuffer == 0x30)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

DWORD CEp101Frame_68_Asdu30::Produce(PEPBUFFERPOS pBufferPos)
{
	return 0;
}
