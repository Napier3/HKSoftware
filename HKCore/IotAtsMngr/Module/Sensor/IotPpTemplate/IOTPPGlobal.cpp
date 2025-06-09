//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IOTPPGlobal.cpp

#include "stdafx.h"
#include "IOTPPGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CIOTPPXmlRWKeys

CIOTPPXmlRWKeys* CIOTPPXmlRWKeys::g_pXmlKeys = NULL;
long CIOTPPXmlRWKeys::g_nIOTRef = 0;


CIOTPPXmlRWKeys::CIOTPPXmlRWKeys()
{
	m_strCIotPpJumpKey = L"jump";
	m_strCIotPpJumpsKey = L"jumps";
	m_strCIotPpTimerKey = L"timer";
	m_strCIotPpTimersKey = L"timers";
	m_strCIotPpAckKey = L"ack";
	m_strCIotPpAcksKey = L"acks";
	m_strCIotPpNodeKey = L"node";
	m_strCIotPpValueKey = L"value";
	m_strCIotPpInterfaceKey = L"interface";
	m_strCIotPpDataListKey = L"data-list";
	m_strCIotPpPkgHeadKey = L"pkg-head";
	m_strCIotPpProcedureKey = L"procedure";
	m_strCIotPpProduceKey = L"pp-produce";
	m_strCIotPpParseKey = L"pp-parse";
	m_strCIotPpProceduresKey = L"procedures";
	m_strCIotPpProducesKey = L"pp-produces";
	m_strCIotPpParsesKey = L"pp-parses";
	m_strCIotPpTemplateKey = L"iot-pp-template";
	m_strDvm_FileKey = L"dvm-file";
	m_strDs_OptrKey = L"ds-optr";
	m_strDsKey = L"ds";
	m_strData_TypeKey = L"data-type";
	m_strValueKey = L"value";
	m_strPkg_IdKey = L"pkg-id";
	m_strTypeKey = L"type";
	m_strJump_ToKey = L"jump-to";
	m_strTimeKey = L"time";
}

CIOTPPXmlRWKeys::~CIOTPPXmlRWKeys()
{
}

CIOTPPXmlRWKeys* CIOTPPXmlRWKeys::Create()
{
	g_nIOTRef++;

	if (g_nIOTRef == 1)
	{
		g_pXmlKeys = new CIOTPPXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CIOTPPXmlRWKeys::Release()
{
	g_nIOTRef--;

	if (g_nIOTRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CIOTPPConstGlobal

long CIOTPPConstGlobal::g_nGlobalRef = 0;
CIOTPPConstGlobal* CIOTPPConstGlobal::g_pGlobal = NULL;


CIOTPPConstGlobal::CIOTPPConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CIOTPPConstGlobal::~CIOTPPConstGlobal()
{
}

CIOTPPConstGlobal* CIOTPPConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CIOTPPConstGlobal();
	}

	return g_pGlobal;
}

void CIOTPPConstGlobal::Release()
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
