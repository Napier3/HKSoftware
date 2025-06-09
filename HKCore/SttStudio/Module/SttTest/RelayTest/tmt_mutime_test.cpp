#include "stdafx.h"
#include "tmt_mutime_test.h"


void stt_init_paras(tmt_MUTIMEPara *pPara)
{
	memset(&pPara, 0, sizeof(tmt_MUTIMEPara));
	pPara->init();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///

void stt_xml_serialize(tmt_MUTIMEPara *pPara, CSttXmlSerializeBase *pXmlSierialize)
{
	//pXmlSierialize->xml_serialize("状态数","StateCount","","number",pParas->m_nStateCount);
	//pXmlSierialize->xml_serialize("加量方式","DataMode","","number",pParas->m_nDataMode);
	//pXmlSierialize->xml_serialize("实验类型","TestType","","number",pParas->m_nTestType);
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_MUTimeTest()
{
	tmt_MUTIMETest oMUTIMETest;
	oMUTIMETest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	//pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oMUTIMETest.m_oMUTIMEPara, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("MUTimeTestDemo.xml");
	//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

