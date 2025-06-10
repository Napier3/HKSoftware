#include "stdafx.h"
#include "CapThreadBase.h"


CCapThreadBase::CCapThreadBase(void)
{
	m_pCaptureThread = NULL;
	m_pParseThread = NULL;
	//m_hCapParseMonitor = NULL;

// 	_InitParseMonitorBuffer(&m_oParseMonitorBuffer);
// 	_InitParseMonitorBuffer(&m_oParseMonitorBuffer, 10000);

	m_bShowFrameRecord = TRUE;
	m_bUseParseThread = FALSE;
// 	m_bCanFreeAllCapDatas = FALSE;
	m_pProtocol = NULL;

	//m_pToWork = new CToWork();
}

CCapThreadBase::~CCapThreadBase(void)
{
//	_FrearseMonitorBuffer(&m_oParseMonitorBuffer);
	StopCapture();
// 	m_oCapBufferMngr.DeleteAll();
// 	delete m_pProtocol;
}

void CCapThreadBase::CreateCapture()
{
	ASSERT (m_pCaptureThread == NULL );
	m_bExitCapture = FALSE;
	m_bStopCapture = FALSE;
	ASSERT( m_pProtocol != NULL);

	if (CreateCaptureThread() == 0xFFFFFFFF)
	{

	}
}

void CCapThreadBase::StopCapture()
{
	m_bStopCapture = TRUE;
}

void CCapThreadBase::ResumeCapture()
{
	m_bStopCapture = FALSE;
}

void CCapThreadBase::ReleaseCapture()
{
// 	if (m_pCaptureThread == NULL)
// 		return;
// 
// 	if (m_bUseParseThread && m_pParseThread == NULL)
// 	{
// 		return;
// 	}
//
	if (m_bExitCapture)
	{
		return;
	}
		
	m_bExitCapture = TRUE;

	ExitCapture();
}

BOOL CCapThreadBase::IsCaptureStarted()
{
	if (m_pCaptureThread == NULL)
	{
		return FALSE;
	}

	if (m_bUseParseThread)
	{
		if (m_pParseThread == NULL)
		{
			return FALSE;
		}
	}

	if (m_bExitCapture)
	{
		return FALSE;
	}

	if (m_bStopCapture)
	{
		return TRUE;
	}

	return TRUE;
}

