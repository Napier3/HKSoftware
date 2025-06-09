#include "stdafx.h"
#include "tmt_low_vol_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_LowVolParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_LowVolParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_LowVolParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_LowVolParasEx));
	pParas->init();
}

void stt_init_results(tmt_LowVolResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_LowVolResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_Common(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��","HoldTime","s","number",pParas->m_fHoldTime);
	pXmlSierialize->xml_serialize("��̬ʱ��","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	// 	pXmlSierialize->xml_serialize("����仯ģʽ","ChangeMode","","PsudtChangeMode",pParas->m_nChangeMode);
	// 	pXmlSierialize->xml_serialize("�仯ʱ��","ChangeTime","","number",pParas->m_fChangeTime);

	pXmlSierialize->xml_serialize("��ѹ����ֵ","UAct","V","number",pParas->m_fUAct);
	pXmlSierialize->xml_serialize("����ʱ��","UActTime","s","number",pParas->m_fUActTime);
	pXmlSierialize->xml_serialize("��ѹ�仯�ʱ���ֵ","DvdtClose","V/s","number",pParas->m_fDvdtClose);
	pXmlSierialize->xml_serialize("������ѹ����","USetMode","","VSetMode",pParas->m_nUSetMode);
	pXmlSierialize->xml_serialize("����","IAct","A","number",pParas->m_fIAct);

	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);

	pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))//���ݴ���
	{
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
	}
#else
	pXmlSierialize->xml_serialize(/* "����ʱ��" */g_sLangTxt_Native_KeepTime.GetString(),"HoldTime","s","number",pParas->m_fHoldTime);
	pXmlSierialize->xml_serialize(/* "��̬ʱ��" */g_sLangTxt_Native_SteadyTime.GetString(),"PreFaultTime","s","number",pParas->m_fPreFaultTime);
	// 	pXmlSierialize->xml_serialize("����仯ģʽ","ChangeMode","","PsudtChangeMode",pParas->m_nChangeMode);
	// 	pXmlSierialize->xml_serialize("�仯ʱ��","ChangeTime","","number",pParas->m_fChangeTime);

	pXmlSierialize->xml_serialize(/* "��ѹ����ֵ" */g_sLangTxt_Native_LowVLockVal.GetString(),"UAct","V","number",pParas->m_fUAct);
	pXmlSierialize->xml_serialize(/* "����ʱ��" */g_sLangTxt_Gradient_ActionTime.GetString(),"UActTime","s","number",pParas->m_fUActTime);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯�ʱ���ֵ" */g_sLangTxt_Native_VChangeRate_blockVal.GetString(),"DvdtClose","V/s","number",pParas->m_fDvdtClose);
	pXmlSierialize->xml_serialize(/* "������ѹ����" */g_sLangTxt_Native_LockVoltDef.GetString(),"USetMode","","VSetMode",pParas->m_nUSetMode);
	pXmlSierialize->xml_serialize(/* "����" */g_sLangTxt_Native_Current.GetString(),"IAct","A","number",pParas->m_fIAct);

	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);

	pXmlSierialize->xml_serialize(/* "�����߼�" */g_sLangTxt_Native_InLogic.GetString(),"_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))//���ݴ���
	{
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
	}
#endif

}

void stt_xml_serialize_PsuLowVolAct(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹ����","dvdt","V/s","number",pParas->m_fDvdt);
	pXmlSierialize->xml_serialize("��ѹ�仯ʼֵ","Vstart","V","number",pParas->m_fVstart);
	pXmlSierialize->xml_serialize("��ѹ�仯��ֵ","Vend","V","number",pParas->m_fVend);
	pXmlSierialize->xml_serialize("��ѹ�仯����","Vstep","V","number",pParas->m_fVstep);
	pXmlSierialize->xml_serialize("��������","FaultType","","PsuLowUChangeMode",pParas->m_nFaultType);
#else
	pXmlSierialize->xml_serialize(/* "��ѹ����" */g_sLangTxt_Native_VoltSlip.GetString(),"dvdt","V/s","number",pParas->m_fDvdt);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯ʼֵ" */g_sLangTxt_Native_InitVoltChange.GetString(),"Vstart","V","number",pParas->m_fVstart);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯��ֵ" */g_sLangTxt_Native_FinalVoltChange.GetString(),"Vend","V","number",pParas->m_fVend);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯����" */g_sLangTxt_Native_VoltChangeStep.GetString(),"Vstep","V","number",pParas->m_fVstep);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Gradient_FailType.GetString(),"FaultType","","PsuLowUChangeMode",pParas->m_nFaultType);
