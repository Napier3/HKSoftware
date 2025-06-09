#include "StdAfx.h"

#include "Ep101Frame_68_Asdu64.h"
#include "EpProtocol101.h"

//////////////////////////////////////////////////////////////////////////
//
CEp101Frame_68_Asdu64::CEp101Frame_68_Asdu64(CEpFrameBase *pHead, CEpFrameBase *pTail)
		:CEp101Frame_68_AsduBase(pHead, pTail)
{
	m_strID = _T("101_ASDU_64");
	m_strName = m_strID;
}

CEp101Frame_68_Asdu64::~CEp101Frame_68_Asdu64()
{

}

DWORD CEp101Frame_68_Asdu64::ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
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


	if (pBufferPos->bAddDetail)
	{
		InitBbDataSet(pDetailList);
	}


	CEpDeviceDatas *pDatas = pBufferPos->pDatas;
	//pDatas->nDataCount = m_nCount;
	pDatas->m_nDeviceDataType = EP_DEVICE_DATA_YX;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		Ep101_GetODDRValue(pBuffer+nPos, pBufferPos->nODDRLen, nODDR);

		if (pBufferPos->bAddDetail)
		{
			AddDataToDataSet(nODDR);
			AddNewByteBlockToDataSet(g_strEpAsduInfOAddr, pBufferPos->nODDRLen, nPos);
		}

		//nODDR -= pProtocol->m_nYxAddr;
		nPos  += pBufferPos->nODDRLen;

		byteValue = *(pBuffer+nPos);
		CEpY4Data *pData = pDatas->AddY4Data(nODDR, byteValue);

// 		pYxData[nIndex].nDataAddr = nODDR;
// 		pYxData[nIndex].fValue = *(pBuffer+nPos);

		if (pBufferPos->bAddDetail)
		{
			AddNewQOIByteBlockToDataSet(g_strEpQOI, 1, nPos, *(pBuffer+nPos), pBufferPos->bAddDetail);
		}

		nPos  += 1;
	}

	return Ep_OffsetEpBufferCurr(pBufferPos, nPos);
}

BOOL CEp101Frame_68_Asdu64::Match(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);

	if (*pRcvBuffer == 0x64)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

DWORD CEp101Frame_68_Asdu64::Produce(PEPBUFFERPOS pBufferPos)
{
	return 0;
}
