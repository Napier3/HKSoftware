#pragma once

#define HAVE_REMOTE
#include "..\WinPcap\Include\pcap.h"
#pragma comment(lib, "wpcap.lib")

extern LONG64 g_nCaptureID;
LONG64 Ep_Cap_GenerateCaptureID();


/* Ethernet protocol ID's */    
#define ETHERTYPE_PUP           0x0200          /* Xerox PUP */
#define ETHERTYPE_IP            0x0800          /* IP */
#define ETHERTYPE_ARP           0x0806          /* Address resolution */
#define ETHERTYPE_REVARP        0x8035          /* Reverse ARP */

/* This structure defines an ethernet arp header.  */

/* ARP protocol opcodes. */
#define ARPOP_REQUEST   1               /* ARP request.  */
#define ARPOP_REPLY     2               /* ARP reply.  */
#define ARPOP_RREQUEST  3               /* RARP request.  */
#define ARPOP_RREPLY    4               /* RARP reply.  */
#define ARPOP_InREQUEST 8               /* InARP request.  */
#define ARPOP_InREPLY   9               /* InARP reply.  */
#define ARPOP_NAK       10              /* (ATM)ARP NAK.  */

/* ARP protocol HARDWARE identifiers. */
#define ARPHRD_NETROM   0               /* From KA9Q: NET/ROM pseudo. */
#define ARPHRD_ETHER    1               /* Ethernet 10/100Mbps.  */
#define ARPHRD_EETHER   2               /* Experimental Ethernet.  */
#define ARPHRD_AX25     3               /* AX.25 Level 2.  */
#define ARPHRD_PRONET   4               /* PROnet token ring.  */
#define ARPHRD_CHAOS    5               /* Chaosnet.  */
#define ARPHRD_IEEE802  6               /* IEEE 802.2 Ethernet/TR/TB.  */
#define ARPHRD_ARCNET   7               /* ARCnet.  */
#define ARPHRD_APPLETLK 8               /* APPLEtalk.  */
#define ARPHRD_DLCI     15              /* Frame Relay DLCI.  */
#define ARPHRD_ATM      19              /* ATM.  */
#define ARPHRD_METRICOM 23              /* Metricom STRIP (new IANA id).  */

/* Dummy types for non ARP hardware */
#define ARPHRD_SLIP       0x256
#define ARPHRD_CSLIP      0x257
#define ARPHRD_SLIP6      0x258
#define ARPHRD_CSLIP6     0x259
#define ARPHRD_RSRVD      0x260             /* Notional KISS type.  */
#define ARPHRD_ADAPT      0x264
#define ARPHRD_ROSE       0x270 
#define ARPHRD_X25        0x271             /* CCITT X.25.  */
#define ARPHDR_HWX25      0x272             /* Boards with X.25 in firmware.  */
#define ARPHRD_PPP        0x512
#define ARPHRD_CISCO      0x513             /* Cisco HDLC.  */
#define ARPHRD_HDLC       ARPHRD_CISCO
#define ARPHRD_LAPB       0x516             /* LAPB.  */
#define ARPHRD_DDCMP      0x517             /* Digital's DDCMP.  */
#define ARPHRD_RAWHDLC    0x518             /* Raw HDLC.  */
    
