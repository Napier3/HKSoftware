//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapConfigGlobal.h

#pragma once

#include "ExBaseList.h"

#define ECCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00040000)
#define ECCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00040000)

#define ECCLASSID_CEPCAPCONFIG       (ECCLASSID_EXLISTCLASS + 0X00000000)
#define ECCLASSID_CEPCAPNETCONFIG       (ECCLASSID_EXLISTCLASS + 0X00000001)
#define ECCLASSID_CEPCAPNETGROUP       (ECCLASSID_EXLISTCLASS + 0X00000002)
#define ECCLASSID_CEPCAPNETDEVICE       (ECCLASSID_BASECLASS + 0X00000003)
#define ECCLASSID_CEPCAPDIRS       (ECCLASSID_EXLISTCLASS + 0X00000004)
#define ECCLASSID_CEPCAPDIR       (ECCLASSID_BASECLASS + 0X00000005)
#define ECCLASSID_CEPCAPSERIALCONFIG       (ECCLASSID_EXLISTCLASS + 0X00000006)
#define ECCLASSID_CEPCAPSERIALGROUP       (ECCLASSID_EXLISTCLASS + 0X00000007)
#define ECCLASSID_CEPCAPSERIALDEVICE       (ECCLASSID_BASECLASS + 0X00000008)
#define ECCLASSID_CEPCAPNETCARD       (ECCLASSID_EXLISTCLASS + 0X00000009)

class CEpCapConfigXmlRWKeys : public CXmlRWKeys
{
protected:
	CEpCapConfigXmlRWKeys();
	virtual ~CEpCapConfigXmlRWKeys();
	static long g_nECRef;

public:
	static CEpCapConfigXmlRWKeys* g_pXmlKeys;
	static CEpCapConfigXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEpCapNetCardKey; //net-card
	BSTR m_strCEpCapSerialDeviceKey; //device
	BSTR m_strCEpCapSerialGroupKey; //group
	BSTR m_strCEpCapSerialConfigKey; //serial-config
	BSTR m_strCEpCapDirKey; //dir
	BSTR m_strCEpCapDirsKey; //dirs
	BSTR m_strCEpCapNetDeviceKey; //device
	BSTR m_strCEpCapNetGroupKey; //group
	BSTR m_strCEpCapNetConfigKey; //net-config
	BSTR m_strCEpCapConfigKey; //ep-cap-config
	BSTR m_strFileKey; //file
	BSTR m_strTcpKey; //tcp
	BSTR m_strUdpKey; //udp
	BSTR m_strIndexKey; //index
	BSTR m_strIPKey; //ip
	BSTR m_strProtocolKey; //protocol
	BSTR m_strValueKey; //value
	BSTR m_strIndex1Key; //index1
	BSTR m_strIndex2Key; //index2
	BSTR m_strComIDKey; //com-id

public:
	static BSTR CEpCapNetCardKey()  {   return g_pXmlKeys->m_strCEpCapNetCardKey;  }
	static BSTR CEpCapSerialDeviceKey()  {   return g_pXmlKeys->m_strCEpCapSerialDeviceKey;  }
	static BSTR CEpCapSerialGroupKey()  {   return g_pXmlKeys->m_strCEpCapSerialGroupKey;  }
	static BSTR CEpCapSerialConfigKey()  {   return g_pXmlKeys->m_strCEpCapSerialConfigKey;  }
	static BSTR CEpCapDirKey()  {   return g_pXmlKeys->m_strCEpCapDirKey;  }
	static BSTR CEpCapDirsKey()  {   return g_pXmlKeys->m_strCEpCapDirsKey;  }
	static BSTR CEpCapNetDeviceKey()  {   return g_pXmlKeys->m_strCEpCapNetDeviceKey;  }
	static BSTR CEpCapNetGroupKey()  {   return g_pXmlKeys->m_strCEpCapNetGroupKey;  }
	static BSTR CEpCapNetConfigKey()  {   return g_pXmlKeys->m_strCEpCapNetConfigKey;  }
	static BSTR CEpCapConfigKey()  {   return g_pXmlKeys->m_strCEpCapConfigKey;  }
	static BSTR FileKey()  {   return g_pXmlKeys->m_strFileKey;  }
	static BSTR TcpKey()  {   return g_pXmlKeys->m_strTcpKey;  }
	static BSTR UdpKey()  {   return g_pXmlKeys->m_strUdpKey;  }
	static BSTR IndexKey()  {   return g_pXmlKeys->m_strIndexKey;  }
	static BSTR IPKey()  {   return g_pXmlKeys->m_strIPKey;  }
	static BSTR ProtocolKey()  {   return g_pXmlKeys->m_strProtocolKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR Index1Key()  {   return g_pXmlKeys->m_strIndex1Key;  }
	static BSTR Index2Key()  {   return g_pXmlKeys->m_strIndex2Key;  }
	static BSTR ComIDKey()  {   return g_pXmlKeys->m_strComIDKey;  }
};



class CEpCapConfigConstGlobal
{
private:
	CEpCapConfigConstGlobal();
	virtual ~CEpCapConfigConstGlobal();

public:
	static CEpCapConfigConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CEpCapConfigConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
