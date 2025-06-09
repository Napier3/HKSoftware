//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceBase.cpp  CCapDeviceBase


#include "stdafx.h"
#include "CapDeviceBase.h"
#include "../ProtocolBase/61850ParseFrameList.h"

extern BOOL g_bSmartCap_RecordNow; 
BOOL _CAL_DELAY_TIME_USE_SAMPLECOUNT_ = FALSE;

CExBaseCycleArray *g_pSmartCapSoeCycleArray = NULL;
CExBaseCycleArray *g_pSmartCapBinCycleArray = NULL;

CCapDeviceBase::CCapDeviceBase()
{
	ZeroMemory(&m_oPrevDatas, sizeof(EPCAPPARSEDATAS));
	ZeroMemory(&m_oAnalysisResults, sizeof(EP_ANALYSIS_RESULT));
	m_nCurrErrorTypeNum = 0;

	//初始化属性
	ZeroMemory(m_byteDestMac, 6);
	ZeroMemory(m_byteSrcMac,6);
	m_dwAppID = 0;
	m_nType = 0;
	m_bLinkState = 0;

	//初始化成员变量
	m_pDeviceInforFrame = NULL;
	m_n64CapDataIndex = 0;
	m_bSelect = 0;

	m_nFillBeginPos = 0;;
	m_nDatasCount = 0;

	m_nFiberIndex = 0;
	m_pIecCfgData = NULL;
	m_nMatchState = MATCH_STATE_NONE;

	::memset(m_dwFlagSVCstc,  0x0,  STCAPPARSE_CONSISTENCY_COUNT * sizeof(DWORD));	
	::memset(m_dwFlagGSCstc,  0x0,  STCAPPARSE_CONSISTENCY_COUNT * sizeof(DWORD));

	::memset(m_destIn, 0x0, 100);
	::memset(m_destOut, 0x0, 50);
	m_dMaxTimeDiscrete = 0;
	m_pRefDvmDataset = NULL;

	for (int i = 0; i < 256;i++)
	{
		m_dTime1[i]  = 0;
		m_dTime2[i]  = 0;
	}
}

CCapDeviceBase::~CCapDeviceBase()
{
}

#include "../../../../SttStudio/Module/SttGlobalDef.h"
/*
<macro type="relay" name="IEC订阅" id="IecRecord">
	<fault-paras-ex name="" id="">
		<data name="使能" id="Enable" unit="" data-type="bool" value="1" default="0"/>
		<data name="过滤计算模式" id="Mode" unit="" data-type="long" value="1" default="0"/> <!-- （0计算；1直接取CRC） -->
		<group name="Subscribe0" id="Subscribe0" data-type="Subscribe" value="">
			<data name="DestMac" id="DestMac" data-type="string" value="010CCD013001" unit="" />
			<data name="APPID" id="APPID" data-type="string" value="0x3001" unit="" />
			<data name="Port" id="Port" data-type="string" value="5" unit="" />
			<data name="Type" id="Type" data-type="string" value="2" unit="" />
			<data name="CRC" id="CRC" data-type="string" value="2" unit="" />
		</group>
        <group name="Subscribe1" id="Subscribe1" data-type="Subscribe" value="">
            <data name="DestMac" id="DestMac" data-type="string" value="010CCD013001" unit="" />
            <data name="APPID" id="APPID" data-type="string" value="0x3001" unit="" />
            <data name="Port" id="Port" data-type="string" value="5" unit="" />
            <data name="Type" id="Type" data-type="string" value="2" unit="" />
            <data name="CRC" id="CRC" data-type="string" value="2" unit="" />
        </group>
	</fault-paras-ex>
</macro>
*/
void CCapDeviceBase::GetSttCapParas(CDataGroup *pSttParas)
{
    CDataGroup *pNew = pSttParas->AddNewGroup("Subscribe", "Subscribe", "Subscribe");
	CString strText;

	if (m_nType != PROTOCOL_61850_TYPE_60448 )
	{
		pNew->AddNewData(XPARA_ID_Port, m_nFiberIndex);
		strText.Format(_T("0x%04X"), m_dwAppID);
		pNew->AddNewData(XPARA_ID_APPID, strText);
		strText = m_strDestAddress;
		strText.Replace("-","");
		pNew->AddNewData(XPARA_ID_DestMac, strText);//20220616 zhouhj 20220616 底层需要MAC故此处加上
		pNew->AddNewData(XPARA_ID_CRC, m_strCRC);
	}
	else
	{
		pNew->AddNewData(XPARA_ID_Port, m_nFiberIndex);
	}
	

	if (m_nType == PROTOCOL_61850_TYPE_91)
	{
		pNew->AddNewData(XPARA_ID_Type, XPARA_ID_TYPE_SMV91);
	}
	else if (m_nType == PROTOCOL_61850_TYPE_92)
	{
		pNew->AddNewData(XPARA_ID_Type, XPARA_ID_TYPE_SMV92);
	}
	else if (m_nType == PROTOCOL_61850_TYPE_GOOSE)
	{
		pNew->AddNewData(XPARA_ID_Type, XPARA_ID_TYPE_GOOSE);
	}
	else if (m_nType == PROTOCOL_61850_TYPE_60448 )
	{
		pNew->AddNewData(XPARA_ID_Type, XPARA_ID_TYPE_FT3);
	}
	else
		pNew->AddNewData(XPARA_ID_Type, _T(""));

//	pNew->AddNewData(XPARA_ID_ChCount, GetCount());
}

