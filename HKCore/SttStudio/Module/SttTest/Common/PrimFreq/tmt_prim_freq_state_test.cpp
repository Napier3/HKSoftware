#include "stdafx.h"
#include "tmt_prim_freq_state_test.h"
#include "../tmt_system_config.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///
///

void stt_xml_serialize_binary_out(tmt_PrimFreqStatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize_binary_in(tmt_PrimFreqStatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize_gradient(tmt_PrimFreqStatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
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


void stt_xml_serialize_ex(tmt_channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize, const char *pszDataTypeID)
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

}


void stt_xml_serialize(tmt_PrimFreqStatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("状态", "state", nIndex, "State", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pStateSerialize = pXmlSierialize->xml_serialize(/* "状态" */ g_sLangTxt_Status.GetString(), "state", nIndex, "State", stt_ParaGroupKey());
#endif

    if (pStateSerialize == NULL)
    {
		return;
    }

    if(stt_xml_serialize_is_read(pStateSerialize))
    {
#ifdef _PSX_QT_LINUX_
        oStatePara.init();
#endif
    }

#ifdef NOT_USE_XLANGUAGE
    pStateSerialize->xml_serialize("触发方式", "EndMode","","StateEndMode_PSUAuto",oStatePara.m_nTriggerCondition);
    pStateSerialize->xml_serialize("输出时间", "LastT","s","number",oStatePara.m_fTimeState);
    pStateSerialize->xml_serialize("触发后保持时间", "EndDelayT","s","number",oStatePara.m_fTimeAfterTrigger);
    pStateSerialize->xml_serialize("开出量保持时间", "OutputHoldT","s","number",oStatePara.m_fOutputHoldTime);

	pStateSerialize->xml_serialize("描述", "Name", "", "string", oStatePara.m_strName);
	pStateSerialize->xml_serialize("ID", "ID", "", "string", oStatePara.m_strID);

    pStateSerialize->xml_serialize("GPS触发时刻（时）", "GpsH"," ","number",oStatePara.m_tGps.nHour);
    pStateSerialize->xml_serialize("GPS触发时刻（分）", "GpsM"," ","number",oStatePara.m_tGps.nMinutes);
    pStateSerialize->xml_serialize("GPS触发时刻（秒）", "GpsS"," ","number",oStatePara.m_tGps.nSeconds);
    pStateSerialize->xml_serialize("递变时间分度(ms)", "RampTimeGrad"," ","number",oStatePara.m_nRampTimeGrad);
	pStateSerialize->xml_serialize("开出模式选择", "BinaryOutType"," ","number",oStatePara.m_nBinaryOutType);//0-开出+Gse,1-只有开出,2-只有Gse
	pStateSerialize->xml_serialize("IDc1", "IDc1", "mA", "number", oStatePara.m_frCurrentDc[0]);
	pStateSerialize->xml_serialize("IDc2", "IDc2", "mA", "number", oStatePara.m_frCurrentDc[1]);

#else
  pStateSerialize->xml_serialize(/* "触发方式" */ g_sLangTxt_Native_TrigMode.GetString(), "EndMode", "", "StateEndMode_PSUAuto", oStatePara.m_nTriggerCondition);
  pStateSerialize->xml_serialize(/* "输出时间" */ g_sLangTxt_Native_OutTime.GetString(), "LastT", "s", "number", oStatePara.m_fTimeState);
  pStateSerialize->xml_serialize(/* "触发后保持时间" */ g_sLangTxt_Native_TrigHoldTime.GetString(), "EndDelayT", "s", "number", oStatePara.m_fTimeAfterTrigger);
  pStateSerialize->xml_serialize(/* "开出量保持时间" */ g_sLangTxt_Native_OutHoldTime.GetString(), "OutputHoldT", "s", "number", oStatePara.m_fOutputHoldTime);
  pStateSerialize->xml_serialize(/* "描述" */ g_sLangTxt_State_Description.GetString(), "Name", "", "string", oStatePara.m_strName);
  pStateSerialize->xml_serialize("ID", "ID", "", "string", oStatePara.m_strID);
  pStateSerialize->xml_serialize("IDc1", "IDc1", "mA", "number", oStatePara.m_frCurrentDc[0]);
  pStateSerialize->xml_serialize("IDc2", "IDc2", "mA", "number", oStatePara.m_frCurrentDc[1]);

  pStateSerialize->xml_serialize(/* "GPS触发时刻（时）" */ g_sLangTxt_Native_GPSTriggerHour.GetString(), "GpsH", " ", "number", oStatePara.m_tGps.nHour);
  pStateSerialize->xml_serialize(/* "GPS触发时刻（分）" */ g_sLangTxt_Native_GPSTriggerMinute.GetString(), "GpsM", " ", "number", oStatePara.m_tGps.nMinutes);
  pStateSerialize->xml_serialize(/* "GPS触发时刻（秒）" */ g_sLangTxt_Native_GPSTriggerSecond.GetString(), "GpsS", " ", "number", oStatePara.m_tGps.nSeconds);
  pStateSerialize->xml_serialize(/* "递变时间分度(ms)" */ g_sLangTxt_Native_GradualTimeScale.GetString(), "RampTimeGrad", " ", "number", oStatePara.m_nRampTimeGrad);
#endif

    if (stt_xml_serialize_is_read(pXmlSierialize))//兼容PsuVm，重新启用
    {
        stt_xml_serialize_gradient(oStatePara, pStateSerialize);  // 采用新的方式
    }
}

void stt_xml_serialize_ex(tmt_PrimFreqStatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize,long nVolRsNum,long nCurRsNum)
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
	pStateSerialize->xml_serialize("ID", "ID", "", "string", oStatePara.m_strID);

    pStateSerialize->xml_serialize("GPS触发时刻（时）", "GpsH"," ","number",oStatePara.m_tGps.nHour);
    pStateSerialize->xml_serialize("GPS触发时刻（分）", "GpsM"," ","number",oStatePara.m_tGps.nMinutes);
    pStateSerialize->xml_serialize("GPS触发时刻（秒）", "GpsS"," ","number",oStatePara.m_tGps.nSeconds);
    pStateSerialize->xml_serialize("递变时间分度(ms)", "RampTimeGrad"," ","number",oStatePara.m_nRampTimeGrad);
	pStateSerialize->xml_serialize("IDc1", "IDc1", "mA", "number", oStatePara.m_frCurrentDc[0]);
	pStateSerialize->xml_serialize("IDc2", "IDc2", "mA", "number", oStatePara.m_frCurrentDc[1]);

#else
  pStateSerialize->xml_serialize(/* "触发方式" */ g_sLangTxt_Native_TrigMode.GetString(), "EndMode", "", "StateEndMode_PSUAuto", oStatePara.m_nTriggerCondition);
  pStateSerialize->xml_serialize(/* "输出时间" */ g_sLangTxt_Native_OutTime.GetString(), "LastT", "s", "number", oStatePara.m_fTimeState);
  pStateSerialize->xml_serialize(/* "触发后保持时间" */ g_sLangTxt_Native_TrigHoldTime.GetString(), "EndDelayT", "s", "number", oStatePara.m_fTimeAfterTrigger);
  pStateSerialize->xml_serialize(/* "开出量保持时间" */ g_sLangTxt_Native_OutHoldTime.GetString(), "OutputHoldT", "s", "number", oStatePara.m_fOutputHoldTime);

  pStateSerialize->xml_serialize(/* "是否直流" */ g_sLangTxt_Native_IsDC.GetString(), "bDC", "", "BOOL", oStatePara.m_bDC);
  pStateSerialize->xml_serialize(/* "是否选择" */ g_sLangTxt_Native_IsSelected.GetString(), "bSelect", "", "BOOL", oStatePara.m_bSelected);
  pStateSerialize->xml_serialize(/* "描述" */ g_sLangTxt_State_Description.GetString(), "Name", "", "string", oStatePara.m_strName);
  pStateSerialize->xml_serialize("ID", "ID", "", "string", oStatePara.m_strID);

  pStateSerialize->xml_serialize(/* "GPS触发时刻（时）" */ g_sLangTxt_Native_GPSTriggerHour.GetString(), "GpsH", " ", "number", oStatePara.m_tGps.nHour);
  pStateSerialize->xml_serialize(/* "GPS触发时刻（分）" */ g_sLangTxt_Native_GPSTriggerMinute.GetString(), "GpsM", " ", "number", oStatePara.m_tGps.nMinutes);
  pStateSerialize->xml_serialize(/* "GPS触发时刻（秒）" */ g_sLangTxt_Native_GPSTriggerSecond.GetString(), "GpsS", " ", "number", oStatePara.m_tGps.nSeconds);
  pStateSerialize->xml_serialize(/* "递变时间分度(ms)" */ g_sLangTxt_Native_GradualTimeScale.GetString(), "RampTimeGrad", " ", "number", oStatePara.m_nRampTimeGrad);
  pStateSerialize->xml_serialize("IDc1", "IDc1", "mA", "number", oStatePara.m_frCurrentDc[0]);
  pStateSerialize->xml_serialize("IDc2", "IDc2", "mA", "number", oStatePara.m_frCurrentDc[1]);

#endif
  CString strID;
  //	int nIDCnt  =  (DIGITAL_CHANNEL_MAX/2)  +  8;// mym 2021-6-24 加了个 8

  for(int nIndex=0;nIndex<nVolRsNum;nIndex++)
  {
	  strID.Format(_T("U%d"),nIndex+1);
	  stt_xml_serialize_ex(&oStatePara.m_uiVOL[nIndex], strID.GetString(),pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
  }

  for(int nIndex=0;nIndex<nCurRsNum;nIndex++)
  {
	  strID.Format(_T("I%d"),nIndex+1);
	  stt_xml_serialize_ex(&oStatePara.m_uiCUR[nIndex], strID.GetString(),pStateSerialize,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
  }

  stt_xml_serialize_binary_in(oStatePara, pStateSerialize);
  stt_xml_serialize_binary_out(oStatePara, pStateSerialize);

}

void stt_xml_serialize_common(tmt_PrimFreqStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize(tmt_PrimFreqStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
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
    for (nIndex=0; nIndex < nStateCount; nIndex++)
    {
        if(stt_xml_serialize_is_read(pXmlSierialize))
        {
                pParas->m_paraPrimFreqState[nIndex].m_bSelected = FALSE;
			stt_xml_serialize(pParas->m_paraPrimFreqState[nIndex], nIndex, pXmlSierialize);
        }
        else
        {
            if(pParas->m_paraPrimFreqState[nIndex].m_bSelected)
            {
                stt_xml_serialize(pParas->m_paraPrimFreqState[nIndex], nIndex, pXmlSierialize);
            }
        }
    }
}

//bSel=true,则
void stt_xml_serialize_ex(tmt_PrimFreqStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,bool bSel)
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
            if (pParas->m_paraPrimFreqState[i].m_bSelected)
            {
                stt_xml_serialize(pParas->m_paraPrimFreqState[i], nIndex, pXmlSierialize);
                nIndex++;
            }
        }
        else
        {
            stt_xml_serialize(pParas->m_paraPrimFreqState[i], nIndex, pXmlSierialize);
            nIndex++;
        }
    }
}

//bSel=true,则
void stt_xml_serialize_ex2(tmt_PrimFreqStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,bool bSel)
{
	bool bRead = stt_xml_serialize_is_read(pXmlSierialize);
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
            if (pParas->m_paraPrimFreqState[i].m_bSelected)
            {
                stt_xml_serialize_ex(pParas->m_paraPrimFreqState[i], nIndex, pXmlSierialize,nVolRsNum,nCurRsNum);
                nIndex++;
            }
        }
        else
        {
            stt_xml_serialize_ex(pParas->m_paraPrimFreqState[i], nIndex, pXmlSierialize,nVolRsNum,nCurRsNum);
            nIndex++;
        }
    }
}


