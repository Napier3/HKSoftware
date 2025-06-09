#include "stdafx.h"
#include "tmt_set_parameter.h"

void stt_init_paras(tmt_Paras *pParas)
{
	memset(&pParas, 0, sizeof(tmt_Paras));
	pParas->init();
}

void stt_xml_serialize(tmt_Paras *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("Ua幅值","_Ua","V","number",pParas->m_uiVOL[0].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ua相位","_UaPh","°","number",pParas->m_uiVOL[0].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Ua频率","_UaFre","Hz","number",pParas->m_uiVOL[0].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Ub幅值","_Ub","V","number",pParas->m_uiVOL[1].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ub相位","_UbPh","°","number",pParas->m_uiVOL[1].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Ub频率","_UbFre","Hz","number",pParas->m_uiVOL[1].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Uc幅值","_Uc","V","number",pParas->m_uiVOL[2].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Uc相位","_UcPh","°","number",pParas->m_uiVOL[2].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Uc频率","_UcFre","Hz","number",pParas->m_uiVOL[2].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Uz幅值","_Uz","V","number",pParas->m_uiVOL[3].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Uz相位","_UzPh","°","number",pParas->m_uiVOL[3].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Uz频率","_UzFre","Hz","number",pParas->m_uiVOL[3].Harm[1].fFreq);

	pXmlSierialize->xml_serialize("Ia幅值","_Ia","A","number",pParas->m_uiCUR[0].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ia相位","_IaPh","°","number",pParas->m_uiCUR[0].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Ia频率","_IaFre","Hz","number",pParas->m_uiCUR[0].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Ib幅值","_Ib","A","number",pParas->m_uiCUR[1].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ib相位","_IbPh","°","number",pParas->m_uiCUR[1].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Ib频率","_IbFre","Hz","number",pParas->m_uiCUR[1].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Ic幅值","_Ic","A","number",pParas->m_uiCUR[2].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ic相位","_IcPh","°","number",pParas->m_uiCUR[2].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Ic频率","_IcFre","Hz","number",pParas->m_uiCUR[2].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("I0幅值","_I0","A","number",pParas->m_uiCUR[3].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("I0相位","_I0Ph","°","number",pParas->m_uiCUR[3].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("I0频率","_I0Fre","Hz","number",pParas->m_uiCUR[3].Harm[1].fFreq);

	pXmlSierialize->xml_serialize("辅助直流电压","fVolAux","V","number",pParas->m_fVolAux);
	pXmlSierialize->xml_serialize("电流启用高功率模式","bLargeCurrent","","BOOL",pParas->m_bLargeCurrent);
	pXmlSierialize->xml_serialize("启用自定义输出","bKeepLoad","","BOOL",pParas->m_bKeepLoad);
}

void stt_xml_serialize_write_SetParameter()
{
	tmt_Paras otmt_Paras;
	otmt_Paras.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&otmt_Paras, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("SetParameterDemo.xml");
//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
