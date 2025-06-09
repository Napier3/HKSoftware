#include "StdAfx.h"
#include "EpEthernetCapThread.h"

#include "Config\MonitorCapConfig.h"
#include "..\MemBuffer\BinaryTextConvert.h"
// long g_nEpEthernetCapError = 0;

//void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

//#define _debug_vlan_

#ifdef _debug_vlan_
BYTE g_pCapConstFrameBuffer[MAX_PATH];
long g_nCapConstFrameBuffer;
long g_nCapConstFrameBufferIndex = 0;

void st_ConvertFrameTextToBinary(const CString &strText, BYTE *pBuffer, long &nLen)
{
	CBinaryTextConvert oConvert;
	oConvert.SetText(strText);
	oConvert.ConvertTextToBinary(FALSE);
	BYTE *pHex = NULL;
	oConvert.GetBinaryRef(&pHex, nLen);

	memcpy(pBuffer, pHex, nLen);
}
//	
#endif

CEpEthernetCapThread::CEpEthernetCapThread(void)
{
	m_adhandle = NULL;
	long nLen = sizeof(EP_ETHER_CAP_CONFIG);
	//memset(&m_oCapConfig, 0, nLen);
//	m_oCapConfig.nNetCardIndex = -1;
//	m_oCapConfig.filters.count_filter = 0;
	SetCaptureNextMode();
//	SetCaptureLoopMode();
	//m_packet_filter = NULL;
	m_bRestartWinCap = FALSE;
	m_nEpEthernetCapError = 0;

	m_bCapTcp = TRUE;
	m_bCapUdp = TRUE;;
	m_bCapAllIP = TRUE;
	m_bCapOther = FALSE;

#ifdef _debug_vlan_
	CString strText;
	strText = _T("00e0a801333f000fe2227d098100000108004500002834e940003b06189e0a2105060a21d901d4cd096407ae1a8f6dcdb9ef501036705eef0000000000000000");
	strText = _T("");
	st_ConvertFrameTextToBinary(strText, g_pCapConstFrameBuffer, g_nCapConstFrameBuffer);
#endif
}

CEpEthernetCapThread::~CEpEthernetCapThread(void)
{
	
}

void CEpEthernetCapThread::SetCapConfig(CEmcNetDevice *pCapConfig)	
{	
	m_pCapConfig = pCapConfig;
	SetCap(pCapConfig->m_nUDP, pCapConfig->m_nTCP, pCapConfig->m_nOther);


	//2012-10-16 17:13
	pcap_if_t* alldevs = NULL;
	char errbuf[PCAP_ERRBUF_SIZE];

	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		TRACE("Error in pcap_findalldevs: %s\n", errbuf);
		return ;
	}

	long nNetCardIndex = 0;
	long nNetCardIndexFind = GetNetCardIndex() - 1;
	ASSERT (nNetCardIndexFind >= 0);
	CStringA strIP;

	for(pcap_if_t* d=alldevs; d;  d=d->next)
	{
		if (d->description && (nNetCardIndexFind == nNetCardIndex))
		{
			TRACE(" %s : (%s)\n", d->name, d->description);
			CLogPrint::LogFormatString(LOGLEVEL_TRACE,_T("网卡【%s】"), CString(d->name));
			CLogPrint::LogFormatString(LOGLEVEL_TRACE,_T("网卡【%s】"), CString(d->description));
			m_strNetCardID = d->name;
			break;
		}
		else if (nNetCardIndexFind == nNetCardIndex)
		{
			m_strNetCardID = d->name;
			TRACE(" %s : (no info.)\n", d->name);
			CLogPrint::LogFormatString(LOGLEVEL_TRACE,_T("网卡【%s】"), CString(d->name));
			break;
		}

		nNetCardIndex++;
	}	

	if (m_strNetCardID.GetLength() == 0)
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE,_T("网卡配置错误【%d】"), nNetCardIndexFind+1);
	}

	InitFilters();
}

void CEpEthernetCapThread::SetCaptureLoopMode()
{
	ASSERT (m_pCaptureThread == NULL && m_adhandle == NULL);
	
	m_bLoopMode = TRUE;
}

