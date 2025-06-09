#include "stdafx.h"
#include "tmt_cb_operate_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_CBOperateParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_CBOperateParas));
	pParas->init();
}

void stt_init_results(tmt_CBOperateResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_CBOperateResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_CBOperateParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("ϵͳ����ģ��(0-�������� 1-��ѹ���� 2-ϵͳ�迹����)","CalcuMode","","UIZCalMode",pParas->m_nCalMode);
	pXmlSierialize->xml_serialize("ϵͳ��Դ�迹","Zs_Mag","��","number",pParas->m_fZs);
	pXmlSierialize->xml_serialize("ϵͳ��Դ�迹��","Zs_Ang","��","number",pParas->m_fPhis);

	pXmlSierialize->xml_serialize("��������","FaultType1","","number",pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("��·����", "ISet1", "A","number",pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize("��·��ѹ", "VSet1", "V","number",pParas->m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize("��·�迹", "Z1", "V","number",pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize("��·�迹��", "Z1Ph", "��","number",pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize("���Ϸ���", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("��������","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);

	pXmlSierialize->xml_serialize("������ʱ��", "TSet1", "s","number",pParas->m_fMaxFaultTime);
//	pXmlSierialize->xml_serialize("��������ʱ", "TAfterTrig1", "s","number",pParas->m_fTAfterTrig[0]);

	pXmlSierialize->xml_serialize("�Ƿ�ת���Թ���","_FaultTrans","","BOOL",pParas->m_bTransFault);
	pXmlSierialize->xml_serialize("����ת��ʱ��", "FaultTransT", "s", "number",  pParas->m_fTransTime);

	pXmlSierialize->xml_serialize("ת����������","FaultType2","","number",pParas->m_nFaultType[1]);
	pXmlSierialize->xml_serialize("ת�����϶�·�迹", "Z2", "V","number",pParas->m_fImpedance[1]);
	pXmlSierialize->xml_serialize("ת�����϶�·�迹��", "Z2Ph", "��","number",pParas->m_fImpAngle[1]);
	pXmlSierialize->xml_serialize("ת�����϶�·����", "ISet2", "A","number",pParas->m_fSCCurrent[1]);
	pXmlSierialize->xml_serialize("ת�����϶�·��ѹ", "VSet2", "V","number",pParas->m_fSCVoltage[1]);
	pXmlSierialize->xml_serialize("ת�����Ϲ��Ϸ���", "FaultDirection2", "", "FaultDirection", pParas->m_nFaultDir[1]);

	pXmlSierialize->xml_serialize("����ʱ������ж�","Ttrip_Check","","long",pParas->m_nTtripCheck);
	pXmlSierialize->xml_serialize("�غ�բ����ʱ������ж�", "TtripD_Check", "","long",pParas->m_nTtripDCheck);
	pXmlSierialize->xml_serialize("����ٶ���ʱ������ж�", "TtripAcc_Check", "","long",pParas->m_nTtripAccCheck);
	pXmlSierialize->xml_serialize("����ʱ����������(s)","Ttrip_AbsErr","","number",pParas->m_fTtripAbsErr);
	pXmlSierialize->xml_serialize("����ʱ����������(%)", "Ttrip_RelErr", "","number",pParas->m_fTtripRelErr);
	pXmlSierialize->xml_serialize("����ʱ������ֵ(s)", "TSetting", "","number",pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("�غ�բ����ʱ����������(s)", "TtripD_AbsErr", "","number",pParas->m_fTtripDAbsErr);
	pXmlSierialize->xml_serialize("�غ�բ����ʱ����������(%)", "TtripD_RelErr", "","number",pParas->m_fTtripDRelErr);
	pXmlSierialize->xml_serialize("�غ�բ����ʱ������ֵ(s)", "DTSetting", "", "number", pParas->m_fDTSetting);
	pXmlSierialize->xml_serialize("����ٶ���ʱ����������(s)", "TtripAcc_AbsErr", "","number",pParas->m_fTtripAccAbsErr);
	pXmlSierialize->xml_serialize("����ٶ���ʱ����������(%)", "TtripAcc_RelErr", "","number",pParas->m_fTtripAccRelErr);
	pXmlSierialize->xml_serialize("����ٶ���ʱ������ֵ(s)", "AccTSetting", "", "number", pParas->m_fAccTSetting);
	pXmlSierialize->xml_serialize("����ʱ������߼��ж�","Ttrip_ErrorLogic","","long",pParas->m_nTtripErrorLogic);
	pXmlSierialize->xml_serialize("�غ�բ����ʱ������߼��ж�", "TtripD_ErrorLogic", "","long",pParas->m_nTtripDErrorLogic);
	pXmlSierialize->xml_serialize("����ٶ���ʱ������߼��ж�", "TtripAcc_ErrorLogic", "","long",pParas->m_nTtripAccErrorLogic);

	pXmlSierialize->xml_serialize("�������","TestProcess","","PsuTestProcCtrl",pParas->m_nTestProcCtrlMode);
	// ���²�����m_nTestProcCtrlMode==ʱ�����ʱ��Ч
	pXmlSierialize->xml_serialize("�غϷ�ʽ","RecloseMode","","PsuRecloseMode",pParas->m_nRecloseMode);
//	pXmlSierialize->xml_serialize("�������������ʱ��","AfterRecloseTime","s","number",pParas->m_fTAfterReclose);
	pXmlSierialize->xml_serialize("�غϳ���ʱ��","RecloseTime","s","set",pParas->m_fRecloseTime);
	pXmlSierialize->xml_serialize("�������������ʱ��","TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
	pXmlSierialize->xml_serialize("����ٿ������������ʱ��", "TAfterAccTrig", "s","number",pParas->m_fTAfterAccTrig);

	if(stt_xml_serialize_is_read(pXmlSierialize))//20230505 ��ȡ�����ݴ���PsuVm
	{
		pXmlSierialize->xml_serialize("ϵͳ����ģ��(0-�������� 1-��ѹ���� 2-ϵͳ�迹����)","CalMode","","UIZCalMode",pParas->m_nCalMode);
		pXmlSierialize->xml_serialize("����ٿ������������ʱ��", "AfterAccTime", "s","number",pParas->m_fTAfterAccTrig);
		pXmlSierialize->xml_serialize("���ѹ","Unom","V","number",pParas->m_fUnom);

		pXmlSierialize->xml_serialize("ϵͳ��Դ�迹","Zs","��","number",pParas->m_fZs);
		pXmlSierialize->xml_serialize("ϵͳ��Դ�迹��","ZsPh","��","number",pParas->m_fPhis);
	}
#else
	pXmlSierialize->xml_serialize(/* "ϵͳ����ģ��(0-�������� 1-��ѹ���� 2-ϵͳ�迹����)" */g_sLangTxt_Native_syscomputModel012.GetString(),"CalcuMode","","UIZCalMode",pParas->m_nCalMode);
	pXmlSierialize->xml_serialize(/* "ϵͳ��Դ�迹" */g_sLangTxt_Native_syspowerImp.GetString(),"Zs_Mag","��","number",pParas->m_fZs);
	pXmlSierialize->xml_serialize(/* "ϵͳ��Դ�迹��" */g_sLangTxt_Native_syspowerImpangle.GetString(),"Zs_Ang","��","number",pParas->m_fPhis);


	pXmlSierialize->xml_serialize("����ʱ������ж�","Ttrip_Check","","long",pParas->m_nTtripCheck);
	pXmlSierialize->xml_serialize("�غ�բ����ʱ������ж�", "TtripD_Check", "","long",pParas->m_nTtripDCheck);
	pXmlSierialize->xml_serialize("����ٶ���ʱ������ж�", "TtripAcc_Check", "","long",pParas->m_nTtripAccCheck);
	pXmlSierialize->xml_serialize("����ʱ����������(s)","Ttrip_AbsErr","","number",pParas->m_fTtripAbsErr);
	pXmlSierialize->xml_serialize("����ʱ����������(%)", "Ttrip_RelErr", "","number",pParas->m_fTtripRelErr);
	pXmlSierialize->xml_serialize("����ʱ������ֵ(s)", "TSetting", "","number",pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("�غ�բ����ʱ����������(s)", "TtripD_AbsErr", "","number",pParas->m_fTtripDAbsErr);
	pXmlSierialize->xml_serialize("�غ�բ����ʱ����������(%)", "TtripD_RelErr", "","number",pParas->m_fTtripDRelErr);
	pXmlSierialize->xml_serialize("�غ�բ����ʱ������ֵ(s)", "DTSetting", "", "number", pParas->m_fDTSetting);
	pXmlSierialize->xml_serialize("����ٶ���ʱ����������(s)", "TtripAcc_AbsErr", "","number",pParas->m_fTtripAccAbsErr);
	pXmlSierialize->xml_serialize("����ٶ���ʱ����������(%)", "TtripAcc_RelErr", "","number",pParas->m_fTtripAccRelErr);
	pXmlSierialize->xml_serialize("����ٶ���ʱ������ֵ(s)", "AccTSetting", "", "number", pParas->m_fAccTSetting);
	pXmlSierialize->xml_serialize("����ʱ������߼��ж�","Ttrip_ErrorLogic","","long",pParas->m_nTtripErrorLogic);
	pXmlSierialize->xml_serialize("�غ�բ����ʱ������߼��ж�", "TtripD_ErrorLogic", "","long",pParas->m_nTtripDErrorLogic);
	pXmlSierialize->xml_serialize("����ٶ���ʱ������߼��ж�", "TtripAcc_ErrorLogic", "","long",pParas->m_nTtripAccErrorLogic);

	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Gradient_FailType.GetString(),"FaultType1","","number",pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "��·����" */g_sLangTxt_Native_ShortCircuit.GetString(), "ISet1", "A","number",pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize(/* "��·��ѹ" */g_sLangTxt_Native_ShortCircuitV.GetString(), "VSet1", "V","number",pParas->m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize(/* "��·�迹" */g_sLangTxt_Native_ShortZImp.GetString(), "Z1", "V","number",pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize(/* "��·�迹��" */g_sLangTxt_Native_ShortZImpAng.GetString(), "Z1Ph", "��","number",pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize(/* "���Ϸ���" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_NatureMalf.GetString(),"FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);

	pXmlSierialize->xml_serialize(/* "������ʱ��" */g_sLangTxt_Native_MaxTimeMalf.GetString(), "TSet1", "s","number",pParas->m_fMaxFaultTime);
	//	pXmlSierialize->xml_serialize("��������ʱ", "TAfterTrig1", "s","number",pParas->m_fTAfterTrig[0]);

	pXmlSierialize->xml_serialize(/* "�Ƿ�ת���Թ���" */g_sLangTxt_Native_TransientFault.GetString(),"_FaultTrans","","BOOL",pParas->m_bTransFault);
	pXmlSierialize->xml_serialize(/* "����ת��ʱ��" */g_sLangTxt_Native_fault_switchtime.GetString(), "FaultTransT", "s", "number",  pParas->m_fTransTime);

	pXmlSierialize->xml_serialize(/* "ת����������" */g_sLangTxt_Native_switchErrtype.GetString(),"FaultType2","","number",pParas->m_nFaultType[1]);
	pXmlSierialize->xml_serialize(/* "ת�����϶�·�迹" */g_sLangTxt_Native_switchErr_shortImp.GetString(), "Z2", "V","number",pParas->m_fImpedance[1]);
	pXmlSierialize->xml_serialize(/* "ת�����϶�·�迹��" */g_sLangTxt_Native_switchErr_shortImpAng.GetString(), "Z2Ph", "��","number",pParas->m_fImpAngle[1]);
	pXmlSierialize->xml_serialize(/* "ת�����϶�·����" */g_sLangTxt_Native_switchErr_shortI.GetString(), "ISet2", "A","number",pParas->m_fSCCurrent[1]);
	pXmlSierialize->xml_serialize(/* "ת�����϶�·��ѹ" */g_sLangTxt_Native_switchErr_shortV.GetString(), "VSet2", "V","number",pParas->m_fSCVoltage[1]);
	pXmlSierialize->xml_serialize(/* "ת�����Ϲ��Ϸ���" */g_sLangTxt_Native_switchErr_direction.GetString(), "FaultDirection2", "", "FaultDirection", pParas->m_nFaultDir[1]);

	pXmlSierialize->xml_serialize(/* "�������" */g_sLangTxt_Native_test_process.GetString(),"TestProcess","","PsuTestProcCtrl",pParas->m_nTestProcCtrlMode);
	// ���²�����m_nTestProcCtrlMode==ʱ�����ʱ��Ч
	pXmlSierialize->xml_serialize(/* "�غϷ�ʽ" */g_sLangTxt_Native_redundancy_mode.GetString(),"RecloseMode","","PsuRecloseMode",pParas->m_nRecloseMode);
	//	pXmlSierialize->xml_serialize("�������������ʱ��","AfterRecloseTime","s","number",pParas->m_fTAfterReclose);
	pXmlSierialize->xml_serialize(/* "�غϳ���ʱ��" */g_sLangTxt_Native_redundancy_duration.GetString(),"RecloseTime","s","set",pParas->m_fRecloseTime);
	pXmlSierialize->xml_serialize(/* "�������������ʱ��" */g_sLangTxt_Native_DurProtTrip.GetString(),"TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
	pXmlSierialize->xml_serialize(/* "����ٿ������������ʱ��" */g_sLangTxt_Native_postswitch_duration.GetString(), "TAfterAccTrig", "s","number",pParas->m_fTAfterAccTrig);

	if(stt_xml_serialize_is_read(pXmlSierialize))//20230505 ��ȡ�����ݴ���PsuVm
	{
		pXmlSierialize->xml_serialize(/* "ϵͳ����ģ��(0-�������� 1-��ѹ���� 2-ϵͳ�迹����)" */g_sLangTxt_Native_syscomputModel012.GetString(),"CalMode","","UIZCalMode",pParas->m_nCalMode);
		pXmlSierialize->xml_serialize(/* "����ٿ������������ʱ��" */g_sLangTxt_Native_postswitch_duration.GetString(), "AfterAccTime", "s","number",pParas->m_fTAfterAccTrig);
		pXmlSierialize->xml_serialize(/* "���ѹ" */g_sLangTxt_Report_Vnom.GetString(),"Unom","V","number",pParas->m_fUnom);

		pXmlSierialize->xml_serialize(/* "ϵͳ��Դ�迹" */g_sLangTxt_Native_syspowerImp.GetString(),"Zs","��","number",pParas->m_fZs);
		pXmlSierialize->xml_serialize(/* "ϵͳ��Դ�迹��" */g_sLangTxt_Native_syspowerImpangle.GetString(),"ZsPh","��","number",pParas->m_fPhis);
	}
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,true);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_CBOperateResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_CBOperateTest *pTests, CSttXmlSerializeBase *pXmlSerialize, long nVolRsNum, long nCurRsNum)
{
	//stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);//mym 2021-7-26 zhuxiao��;��Ϊǰ���Ѿ����л����ˣ���������ע����;

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize(&(pTests->m_oCBOperateParas),  pXmlParas);	//�ļ��Ķ�д
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize(&(pTests->m_oCBOperateParas),  pXmlParas);	//���Բ����·�
		}
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize(&pTests->m_oCBOperateResults,  pXmlResults);
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize(&pTests->m_oCBOperateResults,  pXmlResults);
		}
	}

	return pXmlParas;
}
