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
*�����ļ����ư���·�����������������ж�ȡ��Ȼ����ļ���������
********************************************************************************************************************/
BOOL CAt02dToPcap::OpenPcapFile(const CString &strFilePath)
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

//#define WRITEPCAPTOATO2DFILE

BOOL CAt02dToPcap::ReadPcapFile()
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
	nLen  = m_oPcapFile.Read(m_byBufferIN + m_nLeftBuffer, MAX_AT02DTOPCAP_CAP_BUFFER_IN );
	m_nBufferLen   =  nLen ;

	//�����¼ÿ�ζ�ȡ�ĳ���, Ȼ�󲻶ϵ��ۼ�, ֱ�������ļ��ĳ���Ϊֹ��
	m_nParseLen  +=  nLen;

	//��֮ǰʣ��֡��������ߣ������������Ҫ���ϣ�
	if (m_nCopyFlag==2)
		nLen += m_nLeftBuffer;
	
	//long  nLenAt02d  = 0; 
	long nPacketCnt  = 0;
	::memset(m_byBufferOut, 0x0, MAX_AT02DTOPCAP_CAP_BUFFER_OUT);
	m_nAt02dLen = 0;

	//����������PCAP���ģ�����������AT02D���ģ�
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

//��������������ת����ÿ������204800���ֽڽ�ȥת�������ܻ���ʣ���ֽڣ�Ҳ���ǰ�֡��������ڣ�Ҫ���š�Ȼ���룻
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

	// ����֡������
	m_nIndexPacket  = 0;
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
		at02dpktHead.nIndex         =    GetBigtoLittle32Ex(m_nIndexPacket);
		at02dpktHead.packet_len  =    GetBigtoLittle16Ex(pkthdr.iPLength) ;            //61850���ĵĳ���	
		at02dpktHead.utc_s           =    GetBigtoLittle32Ex(pkthdr.iTimeSecond);
		at02dpktHead.utc_ns         =    GetBigtoLittle32Ex(pkthdr.iTimeSS);
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

		at02dpktHead.len   =  GetBigtoLittle32Ex(nHeadLen);

		//����֡ͷ��
		memcpy(pDataAt02D + m_nIndexAt02d,   &at02dpktHead ,  sizeof( SST_AT02_PKT_HEAD));  

		m_nIndexAt02d +=  sizeof(SST_AT02_PKT_HEAD);

		//�������ݣ�
		memcpy(pDataAt02D + m_nIndexAt02d,  pBuffer + nIndex,  pkthdr.iPLength);  

		m_nIndexAt02d   +=   nHeadLen *  4  +  4;   //����ӵ����4��˼��0x05640564;

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
	 at02dpktHead.packet_len  =    GetBigtoLittle16Ex(pkthdr.iPLength) ;            //61850���ĵĳ���	
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

	 m_nIndexAt02d   +=   nHeadLen *  4  +  4;       //����ӵ����4��˼��0x05640564;

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


//Ĭ������ȡPCAP���ģ�ֱ�Ӱ�IP����ȫ����ȥ����Ϊ�˷�ֹ9-2/GOOSE�л����������ģ����´��������ȹ���һ�飻
BOOL CAt02dToPcap::FilterTCPIPData(const CString & strPcapFile)
{
	return TRUE;
}
