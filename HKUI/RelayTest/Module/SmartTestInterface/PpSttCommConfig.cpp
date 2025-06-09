#include "stdafx.h"
#include"PpSttCommConfig.h"
#include "../SttGlobalDef.h"
#include "../../../System/Module/XAtsSysSvrGlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern BOOL g_bShowTestWndTop;

//////////////////////////////////////////////////////////////////////////
//CPpSttCommConfig
CPpSttCommConfig::CPpSttCommConfig()
{
    m_pCmmConfig = NULL;
}

CPpSttCommConfig::~CPpSttCommConfig()
{ 
	
}

void CPpSttCommConfig::InitAfterRead()
{
    GetCommConfig();
}

void CPpSttCommConfig::InitEngine(const CString &strDeviceSN, const CString &strEngineID, const CString &strPpXmlFile, const CString &strDvmFile)
{
	DeleteAll();
	AddNewData(STT_CMD_PARA_DeviceSN, strDeviceSN);
	AddNewData(XPARA_ID_PPXMLFILE, strPpXmlFile);
	AddNewData(XPARA_ID_DVMFILE, strDvmFile);
	//AddNewData(XPARA_ID_EngineProgID, strEngineID);
	AddNewData(STT_CMD_PARA_EngineProgID, strEngineID);
}

void CPpSttCommConfig::Set_DeviceSN(const CString &strDeviceSN)
{
	SetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN,TRUE);
}

void CPpSttCommConfig::Set_PpXmlFile(const CString &strPpXmlFile)
{
	SetDataValue(XPARA_ID_PPXMLFILE, strPpXmlFile,TRUE);
}

void CPpSttCommConfig::Set_EngineID(const CString &strEngineID)
{
	SetDataValue(STT_CMD_PARA_EngineProgID, strEngineID,TRUE);
}

void CPpSttCommConfig::Set_DvmFile(const CString &strDvmFile)
{
	SetDataValue(STT_CMD_PARA_DvmFile, strDvmFile,TRUE);
}

bool CPpSttCommConfig::Is_MmsEngine()
{
    return CmmConfigIsKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMmsKey);
}

bool CPpSttCommConfig::Is_CmsEngine()
{
    return CmmConfigIsKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmsKey);
}

bool CPpSttCommConfig::Is_PpEngine()
{
   if (Is_PpEngine_Serial())
   {
	   return true;
   }

  if (Is_PpEngine_Net())
  {
	  return true;
  }

    return false;
}

bool CPpSttCommConfig::Is_PpEngine_Net()
{
	if (CmmConfigIsKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpClientKey))
	{
		return true;
	}

	if (CmmConfigIsKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpServerKey))
	{
		return true;
	}

	if (CmmConfigIsKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpClientKey))
	{
		return true;
	}

	if (CmmConfigIsKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpServerKey))
	{
		return true;
	}

	return false;
}

bool CPpSttCommConfig::Is_PpEngine_Serial()
{
	if (CmmConfigIsKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strSerialKey))
	{
		return true;
	}

	return false;
}

CString CPpSttCommConfig::Get_DeviceSN()
{
	CString strVal;
	GetDataValue(STT_CMD_PARA_DeviceSN, strVal);
	return strVal;
}

CString CPpSttCommConfig::Get_DvmFile()
{
    CString strVal;
    GetDataValue(STT_CMD_PARA_DvmFile, strVal);
    return strVal;
}

//2023.11.15 lichao PNS331 新增
//获取Ppxml项内容
CString CPpSttCommConfig::Get_PpxmlFile()
{
	CString strVal;
	GetDataValue(XPARA_ID_PPXMLFILE, strVal);
	return strVal;
}

