#include "stdafx.h"
#include "tmt_power_direction_test.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_PowerDirectionParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_PowerDirectionParas));
	pParas->init();
}

void stt_init_paras(tmt_PowerDirectionParas_I *pParas)
{
    memset(&pParas, 0, sizeof(tmt_PowerDirectionParas));
    pParas->init();
}

void stt_init_paras_ex(tmt_PowerDirectionParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_PowerDirectionParasEx));
	pParas->init();
}


void stt_init_results(tmt_PowerDirectionResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_PowerDirectionResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_PowerDirectionParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("������","TestPhase","","PsuPDTestPhase",pParas->m_nTestPhase);
	pXmlSierialize->xml_serialize("������","FaultPhase","","PsuPDFaultPhase",pParas->m_nFaultPhase);
	pXmlSierialize->xml_serialize("���ϵ�ѹ","FaultVolt","V","number",pParas->m_fSCVoltage);
	pXmlSierialize->xml_serialize("���ϵ���","FaultCurrent","A","number",pParas->m_fSCCurrent);
	pXmlSierialize->xml_serialize("�仯ʼֵ","StartValue","��","number",pParas->m_fStart);
	pXmlSierialize->xml_serialize("�仯��ֵ","EndValue","��","number",pParas->m_fStop);
	pXmlSierialize->xml_serialize("�仯����","StepValue","��","number",pParas->m_fStep);
	pXmlSierialize->xml_serialize("����ʱ��","FaultTime","s","number",pParas->m_fStepTime);

	pXmlSierialize->xml_serialize("�Ƕȶ���","AngleMode","","PsuPDAngleMode",pParas->m_nAngleMode);
	pXmlSierialize->xml_serialize("���߷�ʽ","ConnectMode","","ConnectType",pParas->m_nConnectMode);
#else
  pXmlSierialize->xml_serialize(/* "������" */ g_sLangTxt_State_Testphase.GetString(), "TestPhase", "", "PsuPDTestPhase", pParas->m_nTestPhase);
  pXmlSierialize->xml_serialize(/* "������" */ g_sLangTxt_CharLib_FaultPhase.GetString(), "FaultPhase", "", "PsuPDFaultPhase", pParas->m_nFaultPhase);
  pXmlSierialize->xml_serialize(/* "���ϵ�ѹ" */ g_sLangTxt_Native_FaultVoltage.GetString(), "FaultVolt", "V", "number", pParas->m_fSCVoltage);
  pXmlSierialize->xml_serialize(/* "���ϵ���" */ g_sLangTxt_Native_FaultCurrValue.GetString(), "FaultCurrent", "A", "number", pParas->m_fSCCurrent);
  pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */ g_sLangTxt_Gradient_Init.GetString(), "StartValue", "��", "number", pParas->m_fStart);
  pXmlSierialize->xml_serialize(/* "�仯��ֵ" */ g_sLangTxt_Gradient_Finish.GetString(), "EndValue", "��", "number", pParas->m_fStop);
  pXmlSierialize->xml_serialize(/* "�仯����" */ g_sLangTxt_Gradient_Step.GetString(), "StepValue", "��", "number", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Gradient_Time.GetString(), "FaultTime", "s", "number", pParas->m_fStepTime);

  pXmlSierialize->xml_serialize(/* "�Ƕȶ���" */ g_sLangTxt_Native_AngDef.GetString(), "AngleMode", "", "PsuPDAngleMode", pParas->m_nAngleMode);
  pXmlSierialize->xml_serialize(/* "���߷�ʽ" */ g_sLangTxt_Native_ConnMethod.GetString(), "ConnectMode", "", "ConnectType", pParas->m_nConnectMode);
#endif
	stt_xml_serialize_common(pParas,pXmlSierialize);

	//����ֵ
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("���������","MTA","","number",pParas->m_fMaxSensAngle);
	pXmlSierialize->xml_serialize(_T("��ǰ�Ƕ�"),_T("Lead"),"","number",pParas->m_fLeadAngle);
	pXmlSierialize->xml_serialize(_T("�ͺ�Ƕ�"),_T("Lag"),"","number",pParas->m_fLagAngle);
#else
  pXmlSierialize->xml_serialize(/* "���������" */ g_sLangTxt_Gradient_MaxAngle.GetString(), "MTA", "", "number", pParas->m_fMaxSensAngle);
  pXmlSierialize->xml_serialize(/* _T("��ǰ�Ƕ�") */ g_sLangTxt_Native_LeadAngle.GetString(), _T("Lead"), "", "number", pParas->m_fLeadAngle);
  pXmlSierialize->xml_serialize(/* _T("�ͺ�Ƕ�") */ g_sLangTxt_Native_LagAngle.GetString(), _T("Lag"), "", "number", pParas->m_fLagAngle);
