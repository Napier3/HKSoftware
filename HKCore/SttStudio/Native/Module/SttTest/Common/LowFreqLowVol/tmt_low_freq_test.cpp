#include "stdafx.h"
#include "tmt_low_freq_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_LowFreqParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_LowFreqParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_LowFreqParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_LowFreqParasEx));
	pParas->init();
}

void stt_init_results(tmt_LowFreqResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_LowFreqResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_Common(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��","HoldTime","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("����ʱ��ԣ��","MarginTime","s","number",pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("��̬ʱ��","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	// 	pXmlSierialize->xml_serialize("����仯ģʽ","ChangeMode","","PsudtChangeMode",pParas->m_nChangeMode);
	// 	pXmlSierialize->xml_serialize("�仯ʱ��","ChangeTime","","number",pParas->m_fChangeTime);

	pXmlSierialize->xml_serialize("��Ƶ����ֵ","FAct","Hz","number",pParas->m_fFAct);
	pXmlSierialize->xml_serialize("����ʱ��","FActTime","s","number",pParas->m_fFActTime);
	pXmlSierialize->xml_serialize("�������ֵ","DvdtClose","Hz/s","number",pParas->m_fDfdtClose);
	pXmlSierialize->xml_serialize("������ѹ","Ulow","V","number",pParas->m_fUlow);
	pXmlSierialize->xml_serialize("��������","Ilow","A","number",pParas->m_fILow);
	pXmlSierialize->xml_serialize("������ѹ����","USetMode","","VSetMode",pParas->m_nUSetMode);
#else
	pXmlSierialize->xml_serialize(/* "����ʱ��" */g_sLangTxt_Native_KeepTime.GetString(),"HoldTime","s","number",pParas->m_fHoldTime);
	pXmlSierialize->xml_serialize(/* "��̬ʱ��" */g_sLangTxt_Native_SteadyTime.GetString(),"PreFaultTime","s","number",pParas->m_fPreFaultTime);
	// 	pXmlSierialize->xml_serialize("����仯ģʽ","ChangeMode","","PsudtChangeMode",pParas->m_nChangeMode);
	// 	pXmlSierialize->xml_serialize("�仯ʱ��","ChangeTime","","number",pParas->m_fChangeTime);

	pXmlSierialize->xml_serialize(/* "��Ƶ����ֵ" */g_sLangTxt_Native_LowFreActValue.GetString(),"FAct","Hz","number",pParas->m_fFAct);
	pXmlSierialize->xml_serialize(/* "����ʱ��" */g_sLangTxt_Gradient_ActionTime.GetString(),"FActTime","s","number",pParas->m_fFActTime);
	pXmlSierialize->xml_serialize(/* "�������ֵ" */g_sLangTxt_Native_sliptripValue.GetString(),"DvdtClose","Hz/s","number",pParas->m_fDfdtClose);
	pXmlSierialize->xml_serialize(/* "������ѹ" */g_sLangTxt_interlock_vol.GetString(),"Ulow","V","number",pParas->m_fUlow);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_interlock_cur.GetString(),"Ilow","A","number",pParas->m_fILow);
	pXmlSierialize->xml_serialize(/* "������ѹ����" */g_sLangTxt_Native_LockVoltDef.GetString(),"USetMode","","VSetMode",pParas->m_nUSetMode);
#endif
	

	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Exbinary_out(pParas->m_binOutEx,pXmlSierialize);

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/* "�����߼�" */g_sLangTxt_Native_InLogic.GetString(),"_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#endif

	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))//���ݴ���
	{
	#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("����Aѡ��","_BinAEnable","","BOOL",pParas->m_binIn[0].nSelect);
		pXmlSierialize->xml_serialize("����Bѡ��","_BinBEnable","","BOOL",pParas->m_binIn[1].nSelect);
		pXmlSierialize->xml_serialize("����Cѡ��","_BinCEnable","","BOOL",pParas->m_binIn[2].nSelect);
		pXmlSierialize->xml_serialize("����Dѡ��","_BinDEnable","","BOOL",pParas->m_binIn[3].nSelect);
		pXmlSierialize->xml_serialize("����Eѡ��","_BinEEnable","","BOOL",pParas->m_binIn[4].nSelect);
		pXmlSierialize->xml_serialize("����Fѡ��","_BinFEnable","","BOOL",pParas->m_binIn[5].nSelect);
		pXmlSierialize->xml_serialize("����Gѡ��","_BinGEnable","","BOOL",pParas->m_binIn[6].nSelect);
		pXmlSierialize->xml_serialize("����Hѡ��","_BinHEnable","","BOOL",pParas->m_binIn[7].nSelect);
		pXmlSierialize->xml_serialize("����Iѡ��","_BinIEnable","","BOOL",pParas->m_binIn[8].nSelect);
		pXmlSierialize->xml_serialize("����Jѡ��","_BinJEnable","","BOOL",pParas->m_binIn[9].nSelect);

		pXmlSierialize->xml_serialize("����1״̬","_B01","","DOutputState",pParas->m_binOut[0].nState);
		pXmlSierialize->xml_serialize("����2״̬","_B02","","DOutputState",pParas->m_binOut[1].nState);
		pXmlSierialize->xml_serialize("����3״̬","_B03","","DOutputState",pParas->m_binOut[2].nState);
		pXmlSierialize->xml_serialize("����4״̬","_B04","","DOutputState",pParas->m_binOut[3].nState);
		pXmlSierialize->xml_serialize("����5״̬","_B05","","DOutputState",pParas->m_binOut[4].nState);
		pXmlSierialize->xml_serialize("����6״̬","_B06","","DOutputState",pParas->m_binOut[5].nState);
		pXmlSierialize->xml_serialize("����7״̬","_B07","","DOutputState",pParas->m_binOut[6].nState);
		pXmlSierialize->xml_serialize("����8״̬","_B08","","DOutputState",pParas->m_binOut[7].nState);
	#else
		pXmlSierialize->xml_serialize(/* "����Aѡ��" */g_sLangTxt_Native_InputASelect.GetString(),"_BinAEnable","","BOOL",pParas->m_binIn[0].nSelect);
		pXmlSierialize->xml_serialize(/* "����Bѡ��" */g_sLangTxt_Native_InputBSelect.GetString(),"_BinBEnable","","BOOL",pParas->m_binIn[1].nSelect);
		pXmlSierialize->xml_serialize(/* "����Cѡ��" */g_sLangTxt_Native_InputCSelect.GetString(),"_BinCEnable","","BOOL",pParas->m_binIn[2].nSelect);
		pXmlSierialize->xml_serialize(/* "����Dѡ��" */g_sLangTxt_Native_InputDSelect.GetString(),"_BinDEnable","","BOOL",pParas->m_binIn[3].nSelect);
		pXmlSierialize->xml_serialize(/* "����Eѡ��" */g_sLangTxt_Native_InputESelect.GetString(),"_BinEEnable","","BOOL",pParas->m_binIn[4].nSelect);
		pXmlSierialize->xml_serialize(/* "����Fѡ��" */g_sLangTxt_Native_InputFSelect.GetString(),"_BinFEnable","","BOOL",pParas->m_binIn[5].nSelect);
		pXmlSierialize->xml_serialize(/* "����Gѡ��" */g_sLangTxt_Native_InputGSelect.GetString(),"_BinGEnable","","BOOL",pParas->m_binIn[6].nSelect);
		pXmlSierialize->xml_serialize(/* "����Hѡ��" */g_sLangTxt_Native_InputHSelect.GetString(),"_BinHEnable","","BOOL",pParas->m_binIn[7].nSelect);
		pXmlSierialize->xml_serialize(/* "����Iѡ��" */g_sLangTxt_Native_InputISelect.GetString(),"_BinIEnable","","BOOL",pParas->m_binIn[8].nSelect);
		pXmlSierialize->xml_serialize(/* "����Jѡ��" */g_sLangTxt_Native_InputJSelect.GetString(),"_BinJEnable","","BOOL",pParas->m_binIn[9].nSelect);

		pXmlSierialize->xml_serialize(/* "����1״̬" */g_sLangTxt_Out1_Situation.GetString(),"_B01","","DOutputState",pParas->m_binOut[0].nState);
		pXmlSierialize->xml_serialize(/* "����2״̬" */g_sLangTxt_Out2_Situation.GetString(),"_B02","","DOutputState",pParas->m_binOut[1].nState);
		pXmlSierialize->xml_serialize(/* "����3״̬" */g_sLangTxt_Out3_Situation.GetString(),"_B03","","DOutputState",pParas->m_binOut[2].nState);
		pXmlSierialize->xml_serialize(/* "����4״̬" */g_sLangTxt_Out4_Situation.GetString(),"_B04","","DOutputState",pParas->m_binOut[3].nState);
		pXmlSierialize->xml_serialize(/* "����5״̬" */g_sLangTxt_Out5_Situation.GetString(),"_B05","","DOutputState",pParas->m_binOut[4].nState);
		pXmlSierialize->xml_serialize(/* "����6״̬" */g_sLangTxt_Out6_Situation.GetString(),"_B06","","DOutputState",pParas->m_binOut[5].nState);
		pXmlSierialize->xml_serialize(/* "����7״̬" */g_sLangTxt_Out7_Situation.GetString(),"_B07","","DOutputState",pParas->m_binOut[6].nState);
		pXmlSierialize->xml_serialize(/* "����8״̬" */g_sLangTxt_Out8_Situation.GetString(),"_B08","","DOutputState",pParas->m_binOut[7].nState);
	#endif
		
	}
}

