//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapDeviceModelGlobal.h

#pragma once

#include "ExBaseList.h"

#define ECDMCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define ECDMCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define ECDMCLASSID_CECDMDATA       (ECDMCLASSID_BASECLASS + 0X00000000)
#define ECDMCLASSID_CECDMDATAS       (ECDMCLASSID_EXLISTCLASS + 0X00000001)
#define ECDMCLASSID_CECDMPROTOCOLADDR       (ECDMCLASSID_BASECLASS + 0X00000002)
#define ECDMCLASSID_CECDMPROTOCOLADDRS       (ECDMCLASSID_EXLISTCLASS + 0X00000003)
#define ECDMCLASSID_CEPCAPDEVICEMODEL       (ECDMCLASSID_EXLISTCLASS + 0X00000004)

class CEpCapDeviceModelXmlRWKeys : public CXmlRWKeys
{
protected:
	CEpCapDeviceModelXmlRWKeys();
	virtual ~CEpCapDeviceModelXmlRWKeys();
	static long g_nECDMRef;

public:
	static CEpCapDeviceModelXmlRWKeys* g_pXmlKeys;
	static CEpCapDeviceModelXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEpCapDeviceModelKey; //device-model
	BSTR m_strCEcdmProtocolAddrsKey; //protocol-addr
	BSTR m_strCEcdmProtocolAddrKey; //protocol-addr
	BSTR m_strCEcdmDatasKey; //epoto_datas
	BSTR m_strCEcdmDataKey; //data
	BSTR m_strUnitKey; //unit
	BSTR m_strDataTypeKey; //datatype
	BSTR m_strMinKey; //min
	BSTR m_strMaxKey; //max
	BSTR m_strDeadKey; //dead
	BSTR m_strIndexKey; //index
	BSTR m_strProtocolKey; //protocol
	BSTR m_strYxAddrKey; //yx-addr
	BSTR m_strYcAddrKey; //yc-addr
	BSTR m_strYtAddrKey; //yt-addr

public:
	static BSTR CEpCapDeviceModelKey()  {   return g_pXmlKeys->m_strCEpCapDeviceModelKey;  }
	static BSTR CEcdmProtocolAddrsKey()  {   return g_pXmlKeys->m_strCEcdmProtocolAddrsKey;  }
	static BSTR CEcdmProtocolAddrKey()  {   return g_pXmlKeys->m_strCEcdmProtocolAddrKey;  }
	static BSTR CEcdmDatasKey()  {   return g_pXmlKeys->m_strCEcdmDatasKey;  }
	static BSTR CEcdmDataKey()  {   return g_pXmlKeys->m_strCEcdmDataKey;  }
	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }
	static BSTR DataTypeKey()  {   return g_pXmlKeys->m_strDataTypeKey;  }
	static BSTR MinKey()  {   return g_pXmlKeys->m_strMinKey;  }
	static BSTR MaxKey()  {   return g_pXmlKeys->m_strMaxKey;  }
	static BSTR DeadKey()  {   return g_pXmlKeys->m_strDeadKey;  }
	static BSTR IndexKey()  {   return g_pXmlKeys->m_strIndexKey;  }
	static BSTR ProtocolKey()  {   return g_pXmlKeys->m_strProtocolKey;  }
	static BSTR YxAddrKey()  {   return g_pXmlKeys->m_strYxAddrKey;  }
	static BSTR YcAddrKey()  {   return g_pXmlKeys->m_strYcAddrKey;  }
	static BSTR YtAddrKey()  {   return g_pXmlKeys->m_strYtAddrKey;  }
};



class CEpCapDeviceModelConstGlobal
{
private:
	CEpCapDeviceModelConstGlobal();
	virtual ~CEpCapDeviceModelConstGlobal();

public:
	static CEpCapDeviceModelConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CEpCapDeviceModelConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
