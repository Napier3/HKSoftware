#include "stdafx.h"
#include "SttAppRatesConfig.h"
#include "tmt_adjust_sys_parameter.h"
#include "tmt_common_def.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

CSttAppRatesConfig g_theAppRatesConfig;
CString CSttAppRatesConfig::m_strMacroName = "≤‚ ‘“«±‰±»≈‰÷√";
CString CSttAppRatesConfig::m_strMacroID = STT_MACRO_ID_AppConfig;

CSttAppRatesConfig::CSttAppRatesConfig()
{

}

CSttAppRatesConfig::~CSttAppRatesConfig(void)
{

}

void CSttAppRatesConfig::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_AppConfig(g_theSystemConfig,pXmlSerialize);
}
