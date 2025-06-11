#include "stdafx.h"
#include "tmt_abnormal_test.h"
#include "../../../../../Module/API/StringApi.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_SMVSourceParaSet(tmt_SmvAbnormalMsg *pSmvAbnormalMsg, CSttXmlSerializeBase *pSmvParasSerializeBase)
{
	CSttXmlSerializeBase *pSMVSourceParaSetSerialize = pSmvParasSerializeBase->xml_serialize("SV原始报文参数", "SMVSourceParaSet", "SmvSourcePara", stt_ParaGroupKey());

	if (pSMVSourceParaSetSerialize == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE

	pSMVSourceParaSetSerialize->xml_serialize("设置原始报文","UseOrigPkgSet","","number",pSmvAbnormalMsg->m_nUseOrigPkgSet);
	pSMVSourceParaSetSerialize->xml_serialize("源Mac地址","SrcMAC","","string",pSmvAbnormalMsg->m_strMacAddrSrc);
	pSMVSourceParaSetSerialize->xml_serialize("目的Mac地址","DstMAC","","string",pSmvAbnormalMsg->m_strMacAddrDst);
	pSMVSourceParaSetSerialize->xml_serialize("VlanID","VlanID","","number",pSmvAbnormalMsg->m_nVLanID);
	pSMVSourceParaSetSerialize->xml_serialize("VLanPriority","VlanPriority","","number",pSmvAbnormalMsg->m_nVLanPriority);
	pSMVSourceParaSetSerialize->xml_serialize("网络标识","NetID","","number",pSmvAbnormalMsg->m_nNetType);
	pSMVSourceParaSetSerialize->xml_serialize("APPID","AppID","","number",pSmvAbnormalMsg->m_nAppID);
	pSMVSourceParaSetSerialize->xml_serialize("同步方式","SynMode","","SmvSynMode",pSmvAbnormalMsg->m_nSyn);
	pSMVSourceParaSetSerialize->xml_serialize("版本号","VersionNo","","number",pSmvAbnormalMsg->m_nVersion);
	pSMVSourceParaSetSerialize->xml_serialize("DataSet","DataSet","","string",pSmvAbnormalMsg->m_strDataset);
	pSMVSourceParaSetSerialize->xml_serialize("SVID","SVID","","string",pSmvAbnormalMsg->m_strSVID);
#else
	pSMVSourceParaSetSerialize->xml_serialize(/* "设置原始报文" */ g_sLangTxt_Native_SetOrigMsg.GetString(), "UseOrigPkgSet", "", "number", pSmvAbnormalMsg->m_nUseOrigPkgSet);
    pSMVSourceParaSetSerialize->xml_serialize(/* "源Mac地址" */ g_sLangTxt_IEC_Source.GetString(), "SrcMAC", "", "string", pSmvAbnormalMsg->m_strMacAddrSrc);
    pSMVSourceParaSetSerialize->xml_serialize(/* "目的Mac地址" */ g_sLangTxt_Native_DestMacAddr.GetString(), "DstMAC", "", "string", pSmvAbnormalMsg->m_strMacAddrDst);
    pSMVSourceParaSetSerialize->xml_serialize("VlanID", "VlanID", "", "number", pSmvAbnormalMsg->m_nVLanID);
    pSMVSourceParaSetSerialize->xml_serialize("VLanPriority", "VlanPriority", "", "number", pSmvAbnormalMsg->m_nVLanPriority);
    pSMVSourceParaSetSerialize->xml_serialize(/* "网络标识" */ g_sLangTxt_Native_Netid.GetString(), "NetID", "", "number", pSmvAbnormalMsg->m_nNetType);
    pSMVSourceParaSetSerialize->xml_serialize("APPID", "AppID", "", "number", pSmvAbnormalMsg->m_nAppID);
    pSMVSourceParaSetSerialize->xml_serialize(/* "同步方式" */ g_sLangTxt_IEC_Synchronously.GetString(), "SynMode", "", "SmvSynMode", pSmvAbnormalMsg->m_nSyn);
    pSMVSourceParaSetSerialize->xml_serialize(/* "版本号" */ g_sLangTxt_IEC_Version.GetString(), "VersionNo", "", "number", pSmvAbnormalMsg->m_nVersion);
    pSMVSourceParaSetSerialize->xml_serialize("DataSet", "DataSet", "", "string", pSmvAbnormalMsg->m_strDataset);
    pSMVSourceParaSetSerialize->xml_serialize("SVID", "SVID", "", "string", pSmvAbnormalMsg->m_strSVID);

#endif
}

void stt_xml_serialize_FlyPointSet(tmt_StateAbnormalSMV *pAbnormalSMV, CSttXmlSerializeBase *pSmvParasSerializeBase)
{
	CSttXmlSerializeBase *pFlyPointSetSerialize = pSmvParasSerializeBase->xml_serialize("飞点", "FlyPointSet", "FlyPtSet", stt_ParaGroupKey());

	if (pFlyPointSetSerialize == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pFlyPointSetSerialize->xml_serialize("飞点电压值","FlyPointValue_U","","number",pAbnormalSMV->m_fFlyPointVolt);
	pFlyPointSetSerialize->xml_serialize("飞点电流值","FlyPointValue_I","","number",pAbnormalSMV->m_fFlyPointCurrent);
	pFlyPointSetSerialize->xml_serialize("飞点电压Ua使能","SelFlyUa","","number",pAbnormalSMV->m_nVolChEnable[0]);
	pFlyPointSetSerialize->xml_serialize("飞点电压Ub使能","SelFlyUb","","number",pAbnormalSMV->m_nVolChEnable[1]);
	pFlyPointSetSerialize->xml_serialize("飞点电压Uc使能","SelFlyUc","","number",pAbnormalSMV->m_nVolChEnable[2]);
	pFlyPointSetSerialize->xml_serialize("飞点电流Ia使能","SelFlyIa","","number",pAbnormalSMV->m_nCurChEnable[0]);
	pFlyPointSetSerialize->xml_serialize("飞点电流Ib使能","SelFlyIb","","number",pAbnormalSMV->m_nCurChEnable[1]);
	pFlyPointSetSerialize->xml_serialize("飞点电流Ic使能","SelFlyIc","","number",pAbnormalSMV->m_nCurChEnable[2]);
#else
    pFlyPointSetSerialize->xml_serialize(/* "飞点电压值" */ g_sLangTxt_Native_FlyPntVolt.GetString(), "FlyPointValue_U", "", "number", pAbnormalSMV->m_fFlyPointVolt);
    pFlyPointSetSerialize->xml_serialize(/* "飞点电流值" */ g_sLangTxt_Native_FlyPntCurr.GetString(), "FlyPointValue_I", "", "number", pAbnormalSMV->m_fFlyPointCurrent);
    pFlyPointSetSerialize->xml_serialize(/* "飞点电压Ua使能" */ g_sLangTxt_Native_FlyPntVoltUaEn.GetString(), "SelFlyUa", "", "number", pAbnormalSMV->m_nVolChEnable[0]);
    pFlyPointSetSerialize->xml_serialize(/* "飞点电压Ub使能" */ g_sLangTxt_Native_FlyPntVoltUbEn.GetString(), "SelFlyUb", "", "number", pAbnormalSMV->m_nVolChEnable[1]);
    pFlyPointSetSerialize->xml_serialize(/* "飞点电压Uc使能" */ g_sLangTxt_Native_FlyPntVoltUcEn.GetString(), "SelFlyUc", "", "number", pAbnormalSMV->m_nVolChEnable[2]);
    pFlyPointSetSerialize->xml_serialize(/* "飞点电流Ia使能" */ g_sLangTxt_Native_FlyPntCurrIaEn.GetString(), "SelFlyIa", "", "number", pAbnormalSMV->m_nCurChEnable[0]);
    pFlyPointSetSerialize->xml_serialize(/* "飞点电流Ib使能" */ g_sLangTxt_Native_FlyPntCurrIbEn.GetString(), "SelFlyIb", "", "number", pAbnormalSMV->m_nCurChEnable[1]);
    pFlyPointSetSerialize->xml_serialize(/* "飞点电流Ic使能" */ g_sLangTxt_Native_FlyPntCurrIcEn.GetString(), "SelFlyIc", "", "number", pAbnormalSMV->m_nCurChEnable[2]);
#endif
}

void stt_xml_serialize_FrampShakingSet(tmt_StateAbnormalSMV *pAbnormalSMV, CSttXmlSerializeBase *pSmvParasSerializeBase)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pFrampShakingSetSerialize = pSmvParasSerializeBase->xml_serialize("抖动", "FrampShakingSet", "FrampShaking", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pFrampShakingSetSerialize = pSmvParasSerializeBase->xml_serialize( /* "抖动" */ g_sLangTxt_State_Dithering.GetString(), "FrampShakingSet", "FrampShaking", stt_ParaGroupKey());
#endif
	if (pFrampShakingSetSerialize == NULL)
	{
		return;
	}

#ifdef NOT_USE_XLANGUAGE
	pFrampShakingSetSerialize->xml_serialize("抖动值(单位ns)","FrampShakingValue","","number",pAbnormalSMV->m_uFrampShakingValue);
#else
  pFrampShakingSetSerialize->xml_serialize(/* "抖动值(单位ns)" */ g_sLangTxt_Native_JitterValns.GetString(), "FrampShakingValue", "", "number", pAbnormalSMV->m_uFrampShakingValue);
#endif

}

void stt_xml_serialize_OutOfOrderSet(tmt_StateAbnormalSMV *pAbnormalSMV, CSttXmlSerializeBase *pSmvParasSerializeBase)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pOutOfOrderSetSerialize = pSmvParasSerializeBase->xml_serialize("错序", "OutOfOrderSet", "OutOfOrder", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pOutOfOrderSetSerialize = pSmvParasSerializeBase->xml_serialize( /* "错序" */ g_sLangTxt_State_OutofOrder.GetString(), "OutOfOrderSet", "OutOfOrder", stt_ParaGroupKey());
#endif

	if (pOutOfOrderSetSerialize == NULL)
	{
		return;
	}

#ifdef NOT_USE_XLANGUAGE
	pOutOfOrderSetSerialize->xml_serialize("跳变值","OutOfOrderValue","","number",pAbnormalSMV->m_nOutOfOrderValue);
#else
  pOutOfOrderSetSerialize->xml_serialize(/* "跳变值" */ g_sLangTxt_Native_JumpVal.GetString(), "OutOfOrderValue", "", "number", pAbnormalSMV->m_nOutOfOrderValue);
#endif
}

void stt_xml_serialize_DelayDeviationSet(tmt_StateAbnormalSMV *pAbnormalSMV, CSttXmlSerializeBase *pSmvParasSerializeBase)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pDelayDeviationSetSerialize = pSmvParasSerializeBase->xml_serialize("延时偏差", "DelayDeviationSet", "DelayDeviation", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pDelayDeviationSetSerialize = pSmvParasSerializeBase->xml_serialize(/* "延时偏差" */ g_sLangTxt_Native_DelayDev.GetString(), "DelayDeviationSet", "DelayDeviation", stt_ParaGroupKey());
#endif

	if (pDelayDeviationSetSerialize == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pDelayDeviationSetSerialize->xml_serialize("偏差时间","DeviationValue","us","number",pAbnormalSMV->m_nDelayDeviation);
#else
  pDelayDeviationSetSerialize->xml_serialize(/* "偏差时间" */ g_sLangTxt_Native_DevTime.GetString(), "DeviationValue", "us", "number", pAbnormalSMV->m_nDelayDeviation);
#endif
}

void stt_xml_serialize_DelayChangeSet(tmt_StateAbnormalSMV *pAbnormalSMV, CSttXmlSerializeBase *pSmvParasSerializeBase)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pDelayChangeSetSerialize = pSmvParasSerializeBase->xml_serialize("延时变化", "DelayChangeSet", "DelayChange", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pDelayChangeSetSerialize = pSmvParasSerializeBase->xml_serialize( /* "延时变化" */ g_sLangTxt_Native_DelayVar.GetString(), "DelayChangeSet", "DelayChange", stt_ParaGroupKey());
#endif

	if (pDelayChangeSetSerialize == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pDelayChangeSetSerialize->xml_serialize("延时时间","DelayChangeValue","us","number",pAbnormalSMV->m_nDelayChangeValue);
#else
  pDelayChangeSetSerialize->xml_serialize(/* "延时时间" */ g_sLangTxt_Native_DelayTime.GetString(), "DelayChangeValue", "us", "number", pAbnormalSMV->m_nDelayChangeValue);
#endif
}

void stt_xml_serialize_SeqNumDevtSet(tmt_StateAbnormalSMV *pAbnormalSMV, CSttXmlSerializeBase *pSmvParasSerializeBase)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pSeqNumDevtSetSerialize = pSmvParasSerializeBase->xml_serialize("序号偏差", "SeqNumDevtSet", "SeqNumDevt", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pSeqNumDevtSetSerialize = pSmvParasSerializeBase->xml_serialize( /* "序号偏差" */ g_sLangTxt_Native_SeqDev.GetString(), "SeqNumDevtSet", "SeqNumDevt", stt_ParaGroupKey());
#endif

	if (pSeqNumDevtSetSerialize == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pSeqNumDevtSetSerialize->xml_serialize("序号偏差","SeqNumDevtValue","","number",pAbnormalSMV->m_nSeqNumDevtValue);
#else
  pSeqNumDevtSetSerialize->xml_serialize(/* "序号偏差" */ g_sLangTxt_Native_SeqDev.GetString(), "SeqNumDevtValue", "", "number", pAbnormalSMV->m_nSeqNumDevtValue);
#endif
}

void stt_xml_serialize_QualitySet(tmt_StateAbnormalSMV *pAbnormalSMV, CSttXmlSerializeBase *pSmvParasSerializeBase)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pQualitySetSerialize = pSmvParasSerializeBase->xml_serialize("品质异常", "QualitySet", "QualitySet", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pQualitySetSerialize = pSmvParasSerializeBase->xml_serialize( /* "品质异常" */ g_sLangTxt_Native_QltyExcp.GetString(), "QualitySet", "QualitySet", stt_ParaGroupKey());
#endif

	if (pQualitySetSerialize == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pQualitySetSerialize->xml_serialize("有效","Bit1","","number",pAbnormalSMV->m_nQualityBit[0]);
	pQualitySetSerialize->xml_serialize("溢出","Bit2","","number",pAbnormalSMV->m_nQualityBit[1]);
	pQualitySetSerialize->xml_serialize("超值域","Bit3","","number",pAbnormalSMV->m_nQualityBit[2]);
	pQualitySetSerialize->xml_serialize("坏基准值","Bit4","","number",pAbnormalSMV->m_nQualityBit[3]);
	pQualitySetSerialize->xml_serialize("抖动","Bit5","","number",pAbnormalSMV->m_nQualityBit[4]);
	pQualitySetSerialize->xml_serialize("故障","Bit6","","number",pAbnormalSMV->m_nQualityBit[5]);
	pQualitySetSerialize->xml_serialize("旧数据","Bit7","","number",pAbnormalSMV->m_nQualityBit[6]);
	pQualitySetSerialize->xml_serialize("不一致","Bit8","","number",pAbnormalSMV->m_nQualityBit[7]);
	pQualitySetSerialize->xml_serialize("不精确","Bit9","","number",pAbnormalSMV->m_nQualityBit[8]);
	pQualitySetSerialize->xml_serialize("源","Bit10","","number",pAbnormalSMV->m_nQualityBit[9]);
	pQualitySetSerialize->xml_serialize("测试","Bit11","","number",pAbnormalSMV->m_nQualityBit[10]);
	pQualitySetSerialize->xml_serialize("操作员闭锁","Bit12","","number",pAbnormalSMV->m_nQualityBit[11]);
	CString strName,strID, str1 = "通道",str2 = "使能",strIndex;
#else
	pQualitySetSerialize->xml_serialize(/* "有效" */ g_sLangTxt_Native_Valid.GetString(), "Bit1", "", "number", pAbnormalSMV->m_nQualityBit[0]);
	pQualitySetSerialize->xml_serialize(/* "溢出" */ g_sLangTxt_Native_Overflow.GetString(), "Bit2", "", "number", pAbnormalSMV->m_nQualityBit[1]);
	pQualitySetSerialize->xml_serialize(/* "超值域" */ g_sLangTxt_Native_OutOfRanges.GetString(), "Bit3", "", "number", pAbnormalSMV->m_nQualityBit[2]);
	pQualitySetSerialize->xml_serialize(/* "坏基准值" */ g_sLangTxt_Native_BadBaseVal.GetString(), "Bit4", "", "number", pAbnormalSMV->m_nQualityBit[3]);
	pQualitySetSerialize->xml_serialize(/* "抖动" */ g_sLangTxt_State_Dithering.GetString(), "Bit5", "", "number", pAbnormalSMV->m_nQualityBit[4]);
	pQualitySetSerialize->xml_serialize(/* "故障" */ g_sLangTxt_Native_Fault.GetString(), "Bit6", "", "number", pAbnormalSMV->m_nQualityBit[5]);
	pQualitySetSerialize->xml_serialize(/* "旧数据" */ g_sLangTxt_Native_OldData.GetString(), "Bit7", "", "number", pAbnormalSMV->m_nQualityBit[6]);
	pQualitySetSerialize->xml_serialize(/* "不一致" */ g_sLangTxt_Native_Inconsistent.GetString(), "Bit8", "", "number", pAbnormalSMV->m_nQualityBit[7]);
	pQualitySetSerialize->xml_serialize(/* "不精确" */ g_sLangTxt_Native_Inaccurate.GetString(), "Bit9", "", "number", pAbnormalSMV->m_nQualityBit[8]);
	pQualitySetSerialize->xml_serialize(/* "源" */ g_sLangTxt_Native_Source.GetString(), "Bit10", "", "number", pAbnormalSMV->m_nQualityBit[9]);
	pQualitySetSerialize->xml_serialize(/* "测试" */ g_sLangTxt_State_Test.GetString(), "Bit11", "", "number", pAbnormalSMV->m_nQualityBit[10]);
	pQualitySetSerialize->xml_serialize(/* "操作员闭锁" */ g_sLangTxt_Native_OpLock.GetString(), "Bit12", "", "number", pAbnormalSMV->m_nQualityBit[11]);
	CString strName, strID, str1 = /* "通道" */ g_sLangTxt_Native_Channel, str2 = /* "使能" */ g_sLangTxt_Harm_Enable, strIndex;
#endif

	for (int nIndex = 0;nIndex<50;nIndex++)
	{
		strIndex.Format(_T("%d"),(nIndex+1));
		strName = str1 + strIndex + str2;
		strID.Format(_T("EnableCh%s"),strIndex.GetString());
		pQualitySetSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",pAbnormalSMV->m_nInvalidChanel[nIndex]);
	}
}

void stt_xml_serialize_OutlierSet(tmt_StateAbnormalSMV *pAbnormalSMV, CSttXmlSerializeBase *pSmvParasSerializeBase)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pOutlierSetSerialize = pSmvParasSerializeBase->xml_serialize("异常点选择", "OutlierSet", "Outlier", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pOutlierSetSerialize = pSmvParasSerializeBase->xml_serialize( /* "异常点选择" */ g_sLangTxt_Native_AbnPointSel.GetString(), "OutlierSet", "Outlier", stt_ParaGroupKey());
#endif

	if (pOutlierSetSerialize == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	CString strName,strID, str1 = "异常点",strIndex;
#else
  CString strName, strID, str1 = /* "异常点" */ g_sLangTxt_Native_AbnPoint, strIndex;
#endif
	for (int nIndex = 0;nIndex<80;nIndex++)
	{
		strIndex.Format(_T("%d"),(nIndex+1));
		strName = str1 + strIndex;
		strID.Format(_T("Outlier%s"),strIndex.GetString());
		pOutlierSetSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",pAbnormalSMV->m_nAbnormalPoint[nIndex]);
	}
}

void stt_xml_serialize_AbnormalSMV(tmt_StateAbnormalSMV *pAbnormalSMV, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pSmvParasSerializeBase = pXmlSierialize->xml_serialize("SMV异常参数", "SmvTest", "smv", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pSmvParasSerializeBase = pXmlSierialize->xml_serialize( /* "SMV异常参数" */ g_sLangTxt_Native_SMVAbnParam.GetString(), "SmvTest", "smv", stt_ParaGroupKey());
#endif

	if (pSmvParasSerializeBase == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pSmvParasSerializeBase->xml_serialize("SV异常类型","FaultType","","SVFaultType",pAbnormalSMV->m_nAbnormalType);
#else
  pSmvParasSerializeBase->xml_serialize(/* "SV异常类型" */ g_sLangTxt_Native_SVAbnType.GetString(), "FaultType", "", "SVFaultType", pAbnormalSMV->m_nAbnormalType);
#endif
	if ((stt_xml_serialize_is_read(pXmlSierialize)||stt_xml_serialize_is_register(pXmlSierialize))&&(pAbnormalSMV->m_nAbnormalType == 0))//如果没有异常信息,直接跳过
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pSmvParasSerializeBase->xml_serialize("SV报文组号(从0开始编号)","SendGroup","","number",pAbnormalSMV->m_nGroupIndex);
	pSmvParasSerializeBase->xml_serialize("异常数据发送时间模式(0-周波;1-秒)","SendMode","","SvAbnSendMode",pAbnormalSMV->m_nSendMode);
	pSmvParasSerializeBase->xml_serialize("发送周波数(周波模式)","CircleNum_CircleMode","","number",pAbnormalSMV->m_nCircleNum_TypeCircle);
	pSmvParasSerializeBase->xml_serialize("每秒发送周波数(秒模式)","CircleNum_PerSecond","","number",pAbnormalSMV->m_nCircleNum_TypeSecond);
	pSmvParasSerializeBase->xml_serialize("SV发送时间(秒模式)","SendTime","","number",pAbnormalSMV->m_nSendTime_TypeSecond);
#else
	pSmvParasSerializeBase->xml_serialize(/* "SV报文组号(从0开始编号)" */ g_sLangTxt_Native_SVMsgGrpNum.GetString(), "SendGroup", "", "number", pAbnormalSMV->m_nGroupIndex);
	pSmvParasSerializeBase->xml_serialize(/* "异常数据发送时间模式(0-周波;1-秒)" */ g_sLangTxt_Native_AbnormDataSendTimeMode.GetString(), "SendMode", "", "SvAbnSendMode", pAbnormalSMV->m_nSendMode);
	pSmvParasSerializeBase->xml_serialize(/* "发送周波数(周波模式)" */ g_sLangTxt_Native_SendFreq.GetString(), "CircleNum_CircleMode", "", "number", pAbnormalSMV->m_nCircleNum_TypeCircle);
	pSmvParasSerializeBase->xml_serialize(/* "每秒发送周波数(秒模式)" */ g_sLangTxt_Native_SendFreqPerSec.GetString(), "CircleNum_PerSecond", "", "number", pAbnormalSMV->m_nCircleNum_TypeSecond);
	pSmvParasSerializeBase->xml_serialize(/* "SV发送时间(秒模式)" */ g_sLangTxt_Native_SVSendTimeSecMode.GetString(), "SendTime", "", "number", pAbnormalSMV->m_nSendTime_TypeSecond);
#endif
	stt_xml_serialize_SMVSourceParaSet(&pAbnormalSMV->m_oSmvMsg,pSmvParasSerializeBase);
	stt_xml_serialize_FlyPointSet(pAbnormalSMV,pSmvParasSerializeBase);
	stt_xml_serialize_FrampShakingSet(pAbnormalSMV,pSmvParasSerializeBase);
	stt_xml_serialize_OutOfOrderSet(pAbnormalSMV,pSmvParasSerializeBase);
	stt_xml_serialize_DelayDeviationSet(pAbnormalSMV,pSmvParasSerializeBase);
	stt_xml_serialize_DelayChangeSet(pAbnormalSMV,pSmvParasSerializeBase);
	stt_xml_serialize_SeqNumDevtSet(pAbnormalSMV,pSmvParasSerializeBase);
	stt_xml_serialize_QualitySet(pAbnormalSMV,pSmvParasSerializeBase);
	stt_xml_serialize_OutlierSet(pAbnormalSMV,pSmvParasSerializeBase);
}


void stt_xml_serialize_AbnormalGOOSE(tmt_StateAbnormalGOOSE *pAbnormalGOOSE, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pGooseParasSerializeBase = pXmlSierialize->xml_serialize("GOOSE异常参数", "GooseTest", "goose", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pGooseParasSerializeBase = pXmlSierialize->xml_serialize(/* "GOOSE异常参数" */ g_sLangTxt_Native_GOOSEAbnormParam.GetString(), "GooseTest", "goose", stt_ParaGroupKey());
#endif

	if (pGooseParasSerializeBase == NULL)
	{
		return;
	}

#ifdef NOT_USE_XLANGUAGE

	pGooseParasSerializeBase->xml_serialize("异常组序号（从0计数）","GroupIndex","","number",pAbnormalGOOSE->m_nGroupIndex);

	pGooseParasSerializeBase->xml_serialize("源MAC(选择)","SrcMAC_Sel","","number",pAbnormalGOOSE->m_bSrcMac_Sel);
	pGooseParasSerializeBase->xml_serialize("目标MAC(选择)","DstMAC_Sel","","number",pAbnormalGOOSE->m_bDestMac_Sel);
	pGooseParasSerializeBase->xml_serialize("GocbRef(选择)","GocbRef_Sel","","number",pAbnormalGOOSE->m_bGocbRef_Sel);
	pGooseParasSerializeBase->xml_serialize("GoID(选择)","GoID_Sel","","number",pAbnormalGOOSE->m_bGoID_Sel);
	pGooseParasSerializeBase->xml_serialize("DataSet(选择)","DataSet_Sel","","number",pAbnormalGOOSE->m_bDataSet_Sel);

	pGooseParasSerializeBase->xml_serialize("源MAC","SrcMAC","","string",pAbnormalGOOSE->m_strSrcMac);
	pGooseParasSerializeBase->xml_serialize("目标MAC","DstMAC","","string",pAbnormalGOOSE->m_strDestMac);
	pGooseParasSerializeBase->xml_serialize("GocbRef","GocbRef","","string",pAbnormalGOOSE->m_strGocbRef);
	pGooseParasSerializeBase->xml_serialize("GoID","GoID","","string",pAbnormalGOOSE->m_strGoID);
	pGooseParasSerializeBase->xml_serialize("DataSet","DataSet","","string",pAbnormalGOOSE->m_strDataSet);

	pGooseParasSerializeBase->xml_serialize("AppID(选择)","AppID_Sel","","number",pAbnormalGOOSE->m_bAppID_Sel);
	pGooseParasSerializeBase->xml_serialize("AppID","AppID","","string",pAbnormalGOOSE->m_nAppID);
	pGooseParasSerializeBase->xml_serialize("St(选择)","StNum_Sel","","number",pAbnormalGOOSE->m_bStNumSet_Sel);
	pGooseParasSerializeBase->xml_serialize("St值","StValue","","number",pAbnormalGOOSE->m_nStNum);
	pGooseParasSerializeBase->xml_serialize("Sq(选择)","SqNum_Sel","","number",pAbnormalGOOSE->m_bSqNumSet_Sel);
	pGooseParasSerializeBase->xml_serialize("Sq值","SqValue","","number",pAbnormalGOOSE->m_nSqNum);
	pGooseParasSerializeBase->xml_serialize("允许生存时间(选择)","TTL_Sel","","number",pAbnormalGOOSE->m_bTtlSet_Sel);
	pGooseParasSerializeBase->xml_serialize("允许生存时间","TimeAllowToLive","ms","number",pAbnormalGOOSE->m_nTimeAllowToLive);

	pGooseParasSerializeBase->xml_serialize("委托(选择)","NdsCom_Sel","","number",pAbnormalGOOSE->m_bNdsCom_Sel);
	pGooseParasSerializeBase->xml_serialize("测试标记(选择)","TestFlag_Sel","","number",pAbnormalGOOSE->m_bTestFlag_Sel);

	pGooseParasSerializeBase->xml_serialize("委托","NdsCom","","number",pAbnormalGOOSE->m_nNdsCom);
	pGooseParasSerializeBase->xml_serialize("测试标记","TestFlag","","number",pAbnormalGOOSE->m_nTestFlag);
	pGooseParasSerializeBase->xml_serialize("VlanID(选择)","VlanID_Sel","","number",pAbnormalGOOSE->m_bVlanSet_Sel);
	pGooseParasSerializeBase->xml_serialize("VlanID值","VlanID","","number",pAbnormalGOOSE->m_nVlanID);
	pGooseParasSerializeBase->xml_serialize("网络标识(选择)","NetType_Sel","","number",pAbnormalGOOSE->m_bNetTypeSet_Sel);
	pGooseParasSerializeBase->xml_serialize("网络标识值","NetType","","number",pAbnormalGOOSE->m_nNetType);
	pGooseParasSerializeBase->xml_serialize("配置版本(选择)","Confrecv_Sel","","number",pAbnormalGOOSE->m_bConfRecvSet_Sel);
	pGooseParasSerializeBase->xml_serialize("配置版本值","ConfRecv","","number",pAbnormalGOOSE->m_nConfRecv);

	pGooseParasSerializeBase->xml_serialize("VLanPriority","VLanPriority","","number",pAbnormalGOOSE->m_nVLanPriority);
	pGooseParasSerializeBase->xml_serialize("时间品质","Timequality","","number",pAbnormalGOOSE->m_nTimequality);
#else
	pGooseParasSerializeBase->xml_serialize(/* "异常组序号（从0计数）" */ g_sLangTxt_Native_AbnormGroupSeq.GetString(), "GroupIndex", "", "number", pAbnormalGOOSE->m_nGroupIndex);

	pGooseParasSerializeBase->xml_serialize(/* "源MAC(选择)" */ g_sLangTxt_Native_SrcMACSelect.GetString(), "SrcMAC_Sel", "", "number", pAbnormalGOOSE->m_bSrcMac_Sel);
	pGooseParasSerializeBase->xml_serialize(/* "目标MAC(选择)" */ g_sLangTxt_Native_DestMACSelect.GetString(), "DstMAC_Sel", "", "number", pAbnormalGOOSE->m_bDestMac_Sel);
	pGooseParasSerializeBase->xml_serialize(/* "GocbRef(选择)" */ g_sLangTxt_Native_GocbRefSelect.GetString(), "GocbRef_Sel", "", "number", pAbnormalGOOSE->m_bGocbRef_Sel);
	pGooseParasSerializeBase->xml_serialize(/* "GoID(选择)" */ g_sLangTxt_Native_GoIDSelect.GetString(), "GoID_Sel", "", "number", pAbnormalGOOSE->m_bGoID_Sel);
	pGooseParasSerializeBase->xml_serialize(/* "DataSet(选择)" */ g_sLangTxt_Native_DataSetSelect.GetString(), "DataSet_Sel", "", "number", pAbnormalGOOSE->m_bDataSet_Sel);

	pGooseParasSerializeBase->xml_serialize(/* "源MAC" */ g_sLangTxt_Native_SrcMAC.GetString(), "SrcMAC", "", "string", pAbnormalGOOSE->m_strSrcMac);
	pGooseParasSerializeBase->xml_serialize(/* "目标MAC" */ g_sLangTxt_Native_DestMACs.GetString(), "DstMAC", "", "string", pAbnormalGOOSE->m_strDestMac);
	pGooseParasSerializeBase->xml_serialize("GocbRef", "GocbRef", "", "string", pAbnormalGOOSE->m_strGocbRef);
	pGooseParasSerializeBase->xml_serialize("GoID", "GoID", "", "string", pAbnormalGOOSE->m_strGoID);
	pGooseParasSerializeBase->xml_serialize("DataSet", "DataSet", "", "string", pAbnormalGOOSE->m_strDataSet);

	pGooseParasSerializeBase->xml_serialize(/* "AppID(选择)" */ g_sLangTxt_Native_AppIDSelect.GetString(), "AppID_Sel", "", "number", pAbnormalGOOSE->m_bAppID_Sel);
	pGooseParasSerializeBase->xml_serialize("AppID", "AppID", "", "string", pAbnormalGOOSE->m_nAppID);
	pGooseParasSerializeBase->xml_serialize(/* "St(选择)" */ g_sLangTxt_Native_StSelect.GetString(), "StNum_Sel", "", "number", pAbnormalGOOSE->m_bStNumSet_Sel);
	pGooseParasSerializeBase->xml_serialize(/* "St值" */ g_sLangTxt_Native_StValue.GetString(), "StValue", "", "number", pAbnormalGOOSE->m_nStNum);
	pGooseParasSerializeBase->xml_serialize(/* "Sq(选择)" */ g_sLangTxt_Native_SqSelect.GetString(), "SqNum_Sel", "", "number", pAbnormalGOOSE->m_bSqNumSet_Sel);
	pGooseParasSerializeBase->xml_serialize(/* "Sq值" */ g_sLangTxt_Native_SqValue.GetString(), "SqValue", "", "number", pAbnormalGOOSE->m_nSqNum);
	pGooseParasSerializeBase->xml_serialize(/* "允许生存时间(选择)" */ g_sLangTxt_Native_AllowLiveTSelect.GetString(), "TTL_Sel", "", "number", pAbnormalGOOSE->m_bTtlSet_Sel);
	pGooseParasSerializeBase->xml_serialize(/* "允许生存时间" */ g_sLangTxt_Native_AllowLiveT.GetString(), "TimeAllowToLive", "ms", "number", pAbnormalGOOSE->m_nTimeAllowToLive);

	pGooseParasSerializeBase->xml_serialize(/* "委托(选择)" */ g_sLangTxt_Native_DelegateSelect.GetString(), "NdsCom_Sel", "", "number", pAbnormalGOOSE->m_bNdsCom_Sel);
	pGooseParasSerializeBase->xml_serialize(/* "测试标记(选择)" */ g_sLangTxt_Native_TestMarkSelect.GetString(), "TestFlag_Sel", "", "number", pAbnormalGOOSE->m_bTestFlag_Sel);

	pGooseParasSerializeBase->xml_serialize(/* "委托" */ g_sLangTxt_Native_Delegate.GetString(), "NdsCom", "", "number", pAbnormalGOOSE->m_nNdsCom);
	pGooseParasSerializeBase->xml_serialize(/* "测试标记" */ g_sLangTxt_Native_TestMark.GetString(), "TestFlag", "", "number", pAbnormalGOOSE->m_nTestFlag);
	pGooseParasSerializeBase->xml_serialize(/* "VlanID(选择)" */ g_sLangTxt_Native_VlanIDSelect.GetString(), "VlanID_Sel", "", "number", pAbnormalGOOSE->m_bVlanSet_Sel);
	pGooseParasSerializeBase->xml_serialize(/* "VlanID值" */ g_sLangTxt_Native_VlanIDValue.GetString(), "VlanID", "", "number", pAbnormalGOOSE->m_nVlanID);
	pGooseParasSerializeBase->xml_serialize(/* "网络标识(选择)" */ g_sLangTxt_Native_NetIDSelect.GetString(), "NetType_Sel", "", "number", pAbnormalGOOSE->m_bNetTypeSet_Sel);
	pGooseParasSerializeBase->xml_serialize(/* "网络标识值" */ g_sLangTxt_Native_NetIDValue.GetString(), "NetType", "", "number", pAbnormalGOOSE->m_nNetType);
	pGooseParasSerializeBase->xml_serialize(/* "配置版本(选择)" */ g_sLangTxt_Native_ConfigVerSelect.GetString(), "Confrecv_Sel", "", "number", pAbnormalGOOSE->m_bConfRecvSet_Sel);
	pGooseParasSerializeBase->xml_serialize(/* "配置版本值" */ g_sLangTxt_Native_ConfigVerValue.GetString(), "ConfRecv", "", "number", pAbnormalGOOSE->m_nConfRecv);

	pGooseParasSerializeBase->xml_serialize("VLanPriority", "VLanPriority", "", "number", pAbnormalGOOSE->m_nVLanPriority);
	pGooseParasSerializeBase->xml_serialize(/* "时间品质" */ g_sLangTxt_IEC_TimeQuality.GetString(), "Timequality", "", "number", pAbnormalGOOSE->m_nTimequality);
#endif
}



