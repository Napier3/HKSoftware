#include "stdafx.h"
#include "tmt_binary_state_test.h"
#include "../tmt_system_config.h"
#include "../../../../../Module/API/StringApi.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

long g_nBinaryStateTestMode = 0;//0-�����ն�ģʽ��1-���𿪹����ϻ�����ģʽ

void stt_xml_serialize_BinaryState(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("״̬", "state", nIndex, "State", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pStateSerialize = pXmlSierialize->xml_serialize(/* "״̬" */ g_sLangTxt_Status.GetString(), "state", nIndex, "State", stt_ParaGroupKey());
#endif

    if(pStateSerialize == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pStateSerialize->xml_serialize("������ʽ", "EndMode", "", "StateEndMode_PSUAuto", oStatePara.m_nTriggerCondition);
    pStateSerialize->xml_serialize("���ʱ��", "LastT", "s", "number", oStatePara.m_fTimeState);
    pStateSerialize->xml_serialize("�����󱣳�ʱ��", "EndDelayT", "s", "number", oStatePara.m_fTimeAfterTrigger);
    pStateSerialize->xml_serialize("����������ʱ��", "OutputHoldT", "s", "number", oStatePara.m_fOutputHoldTime);
    pStateSerialize->xml_serialize("GPS����ʱ�̣�ʱ��", "GpsH", " ", "number", oStatePara.m_tGps.nHour);
    pStateSerialize->xml_serialize("GPS����ʱ�̣��֣�", "GpsM", " ", "number", oStatePara.m_tGps.nMinutes);
    pStateSerialize->xml_serialize("GPS����ʱ�̣��룩", "GpsS", " ", "number", oStatePara.m_tGps.nSeconds);
#else
  pStateSerialize->xml_serialize(/* "������ʽ" */ g_sLangTxt_Native_TrigMode.GetString(), "EndMode", "", "StateEndMode_PSUAuto", oStatePara.m_nTriggerCondition);
  pStateSerialize->xml_serialize(/* "���ʱ��" */ g_sLangTxt_Native_OutTime.GetString(), "LastT", "s", "number", oStatePara.m_fTimeState);
  pStateSerialize->xml_serialize(/* "�����󱣳�ʱ��" */ g_sLangTxt_Native_TrigHoldTime.GetString(), "EndDelayT", "s", "number", oStatePara.m_fTimeAfterTrigger);
  pStateSerialize->xml_serialize(/* "����������ʱ��" */ g_sLangTxt_Native_OutHoldTime.GetString(), "OutputHoldT", "s", "number", oStatePara.m_fOutputHoldTime);

  pStateSerialize->xml_serialize(/* "GPS����ʱ�̣�ʱ��" */ g_sLangTxt_Native_GPSTriggerHour.GetString(), "GpsH", " ", "number", oStatePara.m_tGps.nHour);
  pStateSerialize->xml_serialize(/* "GPS����ʱ�̣��֣�" */ g_sLangTxt_Native_GPSTriggerMinute.GetString(), "GpsM", " ", "number", oStatePara.m_tGps.nMinutes);
  pStateSerialize->xml_serialize(/* "GPS����ʱ�̣��룩" */ g_sLangTxt_Native_GPSTriggerSecond.GetString(), "GpsS", " ", "number", oStatePara.m_tGps.nSeconds);
#endif

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		stt_xml_serialize(&oStatePara.m_oGoosePub[0],pStateSerialize);
	}

    stt_xml_serialize_binary_in(oStatePara, pStateSerialize);
	stt_xml_serialize_Exbinary_in(oStatePara.m_binInEx,pStateSerialize);
    stt_xml_serialize_binary_out(oStatePara, pStateSerialize);
	stt_xml_serialize_Exbinary_out(oStatePara.m_binOutEx,pStateSerialize);
}

void stt_xml_serialize_BinaryStates(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_common(pParas, pXmlSierialize);
	pXmlSierialize->xml_serialize("����ģʽ(0-�����ն�ģʽ��1-���𿪹����ϻ�����ģʽ)", "BinaryStateTestMode", "", "number", g_nBinaryStateTestMode);

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("״̬��","StateCount","","number",pParas->m_nStateNumbers);
#else
  pXmlSierialize->xml_serialize(/* "״̬��" */ g_sLangTxt_Native_StateNum.GetString(), "StateCount", "", "number", pParas->m_nStateNumbers);
#endif

	long nIndex = 0;

	for (nIndex=0; nIndex<pParas->m_nStateNumbers; nIndex++)
    {
#ifdef _PSX_QT_LINUX_
        pParas->m_paraState[nIndex].init();
#endif
		stt_xml_serialize_BinaryState(pParas->m_paraState[nIndex], nIndex, pXmlSierialize);
    }
}

void stt_xml_serialize_BinaryState_act_rcd(tmt_BinaryStateResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//������¼,���64��,����ʵ�ʶ������,�����ܵĶ�����Ϣ
{
    CSttXmlSerializeBase *pXmlActRcddata = pXmlSierialize->xml_serialize("ActRcd", "ActRcd", "ActRcd", stt_ParaGroupKey());

    if(pXmlActRcddata == NULL)
    {
        return;
    }

	CString strName,strID,strTemp,strTmp2;
#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("����");
    CString str1Ex = _T("������չ");
    CString str2 = _T("��");
    CString str3 = _T("�ζ���ʱ��");
	int nCnt = get_xml_serialize_binary_count(pXmlSierialize);
#else
	CString str1 = g_sLangTxt_Native_BinX;
	CString str1Ex = g_sLangTxt_Native_InputExpand;
	CString str2 = g_sLangTxt_Native_Number;
	CString str3 = g_sLangTxt_Native_NActionTime;
	int nCnt = g_nBinCount;

	if (nCnt> MAX_BINARYIN_COUNT)
	{
		nCnt = MAX_BINARYIN_COUNT;
	}
#endif

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);

        for(int nIndexAct = 0; ((nIndexAct < 64) && (nIndexAct < pResults->m_nrBinSwitchCount[nIndex])); nIndexAct++)
        {
            strTmp2.Format(_T("%d"), nIndexAct + 1);
            strName = str1 + strTemp + str2 + strTmp2 + str3;

            if(nIndexAct == 0)
            {
                strID.Format("Bin%dActValue1", (nIndex + 1));
                pXmlActRcddata->xml_serialize("", strID.GetString(), "", "long", pResults->m_nBinFirstChgState[nIndex]);
            }

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
            strTemp.Format(_T("%d"), nIndex + 1);

            for(int nIndexAct = 0; ((nIndexAct < 64) && (nIndexAct < pResults->m_nrBinExSwitchCount[nIndex])); nIndexAct++)
            {
                strTmp2.Format(_T("%d"), nIndexAct + 1);
                strName = str1Ex + strTemp + str2 + strTmp2 + str3;
                strID.Format("BinEx%dActCount%d", (nIndex + 1), (nIndexAct + 1));
                pXmlActRcdExdata->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_frTimeBinExAct[nIndex][nIndexAct]);
            }
        }
    }
}

