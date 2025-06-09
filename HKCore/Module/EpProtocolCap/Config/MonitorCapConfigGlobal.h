//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MonitorCapConfigGlobal.h

#pragma once

#include "ExBaseList.h"

#define EMCCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define EMCCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define ECCLASSID_CMONITORCAPCONFIG       (EMCCLASSID_EXLISTCLASS + 0X00000000)
#define EMCCLASSID_CEMCSERIALSCONFIG       (EMCCLASSID_EXLISTCLASS + 0X00000001)
#define EMCCLASSID_CEMCSERIALCONFIG       (EMCCLASSID_BASECLASS + 0X00000002)
#define EMCCLASSID_CEMCNETSCONFIG       (EMCCLASSID_EXLISTCLASS + 0X00000003)
#define EMCCLASSID_CEMCNETCONFIG       (EMCCLASSID_BASECLASS + 0X00000004)
#define EMCCLASSID_CEMCNETDEVICES       (EMCCLASSID_EXLISTCLASS + 0X00000005)
#define EMCCLASSID_CEMCNETDEVICE       (EMCCLASSID_BASECLASS + 0X00000006)
#define EMCCLASSID_CEMCQUERYADDRMAP       (EMCCLASSID_BASECLASS + 0X00000007)
#define EMCCLASSID_CEMCQUERYADDRDIR       (EMCCLASSID_BASECLASS + 0X00000008)
#define EMCCLASSID_CEMCQUERYPROTOCOL       (EMCCLASSID_EXLISTCLASS + 0X00000009)
#define EMCCLASSID_CEMCQUERYPROTOCOLS       (EMCCLASSID_EXLISTCLASS + 0X0000000A)
#define EMCCLASSID_CEMCDEVICEMODELFILES       (EMCCLASSID_EXLISTCLASS + 0X0000000B)
#define EMCCLASSID_CEMCDEVICEMODELFILE       (EMCCLASSID_BASECLASS + 0X0000000C)
#define ECCLASSID_CMONITORQUERYCONFIG       (EMCCLASSID_EXLISTCLASS + 0X0000000D)
#define MNGRCLASSID_CEPCAPYCANALYSISITEM       (EMCCLASSID_BASECLASS + 0X00000000)
#define MNGRCLASSID_CEPCAPYCANALYSIS       (EMCCLASSID_EXLISTCLASS + 0X00000001)
#define MNGRCLASSID_CEPCAPYCANALYSISMNGR       (EMCCLASSID_EXLISTCLASS + 0X00000002)

class CMonitorCapConfigXmlRWKeys : public CXmlRWKeys
{
protected:
	CMonitorCapConfigXmlRWKeys();
	virtual ~CMonitorCapConfigXmlRWKeys();
	static long g_nEMCRef;

public:
	static CMonitorCapConfigXmlRWKeys* g_pXmlKeys;
	static CMonitorCapConfigXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEmcDeviceModelFileKey;
	BSTR m_strCEmcDeviceModelFilesKey;
	BSTR m_strCEmcQueryProtocolsKey; //protocols
	BSTR m_strCEmcQueryProtocolKey; //protocol
	BSTR m_strCEmcQueryAddrDirKey; //dir
	BSTR m_strCEmcQueryAddrMapKey; //addr-map
	BSTR m_strCEmcNetDeviceKey; //net-device
	BSTR m_strCEmcNetDevicesKey; //net-devices
	BSTR m_strCEmcNetConfigKey; //net
	BSTR m_strCEmcNetsConfigKey; //nets
	BSTR m_strCEmcSerialConfigKey; //serial
	BSTR m_strCEmcSerialsConfigKey; //serials
	BSTR m_strCMonitorCapConfigKey; //ep-cap-config
	BSTR m_strProtocolKey; //protocol
	BSTR m_strPortKey; //port
	BSTR m_strBaudRateKey; //baud-rate
	BSTR m_strByteSizeKey; //byte-size
	BSTR m_strStopBitsKey; //stop-bits
	BSTR m_strParityKey; //parity
	BSTR m_strUDPKey; //UDP
	BSTR m_strTCPKey; //TCP
	BSTR m_strOtherKey; //
	BSTR m_strSrcKey; //src
	BSTR m_strDestKey; //dest
	BSTR m_strDirKey; //dir
	BSTR m_strUseGeneratorKey; //use-generator
	BSTR m_strDvmFileKey; //dvm-file

