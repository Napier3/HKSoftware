#include "stdafx.h"
#include "tmt_fa_Paras_set.h"
#include "../tmt_system_config.h"
#include"../../../SttCmd/SttTestCmd.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"
#endif

void stt_xml_serialize(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_base(pParas, pXmlSierialize);
	stt_xml_serialize_binary_closein(pParas, pXmlSierialize);
	stt_xml_serialize_binary_openin(pParas, pXmlSierialize);
	stt_xml_serialize_binary_Fitout(pParas, pXmlSierialize);
	stt_xml_serialize_binary_Quantileout(pParas, pXmlSierialize);
}

//���� ����ֵ ���л�
void stt_xml_serialize_base(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize)
{

	pXmlSierialize->xml_serialize("���ѹ", "RatedVol", "", "", pParas->m_fRatedVoltage);
	pXmlSierialize->xml_serialize("��ѹ", "ResidualVol", "","", pParas->m_fResidualVoltage );
	pXmlSierialize->xml_serialize("�����", "RatedCur", "", "", pParas->m_fRatedCurrent);
	pXmlSierialize->xml_serialize("���ϵ���","FaultCur","","",pParas->m_fFaultCurrent);
	pXmlSierialize->xml_serialize("���ϳ���ʱ��", "FailureDuration", "", "", pParas->m_fFailureDuration);

	pXmlSierialize->xml_serialize("�������ʱ��", "ErrorAssessTime", "", "", pParas->m_fErrorAssessTime);
	pXmlSierialize->xml_serialize("������ʱ��բʱ��", "m_fxTime", "", "", pParas->m_fxTime );
	pXmlSierialize->xml_serialize("��բ���޹���ȷ��ʱ��", "m_fyTime", "", "", pParas->m_fyTime);
	pXmlSierialize->xml_serialize("ʧѹ��բʱ��","m_fzTime","","",pParas->m_fzTime);
	pXmlSierialize->xml_serialize("����ģʽ����ʧѹ��ʱ��բʱ��", "m_fxlTime", "", "", pParas->m_fxlTime);
	pXmlSierialize->xml_serialize("����Ӧ���޹��ϵõ���ʱ��բʱ��", "m_fsTime", "", "", pParas->m_fsTime);
}

//������ 
void stt_xml_serialize_binary_closein(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("�ն˺�բ�������Aѡ��","_BinSelectA","","",pParas->m_binCloseIn[0].nSelect);
	pXmlSierialize->xml_serialize("�ն˺�բ�������Bѡ��","_BinSelectB","","",pParas->m_binCloseIn[1].nSelect);
	pXmlSierialize->xml_serialize("�ն˺�բ�������Cѡ��","_BinSelectC","","",pParas->m_binCloseIn[2].nSelect);
	pXmlSierialize->xml_serialize("�ն˺�բ�������Dѡ��","_BinSelectD","","",pParas->m_binCloseIn[3].nSelect);
	pXmlSierialize->xml_serialize("�ն˺�բ�������Eѡ��","_BinSelectE","","",pParas->m_binCloseIn[4].nSelect);
	pXmlSierialize->xml_serialize("�ն˺�բ�������Fѡ��","_BinSelectF","","",pParas->m_binCloseIn[5].nSelect);
	pXmlSierialize->xml_serialize("�ն˺�բ�������Gѡ��","_BinSelectG","","",pParas->m_binCloseIn[6].nSelect);
}

void stt_xml_serialize_binary_openin(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("�ն˷�բ�������aѡ��","_BinSelecta","","",pParas->m_binOpenIn[0].nSelect);
	pXmlSierialize->xml_serialize("�ն˷�բ�������bѡ��","_BinSelectb","","",pParas->m_binOpenIn[1].nSelect);
	pXmlSierialize->xml_serialize("�ն˷�բ�������cѡ��","_BinSelectc","","",pParas->m_binOpenIn[2].nSelect);
	pXmlSierialize->xml_serialize("�ն˷�բ�������dѡ��","_BinSelectd","","",pParas->m_binOpenIn[3].nSelect);
	pXmlSierialize->xml_serialize("�ն˷�բ�������eѡ��","_BinSelecte","","",pParas->m_binOpenIn[4].nSelect);
	pXmlSierialize->xml_serialize("�ն˷�բ�������fѡ��","_BinSelectf","","",pParas->m_binOpenIn[5].nSelect);
	pXmlSierialize->xml_serialize("�ն˷�բ�������gѡ��","_BinSelectg","","",pParas->m_binOpenIn[6].nSelect);
}


//������
void stt_xml_serialize_binary_Fitout(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("�ն˺�λ�źſ���1״̬","_Bout01","","",pParas->m_binFitout[0].nState);
	pXmlSierialize->xml_serialize("�ն˺�λ�źſ���2״̬","_Bout02","","",pParas->m_binFitout[1].nState);
	pXmlSierialize->xml_serialize("�ն˺�λ�źſ���3״̬","_Bout03","","",pParas->m_binFitout[2].nState);
	pXmlSierialize->xml_serialize("�ն˺�λ�źſ���4״̬","_Bout04","","",pParas->m_binFitout[3].nState);
	pXmlSierialize->xml_serialize("�ն˺�λ�źſ���5״̬","_Bout05","","",pParas->m_binFitout[4].nState);
	pXmlSierialize->xml_serialize("�ն˺�λ�źſ���6״̬","_Bout06","","",pParas->m_binFitout[5].nState);
	pXmlSierialize->xml_serialize("�ն˺�λ�źſ���7״̬","_Bout07","","",pParas->m_binFitout[6].nState);

}

//������
void stt_xml_serialize_binary_Quantileout(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("�ն˷�λ�źſ���1״̬","_Bout1","","",pParas->m_binQuantileout[0].nState);
	pXmlSierialize->xml_serialize("�ն˷�λ�źſ���2״̬","_Bout2","","",pParas->m_binQuantileout[1].nState);
	pXmlSierialize->xml_serialize("�ն˷�λ�źſ���3״̬","_Bout3","","",pParas->m_binQuantileout[2].nState);
	pXmlSierialize->xml_serialize("�ն˷�λ�źſ���4״̬","_Bout4","","",pParas->m_binQuantileout[3].nState);
	pXmlSierialize->xml_serialize("�ն˷�λ�źſ���5״̬","_Bout5","","",pParas->m_binQuantileout[4].nState);
	pXmlSierialize->xml_serialize("�ն˷�λ�źſ���6״̬","_Bout6","","",pParas->m_binQuantileout[5].nState);
	pXmlSierialize->xml_serialize("�ն˷�λ�źſ���7״̬","_Bout7","","",pParas->m_binQuantileout[6].nState);

}


////////////////////////////////
/*
#include"../../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_FaParasSetTest()
{
	tmt_fa_paras_set_test oFATest;
	oFATest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oFATest.m_oFaParasSet, pMacroParas);

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("VoltageTimeTypeSectorMode_Paras.xml");

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
*/


