//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttSafetyMsgCfgGlobal.cpp

#include "stdafx.h"
#include "SttSafetyMsgCfgGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CSttSafetyMsgCfgXmlRWKeys

CSttSafetyMsgCfgXmlRWKeys* CSttSafetyMsgCfgXmlRWKeys::g_pXmlKeys = NULL;
long CSttSafetyMsgCfgXmlRWKeys::g_nSSMCFGRef = 0;


CSttSafetyMsgCfgXmlRWKeys::CSttSafetyMsgCfgXmlRWKeys()
{
	m_strCSttSafetyMsgKey = L"stt-safety-msg";
	m_strCSttSafetyMsgCfgKey = L"stt-safety-msg-cfg";
	m_strCSttSafetyMsgCfgsKey = L"stt-safety-msg-cfgs";
	m_strMsgKey = L"Msg";
}

CSttSafetyMsgCfgXmlRWKeys::~CSttSafetyMsgCfgXmlRWKeys()
{
}

CSttSafetyMsgCfgXmlRWKeys* CSttSafetyMsgCfgXmlRWKeys::Create()
{
	g_nSSMCFGRef++;

	if (g_nSSMCFGRef == 1)
	{
		g_pXmlKeys = new CSttSafetyMsgCfgXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSttSafetyMsgCfgXmlRWKeys::Release()
{
	g_nSSMCFGRef--;

	if (g_nSSMCFGRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSttSafetyMsgCfgConstGlobal

long CSttSafetyMsgCfgConstGlobal::g_nGlobalRef = 0;
CSttSafetyMsgCfgConstGlobal* CSttSafetyMsgCfgConstGlobal::g_pGlobal = NULL;


CSttSafetyMsgCfgConstGlobal::CSttSafetyMsgCfgConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CSttSafetyMsgCfgConstGlobal::~CSttSafetyMsgCfgConstGlobal()
{
}

CSttSafetyMsgCfgConstGlobal* CSttSafetyMsgCfgConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSttSafetyMsgCfgConstGlobal();
	}

	return g_pGlobal;
}

void CSttSafetyMsgCfgConstGlobal::Release()
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
