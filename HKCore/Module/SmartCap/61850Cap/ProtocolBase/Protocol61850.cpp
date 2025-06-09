// EpProtocolBas.cpp: implementation of the CProtocol61850 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Protocol61850.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProtocol61850::CProtocol61850()
{ 
	m_pParseFrames = new C61850ParseFrameList();
	AddNewChild(m_pParseFrames);

	m_strName = _T("61850");
	m_strID = m_strName;
	m_pCapDeviceMngr = NULL;
}

CProtocol61850::~CProtocol61850()
{

}

CExBaseObject* CProtocol61850::Parse(CFrameMemBuffer *pBuffer, CFrameDetail *pDetailList, DWORD dwPara)
{
	InitBufPos();
	m_bufPos.dwPara = dwPara;
	pBuffer->GetBufferPos(m_bufPos);
	m_bufPos.pItemData = &pBuffer->m_oCapBufferItem;  //抓包的报文头
	CExBaseObject *p = NULL;

	//2020-4-11  lijq：考虑多帧报文粘贴在一起的情况
	while (m_bufPos.nFrameCurr < m_bufPos.nBufLength)
	{
		p = m_pParseFrames->Parse(&m_bufPos, pDetailList);

		if (p != NULL)
		{
			AddCapDevice(&pBuffer->m_oCapBufferItem, pBuffer, p);
		}

		if (p == NULL)
		{
			m_bufPos.nFrameCurr++;
		}
	}

	pBuffer->Ebs_SetParsed();

	return p;
}

CExBaseObject* CProtocol61850::Parse(CFrameMemBuffer *pBuffer, DWORD dwPara)
{
	InitBufPos();
	m_bufPos.dwPara = dwPara;
	pBuffer->GetBufferPos(m_bufPos);
	m_bufPos.pItemData = &pBuffer->m_oCapBufferItem; //抓包的报文头
	CExBaseObject *p = NULL;
	m_oCapParseDatas.n64Time = pBuffer->m_n64TimeSnamp; //报文的时间作为数据的时间
	int nPkgType = (pBuffer->m_nFiberAndPkgType&0xFF)/0x10;

	//2020-4-11  lijq：考虑多帧报文粘贴在一起的情况
	//while (m_bufPos.nFrameCurr < m_bufPos.nBufLength)  //2020-06-23  只考虑一帧报文的情况
	{
		if (nPkgType == Protocol61850_Pkg_Type_FT3)//该类型为3代表为FT3报文,调用FT3报文解析函数
		{
			p = m_pParseFrames->Parse_60044(&m_bufPos);
			pBuffer->m_oCapBufferItem.addr_61850.APPID = (pBuffer->m_nFiberAndPkgType&0xFF)%0x10;
		} 
		else if (nPkgType == Protocol61850_Pkg_Type_MUTIMEDATA)//该类型为3代表为FT3报文,调用FT3报文解析函数
		{
			if (m_pCapDeviceMngr != NULL)
			{
				long nTimeDataCh = pBuffer->m_nFiberAndPkgType>>16;
				m_pCapDeviceMngr->AddMUTimeData(nTimeDataCh,pBuffer->m_n64TimeSnamp);
			}
		}
		else
		{
			p = m_pParseFrames->Parse(&m_bufPos);
		}

		if (m_bufPos.pDatas->nParseState < 0)
		{
			m_bufPos.pDatas->dwDatas = 0;

            long nMax = sizeof(EP92PARSEDATA);
            if (nMax < sizeof(EPGOOSEPARSEDATA))
            {
                nMax = sizeof(EPGOOSEPARSEDATA);
            }

			ZeroMemory(&m_bufPos.pDatas->oData92, nMax);
		}

		if (p != NULL)
		{
			AddCapDevice(&pBuffer->m_oCapBufferItem, pBuffer, p);
		}

		if (p == NULL || m_bufPos.pDatas->nParseState < 0)
		{//报文出错，直接退出
			//CLogPrint::LogBuffer(m_bufPos.pBuffer, 0, m_bufPos.nBufLength);
			//break;  //2020-06-23  只考虑一帧报文的情况
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error Package [%d] byte...."), m_bufPos.nBufLength);//chenling20240201 测试提减少打印信息，后面调试放出即可
		}
	}

	pBuffer->Ebs_SetParsed();

	return p;
}

CExBaseObject* CProtocol61850::Parse(CXSmMemBuffer *pBuffer, DWORD dwPara)
{
	return Parse((CFrameMemBuffer*)pBuffer, dwPara);
}

void CProtocol61850::AddCapDevice(PEPCAPBUFFERITEM pItemData, CFrameMemBuffer *pBuffer, CExBaseObject *pFrame)
{
	CCapDeviceBase *pDevice = m_pCapDeviceMngr->FindCapDevice(pItemData);

	if (pDevice == NULL)
	{
		pDevice = m_pCapDeviceMngr->AddCapDevice(pItemData);
		long nLen = pBuffer->GetBufferLength();//GetDataLength();
		BYTE *pData = pBuffer->GetBuffer();
		pDevice->m_oBuffer.SetBuffer(pData, nLen);
		pDevice->m_nMatchState = MATCH_STATE_SURPLUS;
		pDevice->SetChannelNum(pItemData->nChCount);
		pDevice->InitDevice(&m_oCapParseDatas);
		pDevice->ParseDeviceInfor();
		pDevice->SetChannelState(&m_oCapParseDatas);

		if (g_theCapDeviceMngrMsgRcvWnd != NULL)
		{
			g_theCapDeviceMngrMsgRcvWnd->XPostMessage(WM_ADDCAPDEVICE, (WPARAM)pDevice, (LPARAM)pDevice);
		}
	}
	else
	{
		if (pDevice->m_nMatchState == MATCH_STATE_NONE)
		{
			pDevice->m_nMatchState = MATCH_STATE_SUCCESS;

			//FT3报文中不包含通道相关信息,故不需要更新
			if (pDevice->GetClassID() == CPDCLASSID_DEVICE6044)
			{
				pDevice->SetChannelState(&m_oCapParseDatas);
			}
			else
			{
				pDevice->SetChannelNum(pItemData->nChCount);
				pDevice->SetChannelState(&m_oCapParseDatas);
				pDevice->InitDevice(&m_oCapParseDatas);
			}
			

			if (g_theCapDeviceMngrMsgRcvWnd != NULL)
			{
				g_theCapDeviceMngrMsgRcvWnd->XPostMessage(WM_UPDATECAPDEVICE, (WPARAM)pDevice, (LPARAM)pDevice);
			}
		}
		
       pDevice->AddCapDataBuffer(&m_oCapParseDatas,pBuffer->GetBuffer(),pBuffer->GetBufferLength());
	}
}
