//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TestMacroGlobal.cpp

#include "stdafx.h"
#include "TestMacroGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CTestMacroXmlRWKeys

CTestMacroXmlRWKeys* CTestMacroXmlRWKeys::g_pXmlKeys = NULL;
long CTestMacroXmlRWKeys::g_nTMRef = 0;
long g_nResetDatas = 1;   //�Ƿ����ò�����������ֵ����Ϊȱʡֵ  shaolei 2022-1-12

CTestMacroXmlRWKeys::CTestMacroXmlRWKeys()
{
	//macro-include  2021-8-14  lijunqing  ���׮�Զ����ԣ������������ļ�������
	m_strCTestMacrosIncludeKey = L"macros-include"; 
	m_strCTestMacroConfigKey = L"macro-test-config";
	m_strCTestMacroConfigsKey = L"macro-test-configs";
	m_strCTmFaultParasExKey = L"fault-paras-ex";
	m_strCTestMacrosFileMngrKey = L"macro-file-mngr";
	m_strCTestMacrosFileKey = L"macro-file";
	m_strCTmResultParasKey = L"results";
	m_strCTmSearchResultParasKey = L"search-results";
	m_strCTmResultParasExKey = L"results-ex";
	m_strCTmSysParasKey = L"sys-paras";
	m_strCTmFaultParasKey = L"fault-paras";
	m_strCTmFaultParasExKey = L"fault-paras-ex";
	m_strCTestMacrosKey = L"macros";
	m_strCTestMacroKey = L"macro";
	m_strVersionKey = L"version";
	m_strTypeKey = L"type";
	m_strRemarkKey = L"remark";
	m_strProgIDKey = L"prog-id";
	m_strFileKey = L"file";
	m_strCmmFileKey = L"cmm-file";
	m_strTestTypeFileKey = L"test-type-file";
	m_strDataTypeFileKey = L"data-type-file";
	m_strDvmFileKey = L"dvm-file";
	m_strActiveMacroTestKey = L"active-macro-test";
	m_strRecordProgIDKey = L"record-progid";
	m_strIecConfigFileKey = L"iec-config-file";
	m_strExpandConfigFileKey = L"expand-config-file";
	m_strDllCallFileKey = L"dll-call-file";
	m_strOldIDKey = L"id-old";
}

CTestMacroXmlRWKeys::~CTestMacroXmlRWKeys()
{
}

CTestMacroXmlRWKeys* CTestMacroXmlRWKeys::Create()
{
	g_nTMRef++;

	if (g_nTMRef == 1)
	{
		g_pXmlKeys = new CTestMacroXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CTestMacroXmlRWKeys::Release()
{
	g_nTMRef--;

	if (g_nTMRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CTestMacroConstGlobal

long CTestMacroConstGlobal::g_nGlobalRef = 0;
CTestMacroConstGlobal* CTestMacroConstGlobal::g_pGlobal = NULL;


CTestMacroConstGlobal::CTestMacroConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CTestMacroConstGlobal::~CTestMacroConstGlobal()
{
}

CTestMacroConstGlobal* CTestMacroConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CTestMacroConstGlobal();
	}

	return g_pGlobal;
}

void CTestMacroConstGlobal::Release()
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

CString tm_GetParaDataPath(CExBaseObject *pData)
{
	CExBaseObject *pParent = (CExBaseObject*)pData->GetParent();

	if (pParent == NULL)
	{
		return pData->m_strID;
	}

	if (pParent->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return pData->m_strID;
	}

	CString strPath;

	if (pData->GetAncestor(TMCLASSID_CTMRESULTPARASEX) != NULL)
	{
		strPath = pData->GetIDPathEx(TMCLASSID_CTMRESULTPARASEX, FALSE);
	}
	else if (pData->GetAncestor(TMCLASSID_CTMFAULTPARASEX) != NULL)
	{
		strPath = pData->GetIDPathEx(TMCLASSID_CTMFAULTPARASEX, FALSE);
	}
	else
	{
		strPath = pData->m_strID;
	}

	return strPath;
}

