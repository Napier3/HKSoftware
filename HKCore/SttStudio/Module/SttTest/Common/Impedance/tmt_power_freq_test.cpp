#include "stdafx.h"
#include "tmt_power_freq_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_PowerFreqParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_PowerFreqParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_PowerFreqParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_PowerFreqParasEx));
	pParas->init();
}

void stt_init_results(tmt_PowerFreqResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_PowerFreqResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_PowerFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//2022.5.26 caoxc ������Ŀ����
	pXmlSierialize->xml_serialize("��Ŀ����", "TestName", "", "string", pParas->m_pszTestName);

	pXmlSierialize->xml_serialize("��������", "FaultType1", "", "NegFault", pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("����ϵ��", "CalCoef", "", "number", pParas->m_fCalCoef);
	pXmlSierialize->xml_serialize("��·�迹��", "Z1Ph", "��", "number",pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize("��·����", "ISet1", "A", "set",pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize("���Ϸ���", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("��������","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize("������ʱ��", "TSet1", "s", "set",pParas->m_fTSetting);

	pXmlSierialize->xml_serialize("����ǰʱ��","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("�������������ʱ��(s)", "TAfterTrig1", "s", "number", pParas->m_fPostFaultTime);

	//����ֵ����
	pXmlSierialize->xml_serialize("��Ƶ�仯���迹��ֵ","DZset","��","number",pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize("����������","PHLM","��","number",pParas->m_fPostSensAngle);
	pXmlSierialize->xml_serialize("�ӵؾ���ƫ�ƽ�","PHPYXD","��","number",pParas->m_fOffsetAngleLN);
	pXmlSierialize->xml_serialize("������ƫ�ƽ�","PHPYXX","��","number",pParas->m_fOffsetAngleLL);
	pXmlSierialize->xml_serialize("���򲹳�ϵ��","KO","","number",pParas->m_fK0Amp);

	pXmlSierialize->xml_serialize("���ϴ�����ʽ","FaultTrigMode","","number",pParas->m_nFaultTrigMode);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣�ʱ��", "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣��֣�", "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣��룩", "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);

	pXmlSierialize->xml_serialize("PT��װλ��","PTPos","","PTPosition",pParas->m_nPTPoint);
	pXmlSierialize->xml_serialize("CT������","CTPos","","CTPos",pParas->m_nCTPoint);
	pXmlSierialize->xml_serialize("�Ƿ�ģ���·����ʱ","SimulateBreakerDelay","s","number",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize("��·����բ��ʱ","BrkBreakTime","s","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize("��·����բ��ʱ","BrkCloseTime","s","number",pParas->m_fCBCloseTime);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		pXmlSierialize->xml_serialize("������ѡ��","_BinSelect","","BinSelect",pParas->m_nBinSelect);

		pXmlSierialize->xml_serialize("����A","_BinAMode","","DInputState",pParas->m_nDInputState[0]);
		pXmlSierialize->xml_serialize("����B","_BinBMode","","DInputState",pParas->m_nDInputState[1]);
		pXmlSierialize->xml_serialize("����C","_BinCMode","","DInputState",pParas->m_nDInputState[2]);
		pXmlSierialize->xml_serialize("����R","_BinDMode","","DInputState",pParas->m_nDInputState[3]);
		pXmlSierialize->xml_serialize("����E","_BinEMode","","DInputState",pParas->m_nDInputState[4]);
		pXmlSierialize->xml_serialize("����F","_BinFMode","","DInputState",pParas->m_nDInputState[5]);
		pXmlSierialize->xml_serialize("����G","_BinGMode","","DInputState",pParas->m_nDInputState[6]);
		pXmlSierialize->xml_serialize("����H","_BinHMode","","DInputState",pParas->m_nDInputState[7]);
	}
#else
	//2022.5.26 caoxc ������Ŀ����
	pXmlSierialize->xml_serialize(/* "��Ŀ����" */g_sLangTxt_Native_ProjName.GetString(), "TestName", "", "string", pParas->m_pszTestName);

	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType1", "", "NegFault", pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "����ϵ��" */g_sLangTxt_Native_CalcCoef.GetString(), "CalCoef", "", "number", pParas->m_fCalCoef);
	pXmlSierialize->xml_serialize(/* "��·�迹��" */g_sLangTxt_Native_ShortZImpAng.GetString(), "Z1Ph", "��", "number",pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize(/* "��·����" */g_sLangTxt_Native_ShortCircuit.GetString(), "ISet1", "A", "set",pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize(/* "���Ϸ���" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_NatureMalf.GetString(),"FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize(/* "������ʱ��" */g_sLangTxt_Native_MaxTimeMalf.GetString(), "TSet1", "s", "set",pParas->m_fTSetting);

	pXmlSierialize->xml_serialize(/* "����ǰʱ��" */g_sLangTxt_Native_PreFautTime.GetString(),"PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize(/* "�������������ʱ��(s)" */g_sLangTxt_Native_DurProtTrip.GetString(), "TAfterTrig1", "s", "number", pParas->m_fPostFaultTime);

	//����ֵ����
	pXmlSierialize->xml_serialize(/* "��Ƶ�仯���迹��ֵ" */g_sLangTxt_Native_FreqChgZSetting.GetString(),"DZset","��","number",pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize(/* "����������" */g_sLangTxt_Native_PosSeqSensAng.GetString(),"PHLM","��","number",pParas->m_fPostSensAngle);
	pXmlSierialize->xml_serialize(/* "�ӵؾ���ƫ�ƽ�" */g_sLangTxt_Native_GndDistOffset.GetString(),"PHPYXD","��","number",pParas->m_fOffsetAngleLN);
	pXmlSierialize->xml_serialize(/* "������ƫ�ƽ�" */g_sLangTxt_Native_PhaseDistOffset.GetString(),"PHPYXX","��","number",pParas->m_fOffsetAngleLL);
	pXmlSierialize->xml_serialize(/* "���򲹳�ϵ��" */g_sLangTxt_State_ZeroCoeff.GetString(),"KO","","number",pParas->m_fK0Amp);

	pXmlSierialize->xml_serialize(/* "���ϴ�����ʽ" */g_sLangTxt_Native_FaultTrigMethod.GetString(),"FaultTrigMode","","number",pParas->m_nFaultTrigMode);
	pXmlSierialize->xml_serialize(/* "GPS����ʱ�̣�ʱ��" */g_sLangTxt_Native_GPSTriggerHour.GetString(), "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize(/* "GPS����ʱ�̣��֣�" */g_sLangTxt_Native_GPSTriggerMinute.GetString(), "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize(/* "GPS����ʱ�̣��룩" */g_sLangTxt_Native_GPSTriggerSecond.GetString(), "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);

	pXmlSierialize->xml_serialize(/* "PT��װλ��" */g_sLangTxt_Native_PT_installPos.GetString(),"PTPos","","PTPosition",pParas->m_nPTPoint);
	pXmlSierialize->xml_serialize(/* "CT������" */g_sLangTxt_Native_CTPolarityPositive.GetString(),"CTPos","","CTPos",pParas->m_nCTPoint);
	pXmlSierialize->xml_serialize(/* "�Ƿ�ģ���·����ʱ" */g_sLangTxt_Native_SimBrkDel.GetString(),"SimulateBreakerDelay","s","number",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize(/* "��·����բ��ʱ" */g_sLangTxt_Native_BrkTripDel.GetString(),"BrkBreakTime","s","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize(/* "��·����բ��ʱ" */g_sLangTxt_Native_BrkClsDel.GetString(),"BrkCloseTime","s","number",pParas->m_fCBCloseTime);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	pXmlSierialize->xml_serialize(/* "������ת���Ʒ�ʽ" */g_sLangTxt_Native_openflip_Control.GetString(), "_OutputSwitchMode", " ", "OutputSwitchMode", pParas->m_nOutputSwitchMode);
	pXmlSierialize->xml_serialize(/* "������ת��ʱ" */g_sLangTxt_Native_openflip_delay.GetString(), "_OutputDelayTime", "s", "number", pParas->m_fBoutTimeTrig);
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
		pXmlSierialize->xml_serialize(/* "������ѡ��" */g_sLangTxt_Native_input_selection.GetString(),"_BinSelect","","BinSelect",pParas->m_nBinSelect);

		pXmlSierialize->xml_serialize(/* "����A" */g_sLangTxt_Manual_InA.GetString(),"_BinAMode","","DInputState",pParas->m_nDInputState[0]);
		pXmlSierialize->xml_serialize(/* "����B" */g_sLangTxt_Manual_InB.GetString(),"_BinBMode","","DInputState",pParas->m_nDInputState[1]);
		pXmlSierialize->xml_serialize(/* "����C" */g_sLangTxt_Manual_InC.GetString(),"_BinCMode","","DInputState",pParas->m_nDInputState[2]);
		pXmlSierialize->xml_serialize(/* "����R" */g_sLangTxt_Manual_InD.GetString(),"_BinDMode","","DInputState",pParas->m_nDInputState[3]);
		pXmlSierialize->xml_serialize(/* "����E" */g_sLangTxt_Manual_InE.GetString(),"_BinEMode","","DInputState",pParas->m_nDInputState[4]);
		pXmlSierialize->xml_serialize(/* "����F" */g_sLangTxt_Manual_InF.GetString(),"_BinFMode","","DInputState",pParas->m_nDInputState[5]);
		pXmlSierialize->xml_serialize(/* "����G" */g_sLangTxt_Manual_InG.GetString(),"_BinGMode","","DInputState",pParas->m_nDInputState[6]);
		pXmlSierialize->xml_serialize(/* "����H" */g_sLangTxt_Manual_InH.GetString(),"_BinHMode","","DInputState",pParas->m_nDInputState[7]);
	}
#endif
	
}

void stt_xml_serialize_ex(tmt_PowerFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��·�迹��(���ʽ)", "Z1PhExp","","string",pParas->m_pszImpAngle);
#else
	pXmlSierialize->xml_serialize(/* "��·�迹��(���ʽ)" */g_sLangTxt_Native_ShortZImpAngExp.GetString(), "Z1PhExp","","string",pParas->m_pszImpAngle);
#endif

	stt_xml_serialize(pParas,pXmlSierialize);
}


void stt_init_paras_LFPGP(tmt_PowerFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
// 	pXmlSierialize->xml_serialize("��������", "FaultType1", "", "NegFault", pParas->m_nFaultType[0]);
// 	pXmlSierialize->xml_serialize("����ϵ��", "CalCoef", "", "number", pParas->m_fCalCoef);
// 	pXmlSierialize->xml_serialize("��·�迹��", "Z1Ph", "��", "number",pParas->m_fImpAngle[0]);
// 	pXmlSierialize->xml_serialize("��·����", "ISet1", "A", "set",pParas->m_fSCCurrent[0]);
// 	pXmlSierialize->xml_serialize("���Ϸ���", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
// 	pXmlSierialize->xml_serialize("��������","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
// 	pXmlSierialize->xml_serialize("������ʱ��", "TSet1", "s", "set",pParas->m_fTSetting);
// 
// 	pXmlSierialize->xml_serialize("����ǰʱ��","PreFaultTime","s","number",pParas->m_fPreFaultTime);
// 	pXmlSierialize->xml_serialize("��������ʱ", "TAfterTrig1", "s", "number", pParas->m_fPostFaultTime);
// 
// 	//����ֵ����
// 	pXmlSierialize->xml_serialize("��Ƶ�仯���迹��ֵ","DZset","��","number",pParas->m_fSetting[0]);
// 	pXmlSierialize->xml_serialize("����������","PHLM","��","number",pParas->m_fPostSensAngle);
// 	pXmlSierialize->xml_serialize("�ӵؾ���ƫ�ƽ�","PHPYXD","��","number",pParas->m_fOffsetAngleLN);
// 	pXmlSierialize->xml_serialize("������ƫ�ƽ�","PHPYXX","��","number",pParas->m_fOffsetAngleLL);
// 	pXmlSierialize->xml_serialize("���򲹳�ϵ��","KO","","number",pParas->m_fK0Amp);
// 
// 	pXmlSierialize->xml_serialize("���ϴ�����ʽ","FaultTrigMode","","number",pParas->m_nFaultTrigMode);
// 	pXmlSierialize->xml_serialize("GPS����ʱ�̣�ʱ��", "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
// 	pXmlSierialize->xml_serialize("GPS����ʱ�̣��֣�", "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
// 	pXmlSierialize->xml_serialize("GPS����ʱ�̣��룩", "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);
// 
// 	pXmlSierialize->xml_serialize("PT��װλ��","PTPos","","PTPosition",pParas->m_nPTPoint);
// 	pXmlSierialize->xml_serialize("CT������","CTPos","","CTPos",pParas->m_nCTPoint);
// 	pXmlSierialize->xml_serialize("�Ƿ�ģ���·����ʱ","SimulateBreakerDelay","s","number",pParas->m_bCBSimulation);
// 	pXmlSierialize->xml_serialize("��·����բ��ʱ","BrkBreakTime","s","number",pParas->m_fCBTripTime);
// 	pXmlSierialize->xml_serialize("��·����բ��ʱ","BrkCloseTime","s","number",pParas->m_fCBCloseTime);
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 	pXmlSierialize->xml_serialize("������ת���Ʒ�ʽ", "_OutputSwitchMode", " ", "OutputSwitchMode", pParas->m_nOutputSwitchMode);
// 	pXmlSierialize->xml_serialize("������ת��ʱ", "_OutputDelayTime", "s", "number", pParas->m_fBoutTimeTrig);
// 	pXmlSierialize->xml_serialize("��������ʱ��","_OutputKeepTime","s","number",pParas->m_fBoutHoldTime);
// 	pXmlSierialize->xml_serialize("��̬����1״̬","_B01","","DOutputState",pParas->m_nStateBOut[0]);
// 	pXmlSierialize->xml_serialize("��̬����2״̬","_B02","","DOutputState",pParas->m_nStateBOut[1]);
// 	pXmlSierialize->xml_serialize("��̬����3״̬","_B03","","DOutputState",pParas->m_nStateBOut[2]);
// 	pXmlSierialize->xml_serialize("��̬����4״̬","_B04","","DOutputState",pParas->m_nStateBOut[3]);
// 	pXmlSierialize->xml_serialize("��̬����5״̬","_B05","","DOutputState",pParas->m_nStateBOut[4]);
// 	pXmlSierialize->xml_serialize("��̬����6״̬","_B06","","DOutputState",pParas->m_nStateBOut[5]);
// 	pXmlSierialize->xml_serialize("��̬����7״̬","_B07","","DOutputState",pParas->m_nStateBOut[6]);
// 	pXmlSierialize->xml_serialize("��̬����8״̬","_B08","","DOutputState",pParas->m_nStateBOut[7]);
// 
// 	pXmlSierialize->xml_serialize("����A","A","","DInputState",pParas->m_nDInputState[0]);
// 	pXmlSierialize->xml_serialize("����B","B","","DInputState",pParas->m_nDInputState[1]);
// 	pXmlSierialize->xml_serialize("����C","C","","DInputState",pParas->m_nDInputState[2]);
// 	pXmlSierialize->xml_serialize("����R","R","","DInputState",pParas->m_nDInputState[3]);
// 	pXmlSierialize->xml_serialize("����E","E","","DInputState",pParas->m_nDInputState[4]);
// 	pXmlSierialize->xml_serialize("����F","F","","DInputState",pParas->m_nDInputState[5]);
// 	pXmlSierialize->xml_serialize("����G","G","","DInputState",pParas->m_nDInputState[6]);
// 	pXmlSierialize->xml_serialize("����H","H","","DInputState",pParas->m_nDInputState[7]);
// 	pXmlSierialize->xml_serialize("������ѡ��","BinSelect","","BinSelect",pParas->m_nBinSelect);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_PowerFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_PowerFreqTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuPowerFreqDist) == 0)
		{
			stt_xml_serialize_ex(&(pTests->m_oPowerFreqParas), pXmlParas);	//�ļ��Ķ�д
		}
// 		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_LFPGP) == 0)
// 		{
// 			stt_xml_serialize(&(pTests->m_oPowerFreqParas), pXmlParas,nBinExNum,nBoutExNum);	//���Բ����·�
// 		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
//		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuPowerFreqDist) == 0)
		{
			stt_xml_serialize(&pTests->m_oPowerFreqResults, pXmlResults);
		}
// 		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_LFPGP) == 0)
// 		{
// 			stt_xml_serialize(&pTests->m_oPowerFreqResults, pXmlResults,nBinExNum,nBoutExNum);
// 		}
	}

	return pXmlParas;
}