/*
<group>
	<data name="" id="DeviceSN" data-type="" value="MmsEngine_Demo"/>
	<data name="" id="ppxml-file" data-type="" value=""/>
	<data name="" id="dvm-file" data-type="" value="PCS931.xml"/>
	<data name="" id="EngineProgID" value="MmsEngine"/>
	<group name="" id="comm-config" data-type="" value="">
		<data name="" id="mms" data-type="" value="">
			<value name="" id="local-ip" data-type="" value="192.168.1.60"/>
			<value name="" id="local-port" data-type="" value="0"/>
			<value name="" id="remote-ip" data-type="" value="192.168.1.20"/>
			<value name="" id="remote-port" data-type="" value="9988"/>
		</data>
	</group>
</group>
*/

/*
<group>
	<data name="" id="DeviceSN" data-type="" value="PpEngine_TcpClient"/>
	<data name="" id="ppxml-file" data-type="" value="TcpClient.ppxml"/>
	<data name="" id="dvm-file" data-type="" value="PCS931.xml"/>
	<data name="" id="EngineProgID" value="PpEngine"/>
	<group name="" id="comm-config" data-type="" value="">
		<data name="" id="tcp-client" data-type="" value="">
			<value name="" id="local-ip" data-type="" value="192.168.1.60"/>
			<value name="" id="local-port" data-type="" value="0"/>
			<value name="" id="remote-ip" data-type="" value="192.168.1.20"/>
			<value name="" id="remote-port" data-type="" value="9988"/>
		</data>
	</group>
</group>
*/
// BOOL CPpSttCommConfig::InitCmmConfig_Net_TcpClient(CDvmData *pData)
// {
//    CCmmTcpClientConfig *pTcpClient = AddConfigTcpClient();
// 
//    pData->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey,  pTcpClient->m_strLocalIP);
//    pData->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey,  pTcpClient->m_nLocalPort);
//    pData->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey,  pTcpClient->m_strRemoteIP);
//    pData->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey,  pTcpClient->m_nRemotePort);
// 
//    return TRUE;
// }

CDataGroup* CPpSttCommConfig::NewCommConfig()
{
	m_pCmmConfig = new CDataGroup();
	m_pCmmConfig->m_strID = CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey;
	AddNewChild(m_pCmmConfig);

	return m_pCmmConfig;
}

CDvmData* CPpSttCommConfig::CmmCfg_GetByKey(const CString &strKey)
{
	GetCommConfig();

	return (CDvmData*)m_pCmmConfig->FindByID(strKey);
}

CDvmData* CPpSttCommConfig::CmmCfg_GetByKey(BSTR bstrKey)
{
	CString strKey;
	strKey = bstrKey;
	return CmmCfg_GetByKey(strKey);
}

CDvmData* CPpSttCommConfig::CmmCfg_SetByKey(const CString &strKey)
{
	return CmmCfg_AddByKey(strKey, TRUE);
}

CDvmData* CPpSttCommConfig::CmmCfg_SetByKey(BSTR bstrKey)
{
	CString strKey;
	strKey = bstrKey;
	return CmmCfg_AddByKey(strKey, TRUE);
}

bool CPpSttCommConfig::CmmConfigIsKey(const CString &strKey)
{
    CDvmData *pFind = NULL;
    GetCommConfig();

    pFind = (CDvmData*)m_pCmmConfig->FindByID(strKey);

    if (pFind != NULL)
    {
        return true;
    }

    return false;
}

bool CPpSttCommConfig::CmmConfigIsKey(BSTR bstrKey)
{
    CString strKey;
    strKey = bstrKey;
    return CmmConfigIsKey(strKey);
}

CDvmData* CPpSttCommConfig::CmmCfg_AddByKey(const CString &strKey, BOOL bClearAll)
{
	CDvmData *pFind = NULL;
	GetCommConfig();

	pFind = (CDvmData*)m_pCmmConfig->FindByID(strKey);

	if (pFind == NULL)
	{
		if (bClearAll)
		{
			m_pCmmConfig->DeleteAll();
		}

		pFind = new CDvmData();
		pFind->m_strID = strKey;
		pFind->m_strName = strKey;
		m_pCmmConfig->AddNewChild(pFind);
	}

	return pFind;
}

