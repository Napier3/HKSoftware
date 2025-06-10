#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"


class CSttTestAppGateWayCfg : public CExBaseObject
{
public:
	CSttTestAppGateWayCfg();
	virtual ~CSttTestAppGateWayCfg();

private:
	static CSttTestAppGateWayCfg* g_pSttTestAppGateWayCfg;
	static long g_nSttTestAppGateWayCfgRef;

	CString m_strFile;
	
public:
	static CSttTestAppGateWayCfg* Create();
	static void Release();

private:
	CString m_strSubIP; 
	CString m_strGateWay;
	CString m_strMask;
    long m_nAutoRegister;

public:
	static CString GetSubIP()	{	return g_pSttTestAppGateWayCfg->m_strSubIP;	}
	static CString GetMask()	{	return g_pSttTestAppGateWayCfg->m_strMask;	}
	static CString GetGateWay()	{	return g_pSttTestAppGateWayCfg->m_strGateWay;	}
    static long IsAutoRegister()	{	return g_pSttTestAppGateWayCfg->m_nAutoRegister;	}

	static void SetSubIP(const CString &strVal)		{	g_pSttTestAppGateWayCfg->m_strSubIP = strVal;	}
	static void SetMask(const CString &strVal)		{	g_pSttTestAppGateWayCfg->m_strMask = strVal;	}
	static void SetGateWay(const CString &strVal)		{	g_pSttTestAppGateWayCfg->m_strGateWay = strVal;	}
    static void SetAutoRegister(long nVal)			{	g_pSttTestAppGateWayCfg->m_nAutoRegister = nVal;	}

public:
	long Save();
	long Open();
	static void SetSttTestAppGateWayCfg(CSttTestAppGateWayCfg *pCfg)	{	CSttTestAppGateWayCfg::g_pSttTestAppGateWayCfg = pCfg;	}

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return m_strTestAppGateWayCfgKey;	}

private:
	static BSTR m_strTestAppGateWayCfgKey;
	static BSTR m_strSubIPKey;
	static BSTR m_strMaskKey;
	static BSTR m_strGateWayKey;
    static BSTR m_strAutoRegisterKey;
};
