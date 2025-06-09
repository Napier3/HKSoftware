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
	pXmlSierialize->xml_serialize("Ӳ���л�����Ԥ��ʱ��(��λ��,��С1�����5��)","OutputTime","","number",pPara->m_fOutputTime);
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

		pPik08Serialize->xml_serialize("������Դѡ��(0-����,1-����,2-����)","U2Power","","number",pPara->m_oPik08Para[nIndex].m_nU2Power);
		pPik08Serialize->xml_serialize("��ѹͨ��ģʽѡ��(0-4·����,1-�ϲ���A��,2-�ϲ���B��,3-�ϲ���C��)","VoltMode","","number",pPara->m_oPik08Para[nIndex].m_nVoltMode);
		pPik08Serialize->xml_serialize("����ͨ��ģʽѡ��(0-4·����,1-�ϲ���A��,2-�ϲ���B��,3-�ϲ���C��)","CurrMode","","number",pPara->m_oPik08Para[nIndex].m_nCurrMode);
		pPik08Serialize->xml_serialize("��ѹ���ѡ��(1-S1,2-S2,3-S3,�ȵ�)","VoltBoardSel","","number",pPara->m_oPik08Para[nIndex].m_nVoltBoardSel);
		pPik08Serialize->xml_serialize("�������ѡ��(1-S1,2-S2,3-S3,�ȵ�)","CurrBoardSel","","number",pPara->m_oPik08Para[nIndex].m_nCurrBoardSel);
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
