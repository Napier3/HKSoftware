#include "stdafx.h"
#include "tmt_pis2k_test.h"
#include "../../../../Module/API/StringApi.h"

void stt_init_paras(tmt_Pis2kPara *pPara)
{
	memset(&pPara, 0, sizeof(tmt_Pis2kPara));
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

void stt_xml_serialize(tmt_Pis2kPara *pPara, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pSerializePara =pXmlSierialize->xml_serialize("实验参数", "DAValue", "DAValue", stt_ParaGroupKey());
	if (pSerializePara == NULL)
	{
		return;
	}

	pSerializePara->xml_serialize("","ADStart","","BOOL",pPara->m_oDA.ADStart);
	pSerializePara->xml_serialize("","ACDCflag","","number",pPara->m_oDA.ACDCflag);
	pSerializePara->xml_serialize("","DA1_FZ","","number",pPara->m_oDA.DA1_FZ);
	pSerializePara->xml_serialize("","DA1_Frequency","","number",pPara->m_oDA.DA1_Frequency);
	pSerializePara->xml_serialize("","DA1_Phase","","number",pPara->m_oDA.DA1_Phase);
	pSerializePara->xml_serialize("","DA1_ACrisetime","","number",pPara->m_oDA.DA1_ACrisetime);
	pSerializePara->xml_serialize("","DA1_ACdowntime","","number",pPara->m_oDA.DA1_ACdowntime);
	pSerializePara->xml_serialize("","DA1_ACmaxtime","","number",pPara->m_oDA.DA1_ACmaxtime);

	pSerializePara->xml_serialize("","DA2_FZ","","number",pPara->m_oDA.DA2_FZ);
	pSerializePara->xml_serialize("","DA2_ACrisetime","","number",pPara->m_oDA.DA2_ACrisetime);
	pSerializePara->xml_serialize("","DA2_ACdowntime","","number",pPara->m_oDA.DA2_ACdowntime);
	pSerializePara->xml_serialize("","DA2_ACmaxtime","","number",pPara->m_oDA.DA2_ACmaxtime);

	pSerializePara->xml_serialize("","DA_bit8","","number",pPara->m_oDA.DA_bit8);
	pSerializePara->xml_serialize("","AdjCloseLoopMode","","BOOL",pPara->m_oDA.AdjCloseLoopMode);

	CSttXmlSerializeBase *pSerializeSetting =pXmlSierialize->xml_serialize("配置参数", "Setting", "Setting", stt_ParaGroupKey());
	if (pSerializeSetting == NULL)
	{
		return;
	}

	pSerializeSetting->xml_serialize("","VoltageAlarmMin","","number",pPara->m_oSetting.VoltageAlarmMin);
	pSerializeSetting->xml_serialize("","VoltageAlarmMax","","number",pPara->m_oSetting.VoltageAlarmMax);
	pSerializeSetting->xml_serialize("","CurrentAlarmMin","","number",pPara->m_oSetting.CurrentAlarmMin);
	pSerializeSetting->xml_serialize("","CurrentAlarmMax","","number",pPara->m_oSetting.CurrentAlarmMax);

	pSerializeSetting->xml_serialize("","ADCurrentState","","number",pPara->m_oSetting.ADCurrentState);
	pSerializeSetting->xml_serialize("","LocalRemoteFlag","","number",pPara->m_oSetting.LocalRemoteFlag);
	pSerializeSetting->xml_serialize("","WorkModeFlag","","number",pPara->m_oSetting.WorkModeFlag);
    pSerializeSetting->xml_serialize("","AutoADChangeState","","number",pPara->m_oSetting.AutoADChangeState);
    pSerializeSetting->xml_serialize("1-位置1采集系数，2-位置2采集系数","CurrentMeasPos","","number",pPara->m_oSetting.CurrentMeasPos);
}

void stt_xml_serialize(tmt_Pis2kResult *pResult, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("采集电压","V_AD1","","number",pResult->m_fMeasU);
	pXmlSierialize->xml_serialize("泄漏电流","V_AD2","","number",pResult->m_fMeasI);
	pXmlSierialize->xml_serialize("绝缘电阻","V_R","","number",pResult->m_fMeasR);
	pXmlSierialize->xml_serialize("散热器1温度","temp1","","number",pResult->m_fTemp1);
	pXmlSierialize->xml_serialize("散热器2温度","temp2","","number",pResult->m_fTemp2);
	pXmlSierialize->xml_serialize("片上温度","temp3","","number",pResult->m_fTemp3);
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_PtTest()
{
	tmt_Pis2kTest otmt_Pis2kTest;
	otmt_Pis2kTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	//	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&otmt_Pis2kTest.m_oPis2kPara, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("Pis2kTestDemo.xml");
	//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
