#pragma once

#include "../../Module/SmartCap/61850Cap/CapGlobalDef.h"
#include "../../Module/WinPcap/Include/pcap.h"
#pragma comment(lib, "wpcap.lib")
#define LINE_LEN 16

/* 4 bytes IP address */
typedef struct ip_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

/* IPv4 header */
typedef struct ip_header
{
	u_char	ver_ihl;		// Version (4 bits) + Internet header length (4 bits)//后四位是头的长度；
	u_char	tos;			// Type of service 
	u_short tlen;			// Total length 
	u_short identification; // Identification
	u_short flags_fo;		// Flags (3 bits) + Fragment offset (13 bits)
	u_char	ttl;			// Time to live
	u_char	proto;			// Protocol
	u_short crc;			// Header checksum
	ip_address	saddr;		// Source address
	ip_address	daddr;		// Destination address
	u_int	op_pad;			// Option + Padding
}IP_HEADER;

/* TCP header*/
typedef struct tcp_header
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
}TCP_HEADER;

//typedef struct ether_header
//{
//	u_char  ether_dhost[6];      /* destination eth addr */
//	u_char  ether_shost[6];      /* source ether addr    */
//	u_short ether_type;          /* packet type ID field */
//}ETHER_HEADER;

//2字节数的高低字节互调
inline short GetBigtoLittle16(short nValue)
{
	short nRet = 0;

	nRet = ( nValue          & 0xFF)  << 8;
	nRet = ((nValue >> 8) & 0xFF);

	return nRet;
}

//4个字节的大小端互调；
inline long GetBigtoLittle32(long nValue)
{
	long nRet = 0;
	nRet =   (nValue             & 0xFF) << 24;
	nRet += ((nValue >> 8)  & 0xFF)  << 16;
	nRet += ((nValue >> 16) & 0xFF)  << 8;
	nRet += ((nValue >> 24) & 0xFF);

	return nRet;
}

#define MAX_PCAPTOAT02D_CAP_BUFFER_IN 204800 

#define MAX_PCAPTOAT02D_CAP_BUFFER_OUT 409600
class CPcapToAt02d
{

public:
	CPcapToAt02d();
	virtual ~CPcapToAt02d(void);

public:

	BOOL OpenPcapFile(const CString &strFilePath);

	void GetAt02dData(BYTE * pBuffer,   long nLength,  BYTE *pDataAt02d,  long & nLenAt02d,  long &nPacketCnt);
	BOOL FilterTCPIPData(const CString & strPcapFile);
	BOOL ReadPcapFile();
	 void  ResetMember();
	 void  CreateAt02dData(BYTE * pBuffer,   long nLength,  BYTE *pDataAt02D,  long & nLenAt02d,  long &nPacketCnt);
	 void ClosePcapFile();

	 int m_nIndexPacket ;
	 int m_nIndexAt02d ;

	 // BYTE * m_pBuffer;
	 BYTE * m_pDataAt02D;
	 long      m_nLength; 
	 long      m_nPacketCnt;
	 BYTE    m_byBufferIN[MAX_PCAPTOAT02D_CAP_BUFFER_IN + 2000];
	 BYTE    m_byBufferOut[MAX_PCAPTOAT02D_CAP_BUFFER_OUT];
	 long      m_nBufferLen;  // 一次从文件中读取的长度
	 long      m_nSendLeft ;  //发送后还剩下的长度；
	 long      m_nSendLen;   //已经发送的长度；

	 BOOL m_bPcapFile;
	 CFile m_oPcapFile;
	 BOOL m_bReadFinished;

	 long m_nLeftBuffer;
	 long m_nIndexLastPacket;
	 long m_nLastPacketLen;
	 long m_nCopyFlag;

	 long m_nParseLen;
	 long  m_nAt02dLen ; 
	 long m_nFirstEnterFile;

protected:

};