#endif

	stt_xml_serialize_Common(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowVolTime(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹ����","dvdt","V/s","number",pParas->m_fDvdt);
	pXmlSierialize->xml_serialize("��ѹ�仯��ֵ","Vend","V","number",pParas->m_fVend);
    pXmlSierialize->xml_serialize("�����ʱ���ò���","DvdtTiming","","number",pParas->m_nDvdtTiming);
#else
	pXmlSierialize->xml_serialize(/* "��ѹ����" */g_sLangTxt_Native_VoltSlip.GetString(),"dvdt","V/s","number",pParas->m_fDvdt);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯��ֵ" */g_sLangTxt_Native_FinalVoltChange.GetString(),"Vend","V","number",pParas->m_fVend);
    pXmlSierialize->xml_serialize("�����ʱ���ò���","DvdtTiming","","number",pParas->m_nDvdtTiming);
#endif


	stt_xml_serialize_Common(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowVolDvDt(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
 	pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "V/s","number",pParas->m_fDvdtStart);
 	pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "V/s","number",pParas->m_fDvdtEnd);
 	pXmlSierialize->xml_serialize("�仯����", "Step", "V/s","number",pParas->m_fDvdtStep);
 	pXmlSierialize->xml_serialize("��ѹ�仯��ֵ", "Vend", "V","number",pParas->m_fVend);

	if (stt_xml_serialize_is_read(pXmlSierialize))//���ݴ���
	{
		pXmlSierialize->xml_serialize("�仯ʼֵ", "DvdtStart", "V/s","number",pParas->m_fDvdtStart);
		pXmlSierialize->xml_serialize("�仯��ֵ", "DvdtEnd", "V/s","number",pParas->m_fDvdtEnd);
		pXmlSierialize->xml_serialize("�仯����", "DvdtStep", "V/s","number",pParas->m_fDvdtStep);
	}
#else
 	pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "V/s","number",pParas->m_fDvdtStart);
 	pXmlSierialize->xml_serialize(/* "�仯��ֵ" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "V/s","number",pParas->m_fDvdtEnd);
 	pXmlSierialize->xml_serialize(/* "�仯����" */g_sLangTxt_Gradient_Step.GetString(), "Step", "V/s","number",pParas->m_fDvdtStep);
 	pXmlSierialize->xml_serialize(/* "��ѹ�仯��ֵ" */g_sLangTxt_Native_FinalVoltChange.GetString(), "Vend", "V","number",pParas->m_fVend);

	if (stt_xml_serialize_is_read(pXmlSierialize))//���ݴ���
	{
		pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */g_sLangTxt_Gradient_Init.GetString(), "DvdtStart", "V/s","number",pParas->m_fDvdtStart);
		pXmlSierialize->xml_serialize(/* "�仯��ֵ" */g_sLangTxt_Gradient_Finish.GetString(), "DvdtEnd", "V/s","number",pParas->m_fDvdtEnd);
		pXmlSierialize->xml_serialize(/* "�仯����" */g_sLangTxt_Gradient_Step.GetString(), "DvdtStep", "V/s","number",pParas->m_fDvdtStep);
	}
#endif

	stt_xml_serialize_Common(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowVolILock( tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize )
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹ����","dvdt","V/s","number",pParas->m_fDvdt);
	pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "A","number",pParas->m_fIStart);
	pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "A","number",pParas->m_fIEnd);
	pXmlSierialize->xml_serialize("�仯����", "Step", "A","number",pParas->m_fIStep);
	pXmlSierialize->xml_serialize("���������", "IVariable", "","number",pParas->m_nIPhase);
	pXmlSierialize->xml_serialize("��ѹ�仯��ֵ", "Vend", "V","number",pParas->m_fVend);

