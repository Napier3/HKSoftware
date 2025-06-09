#pragma once

#include "../../Module/BaseClass/ExBaseObject.h"

#define MQTT_SERVER_TEST_MODE_FUNCTION			 _T("Function")
#define MQTT_SERVER_TEST_MODE_FUNCTION_PROTOCOL  _T("Function+Protocol")

class CMqttServerConfig : public CExBaseObject
{
private:
	CMqttServerConfig();
	virtual ~CMqttServerConfig();
	CString m_strFile;

private:
	static CMqttServerConfig* g_pMqttServerConfig;
	static long g_nMqttServerConfigRef;

public:
	CString m_strDBIP;
	CString m_strDBPort;
	CString m_strDBEncoding;
	CString m_strDBPassword;
	CString m_strDBName;
	CString m_strTestMode;

	static CMqttServerConfig* Create();
	static void Release();

	static CString GetDBIP(){ return g_pMqttServerConfig->m_strDBIP; }
	static CString GetDBPort(){ return g_pMqttServerConfig->m_strDBPort; }
	static CString GetDBEncoding(){ g_pMqttServerConfig->m_strDBEncoding.MakeLower();	return g_pMqttServerConfig->m_strDBEncoding; }
	static CString GetDBPasswd(){ return g_pMqttServerConfig->m_strDBPassword; }
	static CString GetDBName()	{	return g_pMqttServerConfig->m_strDBName;	}
	static BOOL IsTestModeFunction_Protocol(){	return g_pMqttServerConfig->m_strTestMode == MQTT_SERVER_TEST_MODE_FUNCTION_PROTOCOL;	}

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{  return m_strServerConfigKey;	}


public:
	long Save();
	long Open();

private:
	static BSTR m_strServerConfigKey;

	static BSTR m_strDBIPKey;
	static BSTR m_strDBPortKey;
	static BSTR m_strDBEncodingKey;
	static BSTR m_strDBPasswordKey;
	static BSTR m_strDBNameKey;
	static BSTR m_strTestModeKey;
};