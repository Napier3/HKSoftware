#include "stdafx.h"
#include "tmt_common_def.h"
#include "SttLcPowerTest.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLcPowerTest::m_strMacroName = "光模块功率";
CString CSttLcPowerTest::m_strMacroID = STT_MACRO_ID_LcPowerTest;

CSttLcPowerTest::CSttLcPowerTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
}

CSttLcPowerTest::~CSttLcPowerTest(void)
{

}

void CSttLcPowerTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_LcPower();
#endif
}
