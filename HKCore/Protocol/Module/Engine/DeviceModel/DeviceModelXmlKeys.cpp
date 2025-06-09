#include "stdafx.h"
#include "devicemodelxmlkeys.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDeviceModelXmlKeys* CDeviceModelXmlKeys::g_pXmlRWKeys = NULL;
long CDeviceModelXmlKeys::g_nProtocolXmlRWKeysRef = 0;


CDeviceModelXmlKeys* CDeviceModelXmlKeys::Create()
{
	if (g_pXmlRWKeys == NULL)
	{
		g_pXmlRWKeys = new CDeviceModelXmlKeys();
	
		if (CDataMngrXmlRWKeys::g_pXmlKeys == NULL)
		{
			CDataMngrXmlRWKeys::g_pXmlKeys = g_pXmlRWKeys;
		}
	}

	g_nProtocolXmlRWKeysRef++;

	return g_pXmlRWKeys;
}

void CDeviceModelXmlKeys::Release()
{
	g_nProtocolXmlRWKeysRef--;

	if (g_nProtocolXmlRWKeysRef == 0)
	{
		delete g_pXmlRWKeys;
		g_pXmlRWKeys = NULL;
	}
}


CDeviceModelXmlKeys::CDeviceModelXmlKeys()
{
	m_strDeviceModelKey = L"device-model";

	//tag
	m_strTagKey = L"tag";
	m_strTagsKey = L"tags";
	m_strIsKeyKey=L"iskey";
	m_strDataTypeKey=L"datatype";
	m_strTagValueKey = L"val";
	m_strDataTypeKey_String = L"string";
	m_strDataTypeKey_Double = L"double";
	m_strDataTypeKey_Long = L"long";
	m_strCtrlTypeKey = L"ctrl-type";
	m_strCtrlTypeKey_Edit = L"Edit";
	m_strCtrlTypeKey_CmbUn = L"CmbUn";
	m_strCtrlTypeKey_CmbIn = L"CmbIn";
	m_strCtrlTypeKey_CmbFn = L"CmbFn";

	m_strDmDataTag_Name         = L"name";
	m_strDmDataTag_ID              = L"id";
	m_strDmDataTag_Index         = L"index";
	m_strDmDataTag_ItemIndex  = L"item-index";
	m_strDmDataTag_Unit  = L"unit";
	m_strDmDataTag_Value  = L"value";
	m_strDmDataTag_Change  = L"change";


	//////////////////////////////////////////////////////////////////////////
	//设备数据模型模板
	m_strDeviceModelDefineKey = L"device-model-def";
	m_strDeviceModelTemplateKey = L"device-model-template";
	m_strDeviceModelTemplatesKey = L"device-model-templates";
	m_strNodeTypeKey = L"node-type";
	m_strMin=L"min";
	m_strMax=L"max";
	m_strRemark=L"remark";
	m_strDevcieDefineKey = L"device-model";
	m_strDeviceNodeDefineKey = L"dv-node";
	m_strDeviceNodeDataDefineKey = L"tdata";
	m_strMaxOccursKey = L"max-occurs";
	m_strTemplateFileKey = L"template-file";
	//////////////////////////////////////////////////////////////////////////
	//设备数据
	m_strDeviceModelKey = L"device-model";

	//设备
	m_strDeviceKey = L"device";
	m_strDevicesKey = L"devices";
	m_strTemplateFile = L"tempfile";
	m_strDeviceNodeKey = L"node";
	m_strDeviceNodeDataKey = L"data";

	//通讯配置
	m_strCmmConfigKey = L"comm-config";
	m_strSerialKey  = L"serial";
	m_strNetKey = L"net";
	m_strTcpServerKey  = L"tcp-server";
	m_strTcpClientKey  = L"tcp-client";
	m_strUdpServerKey  = L"udp-server";
	m_strUdpClientKey  = L"udp-client";
	m_strMmsKey  = L"mms";
	m_strCmsKey  = L"cms";

	m_strPortNumKey   = L"port_number";
	m_strBaudRateKey  = L"baud-rate";
	m_strByteSizeKey  = L"byte-size";
	m_strStopBitsKey  = L"stop-bit";
	m_strParityKey  = L"parity";
	m_strLocalIPKey  = L"local-ip";
	m_strLocalPortKey  = L"local-port";
	m_strRemotePortKey  = L"remote-port";
	m_strRemoteIPKey  = L"remote-ip";
	m_strOnConnectKey = L"onconnect";
	m_strMulticastIPKey = L"multicast-ip";
	m_strMulticastPortKey = L"multicast-port";
	m_strUseBroadcastKey = L"use-broadcast";
	m_strClientIPKey = L"client-ip";

	m_strSendTimeout = L"send-time-out";
	m_strReceiveTimeout = L"receive-time-out";

	m_strEncryptPswKey = L"PSW"; //PSW
	m_strEncryptKeyKey = L"KEY"; //KEY

	//设备节点属性
	m_strModel = L"model";
	m_strCpuAddr = L"addr";
	m_strUNom = L"UNom";
	m_strINom = L"INom";
	m_strFNom = L"FNom";
	m_strCPU = L"CPU";
	m_strYC = L"YC";
	m_strYX = L"YX";
	m_strYK = L"YK";
	m_strGroupID = L"GroupID";
	m_strIndex = L"index";
	m_strRcvspt = L"rcv-scpt";
	m_strSndspt = L"snd-scpt";
	m_strValue = L"value";
	m_strBoardNumber = L"boardnumber";
	m_strSelect = L"select";
	m_strUnitKey = L"unit";
	m_strChangeKey = L"change";


	m_strGroup	= L"GROUP";
	m_strItemIndex = L"item-index";

	m_strYT = L"YT";
	m_strSet = L"Set";
}
