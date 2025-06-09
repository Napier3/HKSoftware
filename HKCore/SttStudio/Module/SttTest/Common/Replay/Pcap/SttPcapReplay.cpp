#include "stdafx.h"
#include"SttPcapReplay.h"
#ifdef _PSX_IDE_QT_
	#include "../../../../SttDevice/Module/Driver466/SttDeviceComm.h"
#endif

//QFile oDebugFile("/mnt/Stt/PcapRecvData");
CString CSttPcapReplay::m_strMacroName = "Pcap回放测试";
CString CSttPcapReplay::m_strMacroID = STT_MACRO_ID_DigReplayTest;
CString CSttPcapReplay::m_strFilePostFix = "replaytst";
CString CSttPcapReplay::m_strMacroVer = "1.0";

CSttPcapReplay::CSttPcapReplay()
{
	m_strName = m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	m_pPcapData = (DrvPcapData *)stt_test_get_drvparas_buff();
}

void CSttPcapReplay::Init()
{
//    oDebugFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
	tmt_DigReplayParas::init();
	CSttTestBase::Init();
	m_nCurReqIndex = 1;
	m_nCurReplayIndex = 1;
	m_nCurReplayLoopIndex = 0;
	m_bInLooping = FALSE;
	m_pPcapData->module = 0;
	memset(&m_oPcapParam, 0, sizeof(DrvPcapParam));

	if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
	{
		long nModuleIndex = g_theDeviceSystemParameter->m_oModules_D[0]->m_oModuleAttr.m_nModuleIndex;
		m_pPcapData->module = ModuleIndexTransToDrv(nModuleIndex);
	}

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_D; i++)
	{
		long nModuleIndex = g_theDeviceSystemParameter->m_oModules_D[i]->m_oModuleAttr.m_nModuleIndex;
		m_oPcapParam.modules |= ModuleIndexTransToDrv(nModuleIndex);
	}
}

long CSttPcapReplay::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttPcapReplay::~CSttPcapReplay(void)
{
}

void CSttPcapReplay::AfterSetParameter()
{
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	m_oPcapParam.tripType = m_nTripType;

	switch(m_nTripType)
	{
		case 2: // GPS触发
		{
			short nYear, nMon, nDay, nHour, nMin, nSec;
			TransTimer_t(g_theSttDeviceStatus->m_nUser_s, nYear, nMon, nDay, nHour, nMin, nSec);
			nHour = m_tGps.nHour;
			nMin = m_tGps.nMinutes;
			nSec = m_tGps.nSeconds;
			unsigned int ntime_t;
			TransTimer_To_t(ntime_t, nYear, nMon, nDay, nHour, nMin, nSec);
			ntime_t -= g_theSttDeviceStatus->m_nTimeZone * 3600;
			m_oPcapParam.gpsSec = ntime_t;
			m_oPcapParam.gpsnSec = 0;
		}
		break;

		case 3: // bi(开入)
		{
			m_oPcapParam.stBITrip.nBiLogic = m_nBinLogic;

			for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
			{
				if(m_binIn[i].nSelect)
				{
					m_oPcapParam.stBITrip.nBiRef = m_binIn[i].nTrigMode;
					m_oPcapParam.stBITrip.nVal1 |= (0x01 << i);
				}
			}
		}
		break;
	}

	if(m_fOutPutTime < 1.0)
	{
		m_fOutPutTime = 1.0;//预留最小输出时间
	}

	m_oPcapParam.mSec = m_fOutPutTime * 1000;
#ifdef _PSX_QT_LINUX_
	int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	ioctl(nFd, 0x35A, 0);
	write(nFd, (char *)&m_oPcapParam, sizeof(DrvPcapParam));
#endif
}

void CSttPcapReplay::SendDataToDevice()
{
	int nCurReplayIndex = m_nCurReplayIndex % 2 == 0 ? 2 : 1;
	m_nCurReplayIndex++;
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("SendDataToDevice nCurReplayIndex = %d"), nCurReplayIndex);
	CComtradeDataBuffer *pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(nCurReplayIndex);

	if(!pComtradeBuf->CanRead())
	{
		return;
	}

	unsigned char *pszSrcBuf = (unsigned char *)pComtradeBuf->GetBuffer();
	long nDataLen = pComtradeBuf->GetDataLen();
