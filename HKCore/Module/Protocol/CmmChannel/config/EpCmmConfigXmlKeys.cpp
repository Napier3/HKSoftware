#include "stdafx.h"
#include "EpCmmConfigXmlKeys.h"

CEpCmmConfigXmlKeys* CEpCmmConfigXmlKeys::g_pXmlRWKeys = NULL;
long CEpCmmConfigXmlKeys::g_nProtocolXmlRWKeysRef = 0;


CEpCmmConfigXmlKeys* CEpCmmConfigXmlKeys::Create()
{
	if (g_pXmlRWKeys == NULL)
	{
		g_pXmlRWKeys = new CEpCmmConfigXmlKeys();
	}

	g_nProtocolXmlRWKeysRef++;

	return g_pXmlRWKeys;
}

void CEpCmmConfigXmlKeys::Release()
{
	g_nProtocolXmlRWKeysRef--;

	if (g_nProtocolXmlRWKeysRef == 0)
	{
		delete g_pXmlRWKeys;
		g_pXmlRWKeys = NULL;
	}
}


CEpCmmConfigXmlKeys::CEpCmmConfigXmlKeys()
{
	//Õ®—∂≈‰÷√
	m_strCmmConfigKey = L"comm-config";
	m_strSerialKey  = L"serial";
	m_strNetKey = L"net";
	m_strTcpServerKey  = L"tcp-server";
	m_strTcpClientKey  = L"tcp-client";
	m_strUdpServerKey  = L"udp-server";
	m_strUdpClientKey  = L"udp-client";

	//serial
	m_strPortNumKey   = L"port_number";
	m_strBaudRateKey  = L"baud-rate";
	m_strByteSizeKey  = L"byte-size";
	m_strStopBitsKey  = L"stop-bit";
	m_strParityKey  = L"parity";
	
	//net
	m_strLocalIPKey  = L"local-ip";
	m_strLocalPortKey  = L"local-port";
	m_strRemotePortKey  = L"remote-port";
	m_strRemoteIPKey  = L"remote-ip";
	m_strMulticastIPKey = L"multicast-ip";
	m_strMulticastPortKey = L"multicast-port";
	m_strUseBroadcastKey = L"use-broadcast";
	m_strClientIPKey = L"client-ip";

	m_strSendTimeout = L"send-time-out";
	m_strReceiveTimeout = L"receive-time-out";
}
