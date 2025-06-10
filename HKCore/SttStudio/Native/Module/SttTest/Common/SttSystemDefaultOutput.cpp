#include "stdafx.h"
#include "SttSystemDefaultOutput.h"
#ifdef _PSX_IDE_QT_
#include "../../SttDevice/SttDeviceBase.h"
#endif

CSttSystemDefaultOutput g_theSystemDefaultOutput;

CString CSttSystemDefaultOutput::m_strMacroName = "系统默认输出";
CString CSttSystemDefaultOutput::m_strMacroID = STT_MACRO_ID_SystemDefaultOutput;

CSttSystemDefaultOutput::CSttSystemDefaultOutput()
{

}

CSttSystemDefaultOutput::~CSttSystemDefaultOutput(void)
{

}

void CSttSystemDefaultOutput::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	this->init();
	stt_xml_serialize(this,pXmlSerialize);
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_systemdefaultoutput(this);
#endif
	if(m_bUseSysOutput)
	{
		StartTest();
	}
	else
	{
		StopTest();
	}
}

void CSttSystemDefaultOutput::StartTest()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetTestStart(SystemDefaultOutput);
#endif
}

void CSttSystemDefaultOutput::StopTest()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop(TRUE);
#endif
}
