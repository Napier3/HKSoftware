#include "StdAfx.h"
#include "EpCapThreadBase.h"

long g_EpCapDatasGeneratorMode = 0;
long g_nExitCaptrueState = 0;
long g_DEBUG_MONITOR_STATE = 0;

CEpCapThreadBase::CEpCapThreadBase(void)
{
	m_pCaptureThread = NULL;
	m_pParseThread = NULL;
	m_hCapParseMonitor = NULL;

// 	Ep_InitParseMonitorBuffer(&m_oParseMonitorBuffer);
// 	Ep_InitParseMonitorBuffer(&m_oParseMonitorBuffer, 10000);

	m_pCapGenDatas = NULL;
	m_posCurrData = NULL;

	m_bShowFrameRecord = TRUE;
	m_bUseParseThread = FALSE;
	m_bCanFreeAllCapDatas = FALSE;
	m_bViewThreadRunInfor = FALSE;
	SetCapData(TRUE);
}

void CEpCapThreadBase::CapGenDataThread(LONG nProtocol, EP_ETHER_CAP_IP_GROUP *pIpg)
{
	if (m_pCapGenDatas == NULL)
	{
		return;
	}

	struct timeval64
	{
		union
		{
			struct timeval ts;
			volatile __int64 tm64;
		};
	} ts64;
	
	ep_curr_cap_timeval(ts64.ts);
	m_posCurrData = NULL;
	CEpCapGenData *pData = NULL;

	EP_ETHER_CAP_IP_GROUP ipg;
	memset(&ipg, 0, sizeof(EP_ETHER_CAP_IP_GROUP));

	if (pIpg != NULL)
	{
		ipg = *pIpg;
	}

#ifdef _use_const_101_104
	BYTE pBufferCap[200];
	char strData[200];
	strcpy(strData, "0x6812DC7514000D01030001002240008CCD1FC400");
	long nLen = HexToValue(strData, pBufferCap);
#endif

	while (TRUE)
	{
		if (m_bExitCapture)
		{
			break;
		}

		//解析
		ParseEx();

		if (g_EpCapDatasGeneratorMode == 0)
		{
			Sleep(100);


			continue;
		}

		if (g_EpCapDatasGeneratorMode == 1)
		{//单点
			g_EpCapDatasGeneratorMode = 0;
		}

//		ts64.tm64 += 1;
		ep_curr_cap_timeval(ts64.ts);

#ifdef _use_const_101_104
		if (pIpg == NULL)
		{
			ipg.dst.ip.s_addr = 169936391;
			ipg.src.ip.s_addr = 169990402;
		}
		m_oCapCycleBufferMngr.AddCapBuffer(ts64.ts, ipg, pBufferCap, nLen, nProtocol);
#else
		if (m_posCurrData == NULL)
		{
			m_posCurrData = m_pCapGenDatas->GetHeadPosition();
		}

		if (m_posCurrData == NULL)
		{
			Sleep(100);
			continue;
		}

		pData = (CEpCapGenData*)m_pCapGenDatas->GetNext(m_posCurrData);

		if (pIpg == NULL)
		{
			ipg.dst.ip.s_addr = pData->m_dwAddrDst;
			ipg.src.ip.s_addr = pData->m_dwAddrSrc;
		}
		BYTE *pBuffer = NULL;
		long nDataLength = 0;

		pData->GetFrameDataBuffer(&pBuffer, &nDataLength);

		if (pBuffer != NULL)
		{
			m_oCapCycleBufferMngr.AddCapBuffer(ts64.ts, ipg, pBuffer, nDataLength, nProtocol);
		}
#endif

		Sleep(100);	

		//解析
		ParseEx();

		//释放
		WriteCap();
		FreeAllParsedBuffer();
	}
}

CEpCapThreadBase::~CEpCapThreadBase(void)
{
//	Ep_FreeParseMonitorBuffer(&m_oParseMonitorBuffer);
	StopCapture();
	m_oCapCycleBufferMngr.DeleteAll();
	delete m_pProtocol;
}

void CEpCapThreadBase::CreateCapture()
{
	ASSERT (m_pCaptureThread == NULL );
	m_bExitCapture = FALSE;
	m_bStopCapture = FALSE;
	ASSERT( m_pProtocol != NULL);

	if (CreateCaptureThread() == 0xFFFFFFFF)
	{

	}
}

void CEpCapThreadBase::StopCapture()
{
	m_bStopCapture = TRUE;
}

void CEpCapThreadBase::ResumeCapture()
{
	m_bStopCapture = FALSE;
}

void CEpCapThreadBase::ReleaseCapture()
{
	if (m_pCaptureThread == NULL)
		return;

	if (m_bUseParseThread && m_pParseThread == NULL)
	{
		return;
	}

	if (m_bExitCapture)
	{
		return;
	}
		
	m_bExitCapture = TRUE;

	ExitCapture();
}

