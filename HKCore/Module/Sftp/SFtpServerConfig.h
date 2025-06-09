#pragma once

#include "../../Module/BaseClass/ExBaseObject.h"

class CSFtpServerConfig : public CExBaseObject
{
private:
	CSFtpServerConfig();
	virtual ~CSFtpServerConfig();

private:
	static CSFtpServerConfig* g_pSFtpServerConfig;
	static long g_nFtpServerConfigRef;

	CString m_strFile;
	
public:
	static CSFtpServerConfig* Create();
	static void Release();

public:
	//Test
	CString m_strSftpUser;
	CString m_strSFtpPSW;
	CString m_strServerIP;
	long m_nSftpPort;
	CString m_strServerDir;

	static CString GetServerIP()	{	return g_pSFtpServerConfig->m_strServerIP;	}
	static CString GetSftpUser()	{	return g_pSFtpServerConfig->m_strSftpUser;	}
	static CString GetSftpPsw()	{	return g_pSFtpServerConfig->m_strSFtpPSW;	}
	static CString GetSftpServerDir()	{	return g_pSFtpServerConfig->m_strServerDir;	}
	static long GetSftpPort()	{	return g_pSFtpServerConfig->m_nSftpPort;	}
	
public:
	long Save();
	long Open();

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return m_strServerConfigKey;	}

private:
	static BSTR m_strServerConfigKey;
	static BSTR m_strServerIPKey;
	static BSTR m_strServerSFtpUserKey;
	static BSTR m_strServerSFtpPswKey;
	static BSTR m_strSftpPortKey;
	static BSTR m_strServerDirKey;
};