#include "stdafx.h"
#include "tmt_diff_curr_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

#ifndef _STT_NOT_IN_TEST_SERVER_
#include "../SttSystemConfig.h"
#endif

void stt_init_paras(tmt_DiffCurrParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DiffCurrParas));
	pParas->init();
}

void stt_init_results(tmt_DiffCurrResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DiffCurrResults));
	pResults->init();
}

void stt_xml_serialize_diff_6i_binary_in_pnv(tmt_BinaryIn *pbin, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("����Aѡ��", "BinSelectA", "", "BOOL", pbin[0].nSelect);
    pXmlSierialize->xml_serialize("����Bѡ��", "BinSelectB", "", "BOOL", pbin[1].nSelect);
    pXmlSierialize->xml_serialize("����Cѡ��", "BinSelectC", "", "BOOL", pbin[2].nSelect);
    pXmlSierialize->xml_serialize("����Rѡ��", "BinSelectR", "", "BOOL", pbin[3].nSelect);
    pXmlSierialize->xml_serialize("����aѡ��", "BinSelecta", "", "BOOL", pbin[4].nSelect);
    pXmlSierialize->xml_serialize("����bѡ��", "BinSelectb", "", "BOOL", pbin[5].nSelect);
    pXmlSierialize->xml_serialize("����cѡ��", "BinSelectc", "", "BOOL", pbin[6].nSelect);
    pXmlSierialize->xml_serialize("����rѡ��", "BinSelectr", "", "BOOL", pbin[7].nSelect);
}