CDvmData* CPpSttCommConfig::CmmCfg_AddByKey(BSTR bstrKey, BOOL bClearAll)
{
	CString strKey;
	strKey = bstrKey;
	return CmmCfg_AddByKey(strKey, TRUE);
}

void CPpSttCommConfig::CmmCfg_DelByKey(const CString &strKey)
{
	GetCommConfig();
	m_pCmmConfig->DeleteByID(strKey);
}

void CPpSttCommConfig::CmmCfg_DelByKey(BSTR bstrKey)
{
	CString strKey;
	strKey = bstrKey;
	return CmmCfg_DelByKey(strKey);
}

CDataGroup* CPpSttCommConfig::GetCommConfig()
{
	CString strKey;
	strKey = CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey;
	CDataGroup *pFind = (CDataGroup*)FindByID(strKey);

	if (pFind == NULL)
	{
		pFind = NewCommConfig();
	}

	m_pCmmConfig = pFind;

	return pFind;
}
	
CDvmData* CPpSttCommConfig::Get_TcpClient()
{
    return CmmCfg_GetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpClientKey);
}

CDvmData* CPpSttCommConfig::Get_TcpServer()
{
	return CmmCfg_GetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpServerKey);
}

CDvmData* CPpSttCommConfig::Get_UdpClient()
{
	return CmmCfg_GetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpClientKey);
}

CDvmData* CPpSttCommConfig::Get_UdpServer()
{
	return CmmCfg_GetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpServerKey);
}

CDvmData* CPpSttCommConfig::Get_Serial()
{
	return CmmCfg_GetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strSerialKey);
}

CDvmData* CPpSttCommConfig::Get_MMS()
{
	return CmmCfg_GetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMmsKey);
}

CDvmData* CPpSttCommConfig::Get_CMS()
{
	return CmmCfg_GetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmsKey);
}

CDvmData* CPpSttCommConfig::Add_TcpClient()
{
	return CmmCfg_AddByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpClientKey, FALSE);
}

CDvmData* CPpSttCommConfig::Add_TcpServer()
{
	return CmmCfg_AddByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpServerKey, FALSE);
}

CDvmData* CPpSttCommConfig::Add_UdpClient()
{
	return CmmCfg_AddByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpClientKey, FALSE);
}

CDvmData* CPpSttCommConfig::Add_UdpServer()
{
	return CmmCfg_AddByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpServerKey, FALSE);
}

void CPpSttCommConfig::Set_Net()
{
	if (Is_PpEngine_Net())
	{
		return;
	}

	CmmCfg_DelByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmsKey);
	CmmCfg_DelByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMmsKey);
	CmmCfg_DelByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strSerialKey);
}

CDvmData* CPpSttCommConfig::Set_TcpClient()
{
	Set_Net();

	return CmmCfg_SetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpClientKey);
}

CDvmData* CPpSttCommConfig::Set_TcpServer()
{
	Set_Net();

	return CmmCfg_SetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpServerKey);
}

CDvmData* CPpSttCommConfig::Set_UdpClient()
{
	Set_Net();

	return CmmCfg_SetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpClientKey);
}

CDvmData* CPpSttCommConfig::Set_UdpServer()
{
	Set_Net();

	return CmmCfg_SetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpServerKey);
}

CDvmData* CPpSttCommConfig::Set_Serial()
{
	if (Is_PpEngine_Serial())
	{
		return Get_Serial();
	}

	return CmmCfg_SetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strSerialKey);
}

CDvmData* CPpSttCommConfig::Set_MMS()
{
	if (Is_MmsEngine())
	{
		return Get_MMS();
	}

	return CmmCfg_SetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMmsKey);
}

CDvmData* CPpSttCommConfig::Set_CMS()
{
	if (Is_CmsEngine())
	{
		return Get_CMS();
	}

	return CmmCfg_SetByKey(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmsKey);
}

