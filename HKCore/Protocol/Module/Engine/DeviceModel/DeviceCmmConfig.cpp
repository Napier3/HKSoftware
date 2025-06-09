#include "StdAfx.h"
#include "DeviceCmmConfig.h"
#include "../ProtocolXmlRWKeys.h"
#include "../../../../Module/API/FileApi.h"
#include "../../../../Module/API/GlobalConfigApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDeviceCmmConfig::CDeviceCmmConfig(void)
{

	m_strName = "DeviceCmmConfig";
	m_strID = m_strName;


}

CDeviceCmmConfig::~CDeviceCmmConfig(void)
{
	
}

//基本方法
void CDeviceCmmConfig::Init()
{

}

void CDeviceCmmConfig::InitAfterRead()
{
	
}

//串行化
long CDeviceCmmConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CDeviceCmmConfig::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);
	return 0;
}


long CDeviceCmmConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}


//编辑
BOOL CDeviceCmmConfig::IsEqualOwn(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CDeviceCmmConfig::CopyOwn(CBaseObject* pDest)
{
	CExBaseObject::CopyOwn(pDest);
	return TRUE;
}

CBaseObject* CDeviceCmmConfig::Clone()
{
	CDeviceCmmConfig *pNew = new CDeviceCmmConfig();
	
	Copy(pNew);

	return pNew;
}


//创建子对象
CExBaseObject* CDeviceCmmConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return NULL;
}

CExBaseObject* CDeviceCmmConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew = NULL;

	if (strClassID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strSerialKey)
	{
		pNew = new CCmmSerialConfig();
	}
	else if (strClassID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strNetKey)
	{
		pNew = new CCmmNetConfig();
	}
	else if (strClassID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMmsKey)
	{
		pNew = new CCmmMmsConfig();
	}
	else
	{

	}

	if (pNew != NULL)
	{
		pNew->m_strName = strClassID;
		pNew->m_strID = strClassID;
	}

	return pNew;
}

#ifndef _DeviceCmmConfig_with_no_pptemplate
BOOL CDeviceCmmConfig::OpenPpTemplateXmlFile(const CString &strFile, CString &strDeviceModelFile,const long &nXmlRWType)
{
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(strFile, nXmlRWType);

	if (pRWDoc == NULL)
	{
		return FALSE;
	}

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();

	xml_GetAttibuteValue(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDeviceModelKey, *pDocRoot, strDeviceModelFile);

	CXmlRWNodeBase *pNodeConfig = pDocRoot->GetChildNode(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey);

	if (pNodeConfig != NULL)
	{
		XmlRead(*pNodeConfig, CDeviceModelXmlKeys::g_pXmlRWKeys);
	}

	delete pRWDoc;

	return pNodeConfig != NULL;

// 	MSXML2::IXMLDOMNodePtr oDocRoot = oDoc->GetdocumentElement();
// 
// 	//读设备数据模型文件
// 	_bstr_t bstrDeviceModelFileKey;// = L"/pp-template/@device-mode";
// 	CString strTemp;
// 	strTemp.Format(_T("/%s/@%s"), CProtocolXmlRWKeys::g_pXmlRWKeys->m_strTemplateKey
// 		, CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDeviceModelKey);
// 	bstrDeviceModelFileKey = strTemp;
// 	
// 	MSXML2::IXMLDOMNodePtr oDeviceModelFile = NULL;
// 	oDeviceModelFile = oDocRoot->selectSingleNode(bstrDeviceModelFileKey);
// 	ASSERT (oDeviceModelFile != NULL);
// 
// 	if (oDeviceModelFile != NULL)
// 	{
// 		_bstr_t bstrText = oDeviceModelFile->Gettext();
// 		strDeviceModelFile = bstrText.copy();
// 	}
// 
// 	//读通讯配置信息
// 	//bstrDeviceCmmConfigKey = L"/pp-template/comm-channel";
// 	strTemp.Format(_T("/%s/%s"), CProtocolXmlRWKeys::g_pXmlRWKeys->m_strTemplateKey
// 		, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey);
// 	_bstr_t bstrDeviceCmmConfigKey = strTemp;
// 
// 	MSXML2::IXMLDOMNodePtr oCmmConfig = NULL;
// 	oCmmConfig = oDocRoot->selectSingleNode(bstrDeviceCmmConfigKey);
// 
// 	ASSERT(oCmmConfig != NULL);
// 
// 	if(oCmmConfig == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	XmlRead(oCmmConfig, CDeviceModelXmlKeys::g_pXmlRWKeys);

	return TRUE;
}
#endif

	/************************************************************************/
	/* 2011-01-13 添加 用于点表编辑
	*/
	/************************************************************************/
