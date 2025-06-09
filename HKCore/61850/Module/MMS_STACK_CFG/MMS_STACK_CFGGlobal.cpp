//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MMS_STACK_CFGGlobal.cpp

#include "stdafx.h"
#include "MMS_STACK_CFGGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CMMS_STACK_CFGXmlRWKeys

CMMS_STACK_CFGXmlRWKeys* CMMS_STACK_CFGXmlRWKeys::g_pXmlKeys = NULL;
long CMMS_STACK_CFGXmlRWKeys::g_nMMSRef = 0;


CMMS_STACK_CFGXmlRWKeys::CMMS_STACK_CFGXmlRWKeys()
{
	m_strCMMS_STACK_CFGKey = L"STACK_CFG";
	m_strCStkCfg_NetAddrKey = L"NetAddr";
	m_strCStkCfg_RemoteAddressKey = L"RemoteAddress";
	m_strCStkCfg_RemoteAddressListKey = L"RemoteAddressList";
	m_strCStkCfg_LocalAddressKey = L"LocalAddress";
	m_strCStkCfg_LocalAddressListKey = L"LocalAddressList";
	m_strCStkCfg_NetworkAddressingKey = L"NetworkAddressing";
	m_strCStkCfg_TransportTcpKey = L"Tcp";
	m_strCStkCfg_TransportKey = L"Transport";
	m_strCStkCfg_MMSKey = L"MMS";
	m_strMax_Mms_Pdu_LengthKey = L"Max_Mms_Pdu_Length";
	m_strMax_Calling_ConnectionsKey = L"Max_Calling_Connections";
	m_strMax_Called_ConnectionsKey = L"Max_Called_Connections";
	m_strRfc1006_Max_Tpdu_LenKey = L"Rfc1006_Max_Tpdu_Len";
	m_strRfc1006_Max_Num_ConnsKey = L"Rfc1006_Max_Num_Conns";
	m_strRfc1006_Max_Spdu_OutstandingKey = L"Rfc1006_Max_Spdu_Outstanding";
	m_strAR_NameKey = L"AR_Name";
	m_strAP_TitleKey = L"AP_Title";
	m_strPselKey = L"Psel";
	m_strAE_QualifierKey = L"AE_Qualifier";
	m_strSselKey = L"Ssel";
	m_strTselKey = L"Tsel";
	m_strTransportTypeKey = L"TransportType";
	m_strTypeKey = L"Type";
	m_strNetAddrKey = L"NetAddr";
	m_strEncryptPswKey = L"PSW"; //PSW
	m_strEncryptKeyKey = L"KEY"; //KEY
}

CMMS_STACK_CFGXmlRWKeys::~CMMS_STACK_CFGXmlRWKeys()
{
}

CMMS_STACK_CFGXmlRWKeys* CMMS_STACK_CFGXmlRWKeys::Create()
{
	g_nMMSRef++;

	if (g_nMMSRef == 1)
	{
		g_pXmlKeys = new CMMS_STACK_CFGXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CMMS_STACK_CFGXmlRWKeys::Release()
{
	g_nMMSRef--;

	if (g_nMMSRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CMMS_STACK_CFGConstGlobal

long CMMS_STACK_CFGConstGlobal::g_nGlobalRef = 0;
CMMS_STACK_CFGConstGlobal* CMMS_STACK_CFGConstGlobal::g_pGlobal = NULL;


CMMS_STACK_CFGConstGlobal::CMMS_STACK_CFGConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CMMS_STACK_CFGConstGlobal::~CMMS_STACK_CFGConstGlobal()
{
}

CMMS_STACK_CFGConstGlobal* CMMS_STACK_CFGConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CMMS_STACK_CFGConstGlobal();
	}

	return g_pGlobal;
}

void CMMS_STACK_CFGConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;