void CPpSttCommConfig::MMS_Init(const CString &strLocalIP, const CString &strRemoteIP, long nRemotePort, const CString &strPsw, const CString &strKey)
{
	CDvmData *pMms = Set_MMS();

   dvmdata_set_value(pMms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey,  strLocalIP);
   dvmdata_set_value(pMms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey,  strRemoteIP);
   dvmdata_set_value(pMms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey,  nRemotePort);
   dvmdata_set_value(pMms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptPswKey,  strPsw);
   dvmdata_set_value(pMms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptKeyKey,  strKey);
}

void CPpSttCommConfig::MMS_Set_EncryptPsw(const CString &strPsw)
{
	CDvmData *pMms = Set_MMS();
    dvmdata_set_value(pMms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptPswKey,  strPsw);
}

void CPpSttCommConfig::MMS_Set_EncryptKey(const CString &strKey)
{
	CDvmData *pMms = Set_MMS();
    dvmdata_set_value(pMms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptKeyKey,  strKey);
}

void CPpSttCommConfig::MMS_Set_LocalIP(const CString &strLocalIP)
{
	CDvmData *pMms = Set_MMS();
	dvmdata_set_value(pMms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey,  strLocalIP);
}

void CPpSttCommConfig::MMS_Set_RemoteIP(const CString &strRemoteIP)
{
	CDvmData *pMms = Set_MMS();
	dvmdata_set_value(pMms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey,  strRemoteIP);
}

void CPpSttCommConfig::MMS_Set_RemotePort(long nRemotePort)
{
	CDvmData *pMms = Set_MMS();
	dvmdata_set_value(pMms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey,  nRemotePort);
}

void CPpSttCommConfig::Serial_Set_port_number(long nPortNumber)
{
    CDvmData *pSerial = Set_Serial();
    dvmdata_set_value(pSerial, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strPortNumKey,  nPortNumber);
}

void CPpSttCommConfig::Serial_Set_baud_rate(long nBaudRate)
{
    CDvmData *pSerial = Set_Serial();
    dvmdata_set_value(pSerial, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strBaudRateKey,  nBaudRate);
}

void CPpSttCommConfig::Serial_Set_byte_size(long nByteSize)
{
    CDvmData *pSerial = Set_Serial();
    dvmdata_set_value(pSerial, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strByteSizeKey,  nByteSize);
}

void CPpSttCommConfig::Serial_Set_stop_bit(long nStopBit)
{
    CDvmData *pSerial = Set_Serial();
    dvmdata_set_value(pSerial, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strStopBitsKey,  nStopBit);
}

void CPpSttCommConfig::Serial_Set_parity(long nParity)
{
    CDvmData *pSerial = Set_Serial();
    dvmdata_set_value(pSerial, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strParityKey,  nParity);
}


void CPpSttCommConfig::CMS_Init(const CString &strLocalIP, const CString &strRemoteIP, long nRemotePort, const CString &strPsw, const CString &strKey)
{
	CDvmData *pCms = Set_CMS();

	dvmdata_set_value(pCms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey,  strLocalIP);
	dvmdata_set_value(pCms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey,  strRemoteIP);
	dvmdata_set_value(pCms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey,  nRemotePort);
    dvmdata_set_value(pCms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptPswKey,  strPsw);
    dvmdata_set_value(pCms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptKeyKey,  strKey);
}

void CPpSttCommConfig::PpEngineNet_Init(const CString &strLocalIP,const CString &strRemoteIP, long nRemotePort)
{
	Set_Net();
	TcpClient_Set_LocalIP(strLocalIP);
	TcpClient_Set_RemoteIP(strRemoteIP);
	TcpClient_Set_RemotePort(nRemotePort);
}

void CPpSttCommConfig::CMS_Set_EncryptPsw(const CString &strPsw)
{
    CDvmData *pMms = Set_CMS();
    dvmdata_set_value(pMms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptPswKey,  strPsw);
}

void CPpSttCommConfig::CMS_Set_EncryptKey(const CString &strKey)
{
    CDvmData *pMms = Set_CMS();
    dvmdata_set_value(pMms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptKeyKey,  strKey);
}

