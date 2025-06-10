#include "SttIecRecordCbInterface.h"

CSttIecRecordCbInterface *g_pSttIecRecordCbWidget = NULL;

CSttIecRecordCbInterface::CSttIecRecordCbInterface(void)
{
	m_bMUTestMode = false;
	m_pSVDelayData = NULL;
	m_fIecRcdTimer = STT_IEC_RECORD_TIMER_DEFAULT_VALUE;
	m_pSelectedCbs = NULL; 
	m_bStopTimerUpdate = FALSE;
}

CSttIecRecordCbInterface::~CSttIecRecordCbInterface(void)
{
}

void CSttIecRecordCbInterface::Update_IecRcdTimer()
{

}

void CSttIecRecordCbInterface::UpdateWriteFileTimeAndFileSize(long nTimeMs,long nFileSize)
{

}

void CSttIecRecordCbInterface::UpdateFirstCirclePlot(long nChSetModifyType)
{

}
