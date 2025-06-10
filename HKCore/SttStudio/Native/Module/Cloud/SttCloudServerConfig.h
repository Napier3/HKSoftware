#pragma once

#include "../../../Module/BaseClass/ExBaseObject.h"

class CSttCloudServerConfig : public CExBaseObject
{
private:
	CSttCloudServerConfig();
	virtual ~CSttCloudServerConfig();

private:
	static CSttCloudServerConfig* g_pSttCloudServerConfig;
	static long g_nSttCloudServerConfigRef;

	CString m_strFile;
	
public:
	static CSttCloudServerConfig* Create();
	static void Release();

public:
	long m_nPort;
	CString m_strIP;
	CString m_strRemoteCtrlHisRoot;
	long m_nMysqlPort;
	long m_nMaxClientCount;

	static CString GetSvrIP()	{	return g_pSttCloudServerConfig->m_strIP;	}
	static long GetSvrPort()	{	return g_pSttCloudServerConfig->m_nPort;	}
	static CString GetRemoteCtrlHisRoot()	{	return g_pSttCloudServerConfig->m_strRemoteCtrlHisRoot;	}
	static long GetMysqlPort()	{	return g_pSttCloudServerConfig->m_nMysqlPort;	}
	static long GetMaxClientCount()	{	return g_pSttCloudServerConfig->m_nMaxClientCount;	}

public:
	long Save();
	long Open();

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return m_strServerConfigKey;	}

private:
	static BSTR m_strServerConfigKey;
	static BSTR m_strIPKey;
	static BSTR m_strPortKey;
	static BSTR m_strRemoteCtrlHisRootKey;
	static BSTR m_strMysqlPortKey;
	static BSTR m_strMaxClientCountKey;
};