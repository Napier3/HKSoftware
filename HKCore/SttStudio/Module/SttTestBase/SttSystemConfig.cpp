#include "stdafx.h"
#include "SttSystemConfig.h"
#include "tmt_adjust_sys_parameter.h"
#include "tmt_common_def.h"
#include "../../SttTestBase/SttComplexp.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

CSttDevSystemParas *g_theSystemConfig=NULL;
CString CSttDevSystemParas::m_strMacroName = "ϵͳ��������";
CString CSttDevSystemParas::m_strMacroID = STT_MACRO_ID_SystemConfig;

CSttDevSystemParas::CSttDevSystemParas()
{

}

CSttDevSystemParas::~CSttDevSystemParas(void)
{

}

void CSttDevSystemParas::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(g_theSystemConfig,pXmlSerialize);//��������ʽ���²���

    //20221209 zhoulei ��Ӧ�Զ���������ָ��GOOSE��չ��������
#ifdef _PSX_QT_LINUX_
    SwitchModules oSwitchModules=CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

    if(g_theSystemConfig->m_nRprtUseBinExCnt == 0)
    {
        g_nBinExCount = oSwitchModules.m_nModulesBiCount;
    }
    else
    {
        g_nBinExCount = g_theSystemConfig->m_nRprtUseBinExCnt;
    }
	CSttDeviceBase::g_pSttDeviceBase->SetSystemConfig();
    CSttDeviceBase::g_pSttDeviceBase->SetAuxDcVolt(g_theSystemConfig->m_fAuxDC_Vol);
#else
	g_nBinExCount = g_theSystemConfig->m_nRprtUseBinExCnt;
#endif

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("PowerMode=%d"),g_theSystemConfig->m_oIPowerMode.m_nIPowerMode);
//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("VoltSet=%2.1f"),g_theSystemConfig->m_oIPowerMode.m_fVoltSet);
}
