//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TUnits.cpp

#include "stdafx.h"
#include "TUnits.h"
#include "../API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CTUnits

CTUnits* CTUnits::g_pTUnits = NULL;
long CTUnits::g_nTMRef = 0;

const CString CTUnits::g_strCTUnits_xml_file = _T("Units.xml");

CTUnits::CTUnits()
{
	
}

CTUnits::~CTUnits()
{
}

CTUnits* CTUnits::Create()
{
	g_nTMRef++;

	if (g_nTMRef == 1)
	{
		g_pTUnits = new CTUnits();

		CString strFile;
		strFile = _P_GetConfigPath();
		strFile += g_strCTUnits_xml_file;
		g_pTUnits->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

		xlang_TranslateByResourceFileEx_NoWrite(g_pTUnits, g_strCTUnits_xml_file);
		g_pTUnits->m_oXLanguage.LoadLanguagegResourceFileEx(g_strCTUnits_xml_file);
	}

	return g_pTUnits;
}

void CTUnits::Release()
{
	g_nTMRef--;

	if (g_nTMRef == 0)
	{
		delete g_pTUnits;
		g_pTUnits = NULL;
	}
}

CString CTUnits::unit_xlang_TranslateUnit(const CString &strUnit)
{
	ASSERT (g_pTUnits != NULL);

	if ( xlang_IsCurrXLanguageChinese())
	{
		return strUnit;
	}

	CXLangItem *pTemp = g_pTUnits->m_oXLanguage.FindBySrcText(strUnit);

	if (pTemp == NULL)
	{
		return strUnit;
	}
	else
	{
		return pTemp->m_strTranslation;
	}
}

