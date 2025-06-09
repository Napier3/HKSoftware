#include "StdAfx.h"

#include "Ep101Frame_68_Asdu67.h"
#include "EpProtocol101.h"

//////////////////////////////////////////////////////////////////////////
//
CEp101Frame_68_Asdu67::CEp101Frame_68_Asdu67(CEpFrameBase *pHead, CEpFrameBase *pTail)
		:CEp101Frame_68_AsduBase(pHead, pTail)
{
	m_strID = _T("101_ASDU_67");
	m_strName = m_strID;
}

CEp101Frame_68_Asdu67::~CEp101Frame_68_Asdu67()
{

}

static long g_nAsdu67Counter = 0;

DWORD CEp101Frame_68_Asdu67::ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
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
	pDatas->m_nDeviceDataType = EP_DEVICE_DATA_TSYN;

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

		CEpY4Data *pData = pDatas->AddY4Data(nODDR, 0);

// 		pYxData[nIndex].nDataAddr = nODDR;
// 		pYxData[nIndex].fValue = *(pBuffer+nPos);

// 		if (pBufferPos->bAddDetail)
// 		{
// 			AddNewQOIByteBlockToDataSet(g_strEpQOI, 1, nPos, *(pBuffer+nPos), pBufferPos->bAddDetail);
// 		}
// 
// 		nPos  += 1;

//		nPos += 2;

		// tm;
		Ep101_GetCP56Time2aValue(pBuffer+nPos, pData->m_tm);

/*
		//if (g_nAsdu67Counter == 0 || g_nAsdu67Counter >= 1000)
		{
			EPTIME64 tmSrc = pData->m_tm;
// 			EPTIME64EX tmDest;
// 			Ep_TIME64_to_TIME64EX(tmSrc, tmDest);
 			SYSTEMTIME sysTime;
			sysTime.wYear = *((WORD*)(&pData->m_tm.tm[6]));
			sysTime.wMonth = pData->m_tm.tm[5];
			sysTime.wDay = pData->m_tm.tm[4];
			sysTime.wHour = pData->m_tm.tm[3];
			sysTime.wMinute = pData->m_tm.tm[2];

			long nValue = pData->m_tm.tm[1];
			nValue = nValue << 8;
			nValue += pData->m_tm.tm[0];
			sysTime.wSecond = nValue / 1000;
			sysTime.wMilliseconds = nValue % 1000;
// 			Ep_TIME64EX_to_SYSTEMTIME(tmDest, sysTime);
 			SetLocalTime(&sysTime);
			g_nAsdu67Counter = 0;
// 			CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("系统对时%d-%d-%d %d:%d:%d........")
// 				, sysTime.wYear, sysTime.wMonth, sysTime.wDay
// 				, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
		}
		g_nAsdu67Counter++;
*/

		if (pBufferPos->bAddDetail)
		{
			AddNewTimeByteBlockToDataSet(g_strEpAsduTime, 7, nPos, pData->m_tm);
		}

		nPos += 7;
	}

	return Ep_OffsetEpBufferCurr(pBufferPos, nPos);
}

BOOL CEp101Frame_68_Asdu67::Match(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);

	if (*pRcvBuffer == 0x67)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

DWORD CEp101Frame_68_Asdu67::Produce(PEPBUFFERPOS pBufferPos)
{
	return 0;
}
