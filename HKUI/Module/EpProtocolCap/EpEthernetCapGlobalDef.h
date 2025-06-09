﻿#pragma once

#include "EpCapGlobalDef.h"

//#pragma pack(1)

#define HAVE_REMOTE
#include "..\WinPcap\Include\pcap.h"
#pragma comment(lib, "wpcap.lib")


/* Ethernet protocol ID's */    
#define ETHERTYPE_PUP           0x0200          /* Xerox PUP */
#define ETHERTYPE_IP            0x0800          /* IP */
#define ETHERTYPE_VLAN          0x8100          /* virtual LAN */
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
	u_short arp_operation_code;			 /* ARP opcode (command).  */ //1为请求 2为回复
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
类型	代码	描述	查	询	差		错
0 	0 	回显应答(P i n g应答）		
3 		目的不可达：					
	0 
	1
	2 	网络不可达主机不可达协议不可达				
	3 
	4 
	5 
	6 	端口不可达需要进行分片但设置了不分片比特源站选路失败目的网络不认识					
	7 	目的主机不认识				
	8
	9 	源主机被隔离（作废不用）目的网络被强制禁止				
	1 0 	目的主机被强制禁止				
	11 
	12 
	13 	由于服务类型TO S ，网络不可达由于服务类型TO S ，主机不可达由于过滤，通信被强制禁止				
	14 	主机越权			
	15 	优先权中止生效			
4 	0 	源端被关闭（基本流控制）			
5 	0 	重定向： 对网络重定向				
	1 	对主机重定向				
	2 	对服务类型和网络重定向			
	3 	对服务类型和主机重定向		
8 	0 	请求回显（P i n g请求）			
9 	0 	路由器通告				
1 0 	0 	路由器请求				
11 		超时：					
	0 	传输期间生存时间为0（Traceroute）					
	1 	在数据报组装期间生存时间为0					
1 2 		参数问题：					
	0 	坏的I P首部（包括各种差错）				
	1 	缺少必需的选项				
1 3 	0 	时间戳请求		
1 4 	0 	时间戳应答	
1 5 	0 	信息请求（作废不用）			
1 6 	0 	信息应答（作废不用）			
1 7 	0 	地址掩码请求				
1 8 	0 	地址掩码应答	
*/



typedef struct ep_mac_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
	u_char byte5;
	u_char byte6;
}ep_mac_address;





/*virtua LAN*/
typedef struct ep_vlan_header
{
	u_short	ver_h;
	u_short ether_type;          /* packet type ID field */
}EP_VLAN_HEADER;


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
	u_int th_seq;			//32位序列号
	u_int th_ack;			//32位确认号
	u_char th_lenres;		//4位首部长度/6位保留字
	u_char th_flag;			//6位标志位 
#define TH_FIN        0x01
#define TH_SYN        0x02
#define TH_RST        0x04
#define TH_PUSH       0x08
#define TH_ACK        0x10
#define TH_URG        0x20
	u_short th_win;			//16位窗口大小
	u_short th_sum;			//16位校验和
	u_short th_urp;			//16位紧急数据偏移量
}EP_TCP_HEADER;


typedef struct  ep_psd_header
{
	ep_ip_address saddr;		//源地址
	ep_ip_address daddr;		//目的地址
	u_char mbz;				//置空
	u_char proto;			//协议类型
	u_short tcpl;			//TCP长度
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

	cksum = (cksum>>16) + (cksum&0xffff);  //将高16bit与低16bit相加
	cksum += (cksum>>16);             //将进位到高位的16bit与低16bit 再相加

	return (USHORT)(~cksum);
}

//
typedef struct timeval CAPTIMEVAL;

//////////////////////////////////////////////////////////////////////////
//fileter
typedef struct ep_ether_cap_filter_ports
{
// 	u_char use_sport;    //是否使用sport
// 	u_char use_dport;    //是否使用sport
	u_short sport;
	u_short dport;
}ep_ether_cap_filter_ports;

typedef struct ep_ether_cap_filter_ips
{
// 	u_char use_sip;    //是否使用sip
// 	u_char use_dip;    //是否使用dip
	ep_ip_address sip;		//源地址
	ep_ip_address dip;		//目的地址
}ep_ether_cap_filter_ips;

