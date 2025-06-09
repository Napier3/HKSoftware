#include "stdafx.h"
#include "tmt_pt_test.h"
#include "../../../../Module/API/StringApi.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

void stt_init_paras(tmt_PtPara *pPara)
{
	memset(&pPara, 0, sizeof(tmt_PtPara));
	pPara->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///

void stt_xml_serialize(tmt_PtPara *pPara, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("PT1阻值","PT1","","number",pPara->m_nPT1);
	pXmlSierialize->xml_serialize("PT2阻值","PT2","","number",pPara->m_nPT2);
#else
	pXmlSierialize->xml_serialize(/*"PT1阻值"*/g_sLangTxt_Native_PT1Impedance.GetString(),"PT1","","number",pPara->m_nPT1);
	pXmlSierialize->xml_serialize(/*"PT2阻值"*/g_sLangTxt_Native_PT2Impedance.GetString(),"PT2","","number",pPara->m_nPT2);
#endif
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_PtTest()
{
	tmt_PtTest otmt_PtTest;
	otmt_PtTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
//	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&otmt_PtTest.m_oPtPara, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("PtTestDemo.xml");
	//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
