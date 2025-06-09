
// XPing.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "../API/StringApi.h"
#include "XPing.h"

#ifndef _PSX_QT_LINUX_
#include "inet_ntop.h"
#include < ws2tcpip.h >

#include <iphlpapi.h>
#pragma comment(lib,"iphlpapi.lib")

#include <winsock2.h>
#pragma comment( lib, "ws2_32.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//#define WIN32_LEAN_AND_MEAN

// ICMP ������, ����μ����ĵĵ�һ��
#define ICMP_ECHO_REPLY 0 
#define ICMP_DEST_UNREACH 3
#define ICMP_TTL_EXPIRE 11
#define ICMP_ECHO_REQUEST 8

// ��С��ICMP����С
#define ICMP_MIN 8


// IP ��ͷ
struct IPHeader 
{
	BYTE h_len:4; // Length of the header in dwords
	BYTE version:4; // Version of IP
	BYTE tos; // Type of service
	USHORT total_len; // Length of the packet in dwords
	USHORT ident; // unique identifier
	USHORT flags; // Flags
	BYTE ttl; // Time to live, ����ֶ�������һ��������ʵ��Tracert����
	BYTE proto; // Protocol number (TCP, UDP etc)
	USHORT checksum; // IP checksum
	ULONG source_ip;
	ULONG dest_ip;
};

// ICMP ��ͷ(ʵ�ʵİ�������timestamp�ֶ�, 
// ��������������Ļ�Ӧʱ��,��ʵ��ȫû�б�Ҫ������)
struct ICMPHeader
{
	BYTE type; // ICMP packet type
	BYTE code; // Type sub code
	USHORT checksum;
	USHORT id;
	USHORT seq;
	ULONG timestamp; // not part of ICMP, but we need it
};


extern USHORT ip_checksum(USHORT* buffer, int size);
extern int setup_for_ping(char* host, int ttl, SOCKET& sd, sockaddr_in& dest);
extern int send_ping(SOCKET sd, const sockaddr_in& dest, ICMPHeader* send_buf, int packet_size);
extern int recv_ping(SOCKET sd, sockaddr_in& source, IPHeader* recv_buf,
					 int packet_size);
extern int decode_reply(IPHeader* reply, int bytes, sockaddr_in* from);
extern void init_ping_packet(ICMPHeader* icmp_hdr, int packet_size, int seq_no);

/*
* ������: rawping_driver.cpp
* ˵��: 
* ��������,Ҳ��������
*/
#define DEFAULT_PACKET_SIZE 32 // Ĭ��ICMP���ֽ���
#define DEFAULT_TTL 30 // Ĭ��TTLֵ
#define MAX_PING_DATA_SIZE 1024 // ������ݿ� 
#define MAX_PING_PACKET_SIZE (MAX_PING_DATA_SIZE + sizeof(IPHeader)) //���ICMP������

/* Ϊ send_buf �� recv_buf �����ڴ�
* send_buf��СΪ packet_size
* recv_buf��СΪ MAX_PING_PACKET_SIZE, ��֤����send_buf
*/
int allocate_buffers(ICMPHeader*& send_buf, IPHeader*& recv_buf,
					 int packet_size);


///////////////////////////////////////////////////////////////////////
// Program entry point

