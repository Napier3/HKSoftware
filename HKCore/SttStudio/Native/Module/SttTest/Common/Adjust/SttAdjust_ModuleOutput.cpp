#include "stdafx.h"
#include"SttAdjust_ModuleOutput.h"
#include "../SttSystemConfig.h"
#include "../../../SttDevice/SttDeviceBase.h"

CString CSttAdjust_ModuleOutput::m_strMacroName = "模块输出";
CString CSttAdjust_ModuleOutput::m_strMacroID = STT_MACRO_ID_ModuleOutput;
CString CSttAdjust_ModuleOutput::m_strFilePostFix = "stthrt";
CString CSttAdjust_ModuleOutput::m_strMacroVer ="1.0";

PTMT_ADJ_MODULE_OUTPUT g_theModuleOutPut = NULL;

CSttAdjust_ModuleOutput::CSttAdjust_ModuleOutput() : CSttTestBase()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    Init();
    g_theModuleOutPut = this;
}

void CSttAdjust_ModuleOutput::Init()
{
    TMT_ADJ_MODULE_OUTPUT::init();
}

long CSttAdjust_ModuleOutput::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    return 0;
}

CSttAdjust_ModuleOutput::~CSttAdjust_ModuleOutput(void)
{
    g_theModuleOutPut = NULL;
}

void CSttAdjust_ModuleOutput::AfterSetParameter()
{
}

double CSttAdjust_ModuleOutput::GetTestTimeLong()
{
    float fTime = TIME_ONLINE_DELAY;

    //	fTime = m_oHarmParas.m_fOutPutTime;
    //	fTime += TIME_ONLINE_DELAY;

    return fTime;
}

long CSttAdjust_ModuleOutput::CalReport(UINT nState)
{

    return 0;
}

void CSttAdjust_ModuleOutput::Stop()
{
    CSttTestBase::Stop();
#ifdef _PSX_QT_LINUX_
#ifdef _Board_PNS330
    int nfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
    ioctl(nfd, PNS330_RegAddr_AnalogCtrl, 0);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
}

long CSttAdjust_ModuleOutput::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttAdjust_ModuleOutput::StartTest()
{
    CSttTestBase::StartTest();
    TtmToDrv();
    SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->SetTestStart(ManualTest);
#endif

    CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttAdjust_ModuleOutput::StartTest >>>>>>");
}

void CSttAdjust_ModuleOutput::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_moduleoutput(this);
#endif
}

void CSttAdjust_ModuleOutput::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(this,pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}


