#include "stdafx.h"
#include "tmt_soe_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

void stt_init_paras(tmt_SoeParas *pParas)
{
    pParas->init();
}

void stt_init_results(tmt_SoeResult *pResults)
{
    pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///

void stt_xml_serialize(tmt_SoeParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	CString strSelID,strSelName;
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ģʽ(0-��������,1-�ȴ�GPS)","Mode","","number",pParas->m_nMode);
	pXmlSierialize->xml_serialize("Ӳ��ѡ��(0-����8������,1-��չ���)","Select","","number",pParas->m_nSelect);
	pXmlSierialize->xml_serialize("���붯��(0-����¼,1-��¼)","BiAct","","number",pParas->m_nBiAct);
	pXmlSierialize->xml_serialize("ʵ��������ʱ��(s)","HoldTime","","number",pParas->m_fHoldTime);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣�ʱ��", "GpsH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣��֣�", "GpsM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣��룩", "GpsS"," ","number",pParas->m_tGps.nSeconds);
	pXmlSierialize->xml_serialize("���Դ������Σ�", "TestCount", " ", "number", pParas->m_nTestCount);
	pXmlSierialize->xml_serialize("���", "Interval", " ", "number", pParas->m_nInterval);
	pXmlSierialize->xml_serialize("�ջ�����", "LoopTest", " ", "number", pParas->m_nLoopTest);
	pXmlSierialize->xml_serialize("SOE�ֱ���", "SoeResolution", " ", "number", pParas->m_nSoeResolution);
	pXmlSierialize->xml_serialize("���·��", "dataset-path", " ", "string", pParas->m_strDataset_path);

	for(int nIndex = 0;nIndex<g_nBoutCount;nIndex++)
	{
		strSelName.Format("ѡ����Զ���%d",nIndex+1);
		strSelID.Format("SelTestObject%d",nIndex);
		pXmlSierialize->xml_serialize(strSelName.GetString(),strSelID.GetString(), " ", "string", pParas->m_strSelTestObject[nIndex]);
	}
#else
  pXmlSierialize->xml_serialize(/* "����ģʽ(0-��������,1-�ȴ�GPS)" */ g_sLangTxt_Native_TrigModes.GetString(), "Mode", "", "number", pParas->m_nMode);
  pXmlSierialize->xml_serialize(/* "Ӳ��ѡ��(0-����8������,1-��չ���)" */ g_sLangTxt_Native_HwSelect.GetString(), "Select", "", "number", pParas->m_nSelect);
  pXmlSierialize->xml_serialize(/* "���붯��(0-����¼,1-��¼)" */ g_sLangTxt_Native_InAction.GetString(), "BiAct", "", "number", pParas->m_nBiAct);
  pXmlSierialize->xml_serialize(/* "ʵ��������ʱ��(s)" */ g_sLangTxt_Native_TotalTime.GetString(), "HoldTime", "", "number", pParas->m_fHoldTime);
  pXmlSierialize->xml_serialize(/* "GPS����ʱ�̣�ʱ��" */ g_sLangTxt_Native_GPSTriggerHour.GetString(), "GpsH", " ", "number", pParas->m_tGps.nHour);
  pXmlSierialize->xml_serialize(/* "GPS����ʱ�̣��֣�" */ g_sLangTxt_Native_GPSTriggerMinute.GetString(), "GpsM", " ", "number", pParas->m_tGps.nMinutes);
  pXmlSierialize->xml_serialize(/* "GPS����ʱ�̣��룩" */ g_sLangTxt_Native_GPSTriggerSecond.GetString(), "GpsS", " ", "number", pParas->m_tGps.nSeconds);
  pXmlSierialize->xml_serialize("���Դ���(��)", "TestCount", " ", "number", pParas->m_nTestCount);
  pXmlSierialize->xml_serialize("���", "Interval", " ", "number", pParas->m_nInterval);
  pXmlSierialize->xml_serialize("�ջ�����", "LoopTest", " ", "number", pParas->m_nLoopTest);
  pXmlSierialize->xml_serialize("SOE�ֱ���", "SoeResolution", " ", "number", pParas->m_nSoeResolution);
  pXmlSierialize->xml_serialize("���·��", "dataset-path", " ", "string", pParas->m_strDataset_path);

  for(int nIndex = 0;nIndex<g_nBoutCount;nIndex++)
  {
	  strSelName.Format("ѡ����Զ���%d",nIndex+1);
	  strSelID.Format("SelTestObject%d",nIndex);
	  pXmlSierialize->xml_serialize(strSelName.GetString(),strSelID.GetString(), " ", "string", pParas->m_strSelTestObject[nIndex]);
  }
#endif

    CString strName,strID,strTemp;
#ifdef NOT_USE_XLANGUAGE
	CString str1 = _T("����");
#else
  CString str1 = g_sLangTxt_Native_BoutX;
#endif
    for(int nIndex = 0;nIndex<g_nBoutCount;nIndex++)
    {
		strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp;
		strID.Format("Bout%d",(nIndex+1));

		CSttXmlSerializeBase *pBoutSerialize =pXmlSierialize->xml_serialize(strName.GetString(),strID.GetString(), "BOUT", stt_ParaGroupKey());

		if (pBoutSerialize == NULL)
        {
            continue;
        }
#ifdef NOT_USE_XLANGUAGE
		pBoutSerialize->xml_serialize("�Ƿ�����","isValid","","number",pParas->m_binOut[nIndex].isValid);
		pBoutSerialize->xml_serialize("��λ����","count","","number",pParas->m_binOut[nIndex].cnt);

		pBoutSerialize->xml_serialize("ʵ��ǰ״ֵ̬","PreInitStateValue","","number",pParas->m_binOut[nIndex].otmt_SoeState[0].val);
		//pBoutSerialize->xml_serialize("ʵ���г�ʼ״ֵ̬","InitStateValue","","number",pParas->m_binOut[nIndex].otmt_SoeState[1].val);
		pBoutSerialize->xml_serialize("ʵ��ǰ�Ͽ�����ʱ��(ms)","KeepTime0","","number",pParas->m_binOut[nIndex].otmt_SoeState[0].time);
		pBoutSerialize->xml_serialize("ʵ���бպϳ���ʱ��(ms)","KeepTime1","","number",pParas->m_binOut[nIndex].otmt_SoeState[1].time);
		pBoutSerialize->xml_serialize("ʵ���жϿ�����ʱ��(ms)","KeepTime2","","number",pParas->m_binOut[nIndex].otmt_SoeState[2].time);
		pBoutSerialize->xml_serialize("���Զ���","TestObject","","string",pParas->m_binOut[nIndex].m_strTestObject);
#else
    pBoutSerialize->xml_serialize(/* "�Ƿ�����" */ g_sLangTxt_Native_IsEnabled.GetString(), "isValid", "", "number", pParas->m_binOut[nIndex].isValid);
    pBoutSerialize->xml_serialize(/* "��λ����" */ g_sLangTxt_Native_ShiftCount.GetString(), "count", "", "number", pParas->m_binOut[nIndex].cnt);

    pBoutSerialize->xml_serialize(/* "ʵ��ǰ״ֵ̬" */ g_sLangTxt_Native_PreState.GetString(), "PreInitStateValue", "", "number", pParas->m_binOut[nIndex].otmt_SoeState[0].val);
    //pBoutSerialize->xml_serialize(/* "ʵ���г�ʼ״ֵ̬" */ g_sLangTxt_Native_InitState.GetString(), "InitStateValue", "", "number", pParas->m_binOut[nIndex].otmt_SoeState[1].val);
    pBoutSerialize->xml_serialize(/* "ʵ��ǰ�Ͽ�����ʱ��(ms)" */ g_sLangTxt_Native_PreCutDur.GetString(), "KeepTime0", "", "number", pParas->m_binOut[nIndex].otmt_SoeState[0].time);
    pBoutSerialize->xml_serialize(/* "ʵ���бպϳ���ʱ��(ms)" */ g_sLangTxt_Native_CloseDur.GetString(), "KeepTime1", "", "number", pParas->m_binOut[nIndex].otmt_SoeState[1].time);
    pBoutSerialize->xml_serialize(/* "ʵ���жϿ�����ʱ��(ms)" */ g_sLangTxt_Native_BreakDur.GetString(), "KeepTime2", "", "number", pParas->m_binOut[nIndex].otmt_SoeState[2].time);
	pBoutSerialize->xml_serialize("���Զ���","TestObject","","string",pParas->m_binOut[nIndex].m_strTestObject);
#endif

	}
#ifdef NOT_USE_XLANGUAGE
    str1 = _T("��չ����");
#else
  str1 = g_sLangTxt_Native_BoutEx;
#endif

    for(int nIndex = 0; nIndex < g_nBoutExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
    {
		strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp;
		strID.Format("BoutEx%d",(nIndex+1));

		CSttXmlSerializeBase *pBoutSerialize =pXmlSierialize->xml_serialize(strName.GetString(),strID.GetString(), "BOUTEX", stt_ParaGroupKey());

		if (pBoutSerialize == NULL)
        {
            continue;
        }
#ifdef NOT_USE_XLANGUAGE
		pBoutSerialize->xml_serialize("�Ƿ�����","isValid","","number",pParas->m_binOutEx[nIndex].isValid);
		pBoutSerialize->xml_serialize("��λ����","count","","number",pParas->m_binOutEx[nIndex].cnt);

		pBoutSerialize->xml_serialize("ʵ��ǰ�Ͽ�����ʱ��(ms)","KeepTime0","","number",pParas->m_binOutEx[nIndex].otmt_SoeState[0].time);
		pBoutSerialize->xml_serialize("ʵ���бպϳ���ʱ��(ms)","KeepTime1","","number",pParas->m_binOutEx[nIndex].otmt_SoeState[1].time);
		pBoutSerialize->xml_serialize("ʵ���жϿ�����ʱ��(ms)","KeepTime2","","number",pParas->m_binOutEx[nIndex].otmt_SoeState[2].time);
#else
    pBoutSerialize->xml_serialize(/* "�Ƿ�����" */ g_sLangTxt_Native_IsEnabled.GetString(), "isValid", "", "number", pParas->m_binOutEx[nIndex].isValid);
    pBoutSerialize->xml_serialize(/* "��λ����" */ g_sLangTxt_Native_ShiftCount.GetString(), "count", "", "number", pParas->m_binOutEx[nIndex].cnt);

    pBoutSerialize->xml_serialize(/* "ʵ��ǰ�Ͽ�����ʱ��(ms)" */ g_sLangTxt_Native_PreCutDur.GetString(), "KeepTime0", "", "number", pParas->m_binOutEx[nIndex].otmt_SoeState[0].time);
    pBoutSerialize->xml_serialize(/* "ʵ���бպϳ���ʱ��(ms)" */ g_sLangTxt_Native_CloseDur.GetString(), "KeepTime1", "", "number", pParas->m_binOutEx[nIndex].otmt_SoeState[1].time);
    pBoutSerialize->xml_serialize(/* "ʵ���жϿ�����ʱ��(ms)" */ g_sLangTxt_Native_BreakDur.GetString(), "KeepTime2", "", "number", pParas->m_binOutEx[nIndex].otmt_SoeState[2].time);
#endif
    }
}

void stt_xml_serialize_act_rcd(tmt_SoeResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//������¼,���64��,����ʵ�ʶ������,�����ܵĶ�����Ϣ
{
    CSttXmlSerializeBase *pXmlActRcddata = pXmlSierialize->xml_serialize("ActRcd", "ActRcd", "ActRcd", stt_ParaGroupKey());

	if (pXmlActRcddata == NULL)
    {
        return;
    }

	CString strName,strID,strTemp,strTmp2;
#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("����");
    CString str2 = _T("��");
    CString str3 = _T("�ζ���ʱ��");
#else
  CString str1 = g_sLangTxt_Native_BinX;
  CString str2 = g_sLangTxt_Native_Number;
  CString str3 = g_sLangTxt_Native_NActionTime;
#endif

    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
		strTemp.Format(_T("%d"),nIndex+1);

		for (int nIndexAct = 0;((nIndexAct<BIBO_ACTCOUNT)&&(nIndexAct<pResults->m_nrBinSwitchCount[nIndex]));nIndexAct++)
        {
			strTmp2.Format(_T("%d"),nIndexAct+1);
            strName = str1 + strTemp + str2 + strTmp2 + str3;
			strID.Format("Bin%dActCount%d",(nIndex+1),(nIndexAct+1));
			pXmlActRcddata->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResults->m_frTimeBinAct[nIndex][nIndexAct]);
        }
    }
#ifdef NOT_USE_XLANGUAGE
    str1 = _T("����");
#else
  str1 = g_sLangTxt_Native_BoutX;
#endif
    for(int nIndex = 0; nIndex < MAX_BINARYOUT_COUNT && nIndex < g_nBoutCount; nIndex++)
    {
		strTemp.Format(_T("%d"),nIndex+1);

		for (int nIndexAct = 0;((nIndexAct<BIBO_ACTCOUNT)&&(nIndexAct<pResults->m_nrBoutSwitchCount[nIndex]));nIndexAct++)
        {
			strTmp2.Format(_T("%d"),nIndexAct+1);
            strName = str1 + strTemp + str2 + strTmp2 + str3;
			strID.Format("Bout%dActCount%d",(nIndex+1),(nIndexAct+1));
			pXmlActRcddata->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResults->m_frTimeBoutAct[nIndex][nIndexAct]);
        }
    }

	if (g_nBinExCount>0||g_nBoutExCount>0)
    {
        CSttXmlSerializeBase *pXmlActRcdExdata = pXmlSierialize->xml_serialize("ActRcdEx", "ActRcdEx", "ActRcdEx", stt_ParaGroupKey());

		if (pXmlActRcdExdata == NULL)
        {
            return;
        }

        str1 = _T("����");

        for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
        {
#ifdef NOT_USE_XLANGUAGE
			strTemp.Format(_T("��չ%d"),nIndex+1);
#else
      strTemp.Format(g_sLangTxt_Native_extend, nIndex + 1);
#endif
			for (int nIndexAct = 0;((nIndexAct<BIBO_ACTCOUNT)&&(nIndexAct<pResults->m_nrBinExSwitchCount[nIndex]));nIndexAct++)
            {
				strTmp2.Format(_T("%d"),nIndexAct+1);
                strName = str1 + strTemp + str2 + strTmp2 + str3;
				strID.Format("BinEx%dActCount%d",(nIndex+1),(nIndexAct+1));
				pXmlActRcdExdata->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResults->m_frTimeBinExAct[nIndex][nIndexAct]);
            }
        }

#ifdef NOT_USE_XLANGUAGE
        str1 = _T("����");
#else
    str1 = g_sLangTxt_Native_BoutX;
#endif
        for(int nIndex = 0; nIndex < g_nBoutExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
        {
#ifdef NOT_USE_XLANGUAGE
			strTemp.Format(_T("��չ%d"),nIndex+1);
#else
      strTemp.Format(g_sLangTxt_Native_extend, nIndex + 1);
#endif

			for (int nIndexAct = 0;((nIndexAct<BIBO_ACTCOUNT)&&(nIndexAct<pResults->m_nrBoutExSwitchCount[nIndex]));nIndexAct++)
            {
				strTmp2.Format(_T("%d"),nIndexAct+1);
                strName = str1 + strTemp + str2 + strTmp2 + str3;
				strID.Format("BoutEx%dActCount%d",(nIndex+1),(nIndexAct+1));
				pXmlActRcdExdata->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResults->m_frTimeBoutExAct[nIndex][nIndexAct]);
            }
        }
    }
}