void CEpEthernetCapThread::SetCaptureNextMode()
{
	ASSERT (m_pCaptureThread == NULL && m_adhandle == NULL);
	
	m_bLoopMode = FALSE;
}

BOOL CEpEthernetCapThread::CanRestartNetCap(BOOL bReset)
{
	if (bReset)
	{
		m_nEpEthernetCapError = 0;
		return FALSE;
	}
	else
	{
		m_nEpEthernetCapError++;

		if (m_nEpEthernetCapError > 10)
		{
			m_nEpEthernetCapError = 0;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
// 	if (m_bLoopMode)
// 	{
// 		m_nEpEthernetCapError++;
// 
// 		if (m_nEpEthernetCapError > 20)
// 		{
// 			m_nEpEthernetCapError = 0;
// 			return TRUE;
// 		}
// 		else
// 		{
// 			return FALSE;
// 		}
// 	}
// 	else
// 	{
// 		return (m_nEpEthernetCapError > 2000);
// 	}
}

DWORD CEpEthernetCapThread::CreateCaptureThread()
{
	m_pCaptureThread = AfxBeginThread(CaptureThread,this);
	m_pCaptureThread->m_bAutoDelete = TRUE;

	if (m_bUseParseThread)
	{
		m_pParseThread = AfxBeginThread(ParseThread,this);
		m_pParseThread->m_bAutoDelete = TRUE;
	}

	return 0;
}

void CEpEthernetCapThread::ExitCapture()
{
	if (m_bLoopMode)
	{
		if (m_adhandle != NULL)
		{
			pcap_breakloop(m_adhandle);
			m_adhandle = NULL;
		}
	}
}

void CEpEthernetCapThread::packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	CEpEthernetCapThread *pCapNetThread = (CEpEthernetCapThread*)param;

	if (pCapNetThread->IsCaptureStop())
	{
		return;
	}

	pCapNetThread->packet_handler_r(header, pkt_data);
}

void CEpEthernetCapThread::packet_handler_r(const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	if (IsCaptureStop())
	{
		return;
	}

	//报文类型	//规约类型
	Ep_SetProtocol_FrameType(m_pProtocol->m_bufPos.nProtocol, 0);
	Ep_SetProtocol_ProtoType(m_pProtocol->m_bufPos.nProtocol, EPPROTOCOL_NONE);

	CCapCycleMemBuffer *pCapBuffer = NULL;

	// 通知APP有数据接收到
//	theApp.m_bOnConnect = TRUE;
	struct ether_header *eth = (ether_header *)pkt_data;

	switch(ntohs(eth->ether_type))
	{
		case ETHERTYPE_IP:
			{
				//length of ethernet header				// 获取IP报文头
				pCapBuffer = m_oCapCycleBufferMngr.AddCapBuffer(header, pkt_data);
				ep_ip_header *IPHead=(ep_ip_header *)(pkt_data+14);//14=sizeof(ether_header)
				packet_handler_ip(pCapBuffer, header, IPHead);
			}
			break;

		case ETHERTYPE_VLAN :
			{
				//if (m_bCapOther)
				{
					pCapBuffer = m_oCapCycleBufferMngr.AddCapBuffer(header, pkt_data);
					EP_VLAN_HEADER *vlanHead = (EP_VLAN_HEADER*)(pkt_data+14);
					packet_handler_vlan(pCapBuffer,header, vlanHead);
				}
				//CLogPrint::LogString(LOGLEVEL_TRACE, _T("...."));
			}
			break;

		case ETHERTYPE_ARP:
			{
				if (m_bCapOther)
				{
					pCapBuffer = m_oCapCycleBufferMngr.AddCapBuffer(header, pkt_data);
					pCapBuffer->Set_RECORD_NEEDRECORD();
					arphead *arp = (arphead*)(pkt_data+14);
					packet_handler_arp(pCapBuffer,header, arp);
				}
			}
			break;
		default:
			{
				if (m_bCapOther)
				{
					pCapBuffer = m_oCapCycleBufferMngr.AddCapBuffer(header, pkt_data);
					pCapBuffer->Set_RECORD_NEEDRECORD();
					EP_ETHER_CAP_IP_GROUP ipGroup;
					ZeroMemory(&ipGroup, sizeof(ipGroup));
					ipGroup.dst.port = 60000;
					ipGroup.src.port = 60000;
					pCapBuffer->OffsetCurrPos(-1);
					pCapBuffer->SetState(EBS_BEPARSED);
					pCapBuffer->InitParsePos(pkt_data, 0, ipGroup, EP_CAP_CHTYPE_NET);
				}
			}

			break;
	}

	if (pCapBuffer != NULL)
	{
		ep_cap_timeval_to_64time(header->ts, pCapBuffer->m_ts); 
		if (pCapBuffer->Is_RECORD_NEEDRECORD())
		{
			pCapBuffer->OffsetCurrPos(-1);
			RecordFrame(/*NULL, */pCapBuffer, &m_pProtocol->m_bufPos);
		}
		else
		{
		}

		pCapBuffer->SetState(EBS_BEPARSED);
	}

	//释放
	//FreeAllParsedBuffer();
}

void CEpEthernetCapThread::packet_handler_ip_ex(CCapCycleMemBuffer *pCapBuffer, const struct pcap_pkthdr *header, const ep_ip_header *iph)
{
	EP_ETHER_CAP_IP_GROUP ipGroup;

	ipGroup.src.ip = iph->saddr;
	ipGroup.src.port = 60000;
	ipGroup.dst.ip = iph->daddr;
	ipGroup.dst.port = 60000;
	pCapBuffer->InitParsePos((const u_char*)iph, 0, ipGroup, EP_CAP_CHTYPE_TCP);
}

void CEpEthernetCapThread::packet_handler_ip(CCapCycleMemBuffer *pCapBuffer, const struct pcap_pkthdr *header, const ep_ip_header *iph)
{
	CCapCycleMemBuffer *pRet = NULL;

	switch(iph->protocol)
	{
	case 1:
		pRet = NULL;

		if (m_bCapOther)
		{
			packet_handler_ip_ex(pCapBuffer, header, iph);
			pCapBuffer->Set_RECORD_NEEDRECORD();
		}
// 		ZeroMemory(&pCapBuffer->m_ipGroup, sizeof(EP_ETHER_CAP_IP_GROUP));
// 		pCapBuffer->m_ipGroup.dst.port = 60000;
// 		pCapBuffer->m_ipGroup.src.port = 60000;
		break;
	case 6:
		pRet = packet_handler_ip_tcp(pCapBuffer, header, iph);
		break;
	case 17:
		pRet = packet_handler_ip_udp(pCapBuffer, header, iph);
		break;
	default:
// 		ZeroMemory(&pCapBuffer->m_ipGroup, sizeof(EP_ETHER_CAP_IP_GROUP));
// 		pCapBuffer->m_ipGroup.dst.port = 60000;
// 		pCapBuffer->m_ipGroup.src.port = 60000;
		if (m_bCapOther)
		{
			pCapBuffer->Set_RECORD_NEEDRECORD();
			packet_handler_ip_ex(pCapBuffer, header, iph);
		}

		pRet = NULL;
		break;
	}

	if (pRet != NULL)
	{
		//pCapBuffer->Set_RECORD_NEEDRECORD();
		ParseEx(pCapBuffer);
	}
	else
	{
// 		if (m_bCapOther)
// 		{
// 			EP_ETHER_CAP_IP_GROUP ipGroup;
// 			ZeroMemory(&ipGroup, sizeof(ipGroup));
// 			long iph_len = (iph->ver_ihl & 0x0f) * 4;
// 			pCapBuffer = m_oCapCycleBufferMngr.AddCapBuffer(header->ts, ipGroup, (u_char*)iph, iph_len, EP_CAP_CHTYPE_IP);
// 			pCapBuffer->SetState(EBS_BEPARSED);
// 		}
	}

	//释放
	WriteCap();
	FreeAllParsedBuffer();
}

void CEpEthernetCapThread::packet_handler_vlan(CCapCycleMemBuffer *pCapBuffer, const struct pcap_pkthdr *header, const ep_vlan_header *vlanph)
{
	EP_ETHER_CAP_IP_GROUP ipGroup;
	ZeroMemory(&ipGroup, sizeof(ipGroup));

	switch(ntohs(vlanph->ether_type))
	{
	case ETHERTYPE_IP:
		{
			ep_ip_header *IPHead=(ep_ip_header *)(((u_char*)vlanph)+4);//14=sizeof(ether_header)
			packet_handler_ip(pCapBuffer, header, IPHead);
		}
		break;
	default:

// 		if (m_bCapOther)
// 		{
// 			pCapBuffer = m_oCapCycleBufferMngr.AddCapBuffer(header->ts, ipGroup, (u_char*)vlanph, header->caplen, EP_CAP_CHTYPE_NET);
// 			pCapBuffer->SetState(EBS_BEPARSED);
// 		}

		break;
	}

// 	if (pCapBuffer != NULL)
// 	{
// 		ParseEx(pCapBuffer);
// 	}
// 
// 	//释放
// 	WriteCap();
// 	FreeAllParsedBuffer();
}


void CEpEthernetCapThread::packet_handler_arp(CCapCycleMemBuffer *pCapBuffer, const struct pcap_pkthdr *header, const arphead *arph)
{
	EP_ETHER_CAP_IP_GROUP ipGroup;
	ZeroMemory(&ipGroup, sizeof(ipGroup));

	ep_ip_address	addr;
	memcpy(&addr, arph->arp_source_ip_address, sizeof(ep_ip_address));
	ipGroup.src.ip = addr;
	ipGroup.src.port = 60000;
	memcpy(&addr, arph->arp_destination_ip_address, sizeof(ep_ip_address));
	ipGroup.dst.ip = addr;
	ipGroup.dst.port = 60000;
	pCapBuffer->InitParsePos((const u_char *)arph, 0, ipGroup, EP_CAP_CHTYPE_TCP);
}


CCapCycleMemBuffer* CEpEthernetCapThread::packet_handler_ip_tcp(CCapCycleMemBuffer *pCapBuffer, const struct pcap_pkthdr *header, const ep_ip_header *iph)
{
	if (!m_bCapTcp)
	{
		return NULL;
	}

	m_nEpEthernetCapError = 0;

	ep_tcp_header *tcph;
// 	u_int ip_len;
// 	u_int tcph_len;
// 
// 	// 获取IP报文长度
// 	ip_len = (iph->ver_ihl & 0x0f) * 4;
// 	u_char *pkt_data = (u_char*)iph;
// 
// 	// 获取TCP报文头
// 	tcph = (ep_tcp_header *) (pkt_data + ip_len);
// 
// 	tcph_len = ((tcph->th_lenres & 0xf0) >> 4) * 4;
// 	long nDataLen = header->caplen - tcph_len - ip_len - 14/*ether_header*/;
// 	pkt_data = (u_char*)tcph + tcph_len;
// 
// 	int iPSH = pkt_data[14+ip_len+13] & 0x08;


	u_int iph_len;
	u_int tcph_len;

	// 获取IP报文长度
	iph_len = (iph->ver_ihl & 0x0f) * 4;
	u_char *pkt_data = (u_char*)iph;
	u_char *pkt_data_iph = NULL;

	// 获取TCP报文头
	tcph = (ep_tcp_header *) (pkt_data + iph_len);
	EP_ETHER_CAP_IP_GROUP ipGroup;
	ZeroMemory(&ipGroup, sizeof(ipGroup));

	if ((ntohs( tcph->dport ) != 2404) && (ntohs( tcph->sport ) != 2404))
	{
		pkt_data_iph = (u_char*)iph;
	}

	tcph_len = ((tcph->th_lenres & 0xf0) >> 4) * 4;
	long nDataLen = ntohs(iph->tlen) - tcph_len - iph_len;// - 14/*ether_header*/;

	pkt_data = (u_char*)tcph;
	pkt_data = pkt_data + tcph_len;

	int iPSH = tcph->th_flag & 0x08;
	if (iPSH != 0)
	{//data process

	}

	if (nDataLen < 0)
	{
		pkt_data_iph = (u_char*)iph;
	}

	m_nEpEthernetCapError = 0;

// 	if (IsIpIn(iph->saddr.S_un.S_addr) || IsIpIn(iph->daddr.S_un.S_addr))
// 	{
// 	}
// 	else
// 	{
// 		return NULL;
// 	}

	ipGroup.src.ip = iph->saddr;
	ipGroup.src.port = ntohs( tcph->sport );
	ipGroup.dst.ip = iph->daddr;
	ipGroup.dst.port = ntohs( tcph->dport );
	pCapBuffer->InitParsePos(pkt_data, nDataLen, ipGroup, EP_CAP_CHTYPE_TCP);

	//if (iPSH != 0)
	if (pkt_data_iph == NULL)
	{
		//pCapBuffer = m_oCapCycleBufferMngr.AddCapBuffer(header->ts, ipGroup, pkt_data, nDataLen, EP_CAP_CHTYPE_TCP);
		return pCapBuffer;
	}
	else
	{
// 		if (m_bCapOther)
// 		{
// 			pCapBuffer = m_oCapCycleBufferMngr.AddCapBuffer(header->ts, ipGroup, pkt_data_iph, iph_len, EP_CAP_CHTYPE_TCP);
// 			pCapBuffer->SetState(EBS_BEPARSED);
// 		}

		return NULL;
	}
}

CCapCycleMemBuffer* CEpEthernetCapThread::packet_handler_ip_udp(CCapCycleMemBuffer *pCapBuffer, const struct pcap_pkthdr *header, const ep_ip_header *iph)
{
	if (!m_bCapUdp)
	{
		return NULL;
	}

	ep_udp_header *udph;
	u_int ip_len;
	u_int udph_len;
	u_int u_offset;

	// 获取IP报文长度
	ip_len = (iph->ver_ihl & 0xf) * 4;
	u_char *pkt_data = (u_char*)iph;

	// 获取TCP报文头
	udph = (ep_udp_header *) (pkt_data + ip_len);


	udph_len = 8;//udph->len * 4;
	u_offset = ip_len + udph_len;
	pkt_data = (u_char*)udph;
	long nlen = ((udph->len >> 8) & 0xFF) + ((udph->len & 0xFF) << 8);
	long nDataLen = nlen - 8;
	pkt_data += 8;

	EP_ETHER_CAP_IP_GROUP ipGroup;
	ipGroup.src.ip = iph->saddr;
	ipGroup.src.port = ntohs( udph->sport );
	ipGroup.dst.ip = iph->daddr;
	ipGroup.dst.port = ntohs( udph->dport );
	pCapBuffer->InitParsePos(pkt_data, nDataLen, ipGroup, EP_CAP_CHTYPE_UDP);
	
	if (nDataLen < 0)
	{
		return NULL;
	}

	m_nEpEthernetCapError = 0;
// 	if (IsIpIn(iph->saddr.S_un.S_addr) || IsIpIn(iph->daddr.S_un.S_addr))
// 	{
// 	}
// 	else
// 	{
// 		return NULL;
// 	}


	if ((ntohs( udph->dport ) == 2404) || (ntohs( udph->sport ) == 2404))
	{
	}
	else
	{
		return NULL;
	}

	//CCapCycleMemBuffer* pBuffer = m_oCapCycleBufferMngr.AddCapBuffer(header->ts, ipGroup, pkt_data, nDataLen, EP_CAP_CHTYPE_TCP);

	return pCapBuffer;
}

void CEpEthernetCapThread::packet_handler_ip_icmp(const struct pcap_pkthdr *header, const ep_ip_header *iph)
{

}

void CEpEthernetCapThread::packet_handler_ip_igmp(const struct pcap_pkthdr *header, const ep_ip_header *iph)
{

}

void CEpEthernetCapThread::CloseWinCap()
{
	if (m_adhandle != NULL)
	{
		pcap_close(m_adhandle);
		//delete m_packet_filter;
		m_adhandle  = NULL;
	}

}


long CEpEthernetCapThread::StartWinPcap()
{
// 	if (m_adhandle != NULL)
// 	{
// 		pcap_close(m_adhandle);
// 		delete m_packet_filter;
// 		m_adhandle  = NULL;
// 	}
// 
// 	pcap_if_t *alldevs;
// 	pcap_if_t *d;
// 	int i=0;
// 	pcap_t *adhandle;
// 	char errbuf[PCAP_ERRBUF_SIZE];
// 	u_int netmask;
// 
// 	struct bpf_program fcode;
// 	CString strMsg;
// 
// 	// 获取网络设备列表
// 	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
// 	{
// 		m_pCaptureThread = NULL;
// 		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("（%s）获取网络设备列表"), m_strName);
// 		return 0;
// 	}
// 
// 	// 跳至选择的网络设备
// 	long nNetCardIndex = GetNetCardIndex();
// 
// 	for(d=alldevs, i=0; i < nNetCardIndex-1 ;d=d->next, i++);
// 
// 	// 	// 打开网络设备
// 	// 	if ( (adhandle= pcap_open(d->name,	// name of the device
// 	// 							 65536,		// portion of the packet to capture. 
// 	// 										// 65536 grants that the whole packet will be captured on all the MACs.
// 	// 							 PCAP_OPENFLAG_PROMISCUOUS,			// promiscuous mode
// 	// 							 1000,		// read timeout
// 	// 							 NULL,		// remote authentication
// 	// 							 errbuf		// error buffer
// 	// 							 ) ) == NULL)
// 	// 	{
// 	// 		CString strError(errbuf);
// 	// 		CLogPrint::LogString(LOGLEVEL_ERROR, strError);
// 	// 		pcap_freealldevs(alldevs);
// 	// 		return S_FALSE;
// 	// 	}
// 
// 	if (d == NULL)
// 	{
// 		m_pCaptureThread = NULL;
// 		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("（%s）不能打开网络适配器,请在网卡设置中经行设置"), m_strName);
// 		return 0;
// 	}
// 
// 	if((adhandle= pcap_open_live(d->name, 65536, 1 , 10, errbuf)) == NULL)
// 	{
// 		CLogPrint::LogString(LOGLEVEL_TRACE, _T("不能打开网络适配器,请在网卡设置中经行设置"));
// 		return 0;  
// 	}
// 
// 	// 检查链路层
// 	if(pcap_datalink(adhandle) != DLT_EN10MB)
// 	{
// 		CLogPrint::LogString(LOGLEVEL_ERROR,  _T("该程序仅支持以太网设备"));
// 		pcap_freealldevs(alldevs);
// 		return S_FALSE;
// 	}
// 
// 	// 设置掩码
// 	netmask=0xffffff; 
// 
// 	CString strFilter;
// 	GetFilterString(strFilter);
// 	CString_to_char(strFilter, &m_packet_filter);
// 
// 	// 编译搜索过滤字符串
// 	if (pcap_compile(adhandle, &fcode, m_packet_filter, 1, netmask) <0 )
// 	{
// 		CLogPrint::LogString(LOGLEVEL_ERROR,  _T("编译过滤字符串失败"));
// 		pcap_freealldevs(alldevs);
// 		delete m_packet_filter;
// 		m_packet_filter = NULL;
// 		return S_FALSE;
// 	}
// 
// 	// 设置过滤器
// 	if (pcap_setfilter(adhandle, &fcode)<0)
// 	{
// 		CLogPrint::LogString(LOGLEVEL_ERROR, _T("设置过滤器失败") );
// 		pcap_freealldevs(alldevs);
// 		delete m_packet_filter;
// 		m_packet_filter = NULL;
// 		return S_FALSE;
// 	}
// 
// 	CString strText;
// 	strText.Format(_T("------开始监听设备 { %s }------"), CString(d->description));
// 	CLogPrint::LogString(LOGLEVEL_TRACE, strText);
// 
// 	// 释放设备列表
// 	pcap_freealldevs(alldevs);
// 	m_adhandle = adhandle;

	int i=0;
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask;

	struct bpf_program fcode;
	CString strMsg;

	// 跳至选择的网络设备
	long nNetCardIndex = GetNetCardIndex();

	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("启动网卡%d监视......"), nNetCardIndex);

	m_strID = m_strNetCardID;

	adhandle = pcap_open(m_strNetCardID,					//设备名
						 65536,							//要捕捉的数据包的部分 
						 PCAP_OPENFLAG_PROMISCUOUS,		//混杂模式
						 10,								//读取超时时间(ms)
						 NULL,							//远程机器验证
						 errbuf);	

	//if((adhandle= pcap_open_live(d->name, 65536, 1 , 10, errbuf)) == NULL)
	if (adhandle == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("不能打开网络适配器【%s】,请在网卡设置中进行设置"), m_strNetCardID);
		return 0;  
	}

	// 检查链路层
	if(pcap_datalink(adhandle) != DLT_EN10MB)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR,  _T("该程序仅支持以太网设备"));
		return 0;
	}

	// 设置掩码
	netmask=0xffffff; 

	CString strFilter;
	GetFilterString(strFilter);
	CString_to_char(strFilter, m_packet_filter);

	// 编译搜索过滤字符串
	if (pcap_compile(adhandle, &fcode, m_packet_filter, 0, netmask) <0 )
	{
		CLogPrint::LogString(LOGLEVEL_ERROR,  _T("编译过滤字符串失败"));
		return 0;
	}

	// 设置过滤器
	if (pcap_setfilter(adhandle, &fcode)<0)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, _T("设置过滤器失败") );
		return 0;
	}

	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("------开始监听设备【%s】------"), m_strNetCardID);

	// 释放设备列表
	m_adhandle = adhandle;

	return 1;
}