int xping(char* pszIP)
{
	int nRet = 0;
	int seq_no = 0; //���ڷ��ͺͽ��ܵ�ICMP��ͷ��
	ICMPHeader* send_buf = 0; 
	IPHeader* recv_buf = 0;

	// �ж��������Ƿ�Ϸ�
// 	if (argc < 2) {
// 		cerr << "usage: " << argv[0] << " [data_size] [ttl]" <<
// 			endl;
// 		cerr << "\tdata_size can be up to " << MAX_PING_DATA_SIZE <<
// 			" bytes. Default is " << DEFAULT_PACKET_SIZE << "." << 
// 			endl; 
// 		cerr << "\tttl should be 255 or lower. Default is " <<
// 			DEFAULT_TTL << "." << endl;
// 		return 1;
// 	}

	// ���������в���
	int packet_size = DEFAULT_PACKET_SIZE;
	int ttl = DEFAULT_TTL;

// 	if (argc > 2) {
// 		int temp = atoi(argv[2]);
// 		if (temp != 0) {
// 			packet_size = temp;
// 		}
// 		if (argc > 3) {
// 			temp = atoi(argv[3]);
// 			if ((temp >= 0) && (temp <= 255)) {
// 				ttl = temp;
// 			}
// 		}
// 	}

	packet_size = max(sizeof(ICMPHeader), 
		min(MAX_PING_DATA_SIZE, (unsigned int)packet_size));

	// ���� Winsock
	WSAData wsaData;

	if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0)
	{
		//cerr << "Failed to find Winsock 2.1 or better." << endl;
		return nRet;
	}

	SOCKET sd; // RAW Socket���
	sockaddr_in dest, source; 

	// ��������(����sd, ����ttl, ����dest��ֵ)
	if (setup_for_ping(pszIP, ttl, sd, dest) < 0) 
	{
		goto cleanup; //�ͷ���Դ���˳�
	}
	
	// Ϊsend_buf��recv_buf�����ڴ� 
	if (allocate_buffers(send_buf, recv_buf, packet_size) < 0) 
	{
		goto cleanup;
	}
	
	// ���Ի�IMCP���ݰ�(type=8,code=0)
	init_ping_packet(send_buf, packet_size, seq_no);
	long nRrvCount = 0;

	// ����ICMP���ݰ�
	if (send_ping(sd, dest, send_buf, packet_size) >= 0)
	{
		while (nRrvCount < 5) 
		{
			nRrvCount++;

			// ���ܻ�Ӧ��
			if (recv_ping(sd, source, recv_buf, MAX_PING_PACKET_SIZE) <	0)
			{
					// Pull the sequence number out of the ICMP header. If 
					// it's bad, we just complain, but otherwise we take 
					// off, because the read failed for some reason.
					unsigned short header_len = recv_buf->h_len * 4;
					ICMPHeader* icmphdr = (ICMPHeader*)((char*)recv_buf + header_len);
				
					if (icmphdr->seq != seq_no) 
					{
						//cerr << "bad sequence number!" << endl;
						continue;
					}
					else 
					{
						nRet = 0;
						break;
					}
			}

			if (decode_reply(recv_buf, packet_size, &source) == 0)
			{
				// Success or fatal error (as opposed to a minor error) 
				// so take off.
				nRet = 1;
				break;
			}
		}
	}

cleanup:
	delete[]send_buf; //�ͷŷ�����ڴ�
	delete[]recv_buf;
	WSACleanup(); // ����winsock

	return nRet;
}

// Ϊsend_buf �� recv_buf���ڴ����. ̫��, ���Թ�
int allocate_buffers(ICMPHeader*& send_buf, IPHeader*& recv_buf,
					 int packet_size)
{
	// First the send buffer
	send_buf = (ICMPHeader*)new char[packet_size]; 

	if (send_buf == 0) 
	{
		//cerr << "Failed to allocate output buffer." << endl;
		return -1;
	}

	// And then the receive buffer
	recv_buf = (IPHeader*)new char[MAX_PING_PACKET_SIZE];

	if (recv_buf == 0)
	{
		//cerr << "Failed to allocate output buffer." << endl;
		return -1;
	}

	return 0;
}

/*
* ������: rawping.cpp
* ˵��: 
* ��Ҫ������ʵ�ֲ���
*/


// ����ICMP����У��͵ļ��㷨, �ܶ�ط�����˵��, ����û�б�Ҫ��ϸ��
// ֻ��һ��Ҫ��, ��У��֮ǰ, ��ؽ�ICMP��ͷ��checksum�ֶ���Ϊ0
USHORT ip_checksum(USHORT* buffer, int size) 
{
	unsigned long cksum = 0;

	// Sum all the words together, adding the final byte if size is odd
	while (size > 1) {
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}

	if (size)
	{
		cksum += *(UCHAR*)buffer;
	}

	// Do a little shuffling
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);

	// Return the bitwise complement of the resulting mishmash
	return (USHORT)(~cksum);
}

//���Ի�RAW Socket, ����ttl, ���Ի�dest
// ����ֵ <0 ��ʧ��

int setup_for_ping(char* host, int ttl, SOCKET& sd, sockaddr_in& dest)
{
	// Create the socket
	sd = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, 0, 0, WSA_FLAG_OVERLAPPED);

	if (sd == INVALID_SOCKET) 
	{
// 		cerr << "Failed to create raw socket: " << WSAGetLastError() <<
// 			endl;
		return -1;
	}

	struct timeval tv_out;
	tv_out.tv_sec = 200;//�ȴ�200ms
	tv_out.tv_usec = 0;

	if( setsockopt( sd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv_out, sizeof( tv_out ) ) == SOCKET_ERROR )
	{
		return -1;
	}

	if( setsockopt( sd, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv_out, sizeof( tv_out ) ) == SOCKET_ERROR )
	{
		return -1;
	}

	if (setsockopt(sd, IPPROTO_IP, IP_TTL, (const char*)&ttl, 
		sizeof(ttl)) == SOCKET_ERROR)
	{
// 			cerr << "TTL setsockopt failed: " << WSAGetLastError() << endl;
			return -1;
	}

	// Initialize the destination host info block
	memset(&dest, 0, sizeof(dest));

	// Turn first passed parameter into an IP address to ping
	unsigned int addr = inet_addr(host);
	if (addr != INADDR_NONE) 
	{
		// It was a dotted quad number, so save result
		dest.sin_addr.s_addr = addr;
		dest.sin_family = AF_INET;
	}
	else 
	{
		// Not in dotted quad form, so try and look it up
		hostent* hp = gethostbyname(host);

		if (hp != 0)
		{
			// Found an address for that host, so save it
			memcpy(&(dest.sin_addr), hp->h_addr, hp->h_length);
			dest.sin_family = hp->h_addrtype;
		}
		else 
		{
			// Not a recognized hostname either!
// 			cerr << "Failed to resolve " << host << endl;
			return -1;
		}
	}



	return 0;
}




