#include "stdafx.h"
#include "tmt_abnsimulation_test.h"


void stt_init_paras(tmt_AbnsimulationParas *pParas)
{
    memset(&pParas, 0, sizeof(tmt_AbnsimulationParas));
    pParas->init();
}




///////////////////////////////////////////////////////////////////////////////////////////////////
//void stt_xml_serialize(tmt_ChannelHarm &oChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize)
//{
//    CSttXmlSerializeBase *pChannel =pXmlSierialize->xml_serialize(pszID, pszID, "channel", stt_ParaGroupKey());

//    if (pChannel == NULL)
//    {
//        return;
//    }

//    pChannel->xml_serialize("��ֵ", "mag", "", "float", oChannel.fAmp);
//    pChannel->xml_serialize("��λ", "ang", "", "float",  oChannel.fAngle);
//    pChannel->xml_serialize("Ƶ��", "freq", "", "float", oChannel.fFreq);
//}

void stt_xml_serialize_binary_out(tmt_abnstate_para &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
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
        strID.Format("Bout%dState");
        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","DOutputState",oStatePara.m_binOut[nIndex].nState);
    }
}

void stt_xml_serialize_binary_in(tmt_abnstate_para &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
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

#ifdef _PSX_IDE_QT_
void stt_xml_serialize_Goose(tmt_goose &oAbnGSPara, CSttXmlSerializeBase *pXmlSierialize)
{

    CSttXmlSerializeBase *pGSSerialize =pXmlSierialize->xml_serialize("Goose�쳣ģ���������", "GooseSet", "GSSET", stt_ParaGroupKey());

    if (pGSSerialize == NULL)
    {
        return;
    }


    pGSSerialize->xml_serialize("ԴMAC��ַ", "SrcMac","","SrcMac",(CString &)oAbnGSPara.m_MacSrc);
    pGSSerialize->xml_serialize("Ŀ��MAC��ַ", "DestMac","","DestMac",(CString &)oAbnGSPara.m_MacDesc);
    pGSSerialize->xml_serialize("GcRef", "GcRef","","GcRef",(CString &)oAbnGSPara.m_GcRef);
    pGSSerialize->xml_serialize("GoID", "GOID","","GOID",(CString &)oAbnGSPara.m_GoID);
    pGSSerialize->xml_serialize("���ݼ�", "DataSet","","DataSet",(CString &)oAbnGSPara.m_DataSetRef);
    pGSSerialize->xml_serialize("���ð汾", "ConfRev","","ConfRev",(CString &)oAbnGSPara.m_ConfRev);
    pGSSerialize->xml_serialize("St", "ST","","ST",(CString &)oAbnGSPara.m_StNum);
    pGSSerialize->xml_serialize("Sq", "SQ","","SQ",(CString &)oAbnGSPara.m_SqNum);

    pGSSerialize->xml_serialize("TTL", "TTL","","TTL",(CString &)oAbnGSPara.m_TTL);
    pGSSerialize->xml_serialize("APPID", "APPID","","APPID",(CString &)oAbnGSPara.m_AppID);
    pGSSerialize->xml_serialize("ί��", "Entrust","","Entrust",(CString &)oAbnGSPara.m_NdsCom);

    pGSSerialize->xml_serialize("����λʹ��", "Test","","Test",oAbnGSPara.nTestModePos);
    pGSSerialize->xml_serialize("Vlan", "VLAN","","VLAN",(CString &)oAbnGSPara.m_VLanID);
    pGSSerialize->xml_serialize("�����ʶ", "NetType","","NetType",(CString &)oAbnGSPara.m_NetType);
    pGSSerialize->xml_serialize("Vlan���ȼ�", "VlanPrrty","","VlanPrrty",(CString &)oAbnGSPara.m_VLanPri);
    pGSSerialize->xml_serialize("ʱ��Ʒ��", "TimeQlty","","TimeQlty",(int &)oAbnGSPara.ntimequality);

}
#endif

//Ʒ���쳣����
void stt_xml_serialize_SMV_AbnQltySet(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CString strChannel, strChannelID;
    CSttXmlSerializeBase *pAbnQltySerialize =pXmlSierialize->xml_serialize("Ʒ���쳣����", "AbnQltySet", "AbnQltySet", stt_ParaGroupKey());

    if (pAbnQltySerialize == NULL)
    {
        return;
    }
    for(int i=0; i<50;i++)
    {
       strChannel.Format(_T("ͨ��%dʹ��"), i+1);
       strChannelID.Format(_T("Channel%dEnable"), i+1);
        pAbnQltySerialize->xml_serialize(strChannel.GetString(), strChannelID.GetString(),"","BOOL",oAbnSVPara.bQltyInvChannel[i]);
    }
    pAbnQltySerialize->xml_serialize("��Ч", "QltySetbit01","","number",oAbnSVPara.QltySet.nValid);
    pAbnQltySerialize->xml_serialize("���", "QltySetbit2","","BOOL",oAbnSVPara.QltySet.bOverflow);
    pAbnQltySerialize->xml_serialize("��ֵ��", "QltySetbit3","","number",oAbnSVPara.QltySet.bOutRange);
    pAbnQltySerialize->xml_serialize("����׼ֵ", "QltySetbit4","","BOOL",oAbnSVPara.QltySet.bBadBmVal);
    pAbnQltySerialize->xml_serialize("����", "QltySetbit5","","number",oAbnSVPara.QltySet.bJitter);
    pAbnQltySerialize->xml_serialize("����", "QltySetbit6","","BOOL",oAbnSVPara.QltySet.bFault);
    pAbnQltySerialize->xml_serialize("������", "QltySetbit7","","number",oAbnSVPara.QltySet.bOldDataOT);
    pAbnQltySerialize->xml_serialize("��һ��", "QltySetbit8","","BOOL",oAbnSVPara.QltySet.bInconformity);
    pAbnQltySerialize->xml_serialize("����ȷ", "QltySetbit9","","number",oAbnSVPara.QltySet.bImprecise);
    pAbnQltySerialize->xml_serialize("Դ", "QltySetbit10","","BOOL",oAbnSVPara.QltySet.bSrc);
    pAbnQltySerialize->xml_serialize("����", "QltySetbit11","","number",oAbnSVPara.QltySet.bTest);
    pAbnQltySerialize->xml_serialize("����Ա����", "QltySetbit12","","BOOL",oAbnSVPara.QltySet.bOprLock);
}

//�쳣������
void stt_xml_serialize_SMV_AbnPtSet(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CString strPtName, strPtID;
    CSttXmlSerializeBase *pAbnPtSerialize =pXmlSierialize->xml_serialize("�쳣������", "AbnPtSet", "AbnPtSet", stt_ParaGroupKey());

    if (pAbnPtSerialize == NULL)
    {
        return;
    }

    for(int i=0; i<80;i++)
    {
       strPtName.Format(_T("��%dʹ��"), i+1);
       strPtID.Format(_T("Point%dEnable"), i+1);
        pAbnPtSerialize->xml_serialize(strPtName.GetString(), strPtID.GetString(),"","BOOL",oAbnSVPara.bSVAbnSet[i]);
    }
}

//�����쳣����
#ifdef _PSX_IDE_QT_
void stt_xml_serialize_SMV_AbnMsgSet(tmt_sv_92 &oMsg, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pAbnMsgSerialize =pXmlSierialize->xml_serialize("�����쳣����", "AbnMsgSet", "AbnMsgSet", stt_ParaGroupKey());

    if (pAbnMsgSerialize == NULL)
    {
        return;
    }
    pAbnMsgSerialize->xml_serialize("ԴMac��ַ", "SrcMac","","SrcMac",(CString &)oMsg.m_MacSrc);
    pAbnMsgSerialize->xml_serialize("Ŀ��Mac��ַ", "DestMac","","DestMac",(CString &)oMsg.m_MacDesc);
    pAbnMsgSerialize->xml_serialize("VlanID", "VLANID","","VLANID",(CString &)oMsg.m_VLanID);
    pAbnMsgSerialize->xml_serialize("Vlan���ȼ�", "VlanPrrty","","VlanPrrty",(CString &)oMsg.m_VLanPri);
    pAbnMsgSerialize->xml_serialize("�����ʶ", "NetType","","NetType",(CString &)oMsg.m_NetType);
    pAbnMsgSerialize->xml_serialize("AppID", "APPID","","APPID",(CString &)oMsg.m_AppID);
    pAbnMsgSerialize->xml_serialize("ͬ����ʽ", "SyncMode","","SyncMode",(CString &)oMsg.m_SyncMode);
    pAbnMsgSerialize->xml_serialize("�汾��", "ConfRev","","ConfRev",(CString &)oMsg.m_ConfRev);
    pAbnMsgSerialize->xml_serialize("������ʱ", "DelayTime","","DelayTime",(CString &)oMsg.m_DelayTimeValue);
    pAbnMsgSerialize->xml_serialize("���ݼ�", "DataSet","","DataSet",(CString &)oMsg.m_Datset);
    pAbnMsgSerialize->xml_serialize("RefrTm", "RefrTm","","RefrTm",oMsg.m_bRefrTm);
    pAbnMsgSerialize->xml_serialize("SVID", "SVID","","SVID",(CString &)oMsg.m_SVID);
}
#endif

//�ɵ����
void stt_xml_serialize_SMV_FlyPt(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pFlyPtSerialize =pXmlSierialize->xml_serialize("�ɵ�����", "FlyPtSet", "FlyPtSet", stt_ParaGroupKey());

    if (pFlyPtSerialize == NULL)
    {
        return;
    }
    pFlyPtSerialize->xml_serialize("�ɵ��ѹֵ", "FlyPointU","","number",oAbnSVPara.fFlyPointVolt);
    pFlyPtSerialize->xml_serialize("�ɵ����ֵ", "FlyPointI","","number",oAbnSVPara.fFlyPointCur);
    pFlyPtSerialize->xml_serialize("�ɵ��ѹUaʹ��", "bUaFly","","BOOL",oAbnSVPara.bVolFly[0]);
    pFlyPtSerialize->xml_serialize("�ɵ��ѹUbʹ��", "bUbFly","","BOOL",oAbnSVPara.bVolFly[1]);
    pFlyPtSerialize->xml_serialize("�ɵ��ѹUcʹ��", "bUcFly","","BOOL",oAbnSVPara.bVolFly[2]);
    pFlyPtSerialize->xml_serialize("�ɵ����Iaʹ��", "bIaFly","","BOOL",oAbnSVPara.bCurFly[0]);
    pFlyPtSerialize->xml_serialize("�ɵ����Ibʹ��", "bIbFly","","BOOL",oAbnSVPara.bCurFly[1]);
    pFlyPtSerialize->xml_serialize("�ɵ����Icʹ��", "bIcFly","","BOOL",oAbnSVPara.bCurFly[2]);
}

//��������
void stt_xml_serialize_SMV_Jitter(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pJitterSerialize =pXmlSierialize->xml_serialize("��������", "JitterSet", "JitterSet", stt_ParaGroupKey());

    if (pJitterSerialize == NULL)
    {
        return;
    }
    pJitterSerialize->xml_serialize("����ֵ",          "Jitter",         "ns","number",oAbnSVPara.nJitter);
}

//�������
void stt_xml_serialize_SMV_ErrCmpt(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pErrCmptSerialize =pXmlSierialize->xml_serialize("�������", "ErrCmpt", "ErrCmpt", stt_ParaGroupKey());

    if (pErrCmptSerialize == NULL)
    {
        return;
    }
    pErrCmptSerialize->xml_serialize("����ֵ", "ErrCmpt","","number",oAbnSVPara.nErrCmpt);
}

//��ʱƫ��
void stt_xml_serialize_SMV_OffsetTime(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pOffsetTimeSerialize =pXmlSierialize->xml_serialize("��ʱƫ��", "OffsetTime", "OffsetTime", stt_ParaGroupKey());

    if (pOffsetTimeSerialize == NULL)
    {
        return;
    }
    pOffsetTimeSerialize->xml_serialize("ƫ��ʱ��", "OffsetTime","us","number",oAbnSVPara.fOffsetTime);
}

//��ʱ�仯
void stt_xml_serialize_SMV_DelayTime(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pDelayTimeSerialize =pXmlSierialize->xml_serialize("��ʱ�仯", "DelayTime", "DelayTime", stt_ParaGroupKey());

    if (pDelayTimeSerialize == NULL)
    {
        return;
    }
    pDelayTimeSerialize->xml_serialize("��ʱʱ��", "DelayTime","us","number",oAbnSVPara.fDelayTime);
}

//���ƫ��
void stt_xml_serialize_SMV_OffsetIndex(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pOffsetIndexSerialize =pXmlSierialize->xml_serialize("���ƫ��", "OffsetIndex", "OffsetIndex", stt_ParaGroupKey());

    if (pOffsetIndexSerialize == NULL)
    {
        return;
    }
    pOffsetIndexSerialize->xml_serialize("���ƫ��", "ErrIndex","","number",oAbnSVPara.nErrIndex);
}

void stt_xml_serialize_SMV(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pSVSerialize =pXmlSierialize->xml_serialize("SV�쳣ģ���������", "SvSet", "SVSET", stt_ParaGroupKey());

    if (pSVSerialize == NULL)
    {
        return;
    }

    pSVSerialize->xml_serialize("SV�쳣��ʽ", "SmvAbnType","","SmvAbnType",oAbnSVPara.nAbnType);
    //��֡�쳣����ʱֻ��Ҫ�����쳣�㼴��
    //�ɵ����
     stt_xml_serialize_SMV_FlyPt(oAbnSVPara, pSVSerialize);
    //��������
      stt_xml_serialize_SMV_Jitter(oAbnSVPara, pSVSerialize);
    //�������
       stt_xml_serialize_SMV_ErrCmpt(oAbnSVPara, pSVSerialize);
    //�쳣������
    stt_xml_serialize_SMV_AbnPtSet(oAbnSVPara, pSVSerialize);
    //��ʱƫ��
    stt_xml_serialize_SMV_OffsetTime(oAbnSVPara, pSVSerialize);
    //��ʱ�仯
    stt_xml_serialize_SMV_DelayTime(oAbnSVPara, pSVSerialize);
    //���ƫ��
    stt_xml_serialize_SMV_OffsetIndex(oAbnSVPara, pSVSerialize);
    //Ʒ���쳣����
    stt_xml_serialize_SMV_AbnQltySet(oAbnSVPara, pSVSerialize);

    pSVSerialize->xml_serialize("����ѡ��", "MsgSel","","MsgSel",oAbnSVPara.nSvGroupSel);
    pSVSerialize->xml_serialize("�쳣����", "AbnSndTyp","","AbnSndTyp",(int &)oAbnSVPara.nInvDataSndTyp);
    pSVSerialize->xml_serialize("�����ܲ���", "SndCircles","","number",oAbnSVPara.nCircle);
    pSVSerialize->xml_serialize("ÿ�뷢���ܲ���",     "CirclesPerSnd",         "","number",oAbnSVPara.nCirclePerSecond);
    pSVSerialize->xml_serialize("����ʱ��", "SndTime","","number",oAbnSVPara.nHoldTime);
        //�����쳣����
#ifdef _PSX_IDE_QT_
    stt_xml_serialize_SMV_AbnMsgSet(oAbnSVPara.oIec61850_9_2Msg, pSVSerialize);
#endif
}

//void stt_xml_serialize_gradient(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
//{
//    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("�ݱ�", "Ramp", "RAMP", stt_ParaGroupKey());
//
//    if (pStateSerialize == NULL)
//    {
//        return;
//    }
//
//    pStateSerialize->xml_serialize("�ݱ�����ѡ��","PsuSttRampType","","PsuSttRampType",oStatePara.m_nRampType);
//    pStateSerialize->xml_serialize("�ݱ�ͨ��ѡ��","_GradientChSelect","","PsuGradientChannel",oStatePara.m_sttGradient.iVar);
//    pStateSerialize->xml_serialize("df/dt","_dfdt","","number",oStatePara.m_sttGradient.fdfdt);
//    pStateSerialize->xml_serialize("dv/dt","_dvdt","","number",oStatePara.m_sttGradient.fdvdt);
//    pStateSerialize->xml_serialize("��ʼֵ","_Start","","number",oStatePara.m_sttGradient.fStart);
//    pStateSerialize->xml_serialize("��ֵֹ","_End","","number",oStatePara.m_sttGradient.fEnd);
//    pStateSerialize->xml_serialize("������ѹ","_TrigerV","","number",oStatePara.m_sttGradient.fTrigerV);
//    pStateSerialize->xml_serialize("�仯����","_Step","","number",oStatePara.m_sttGradient.fStep);
//    pStateSerialize->xml_serialize("ÿ��ʱ��","_StepTime","","number",oStatePara.m_sttGradient.fStepTime);
//}

void stt_xml_serialize(tmt_abnstate_para &oAbnStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("״̬", "state", nIndex, "State", stt_ParaGroupKey());

    if (pStateSerialize == NULL)
    {
        return;
    }

    pStateSerialize->xml_serialize(("������ʽ"), ("EndMode"),(" "),("StateEndMode_PSU"),oAbnStatePara.m_nTriggerCondition);
    pStateSerialize->xml_serialize(("���ʱ��"), ("LastT"),("s"),("number"),oAbnStatePara.m_fTimeState);
    pStateSerialize->xml_serialize(("�����󱣳�ʱ��"), ("EndDelayT"),("s"),("number"),oAbnStatePara.m_fTimeAfterTrigger);
 //   pStateSerialize->xml_serialize(("�Ƿ�ֱ��"), ("bDC"),(""),("BOOL"),oStatePara.m_bDC);
 //   pStateSerialize->xml_serialize("����ֱ����ѹ","VdcAux","V","number",oStatePara.m_fVolAux);
    pStateSerialize->xml_serialize("GPS����ʱ�̣�ʱ��", "GpsH"," ","number",oAbnStatePara.m_tGps.nHour);
    pStateSerialize->xml_serialize("GPS����ʱ�̣��֣�", "GpsM"," ","number",oAbnStatePara.m_tGps.nMinutes);
    pStateSerialize->xml_serialize("GPS����ʱ�̣��룩", "GpsS"," ","number",oAbnStatePara.m_tGps.nSeconds);
    pStateSerialize->xml_serialize("�쳣ģ������", "abnType"," ","number",oAbnStatePara.m_nAbnormalType);

    stt_xml_serialize(oAbnStatePara.m_uiVOL[0].Harm[1], "Ua",pStateSerialize);
    stt_xml_serialize(oAbnStatePara.m_uiVOL[1].Harm[1], "Ub", pStateSerialize);
    stt_xml_serialize(oAbnStatePara.m_uiVOL[2].Harm[1], "Uc", pStateSerialize);
    stt_xml_serialize(oAbnStatePara.m_uiVOL[3].Harm[1], "Uap", pStateSerialize);
    stt_xml_serialize(oAbnStatePara.m_uiVOL[4].Harm[1], "Ubp", pStateSerialize);
    stt_xml_serialize(oAbnStatePara.m_uiVOL[5].Harm[1], "Ucp", pStateSerialize);

    stt_xml_serialize(oAbnStatePara.m_uiCUR[0].Harm[1], "Ia",pStateSerialize);
    stt_xml_serialize(oAbnStatePara.m_uiCUR[1].Harm[1], "Ib", pStateSerialize);
    stt_xml_serialize(oAbnStatePara.m_uiCUR[2].Harm[1], "Ic", pStateSerialize);
    stt_xml_serialize(oAbnStatePara.m_uiCUR[3].Harm[1], "Iap", pStateSerialize);
    stt_xml_serialize(oAbnStatePara.m_uiCUR[4].Harm[1], "Ibp", pStateSerialize);
    stt_xml_serialize(oAbnStatePara.m_uiCUR[5].Harm[1], "Icp", pStateSerialize);

    stt_xml_serialize_binary_in(oAbnStatePara, pStateSerialize);

    stt_xml_serialize_binary_out(oAbnStatePara, pStateSerialize);

#ifdef _PSX_IDE_QT_
    stt_xml_serialize_Goose(oAbnStatePara.m_gooseAbnormalPara, pStateSerialize);
#endif

    stt_xml_serialize_SMV(oAbnStatePara.m_smvAbnormalPara, pStateSerialize);
 //   stt_xml_serialize_gradient(oStatePara, pStateSerialize);
}

void stt_xml_serialize(tmt_AbnsimulationParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{

    pXmlSierialize->xml_serialize("��������ת�б�����", "_BinTripRef"," ","StateBinTripRef",pParas->m_nBinTripRef);
    pXmlSierialize->xml_serialize("�Ƿ����ֱ������","FaultId","s","BOOL",pParas->m_bPlusDC);
    pXmlSierialize->xml_serialize("ֱ��������˥��ʱ�䳣��", "_Tao","s","number",pParas->m_fTao);
    pXmlSierialize->xml_serialize("�ظ�����", "_RepeatNumbers"," ","number",pParas->m_nRepeatNumbers);
    pXmlSierialize->xml_serialize("״̬��","StateCount","","number",pParas->m_nStateNumbers);

    long nIndex = 0;

    for (nIndex=0; nIndex<pParas->m_nStateNumbers; nIndex++)
    {
        stt_xml_serialize(pParas->m_AbnStatepara[nIndex], nIndex, pXmlSierialize);
    }
}



#include"../../SttCmd/SttTestCmd.h"
#include"tmt_abnsimulation_test.h"
#include"../../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_AbnStateTest()
{
    tmt_AbnSimulationTest oAbnSimulationTest;
    oAbnSimulationTest.init(10);
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oAbnSimulationTest.m_oAbnSimulationParas, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("AbnSimulationTest.xml");
    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
