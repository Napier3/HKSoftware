#include "stdafx.h"
#include "tmt_ied_test.h"


void stt_init_paras(tmt_IEDTest *pPara)
{
	memset(&pPara, 0, sizeof(MAX_STATE_COUNT));
	pPara->init();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///

void stt_xml_serialize(tmt_IEDParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("状态数","StateCount","","number",pParas->m_nStateCount);
	pXmlSierialize->xml_serialize("加量方式","DataMode","","number",pParas->m_nDataMode);
	pXmlSierialize->xml_serialize("实验类型","TestType","","number",pParas->m_nTestType);
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_IEDTest()
{
	tmt_IEDTest oIEDTest;
	oIEDTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	//pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oIEDTest.m_oIEDParas, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("IEDTestDemo.xml");
	//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

