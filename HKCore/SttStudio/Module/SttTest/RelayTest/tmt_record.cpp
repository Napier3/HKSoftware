#include "stdafx.h"
#include "tmt_record.h"

void stt_init_paras(tmt_RecordParas *pParas)
{
	pParas->init(IECSIZE_MAX);
}

void stt_xml_serialize(tmt_RecordPara &oPara, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pSubSerialize =pXmlSierialize->xml_serialize("����", "Subscribe", nIndex, "Subscribe", stt_ParaGroupKey());

	if (pSubSerialize == NULL)
	{
		return;
	}

	pSubSerialize->xml_serialize(("Ŀ��MAC"), ("DestMac"),(" "),("string"),oPara.dest_mac);
	pSubSerialize->xml_serialize(("Appid"), ("APPID"),(" "),("string"),oPara.appid);
	pSubSerialize->xml_serialize(("���չ��"), ("Port"),(" "),("string"),oPara.port);
	pSubSerialize->xml_serialize(("��������"), ("Type"),(" "),("string"),oPara.ntype);
}

void stt_xml_serialize(tmt_RecordParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{	
	pXmlSierialize->xml_serialize("��������","SubscribeCount","","int",pParas->m_nSubNumber);
	pXmlSierialize->xml_serialize("����ģʽ","Mode","","int",pParas->m_mode);
	long nIndex = 0;

	for (nIndex=0; nIndex<pParas->m_nSubNumber; nIndex++)
	{
		stt_xml_serialize(pParas->m_paras[nIndex], nIndex, pXmlSierialize);
	}
}

#include"../../SttCmd/SttTestCmd.h"
#include"tmt_record.h"
#include"../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_Record()
{
	tmt_RecordTest oRecordTest;
	oRecordTest.init(IECSIZE_MAX);
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	//pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oRecordTest.m_oRecordPara, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("RecordDemo.xml");
	//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
