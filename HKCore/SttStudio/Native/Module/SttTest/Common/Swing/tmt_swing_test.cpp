#include "stdafx.h"
#include "tmt_swing_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_SwingParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_SwingParas));
	pParas->init();
}

void stt_init_results(tmt_SwingResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_SwingResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_SwingParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE

	pXmlSierialize->xml_serialize("����ʼֵ", "PAngleStart", "��", "number", pParas->m_fPowerAngleBegin);
	pXmlSierialize->xml_serialize("������ֵ", "PAngleEnd", "��", "number", pParas->m_fPowerAngleEnd);
	pXmlSierialize->xml_serialize("������", "SwingCycle", "s", "number", pParas->m_fCycle);//������
	pXmlSierialize->xml_serialize("�񵴴���", "SwingCount", "", "number", pParas->m_nSwingCount);//������
	pXmlSierialize->xml_serialize("|Em|/|En|", "EmEnRate", "", "number", pParas->m_fRate);
	pXmlSierialize->xml_serialize("��բ�����", "TripPoint", "", "PsuTripBin", pParas->m_nTripPoint);//������
	pXmlSierialize->xml_serialize("�����źŽӵ�", "TripSpeedUp", "", "PsuTripBin", pParas->m_nTripSpeedUp);//������
	pXmlSierialize->xml_serialize("�����źŽӵ�", "TripSpeedDown", "", "PsuTripBin", pParas->m_nTripSpeedDown);//������
	pXmlSierialize->xml_serialize("�Ƿ�������","bReciprocating","","BOOL",pParas->m_bReciprocating);
	pXmlSierialize->xml_serialize("�ٶȱ仯ѡ��","AccelerateSlct","","PsuAccelerateSlct",pParas->m_nAccelerate);
	pXmlSierialize->xml_serialize("�Ƿ���迹","bDzdt","","BOOL",pParas->m_bDzdt);//������
	pXmlSierialize->xml_serialize("�迹�仯��", "Dzdt", "��/s", "number", pParas->m_fDzdt);//������

	pXmlSierialize->xml_serialize("�Ƿ�ת���Թ���","_FaultTrans","","BOOL",pParas->m_bTransFault);
	pXmlSierialize->xml_serialize("��������", "FaultType1", "", "SystemFault", pParas->m_nFaultType);
	pXmlSierialize->xml_serialize("��·�迹", "Z1", "��", "number", pParas->m_fImpedance);
	pXmlSierialize->xml_serialize("��·����", "ISet1", "A", "set", pParas->m_fSCurrent);
	pXmlSierialize->xml_serialize("����ʱ��", "FaultTime", "s", "set", pParas->m_fFaultTime);//������
	pXmlSierialize->xml_serialize("���򲹳�ϵ�����㷽ʽ","K0Mode","��","ZeroCalModePnv",pParas->m_nK0CalMode);
	pXmlSierialize->xml_serialize("���򲹳�ϵ��(|K0|$KR$|Z0/Z1|)","KlKr","","set",pParas->m_fK0Amp);
	pXmlSierialize->xml_serialize("���򲹳�ϵ��(Phi(K0)$KX$Phi(Z0/Z1))","AngKx","","set",pParas->m_fK0Angle);

	pXmlSierialize->xml_serialize("��ǰʱ��","PreFaultTime","s","number",pParas->m_fPreFaultTime);//������
	pXmlSierialize->xml_serialize("CT������","CTPos","","CTPosPnv",pParas->m_nCTPoint);
	pXmlSierialize->xml_serialize("ϵͳ���迹","ImpSys","��","number",pParas->m_fImpSys);
	pXmlSierialize->xml_serialize("ϵͳ���迹��","ImpSysPh","��","number",pParas->m_fImpSysPh);
	pXmlSierialize->xml_serialize("��ѹ���迹","ImpTf","��","number",pParas->m_fImpTf);
	pXmlSierialize->xml_serialize("��ѹ���迹��","ImpTfPh","��","number",pParas->m_fImpTfPh);
	pXmlSierialize->xml_serialize("�������̬�迹","ImpTs","��","number",pParas->m_fImpTs);
	pXmlSierialize->xml_serialize("����ʱ�䶨ֵ","TimeActSetting","s","number",pParas->m_fActTimeSet);


// 	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
//  	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize,nBinExNum);
 	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);

	if (stt_xml_serialize_is_read(pXmlSierialize))//���ݴ���
	{
		pXmlSierialize->xml_serialize("����1״̬","_B01","","DOutputState",pParas->m_binOut[0].nState);
		pXmlSierialize->xml_serialize("����2״̬","_B02","","DOutputState",pParas->m_binOut[1].nState);
		pXmlSierialize->xml_serialize("����3״̬","_B03","","DOutputState",pParas->m_binOut[2].nState);
		pXmlSierialize->xml_serialize("����4״̬","_B04","","DOutputState",pParas->m_binOut[3].nState);
		pXmlSierialize->xml_serialize("����5״̬","_B05","","DOutputState",pParas->m_binOut[4].nState);
		pXmlSierialize->xml_serialize("����6״̬","_B06","","DOutputState",pParas->m_binOut[5].nState);
		pXmlSierialize->xml_serialize("����7״̬","_B07","","DOutputState",pParas->m_binOut[6].nState);
		pXmlSierialize->xml_serialize("����8״̬","_B08","","DOutputState",pParas->m_binOut[7].nState);

        stt_xml_serialize(&pParas->m_oGoosePub[0],pXmlSierialize);
	}
