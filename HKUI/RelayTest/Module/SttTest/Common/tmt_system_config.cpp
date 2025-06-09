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
// 	CString strTmp1 = _T("��"),strTmp2,strTmp3 = _T("�����źű��");
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
// 	pChildSerialize->xml_serialize(_T("���ź�PTһ��ֵ"),_T("PT_Primary_Weak"),"V","float",pSystemParas->m_fVPrimary_Weak[nGroupIndex]);
// 	pChildSerialize->xml_serialize(_T("���ź�PT����ֵ"),_T("PT_Secondary_Weak"),"V","float",pSystemParas->m_fVSecondary_Weak[nGroupIndex]);
// 	pChildSerialize->xml_serialize(_T("���ź�CTһ��ֵ"),_T("CT_Primary_Weak"),"A","float",pSystemParas->m_fIPrimary_Weak[nGroupIndex]);
// 	pChildSerialize->xml_serialize(_T("���ź�CT����ֵ"),_T("CT_Secondary_Weak"),"V","float",pSystemParas->m_fISecondary_Weak[nGroupIndex]);
// }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_CurrModule(tmt_GearSetCurModules *pGearSetCurModules, const int &nGroupIndex, CSttXmlSerializeBase *pXmlSierialize)
{
    CString strDesc = _T(""), strID;
//	CString strTmp1 = _T("��"),strTmp2,strTmp3 = _T("�����ģ��");
#ifdef NOT_USE_XLANGUAGE
    strDesc += _T("��");
    strDesc.AppendFormat(_T("%d"), nGroupIndex + 1);
    strDesc += _T("�����ģ��");
#else
  strDesc += /* _T("��") */ g_sLangTxt_Native_Number;
  strDesc.AppendFormat(_T("%d"), nGroupIndex + 1);
  strDesc += /* _T("�����ģ��") */ g_sLangTxt_Native_GroupCurrMod;
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
    pChildSerialize->xml_serialize(_T("����ģ��λ��"), _T("ModulePos"), "", "number", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nModulePos);
    pChildSerialize->xml_serialize(_T("����ģ�鵵λֵ"), _T("CurModuleGear"), "", "number", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nIPowerMode);
    pChildSerialize->xml_serialize(_T("����ͨ�����˿ڵ�ѹ"), _T("MaxPortVol"), "", "float", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_fVoltSet);
    pChildSerialize->xml_serialize(_T("�ϲ���������"), _T("MergeCurTerminal"), "", "float", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nMergeCurTerminal);
    pChildSerialize->xml_serialize(_T("���������˿�"), _T("LargeCurOutTerm"), "", "number", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nLargeCurOutTerm);
#else
  pChildSerialize->xml_serialize(/* _T("����ģ��λ��") */ g_sLangTxt_Native_CurrModPos.GetString(), _T("ModulePos"), "", "number", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nModulePos);
  pChildSerialize->xml_serialize(/* _T("����ģ�鵵λֵ") */ g_sLangTxt_Native_CurrModGearVal.GetString(), _T("CurModuleGear"), "", "number", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nIPowerMode);
  pChildSerialize->xml_serialize(/* _T("����ͨ�����˿ڵ�ѹ") */ g_sLangTxt_Native_CurrChanMaxVolt.GetString(), _T("MaxPortVol"), "", "float", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_fVoltSet);
  pChildSerialize->xml_serialize(/* _T("�ϲ���������") */ g_sLangTxt_Native_MergeCurrTerm.GetString(), _T("MergeCurTerminal"), "", "float", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nMergeCurTerminal);
  pChildSerialize->xml_serialize(/* _T("���������˿�") */ g_sLangTxt_Highcurrent.GetString(), _T("LargeCurOutTerm"), "", "number", pGearSetCurModules->m_oCurModuleGear[nGroupIndex].m_nLargeCurOutTerm);
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
    pXmlSierialize->xml_serialize("����ģ������", "CurrModuleNum", "", "number", pGearSetCurModules->m_nCurModuleNum);
#else
  pXmlSierialize->xml_serialize(/* _T("����ģ������") */ g_sLangTxt_Native_CurrModCount.GetString(), "CurrModuleNum", "", "number", pGearSetCurModules->m_nCurModuleNum);
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
    pPeripheralXmlSierialize->xml_serialize("����", "Ble", "", "long", pPeripheral->m_bBle);
    pPeripheralXmlSierialize->xml_serialize("��������", "NetWifi", "", "long", pPeripheral->m_bNetWifi);
    pPeripheralXmlSierialize->xml_serialize("��������", "NetRj45", "", "long", pPeripheral->m_bNetRj45);
    pPeripheralXmlSierialize->xml_serialize("Lcd����ʱ��", "LcdTimes", "", "long", pPeripheral->m_nLcdTimes);
	pPeripheralXmlSierialize->xml_serialize("Lcd��󱳹�����", "LcdLight", "", "long", pPeripheral->m_nLcdLight);
#else
  pPeripheralXmlSierialize->xml_serialize("4G", "4G", "", "long", pPeripheral->m_b4G);
  pPeripheralXmlSierialize->xml_serialize(/* "����" */ g_sLangTxt_State_Bluetooth.GetString(), "Ble", "", "long", pPeripheral->m_bBle);
  pPeripheralXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_WirelessNet.GetString(), "NetWifi", "", "long", pPeripheral->m_bNetWifi);
  pPeripheralXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_WiredNet.GetString(), "NetRj45", "", "long", pPeripheral->m_bNetRj45);
  pPeripheralXmlSierialize->xml_serialize(/* "Lcd����ʱ��" */ g_sLangTxt_Native_LcdBacklightTime.GetString(), "LcdTimes", "", "long", pPeripheral->m_nLcdTimes);
  pPeripheralXmlSierialize->xml_serialize(/* "Lcd��󱳹�����" */ g_sLangTxt_Native_TouchSensitivity.GetString(), "LcdLight", "", "long", pPeripheral->m_nLcdLight);
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_ErrorValues(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize(_T("��������ֵ�������(A)"), _T("CurAbsError"), "", "number", pSystemParas->m_fCurValue_AbsError);
    pXmlSierialize->xml_serialize(_T("��������ֵ������(%)"), _T("CurRelError"), "", "number", pSystemParas->m_fCurValue_RelError);
    pXmlSierialize->xml_serialize(_T("��ѹ����ֵ�������(V)"), _T("VolAbsError"), "", "number", pSystemParas->m_fVolValue_AbsError);
    pXmlSierialize->xml_serialize(_T("��ѹ����ֵ������(%)"), _T("VolRelError"), "", "number", pSystemParas->m_fVolValue_RelError);
    pXmlSierialize->xml_serialize(_T("�迹����ֵ�������(��)"), _T("ImpAbsError"), "", "number", pSystemParas->m_fImpValue_AbsError);
    pXmlSierialize->xml_serialize(_T("�迹����ֵ������(%)"), _T("ImpRelError"), "", "number", pSystemParas->m_fImpValue_RelError);
    pXmlSierialize->xml_serialize(_T("����ʱ��������(s)"), _T("TimeAbsError"), "", "number", pSystemParas->m_fTimeValue_AbsError);
    pXmlSierialize->xml_serialize(_T("����ʱ��������(%)"), _T("TimeRelError"), "", "number", pSystemParas->m_fTimeValue_RelError);
    pXmlSierialize->xml_serialize(_T("��λ���ֵ(��)"), _T("AngError"), "", "number", pSystemParas->m_fAngValue_AbsError);
    pXmlSierialize->xml_serialize(_T("Ƶ�����ֵ(Hz)"), _T("FreError"), "", "number", pSystemParas->m_fFreValue_AbsError);
    pXmlSierialize->xml_serialize(_T("��ѹ�������ֵ(V/s)"), _T("dvdtError"), "", "number", pSystemParas->m_fdvdtValue_AbsError);
    pXmlSierialize->xml_serialize(_T("Ƶ�ʻ������ֵ(Hz/s)"), _T("dfdtError"), "", "number", pSystemParas->m_fdfdtValue_AbsError);
    pXmlSierialize->xml_serialize(_T("������ƶ�ϵ���������"), _T("DiffRateCoefAbsError"), "", "number", pSystemParas->m_fDiffRateCoef_AbsError);
    pXmlSierialize->xml_serialize(_T("������ƶ�ϵ��������(%)"), _T("DiffRateCoefRelError"), "", "number", pSystemParas->m_fDiffRateCoef_RelError);
    pXmlSierialize->xml_serialize(_T("�г���ƶ�ϵ���������"), _T("DiffHarmCoefAbsError"), "", "number", pSystemParas->m_fDiffHarmCoef_AbsError);
    pXmlSierialize->xml_serialize(_T("�г���ƶ�ϵ��������(%)"), _T("DiffHarmCoefRelError"), "", "number", pSystemParas->m_fDiffHarmCoef_RelError);
#else
  pXmlSierialize->xml_serialize(/* _T("��������ֵ�������(A)") */ g_sLangTxt_Native_CurrentActionError.GetString(), _T("CurAbsError"), "", "number", pSystemParas->m_fCurValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("��������ֵ������(%)") */ g_sLangTxt_Native_CurrentActionRelError.GetString(), _T("CurRelError"), "", "number", pSystemParas->m_fCurValue_RelError);
  pXmlSierialize->xml_serialize(/* _T("��ѹ����ֵ�������(V)") */ g_sLangTxt_Native_VoltageActionError.GetString(), _T("VolAbsError"), "", "number", pSystemParas->m_fVolValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("��ѹ����ֵ������(%)") */ g_sLangTxt_Native_VoltageActionRelError.GetString(), _T("VolRelError"), "", "number", pSystemParas->m_fVolValue_RelError);
  pXmlSierialize->xml_serialize(/* _T("�迹����ֵ�������(��)") */ g_sLangTxt_Native_ImpedanceActionError.GetString(), _T("ImpAbsError"), "", "number", pSystemParas->m_fImpValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("�迹����ֵ������(%)") */ g_sLangTxt_Native_ImpedanceActionRelError.GetString(), _T("ImpRelError"), "", "number", pSystemParas->m_fImpValue_RelError);
  pXmlSierialize->xml_serialize(/* _T("����ʱ��������(s)") */ g_sLangTxt_Native_ActionTimeAbsError.GetString(), _T("TimeAbsError"), "", "number", pSystemParas->m_fTimeValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("����ʱ��������(%)") */ g_sLangTxt_Native_ActionTimeRelError.GetString(), _T("TimeRelError"), "", "number", pSystemParas->m_fTimeValue_RelError);
  pXmlSierialize->xml_serialize(/* _T("��λ���ֵ(��)") */ g_sLangTxt_Native_PhaseErrorValue.GetString(), _T("AngError"), "", "number", pSystemParas->m_fAngValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("Ƶ�����ֵ(Hz)") */ g_sLangTxt_Native_FreqErrorValue.GetString(), _T("FreError"), "", "number", pSystemParas->m_fFreValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("��ѹ�������ֵ(V/s)") */ g_sLangTxt_Native_VoltSlipErrorValue.GetString(), _T("dvdtError"), "", "number", pSystemParas->m_fdvdtValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("Ƶ�ʻ������ֵ(Hz/s)") */ g_sLangTxt_Native_FreqSlipErrorValue.GetString(), _T("dfdtError"), "", "number", pSystemParas->m_fdfdtValue_AbsError);
  pXmlSierialize->xml_serialize(/* _T("������ƶ�ϵ���������") */ g_sLangTxt_Native_DiffRatioBrakeAbsError.GetString(), _T("DiffRateCoefAbsError"), "", "number", pSystemParas->m_fDiffRateCoef_AbsError);
  pXmlSierialize->xml_serialize(/* _T("������ƶ�ϵ��������(%)") */ g_sLangTxt_Native_DiffRatioBrakeRelError.GetString(), _T("DiffRateCoefRelError"), "", "number", pSystemParas->m_fDiffRateCoef_RelError);
  pXmlSierialize->xml_serialize(/* _T("�г���ƶ�ϵ���������") */ g_sLangTxt_Native_DiffHarmonicBrakeAbsError.GetString(), _T("DiffHarmCoefAbsError"), "", "number", pSystemParas->m_fDiffHarmCoef_AbsError);
  pXmlSierialize->xml_serialize(/* _T("�г���ƶ�ϵ��������(%)") */ g_sLangTxt_Native_DiffHarmonicBrakeRelError.GetString(), _T("DiffHarmCoefRelError"), "", "number", pSystemParas->m_fDiffHarmCoef_RelError);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_SystemParas(pSystemParas, pXmlSierialize);

#ifdef _STT_NOT_IN_TEST_SERVER_
	stt_xml_serialize_AuxDC(pSystemParas, pXmlSierialize);//20240226 �ײ�ر�ϵͳ�����޸ĸ���ֱ�����
	stt_xml_serialize_ModulesGearSwitch(pSystemParas, pXmlSierialize);//20240513 Ӳ����Ҫ��,�ײ�ر�ϵͳ�����޸ĵ����������
#endif

    stt_xml_serialize_PeripheralCtrl(pSystemParas, pXmlSierialize);
}

