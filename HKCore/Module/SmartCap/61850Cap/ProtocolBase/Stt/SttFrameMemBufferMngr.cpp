#include "stdafx.h"
#include "SttFrameMemBufferMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrameMemBufferMngr::CSttFrameMemBufferMngr(void)
{
	//lijunqing 2020-6-17
	//一次性分配32M内存空间  16M=16777216  32M=33554432
	SetBufferLength(33554432);
}

CSttFrameMemBufferMngr::~CSttFrameMemBufferMngr(void)
{
	Free();
}
#include <math.h>

//pBuffer包含了SST_AT02_PKT_HEAD
CFrameMemBuffer* CSttFrameMemBufferMngr::AddFrameBuffer(const SST_AT02_PKT_HEAD *header, const BYTE *pBuffer)
{
	__int64 n64Time = header->utc_s;
	n64Time = n64Time << 32;
	n64Time += header->utc_ns ;

	if (m_oBeginTime.n64Time == 0)
	{
		m_oBeginTime.stt_utc.utc_s = header->utc_s;
		m_oBeginTime.stt_utc.utc_ns = header->utc_ns;
	}

	// mym add 加这个是为了测试看看时间传递过来的值是多少，
// 	BYTE byTime[8];
// 	::memset(byTime,  0x0, 8);
// 	::memcpy(byTime,  &n64Time,   8);
// 	BYTE t4 =  byTime[0];	
// 	BYTE t3 =  byTime[1];
// 	BYTE t2 =  byTime[2];
// 	BYTE t1 =  byTime[3];
// 	BYTE t8 =  byTime[4];	
// 	BYTE t7=  byTime[5];
// 	BYTE t6 =  byTime[6];
// 	BYTE t5 =  byTime[7];
// 	double Time1      =   t4  +  t3  *  pow(2.0,  8)  +  t2  *  pow(2.0,  16)  +  t1  *  pow(2.0,  24);
// 	double usTime1  =   t8   +  t7 *  pow(2.0,   8)  +   t6   *   pow(2.0,   16)  +  t5  *  pow(2.0,  24);
// 	CTime time = (CTime)(int)Time1;
// 	CString strTime = time.Format("%Y-%m-%d %H:%M:%S");

	m_n64CapIndex++;
	CFrameMemBuffer *pFrameBuffer = (CFrameMemBuffer*)GetFrameBuffer(m_nCurrIndex);
	
	if (pFrameBuffer == NULL)
	{
		pFrameBuffer =(CFrameMemBuffer*)NewMemBuffer();
		m_pdwXSmMemBuffer[m_nCurrIndex] = (DWORD)pFrameBuffer;
	}

	long nLen = header->packet_len;
	pFrameBuffer->m_n64FrameID = m_n64CapIndex;

	//2020-6-17  lijunqing 
	if (m_pBuffer != NULL)
	{
		pFrameBuffer->AttachBuffer(AllocBuffer(nLen), nLen);
	}
	else
	{
		pFrameBuffer->SetBufferLength(nLen);
	}

	pFrameBuffer->CopyBuffer((BYTE*)pBuffer, nLen, 0);
	pFrameBuffer->m_oCapBufferItem.Time = n64Time;
	pFrameBuffer->m_n64TimeSnamp = n64Time;
	pFrameBuffer->m_nFiberAndPkgType = header->filber_smv_gs;

	//zhouhj 2024.3.27 如果是合并单元时间数据类型,则将存储对应软件资源类型及序号存入整型高2位
	int nPkgType = (pFrameBuffer->m_nFiberAndPkgType&0xFF)/0x10;

	if (nPkgType == Protocol61850_Pkg_Type_MUTIMEDATA)
	{
		int nChData = header->crc<<16;
		int nPkgType = pFrameBuffer->m_nFiberAndPkgType&0xFF;
		pFrameBuffer->m_nFiberAndPkgType = nPkgType + nChData;
	}

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

CFrameMemBuffer* CSttFrameMemBufferMngr::AddFrameBuffer(const BYTE *pBuffer, long nLength)
{
	m_n64CapIndex++;
	CFrameMemBuffer *pFrameBuffer = (CFrameMemBuffer*)GetFrameBuffer(m_nCurrIndex);

	if (pFrameBuffer == NULL)
	{
		pFrameBuffer =(CFrameMemBuffer*)NewMemBuffer();
		m_pdwXSmMemBuffer[m_nCurrIndex] = (DWORD)pFrameBuffer;
	}

	pFrameBuffer->m_n64FrameID = m_n64CapIndex;

	//2020-6-17  lijunqing 
	if (m_pBuffer != NULL)
	{
		pFrameBuffer->AttachBuffer(AllocBuffer(nLength), nLength);
	}
	else
	{
		pFrameBuffer->SetBufferLength(nLength);
	}

	pFrameBuffer->CopyBuffer((BYTE*)pBuffer, nLength, 0);
	pFrameBuffer->m_oCapBufferItem.Time = 0;
	pFrameBuffer->m_n64TimeSnamp = 0;
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

