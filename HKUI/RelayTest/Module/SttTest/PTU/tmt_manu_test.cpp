#include "stdafx.h"
#include "tmt_manu_test.h"

void stt_init_paras(tmt_ManualParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_ManualParas));
	pParas->init();
}

void stt_init_results(tmt_ManualResult *pResults)
{
	memset(&pResults, 0, sizeof(tmt_ManualResult));
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

void stt_xml_serialize_binary_out(tmt_BinaryOut *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("开出1状态","_Bout1","","DOutputState",pParas[0].nState);
	pXmlSierialize->xml_serialize("开出2状态","_Bout2","","DOutputState",pParas[1].nState);
	pXmlSierialize->xml_serialize("开出3状态","_Bout3","","DOutputState",pParas[2].nState);
	pXmlSierialize->xml_serialize("开出4状态","_Bout4","","DOutputState",pParas[3].nState);
	pXmlSierialize->xml_serialize("开出5状态","_Bout5","","DOutputState",pParas[4].nState);
	pXmlSierialize->xml_serialize("开出6状态","_Bout6","","DOutputState",pParas[5].nState);
	pXmlSierialize->xml_serialize("开出7状态","_Bout7","","DOutputState",pParas[6].nState);
	pXmlSierialize->xml_serialize("开出8状态","_Bout8","","DOutputState",pParas[7].nState);
}

void stt_xml_serialize_binary_in(tmt_BinaryIn *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("开入A选择","_BinSelectA","","BOOL",pParas[0].nSelect);
	pXmlSierialize->xml_serialize("开入B选择","_BinSelectB","","BOOL",pParas[1].nSelect);
	pXmlSierialize->xml_serialize("开入C选择","_BinSelectC","","BOOL",pParas[2].nSelect);
	pXmlSierialize->xml_serialize("开入R选择","_BinSelectR","","BOOL",pParas[3].nSelect);
	pXmlSierialize->xml_serialize("开入a选择","_BinSelecta","","BOOL",pParas[4].nSelect);
	pXmlSierialize->xml_serialize("开入b选择","_BinSelectb","","BOOL",pParas[5].nSelect);
	pXmlSierialize->xml_serialize("开入c选择","_BinSelectc","","BOOL",pParas[6].nSelect);
	pXmlSierialize->xml_serialize("开入r选择","_BinSelectr","","BOOL",pParas[7].nSelect);
}

void stt_xml_serialize_dc(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	int bDC = 0;
	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
	{
		pXmlSierialize->xml_serialize("是否以直流模式输出", "bDC", "", "BOOL", bDC);
		pParas->setDC(bDC);
	}
	else if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_WRITE)
	{
		if (pParas->m_bDC)
		{
			bDC = 1;
		}
		pXmlSierialize->xml_serialize("是否以直流模式输出", "bDC", "", "BOOL", bDC);
	}
}

void stt_xml_serialize_Aging(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	int bAging = 0;
	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
	{
		pXmlSierialize->xml_serialize("是否老化试验", "bAging", "", "BOOL", bAging);
		pParas->m_bAging = bAging;
	}
	else if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_WRITE)
	{
		if (pParas->m_bAging)
		{
			bAging = 1;
		}
		pXmlSierialize->xml_serialize("是否老化试验", "bAging", "", "BOOL", bAging);
	}
}

void stt_xml_serialize_Lock(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	int bLock = 0;
	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
	{
		pXmlSierialize->xml_serialize("是否锁定", "_bLock", "", "BOOL", bLock);
		pParas->m_bLockChanged = bLock;
	}
	else if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_WRITE)
	{
		if (pParas->m_bLockChanged)
		{
			bLock = 1;
		}
		pXmlSierialize->xml_serialize("是否锁定", "_bLock", "", "BOOL", bLock);
	}
}

void stt_xml_serialize_Auto(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	int bAuto = 0;
	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
	{
		pXmlSierialize->xml_serialize("是否自动递变", "_bAuto", "", "BOOL", bAuto);
		pParas->m_bAuto = bAuto;
	}
	else if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_WRITE)
	{
		if (pParas->m_bAuto)
		{
			bAuto = 1;
		}
		pXmlSierialize->xml_serialize("是否自动递变", "_bAuto", "", "BOOL", bAuto);
	}
}

