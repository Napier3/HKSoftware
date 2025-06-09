// IniKey.cpp: implementation of the CIniKey class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniKey.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniKey::CIniKey()
{
	m_strKeyValue	= "";	
}

CIniKey::CIniKey(const CString &strName, const CString &strValue)
{
	m_strName	= strName;
	m_strKeyValue	= strValue;
	m_strName.TrimLeft();
}

CIniKey::CIniKey(const char *pszKeyName,const char *pszKeyValue)
{
	m_strName	= pszKeyName;
	m_strKeyValue	= pszKeyValue;
	m_strName.TrimLeft();
}
CIniKey::~CIniKey()
{

}

//是否合法，即m_strName不为空
BOOL CIniKey::IsLegal()
{
	return (m_strName.GetLength() > 0) ;
}

CString CIniKey::GetKeyValue()
{
	return m_strKeyValue;
}

void CIniKey::SetKeyValue(const CString &strValue)
{
	m_strKeyValue = strValue;
}

CString CIniKey::GetKeyName()
{
	return m_strName;
}

void CIniKey::SetKeyName(const CString &strName)
{
	m_strName = strName;
	m_strName.TrimLeft();
}

void CIniKey::Save(CString &strKey)
{
	strKey.Format(_T("%s=%s\r\n"),m_strName,m_strKeyValue);
}

void CIniKey::Save(CFile *pFile)
{
	CString strTemp("");
	Save(strTemp);

	Ini_WriteString(pFile, strTemp);
}