long CDeviceCmmConfig::InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent)
{
	return 0;
}

CExBaseObject* CDeviceCmmConfig::GetChildByClassID(UINT nClassID)
{
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = GetHeadPosition();
	UINT nID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject*)GetNext(pos);
		nID = p->GetClassID();

		if (nClassID == nID)
		{
			pFind = p;
			break;
		}

		if (nID == DMCLASSID_NET_CONFIG)
		{
			pFind = ((CCmmNetConfig*)p)->GetChildByClassID(nClassID);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}

CCmmSerialConfig* CDeviceCmmConfig::AddConfigSerial()
{
	CCmmSerialConfig *pSerial = GetConfigSerial();

	if (pSerial != NULL)
	{
		return pSerial;
	}

	ChangeToSerialMode();

	return GetConfigSerial();
}

CCmmMmsConfig* CDeviceCmmConfig::AddConfigMms()
{
	CCmmMmsConfig *pMms = GetConfigMms();

	if (pMms != NULL)
	{
		return pMms;
	}

	ChangeToMmsMode();

	return GetConfigMms();
}

CCmmTcpServerConfig* CDeviceCmmConfig::AddConfigTcpServer()
{
	ChangeToNetMode();

	CCmmTcpServerConfig *pCfg = GetConfigTcpServer();

	if (pCfg == NULL)
	{
		CCmmNetConfig *pNetCfg = GetNetConfig();
		pCfg = pNetCfg->AddConfigTcpServer();
	}

	return pCfg;
}

CCmmTcpClientConfig* CDeviceCmmConfig::AddConfigTcpClient()
{
	ChangeToNetMode();

	CCmmTcpClientConfig *pCfg = GetConfigTcpClient();

	if (pCfg == NULL)
	{
		CCmmNetConfig *pNetCfg = GetNetConfig();
		pCfg = pNetCfg->AddConfigTcpClient();
	}

	return pCfg;
}

CCmmUdpServerConfig* CDeviceCmmConfig::AddConfigUdpServer()
{
	ChangeToNetMode();

	CCmmUdpServerConfig *pCfg = GetConfigUdpServer();

	if (pCfg == NULL)
	{
		CCmmNetConfig *pNetCfg = GetNetConfig();
		pCfg = pNetCfg->AddConfigUdpServer();
	}

	return pCfg;
}

CCmmUdpClientConfig* CDeviceCmmConfig::AddConfigUdpClient()
{
	ChangeToNetMode();

	CCmmUdpClientConfig *pCfg = GetConfigUdpClient();

	if (pCfg == NULL)
	{
		CCmmNetConfig *pNetCfg = GetNetConfig();
		pCfg = pNetCfg->AddConfigUdpClient();
	}

	return pCfg;
}

void CDeviceCmmConfig::ChangeToSerialMode()
{
	CExBaseObject *pHead = GetHead();

	if (pHead != NULL)
	{
		if (pHead->GetClassID() == DMCLASSID_CMM_SERIAL_CONFIG)
		{
			return;
		}

		DeleteAll();
	}

	pHead = new CCmmSerialConfig();
	AddNewChild(pHead);
}

void CDeviceCmmConfig::ChangeToMmsMode()
{
	CExBaseObject *pHead = GetHead();

	if (pHead != NULL)
	{
		if (pHead->GetClassID() == DMCLASSID_CMM_MMS_CONFIG)
		{
			return;
		}

		DeleteAll();
	}

	pHead = new CCmmMmsConfig();
	AddNewChild(pHead);
}