void stt_xml_serialize_PsuLowFreqAct(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("Ƶ�ʻ���","dvdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize("Ƶ�ʱ仯ʼֵ","Fstart","Hz","number",pParas->m_fFstart);
	pXmlSierialize->xml_serialize("Ƶ�ʱ仯��ֵ","Fend","Hz","number",pParas->m_fFend);
	pXmlSierialize->xml_serialize("Ƶ�ʱ仯����","Fstep","Hz","number",pParas->m_fFstep);
#else
	pXmlSierialize->xml_serialize(/* "Ƶ�ʻ���" */g_sLangTxt_Native_FreqSlip.GetString(),"dvdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʱ仯ʼֵ" */g_sLangTxt_Native_FreInitialValue.GetString(),"Fstart","Hz","number",pParas->m_fFstart);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʱ仯��ֵ" */g_sLangTxt_Native_FreFinalValue.GetString(),"Fend","Hz","number",pParas->m_fFend);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʱ仯����" */g_sLangTxt_Native_FreChangeStep.GetString(),"Fstep","Hz","number",pParas->m_fFstep);
#endif

	stt_xml_serialize_Common(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowFreqTime(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("Ƶ�ʻ���","dvdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize("Ƶ�ʱ仯��ֵ","Fend","Hz","number",pParas->m_fFend);
    pXmlSierialize->xml_serialize("�����ʱ���ò���","DfdtTiming","","number",pParas->m_nDfdtTiming);
#else
	pXmlSierialize->xml_serialize(/* "Ƶ�ʻ���" */g_sLangTxt_Native_FreqSlip.GetString(),"dvdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʱ仯��ֵ" */g_sLangTxt_Native_FreFinalValue.GetString(),"Fend","Hz","number",pParas->m_fFend);
    pXmlSierialize->xml_serialize("�����ʱ���ò���","DfdtTiming","","number",pParas->m_nDfdtTiming);
#endif


	stt_xml_serialize_Common(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowFreqDfDt(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "Hz/s","number",pParas->m_fDfdtStart);
	pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "Hz/s","number",pParas->m_fDfdtEnd);
	pXmlSierialize->xml_serialize("�仯����", "Step", "Hz/s","number",pParas->m_fDfdtStep);
	pXmlSierialize->xml_serialize("Ƶ����ֵ", "FreqEnd", "Hz","number",pParas->m_fFend);
	stt_xml_serialize_Common(pParas,pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))//���ݴ���
	{
		pXmlSierialize->xml_serialize("�仯ʼֵ", "DfdtStart", "Hz/s","number",pParas->m_fDfdtStart);
		pXmlSierialize->xml_serialize("�仯��ֵ", "DfdtEnd", "Hz/s","number",pParas->m_fDfdtEnd);
		pXmlSierialize->xml_serialize("�仯����", "DfdtStep", "Hz/s","number",pParas->m_fDfdtStep);
		pXmlSierialize->xml_serialize("Ƶ����ֵ", "Fend", "Hz","number",pParas->m_fFend);
	}
#else
	pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "Hz/s","number",pParas->m_fDfdtStart);
	pXmlSierialize->xml_serialize(/* "�仯��ֵ" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "Hz/s","number",pParas->m_fDfdtEnd);
	pXmlSierialize->xml_serialize(/* "�仯����" */g_sLangTxt_Gradient_Step.GetString(), "Step", "Hz/s","number",pParas->m_fDfdtStep);
	pXmlSierialize->xml_serialize(/* "Ƶ����ֵ" */g_sLangTxt_Native_FreFinal.GetString(), "FreqEnd", "Hz","number",pParas->m_fFend);
	stt_xml_serialize_Common(pParas,pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))//���ݴ���
	{
		pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */g_sLangTxt_Gradient_Init.GetString(), "DfdtStart", "Hz/s","number",pParas->m_fDfdtStart);
		pXmlSierialize->xml_serialize(/* "�仯��ֵ" */g_sLangTxt_Gradient_Finish.GetString(), "DfdtEnd", "Hz/s","number",pParas->m_fDfdtEnd);
		pXmlSierialize->xml_serialize(/* "�仯����" */g_sLangTxt_Gradient_Step.GetString(), "DfdtStep", "Hz/s","number",pParas->m_fDfdtStep);
		pXmlSierialize->xml_serialize(/* "Ƶ����ֵ" */g_sLangTxt_Native_FreFinal.GetString(), "Fend", "Hz","number",pParas->m_fFend);
	}
