#include "StdAfx.h"
#include "EpCapTextFuncs.h"


void EpTxt_GetAddrText(EP_ETHER_CAP_IP cap_ip, CString &strText, BOOL bDest)
{
	if (cap_ip.ip.s_addr == 0)
	{
		if (bDest)
		{
			strText = _T("----");
		}
		else
		{
			if (cap_ip.port > 256)
			{
				strText = _T("----");
			}
			else
			{
				strText.Format(_T("COM%d"), cap_ip.port);
			}
		}
	}
	else
	{
		//ep_GetIpV4_H_L(&cap_ip.ip, strText);
		ep_GetIpV4(&cap_ip.ip, strText);
	}
}

void EpTxt_GetContentText(PEPCAPDBBUFFERINDEX pIndex, CString &strText)
{
	EpTxt_GetContentText(pIndex->nProtocol, -1/*pIndex->oDataHead.nDeviceDataType*/, strText);
// 	WORD nFrameType = (WORD)Ep_GetProtocol_FrameType(pIndex->nProtocol);
// 
// 	if (nFrameType == 0)
// 	{
// 		strText = _T("错误的报文");
// 	}
// 	else if (nFrameType == (EPCLASSID_101_TFRAME_E5 & 0x0FF))
// 	{
// 		strText = _T("无数据时的标准回复");
// 	}
// 	else if (nFrameType == (EPCLASSID_101_TFRAME_10 & 0x0FF))
// 	{
// 		strText = _T("固定长度报文帧");
// 	}
// 	else if (nFrameType == (EPCLASSID_101_TFRAME_10 & 0x0FF))
// 	{
// 		strText = _T("固定长度报文帧");
// 	}
// 	else if (nFrameType == (EPCLASSID_104_TFRAME_68_S & 0x0FF))
// 	{
// 		strText = _T("S格式报文");
// 	}
// 	else if (nFrameType == (EPCLASSID_104_TFRAME_68_U & 0x0FF))
// 	{
// 		strText = _T("U格式报文");
// 	}
// 	else
// 	{
// 		switch (pIndex->oDataHead.nDeviceDataType)
// 		{
// 		case EP_DEVICE_DATA_YC:
// 			strText = _T("遥测报文");
// 			break;
// 		case EP_DEVICE_DATA_YX:
// 			strText = _T("遥信报文");
// 			break;
// 		case EP_DEVICE_DATA_YT:
// 			strText = _T("遥调报文");
// 			break;
// 		case EP_DEVICE_DATA_EMPTY:
// 			strText = _T("");
// 			break;
// 		case EP_DEVICE_DATA_YK:
// 			strText = _T("遥控报文");
// 			break;
// 		case EP_DEVICE_DATA_TSYN:
// 			strText = _T("对时报文");
// 			break;
// 		}
// 
// 		strText.AppendFormat(_T("(ASDU %02X)"), Ep_GetProtocol_FrameType(pIndex->nProtocol));
// 	}
}


void EpTxt_GetContentText(DWORD nProtocol, WORD nDeviceDataType, CString &strText)
{
	WORD nFrameType = (WORD)Ep_GetProtocol_FrameType(nProtocol);
	WORD nProto = (WORD)Ep_GetProtocol_ProtoType(nProtocol);

	if (nProto == EPPROTOCOL_NONE)
	{
		strText = _T("网络报文");
		return;
	}

	WORD nCapType = (WORD)Ep_GetProtocol_CapType(nProtocol);

	

	if (nFrameType == 0)
	{
		if (nCapType != EP_CAP_CHTYPE_SERIAL)
		{
			strText = _T("网络报文");
		}
		else
		{
			strText = _T("错误的报文");
		}
	}
	else if (nFrameType == (EPCLASSID_101_TFRAME_E5 & 0x0FF))
	{
		strText = _T("无数据时的标准回复");
	}
	else if (nFrameType == (EPCLASSID_101_TFRAME_10 & 0x0FF))
	{
		strText = _T("固定长度报文帧");
	}
	else if (nFrameType == (EPCLASSID_101_TFRAME_10 & 0x0FF))
	{
		strText = _T("固定长度报文帧");
	}
	else if (nFrameType == (EPCLASSID_104_TFRAME_68_S & 0x0FF))
	{
		strText = _T("S格式报文");
	}
	else if (nFrameType == (EPCLASSID_104_TFRAME_68_U & 0x0FF))
	{
		strText = _T("U格式报文");
	}
	else
	{
		UINT nDeviceDataType = Ep_GetProtocol_FrameType(nProtocol);
// 		switch (nDeviceDataType)
// 		{
// 		case EP_DEVICE_DATA_YC:
// 			strText = _T("遥测报文");
// 			break;
// 		case EP_DEVICE_DATA_YX:
// 			strText = _T("遥信报文");
// 			break;
// 		case EP_DEVICE_DATA_YT:
// 			strText = _T("遥调报文");
// 			break;
// 		case EP_DEVICE_DATA_EMPTY:
// 			strText = _T("");
// 			break;
// 		case EP_DEVICE_DATA_YK:
// 			strText = _T("遥控报文");
// 			break;
// 		case EP_DEVICE_DATA_TSYN:
// 			strText = _T("对时报文");
// 			break;
// 		}

		strText.Format(_T("(ASDU %02X)"), nDeviceDataType);
	}

// 	nFrameType = Ep_GetProtocol_CapType(nProtocol);
// 
// 	if (EP_CAP_CHTYPE_TCP == nFrameType)
// 	{
// 		strText += _T(" (TCP)");
// 	}
// 	else if (EP_CAP_CHTYPE_UDP == nFrameType)
// 	{
// 		strText += _T(" (UDP)");
// 	}
// 	else
// 	{
// 		strText += _T(" (?)");
// 	}

}