void stt_xml_serialize_act_rcd(tmt_PrimFreqStateResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//动作记录,最大64次,根据实际动作情况,上送总的动作信息
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

void stt_xml_serialize(tmt_PrimFreqStateResult &oStateResult, tmt_PrimFreqStatePara* pParaState, long nStateIndex, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef,int *pnFirstBinInitState,int *pnFirstBinExInitState)
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
    int nAct[MAX_BINARYIN_COUNT];
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
            if(pParaState->m_binIn[nIndex].nSelect == 1)
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
                    if(pParaState->m_binInEx[nIndex].nSelect == 1)
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


void stt_xml_serialize_common(tmt_PrimFreqStateResults *pResults, BOOL *bUseErr, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize(tmt_PrimFreqStateResults *pResults,tmt_PrimFreqStateParas *pStateParas,int nStateNums, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef)
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
        if(pStateParas->m_paraPrimFreqState[nIndex].m_bSelected)
        {
			tmt_PrimFreqStatePara *pPara = (tmt_PrimFreqStatePara *)&pStateParas->m_paraPrimFreqState[nIndex];
            stt_xml_serialize(pResults->m_resultState[nIndex], /*pStateParas->m_paraPrimFreqState[nIndex]*/pPara,nIndex,
				pXmlSierialize,nBinTripRef,pResults->m_nBinRefState,pResults->m_nBinExRefState);
            nStateCount++;
            if(nStateCount == nStateNums)
            {
                break;
            }
        }
    }
}

