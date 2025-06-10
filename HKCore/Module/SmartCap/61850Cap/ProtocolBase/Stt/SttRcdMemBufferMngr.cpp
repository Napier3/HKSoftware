#include "stdafx.h"
#include "SttRcdMemBufferMngr.h"
#include "../61850ParseFrameList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CSttRcdMemBuffer
CSttRcdMemBuffer::CSttRcdMemBuffer()
{

}

CSttRcdMemBuffer::~CSttRcdMemBuffer()
{

}

BOOL CSttRcdMemBuffer::ReadHexTestFile(const CString &strFile)
{
	CFile oFile;
	BOOL b = oFile.Open(strFile, CFile::modeRead);

	if (!b)
	{
		return TRUE;
	}

	long nLen = oFile.GetLength();
	long nBufLen = nLen;
	SetBufferLength(nBufLen);
	BYTE *pBuffer = GetBuffer();
	BYTE pReadBuffer[1024];

	while (TRUE)
	{
		nLen = oFile.Read(pReadBuffer, 1024);

		if (nLen <= 0)
		{
			break;
		}

		pBuffer += HexToValue((char*)pReadBuffer, nLen, pBuffer, 0);
	}

	oFile.Close();

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//CSttRcdMemBufferMngr
CSttRcdMemBufferMngr::CSttRcdMemBufferMngr(void)
{
	//数字化AT02每200ms上报一次，每次最多200K的，所以设计最大10分钟的临时缓存
	SetMaxCount(3000);

	//lijunqing 2020-6-17
	//一次性分配16M内存空间  16M=16777216

#ifdef _PSX_QT_LINUX_
	SetBufferLength(16777216);
#else
	SetBufferLength(33554432);
#endif

	m_nFrameCount = 0;
	ZeroMemory(&m_oPrevHead, sizeof(m_oPrevHead));
}

CSttRcdMemBufferMngr::~CSttRcdMemBufferMngr(void)
{
	Free();
}


CXSmMemBuffer* CSttRcdMemBufferMngr::AddFrameBuffer(const BYTE *pBuffer, long nLen)
{
	m_n64CapIndex++;
	CSttRcdMemBuffer *pFrameBuffer = (CSttRcdMemBuffer*)GetFrameBuffer(m_nCurrIndex);

	if (pFrameBuffer == NULL)
	{
		pFrameBuffer =(CSttRcdMemBuffer*)NewMemBuffer();
		m_pdwXSmMemBuffer[m_nCurrIndex] = (DWORD)pFrameBuffer;
	}

	//lijunqing 2020-6-17
	if (m_pBuffer != NULL)
	{
		pFrameBuffer->AttachBuffer(AllocBuffer(nLen), nLen);
	}
	else
	{
		pFrameBuffer->SetBufferLength(nLen);//+4);
	}

	pFrameBuffer->CopyBuffer((BYTE*)pBuffer, nLen, 0);
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

void CSttRcdMemBufferMngr::TransCapPkg()
{
	ParseSttRcdBuffer();
}

void CSttRcdMemBufferMngr::Release()
{
	delete this;
}

CXSmMemBufferMngr* CSttRcdMemBufferMngr::GetXSmMemBufferMngr()
{
	return this;
}

void CSttRcdMemBufferMngr::ReadHexTestFile(const CString &strFile)
{
	CSttRcdMemBuffer *pNew = new CSttRcdMemBuffer();
	if (!pNew->ReadHexTestFile(strFile))
	{
		delete pNew;
	}

	AddFrameBuffer(pNew->GetBuffer(), pNew->GetBufferLength());
	delete pNew;

	ParseSttRcdBuffer();
}

void CSttRcdMemBufferMngr::AttachPkgTransDest(CXSmMemBufferMngr *pDestBuffer)
{
	m_pRefSttFrameBufMngr = (CSttFrameMemBufferMngr*)pDestBuffer;
}

void CSttRcdMemBufferMngr::ResetBuffer()
{

}

void CSttRcdMemBufferMngr::ResetRcdMngr()
{
	m_n64CapIndex = 0;
	m_nCurrIndex = 0;
	m_nCurrCount = 0;
}

void CSttRcdMemBufferMngr::ParseSttRcdBuffer()
{
	long nBegin1 = -1, nEnd1 = -1, nBegin2 = -1, nEnd2 = -1;
	GetParseIndexRange(nBegin1, nEnd1, nBegin2, nEnd2);

	if (nEnd1 >= nBegin1)
	{
		if (!ParseSttRcdBuffer(nBegin1, nEnd1))
		{
			return;
		}
	}

	if (nBegin2 >= 0)
	{
		ParseSttRcdBuffer(nBegin2, nEnd2);
	}

}

void CSttRcdMemBufferMngr::LogBufferPos()
{
// 	long nReadPos = m_nReadPos;
// 	long nWritePos = m_pRingMemBufShm->GetWritePos();
// 	long nDataLen = m_pRingMemBufShm->GetDataLen();
	long nCalLen = 0;
	float fRate = 0.0f;

// 	if (nWritePos < nReadPos)
// 	{
// 		nCalLen = nDataLen - nReadPos;
// 		nCalLen += nWritePos;
// 	}
// 	else
// 	{
// 		nCalLen = nWritePos - nReadPos;
// 	}
// 
// 	fRate = ((float)nCalLen)/((float)nDataLen);


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

	if (/*(nCalLen>0)||*/(nNeedParseCount > 200/*0*/))//zhouhj 20230701 最大解析200000帧,缓存在200帧以内,暂不打印
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(" nNdCnt=%d"),nNeedParseCount);
	}
}

