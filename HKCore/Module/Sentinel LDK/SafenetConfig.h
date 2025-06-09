#pragma once

/*
	功能描述：自动测试配置；设置自动测试过程中相关的配置
	关联文件：Safenet.xml/TCtrlCnr.ini
*/
#include "SafenetXMLRWKeys.h"

class CSafenetConfig : public CExBaseObject
{
private:
	CSafenetConfig();
	virtual ~CSafenetConfig();

public:
	static CSafenetConfig* g_pSafenetConfig;
	static long g_nSafenetConfigRef;
	static CString g_strSafenetConfigFile;
	static CString g_strSafenetServerConfigFile;

	static CSafenetConfig* Create(BOOL bCreateServer);
	static void Release();

public:
	//Test
	long m_nServerPort;
	CString m_strServerIP;
	CString m_strUserID;
	CString m_strUserPsw;
	long    m_nUseServer;

	CString m_strSeverHostName;			//服务器主机名
	CString m_strSeverMac;				//服务器主机网卡Mac
	CString m_strLocalGatewayMac;		//客户端网关Mac
	long m_nAccessType;					//访问服务器方式，0：IP,1:主机名【必须是同一用户组局域网内】
public:
	long Save();
	long Open(const CString &strConfigFile);

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return CSafenetXMLRWKeys::g_pSafenetRWKeys->m_strSafenetKey;	}

	static BOOL IsSafenetServer();
	static CString GetServerIP();
	static long GetServerPort();
	static CString GetUserID();
	static CString GetUserPsw();

	static CString GetSeverHostName();
	static CString GetSeverMac();
	static CString GetLocalGatewayMac();
	static long GetAccessType();
	static CString GetServerIPOrHost();
	
	static void SetServerIP(const CString &strIP);
	static void SetServerPort(UINT nPort);
	static void SetUserID(const CString &strUserID);
	static void SetUserPsw(const CString &strUserPsw);

private:
	CString m_strSafenetConfigFile;
	CString GetSafenetConfigFile(const CString &strConfigFile);
	BOOL InitSafenetServer();
};