#include "stdafx.h"
#include "tmt_state_test.h"
#include "tmt_system_config.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

void stt_init_paras(tmt_StateParas *pParas)
{
    //	memset(&pParas, 0, sizeof(MAX_STATE_COUNT));
    //	pParas->init();
}

void stt_init_results(tmt_StateResults *pResults)
{
    //	memset(&pResults, 0, sizeof(MAX_STATE_COUNT));
    //	pResults->init();
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

void stt_xml_serialize_Harm(tmt_ChannelHarm *pChannelHarm,const char *pszID,long nIndex,CSttXmlSerializeBase *pXmlSierialize,const char *pszDataTypeID)
{
    CSttXmlSerializeBase *pChannelSerializeBase =pXmlSierialize->xml_serialize(pszID, pszID, "harm", stt_ParaGroupKey());

    if (pChannelSerializeBase == NULL)
    {
        return;
    }

#ifdef NOT_USE_XLANGUAGE
    pChannelSerializeBase->xml_serialize_sys_pata("幅值", "mag", "", "float", pChannelHarm[nIndex].fAmp, pszDataTypeID);//Xzt
    pChannelSerializeBase->xml_serialize("相位", "ang", "", "float",  pChannelHarm[nIndex].fAngle);
#else
  pChannelSerializeBase->xml_serialize_sys_pata(/* "幅值" */ g_sLangTxt_Native_Amplitude.GetString(), "mag", "", "float", pChannelHarm[nIndex].fAmp, pszDataTypeID);
  pChannelSerializeBase->xml_serialize(/* "相位" */ g_sLangTxt_Native_Phase.GetString(), "ang", "", "float", pChannelHarm[nIndex].fAngle);
#endif
    pChannelHarm[nIndex].fFreq=pChannelHarm[1].fFreq*nIndex;

    if (stt_xml_serialize_is_read(pXmlSierialize))//在读到幅值、相位节点时，需要将m_bSelect置为1
    {
        pChannelHarm[nIndex].m_bSelect = 1;
    }
}

void stt_xml_serialize_ChRamp(tmt_Channel *pChannel,CSttXmlSerializeBase *pChannelXmlSierialize)
{
    CSttXmlSerializeBase *pChRampXmlSerializeBase =pChannelXmlSierialize->xml_serialize("ramp", "ramp", "ramp", stt_ParaGroupKey());

    if (pChRampXmlSerializeBase == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pChRampXmlSerializeBase->xml_serialize("幅值递变标识", "MagHarmRampIndex", "", "long", pChannel->Ramp[0].nIndex);
#else
  pChRampXmlSerializeBase->xml_serialize(/* "幅值递变标识" */ g_sLangTxt_Native_AmplitudeGradual.GetString(), "MagHarmRampIndex", "", "long", pChannel->Ramp[0].nIndex);
#endif

    if (pChannel->Ramp[0].nIndex>=0)//当递变通道有效时,再读写其它两个数据
    {
#ifdef NOT_USE_XLANGUAGE
        pChRampXmlSerializeBase->xml_serialize("幅值递变终值", "MagRampEnd", "", "float", pChannel->Ramp[0].fEnd);
        pChRampXmlSerializeBase->xml_serialize("幅值递变步长", "MagRampStep", "", "float", pChannel->Ramp[0].fStep);
#else
    pChRampXmlSerializeBase->xml_serialize(/* "幅值递变终值" */ g_sLangTxt_Native_AmplitudeEndValue.GetString(), "MagRampEnd", "", "float", pChannel->Ramp[0].fEnd);
    pChRampXmlSerializeBase->xml_serialize(/* "幅值递变步长" */ g_sLangTxt_Native_AmplitudeStep.GetString(), "MagRampStep", "", "float", pChannel->Ramp[0].fStep);
#endif
    }
#ifdef NOT_USE_XLANGUAGE
    pChRampXmlSerializeBase->xml_serialize("相位递变标识", "AngHarmRampIndex", "", "long", pChannel->Ramp[1].nIndex);
#else
  pChRampXmlSerializeBase->xml_serialize(/* "相位递变标识" */ g_sLangTxt_Native_PhaseFlag.GetString(), "AngHarmRampIndex", "", "long", pChannel->Ramp[1].nIndex);
#endif

    if (pChannel->Ramp[1].nIndex>=0)
    {
#ifdef NOT_USE_XLANGUAGE
        pChRampXmlSerializeBase->xml_serialize("相位递变终值", "AngRampEnd", "", "float", pChannel->Ramp[1].fEnd);
        pChRampXmlSerializeBase->xml_serialize("相位递变步长", "AngRampStep", "", "float", pChannel->Ramp[1].fStep);
#else
    pChRampXmlSerializeBase->xml_serialize(/* "相位递变终值" */ g_sLangTxt_Native_PhaseEndVal.GetString(), "AngRampEnd", "", "float", pChannel->Ramp[1].fEnd);
    pChRampXmlSerializeBase->xml_serialize(/* "相位递变步长" */ g_sLangTxt_Native_PhaseStep.GetString(), "AngRampStep", "", "float", pChannel->Ramp[1].fStep);
#endif
    }
#ifdef NOT_USE_XLANGUAGE
    pChRampXmlSerializeBase->xml_serialize("频率递变标识", "FreqHarmRampIndex", "", "long", pChannel->Ramp[2].nIndex);
#else
  pChRampXmlSerializeBase->xml_serialize(/* "频率递变标识" */ g_sLangTxt_Native_FreqFlag.GetString(), "FreqHarmRampIndex", "", "long", pChannel->Ramp[2].nIndex);
#endif

    if (pChannel->Ramp[2].nIndex>=0)
    {
#ifdef NOT_USE_XLANGUAGE
        pChRampXmlSerializeBase->xml_serialize("频率递变终值", "FreqRampEnd", "", "float", pChannel->Ramp[2].fEnd);
        pChRampXmlSerializeBase->xml_serialize("频率递变步长", "FreqRampStep", "", "float", pChannel->Ramp[2].fStep);
#else
    pChRampXmlSerializeBase->xml_serialize(/* "频率递变终值" */ g_sLangTxt_Native_FreqEnd.GetString(), "FreqRampEnd", "", "float", pChannel->Ramp[2].fEnd);
    pChRampXmlSerializeBase->xml_serialize(/* "频率递变步长" */ g_sLangTxt_Native_FreqStep.GetString(), "FreqRampStep", "", "float", pChannel->Ramp[2].fStep);
#endif
    }
}

void stt_xml_serialize(tmt_channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize, const char *pszDataTypeID,int nHarmCount)
{
    CSttXmlSerializeBase *pChannelXmlSerializeBase =pXmlSierialize->xml_serialize(pszID, pszID, "channel", stt_ParaGroupKey());

    if (pChannelXmlSerializeBase == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pChannelXmlSerializeBase->xml_serialize_sys_pata("幅值", "mag", "", "float", pChannel->Harm[1].fAmp, pszDataTypeID);
    pChannelXmlSerializeBase->xml_serialize("相位", "ang", "", "float",  pChannel->Harm[1].fAngle);
    pChannelXmlSerializeBase->xml_serialize_sys_pata("频率", "freq", "", "float", pChannel->Harm[1].fFreq, STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
#else
  pChannelXmlSerializeBase->xml_serialize_sys_pata(/* "幅值" */ g_sLangTxt_Native_Amplitude.GetString(), "mag", "", "float", pChannel->Harm[1].fAmp, pszDataTypeID);
  pChannelXmlSerializeBase->xml_serialize(/* "相位" */ g_sLangTxt_Native_Phase.GetString(), "ang", "", "float", pChannel->Harm[1].fAngle);
  pChannelXmlSerializeBase->xml_serialize_sys_pata(/* "频率" */ g_sLangTxt_Native_Freq.GetString(), "freq", "", "float", pChannel->Harm[1].fFreq, STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
#endif
    CString strID;
    BOOL bReadSelect=FALSE;
    if(stt_xml_serialize_is_read(pChannelXmlSerializeBase))
    {
        bReadSelect=TRUE;
    }

    nHarmCount++;//20220516 zhouhj 需要读写的谐波次数需要增加1,为实际解析的谐波次数

    if (nHarmCount>MAX_HARM_COUNT)
    {
        nHarmCount = MAX_HARM_COUNT;
    }

    for (int nIndex = 2;nIndex<nHarmCount;nIndex++)
    {
        strID.Format(_T("Harm%d"),nIndex);
        if (pChannel->Harm[nIndex].m_bSelect||bReadSelect)
        {
            stt_xml_serialize_Harm(pChannel->Harm,strID.GetString(),nIndex,pChannelXmlSerializeBase, pszDataTypeID);
        }
    }

    stt_xml_serialize_ChRamp(pChannel,pChannelXmlSerializeBase);
}

void stt_xml_serialize_statenUnI_pnv(tmt_channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize, const char *pszDataTypeID,int nHarmCount)
{
    CSttXmlSerializeBase *pChannelXmlSerializeBase =pXmlSierialize->xml_serialize(pszID, pszID, "channel", stt_ParaGroupKey());

    if (pChannelXmlSerializeBase == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pChannelXmlSerializeBase->xml_serialize_sys_pata("幅值", "Mag", "", "float", pChannel->Harm[1].fAmp, pszDataTypeID);
    pChannelXmlSerializeBase->xml_serialize("相位", "Ph", "", "float",  pChannel->Harm[1].fAngle);
    pChannelXmlSerializeBase->xml_serialize_sys_pata("频率", "Fre", "", "float", pChannel->Harm[1].fFreq, STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
#else
  pChannelXmlSerializeBase->xml_serialize_sys_pata(/* "幅值" */ g_sLangTxt_Native_Amplitude.GetString(), "Mag", "", "float", pChannel->Harm[1].fAmp, pszDataTypeID);
  pChannelXmlSerializeBase->xml_serialize(/* "相位" */ g_sLangTxt_Native_Phase.GetString(), "Ph", "", "float", pChannel->Harm[1].fAngle);
  pChannelXmlSerializeBase->xml_serialize_sys_pata(/* "频率" */ g_sLangTxt_Native_Freq.GetString(), "Fre", "", "float", pChannel->Harm[1].fFreq, STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
#endif
    CString strID;
    BOOL bReadSelect=FALSE;
    if(stt_xml_serialize_is_read(pChannelXmlSerializeBase))
    {
        bReadSelect=TRUE;
    }

    nHarmCount++;//20220516 zhouhj 需要读写的谐波次数需要增加1,为实际解析的谐波次数

    if (nHarmCount>MAX_HARM_COUNT)
    {
        nHarmCount = MAX_HARM_COUNT;
    }

    for (int nIndex = 2;nIndex<nHarmCount;nIndex++)
    {
        strID.Format(_T("Harm%d"),nIndex);
        if (pChannel->Harm[nIndex].m_bSelect||bReadSelect)
        {
            stt_xml_serialize_Harm(pChannel->Harm,strID.GetString(),nIndex,pChannelXmlSerializeBase, pszDataTypeID);
        }
    }

    stt_xml_serialize_ChRamp(pChannel,pChannelXmlSerializeBase);
}

void stt_xml_serialize_binary_out(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("开出", "BOout", "BOUT", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pStateSerialize = pXmlSierialize->xml_serialize(/* "开出" */ g_sLangTxt_Native_BoutX.GetString(), "BOout", "BOUT", stt_ParaGroupKey());
#endif

    if (pStateSerialize == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pStateSerialize->xml_serialize("开出翻转延时","BoutDelayT","s","number",oStatePara.m_binOut[0].fTimeTrig);
#else
  pStateSerialize->xml_serialize(/* "开出翻转延时" */ g_sLangTxt_Native_FlipDelay.GetString(), "BoutDelayT", "s", "number", oStatePara.m_binOut[0].fTimeTrig);
#endif
    CString strName,strID,strTemp;
#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("开出");
    CString str2 = _T("状态");
#else
  CString str1 = g_sLangTxt_Native_BoutX;
  CString str2 = g_sLangTxt_Status;
#endif
    long nMaxBoutNum = get_xml_serialize_binary_out_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nMaxBoutNum; nIndex++)
    {
        strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp + str2;
        //		strName.Format(_T("开出%d状态"),nIndex+1);
        strID.Format("Bout%dState",(nIndex+1));
        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","DOutputState",oStatePara.m_binOut[nIndex].nState);
    }
}

void stt_xml_serialize_binary_in(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("开入", "BIn", "BIN", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pStateSerialize = pXmlSierialize->xml_serialize(/* "开入" */ g_sLangTxt_Native_BinX.GetString(), "BIn", "BIN", stt_ParaGroupKey());
#endif

    if (pStateSerialize == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pStateSerialize->xml_serialize("开入逻辑", "AndOr","","InPutLogic_Psu",oStatePara.m_nBinLogic);
#else
  pStateSerialize->xml_serialize(/* "开入逻辑" */ g_sLangTxt_Native_InLogic.GetString(), "AndOr", "", "InPutLogic_Psu", oStatePara.m_nBinLogic);
#endif
    char pszBInName[MAX_BINARYIN_COUNT] = "ABCDEFGHIJKLMNOPQRS";
	pszBInName[19]='T';
    CString strName, strID;
#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("开入");
    CString str2 = _T("选择");
#else
  CString str1 = g_sLangTxt_Native_BinX;
  CString str2 = g_sLangTxt_Select;
#endif
    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strName = str1 + pszBInName[nIndex] + str2;
        strID.Format("BIn%c",pszBInName[nIndex]);
        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","BOOL",oStatePara.m_binIn[nIndex].nSelect);
    }
}

void stt_xml_serialize_gradient(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("递变", "Ramp", "RAMP", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pStateSerialize = pXmlSierialize->xml_serialize(/* "递变" */ g_sLangTxt_Manual_Changing.GetString(), "Ramp", "RAMP", stt_ParaGroupKey());
#endif

    if (pStateSerialize == NULL)
    {
        return;
    }

//Xuzt 2024.4.10 新增用于兼容PsuVM相关接口功能
        pStateSerialize->xml_serialize("递变类型选择","PsuSttRampType","","PsuSttRampType",oStatePara.m_nRampType);
        pStateSerialize->xml_serialize("递变通道选择","_GradientChSelect","","PsuGradientChannel",oStatePara.m_sttGradient.iVar);
        pStateSerialize->xml_serialize("df/dt","_dfdt","","number",oStatePara.m_sttGradient.fdfdt);
        pStateSerialize->xml_serialize("dv/dt","_dvdt","","number",oStatePara.m_sttGradient.fdvdt);
        pStateSerialize->xml_serialize("触发电压","_TrigerV","","number",oStatePara.m_sttGradient.fTrigerV);
    //	pStateSerialize->xml_serialize("终止电压","_EndV","","number",oStatePara.m_sttGradient.fEndV);
    //	pStateSerialize->xml_serialize("起始频率","_StartF","","number",oStatePara.m_sttGradient.fStartF);
    //	pStateSerialize->xml_serialize("终止频率","_EndF","","number",oStatePara.m_sttGradient.fEndF);
        pStateSerialize->xml_serialize("起始值","_Start","","number",oStatePara.m_sttGradient.fStart);
        pStateSerialize->xml_serialize("终止值","_End","","number",oStatePara.m_sttGradient.fEnd);
        pStateSerialize->xml_serialize("变化步长","_Step","","number",oStatePara.m_sttGradient.fStep);
        pStateSerialize->xml_serialize("每步时间","_StepTime","","number",oStatePara.m_sttGradient.fStepTime);
}

BOOL stt_xml_serialize(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize,int nHarmCount)
{
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("状态", "state", nIndex, "State", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pStateSerialize = pXmlSierialize->xml_serialize(/* "状态" */ g_sLangTxt_Status.GetString(), "state", nIndex, "State", stt_ParaGroupKey());
#endif

    if (pStateSerialize == NULL)
    {
		return FALSE;
    }

    if(stt_xml_serialize_is_read(pStateSerialize))
    {
#ifdef _PSX_QT_LINUX_
        oStatePara.init();
#endif
    }

	BOOL bFindSelect = FALSE;
#ifdef NOT_USE_XLANGUAGE
    pStateSerialize->xml_serialize("触发方式", "EndMode","","StateEndMode_PSUAuto",oStatePara.m_nTriggerCondition);
    pStateSerialize->xml_serialize("输出时间", "LastT","s","number",oStatePara.m_fTimeState);
    pStateSerialize->xml_serialize("触发后保持时间", "EndDelayT","s","number",oStatePara.m_fTimeAfterTrigger);
    pStateSerialize->xml_serialize("开出量保持时间", "OutputHoldT","s","number",oStatePara.m_fOutputHoldTime);

    pStateSerialize->xml_serialize("是否直流", "bDC","","BOOL",oStatePara.m_bDC);
	bFindSelect = pStateSerialize->xml_serialize("是否选择", "bSelect", "", "BOOL", oStatePara.m_bSelected);
	pStateSerialize->xml_serialize("是否叠加直流分量","FaultId","s","BOOL",oStatePara.m_bPlusDC);
	pStateSerialize->xml_serialize("直流分量的衰减时间常数", "_Tao","s","number",oStatePara.m_fTao);

    pStateSerialize->xml_serialize("描述", "Name", "", "string", oStatePara.m_strName);
   	pStateSerialize->xml_serialize("辅助直流电压","VdcAux","V","number",oStatePara.m_fVolAux);
    //	pStateSerialize->xml_serialize("辅助直流电流","IdcAux","mA","number",oStatePara.m_fCurAux);
    //	pStateSerialize->xml_serialize("是否检修模式", "bTest","","BOOL",oStatePara.m_bTestMode);

    pStateSerialize->xml_serialize("GPS触发时刻（时）", "GpsH"," ","number",oStatePara.m_tGps.nHour);
    pStateSerialize->xml_serialize("GPS触发时刻（分）", "GpsM"," ","number",oStatePara.m_tGps.nMinutes);
    pStateSerialize->xml_serialize("GPS触发时刻（秒）", "GpsS"," ","number",oStatePara.m_tGps.nSeconds);
    pStateSerialize->xml_serialize("递变时间分度(ms)", "RampTimeGrad"," ","number",oStatePara.m_nRampTimeGrad);
	pStateSerialize->xml_serialize("开出模式选择", "BinaryOutType"," ","number",oStatePara.m_nBinaryOutType);//0-开出+Gse,1-只有开出,2-只有Gse

#else
  pStateSerialize->xml_serialize(/* "触发方式" */ g_sLangTxt_Native_TrigMode.GetString(), "EndMode", "", "StateEndMode_PSUAuto", oStatePara.m_nTriggerCondition);
  pStateSerialize->xml_serialize(/* "输出时间" */ g_sLangTxt_Native_OutTime.GetString(), "LastT", "s", "number", oStatePara.m_fTimeState);
  pStateSerialize->xml_serialize(/* "触发后保持时间" */ g_sLangTxt_Native_TrigHoldTime.GetString(), "EndDelayT", "s", "number", oStatePara.m_fTimeAfterTrigger);
  pStateSerialize->xml_serialize(/* "开出量保持时间" */ g_sLangTxt_Native_OutHoldTime.GetString(), "OutputHoldT", "s", "number", oStatePara.m_fOutputHoldTime);

  pStateSerialize->xml_serialize(/* "是否直流" */ g_sLangTxt_Native_IsDC.GetString(), "bDC", "", "BOOL", oStatePara.m_bDC);
  pStateSerialize->xml_serialize(/* "是否选择" */ g_sLangTxt_Native_IsSelected.GetString(), "bSelect", "", "BOOL", oStatePara.m_bSelected);
  pStateSerialize->xml_serialize("是否叠加直流分量","FaultId","s","BOOL",oStatePara.m_bPlusDC);
  pStateSerialize->xml_serialize("直流分量的衰减时间常数", "_Tao","s","number",oStatePara.m_fTao);
  pStateSerialize->xml_serialize(/* "描述" */ g_sLangTxt_State_Description.GetString(), "Name", "", "string", oStatePara.m_strName);
  pStateSerialize->xml_serialize(/* "辅助直流电压" */ g_sLangTxt_Native_AuxiDCV.GetString(), "VdcAux", "V", "number", oStatePara.m_fVolAux);
  //	pStateSerialize->xml_serialize("辅助直流电流","IdcAux","mA","number",oStatePara.m_fCurAux);
  //	pStateSerialize->xml_serialize("是否检修模式", "bTest","","BOOL",oStatePara.m_bTestMode);

  pStateSerialize->xml_serialize(/* "GPS触发时刻（时）" */ g_sLangTxt_Native_GPSTriggerHour.GetString(), "GpsH", " ", "number", oStatePara.m_tGps.nHour);
  pStateSerialize->xml_serialize(/* "GPS触发时刻（分）" */ g_sLangTxt_Native_GPSTriggerMinute.GetString(), "GpsM", " ", "number", oStatePara.m_tGps.nMinutes);
  pStateSerialize->xml_serialize(/* "GPS触发时刻（秒）" */ g_sLangTxt_Native_GPSTriggerSecond.GetString(), "GpsS", " ", "number", oStatePara.m_tGps.nSeconds);
  pStateSerialize->xml_serialize(/* "递变时间分度(ms)" */ g_sLangTxt_Native_GradualTimeScale.GetString(), "RampTimeGrad", " ", "number", oStatePara.m_nRampTimeGrad);
#endif

    /**********兼容PTU200L安卓*********/
    if (stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&oStatePara.m_uiVOL[0], "Ua",pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiVOL[1], "Ub", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiVOL[2], "Uc", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiVOL[3], "Uap", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiVOL[4], "Ubp", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiVOL[5], "Ucp", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);

        stt_xml_serialize(&oStatePara.m_uiCUR[0], "Ia",pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiCUR[1], "Ib", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiCUR[2], "Ic", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiCUR[3], "Iap", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiCUR[4], "Ibp", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiCUR[5], "Icp", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
    }
    /**********兼容PTU200L安卓*********/

    /**********兼容PsuVm*********/
    if (stt_xml_serialize_is_read(pXmlSierialize))//顺接上面兼容PTU200L安卓部分
    {
        stt_xml_serialize(&oStatePara.m_uiVOL[6], "Usa",pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiVOL[7], "Usb", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiVOL[8], "Usc", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiVOL[9], "Uta", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiVOL[10], "Utb", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiVOL[11], "Utc", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);

        stt_xml_serialize(&oStatePara.m_uiCUR[6], "Isa",pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiCUR[7], "Isb", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiCUR[8], "Isc", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiCUR[9], "Ita", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiCUR[10], "Itb", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize(&oStatePara.m_uiCUR[11], "Itc", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
    }
    /**********兼容PsuVm*********/

    //新版序列化,U1~U48,i1~i48
    CString strID;
    for(int nIndex=0;nIndex<MAX_VOLTAGE_COUNT;nIndex++)
    {
        strID.Format(_T("U%d"),nIndex+1);
        stt_xml_serialize(&oStatePara.m_uiVOL[nIndex], strID.GetString(),pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);

        strID.Format(_T("I%d"),nIndex+1);
        stt_xml_serialize(&oStatePara.m_uiCUR[nIndex], strID.GetString(),pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
    }

    if (stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&oStatePara.m_oGoosePub[0],pStateSerialize);
        stt_xml_serialize(&oStatePara.m_oFt3Pub[0],pStateSerialize);
    }

    //2022-1-8  LINUX TestCtrl 用到结构体，不需要引用Device
    //此两个变量做成成员变量
    /*    int nBinExCount=MAX_ExBINARY_COUNT;
    int nBoutExCount=MAX_ExBINARY_COUNT;

#ifdef _PSX_QT_LINUX_
    nBinExCount=CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules.m_nModulesBiCount;
    nBoutExCount=CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules.m_nModulesBoCount;
#endif
*/
    stt_xml_serialize_binary_in(oStatePara, pStateSerialize);
    stt_xml_serialize_Exbinary_in(oStatePara.m_binInEx,pStateSerialize);
    stt_xml_serialize_binary_out(oStatePara, pStateSerialize);
    stt_xml_serialize_Exbinary_out(oStatePara.m_binOutEx,pStateSerialize);

    stt_xml_serialize_AbnormalSMV(&oStatePara.m_oAbnormalSMV,pStateSerialize);
    stt_xml_serialize_AbnormalGOOSE(&oStatePara.m_oAbnormalGOOSE,pStateSerialize);
    if (stt_xml_serialize_is_read(pXmlSierialize))//兼容PsuVm，重新启用
    {
        stt_xml_serialize_gradient(oStatePara, pStateSerialize);  // 采用新的方式
    }

	return bFindSelect;
}

void stt_xml_serialize_statenUnI_pnv(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize, int nMode,int nHarmCount)
{
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("状态", "state", nIndex, "State", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pStateSerialize = pXmlSierialize->xml_serialize(/* "状态" */ g_sLangTxt_State.GetString(), "state", nIndex, "State", stt_ParaGroupKey());
#endif


    if (pStateSerialize == NULL)
    {
        return;
    }

#ifdef NOT_USE_XLANGUAGE
    pStateSerialize->xml_serialize("触发方式", "EndMode","","StateEndMode",oStatePara.m_nTriggerCondition);
    pStateSerialize->xml_serialize("输出时间", "LastT","s","number",oStatePara.m_fTimeState);
    pStateSerialize->xml_serialize("触发后保持时间", "EndDelayT","s","number",oStatePara.m_fTimeAfterTrigger);
    pStateSerialize->xml_serialize("开出量保持时间", "OutputHoldT","s","number",oStatePara.m_fOutputHoldTime);

    pStateSerialize->xml_serialize("是否直流", "bDC","","BOOL",oStatePara.m_bDC);
    pStateSerialize->xml_serialize("辅助直流电压","VdcAux","V","number",oStatePara.m_fVolAux);
    //	pStateSerialize->xml_serialize("辅助直流电流","IdcAux","mA","number",oStatePara.m_fCurAux);
    //	pStateSerialize->xml_serialize("是否检修模式", "bTest","","BOOL",oStatePara.m_bTestMode);

    pStateSerialize->xml_serialize("GPS触发时刻（时）", "GpsH"," ","number",oStatePara.m_tGps.nHour);
    pStateSerialize->xml_serialize("GPS触发时刻（分）", "GpsM"," ","number",oStatePara.m_tGps.nMinutes);
    pStateSerialize->xml_serialize("GPS触发时刻（秒）", "GpsS"," ","number",oStatePara.m_tGps.nSeconds);
    pStateSerialize->xml_serialize("递变时间分度(ms)", "RampTimeGrad"," ","number",oStatePara.m_nRampTimeGrad);
#else
  pStateSerialize->xml_serialize(/* "触发方式" */ g_sLangTxt_Native_TrigMode.GetString(), "EndMode", "", "StateEndMode", oStatePara.m_nTriggerCondition);
  pStateSerialize->xml_serialize(/* "输出时间" */ g_sLangTxt_Native_OutTime.GetString(), "LastT", "s", "number", oStatePara.m_fTimeState);
  pStateSerialize->xml_serialize(/* "触发后保持时间" */ g_sLangTxt_Native_TrigHoldTime.GetString(), "EndDelayT", "s", "number", oStatePara.m_fTimeAfterTrigger);
  pStateSerialize->xml_serialize(/* "开出量保持时间" */ g_sLangTxt_Native_OutHoldTime.GetString(), "OutputHoldT", "s", "number", oStatePara.m_fOutputHoldTime);

  pStateSerialize->xml_serialize(/* "是否直流" */ g_sLangTxt_Native_IsDC.GetString(), "bDC", "", "BOOL", oStatePara.m_bDC);
  pStateSerialize->xml_serialize(/* "辅助直流电压" */ g_sLangTxt_Native_AuxiDCV.GetString(), "VdcAux", "V", "number", oStatePara.m_fVolAux);
  //	pStateSerialize->xml_serialize("辅助直流电流","IdcAux","mA","number",oStatePara.m_fCurAux);
  //	pStateSerialize->xml_serialize("是否检修模式", "bTest","","BOOL",oStatePara.m_bTestMode);

  pStateSerialize->xml_serialize(/* "GPS触发时刻（时）" */ g_sLangTxt_Native_GPSTriggerHour.GetString(), "GpsH", " ", "number", oStatePara.m_tGps.nHour);
  pStateSerialize->xml_serialize(/* "GPS触发时刻（分）" */ g_sLangTxt_Native_GPSTriggerMinute.GetString(), "GpsM", " ", "number", oStatePara.m_tGps.nMinutes);
  pStateSerialize->xml_serialize(/* "GPS触发时刻（秒）" */ g_sLangTxt_Native_GPSTriggerSecond.GetString(), "GpsS", " ", "number", oStatePara.m_tGps.nSeconds);
  pStateSerialize->xml_serialize(/* "递变时间分度(ms)" */ g_sLangTxt_Native_GradualTimeScale.GetString(), "RampTimeGrad", " ", "number", oStatePara.m_nRampTimeGrad);
#endif

    if(nMode == STT_PNV_STATE_6U6I)
    {
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[0], "Ua",pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[1], "Ub", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[2], "Uc", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[3], "Uap", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[4], "Ubp", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[5], "Ucp", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);

        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[6], "Uas",pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[7], "Ubs", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[8], "Ucs", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[9], "Uat", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[10], "Ubt", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[11], "Uct", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);

        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[0], "Ia",pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[1], "Ib", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[2], "Ic", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[3], "Iap", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[4], "Ibp", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[5], "Icp", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);

        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[6], "Ias",pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[7], "Ibs", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[8], "Ics", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[9], "Iat", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[10], "Ibt", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[11], "Ict", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
    }
    if(nMode == STT_PNV_STATE_4U3I)
    {
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[0], "Ua",pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[1], "Ub", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[2], "Uc", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiVOL[3], "Uz", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[0], "Ia",pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[1], "Ib", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
        stt_xml_serialize_statenUnI_pnv(&oStatePara.m_uiCUR[2], "Ic", pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
    }
    if (stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&oStatePara.m_oGoosePub[0],pStateSerialize);
        stt_xml_serialize(&oStatePara.m_oFt3Pub[0],pStateSerialize);
    }
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pBInSerialize =pStateSerialize->xml_serialize("开入", "BIn", "BIN", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pBInSerialize = pStateSerialize->xml_serialize(/* "开入" */ g_sLangTxt_Native_BinX.GetString(), "BIn", "BIN", stt_ParaGroupKey());
#endif

    if (pBInSerialize != NULL)
    {
#ifdef NOT_USE_XLANGUAGE
        pBInSerialize->xml_serialize("开入逻辑", "AndOr","","InPutLogic",oStatePara.m_nBinLogic);
#else
    pBInSerialize->xml_serialize(/* "开入逻辑" */ g_sLangTxt_Native_InLogic.GetString(), "AndOr", "", "InPutLogic", oStatePara.m_nBinLogic);
#endif
        char pszBInName[9]="ABCRabcr";
        CString strName,strID;
#ifdef NOT_USE_XLANGUAGE
        CString str1 = _T("开入");
        CString str2 = _T("选择");
#else
    CString str1 = g_sLangTxt_Native_BinX;
    CString str2 = g_sLangTxt_Select;
#endif
        for(int nIndex = 0; nIndex < 8; nIndex++)
        {
            strName = str1 + pszBInName[nIndex] + str2;
            strID.Format("BIn%c",pszBInName[nIndex]);
            pBInSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","BOOL",oStatePara.m_binIn[nIndex].nSelect);
        }
    }

    stt_xml_serialize_Exbinary_in(oStatePara.m_binInEx,pStateSerialize);

#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pBoutsSerialize = pStateSerialize->xml_serialize("开出", "BOout", "BOUT", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pBoutsSerialize = pStateSerialize->xml_serialize(/* "开出" */ g_sLangTxt_Native_BoutX.GetString(), "BOout", "BOUT", stt_ParaGroupKey());
#endif
    if (pBoutsSerialize != NULL)
    {
        CString strID;
        for(int nIndex = 0; nIndex < 8; nIndex++)
        {
            strID.Format("Bout%d",(nIndex+1));
            CSttXmlSerializeBase *pBoutSerialize = pBoutsSerialize->xml_serialize("", strID.GetString(), "BOCH", stt_ParaGroupKey());
            if (pBoutSerialize != NULL)
            {
#ifdef NOT_USE_XLANGUAGE
                pBoutSerialize->xml_serialize("开出翻转延时","DelayT","s","number",oStatePara.m_binOut[nIndex].fTimeTrig);
                pBoutSerialize->xml_serialize("开出状态","State","","DOutputState",oStatePara.m_binOut[nIndex].nState);
#else
        pBoutSerialize->xml_serialize(/* "开出翻转延时" */ g_sLangTxt_Native_FlipDelay.GetString(), "DelayT", "s", "number", oStatePara.m_binOut[nIndex].fTimeTrig);
        pBoutSerialize->xml_serialize(/* "开出状态" */ g_sLangTxt_Native_OpenState.GetString(), "State", "", "DOutputState", oStatePara.m_binOut[nIndex].nState);
#endif
            }
        }
    }

    stt_xml_serialize_Exbinary_out(oStatePara.m_binOutEx,pStateSerialize);
}

void stt_xml_serialize_ex(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize,long nVolRsNum,long nCurRsNum,long nHarmCount,bool bSmvAbnormal, bool bGooseAbnormal)
{
    if (nVolRsNum > MAX_VOLTAGE_COUNT)
    {
        nVolRsNum = MAX_VOLTAGE_COUNT;
    }

    if (nCurRsNum > MAX_CURRENT_COUNT)
    {
        nCurRsNum = MAX_CURRENT_COUNT;
    }

#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("状态", "state", nIndex, "State", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pStateSerialize = pXmlSierialize->xml_serialize(/* "状态" */ g_sLangTxt_State.GetString(), "state", nIndex, "State", stt_ParaGroupKey());
#endif

    if (pStateSerialize == NULL)
    {
        return;
    }

#ifdef NOT_USE_XLANGUAGE
    pStateSerialize->xml_serialize("触发方式", "EndMode","","StateEndMode_PSUAuto",oStatePara.m_nTriggerCondition);
    pStateSerialize->xml_serialize("输出时间", "LastT","s","number",oStatePara.m_fTimeState);
    pStateSerialize->xml_serialize("触发后保持时间", "EndDelayT","s","number",oStatePara.m_fTimeAfterTrigger);
    pStateSerialize->xml_serialize("开出量保持时间", "OutputHoldT","s","number",oStatePara.m_fOutputHoldTime);

    pStateSerialize->xml_serialize("是否直流", "bDC","","BOOL",oStatePara.m_bDC);
    pStateSerialize->xml_serialize("是否选择", "bSelect", "", "BOOL", oStatePara.m_bSelected);
    pStateSerialize->xml_serialize("描述", "Name", "", "string", oStatePara.m_strName);
	pStateSerialize->xml_serialize("是否叠加直流分量","FaultId","s","BOOL",oStatePara.m_bPlusDC);
	pStateSerialize->xml_serialize("直流分量的衰减时间常数", "_Tao","s","number",oStatePara.m_fTao);

    pStateSerialize->xml_serialize("辅助直流电压","VdcAux","V","number",oStatePara.m_fVolAux);
    //	pStateSerialize->xml_serialize("辅助直流电流","IdcAux","mA","number",oStatePara.m_fCurAux);
    //	pStateSerialize->xml_serialize("是否检修模式", "bTest","","BOOL",oStatePara.m_bTestMode);

    pStateSerialize->xml_serialize("GPS触发时刻（时）", "GpsH"," ","number",oStatePara.m_tGps.nHour);
    pStateSerialize->xml_serialize("GPS触发时刻（分）", "GpsM"," ","number",oStatePara.m_tGps.nMinutes);
    pStateSerialize->xml_serialize("GPS触发时刻（秒）", "GpsS"," ","number",oStatePara.m_tGps.nSeconds);
    pStateSerialize->xml_serialize("递变时间分度(ms)", "RampTimeGrad"," ","number",oStatePara.m_nRampTimeGrad);
#else
  pStateSerialize->xml_serialize(/* "触发方式" */ g_sLangTxt_Native_TrigMode.GetString(), "EndMode", "", "StateEndMode_PSUAuto", oStatePara.m_nTriggerCondition);
  pStateSerialize->xml_serialize(/* "输出时间" */ g_sLangTxt_Native_OutTime.GetString(), "LastT", "s", "number", oStatePara.m_fTimeState);
  pStateSerialize->xml_serialize(/* "触发后保持时间" */ g_sLangTxt_Native_TrigHoldTime.GetString(), "EndDelayT", "s", "number", oStatePara.m_fTimeAfterTrigger);
  pStateSerialize->xml_serialize(/* "开出量保持时间" */ g_sLangTxt_Native_OutHoldTime.GetString(), "OutputHoldT", "s", "number", oStatePara.m_fOutputHoldTime);

  pStateSerialize->xml_serialize(/* "是否直流" */ g_sLangTxt_Native_IsDC.GetString(), "bDC", "", "BOOL", oStatePara.m_bDC);
  pStateSerialize->xml_serialize(/* "是否选择" */ g_sLangTxt_Native_IsSelected.GetString(), "bSelect", "", "BOOL", oStatePara.m_bSelected);
  pStateSerialize->xml_serialize("是否叠加直流分量","FaultId","s","BOOL",oStatePara.m_bPlusDC);
  pStateSerialize->xml_serialize("直流分量的衰减时间常数", "_Tao","s","number",oStatePara.m_fTao);
  pStateSerialize->xml_serialize(/* "描述" */ g_sLangTxt_State_Description.GetString(), "Name", "", "string", oStatePara.m_strName);
  pStateSerialize->xml_serialize(/* "辅助直流电压" */ g_sLangTxt_Native_AuxiDCV.GetString(), "VdcAux", "V", "number", oStatePara.m_fVolAux);
  //	pStateSerialize->xml_serialize("辅助直流电流","IdcAux","mA","number",oStatePara.m_fCurAux);
  //	pStateSerialize->xml_serialize("是否检修模式", "bTest","","BOOL",oStatePara.m_bTestMode);

  pStateSerialize->xml_serialize(/* "GPS触发时刻（时）" */ g_sLangTxt_Native_GPSTriggerHour.GetString(), "GpsH", " ", "number", oStatePara.m_tGps.nHour);
  pStateSerialize->xml_serialize(/* "GPS触发时刻（分）" */ g_sLangTxt_Native_GPSTriggerMinute.GetString(), "GpsM", " ", "number", oStatePara.m_tGps.nMinutes);
  pStateSerialize->xml_serialize(/* "GPS触发时刻（秒）" */ g_sLangTxt_Native_GPSTriggerSecond.GetString(), "GpsS", " ", "number", oStatePara.m_tGps.nSeconds);
  pStateSerialize->xml_serialize(/* "递变时间分度(ms)" */ g_sLangTxt_Native_GradualTimeScale.GetString(), "RampTimeGrad", " ", "number", oStatePara.m_nRampTimeGrad);
#endif
    //新版序列化,U1~U18,i1~i18
    CString strID;
    //	int nIDCnt  =  (DIGITAL_CHANNEL_MAX/2)  +  8;// mym 2021-6-24 加了个 8

    for(int nIndex=0;nIndex<nVolRsNum;nIndex++)
    {
        strID.Format(_T("U%d"),nIndex+1);
        stt_xml_serialize(&oStatePara.m_uiVOL[nIndex], strID.GetString(),pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom,nHarmCount);
    }

    for(int nIndex=0;nIndex<nCurRsNum;nIndex++)
    {
        strID.Format(_T("I%d"),nIndex+1);
        stt_xml_serialize(&oStatePara.m_uiCUR[nIndex], strID.GetString(),pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom,nHarmCount);
    }

    stt_xml_serialize_binary_in(oStatePara, pStateSerialize);
    stt_xml_serialize_Exbinary_in(oStatePara.m_binInEx,pStateSerialize);
    stt_xml_serialize_binary_out(oStatePara, pStateSerialize);
    stt_xml_serialize_Exbinary_out(oStatePara.m_binOutEx,pStateSerialize);

    if (bSmvAbnormal)
    {
        stt_xml_serialize_AbnormalSMV(&oStatePara.m_oAbnormalSMV,pStateSerialize);
    }

    if (bGooseAbnormal)
    {
        stt_xml_serialize_AbnormalGOOSE(&oStatePara.m_oAbnormalGOOSE,pStateSerialize);
    }
    //	stt_xml_serialize_gradient(oStatePara, pStateSerialize);zhouhj 20211009 采用新的方式
}

void stt_xml_serialize_ex(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize,long nVolRsNum,long nCurRsNum,long nHarmCount)
{
    stt_xml_serialize_ex(oStatePara,nIndex,pXmlSierialize,nVolRsNum,nCurRsNum,nHarmCount,true,true);
}

void stt_xml_serialize_common(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("开入量翻转判别条件", "_BinTripRef"," ","StateBinTripRef",pParas->m_nBinTripRef);
	pXmlSierialize->xml_serialize("是否为顺序状态序列", "_bSequence"," ","BOOL",pParas->m_bSequence);
	pXmlSierialize->xml_serialize("是否叠加直流分量","FaultId","s","long",pParas->m_nPlusDC);
	pXmlSierialize->xml_serialize("直流分量的衰减时间常数", "_Tao","s","number",pParas->m_fTao);
	pXmlSierialize->xml_serialize("重复次数", "_RepeatNumbers"," ","number",pParas->m_nRepeatNumbers);

    CSttXmlSerializeBase *pEstimatesSerialize = pXmlSierialize->xml_serialize("结果评估", "rslt_evaluation", "rslt_evaluation", stt_ParaGroupKey());
#else
  pXmlSierialize->xml_serialize(/* "开入量翻转判别条件" */ g_sLangTxt_Native_InFlipCond.GetString(), "_BinTripRef", " ", "StateBinTripRef", pParas->m_nBinTripRef);
  pXmlSierialize->xml_serialize(/* "是否为顺序状态序列" */ g_sLangTxt_Native_IsSeqStateSeq.GetString(), "_bSequence", " ", "BOOL", pParas->m_bSequence);
  pXmlSierialize->xml_serialize(/* "是否叠加直流分量" */ g_sLangTxt_Native_DCOverlay.GetString(), "FaultId", "s", "long", pParas->m_nPlusDC);
  pXmlSierialize->xml_serialize(/* "直流分量的衰减时间常数" */ g_sLangTxt_Native_DCDampTime.GetString(), "_Tao", "s", "number", pParas->m_fTao);
  pXmlSierialize->xml_serialize(/* "重复次数" */ g_sLangTxt_Native_RepeatCount.GetString(), "_RepeatNumbers", " ", "number", pParas->m_nRepeatNumbers);

  CSttXmlSerializeBase *pEstimatesSerialize = pXmlSierialize->xml_serialize("结果评估", "rslt_evaluation", "rslt_evaluation", stt_ParaGroupKey());
#endif
    if (pEstimatesSerialize == NULL)
    {
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        CSttXmlSerializeBase *pEstimateSerialize = pEstimatesSerialize->xml_serialize("结果评估", "rslt_evaluation", i, "rslt_evaluation", stt_ParaGroupKey());
		if (pEstimateSerialize == NULL)
        {
            return;
        }

#ifdef NOT_USE_XLANGUAGE
        pEstimateSerialize->xml_serialize("使能评估", "UseError", " ", "BOOL", pParas->m_paraEstimates[i].m_bUseError);
		pEstimateSerialize->xml_serialize("计时起点_状态", "TtripBegin_State"," ","string",pParas->m_paraEstimates[i].m_strTtripBegin_State);
		pEstimateSerialize->xml_serialize("计时终点_状态", "TtripEnd_State"," ","string",pParas->m_paraEstimates[i].m_strTtripEnd_State);
		pEstimateSerialize->xml_serialize("计时起点_开入", "TtripBegin_Bin"," ","string",pParas->m_paraEstimates[i].m_strTtripBegin_Bin);
		pEstimateSerialize->xml_serialize("计时终点_开入", "TtripEnd_Bin"," ","string",pParas->m_paraEstimates[i].m_strTtripEnd_Bin);
		pEstimateSerialize->xml_serialize("绝对误差限", "ActT_AbsErr"," ","number",pParas->m_paraEstimates[i].m_fActT_AbsErr);
		pEstimateSerialize->xml_serialize("相对误差限", "ActT_RelErr"," ","number",pParas->m_paraEstimates[i].m_fActT_RelErr);
		pEstimateSerialize->xml_serialize("整定值", "TSet"," ","number",pParas->m_paraEstimates[i].m_fTset);
		pEstimateSerialize->xml_serialize("判断逻辑", "ErrorLogic"," ","number",pParas->m_paraEstimates[i].m_nErrorLogic);
#else
    pEstimateSerialize->xml_serialize(/* "使能评估" */ g_sLangTxt_Native_EnableEval.GetString(), "UseError", " ", "BOOL", pParas->m_paraEstimates[i].m_bUseError);
    pEstimateSerialize->xml_serialize(/* "计时起点_状态" */ g_sLangTxt_Native_TimeStartState.GetString(), "TtripBegin_State", " ", "string", pParas->m_paraEstimates[i].m_strTtripBegin_State);
    pEstimateSerialize->xml_serialize(/* "计时终点_状态" */ g_sLangTxt_Native_TimeEndState.GetString(), "TtripEnd_State", " ", "string", pParas->m_paraEstimates[i].m_strTtripEnd_State);
    pEstimateSerialize->xml_serialize(/* "计时起点_开入" */ g_sLangTxt_Native_TimeStartInput.GetString(), "TtripBegin_Bin", " ", "string", pParas->m_paraEstimates[i].m_strTtripBegin_Bin);
    pEstimateSerialize->xml_serialize(/* "计时终点_开入" */ g_sLangTxt_Native_TimeEndInput.GetString(), "TtripEnd_Bin", " ", "string", pParas->m_paraEstimates[i].m_strTtripEnd_Bin);
    pEstimateSerialize->xml_serialize(/* "绝对误差限" */ g_sLangTxt_Native_AbsErrorLimit.GetString(), "ActT_AbsErr", " ", "number", pParas->m_paraEstimates[i].m_fActT_AbsErr);
    pEstimateSerialize->xml_serialize(/* "相对误差限" */ g_sLangTxt_Native_RelErrorLimit.GetString(), "ActT_RelErr", " ", "number", pParas->m_paraEstimates[i].m_fActT_RelErr);
    pEstimateSerialize->xml_serialize(/* "整定值" */ g_sLangTxt_State_SettingValue.GetString(), "TSet", " ", "number", pParas->m_paraEstimates[i].m_fTset);
    pEstimateSerialize->xml_serialize(/* "判断逻辑" */ g_sLangTxt_Native_JudgeLogic.GetString(), "ErrorLogic", " ", "number", pParas->m_paraEstimates[i].m_nErrorLogic);
#endif
    }
}

void stt_xml_serialize(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nHarmCount)
{
    stt_xml_serialize_common(pParas,pXmlSierialize);

#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("状态数","StateCount","","number",pParas->m_nStateNumbers);
#else
  pXmlSierialize->xml_serialize(/* "状态数" */ g_sLangTxt_Native_StateNum.GetString(), "StateCount", "", "number", pParas->m_nStateNumbers);
#endif

    long nStateCount = pParas->m_nStateNumbers;
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        nStateCount = g_nStateCount;
	}
    long nIndex = 0;
	long nSelectCount = 0;
	BOOL bFindSelect = FALSE;
    for (nIndex=0; nIndex < nStateCount; nIndex++)
    {
        if(stt_xml_serialize_is_read(pXmlSierialize))
        {
			pParas->m_paraState[nIndex].m_bSelected = FALSE;
			bFindSelect = stt_xml_serialize(pParas->m_paraState[nIndex], nIndex, pXmlSierialize,nHarmCount);
			if(bFindSelect)
			{
				if(pParas->m_paraState[nIndex].m_bSelected)
				{
					nSelectCount++;
				}
			}
        }
        else
        {
            if(pParas->m_paraState[nIndex].m_bSelected)
            {
                stt_xml_serialize(pParas->m_paraState[nIndex], nIndex, pXmlSierialize,nHarmCount);
            }
        }
    }

	if(nSelectCount > 0)
	{
		pParas->m_nStateNumbers = nSelectCount;
	}
}

void stt_xml_serialize_statenUnI_pnv(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize, int nMode, long nHarmCount)
{
    stt_xml_serialize_common(pParas,pXmlSierialize);

#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("状态数","StateCount","","number",pParas->m_nStateNumbers);
#else
  pXmlSierialize->xml_serialize(/* "状态数" */ g_sLangTxt_Native_StateNum.GetString(), "StateCount", "", "number", pParas->m_nStateNumbers);
#endif
	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
    {

#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("是否叠加直流分量","_bFaultId","s","long",pParas->m_nPlusDC);
#else
		pXmlSierialize->xml_serialize(/* "是否叠加直流分量" */ g_sLangTxt_Native_DCOverlay.GetString(), "_bFaultId", "s", "long", pParas->m_nPlusDC);
#endif

    }

    long nIndex = 0;

	for (nIndex=0; nIndex<pParas->m_nStateNumbers && nIndex<g_nStateCount; nIndex++)
    {
#ifdef _PSX_QT_LINUX_
        pParas->m_paraState[nIndex].init();
#endif
        stt_xml_serialize_statenUnI_pnv(pParas->m_paraState[nIndex], nIndex+1, pXmlSierialize, nMode, nHarmCount);
    }
}

//bSel=true,则
void stt_xml_serialize_ex(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,bool bSel,long nHarmCount)
{
    stt_xml_serialize_common(pParas,pXmlSierialize);

    if (stt_xml_serialize_is_write(pXmlSierialize) && bSel)
    {//下发命令时
        int nSelCnt = pParas->GetSelCount();
#ifdef NOT_USE_XLANGUAGE
        pXmlSierialize->xml_serialize("状态数","StateCount","","number",nSelCnt);
#else
    pXmlSierialize->xml_serialize(/* "状态数" */ g_sLangTxt_Native_StateNum.GetString(), "StateCount", "", "number", nSelCnt);
#endif
    }
    else
    {
#ifdef NOT_USE_XLANGUAGE
        pXmlSierialize->xml_serialize("状态数","StateCount","","number",pParas->m_nStateNumbers);
#else
    pXmlSierialize->xml_serialize(/* "状态数" */ g_sLangTxt_Native_StateNum.GetString(), "StateCount", "", "number", pParas->m_nStateNumbers);
#endif
        if (stt_xml_serialize_is_read(pXmlSierialize))
        {
            pParas->init(pParas->m_nStateNumbers);
        }
    }

    long nIndex = 0;
    for (int i=0; i<pParas->m_nStateNumbers; i++)
    {
        if (bSel)
        {
            if (pParas->m_paraState[i].m_bSelected)
            {
                stt_xml_serialize(pParas->m_paraState[i], nIndex, pXmlSierialize,nHarmCount);
                nIndex++;
            }
        }
        else
        {
            stt_xml_serialize(pParas->m_paraState[i], nIndex, pXmlSierialize,nHarmCount);
            nIndex++;
        }
    }
}

//bSel=true,则
void stt_xml_serialize_ex2(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,bool bSel,long nHarmCount, bool bSmvAbnormal, bool bGooseAbnormal)
{
    stt_xml_serialize_common(pParas,pXmlSierialize);

    if (stt_xml_serialize_is_write(pXmlSierialize) && bSel)
    {//下发命令时
        int nSelCnt = pParas->GetSelCount();
#ifdef NOT_USE_XLANGUAGE
        pXmlSierialize->xml_serialize("状态数","StateCount","","number",nSelCnt);
#else
    pXmlSierialize->xml_serialize(/* "状态数" */ g_sLangTxt_Native_StateNum.GetString(), "StateCount", "", "number", nSelCnt);
#endif
    }
    else
    {
#ifdef NOT_USE_XLANGUAGE
        pXmlSierialize->xml_serialize("状态数","StateCount","","number",pParas->m_nStateNumbers);
#else
    pXmlSierialize->xml_serialize(/* "状态数" */ g_sLangTxt_Native_StateNum.GetString(), "StateCount", "", "number", pParas->m_nStateNumbers);
#endif
        if (stt_xml_serialize_is_read(pXmlSierialize))
        {
            pParas->init(pParas->m_nStateNumbers);
        }
    }

    long nIndex = 0;
    for (int i=0; i<pParas->m_nStateNumbers; i++)
    {
        if (bSel)
        {
            if (pParas->m_paraState[i].m_bSelected)
            {
                stt_xml_serialize_ex(pParas->m_paraState[i], nIndex, pXmlSierialize,nVolRsNum,nCurRsNum,nHarmCount,bSmvAbnormal, bGooseAbnormal);
                nIndex++;
            }
        }
        else
        {
            stt_xml_serialize_ex(pParas->m_paraState[i], nIndex, pXmlSierialize,nVolRsNum,nCurRsNum,nHarmCount,bSmvAbnormal, bGooseAbnormal);
            nIndex++;
        }
    }
}

void stt_xml_serialize_ex2(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,bool bSel,long nHarmCount)
{
    stt_xml_serialize_ex2(pParas,pXmlSierialize,nVolRsNum,nCurRsNum,bSel,nHarmCount,true,true);
}

void stt_xml_serialize_act_rcd(tmt_StateResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//动作记录,最大64次,根据实际动作情况,上送总的动作信息
{
    CSttXmlSerializeBase *pXmlActRcddata = pXmlSierialize->xml_serialize("ActRcd", "ActRcd", "ActRcd", stt_ParaGroupKey());

    if (pXmlActRcddata == NULL)
    {
        return;
    }

    CString strName,strID,strTemp,strTmp2;

#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("开入");
    CString str1Ex = _T("开入扩展");
    CString str2 = _T("第");
    CString str3 = _T("次动作时间");
#else
  CString str1 = g_sLangTxt_Native_BinX;
  CString str1Ex = g_sLangTxt_Native_InputExpand;
  CString str2 = g_sLangTxt_Native_Number;
  CString str3 = g_sLangTxt_Native_NActionTime;
#endif
    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"),nIndex+1);

        for (int nIndexAct = 0;((nIndexAct<64)&&(nIndexAct<pResults->m_nrBinSwitchCount[nIndex]));nIndexAct++)
        {
            strTmp2.Format(_T("%d"),nIndexAct+1);
            strName = str1 + strTemp + str2 + strTmp2 + str3;
            strID.Format("Bin%dActCount%d",(nIndex+1),(nIndexAct+1));
            pXmlActRcddata->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResults->m_frTimeBinAct[nIndex][nIndexAct]);
        }
    }

    if (g_nBinExCount>0)
    {
        CSttXmlSerializeBase *pXmlActRcdExdata = pXmlSierialize->xml_serialize("ActRcdEx", "ActRcdEx", "ActRcdEx", stt_ParaGroupKey());

        if (pXmlActRcdExdata == NULL)
        {
            return;
        }

        for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
        {
            strTemp.Format(_T("%d"),nIndex+1);

            for (int nIndexAct = 0;((nIndexAct<64)&&(nIndexAct<pResults->m_nrBinExSwitchCount[nIndex]));nIndexAct++)
            {
                strTmp2.Format(_T("%d"),nIndexAct+1);
                strName = str1Ex + strTemp + str2 + strTmp2 + str3;
                strID.Format("BinEx%dActCount%d",(nIndex+1),(nIndexAct+1));
                pXmlActRcdExdata->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResults->m_frTimeBinExAct[nIndex][nIndexAct]);
            }
        }
    }
}

void stt_xml_serialize(tmt_StateResult &oStateResult, tmt_StatePara oParaState, long nStateIndex, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef,int *pnFirstBinInitState,int *pnFirstBinExInitState)
{
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("状态", "state", nStateIndex, "State", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pStateSerialize = pXmlSierialize->xml_serialize(/* "状态" */ g_sLangTxt_Status.GetString(), "state", nStateIndex, "State", stt_ParaGroupKey());
#endif
    if (pStateSerialize == NULL)
    {
        return;
    }

	pStateSerialize->xml_serialize("动作步长", "ActStepIndex", "", "number", oStateResult.m_nCurStepIndex);

    CString strName, strID, strTemp;
#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("开入");
    CString strDesc = _T("动作描述");
#else
  CString str1 = g_sLangTxt_Native_BinX;
  CString strDesc = g_sLangTxt_Native_ActionDesc;
#endif
	int nAct[MAX_ExBINARY_COUNT];
    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp + strDesc;
        strID.Format("ActBin%d",(nIndex+1));
        nAct[nIndex] = 0;

        if(oStateResult.m_nAct == 1)
        {
			if(nStateIndex == 0)
			{
				nAct[nIndex] = (oStateResult.m_nrBinSwitchCount[nIndex] > 0);
			}
			else
			{
				if ((nBinTripRef == 1)&&(oStateResult.m_nBinFirstChgState[nIndex] == pnFirstBinInitState[nIndex]))//如果是以第一态为参考, 并且与第一台初始值不一致
				{
					nAct[nIndex] = (oStateResult.m_nrBinSwitchCount[nIndex] > 1);
				}
				else
				{
					nAct[nIndex] = (oStateResult.m_nrBinSwitchCount[nIndex] > 0);
				}
			}
        }

        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",nAct[nIndex]);
    }

#ifdef NOT_USE_XLANGUAGE
    CString str2 = _T("翻转时刻");
#else
  CString str2 = g_sLangTxt_Native_FlipMoment;
#endif
    float fTtripBin;

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp + str2;

        strID.Format("TtripBin%d",(nIndex+1));
        fTtripBin = 0;

        if(nAct[nIndex] == 1)
        {
            if(oParaState.m_binIn[nIndex].nSelect == 1)
            {
                if(nStateIndex == 0)
                {
                    fTtripBin = oStateResult.m_frTimeBinAct[nIndex][0];
                }
                else
                {
                    if ((nBinTripRef == 1)&&(oStateResult.m_nBinFirstChgState[nIndex] == pnFirstBinInitState[nIndex]))
                    {
                        fTtripBin = oStateResult.m_frTimeBinAct[nIndex][1];
                    }
                    else
                    {
                        fTtripBin = oStateResult.m_frTimeBinAct[nIndex][0];
                    }
                }
            }
        }

        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",fTtripBin);
    }

#ifdef NOT_USE_XLANGUAGE
    CString strRampStepIndex = _T("递变动作步数标识");
#else
  CString strRampStepIndex = g_sLangTxt_Native_StepChangeID;
#endif

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp + strRampStepIndex;

        strID.Format("RampStepIndexBin%d",(nIndex+1));
        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",oStateResult.m_nRampIndex[nIndex]);
    }

    if (g_nBinExCount>0)
    {
#ifdef NOT_USE_XLANGUAGE
        CString str1Ex = _T("开入扩展");
#else
    CString str1Ex = g_sLangTxt_Native_InputExpand;
#endif
        CSttXmlSerializeBase *pXmlStateBinEx = pStateSerialize->xml_serialize("StateBinEx", "StateBinEx", "StateBinEx", stt_ParaGroupKey());

        if (pXmlStateBinEx != NULL)
        {
#ifdef NOT_USE_XLANGUAGE
            CString strDesc = _T("动作描述");
#else
      CString strDesc = g_sLangTxt_Native_ActionDesc;
#endif
            int nBinExCount = g_nBinExCount;//20230409 zhouhj

			if (nBinExCount>MAX_ExBINARY_COUNT)
            {
                nBinExCount = MAX_ExBINARY_COUNT;
            }

            for(int nIndex = 0;nIndex<nBinExCount;nIndex++)
            {
                strTemp.Format(_T("%d"),nIndex+1);
                strName = str1Ex + strTemp + strDesc;
                strID.Format("ActBinEx%d",(nIndex+1));
                nAct[nIndex] = 0;

                if(oStateResult.m_nAct == 1)
                {
					if(nStateIndex == 0)
					{
						nAct[nIndex] = (oStateResult.m_nrBinExSwitchCount[nIndex] > 0);
					}
					else
					{
						if ((nBinTripRef == 1)&&(oStateResult.m_nBinExFirstChgState[nIndex] == pnFirstBinExInitState[nIndex]))//如果是以第一态为参考, 并且与第一台初始值不一致
						{
							nAct[nIndex] = (oStateResult.m_nrBinExSwitchCount[nIndex] > 1);
						}
						else
						{
							nAct[nIndex] = (oStateResult.m_nrBinExSwitchCount[nIndex] > 0);
						}
					}
                }

                pXmlStateBinEx->xml_serialize(strName.GetString(),strID.GetString(),"","number",nAct[nIndex]);
            }

            float fTtripBinEx;

            for(int nIndex = 0; nIndex < nBinExCount; nIndex++)
            {
                strTemp.Format(_T("%d"),nIndex+1);
                strName = str1Ex + strTemp + str2;

                strID.Format("TtripBinEx%d",(nIndex+1));
                fTtripBinEx = 0;

                if(nAct[nIndex] == 1)
                {
                    if(oParaState.m_binInEx[nIndex].nSelect == 1)
                    {
                        if(nStateIndex == 0)
                        {
                            fTtripBinEx = oStateResult.m_frTimeBinExAct[nIndex][0];
                        }
                        else
                        {
                            if ((nBinTripRef == 1)&&(oStateResult.m_nBinExFirstChgState[nIndex] == pnFirstBinExInitState[nIndex]))
                            {
                                fTtripBinEx = oStateResult.m_frTimeBinExAct[nIndex][1];
                            }
                            else
                            {
                                fTtripBinEx = oStateResult.m_frTimeBinExAct[nIndex][0];
                            }
                        }
                    }
                }

                pXmlStateBinEx->xml_serialize(strName.GetString(),strID.GetString(),"","number",fTtripBinEx);
            }

            for(int nIndex = 0; nIndex < nBinExCount; nIndex++)
            {
                strTemp.Format(_T("%d"),nIndex+1);
                strName = str1Ex + strTemp + strRampStepIndex;
                strID.Format("RampStepIndexBinEx%d",(nIndex+1));
                pXmlStateBinEx->xml_serialize(strName.GetString(),strID.GetString(),"","number",oStateResult.m_nRampIndexEx[nIndex]);
            }
        }
    }

    stt_xml_serialize_act_rcd(&oStateResult,pStateSerialize);
}

void stt_xml_serialize_common(tmt_StateResults *pResults, BOOL *bUseErr, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pEstimatesSerialize = pXmlSierialize->xml_serialize("结果评估", "rslt_evaluation", "rslt_evaluation", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pEstimatesSerialize = pXmlSierialize->xml_serialize(/* "结果评估" */ g_sLangTxt_StateEstimate_ResultEstimate.GetString(), "rslt_evaluation", "rslt_evaluation", stt_ParaGroupKey());
#endif

    if (pEstimatesSerialize == NULL)
    {
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        if(!bUseErr[i])
            continue;

#ifdef NOT_USE_XLANGUAGE
        CSttXmlSerializeBase *pEstimateSerialize = pEstimatesSerialize->xml_serialize("结果评估", "rslt_evaluation", i, "rslt_evaluation", stt_ParaGroupKey());
#else
    CSttXmlSerializeBase *pEstimateSerialize = pEstimatesSerialize->xml_serialize(/* "结果评估" */ g_sLangTxt_StateEstimate_ResultEstimate.GetString(), "rslt_evaluation", i, "rslt_evaluation", stt_ParaGroupKey());
#endif
		if (pEstimateSerialize == NULL)
        {
            return;
        }
#ifdef NOT_USE_XLANGUAGE
        pEstimateSerialize->xml_serialize("自定义动作时间","Ttrip","","float",pResults->m_resultEstimates[i].m_fTtrip);
        pEstimateSerialize->xml_serialize("自定义动作时间绝对误差","Ttrip_AbsErr","","float",pResults->m_resultEstimates[i].m_fTtrip_AbsErr);
        pEstimateSerialize->xml_serialize("自定义动作时间相对误差","Ttrip_RelErr","","float",pResults->m_resultEstimates[i].m_fTtrip_RelErr);
#else
    pEstimateSerialize->xml_serialize(/* "自定义动作时间" */ g_sLangTxt_Native_CustomActTime.GetString(), "Ttrip", "", "float", pResults->m_resultEstimates[i].m_fTtrip);
    pEstimateSerialize->xml_serialize(/* "自定义动作时间绝对误差" */ g_sLangTxt_Native_AbsError.GetString(), "Ttrip_AbsErr", "", "float", pResults->m_resultEstimates[i].m_fTtrip_AbsErr);
    pEstimateSerialize->xml_serialize(/* "自定义动作时间相对误差" */ g_sLangTxt_Native_RelError.GetString(), "Ttrip_RelErr", "", "float", pResults->m_resultEstimates[i].m_fTtrip_RelErr);
#endif
    }
}

void stt_xml_serialize_statenUnI_pnv(tmt_StateResult &oStateResult, tmt_StatePara &oParaState, long nStateIndex, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef,int *pnFirstBinInitState,int *pnFirstBinExInitState)
{
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("状态", "state", nStateIndex, "State", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pStateSerialize = pXmlSierialize->xml_serialize(/* "状态" */ g_sLangTxt_Status.GetString(), "state", nStateIndex, "State", stt_ParaGroupKey());
#endif


    if (pStateSerialize == NULL)
    {
        return;
    }

    CString strName,strID,strTemp;

#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("开入");
    CString strDesc = _T("动作描述");
#else
  CString str1 = g_sLangTxt_Native_BinX;
  CString strDesc = g_sLangTxt_Native_ActionDesc;
#endif
	int nAct[MAX_ExBINARY_COUNT];
    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp + strDesc;
        strID.Format("ActBin%d",(nIndex+1));
        nAct[nIndex] = 0;

//        if(oStateResult.m_nAct == 1)
        {
            if ((nBinTripRef == 1)&&(oStateResult.m_nBinFirstChgState[nIndex] == pnFirstBinInitState[nIndex]))//如果是以第一态为参考, 并且与第一台初始值不一致
            {
                nAct[nIndex] = (oStateResult.m_nrBinSwitchCount[nIndex] > 1);
            }
            else
            {
                nAct[nIndex] = (oStateResult.m_nrBinSwitchCount[nIndex] > 0);
            }
        }

        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",nAct[nIndex]);
    }

#ifdef NOT_USE_XLANGUAGE
    CString str2 = _T("翻转时刻");
#else
  CString str2 = g_sLangTxt_Native_FlipMoment;
#endif

    float fTtripBin;

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp + str2;

        strID.Format("TtripBin%d",(nIndex+1));
        fTtripBin = 0;

        if(nAct[nIndex] == 1)
        {
            if(oParaState.m_binIn[nIndex].nSelect == 1)
            {
                if(nStateIndex == 1)
                {
                    fTtripBin = oStateResult.m_frTimeBinAct[nIndex][0];
                }
                else
                {
                    if ((nBinTripRef == 1)&&(oStateResult.m_nBinFirstChgState[nIndex] == pnFirstBinInitState[nIndex]))
                    {
                        fTtripBin = oStateResult.m_frTimeBinAct[nIndex][1];
                    }
                    else
                    {
                        fTtripBin = oStateResult.m_frTimeBinAct[nIndex][0];
                    }
                }
            }
        }

        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",fTtripBin);
    }

#ifdef NOT_USE_XLANGUAGE
    CString strRampStepIndex = _T("递变动作步数标识");
#else
  CString strRampStepIndex = g_sLangTxt_Native_StepChangeID;
#endif

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp + strRampStepIndex;

        strID.Format("RampStepIndexBin%d",(nIndex+1));
        pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",oStateResult.m_nRampIndex[nIndex]);
    }

    if (g_nBinExCount>0)
    {
#ifdef NOT_USE_XLANGUAGE
        CString str1Ex = _T("开入扩展");
#else
    CString str1Ex = g_sLangTxt_Native_InputExpand;
#endif
        CSttXmlSerializeBase *pXmlStateBinEx = pStateSerialize->xml_serialize("StateBinEx", "StateBinEx", "StateBinEx", stt_ParaGroupKey());

        if (pXmlStateBinEx != NULL)
        {
#ifdef NOT_USE_XLANGUAGE
            CString strDesc = _T("动作描述");
#else
      CString strDesc = g_sLangTxt_Native_ActionDesc;
#endif
            int nBinExCount = g_nBinExCount;//20230409 zhouhj
            int nAct[MAX_ExBINARY_COUNT];

            if (nBinExCount>MAX_ExBINARY_COUNT)
            {
                nBinExCount = MAX_ExBINARY_COUNT;
            }

            for(int nIndex = 0;nIndex<nBinExCount;nIndex++)
            {
                strTemp.Format(_T("%d"),nIndex+1);
                strName = str1Ex + strTemp + strDesc;
                strID.Format("ActBinEx%d",(nIndex+1));
                nAct[nIndex] = 0;

//                if(oStateResult.m_nAct == 1)
                {
                    if ((nBinTripRef == 1)&&(oStateResult.m_nBinExFirstChgState[nIndex] == pnFirstBinExInitState[nIndex]))//如果是以第一态为参考, 并且与第一台初始值不一致
                    {
                        nAct[nIndex] = (oStateResult.m_nrBinExSwitchCount[nIndex] > 1);
                    }
                    else
                    {
                        nAct[nIndex] = (oStateResult.m_nrBinExSwitchCount[nIndex] > 0);
                    }
                }

                pXmlStateBinEx->xml_serialize(strName.GetString(),strID.GetString(),"","number",nAct[nIndex]);
            }

            float fTtripBinEx;

            for(int nIndex = 0; nIndex < nBinExCount; nIndex++)
            {
                strTemp.Format(_T("%d"),nIndex+1);
                strName = str1Ex + strTemp + str2;

                strID.Format("TtripBinEx%d",(nIndex+1));
                fTtripBinEx = 0;

                if(nAct[nIndex] == 1)
                {
                    if(oParaState.m_binInEx[nIndex].nSelect == 1)
                    {
                        if(nStateIndex == 1)
                        {
                            fTtripBinEx = oStateResult.m_frTimeBinExAct[nIndex][0];
                        }
                        else
                        {
                            if ((nBinTripRef == 1)&&(oStateResult.m_nBinExFirstChgState[nIndex] == pnFirstBinExInitState[nIndex]))
                            {
                                fTtripBinEx = oStateResult.m_frTimeBinExAct[nIndex][1];
                            }
                            else
                            {
                                fTtripBinEx = oStateResult.m_frTimeBinExAct[nIndex][0];
                            }
                        }
                    }
                }

                pXmlStateBinEx->xml_serialize(strName.GetString(),strID.GetString(),"","number",fTtripBinEx);
            }

            for(int nIndex = 0; nIndex < nBinExCount; nIndex++)
            {
                strTemp.Format(_T("%d"),nIndex+1);
                strName = str1Ex + strTemp + strRampStepIndex;
                strID.Format("RampStepIndexBinEx%d",(nIndex+1));
                pXmlStateBinEx->xml_serialize(strName.GetString(),strID.GetString(),"","number",oStateResult.m_nRampIndexEx[nIndex]);
            }
        }
    }

    stt_xml_serialize_act_rcd(&oStateResult,pStateSerialize);
}

void stt_xml_serialize(tmt_StateResults *pResults,tmt_StateParas *pStateParas,int nStateNums, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef)
{
    BOOL bUseErr[10];
    for (int i=0; i < 10; i++)
    {
        if(pStateParas->m_paraEstimates[i].m_bUseError)
        {
            bUseErr[i] = TRUE;
        }
        else
        {
            bUseErr[i] = FALSE;
        }
    }
    stt_xml_serialize_common(pResults, bUseErr, pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("当前循环的序号","LoopIndex","","long",pResults->m_nLoopIndex);
#else
  pXmlSierialize->xml_serialize(/* "当前循环的序号" */ g_sLangTxt_Native_CurrLoop.GetString(), "LoopIndex", "", "long", pResults->m_nLoopIndex);
#endif
    long nStateCount = 0;
    for (int nIndex=0; nIndex < g_nStateCount; nIndex++)
    {
        if(pStateParas->m_paraState[nIndex].m_bSelected)
        {
            stt_xml_serialize(pResults->m_resultState[nIndex], pStateParas->m_paraState[nIndex],nIndex, pXmlSierialize,nBinTripRef,pResults->m_nBinRefState,
                              pResults->m_nBinExRefState);
            nStateCount++;
            if(nStateCount == nStateNums)
            {
                break;
            }
        }
    }
}

void stt_xml_serialize_statenUnI_pnv(tmt_StateResults *pResults,tmt_StateParas *pStateParas,int nStateNums, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef)
{
    BOOL bUseErr[10];
    for (int i=0; i < 10; i++)
    {
		if(pStateParas->m_paraEstimates[i].m_bUseError)
        {
            bUseErr[i] = TRUE;
        }
        else
        {
            bUseErr[i] = FALSE;
        }
    }
    stt_xml_serialize_common(pResults, bUseErr, pXmlSierialize);
	for (int nIndex=0; nIndex<nStateNums && nIndex < g_nStateCount; nIndex++)
    {
		stt_xml_serialize_statenUnI_pnv(pResults->m_resultState[nIndex], pStateParas->m_paraState[nIndex],nIndex+1, pXmlSierialize,nBinTripRef,pResults->m_nBinRefState,
                                        pResults->m_nBinExRefState);
    }
}

#include"../../SttCmd/SttTestCmd.h"
#include"tmt_state_test.h"
#include"../../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_StateTest()
{
    tmt_StateTest oStateTest;
    oStateTest.init(10);
    oStateTest.m_oStateParas.m_nStateNumbers = 10;
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    g_nBinExCount = 60;
    g_nBoutExCount = 60;
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    CSttXmlSerializeBase *pMacroResults = oSttXmlSerializeTool.GetMacroResults();
    stt_xml_serialize(&oStateTest.m_oStateResults,&oStateTest.m_oStateParas,10, pMacroResults,0);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("StateTestDemo.xml");
    //  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

//////////////////////////////////////////////////////////////////////////
//

tmt_StatePara* stt_state_paras_insert_after(tmt_StateParas *pParas, tmt_StatePara *pSrc, int nAfter)
{
    if (nAfter >= pParas->m_nStateNumbers || nAfter < 0)
    {
        return NULL;
    }

    if (pParas->m_nStateNumbers >= g_nStateCount)
    {
        return NULL;
    }

    int nIndex = 0;

    for (nIndex=pParas->m_nStateNumbers; nIndex > nAfter+1; nIndex--)
    {
        pParas->m_paraState[nIndex] = pParas->m_paraState[nIndex-1];
    }

    if (pSrc != NULL)
    {
        tmt_StatePara *pDst = new tmt_StatePara;
        memcpy(pDst,pSrc,sizeof(tmt_StatePara));
        pParas->m_paraState[nAfter+1] = *pDst;
    }
    else
    {
        tmt_StatePara *pDst = new tmt_StatePara;
        pParas->m_paraState[nAfter+1] = *pDst;
    }

    pParas->m_nStateNumbers++;

    return &pParas->m_paraState[nAfter+1];
}

tmt_StatePara* stt_state_paras_insert_before(tmt_StateParas *pParas, tmt_StatePara *pSrc, int nBefore)
{
    if (nBefore >= pParas->m_nStateNumbers || nBefore < 0)
    {
        return NULL;
    }

    if (pParas->m_nStateNumbers >= g_nStateCount)
    {
        return NULL;
    }

    int nIndex = 0;

    for (nIndex=pParas->m_nStateNumbers; nIndex > nBefore; nIndex--)
    {
        pParas->m_paraState[nIndex] = pParas->m_paraState[nIndex-1];
    }

    if (pSrc != NULL)
    {
        tmt_StatePara *pDst = new tmt_StatePara;
        memcpy(pDst,pSrc,sizeof(tmt_StatePara));
        pParas->m_paraState[nBefore] = *pDst;
    }
    else
    {
        tmt_StatePara *pDst = new tmt_StatePara;
        pParas->m_paraState[nBefore] = *pDst;
    }

    pParas->m_nStateNumbers++;

    return &pParas->m_paraState[nBefore];
}

void stt_state_paras_delete(tmt_StateParas *pParas, int nIndex)
{
    if (nIndex >= pParas->m_nStateNumbers || nIndex < 0)
    {
        return;
    }

    for (int i=nIndex+1; i<pParas->m_nStateNumbers; i++)
    {
        pParas->m_paraState[i-1] = pParas->m_paraState[i];
    }

    pParas->m_nStateNumbers--;
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_state_test *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,long nHarmCount, bool bSmvAbnormal, bool bGooseAbnormal)
{
    //	stt_xml_serialize((PTMT_PARAS_HEAD)pParas, pXmlSierialize);

    CSttXmlSerializeBase *pXmlParas = pXmlSierialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas  != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_serialize_ex2(&pParas->m_oStateParas, pXmlParas,nVolRsNum,nCurRsNum,FALSE,nHarmCount,bSmvAbnormal, bGooseAbnormal);
        }
        else
        {
            stt_xml_serialize_ex2(&pParas->m_oStateParas, pXmlParas,nVolRsNum,nCurRsNum,TRUE,nHarmCount,bSmvAbnormal, bGooseAbnormal);
        }
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSierialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults  != NULL)
    {
                // 20240223 suayng 重新打开模板重新更新状态数
		if(stt_xml_serialize_is_read(pXmlParas)|| stt_xml_serialize_is_register(pXmlParas) )
		{
			 pParas->m_oStateResults.init(pParas->m_oStateParas.m_nStateNumbers);
		}
        stt_xml_serialize(&pParas->m_oStateResults, &pParas->m_oStateParas, pParas->m_oStateParas.m_nStateNumbers,pXmlResults,pParas->m_oStateParas.m_nBinTripRef);
    }

    return pXmlParas;
}


CSttXmlSerializeBase* stt_xml_serialize(tmt_state_test *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,long nHarmCount)
{
    return stt_xml_serialize(pParas,pXmlSierialize,nVolRsNum,nCurRsNum,nHarmCount,true,true);
}