BOOL CCapThreadBase::HasAllCapThreadExit()
{
	if (m_pCaptureThread != NULL)
	{
		return FALSE;
	}

	if (m_bUseParseThread)
	{
		if (m_pParseThread != NULL)
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CCapThreadBase::WriteCap()	
{	

}

void CCapThreadBase::FreeAllCapDatas()
{
// 	while (m_bCanFreeAllCapDatas)
// 	{
// 		m_oCapBufferMngr.DeleteAll();
// 		m_bCanFreeAllCapDatas = FALSE;
// 	}
}

void CCapThreadBase::FreeAllParsedBuffer()
{
	
}

void CCapThreadBase::Parse(CFrameMemBuffer *pCapBuffer)
{
	if (pCapBuffer == NULL)
	{
		return;
	}

	while (TRUE)
	{
		CExBaseObject *p = m_pProtocol->Parse(pCapBuffer, FALSE);
		pCapBuffer->SetState(EBS_BEPARSED);

		if (p != NULL)
		{
			//添加到数据缓冲区
			
		}
		else if (Ep_IsMatchStateNotFull(&m_pProtocol->m_bufPos) )
		{//报文不完整,在GetBufferNeedParse合并到下一个Buffer
			return;
		}
		else
		{
			return;
		}
	}
}


long CCapThreadBase::MemBufferMngrParse()
{
	CXSmMemBuffer *pCapBuffer = NULL;
	long nBegin1 = -1, nEnd1 = -1, nBegin2 = -1, nEnd2 = -1;
	m_pCapBufferMngr->GetParseIndexRange(nBegin1, nEnd1, nBegin2, nEnd2);
	long nIndex = 0;
	CExBaseObject *p = NULL;

	if (nEnd1 < 0)
	{
		return 0;
	}

	for (nIndex=nBegin1; nIndex<=nEnd1; nIndex++)
	{
		if (m_bExitCapture)
		{
			return 0;
		}

		pCapBuffer = m_pCapBufferMngr->GetFrameBuffer(nIndex);
		p = m_pProtocol->Parse(pCapBuffer, 0);

		if (p == NULL || m_pProtocol->m_bufPos.pDatas->nParseState < 0)
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Parse Error [%016I64X]"), pCapBuffer->m_n64TimeSnamp);//chenling20240201 测试提减少打印信息，后面调试放出即可
		}

		//下一次的位置 = 当前位置的下一个位置
		m_pCapBufferMngr->SetCurrParseIndex(nIndex+1);
	}

	if (nBegin2 < 0)
	{
		return nEnd1 - nBegin1 + 1;
	}

	for (nIndex=nBegin2; nIndex<=nEnd2; nIndex++)
	{
		if (m_bExitCapture)
		{
			return 0;
		}

		pCapBuffer = m_pCapBufferMngr->GetFrameBuffer(nIndex);
		p = m_pProtocol->Parse(pCapBuffer, 0);

		if (p == NULL || m_pProtocol->m_bufPos.pDatas->nParseState < 0)
		{
			int nPkgType = (pCapBuffer->m_nFiberAndPkgType&0xFF)/0x10;

			if (nPkgType != Protocol61850_Pkg_Type_MUTIMEDATA)//zhouhj 2024.4.24 去除该类报文
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("[%016I64X]"), pCapBuffer->m_n64TimeSnamp);
			}
		}

		//下一次的位置 = 当前位置的下一个位置
		m_pCapBufferMngr->SetCurrParseIndex(nIndex+1);
	}

	return nEnd1 - nBegin1 + nEnd2 - nBegin2 + 2;
}

// 
// void CCapThreadBase::RecordFrame(CExBaseObject *pFrame, CFrameMemBuffer *pBuffer, PBUFFERPOS pBuffPos)
// {
// 	CFrameBase *pFrameBase = (CFrameBase*)pFrame;
// 	long nCurrIndex = 0;
// 	CFrameRecord *pRecord = m_oRecordMngr.AddRecord(nCurrIndex);
// 
// 	ASSERT (pRecord != NULL);
// 
// 	if (pRecord == NULL)
// 	{
// 		return;
// 	}
// 
// 	pRecord->m_nProtocol = pBuffPos->nProtocol;
// 	pRecord->m_tm = pBuffer->m_ts; //cap的时间
// 	pRecord->m_ipGroup = pBuffer->m_ipGroup; //cap的时间
// 	pRecord->m_n64CapID = pBuffer->m_n64CapID;   //cap id
// 	pRecord->m_nDataCount = pBuffPos->pDatas->GetCount(); //cap的时间
// 	pRecord->m_nDeviceDataType = pBuffPos->pDatas->m_nDeviceDataType; //cap的时间
// 
// 	if (pFrameBase != NULL)
// 	{
// 		pRecord->SetBuffer(pBuffPos->pBuffer, pBuffPos->dwBufferLen);
// 	}
// 	else
// 	{
// 		pRecord->SetBuffer(pBuffer->GetBuffer(), pBuffer->GetDataLength());
// 	}
// 
// 	//根据pBuffer的情况确定显示的处理情况
// 	if (m_bShowFrameRecord && m_hCapParseMonitor != NULL)
// 	{
// 		if (::IsWindow(m_hCapParseMonitor))
// 		{
// 			::PostMessage(m_hCapParseMonitor, WM_CAP_MONITOR, (WPARAM)&m_oRecordMngr, (LPARAM)nCurrIndex);
// 		}
// 	}
// }
// 