BOOL CCapDeviceBase::SetChannelNum(long nChannelNum)
{
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("SetChannelNum,当前AppID=0x%04X,Old总通道数(%ld),new总通道数(%ld)."),m_dwAppID,GetCount(),nChannelNum);
	long nOldNum = GetCount();

	if (nChannelNum == nOldNum)
	{
		return FALSE;
	}

	if (nOldNum > nChannelNum)
	{
		return TRUE;
	}

	CExBaseList *pParent = (CExBaseList*)m_pParent;
	long nDeviceIndex = pParent->FindIndex(this);

	long nIndex = 0;
	long nCount = nChannelNum - nOldNum;
	CCapDeviceChBase *pCh = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pCh = CreateChannel();
		pCh->InitNameID(nDeviceIndex, nIndex+nOldNum);//20220607 对于增加的通道,按实际的ID进行编号
		AddNewChild(pCh);
	}

	return nChannelNum;
}

BOOL CCapDeviceBase::Compare(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT)
{
	if (memcmp(m_byteDestMac, pDstMac, 6) != 0)
	{
		return FALSE;
	}

	//2020-07-02  lijunqing 
// 	if (memcmp(m_byteSrcMac, pSrcMac, 6) != 0)
// 	{
// 		return FALSE;
// 	}

	if (m_dwAppID != APPID)
	{
		return FALSE;
	}

	if (m_nType != nCMT)
	{
		return FALSE;
	}

	return TRUE;
}
BOOL CCapDeviceBase::Compare(PEPCAPBUFFERITEM pItemData)
{
// 	if (memcmp(m_byteDestMac, pItemData->addr_61850.dstMac, 6) != 0)
// 	{
// 		return FALSE;
// 	}

// 	if (memcmp(m_byteSrcMac, pItemData->addr_61850.srcMac, 6) != 0)
// 	{
// 		return FALSE;
// 	}

	if (m_dwAppID != pItemData->addr_61850.APPID)
	{
		return FALSE;
	}

	if (m_nType != pItemData->nProtocol)
	{
		return FALSE;
	}

	return TRUE;
}

