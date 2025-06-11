#include "StdAfx.h"
#include "SttLocalRcdMemBufferMngrLinux.h"
#include "../../../../Module/SmartCap/61850Cap/ProtocolBase/61850ParseFrameList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "../../../../Module/SmartCap/XSmartCapFileWrite.h"

//////////////////////////////////////////////////////////////////////////
//CSttLocalRcdMemBufferMngrLinux
CSttLocalRcdMemBufferMngrLinux::CSttLocalRcdMemBufferMngrLinux(void)
{
	m_nSttRcdBufferPos = 0;
	m_nReadPos = 0;
	m_pRingMemBufShm = NULL;
	m_pRefSttFrameBufMngr = NULL;
	m_oPkgHeadStcMngr.init();
}

CSttLocalRcdMemBufferMngrLinux::~CSttLocalRcdMemBufferMngrLinux(void)
{
	
}


CXSmMemBuffer* CSttLocalRcdMemBufferMngrLinux::AddFrameBuffer(const BYTE *pBuffer, long nLen)
{
	return NULL;
}

void CSttLocalRcdMemBufferMngrLinux::TransCapPkg_DebugHead()
{
	//缓冲区最多有  RCD_PARSE_BUFFER_MAX_LEN   81920  报文
	long nReadLen = 60 * sizeof(SST_AT02_PKT_HEAD);

	while (true)
	{
		long nTotalLen = m_pRingMemBufShm->ReadBuf((char*)m_pRingMemBufRead, m_nReadPos, nReadLen, nReadLen);

		if (nTotalLen == 0)
		{
			return;
		}

//		CXSmartCapFileWrite::WriteBuffer((char*)m_pRingMemBufRead, nTotalLen); //20220620 zhouhj 报文头模式 不再写文件
		CXCapPkgBufferMngrInterface::AnalysisSttAT02HeadBuffer(m_pRingMemBufRead, nTotalLen);
	}
}

//从m_pRingMemBufShm中提取一个个的61850报文，添加到m_pRefSttFrameBufMngr中
void CSttLocalRcdMemBufferMngrLinux::TransCapPkg()
{
	if (m_pRingMemBufShm == NULL)
	{
		return;
	}

	if (CXCapPkgBufferMngrInterface::Is_XSmartCapDebugHead())
	{//2022-6-19  lijunqing  调试报文头的模式
		return TransCapPkg_DebugHead();
	}

	//缓冲区最多有  RCD_PARSE_BUFFER_MAX_LEN   81920  报文
	long nReadLen = CAPPKG_READ_LEN_ONCE;

	while (true)
	{
		long nTotalLen = m_pRingMemBufShm->ReadBuf((char*)m_pRingMemBufRead, m_nReadPos, nReadLen, nReadLen);

		if (nTotalLen == 0)
		{
			return;
		}

		//2022-6-13  lijunqing   如果是写文件，则不再做任何处理
		if (CXSmartCapFileWrite::WriteBuffer((char*)m_pRingMemBufRead, nTotalLen))
		{
			continue;
		}

		CXCapPkgBufferMngrInterface::ParseSttRcdBuffer(m_pRingMemBufRead, nTotalLen);
	}
}

void CSttLocalRcdMemBufferMngrLinux::Release()
{
	delete this;
}

CXSmMemBufferMngr* CSttLocalRcdMemBufferMngrLinux::GetXSmMemBufferMngr()
{
	return NULL;
}

void CSttLocalRcdMemBufferMngrLinux::ReadHexTestFile(const CString &strFile)
{

}

void CSttLocalRcdMemBufferMngrLinux::AttachPkgTransDest(CXSmMemBufferMngr *pDestBuffer)
{
	m_pRefSttFrameBufMngr = (CSttFrameMemBufferMngr*)pDestBuffer;
}

void CSttLocalRcdMemBufferMngrLinux::SetRingMemBuf(CRingMemBuf *pRingMemBuf)
{
	m_pRingMemBufShm = pRingMemBuf;
}

void CSttLocalRcdMemBufferMngrLinux::ResetBuffer()
{
	//从当前写的位置开始读取
    m_nReadPos = m_pRingMemBufShm->GetWritePos();
	m_oPkgHeadStcMngr.init();
}

//2022-4-21  lijunqing 监视缓冲区位置：填充位置和解析位置
void CSttLocalRcdMemBufferMngrLinux::LogBufferPos()
{
	long nReadPos = m_nReadPos;
	long nWritePos = m_pRingMemBufShm->GetWritePos();
	long nDataLen = m_pRingMemBufShm->GetDataLen();
	long nCalLen = 0;
	float fRate = 0.0f;

	if (nWritePos < nReadPos)
	{
		nCalLen = nDataLen - nReadPos;
		nCalLen += nWritePos;
	}
	else
	{
		nCalLen = nWritePos - nReadPos;
	}

	fRate = ((float)nCalLen)/((float)nDataLen);


	long nBegin1 = -1, nEnd1 = -1, nBegin2 = -1, nEnd2 = -1;
	m_pRefSttFrameBufMngr->GetParseIndexRange(nBegin1, nEnd1, nBegin2, nEnd2);

	long nNeedParseCount = 0;

	if (nEnd1 > nBegin1)
	{
		nNeedParseCount += nEnd1 - nBegin1;
	}

	if (nEnd2 > 0)
	{
		nNeedParseCount += nEnd2 - nBegin2;
	}

	if ((nCalLen>0)||(nNeedParseCount > 0))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("WritePos[%d] ReadPos[%d] rate[%.3f] CalLen=[%d]  nNdCnt=%d")
			/*, nDataLen*/, nWritePos, nReadPos,fRate, nCalLen,/*nBegin1 ,nEnd1,nBegin2,nEnd2,*/ nNeedParseCount);
	}
}

 