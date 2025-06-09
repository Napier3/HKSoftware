#pragma once

#include "../SmDb/XSmMemBufferMngr.h"
#include "61850Cap/CapGlobalDef.h"
#include "61850Cap/ProtocolBase/Stt/SttFrameMemBufferMngr.h"

#define RCD_PARSE_BUFFER_MAX_LEN   81920
#define RCD_LEFT_BUFFER_MAX_LEN     4096

//2022-4-6  lijunqing
//报文转换接口，例如将AT02D报文转换为纯数字报文
//对于数字化录波，有各种不同的情况，各种情况都必须将协议报文转换为数字化报文
class CXCapPkgBufferMngrInterface
{
public:
	virtual CXSmMemBuffer* AddFrameBuffer(const BYTE *pBuffer, long nLen) = 0;
	virtual void TransCapPkg() = 0;
	virtual void Release() = 0;
	virtual CXSmMemBufferMngr* GetXSmMemBufferMngr() = 0;
	virtual void ReadHexTestFile(const CString &strFile) = 0;
	virtual void AttachPkgTransDest(CXSmMemBufferMngr *pDestBuffer) = 0;

	virtual void ResetBuffer() = 0;  //2022-4-20  lijunqing
	virtual void LogBufferPos(){}   //2022-4-21  lijunqing 监视缓冲区位置：填充位置和解析位置

public:
	CXCapPkgBufferMngrInterface()
	{
		m_oPkgHeadStcMngr.init();
		m_pSttRcdBuffer[0]  = 0;
		m_pLeftBuffer[0]  = 0;
		m_nLeftBufferLen = 0;
		m_pRefSttFrameBufMngr = NULL;
	}
	virtual ~CXCapPkgBufferMngrInterface()
	{

	}

protected:
	//用于记录一批缓冲区中，存在不完整的报文，后续的报文在下面一批缓冲区中
	//这种可能性很低，但是先把这部分设计留着，如果存在则后续实现
	BYTE m_pSttRcdBuffer[RCD_PARSE_BUFFER_MAX_LEN+10];
	BYTE m_pLeftBuffer[RCD_LEFT_BUFFER_MAX_LEN];
	long m_nLeftBufferLen;

	long m_nFrameCount;
	SST_AT02_PKT_HEAD m_oPrevHead ;
	__int64 m_n64PrevTime;
	CSttFrameMemBufferMngr *m_pRefSttFrameBufMngr;

protected:
	void ParseSttRcdBufferEx(long nBufLen);
	void ParseSttRcdBuffer(BYTE *pBuffer, long nLenCopyLeft);

//2022-6-19  lijunqing
// 很容易出现丢包的情况，为了排除是因为应用程序消耗资源比较大的情况，只做
// AT02D报文头分析。
protected:
	STT_AT02_PKT_HEAD_STC_MNGR m_oPkgHeadStcMngr;
	static long g_nXSmartCapDebugHead;

	PSTT_AT02_PKT_HEAD_STC SttAddAppID(unsigned short nAppID);
	void SttAt02HadStc(SST_AT02_PKT_HEAD &oHead);
	void AnalysisSttAT02HeadBuffer(BYTE *pBuffer, long nLenBuffer);

public:
	PSTT_AT02_PKT_HEAD_STC_MNGR GetPkgHeadStcMngr()	{	return &m_oPkgHeadStcMngr;		}
	static void XSmartCapDebugHead();
	static BOOL Is_XSmartCapDebugHead();
};

void xsmartcap_ReadHead(PEPBUFFERPOS pBufferPos, SST_AT02_PKT_HEAD &oHead);
