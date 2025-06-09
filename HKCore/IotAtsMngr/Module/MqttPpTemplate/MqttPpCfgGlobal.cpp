//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MqttPpCfgGlobal.cpp

#include "stdafx.h"
#include "MqttPpCfgGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CMqttPpCfgXmlRWKeys

CMqttPpCfgXmlRWKeys* CMqttPpCfgXmlRWKeys::g_pXmlKeys = NULL;
long CMqttPpCfgXmlRWKeys::g_nMqttRef = 0;


CMqttPpCfgXmlRWKeys::CMqttPpCfgXmlRWKeys()
{
	m_strCMqttPpProcedureKey = L"procedure";
	m_strCMqttPpProceduresKey = L"procedures";
	m_strCMqttPpOverTimeKey = L"overtime";
	m_strCMqttPpAckKey = L"ack";
	m_strCMqttPpAcksKey = L"acks";
	m_strCMqttPpPkgKey = L"pkg";
	m_strCMqttPpProduceKey = L"pp-produce";
	m_strCMqttPpProducesKey = L"pp-produces";
	m_strCMqttPpPraseKey = L"pp-prase";
	m_strCMqttPpPrasesKey = L"pp-prases";
	m_strCMqttPpTemplateKey = L"mqtt-pp-template";
	m_strDvm_FileKey = L"dvm-file";
	m_strDs_OptrKey = L"ds-optr";
	m_strDsKey = L"ds";
	m_strPp_PkgKey = L"pp-pkg";
	m_strJump_ToKey = L"jump-to";
	m_strValueKey = L"value";
}

CMqttPpCfgXmlRWKeys::~CMqttPpCfgXmlRWKeys()
{
}

CMqttPpCfgXmlRWKeys* CMqttPpCfgXmlRWKeys::Create()
{
	g_nMqttRef++;

	if (g_nMqttRef == 1)
	{
		g_pXmlKeys = new CMqttPpCfgXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CMqttPpCfgXmlRWKeys::Release()
{
	g_nMqttRef--;

	if (g_nMqttRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CMqttPpCfgConstGlobal

long CMqttPpCfgConstGlobal::g_nGlobalRef = 0;
CMqttPpCfgConstGlobal* CMqttPpCfgConstGlobal::g_pGlobal = NULL;


CMqttPpCfgConstGlobal::CMqttPpCfgConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CMqttPpCfgConstGlobal::~CMqttPpCfgConstGlobal()
{
}

CMqttPpCfgConstGlobal* CMqttPpCfgConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CMqttPpCfgConstGlobal();
	}

	return g_pGlobal;
}

void CMqttPpCfgConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;