void CCapDeviceBase::Iinit(PEPCAPBUFFERITEM pItemData)
{
	memcpy(m_byteDestMac, pItemData->addr_61850.dstMac, 6);
	memcpy(m_byteSrcMac, pItemData->addr_61850.srcMac, 6);
	m_dwAppID = pItemData->addr_61850.APPID;
	m_nType = pItemData->nProtocol;
	SetChannelNum(pItemData->nChCount);

	memcpy(m_oAnalysisResults.srcMAC,  m_byteSrcMac, 6);
	memcpy(m_oAnalysisResults.desMAC, m_byteDestMac, 6);
	m_oAnalysisResults.m_dwAppID =  m_dwAppID;
	m_oAnalysisResults.dDeltTime = 0;
	ep_protocol_analysis_init(m_oAnalysisResults); 	
	m_oPrevDatas.nFirstPacket = 0;  //初始化的时候置成0，第一帧不检查；
}

BOOL CCapDeviceBase::IsSameType(long nType)
{
    if ( iecfg_IsTypeGoose(nType) )
	{
        return (iecfg_IsTypeGoose(m_nType));
	}
    else if(iecfg_IsTypeAnalog(nType))
    {
        return (iecfg_IsTypeAnalog(m_nType));
    }

    return FALSE;
}

void CCapDeviceBase::InitNameAndID(long nTypeCount)
{
	if (m_strID.GetLength() > 0)
	{
		return;
	}

	if (m_nType == PROTOCOL_61850_TYPE_GOOSE)
	{
		m_strID.Format(_T("%s%d"),CAP_DATASET_MAP_ID_GOUT, nTypeCount);
	}
	else
	{
		m_strID.Format(_T("%s%d"),CAP_DATASET_MAP_ID_dsSV, nTypeCount);
	}

	m_strName.Format(_T("0x%04X_"), m_dwAppID);
	m_strName += m_strID;
}

void CCapDeviceBase::UpdateErrorTypeNum()
{

}

void CCapDeviceBase::InitAddress()
{
	m_strDestAddress = st_GetMacString(m_byteDestMac);
	m_strSrcAddress = st_GetMacString(m_byteSrcMac);
}

void CCapDeviceBase::InitIecfgData(CIecCfgDataBase *pIecCfgData)
{
	m_pIecCfgData = pIecCfgData;
}

void CCapDeviceBase::ParseDeviceInfor()
{
	if (m_pDeviceInforFrame != NULL)
	{
		return;
	}
	C61850ParseFrameList oFrameList;
	EPBUFFERPOS bufPos;
	ZeroMemory(&bufPos, sizeof(EPBUFFERPOS));
	m_oBuffer.GetBufferPos(bufPos);
	m_pDeviceInforFrame = oFrameList.ParseInfor(&bufPos, this);
}

void CCapDeviceBase::SetCapSelect(BOOL bSelect)
{
	m_nFillBeginPos = 0;;
	m_nDatasCount = 0;

	m_bSelect = bSelect;
	m_n64CapDataIndex = 0;

	if (m_bSelect)
	{//选择设备，设置缓冲区大小
		if (GetClassID() == CPDCLASSID_DEVICEGOOSE)
		{
			m_oCapTimeBuffer.SetBufferLength(CAP_RECORD_POINTS_GS);
		}
		else
		{
		m_oCapTimeBuffer.SetBufferLength(CAP_RECORD_POINTS);
	}
	}
	else
	{//不选择设备，清空缓存大小
		m_oCapTimeBuffer.FreeBuffer();
	}
}

