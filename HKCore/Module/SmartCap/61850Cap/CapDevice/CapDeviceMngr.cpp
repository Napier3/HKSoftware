//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceMngr.cpp  CCapDeviceMngr


#include "stdafx.h"
#include "CapDeviceMngr.h"

#include "CapDevice91.h"
#include "CapDevice92.h"
#include "CapDevice6044.h"
#include "CapDeviceGoose.h"

#include "../../../../SttStudio/Module/SttGlobalDef.h"

CXWndInterface *g_theCapDeviceMngrMsgRcvWnd = NULL;

CCapDeviceMngr::CCapDeviceMngr()
{
	//初始化属性
	m_pRecordTest = NULL;
	m_nTimeDataCh = 0;
	m_oTimeDataList.AllocMemBuffer(PKG_TIMEDATA_MEMBUFFER_MAX_NUM);

	//初始化成员变量

}

CCapDeviceMngr::~CCapDeviceMngr()
{
	m_oTimeDataList.FreeMemBuffer();
}


//2022-4-14  lijunqing
void CCapDeviceMngr::GetSttCapParas(CCapDeviceBase *pCapDeviceBase, CDataGroup *pSttParas, BOOL bUseSmv, 
									BOOL bUseGoose,BOOL bUseFT3)
{
	if (pCapDeviceBase->m_nType == PROTOCOL_61850_TYPE_GOOSE)
	{
		if (!bUseGoose)
		{
			return;
		}
	}
	else if (pCapDeviceBase->m_nType == PROTOCOL_61850_TYPE_6044)
	{
		if (!bUseFT3)
		{
			return;
		}
	}
	else
	{
		if (!bUseSmv)
		{
			return;
		}
	}

	if (pCapDeviceBase->m_bSelect == 0)
	{
		return;
	}

	pCapDeviceBase->GetSttCapParas(pSttParas);
}

void CCapDeviceMngr::GetSttCapParas(CDataGroup *pSttParas, BOOL bUseSmv, BOOL bUseGoose,BOOL bUseFT3)
{
	POS pos = GetHeadPosition();
	CCapDeviceBase *pCapDeviceBase = NULL;

	while (pos != NULL)
	{
		pCapDeviceBase = (CCapDeviceBase *)GetNext(pos);
		GetSttCapParas(pCapDeviceBase, pSttParas, bUseSmv, bUseGoose,bUseFT3);
	}

    //整理控制块Group的ID：Subscribe0, Subscribe1, ...
    pos = pSttParas->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    long nIndex = 0;

    while(pos != NULL)
    {
        pObj = pSttParas->GetNext(pos);

        if(pObj->GetClassID() != DTMCLASSID_CDATAGROUP)
        {
            continue;
        }

        pObj->m_strID.Format(_T("Subscribe%d"), nIndex);
        //pObj->m_strName = pObj->m_strID;
        nIndex++;
    }
}

void CCapDeviceMngr::UnselectAllCap(BOOL bSmv, BOOL bGoose,BOOL bFT3)
{
	POS pos = GetHeadPosition();
	CCapDeviceBase *pCapDeviceBase = NULL;

	while (pos != NULL)
	{
		pCapDeviceBase = (CCapDeviceBase *)GetNext(pos);

		if ((pCapDeviceBase->m_nType == PROTOCOL_61850_TYPE_92)&&(bSmv))
		{
			pCapDeviceBase->m_bSelect = 0;
		}
		else if ((pCapDeviceBase->m_nType == PROTOCOL_61850_TYPE_GOOSE)&&(bGoose))
		{
			pCapDeviceBase->m_bSelect = 0;
		}
		else if ((pCapDeviceBase->m_nType == PROTOCOL_61850_TYPE_6044)&&(bFT3))
		{
			pCapDeviceBase->m_bSelect = 0;
		}
	}
}