void stt_xml_serialize_AuxDC(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize) //zhouhj 20211016 �������ڸ���ֱ������
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("����ֱ����ѹֵ", "AuxVolDC", "s", "float", pSystemParas->m_fAuxDC_Vol);
    pXmlSierialize->xml_serialize("����ֱ������ֵ", "AuxCurDC", "s", "float", pSystemParas->m_fAuxDC_Cur);
#else
  pXmlSierialize->xml_serialize(/* "����ֱ����ѹֵ" */ g_sLangTxt_Native_AuxDcVoltageValue.GetString(), "AuxVolDC", "s", "float", pSystemParas->m_fAuxDC_Vol);
  pXmlSierialize->xml_serialize(/* "����ֱ������ֵ" */ g_sLangTxt_Native_AuxDcCurrentValue.GetString(), "AuxCurDC", "s", "float", pSystemParas->m_fAuxDC_Cur);
#endif
}

void stt_xml_serialize_AppConfig(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize) //zhouhj 20221207 �����������ñ��
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("���ģ����", "HasAnalog", " ", "number", pSystemParas->m_nHasAnalog);
	pXmlSierialize->xml_serialize("���������", "HasDigital", " ", "number", pSystemParas->m_nHasDigital);
	pXmlSierialize->xml_serialize("������ź�", "HasWeek", " ", "number", pSystemParas->m_nHasWeek);
    pXmlSierialize->xml_serialize("��ѹ���һ��ֵ(��1��)", "_UaPrimary", "kV", "float", pSystemParas->m_fVPrimary[0]);
    pXmlSierialize->xml_serialize("��ѹ���һ��ֵ(��2��)", "_UxPrimary", "kV", "float", pSystemParas->m_fVPrimary[1]);
    pXmlSierialize->xml_serialize("��ѹ���һ��ֵ(��3��)", "_UuPrimary", "kV", "float", pSystemParas->m_fVPrimary[2]);
    pXmlSierialize->xml_serialize("��ѹ���һ��ֵ(��4��)", "_UrPrimary", "kV", "float", pSystemParas->m_fVPrimary[3]);
    pXmlSierialize->xml_serialize("��ѹ���һ��ֵ(��5��)", "_U5Primary", "kV", "float", pSystemParas->m_fVPrimary[4]);
    pXmlSierialize->xml_serialize("��ѹ���һ��ֵ(��6��)", "_U6Primary", "kV", "float", pSystemParas->m_fVPrimary[5]);
    pXmlSierialize->xml_serialize("��ѹ��ȶ���ֵ(��1��)", "_UaSecondary", "V", "float", pSystemParas->m_fVSecondary[0]);
    pXmlSierialize->xml_serialize("��ѹ��ȶ���ֵ(��2��)", "_UxSecondary", "V", "float", pSystemParas->m_fVSecondary[1]);
    pXmlSierialize->xml_serialize("��ѹ��ȶ���ֵ(��3��)", "_UuSecondary", "V", "float", pSystemParas->m_fVSecondary[2]);
    pXmlSierialize->xml_serialize("��ѹ��ȶ���ֵ(��4��)", "_UrSecondary", "V", "float", pSystemParas->m_fVSecondary[3]);
    pXmlSierialize->xml_serialize("��ѹ��ȶ���ֵ(��5��)", "_U5Secondary", "V", "float", pSystemParas->m_fVSecondary[4]);
    pXmlSierialize->xml_serialize("��ѹ��ȶ���ֵ(��6��)", "_U6Secondary", "V", "float", pSystemParas->m_fVSecondary[5]);
    pXmlSierialize->xml_serialize("�������һ��ֵ(��1��)", "_IaPrimary", "A", "float", pSystemParas->m_fIPrimary[0]);
    pXmlSierialize->xml_serialize("�������һ��ֵ(��2��)", "_IxPrimary", "A", "float", pSystemParas->m_fIPrimary[1]);
    pXmlSierialize->xml_serialize("�������һ��ֵ(��3��)", "_IuPrimary", "A", "float", pSystemParas->m_fIPrimary[2]);
    pXmlSierialize->xml_serialize("�������һ��ֵ(��4��)", "_IrPrimary", "A", "float", pSystemParas->m_fIPrimary[3]);
    pXmlSierialize->xml_serialize("�������һ��ֵ(��5��)", "_I5Primary", "A", "float", pSystemParas->m_fIPrimary[4]);
    pXmlSierialize->xml_serialize("�������һ��ֵ(��6��)", "_I6Primary", "A", "float", pSystemParas->m_fIPrimary[5]);
    pXmlSierialize->xml_serialize("������ȶ���ֵ(��1��)", "_IaSecondary", "A", "float", pSystemParas->m_fISecondary[0]);
    pXmlSierialize->xml_serialize("������ȶ���ֵ(��2��)", "_IxSecondary", "A", "float", pSystemParas->m_fISecondary[1]);
    pXmlSierialize->xml_serialize("������ȶ���ֵ(��3��)", "_IuSecondary", "A", "float", pSystemParas->m_fISecondary[2]);
    pXmlSierialize->xml_serialize("������ȶ���ֵ(��4��)", "_IrSecondary", "A", "float", pSystemParas->m_fISecondary[3]);
    pXmlSierialize->xml_serialize("������ȶ���ֵ(��5��)", "_I5Secondary", "A", "float", pSystemParas->m_fISecondary[4]);
    pXmlSierialize->xml_serialize("������ȶ���ֵ(��6��)", "_I6Secondary", "A", "float", pSystemParas->m_fISecondary[5]);
