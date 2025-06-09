#ifndef DEVICEMODELXMLKEYS
#define DEVICEMODELXMLKEYS

#include "../../../../module/baseclass/baseobject.h"
#include "../PpGlobalDefine.h"
#include "DeviceClassIDDefine.h"
#include "../../../../Module/DataMngr/DataMngrGlobal.h"

class CDeviceModelXmlKeys :public CDataMngrXmlRWKeys  //CXmlRWKeys
{
public:
	CDeviceModelXmlKeys();
	virtual ~CDeviceModelXmlKeys(){};

public:
	static CDeviceModelXmlKeys* g_pXmlRWKeys;
	static CDeviceModelXmlKeys* Create();
	static void Release();
	static long g_nProtocolXmlRWKeysRef;

public:
	//ttag
	BSTR m_strTagKey;
	BSTR m_strTagsKey;
	BSTR m_strIsKeyKey;
	BSTR m_strDataTypeKey;
	BSTR m_strTagValueKey;
	BSTR m_strDataTypeKey_String;
	BSTR m_strDataTypeKey_Double;
	BSTR m_strDataTypeKey_Long;
	BSTR m_strCtrlTypeKey;
	BSTR m_strCtrlTypeKey_Edit;//L"Edit";
	BSTR m_strCtrlTypeKey_CmbUn;//L"CmbUn";
	BSTR m_strCtrlTypeKey_CmbIn;//L"CmbIn";
	BSTR m_strCtrlTypeKey_CmbFn;//L"CmbFn";

	BSTR m_strDmDataTag_Name;
	BSTR m_strDmDataTag_ID;
	BSTR m_strDmDataTag_Index;
	BSTR m_strDmDataTag_ItemIndex;
	BSTR m_strDmDataTag_Unit;
	BSTR m_strDmDataTag_Value;
	BSTR m_strDmDataTag_Change;


	//////////////////////////////////////////////////////////////////////////
	//设备数据模型模板
	BSTR m_strDeviceModelDefineKey;
	BSTR m_strDeviceModelTemplateKey;
	BSTR m_strDeviceModelTemplatesKey;
	BSTR m_strNodeTypeKey;
	BSTR m_strMin;
	BSTR m_strMax;
	BSTR m_strRemark;
	BSTR m_strDevcieDefineKey;
	BSTR m_strDeviceNodeDefineKey;
	BSTR m_strDeviceNodeDataDefineKey;
	BSTR m_strMaxOccursKey;
	BSTR m_strTemplateFileKey;


	//////////////////////////////////////////////////////////////////////////
	//设备数据
	BSTR m_strDeviceModelKey;
	
	//设备
	BSTR m_strDeviceKey;
	BSTR m_strDevicesKey;
	BSTR m_strTemplateFile;
	BSTR m_strDeviceNodeKey;
	BSTR m_strDeviceNodeDataKey;

	//设备节点属性
	BSTR m_strModel;//model
	BSTR m_strCpuAddr;//addr
	BSTR m_strUNom;//UNom
	BSTR m_strINom;//INom
	BSTR m_strFNom;//FNom
	BSTR m_strCPU;//CPU
	BSTR m_strYC;//YC
	BSTR m_strYX;//YX
	BSTR m_strYK;//YK
	BSTR m_strGroupID;//GroupID
	BSTR m_strIndex;//index
	BSTR m_strRcvspt; //rcv-spt
	BSTR m_strSndspt; //snd-spt
	BSTR m_strValue; //value
	BSTR m_strBoardNumber; //boardnumber
	BSTR m_strSelect; //select
	BSTR m_strUnitKey;
	BSTR m_strChangeKey;

	//通讯配置
	BSTR m_strCmmConfigKey;
	BSTR m_strSerialKey;
	BSTR m_strNetKey;
	BSTR m_strMmsKey;
	BSTR m_strCmsKey;

	BSTR m_strTcpServerKey;
	BSTR m_strTcpClientKey;
	BSTR m_strUdpServerKey;
	BSTR m_strUdpClientKey;

	BSTR m_strPortNumKey;
	BSTR m_strBaudRateKey;
	BSTR m_strByteSizeKey;
	BSTR m_strStopBitsKey;
	BSTR m_strParityKey;
	BSTR m_strLocalIPKey;
	BSTR m_strLocalPortKey;
	BSTR m_strRemotePortKey;
	BSTR m_strRemoteIPKey;
	BSTR m_strOnConnectKey;
	BSTR m_strMulticastIPKey;
	BSTR m_strMulticastPortKey;
	BSTR m_strUseBroadcastKey;
	BSTR m_strClientIPKey;
	BSTR m_strEncryptPswKey; //PSW
	BSTR m_strEncryptKeyKey; //KEY

	BSTR m_strSendTimeout;
	BSTR m_strReceiveTimeout;

	BSTR m_strGroup;
	BSTR m_strItemIndex;

	BSTR m_strYT;
	BSTR m_strSet;

public:
	static BSTR DmDataTag_Name()		    {    return g_pXmlRWKeys->m_strDmDataTag_Name;	}
	static BSTR DmDataTag_ID()		            {    return g_pXmlRWKeys->m_strDmDataTag_ID;	};
	static BSTR DmDataTag_Index()		    {    return g_pXmlRWKeys->m_strDmDataTag_Index;	};
	static BSTR DmDataTag_ItemIndex()		{    return g_pXmlRWKeys->m_strDmDataTag_ItemIndex;	};
	static BSTR DmDataTag_Unit()		{    return g_pXmlRWKeys->m_strDmDataTag_Unit;	};
	static BSTR DmDataTag_Value()		{    return g_pXmlRWKeys->m_strDmDataTag_Value;	};
	static BSTR DmDataTag_Change()		{    return g_pXmlRWKeys->m_strDmDataTag_Change;	};

};
#endif
