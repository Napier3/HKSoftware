#include "stdafx.h"
#include "XSmartCapInterface.h"


void xsmartcap_ReadHead(PEPBUFFERPOS pBufferPos, SST_AT02_PKT_HEAD &oHead)
{
	oHead.hd_flag = Ep_BufferReadDWord2(pBufferPos);;
	oHead.len = Ep_BufferReadDWord2(pBufferPos);
	oHead.utc_s = Ep_BufferReadDWord2(pBufferPos);
	oHead.utc_ns = Ep_BufferReadDWord2(pBufferPos);
	oHead.filber_smv_gs = Ep_BufferReadWord2(pBufferPos);

// 	int nPkgType = (oHead.filber_smv_gs&0xFF)/0x10;
// 
// 	if (nPkgType != 3)
// 	{
// 		nPkgType = 4;
// 	}

	oHead.appid = Ep_BufferReadWord2(pBufferPos);
	oHead.packet_len = Ep_BufferReadWord2(pBufferPos);  //61850报文的长度
	oHead.crc = Ep_BufferReadWord2(pBufferPos);

#ifdef SST_AT02_PKT_HEAD_USE_RESERVE
	oHead.sv_smp_cnt = Ep_BufferReadWord2(pBufferPos);
	oHead.reserive = Ep_BufferReadWord2(pBufferPos);
#else
	oHead.nIndex = Ep_BufferReadDWord2(pBufferPos);
#endif
}

#include "../API/GlobalConfigApi.h"

void WritePkgDataFile(BYTE *pBuffer, long nLenCopyLeft)
{
	if (nLenCopyLeft<20000)
	{
		return;
	}

	char oCharString[1000];
	memset(oCharString,0,1000);
	int nCurIndex = 0;

	for (nCurIndex = 0;nCurIndex<nLenCopyLeft;)
	{
		ValueToHex(pBuffer,4,oCharString);

		if (strcmp(oCharString,_T("0x05640564")) == 0)
		{
			break;
		}

		pBuffer += 4;
		nCurIndex += 2;
	}

	CString strFile;
	strFile = _P_GetBinPath();
	SYSTEMTIME tm;
	::GetLocalTime(&tm);

	strFile.AppendFormat(_T("%02d%02d%02d.txt"), tm.wHour, tm.wMinute, tm.wSecond);
	CFile oFile;

	if (! oFile.Open(strFile, CFile::modeCreate | CFile::modeWrite))
	{
		return;
	}

	

	for (;nCurIndex<nLenCopyLeft;)
	{
		ValueToHex(pBuffer,100,oCharString);
		oFile.Write(oCharString, 202);
		oFile.Write(_T("\r\n"), 2);
		pBuffer += 100;
		nCurIndex += 100;
	}

	oFile.Close();
}

void CXCapPkgBufferMngrInterface::ParseSttRcdBuffer(BYTE *pBuffer, long nLenCopyLeft)
{
//	WritePkgDataFile(pBuffer,nLenCopyLeft);
	long nLenCopy = 0;
	long nBufLen = 0;

	while (nLenCopyLeft > 0)
	{
		if (nLenCopyLeft + m_nLeftBufferLen > RCD_PARSE_BUFFER_MAX_LEN)
		{
			nLenCopy = RCD_PARSE_BUFFER_MAX_LEN - m_nLeftBufferLen;
			nBufLen = RCD_PARSE_BUFFER_MAX_LEN;
		}
		else
		{
			nLenCopy = nLenCopyLeft;
			nBufLen = nLenCopyLeft + m_nLeftBufferLen;
		}

		if (m_nLeftBufferLen > 0)
		{
			memcpy(m_pSttRcdBuffer, m_pLeftBuffer, m_nLeftBufferLen);
		}

		memcpy(m_pSttRcdBuffer + m_nLeftBufferLen, pBuffer, nLenCopy);
		ParseSttRcdBufferEx(nBufLen);
		nLenCopyLeft -= nLenCopy;
		pBuffer += nLenCopy;
	}
}

