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

//    pChannel->xml_serialize("幅值", "mag", "", "float", oChannel.fAmp);
//    pChannel->xml_serialize("相位", "ang", "", "float",  oChannel.fAngle);
//    pChannel->xml_serialize("频率", "freq", "", "float", oChannel.fFreq);
//}

void stt_xml_serialize_binary_out(tmt_abnstate_para &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("开出", "BOout", "BOUT", stt_ParaGroupKey());

    if (pStateSerialize == NULL)
    {
        return;
    }

    pStateSerialize->xml_serialize("开出翻转延时","BoutDelayT","s","number",oStatePara.m_binOut[0].fTimeTrig);

    CString strName,strID,strTmp;
    for(int nIndex = 0;nIndex<MAX_PARACOUNT_BINARY;nIndex++)
    {
        strName.Format("开出%d状态",(nIndex+1));
        strID.Format("Bout%dState");
        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","DOutputState",oStatePara.m_binOut[nIndex].nState);
    }
}

void stt_xml_serialize_binary_in(tmt_abnstate_para &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("开入", "BIn", "BIN", stt_ParaGroupKey());

    if (pStateSerialize == NULL)
    {
        return;
    }

    pStateSerialize->xml_serialize("开入逻辑", "AndOr","","InPutLogic_Psu",oStatePara.m_nBinLogic);
 
    char pszBInName[20]="ABCDEFGH";
    CString strName,strID,strTmp;
    for(int nIndex = 0;nIndex<MAX_PARACOUNT_BINARY;nIndex++)
    {
        strName.Format("开入%c选择",pszBInName[nIndex]);
        strID.Format("BIn%c",pszBInName[nIndex]);
        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","BOOL",oStatePara.m_binIn[nIndex].nSelect);
    }
}

#ifdef _PSX_IDE_QT_
void stt_xml_serialize_Goose(tmt_goose &oAbnGSPara, CSttXmlSerializeBase *pXmlSierialize)
{

    CSttXmlSerializeBase *pGSSerialize =pXmlSierialize->xml_serialize("Goose异常模拟参数设置", "GooseSet", "GSSET", stt_ParaGroupKey());

    if (pGSSerialize == NULL)
    {
        return;
    }


    pGSSerialize->xml_serialize("源MAC地址", "SrcMac","","SrcMac",(CString &)oAbnGSPara.m_MacSrc);
    pGSSerialize->xml_serialize("目的MAC地址", "DestMac","","DestMac",(CString &)oAbnGSPara.m_MacDesc);
    pGSSerialize->xml_serialize("GcRef", "GcRef","","GcRef",(CString &)oAbnGSPara.m_GcRef);
    pGSSerialize->xml_serialize("GoID", "GOID","","GOID",(CString &)oAbnGSPara.m_GoID);
    pGSSerialize->xml_serialize("数据集", "DataSet","","DataSet",(CString &)oAbnGSPara.m_DataSetRef);
    pGSSerialize->xml_serialize("配置版本", "ConfRev","","ConfRev",(CString &)oAbnGSPara.m_ConfRev);
    pGSSerialize->xml_serialize("St", "ST","","ST",(CString &)oAbnGSPara.m_StNum);
    pGSSerialize->xml_serialize("Sq", "SQ","","SQ",(CString &)oAbnGSPara.m_SqNum);

    pGSSerialize->xml_serialize("TTL", "TTL","","TTL",(CString &)oAbnGSPara.m_TTL);
    pGSSerialize->xml_serialize("APPID", "APPID","","APPID",(CString &)oAbnGSPara.m_AppID);
    pGSSerialize->xml_serialize("委托", "Entrust","","Entrust",(CString &)oAbnGSPara.m_NdsCom);

    pGSSerialize->xml_serialize("检修位使能", "Test","","Test",oAbnGSPara.nTestModePos);
    pGSSerialize->xml_serialize("Vlan", "VLAN","","VLAN",(CString &)oAbnGSPara.m_VLanID);
    pGSSerialize->xml_serialize("网络标识", "NetType","","NetType",(CString &)oAbnGSPara.m_NetType);
    pGSSerialize->xml_serialize("Vlan优先级", "VlanPrrty","","VlanPrrty",(CString &)oAbnGSPara.m_VLanPri);
    pGSSerialize->xml_serialize("时间品质", "TimeQlty","","TimeQlty",(int &)oAbnGSPara.ntimequality);

}
#endif

