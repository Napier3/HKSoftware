// LanguageMngr.h: interface for the CLanguageMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANGUAGEMNGR_H__AA4C49EE_6C53_4CCF_8C84_E05B792E8558__INCLUDED_)
#define AFX_LANGUAGEMNGR_H__AA4C49EE_6C53_4CCF_8C84_E05B792E8558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Language.h"

class CLanguageMngr  
{
public:
	CLanguageMngr();
	virtual ~CLanguageMngr();

	static const CString g_strCurrLanguageRegKey;

public:
	CString m_strCurrLanguage;

private:
	CLanguage* m_pCurrLanguage;
	
#ifdef _DEBUG_LANGUAGE_MNGR
	static const CString g_strLanguageDefineFile;
	CLanguage* m_pDebugLanguage;
#endif

public:
	void Init();
	CLanguage* GetCurrLanguage()
	{
		return m_pCurrLanguage;
	}

	BOOL RegisterString(const CString &strID, const CString &strString);
	BOOL RegisterString(char* strID, char* strString);

#ifdef _DEBUG_LANGUAGE_MNGR
	BOOL Debug_WriteTempXmlFile();
#endif
	virtual void RegisterLanguageResource() = 0;
	virtual void InitCurrLanguage();
};

BOOL GetLanguageStringByID(const CString &strID, CString &strLanguageString);
BOOL GetLanguageStringByID(char* strID, char* &strLanguageString);
CString GetLanguageStringByID(const CString &strID);
BOOL ParseLanguageString(CString &strLanguageString);
BOOL RegisterStringByParse(const CString &strID, CString &strString);
BOOL RegisterStringByParse(LPCTSTR strID, LPCTSTR strString);

#ifdef _DEBUG_LANGUAGE_MNGR
BOOL Debug_RegisterString(const CString &strID,const  CString &strString);
BOOL Debug_RegisterString(LPCTSTR strID, LPCTSTR strString);
#endif

#endif // !defined(AFX_LANGUAGEMNGR_H__AA4C49EE_6C53_4CCF_8C84_E05B792E8558__INCLUDED_)