BOOL CCapDeviceMngr::IsFT3Rcd()
{
	POS pos = GetHeadPosition();
	CCapDeviceBase *pCapDeviceBase = NULL;

	while (pos != NULL)
	{
		pCapDeviceBase = (CCapDeviceBase *)GetNext(pos);

		if (!pCapDeviceBase->m_bSelect)
		{
			continue;
		}

		if (pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			return TRUE;
		}
	}

	return FALSE;
}

// void CCapDeviceMngr::UpdateSeletStateAllCap(BOOL bSmv92Sel, BOOL bGooseSel,BOOL bFT3_Sel)
// {
// 	POS pos = GetHeadPosition();
// 	CCapDeviceBase *pCapDeviceBase = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pCapDeviceBase = (CCapDeviceBase *)GetNext(pos);
// 
// 		if (pCapDeviceBase->m_nType == PROTOCOL_61850_TYPE_92)
// 		{
// 			pCapDeviceBase->m_bSelect = bSmv92Sel;
// 		}
// 		else if (pCapDeviceBase->m_nType == PROTOCOL_61850_TYPE_GOOSE)
// 		{
// 			pCapDeviceBase->m_bSelect = bGooseSel;
// 		}
// 		else if (pCapDeviceBase->m_nType == PROTOCOL_61850_TYPE_6044)
// 		{
// 			pCapDeviceBase->m_bSelect = bFT3_Sel;
// 		}
// 	}
// }

