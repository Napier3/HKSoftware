#include "stdafx.h"
#include "tmt_async_state_test.h"
#include "../tmt_system_config.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              
#endif

void stt_xml_serialize_Modules(tmt_async_modules *pModules, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize("硬件模块", "DeviceModules", "Modules", stt_ParaGroupKey());
	if (pSerialize == NULL)
	{
		return;
	}

	pSerialize->xml_serialize("模拟量模块数","AnalogCount","","number",pModules->m_nAnalogCount);
	pSerialize->xml_serialize("弱信号模块数","WeekCount","","number",pModules->m_nWeekCount);

	for (int i=0; i<pModules->m_nAnalogCount; i++)
	{
		stt_xml_serialize_Analog(&pModules->m_oAnalogModules[i],i,pSerialize);
	}

	for (int i=0; i<pModules->m_nWeekCount; i++)
	{
		stt_xml_serialize_Week(&pModules->m_oWeekModules[i],i,pSerialize);
	}
	if(pModules->m_oDigitalModules.m_nModulePos != 0 && stt_xml_serialize_is_write(pSerialize))
	{
		//下发命令
		stt_xml_serialize_Digital(&pModules->m_oDigitalModules,pSerialize);
	}
	else if(stt_xml_serialize_is_read(pSerialize)||stt_xml_serialize_is_register(pSerialize))
	{
	stt_xml_serialize_Digital(&pModules->m_oDigitalModules,pSerialize);
	}

	pSerialize->xml_serialize("模拟量直流状态","AnalogDcState","","bool",pModules->m_nDc[ASYNC_MODULE_TYPE_ANALOG]);
	pSerialize->xml_serialize("弱信号直流状态","WeekDcState","","bool",pModules->m_nDc[ASYNC_MODULE_TYPE_WEEK]);
	pSerialize->xml_serialize("数字量直流状态","DigitalDcState","","bool",pModules->m_nDc[ASYNC_MODULE_TYPE_DIGITAL]);


}