void CCapDeviceBase::AddCapDataBuffer(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead,long nBufferLenth)
{
// 	if (!m_bSelect)
// 	{
// 		return;
// 	}
	if (!g_bSmartCap_RecordNow)
	{
		return;
	}
	//2020-06-27  更新链接状态
	m_bLinkState = 1;
	m_oTickCount.Enter();

	//数据的次数
	m_n64CapDataIndex++;


	AnalysisData(pDatas,pBuferHead,nBufferLenth);

	if (g_oCapAnalysisConfig.m_bUseCapRecord)
	{//是否进行录波处理 2022-6-19
		CapRecord(pDatas);
	}
	

    //for debug
	// m_oPrevDatas = *pDatas;
    //return ;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//以下N行代码  mym  add   2020-06-18
	UINT nClassID  = GetClassID();

	if (nClassID == CPDCLASSID_DEVICE92)
	{
		analysis92(pDatas);
	}
	else if (nClassID == CPDCLASSID_DEVICEGOOSE)
	{
		analysis_gs(pDatas);
	}
	else if (nClassID == CPDCLASSID_DEVICE6044)
	{
		analysis6044(pDatas);
	}
	
	m_oAnalysisResults.nPkgNum++;//报文总帧数加1
	m_oPrevDatas = *pDatas;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

//2022-6-19  lijunqing
void CCapDeviceBase::CapRecord(PEPCAPPARSEDATAS pDatas)
{
	POS pos = GetHeadPosition();
	CCapDeviceChBase *pCh = NULL;
	EPCAPPARSEDATA *pSmvData = pDatas->pDatas;
	long nIndex = 0;

	//通道数据的时间
	while (pos != NULL)
	{
		pCh = (CCapDeviceChBase *)GetNext(pos);
		pCh->CapRecord(pSmvData[nIndex].dwValue, m_nFillBeginPos);

		nIndex++;

		if (nIndex >= pDatas->dwDatas)
		{
			break;
		}
	}

	m_nFillBeginPos++;

	UINT nClassID  = GetClassID();
	long nMaxCapNum = CAP_RECORD_POINTS;

	if (nClassID == CPDCLASSID_DEVICEGOOSE)//20220523 zhouhj 需要根据设备类型进行判断
	{
		nMaxCapNum = CAP_RECORD_POINTS_GS;
	}

	if (m_nFillBeginPos >= nMaxCapNum)
	{
		m_nFillBeginPos = 0;
	}

	if (m_nDatasCount != nMaxCapNum)
	{
		m_nDatasCount++;
	}

	pos = GetHeadPosition();
	while (pos != NULL)
	{
		pCh = (CCapDeviceChBase *)GetNext(pos);
		pCh->SetPosition(m_nFillBeginPos, m_nDatasCount);
	}
}

void CCapDeviceBase::analysis92(PEPCAPPARSEDATAS pDatas)
{
}

void CCapDeviceBase::analysis6044(PEPCAPPARSEDATAS pDatas)
{
}

void CCapDeviceBase::analysis_gs(PEPCAPPARSEDATAS pDatas)
{
	if (g_oCapAnalysisConfig.m_bGsAnalysis)
	{
		ep_protocol_analysisGS(&m_oPrevDatas,   pDatas,  &m_oAnalysisResults);

		//这里存储变位后的GOOSE控制块的时标；
		// mym 2020-11-02 原来是下面这样的；
		//if (m_oAnalysisResults.rslt_gs.nErrorType [0]  > 0)
		//	m_dGOOSESyn = ep_tm_n64_t0_double(m_oAnalysisResults.n64Time);

		if (m_oAnalysisResults.rslt_gs.nErrorType [0]  > 0)
			m_dGOOSESyn = ep_tm_n64_t0_double(m_oAnalysisResults.n64Time);

		// PNI302  提取出变位的时间；mym 2020-11-03 
		if (m_oAnalysisResults.nCurChnel >= 0)
		{
			if (m_oAnalysisResults.nChangeFlag[m_oAnalysisResults.nCurChnel]  > 0)
			{
				m_dTime1[m_oAnalysisResults.nCurChnel] = ep_tm_n64_t0_double(m_oAnalysisResults.n64Time);
				m_oAnalysisResults.nChangeFlag[m_oAnalysisResults.nCurChnel] = 0;

				CString strText;
				ep_cap_timeval_to_string_ns(m_oAnalysisResults.n64Time, strText);
				m_dTime2[m_oAnalysisResults.nCurChnel]  = 0;
			}
		}

		ep_consistence_analysisGS();
		pDatas->nFirstPacket = 1;//mym 20202-6-21 解析完后当前帧就把标志置1；
	}
}

//2022-5-3  lijunqing
void CCapDeviceBase::ClearCap()
{
	m_nMatchState = MATCH_STATE_NONE;
	m_bLinkState = 0;
	m_pRefDvmDataset = NULL;

	POS pos = GetHeadPosition();
	CCapDeviceChBase *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CCapDeviceChBase *)GetNext(pos);
		pCh->AttachCapRecord(NULL);
	}
}