void stt_xml_serialize(tmt_SoeResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	CString strName,strID,strTemp;
#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("����");
    CString str2 = _T("���״̬");
#else
  CString str1 = g_sLangTxt_Native_BinX;
  CString str2 = g_sLangTxt_Native_result_status;
#endif

    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
		strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp + str2;

		strID.Format("StateBin%d",(nIndex+1));
		pXmlSierialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResults->m_nrBinSwitchCount[nIndex]);
    }

	if (g_nBinExCount>0)
    {
        CSttXmlSerializeBase *pXmlStateBinEx = pXmlSierialize->xml_serialize("StateBinEx", "StateBinEx", "StateBinEx", stt_ParaGroupKey());

		if (pXmlStateBinEx != NULL)
        {
            for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
            {
#ifdef NOT_USE_XLANGUAGE
				strTemp.Format(_T("��չ%d"),nIndex+1);
#else
        strTemp.Format(g_sLangTxt_Native_extend, nIndex + 1);
#endif
                strName = str1 + strTemp + str2;

				strID.Format("StateBinEx%d",(nIndex+1));
				pXmlStateBinEx->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResults->m_nrBinExSwitchCount[nIndex]);
            }
        }
    }

#ifdef NOT_USE_XLANGUAGE
    str1 = _T("����");