void stt_xml_serialize_binary_out(tmt_AsyncStatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize_binary_in(tmt_AsyncStatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
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
	CString strName, strID;
#ifdef NOT_USE_XLANGUAGE
	CString str1 = _T("开入");
	CString str2 = _T("选择");
#else
	CString str1 = g_sLangTxt_Native_BinX;
	CString str2 = g_sLangTxt_Select;
#endif
// 	int nCnt = get_xml_serialize_binary_count(pXmlSierialize);
	int nCnt = 8;

	for(int nIndex = 0; nIndex < nCnt; nIndex++)
	{
		strName = str1 + pszBInName[nIndex] + str2;
		strID.Format("BIn%c",pszBInName[nIndex]);
		pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","BOOL",oStatePara.m_binIn[nIndex].nSelect);
	}
}

BOOL stt_xml_serialize(tmt_AsyncStatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
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

    pStateSerialize->xml_serialize("触发方式", "EndMode","","StateEndMode_PSUAuto",oStatePara.m_nTriggerCondition);
    pStateSerialize->xml_serialize("输出时间", "LastT","s","number",oStatePara.m_fTimeState);
    pStateSerialize->xml_serialize("触发后保持时间", "EndDelayT","s","number",oStatePara.m_fTimeAfterTrigger);
    pStateSerialize->xml_serialize("开出量保持时间", "OutputHoldT","s","number",oStatePara.m_fOutputHoldTime);

	pStateSerialize->xml_serialize("是否选择", "bSelect", "", "BOOL", oStatePara.m_bSelected);
// 	pStateSerialize->xml_serialize("直流分量的衰减时间常数", "_Tao","s","number",oStatePara.m_fTao);

	pStateSerialize->xml_serialize("描述", "Name", "", "string", oStatePara.m_strName);
   	pStateSerialize->xml_serialize("辅助直流电压","VdcAux","V","number",oStatePara.m_fVolAux);

    pStateSerialize->xml_serialize("GPS触发时刻（时）", "GpsH"," ","number",oStatePara.m_tGps.nHour);
    pStateSerialize->xml_serialize("GPS触发时刻（分）", "GpsM"," ","number",oStatePara.m_tGps.nMinutes);
    pStateSerialize->xml_serialize("GPS触发时刻（秒）", "GpsS"," ","number",oStatePara.m_tGps.nSeconds);
    pStateSerialize->xml_serialize("递变时间分度(ms)", "RampTimeGrad"," ","number",oStatePara.m_nRampTimeGrad);
	pStateSerialize->xml_serialize("开出模式选择", "BinaryOutType"," ","number",oStatePara.m_nBinaryOutType);//0-开出+Gse,1-只有开出,2-只有Gse

    //新版序列化,U1~U48,i1~i48
//     CString strID;
//     for(int nIndex=0;nIndex<MAX_VOLTAGE_COUNT;nIndex++)
//     {
//         strID.Format(_T("U%d"),nIndex+1);
//         stt_xml_serialize(&oStatePara.m_uiVOL[nIndex], strID.GetString(),pStateSerialize,nHarmCount);
// 
//         strID.Format(_T("I%d"),nIndex+1);
//         stt_xml_serialize(&oStatePara.m_uiCUR[nIndex], strID.GetString(),pStateSerialize,nHarmCount);
//     }

//     if (stt_xml_serialize_is_read(pXmlSierialize))
//     {
//         stt_xml_serialize(&oStatePara.m_oGoosePub[0],pStateSerialize);
//         stt_xml_serialize(&oStatePara.m_oFt3Pub[0],pStateSerialize);
// 	}


	//----------------------------------
    stt_xml_serialize_binary_in(oStatePara, pStateSerialize);
    stt_xml_serialize_Exbinary_in(oStatePara.m_binInEx,pStateSerialize);
    stt_xml_serialize_binary_out(oStatePara, pStateSerialize);
    stt_xml_serialize_Exbinary_out(oStatePara.m_binOutEx,pStateSerialize);
	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		stt_xml_serialize(&oStatePara.m_oGoosePub[0],pStateSerialize);
		stt_xml_serialize(&oStatePara.m_oFt3Pub[0],pStateSerialize);
	}

	stt_xml_serialize_Modules(&oStatePara.m_oStateAsyncModule,pStateSerialize);

    return TRUE;
}

void stt_xml_serialize(tmt_AsyncStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
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
	BOOL bValid;
	for (nIndex=0; nIndex < nStateCount; nIndex++)
	{
		if(stt_xml_serialize_is_read(pXmlSierialize))
		{
			bValid = stt_xml_serialize(pParas->m_paraState[nIndex], nIndex, pXmlSierialize);
			if(bValid)
			{
				pParas->m_paraState[nIndex].m_bSelected = TRUE;
			}
			else
			{
				pParas->m_paraState[nIndex].m_bSelected = FALSE;
			}
		}
		else
		{
			if(pParas->m_paraState[nIndex].m_bSelected)
			{
				stt_xml_serialize(pParas->m_paraState[nIndex], nIndex, pXmlSierialize);
			}
		}
	}
}

