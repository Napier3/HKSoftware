#include "stdafx.h"
#include "tmt_fault_gradient_test.h"
#include"../../../SttCmd/SttTestCmd.h"
#include"../../../../../Module/API/GlobalConfigApi.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
////////////////////////////////////参数读写
void stt_xml_serialize(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_base(pParas, pXmlSierialize);
	stt_xml_serialize_FaultGradientSetting(pParas, pXmlSierialize);
	stt_xml_serialize_FaultGradientError(pParas, pXmlSierialize);
	stt_xml_serialize_binary_AndOr(pParas, pXmlSierialize);
	stt_xml_serialize_binary_in(pParas, pXmlSierialize);
	stt_xml_serialize_binary_out(pParas, pXmlSierialize);
	
}

//界面 基础值 序列化
void stt_xml_serialize_base(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("变化始值", "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize("变化终值", "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize("变化步长", "Step", "", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize("故障时间(秒)", "FaultTime", "s", "set", pParas->m_fFaultTime);
	pXmlSierialize->xml_serialize("测试返回系数", "VaryMode", "", "number", pParas->m_nTestMode);
	
	pXmlSierialize->xml_serialize("故障模式", "FaultMode", "", "UIRampType", pParas->m_nFaultMode);
	pXmlSierialize->xml_serialize("变化量", "ChangeValue", "", "UIRampChannel", pParas->m_nChangeValue);
	pXmlSierialize->xml_serialize("测试通道类型", "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize("短路电压值", "ShorVmValue", "V", "set", pParas->m_fShortVm);
	pXmlSierialize->xml_serialize("短路电压类型","ShorVmType","","number",pParas->m_nShortVmType);
	pXmlSierialize->xml_serialize("短路电流", "ShortVa", "A", "number", pParas->m_fShortVa);
	pXmlSierialize->xml_serialize("阻抗角", "ImpedanceAngel", "°", "number", pParas->m_fAngle);

	pXmlSierialize->xml_serialize("变化前时间(秒)", "_PrepareTime", "s", "set", pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("故障前时间(秒)", "_PreFaultTime", "s", "set", pParas->m_fPreFaultTime );
	pXmlSierialize->xml_serialize("故障前电压", "_PrepareFaultVm", "V", "number", pParas->m_fPreFaultEDU);
	pXmlSierialize->xml_serialize("故障前电流","_PrepareFaultVa","A","number",pParas->m_fPreFaultEDI);
	pXmlSierialize->xml_serialize("故障前相角", "_PreFaultAngle", "°", "number", pParas->m_fEDUaIaAngle);
}

//开入量 逻辑或与
void stt_xml_serialize_binary_AndOr(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
}

//开入量 
void stt_xml_serialize_binary_in(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("开入A选择","_BinSelectA","","BOOL",pParas->m_binIn[0].nSelect);
	pXmlSierialize->xml_serialize("开入B选择","_BinSelectB","","BOOL",pParas->m_binIn[1].nSelect);
	pXmlSierialize->xml_serialize("开入C选择","_BinSelectC","","BOOL",pParas->m_binIn[2].nSelect);
	pXmlSierialize->xml_serialize("开入D选择","_BinSelectD","","BOOL",pParas->m_binIn[3].nSelect);
	pXmlSierialize->xml_serialize("开入E选择","_BinSelectE","","BOOL",pParas->m_binIn[4].nSelect);
	pXmlSierialize->xml_serialize("开入F选择","_BinSelectF","","BOOL",pParas->m_binIn[5].nSelect);
	pXmlSierialize->xml_serialize("开入G选择","_BinSelectG","","BOOL",pParas->m_binIn[6].nSelect);
	pXmlSierialize->xml_serialize("开入H选择","_BinSelectH","","BOOL",pParas->m_binIn[7].nSelect);
	pXmlSierialize->xml_serialize("开入I选择","_BinSelectI","","BOOL",pParas->m_binIn[8].nSelect);
	pXmlSierialize->xml_serialize("开入J选择","_BinSelectJ","","BOOL",pParas->m_binIn[9].nSelect);

}

//常态开出 故障开出
void stt_xml_serialize_binary_out(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("常态开出1状态","_BoutNomal1","","DOutputState",pParas->m_binOut[0][0].nState);
	pXmlSierialize->xml_serialize("常态开出2状态","_BoutNomal2","","DOutputState",pParas->m_binOut[0][1].nState);
	pXmlSierialize->xml_serialize("常态开出3状态","_BoutNomal3","","DOutputState",pParas->m_binOut[0][2].nState);
	pXmlSierialize->xml_serialize("常态开出4状态","_BoutNomal4","","DOutputState",pParas->m_binOut[0][3].nState);
	pXmlSierialize->xml_serialize("常态开出5状态","_BoutNomal5","","DOutputState",pParas->m_binOut[0][4].nState);
	pXmlSierialize->xml_serialize("常态开出6状态","_BoutNomal6","","DOutputState",pParas->m_binOut[0][5].nState);
	pXmlSierialize->xml_serialize("常态开出7状态","_BoutNomal7","","DOutputState",pParas->m_binOut[0][6].nState);
	pXmlSierialize->xml_serialize("常态开出8状态","_BoutNomal8","","DOutputState",pParas->m_binOut[0][7].nState);
	pXmlSierialize->xml_serialize("常态开出9状态","_BoutNomal9","","DOutputState",pParas->m_binOut[0][8].nState);
	pXmlSierialize->xml_serialize("常态开出10状态","_BoutNomal10","","DOutputState",pParas->m_binOut[0][9].nState);

	pXmlSierialize->xml_serialize("故障态开出1状态","_BoutError1","","DOutputState",pParas->m_binOut[1][0].nState);
	pXmlSierialize->xml_serialize("故障态开出2状态","_BoutError2","","DOutputState",pParas->m_binOut[1][1].nState);
	pXmlSierialize->xml_serialize("故障态开出3状态","_BoutError3","","DOutputState",pParas->m_binOut[1][2].nState);
	pXmlSierialize->xml_serialize("故障态开出4状态","_BoutError4","","DOutputState",pParas->m_binOut[1][3].nState);
	pXmlSierialize->xml_serialize("故障态开出5状态","_BoutError5","","DOutputState",pParas->m_binOut[1][4].nState);
	pXmlSierialize->xml_serialize("故障态开出6状态","_BoutError6","","DOutputState",pParas->m_binOut[1][5].nState);
	pXmlSierialize->xml_serialize("故障态开出7状态","_BoutError7","","DOutputState",pParas->m_binOut[1][6].nState);
	pXmlSierialize->xml_serialize("故障态开出8状态","_BoutError8","","DOutputState",pParas->m_binOut[1][7].nState);
	pXmlSierialize->xml_serialize("故障态开出9状态","_BoutError9","","DOutputState",pParas->m_binOut[1][8].nState);
	pXmlSierialize->xml_serialize("故障态开出10状态","_BoutError10","","DOutputState",pParas->m_binOut[1][9].nState);
}

//整定值 
void stt_xml_serialize_FaultGradientSetting(tmt_faultGradientParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
#ifndef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize(/*"电压整定动作值"*/g_sLangTxt_Native_VolSetActValue.GetString(), "USet", "V", "float", pParas->m_fUSet);
    pXmlSierialize->xml_serialize(/*"电流整定动作值"*/g_sLangTxt_Native_CurSetActValue.GetString(), "ISet", "A", "float", pParas->m_fISet);
    pXmlSierialize->xml_serialize("阻抗角整定动作值", "ImpAngleSet", "°", "float", pParas->m_fImpAngleSet);
    pXmlSierialize->xml_serialize("短路阻抗整定动作值", "ShortZImp", "Ω", "float", pParas->m_fShortZImp);
    pXmlSierialize->xml_serialize(/*"频率整定动作值"*/g_sLangTxt_Native_FreqSetActValue.GetString(), "HzSet", "Hz", "float", pParas->m_fHzSet);
    pXmlSierialize->xml_serialize(/*"边界角1整定值"*/g_sLangTxt_Native_BoundaryAngle1SetVal.GetString(), "AngleFSet", "°", "float", pParas->m_fAngleFSet);
    pXmlSierialize->xml_serialize(/*"边界角2整定值"*/g_sLangTxt_Native_BoundaryAngle2SetVal.GetString(), "AngleSSet", "°", "float", pParas->m_fAngleSSet);
    pXmlSierialize->xml_serialize(/*"最大灵敏角整定值"*/g_sLangTxt_Native_MaxSensitivityAngleSetVal.GetString(), "MaxAngleSet", "°", "float", pParas->m_fMaxAngleSet);
    pXmlSierialize->xml_serialize(/*"返回系数整定值"*/g_sLangTxt_Native_FeedbackCoefSettingVal.GetString(), "RetCoefSet", "", "float", pParas->m_fRetCoefSet);
#else
#endif
}

//评估 误差值 
void stt_xml_serialize_FaultGradientError(tmt_faultGradientParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("电压动作值绝对误差","UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize("电压动作值相对误差","UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize("电压动作值误差判断逻辑","UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("电流动作值绝对误差","IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize("电流动作值相对误差","IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize("电流动作值误差判断逻辑","IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("阻抗角动作值绝对误差", "ImpAngleActVal_AbsErr", "", "float", pParas->m_fImpAngleActVal_AbsErr);
	pXmlSierialize->xml_serialize("阻抗角动作值相对误差", "ImpAngleActVal_RelErr", "", "float", pParas->m_fImpAngleActVal_RelErr);
	pXmlSierialize->xml_serialize("阻抗角动作值误差判断逻辑", "ImpAngleActVal_ErrorLogic", "", "number", pParas->m_nImpAngleActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("短路阻抗动作值绝对误差", "ShortZImpActVal_AbsErr", "", "float", pParas->m_fShortZImpActVal_AbsErr);
	pXmlSierialize->xml_serialize("短路阻抗动作值相对误差", "ShortZImpActVal_RelErr", "", "float", pParas->m_fShortZImpActVal_RelErr);
	pXmlSierialize->xml_serialize("短路阻抗动作值误差判断逻辑", "ShortZImpActVal_ErrorLogic", "", "number", pParas->m_nShortZImpActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("频率动作值绝对误差","HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);	
	pXmlSierialize->xml_serialize("频率动作值相对误差","HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);	
	pXmlSierialize->xml_serialize("频率动作值误差判断逻辑","HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);	
#ifndef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize(/*"边界角1绝对误差"*/g_sLangTxt_Native_BndryAng1AbsErr.GetString(), "AngleF_AbsErr", "°", "float", pParas->m_fAngleF_AbsErr);
	pXmlSierialize->xml_serialize(/*"边界角1相对误差"*/g_sLangTxt_Native_BndryAng1RelErr.GetString(), "AngleF_RelErr", "", "float", pParas->m_fAngleF_RelErr);
	pXmlSierialize->xml_serialize(/*"边界角1误差判断逻辑"*/g_sLangTxt_Native_BndryAng1ErrDetectLogic.GetString(), "AngleF_ErrorLogic", "", "number", pParas->m_nAngleF_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"边界角2绝对误差"*/g_sLangTxt_Native_BndryAng2AbsErr.GetString(), "AngleS_AbsErr", "°", "float", pParas->m_fAngleS_AbsErr);
	pXmlSierialize->xml_serialize(/*"边界角2相对误差"*/g_sLangTxt_Native_BndryAng2RelErr.GetString(), "AngleS_RelErr", "", "float", pParas->m_fAngleS_RelErr);
	pXmlSierialize->xml_serialize(/*"边界角2误差判断逻辑"*/g_sLangTxt_Native_BndryAng2ErrDetectLogic.GetString(), "AngleS_ErrorLogic", "", "number", pParas->m_nAngleS_ErrorLogic);
#else
#endif
    pXmlSierialize->xml_serialize("最大灵敏角绝对误差","MaxAngle_AbsErr","°","float",pParas->m_fMaxAngle_AbsErr);
	pXmlSierialize->xml_serialize("最大灵敏角相对误差","MaxAngle_RelErr","","float",pParas->m_fMaxAngle_RelErr);
	pXmlSierialize->xml_serialize("最大灵敏角误差判断逻辑","MaxAngle_ErrorLogic","","number",pParas->m_nMaxAngle_ErrorLogic);	
	pXmlSierialize->xml_serialize("返回系数绝对误差", "RetCoef_AbsErr", "", "float", pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize("返回系数相对误差", "RetCoef_RelErr", "", "float", pParas->m_fRetCoef_RelErr);
	pXmlSierialize->xml_serialize("返回系数误差判断逻辑", "RetCoef_ErrorLogic", "", "number", pParas->m_nRetCoef_ErrorLogic);

}

/////////////////////////////////////////////结果 读写
void stt_xml_serialize(tmt_faultGradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("动作值","TripValue","A/V","number",pResults->m_fTripValue);
	pXmlSierialize->xml_serialize("动作时间","TripTime","s","number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("返回值","ReturnValue","A/V","number",pResults->m_fReturnValue);
	pXmlSierialize->xml_serialize("返回系数","ReturnCoef","","number",pResults->m_fReturnCoef);
	pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);

	pXmlSierialize->xml_serialize("电压动作值误差","TripUErrVal","","number",pResults->m_fTripUErrVal);
	pXmlSierialize->xml_serialize("电流动作值误差","TripIErrVal","","number",pResults->m_fTripIErrVal);
	pXmlSierialize->xml_serialize("频率动作值误差","TripHzErrVal","","number",pResults->m_fTripHzErrVal);
	pXmlSierialize->xml_serialize("阻抗角动作值误差", "ImpAngleErrVal", "", "number", pResults->m_fImpAngleErrVal);
	pXmlSierialize->xml_serialize("短路阻抗动作值误差", "ImpAngleErrVal", "", "number", pResults->m_fShortZImp);
	pXmlSierialize->xml_serialize("返回系数误差","RetCoefErrVal","","number",pResults->m_fRetCoefErrVal);
	pXmlSierialize->xml_serialize("最大灵敏角误差","MaxAngleErrVal","","number",pResults->m_fMaxAngleErrVal);
	
	pXmlSierialize->xml_serialize("开入1动作值","TripValueA","A/V","number",pResults->m_fTripValueChl[0]);
	pXmlSierialize->xml_serialize("开入2动作值","TripValueB","A/V","number",pResults->m_fTripValueChl[1]);
	pXmlSierialize->xml_serialize("开入3动作值","TripValueC","A/V","number",pResults->m_fTripValueChl[2]);
	pXmlSierialize->xml_serialize("开入4动作值","TripValueD","A/V","number",pResults->m_fTripValueChl[3]);
	pXmlSierialize->xml_serialize("开入5动作值","TripValueE","A/V","number",pResults->m_fTripValueChl[4]);
	pXmlSierialize->xml_serialize("开入6动作值","TripValueF","A/V","number",pResults->m_fTripValueChl[5]);
	pXmlSierialize->xml_serialize("开入7动作值","TripValueG","A/V","number",pResults->m_fTripValueChl[6]);
	pXmlSierialize->xml_serialize("开入8动作值","TripValueH","A/V","number",pResults->m_fTripValueChl[7]);

	pXmlSierialize->xml_serialize("边界角1","AngleF","","number",pResults->m_oMaxAngle.m_fAngleF);
	pXmlSierialize->xml_serialize("边界角2","AngleS","","number",pResults->m_oMaxAngle.m_fAngleS);
	pXmlSierialize->xml_serialize("最大灵敏角","MaxAngle","","number",pResults->m_oMaxAngle.m_fMaxAngle);

	if (g_nBinExCount>0)
	{
		CSttXmlSerializeBase *pXmlTripValueEx = pXmlSierialize->xml_serialize("TripValueEx", "TripValueEx", "TripValueEx", stt_ParaGroupKey());

		if (pXmlTripValueEx != NULL)
		{
			CString strName,strID,strTemp;

			CString str1 = _T("开入");
			CString str1Ex = _T("开入扩展");
			CString str2 = _T("动作值");

			for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
			{
				strTemp.Format(_T("%d"),nIndex+1);
				strName = str1Ex + strTemp + str2;

				strID.Format("TripValueEx%d",(nIndex+1));
				pXmlTripValueEx->xml_serialize(strName.GetString(),strID.GetString(),"","A/V",pResults->m_fTripValueExChl[nIndex]);
			}
		}
	}
}

////////////////////////////////
void stt_xml_serialize_write_FaultGradientTest()
{
	tmt_faultGradientTest oFGTest;
	oFGTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oFGTest.m_oFaultGradientParas, pMacroParas);

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("FaultGradientTestDemo.xml");

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}


