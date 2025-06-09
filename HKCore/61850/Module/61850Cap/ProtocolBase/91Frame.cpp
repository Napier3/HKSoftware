#include "StdAfx.h"

#include "91Frame.h"
#include "..\CapDevice\CapDevice91.h"

//////////////////////////////////////////////////////////////////////////
//
C91Frame::C91Frame()
{
	m_strID = _T("9-1");
	m_strName = m_strID;
}

C91Frame::~C91Frame()
{

}

DWORD C91Frame::ParseOwn(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList)
{
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);

	long APDULen = ReadLength(_T("APDULen"), pBufferPos, pDetailList);

	int Len_noASDU = 2;
	long Num_ASDU = Ep_BufferReadDWord2(pBufferPos, Len_noASDU);//Bytes2UInt(pPacketStream+_pos,Len_noASDU);
	pDetailList->AddByteBlockByValue(_T("Num_ASDU"), Num_ASDU,Len_noASDU, Ep_GetValuePos(pBufferPos));

	if(Num_ASDU<=0)
	{
		return -1;
	}

	int nSingleASDULength = (APDULen-2) / Num_ASDU;

	CByteBlocks *pAsduBlocks = NULL;
	((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount = 12;
	DWORD dwValue = 0;
	WORD wValue = 0;
	BYTE byteValue = 0;

	//for(int i=0; i<Num_ASDU; i++)
	{
		CString strID;
		strID.Format(_T("ASDU-%d"), 1);
		pAsduBlocks = pDetailList->AddNewByteBlocks(strID);

		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("Length"), wValue, Ep_GetValuePos(pBufferPos));

		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("LNName"), byteValue, Ep_GetValuePos(pBufferPos));

		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("DataSetName"), byteValue, Ep_GetValuePos(pBufferPos));

		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("LDName"), wValue, Ep_GetValuePos(pBufferPos));

		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("额定相电流"), wValue, Ep_GetValuePos(pBufferPos));

		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("额定中心点电流"), wValue, Ep_GetValuePos(pBufferPos));

		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("额定相电压"), wValue, Ep_GetValuePos(pBufferPos));

		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("延时时间"), wValue, Ep_GetValuePos(pBufferPos));

		for (long nChIndex=1; nChIndex<=12; nChIndex++)
		{
			CString strID;
			strID.Format(_T("通道%d"), nChIndex);
			wValue = Ep_BufferReadWord2(pBufferPos);
			pAsduBlocks->AddByteBlockByValue(strID, (short)wValue, Ep_GetValuePos(pBufferPos));
		}

		dwValue = Ep_BufferReadDWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("StateWord"), dwValue, Ep_GetValuePos(pBufferPos));

		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("smpCnt"), wValue, Ep_GetValuePos(pBufferPos));

		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("SmpRate"), byteValue, Ep_GetValuePos(pBufferPos));

		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("Version"), byteValue, Ep_GetValuePos(pBufferPos));
	}

	if (Num_ASDU > 1)
	{
		CString strID;
		strID = _T("ASDU-状态数据集");
		pAsduBlocks = pDetailList->AddNewByteBlocks(strID);

// 		dwValue = Ep_BufferReadDWord2(pBufferPos);
// 		pAsduBlocks->AddByteBlockByValue(_T("State"), dwValue, Ep_GetValuePos(pBufferPos));
// 
		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("Length"), wValue, Ep_GetValuePos(pBufferPos));

		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("LNName"), byteValue, Ep_GetValuePos(pBufferPos));

		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("DataSetName"), byteValue, Ep_GetValuePos(pBufferPos));

		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("LDName"), wValue, Ep_GetValuePos(pBufferPos));

		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("额定相电流"), wValue, Ep_GetValuePos(pBufferPos));

		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("额定中心点电流"), wValue, Ep_GetValuePos(pBufferPos));

		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("额定相电压"), wValue, Ep_GetValuePos(pBufferPos));

		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("延时时间"), wValue, Ep_GetValuePos(pBufferPos));

		//5
		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("Value"), byteValue, Ep_GetValuePos(pBufferPos));
		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("Value"), byteValue, Ep_GetValuePos(pBufferPos));
		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("Value"), byteValue, Ep_GetValuePos(pBufferPos));
		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("Value"), byteValue, Ep_GetValuePos(pBufferPos));
		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("Value"), byteValue, Ep_GetValuePos(pBufferPos));

		//
		wValue = Ep_BufferReadWord2(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("smpCnt"), wValue, Ep_GetValuePos(pBufferPos));

		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("SmpRate"), byteValue, Ep_GetValuePos(pBufferPos));

		byteValue = Ep_BufferReadByte(pBufferPos);
		pAsduBlocks->AddByteBlockByValue(_T("Version"), byteValue, Ep_GetValuePos(pBufferPos));
	}

	return 0;
}