void CDeviceCmmConfig::ChangeToNetMode()
{
	CExBaseObject *pHead = GetHead();

	if (pHead != NULL)
	{
		if (pHead->GetClassID() == DMCLASSID_NET_CONFIG)
		{
			return;
		}

		DeleteAll();
	}

	pHead = new CCmmNetConfig();
	AddNewChild(pHead);
}

CCmmNetConfig* CDeviceCmmConfig::GetNetConfig()
{
	CExBaseObject *pHead = GetHead();

	if (pHead != NULL)
	{
		if (pHead->GetClassID() == DMCLASSID_NET_CONFIG)
		{
			return (CCmmNetConfig*)pHead;
		}
	}

	return NULL;
}

CCmmSerialConfig* CDeviceCmmConfig::GetConfigSerial()
{
	CCmmSerialConfig *pSerial = NULL;
	CExBaseObject *pHead = GetHead();

	if (pHead != NULL)
	{
		if (pHead->GetClassID() == DMCLASSID_CMM_SERIAL_CONFIG)
		{
			pSerial = (CCmmSerialConfig*)pHead;
		}
	}

	return pSerial;
}

CCmmMmsConfig* CDeviceCmmConfig::GetConfigMms()
{
	CCmmMmsConfig *pMms = NULL;
	CExBaseObject *pHead = GetHead();

	if (pHead != NULL)
	{
		if (pHead->GetClassID() == DMCLASSID_CMM_MMS_CONFIG)
		{
			pMms = (CCmmMmsConfig*)pHead;
		}
	}

	return pMms;
}

CCmmNetConfig* CDeviceCmmConfig::GetConfigNet()
{
	CCmmNetConfig *pNetConfig = GetNetConfig();
	//ASSERT (pNetConfig != NULL);   //shaolei  注释于20210511

	return pNetConfig;
}

CCmmTcpServerConfig* CDeviceCmmConfig::GetConfigTcpServer()
{
	CCmmNetConfig *pNetConfig = GetNetConfig();
	ASSERT (pNetConfig != NULL);

	if (pNetConfig == NULL)
	{
		return NULL;
	}

	return pNetConfig->GetConfigTcpServer();
}

CCmmTcpClientConfig* CDeviceCmmConfig::GetConfigTcpClient()
{
	CCmmNetConfig *pNetConfig = GetNetConfig();
	ASSERT (pNetConfig != NULL);

	if (pNetConfig == NULL)
	{
		return NULL;
	}

	return pNetConfig->GetConfigTcpClient();
}

CCmmUdpServerConfig* CDeviceCmmConfig::GetConfigUdpServer()
{
	CCmmNetConfig *pNetConfig = GetNetConfig();
	ASSERT (pNetConfig != NULL);

	if (pNetConfig == NULL)
	{
		return NULL;
	}

	return pNetConfig->GetConfigUdpServer();
}

CCmmUdpClientConfig* CDeviceCmmConfig::GetConfigUdpClient()
{
	CCmmNetConfig *pNetConfig = GetNetConfig();
	ASSERT (pNetConfig != NULL);

	if (pNetConfig == NULL)
	{
		return NULL;
	}

	return pNetConfig->GetConfigUdpClient();
}

void CDeviceCmmConfig::DeleteConfigTcpServer()
{
	CCmmNetConfig* pNetCfg = GetNetConfig();

	if (pNetCfg != NULL)
	{
		pNetCfg->DeleteConfigTcpServer();
	}
}

void CDeviceCmmConfig::DeleteConfigTcpClient()
{
	CCmmNetConfig* pNetCfg = GetNetConfig();

	if (pNetCfg != NULL)
	{
		pNetCfg->DeleteConfigTcpClient();
	}
}

void CDeviceCmmConfig::DeleteConfigUdpServer()
{
	CCmmNetConfig* pNetCfg = GetNetConfig();

	if (pNetCfg != NULL)
	{
		pNetCfg->DeleteConfigUdpServer();
	}
}

void CDeviceCmmConfig::DeleteConfigUdpClient()
{
	CCmmNetConfig* pNetCfg = GetNetConfig();

	if (pNetCfg != NULL)
	{
		pNetCfg->DeleteConfigUdpClient();
	}
}

