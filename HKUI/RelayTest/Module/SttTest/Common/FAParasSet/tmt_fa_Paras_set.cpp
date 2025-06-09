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

//界面 基础值 序列化
void stt_xml_serialize_base(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize)
{

	pXmlSierialize->xml_serialize("额定电压", "RatedVol", "", "", pParas->m_fRatedVoltage);
	pXmlSierialize->xml_serialize("残压", "ResidualVol", "","", pParas->m_fResidualVoltage );
	pXmlSierialize->xml_serialize("额定电流", "RatedCur", "", "", pParas->m_fRatedCurrent);
	pXmlSierialize->xml_serialize("故障电流","FaultCur","","",pParas->m_fFaultCurrent);
	pXmlSierialize->xml_serialize("故障持续时间", "FailureDuration", "", "", pParas->m_fFailureDuration);

	pXmlSierialize->xml_serialize("误差评估时间", "ErrorAssessTime", "", "", pParas->m_fErrorAssessTime);
	pXmlSierialize->xml_serialize("来电延时合闸时间", "m_fxTime", "", "", pParas->m_fxTime );
	pXmlSierialize->xml_serialize("合闸后无故障确认时间", "m_fyTime", "", "", pParas->m_fyTime);
	pXmlSierialize->xml_serialize("失压跳闸时间","m_fzTime","","",pParas->m_fzTime);
	pXmlSierialize->xml_serialize("联络模式单侧失压延时合闸时间", "m_fxlTime", "", "", pParas->m_fxlTime);
	pXmlSierialize->xml_serialize("自适应型无故障得电延时合闸时间", "m_fsTime", "", "", pParas->m_fsTime);
}

//开入量 
void stt_xml_serialize_binary_closein(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("终端合闸输出开入A选择","_BinSelectA","","",pParas->m_binCloseIn[0].nSelect);
	pXmlSierialize->xml_serialize("终端合闸输出开入B选择","_BinSelectB","","",pParas->m_binCloseIn[1].nSelect);
	pXmlSierialize->xml_serialize("终端合闸输出开入C选择","_BinSelectC","","",pParas->m_binCloseIn[2].nSelect);
	pXmlSierialize->xml_serialize("终端合闸输出开入D选择","_BinSelectD","","",pParas->m_binCloseIn[3].nSelect);
	pXmlSierialize->xml_serialize("终端合闸输出开入E选择","_BinSelectE","","",pParas->m_binCloseIn[4].nSelect);
	pXmlSierialize->xml_serialize("终端合闸输出开入F选择","_BinSelectF","","",pParas->m_binCloseIn[5].nSelect);
	pXmlSierialize->xml_serialize("终端合闸输出开入G选择","_BinSelectG","","",pParas->m_binCloseIn[6].nSelect);
}

void stt_xml_serialize_binary_openin(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("终端分闸输出开入a选择","_BinSelecta","","",pParas->m_binOpenIn[0].nSelect);
	pXmlSierialize->xml_serialize("终端分闸输出开入b选择","_BinSelectb","","",pParas->m_binOpenIn[1].nSelect);
	pXmlSierialize->xml_serialize("终端分闸输出开入c选择","_BinSelectc","","",pParas->m_binOpenIn[2].nSelect);
	pXmlSierialize->xml_serialize("终端分闸输出开入d选择","_BinSelectd","","",pParas->m_binOpenIn[3].nSelect);
	pXmlSierialize->xml_serialize("终端分闸输出开入e选择","_BinSelecte","","",pParas->m_binOpenIn[4].nSelect);
	pXmlSierialize->xml_serialize("终端分闸输出开入f选择","_BinSelectf","","",pParas->m_binOpenIn[5].nSelect);
	pXmlSierialize->xml_serialize("终端分闸输出开入g选择","_BinSelectg","","",pParas->m_binOpenIn[6].nSelect);
}


//开出量
void stt_xml_serialize_binary_Fitout(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("终端合位信号开出1状态","_Bout01","","",pParas->m_binFitout[0].nState);
	pXmlSierialize->xml_serialize("终端合位信号开出2状态","_Bout02","","",pParas->m_binFitout[1].nState);
	pXmlSierialize->xml_serialize("终端合位信号开出3状态","_Bout03","","",pParas->m_binFitout[2].nState);
	pXmlSierialize->xml_serialize("终端合位信号开出4状态","_Bout04","","",pParas->m_binFitout[3].nState);
	pXmlSierialize->xml_serialize("终端合位信号开出5状态","_Bout05","","",pParas->m_binFitout[4].nState);
	pXmlSierialize->xml_serialize("终端合位信号开出6状态","_Bout06","","",pParas->m_binFitout[5].nState);
	pXmlSierialize->xml_serialize("终端合位信号开出7状态","_Bout07","","",pParas->m_binFitout[6].nState);

}

//开出量
void stt_xml_serialize_binary_Quantileout(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("终端分位信号开出1状态","_Bout1","","",pParas->m_binQuantileout[0].nState);
	pXmlSierialize->xml_serialize("终端分位信号开出2状态","_Bout2","","",pParas->m_binQuantileout[1].nState);
	pXmlSierialize->xml_serialize("终端分位信号开出3状态","_Bout3","","",pParas->m_binQuantileout[2].nState);
	pXmlSierialize->xml_serialize("终端分位信号开出4状态","_Bout4","","",pParas->m_binQuantileout[3].nState);
	pXmlSierialize->xml_serialize("终端分位信号开出5状态","_Bout5","","",pParas->m_binQuantileout[4].nState);
	pXmlSierialize->xml_serialize("终端分位信号开出6状态","_Bout6","","",pParas->m_binQuantileout[5].nState);
	pXmlSierialize->xml_serialize("终端分位信号开出7状态","_Bout7","","",pParas->m_binQuantileout[6].nState);

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


