#include "stdafx.h"
#include "tmt_system_config.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void stt_xml_serialize_WeakRate(PTT_SystemParas pSystemParas,const int &nGroupIndex, CSttXmlSerializeBase *pXmlSierialize)
// {
// 	CString strDesc,strID;
// 	CString strTmp1 = _T("第"),strTmp2,strTmp3 = _T("组弱信号变比");
// 	strTmp2.Format(_T("%d"),nGroupIndex+1);
// 	strDesc = strTmp1 +strTmp2 +strTmp3;
// //	strDesc.Format(_T("%s%d%s"),strTmp1.GetString(), nGroupIndex+1,strTmp2.GetString());
// 	strID.Format(_T("WeakRate%d"),nGroupIndex+1);
// 	CSttXmlSerializeBase *pChildSerialize =pXmlSierialize->xml_serialize(strDesc.GetString(), strID.GetString(), "WeakRate", stt_ParaGroupKey());
//
// 	if (pChildSerialize == NULL)
// 	{
// 		return;
// 	}
//
// 	pChildSerialize->xml_serialize(_T("弱信号PT一次值"),_T("PT_Primary_Weak"),"V","float",pSystemParas->m_fVPrimary_Weak[nGroupIndex]);
// 	pChildSerialize->xml_serialize(_T("弱信号PT二次值"),_T("PT_Secondary_Weak"),"V","float",pSystemParas->m_fVSecondary_Weak[nGroupIndex]);
// 	pChildSerialize->xml_serialize(_T("弱信号CT一次值"),_T("CT_Primary_Weak"),"A","float",pSystemParas->m_fIPrimary_Weak[nGroupIndex]);
// 	pChildSerialize->xml_serialize(_T("弱信号CT二次值"),_T("CT_Secondary_Weak"),"V","float",pSystemParas->m_fISecondary_Weak[nGroupIndex]);
// }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_CurrModule(tmt_GearSetCurModules *pGearSetCurModules, const int &nGroupIndex, CSttXmlSerializeBase *pXmlSierialize)
{
    CString strDesc = _T(""), strID;
//	CString strTmp1 = _T("第"),strTmp2,strTmp3 = _T("组电流模块");
#ifdef NOT_USE_XLANGUAGE
    strDesc += _T("第");
    strDesc.AppendFormat(_T("%d"), nGroupIndex + 1);
    strDesc += _T("组电流模块");
#else
  strDesc += /* _T("第") */ g_sLangTxt_Native_Number;
  strDesc.AppendFormat(_T("%d"), nGroupIndex + 1);
  strDesc += /* _T("组电流模块") */ g_sLangTxt_Native_GroupCurrMod;
#endif
//	strTmp2.Format(_T("%d"),nGroupIndex+1);
//	strDesc = strTmp1 +strTmp2 +strTmp3;
//	strDesc.Format(_T("%s%d%s"),strTmp1.GetString(), nGroupIndex+1,strTmp2.GetString());
    strID.Format(_T("CurrModule%d"), nGroupIndex + 1);
    CSttXmlSerializeBase *pChildSerialize = pXmlSierialize->xml_serialize(strDesc.GetString(), strID.GetString(), "CurrModule", stt_ParaGroupKey());

    if(pChildSerialize == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pChildSerialize->xml_serialize(_T("电流模块位置"), _T("ModulePos"), "", "number", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nModulePos);
    pChildSerialize->xml_serialize(_T("电流模块档位值"), _T("CurModuleGear"), "", "number", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nIPowerMode);
    pChildSerialize->xml_serialize(_T("电流通道最大端口电压"), _T("MaxPortVol"), "", "float", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_fVoltSet);
    pChildSerialize->xml_serialize(_T("合并电流端子"), _T("MergeCurTerminal"), "", "float", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nMergeCurTerminal);
    pChildSerialize->xml_serialize(_T("大电流输出端口"), _T("LargeCurOutTerm"), "", "number", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nLargeCurOutTerm);
#else
  pChildSerialize->xml_serialize(/* _T("电流模块位置") */ g_sLangTxt_Native_CurrModPos.GetString(), _T("ModulePos"), "", "number", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nModulePos);
  pChildSerialize->xml_serialize(/* _T("电流模块档位值") */ g_sLangTxt_Native_CurrModGearVal.GetString(), _T("CurModuleGear"), "", "number", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nIPowerMode);
  pChildSerialize->xml_serialize(/* _T("电流通道最大端口电压") */ g_sLangTxt_Native_CurrChanMaxVolt.GetString(), _T("MaxPortVol"), "", "float", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_fVoltSet);
  pChildSerialize->xml_serialize(/* _T("合并电流端子") */ g_sLangTxt_Native_MergeCurrTerm.GetString(), _T("MergeCurTerminal"), "", "float", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nMergeCurTerminal);
  pChildSerialize->xml_serialize(/* _T("大电流输出端口") */ g_sLangTxt_Highcurrent.GetString(), _T("LargeCurOutTerm"), "", "number", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nLargeCurOutTerm);
#endif
}

void stt_xml_serialize_CurrModules(tmt_GearSetCurModules *pGearSetCurModules, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pChildSerialize = pXmlSierialize->xml_serialize("CurrModules", "CurrModules", "CurrModules", stt_ParaGroupKey());

    if(pChildSerialize == NULL)
    {
        return;
    }

    stt_xml_serialize_ModulesGearSwitch(pGearSetCurModules, pChildSerialize);
}

void stt_xml_serialize_ModulesGearSwitch(tmt_GearSetCurModules *pGearSetCurModules, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("电流模块数量", "CurrModuleNum", "", "number", pGearSetCurModules->m_nCurModuleNum);
#else
  pXmlSierialize->xml_serialize(/* _T("电流模块数量") */ g_sLangTxt_Native_CurrModCount.GetString(), "CurrModuleNum", "", "number", pGearSetCurModules->m_nCurModuleNum);
#endif

    for(int nIndex = 0; nIndex < pGearSetCurModules->m_nCurModuleNum; nIndex++)
    {
        stt_xml_serialize_CurrModule(pGearSetCurModules, nIndex, pXmlSierialize);
    }
}

void stt_xml_serialize_Peripheral(tmt_Peripheral *pPeripheral, CSttXmlSerializeBase *pXmlSierialize, BOOL bUseChildGroup)
{
    CSttXmlSerializeBase *pPeripheralXmlSierialize = pXmlSierialize;

    if(bUseChildGroup)
    {
        pPeripheralXmlSierialize = pXmlSierialize->xml_serialize("Peripheral", "Peripheral", "Peripheral", stt_ParaGroupKey());

        if(pPeripheralXmlSierialize == NULL)
        {
            return;
        }
    }
#ifdef NOT_USE_XLANGUAGE
    pPeripheralXmlSierialize->xml_serialize("4G", "4G", "", "long", pPeripheral->m_b4G);
    pPeripheralXmlSierialize->xml_serialize("蓝牙", "Ble", "", "long", pPeripheral->m_bBle);
    pPeripheralXmlSierialize->xml_serialize("无线网络", "NetWifi", "", "long", pPeripheral->m_bNetWifi);
    pPeripheralXmlSierialize->xml_serialize("有线网络", "NetRj45", "", "long", pPeripheral->m_bNetRj45);
    pPeripheralXmlSierialize->xml_serialize("Lcd背光时长", "LcdTimes", "", "long", pPeripheral->m_nLcdTimes);
	pPeripheralXmlSierialize->xml_serialize("Lcd最大背光亮度", "LcdLight", "", "long", pPeripheral->m_nLcdLight);
#else
  pPeripheralXmlSierialize->xml_serialize("4G", "4G", "", "long", pPeripheral->m_b4G);
  pPeripheralXmlSierialize->xml_serialize(/* "蓝牙" */ g_sLangTxt_State_Bluetooth.GetString(), "Ble", "", "long", pPeripheral->m_bBle);
  pPeripheralXmlSierialize->xml_serialize(/* "无线网络" */ g_sLangTxt_Native_WirelessNet.GetString(), "NetWifi", "", "long", pPeripheral->m_bNetWifi);
  pPeripheralXmlSierialize->xml_serialize(/* "有线网络" */ g_sLangTxt_Native_WiredNet.GetString(), "NetRj45", "", "long", pPeripheral->m_bNetRj45);
  pPeripheralXmlSierialize->xml_serialize(/* "Lcd背光时长" */ g_sLangTxt_Native_LcdBacklightTime.GetString(), "LcdTimes", "", "long", pPeripheral->m_nLcdTimes);
  pPeripheralXmlSierialize->xml_serialize(/* "Lcd最大背光亮度" */ g_sLangTxt_Native_TouchSensitivity.GetString(), "LcdLight", "", "long", pPeripheral->m_nLcdLight);
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_ErrorValues(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize(_T("电流动作值绝对误差(A)"), _T("CurAbsError"), "", "number", pSystemParas->m_fCurValue_AbsError);
    pXmlSierialize->xml_serialize(_T("电流动作值相对误差(%)"), _T("CurRelError"), "", "number", pSystemParas->m_fCurValue_RelError);
    pXmlSierialize->xml_serialize(_T("电压动作值绝对误差(V)"), _T("VolAbsError"), "", "number", pSystemParas->m_fVolValue_AbsError);
    pXmlSierialize->xml_serialize(_T("电压动作值相对误差(%)"), _T("VolRelError"), "", "number", pSystemParas->m_fVolValue_RelError);
    pXmlSierialize->xml_serialize(_T("阻抗动作值绝对误差(Ω)"), _T("ImpAbsError"), "", "number", pSystemParas->m_fImpValue_AbsError);
    pXmlSierialize->xml_serialize(_T("阻抗动作值相对误差(%)"), _T("ImpRelError"), "", "number", pSystemParas->m_fImpValue_RelError);
    pXmlSierialize->xml_serialize(_T("动作时间绝对误差(s)"), _T("TimeAbsError"), "", "number", pSystemParas->m_fTimeValue_AbsError);
    pXmlSierialize->xml_serialize(_T("动作时间相对误差(%)"), _T("TimeRelError"), "", "number", pSystemParas->m_fTimeValue_RelError);
    pXmlSierialize->xml_serialize(_T("相位误差值(°)"), _T("AngError"), "", "number", pSystemParas->m_fAngValue_AbsError);
    pXmlSierialize->xml_serialize(_T("频率误差值(Hz)"), _T("FreError"), "", "number", pSystemParas->m_fFreValue_AbsError);
    pXmlSierialize->xml_serialize(_T("电压滑差误差值(V/s)"), _T("dvdtError"), "", "number", pSystemParas->m_fdvdtValue_AbsError);
    pXmlSierialize->xml_serialize(_T("频率滑差误差值(Hz/s)"), _T("dfdtError"), "", "number", pSystemParas->m_fdfdtValue_AbsError);
    pXmlSierialize->xml_serialize(_T("差动比率制动系数绝对误差"), _T("DiffRateCoefAbsError"), "", "number", pSystemParas->m_fDiffRateCoef_AbsError);
    pXmlSierialize->xml_serialize(_T("差动比率制动系数相对误差(%)"), _T("DiffRateCoefRelError"), "", "number", pSystemParas->m_fDiffRateCoef_RelError);
    pXmlSierialize->xml_serialize(_T("差动谐波制动系数绝对误差"), _T("DiffHarmCoefAbsError"), "", "number", pSystemParas->m_fDiffHarmCoef_AbsError);
    pXmlSierialize->xml_serialize(_T("差动谐波制动系数相对误差(%)"), _T("DiffHarmCoefRelError"), "", "number", pSystemParas->m_fDiffHarmCoef_RelError);
#else
  pXmlSierialize->xml_serialize(/* _T("电流动作值绝对误差(A)") */ g_sLangTxt_Native_CurrentActionError.GetString(), _T("CurAbsError"), "", "number", pSystemParas->m_fCurValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("电流动作值相对误差(%)") */ g_sLangTxt_Native_CurrentActionRelError.GetString(), _T("CurRelError"), "", "number", pSystemParas->m_fCurValue_RelError);
  pXmlSierialize->xml_serialize(/* _T("电压动作值绝对误差(V)") */ g_sLangTxt_Native_VoltageActionError.GetString(), _T("VolAbsError"), "", "number", pSystemParas->m_fVolValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("电压动作值相对误差(%)") */ g_sLangTxt_Native_VoltageActionRelError.GetString(), _T("VolRelError"), "", "number", pSystemParas->m_fVolValue_RelError);
  pXmlSierialize->xml_serialize(/* _T("阻抗动作值绝对误差(Ω)") */ g_sLangTxt_Native_ImpedanceActionError.GetString(), _T("ImpAbsError"), "", "number", pSystemParas->m_fImpValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("阻抗动作值相对误差(%)") */ g_sLangTxt_Native_ImpedanceActionRelError.GetString(), _T("ImpRelError"), "", "number", pSystemParas->m_fImpValue_RelError);
  pXmlSierialize->xml_serialize(/* _T("动作时间绝对误差(s)") */ g_sLangTxt_Native_ActionTimeAbsError.GetString(), _T("TimeAbsError"), "", "number", pSystemParas->m_fTimeValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("动作时间相对误差(%)") */ g_sLangTxt_Native_ActionTimeRelError.GetString(), _T("TimeRelError"), "", "number", pSystemParas->m_fTimeValue_RelError);
  pXmlSierialize->xml_serialize(/* _T("相位误差值(°)") */ g_sLangTxt_Native_PhaseErrorValue.GetString(), _T("AngError"), "", "number", pSystemParas->m_fAngValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("频率误差值(Hz)") */ g_sLangTxt_Native_FreqErrorValue.GetString(), _T("FreError"), "", "number", pSystemParas->m_fFreValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("电压滑差误差值(V/s)") */ g_sLangTxt_Native_VoltSlipErrorValue.GetString(), _T("dvdtError"), "", "number", pSystemParas->m_fdvdtValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("频率滑差误差值(Hz/s)") */ g_sLangTxt_Native_FreqSlipErrorValue.GetString(), _T("dfdtError"), "", "number", pSystemParas->m_fdfdtValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("差动比率制动系数绝对误差") */ g_sLangTxt_Native_DiffRatioBrakeAbsError.GetString(), _T("DiffRateCoefAbsError"), "", "number", pSystemParas->m_fDiffRateCoef_AbsError);
  pXmlSierialize->xml_serialize(/* _T("差动比率制动系数相对误差(%)") */ g_sLangTxt_Native_DiffRatioBrakeRelError.GetString(), _T("DiffRateCoefRelError"), "", "number", pSystemParas->m_fDiffRateCoef_RelError);
  pXmlSierialize->xml_serialize(/* _T("差动谐波制动系数绝对误差") */ g_sLangTxt_Native_DiffHarmonicBrakeAbsError.GetString(), _T("DiffHarmCoefAbsError"), "", "number", pSystemParas->m_fDiffHarmCoef_AbsError);
  pXmlSierialize->xml_serialize(/* _T("差动谐波制动系数相对误差(%)") */ g_sLangTxt_Native_DiffHarmonicBrakeRelError.GetString(), _T("DiffHarmCoefRelError"), "", "number", pSystemParas->m_fDiffHarmCoef_RelError);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_SystemParas(pSystemParas, pXmlSierialize);

#ifdef _STT_NOT_IN_TEST_SERVER_
	stt_xml_serialize_AuxDC(pSystemParas, pXmlSierialize);//20240226 底层关闭系统参数修改辅助直流入口
	stt_xml_serialize_ModulesGearSwitch(pSystemParas, pXmlSierialize);//20240513 硬件部要求,底层关闭系统参数修改电流功率入口
#endif

    stt_xml_serialize_PeripheralCtrl(pSystemParas, pXmlSierialize);
}

void stt_xml_serialize_AuxDC(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize) //zhouhj 20211016 单独用于辅助直流设置
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("辅助直流电压值", "AuxVolDC", "s", "float", pSystemParas->m_fAuxDC_Vol);
    pXmlSierialize->xml_serialize("辅助直流电流值", "AuxCurDC", "s", "float", pSystemParas->m_fAuxDC_Cur);
#else
  pXmlSierialize->xml_serialize(/* "辅助直流电压值" */ g_sLangTxt_Native_AuxDcVoltageValue.GetString(), "AuxVolDC", "s", "float", pSystemParas->m_fAuxDC_Vol);
  pXmlSierialize->xml_serialize(/* "辅助直流电流值" */ g_sLangTxt_Native_AuxDcCurrentValue.GetString(), "AuxCurDC", "s", "float", pSystemParas->m_fAuxDC_Cur);
#endif
}

void stt_xml_serialize_AppConfig(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize) //zhouhj 20221207 增加用于设置变比
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("输出模拟量", "HasAnalog", " ", "number", pSystemParas->m_nHasAnalog);
	pXmlSierialize->xml_serialize("输出数字量", "HasDigital", " ", "number", pSystemParas->m_nHasDigital);
	pXmlSierialize->xml_serialize("输出弱信号", "HasWeek", " ", "number", pSystemParas->m_nHasWeek);
    pXmlSierialize->xml_serialize("电压变比一次值(第1组)", "_UaPrimary", "kV", "float", pSystemParas->m_fVPrimary[0]);
    pXmlSierialize->xml_serialize("电压变比一次值(第2组)", "_UxPrimary", "kV", "float", pSystemParas->m_fVPrimary[1]);
    pXmlSierialize->xml_serialize("电压变比一次值(第3组)", "_UuPrimary", "kV", "float", pSystemParas->m_fVPrimary[2]);
    pXmlSierialize->xml_serialize("电压变比一次值(第4组)", "_UrPrimary", "kV", "float", pSystemParas->m_fVPrimary[3]);
    pXmlSierialize->xml_serialize("电压变比一次值(第5组)", "_U5Primary", "kV", "float", pSystemParas->m_fVPrimary[4]);
    pXmlSierialize->xml_serialize("电压变比一次值(第6组)", "_U6Primary", "kV", "float", pSystemParas->m_fVPrimary[5]);
    pXmlSierialize->xml_serialize("电压变比二次值(第1组)", "_UaSecondary", "V", "float", pSystemParas->m_fVSecondary[0]);
    pXmlSierialize->xml_serialize("电压变比二次值(第2组)", "_UxSecondary", "V", "float", pSystemParas->m_fVSecondary[1]);
    pXmlSierialize->xml_serialize("电压变比二次值(第3组)", "_UuSecondary", "V", "float", pSystemParas->m_fVSecondary[2]);
    pXmlSierialize->xml_serialize("电压变比二次值(第4组)", "_UrSecondary", "V", "float", pSystemParas->m_fVSecondary[3]);
    pXmlSierialize->xml_serialize("电压变比二次值(第5组)", "_U5Secondary", "V", "float", pSystemParas->m_fVSecondary[4]);
    pXmlSierialize->xml_serialize("电压变比二次值(第6组)", "_U6Secondary", "V", "float", pSystemParas->m_fVSecondary[5]);
    pXmlSierialize->xml_serialize("电流变比一次值(第1组)", "_IaPrimary", "A", "float", pSystemParas->m_fIPrimary[0]);
    pXmlSierialize->xml_serialize("电流变比一次值(第2组)", "_IxPrimary", "A", "float", pSystemParas->m_fIPrimary[1]);
    pXmlSierialize->xml_serialize("电流变比一次值(第3组)", "_IuPrimary", "A", "float", pSystemParas->m_fIPrimary[2]);
    pXmlSierialize->xml_serialize("电流变比一次值(第4组)", "_IrPrimary", "A", "float", pSystemParas->m_fIPrimary[3]);
    pXmlSierialize->xml_serialize("电流变比一次值(第5组)", "_I5Primary", "A", "float", pSystemParas->m_fIPrimary[4]);
    pXmlSierialize->xml_serialize("电流变比一次值(第6组)", "_I6Primary", "A", "float", pSystemParas->m_fIPrimary[5]);
    pXmlSierialize->xml_serialize("电流变比二次值(第1组)", "_IaSecondary", "A", "float", pSystemParas->m_fISecondary[0]);
    pXmlSierialize->xml_serialize("电流变比二次值(第2组)", "_IxSecondary", "A", "float", pSystemParas->m_fISecondary[1]);
    pXmlSierialize->xml_serialize("电流变比二次值(第3组)", "_IuSecondary", "A", "float", pSystemParas->m_fISecondary[2]);
    pXmlSierialize->xml_serialize("电流变比二次值(第4组)", "_IrSecondary", "A", "float", pSystemParas->m_fISecondary[3]);
    pXmlSierialize->xml_serialize("电流变比二次值(第5组)", "_I5Secondary", "A", "float", pSystemParas->m_fISecondary[4]);
    pXmlSierialize->xml_serialize("电流变比二次值(第6组)", "_I6Secondary", "A", "float", pSystemParas->m_fISecondary[5]);
#else
	pXmlSierialize->xml_serialize("输出模拟量", "HasAnalog", " ", "number", pSystemParas->m_nHasAnalog);
	pXmlSierialize->xml_serialize("输出数字量", "HasDigital", " ", "number", pSystemParas->m_nHasDigital);
	pXmlSierialize->xml_serialize("输出弱信号", "HasWeek", " ", "number", pSystemParas->m_nHasWeek);
  pXmlSierialize->xml_serialize(/* "电压变比一次值(第1组)" */ g_sLangTxt_Native_VoltageRatioPrimary1.GetString(), "_UaPrimary", "kV", "float", pSystemParas->m_fVPrimary[0]);
  pXmlSierialize->xml_serialize(/* "电压变比一次值(第2组)" */ g_sLangTxt_Native_VoltageRatioPrimary2.GetString(), "_UxPrimary", "kV", "float", pSystemParas->m_fVPrimary[1]);
  pXmlSierialize->xml_serialize(/* "电压变比一次值(第3组)" */ g_sLangTxt_Native_VoltageRatioPrimary3.GetString(), "_UuPrimary", "kV", "float", pSystemParas->m_fVPrimary[2]);
  pXmlSierialize->xml_serialize(/* "电压变比一次值(第4组)" */ g_sLangTxt_Native_VoltageRatioPrimary4.GetString(), "_UrPrimary", "kV", "float", pSystemParas->m_fVPrimary[3]);
  pXmlSierialize->xml_serialize(/* "电压变比一次值(第5组)" */ g_sLangTxt_Native_VoltageRatioPrimary5.GetString(), "_U5Primary", "kV", "float", pSystemParas->m_fVPrimary[4]);
  pXmlSierialize->xml_serialize(/* "电压变比一次值(第6组)" */ g_sLangTxt_Native_VoltageRatioPrimary6.GetString(), "_U6Primary", "kV", "float", pSystemParas->m_fVPrimary[5]);
  pXmlSierialize->xml_serialize(/* "电压变比二次值(第1组)" */ g_sLangTxt_Native_VoltageRatioSecondary1.GetString(), "_UaSecondary", "V", "float", pSystemParas->m_fVSecondary[0]);
  pXmlSierialize->xml_serialize(/* "电压变比二次值(第2组)" */ g_sLangTxt_Native_VoltageRatioSecondary2.GetString(), "_UxSecondary", "V", "float", pSystemParas->m_fVSecondary[1]);
  pXmlSierialize->xml_serialize(/* "电压变比二次值(第3组)" */ g_sLangTxt_Native_VoltageRatioSecondary3.GetString(), "_UuSecondary", "V", "float", pSystemParas->m_fVSecondary[2]);
  pXmlSierialize->xml_serialize(/* "电压变比二次值(第4组)" */ g_sLangTxt_Native_VoltageRatioSecondary4.GetString(), "_UrSecondary", "V", "float", pSystemParas->m_fVSecondary[3]);
  pXmlSierialize->xml_serialize(/* "电压变比二次值(第5组)" */ g_sLangTxt_Native_VoltageRatioSecondary5.GetString(), "_U5Secondary", "V", "float", pSystemParas->m_fVSecondary[4]);
  pXmlSierialize->xml_serialize(/* "电压变比二次值(第6组)" */ g_sLangTxt_Native_VoltageRatioSecondary6.GetString(), "_U6Secondary", "V", "float", pSystemParas->m_fVSecondary[5]);
  pXmlSierialize->xml_serialize(/* "电流变比一次值(第1组)" */ g_sLangTxt_Native_CurrentRatioPrimary1.GetString(), "_IaPrimary", "A", "float", pSystemParas->m_fIPrimary[0]);
  pXmlSierialize->xml_serialize(/* "电流变比一次值(第2组)" */ g_sLangTxt_Native_CurrentRatioPrimary2.GetString(), "_IxPrimary", "A", "float", pSystemParas->m_fIPrimary[1]);
  pXmlSierialize->xml_serialize(/* "电流变比一次值(第3组)" */ g_sLangTxt_Native_CurrentRatioPrimary3.GetString(), "_IuPrimary", "A", "float", pSystemParas->m_fIPrimary[2]);
  pXmlSierialize->xml_serialize(/* "电流变比一次值(第4组)" */ g_sLangTxt_Native_CurrentRatioPrimary4.GetString(), "_IrPrimary", "A", "float", pSystemParas->m_fIPrimary[3]);
  pXmlSierialize->xml_serialize(/* "电流变比一次值(第5组)" */ g_sLangTxt_Native_CurrentRatioPrimary5.GetString(), "_I5Primary", "A", "float", pSystemParas->m_fIPrimary[4]);
  pXmlSierialize->xml_serialize(/* "电流变比一次值(第6组)" */ g_sLangTxt_Native_CurrentRatioPrimary6.GetString(), "_I6Primary", "A", "float", pSystemParas->m_fIPrimary[5]);
  pXmlSierialize->xml_serialize(/* "电流变比二次值(第1组)" */ g_sLangTxt_Native_CurrentRatioSecondary1.GetString(), "_IaSecondary", "A", "float", pSystemParas->m_fISecondary[0]);
  pXmlSierialize->xml_serialize(/* "电流变比二次值(第2组)" */ g_sLangTxt_Native_CurrentRatioSecondary2.GetString(), "_IxSecondary", "A", "float", pSystemParas->m_fISecondary[1]);
  pXmlSierialize->xml_serialize(/* "电流变比二次值(第3组)" */ g_sLangTxt_Native_CurrentRatioSecondary3.GetString(), "_IuSecondary", "A", "float", pSystemParas->m_fISecondary[2]);
  pXmlSierialize->xml_serialize(/* "电流变比二次值(第4组)" */ g_sLangTxt_Native_CurrentRatioSecondary4.GetString(), "_IrSecondary", "A", "float", pSystemParas->m_fISecondary[3]);
  pXmlSierialize->xml_serialize(/* "电流变比二次值(第5组)" */ g_sLangTxt_Native_CurrentRatioSecondary5.GetString(), "_I5Secondary", "A", "float", pSystemParas->m_fISecondary[4]);
  pXmlSierialize->xml_serialize(/* "电流变比二次值(第6组)" */ g_sLangTxt_Native_CurrentRatioSecondary6.GetString(), "_I6Secondary", "A", "float", pSystemParas->m_fISecondary[5]);
#endif
}

