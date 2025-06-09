#include "stdafx.h"
#include "SttModulesGearSwitch.h"
#include "tmt_adjust_sys_parameter.h"
#include "tmt_common_def.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

CString CSttModulesGearSwitch::m_strMacroName = "Ä£¿éµµÎ»ÇÐ»»";
CString CSttModulesGearSwitch::m_strMacroID = STT_MACRO_ID_ModulesGearSwitch;

CSttModulesGearSwitch::CSttModulesGearSwitch()
{
    m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
}

CSttModulesGearSwitch::~CSttModulesGearSwitch(void)
{

}

void CSttModulesGearSwitch::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_ModulesGearSwitch(g_theSystemConfig, pXmlSerialize);
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetCurMergeConfig();
#endif
}

void CSttModulesGearSwitch::StartTest()
{
	ReturnTestStateEvent_TestFinish(0,0,FALSE);
}
