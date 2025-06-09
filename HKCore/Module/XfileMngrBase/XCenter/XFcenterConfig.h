#pragma once

/*
	功能描述：自动测试配置；设置自动测试过程中相关的配置
	关联文件：XFcenter.xml/TCtrlCnr.ini
*/
#include "XFcenterXMLRWKeys.h"

class CXFcenterConfig : public CExBaseObject
{
private:
	CXFcenterConfig();
	virtual ~CXFcenterConfig();

public:
	static CXFcenterConfig* g_pXFcenterConfig;
	static long g_nXFcenterConfigRef;
	static CString g_strXFcenterServerConfigFile;

	static CXFcenterConfig* Create();
	static void Release();

public:
	//Test
	long m_nServerPort;
	CString m_strServerIP;
	CString m_strUserID;
	CString m_strUserPsw;
	long    m_nUseServer;

	CString m_strReportFileMngrID;
	CString m_strTestTemplateFileMngrID;
	CString m_strProtocolFileMngrID;

	CString m_strSeverHostName;			//服务器主机名
	CString m_strSeverMac;				//服务器主机网卡Mac
	CString m_strLocalGateWayMac;       //客户端本地网关MAC
	long m_nAccessType;					//访问服务器方式，0：IP,1:主机名【必须是同一用户组局域网内】

public:
	long Save();
	long Open(const CString &strConfigFile);

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return CXFcenterXMLRWKeys::g_pXFcenterRWKeys->m_strXFcenterKey;	}

	static BOOL IsXFcenterServer();
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

	static void SaveConfigFile();

	static CString GetReportFileMngrID();
	static CString GetTestTemplateFileMngrID();
	static CString GetProtocolFileMngrID();
	static void SetReportFileMngrID(const CString &strID);
	static void SetTestTemplateFileMngrID(const CString &strID);
	static void SetProtocolFileMngrID(const CString &strID);

	static CExBaseList* GetBuckets();

private:
	CString m_strXFcenterConfigFile;
	CString GetXFcenterConfigFile(const CString &strConfigFile);
	BOOL InitXFcenterServer();

	CExBaseList m_listBucket;
};