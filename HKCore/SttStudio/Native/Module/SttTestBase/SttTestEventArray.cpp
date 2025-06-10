#include "StdAfx.h"
#include "SttTestEventArray.h"
#include "../SttCmd/SttSysState.h"
#include "../SttTest/Common/SttSystemConfig.h"

//////////////////////////////////////////////////////////////////////////
//STT_TEST_EVENT_CYCLE_ARRAY
//2020-10-22  lijunqing 
PSTT_TEST_EVENT_CYCLE_ARRAY g_theSttTestEventCycleArray = NULL;
PSTT_RtDatas_CYCLE_ARRAY g_theSttRtDatasCycleArray = NULL;

void stt_create_test_event_cycle_array()
{
	if (g_theSttTestEventCycleArray == NULL)
	{
		g_theSttTestEventCycleArray = (PSTT_TEST_EVENT_CYCLE_ARRAY)malloc(sizeof(STT_TEST_EVENT_CYCLE_ARRAY));
		memset(g_theSttTestEventCycleArray, 0, sizeof(STT_TEST_EVENT_CYCLE_ARRAY));
		g_theSttTestEventCycleArray->m_nMaxCount = STT_TEST_EVENT_MAX_COUNT;
	}
}

void stt_free_test_event_cycle_array()
{
	if (g_theSttTestEventCycleArray != NULL)
	{
		free(g_theSttTestEventCycleArray);
		g_theSttTestEventCycleArray = NULL;
	}
}

void stt_create_rtdatas_cycle_array()
{
	if (g_theSttRtDatasCycleArray == NULL)
	{
		g_theSttRtDatasCycleArray = (PSTT_RtDatas_CYCLE_ARRAY)malloc(sizeof(STT_RtDatas_CYCLE_ARRAY));
//		memset(g_theSttRtDatasCycleArray, 0, sizeof(STT_RtDatas_CYCLE_ARRAY));
		g_theSttRtDatasCycleArray->m_nMaxCount = GRADIENT_MAX_COUNT+10;
	}
}

void stt_free_rtdatas_cycle_array()
{
	if (g_theSttRtDatasCycleArray != NULL)
	{
		free(g_theSttRtDatasCycleArray);
		g_theSttRtDatasCycleArray = NULL;
	}
}

void stt_clear_test_event_cycle_array()
{
	if (g_theSttTestEventCycleArray != NULL)
	{
		g_theSttTestEventCycleArray->m_nCurrCount = 0;
		g_theSttTestEventCycleArray->m_nCurrReadIndex = 0;
		g_theSttTestEventCycleArray->m_nCurrIndex = 0;
	}
}
//void stt_add_test_event(int nType,int nStateIndex, int nStepIndex, int nChannel, int nValue, double dTime, double dRealTime)
//{
//	PSTT_TEST_EVENT pEvent = &g_theSttTestEventCycleArray->bufEvent[g_theSttTestEventCycleArray->m_nCurrIndex];

//	pEvent->nType = nType;
//	pEvent->nStateIndex= nStateIndex;
//	pEvent->nStepIndex= nStepIndex;
//	pEvent->nChannel=nChannel;
//	pEvent->nValue=nValue;
//	pEvent->oTime.dTime=dTime;
//	pEvent->oTime.dRealTime=dRealTime;

//	stt_cycle_buffer_increase_curr_index(g_theSttTestEventCycleArray);
//}

void stt_add_test_event(STT_TEST_EVENT obufEvent)
{
	PSTT_TEST_EVENT pEvent = &g_theSttTestEventCycleArray->bufEvent[g_theSttTestEventCycleArray->m_nCurrIndex];

//	pEvent->nType = nType;
//	pEvent->nStateIndex= nStateIndex;
//	pEvent->nStepIndex= nStepIndex;
//	pEvent->nChannel=nChannel;
//	pEvent->nValue=nValue;
//	pEvent->oTime.dTime=dTime;
//	pEvent->oTime.dRealTime=dRealTime;

	memcpy(pEvent,&obufEvent,sizeof(STT_TEST_EVENT));
	stt_cycle_buffer_increase_curr_index(g_theSttTestEventCycleArray);
}

