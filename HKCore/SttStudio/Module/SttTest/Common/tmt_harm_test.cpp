#include "stdafx.h"
#include "tmt_harm_test.h"
#include "../../../../Module/API/StringApi.h"
#include "tmt_system_config.h"
#include <math.h>

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

long g_nHarmWriteSerialMode = STT_TMT_harm_write_serialize_Mode_ALL; 

void stt_init_paras(tmt_HarmParas *pParas)
{
    pParas->init();
}

void stt_init_results(tmt_HarmResult *pResults)
{
    pResults->init();
}

void tmt_harm_paras::ClearHarmChs_SelectIndex()//把所有谐波通道(2次及以上谐波)的选择置为-1
{
	int i = 0 ,j = 0;

	for(i=0; i<MAX_VOLTAGE_COUNT; i++)
	{
		for (j=2; j<MAX_HARM_COUNT; j++)
		{
			m_uiVOL[i].Harm[j].nSelectIndex = -1;
			m_uiCUR[i].Harm[j].nSelectIndex = -1;
		}	
	}
}

void tmt_harm_paras::SetHarmChsSelectIndex_BeforeClearZero()//点击清零按钮时,标记所有修改的通道
{
	int i = 0 ,j = 0;

	for(i=0; i<MAX_VOLTAGE_COUNT; i++)
	{
		for (j=2; j<MAX_HARM_COUNT; j++)
		{
			if (fabs(m_uiVOL[i].Harm[j].fAmp)>0.0001)
			{
				m_uiVOL[i].Harm[j].nSelectIndex = 1;
			}

			if (fabs(m_uiCUR[i].Harm[j].fAmp)>0.0001)
			{
				m_uiCUR[i].Harm[j].nSelectIndex = 1;
			}
		}	
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///


void stt_xml_serialize(CString strName, CString strID, int nIndex, int nType, tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize, int nHarmCount)
{
    char chName[MAX_PATH], chID[MAX_PATH], chID2[MAX_PATH], chUnit[MAX_PATH], chEnable[MAX_PATH];//dingxy 20240412 新增勾选使能下发，用于打开模板生效
    CString_to_char(strName, chName);
    CString_to_char(strID, chID);
    CSttXmlSerializeBase *pHarmSerialize = pXmlSierialize->xml_serialize(chName, chID, "harm", stt_ParaGroupKey());
	char chSysParaID[10];

    if(pHarmSerialize == NULL)
    {
        return;
    }

    tmt_channel *pHarm = (nType == 0) ? &pParas->m_uiVOL[nIndex] : &pParas->m_uiCUR[nIndex];

    if(nType == 0)
    {
        sprintf(chID, "%s", "U0Amp");
        sprintf(chID2, "%s", "U0Ang");
        sprintf(chUnit, "%s", "V");
		sprintf(chEnable, "%s", "U0Enable");
		sprintf(chSysParaID, "%s", STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    }
    else
    {
        sprintf(chID, "%s", "I0Amp");
        sprintf(chID2, "%s", "I0Ang");
        sprintf(chUnit, "%s", "A");
		sprintf(chEnable, "%s", "I0Enable");
		sprintf(chSysParaID, "%s", STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    }

#ifdef _STT_NOT_IN_TEST_SERVER_
	pHarmSerialize->xml_serialize("基波是否使能", chEnable, "", "BOOL", pHarm->Harm[1].m_bSelect);
#endif

    float fSetValue = 0;

    if(stt_xml_serialize_is_write(pHarmSerialize) && (!pHarm->Harm[1].m_bSelect)) //20220816 zhouhj 在写模式,基波未选择的情况下,基波值写0
    {
#ifdef NOT_USE_XLANGUAGE
        pHarmSerialize->xml_serialize_sys_pata("基波幅值", chID, chUnit, "number", fSetValue,chSysParaID);
#else
		        pHarmSerialize->xml_serialize_sys_pata(/*"基波幅值"*/g_sLangTxt_Native_fundamentalAmp.GetString(), chID, chUnit, "number", fSetValue,chSysParaID);
#endif
    }
    else
    {
#ifdef NOT_USE_XLANGUAGE
        pHarmSerialize->xml_serialize_sys_pata("基波幅值", chID, chUnit, "number", pHarm->Harm[1].fAmp,chSysParaID);
#else
		        pHarmSerialize->xml_serialize_sys_pata(/*"基波幅值"*/g_sLangTxt_Native_fundamentalAmp.GetString(), chID, chUnit, "number", pHarm->Harm[1].fAmp,chSysParaID);
#endif
    }
#ifdef NOT_USE_XLANGUAGE
    pHarmSerialize->xml_serialize("基波相位", chID2, "°", "number", pHarm->Harm[1].fAngle);
#else
	    pHarmSerialize->xml_serialize(/*"基波相位"*/g_sLangTxt_Native_fundamentalPhase.GetString(), chID2, "°", "number", pHarm->Harm[1].fAngle);
#endif
    pHarm->Harm[1].nSelectIndex = 0;
    pHarm->Harm[1].fFreq   =  pParas->m_fBaseFre;
    int nSelectIndex = 1;
    nHarmCount++;//20220516 zhouhj 需要读写的谐波次数需要增加1,为实际解析的谐波次数

    if(nHarmCount > MAX_HARM_COUNT)
    {
        nHarmCount = MAX_HARM_COUNT;
    }

    for(int i  =  2;  i  < nHarmCount ;  i++)
    {
		sprintf(chEnable,   "harm%dEnable",   i);
#ifdef _STT_NOT_IN_TEST_SERVER_
		pHarmSerialize->xml_serialize("是否使能", chEnable, "", "BOOL", pHarm->Harm[i].m_bSelect);
#endif
        if(pHarm->Harm[i].m_bSelect)
        {
#ifdef NOT_USE_XLANGUAGE
            sprintf(chName,   "%d次谐波相位",   i);
#else
		 sprintf(chName,   /*"%d次谐波相位"*/g_sLangTxt_Native_NthHarmPhase.GetString(),   i);
#endif
            sprintf(chID,   "harm%dAng",   i);

			if (!stt_xml_serialize_is_read(pHarmSerialize))//不是读的模式,即注册或者写的模式下
			{
				if (g_nHarmWriteSerialMode == STT_TMT_harm_write_serialize_Mode_NotZero)
				{
					if (fabs(pHarm->Harm[i].fAmp)<0.0001f)
					{
						continue;
					}
				} 
				else if (g_nHarmWriteSerialMode == STT_TMT_harm_write_serialize_Mode_Changed)
				{
					if (pHarm->Harm[i].nSelectIndex != 1)
					{
						continue;
					}
				}
			}

			BOOL bRet = pHarmSerialize->xml_serialize(chName, chID,   "°",   "number",   pHarm->Harm[i].fAngle);

			if(!bRet)
			{
				if(!(pParas->m_bAuto) || pParas->m_oHarmGradient.nHarmIndex != i)
            {
					//占用所有通道对应nHarmIndex的波形位置，简单粗暴
                pHarm->Harm[i].nSelectIndex = -1;//用于SttDeviceBase叠加谐波时过滤
                continue;
            }
			}
#ifdef NOT_USE_XLANGUAGE
            sprintf(chName, "%d次谐波幅值",   i);
#else
			sprintf(chName, /*"%d次谐波幅值"*/g_sLangTxt_Native_NthHarmAmpl.GetString(),   i);
#endif
            sprintf(chID, "harm%dAmp",   i);

            if(pParas->m_nHarmMode == 0)
            {
                pHarmSerialize->xml_serialize(chName,   chID,   chUnit,   "number",   pHarm->Harm[i].fAmp);

				if (stt_xml_serialize_is_read(pHarmSerialize))//zhouhj 20230711 读取完成后,对含有率进行处理赋值
				{
					pHarm->Harm[i].fContent   =     100 * pHarm->Harm[i].fAmp /pHarm->Harm[1].fAmp;
				}
            }
            else
            {
                float fVal;
                pHarmSerialize->xml_serialize(chName,   chID,   chUnit,   "number",  fVal);
                pHarm->Harm[i].fAmp   =   pHarm->Harm[1].fAmp  *  fVal  *  0.01;
            }

            pHarm->Harm[i].nSelectIndex = nSelectIndex++;//从2次谐波开始计数选中的叠加波形
        }

        pHarm->Harm[i].fFreq    =    pParas->m_fBaseFre   *   i;
    }

    if(pHarm->Harm[0].m_bSelect)
    {
#ifdef NOT_USE_XLANGUAGE
        pHarmSerialize->xml_serialize("直流分量",   "DC",   chUnit,   "number",   pHarm->Harm[0].fAmp);
#else
		        pHarmSerialize->xml_serialize(/*"直流分量"*/g_sLangTxt_Native_DCCompVaule.GetString(),   "DC",   chUnit,   "number",   pHarm->Harm[0].fAmp);
#endif
    }
    else
    {
#ifdef NOT_USE_XLANGUAGE
        pHarmSerialize->xml_serialize("直流分量",   "DC",   chUnit,   "number",   fSetValue);
#else
	pHarmSerialize->xml_serialize(/*"直流分量"*/g_sLangTxt_Native_DCCompVaule.GetString(),   "DC",   chUnit,   "number",   fSetValue);
#endif
    }

    if(pHarm->InterHarm.m_bSelect)
    {
        if(nType == 0)
        {
            sprintf(chUnit, "%s", "V");
        }
        else
        {
            sprintf(chUnit, "%s", "A");
        }

        pHarmSerialize->xml_serialize("", "InterHarmAmp",   chUnit,   "number",   pHarm->InterHarm.fAmp);
        pHarmSerialize->xml_serialize("", "InterHarmAng",   "°",   "number",   pHarm->InterHarm.fAngle);
        BOOL bRet = pHarmSerialize->xml_serialize("", "InterHarmFre",   "Hz",   "number",   pHarm->InterHarm.fFreq);

        if(bRet)
        {
            pHarm->InterHarm.nSelectIndex = 1;
        }
    }
}

void stt_xml_serialize_auto(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pAutoSerialize = pXmlSierialize->xml_serialize("自动变化设置", "autoset", "auto", stt_ParaGroupKey());
#else
    CSttXmlSerializeBase *pAutoSerialize = pXmlSierialize->xml_serialize(/*"自动变化设置"*/g_sLangTxt_Native_AutoVarConfig.GetString(), "autoset", "auto", stt_ParaGroupKey());
#endif
    if(pAutoSerialize == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pAutoSerialize->xml_serialize("是否自动变化", "_bAutoChange", "", "BOOL", pParas->m_bAuto);
    pAutoSerialize->xml_serialize("变化量选择", "_Variable", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
    pAutoSerialize->xml_serialize("变化类型选择", "_VarType", "", "PsuGradientType", pParas->m_nGradientTpSelect);
    pAutoSerialize->xml_serialize("变化谐波次数", "_HarmIndex", "", "number", pParas->m_oHarmGradient.nHarmIndex);
    pAutoSerialize->xml_serialize("变化始值", "_BeginVal", "", "number", pParas->m_oHarmGradient.fStart);
    pAutoSerialize->xml_serialize("变化终值", "_EndVal", "", "number", pParas->m_oHarmGradient.fEnd);
    pAutoSerialize->xml_serialize("变化步长", "_StepVal", "", "number", pParas->m_oHarmGradient.fStep);
    pAutoSerialize->xml_serialize("每步时间", "_StepTime", "s", "number", pParas->m_oHarmGradient.fStepTime);
    pAutoSerialize->xml_serialize("测试通道类型", "VarIndexType", "", "number", pParas->m_nVarIndexType);
#else
	pAutoSerialize->xml_serialize(/*"是否自动变化"*/g_sLangTxt_Native_AutoVarStatus.GetString(), "_bAutoChange", "", "BOOL", pParas->m_bAuto);
	pAutoSerialize->xml_serialize(/*"变化量选择"*/g_sLangTxt_Native_VarSelect.GetString(), "_Variable", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
	pAutoSerialize->xml_serialize(/*"变化类型选择"*/g_sLangTxt_Native_VarTypeSelect.GetString(), "_VarType", "", "PsuGradientType", pParas->m_nGradientTpSelect);
	pAutoSerialize->xml_serialize(/*"变化谐波次数"*/g_sLangTxt_Native_VarHarmonicNum.GetString(), "_HarmIndex", "", "number", pParas->m_oHarmGradient.nHarmIndex);
	pAutoSerialize->xml_serialize(/*"变化始值"*/g_sLangTxt_Gradient_Init.GetString(), "_BeginVal", "", "number", pParas->m_oHarmGradient.fStart);
	pAutoSerialize->xml_serialize(/*"变化终值"*/g_sLangTxt_Gradient_Finish.GetString(), "_EndVal", "", "number", pParas->m_oHarmGradient.fEnd);
	pAutoSerialize->xml_serialize(/*"变化步长"*/g_sLangTxt_Gradient_Step.GetString(), "_StepVal", "", "number", pParas->m_oHarmGradient.fStep);
	pAutoSerialize->xml_serialize(/*"每步时间"*/g_sLangTxt_Native_step_time.GetString(), "_StepTime", "s", "number", pParas->m_oHarmGradient.fStepTime);
	pAutoSerialize->xml_serialize(/*"测试通道类型"*/g_sLangTxt_Native_TestChannelType.GetString(), "VarIndexType", "", "number", pParas->m_nVarIndexType);
#endif
}

void stt_xml_serialize(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nHarmCount)
{
    stt_xml_serialize(pParas, pXmlSierialize, MAX_VOLTAGE_COUNT, MAX_CURRENT_COUNT, nHarmCount);
}

void stt_xml_serialize(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum, long nHarmCount)
{
    if(nVolRsNum > MAX_VOLTAGE_COUNT)
    {
        nVolRsNum = MAX_VOLTAGE_COUNT;
    }

    if(nCurRsNum > MAX_CURRENT_COUNT)
    {
        nCurRsNum = MAX_CURRENT_COUNT;
    }
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("输出限时(s)", "_TimeLimit", "s", "number", pParas->m_fOutPutTime);
    pXmlSierialize->xml_serialize("谐波表示方式", "_HarmMode", "", "HarExpression", pParas->m_nHarmMode);
    pXmlSierialize->xml_serialize("基波频率", "_BaseFre", "Hz", "number", pParas->m_fBaseFre);
    //	pXmlSierialize->xml_serialize("是否锁定本次设置值","_bLock","","BOOL",pParas->m_bLock);
    pXmlSierialize->xml_serialize("是否开入停止", "bBinStop", "", "BOOL", pParas->m_bBinStop);
	pXmlSierialize->xml_serialize("电压通道类型选择", "_VarVolChType", "", "number", pParas->m_nVolChSelect);
	pXmlSierialize->xml_serialize("电流通道类型选择", "_VarCurChType", "", "number", pParas->m_nCurChSelect);

#else
	pXmlSierialize->xml_serialize(/*"输出限时(s)"*/g_sLangTxt_Native_outputTimeLimit.GetString(), "_TimeLimit", "s", "number", pParas->m_fOutPutTime);
	pXmlSierialize->xml_serialize(/*"谐波表示方式"*/g_sLangTxt_Native_harmRepresent.GetString(), "_HarmMode", "", "HarExpression", pParas->m_nHarmMode);
	pXmlSierialize->xml_serialize(/*"基波频率"*/g_sLangTxt_Native_fundamentalFreq.GetString(), "_BaseFre", "Hz", "number", pParas->m_fBaseFre);
	//	pXmlSierialize->xml_serialize("是否锁定本次设置值","_bLock","","BOOL",pParas->m_bLock);
	pXmlSierialize->xml_serialize(/*"是否开入停止"*/g_sLangTxt_Native_YNInputStop.GetString(), "bBinStop", "", "BOOL", pParas->m_bBinStop);

	pXmlSierialize->xml_serialize("电压通道类型选择", "_VarVolChType", "", "number", pParas->m_nVolChSelect);
	pXmlSierialize->xml_serialize("电流通道类型选择", "_VarCurChType", "", "number", pParas->m_nCurChSelect);
#endif
	stt_xml_serialize_auto(pParas, pXmlSierialize);

    /**********兼容PTU200L安卓*********/
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        CString strName[] = {_T("Ua"), _T("Ub"), _T("Uc"), _T("Uap"), _T("Ubp"), _T("Ucp"), _T("Ia"), _T("Ib"), _T("Ic"), _T("Iap"), _T("Ibp"), _T("Icp")};
        CString strID[] = {_T("Ua"), _T("Ub"), _T("Uc"), _T("Uap"), _T("Ubp"), _T("Ucp"), _T("Ia"), _T("Ib"), _T("Ic"), _T("Iap"), _T("Ibp"), _T("Icp")};

        for(int i = 0; i < 6; i++)
        {
            stt_xml_serialize(strName[i], strID[i], i, 0, pParas, pXmlSierialize, nHarmCount);
        }

        for(int i = 0; i < 6; i++)
        {
            stt_xml_serialize(strName[i + 6], strID[i + 6], i, 1, pParas, pXmlSierialize, nHarmCount);
        }
    }

    /**********兼容PTU200L安卓*********/
    //新版序列化,U1~U48,i1~i48
    CString strId;

    for(int i = 0; i < nVolRsNum; i++)
    {
        strId.Format(_T("U%d"), i + 1);
        stt_xml_serialize("", strId, i, 0, pParas, pXmlSierialize, nHarmCount);
    }

    for(int i = 0; i < nCurRsNum; i++)
    {
        strId.Format(_T("I%d"), i + 1);
        stt_xml_serialize("", strId, i, 1, pParas, pXmlSierialize, nHarmCount);
    }
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pBinSerialize = pXmlSierialize->xml_serialize("开入量设置", "binset", "bin", stt_ParaGroupKey());
#else
	    CSttXmlSerializeBase *pBinSerialize = pXmlSierialize->xml_serialize(/*"开入量设置"*/g_sLangTxt_Native_InputSet.GetString(), "binset", "bin", stt_ParaGroupKey());
#endif
    if(pBinSerialize == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pBinSerialize->xml_serialize("开入逻辑", "_AndOr", "", "InPutLogic_Psu", pParas->m_oBinaryConfig.m_nBinLogic);
#else
	    pBinSerialize->xml_serialize(/*"开入逻辑"*/g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_oBinaryConfig.m_nBinLogic);
#endif
    stt_xml_serialize_binary_in(pParas->m_oBinaryConfig.m_binIn, pBinSerialize);
    stt_xml_serialize_Exbinary_in(pParas->m_oBinaryConfig.m_binInEx, pBinSerialize);
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pBoutSerialize = pXmlSierialize->xml_serialize("开出量设置", "boutset", "bout", stt_ParaGroupKey());
#else
	    CSttXmlSerializeBase *pBoutSerialize = pXmlSierialize->xml_serialize(/*"开出量设置"*/g_sLangTxt_Gradient_BoutSet.GetString(), "boutset", "bout", stt_ParaGroupKey());
#endif

    if(pBoutSerialize == NULL)
    {
        return;
    }

    stt_xml_serialize_binary_out(pParas->m_oBinaryConfig.m_binOut, pBoutSerialize);
    stt_xml_serialize_Exbinary_out(pParas->m_oBinaryConfig.m_binOutEx, pBoutSerialize);

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
    }

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("动作整定时间","TSet","s","float",pParas->m_fTimeSet);
	pXmlSierialize->xml_serialize("电压整定动作值","USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize("电流整定动作值","ISet","A","float",pParas->m_fISet);

	pXmlSierialize->xml_serialize("动作时间值绝对误差","Ttrip_AbsErr","","float",pParas->m_fTimeValue_AbsErr);
	pXmlSierialize->xml_serialize("动作时间值相对误差","Ttrip_RelErr","","float",pParas->m_fTimeValue_RelErr);
	pXmlSierialize->xml_serialize("动作时间误差判断逻辑","TimeValue_ErrorLogic","","number",pParas->m_nTimeValue_ErrorLogic);
	pXmlSierialize->xml_serialize("电压动作值绝对误差","UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize("电压动作值相对误差","UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize("电压动作值误差判断逻辑","UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("电流动作值绝对误差","IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize("电流动作值相对误差","IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize("电流动作值误差判断逻辑","IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
#else
	pXmlSierialize->xml_serialize(/*"动作整定时间"*/g_sLangTxt_Native_acttuning_time.GetString(),"TSet","s","float",pParas->m_fTimeSet);
	pXmlSierialize->xml_serialize(/*"电压整定动作值"*/g_sLangTxt_Native_VolSetActValue.GetString(),"USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize(/*"电流整定动作值"*/g_sLangTxt_Native_CurSetActValue.GetString(),"ISet","A","float",pParas->m_fISet);

	pXmlSierialize->xml_serialize(/*"动作时间值绝对误差"*/g_sLangTxt_Native_ActTimeValueAbsErr.GetString(),"Ttrip_AbsErr","","float",pParas->m_fTimeValue_AbsErr);
	pXmlSierialize->xml_serialize(/*"动作时间值相对误差"*/g_sLangTxt_Native_ActTimeValueRelErr.GetString(),"Ttrip_RelErr","","float",pParas->m_fTimeValue_RelErr);
	pXmlSierialize->xml_serialize(/*"动作时间误差判断逻辑"*/g_sLangTxt_Native_ActTimeValueErrLogic.GetString(),"TimeValue_ErrorLogic","","number",pParas->m_nTimeValue_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"电压动作值绝对误差"*/g_sLangTxt_Native_VActionValueAbsErr.GetString(),"UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize(/*"电压动作值相对误差"*/g_sLangTxt_Native_VActionValueRelErr.GetString(),"UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize(/*"电压动作值误差判断逻辑"*/g_sLangTxt_Native_VActionValueErrLogic.GetString(),"UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"电流动作值绝对误差"*/g_sLangTxt_Native_IActionValueAbsErr.GetString(),"IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize(/*"电流动作值相对误差"*/g_sLangTxt_Native_IActionValueRelErr.GetString(),"IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize(/*"电流动作值误差判断逻辑"*/g_sLangTxt_Native_IActionValueErrLogic.GetString(),"IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
#endif
}

void stt_xml_serialize_act_rcd(tmt_HarmResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//动作记录,最大64次,根据实际动作情况,上送总的动作信息
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

void stt_xml_serialize(tmt_HarmResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("动作标记", "TripFlag", "", "number", pResults->m_nTripFlag);
    pXmlSierialize->xml_serialize("动作时间", "TripTime", "s", "number", pResults->m_fTripTime);
    pXmlSierialize->xml_serialize("动作值", "ActValue", "s", "number", pResults->m_fActValue);
    pXmlSierialize->xml_serialize("返回值", "ReturnValue", "", "number", pResults->m_fReturnValue);
    pXmlSierialize->xml_serialize("返回系数", "ReturnCoef", "", "number", pResults->m_fReturnCoef);
    pXmlSierialize->xml_serialize("返回时间", "ReturnTime", "", "number", pResults->m_fReturnTime);
#else
	pXmlSierialize->xml_serialize(/*"动作标记"*/g_sLangTxt_Native_action_mark.GetString(), "TripFlag", "", "number", pResults->m_nTripFlag);
	pXmlSierialize->xml_serialize(/*"动作时间"*/g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "s", "number", pResults->m_fTripTime);
	pXmlSierialize->xml_serialize(/*"动作值"*/g_sLangTxt_State_ActionValue.GetString(), "ActValue", "s", "number", pResults->m_fActValue);
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

#include"../../SttCmd/SttTestCmd.h"
#include"../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_HarmTest()
{
    tmt_HarmTest oHarmTest;
    oHarmTest.init();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oHarmTest.m_oHarmParas, pMacroParas, 6, 6, 31);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("HarmTestDemo.xml");
    //    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

CSttXmlSerializeBase *stt_xml_serialize(tmt_harm_test *pHarmTest, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum, long nHarmCount)
{
    stt_xml_serialize((PTMT_PARAS_HEAD)pHarmTest, pXmlSierialize);
    CSttXmlSerializeBase *pXmlParas = pXmlSierialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if(pXmlParas  != NULL)
    {
        stt_xml_serialize(&pHarmTest->m_oHarmParas, pXmlParas, nVolRsNum, nCurRsNum, nHarmCount);
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSierialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if(pXmlResults  != NULL)
    {
        stt_xml_serialize(&pHarmTest->m_oHarmResult, pXmlResults);
    }

    return pXmlParas;
}


/*
void stt_xml_serialize_ex(CString strName, CString strID, int nIndex, int nType, tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize, bool bSel)
{
	char chName[MAX_PATH],chID[MAX_PATH], chName2[MAX_PATH],chID2[MAX_PATH], chUnit[MAX_PATH];
	CString_to_char(strName, chName);
	CString_to_char(strID, chID);
	CSttXmlSerializeBase *pHarmSerialize =pXmlSierialize->xml_serialize(chName, chID, "harm", stt_ParaGroupKey());

	if (pHarmSerialize == NULL)
	{
		return;
	}

	tmt_channel *pHarm = (nType==0) ? &pParas->m_uiVOL[nIndex]:&pParas->m_uiCUR[nIndex];

	if (nType == 0)
	{
		sprintf(chID, "%s", "U0Amp");
		sprintf(chID2, "%s", "U0Ang");
		sprintf(chUnit, "%s", "V");
	}
	else
	{
		sprintf(chID, "%s", "I0Amp");
		sprintf(chID2, "%s", "I0Ang");
		sprintf(chUnit, "%s", "A");
	}

	float fAmp = 0,fAngle = 0;

	pHarmSerialize->xml_serialize("基波幅值",chID,chUnit,"number",pHarm->Harm[1].fAmp);
	pHarmSerialize->xml_serialize("基波相位",chID2,"°","number",pHarm->Harm[1].fAngle);

	pHarm->Harm[1].fFreq  =  pParas->m_fBaseFre;
	for(int i  =  2;     i  <  MAX_HARM_COUNT;   i++)
	{
		sprintf(chName, "%d次谐波幅值", i);
		sprintf(chID, "harm%dAmp", i);
		sprintf(chName2, "%d次谐波相位", i);
		sprintf(chID2, "harm%dAng", i);

		if (stt_xml_serialize_is_write(pXmlSierialize) && bSel)
		{//下发命令
			if (!pHarm->Harm[i].m_bSelect)
			{
				pHarmSerialize->xml_serialize(chName,chID,chUnit,"number", fAmp);
				pHarmSerialize->xml_serialize(chName2,chID2,"°","number",  fAngle);
			}
			else
			{
				pHarmSerialize->xml_serialize(chName,chID,chUnit,"number",pHarm->Harm[i].fAmp);
				pHarmSerialize->xml_serialize(chName2,chID2,"°","number",pHarm->Harm[i].fAngle);
			}
		}
		else
		{

			pHarmSerialize->xml_serialize(chName,chID,chUnit,"number",pHarm->Harm[i].fAmp);
			pHarmSerialize->xml_serialize(chName2,chID2,"°","number",pHarm->Harm[i].fAngle);

		}

		pHarm->Harm[i].fFreq=pParas->m_fBaseFre*i;
	}
	pHarmSerialize->xml_serialize("直流分量","DC",chUnit,"number",pHarm->Harm[0].fAmp);
}
*/


/*
void stt_xml_serialize_ex(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize, bool bSel)
{
	pXmlSierialize->xml_serialize("输出限时","_TimeLimit","s","number",pParas->m_fOutPutTime);
	pXmlSierialize->xml_serialize("谐波表示方式","_HarmMode","","HarExpression",pParas->m_nHarmMode);
	pXmlSierialize->xml_serialize("基波频率","_BaseFre","Hz","number",pParas->m_fBaseFre);
	pXmlSierialize->xml_serialize("是否锁定本次设置值","_bLock","","BOOL",pParas->m_bLock);

	CString strName[]={_T("Ua"),_T("Ub"),_T("Uc"),_T("Uap"),_T("Ubp"),_T("Ucp"),_T("Ia"),_T("Ib"),_T("Ic"),_T("Iap"),_T("Ibp"),_T("Icp")};
	CString strID[]={_T("Ua"),_T("Ub"),_T("Uc"),_T("Uap"),_T("Ubp"),_T("Ucp"),_T("Ia"),_T("Ib"),_T("Ic"),_T("Iap"),_T("Ibp"),_T("Icp")};

	for (int i=0; i<4; i++)
	{
		stt_xml_serialize_ex(strName[i], strID[i], i, 0, pParas, pXmlSierialize,bSel);
	}

	for (int i=0; i<4; i++)
	{
		stt_xml_serialize_ex(strName[i+6], strID[i+6], i, 1, pParas, pXmlSierialize,bSel);
	}

	CSttXmlSerializeBase *pBinSerialize =pXmlSierialize->xml_serialize("开入量设置", "binset", "bin", stt_ParaGroupKey());
	if (pBinSerialize == NULL)
	{
		return;
	}
	pBinSerialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_oBinaryConfig.m_nBinLogic);
	stt_xml_serialize_binary_in(pParas->m_oBinaryConfig.m_binIn,pBinSerialize);
	stt_xml_serialize_Exbinary_in(pParas->m_oBinaryConfig.m_binInEx,pBinSerialize);

	CSttXmlSerializeBase *pBoutSerialize =pXmlSierialize->xml_serialize("开出量设置", "boutset", "bout", stt_ParaGroupKey());
	if (pBoutSerialize == NULL)
	{
		return;
	}
	stt_xml_serialize_binary_out(pParas->m_oBinaryConfig.m_binOut, pBoutSerialize);
	stt_xml_serialize_Exbinary_out(pParas->m_oBinaryConfig.m_binOutEx,pBoutSerialize);
	stt_xml_serialize_auto(pParas, pXmlSierialize);
}

*/
