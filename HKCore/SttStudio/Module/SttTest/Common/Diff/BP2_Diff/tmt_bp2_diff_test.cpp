#include "stdafx.h"
#include "tmt_bp2_diff_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_BP2DiffParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_BP2DiffParas));
	pParas->init();
}

void stt_init_results(tmt_BP2DiffResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_BP2DiffResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_diff_search_results(tmt_BP2DiffParas *pParas,tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�������","SearchBegin","","number",pParas->m_fSearchBegin);
	pXmlSierialize->xml_serialize("��ǰֵ","CurrSearchVal","","number",pParas->m_fCurrScanVal);
	pXmlSierialize->xml_serialize("�����յ�","SearchEnd","","number",pParas->m_fSearchEnd);
	pXmlSierialize->xml_serialize("�������䳤��","SearchArea","","number",pParas->m_fSearchArea);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("I2A","TripI2A","In/A","number",pResults->m_fI2);
	pXmlSierialize->xml_serialize("�ƶ�����","Ir","","number",pParas->m_fIr_Id);
	pXmlSierialize->xml_serialize("�����","Id","","number",pParas->m_fIdiff);//20230428 zhouhj ��������г���ƶ�����
#else
  pXmlSierialize->xml_serialize(/* "�������" */ g_sLangTxt_Native_SearchStart.GetString(), "SearchBegin", "", "number", pParas->m_fSearchBegin);
  pXmlSierialize->xml_serialize(/* "��ǰֵ" */ g_sLangTxt_Native_CurrentValue.GetString(), "CurrSearchVal", "", "number", pParas->m_fCurrScanVal);
  pXmlSierialize->xml_serialize(/* "�����յ�" */ g_sLangTxt_Native_SearchEnd.GetString(), "SearchEnd", "", "number", pParas->m_fSearchEnd);
  pXmlSierialize->xml_serialize(/* "�������䳤��" */ g_sLangTxt_Native_SearchLen.GetString() "SearchArea", "", "number", pParas->m_fSearchArea);
  pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
  pXmlSierialize->xml_serialize("I2A", "TripI2A", "In/A", "number", pResults->m_fI2);
  pXmlSierialize->xml_serialize(/* "�ƶ�����" */ g_sLangTxt_Native_ControlCurrent.GetString(), "Ir", "", "number", pParas->m_fIr_Id);
  pXmlSierialize->xml_serialize(/* "�����" */ g_sLangTxt_Native_DiffCurrents.GetString(), "Id", "", "number", pParas->m_fIdiff);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_common_fault_paras(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�Ƿ��Զ�����","_AutoTest","","number",pParas->m_nAutoSearch);
	pXmlSierialize->xml_serialize("�仯ʼֵ","BeginVal","In/A","number",pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize("�仯��ֵ","EndVal","In/A","number",pParas->m_fScanTo);
	pXmlSierialize->xml_serialize("���Ծ���","Step","In/A","number",pParas->m_fStep);
	pXmlSierialize->xml_serialize("��ʽ�ƶ�����(Ir-Id)","Ir","A","number",pParas->m_fIr_Id);
	pXmlSierialize->xml_serialize("�������ֵ","IdSetting","A","number",pParas->m_fIdSetting);
#else
  pXmlSierialize->xml_serialize(/* "�Ƿ��Զ�����" */ g_sLangTxt_Native_AutoSearch.GetString(), "_AutoTest", "", "number", pParas->m_nAutoSearch);
  pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "In/A", "number", pParas->m_fScanFrom);
  pXmlSierialize->xml_serialize(/* "�仯��ֵ" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "In/A", "number", pParas->m_fScanTo);
  pXmlSierialize->xml_serialize(/* "���Ծ���" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "In/A", "number", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "��ʽ�ƶ�����(Ir-Id)" */ g_sLangTxt_Native_ComplexBrakeCurrent.GetString(), "Ir", "A", "number", pParas->m_fIr_Id);
  pXmlSierialize->xml_serialize(/* "�������ֵ" */ g_sLangTxt_Native_DiffCurrentSetVal.GetString(), "IdSetting", "A", "number", pParas->m_fIdSetting);
#endif
}

void stt_xml_serialize_common_sys_paras(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����(0-������� 1-С������)","DiffType","","number",pParas->m_nDiffType);
	pXmlSierialize->xml_serialize("����ǰʱ��","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("����ʱ��","FaultTime","s","number",pParas->m_fFaultTime);
	pXmlSierialize->xml_serialize("Ua��ֵ","UaMag","V","number",pParas->m_fUmag[0]);
	pXmlSierialize->xml_serialize("Ub��ֵ","UbMag","V","number",pParas->m_fUmag[1]);
	pXmlSierialize->xml_serialize("Uc��ֵ","UcMag","V","number",pParas->m_fUmag[2]);

	pXmlSierialize->xml_serialize("Ua��λ","UaAng","��","number",pParas->m_fUang[0]);
	pXmlSierialize->xml_serialize("Ub��λ","UbAng","��","number",pParas->m_fUang[1]);
	pXmlSierialize->xml_serialize("Uc��λ","UcAng","��","number",pParas->m_fUang[2]);

	pXmlSierialize->xml_serialize("���1TA���","TA1","","number",pParas->m_fTA1);
	pXmlSierialize->xml_serialize("���2TA���","TA2","","number",pParas->m_fTA2);
	pXmlSierialize->xml_serialize("���3TA���","TA3","","number",pParas->m_fTA3);
	pXmlSierialize->xml_serialize("���TA���","TAmax","","number",pParas->m_fTAmax);
	pXmlSierialize->xml_serialize("��������","SearchMode","","SearchModePnv",pParas->m_nSearchMode);

	// ��ֵ���
	pXmlSierialize->xml_serialize("��ż�����","IDoor","In/A","number",pParas->m_fIcdqd);

	pXmlSierialize->xml_serialize("��ʽ����ϵ����ֵ","CompoundKh","","number",pParas->m_fCompoundKh);
	pXmlSierialize->xml_serialize("��ʽ����ϵ����ֵ","CompoundKl","","number",pParas->m_fCompoundKl);

	pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
  pXmlSierialize->xml_serialize(/* "����(0-������� 1-С������)" */ g_sLangTxt_Native_DiffType.GetString(), "DiffType", "", "number", pParas->m_nDiffType);
  pXmlSierialize->xml_serialize(/* "����ǰʱ��" */ g_sLangTxt_Native_PreFautTime.GetString(), "PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
  pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Gradient_FailTime.GetString(), "FaultTime", "s", "number", pParas->m_fFaultTime);
  pXmlSierialize->xml_serialize(/* "Ua��ֵ" */ g_sLangTxt_Native_UaAmplitude.GetString(), "UaMag", "V", "number", pParas->m_fUmag[0]);
  pXmlSierialize->xml_serialize(/* "Ub��ֵ" */ g_sLangTxt_Native_UbAmplitude.GetString(), "UbMag", "V", "number", pParas->m_fUmag[1]);
  pXmlSierialize->xml_serialize(/* "Uc��ֵ" */ g_sLangTxt_Native_UcAmplitude.GetString(), "UcMag", "V", "number", pParas->m_fUmag[2]);

  pXmlSierialize->xml_serialize(/* "Ua��λ" */ g_sLangTxt_Native_UaPhase.GetString(), "UaAng", "��", "number", pParas->m_fUang[0]);
  pXmlSierialize->xml_serialize(/* "Ub��λ" */ g_sLangTxt_Native_UbPhase.GetString(), "UbAng", "��", "number", pParas->m_fUang[1]);
  pXmlSierialize->xml_serialize(/* "Uc��λ" */ g_sLangTxt_Native_UcPhase.GetString(), "UcAng", "��", "number", pParas->m_fUang[2]);

  pXmlSierialize->xml_serialize(/* "���1TA���" */ g_sLangTxt_Native_Gap1TARatio.GetString(), "TA1", "", "number", pParas->m_fTA1);
  pXmlSierialize->xml_serialize(/* "���2TA���" */ g_sLangTxt_Native_Gap2TARatio.GetString(), "TA2", "", "number", pParas->m_fTA2);
  pXmlSierialize->xml_serialize(/* "���3TA���" */ g_sLangTxt_Native_Gap3TARatio.GetString(), "TA3", "", "number", pParas->m_fTA3);
  pXmlSierialize->xml_serialize(/* "���TA���" */ g_sLangTxt_Native_MaxTARatio.GetString(), "TAmax", "", "number", pParas->m_fTAmax);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_SearchMeth.GetString(), "SearchMode", "", "SearchModePnv", pParas->m_nSearchMode);

  // ��ֵ���
  pXmlSierialize->xml_serialize(/* "��ż�����" */ g_sLangTxt_Native_DiffThreshCurrent.GetString(), "IDoor", "In/A", "number", pParas->m_fIcdqd);

  pXmlSierialize->xml_serialize(/* "��ʽ����ϵ����ֵ" */ g_sLangTxt_Native_HighCompRatioCoef.GetString(), "CompoundKh", "", "number", pParas->m_fCompoundKh);
  pXmlSierialize->xml_serialize(/* "��ʽ����ϵ����ֵ" */ g_sLangTxt_Native_LowCompRatioCoef.GetString(), "CompoundKl", "", "number", pParas->m_fCompoundKl);

  pXmlSierialize->xml_serialize(/* "�����߼�" */ g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);
}

void stt_xml_serialize_common_sys_paras_ex(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�����ƶ�ϵ�����(0-��ֵ 1-��ֵ)","KAType","","number",pParas->m_nKAType);
	pXmlSierialize->xml_serialize("�����Id(���ʽ)","IdExp","","string",pParas->m_pszId);
	pXmlSierialize->xml_serialize("��ʽ�ƶ�����(Ir-Id)(���ʽ)","(Ir-Id)Exp","","string",pParas->m_pszIrId);
#else
  pXmlSierialize->xml_serialize(/* "�����ƶ�ϵ�����(0-��ֵ 1-��ֵ)" */ g_sLangTxt_Native_BrkCoeffType.GetString(), "KAType", "", "number", pParas->m_nKAType);
  pXmlSierialize->xml_serialize(/* "�����Id(���ʽ)" */ g_sLangTxt_Native_DiffCurrentIds.GetString(), "IdExp", "", "string", pParas->m_pszId);
  pXmlSierialize->xml_serialize(/* "��ʽ�ƶ�����(Ir-Id)(���ʽ)" */ g_sLangTxt_Native_CompBrakeCurr.GetString(), "(Ir-Id)Exp", "", "string", pParas->m_pszIrId);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_thr(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}

void stt_xml_serialize_thr_ex(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras_ex(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_thr(tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�����ֵ", "Iqd", "In/A", "number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("��������","ActFlag","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("�����ƶ�ϵ��","RateKid","","number",pResults->m_fRateKid); //yyj add 
#else
  pXmlSierialize->xml_serialize(/* "�����ֵ" */ g_sLangTxt_Native_DiffActionVal.GetString(), "Iqd", "In/A", "number", pResults->m_fIdiffActValue);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
  pXmlSierialize->xml_serialize(/* "�����ƶ�ϵ��" */ g_sLangTxt_Native_ProportionalBrakingFactor.GetString(), "RateKid", "", "number", pResults->m_fRateKid);  // yyj add
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_rate(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}

void stt_xml_serialize_rate_ex(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras_ex(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_rate(tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ǰ����ֵ","CurrentId","In/A","number",pResults->m_fIdiffSettingValue);
	pXmlSierialize->xml_serialize("�����ֵ","TripId","In/A","number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("���������","ActId","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("�ƶ�����","TripIr","In/A","number",pResults->m_fIbiasValue);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("I2A","TripI2A","In/A","number",pResults->m_fI2);
	pXmlSierialize->xml_serialize("�����ƶ�ϵ��","RateKid","","number",pResults->m_fRateKid); //yyj add 
#else
  pXmlSierialize->xml_serialize(/* "��ǰ����ֵ" */ g_sLangTxt_Native_CurrSearchVal.GetString(), "CurrentId", "In/A", "number", pResults->m_fIdiffSettingValue);
  pXmlSierialize->xml_serialize(/* "�����ֵ" */ g_sLangTxt_Native_DiffActionVal.GetString(), "TripId", "In/A", "number", pResults->m_fIdiffActValue);
  pXmlSierialize->xml_serialize(/* "���������" */ g_sLangTxt_Native_DiffActionDesc.GetString(), "ActId", "", "number", pResults->m_nActFlag);
  pXmlSierialize->xml_serialize(/* "�ƶ�����" */ g_sLangTxt_Native_ControlCurrent.GetString(), "TripIr", "In/A", "number", pResults->m_fIbiasValue);
  pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
  pXmlSierialize->xml_serialize("I2A", "TripI2A", "In/A", "number", pResults->m_fI2);
  pXmlSierialize->xml_serialize(/* "�����ƶ�ϵ��" */ g_sLangTxt_Native_ProportionalBrakingFactor.GetString(), "RateKid", "", "number", pResults->m_fRateKid);  // yyj add
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_cboperate(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�����","Id","In/A","number",pParas->m_fIdiff);
	pXmlSierialize->xml_serialize("��ʽ�ƶ�����(Ir-Id)","Ir","In/A","number",pParas->m_fIr_Id);
	pXmlSierialize->xml_serialize("��ѹ����Ԫ��","ULockType","","BP2ULockType",pParas->m_nULockType);
	pXmlSierialize->xml_serialize("������ѹֵ","ULockValue","","number",pParas->m_fULockValue);
#else
  pXmlSierialize->xml_serialize(/* "�����" */ g_sLangTxt_Native_DiffCurrents.GetString(), "Id", "In/A", "number", pParas->m_fIdiff);
  pXmlSierialize->xml_serialize(/* "��ʽ�ƶ�����(Ir-Id)" */ g_sLangTxt_Native_ComplexBrakeCurrent.GetString(), "Ir", "In/A", "number", pParas->m_fIr_Id);
  pXmlSierialize->xml_serialize(/* "��ѹ����Ԫ��" */ g_sLangTxt_Native_VoltLockElem.GetString(), "ULockType", "", "BP2ULockType", pParas->m_nULockType);
  pXmlSierialize->xml_serialize(/* "������ѹֵ" */ g_sLangTxt_Native_LockVoltValue.GetString(), "ULockValue", "", "number", pParas->m_fULockValue);
#endif
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}

void stt_xml_serialize_cboperate_ex(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�����","Id","In/A","number",pParas->m_fIdiff);
	pXmlSierialize->xml_serialize("��ʽ�ƶ�����(Ir-Id)","Ir","In/A","number",pParas->m_fIr_Id);
	pXmlSierialize->xml_serialize("��ѹ����Ԫ��","ULockType","","BP2ULockType",pParas->m_nULockType);
	pXmlSierialize->xml_serialize("������ѹֵ","ULockValue","","number",pParas->m_fULockValue);
#else
  pXmlSierialize->xml_serialize(/* "�����" */ g_sLangTxt_Native_DiffCurrents.GetString(), "Id", "In/A", "number", pParas->m_fIdiff);
  pXmlSierialize->xml_serialize(/* "��ʽ�ƶ�����(Ir-Id)" */ g_sLangTxt_Native_ComplexBrakeCurrent.GetString(), "Ir", "In/A", "number", pParas->m_fIr_Id);
  pXmlSierialize->xml_serialize(/* "��ѹ����Ԫ��" */ g_sLangTxt_Native_VoltLockElem.GetString(), "ULockType", "", "BP2ULockType", pParas->m_nULockType);
  pXmlSierialize->xml_serialize(/* "������ѹֵ" */ g_sLangTxt_Native_LockVoltValue.GetString(), "ULockValue", "", "number", pParas->m_fULockValue);
#endif

	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras_ex(pParas,pXmlSierialize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_cboperate(tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��", "TripTime", "s", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("��������","ActFlag","","number",pResults->m_nActFlag);
#else
  pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "s", "number", pResults->m_fTripTime);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttXmlSerializeBase* stt_xml_serialize(tmt_BP2DiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
//	stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest) == 0)
		{
			stt_xml_serialize_thr_ex(&(pTests->m_oDiffCurrParas),  pXmlParas);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("����", "ThrType", "", "number", ((tmt_BP2DiffThrTest*)pTests)->m_nThrType);
#else
      pXmlParas->xml_serialize(/* "����" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_BP2DiffThrTest *)pTests)->m_nThrType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest) == 0)
		{
			stt_xml_serialize_rate_ex(&(pTests->m_oDiffCurrParas), pXmlParas);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("����", "RateType", "", "number", ((tmt_BP2DiffRateTest*)pTests)->m_nRateType);
#else
      pXmlParas->xml_serialize(/* "����" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_BP2DiffRateTest *)pTests)->m_nRateType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest) == 0)
		{
			stt_xml_serialize_cboperate_ex(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest) == 0)
		{
			stt_xml_serialize_thr(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest) == 0)
		{
			stt_xml_serialize_rate(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest) == 0)
		{
			stt_xml_serialize_cboperate(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
	}

	return pXmlParas;
}

void stt_xml_serialize(tmt_BP2DiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly)
{
	if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_thr_ex(&(pTests->m_oDiffCurrParas), pXmlSerialize);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("����", "ThrType", "", "number", ((tmt_BP2DiffThrTest*)pTests)->m_nThrType);
#else
      pXmlSerialize->xml_serialize(/* "����" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_BP2DiffThrTest *)pTests)->m_nThrType);
#endif
		}

		stt_xml_serialize_thr(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_rate_ex(&(pTests->m_oDiffCurrParas), pXmlSerialize);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("����", "RateType", "", "number", ((tmt_BP2DiffRateTest*)pTests)->m_nRateType);
#else
      pXmlSerialize->xml_serialize(/* "����" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_BP2DiffRateTest *)pTests)->m_nRateType);
#endif
		}

		stt_xml_serialize_rate(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_cboperate_ex(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_cboperate(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
}
