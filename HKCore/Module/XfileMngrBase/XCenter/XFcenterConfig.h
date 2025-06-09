#pragma once

/*
	�����������Զ��������ã������Զ����Թ�������ص�����
	�����ļ���XFcenter.xml/TCtrlCnr.ini
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

	CString m_strSeverHostName;			//������������
	CString m_strSeverMac;				//��������������Mac
	CString m_strLocalGateWayMac;       //�ͻ��˱�������MAC
	long m_nAccessType;					//���ʷ�������ʽ��0��IP,1:��������������ͬһ�û���������ڡ�

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