#else
  str1 = g_sLangTxt_Native_BoutX;
#endif
    for(int nIndex = 0; nIndex < MAX_BINARYOUT_COUNT && nIndex < g_nBoutCount; nIndex++)
    {
		strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp + str2;

		strID.Format("StateBout%d",(nIndex+1));
		pXmlSierialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResults->m_nrBoutSwitchCount[nIndex]);
    }

	if (g_nBoutExCount>0)
    {
        CSttXmlSerializeBase *pXmlStateBoutEx = pXmlSierialize->xml_serialize("StateBoutEx", "StateBoutEx", "StateBoutEx", stt_ParaGroupKey());

		if (pXmlStateBoutEx != NULL)
        {
            for(int nIndex = 0; nIndex < g_nBoutExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
            {
#ifdef NOT_USE_XLANGUAGE
				strTemp.Format(_T("��չ%d"),nIndex+1);
#else
        strTemp.Format(g_sLangTxt_Native_extend, nIndex + 1);
#endif
                strName = str1 + strTemp + str2;

				strID.Format("StateBoutEx%d",(nIndex+1));
				pXmlStateBoutEx->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResults->m_nrBoutExSwitchCount[nIndex]);
            }
        }
    }

	stt_xml_serialize_act_rcd(pResults,pXmlSierialize);
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_SoeTest()
{
    tmt_SoeTest oSoeTest;
    oSoeTest.init();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeRegister(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oSoeTest.m_oSoeParas, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("SoeTestDemo.xml");
    //    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    CSttCmdDefineXmlRWKeys::g_pXmlKeys;
    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
