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
	pXmlSierialize->xml_serialize("�ȴ������ʱʱ��,��λs","WaitTime","","number",pPara->m_nWaitTime);
	pXmlSierialize->xml_serialize("�Ƕȿ���,0-ת�� 1-����","nMode","","number",pPara->m_nMode);
	pXmlSierialize->xml_serialize("��Դ��ת�Ƕ�","Angle","","number",pPara->m_nAngle);
	pXmlSierialize->xml_serialize("0-��ת,1-��ת","Direction","","number",pPara->m_nDirection);
}

void stt_xml_serialize(tmt_LightGetAngleResult *pResult, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("����ֵ","TotalCode","","number",pResult->m_nTotalCode);
	pXmlSierialize->xml_serialize("Ȧ��","RingCnt","","number",pResult->m_nRingCnt);
	pXmlSierialize->xml_serialize("��Ȧֵ","RingValue","","number",pResult->m_nRingValue);
	pXmlSierialize->xml_serialize("�������Ƕ�ֵ(�Ѿ��Ŵ�100��)","Angle","","number",pResult->m_nAngle);
	pXmlSierialize->xml_serialize("����","Reserve","","number",pResult->m_nReserve);
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
