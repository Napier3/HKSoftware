//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MqttPpCfgGlobal.h

#pragma once

#include "../../../Module/DataMngr/DataMngrGlobal.h"

#define MqttCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00090000)
#define MqttCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00090000)

#define MQTTCLASSID_CMQTTPPTEMPLATE       (MqttCLASSID_EXLISTCLASS + 0X00000000)
#define MQTTCLASSID_CMQTTPPPRASES       (MqttCLASSID_EXLISTCLASS + 0X00000001)
#define MQTTCLASSID_CMQTTPPPRASE       (MqttCLASSID_EXLISTCLASS + 0X00000002)
#define MQTTCLASSID_CMQTTPPPRODUCES       (MqttCLASSID_EXLISTCLASS + 0X00000003)
#define MQTTCLASSID_CMQTTPPPRODUCE       (MqttCLASSID_EXLISTCLASS + 0X00000004)
#define MQTTCLASSID_CMQTTPPPKG       (MqttCLASSID_EXLISTCLASS + 0X00000005)
#define MQTTCLASSID_CMQTTPPACKS       (MqttCLASSID_EXLISTCLASS + 0X00000006)
#define MQTTCLASSID_CMQTTPPACK       (MqttCLASSID_BASECLASS + 0X00000007)
#define MQTTCLASSID_CMQTTPPOVERTIME       (MqttCLASSID_BASECLASS + 0X00000008)
#define MQTTCLASSID_CMQTTPPPROCEDURES       (MqttCLASSID_EXLISTCLASS + 0X00000009)
#define MQTTCLASSID_CMQTTPPPROCEDURE       (MqttCLASSID_EXLISTCLASS + 0X0000000A)

class CMqttPpCfgXmlRWKeys : public CDataMngrXmlRWKeys
{
protected:
	CMqttPpCfgXmlRWKeys();
	virtual ~CMqttPpCfgXmlRWKeys();
	static long g_nMqttRef;

public:
	static CMqttPpCfgXmlRWKeys* g_pXmlKeys;
	static CMqttPpCfgXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCMqttPpProcedureKey; //procedure
	BSTR m_strCMqttPpProceduresKey; //procedures
	BSTR m_strCMqttPpOverTimeKey; //overtime
	BSTR m_strCMqttPpAckKey; //ack
	BSTR m_strCMqttPpAcksKey; //acks
	BSTR m_strCMqttPpPkgKey; //pkg
	BSTR m_strCMqttPpProduceKey; //pp-produce
	BSTR m_strCMqttPpProducesKey; //pp-produces
	BSTR m_strCMqttPpPraseKey; //pp-prase
	BSTR m_strCMqttPpPrasesKey; //pp-prases
	BSTR m_strCMqttPpTemplateKey; //mqtt-pp-template
	BSTR m_strDvm_FileKey; //dvm-file
	BSTR m_strDs_OptrKey; //ds-optr
	BSTR m_strDsKey; //ds
	BSTR m_strPp_PkgKey; //pp-pkg
	BSTR m_strJump_ToKey; //jump-to
	BSTR m_strValueKey; //value

public:
	static BSTR CMqttPpProcedureKey()  {   return g_pXmlKeys->m_strCMqttPpProcedureKey;  }
	static BSTR CMqttPpProceduresKey()  {   return g_pXmlKeys->m_strCMqttPpProceduresKey;  }
	static BSTR CMqttPpOverTimeKey()  {   return g_pXmlKeys->m_strCMqttPpOverTimeKey;  }
	static BSTR CMqttPpAckKey()  {   return g_pXmlKeys->m_strCMqttPpAckKey;  }
	static BSTR CMqttPpAcksKey()  {   return g_pXmlKeys->m_strCMqttPpAcksKey;  }
	static BSTR CMqttPpPkgKey()  {   return g_pXmlKeys->m_strCMqttPpPkgKey;  }
	static BSTR CMqttPpProduceKey()  {   return g_pXmlKeys->m_strCMqttPpProduceKey;  }
	static BSTR CMqttPpProducesKey()  {   return g_pXmlKeys->m_strCMqttPpProducesKey;  }
	static BSTR CMqttPpPraseKey()  {   return g_pXmlKeys->m_strCMqttPpPraseKey;  }
	static BSTR CMqttPpPrasesKey()  {   return g_pXmlKeys->m_strCMqttPpPrasesKey;  }
	static BSTR CMqttPpTemplateKey()  {   return g_pXmlKeys->m_strCMqttPpTemplateKey;  }
	static BSTR Dvm_FileKey()  {   return g_pXmlKeys->m_strDvm_FileKey;  }
	static BSTR Ds_OptrKey()  {   return g_pXmlKeys->m_strDs_OptrKey;  }
	static BSTR DsKey()  {   return g_pXmlKeys->m_strDsKey;  }
	static BSTR Pp_PkgKey()  {   return g_pXmlKeys->m_strPp_PkgKey;  }
	static BSTR Jump_ToKey()  {   return g_pXmlKeys->m_strJump_ToKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
};



class CMqttPpCfgConstGlobal
{
private:
	CMqttPpCfgConstGlobal();
	virtual ~CMqttPpCfgConstGlobal();

public:
	static CMqttPpCfgConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CMqttPpCfgConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
