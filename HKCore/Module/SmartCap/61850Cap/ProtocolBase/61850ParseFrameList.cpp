// 61850ParseFrameList.cpp: implementation of the C61850ParseFrameList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "61850ParseFrameList.h"
#include "../EthernetCapGlobalDef.h"
#include "../CapDevice/CapDeviceGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C61850ParseFrameList::C61850ParseFrameList()
{
	m_p91Frame = new C91Frame();
	AddNewChild(m_p91Frame);

	m_p92Frame = new C92Frame();
	AddNewChild(m_p92Frame);

	m_pGooseFrame = new CStGooseFrame();
	AddNewChild(m_pGooseFrame);
	m_p6044Frame = NULL;
}

C61850ParseFrameList::~C61850ParseFrameList()
{
}

C6044Frame* C61850ParseFrameList::Get6044Frame()
{
	if (m_p6044Frame != NULL)
	{
		return m_p6044Frame;
	}

	m_p6044Frame = new C6044Frame();
	AddNewChild(m_p6044Frame);
	return m_p6044Frame;
}

CFrameBase* C61850ParseFrameList::Parse(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList)
{
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);

	PEPCAPBUFFERITEM pItemData = (PEPCAPBUFFERITEM)pBufferPos->pItemData;
	PETHER_HEADER pHeader = (PETHER_HEADER)pBuffer;
    unsigned short EtherType = pHeader->ether_type;
	u_short nAPPID = 0;
	Ep_OffsetBufferCurr(pBufferPos, 14);//sizeof(ETHER_HEADER));

	if (pDetailList!= NULL)
	{
		//yyj
		pDetailList->AddByteBlockByValue_MAC(_T("目标MAC"), pHeader->ether_dhost, 0);
		pDetailList->AddByteBlockByValue_MAC(_T("源MAC"), pHeader->ether_shost, 6);
	}

	memcpy(pItemData->addr_61850.srcMac, pHeader->ether_shost, 6);
	memcpy(pItemData->addr_61850.dstMac, pHeader->ether_dhost, 6);

	//判断是否存在优先级标志
	if (EtherType == 0x0081)	//存在优先级标志
	{
		if (pDetailList!= NULL)
		{
			//yyj
//			pDetailList->AddByteBlockByValue(_T("优先级标志"), EtherType, 12);
			Ep_OffsetBufferCurr(pBufferPos, -2);

			WORD wTPID = Ep_BufferReadWord2(pBufferPos);
			pDetailList->AddByteBlockByValue(_T("TPID"), wTPID, Ep_GetValuePos(pBufferPos));

			WORD wTCI = Ep_BufferReadWord2(pBufferPos);
			pDetailList->AddByteBlockByValue(_T("TCI"), wTCI, Ep_GetValuePos(pBufferPos));
		}

		if(!Ep_IsBufferEnough(pBufferPos, 18))
		{
			return NULL;	
		}

		EtherType = Ep_BufferReadWord(pBufferPos);
	}
	else
	{

	}

	if (pDetailList!= NULL)
	{
		pDetailList->AddByteBlockByValue(_T("EtherType"), EtherType, Ep_GetValuePos(pBufferPos));
	}

	//APPID
	nAPPID = Ep_BufferReadWord2(pBufferPos);
	pItemData->addr_61850.APPID = nAPPID;

	if (pDetailList!= NULL)
	{
		pDetailList->AddByteBlockByValue(_T("APPID"), nAPPID, Ep_GetValuePos(pBufferPos));
	}

	//Length
	WORD nLength = Ep_BufferReadWord2(pBufferPos);

	if (pDetailList!= NULL)
	{
		pDetailList->AddByteBlockByValue(_T("Length"), nLength, Ep_GetValuePos(pBufferPos));
	}

	WORD wReserve1 = Ep_BufferReadWord(pBufferPos);
	if (pDetailList!= NULL)
	{
		pDetailList->AddByteBlockByValue(_T("Reserve1"), wReserve1, Ep_GetValuePos(pBufferPos));
	}

	WORD wReserve2 = Ep_BufferReadWord(pBufferPos);
	if (pDetailList!= NULL)
	{
		pDetailList->AddByteBlockByValue(_T("Reserve2"), wReserve2, Ep_GetValuePos(pBufferPos));
	}

	if(EtherType==0xBA88)
	{
		BYTE byteType = Ep_BufferReadByte(pBufferPos);

		if(byteType == 0x60)
		{
			if (pDetailList!= NULL)
			{
				pDetailList->AddNewByteBlock(_T("规约类型"), 1, Ep_GetValuePos(pBufferPos));
				pDetailList->AddBbInfor(_T("类型"), _T("9-2"));
			}
			pItemData->nProtocol = PROTOCOL_61850_TYPE_92;
			pBufferPos->pDatas->nParseState = m_p92Frame->ParseOwn(pBufferPos, pDetailList);

			return m_p92Frame;
		}

		if(byteType==0x80)
		{
			if (pDetailList!= NULL)
			{
				pDetailList->AddNewByteBlock(_T("规约类型"), 1, Ep_GetValuePos(pBufferPos));
				pDetailList->AddBbInfor(_T("类型"), _T("9-1"));
			}

			pItemData->nProtocol = PROTOCOL_61850_TYPE_91;
			pBufferPos->pDatas->nParseState = m_p91Frame->ParseOwn(pBufferPos, pDetailList);

			return m_p91Frame;
		}

		return NULL;
	}

	if(EtherType==0xB888)
	{
		BYTE byteType = Ep_BufferReadByte(pBufferPos);

		if(byteType==0x61)
		{
			if (pDetailList!= NULL)
			{
				pDetailList->AddByteBlockByValue(_T("规约类型"), byteType, Ep_GetValuePos(pBufferPos));
				pDetailList->AddBbInfor(_T("类型"), _T("GOOSE"));
			}
			pItemData->nProtocol = PROTOCOL_61850_TYPE_GOOSE;
			pBufferPos->pDatas->nParseState = m_pGooseFrame->ParseOwn(pBufferPos, pDetailList);
			return m_pGooseFrame;
		}
	}

	return NULL;
}

