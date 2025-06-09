//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapDeviceModelGlobal.cpp

#include "stdafx.h"
#include "EpCapDeviceModelGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CEpCapDeviceModelXmlRWKeys

CEpCapDeviceModelXmlRWKeys* CEpCapDeviceModelXmlRWKeys::g_pXmlKeys = NULL;
long CEpCapDeviceModelXmlRWKeys::g_nECDMRef = 0;


CEpCapDeviceModelXmlRWKeys::CEpCapDeviceModelXmlRWKeys()
{
	m_strCEpCapDeviceModelKey = L"device-model";
	m_strCEcdmProtocolAddrsKey = L"protocol-addrs";
	m_strCEcdmProtocolAddrKey = L"protocol-addr";
	m_strCEcdmDatasKey = L"epoto_datas";
	m_strCEcdmDataKey = L"data";
	m_strUnitKey = L"unit";
	m_strDataTypeKey = L"datatype";
	m_strMinKey = L"min";
	m_strMaxKey = L"max";
	m_strDeadKey = L"dead";
	m_strIndexKey = L"index";
	m_strProtocolKey = L"protocol";
	m_strYxAddrKey = L"yx-addr";
	m_strYcAddrKey = L"yc-addr";
	m_strYtAddrKey = L"yt-addr";
}

CEpCapDeviceModelXmlRWKeys::~CEpCapDeviceModelXmlRWKeys()
{
}

CEpCapDeviceModelXmlRWKeys* CEpCapDeviceModelXmlRWKeys::Create()
{
	g_nECDMRef++;

	if (g_nECDMRef == 1)
	{
		g_pXmlKeys = new CEpCapDeviceModelXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CEpCapDeviceModelXmlRWKeys::Release()
{
	g_nECDMRef--;

	if (g_nECDMRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CEpCapDeviceModelConstGlobal

long CEpCapDeviceModelConstGlobal::g_nGlobalRef = 0;
CEpCapDeviceModelConstGlobal* CEpCapDeviceModelConstGlobal::g_pGlobal = NULL;


CEpCapDeviceModelConstGlobal::CEpCapDeviceModelConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CEpCapDeviceModelConstGlobal::~CEpCapDeviceModelConstGlobal()
{
}

CEpCapDeviceModelConstGlobal* CEpCapDeviceModelConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CEpCapDeviceModelConstGlobal();
	}

	return g_pGlobal;
}

void CEpCapDeviceModelConstGlobal::Release()
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
