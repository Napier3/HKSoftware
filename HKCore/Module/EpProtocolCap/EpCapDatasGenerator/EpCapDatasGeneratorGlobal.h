//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapDatasGeneratorGlobal.h

#pragma once

#include "ExBaseList.h"

#define ECGCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define ECGCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define ECGCLASSID_CEPCAPGENDATA       (ECGCLASSID_BASECLASS + 0X00000000)
#define ECGCLASSID_CEPCAPGENDATAS       (ECGCLASSID_EXLISTCLASS + 0X00000001)
#define ECGCLASSID_CEPCAPGENUDP       (ECGCLASSID_BASECLASS + 0X00000002)
#define ECGCLASSID_CEPCAPGENSERIAL       (ECGCLASSID_BASECLASS + 0X00000003)
#define ECGCLASSID_CEPCAPGENMNGR       (ECGCLASSID_EXLISTCLASS + 0X00000004)
#define ECGCLASSID_CEPCAPGENBASE       (ECGCLASSID_BASECLASS + 0X00000005)

class CEpCapDatasGeneratorXmlRWKeys : public CXmlRWKeys
{
protected:
	CEpCapDatasGeneratorXmlRWKeys();
	virtual ~CEpCapDatasGeneratorXmlRWKeys();
	static long g_nECGRef;

public:
	static CEpCapDatasGeneratorXmlRWKeys* g_pXmlKeys;
	static CEpCapDatasGeneratorXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEpCapGenBaseKey; //
	BSTR m_strCEpCapGenMngrKey; //gen-mngr
	BSTR m_strCEpCapGenSerialKey; //gen-serial
	BSTR m_strCEpCapGenUdpKey; //gen-udp
	BSTR m_strCEpCapGenDatasKey; //cap-datas
	BSTR m_strCEpCapGenDataKey; //cap-data
	BSTR m_strCapIDKey; //cap-id
	BSTR m_strCapTimeKey; //cap-tm
	BSTR m_strCapMsKey; //cap-ms
	BSTR m_strAddrSrcKey; //addr-src
	BSTR m_strAddrDstKey; //addr-dst
	BSTR m_strTypeKey; //type
	BSTR m_strDataKey; //data
	BSTR m_strLocalIPKey; //local-ip
	BSTR m_strLocalPortKey; //local-port
	BSTR m_strRemotePortKey; //remote-port
	BSTR m_strRemoteIPKey; //remote-ip
	BSTR m_strBaudRateKey; //baud-rate
	BSTR m_strDataBitKey; //data-bit
	BSTR m_strStopBitKey; //stop-bit
	BSTR m_strParityKey; //parity
	BSTR m_strPortKey; //port
	BSTR m_strFileKey; //gen-file

public:
	static BSTR CEpCapGenBaseKey()  {   return g_pXmlKeys->m_strCEpCapGenBaseKey;  }
	static BSTR CEpCapGenMngrKey()  {   return g_pXmlKeys->m_strCEpCapGenMngrKey;  }
	static BSTR CEpCapGenSerialKey()  {   return g_pXmlKeys->m_strCEpCapGenSerialKey;  }
	static BSTR CEpCapGenUdpKey()  {   return g_pXmlKeys->m_strCEpCapGenUdpKey;  }
	static BSTR CEpCapGenDatasKey()  {   return g_pXmlKeys->m_strCEpCapGenDatasKey;  }
	static BSTR CEpCapGenDataKey()  {   return g_pXmlKeys->m_strCEpCapGenDataKey;  }
	static BSTR CapIDKey()  {   return g_pXmlKeys->m_strCapIDKey;  }
	static BSTR CapTimeKey()  {   return g_pXmlKeys->m_strCapTimeKey;  }
	static BSTR CapMsKey()  {   return g_pXmlKeys->m_strCapMsKey;  }
	static BSTR AddrSrcKey()  {   return g_pXmlKeys->m_strAddrSrcKey;  }
	static BSTR AddrDstKey()  {   return g_pXmlKeys->m_strAddrDstKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR DataKey()  {   return g_pXmlKeys->m_strDataKey;  }
	static BSTR LocalIPKey()  {   return g_pXmlKeys->m_strLocalIPKey;  }
	static BSTR LocalPortKey()  {   return g_pXmlKeys->m_strLocalPortKey;  }
	static BSTR RemotePortKey()  {   return g_pXmlKeys->m_strRemotePortKey;  }
	static BSTR RemoteIPKey()  {   return g_pXmlKeys->m_strRemoteIPKey;  }
	static BSTR BaudRateKey()  {   return g_pXmlKeys->m_strBaudRateKey;  }
	static BSTR DataBitKey()  {   return g_pXmlKeys->m_strDataBitKey;  }
	static BSTR StopBitKey()  {   return g_pXmlKeys->m_strStopBitKey;  }
	static BSTR ParityKey()  {   return g_pXmlKeys->m_strParityKey;  }
	static BSTR PortKey()  {   return g_pXmlKeys->m_strPortKey;  }
	static BSTR FileKey()  {   return g_pXmlKeys->m_strFileKey;  }
};



class CEpCapDatasGeneratorConstGlobal
{
private:
	CEpCapDatasGeneratorConstGlobal();
	virtual ~CEpCapDatasGeneratorConstGlobal();

public:
	static CEpCapDatasGeneratorConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CEpCapDatasGeneratorConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
