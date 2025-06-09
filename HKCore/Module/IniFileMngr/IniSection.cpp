// IniSection.cpp: implementation of the CIniSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniSection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniSection::CIniSection()
{
	m_strName	= "";
}

CIniSection::CIniSection(const CString &strSectionName)
{
	m_strName = strSectionName;	
}

CIniSection::~CIniSection()
{
}

//设置Section的名称
void CIniSection::SetSectionName(const CString &strName)
{
	m_strName = strName;
}

void CIniSection::SetSectionName(const char *pszName)
{
	m_strName = pszName;
}

//获得Section的名称
CString CIniSection::GetSectionName()
{
	return m_strName;
}

//根据Key名称获取Key的数据
CString CIniSection::operator[](const CString &strKeyName)
{	
	return GetKeyValue(strKeyName);
}

CString CIniSection::operator[](const char *pszKeyName)
{
	CString strKeyName;
	
	if (pszKeyName != NULL)
	{
		strKeyName = pszKeyName;
		return (*this)[strKeyName];
	}

	return _T("");
}

CString CIniSection::GetKeyValue(const CString &strKeyName, const CString &strValue)
{
	CIniKey *pIniKey = GetKey(strKeyName);
	
	if (pIniKey != NULL)
	{
		return pIniKey->m_strKeyValue;
	}
	
	return strValue;
}

CString CIniSection::GetKeyValue(const char *pszKeyName, const char *pszValue)
{
	return GetKeyValue(CString(pszKeyName), CString(pszValue));
}

long CIniSection::GetKeyValueLong(const CString &strKeyName, const long &nDefValue)
{
	CIniKey *pIniKey = GetKey(strKeyName);
	
	long nVal = nDefValue;

	if (pIniKey != NULL)
	{
		nVal = CString_To_long( pIniKey->m_strKeyValue);
	}
	
	return nVal;
}

long CIniSection::GetKeyValueLong(const char *pszKeyName, const long &nDefValue)
{
	return GetKeyValueLong(CString(pszKeyName), nDefValue);
}

BOOL CIniSection::SetKeyValue(const CString &strKeyName,const CString &strKeyValue)
{
	CIniKey *pIniKey = GetKey(strKeyName);
	
	if (pIniKey == NULL)
	{
		return FALSE;
	}
	
	pIniKey->SetKeyValue(strKeyValue);
	return TRUE;
}

BOOL CIniSection::SetKeyValue(const char *pszKeyName,const char *pszKeyValue)
{
	return SetKeyValue(CString(pszKeyName),CString(pszKeyValue));
}

//根据Key名称获取Key对象
CIniKey* CIniSection::GetKey(const CString &strKeyName)
{
	CIniKey *pIniKeyFind = (CIniKey*)FindByName(strKeyName);
	return pIniKeyFind;
}

CIniKey* CIniSection::GetKey(const char* pszKeyName)
{
	CString strKeyName;
	strKeyName = pszKeyName;
	return GetKey(strKeyName);
}

//插入新的Key对象
CIniKey* CIniSection::InsertKey(const char *pszKeyName,const char *pszKeyValue)
{
	CIniKey *pIniKey = NULL;
	pIniKey = GetKey(pszKeyName);

	if (pIniKey != NULL)
	{
		pIniKey->m_strKeyValue =pszKeyValue;
		return pIniKey;
	}

	pIniKey = new CIniKey(pszKeyName, pszKeyValue);

	if (pIniKey->IsLegal())
	{
		AddNewChild(pIniKey);
	}
	else
	{
		delete pIniKey;
		pIniKey = NULL;
	}
	
	return pIniKey;
}

CIniKey* CIniSection::InsertKey(const CString &strKeyName,const CString &strKeyValue)
{
	CIniKey *pIniKey = NULL;
	pIniKey = GetKey(strKeyName);

	if (pIniKey != NULL)
	{
		pIniKey->SetKeyValue(strKeyValue);
		return pIniKey;
	}

	pIniKey = new CIniKey(strKeyName, strKeyValue);
	if (pIniKey->IsLegal())
	{
		AddNewChild(pIniKey);
	}
	else
	{
		delete pIniKey;
		pIniKey = NULL;
	}
	
	return pIniKey;
}

//为通过Key索引访问Section对象的Key而设计的接口
long CIniSection::GetKeyCount()
{	
	return GetCount();
}

CIniKey* CIniSection::GetKey(long lIndex)
{
	return (*this)[lIndex];
}

CIniKey* CIniSection::operator[](long lIndex)
{
	CIniKey *pIniKey = NULL;
	POS pos = FindIndex(lIndex);
	
	if (pos != NULL)
	{	
		pIniKey = (CIniKey *)GetAt(pos);		
	}	
		
	return pIniKey;
}

//删除Key对象
BOOL CIniSection::DeleteKey(const CString &strKeyName)
{
	CIniKey *pKey = NULL;
	pKey = GetKey(strKeyName);
	return DeleteKey(pKey);
}

BOOL CIniSection::DeleteKey(const char *pszKeyName)
{
	CIniKey *pKey = NULL;
	pKey = GetKey(pszKeyName);
	return DeleteKey(pKey);
}

BOOL CIniSection::DeleteKey(CIniKey *pKey)
{	
	CIniKey *pIniKey = NULL;
	POS pos = Find(pKey);
	
	if (pos != NULL)
	{	
		RemoveAt(pos);
		delete pIniKey;
		return TRUE;
	}	
	
	return FALSE;	
}

void CIniSection::Save(CString &strSection)
{
	CString strTemp("");
	SaveSectionName(strTemp);
	strSection += strTemp;

	CIniKey *pIniKey = NULL;
	POS pos = GetHeadPosition();
	
	while (pos != NULL)
	{	
		pIniKey = (CIniKey*)GetNext(pos);
		pIniKey->Save(strTemp);
		strSection += strTemp;
	}
	strSection += "\r\n";
}

void CIniSection::Save(CFile *pFile)
{
	if (pFile == NULL)
	{
		return;
	}

	CString strTemp("");
	CString strNewLine("\r\n");

	SaveSectionName(strTemp);
	Ini_WriteString(pFile, strTemp);

	CIniKey *pIniKey = NULL;
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{	
		pIniKey = (CIniKey*)GetNext(pos);
		pIniKey->Save(pFile);
	}	

	Ini_WriteString(pFile, strNewLine);
}

inline void CIniSection::SaveSectionName(CString &strSection)
{
	strSection.Format(_T("[%s]\r\n"), m_strName);
}