BOOL EpTxt_GetItemTextBuffer(CCapSmDb *pCapSmDb, CEpCapDbBufferIndex *pDbIndex,CString &strText)
{
	BYTE *pBuffer = pDbIndex->GetBuffer();
	long nLen = pDbIndex->m_oEpCapBufferIndex.nFrameLen;//pDbIndex->GetBufferLength();

	if (pBuffer == NULL)
	{
		if (pCapSmDb != NULL)
		{
			pCapSmDb->ReadCapBuffer(&(pDbIndex->m_oEpCapBufferIndex), &(pDbIndex->m_oBuffer) );
			pBuffer = pDbIndex->GetBuffer();
			nLen = pDbIndex->m_oEpCapBufferIndex.nFrameLen;//pDbIndex->GetBufferLength();
		}
	}

	if (pBuffer == NULL)
	{
		strText = _T("Error......");
		return FALSE;
	}

	EpTxt_GetItemTextBuffer(pBuffer, nLen, strText);
// 	if (nLen  == 0)
// 	{
// 		strText += _T("......");
// 	}
// 	else
// 	{
// 		CBinaryTextConvert oConvert;
// 		long nIndex = 0;
// 		char pText[4];
// 		pText[3] = 0;
// 
// 		for (nIndex=0; nIndex<nLen; nIndex++)
// 		{
// 			CBinaryTextConvert::ValueToString_Hex(*(pBuffer+nIndex), (BYTE*)pText);
// 			strText += pText;
// 		}
// 	}

	return TRUE;
}

BOOL EpTxt_GetItemTextBuffer(BYTE *pBuffer, long nLen, CString &strText)
{
	if (pBuffer == NULL)
	{
		strText = _T("Error......");
		return FALSE;
	}

	if (nLen  == 0)
	{
		strText += _T("......");
	}
	else
	{
		if (nLen > 64)
		{
			nLen = 64;
		}

		CBinaryTextConvert oConvert;
		long nIndex = 0;
		char pText[4];
		pText[3] = 0;

		for (nIndex=0; nIndex<nLen; nIndex++)
		{
			CBinaryTextConvert::ValueToString_Hex(*(pBuffer+nIndex), (BYTE*)pText);
			strText += pText;
		}
	}

	return TRUE;
}

#ifdef _MonitorQueryConfig_H__

void EpTxt_GetDir(CMonitorQueryConfig *pCapConfig, EP_ETHER_CAP_IP cap_ip, CString &strText)
{
	long nDir = -1;

// 	if (cap_ip.ip.s_addr == 0)
// 	{
// 		CEmcSerialConfig *pSerial = pCapConfig->m_pEmcSerialsConfig->FindByPort(cap_ip.port);
// 		if (pSerial != NULL)
// 		{
// 			nDir = pSerial->m_nDir;
// 		}
// 	}
// 	else
	{
		CString strIP;
		ep_GetIpV4(&cap_ip.ip, strIP);
		CEmcNetConfig *pNet = (CEmcNetConfig*)pCapConfig->m_pEmcNetsConfig->FindByID(strIP);
		if (pNet != NULL)
		{
			nDir = pNet->m_nDir;
		}
	}

	if (nDir == -1)
	{
		strText = _T("------");
	}
	else
	{
		strText = Ep_GetProtocolDir(nDir);
	}
}
#endif


CString EpTxt_GetCapFrameTitle(long nCol)
{
	switch (nCol)
	{
	case EPCAP_QUERYFRAME_COL_INDEX:
		return _T("编号");
	case EPCAP_QUERYFRAME_COL_TIME:
		return _T("时间");
	case EPCAP_QUERYFRAME_COL_SRCADDR:
		return _T("源地址");
	case EPCAP_QUERYFRAME_COL_DESTADDR:
		return _T("目标地址");
	case EPCAP_QUERYFRAME_COL_DIR:
		return _T("报文方向");
	case EPCAP_QUERYFRAME_COL_FRAME_DESC:
		return _T("报文内容");
	case EPCAP_QUERYFRAME_COL_FRAME_TEXT:
		return _T("报文信息");
	case EPCAP_QUERYFRAME_COL_CAPID:
		return _T("CAPID");
	default:
		return _T("");
	}
}