#else
	pXmlSierialize->xml_serialize("���ģ����", "HasAnalog", " ", "number", pSystemParas->m_nHasAnalog);
	pXmlSierialize->xml_serialize("���������", "HasDigital", " ", "number", pSystemParas->m_nHasDigital);
	pXmlSierialize->xml_serialize("������ź�", "HasWeek", " ", "number", pSystemParas->m_nHasWeek);
  pXmlSierialize->xml_serialize(/* "��ѹ���һ��ֵ(��1��)" */ g_sLangTxt_Native_VoltageRatioPrimary1.GetString(), "_UaPrimary", "kV", "float", pSystemParas->m_fVPrimary[0]);
  pXmlSierialize->xml_serialize(/* "��ѹ���һ��ֵ(��2��)" */ g_sLangTxt_Native_VoltageRatioPrimary2.GetString(), "_UxPrimary", "kV", "float", pSystemParas->m_fVPrimary[1]);
  pXmlSierialize->xml_serialize(/* "��ѹ���һ��ֵ(��3��)" */ g_sLangTxt_Native_VoltageRatioPrimary3.GetString(), "_UuPrimary", "kV", "float", pSystemParas->m_fVPrimary[2]);
  pXmlSierialize->xml_serialize(/* "��ѹ���һ��ֵ(��4��)" */ g_sLangTxt_Native_VoltageRatioPrimary4.GetString(), "_UrPrimary", "kV", "float", pSystemParas->m_fVPrimary[3]);
  pXmlSierialize->xml_serialize(/* "��ѹ���һ��ֵ(��5��)" */ g_sLangTxt_Native_VoltageRatioPrimary5.GetString(), "_U5Primary", "kV", "float", pSystemParas->m_fVPrimary[4]);
  pXmlSierialize->xml_serialize(/* "��ѹ���һ��ֵ(��6��)" */ g_sLangTxt_Native_VoltageRatioPrimary6.GetString(), "_U6Primary", "kV", "float", pSystemParas->m_fVPrimary[5]);
  pXmlSierialize->xml_serialize(/* "��ѹ��ȶ���ֵ(��1��)" */ g_sLangTxt_Native_VoltageRatioSecondary1.GetString(), "_UaSecondary", "V", "float", pSystemParas->m_fVSecondary[0]);
  pXmlSierialize->xml_serialize(/* "��ѹ��ȶ���ֵ(��2��)" */ g_sLangTxt_Native_VoltageRatioSecondary2.GetString(), "_UxSecondary", "V", "float", pSystemParas->m_fVSecondary[1]);
  pXmlSierialize->xml_serialize(/* "��ѹ��ȶ���ֵ(��3��)" */ g_sLangTxt_Native_VoltageRatioSecondary3.GetString(), "_UuSecondary", "V", "float", pSystemParas->m_fVSecondary[2]);
  pXmlSierialize->xml_serialize(/* "��ѹ��ȶ���ֵ(��4��)" */ g_sLangTxt_Native_VoltageRatioSecondary4.GetString(), "_UrSecondary", "V", "float", pSystemParas->m_fVSecondary[3]);
  pXmlSierialize->xml_serialize(/* "��ѹ��ȶ���ֵ(��5��)" */ g_sLangTxt_Native_VoltageRatioSecondary5.GetString(), "_U5Secondary", "V", "float", pSystemParas->m_fVSecondary[4]);
  pXmlSierialize->xml_serialize(/* "��ѹ��ȶ���ֵ(��6��)" */ g_sLangTxt_Native_VoltageRatioSecondary6.GetString(), "_U6Secondary", "V", "float", pSystemParas->m_fVSecondary[5]);
  pXmlSierialize->xml_serialize(/* "�������һ��ֵ(��1��)" */ g_sLangTxt_Native_CurrentRatioPrimary1.GetString(), "_IaPrimary", "A", "float", pSystemParas->m_fIPrimary[0]);
  pXmlSierialize->xml_serialize(/* "�������һ��ֵ(��2��)" */ g_sLangTxt_Native_CurrentRatioPrimary2.GetString(), "_IxPrimary", "A", "float", pSystemParas->m_fIPrimary[1]);
  pXmlSierialize->xml_serialize(/* "�������һ��ֵ(��3��)" */ g_sLangTxt_Native_CurrentRatioPrimary3.GetString(), "_IuPrimary", "A", "float", pSystemParas->m_fIPrimary[2]);
  pXmlSierialize->xml_serialize(/* "�������һ��ֵ(��4��)" */ g_sLangTxt_Native_CurrentRatioPrimary4.GetString(), "_IrPrimary", "A", "float", pSystemParas->m_fIPrimary[3]);
  pXmlSierialize->xml_serialize(/* "�������һ��ֵ(��5��)" */ g_sLangTxt_Native_CurrentRatioPrimary5.GetString(), "_I5Primary", "A", "float", pSystemParas->m_fIPrimary[4]);
  pXmlSierialize->xml_serialize(/* "�������һ��ֵ(��6��)" */ g_sLangTxt_Native_CurrentRatioPrimary6.GetString(), "_I6Primary", "A", "float", pSystemParas->m_fIPrimary[5]);
  pXmlSierialize->xml_serialize(/* "������ȶ���ֵ(��1��)" */ g_sLangTxt_Native_CurrentRatioSecondary1.GetString(), "_IaSecondary", "A", "float", pSystemParas->m_fISecondary[0]);
  pXmlSierialize->xml_serialize(/* "������ȶ���ֵ(��2��)" */ g_sLangTxt_Native_CurrentRatioSecondary2.GetString(), "_IxSecondary", "A", "float", pSystemParas->m_fISecondary[1]);
  pXmlSierialize->xml_serialize(/* "������ȶ���ֵ(��3��)" */ g_sLangTxt_Native_CurrentRatioSecondary3.GetString(), "_IuSecondary", "A", "float", pSystemParas->m_fISecondary[2]);
  pXmlSierialize->xml_serialize(/* "������ȶ���ֵ(��4��)" */ g_sLangTxt_Native_CurrentRatioSecondary4.GetString(), "_IrSecondary", "A", "float", pSystemParas->m_fISecondary[3]);
  pXmlSierialize->xml_serialize(/* "������ȶ���ֵ(��5��)" */ g_sLangTxt_Native_CurrentRatioSecondary5.GetString(), "_I5Secondary", "A", "float", pSystemParas->m_fISecondary[4]);
  pXmlSierialize->xml_serialize(/* "������ȶ���ֵ(��6��)" */ g_sLangTxt_Native_CurrentRatioSecondary6.GetString(), "_I6Secondary", "A", "float", pSystemParas->m_fISecondary[5]);
