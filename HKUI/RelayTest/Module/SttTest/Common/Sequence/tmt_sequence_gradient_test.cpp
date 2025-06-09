#include "stdafx.h"
#include "tmt_sequence_gradient_test.h"
#include"../../../SttCmd/SttTestCmd.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///
///

#ifndef _STT_NOT_IN_TEST_SERVER_
#include "../SttSystemConfig.h"

void stt_xml_serialize_Sequence(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize,
                                tmt_channel *puiVOL1, tmt_channel *puiVOL2, tmt_channel *puiVOL3,
                                tmt_channel *puiCUR1, tmt_channel *puiCUR2, tmt_channel *puiCUR3)
{
#ifdef NOT_USE_XLANGUAGE
    CString strID, strTypeID[3];
    strTypeID[0] = _T("_Prepare");
    strTypeID[1] = _T("_PreFault");
    strTypeID[2] = _T("_Fault");
    float fFreq = g_theSystemConfig->m_fFNom;
//    pXmlSierialize->xml_serialize("Ƶ��", "Freq", " ", "number", fFreq);
    tmt_channel *pU, *pI;

    for(int nTypeIndex = 0; nTypeIndex < 3; nTypeIndex++)
    {
        switch(nTypeIndex)
        {
            case 0:
                pU = puiVOL1;
                pI = puiCUR1;
                break;

            case 1:
                pU = puiVOL2;
                pI = puiCUR2;
                break;

            case 2:
                pU = puiVOL3;
                pI = puiCUR3;
                break;
        }

        pU[0].Harm[1].fFreq = fFreq;
        strID.Format(_T("U1_1%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pU[0].Harm[1].fAmp);
        strID.Format(_T("U1_1Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pU[0].Harm[1].fAngle);
        pU[1].Harm[1].fFreq = fFreq;
        strID.Format(_T("U1_2%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pU[1].Harm[1].fAmp);
        strID.Format(_T("U1_2Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pU[1].Harm[1].fAngle);
        pU[2].Harm[1].fFreq = fFreq;
        strID.Format(_T("U1_0%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pU[2].Harm[1].fAmp);
        strID.Format(_T("U1_0Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pU[2].Harm[1].fAngle);
        pI[0].Harm[1].fFreq = fFreq;
        strID.Format(_T("I1_1%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pI[0].Harm[1].fAmp);
        strID.Format(_T("I1_1Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pI[0].Harm[1].fAngle);
        pI[1].Harm[1].fFreq = fFreq;
        strID.Format(_T("I1_2%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pI[1].Harm[1].fAmp);
        strID.Format(_T("I1_2Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pI[1].Harm[1].fAngle);
        pI[2].Harm[1].fFreq = fFreq;
        strID.Format(_T("I1_0%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pI[2].Harm[1].fAmp);
        strID.Format(_T("I1_0Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pI[2].Harm[1].fAngle);
    }

    pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "", "set", pParas->m_fStop);
    pXmlSierialize->xml_serialize("���Ծ���", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("����ʱ��(��)", "StepTime", "s", "set", pParas->m_fStepTime);
	pXmlSierialize->xml_serialize("����ʱ��ԣ��","MarginTime","s","number",pParas->m_fMarginTime);
    pXmlSierialize->xml_serialize("�ݱ����", "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
    pXmlSierialize->xml_serialize("�ݱ�����", "VarType", "", "UIRampType", pParas->m_nType);
    pXmlSierialize->xml_serialize("����ǰʱ��(��)", "_PrepareTime", "s", "number", pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize("����ǰʱ��(��)", "_PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0], pXmlSierialize, FALSE);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1], pXmlSierialize, TRUE);
    pXmlSierialize->xml_serialize("�����߼�", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
    }
#else
 	CString strID, strTypeID[3];
    strTypeID[0] = _T("_Prepare");
    strTypeID[1] = _T("_PreFault");
    strTypeID[2] = _T("_Fault");
    float fFreq = 50.0;
    pXmlSierialize->xml_serialize(/* "Ƶ��" */g_sLangTxt_Native_Freq.GetString(), "Freq", " ", "number", fFreq);
    tmt_channel *pU, *pI;

    for(int nTypeIndex = 0; nTypeIndex < 3; nTypeIndex++)
    {
        switch(nTypeIndex)
        {
            case 0:
                pU = puiVOL1;
                pI = puiCUR1;
                break;

            case 1:
                pU = puiVOL2;
                pI = puiCUR2;
                break;

            case 2:
                pU = puiVOL3;
                pI = puiCUR3;
                break;
        }

        pU[0].Harm[1].fFreq = fFreq;
        strID.Format(_T("U1_1%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pU[0].Harm[1].fAmp);
        strID.Format(_T("U1_1Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pU[0].Harm[1].fAngle);
        pU[1].Harm[1].fFreq = fFreq;
        strID.Format(_T("U1_2%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pU[1].Harm[1].fAmp);
        strID.Format(_T("U1_2Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pU[1].Harm[1].fAngle);
        pU[2].Harm[1].fFreq = fFreq;
        strID.Format(_T("U1_0%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pU[2].Harm[1].fAmp);
        strID.Format(_T("U1_0Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pU[2].Harm[1].fAngle);
        pI[0].Harm[1].fFreq = fFreq;
        strID.Format(_T("I1_1%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pI[0].Harm[1].fAmp);
        strID.Format(_T("I1_1Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pI[0].Harm[1].fAngle);
        pI[1].Harm[1].fFreq = fFreq;
        strID.Format(_T("I1_2%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pI[1].Harm[1].fAmp);
        strID.Format(_T("I1_2Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pI[1].Harm[1].fAngle);
        pI[2].Harm[1].fFreq = fFreq;
        strID.Format(_T("I1_0%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pI[2].Harm[1].fAmp);
        strID.Format(_T("I1_0Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pI[2].Harm[1].fAngle);
    }

    pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize(/* "�仯��ֵ" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "", "set", pParas->m_fStop);
    pXmlSierialize->xml_serialize(/* "���Ծ���" */g_sLangTxt_Native_TestPrecision.GetString(), "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize(/* "����ʱ��(��)" */g_sLangTxt_State_StepTime.GetString(), "StepTime", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize(/* "�ݱ����" */g_sLangTxt_Native_VariablePhaseChange.GetString(), "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
    pXmlSierialize->xml_serialize(/* "����ǰʱ��(��)" */g_sLangTxt_Native_PreTestTimeS.GetString(), "_PrepareTime", "s", "number", pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize(/* "����ǰʱ��(��)" */g_sLangTxt_Native_FaultPreTimeS.GetString(), "_PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize(/* "����ǰ��ѹ�������(U-I)" */g_sLangTxt_Native_FaultPreUIPhaseAngle.GetString(), "PreAngle", "��", "number",  pParas->m_fDiffIAngle);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0], pXmlSierialize, FALSE);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1], pXmlSierialize, TRUE);
    pXmlSierialize->xml_serialize(/* "�����߼�" */g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);

    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
    }
#endif
   
}
#endif

void stt_xml_serializeSequenceGradientSetting(tmt_GradientParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹ��������ֵ","USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize("������������ֵ","ISet","A","float",pParas->m_fISet);
	pXmlSierialize->xml_serialize("����ϵ������ֵ","RetCoefSet","","float",pParas->m_fRetCoefSet);
#else
	pXmlSierialize->xml_serialize(/* "��ѹ��������ֵ" */g_sLangTxt_Native_VolSetActValue.GetString(),"USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize(/* "������������ֵ" */g_sLangTxt_Native_CurSetActValue.GetString(),"ISet","A","float",pParas->m_fISet);
	pXmlSierialize->xml_serialize(/* "����ϵ������ֵ" */g_sLangTxt_Native_PhSetActValue.GetString(),"RetCoefSet","","float",pParas->m_fRetCoefSet);
#endif

}

void stt_xml_serialize_sequence_base(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("�ݱ�ģʽ(0-����ģʽ1-��ѹ�ݱ� 2-�����ݱ� 3-��������ģʽ)", "SttTestMode", "", "number", pParas->m_nSttTestMode);

    pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "", "set", pParas->m_fStop );
    pXmlSierialize->xml_serialize("���Ծ���", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("����ʱ��(��)", "StepTime", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("���Է���ϵ��", "VaryMode", "", "number", pParas->m_nTestMode);
    pXmlSierialize->xml_serialize("����ͨ������", "VarIndexType", "", "number", pParas->m_nVarIndexType);
    pXmlSierialize->xml_serialize("�ݱ����", "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
    pXmlSierialize->xml_serialize("�ݱ�����", "VarType", "", "UIRampType", pParas->m_nType);
    pXmlSierialize->xml_serialize("��λ�ݱ䷽��(0:��ʱ�� 1:˳ʱ��)", "PhaseGradDir", "", "number", pParas->m_nPhaseGradDir);
	pXmlSierialize->xml_serialize("����ǰʱ��(��)","_PrepareTime","s","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("����ǰʱ��(��)","_PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("�仯ǰ������ֵ","_IPre","A","number",pParas->m_fEDI);
    pXmlSierialize->xml_serialize("����ǰ��ѹ�������(U-I)", "PreAngle", "��", "number",  pParas->m_fEDUaIaAngle);
	pXmlSierialize->xml_serialize("�仯ǰ������ֵ","_IPre","A","number",pParas->m_fEDI);
    pXmlSierialize->xml_serialize("����ǰ��ѹ�������(U-I)", "PreAngle", "��", "number",  pParas->m_fEDUaIaAngle);
    //���ݱ仯ǰ������ʼ������ǰ����
    if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pParas->m_fG1Current=pParas->m_fEDI;
		pParas->m_fG2Current=pParas->m_fEDI;
	}

	pXmlSierialize->xml_serialize("����̬��1��ѹ��ֵ","_UFaultG1","V","number",pParas->m_fG1Volt);
	pXmlSierialize->xml_serialize("����̬��1������ֵ","_IFaultG1","A","number",pParas->m_fG1Current);
	pXmlSierialize->xml_serialize("����̬��������ǲ�","_DiffIAngle","��","number",pParas->m_fDiffIAngle);
	pXmlSierialize->xml_serialize("����̬Ƶ��","_FreqFault","Hz","number",pParas->m_fHz);
	pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);

	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0],pXmlSierialize,FALSE);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1],pXmlSierialize,TRUE);

	stt_xml_serializeSequenceGradientSetting(pParas,pXmlSierialize);

	pXmlSierialize->xml_serialize("��ѹ����ֵ�������","UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize("��ѹ����ֵ������","UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize("��ѹ����ֵ����ж��߼�","UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("��������ֵ�������","IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize("��������ֵ������","IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize("��������ֵ����ж��߼�","IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("����ϵ���������","RetCoef_AbsErr","","float",pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize("����ϵ��������","RetCoef_RelErr","","float",pParas->m_fRetCoef_RelErr);	
	pXmlSierialize->xml_serialize("����ϵ������ж��߼�","RetCoef_ErrorLogic","","number",pParas->m_nRetCoef_ErrorLogic);
#else
	pXmlSierialize->xml_serialize(/* "�ݱ�ģʽ(0-����ģʽ1-��ѹ�ݱ� 2-�����ݱ� 3-��������ģʽ)" */g_sLangTxt_Native_VariableMode0123.GetString(), "SttTestMode", "", "number", pParas->m_nSttTestMode);

	pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize(/* "�仯��ֵ" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize(/* "���Ծ���" */g_sLangTxt_Native_TestPrecision.GetString(), "Step", "", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize(/* "����ʱ��(��)" */g_sLangTxt_State_StepTime.GetString(), "StepTime", "s", "set", pParas->m_fStepTime);
	pXmlSierialize->xml_serialize(/* "���Է���ϵ��" */g_sLangTxt_Native_TestReturnCoefficient.GetString(), "VaryMode", "", "number", pParas->m_nTestMode);
	pXmlSierialize->xml_serialize(/* "����ͨ������" */g_sLangTxt_Native_TestChannelType.GetString(), "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize(/* "�ݱ����" */g_sLangTxt_Native_VariablePhaseChange.GetString(), "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
	pXmlSierialize->xml_serialize(/* "�ݱ�����" */g_sLangTxt_Native_VariableType.GetString(), "VarType", "", "UIRampType", pParas->m_nType);
	pXmlSierialize->xml_serialize(/* "��λ�ݱ䷽��(0:��ʱ�� 1:˳ʱ��)" */g_sLangTxt_Native_PhaseShiftDir01.GetString(), "PhaseGradDir", "", "number", pParas->m_nPhaseGradDir);
	pXmlSierialize->xml_serialize(/* "����ǰʱ��(��)" */g_sLangTxt_Native_PreTestTimeS.GetString(),"_PrepareTime","s","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize(/* "����ǰʱ��(��)" */g_sLangTxt_Native_FaultPreTimeS.GetString(),"_PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize(/* "�仯ǰ������ֵ" */g_sLangTxt_Native_IBeforeChange.GetString(),"_IPre","A","number",pParas->m_fEDI);
	pXmlSierialize->xml_serialize(/* "����ǰ��ѹ�������(U-I)" */g_sLangTxt_Native_FaultPreUIPhaseAngle.GetString(), "PreAngle", "��", "number",  pParas->m_fEDUaIaAngle);
	pXmlSierialize->xml_serialize(/* "�仯ǰ������ֵ" */g_sLangTxt_Native_IBeforeChange.GetString(),"_IPre","A","number",pParas->m_fEDI);
	pXmlSierialize->xml_serialize(/* "����ǰ��ѹ�������(U-I)" */g_sLangTxt_Native_FaultPreUIPhaseAngle.GetString(), "PreAngle", "��", "number",  pParas->m_fEDUaIaAngle);
	//���ݱ仯ǰ������ʼ������ǰ����
	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pParas->m_fG1Current=pParas->m_fEDI;
		pParas->m_fG2Current=pParas->m_fEDI;
	}

	pXmlSierialize->xml_serialize(/* "����̬��1��ѹ��ֵ" */g_sLangTxt_Native_FaultGroup1VAmp.GetString(),"_UFaultG1","V","number",pParas->m_fG1Volt);
	pXmlSierialize->xml_serialize(/* "����̬��1������ֵ" */g_sLangTxt_Native_FaultGroup1IAmp.GetString(),"_IFaultG1","A","number",pParas->m_fG1Current);
	pXmlSierialize->xml_serialize(/* "����̬��������ǲ�" */g_sLangTxt_Native_FaultGroupIPhaseDiff.GetString(),"_DiffIAngle","��","number",pParas->m_fDiffIAngle);
	pXmlSierialize->xml_serialize(/* "����̬Ƶ��" */g_sLangTxt_Native_FaultGroupFreq.GetString(),"_FreqFault","Hz","number",pParas->m_fHz);
	pXmlSierialize->xml_serialize(/* "�����߼�" */g_sLangTxt_Native_InLogic.GetString(),"_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0],pXmlSierialize,FALSE);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1],pXmlSierialize,TRUE);

	stt_xml_serializeSequenceGradientSetting(pParas,pXmlSierialize);

	pXmlSierialize->xml_serialize(/* "��ѹ����ֵ�������" */g_sLangTxt_Native_VActionValueAbsErr.GetString(),"UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize(/* "��ѹ����ֵ������" */g_sLangTxt_Native_VActionValueRelErr.GetString(),"UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize(/* "��ѹ����ֵ����ж��߼�" */g_sLangTxt_Native_VActionValueErrLogic.GetString(),"UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/* "��������ֵ�������" */g_sLangTxt_Native_IActionValueAbsErr.GetString(),"IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize(/* "��������ֵ������" */g_sLangTxt_Native_IActionValueRelErr.GetString(),"IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize(/* "��������ֵ����ж��߼�" */g_sLangTxt_Native_IActionValueErrLogic.GetString(),"IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/* "����ϵ���������" */g_sLangTxt_Native_CoefficientAbsErr.GetString(),"RetCoef_AbsErr","","float",pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize(/* "����ϵ��������" */g_sLangTxt_Native_CoefficientRelErr.GetString(),"RetCoef_RelErr","","float",pParas->m_fRetCoef_RelErr);	
	pXmlSierialize->xml_serialize(/* "����ϵ������ж��߼�" */g_sLangTxt_Native_CoefficientErrLogic.GetString(),"RetCoef_ErrorLogic","","number",pParas->m_nRetCoef_ErrorLogic);
#endif
	
}

void stt_xml_serialize_sequence_Chs(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	CString strID,strTypeID[3];
    strTypeID[0] = _T("_Prepare");
    strTypeID[1] = _T("_PreFault");
    strTypeID[2] = _T("_Fault");

	for (int nTypeIndex = 0; nTypeIndex < 3; nTypeIndex++)
    {
        for(int nIndex = 0; nIndex < 3; nIndex++)
        {
			if (nIndex == 2)
            {
				strID.Format(_T("U1_0%s"),strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"V","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fAmp);
				strID.Format(_T("U1_0Ph%s"),strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"��","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fAngle);
				strID.Format(_T("U1_0Fre%s"),strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fFreq);
            }
            else
            {
				strID.Format(_T("U1_%d%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"V","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fAmp);
				strID.Format(_T("U1_%dPh%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"��","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fAngle);
				strID.Format(_T("U1_%dFre%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fFreq);
            }

        }

        for(int nIndex = 0; nIndex < 3; nIndex++)
        {
			if (nIndex == 2)
            {
				strID.Format(_T("I1_0%s"),strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"A","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fAmp);
				strID.Format(_T("I1_0Ph%s"),strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"��","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fAngle);
				strID.Format(_T("I1_0Fre%s"),strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fFreq);
            }
            else
            {
				strID.Format(_T("I1_%d%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"A","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fAmp);
				strID.Format(_T("I1_%dPh%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"��","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fAngle);
				strID.Format(_T("I1_%dFre%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fFreq);
            }
        }
    }
}

void stt_xml_serialize_sequence_ex(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    stt_xml_serialize_sequence_base(pParas, pXmlSierialize);
    stt_xml_serialize_sequence_Chs(pParas, pXmlSierialize);

	tmt_GradientParasEx* pParasEx = (tmt_GradientParasEx*)pParas;

    //�о�����
    int bVal = 0;
	if (stt_xml_serialize_is_read(pXmlSierialize))
    {
		pXmlSierialize->xml_serialize("��������Ч","_XD","","number",bVal);
        pParasEx->sCondition.bXD = bVal;
		pXmlSierialize->xml_serialize("������","_XDVal","","number",pParasEx->sCondition.fXD);
    }
	else if (stt_xml_serialize_is_register(pXmlSierialize))
    {
		if(pParasEx->sCondition.bXD){	bVal = 1;	}
		pXmlSierialize->xml_serialize("��������Ч","_XD","","number",bVal);
		pXmlSierialize->xml_serialize("������","_XDVal","","number",pParasEx->sCondition.fXD);
    }

	if (stt_xml_serialize_is_read(pXmlSierialize))
    {
		pXmlSierialize->xml_serialize("���������Ч","_JD","","number",bVal);
        pParasEx->sCondition.bJD = bVal;
		pXmlSierialize->xml_serialize("�������","_JDVal","","number",pParasEx->sCondition.fJD);
    }
	else if (stt_xml_serialize_is_register(pXmlSierialize))
	{
		bVal = 0;
		if(pParasEx->sCondition.bJD){	bVal = 1;	}
		pXmlSierialize->xml_serialize("���������Ч","_JD","","number",bVal);
		pXmlSierialize->xml_serialize("�������","_JDVal","","number",pParasEx->sCondition.fJD);
	}

	// 	if (stt_xml_serialize_is_read(pXmlSierialize))
	// 	{
	// 		pXmlSierialize->xml_serialize("����ϵ����Ч","_Coeff","","number",bVal);
	// 		pParasEx->sCondition.bCoeff = bVal;
	// 		pXmlSierialize->xml_serialize("����ϵ��","_CoeffVal","","number",pParasEx->sCondition.fCoeff);
	// 	}
	// 	else if (stt_xml_serialize_is_register(pXmlSierialize))
	// 	{
	// 		bVal = 0;
	// 		if(pParasEx->sCondition.bCoeff){	bVal = 1;	}
	// 		pXmlSierialize->xml_serialize("����ϵ����Ч","_Coeff","","number",bVal);
	// 		pXmlSierialize->xml_serialize("����ϵ��","_CoeffVal","","number",pParasEx->sCondition.fCoeff);
	// 	}

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pXmlSierialize->xml_serialize("�о��߼�","_LogicOrAnd","��","number",bVal);
		pParasEx->sCondition.bLogicOr = bVal;
	}
	else if (stt_xml_serialize_is_register(pXmlSierialize))
    {
        bVal = 0;
		if(pParasEx->sCondition.bLogicOr){		bVal = 1;	}
		pXmlSierialize->xml_serialize("�о��߼�","_LogicOrAnd","��","number",bVal);
	}
#else
	stt_xml_serialize_sequence_base(pParas, pXmlSierialize);
	stt_xml_serialize_sequence_Chs(pParas, pXmlSierialize);

	tmt_GradientParasEx* pParasEx = (tmt_GradientParasEx*)pParas;

	//�о�����
	int bVal = 0;
	if (stt_xml_serialize_is_read(pXmlSierialize))
        {
		pXmlSierialize->xml_serialize(/* "��������Ч" */g_sLangTxt_Native_relativeErr.GetString(),"_XD","","number",bVal);
		pParasEx->sCondition.bXD = bVal;
		pXmlSierialize->xml_serialize(/* "������" */g_sLangTxt_StateEstimate_RelError.GetString(),"_XDVal","","number",pParasEx->sCondition.fXD);
	}
	else if (stt_xml_serialize_is_register(pXmlSierialize))
	{
		if(pParasEx->sCondition.bXD){	bVal = 1;	}
		pXmlSierialize->xml_serialize(/* "��������Ч" */g_sLangTxt_Native_relativeErr.GetString(),"_XD","","number",bVal);
		pXmlSierialize->xml_serialize(/* "������" */g_sLangTxt_StateEstimate_RelError.GetString(),"_XDVal","","number",pParasEx->sCondition.fXD);//g_sLangTxt_StateEstimate_RelError
        }

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pXmlSierialize->xml_serialize(/* "���������Ч" */g_sLangTxt_Native_relativeErr.GetString(),"_JD","","number",bVal);
		pParasEx->sCondition.bJD = bVal;
		pXmlSierialize->xml_serialize(/* "�������" */g_sLangTxt_StateEstimate_RelError.GetString(),"_JDVal","","number",pParasEx->sCondition.fJD);//g_sLangTxt_StateEstimate_AbsError
	}
	else if (stt_xml_serialize_is_register(pXmlSierialize))
	{
		bVal = 0;
		if(pParasEx->sCondition.bJD){	bVal = 1;	}
		pXmlSierialize->xml_serialize(/* "���������Ч" */g_sLangTxt_Native_relativeErr.GetString(),"_JD","","number",bVal);
		pXmlSierialize->xml_serialize(/* "�������" */g_sLangTxt_StateEstimate_RelError.GetString(),"_JDVal","","number",pParasEx->sCondition.fJD);
    }

// 	if (stt_xml_serialize_is_read(pXmlSierialize))
// 	{
// 		pXmlSierialize->xml_serialize("����ϵ����Ч","_Coeff","","number",bVal);
// 		pParasEx->sCondition.bCoeff = bVal;
// 		pXmlSierialize->xml_serialize("����ϵ��","_CoeffVal","","number",pParasEx->sCondition.fCoeff);
// 	}
// 	else if (stt_xml_serialize_is_register(pXmlSierialize))
// 	{
// 		bVal = 0;
// 		if(pParasEx->sCondition.bCoeff){	bVal = 1;	}
// 		pXmlSierialize->xml_serialize("����ϵ����Ч","_Coeff","","number",bVal);
// 		pXmlSierialize->xml_serialize("����ϵ��","_CoeffVal","","number",pParasEx->sCondition.fCoeff);
// 	}

	if (stt_xml_serialize_is_read(pXmlSierialize))
    {
		pXmlSierialize->xml_serialize(/* "�о��߼�" */g_sLangTxt_Native_criteria_logic.GetString(),"_LogicOrAnd","��","number",bVal);
        pParasEx->sCondition.bLogicOr = bVal;
    }
	else if (stt_xml_serialize_is_register(pXmlSierialize))
    {
        bVal = 0;
		if(pParasEx->sCondition.bLogicOr){		bVal = 1;	}
		pXmlSierialize->xml_serialize(/* "�о��߼�" */g_sLangTxt_Native_criteria_logic.GetString(),"_LogicOrAnd","��","number",bVal);
	}
#endif
	
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_sequence_gradient_test_ex *pParas, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize_sequence_ex(&pParas->m_oSequenceGradientParasEx, pXmlParas);	//�ļ��Ķ�д
		}
		else if (pParas->m_nSelected)//�������Ƿ�ѡ��
		{
			stt_xml_serialize_sequence_ex(&pParas->m_oSequenceGradientParasEx, pXmlParas);	//���Բ����·�
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_sequence_serialize(&pParas->m_oSequenceResultParas, pXmlResults);
		}
		else if (pParas->m_nSelected)
        {
			stt_xml_sequence_serialize(&pParas->m_oSequenceResultParas, pXmlResults);
		}
	}

	return pXmlParas;
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_SequenceGradientPnvTest *pParas, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_sequence_pnv_serialize(&pParas->m_oSequenceGradientParas, pXmlParas);	//�ļ��Ķ�д
        }
        else if (pParas->m_nSelected)//�������Ƿ�ѡ��
        {
            stt_xml_sequence_pnv_serialize(&pParas->m_oSequenceGradientParas, pXmlParas);	//���Բ����·�
        }
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_sequence_pnv_serialize(&pParas->m_oSequenceResultParas, pXmlResults);
        }
        else if (pParas->m_nSelected)
        {
            stt_xml_sequence_pnv_serialize(&pParas->m_oSequenceResultParas, pXmlResults);
        }
    }

    return pXmlParas;
}

void stt_xml_sequence_serialize(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_sequence_base(pParas, pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		if(pParas->m_nSttTestMode == GradientTest_Base_1)
		{
			stt_xml_serialize_sequence_Chs(pParas, pXmlSierialize);
		}
		else
		{
			CString strID;
			for(int nIndex=0;nIndex<3;nIndex++)
			{
				if (nIndex == 2)
				{
					strID.Format(_T("U1_0"));
					pXmlSierialize->xml_serialize("",strID.GetString(),"V","number",pParas->m_uiVOL[2][nIndex].Harm[1].fAmp);
					strID.Format(_T("U1_0Ph"));
					pXmlSierialize->xml_serialize("",strID.GetString(),"��","number",pParas->m_uiVOL[2][nIndex].Harm[1].fAngle);
					strID.Format(_T("U1_0Fre"));
					pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiVOL[2][nIndex].Harm[1].fFreq);
				}
				else
				{
					strID.Format(_T("U1_%d"),nIndex+1);
					pXmlSierialize->xml_serialize("",strID.GetString(),"V","number",pParas->m_uiVOL[2][nIndex].Harm[1].fAmp);
					strID.Format(_T("U1_%dPh"),nIndex+1);
					pXmlSierialize->xml_serialize("",strID.GetString(),"��","number",pParas->m_uiVOL[2][nIndex].Harm[1].fAngle);
					strID.Format(_T("U1_%dFre"),nIndex+1);
					pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiVOL[2][nIndex].Harm[1].fFreq);
				}
        }

			for(int nIndex=0;nIndex<3;nIndex++)
			{
				if (nIndex == 2)
				{
					strID.Format(_T("I1_0"));
					pXmlSierialize->xml_serialize("",strID.GetString(),"A","number",pParas->m_uiCUR[2][nIndex].Harm[1].fAmp);
					strID.Format(_T("I1_0Ph"));
					pXmlSierialize->xml_serialize("",strID.GetString(),"��","number",pParas->m_uiCUR[2][nIndex].Harm[1].fAngle);
					strID.Format(_T("I1_0Fre"));
					pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiCUR[2][nIndex].Harm[1].fFreq);
				}
				else
				{
					strID.Format(_T("I1_%d"),nIndex+1);
					pXmlSierialize->xml_serialize("",strID.GetString(),"A","number",pParas->m_uiCUR[2][nIndex].Harm[1].fAmp);
					strID.Format(_T("I1_%dPh"),nIndex+1);
					pXmlSierialize->xml_serialize("",strID.GetString(),"��","number",pParas->m_uiCUR[2][nIndex].Harm[1].fAngle);
					strID.Format(_T("I1_%dFre"),nIndex+1);
					pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiCUR[2][nIndex].Harm[1].fFreq);
				}
			}
		}
	}
	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		stt_xml_serialize(&pParas->m_oGoosePub[0],pXmlSierialize);
    }
}

void stt_xml_sequence_serialize(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("����ֵ", "TripValue", "A/V", "number", pResults->m_fTripValue);
    pXmlSierialize->xml_serialize("����ʱ��", "TripTime", "s", "number", pResults->m_fTripTime);
    pXmlSierialize->xml_serialize("��ѹ����ֵ���", "TripUErrVal", "", "number", pResults->m_fTripUErrVal);
    pXmlSierialize->xml_serialize("��������ֵ���", "TripIErrVal", "", "number", pResults->m_fTripIErrVal);
    pXmlSierialize->xml_serialize("��������", "ActDsec", "", "number", pResults->m_nAct);
    pXmlSierialize->xml_serialize("����1����ֵ", "TripValueA", "A/V", "number", pResults->m_fTripValueChl[0]);
    pXmlSierialize->xml_serialize("����2����ֵ", "TripValueB", "A/V", "number", pResults->m_fTripValueChl[1]);
    pXmlSierialize->xml_serialize("����3����ֵ", "TripValueC", "A/V", "number", pResults->m_fTripValueChl[2]);
    pXmlSierialize->xml_serialize("����4����ֵ", "TripValueD", "A/V", "number", pResults->m_fTripValueChl[3]);
    pXmlSierialize->xml_serialize("����5����ֵ", "TripValueE", "A/V", "number", pResults->m_fTripValueChl[4]);
    pXmlSierialize->xml_serialize("����6����ֵ", "TripValueF", "A/V", "number", pResults->m_fTripValueChl[5]);
    pXmlSierialize->xml_serialize("����7����ֵ", "TripValueG", "A/V", "number", pResults->m_fTripValueChl[6]);
    pXmlSierialize->xml_serialize("����8����ֵ", "TripValueH", "A/V", "number", pResults->m_fTripValueChl[7]);

    if(g_nBinExCount > 0)
    {
        CSttXmlSerializeBase *pXmlTripValueEx = pXmlSierialize->xml_serialize("TripValueEx", "TripValueEx", "TripValueEx", stt_ParaGroupKey());

        if(pXmlTripValueEx != NULL)
        {
            CString strName, strID, strTemp;
            CString str1 = _T("����");
            CString str1Ex = _T("������չ");
            CString str2 = _T("����ֵ");

            for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
            {
                strTemp.Format(_T("%d"), nIndex + 1);
                strName = str1Ex + strTemp + str2;

                strID.Format("TripValueEx%d", (nIndex + 1));
                pXmlTripValueEx->xml_serialize(strName.GetString(), strID.GetString(), "", "A/V", pResults->m_fTripValueExChl[nIndex]);
            }
        }
    }
#else
	pXmlSierialize->xml_serialize(/* "����ֵ" */g_sLangTxt_State_ActionValue.GetString(), "TripValue", "A/V", "number", pResults->m_fTripValue);//g_sLangTxt_State_ActionValue
    pXmlSierialize->xml_serialize(/* "����ʱ��" */g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "s", "number", pResults->m_fTripTime);//g_sLangTxt_Gradient_ActionTime
    pXmlSierialize->xml_serialize(/* "��ѹ����ֵ���" */g_sLangTxt_Native_VActionValueErr.GetString(), "TripUErrVal", "", "number", pResults->m_fTripUErrVal);
    pXmlSierialize->xml_serialize(/* "��������ֵ���" */g_sLangTxt_Native_IActionValueErr.GetString(), "TripIErrVal", "", "number", pResults->m_fTripIErrVal);
    pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActDsec", "", "number", pResults->m_nAct);//g_sLangTxt_Native_ActionDesc
    pXmlSierialize->xml_serialize(/* "����1����ֵ" */g_sLangTxt_Native_input1_ActionVal.GetString(), "TripValueA", "A/V", "number", pResults->m_fTripValueChl[0]);
    pXmlSierialize->xml_serialize(/* "����2����ֵ" */g_sLangTxt_Native_input2_ActionVal.GetString(), "TripValueB", "A/V", "number", pResults->m_fTripValueChl[1]);
    pXmlSierialize->xml_serialize(/* "����3����ֵ" */g_sLangTxt_Native_input3_ActionVal.GetString(), "TripValueC", "A/V", "number", pResults->m_fTripValueChl[2]);
    pXmlSierialize->xml_serialize(/* "����4����ֵ" */g_sLangTxt_Native_input4_ActionVal.GetString(), "TripValueD", "A/V", "number", pResults->m_fTripValueChl[3]);
    pXmlSierialize->xml_serialize(/* "����5����ֵ" */g_sLangTxt_Native_input5_ActionVal.GetString(), "TripValueE", "A/V", "number", pResults->m_fTripValueChl[4]);
    pXmlSierialize->xml_serialize(/* "����6����ֵ" */g_sLangTxt_Native_input6_ActionVal.GetString(), "TripValueF", "A/V", "number", pResults->m_fTripValueChl[5]);
    pXmlSierialize->xml_serialize(/* "����7����ֵ" */g_sLangTxt_Native_input7_ActionVal.GetString(), "TripValueG", "A/V", "number", pResults->m_fTripValueChl[6]);
    pXmlSierialize->xml_serialize(/* "����8����ֵ" */g_sLangTxt_Native_input8_ActionVal.GetString(), "TripValueH", "A/V", "number", pResults->m_fTripValueChl[7]);

    if(g_nBinExCount > 0)
    {
        CSttXmlSerializeBase *pXmlTripValueEx = pXmlSierialize->xml_serialize("TripValueEx", "TripValueEx", "TripValueEx", stt_ParaGroupKey());

        if(pXmlTripValueEx != NULL)
        {
            CString strName, strID, strTemp;
            CString str1 = /* _T("����") */g_sLangTxt_Native_BinX;
            CString str1Ex = /* _T("������չ") */g_sLangTxt_Native_InputExpand;
            CString str2 = /* _T("����ֵ") */g_sLangTxt_State_ActionValue;

            for(int nIndex = 0; nIndex < g_nBinExCount; nIndex++)
            {
                strTemp.Format(_T("%d"), nIndex + 1);
                strName = str1Ex + strTemp + str2;

                strID.Format("TripValueEx%d", (nIndex + 1));
                pXmlTripValueEx->xml_serialize(strName.GetString(), strID.GetString(), "", "A/V", pResults->m_fTripValueExChl[nIndex]);
            }
        }
    }
#endif
}

void stt_xml_sequence_pnv_serialize(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "", "set", pParas->m_fStop );
    pXmlSierialize->xml_serialize("���Ծ���", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("��������ʱ��", "TSetting", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("���Է���ϵ��", "VaryMode", "", "number", pParas->m_nTestMode);
    pXmlSierialize->xml_serialize("����ͨ������", "VarIndexType", "", "number", pParas->m_nVarIndexType);
    pXmlSierialize->xml_serialize("�ݱ����", "VarPhase", "", "UIRampChannel", pParas->m_nChannel);
    pXmlSierialize->xml_serialize("�ݱ�����", "VarType", "", "UIRampType", pParas->m_nType);
    pXmlSierialize->xml_serialize("����ǰ����ʱ��(��)","RampResetTime","s","number",pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize("����ǰ����ʱ��(��)","FaultResetTime","s","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("ÿ��ʱ��ԣ��","StepTimeAdded","s","number",pParas->m_fMarginTime);

    pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
    pXmlSierialize->xml_serialize("����Aѡ��", "_BinSelectA", "", "BOOL", pParas->m_binIn[0].nSelect);
    pXmlSierialize->xml_serialize("����Bѡ��", "_BinSelectB", "", "BOOL", pParas->m_binIn[1].nSelect);
    pXmlSierialize->xml_serialize("����Cѡ��", "_BinSelectC", "", "BOOL", pParas->m_binIn[2].nSelect);
    pXmlSierialize->xml_serialize("����Rѡ��", "_BinSelectR", "", "BOOL", pParas->m_binIn[3].nSelect);
    pXmlSierialize->xml_serialize("����aѡ��", "_BinSelecta", "", "BOOL", pParas->m_binIn[4].nSelect);
    pXmlSierialize->xml_serialize("����bѡ��", "_BinSelectb", "", "BOOL", pParas->m_binIn[5].nSelect);
    pXmlSierialize->xml_serialize("����cѡ��", "_BinSelectc", "", "BOOL", pParas->m_binIn[6].nSelect);
    pXmlSierialize->xml_serialize("����rѡ��", "_BinSelectr", "", "BOOL", pParas->m_binIn[7].nSelect);

    pXmlSierialize->xml_serialize("����1","_Bout1","","DOutputState",pParas->m_binOut[0][0].nState);
    pXmlSierialize->xml_serialize("����2","_Bout2","","DOutputState",pParas->m_binOut[0][1].nState);
    pXmlSierialize->xml_serialize("����3","_Bout3","","DOutputState",pParas->m_binOut[0][2].nState);
    pXmlSierialize->xml_serialize("����4","_Bout4","","DOutputState",pParas->m_binOut[0][3].nState);
    pXmlSierialize->xml_serialize("����1����״̬","_BoutF1","","DOutputState",pParas->m_binOut[1][0].nState);
    pXmlSierialize->xml_serialize("����2����״̬","_BoutF2","","DOutputState",pParas->m_binOut[1][1].nState);
    pXmlSierialize->xml_serialize("����3����״̬","_BoutF3","","DOutputState",pParas->m_binOut[1][2].nState);
    pXmlSierialize->xml_serialize("����4����״̬","_BoutF4","","DOutputState",pParas->m_binOut[1][3].nState);
    pXmlSierialize->xml_serialize("��������ʱ��","_BoutHoldTime","","number",pParas->m_binOut[1][0].fHoldTime);

    pXmlSierialize->xml_serialize("V1��ʼ��ֵ","V10_Amp","V","number",pParas->m_uiVOL[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("V1��ʼ��λ","V10_Ph","��","number",pParas->m_uiVOL[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("V2��ʼ��ֵ","V20_Amp","V","number",pParas->m_uiVOL[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("V2��ʼ��λ","V20_Ph","��","number",pParas->m_uiVOL[0][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("V0��ʼ��ֵ","V00_Amp","V","number",pParas->m_uiVOL[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("V0��ʼ��λ","V00_Ph","��","number",pParas->m_uiVOL[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("I1��ʼ��ֵ","I10_Amp","A","number",pParas->m_uiCUR[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("I1��ʼ��λ","I10_Ph","��","number",pParas->m_uiCUR[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("I2��ʼ��ֵ","I20_Amp","A","number",pParas->m_uiCUR[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("I2��ʼ��λ","I20_Ph","��","number",pParas->m_uiCUR[0][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("I0��ʼ��ֵ","I00_Amp","A","number",pParas->m_uiCUR[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("I0��ʼ��λ","I00_Ph","��","number",pParas->m_uiCUR[0][0].Harm[1].fAngle);
}

void stt_xml_sequence_pnv_serialize(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("����ֵ", "TripValue", "A", "number", pResults->m_fTripValue);
    pXmlSierialize->xml_serialize("����ֵ", "ReturnValue", "V", "number", pResults->m_fReturnValue);
    pXmlSierialize->xml_serialize("����ϵ��", "ReturnCoef", "", "number", pResults->m_fReturnCoef);
    pXmlSierialize->xml_serialize("��������", "ActDsc", "", "number", pResults->m_nAct);
}

#include "../../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_SequenceGradientTest()
{
	tmt_SequenceGradientTest oSequenceGradientTest;
	oSequenceGradientTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeRegister(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_sequence_serialize(&oSequenceGradientTest.m_oSequenceGradientParas, pMacroParas);

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("SequenceGradientTestDemo.xml");
	//  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
