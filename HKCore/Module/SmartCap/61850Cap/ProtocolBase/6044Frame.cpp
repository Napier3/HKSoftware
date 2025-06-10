#include "stdafx.h"

#include "6044Frame.h"
#include "../CapDevice/CapDevice6044.h"

//////////////////////////////////////////////////////////////////////////
//
C6044Frame::C6044Frame()
{
	m_strID = _T("6044");
	m_strName = m_strID;
}

C6044Frame::~C6044Frame()
{
}

//#define  USE_OLD
long C6044Frame::ParseOwn(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList)
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

#ifdef USE_OLD
	ReadTagLenValue(_T("ASDU-NO"), byteTag, nLen, Num_ASDU,  pBufferPos,  pDetailList);
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

#endif

#ifndef USE_OLD
	//security 是0x81 当是81的时候，后面的长度就是值；
	while (TRUE)
	{
		CString strID; 
		//把strID带出来，把byteTag也代出来；
		ReadTagLen(strID,  byteTag,  nLen,  pBufferPos,  pDetailList);

		switch (byteTag)
		{
		case 0x80:		
			{
				ReadTagValue(strID,  nLen, nValue, pBufferPos, pDetailList);
				Num_ASDU = nValue;
				break;
			}
		case 0x81:	//Security
			{
				//这时候 不用再调用读取VALUE函数，	ReadTagValue(nLen,  nValue,  pBufferPos);
				//直接获取nLen，就是获得的值；

				break;
			}
		default:
			break;
		}

		if (byteTag == 0xA2)
		{
			//ReadTagValue(strID,  nLen, nValue, pBufferPos, pDetailList);
			break;
		}
	}
#endif
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Loop ASDU 
	CByteBlocks *pAsduBlocks = NULL;

	for(int i  =  0;  i < Num_ASDU;  i++)
	{
		CString strID;
		strID.Format(_T("ASDU-%d"),  i + 1);
		pAsduBlocks = pDetailList->AddNewByteBlocks(strID);

		//ASDU 标记
		ReadTagLength(_T("ASDU-Tag"),   byteTag,   nLen,   pBufferPos,   pAsduBlocks);

		//SVID
		ReadTagLenValue(_T("SVID"),   byteTag,   nLen,   strValue,  pBufferPos,  pAsduBlocks);
		if (byteTag != 0x80)
		{
			return -1;
		}

		long nChCount = 0;

#ifndef USE_OLD
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//mym add 2020-07-23 
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (Ep_NoInBuffer(pBufferPos))
		{
			return -1;
		}
		
		while (TRUE)
		{
			if (! Ep_IsBufferEnough(pBufferPos, nLen))//2020-07-15  lijunqing  数据的长度足够
			{
				return -1;
			}


			CString strID; 
			//把strID带出来，把byteTag也代出来；
			ReadTagLenEx(strID,  byteTag,  nLen,  pBufferPos,  pAsduBlocks);

			switch (byteTag)
			{
			case 0x81:				
			case 0x82:				
			case 0x83:				
			case 0x84:			
			case 0x85:				
			case 0x86:
				{
					ReadTagValue(strID,  nLen, nValue, pBufferPos, pAsduBlocks);
					break;
				}
			}

			if (byteTag == 0x87)
			{	
				nChCount  = nLen;
				break;
			}
		}

#endif

		//需要添加的
		//0x81 security 0x86   smprate 0x84  refresh time    mym add 2020-7-13
		
#ifdef USE_OLD
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
		//long nChCount = 0;
		ReadTagLength(_T("通道数"), byteTag, nChCount, pBufferPos, pAsduBlocks);
		if (byteTag != 0x87)
		{
			return -1;
		}
#endif
		

		nChCount /= 8;
        if (((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount != nChCount) // 20220628 zhouhj 由之前的小于改为不等于
            ((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount = nChCount;

        //((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount = max(((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount, nChCount);
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

long C6044Frame::ParseOwn(PEPBUFFERPOS pBufferPos)
{
	//6044的内容就是对应的数据部分,解析不放在此处
//	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);
// 	PEPCAPPARSEDATAS pDatas = pBufferPos->pDatas;  
// 	PEPCAPPARSEDATA pData = pDatas->pDatas;
// 	pBufferPos->pDatas->dwDatas = pData -  pBufferPos->pDatas->pDatas;
	return 0;
}


DWORD C6044Frame::ParseInfor(PEPBUFFERPOS pBufferPos, CExBaseObject *pDevice)
{
	CCapDevice6044 *pDevice6044 = (CCapDevice6044 *)pDevice;
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
	ReadTagLenValue(byteTag, nLen, pDevice6044->m_nAsduNum, pBufferPos);
	if (byteTag != 0x80)
	{
		return -1;
	}

	if(pDevice6044->m_nAsduNum<=0)
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

	for(int i=0; i<pDevice6044->m_nAsduNum; i++)
	{
		//ASDU 标记
		ReadTagLength(byteTag, nLen, pBufferPos);

// 		//SVID
// 		ReadTagLenValue(byteTag, nLen, pDevice6044->m_strSVID, pBufferPos);
// 		if (byteTag != 0x80)
// 		{
// 			return -1;
// 		}

		//smpCnt
		ReadTagLenValue(byteTag, nLen, nValue, pBufferPos);
		if (byteTag != 0x82)
		{
			return -1;
		}

// 		//confRev
// 		ReadTagLenValue(byteTag, nLen, pDevice6044->m_nConfRev, pBufferPos);
// 		if (byteTag != 0x83)
// 		{
// 			return -1;
// 		}

// 		//smpSynch
// 		ReadTagLenValue(byteTag, nLen, pDevice6044->m_nSmpSynch, pBufferPos);
// 		if (byteTag != 0x85)
// 		{
// 			return -1;
// 		}

		//通道数
		long nChCount = 0;
		ReadTagLength(byteTag, nChCount, pBufferPos);
		if (byteTag != 0x87)
		{
			return -1;
		}

		nChCount /= 8;
		pDevice6044->SetChannelNum(nChCount);

		for (long nChIndex=1; nChIndex<=nChCount; nChIndex++)
		{
			Ep_BufferReadWord2(pBufferPos);
			Ep_BufferReadWord2(pBufferPos);
		}
	}

	return 0;
}

BOOL C6044Frame::Match(PEPBUFFERPOS pBufferPos)
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
