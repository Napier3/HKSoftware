//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CFile_Pcap.h  xujinqiang20200628add��pcap�ļ���

#pragma once

#include "..\..\SmartCap\XSmartCapMngr.h"
#include "..\..\SmartCap\61850Cap\CapGlobalDef.h"

#define PERPAGE_MAX_LEN 10485760 //ÿ�ζ�ȡ�����ݴ�С

//Pcap�ļ���
class CFile_Pcap
{
public:
	CFile_Pcap();
	~CFile_Pcap();

	//��
	FILE *PcapOpenFile(const CString &strFile); 

	//д��
	void PcapWriteFrame(CXSmMemBuffer *pCapBuffer); //дһ֡at02����

	void PcapWriteFile(CSttFrameMemBufferMngr *pSttFrameMemBufferMngr); //д����at02����

	//�ر�
	void PcapCloseFile();

private:
	FILE *m_pFile;
};