#else
	pXmlSierialize->xml_serialize(/* "����ʼֵ" */g_sLangTxt_Native_AngleStartPar1.GetString(), "PAngleStart", "��", "number", pParas->m_fPowerAngleBegin);
	pXmlSierialize->xml_serialize(/* "������ֵ" */g_sLangTxt_Native_AngleEndPar1.GetString(), "PAngleEnd", "��", "number", pParas->m_fPowerAngleEnd);
	pXmlSierialize->xml_serialize(/* "������" */g_sLangTxt_Native_OscilPeriod1.GetString(), "SwingCycle", "s", "number", pParas->m_fCycle);//������
	pXmlSierialize->xml_serialize(/* "�񵴴���" */g_sLangTxt_Native_OscilCount.GetString(), "SwingCount", "", "number", pParas->m_nSwingCount);//������
	pXmlSierialize->xml_serialize("|Em|/|En|", "EmEnRate", "", "number", pParas->m_fRate);
	pXmlSierialize->xml_serialize(/* "��բ�����" */g_sLangTxt_Native_TripAccessPoint.GetString(), "TripPoint", "", "PsuTripBin", pParas->m_nTripPoint);//������
	pXmlSierialize->xml_serialize(/* "�����źŽӵ�" */g_sLangTxt_Native_AccelSignalCont.GetString(), "TripSpeedUp", "", "PsuTripBin", pParas->m_nTripSpeedUp);//������
	pXmlSierialize->xml_serialize(/* "�����źŽӵ�" */g_sLangTxt_Native_DecelSignalCont.GetString(), "TripSpeedDown", "", "PsuTripBin", pParas->m_nTripSpeedDown);//������
	pXmlSierialize->xml_serialize(/* "�Ƿ�������" */g_sLangTxt_Native_ReOscillat_ornot.GetString(),"bReciprocating","","BOOL",pParas->m_bReciprocating);
	pXmlSierialize->xml_serialize(/* "�ٶȱ仯ѡ��" */g_sLangTxt_Native_SpeedChange.GetString(),"AccelerateSlct","","PsuAccelerateSlct",pParas->m_nAccelerate);
	pXmlSierialize->xml_serialize(/* "�Ƿ���迹" */g_sLangTxt_Native_ImpedanceChange_ornot.GetString(),"bDzdt","","BOOL",pParas->m_bDzdt);//������
	pXmlSierialize->xml_serialize(/* "�迹�仯��" */g_sLangTxt_Native_ImpedanceRateChange.GetString(), "Dzdt", "��/s", "number", pParas->m_fDzdt);//������

	pXmlSierialize->xml_serialize(/* "�Ƿ�ת���Թ���" */g_sLangTxt_Native_TransientFault.GetString(),"_FaultTrans","","BOOL",pParas->m_bTransFault);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType1", "", "SystemFault", pParas->m_nFaultType);
	pXmlSierialize->xml_serialize(/* "��·�迹" */g_sLangTxt_Native_ShortZImp.GetString(), "Z1", "��", "number", pParas->m_fImpedance);
	pXmlSierialize->xml_serialize(/* "��·����" */g_sLangTxt_Native_FaultCurrValue.GetString(), "ISet1", "A", "set", pParas->m_fSCurrent);
	pXmlSierialize->xml_serialize(/* "����ʱ��" */g_sLangTxt_Gradient_Time.GetString(), "FaultTime", "s", "set", pParas->m_fFaultTime);//������
	pXmlSierialize->xml_serialize(/* "���򲹳�ϵ�����㷽ʽ" */g_sLangTxt_Native_zeroseq_comp_calculat1.GetString(),"K0Mode",/* "��" */g_sLangTxt_None.GetString(),"ZeroCalModePnv",pParas->m_nK0CalMode);
	pXmlSierialize->xml_serialize(/* "���򲹳�ϵ��(|K0|$KR$|Z0/Z1|)" */g_sLangTxt_Native_ZeroSeqComp1.GetString(),"KlKr","","set",pParas->m_fK0Amp);
	pXmlSierialize->xml_serialize(/* "���򲹳�ϵ��(Phi(K0)$KX$Phi(Z0/Z1))" */g_sLangTxt_Native_ZeroSeqComp2.GetString(),"AngKx","","set",pParas->m_fK0Angle);

	pXmlSierialize->xml_serialize(/* "��ǰʱ��" */g_sLangTxt_Native_PreOscTime.GetString(),"PreFaultTime","s","number",pParas->m_fPreFaultTime);//������
	pXmlSierialize->xml_serialize(/* "CT������" */g_sLangTxt_Native_CTPolarityPositive.GetString(),"CTPos","","CTPosPnv",pParas->m_nCTPoint);
	pXmlSierialize->xml_serialize(/* "ϵͳ���迹" */g_sLangTxt_Native_SysImp.GetString(),"ImpSys","��","number",pParas->m_fImpSys);
	pXmlSierialize->xml_serialize(/* "ϵͳ���迹��" */g_sLangTxt_Native_SysImpedAngle.GetString(),"ImpSysPh","��","number",pParas->m_fImpSysPh);
	pXmlSierialize->xml_serialize(/* "��ѹ���迹" */g_sLangTxt_Native_TransImp.GetString(),"ImpTf","��","number",pParas->m_fImpTf);
	pXmlSierialize->xml_serialize(/* "��ѹ���迹��" */g_sLangTxt_Native_TransImpedAngle.GetString(),"ImpTfPh","��","number",pParas->m_fImpTfPh);
	pXmlSierialize->xml_serialize(/* "�������̬�迹" */g_sLangTxt_Native_GeneTransImped.GetString(),"ImpTs","��","number",pParas->m_fImpTs);
	pXmlSierialize->xml_serialize(/* "����ʱ�䶨ֵ" */g_sLangTxt_Native_OpTimeSet.GetString(),"TimeActSetting","s","number",pParas->m_fActTimeSet);


