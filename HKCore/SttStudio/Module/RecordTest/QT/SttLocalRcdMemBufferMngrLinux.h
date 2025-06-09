#pragma once

#include "../RingMemBuf.h"
#include "../../../../Module/SmartCap/XSmartCapInterface.h"
#include "../../../../Module/SmartCap/61850Cap/ProtocolBase/Stt/SttFrameMemBufferMngr.h"

//RCD_PARSE_BUFFER_MAX_LEN(81920) - 10240
#define CAPPKG_READ_LEN_ONCE   71680

class CSttLocalRcdMemBufferMngrLinux : public CXCapPkgBufferMngrInterface
{
public://CXCapPkgTransInterface
	virtual CXSmMemBuffer* AddFrameBuffer(const BYTE *pBuffer, long nLen);
	virtual void TransCapPkg();
	virtual void Release();
	virtual CXSmMemBufferMngr* GetXSmMemBufferMngr();
	virtual void ReadHexTestFile(const CString &strFile);
	virtual void AttachPkgTransDest(CXSmMemBufferMngr *pDestBuffer);
	virtual void ResetBuffer();  //2022-4-20  lijunqing

	void SetRingMemBuf(CRingMemBuf *pRingMemBuf);
	virtual void LogBufferPos();   //2022-4-21  lijunqing 监视缓冲区位置：填充位置和解析位置

protected:
	void TransCapPkg_DebugHead();

public:
	CSttLocalRcdMemBufferMngrLinux(void);
	virtual ~CSttLocalRcdMemBufferMngrLinux(void);
	
protected:
	CRingMemBuf *m_pRingMemBufShm;
	BYTE m_pRingMemBufRead[CAPPKG_READ_LEN_ONCE];

	long m_nReadPos;
	long m_nSttRcdBufferPos;
};