#endif
}

void stt_xml_serialize_ModulesGearSwitch(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize) //�������ڵ�λ�л�
{
    stt_xml_serialize_CurrModules(&pSystemParas->m_oGearSetCurModules, pXmlSierialize);
}

void stt_xml_serialize_PeripheralCtrl(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize) //�������������л�
{
    stt_xml_serialize_Peripheral(&pSystemParas->m_oPeripheral, pXmlSierialize);
}

void stt_xml_serialize_SystemParas(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize) //��������ϵͳ��������
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("���ģ����", "HasAnalog", " ", "number", pSystemParas->m_nHasAnalog);
    pXmlSierialize->xml_serialize("���������", "HasDigital", " ", "number", pSystemParas->m_nHasDigital);
    pXmlSierialize->xml_serialize("������ź�", "HasWeek", " ", "number", pSystemParas->m_nHasWeek);
	pXmlSierialize->xml_serialize("��������(0-һ��ֵ 1-����ֵ)", "ParaMode", " ", "number", pSystemParas->m_nParaMode);
    pXmlSierialize->xml_serialize("���������ʽ", "PkgOutputMode", " ", "number", pSystemParas->m_nIecFormat);
    pXmlSierialize->xml_serialize("��ߵ�ѹֵ", "NormVol", "V", "float", pSystemParas->m_fVNom);
    pXmlSierialize->xml_serialize("�����ֵ", "NormCur", "A", "float", pSystemParas->m_fINom);
    pXmlSierialize->xml_serialize("�Ƶ��", "NormFre", "Hz", "float", pSystemParas->m_fFNom);
	pXmlSierialize->xml_serialize("������ѹ","ZeroVol","V","float",pSystemParas->m_fU0_Std);
	pXmlSierialize->xml_serialize("��������","ZeroCur","A","float",pSystemParas->m_fI0_Std);
    pXmlSierialize->xml_serialize("����ʱ��", "StabTime", "s", "float", pSystemParas->m_fStabTime);
    pXmlSierialize->xml_serialize("��ʼ������ʱ(s)", "OverLoadDelay", "s", "float", pSystemParas->m_fOverLoadDelay);
    pXmlSierialize->xml_serialize("1588ͬ������", "Syn1588", " ", "number", pSystemParas->m_n588Syn);
    pXmlSierialize->xml_serialize("B���߼�(0-���߼�,1-���߼�)", "BCodeMode", " ", "number", pSystemParas->m_nBCodeMode);
    pXmlSierialize->xml_serialize("�������ӷ�ʽ(0-˫��,1-����)", "LoopMode", " ", "number", pSystemParas->m_nLoopMode);
    pXmlSierialize->xml_serialize("������ͬ��", "SyncSecond", "", "BOOL", pSystemParas->m_bSyncSecond);
    pXmlSierialize->xml_serialize("�����Զ�����", "CheckHeartOverTime", "", "BOOL", pSystemParas->m_bCheckHeartOverTime);
    pXmlSierialize->xml_serialize("ʹ��ģ�����ɼ�", "UseAnalogMeas", " ", "number", pSystemParas->m_nUseAnalogMeas); //20220806 zhouhj �������ڲɼ�
    pXmlSierialize->xml_serialize("ʹ���������ɼ�", "UseDigitalMeas", " ", "number", pSystemParas->m_nUseDigitalMeas);
    pXmlSierialize->xml_serialize("ʹ��С�źŲɼ�", "UseWeekMeas", " ", "number", pSystemParas->m_nUseWeekMeas);
    pXmlSierialize->xml_serialize("�������ɼ���������", "IecFormatMeas", " ", "number", pSystemParas->m_nIecFormatMeas);
    pXmlSierialize->xml_serialize("B������߼�(0-���߼�,1-���߼�)", "BCodeModeMeas", " ", "number", pSystemParas->m_nBCodeModeMeas);
    pXmlSierialize->xml_serialize("������Ҫ����չ��������(0-�Զ�������������չģ��)", "RprtUseBinExCnt", " ", "number", pSystemParas->m_nRprtUseBinExCnt);
    pXmlSierialize->xml_serialize("�ײ��ϱ����ݵ�ʱ��", "TimeZone", " ", "long", pSystemParas->m_nTimeZone);
    pXmlSierialize->xml_serialize("GPSתB��ʱʹ���û�����ʱ��", "GtoB_UseUserTz", " ", "BOOL", pSystemParas->m_bGtoB_UseUserTz);
    pXmlSierialize->xml_serialize("����ɢ�ȷ���ģʽ(0-����,1-����)", "WindSpeed", " ", "long", pSystemParas->m_nWindSpeed);
