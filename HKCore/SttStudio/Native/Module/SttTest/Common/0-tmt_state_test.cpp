#include "stdafx.h"
#include "tmt_state_test.h"

void stt_init_paras(tmt_StateParas *pParas)
{
    memset(&pParas, 0, sizeof(MAX_STATE_COUNT));
    pParas->init();
}

void stt_init_results(tmt_StateResults *pResults)
{
    memset(&pResults, 0, sizeof(MAX_STATE_COUNT));
    pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///
///
void stt_xml_serialize(tmt_ChannelHarm &oChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pChannel =pXmlSierialize->xml_serialize(pszID, pszID, "channel", stt_ParaGroupKey());

    if (pChannel == NULL)
    {
        return;
    }

    pChannel->xml_serialize("��ֵ", "mag", "", "float", oChannel.fAmp);
    pChannel->xml_serialize("��λ", "ang", "", "float",  oChannel.fAngle);
    pChannel->xml_serialize("Ƶ��", "freq", "", "float", oChannel.fFreq);
}

void stt_xml_serialize_binary_out(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("����", "BOout", "BOUT", stt_ParaGroupKey());

    if (pStateSerialize == NULL)
    {
        return;
    }

    pStateSerialize->xml_serialize("������ת��ʱ","BoutDelayT","s","number",oStatePara.m_binOut[0].fTimeTrig);

    CString strName,strID,strTmp;
    for(int nIndex = 0;nIndex<MAX_PARACOUNT_BINARY;nIndex++)
    {
        strName.Format("����%d״̬",(nIndex+1));
		strID.Format("Bout%dState",(nIndex+1));
        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","DOutputState",oStatePara.m_binOut[nIndex].nState);
    }
}

void stt_xml_serialize_binary_in(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("����", "BIn", "BIN", stt_ParaGroupKey());

    if (pStateSerialize == NULL)
    {
        return;
    }

    pStateSerialize->xml_serialize("�����߼�", "AndOr","","InPutLogic_Psu",oStatePara.m_nBinLogic);

    char pszBInName[20]="ABCDEFGH";
    CString strName,strID,strTmp;
    for(int nIndex = 0;nIndex<MAX_PARACOUNT_BINARY;nIndex++)
    {
        strName.Format("����%cѡ��",pszBInName[nIndex]);
        strID.Format("BIn%c",pszBInName[nIndex]);
        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","BOOL",oStatePara.m_binIn[nIndex].nSelect);
    }
}

void stt_xml_serialize_gradient(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("�ݱ�", "Ramp", "RAMP", stt_ParaGroupKey());

    if (pStateSerialize == NULL)
    {
        return;
    }

    pStateSerialize->xml_serialize("�ݱ�����ѡ��","PsuSttRampType","","PsuSttRampType",oStatePara.m_nRampType);
    pStateSerialize->xml_serialize("�ݱ�ͨ��ѡ��","_GradientChSelect","","PsuGradientChannel",oStatePara.m_sttGradient.iVar);
    pStateSerialize->xml_serialize("df/dt","_dfdt","","number",oStatePara.m_sttGradient.fdfdt);
    pStateSerialize->xml_serialize("dv/dt","_dvdt","","number",oStatePara.m_sttGradient.fdvdt);
    pStateSerialize->xml_serialize("��ʼֵ","_Start","","number",oStatePara.m_sttGradient.fStart);
    pStateSerialize->xml_serialize("��ֵֹ","_End","","number",oStatePara.m_sttGradient.fEnd);
    pStateSerialize->xml_serialize("������ѹ","_TrigerV","","number",oStatePara.m_sttGradient.fTrigerV);
    pStateSerialize->xml_serialize("�仯����","_Step","","number",oStatePara.m_sttGradient.fStep);
    pStateSerialize->xml_serialize("ÿ��ʱ��","_StepTime","","number",oStatePara.m_sttGradient.fStepTime);
}

void stt_xml_serialize(tmt_GoosePub &oGoosePub, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pGooseSerialize =pXmlSierialize->xml_serialize("GOOSE�������ƿ�", "GOOSE", nIndex, "GOOSE", stt_ParaGroupKey());
    pGooseSerialize->xml_serialize("�ü���","_Test","","BOOL",oGoosePub.m_bTest);

    CSttXmlSerializeBase *pChannelsSerialize =pGooseSerialize->xml_serialize("GOOSE�������ƿ�", "channels", nIndex, "Channels", stt_ParaGroupKey());
    CString strChannelID;

    for(int nIndex=0;nIndex<MAX_GOOSE_CHANNEL_COUNT;nIndex++)
    {
        strChannelID.Format(_T("channel%d"),nIndex);
        pChannelsSerialize->xml_serialize("GOOSEͨ��", strChannelID.GetString()," ","string",oGoosePub.m_strChannel[nIndex]);
    }
}

void stt_xml_serialize(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("״̬", "state", nIndex, "State", stt_ParaGroupKey());

    if (pStateSerialize == NULL)
    {
        return;
    }

    pStateSerialize->xml_serialize(("������ʽ"), ("EndMode"),(" "),("StateEndMode_PSU"),oStatePara.m_nTriggerCondition);
    pStateSerialize->xml_serialize(("���ʱ��"), ("LastT"),("s"),("number"),oStatePara.m_fTimeState);
    pStateSerialize->xml_serialize(("�����󱣳�ʱ��"), ("EndDelayT"),("s"),("number"),oStatePara.m_fTimeAfterTrigger);
    pStateSerialize->xml_serialize(("�Ƿ�ֱ��"), ("bDC"),(""),("BOOL"),oStatePara.m_bDC);
    pStateSerialize->xml_serialize("����ֱ����ѹ","VdcAux","V","number",oStatePara.m_fVolAux);
    pStateSerialize->xml_serialize("GPS����ʱ�̣�ʱ��", "GpsH"," ","number",oStatePara.m_tGps.nHour);
    pStateSerialize->xml_serialize("GPS����ʱ�̣��֣�", "GpsM"," ","number",oStatePara.m_tGps.nMinutes);
    pStateSerialize->xml_serialize("GPS����ʱ�̣��룩", "GpsS"," ","number",oStatePara.m_tGps.nSeconds);

    stt_xml_serialize(oStatePara.m_uiVOL[0].Harm[1], "Ua",pStateSerialize);
    stt_xml_serialize(oStatePara.m_uiVOL[1].Harm[1], "Ub", pStateSerialize);
    stt_xml_serialize(oStatePara.m_uiVOL[2].Harm[1], "Uc", pStateSerialize);
    stt_xml_serialize(oStatePara.m_uiVOL[3].Harm[1], "Uap", pStateSerialize);
    stt_xml_serialize(oStatePara.m_uiVOL[4].Harm[1], "Ubp", pStateSerialize);
    stt_xml_serialize(oStatePara.m_uiVOL[5].Harm[1], "Ucp", pStateSerialize);

    stt_xml_serialize(oStatePara.m_uiCUR[0].Harm[1], "Ia",pStateSerialize);
    stt_xml_serialize(oStatePara.m_uiCUR[1].Harm[1], "Ib", pStateSerialize);
    stt_xml_serialize(oStatePara.m_uiCUR[2].Harm[1], "Ic", pStateSerialize);
    stt_xml_serialize(oStatePara.m_uiCUR[3].Harm[1], "Iap", pStateSerialize);
    stt_xml_serialize(oStatePara.m_uiCUR[4].Harm[1], "Ibp", pStateSerialize);
    stt_xml_serialize(oStatePara.m_uiCUR[5].Harm[1], "Icp", pStateSerialize);

    for(int nIndex = 0;nIndex<MAX_GOOSEPUB_COUNT;nIndex++)
    {
        stt_xml_serialize(oStatePara.m_oGoosePub[nIndex],nIndex,pStateSerialize);
    }

    stt_xml_serialize_binary_in(oStatePara, pStateSerialize);
    stt_xml_serialize_binary_out(oStatePara, pStateSerialize);
    stt_xml_serialize_gradient(oStatePara, pStateSerialize);
}

void stt_xml_serialize(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("��������ת�б�����", "_BinTripRef"," ","StateBinTripRef",pParas->m_nBinTripRef);
    pXmlSierialize->xml_serialize("�Ƿ����ֱ������","FaultId","s","BOOL",pParas->m_bPlusDC);
    pXmlSierialize->xml_serialize("ֱ��������˥��ʱ�䳣��", "_Tao","s","number",pParas->m_fTao);
    pXmlSierialize->xml_serialize("�ظ�����", "_RepeatNumbers"," ","number",pParas->m_nRepeatNumbers);
    pXmlSierialize->xml_serialize("״̬��","StateCount","","number",pParas->m_nStateNumbers);

    long nIndex = 0;

    for (nIndex=0; nIndex<pParas->m_nStateNumbers; nIndex++)
    {
        stt_xml_serialize(pParas->m_paraState[nIndex], nIndex, pXmlSierialize);
    }
}

void stt_xml_serialize(tmt_StateResult &oStateResult, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("״̬", "state", nIndex, "State", stt_ParaGroupKey());

    if (pStateSerialize == NULL)
    {
        return;
    }

    CString strName,strID;
    for(int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
    {
        strName.Format("����%d��תʱ��",(nIndex+1));
        strID.Format("TtripBin%d",(nIndex+1));
        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",oStateResult.m_frTimeBinAct[nIndex][0]);
    }
}

void stt_xml_serialize(tmt_StateResults *pResults,int nStateNums, CSttXmlSerializeBase *pXmlSierialize)
{
    for (int nIndex=0; nIndex<nStateNums; nIndex++)
    {
        stt_xml_serialize(pResults->m_resultState[nIndex], nIndex, pXmlSierialize);
    }
}

#include"../../SttCmd/SttTestCmd.h"
#include"tmt_state_test.h"
#include"../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_StateTest()
{
    tmt_StateTest oStateTest;
    oStateTest.init(10);
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oStateTest.m_oStateParas, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("StateTestDemo.xml");
//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