CString CCapDeviceBase::GetCtrlDesc()
{
	CString strDesc;

	if (m_pIecCfgData == NULL)
	{
		strDesc = m_strName;
	} 
	else
	{
		strDesc = m_pIecCfgData->m_strIedRefDesc;
	}

	return strDesc;
}

void CCapDeviceBase::InitDevice(PEPCAPPARSEDATAS pDatas)
{
	POS pos = GetHeadPosition();
	CCapDeviceChBase *pCh = NULL;
	long nIndex = 0;
	EPCAPPARSEDATA *pData = pDatas->pDatas;

	while (pos != NULL)
	{
		pCh = (CCapDeviceChBase *)GetNext(pos);
		pCh->UpdateChTypeAndLength(pData[nIndex].wChType,pData[nIndex].wLength);
//		pCh->m_nChType = pData[nIndex].wChType;
		pCh->m_nLength = pData[nIndex].wLength;
		nIndex++;

		if (nIndex >= pDatas->dwDatas)
		{
			break;
		}
	}
}

void CCapDeviceBase::InitDevice(CIecCfgDataBase *pIecCfgData)
{
	m_pIecCfgData = pIecCfgData;
	ASSERT(pIecCfgData != NULL);

	cap_mac_string_to_byte(m_strDestAddress, m_byteDestMac);
	cap_mac_string_to_byte(m_strSrcAddress, m_byteSrcMac);

	if (pIecCfgData)
	{
//		m_strName = pIecCfgData->m_strIedRefDesc;//20230222 zhouhj 描述使用固定包含AppID的格式
		m_nFiberIndex = pIecCfgData->m_nFiber2Index;

// 		if (pIecCfgData->m_strDvmDatasetID.GetLength() > 0)  //20221220 zhouhj 不修改ID
// 		{
// 			m_strID = pIecCfgData->m_strDvmDatasetID;
// 		}
// 		else
// 		{
// 		m_strID = pIecCfgData->m_strID;
// 		}
	}

	//lijunqing 2020-6-19  初始化的时候赋值，分析过程中
	memcpy(m_oAnalysisResults.srcMAC,  m_byteSrcMac, 6);
	memcpy(m_oAnalysisResults.desMAC, m_byteDestMac, 6);
	m_oAnalysisResults.m_dwAppID =  m_dwAppID;
	ep_protocol_analysis_init(m_oAnalysisResults); 

	m_oPrevDatas.nFirstPacket = 0;  //初始化的时候置成0，第一帧不检查；
}

void CCapDeviceBase::SetChannelState(PEPCAPPARSEDATAS pParseDatas)
{
	CCapDeviceChBase *pCh = NULL;
	int nIndex = 0;
	POS pos;

	if (m_nMatchState == MATCH_STATE_SURPLUS || m_nMatchState == MATCH_STATE_MISS)
	{
		pos = GetHeadPosition();
		while (pos)
		{
			pCh = (CCapDeviceChBase*)GetNext(pos);	
			pCh->SetMatchState(m_nMatchState);
		}
	}
	else if (m_nMatchState == MATCH_STATE_SUCCESS)
	{
		pos = GetHeadPosition();
		while (pos)
		{
			nIndex++;
			pCh = (CCapDeviceChBase*)GetNext(pos);	

			if (nIndex <= pParseDatas->dwDatas)
			{
				pCh->SetMatchState(MATCH_STATE_SUCCESS);
			}
			else
			{
				pCh->SetMatchState(MATCH_STATE_MISS);	
			}
		}

		long nExtraCount = pParseDatas->dwDatas - nIndex;
		CCapDeviceChBase *pCh = NULL;
		CString strInit;

		for (int i=0; i<nExtraCount; i++)
		{
			pCh = CreateChannel();

			strInit.Format(_T("通道%d"),i+1);
			pCh->InitNameID(strInit);
			pCh->SetMatchState(MATCH_STATE_SURPLUS);

			AddNewChild(pCh);
		}
	}
}