// 	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
//  	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize,nBinExNum);
 	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);

	if (stt_xml_serialize_is_read(pXmlSierialize))//���ݴ���
	{
		pXmlSierialize->xml_serialize(/* "����1״̬" */g_sLangTxt_Out1_Situation.GetString(),"_B01","","DOutputState",pParas->m_binOut[0].nState);
		pXmlSierialize->xml_serialize(/* "����2״̬" */g_sLangTxt_Out2_Situation.GetString(),"_B02","","DOutputState",pParas->m_binOut[1].nState);
		pXmlSierialize->xml_serialize(/* "����3״̬" */g_sLangTxt_Out3_Situation.GetString(),"_B03","","DOutputState",pParas->m_binOut[2].nState);
		pXmlSierialize->xml_serialize(/* "����4״̬" */g_sLangTxt_Out4_Situation.GetString(),"_B04","","DOutputState",pParas->m_binOut[3].nState);
		pXmlSierialize->xml_serialize(/* "����5״̬" */g_sLangTxt_Out5_Situation.GetString(),"_B05","","DOutputState",pParas->m_binOut[4].nState);
		pXmlSierialize->xml_serialize(/* "����6״̬" */g_sLangTxt_Out6_Situation.GetString(),"_B06","","DOutputState",pParas->m_binOut[5].nState);
		pXmlSierialize->xml_serialize(/* "����7״̬" */g_sLangTxt_Out7_Situation.GetString(),"_B07","","DOutputState",pParas->m_binOut[6].nState);
		pXmlSierialize->xml_serialize(/* "����8״̬" */g_sLangTxt_Out8_Situation.GetString(),"_B08","","DOutputState",pParas->m_binOut[7].nState);

        stt_xml_serialize(&pParas->m_oGoosePub[0],pXmlSierialize);
	}
#endif
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_SwingResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��������ʱ��", "TripTime", "", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("�����źų���ʱ��", "SpeedUp", "", "number",pResults->m_fSpeedUp);
	pXmlSierialize->xml_serialize("�����źų���ʱ��", "SpeedDown", "", "number",pResults->m_fSpeedDown);
	pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "��������ʱ��" */g_sLangTxt_Native_ProtRelayTime1.GetString(), "TripTime", "", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize(/* "�����źų���ʱ��" */g_sLangTxt_Native_AccelSigOutTime1.GetString(), "SpeedUp", "", "number",pResults->m_fSpeedUp);
	pXmlSierialize->xml_serialize(/* "�����źų���ʱ��" */g_sLangTxt_Native_DecelSigOutTime1.GetString(), "SpeedDown", "", "number",pResults->m_fSpeedDown);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}

CSttXmlSerializeBase* stt_xml_serialize(tmt_SwingTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

 	if (pXmlParas != NULL)
 	{
		stt_xml_serialize(&(pTests->m_oSwingParas), pXmlParas);
 	}
 
 	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());
 
 	if (pXmlResults != NULL)
 	{
		stt_xml_serialize(&pTests->m_oSwingResults,  pXmlResults);
 	}

	return pXmlParas;
}
