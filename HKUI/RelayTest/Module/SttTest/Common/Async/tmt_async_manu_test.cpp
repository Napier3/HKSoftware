#include "tmt_async_manu_test.h"
#include "stdafx.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"
#endif

#ifdef _STT_NOT_IN_TEST_SERVER_
#include "../../../SttTestSysGlobalPara.h"
#endif

void stt_xml_serialize_Modules(tmt_AsyncManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	tmt_async_modules *pModules = &pParas->m_oAsyncModuels;

	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize("硬件模块", "DeviceModules", "Modules", stt_ParaGroupKey());
	if (pSerialize == NULL)
	{
		return;
	}

	pSerialize->xml_serialize("模拟量模块数","AnalogCount","","number",pModules->m_nAnalogCount);
	pSerialize->xml_serialize("弱信号模块数","WeekCount","","number",pModules->m_nWeekCount);

	long nHasOutput = 1;
#ifdef _STT_NOT_IN_TEST_SERVER_
	nHasOutput = g_oSystemParas.m_nHasAnalog;
#else
	nHasOutput = 1;
#endif
	if(nHasOutput || !stt_xml_serialize_is_write(pSerialize))
	{
		for (int i=0; i<pModules->m_nAnalogCount; i++)
		{
			stt_xml_serialize_Analog(&pModules->m_oAnalogModules[i],i,pSerialize);
		}
		if(pModules->m_nAnalogCount > 0)
		{
			stt_xml_serialize_Gradient(&pParas->m_manuGradient[ASYNC_MODULE_TYPE_ANALOG],pSerialize,ASYNC_MODULE_TYPE_ANALOG);
		}
	}

#ifdef _STT_NOT_IN_TEST_SERVER_
	nHasOutput = g_oSystemParas.m_nHasWeek;
#else
	nHasOutput = 1;
#endif
	if(nHasOutput || !stt_xml_serialize_is_write(pSerialize))
	{
		for (int i=0; i<pModules->m_nWeekCount; i++)
		{
			stt_xml_serialize_Week(&pModules->m_oWeekModules[i],i,pSerialize);
		}

		if(pModules->m_nWeekCount > 0)
		{
			stt_xml_serialize_Gradient(&pParas->m_manuGradient[ASYNC_MODULE_TYPE_WEEK],pSerialize,ASYNC_MODULE_TYPE_WEEK);
		}
	}

#ifdef _STT_NOT_IN_TEST_SERVER_
	nHasOutput = g_oSystemParas.m_nHasDigital;
#else
	nHasOutput = 1;
#endif
	if((pModules->m_oDigitalModules.m_nModulePos != 0 && stt_xml_serialize_is_write(pSerialize)) && nHasOutput)
	{
		//下发命令
		stt_xml_serialize_Digital(&pModules->m_oDigitalModules,pSerialize);
		stt_xml_serialize_Gradient(&pParas->m_manuGradient[ASYNC_MODULE_TYPE_DIGITAL],pSerialize,ASYNC_MODULE_TYPE_DIGITAL);
	}
	else if(stt_xml_serialize_is_read(pSerialize)||stt_xml_serialize_is_register(pSerialize))
	{
		stt_xml_serialize_Digital(&pModules->m_oDigitalModules,pSerialize);
		stt_xml_serialize_Gradient(&pParas->m_manuGradient[ASYNC_MODULE_TYPE_DIGITAL],pSerialize,ASYNC_MODULE_TYPE_DIGITAL);
	}

	pSerialize->xml_serialize("模拟量直流状态","AnalogDcState","","bool",pModules->m_nDc[ASYNC_MODULE_TYPE_ANALOG]);
	pSerialize->xml_serialize("弱信号直流状态","WeekDcState","","bool",pModules->m_nDc[ASYNC_MODULE_TYPE_WEEK]);
	pSerialize->xml_serialize("数字量直流状态","DigitalDcState","","bool",pModules->m_nDc[ASYNC_MODULE_TYPE_DIGITAL]);

}

