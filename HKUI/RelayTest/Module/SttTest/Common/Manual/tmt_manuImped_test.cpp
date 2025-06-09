#include "stdafx.h"
#include "./tmt_manuImped_test.h"
#include "../tmt_system_config.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              
#endif

void stt_init_paras(tmt_ManualImpedParas *pParas)
{
    memset(&pParas, 0, sizeof(tmt_ManualImpedParas));
    pParas->init();
}

void stt_init_results(tmt_ManualImpedResult *pResults)
{
    memset(&pResults, 0, sizeof(tmt_ManualImpedResult));
    pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_Manu_Imped(tmt_ManualImpedParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("�迹����","CalcuMode","","UIZCalMode",pParas->m_nCalMode);
	pXmlSierialize->xml_serialize("��·����","ISet1","A","number",pParas->m_fSCCurrent);
	pXmlSierialize->xml_serialize("��·��ѹ","VSet1","V","float",pParas->m_fSCVoltage);
	pXmlSierialize->xml_serialize("��ϵ����ϵ��ģʽ","OffsetsMode","","number",pParas->m_nOffsetsMode);
	pXmlSierialize->xml_serialize("��ֵKr","ComputateA","","float",pParas->m_fAmplitudeOrKr);
	pXmlSierialize->xml_serialize("��λKx","ComputateB","","float",pParas->m_fPhaseOrKx);
	pXmlSierialize->xml_serialize("��������","FaultType","","number",pParas->m_nFaultType);
	pXmlSierialize->xml_serialize("�迹����ѡ��","ImpedChoose","","number",pParas->m_nImped);
	pXmlSierialize->xml_serialize("|Z|��ֵ","ComputateAmpZ","��","float",pParas->m_fZAmp);
	pXmlSierialize->xml_serialize("|Z|�Ƕ�","ComputateAngleZ","��","float",pParas->m_fZAngle);
	pXmlSierialize->xml_serialize("R��ֵ","ComputateAmpRx","��","float",pParas->m_fR);
	pXmlSierialize->xml_serialize("X��ֵ","ComputateAngleX","��","float",pParas->m_fX);
	pXmlSierialize->xml_serialize("Zs��ֵ","ComputateAmpZs","V","float",pParas->m_fSZSAmp);
	pXmlSierialize->xml_serialize("Zs�Ƕ�","ComputateAngleZs","��","float",pParas->m_fSZSAngle);
	pXmlSierialize->xml_serialize("����ѡ��1","FirstMode","","number",pParas->m_nFirstMode);
	pXmlSierialize->xml_serialize("����ѡ��2","SecondMode","","number",pParas->m_nSecondMode);
	pXmlSierialize->xml_serialize("��̬ʱ��","NormalTime","","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("����ǰʱ��","FaultBeTime","","number",pParas->m_fPreFaultTime); 
	pXmlSierialize->xml_serialize("ͻ��������","Mutation","","number",pParas->m_bMutation);
}

void stt_xml_serialize(tmt_ManualImpedParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
#ifdef NOT_USE_XLANGUAGE
        pXmlSierialize->xml_serialize("Ua��ֵ", "Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp);
        pXmlSierialize->xml_serialize("Ua��λ", "UaPh", "��", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
        pXmlSierialize->xml_serialize("UaƵ��", "UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq);
        pXmlSierialize->xml_serialize("Ub��ֵ", "Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp);
        pXmlSierialize->xml_serialize("Ub��λ", "UbPh", "��", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
        pXmlSierialize->xml_serialize("UbƵ��", "UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq);
        pXmlSierialize->xml_serialize("Uc��ֵ", "Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp);
        pXmlSierialize->xml_serialize("Uc��λ", "UcPh", "��", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
        pXmlSierialize->xml_serialize("UcƵ��", "UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq);
        pXmlSierialize->xml_serialize("Uz��ֵ", "Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp);
        pXmlSierialize->xml_serialize("Uz��λ", "UapPh", "��", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
        pXmlSierialize->xml_serialize("UzƵ��", "UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq);
        pXmlSierialize->xml_serialize("Ia��ֵ", "Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp);
        pXmlSierialize->xml_serialize("Ia��λ", "IaPh", "��", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
        pXmlSierialize->xml_serialize("IaƵ��", "IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq);
        pXmlSierialize->xml_serialize("Ib��ֵ", "Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp);
        pXmlSierialize->xml_serialize("Ib��λ", "IbPh", "��", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
        pXmlSierialize->xml_serialize("IbƵ��", "IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq);
        pXmlSierialize->xml_serialize("Ic��ֵ", "Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp);
        pXmlSierialize->xml_serialize("Ic��λ", "IcPh", "��", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
        pXmlSierialize->xml_serialize("IcƵ��", "IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq); 

		pXmlSierialize->xml_serialize("�仯ʼֵ", "Start", "", "number", pParas->m_manuImpedGradient.fStart);
		pXmlSierialize->xml_serialize("�仯��ֵ", "End", "", "number", pParas->m_manuImpedGradient.fEnd);
		pXmlSierialize->xml_serialize("�仯����", "Step", "", "number", pParas->m_manuImpedGradient.fStep);
		pXmlSierialize->xml_serialize("ÿ��ʱ��", "StepTime", "", "number", pParas->m_manuImpedGradient.fStepTime);
		pXmlSierialize->xml_serialize("������ʱ", "TrigDelay", "", "number", pParas->m_manuImpedGradient.fTrigDelay);
		pXmlSierialize->xml_serialize("�����߼�", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
		pXmlSierialize->xml_serialize("�Ƿ�����", "_bLock", "", "number", pParas->m_bLockChanged);
		pXmlSierialize->xml_serialize("�Ƿ���ֹͣ", "bBinStop", "", "BOOL", pParas->m_bBinStop);
		pXmlSierialize->xml_serialize("�Ƿ��Զ��ݱ�", "_bAuto", "", "number", pParas->m_bAuto);

#else
		pXmlSierialize->xml_serialize(/*"Ua��ֵ"*/g_sLangTxt_Native_UaAmplitude.GetString(), "Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp);
		pXmlSierialize->xml_serialize(/*"Ua��λ"*/g_sLangTxt_Native_UaPhase.GetString(), "UaPh", "��", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
		pXmlSierialize->xml_serialize(/*"UaƵ��"*/g_sLangTxt_Native_UaFreq.GetString(), "UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq);
		pXmlSierialize->xml_serialize(/*"Ub��ֵ"*/g_sLangTxt_Native_UbAmplitude.GetString(), "Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp);
		pXmlSierialize->xml_serialize(/*"Ub��λ"*/g_sLangTxt_Native_UbPhase.GetString(), "UbPh", "��", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
		pXmlSierialize->xml_serialize(/*"UbƵ��"*/g_sLangTxt_Native_UbFreq.GetString(), "UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq);
		pXmlSierialize->xml_serialize(/*"Uc��ֵ"*/g_sLangTxt_Native_UcAmplitude.GetString(), "Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp);
		pXmlSierialize->xml_serialize(/*"Uc��λ"*/g_sLangTxt_Native_UcPhase.GetString(), "UcPh", "��", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
		pXmlSierialize->xml_serialize(/*"UcƵ��"*/g_sLangTxt_Native_UcFreq.GetString(), "UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq);
		pXmlSierialize->xml_serialize(/*"Uz��ֵ"*/g_sLangTxt_Native_UapAmp.GetString(), "Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp);
		pXmlSierialize->xml_serialize(/*"Uz��λ"*/g_sLangTxt_Native_UapPhase.GetString(), "UapPh", "��", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
		pXmlSierialize->xml_serialize(/*"UzƵ��"*/g_sLangTxt_Native_UapFreq.GetString(), "UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq);	
		pXmlSierialize->xml_serialize(/*"Ia��ֵ"*/g_sLangTxt_Native_IaAmp.GetString(), "Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp);
		pXmlSierialize->xml_serialize(/*"Ia��λ"*/g_sLangTxt_Native_IaPhase.GetString(), "IaPh", "��", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
		pXmlSierialize->xml_serialize(/*"IaƵ��"*/g_sLangTxt_Native_IaFreq.GetString(), "IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq);
		pXmlSierialize->xml_serialize(/*"Ib��ֵ"*/g_sLangTxt_Native_IbAmp.GetString(), "Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp);
		pXmlSierialize->xml_serialize(/*"Ib��λ"*/g_sLangTxt_Native_IbPhase.GetString(), "IbPh", "��", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
		pXmlSierialize->xml_serialize(/*"IbƵ��"*/g_sLangTxt_Native_IbFreq.GetString(), "IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq);
		pXmlSierialize->xml_serialize(/*"Ic��ֵ"*/g_sLangTxt_Native_IcAmp.GetString(), "Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp);
		pXmlSierialize->xml_serialize(/*"Ic��λ"*/g_sLangTxt_Native_IcPhase.GetString(), "IcPh", "��", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
		pXmlSierialize->xml_serialize(/*"IcƵ��"*/g_sLangTxt_Native_IcFreq.GetString(), "IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq);	

		pXmlSierialize->xml_serialize(/*"�仯ʼֵ"*/g_sLangTxt_Gradient_Init.GetString(), "Start", "", "number", pParas->m_manuImpedGradient.fStart);
		pXmlSierialize->xml_serialize(/*"�仯��ֵ"*/g_sLangTxt_Gradient_Finish.GetString(), "End", "", "number", pParas->m_manuImpedGradient.fEnd);
		pXmlSierialize->xml_serialize(/*"�仯����"*/g_sLangTxt_Gradient_Step.GetString(), "Step", "", "number", pParas->m_manuImpedGradient.fStep);
		pXmlSierialize->xml_serialize(/*"ÿ��ʱ��"*/g_sLangTxt_Native_step_time.GetString(), "StepTime", "", "number", pParas->m_manuImpedGradient.fStepTime);
		pXmlSierialize->xml_serialize(/*"������ʱ"*/g_sLangTxt_Native_trigger_delay.GetString(), "TrigDelay", "", "number", pParas->m_manuImpedGradient.fTrigDelay);
		pXmlSierialize->xml_serialize(/*"�����߼�"*/g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
		pXmlSierialize->xml_serialize(/*"�Ƿ�����"*/g_sLangTxt_Native_YN_locked.GetString(), "_bLock", "", "number", pParas->m_bLockChanged);
		pXmlSierialize->xml_serialize(/*"�Ƿ��Զ��ݱ�"*/g_sLangTxt_Native_YN_autoevo.GetString(), "_bAuto", "", "number", pParas->m_bAuto);
#endif
    }
	stt_xml_serialize_Manu_Imped(pParas,pXmlSierialize);

    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    //Ex
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx, pXmlSierialize);

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
    }

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��������ʱ��", "TSet", "s", "float", pParas->m_fTimeSet);
	pXmlSierialize->xml_serialize("��ѹ��������ֵ", "USet", "V", "float", pParas->m_fUSet);
	pXmlSierialize->xml_serialize("������������ֵ", "ISet", "A", "float", pParas->m_fISet);
	pXmlSierialize->xml_serialize("��λ��������ֵ", "AngleSet", "��", "float", pParas->m_fAngleSet);
	//pXmlSierialize->xml_serialize("Ƶ����������ֵ", "HzSet", "Hz", "float", pParas->m_fHzSet);
	pXmlSierialize->xml_serialize("�迹��������ֵ", "ImpSet", "��", "float", pParas->m_fImpSet);
	pXmlSierialize->xml_serialize("����ϵ������ֵ", "RetCoefSet", "", "float", pParas->m_fRetCoefSet);
	pXmlSierialize->xml_serialize("����ʱ��ֵ�������", "Ttrip_AbsErr", "", "float", pParas->m_fTimeValue_AbsErr);
	pXmlSierialize->xml_serialize("����ʱ��ֵ������", "Ttrip_RelErr", "", "float", pParas->m_fTimeValue_RelErr);
	pXmlSierialize->xml_serialize("����ʱ������ж��߼�", "TimeValue_ErrorLogic", "", "number", pParas->m_nTimeValue_ErrorLogic);
	pXmlSierialize->xml_serialize("��ѹ����ֵ�������", "UActVal_AbsErr", "", "float", pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize("��ѹ����ֵ������", "UActVal_RelErr", "", "float", pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize("��ѹ����ֵ����ж��߼�", "UActVal_ErrorLogic", "", "number", pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("��������ֵ�������", "IActVal_AbsErr", "", "float", pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize("��������ֵ������", "IActVal_RelErr", "", "float", pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize("��������ֵ����ж��߼�", "IActVal_ErrorLogic", "", "number", pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("��λ����ֵ�������", "AngleActVal_AbsErr", "", "float", pParas->m_fAngleActVal_AbsErr);
	pXmlSierialize->xml_serialize("��λ����ֵ������", "AngleActVal_RelErr", "", "float", pParas->m_fAngleActVal_RelErr);
	pXmlSierialize->xml_serialize("��λ����ֵ����ж��߼�", "AngleActVal_ErrorLogic", "", "number", pParas->m_nAngleActVal_ErrorLogic);
	//pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ�������","HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);
	//pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ������","HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);
	//pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ����ж��߼�","HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("�迹����ֵ�������", "ImpActVal_AbsErr", "", "float", pParas->m_fImpValue_AbsErr);
	pXmlSierialize->xml_serialize("�迹����ֵ������", "ImpActVal_RelErr", "", "float", pParas->m_fImpValue_RelErr);
	pXmlSierialize->xml_serialize("�迹����ֵ����ж��߼�", "ImpActVal_ErrorLogic", "", "number", pParas->m_nImpValue_ErrorLogic);
	pXmlSierialize->xml_serialize("����ϵ���������", "RetCoef_AbsErr", "", "float", pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize("����ϵ��������", "RetCoef_RelErr", "", "float", pParas->m_fRetCoef_RelErr);
	pXmlSierialize->xml_serialize("����ϵ������ж��߼�", "RetCoef_ErrorLogic", "", "number", pParas->m_nRetCoef_ErrorLogic);
#else
	pXmlSierialize->xml_serialize(/* "��������ʱ��" */g_sLangTxt_Native_acttuning_time.GetString(), "TSet", "s", "float", pParas->m_fTimeSet);
	pXmlSierialize->xml_serialize(/* "��ѹ��������ֵ" */g_sLangTxt_Native_VolSetActValue.GetString(), "USet", "V", "float", pParas->m_fUSet);
	pXmlSierialize->xml_serialize(/* "������������ֵ" */g_sLangTxt_Native_CurSetActValue.GetString(), "ISet", "A", "float", pParas->m_fISet);
	pXmlSierialize->xml_serialize(/* "��λ��������ֵ" */g_sLangTxt_Native_PhSetActValue.GetString(), "AngleSet", "��", "float", pParas->m_fAngleSet);
	//pXmlSierialize->xml_serialize(/* "Ƶ����������ֵ" */g_sLangTxt_Native_FreqSetActValue.GetString(), "HzSet", "Hz", "float", pParas->m_fHzSet);
	pXmlSierialize->xml_serialize("�迹��������ֵ", "ImpSet", "��", "float", pParas->m_fImpSet);
	pXmlSierialize->xml_serialize(/* "����ϵ������ֵ" */g_sLangTxt_Native_FeedbackCoefSettingVal.GetString(), "RetCoefSet", "", "float", pParas->m_fRetCoefSet);
	pXmlSierialize->xml_serialize(/* "����ʱ��ֵ�������" */g_sLangTxt_Native_ActTimeValueAbsErr.GetString(), "Ttrip_AbsErr", "", "float", pParas->m_fTimeValue_AbsErr);
	pXmlSierialize->xml_serialize(/* "����ʱ��ֵ������" */g_sLangTxt_Native_ActTimeValueRelErr.GetString(), "Ttrip_RelErr", "", "float", pParas->m_fTimeValue_RelErr);
	pXmlSierialize->xml_serialize(/* "����ʱ������ж��߼�" */g_sLangTxt_Native_ActTimeValueErrLogic.GetString(), "TimeValue_ErrorLogic", "", "number", pParas->m_nTimeValue_ErrorLogic);
	pXmlSierialize->xml_serialize(/* "��ѹ����ֵ�������" */g_sLangTxt_Native_VActionValueAbsErr.GetString(), "UActVal_AbsErr", "", "float", pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize(/* "��ѹ����ֵ������" */g_sLangTxt_Native_VActionValueRelErr.GetString(), "UActVal_RelErr", "", "float", pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize(/* "��ѹ����ֵ����ж��߼�" */g_sLangTxt_Native_VActionValueErrLogic.GetString(), "UActVal_ErrorLogic", "", "number", pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/* "��������ֵ�������" */g_sLangTxt_Native_IActionValueAbsErr.GetString(), "IActVal_AbsErr", "", "float", pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize(/* "��������ֵ������" */g_sLangTxt_Native_IActionValueRelErr.GetString(), "IActVal_RelErr", "", "float", pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize(/* "��������ֵ����ж��߼�" */g_sLangTxt_Native_IActionValueErrLogic.GetString(), "IActVal_ErrorLogic", "", "number", pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/* "��λ����ֵ�������" */g_sLangTxt_Native_PhaseActValueAbsErr.GetString(), "AngleActVal_AbsErr", "", "float", pParas->m_fAngleActVal_AbsErr);
	pXmlSierialize->xml_serialize(/* "��λ����ֵ������" */g_sLangTxt_Native_PhaseActValueRelErr.GetString(), "AngleActVal_RelErr", "", "float", pParas->m_fAngleActVal_RelErr);
	pXmlSierialize->xml_serialize(/* "��λ����ֵ����ж��߼�" */g_sLangTxt_Native_PhaseActValueErrLogic.GetString(), "AngleActVal_ErrorLogic", "", "number", pParas->m_nAngleActVal_ErrorLogic);
	//pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ�������","HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);
	//pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ������","HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);
	//pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ����ж��߼�","HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("�迹����ֵ�������", "ImpActVal_AbsErr", "", "float", pParas->m_fImpValue_AbsErr);
	pXmlSierialize->xml_serialize("�迹����ֵ������", "ImpActVal_RelErr", "", "float", pParas->m_fImpValue_RelErr);
	pXmlSierialize->xml_serialize("�迹����ֵ����ж��߼�", "ImpActVal_ErrorLogic", "", "number", pParas->m_nImpValue_ErrorLogic);
	pXmlSierialize->xml_serialize(/* "����ϵ���������" */g_sLangTxt_Native_CoefficientAbsErr.GetString(), "RetCoef_AbsErr", "", "float", pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize(/* "����ϵ��������" */g_sLangTxt_Native_CoefficientRelErr.GetString(), "RetCoef_RelErr", "", "float", pParas->m_fRetCoef_RelErr);
	pXmlSierialize->xml_serialize(/* "����ϵ������ж��߼�" */g_sLangTxt_Native_CoefficientErrLogic.GetString(), "RetCoef_ErrorLogic", "", "number", pParas->m_nRetCoef_ErrorLogic);
#endif
}

void stt_xml_serialize_act_rcd(tmt_ManualImpedResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//������¼,���64��,����ʵ�ʶ������,�����ܵĶ�����Ϣ
{
    CSttXmlSerializeBase *pXmlActRcddata = pXmlSierialize->xml_serialize("ActRcd", "ActRcd", "ActRcd", stt_ParaGroupKey());

    if(pXmlActRcddata == NULL)
    {
        return;
    }

    CString strName, strID, strTemp, strTmp2;

#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("����");
    CString str2 = _T("��");
    CString str3 = _T("�ζ���ʱ��");
#else
	CString str1 = /*_T("����")*/g_sLangTxt_Native_BinX;
	CString str2 = /*_T("��")*/g_sLangTxt_Native_Number;
	CString str3 = /*_T("�ζ���ʱ��")*/g_sLangTxt_Native_NActionTime;
#endif

    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);

        for(int nIndexAct = 0; ((nIndexAct < 64) && (nIndexAct < pResults->m_nrBinSwitchCount[nIndex])); nIndexAct++)
        {
            strTmp2.Format(_T("%d"), nIndexAct + 1);
            strName = str1 + strTemp + str2 + strTmp2 + str3;
            strID.Format("Bin%dActCount%d", (nIndex + 1), (nIndexAct + 1));
            pXmlActRcddata->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_frTimeBinAct[nIndex][nIndexAct]);
        }
    }

    if(g_nBinExCount > 0)
    {
        CSttXmlSerializeBase *pXmlActRcdExdata = pXmlSierialize->xml_serialize("ActRcdEx", "ActRcdEx", "ActRcdEx", stt_ParaGroupKey());

        if(pXmlActRcdExdata == NULL)
        {
            return;
        }

        for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
        {
#ifdef NOT_USE_XLANGUAGE
            strTemp.Format(_T("��չ%d"), nIndex + 1);
#else
	    strTemp.Format(/*_T("��չ%d")*/g_sLangTxt_Native_extend.GetString(), nIndex + 1);
#endif
            for(int nIndexAct = 0; ((nIndexAct < 64) && (nIndexAct < pResults->m_nrBinExSwitchCount[nIndex])); nIndexAct++)
            {
                strTmp2.Format(_T("%d"), nIndexAct + 1);
                strName = str1 + strTemp + str2 + strTmp2 + str3;
                strID.Format("BinEx%dActCount%d", (nIndex + 1), (nIndexAct + 1));
                pXmlActRcdExdata->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_frTimeBinExAct[nIndex][nIndexAct]);
            }
        }
    }
}

void stt_xml_serialize(tmt_ManualImpedResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("�������", "TripFlag", "", "number", pResults->m_nTripFlag);
    pXmlSierialize->xml_serialize("����ʱ��", "TripTime", "", "number", pResults->m_fTripTime);
    pXmlSierialize->xml_serialize("����ֵ", "ActValue", "", "number", pResults->m_fActValue);
    pXmlSierialize->xml_serialize("����ֵ", "ReturnValue", "", "number", pResults->m_fReturnValue);
    pXmlSierialize->xml_serialize("����ϵ��", "ReturnCoef", "", "number", pResults->m_fReturnCoef);
    pXmlSierialize->xml_serialize("����ʱ��", "ReturnTime", "", "number", pResults->m_fReturnTime);
#else
	pXmlSierialize->xml_serialize(/*"�������"*/g_sLangTxt_Native_action_mark.GetString(), "TripFlag", "", "number", pResults->m_nTripFlag);
	pXmlSierialize->xml_serialize(/*"����ʱ��"*/g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number", pResults->m_fTripTime);
	pXmlSierialize->xml_serialize(/*"����ֵ"*/g_sLangTxt_State_ActionValue.GetString(), "ActValue", "", "number", pResults->m_fActValue);
	pXmlSierialize->xml_serialize(/*"����ֵ"*/g_sLangTxt_Native_ReturnValue.GetString(), "ReturnValue", "", "number", pResults->m_fReturnValue);
	pXmlSierialize->xml_serialize(/*"����ϵ��"*/g_sLangTxt_Gradient_ReCoefficient.GetString(), "ReturnCoef", "", "number", pResults->m_fReturnCoef);
	pXmlSierialize->xml_serialize(/*"����ʱ��"*/g_sLangTxt_Native_ReturnTime.GetString(), "ReturnTime", "", "number", pResults->m_fReturnTime);
#endif
    CString strName, strID, strTemp;
#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("����");
    CString str2 = _T("���״̬");
#else
	CString str1 = /*_T("����")*/g_sLangTxt_Native_BinX;
	CString str2 = /*_T("���״̬")*/g_sLangTxt_Native_result_status;
#endif
    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);
    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);
        strName = str1 + strTemp + str2;
        strID.Format("StateBin%d", (nIndex + 1));
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_nrBinSwitchCount[nIndex]);
    }

    if(g_nBinExCount > 0)
    {
        CSttXmlSerializeBase *pXmlStateBinEx = pXmlSierialize->xml_serialize("StateBinEx", "StateBinEx", "StateBinEx", stt_ParaGroupKey());

        if(pXmlStateBinEx != NULL)
        {
            for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
            {
#ifdef NOT_USE_XLANGUAGE
                strTemp.Format(_T("��չ%d"), nIndex + 1);
#else
		strTemp.Format(/*_T("��չ%d")*/g_sLangTxt_Native_extend.GetString(), nIndex + 1);
#endif
                strName = str1 + strTemp + str2;
                strID.Format("StateBinEx%d", (nIndex + 1));
                pXmlStateBinEx->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_nrBinExSwitchCount[nIndex]);
            }
        }
    }
    stt_xml_serialize_act_rcd(pResults, pXmlSierialize);
}

#include"../../../SttCmd/SttTestCmd.h"
#include"../../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_ManuImpedTest()
{
    tmt_ManualImpedTest oManualTest;
    oManualTest.init();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oManualTest.m_oManuImpedParas, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("ManualTestImpedDemo.xml");
    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

CSttXmlSerializeBase *stt_xml_serialize(tmt_ManualImpedTest *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSierialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if(pXmlParas  != NULL)
    {
        stt_xml_serialize(&pParas->m_oManuImpedParas, pXmlParas);
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSierialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if(pXmlResults  != NULL)
    {
        stt_xml_serialize(&pParas->m_oManuImpedResult, pXmlResults);
    }

    return pXmlParas;
}
