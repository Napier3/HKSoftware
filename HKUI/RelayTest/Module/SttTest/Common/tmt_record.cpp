#include "stdafx.h"
#include "tmt_record.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

void stt_init_paras(tmt_RecordParas *pParas)
{
	pParas->init(IECSIZE_MAX);
}

void stt_xml_serialize(tmt_RecordPara &oPara, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pSubSerialize =pXmlSierialize->xml_serialize("订阅", "Subscribe", nIndex, "Subscribe", stt_ParaGroupKey());

	if (pSubSerialize == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pSubSerialize->xml_serialize(("目标MAC"), ("DestMac"),(" "),("string"),oPara.dest_mac);
	pSubSerialize->xml_serialize(("Appid"), ("APPID"),(" "),("string"),oPara.appid);
	pSubSerialize->xml_serialize(("接收光口"), ("Port"),(" "),("string"),oPara.port);
	pSubSerialize->xml_serialize(("报文类型"), ("Type"),(" "),("string"),oPara.ntype);
#else
	pSubSerialize->xml_serialize((/*"目标MAC"*/g_sLangTxt_Native_DestMACs.GetString()), ("DestMac"),(" "),("string"),oPara.dest_mac);
	pSubSerialize->xml_serialize(("Appid"), ("APPID"),(" "),("string"),oPara.appid);
	pSubSerialize->xml_serialize((/*"接收光口"*/g_sLangTxt_Native_RecvOptPort.GetString()), ("Port"),(" "),("string"),oPara.port);
	pSubSerialize->xml_serialize((/*"报文类型"*/g_sLangTxt_Gradient_MessageType.GetString()), ("Type"),(" "),("string"),oPara.ntype);
#endif
}

void stt_xml_serialize(tmt_RecordParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{	
	#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("订阅总数","SubscribeCount","","int",pParas->m_nSubNumber);
	pXmlSierialize->xml_serialize("工作模式","Mode","","int",pParas->m_mode);
	pXmlSierialize->xml_serialize("订阅IED","CRC","","int",pParas->m_crc);
#else
	pXmlSierialize->xml_serialize(/*"订阅总数"*/g_sLangTxt_Native_TotalSubs.GetString(),"SubscribeCount","","int",pParas->m_nSubNumber);
	pXmlSierialize->xml_serialize(/*"工作模式"*/g_sLangTxt_Native_OpMode.GetString(),"Mode","","int",pParas->m_mode);
	pXmlSierialize->xml_serialize(/*"订阅IED"*/g_sLangTxt_IEC_SubIED.GetString(),"CRC","","int",pParas->m_crc);
#endif

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
