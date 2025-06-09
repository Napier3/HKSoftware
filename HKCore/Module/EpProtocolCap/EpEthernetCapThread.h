#pragma once


#include "EpEthernetCapGlobalDef.h"
#include "EpCapThreadBase.h"
#include "Config\EmcNetDevice.h"

// extern long g_nEpEthernetCapError;

class CEpEthernetCapThread : public CEpCapThreadBase
{
public:
	CEpEthernetCapThread(void);
	~CEpEthernetCapThread(void);

	virtual UINT GetClassID()	{	return CAPTHREAD_ETHERNET;	}

	static CEpEthernetCapThread* CreateCapThread()
	{
		CEpEthernetCapThread *pThread = new CEpEthernetCapThread();
		return pThread;
	}

protected:
	pcap_t *m_adhandle;
	BOOL m_bLoopMode;
	CEmcNetDevice *m_pCapConfig;
	char m_packet_filter[4096];
	BOOL m_bRestartWinCap;
	long m_nEpEthernetCapError;

	long m_nCapIpCount;
	DWORD m_dwCapIps[MAX_PATH];

	BOOL m_bCapTcp;
	BOOL m_bCapOther;
	BOOL m_bCapUdp;
	BOOL m_bCapAllIP;
	CStringA m_strNetCardID;

protected:
	void SetCap(BOOL bUdp, BOOL bTcp, BOOL bCapOther)
	{
		m_bCapUdp = bUdp;
		m_bCapTcp = bTcp;
		m_bCapOther = bCapOther;
	}

	virtual DWORD CreateCaptureThread();
	virtual void ExitCapture();
	long StartWinPcap();
	BOOL IsIpIn(DWORD dwIP);
	void CloseWinCap();

public:
	void SetCapConfig(CEmcNetDevice *pCapConfig);//	{	m_pCapConfig = pCapConfig;	}
	void SetCaptureLoopMode();
	void SetCaptureNextMode();
	UINT GetNetCardIndex()	{	return m_pCapConfig->m_nNetCardIndex;		}
	void SetRestartWinCap()	{	m_bRestartWinCap = TRUE;	}
	BOOL CanRestartNetCap(BOOL bReset);

protected:
	static UINT CaptureThread(LPVOID pParam);	
	static UINT ParseThread(LPVOID pParam);	
	static void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

	void packet_handler_r(const struct pcap_pkthdr *header, const u_char *pkt_data);
	void packet_handler_ip(CCapCycleMemBuffer *pCapBuffer, const struct pcap_pkthdr *header, const ep_ip_header *iph);
	void packet_handler_ip_ex(CCapCycleMemBuffer *pCapBuffer, const struct pcap_pkthdr *header, const ep_ip_header *iph);
	void packet_handler_vlan(CCapCycleMemBuffer *pCapBuffer, const struct pcap_pkthdr *header, const ep_vlan_header *vlanph);
	void packet_handler_arp(CCapCycleMemBuffer *pCapBuffer, const struct pcap_pkthdr *header, const arphead *vlanph);
	CCapCycleMemBuffer* packet_handler_ip_tcp(CCapCycleMemBuffer *pCapBuffer, const struct pcap_pkthdr *header, const ep_ip_header *iph);
	CCapCycleMemBuffer* packet_handler_ip_udp(CCapCycleMemBuffer *pCapBuffer, const struct pcap_pkthdr *header, const ep_ip_header *iph);
	void packet_handler_ip_icmp(const struct pcap_pkthdr *header, const ep_ip_header *iph);
	void packet_handler_ip_igmp(const struct pcap_pkthdr *header, const ep_ip_header *iph);

	void GetFilterString(CString &strFilter);
	void InitFilters();
};