#define ARPHRD_TUNNEL     0x768             /* IPIP tunnel.  */
#define ARPHRD_TUNNEL6    0x769             /* IPIP6 tunnel.  */
#define ARPHRD_FRAD       0x770             /* Frame Relay Access Device.  */
#define ARPHRD_SKIP       0x771             /* SKIP vif.  */
#define ARPHRD_LOOPBACK   0x772             /* Loopback device.  */
#define ARPHRD_LOCALTLK   0x773             /* Localtalk device.  */
#define ARPHRD_FDDI       0x774             /* Fiber Distributed Data Interface. */
#define ARPHRD_BIF        0x775             /* AP1000 BIF.  */ 
#define ARPHRD_SIT        0x776             /* sit0 device - IPv6-in-IPv4.  */
#define ARPHRD_IPDDP      0x777             /* IP-in-DDP tunnel.  */
#define ARPHRD_IPGRE      0x778             /* GRE over IP.  */
#define ARPHRD_PIMREG     0x779             /* PIMSM register interface.  */
#define ARPHRD_HIPPI      0x780             /* High Performance Parallel I'face. */
#define ARPHRD_ASH        0x781             /* (Nexus Electronics) Ash.  */
#define ARPHRD_ECONET     0x782             /* Acorn Econet.  */
#define ARPHRD_IRDA       0x783             /* Linux-IrDA.  */
#define ARPHRD_FCPP       0x784             /* Point to point fibrechanel.  */
#define ARPHRD_FCAL       0x785             /* Fibrechanel arbitrated loop.  */
#define ARPHRD_FCPL       0x786             /* Fibrechanel public loop.  */
#define ARPHRD_FCPFABRIC  0x787             /* Fibrechanel fabric.  */
#define ARPHRD_IEEE802_TR 0x800             /* Magic type ident for TR.  */
#define ARPHRD_IEEE80211  0x801             /* IEEE 802.11.  */


/* IP version number */
#define IPVERSION       4

struct ether_header
{
	u_char  ether_dhost[6];      /* destination eth addr */
	u_char  ether_shost[6];      /* source ether addr    */
	u_short ether_type;          /* packet type ID field */
};

//////////////////////////////////////////////////////////////////////////
//ARP
struct arphead
{
	u_short arp_hardware_type;				 /* Format of hardware address.  */
	u_short arp_protocol_type;				 /* Format of protocol address.  */
	u_char arp_hardware_length;			 /* Length of hardware address.  */
	u_char arp_protocol_length;			 /* Length of protocol address.  */
	u_short arp_operation_code;			 /* ARP opcode (command).  */ //1Ϊ���� 2Ϊ�ظ�
	u_char arp_source_ethernet_address[6];		 /* Sender hardware address.  */
	u_char arp_source_ip_address[4];			 /* Sender IP address.  */
	u_char arp_destination_ethernet_address[6];   /* Target hardware address.  */
	u_char arp_destination_ip_address[4];		 /* Target IP address.  */
};

//////////////////////////////////////////////////////////////////////////
//ICMP
struct ep_icmp_header
{
	u_char icmp_type;
	u_char icmp_code;
	u_short icmp_checksum;
	u_short icmp_id;
	u_short icmp_sequence;
};
/*
icmp
����	����	����	��	ѯ	��		��
0 	0 	����Ӧ��(P i n gӦ��		
3 		Ŀ�Ĳ��ɴ					
	0 
	1
	2 	���粻�ɴ��������ɴ�Э�鲻�ɴ�				
	3 
	4 
	5 
	6 	�˿ڲ��ɴ���Ҫ���з�Ƭ�������˲���Ƭ����Դվѡ·ʧ��Ŀ�����粻��ʶ					
	7 	Ŀ����������ʶ				
	8
	9 	Դ���������루���ϲ��ã�Ŀ�����类ǿ�ƽ�ֹ				
	1 0 	Ŀ��������ǿ�ƽ�ֹ				
	11 
	12 
	13 	���ڷ�������TO S �����粻�ɴ����ڷ�������TO S ���������ɴ����ڹ��ˣ�ͨ�ű�ǿ�ƽ�ֹ				
	14 	����ԽȨ			
	15 	����Ȩ��ֹ��Ч			
4 	0 	Դ�˱��رգ����������ƣ�			
5 	0 	�ض��� �������ض���				
	1 	�������ض���				
	2 	�Է������ͺ������ض���			
	3 	�Է������ͺ������ض���		
8 	0 	������ԣ�P i n g����			
9 	0 	·����ͨ��				
1 0 	0 	·��������				
11 		��ʱ��					
	0 	�����ڼ�����ʱ��Ϊ0��Traceroute��					
	1 	�����ݱ���װ�ڼ�����ʱ��Ϊ0					
1 2 		�������⣺					
	0 	����I P�ײ����������ֲ��				
	1 	ȱ�ٱ����ѡ��				
1 3 	0 	ʱ�������		
1 4 	0 	ʱ���Ӧ��	
1 5 	0 	��Ϣ�������ϲ��ã�			
1 6 	0 	��ϢӦ�����ϲ��ã�			
1 7 	0 	��ַ��������				
1 8 	0 	��ַ����Ӧ��	
*/