DWORD C91Frame::ParseOwn(PEPBUFFERPOS pBufferPos)
{
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);

	long APDULen = ReadLength(pBufferPos);

	int Len_noASDU = 2;
	long Num_ASDU = Ep_BufferReadDWord2(pBufferPos, Len_noASDU);//Bytes2UInt(pPacketStream+_pos,Len_noASDU);
	if(Num_ASDU<=0)
	{
		return -1;
	}

	int nSingleASDULength = (APDULen-2) / Num_ASDU;
	CByteBlocks *pAsduBlocks = NULL;
	((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount = 12;
	ASSERT (pBufferPos->pDatas != NULL);
	PEPCAPPARSEDATA pData = pBufferPos->pDatas->pDatas;

	WORD wValue = 0;
	BYTE byteValue = 0;
	DWORD dwValue = 0;

	//for(int i=0; i<Num_ASDU; i++)
	{
		wValue = Ep_BufferReadWord2(pBufferPos);
		byteValue = Ep_BufferReadByte(pBufferPos);
		byteValue = Ep_BufferReadByte(pBufferPos);
		wValue = Ep_BufferReadWord2(pBufferPos);
		wValue = Ep_BufferReadWord2(pBufferPos);
		wValue = Ep_BufferReadWord2(pBufferPos);
		wValue = Ep_BufferReadWord2(pBufferPos);
		wValue = Ep_BufferReadWord2(pBufferPos);

		for (long nChIndex=1; nChIndex<=12; nChIndex++)
		{
			pData->dwValue = (short)Ep_BufferReadWord2(pBufferPos);
			pData++;
		}

		dwValue = Ep_BufferReadDWord2(pBufferPos);
		wValue = Ep_BufferReadWord2(pBufferPos);
		byteValue = Ep_BufferReadByte(pBufferPos);

		byteValue = Ep_BufferReadByte(pBufferPos);
	}

	if (Num_ASDU > 1)
	{
		wValue = Ep_BufferReadWord2(pBufferPos);
		Ep_OffsetBufferCurr(pBufferPos, wValue);

// 		byteValue = Ep_BufferReadByte(pBufferPos);
// 		byteValue = Ep_BufferReadByte(pBufferPos);
// 		wValue = Ep_BufferReadWord2(pBufferPos);
// 		wValue = Ep_BufferReadWord2(pBufferPos);
// 		wValue = Ep_BufferReadWord2(pBufferPos);
// 		wValue = Ep_BufferReadWord2(pBufferPos);
// 		wValue = Ep_BufferReadWord2(pBufferPos);
// 		//5
// 		byteValue = Ep_BufferReadByte(pBufferPos);
// 		byteValue = Ep_BufferReadByte(pBufferPos);
// 		byteValue = Ep_BufferReadByte(pBufferPos);
// 		byteValue = Ep_BufferReadByte(pBufferPos);
// 		byteValue = Ep_BufferReadByte(pBufferPos);
// 
// 		//
// 		wValue = Ep_BufferReadWord2(pBufferPos);
// 		byteValue = Ep_BufferReadByte(pBufferPos);
// 		byteValue = Ep_BufferReadByte(pBufferPos);
	}

	pBufferPos->pDatas->dwDatas = pData - pBufferPos->pDatas->pDatas;

	return 0;
}

DWORD C91Frame::ParseInfor(PEPBUFFERPOS pBufferPos, CExBaseObject *pDevice)
{
	CCapDevice91 *pDevice91 = (CCapDevice91 *)pDevice;
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);
	long APDULen = ReadLength(pBufferPos);

	int Len_noASDU = 2;
	pDevice91->m_nAsduNum = Ep_BufferReadDWord2(pBufferPos, Len_noASDU);//Bytes2UInt(pPacketStream+_pos,Len_noASDU);
	if(pDevice91->m_nAsduNum<=0)
	{
		return -1;
	}

	pDevice91->SetChannelNum(12);

	//for(int i=0; i<pDevice91->m_nAsduNum; i++)
	{
		WORD wValue = Ep_BufferReadWord2(pBufferPos);
		pDevice91->m_dwLNName = Ep_BufferReadByte(pBufferPos);
		pDevice91->m_dwDataSet = Ep_BufferReadByte(pBufferPos);
		pDevice91->m_dwLDName = Ep_BufferReadWord2(pBufferPos);
		pDevice91->m_dwINomPh = Ep_BufferReadWord2(pBufferPos);
		pDevice91->m_dwINomNeutral = Ep_BufferReadWord2(pBufferPos);
		pDevice91->m_dwUNomPh = Ep_BufferReadWord2(pBufferPos);
		pDevice91->m_dwDelayTime = Ep_BufferReadWord2(pBufferPos);

		for (long nChIndex=1; nChIndex<=12; nChIndex++)
		{
			Ep_BufferReadWord2(pBufferPos);
		}

		pDevice91->m_dwStateWord = Ep_BufferReadDWord2(pBufferPos);
		pDevice91->m_dwSmpCnt = Ep_BufferReadWord2(pBufferPos);
		pDevice91->m_nSampleRate = Ep_BufferReadByte(pBufferPos);
		pDevice91->m_dwVersion = Ep_BufferReadByte(pBufferPos);
	}

	if (pDevice91->m_nAsduNum > 1)
	{
		WORD wValue = Ep_BufferReadWord2(pBufferPos);
		Ep_OffsetBufferCurr(pBufferPos, wValue);
	}

	return 0;
}

BOOL C91Frame::Match(PEPBUFFERPOS pBufferPos)
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
