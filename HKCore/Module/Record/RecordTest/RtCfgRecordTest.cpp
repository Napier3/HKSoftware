// RtCfgRecordTest.cpp: implementation of the CRtCfgRecordTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtCfgRecordTest.h"

#include "RtCfgRecordTests.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char *CRtCfgRecordTest::g_pszKeyRecordTest = "record-test";
const char *CRtCfgRecordTest::g_pszKeyAppModel   = "model";
const char *CRtCfgRecordTest::g_pszKeyTestGroup_Type		 = "testgroup-type";
const char *CRtCfgRecordTest::g_pszKeyRemark	 = "remark";
const char *CRtCfgRecordTest::g_pszKeyRtInfo	 = "rtinfo";
const char *CRtCfgRecordTest::g_pszKeyAnalysePage = "analysepage";
const char *CRtCfgRecordTest::g_pszKeyTestType = "testtype";

CRtCfgRecordTest::CRtCfgRecordTest()
{
	m_pVariables	= NULL;
	//m_pAppModels	= NULL;	
}

CRtCfgRecordTest::~CRtCfgRecordTest()
{
}

long CRtCfgRecordTest::GetRTStatus()
{
	return m_nStatus;
}

void CRtCfgRecordTest::SetRTStatus(long nRTStatus)
{
	m_nStatus = nRTStatus;
}

CString CRtCfgRecordTest::GetRTStatusString()
{
	CString str;
	long nRTStatus = GetRTStatus();
	
	switch(nRTStatus) 
	{
	case RT_CANBEUSED:
		str = _T("RT_CANBEUSED");
		//str = GetLanguageStringByID(gs_strLanguage_msRTCanUse);
		break;
	case RT_CANOTBEUSED:
		str = _T("RT_CANOTBEUSED");
		//str = GetLanguageStringByID(gs_strLanguage_msRTCanotUse);
		break;
	case RT_DEVALOPING:
		str = _T("RT_DEVALOPING");
		//str = GetLanguageStringByID(gs_strLanguage_msRTDeveloping);		
		break;
	case RT_ENTRY:
		str = _T("RT_ENTRY");
		//str = GetLanguageStringByID(gs_strLanguage_msRTEntry);
		break;
	default:;
	}

	return str;
}

BOOL CRtCfgRecordTest::IsUniversalTest()
{
	BOOL bTrue = FALSE;

	if (_stricmp(m_strTestGroupType.GetString(), CRtTypes::g_pszKeyUniversal) == 0)
	{
		bTrue = TRUE;
	}
	else
	{
		
	}
	
	return bTrue;
}
