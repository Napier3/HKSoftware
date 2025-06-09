#ifndef _EpCmmConfigXmlKeys_h__
#define _EpCmmConfigXmlKeys_h__

#include "..\..\..\baseclass\baseobject.h"

class CEpCmmConfigXmlKeys :public CXmlRWKeys
{
public:
	CEpCmmConfigXmlKeys();
	virtual ~CEpCmmConfigXmlKeys(){};

public:
	static CEpCmmConfigXmlKeys* g_pXmlRWKeys;
	static CEpCmmConfigXmlKeys* Create();
	static void Release();
	static long g_nProtocolXmlRWKeysRef;

public:
	//Õ®—∂≈‰÷√
	BSTR m_strCmmConfigKey;
	BSTR m_strSerialKey;
	BSTR m_strNetKey;

	BSTR m_strTcpServerKey;
	BSTR m_strTcpClientKey;
	BSTR m_strUdpServerKey;
	BSTR m_strUdpClientKey;

	//serial
	BSTR m_strPortNumKey;
	BSTR m_strBaudRateKey;
	BSTR m_strByteSizeKey;
	BSTR m_strStopBitsKey;
	BSTR m_strParityKey;
	
	//net
	BSTR m_strLocalIPKey;
	BSTR m_strLocalPortKey;
	BSTR m_strRemotePortKey;
	BSTR m_strRemoteIPKey;
	BSTR m_strMulticastIPKey;
	BSTR m_strMulticastPortKey;
	BSTR m_strUseBroadcastKey;
	BSTR m_strClientIPKey;

	BSTR m_strSendTimeout;
	BSTR m_strReceiveTimeout;
};

#endif//_EpCmmConfigXmlKeys_h__
