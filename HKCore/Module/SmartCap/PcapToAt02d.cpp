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
*�����ļ����ư���·�����������������ж�ȡ��Ȼ����ļ���������
********************************************************************************************************************/
BOOL CPcapToAt02d::OpenPcapFile(const CString &strFilePath)
{
	if (m_bPcapFile)
	{
		m_oPcapFile.Close();
		m_bPcapFile = FALSE;
	}
	m_bPcapFile =  m_oPcapFile.Open(strFilePath, CFile::modeRead);
	//��ȡ�ļ��ĳ��ȣ�
	m_nLength  = m_oPcapFile.GetLength();
	m_bReadFinished = FALSE;
	m_nFirstEnterFile = 0;//���ļ���ʱ���Ƿ��ȡPCAP�ļ�ͷ�ı�־��
	return m_bPcapFile;
}

#define WRITEPCAPTOATO2DFILE
int g_nReadFileCnt = 0;
FILE* g_pwFile = NULL;
BOOL CPcapToAt02d::ReadPcapFile()
{
	long nLen  =  0;
	//����1��ʱ������
	if (m_nCopyFlag==1)
	{
		m_nLeftBuffer = 0;
	}
	//����2��ʱ������������ȥ��
	else if (m_nCopyFlag==2)
	{
		//��ʣ�µı��Ŀ�����ȥ����ͷ��ʼ��ţ�
		if (m_nLeftBuffer  > 0)
			::memcpy(m_byBufferIN,  m_byBufferIN  +  m_nIndexLastPacket,   m_nLeftBuffer);
	}

	//ÿ�ζ�ȡ204800���ֽڣ�
	nLen  = m_oPcapFile.Read(m_byBufferIN + m_nLeftBuffer, MAX_PCAPTOAT02D_CAP_BUFFER_IN );
	m_nBufferLen   =  nLen ;

	//�����¼ÿ�ζ�ȡ�ĳ���, Ȼ�󲻶ϵ��ۼ�, ֱ�������ļ��ĳ���Ϊֹ��
	m_nParseLen  +=  nLen;

	//��֮ǰʣ��֡��������ߣ������������Ҫ���ϣ�
	if (m_nCopyFlag==2)
		nLen += m_nLeftBuffer;
	
	//long  nLenAt02d  = 0; 
	long nPacketCnt  = 0;
	::memset(m_byBufferOut, 0x0, MAX_PCAPTOAT02D_CAP_BUFFER_OUT);
	m_nAt02dLen = 0;

	//����������PCAP���ģ�����������AT02D���ģ�
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

//��������������ת����ÿ������204800���ֽڽ�ȥת�������ܻ���ʣ���ֽڣ�Ҳ���ǰ�֡��������ڣ�Ҫ���š�Ȼ���룻
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

	// ����֡������
	//m_nIndexPacket  = 0;
	m_nIndexAt02d   = 0;

//	int nLastPacketLen = 0;//��¼���һ֡���ĵĳ��ȣ�
//	int nIndexLastPacket  = 0;
	//����Ϊ�˶�һ���ļ�����һ�㣬��Ҫ��ס���һ֡ͷ��λ�ã�Ϊ�����İ�֡�ܹ��������Ļ��������ν��ϣ�
	while(nIndex  <  nLength)  
	{
		//��ȡ����ͷ;
		memcpy( (void*)&pkthdr,  (void*)(pBuffer + nIndex)  ,  sizeof(struct _pkthdr));  

		//�����Ǽ�¼���һ֡�ı���ͷ��������
		m_nIndexLastPacket  = nIndex ;

		//������ĳ��ȼ�ȥ��ǰ������С����һ֡���ĵĳ��ȣ���ô����Ϊ���Խ����ˣ�����ѭ����
		if (nLength  - nIndex   <  m_nLastPacketLen)
		{
			break;
		}

		nIndex +=  sizeof(struct _pkthdr) ;

		//��д֡ͷ��
		at02dpktHead.nIndex         =    GetBigtoLittle32(m_nIndexPacket);
		at02dpktHead.packet_len  =    GetBigtoLittle16(pkthdr.iPLength) ;            //61850���ĵĳ���	
		at02dpktHead.utc_s           =    GetBigtoLittle32(pkthdr.iTimeSecond);
		at02dpktHead.utc_ns         =    GetBigtoLittle32(pkthdr.iTimeSS);
		int nHeadLen =  0;
		//######################################################################
		//����Ҫ�жϼ��糤��Ϊ0��������쳣���ĵ��������ʱû���ж�
		//######################################################################
		if ((24 + pkthdr.iPLength)%4==0)
			nHeadLen               =   ( (24 + pkthdr.iPLength )/4);                              //len*4=�������ĵĳ���
		else if ((24 + pkthdr.iPLength)%4==1)
			nHeadLen               =    ( (24 + pkthdr.iPLength + 3)/4);                         //len*4=�������ĵĳ���;
		else if ((24 + pkthdr.iPLength)%4==2)
			nHeadLen               =    ( (24 + pkthdr.iPLength + 2)/4);                         //len*4=�������ĵĳ���;
		else if ((24 + pkthdr.iPLength)%4==3)
			nHeadLen               =    ( (24 + pkthdr.iPLength + 1)/4);                         //len*4=�������ĵĳ���;

		at02dpktHead.len   =  GetBigtoLittle32(nHeadLen);

		//����֡ͷ��
		memcpy(pDataAt02D + m_nIndexAt02d,   &at02dpktHead ,  sizeof( SST_AT02_PKT_HEAD));  

		m_nIndexAt02d +=  sizeof(SST_AT02_PKT_HEAD);

		//�������ݣ�
		memcpy(pDataAt02D + m_nIndexAt02d,  pBuffer + nIndex,  pkthdr.iPLength);  

		m_nIndexAt02d   +=   nHeadLen *  4  +  4  -  sizeof(SST_AT02_PKT_HEAD);   //����ӵ����4��˼��0x05640564;

		//����4������������0��
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

		//�������Ǽ�¼�����һ֡��֡ͷ���ϱ��ĵĳ��ȣ�������������һ֡�ĳ��ȣ�������Ϊ�˻�ȡѭ���˳�ȥ֮ǰ�����һ֡�ĳ��ȣ�
		m_nLastPacketLen =  pkthdr.iPLength   +   sizeof(struct _pkthdr) ;

		//��ȡ�������ݣ�
		nIndex +=  pkthdr.iPLength;  
		m_nIndexPacket++;
	}
	nPacketCnt  = m_nIndexPacket ;
	nLenAt02d  =  m_nIndexAt02d;
	m_nAt02dLen = m_nIndexAt02d ;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���������ȡ�����һ֡û�н�������һ֡���ĵ���ʼ��,ʣ�µĳ��ȣ��´��ڰ����֡��������ȥ��
	m_nLeftBuffer  =  nLength  -  m_nIndexLastPacket;
	if (m_nLeftBuffer == m_nLastPacketLen && m_nLeftBuffer != 0)//���һ֡�ĳ��ȣ�������Ҫ�Ƚ�һ�£�
	{//���������ֵ����Ҳ������㣬���ð�ʣ��ĳ��ȿ�����ȥ������Ҫ������ȥ��
		m_nCopyFlag = 1;
	}
	else 
	{
		m_nCopyFlag = 2;//����2��ʱ����Ҫ������
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

 //����˵�������뺯���Ļ�����ָ�룬���������ȣ����AT02D�Ļ����������������ȣ�֡��������
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

	 // ����֡������
	 m_nIndexPacket  = 0;
	 m_nIndexAt02d   = 0;

	 while(nIndex  <  nLength)  
	 {
		 //��ȡ����ͷ;
		 memcpy( (void*)&pkthdr,  (void*)(pBuffer + nIndex)  ,  sizeof(struct _pkthdr));  

		 nIndex +=  sizeof(struct _pkthdr) ;

		 //��д֡ͷ��
		 at02dpktHead.nIndex         =    GetBigtoLittle32(m_nIndexPacket);
		 at02dpktHead.packet_len  =    GetBigtoLittle16(pkthdr.iPLength) ;            //61850���ĵĳ���	
		 at02dpktHead.utc_s           =    GetBigtoLittle32(pkthdr.iTimeSecond);
		 at02dpktHead.utc_ns         =    GetBigtoLittle32(pkthdr.iTimeSS);
		 int nHeadLen =  0;
		 //######################################################################
		 //����Ҫ�жϼ��糤��Ϊ0��������쳣���ĵ��������ʱû���ж�
		 //######################################################################
		 if ((24 + pkthdr.iPLength)%4==0)
			 nHeadLen               =   ( (24 + pkthdr.iPLength )/4);                              //len*4=�������ĵĳ���
		 else if ((24 + pkthdr.iPLength)%4==1)
			 nHeadLen               =    ( (24 + pkthdr.iPLength + 3)/4);                         //len*4=�������ĵĳ���;
		 else if ((24 + pkthdr.iPLength)%4==2)
			 nHeadLen               =    ( (24 + pkthdr.iPLength + 2)/4);                         //len*4=�������ĵĳ���;
		 else if ((24 + pkthdr.iPLength)%4==3)
			 nHeadLen               =    ( (24 + pkthdr.iPLength + 1)/4);                         //len*4=�������ĵĳ���;

		 at02dpktHead.len   =  GetBigtoLittle32(nHeadLen);

		 //����֡ͷ��
		 memcpy(pDataAt02D + m_nIndexAt02d,   &at02dpktHead ,  sizeof( SST_AT02_PKT_HEAD));  

		 m_nIndexAt02d +=  sizeof(SST_AT02_PKT_HEAD);

		 //�������ݣ�
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
		 m_nIndexAt02d   +=   nHeadLen *  4  +  4  -  sizeof(SST_AT02_PKT_HEAD);   //����ӵ����4��˼��0x05640564;

		 //����4������������0��
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

		 //��ȡ�������ݣ�
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
//Ĭ������ȡPCAP���ģ�ֱ�Ӱ�IP����ȫ����ȥ����Ϊ�˷�ֹ9-2/GOOSE�л����������ģ����´��������ȹ���һ�飻
BOOL CPcapToAt02d::FilterTCPIPData(const CString & strPcapFile)
{
	pcap_t* fp;
	char errbuf[PCAP_ERRBUF_SIZE];
	//��Pcap��

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

	//��ȡ�ļ�ֱ����β
	struct pcap_pkthdr* header;		//����ͷ
	const unsigned char* pkt_data;	//��������
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
		//ƫ��14���ֽڣ�����̫��ͷ������2���ֽ���IPͷ��
		iph = (IP_HEADER*)(pkt_data + 14); //length of ethernet header  
		
		if (iph->proto == 6)
		{
			continue;
		}
	
		// ��ȡIP���ĳ���
		iph_len = (iph->ver_ihl & 0x0f) * 4;//����ĳ�����ͷ�ĳ��ȣ���4�ı�����Ҳ����DWORD��������
		u_char *ip_data = (u_char*)iph;
		tcph = (TCP_HEADER*) (ip_data + iph_len);//����������ƫ���� IP����ͷ�ĳ��ȣ�֮�����TCP���ĵ�ͷ��Ҳ��20���ֽڡ�

		//��������Ƕ˿ڣ�ʹ�õ�ʱ��Ҫ������ã�����ע���� 19814 ��AT02�Ķ˿ڣ�
		if (tcph->sport != 0xf707)//19814
		{
			//����AT02���������ı���
			//continue;
		}

		tcph_len = ((tcph->th_lenres & 0xf0) >> 4) * 4;//4λ�ײ����ȣ���DWORD��������Ҳ����Ҫ����4 ����ֽ�����
		long nDataLen = ntohs(iph->tlen) - tcph_len - iph_len;// - 14ether_header; //����ͷ��IP���� ��ȥ tcpͷ���ȣ��ټ�ȥIPͷ���ȣ��������ݵĳ��ȣ�

		ip_data = (u_char*)tcph;
		ip_data = ip_data + tcph_len;// ƫ��TCPͷ�ĳ��ȣ��������TCP�������ˣ�
		*/
		//fwrite(ip_data, nDataLen, 1, pfile);
		int nDataLen = header->caplen;
		//��һ֡Ҫд���ļ�ͷ��
		if (nPacket==0)
			fwrite(byHead, 24, 1, pfile);
		fwrite(header, 16, 1, pfile);
		fwrite(pkt_data, nDataLen, 1, pfile);
		nPacket++;
	}

	pcap_close(fp);
	fclose(pfile);
	return TRUE;
	//MessageBox("��ȡ���");
}
