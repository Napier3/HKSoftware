#pragma once
#include "../../../Module/BaseClass/ExBaseObject.h"

class CSttUpdateCfg : public CExBaseObject
{
public:
	CSttUpdateCfg();
	virtual ~CSttUpdateCfg();

public:
	static CSttUpdateCfg* Create();
	static void Release();

	static CSttUpdateCfg* g_pVerUpdateCfg;
	static long g_nVerUpdateCfgRef;

	CString m_strFile;

	CString m_strSysID;
	CString m_strVerID;
	long m_nVerIdx;
	CString m_strTestAppID;

public:
	static CString GetSysID()	{	return g_pVerUpdateCfg->m_strSysID;	}
	static CString GetVerID()	{	return g_pVerUpdateCfg->m_strVerID;	}
	static long GetVerIdx()	{	return g_pVerUpdateCfg->m_nVerIdx;	}
	static CString GetTestAppID()	{	return g_pVerUpdateCfg->m_strTestAppID;	}

	static void SetSysID(const CString &strVal)			{	g_pVerUpdateCfg->m_strSysID = strVal;	}
	static void SetVerID(const CString &strVal)			{	g_pVerUpdateCfg->m_strVerID = strVal;	}
	static long SetVerIdx(long nVerIdx)					{   g_pVerUpdateCfg->m_nVerIdx = nVerIdx;	}
	static void SetTestAppID(const CString &strVal)		{	g_pVerUpdateCfg->m_strTestAppID = strVal;	}

private:
	static BSTR m_strVerUpdateCfgKey; 	//ver-update-cfg
	static BSTR m_strSysIDKey;			//sys-id
	static BSTR m_strVerIDKey;			//ver-id
	static BSTR m_strVerIdxKey;			//ver-idx
	static BSTR m_strTestAppIDKey;		//testapp-id

public:
	BOOL Save();
	BOOL Open(const CString& strPath=_T(""));

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return m_strVerUpdateCfgKey;	}
};

