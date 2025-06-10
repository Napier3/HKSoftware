#include "stdafx.h"
#include "SttTestSysGlobalPara.h"
#include "SttCmd/SttParas.h"
#include "SttCmd/SttMacro.h"
#include"XLangResource_Native.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


TMT_SYSTEM_DEFAULT_OUTPUT_PARAS g_oDefaultOutputPara;
STT_SystemParas g_oSystemParas;
tmt_PtPara g_oPTTestPara;
LocalSysPara g_oLocalSysPara;


//2022-9-19  lijunqing  同样的代码，出现了好几个地方
void stt_SystemParas_GetString(CString &strSysParas)
{
	CSttMacro *pSysConfigMacro = new CSttMacro;
	CSttParas *pSttParas = new CSttParas;
	pSysConfigMacro->AddNewChild(pSttParas);
	CSttDataGroupSerializeRegister oRegister(pSttParas);
	stt_xml_serialize(&g_oSystemParas, &oRegister);
	//此处未完成，需要将系统参数的结构体，转成对象  shaolei
	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	strSysParas = pSysConfigMacro->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	//oIecDataGroup.AddTail(&g_oSttTestResourceMngr.m_oIecDatasMngr);
	delete pSysConfigMacro;
}

void stt_SystemParas_SetString(const CString &strSysParas)
{
	stt_SystemParas_SetString((char*)strSysParas.GetString(), strSysParas.GetLength());
}

