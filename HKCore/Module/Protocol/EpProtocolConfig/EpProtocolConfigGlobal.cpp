//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpProtocolConfigGlobal.cpp

#include "stdafx.h"
#include "EpProtocolConfigGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CEpProtocolConfigXmlRWKeys

CEpProtocolConfigXmlRWKeys* CEpProtocolConfigXmlRWKeys::g_pXmlKeys = NULL;
long CEpProtocolConfigXmlRWKeys::g_nEPCRef = 0;


CEpProtocolConfigXmlRWKeys::CEpProtocolConfigXmlRWKeys()
{
	m_strCEpProtocolConfigKey = L"ep-protocol-config";
	m_strCEp104ConfigKey = L"IEC60870-5-104";
	m_strCEp101ConfigKey = L"IEC60870-5-101";
	m_strOddrKey = L"oddr";
	m_strYxAddrKey = L"yx-addr";
	m_strYcAddrKey = L"yc-addr";
	m_strYtAddrKey = L"yt-addr";
}

CEpProtocolConfigXmlRWKeys::~CEpProtocolConfigXmlRWKeys()
{
}

CEpProtocolConfigXmlRWKeys* CEpProtocolConfigXmlRWKeys::Create()
{
	g_nEPCRef++;

	if (g_nEPCRef == 1)
	{
		g_pXmlKeys = new CEpProtocolConfigXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CEpProtocolConfigXmlRWKeys::Release()
{
	g_nEPCRef--;

	if (g_nEPCRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CEpProtocolConfigConstGlobal

long CEpProtocolConfigConstGlobal::g_nGlobalRef = 0;
CEpProtocolConfigConstGlobal* CEpProtocolConfigConstGlobal::g_pGlobal = NULL;


CEpProtocolConfigConstGlobal::CEpProtocolConfigConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CEpProtocolConfigConstGlobal::~CEpProtocolConfigConstGlobal()
{
}

CEpProtocolConfigConstGlobal* CEpProtocolConfigConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CEpProtocolConfigConstGlobal();
	}

	return g_pGlobal;
}

void CEpProtocolConfigConstGlobal::Release()
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