#endif
}

void stt_xml_serialize_PsuLowFreqILock(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "A","number",pParas->m_fIStart);
	pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "A","number",pParas->m_fIEnd);
	pXmlSierialize->xml_serialize("�仯����", "Step", "A","number",pParas->m_fIStep);
	pXmlSierialize->xml_serialize("Ƶ�ʻ���","Dfdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize("Ƶ����ֵ", "RampTo", "Hz","number",pParas->m_fFend);
	pXmlSierialize->xml_serialize("�����仯��", "IVariable", "","number",pParas->m_nIPhase);
	stt_xml_serialize_Common(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "A","number",pParas->m_fIStart);
	pXmlSierialize->xml_serialize(/* "�仯��ֵ" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "A","number",pParas->m_fIEnd);
	pXmlSierialize->xml_serialize(/* "�仯����" */g_sLangTxt_Gradient_Step.GetString(), "Step", "A","number",pParas->m_fIStep);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʻ���" */g_sLangTxt_Native_FreqSlip.GetString(),"Dfdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize(/* "Ƶ����ֵ" */g_sLangTxt_Native_FreFinal.GetString(), "RampTo", "Hz","number",pParas->m_fFend);
	pXmlSierialize->xml_serialize(/* "�����仯��" */g_sLangTxt_Native_IChangePhase.GetString(), "IVariable", "","number",pParas->m_nIPhase);
	stt_xml_serialize_Common(pParas,pXmlSierialize);
#endif
}