void stt_xml_serialize_diff_6i_binary_out_pnv(tmt_BinaryOut *pbOut, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("����1״̬", "_FaultBO01", "", "DOutputState", pbOut[0].nState);
    pXmlSierialize->xml_serialize("����2״̬", "_FaultBO02", "", "DOutputState", pbOut[1].nState);
    pXmlSierialize->xml_serialize("����3״̬", "_FaultBO03", "", "DOutputState", pbOut[2].nState);
    pXmlSierialize->xml_serialize("����4״̬", "_FaultBO04", "", "DOutputState", pbOut[3].nState);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_diff_search_results(tmt_DiffCurrParas *pParas,tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�������","SearchBegin","","number",pParas->m_fSearchBegin);
	pXmlSierialize->xml_serialize("��ǰֵ","CurrSearchVal","","number",pParas->m_fCurrScanVal);
	pXmlSierialize->xml_serialize("�����յ�","SearchEnd","","number",pParas->m_fSearchEnd);
	pXmlSierialize->xml_serialize("�������䳤��","SearchArea","","number",pParas->m_fSearchArea);
	pXmlSierialize->xml_serialize("I1(Ie)","TripI1Ie","Ie","number",pResults->m_fI1Ie);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("I2(Ie)","TripI2Ie","Ie","number",pResults->m_fI2Ie);
	pXmlSierialize->xml_serialize("I2A","TripI2A","In/A","number",pResults->m_fI2);
	pXmlSierialize->xml_serialize("�ƶ�����","Ir","","number",pParas->m_fIbias);
#else
  pXmlSierialize->xml_serialize(/* "�������" */ g_sLangTxt_Native_SearchStart.GetString(), "SearchBegin", "", "number", pParas->m_fSearchBegin);
  pXmlSierialize->xml_serialize(/* "��ǰֵ" */ g_sLangTxt_Native_CurrentValue.GetString(), "CurrSearchVal", "", "number", pParas->m_fCurrScanVal);
  pXmlSierialize->xml_serialize(/* "�����յ�" */ g_sLangTxt_Native_SearchEnd.GetString(), "SearchEnd", "", "number", pParas->m_fSearchEnd);
  pXmlSierialize->xml_serialize(/* "�������䳤��" */ g_sLangTxt_Native_SearchLen.GetString(), "SearchArea", "", "number", pParas->m_fSearchArea);
  pXmlSierialize->xml_serialize("I1(Ie)", "TripI1Ie", "Ie", "number", pResults->m_fI1Ie);
  pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
  pXmlSierialize->xml_serialize("I2(Ie)", "TripI2Ie", "Ie", "number", pResults->m_fI2Ie);
  pXmlSierialize->xml_serialize("I2A", "TripI2A", "In/A", "number", pResults->m_fI2);
  pXmlSierialize->xml_serialize(/* "�ƶ�����" */ g_sLangTxt_Native_ControlCurrent.GetString(), "Ir", "", "number", pParas->m_fIbias);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_common_fault_paras(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2022.5.12 caoxc
	if(!pXmlSierialize->xml_serialize("��Ŀ����", "TestName", "", "string", pParas->m_pszTestName))
	{
		memset(pParas->m_pszTestName,0,32);
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�Ƿ��Զ�����","_AutoTest","","number",pParas->m_nAutoSearch);
	pXmlSierialize->xml_serialize("�仯ʼֵ","BeginVal","In/A","number",pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize("�仯��ֵ","EndVal","In/A","number",pParas->m_fScanTo);
	pXmlSierialize->xml_serialize("���Ծ���","Step","In/A","number",pParas->m_fStep);
	pXmlSierialize->xml_serialize("�ƶ�����","Ir","A","number",pParas->m_fIbias);
	pXmlSierialize->xml_serialize("��������","FaultType","","PsuDiffFaultType",pParas->m_nPhase);
	pXmlSierialize->xml_serialize("�������ֵ","IdSetting","A","number",pParas->m_fIdSetting);
#else
  pXmlSierialize->xml_serialize(/* "�Ƿ��Զ�����" */ g_sLangTxt_Native_AutoSearch.GetString(), "_AutoTest", "", "number", pParas->m_nAutoSearch);
  pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "In/A", "number", pParas->m_fScanFrom);
  pXmlSierialize->xml_serialize(/* "�仯��ֵ" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "In/A", "number", pParas->m_fScanTo);
  pXmlSierialize->xml_serialize(/* "���Ծ���" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "In/A", "number", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "�ƶ�����" */ g_sLangTxt_State_BrakingCur.GetString(), "Ir", "A", "number", pParas->m_fIbias);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "", "PsuDiffFaultType", pParas->m_nPhase);
  pXmlSierialize->xml_serialize(/* "�������ֵ" */ g_sLangTxt_Native_DiffCurrentSetVal.GetString(), "IdSetting", "A", "number", pParas->m_fIdSetting);
#endif
}

void stt_xml_serialize_common_sys_paras(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	BOOL bFind = pXmlSierialize->xml_serialize("׼��ʱ��","PrepareTime","s","number",pParas->m_fPreTime);
	pXmlSierialize->xml_serialize("����ǰʱ��","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	if(!bFind)
	{
		pParas->m_fPreTime = pParas->m_fPreFaultTime;
	}
	pXmlSierialize->xml_serialize("����ʱ��","FaultTime","s","number",pParas->m_fFaultTime);
	pXmlSierialize->xml_serialize("CT����","CTPoint","","CTPositionPnv",pParas->m_bCTStarPoint);
	pXmlSierialize->xml_serialize("Ir�ƶ�����","IrEquation","","IrEquationPnv",pParas->m_nIbiasCal);
	pXmlSierialize->xml_serialize("K1","K","","set",pParas->m_fFactor1);
	pXmlSierialize->xml_serialize("K2","K2","","number",pParas->m_fFactor2);
// 	pXmlSierialize->xml_serialize("�����","Inom","","number",pParas->m_fInom);
// 	pXmlSierialize->xml_serialize("���ѹ","Vnom","","number",pParas->m_fVnom);
// 	pXmlSierialize->xml_serialize("�Ƶ��","Fnom","Hz","number",pParas->m_fFnom);
	pXmlSierialize->xml_serialize("��һ���ѹ��̬���ֵ","Vg1","V","number",pParas->m_fVg1);
	pXmlSierialize->xml_serialize("�ڶ����ѹ��̬���ֵ","Vg2","V","number",pParas->m_fVg2);
	pXmlSierialize->xml_serialize("��һ���ѹ����̬���������ֵ","Vg1_fault","V","number",pParas->m_fVg1_fault);
	pXmlSierialize->xml_serialize("�ڶ����ѹ����̬���������ֵ","Vg2_fault","V","number",pParas->m_fVg2_fault);

	pXmlSierialize->xml_serialize("ƽ��ϵ�����÷�ʽ","KPSetMode","","KpSetMode",pParas->m_nKcal );
	pXmlSierialize->xml_serialize("��ѹ��ƽ��ϵ������ֵ","KphSet","","number",pParas->m_fKph);
	pXmlSierialize->xml_serialize("��ѹ��ƽ��ϵ������ֵ","KpmSet","","number",pParas->m_fKpm);
	pXmlSierialize->xml_serialize("��ѹ��ƽ��ϵ������ֵ","KplSet","","number",pParas->m_fKpl);
	pXmlSierialize->xml_serialize("��ѹ�������","Sn","MVA","number",pParas->m_fSN);
	pXmlSierialize->xml_serialize("��ѹ����ѹ","HUn","kV","number",pParas->m_fUh);
	pXmlSierialize->xml_serialize("��ѹ��CT���","HCt","","number",pParas->m_fCTh);
	pXmlSierialize->xml_serialize("��ѹ����ѹ","MUn","kV","number",pParas->m_fUm);
	pXmlSierialize->xml_serialize("��ѹ��CT���","MCt","","number",pParas->m_fCTm);
	pXmlSierialize->xml_serialize("��ѹ����ѹ","LUn","kV","number",pParas->m_fUl);
	pXmlSierialize->xml_serialize("��ѹ��CT���","LCt","","number",pParas->m_fCTl);
	pXmlSierialize->xml_serialize("��ѹ�����������ʽ","WindH","","DiffConnectMode",pParas->m_nWindH);
	pXmlSierialize->xml_serialize("��ѹ�����������ʽ","WindM","","DiffConnectMode",pParas->m_nWindM);
	pXmlSierialize->xml_serialize("��ѹ�����������ʽ","WindL","","DiffConnectMode",pParas->m_nWindL);
	pXmlSierialize->xml_serialize("�������������","AdoptWind","","TransHMLSel",pParas->m_nWindSide);
	pXmlSierialize->xml_serialize("�����ڲ���λУ����ʽ","PhCorrectMode","","TransPhCorrectModePnv",pParas->m_nAngleMode);
	pXmlSierialize->xml_serialize("��������֮��ǲ�(�ӵ���)","TransGroupMode","","ConnModePnv",pParas->m_nConnectMode);
	pXmlSierialize->xml_serialize("ƽ��ϵ������","JXFactor","","JXFactorPnv",pParas->m_nJXFactor);
	pXmlSierialize->xml_serialize("��������","SearchMode","","SearchModePnv",pParas->m_nSearchMode);
	//��λ������
	pXmlSierialize->xml_serialize("��ѹ��CTһ��ֵ","CTPh","","number",pParas->m_fCTPh);
	pXmlSierialize->xml_serialize("��ѹ��CTһ��ֵ","CTPm","","number",pParas->m_fCTPm);
	pXmlSierialize->xml_serialize("��ѹ��CTһ��ֵ","CTPl","","number",pParas->m_fCTPl);
	pXmlSierialize->xml_serialize("��ѹ��CT����ֵ","CTSh","","number",pParas->m_fCTSh);
	pXmlSierialize->xml_serialize("��ѹ��CT����ֵ","CTSm","","number",pParas->m_fCTSm);
	pXmlSierialize->xml_serialize("��ѹ��CT����ֵ","CTSl","","number",pParas->m_fCTSl);

	// ��ֵ���
	pXmlSierialize->xml_serialize("��ֵ������ʽ","MinAxis","","SettingModePnv",pParas->m_bMinAxis);//++++Ĭ�ϱ���ֵ
	pXmlSierialize->xml_serialize("��׼����ѡ��", "InSel", "", "CurrentSelPnv", pParas->m_nInSel);
	pXmlSierialize->xml_serialize("��׼�����趨ֵ", "InSet", "A", "number", pParas->m_fIbase);
	pXmlSierialize->xml_serialize("��ٶϵ���","IQuick","In/A","number",pParas->m_fIsd);
	pXmlSierialize->xml_serialize("��ż�����","IDoor","In/A","number",pParas->m_fIcdqd);

	pXmlSierialize->xml_serialize("�����ƶ��յ���","KneePoints","","number",pParas->m_nKneePoints);
	pXmlSierialize->xml_serialize("�����ƶ��յ�1����","Limp1","","number",pParas->m_fIp1);
	pXmlSierialize->xml_serialize("�����ƶ��յ�2����","Limp2","","number",pParas->m_fIp2);
	pXmlSierialize->xml_serialize("�����ƶ��յ�3����","Limp3","","number",pParas->m_fIp3);

	pXmlSierialize->xml_serialize("������б��","Kid0","","number",pParas->m_fKid0);
	pXmlSierialize->xml_serialize("���������ƶ�����б��1","Kid1","","number",pParas->m_fKid1);
	pXmlSierialize->xml_serialize("���������ƶ�����б��2","Kid2","","number",pParas->m_fKid2);
	pXmlSierialize->xml_serialize("���������ƶ�����б��3","Kid3","","number",pParas->m_fKid3);

	//2022.5.16 caoxc
	pXmlSierialize->xml_serialize("����г���ƶ�ϵ��","CoefHarm2","","number",pParas->m_fCoefHarm2);
	pXmlSierialize->xml_serialize("����г���ƶ�ϵ��","CoefHarm3","","number",pParas->m_fCoefHarm3);
	pXmlSierialize->xml_serialize("���г���ƶ�ϵ��","CoefHarm5","","number",pParas->m_fCoefHarm5);

	pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
  //	pXmlSierialize->xml_serialize("׼��ʱ��","PrepareTime","s","number",pParas->m_fPreTime);
  pXmlSierialize->xml_serialize(/* "����ǰʱ��" */ g_sLangTxt_Native_PreFautTime.GetString(), "PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
  pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Gradient_FailTime.GetString(), "FaultTime", "s", "number", pParas->m_fFaultTime);
  pXmlSierialize->xml_serialize(/* "CT����" */ g_sLangTxt_State_CTpolarity.GetString(), "CTPoint", "", "CTPositionPnv", pParas->m_bCTStarPoint);
  pXmlSierialize->xml_serialize(/* "Ir�ƶ�����" */ g_sLangTxt_Native_IrBrakeEq.GetString(), "IrEquation", "", "IrEquationPnv", pParas->m_nIbiasCal);
  pXmlSierialize->xml_serialize("K1", "K", "", "set", pParas->m_fFactor1);
  pXmlSierialize->xml_serialize("K2", "K2", "", "number", pParas->m_fFactor2);
  // 	pXmlSierialize->xml_serialize("�����","Inom","","number",pParas->m_fInom);
  // 	pXmlSierialize->xml_serialize("���ѹ","Vnom","","number",pParas->m_fVnom);
  // 	pXmlSierialize->xml_serialize("�Ƶ��","Fnom","Hz","number",pParas->m_fFnom);
  pXmlSierialize->xml_serialize(/* "��һ���ѹ��̬���ֵ" */ g_sLangTxt_Native_FirstVoltNormOutput.GetString(), "Vg1", "V", "number", pParas->m_fVg1);
  pXmlSierialize->xml_serialize(/* "�ڶ����ѹ��̬���ֵ" */ g_sLangTxt_Native_SecondVoltNormOutput.GetString(), "Vg2", "V", "number", pParas->m_fVg2);
  pXmlSierialize->xml_serialize(/* "��һ���ѹ����̬���������ֵ" */ g_sLangTxt_Native_VoltFaultState.GetString(), "Vg1_fault", "V", "number", pParas->m_fVg1_fault);
  pXmlSierialize->xml_serialize(/* "�ڶ����ѹ����̬���������ֵ" */ g_sLangTxt_Native_VoltFaultState2.GetString(), "Vg2_fault", "V", "number", pParas->m_fVg2_fault);

  pXmlSierialize->xml_serialize(/* "ƽ��ϵ�����÷�ʽ" */ g_sLangTxt_Native_BalanceMode.GetString(), "KPSetMode", "", "KpSetMode", pParas->m_nKcal);
  pXmlSierialize->xml_serialize(/* "��ѹ��ƽ��ϵ������ֵ" */ g_sLangTxt_Native_HVBalanceCoeff.GetString(), "KphSet", "", "number", pParas->m_fKph);
  pXmlSierialize->xml_serialize(/* "��ѹ��ƽ��ϵ������ֵ" */ g_sLangTxt_Native_MVBalanceCoeff.GetString(), "KpmSet", "", "number", pParas->m_fKpm);
  pXmlSierialize->xml_serialize(/* "��ѹ��ƽ��ϵ������ֵ" */ g_sLangTxt_Native_LVBalanceCoeff.GetString(), "KplSet", "", "number", pParas->m_fKpl);
  pXmlSierialize->xml_serialize(/* "��ѹ�������" */ g_sLangTxt_Native_TransfRatedCapacity.GetString(), "Sn", "MVA", "number", pParas->m_fSN);
  pXmlSierialize->xml_serialize(/* "��ѹ����ѹ" */ g_sLangTxt_Native_HighVoltSideRatedVolt.GetString(), "HUn", "kV", "number", pParas->m_fUh);
  pXmlSierialize->xml_serialize(/* "��ѹ��CT���" */ g_sLangTxt_Native_HVCTRatio.GetString(), "HCt", "", "number", pParas->m_fCTh);
  pXmlSierialize->xml_serialize(/* "��ѹ����ѹ" */ g_sLangTxt_Native_MedVoltSideRatedVolt.GetString(), "MUn", "kV", "number", pParas->m_fUm);
  pXmlSierialize->xml_serialize(/* "��ѹ��CT���" */ g_sLangTxt_Native_MVCTRatio.GetString(), "MCt", "", "number", pParas->m_fCTm);
  pXmlSierialize->xml_serialize(/* "��ѹ����ѹ" */ g_sLangTxt_Native_LowVoltSideRatedVolt.GetString(), "LUn", "kV", "number", pParas->m_fUl);
  pXmlSierialize->xml_serialize(/* "��ѹ��CT���" */ g_sLangTxt_Native_LVCTRatio.GetString(), "LCt", "", "number", pParas->m_fCTl);
  pXmlSierialize->xml_serialize(/* "��ѹ�����������ʽ" */ g_sLangTxt_State_Hswindwirtype.GetString(), "WindH", "", "DiffConnectMode", pParas->m_nWindH);
  pXmlSierialize->xml_serialize(/* "��ѹ�����������ʽ" */ g_sLangTxt_Native_MedVoltWindingConnType.GetString(), "WindM", "", "DiffConnectMode", pParas->m_nWindM);
  pXmlSierialize->xml_serialize(/* "��ѹ�����������ʽ" */ g_sLangTxt_State_Lswindwirtype.GetString(), "WindL", "", "DiffConnectMode", pParas->m_nWindL);
  pXmlSierialize->xml_serialize(/* "�������������" */ g_sLangTxt_Native_TestCoil.GetString(), "AdoptWind", "", "TransHMLSel", pParas->m_nWindSide);
  pXmlSierialize->xml_serialize(/* "�����ڲ���λУ����ʽ" */ g_sLangTxt_Native_ProtPhaseCorr.GetString(), "PhCorrectMode", "", "TransPhCorrectModePnv", pParas->m_nAngleMode);
  pXmlSierialize->xml_serialize(/* "��������֮��ǲ�(�ӵ���)" */ g_sLangTxt_Native_AngleDiffClockHrsTestWindings.GetString(), "TransGroupMode", "", "ConnModePnv", pParas->m_nConnectMode);
  pXmlSierialize->xml_serialize(/* "ƽ��ϵ������" */ g_sLangTxt_State_Bfactorcalculation.GetString(), "JXFactor", "", "JXFactorPnv", pParas->m_nJXFactor);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_SearchMeth.GetString(), "SearchMode", "", "SearchModePnv", pParas->m_nSearchMode);
  // ��λ������
  pXmlSierialize->xml_serialize(/* "��ѹ��CTһ��ֵ" */ g_sLangTxt_Native_HVSideCTPrimVal.GetString(), "CTPh", "", "number", pParas->m_fCTPh);
  pXmlSierialize->xml_serialize(/* "��ѹ��CTһ��ֵ" */ g_sLangTxt_Native_MVSideCTPrimVal.GetString(), "CTPm", "", "number", pParas->m_fCTPm);
  pXmlSierialize->xml_serialize(/* "��ѹ��CTһ��ֵ" */ g_sLangTxt_Native_LVSideCTPrimVal.GetString(), "CTPl", "", "number", pParas->m_fCTPl);
  pXmlSierialize->xml_serialize(/* "��ѹ��CT����ֵ" */ g_sLangTxt_Native_HVSide2CTPrimVal.GetString(), "CTSh", "", "number", pParas->m_fCTSh);
  pXmlSierialize->xml_serialize(/* "��ѹ��CT����ֵ" */ g_sLangTxt_Native_MVSide2CTPrimVal.GetString(), "CTSm", "", "number", pParas->m_fCTSm);
  pXmlSierialize->xml_serialize(/* "��ѹ��CT����ֵ" */ g_sLangTxt_Native_LVSide2CTPrimVal.GetString(), "CTSl", "", "number", pParas->m_fCTSl);

  // ��ֵ���
  pXmlSierialize->xml_serialize(/* "��ֵ������ʽ" */ g_sLangTxt_Native_DevSetMethod.GetString(), "MinAxis", "", "SettingModePnv", pParas->m_bMinAxis);  //++++Ĭ�ϱ���ֵ
  pXmlSierialize->xml_serialize(/* "��׼����ѡ��" */ g_sLangTxt_Native_RefCurrentSel.GetString(), "InSel", "", "CurrentSelPnv", pParas->m_nInSel);
  pXmlSierialize->xml_serialize(/* "��׼�����趨ֵ" */ g_sLangTxt_Native_BaseCurrSet.GetString(), "InSet", "A", "number", pParas->m_fIbase);
  pXmlSierialize->xml_serialize(/* "��ٶϵ���" */ g_sLangTxt_Native_DiffQuickBreakCurr.GetString(), "IQuick", "In/A", "number", pParas->m_fIsd);
  pXmlSierialize->xml_serialize(/* "��ż�����" */ g_sLangTxt_Native_DiffThreshCurrent.GetString(), "IDoor", "In/A", "number", pParas->m_fIcdqd);

  pXmlSierialize->xml_serialize(/* "�����ƶ��յ���" */ g_sLangTxt_Native_RatioBrakeTurnPts.GetString(), "KneePoints", "", "number", pParas->m_nKneePoints);
  pXmlSierialize->xml_serialize(/* "�����ƶ��յ�1����" */ g_sLangTxt_Native_RatioBrakeTurn1Curr.GetString(), "Limp1", "", "number", pParas->m_fIp1);
  pXmlSierialize->xml_serialize(/* "�����ƶ��յ�2����" */ g_sLangTxt_Native_RatioBrakeTurn2Curr.GetString(), "Limp2", "", "number", pParas->m_fIp2);
  pXmlSierialize->xml_serialize(/* "�����ƶ��յ�3����" */ g_sLangTxt_Native_RatioBrakeTurn3Curr.GetString(), "Limp3", "", "number", pParas->m_fIp3);

  pXmlSierialize->xml_serialize(/* "������б��" */ g_sLangTxt_Native_StartSegSlope.GetString(), "Kid0", "", "number", pParas->m_fKid0);
  pXmlSierialize->xml_serialize(/* "���������ƶ�����б��1" */ g_sLangTxt_Native_FundRatioBrkSlope1.GetString(), "Kid1", "", "number", pParas->m_fKid1);
  pXmlSierialize->xml_serialize(/* "���������ƶ�����б��2" */ g_sLangTxt_Native_FundRatioBrkSlope2.GetString(), "Kid2", "", "number", pParas->m_fKid2);
  pXmlSierialize->xml_serialize(/* "���������ƶ�����б��3" */ g_sLangTxt_Native_FundRatioBrkSlope3.GetString(), "Kid3", "", "number", pParas->m_fKid3);

  // 2022.5.16 caoxc
  pXmlSierialize->xml_serialize(/* "����г���ƶ�ϵ��" */ g_sLangTxt_Native_SecHarBrkCoef.GetString(), "CoefHarm2", "", "number", pParas->m_fCoefHarm2);
  pXmlSierialize->xml_serialize(/* "����г���ƶ�ϵ��" */ g_sLangTxt_Native_ThiHarBrkCoef.GetString(), "CoefHarm3", "", "number", pParas->m_fCoefHarm3);
  pXmlSierialize->xml_serialize(/* "���г���ƶ�ϵ��" */ g_sLangTxt_Native_FivHarBrkCoef.GetString(), "CoefHarm5", "", "number", pParas->m_fCoefHarm5);

  pXmlSierialize->xml_serialize(/* "�����߼�" */ g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_thr(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_thr(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize_rate(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_rate(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ǰ����ֵ","CurrentId","In/A","number",pResults->m_fIdiffSettingValue);
	pXmlSierialize->xml_serialize("�����ֵ","TripId","In/A","number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("���������","ActId","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("�ƶ�����","TripIr","In/A","number",pResults->m_fIbiasValue);
	pXmlSierialize->xml_serialize("I1(Ie)","TripI1Ie","Ie","number",pResults->m_fI1Ie);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("I2(Ie)","TripI2Ie","Ie","number",pResults->m_fI2Ie);
	pXmlSierialize->xml_serialize("I2A","TripI2A","In/A","number",pResults->m_fI2);
	pXmlSierialize->xml_serialize("�����ƶ�ϵ��","RateKid","","number",pResults->m_fRateKid); //yyj add 
#else
  pXmlSierialize->xml_serialize(/* "��ǰ����ֵ" */ g_sLangTxt_Native_CurrSearchVal.GetString(), "CurrentId", "In/A", "number", pResults->m_fIdiffSettingValue);
  pXmlSierialize->xml_serialize(/* "�����ֵ" */ g_sLangTxt_Native_DiffActionVal.GetString(), "TripId", "In/A", "number", pResults->m_fIdiffActValue);
  pXmlSierialize->xml_serialize(/* "���������" */ g_sLangTxt_Native_DiffActionDesc.GetString(), "ActId", "", "number", pResults->m_nActFlag);
  pXmlSierialize->xml_serialize(/* "�ƶ�����" */ g_sLangTxt_Native_ControlCurrent.GetString(), "TripIr", "In/A", "number", pResults->m_fIbiasValue);
  pXmlSierialize->xml_serialize("I1(Ie)", "TripI1Ie", "Ie", "number", pResults->m_fI1Ie);
  pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
  pXmlSierialize->xml_serialize("I2(Ie)", "TripI2Ie", "Ie", "number", pResults->m_fI2Ie);
  pXmlSierialize->xml_serialize("I2A", "TripI2A", "In/A", "number", pResults->m_fI2);
  pXmlSierialize->xml_serialize(/* "�����ƶ�ϵ��" */ g_sLangTxt_Native_ProportionalBrakingFactor.GetString(), "RateKid", "", "number", pResults->m_fRateKid);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_quick(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_quick(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize_harm(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2022.5.16 caoxc
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

void stt_xml_serialize_harm(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize_acttime(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2022.5.16 caoxc
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

void stt_xml_serialize_acttime(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��", "TripTime", "s", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("��������","ActFlag","","number",pResults->m_nActFlag);
#else
  pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "s", "number", pResults->m_fTripTime);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
#endif
}

void stt_xml_serialize_6i_rate_pnv(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
    stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
    pXmlSierialize->xml_serialize("���Ϻ����ʱ��","AfterFaultTime","s","number",pParas->m_fAfterFaultTime);
    pXmlSierialize->xml_serialize("����ǰ����","m_PreFaultIp","","number",pParas->m_fPreFaultIp);
    pXmlSierialize->xml_serialize("�����ѹ��ֵ","VzAmp","","number",pParas->m_fVzAmp);
    pXmlSierialize->xml_serialize("�������ֵ","IdSet","A","number",pParas->m_fIdSetting);
    pXmlSierialize->xml_serialize("I1���������ϵ��","KP1","","number",pParas->m_fKph);//���ոߵͲ�洢�������������鸳ֵxuzhantao240301
    pXmlSierialize->xml_serialize("I2���������ϵ��","KP2","","number",pParas->m_fKpl);
    pXmlSierialize->xml_serialize("�����߼�","AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);

#ifndef _STT_NOT_IN_TEST_SERVER_
	pXmlSierialize->xml_serialize("0-����Ŀ��뿪����1-����+��չ�Ŀ��뿪��","BinBoutMode","","long",g_theSystemConfig->m_nBinBoutMode);
#endif

    stt_xml_serialize_diff_6i_binary_in_pnv(pParas->m_binIn,pXmlSierialize);
    stt_xml_serialize_diff_6i_binary_out_pnv(pParas->m_binOut, pXmlSierialize);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_6i_rate_pnv(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
    {
    stt_xml_serialize_rate(pResults,pXmlSierialize);
    pXmlSierialize->xml_serialize("�������","TripFlag","","number",pResults->m_nActFlag);
    pXmlSierialize->xml_serialize("����ж�","RsltJdg","","number",pResults->m_nActFlag);
    pXmlSierialize->xml_serialize("�������","RsltDsc","","number",pResults->m_nActFlag);
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_6i_harm_pnv(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("�仯ʼֵ","BeginVal","%","number",pParas->m_fScanFrom);
    pXmlSierialize->xml_serialize("�仯��ֵ","EndVal","%","number",pParas->m_fScanTo);
    pXmlSierialize->xml_serialize("���Ծ���","Step","%","number",pParas->m_fStep);
    pXmlSierialize->xml_serialize("�����","Id","In/A","number",pParas->m_fIdiff);
    pXmlSierialize->xml_serialize("г������","HarmIndex","","DiffHarmIndex",pParas->m_nHarmIndex);
    pXmlSierialize->xml_serialize("��������","FaultType","","PsuDiffFaultType",pParas->m_nPhase);
    pXmlSierialize->xml_serialize("г���ƶ�ϵ����ֵ","RateHarmSet","","number",pParas->m_fCoefHarm2);
    pXmlSierialize->xml_serialize("���Ϻ����ʱ��","AfterFaultTime","s","number",pParas->m_fAfterFaultTime);
    pXmlSierialize->xml_serialize("�����ѹ��ֵ","VzAmp","","number",pParas->m_fVzAmp);
    pXmlSierialize->xml_serialize("I1���������ϵ��","KP1","","number",pParas->m_fKph);//���ոߵͲ�洢�������������鸳ֵxuzhantao240301
    pXmlSierialize->xml_serialize("I2���������ϵ��","KP2","","number",pParas->m_fKpl);
    pXmlSierialize->xml_serialize("�����߼�","AndOr","","InPutLogic",pParas->m_nBinLogic);
    pXmlSierialize->xml_serialize("г��ʩ�Ӳ�","HarmPos","","HarmPos",pParas->m_nHarmPos);
    pXmlSierialize->xml_serialize("Ir�ƶ�����","IrEquation","","IrEquationI1I2",pParas->m_nIdiffCal);
    pXmlSierialize->xml_serialize("�����ڲ�����������ʽ","PhCorrectMode","","TransPhCorrectMode",pParas->m_nY0CorrectMode);
    stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
    stt_xml_serialize_diff_6i_binary_in_pnv(pParas->m_binIn,pXmlSierialize);
    stt_xml_serialize_diff_6i_binary_out_pnv(pParas->m_binOut, pXmlSierialize);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_6i_harm_pnv(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_harm(pResults,pXmlSierialize);
    pXmlSierialize->xml_serialize("�������","TripFlag","","number",pResults->m_nActFlag);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttXmlSerializeBase* stt_xml_serialize(tmt_DiffCurrThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
//	stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest) == 0)
		{
			stt_xml_serialize_thr(&(pTests->m_oDiffCurrParas),  pXmlParas);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("����", "ThrType", "", "number", ((tmt_DiffCurrThrTest*)pTests)->m_nThrType);
#else
      pXmlParas->xml_serialize(/* "����" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_DiffCurrThrTest *)pTests)->m_nThrType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest) == 0)
		{
			stt_xml_serialize_rate(&(pTests->m_oDiffCurrParas), pXmlParas);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("����", "RateType", "", "number", ((tmt_DiffCurrRateTest*)pTests)->m_nRateType);
#else
      pXmlParas->xml_serialize(/* "����" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_DiffCurrRateTest *)pTests)->m_nRateType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest) == 0)
		{
			stt_xml_serialize_quick(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest) == 0)
		{
			stt_xml_serialize_harm(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest) == 0)
		{
			stt_xml_serialize_acttime(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_Diff6IRateRestrainSearchTest) == 0)
        {
            stt_xml_serialize_6i_rate_pnv(&(pTests->m_oDiffCurrParas),  pXmlParas);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_Diff6IHarmRestrainSearchTest) == 0)
        {
            stt_xml_serialize_6i_harm_pnv(&(pTests->m_oDiffCurrParas),  pXmlParas);
        }
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest) == 0)
		{
			stt_xml_serialize_thr(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest) == 0)
		{
			stt_xml_serialize_rate(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest) == 0)
		{
			stt_xml_serialize_quick(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest) == 0)
		{
			stt_xml_serialize_harm(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest) == 0)
		{
			stt_xml_serialize_acttime(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_Diff6IRateRestrainSearchTest) == 0)
        {
            stt_xml_serialize_6i_rate_pnv(&pTests->m_oDiffCurrResults,  pXmlResults);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_Diff6IHarmRestrainSearchTest) == 0)
        {
            stt_xml_serialize_6i_harm_pnv(&pTests->m_oDiffCurrResults,  pXmlResults);
        }
	}

	return pXmlParas;
}

void stt_xml_serialize(tmt_DiffCurrThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly)
{
	if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_thr(&(pTests->m_oDiffCurrParas), pXmlSerialize);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("����", "ThrType", "", "number", ((tmt_DiffCurrThrTest*)pTests)->m_nThrType);
#else
      pXmlSerialize->xml_serialize(/* "����" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_DiffCurrThrTest *)pTests)->m_nThrType);
#endif
		}

		stt_xml_serialize_thr(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_rate(&(pTests->m_oDiffCurrParas), pXmlSerialize);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("����", "RateType", "", "number", ((tmt_DiffCurrRateTest*)pTests)->m_nRateType);
#else
      pXmlSerialize->xml_serialize(/* "����" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_DiffCurrRateTest *)pTests)->m_nRateType);
#endif
		}

		stt_xml_serialize_rate(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_quick(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_quick(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_harm(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_harm(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_acttime(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_acttime(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}

     else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_Diff6IRateRestrainSearchTest) == 0)
      {
            if(!bResultOnly)
            {
                stt_xml_serialize_6i_rate_pnv(&(pTests->m_oDiffCurrParas), pXmlSerialize);
            }

            stt_xml_serialize_6i_rate_pnv(&(pTests->m_oDiffCurrParas), pXmlSerialize);
    }
    else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_Diff6IHarmRestrainSearchTest) == 0)
     {
           if(!bResultOnly)
           {
               stt_xml_serialize_6i_harm_pnv(&(pTests->m_oDiffCurrParas), pXmlSerialize);
           }

           stt_xml_serialize_6i_harm_pnv(&(pTests->m_oDiffCurrParas), pXmlSerialize);
   }
}