#include"../../../SttCmd/SttTestCmd.h"
#include"tmt_prim_freq_state_test.h"
#include"../../../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_PrimFreqStateTest()
{
    tmt_PrimFreqStateTest oStateTest;
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
    strXMLPath += ("PrimFreqStateTestDemo.xml");
    //  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

//////////////////////////////////////////////////////////////////////////
//

tmt_PrimFreqStatePara* stt_prim_freq_state_paras_insert_after(tmt_PrimFreqStateParas *pParas, tmt_PrimFreqStatePara *pSrc, int nAfter)
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
        pParas->m_paraPrimFreqState[nIndex] = pParas->m_paraPrimFreqState[nIndex-1];
    }
	
	for (nIndex = nAfter + 1; nIndex  < pParas->m_nStateNumbers; nIndex++)
	{
		strcpy(pParas->m_paraPrimFreqState[nIndex].m_strID, pParas->m_paraPrimFreqState[nIndex + 1].m_strID);
	}

    if (pSrc != NULL)
    {
        tmt_PrimFreqStatePara *pDst = new tmt_PrimFreqStatePara;
        memcpy(pDst,pSrc,sizeof(tmt_PrimFreqStatePara));
        pParas->m_paraPrimFreqState[nAfter+1] = *pDst;
    }
    else
    {
        tmt_PrimFreqStatePara *pDst = new tmt_PrimFreqStatePara;
        pParas->m_paraPrimFreqState[nAfter+1] = *pDst;
    }

    pParas->m_nStateNumbers++;

    return (tmt_PrimFreqStatePara*)&pParas->m_paraPrimFreqState[nAfter+1];
}