//���Ի�ICMP�İ�ͷ, ��data�����������, ��������������У���

void init_ping_packet(ICMPHeader* icmp_hdr, int packet_size, int seq_no)
{
	// Set up the packet's fields
	icmp_hdr->type = ICMP_ECHO_REQUEST;
	icmp_hdr->code = 0;
	icmp_hdr->checksum = 0;
	icmp_hdr->id = (USHORT)GetCurrentProcessId();
	icmp_hdr->seq = seq_no;
	icmp_hdr->timestamp = GetTickCount();

	// "You're dead meat now, packet!"
	const unsigned long int deadmeat = 0xDEADBEEF;
	char* datapart = (char*)icmp_hdr + sizeof(ICMPHeader);
	int bytes_left = packet_size - sizeof(ICMPHeader);

	while (bytes_left > 0)
	{
		memcpy(datapart, &deadmeat, min(int(sizeof(deadmeat)), 
			bytes_left));
		bytes_left -= sizeof(deadmeat);
		datapart += sizeof(deadmeat);
	}

	// Calculate a checksum on the result
	icmp_hdr->checksum = ip_checksum((USHORT*)icmp_hdr, packet_size);
}

// �������ɵ�ICMP��
// ����ֵ <0 ��ʧ��

int send_ping(SOCKET sd, const sockaddr_in& dest, ICMPHeader* send_buf,
			  int packet_size)
{
	// Send the ping packet in send_buf as-is
// 	cout << "Sending " << packet_size << " bytes to " << 
// 		inet_ntoa(dest.sin_addr) << "..." << flush;
	int bwrote = sendto(sd, (char*)send_buf, packet_size, 0, 
		(sockaddr*)&dest, sizeof(dest));

	if (bwrote == SOCKET_ERROR) 
	{
// 		cerr << "send failed: " << WSAGetLastError() << endl;
		return -1;
	}
	else if (bwrote < packet_size) 
	{
// 		cout << "sent " << bwrote << " bytes..." << flush;
	}

	return 0;
}


// ����ICMP��
// ����ֵ <0 ��ʧ��
int recv_ping(SOCKET sd, sockaddr_in& source, IPHeader* recv_buf, 
			  int packet_size)
{
	// Wait for the ping reply
	int fromlen = sizeof(source);
	int bread = recvfrom(sd, (char*)recv_buf, 
		packet_size + sizeof(IPHeader), 0,
		(sockaddr*)&source, &fromlen);

	if (bread == SOCKET_ERROR)
	{
// 		cerr << "read failed: ";
		int errocode = WSAGetLastError();
		if (WSAGetLastError() == WSAEMSGSIZE)
		{
// 			cerr << "buffer too small" << endl;
		}
		else 
		{
// 			cerr << "error #" << WSAGetLastError() << endl;
		}

		return -1;
	}

	return 0;
}


