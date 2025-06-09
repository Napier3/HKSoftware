#include "stdafx.h"
#include "SttAuxDCOutput.h"
#include "tmt_adjust_sys_parameter.h"
#include "tmt_common_def.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

CString CSttAuxDCOutput::m_strMacroName = "辅助直流输出设置";
CString CSttAuxDCOutput::m_strMacroID = STT_MACRO_ID_AuxDCOutput;

CSttAuxDCOutput::CSttAuxDCOutput()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
}

CSttAuxDCOutput::~CSttAuxDCOutput(void)
{

}

void CSttAuxDCOutput::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_AuxDC(g_theSystemConfig,pXmlSerialize);

#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetAuxDcVolt(g_theSystemConfig->m_fAuxDC_Vol);
#endif
}

void CSttAuxDCOutput::StartTest()
{
	ReturnTestStateEvent_TestFinish(0,0,FALSE);
}
