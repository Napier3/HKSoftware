#include "stdafx.h"
#include "tmt_dc_failureprot_test.h"
// #ifdef NOT_USE_XLANGUAGE
// #else
//#include "../../../XLangResource_Native.h"                              

/*#endif*/

void stt_init_paras(tmt_DCFailureProtParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DCFailureProtParas));
	pParas->init();
}

void stt_init_results(tmt_DCFailureProtResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DCFailureProtResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_Common(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("Ⅱ段变化量动作定值" , "DidtActValue", "number", "string",  pParas->m_fActValue_Setting[1]);
	pXmlSierialize->xml_serialize("Ⅱ段动作时间" , "DidtActTime", "无", "number",  pParas->m_fActTime_Setting[1]);
	pXmlSierialize->xml_serialize("Ⅰ段动作电流定值" , "ActValue", "无", "number",  pParas->m_fActValue_Setting[0]);
	pXmlSierialize->xml_serialize("Ⅰ段动作时间" , "ActTime", "无", "number",  pParas->m_fActTime_Setting[0]);

	pXmlSierialize->xml_serialize("故障前时间" , "PreDowntime", "无", "number",  pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("故障时间裕度" , "MarginTime", "无", "number",  pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("故障前电压" , "PreFaultVoltage", "无", "number",  pParas->m_fPreFaultVol);
	pXmlSierialize->xml_serialize("故障前电流" , "PreFaultCurrent", "无", "number",  pParas->m_fPreFaultCur);
	//pXmlSierialize->xml_serialize("保持时间" , "Holdtime", "无", "number",  pParas->m_fHoldTime);
	pXmlSierialize->xml_serialize("电流通道选择" , "CurChanSelect", "无", "number",  pParas->m_nIChanSelect);
	pXmlSierialize->xml_serialize("开入A选择" , "_BinSelectA", "无", "BOOL",  pParas->m_binIn[0].nSelect);
	pXmlSierialize->xml_serialize("开入B选择" , "_BinSelectB", "无", "BOOL",  pParas->m_binIn[1].nSelect);
	pXmlSierialize->xml_serialize("开入C选择" , "_BinSelectC", "无", "BOOL",  pParas->m_binIn[2].nSelect);
	pXmlSierialize->xml_serialize("开入D选择" , "_BinSelectD", "无", "BOOL",  pParas->m_binIn[3].nSelect);
	pXmlSierialize->xml_serialize("开入E选择" , "_BinSelectE", "无", "BOOL",  pParas->m_binIn[4].nSelect);
	pXmlSierialize->xml_serialize("开入F选择" , "_BinSelectF", "无", "BOOL",  pParas->m_binIn[5].nSelect);
	pXmlSierialize->xml_serialize("开入G选择" , "_BinSelectG", "无", "BOOL",  pParas->m_binIn[6].nSelect);
	pXmlSierialize->xml_serialize("开入H选择" , "_BinSelectH", "无", "BOOL",  pParas->m_binIn[7].nSelect);
	pXmlSierialize->xml_serialize("逻辑选择" , "LogicSelect", "无", "BOOL",   pParas->m_nBinLogic);
    pXmlSierialize->xml_serialize("开出1状态" , "_BoutSelect1", "无", "DOutputState",  pParas->m_nStateBOut[0]);
    pXmlSierialize->xml_serialize("开出2状态" , "_BoutSelect2", "无", "DOutputState",  pParas->m_nStateBOut[1]);
    pXmlSierialize->xml_serialize("开出3状态" , "_BoutSelect3", "无", "DOutputState",  pParas->m_nStateBOut[2]);
    pXmlSierialize->xml_serialize("开出4状态" , "_BoutSelect4", "无", "DOutputState",  pParas->m_nStateBOut[3]);
    pXmlSierialize->xml_serialize("开出5状态" , "_BoutSelect5", "无", "DOutputState",  pParas->m_nStateBOut[4]);
    pXmlSierialize->xml_serialize("开出6状态" , "_BoutSelect6", "无", "DOutputState",  pParas->m_nStateBOut[5]);
    pXmlSierialize->xml_serialize("开出7状态" , "_BoutSelect7", "无", "DOutputState",  pParas->m_nStateBOut[6]);
    pXmlSierialize->xml_serialize("开出8状态" , "_BoutSelect8", "无", "DOutputState",  pParas->m_nStateBOut[7]);
	pXmlSierialize->xml_serialize("开出翻转启动方式" , "BoutSwitchMode", "无", "number",  pParas->m_nOutputSwitchMode);
	pXmlSierialize->xml_serialize("开出保持时间" , "BoutHoldTime", "无", "number",  pParas->m_fBoutHoldTime);
	pXmlSierialize->xml_serialize("开出反转时刻" , "BoutTimeTrig", "无", "number",  pParas->m_fBoutTimeTrig);

	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
//	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_FailureProtDidtActValue(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
   pXmlSierialize->xml_serialize("保持时间" , "Holdtime", "无", "number",  pParas->m_fHoldTime);
   pXmlSierialize->xml_serialize("电流变化始值" , "SecCurStart", "无", "number",  pParas->m_fIstart);
   pXmlSierialize->xml_serialize("电流变化终值" , "SecCurEnd", "无", "number",  pParas->m_fIend);
   pXmlSierialize->xml_serialize("电流滑差起始值" , "SecCurDidtStart", "无", "number",  pParas->m_fDidtStart);
   pXmlSierialize->xml_serialize("电流滑差终止值" , "SecCurDidtEnd", "无", "number",  pParas->m_fDidtEnd);
   pXmlSierialize->xml_serialize("电流滑差变化步长" , "SecCurStep", "无", "number",  pParas->m_fDidtStep);

   stt_xml_serialize_Common(pParas,pXmlSierialize);

}
void stt_xml_serialize_FailureProtDidtActTime(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("保持时间" , "Holdtime", "无", "number",  pParas->m_fHoldTime);
	pXmlSierialize->xml_serialize("电流滑差" , "SecCurDidt", "无", "number",  pParas->m_fDidt);
	pXmlSierialize->xml_serialize("电流变化始值" , "SecCurStart", "无", "number",  pParas->m_fIstart);
	pXmlSierialize->xml_serialize("电流变化终值" , "SecCurEnd", "无", "number",  pParas->m_fIend);

	 stt_xml_serialize_Common(pParas,pXmlSierialize);
}
void stt_xml_serialize_FailureProtActValue(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{   

	pXmlSierialize->xml_serialize("Ⅰ段电流变化始值" , "FirCurStart", "无", "number",  pParas->m_fFIstart);
	pXmlSierialize->xml_serialize("Ⅰ段电流变化终值" , "FirCurEnd", "无", "number",  pParas->m_fFIend);
	pXmlSierialize->xml_serialize("Ⅰ段电流变化步长" , "FirCurStep", "无", "number",  pParas->m_fFIstep);
	pXmlSierialize->xml_serialize("整定动作时间" , "TunActionTime", "无", "number",  pParas->m_fFActionTime);

	 stt_xml_serialize_Common(pParas,pXmlSierialize);
}
void stt_xml_serialize_FailureProtActTime(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("Ⅰ段电流" , "FirCurrent", "无", "number",  pParas->m_fFI);
	pXmlSierialize->xml_serialize("倍数" , "Multiple", "无", "number",  pParas->m_fMul);
	pXmlSierialize->xml_serialize("整定动作时间" , "TunActionTime", "无", "number",  pParas->m_fFActionTime);

	 stt_xml_serialize_Common(pParas,pXmlSierialize);
}

void stt_xml_serialize_FailureProtDidtActValue_ex(tmt_DCFailureProtParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("电流变化始值(表达式)" , "SecCurStartExp", "无", "string",  pParas->m_pszIstart);
	pXmlSierialize->xml_serialize("电流变化终值(表达式)" , "SecCurEndExp", "无", "string",  pParas->m_pszIend);
	pXmlSierialize->xml_serialize("电流滑差起始值(表达式)" , "SecCurDidtStartExp", "无", "string",  pParas->m_pszDidtStart);
	pXmlSierialize->xml_serialize("电流滑差终止值(表达式)" , "SecCurDidtEndExp", "无", "string",  pParas->m_pszDidtEnd);
	pXmlSierialize->xml_serialize("电流滑差变化步长(表达式)" , "SecCurStepExp", "无", "string",  pParas->m_pszDidtStep);
	pXmlSierialize->xml_serialize("保持时间(表达式)" , "HoldtimeExp", "无", "string",  pParas->m_pszHoldTime);

	stt_xml_serialize_FailureProtDidtActValue(pParas,pXmlSierialize);
}
void stt_xml_serialize_FailureProtDidtActTime_ex(tmt_DCFailureProtParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("电流滑差(表达式)" , "SecCurDidtExp", "无", "string",  pParas->m_pszDidt);
	pXmlSierialize->xml_serialize("电流变化始值(表达式)" , "SecCurStartExp", "无", "string",  pParas->m_pszIstart);
	pXmlSierialize->xml_serialize("电流变化终值(表达式)" , "SecCurEndExp", "无", "string",  pParas->m_pszIend);
	pXmlSierialize->xml_serialize("保持时间(表达式)" , "HoldtimeExp", "无", "string",  pParas->m_pszHoldTime);

	 stt_xml_serialize_FailureProtDidtActTime(pParas,pXmlSierialize);
}
void stt_xml_serialize_FailureProtActValue_ex(tmt_DCFailureProtParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("Ⅰ段动作电流定值(表达式)" , "ActValueExp", "无", "string",  pParas->m_fActValue_Setting[0]);
	pXmlSierialize->xml_serialize("Ⅰ段电流变化始值(表达式)" , "FirCurStartExp", "无", "string",  pParas->m_pszFIstart);
	pXmlSierialize->xml_serialize("Ⅰ段电流变化终值(表达式)" , "FirCurEndExp", "无", "string",  pParas->m_pszFIend);
	pXmlSierialize->xml_serialize("Ⅰ段电流变化步长(表达式)" , "FirCurStepExp", "无", "string",  pParas->m_pszFIstep);
	pXmlSierialize->xml_serialize("整定动作时间(表达式)" , "TunActionTimeExp", "无", "string",  pParas->m_pszFActionTime);

	stt_xml_serialize_FailureProtActValue(pParas,pXmlSierialize);

}
void stt_xml_serialize_FailureProtActTime_ex(tmt_DCFailureProtParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("Ⅰ段电流(表达式)" , "FirCurrentExp", "无", "string",  pParas->m_pszFI);
	pXmlSierialize->xml_serialize("倍数(表达式)" , "MultipleExp", "无", "string",  pParas->m_pszMul);
	pXmlSierialize->xml_serialize("整定动作时间(表达式)" , "TunActionTimeExp", "无", "string",  pParas->m_pszFActionTime);

	stt_xml_serialize_FailureProtActTime(pParas,pXmlSierialize);

}

void stt_xml_serialize_FailureProtDidtActValue(tmt_DCFailureProtResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
   pXmlSierialize->xml_serialize( "Ⅱ段电流实际变化率" , "SecActionCurrent", "无", "number", pResults->m_fResSACValue);
}
void stt_xml_serialize_FailureProtDidtActTime(tmt_DCFailureProtResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize( "Ⅱ段动作实际时间" , "SecActionTime", "无", "number", pResults->m_fResSATime);
}
void stt_xml_serialize_FailureProtActValue(tmt_DCFailureProtResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
   pXmlSierialize->xml_serialize("Ⅰ段电流实际动作值", "FirActionCurrent", "无", "number", pResults->m_fResFACurValue);
}
void stt_xml_serialize_FailureProtActTime(tmt_DCFailureProtResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
   pXmlSierialize->xml_serialize("Ⅰ段动作实际时间", "FirActionTime", "无", "number", pResults->m_fResFATime);
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DCFailureDidtActValueTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtDidtActValue) == 0)
		{
			stt_xml_serialize_FailureProtDidtActValue_ex(&(pTests->m_oFailureProtTestParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtDidtActTime) == 0)
		{
			stt_xml_serialize_FailureProtDidtActTime_ex(&(pTests->m_oFailureProtTestParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtActValue) == 0)
		{
			stt_xml_serialize_FailureProtActValue_ex(&(pTests->m_oFailureProtTestParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtActTime) == 0)
		{
			stt_xml_serialize_FailureProtActTime_ex(&(pTests->m_oFailureProtTestParas), pXmlParas);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{ 
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtDidtActValue) == 0)
		{
			stt_xml_serialize_FailureProtDidtActValue(&(pTests->m_oFailureProtTestResults), pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtDidtActTime) == 0)
		{
			stt_xml_serialize_FailureProtDidtActTime(&(pTests->m_oFailureProtTestResults), pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtActValue) == 0)
		{
			stt_xml_serialize_FailureProtActValue(&(pTests->m_oFailureProtTestResults), pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtActTime) == 0)
		{
			stt_xml_serialize_FailureProtActTime(&(pTests->m_oFailureProtTestResults), pXmlResults);
		}
		
	}

	return pXmlParas;
}

void stt_xml_serialize_ex(tmt_DCFailureDidtActValueTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly)
{
	if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtDidtActValue) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_FailureProtDidtActValue_ex(&(pTests->m_oFailureProtTestParas), pXmlSerialize);
		}

		stt_xml_serialize_FailureProtDidtActValue(&(pTests->m_oFailureProtTestResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtDidtActTime) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_FailureProtDidtActTime_ex(&(pTests->m_oFailureProtTestParas), pXmlSerialize);
		}

		stt_xml_serialize_FailureProtDidtActTime(&(pTests->m_oFailureProtTestResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtActValue) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_FailureProtActValue_ex(&(pTests->m_oFailureProtTestParas), pXmlSerialize);
		}

		stt_xml_serialize_FailureProtActValue(&(pTests->m_oFailureProtTestResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtActTime) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_FailureProtActTime_ex(&(pTests->m_oFailureProtTestParas), pXmlSerialize);
		}

		stt_xml_serialize_FailureProtActTime(&(pTests->m_oFailureProtTestResults), pXmlSerialize);
	}
}
