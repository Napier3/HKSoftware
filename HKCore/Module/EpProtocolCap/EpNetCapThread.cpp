#include "StdAfx.h"
#include "EpNetCapThread.h"

//void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

CEpNetCapThread::CEpNetCapThread(void)
{
	m_pCaptureThread = NULL;
	m_pParseThread = NULL;
	m_adhandle = NULL;
	m_bFreeCapBuffer = FALSE;
	memset(&m_oCapConfig, 0, sizeof(ep_cap_config));
	SetCaptureNextMode();
}

CEpNetCapThread::~CEpNetCapThread(void)
{
	StopCapture();
}

void CEpNetCapThread::SetCaptureLoopMode()
{
	ASSERT (m_pCaptureThread == NULL && m_adhandle == NULL);
	
	m_bLoopMode = TRUE;
}

void CEpNetCapThread::SetCaptureNextMode()
{
	ASSERT (m_pCaptureThread == NULL && m_adhandle == NULL);
	
	m_bLoopMode = FALSE;
}

void CEpNetCapThread::StartCapture()
{
	ASSERT (m_pCaptureThread == NULL && m_pParseThread == NULL);
	m_bExitCapture = FALSE;
	m_bStopCapture = FALSE;

	m_pCaptureThread = AfxBeginThread(CaptureThread,this);
	m_pCaptureThread->m_bAutoDelete = TRUE;

	m_pParseThread = AfxBeginThread(ParseThread,this);
	m_pParseThread->m_bAutoDelete = TRUE;
}

void CEpNetCapThread::StopCapture()
{
	m_bStopCapture = TRUE;
}

void CEpNetCapThread::ResumeCapture()
{
	m_bStopCapture = FALSE;
}

void CEpNetCapThread::ExitCapture()
{
	if (m_pCaptureThread == NULL || m_pParseThread == NULL)
		return;

	if (m_bExitCapture)
	{
		return;
	}
		
	m_bExitCapture = TRUE;

	if (m_bLoopMode)
	{
		if (m_adhandle != NULL)
		{
			pcap_breakloop(m_adhandle);
			m_adhandle = NULL;
		}
	}
}

BOOL CEpNetCapThread::IsCaptureStarted()
{
	if (m_pCaptureThread == NULL || m_pParseThread == NULL)
	{
		return FALSE;
	}

	if (m_bExitCapture)
	{
		return FALSE;
	}

	if (m_bStopCapture)
	{
		return TRUE;
	}

	return TRUE;
}

BOOL CEpNetCapThread::HasAllCapThreadExit()
{
	if (m_pCaptureThread != NULL || m_pParseThread != NULL)
	{
		return FALSE;
	}

	return TRUE;
}


void CEpNetCapThread::packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	CEpNetCapThread *pCapNetThread = (CEpNetCapThread*)param;

	if (pCapNetThread->IsCaptureStop())
	{
		return;
	}

	pCapNetThread->packet_handler(header, pkt_data);
}

void CEpNetCapThread::packet_handler(const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	if (IsCaptureStop())
	{
		return;
	}

	// 通知APP有数据接收到
//	theApp.m_bOnConnect = TRUE;
	struct ether_header *eth = (ether_header *)pkt_data;

	switch(ntohs(eth->ether_type))
	{
		case ETHERTYPE_IP:
			{
				//length of ethernet header
				// 获取IP报文头
				ep_ip_header *IPHead=(ep_ip_header *)(pkt_data+14);
				packet_handler_ip(header, IPHead);
			}
			break;
		default:
			break;
	}

}

void CEpNetCapThread::packet_handler_ip(const struct pcap_pkthdr *header, const ep_ip_header *iph)
{
	switch(iph->protocol)
	{
	case 1:
		break;
	case 6:
		packet_handler_ip_tcp(header, iph);
		break;
	case 17:
		packet_handler_ip_udp(header, iph);
		break;
	default:
		break;
	}
}