void stt_xml_serialize_ModulesGearSwitch(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize) //单独用于档位切换
{
    stt_xml_serialize_CurrModules(&pSystemParas->m_oGearSetCurModules, pXmlSierialize);
}

void stt_xml_serialize_PeripheralCtrl(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize) //单独用于外设切换
{
    stt_xml_serialize_Peripheral(&pSystemParas->m_oPeripheral, pXmlSierialize);
}

void stt_xml_serialize_SystemParas(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize) //单独用于系统参数设置
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("输出模拟量", "HasAnalog", " ", "number", pSystemParas->m_nHasAnalog);
    pXmlSierialize->xml_serialize("输出数字量", "HasDigital", " ", "number", pSystemParas->m_nHasDigital);
    pXmlSierialize->xml_serialize("输出弱信号", "HasWeek", " ", "number", pSystemParas->m_nHasWeek);
	pXmlSierialize->xml_serialize("参数设置(0-一次值 1-二次值)", "ParaMode", " ", "number", pSystemParas->m_nParaMode);
    pXmlSierialize->xml_serialize("报文输出格式", "PkgOutputMode", " ", "number", pSystemParas->m_nIecFormat);
    pXmlSierialize->xml_serialize("额定线电压值", "NormVol", "V", "float", pSystemParas->m_fVNom);
    pXmlSierialize->xml_serialize("额定电流值", "NormCur", "A", "float", pSystemParas->m_fINom);
    pXmlSierialize->xml_serialize("额定频率", "NormFre", "Hz", "float", pSystemParas->m_fFNom);
	pXmlSierialize->xml_serialize("额定零序电压","ZeroVol","V","float",pSystemParas->m_fU0_Std);
	pXmlSierialize->xml_serialize("额定零序电流","ZeroCur","A","float",pSystemParas->m_fI0_Std);
    pXmlSierialize->xml_serialize("防抖时间", "StabTime", "s", "float", pSystemParas->m_fStabTime);
    pXmlSierialize->xml_serialize("开始过载延时(s)", "OverLoadDelay", "s", "float", pSystemParas->m_fOverLoadDelay);
    pXmlSierialize->xml_serialize("1588同步机制", "Syn1588", " ", "number", pSystemParas->m_n588Syn);
    pXmlSierialize->xml_serialize("B码逻辑(0-正逻辑,1-负逻辑)", "BCodeMode", " ", "number", pSystemParas->m_nBCodeMode);
    pXmlSierialize->xml_serialize("光纤连接方式(0-双回,1-单回)", "LoopMode", " ", "number", pSystemParas->m_nLoopMode);
    pXmlSierialize->xml_serialize("开启秒同步", "SyncSecond", "", "BOOL", pSystemParas->m_bSyncSecond);
    pXmlSierialize->xml_serialize("检测测试端心跳", "CheckHeartOverTime", "", "BOOL", pSystemParas->m_bCheckHeartOverTime);
    pXmlSierialize->xml_serialize("使用模拟量采集", "UseAnalogMeas", " ", "number", pSystemParas->m_nUseAnalogMeas); //20220806 zhouhj 增加用于采集
    pXmlSierialize->xml_serialize("使用数字量采集", "UseDigitalMeas", " ", "number", pSystemParas->m_nUseDigitalMeas);
    pXmlSierialize->xml_serialize("使用小信号采集", "UseWeekMeas", " ", "number", pSystemParas->m_nUseWeekMeas);
    pXmlSierialize->xml_serialize("数字量采集报文类型", "IecFormatMeas", " ", "number", pSystemParas->m_nIecFormatMeas);
    pXmlSierialize->xml_serialize("B码接收逻辑(0-正逻辑,1-负逻辑)", "BCodeModeMeas", " ", "number", pSystemParas->m_nBCodeModeMeas);
    pXmlSierialize->xml_serialize("报告需要的扩展开入数量(0-自动关联开关量扩展模块)", "RprtUseBinExCnt", " ", "number", pSystemParas->m_nRprtUseBinExCnt);
    pXmlSierialize->xml_serialize("底层上报数据的时区", "TimeZone", " ", "long", pSystemParas->m_nTimeZone);
    pXmlSierialize->xml_serialize("GPS转B码时使用用户设置时区", "GtoB_UseUserTz", " ", "BOOL", pSystemParas->m_bGtoB_UseUserTz);
    pXmlSierialize->xml_serialize("机器散热风扇模式(0-静音,1-正常)", "WindSpeed", " ", "long", pSystemParas->m_nWindSpeed);