void CXCapPkgBufferMngrInterface::ParseSttRcdBufferEx(long nBufLen)
{
	SST_AT02_PKT_HEAD oHead ;
	long nLenLeft = nBufLen;
	EPBUFFERPOS oBuffPos;
	memset(&oBuffPos, 0, sizeof(EPBUFFERPOS));

	oBuffPos.pBuffer = m_pSttRcdBuffer;
	oBuffPos.nIndex = 0;
	oBuffPos.nPrevIndex = 0;
	oBuffPos.nBufLength = nLenLeft;
	nLenLeft = Ep_BufferLeave(&oBuffPos);
	long nPrevIndex = 0;
	DWORD dwHeadFrm = 0;
	long nPkgLen = 0;
	long nErrorCount = 0;

	while (nLenLeft > 0)
	{
		if (nLenLeft > sizeof(SST_AT02_PKT_HEAD))
		{
			nErrorCount = 0;
			nPrevIndex = oBuffPos.nIndex;

			//yyj—找起始固定帧头0x05640564
			dwHeadFrm = Ep_BufferGetDWord2(&oBuffPos);
			while(dwHeadFrm != STT_AT02_FIXED_HEAD)
			{
				Ep_OffsetBufferCurr(&oBuffPos,1);
				nLenLeft = Ep_BufferLeave(&oBuffPos);
				nErrorCount++;
				
				if (nLenLeft<STT_AT02_FIXED_HEAD_LEN)
				{
					memcpy(m_pLeftBuffer, Ep_GetBufferCurr(&oBuffPos), nLenLeft);
					m_nLeftBufferLen = nLenLeft;
//					CLogPrint::LogBuffer(oBuffPos.pBuffer, nPrevIndex, nErrorCount);
//					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error Buffer [%d] byte...."), nErrorCount);
					break;
				}

				dwHeadFrm = Ep_BufferGetDWord2(&oBuffPos);
			}

			if (nErrorCount > 0)
			{
//				CLogPrint::LogBuffer(oBuffPos.pBuffer, nPrevIndex, nErrorCount);
//				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error Buffer [%d] byte...."), nErrorCount);
			}
		}

		nPrevIndex = oBuffPos.nIndex;

		if (nLenLeft < sizeof(SST_AT02_PKT_HEAD))
		{
			oBuffPos.nIndex = nPrevIndex;
			nLenLeft = Ep_BufferLeave(&oBuffPos);
			ASSERT (nLenLeft >= 0);
			memcpy(m_pLeftBuffer, Ep_GetBufferCurr(&oBuffPos), nLenLeft);
			m_nLeftBufferLen = nLenLeft;
			break;
		}

		xsmartcap_ReadHead(&oBuffPos, oHead);

		if (oHead.len <= 0 || oHead.len >= 1024)
		{//异常的长度
			//ASSERT (FALSE);
			oBuffPos.nIndex = nPrevIndex;
			Ep_OffsetBufferCurr(&oBuffPos,1);
			nLenLeft = Ep_BufferLeave(&oBuffPos);
			continue;
		}

		nLenLeft = Ep_BufferLeave(&oBuffPos);
		nPkgLen = oHead.len*4 - sizeof(SST_AT02_PKT_HEAD) + 4;

		if (nLenLeft < nPkgLen)
		{		
			oBuffPos.nIndex = nPrevIndex;
			nLenLeft = Ep_BufferLeave(&oBuffPos);
			ASSERT (nLenLeft >= 0);
			memcpy(m_pLeftBuffer, Ep_GetBufferCurr(&oBuffPos), nLenLeft);
			m_nLeftBufferLen = nLenLeft;

			break;
		}
		else
		{
			CFrameMemBuffer *pFrameBuf = m_pRefSttFrameBufMngr->AddFrameBuffer(&oHead, Ep_GetBufferCurr(&oBuffPos));

// 			if (m_oPrevHead.appid != 0)//20220613 zhouhj 之前AT02D调试用,现index位置已传递通道数的值,不能再进行比较
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

			m_oPrevHead = oHead;
			m_n64PrevTime = pFrameBuf->m_n64TimeSnamp;

			Ep_OffsetBufferCurr(&oBuffPos, nPkgLen);
			nLenLeft = Ep_BufferLeave(&oBuffPos);		//完整帧之后的剩余长度
			ASSERT (nLenLeft >= 0);
			m_nFrameCount++;
		}

		//剩余帧长度不满一帧头拷贝到m_pLeftBuffer
		if (nLenLeft < sizeof(SST_AT02_PKT_HEAD))
		{
			memcpy(m_pLeftBuffer, Ep_GetBufferCurr(&oBuffPos), nLenLeft);
			m_nLeftBufferLen = nLenLeft;

			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
PSTT_AT02_PKT_HEAD_STC CXCapPkgBufferMngrInterface::SttAddAppID(unsigned short nAppID)
{
	long k = 0;

	for (k=0; k<m_oPkgHeadStcMngr.nCount; k++)
	{
		if (m_oPkgHeadStcMngr.oHeadStc[k].appid == nAppID)
		{
			return &m_oPkgHeadStcMngr.oHeadStc[k];
		}
	}

	if (m_oPkgHeadStcMngr.nCount >= STT_AT02_HDAD_STC_MAX)
	{
		return NULL;
	}

	m_oPkgHeadStcMngr.oHeadStc[k].appid = nAppID;
	m_oPkgHeadStcMngr.nCount++;

	return &m_oPkgHeadStcMngr.oHeadStc[k];
}

void CXCapPkgBufferMngrInterface::SttAt02HadStc(SST_AT02_PKT_HEAD &oHead)
{
#ifdef SST_AT02_PKT_HEAD_USE_RESERVE
	PSTT_AT02_PKT_HEAD_STC p = SttAddAppID(oHead.appid);
	p->nPkgCount++;

	if (p->prev_sv_smp_cnt == 0xFFFF)
	{//第一帧
		p->prev_sv_smp_cnt = oHead.sv_smp_cnt;
		return;
	}

	if (p->prev_sv_smp_cnt == 3999)
	{
		if (oHead.sv_smp_cnt == 0)
		{
		}
		else
		{
			p->nSmpCntError += oHead.sv_smp_cnt;
		}
	}
	else
	{
		if (p->prev_sv_smp_cnt == oHead.sv_smp_cnt - 1)
		{
		}
		else
		{
			if (p->prev_sv_smp_cnt > oHead.sv_smp_cnt)
			{
				p->nSmpCntError += oHead.sv_smp_cnt;
				p->nSmpCntError += 3999 - p->prev_sv_smp_cnt;
			}
			else
			{
				p->nSmpCntError += oHead.sv_smp_cnt - p->prev_sv_smp_cnt;
			}
		}
	}

	p->prev_sv_smp_cnt = oHead.sv_smp_cnt;
#endif
}

void CXCapPkgBufferMngrInterface::AnalysisSttAT02HeadBuffer(BYTE *pBuffer, long nLenBuffer)
{
	long nLenHead = sizeof(SST_AT02_PKT_HEAD);

	//上次遗留剩下的报文
	if (m_nLeftBufferLen > 0)
	{
		memcpy(m_pSttRcdBuffer, m_pLeftBuffer, m_nLeftBufferLen);
	}

	memcpy(m_pSttRcdBuffer + m_nLeftBufferLen, pBuffer, nLenBuffer);

	SST_AT02_PKT_HEAD oHead ;
	long nLenLeft = m_nLeftBufferLen + nLenBuffer;
	EPBUFFERPOS oBuffPos;
	memset(&oBuffPos, 0, sizeof(EPBUFFERPOS));

	oBuffPos.pBuffer = m_pSttRcdBuffer;
	oBuffPos.nIndex = 0;
	oBuffPos.nPrevIndex = 0;
	oBuffPos.nBufLength = nLenLeft;
	nLenLeft = Ep_BufferLeave(&oBuffPos);
	long nPrevIndex = 0;
	DWORD dwHeadFrm = 0;
	long nPkgLen = 0;
	long nErrorCount = 0;

	while (nLenLeft >= nLenHead)
	{
		xsmartcap_ReadHead(&oBuffPos, oHead);
		SttAt02HadStc(oHead);
		nLenLeft = Ep_BufferLeave(&oBuffPos);
	}

	if (nLenLeft > 0)
	{
		memcpy(m_pLeftBuffer, Ep_GetBufferCurr(&oBuffPos), nLenLeft);
		m_nLeftBufferLen = nLenLeft;
	}
	else
	{
		m_nLeftBufferLen = 0;
	}
}


//////////////////////////////////////////////////////////////////////////
//
long CXCapPkgBufferMngrInterface::g_nXSmartCapDebugHead = 0;

void CXCapPkgBufferMngrInterface::XSmartCapDebugHead()
{
	g_nXSmartCapDebugHead = 1;
}

BOOL CXCapPkgBufferMngrInterface::Is_XSmartCapDebugHead()
{
	return g_nXSmartCapDebugHead;
}