BOOL CSttRcdMemBufferMngr::ParseSttRcdBuffer(long nBegin, long nEnd)
{
	if (nBegin < 0 || nEnd < 0)
	{
		return FALSE;
	}

	long nIndex = 0;
	CSttRcdMemBuffer *pRcdBuffer = NULL;

	for (nIndex=nBegin; nIndex<= nEnd; nIndex++)
	{
		pRcdBuffer = (CSttRcdMemBuffer*)GetFrameBuffer(nIndex);
		ParseSttRcdBuffer(pRcdBuffer);
		SetCurrParseIndex(nIndex+1);
	}

	return TRUE;
}

// void CSttRcdMemBufferMngr::ReadHead(PEPBUFFERPOS pBufferPos, SST_AT02_PKT_HEAD &oHead)
// {
// 	oHead.hd_flag = Ep_BufferReadDWord2(pBufferPos);;
// 	oHead.len = Ep_BufferReadDWord2(pBufferPos);
// 	oHead.utc_s = Ep_BufferReadDWord2(pBufferPos);
// 	oHead.utc_ns = Ep_BufferReadDWord2(pBufferPos);
// 	oHead.filber_smv_gs = Ep_BufferReadWord2(pBufferPos);
// 	oHead.appid = Ep_BufferReadWord2(pBufferPos);
// 	oHead.packet_len = Ep_BufferReadWord2(pBufferPos);  //61850报文的长度
// 	oHead.crc = Ep_BufferReadWord2(pBufferPos);
// 
// #ifdef SST_AT02_PKT_HEAD_USE_RESERVE
// 	oHead.sv_smp_cnt = Ep_BufferReadWord2(pBufferPos);
// 	oHead.reserive = Ep_BufferReadWord2(pBufferPos);
// #else
// 	oHead.nIndex = Ep_BufferReadDWord2(pBufferPos);
// #endif
// }