void stt_add_iec_detect_event(int nType,STT_IEC_DETECT oIecDetect)
{
	PSTT_TEST_EVENT pEvent = &g_theSttTestEventCycleArray->bufEvent[g_theSttTestEventCycleArray->m_nCurrIndex];

	pEvent->oEventInfo[0].nType= nType;
	memcpy(&pEvent->oEventInfo[0].oIecDetect,&oIecDetect,sizeof(STT_IEC_DETECT));

	stt_cycle_buffer_increase_curr_index(g_theSttTestEventCycleArray);
}

long stt_get_test_event_count()
{
	return stt_cycle_buffer_get_read_count(g_theSttTestEventCycleArray);
}

void stt_xml_serialize_test_events(PSTT_TEST_EVENT pEvent, CSttXmlSerializeBase *pXmlSerialize)
{
	CString strID=_T("Event");
	if(pEvent->nEventInfoCnt>0)
	{
		if(pEvent->oEventInfo[0].nType==SttResult_Type_Bin||pEvent->oEventInfo[0].nType==SttResult_Type_BinEx)
			strID=SYS_STATE_XEVENT_EVENTID_BIN;
		else if(pEvent->oEventInfo[0].nType==SttResult_Type_Bout||pEvent->oEventInfo[0].nType==SttResult_Type_BoutEx)
			strID=SYS_STATE_XEVENT_EVENTID_BOUT;
	}
	else
		return;

	CSttXmlSerializeBase *pXmlEvent = pXmlSerialize->xml_serialize("Event", strID.GetString(), "Event", stt_ParaGroupKey());

	if (pXmlEvent == NULL)
	{
		return;
	}

    char pszValue[64], pszID[32];
	stt_xml_serialize_test_events_time(pXmlEvent, &pEvent->oTime);

	BOOL bStateStepIndex=FALSE;
	for(int nEventIndex=0;nEventIndex<pEvent->nEventInfoCnt;nEventIndex++)
	{
		STT_TEST_EVENT_INFO oEventInfo=pEvent->oEventInfo[nEventIndex];
		if(!bStateStepIndex)
		{
			//同类消息只添加一次CurrStateIndex CurrStepIndex
			if (oEventInfo.nStateIndex > -1)
			{
				pXmlEvent->xml_serialize("CurrStateIndex","CurrStateIndex","","long", oEventInfo.nStateIndex);
                pXmlEvent->xml_serialize("CurrStateNum","CurrStateNum","","long", oEventInfo.nStateNum);
			}
			if (oEventInfo.nStepIndex > -1)
			{
				pXmlEvent->xml_serialize("CurrStepIndex","CurrStepIndex","","long", oEventInfo.nStepIndex);
			}
			bStateStepIndex=TRUE;
		}

		switch(oEventInfo.nType)
		{
		case SttResult_Type_Bin:
		{
			sprintf(pszID, "Bin%03d", oEventInfo.nChannel);
			sprintf(pszValue, "%d", oEventInfo.nValue);
			pXmlEvent->xml_serialize(pszID, pszID, "", "long", pszValue);
		}
			break;
		case SttResult_Type_BinEx:
		{
			sprintf(pszID, "BinEx%03d", oEventInfo.nChannel);
			sprintf(pszValue, "%d", oEventInfo.nValue);
			pXmlEvent->xml_serialize(pszID, pszID, "", "long", pszValue);
		}
			break;
		case SttResult_Type_StateChange:
		{
            pXmlEvent->xml_serialize("StateChange","StateChange","","long", oEventInfo.nStateNum);
		}
			break;
		case SttResult_Type_Ramp_BfFault:
		{
			pXmlEvent->xml_serialize("PreFault","PreFault","","long", "1");//代表当前为故障前状态
		}
			break;
		case SttResult_Type_Ramp_Fault:
		{
			pXmlEvent->xml_serialize("PreFault","PreFault","","long", "0");//代表当前为故障状态
		}
			break;
		case SttResult_Type_PPSTime:
		{
			sprintf(pszID, "PPSTime%03d", oEventInfo.nStateIndex);
			sprintf(pszValue, "%d", oEventInfo.nValue);
			pXmlEvent->xml_serialize(pszID, pszID, "", "long", pszValue);
		}
			break;
		case SttResult_Type_IEC_DETECT:
		{
			CSttXmlSerializeBase *pXmlDataEvent=pXmlEvent->xml_serialize("","IEC_DETECT","IECDETECT");
			pXmlDataEvent->xml_serialize("AppID","AppID","","long",oEventInfo.oIecDetect.nAppid, stt_ValueKey());
			pXmlDataEvent->xml_serialize("CRC", "CRC","","long",oEventInfo.oIecDetect.nCrc, stt_ValueKey());
			pXmlDataEvent->xml_serialize("FiberIndex","FiberIndex","","long",oEventInfo.oIecDetect.nPort, stt_ValueKey());
			pXmlDataEvent->xml_serialize("IecType","IecType","","long",oEventInfo.oIecDetect.nType, stt_ValueKey());
		}
			break;
		case SttResult_Type_Bout:
		{
			sprintf(pszID, "Bout%03d", oEventInfo.nChannel);
			sprintf(pszValue, "%d", oEventInfo.nValue);
			pXmlEvent->xml_serialize(pszID, pszID, "", "long", pszValue);
		}
			break;
		case SttResult_Type_BoutEx:
		{
			sprintf(pszID, "BoutEx%03d", oEventInfo.nChannel);
			sprintf(pszValue, "%d", oEventInfo.nValue);
			pXmlEvent->xml_serialize(pszID, pszID, "", "long", pszValue);
		}
			break;
		case SttResult_Type_Swing_Swing:
		{
			pXmlEvent->xml_serialize("Swing","Swing_Shake","","long", "1");
		}
			break;
		case SttResult_Type_Swing_Fault:
		{
			pXmlEvent->xml_serialize("Swing","Swing_Fault","","long", "1");
		}
			break;
		default:
			break;
		}
	}
}

