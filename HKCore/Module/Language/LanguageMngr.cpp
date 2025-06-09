// LanguageMngr.cpp: implementation of the CLanguageMngr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LanguageMngr.h"
#include "LanguageNameParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const CString CLanguageMngr::g_strCurrLanguageRegKey  = _T("curr-language");

#ifdef _DEBUG_LANGUAGE_MNGR
const CString CLanguageMngr::g_strLanguageDefineFile  = "LanguageDefine.xml";
#endif

CLanguageMngr::CLanguageMngr()
{
	m_pCurrLanguage = new CLanguage();
#ifdef _DEBUG_LANGUAGE_MNGR
	m_pDebugLanguage = new CLanguage();
#endif
}

CLanguageMngr::~CLanguageMngr()
{
#ifdef _DEBUG_LANGUAGE_MNGR
	if (m_pCurrLanguage != NULL && m_pDebugLanguage != NULL)
	{
		Debug_WriteTempXmlFile();
	}
#endif
	
	if (m_pCurrLanguage != NULL)
	{
		delete m_pCurrLanguage;
		m_pCurrLanguage = NULL;
	}

#ifdef _DEBUG_LANGUAGE_MNGR
	if (m_pDebugLanguage != NULL)
	{
		delete m_pDebugLanguage;
		m_pDebugLanguage = NULL;
	}
#endif
}

void CLanguageMngr::Init()
{
	if (ReadDataFromRegister((CString)_P_GetSoftRegKey(),  (CString)g_strCurrLanguageRegKey, m_strCurrLanguage))
	{
	}
	else
	{
		m_strCurrLanguage = L"Chinese";//English
	}

	CString strFile;
	strFile.Format(_T("%s%s.xml"), (CString)_P_GetLanguagePath(), m_strCurrLanguage);
	
	/*if (!m_pCurrLanguage->ReadXmlFile(strFile))
	{
		m_pCurrLanguage->Debug_WriteTempXmlFile(strFile);
	}*/

#ifdef _DEBUG_LANGUAGE_MNGR
	strFile.Format(_T("%s%s"), (CString)_P_GetLanguagePath(), g_strLanguageDefineFile);
	m_pDebugLanguage->ReadXmlFile(strFile);
#endif
}

BOOL CLanguageMngr::RegisterString(const CString &strID, const CString &strString)
{
	ASSERT(m_pCurrLanguage != NULL);
	m_pCurrLanguage->RegisterString(strID, strString);

#ifdef _DEBUG_LANGUAGE_MNGR
	ASSERT(m_pDebugLanguage != NULL);
	m_pDebugLanguage->RegisterString(strID, strString);
#endif
	return TRUE;
}

BOOL CLanguageMngr::RegisterString(char* strID, char* strString)
{
	ASSERT(m_pCurrLanguage != NULL);
	m_pCurrLanguage->RegisterString(strID, strString);
	
#ifdef _DEBUG_LANGUAGE_MNGR
	ASSERT(m_pDebugLanguage != NULL);
	m_pDebugLanguage->RegisterString(strID, strString);
#endif
	return TRUE;
}

//#ifdef _DEBUG_LANGUAGE_MNGR
//BOOL CLanguageMngr::Debug_RegisterString(const CString &strID, CString &strString)
//{
//	ASSERT(m_pDebugLanguage != NULL);
//	m_pDebugLanguage->RegisterString(strID, strString);
//
//	return TRUE;
//}
//
//BOOL CLanguageMngr::Debug_RegisterString(LPCTSTR strID, LPCTSTR strString)
//{
//	ASSERT(m_pDebugLanguage != NULL);
//	m_pDebugLanguage->RegisterString(strID, strString);
//	return TRUE;
//}
//#endif

#ifdef _DEBUG_LANGUAGE_MNGR
BOOL CLanguageMngr::Debug_WriteTempXmlFile()
{
	CString strFile;
	strFile.Format(_T("%s%s"), (CString)_P_GetLanguagePath(), g_strLanguageDefineFile);
	m_pDebugLanguage->ReadXmlFile(strFile); //读取语言配置文件的数据
	m_pDebugLanguage->Append(m_pCurrLanguage);//将当前应用程序的语言资源添加到末尾
	m_pDebugLanguage->Debug_WriteTempXmlFile(strFile);//保存文件
	
	return TRUE;
}
#endif

//////////////////////////////////////////////////////////////////////////
CLanguage *g_CurrLanguage = NULL;

//CLanguageNameParser oParser;

#ifdef _DEBUG_LANGUAGE_MNGR
CLanguage *g_Debug_CurrLanguage = NULL;
#endif

void CLanguageMngr::InitCurrLanguage()
{
	g_CurrLanguage = m_pCurrLanguage;

#ifdef _DEBUG_LANGUAGE_MNGR
	g_Debug_CurrLanguage = m_pDebugLanguage;
	//Debug_WriteTempXmlFile();
#endif
}

BOOL GetLanguageStringByID(const CString &strID, CString &strLanguageString)
{
	ASSERT (g_CurrLanguage != NULL);
	return g_CurrLanguage->GetLanguageStringByID(strID, strLanguageString);
}

BOOL GetLanguageStringByID(LPCTSTR strID, CString &strLanguageString)
{
	ASSERT (g_CurrLanguage != NULL);
	return g_CurrLanguage->GetLanguageStringByID(strID, strLanguageString);
}

CString GetLanguageStringByID(const CString &strID)
{
	ASSERT (g_CurrLanguage != NULL);
	return g_CurrLanguage->GetLanguageStringByID(strID);
}

BOOL ParseLanguageString(CString &strLanguageString)
{
	if (strLanguageString.GetLength() > 0)
	{
		CLanguageNameParser oParser;
		oParser.ParseLanguageString(strLanguageString);
	}
	else
	{
	}

	return TRUE;
}

BOOL RegisterStringByParse(const CString &strID, CString &strString)
{
	ASSERT (g_CurrLanguage != NULL);
	return g_CurrLanguage->RegisterString(strID, strString);
}

BOOL RegisterStringByParse(char* strID, char* strString)
{
	ASSERT (g_CurrLanguage != NULL);
	return g_CurrLanguage->RegisterString(strID, strString);
}

#ifdef _DEBUG_LANGUAGE_MNGR
BOOL Debug_RegisterString(const CString &strID, const CString &strString)
{
	ASSERT (g_CurrLanguage != NULL);
	return g_Debug_CurrLanguage->RegisterString(strID, strString);	
}
// 
// BOOL Debug_RegisterString(LPCTSTR strID, LPCTSTR strString)
// {
// 	ASSERT (g_CurrLanguage != NULL);
// 	return g_Debug_CurrLanguage->RegisterString(strID, strString);	
// }

#endif