typedef struct ep_ether_cap_filter
{
	u_char type;   //TCP,UDP,ICMP,ARP,......
	ep_ether_cap_filter_ports ports;
	ep_ether_cap_filter_ips ips;
}ep_ether_cap_filter;

#define MAX_EP_ETHER_CAP_FILTER_COUNT  20
typedef struct ep_ether_cap_filters
{
	u_char count_filter;
	ep_ether_cap_filter filters[MAX_EP_ETHER_CAP_FILTER_COUNT];
}ep_ether_cap_filters;

typedef struct ep_ether_cap_config
{
	ep_ether_cap_filters filters;   //过滤器
	UINT nNetCardIndex;  //网卡索引
}EP_ETHER_CAP_CONFIG;

enum ep_filter_type
{
	EFT_TCP=0, EFT_UDP, EFT_ICMP, EFT_ARP
};

inline BOOL ep_IsFilterUseSIp(ep_ether_cap_filter *pFilter)		{	return (pFilter->ips.sip.s_addr != 0);}
inline BOOL ep_IsFilterUseDIp(ep_ether_cap_filter *pFilter)		{	return (pFilter->ips.dip.s_addr != 0);}
inline BOOL ep_IsFilterUseIp(ep_ether_cap_filter *pFilter)		{	return (ep_IsFilterUseSIp(pFilter) || ep_IsFilterUseDIp(pFilter));}
inline BOOL ep_IsFilterUseSDIp(ep_ether_cap_filter *pFilter)		{	return (ep_IsFilterUseSIp(pFilter) && ep_IsFilterUseDIp(pFilter));}
inline BOOL ep_IsFilterUseSIp(ep_ether_cap_filter_ips *pIps)		{	return (pIps->sip.s_addr != 0);}
inline BOOL ep_IsFilterUseDIp(ep_ether_cap_filter_ips *pIps)		{	return (pIps->dip.s_addr != 0);}
inline BOOL ep_IsFilterUseIp(ep_ether_cap_filter_ips *pIps)		{	return (ep_IsFilterUseSIp(pIps) || ep_IsFilterUseDIp(pIps));}
inline BOOL ep_IsFilterUseSDIp(ep_ether_cap_filter_ips *pIps)		{	return (ep_IsFilterUseSIp(pIps) && ep_IsFilterUseDIp(pIps));}

inline BOOL ep_IsFilterUseSPort(ep_ether_cap_filter *pFilter)	{	return (pFilter->ports.sport != 0);}
inline BOOL ep_IsFilterUseDPort(ep_ether_cap_filter *pFilter)	{	return (pFilter->ports.dport != 0);}
inline BOOL ep_IsFilterUsePort(ep_ether_cap_filter *pFilter)	{	return (ep_IsFilterUseSPort(pFilter) || ep_IsFilterUseDPort(pFilter));}
inline BOOL ep_IsFilterUseSDPort(ep_ether_cap_filter *pFilter)	{	return (ep_IsFilterUseSPort(pFilter) && ep_IsFilterUseDPort(pFilter));}
inline BOOL ep_IsFilterUseSPort(ep_ether_cap_filter_ports *pPorts)	{	return (pPorts->sport != 0);}
inline BOOL ep_IsFilterUseDPort(ep_ether_cap_filter_ports *pPorts)	{	return (pPorts->dport != 0);}
inline BOOL ep_IsFilterUsePort(ep_ether_cap_filter_ports *pPorts)	{	return (ep_IsFilterUseSPort(pPorts) || ep_IsFilterUseDPort(pPorts));}
inline BOOL ep_IsFilterUseSDPort(ep_ether_cap_filter_ports *pPorts)	{	return (ep_IsFilterUseSPort(pPorts) && ep_IsFilterUseDPort(pPorts));}

void ep_SetIP(ep_ip_address *pIP, ULONG dwIP);
inline void ep_SetIP(ep_ip_address &ip, ULONG dwIP)		{		ep_SetIP(&ip, dwIP);	}
void ep_SetIpV4(ep_ip_address *ip, const CString &strIP);
inline void ep_SetIpV4(ep_ip_address &ip, const CString &strIP)		{	ep_SetIpV4(&ip, strIP);	}

