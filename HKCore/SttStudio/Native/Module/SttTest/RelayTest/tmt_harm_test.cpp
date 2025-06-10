#include "stdafx.h"
#include "tmt_harm_test.h"
#include "../../../../Module/API/StringApi.h"

void stt_init_paras(tmt_HarmParas *pParas)
{
    memset(&pParas, 0, sizeof(tmt_HarmParas));
    pParas->init();
}

void stt_init_results(tmt_HarmResult *pResults)
{
    memset(&pResults, 0, sizeof(tmt_HarmResult));
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

void stt_xml_serialize(CString strName, CString strID, int nIndex, int nType, tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    char chName[MAX_PATH],chID[MAX_PATH], chID2[MAX_PATH], chUnit[MAX_PATH];
    CString_to_char(strName, chName);
    CString_to_char(strID, chID);
    CSttXmlSerializeBase *pHarmSerialize =pXmlSierialize->xml_serialize(chName, chID, "harm", stt_ParaGroupKey());

    if (pHarmSerialize == NULL)
    {
        return;
    }

    tmt_channel *pHarm = (nType==0) ? &pParas->m_uiVOL[nIndex]:&pParas->m_uiCUR[nIndex];

    if (nType == 0)
        {
            sprintf(chID, "%s", "U0Amp");
            sprintf(chID2, "%s", "U0Ang");
            sprintf(chUnit, "%s", "V");
        }
        else
        {
            sprintf(chID, "%s", "I0Amp");
            sprintf(chID2, "%s", "I0Ang");
            sprintf(chUnit, "%s", "A");
        }

    pHarmSerialize->xml_serialize("基波幅值",chID,chUnit,"number",pHarm->Harm[1].fAmp);
    pHarmSerialize->xml_serialize("基波相位",chID2,"°","number",pHarm->Harm[1].fAngle);
	pHarm->Harm[1].fFreq=pParas->m_fBaseFre;
    for(int i=2; i<MAX_HARM_COUNT; i++)
    {
        sprintf(chName, "%d次谐波幅值", i);
        sprintf(chID, "harm%dAmp", i);
        pHarmSerialize->xml_serialize(chName,chID,chUnit,"number",pHarm->Harm[i].fAmp);
        sprintf(chName, "%d次谐波相位", i);
        sprintf(chID, "harm%dAng", i);
		pHarmSerialize->xml_serialize(chName,chID,"°","number",pHarm->Harm[i].fAngle);
		pHarm->Harm[i].fFreq=pParas->m_fBaseFre*i;
    }
    pHarmSerialize->xml_serialize("直流分量","DC",chUnit,"number",pHarm->Harm[0].fAmp);
}

void stt_xml_serialize_ex(CString strName, CString strID, int nIndex, int nType, tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize, bool bSel)
{
	char chName[MAX_PATH],chID[MAX_PATH], chName2[MAX_PATH],chID2[MAX_PATH], chUnit[MAX_PATH];
	CString_to_char(strName, chName);
	CString_to_char(strID, chID);
	CSttXmlSerializeBase *pHarmSerialize =pXmlSierialize->xml_serialize(chName, chID, "harm", stt_ParaGroupKey());

	if (pHarmSerialize == NULL)
	{
		return;
	}

	tmt_channel *pHarm = (nType==0) ? &pParas->m_uiVOL[nIndex]:&pParas->m_uiCUR[nIndex];

	if (nType == 0)
	{
		sprintf(chID, "%s", "U0Amp");
		sprintf(chID2, "%s", "U0Ang");
		sprintf(chUnit, "%s", "V");
	}
	else
	{
		sprintf(chID, "%s", "I0Amp");
		sprintf(chID2, "%s", "I0Ang");
		sprintf(chUnit, "%s", "A");
	}

	float fAmp = 0,fAngle = 0;
	pHarmSerialize->xml_serialize("基波幅值",chID,chUnit,"number",pHarm->Harm[1].fAmp);
	pHarmSerialize->xml_serialize("基波相位",chID2,"°","number",pHarm->Harm[1].fAngle);
	pHarm->Harm[1].fFreq=pParas->m_fBaseFre;
	for(int i=2; i<MAX_HARM_COUNT; i++)
	{
		sprintf(chName, "%d次谐波幅值", i);
		sprintf(chID, "harm%dAmp", i);
		sprintf(chName2, "%d次谐波相位", i);
		sprintf(chID2, "harm%dAng", i);

		if (stt_xml_serialize_is_write(pXmlSierialize) && bSel)
		{//下发命令
			if (!pHarm->Harm[i].m_bSelect)
			{
				pHarmSerialize->xml_serialize(chName,chID,chUnit,"number",fAmp);
				pHarmSerialize->xml_serialize(chName2,chID2,"°","number",fAngle);
			}
			else
			{
				pHarmSerialize->xml_serialize(chName,chID,chUnit,"number",pHarm->Harm[i].fAmp);
				pHarmSerialize->xml_serialize(chName2,chID2,"°","number",pHarm->Harm[i].fAngle);
			}
		}
		else
		{
			pHarmSerialize->xml_serialize(chName,chID,chUnit,"number",pHarm->Harm[i].fAmp);
			pHarmSerialize->xml_serialize(chName2,chID2,"°","number",pHarm->Harm[i].fAngle);
		}
		
		pHarm->Harm[i].fFreq=pParas->m_fBaseFre*i;
	}
}

void stt_xml_serialize_binary_in(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pBinSerialize =pXmlSierialize->xml_serialize("开入量设置", "binset", "bin", stt_ParaGroupKey());
	if (pBinSerialize == NULL)
	{
		return;
	}
    pBinSerialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
//    pXmlSierialize->xml_serialize("开入防抖时间","_SureTime","s","number",&pParas->m_fStabTime);
    pBinSerialize->xml_serialize("开入A选择","_BinSelectA","","BOOL",pParas->m_binIn[0].nSelect);
    pBinSerialize->xml_serialize("开入B选择","_BinSelectB","","BOOL",pParas->m_binIn[1].nSelect);
    pBinSerialize->xml_serialize("开入C选择","_BinSelectC","","BOOL",pParas->m_binIn[2].nSelect);
    pBinSerialize->xml_serialize("开入R选择","_BinSelectR","","BOOL",pParas->m_binIn[3].nSelect);
    pBinSerialize->xml_serialize("开入a选择","_BinSelecta","","BOOL",pParas->m_binIn[4].nSelect);
    pBinSerialize->xml_serialize("开入b选择","_BinSelectb","","BOOL",pParas->m_binIn[5].nSelect);
    pBinSerialize->xml_serialize("开入c选择","_BinSelectc","","BOOL",pParas->m_binIn[6].nSelect);
    pBinSerialize->xml_serialize("开入r选择","_BinSelectr","","BOOL",pParas->m_binIn[7].nSelect);
}

void stt_xml_serialize_binary_out(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pBoutSerialize =pXmlSierialize->xml_serialize("开出量设置", "boutset", "bout", stt_ParaGroupKey());
	if (pBoutSerialize == NULL)
	{
		return;
	}
    pBoutSerialize->xml_serialize("开出1状态","_Bout1","","DOutputState",pParas->m_binOut[0].nState);
    pBoutSerialize->xml_serialize("开出2状态","_Bout2","","DOutputState",pParas->m_binOut[1].nState);
    pBoutSerialize->xml_serialize("开出3状态","_Bout3","","DOutputState",pParas->m_binOut[2].nState);
    pBoutSerialize->xml_serialize("开出4状态","_Bout4","","DOutputState",pParas->m_binOut[3].nState);
    pBoutSerialize->xml_serialize("开出5状态","_Bout5","","DOutputState",pParas->m_binOut[4].nState);
    pBoutSerialize->xml_serialize("开出6状态","_Bout6","","DOutputState",pParas->m_binOut[5].nState);
    pBoutSerialize->xml_serialize("开出7状态","_Bout7","","DOutputState",pParas->m_binOut[6].nState);
    pBoutSerialize->xml_serialize("开出8状态","_Bout8","","DOutputState",pParas->m_binOut[7].nState);
}

void stt_xml_serialize_auto(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pAutoSerialize =pXmlSierialize->xml_serialize("自动变化设置", "autoset", "auto", stt_ParaGroupKey());
	if (pAutoSerialize == NULL)
	{
		return;
	}
    pAutoSerialize->xml_serialize("是否自动变化","_bAutoChange","","BOOL",pParas->m_bAuto);
    pAutoSerialize->xml_serialize("变化量选择","_Variable","","PsuGradientChannel",pParas->m_nGradientChSelect);
    pAutoSerialize->xml_serialize("变化类型选择","_VarType","","PsuGradientType",pParas->m_nGradientTpSelect);
    pAutoSerialize->xml_serialize("变化谐波次数","_HarmIndex","","number",pParas->m_oHarmGradient.nHarmIndex);
    pAutoSerialize->xml_serialize("变化始值","_BeginVal","","number",pParas->m_oHarmGradient.fStart);
    pAutoSerialize->xml_serialize("变化终值","_EndVal","","number",pParas->m_oHarmGradient.fEnd);
    pAutoSerialize->xml_serialize("变化步长","_StepVal","","number",pParas->m_oHarmGradient.fStep);
    pAutoSerialize->xml_serialize("每步时间","_StepTime","s","number",pParas->m_oHarmGradient.fStepTime);
}

void stt_xml_serialize(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("输出限时","_TimeLimit","s","number",pParas->m_fOutPutTime);
    pXmlSierialize->xml_serialize("谐波表示方式","_HarmMode","","HarExpression",pParas->m_nHarmMode);
    pXmlSierialize->xml_serialize("基波频率","_BaseFre","Hz","number",pParas->m_fBaseFre);
    pXmlSierialize->xml_serialize("是否锁定本次设置值","_bLock","","BOOL",pParas->m_bLock);

        CString strName[]={_T("Ua1"),_T("Ub1"),_T("Uc1"),_T("Ua2"),_T("Ub2"),_T("Uc2"),_T("Ia1"),_T("Ib1"),_T("Ic1"),_T("Ia2"),_T("Ib2"),_T("Ic2")};
        CString strID[]={_T("Ua1"),_T("Ub1"),_T("Uc1"),_T("Ua2"),_T("Ub2"),_T("Uc2"),_T("Ia1"),_T("Ib1"),_T("Ic1"),_T("Ia2"),_T("Ib2"),_T("Ic2")};

        for (int i=0; i<6; i++)
        {
            stt_xml_serialize(strName[i], strID[i], i, 0, pParas, pXmlSierialize);
        }

        for (int i=0; i<6; i++)
        {
            stt_xml_serialize(strName[i+6], strID[i+6], i+6, 1, pParas, pXmlSierialize);
        }

        stt_xml_serialize_binary_in(pParas, pXmlSierialize);
        stt_xml_serialize_binary_out(pParas, pXmlSierialize);
        stt_xml_serialize_auto(pParas, pXmlSierialize);
		pParas->m_oHarmGradient.nHarmIndex++;
}

void stt_xml_serialize_ex(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize, bool bSel)
{
	pXmlSierialize->xml_serialize("基波频率","_BaseFre","Hz","number",pParas->m_fBaseFre);

	CString strName[]={_T("Ua"),_T("Ub"),_T("Uc"),_T("Uz"),_T("Ia"),_T("Ib"),_T("Ic"),_T("I0")};
	CString strID[]={_T("Ua"),_T("Ub"),_T("Uc"),_T("Uz"),_T("Ia"),_T("Ib"),_T("Ic"),_T("I0")};

	for (int i=0; i<4; i++)
	{
		stt_xml_serialize_ex(strName[i], strID[i], i, 0, pParas, pXmlSierialize,bSel);
	}

	for (int i=0; i<4; i++)
	{
		stt_xml_serialize_ex(strName[i+4], strID[i+4], i, 1, pParas, pXmlSierialize,bSel);
	}
}

void stt_xml_serialize(tmt_HarmResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("动作标记","TripFlag","","number", pResults->m_nTripFlag);
    pXmlSierialize->xml_serialize("动作时间","TripTime","s","number", pResults->m_fTripTime);
    pXmlSierialize->xml_serialize("动作值","ActValue","s","number", pResults->m_fActValue);
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_HarmTest()
{
    tmt_HarmTest oHarmTest;
    oHarmTest.init();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oHarmTest.m_oHarmParas, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
	strXMLPath += ("HarmTestDemo.xml");
//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