// ���յ���ICMP����
// ����ֵ -2�����, -1 ��ʧ��, 0 �ɹ�
int decode_reply(IPHeader* reply, int bytes, sockaddr_in* from) 
{
	// ����IP��ͷ, �ҵ�ICMP�İ�ͷ
	unsigned short header_len = reply->h_len * 4;
	ICMPHeader* icmphdr = (ICMPHeader*)((char*)reply + header_len);

	// ���ĳ��ȺϷ�, header_len + ICMP_MINΪ��СICMP���ĳ���
	if (bytes < header_len + ICMP_MIN) 
	{
// 		cerr << "too few bytes from " << inet_ntoa(from->sin_addr) << 
// 			endl;
		return -1;
	}
	// ����İ�������ϸ�μ��ҵĵ�һ���� "͸��ICMPЭ��(һ): Э��ԭ��"
	else if (icmphdr->type != ICMP_ECHO_REPLY) 
	{ //�������ظ�
		if (icmphdr->type != ICMP_TTL_EXPIRE)
		{ //ttl��Ϊ��
			if (icmphdr->type == ICMP_DEST_UNREACH)
			{ //�������ɴ�
// 				cerr << "Destination unreachable" << endl;
			}
			else
			{ //�Ƿ���ICMP������
// 				cerr << "Unknown ICMP packet type " << int(icmphdr->type) <<
// 					" received" << endl;
			}
			return -1;
		}
	}
	else if (icmphdr->id != (USHORT)GetCurrentProcessId())
	{ 
		//���Ǳ����̷��İ�, ������ͬ��������ping���̷���
		return -2;
	}

	// ָ���������˶�Զ
	// [bugfree]����Ϊ��������������, ��Ϊ��Щϵͳ��ttl��ֵΪ128��winXP, 
	// ��ЩΪ256���ҵ�DNS������211.97.168.129, ���߼���Ϊ256�е����, 
	// ����һ��̽���������, ��email:zhangliangsd@hotmail.com
	int nHops = int(256 - reply->ttl);
	if (nHops == 192)
	{ 
		// TTL came back 64, so ping was probably to a host on the
		// LAN -- call it a single hop.
		nHops = 1;
	}
	else if (nHops == 128)
	{
		// Probably localhost
		nHops = 0;
	}

	// ���й�������,��ӡ��Ϣ
// 	cout << endl << bytes << " bytes from " << 
// 		inet_ntoa(from->sin_addr) << ", icmp_seq " << 
// 		icmphdr->seq << ", ";

	if (icmphdr->type == ICMP_TTL_EXPIRE)
	{
// 		cout << "TTL expired." << endl;
	}
	else 
	{
// 		cout << nHops << " hop" << (nHops == 1 ? "" : "s");
// 		cout << ", time: " << (GetTickCount() - icmphdr->timestamp) <<
// 			" ms." << endl;
	}

	return 0;
}

BOOL GetIPFromHostNameAndMac(const CString &strHost,const CString &strServerMac,const CString &strLocalGatewayMac,CString &strIP)
{
	ASSERT(!strHost.IsEmpty());
	ASSERT(!strServerMac.IsEmpty());
	ASSERT(!strLocalGatewayMac.IsEmpty());

	XInitSocket();

	char *pchHost = NULL;
	CString_to_char(strHost,&pchHost);

	struct hostent *host = NULL;
	host = gethostbyname(pchHost);
	delete pchHost;


	if (host == NULL) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�Ҳ���������%s��"), strHost);
		return FALSE;    
	}    

	//��������ı���    
	char **pptr = NULL;    
	char domain[64];    

	HRESULT hr;
	IPAddr  ipAddr;
	ULONG   pulMac[2];
	ULONG   ulLen = 6;

	CString strTmpMac = _T("");
	CString strTmpIP = _T("");
	char pszTempIP[32];

	switch(host->h_addrtype)			
	{				
	case AF_INET:				
	case AF_INET6:				
		pptr = host->h_addr_list;  				
		for(; *pptr!=NULL; pptr++) 
		{
			strTmpIP = xinet_ntop(host->h_addrtype, *pptr, domain,64);
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("������IP��%s"), strTmpIP);

			CString_to_char(strTmpIP, pszTempIP);
			memset (pulMac, 0xff, sizeof (pulMac));
			ipAddr = inet_addr(pszTempIP);
			hr = SendARP(ipAddr, 0, pulMac, &ulLen);

			if (hr == NO_ERROR)
			{
				unsigned char * mac_addr=(unsigned char*)pulMac;
				strTmpMac.Format(_T("%.2x-%.2x-%.2x-%.2x-%.2x-%.2x")
					,mac_addr[0],mac_addr[1],mac_addr[2],mac_addr[3],mac_addr[4],mac_addr[5]);

				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("������MAC��%s"), strTmpMac);
				if (strTmpMac.CompareNoCase(strServerMac) == 0)
				{
					strIP = strTmpIP;
					return TRUE;
				}
				else if (strTmpMac.CompareNoCase(strLocalGatewayMac) == 0)
				{
					strIP = strTmpIP;
					return TRUE;
				}
			}
		}								
		break;			
	default:				
		break;	
	}

	return FALSE; 
}

BOOL XInitSocket()
{
	//��ʼ��socket
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );

	if ( err != 0 ) 
	{
		return FALSE;
	}

	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 ) 
	{
		XExitSocket();
		return FALSE; 
	}

	return TRUE;
}

void XExitSocket()
{
	WSACleanup();
}
#else

#include <QString>
#include <QProcess>


int xping(char* pszIP)
{
    char pszCmd[64];
    sprintf(pszCmd, "ping -c 1 %s ", pszIP);

    if (system(pszCmd) == 0)
    {
        return 1;
    }
    else
    {
         return 0;
    }
}

BOOL GetIPFromHostNameAndMac(const CString &strHost,const CString &strServerMac,const CString &strLocalGatewayMac,CString &strIP)
{
    return FALSE;
}

BOOL XInitSocket()
{
    return TRUE;
}

void XExitSocket()
{

}

#endif


BOOL xping(const CString &strIP)
{
	char pszIP[20];
	CString_to_char(strIP,pszIP);
	return xping(pszIP);
}