void ep_GetIpV4(ep_ip_address *ip, CString &strIP);
void ep_GetIpV4_H_L(ep_ip_address *ip, CString &strIP);
DWORD ep_GetIpV4(const CString &strIP);
DWORD ep_GetIpV4_H_L(const CString &strIP);
inline void ep_GetIpV4(ep_ip_address &ip, CString &strIP)	{		ep_GetIpV4(&ip, strIP);	}

void ep_FreeFilters(ep_ether_cap_filters *pFilters);
inline void ep_FreeFilters(ep_ether_cap_filters &filters)	{	ep_FreeFilters(&filters);	}

BOOL ep_SetFilterCount(ep_ether_cap_filters *pFilters, u_char count);
inline BOOL ep_SetFilterCount(ep_ether_cap_filters &filters, u_char count)	{	return ep_SetFilterCount(&filters, count);	}

void ep_SetTcpFilter(ep_ether_cap_filters *pFilters, u_char index, DWORD sip, DWORD dip, SHORT sport, SHORT dport);
inline void ep_SetTcpFilter(ep_ether_cap_filters &filters, u_char index, DWORD sip, DWORD dip, SHORT sport, SHORT dport)	{	ep_SetTcpFilter(&filters, index, sip, dip, sport, dport);	}
void ep_SetUdpFilter(ep_ether_cap_filters *pFilters, u_char index, DWORD sip, DWORD dip, SHORT sport, SHORT dport);
inline void ep_SetUdpFilter(ep_ether_cap_filters &filters, u_char index, DWORD sip, DWORD dip, SHORT sport, SHORT dport)	{	ep_SetUdpFilter(&filters, index, sip, dip, sport, dport);	}

ep_ether_cap_filter* ep_AddTcpFilter(ep_ether_cap_filters *pFilters, DWORD sip, DWORD dip, SHORT sport, SHORT dport);
inline ep_ether_cap_filter* ep_AddTcpFilter(ep_ether_cap_filters &filters, DWORD sip, DWORD dip, SHORT sport, SHORT dport)	{	return ep_AddTcpFilter(&filters, sip, dip, sport, dport);	}
ep_ether_cap_filter* ep_AddUdpFilter(ep_ether_cap_filters *pFilters, DWORD sip, DWORD dip, SHORT sport, SHORT dport);
inline ep_ether_cap_filter* ep_AddUdpFilter(ep_ether_cap_filters &filters, DWORD sip, DWORD dip, SHORT sport, SHORT dport)	{	return ep_AddUdpFilter(&filters, sip, dip, sport, dport);	}

ep_ether_cap_filter* ep_FindFilter(ep_ether_cap_filters *pFilters, u_char type, DWORD sip, DWORD dip, SHORT sport, SHORT dport);

ep_ether_cap_filter* ep_AddFilter(ep_ether_cap_filters *pFilters, u_char type, DWORD sip, DWORD dip, SHORT sport, SHORT dport);
inline ep_ether_cap_filter* ep_AddFilter(ep_ether_cap_filters &filters, u_char type, DWORD sip, DWORD dip, SHORT sport, SHORT dport)	{	return ep_AddFilter(&filters, type, sip, dip, sport, dport);	}

void ep_DeleteFilter(ep_ether_cap_filters *pFilters, ep_ether_cap_filter *pFilter);
void ep_DeleteFilter(ep_ether_cap_filters *pFilters, u_char index);

void ep_GetFilterString(ep_ether_cap_filter *pFilter, CString &strFilter);
inline void ep_GetFilterString(ep_ether_cap_filter &filter, CString &strFilter)		{	ep_GetFilterString(&filter, strFilter);	}

void ep_GetFiltersString(ep_ether_cap_filters *pFilters, CString &strFilter);
inline void ep_GetFiltersString(ep_ether_cap_filters &filters, CString &strFilter)		{	ep_GetFiltersString(&filters, strFilter);	}

void ep_GetFilterType(UINT nType, CString &strType);
void ep_GetIpProtocol(UINT nProtocol, CString &strProtocol);


//////////////////////////////////////////////////////////////////////////
COLORREF GetEpCapIpGroupColor(EP_ETHER_CAP_IP_GROUP &ip);
