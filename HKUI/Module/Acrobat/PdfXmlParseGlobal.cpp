//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PdfParseGlobal.cpp

#include "stdafx.h"
#include "PdfXmlParseGlobal.h"
#include "../API/FileApi.h"
#include <math.h>
#include "../API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CPdfParseXmlRWKeys

CPdfParseXmlRWKeys* CPdfParseXmlRWKeys::g_pXmlKeys = NULL;
long CPdfParseXmlRWKeys::g_nPDFPRef = 0;


CPdfParseXmlRWKeys::CPdfParseXmlRWKeys()
{
	m_strRowKey = L"row"; 
	m_strTableKey = L"table"; 
	m_strTablesKey = L"tables";
	m_strVposKey = L"vpos";
	m_strHposKey = L"hpos";
	m_strVpos2Key = L"vpos2";
	m_strHpos2Key = L"hpos2";
	m_strWidthKey = L"width";
	m_strHeightKey = L"height";
	m_strColKey = L"col";
	m_strColsKey = L"cols";
	m_strStringDataKey = L"string";
}

CPdfParseXmlRWKeys::~CPdfParseXmlRWKeys()
{
}

CPdfParseXmlRWKeys* CPdfParseXmlRWKeys::Create()
{
	g_nPDFPRef++;

	if (g_nPDFPRef == 1)
	{
		g_pXmlKeys = new CPdfParseXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CPdfParseXmlRWKeys::Release()
{
	g_nPDFPRef--;

	if (g_nPDFPRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}
