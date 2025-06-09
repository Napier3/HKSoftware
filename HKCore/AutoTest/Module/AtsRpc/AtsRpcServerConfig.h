#pragma once

#include "../../Module/BaseClass/ExBaseObject.h"

class CAtsRpcServerConfig : public CExBaseObject
{
private:
	CAtsRpcServerConfig();
	virtual ~CAtsRpcServerConfig();

private:
	static CAtsRpcServerConfig* g_pAtsRpcServerConfig;
	static long g_nAtsRpcServerConfigRef;

	CString m_strFile;
	
public:
	static CAtsRpcServerConfig* Create();
	static void Release();

public:
	//Test
	CString m_strRemoteIP;
	long m_nRpcServerPort;
	CString m_strFtpUser;
	CString m_strFtpPSW;
	CString m_strLocalIP;

	static CString GetRemoteIP()	{	return g_pAtsRpcServerConfig->m_strRemoteIP;	}
	static CString GetLocalIP()	{	return g_pAtsRpcServerConfig->m_strLocalIP;	}
	static long GetRpcServerPort()	{	return g_pAtsRpcServerConfig->m_nRpcServerPort;	}
	static CString GeFtpUser()	{	return g_pAtsRpcServerConfig->m_strFtpUser;	}
	static CString GeFtpPSW()	{	return g_pAtsRpcServerConfig->m_strFtpPSW;	}
	
public:
	long Save();
	long Open();

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return m_strServerConfigKey;	}

private:
	static BSTR m_strServerConfigKey;
	static BSTR m_strRemoteIPKey;
	static BSTR m_strLocalIPKey;
	static BSTR m_strServerRpcPortKey;
	static BSTR m_strServerFtpUserKey;
	static BSTR m_strServerFtpPswKey;

};