void CCapDeviceBase::Reset()
{
	m_n64CapDataIndex = 0;
	m_nFillBeginPos = 0;
	m_nDatasCount = 0;

	POS pos = GetHeadPosition();
	CCapDeviceChBase *pCh = NULL;

	pos = GetHeadPosition();
	while (pos != NULL)
	{
		pCh = (CCapDeviceChBase *)GetNext(pos);
		pCh->SetPosition(m_nFillBeginPos, m_nDatasCount);
	}

	ZeroMemory(&m_oPrevDatas, sizeof(EPCAPPARSEDATAS));
	ep_protocol_analysis_init(m_oAnalysisResults); 
	m_nCurrErrorTypeNum = 0;

	m_oPrevDatas.nFirstPacket = 0;  //初始化的时候置成0，第一帧不检查；
}

//数据接受超时
BOOL CCapDeviceBase::IsDataRcvOverTime()
{
	if (g_nXSmartCapDebugMode)
	{
		return m_oTickCount.GetTickCountLong(FALSE) > 200000; 
	}
	else
	{
		return m_oTickCount.GetTickCountLong(FALSE) > 10000; 
	}
}

void CCapDeviceBase::AttachIecCfgData(CIecCfgDataBase *pCfgDataBase)
{
	m_pIecCfgData = pCfgDataBase;

	if(pCfgDataBase == NULL)
	{
		return;
	}

	InitDevice(m_pIecCfgData);

	CCapDeviceChBase *pCh = NULL;
	CIecCfgDataChBase *pCfgDataCh = NULL;
	long nChCount = GetCount();

	for(int nIndex=0;nIndex<nChCount;nIndex++)
	{
		pCh = (CCapDeviceChBase *)GetAtIndex(nIndex);
		pCh->AttachIecCfgDataCh((CIecCfgDataChBase*)m_pIecCfgData->m_pCfgChs->GetAtIndex(nIndex));
	}

	SetDeviceChMaps();
}

void CCapDeviceBase::CreateDvmDataset(CDvmDataset *pDataset)
{
	m_pRefDvmDataset = pDataset;
	pDataset->m_dwItemData = (DWORD)this;
	pDataset->m_strID = m_strID;
	pDataset->m_strName = m_strName;

	CCapDeviceChBase *pCh = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pChData = NULL;

	while (pos != NULL)
	{
		pCh = (CCapDeviceChBase *)GetNext(pos);
		pChData = new CDvmData();
		pDataset->AddNewChild(pChData);
		pCh->InitChannel(pChData);
	}
}

void CCapDeviceBase::UpdateDvmDeviceDatas()
{

}

void cap_mac_string_to_byte(const CString &strMac, BYTE *pMAC)
{
	long btMac[6];
	const char *pString = strMac.GetString();

	sscanf(pString,_T("%02X-%02X-%02X-%02X-%02X-%02X"),&btMac[0],&btMac[1],&btMac[2],&btMac[3],&btMac[4],&btMac[5]);

	for(int i=0;i<6;i++)
		pMAC[i] = (BYTE)btMac[i];
}

//16进制字符串 转成16进制值，方便比较；
int HexStringToByteEx(char s[],  unsigned char bits[]) 
{	
	int i,n = 0;	for(i = 0; s[i]; i += 2)
	{		
		if(s[i] >= 'A' && s[i] <= 'F')		
			bits[n] = s[i] - 'A' + 10;		
		else bits[n] = s[i] - '0';		
		if(s[i + 1] >= 'A' && s[i + 1] <= 'F')	
			bits[n] = (bits[n] << 4) | (s[i + 1] - 'A' + 10);	
		else 
			bits[n] = (bits[n] << 4) | (s[i + 1] - '0');	
		++n;	
	}	
	return n;
}

