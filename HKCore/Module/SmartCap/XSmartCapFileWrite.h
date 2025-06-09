#pragma once

#include "../SmDb/XSmMemBufferMngr.h"
#include "61850Cap/CapGlobalDef.h"
#include "61850Cap/ProtocolBase/Stt/SttFrameMemBufferMngr.h"


//2022-6-13  lijunqing
class CXSmartCapFileWrite
{
private:
	CXSmartCapFileWrite();
	virtual ~CXSmartCapFileWrite();

	static CXSmartCapFileWrite *g_pXSmartCapFileWrite;
	static long g_nXSmartCapFileWriteRef;
	
	CFile m_oFile;
	BOOL m_bOpenSucc;
	CString m_strWriteFilePath;
	static long g_nWriteLength;
	static long g_nCanWriteFile;
	static long g_nIsFT3PcapFile;//��ǵ�ǰ�洢��pcap�ļ��Ƿ�ΪFT3��ʽ
	
//	static CString g_strPcapFilePath;//20231012 wxy �ⲿ��ȡ�ļ�·������
	
public:
	static void Create();
	static void Release();
	static BOOL HasRelease();//�жϵ�ǰ�Ƿ����ͷ�
	static BOOL WriteBuffer(char *pBuffer, long nLen);
	static long GetWriteLen();
	static BOOL StopWrite(const CString &strPcapFilePath);
	static CString GetWriteFilePath();
	static BOOL HasCloseFile();
//	static CString GetPcapFilePath();//20231012 wxy �ⲿ��ȡ�ļ�·������

	BOOL SavePcapFile(const CString &strPcapFilePath = _T(""));//��At02d�ļ����ΪPCAP�ļ�
};
