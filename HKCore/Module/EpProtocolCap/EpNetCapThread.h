#pragma once


//#include "EpCapThreadGlobalDef.h"
#include "CapCycleMemBufferMngr.h"
#include "..\ProtocolBase\ProtocolBase.h"


class CEpNetCapThread
{
public:
	CEpNetCapThread(void);
	~CEpNetCapThread(void);

	static CEpNetCapThread* CreateCapThread(CProtocolBase *pProtocol)
	{
		CEpNetCapThread *pThread = new CEpNetCapThread();
		pThread->m_pProtocol = pProtocol;
		return pThread;
	}

protected:
	CWinThread *m_pCaptureThread;
	CWinThread *m_pParseThread;
	pcap_t *m_adhandle;
	CCapCycleMemBufferMngr m_oCapCycleBufferMngr;
	CProtocolBase *m_pProtocol;  //关联的规约对象

public:
	ep_cap_filters* GetFilters()	{	return &(m_oCapConfig.filters);	}
	ep_cap_config* GetCapConfig()	{	return &m_oCapConfig;	}
	CCapCycleMemBufferMngr* GetCapCycleMemBufferMngr()	{	return &m_oCapCycleBufferMngr;	}
	void SetCaptureLoopMode();
	void SetCaptureNextMode();
	
	void StartCapture();
	void StopCapture();
	void ResumeCapture();
	void ExitCapture();
	BOOL HasAllCapThreadExit();
	BOOL IsCaptureStarted();
	BOOL IsCaptureStop()	{	return m_bStopCapture;	}
	void FreeParsedBuffer()	{	m_bFreeCapBuffer = TRUE;	}
	UINT GetNetCardIndex()	{	return m_oCapConfig.nNetCardIndex;		}
//	void PacketProcess(const struct pcap_pkthdr *header, const u_char *pkt_data);

protected:
	static UINT CaptureThread(LPVOID pParam);	
	static UINT ParseThread(LPVOID pParam);	
	static void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
	void packet_handler(const struct pcap_pkthdr *header, const u_char *pkt_data);
	void packet_handler_ip(const struct pcap_pkthdr *header, const ep_ip_header *iph);
	void packet_handler_ip_tcp(const struct pcap_pkthdr *header, const ep_ip_header *iph);
	void packet_handler_ip_udp(const struct pcap_pkthdr *header, const ep_ip_header *iph);
	void packet_handler_ip_icmp(const struct pcap_pkthdr *header, const ep_ip_header *iph);
	void packet_handler_ip_igmp(const struct pcap_pkthdr *header, const ep_ip_header *iph);

protected:
	BOOL m_bLoopMode;
	BOOL m_bStopCapture;
	BOOL m_bExitCapture;
	BOOL m_bFreeCapBuffer;  //释放处理完毕的缓冲区

	//ep_cap_filters m_filters;
	EP_CAP_CONFIG m_oCapConfig;

protected:
	void GetFilterString(CString &strFilter);
	void FreeAllParsedBuffer();
};
