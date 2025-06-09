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
	//保存ini文件
	void Save();
	void SaveAs(CString &strFile);
	void Save(CString &strData);
	
	//########################## Section管理 #######################################
	//通过Section名称获取Section对象
	CIniSection* GetSection(const CString &strSectionName);
	CIniSection* GetSection(const char *pszSectionName);
	CIniSection* operator[](const CString &strSectionName);
	CIniSection* operator[](const char *pszSectionName);
	
	//插入新的Section对象
	CIniSection* InsertSection(const CString &strSectionName);
	CIniSection* InsertSection(const char *pszSectionName);
	
	//删除Section对象
	BOOL DeleteSection(const CString &strSectionName);
	BOOL DeleteSection(const char *pszSectionName);
	
	//为通过Section的索引获取Section对象提供的接口
	long GetSectionCount();
	CIniSection* GetSection(long lIndex);
	CIniSection* operator[](long lIndex);
	
	//通过Section名称、Key名称获取Key数据
	CString GetKeyValue(const CString &strSectionName,const CString &strKeyName);
	CString GetKeyValue(const char *pszSectionName,const char *pszKeyName);
	
	//通过Section名称、Key名称获取Key对象
	CIniKey* GetKey(const CString &strSectionName,const CString &strKeyName);
	CIniKey* GetKey(const char *pszSectionName,const char *pszKeyName);
	
	//########################## Key管理 #######################################
	//插入新的Key
	CIniKey* InsertKey(const CString &strSectionName,const CString &strKeyName,const CString &strKeyValue);
	CIniKey* InsertKey(const char *pszSectionName,const char *pszKeyName,const char *pszKeyValue);
	
	//删除Key
	BOOL DeleteKey(const CString &strSectionName,const CString &strKeyName);
	BOOL DeleteKey(const char *pszSectionName,const char *pszKeyName);

private:
	CString m_strIniFile;
	
	void Save(CFile *pFile);
};

#endif // !defined(AFX_INIFILE_H__FD1FFE80_8CCB_4DE8_99FA_12BAE2B5BE49__INCLUDED_)