void stt_xml_serialize_Gradient(tmt_async_manu_gradient *pGradientPara, CSttXmlSerializeBase *pXmlSierialize, int nModuleType)
{
	CString strID,strName;

	if(nModuleType == ASYNC_MODULE_TYPE_ANALOG)
	{
		strID = _T("AnalogGradientPara");
		strName = _T("模拟量模块递变参数");
	}
	else if(nModuleType == ASYNC_MODULE_TYPE_WEEK)
	{
		strID = _T("WeekGradientPara");
		strName = _T("弱信号模块递变参数");
	}
	else
	{
		strID = _T("DigitalGradientPara");
		strName = _T("数字量模块递变参数");
	}

	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "GradientPara", stt_ParaGroupKey());
	if (pSerialize == NULL)
	{
		return;
	}

	pSerialize->xml_serialize("模块选择", "_GradientModuleSelect", "", "PsuGradientModule", pGradientPara->m_nGradientModuleSelect);
	pSerialize->xml_serialize("通道选择", "_GradientChSelect", "", "PsuGradientChannel", pGradientPara->m_nGradientChSelect);
	pSerialize->xml_serialize("类型选择", "_GradientTpSelect", "", "PsuGradientType", pGradientPara->m_nGradientTpSelect);
	pSerialize->xml_serialize("变化模式", "Mode", "", "UIVariateMode", pGradientPara->nMode);
	pSerialize->xml_serialize("变化始值", "Start", "", "number", pGradientPara->fStart);
	pSerialize->xml_serialize("变化终值", "End", "", "number", pGradientPara->fEnd);
	pSerialize->xml_serialize("变化步长", "Step", "", "number", pGradientPara->fStep);
	pSerialize->xml_serialize("每步时间", "StepTime", "", "number", pGradientPara->fStepTime);
	pSerialize->xml_serialize("触发延时", "TrigDelay", "", "number", pGradientPara->fTrigDelay);

}

