//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MmsRcdFilesMngrGlobal.cpp

#include "stdafx.h"
#include "MmsRcdFilesMngrGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CMmsRcdFilesMngrXmlRWKeys

CMmsRcdFilesMngrXmlRWKeys* CMmsRcdFilesMngrXmlRWKeys::g_pXmlKeys = NULL;
long CMmsRcdFilesMngrXmlRWKeys::g_nMngrRef = 0;


CMmsRcdFilesMngrXmlRWKeys::CMmsRcdFilesMngrXmlRWKeys()
{
	m_strCRcdFileKey = L"rcd-file";
	m_strCRcdDirKey = L"rcd-dir";
	m_strCMmsDeviceKey = L"mms-device";
	m_strCMmsDevicesKey = L"mms-devices";
	m_strDirsizeKey = L"dirsize";
	m_strDirtimeKey = L"dirtime";
	m_strFilesizeKey = L"filesize";
	m_strFiletimeKey = L"filetime";
}

CMmsRcdFilesMngrXmlRWKeys::~CMmsRcdFilesMngrXmlRWKeys()
{
}

CMmsRcdFilesMngrXmlRWKeys* CMmsRcdFilesMngrXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CMmsRcdFilesMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CMmsRcdFilesMngrXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CMmsRcdFilesMngrConstGlobal

long CMmsRcdFilesMngrConstGlobal::g_nGlobalRef = 0;
CMmsRcdFilesMngrConstGlobal* CMmsRcdFilesMngrConstGlobal::g_pGlobal = NULL;


CMmsRcdFilesMngrConstGlobal::CMmsRcdFilesMngrConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CMmsRcdFilesMngrConstGlobal::~CMmsRcdFilesMngrConstGlobal()
{
}

CMmsRcdFilesMngrConstGlobal* CMmsRcdFilesMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CMmsRcdFilesMngrConstGlobal();
	}

	return g_pGlobal;
}

void CMmsRcdFilesMngrConstGlobal::Release()
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
