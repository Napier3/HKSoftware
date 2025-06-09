#include "StdAfx.h"

#include "PcapToAt02d.h"

CPcapToAt02d::CPcapToAt02d()
{
	m_nIndexPacket = 0;
	m_nIndexAt02d = 0;
	m_bReadFinished = FALSE;
	m_nBufferLen = 204800;
	::memset(m_byBufferIN, 0x0, MAX_PCAPTOAT02D_CAP_BUFFER_IN + 2000);
	::memset(m_byBufferOut, 0x0, MAX_PCAPTOAT02D_CAP_BUFFER_OUT);
	m_nLeftBuffer = 0;
	m_nIndexLastPacket = 0;
	m_nLastPacketLen = 0;
	m_nCopyFlag = 0;
	m_nParseLen = 0;
	m_nAt02dLen = 0;
	m_nFirstEnterFile = 0;
	m_bPcapFile = FALSE;
}

CPcapToAt02d::~CPcapToAt02d()
{

}

/*******************************************************************************************************************
*设置文件名称包括路径过来，在这个类进行读取，然后对文件进行整理；
********************************************************************************************************************/
BOOL CPcapToAt02d::OpenPcapFile(const CString &strFilePath)
{
	if (m_bPcapFile)
	{
		m_oPcapFile.Close();
		m_bPcapFile = FALSE;
	}
	m_bPcapFile =  m_oPcapFile.Open(strFilePath, CFile::modeRead);
	//获取文件的长度；
	m_nLength  = m_oPcapFile.GetLength();
	m_bReadFinished = FALSE;
	m_nFirstEnterFile = 0;//打开文件的时候是否获取PCAP文件头的标志；
	return m_bPcapFile;
}

#define WRITEPCAPTOATO2DFILE
int g_nReadFileCnt = 0;
FILE* g_pwFile = NULL;
BOOL CPcapToAt02d::ReadPcapFile()
{
	long nLen  =  0;
	//等于1的时候不添补；
	if (m_nCopyFlag==1)
	{
		m_nLeftBuffer = 0;
	}
	//等于2的时候添补、拷贝进去；
	else if (m_nCopyFlag==2)
	{
		//把剩下的报文拷贝进去，从头开始存放；
		if (m_nLeftBuffer  > 0)
			::memcpy(m_byBufferIN,  m_byBufferIN  +  m_nIndexLastPacket,   m_nLeftBuffer);
	}

	//每次读取204800个字节；
	nLen  = m_oPcapFile.Read(m_byBufferIN + m_nLeftBuffer, MAX_PCAPTOAT02D_CAP_BUFFER_IN );
	m_nBufferLen   =  nLen ;

	//这里记录每次读取的长度, 然后不断的累加, 直道等于文件的长度为止；
	m_nParseLen  +=  nLen;

	//把之前剩下帧拷贝到里边，所以这个长度要加上；
	if (m_nCopyFlag==2)
		nLen += m_nLeftBuffer;
	
	//long  nLenAt02d  = 0; 
	long nPacketCnt  = 0;
	::memset(m_byBufferOut, 0x0, MAX_PCAPTOAT02D_CAP_BUFFER_OUT);
	m_nAt02dLen = 0;

	//这里送入是PCAP报文，导出来的是AT02D报文；
	CreateAt02dData(m_byBufferIN,    nLen,   m_byBufferOut,   m_nAt02dLen,   nPacketCnt );

#ifdef WRITEPCAPTOATO2DFILE
	CString strPath = "D:/Program Files/EPOTO/e-Monitor/Library/mym.at02d";

	if (g_nReadFileCnt==0)
	{
#ifdef _PSX_IDE_QT_
		g_pwFile = fopen( strPath.GetString(), "wb");  
#else
		g_pwFile = fopen( strPath, "wb");  
#endif
		//fwrite( (void*)(m_byBufferIN),  1, nLen,  pwFile);  
		if (g_pwFile != NULL)
		{
			fwrite( (void*)(m_byBufferOut),  1, m_nAt02dLen,  g_pwFile);  
			//	fclose( pwFile); 
		}
	}
	else 
	{
		if (g_pwFile != NULL)
			fwrite( (void*)(m_byBufferOut),  1, m_nAt02dLen,  g_pwFile);  
		//	fclose( pwFile); 
	}


#endif

	g_nReadFileCnt++;
	if (nLen == 0)
	{
		if (g_pwFile!=NULL)
			fclose( g_pwFile); 
		m_bReadFinished = TRUE;
		return FALSE;
	}

	return TRUE;
}

