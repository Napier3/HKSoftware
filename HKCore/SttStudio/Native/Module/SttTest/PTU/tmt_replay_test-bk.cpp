#include "stdafx.h"
#include "tmt_replay_test.h"

void stt_xml_serialize_module(TMT_REPLAY_MODULE *pModule, int nIndex,CSttXmlSerializeBase *pXmlSierialize)
{
	char chName[MAX_PATH],chID[MAX_PATH];
	sprintf(chName, "模块%d", nIndex+1);
	sprintf(chID, "Module%d", nIndex+1);

	CSttXmlSerializeBase *pBinSerialize =pXmlSierialize->xml_serialize(chName, chID, "Module", stt_ParaGroupKey());
	if (pBinSerialize == NULL)
	{
		return;
	}

	pBinSerialize->xml_serialize("选择","Sel","","bool",pModule->m_nSel);
	pBinSerialize->xml_serialize("Index","Index","","number",pModule->m_nIndex);
	pBinSerialize->xml_serialize("ChUseCount","ChUseCount","","number",pModule->m_nChUseCount);

	for (int i=0; i<pModule->m_nChUseCount; i++)
	{
		sprintf(chName, "Ch%dID", i+1);
		sprintf(chID, "Ch%dID", i+1);
		pBinSerialize->xml_serialize(chName,chID,"","string",pModule->m_oChMap[i].m_strChID);
	}
}

void stt_xml_serialize(tmt_ReplayTest *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("采样频率","SampleFreq","Hz","number",pParas->m_nSampleFreq);
	pXmlSierialize->xml_serialize("模块数","ModuleCount","","number",pParas->m_nModuleCount);

	int i = 0;
	char chName[MAX_PATH],chID[MAX_PATH];

	for (i=0; i<pParas->m_nModuleCount; i++)
	{
		stt_xml_serialize_module(&pParas->m_oModule[i],i,pXmlSierialize);
	}

	pXmlSierialize->xml_serialize("触发条件","TriggerType","","number",pParas->m_nTripType);
	pXmlSierialize->xml_serialize("触发时刻(秒)","TrigTimeS","","number",pParas->m_nTrigTimeS);
	pXmlSierialize->xml_serialize("触发时刻(纳秒)","TrigTimeNS","","number",pParas->m_nTrigTimeNS);
	pXmlSierialize->xml_serialize("周波数","CycleNum","","number",pParas->m_nStartCycleNum);
	pXmlSierialize->xml_serialize("触发后模式","TrigAfterMode","","number",pParas->m_nTrigAfterMode);
	pXmlSierialize->xml_serialize("开入逻辑", "AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);

	char pszBInName[MAX_BINARYIN_COUNT]="ABCDEFGH";
	for(i=0; i<MAX_BINARYIN_COUNT; i++)
	{
		sprintf(chName, "开入%c选择", pszBInName[i]);
		sprintf(chID, "BIn%c", pszBInName[i]);
		pXmlSierialize->xml_serialize(chName,chID,"","BOOL",pParas->m_binIn[i].nSelect);
	}
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_ReplayTest()
{
    tmt_ReplayTest oReplayTest;
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oReplayTest, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("ReplayTest.xml");
    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