BOOL CEpCapThreadBase::IsCaptureStarted()
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

BOOL CEpCapThreadBase::HasAllCapThreadExit()
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

void CEpCapThreadBase::WriteCap()	
{	

}

void CEpCapThreadBase::FreeAllCapDatas()
{
	while (m_bCanFreeAllCapDatas)
	{
		m_oRecordMngr.DeleteAll();
		m_oCapCycleBufferMngr.DeleteAll();
		m_bCanFreeAllCapDatas = FALSE;
	}
}

void CEpCapThreadBase::FreeAllParsedBuffer()
{
	if (m_oCapCycleBufferMngr.IsWriteFinished())
	{
		m_oCapCycleBufferMngr.SetWriteFinished(FALSE);
		m_oCapCycleBufferMngr.FreeParsedBuffer();
	}
}
// 
// void CEpCapThreadBase::Parse()
// {
// 	while (TRUE)
// 	{
// 		if (m_bExitCapture)
// 		{
// 			m_pProtocol->OnExit();
// 			break;
// 		}
// 
// 		//是否有可以待解析处理的缓冲区对象
// 		if (m_oCapCycleBufferMngr.HasBufferNeedParse())
// 		{
// 			CEpCycleMemBuffer *pBuffer = m_oCapCycleBufferMngr.GetBufferNeedParse();
// 
// 			if (pBuffer == NULL)
// 			{
// 				Sleep(10);
// 				continue;
// 			}
// 
// 			while (TRUE)
// 			{
// 				if (pBuffer->GetLengthNeedParse() <= 0)
// 				{
// 					break;
// 				}
// 
// 				CExBaseObject *p = m_pProtocol->Parse(pBuffer, NULL, FALSE);
// 
// 				if (p != NULL)
// 				{
// 					//添加到数据缓冲区
// 					RecordFrame(p, (CCapCycleMemBuffer*)pBuffer, &m_pProtocol->m_bufPos);
// 					CEpFrameBase *pFrame = (CEpFrameBase*)p;
// 					pFrame->DeleteAll();
// 					pFrame->FreeBuffer();
// 				}
// 				else if (Ep_IsMatchStateNotFull(&m_pProtocol->m_bufPos) )
// 				{//报文不完整,在GetBufferNeedParse合并到下一个Buffer
// 					RecordFrame(NULL, (CCapCycleMemBuffer*)pBuffer, &m_pProtocol->m_bufPos);
// 					pBuffer->OffsetCurrPos(-1);
// 					break;
// 				}
// 				else
// 				{
// 					RecordFrame(NULL, (CCapCycleMemBuffer*)pBuffer, &m_pProtocol->m_bufPos);
// 					pBuffer->OffsetCurrPos(-1);
// 					break;
// // 					pBuffer->SetState(EBS_PARSEDERROR);
// // 					pBuffer->OffsetCurrPos(-1);//位移下一个位置
// // 
// // 					if (pBuffer->GetUnparseBufferLength() <= 0)
// // 					{//如果缓冲区处理完毕,结束
// // 						pBuffer->SetState(EBS_BEPARSED);
// // 						break;
// // 					}
// 				}
// 			}
// 		}
// 
// 		Sleep(10);
// 	}
// }