void stt_SystemParas_SetString(char *strSysParas, long nLen)
{
	CDataGroup oSysParas;
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oSysParas.SetXml_ASCII(strSysParas, nLen, CDataMngrXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	CDvmData *pDvmData = (CDvmData*)oSysParas.FindByID("StabTime");

	if (pDvmData != NULL)//zhouhj防抖时间界面显示单位ms,实际传参为s,网页端不好处理,在此处处理
	{
		double dStabTimeMs = CString_To_double(pDvmData->m_strValue);
		double dStabTimeS = dStabTimeMs/1000;
		pDvmData->m_strValue.Format(_T("%lf"),dStabTimeS);
	}

	CSttDataGroupSerializeRead oRead(&oSysParas);
	stt_xml_serialize(&g_oSystemParas, &oRead);
	stt_xml_serialize_Peripheral(&g_oSystemParas.m_oPeripheral,&oRead,FALSE);

}

long Global_GetMaxFreq()
{
	long nMaxFreq = g_oLocalSysPara.m_nMaxHarmCount-1;
	nMaxFreq *= 50;


	if (nMaxFreq>4000)
	{
		nMaxFreq = 4000;
	}

	return nMaxFreq;
}

BOOL GetResultStringGradientTest(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults)
{
	if (pValues == NULL)
	{
		return FALSE;
	}

	long nTestMode = 0;////测试类型：0-动作值 1-返回系数 2-最大灵敏角
	long nChannel = va1_type;
	long nType = 0;//幅值、相位、频率
	long nAct = 0;//先判断是否动作
	CDvmValue *pResultValue = NULL;

	if (!pValues->GetValue(_T("VaryMode"),nTestMode))
	{
		return FALSE;
	}

	if (!pValues->GetValue(_T("VarType"),nType))
	{
		return FALSE;
	}

	if (!pValues->GetValue(_T("VarIndex"),nChannel))
	{
		return FALSE;
	}

	if (!pValues->GetValue(_T("ActDsec"),nAct))
	{
		return FALSE;
	}

	CString strUnitString;
	strUnitString = _T("V");


	if (nType == 0)
	{
		if (CHANNAL_TYPE_I(nChannel))
		{
			strUnitString = _T("A");
		}
	}
	else if (nType == 1)
	{
		strUnitString = _T("°");
	}
	else if (nType == 2)
	{
		strUnitString = _T("Hz");
	}

	CDvmValue *pTripValue = (CDvmValue *)pValues->FindByID(_T("TripValue"));
	CDvmValue *pReturnValue = (CDvmValue *)pValues->FindByID(_T("ReturnValue"));
	CDvmValue *pReturnCoef= (CDvmValue *)pValues->FindByID(_T("ReturnCoef"));
	CDvmValue *pAngleF = (CDvmValue *)pValues->FindByID(_T("AngleF"));
	CDvmValue *pAngleS = (CDvmValue *)pValues->FindByID(_T("AngleS"));
	CDvmValue *pMaxAngle= (CDvmValue *)pValues->FindByID(_T("MaxAngle"));

	if ((pTripValue == NULL)||(pReturnValue == NULL)||(pReturnCoef == NULL)||(pAngleF == NULL)
		||(pAngleS == NULL)||(pMaxAngle == NULL))
	{
		return FALSE;
	}

	double dValue = 0.0f;

	if (nTestMode == 2)//先对最大灵敏角做处理
	{
		if (nAct<=0)
		{
			bHasActValue = FALSE;
			return TRUE;
		}
		else
		{
			bHasActValue = TRUE;
			dValue = CString_To_double(pMaxAngle->m_strValue);
			pResultValue = (CDvmValue *)pTestMacroResults.FindByID(_T("MaxAngle"));

			strResultsString += pResultValue->m_strName.GetString();
			strResultsString += ":";
			pMaxAngle->m_strValue.Format(_T("%.3lf"),dValue);
			strResultsString.AppendFormat(_T("%.3lf"),dValue);
			strResultsString += strUnitString;
			strResultsString += ";";

			dValue = CString_To_double(pAngleF->m_strValue);
			pResultValue = (CDvmValue *)pTestMacroResults.FindByID(_T("AngleF"));

			strResultsString += pResultValue->m_strName.GetString();
			strResultsString += ":";
			pAngleF->m_strValue.Format(_T("%.3lf"),dValue);
			strResultsString.AppendFormat(_T("%.3lf"),dValue);
			strResultsString += strUnitString;
			strResultsString += ";";

			dValue = CString_To_double(pAngleS->m_strValue);
			pResultValue = (CDvmValue *)pTestMacroResults.FindByID(_T("AngleS"));

			strResultsString += pResultValue->m_strName.GetString();
			strResultsString += ":";
			pAngleS->m_strValue.Format(_T("%.3lf"),dValue);
			strResultsString.AppendFormat(_T("%.3lf"),dValue);
			strResultsString += strUnitString;
			strResultsString += ";";
			return TRUE;
		}
	}

	//不管是动作值还是返回值,都是先显示动作值
	if ((pTripValue->m_strValue == "未动作")||(nAct<=0))
	{
		bHasActValue = FALSE;
		return TRUE;
	}
	else
	{
		dValue = CString_To_double(pTripValue->m_strValue);
		pResultValue = (CDvmValue *)pTestMacroResults.FindByID(_T("TripValue"));//dxy 20231031 解决动作值乱码

		if ((dValue<= 0.00001)&&(nType != 1))//动作值小于等于0,并且递变类型不为相位
		{
			bHasActValue = FALSE;
			return TRUE;
		}

		bHasActValue = TRUE;
		/*strResultsString += pTripValue->m_strName;*/
		strResultsString += pResultValue->m_strName.GetString();
		strResultsString += ":";
		pTripValue->m_strValue.Format(_T("%.3lf"),dValue);
		strResultsString.AppendFormat(_T("%.3lf"),dValue);
		strResultsString += strUnitString;
		strResultsString += ";";
	}


	if (nTestMode == 1)//如果测试的是返回值
	{
		if (pReturnValue->m_strValue == "未动作")
		{
			strResultsString += pReturnValue->m_strName;
			strResultsString += ":";
#ifdef NOT_USE_XLANGUAGE
			strResultsString += _T("未动作");
#else
			strResultsString += g_sLangTxt_State_NoActioned;
#endif
			strResultsString += ";";
		}
		else
		{
			dValue = CString_To_double(pReturnValue->m_strValue);
			pResultValue = (CDvmValue *)pTestMacroResults.FindByID(_T("ReturnValue"));

			strResultsString += pResultValue->m_strName.GetString();
			strResultsString += ":";
			pReturnValue->m_strValue.Format(_T("%.3lf"),dValue);
			strResultsString.AppendFormat(_T("%.3lf"),dValue);
			strResultsString += strUnitString;
			strResultsString += ";";

			dValue = CString_To_double(pReturnCoef->m_strValue);
			pResultValue = (CDvmValue *)pTestMacroResults.FindByID(_T("ReturnCoef"));

			strResultsString += pResultValue->m_strName.GetString();
			strResultsString += ":";
			pReturnCoef->m_strValue.Format(_T("%.3lf"),dValue);
			strResultsString.AppendFormat(_T("%.3lf"),dValue);
			strResultsString += ";";
		}
	}

	return TRUE;
}

BOOL GetResultStringLineVolGradientTest(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults)
{
	if (pValues == NULL)
	{
		return FALSE;
	}

	long nTestMode = 0;////测试类型：0-动作值 1-返回系数 2-最大灵敏角
	long nChannel = va1_type;
	long nType = 0;//幅值、相位、频率
	long nAct = 0;//先判断是否动作
	CDvmValue *pResultValue = NULL;

	if (!pValues->GetValue(_T("VaryMode"),nTestMode))
	{
		return FALSE;
	}

	if (!pValues->GetValue(_T("VarType"),nType))
	{
		return FALSE;
	}

	if (!pValues->GetValue(_T("VarIndex"),nChannel))
	{
		return FALSE;
	}

	if (!pValues->GetValue(_T("ActDsec"),nAct))
	{
		return FALSE;
	}

	CString strUnitString;
	strUnitString = _T("V");


	if (nType == 0)
	{
		if (LINEVOL_CHANNAL_TYPE_I(nChannel))
		{
			strUnitString = _T("A");
		}
	}
	else if (nType == 1)
	{
		strUnitString = _T("°");
	}
	else if (nType == 2)
	{
		strUnitString = _T("Hz");
	}

	CDvmValue *pTripValue = (CDvmValue *)pValues->FindByID(_T("TripValue"));
	CDvmValue *pReturnValue = (CDvmValue *)pValues->FindByID(_T("ReturnValue"));
	CDvmValue *pReturnCoef= (CDvmValue *)pValues->FindByID(_T("ReturnCoef"));
	CDvmValue *pAngleF = (CDvmValue *)pValues->FindByID(_T("AngleF"));
	CDvmValue *pAngleS = (CDvmValue *)pValues->FindByID(_T("AngleS"));
	CDvmValue *pMaxAngle= (CDvmValue *)pValues->FindByID(_T("MaxAngle"));

	if ((pTripValue == NULL)||(pReturnValue == NULL)||(pReturnCoef == NULL)||(pAngleF == NULL)
		||(pAngleS == NULL)||(pMaxAngle == NULL))
	{
		return FALSE;
	}

	double dValue = 0.0f;

	if (nTestMode == 2)//先对最大灵敏角做处理
	{
		if (nAct<=0)
		{
			bHasActValue = FALSE;
			return TRUE;
		}
		else
		{
			bHasActValue = TRUE;
			dValue = CString_To_double(pMaxAngle->m_strValue);
			strResultsString += pMaxAngle->m_strName;
			strResultsString += ":";
			pMaxAngle->m_strValue.Format(_T("%.3lf"),dValue);
			strResultsString.AppendFormat(_T("%.3lf"),dValue);
			strResultsString += strUnitString;
			strResultsString += ";";

			dValue = CString_To_double(pAngleF->m_strValue);
			strResultsString += pAngleF->m_strName;
			strResultsString += ":";
			pAngleF->m_strValue.Format(_T("%.3lf"),dValue);
			strResultsString.AppendFormat(_T("%.3lf"),dValue);
			strResultsString += strUnitString;
			strResultsString += ";";

			dValue = CString_To_double(pAngleS->m_strValue);
			strResultsString += pAngleS->m_strName;
			strResultsString += ":";
			pAngleS->m_strValue.Format(_T("%.3lf"),dValue);
			strResultsString.AppendFormat(_T("%.3lf"),dValue);
			strResultsString += strUnitString;
			strResultsString += ";";
			return TRUE;
		}
	}

	//不管是动作值还是返回值,都是先显示动作值
	if ((pTripValue->m_strValue == "未动作")||(nAct<=0))
	{
		bHasActValue = FALSE;
		return TRUE;
	}
	else
	{
		dValue = CString_To_double(pTripValue->m_strValue);
		pResultValue = (CDvmValue *)pTestMacroResults.FindByID(_T("TripValue"));

		if ((dValue<= 0.00001)&&(nType != 1))//动作值小于等于0,并且递变类型不为相位
		{
			bHasActValue = FALSE;
			return TRUE;
		}

		bHasActValue = TRUE;
		/*strResultsString += pTripValue->m_strName;*/
		strResultsString += pResultValue->m_strName.GetString();
		strResultsString += ":";
		pTripValue->m_strValue.Format(_T("%.3lf"),dValue);
		strResultsString.AppendFormat(_T("%.3lf"),dValue);
		strResultsString += strUnitString;
		strResultsString += ";";
	}


	if (nTestMode == 1)//如果测试的是返回值
	{
		if (pReturnValue->m_strValue == "未动作")
		{
			strResultsString += pReturnValue->m_strName;
			strResultsString += ":";
#ifdef NOT_USE_XLANGUAGE
			strResultsString += _T("未动作");
#else
			strResultsString += g_sLangTxt_State_NoActioned;
#endif
			strResultsString += ";";
		}
		else
		{
			dValue = CString_To_double(pReturnValue->m_strValue);
			strResultsString += pReturnValue->m_strName;
			strResultsString += ":";
			pReturnValue->m_strValue.Format(_T("%.3lf"),dValue);
			strResultsString.AppendFormat(_T("%.3lf"),dValue);
			strResultsString += strUnitString;
			strResultsString += ";";

			dValue = CString_To_double(pReturnCoef->m_strValue);
			strResultsString += pReturnCoef->m_strName;
			strResultsString += ":";
			pReturnCoef->m_strValue.Format(_T("%.3lf"),dValue);
			strResultsString.AppendFormat(_T("%.3lf"),dValue);
			strResultsString += ";";
		}
	}

	return TRUE;
}

BOOL GetResultStringSequenceGradientTest(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults)
{
	if (pValues == NULL)
	{
		return FALSE;
	}

	long nTestMode = 0;////测试类型：0-动作值 1-返回系数 2-最大灵敏角
	long nChannel = va1_type;
	long nType = 0;//幅值、相位、频率
	long nAct = 0;//先判断是否动作
	CDvmValue *pResultValue = NULL;

	if (!pValues->GetValue(_T("VaryMode"),nTestMode))
	{
		return FALSE;
	}

	if (!pValues->GetValue(_T("VarType"),nType))
	{
		return FALSE;
	}

	if (!pValues->GetValue(_T("VarIndex"),nChannel))
	{
		return FALSE;
	}

	if (!pValues->GetValue(_T("ActDsec"),nAct))
	{
		return FALSE;
	}

	CString strUnitString;
	strUnitString = _T("V");


	if (nType == 0)
	{
		if (SEQUENCE_CHANNAL_TYPE_I(nChannel))
		{
			strUnitString = _T("A");
		}
	}
	else if (nType == 1)
	{
		strUnitString = _T("°");
	}
	else if (nType == 2)
	{
		strUnitString = _T("Hz");
	}

	CDvmValue *pTripValue = (CDvmValue *)pValues->FindByID(_T("TripValue"));
// 	CDvmValue *pReturnValue = (CDvmValue *)pValues->FindByID(_T("ReturnValue"));
// 	CDvmValue *pReturnCoef= (CDvmValue *)pValues->FindByID(_T("ReturnCoef"));
// 	CDvmValue *pAngleF = (CDvmValue *)pValues->FindByID(_T("AngleF"));
// 	CDvmValue *pAngleS = (CDvmValue *)pValues->FindByID(_T("AngleS"));
// 	CDvmValue *pMaxAngle= (CDvmValue *)pValues->FindByID(_T("MaxAngle"));

	if ((pTripValue == NULL)/*||(pReturnValue == NULL)||(pReturnCoef == NULL)||(pAngleF == NULL)*/
		/*||(pAngleS == NULL)||(pMaxAngle == NULL)*/)
	{
		return FALSE;
	}

	double dValue = 0.0f;

// 	if (nTestMode == 2)//先对最大灵敏角做处理
// 	{
// 		if (nAct<=0)
// 		{
// 			bHasActValue = FALSE;
// 			return TRUE;
// 		}
// 		else
// 		{
// 			bHasActValue = TRUE;
// 			dValue = CString_To_double(pMaxAngle->m_strValue);
// 			strResultsString += pMaxAngle->m_strName;
// 			strResultsString += ":";
// 			pMaxAngle->m_strValue.Format(_T("%.3lf"),dValue);
// 			strResultsString.AppendFormat(_T("%.3lf"),dValue);
// 			strResultsString += strUnitString;
// 			strResultsString += ";";
// 
// 			dValue = CString_To_double(pAngleF->m_strValue);
// 			strResultsString += pAngleF->m_strName;
// 			strResultsString += ":";
// 			pAngleF->m_strValue.Format(_T("%.3lf"),dValue);
// 			strResultsString.AppendFormat(_T("%.3lf"),dValue);
// 			strResultsString += strUnitString;
// 			strResultsString += ";";
// 
// 			dValue = CString_To_double(pAngleS->m_strValue);
// 			strResultsString += pAngleS->m_strName;
// 			strResultsString += ":";
// 			pAngleS->m_strValue.Format(_T("%.3lf"),dValue);
// 			strResultsString.AppendFormat(_T("%.3lf"),dValue);
// 			strResultsString += strUnitString;
// 			strResultsString += ";";
// 			return TRUE;
// 		}
// 	}

	//不管是动作值还是返回值,都是先显示动作值
	if ((pTripValue->m_strValue == "未动作")||(nAct<=0))
	{
		bHasActValue = FALSE;
		return TRUE;
	}
	else
	{
		dValue = CString_To_double(pTripValue->m_strValue);

		if ((dValue<= 0.00001)&&(nType != 1))//动作值小于等于0,并且递变类型不为相位
		{
			bHasActValue = FALSE;
			return TRUE;
		}

		pResultValue = (CDvmValue *)pTestMacroResults.FindByID(_T("TripValue"));//dxy 20231031 解决动作值乱码

		bHasActValue = TRUE;
		/*strResultsString += pTripValue->m_strName.GetString();*/
		strResultsString += pResultValue->m_strName.GetString();
		strResultsString += ":";
		pTripValue->m_strValue.Format(_T("%.3lf"),dValue);
		strResultsString.AppendFormat(_T("%.3lf"),dValue);
		strResultsString += strUnitString;
		strResultsString += ";";
	}


// 	if (nTestMode == 1)//如果测试的是返回值
// 	{
// 		if (pReturnValue->m_strValue == "未动作")
// 		{
// 			strResultsString += pReturnValue->m_strName;
// 			strResultsString += ":";
// 			strResultsString += g_sLangTxt_State_NoActioned;
// 			strResultsString += ";";
// 		}
// 		else
// 		{
// 			dValue = CString_To_double(pReturnValue->m_strValue);
// 			strResultsString += pReturnValue->m_strName;
// 			strResultsString += ":";
// 			pReturnValue->m_strValue.Format(_T("%.3lf"),dValue);
// 			strResultsString.AppendFormat(_T("%.3lf"),dValue);
// 			strResultsString += strUnitString;
// 			strResultsString += ";";
// 
// 			dValue = CString_To_double(pReturnCoef->m_strValue);
// 			strResultsString += pReturnCoef->m_strName;
// 			strResultsString += ":";
// 			pReturnCoef->m_strValue.Format(_T("%.3lf"),dValue);
// 			strResultsString.AppendFormat(_T("%.3lf"),dValue);
// 			strResultsString += ";";
// 		}
// 	}

	return TRUE;
}

BOOL GetResultStringULockOverCurrent(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults)
{
	if (pValues == NULL)
	{
		return FALSE;
	}

	long nULockFaultType = 0;//复压闭锁故障类型0-低电压,1-负序电压 2-A相低电流 3-B相低电流  4-C相低电流

	if (!pValues->GetValue(_T("FaultType"),nULockFaultType))
	{
		return FALSE;
	}

	CDvmValue *pTripValue = (CDvmValue *)pValues->FindByID(_T("TripValue"));


	if ((pTripValue == NULL))
	{
		return FALSE;
	}

	double dValue = 0.0f;
	CString strUnitString;
	strUnitString = _T("V");
	CDvmValue *pResultValue = NULL;

	if (nULockFaultType>1)
	{
		strUnitString = _T("A");
	}

	//不管是动作值还是返回值,都是先显示动作值
	if (pTripValue->m_strValue == "未动作")
	{
		bHasActValue = FALSE;
		return TRUE;
	}
	else
	{
		dValue = CString_To_double(pTripValue->m_strValue);

		if ((dValue<= 0.00001))//动作值小于等于0,并且递变类型不为相位
		{
			bHasActValue = FALSE;
			return TRUE;
		}

		pResultValue = (CDvmValue *)pTestMacroResults.FindByID(_T("TripValue"));//zhangyq 20231226 测试结果栏内动作值乱码

		bHasActValue = TRUE;
		strResultsString += pResultValue->m_strName.GetString();
		//strResultsString += pTripValue->m_strName;
		strResultsString += ":";
		pTripValue->m_strValue.Format(_T("%.3lf"),dValue);
		strResultsString.AppendFormat(_T("%.3lf"),dValue);
		strResultsString += strUnitString;
		strResultsString += ";";
	}

	return TRUE;
}

BOOL GetResultStringPowerDirection(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults)
{
	if (pValues == NULL)
	{
		return FALSE;
	}

	long nAct = 0;//先判断是否动作
	CDvmValue *pResultValue = NULL;

	if (!pValues->GetValue(_T("ActDsec"),nAct))
	{
		return FALSE;
	}

	CDvmValue *pActDsecValue = (CDvmValue *)pValues->FindByID(_T("ActDsec"));
	

	if (/*nAct <=0*/pActDsecValue->m_strValue == "未动作" )
	{
		bHasActValue = FALSE;
		return TRUE;
	}

	bHasActValue = TRUE;
	CDvmValue *pAngleF = (CDvmValue *)pValues->FindByID(_T("AngleF"));
	CDvmValue *pAngleS = (CDvmValue *)pValues->FindByID(_T("AngleS"));
	CDvmValue *pMaxAngle= (CDvmValue *)pValues->FindByID(_T("MaxAngle"));

	if (pAngleF == NULL)
	{
		pAngleF = (CDvmValue *)pValues->FindByID(_T("Angle1"));
	}

	if (pAngleS == NULL)
	{
		pAngleS = (CDvmValue *)pValues->FindByID(_T("Angle2"));
	}

	if ((pAngleF != NULL)&&(pAngleS != NULL)&&(pMaxAngle != NULL))
	{
		bHasActValue = TRUE;
		double dValue = 0.0f;
		dValue = CString_To_double(pMaxAngle->m_strValue);
		pResultValue = (CDvmValue *)pTestMacroResults.FindByID(_T("MaxAngle"));
// 		strResultsString += pMaxAngle->m_strName;
		strResultsString += pResultValue->m_strName.GetString();
		strResultsString += ":";
		pMaxAngle->m_strValue.Format(_T("%.3lf"),dValue);
		strResultsString.AppendFormat(_T("%.3lf"),dValue);
		strResultsString += "°;";

		dValue = CString_To_double(pAngleF->m_strValue);
		pResultValue = (CDvmValue *)pTestMacroResults.FindByID(_T("AngleF"));
// 		strResultsString += pAngleF->m_strName;
		strResultsString += pResultValue->m_strName.GetString();
		strResultsString += ":";
		pAngleF->m_strValue.Format(_T("%.3lf"),dValue);
		strResultsString.AppendFormat(_T("%.3lf"),dValue);
		strResultsString += "°;";

		dValue = CString_To_double(pAngleS->m_strValue);
		pResultValue = (CDvmValue *)pTestMacroResults.FindByID(_T("AngleS"));
		strResultsString += pResultValue->m_strName.GetString();
		strResultsString += ":";
		pAngleS->m_strValue.Format(_T("%.3lf"),dValue);
		strResultsString.AppendFormat(_T("%.3lf"),dValue);
		strResultsString += "°;";
	}

	return TRUE;
}

BOOL GetResultStringVoltageActValue(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults)
{
	if (pValues == NULL)
	{
		return FALSE;
	}

	double dValue = 0;
	POS pos = pTestMacroResults.GetHeadPosition();
	while(pos)
	{
		CDvmData* pCurrData = (CDvmData*)pTestMacroResults.GetNext(pos);
		CDvmValue* pResultValue = (CDvmValue*)pValues->FindByID(pCurrData->m_strID);

		if (pResultValue !=NULL)
		{
			if (pResultValue->m_strValue != g_sLangTxt_State_NoActioned)
			{
				if (pResultValue->m_strValue == "未动作")
				{
					pResultValue->m_strValue = g_sLangTxt_State_NoActioned;
				}
				else
				{
					dValue = CString_To_double(pResultValue->m_strValue);

					if ((pCurrData->m_strUnit != "°")&&(dValue<= 0.00001))
					{
						pResultValue->m_strValue = g_sLangTxt_State_NoActioned;
					}
					else if(pCurrData->m_strID != "AngleF"
						&& pCurrData->m_strID != "AngleS"
						&& pCurrData->m_strID != "MaxAngle"
						&& pCurrData->m_strID != "TripTime")
					{
						bHasActValue = TRUE;
						strResultsString += pCurrData->m_strName;
						strResultsString += ":";
						pResultValue->m_strValue.Format(_T("%.3lf"),dValue);
						strResultsString.AppendFormat(_T("%.3lf"),dValue);
						strResultsString += pCurrData->m_strUnit;
						if(pCurrData->m_strID == "TripValue" && !pCurrData->m_strUnit.GetLength())
						{
							strResultsString += "V";
						}
						strResultsString += ";";
					}
				}
				
			}
		}
	}

	return TRUE;
}

BOOL GetResultStringCurrentActValue(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults)
{
	if (pValues == NULL)
	{
		return FALSE;
	}

	double dValue = 0;
	POS pos = pTestMacroResults.GetHeadPosition();
	while(pos)
	{
		CDvmData* pCurrData = (CDvmData*)pTestMacroResults.GetNext(pos);
		CDvmValue* pResultValue = (CDvmValue*)pValues->FindByID(pCurrData->m_strID);

		if (pResultValue !=NULL)
		{
			if (pResultValue->m_strValue != g_sLangTxt_State_NoActioned/*"未动作"*/)
			{
				if (pResultValue->m_strValue == "未动作")
				{
					pResultValue->m_strValue = g_sLangTxt_State_NoActioned;
				}
				else
				{
					dValue = CString_To_double(pResultValue->m_strValue);

					if ((pCurrData->m_strUnit != "°")&&(dValue<= 0.00001))
					{
						pResultValue->m_strValue = g_sLangTxt_State_NoActioned;
					}
					else if(pCurrData->m_strID != "AngleF"
						&& pCurrData->m_strID != "AngleS"
						&& pCurrData->m_strID != "MaxAngle"
						&& pCurrData->m_strID != "TripTime")
					{
						bHasActValue = TRUE;
						strResultsString += pCurrData->m_strName;
						strResultsString += ":";
						pResultValue->m_strValue.Format(_T("%.3lf"),dValue);
						strResultsString.AppendFormat(_T("%.3lf"),dValue);
						if ((pCurrData->m_strID.Find("TripValue") >= 0) && (pCurrData->m_strUnit.GetLength()))
						{
							pCurrData->m_strUnit = "A";//dingxy 20240808 将开入动作值单位由A/V改为A
						}
						strResultsString += pCurrData->m_strUnit;
						if(pCurrData->m_strID == "TripValue" && !pCurrData->m_strUnit.GetLength())
						{
							strResultsString += "A";
						}
						strResultsString += ";";
					}
				}
			}
		}
	}

	return TRUE;
}

BOOL GetResultStringDistanceSearchTest(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults)
{
	if (pValues == NULL)
	{
		return FALSE;
	}

	double dValue = 0;
	POS pos = pTestMacroResults.GetHeadPosition();

	while(pos)
	{
		CDvmData* pCurrData = (CDvmData*)pTestMacroResults.GetNext(pos);
		CDvmValue* pResultValue = (CDvmValue*)pValues->FindByID(pCurrData->m_strID);

		if (pResultValue !=NULL)
	{
		if(pResultValue->m_strValue != g_sLangTxt_State_NoActioned/*"未动作"*/)
		{
				dValue = CString_To_double(pResultValue->m_strValue);

				if(pCurrData->m_strID == "TripZ")
				{
					bHasActValue = TRUE;

					strResultsString += pCurrData->m_strName;
					strResultsString += ":";
					pResultValue->m_strValue.Format(_T("%.3lf"),dValue);
					strResultsString.AppendFormat(_T("%.3lf"),dValue);
					strResultsString += "Ω";
					strResultsString += ";";
				}
				else if(pCurrData->m_strID == "TripZAngle")
				{
					if (dValue<= 0.00001)
					{
						pResultValue->m_strValue = g_sLangTxt_State_NoActioned/*"未动作"*/;
						return TRUE;
					}
					bHasActValue = TRUE;
					strResultsString += pCurrData->m_strName;
					strResultsString += ":";
					pResultValue->m_strValue.Format(_T("%.3lf"),dValue);
					strResultsString.AppendFormat(_T("%.3lf"),dValue);
					strResultsString += "°";
					
				}
			}
		}
	}

	return TRUE;
}

BOOL GetResultStringStateTest( CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults )
{
	if (pValues == NULL)
	{
		return FALSE;
	}

	double dValue = 0;
	BOOL bHasStateResult = FALSE;
	POS pos = pValues->GetHeadPosition();
	while(pos)
	{
		CDvmData* pCurrData = (CDvmData*)pValues->GetNext(pos);
		dValue = CString_To_double(pCurrData->m_strValue);
		//如果开出状态值为0，手动转换为中文未动作
		//if (pCurrData->m_strID.contains("TtripBin"))
		if (pCurrData->m_strID.Find("TtripBin") >= 0)
 		{
			if (dValue <= 0.00001)
			{
				pCurrData->m_strValue = g_sLangTxt_State_NoActioned/*"未动作"*/;
			}
			else
			{
				bHasActValue = TRUE;
			}
 		}
	}
	POS posResult = pTestMacroResults.GetHeadPosition();
	while(posResult)
	{
		CDvmData* pCurrData = (CDvmData*)pTestMacroResults.GetNext(posResult);
		CDvmValue* pResultValue = (CDvmValue*)pValues->FindByID(pCurrData->m_strID);

		if (pResultValue !=NULL)
		{
			bHasStateResult = TRUE;
			if (pResultValue->m_strValue != g_sLangTxt_State_NoActioned/*"未动作"*/)
			{
				if (pResultValue->m_strValue == "未动作")
				{
					pResultValue->m_strValue = g_sLangTxt_State_NoActioned;
				}
				else
				{
					dValue = CString_To_double(pResultValue->m_strValue);

					if ((pCurrData->m_strUnit != "°")&&(dValue<= 0.00001))
					{
						pResultValue->m_strValue = g_sLangTxt_State_NoActioned/*"未动作"*/;
					}
					else
					{
						bHasActValue = TRUE;
						strResultsString += pCurrData->m_strName;
						strResultsString += ":";
						long nPrecision = 3;
						if ((dValue>0.000f)&&(dValue<0.001f))
						{
							if (dValue<0.0001f)
							{
								nPrecision = 5;
							}
							else
							{
								nPrecision = 4;
							}
						}
						//pResultValue->m_strValue = QString::number(dValue,'f',nPrecision);
						CString strFormat;
						strFormat.Format(_T("%%.%df"), nPrecision);
						pResultValue->m_strValue.Format(strFormat, dValue);
						strResultsString += pResultValue->m_strValue;
						strResultsString += pCurrData->m_strUnit;
						strResultsString += ";";
					}
				}
				
			}
		}
	}

	return bHasStateResult;
}

CString Global_GetSoftwareGeneVersion(const CString &strDateString)
{
	CString strTmp1,strTmp2;
	long nYear = 2022,nMonth = 1,nDay = 1;
	long nLenth = strDateString.Find(' ');

	if (nLenth != -1)
	{
		strTmp1 = strDateString.Left(nLenth);

		if(strTmp1 == "Jan")
		{
			nMonth = 1;
		} 	
		else if(strTmp1 == "Feb")
		{
			nMonth = 2;
		}
		else if(strTmp1 == "Mar")
		{
			nMonth = 3;
		}
		else if(strTmp1 == "Apr")
		{
			nMonth = 4;
		}			
		else if(strTmp1 == "May")
		{
			nMonth = 5;
		} 	
		else if(strTmp1 == "Jun")
		{
			nMonth = 6;
		} 	
		else if(strTmp1 == "Jul")
		{
			nMonth = 7;
		}
		else if(strTmp1 == "Aug")
		{
			nMonth = 8;
		}
		else if(strTmp1 == "Sep")
		{
			nMonth = 9;
		}
		else if(strTmp1 == "Oct")
		{
			nMonth = 10;
		}
		else if(strTmp1 == "Nov")
		{
			nMonth = 11;
		}
		else if(strTmp1 == "Dec")
		{
			nMonth = 12;
		}

		strTmp2 = strDateString.Mid(nLenth + 1);
#ifdef _PSX_IDE_QT_
		strTmp1 = strTmp2.simplified();
#endif
		nLenth = strTmp1.Find(' ');

		if (nLenth != -1)
		{
			strTmp2 = strTmp1.Left(nLenth);
			nDay = CString_To_long(strTmp2);
			strTmp2 = strTmp1.Mid(nLenth+1);
			nYear = CString_To_long(strTmp2);
		}
	}

	strTmp1.Format(_T("%ld%02ld%02ld"),nYear,nMonth,nDay);
	return strTmp1;
}