void CEpNetCapThread::packet_handler_ip_tcp(const struct pcap_pkthdr *header, const ep_ip_header *iph)
{
	ep_tcp_header *tcph;
	u_int ip_len;
	u_int tcph_len;

	// 获取IP报文长度
	ip_len = (iph->ver_ihl & 0xf) * 4;
	u_char *pkt_data = (u_char*)iph;

	// 获取TCP报文头
	tcph = (ep_tcp_header *) (pkt_data + ip_len);

	EP_CAP_IP_GROUP ipGroup;
	ipGroup.src.ip = iph->saddr;
	ipGroup.src.port = ntohs( tcph->sport );
	ipGroup.dst.ip = iph->daddr;
	ipGroup.dst.port = ntohs( tcph->dport );

	tcph_len = ((tcph->th_lenres & 0xf0) >> 4) * 4;
	long nDataLen = header->caplen - tcph_len - ip_len - 14/*ether_header*/;
	pkt_data = (u_char*)tcph + tcph_len;

	//if (iPSH != 0)
	{
		m_oCapCycleBufferMngr.AddCapBuffer(header->ts, ipGroup, pkt_data, nDataLen, iph->protocol);
	}
}

void CEpNetCapThread::packet_handler_ip_udp(const struct pcap_pkthdr *header, const ep_ip_header *iph)
{
	ep_udp_header *udph;
	u_int ip_len;
	u_int udph_len;
	u_int u_offset;

	// 获取IP报文长度
	ip_len = (iph->ver_ihl & 0xf) * 4;
	u_char *pkt_data = (u_char*)iph;

	// 获取TCP报文头
	udph = (ep_udp_header *) (pkt_data + ip_len);

	EP_CAP_IP_GROUP ipGroup;
	ipGroup.src.ip = iph->saddr;
	ipGroup.src.port = ntohs( udph->sport );
	ipGroup.dst.ip = iph->daddr;
	ipGroup.dst.port = ntohs( udph->dport );

	udph_len = 8;//udph->len * 4;
	u_offset = ip_len + udph_len;
	pkt_data = (u_char*)udph;
	long nlen = ((udph->len >> 8) & 0xFF) + ((udph->len & 0xFF) << 8);
	long nDataLen = nlen - 8;
	pkt_data += 8;

	//if (iPSH != 0)
	{
		m_oCapCycleBufferMngr.AddCapBuffer(header->ts, ipGroup, pkt_data, nDataLen, iph->protocol);
	}
}

void CEpNetCapThread::packet_handler_ip_icmp(const struct pcap_pkthdr *header, const ep_ip_header *iph)
{

}

void CEpNetCapThread::packet_handler_ip_igmp(const struct pcap_pkthdr *header, const ep_ip_header *iph)
{

}



