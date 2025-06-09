#include "stdafx.h"
#include "tmt_timemeasure_test.h"


void stt_init_paras(tmt_TimeMeasureTest *pPara)
{
	pPara->init();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///


void stt_xml_serialize_binary_out(tmt_TimeMeasurePara &oTimeMeasurePara, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("开出", "BOout", "BOUT", stt_ParaGroupKey());

	if (pStateSerialize == NULL)
	{
		return;
	}
	CString strName,strID;
	for(int nIndex = 0;nIndex < 16;nIndex++)
	{
		strName.Format("开出%d状态",(nIndex+1));
		strID.Format("Bout%dState",(nIndex+1));
		pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","DOutputState",oTimeMeasurePara.m_binOut[nIndex].nState);
	}
}

void stt_xml_serialize(tmt_TimeMeasurePara &oTimeMeasurePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("状态", "state", nIndex, "State", stt_ParaGroupKey());

	if (pStateSerialize == NULL)
	{
		return;
	}

	pStateSerialize->xml_serialize("触发模式","TrigType","","number",oTimeMeasurePara.m_nTrigType);
	pStateSerialize->xml_serialize("持续时间","OutputTime","ms","number",oTimeMeasurePara.m_nOutputTime);
	stt_xml_serialize_binary_out(oTimeMeasurePara, pStateSerialize);
}

void stt_xml_serialize(tmt_TimeMeasureParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("状态数","StateCount","","number",pParas->m_nStateCount);	

	for(int i=0;i<pParas->m_nStateCount;i++)
	{
		stt_xml_serialize(pParas->m_oTimeMeasurePara[i], i, pXmlSierialize);
	}
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_TimeMeasureTest()
{
	tmt_TimeMeasureTest oTimeMeasureTest;
	oTimeMeasureTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	//pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oTimeMeasureTest.m_oTimeMeasureParas, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("TimeMeasureTestDemo.xml");
//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