UINT CEpEthernetCapThread::CaptureThread(LPVOID pParam)
{
	CEpEthernetCapThread* pThis = (CEpEthernetCapThread*)pParam;

	if (g_DEBUG_MONITOR_STATE == 1)
	{
		pThis->CapGenDataThread(EP_CAP_CHTYPE_UDP);
	}
	else
	{
/*
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
			pThis->m_pCaptureThread = NULL;
			CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("（%s）获取网络设备列表"), pThis->m_strName);
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

		if (d == NULL)
		{
			pThis->m_pCaptureThread = NULL;
			CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("（%s）不能打开网络适配器,请在网卡设置中经行设置"), pThis->m_strName);
			return 0;
		}

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
	*/	
		if (!pThis->StartWinPcap())
		{
			pThis->m_pCaptureThread = NULL;
			return 0;
		}

		if (pThis->m_bLoopMode)
		{
			pcap_loop(pThis->m_adhandle, 0, packet_handler, (u_char*)pThis);	
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

				if (pThis->m_bViewThreadRunInfor)
				{
					CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("%s running......"), pThis->m_strName);
					pThis->m_bViewThreadRunInfor = FALSE;
				}

				if (!pThis->m_bCapData)
				{
					pcap_next_ex(pThis->m_adhandle,&header,&data);
					pThis->m_nEpEthernetCapError = 0;
					Sleep(300);
					continue;
				}

				if (pThis->m_oCapCycleBufferMngr.GetCount() > 100000)
				{
					pThis->m_bCapData = FALSE;
					CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("%s 线程监视出现错误"), pThis->m_strName);
				}

				if (pThis->m_bRestartWinCap)
				{
					pThis->CloseWinCap();
					Sleep(3000);
					pThis->m_nEpEthernetCapError = 0;
					pThis->m_bRestartWinCap = FALSE;
					pThis->StartWinPcap();

					while (pThis->m_adhandle == NULL)
					{
						pThis->CloseWinCap();
						Sleep(3000);
						pThis->StartWinPcap();
					}
				}

#ifdef _debug_vlan_
				long res = g_nCapConstFrameBuffer;
				struct pcap_pkthdr oTestHeader;
				oTestHeader.caplen = g_nCapConstFrameBuffer;
				oTestHeader.len = g_nCapConstFrameBuffer;
				oTestHeader.ts.tv_sec = 42*365*24*60*60;//2012年
				oTestHeader.ts.tv_usec = 0;
				struct pcap_pkthdr *header = &oTestHeader;
				const u_char *data = g_pCapConstFrameBuffer;
#else
	 			long res = pcap_next_ex(pThis->m_adhandle,&header,&data);
#endif
		 	
	 			if(res <= 0)
	 			{
				//	pThis->m_nEpEthernetCapError += 5;
	 				Sleep(1);
	 				continue;
	 			}
	 			else
	 			{
	 				if (!pThis->IsCaptureStop())
	 				{//记录缓冲区数据
						pThis->packet_handler_r(header, data);
	 				}
	 			}
	 		}
		}

		pcap_close(pThis->m_adhandle);
		//delete pThis->m_packet_filter;
		//pThis->m_packet_filter = NULL;
		pThis->m_adhandle  = NULL;

	}

	pThis->FreeAllCapDatas();
	pThis->m_pCaptureThread = NULL;
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("监视线程（%s）结束"), pThis->m_strName);

	return 0;
}