CCapDeviceBase* CCapDeviceMngr::FindCapDevice(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT)
{
	CCapDeviceBase *p = NULL;
	CCapDeviceBase *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		if (p->Compare(pDstMac, pSrcMac, APPID, nCMT))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CCapDeviceBase* CCapDeviceMngr::FindCapDevice(UINT nAppID, const CString &strDetectPkgType
											  ,long nPort)
{
	long nPkgClassID = 0;
	CCapDeviceBase *p = NULL;
	CCapDeviceBase *pFind = NULL;

	if (strDetectPkgType == XPARA_ID_TYPE_SMV92)
	{
		nPkgClassID = CPDCLASSID_DEVICE92;
	}
	else if (strDetectPkgType == XPARA_ID_TYPE_SMV91)
	{
		nPkgClassID = CPDCLASSID_DEVICE91;
	}
	else if (strDetectPkgType == XPARA_ID_TYPE_FT3)
	{
		nPkgClassID = CPDCLASSID_DEVICE6044;
	}
	else if (strDetectPkgType == XPARA_ID_TYPE_GOOSE)
	{
		nPkgClassID = CPDCLASSID_DEVICEGOOSE;
	}

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		//如果报文类型不一致,则忽略
		if (p->GetClassID() != nPkgClassID)
		{
			continue;
		}

		//对于FT3报文,只需要光口号一致
		if (p->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			if (p->m_nFiberIndex == nPort)
			{
				pFind = p;
				break;
			}
		}
		else if (p->m_dwAppID == nAppID)//9-2及GOOSE报文判别AppID
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

//2022-5-26 
CCapDeviceBase* CCapDeviceMngr::FindCapDevice(CDvmDataset *pDataset)
{
	CCapDeviceBase *p = NULL;
	CCapDeviceBase *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		if (p->GetDvmDataset() == pDataset)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

long CCapDeviceMngr::GetDeviceCount(long nClassID)
{
	long nCount = 0;

	CCapDeviceBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		if (p->GetClassID() == nClassID)
		{
			nCount++;
		}
	}


	return nCount;
}

CCapDeviceBase* CCapDeviceMngr::FindCapDevice(CDataGroup *pSttIecCb)
{
	long nAppID = 0,nPort = 0;
	CString strType;

	stt_GetDataValueByID(pSttIecCb, XPARA_ID_APPID, nAppID);
	stt_GetDataValueByID(pSttIecCb, XPARA_ID_Type, strType);
	stt_GetDataValueByID(pSttIecCb, XPARA_ID_Port, nPort);
	return FindCapDevice(nAppID,strType,nPort);
}

CCapDeviceBase* CCapDeviceMngr::AddCapDevice(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT)
{
	CCapDeviceBase *pNew = NULL;

	switch (nCMT)
	{
	case PROTOCOL_61850_TYPE_91:
		pNew = new CCapDevice91();
		break;
	case PROTOCOL_61850_TYPE_92:
		pNew = new CCapDevice92();
		break;
	case PROTOCOL_61850_TYPE_GOOSE:
		pNew = new CCapDeviceGoose();
		break;
	case PROTOCOL_61850_TYPE_60448:
		pNew = new CCapDevice6044();
		break;
	default:
		break;
	}

	return pNew;
}



CCapDeviceBase* CCapDeviceMngr::FindCapDevice(PEPCAPBUFFERITEM pItemData)
{
	CCapDeviceBase *p = NULL;
	CCapDeviceBase *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		if (p->Compare(pItemData))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CCapDeviceBase* CCapDeviceMngr::AddCapDevice(PEPCAPBUFFERITEM pItemData)
{
	CCapDeviceBase *pNew = NULL;

	switch (pItemData->nProtocol)
	{
	case PROTOCOL_61850_TYPE_91:
		pNew = new CCapDevice91();
		AddNewChild(pNew);
		pNew->Iinit(pItemData);
		break;
	case PROTOCOL_61850_TYPE_92:
		pNew = new CCapDevice92();
		AddNewChild(pNew);
		pNew->Iinit(pItemData);
		break;
	case PROTOCOL_61850_TYPE_GOOSE:
		pNew = new CCapDeviceGoose();
		AddNewChild(pNew);
		pNew->Iinit(pItemData);
		break;
	case PROTOCOL_61850_TYPE_60448:
		pNew = new CCapDevice6044();
		AddNewChild(pNew);
		pNew->Iinit(pItemData);
		break;
	default:
		break;
	}

	InitNameAndID(pNew);

	return pNew;
}

void CCapDeviceMngr::InitNameAndID(CCapDeviceBase *pCapDevice)
{
	if (pCapDevice == NULL)
	{
		return;
	}

	CCapDeviceBase *p = NULL;
	POS pos = GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		if (p->IsSameType(pCapDevice->m_nType))
		{
			nIndex++;
		}
	}

	pCapDevice->InitNameAndID(nIndex);
}

CCapDeviceBase* CCapDeviceMngr::AddCapDevice(CDataGroup *pSttIecCb)
{
	CString strType, strCRC, strPkgDetect,strSTMode;
	long nPort = 0 , nAppID = 0, nChCount = 0;  //2022-12-25  lijunqing 没有初始化，调试的时候导致通道数没定义，为随机数
	long nSmpRate = 0,nPkgLenth = 0;
	double dBaudRate = 0.0f;//2.5M为整数
	strSTMode = "FT3";

	stt_GetDataValueByID(pSttIecCb, XPARA_ID_APPID, nAppID);
	stt_GetDataValueByID(pSttIecCb, XPARA_ID_Type, strType);
	stt_GetDataValueByID(pSttIecCb, XPARA_ID_Port, nPort);
	stt_GetDataValueByID(pSttIecCb, XPARA_ID_CRC, strCRC);
	stt_GetDataValueByID(pSttIecCb, XPARA_ID_PkgDetect, strPkgDetect);
	stt_GetDataValueByID(pSttIecCb, XPARA_ID_ChCount, nChCount);
	stt_GetDataValueByID(pSttIecCb, XPARA_ID_SampleRate, nSmpRate);
	stt_GetDataValueByID(pSttIecCb, XPARA_ID_BaudRate, dBaudRate);
	stt_GetDataValueByID(pSttIecCb, XPARA_ID_OnePkgLen, nPkgLenth);
	stt_GetDataValueByID(pSttIecCb, XPARA_ID_STMode, strSTMode);

	//2022-6-11 lijunqing  如果通道数为0，则忽略此控制块。这样方便系统处理
	if ((nChCount <= 0)&&(strType != XPARA_ID_TYPE_FT3))//非FT3并且通道数为0,则忽略
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("IecCb: [%s] [%04X] ChCount==0"), strType.GetString(), nAppID);
		return NULL;
	}

	CCapDeviceBase *pNew = FindCapDevice(nAppID,strType,nPort);

	if (pNew != NULL)//20220609 zhouhj  需要AppID结合报文类型一起判断
	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("(Modify)strCRC=%s,%s;strPkgDetect=%s,%s;nPort=%d,%d;"),pNew->m_strCRC.GetString(),strCRC.GetString(),
// 			pNew->m_strPkgDetect.GetString(),strPkgDetect.GetString(),pNew->m_nFiberIndex,nPort);
		pNew->m_strCRC = strCRC;
		pNew->m_strPkgDetect = strPkgDetect;
		pNew->m_nFiberIndex = nPort;

		if (pNew->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			CCapDevice6044 *pCapDevice6044 = (CCapDevice6044*)pNew;
			pCapDevice6044->m_nSmpRate = nSmpRate;
			pCapDevice6044->m_nPkgLenth = nPkgLenth;
			pCapDevice6044->m_nPkgDatasLenth = nPkgLenth;
			pCapDevice6044->m_dBaudRate = dBaudRate;
			pCapDevice6044->m_strSTMode = strSTMode;
		}

		return NULL;//如果查找成功返回空,未创建信息的Device
	}
	
	if (strType == XPARA_ID_TYPE_SMV91)
	{
		pNew = new CCapDevice91();
		pNew->m_nType = PROTOCOL_61850_TYPE_91;
	}
	else if (strType == XPARA_ID_TYPE_SMV92)
	{
		pNew = new CCapDevice92();
		pNew->m_nType = PROTOCOL_61850_TYPE_92;
	}
	else if (strType == XPARA_ID_TYPE_GOOSE)
	{
		pNew = new CCapDeviceGoose();
		pNew->m_nType = PROTOCOL_61850_TYPE_GOOSE;
	}
	else if (strType == XPARA_ID_TYPE_FT3)
	{
		CCapDevice6044 *pCapDevice6044 = new CCapDevice6044();
		pNew = pCapDevice6044;
		pCapDevice6044->m_nSmpRate = nSmpRate;
		pCapDevice6044->m_nPkgLenth = nPkgLenth;
		pCapDevice6044->m_nPkgDatasLenth = nPkgLenth;
		pCapDevice6044->m_dBaudRate = dBaudRate;
		pCapDevice6044->m_strSTMode = strSTMode;
		pNew->m_nType = PROTOCOL_61850_TYPE_60448;
	}

	if (pNew != NULL)
	{
		pNew->m_dwAppID = nAppID;
		pNew->m_strCRC = strCRC;
		pNew->m_strPkgDetect = strPkgDetect;
		pNew->m_nFiberIndex = nPort;
		AddNewChild(pNew);
		InitNameAndID(pNew);
		pNew->SetChannelNum(nChCount);

// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("(New)m_dwAppID=0x%04X;strCRC=%s;strPkgDetect=%s;nPort=%d;"),pNew->m_dwAppID,pNew->m_strCRC.GetString(),
// 			pNew->m_strPkgDetect.GetString(),pNew->m_nFiberIndex);
	}

	return pNew;
}

