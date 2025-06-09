#include "stdafx.h"
#include "tmt_linevolt_gradient_test.h"
#include"../../../SttCmd/SttTestCmd.h"
#include"../tmt_gradient_test.h"
#include"../../../../../Module/API/GlobalConfigApi.h"

#ifndef _STT_NOT_IN_TEST_SERVER_
#include "../SttSystemConfig.h"
#endif

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              
#endif

#ifndef _STT_NOT_IN_TEST_SERVER_
void stt_xml_serialize_linevolt(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize,
                                tmt_channel *puiVOL1, tmt_channel *puiVOL2, tmt_channel *puiVOL3,
                                tmt_channel *puiCUR1, tmt_channel *puiCUR2, tmt_channel *puiCUR3)
{
    CString strID, strTypeID[3];
    strTypeID[0] = _T("_Prepare");
    strTypeID[1] = _T("_PreFault");
    strTypeID[2] = _T("_Fault");
    float fFreq = g_theSystemConfig->m_fFNom;
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("Ƶ��", "Freq", " ", "number", fFreq);
#else
    pXmlSierialize->xml_serialize(/* "Ƶ��" */g_sLangTxt_Native_Freq.GetString(), "Freq", " ", "number", fFreq);
#endif

    tmt_channel *pUI;

    for(int nTypeIndex = 0; nTypeIndex < 3; nTypeIndex++)
    {
        switch(nTypeIndex)
        {
            case 0:
                pUI = puiVOL1;
                break;

            case 1:
                pUI = puiVOL2;
                break;

            case 2:
                pUI = puiVOL3;
                break;
        }

        pUI[0].Harm[1].fFreq = fFreq;
        strID.Format(_T("Uab1%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pUI[0].Harm[1].fAmp);
        strID.Format(_T("Uab1Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pUI[0].Harm[1].fAngle);
        pUI[1].Harm[1].fFreq = fFreq;
        strID.Format(_T("3U0_1%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pUI[1].Harm[1].fAmp);
        strID.Format(_T("3U0_1Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pUI[1].Harm[1].fAngle);
        pUI[2].Harm[1].fFreq = fFreq;
        strID.Format(_T("Uab2%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pUI[2].Harm[1].fAmp);
        strID.Format(_T("Uab2Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pUI[2].Harm[1].fAngle);
        pUI[3].Harm[1].fFreq = fFreq;
        strID.Format(_T("3U0_2%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pUI[3].Harm[1].fAmp);
        strID.Format(_T("3U0_2Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pUI[3].Harm[1].fAngle);
    }

    for(int nTypeIndex = 0; nTypeIndex < 3; nTypeIndex++)
    {
        switch(nTypeIndex)
        {
            case 0:
                pUI = puiCUR1;
                break;

            case 1:
                pUI = puiCUR2;
                break;

            case 2:
                pUI = puiCUR3;
                break;
        }

        for(int nGroup = 0; nGroup < 2; nGroup++)
        {
            pUI[nGroup * 3].Harm[1].fFreq = fFreq;
            strID.Format(_T("Ia%d%s"), nGroup + 1, strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pUI[nGroup * 3].Harm[1].fAmp);
            strID.Format(_T("Ia%dPh%s"), nGroup + 1, strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pUI[nGroup * 3].Harm[1].fAngle);
            pUI[nGroup * 3 + 1].Harm[1].fFreq = fFreq;
            strID.Format(_T("Ib%d%s"), nGroup + 1, strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pUI[nGroup * 3 + 1].Harm[1].fAmp);
            strID.Format(_T("Ib%dPh%s"), nGroup + 1, strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pUI[nGroup * 3 + 1].Harm[1].fAngle);
            pUI[nGroup * 3 + 2].Harm[1].fFreq = fFreq;
            strID.Format(_T("Ic%d%s"), nGroup + 1, strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pUI[nGroup * 3 + 2].Harm[1].fAmp);
            strID.Format(_T("Ic%dPh%s"), nGroup + 1, strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pUI[nGroup * 3 + 2].Harm[1].fAngle);
        }
    }
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "", "set", pParas->m_fStop);
    pXmlSierialize->xml_serialize("���Ծ���", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("����ʱ��(��)", "StepTime", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("�ݱ����", "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
    pXmlSierialize->xml_serialize("����ǰʱ��(��)", "_PrepareTime", "s", "number", pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize("����ǰʱ��(��)", "_PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0], pXmlSierialize, FALSE);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1], pXmlSierialize, TRUE);
    pXmlSierialize->xml_serialize("�����߼�", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#else
    pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize(/* "�仯��ֵ" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "", "set", pParas->m_fStop);
    pXmlSierialize->xml_serialize(/* "���Ծ���" */g_sLangTxt_Native_TestPrecision.GetString(), "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize(/* "����ʱ��(��)" */g_sLangTxt_Native_StepTimeSec.GetString(), "StepTime", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize(/* "�ݱ����" */g_sLangTxt_Native_VariablePhaseChange.GetString(), "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
    pXmlSierialize->xml_serialize(/* "����ǰʱ��(��)" */g_sLangTxt_Native_PreTestTimeS.GetString(), "_PrepareTime", "s", "number", pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize(/* "����ǰʱ��(��)" */g_sLangTxt_Native_FaultPreTimeS.GetString(), "_PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0], pXmlSierialize, FALSE);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1], pXmlSierialize, TRUE);
    pXmlSierialize->xml_serialize(/* "�����߼�" */g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif

    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
    }
}
#endif

void stt_xml_serialize_write_LineVolGradientTest()
{
    tmt_linevolgradient_test_ex oLineVolGradientTest;
    oLineVolGradientTest.init();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeRegister(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize_LineVol_ex(&oLineVolGradientTest.m_oLineVolGradientParasEx, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("LineVolGradientTestDemo.xml");
    //  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

void stt_xml_serialize_LineVol(tmt_LineVolGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_base_LineVol(pParas, pXmlSierialize);

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        if(pParas->m_nSttTestMode == GradientTest_Base_1)
        {
            stt_xml_serialize_Chs_linevolt(pParas, pXmlSierialize);
        }
        else
        {
        #ifdef NOT_USE_XLANGUAGE
            pXmlSierialize->xml_serialize("Uab1��ֵ", "Uab1Amp", "V", "number", pParas->m_uiVOL[2][0].Harm[1].fAmp);
            pXmlSierialize->xml_serialize("Uab1��λ", "Uab1Ph", "��", "number", pParas->m_uiVOL[2][0].Harm[1].fAngle);
            pXmlSierialize->xml_serialize("Uab1Ƶ��", "Uab1Fre", "Hz", "number", pParas->m_uiVOL[2][0].Harm[1].fFreq);
            pXmlSierialize->xml_serialize("3U0_1��ֵ", "3U0_1Amp", "V", "number", pParas->m_uiVOL[2][1].Harm[1].fAmp);
            pXmlSierialize->xml_serialize("3U0_1��λ", "3U0_1Ph", "��", "number", pParas->m_uiVOL[2][1].Harm[1].fAngle);
            pXmlSierialize->xml_serialize("3U0_1Ƶ��", "3U0_1Fre", "Hz", "number", pParas->m_uiVOL[2][1].Harm[1].fFreq);
            pXmlSierialize->xml_serialize("Uab2��ֵ", "Uab2Amp", "V", "number", pParas->m_uiVOL[2][2].Harm[1].fAmp);
            pXmlSierialize->xml_serialize("Uab2��λ", "Uab2Ph", "��", "number", pParas->m_uiVOL[2][2].Harm[1].fAngle);
            pXmlSierialize->xml_serialize("Uab2Ƶ��", "Uab2Fre", "Hz", "number", pParas->m_uiVOL[2][2].Harm[1].fFreq);
            pXmlSierialize->xml_serialize("3U0_2��ֵ", "3U0_2Amp", "V", "number", pParas->m_uiVOL[2][3].Harm[1].fAmp);
            pXmlSierialize->xml_serialize("3U0_2��λ", "3U0_2Ph", "��", "number", pParas->m_uiVOL[2][3].Harm[1].fAngle);
            pXmlSierialize->xml_serialize("3U0_2Ƶ��", "3U0_2Fre", "Hz", "number", pParas->m_uiVOL[2][3].Harm[1].fFreq);
            pXmlSierialize->xml_serialize("Ia1��ֵ", "Ia1Amp", "A", "number", pParas->m_uiCUR[2][0].Harm[1].fAmp);
            pXmlSierialize->xml_serialize("Ia1��λ", "Ia1Ph", "��", "number", pParas->m_uiCUR[2][0].Harm[1].fAngle);
            pXmlSierialize->xml_serialize("Ia1Ƶ��", "Ia1Fre", "Hz", "number", pParas->m_uiCUR[2][0].Harm[1].fFreq);
            pXmlSierialize->xml_serialize("Ib1��ֵ", "Ib1Amp", "A", "number", pParas->m_uiCUR[2][1].Harm[1].fAmp);
            pXmlSierialize->xml_serialize("Ib1��λ", "Ib1Ph", "��", "number", pParas->m_uiCUR[2][1].Harm[1].fAngle);
            pXmlSierialize->xml_serialize("Ib1Ƶ��", "Ib1Fre", "Hz", "number", pParas->m_uiCUR[2][1].Harm[1].fFreq);
            pXmlSierialize->xml_serialize("Ic1��ֵ", "Ic1Amp", "A", "number", pParas->m_uiCUR[2][2].Harm[1].fAmp);
            pXmlSierialize->xml_serialize("Ic1��λ", "Ic1Ph", "��", "number", pParas->m_uiCUR[2][2].Harm[1].fAngle);
            pXmlSierialize->xml_serialize("Ic1Ƶ��", "Ic1Fre", "Hz", "number", pParas->m_uiCUR[2][2].Harm[1].fFreq);
            pXmlSierialize->xml_serialize("Ia2��ֵ", "Ia2Amp", "A", "number", pParas->m_uiCUR[2][3].Harm[1].fAmp);
            pXmlSierialize->xml_serialize("Ia2��λ", "Ia2Ph", "��", "number", pParas->m_uiCUR[2][3].Harm[1].fAngle);
            pXmlSierialize->xml_serialize("Ia2Ƶ��", "Ia2Fre", "Hz", "number", pParas->m_uiCUR[2][3].Harm[1].fFreq);
            pXmlSierialize->xml_serialize("Ib2��ֵ", "Ib2Amp", "A", "number", pParas->m_uiCUR[2][4].Harm[1].fAmp);
            pXmlSierialize->xml_serialize("Ib2��λ", "Ib2Ph", "��", "number", pParas->m_uiCUR[2][4].Harm[1].fAngle);
            pXmlSierialize->xml_serialize("Ib2Ƶ��", "Ib2Fre", "Hz", "number", pParas->m_uiCUR[2][4].Harm[1].fFreq);
            pXmlSierialize->xml_serialize("Ic2��ֵ", "Ic2Amp", "A", "number", pParas->m_uiCUR[2][5].Harm[1].fAmp);
            pXmlSierialize->xml_serialize("Ic2��λ", "Ic2Ph", "��", "number", pParas->m_uiCUR[2][5].Harm[1].fAngle);
            pXmlSierialize->xml_serialize("Ic2Ƶ��", "Ic2Fre", "Hz", "number", pParas->m_uiCUR[2][5].Harm[1].fFreq);
        #else
            pXmlSierialize->xml_serialize(/* "Uab1��ֵ" */g_sLangTxt_Native_Uab1Amp.GetString(), "Uab1Amp", "V", "number", pParas->m_uiVOL[2][0].Harm[1].fAmp);
            pXmlSierialize->xml_serialize(/* "Uab1��λ" */g_sLangTxt_Native_Uab1Ph.GetString(), "Uab1Ph", "��", "number", pParas->m_uiVOL[2][0].Harm[1].fAngle);
            pXmlSierialize->xml_serialize(/* "Uab1Ƶ��" */g_sLangTxt_Native_Uab1Fre.GetString(), "Uab1Fre", "Hz", "number", pParas->m_uiVOL[2][0].Harm[1].fFreq);
            pXmlSierialize->xml_serialize(/* "3U0_1��ֵ" */g_sLangTxt_Native_3U0_1Amp.GetString(), "3U0_1Amp", "V", "number", pParas->m_uiVOL[2][1].Harm[1].fAmp);
            pXmlSierialize->xml_serialize(/* "3U0_1��λ" */g_sLangTxt_Native_3U0_1Ph.GetString(), "3U0_1Ph", "��", "number", pParas->m_uiVOL[2][1].Harm[1].fAngle);
            pXmlSierialize->xml_serialize(/* "3U0_1Ƶ��" */g_sLangTxt_Native_3U0_1Fre.GetString(), "3U0_1Fre", "Hz", "number", pParas->m_uiVOL[2][1].Harm[1].fFreq);
            pXmlSierialize->xml_serialize(/* "Uab2��ֵ" */g_sLangTxt_Native_Uab2Amp.GetString(), "Uab2Amp", "V", "number", pParas->m_uiVOL[2][2].Harm[1].fAmp);
            pXmlSierialize->xml_serialize(/* "Uab2��λ" */g_sLangTxt_Native_Uab2Ph.GetString(), "Uab2Ph", "��", "number", pParas->m_uiVOL[2][2].Harm[1].fAngle);
            pXmlSierialize->xml_serialize(/* "Uab2Ƶ��" */g_sLangTxt_Native_Uab2Fre.GetString(), "Uab2Fre", "Hz", "number", pParas->m_uiVOL[2][2].Harm[1].fFreq);
            pXmlSierialize->xml_serialize(/* "3U0_2��ֵ" */g_sLangTxt_Native_3U0_2Amp.GetString(), "3U0_2Amp", "V", "number", pParas->m_uiVOL[2][3].Harm[1].fAmp);
            pXmlSierialize->xml_serialize(/* "3U0_2��λ" */g_sLangTxt_Native_3U0_2Ph.GetString(), "3U0_2Ph", "��", "number", pParas->m_uiVOL[2][3].Harm[1].fAngle);
            pXmlSierialize->xml_serialize(/* "3U0_2Ƶ��" */g_sLangTxt_Native_3U0_2Fre.GetString(), "3U0_2Fre", "Hz", "number", pParas->m_uiVOL[2][3].Harm[1].fFreq);
            pXmlSierialize->xml_serialize(/* "Ia1��ֵ" */g_sLangTxt_Native_Ia1Amp.GetString(), "Ia1Amp", "A", "number", pParas->m_uiCUR[2][0].Harm[1].fAmp);
            pXmlSierialize->xml_serialize(/* "Ia1��λ" */g_sLangTxt_Native_Ia1Ph.GetString(), "Ia1Ph", "��", "number", pParas->m_uiCUR[2][0].Harm[1].fAngle);
            pXmlSierialize->xml_serialize(/* "Ia1Ƶ��" */g_sLangTxt_Native_Ia1Fre.GetString(), "Ia1Fre", "Hz", "number", pParas->m_uiCUR[2][0].Harm[1].fFreq);
            pXmlSierialize->xml_serialize(/* "Ib1��ֵ" */g_sLangTxt_Native_Ib1Amp.GetString(), "Ib1Amp", "A", "number", pParas->m_uiCUR[2][1].Harm[1].fAmp);
            pXmlSierialize->xml_serialize(/* "Ib1��λ" */g_sLangTxt_Native_Ib1Ph.GetString(), "Ib1Ph", "��", "number", pParas->m_uiCUR[2][1].Harm[1].fAngle);
            pXmlSierialize->xml_serialize(/* "Ib1Ƶ��" */g_sLangTxt_Native_Ib1Fre.GetString(), "Ib1Fre", "Hz", "number", pParas->m_uiCUR[2][1].Harm[1].fFreq);
            pXmlSierialize->xml_serialize(/* "Ic1��ֵ" */g_sLangTxt_Native_Ic1Amp.GetString(), "Ic1Amp", "A", "number", pParas->m_uiCUR[2][2].Harm[1].fAmp);
            pXmlSierialize->xml_serialize(/* "Ic1��λ" */g_sLangTxt_Native_Ic1Ph.GetString(), "Ic1Ph", "��", "number", pParas->m_uiCUR[2][2].Harm[1].fAngle);
            pXmlSierialize->xml_serialize(/* "Ic1Ƶ��" */g_sLangTxt_Native_Ic1Fre.GetString(), "Ic1Fre", "Hz", "number", pParas->m_uiCUR[2][2].Harm[1].fFreq);
            pXmlSierialize->xml_serialize(/* "Ia2��ֵ" */g_sLangTxt_Native_Ia2Amp.GetString(), "Ia2Amp", "A", "number", pParas->m_uiCUR[2][3].Harm[1].fAmp);
            pXmlSierialize->xml_serialize(/* "Ia2��λ" */g_sLangTxt_Native_Ia2Ph.GetString(), "Ia2Ph", "��", "number", pParas->m_uiCUR[2][3].Harm[1].fAngle);
            pXmlSierialize->xml_serialize(/* "Ia2Ƶ��" */g_sLangTxt_Native_Ia2Fre.GetString(), "Ia2Fre", "Hz", "number", pParas->m_uiCUR[2][3].Harm[1].fFreq);
            pXmlSierialize->xml_serialize(/* "Ib2��ֵ" */g_sLangTxt_Native_Ib2Amp.GetString(), "Ib2Amp", "A", "number", pParas->m_uiCUR[2][4].Harm[1].fAmp);
            pXmlSierialize->xml_serialize(/* "Ib2��λ" */g_sLangTxt_Native_Ib2Ph.GetString(), "Ib2Ph", "��", "number", pParas->m_uiCUR[2][4].Harm[1].fAngle);
            pXmlSierialize->xml_serialize(/* "Ib2Ƶ��" */g_sLangTxt_Native_Ib2Fre.GetString(), "Ib2Fre", "Hz", "number", pParas->m_uiCUR[2][4].Harm[1].fFreq);
            pXmlSierialize->xml_serialize(/* "Ic2��ֵ" */g_sLangTxt_Native_Ic2Amp.GetString(), "Ic2Amp", "A", "number", pParas->m_uiCUR[2][5].Harm[1].fAmp);
            pXmlSierialize->xml_serialize(/* "Ic2��λ" */g_sLangTxt_Native_Ic2Ph.GetString(), "Ic2Ph", "��", "number", pParas->m_uiCUR[2][5].Harm[1].fAngle);
            pXmlSierialize->xml_serialize(/* "Ic2Ƶ��" */g_sLangTxt_Native_Ic2Fre.GetString(), "Ic2Fre", "Hz", "number", pParas->m_uiCUR[2][5].Harm[1].fFreq);
        #endif

        }
    }

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
    }
}

void stt_xml_serialize_LineVol(tmt_LineVolGradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("����ֵ", "TripValue", "A/V", "number", pResults->m_fTripValue);
    pXmlSierialize->xml_serialize("����ʱ��", "TripTime", "s", "number", pResults->m_fTripTime);
// 	pXmlSierialize->xml_serialize("����ֵ","ReturnValue","A/V","number",pResults->m_fReturnValue);
// 	pXmlSierialize->xml_serialize("����ϵ��","ReturnCoef","","number",pResults->m_fReturnCoef);
// 	pXmlSierialize->xml_serialize("�߽��1","AngleF","","number",pResults->m_oMaxAngle.m_fAngleF);
// 	pXmlSierialize->xml_serialize("�߽��2","AngleS","","number",pResults->m_oMaxAngle.m_fAngleS);
// 	pXmlSierialize->xml_serialize("���������","MaxAngle","","number",pResults->m_oMaxAngle.m_fMaxAngle);
    pXmlSierialize->xml_serialize("��ѹ����ֵ���", "TripUErrVal", "", "number", pResults->m_fTripUErrVal);
    pXmlSierialize->xml_serialize("��������ֵ���", "TripIErrVal", "", "number", pResults->m_fTripIErrVal);
// 	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ���","TripHzErrVal","","number",pResults->m_fTripHzErrVal);
// 	pXmlSierialize->xml_serialize("��λ����ֵ���","TripAngleErrVal","","number",pResults->m_fTripAngleErrVal);
// 	pXmlSierialize->xml_serialize("����ϵ�����","RetCoefErrVal","","number",pResults->m_fRetCoefErrVal);
// 	pXmlSierialize->xml_serialize("������������","MaxAngleErrVal","","number",pResults->m_fMaxAngleErrVal);
// 	pXmlSierialize->xml_serialize("�߽��1���","AngleFErrVal","","number",pResults->m_fAngleFErrVal);
// 	pXmlSierialize->xml_serialize("�߽��2���","AngleSErrVal","","number",pResults->m_fAngleSErrVal);
    pXmlSierialize->xml_serialize("��������", "ActDsec", "", "number", pResults->m_nAct);
    pXmlSierialize->xml_serialize("����1����ֵ", "TripValueA", "A/V", "number", pResults->m_fTripValueChl[0]);
    pXmlSierialize->xml_serialize("����2����ֵ", "TripValueB", "A/V", "number", pResults->m_fTripValueChl[1]);
    pXmlSierialize->xml_serialize("����3����ֵ", "TripValueC", "A/V", "number", pResults->m_fTripValueChl[2]);
    pXmlSierialize->xml_serialize("����4����ֵ", "TripValueD", "A/V", "number", pResults->m_fTripValueChl[3]);
    pXmlSierialize->xml_serialize("����5����ֵ", "TripValueE", "A/V", "number", pResults->m_fTripValueChl[4]);
    pXmlSierialize->xml_serialize("����6����ֵ", "TripValueF", "A/V", "number", pResults->m_fTripValueChl[5]);
    pXmlSierialize->xml_serialize("����7����ֵ", "TripValueG", "A/V", "number", pResults->m_fTripValueChl[6]);
    pXmlSierialize->xml_serialize("����8����ֵ", "TripValueH", "A/V", "number", pResults->m_fTripValueChl[7]);
#else
    pXmlSierialize->xml_serialize(/* "����ֵ" */g_sLangTxt_State_ActionValue.GetString(), "TripValue", "A/V", "number", pResults->m_fTripValue);
    pXmlSierialize->xml_serialize(/* "����ʱ��" */g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "s", "number", pResults->m_fTripTime);
// 	pXmlSierialize->xml_serialize("����ֵ","ReturnValue","A/V","number",pResults->m_fReturnValue);
// 	pXmlSierialize->xml_serialize("����ϵ��","ReturnCoef","","number",pResults->m_fReturnCoef);
// 	pXmlSierialize->xml_serialize("�߽��1","AngleF","","number",pResults->m_oMaxAngle.m_fAngleF);
// 	pXmlSierialize->xml_serialize("�߽��2","AngleS","","number",pResults->m_oMaxAngle.m_fAngleS);
// 	pXmlSierialize->xml_serialize("���������","MaxAngle","","number",pResults->m_oMaxAngle.m_fMaxAngle);
    pXmlSierialize->xml_serialize(/* "��ѹ����ֵ���" */g_sLangTxt_Native_VActionValueErr.GetString(), "TripUErrVal", "", "number", pResults->m_fTripUErrVal);
    pXmlSierialize->xml_serialize(/* "��������ֵ���" */g_sLangTxt_Native_IActionValueErr.GetString(), "TripIErrVal", "", "number", pResults->m_fTripIErrVal);
// 	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ���","TripHzErrVal","","number",pResults->m_fTripHzErrVal);
// 	pXmlSierialize->xml_serialize("��λ����ֵ���","TripAngleErrVal","","number",pResults->m_fTripAngleErrVal);
// 	pXmlSierialize->xml_serialize("����ϵ�����","RetCoefErrVal","","number",pResults->m_fRetCoefErrVal);
// 	pXmlSierialize->xml_serialize("������������","MaxAngleErrVal","","number",pResults->m_fMaxAngleErrVal);
// 	pXmlSierialize->xml_serialize("�߽��1���","AngleFErrVal","","number",pResults->m_fAngleFErrVal);
// 	pXmlSierialize->xml_serialize("�߽��2���","AngleSErrVal","","number",pResults->m_fAngleSErrVal);
    pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(), "ActDsec", "", "number", pResults->m_nAct);
    pXmlSierialize->xml_serialize(/* "����1����ֵ" */g_sLangTxt_Native_input1_ActionVal.GetString(), "TripValueA", "A/V", "number", pResults->m_fTripValueChl[0]);
    pXmlSierialize->xml_serialize(/* "����2����ֵ" */g_sLangTxt_Native_input2_ActionVal.GetString(), "TripValueB", "A/V", "number", pResults->m_fTripValueChl[1]);
    pXmlSierialize->xml_serialize(/* "����3����ֵ" */g_sLangTxt_Native_input3_ActionVal.GetString(), "TripValueC", "A/V", "number", pResults->m_fTripValueChl[2]);
    pXmlSierialize->xml_serialize(/* "����4����ֵ" */g_sLangTxt_Native_input4_ActionVal.GetString(), "TripValueD", "A/V", "number", pResults->m_fTripValueChl[3]);
    pXmlSierialize->xml_serialize(/* "����5����ֵ" */g_sLangTxt_Native_input5_ActionVal.GetString(), "TripValueE", "A/V", "number", pResults->m_fTripValueChl[4]);
    pXmlSierialize->xml_serialize(/* "����6����ֵ" */g_sLangTxt_Native_input6_ActionVal.GetString(), "TripValueF", "A/V", "number", pResults->m_fTripValueChl[5]);
    pXmlSierialize->xml_serialize(/* "����7����ֵ" */g_sLangTxt_Native_input7_ActionVal.GetString(), "TripValueG", "A/V", "number", pResults->m_fTripValueChl[6]);
    pXmlSierialize->xml_serialize(/* "����8����ֵ" */g_sLangTxt_Native_input8_ActionVal.GetString(), "TripValueH", "A/V", "number", pResults->m_fTripValueChl[7]);

#endif


    if(g_nBinExCount > 0)
    {
        CSttXmlSerializeBase *pXmlTripValueEx = pXmlSierialize->xml_serialize("TripValueEx", "TripValueEx", "TripValueEx", stt_ParaGroupKey());

        if(pXmlTripValueEx != NULL)
        {
#ifdef NOT_USE_XLANGUAGE
            CString strName, strID, strTemp;
            CString str1 = _T("����");
            CString str1Ex = _T("������չ");
            CString str2 = _T("����ֵ");
#else
            CString strName, strID, strTemp;
            CString str1 = /* _T("����") */g_sLangTxt_Native_BinX;
            CString str1Ex = /* _T("������չ") */g_sLangTxt_Native_InputExpand;
            CString str2 = /* _T("����ֵ") */g_sLangTxt_State_ActionValue;
#endif

            for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
            {
                strTemp.Format(_T("%d"), nIndex + 1);
                strName = str1Ex + strTemp + str2;

                strID.Format("TripValueEx%d", (nIndex + 1));
                pXmlTripValueEx->xml_serialize(strName.GetString(), strID.GetString(), "", "A/V", pResults->m_fTripValueExChl[nIndex]);
            }
        }
    }
}

void stt_xml_serialize_Chs_linevolt(tmt_LineVolGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    float fFreq = 50.0;
    CString strID, strTypeID[3];
    strTypeID[0] = _T("_Prepare");
    strTypeID[1] = _T("_PreFault");
    strTypeID[2] = _T("_Fault");
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("Ƶ��", "Freq", " ", "number", fFreq);
#else
    pXmlSierialize->xml_serialize(/* "Ƶ��" */g_sLangTxt_Native_Freq.GetString(), "Freq", " ", "number", fFreq);
#endif

    for(int nTypeIndex = 0; nTypeIndex < 3; nTypeIndex++)
    {
        pParas->m_uiVOL[nTypeIndex][0].Harm[1].fFreq = fFreq;
        strID.Format(_T("Uab1%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pParas->m_uiVOL[nTypeIndex][0].Harm[1].fAmp);
        strID.Format(_T("Uab1Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pParas->m_uiVOL[nTypeIndex][0].Harm[1].fAngle);
        pParas->m_uiVOL[nTypeIndex][1].Harm[1].fFreq = fFreq;
        strID.Format(_T("3U0_1%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pParas->m_uiVOL[nTypeIndex][1].Harm[1].fAmp);
        strID.Format(_T("3U0_1Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pParas->m_uiVOL[nTypeIndex][1].Harm[1].fAngle);
        pParas->m_uiVOL[nTypeIndex][2].Harm[1].fFreq = fFreq;
        strID.Format(_T("Uab2%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pParas->m_uiVOL[nTypeIndex][2].Harm[1].fAmp);
        strID.Format(_T("Uab2Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pParas->m_uiVOL[nTypeIndex][2].Harm[1].fAngle);
        pParas->m_uiVOL[nTypeIndex][3].Harm[1].fFreq = fFreq;
        strID.Format(_T("3U0_2%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pParas->m_uiVOL[nTypeIndex][3].Harm[1].fAmp);
        strID.Format(_T("3U0_2Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pParas->m_uiVOL[nTypeIndex][3].Harm[1].fAngle);

        for(int nGroup = 0; nGroup < 2; nGroup++)
        {
            pParas->m_uiCUR[nTypeIndex][nGroup * 3].Harm[1].fFreq = fFreq;
            strID.Format(_T("Ia%d%s"), nGroup + 1, strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pParas->m_uiCUR[nTypeIndex][nGroup * 3].Harm[1].fAmp);
            strID.Format(_T("Ia%dPh%s"), nGroup + 1, strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pParas->m_uiCUR[nTypeIndex][nGroup * 3].Harm[1].fAngle);
            pParas->m_uiCUR[nTypeIndex][nGroup * 3 + 1].Harm[1].fFreq = fFreq;
            strID.Format(_T("Ib%d%s"), nGroup + 1, strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pParas->m_uiCUR[nTypeIndex][nGroup * 3 + 1].Harm[1].fAmp);
            strID.Format(_T("Ib%dPh%s"), nGroup + 1, strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pParas->m_uiCUR[nTypeIndex][nGroup * 3 + 1].Harm[1].fAngle);
            pParas->m_uiCUR[nTypeIndex][nGroup * 3 + 2].Harm[1].fFreq = fFreq;
            strID.Format(_T("Ic%d%s"), nGroup + 1, strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pParas->m_uiCUR[nTypeIndex][nGroup * 3 + 2].Harm[1].fAmp);
            strID.Format(_T("Ic%dPh%s"), nGroup + 1, strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pParas->m_uiCUR[nTypeIndex][nGroup * 3 + 2].Harm[1].fAngle);
        }
    }
}

void stt_xml_serializeLineVolGradientSetting(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("��ѹ��������ֵ", "USet", "V", "float", pParas->m_fUSet);
    pXmlSierialize->xml_serialize("������������ֵ", "ISet", "A", "float", pParas->m_fISet);
#else
    pXmlSierialize->xml_serialize(/* "��ѹ��������ֵ" */g_sLangTxt_Native_VolSetActValue.GetString(), "USet", "V", "float", pParas->m_fUSet);
    pXmlSierialize->xml_serialize(/* "������������ֵ" */g_sLangTxt_Native_CurSetActValue.GetString(), "ISet", "A", "float", pParas->m_fISet);
#endif

}

CSttXmlSerializeBase *stt_xml_serialize_LineVol(tmt_linevolgradient_test_ex *pParas, CSttXmlSerializeBase *pXmlSerialize)
{
    //	stt_xml_serialize((PTMT_PARAS_HEAD)pParas, pXmlSerialize);

    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if(pXmlParas != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
			stt_xml_serialize_LineVol_ex(&pParas->m_oLineVolGradientParasEx, pXmlParas);	//�ļ��Ķ�д
        }
        else if(pParas->m_nSelected)
        {
			stt_xml_serialize_LineVol_ex(&pParas->m_oLineVolGradientParasEx, pXmlParas);	//���Բ����·�
        }
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if(pXmlResults != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
			stt_xml_serialize_LineVol(&pParas->m_oLineVolGradientResultParas, pXmlResults);
        }
        else if(pParas->m_nSelected)
        {
			stt_xml_serialize_LineVol(&pParas->m_oLineVolGradientResultParas, pXmlResults);
        }
    }

    return pXmlParas;
}

void stt_xml_serialize_base_LineVol(tmt_LineVolGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("�ݱ�ģʽ(0-����ģʽ1-��ѹ�ݱ� 2-�����ݱ� 3-��������ģʽ)", "SttTestMode", "", "number", pParas->m_nSttTestMode);
    pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "", "set", pParas->m_fStop);
    pXmlSierialize->xml_serialize("���Ծ���", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("����ʱ��(��)", "StepTime", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("���Է���ϵ��", "VaryMode", "", "number", pParas->m_nTestMode);
    pXmlSierialize->xml_serialize("����ͨ������", "VarIndexType", "", "number", pParas->m_nVarIndexType);
    pXmlSierialize->xml_serialize("�ݱ����", "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
    pXmlSierialize->xml_serialize("�ݱ�����", "VarType", "", "UIRampType", pParas->m_nType);
    pXmlSierialize->xml_serialize("��λ�ݱ䷽��(0:��ʱ�� 1:˳ʱ��)", "PhaseGradDir", "", "number", pParas->m_nPhaseGradDir);
    //	pXmlSierialize->xml_serialize("�Ƶ��","_Freq","Hz","number",pParas->m_fEDFreq);
    pXmlSierialize->xml_serialize("����ǰʱ��(��)", "_PrepareTime", "s", "number", pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize("����ǰʱ��(��)", "_PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
    //	pXmlSierialize->xml_serialize("���ѹ��ֵ","_UPre","V","number",pParas->m_fEDU);
    pXmlSierialize->xml_serialize("�仯ǰ������ֵ", "_IPre", "A", "number", pParas->m_fEDI);
    pXmlSierialize->xml_serialize("����ǰ��ѹ�������(U-I)", "PreAngle", "��", "number",  pParas->m_fEDUaIaAngle);
#else
    pXmlSierialize->xml_serialize(/* "�ݱ�ģʽ(0-����ģʽ1-��ѹ�ݱ� 2-�����ݱ� 3-��������ģʽ)" */g_sLangTxt_Native_VariableMode0123.GetString(), "SttTestMode", "", "number", pParas->m_nSttTestMode);
    pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize(/* "�仯��ֵ" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "", "set", pParas->m_fStop);
    pXmlSierialize->xml_serialize(/* "���Ծ���" */g_sLangTxt_Native_TestPrecision.GetString(), "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize(/* "����ʱ��(��)" */g_sLangTxt_Native_StepTimeSec.GetString(), "StepTime", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize(/* "���Է���ϵ��" */g_sLangTxt_Native_TestReturnCoefficient.GetString(), "VaryMode", "", "number", pParas->m_nTestMode);
    pXmlSierialize->xml_serialize(/* "����ͨ������" */g_sLangTxt_Native_TestChannelType.GetString(), "VarIndexType", "", "number", pParas->m_nVarIndexType);
    pXmlSierialize->xml_serialize(/* "�ݱ����" */g_sLangTxt_Native_VariablePhaseChange.GetString(), "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
    pXmlSierialize->xml_serialize(/* "�ݱ�����" */g_sLangTxt_Native_VariableType.GetString(), "VarType", "", "UIRampType", pParas->m_nType);
    pXmlSierialize->xml_serialize(/* "��λ�ݱ䷽��(0:��ʱ�� 1:˳ʱ��)" */g_sLangTxt_Native_PhaseShiftDir01.GetString(), "PhaseGradDir", "", "number", pParas->m_nPhaseGradDir);
    //	pXmlSierialize->xml_serialize("�Ƶ��","_Freq","Hz","number",pParas->m_fEDFreq);
    pXmlSierialize->xml_serialize(/* "����ǰʱ��(��)" */g_sLangTxt_Native_PreTestTimeS.GetString(), "_PrepareTime", "s", "number", pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize(/* "����ǰʱ��(��)" */g_sLangTxt_Native_FaultPreTimeS.GetString(), "_PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
    //	pXmlSierialize->xml_serialize("���ѹ��ֵ","_UPre","V","number",pParas->m_fEDU);
    pXmlSierialize->xml_serialize(/* "�仯ǰ������ֵ" */g_sLangTxt_Native_IBeforeChange.GetString(), "_IPre", "A", "number", pParas->m_fEDI);
    pXmlSierialize->xml_serialize(/* "����ǰ��ѹ�������(U-I)" */g_sLangTxt_Native_FaultPreUIPhaseAngle.GetString(), "PreAngle", "��", "number",  pParas->m_fEDUaIaAngle);
#endif

    //���ݱ仯ǰ������ʼ������ǰ����
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        pParas->m_fG1Current = pParas->m_fEDI;
        pParas->m_fG2Current = pParas->m_fEDI;
    }

#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("����̬��1��ѹ��ֵ", "_UFaultG1", "V", "number", pParas->m_fG1Volt);
    pXmlSierialize->xml_serialize("����̬��2��ѹ��ֵ", "_UFaultG2", "V", "number", pParas->m_fG2Volt);
    pXmlSierialize->xml_serialize("����̬��1������ֵ", "_IFaultG1", "V", "number", pParas->m_fG1Current);
    pXmlSierialize->xml_serialize("����̬��2������ֵ", "_IFaultG2", "V", "number", pParas->m_fG2Current);
    pXmlSierialize->xml_serialize("����̬��������ǲ�", "_DiffIAngle", "��", "number", pParas->m_fDiffIAngle);
    pXmlSierialize->xml_serialize("����̬Ƶ��", "_FreqFault", "Hz", "number", pParas->m_fHz);

    pXmlSierialize->xml_serialize("�����߼�", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0], pXmlSierialize, FALSE);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1], pXmlSierialize, TRUE);

    stt_xml_serializeLineVolGradientSetting(pParas, pXmlSierialize);

	pXmlSierialize->xml_serialize("��ѹ����ֵ�������","UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize("��ѹ����ֵ������","UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize("��ѹ����ֵ����ж��߼�","UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("��������ֵ�������","IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize("��������ֵ������","IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize("��������ֵ����ж��߼�","IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
#else
    pXmlSierialize->xml_serialize(/* "����̬��1��ѹ��ֵ" */g_sLangTxt_Native_FaultGroup1VAmp.GetString(), "_UFaultG1", "V", "number", pParas->m_fG1Volt);
    pXmlSierialize->xml_serialize(/* "����̬��2��ѹ��ֵ" */g_sLangTxt_Native_FSG2VoltageAmplitude.GetString(), "_UFaultG2", "V", "number", pParas->m_fG2Volt);
    pXmlSierialize->xml_serialize(/* "����̬��1������ֵ" */g_sLangTxt_Native_FaultGroup1IAmp.GetString(), "_IFaultG1", "V", "number", pParas->m_fG1Current);
    pXmlSierialize->xml_serialize(/* "����̬��2������ֵ" */g_sLangTxt_Native_FSG2CurrentAmplitude.GetString(), "_IFaultG2", "V", "number", pParas->m_fG2Current);
    pXmlSierialize->xml_serialize(/* "����̬��������ǲ�" */g_sLangTxt_Native_FaultGroupIPhaseDiff.GetString(), "_DiffIAngle", "��", "number", pParas->m_fDiffIAngle);
    pXmlSierialize->xml_serialize(/* "����̬Ƶ��" */g_sLangTxt_Native_FaultGroupFreq.GetString(), "_FreqFault", "Hz", "number", pParas->m_fHz);

    pXmlSierialize->xml_serialize(/* "�����߼�" */g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0], pXmlSierialize, FALSE);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1], pXmlSierialize, TRUE);

    stt_xml_serializeLineVolGradientSetting(pParas, pXmlSierialize);

	pXmlSierialize->xml_serialize(/* "��ѹ����ֵ�������" */g_sLangTxt_Native_VActionValueAbsErr.GetString(),"UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize(/* "��ѹ����ֵ������" */g_sLangTxt_Native_VActionValueRelErr.GetString(),"UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize(/* "��ѹ����ֵ����ж��߼�" */g_sLangTxt_Native_VActionValueErrLogic.GetString(),"UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/* "��������ֵ�������" */g_sLangTxt_Native_IActionValueAbsErr.GetString(),"IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize(/* "��������ֵ������" */g_sLangTxt_Native_IActionValueRelErr.GetString(),"IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize(/* "��������ֵ����ж��߼�" */g_sLangTxt_Native_IActionValueErrLogic.GetString(),"IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
#endif



// 	pXmlSierialize->xml_serialize("��λ����ֵ�������","AngleActVal_AbsErr","","float",pParas->m_fAngleActVal_AbsErr);
// 	pXmlSierialize->xml_serialize("��λ����ֵ������","AngleActVal_RelErr","","float",pParas->m_fAngleActVal_RelErr);
// 	pXmlSierialize->xml_serialize("��λ����ֵ����ж��߼�","AngleActVal_ErrorLogic","","number",pParas->m_nAngleActVal_ErrorLogic);
// 	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ�������","HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);	
// 	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ������","HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);	
// 	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ����ж��߼�","HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);	
// 	pXmlSierialize->xml_serialize("����ϵ���������","RetCoef_AbsErr","","float",pParas->m_fRetCoef_AbsErr);
// 	pXmlSierialize->xml_serialize("����ϵ��������","RetCoef_RelErr","","float",pParas->m_fRetCoef_RelErr);	
// 	pXmlSierialize->xml_serialize("����ϵ������ж��߼�","RetCoef_ErrorLogic","","number",pParas->m_nRetCoef_ErrorLogic);
// 	pXmlSierialize->xml_serialize("��������Ǿ������","MaxAngle_AbsErr","��","float",pParas->m_fMaxAngle_AbsErr);	
// 	pXmlSierialize->xml_serialize("���������������","MaxAngle_RelErr","","float",pParas->m_fMaxAngle_RelErr);
// 	pXmlSierialize->xml_serialize("�������������ж��߼�","MaxAngle_ErrorLogic","","number",pParas->m_nMaxAngle_ErrorLogic);	
// 	pXmlSierialize->xml_serialize("�߽��1�������","AngleF_AbsErr","��","float",pParas->m_fAngleF_AbsErr);	
// 	pXmlSierialize->xml_serialize("�߽��1������","AngleF_RelErr","","float",pParas->m_fAngleF_RelErr);	
// 	pXmlSierialize->xml_serialize("�߽��1����ж��߼�","AngleF_ErrorLogic","","number",pParas->m_nAngleF_ErrorLogic);
// 	pXmlSierialize->xml_serialize("�߽��2�������","AngleS_AbsErr","��","float",pParas->m_fAngleS_AbsErr);	
// 	pXmlSierialize->xml_serialize("�߽��2������","AngleS_RelErr","","float",pParas->m_fAngleS_RelErr);
// 	pXmlSierialize->xml_serialize("�߽��2����ж��߼�","AngleS_ErrorLogic","","number",pParas->m_nAngleS_ErrorLogic);

}

void stt_xml_serialize_LineVol_ex(tmt_LineVolGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_base_LineVol(pParas, pXmlSierialize);
    stt_xml_serialize_Chs_linevolt(pParas, pXmlSierialize);

	tmt_LineVolGradientParasEx* pParasEx = (tmt_LineVolGradientParasEx*)pParas;

    //�о�����
    int bVal = 0;
#ifdef NOT_USE_XLANGUAGE
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        pXmlSierialize->xml_serialize("��������Ч", "_XD", "", "number", bVal);
        pParasEx->sCondition.bXD = bVal;
        pXmlSierialize->xml_serialize("������", "_XDVal", "", "number", pParasEx->sCondition.fXD);
    }
    else if(stt_xml_serialize_is_register(pXmlSierialize))
    {
		if(pParasEx->sCondition.bXD){	bVal = 1;	}
        pXmlSierialize->xml_serialize("��������Ч", "_XD", "", "number", bVal);
        pXmlSierialize->xml_serialize("������", "_XDVal", "", "number", pParasEx->sCondition.fXD);
    }

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        pXmlSierialize->xml_serialize("���������Ч", "_JD", "", "number", bVal);
        pParasEx->sCondition.bJD = bVal;
        pXmlSierialize->xml_serialize("�������", "_JDVal", "", "number", pParasEx->sCondition.fJD);
    }
    else if(stt_xml_serialize_is_register(pXmlSierialize))
    {
        bVal = 0;
		if(pParasEx->sCondition.bJD){	bVal = 1;	}
        pXmlSierialize->xml_serialize("���������Ч", "_JD", "", "number", bVal);
        pXmlSierialize->xml_serialize("�������", "_JDVal", "", "number", pParasEx->sCondition.fJD);
    }

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        pXmlSierialize->xml_serialize("����ϵ����Ч", "_Coeff", "", "number", bVal);
        pParasEx->sCondition.bCoeff = bVal;
        pXmlSierialize->xml_serialize("����ϵ��", "_CoeffVal", "", "number", pParasEx->sCondition.fCoeff);
    }
    else if(stt_xml_serialize_is_register(pXmlSierialize))
    {
        bVal = 0;
		if(pParasEx->sCondition.bCoeff){	bVal = 1;	}
        pXmlSierialize->xml_serialize("����ϵ����Ч", "_Coeff", "", "number", bVal);
        pXmlSierialize->xml_serialize("����ϵ��", "_CoeffVal", "", "number", pParasEx->sCondition.fCoeff);
    }

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        pXmlSierialize->xml_serialize("�о��߼�", "_LogicOrAnd", "��", "number", bVal);
        pParasEx->sCondition.bLogicOr = bVal;
    }
    else if(stt_xml_serialize_is_register(pXmlSierialize))
    {
        bVal = 0;
		if(pParasEx->sCondition.bLogicOr){		bVal = 1;	}
        pXmlSierialize->xml_serialize("�о��߼�", "_LogicOrAnd", "��", "number", bVal);
    }
#else
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        pXmlSierialize->xml_serialize(/* "��������Ч" */g_sLangTxt_Native_relativeErr.GetString(), "_XD", "", "number", bVal);
        pParasEx->sCondition.bXD = bVal;
        pXmlSierialize->xml_serialize(/* "������" */g_sLangTxt_StateEstimate_RelError.GetString(), "_XDVal", "", "number", pParasEx->sCondition.fXD);
    }
    else if(stt_xml_serialize_is_register(pXmlSierialize))
    {
		if(pParasEx->sCondition.bXD){	bVal = 1;	}
        pXmlSierialize->xml_serialize(/* "��������Ч" */g_sLangTxt_Native_relativeErr.GetString(), "_XD", "", "number", bVal);
        pXmlSierialize->xml_serialize(/* "������" */g_sLangTxt_StateEstimate_RelError.GetString(), "_XDVal", "", "number", pParasEx->sCondition.fXD);
    }

    if(stt_xml_serialize_is_read(pXmlSierialize))
        {
        pXmlSierialize->xml_serialize(/* "���������Ч" */g_sLangTxt_Native_AbsErrValid.GetString(), "_JD", "", "number", bVal);
        pParasEx->sCondition.bJD = bVal;
        pXmlSierialize->xml_serialize(/* "�������" */g_sLangTxt_StateEstimate_AbsError.GetString(), "_JDVal", "", "number", pParasEx->sCondition.fJD);
    }
    else if(stt_xml_serialize_is_register(pXmlSierialize))
    {
        bVal = 0;
		if(pParasEx->sCondition.bJD){	bVal = 1;	}
        pXmlSierialize->xml_serialize(/* "���������Ч" */g_sLangTxt_Native_AbsErrValid.GetString(), "_JD", "", "number", bVal);
        pXmlSierialize->xml_serialize(/* "�������" */g_sLangTxt_StateEstimate_AbsError.GetString(), "_JDVal", "", "number", pParasEx->sCondition.fJD);
        }

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        pXmlSierialize->xml_serialize(/* "����ϵ����Ч" */g_sLangTxt_Native_RetCoeffValid.GetString(), "_Coeff", "", "number", bVal);
        pParasEx->sCondition.bCoeff = bVal;
        pXmlSierialize->xml_serialize(/* "����ϵ��" */g_sLangTxt_Gradient_ReCoefficient.GetString(), "_CoeffVal", "", "number", pParasEx->sCondition.fCoeff);
    }
    else if(stt_xml_serialize_is_register(pXmlSierialize))
    {
        bVal = 0;
		if(pParasEx->sCondition.bCoeff){	bVal = 1;	}
        pXmlSierialize->xml_serialize(/* "����ϵ����Ч" */g_sLangTxt_Native_RetCoeffValid.GetString(), "_Coeff", "", "number", bVal);
        pXmlSierialize->xml_serialize(/* "����ϵ��" */g_sLangTxt_Gradient_ReCoefficient.GetString(), "_CoeffVal", "", "number", pParasEx->sCondition.fCoeff);
    }

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        pXmlSierialize->xml_serialize(/* "�о��߼�" */g_sLangTxt_Native_criteria_logic.GetString(), "_LogicOrAnd", "��", "number", bVal);
        pParasEx->sCondition.bLogicOr = bVal;
    }
    else if(stt_xml_serialize_is_register(pXmlSierialize))
    {
        bVal = 0;
		if(pParasEx->sCondition.bLogicOr){		bVal = 1;	}
        pXmlSierialize->xml_serialize(/* "�о��߼�" */g_sLangTxt_Native_criteria_logic.GetString(), "_LogicOrAnd", "��", "number", bVal);
    }
#endif
    
}
