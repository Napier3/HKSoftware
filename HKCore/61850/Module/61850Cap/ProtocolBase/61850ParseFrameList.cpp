// 61850ParseFrameList.cpp: implementation of the C61850ParseFrameList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "61850ParseFrameList.h"
#include "..\EthernetCapGlobalDef.h"
#include "..\CapDevice\CapDeviceGlobal.h"

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
}

C61850ParseFrameList::~C61850ParseFrameList()
{

}

CFrameBase* C61850ParseFrameList::Parse(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList)
{
	BYTE *pBuffer = Ep_GetBufferCurr(pBufferPos);

	PEPCAPBUFFERITEM pItemData = (PEPCAPBUFFERITEM)pBufferPos->pItemData;
	PETHER_HEADER pHeader = (PETHER_HEADER)pBuffer;
	UINT16 EtherType = pHeader->ether_type;
	u_short nAPPID = 0;
	Ep_OffsetBufferCurr(pBufferPos, 14);//sizeof(ETHER_HEADER));

	if (pDetailList!= NULL)
	{
		pDetailList->AddByteBlockByValue_MAC(_T("源MAC"), pHeader->ether_shost, 0);
		pDetailList->AddByteBlockByValue_MAC(_T("目标MAC"), pHeader->ether_dhost, 6);
	}

	memcpy(pItemData->addr_61850.srcMac, pHeader->ether_shost, 6);
	memcpy(pItemData->addr_61850.dstMac, pHeader->ether_dhost, 6);

	//判断是否存在优先级标志
	if (EtherType == 0x0081)	//存在优先级标志
	{
		if (pDetailList!= NULL)
		{
			pDetailList->AddByteBlockByValue(_T("优先级标志"), EtherType, 12);
		}

		if(Ep_IsBufferEnough(pBufferPos, 18))
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
			m_p92Frame->ParseOwn(pBufferPos, pDetailList);

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
			m_p91Frame->ParseOwn(pBufferPos, pDetailList);

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
			m_pGooseFrame->ParseOwn(pBufferPos, pDetailList);
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
	UINT16 EtherType = pHeader->ether_type;
	u_short nAPPID = 0;
	Ep_OffsetBufferCurr(pBufferPos, 14);//sizeof(ETHER_HEADER));

	//判断是否存在优先级标志
	if (EtherType == 0x0081)	//存在优先级标志
	{
		if(Ep_IsBufferEnough(pBufferPos, 18))
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
	UINT16 EtherType = pHeader->ether_type;
	u_short nAPPID = 0;
	Ep_OffsetBufferCurr(pBufferPos, 14);//sizeof(ETHER_HEADER));

	memcpy(pItemData->addr_61850.srcMac, pHeader->ether_shost, 6);
	memcpy(pItemData->addr_61850.dstMac, pHeader->ether_dhost, 6);

	//判断是否存在优先级标志
	if (EtherType == 0x0081)	//存在优先级标志
	{
		if(Ep_IsBufferEnough(pBufferPos, 18))
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
			m_p92Frame->ParseOwn(pBufferPos);

			return m_p92Frame;
		}

		if(byteType==0x80)
		{
			pItemData->nProtocol = PROTOCOL_61850_TYPE_91;
			m_p91Frame->ParseOwn(pBufferPos);

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
			m_pGooseFrame->ParseOwn(pBufferPos);
			return m_pGooseFrame;
		}
	}

	return NULL;
}

CFrameBase* C61850ParseFrameList::Match(PEPBUFFERPOS pBufferPos)
{
	

	return NULL;
}

DWORD C61850ParseFrameList::Produce(PEPBUFFERPOS pBufferPos)
{
	ASSERT (FALSE);
	return 0;
}