#else
  pXmlSierialize->xml_serialize(/* "输出模拟量" */ ""/*g_sLangTxt_Native_OutputAnalog.GetString()*/, "HasAnalog", " ", "number", pSystemParas->m_nHasAnalog);
  pXmlSierialize->xml_serialize(/* "输出数字量" */ ""/*g_sLangTxt_Native_OutputDigital.GetString()*/, "HasDigital", " ", "number", pSystemParas->m_nHasDigital);
  pXmlSierialize->xml_serialize(/* "输出弱信号" */ ""/*g_sLangTxt_Native_OutputWeakSig.GetString()*/, "HasWeek", " ", "number", pSystemParas->m_nHasWeek);
  pXmlSierialize->xml_serialize(/* "报文输出格式" */ ""/*g_sLangTxt_Native_MsgFormat.GetString()*/, "PkgOutputMode", " ", "number", pSystemParas->m_nIecFormat);
  pXmlSierialize->xml_serialize(/* "额定线电压值" */ ""/*g_sLangTxt_Native_RatedLineVolt.GetString()*/, "NormVol", "V", "float", pSystemParas->m_fVNom);
  pXmlSierialize->xml_serialize(/* "额定电流值" */ ""/*g_sLangTxt_Native_RatedCurrVal.GetString()*/, "NormCur", "A", "float", pSystemParas->m_fINom);
  pXmlSierialize->xml_serialize(/* "额定频率" */ ""/*g_sLangTxt_Report_Fnom.GetString()*/, "NormFre", "Hz", "float", pSystemParas->m_fFNom);
  pXmlSierialize->xml_serialize(/* "额定零序电压" */ ""/*g_sLangTxt_Native_RatedZeroVolt.GetString()*/, "ZeroVol", "V", "float", pSystemParas->m_fU0_Std);
  pXmlSierialize->xml_serialize(/* "额定零序电流" */ ""/*g_sLangTxt_Native_RatedZeroCurr.GetString()*/, "ZeroCur", "A", "float", pSystemParas->m_fI0_Std);
  pXmlSierialize->xml_serialize(/* "防抖时间" */ ""/*g_sLangTxt_Report_AntiShakeTime.GetString()*/, "StabTime", "s", "float", pSystemParas->m_fStabTime);
  pXmlSierialize->xml_serialize(/* "开始过载延时(s)" */ ""/*g_sLangTxt_Native_StartOverloadDelay.GetString()*/, "OverLoadDelay", "s", "float", pSystemParas->m_fOverLoadDelay);
  pXmlSierialize->xml_serialize(/* "1588同步机制" */ ""/*g_sLangTxt_Native_1588SyncMech.GetString()*/, "Syn1588", " ", "number", pSystemParas->m_n588Syn);
  pXmlSierialize->xml_serialize(/* "B码逻辑(0-正逻辑,1-负逻辑)" */"" /*g_sLangTxt_Native_BCodeLogic.GetString()*/, "BCodeMode", " ", "number", pSystemParas->m_nBCodeMode);
  pXmlSierialize->xml_serialize(/* "光纤连接方式(0-双回,1-单回)" */ ""/*g_sLangTxt_Native_FiberConn.GetString()*/, "LoopMode", " ", "number", pSystemParas->m_nLoopMode);
  pXmlSierialize->xml_serialize(/* "开启秒同步" */ ""/*g_sLangTxt_Manual_OpenSecSync.GetString()*/, "SyncSecond", "", "BOOL", pSystemParas->m_bSyncSecond);
  pXmlSierialize->xml_serialize(/* "检测测试端心跳" */ ""/*g_sLangTxt_Native_CheckTestEndHeartbeat.GetString()*/, "CheckHeartOverTime", "", "BOOL", pSystemParas->m_bCheckHeartOverTime);
  pXmlSierialize->xml_serialize(/* "使用模拟量采集" */ ""/*g_sLangTxt_Native_UseAnalogCapture.GetString()*/, "UseAnalogMeas", " ", "number", pSystemParas->m_nUseAnalogMeas);  // 20220806 zhouhj 增加用于采集
  pXmlSierialize->xml_serialize(/* "使用数字量采集" */ ""/*g_sLangTxt_Native_UseDigitalCapture.GetString()*/, "UseDigitalMeas", " ", "number", pSystemParas->m_nUseDigitalMeas);
  pXmlSierialize->xml_serialize(/* "使用小信号采集" */ ""/*g_sLangTxt_Native_UseSmallSignalCapture.GetString()*/, "UseWeekMeas", " ", "number", pSystemParas->m_nUseWeekMeas);
  pXmlSierialize->xml_serialize(/* "数字量采集报文类型" */ ""/*g_sLangTxt_Native_DigitalCaptureMsgType.GetString()*/, "IecFormatMeas", " ", "number", pSystemParas->m_nIecFormatMeas);
  pXmlSierialize->xml_serialize(/* "B码接收逻辑(0-正逻辑,1-负逻辑)" */ ""/*g_sLangTxt_Native_BCodeReceiveLogic.GetString()*/, "BCodeModeMeas", " ", "number", pSystemParas->m_nBCodeModeMeas);
  pXmlSierialize->xml_serialize(/* "报告需要的扩展开入数量(0-自动关联开关量扩展模块)" */ ""/*g_sLangTxt_Native_ReportExtInQty.GetString()*/, "RprtUseBinExCnt", " ", "number", pSystemParas->m_nRprtUseBinExCnt);
  pXmlSierialize->xml_serialize(/* "底层上报数据的时区" */ ""/*g_sLangTxt_Native_BaseReportTimeZone.GetString()*/, "TimeZone", " ", "long", pSystemParas->m_nTimeZone);
  pXmlSierialize->xml_serialize(/* "GPS转B码时使用用户设置时区" */ ""/*g_sLangTxt_Native_GPStoBCodeUserTZ.GetString()*/, "GtoB_UseUserTz", " ", "BOOL", pSystemParas->m_bGtoB_UseUserTz);
  pXmlSierialize->xml_serialize(/* "机器散热风扇模式(0-静音,1-正常)" */ ""/*g_sLangTxt_Native_MachineFanMode.GetString()*/, "WindSpeed", " ", "long", pSystemParas->m_nWindSpeed);
#endif
    CSttXmlSerializeBase *pErrorValuesSerialize = pXmlSierialize->xml_serialize(_T("ErrorValues"), _T("ErrorValues"), _T("ErrorValues"), stt_ParaGroupKey());

    if(pErrorValuesSerialize != NULL)
    {
        stt_xml_serialize_ErrorValues(pSystemParas, pErrorValuesSerialize);
    }

    //20220311 zhoulei PTU200L
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        pXmlSierialize->xml_serialize("", "PowerMode_Mode", "", "number", pSystemParas->m_oGearSetCurModules.m_oCurModuleGear[0].m_nIPowerMode);
        pXmlSierialize->xml_serialize("", "PowerMode_VoltSet", "", "number", pSystemParas->m_oGearSetCurModules.m_oCurModuleGear[0].m_fVoltSet);
    }
}


//#include"../../SttCmd/StttestCmd.h"
#include"../../SttCmd/SttTestCmd.h"
#include"../../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_SystemConfig()
{
    STT_SystemParas oSystemParas;
    oSystemParas.init();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oSystemParas, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("SystemParasDemo.xml");
    //    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