void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("Ua幅值","_Ua","V","number",pParas->m_uiVOL[0].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ua相位","_UaPh","°","number",pParas->m_uiVOL[0].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Ua频率","_UaFre","Hz","number",pParas->m_uiVOL[0].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Ub幅值","_Ub","V","number",pParas->m_uiVOL[1].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ub相位","_UbPh","°","number",pParas->m_uiVOL[1].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Ub频率","_UbFre","Hz","number",pParas->m_uiVOL[1].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Uc幅值","_Uc","V","number",pParas->m_uiVOL[2].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Uc相位","_UcPh","°","number",pParas->m_uiVOL[2].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Uc频率","_UcFre","Hz","number",pParas->m_uiVOL[2].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Uz幅值","_Uz","V","number",pParas->m_uiVOL[3].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Uz相位","_UzPh","°","number",pParas->m_uiVOL[3].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Uz频率","_UzFre","Hz","number",pParas->m_uiVOL[3].Harm[1].fFreq);

	pXmlSierialize->xml_serialize("Ia幅值","_Ia","A","number",pParas->m_uiCUR[0].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ia相位","_IaPh","°","number",pParas->m_uiCUR[0].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Ia频率","_IaFre","Hz","number",pParas->m_uiCUR[0].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Ib幅值","_Ib","A","number",pParas->m_uiCUR[1].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ib相位","_IbPh","°","number",pParas->m_uiCUR[1].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Ib频率","_IbFre","Hz","number",pParas->m_uiCUR[1].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Ic幅值","_Ic","A","number",pParas->m_uiCUR[2].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ic相位","_IcPh","°","number",pParas->m_uiCUR[2].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("Ic频率","_IcFre","Hz","number",pParas->m_uiCUR[2].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("I0幅值","_I0","A","number",pParas->m_uiCUR[3].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("I0相位","_I0Ph","°","number",pParas->m_uiCUR[3].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("I0频率","_I0Fre","Hz","number",pParas->m_uiCUR[3].Harm[1].fFreq);

	pXmlSierialize->xml_serialize("过载延时","fOverload","s","number",pParas->m_fOverloadDelaytime);
    pXmlSierialize->xml_serialize("最长输出时间", "OutputTime"," ","number",pParas->m_fOutPutTime);
	pXmlSierialize->xml_serialize("辅助直流电流","fCurAux","mA","number",pParas->m_fCurAux);
	pXmlSierialize->xml_serialize("辅助直流电压","fVolAux","V","number",pParas->m_fVolAux);
	
	pXmlSierialize->xml_serialize("递变通道选择","_GradientChSelect","","PsuGradientChannel",pParas->m_nGradientChSelect);
	pXmlSierialize->xml_serialize("递变类型选择","_GradientTpSelect","","PsuGradientType",pParas->m_nGradientTpSelect);
	pXmlSierialize->xml_serialize("变化模式","Mode","","UIVariateMode",pParas->m_manuGradient.nMode);
	pXmlSierialize->xml_serialize("变化始值","Start","","number",pParas->m_manuGradient.fStart);
	pXmlSierialize->xml_serialize("变化终值","End","","number",pParas->m_manuGradient.fEnd);
	pXmlSierialize->xml_serialize("变化步长","Step","","number",pParas->m_manuGradient.fStep);
	pXmlSierialize->xml_serialize("每步时间","StepTime","","number",pParas->m_manuGradient.fStepTime);
	pXmlSierialize->xml_serialize("触发延时","TrigDelay","","number",pParas->m_manuGradient.fTrigDelay);
	pXmlSierialize->xml_serialize("变化谐波次数","Harm","","number",pParas->m_manuGradient.nHarmIndex);

	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut,pXmlSierialize);
	stt_xml_serialize_dc(pParas,pXmlSierialize);
	stt_xml_serialize_Aging(pParas,pXmlSierialize);
	stt_xml_serialize_Lock(pParas,pXmlSierialize);
	stt_xml_serialize_Auto(pParas,pXmlSierialize);
}

void stt_xml_serialize(tmt_ManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{

}

#include"../../SttCmd/SttTestCmd.h"
#include"tmt_manu_test.h"
#include"../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_ManuTest()
{
	tmt_ManualTest oManualTest;
	oManualTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oManualTest.m_oManuParas, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("ManualTestDemo.xml");
//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