void stt_xml_serialize_test_events(CSttXmlSerializeBase *pXmlSerialize, long nBegin, long nEnd)
{
	if (nBegin==-1 || nEnd == -1)
	{
		return;
	}

	for (long k=nBegin; k<= nEnd; k++)
	{
		stt_xml_serialize_test_events(&g_theSttTestEventCycleArray->bufEvent[k], pXmlSerialize);
	}

	stt_cycle_buffer_set_read_index(g_theSttTestEventCycleArray, nEnd+1);
}

void stt_xml_serialize_test_events(CSttXmlSerializeBase *pXmlSerialize)
{
	long nBegin1 = -1;
	long nEnd1 = -1;
	long nBegin2 = -1;
	long nEnd2 = -1;

	stt_get_read_index_range(g_theSttTestEventCycleArray, nBegin1, nEnd1, nBegin2, nEnd2);

	stt_xml_serialize_test_events(pXmlSerialize, nBegin1, nEnd1);
	stt_xml_serialize_test_events(pXmlSerialize, nBegin2, nEnd2);
}

void stt_xml_serialize_test_events_time(CSttXmlSerializeBase *pXmlSerialize, PSTT_TIME pSttTime)
{
	if (pSttTime == NULL)
	{
		return;
	}

	char pszValue[64];

	if (pSttTime->dTime > 0)
	{
        double dLocalTime = pSttTime->dTime + g_theSystemConfig->m_nTimeZone*3600;
        sprintf(pszValue, "%.9f", dLocalTime);
		pXmlSerialize->xml_serialize("绝对时间","Time","","time", pszValue);
#ifdef _PSX_QT_LINUX_
        long nLTime_s = dLocalTime;
        double nLTime_ns = dLocalTime - nLTime_s;
//        QDateTime oDate = QDateTime::fromTime_t(nLTime_s);
//        CString strDate = oDate.toString("yyyy-MM-dd hh:mm:ss.");
        short nYear,nMon,nDay,nHour,nMin,nSec;
        CString strDate;
        TransTimer_t(nLTime_s,nYear,nMon,nDay,nHour,nMin,nSec);
        strDate.Format("%04d-%02d-%02d %02d:%02d:%02d.",nYear,nMon,nDay,nHour,nMin,nSec);

        sprintf(pszValue, "%09d", (long)(nLTime_ns*1000000000));
        CString strTime(pszValue);
        strDate += strTime;
        pXmlSerialize->xml_serialize("绝对时间","TimeStr","","string", strDate);
#endif
	}

	sprintf(pszValue, "%.9f", pSttTime->dRealTime);
	pXmlSerialize->xml_serialize("相对时间","RealTime","","double", pszValue);

	if (pSttTime->dBinActTime > 0)
	{
		sprintf(pszValue, "%.9f", pSttTime->dBinActTime);
		pXmlSerialize->xml_serialize("开入动作时间","BinActTime","","double", pszValue);
	}
}

