//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SclFileMngrGlobal.cpp

#include "stdafx.h"
#include "SclFileMngrGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CSclFileMngrXmlRWKeys

CSclFileMngrXmlRWKeys* CSclFileMngrXmlRWKeys::g_pXmlKeys = NULL;
long CSclFileMngrXmlRWKeys::g_nMngrRef = 0;


CSclFileMngrXmlRWKeys::CSclFileMngrXmlRWKeys()
{
	m_strCXSclFileObjKey = L"scl-file";
	m_strCXSclFileMngrKey = L"scl-file-mngr";
	m_strCurr_Sel_IedKey = L"curr-sel-ied";
	m_strSizeKey = L"size";
	m_strSscl_PathKey = L"sscl-path";
	m_strScl_PathKey = L"scl-path";
	m_strUseKey = L"use";
}

CSclFileMngrXmlRWKeys::~CSclFileMngrXmlRWKeys()
{
}

CSclFileMngrXmlRWKeys* CSclFileMngrXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CSclFileMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSclFileMngrXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSclFileMngrConstGlobal

long CSclFileMngrConstGlobal::g_nGlobalRef = 0;
CSclFileMngrConstGlobal* CSclFileMngrConstGlobal::g_pGlobal = NULL;


CSclFileMngrConstGlobal::CSclFileMngrConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CSclFileMngrConstGlobal::~CSclFileMngrConstGlobal()
{
}

CSclFileMngrConstGlobal* CSclFileMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSclFileMngrConstGlobal();
	}

	return g_pGlobal;
}

void CSclFileMngrConstGlobal::Release()
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