void CCapDeviceMngr::Reset()
{
	CCapDeviceBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);
		p->Reset();
	}
}

long CCapDeviceMngr::GetSmpRate_FT3()
{
	CCapDeviceBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		if (!p->m_bSelect)
		{
			continue;
		}

		if (p->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			CCapDevice6044 *pCapDevice6044 = (CCapDevice6044 *)p;
			return pCapDevice6044->m_nSmpRate;
		}
	}

	return 4000;
}

void CCapDeviceMngr::ClearAllIecfgAttach()
{
	CCapDeviceBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);
		p->InitIecfgData(NULL);
	}
}

BOOL CCapDeviceMngr::ValidSelectFT3CB_PkgLenth()
{
	CCapDeviceBase *p = NULL;
	CCapDevice6044 *pCapDevice6044 = NULL;
	CIecCfg6044CommonData *pIecCfg6044CommonData = NULL;
	long nFT3In_PkgLenth = 0;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		if (p->GetClassID() != CPDCLASSID_DEVICE6044)
		{
			continue;
		}

		if (!p->m_bSelect)
		{
			continue;
		}

		pCapDevice6044 = (CCapDevice6044 *)p;
		pIecCfg6044CommonData = (CIecCfg6044CommonData *)pCapDevice6044->GetIecCfgData(); 

		if (pIecCfg6044CommonData== NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前光口(%ld)未配置探测FT3控制块."),pCapDevice6044->m_nFiberIndex + 1);
			return FALSE;
		}

		nFT3In_PkgLenth = pIecCfg6044CommonData->GetPkgLenth();

		if (nFT3In_PkgLenth != pCapDevice6044->m_nPkgLenth)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("光口%ld,FT3订阅界面配置报文长度(%ld)与实际报文长度(%ld)不一致."),
				pCapDevice6044->m_nFiberIndex + 1,nFT3In_PkgLenth,pCapDevice6044->m_nPkgLenth);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CCapDeviceMngr::ValidSelectFT3CB_PkgLenth(long nFt3CrcType)
{
	CCapDeviceBase *p = NULL;
	CCapDevice6044 *pCapDevice6044 = NULL;
	CIecCfg6044CommonData *pIecCfg6044CommonData = NULL;
	long nFT3In_PkgLenth = 0;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		if (p->GetClassID() != CPDCLASSID_DEVICE6044)
		{
			continue;
		}

		if (!p->m_bSelect)
		{
			continue;
		}

		pCapDevice6044 = (CCapDevice6044 *)p;
		pIecCfg6044CommonData = (CIecCfg6044CommonData *)pCapDevice6044->GetIecCfgData(); 

		if (pIecCfg6044CommonData== NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前光口(%ld)未配置探测FT3控制块."),pCapDevice6044->m_nFiberIndex + 1);
			return FALSE;
		}
		
		pCapDevice6044->m_nFt3_CrcType = nFt3CrcType;//20240811 suyang 将CRC赋值给6044中的CRC
		nFT3In_PkgLenth = pIecCfg6044CommonData->GetPkgLenth(nFt3CrcType);
		if (nFT3In_PkgLenth != pCapDevice6044->m_nPkgLenth)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("光口%ld,FT3订阅界面配置报文长度(%ld)与实际报文长度(%ld)不一致."),
				pCapDevice6044->m_nFiberIndex + 1,nFT3In_PkgLenth,pCapDevice6044->m_nPkgLenth);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CCapDeviceMngr::ValidSTMode()
{
	CCapDeviceBase *p = NULL;
	CCapDevice6044 *pCapDevice6044 = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		if (p->GetClassID() != CPDCLASSID_DEVICE6044)
		{
			continue;
		}

		if (!p->m_bSelect)
		{
			continue;
		}

		pCapDevice6044 = (CCapDevice6044 *)p;

		if (pCapDevice6044->m_strSTMode != "FT3")
		{
#ifdef _PSX_QT_LINUX_
			CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("当前接收光口(%ld)配置的模式(%s)非FT3模式,无法进入录波.")
				,pCapDevice6044->m_nFiberIndex + 1,pCapDevice6044->m_strSTMode.GetString());
#else
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前接收光口(%ld)配置的模式(%s)非FT3模式,无法进入录波.")
				,pCapDevice6044->m_nFiberIndex + 1,pCapDevice6044->m_strSTMode.GetString());