void CDeviceCmmConfig::InitBy(CDeviceCmmConfig *pCmmCfg)
{
	DeleteAll();
	AppendCloneEx(*pCmmCfg);
}

void CDeviceCmmConfig::InitByOnlyConfig(BSTR strCmmConfig)
{
	CDeviceCmmConfig oCmmConfig;
	oCmmConfig.SetXml(strCmmConfig, CDeviceModelXmlKeys::g_pXmlRWKeys);
	InitByOnlyConfig(&oCmmConfig);
}


void CDeviceCmmConfig::InitByOnlyConfig(CDeviceCmmConfig *pCmmCfg)
{
	InitByOnlyConfig(this, pCmmCfg);
}

void CDeviceCmmConfig::InitByOnlyConfig(CExBaseList *pDestCmmCfg, CExBaseList *pSrcCmmCfg)
{
	POS posDest = pDestCmmCfg->GetHeadPosition();
	CExBaseObject *pDest = NULL;
	CExBaseObject *pSrc = NULL;

	while (posDest != NULL)
	{
		pDest = pDestCmmCfg->GetNext(posDest);
		pSrc = pSrcCmmCfg->FindByClassID(pDest->GetClassID());

		if (pSrc != NULL)
		{
			pSrc->CopyOwn(pDest);

			if (pDest->IsBaseList())
			{
				InitByOnlyConfig((CExBaseList*)pDest, (CExBaseList*)pSrc);
			}
		}
	}
}


void CDeviceCmmConfig::SelectCmmCfgChannel(CExBaseList &listCmmCfg)
{
	SelectCmmCfgChannel(this, listCmmCfg);
}

void CDeviceCmmConfig::SelectCmmCfgChannel(CExBaseList *pListSrc, CExBaseList &listCmmCfg)
{
	POS pos = pListSrc->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pListSrc->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DMCLASSID_CMM_UDP_SERVER_CONFIG
			|| nClassID == DMCLASSID_CMM_UDP_CLIENT_CONFIG
			|| nClassID == DMCLASSID_CMM_TCP_CLIENT_CONFIG
			|| nClassID == DMCLASSID_CMM_TCP_SERVER_CONFIG
			|| nClassID == DMCLASSID_CMM_SERIAL_CONFIG
			|| nClassID == DMCLASSID_CMM_MMS_CONFIG)
		{
			listCmmCfg.AddTail(p);
		}
		else
		{
			if (p->IsBaseList(nClassID))
			{
				SelectCmmCfgChannel((CExBaseList*)p, listCmmCfg);
			}
		}
	}
}