//品质异常设置
void stt_xml_serialize_SMV_AbnQltySet(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CString strChannel, strChannelID;
    CSttXmlSerializeBase *pAbnQltySerialize =pXmlSierialize->xml_serialize("品质异常设置", "AbnQltySet", "AbnQltySet", stt_ParaGroupKey());

    if (pAbnQltySerialize == NULL)
    {
        return;
    }
    for(int i=0; i<50;i++)
    {
       strChannel.Format(_T("通道%d使能"), i+1);
       strChannelID.Format(_T("Channel%dEnable"), i+1);
        pAbnQltySerialize->xml_serialize(strChannel.GetString(), strChannelID.GetString(),"","BOOL",oAbnSVPara.bQltyInvChannel[i]);
    }
    pAbnQltySerialize->xml_serialize("有效", "QltySetbit01","","number",oAbnSVPara.QltySet.nValid);
    pAbnQltySerialize->xml_serialize("溢出", "QltySetbit2","","BOOL",oAbnSVPara.QltySet.bOverflow);
    pAbnQltySerialize->xml_serialize("超值域", "QltySetbit3","","number",oAbnSVPara.QltySet.bOutRange);
    pAbnQltySerialize->xml_serialize("坏基准值", "QltySetbit4","","BOOL",oAbnSVPara.QltySet.bBadBmVal);
    pAbnQltySerialize->xml_serialize("抖动", "QltySetbit5","","number",oAbnSVPara.QltySet.bJitter);
    pAbnQltySerialize->xml_serialize("故障", "QltySetbit6","","BOOL",oAbnSVPara.QltySet.bFault);
    pAbnQltySerialize->xml_serialize("旧数据", "QltySetbit7","","number",oAbnSVPara.QltySet.bOldDataOT);
    pAbnQltySerialize->xml_serialize("不一致", "QltySetbit8","","BOOL",oAbnSVPara.QltySet.bInconformity);
    pAbnQltySerialize->xml_serialize("不精确", "QltySetbit9","","number",oAbnSVPara.QltySet.bImprecise);
    pAbnQltySerialize->xml_serialize("源", "QltySetbit10","","BOOL",oAbnSVPara.QltySet.bSrc);
    pAbnQltySerialize->xml_serialize("测试", "QltySetbit11","","number",oAbnSVPara.QltySet.bTest);
    pAbnQltySerialize->xml_serialize("操作员闭锁", "QltySetbit12","","BOOL",oAbnSVPara.QltySet.bOprLock);
}

//异常点设置
void stt_xml_serialize_SMV_AbnPtSet(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CString strPtName, strPtID;
    CSttXmlSerializeBase *pAbnPtSerialize =pXmlSierialize->xml_serialize("异常点设置", "AbnPtSet", "AbnPtSet", stt_ParaGroupKey());

    if (pAbnPtSerialize == NULL)
    {
        return;
    }

    for(int i=0; i<80;i++)
    {
       strPtName.Format(_T("点%d使能"), i+1);
       strPtID.Format(_T("Point%dEnable"), i+1);
        pAbnPtSerialize->xml_serialize(strPtName.GetString(), strPtID.GetString(),"","BOOL",oAbnSVPara.bSVAbnSet[i]);
    }
}

