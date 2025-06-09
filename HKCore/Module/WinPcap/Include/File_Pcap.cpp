//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CFile_Pcap.cpp 


#include "stdafx.h"
#include "File_Pcap.h"

CFile_Pcap::CFile_Pcap()
{
	m_pFile = NULL;
}

CFile_Pcap::~CFile_Pcap()
{

}

FILE *CFile_Pcap::PcapOpenFile(const CString &strFile)
{
	m_pFile = fopen(strFile, "w+b");

	if (m_pFile == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("���ļ�%sʧ��"), strFile);
		return NULL;
	}

	//д�ļ�ͷ
	_file_header header;
	header.iMagic = 0xA1B23C4D;
	header.iMaVersion = 0x02;
	header.iMiVersion = 0x04;
	header.iTimezone = 0x00;
	header.iSigFlags = 0x00;
	header.iSnapLen = 0x40000;
	header.iLinkType = 0x01;

	char *pData = (char*)&header;
	fwrite(pData, sizeof(_file_header), 1, m_pFile);

	return m_pFile;
}

void CFile_Pcap::PcapWriteFrame(CXSmMemBuffer *pCapBuffer)
{
	if (m_pFile == NULL || pCapBuffer == NULL)
	{
		return;
	}

	__int64 n64TimeSnamp = pCapBuffer->m_n64TimeSnamp;  //H32=s   L32=ns
	long n32TimeSnampHigh = (n64TimeSnamp>>32);
	long n32TimeSnampLow = (n64TimeSnamp & 0xffffffff);

	_pkthdr pkthdr;
	pkthdr.iPLength = pCapBuffer->GetBufferLength();
	pkthdr.iLength = pCapBuffer->GetBufferLength();
	pkthdr.iTimeSecond = n32TimeSnampHigh;
	pkthdr.iTimeSS = n32TimeSnampLow;

	char *pData = (char*)&pkthdr;
	fwrite(pData, sizeof(_pkthdr), 1, m_pFile); //дpcap֡ͷ

	fwrite(pCapBuffer->GetBuffer(), pCapBuffer->GetBufferLength(), 1, m_pFile); //дat02d����
}

void CFile_Pcap::PcapWriteFile(CSttFrameMemBufferMngr *pSttFrameMemBufferMngr)
{
	if (m_pFile == NULL || pSttFrameMemBufferMngr == NULL)
	{
		return;
	}

	CXSmMemBuffer *pCapBuffer = NULL;

	long nBegin1 = -1, nEnd1 = -1, nBegin2 = -1, nEnd2 = -1;
	pSttFrameMemBufferMngr->GetLastParseIndexRange(nBegin1, nEnd1, nBegin2, nEnd2);

	if(nEnd1 < 0)
	{
		return;
	}

	for (long nIndex=nBegin1; nIndex <= nEnd1; nIndex++)
	{
		pCapBuffer = pSttFrameMemBufferMngr->GetFrameBuffer(nIndex); //��������ÿһ֡at02�������ݣ�����������ͷ��
		PcapWriteFrame(pCapBuffer);
	}

	if(nEnd2 < 0)
	{
		return;
	}

	for (long nIndex=nBegin2; nIndex <= nEnd2; nIndex++)
	{
		pCapBuffer = pSttFrameMemBufferMngr->GetFrameBuffer(nIndex); //��������ÿһ֡at02�������ݣ�����������ͷ��
		PcapWriteFrame(pCapBuffer);
	}
}

void CFile_Pcap::PcapCloseFile()
{
	if(m_pFile != NULL)
	{
		fclose(m_pFile);
	}
}
