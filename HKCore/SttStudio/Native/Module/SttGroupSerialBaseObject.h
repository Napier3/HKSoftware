#pragma once

#include "../../Module/BaseClass/ExBaseList.h"
#include "SttTestBase/SttXmlSerializeBase.h"


class CSttTestAppCfg : public CExBaseList
{
public:
	CSttTestAppCfg();
	virtual ~CSttTestAppCfg();

private:
	CString m_strFile;
	
private:
	CString m_strMacroFileID;
	CString m_strType; 
	CString m_strLocalIP;
	CString m_strTestAppIP;
	long m_nTestServerPort;
	long m_nNativeServerPort;
	CString m_strMulticastIP;
	long m_nMulticastPort;
	CString m_strCloudIP;
	long m_nCloudServerPort;
	long m_nMultiLocalPort;
	CString m_strTestAppSN;

	CString m_strCopName;
	CString m_strUserName;

public:
	BOOL IsMacroFileID(const CString &strMacroFileID)	{	return m_strMacroFileID == strMacroFileID;	}
	CString GetMacroFileID()	{	return m_strMacroFileID;	}
	CString GetLocalIP()	{	return m_strLocalIP;	}
	long GetMultiLocalPort()	{	return m_nMultiLocalPort;	}
	CString GetTestAppIP()	{	return m_strTestAppIP;	}
	long GetTestServerPort()	{	return m_nTestServerPort;	}
	long GetNativeServerPort()	{	return m_nNativeServerPort;	}
	CString GetMulticastIP()	{	return m_strMulticastIP;	}
	long GetMulticastPort()	{	return m_nMulticastPort;	}
	CString GetCloudIP()	{	return m_strCloudIP;	}
	long GetCloudServerPort()	{	return m_nCloudServerPort;	}
	CString GetCopName()	{	return m_strCopName;	}
	CString GetUserName()	{	return m_strUserName;	}
	CString GetTestAppSN()	{	return m_strTestAppSN;	}

	void SetLocalIP(const CString &strVal)		{	m_strLocalIP = strVal;	}
	void SetTestAppIP(const CString &strVal)		{	m_strTestAppIP = strVal;	}
	void SetTestServerPort(long nVal)			{	m_nTestServerPort = nVal;	}
	void SetNativeServerPort(long nVal)			{	m_nNativeServerPort = nVal;	}
	void SetMulticastIP(const CString &strVal)	{	m_strMulticastIP = strVal;	}
	void SetMulticastPort(long nVal)				{	m_nMulticastPort = nVal;	}
	void SetCloudIP(const CString &strVal)		{	m_strCloudIP = strVal;	}
	void SetCloudServerPort(long nVal)			{	m_nCloudServerPort = nVal;	}
	void SetCopName(const CString &strVal)		{	m_strCopName = strVal;	}
	void SetUserName(const CString &strVal)		{	m_strUserName = strVal;	}
	void SetTestAppSN(const CString &strVal)		{	m_strTestAppSN = strVal;	}

	BOOL IsLocal()			{	return m_strType == STT_TEST_APP_TYPE_LOCAL;	}
	void SetLocalApp()	{	m_strType = STT_TEST_APP_TYPE_LOCAL;	}
	void SetRemoteApp()	{	m_strType = STT_TEST_APP_TYPE_REMOTE;	}

private:
	long Save();
	long Open();
	CString GetFileName()	{	return	 m_strFile; }
	void SetFileName(const CString &strFile)	{	m_strFile = strFile;	}

public:
	//2021-8-12  lijunqing
	CString GetSttCfgFile();
	CString GetOldCfgFile();
	void SttOpen(const CString &strFile);
	void SttSave(const CString &strFile);
	void SttSetXml(const CString &strXml);
	void SttSetXml_UTF8(const CString &strXml);
	void SttSetXml_UTF8(char *pszBuffer, long nLen);
	BOOL stt_xml_serialize(CSttXmlSerializeBase *pXmlSierialize);

	void SaveAfterConfig();
public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return m_strTestAppCfgKey;	}

private:
	static BSTR m_strTestAppCfgKey;
	static BSTR m_strTypeKey;
	static BSTR m_strLocalIPKey;
	static BSTR m_strTestAppIPKey;
	static BSTR m_strTestAppSNKey;
	static BSTR m_strTestServerPortKey;
	static BSTR m_strNativeServerPortKey;
	static BSTR m_strMulticastIPKey;
	static BSTR m_strMulticastPortKey;
	static BSTR m_strMultiLocalPortKey;
	static BSTR m_strCloudIPKey;
	static BSTR m_strCloudServerPortKey;
	static BSTR m_strCopNameKey;
	static BSTR m_strUserNameKey;
};

/////////////////////////////////////////////////////////////////////////////
//CSttTestApps
class CSttTestApps : public CExBaseList
{
public:
	CSttTestApps();
	virtual ~CSttTestApps();

public:
	static CSttTestApps* g_pSttTestApps;
	static long g_nSttTestAppsRef;

	CString m_strFile;

public:
	static CSttTestApps* Create();
	static void Release();

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR GetXmlElementKey()	{      return m_strTestAppsKey;	}
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	CSttTestAppCfg* FindByMacroFileID(const CString &strMacroFileID);
	CSttTestAppCfg* FindByType(const CString &strType)		{	return FindByMacroFileID(strType);	}

public:
	long Save();
	long Open();

private:
	static BSTR m_strTestAppsKey;
};