	BSTR m_strCEpCapYcAnalysisMngrKey; //analysis-mngr
	BSTR m_strCEpCapYcAnalysisKey; //yc-analysis
	BSTR m_strCEpCapYcAnalysisItemKey; //item
	BSTR m_strItemIndexKey; //item-index
	BSTR m_strColorKey;  //protocol
	BSTR m_strDrawTypeKey;  //draw-type
	BSTR m_strFileKey;  //protocol

public:
	static BSTR CEpCapYcAnalysisMngrKey()  {   return g_pXmlKeys->m_strCEpCapYcAnalysisMngrKey;  }
	static BSTR CEpCapYcAnalysisKey()  {   return g_pXmlKeys->m_strCEpCapYcAnalysisKey;  }
	static BSTR CEpCapYcAnalysisItemKey()  {   return g_pXmlKeys->m_strCEpCapYcAnalysisItemKey;  }
	static BSTR ItemIndexKey()  {   return g_pXmlKeys->m_strItemIndexKey;  }
	static BSTR CEmcDeviceModelFileKey()  {   return g_pXmlKeys->m_strCEmcDeviceModelFileKey;  }
	static BSTR CEmcDeviceModelFilesKey()  {   return g_pXmlKeys->m_strCEmcDeviceModelFilesKey;  }
	static BSTR CEmcQueryProtocolsKey()  {   return g_pXmlKeys->m_strCEmcQueryProtocolsKey;  }
	static BSTR CEmcQueryProtocolKey()  {   return g_pXmlKeys->m_strCEmcQueryProtocolKey;  }
	static BSTR CEmcQueryAddrDirKey()  {   return g_pXmlKeys->m_strCEmcQueryAddrDirKey;  }
	static BSTR CEmcQueryAddrMapKey()  {   return g_pXmlKeys->m_strCEmcQueryAddrMapKey;  }
	static BSTR CEmcNetDeviceKey()  {   return g_pXmlKeys->m_strCEmcNetDeviceKey;  }
	static BSTR CEmcNetDevicesKey()  {   return g_pXmlKeys->m_strCEmcNetDevicesKey;  }
	static BSTR CEmcNetConfigKey()  {   return g_pXmlKeys->m_strCEmcNetConfigKey;  }
	static BSTR CEmcNetsConfigKey()  {   return g_pXmlKeys->m_strCEmcNetsConfigKey;  }
	static BSTR CEmcSerialConfigKey()  {   return g_pXmlKeys->m_strCEmcSerialConfigKey;  }
	static BSTR CEmcSerialsConfigKey()  {   return g_pXmlKeys->m_strCEmcSerialsConfigKey;  }
	static BSTR CMonitorCapConfigKey()  {   return g_pXmlKeys->m_strCMonitorCapConfigKey;  }
	static BSTR ProtocolKey()  {   return g_pXmlKeys->m_strProtocolKey;  }
	static BSTR PortKey()  {   return g_pXmlKeys->m_strPortKey;  }
	static BSTR BaudRateKey()  {   return g_pXmlKeys->m_strBaudRateKey;  }
	static BSTR ByteSizeKey()  {   return g_pXmlKeys->m_strByteSizeKey;  }
	static BSTR StopBitsKey()  {   return g_pXmlKeys->m_strStopBitsKey;  }
	static BSTR ParityKey()  {   return g_pXmlKeys->m_strParityKey;  }
	static BSTR UDPKey()  {   return g_pXmlKeys->m_strUDPKey;  }
	static BSTR TCPKey()  {   return g_pXmlKeys->m_strTCPKey;  }
	static BSTR SrcKey()  {   return g_pXmlKeys->m_strSrcKey;  }
	static BSTR DestKey()  {   return g_pXmlKeys->m_strDestKey;  }
	static BSTR DirKey()  {   return g_pXmlKeys->m_strDirKey;  }
	static BSTR DvmFileKey()  {   return g_pXmlKeys->m_strDvmFileKey;  }
};



class CMonitorCapConfigConstGlobal
{
private:
	CMonitorCapConfigConstGlobal();
	virtual ~CMonitorCapConfigConstGlobal();

public:
	static CMonitorCapConfigConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CMonitorCapConfigConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

inline CString Ep_GetProtocolDir(long nDir)
{
	if (nDir == 0)
	{
		return _T("监视方向");
	}
	else
	{
		return _T("控制方向");
	}
}

