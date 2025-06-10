#include "stdafx.h"
#include "tmt_diff_cbop_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_DiffCBOpParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DiffCBOpParas));
	pParas->init();
}

void stt_init_results(tmt_DiffCBOpResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DiffCBOpResults));
    pResults->init();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize(tmt_DiffCBOpParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��������","FaultType","","number",pParas->m_nFaultType);
	pXmlSierialize->xml_serialize("���ϵ�λ��","FaultLocation","","number",pParas->m_nFaultLocation);
	pXmlSierialize->xml_serialize("�������","ErrorType","","number",pParas->m_nErrorType);
	pXmlSierialize->xml_serialize("����(A)","Current","","number",pParas->m_fCurrent);
	pXmlSierialize->xml_serialize("Ƶ��(Hz)","Freq","","number",pParas->m_fFreq);
    pXmlSierialize->xml_serialize("��һ���ѹ��̬���ֵ","Vg1","V","number",pParas->m_fVg1);
    pXmlSierialize->xml_serialize("�ڶ����ѹ��̬���ֵ","Vg2","V","number",pParas->m_fVg2);

    pXmlSierialize->xml_serialize("��ѹ�������", "SN", "", "number", pParas->m_fSN);
    pXmlSierialize->xml_serialize("����ƽ��ϵ��", "Kcal", "", "number", pParas->m_nKcal);

	pXmlSierialize->xml_serialize("��ѹ����ѹ��ƽ��ϵ��", "Kph", "","number",pParas->m_fKph);
	pXmlSierialize->xml_serialize("��ѹ����ѹ����ѹ", "Uh", "","number",pParas->m_fUh);
    pXmlSierialize->xml_serialize("��ѹ����ѹ������", "Inh", "","number",pParas->m_fInh);
    pXmlSierialize->xml_serialize("��ѹ����ѹ��CT���", "CTh", "","number",pParas->m_fCTh);

	pXmlSierialize->xml_serialize("��ѹ����ѹ��ƽ��ϵ��","Kpm","","number",pParas->m_fKpm);
	pXmlSierialize->xml_serialize("��ѹ����ѹ����ѹ", "Um", "","number",pParas->m_fUm);
    pXmlSierialize->xml_serialize("��ѹ����ѹ������", "Inm", "","number",pParas->m_fInm);
    pXmlSierialize->xml_serialize("��ѹ����ѹ��CT���","CTm","","number",pParas->m_fCTm);

    pXmlSierialize->xml_serialize("��ѹ����ѹ��ƽ��ϵ��","Kpl","","number",pParas->m_fKpl);
    pXmlSierialize->xml_serialize("��ѹ����ѹ����ѹ", "Ul", "","number",pParas->m_fUl);
    pXmlSierialize->xml_serialize("��ѹ����ѹ������", "Inl", "","number",pParas->m_fInl);
    pXmlSierialize->xml_serialize("��ѹ����ѹ��CT���","CTl","","number",pParas->m_fCTl);

	pXmlSierialize->xml_serialize("�������(S) +", "AbsErrSum", "","number",pParas->m_fAbsErrSum);
	pXmlSierialize->xml_serialize("�������(S) -", "AbsErrReduce", "","number",pParas->m_fAbsErrReduce);
	pXmlSierialize->xml_serialize("������", "RelErr", "", "number", pParas->m_fRelErr);

	pXmlSierialize->xml_serialize("׼��ʱ��", "PrepareTime", "","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("����ǰʱ��", "PreFaultTime", "","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("����ʱ��", "FaultTime", "","number",pParas->m_fFaultTime);
	pXmlSierialize->xml_serialize("����ʱ��ԣ��", "FaultTimeMargin", "","number",pParas->m_fFaultTimeMargin);
    pXmlSierialize->xml_serialize("�����󱣳�ʱ��", "ActionHoldTime", "","number",pParas->m_fActionHoldTime);
    pXmlSierialize->xml_serialize("��ѹ�����������ʽ","WindH","","DiffConnectMode",pParas->m_nWindH);
    pXmlSierialize->xml_serialize("��ѹ�����������ʽ","WindM","","DiffConnectMode",pParas->m_nWindM);
    pXmlSierialize->xml_serialize("��ѹ�����������ʽ","WindL","","DiffConnectMode",pParas->m_nWindL);
    pXmlSierialize->xml_serialize("�������������","AdoptWind","","TransHMLSel",pParas->m_nWindSide);
    pXmlSierialize->xml_serialize("�����ڲ���λУ����ʽ","PhCorrectMode","","TransPhCorrectModePnv",pParas->m_nAngleMode);
    pXmlSierialize->xml_serialize("��-�������ӵ���", "AroundClockNumHM", "","number",pParas->m_nAroundClockNumHM);
    pXmlSierialize->xml_serialize("��-�������ӵ���", "AroundClockNumHL", "", "number", pParas->m_nAroundClockNumHL);
    pXmlSierialize->xml_serialize("ƽ��ϵ������", "BalanceTerms", "","number",pParas->m_nBalanceTerms);
	pXmlSierialize->xml_serialize("CT����", "CTStarPoint", "","number",pParas->m_bCTStarPoint);
	pXmlSierialize->xml_serialize("�ƶ�����", "IbiasCal", "", "number", pParas->m_nIbiasCal);
	pXmlSierialize->xml_serialize("K1","Factor1","","number",pParas->m_fFactor1);
	pXmlSierialize->xml_serialize("K2", "Factor2", "","number",pParas->m_fFactor2);
	pXmlSierialize->xml_serialize("�������", "ComBineFeature", "","long",pParas->m_nComBineFeature);

	pXmlSierialize->xml_serialize("�ӵ�","Earthing","","number",pParas->m_nEarthing);
	pXmlSierialize->xml_serialize("��·��ģ��  S1=��ģ��,S2=ģ�� 0(0:��ģ��,1:ģ��)","CBSimulation","","",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize("��բʱ��","CBTripTime","","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize("��բʱ��","CBCloseTime","","number",pParas->m_fCBCloseTime);
	pXmlSierialize->xml_serialize("����","Coordinate","","number",pParas->m_nCoordinate);
    pXmlSierialize->xml_serialize("��׼����ѡ��", "InSel", "", "CurrentSelPnv", pParas->m_nInSel);
    pXmlSierialize->xml_serialize("��׼�����趨ֵ", "InSet", "A", "number", pParas->m_fIbase);

	pXmlSierialize->xml_serialize("����A","A","","DInputState",pParas->m_binIn[0]);
	pXmlSierialize->xml_serialize("����B","B","","DInputState",pParas->m_binIn[1]);
	pXmlSierialize->xml_serialize("����C","C","","DInputState",pParas->m_binIn[2]);
	pXmlSierialize->xml_serialize("����R","R","","DInputState",pParas->m_binIn[3]);
	pXmlSierialize->xml_serialize("����E","E","","DInputState",pParas->m_binIn[4]);
	pXmlSierialize->xml_serialize("����F","F","","DInputState",pParas->m_binIn[5]);
	pXmlSierialize->xml_serialize("����G","G","","DInputState",pParas->m_binIn[6]);
	pXmlSierialize->xml_serialize("����H","H","","DInputState",pParas->m_binIn[7]);
    pXmlSierialize->xml_serialize("�����߼�", "_AndOr", "","number",pParas->m_nBinLogic);

	pXmlSierialize->xml_serialize("��̬����1״̬","_B01","","DOutputState",pParas->m_binOut[0][0]);
	pXmlSierialize->xml_serialize("��̬����2״̬","_B02","","DOutputState",pParas->m_binOut[0][1]);
	pXmlSierialize->xml_serialize("��̬����3״̬","_B03","","DOutputState",pParas->m_binOut[0][2]);
	pXmlSierialize->xml_serialize("��̬����4״̬","_B04","","DOutputState",pParas->m_binOut[0][3]);
	pXmlSierialize->xml_serialize("��̬����5״̬","_B05","","DOutputState",pParas->m_binOut[0][4]);
	pXmlSierialize->xml_serialize("��̬����6״̬","_B06","","DOutputState",pParas->m_binOut[0][5]);
	pXmlSierialize->xml_serialize("��̬����7״̬","_B07","","DOutputState",pParas->m_binOut[0][6]);
	pXmlSierialize->xml_serialize("��̬����8״̬","_B08","","DOutputState",pParas->m_binOut[0][7]);
	pXmlSierialize->xml_serialize("����̬����1״̬","_FaultB01","","DOutputState",pParas->m_binOut[1][0]);
	pXmlSierialize->xml_serialize("����̬����2״̬","_FaultB02","","DOutputState",pParas->m_binOut[1][1]);
	pXmlSierialize->xml_serialize("����̬����3״̬","_FaultB03","","DOutputState",pParas->m_binOut[1][2]);
	pXmlSierialize->xml_serialize("����̬����4״̬","_FaultB04","","DOutputState",pParas->m_binOut[1][3]);
	pXmlSierialize->xml_serialize("����̬����5״̬","_FaultB05","","DOutputState",pParas->m_binOut[1][4]);
	pXmlSierialize->xml_serialize("����̬����6״̬","_FaultB06","","DOutputState",pParas->m_binOut[1][5]);
	pXmlSierialize->xml_serialize("����̬����7״̬","_FaultB07","","DOutputState",pParas->m_binOut[1][6]);
	pXmlSierialize->xml_serialize("����̬����8״̬","_FaultB08","","DOutputState",pParas->m_binOut[1][7]);


#else
	pXmlSierialize->xml_serialize("��������","FaultType","","number",pParas->m_nFaultType);
	pXmlSierialize->xml_serialize("�������","ErrorType","","number",pParas->m_nErrorType);
	pXmlSierialize->xml_serialize("���ϵ�λ��","FaultLocation","","number",pParas->m_nFaultLocation);
	pXmlSierialize->xml_serialize("����(A)","Current","","number",pParas->m_fCurrent);
	pXmlSierialize->xml_serialize("Ƶ��(Hz)","Freq","","number",pParas->m_fFreq);

	pXmlSierialize->xml_serialize("��ѹ����ѹ��ƽ��ϵ��", "Kph", "","number",pParas->m_fKph);
	pXmlSierialize->xml_serialize("��ѹ����ѹ����ѹ", "Uh", "","number",pParas->m_fUh);
	pXmlSierialize->xml_serialize("��ѹ����ѹ������", "TransfHvCur", "","number",pParas->m_fTransfHvCur);
	pXmlSierialize->xml_serialize("��ѹ����ѹ��CT���", "TransfHvCT", "","number",pParas->m_fTransfHvCT);
	pXmlSierialize->xml_serialize("��ѹ����ѹ������", "TransfHvKVA", "", "number", pParas->m_fTransfHvKVA);

	pXmlSierialize->xml_serialize("��ѹ����ѹ��ƽ��ϵ��","Kpm","","number",pParas->m_fKpm);
	pXmlSierialize->xml_serialize("��ѹ����ѹ����ѹ", "Um", "","number",pParas->m_fUm);
	pXmlSierialize->xml_serialize("��ѹ����ѹ������", "TransfMvCur", "","number",pParas->m_fTransfMvCur);
	pXmlSierialize->xml_serialize("��ѹ����ѹ��CT���","TransfMvCT","","number",pParas->m_fTransfMvCT);

	pXmlSierialize->xml_serialize("��ѹ����ѹ������", "Kpl", "", "number",  pParas->m_fTransfLvKpl);
	pXmlSierialize->xml_serialize("��ѹ����ѹ��ƽ��ϵ��","Ul","","number",pParas->m_fKpl);
	pXmlSierialize->xml_serialize("��ѹ����ѹ����ѹ", "TransfLvCur", "","number",pParas->m_fUl);
	pXmlSierialize->xml_serialize("��ѹ����ѹ������", "TransfLvCT", "","number",pParas->m_fTransfLvCT);

	pXmlSierialize->xml_serialize("�������(S) +", "AbsErrSum", "","number",pParas->m_fAbsErrSum);
	pXmlSierialize->xml_serialize("�������(S) -", "AbsErrReduce", "","number",pParas->m_fAbsErrReduce);
	pXmlSierialize->xml_serialize("������", "RelErr", "", "number", pParas->m_fRelErr);

	pXmlSierialize->xml_serialize("׼��ʱ��", "PrepareTime", "","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("����ǰʱ��", "PreFaultTime", "","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("����ʱ��ԣ��", "FaultTimeMargin", "","number",pParas->m_fFaultTimeMargin);
	pXmlSierialize->xml_serialize("��-�������ӵ���", "AroundClockNumHM", "","number",pParas->m_fActionHoldTime);
	pXmlSierialize->xml_serialize("��-�������ӵ���", "AroundClockNumHL", "", "number", pParas->m_nAroundClockNumHM);
	pXmlSierialize->xml_serialize("ƽ��ϵ������", "BalanceTerms", "","number",pParas->m_nAroundClockNumHL);
	pXmlSierialize->xml_serialize("CT����", "CTStarPoint", "","number",pParas->m_bCTStarPoint);
	pXmlSierialize->xml_serialize("�ƶ�����", "IbiasCal", "", "number", pParas->m_nIbiasCal);
	pXmlSierialize->xml_serialize("K1","Factor1","","number",pParas->m_fFactor1);
	pXmlSierialize->xml_serialize("K2", "Factor2", "","number",pParas->m_fFactor2);
	pXmlSierialize->xml_serialize("�������", "ComBineFeature", "","long",pParas->m_nComBineFeature);

	pXmlSierialize->xml_serialize("�ӵ�","Earthing","","number",pParas->m_nEarthing);
	pXmlSierialize->xml_serialize("��·��ģ��  S1=��ģ��,S2=ģ�� 0(0:��ģ��,1:ģ��)","CBSimulation","","",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize("��բʱ��","CBTripTime","","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize("��բʱ��","CBCloseTime","","number",pParas->m_fCBCloseTime);
	pXmlSierialize->xml_serialize("����","Coordinate","","number",pParas->m_nCoordinate);

	pXmlSierialize->xml_serialize("����A","A","","DInputState",pParas->m_binIn[0]);
	pXmlSierialize->xml_serialize("����B","B","","DInputState",pParas->m_binIn[1]);
	pXmlSierialize->xml_serialize("����C","C","","DInputState",pParas->m_binIn[2]);
	pXmlSierialize->xml_serialize("����R","R","","DInputState",pParas->m_binIn[3]);
	pXmlSierialize->xml_serialize("����E","E","","DInputState",pParas->m_binIn[4]);
	pXmlSierialize->xml_serialize("����F","F","","DInputState",pParas->m_binIn[5]);
	pXmlSierialize->xml_serialize("����G","G","","DInputState",pParas->m_binIn[6]);
	pXmlSierialize->xml_serialize("����H","H","","DInputState",pParas->m_binIn[7]);
	pXmlSierialize->xml_serialize("�����߼�", "BinLogic", "","number",pParas->m_nBinLogic);

	pXmlSierialize->xml_serialize("��̬����1״̬","_B01","","DOutputState",pParas->m_binOut[0][0]);
	pXmlSierialize->xml_serialize("��̬����2״̬","_B02","","DOutputState",pParas->m_binOut[0][1]);
	pXmlSierialize->xml_serialize("��̬����3״̬","_B03","","DOutputState",pParas->m_binOut[0][2]);
	pXmlSierialize->xml_serialize("��̬����4״̬","_B04","","DOutputState",pParas->m_binOut[0][3]);
	pXmlSierialize->xml_serialize("��̬����5״̬","_B05","","DOutputState",pParas->m_binOut[0][4]);
	pXmlSierialize->xml_serialize("��̬����6״̬","_B06","","DOutputState",pParas->m_binOut[0][5]);
	pXmlSierialize->xml_serialize("��̬����7״̬","_B07","","DOutputState",pParas->m_binOut[0][6]);
	pXmlSierialize->xml_serialize("��̬����8״̬","_B08","","DOutputState",pParas->m_binOut[0][7]);
	pXmlSierialize->xml_serialize("����̬����1״̬","_FaultB01","","DOutputState",pParas->m_binOut[1][0]);
	pXmlSierialize->xml_serialize("����̬����2״̬","_FaultB02","","DOutputState",pParas->m_binOut[1][1]);
	pXmlSierialize->xml_serialize("����̬����3״̬","_FaultB03","","DOutputState",pParas->m_binOut[1][2]);
	pXmlSierialize->xml_serialize("����̬����4״̬","_FaultB04","","DOutputState",pParas->m_binOut[1][3]);
	pXmlSierialize->xml_serialize("����̬����5״̬","_FaultB05","","DOutputState",pParas->m_binOut[1][4]);
	pXmlSierialize->xml_serialize("����̬����6״̬","_FaultB06","","DOutputState",pParas->m_binOut[1][5]);
	pXmlSierialize->xml_serialize("����̬����7״̬","_FaultB07","","DOutputState",pParas->m_binOut[1][6]);
	pXmlSierialize->xml_serialize("����̬����8״̬","_FaultB08","","DOutputState",pParas->m_binOut[1][7]);
#endif

}

void stt_xml_serialize(tmt_DiffCBOpResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("����ʱ��", "TripTime", "s", "number",pResults->m_fTripTime);
    pXmlSierialize->xml_serialize("��������","ActFlag","","number",pResults->m_nActFlag);
#else
  pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "s", "number", pResults->m_fTripTime);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
#endif
}
CSttXmlSerializeBase* stt_xml_serialize( tmt_diff_cbop_Test *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        stt_xml_serialize(&(pTests->m_oDiffProtectionParas),  pXmlParas);	//�ļ��Ķ�д
    }

    CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        stt_xml_serialize(&pTests->m_oDiffProtectionResults,  pXmlResults);
    }

    return pXmlParas;
}

#include"../../../SttCmd/SttTestCmd.h"
#include"../../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_DiffCBOp()
{
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	//stt_xml_serialize(&oReplayTest, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("ReplayTest.xml");
	pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

