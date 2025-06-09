#include "StdAfx.h"

#include "Ep101Frame_68_Asdu0D.h"
#include "EpProtocol101.h"

//////////////////////////////////////////////////////////////////////////
//
CEp101Frame_68_Asdu0D::CEp101Frame_68_Asdu0D(CEpFrameBase *pHead, CEpFrameBase *pTail)
		:CEp101Frame_68_AsduBase(pHead, pTail)
{
	m_strID = _T("101_ASDU_0D");
	m_strName = m_strID;
}

CEp101Frame_68_Asdu0D::~CEp101Frame_68_Asdu0D()
{

}

/*
void CProtocol::ASDU_D(const BYTE *byASDU, const int iLen, CString &strMsg, CMFCPropertyGridProperty *pGroup)
{
	CMFCPropertyGridProperty *pProp = NULL;
	int iSQ, iNum, iCOT;
	int iCursor = 0;
	Deal_ASDU_Head(byASDU, iCursor, iSQ, iNum, iCOT, strMsg, pGroup);	

	int iODDR, iOV, iBL, iSB, iNT, iIV;
	float fValue;
	CString strTime = "";
	if (iSQ == 0)
	{
		// 不连续测量值	
		for (int iIndex=0; iIndex<iNum; iIndex++)
		{
			GetODDRValue(byASDU, iCursor, iIndex, iODDR, pGroup);
			iODDR -= m_addr.m_iYc_Addr;

			fValue = GetIEEE754Value(byASDU, iCursor, pGroup);
			GetQDSValue(byASDU[iCursor++], iOV, iBL, iSB, iNT, iIV, pProp);

			if (iODDR >= 0 && iODDR < m_iYcCount && m_pYcData[iODDR].bUsed)
			{
				//TRACE("不连续 fValue(%d) = %.3f;  \n",  nIndex, fValue);
				InsertYcDataToDB(m_nCaptureID, m_pYcData[iODDR].nDataID, fValue, strTime, FRAME_No_Timer);
			}
		}
	}
	else
	{
		// 连续测量值
		GetODDRValue(byASDU, iCursor, -1, iODDR, pGroup);
		iODDR -= m_addr.m_iYc_Addr;
		for (int iIndex=0; iIndex<iNum; iIndex++)
		{
			fValue = GetIEEE754Value(byASDU, iCursor, pGroup);
			GetQDSValue(byASDU[iCursor++], iOV, iBL, iSB, iNT, iIV, pProp);
			if (iIndex+iODDR >= 0 && iIndex+iODDR < m_iYcCount && m_pYcData[iIndex+iODDR].bUsed)
			{
				//TRACE("连 续 fValue(%d) = %.3f;  \n",  iIndex+nIndex, fValue);
				InsertYcDataToDB(m_nCaptureID, m_pYcData[iIndex+iODDR].nDataID, fValue, strTime, FRAME_No_Timer);
			}
		}
	}	
}


*/

DWORD CEp101Frame_68_Asdu0D::ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
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
				AddNewAddrByteBlockToDataSet(g_strEpAsduInfOAddr, pBufferPos->nODDRLen, nPos);
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

			nPos++;

			CEpY4Data *pData = pDatas->AddY4Data(nODDR, fValue);

// 			if (iODDR >= 0 && iODDR < m_iYcCount && m_pYcData[iODDR].bUsed)
// 			{
// 				//TRACE("不连续 fValue(%d) = %.3f;  \n",  nIndex, fValue);
// 				InsertYcDataToDB(m_nCaptureID, m_pYcData[iODDR].nDataID, fValue, strTime, FRAME_No_Timer);
// 			}
		}
	}
	else
	{
		nLen = Ep101_GetODDRValue(pBuffer, pBufferPos->nODDRLen, nODDR);

		if (pBufferPos->bAddDetail)
		{
			AddNewByteBlock(pDetailList, g_strEpAsduInfOAddr, pBufferPos->nODDRLen, nPos);
		}

		//nODDR -= pProtocol->m_nYcAddr;
		nPos  += pBufferPos->nODDRLen;

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

			nPos++;

			CEpY4Data *pData = pDatas->AddY4Data(nODDR+nIndex, fValue);
// 			pYcData[nIndex].nDataAddr = nODDR;
// 			pYcData[nIndex].fValue = fValue;
		}
	}

	return Ep_OffsetEpBufferCurr(pBufferPos, nPos);
}

BOOL CEp101Frame_68_Asdu0D::Match(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);

	if (*pRcvBuffer == 0x0D)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

DWORD CEp101Frame_68_Asdu0D::Produce(PEPBUFFERPOS pBufferPos)
{
	return 0;
}
