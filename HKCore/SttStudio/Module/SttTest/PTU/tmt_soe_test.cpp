#include "stdafx.h"
#include "tmt_soe_test.h"
#include "../../../../Module/API/StringApi.h"

void stt_init_paras(tmt_SoeParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_SoeParas));
	pParas->init();
}

void stt_init_results(tmt_SoeResult *pResults)
{
	memset(&pResults, 0, sizeof(tmt_SoeResult));
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

void stt_xml_serialize(tmt_SoeState &pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("����ֵ","BoutState","","number",pParas.val);
	pXmlSierialize->xml_serialize("����ʱ��","KeepTime","","number",pParas.time);
}

void stt_xml_serialize(tmt_SoeParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("����ģʽ","Mode","","number",pParas->m_nMode);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣�ʱ��", "GpsH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣��֣�", "GpsM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣��룩", "GpsS"," ","number",pParas->m_tGps.nSeconds);

	CString strName,strID,strTmp;
	CString str1 = _T("����");
	for(int nIndex = 0;nIndex<MAX_PARACOUNT_BINARY;nIndex++)
	{
//		strName.Format("����%d",(nIndex+1));
		strTmp.Format(_T("%d"),nIndex+1);
		strName = str1 + strTmp;

		strID.Format("Bout%d",(nIndex+1));

		CSttXmlSerializeBase *pBoutSerialize =pXmlSierialize->xml_serialize(strName.GetString()/*strName.toUtf8().data()*/,strID.GetString(), "BOUT", stt_ParaGroupKey());

		if (pBoutSerialize == NULL)
		{
			continue;
		}
		pBoutSerialize->xml_serialize("�Ƿ�����","isValid","","number",pParas->m_binOut[nIndex].isValid);
		pBoutSerialize->xml_serialize("��λ����","count","","number",pParas->m_binOut[nIndex].cnt);

		pBoutSerialize->xml_serialize("ʵ��ǰ�Ͽ�����ʱ��","KeepTime0","","number",pParas->m_binOut[nIndex].otmt_SoeState[0].time);
		pBoutSerialize->xml_serialize("ʵ���бպϳ���ʱ��","KeepTime1","","number",pParas->m_binOut[nIndex].otmt_SoeState[1].time);
		pBoutSerialize->xml_serialize("ʵ���жϿ�����ʱ��","KeepTime2","","number",pParas->m_binOut[nIndex].otmt_SoeState[2].time);
	}
}

void stt_xml_serialize(tmt_SoeResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("�������","TripFlag","","number", pResults->m_nTripFlag);
	pXmlSierialize->xml_serialize("����ʱ��","TripTime","s","number", pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("����ֵ","ActValue","s","number", pResults->m_fActValue);
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_SoeTest()
{
	tmt_SoeTest oSoeTest;
	oSoeTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
//	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oSoeTest.m_oSoeParas, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("SoeTestDemo.xml");
//  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
