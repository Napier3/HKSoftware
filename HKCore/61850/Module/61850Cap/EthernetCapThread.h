#pragma once


#include "EthernetCapGlobalDef.h"
#include "CapThreadBase.h"

// extern long g_nEthernetCapError;

class CEthernetCapThread : public CCapThreadBase
{
public:
	CEthernetCapThread(void);
	~CEthernetCapThread(void);

	static CEthernetCapThread* CreateNew()
	{
		CEthernetCapThread *pThread = new CEthernetCapThread();
		return pThread;
	}

protected:
	pcap_t *m_adhandle;
	BOOL m_bLoopMode;
	char m_packet_filter[4096];
	BOOL m_bRestartWinCap;
	long m_nEthernetCapError;

	ETHER_CAP_CONFIG m_oEtherCapConfig;

protected:
	virtual DWORD CreateCaptureThread();
	virtual void ExitCapture();

	long StartWinPcap();
	void CloseWinCap();

public:
	void SetCapConfig(PETHER_CAP_CONFIG pConfig, DWORD dwMask=CAPCFGMASK_ALL);
	PETHER_CAP_CONFIG GetCapConfig()				{	return &m_oEtherCapConfig;		}

	void SetCaptureLoopMode();
	void SetCaptureNextMode();
	UINT GetNetCardIndex()	{	return m_oEtherCapConfig.nNetCardIndex;		}
	void SetRestartWinCap()	{	m_bRestartWinCap = TRUE;	}
	BOOL CanRestartNetCap(BOOL bReset);

protected:
	static UINT CaptureThread(LPVOID pParam);	
	static UINT ParseThread(LPVOID pParam);	
	static void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

	void packet_handler_r(const struct pcap_pkthdr *header, const u_char *pkt_data);
// 	void packet_handler_ip(const struct pcap_pkthdr *header, const _ip_header *iph);
// 	CFrameMemBuffer* packet_handler_ip_tcp(const struct pcap_pkthdr *header, const _ip_header *iph);
// 	CFrameMemBuffer* packet_handler_ip_udp(const struct pcap_pkthdr *header, const _ip_header *iph);
// 	void packet_handler_ip_icmp(const struct pcap_pkthdr *header, const _ip_header *iph);
// 	void packet_handler_ip_igmp(const struct pcap_pkthdr *header, const _ip_header *iph);

	void GetFilterString(CString &strFilter);
	void InitFilters();
};
