//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PNTplMngrGlobal.cpp

#include "stdafx.h"
#include "PNTplMngrGlobal.h"
#include "..\..\..\..\Module\API\FileApi.h"
#include "..\..\XLanguageResourceAts.h"
//////////////////////////////////////////////////////////////////////////
//CPNTplMngrXmlRWKeys

CPNTplMngrXmlRWKeys* CPNTplMngrXmlRWKeys::g_pXmlKeys = NULL;
long CPNTplMngrXmlRWKeys::g_nMngrRef = 0;


CPNTplMngrXmlRWKeys::CPNTplMngrXmlRWKeys()
{
	m_strCPNTplGroupKey = L"pntplgroup";
	m_strCPNTplTextKey = L"pntpltext";
	m_strCPNTplEquationKey = L"pntplequation";
	m_strCPNTplElementKey = L"pntplelement";
	m_strCPNTplRootKey = L"pntplroot";
	m_strValueKey = L"value";
}

CPNTplMngrXmlRWKeys::~CPNTplMngrXmlRWKeys()
{
}

CPNTplMngrXmlRWKeys* CPNTplMngrXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CPNTplMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CPNTplMngrXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CPNTplMngrConstGlobal

long CPNTplMngrConstGlobal::g_nGlobalRef = 0;
CPNTplMngrConstGlobal* CPNTplMngrConstGlobal::g_pGlobal = NULL;


CPNTplMngrConstGlobal::CPNTplMngrConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CPNTplMngrConstGlobal::~CPNTplMngrConstGlobal()
{
}

CPNTplMngrConstGlobal* CPNTplMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CPNTplMngrConstGlobal();
	}

	return g_pGlobal;
}

void CPNTplMngrConstGlobal::Release()
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



BOOL ptt_PopOpenPowerTestTplFileDlg(CString &strPath)
{
	return PopupOpenFileDialog(NULL, strPath, _T("tpl | *.tpl;|tpl (*.tpl)|*.tpl|"), _T("tpl"), 
		g_sLangTxt_OpenPowerTestTemplate);
		//_T("ѡ��PowerTestģ���ļ�"));
}