void CPpSttCommConfig::CMS_Set_LocalIP(const CString &strLocalIP)
{
	CDvmData *pCms = Set_CMS();
	dvmdata_set_value(pCms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey,  strLocalIP);
}

void CPpSttCommConfig::CMS_Set_RemoteIP(const CString &strRemoteIP)
{
	CDvmData *pCms = Set_CMS();
	dvmdata_set_value(pCms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey,  strRemoteIP);
}

void CPpSttCommConfig::CMS_Set_RemotePort(long nRemotePort)
{
	CDvmData *pCms = Set_CMS();
	dvmdata_set_value(pCms, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey,  nRemotePort);
}

//////////////////////////////////////////////////////////////////////////////////
///TcpClient
void CPpSttCommConfig::TcpClient_Set_LocalIP(const CString &strLocalIP)
{
    CDvmData *pTcpClient = Set_TcpClient();
    dvmdata_set_value(pTcpClient, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey,  strLocalIP);
}

void CPpSttCommConfig::TcpClient_Set_LocalPort(long nLocalPort)
{
    CDvmData *pTcpClient = Set_TcpClient();
    dvmdata_set_value(pTcpClient, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey,  nLocalPort);
}

void CPpSttCommConfig::TcpClient_Set_RemoteIP(const CString &strRemoteIP)
{
    CDvmData *pTcpClient = Set_TcpClient();
    dvmdata_set_value(pTcpClient, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey,  strRemoteIP);
}

void CPpSttCommConfig::TcpClient_Set_RemotePort(long nRemotePort)
{
    CDvmData *pTcpClient = Set_TcpClient();
    dvmdata_set_value(pTcpClient, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey,  nRemotePort);
}


///////////////////////////////////////////////////////////////////////
///TcpServer
void CPpSttCommConfig::TcpServer_Set_LocalIP(const CString &strLocalIP)
{
    CDvmData *pTcpServer = Set_TcpServer();
    dvmdata_set_value(pTcpServer, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey,  strLocalIP);
}

void CPpSttCommConfig::TcpServer_Set_LocalPort(long nLocalPort)
{
    CDvmData *pTcpServer = Set_TcpServer();
    dvmdata_set_value(pTcpServer, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey,  nLocalPort);
}


//UdpServer_Set
void CPpSttCommConfig::UdpServer_Set_LocalIP(const CString &strLocalIP)
{
    CDvmData *pUdpServer = Set_UdpServer();
    dvmdata_set_value(pUdpServer, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey,  strLocalIP);
}
void CPpSttCommConfig::UdpServer_Set_LocalPort(long nLocalPort)
{
    CDvmData *pUdpServer = Set_UdpServer();
    dvmdata_set_value(pUdpServer, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey,  nLocalPort);
}
void CPpSttCommConfig::UdpServer_Set_MuticastIP(const CString &strMuticastIP)
{
    CDvmData *pUdpServer = Set_UdpServer();
    dvmdata_set_value(pUdpServer, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastIPKey,  strMuticastIP);
}

//UdpClient_Set
void CPpSttCommConfig::UdpClient_Set_LocalIP(const CString &strLocalIP)
{
    CDvmData *pUdpClient = Set_UdpClient();
    dvmdata_set_value(pUdpClient, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey,  strLocalIP);
}
void CPpSttCommConfig::UdpClient_Set_LocalPort(long nLocalPort)
{
    CDvmData *pUdpClient = Set_UdpClient();
    dvmdata_set_value(pUdpClient, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey,  nLocalPort);
}
void CPpSttCommConfig::UdpClient_Set_MuticastIP(const CString &strMuticastIP)
{
    CDvmData *pUdpClient = Set_UdpClient();
    dvmdata_set_value(pUdpClient, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastIPKey,  strMuticastIP);
}
void CPpSttCommConfig::UdpClient_Set_RemoteIP(const CString &strRemoteIP)
{
    CDvmData *pUdpClient = Set_UdpClient();
    dvmdata_set_value(pUdpClient, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey,  strRemoteIP);
}