CFrameBase* C61850ParseFrameList::ParseInfor(PEPBUFFERPOS pBufferPos, CExBaseObject *pDevice)
{
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);

	PEPCAPBUFFERITEM pItemData = (PEPCAPBUFFERITEM)pBufferPos->pItemData;
	PETHER_HEADER pHeader = (PETHER_HEADER)pBuffer;
    unsigned short EtherType = pHeader->ether_type;
	u_short nAPPID = 0;
	Ep_OffsetBufferCurr(pBufferPos, 14);//sizeof(ETHER_HEADER));

	//判断是否存在优先级标志
	if (EtherType == 0x0081)	//存在优先级标志
	{
		//yyj 
		Ep_OffsetBufferCurr(pBufferPos, -2);
		WORD wTPID = Ep_BufferReadWord2(pBufferPos);
		WORD wTCI = Ep_BufferReadWord2(pBufferPos);

		if(!Ep_IsBufferEnough(pBufferPos, 18))
		{
			return NULL;	
		}

		EtherType = Ep_BufferReadWord(pBufferPos);
	}
	else
	{

	}

	//APPID
	nAPPID = Ep_BufferReadWord2(pBufferPos);

	//Length
	WORD nLength = Ep_BufferReadWord2(pBufferPos);
	WORD wReserve1 = Ep_BufferReadWord(pBufferPos);
	WORD wReserve2 = Ep_BufferReadWord(pBufferPos);

	if(EtherType==0xBA88)
	{
		BYTE byteType = Ep_BufferReadByte(pBufferPos);

		if(byteType == 0x60)
		{
			m_p92Frame->ParseInfor(pBufferPos, pDevice);
			return m_p92Frame;
		}

		if(byteType==0x80)
		{
			m_p91Frame->ParseInfor(pBufferPos, pDevice);
			return m_p91Frame;
		}

		return NULL;
	}

	if(EtherType==0xB888)
	{
		BYTE byteType = Ep_BufferReadByte(pBufferPos);

		if(byteType==0x61)
		{
			m_pGooseFrame->ParseInfor(pBufferPos, pDevice);
			return m_pGooseFrame;
		}
	}

	return NULL;
}