//报文异常设置
#ifdef _PSX_IDE_QT_
void stt_xml_serialize_SMV_AbnMsgSet(tmt_sv_92 &oMsg, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pAbnMsgSerialize =pXmlSierialize->xml_serialize("报文异常设置", "AbnMsgSet", "AbnMsgSet", stt_ParaGroupKey());

    if (pAbnMsgSerialize == NULL)
    {
        return;
    }
    pAbnMsgSerialize->xml_serialize("源Mac地址", "SrcMac","","SrcMac",(CString &)oMsg.m_MacSrc);
    pAbnMsgSerialize->xml_serialize("目的Mac地址", "DestMac","","DestMac",(CString &)oMsg.m_MacDesc);
    pAbnMsgSerialize->xml_serialize("VlanID", "VLANID","","VLANID",(CString &)oMsg.m_VLanID);
    pAbnMsgSerialize->xml_serialize("Vlan优先级", "VlanPrrty","","VlanPrrty",(CString &)oMsg.m_VLanPri);
    pAbnMsgSerialize->xml_serialize("网络标识", "NetType","","NetType",(CString &)oMsg.m_NetType);
    pAbnMsgSerialize->xml_serialize("AppID", "APPID","","APPID",(CString &)oMsg.m_AppID);
    pAbnMsgSerialize->xml_serialize("同步方式", "SyncMode","","SyncMode",(CString &)oMsg.m_SyncMode);
    pAbnMsgSerialize->xml_serialize("版本号", "ConfRev","","ConfRev",(CString &)oMsg.m_ConfRev);
    pAbnMsgSerialize->xml_serialize("采样延时", "DelayTime","","DelayTime",(CString &)oMsg.m_DelayTimeValue);
    pAbnMsgSerialize->xml_serialize("数据集", "DataSet","","DataSet",(CString &)oMsg.m_Datset);
    pAbnMsgSerialize->xml_serialize("RefrTm", "RefrTm","","RefrTm",oMsg.m_bRefrTm);
    pAbnMsgSerialize->xml_serialize("SVID", "SVID","","SVID",(CString &)oMsg.m_SVID);
}
#endif

//飞点测试
void stt_xml_serialize_SMV_FlyPt(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pFlyPtSerialize =pXmlSierialize->xml_serialize("飞点设置", "FlyPtSet", "FlyPtSet", stt_ParaGroupKey());

    if (pFlyPtSerialize == NULL)
    {
        return;
    }
    pFlyPtSerialize->xml_serialize("飞点电压值", "FlyPointU","","number",oAbnSVPara.fFlyPointVolt);
    pFlyPtSerialize->xml_serialize("飞点电流值", "FlyPointI","","number",oAbnSVPara.fFlyPointCur);
    pFlyPtSerialize->xml_serialize("飞点电压Ua使能", "bUaFly","","BOOL",oAbnSVPara.bVolFly[0]);
    pFlyPtSerialize->xml_serialize("飞点电压Ub使能", "bUbFly","","BOOL",oAbnSVPara.bVolFly[1]);
    pFlyPtSerialize->xml_serialize("飞点电压Uc使能", "bUcFly","","BOOL",oAbnSVPara.bVolFly[2]);
    pFlyPtSerialize->xml_serialize("飞点电流Ia使能", "bIaFly","","BOOL",oAbnSVPara.bCurFly[0]);
    pFlyPtSerialize->xml_serialize("飞点电流Ib使能", "bIbFly","","BOOL",oAbnSVPara.bCurFly[1]);
    pFlyPtSerialize->xml_serialize("飞点电流Ic使能", "bIcFly","","BOOL",oAbnSVPara.bCurFly[2]);
}

//抖动测试
void stt_xml_serialize_SMV_Jitter(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pJitterSerialize =pXmlSierialize->xml_serialize("抖动测试", "JitterSet", "JitterSet", stt_ParaGroupKey());

    if (pJitterSerialize == NULL)
    {
        return;
    }
    pJitterSerialize->xml_serialize("抖动值",          "Jitter",         "ns","number",oAbnSVPara.nJitter);
}