//16进制字节数转成16进制字符串；
CString GetMacStringFromByte(const unsigned char *pMacAddr)
{
	CString strMac;
	strMac.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"),pMacAddr[0], pMacAddr[1], pMacAddr[2], pMacAddr[3], pMacAddr[4], pMacAddr[5]);
	return strMac;
}

// void ByteToHexStr(const unsigned char* source, char* dest, int sourceLen)
// {
// 	short i;
// 	unsigned char highByte, lowByte;
// 
// 	for (i = 0; i < sourceLen; i++)
// 	{
// 		highByte = source[i] >> 4;
// 		lowByte = source[i] & 0x0f ;
// 
// 		highByte += 0x30;
// 
// 		if (highByte > 0x39)
// 			dest[i * 2] = highByte + 0x07;
// 		else
// 			dest[i * 2] = highByte;
// 
// 		lowByte += 0x30;
// 		if (lowByte > 0x39)
// 			dest[i * 2 + 1] = lowByte + 0x07;
// 		else
// 			dest[i * 2 + 1] = lowByte;
// 	}
// 	return ;
// }

//检查报文一致性
void CCapDeviceBase::ep_consistence_analysis92()
{
	if (m_oPrevDatas.nFirstPacket==0)
		return;

	CIecCfg92Data* pCfgData92  = (CIecCfg92Data*)GetIecCfgData();

	CString strDesMAC;
	CString strSVID;
	CString strDestAddress;	

	long nP = 0, nQ = 0;
	if(pCfgData92 == NULL)
		return;

	//这里取第一个ASDU的信息来做比较； 
	//for (int i = 0; i < pCapDevice->m_oPrevDatas.oData92.Num_ASDU;i++)
	////{
	//break;
	///}
	//if (pCapDevice->m_oPrevDatas.oData92.nTestMode==)
	//{
	m_dwFlagSVCstc[0] += 0;
	//}
	nP = m_oPrevDatas.oData92.Asdu[0].confRev;
	nQ = pCfgData92->m_dwVersion;
	if (nP   !=  nQ)
		m_dwFlagSVCstc[1] += 1;

	nP = m_oPrevDatas.oData92.APDULen;
	//APDU长度单独判断报文里的信息；
	if (nP)
		m_dwFlagSVCstc[2] += 0;

	nP = m_oPrevDatas.oData92.nChCount/*/8*/;//20220614 zhouhj 已在赋值位置统一处理除以8的问题
	nQ = pCfgData92->m_nChannelNum;
	if (nP  !=  nQ)
		m_dwFlagSVCstc[3] += 1;

	//if (nP==nQ)
	m_dwFlagSVCstc[4] = 0;
	//if (nP==nQ)
	m_dwFlagSVCstc[5] = 0;

	nP = m_oPrevDatas.oData92.Asdu[0].smpSynch;
	nQ = pCfgData92->m_nSyn;
	if (nP  !=  nQ)
		m_dwFlagSVCstc[6] += 1;

	//nP = pCapDevice->m_oPrevDatas.oData92.Num_ASDU;
	//nQ = pCfgData92->m_nSampleRate;
	//if (nP==nQ)
	m_dwFlagSVCstc[7] += 0;

	nP = m_oPrevDatas.oData92.Num_ASDU;
	nQ = pCfgData92->m_nAsduNum;
	if (nP  != nQ)
		m_dwFlagSVCstc[8] += 1;

	strDestAddress = pCfgData92->m_strDestAddress;
	strDestAddress.Remove('-');

	//先把目标地址转成char ，然后在比较；
	int  nlength = strDestAddress.GetLength();
	if (nlength > 0 && nlength <= 25)
	{
		::memcpy(m_destIn, strDestAddress.GetString(), strDestAddress.GetLength());
		HexStringToByteEx(m_destIn,  m_destOut);
		if (memcmp((char*)m_destOut,  m_oPrevDatas.destMAC, 6)  !=  0)
			m_dwFlagSVCstc[9] += 1;
	}
	strSVID = m_oPrevDatas.oData92.Asdu[0].SVID;
	if (strSVID  !=  pCfgData92->m_strSVID)
		m_dwFlagSVCstc[10] += 1;
}