UINT CEpNetCapThread::CaptureThread(LPVOID pParam)
{
	CEpNetCapThread* pThis = (CEpNetCapThread*)pParam;

	pcap_if_t *alldevs;
	pcap_if_t *d;
	int i=0;
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask;

	struct bpf_program fcode;
	CString strMsg;

	// 获取网络设备列表
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
	{
		return 0;
	}

	// 跳至选择的网络设备
	long nNetCardIndex = pThis->GetNetCardIndex();

	for(d=alldevs, i=0; i < nNetCardIndex-1 ;d=d->next, i++);
	
// 	// 打开网络设备
// 	if ( (adhandle= pcap_open(d->name,	// name of the device
// 							 65536,		// portion of the packet to capture. 
// 										// 65536 grants that the whole packet will be captured on all the MACs.
// 							 PCAP_OPENFLAG_PROMISCUOUS,			// promiscuous mode
// 							 1000,		// read timeout
// 							 NULL,		// remote authentication
// 							 errbuf		// error buffer
// 							 ) ) == NULL)
// 	{
// 		CString strError(errbuf);
// 		CLogPrint::LogString(LOGLEVEL_ERROR, strError);
// 		pcap_freealldevs(alldevs);
// 		return S_FALSE;
// 	}
	if((adhandle= pcap_open_live(d->name, 65536, 1 , 10, errbuf)) == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("不能打开网络适配器,请在网卡设置中经行设置"));
		return 0;  
	}

	// 检查链路层
	if(pcap_datalink(adhandle) != DLT_EN10MB)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR,  _T("该程序仅支持以太网设备"));
		pcap_freealldevs(alldevs);
		return S_FALSE;
	}

	// 设置掩码
	netmask=0xffffff; 

	CString strFilter;
	pThis->GetFilterString(strFilter);
	char *packet_filter = NULL;
	CString_to_char(strFilter, &packet_filter);

	// 编译搜索过滤字符串
	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) <0 )
	{
		CLogPrint::LogString(LOGLEVEL_ERROR,  _T("编译过滤字符串失败"));
		pcap_freealldevs(alldevs);
		delete packet_filter;
		return S_FALSE;
	}
	
	// 设置过滤器
	if (pcap_setfilter(adhandle, &fcode)<0)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, _T("设置过滤器失败") );
		pcap_freealldevs(alldevs);
		delete packet_filter;
		return S_FALSE;
	}
	
	CString strText;
	strText.Format(_T("------开始监听设备 { %s }------"), CString(d->description));
	CLogPrint::LogString(LOGLEVEL_TRACE, strText);
	
	// 释放设备列表
	pcap_freealldevs(alldevs);
	
	// 开始监视
	pThis->m_adhandle = adhandle;
	
	if (pThis->m_bLoopMode)
	{
		pcap_loop(adhandle, 0, packet_handler, (u_char*)pThis);	
	}
	else
	{
		struct pcap_pkthdr *header;
		const u_char *data;

		//adhandle后不调用pcap_loop，而用下面的方法：
	 	while(TRUE)
	 	{
	 		if (pThis->m_bExitCapture)
	 		{
	 			break;
	 		}
	 
			//释放缓冲区
			pThis->FreeAllParsedBuffer();

	 		long res = pcap_next_ex(adhandle,&header,&data);
	 	
	 		if(res==0)
	 		{
	 			Sleep(10);
	 			continue;
	 		}
	 		else
	 		{
	 			if (!pThis->IsCaptureStop())
	 			{//记录缓冲区数据
					pThis->packet_handler(header, data);
	 			}
	 		}
	 	}
	}

	pcap_close(adhandle);
	delete packet_filter;
	pThis->m_adhandle  = NULL;
	pThis->m_pCaptureThread = NULL;

	return 0;
}


UINT CEpNetCapThread::ParseThread(LPVOID pParam)
{
	CEpNetCapThread *pThis = (CEpNetCapThread*)pParam;
	CProtocolBase *pProtocol = pThis->m_pProtocol;

	while (TRUE)
	{
		if (pThis->m_bExitCapture)
		{
			pThis->m_pProtocol->OnExit();
			break;
		}

		//是否有可以待解析处理的缓冲区对象
		if (pThis->m_oCapCycleBufferMngr.HasBufferNeedParse())
		{
			CEpCycleMemBuffer *pBuffer = pThis->m_oCapCycleBufferMngr.GetBufferNeedParse();

			if (pBuffer != NULL)
			{
				pThis->m_pProtocol->Parse(pBuffer);
			}
		}

		//处理缓冲区
		//如果缓冲区部分被处理，则需要合并缓冲区
		
		Sleep(10);
	}

	pThis->m_pParseThread = NULL;

	return 0;
}

void CEpNetCapThread::GetFilterString(CString &strFilter)
{
	ep_GetFiltersString(m_oCapConfig.filters, strFilter);
}

void CEpNetCapThread::FreeAllParsedBuffer()
{
	if (!m_bFreeCapBuffer)
	{
		return;
	}

	m_oCapCycleBufferMngr.FreeParsedBuffer();
}