CFrameBase* C61850ParseFrameList::Parse(PEPBUFFERPOS pBufferPos)
{
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);

	PEPCAPBUFFERITEM pItemData = (PEPCAPBUFFERITEM)pBufferPos->pItemData;
	PETHER_HEADER pHeader = (PETHER_HEADER)pBuffer;
    unsigned short EtherType = pHeader->ether_type;
	u_short nAPPID = 0;
	Ep_OffsetBufferCurr(pBufferPos, 14);//sizeof(ETHER_HEADER));

	memcpy(pItemData->addr_61850.srcMac, pHeader->ether_shost, 6);
	memcpy(pItemData->addr_61850.dstMac, pHeader->ether_dhost, 6);

	//2020-06-27 lijunqing
	memcpy(pBufferPos->pDatas->srcMAC, pHeader->ether_shost, 6);
	memcpy(pBufferPos->pDatas->destMAC, pHeader->ether_dhost, 6);
	WORD wPri = 0,wVID = 0;

	//判断是否存在优先级标志
	if (EtherType == 0x0081)	//存在优先级标志
	{
		//yyj 
		Ep_OffsetBufferCurr(pBufferPos, -2);
		WORD wTPID = Ep_BufferReadWord2(pBufferPos);
		WORD wTCI = Ep_BufferReadWord2(pBufferPos);

		wPri = wTCI >> 13;//优先级占3位
		wVID = (wTCI&0x0FFF);//VID占12位


		if(!Ep_IsBufferEnough(pBufferPos, 18))
		{
			return NULL;	
		}

		EtherType = Ep_BufferReadWord(pBufferPos);
	}
	else
	{

	}

	//APPID
	nAPPID = Ep_BufferReadWord2(pBufferPos);
	pItemData->addr_61850.APPID = nAPPID;
	pBufferPos->pDatas->APPID = nAPPID;   //2020-06-27 lijunqing

	//Length
	WORD nLength = Ep_BufferReadWord2(pBufferPos);
	WORD wReserve1 = Ep_BufferReadWord(pBufferPos);
	WORD wReserve2 = Ep_BufferReadWord(pBufferPos);

	if(EtherType==0xBA88)
	{
		BYTE byteType = Ep_BufferReadByte(pBufferPos);

		if(byteType == 0x60)
		{
			pItemData->nProtocol = PROTOCOL_61850_TYPE_92;
			pBufferPos->pDatas->nParseState = m_p92Frame->ParseOwn(pBufferPos);
			pBufferPos->pDatas->oData92.VlanPr = wPri;
			pBufferPos->pDatas->oData92.VlanID = wVID;
			return m_p92Frame;
		}

		if(byteType==0x80)
		{
			pItemData->nProtocol = PROTOCOL_61850_TYPE_91;
			pBufferPos->pDatas->nParseState = m_p91Frame->ParseOwn(pBufferPos);

			return m_p91Frame;
		}

		return NULL;
	}

	if(EtherType==0xB888)
	{
		BYTE byteType = Ep_BufferReadByte(pBufferPos);

		if(byteType==0x61)
		{
			pItemData->nProtocol = PROTOCOL_61850_TYPE_GOOSE;
			pBufferPos->pDatas->nParseState = m_pGooseFrame->ParseOwn(pBufferPos);
			pBufferPos->pDatas->oDataGs.VLAN_P = wPri;
			pBufferPos->pDatas->oDataGs.VLAN_ID = wVID;
			return m_pGooseFrame;
		}
	}

	return NULL;
}