//错序测试
void stt_xml_serialize_SMV_ErrCmpt(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pErrCmptSerialize =pXmlSierialize->xml_serialize("错序测试", "ErrCmpt", "ErrCmpt", stt_ParaGroupKey());

    if (pErrCmptSerialize == NULL)
    {
        return;
    }
    pErrCmptSerialize->xml_serialize("跳变值", "ErrCmpt","","number",oAbnSVPara.nErrCmpt);
}

//延时偏差
void stt_xml_serialize_SMV_OffsetTime(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pOffsetTimeSerialize =pXmlSierialize->xml_serialize("延时偏差", "OffsetTime", "OffsetTime", stt_ParaGroupKey());

    if (pOffsetTimeSerialize == NULL)
    {
        return;
    }
    pOffsetTimeSerialize->xml_serialize("偏差时间", "OffsetTime","us","number",oAbnSVPara.fOffsetTime);
}

//延时变化
void stt_xml_serialize_SMV_DelayTime(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pDelayTimeSerialize =pXmlSierialize->xml_serialize("延时变化", "DelayTime", "DelayTime", stt_ParaGroupKey());

    if (pDelayTimeSerialize == NULL)
    {
        return;
    }
    pDelayTimeSerialize->xml_serialize("延时时间", "DelayTime","us","number",oAbnSVPara.fDelayTime);
}

//序号偏差
void stt_xml_serialize_SMV_OffsetIndex(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pOffsetIndexSerialize =pXmlSierialize->xml_serialize("序号偏差", "OffsetIndex", "OffsetIndex", stt_ParaGroupKey());

    if (pOffsetIndexSerialize == NULL)
    {
        return;
    }
    pOffsetIndexSerialize->xml_serialize("序号偏差", "ErrIndex","","number",oAbnSVPara.nErrIndex);
}

void stt_xml_serialize_SMV(tmt_SmvAbnormal &oAbnSVPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pSVSerialize =pXmlSierialize->xml_serialize("SV异常模拟参数设置", "SvSet", "SVSET", stt_ParaGroupKey());

    if (pSVSerialize == NULL)
    {
        return;
    }

    pSVSerialize->xml_serialize("SV异常方式", "SmvAbnType","","SmvAbnType",oAbnSVPara.nAbnType);
    //丢帧异常，暂时只需要设置异常点即可
    //飞点测试
     stt_xml_serialize_SMV_FlyPt(oAbnSVPara, pSVSerialize);
    //抖动测试
      stt_xml_serialize_SMV_Jitter(oAbnSVPara, pSVSerialize);
    //错序测试
       stt_xml_serialize_SMV_ErrCmpt(oAbnSVPara, pSVSerialize);
    //异常点设置
    stt_xml_serialize_SMV_AbnPtSet(oAbnSVPara, pSVSerialize);
    //延时偏差
    stt_xml_serialize_SMV_OffsetTime(oAbnSVPara, pSVSerialize);
    //延时变化
    stt_xml_serialize_SMV_DelayTime(oAbnSVPara, pSVSerialize);
    //序号偏差
    stt_xml_serialize_SMV_OffsetIndex(oAbnSVPara, pSVSerialize);
    //品质异常设置
    stt_xml_serialize_SMV_AbnQltySet(oAbnSVPara, pSVSerialize);

    pSVSerialize->xml_serialize("报文选择", "MsgSel","","MsgSel",oAbnSVPara.nSvGroupSel);
    pSVSerialize->xml_serialize("异常数据", "AbnSndTyp","","AbnSndTyp",(int &)oAbnSVPara.nInvDataSndTyp);
    pSVSerialize->xml_serialize("发送周波数", "SndCircles","","number",oAbnSVPara.nCircle);
    pSVSerialize->xml_serialize("每秒发送周波数",     "CirclesPerSnd",         "","number",oAbnSVPara.nCirclePerSecond);
    pSVSerialize->xml_serialize("发送时间", "SndTime","","number",oAbnSVPara.nHoldTime);
        //报文异常设置
#ifdef _PSX_IDE_QT_
    stt_xml_serialize_SMV_AbnMsgSet(oAbnSVPara.oIec61850_9_2Msg, pSVSerialize);
#endif
}

