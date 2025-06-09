#include "stdafx.h"
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
	pXmlSierialize->xml_serialize("Ua��ֵ","_Ua","V","number",pParas->m_uiVOL[0].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ua��λ","_UaPh","��","number",pParas->m_uiVOL[0].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("UaƵ��","_UaFre","Hz","number",pParas->m_uiVOL[0].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Ub��ֵ","_Ub","V","number",pParas->m_uiVOL[1].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ub��λ","_UbPh","��","number",pParas->m_uiVOL[1].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("UbƵ��","_UbFre","Hz","number",pParas->m_uiVOL[1].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Uc��ֵ","_Uc","V","number",pParas->m_uiVOL[2].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Uc��λ","_UcPh","��","number",pParas->m_uiVOL[2].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("UcƵ��","_UcFre","Hz","number",pParas->m_uiVOL[2].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Uz��ֵ","_Uz","V","number",pParas->m_uiVOL[3].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Uz��λ","_UzPh","��","number",pParas->m_uiVOL[3].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("UzƵ��","_UzFre","Hz","number",pParas->m_uiVOL[3].Harm[1].fFreq);

	pXmlSierialize->xml_serialize("Ia��ֵ","_Ia","A","number",pParas->m_uiCUR[0].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ia��λ","_IaPh","��","number",pParas->m_uiCUR[0].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("IaƵ��","_IaFre","Hz","number",pParas->m_uiCUR[0].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Ib��ֵ","_Ib","A","number",pParas->m_uiCUR[1].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ib��λ","_IbPh","��","number",pParas->m_uiCUR[1].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("IbƵ��","_IbFre","Hz","number",pParas->m_uiCUR[1].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Ic��ֵ","_Ic","A","number",pParas->m_uiCUR[2].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ic��λ","_IcPh","��","number",pParas->m_uiCUR[2].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("IcƵ��","_IcFre","Hz","number",pParas->m_uiCUR[2].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("I0��ֵ","_I0","A","number",pParas->m_uiCUR[3].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("I0��λ","_I0Ph","��","number",pParas->m_uiCUR[3].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("I0Ƶ��","_I0Fre","Hz","number",pParas->m_uiCUR[3].Harm[1].fFreq);

	pXmlSierialize->xml_serialize("����ֱ����ѹ","fVolAux","V","number",pParas->m_fVolAux);
	pXmlSierialize->xml_serialize("�������ø߹���ģʽ","bLargeCurrent","","BOOL",pParas->m_bLargeCurrent);
	pXmlSierialize->xml_serialize("�����Զ������","bKeepLoad","","BOOL",pParas->m_bKeepLoad);
#else
  pXmlSierialize->xml_serialize(/* "Ua��ֵ" */ g_sLangTxt_Native_UaAmplitude.GetString(), "_Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Ua��λ" */ g_sLangTxt_Native_UaPhase.GetString(), "_UaPh", "��", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "UaƵ��" */ g_sLangTxt_Native_UaFreq.GetString(), "_UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq);
  pXmlSierialize->xml_serialize(/* "Ub��ֵ" */ g_sLangTxt_Native_UbAmplitude.GetString(), "_Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Ub��λ" */ g_sLangTxt_Native_UbPhase.GetString(), "_UbPh", "��", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "UbƵ��" */ g_sLangTxt_Native_UbFreq.GetString(), "_UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq);
  pXmlSierialize->xml_serialize(/* "Uc��ֵ" */ g_sLangTxt_Native_UcAmplitude.GetString(), "_Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Uc��λ" */ g_sLangTxt_Native_UcPhase.GetString(), "_UcPh", "��", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "UcƵ��" */ g_sLangTxt_Native_UcFreq.GetString(), "_UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq);
  pXmlSierialize->xml_serialize(/* "Uz��ֵ" */ g_sLangTxt_Native_UzAmp.GetString(), "_Uz", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Uz��λ" */ g_sLangTxt_Native_UzPhase.GetString(), "_UzPh", "��", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "UzƵ��" */ g_sLangTxt_Native_UzFreq.GetString(), "_UzFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq);

  pXmlSierialize->xml_serialize(/* "Ia��ֵ" */ g_sLangTxt_Native_IaAmp.GetString(), "_Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Ia��λ" */ g_sLangTxt_Native_IaPhase.GetString(), "_IaPh", "��", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "IaƵ��" */ g_sLangTxt_Native_IaFreq.GetString(), "_IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq);
  pXmlSierialize->xml_serialize(/* "Ib��ֵ" */ g_sLangTxt_Native_IbAmp.GetString(), "_Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Ib��λ" */ g_sLangTxt_Native_IbPhase.GetString(), "_IbPh", "��", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "IbƵ��" */ g_sLangTxt_Native_IbFreq.GetString(), "_IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq);
  pXmlSierialize->xml_serialize(/* "Ic��ֵ" */ g_sLangTxt_Native_IcAmp.GetString(), "_Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "Ic��λ" */ g_sLangTxt_Native_IcPhase.GetString(), "_IcPh", "��", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "IcƵ��" */ g_sLangTxt_Native_IcFreq.GetString(), "_IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq);
  pXmlSierialize->xml_serialize(/* "I0��ֵ" */ g_sLangTxt_Native_I0Amplitude.GetString(), "_I0", "A", "number", pParas->m_uiCUR[3].Harm[1].fAmp);
  pXmlSierialize->xml_serialize(/* "I0��λ" */ g_sLangTxt_Native_I0Phase.GetString(), "_I0Ph", "��", "number", pParas->m_uiCUR[3].Harm[1].fAngle);
  pXmlSierialize->xml_serialize(/* "I0Ƶ��" */ g_sLangTxt_Native_I0Frequency.GetString(), "_I0Fre", "Hz", "number", pParas->m_uiCUR[3].Harm[1].fFreq);

  pXmlSierialize->xml_serialize(/* "����ֱ����ѹ" */ g_sLangTxt_Native_AuxiDCV.GetString(), "fVolAux", "V", "number", pParas->m_fVolAux);
  pXmlSierialize->xml_serialize(/* "�������ø߹���ģʽ" */ g_sLangTxt_Native_CurrentHighPowerMode.GetString(), "bLargeCurrent", "", "BOOL", pParas->m_bLargeCurrent);
  pXmlSierialize->xml_serialize(/* "�����Զ������" */ g_sLangTxt_Native_EnableCustomOutput.GetString(), "bKeepLoad", "", "BOOL", pParas->m_bKeepLoad);
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
