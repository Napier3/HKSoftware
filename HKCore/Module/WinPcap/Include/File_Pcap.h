//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CFile_Pcap.h  xujinqiang20200628add，pcap文件类

#pragma once

#include "..\..\SmartCap\XSmartCapMngr.h"
#include "..\..\SmartCap\61850Cap\CapGlobalDef.h"

#define PERPAGE_MAX_LEN 10485760 //每次读取的数据大小

//Pcap文件类
class CFile_Pcap
{
public:
	CFile_Pcap();
	~CFile_Pcap();

	//打开
	FILE *PcapOpenFile(const CString &strFile); 

	//写入
	void PcapWriteFrame(CXSmMemBuffer *pCapBuffer); //写一帧at02报文

	void PcapWriteFile(CSttFrameMemBufferMngr *pSttFrameMemBufferMngr); //写所有at02报文

	//关闭
	void PcapCloseFile();

private:
	FILE *m_pFile;
};
