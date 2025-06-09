#include "stdafx.h"
#include "SttPID16Test.h"
#include "../../SttDevice/SttDeviceBase.h"

CString CSttPid16Test::m_strMacroName = "PID16测试";
CString CSttPid16Test::m_strMacroID = STT_MACRO_ID_Pid16Test;
CString CSttPid16Test::m_strFilePostFix = "sttptt";
CString CSttPid16Test::m_strMacroVer ="1.0";

CSttPid16Test::CSttPid16Test()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttPid16Test::Init()
{
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

CSttPid16Test::~CSttPid16Test(void)
{

}

void CSttPid16Test::AfterSetParameter()
{	

}

BOOL CSttPid16Test::EventProcess()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProPid01DrvResult();
#endif
	return FALSE;
}

void CSttPid16Test::StartTest()
{
	CSttTestBase::StartTest();
    CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttPid16Test::DataDownload Finished");
	TtmToDrv();
}

void CSttPid16Test::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
    tmt_Pid16Para *p=this;
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_pid16(p);
#endif
}

void CSttPid16Test::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    pXmlSerialize->xml_serialize("硬件切换动作预留时间(单位秒,最小1秒最大5秒)","OutputTime","","number",this->m_fOutputTime);
    CString strID;
    for(int nIndex = 0; nIndex < 16; nIndex++)
    {
        strID.Format("_Bout%d",nIndex+1);
        pXmlSerialize->xml_serialize("",strID.GetString(),"","DOutputState",m_binOut[nIndex].nState);
    }
}
