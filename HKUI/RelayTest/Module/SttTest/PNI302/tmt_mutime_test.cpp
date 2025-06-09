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
	pXmlSierialize->xml_serialize("逻辑类型","Logic","","number",pPara->m_nLogic);
	pXmlSierialize->xml_serialize("边沿触发方式","Rising","","number",pPara->m_nRising);
	pXmlSierialize->xml_serialize("持续秒数","Sec","","number",pPara->m_nSec);
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