//void stt_xml_serialize_gradient(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
//{
//    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("递变", "Ramp", "RAMP", stt_ParaGroupKey());
//
//    if (pStateSerialize == NULL)
//    {
//        return;
//    }
//
//    pStateSerialize->xml_serialize("递变类型选择","PsuSttRampType","","PsuSttRampType",oStatePara.m_nRampType);
//    pStateSerialize->xml_serialize("递变通道选择","_GradientChSelect","","PsuGradientChannel",oStatePara.m_sttGradient.iVar);
//    pStateSerialize->xml_serialize("df/dt","_dfdt","","number",oStatePara.m_sttGradient.fdfdt);
//    pStateSerialize->xml_serialize("dv/dt","_dvdt","","number",oStatePara.m_sttGradient.fdvdt);
//    pStateSerialize->xml_serialize("起始值","_Start","","number",oStatePara.m_sttGradient.fStart);
//    pStateSerialize->xml_serialize("终止值","_End","","number",oStatePara.m_sttGradient.fEnd);
//    pStateSerialize->xml_serialize("触发电压","_TrigerV","","number",oStatePara.m_sttGradient.fTrigerV);
//    pStateSerialize->xml_serialize("变化步长","_Step","","number",oStatePara.m_sttGradient.fStep);
//    pStateSerialize->xml_serialize("每步时间","_StepTime","","number",oStatePara.m_sttGradient.fStepTime);
//}

void stt_xml_serialize(tmt_abnstate_para &oAbnStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("状态", "state", nIndex, "State", stt_ParaGroupKey());

    if (pStateSerialize == NULL)
    {
        return;
    }

    pStateSerialize->xml_serialize(("触发方式"), ("EndMode"),(" "),("StateEndMode_PSU"),oAbnStatePara.m_nTriggerCondition);
    pStateSerialize->xml_serialize(("输出时间"), ("LastT"),("s"),("number"),oAbnStatePara.m_fTimeState);
    pStateSerialize->xml_serialize(("触发后保持时间"), ("EndDelayT"),("s"),("number"),oAbnStatePara.m_fTimeAfterTrigger);
 //   pStateSerialize->xml_serialize(("是否直流"), ("bDC"),(""),("BOOL"),oStatePara.m_bDC);
 //   pStateSerialize->xml_serialize("辅助直流电压","VdcAux","V","number",oStatePara.m_fVolAux);
    pStateSerialize->xml_serialize("GPS触发时刻（时）", "GpsH"," ","number",oAbnStatePara.m_tGps.nHour);
    pStateSerialize->xml_serialize("GPS触发时刻（分）", "GpsM"," ","number",oAbnStatePara.m_tGps.nMinutes);
    pStateSerialize->xml_serialize("GPS触发时刻（秒）", "GpsS"," ","number",oAbnStatePara.m_tGps.nSeconds);
    pStateSerialize->xml_serialize("异常模拟类型", "abnType"," ","number",oAbnStatePara.m_nAbnormalType);

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

    pXmlSierialize->xml_serialize("开入量翻转判别条件", "_BinTripRef"," ","StateBinTripRef",pParas->m_nBinTripRef);
    pXmlSierialize->xml_serialize("是否叠加直流分量","FaultId","s","BOOL",pParas->m_bPlusDC);
    pXmlSierialize->xml_serialize("直流分量的衰减时间常数", "_Tao","s","number",pParas->m_fTao);
    pXmlSierialize->xml_serialize("重复次数", "_RepeatNumbers"," ","number",pParas->m_nRepeatNumbers);
    pXmlSierialize->xml_serialize("状态数","StateCount","","number",pParas->m_nStateNumbers);

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