#else
  pXmlSierialize->xml_serialize(/* "���ģ����" */ ""/*g_sLangTxt_Native_OutputAnalog.GetString()*/, "HasAnalog", " ", "number", pSystemParas->m_nHasAnalog);
  pXmlSierialize->xml_serialize(/* "���������" */ ""/*g_sLangTxt_Native_OutputDigital.GetString()*/, "HasDigital", " ", "number", pSystemParas->m_nHasDigital);
  pXmlSierialize->xml_serialize(/* "������ź�" */ ""/*g_sLangTxt_Native_OutputWeakSig.GetString()*/, "HasWeek", " ", "number", pSystemParas->m_nHasWeek);
  pXmlSierialize->xml_serialize(/* "���������ʽ" */ ""/*g_sLangTxt_Native_MsgFormat.GetString()*/, "PkgOutputMode", " ", "number", pSystemParas->m_nIecFormat);
  pXmlSierialize->xml_serialize(/* "��ߵ�ѹֵ" */ ""/*g_sLangTxt_Native_RatedLineVolt.GetString()*/, "NormVol", "V", "float", pSystemParas->m_fVNom);
  pXmlSierialize->xml_serialize(/* "�����ֵ" */ ""/*g_sLangTxt_Native_RatedCurrVal.GetString()*/, "NormCur", "A", "float", pSystemParas->m_fINom);
  pXmlSierialize->xml_serialize(/* "�Ƶ��" */ ""/*g_sLangTxt_Report_Fnom.GetString()*/, "NormFre", "Hz", "float", pSystemParas->m_fFNom);
  pXmlSierialize->xml_serialize(/* "������ѹ" */ ""/*g_sLangTxt_Native_RatedZeroVolt.GetString()*/, "ZeroVol", "V", "float", pSystemParas->m_fU0_Std);
  pXmlSierialize->xml_serialize(/* "��������" */ ""/*g_sLangTxt_Native_RatedZeroCurr.GetString()*/, "ZeroCur", "A", "float", pSystemParas->m_fI0_Std);
  pXmlSierialize->xml_serialize(/* "����ʱ��" */ ""/*g_sLangTxt_Report_AntiShakeTime.GetString()*/, "StabTime", "s", "float", pSystemParas->m_fStabTime);
  pXmlSierialize->xml_serialize(/* "��ʼ������ʱ(s)" */ ""/*g_sLangTxt_Native_StartOverloadDelay.GetString()*/, "OverLoadDelay", "s", "float", pSystemParas->m_fOverLoadDelay);
  pXmlSierialize->xml_serialize(/* "1588ͬ������" */ ""/*g_sLangTxt_Native_1588SyncMech.GetString()*/, "Syn1588", " ", "number", pSystemParas->m_n588Syn);
  pXmlSierialize->xml_serialize(/* "B���߼�(0-���߼�,1-���߼�)" */"" /*g_sLangTxt_Native_BCodeLogic.GetString()*/, "BCodeMode", " ", "number", pSystemParas->m_nBCodeMode);
  pXmlSierialize->xml_serialize(/* "�������ӷ�ʽ(0-˫��,1-����)" */ ""/*g_sLangTxt_Native_FiberConn.GetString()*/, "LoopMode", " ", "number", pSystemParas->m_nLoopMode);
  pXmlSierialize->xml_serialize(/* "������ͬ��" */ ""/*g_sLangTxt_Manual_OpenSecSync.GetString()*/, "SyncSecond", "", "BOOL", pSystemParas->m_bSyncSecond);
  pXmlSierialize->xml_serialize(/* "�����Զ�����" */ ""/*g_sLangTxt_Native_CheckTestEndHeartbeat.GetString()*/, "CheckHeartOverTime", "", "BOOL", pSystemParas->m_bCheckHeartOverTime);
  pXmlSierialize->xml_serialize(/* "ʹ��ģ�����ɼ�" */ ""/*g_sLangTxt_Native_UseAnalogCapture.GetString()*/, "UseAnalogMeas", " ", "number", pSystemParas->m_nUseAnalogMeas);  // 20220806 zhouhj �������ڲɼ�
  pXmlSierialize->xml_serialize(/* "ʹ���������ɼ�" */ ""/*g_sLangTxt_Native_UseDigitalCapture.GetString()*/, "UseDigitalMeas", " ", "number", pSystemParas->m_nUseDigitalMeas);
  pXmlSierialize->xml_serialize(/* "ʹ��С�źŲɼ�" */ ""/*g_sLangTxt_Native_UseSmallSignalCapture.GetString()*/, "UseWeekMeas", " ", "number", pSystemParas->m_nUseWeekMeas);
  pXmlSierialize->xml_serialize(/* "�������ɼ���������" */ ""/*g_sLangTxt_Native_DigitalCaptureMsgType.GetString()*/, "IecFormatMeas", " ", "number", pSystemParas->m_nIecFormatMeas);
  pXmlSierialize->xml_serialize(/* "B������߼�(0-���߼�,1-���߼�)" */ ""/*g_sLangTxt_Native_BCodeReceiveLogic.GetString()*/, "BCodeModeMeas", " ", "number", pSystemParas->m_nBCodeModeMeas);
  pXmlSierialize->xml_serialize(/* "������Ҫ����չ��������(0-�Զ�������������չģ��)" */ ""/*g_sLangTxt_Native_ReportExtInQty.GetString()*/, "RprtUseBinExCnt", " ", "number", pSystemParas->m_nRprtUseBinExCnt);
  pXmlSierialize->xml_serialize(/* "�ײ��ϱ����ݵ�ʱ��" */ ""/*g_sLangTxt_Native_BaseReportTimeZone.GetString()*/, "TimeZone", " ", "long", pSystemParas->m_nTimeZone);
  pXmlSierialize->xml_serialize(/* "GPSתB��ʱʹ���û�����ʱ��" */ ""/*g_sLangTxt_Native_GPStoBCodeUserTZ.GetString()*/, "GtoB_UseUserTz", " ", "BOOL", pSystemParas->m_bGtoB_UseUserTz);
  pXmlSierialize->xml_serialize(/* "����ɢ�ȷ���ģʽ(0-����,1-����)" */ ""/*g_sLangTxt_Native_MachineFanMode.GetString()*/, "WindSpeed", " ", "long", pSystemParas->m_nWindSpeed);
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