#else
	pXmlSierialize->xml_serialize(/* "��ѹ����" */g_sLangTxt_Native_VoltSlip.GetString(),"dvdt","V/s","number",pParas->m_fDvdt);
	pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "A","number",pParas->m_fIStart);
	pXmlSierialize->xml_serialize(/* "�仯��ֵ" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "A","number",pParas->m_fIEnd);
	pXmlSierialize->xml_serialize(/* "�仯����" */g_sLangTxt_Gradient_Step.GetString(), "Step", "A","number",pParas->m_fIStep);
	pXmlSierialize->xml_serialize(/* "���������" */g_sLangTxt_Native_IChangePhase.GetString(), "IVariable", "","number",pParas->m_nIPhase);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯��ֵ" */g_sLangTxt_Native_FinalVoltChange.GetString(), "Vend", "V","number",pParas->m_fVend);
#endif

	stt_xml_serialize_Common(pParas,pXmlSierialize);

}

void stt_xml_serialize_PnvLowVolAct(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("��ѹ����","Dvdt","V/s","number",pParas->m_fDvdt);
    pXmlSierialize->xml_serialize("�仯ʼֵ","BeginVal","V","number",pParas->m_fVstart);
    pXmlSierialize->xml_serialize("�仯��ֵ","EndVal","V","number",pParas->m_fVend);
    pXmlSierialize->xml_serialize("���Ծ���","Step","V","number",pParas->m_fVstep);

    pXmlSierialize->xml_serialize("��ѹ�仯��","VolVari","","LowVolVari",pParas->m_nFaultType);
    pXmlSierialize->xml_serialize("����ʱ��","TimeAfterTrig","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("����ǰ����ʱ��","RampResetTime","s","number",pParas->m_fPreFaultTime);

    pXmlSierialize->xml_serialize("���ⶨֵ","ValSetting","V","number",pParas->m_fUAct);
    pXmlSierialize->xml_serialize("��ѹ����","VSetMode","","VSetMode",pParas->m_nUSetMode);

    pXmlSierialize->xml_serialize("����Ia","_FaultIa","A","set",pParas->m_uiCUR[1][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Ib","_FaultIb","A","set",pParas->m_uiCUR[1][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Ic","_FaultIc","A","set",pParas->m_uiCUR[1][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Ia��λ","_FaultIaPh","��","number",pParas->m_uiCUR[1][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����Ib��λ","_FaultIbPh","��","number",pParas->m_uiCUR[1][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����Ic��λ","_FaultIcPh","��","number",pParas->m_uiCUR[1][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����Ua��λ","_FaultUaPh","��","number",pParas->m_uiVOL[1][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����Ub��λ","_FaultUbPh","��","number",pParas->m_uiVOL[1][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����Uc��λ","_FaultUcPh","��","number",pParas->m_uiVOL[1][2].Harm[1].fAngle);

    pXmlSierialize->xml_serialize("����ǰIa","_PreFaultIa","A","set",pParas->m_uiCUR[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰIb","_PreFaultIb","A","set",pParas->m_uiCUR[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰIc","_PreFaultIc","A","set",pParas->m_uiCUR[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰIa��λ","_PreFaultIaPh","��","number",pParas->m_uiCUR[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����ǰIb��λ","_PreFaultIbPh","��","number",pParas->m_uiCUR[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����ǰIc��λ","_PreFaultIcPh","��","number",pParas->m_uiCUR[0][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����ǰUa","_PreFaultUa","V","set",pParas->m_uiVOL[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰUb","_PreFaultUb","V","set",pParas->m_uiVOL[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰUc","_PreFaultUc","V","set",pParas->m_uiVOL[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰUa��λ","_PreFaultUaPh","��","number",pParas->m_uiVOL[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����ǰUb��λ","_PreFaultUbPh","��","number",pParas->m_uiVOL[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����ǰUc��λ","_PreFaultUcPh","��","number",pParas->m_uiVOL[0][2].Harm[1].fAngle);


    stt_xml_serialize_binary_out(pParas->m_binOut,pXmlSierialize);
    pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic",pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);

}

void stt_xml_serialize_PnvLowVolTime(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("��ѹ����","Dvdt","V/s","number",pParas->m_fDvdt);
    pXmlSierialize->xml_serialize("�仯��ֵֹ","RampTo","V","number",pParas->m_fVend);

    pXmlSierialize->xml_serialize("����ʱ��","TimeAfterTrig","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("����ǰ����ʱ��","RampResetTime","s","number",pParas->m_fPreFaultTime);

    pXmlSierialize->xml_serialize("��ʱ����ֵ","TimerStartValue","V","number",pParas->m_fUActTime);
    pXmlSierialize->xml_serialize("������ѹ����","VSetMode","","VSetMode",pParas->m_nUSetMode);

    pXmlSierialize->xml_serialize("Ia","Ia","A","set",pParas->m_uiCUR[1][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib","Ib","A","set",pParas->m_uiCUR[1][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic","Ic","A","set",pParas->m_uiCUR[1][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia��λ","IaPh","��","number",pParas->m_uiCUR[1][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib��λ","IbPh","��","number",pParas->m_uiCUR[1][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic��λ","IcPh","��","number",pParas->m_uiCUR[1][2].Harm[1].fAngle);

    pXmlSierialize->xml_serialize("����ǰUa","_PreFaultUa","V","set",pParas->m_uiVOL[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰUb","_PreFaultUb","V","set",pParas->m_uiVOL[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰUc","_PreFaultUc","V","set",pParas->m_uiVOL[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰUa��λ","_PreFaultUaPh","��","number",pParas->m_uiVOL[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����ǰUb��λ","_PreFaultUbPh","��","number",pParas->m_uiVOL[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����ǰUc��λ","_PreFaultUcPh","��","number",pParas->m_uiVOL[0][2].Harm[1].fAngle);

    stt_xml_serialize_binary_out(pParas->m_binOut,pXmlSierialize);
    pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic",pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);

}

void stt_xml_serialize_PnvLowVolDvDt(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "V/s","number",pParas->m_fDvdtStart);
    pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "V/s","number",pParas->m_fDvdtEnd);
    pXmlSierialize->xml_serialize("�仯����", "Step", "V/s","number",pParas->m_fDvdtStep);
    pXmlSierialize->xml_serialize("��ѹ�仯��ֵ", "Vend", "V","number",pParas->m_fVend);

    pXmlSierialize->xml_serialize("����ʱ��","TimeAfterTrig","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("����ǰ����ʱ��","RampResetTime","s","number",pParas->m_fPreFaultTime);

    pXmlSierialize->xml_serialize("���ⶨֵ","ValSetting","V","number",pParas->m_fDvdtClose);
    pXmlSierialize->xml_serialize("��ѹ����","VSetMode","","VSetMode",pParas->m_nUSetMode);

    pXmlSierialize->xml_serialize("����Ia","_FaultIa","A","set",pParas->m_uiCUR[1][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Ib","_FaultIb","A","set",pParas->m_uiCUR[1][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Ic","_FaultIc","A","set",pParas->m_uiCUR[1][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Ia��λ","_FaultIaPh","��","number",pParas->m_uiCUR[1][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����Ib��λ","_FaultIbPh","��","number",pParas->m_uiCUR[1][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����Ic��λ","_FaultIcPh","��","number",pParas->m_uiCUR[1][2].Harm[1].fAngle);

    pXmlSierialize->xml_serialize("����ǰIa","_PreFaultIa","A","set",pParas->m_uiCUR[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰIb","_PreFaultIb","A","set",pParas->m_uiCUR[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰIc","_PreFaultIc","A","set",pParas->m_uiCUR[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰIa��λ","_PreFaultIaPh","��","number",pParas->m_uiCUR[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����ǰIb��λ","_PreFaultIbPh","��","number",pParas->m_uiCUR[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����ǰIc��λ","_PreFaultIcPh","��","number",pParas->m_uiCUR[0][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����ǰUa","_PreFaultUa","V","set",pParas->m_uiVOL[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰUb","_PreFaultUb","V","set",pParas->m_uiVOL[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰUc","_PreFaultUc","V","set",pParas->m_uiVOL[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����ǰUa��λ","_PreFaultUaPh","��","number",pParas->m_uiVOL[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����ǰUb��λ","_PreFaultUbPh","��","number",pParas->m_uiVOL[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("����ǰUc��λ","_PreFaultUcPh","��","number",pParas->m_uiVOL[0][2].Harm[1].fAngle);


    stt_xml_serialize_binary_out(pParas->m_binOut,pXmlSierialize);
    pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic",pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);

}

void stt_xml_serialize_LowVol_search_results(tmt_LowVolParas *pParas,tmt_LowVolResults *pResults,CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSerialize->xml_serialize("��ǰ��������ֵ(dvdt)","CurrSearchDvdt","","number",pParas->m_fCurrSearchDvdt);
#else
	pXmlSerialize->xml_serialize(/* "��ǰ��������ֵ(dvdt)" */g_sLangTxt_Native_SearchslipVal2.GetString(),"CurrSearchDvdt","","number",pParas->m_fCurrSearchDvdt);
#endif

}

void stt_xml_serialize_PsuLowVolAct_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("��ѹ����(���ʽ)","dvdtExp","","string",pParas->m_pszDvdt);
	pXmlSierialize->xml_serialize("��ѹ�仯ʼֵ(���ʽ)","VstartExp","","string",pParas->m_pszVstart);
	pXmlSierialize->xml_serialize("��ѹ�仯��ֵ(���ʽ)","VendExp","","string",pParas->m_pszVend);
	pXmlSierialize->xml_serialize("��ѹ�仯����(���ʽ)","VstepExp","","string",pParas->m_pszVstep);
#else
	pXmlSierialize->xml_serialize(/* "����ʱ��(���ʽ)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "��ѹ����(���ʽ)" */g_sLangTxt_Native_VoltSlip.GetString(),"dvdtExp","","string",pParas->m_pszDvdt);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯ʼֵ(���ʽ)" */g_sLangTxt_Native_VInitialValueExp.GetString(),"VstartExp","","string",pParas->m_pszVstart);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯��ֵ(���ʽ)" */g_sLangTxt_Native_VFinalValueExp.GetString(),"VendExp","","string",pParas->m_pszVend);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯����(���ʽ)" */g_sLangTxt_Native_VChangeStepExp.GetString(),"VstepExp","","string",pParas->m_pszVstep);
#endif
	stt_xml_serialize_PsuLowVolAct(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowVolTime_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("��ѹ����(���ʽ)","dvdtExp","","string",pParas->m_pszDvdt);
	pXmlSierialize->xml_serialize("��ѹ�仯��ֵ(���ʽ)","VendExp","","string",pParas->m_pszVend);
#else
	pXmlSierialize->xml_serialize(/* "����ʱ��(���ʽ)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "��ѹ����(���ʽ)" */g_sLangTxt_Native_VoltSlip.GetString(),"dvdtExp","","string",pParas->m_pszDvdt);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯��ֵ(���ʽ)" */g_sLangTxt_Native_VFinalValueExp.GetString(),"VendExp","","string",pParas->m_pszVend);
#endif

	stt_xml_serialize_PsuLowVolTime(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowVolDvDt_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("��ѹ�仯��ֵ(���ʽ)","VendExp","","string",pParas->m_pszVend);

	pXmlSierialize->xml_serialize("����仯ʼֵ(���ʽ)", "BeginValExp", "","string",pParas->m_pszDvdtStart);
	pXmlSierialize->xml_serialize("����仯��ֵ(���ʽ)", "EndValExp", "","string",pParas->m_pszDvdtEnd);
	pXmlSierialize->xml_serialize("����仯����(���ʽ)", "StepExp", "","string",pParas->m_pszDvdtStep);
#else
	pXmlSierialize->xml_serialize(/* "����ʱ��(���ʽ)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯��ֵ(���ʽ)" */g_sLangTxt_Native_VFinalValueExp.GetString(),"VendExp","","string",pParas->m_pszVend);

	pXmlSierialize->xml_serialize(/* "����仯ʼֵ(���ʽ)" */g_sLangTxt_Native_SlipInitialValueExp.GetString(), "BeginValExp", "","string",pParas->m_pszDvdtStart);
	pXmlSierialize->xml_serialize(/* "����仯��ֵ(���ʽ)" */g_sLangTxt_Native_SlipFinalValueExp.GetString(), "EndValExp", "","string",pParas->m_pszDvdtEnd);
	pXmlSierialize->xml_serialize(/* "����仯����(���ʽ)" */g_sLangTxt_Native_SlipChangeStepExp.GetString(), "StepExp", "","string",pParas->m_pszDvdtStep);
#endif

	stt_xml_serialize_PsuLowVolDvDt(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowVolILock_ex( tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize )
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹ����(���ʽ)","dvdtExp","","string",pParas->m_pszDvdt);
	pXmlSierialize->xml_serialize("��ѹ�仯��ֵ(���ʽ)","VendExp","","string",pParas->m_pszVend);
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("�����仯ʼֵ(���ʽ)", "BeginValExp", "","string",pParas->m_pszIStart);
	pXmlSierialize->xml_serialize("�����仯��ֵ(���ʽ)", "EndValExp", "","string",pParas->m_pszIEnd);
	pXmlSierialize->xml_serialize("�����仯����(���ʽ)", "StepExp", "","string",pParas->m_pszIStep);
#else
	pXmlSierialize->xml_serialize(/* "��ѹ����(���ʽ)" */g_sLangTxt_Native_VoltSlip.GetString(),"dvdtExp","","string",pParas->m_pszDvdt);
	pXmlSierialize->xml_serialize(/* "��ѹ�仯��ֵ(���ʽ)" */g_sLangTxt_Native_VFinalValueExp.GetString(),"VendExp","","string",pParas->m_pszVend);
	pXmlSierialize->xml_serialize(/* "����ʱ��(���ʽ)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "�����仯ʼֵ(���ʽ)" */g_sLangTxt_Native_IInitialValueExp.GetString(), "BeginValExp", "","string",pParas->m_pszIStart);
	pXmlSierialize->xml_serialize(/* "�����仯��ֵ(���ʽ)" */g_sLangTxt_Native_IFinalValueExp.GetString(), "EndValExp", "","string",pParas->m_pszIEnd);
	pXmlSierialize->xml_serialize(/* "�����仯����(���ʽ)" */g_sLangTxt_Native_IChangeStepExp.GetString(), "StepExp", "","string",pParas->m_pszIStep);
#endif
	stt_xml_serialize_PsuLowVolILock(pParas,pXmlSierialize);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_PsuLowVolAct(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹ���ض���ֵ","TripVol","V","number",pResults->m_fLowUAct);
	pXmlSierialize->xml_serialize("��ѹ��������", "ActVol", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "��ѹ���ض���ֵ" */g_sLangTxt_Native_LowVoltUnderloadTripSet.GetString(),"TripVol","V","number",pResults->m_fLowUAct);
	pXmlSierialize->xml_serialize(/* "��ѹ��������" */g_sLangTxt_Native_LowVActionDesc.GetString(), "ActVol", "", "number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_PsuLowVolTime(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹ���ض���ʱ��","TTripLv","s","number",pResults->m_fLowUActTime);
	pXmlSierialize->xml_serialize("��������", "ActLv", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "��ѹ���ض���ʱ��" */g_sLangTxt_Native_LowVoltUnderloadTripSet.GetString(),"TTripLv","s","number",pResults->m_fLowUActTime);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActLv", "", "number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_PsuLowVolDvDt(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹ�����ֵ", "TripDvdt", "V/s", "number",pResults->m_fDvdtAct);
	pXmlSierialize->xml_serialize("��������", "ActDvdt", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "��ѹ�����ֵ" */g_sLangTxt_Native_VoltSlipAct.GetString(), "TripDvdt", "V/s", "number",pResults->m_fDvdtAct);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActDvdt", "", "number",pResults->m_nAct);
#endif

}
void stt_xml_serialize_PsuLowVolILock( tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize )
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�͵�������ֵ����", "TripILock", "A", "number",pResults->m_fIAct);
	pXmlSierialize->xml_serialize("��������", "ActILock", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize( "�͵�������ֵ����" , "TripILock", "A", "number",pResults->m_fIAct);
	pXmlSierialize->xml_serialize( "��������" , "ActILock", "", "number",pResults->m_nAct);
#endif
}
void stt_xml_serialize_PnvLowVolAct(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("��ѹ���ض���ֵ","TripVol","V","number",pResults->m_fLowUAct);
    pXmlSierialize->xml_serialize("��ѹ��������", "ActVol", "", "number",pResults->m_nAct);
    pXmlSierialize->xml_serialize("����ж�","RsltJdg","","number",pResults->m_nAct);
    pXmlSierialize->xml_serialize("�������","RsltDsc","","number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "��ѹ���ض���ֵ" */g_sLangTxt_Native_LowVoltUnderloadTripSet.GetString(),"TripVol","V","number",pResults->m_fLowUAct);
    pXmlSierialize->xml_serialize(/* "��ѹ��������" */g_sLangTxt_Native_LowVActionDesc.GetString(), "ActVol", "", "number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_PnvLowVolTime(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("��ѹ���ض���ʱ��","TTripLv","s","number",pResults->m_fLowUActTime);
    pXmlSierialize->xml_serialize("��������", "ActLv", "", "number",pResults->m_nAct);
    pXmlSierialize->xml_serialize("����ж�","RsltJdg","","number",pResults->m_nAct);
    pXmlSierialize->xml_serialize("�������","RsltDsc","","number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "��ѹ���ض���ʱ��" */g_sLangTxt_Native_LowVoltUnderloadTripSet.GetString(),"TTripLv","s","number",pResults->m_fLowUActTime);
    pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActLv", "", "number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_PnvLowVolDvDt(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("����ֵ", "TripDvdt", "V/s", "number",pResults->m_fDvdtAct);
    pXmlSierialize->xml_serialize("��������", "ActDfdt", "", "number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "��ѹ�����ֵ" */g_sLangTxt_Native_VoltSlipAct.GetString(), "TripDvdt", "V/s", "number",pResults->m_fDvdtAct);
    pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActDvdt", "", "number",pResults->m_nAct);
#endif

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttXmlSerializeBase* stt_xml_serialize(tmt_LowVolTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolAct) == 0)
		{
			stt_xml_serialize_PsuLowVolAct_ex(&(pTests->m_oLowVolParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolTime) == 0)
		{
			stt_xml_serialize_PsuLowVolTime_ex(&(pTests->m_oLowVolParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolDvdt) == 0)
		{
			stt_xml_serialize_PsuLowVolDvDt_ex(&(pTests->m_oLowVolParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolILock) == 0)
		{
			stt_xml_serialize_PsuLowVolILock_ex(&(pTests->m_oLowVolParas), pXmlParas);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolAct) == 0)
		{
			stt_xml_serialize_PsuLowVolAct(&pTests->m_oLowVolResults, pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolTime) == 0)
		{
			stt_xml_serialize_PsuLowVolTime(&pTests->m_oLowVolResults, pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolDvdt) == 0)
		{
			stt_xml_serialize_PsuLowVolDvDt(&(pTests->m_oLowVolResults), pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolILock) == 0)
		{
			stt_xml_serialize_PsuLowVolILock(&(pTests->m_oLowVolResults), pXmlResults);
		}
	}

	return pXmlParas;
}
CSttXmlSerializeBase* stt_xml_serialize(tmt_PnvLowVolTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowVolAct) == 0)
        {
            stt_xml_serialize_PnvLowVolAct(&(pTests->m_oLowVolParas), pXmlParas);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowVolTime) == 0)
        {
            stt_xml_serialize_PnvLowVolTime(&(pTests->m_oLowVolParas), pXmlParas);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowVolDvdt) == 0)
        {
            stt_xml_serialize_PnvLowVolDvDt(&(pTests->m_oLowVolParas), pXmlParas);
        }
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowVolAct) == 0)
        {
            stt_xml_serialize_PnvLowVolAct(&pTests->m_oLowVolResults, pXmlResults);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowVolTime) == 0)
        {
            stt_xml_serialize_PnvLowVolTime(&pTests->m_oLowVolResults, pXmlResults);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowVolDvdt) == 0)
        {
            stt_xml_serialize_PnvLowVolDvDt(&(pTests->m_oLowVolResults), pXmlParas);
        }
    }

    return pXmlParas;
}