tmt_PrimFreqStatePara* stt_prim_freq_state_paras_insert_before(tmt_PrimFreqStateParas *pParas, tmt_PrimFreqStatePara *pSrc, int nBefore)
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
        pParas->m_paraPrimFreqState[nIndex] = pParas->m_paraPrimFreqState[nIndex-1];
    }

    if (pSrc != NULL)
    {
        tmt_PrimFreqStatePara *pDst = new tmt_PrimFreqStatePara;
        memcpy(pDst,pSrc,sizeof(tmt_PrimFreqStatePara));
        pParas->m_paraPrimFreqState[nBefore] = *pDst;
    }
    else
    {
        tmt_PrimFreqStatePara *pDst = new tmt_PrimFreqStatePara;
        pParas->m_paraPrimFreqState[nBefore] = *pDst;
    }

    pParas->m_nStateNumbers++;

    return (tmt_PrimFreqStatePara*)&pParas->m_paraPrimFreqState[nBefore];
}

void stt_prim_freq_state_paras_delete(tmt_PrimFreqStateParas *pParas, int nIndex)
{
    if (nIndex >= pParas->m_nStateNumbers || nIndex < 0)
    {
        return;
    }

    for (int i=nIndex+1; i<pParas->m_nStateNumbers; i++)
    {
        pParas->m_paraPrimFreqState[i-1] = pParas->m_paraPrimFreqState[i];
    }

    pParas->m_nStateNumbers--;
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_PrimFreqStateTest *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum)
{
    //	stt_xml_serialize((PTMT_PARAS_HEAD)pParas, pXmlSierialize);

    CSttXmlSerializeBase *pXmlParas = pXmlSierialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas  != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_serialize_ex2(&pParas->m_oStateParas, pXmlParas,nVolRsNum,nCurRsNum,FALSE);
        }
        else
        {
            stt_xml_serialize_ex2(&pParas->m_oStateParas, pXmlParas,nVolRsNum,nCurRsNum,TRUE);
        }
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSierialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults  != NULL)
    {
		if(stt_xml_serialize_is_read(pXmlParas)|| stt_xml_serialize_is_register(pXmlParas) )
		{
			 pParas->m_oStateResults.init(pParas->m_oStateParas.m_nStateNumbers);
		}
        stt_xml_serialize(&pParas->m_oStateResults, &pParas->m_oStateParas, pParas->m_oStateParas.m_nStateNumbers,pXmlResults,pParas->m_oStateParas.m_nBinTripRef);
    }

    return pXmlParas;
}
