#include "stdafx.h"
#include "tmt_light_anglectrl.h"
#include "../../../../Module/API/StringApi.h"

void stt_init_paras(tmt_LightAnglePara *pPara)
{
	memset(&pPara, 0, sizeof(tmt_LightAnglePara));
	pPara->init();
}

void stt_xml_serialize(tmt_LightAnglePara *pPara, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("等待电机超时时间,单位s","WaitTime","","number",pPara->m_nWaitTime);
	pXmlSierialize->xml_serialize("角度控制,0-转动 1-清零","nMode","","number",pPara->m_nMode);
	pXmlSierialize->xml_serialize("光源旋转角度","Angle","","number",pPara->m_nAngle);
	pXmlSierialize->xml_serialize("0-正转,1-反转","Direction","","number",pPara->m_nDirection);
}

void stt_xml_serialize(tmt_LightGetAngleResult *pResult, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("总码值","TotalCode","","number",pResult->m_nTotalCode);
	pXmlSierialize->xml_serialize("圈数","RingCnt","","number",pResult->m_nRingCnt);
	pXmlSierialize->xml_serialize("单圈值","RingValue","","number",pResult->m_nRingValue);
	pXmlSierialize->xml_serialize("编码器角度值(已经放大100倍)","Angle","","number",pResult->m_nAngle);
	pXmlSierialize->xml_serialize("备用","Reserve","","number",pResult->m_nReserve);
}

#include "../../SttCmd/SttTestCmd.h"
#include "../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_LightAngleTest()
{
	tmt_LightAngleTest otmt_LightAngleTest;
	otmt_LightAngleTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
//	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&otmt_LightAngleTest.m_oLightAnglePara, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("LightAngleCtrl.xml");
	//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

void stt_xml_serialize_write_LightGetAngle()
{
	tmt_LightGetAngle otmt_LightGetAngle;
	otmt_LightGetAngle.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	CSttXmlSerializeBase *pMacroResults = oSttXmlSerializeTool.GetMacroResults();
	stt_xml_serialize(&otmt_LightGetAngle.m_oLightGetAngleResult, pMacroResults);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("LightGetAngle.xml");
	//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
