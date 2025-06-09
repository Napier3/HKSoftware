#include "stdafx.h"
#include "tmt_ied_test.h"


void stt_init_paras(tmt_IEDTest *pPara)
{
	memset(&pPara, 0, sizeof(tmt_IEDTest));
	pPara->init();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///

void stt_xml_serialize_binary_out(tmt_IEDPara &otmt_IEDPara, int nState,CSttXmlSerializeBase *pXmlSierialize)
{
	CString strName,strID,strTmp;
	strName.Format("状态%d",(nState+1));
	strID.Format("State%d",(nState+1));
	CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize(strName.toUtf8().data(), strID.GetString(), "State", stt_ParaGroupKey());

	if (pStateSerialize == NULL)
	{
		return;
	}

	for(int nIndex = 0;nIndex<256;nIndex++)
	{
		strName.Format("开出%d",(nIndex+1));
		strID.Format("Bout%d",(nIndex+1));
		pStateSerialize->xml_serialize(strName.toUtf8().data(),strID.GetString(),"","DOutputState",otmt_IEDPara.m_binOut[nIndex].nState);
	}
}

void stt_xml_serialize(tmt_IEDParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("故障前时间","FaultPreTime","ms","number",pParas->m_nFaultPreTime);
	pXmlSierialize->xml_serialize("状态间隔时间","OutputTime","ms","number",pParas->m_nOutputTime);
	pXmlSierialize->xml_serialize("开出保持时间","BoKeepTime","ms","number",pParas->m_nBoKeepTime);
	pXmlSierialize->xml_serialize("加量方式","DataMode","","number",pParas->m_nDataMode);
	pXmlSierialize->xml_serialize("实验类型","TestType","","number",pParas->m_nTestType);
	pXmlSierialize->xml_serialize("风暴重复次数","RepeatCount","","number",pParas->m_nRepeatCount);
	pXmlSierialize->xml_serialize("状态数","StateCount","","number",pParas->m_nStateCount);

	for(int i=0;i<pParas->m_nStateCount;i++)
	{
		stt_xml_serialize_binary_out(pParas->m_otmt_IEDPara[i],i,pXmlSierialize);
	}
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

