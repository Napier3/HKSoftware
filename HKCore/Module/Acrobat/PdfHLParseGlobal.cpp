//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PdfHLParseGlobal.cpp

#include "stdafx.h"
#include "PdfHLParseGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CPdfHLParseXmlRWKeys

CPdfHLParseXmlRWKeys* CPdfHLParseXmlRWKeys::g_pXmlKeys = NULL;
long CPdfHLParseXmlRWKeys::g_nPDF_Ref = 0;


CPdfHLParseXmlRWKeys::CPdfHLParseXmlRWKeys()
{
	m_strCPdfDBHeadKey = L"tableHead";
	m_strCPdfDBTableKey = L"tableBelong";
	m_strCPdfDBInfoKey = L"PdfInfo";
	m_strNameHeadKey = L"NameHead";
	m_strDWHeadKey = L"DWHead";
	m_strValueHeadKey = L"ValueHead";
	m_strExistHeadKey = L"ExistHead";
}

CPdfHLParseXmlRWKeys::~CPdfHLParseXmlRWKeys()
{
}

CPdfHLParseXmlRWKeys* CPdfHLParseXmlRWKeys::Create()
{
	g_nPDF_Ref++;

	if (g_nPDF_Ref == 1)
	{
		g_pXmlKeys = new CPdfHLParseXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CPdfHLParseXmlRWKeys::Release()
{
	g_nPDF_Ref--;

	if (g_nPDF_Ref == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CPdfHLParseConstGlobal

long CPdfHLParseConstGlobal::g_nGlobalRef = 0;
CPdfHLParseConstGlobal* CPdfHLParseConstGlobal::g_pGlobal = NULL;


CPdfHLParseConstGlobal::CPdfHLParseConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CPdfHLParseConstGlobal::~CPdfHLParseConstGlobal()
{
}

CPdfHLParseConstGlobal* CPdfHLParseConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CPdfHLParseConstGlobal();
	}

	return g_pGlobal;
}

void CPdfHLParseConstGlobal::Release()
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
