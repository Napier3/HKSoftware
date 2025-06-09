#include "stdafx.h"
#include "tmt_pid01_test.h"
#include "../../../../Module/API/StringApi.h"
#include "qdebug.h"

void stt_init_paras(tmt_Pid01Para *pPara)
{
	memset(&pPara, 0, sizeof(tmt_Pid01Para));
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

void stt_xml_serialize(tmt_Pid01Para *pPara, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("硬件切换动作预留时间(单位秒,最小1秒最大5秒)","OutputTime","","number",pPara->m_fOutputTime);
	stt_xml_serialize_binary_out(pPara->m_binOut, pXmlSierialize);
	CString strID,strTemp;
	CString str1 = _T("PIK08_");
	for(int nIndex = 0;nIndex<2;nIndex++)
	{
		strTemp.Format("%d",nIndex+1);
		strID = str1 + strTemp;
		CSttXmlSerializeBase *pPik08Serialize =pXmlSierialize->xml_serialize(strID.GetString(),strID.GetString(), "PIK08Para", stt_ParaGroupKey());
		if (pPik08Serialize == NULL)
			continue;

		pPik08Serialize->xml_serialize("主备电源选择(0-单主,1-单备,2-主备)","U2Power","","number",pPara->m_oPik08Para[nIndex].m_nU2Power);
		pPik08Serialize->xml_serialize("电压通道模式选择(0-4路单独,1-合并到A相,2-合并到B相,3-合并到C相)","VoltMode","","number",pPara->m_oPik08Para[nIndex].m_nVoltMode);
		pPik08Serialize->xml_serialize("电流通道模式选择(0-4路单独,1-合并到A相,2-合并到B相,3-合并到C相)","CurrMode","","number",pPara->m_oPik08Para[nIndex].m_nCurrMode);
		pPik08Serialize->xml_serialize("电压间隔选择(1-S1,2-S2,3-S3,等等)","VoltBoardSel","","number",pPara->m_oPik08Para[nIndex].m_nVoltBoardSel);
		pPik08Serialize->xml_serialize("电流间隔选择(1-S1,2-S2,3-S3,等等)","CurrBoardSel","","number",pPara->m_oPik08Para[nIndex].m_nCurrBoardSel);
	}
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_Pid01Test()
{
	tmt_Pid01Test oPid01Test;
	oPid01Test.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oPid01Test.m_oPid01Para, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("Pid01TestDemo.xml");
	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