/*
<group id="omm-config" >  【通信地址设置】
    <data id="serial" value=""/>【串口】
        <value id="port_number" value="4"/>
        <value id="baud-rate" value="4800"/>
        <value id="byte-size" value="8"/>
        <value id="stop-bit" value="2"/>
        <value id="parity" value="0"/>
        <value id="port_number" value="4"/>
    </data>
    <data id="tcp-server" value=""/>
        <value id="local-ip" value="127.0.0.1"/>
        <value id="local-port" value="2404"/>
    </data>
    <data id="tcp-client" value=""/>
        <value id="local-ip" value="127.0.0.1"/>
        <value id="local-port" value="0"/>
        <value id="remote-ip" value="100.100.102.1"/>
        <value id="remote-port" value="2404"/>
    </data>
    <data id="udp-server" value=""/>
        <value id="local-ip" value="127.0.0.1"/>
        <value id="local-port" value="2404"/>
        <value id="use-broadcast" value="0"/>
        <value id="multicast-ip" value="0.0.0.0"/>
        <value id="multicast-port" value="0"/>
    </data>
    <data id="udp-client" value=""/>
        <value id="local-ip" value="127.0.0.1"/>
        <value id="local-port" value="2404"/>
        <value id="remote-ip" value="100.100.102.1"/>
        <value id="remote-port" value="2404"/>
        <value id="use-broadcast" value="0"/>
        <value id="multicast-ip" value="0.0.0.0"/>
        <value id="multicast-port" value="0"/>
    </data>
</group>
*/
 BOOL CDeviceCmmConfig::InitCmmConfig(CDataGroup *pGroup)
 {
     DeleteAll();
    CDvmData *pData = NULL;
    POS pos = pGroup->GetHeadPosition();

    while (pos != NULL)
    {
        pData = (CDvmData*)pGroup->GetNext(pos);

        if (pData->m_strID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpClientKey)
        {
            InitCmmConfig_Net_TcpClient(pData);
        }
        else   if (pData->m_strID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpServerKey)
        {
             InitCmmConfig_Net_TcpServer(pData);
        }
        else   if (pData->m_strID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpClientKey)
        {
             InitCmmConfig_Net_UdpClient(pData);
        }
        else   if (pData->m_strID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpServerKey)
        {
             InitCmmConfig_Net_UdpServer(pData);
        }
    }

	return TRUE;
 }

 /*
<data id="tcp-client" value=""/>
    <value id="local-ip" value="127.0.0.1"/>
    <value id="local-port" value="0"/>
    <value id="remote-ip" value="100.100.102.1"/>
    <value id="remote-port" value="2404"/>
</data>
*/
 BOOL CDeviceCmmConfig::InitCmmConfig_Net_TcpClient(CDvmData *pData)
 {
     CCmmTcpClientConfig *pTcpClient = AddConfigTcpClient();

     pData->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey,  pTcpClient->m_strLocalIP);
     pData->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey,  pTcpClient->m_nLocalPort);
     pData->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey,  pTcpClient->m_strRemoteIP);
     pData->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey,  pTcpClient->m_nRemotePort);

     return TRUE;
 }

 /*
<data id="tcp-server" value=""/>
    <value id="local-ip" value="127.0.0.1"/>
    <value id="local-port" value="0"/>
</data>
*/
 BOOL CDeviceCmmConfig::InitCmmConfig_Net_TcpServer(CDvmData *pData)
 {
     return TRUE;
 }

 BOOL CDeviceCmmConfig::InitCmmConfig_Net_UdpClient(CDvmData *pData)
 {
     return TRUE;
 }

 BOOL CDeviceCmmConfig::InitCmmConfig_Net_UdpServer(CDvmData *pData)
 {
     return TRUE;
 }

 BOOL CDeviceCmmConfig::InitCmmConfig_Serial(CDvmData *pData)
 {
     return TRUE;
 }

 //2023-4-18 lijunqing
 void CDeviceCmmConfig::SetPort(long nPort)
 {
	SetPort(this, nPort);
 }

 void CDeviceCmmConfig::SetPort(CExBaseList *pListSrc, long nPort)
 {
	 POS pos = pListSrc->GetHeadPosition();
	 CExBaseObject *p = NULL;
	 UINT nClassID = 0;

	 while (pos != NULL)
	 {
		 p = (CExBaseObject *)pListSrc->GetNext(pos);
		 nClassID = p->GetClassID();

		 if (nClassID == DMCLASSID_CMM_UDP_SERVER_CONFIG
			 || nClassID == DMCLASSID_CMM_UDP_CLIENT_CONFIG
			 || nClassID == DMCLASSID_CMM_TCP_CLIENT_CONFIG
			 || nClassID == DMCLASSID_CMM_TCP_SERVER_CONFIG
			 || nClassID == DMCLASSID_CMM_SERIAL_CONFIG
			 || nClassID == DMCLASSID_CMM_MMS_CONFIG)
		 {
			((CCmmConfigBase*)p)->SetPort(nPort);
		 }
		 else
		 {
			 SetPort((CExBaseList*)p, nPort);
		 }
	 }
 }

//////////////////////////////////////////////////////////////////////////

CString pp_GetDeviceCmmCfgFile(const CString &strDeviceFile)
{
	CString strCmmCfgFile;

	if (!IsFileExist(strDeviceFile))
	{
		strCmmCfgFile =_P_GetLibraryPath();
		strCmmCfgFile += strDeviceFile;
	}
	else
	{
		strCmmCfgFile = strDeviceFile;
	}

	strCmmCfgFile.Replace(_T(".xml"), _T("_CmmCfg.xml"));

	return strCmmCfgFile;
}