#endif
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize(tmt_PowerDirectionParas_I *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("��������Χ","AngleRange","","number",pParas->m_fAngleRange);
    pXmlSierialize->xml_serialize("�Ƕ�ԣ��","AngleMargin","","number",pParas->m_fAngleMargin);
    stt_xml_serialize((tmt_PowerDirectionParas *)pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_ex(tmt_PowerDirectionParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�仯ʼֵ(���ʽ)", "BeginValExp", "", "string",pParas->m_pszStart);
	pXmlSierialize->xml_serialize("�仯��ֵ(���ʽ)", "EndValExp", "", "string", pParas->m_pszStop );
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)", "StepTimeExp", "", "string", pParas->m_pszStepTime);
	pXmlSierialize->xml_serialize("��·��ѹ(���ʽ)", "VSet1Exp", "", "string", pParas->m_pszSCVoltage);
	pXmlSierialize->xml_serialize("��·����(���ʽ)", "ISet1Exp", "", "string",pParas->m_pszSCCurrent);
#else
  pXmlSierialize->xml_serialize(/* "�仯ʼֵ(���ʽ)" */ g_sLangTxt_Native_VarStartValue.GetString(), "BeginValExp", "", "string", pParas->m_pszStart);
  pXmlSierialize->xml_serialize(/* "�仯��ֵ(���ʽ)" */ g_sLangTxt_Native_VarEndValue.GetString(), "EndValExp", "", "string", pParas->m_pszStop);
  pXmlSierialize->xml_serialize(/* "����ʱ��(���ʽ)" */ g_sLangTxt_Native_StepTime.GetString(), "StepTimeExp", "", "string", pParas->m_pszStepTime);
  pXmlSierialize->xml_serialize(/* "��·��ѹ(���ʽ)" */ g_sLangTxt_Native_ShortVolt.GetString(), "VSet1Exp", "", "string", pParas->m_pszSCVoltage);
  pXmlSierialize->xml_serialize(/* "��·����(���ʽ)" */ g_sLangTxt_Native_ShortCurr.GetString(), "ISet1Exp", "", "string", pParas->m_pszSCCurrent);
#endif
	stt_xml_serialize(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_power_dir(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�߽��1","AngleF","","number",pResults->m_oMaxAngle.m_fAngleF);
	pXmlSierialize->xml_serialize("�߽��2","AngleS","","number",pResults->m_oMaxAngle.m_fAngleS);
#else
  pXmlSierialize->xml_serialize(/* "�߽��1" */ g_sLangTxt_Native_BoundAngle1.GetString(), "AngleF", "", "number", pResults->m_oMaxAngle.m_fAngleF);
  pXmlSierialize->xml_serialize(/* "�߽��2" */ g_sLangTxt_Native_BoundAngle2.GetString(), "AngleS", "", "number", pResults->m_oMaxAngle.m_fAngleS);
#endif
	if (stt_xml_serialize_is_write(pXmlSierialize) || stt_xml_serialize_is_register(pXmlSierialize))//���ݴ���
	{
#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("�߽��1(����)","Angle1","","number",pResults->m_oMaxAngle.m_fAngleF);
		pXmlSierialize->xml_serialize("�߽��2(����)","Angle2","","number",pResults->m_oMaxAngle.m_fAngleS);
#else
                 pXmlSierialize->xml_serialize(/* "�߽��1(����)" */ g_sLangTxt_Native_BoundaryAngle1.GetString(), "Angle1", "", "number", pResults->m_oMaxAngle.m_fAngleF);
                pXmlSierialize->xml_serialize(/* "�߽��2(����)" */ g_sLangTxt_Native_BoundaryAngle2.GetString(), "Angle2", "", "number", pResults->m_oMaxAngle.m_fAngleS);
#endif
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("���������","MaxAngle","","number",pResults->m_oMaxAngle.m_fMaxAngle);
	pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
#else
        pXmlSierialize->xml_serialize(/* "���������" */ g_sLangTxt_Gradient_MaxAngle.GetString(), "MaxAngle", "", "number", pResults->m_oMaxAngle.m_fMaxAngle);
        pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActDsec", "", "number", pResults->m_nAct);
#endif
}

void stt_xml_serialize_pnv(tmt_PowerDirectionParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{//xxxx
    pXmlSierialize->xml_serialize("�߽�1��ֵ","AngleSet1","��","number",pParas->m_fStart);
    pXmlSierialize->xml_serialize("�߽�2��ֵ","AngleSet2","��","number",pParas->m_fStop);
    pXmlSierialize->xml_serialize("���Ծ���","Step","��","number",pParas->m_fStep);
    pXmlSierialize->xml_serialize("��������ʱ��","TSetting","s","number",pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("�ǶȲ���ƫ��","AngleOffset","��","number",pParas->m_fAngleOffset);
    pXmlSierialize->xml_serialize("�������","VarIndex","","ArcRampIndex",pParas->m_nVarIndex);

    pXmlSierialize->xml_serialize("��λ�Ե�ѹΪ�ο�","AngleRef","","BOOL",pParas->m_nAngleMode);

    pXmlSierialize->xml_serialize("����ǰ����ʱ��","RampResetTime","s","number",pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize("����ǰ����ʱ��","FaultResetTime","s","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("ÿ��ʱ��ԣ��","StepTimeAdded","s","number",pParas->m_fMarginTime);

    pXmlSierialize->xml_serialize("����Ua","Ua0","V","number",pParas->m_uiVOL[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Ub","Ub0","V","number",pParas->m_uiVOL[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Uc","Uc0","V","number",pParas->m_uiVOL[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Ia","Ia0","A","number",pParas->m_uiCUR[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Ib","Ib0","A","number",pParas->m_uiCUR[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Ic","Ic0","A","number",pParas->m_uiCUR[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua","Ua","V","number",pParas->m_uiVOL[2][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub","Ub","V","number",pParas->m_uiVOL[2][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc","Uc","V","number",pParas->m_uiVOL[2][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia","Ia","A","number",pParas->m_uiCUR[2][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib","Ib","A","number",pParas->m_uiCUR[2][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic","Ic","A","number",pParas->m_uiCUR[2][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua��λ","UaPh","��","number",pParas->m_uiVOL[2][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub��λ","UbPh","��","number",pParas->m_uiVOL[2][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc��λ","UcPh","��","number",pParas->m_uiVOL[2][2].Harm[1].fAngle);

    pXmlSierialize->xml_serialize("����Aѡ��", "_BinSelectA", "", "BOOL", pParas->m_binIn[0].nSelect);
    pXmlSierialize->xml_serialize("����Bѡ��", "_BinSelectB", "", "BOOL", pParas->m_binIn[1].nSelect);
    pXmlSierialize->xml_serialize("����Cѡ��", "_BinSelectC", "", "BOOL", pParas->m_binIn[2].nSelect);
    pXmlSierialize->xml_serialize("����Rѡ��", "_BinSelectR", "", "BOOL", pParas->m_binIn[3].nSelect);
    pXmlSierialize->xml_serialize("����aѡ��", "_BinSelecta", "", "BOOL", pParas->m_binIn[4].nSelect);
    pXmlSierialize->xml_serialize("����bѡ��", "_BinSelectb", "", "BOOL", pParas->m_binIn[5].nSelect);
    pXmlSierialize->xml_serialize("����cѡ��", "_BinSelectc", "", "BOOL", pParas->m_binIn[6].nSelect);
    pXmlSierialize->xml_serialize("����rѡ��", "_BinSelectr", "", "BOOL", pParas->m_binIn[7].nSelect);
    pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);

    pXmlSierialize->xml_serialize("����1","_Bout1","","DOutputState",pParas->m_binOut[0][0].nState);
    pXmlSierialize->xml_serialize("����2","_Bout2","","DOutputState",pParas->m_binOut[0][1].nState);
    pXmlSierialize->xml_serialize("����3","_Bout3","","DOutputState",pParas->m_binOut[0][2].nState);
    pXmlSierialize->xml_serialize("����4","_Bout4","","DOutputState",pParas->m_binOut[0][3].nState);

    pXmlSierialize->xml_serialize("����1����״̬","_BoutF1","","DOutputState",pParas->m_binOut[1][0].nState);
    pXmlSierialize->xml_serialize("����2����״̬","_BoutF2","","DOutputState",pParas->m_binOut[1][1].nState);
    pXmlSierialize->xml_serialize("����3����״̬","_BoutF3","","DOutputState",pParas->m_binOut[1][2].nState);
    pXmlSierialize->xml_serialize("����4����״̬","_BoutF4","","DOutputState",pParas->m_binOut[1][3].nState);
    pXmlSierialize->xml_serialize("��������ʱ��","_BoutHoldTime","s","number",pParas->m_binOut[1][0].fHoldTime);
}

void stt_xml_serialize_pnv_power_dir(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("�����߽�1","TripAngle1","","number",pResults->m_oMaxAngle.m_fAngleF);
    pXmlSierialize->xml_serialize("�����߽�2","TripAngle2","","number",pResults->m_oMaxAngle.m_fAngleS);
    pXmlSierialize->xml_serialize("������","LmAngle","","number",pResults->m_oMaxAngle.m_fMaxAngle);
    pXmlSierialize->xml_serialize("��������","ActDsc","","number",pResults->m_nAct);
}

CSttXmlSerializeBase* stt_xml_serialize( tmt_PowerDirectionTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		stt_xml_serialize_ex(&(pTests->m_oTmtParas),  pXmlParas);	//�ļ��Ķ�д
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize_power_dir(&pTests->m_oTmtResults,  pXmlResults);
	}

	return pXmlParas;
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_PowerDirectionTest_I *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        stt_xml_serialize(&(pTests->m_oTmtParas),  pXmlParas);	//�ļ��Ķ�д
    }

    CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        stt_xml_serialize_pnv_power_dir(&pTests->m_oTmtResults,  pXmlResults);
    }

    return pXmlParas;
}

CSttXmlSerializeBase* stt_xml_serialize( tmt_PnvPowerDirectionTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        stt_xml_serialize(&(pTests->m_oTmtParas),  pXmlParas);	//�ļ��Ķ�д
    }

    CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        stt_xml_serialize_pnv_power_dir(&pTests->m_oTmtResults,  pXmlResults);
    }

    return pXmlParas;
}