void CSttRcdMemBufferMngr::ParseSttRcdBuffer(CSttRcdMemBuffer *pRcdBuffer)
{
	BYTE *pBuffer = pRcdBuffer->GetBuffer();
	long nLenCopyLeft = pRcdBuffer->GetBufferLength();
// 	long nLenCopy = 0;
// 	long nBufLen = 0;
// 
// 	while (nLenCopyLeft > 0)
// 	{
// 		if (nLenCopyLeft + m_nLeftBufferLen > RCD_PARSE_BUFFER_MAX_LEN)
// 		{
// 			nLenCopy = RCD_PARSE_BUFFER_MAX_LEN - m_nLeftBufferLen;
// 			nBufLen = RCD_PARSE_BUFFER_MAX_LEN;
// 		}
// 		else
// 		{
// 			nLenCopy = nLenCopyLeft;
// 			nBufLen = nLenCopyLeft + m_nLeftBufferLen;
// 		}
// 
// 		if (m_nLeftBufferLen > 0)
// 		{
// 			memcpy(m_pSttRcdBuffer, m_pLeftBuffer, m_nLeftBufferLen);
// 		}
// 
// 		memcpy(m_pSttRcdBuffer + m_nLeftBufferLen, pBuffer, nLenCopy);
// 		ParseSttRcdBufferEx(nBufLen);
// 		nLenCopyLeft -= nLenCopy;
// 		pBuffer += nLenCopy;
// 	}
	CXCapPkgBufferMngrInterface::ParseSttRcdBuffer(pBuffer, nLenCopyLeft);

	pRcdBuffer->Ebs_SetParsed();
}
// 
// void CSttRcdMemBufferMngr::ParseSttRcdBufferEx(long nBufLen)
// {
// 	SST_AT02_PKT_HEAD oHead ;
// 	long nLenLeft = nBufLen;
// 	EPBUFFERPOS oBuffPos;
// 	memset(&oBuffPos, 0, sizeof(EPBUFFERPOS));
// 
// 	oBuffPos.pBuffer = m_pSttRcdBuffer;
// 	oBuffPos.nIndex = 0;
// 	oBuffPos.nPrevIndex = 0;
// 	oBuffPos.nBufLength = nLenLeft;
// 	nLenLeft = Ep_BufferLeave(&oBuffPos);
// 	long nPrevIndex = 0;
// 	DWORD dwHeadFrm = 0;
// 	long nPkgLen = 0;
// 	long nErrorCount = 0;
// 
// 	while (nLenLeft > 0)
// 	{
// 		if (nLenLeft > sizeof(SST_AT02_PKT_HEAD))
// 		{
// 			nErrorCount = 0;
// 			nPrevIndex = oBuffPos.nIndex;
// 
// 			//yyj—找起始固定帧头0x05640564
// 			dwHeadFrm = Ep_BufferGetDWord2(&oBuffPos);
// 			while(dwHeadFrm != STT_AT02_FIXED_HEAD)
// 			{
// 				Ep_OffsetBufferCurr(&oBuffPos,1);
// 				nLenLeft = Ep_BufferLeave(&oBuffPos);
// 				nErrorCount++;
// 				
// 				if (nLenLeft<STT_AT02_FIXED_HEAD_LEN)
// 				{
// 					memcpy(m_pLeftBuffer, Ep_GetBufferCurr(&oBuffPos), nLenLeft);
// 					m_nLeftBufferLen = nLenLeft;
// 					//CLogPrint::LogBuffer(oBuffPos.pBuffer, nPrevIndex, nErrorCount);
// 					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error Buffer [%d] byte...."), nErrorCount);
// 					break;
// 				}
// 
// 				dwHeadFrm = Ep_BufferGetDWord2(&oBuffPos);
// 			}
// 
// 			if (nErrorCount > 0)
// 			{
// 				//CLogPrint::LogBuffer(oBuffPos.pBuffer, nPrevIndex, nErrorCount);
// 				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error Buffer [%d] byte...."), nErrorCount);
// 			}
// 		}
// 
// 		nPrevIndex = oBuffPos.nIndex;
// 
// 		if (nLenLeft < sizeof(SST_AT02_PKT_HEAD))
// 		{
// 			oBuffPos.nIndex = nPrevIndex;
// 			nLenLeft = Ep_BufferLeave(&oBuffPos);
// 			ASSERT (nLenLeft >= 0);
// 			memcpy(m_pLeftBuffer, Ep_GetBufferCurr(&oBuffPos), nLenLeft);
// 			m_nLeftBufferLen = nLenLeft;
// 			break;
// 		}
// 
// 		ReadHead(&oBuffPos, oHead);
// 
// 		if (oHead.len <= 0 || oHead.len >= 1024)
// 		{//异常的长度
// 			//ASSERT (FALSE);
// 			oBuffPos.nIndex = nPrevIndex;
// 			Ep_OffsetBufferCurr(&oBuffPos,1);
// 			nLenLeft = Ep_BufferLeave(&oBuffPos);
// 			continue;
// 		}
// 
// 		nLenLeft = Ep_BufferLeave(&oBuffPos);
// 		nPkgLen = oHead.len*4 - sizeof(SST_AT02_PKT_HEAD) + 4;
// 
// 		if (nLenLeft < nPkgLen)
// 		{		
// 			oBuffPos.nIndex = nPrevIndex;
// 			nLenLeft = Ep_BufferLeave(&oBuffPos);
// 			ASSERT (nLenLeft >= 0);
// 			memcpy(m_pLeftBuffer, Ep_GetBufferCurr(&oBuffPos), nLenLeft);
// 			m_nLeftBufferLen = nLenLeft;
// 
// 			break;
// 		}
// 		else
// 		{
// 			CFrameMemBuffer *pFrameBuf = m_pRefSttFrameBufMngr->AddFrameBuffer(&oHead, Ep_GetBufferCurr(&oBuffPos));
// 
// 			if (m_oPrevHead.appid != 0)
// 			{
// #ifdef SST_AT02_PKT_HEAD_USE_RESERVE
// 				if (m_oPrevHead.reserive + 1 != oHead.reserive)
// #else
// 				if (m_oPrevHead.nIndex + 1 != oHead.nIndex)
// #endif
// 				{
// 					CString strText;
// #ifdef SST_AT02_PKT_HEAD_USE_RESERVE
// 					strText.Format(_T("%04X [%016I64X]        %04X [%016I64X]")
// 						, m_oPrevHead.reserive, m_n64PrevTime
// 						, oHead.reserive, pFrameBuf->m_n64TimeSnamp);
// #else
// 					strText.Format(_T("%08X [%016I64X]       %08X [%016I64X]")
// 						, m_oPrevHead.nIndex, m_n64PrevTime
// 						, oHead.nIndex, pFrameBuf->m_n64TimeSnamp);;
// #endif
// 					CLogPrint::LogString(XLOGLEVEL_TRACE, strText);
// 				}
// 			}
// 
// 			m_oPrevHead = oHead;
// 			m_n64PrevTime = pFrameBuf->m_n64TimeSnamp;
// 
// 			Ep_OffsetBufferCurr(&oBuffPos, nPkgLen);
// 			nLenLeft = Ep_BufferLeave(&oBuffPos);		//完整帧之后的剩余长度
// 			ASSERT (nLenLeft >= 0);
// 			m_nFrameCount++;
// 		}
// 
// 		//剩余帧长度不满一帧头拷贝到m_pLeftBuffer
// 		if (nLenLeft < sizeof(SST_AT02_PKT_HEAD))
// 		{
// 			memcpy(m_pLeftBuffer, Ep_GetBufferCurr(&oBuffPos), nLenLeft);
// 			m_nLeftBufferLen = nLenLeft;
// 
// 			break;
// 		}
// 	}
// }