void stt_xml_serialize(tmt_AsyncStateResults *pResults,tmt_AsyncStateParas *pStateParas,int nStateNums, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef)
{
// 	BOOL bUseErr[10];
// 	for (int i=0; i < 10; i++)
// 	{
// 		if(pStateParas->m_paraEstimates[i].m_bUseError)
// 		{
// 			bUseErr[i] = TRUE;
// 		}
// 		else
// 		{
// 			bUseErr[i] = FALSE;
// 		}
// 	}
// 	stt_xml_serialize_common(pResults, bUseErr, pXmlSierialize);
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

void stt_xml_serialize(tmt_AsyncStateResult &oStateResult, tmt_AsyncStatePara oParaState, long nStateIndex, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef,int *pnFirstBinInitState,int *pnFirstBinExInitState)
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

CSttXmlSerializeBase* stt_xml_serialize( tmt_async_state_test *pParas, CSttXmlSerializeBase *pXmlSierialize/*, long nVolRsNum,long nCurRsNum,long nHarmCount*/ )
{
	CSttXmlSerializeBase *pXmlParas = pXmlSierialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());
	if (pXmlParas  != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize_ex2(&pParas->m_oStateAsyncParas, pXmlParas,FALSE);
		}
		else
		{
			stt_xml_serialize_ex2(&pParas->m_oStateAsyncParas, pXmlParas,TRUE);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSierialize->xml_serialize("results", "results", "results", stt_ResultsKey());
	if (pXmlResults  != NULL)
	{
		// 20240223 suayng 重新打开模板重新更新状态数
		if(stt_xml_serialize_is_read(pXmlParas)|| stt_xml_serialize_is_register(pXmlParas) )
		{
			pParas->m_oStateAsyncResults.init(pParas->m_oStateAsyncParas.m_nStateNumbers);
		}
		stt_xml_serialize(&pParas->m_oStateAsyncResults, &pParas->m_oStateAsyncParas, pParas->m_oStateAsyncParas.m_nStateNumbers,
			pXmlResults,1);
	}

	return pXmlParas;
}

void stt_xml_serialize_ex2(tmt_AsyncStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize, bool bSel)
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
				stt_xml_serialize(pParas->m_paraState[i], nIndex, pXmlSierialize);
				nIndex++;
			}
		}
		else
		{
			stt_xml_serialize(pParas->m_paraState[i], nIndex, pXmlSierialize);
			nIndex++;
		}
	}
}

void stt_xml_serialize_act_rcd(tmt_AsyncStateResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//动作记录,最大64次,根据实际动作情况,上送总的动作信息
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
#include"../../../SttCmd/SttTestCmd.h"
#include"../../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_AsyncStateTest()
{
	tmt_AsyncStateTest oStateTest;
	oStateTest.init(10);
	oStateTest.m_oStateAsyncParas.m_nStateNumbers = 10;
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
	stt_xml_serialize(&oStateTest.m_oStateAsyncResults,&oStateTest.m_oStateAsyncParas,10, pMacroResults,0);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("AsyncStateTestDemo.xml");
	//  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

tmt_AsyncStatePara * stt_async_state_paras_insert_after( tmt_AsyncStateParas *pParas, tmt_AsyncStatePara *pSrc, int nAfter )
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
		tmt_AsyncStatePara *pDst = new tmt_AsyncStatePara;
		pDst->Copy(*pSrc);
		pParas->m_paraState[nAfter+1] = *pDst;
	}
	else
	{
		tmt_AsyncStatePara *pDst = new tmt_AsyncStatePara;
		pParas->m_paraState[nAfter+1] = *pDst;
	}

	pParas->m_nStateNumbers++;

	return &pParas->m_paraState[nAfter+1];
}

void stt_async_state_paras_delete( tmt_AsyncStateParas *pParas, int nIndex )
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

void stt_xml_serialize_common( tmt_AsyncStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize )
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("开入量翻转判别条件", "_BinTripRef"," ","StateBinTripRef",pParas->m_nBinTripRef);
// 	CSttXmlSerializeBase *pEstimatesSerialize = pXmlSierialize->xml_serialize("结果评估", "rslt_evaluation", "rslt_evaluation", stt_ParaGroupKey());

#else

	pXmlSierialize->xml_serialize(/* "开入量翻转判别条件" */ g_sLangTxt_Native_InFlipCond.GetString(), "_BinTripRef", " ", "StateBinTripRef", pParas->m_nBinTripRef);
// 	CSttXmlSerializeBase *pEstimatesSerialize = pXmlSierialize->xml_serialize("结果评估", "rslt_evaluation", "rslt_evaluation", stt_ParaGroupKey());

#endif

}
