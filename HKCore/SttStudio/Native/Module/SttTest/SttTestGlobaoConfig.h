#ifndef _SttTestGlobaoConfig_H_
#define _SttTestGlobaoConfig_H_

#include "../SttTestBase/SttXmlSerialize.h"

//2020-10-21  lijunqing 
//XML串行化参数，用于区分是串行化整个校准系数文件或者是部分
typedef struct stt_adj_parameter_xml_serial_config
{
	long m_nDeviceAttr;
	long m_nBOutAttr;
	long m_nBinAttr;
	long m_nModuleAttr;
	long m_nModuleChDef;
	long m_nModuleHdGear;
	long m_nModuleAdjusts;

	void init()
	{
		m_nDeviceAttr = 1;
		m_nBOutAttr = 1;
		m_nBinAttr = 1;
		m_nModuleAttr = 1;
		m_nModuleChDef = 1;
		m_nModuleHdGear = 1;
		m_nModuleAdjusts = 1;
	}

	long has_module()
	{
		return ((m_nModuleAttr != 0) || (m_nModuleChDef != 0) || (m_nModuleHdGear != 0) || (m_nModuleAdjusts != 0));
	}
}STT_ADJ_PARAMETER_XML_SERIAL_CONFIG, *PSTT_ADJ_PARAMETER_XML_SERIAL_CONFIG;

extern STT_ADJ_PARAMETER_XML_SERIAL_CONFIG g_theAdjParaXmlSerialConfig;

void stt_init_adj_para_config();
void stt_xml_serialize_adj_para_config(CSttXmlSerializeBase *pXmlSerialize);


//////////////////////////////////////////////////////////////////////////
//
typedef struct stt_test_system_status_config
{
	long m_nDeviceStatus;
	long m_nTestStatus;
	long m_nAtsStatus;
	long m_nLiveUpdateStatus;

	void init()
	{
		m_nDeviceStatus = 0;
		m_nTestStatus = 0;
		m_nAtsStatus = 0;
		m_nLiveUpdateStatus = 0;
	}
}STT_TEST_SYSTEM_STATUS_CONFIG, *PSTT_TEST_SYSTEM_STATUS_CONFIG;

extern STT_TEST_SYSTEM_STATUS_CONFIG g_theTestSystemStatusConfig;

void init_stt_test_system_status_config();
void stt_xml_serialize_test_system_status_config(CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_test_system_status_config(PSTT_TEST_SYSTEM_STATUS_CONFIG pConfig, CSttXmlSerializeBase *pXmlSerialize);

#endif // _SttTestGlobaoConfig_H_