#endif
			return FALSE;
		}
	}

	return TRUE;
}

//定期更新装置链接状态  2020-06-27  lijunqing
void CCapDeviceMngr::UpdateDeviceLinkState()
{
	if (m_pRecordTest == NULL)
	{
		return;
	}

	CCapDeviceBase *p = NULL;
	POS pos = GetHeadPosition();
	long nHdIndex = 1;

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);
		
		if (p->IsDataRcvOverTime() && p->m_bLinkState != 0)
		{
			p->m_bLinkState = 0;
			m_pRecordTest->m_pVariables->ResetValuesByHdIndex(nHdIndex);

			if (p->GetClassID() == CPDCLASSID_DEVICE92)
			{
#ifdef _PSX_QT_LINUX_
				CLogPrint::LogFormatString(XLOGLEVEL_ASSIST, _T("SMV控制块(%s)断链."), p->m_strID.GetString());
#else
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("SMV控制块(%s)断链."), p->m_strID.GetString());
#endif
			}
			else if (p->GetClassID() == CPDCLASSID_DEVICEGOOSE)
			{
#ifdef _PSX_QT_LINUX_
				CLogPrint::LogFormatString(XLOGLEVEL_ASSIST, _T("GOOSE控制块(%s)断链."), p->m_strID.GetString());
#else
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("GOOSE控制块(%s)断链."), p->m_strID.GetString());
#endif				
			}
			else if (p->GetClassID() == CPDCLASSID_DEVICE6044)
			{
#ifdef _PSX_QT_LINUX_
				CLogPrint::LogFormatString(XLOGLEVEL_ASSIST, _T("FT3报文(%s)断链."), p->m_strID.GetString());
#else
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("FT3报文(%s)断链."), p->m_strID.GetString());
#endif						
			}
			else
			{
#ifdef _PSX_QT_LINUX_
				CLogPrint::LogFormatString(XLOGLEVEL_ASSIST, _T("%s 断链."), p->m_strID.GetString());
#else
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("%s 断链."), p->m_strID.GetString());
#endif						
			}
		}

		nHdIndex++;
	}
}