typedef struct ep_ip_address : public in_addr
{
}ep_ip_address;

typedef struct ep_mac_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
	u_char byte5;
	u_char byte6;
}ep_mac_address;

typedef struct ep_cap_ip
{
	ep_ip_address ip;
	u_short port;
}EP_CAP_IP;

typedef struct ep_cap_ip_group
{
	EP_CAP_IP src;
	EP_CAP_IP dst;
}EP_CAP_IP_GROUP;


/* IPv4 header */
typedef struct ep_ip_header
{
	u_char	ver_ihl;		// Version (4 bits) + Internet header length (4 bits)
	u_char	tos;			// Type of service 
	u_short tlen;			// Total length 
	u_short identification; // Identification
	u_short flags_fo;		// Flags (3 bits) + Fragment offset (13 bits)
	u_char	ttl;			// Time to live
	u_char	protocol;			// Protocol ICMP(1) IGMP(2) TCP(6) UDP(17)
	u_short crc;			// Header ep_checksum
	ep_ip_address	saddr;		// Source address
	ep_ip_address	daddr;		// Destination address
	u_int	op_pad;			// Option + Padding
}EP_IP_HEADER;

/* UDP header*/
typedef struct ep_udp_header
{
	u_short sport;			// Source port
	u_short dport;			// Destination port
	u_short len;			// Datagram length
	u_short crc;			// Checksum
}EP_UDP_HEADER;

/* TCP header*/
typedef struct ep_tcp_header
{
	u_short sport;			// Source port
	u_short dport;			// Destination port
	u_int th_seq;			//32λ���к�
	u_int th_ack;			//32λȷ�Ϻ�
	u_char th_lenres;		//4λ�ײ�����/6λ������
	u_char th_flag;			//6λ��־λ 
#define TH_FIN        0x01
#define TH_SYN        0x02
#define TH_RST        0x04
#define TH_PUSH       0x08
#define TH_ACK        0x10
#define TH_URG        0x20
	u_short th_win;			//16λ���ڴ�С
	u_short th_sum;			//16λУ���
	u_short th_urp;			//16λ��������ƫ����
}EP_TCP_HEADER;


typedef struct  ep_psd_header
{
	ep_ip_address saddr;		//Դ��ַ
	ep_ip_address daddr;		//Ŀ�ĵ�ַ
	u_char mbz;				//�ÿ�
	u_char proto;			//Э������
	u_short tcpl;			//TCP����
}EP_PSD_HEADER;


static SHORT ep_checksum(USHORT* buffer, int size)
{
	unsigned long cksum = 0;

	while(size>1)
	{
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}

	if(size)
	{
		cksum += *(UCHAR*)buffer;
	}

	cksum = (cksum>>16) + (cksum&0xffff);  //����16bit���16bit���
	cksum += (cksum>>16);             //����λ����λ��16bit���16bit �����

	return (USHORT)(~cksum);
}

//
typedef struct timeval CAPTIMEVAL;

//////////////////////////////////////////////////////////////////////////
//fileter
typedef struct ep_cap_filter_ports
{
// 	u_char use_sport;    //�Ƿ�ʹ��sport
// 	u_char use_dport;    //�Ƿ�ʹ��sport
	u_short sport;
	u_short dport;
}ep_cap_filter_ports;