#ifdef _PSX_QT_LINUX_
	int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	ioctl(nFd, 0x35A, 1);
	memcpy(m_pPcapData->dat, pszSrcBuf, nDataLen * 4);
	m_pPcapData->pkglen = nDataLen;
	write(nFd, (char *)m_pPcapData, sizeof(DrvPcapData));
#endif
//    oDebugFile.write((char *)pszSrcBuf, nDataLen * sizeof(float));
//    oDebugFile.flush();
//    system("sync");
//    if(m_bSendFinish)
//    {
//        oDebugFile.close();
//    }
//    else
//    {
//        CSttTestServerBase *pServerEngine = CSttTestServerBase::GetServerEngine();
//        ASSERT(pServerEngine != NULL);
//        m_nCurReqIndex++;
//        pServerEngine->Comtrade_SendRequestData(m_nCurReqIndex % 2 == 0 ? 2 : 1);
//    }
}

BOOL CSttPcapReplay::EventProcess()
{
#ifdef _PSX_QT_LINUX_
	BOOL bTestFinished = FALSE;
	int nfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	char *pDrvResults = stt_test_get_drvresult_buff();
	int nret = 0;
	
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	nret = read(nfd, pDrvResults, 0x203);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	if(nret > 0)
	{
		Drv_ResultItem oDrvResItem;
		int nDrvResItemLen = sizeof(Drv_ResultItem);

		for(int i = 0; i < nret / nDrvResItemLen; i++)
		{
			memcpy(&oDrvResItem, pDrvResults + i * nDrvResItemLen, nDrvResItemLen);
			double dTime = oDrvResItem.nSec + oDrvResItem.nNanoSec * 0.000000001;

			if(oDrvResItem.nType == RESULT_TYPE_PcapReplay_Start)
			{
				ReturnTestStateEvent_TestStart(dTime, 0, FALSE);
			}
			else if(oDrvResItem.nType == RESULT_TYPE_PcapReplay_Trip)
			{
				m_dTestStartTime = dTime;//第一个报文输出点时间，循环时为第一个循环输出点
			}			
			else if(oDrvResItem.nType == DrvResult_BI)
			{
				STT_TEST_EVENT obufEvent;
				int nEventIndex = 0;
				obufEvent.oTime.dTime = dTime;
				obufEvent.oTime.dRealTime = dTime - m_dTestStartTime;
				obufEvent.oTime.dBinActTime = -1;
				int nBiChang = 0;
				int nBiValue = 0;
				int nCnt = g_nBinCount;

				if(nCnt > MAX_BINARYIN_COUNT)
				{
					nCnt = MAX_BINARYIN_COUNT;
				}
				else
				{
					if(nCnt < 8)
					{
						nCnt = 8;//GOOSE开入映射D1-D8
					}
				}

				for(int nChanIndex = 0; nChanIndex < nCnt; nChanIndex++)
				{
					nBiValue = oDrvResItem.nBi.item[0].nVal1 >> nChanIndex;
					nBiValue = nBiValue & 0x1;
					nBiChang = oDrvResItem.oBiChg.item[0].nVal1 >> nChanIndex;
					nBiChang = nBiChang & 0x1;

					if(nBiChang == 0)
					{
						continue;
					}

					nBiValue = (nBiValue == 0 ? 1 : 0);
					obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bin;
					obufEvent.oEventInfo[nEventIndex].nStateIndex = -1;
					obufEvent.oEventInfo[nEventIndex].nStateNum = -1;
					obufEvent.oEventInfo[nEventIndex].nStepIndex = -1;
					obufEvent.oEventInfo[nEventIndex].nChannel = nChanIndex + 1;
					obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
					nEventIndex++;
				}

				if(nEventIndex > 0)
				{
					obufEvent.nEventInfoCnt = nEventIndex;
					stt_add_test_event(obufEvent);
				}
			}
		}
	}

	if(bTestFinished)
	{
		//下发停止命令结束的情况，驱动不再主动返回消息
		ReturnTestStateEvent_TestFinish(0, 0, FALSE);
	}
#endif
	return FALSE;
}

