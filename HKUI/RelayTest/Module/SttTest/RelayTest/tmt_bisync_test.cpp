#include "stdafx.h"
#include "tmt_bisync_test.h"


void stt_init_paras(tmt_BiSyncTest *pPara)
{
	pPara->init();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///
///
void stt_xml_serialize(tmt_BiSyncPara *pPara, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("状态持续时间","OutputTime","s","number",pPara->m_nOutputTime);
//	char pszBInName[20]="ABCDEFGH";
//	CString strName,strID;
//	for(int nIndex = 0;nIndex<MAX_PARACOUNT_BINARY;nIndex++)
//	{
//		strName.Format("开入%c选择",pszBInName[nIndex]);
//		strID.Format("BIn%c",pszBInName[nIndex]);
//		pXmlSierialize->xml_serialize(strName.GetString(),strID.GetString(),"","BOOL",pPara->m_binIn[nIndex].nSelect);
//	}
}


//void stt_xml_serialize_result(tmt_BiSyncTest *pTmt, CSttXmlSerializeBase *pXmlSierialize)
//{
//	pXmlSierialize->xml_serialize("结果数","ResultCount","","number",pTmt->m_oBiSyncPara.m_nStateNumbers);
//	for(int nIndex=0;nIndex<pTmt->m_oBiSyncPara.m_nStateNumbers;nIndex++)
//	{
//		CString strName,strID;
//		strName.Format("状态%d结果",nIndex);
//		strID.Format("Result%d",nIndex);
//		CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize(strName.GetString(),strID.GetString(),"RESULT",stt_ParaGroupKey());
//		if (pStateSerialize == NULL)
//		{
//			return;
//		}
//		pStateSerialize->xml_serialize("秒值","Sec","","number",pTmt->m_oBiSyncResults.m_resultState[nIndex].m_TimeSec);
//		pStateSerialize->xml_serialize("纳秒值","NSec","","number",pTmt->m_oBiSyncResults.m_resultState[nIndex].m_TimeNSec);
//	}
//}

#include"../../SttCmd/SttTestCmd.h"
#include"tmt_state_test.h"
#include"../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_BiSyncTest()
{
	tmt_BiSyncTest oBiSyncTest;
	oBiSyncTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	//pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	//CSttXmlSerializeBase *pMacroResults = oSttXmlSerializeTool.GetMacroResults();
	stt_xml_serialize(&oBiSyncTest.m_oBiSyncPara, pMacroParas);
	//stt_xml_serialize_result(&oBiSyncTest, pMacroResults);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("BiSyncTestDemo.xml");
//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
