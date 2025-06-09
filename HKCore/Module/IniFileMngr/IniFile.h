#if !defined(AFX_INIFILE_H__FD1FFE80_8CCB_4DE8_99FA_12BAE2B5BE49__INCLUDED_)
#define AFX_INIFILE_H__FD1FFE80_8CCB_4DE8_99FA_12BAE2B5BE49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IniSection.h"

class CIniFile : public CExBaseList
{
public:
	CIniFile();
	CIniFile(const CString &strFile);
	virtual ~CIniFile();
	
	BOOL SetIniFile(const CString &strFile);
	//����ini�ļ�
	void Save();
	void SaveAs(CString &strFile);
	void Save(CString &strData);
	
	//########################## Section���� #######################################
	//ͨ��Section���ƻ�ȡSection����
	CIniSection* GetSection(const CString &strSectionName);
	CIniSection* GetSection(const char *pszSectionName);
	CIniSection* operator[](const CString &strSectionName);
	CIniSection* operator[](const char *pszSectionName);
	
	//�����µ�Section����
	CIniSection* InsertSection(const CString &strSectionName);
	CIniSection* InsertSection(const char *pszSectionName);
	
	//ɾ��Section����
	BOOL DeleteSection(const CString &strSectionName);
	BOOL DeleteSection(const char *pszSectionName);
	
	//Ϊͨ��Section��������ȡSection�����ṩ�Ľӿ�
	long GetSectionCount();
	CIniSection* GetSection(long lIndex);
	CIniSection* operator[](long lIndex);
	
	//ͨ��Section���ơ�Key���ƻ�ȡKey����
	CString GetKeyValue(const CString &strSectionName,const CString &strKeyName);
	CString GetKeyValue(const char *pszSectionName,const char *pszKeyName);
	
	//ͨ��Section���ơ�Key���ƻ�ȡKey����
	CIniKey* GetKey(const CString &strSectionName,const CString &strKeyName);
	CIniKey* GetKey(const char *pszSectionName,const char *pszKeyName);
	
	//########################## Key���� #######################################
	//�����µ�Key
	CIniKey* InsertKey(const CString &strSectionName,const CString &strKeyName,const CString &strKeyValue);
	CIniKey* InsertKey(const char *pszSectionName,const char *pszKeyName,const char *pszKeyValue);
	
	//ɾ��Key
	BOOL DeleteKey(const CString &strSectionName,const CString &strKeyName);
	BOOL DeleteKey(const char *pszSectionName,const char *pszKeyName);

private:
	CString m_strIniFile;
	
	void Save(CFile *pFile);
};

#endif // !defined(AFX_INIFILE_H__FD1FFE80_8CCB_4DE8_99FA_12BAE2B5BE49__INCLUDED_)
