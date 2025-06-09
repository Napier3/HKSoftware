#include "SttIecRecordCbInterface.h"

CSttIecRecordCbInterface *g_pSttIecRecordCbWidget = NULL;

CSttIecRecordCbInterface::CSttIecRecordCbInterface(void)
{
	m_bMUTestMode = false;
	m_pSVDelayData = NULL;
	m_fIecRcdTimer = STT_IEC_RECORD_TIMER_DEFAULT_VALUE;
}

CSttIecRecordCbInterface::~CSttIecRecordCbInterface(void)
{
}

void CSttIecRecordCbInterface::Update_IecRcdTimer()
{

}