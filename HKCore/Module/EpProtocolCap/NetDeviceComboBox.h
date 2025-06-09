#pragma once

#include "EpEthernetCapGlobalDef.h"
// CNetDeviceComboBox

class CNetDeviceComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CNetDeviceComboBox)

public:
	CNetDeviceComboBox();
	virtual ~CNetDeviceComboBox();

	void InitNetDevice(BOOL bOnllyShowDesc=FALSE);
	CString GetIp()	{	return m_strIP;	}

	void GetIp(BYTE &byte1, BYTE &byte2, BYTE &byte3, BYTE &byte4)
	{
		byte1 = m_byte1;
		byte2 = m_byte2;
		byte3 = m_byte3;
		byte4 = m_byte4;
	}

private:
	pcap_if_t *alldevs;

	CString m_strIP;
	BYTE m_byte1;
	BYTE m_byte2;
	BYTE m_byte3;
	BYTE m_byte4;
	void InitIp(pcap_if_t *d);

protected:
	DECLARE_MESSAGE_MAP()
};


