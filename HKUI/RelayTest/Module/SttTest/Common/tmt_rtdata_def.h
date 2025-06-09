#pragma once

#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"

typedef struct tmt_rtdata_ch
{
public:
	long  m_nIndex;//U1~U48,I1~I48
	float m_fMag;
	float m_fAng;
	float m_fFreq;//考虑到频率递变时使用	

public:
	void init()
	{
		m_fMag = 0;
		m_fAng = 0;
		m_fFreq = 50;
	}

	tmt_rtdata_ch()	{	init();	}
}tmt_RtDataCh;

typedef struct tmt_rtdata_chs
{
public:
	tmt_RtDataCh m_oVolCh[MAX_VOLTAGE_COUNT];
	tmt_RtDataCh m_oCurCh[MAX_CURRENT_COUNT];
	int m_nCurChCount;//当前电流通道数
	int m_nVolChCount;//当前电压通道数
	double m_dTime;//绝对时间
	double m_dRealTime;//相对时间
public:
	void init()
	{
		for (int nIndex = 0;nIndex<MAX_VOLTAGE_COUNT;nIndex++)
		{
			m_oVolCh[nIndex].m_nIndex=nIndex;
			m_oVolCh[nIndex].init();
		}

		for (int nIndex = 0;nIndex<MAX_CURRENT_COUNT;nIndex++)
		{
			m_oCurCh[nIndex].m_nIndex=nIndex;
			m_oCurCh[nIndex].init();
		}

		m_nCurChCount = 0;
		m_nVolChCount = 0;
		m_dTime = 0;
		m_dRealTime = 0;
	}

	tmt_rtdata_chs()	{	init();	}
}tmt_RtDataChs;

typedef struct stt_time
{
	double dTime;   //绝对时刻
	double dRealTime;    //相对时间
	double dBinActTime;    //开入动作时间
}STT_TIME, *PSTT_TIME;

typedef struct stt_rtdata_event_info
{
	long m_nIndex;
	float m_fMag;
	float m_fAng;
	float m_fFreq;
}STT_RTDATA_EVENT_INFO, *PSTT_RTDATA_EVENT_INFO;

typedef struct stt_rtdata_event
{
	STT_RTDATA_EVENT_INFO m_oVolCh[MAX_VOLTAGE_COUNT];
	STT_RTDATA_EVENT_INFO m_oCurCh[MAX_CURRENT_COUNT];
	int m_nCurChCount;//当前电流通道数
	int m_nVolChCount;//当前电压通道数
	STT_RTDATA_EVENT_INFO m_oFaultVolCh;//高级模块矢量
	STT_RTDATA_EVENT_INFO m_oFaultCurCh;
	STT_RTDATA_EVENT_INFO m_oFaultZCh;
	int m_nHasFaultVolCur;
	STT_TIME   oTime;
}STT_RTDATA_EVENT, *PSTT_RTDATA_EVENT;

void stt_xml_serialize_write_RtDataChs(long nCurChNum,long nVolChNum);
void stt_xml_serialize_rtdata(PSTT_RTDATA_EVENT pRtData, CSttXmlSerializeBase *pXmlSierialize);


