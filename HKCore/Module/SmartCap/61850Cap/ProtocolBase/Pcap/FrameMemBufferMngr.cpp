#include "StdAfx.h"
#include "FrameMemBufferMngr.h"
#include "../../../../WinPcap/Include/pcap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CFrameMemBufferMngr::CFrameMemBufferMngr(void)
{
	
}

CFrameMemBufferMngr::~CFrameMemBufferMngr(void)
{
	Free();
}

CFrameMemBuffer* CFrameMemBufferMngr::AddFrameBuffer(const struct pcap_pkthdr *header, const BYTE *pBuffer)
{
	__int64 n64Time = header->ts.tv_sec;
	n64Time = n64Time << 32;
	n64Time += header->ts.tv_usec ;

	double dTimeSnamp = header->ts.tv_sec + 1E-6 * header->ts.tv_usec;

	if (m_nCurrIndex == 0/*m_oBeginTime.dTime == 0*/)//2023.7.17 zhouhj 
	{
		m_oBeginTime.dTime = dTimeSnamp;
	}

	m_n64CapIndex++;
	CFrameMemBuffer *pFrameBuffer = (CFrameMemBuffer*)GetFrameBuffer(m_nCurrIndex);
	
	if (pFrameBuffer == NULL)
	{
		pFrameBuffer =(CFrameMemBuffer*)NewMemBuffer();
		m_pdwXSmMemBuffer[m_nCurrIndex] = (DWORD)pFrameBuffer;
	}

#ifdef FrameMemBuffer_use_pkthdr
	pFrameBuffer->m_oPcapHeader = *header;
#endif

	long nLen = header->caplen;

#ifdef FrameMemBuffer_use_FrameID
	pFrameBuffer->m_n64FrameID = m_n64CapIndex;
#endif
	pFrameBuffer->SetBufferLength(nLen);//+4);
	pFrameBuffer->CopyBuffer((BYTE*)pBuffer, nLen, 0);
	pFrameBuffer->m_oCapBufferItem.Time = n64Time/*n64Time*/;
//	pFrameBuffer->m_oCapBufferItem.usec = header->ts.tv_usec;////zhouhj 2023.7.23 增加报文时间戳中us记录
	m_nCurrIndex++;

	if (m_nCurrIndex >= m_nMaxCount)
	{
		m_nCurrIndex = 0;
	}

	m_nCurrCount++;
	if (m_nCurrCount >= m_nMaxCount)
	{
		m_nCurrCount = m_nMaxCount;
	}

	return pFrameBuffer;
}