//void stt_xml_serialize_test_events_time(CSttXmlSerializeBase *pXmlSerialize, long nUtc_s, long nUtc_ns)
//{
//	pXmlSerialize->xml_serialize("Utc_s","Utc_s","","long", nUtc_s);
//    pXmlSerialize->xml_serialize("Utc_ns","Utc_ns","","long", nUtc_ns);
//}

void stt_test_event_set_lock(long nLockFlag)
{
	g_theSttTestEventCycleArray->m_nLockFlag = nLockFlag;
}

long stt_test_event_set_is_lock()
{
	return g_theSttTestEventCycleArray->m_nLockFlag;
}

void stt_add_rtdatas(STT_RTDATA_EVENT oRtdata)
{
	PSTT_RTDATA_EVENT pRtDataEvent = &g_theSttRtDatasCycleArray->bufRtdata[g_theSttRtDatasCycleArray->m_nCurrIndex];
	memcpy(pRtDataEvent,&oRtdata,sizeof(STT_RTDATA_EVENT));
//	pRtDataEvent->oTime.dTime=oRtdata.oTime.dTime;
//	pRtDataEvent->oTime.dRealTime=oRtdata.oTime.dRealTime;
//	pRtDataEvent->m_nCurChCount=oRtdata.m_nCurChCount;
//	pRtDataEvent->m_nVolChCount=oRtdata.m_nVolChCount;

//	for(int nIndex=0;nIndex<pRtDataEvent->m_nCurChCount;nIndex++)
//	{
//		pRtDataEvent->m_oCurCh[nIndex].m_nMag=oRtdata.m_oCurCh[nIndex].m_nMag;
//		pRtDataEvent->m_oCurCh[nIndex].m_nAng=oRtdata.m_oCurCh[nIndex].m_nAng;
//		pRtDataEvent->m_oCurCh[nIndex].m_nFreq=oRtdata.m_oCurCh[nIndex].m_nFreq;
//		pRtDataEvent->m_oCurCh[nIndex].m_nIndex=oRtdata.m_oCurCh[nIndex].m_nIndex;
//	}

//	for(int nIndex=0;nIndex<pRtDataEvent->m_nVolChCount;nIndex++)
//	{
//		pRtDataEvent->m_oVolCh[nIndex].m_nMag=oRtdata.m_oVolCh[nIndex].m_nMag;
//		pRtDataEvent->m_oVolCh[nIndex].m_nAng=oRtdata.m_oVolCh[nIndex].m_nAng;
//		pRtDataEvent->m_oVolCh[nIndex].m_nFreq=oRtdata.m_oVolCh[nIndex].m_nFreq;
//		pRtDataEvent->m_oVolCh[nIndex].m_nIndex=oRtdata.m_oVolCh[nIndex].m_nIndex;
//	}

	stt_cycle_buffer_increase_curr_index(g_theSttRtDatasCycleArray);
}

long stt_get_rtdatas_count()
{
	if(g_theSttRtDatasCycleArray == NULL)
	{
		return 0;
	}
	else
	{
		return stt_cycle_buffer_get_read_count(g_theSttRtDatasCycleArray);
	}
}

void stt_xml_serialize_rtdatas(CSttXmlSerializeBase *pXmlSerialize, long nBegin, long nEnd)
{
	if (nBegin==-1 || nEnd == -1)
	{
		return;
	}

	for (long k=nBegin; k<= nEnd; k++)
	{
		stt_xml_serialize_rtdata(&g_theSttRtDatasCycleArray->bufRtdata[k], pXmlSerialize);
	}

	stt_cycle_buffer_set_read_index(g_theSttRtDatasCycleArray, nEnd+1);
}

void stt_xml_serialize_rtdatas(CSttXmlSerializeBase *pXmlSerialize)
{
	long nBegin1 = -1;
	long nEnd1 = -1;
	long nBegin2 = -1;
	long nEnd2 = -1;

	stt_get_read_index_range(g_theSttRtDatasCycleArray, nBegin1, nEnd1, nBegin2, nEnd2);

	stt_xml_serialize_rtdatas(pXmlSerialize, nBegin1, nEnd1);
	stt_xml_serialize_rtdatas(pXmlSerialize, nBegin2, nEnd2);
}