typedef struct ep_cap_filter_ips
{
// 	u_char use_sip;    //�Ƿ�ʹ��sip
// 	u_char use_dip;    //�Ƿ�ʹ��dip
	ep_ip_address sip;		//Դ��ַ
	ep_ip_address dip;		//Ŀ�ĵ�ַ
}ep_cap_filter_ips;

typedef struct ep_cap_filter
{
	u_char type;   //TCP,UDP,ICMP,ARP,......
	ep_cap_filter_ports ports;
	ep_cap_filter_ips ips;
}ep_cap_filter;

#define MAX_EP_CAP_FILTER_COUNT  250
typedef struct ep_cap_filters
{
	u_char count_filter;
	ep_cap_filter filters[MAX_EP_CAP_FILTER_COUNT];
}ep_cap_filters;

typedef struct ep_cap_config
{
	ep_cap_filters filters;   //������
	UINT nNetCardIndex;  //��������
}EP_CAP_CONFIG;

enum ep_filter_type
{
	EFT_TCP=0, EFT_UDP, EFT_ICMP, EFT_ARP
};

inline BOOL ep_IsFilterUseSIp(ep_cap_filter *pFilter)		{	return (pFilter->ips.sip.s_addr != 0);}
inline BOOL ep_IsFilterUseDIp(ep_cap_filter *pFilter)		{	return (pFilter->ips.dip.s_addr != 0);}
inline BOOL ep_IsFilterUseIp(ep_cap_filter *pFilter)		{	return (ep_IsFilterUseSIp(pFilter) || ep_IsFilterUseDIp(pFilter));}
inline BOOL ep_IsFilterUseSDIp(ep_cap_filter *pFilter)		{	return (ep_IsFilterUseSIp(pFilter) && ep_IsFilterUseDIp(pFilter));}
inline BOOL ep_IsFilterUseSIp(ep_cap_filter_ips *pIps)		{	return (pIps->sip.s_addr != 0);}
inline BOOL ep_IsFilterUseDIp(ep_cap_filter_ips *pIps)		{	return (pIps->dip.s_addr != 0);}
inline BOOL ep_IsFilterUseIp(ep_cap_filter_ips *pIps)		{	return (ep_IsFilterUseSIp(pIps) || ep_IsFilterUseDIp(pIps));}
inline BOOL ep_IsFilterUseSDIp(ep_cap_filter_ips *pIps)		{	return (ep_IsFilterUseSIp(pIps) && ep_IsFilterUseDIp(pIps));}

inline BOOL ep_IsFilterUseSPort(ep_cap_filter *pFilter)	{	return (pFilter->ports.sport != 0);}
inline BOOL ep_IsFilterUseDPort(ep_cap_filter *pFilter)	{	return (pFilter->ports.dport != 0);}
inline BOOL ep_IsFilterUsePort(ep_cap_filter *pFilter)	{	return (ep_IsFilterUseSPort(pFilter) || ep_IsFilterUseDPort(pFilter));}
inline BOOL ep_IsFilterUseSDPort(ep_cap_filter *pFilter)	{	return (ep_IsFilterUseSPort(pFilter) && ep_IsFilterUseDPort(pFilter));}
inline BOOL ep_IsFilterUseSPort(ep_cap_filter_ports *pPorts)	{	return (pPorts->sport != 0);}
inline BOOL ep_IsFilterUseDPort(ep_cap_filter_ports *pPorts)	{	return (pPorts->dport != 0);}
inline BOOL ep_IsFilterUsePort(ep_cap_filter_ports *pPorts)	{	return (ep_IsFilterUseSPort(pPorts) || ep_IsFilterUseDPort(pPorts));}
inline BOOL ep_IsFilterUseSDPort(ep_cap_filter_ports *pPorts)	{	return (ep_IsFilterUseSPort(pPorts) && ep_IsFilterUseDPort(pPorts));}

