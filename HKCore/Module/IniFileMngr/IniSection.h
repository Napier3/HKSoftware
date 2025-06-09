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

	//设置Section的名称
	void SetSectionName(const CString &strName);
	void SetSectionName(const char *pszName);

	//获得Section的名称
	CString GetSectionName();
	
	////根据Key名称获取Key的数据
	CString operator[](const CString &strKeyName);
	CString operator[](const char *pszKeyName);
	CString GetKeyValue(const CString &strKeyName, const CString &strValue=_T(""));
	CString GetKeyValue(const char *pszKeyName, const char *pszValue="");
	long GetKeyValueLong(const CString &strKeyName, const long &nDefValue=0);
	long GetKeyValueLong(const char *pszKeyName, const long &nDefValue=0);
	BOOL SetKeyValue(const CString &strKeyName,const CString &strKeyValue);
	BOOL SetKeyValue(const char *pszKeyName,const char *pszKeyValue);
	
	//根据Key名称获取Key对象
	CIniKey* GetKey(const CString &strKeyName);
	CIniKey* GetKey(const char* pszKeyName);
	
	//插入新的Key对象
	CIniKey* InsertKey(const char *pszKeyName,const char *pszKeyValue);
	CIniKey* InsertKey(const CString &strKeyName,const CString &strKeyValue);
	
	//为通过Key索引访问Section对象的Key而设计的接口
	long GetKeyCount();
	CIniKey* GetKey(long lIndex);
	CIniKey* operator[](long lIndex);
	
	//删除Key对象
	BOOL DeleteKey(const CString &strKeyName);
	BOOL DeleteKey(const char *pszKeyName);
	BOOL DeleteKey(CIniKey *pKey);

	//保存
	void Save(CString &strSection);
	void Save(CFile *pFile = NULL);

private:
	void SaveSectionName(CString &strSection);
};

#endif // !defined(AFX_INISECTION_H__3728486B_1FA3_49BD_9326_FAA4832D903C__INCLUDED_)