void CPpSttCommConfig::UdpClient_Set_RemotePort(long nRemotePort)
{
    CDvmData *pUdpClient = Set_UdpClient();
    dvmdata_set_value(pUdpClient, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey,  nRemotePort);
}



//TcpClient_Get
CString CPpSttCommConfig::TcpClient_Get_RemotePort()
{
    CDvmData *pTcpClient = Set_TcpClient();
    return pTcpClient->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey);
}

CString CPpSttCommConfig::TcpClient_Get_RemoteIP()
{
    CDvmData *pTcpClient = Set_TcpClient();
    return pTcpClient->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey);
}

CString CPpSttCommConfig::TcpClient_Get_LocalIP()
{
    CDvmData *pTcpClient = Set_TcpClient();
    return pTcpClient->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey);
}
CString CPpSttCommConfig::TcpClient_Get_LocalPort()
{
    CDvmData *pTcpClient = Set_TcpClient();
    return pTcpClient->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey);
}

//TcpServer_Get
CString  CPpSttCommConfig::TcpServer_Get_LocalPort()
{
    CDvmData *pTcpServer = Set_TcpServer();
    return pTcpServer->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey);
}
CString  CPpSttCommConfig::TcpServer_Get_LocalIP()
{
    CDvmData *pTcpServer = Set_TcpServer();
    return pTcpServer->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey);
}

//UdpServer_Get
CString  CPpSttCommConfig::UdpServer_Get_MuticastIP()
{
    CDvmData *pUdpServer = Set_UdpServer();
    return pUdpServer->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastIPKey);
}
CString  CPpSttCommConfig::UdpServer_Get_LocalPort()
{
    CDvmData *pUdpServer = Set_UdpServer();
    return pUdpServer->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey);
}
CString  CPpSttCommConfig::UdpServer_Get_LocalIP()
{
    CDvmData *pUdpServer = Set_UdpServer();
    return pUdpServer->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey);
}

//UdpClient_Get
CString  CPpSttCommConfig::UdpClient_Get_RemotePort()
{
    CDvmData *pUdpClient = Set_UdpClient();
    return pUdpClient->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey);
}
CString  CPpSttCommConfig::UdpClient_Get_RemoteIP()
{
    CDvmData *pUdpClient = Set_UdpClient();
    return pUdpClient->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey);
}
CString  CPpSttCommConfig::UdpClient_Get_MuticastIP()
{
    CDvmData *pUdpClient = Set_UdpClient();
    return pUdpClient->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastIPKey);
}
CString  CPpSttCommConfig::UdpClient_Get_LocalPort()
{
    CDvmData *pUdpClient = Set_UdpClient();
    return pUdpClient->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey);
}
CString  CPpSttCommConfig::UdpClient_Get_LocalIP()
{
    CDvmData *pUdpClient = Set_UdpClient();
    return pUdpClient->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey);
}

//SerialMode_Get
CString CPpSttCommConfig::Serial_Get_port_number()
{
    CDvmData *pSerial = Set_Serial();
    return pSerial->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strPortNumKey);
}
CString CPpSttCommConfig::Serial_Get_baud_rate()
{
    CDvmData *pSerial = Set_Serial();
    return pSerial->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strBaudRateKey);
}
CString CPpSttCommConfig::Serial_Get_byte_size()
{
    CDvmData *pSerial = Set_Serial();
    return pSerial->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strByteSizeKey);
}
CString CPpSttCommConfig::Serial_Get_stop_bit()
{
    CDvmData *pSerial = Set_Serial();
    return pSerial->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strStopBitsKey);
}
CString CPpSttCommConfig::Serial_Get_parity()
{
    CDvmData *pSerial = Set_Serial();
    return pSerial->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strParityKey);
}