UINT CEpEthernetCapThread::ParseThread(LPVOID pParam)
{
	CEpEthernetCapThread *pThis = (CEpEthernetCapThread*)pParam;

//	pThis->Parse();
//	pThis->m_pParseThread = NULL;

	return 0;
}

void CEpEthernetCapThread::GetFilterString(CString &strFilter)
{
// 	if (m_bCapTcp && m_bCapUdp)
// 	{
//		strFilter = _T("((tcp and ip) or (udp and ip)) and (src port 2404 or dst port 2404)");
// 	}
// 	else if (m_bCapUdp)
// 	{
// 		strFilter = _T("( (udp and ip) and (src port 2404 or dst port 2404)");
// 	}
// 	else if (m_bCapTcp)
// 	{
//		strFilter = _T("(tcp and ip) and (src port 2404 or dst port 2404)");
// 	}
// 	else
// 	{
//		strFilter = _T("( src port 2404 or dst port 2404)");
// 	}

	strFilter = _T("");
// 	CString strTcp;
// 	CString strUdp;
// 	CString strPort;
// 
// 	strPort = _T("(src port 2404 or dst port 2404)");
// 
// 	if (m_pCapConfig->m_nTCP)
// 	{
// 		strTcp = _T("(tcp and ip)");
// 	}
// 
// 	if (m_pCapConfig->m_nUDP)
// 	{
// 		strTcp = _T("(udp and ip)");
// 	}
// 	
// 	if (m_pCapConfig->m_nTCP && m_pCapConfig->m_nUDP)
// 	{
// 		strFilter.Format(_T("(%s or %s) and %s"), strTcp, strUdp, str)
// 	}
}