void ep_SetIP(ep_ip_address *pIP, ULONG dwIP);
inline void ep_SetIP(ep_ip_address &ip, ULONG dwIP)		{		ep_SetIP(&ip, dwIP);	}
void ep_SetIpV4(ep_ip_address *ip, const CString &strIP);
inline void ep_SetIpV4(ep_ip_address &ip, const CString &strIP)		{	ep_SetIpV4(&ip, strIP);	}

void ep_GetIpV4(ep_ip_address *ip, CString &strIP);
inline void ep_GetIpV4(ep_ip_address &ip, CString &strIP)	{		ep_GetIpV4(&ip, strIP);	}

void ep_FreeFilters(ep_cap_filters *pFilters);
inline void ep_FreeFilters(ep_cap_filters &filters)	{	ep_FreeFilters(&filters);	}

BOOL ep_SetFilterCount(ep_cap_filters *pFilters, u_char count);
inline BOOL ep_SetFilterCount(ep_cap_filters &filters, u_char count)	{	return ep_SetFilterCount(&filters, count);	}

void ep_SetTcpFilter(ep_cap_filters *pFilters, u_char index, DWORD sip, DWORD dip, SHORT sport, SHORT dport);
inline void ep_SetTcpFilter(ep_cap_filters &filters, u_char index, DWORD sip, DWORD dip, SHORT sport, SHORT dport)	{	ep_SetTcpFilter(&filters, index, sip, dip, sport, dport);	}
void ep_SetUdpFilter(ep_cap_filters *pFilters, u_char index, DWORD sip, DWORD dip, SHORT sport, SHORT dport);
inline void ep_SetUdpFilter(ep_cap_filters &filters, u_char index, DWORD sip, DWORD dip, SHORT sport, SHORT dport)	{	ep_SetUdpFilter(&filters, index, sip, dip, sport, dport);	}

ep_cap_filter* ep_AddTcpFilter(ep_cap_filters *pFilters, DWORD sip, DWORD dip, SHORT sport, SHORT dport);
inline ep_cap_filter* ep_AddTcpFilter(ep_cap_filters &filters, DWORD sip, DWORD dip, SHORT sport, SHORT dport)	{	return ep_AddTcpFilter(&filters, sip, dip, sport, dport);	}
ep_cap_filter* ep_AddUdpFilter(ep_cap_filters *pFilters, DWORD sip, DWORD dip, SHORT sport, SHORT dport);
inline ep_cap_filter* ep_AddUdpFilter(ep_cap_filters &filters, DWORD sip, DWORD dip, SHORT sport, SHORT dport)	{	return ep_AddUdpFilter(&filters, sip, dip, sport, dport);	}

ep_cap_filter* ep_FindFilter(ep_cap_filters *pFilters, u_char type, DWORD sip, DWORD dip, SHORT sport, SHORT dport);

ep_cap_filter* ep_AddFilter(ep_cap_filters *pFilters, u_char type, DWORD sip, DWORD dip, SHORT sport, SHORT dport);
inline ep_cap_filter* ep_AddFilter(ep_cap_filters &filters, u_char type, DWORD sip, DWORD dip, SHORT sport, SHORT dport)	{	return ep_AddFilter(&filters, type, sip, dip, sport, dport);	}

void ep_DeleteFilter(ep_cap_filters *pFilters, ep_cap_filter *pFilter);
void ep_DeleteFilter(ep_cap_filters *pFilters, u_char index);

void ep_GetFilterString(ep_cap_filter *pFilter, CString &strFilter);
inline void ep_GetFilterString(ep_cap_filter &filter, CString &strFilter)		{	ep_GetFilterString(&filter, strFilter);	}

void ep_GetFiltersString(ep_cap_filters *pFilters, CString &strFilter);
inline void ep_GetFiltersString(ep_cap_filters &filters, CString &strFilter)		{	ep_GetFiltersString(&filters, strFilter);	}

void ep_GetFilterType(UINT nType, CString &strType);
void ep_GetIpProtocol(UINT nProtocol, CString &strProtocol);