BOOL CSttPcapReplay::EventProcessEx()
{
#ifdef _PSX_QT_LINUX_
	BOOL bTestFinished = FALSE;
	int nfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	long nRet = ioctl(nfd, 0x501, 0);

	if(nRet == REPLAY_FLAG_WRITE_FINISH)
	{
		if(m_bSendFinish)
		{
			ioctl(nfd, 0x103, 0x12);
			//开始回放
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("StartEventThread  PcapReplay"));
		}
		else
		{
			//继续下载后续回放数据
			CSttTestServerBase *pServerEngine = CSttTestServerBase::GetServerEngine();
			ASSERT(pServerEngine != NULL);
			m_nCurReqIndex++;
			pServerEngine->Comtrade_SendRequestData(m_nCurReqIndex % 2 == 0 ? 2 : 1);
		}
	}
	else if(nRet == REPLAY_FLAG_TEST_FINISH)
	{
		//实验结束中断
		if(m_nIsLoop)
		{
			if(m_nCurReplayLoopIndex++ < m_nLoopNum)
			{
				m_bInLooping = TRUE;
				ioctl(nfd, 0x146, 0);
			}
			else
			{
				ioctl(nfd, 0x103, 0);
				bTestFinished = TRUE;
			}
		}
		else
		{
			ioctl(nfd, 0x103, 0);
			bTestFinished = TRUE;
		}
	}

#endif
	return TRUE;
}

void CSttPcapReplay::Triger()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetStateTriger();
#endif
}

void CSttPcapReplay::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(this, pXmlSerialize);

	if(stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttPcapReplay::OnSendDataFinish(int nIndex, int nSendNum)
{
	//Comtrade数据发送完成命令
	UINT nSendIndex = (UINT)nIndex & 0x7FFFFFFF;

	if(nSendIndex != 0)
	{
		m_bSendFinish = ((UINT)nIndex) >> 31;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("OnSendDataFinish:nIndex=%d,nSendNum=%d"), nSendIndex, nSendNum);
	//通知接收线程数据已发送完成
	g_oSttComtradeRcvSocket.OnSendDataFinish(nSendIndex, nSendNum);
}

void CSttPcapReplay::OnSendDataStart(int nIndex, int nSendNum)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("OnSendDataStart:nIndex=%d,nSendNum=%d"), nIndex, nSendNum);
	//通知接收线程数据开始发送
	g_oSttComtradeRcvSocket.OnSendDataStart(nIndex, nSendNum);
}

void CSttPcapReplay::OnAfterMoveToComtradeBuf(int nIndex, int nDataLen)
{
	CSttTestServerBase *pServerEngine = CSttTestServerBase::GetServerEngine();
	ASSERT(pServerEngine != NULL);
	SendDataToDevice();
}

void CSttPcapReplay::StartTest()
{
	if(GetTestStarting())
	{
		return;
	}

	SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
	if(!CSttDeviceBase::g_pSttDeviceBase->m_bTestStarting)
	{
		CSttDeviceBase::g_pSttDeviceBase->m_bTestStarting = TRUE;
		pthread_mutex_unlock(&g_oTestResultMutex);
	}
	CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
	CSttTestBase::StartTest();
	//重新初始化AB缓存
	CComtradeBufMngr::g_pComtradeBufMngr->ResetBuf();
	g_oSttComtradeRcvSocket.ResetRcvLen();
	//收到开始测试命令后，根据配置参数请求数据
	CSttTestServerBase *pServerEngine = CSttTestServerBase::GetServerEngine();
	ASSERT(pServerEngine != NULL);
	pServerEngine->Comtrade_SendRequestData(m_nCurReqIndex % 2 == 0 ? 2 : 1);
}

