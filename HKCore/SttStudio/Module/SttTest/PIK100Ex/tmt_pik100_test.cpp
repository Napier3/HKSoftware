#include "stdafx.h"
#include "tmt_pik100_test.h"
#include "../../../../Module/API/StringApi.h"
#include "qdebug.h"

void stt_init_paras(tmt_Pik100Para *pPara)
{
	memset(&pPara, 0, sizeof(tmt_Pik100Para));
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

void stt_xml_serialize(tmt_Pik100Para *pPara, CSttXmlSerializeBase *pXmlSierialize)
{

	CSttXmlSerializeBase *pSerializePara =pXmlSierialize->xml_serialize("实验参数", "DAValue", "DAValue", stt_ParaGroupKey());
	if (pSerializePara == NULL)
	{
		return;
	}
	pSerializePara->xml_serialize("","StateStart","","number",pPara->m_oDA.StateStart);
	pSerializePara->xml_serialize("","K1","","number",pPara->m_oDA.K1);
	pSerializePara->xml_serialize("","K2","","number",pPara->m_oDA.K2);
	pSerializePara->xml_serialize("","K3","","number",pPara->m_oDA.K3);
	pSerializePara->xml_serialize("","K4","","number",pPara->m_oDA.K4);
	pSerializePara->xml_serialize("","K5","","number",pPara->m_oDA.K5);
	pSerializePara->xml_serialize("","K6","","number",pPara->m_oDA.K6);
	pSerializePara->xml_serialize("","K7","","number",pPara->m_oDA.K7);
	pSerializePara->xml_serialize("","K8","","number",pPara->m_oDA.K8);
	pSerializePara->xml_serialize("","K9","","number",pPara->m_oDA.K9);
	pSerializePara->xml_serialize("","K10","","number",pPara->m_oDA.K10);
	pSerializePara->xml_serialize("","K11","","number",pPara->m_oDA.K11);
	pSerializePara->xml_serialize("","K12","","number",pPara->m_oDA.K12);
	pSerializePara->xml_serialize("","K13","","number",pPara->m_oDA.K13);
	pSerializePara->xml_serialize("","K14","","number",pPara->m_oDA.K14);
	pSerializePara->xml_serialize("","K15","","number",pPara->m_oDA.K15);
	pSerializePara->xml_serialize("","K16","","number",pPara->m_oDA.K16);
	pSerializePara->xml_serialize("","K17","","number",pPara->m_oDA.K17);
	pSerializePara->xml_serialize("","K18","","number",pPara->m_oDA.K18);
	pSerializePara->xml_serialize("","K19","","number",pPara->m_oDA.K19);
	pSerializePara->xml_serialize("","K20","","number",pPara->m_oDA.K20);
	pSerializePara->xml_serialize("","K21","","number",pPara->m_oDA.K21);
	pSerializePara->xml_serialize("","K22","","number",pPara->m_oDA.K22);
	pSerializePara->xml_serialize("","K23","","number",pPara->m_oDA.K23);
	pSerializePara->xml_serialize("","K24","","number",pPara->m_oDA.K24);
	pSerializePara->xml_serialize("","K25","","number",pPara->m_oDA.K25);
	pSerializePara->xml_serialize("","K26","","number",pPara->m_oDA.K26);
	pSerializePara->xml_serialize("","K27","","number",pPara->m_oDA.K27);
	pSerializePara->xml_serialize("","K28","","number",pPara->m_oDA.K28);
	pSerializePara->xml_serialize("","K29","","number",pPara->m_oDA.K29);
	pSerializePara->xml_serialize("","K30","","number",pPara->m_oDA.K30);
	pSerializePara->xml_serialize("","K31","","number",pPara->m_oDA.K31);
	pSerializePara->xml_serialize("","K32","","number",pPara->m_oDA.K32);
	pSerializePara->xml_serialize("","K33","","number",pPara->m_oDA.K33);
	pSerializePara->xml_serialize("","K34","","number",pPara->m_oDA.K34);
	pSerializePara->xml_serialize("","K35","","number",pPara->m_oDA.K35);
	pSerializePara->xml_serialize("","K36","","number",pPara->m_oDA.K36);
	pSerializePara->xml_serialize("","K37","","number",pPara->m_oDA.K37);
	pSerializePara->xml_serialize("","K38","","number",pPara->m_oDA.K38);
	pSerializePara->xml_serialize("","K39","","number",pPara->m_oDA.K39);
	pSerializePara->xml_serialize("","K40","","number",pPara->m_oDA.K40);
	pSerializePara->xml_serialize("","K41","","number",pPara->m_oDA.K41);
	pSerializePara->xml_serialize("","K42","","number",pPara->m_oDA.K42);
	pSerializePara->xml_serialize("","Addr010c","","number",pPara->m_oDA.Addr010c);

	pSerializePara->xml_serialize("","VsenseFlag","","number",pPara->m_oDA.VsenseFlag);
	pSerializePara->xml_serialize("","V24VIsenseFlag","","number",pPara->m_oDA.V24VIsenseFlag);
	pSerializePara->xml_serialize("","V220VIsenseFlag","","number",pPara->m_oDA.V220VIsenseFlag);
	pSerializePara->xml_serialize("","StateReadyFlag","","number",pPara->m_oDA.StateReadyFlag);
	pSerializePara->xml_serialize("","CountFlag","","number",pPara->m_oDA.CountFlag);

}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_PtTest()
{
	tmt_Pik100Test otmt_Pik100Test;
	otmt_Pik100Test.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
//	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&otmt_Pik100Test.m_oPik100Para, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("Pik100TestDemo.xml");
	//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
