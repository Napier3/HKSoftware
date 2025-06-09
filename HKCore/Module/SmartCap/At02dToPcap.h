#pragma once

#include "..\..\Module\SmartCap\61850Cap\CapGlobalDef.h"
#include "..\..\Module\WinPcap\Include\pcap.h"
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
	u_char	ver_ihl;		// Version (4 bits) + Internet header length (4 bits)//����λ��ͷ�ĳ��ȣ�
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
}TCP_HEADER;

//typedef struct ether_header
//{
//	u_char  ether_dhost[6];      /* destination eth addr */
//	u_char  ether_shost[6];      /* source ether addr    */
//	u_short ether_type;          /* packet type ID field */
//}ETHER_HEADER;

//2�ֽ����ĸߵ��ֽڻ���
inline short GetBigtoLittle16Ex(short nValue)
{
	BYTE    byH  = nValue&0x00ff;
	BYTE    byL   = (nValue&0xff00)>>8; 

	return  (byH<<8) |byL ;
}

//4���ֽڵĴ�С�˻�����
inline long GetBigtoLittle32Ex(long nValue)
{
	BYTE    by1   = nValue &0x000000ff;
	BYTE    by2   = (nValue&0x0000ff00)>>8; 
	BYTE    by3   = (nValue&0x00ff0000)>>16;
	BYTE    by4   = (nValue&0xff000000)>>24; 

	return  (by1<<24) | ( by2<<16) | (by3<<8) | by4 ;
}

#define MAX_AT02DTOPCAP_CAP_BUFFER_IN 204800 

#define MAX_AT02DTOPCAP_CAP_BUFFER_OUT 409600
class CAt02dToPcap
{

public:
	CAt02dToPcap();
	virtual ~CAt02dToPcap(void);

public:

	BOOL OpenPcapFile(const CString &strFilePath);

	void GetAt02dData(BYTE *pDataAt02D,  long & nLenAt02d, BYTE * pPcapBuffer,   long nPcapLength,   long &nPacketCnt);
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
	 BYTE    m_byBufferIN[MAX_AT02DTOPCAP_CAP_BUFFER_IN + 2000];
	 BYTE    m_byBufferOut[MAX_AT02DTOPCAP_CAP_BUFFER_OUT];
	 long      m_nBufferLen;  // һ�δ��ļ��ж�ȡ�ĳ���
	 long      m_nSendLeft ;  //���ͺ�ʣ�µĳ��ȣ�
	 long      m_nSendLen;   //�Ѿ����͵ĳ��ȣ�

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
