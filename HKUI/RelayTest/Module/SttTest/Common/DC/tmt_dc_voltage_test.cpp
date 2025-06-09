#include "stdafx.h"
#include "tmt_dc_voltage_test.h"
#include"../../../SttCmd/SttTestCmd.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif
void stt_init_paras(tmt_DcVoltageParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DcVoltageParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_DcVoltageParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DcVoltageParasEx));
	pParas->init();
}

void stt_init_results(tmt_DcVoltageResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DcVoltageResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serializeDcvVoltageSetting(tmt_DcVoltageParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
	//����ֵ
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹI�ζ�ֵ","Uset1","V","float",pParas->m_fSettingOverVol[0]);
	pXmlSierialize->xml_serialize("��ѹII�ζ�ֵ","Uset2","V","float",pParas->m_fSettingOverVol[1]);
	pXmlSierialize->xml_serialize("��ѹIII�ζ�ֵ","Uset3","V","float",pParas->m_fSettingOverVol[2]);
	pXmlSierialize->xml_serialize("��ѹIV�ζ�ֵ","Uset4","V","float",pParas->m_fSettingOverVol[3]);

	pXmlSierialize->xml_serialize("��ѹI��ʱ��","Tset1","s","float",pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize("��ѹII��ʱ��","Tset2","s","float",pParas->m_fSettingTime[1]);
	pXmlSierialize->xml_serialize("��ѹIII��ʱ��","Tset3","s","float",pParas->m_fSettingTime[2]);
	pXmlSierialize->xml_serialize("��ѹIV��ʱ��","Tset4","s","float",pParas->m_fSettingTime[3]);
#else
	pXmlSierialize->xml_serialize(/* "��ѹI�ζ�ֵ" */ g_sLangTxt_Native_OV1SetValue.GetString(), "Uset1", "V", "float", pParas->m_fSettingOverVol[0]);
	pXmlSierialize->xml_serialize(/* "��ѹII�ζ�ֵ" */ g_sLangTxt_Native_OV2SetValue.GetString(), "Uset2", "V", "float", pParas->m_fSettingOverVol[1]);
	pXmlSierialize->xml_serialize(/* "��ѹIII�ζ�ֵ" */ g_sLangTxt_Native_OV3SetValue.GetString(), "Uset3", "V", "float", pParas->m_fSettingOverVol[2]);
	pXmlSierialize->xml_serialize(/* "��ѹIV�ζ�ֵ" */ g_sLangTxt_Native_OV4SetValue.GetString(), "Uset4", "V", "float", pParas->m_fSettingOverVol[3]);

	pXmlSierialize->xml_serialize(/* "��ѹI��ʱ��" */ g_sLangTxt_Native_OV1Time.GetString(), "Tset1", "s", "float", pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize(/* "��ѹII��ʱ��" */ g_sLangTxt_Native_OV2Time.GetString(), "Tset2", "s", "float", pParas->m_fSettingTime[1]);
	pXmlSierialize->xml_serialize(/* "��ѹIII��ʱ��" */ g_sLangTxt_Native_OV3Time.GetString(), "Tset3", "s", "float", pParas->m_fSettingTime[2]);
	pXmlSierialize->xml_serialize(/* "��ѹIV��ʱ��" */ g_sLangTxt_Native_OV4Time.GetString(), "Tset4", "s", "float", pParas->m_fSettingTime[3]);
#endif
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_DcVoltage(tmt_DcVoltageParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2022.5.26 caoxc ������Ŀ����ID
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����", "GroupID", "��", "string",  pParas->m_pszGroupID);
	pXmlSierialize->xml_serialize("����ͨ��", "FaultVarIndex", "", "UIRampChannel", pParas->m_nFaultChannel);
	pXmlSierialize->xml_serialize("����ͨ��", "CurrentVarIndex", "", "UIRampChannel", pParas->m_nCurrentChannel);
	pXmlSierialize->xml_serialize("����������ѹ", "FaultUf", "V", "number", pParas->m_fUSetting);
	pXmlSierialize->xml_serialize("����", "ISetting", "A", "number", pParas->m_fCurrent);
	pXmlSierialize->xml_serialize("����", "Rate", "��", "number",pParas->m_fRate);
	pXmlSierialize->xml_serialize("������ʱ��", "TSetting", "s","number",pParas->m_fMaxFaultTime);
	pXmlSierialize->xml_serialize("����ʱ��ԣ��","FaultTime","s","number",pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("����ǰʱ��","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("�������������ʱ��","PostFaultTime","s","number",pParas->m_fPostFaultTime);
	pXmlSierialize->xml_serialize("���ϴ�����ʽ","FaultTrigMode","","FaultTrigModePnv",pParas->m_nFaultTrigMode);
	pXmlSierialize->xml_serialize("�Ƿ�ģ���·����ʱ","SimulateBreakerDelay","s","number",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize("��·����բ��ʱ","BrkBreakTime","s","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize("��·����բ��ʱ","BrkCloseTime","s","number",pParas->m_fCBCloseTime);
	pXmlSierialize->xml_serialize("����ǰ��ѹ", "PreFaultUf", "V", "number", pParas->m_fPreFaultVol);
	pXmlSierialize->xml_serialize("����ǰ����", "PreFaultIf", "A", "number", pParas->m_fPreFaultCur);
	pXmlSierialize->xml_serialize("��ѹ����", "VolType", "", "number", pParas->m_nVolType);
	
	pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/* "����" */ g_sLangTxt_Native_Grouping.GetString(), "GroupID", "��", "string", pParas->m_pszGroupID);
	pXmlSierialize->xml_serialize(/* "����ͨ��" */ g_sLangTxt_Native_FaultChnl.GetString(), "FaultVarIndex", "", "UIRampChannel", pParas->m_nFaultChannel);
	pXmlSierialize->xml_serialize(/* "����ͨ��" */ g_sLangTxt_Harm_IChannel.GetString(), "CurrentVarIndex", "", "UIRampChannel", pParas->m_nCurrentChannel);
	pXmlSierialize->xml_serialize(/* "����������ѹ" */ g_sLangTxt_Native_SetActVolt.GetString(), "FaultUf", "V", "number", pParas->m_fUSetting);
	pXmlSierialize->xml_serialize(/* "����" */ g_sLangTxt_Native_Current.GetString(), "ISetting", "A", "number", pParas->m_fCurrent);
	pXmlSierialize->xml_serialize(/* "����" */ g_sLangTxt_Native_Multiple.GetString(), "Rate", "��", "number", pParas->m_fRate);
	pXmlSierialize->xml_serialize(/* "������ʱ��" */ g_sLangTxt_Native_MaxTimeMalf.GetString(), "TSetting", "s", "number", pParas->m_fMaxFaultTime);
	pXmlSierialize->xml_serialize(/* "����ʱ��ԣ��" */ g_sLangTxt_Native_FaultTimeMargin.GetString(), "FaultTime", "s", "number", pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize(/* "����ǰʱ��" */ g_sLangTxt_Native_PreFautTime.GetString(), "PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize(/* "�������������ʱ��" */ g_sLangTxt_Native_DurProtTrip.GetString(), "PostFaultTime", "s", "number", pParas->m_fPostFaultTime);
	pXmlSierialize->xml_serialize(/* "���ϴ�����ʽ" */ g_sLangTxt_Native_FaultTrigMethod.GetString(), "FaultTrigMode", "", "FaultTrigModePnv", pParas->m_nFaultTrigMode);
	pXmlSierialize->xml_serialize(/* "�Ƿ�ģ���·����ʱ" */ g_sLangTxt_Native_SimBrkDel.GetString(), "SimulateBreakerDelay", "s", "number", pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize(/* "��·����բ��ʱ" */ g_sLangTxt_Native_BrkTripDel.GetString(), "BrkBreakTime", "s", "number", pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize(/* "��·����բ��ʱ" */ g_sLangTxt_Native_BrkClsDel.GetString(), "BrkCloseTime", "s", "number", pParas->m_fCBCloseTime);
	pXmlSierialize->xml_serialize(/* "����ǰ��ѹ" */ g_sLangTxt_Native_PreFaultVolt.GetString(), "PreFaultUf", "V", "number", pParas->m_fPreFaultVol);
	pXmlSierialize->xml_serialize(/* "����ǰ����" */ g_sLangTxt_Native_PreFaultCurr.GetString(), "PreFaultIf", "A", "number", pParas->m_fPreFaultCur);
	pXmlSierialize->xml_serialize(/* "��ѹ����" */ g_sLangTxt_Native_VoltType.GetString(), "VolType", "", "number", pParas->m_nVolType);

	pXmlSierialize->xml_serialize(/* "�����߼�" */ g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
	stt_xml_serializeDcvVoltageSetting(pParas,pXmlSierialize);
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);
}

void stt_xml_serialize_DcVoltage_ex(tmt_DcVoltageParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_DcVoltage(pParas,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����������ѹ(���ʽ)", "FaultUfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("����ʱ�䶨ֵ(���ʽ)", "MaxTSettingExp", "", "string", pParas->m_maxTSetting);
#else
    pXmlSierialize->xml_serialize(/* "����������ѹ(���ʽ)" */ g_sLangTxt_Native_ActionVoltExpr.GetString(), "FaultUfExp", "", "string", pParas->m_pszSetting);
    pXmlSierialize->xml_serialize(/* "����ʱ�䶨ֵ(���ʽ)" */ g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "MaxTSettingExp", "", "string", pParas->m_maxTSetting);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_DcVoltageResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("A�ද��ʱ��","TtripA","s","number",pResults->m_fFirstTripTime[0]);
	pXmlSierialize->xml_serialize("B�ද��ʱ��","TtripB","s","number",pResults->m_fFirstTripTime[1]);
	pXmlSierialize->xml_serialize("C�ද��ʱ��","TtripC","s","number",pResults->m_fFirstTripTime[2]);
	pXmlSierialize->xml_serialize("�غ�բ����ʱ��","TtripD","s","number",pResults->m_fRecloseTime);
	pXmlSierialize->xml_serialize("����E����ʱ��", "TtripE", "s", "number", pResults->m_fFirstTripTime[4]);
	pXmlSierialize->xml_serialize("����F����ʱ��", "TtripF", "s", "number",pResults->m_fFirstTripTime[5]);
	pXmlSierialize->xml_serialize("����G����ʱ��", "TtripG", "s", "number",pResults->m_fFirstTripTime[6]);
	pXmlSierialize->xml_serialize("����H����ʱ��", "TtripH", "s", "number",pResults->m_fFirstTripTime[7]);
	pXmlSierialize->xml_serialize("����ʱ��", "TripTime", "", "number",pResults->m_fTripTime);

	pXmlSierialize->xml_serialize("����A��������","ActA","","number",pResults->m_nActA);
	pXmlSierialize->xml_serialize("����B��������","ActB","","number",pResults->m_nActB);
	pXmlSierialize->xml_serialize("����C��������","ActC","","number",pResults->m_nActC);
	pXmlSierialize->xml_serialize("�غ�բ��������","ActD","","number",pResults->m_nActD);
	pXmlSierialize->xml_serialize("����ٶ���ʱ��","TtripAcc","s","number",pResults->m_fSecondTripTime);
	pXmlSierialize->xml_serialize("����ٶ�������","ActAcc","","number",pResults->m_nActAcc);

	pXmlSierialize->xml_serialize("ʵ�ʶ�·����","FaultCurrent","","number",pResults->m_fFaultCurrent);
	pXmlSierialize->xml_serialize("ʵ�ʶ�·��ѹ","FaultVolt","","number",pResults->m_fFaultVol);
	pXmlSierialize->xml_serialize("��ѹֵ", "UGL", "V", "number", pResults->m_fDcVoltage);
#else
	pXmlSierialize->xml_serialize(/* "A�ද��ʱ��" */ g_sLangTxt_Native_PhaseATime.GetString(), "TtripA", "s", "number", pResults->m_fFirstTripTime[0]);
	pXmlSierialize->xml_serialize(/* "B�ද��ʱ��" */ g_sLangTxt_Native_PhaseBTime.GetString(), "TtripB", "s", "number", pResults->m_fFirstTripTime[1]);
	pXmlSierialize->xml_serialize(/* "C�ද��ʱ��" */ g_sLangTxt_Native_PhaseCTime.GetString(), "TtripC", "s", "number", pResults->m_fFirstTripTime[2]);
	pXmlSierialize->xml_serialize(/* "�غ�բ����ʱ��" */ g_sLangTxt_Native_RecloseTime.GetString(), "TtripD", "s", "number", pResults->m_fRecloseTime);
	pXmlSierialize->xml_serialize(/* "����E����ʱ��" */ g_sLangTxt_Native_InputETime.GetString(), "TtripE", "s", "number", pResults->m_fFirstTripTime[4]);
	pXmlSierialize->xml_serialize(/* "����F����ʱ��" */ g_sLangTxt_Native_InputFTime.GetString(), "TtripF", "s", "number", pResults->m_fFirstTripTime[5]);
	pXmlSierialize->xml_serialize(/* "����G����ʱ��" */ g_sLangTxt_Native_InputGTime.GetString(), "TtripG", "s", "number", pResults->m_fFirstTripTime[6]);
	pXmlSierialize->xml_serialize(/* "����H����ʱ��" */ g_sLangTxt_Native_InputHTime.GetString(), "TtripH", "s", "number", pResults->m_fFirstTripTime[7]);
	pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number", pResults->m_fTripTime);

	pXmlSierialize->xml_serialize(/* "����A��������" */ g_sLangTxt_Native_InputADesc.GetString(), "ActA", "", "number", pResults->m_nActA);
	pXmlSierialize->xml_serialize(/* "����B��������" */ g_sLangTxt_Native_InputBDesc.GetString(), "ActB", "", "number", pResults->m_nActB);
	pXmlSierialize->xml_serialize(/* "����C��������" */ g_sLangTxt_Native_InputCDesc.GetString(), "ActC", "", "number", pResults->m_nActC);
	pXmlSierialize->xml_serialize(/* "�غ�բ��������" */ g_sLangTxt_Native_ReclActDesc.GetString(), "ActD", "", "number", pResults->m_nActD);
	pXmlSierialize->xml_serialize(/* "����ٶ���ʱ��" */ g_sLangTxt_Native_PostAccTime.GetString(), "TtripAcc", "s", "number", pResults->m_fSecondTripTime);
	pXmlSierialize->xml_serialize(/* "����ٶ�������" */ g_sLangTxt_Native_PostAccDesc.GetString(), "ActAcc", "", "number", pResults->m_nActAcc);

	pXmlSierialize->xml_serialize(/* "ʵ�ʶ�·����" */ g_sLangTxt_Native_ActShortCur.GetString(), "FaultCurrent", "", "number", pResults->m_fFaultCurrent);
	pXmlSierialize->xml_serialize(/* "ʵ�ʶ�·��ѹ" */ g_sLangTxt_Native_ActShortVol.GetString(), "FaultVolt", "", "number", pResults->m_fFaultVol);
	pXmlSierialize->xml_serialize(/* "��ѹֵ" */ g_sLangTxt_Native_OverVoltVal.GetString(), "UGL", "V", "number", pResults->m_fDcVoltage);
#endif
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DcVoltageTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCVoltageTest) == 0)
		{
			stt_xml_serialize_DcVoltage_ex(&(pTests->m_oDcVoltageParas), pXmlParas);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCVoltageTest) == 0)
		{
			stt_xml_serialize(&pTests->m_oDcVoltageResults, pXmlResults);
		}
	}

	return pXmlParas;
}

#include"../../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_DcVoltageTest()
{
	tmt_DcVoltageTest oDcVoltageTest;
	oDcVoltageTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeRegister(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize_DcVoltage_ex(&oDcVoltageTest.m_oDcVoltageParas, pMacroParas);

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("DcVoltageTestDemo.xml");
	//  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
