#include "StdAfx.h"

#include "At02dToPcap.h"

CAt02dToPcap::CAt02dToPcap()
{
	m_nIndexPacket = 0;
	m_nIndexAt02d = 0;
	m_bReadFinished = FALSE;
	m_nBufferLen = 204800;
	::memset(m_byBufferIN, 0x0, MAX_AT02DTOPCAP_CAP_BUFFER_IN + 2000);
	::memset(m_byBufferOut, 0x0, MAX_AT02DTOPCAP_CAP_BUFFER_OUT);
	m_nLeftBuffer = 0;
	m_nIndexLastPacket = 0;
	m_nLastPacketLen = 0;
	m_nCopyFlag = 0;
	m_nParseLen = 0;
	m_nAt02dLen = 0;
	m_nFirstEnterFile = 0;
	m_bPcapFile = FALSE;
}

CAt02dToPcap::~CAt02dToPcap()
{

}

/*******************************************************************************************************************
*设置文件名称包括路径过来，在这个类进行读取，然后对文件进行整理；
********************************************************************************************************************/
BOOL CAt02dToPcap::OpenPcapFile(const CString &strFilePath)
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

//#define WRITEPCAPTOATO2DFILE

BOOL CAt02dToPcap::ReadPcapFile()
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
	nLen  = m_oPcapFile.Read(m_byBufferIN + m_nLeftBuffer, MAX_AT02DTOPCAP_CAP_BUFFER_IN );
	m_nBufferLen   =  nLen ;

	//这里记录每次读取的长度, 然后不断的累加, 直道等于文件的长度为止；
	m_nParseLen  +=  nLen;

	//把之前剩下帧拷贝到里边，所以这个长度要加上；
	if (m_nCopyFlag==2)
		nLen += m_nLeftBuffer;
	
	//long  nLenAt02d  = 0; 
	long nPacketCnt  = 0;
	::memset(m_byBufferOut, 0x0, MAX_AT02DTOPCAP_CAP_BUFFER_OUT);
	m_nAt02dLen = 0;

	//这里送入是PCAP报文，导出来的是AT02D报文；
	CreateAt02dData(m_byBufferIN,    nLen,   m_byBufferOut,   m_nAt02dLen,   nPacketCnt );

#ifdef WRITEPCAPTOATO2DFILE
	CString strPath = "D:\\Program Files\\EPOTO\\e-Monitor\\Library\\mym.at02d";
	FILE* pwFile = fopen( strPath, "wb");  
	fwrite( (void*)(m_byBufferIN),  1, nLen,  pwFile);  
	fclose( pwFile);  
#endif

	if (nLen == 0)
	{
		m_bReadFinished = TRUE;
		return FALSE;
	}

	return TRUE;
}

//在这个函数里进行转化，每次填入204800个字节进去转化，可能会有剩余字节，也就是半帧的情况存在，要攒着。然后倒入；
void CAt02dToPcap::CreateAt02dData(BYTE * pBuffer,   long nLength,  BYTE *pDataAt02D,  long & nLenAt02d,  long &nPacketCnt)
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
	m_nIndexPacket  = 0;
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
		at02dpktHead.nIndex         =    GetBigtoLittle32Ex(m_nIndexPacket);
		at02dpktHead.packet_len  =    GetBigtoLittle16Ex(pkthdr.iPLength) ;            //61850报文的长度	
		at02dpktHead.utc_s           =    GetBigtoLittle32Ex(pkthdr.iTimeSecond);
		at02dpktHead.utc_ns         =    GetBigtoLittle32Ex(pkthdr.iTimeSS);
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

		at02dpktHead.len   =  GetBigtoLittle32Ex(nHeadLen);

		//拷贝帧头；
		memcpy(pDataAt02D + m_nIndexAt02d,   &at02dpktHead ,  sizeof( SST_AT02_PKT_HEAD));  

		m_nIndexAt02d +=  sizeof(SST_AT02_PKT_HEAD);

		//拷贝数据；
		memcpy(pDataAt02D + m_nIndexAt02d,  pBuffer + nIndex,  pkthdr.iPLength);  

		m_nIndexAt02d   +=   nHeadLen *  4  +  4;   //后面加的这个4意思是0x05640564;

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
 void CAt02dToPcap::GetAt02dData( BYTE *pDataAt02D,  long & nLenAt02d, BYTE * pPcapBuffer,   long nPcapLength,  long &nPacketCnt)
 {
	 SST_AT02_PKT_HEAD  at02dpktHead,  at02dpktHeadTemp;
	 _file_header fileHeader;
	 _pkthdr pkthdr;

	 at02dpktHead.hd_flag = 0x64056405;
	 at02dpktHead.filber_smv_gs = 0;
	 at02dpktHead.appid = 0;
	 at02dpktHead.crc = 0;
	 at02dpktHead.nIndex         =    GetBigtoLittle32Ex(m_nIndexPacket);
	 at02dpktHead.packet_len  =    GetBigtoLittle16Ex(pkthdr.iPLength) ;            //61850报文的长度	
	 at02dpktHead.utc_s           =    GetBigtoLittle32Ex(pkthdr.iTimeSecond);
	 at02dpktHead.utc_ns         =    GetBigtoLittle32Ex(pkthdr.iTimeSS);
	 int nHeadLen =  0;

	 at02dpktHead.len   =  GetBigtoLittle32Ex(nHeadLen);

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

	 m_nIndexAt02d   +=   nHeadLen *  4  +  4;       //后面加的这个4意思是0x05640564;

 }


 void CAt02dToPcap:: ClosePcapFile()
 {
	 if (m_bPcapFile)
	{
		m_oPcapFile.Close();
		m_bPcapFile = FALSE;
	}
 }

void CAt02dToPcap::ResetMember()
{
//	return;
	m_nIndexPacket = 0;
	m_nIndexAt02d = 0;
	m_bReadFinished = FALSE;
	m_nBufferLen = 204800;
	::memset(m_byBufferIN, 0x0, MAX_AT02DTOPCAP_CAP_BUFFER_IN + 2000);
	::memset(m_byBufferOut, 0x0, MAX_AT02DTOPCAP_CAP_BUFFER_OUT);
	m_nLeftBuffer = 0;
	m_nIndexLastPacket = 0;
	m_nLastPacketLen = 0;
	m_nCopyFlag = 0;
	m_nParseLen = 0;
	m_nAt02dLen = 0;
	m_nFirstEnterFile = 0;
	//m_bPcapFile = FALSE;
}


//默认是提取PCAP报文，直接把IP报文全部舍去，是为了防止9-2/GOOSE中混有其他报文，导致错误；所以先过滤一遍；
BOOL CAt02dToPcap::FilterTCPIPData(const CString & strPcapFile)
{
	return TRUE;
}
