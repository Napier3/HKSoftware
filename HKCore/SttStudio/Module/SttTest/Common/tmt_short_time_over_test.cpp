#include "stdafx.h"
#include "tmt_short_time_over_test.h"
#include "tmt_system_config.h"


#include"../../SttCmd/SttTestCmd.h"
#include"../../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_ShortTimeOverTest()
{
	//tmt_ShortTimeOver_Test oShortTimeOverTest;
	//oShortTimeOverTest.init();
	//CSttXmlSerializeTool oSttXmlSerializeTool;
	//CSttTestCmd oSttTestCmd;
	//CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	//pMacro->GetParas();
	//pMacro->GetResults();
	//oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	//CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	//CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	//stt_xml_serialize(&oShortTimeOverTest.m_oShortTimeOverParas, pMacroParas);
	//CString strXMLPath;
	//strXMLPath = _P_GetConfigPath();
	//strXMLPath += ("ManualTestDemo.xml");
	////   pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	//oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

void stt_init_paras(tmt_ShortTimeOver_Paras *pParas)
{
	/*memset(&pParas, 0, sizeof(tmt_ShortTimeOver_Paras));
	pParas->init();*/
}

void stt_init_results(tmt_ShortTimeOver_Results *pResults)
{
	/*memset(&pResults, 0, sizeof(tmt_ShortTimeOver_Results));
	pResults->init();*/
}

void stt_xml_serialize(tmt_ShortTimeOver_Paras *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//stt_xml_serialize_ex(pParas->m_pParaShortTimeOver, 0, pXmlSierialize, MAX_VOLTAGE_COUNT, MAX_CURRENT_COUNT);
	stt_xml_serialize_ex2(pParas,pXmlSierialize, MAX_VOLTAGE_COUNT, MAX_CURRENT_COUNT);
}

void stt_xml_serialize(tmt_ShortTimeOver_Results *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	
}



//CSttXmlSerializeBase *stt_xml_serialize(tmt_ShortTimeOver_Test *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum)
//{
//	CSttXmlSerializeBase *pXmlParas = pXmlSierialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());
//
//	if(pXmlParas  != NULL)
//	{
//		stt_xml_serialize(&pParas->m_oShortTimeOverParas, pXmlParas, nVolRsNum, nCurRsNum);
//	}
//
//	CSttXmlSerializeBase *pXmlResults = pXmlSierialize->xml_serialize("results", "results", "results", stt_ResultsKey());
//
//	if(pXmlResults  != NULL)
//	{
//		stt_xml_serialize(&pParas->m_oShortTimeOverParas, pXmlResults);
//	}
//
//	return pXmlParas;
//}

void stt_xml_serialize(tmt_Channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pChannelXmlSerializeBase =pXmlSierialize->xml_serialize(pszID, pszID, "channel", stt_ParaGroupKey());

	if (pChannelXmlSerializeBase == NULL)
	{
			return;
	}


	pChannelXmlSerializeBase->xml_serialize("幅值", "mag", "", "float", pChannel->Harm[1].fAmp);
	pChannelXmlSerializeBase->xml_serialize("相位", "ang", "", "float",  pChannel->Harm[1].fAngle);
	pChannelXmlSerializeBase->xml_serialize("频率", "freq", "", "float", pChannel->Harm[1].fFreq);
}

void stt_xml_serialize_ex(tmt_ShortTimeOver_Para &oPara, long nIndex, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum)
{

	//CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("ShortTimeOver", "ShortTimeOver", "ShortTimeOver", stt_ParaGroupKey());
	CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("状态", "state", nIndex, "State", stt_ParaGroupKey());

	//pStateSerialize->xml_serialize("输出时间", "LastT", "s", "number", oStatePara.m_fTimeState);
	pStateSerialize->xml_serialize("施加次数", "InflictCount", "", "number", oPara.m_nInflictCount);
	pStateSerialize->xml_serialize("单次施加时间", "OnceInflictTime", "s", "number", oPara.m_fOnceInflictTime);
	pStateSerialize->xml_serialize("相邻施加时间间隔", "IntervalTime", "s", "number", oPara.m_fIntervalTime);

	//新版序列化,U1~U18,i1~i18
	CString strID;
	//	int nIDCnt  =  (DIGITAL_CHANNEL_MAX/2)  +  8;// mym 2021-6-24 加了个 8

	for(int nIndex=0;nIndex<nVolRsNum;nIndex++)
	{
		strID.Format(_T("U%d"),nIndex+1);
		stt_xml_serialize(&oPara.m_uiVOL[nIndex], strID.GetString(),pStateSerialize);
	}

	for(int nIndex=0;nIndex<nCurRsNum;nIndex++)
	{
		strID.Format(_T("I%d"),nIndex+1);
		stt_xml_serialize(&oPara.m_uiCUR[nIndex], strID.GetString(),pStateSerialize);
	}
}

void stt_xml_serialize_ex2(tmt_ShortTimeOver_Paras *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum)
{

	pXmlSierialize->xml_serialize("状态数","StateCount","","number",pParas->m_nStateNumbers);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pParas->init(pParas->m_nStateNumbers);
	}
	
	long nIndex = 0;
	for (int i=0; i<pParas->m_nStateNumbers; i++)
	{
		
		stt_xml_serialize_ex(pParas->m_pParaShortTimeOver[i], nIndex, pXmlSierialize,nVolRsNum,nCurRsNum);
		nIndex++;
	}
}


