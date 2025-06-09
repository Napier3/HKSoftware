﻿#include "stdafx.h"
#include "tmt_set_parameter.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

void stt_init_paras(tmt_Paras *pParas)
{
	memset(&pParas, 0, sizeof(tmt_Paras));
	pParas->init();
}

void stt_xml_serialize(tmt_Paras *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
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
#else
  pXmlSierialize->xml_serialize(/* "Ua幅值" */ g_sLangTxt_Native_UaAmplitude.GetString(), "_Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Ua相位" */ g_sLangTxt_Native_UaPhase.GetString(), "_UaPh", "°", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "Ua频率" */ g_sLangTxt_Native_UaFreq.GetString(), "_UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq);
  pXmlSierialize->xml_serialize(/* "Ub幅值" */ g_sLangTxt_Native_UbAmplitude.GetString(), "_Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Ub相位" */ g_sLangTxt_Native_UbPhase.GetString(), "_UbPh", "°", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "Ub频率" */ g_sLangTxt_Native_UbFreq.GetString(), "_UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq);
  pXmlSierialize->xml_serialize(/* "Uc幅值" */ g_sLangTxt_Native_UcAmplitude.GetString(), "_Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Uc相位" */ g_sLangTxt_Native_UcPhase.GetString(), "_UcPh", "°", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "Uc频率" */ g_sLangTxt_Native_UcFreq.GetString(), "_UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq);
  pXmlSierialize->xml_serialize(/* "Uz幅值" */ g_sLangTxt_Native_UzAmp.GetString(), "_Uz", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Uz相位" */ g_sLangTxt_Native_UzPhase.GetString(), "_UzPh", "°", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "Uz频率" */ g_sLangTxt_Native_UzFreq.GetString(), "_UzFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq);

  pXmlSierialize->xml_serialize(/* "Ia幅值" */ g_sLangTxt_Native_IaAmp.GetString(), "_Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Ia相位" */ g_sLangTxt_Native_IaPhase.GetString(), "_IaPh", "°", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "Ia频率" */ g_sLangTxt_Native_IaFreq.GetString(), "_IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq);
  pXmlSierialize->xml_serialize(/* "Ib幅值" */ g_sLangTxt_Native_IbAmp.GetString(), "_Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Ib相位" */ g_sLangTxt_Native_IbPhase.GetString(), "_IbPh", "°", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "Ib频率" */ g_sLangTxt_Native_IbFreq.GetString(), "_IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq);
  pXmlSierialize->xml_serialize(/* "Ic幅值" */ g_sLangTxt_Native_IcAmp.GetString(), "_Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Ic相位" */ g_sLangTxt_Native_IcPhase.GetString(), "_IcPh", "°", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "Ic频率" */ g_sLangTxt_Native_IcFreq.GetString(), "_IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq);
  pXmlSierialize->xml_serialize(/* "I0幅值" */ g_sLangTxt_Native_I0Amplitude.GetString(), "_I0", "A", "number", pParas->m_uiCUR[3].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "I0相位" */ g_sLangTxt_Native_I0Phase.GetString(), "_I0Ph", "°", "number", pParas->m_uiCUR[3].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "I0频率" */ g_sLangTxt_Native_I0Frequency.GetString(), "_I0Fre", "Hz", "number", pParas->m_uiCUR[3].Harm[1].fFreq);

  pXmlSierialize->xml_serialize(/* "辅助直流电压" */ g_sLangTxt_Native_AuxiDCV.GetString(), "fVolAux", "V", "number", pParas->m_fVolAux);
  pXmlSierialize->xml_serialize(/* "电流启用高功率模式" */ g_sLangTxt_Native_CurrentHighPowerMode.GetString(), "bLargeCurrent", "", "BOOL", pParas->m_bLargeCurrent);
  pXmlSierialize->xml_serialize(/* "启用自定义输出" */ g_sLangTxt_Native_EnableCustomOutput.GetString(), "bKeepLoad", "", "BOOL", pParas->m_bKeepLoad);
#endif
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