//在这个函数里进行转化，每次填入204800个字节进去转化，可能会有剩余字节，也就是半帧的情况存在，要攒着。然后倒入；
void CPcapToAt02d::CreateAt02dData(BYTE * pBuffer,   long nLength,  BYTE *pDataAt02D,  long & nLenAt02d,  long &nPacketCnt)
{	 
	SST_AT02_PKT_HEAD  at02dpktHead,  at02dpktHeadTemp;
	_file_header fileHeader;
	_pkthdr pkthdr;

	at02dpktHead.hd_flag = 0x64056405;
	at02dpktHead.filber_smv_gs = 0;
	at02dpktHead.appid = 0;
	at02dpktHead.crc = 0;
	int nIndex = 0;
	if (m_nFirstEnterFile==0)
		nIndex = sizeof(struct _file_header);  	
	else 
		nIndex = 0;
	m_nFirstEnterFile = 1;

	//memcpy( (void*)&fileHeader,   (void*)(pBuffer) ,  sizeof(struct _file_header));  

	// 报文帧数量；
	//m_nIndexPacket  = 0;
	m_nIndexAt02d   = 0;

//	int nLastPacketLen = 0;//记录最后一帧报文的长度；
//	int nIndexLastPacket  = 0;
	//这里为了读一点文件改造一点，需要记住最后一帧头的位置，为了最后的半帧能够接入后面的缓冲区，衔接上；
	while(nIndex  <  nLength)  
	{
		//获取报文头;
		memcpy( (void*)&pkthdr,  (void*)(pBuffer + nIndex)  ,  sizeof(struct _pkthdr));  

		//这里是记录最后一帧的报文头的索引；
		m_nIndexLastPacket  = nIndex ;

		//如果报文长度减去当前索引，小于上一帧报文的长度，那么则认为可以结束了，跳出循环；
		if (nLength  - nIndex   <  m_nLastPacketLen)
		{
			break;
		}

		nIndex +=  sizeof(struct _pkthdr) ;

		//填写帧头；
		at02dpktHead.nIndex         =    GetBigtoLittle32(m_nIndexPacket);
		at02dpktHead.packet_len  =    GetBigtoLittle16(pkthdr.iPLength) ;            //61850报文的长度	
		at02dpktHead.utc_s           =    GetBigtoLittle32(pkthdr.iTimeSecond);
		at02dpktHead.utc_ns         =    GetBigtoLittle32(pkthdr.iTimeSS);
		int nHeadLen =  0;
		//######################################################################
		//这里要判断假如长度为0的情况的异常报文的情况；暂时没有判断
		//######################################################################
		if ((24 + pkthdr.iPLength)%4==0)
			nHeadLen               =   ( (24 + pkthdr.iPLength )/4);                              //len*4=整个报文的长度
		else if ((24 + pkthdr.iPLength)%4==1)
			nHeadLen               =    ( (24 + pkthdr.iPLength + 3)/4);                         //len*4=整个报文的长度;
		else if ((24 + pkthdr.iPLength)%4==2)
			nHeadLen               =    ( (24 + pkthdr.iPLength + 2)/4);                         //len*4=整个报文的长度;
		else if ((24 + pkthdr.iPLength)%4==3)
			nHeadLen               =    ( (24 + pkthdr.iPLength + 1)/4);                         //len*4=整个报文的长度;

		at02dpktHead.len   =  GetBigtoLittle32(nHeadLen);

		//拷贝帧头；
		memcpy(pDataAt02D + m_nIndexAt02d,   &at02dpktHead ,  sizeof( SST_AT02_PKT_HEAD));  

		m_nIndexAt02d +=  sizeof(SST_AT02_PKT_HEAD);

		//拷贝数据；
		memcpy(pDataAt02D + m_nIndexAt02d,  pBuffer + nIndex,  pkthdr.iPLength);  

		m_nIndexAt02d   +=   nHeadLen *  4  +  4  -  sizeof(SST_AT02_PKT_HEAD);   //后面加的这个4意思是0x05640564;

		//不够4的整数倍补齐0；
		if ((24 + pkthdr.iPLength)%4==0)
		{}
		else if ((24 + pkthdr.iPLength)%4==1)
		{
			*(pDataAt02D + m_nIndexAt02d  -  3) = 0;
			*(pDataAt02D + m_nIndexAt02d  -  2) = 0;
			*(pDataAt02D + m_nIndexAt02d  -  1) = 0;
		}
		else if ((24 + pkthdr.iPLength)%4==2)
		{
			*(pDataAt02D + m_nIndexAt02d  -  2) = 0;
			*(pDataAt02D + m_nIndexAt02d  -  1) = 0;
		}
		else if ((24 + pkthdr.iPLength)%4==3)
		{
			*(pDataAt02D + m_nIndexAt02d  - 1) = 0;
		}

		//这样就是记录，最后一帧的帧头加上报文的长度，就是整个完整一帧的长度，这里是为了获取循环退出去之前的最后一帧的长度；
		m_nLastPacketLen =  pkthdr.iPLength   +   sizeof(struct _pkthdr) ;

		//获取报文数据；
		nIndex +=  pkthdr.iPLength;  
		m_nIndexPacket++;
	}
	nPacketCnt  = m_nIndexPacket ;
	nLenAt02d  =  m_nIndexAt02d;
	m_nAt02dLen = m_nIndexAt02d ;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//这里相减获取最后那一帧没有解析的那一帧报文的起始点,剩下的长度，下次在把这半帧给拷贝进去；
	m_nLeftBuffer  =  nLength  -  m_nIndexLastPacket;
	if (m_nLeftBuffer == m_nLastPacketLen && m_nLeftBuffer != 0)//最后一帧的长度；这两个要比较一下；
	{//如果这两个值相等且不等于零，则不用把剩余的长度拷贝进去，否则都要拷贝进去。
		m_nCopyFlag = 1;
	}
	else 
	{
		m_nCopyFlag = 2;//等于2的时候需要拷贝；
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

 //参数说明：进入函数的缓冲区指针，缓冲区长度；变成AT02D的缓冲区，缓冲区长度，帧的数量；
 void CPcapToAt02d::GetAt02dData(BYTE * pBuffer,   long nLength,  BYTE *pDataAt02D,  long & nLenAt02d,  long &nPacketCnt)
 {
	 SST_AT02_PKT_HEAD  at02dpktHead,  at02dpktHeadTemp;
	 _file_header fileHeader;
	 _pkthdr pkthdr;

	 at02dpktHead.hd_flag = 0x64056405;
	 at02dpktHead.filber_smv_gs = 0;
	 at02dpktHead.appid = 0;
	 at02dpktHead.crc = 0;

	 int nIndex = sizeof(struct _file_header);  
	 memcpy( (void*)&fileHeader,   (void*)(pBuffer) ,  sizeof(struct _file_header));  

	 // 报文帧数量；
	 m_nIndexPacket  = 0;
	 m_nIndexAt02d   = 0;

	 while(nIndex  <  nLength)  
	 {
		 //获取报文头;
		 memcpy( (void*)&pkthdr,  (void*)(pBuffer + nIndex)  ,  sizeof(struct _pkthdr));  

		 nIndex +=  sizeof(struct _pkthdr) ;

		 //填写帧头；
		 at02dpktHead.nIndex         =    GetBigtoLittle32(m_nIndexPacket);
		 at02dpktHead.packet_len  =    GetBigtoLittle16(pkthdr.iPLength) ;            //61850报文的长度	
		 at02dpktHead.utc_s           =    GetBigtoLittle32(pkthdr.iTimeSecond);
		 at02dpktHead.utc_ns         =    GetBigtoLittle32(pkthdr.iTimeSS);
		 int nHeadLen =  0;
		 //######################################################################
		 //这里要判断假如长度为0的情况的异常报文的情况；暂时没有判断
		 //######################################################################
		 if ((24 + pkthdr.iPLength)%4==0)
			 nHeadLen               =   ( (24 + pkthdr.iPLength )/4);                              //len*4=整个报文的长度
		 else if ((24 + pkthdr.iPLength)%4==1)
			 nHeadLen               =    ( (24 + pkthdr.iPLength + 3)/4);                         //len*4=整个报文的长度;
		 else if ((24 + pkthdr.iPLength)%4==2)
			 nHeadLen               =    ( (24 + pkthdr.iPLength + 2)/4);                         //len*4=整个报文的长度;
		 else if ((24 + pkthdr.iPLength)%4==3)
			 nHeadLen               =    ( (24 + pkthdr.iPLength + 1)/4);                         //len*4=整个报文的长度;

		 at02dpktHead.len   =  GetBigtoLittle32(nHeadLen);

		 //拷贝帧头；
		 memcpy(pDataAt02D + m_nIndexAt02d,   &at02dpktHead ,  sizeof( SST_AT02_PKT_HEAD));  

		 m_nIndexAt02d +=  sizeof(SST_AT02_PKT_HEAD);

		 //拷贝数据；
		 memcpy(pDataAt02D + m_nIndexAt02d,  pBuffer + nIndex,  pkthdr.iPLength);  

		 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 int nFlag = 1;
		 if(m_nIndexPacket%10==0&&nFlag==2)
		 {
			 char strPath[100];  

			 sprintf( strPath, "D:\\Program Files\\EPOTO\\e-Monitor\\Library\\%d-%d.pcap",   m_nIndexPacket,   (int)at02dpktHead.utc_ns );  

			 strPath[99] = '\0';  

			 FILE* pwFile = fopen( strPath, "wb");  

			 fwrite((void*)&at02dpktHead,  1,  sizeof( SST_AT02_PKT_HEAD),   pwFile);  
			 fwrite( (void*)(pDataAt02D + m_nIndexAt02d),  1,  pkthdr.iPLength, pwFile);  
			 fclose( pwFile);  
		 }

		 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 m_nIndexAt02d   +=   nHeadLen *  4  +  4  -  sizeof(SST_AT02_PKT_HEAD);   //后面加的这个4意思是0x05640564;

		 //不够4的整数倍补齐0；
		 if ((24 + pkthdr.iPLength)%4==0)
		 {}
		 else if ((24 + pkthdr.iPLength)%4==1)
		 {
			 *(pDataAt02D + m_nIndexAt02d  -  3) = 0;
			 *(pDataAt02D + m_nIndexAt02d  -  2) = 0;
			 *(pDataAt02D + m_nIndexAt02d  -  1) = 0;
		 }
		 else if ((24 + pkthdr.iPLength)%4==2)
		 {
			 *(pDataAt02D + m_nIndexAt02d  -  2) = 0;
			 *(pDataAt02D + m_nIndexAt02d  -  1) = 0;
		 }
		 else if ((24 + pkthdr.iPLength)%4==3)
		 {
			 *(pDataAt02D + m_nIndexAt02d  - 1) = 0;
		 }

		 //获取报文数据；
		 nIndex +=  pkthdr.iPLength;  
		 m_nIndexPacket++;
	 }
	 nPacketCnt  = m_nIndexPacket ;
	 nLenAt02d = m_nIndexAt02d;
 }


 void CPcapToAt02d:: ClosePcapFile()
 {
	 if (m_bPcapFile)
	{
		m_oPcapFile.Close();
		m_bPcapFile = FALSE;
	}
 }

void CPcapToAt02d::ResetMember()
{
//	return;
	m_nIndexPacket = 0;
	m_nIndexAt02d = 0;
	m_bReadFinished = FALSE;
	m_nBufferLen = 204800;
	::memset(m_byBufferIN, 0x0, MAX_PCAPTOAT02D_CAP_BUFFER_IN + 2000);
	::memset(m_byBufferOut, 0x0, MAX_PCAPTOAT02D_CAP_BUFFER_OUT);
	m_nLeftBuffer = 0;
	m_nIndexLastPacket = 0;
	m_nLastPacketLen = 0;
	m_nCopyFlag = 0;
	m_nParseLen = 0;
	m_nAt02dLen = 0;
	m_nFirstEnterFile = 0;
	//m_bPcapFile = FALSE;
}

/*
010CCD01000108080808080B8
100C000

88B8
00010100
00000000
6181F5
8018494C32323031525049542F4C4C4E3024474F24676F63623181022710
8218494C32323031525049542F4C4C4E30246473474F4F534531
8318494C32323031525049542F4C4C4E3024474F24676F636231
8408386BE4A3FFFFFE0A
850400000001
860400000005
870100
8802000101
890100
8A0164
AB82028A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
830100910800
*/

/*
010CCD010001
08080808080B
8100C000

88B8
00010100

00000000

6181F5

8018494C32323031525049542F4C4C4E3024
474F24676F636231

81022710

8218494C32323031525049542F4C4C4E30246473474F4F534531

8318494C32323031525049542F4C4C4E3024474F24676F636231
8408386BE4C7FFFFFE0A
850400000001
860400000005
870100
88020001
890100
8A8A0164
AB
82028A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
8301009108000000000000000A
830100910800
*/
//默认是提取PCAP报文，直接把IP报文全部舍去，是为了防止9-2/GOOSE中混有其他报文，导致错误；所以先过滤一遍；
BOOL CPcapToAt02d::FilterTCPIPData(const CString & strPcapFile)
{
	pcap_t* fp;
	char errbuf[PCAP_ERRBUF_SIZE];
	//打开Pcap包

	byte byHead[24] = {0};

#ifdef _PSX_IDE_QT_
	FILE* pwFile = fopen( strPcapFile.GetString(), "rb"); 
#else
	FILE* pwFile = fopen( strPcapFile, "rb"); 
#endif
	if (pwFile   !=   NULL)
	{
		fread( byHead,  1, 24 ,pwFile);  
		fclose( pwFile);  
	}
	else
		return FALSE;

	fp = pcap_open_offline(strPcapFile.GetString(), errbuf);

	if (fp == NULL)
	{
		//MessageBox(errbuf);
		return  FALSE;
	}

	CString strFile;
	long nPos = strPcapFile.ReverseFind('.');
	strFile = strPcapFile.Left(nPos+1);
	strFile += "at02d";
	FILE *pfile = fopen(strFile.GetString(), "w+b");


	if (pfile == NULL)
	{
		pcap_close(fp);
		return FALSE;
	}

	//读取文件直到结尾
	struct pcap_pkthdr* header;		//报文头
	const unsigned char* pkt_data;	//报文内容
	IP_HEADER* iph;
	TCP_HEADER *tcph;
	u_int iph_len;
	u_int tcph_len;

	int nPacket =0;
	while ((pcap_next_ex(fp, &header, &pkt_data)) > 0)
	{
		ETHER_HEADER *eth = (ETHER_HEADER*)pkt_data;
	
		if (ntohs(eth->ether_type) == 0x0800)//IP
		{
			continue;
		}

		/*
		//偏移14个字节，是以太的头，后面2个字节是IP头，
		iph = (IP_HEADER*)(pkt_data + 14); //length of ethernet header  
		
		if (iph->proto == 6)
		{
			continue;
		}
	
		// 获取IP报文长度
		iph_len = (iph->ver_ihl & 0x0f) * 4;//这里的长度是头的长度，是4的倍数，也就是DWORD的数量；
		u_char *ip_data = (u_char*)iph;
		tcph = (TCP_HEADER*) (ip_data + iph_len);//这里又往后偏移了 IP报文头的长度，之后就是TCP报文的头，也是20个字节。

		//这里这个是端口，使用的时候要灵活运用，可以注销掉 19814 是AT02的端口；
		if (tcph->sport != 0xf707)//19814
		{
			//不是AT02发送上来的报文
			//continue;
		}

		tcph_len = ((tcph->th_lenres & 0xf0) >> 4) * 4;//4位首部长度，是DWORD个数量，也就是要乘以4 获得字节数；
		long nDataLen = ntohs(iph->tlen) - tcph_len - iph_len;// - 14ether_header; //这里头的IP长度 减去 tcp头长度，再减去IP头长度，就是数据的长度；

		ip_data = (u_char*)tcph;
		ip_data = ip_data + tcph_len;// 偏移TCP头的长度，后面就是TCP的数据了；
		*/
		//fwrite(ip_data, nDataLen, 1, pfile);
		int nDataLen = header->caplen;
		//第一帧要写个文件头；
		if (nPacket==0)
			fwrite(byHead, 24, 1, pfile);
		fwrite(header, 16, 1, pfile);
		fwrite(pkt_data, nDataLen, 1, pfile);
		nPacket++;
	}

	pcap_close(fp);
	fclose(pfile);
	return TRUE;
	//MessageBox("提取完成");
}