void stt_xml_serialize(tmt_AsyncManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_Modules(pParas,pXmlSierialize);

	pXmlSierialize->xml_serialize("是否开入停止", "bBinStop", "", "BOOL", pParas->m_bBinStop);
	//	pXmlSierialize->xml_serialize("过载延时","fOverload","s","number",pParas->m_fOverloadDelaytime);
// 	pXmlSierialize->xml_serialize("是否以直流模式输出", "bDC", "", "BOOL", pParas->m_bDC);
	pXmlSierialize->xml_serialize("是否老化试验", "bAging", "", "BOOL", pParas->m_bAging);
	pXmlSierialize->xml_serialize("辅助直流电流", "fCurAux", "mA", "number", pParas->m_fCurAux);
	pXmlSierialize->xml_serialize("辅助直流电压", "_UdcAux", "V", "number", pParas->m_fVolAux);
	pXmlSierialize->xml_serialize("递变模块类型选择", "GradientModuleTypeSel", "", "PsuGradientModuleType", pParas->m_nGradientModuleTypeSel);
// 	pXmlSierialize->xml_serialize("变化谐波次数", "Harm", "", "number", pParas->m_manuGradient.nHarmIndex);
// 	pXmlSierialize->xml_serialize("测试通道类型", "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize("开入逻辑", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);

	stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	//Ex
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);
	stt_xml_serialize_Exbinary_out(pParas->m_binOutEx, pXmlSierialize);

	pXmlSierialize->xml_serialize("是否锁定", "_bLock", "", "BOOL", pParas->m_bLockChanged);
	pXmlSierialize->xml_serialize("是否自动递变", "_bAuto", "", "BOOL", pParas->m_bAuto);

	if(stt_xml_serialize_is_read(pXmlSierialize))
	{
		stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
		stt_xml_serialize(&pParas->m_oFt3Pub[0], pXmlSierialize);
		stt_xml_serialize(&pParas->m_o2MOnePortPub[0], pXmlSierialize);
	}

	pXmlSierialize->xml_serialize("最长输出时间(s)", "OutputTime", " ", "number", pParas->m_fOutPutTime);

	pXmlSierialize->xml_serialize("动作整定时间","TSet","s","float",pParas->m_fTimeSet);
	pXmlSierialize->xml_serialize("电压整定动作值","USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize("电流整定动作值","ISet","A","float",pParas->m_fISet);
	pXmlSierialize->xml_serialize("相位整定动作值","AngleSet","°","float",pParas->m_fAngleSet);
	pXmlSierialize->xml_serialize("频率整定动作值","HzSet","Hz","float",pParas->m_fHzSet);
	pXmlSierialize->xml_serialize("返回系数整定值","RetCoefSet","","float",pParas->m_fRetCoefSet);


	pXmlSierialize->xml_serialize("动作时间值绝对误差","Ttrip_AbsErr","","float",pParas->m_fTimeValue_AbsErr);
	pXmlSierialize->xml_serialize("动作时间值相对误差","Ttrip_RelErr","","float",pParas->m_fTimeValue_RelErr);
	pXmlSierialize->xml_serialize("动作时间误差判断逻辑","TimeValue_ErrorLogic","","number",pParas->m_nTimeValue_ErrorLogic);
	pXmlSierialize->xml_serialize("电压动作值绝对误差","UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize("电压动作值相对误差","UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize("电压动作值误差判断逻辑","UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("电流动作值绝对误差","IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize("电流动作值相对误差","IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize("电流动作值误差判断逻辑","IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("相位动作值绝对误差","AngleActVal_AbsErr","","float",pParas->m_fAngleActVal_AbsErr);
	pXmlSierialize->xml_serialize("相位动作值相对误差","AngleActVal_RelErr","","float",pParas->m_fAngleActVal_RelErr);
	pXmlSierialize->xml_serialize("相位动作值误差判断逻辑","AngleActVal_ErrorLogic","","number",pParas->m_nAngleActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("频率动作值绝对误差","HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);	
	pXmlSierialize->xml_serialize("频率动作值相对误差","HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);	
	pXmlSierialize->xml_serialize("频率动作值误差判断逻辑","HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);	
	pXmlSierialize->xml_serialize("返回系数绝对误差","RetCoef_AbsErr","","float",pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize("返回系数相对误差","RetCoef_RelErr","","float",pParas->m_fRetCoef_RelErr);	
	pXmlSierialize->xml_serialize("返回系数误差判断逻辑","RetCoef_ErrorLogic","","number",pParas->m_nRetCoef_ErrorLogic);
}

void stt_xml_serialize_act_rcd(tmt_AsyncManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//动作记录,最大64次,根据实际动作情况,上送总的动作信息
{
	CSttXmlSerializeBase *pXmlActRcddata = pXmlSierialize->xml_serialize("ActRcd", "ActRcd", "ActRcd", stt_ParaGroupKey());

	if(pXmlActRcddata == NULL)
	{
		return;
	}

	CString strName, strID, strTemp, strTmp2;

#ifdef NOT_USE_XLANGUAGE
	CString str1 = _T("开入");
	CString str2 = _T("第");
	CString str3 = _T("次动作时间");
#else
	CString str1 = /*_T("开入")*/g_sLangTxt_Native_BinX;
	CString str2 = /*_T("第")*/g_sLangTxt_Native_Number;
	CString str3 = /*_T("次动作时间")*/g_sLangTxt_Native_NActionTime;
#endif

	int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

	for(int nIndex = 0; nIndex < nCnt; nIndex++)
	{
		strTemp.Format(_T("%d"), nIndex + 1);

		for(int nIndexAct = 0; ((nIndexAct < 64) && (nIndexAct < pResults->m_nrBinSwitchCount[nIndex])); nIndexAct++)
		{
			strTmp2.Format(_T("%d"), nIndexAct + 1);
			strName = str1 + strTemp + str2 + strTmp2 + str3;
			strID.Format("Bin%dActCount%d", (nIndex + 1), (nIndexAct + 1));
			pXmlActRcddata->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_frTimeBinAct[nIndex][nIndexAct]);
		}
	}

	if(g_nBinExCount > 0)
	{
		CSttXmlSerializeBase *pXmlActRcdExdata = pXmlSierialize->xml_serialize("ActRcdEx", "ActRcdEx", "ActRcdEx", stt_ParaGroupKey());

		if(pXmlActRcdExdata == NULL)
		{
			return;
		}

		for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
		{
#ifdef NOT_USE_XLANGUAGE
			strTemp.Format(_T("扩展%d"), nIndex + 1);
#else
			strTemp.Format(/*_T("扩展%d")*/g_sLangTxt_Native_extend.GetString(), nIndex + 1);
#endif
			for(int nIndexAct = 0; ((nIndexAct < 64) && (nIndexAct < pResults->m_nrBinExSwitchCount[nIndex])); nIndexAct++)
			{
				strTmp2.Format(_T("%d"), nIndexAct + 1);
				strName = str1 + strTemp + str2 + strTmp2 + str3;
				strID.Format("BinEx%dActCount%d", (nIndex + 1), (nIndexAct + 1));
				pXmlActRcdExdata->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_frTimeBinExAct[nIndex][nIndexAct]);
			}
		}
	}
}

void stt_xml_serialize(tmt_AsyncManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("动作标记", "TripFlag", "", "number", pResults->m_nTripFlag);
    pXmlSierialize->xml_serialize("动作时间", "TripTime", "", "number", pResults->m_fTripTime);
    pXmlSierialize->xml_serialize("动作值", "ActValue", "", "number", pResults->m_fActValue);
    pXmlSierialize->xml_serialize("返回值", "ReturnValue", "", "number", pResults->m_fReturnValue);
    pXmlSierialize->xml_serialize("返回系数", "ReturnCoef", "", "number", pResults->m_fReturnCoef);
    pXmlSierialize->xml_serialize("返回时间", "ReturnTime", "", "number", pResults->m_fReturnTime);
#else
	pXmlSierialize->xml_serialize(/*"动作标记"*/g_sLangTxt_Native_action_mark.GetString(), "TripFlag", "", "number", pResults->m_nTripFlag);
	pXmlSierialize->xml_serialize(/*"动作时间"*/g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number", pResults->m_fTripTime);
	pXmlSierialize->xml_serialize(/*"动作值"*/g_sLangTxt_State_ActionValue.GetString(), "ActValue", "", "number", pResults->m_fActValue);
	pXmlSierialize->xml_serialize(/*"返回值"*/g_sLangTxt_Native_ReturnValue.GetString(), "ReturnValue", "", "number", pResults->m_fReturnValue);
	pXmlSierialize->xml_serialize(/*"返回系数"*/g_sLangTxt_Gradient_ReCoefficient.GetString(), "ReturnCoef", "", "number", pResults->m_fReturnCoef);
	pXmlSierialize->xml_serialize(/*"返回时间"*/g_sLangTxt_Native_ReturnTime.GetString(), "ReturnTime", "", "number", pResults->m_fReturnTime);
#endif
    CString strName, strID, strTemp;
#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("开入");
    CString str2 = _T("结果状态");
#else
	CString str1 = /*_T("开入")*/g_sLangTxt_Native_BinX;
	CString str2 = /*_T("结果状态")*/g_sLangTxt_Native_result_status;
#endif
    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);
    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);
        strName = str1 + strTemp + str2;
        strID.Format("StateBin%d", (nIndex + 1));
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_nrBinSwitchCount[nIndex]);
    }

    if(g_nBinExCount > 0)
    {
        CSttXmlSerializeBase *pXmlStateBinEx = pXmlSierialize->xml_serialize("StateBinEx", "StateBinEx", "StateBinEx", stt_ParaGroupKey());

        if(pXmlStateBinEx != NULL)
        {
            for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
            {
#ifdef NOT_USE_XLANGUAGE
                strTemp.Format(_T("扩展%d"), nIndex + 1);
#else
		strTemp.Format(/*_T("扩展%d")*/g_sLangTxt_Native_extend.GetString(), nIndex + 1);
#endif
                strName = str1 + strTemp + str2;
                strID.Format("StateBinEx%d", (nIndex + 1));
                pXmlStateBinEx->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_nrBinExSwitchCount[nIndex]);
            }
        }
    }

    stt_xml_serialize_act_rcd(pResults, pXmlSierialize);
}


CSttXmlSerializeBase *stt_xml_serialize(tmt_async_manual_test *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//	stt_xml_serialize((PTMT_PARAS_HEAD)pParas, pXmlSierialize);
	CSttXmlSerializeBase *pXmlParas = pXmlSierialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if(pXmlParas  != NULL)
	{
		stt_xml_serialize(&pParas->m_oParas, pXmlParas);
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSierialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if(pXmlResults  != NULL)
	{
		stt_xml_serialize(&pParas->m_oResult, pXmlResults);
	}

	return pXmlParas;
}


#include"../../../SttCmd/SttTestCmd.h"
#include"../../../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_AsyncManualTest()
{
	tmt_AsyncManualTest oAsyncManuTest;
	oAsyncManuTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oAsyncManuTest.m_oParas, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("AsyncManualTestDemo.xml");
	//   pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

