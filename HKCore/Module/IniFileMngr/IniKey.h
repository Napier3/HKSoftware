// IniKey.h: interface for the CIniKey class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIKEY_H__9221D704_B72C_4F8A_8F7E_5D0717121DB8__INCLUDED_)
#define AFX_INIKEY_H__9221D704_B72C_4F8A_8F7E_5D0717121DB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\BaseClass\ExBaseList.h"

class CIniKey : public CExBaseObject  
{
public:
	CIniKey();
	CIniKey(const CString &strName, const CString &strValue);
	CIniKey(const char *pszKeyName,const char *pszKeyValue);
	virtual ~CIniKey();

public:
	BOOL IsLegal();	//是否合法，即m_strKeyName不为空

	CString GetKeyValue();
	void SetKeyValue(const CString &strValue);
	CString GetKeyName();
	void SetKeyName(const CString &strName);
	void Save(CString &strKey);
	void Save(CFile *pFile = NULL);

public:
	CString m_strKeyValue;
};

void inline Ini_WriteString(CFile *pFile, const CString &strText)
{
	char *pszString = NULL;
#ifdef _UNICODE
	CString_to_char(strText, &pszString);
	pFile->Write(pszString, strlen(pszString));
	delete pszString;
#else
	pFile->Write(strText, strText.GetLength());
#endif
}
#endif // !defined(AFX_INIKEY_H__9221D704_B72C_4F8A_8F7E_5D0717121DB8__INCLUDED_)
