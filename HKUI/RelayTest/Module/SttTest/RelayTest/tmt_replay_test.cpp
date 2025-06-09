#include "stdafx.h"
#include "tmt_replay_test.h"

void stt_xml_serialize(tmt_ReplayTest *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("����Ƶ��","SampleFreq","Hz","number",pParas->m_nSampleFreq);

	int i = 0;
	char chName[MAX_PATH],chID[MAX_PATH];
	for (i=0; i<MAX_MODULE_COUNT; i++)
	{
		sprintf(chName, "ģ��%d����ط�", i+1);
		sprintf(chID, "SelectModule%d", i);
		pXmlSierialize->xml_serialize(chName,chID,"","number",pParas->m_nModuleSel[i]);
	}

	pXmlSierialize->xml_serialize("��������","TriggerType","","number",pParas->m_nTripType);
	pXmlSierialize->xml_serialize("����ʱ��(��)","TrigTimeS","","number",pParas->m_nTrigTimeS);
	pXmlSierialize->xml_serialize("����ʱ��(����)","TrigTimeNS","","number",pParas->m_nTrigTimeNS);
	pXmlSierialize->xml_serialize("ѭ������","LoopCnt","","number",pParas->m_nStartLoopCount);
	pXmlSierialize->xml_serialize("�ܲ���","CycleNum","","number",pParas->m_nStartCycleNum);
	pXmlSierialize->xml_serialize("������ģʽ","TrigAfterMode","","number",pParas->m_nTrigAfterMode);
	pXmlSierialize->xml_serialize("�����߼�", "AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);

	char pszBInName[MAX_BINARYIN_COUNT]="ABCDEFGH";
	for(i=0; i<MAX_BINARYIN_COUNT; i++)
	{
		sprintf(chName, "����%cѡ��", pszBInName[i]);
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