void stt_xml_serialize(tmt_BinaryStateResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    CString strID;
    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(int i = 0; i < nCnt; i++)
    {
        strID.Format("Bin%dActTotalCount", (i + 1));
        pXmlSierialize->xml_serialize("", strID.GetString(), "", "long", pResults->m_nrBinSwitchTotalCount[i]);
    }

    for (int nIndex=0; nIndex<pResults->m_nresultCount; nIndex++)
    {
#ifdef NOT_USE_XLANGUAGE
        CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("״̬", "state", "State", stt_ParaGroupKey());
#else
    CSttXmlSerializeBase *pStateSerialize = pXmlSierialize->xml_serialize(/* "״̬" */ g_sLangTxt_Status.GetString(), "state", "State", stt_ParaGroupKey());
#endif
        if (pStateSerialize == NULL)
        {
            return;
        }
#ifdef NOT_USE_XLANGUAGE
        pStateSerialize->xml_serialize("ѭ�����","LoopIndx","","number",pResults->m_resultState[nIndex].m_nCurLoopIndx);
        pStateSerialize->xml_serialize("״̬���","StateIndex","","number",pResults->m_resultState[nIndex].m_nCurStateIndx);
#else
    pStateSerialize->xml_serialize(/* "ѭ�����" */ g_sLangTxt_Native_LoopNum.GetString(), "LoopIndx", "", "number", pResults->m_resultState[nIndex].m_nCurLoopIndx);
    pStateSerialize->xml_serialize(/* "״̬���" */ g_sLangTxt_Native_StateNums.GetString(), "StateIndex", "", "number", pResults->m_resultState[nIndex].m_nCurStateIndx);
#endif
		stt_xml_serialize_BinaryState_act_rcd(&pResults->m_resultState[nIndex],pStateSerialize);
    }
    pResults->init();
}

#include"../../../SttCmd/SttTestCmd.h"
#include"../../../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_BinaryStateTest()
{
    tmt_BinaryStateTest oStateTest;
    oStateTest.init(10);
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oStateTest.m_oStateParas, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("BinaryStateTestDemo.xml");
    //  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

