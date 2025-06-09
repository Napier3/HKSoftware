// IniSection.h: interface for the CIniSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INISECTION_H__3728486B_1FA3_49BD_9326_FAA4832D903C__INCLUDED_)
#define AFX_INISECTION_H__3728486B_1FA3_49BD_9326_FAA4832D903C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IniKey.h"

class CIniSection : public CExBaseList
{
public:
	CIniSection();
	CIniSection(const CString &strSectionName);
	virtual ~CIniSection();

	//����Section������
	void SetSectionName(const CString &strName);
	void SetSectionName(const char *pszName);

	//���Section������
	CString GetSectionName();
	
	////����Key���ƻ�ȡKey������
	CString operator[](const CString &strKeyName);
	CString operator[](const char *pszKeyName);
	CString GetKeyValue(const CString &strKeyName, const CString &strValue=_T(""));
	CString GetKeyValue(const char *pszKeyName, const char *pszValue="");
	long GetKeyValueLong(const CString &strKeyName, const long &nDefValue=0);
	long GetKeyValueLong(const char *pszKeyName, const long &nDefValue=0);
	BOOL SetKeyValue(const CString &strKeyName,const CString &strKeyValue);
	BOOL SetKeyValue(const char *pszKeyName,const char *pszKeyValue);
	
	//����Key���ƻ�ȡKey����
	CIniKey* GetKey(const CString &strKeyName);
	CIniKey* GetKey(const char* pszKeyName);
	
	//�����µ�Key����
	CIniKey* InsertKey(const char *pszKeyName,const char *pszKeyValue);
	CIniKey* InsertKey(const CString &strKeyName,const CString &strKeyValue);
	
	//Ϊͨ��Key��������Section�����Key����ƵĽӿ�
	long GetKeyCount();
	CIniKey* GetKey(long lIndex);
	CIniKey* operator[](long lIndex);
	
	//ɾ��Key����
	BOOL DeleteKey(const CString &strKeyName);
	BOOL DeleteKey(const char *pszKeyName);
	BOOL DeleteKey(CIniKey *pKey);

	//����
	void Save(CString &strSection);
	void Save(CFile *pFile = NULL);

private:
	void SaveSectionName(CString &strSection);
};

#endif // !defined(AFX_INISECTION_H__3728486B_1FA3_49BD_9326_FAA4832D903C__INCLUDED_)
