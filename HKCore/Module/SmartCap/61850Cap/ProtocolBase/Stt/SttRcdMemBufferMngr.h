#pragma once

#include "../FrameMemBuffer.h"
#include "../../../../../Module/SmDb/XSmMemBufferMngr.h"
#include "../Stt/SttFrameMemBufferMngr.h"
#include "../../../XSmartCapInterface.h"

class CSttRcdMemBuffer : public CXSmMemBuffer
{
public:
	CSttRcdMemBuffer();
	virtual ~CSttRcdMemBuffer();

public:
	BOOL ReadHexTestFile(const CString &strFile);
};

class CSttRcdMemBufferMngr : public CXSmMemBufferMngr, public CXCapPkgBufferMngrInterface
{
public://CXCapPkgTransInterface
	virtual CXSmMemBuffer* AddFrameBuffer(const BYTE *pBuffer, long nLen);
	virtual void TransCapPkg();
	virtual void Release();
	virtual CXSmMemBufferMngr* GetXSmMemBufferMngr();
	virtual void ReadHexTestFile(const CString &strFile);
	virtual void AttachPkgTransDest(CXSmMemBufferMngr *pDestBuffer);
	virtual void ResetBuffer();  //2022-4-20  lijunqing
	virtual void LogBufferPos();

public:
	CSttRcdMemBufferMngr(void);
	virtual ~CSttRcdMemBufferMngr(void);

	//CSttRcdMemBuffer* AddFrameBuffer(const BYTE *pBuffer, long nLen);
	void ParseSttRcdBuffer();
	
	CSttFrameMemBufferMngr *GetFrameMemBufferMngr()	{	return m_pRefSttFrameBufMngr;	}	//yyj
	void ParseSttFrameBufferMngr();
	void ParseSttRcdBuffer(CSttRcdMemBuffer *pRcdBuffer);

	void ResetRcdMngr();

protected:
// 	CSttFrameMemBufferMngr *m_pRefSttFrameBufMngr;
// 	long m_nFrameCount;
// 	SST_AT02_PKT_HEAD m_oPrevHead ;
// 	__int64 m_n64PrevTime;
	

	BOOL ParseSttRcdBuffer(long nBegin, long nEnd);
	//void ParseSttRcdBufferEx(long nBufLen);

//	void ReadHead(PEPBUFFERPOS pBufferPos, SST_AT02_PKT_HEAD &oHead);
public:
	//void ReadHexTestFile(const CString &strFile);

	void ClearLeftBuffer(); //xujinqiang0718：清空m_pSttRcdBuffer、m_pLeftBuffer（仅仅导出pcap功能调用，独立的RcdBufferMngr）
};

