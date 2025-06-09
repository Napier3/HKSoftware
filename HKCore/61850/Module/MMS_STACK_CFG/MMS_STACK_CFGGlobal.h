//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MMS_STACK_CFGGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define MMSCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MMSCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MMSCLASSID_CSTKCFG_MMS       (MMSCLASSID_BASECLASS + 0X00000000)
#define MMSCLASSID_CSTKCFG_TRANSPORT       (MMSCLASSID_EXLISTCLASS + 0X00000001)
#define MMSCLASSID_CSTKCFG_TRANSPORTTCP       (MMSCLASSID_BASECLASS + 0X00000002)
#define MMSCLASSID_CSTKCFG_NETWORKADDRESSING       (MMSCLASSID_EXLISTCLASS + 0X00000003)
#define MMSCLASSID_CSTKCFG_LOCALADDRESSLIST       (MMSCLASSID_EXLISTCLASS + 0X00000004)
#define MMSCLASSID_CSTKCFG_LOCALADDRESS       (MMSCLASSID_BASECLASS + 0X00000005)
#define MMSCLASSID_CSTKCFG_REMOTEADDRESSLIST       (MMSCLASSID_EXLISTCLASS + 0X00000006)
#define MMSCLASSID_CSTKCFG_REMOTEADDRESS       (MMSCLASSID_EXLISTCLASS + 0X00000007)
#define MMSCLASSID_CSTKCFG_NETADDR       (MMSCLASSID_BASECLASS + 0X00000008)
#define MMSCLASSID_CMMS_STACK_CFG       (MMSCLASSID_EXLISTCLASS + 0X00000009)

class CMMS_STACK_CFGXmlRWKeys : public CXmlRWKeys
{
protected:
	CMMS_STACK_CFGXmlRWKeys();
	virtual ~CMMS_STACK_CFGXmlRWKeys();
	static long g_nMMSRef;

public:
	static CMMS_STACK_CFGXmlRWKeys* g_pXmlKeys;
	static CMMS_STACK_CFGXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCMMS_STACK_CFGKey; //STACK_CFG
	BSTR m_strCStkCfg_NetAddrKey; //NetAddr
	BSTR m_strCStkCfg_RemoteAddressKey; //RemoteAddress
	BSTR m_strCStkCfg_RemoteAddressListKey; //RemoteAddressList
	BSTR m_strCStkCfg_LocalAddressKey; //LocalAddress
	BSTR m_strCStkCfg_LocalAddressListKey; //LocalAddressList
	BSTR m_strCStkCfg_NetworkAddressingKey; //NetworkAddressing
	BSTR m_strCStkCfg_TransportTcpKey; //Tcp
	BSTR m_strCStkCfg_TransportKey; //Transport
	BSTR m_strCStkCfg_MMSKey; //MMS
	BSTR m_strMax_Mms_Pdu_LengthKey; //Max_Mms_Pdu_Length
	BSTR m_strMax_Calling_ConnectionsKey; //Max_Calling_Connections
	BSTR m_strMax_Called_ConnectionsKey; //Max_Called_Connections
	BSTR m_strRfc1006_Max_Tpdu_LenKey; //Rfc1006_Max_Tpdu_Len
	BSTR m_strRfc1006_Max_Num_ConnsKey; //Rfc1006_Max_Num_Conns
	BSTR m_strRfc1006_Max_Spdu_OutstandingKey; //Rfc1006_Max_Spdu_Outstanding
	BSTR m_strAR_NameKey; //AR_Name
	BSTR m_strAP_TitleKey; //AP_Title
	BSTR m_strPselKey; //Psel
	BSTR m_strAE_QualifierKey; //AE_Qualifier
	BSTR m_strSselKey; //Ssel
	BSTR m_strTselKey; //Tsel
	BSTR m_strTransportTypeKey; //TransportType
	BSTR m_strTypeKey; //Type
	BSTR m_strNetAddrKey; //NetAddr
	BSTR m_strEncryptPswKey; //PSW
	BSTR m_strEncryptKeyKey; //KEY

public:
	static BSTR CMMS_STACK_CFGKey()  {   return g_pXmlKeys->m_strCMMS_STACK_CFGKey;  }
	static BSTR CStkCfg_NetAddrKey()  {   return g_pXmlKeys->m_strCStkCfg_NetAddrKey;  }
	static BSTR CStkCfg_RemoteAddressKey()  {   return g_pXmlKeys->m_strCStkCfg_RemoteAddressKey;  }
	static BSTR CStkCfg_RemoteAddressListKey()  {   return g_pXmlKeys->m_strCStkCfg_RemoteAddressListKey;  }
	static BSTR CStkCfg_LocalAddressKey()  {   return g_pXmlKeys->m_strCStkCfg_LocalAddressKey;  }
	static BSTR CStkCfg_LocalAddressListKey()  {   return g_pXmlKeys->m_strCStkCfg_LocalAddressListKey;  }
	static BSTR CStkCfg_NetworkAddressingKey()  {   return g_pXmlKeys->m_strCStkCfg_NetworkAddressingKey;  }
	static BSTR CStkCfg_TransportTcpKey()  {   return g_pXmlKeys->m_strCStkCfg_TransportTcpKey;  }
	static BSTR CStkCfg_TransportKey()  {   return g_pXmlKeys->m_strCStkCfg_TransportKey;  }
	static BSTR CStkCfg_MMSKey()  {   return g_pXmlKeys->m_strCStkCfg_MMSKey;  }
	static BSTR Max_Mms_Pdu_LengthKey()  {   return g_pXmlKeys->m_strMax_Mms_Pdu_LengthKey;  }
	static BSTR Max_Calling_ConnectionsKey()  {   return g_pXmlKeys->m_strMax_Calling_ConnectionsKey;  }
	static BSTR Max_Called_ConnectionsKey()  {   return g_pXmlKeys->m_strMax_Called_ConnectionsKey;  }
	static BSTR Rfc1006_Max_Tpdu_LenKey()  {   return g_pXmlKeys->m_strRfc1006_Max_Tpdu_LenKey;  }
	static BSTR Rfc1006_Max_Num_ConnsKey()  {   return g_pXmlKeys->m_strRfc1006_Max_Num_ConnsKey;  }
	static BSTR Rfc1006_Max_Spdu_OutstandingKey()  {   return g_pXmlKeys->m_strRfc1006_Max_Spdu_OutstandingKey;  }
	static BSTR AR_NameKey()  {   return g_pXmlKeys->m_strAR_NameKey;  }
	static BSTR AP_TitleKey()  {   return g_pXmlKeys->m_strAP_TitleKey;  }
	static BSTR PselKey()  {   return g_pXmlKeys->m_strPselKey;  }
	static BSTR AE_QualifierKey()  {   return g_pXmlKeys->m_strAE_QualifierKey;  }
	static BSTR SselKey()  {   return g_pXmlKeys->m_strSselKey;  }
	static BSTR TselKey()  {   return g_pXmlKeys->m_strTselKey;  }
	static BSTR TransportTypeKey()  {   return g_pXmlKeys->m_strTransportTypeKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR NetAddrKey()  {   return g_pXmlKeys->m_strNetAddrKey;  }
};



class CMMS_STACK_CFGConstGlobal
{
private:
	CMMS_STACK_CFGConstGlobal();
	virtual ~CMMS_STACK_CFGConstGlobal();

public:
	static CMMS_STACK_CFGConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CMMS_STACK_CFGConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