void CEpEthernetCapThread::InitFilters()
{
// 	CMonitorCapConfig *pCapConfig = (CMonitorCapConfig*)m_pCapConfig->GetAncestor(ECCLASSID_CMONITORCAPCONFIG);
// 	CEmcNetsConfig *pEmcNetsConfig = pCapConfig->m_pEmcNetsConfig;
// 	CEmcNetConfig *pConfig = NULL;
// 	POS pos = NULL;
// 
// 	m_nCapIpCount = 0;
// // 	m_dwCapIps[MAX_PATH];
// 	long nIndex = 0;
// 	char pszIpBuffer[MAX_PATH];
// 	pos = pEmcNetsConfig->GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pConfig =  (CEmcNetConfig*)pEmcNetsConfig->GetNext(pos);
// 		CString_to_char(pConfig->m_strID , pszIpBuffer);
// 		m_dwCapIps[nIndex] = ep_GetIpV4(pConfig->m_strID);
// 		nIndex++;
// 		m_nCapIpCount++;
// 	}
}


BOOL CEpEthernetCapThread::IsIpIn(DWORD dwIP)
{
	if (m_bCapAllIP)
	{
		return TRUE;
	}

	long nIndex = 0;
	for (nIndex=0; nIndex<m_nCapIpCount; nIndex++)
	{
		if (dwIP == m_dwCapIps[nIndex])
		{
			return TRUE;
		}
	}

	return FALSE;
}