//////////////////////////////////////////////////////////////////////////
//

void CSttRcdMemBufferMngr::ParseSttFrameBufferMngr()
{
	//lijunqing 2020-06-27
	//to yyj : 局部变量不能用m_开头，拷贝、粘贴代码的时候也注意下规范
	//C61850ParseFrameList m_o61850ParseFrameList;
	C61850ParseFrameList o61850ParseFrameList;
	CXSmMemBuffer *pCapBuffer = NULL;
	long nBegin1 = -1, nEnd1 = -1, nBegin2 = -1, nEnd2 = -1;

	m_pRefSttFrameBufMngr->GetParseIndexRange(nBegin1, nEnd1, nBegin2, nEnd2);
	long nIndex = 0;

	if (nEnd1 < 0)
	{
		return;
	}

	for (nIndex=nBegin1; nIndex<=nEnd1; nIndex++)
	{
		pCapBuffer = m_pRefSttFrameBufMngr->GetFrameBuffer(nIndex);
		
		EPBUFFERPOS bufPos;
		ZeroMemory(&bufPos, sizeof(EPBUFFERPOS));

		EPCAPPARSEDATAS m_oCapParseDatas;
		bufPos.pDatas = &m_oCapParseDatas;

		pCapBuffer->GetBufferPos(bufPos);

		bufPos.pItemData = &((CFrameMemBuffer*)pCapBuffer)->m_oCapBufferItem;
		o61850ParseFrameList.Parse(&bufPos);

		m_pRefSttFrameBufMngr->SetCurrParseIndex(nIndex+1);
	}

	m_pRefSttFrameBufMngr->SetLastParseIndex(nBegin1);

	if (nBegin2 < 0)
	{
		return;
	}

	for (nIndex=nBegin2; nIndex<=nEnd2; nIndex++)
	{
		pCapBuffer = m_pRefSttFrameBufMngr->GetFrameBuffer(nIndex);
		
		EPBUFFERPOS bufPos;
		ZeroMemory(&bufPos, sizeof(EPBUFFERPOS));

		EPCAPPARSEDATAS m_oCapParseDatas;
		bufPos.pDatas = &m_oCapParseDatas;

		pCapBuffer->GetBufferPos(bufPos);

		bufPos.pItemData = &((CFrameMemBuffer*)pCapBuffer)->m_oCapBufferItem;
		o61850ParseFrameList.Parse(&bufPos);

		m_pRefSttFrameBufMngr->SetCurrParseIndex(nIndex+1);
	}

	m_pRefSttFrameBufMngr->SetLastParseIndex(nBegin2);
}

void CSttRcdMemBufferMngr::ClearLeftBuffer()
{
	ZeroMemory(m_pSttRcdBuffer, RCD_PARSE_BUFFER_MAX_LEN+10);
	ZeroMemory(m_pLeftBuffer, RCD_LEFT_BUFFER_MAX_LEN);
	m_nLeftBufferLen = 0;
}
