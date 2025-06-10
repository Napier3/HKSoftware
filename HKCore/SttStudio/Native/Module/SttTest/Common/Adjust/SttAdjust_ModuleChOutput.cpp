#include "stdafx.h"
#include"SttAdjust_ModuleChOutput.h"
#include "../SttSystemConfig.h"
#include "../../../SttDevice/SttDeviceBase.h"

CString CSttAdjust_ModuleChOutput::m_strMacroName = "模块单通道输出";
CString CSttAdjust_ModuleChOutput::m_strMacroID = STT_MACRO_ID_ModuleChOutput;
CString CSttAdjust_ModuleChOutput::m_strFilePostFix = "stthrt";
CString CSttAdjust_ModuleChOutput::m_strMacroVer ="1.0";

PTMT_ADJ_MODULECH_OUTPUT g_theModuleChOutPut = NULL;

CSttAdjust_ModuleChOutput::CSttAdjust_ModuleChOutput() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
	g_theModuleChOutPut = this;
}

void CSttAdjust_ModuleChOutput::Init()
{
	TMT_ADJ_MODULECH_OUTPUT::init();
}

long CSttAdjust_ModuleChOutput::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttAdjust_ModuleChOutput::~CSttAdjust_ModuleChOutput(void)
{
	g_theModuleChOutPut = NULL;
}

void CSttAdjust_ModuleChOutput::AfterSetParameter()
{
}

double CSttAdjust_ModuleChOutput::GetTestTimeLong()
{
	float fTime = TIME_ONLINE_DELAY;

	//	fTime = m_oHarmParas.m_fOutPutTime;
	//	fTime += TIME_ONLINE_DELAY;

	return fTime;
}

long CSttAdjust_ModuleChOutput::CalReport(UINT nState)
{

	return 0;
}

void CSttAdjust_ModuleChOutput::Stop()
{
	CSttTestBase::Stop();
}

long CSttAdjust_ModuleChOutput::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttAdjust_ModuleChOutput::StartTest()
{
	CSttTestBase::StartTest();
	TtmToDrv();
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetTestStart(ManualTest);
#endif

	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttAdjust_ModuleChOutput::DataDownload Finished");
}

void CSttAdjust_ModuleChOutput::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_modulechoutput(this);
#endif
}

void CSttAdjust_ModuleChOutput::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}


