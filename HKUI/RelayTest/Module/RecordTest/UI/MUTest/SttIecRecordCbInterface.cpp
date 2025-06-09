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

void CSttIecRecordCbInterface::InitIecRecordCb(const CString &strIecFunc){}//用于区分录波存储模式还是非存储模式
void CSttIecRecordCbInterface::SetSelectedCbs(CExBaseList *pSelectedCbs){}
void CSttIecRecordCbInterface::Ats_IecRecord(BOOL bIsFromIecfgFile){}
//	virtual void Connect_UpdateMUTimeAccurRlt(BOOL bCoonect){}
void CSttIecRecordCbInterface::SetEnable_BtnBack(bool bEnable){}

void CSttIecRecordCbInterface::Update_IecRcdTimer()
{

}

void CSttIecRecordCbInterface::UpdateWriteFileTimeAndFileSize(long nTimeMs,long nFileSize)
{

}

void CSttIecRecordCbInterface::UpdateFirstCirclePlot(long nChSetModifyType)
{

}
