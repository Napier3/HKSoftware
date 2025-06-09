#include "StdAfx.h"

#include "92Frame.h"
#include "..\CapDevice\CapDevice92.h"

//////////////////////////////////////////////////////////////////////////
//
C92Frame::C92Frame()
{
	m_strID = _T("9-1");
	m_strName = m_strID;
}

C92Frame::~C92Frame()
{

}

long C92Frame::ParseOwn(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList)
{
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);

	BYTE byteValue = 0;
	WORD wValue = 0;
	DWORD dwValue;
	long nValue = 0;
	long nLen = 0;
	BYTE byteTag = 0;
	CString strValue;

	//APDULen
	long APDULen = 0;
	APDULen = ReadLength(_T("APDULen"), pBufferPos, pDetailList);

	//NO_ASDU
	long Len_noASDU = 0;
	long Num_ASDU = 0;
	ReadTagLenValue(_T("ASDU-NO"), byteTag, nLen, Num_ASDU, pBufferPos, pDetailList);
	if (byteTag != 0x80)
	{
		return -1;
	}

	if(Num_ASDU<=0)
	{
		return -1;
	}

	//Sequence of ASDU
	long Len_SequenceOfASDU = 0;
	long SequenceOfASDU = 0;
	ReadTagLength(_T("Sequence of ASDU"), byteTag, nLen, pBufferPos, pDetailList);
	if (byteTag != 0xA2)
	{
		return -1;
	}

	//Loop ASDU 
	CByteBlocks *pAsduBlocks = NULL;

	for(int i=0; i<Num_ASDU; i++)
	{
		CString strID;
		strID.Format(_T("ASDU-%d"), i+1);
		pAsduBlocks = pDetailList->AddNewByteBlocks(strID);

		//ASDU 标记
		ReadTagLength(_T("ASDU-Tag"), byteTag, nLen, pBufferPos, pAsduBlocks);

		//SVID
		ReadTagLenValue(_T("SVID"), byteTag, nLen, strValue, pBufferPos, pAsduBlocks);
		if (byteTag != 0x80)
		{
			return -1;
		}

		//需要添加的
		//0x81 security 0x86   smprate 0x84  refresh time    mym add 2020-7-13
		
		//Security
		ReadTagLenValue(_T("Security"), byteTag, nLen, nValue, pBufferPos, pAsduBlocks);
		if (byteTag != 0x81)
		{
			return -1;
		}
		
		//smpCnt
		ReadTagLenValue(_T("smpCnt"), byteTag, nLen, nValue, pBufferPos, pAsduBlocks);

		if (byteTag != 0x82)
		{
			return -1;
		}

		//confRev
		ReadTagLenValue(_T("confRev"), byteTag, nLen, nValue, pBufferPos, pAsduBlocks);

		if (byteTag != 0x83)
		{
			return -1;
		}

		// mym add 2020-7-13
		//refreshTime
		ReadTagLenValue(_T("refreshTime"), byteTag, nLen, nValue, pBufferPos, pAsduBlocks);
		if (byteTag != 0x84)
		{
			return -1;
		}

		//smpSynch
		ReadTagLenValue(_T("smpSynch"), byteTag, nLen, nValue, pBufferPos, pAsduBlocks);
		if (byteTag != 0x85)
		{
			return -1;
		}

		// mym add 2020-7-13
		//smpRate
		ReadTagLenValue(_T("smpRate"), byteTag, nLen, nValue, pBufferPos, pAsduBlocks);
		if (byteTag != 0x86)
		{
			return -1;
		}


		//通道数
		long nChCount = 0;
		ReadTagLength(_T("通道数"), byteTag, nChCount, pBufferPos, pAsduBlocks);
		if (byteTag != 0x87)
		{
			return -1;
		}

		nChCount /= 8;
		((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount = max(((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount, nChCount);


		CByteBlocks *pChBlocks = NULL;

		for (long nChIndex=1; nChIndex<=nChCount; nChIndex++)
		{
			CString strID;
			strID.Format(_T("通道%d"), nChIndex);
			pChBlocks = pAsduBlocks->AddNewByteBlocks(strID);

			dwValue = Ep_BufferReadDWord2(pBufferPos);
			pChBlocks->AddByteBlockByValue(_T("_Value"), dwValue, Ep_GetValuePos(pBufferPos));

			dwValue = Ep_BufferReadDWord2(pBufferPos);
			pChBlocks->AddByteBlockByValue(_T("_Quality"), dwValue, Ep_GetValuePos(pBufferPos));
		}
	}

	return 0;
}

long C92Frame::ParseOwn(PEPBUFFERPOS pBufferPos)
{
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);
	ASSERT (pBufferPos->pDatas != NULL);

	PEPCAPPARSEDATAS pDatas = pBufferPos->pDatas;                // add mym 2020-06-17
	PEPCAPPARSEDATA pData = pDatas->pDatas;

	BYTE byteValue = 0;
	WORD wValue = 0;
// 	DWORD dwValue;
	long nValue = 0;
	long nLen = 0;
	BYTE byteTag = 0;
	CString strValue;

	//APDULen
	pDatas->oData92.APDULen = ReadLength(pBufferPos);

	
	//NO_ASDU
	long Len_noASDU = 0;
	long Num_ASDU = 0;

	/*
	ReadTagLenValue(byteTag, nLen, Num_ASDU, pBufferPos);
	pDatas->oData92.Num_ASDU = Num_ASDU; // add mym 2020-06-17

	if (byteTag != 0x80)
	{
		return -1;
	}

	if(Num_ASDU<=0)
	{
		return -1;
	}


	//Sequence of ASDU
	long Len_SequenceOfASDU = 0;
	long SequenceOfASDU = 0;
	ReadTagLength(byteTag, nLen, pBufferPos);
	if (byteTag != 0xA2)
	{
		return -1;
	}

	pDatas->oData92.SequenceOfASDU = nLen; // add mym 2020-06-17
	*/
	// mym add 把上面的注销了，添加如下的代码，是为了存在0x81的情况，程序正常跑
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//security 是0x81 当是81的时候，后面的长度就是值；
	while (TRUE)
	{
		ReadTagLen(byteTag,  nLen,  pBufferPos);

		switch (byteTag)
		{
		case 0x80:	
			{
				ReadTagValue(byteTag, nLen,  Num_ASDU,  pBufferPos);
				pDatas->oData92.Num_ASDU = Num_ASDU; // add mym 2020-07-13
				break;
			}
		case 0x81:
			{
				//这时候 不用再调用读取VALUE函数，	ReadTagValue(nLen,  nValue,  pBufferPos);
				//直接获取nLen，就是获得的值；

				break;
			}
		}
		if (byteTag == 0xA2)
		{
			pDatas->oData92.SequenceOfASDU = nLen; // add mym 2020-07-13
			break;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	//Loop ASDU 
	for(int i  =  0; i  <  Num_ASDU;  i++)
	{
		//ASDU 标记
		ReadTagLength(byteTag, nLen, pBufferPos);

		//SVID
		//ReadTagLenValue(byteTag, nLen, strValue, pBufferPos);  
		ReadTagLenValue(byteTag, nLen, pDatas->oData92.Asdu[i].SVID, pBufferPos); //mayangming 2020-6-17
		if (byteTag != 0x80)
		{
			return -1;
		}

		if (Ep_NoInBuffer(pBufferPos))
		{
			return -1;
		}

		// 2020-7-11 add mym 
		//dataset
		//char dataset[64] = {0};//暂时定在这里也不用；
		//ReadTagLenValue(byteTag, nLen, dataset, pBufferPos);
		//if (byteTag != 0x81)
		//{
		//	return -1;
		//}

		long nChCount = 0;
		while (TRUE)
		{
			ReadTagLen(byteTag, nLen, pBufferPos);

			switch (byteTag)
			{
			case 0x81:	
				{
					ReadTagValue(byteTag, nLen, nValue, pBufferPos);
					break;
				}		
			case 0x82://smpcnt
				{
					ReadTagValue(byteTag, nLen, nValue, pBufferPos);
					pDatas->oData92.Asdu[i].smpCnt = nValue; //mayangming 2020-6-17
					break;
				}
			case 0x83:	//confRev
				{
					ReadTagValue(byteTag, nLen, nValue, pBufferPos);
					pDatas->oData92.Asdu[i].confRev = nValue; //mayangming 2020-6-17
					break;
				}
			case 0x84:  // refresh time  
				{
					ReadTagValue(byteTag, nLen, nValue, pBufferPos);
					break;
				}
			case 0x85:	//smpSynch
				{
					ReadTagValue(byteTag, nLen, nValue, pBufferPos);
					pDatas->oData92.Asdu[i].smpSynch = nValue;   //mayangming 2020-6-17
					break;
				}
			case 0x86://smpRate
				{
					ReadTagValue(byteTag, nLen, nValue, pBufferPos);
					break;
				}
			}

			if (byteTag == 0x87)
			{	
				nChCount  = nLen;
				pDatas->oData92.nChCount = nChCount;   //mayangming 2020-07-13
				break;
			}
		}

        /*
        //smpCnt
		ReadTagLenValue(byteTag, nLen, nValue, pBufferPos);
		pDatas->oData92.Asdu[i].smpCnt = nValue; //mayangming 2020-6-17
		if (byteTag != 0x82)
		{
			return -1;
		}

		//confRev
		ReadTagLenValue(byteTag, nLen, nValue, pBufferPos);	
		pDatas->oData92.Asdu[i].confRev = nValue; //mayangming 2020-6-17

		if (byteTag != 0x83)
		{
			return -1;
		}

		//smpSynch
		ReadTagLenValue(byteTag, nLen, nValue, pBufferPos);	
		pDatas->oData92.Asdu[i].smpSynch = nValue;   //mayangming 2020-6-17

		if (byteTag != 0x85)
		{
			return -1;
		}

		//通道数
	
		ReadTagLength(byteTag, nChCount, pBufferPos);	

		if (byteTag == 0x86)
		{//采样率，忽略
			pBufferPos->nIndex += nChCount;
			ReadTagLength(byteTag, nChCount, pBufferPos);	
		}
       */
		//pDatas->oData92.nChCount = nChCount;   //mayangming 2020-6-17

		// mym 注销；
		//if (byteTag != 0x87)
		//{
			//return -1;
		//}

		nChCount /= 8;
		((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount = max(((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount, nChCount);

		for (long nChIndex=1; nChIndex<=nChCount; nChIndex++)
		{
			if (Ep_NoInBuffer(pBufferPos))
			{
				return -1;
			}

			pData->dwValue  = Ep_BufferReadDWord2(pBufferPos);
			pData->dwValue2 = Ep_BufferReadDWord2(pBufferPos);
			pData++;
		}
	}

	pBufferPos->pDatas->dwDatas = pData -  pBufferPos->pDatas->pDatas;

	return 0;
}


DWORD C92Frame::ParseInfor(PEPBUFFERPOS pBufferPos, CExBaseObject *pDevice)
{
	CCapDevice92 *pDevice92 = (CCapDevice92 *)pDevice;
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);

	BYTE byteValue = 0;
	WORD wValue = 0;
// 	DWORD dwValue;
	long nValue = 0;
	long nLen = 0;
	BYTE byteTag = 0;
	CString strValue;

	//APDULen
	long APDULen = 0;
	APDULen = ReadLength(pBufferPos);

	//NO_ASDU
	long Len_noASDU = 0;
	ReadTagLenValue(byteTag, nLen, pDevice92->m_nAsduNum, pBufferPos);
	if (byteTag != 0x80)
	{
		return -1;
	}

	if(pDevice92->m_nAsduNum<=0)
	{
		return -1;
	}

	//Sequence of ASDU
	long Len_SequenceOfASDU = 0;
	long SequenceOfASDU = 0;
	ReadTagLength(byteTag, nLen, pBufferPos);
	if (byteTag != 0xA2)
	{
		return -1;
	}

	//Loop ASDU 

	for(int i=0; i<pDevice92->m_nAsduNum; i++)
	{
		//ASDU 标记
		ReadTagLength(byteTag, nLen, pBufferPos);

		//SVID
		ReadTagLenValue(byteTag, nLen, pDevice92->m_strSVID, pBufferPos);
		if (byteTag != 0x80)
		{
			return -1;
		}

		//smpCnt
		ReadTagLenValue(byteTag, nLen, nValue, pBufferPos);
		if (byteTag != 0x82)
		{
			return -1;
		}

		//confRev
		ReadTagLenValue(byteTag, nLen, pDevice92->m_nConfRev, pBufferPos);
		if (byteTag != 0x83)
		{
			return -1;
		}

		//smpSynch
		ReadTagLenValue(byteTag, nLen, pDevice92->m_nSmpSynch, pBufferPos);
		if (byteTag != 0x85)
		{
			return -1;
		}

		//通道数
		long nChCount = 0;
		ReadTagLength(byteTag, nChCount, pBufferPos);
		if (byteTag != 0x87)
		{
			return -1;
		}

		nChCount /= 8;
		pDevice92->SetChannelNum(nChCount);

		for (long nChIndex=1; nChIndex<=nChCount; nChIndex++)
		{
			Ep_BufferReadWord2(pBufferPos);
			Ep_BufferReadWord2(pBufferPos);
		}
	}

	return 0;
}

BOOL C92Frame::Match(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetBufferCurr(pBufferPos);

	if (*pRcvBuffer == 0x30)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
