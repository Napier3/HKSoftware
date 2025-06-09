#pragma once

#include "../../../Module/BaseClass/ExBaseObject.h"

class CRdReadConfig : public CExBaseObject
{
private:
	CRdReadConfig();
	virtual ~CRdReadConfig();

private:
	static CRdReadConfig* g_pOAMngrSvrConfig;
	static long g_nOAMngrSvrConfigRef;

	CString m_strFile;
	
public:
	static CRdReadConfig* Create();
	static void Release();

public:
	//Test
	long m_nSerialPort;
	CString m_strIaAmpDesc[50];
	CString m_strIaPhaseDesc[50];
	CString m_strIaFreDesc[50];
	CString m_strIbAmpDesc[50];
	CString m_strIbPhaseDesc[50];
	CString m_strIbFreDesc[50];
	CString m_strIcAmpDesc[50];
	CString m_strIcPhaseDesc[50];
	CString m_strIcFreDesc[50];

	CString m_strUaAmpDesc[50];
	CString m_strUaPhaseDesc[50];
	CString m_strUaFreDesc[50];
	CString m_strUbAmpDesc[50];
	CString m_strUbPhaseDesc[50];
	CString m_strUbFreDesc[50];
	CString m_strUcAmpDesc[50];
	CString m_strUcPhaseDesc[50];
	CString m_strUcFreDesc[50];
	CString m_strUaTHDDesc;
	CString m_strUbTHDDesc;
	CString m_strUcTHDDesc;
	CString m_strIaTHDDesc;
	CString m_strIbTHDDesc;
	CString m_strIcTHDDesc;

	static long GetSerialPort()	{	return g_pOAMngrSvrConfig->m_nSerialPort;	}

	static CString GetIaAmpDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strIaAmpDesc[nHarmIndex];	}
	static CString GetIaPhaseDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strIaPhaseDesc[nHarmIndex];	}
	static CString GetIaFreDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strIaFreDesc[nHarmIndex];	}
	static CString GetIbAmpDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strIbAmpDesc[nHarmIndex];	}
	static CString GetIbPhaseDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strIbPhaseDesc[nHarmIndex];	}
	static CString GetIbFreDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strIbFreDesc[nHarmIndex];	}
	static CString GetIcAmpDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strIcAmpDesc[nHarmIndex];	}
	static CString GetIcPhaseDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strIcPhaseDesc[nHarmIndex];	}
	static CString GetIcFreDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strIcFreDesc[nHarmIndex];	}

	static CString GetUaAmpDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strUaAmpDesc[nHarmIndex];	}
	static CString GetUaPhaseDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strUaPhaseDesc[nHarmIndex];	}
	static CString GetUaFreDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strUaFreDesc[nHarmIndex];	}
	static CString GetUbAmpDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strUbAmpDesc[nHarmIndex];	}
	static CString GetUbPhaseDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strUbPhaseDesc[nHarmIndex];	}
	static CString GetUbFreDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strUbFreDesc[nHarmIndex];	}
	static CString GetUcAmpDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strUcAmpDesc[nHarmIndex];	}
	static CString GetUcPhaseDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strUcPhaseDesc[nHarmIndex];	}
	static CString GetUcFreDesc(long nHarmIndex)	{	return g_pOAMngrSvrConfig->m_strUcFreDesc[nHarmIndex];	}

	static CString GetUaTHDDesc()	{	return g_pOAMngrSvrConfig->m_strUaTHDDesc;	}
	static CString GetUbTHDDesc()	{	return g_pOAMngrSvrConfig->m_strUbTHDDesc;	}
	static CString GetUcTHDDesc()	{	return g_pOAMngrSvrConfig->m_strUcTHDDesc;	}
	static CString GetIaTHDDesc()	{	return g_pOAMngrSvrConfig->m_strIaTHDDesc;	}
	static CString GetIbTHDDesc()	{	return g_pOAMngrSvrConfig->m_strIbTHDDesc;	}
	static CString GetIcTHDDesc()	{	return g_pOAMngrSvrConfig->m_strIcTHDDesc;	}	

public:
	long Save();
	long Open();

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return m_strRdConfigKey;	}

private:
	static BSTR m_strRdConfigKey;
	static BSTR m_strSerialPortKey;

	BSTR m_strIaAmpKey[50];
	BSTR m_strIaPhaseKey[50];
	BSTR m_strIaFreKey[50];
	BSTR m_strIbAmpKey[50];
	BSTR m_strIbPhaseKey[50];
	BSTR m_strIbFreKey[50];
	BSTR m_strIcAmpKey[50];
	BSTR m_strIcPhaseKey[50];
	BSTR m_strIcFreKey[50];

	BSTR m_strUaAmpKey[50];
	BSTR m_strUaPhaseKey[50];
	BSTR m_strUaFreKey[50];
	BSTR m_strUbAmpKey[50];
	BSTR m_strUbPhaseKey[50];
	BSTR m_strUbFreKey[50];
	BSTR m_strUcAmpKey[50];
	BSTR m_strUcPhaseKey[50];
	BSTR m_strUcFreKey[50];

	static BSTR m_strUaTHDKey;
	static BSTR m_strUbTHDKey;
	static BSTR m_strUcTHDKey;
	static BSTR m_strIaTHDKey;
	static BSTR m_strIbTHDKey;
	static BSTR m_strIcTHDKey;
};