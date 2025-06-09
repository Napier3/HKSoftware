#include "stdafx.h"
#include "tmt_ulock_overcurrent_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_ULockOverCurrentParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_ULockOverCurrentParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_ULockOverCurrentParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_ULockOverCurrentParasEx));
	pParas->init();
}

void stt_init_results(tmt_ULockOverCurrentResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_ULockOverCurrentResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_ULockOverCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("变化始值", "BeginVal", "", "set",pParas->m_fStart);
	pXmlSierialize->xml_serialize("变化终值", "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize("测试精度", "Step", "", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize("步长时间", "StepTime", "s", "set", pParas->m_fStepTime);
	pXmlSierialize->xml_serialize("故障类型", "FaultType", "", "PsuFYBSFaultType",pParas->m_nULockFaultType);
	pXmlSierialize->xml_serialize("短路电压", "VSet1", "V", "set", pParas->m_fSCVoltage);
	pXmlSierialize->xml_serialize("短路电流", "ISet1", "A", "set",pParas->m_fSCCurrent);
	pXmlSierialize->xml_serialize("阻抗角", "Z1Ph", "°", "number", pParas->m_fImpAngle);
	pXmlSierialize->xml_serialize("是否测试返回值", "VaryMode", "", "number", pParas->m_nTestMode);

	pXmlSierialize->xml_serialize("低电压(V)", "Vzd", "", "number", pParas->m_fVzd);
	pXmlSierialize->xml_serialize("负序电压(V)", "V2zd", "", "number", pParas->m_fV2zd);
	pXmlSierialize->xml_serialize("动作电流(A)", "Izd", "", "number", pParas->m_fIzd);
	pXmlSierialize->xml_serialize("延时时间(s)", "T1", "", "number", pParas->m_fT1);
	pXmlSierialize->xml_serialize("最大灵敏角(°)", "Phimax", "", "number", pParas->m_fPhimax);
	pXmlSierialize->xml_serialize("动作区大小(°)", "PhiSize", "", "number", pParas->m_fPhiSize);
	pXmlSierialize->xml_serialize("动作方向", "IPoint", "", "number", pParas->m_nIPoint);
	pXmlSierialize->xml_serialize("低电压定义", "USetMode", "", "number", pParas->m_nUSetMode);
#else
  pXmlSierialize->xml_serialize(/* "变化始值" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "", "set", pParas->m_fStart);
  pXmlSierialize->xml_serialize(/* "变化终值" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "", "set", pParas->m_fStop);
  pXmlSierialize->xml_serialize(/* "测试精度" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "", "set", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "步长时间" */ g_sLangTxt_Native_StepTimes.GetString(), "StepTime", "s", "set", pParas->m_fStepTime);
  pXmlSierialize->xml_serialize(/* "故障类型" */ g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "", "PsuFYBSFaultType", pParas->m_nULockFaultType);
  pXmlSierialize->xml_serialize(/* "短路电压" */ g_sLangTxt_Native_ShortCircuitV.GetString(), "VSet1", "V", "set", pParas->m_fSCVoltage);
  pXmlSierialize->xml_serialize(/* "短路电流" */ g_sLangTxt_Native_ShortCircuit.GetString(), "ISet1", "A", "set", pParas->m_fSCCurrent);
  pXmlSierialize->xml_serialize(/* "阻抗角" */ g_sLangTxt_Native_ImpedanceAngles.GetString(), "Z1Ph", "°", "number", pParas->m_fImpAngle);
  pXmlSierialize->xml_serialize(/* "是否测试返回值" */ g_sLangTxt_Native_TestReturnValue.GetString(), "VaryMode", "", "number", pParas->m_nTestMode);

  pXmlSierialize->xml_serialize(/* "低电压(V)" */ g_sLangTxt_Native_LowVoltagev.GetString(), "Vzd", "", "number", pParas->m_fVzd);
  pXmlSierialize->xml_serialize(/* "负序电压(V)" */ g_sLangTxt_Native_NegativeSeqVolt.GetString(), "V2zd", "", "number", pParas->m_fV2zd);
  pXmlSierialize->xml_serialize(/* "动作电流(A)" */ g_sLangTxt_Native_ActionCurrent.GetString(), "Izd", "", "number", pParas->m_fIzd);
  pXmlSierialize->xml_serialize(/* "延时时间(s)" */ g_sLangTxt_Native_DelayTimes.GetString(), "T1", "", "number", pParas->m_fT1);
  pXmlSierialize->xml_serialize(/* "最大灵敏角(°)" */ g_sLangTxt_Gradient_MaxSenAngle.GetString(), "Phimax", "", "number", pParas->m_fPhimax);
  pXmlSierialize->xml_serialize(/* "动作区大小(°)" */ g_sLangTxt_Native_ActionAreaSize.GetString(), "PhiSize", "", "number", pParas->m_fPhiSize);
  pXmlSierialize->xml_serialize(/* "动作方向" */ g_sLangTxt_Native_ActDirection.GetString(), "IPoint", "", "number", pParas->m_nIPoint);
  pXmlSierialize->xml_serialize(/* "低电压定义" */ g_sLangTxt_Native_LowVoltageDef.GetString(), "USetMode", "", "number", pParas->m_nUSetMode);
#endif
	stt_xml_serialize_common(pParas,pXmlSierialize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_ex(tmt_ULockOverCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("变化始值(表达式)", "BeginValExp", "", "string",pParas->m_pszStart);
	pXmlSierialize->xml_serialize("变化终值(表达式)", "EndValExp", "", "string", pParas->m_pszStop );
	pXmlSierialize->xml_serialize("步长时间(表达式)", "StepTimeExp", "", "string", pParas->m_pszStepTime);
	pXmlSierialize->xml_serialize("短路电压(表达式)", "VSet1Exp", "", "string", pParas->m_pszSCVoltage);
	pXmlSierialize->xml_serialize("短路电流(表达式)", "ISet1Exp", "", "string",pParas->m_pszSCCurrent);
	pXmlSierialize->xml_serialize("阻抗角(表达式)", "Z1PhExp", "", "string", pParas->m_pszImpAngle);
#else
  pXmlSierialize->xml_serialize(/* "变化始值(表达式)" */ g_sLangTxt_Native_VarStartValue.GetString(), "BeginValExp", "", "string", pParas->m_pszStart);
  pXmlSierialize->xml_serialize(/* "变化终值(表达式)" */ g_sLangTxt_Native_VarEndValue.GetString(), "EndValExp", "", "string", pParas->m_pszStop);
  pXmlSierialize->xml_serialize(/* "步长时间(表达式)" */ g_sLangTxt_Native_StepTime.GetString(), "StepTimeExp", "", "string", pParas->m_pszStepTime);
  pXmlSierialize->xml_serialize(/* "短路电压(表达式)" */ g_sLangTxt_Native_ShortVolt.GetString(), "VSet1Exp", "", "string", pParas->m_pszSCVoltage);
  pXmlSierialize->xml_serialize(/* "短路电流(表达式)" */ g_sLangTxt_Native_ShortCurr.GetString(), "ISet1Exp", "", "string", pParas->m_pszSCCurrent);
  pXmlSierialize->xml_serialize(/* "阻抗角(表达式)" */ g_sLangTxt_Native_ImpedanceAnglexp.GetString(), "Z1PhExp", "", "string", pParas->m_pszImpAngle);
#endif
	stt_xml_serialize(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_ULockOverCurrentResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize((tmt_GradientResult*)pResults,pXmlSierialize);
}

CSttXmlSerializeBase* stt_xml_serialize( tmt_ULockOverCurrentTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		stt_xml_serialize_ex(&(pTests->m_oTmtParas),  pXmlParas);	//文件的读写
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize(&pTests->m_oTmtResults,  pXmlResults);
	}

	return pXmlParas;
}