//MmsMode_Get
CString CPpSttCommConfig::MMS_Get_LocalIP()
{
    CDvmData *pMms = Set_MMS();
    return pMms->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey);
}
CString CPpSttCommConfig::MMS_Get_RemoteIP()
{
	CDvmData *pMms = Set_MMS();
	return pMms->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey);
}
CString CPpSttCommConfig::MMS_Get_EncryptKey()
{
    CDvmData *pMms = Set_MMS();
    return pMms->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptKeyKey);
}
CString CPpSttCommConfig::MMS_Get_EncryptPsw()
{
    CDvmData *pMms = Set_MMS();
    return pMms->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptPswKey);
}

//Cms_Get
CString CPpSttCommConfig::CMS_Get_LocalIP()
{
    CDvmData *pCms=Set_CMS();
    return pCms->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey);
}
CString CPpSttCommConfig::CMS_Get_EncryptKey()
{
    CDvmData *pCms=Set_CMS();
    return pCms->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptKeyKey);
}
CString CPpSttCommConfig::CMS_Get_EncryptPsw()
{
    CDvmData *pCms=Set_CMS();
    return pCms->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptPswKey);
}
CString CPpSttCommConfig::CMS_Get_RemoteIP()
{
    CDvmData *pCms=Set_CMS();
    return pCms->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey);
}

CString CPpSttCommConfig::CMS_Get_RemotePort()
{
    CDvmData *pCms=Set_CMS();
    return pCms->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey);
}

void CPpSttCommConfig::dvmdata_set_value(CDvmData *pData, BSTR bstrKey, const CString &strValue)
{
	CString strKey;
	strKey = bstrKey;
	pData->SetValue(strKey, strValue);
}

void CPpSttCommConfig::dvmdata_set_value(CDvmData *pData, BSTR bstrKey, long nValue)
{
	CString strKey;
	strKey = bstrKey;
	pData->SetValue(strKey, nValue);
}


BOOL CPpSttCommConfig::OpenCommConfigFile(const CString &strFile)
{
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	return bRet;
}

void CPpSttCommConfig::SaveCommConfigFile(const CString &strFile)
{
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value++;
	BOOL bRet = SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value--;
}

void CPpSttCommConfig::UpdateFilePath_UseAbs()
{
	CString strFolderPath,strFileName,strTmp;
	strFolderPath = _P_GetInstallPath();
	strFolderPath += _T("e-Protocol/Template/");
	strFileName = "";
	GetDataValue(XPARA_ID_PPXMLFILE,strFileName);

	if (!strFileName.IsEmpty())
	{
		strTmp = strFolderPath + strFileName;

		if (IsFileExist(strTmp))
		{
			SetDataValue(XPARA_ID_PPXMLFILE,strTmp);
		}
	}

	strFolderPath = _P_GetInstallPath();
	strFolderPath += _T("e-Protocol/Library/");
	strFileName = "";
	GetDataValue(XPARA_ID_DVMFILE,strFileName);

	if (!strFileName.IsEmpty())
	{
		strTmp = strFolderPath + strFileName;

		if (IsFileExist(strTmp))
		{
			SetDataValue(XPARA_ID_DVMFILE,strTmp);
		}
	}
}


//////////////////////////////////////////////////////////////////////////
CPpSttCommConfigs::CPpSttCommConfigs()
{

}

CPpSttCommConfigs::~CPpSttCommConfigs()
{

}

BOOL CPpSttCommConfigs::OpenCommConfigsFile(const CString &strFile)
{
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	return bRet;
}

void CPpSttCommConfigs::SaveCommConfigsFile(const CString &strFile)
{

}



//////////////////////////////////////////////////////////////////////////
CString File_SmartTestCommConfig_mms()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SmartTestCommConfig_mms.xml");

	return strFile;
}

CString File_SmartTestCommConfig_cms()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SmartTestCommConfig_cms.xml");

	return strFile;
}

CString File_SmartTestCommConfig_pp()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SmartTestCommConfig_pp.xml");

	return strFile;
}