void stt_xml_serialize_PsuLowFreqULock(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "A","number",pParas->m_fUStart);
	pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "A","number",pParas->m_fUEnd);
	pXmlSierialize->xml_serialize("�仯����", "Step", "A","number",pParas->m_fUStep);
	pXmlSierialize->xml_serialize("Ƶ�ʻ���","Dfdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize("Ƶ����ֵ", "RampTo", "Hz","number",pParas->m_fFend);
	pXmlSierialize->xml_serialize("��ѹ�仯��", "UVariable", "","number",pParas->m_nUPhase);
	stt_xml_serialize_Common(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "A","number",pParas->m_fUStart);
	pXmlSierialize->xml_serialize(/* "�仯��ֵ" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "A","number",pParas->m_fUEnd);
	pXmlSierialize->xml_serialize(/* "�仯����" */g_sLangTxt_Gradient_Step.GetString(), "Step", "A","number",pParas->m_fUStep);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʻ���" */g_sLangTxt_Native_FreqSlip.GetString(),"Dfdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize(/* "Ƶ����ֵ" */g_sLangTxt_Native_FreFinal.GetString(), "RampTo", "Hz","number",pParas->m_fFend);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯��" */g_sLangTxt_Native_VoltChangeAmt.GetString(), "UVariable", "","number",pParas->m_nUPhase);
	stt_xml_serialize_Common(pParas,pXmlSierialize);
#endif

}

