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
	static long g_nIsFT3PcapFile;//标记当前存储的pcap文件是否为FT3格式
	
//	static CString g_strPcapFilePath;//20231012 wxy 外部获取文件路径名称
	
public:
	static void Create();
	static void Release();
	static BOOL HasRelease();//判断当前是否已释放
	static BOOL WriteBuffer(char *pBuffer, long nLen);
	static long GetWriteLen();
	static BOOL StopWrite(const CString &strPcapFilePath);
	static CString GetWriteFilePath();
	static BOOL HasCloseFile();
//	static CString GetPcapFilePath();//20231012 wxy 外部获取文件路径名称

	BOOL SavePcapFile(const CString &strPcapFilePath = _T(""));//将At02d文件另存为PCAP文件
};
