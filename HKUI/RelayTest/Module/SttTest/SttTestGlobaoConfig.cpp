#include "stdafx.h"
#include "SttTestGlobaoConfig.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/API/GlobalConfigApi.h"

STT_ADJ_PARAMETER_XML_SERIAL_CONFIG g_theAdjParaXmlSerialConfig;

//////////////////////////////////////////////////////////////////////////
//

void stt_init_adj_para_config()
{
	g_theAdjParaXmlSerialConfig.init();
}

void stt_xml_serialize_adj_para_config(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_init_adj_para_config();

	memset(&g_theAdjParaXmlSerialConfig, 0, sizeof(STT_ADJ_PARAMETER_XML_SERIAL_CONFIG));

	pXmlSerialize->xml_serialize("DeviceAttrs",             "DeviceAttrs",					"","long",g_theAdjParaXmlSerialConfig.m_nDeviceAttr);
	pXmlSerialize->xml_serialize("BoutTrunOnValueDef",		"BoutTrunOnValueDef",			"","long",g_theAdjParaXmlSerialConfig.m_nBOutAttr);
	pXmlSerialize->xml_serialize("BinAdjustParas",			"BinAdjustParas",				"","long",g_theAdjParaXmlSerialConfig.m_nBinAttr);
	pXmlSerialize->xml_serialize("ModuleAttrs",             "ModuleAttrs",					"","long",g_theAdjParaXmlSerialConfig.m_nModuleAttr);
	pXmlSerialize->xml_serialize("ChMapDef",                "ChMapDef",						"","long",g_theAdjParaXmlSerialConfig.m_nModuleChDef);
	pXmlSerialize->xml_serialize("HdGears",                 "HdGears",						"","long",g_theAdjParaXmlSerialConfig.m_nModuleHdGear);
	pXmlSerialize->xml_serialize("AdjustParas",             "AdjustParas",					"","long",g_theAdjParaXmlSerialConfig.m_nModuleAdjusts);
}


//////////////////////////////////////////////////////////////////////////
//
STT_TEST_SYSTEM_STATUS_CONFIG g_theTestSystemStatusConfig;

void init_stt_test_system_status_config()
{
	g_theTestSystemStatusConfig.init();
}

void stt_xml_serialize_test_system_status_config(CSttXmlSerializeBase *pXmlSerialize)
{
	g_theTestSystemStatusConfig.init();

	stt_xml_serialize_test_system_status_config(&g_theTestSystemStatusConfig, pXmlSerialize);
}

void stt_xml_serialize_test_system_status_config(PSTT_TEST_SYSTEM_STATUS_CONFIG pConfig, CSttXmlSerializeBase *pXmlSerialize)
{
	g_theTestSystemStatusConfig.init();

	pXmlSerialize->xml_serialize("DeviceStatus",          "DeviceStatus",       "","long", pConfig->m_nDeviceStatus);
	pXmlSerialize->xml_serialize("TestStatus",             "TestStatus",          "","long", pConfig->m_nTestStatus);
	pXmlSerialize->xml_serialize("AtsStatus",               "AtsStatus",           "","long", pConfig->m_nAtsStatus);
	pXmlSerialize->xml_serialize("LiveUpdateStatus",     "LiveUpdateStatus",  "","long", pConfig->m_nLiveUpdateStatus);
}
