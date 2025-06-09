#include "stdafx.h"
#include "tmt_elec_railway_diff_test.h"
#include "../../../SttTestBase/SttXmlSerialize.h"
#include "../../../SttCmd/SttTestCmd.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif
void stt_init_paras(tmt_ElecRailwayDiffParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_ElecRailwayDiffParas));
	pParas->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_diff_search_results(tmt_ElecRailwayDiffParas *pParas,tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�������","SearchBegin","","number",pParas->m_fSearchBegin);
	pXmlSierialize->xml_serialize("��ǰֵ","CurrSearchVal","","number",pParas->m_fCurrScanVal);
	pXmlSierialize->xml_serialize("�����յ�","SearchEnd","","number",pParas->m_fSearchEnd);
	pXmlSierialize->xml_serialize("�������䳤��","SearchArea","","number",pParas->m_fSearchArea);
	pXmlSierialize->xml_serialize("I1(Ie)","TripI1Ie","Ie","number",pResults->m_fI1Ie);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("Ialpha(Ie)","TripIalphaIe","Ie","number",pResults->m_fIalphaIe);
	pXmlSierialize->xml_serialize("IalphaA","TripIalphaA","In/A","number",pResults->m_fIalpha);
	pXmlSierialize->xml_serialize("Ibeta(Ie)","TripIbetaIe","Ie","number",pResults->m_fIbetaIe);
	pXmlSierialize->xml_serialize("IbetaA","TripIbetaA","In/A","number",pResults->m_fIbeta);
	pXmlSierialize->xml_serialize("�ƶ�����","Ir","","number",pParas->m_fIbias);
#else
  pXmlSierialize->xml_serialize(/* "�������" */ g_sLangTxt_Native_SearchStart.GetString(), "SearchBegin", "", "number", pParas->m_fSearchBegin);
  pXmlSierialize->xml_serialize(/* "��ǰֵ" */ g_sLangTxt_Native_CurrentValue.GetString(), "CurrSearchVal", "", "number", pParas->m_fCurrScanVal);
  pXmlSierialize->xml_serialize(/* "�����յ�" */ g_sLangTxt_Native_SearchEnd.GetString(), "SearchEnd", "", "number", pParas->m_fSearchEnd);
  pXmlSierialize->xml_serialize(/* "�������䳤��" */ g_sLangTxt_Native_SearchLen.GetString(), "SearchArea", "", "number", pParas->m_fSearchArea);
  pXmlSierialize->xml_serialize("I1(Ie)", "TripI1Ie", "Ie", "number", pResults->m_fI1Ie);
  pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
  pXmlSierialize->xml_serialize("Ialpha(Ie)", "TripIalphaIe", "Ie", "number", pResults->m_fIalphaIe);
  pXmlSierialize->xml_serialize("IalphaA", "TripIalphaA", "In/A", "number", pResults->m_fIalpha);
  pXmlSierialize->xml_serialize("Ibeta(Ie)", "TripIbetaIe", "Ie", "number", pResults->m_fIbetaIe);
  pXmlSierialize->xml_serialize("IbetaA", "TripIbetaA", "In/A", "number", pResults->m_fIbeta);
  pXmlSierialize->xml_serialize(/* "�ƶ�����" */ g_sLangTxt_Native_ControlCurrent.GetString(), "Ir", "", "number", pParas->m_fIbias);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_common_fault_paras(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2023.4.26 zhangyq
#ifdef NOT_USE_XLANGUAGE
	if(!pXmlSierialize->xml_serialize("��Ŀ����", "TestName", "", "string", pParas->m_pszTestName))
#else
  if (!pXmlSierialize->xml_serialize(/* "��Ŀ����" */ g_sLangTxt_Native_ProjName.GetString(), "TestName", "", "string", pParas->m_pszTestName))
#endif
	{
		memset(pParas->m_pszTestName,0,32);
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�Ƿ��Զ�����","_AutoTest","","number",pParas->m_nAutoSearch);
	pXmlSierialize->xml_serialize("�仯ʼֵ","BeginVal","In/A","number",pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize("�仯��ֵ","EndVal","In/A","number",pParas->m_fScanTo);
	pXmlSierialize->xml_serialize("���Ծ���","Step","In/A","number",pParas->m_fStep);
	pXmlSierialize->xml_serialize("�ƶ�����","Ir","A","number",pParas->m_fIbias);
	pXmlSierialize->xml_serialize("�����","Id","In/A","number",pParas->m_fIdiff);
	pXmlSierialize->xml_serialize("��������","FaultType","","PsuDiffFaultType",pParas->m_nPhase);
	pXmlSierialize->xml_serialize("�������ֵ","IdSetting","A","number",pParas->m_fIdSetting);
#else
  pXmlSierialize->xml_serialize(/* "�Ƿ��Զ�����" */ g_sLangTxt_Native_AutoSearch.GetString(), "_AutoTest", "", "number", pParas->m_nAutoSearch);
  pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "In/A", "number", pParas->m_fScanFrom);
  pXmlSierialize->xml_serialize(/* "�仯��ֵ" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "In/A", "number", pParas->m_fScanTo);
  pXmlSierialize->xml_serialize(/* "���Ծ���" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "In/A", "number", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "�ƶ�����" */ g_sLangTxt_State_BrakingCur.GetString(), "Ir", "A", "number", pParas->m_fIbias);
  pXmlSierialize->xml_serialize(/* "�����" */ g_sLangTxt_State_DifferentCur.GetString(), "Id", "In/A", "number", pParas->m_fIdiff);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "", "PsuDiffFaultType", pParas->m_nPhase);
  pXmlSierialize->xml_serialize(/* "�������ֵ" */ g_sLangTxt_Native_DiffCurrentSetVal.GetString(), "IdSetting", "A", "number", pParas->m_fIdSetting);
#endif
}

void stt_xml_serialize_common_sys_paras(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	BOOL bFind = pXmlSierialize->xml_serialize("׼��ʱ��","PrepareTime","s","number",pParas->m_fPreTime);
	pXmlSierialize->xml_serialize("����ǰʱ��","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	if(!bFind)
	{
		pParas->m_fPreTime = 0.001f;
	}
	pXmlSierialize->xml_serialize("����ʱ��","FaultTime","s","number",pParas->m_fFaultTime);
	pXmlSierialize->xml_serialize("CT����","CTPoint","","CTPositionPnv",pParas->m_bCTStarPoint);
	pXmlSierialize->xml_serialize("Ir�ƶ�����","IrEquation","","IrEquationPnv",pParas->m_nIbiasCal);

	pXmlSierialize->xml_serialize("��һ���ѹ���ֵ","Vg1","V","number",pParas->m_fVg1);
	pXmlSierialize->xml_serialize("�ڶ����ѹ���ֵ","Vg2","V","number",pParas->m_fVg2);

	pXmlSierialize->xml_serialize("ƽ��ϵ��","KplSet","","number",pParas->m_fKpl);
	

	pXmlSierialize->xml_serialize("��������","SearchMode","","SearchModePnv",pParas->m_nSearchMode);

	// ��ֵ���
	pXmlSierialize->xml_serialize("��ֵ������ʽ","MinAxis","","SettingModePnv",pParas->m_bMinAxis);//++++Ĭ�ϱ���ֵ
	pXmlSierialize->xml_serialize("�����", "InSet", "A", "number", pParas->m_fIbase);
	pXmlSierialize->xml_serialize("��ٶϵ���","IQuick","In/A","number",pParas->m_fIsd);
	pXmlSierialize->xml_serialize("��ż�����","IDoor","In/A","number",pParas->m_fIcdqd);

	pXmlSierialize->xml_serialize("�����ƶ��յ�1����","Limp1","","number",pParas->m_fIp1);
	pXmlSierialize->xml_serialize("�����ƶ��յ�2����","Limp2","","number",pParas->m_fIp2);

	pXmlSierialize->xml_serialize("���������ƶ�����б��1","Kid1","","number",pParas->m_fKid1);
	pXmlSierialize->xml_serialize("���������ƶ�����б��2","Kid2","","number",pParas->m_fKid2);

	pXmlSierialize->xml_serialize("��ѹ��������ʽ","TranSort","","number",pParas->m_nTranSort);
	pXmlSierialize->xml_serialize("��ѹ��CT���߷�ʽ","RWCTconnect","","number",pParas->m_nRWCTconnect);
	pXmlSierialize->xml_serialize("ƽ��ϵ�����㷽��","KphMode","","number",pParas->m_nKphMode);

	//��λ������
	pXmlSierialize->xml_serialize("2��г���ƶ�ϵ��","CoefHarm2","","number",pParas->m_fCoefHarm2);
	pXmlSierialize->xml_serialize("3��г���ƶ�ϵ��","CoefHarm3","","number",pParas->m_fCoefHarm3);
	pXmlSierialize->xml_serialize("5��г���ƶ�ϵ��","CoefHarm5","","number",pParas->m_fCoefHarm5);

	pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
  pXmlSierialize->xml_serialize(/* "����ǰʱ��" */ g_sLangTxt_Native_PreFautTime.GetString(), "PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
  pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Gradient_FailTime.GetString(), "FaultTime", "s", "number", pParas->m_fFaultTime);
  pXmlSierialize->xml_serialize(/* "CT����" */ g_sLangTxt_State_CTpolarity.GetString(), "CTPoint", "", "CTPositionPnv", pParas->m_bCTStarPoint);
  pXmlSierialize->xml_serialize(/* "Ir�ƶ�����" */ g_sLangTxt_Native_IrBrakeEq.GetString(), "IrEquation", "", "IrEquationPnv", pParas->m_nIbiasCal);

  pXmlSierialize->xml_serialize(/* "��һ���ѹ���ֵ" */ g_sLangTxt_Native_FirstGroupVoltageOut.GetString(), "Vg1", "V", "number", pParas->m_fVg1);
  pXmlSierialize->xml_serialize(/* "�ڶ����ѹ���ֵ" */ g_sLangTxt_Native_SecondGroupVoltageOut.GetString(), "Vg2", "V", "number", pParas->m_fVg2);

  pXmlSierialize->xml_serialize(/* "ƽ��ϵ��" */ g_sLangTxt_Native_BalCoeff.GetString(), "KplSet", "", "number", pParas->m_fKpl);

  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_SearchMeth.GetString(), "SearchMode", "", "SearchModePnv", pParas->m_nSearchMode);

  // ��ֵ���
  pXmlSierialize->xml_serialize(/* "��ֵ������ʽ" */ g_sLangTxt_Native_DevSetMethod.GetString(), "MinAxis", "", "SettingModePnv", pParas->m_bMinAxis);  //++++Ĭ�ϱ���ֵ
  pXmlSierialize->xml_serialize(/* "�����" */ g_sLangTxt_Native_EDCurrent.GetString(), "InSet", "A", "number", pParas->m_fIbase);
  pXmlSierialize->xml_serialize(/* "��ٶϵ���" */ g_sLangTxt_Native_DiffQuickBreakCurr.GetString(), "IQuick", "In/A", "number", pParas->m_fIsd);
  pXmlSierialize->xml_serialize(/* "��ż�����" */ g_sLangTxt_Native_DiffThreshCurrent.GetString(), "IDoor", "In/A", "number", pParas->m_fIcdqd);

  pXmlSierialize->xml_serialize(/* "�����ƶ��յ�1����" */ g_sLangTxt_Native_RatioBrakeTurn1Curr.GetString(), "Limp1", "", "number", pParas->m_fIp1);
  pXmlSierialize->xml_serialize(/* "�����ƶ��յ�2����" */ g_sLangTxt_Native_RatioBrakeTurn2Curr.GetString(), "Limp2", "", "number", pParas->m_fIp2);

  pXmlSierialize->xml_serialize(/* "���������ƶ�����б��1" */ g_sLangTxt_Native_FundRatioBrkSlope1.GetString(), "Kid1", "", "number", pParas->m_fKid1);
  pXmlSierialize->xml_serialize(/* "���������ƶ�����б��2" */ g_sLangTxt_Native_FundRatioBrkSlope2.GetString(), "Kid2", "", "number", pParas->m_fKid2);

  pXmlSierialize->xml_serialize(/* "��ѹ��������ʽ" */ g_sLangTxt_Native_TransConnForm.GetString(), "TranSort", "", "number", pParas->m_nTranSort);
  pXmlSierialize->xml_serialize(/* "��ѹ��CT���߷�ʽ" */ g_sLangTxt_Native_HVCTConnectionMode.GetString(), "RWCTconnect", "", "number", pParas->m_nRWCTconnect);
  pXmlSierialize->xml_serialize(/* "ƽ��ϵ�����㷽��" */ g_sLangTxt_Native_BalanceCoeffCalcMethod.GetString(), "KphMode", "", "number", pParas->m_nKphMode);

  // ��λ������
  pXmlSierialize->xml_serialize(/* "2��г���ƶ�ϵ��" */ g_sLangTxt_Native_2HarBrkCoef.GetString(), "CoefHarm2", "", "number", pParas->m_fCoefHarm2);
  pXmlSierialize->xml_serialize(/* "3��г���ƶ�ϵ��" */ g_sLangTxt_Native_3HarBrkCoef.GetString(), "CoefHarm3", "", "number", pParas->m_fCoefHarm3);
  pXmlSierialize->xml_serialize(/* "5��г���ƶ�ϵ��" */ g_sLangTxt_Native_5HarBrkCoef.GetString(), "CoefHarm5", "", "number", pParas->m_fCoefHarm5);

  pXmlSierialize->xml_serialize(/* "�����߼�" */ g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_thr(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_thr_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�����ֵ", "Iqd", "In/A", "number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("��������","ActFlag","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("�����ƶ�ϵ��","RateKid","","number",pResults->m_fRateKid); //yyj add 
#else
  pXmlSierialize->xml_serialize(/* "�����ֵ" */ g_sLangTxt_Native_DiffActionVal.GetString(), "Iqd", "In/A", "number", pResults->m_fIdiffActValue);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
  pXmlSierialize->xml_serialize(/* "�����ƶ�ϵ��" */ g_sLangTxt_Native_ProportionalBrakingFactor.GetString(), "RateKid", "", "number", pResults->m_fRateKid);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_rate(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_rate_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ǰ����ֵ","CurrentId","In/A","number",pResults->m_fIdiffSettingValue);
	pXmlSierialize->xml_serialize("�����ֵ","TripId","In/A","number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("���������","ActId","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("�ƶ�����","TripIr","In/A","number",pResults->m_fIbiasValue);
	pXmlSierialize->xml_serialize("I1(Ie)","TripI1Ie","Ie","number",pResults->m_fI1Ie);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("Ialpha(Ie)","TripIalphaIe","Ie","number",pResults->m_fIalphaIe);
	pXmlSierialize->xml_serialize("IalphaA","TripIalphaA","In/A","number",pResults->m_fIalpha);
	pXmlSierialize->xml_serialize("Ibeta(Ie)","TripIbetaIe","Ie","number",pResults->m_fIbetaIe);
	pXmlSierialize->xml_serialize("IbetaA","TripIbetaA","In/A","number",pResults->m_fIbeta);
	pXmlSierialize->xml_serialize("�����ƶ�ϵ��","RateKid","","number",pResults->m_fRateKid); //yyj add 
#else
  pXmlSierialize->xml_serialize(/* "��ǰ����ֵ" */ g_sLangTxt_Native_CurrSearchVal.GetString(), "CurrentId", "In/A", "number", pResults->m_fIdiffSettingValue);
  pXmlSierialize->xml_serialize(/* "�����ֵ" */ g_sLangTxt_Native_DiffActionVal.GetString(), "TripId", "In/A", "number", pResults->m_fIdiffActValue);
  pXmlSierialize->xml_serialize(/* "���������" */ g_sLangTxt_Native_DiffActionDesc.GetString(), "ActId", "", "number", pResults->m_nActFlag);
  pXmlSierialize->xml_serialize(/* "�ƶ�����" */ g_sLangTxt_Native_ControlCurrent.GetString(), "TripIr", "In/A", "number", pResults->m_fIbiasValue);
  pXmlSierialize->xml_serialize("I1(Ie)", "TripI1Ie", "Ie", "number", pResults->m_fI1Ie);
  pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
  pXmlSierialize->xml_serialize("Ialpha(Ie)", "TripIalphaIe", "Ie", "number", pResults->m_fIalphaIe);
  pXmlSierialize->xml_serialize("IalphaA", "TripIalphaA", "In/A", "number", pResults->m_fIalpha);
  pXmlSierialize->xml_serialize("Ibeta(Ie)", "TripIbetaIe", "Ie", "number", pResults->m_fIbetaIe);
  pXmlSierialize->xml_serialize("IbetaA", "TripIbetaA", "In/A", "number", pResults->m_fIbeta);
  pXmlSierialize->xml_serialize(/* "�����ƶ�ϵ��" */ g_sLangTxt_Native_ProportionalBrakingFactor.GetString(), "RateKid", "", "number", pResults->m_fRateKid);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_quick(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_quick_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�ٶϵ���", "Isd", "In/A", "number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("��������","ActFlag","","number",pResults->m_nActFlag);
#else
  pXmlSierialize->xml_serialize(/* "�ٶϵ���" */ g_sLangTxt_Native_InstCurr.GetString(), "Isd", "In/A", "number", pResults->m_fIdiffActValue);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_harm(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2023.4.26 zhangyq
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��Ŀ����", "TestName", "", "string", pParas->m_pszTestName);

	pXmlSierialize->xml_serialize("�Ƿ��Զ�����","_AutoTest","","number",pParas->m_nAutoSearch);
	pXmlSierialize->xml_serialize("�仯ʼֵ","BeginVal","%","number",pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize("�仯��ֵ","EndVal","%","number",pParas->m_fScanTo);
	pXmlSierialize->xml_serialize("���Ծ���","Step","%","number",pParas->m_fStep);
	pXmlSierialize->xml_serialize("�����","Id","In/A","number",pParas->m_fIdiff);
	pXmlSierialize->xml_serialize("г������","HarmIndex","","DiffHarmIndex",pParas->m_nHarmIndex);
	pXmlSierialize->xml_serialize("��������","FaultType","","PsuDiffFaultType",pParas->m_nPhase);
	pXmlSierialize->xml_serialize("г���ƶ�ϵ����ֵ","RateHarmSet","","number",pParas->m_fCoefHarm2);
#else
  pXmlSierialize->xml_serialize(/* "��Ŀ����" */ g_sLangTxt_Native_ProjName.GetString(), "TestName", "", "string", pParas->m_pszTestName);

  pXmlSierialize->xml_serialize(/* "�Ƿ��Զ�����" */ g_sLangTxt_Native_AutoSearch.GetString(), "_AutoTest", "", "number", pParas->m_nAutoSearch);
  pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "%", "number", pParas->m_fScanFrom);
  pXmlSierialize->xml_serialize(/* "�仯��ֵ" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "%", "number", pParas->m_fScanTo);
  pXmlSierialize->xml_serialize(/* "���Ծ���" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "%", "number", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "�����" */ g_sLangTxt_State_DifferentCur.GetString(), "Id", "In/A", "number", pParas->m_fIdiff);
  pXmlSierialize->xml_serialize(/* "г������" */ g_sLangTxt_Native_harmonicOrder.GetString(), "HarmIndex", "", "DiffHarmIndex", pParas->m_nHarmIndex);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "", "PsuDiffFaultType", pParas->m_nPhase);
  pXmlSierialize->xml_serialize(/* "г���ƶ�ϵ����ֵ" */ g_sLangTxt_Native_HarmonicBrakeCoeff.GetString(), "RateHarmSet", "", "number", pParas->m_fCoefHarm2);
#endif
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_harm_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("г���ƶ�ϵ��","TripRHarm","A","number",pResults->m_fIrCoef);
	pXmlSierialize->xml_serialize("г���ƶ�ϵ������","ActRHarm","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("A���������","TripABase","A","number",pResults->m_fIRbase[0]);
	pXmlSierialize->xml_serialize("B���������","TripBBase","A","number",pResults->m_fIRbase[1]);
	pXmlSierialize->xml_serialize("C���������","TripCBase","A","number",pResults->m_fIRbase[2]);
	pXmlSierialize->xml_serialize("A��г������","TripAHarm","A","number",pResults->m_fIharm[0]);
	pXmlSierialize->xml_serialize("B��г������","TripBHarm","A","number",pResults->m_fIharm[1]);
	pXmlSierialize->xml_serialize("C��г������","TripCHarm","A","number",pResults->m_fIharm[2]);
#else
  pXmlSierialize->xml_serialize(/* "г���ƶ�ϵ��" */ g_sLangTxt_State_HarmonicBrakingcoefficient.GetString(), "TripRHarm", "A", "number", pResults->m_fIrCoef);
  pXmlSierialize->xml_serialize(/* "г���ƶ�ϵ������" */ g_sLangTxt_Native_HarmonicBrakeDesc.GetString(), "ActRHarm", "", "number", pResults->m_nActFlag);
  pXmlSierialize->xml_serialize(/* "A���������" */ g_sLangTxt_Native_PhaseACurrent.GetString(), "TripABase", "A", "number", pResults->m_fIRbase[0]);
  pXmlSierialize->xml_serialize(/* "B���������" */ g_sLangTxt_Native_PhaseBCurrent.GetString(), "TripBBase", "A", "number", pResults->m_fIRbase[1]);
  pXmlSierialize->xml_serialize(/* "C���������" */ g_sLangTxt_Native_PhaseCCurrent.GetString(), "TripCBase", "A", "number", pResults->m_fIRbase[2]);
  pXmlSierialize->xml_serialize(/* "A��г������" */ g_sLangTxt_Native_PhaseAHarmCur.GetString(), "TripAHarm", "A", "number", pResults->m_fIharm[0]);
  pXmlSierialize->xml_serialize(/* "B��г������" */ g_sLangTxt_Native_BHarmonicCurrent.GetString(), "TripBHarm", "A", "number", pResults->m_fIharm[1]);
  pXmlSierialize->xml_serialize(/* "C��г������" */ g_sLangTxt_Native_CHarmonicCurrent.GetString(), "TripCHarm", "A", "number", pResults->m_fIharm[2]);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_acttime(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2023.4.26 zhangyq
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��Ŀ����", "TestName", "", "string", pParas->m_pszTestName);

	pXmlSierialize->xml_serialize("�����","Id","In/A","number",pParas->m_fIdiff);
	pXmlSierialize->xml_serialize("�ƶ�����","Ir","In/A","number",pParas->m_fIbias);
	pXmlSierialize->xml_serialize("��������","FaultType","","PsuDiffFaultType",pParas->m_nPhase);
#else
  pXmlSierialize->xml_serialize(/* "��Ŀ����" */ g_sLangTxt_Native_ProjName.GetString(), "TestName", "", "string", pParas->m_pszTestName);

  pXmlSierialize->xml_serialize(/* "�����" */ g_sLangTxt_State_DifferentCur.GetString(), "Id", "In/A", "number", pParas->m_fIdiff);
  pXmlSierialize->xml_serialize(/* "�ƶ�����" */ g_sLangTxt_State_BrakingCur.GetString(), "Ir", "In/A", "number", pParas->m_fIbias);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "", "PsuDiffFaultType", pParas->m_nPhase);
#endif

	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_acttime_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
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

CSttXmlSerializeBase* stt_xml_serialize(tmt_ElecRailwayDiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
//	stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffTest) == 0)
		{
			stt_xml_serialize_thr(&(pTests->m_oDiffCurrParas),  pXmlParas);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("����", "ThrType", "", "number", ((tmt_ElecRailwayDiffThrTest*)pTests)->m_nThrType);
#else
      pXmlParas->xml_serialize(/* "����" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_ElecRailwayDiffThrTest *)pTests)->m_nThrType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffRateTest) == 0)
		{
			stt_xml_serialize_rate(&(pTests->m_oDiffCurrParas), pXmlParas);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("����", "RateType", "", "number", ((tmt_ElecRailwayDiffRateTest*)pTests)->m_nRateType);
#else
      pXmlParas->xml_serialize(/* "����" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_ElecRailwayDiffRateTest *)pTests)->m_nRateType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffQuickTest) == 0)
		{
			stt_xml_serialize_quick(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffHarmTest) == 0)
		{
			stt_xml_serialize_harm(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffTimeTest) == 0)
		{
			stt_xml_serialize_acttime(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffTest) == 0)
		{
			stt_xml_serialize_thr(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffRateTest) == 0)
		{
			stt_xml_serialize_rate_elec_railway(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffQuickTest) == 0)
		{
			stt_xml_serialize_quick(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffHarmTest) == 0)
		{
			stt_xml_serialize_harm(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffTimeTest) == 0)
		{
			stt_xml_serialize_acttime(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
	}

	return pXmlParas;
}

void stt_xml_serialize(tmt_ElecRailwayDiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly)
{
	if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_thr(&(pTests->m_oDiffCurrParas), pXmlSerialize);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("����", "ThrType", "", "number", ((tmt_ElecRailwayDiffThrTest*)pTests)->m_nThrType);
#else
      pXmlSerialize->xml_serialize(/* "����" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_ElecRailwayDiffThrTest *)pTests)->m_nThrType);
#endif
		}

		stt_xml_serialize_thr(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffRateTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_rate(&(pTests->m_oDiffCurrParas), pXmlSerialize);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("����", "RateType", "", "number", ((tmt_ElecRailwayDiffRateTest*)pTests)->m_nRateType);
#else
      pXmlSerialize->xml_serialize(/* "����" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_ElecRailwayDiffRateTest *)pTests)->m_nRateType);
#endif
		}

		stt_xml_serialize_rate_elec_railway(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffQuickTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_quick(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_quick(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffHarmTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_harm(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_harm(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffTimeTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_acttime(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_acttime(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
}

void stt_xml_serialize_write_ElecRailwayDiffTest()
{
//	tmt_ElecRailwayDiffThrTest oElecRailwayDiffThrTest;
//	oElecRailwayDiffThrTest.init();
//	CSttXmlSerializeTool oSttXmlSerializeTool;
//	CSttTestCmd oSttTestCmd;
//	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
//	pMacro->GetParas();
//	pMacro->GetResults();
//	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
//	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
//	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
//	stt_xml_serialize(&oElecRailwayDiffThrTest, pMacroParas,0,0);
//	CString strXMLPath;
//	strXMLPath = _P_GetConfigPath();
//	strXMLPath += ("ElecRailwayDiffTestDemo.xml");
//	pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
//
//	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