void stt_xml_serialize_PnvLowFreqTime(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("Ƶ�ʻ���","Dfdt","Hz/s","number",pParas->m_fDfdt);
    pXmlSierialize->xml_serialize("Ƶ�ʱ仯��ֵ","RampTo","Hz","number",pParas->m_fFend);
    pXmlSierialize->xml_serialize("����ʱ��","TimeAfterTrig","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("��ʱ����ֵ","TimerStartValue","Hz","number",pParas->m_fFAct);
    pXmlSierialize->xml_serialize("����ֵ","ResetValue","Hz","number",pParas->m_fFnom);
    pXmlSierialize->xml_serialize("����ǰ����ʱ��","RampResetTime","s","number",pParas->m_fPreFaultTime);

    pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);

    pXmlSierialize->xml_serialize("Ua��ֵ", "Ua", "V", "number", pParas->m_fUabc[0]);
    pXmlSierialize->xml_serialize("Ua��λ", "UaPh", "��", "number", pParas->m_fUabcPh[0]);
    pXmlSierialize->xml_serialize("Ub��ֵ", "Ub", "V", "number", pParas->m_fUabc[1]);
    pXmlSierialize->xml_serialize("Ub��λ", "UbPh", "��", "number", pParas->m_fUabcPh[1]);
    pXmlSierialize->xml_serialize("Uc��ֵ", "Uc", "V", "number", pParas->m_fUabc[2]);
    pXmlSierialize->xml_serialize("Uc��λ", "UcPh", "��", "number", pParas->m_fUabcPh[2]);
    pXmlSierialize->xml_serialize("Ia��ֵ", "Ia", "A", "number", pParas->m_fIabc[0]);
    pXmlSierialize->xml_serialize("Ia��λ", "IaPh", "��", "number", pParas->m_fIabcPh[0]);
    pXmlSierialize->xml_serialize("Ib��ֵ", "Ib", "A", "number", pParas->m_fIabc[1]);
    pXmlSierialize->xml_serialize("Ib��λ", "IbPh", "��", "number", pParas->m_fIabcPh[1]);
    pXmlSierialize->xml_serialize("Ic��ֵ", "Ic", "A", "number", pParas->m_fIabc[2]);
    pXmlSierialize->xml_serialize("Ic��λ", "IcPh", "��", "number", pParas->m_fIabcPh[2]);

    stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx,pXmlSierialize);
}
void stt_xml_serialize_PnvLowFreqAct(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("Ƶ�ʱ仯��","Dfdt","Hz/s","number",pParas->m_fDfdt);
    pXmlSierialize->xml_serialize("�仯ʼֵ","BeginVal","Hz","number",pParas->m_fFstart);
    pXmlSierialize->xml_serialize("�仯��ֵ","EndVal","Hz","number",pParas->m_fFend);
    pXmlSierialize->xml_serialize("���Ծ���","Step","Hz","number",pParas->m_fFstep);

    pXmlSierialize->xml_serialize("����ʱ��","TimeAfterTrig","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("���ⶨֵ","ValSetting","Hz","number",pParas->m_fFAct);
    pXmlSierialize->xml_serialize("����ֵ","_ResetValue","Hz","number",pParas->m_fFnom);
    pXmlSierialize->xml_serialize("����ǰ����ʱ��","RampResetTime","s","number",pParas->m_fPreFaultTime);

    pXmlSierialize->xml_serialize("����ǰUa", "_PreFaultUa", "V", "number", pParas->m_fUabc[0]);
    pXmlSierialize->xml_serialize("����ǰUa��λ", "_PreFaultUaPh", "��", "number", pParas->m_fUabcPh[0]);
    pXmlSierialize->xml_serialize("����ǰUb", "_PreFaultUb", "V", "number", pParas->m_fUabc[1]);
    pXmlSierialize->xml_serialize("����ǰUb��λ", "_PreFaultUbPh", "��", "number", pParas->m_fUabcPh[1]);
    pXmlSierialize->xml_serialize("����ǰUc", "_PreFaultUc", "V", "number", pParas->m_fUabc[2]);
    pXmlSierialize->xml_serialize("����ǰUc��λ", "_PreFaultUcPh", "��", "number", pParas->m_fUabcPh[2]);
    pXmlSierialize->xml_serialize("����ǰIa", "_PreFaultIa", "A", "number", pParas->m_fIabc[0]);
    pXmlSierialize->xml_serialize("����ǰIa��λ", "_PreFaultIaPh", "��", "number", pParas->m_fIabcPh[0]);
    pXmlSierialize->xml_serialize("����ǰIb", "_PreFaultIb", "A", "number", pParas->m_fIabc[1]);
    pXmlSierialize->xml_serialize("����ǰIb��λ", "_PreFaultIbPh", "��", "number", pParas->m_fIabcPh[1]);
    pXmlSierialize->xml_serialize("����ǰIc", "_PreFaultIc", "A", "number", pParas->m_fIabc[2]);
    pXmlSierialize->xml_serialize("����ǰIc��λ", "_PreFaultIcPh", "��", "number", pParas->m_fIabcPh[2]);
    pXmlSierialize->xml_serialize("����Ua", "_FaultUa", "V", "number", pParas->m_fUabc[3]);
    pXmlSierialize->xml_serialize("����Ua��λ", "_FaultUaPh", "��", "number", pParas->m_fUabcPh[3]);
    pXmlSierialize->xml_serialize("����Ub", "_FaultUb", "V", "number", pParas->m_fUabc[4]);
    pXmlSierialize->xml_serialize("����Ub��λ", "_FaultUbPh", "��", "number", pParas->m_fUabcPh[4]);
    pXmlSierialize->xml_serialize("����Uc", "_FaultUc", "V", "number", pParas->m_fUabc[5]);
    pXmlSierialize->xml_serialize("����Uc��λ", "_FaultUcPh", "��", "number", pParas->m_fUabcPh[5]);
    pXmlSierialize->xml_serialize("����Ia", "_FaultIa", "A", "number", pParas->m_fIabc[3]);
    pXmlSierialize->xml_serialize("����Ia��λ", "_FaultIaPh", "��", "number", pParas->m_fIabcPh[3]);
    pXmlSierialize->xml_serialize("����Ib", "_FaultIb", "A", "number", pParas->m_fIabc[4]);
    pXmlSierialize->xml_serialize("����Ib��λ", "_FaultIbPh", "��", "number", pParas->m_fIabcPh[4]);
    pXmlSierialize->xml_serialize("����Ic", "_FaultIc", "A", "number", pParas->m_fIabc[5]);
    pXmlSierialize->xml_serialize("����Ic��λ", "_FaultIcPh", "��", "number", pParas->m_fIabcPh[5]);

    pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx,pXmlSierialize);
}
void stt_xml_serialize_PnvLowFreqDfdt(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "Hz/s","number",pParas->m_fDfdtStart);
    pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "Hz/s","number",pParas->m_fDfdtEnd);
    pXmlSierialize->xml_serialize("���Ծ���", "Step", "Hz/s","number",pParas->m_fDfdtStep);
    pXmlSierialize->xml_serialize("Ƶ����ֵ", "FreqEnd", "Hz","number",pParas->m_fFend);

    pXmlSierialize->xml_serialize("����ʱ��","TimeAfterTrig","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("���ⶨֵ","ValSetting","Hz","number",pParas->m_fDfdtClose);
    pXmlSierialize->xml_serialize("����ֵ","ResetValue","Hz","number",pParas->m_fFnom);
    pXmlSierialize->xml_serialize("����ǰ����ʱ��","RampResetTime","s","number",pParas->m_fPreFaultTime);

    pXmlSierialize->xml_serialize("����ǰUa", "_PreFaultUa", "V", "number", pParas->m_fUabc[0]);
    pXmlSierialize->xml_serialize("����ǰUa��λ", "_PreFaultUaPh", "��", "number", pParas->m_fUabcPh[0]);
    pXmlSierialize->xml_serialize("����ǰUb", "_PreFaultUb", "V", "number", pParas->m_fUabc[1]);
    pXmlSierialize->xml_serialize("����ǰUb��λ", "_PreFaultUbPh", "��", "number", pParas->m_fUabcPh[1]);
    pXmlSierialize->xml_serialize("����ǰUc", "_PreFaultUc", "V", "number", pParas->m_fUabc[2]);
    pXmlSierialize->xml_serialize("����ǰUc��λ", "_PreFaultUcPh", "��", "number", pParas->m_fUabcPh[2]);
    pXmlSierialize->xml_serialize("����ǰIa", "_PreFaultIa", "A", "number", pParas->m_fIabc[0]);
    pXmlSierialize->xml_serialize("����ǰIa��λ", "_PreFaultIaPh", "��", "number", pParas->m_fIabcPh[0]);
    pXmlSierialize->xml_serialize("����ǰIb", "_PreFaultIb", "A", "number", pParas->m_fIabc[1]);
    pXmlSierialize->xml_serialize("����ǰIb��λ", "_PreFaultIbPh", "��", "number", pParas->m_fIabcPh[1]);
    pXmlSierialize->xml_serialize("����ǰIc", "_PreFaultIc", "A", "number", pParas->m_fIabc[2]);
    pXmlSierialize->xml_serialize("����ǰIc��λ", "_PreFaultIcPh", "��", "number", pParas->m_fIabcPh[2]);
    pXmlSierialize->xml_serialize("����Ua", "_FaultUa", "V", "number", pParas->m_fUabc[3]);
    pXmlSierialize->xml_serialize("����Ua��λ", "_FaultUaPh", "��", "number", pParas->m_fUabcPh[3]);
    pXmlSierialize->xml_serialize("����Ub", "_FaultUb", "V", "number", pParas->m_fUabc[4]);
    pXmlSierialize->xml_serialize("����Ub��λ", "_FaultUbPh", "��", "number", pParas->m_fUabcPh[4]);
    pXmlSierialize->xml_serialize("����Uc", "_FaultUc", "V", "number", pParas->m_fUabc[5]);
    pXmlSierialize->xml_serialize("����Uc��λ", "_FaultUcPh", "��", "number", pParas->m_fUabcPh[5]);
    pXmlSierialize->xml_serialize("����Ia", "_FaultIa", "A", "number", pParas->m_fIabc[3]);
    pXmlSierialize->xml_serialize("����Ia��λ", "_FaultIaPh", "��", "number", pParas->m_fIabcPh[3]);
    pXmlSierialize->xml_serialize("����Ib", "_FaultIb", "A", "number", pParas->m_fIabc[4]);
    pXmlSierialize->xml_serialize("����Ib��λ", "_FaultIbPh", "��", "number", pParas->m_fIabcPh[4]);
    pXmlSierialize->xml_serialize("����Ic", "_FaultIc", "A", "number", pParas->m_fIabc[5]);
    pXmlSierialize->xml_serialize("����Ic��λ", "_FaultIcPh", "��", "number", pParas->m_fIabcPh[5]);

    pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx,pXmlSierialize);
}
void stt_xml_serialize_LowFreq_search_results(tmt_LowFreqParas *pParas,tmt_LowFreqResults *pResults,CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSerialize->xml_serialize("��ǰ��������ֵ(dfdt)","CurrSearchDfdt","","number",pParas->m_fCurrSearchDfdt);
#else
	pXmlSerialize->xml_serialize(/* "��ǰ��������ֵ(dfdt)" */g_sLangTxt_Native_SearchslipVal.GetString(),"CurrSearchDfdt","","number",pParas->m_fCurrSearchDfdt);
#endif

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_PsuLowFreqAct_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("Ƶ�ʻ���(���ʽ)","dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize("Ƶ�ʱ仯ʼֵ(���ʽ)","FstartExp","","string",pParas->m_pszFstart);
	pXmlSierialize->xml_serialize("Ƶ�ʱ仯��ֵ(���ʽ)","FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize("Ƶ�ʱ仯����(���ʽ)","FstepExp","","string",pParas->m_pszFstep);
#else
	pXmlSierialize->xml_serialize(/* "����ʱ��(���ʽ)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʻ���(���ʽ)" */g_sLangTxt_Native_FreqSlip_Exp.GetString(),"dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʱ仯ʼֵ(���ʽ)" */g_sLangTxt_Native_FreInitialValueExp.GetString(),"FstartExp","","string",pParas->m_pszFstart);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʱ仯��ֵ(���ʽ)" */g_sLangTxt_Native_FreFinalValueExp.GetString(),"FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʱ仯����(���ʽ)" */g_sLangTxt_Native_FreChangeStepExp.GetString(),"FstepExp","","string",pParas->m_pszFstep);
#endif
	
	stt_xml_serialize_PsuLowFreqAct(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowFreqTime_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("Ƶ�ʻ���(���ʽ)","dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize("Ƶ�ʱ仯��ֵ(���ʽ)","FendExp","","string",pParas->m_pszFend);
#else
	pXmlSierialize->xml_serialize(/* "����ʱ��(���ʽ)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʻ���(���ʽ)" */g_sLangTxt_Native_FreqSlip_Exp.GetString(),"dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʱ仯��ֵ(���ʽ)" */g_sLangTxt_Native_FreFinalValueExp.GetString(),"FendExp","","string",pParas->m_pszFend);
#endif
	stt_xml_serialize_PsuLowFreqTime(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowFreqDfDt_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("Ƶ�ʱ仯��ֵ(���ʽ)","FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize("����仯ʼֵ(���ʽ)", "BeginValExp", "","string",pParas->m_pszDfdtStart);
	pXmlSierialize->xml_serialize("����仯��ֵ(���ʽ)", "EndValExp", "","string",pParas->m_pszDfdtEnd);
	pXmlSierialize->xml_serialize("����仯����(���ʽ)", "StepExp", "","string",pParas->m_pszDfdtStep);
#else
	pXmlSierialize->xml_serialize(/* "����ʱ��(���ʽ)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʱ仯��ֵ(���ʽ)" */g_sLangTxt_Native_FreFinalValueExp.GetString(),"FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize(/* "����仯ʼֵ(���ʽ)" */g_sLangTxt_Native_SlipInitialValueExp.GetString(), "BeginValExp", "","string",pParas->m_pszDfdtStart);
	pXmlSierialize->xml_serialize(/* "����仯��ֵ(���ʽ)" */g_sLangTxt_Native_SlipFinalValueExp.GetString(), "EndValExp", "","string",pParas->m_pszDfdtEnd);
	pXmlSierialize->xml_serialize(/* "����仯����(���ʽ)" */g_sLangTxt_Native_SlipChangeStepExp.GetString(), "StepExp", "","string",pParas->m_pszDfdtStep);
#endif

	stt_xml_serialize_PsuLowFreqDfDt(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowFreqILock_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("Ƶ�ʻ���(���ʽ)","dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize("Ƶ�ʱ仯��ֵ(���ʽ)","FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize("�����仯ʼֵ(���ʽ)", "BeginValExp", "","string",pParas->m_pszIStart);
	pXmlSierialize->xml_serialize("�����仯��ֵ(���ʽ)", "EndValExp", "","string",pParas->m_pszIEnd);
	pXmlSierialize->xml_serialize("�����仯����(���ʽ)", "StepExp", "","string",pParas->m_pszIStep);
#else
	pXmlSierialize->xml_serialize(/* "����ʱ��(���ʽ)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʻ���(���ʽ)" */g_sLangTxt_Native_FreqSlip_Exp.GetString(),"dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʱ仯��ֵ(���ʽ)" */g_sLangTxt_Native_FreFinalValueExp.GetString(),"FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize(/* "�����仯ʼֵ(���ʽ)" */g_sLangTxt_Native_IInitialValueExp.GetString(), "BeginValExp", "","string",pParas->m_pszIStart);
	pXmlSierialize->xml_serialize(/* "�����仯��ֵ(���ʽ)" */g_sLangTxt_Native_IFinalValueExp.GetString(), "EndValExp", "","string",pParas->m_pszIEnd);
	pXmlSierialize->xml_serialize(/* "�����仯����(���ʽ)" */g_sLangTxt_Native_IChangeStepExp.GetString(), "StepExp", "","string",pParas->m_pszIStep);
#endif
	stt_xml_serialize_PsuLowFreqILock(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowFreqULock_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("Ƶ�ʻ���(���ʽ)","dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize("Ƶ�ʱ仯��ֵ(���ʽ)","FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize("��ѹ�仯ʼֵ(���ʽ)", "BeginValExp", "","string",pParas->m_pszUStart);
	pXmlSierialize->xml_serialize("��ѹ�仯��ֵ(���ʽ)", "EndValExp", "","string",pParas->m_pszUEnd);
	pXmlSierialize->xml_serialize("��ѹ�仯����(���ʽ)", "StepExp", "","string",pParas->m_pszUStep);
#else
	pXmlSierialize->xml_serialize(/* "����ʱ��(���ʽ)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʻ���(���ʽ)" */g_sLangTxt_Native_FreqSlip_Exp.GetString(),"dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʱ仯��ֵ(���ʽ)" */g_sLangTxt_Native_FreFinalValueExp.GetString(),"FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯ʼֵ(���ʽ)" */g_sLangTxt_Native_VInitialValueExp.GetString(), "BeginValExp", "","string",pParas->m_pszUStart);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯��ֵ(���ʽ)" */g_sLangTxt_Native_VFinalValueExp.GetString(), "EndValExp", "","string",pParas->m_pszUEnd);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯����(���ʽ)" */g_sLangTxt_Native_VChangeStepExp.GetString(), "StepExp", "","string",pParas->m_pszUStep);
#endif

	stt_xml_serialize_PsuLowFreqULock(pParas,pXmlSierialize);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_PsuLowFreqAct(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ","TripFre","Hz","number",pResults->m_fLowFAct);
	pXmlSierialize->xml_serialize("���ܶ�������", "ActFre", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "Ƶ�ʶ���ֵ" */g_sLangTxt_Native_FreActValue.GetString(),"TripFre","Hz","number",pResults->m_fLowFAct);
	pXmlSierialize->xml_serialize(/* "���ܶ�������" */g_sLangTxt_Native_LowCycleActDesc.GetString(), "ActFre", "", "number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_PsuLowFreqTime(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("���ܼ��ض���ʱ��","TTripLf","s","number",pResults->m_fLowFActTime);
	pXmlSierialize->xml_serialize("��������", "ActLf", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "���ܼ��ض���ʱ��" */g_sLangTxt_lowfreqloadre_ActTime.GetString(),"TTripLf","s","number",pResults->m_fLowFActTime);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActLf", "", "number",pResults->m_nAct);
#endif
}

void stt_xml_serialize_PsuLowFreqDfDt(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�����ֵ","TripDfdt","Hz/s","number",pResults->m_fDfdtAct);
	pXmlSierialize->xml_serialize("��������", "ActDfdt", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "�����ֵ" */g_sLangID_Native_SlipActValue.GetString(),"TripDfdt","Hz/s","number",pResults->m_fDfdtAct);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActDfdt", "", "number",pResults->m_nAct);
#endif
}

void stt_xml_serialize_PsuLowFreqILock(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��������ֵ", "TripILock", "A", "number",pResults->m_fIAct);
	pXmlSierialize->xml_serialize("��������", "ActILock", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "��������ֵ" */g_sLangTxt_Native_IBlockValue.GetString(), "TripILock", "A", "number",pResults->m_fIAct);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActILock", "", "number",pResults->m_nAct);
#endif
}

void stt_xml_serialize_PsuLowFreqULock(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹ����ֵ", "TripULock", "V", "number",pResults->m_fUAct);
	pXmlSierialize->xml_serialize("��������", "ActULock", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "��ѹ����ֵ" */g_sLangTxt_Native_VBlockValue.GetString(), "TripULock", "V", "number",pResults->m_fUAct);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActULock", "", "number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_PnvLowFreqTime(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("���ܼ��ض���ʱ��","TripT","s","number",pResults->m_fLowFActTime);
    pXmlSierialize->xml_serialize("��������", "ActT", "", "number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "���ܼ��ض���ʱ��" */g_sLangTxt_lowfreqloadre_ActTime.GetString(),"TripT","s","number",pResults->m_fLowFActTime);
    pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActT", "", "number",pResults->m_nAct);
#endif
}

void stt_xml_serialize_PnvLowFreqAct(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("���ܶ���ֵ","TripFreq","Hz","number",pResults->m_fLowFAct);
    pXmlSierialize->xml_serialize("���ܶ�������", "ActFreq", "", "number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "���ܼ��ض���ʱ��" */g_sLangTxt_lowfreqloadre_ActTime.GetString(),"TripT","s","number",pResults->m_fLowFActTime);
    pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActT", "", "number",pResults->m_nAct);
#endif
}

void stt_xml_serialize_PnvLowFreqDfdt(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("����ֵ","TripDfdt","Hz/s","number",pResults->m_fDfdtAct);
    pXmlSierialize->xml_serialize("��������", "ActDfdt", "", "number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "���ܼ��ض���ʱ��" */g_sLangTxt_lowfreqloadre_ActTime.GetString(),"TripT","s","number",pResults->m_fLowFActTime);
    pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActT", "", "number",pResults->m_nAct);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttXmlSerializeBase* stt_xml_serialize(tmt_LowFreqTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqAct) == 0)
		{
			stt_xml_serialize_PsuLowFreqAct_ex(&(pTests->m_oLowFreqParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqTime) == 0)
		{
			stt_xml_serialize_PsuLowFreqTime_ex(&(pTests->m_oLowFreqParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqDfdt) == 0)
		{
			stt_xml_serialize_PsuLowFreqDfDt_ex(&(pTests->m_oLowFreqParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqILock) == 0)
		{
			stt_xml_serialize_PsuLowFreqILock_ex(&(pTests->m_oLowFreqParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqULock) == 0)
		{
			stt_xml_serialize_PsuLowFreqULock_ex(&(pTests->m_oLowFreqParas), pXmlParas);
		}
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqTime) == 0)
        {
            stt_xml_serialize_PnvLowFreqTime(&(pTests->m_oLowFreqParas), pXmlParas);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqAct) == 0)
        {
            stt_xml_serialize_PnvLowFreqAct(&(pTests->m_oLowFreqParas), pXmlParas);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqDfdt) == 0)
        {
            stt_xml_serialize_PnvLowFreqDfdt(&(pTests->m_oLowFreqParas), pXmlParas);
        }
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqAct) == 0)
		{
			stt_xml_serialize_PsuLowFreqAct(&pTests->m_oLowFreqResults, pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqTime) == 0)
		{
			stt_xml_serialize_PsuLowFreqTime(&pTests->m_oLowFreqResults, pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqDfdt) == 0)
		{
			stt_xml_serialize_PsuLowFreqDfDt(&(pTests->m_oLowFreqResults), pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqILock) == 0)
		{
			stt_xml_serialize_PsuLowFreqILock(&(pTests->m_oLowFreqResults), pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqULock) == 0)
		{
			stt_xml_serialize_PsuLowFreqULock(&(pTests->m_oLowFreqResults), pXmlResults);
		}
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqTime) == 0)
        {
            stt_xml_serialize_PnvLowFreqTime(&(pTests->m_oLowFreqResults), pXmlResults);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqAct) == 0)
        {
            stt_xml_serialize_PnvLowFreqAct(&(pTests->m_oLowFreqResults), pXmlParas);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqDfdt) == 0)
        {
            stt_xml_serialize_PnvLowFreqDfdt(&(pTests->m_oLowFreqResults), pXmlParas);
        }
	}

	return pXmlParas;
}

void stt_xml_serialize_ex(tmt_LowFreqTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly)
{
	if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqAct) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_PsuLowFreqAct_ex(&(pTests->m_oLowFreqParas), pXmlSerialize);
		}
		
		stt_xml_serialize_PsuLowFreqAct(&(pTests->m_oLowFreqResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqTime) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_PsuLowFreqTime_ex(&(pTests->m_oLowFreqParas), pXmlSerialize);
		}
		
		stt_xml_serialize_PsuLowFreqTime(&(pTests->m_oLowFreqResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqDfdt) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_PsuLowFreqDfDt_ex(&(pTests->m_oLowFreqParas), pXmlSerialize);
		}
		
		stt_xml_serialize_PsuLowFreqDfDt(&(pTests->m_oLowFreqResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqILock) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_PsuLowFreqILock_ex(&(pTests->m_oLowFreqParas), pXmlSerialize);
		}
		
		stt_xml_serialize_PsuLowFreqILock(&(pTests->m_oLowFreqResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqULock) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_PsuLowFreqULock_ex(&(pTests->m_oLowFreqParas), pXmlSerialize);
		}
		
		stt_xml_serialize_PsuLowFreqULock(&(pTests->m_oLowFreqResults), pXmlSerialize);
	}
    else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqTime) == 0)
    {
        if(!bResultOnly)
        {
            stt_xml_serialize_PnvLowFreqTime(&(pTests->m_oLowFreqParas), pXmlSerialize);
        }

        stt_xml_serialize_PnvLowFreqTime(&(pTests->m_oLowFreqResults), pXmlSerialize);
    }
    else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqTime) == 0)
    {
        if(!bResultOnly)
        {
            stt_xml_serialize_PnvLowFreqAct(&(pTests->m_oLowFreqParas), pXmlSerialize);
        }

        stt_xml_serialize_PnvLowFreqAct(&(pTests->m_oLowFreqResults), pXmlSerialize);
    }
    else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqTime) == 0)
    {
        if(!bResultOnly)
        {
            stt_xml_serialize_PnvLowFreqDfdt(&(pTests->m_oLowFreqParas), pXmlSerialize);
        }

        stt_xml_serialize_PnvLowFreqDfdt(&(pTests->m_oLowFreqResults), pXmlSerialize);
    }
}