//GOOSE一致性检查 mym 20202-6-19
void CCapDeviceBase::ep_consistence_analysisGS( )
{
	CIecCfgGooseDataBase* pCfgGSData = (CIecCfgGooseDataBase*)GetIecCfgData();
	if ( pCfgGSData==NULL)
		return;
	if (m_oPrevDatas.nFirstPacket==0)
		return;


	if (m_oPrevDatas.oDataGs.nTestMode  !=  pCfgGSData->m_bTest)
		m_dwFlagGSCstc[0] += 1;

	if (m_oPrevDatas.oDataGs.nConfRev  !=  pCfgGSData->m_dwVersion)
		m_dwFlagGSCstc[1] += 1;

	//pCapDevice->m_oPrevDatas.oDataGs.APDULen;
	m_dwFlagGSCstc[2] = 0;

	// CFG中没有通道数量；
	m_oPrevDatas.oDataGs.nChCnt;       
	m_dwFlagGSCstc[3] += 0;

	if (m_oPrevDatas.oDataGs.VLAN_ID  !=  pCfgGSData->m_dwVLandID)
		m_dwFlagGSCstc[4] += 0;

	if (m_oPrevDatas.oDataGs.VLAN_P  !=  pCfgGSData->m_dwVLandPriority)
		m_dwFlagGSCstc[5] += 0;

	CString desMAC = pCfgGSData->m_strDestAddress;
	if (desMAC.Find("-") >=0 )
		desMAC.Remove('-');
	//desMAC.MakeLower();

	//这里16进制字符串要转化成16进制字节才能比较；
	///////////////////////////////////////////////////////////////
	int  nlength = desMAC.GetLength();
	if (nlength > 0 && nlength <= 25)
	{
		::memcpy(m_destIn,  desMAC.GetString(),  desMAC.GetLength());
		HexStringToByteEx(m_destIn,  m_destOut);
		if (memcmp((char*)m_destOut,  m_oPrevDatas.destMAC, 6)  !=  0)
			m_dwFlagGSCstc[6]  += 1;
		else 
		{
			int adf = 0;
		}
	}

	////////////////////////////

	//HexStringToByteEx();
	//if (memcmp(desMAC,  m_oPrevDatas.destMAC, 6)  !=  0)
	//m_dwFlagGSCstc[6]  += 1;

	if (pCfgGSData->m_strgocbRef != m_oPrevDatas.oDataGs.GORef)
		m_dwFlagGSCstc[7] += 1;

	if (pCfgGSData->m_strGooseId   !=  m_oPrevDatas.oDataGs.GOID)
		m_dwFlagGSCstc[8] += 1;
}

// long CCapDeviceBase::GetChIndexBySelectChIndex(long nSelectIndex)
// {
// 	CCapDeviceChBase *pCh = NULL;
// 	long nCurrChIndex = 0,nCurrSelectIndex = -1;
// 	POS pos = GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pCh = (CCapDeviceChBase *)GetNext(pos);
// 
// 		if (pCh->m_nSelect)
// 		{
// 			nCurrSelectIndex++;
// 
// 			if (nSelectIndex == nCurrSelectIndex)
// 			{
// 				break;
// 			}
// 		}
// 
// 		nCurrChIndex++;
// 	}
// 
// 	return nCurrChIndex;
// }

//long CCapDeviceBase::GetSelectChIndexByChIndex(long nChIndex)
// {
// 	CCapDeviceChBase *pCh = NULL;
// 	long nCurrChIndex = 0,nCurrSelectIndex = -1;
// 	POS pos = GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pCh = (CCapDeviceChBase *)GetNext(pos);
// 
// 		if (pCh->m_nSelect)
// 		{
// 			nCurrSelectIndex++;
// 		}
// 
// 		if (nCurrChIndex == nChIndex)
// 		{
// 			break;
// 		}
// 
// 		nCurrChIndex++;
// 	}
// 
// 	return nCurrSelectIndex;
//}