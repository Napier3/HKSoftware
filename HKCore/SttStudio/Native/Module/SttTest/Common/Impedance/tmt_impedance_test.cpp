#include "stdafx.h"
#include "tmt_impedance_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

#ifndef _STT_NOT_IN_TEST_SERVER_
#include "../SttSystemConfig.h"
#endif

void stt_xml_serialize_impedance_paras(tmt_ImpedanceParas *pParas, CSttXmlSerializeBase *pXmlSierialize,BOOL bImpBase)
{
#ifndef _STT_NOT_IN_TEST_SERVER_
	pXmlSierialize->xml_serialize("0-����Ŀ��뿪����1-����+��չ�Ŀ��뿪��","BinBoutMode","","long",g_theSystemConfig->m_nBinBoutMode);
#endif

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��ԣ��","FaultTime","s","number",pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("����ǰʱ��","PreFaultTime","s","number",pParas->m_fPreFaultTime);

	pXmlSierialize->xml_serialize("���ϴ�����ʽ","FaultTrigMode","","FaultTrigModePnv",pParas->m_nFaultTrigMode);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣�ʱ��", "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣��֣�", "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣��룩", "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);

	pXmlSierialize->xml_serialize("���򲹳�ϵ����﷽ʽ","K0Mode","��","ZeroCalMode",pParas->m_nK0CalMode);
	pXmlSierialize->xml_serialize("���򲹳�ϵ��RE/RL","KlKr","","number",pParas->m_fK0Amp);
	pXmlSierialize->xml_serialize("���򲹳�ϵ��XE/XL","AngKx","","number",pParas->m_fK0Angle);

	pXmlSierialize->xml_serialize("���ɵ���", "ILoad", "A", "number",pParas->m_fIfh);
	pXmlSierialize->xml_serialize("���ɹ���", "ILoadPh", "��", "number",pParas->m_fPowerAngle);

	pXmlSierialize->xml_serialize("PT��װλ��","PTPos","","PTPosition",pParas->m_nPTPoint);
	pXmlSierialize->xml_serialize("CT������","CTPos","","CTPos",pParas->m_nCTPoint);
	pXmlSierialize->xml_serialize("�Ƿ�ģ���·����ʱ","SimulateBreakerDelay","s","number",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize("��·����բ��ʱ","BrkBreakTime","s","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize("��·����բ��ʱ","BrkCloseTime","s","number",pParas->m_fCBCloseTime);

	pXmlSierialize->xml_serialize("�Ƿ���ӷ����ڷ���","FaultId","s","BOOL",pParas->m_bIPlusDC);
//	pXmlSierialize->xml_serialize("˥��ʱ�䳣��", "Tao","s","number",pParas->m_fTao);
	pXmlSierialize->xml_serialize("��բ�Ƿ�ʽ( 0-��� 1-��ֵ)", "FaultAngMode", "", "FaultAngModePnv",pParas->m_nFaultIncMode);
	pXmlSierialize->xml_serialize("��բ��", "FaultAng", "��", "number", pParas->m_fFaultAngle);
//	pXmlSierialize->xml_serialize("��բ�ǵ���ʼֵ", "FaultAng_0", "��", "number", pParas->m_fFaultAng_0);


	if (bImpBase)
	{
		pXmlSierialize->xml_serialize("Vz�������", "VzDefine", "", "PsuVzDefine", pParas->m_nVzDefine);	
		pXmlSierialize->xml_serialize("Vz�ο���", "VzPhDefine", "", "PsuVzRefPhase", pParas->m_nVzPhDefine);	
		pXmlSierialize->xml_serialize("Vz���", "VzPh", "��", "number", pParas->m_fUxInput_Ang);	
	}
	else
	{
		pXmlSierialize->xml_serialize("�غ�բʱ�䶨ֵ","RecloseTime","s","set",pParas->m_fRecloseTime);
		pXmlSierialize->xml_serialize("�����ʱ�䶨ֵ","AfterAcceTime","s","set",pParas->m_fAfterAcceTime);
		pXmlSierialize->xml_serialize("������ѹUx �����ʽ", "UxMode", "", "UxMode", pParas->m_nVzDefine);	
		pXmlSierialize->xml_serialize("ͬ�ڵ�ѹ��ֵ(��ͬ�ڷ�ʽ��Ч)","UxInputMag","V","number",pParas->m_fUxInput_Mag);
		pXmlSierialize->xml_serialize("ͬ�ڵ�ѹ��λ(��ͬ�ڷ�ʽ��Ч)","UxInputAng","��","number",pParas->m_fUxInput_Ang);
		pXmlSierialize->xml_serialize("��ѹ����ֵ","UxHigh","V","number",pParas->m_fUxHigh);
		pXmlSierialize->xml_serialize("��ѹ����ֵ","UxLow","V","number",pParas->m_fUxLow);
	}

	pXmlSierialize->xml_serialize("������ת���Ʒ�ʽ", "_OutputSwitchMode", " ", "OutputSwitchMode", pParas->m_nOutputSwitchMode);
	pXmlSierialize->xml_serialize("������ת��ʱ", "_OutputDelayTime", "s", "number", pParas->m_fBoutTimeTrig);
	pXmlSierialize->xml_serialize("��������ʱ��","_OutputKeepTime","s","number",pParas->m_fBoutHoldTime);
	pXmlSierialize->xml_serialize("��̬����1״̬","_B01","","DOutputState",pParas->m_nStateBOut[0]);
	pXmlSierialize->xml_serialize("��̬����2״̬","_B02","","DOutputState",pParas->m_nStateBOut[1]);
	pXmlSierialize->xml_serialize("��̬����3״̬","_B03","","DOutputState",pParas->m_nStateBOut[2]);
	pXmlSierialize->xml_serialize("��̬����4״̬","_B04","","DOutputState",pParas->m_nStateBOut[3]);
	pXmlSierialize->xml_serialize("��̬����5״̬","_B05","","DOutputState",pParas->m_nStateBOut[4]);
	pXmlSierialize->xml_serialize("��̬����6״̬","_B06","","DOutputState",pParas->m_nStateBOut[5]);
	pXmlSierialize->xml_serialize("��̬����7״̬","_B07","","DOutputState",pParas->m_nStateBOut[6]);
	pXmlSierialize->xml_serialize("��̬����8״̬","_B08","","DOutputState",pParas->m_nStateBOut[7]);

	pXmlSierialize->xml_serialize("����A","A","","DInputState",pParas->m_nDInputState[0]);
	pXmlSierialize->xml_serialize("����B","B","","DInputState",pParas->m_nDInputState[1]);
	pXmlSierialize->xml_serialize("����C","C","","DInputState",pParas->m_nDInputState[2]);
	pXmlSierialize->xml_serialize("����R","R","","DInputState",pParas->m_nDInputState[3]);
	pXmlSierialize->xml_serialize("����E","E","","DInputState",pParas->m_nDInputState[4]);
	pXmlSierialize->xml_serialize("����F","F","","DInputState",pParas->m_nDInputState[5]);
	pXmlSierialize->xml_serialize("����G","G","","DInputState",pParas->m_nDInputState[6]);
	pXmlSierialize->xml_serialize("����H","H","","DInputState",pParas->m_nDInputState[7]);
	pXmlSierialize->xml_serialize("������ѡ��","BinSelect","","BinSelect",pParas->m_nBinSelect);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		//������ǰ�ӿڳ�����
		pXmlSierialize->xml_serialize("GPS����ʱ�̣�ʱ��", "GpsH"," ","number",pParas->m_tGps.nHour);
		pXmlSierialize->xml_serialize("GPS����ʱ�̣��֣�", "GpsM"," ","number",pParas->m_tGps.nMinutes);
		pXmlSierialize->xml_serialize("GPS����ʱ�̣��룩", "GpsS"," ","number",pParas->m_tGps.nSeconds);

		pXmlSierialize->xml_serialize("��բ�Ƿ�ʽ( 0-��� 1-��ֵ)", "FaultIncMode", "", "FaultAngModePnv",pParas->m_nFaultIncMode);
		pXmlSierialize->xml_serialize("�Ƿ���ӷ����ڷ���","bIPlusDC","","BOOL",pParas->m_bIPlusDC);

		pXmlSierialize->xml_serialize("����A","_BinAMode","","DInputState",pParas->m_nDInputState[0]);
		pXmlSierialize->xml_serialize("����B","_BinBMode","","DInputState",pParas->m_nDInputState[1]);
		pXmlSierialize->xml_serialize("����C","_BinCMode","","DInputState",pParas->m_nDInputState[2]);
		pXmlSierialize->xml_serialize("����R","_BinDMode","","DInputState",pParas->m_nDInputState[3]);
		pXmlSierialize->xml_serialize("����E","_BinEMode","","DInputState",pParas->m_nDInputState[4]);
		pXmlSierialize->xml_serialize("����F","_BinFMode","","DInputState",pParas->m_nDInputState[5]);
		pXmlSierialize->xml_serialize("����G","_BinGMode","","DInputState",pParas->m_nDInputState[6]);
		pXmlSierialize->xml_serialize("����H","_BinHMode","","DInputState",pParas->m_nDInputState[7]);

        //Pnv�������ݴ���
        pXmlSierialize->xml_serialize("�غ�բʱ�䶨ֵ","RecloseTime","s","set",pParas->m_fRecloseTime);
        pXmlSierialize->xml_serialize("�����ʱ�䶨ֵ","AfterAcceTime","s","set",pParas->m_fAfterAcceTime);
        pXmlSierialize->xml_serialize("������ѹUx �����ʽ", "UxMode", "", "UxMode", pParas->m_nVzDefine);
        pXmlSierialize->xml_serialize("ͬ�ڵ�ѹ��ֵ(��ͬ�ڷ�ʽ��Ч)","UxInputMag","V","number",pParas->m_fUxInput_Mag);
        pXmlSierialize->xml_serialize("ͬ�ڵ�ѹ��λ(��ͬ�ڷ�ʽ��Ч)","UxInputAng","��","number",pParas->m_fUxInput_Ang);
        pXmlSierialize->xml_serialize("��ѹ����ֵ","UxHigh","V","number",pParas->m_fUxHigh);
        pXmlSierialize->xml_serialize("��ѹ����ֵ","UxLow","V","number",pParas->m_fUxLow);
        pXmlSierialize->xml_serialize("��բ��ѡ��( 0-��� 1-��ֵ)", "FaultIncMode", "", "FaultAngModePnv",pParas->m_nFaultIncMode);
        pXmlSierialize->xml_serialize("����Aʹ��","BinA","","DInputState",pParas->m_nDInputState[0]);
        pXmlSierialize->xml_serialize("����Bʹ��","BinB","","DInputState",pParas->m_nDInputState[1]);
        pXmlSierialize->xml_serialize("����Cʹ��","BinC","","DInputState",pParas->m_nDInputState[2]);
        pXmlSierialize->xml_serialize("����Rʹ��","BinR","","DInputState",pParas->m_nDInputState[3]);
        pXmlSierialize->xml_serialize("����Eʹ��","BinE","","DInputState",pParas->m_nDInputState[4]);
        pXmlSierialize->xml_serialize("����Fʹ��","BinF","","DInputState",pParas->m_nDInputState[5]);
        pXmlSierialize->xml_serialize("����Gʹ��","BinG","","DInputState",pParas->m_nDInputState[6]);
        pXmlSierialize->xml_serialize("����Hʹ��","BinH","","DInputState",pParas->m_nDInputState[7]);
        pXmlSierialize->xml_serialize("������ѡ��","AndOr","","BinSelect",pParas->m_nBinSelect);
	}
#else
	pXmlSierialize->xml_serialize(/* "����ʱ��ԣ��" */g_sLangTxt_Native_FaultTimeMargin.GetString(),"FaultTime","s","number",pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize(/* "����ǰʱ��" */g_sLangTxt_Native_PreFautTime.GetString(),"PreFaultTime","s","number",pParas->m_fPreFaultTime);

	pXmlSierialize->xml_serialize(/* "���ϴ�����ʽ" */g_sLangTxt_Native_FaultTrigMethod.GetString(),"FaultTrigMode","","FaultTrigModePnv",pParas->m_nFaultTrigMode);
	pXmlSierialize->xml_serialize(/* "GPS����ʱ�̣�ʱ��" */g_sLangTxt_Native_GPSTriggerHour.GetString(), "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize(/* "GPS����ʱ�̣��֣�" */g_sLangTxt_Native_GPSTriggerMinute.GetString(), "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize(/* "GPS����ʱ�̣��룩" */g_sLangTxt_Native_GPSTriggerSecond.GetString(), "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);

	pXmlSierialize->xml_serialize(/* "���򲹳�ϵ����﷽ʽ" */g_sLangTxt_Native_ZeroSeqCompExp.GetString(),"K0Mode",/* "��" */g_sLangTxt_without.GetString(),"ZeroCalMode",pParas->m_nK0CalMode);
	pXmlSierialize->xml_serialize(/* "���򲹳�ϵ��RE/RL" */g_sLangTxt_Native_ZeroSeqComp_RERL.GetString(),"KlKr","","number",pParas->m_fK0Amp);
	pXmlSierialize->xml_serialize(/* "���򲹳�ϵ��XE/XL" */g_sLangTxt_Native_ZeroSeqComp_XEXL.GetString(),"AngKx","","number",pParas->m_fK0Angle);

	pXmlSierialize->xml_serialize(/* "���ɵ���" */g_sLangTxt_Native_load_current.GetString(), "ILoad", "A", "number",pParas->m_fIfh);
	pXmlSierialize->xml_serialize(/* "���ɹ���" */g_sLangTxt_Native_loadpowerAng.GetString(), "ILoadPh", "��", "number",pParas->m_fPowerAngle);

	pXmlSierialize->xml_serialize(/* "PT��װλ��" */g_sLangTxt_Native_PT_installPos.GetString(),"PTPos","","PTPosition",pParas->m_nPTPoint);
	pXmlSierialize->xml_serialize(/* "CT������" */g_sLangTxt_Native_CTPolarityPositive.GetString(),"CTPos","","CTPos",pParas->m_nCTPoint);
	pXmlSierialize->xml_serialize(/* "�Ƿ�ģ���·����ʱ" */g_sLangTxt_Native_SimBrkDel.GetString(),"SimulateBreakerDelay","s","number",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize(/* "��·����բ��ʱ" */g_sLangTxt_Native_BrkTripDel.GetString(),"BrkBreakTime","s","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize(/* "��·����բ��ʱ" */g_sLangTxt_Native_BrkClsDel.GetString(),"BrkCloseTime","s","number",pParas->m_fCBCloseTime);

	pXmlSierialize->xml_serialize(/* "�Ƿ���ӷ����ڷ���" */g_sLangTxt_Native_superimpose_ornot.GetString(),"FaultId","s","BOOL",pParas->m_bIPlusDC);
	//	pXmlSierialize->xml_serialize("˥��ʱ�䳣��", "Tao","s","number",pParas->m_fTao);
	pXmlSierialize->xml_serialize(/* "��բ�Ƿ�ʽ( 0-��� 1-��ֵ)" */g_sLangTxt_Native_closeAngmode01.GetString(), "FaultAngMode", "", "FaultAngModePnv",pParas->m_nFaultIncMode);
	pXmlSierialize->xml_serialize(/* "��բ��" */g_sLangTxt_Native_closing_angle.GetString(), "FaultAng", "��", "number", pParas->m_fFaultAngle);
	//	pXmlSierialize->xml_serialize("��բ�ǵ���ʼֵ", "FaultAng_0", "��", "number", pParas->m_fFaultAng_0);


	if (bImpBase)
	{
		pXmlSierialize->xml_serialize(/* "Vz�������" */g_sLangTxt_Native_Vz_outputDef.GetString(), "VzDefine", "", "PsuVzDefine", pParas->m_nVzDefine);	
		pXmlSierialize->xml_serialize(/* "Vz�ο���" */g_sLangTxt_Native_Vz_referPhase.GetString(), "VzPhDefine", "", "PsuVzRefPhase", pParas->m_nVzPhDefine);	
		pXmlSierialize->xml_serialize(/* "Vz���" */g_sLangTxt_Native_Vz_phase_angle.GetString(), "VzPh", "��", "number", pParas->m_fUxInput_Ang);	
	}
	else
	{
		pXmlSierialize->xml_serialize(/* "�غ�բʱ�䶨ֵ" */g_sLangTxt_Native_reclose_timeset.GetString(),"RecloseTime","s","set",pParas->m_fRecloseTime);
		pXmlSierialize->xml_serialize(/* "�����ʱ�䶨ֵ" */g_sLangTxt_Native_PostAccelerat_TimeSet.GetString(),"AfterAcceTime","s","set",pParas->m_fAfterAcceTime);
		pXmlSierialize->xml_serialize(/* "������ѹUx �����ʽ" */g_sLangTxt_Native_auxiV_UxoutputMode.GetString(), "UxMode", "", "UxMode", pParas->m_nVzDefine);	
		pXmlSierialize->xml_serialize(/* "ͬ�ڵ�ѹ��ֵ(��ͬ�ڷ�ʽ��Ч)" */g_sLangTxt_Native_synchronous_VAmp.GetString(),"UxInputMag","V","number",pParas->m_fUxInput_Mag);
		pXmlSierialize->xml_serialize(/* "ͬ�ڵ�ѹ��λ(��ͬ�ڷ�ʽ��Ч)" */g_sLangTxt_Native_synchronous_VPh.GetString(),"UxInputAng","��","number",pParas->m_fUxInput_Ang);
		pXmlSierialize->xml_serialize(/* "��ѹ����ֵ" */g_sLangTxt_Native_pressTestVal.GetString(),"UxHigh","V","number",pParas->m_fUxHigh);
		pXmlSierialize->xml_serialize(/* "��ѹ����ֵ" */g_sLangTxt_Native_NOpressTestVal.GetString(),"UxLow","V","number",pParas->m_fUxLow);
	}

	pXmlSierialize->xml_serialize(/* "������ת���Ʒ�ʽ" */g_sLangTxt_Native_openflip_Control.GetString(), "_OutputSwitchMode", " ", "OutputSwitchMode", pParas->m_nOutputSwitchMode);
	pXmlSierialize->xml_serialize(/* "������ת��ʱ" */g_sLangTxt_Native_FlipDelay.GetString(), "_OutputDelayTime", "s", "number", pParas->m_fBoutTimeTrig);
	pXmlSierialize->xml_serialize(/* "��������ʱ��" */g_sLangTxt_Native_OutputHoldTimeS.GetString(),"_OutputKeepTime","s","number",pParas->m_fBoutHoldTime);
	pXmlSierialize->xml_serialize(/* "��̬����1״̬" */g_sLangTxt_Native_NormalOpen1State.GetString(),"_B01","","DOutputState",pParas->m_nStateBOut[0]);
	pXmlSierialize->xml_serialize(/* "��̬����2״̬" */g_sLangTxt_Native_NormalOpen2State.GetString(),"_B02","","DOutputState",pParas->m_nStateBOut[1]);
	pXmlSierialize->xml_serialize(/* "��̬����3״̬" */g_sLangTxt_Native_NormalOpen3State.GetString(),"_B03","","DOutputState",pParas->m_nStateBOut[2]);
	pXmlSierialize->xml_serialize(/* "��̬����4״̬" */g_sLangTxt_Native_NormalOpen4State.GetString(),"_B04","","DOutputState",pParas->m_nStateBOut[3]);
	pXmlSierialize->xml_serialize(/* "��̬����5״̬" */g_sLangTxt_Native_NormalOpen5State.GetString(),"_B05","","DOutputState",pParas->m_nStateBOut[4]);
	pXmlSierialize->xml_serialize(/* "��̬����6״̬" */g_sLangTxt_Native_NormalOpen6State.GetString(),"_B06","","DOutputState",pParas->m_nStateBOut[5]);
	pXmlSierialize->xml_serialize(/* "��̬����7״̬" */g_sLangTxt_Native_NormalOpen7State.GetString(),"_B07","","DOutputState",pParas->m_nStateBOut[6]);
	pXmlSierialize->xml_serialize(/* "��̬����8״̬" */g_sLangTxt_Native_NormalOpen8State.GetString(),"_B08","","DOutputState",pParas->m_nStateBOut[7]);

	pXmlSierialize->xml_serialize(/* "����A" */g_sLangTxt_Manual_InA.GetString(),"A","","DInputState",pParas->m_nDInputState[0]);
	pXmlSierialize->xml_serialize(/* "����B" */g_sLangTxt_Manual_InB.GetString(),"B","","DInputState",pParas->m_nDInputState[1]);
	pXmlSierialize->xml_serialize(/* "����C" */g_sLangTxt_Manual_InC.GetString(),"C","","DInputState",pParas->m_nDInputState[2]);
	pXmlSierialize->xml_serialize(/* "����R" */g_sLangTxt_Manual_InD.GetString(),"R","","DInputState",pParas->m_nDInputState[3]);
	pXmlSierialize->xml_serialize(/* "����E" */g_sLangTxt_Manual_InE.GetString(),"E","","DInputState",pParas->m_nDInputState[4]);
	pXmlSierialize->xml_serialize(/* "����F" */g_sLangTxt_Manual_InF.GetString(),"F","","DInputState",pParas->m_nDInputState[5]);
	pXmlSierialize->xml_serialize(/* "����G" */g_sLangTxt_Manual_InG.GetString(),"G","","DInputState",pParas->m_nDInputState[6]);
	pXmlSierialize->xml_serialize(/* "����H" */g_sLangTxt_Manual_InH.GetString(),"H","","DInputState",pParas->m_nDInputState[7]);
	pXmlSierialize->xml_serialize(/* "������ѡ��" */g_sLangTxt_Native_input_selection.GetString(),"BinSelect","","BinSelect",pParas->m_nBinSelect);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		//������ǰ�ӿڳ�����
		pXmlSierialize->xml_serialize(/* "GPS����ʱ�̣�ʱ��" */g_sLangTxt_Native_GPSTriggerHour.GetString(), "GpsH"," ","number",pParas->m_tGps.nHour);
		pXmlSierialize->xml_serialize(/* "GPS����ʱ�̣��֣�" */g_sLangTxt_Native_GPSTriggerMinute.GetString(), "GpsM"," ","number",pParas->m_tGps.nMinutes);
		pXmlSierialize->xml_serialize(/* "GPS����ʱ�̣��룩" */g_sLangTxt_Native_GPSTriggerSecond.GetString(), "GpsS"," ","number",pParas->m_tGps.nSeconds);

		pXmlSierialize->xml_serialize(/* "��բ�Ƿ�ʽ( 0-��� 1-��ֵ)" */g_sLangTxt_Native_closeAngmode01.GetString(), "FaultIncMode", "", "FaultAngModePnv",pParas->m_nFaultIncMode);
		pXmlSierialize->xml_serialize(/* "�Ƿ���ӷ����ڷ���" */g_sLangTxt_Native_superimposed_ornot1.GetString(),"bIPlusDC","","BOOL",pParas->m_bIPlusDC);

		pXmlSierialize->xml_serialize(/* "����A" */g_sLangTxt_Manual_InA.GetString(),"_BinAMode","","DInputState",pParas->m_nDInputState[0]);
		pXmlSierialize->xml_serialize(/* "����B" */g_sLangTxt_Manual_InB.GetString(),"_BinBMode","","DInputState",pParas->m_nDInputState[1]);
		pXmlSierialize->xml_serialize(/* "����C" */g_sLangTxt_Manual_InC.GetString(),"_BinCMode","","DInputState",pParas->m_nDInputState[2]);
		pXmlSierialize->xml_serialize(/* "����D" */g_sLangTxt_Manual_InD.GetString(),"_BinDMode","","DInputState",pParas->m_nDInputState[3]);
		pXmlSierialize->xml_serialize(/* "����E" */g_sLangTxt_Manual_InE.GetString(),"_BinEMode","","DInputState",pParas->m_nDInputState[4]);
		pXmlSierialize->xml_serialize(/* "����F" */g_sLangTxt_Manual_InF.GetString(),"_BinFMode","","DInputState",pParas->m_nDInputState[5]);
		pXmlSierialize->xml_serialize(/* "����G" */g_sLangTxt_Manual_InG.GetString(),"_BinGMode","","DInputState",pParas->m_nDInputState[6]);
		pXmlSierialize->xml_serialize(/* "����H" */g_sLangTxt_Manual_InH.GetString(),"_BinHMode","","DInputState",pParas->m_nDInputState[7]);
	}
#endif
	
}


void stt_xml_serialize_impedance_results(tmt_ImpedanceResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("A�ද��ʱ��","TtripA","s","number",pResults->m_fFirstTripTime[0]);
	pXmlSierialize->xml_serialize("B�ද��ʱ��","TtripB","s","number",pResults->m_fFirstTripTime[1]);
	pXmlSierialize->xml_serialize("C�ද��ʱ��","TtripC","s","number",pResults->m_fFirstTripTime[2]);
	pXmlSierialize->xml_serialize("�غ�բ����ʱ��","TtripD","s","number",pResults->m_fRecloseTime);
	pXmlSierialize->xml_serialize("����E����ʱ��", "TtripE", "s", "number", pResults->m_fFirstTripTime[4]);
	pXmlSierialize->xml_serialize("����F����ʱ��", "TtripF", "s", "number",pResults->m_fFirstTripTime[5]);
	pXmlSierialize->xml_serialize("����G����ʱ��", "TtripG", "s", "number",pResults->m_fFirstTripTime[6]);
	pXmlSierialize->xml_serialize("����H����ʱ��", "TtripH", "s", "number",pResults->m_fFirstTripTime[7]);
	pXmlSierialize->xml_serialize("����ʱ��", "TripTime", "", "number",pResults->m_fTripTime);

	pXmlSierialize->xml_serialize("����A��������","ActA","","number",pResults->m_nActA);
	pXmlSierialize->xml_serialize("����B��������","ActB","","number",pResults->m_nActB);
	pXmlSierialize->xml_serialize("����C��������","ActC","","number",pResults->m_nActC);
	pXmlSierialize->xml_serialize("�غ�բ��������","ActD","","number",pResults->m_nActD);

	pXmlSierialize->xml_serialize("����ٶ���ʱ��","TtripAcc","s","number",pResults->m_fSecondTripTime);
	pXmlSierialize->xml_serialize("����ٶ�������","ActAcc","","number",pResults->m_nActAcc);

	pXmlSierialize->xml_serialize("ʵ�ʶ�·����","FaultCurrent","","number",pResults->m_fFaultCurrent);
	pXmlSierialize->xml_serialize("ʵ�ʶ�·��ѹ","FaultVolt","","number",pResults->m_fFaultVol);
#else
	pXmlSierialize->xml_serialize(/* "A�ද��ʱ��" */g_sLangTxt_Native_PhaseATime.GetString(),"TtripA","s","number",pResults->m_fFirstTripTime[0]);
	pXmlSierialize->xml_serialize(/* "B�ද��ʱ��" */g_sLangTxt_Native_PhaseBTime.GetString(),"TtripB","s","number",pResults->m_fFirstTripTime[1]);
	pXmlSierialize->xml_serialize(/* "C�ද��ʱ��" */g_sLangTxt_Native_PhaseCTime.GetString(),"TtripC","s","number",pResults->m_fFirstTripTime[2]);
	pXmlSierialize->xml_serialize(/* "�غ�բ����ʱ��" */g_sLangTxt_Native_RecloseTime.GetString(),"TtripD","s","number",pResults->m_fRecloseTime);
	pXmlSierialize->xml_serialize(/* "����E����ʱ��" */g_sLangTxt_Native_InputETime.GetString(), "TtripE", "s", "number", pResults->m_fFirstTripTime[4]);
	pXmlSierialize->xml_serialize(/* "����F����ʱ��" */g_sLangTxt_Native_InputFTime.GetString(), "TtripF", "s", "number",pResults->m_fFirstTripTime[5]);
	pXmlSierialize->xml_serialize(/* "����G����ʱ��" */g_sLangTxt_Native_InputGTime.GetString(), "TtripG", "s", "number",pResults->m_fFirstTripTime[6]);
	pXmlSierialize->xml_serialize(/* "����H����ʱ��" */g_sLangTxt_Native_InputHTime.GetString(), "TtripH", "s", "number",pResults->m_fFirstTripTime[7]);
	pXmlSierialize->xml_serialize(/* "����ʱ��" */g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number",pResults->m_fTripTime);

	pXmlSierialize->xml_serialize(/* "����A��������" */g_sLangTxt_Native_InputADesc.GetString(),"ActA","","number",pResults->m_nActA);
	pXmlSierialize->xml_serialize(/* "����B��������" */g_sLangTxt_Native_InputBDesc.GetString(),"ActB","","number",pResults->m_nActB);
	pXmlSierialize->xml_serialize(/* "����C��������" */g_sLangTxt_Native_InputCDesc.GetString(),"ActC","","number",pResults->m_nActC);
	pXmlSierialize->xml_serialize(/* "�غ�բ��������" */g_sLangTxt_Native_ReclActDesc.GetString(),"ActD","","number",pResults->m_nActD);

	pXmlSierialize->xml_serialize(/* "����ٶ���ʱ��" */g_sLangTxt_Native_PostAccTime.GetString(),"TtripAcc","s","number",pResults->m_fSecondTripTime);
	pXmlSierialize->xml_serialize(/* "����ٶ�������" */g_sLangTxt_Native_PostAccDesc.GetString(),"ActAcc","","number",pResults->m_nActAcc);

	pXmlSierialize->xml_serialize(/* "ʵ�ʶ�·����" */g_sLangTxt_Native_ActShortCur.GetString(),"FaultCurrent","","number",pResults->m_fFaultCurrent);
	pXmlSierialize->xml_serialize(/* "ʵ�ʶ�·��ѹ" */g_sLangTxt_Native_ActShortVol.GetString(),"FaultVolt","","number",pResults->m_fFaultVol);
#endif
	
}