void CEpCapThreadBase::ParseEx()
{
	while (TRUE)
	{
		if (m_bExitCapture)
		{
			m_pProtocol->OnExit();
			break;
		}

		//是否有可以待解析处理的缓冲区对象
		if (m_oCapCycleBufferMngr.HasBufferNeedParse())
		{
			CCapCycleMemBuffer *pCapBuffer = (CCapCycleMemBuffer*)m_oCapCycleBufferMngr.GetBufferNeedParse();

			if (pCapBuffer == NULL)
			{
				break;
			}

			while (TRUE)
			{
				if (pCapBuffer->GetLengthNeedParse() <= 0)
				{
					pCapBuffer->OffsetCurrPos(-1);
					pCapBuffer->SetState(EBS_BEPARSED);
					break;
				}

				CExBaseObject *p = m_pProtocol->Parse(pCapBuffer, NULL, FALSE);

				if (p != NULL)
				{
					//添加到数据缓冲区
					//RecordFrame(p, pCapBuffer, &m_pProtocol->m_bufPos);
					//CEpFrameBase *pFrame = (CEpFrameBase*)p;
					//pFrame->DeleteAll();
					//pFrame->FreeBuffer();

					//如果没有全部解析完成，则切割CCapCycleMemBuffer
					if (!pCapBuffer->Ebs_BeParsed())
					{
						pCapBuffer = m_oCapCycleBufferMngr.SplitBuffer(pCapBuffer);

						if (pCapBuffer == NULL)
						{
							break;
						}
					}
				}
				else if (Ep_IsMatchStateNotFull(&m_pProtocol->m_bufPos) )
				{//报文不完整,在GetBufferNeedParse合并到下一个Buffer
					//RecordFrame(NULL, pCapBuffer, &m_pProtocol->m_bufPos);
					pCapBuffer->OffsetCurrPos(-1);
					break;
				}
				else
				{
					//RecordFrame(NULL, pCapBuffer, &m_pProtocol->m_bufPos);
					pCapBuffer->OffsetCurrPos(-1);
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
}

void CEpCapThreadBase::ParseEx(CCapCycleMemBuffer *pCapBuffer)
{
// 	CCapCycleMemBuffer *pTempBuffer = (CCapCycleMemBuffer*)m_oCapCycleBufferMngr.GetBufferNeedParse();
// 
// 	if (pCapBuffer != pTempBuffer)
// 	{
// 		CLogPrint::LogString(LOGLEVEL_TRACE, _T("pCapBuffer != pTempBuffer"));
// 	}

	if (pCapBuffer == NULL)
	{
		return;
	}

	while (TRUE)
	{
		if (pCapBuffer->GetLengthNeedParse() <= 0)
		{
			pCapBuffer->OffsetCurrPos(-1);
			break;
		}

		CExBaseObject *p = m_pProtocol->Parse(pCapBuffer, NULL, FALSE);
		pCapBuffer->OffsetCurrPos(-1);

		if (p != NULL)
		{
			pCapBuffer->Set_RECORD_NEEDRECORD();
			//添加到数据缓冲区
			//RecordFrame(p, pCapBuffer, &m_pProtocol->m_bufPos);
			//CEpFrameBase *pFrame = (CEpFrameBase*)p;
			//pFrame->DeleteAll();
			//pFrame->FreeBuffer();

			//如果没有全部解析完成，则切割CCapCycleMemBuffer
// 			if (!pCapBuffer->Ebs_BeParsed())
// 			{
// 				pCapBuffer = m_oCapCycleBufferMngr.SplitBuffer(pCapBuffer);
// 
// 				if (pCapBuffer == NULL)
// 				{
// 					return;
// 				}
// 			}
		}
		else if (Ep_IsMatchStateNotFull(&m_pProtocol->m_bufPos) )
		{//报文不完整,在GetBufferNeedParse合并到下一个Buffer
			//RecordFrame(NULL, pCapBuffer, &m_pProtocol->m_bufPos);
			//pCapBuffer->OffsetCurrPos(-1);
			break;
		}
		else
		{
			//RecordFrame(NULL, pCapBuffer, &m_pProtocol->m_bufPos);
			//pCapBuffer->OffsetCurrPos(-1);
			break;
		}
	}

	pCapBuffer->SetState(EBS_BEPARSED);

}

void CEpCapThreadBase::RecordFrame(/*CExBaseObject *pFrame, */CCapCycleMemBuffer *pCycleBuffer, PEPBUFFERPOS pBuffPos)
{
	//pCycleBuffer->m_dwRecord = TRUE;
	pCycleBuffer->Set_RECORD_HASRECORD();
	//CEpFrameBase *pEpFrameBase = (CEpFrameBase*)pFrame;
	long nCurrIndex = 0;
	CEpFrameRecord *pRecord = m_oRecordMngr.AddRecord(nCurrIndex);

	ASSERT (pRecord != NULL);

	if (pRecord == NULL)
	{
		return;
	}

	pRecord->m_nProtocol = pBuffPos->nProtocol;
	pRecord->m_tm = pCycleBuffer->m_ts; //cap的时间
	pRecord->m_ipGroup = pCycleBuffer->m_ipGroup; //cap的时间
	pRecord->m_n64CapID = pCycleBuffer->m_n64CapID;   //cap id

	if (pBuffPos->pDatas != NULL)
	{
		pRecord->m_nDataCount = pBuffPos->pDatas->GetCount(); //cap的时间
		pRecord->m_nDeviceDataType = pBuffPos->pDatas->m_nDeviceDataType; //cap的时间
	}
	else
	{
		pRecord->m_nDataCount = 0;
	}

	pRecord->SetBuffer(pCycleBuffer->GetBuffer(), pCycleBuffer->GetDataLength());
// 	if (pEpFrameBase != NULL)
// 	{
// 		pRecord->SetBuffer(pBuffPos->pBuffer, pBuffPos->dwBufferLen);
// 	}
// 	else
// 	{
// 		pRecord->SetBuffer(pCycleBuffer->GetBuffer(), pCycleBuffer->GetDataLength());
// 	}

	//根据pBuffer的情况确定显示的处理情况
	if (m_bShowFrameRecord && m_hCapParseMonitor != NULL)
	{
		if (::IsWindow(m_hCapParseMonitor))
		{
			::PostMessage(m_hCapParseMonitor, WM_CAP_MONITOR, (WPARAM)&m_oRecordMngr, (LPARAM)nCurrIndex);
		}
	}
}