void CCapDeviceMngr::SelectDevicesByLink(CExBaseList &list, UINT nClassID, BOOL bLink)
{
	CCapDeviceBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		if (p->GetClassID() != nClassID)
		{
			continue;
		}

		if (p->m_bLinkState == bLink)
		{
			list.AddTail(p);
		}
	}
}

//2022-5-3  lijunqing
void CCapDeviceMngr::ClearCap()
{
	CCapDeviceBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);
		p->ClearCap();

	}		

}


void CCapDeviceMngr::ClearPara()
{
	CCapDeviceBase *p = NULL;
	POS pos = GetHeadPosition();
	long nHdIndex = 1;

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);
		p->m_bLinkState = 0;

		if(m_pRecordTest->m_pVariables)
		{
			m_pRecordTest->m_pVariables->ResetValuesByHdIndex(nHdIndex);
			m_pRecordTest->m_pVariables->ResetValueCal();
		}

		nHdIndex++;
	}
}


//2022-12-25  lijunqing
CCapDeviceBase* CCapDeviceMngr::GetSelectDevice()
{
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		CCapDeviceBase *pCapDevice = (CCapDeviceBase *)GetNext(pos);

		if (pCapDevice->m_bSelect)
		{
			return pCapDevice;
		}
	}

	return NULL;
}

long CCapDeviceMngr::GetSelectDeviceCount(UINT uClassID)
{
	long nCount = 0;

	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		CCapDeviceBase *pCapDevice = (CCapDeviceBase *)GetNext(pos);

		if (pCapDevice->m_bSelect == 0)
		{
			continue;
		}

		if ((uClassID == 0)||(pCapDevice->GetClassID() == uClassID))
		{
			nCount++;
		}
	}

	return nCount;
}

void CCapDeviceMngr::ResetTimeDataList()
{
	m_oTimeDataList.ResetOffsetDataFillBeginPosition();
	m_nTimeDataCh = 0;
}

void CCapDeviceMngr::AddMUTimeData(int nTimeDataCh,__int64 n64TimeData)
{
	if (nTimeDataCh != m_nTimeDataCh)
	{
		ResetTimeDataList();
		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("AddMUTimeData[%d]"),nTimeDataCh);
	}

	m_nTimeDataCh = nTimeDataCh;
	m_oTimeDataList.AppendBuffer(&n64TimeData,1);
}
