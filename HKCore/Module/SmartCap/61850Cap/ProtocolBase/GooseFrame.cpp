#include "stdafx.h"

#include "GooseFrame.h"
#include "../CapDevice/CapDeviceGoose.h"

//////////////////////////////////////////////////////////////////////////
//
CStGooseFrame::CStGooseFrame()
{
	m_strID = _T("GOOSE");
	m_strName = m_strID;
}

CStGooseFrame::~CStGooseFrame()
{

}

long CStGooseFrame::ParseOwn(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList)
{
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);

	long DataLen = Ep_BufferLeave(pBufferPos);
	BYTE *pPacketStream = pBuffer;
	int _pos = 0;
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

	//gocbRef
	ReadTagLenValue(_T("gocbRef"), byteTag, nLen, strValue, pBufferPos, pDetailList);
	if (byteTag != 0x80)
	{
		return -1;
	}

	//timeAllowedtoLive
	ReadTagLenValue(_T("timeAllowedtoLive"), byteTag, nLen, nValue, pBufferPos, pDetailList);
	if (byteTag != 0x81)
	{
		return -1;
	}

	//dataSet
	ReadTagLenValue(_T("dataSet"), byteTag, nLen, strValue, pBufferPos, pDetailList);
	if (byteTag != 0x82)
	{
		return -1;
	}

	//goID
	ReadTagLenValue(_T("goID"), byteTag, nLen, strValue, pBufferPos, pDetailList);
	if (byteTag != 0x83)
	{
		return -1;
	}

	//Time
	double dTime = 0;
	ReadTime(_T("Time"), byteTag, nLen, dTime, pBufferPos, pDetailList);
	if (byteTag != 0x84)
	{
		return -1;
	}

	//stNum
	ReadTagLenValue(_T("stNum"), byteTag, nLen, nValue, pBufferPos, pDetailList);
	if (byteTag != 0x85)
	{
		return -1;
	}

	//sqNum
	ReadTagLenValue(_T("sqNum"), byteTag, nLen, nValue, pBufferPos, pDetailList);
	if (byteTag != 0x86)
	{
		return -1;
	}

	//Test
	ReadTagLenValue(_T("Test"), byteTag, nLen, nValue, pBufferPos, pDetailList);
	if (byteTag != 0x87)
	{
		return -1;
	}

	//confRev
	ReadTagLenValue(_T("confRev"), byteTag, nLen, nValue, pBufferPos, pDetailList);
	if (byteTag != 0x88)
	{
		return -1;
	}

	//ndsCom
	ReadTagLenValue(_T("ndsCom"), byteTag, nLen, nValue, pBufferPos, pDetailList);
	if (byteTag != 0x89)
	{
		return -1;
	}

	//ͨ����
	long nChCount = 0;
	ReadTagLenValue(_T("ͨ����"), byteTag, nLen, nChCount, pBufferPos, pDetailList);
	if (byteTag != 0x8A)
	{
		return -1;
	}

	//Datas
	ReadTagLength(_T("AllDatas"), byteTag, nLen, pBufferPos, pDetailList);
	if (byteTag != 0xAB)
	{
		return -1;
	}

	CByteBlocks *pChBlocks = NULL;

    if (((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount < nChCount)
    {
        ((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount = nChCount;
    }

    //((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount = max(((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount, nChCount);

	for (long nChIndex=1; nChIndex<=nChCount; nChIndex++)
	{
		CString strID;
		strID.Format(_T("ͨ��%d"), nChIndex);
		pChBlocks = pDetailList->AddNewByteBlocks(strID);

		//type
		BYTE byteType = Ep_BufferReadByte(pBufferPos);
		pChBlocks->AddByteBlockByValue(_T("_Type"), byteType, Ep_GetValuePos(pBufferPos));

		nLen = Ep_BufferReadByte(pBufferPos);
		pChBlocks->AddByteBlockByValue(_T("_Length"), (BYTE)nLen, Ep_GetValuePos(pBufferPos));

		switch (byteType)
		{
		case 0x83://����
			byteValue = Ep_BufferReadByte(pBufferPos);
			pChBlocks->AddByteBlockByValue(_T("_Value"), byteValue, Ep_GetValuePos(pBufferPos));
			pChBlocks->AddBbInfor(_T("����"), _T("����"));
			break;
		case 0x84://˫��
			nValue = Ep_BufferReadDWord2(pBufferPos, nLen);
			pChBlocks->AddByteBlockByValue(_T("_Value"), nValue, nLen, Ep_GetValuePos(pBufferPos));

// 			if (nLen == 2)//20220623 zhouhj �����ֽڳ����޷��ж�˫�㡢Ʒ�ʵ���Ϣ
// 			{
// 				pChBlocks->AddBbInfor(_T("����"), _T("˫��"));
// 			}
// 			else if (nLen == 3)//20220613  zhouhj 
// 			{
// 				pChBlocks->AddBbInfor(_T("����"), _T("Ʒ��"));
// 			}
// 			else
			{
				pChBlocks->AddBbInfor(_T("����"), _T("λ��"));
			}
			break;
		case 0x85://ö�١�����
			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
			pChBlocks->AddByteBlockByValue(_T("_Value"), nValue, nLen, Ep_GetValuePos(pBufferPos));

			if (nLen == 2)
			{
				pChBlocks->AddBbInfor(_T("����"), _T("ö��"));
			} 
			else
			{
				pChBlocks->AddBbInfor(_T("����"), _T("INT"));
			}
			break;
		case 0x86://UINT
			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
			pChBlocks->AddByteBlockByValue(_T("_Value"), nValue, nLen, Ep_GetValuePos(pBufferPos));
			pChBlocks->AddBbInfor(_T("����"), _T("UINT"));
			break;
		case 0x91://ʱ��
			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
			pChBlocks->AddByteBlockByValue(_T("_Value"), nValue, nLen, Ep_GetValuePos(pBufferPos));
			pChBlocks->AddBbInfor(_T("����"), _T("ʱ��"));
			break;
		case 0x87://����
			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
			pChBlocks->AddByteBlockByValue(_T("_Value"), nValue, nLen, Ep_GetValuePos(pBufferPos));
			pChBlocks->AddBbInfor(_T("����"), _T("����"));
			break;
		case 0xA2://�ṹ  20220615 zhouhj  ��ʱ��������ʽ����,�����迼�ǵ��ṹ���ڵĲ�ͬ��������
			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
			pChBlocks->AddByteBlockByValue(_T("_Value"), nValue, nLen, Ep_GetValuePos(pBufferPos));
			pChBlocks->AddBbInfor(_T("����"), _T("�ṹ"));
			break;
		case 0x8A://�ַ���
			{
				char strText[MAX_PATH];
				Ep_BufferReadString(pBufferPos, nLen, strText);
				pChBlocks->AddByteBlockByValue(_T("_Value"), CString(strText), nLen, Ep_GetValuePos(pBufferPos));
				pChBlocks->AddBbInfor(_T("����"), _T("����"));
			}
		default:
			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
			pChBlocks->AddByteBlockByValue(_T("_Value"), nValue, nLen, Ep_GetValuePos(pBufferPos));
			pChBlocks->AddBbInfor(_T("����"), _T("����"));
			break;
		}
	}

	return Ep_OffsetBufferCurr(pBufferPos, _pos);
}

long CStGooseFrame::ParseOwn(PEPBUFFERPOS pBufferPos)
{
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);

	long DataLen = Ep_BufferLeave(pBufferPos);

	PEPCAPPARSEDATAS pDatas = pBufferPos->pDatas;   // add mym 2020-06-17

	BYTE *pPacketStream = pBuffer;
	int _pos = 0;
	BYTE byteValue = 0;
	WORD wValue = 0;
	DWORD dwValue = 0;
	long nValue = 0;
	long nLen = 0;
	BYTE byteTag = 0;
	CString strValue;
    
	//������ȱ��VLANID ,VLANP �ķ������   mym   2020-06-19;
	EPGOOSEPARSEDATA *pGoData = &pDatas->oDataGs;

	//APDULen
	long APDULen = 0;
	APDULen = ReadLength(pBufferPos);

	pGoData->APDULen = APDULen;

	//gocbRef
	ReadTagLenValue(byteTag, nLen, pGoData->GORef, pBufferPos);
	if (byteTag != 0x80)
	{
		return -1;
	}

	//timeAllowedtoLive
	ReadTagLenValue(byteTag,  nLen,  pGoData->TimeAllowedToLive,  pBufferPos);
	if (byteTag != 0x81)
	{
		return -1;
	}

	//dataSet
	ReadTagLenValue(byteTag,  nLen,  pDatas->oDataGs.GODataSet, pBufferPos);//wangtao 20240509 DataSet�������ĵĵط�
	if (byteTag != 0x82)
	{
		return -1;
	}

	//goID
	ReadTagLenValue(byteTag,  nLen,  pDatas->oDataGs.GOID,  pBufferPos);
	if (byteTag != 0x83)
	{
		return -1;
	}

	//Time
	double dTime = 0;
	BYTE *pCurr = Ep_GetBufferCurr(pBufferPos);
	pGoData->ClockFlag = pCurr[9];//20220620  zhouhj ʱ�����ݵ����һ���ֽ�ΪƷ��

	ReadTime(byteTag, nLen, pGoData->EventTimeSample, pBufferPos);

	if (byteTag != 0x84)
	{
		return -1;
	}

	//stNum
	ReadTagLenValue(byteTag, nLen, nValue, pBufferPos);
	pDatas->oDataGs.stNO = nValue;     // add mym 2020-06-17
	if (byteTag != 0x85)
	{
		return -1;
	}

	//sqNum
	ReadTagLenValue(byteTag, nLen, nValue, pBufferPos);
	pDatas->oDataGs.sqNO  = nValue;     // add mym 2020-06-17
	if (byteTag != 0x86)
	{
		return -1;
	}

	//Test
	ReadTagLenValue(byteTag, nLen, nValue, pBufferPos);
	pDatas->oDataGs.nTestMode  = nValue;      // add mym 2020-06-19
	if (byteTag != 0x87)
	{
		return -1;
	}

	//confRev
	ReadTagLenValue(byteTag, nLen, nValue, pBufferPos);
	pDatas->oDataGs.nConfRev  = nValue;     // add mym 2020-06-19
	if (byteTag != 0x88)
	{
		return -1;
	}

	//ndsCom
	ReadTagLenValue(byteTag, nLen, nValue, pBufferPos);	
	pDatas->oDataGs.ndsCom  = nValue;       // add mym 2020-06-19
	if (byteTag != 0x89)
	{
		return -1;
	}

	//ͨ����
	long nChCount = 0;
	ReadTagLenValue(byteTag, nLen, nChCount, pBufferPos);
	pGoData->nChCnt  = nChCount;     // add mym 2020-06-17
	if (byteTag != 0x8A)
	{
		return -1;
	}

	//Datas
	ReadTagLength(byteTag, nLen, pBufferPos);
	if (byteTag != 0xAB)
	{
		return -1;
	}

    if (((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount != nChCount) // 20220628 zhouhj ��֮ǰ��С�ڸ�Ϊ������
    {
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("GOOSE��ͨ����(%ld),��ǰ֡����ͨ����(%ld),��ǰЭ��(%u)."),
// 			((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount,nChCount,((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nProtocol);
       ((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount = nChCount;
    }
    //((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount = max(((PEPCAPBUFFERITEM)pBufferPos->pItemData)->nChCount, nChCount);

	ASSERT (pBufferPos->pDatas != NULL);
	PEPCAPPARSEDATA pData = pBufferPos->pDatas->pDatas;

	//for (long nChIndex=1; nChIndex<=nChCount; nChIndex++)

	for (long nChIndex = 0; nChIndex < nChCount;  nChIndex++)
	{ 
		//type
		pData->wChType = Ep_BufferReadByte(pBufferPos);
		nLen = Ep_BufferReadByte(pBufferPos);
		pData->wLength = nLen;

		pDatas->oDataGs.chData[nChIndex].wChType = pData->wChType;   // add mym 2020-06-17
		switch (pData->wChType)
		{
		case 0x83://����
			pData->dwValue = Ep_BufferReadByte(pBufferPos);
			pDatas->oDataGs.chData[nChIndex].dwValue =  pData->dwValue ; // add mym 2020-06-17
			break;
		case 0x84://˫��
			pData->dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
			pDatas->oDataGs.chData[nChIndex].dwValue =  pData->dwValue ; // add mym 2020-06-17
			break;
		case 0x85://ö��
			pData->dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
			pDatas->oDataGs.chData[nChIndex].dwValue =  pData->dwValue ; // add mym 2020-06-17
			break;
		case 0x86://UINT
			pData->dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
			pDatas->oDataGs.chData[nChIndex].dwValue =  pData->dwValue ; // add mym 2020-06-17
			break;
		case 0x91://ʱ��
			pData->dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
			pDatas->oDataGs.chData[nChIndex].dwValue =  pData->dwValue ; // add mym 2020-06-17
			break;
		case 0x87://����
			pData->dwValue = Ep_BufferReadFloat2(pBufferPos, nLen);
			pDatas->oDataGs.chData[nChIndex].dwValue =  pData->dwValue ; // add mym 2020-06-17
			break;
		case 0x8A://����
			pData->dwValue = Ep_BufferReadFloat2(pBufferPos, nLen);//20220615����ֵ��ȡ
			//Ep_OffsetBufferCurr(pBufferPos, nLen);
			pDatas->oDataGs.chData[nChIndex].dwValue =  pData->dwValue ; // add mym 2020-06-17
			break;
		default:
			pData->dwValue = 0;
			Ep_OffsetBufferCurr(pBufferPos, nLen);//Ep_BufferReadDWord2(pBufferPos, nLen);
			break;
		}
		pData++;
	}

	pBufferPos->pDatas->dwDatas = pData - pBufferPos->pDatas->pDatas;

	return 0;
}

DWORD CStGooseFrame::ParseInfor(PEPBUFFERPOS pBufferPos, CExBaseObject *pDevice)
{
	ASSERT (CPDCLASSID_DEVICEGOOSE == pDevice->GetClassID());
	CCapDeviceGoose *pDeviceGoose = (	CCapDeviceGoose *)pDevice;
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);

	BYTE byteValue = 0;
	WORD wValue = 0;
	DWORD dwValue = 0;
	long nValue = 0;
	long nLen = 0;
	BYTE byteTag = 0;
	CString strValue;

	//APDULen
	long APDULen = 0;
	APDULen = ReadLength(pBufferPos);

	//gocbRef
	ReadTagLenValue(byteTag, nLen, pDeviceGoose->m_strgocbRef, pBufferPos);
	if (byteTag != 0x80)
	{
		return -1;
	}

	//timeAllowedtoLive
	ReadTagLenValue(byteTag, nLen, pDeviceGoose->m_dwTimeAllowToAlive, pBufferPos);
	if (byteTag != 0x81)
	{
		return -1;
	}

	//dataSet
	ReadTagLenValue(byteTag, nLen, pDeviceGoose->m_strDataSet, pBufferPos);
	if (byteTag != 0x82)
	{
		return -1;
	}

	//goID
	ReadTagLenValue(byteTag, nLen, pDeviceGoose->m_strGooseId, pBufferPos);
	if (byteTag != 0x83)
	{
		return -1;
	}

	//Time
	double dTime = 0;
	ReadTime(byteTag, nLen, pDeviceGoose->m_dTime, pBufferPos);
	if (byteTag != 0x84)
	{
		return -1;
	}

	//stNum
	ReadTagLenValue(byteTag, nLen, pDeviceGoose->m_dwStNum, pBufferPos);
	if (byteTag != 0x85)
	{
		return -1;
	}

	//sqNum
	ReadTagLenValue(byteTag, nLen, pDeviceGoose->m_dwSqNum, pBufferPos);
	if (byteTag != 0x86)
	{
		return -1;
	}

	//Test
	ReadTagLenValue(byteTag, nLen, pDeviceGoose->m_nTest, pBufferPos);
	if (byteTag != 0x87)
	{
		return -1;
	}

	//confRev
	ReadTagLenValue(byteTag, nLen, pDeviceGoose->m_dwVersion, pBufferPos);
	if (byteTag != 0x88)
	{
		return -1;
	}

	//ndsCom
	ReadTagLenValue(byteTag, nLen, pDeviceGoose->m_dwNdsCom, pBufferPos);
	if (byteTag != 0x89)
	{
		return -1;
	}

	//ͨ����
	long nChCount = 0;
	ReadTagLenValue(byteTag, nLen, nChCount, pBufferPos);
	if (byteTag != 0x8A)
	{
		return -1;
	}

	//Datas
	ReadTagLength(byteTag, nLen, pBufferPos);
	if (byteTag != 0xAB)
	{
		return -1;
	}

	pDeviceGoose->SetChannelNum(nChCount);
	CCapDeviceGooseCh *pCh = NULL;

	for (long nChIndex=1; nChIndex<=nChCount; nChIndex++)
	{
		if (Ep_NoInBuffer(pBufferPos))
		{
			return -1;
		}

		pCh = (CCapDeviceGooseCh*)pDeviceGoose->GetAtIndex(nChIndex-1);

		if (pCh == NULL)
		{
			break;
		}

		pCh->m_nChType = Ep_BufferReadByte(pBufferPos);
		pCh->m_nLength = Ep_BufferReadByte(pBufferPos);
		Ep_OffsetBufferCurr(pBufferPos, pCh->m_nLength);

// 		switch (pCh->m_nChType)
// 		{
// 		case 0x83://����
// 			dwValue = Ep_BufferReadByte(pBufferPos);
// 			break;
// 		case 0x84://˫��
// 			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
// 			break;
// 		case 0x85://ö��
// 			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
// 			break;
// 		case 0x86://UINT
// 			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
// 			break;
// 		case 0x91://ʱ��
// 			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
// 			break;
// 		case 0x87://����
// 			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
// 			break;
// 		case 0x8A://�ַ���
// 			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
// 			break;
// 		default:
// 			dwValue = Ep_BufferReadDWord2(pBufferPos, nLen);
// 			break;
// 		}

		pCh->InitChTypeName();
	}

	return 0;
}

BOOL CStGooseFrame::Match(PEPBUFFERPOS pBufferPos)
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