CFrameBase* C61850ParseFrameList::Parse_60044(PEPBUFFERPOS pBufferPos)
{
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);
	PEPCAPBUFFERITEM pItemData = (PEPCAPBUFFERITEM)pBufferPos->pItemData;
	memset(pItemData->addr_61850.srcMac, 0, 6);
	memset(pItemData->addr_61850.dstMac, 0, 6);
	memset(pBufferPos->pDatas->srcMAC, 0, 6);
	memset(pBufferPos->pDatas->destMAC, 0, 6);
	pItemData->addr_61850.APPID = 0;
	pBufferPos->pDatas->APPID = 0; 
	pItemData->nProtocol = PROTOCOL_61850_TYPE_60448;
	Get6044Frame();
	pBufferPos->pDatas->nParseState = m_p6044Frame->ParseOwn(pBufferPos);
	return m_p6044Frame;
}

// CFrameBase* C61850ParseFrameList::Match(PEPBUFFERPOS pBufferPos)
// {
// 	
// 
// 	return NULL;
// }

DWORD C61850ParseFrameList::Produce(PEPBUFFERPOS pBufferPos)
{
	ASSERT (FALSE);
	return 0;
}

long match_61850(BYTE *pBuffer, long nLen)
{
	EPBUFFERPOS buf_pos;
	memset(&buf_pos, 0, sizeof(EPBUFFERPOS));
	buf_pos.pBuffer = pBuffer;
	buf_pos.nBufLength = nLen;
	PETHER_HEADER pHeader = (PETHER_HEADER)pBuffer;
    unsigned short EtherType = pHeader->ether_type;

	Ep_OffsetBufferCurr(&buf_pos, 14);//sizeof(ETHER_HEADER));

	//memcpy(pItemData->addr_61850.srcMac, pHeader->ether_shost, 6);
	//memcpy(pItemData->addr_61850.dstMac, pHeader->ether_dhost, 6);

	//2020-06-27 lijunqing
	//memcpy(pBufferPos->pDatas->srcMAC, pHeader->ether_shost, 6);
	//memcpy(pBufferPos->pDatas->destMAC, pHeader->ether_dhost, 6);

	//判断是否存在优先级标志
	if (EtherType == 0x0081)	//存在优先级标志
	{
		//yyj 
		Ep_OffsetBufferCurr(&buf_pos, -2);
		WORD wTPID = Ep_BufferReadWord2(&buf_pos);
		WORD wTCI = Ep_BufferReadWord2(&buf_pos);
		EtherType = Ep_BufferReadWord(&buf_pos);
	}
	else
	{

	}

	//APPID
	Ep_BufferReadWord2(&buf_pos);
	//pItemData->addr_61850.APPID = nAPPID;
	//pBufferPos->pDatas->APPID = nAPPID;   //2020-06-27 lijunqing

	//Length
	WORD nLength = Ep_BufferReadWord2(&buf_pos);
	WORD wReserve1 = Ep_BufferReadWord(&buf_pos);
	WORD wReserve2 = Ep_BufferReadWord(&buf_pos);

	if(EtherType==0xBA88)
	{
		BYTE byteType = Ep_BufferReadByte(&buf_pos);

		if(byteType == 0x60)
		{
			long nLen = pkg_61850_read_length(&buf_pos);
			Ep_OffsetBufferCurr(&buf_pos, nLen);

			return buf_pos.nIndex;
		}

		if(byteType==0x80)
		{
			long nLen = pkg_61850_read_length(&buf_pos);
			Ep_OffsetBufferCurr(&buf_pos, nLen);

			return buf_pos.nIndex;
		}

		return 0;
	}

	if(EtherType==0xB888)
	{
		BYTE byteType = Ep_BufferReadByte(&buf_pos);

		if(byteType==0x61)
		{
			long nLen = pkg_61850_read_length(&buf_pos);
			Ep_OffsetBufferCurr(&buf_pos, nLen);

			return buf_pos.nIndex;
		}
	}

	return 0;
}

