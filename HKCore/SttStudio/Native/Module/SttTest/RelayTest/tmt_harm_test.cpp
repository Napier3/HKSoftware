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

    pHarmSerialize->xml_serialize("������ֵ",chID,chUnit,"number",pHarm->Harm[1].fAmp);
    pHarmSerialize->xml_serialize("������λ",chID2,"��","number",pHarm->Harm[1].fAngle);
	pHarm->Harm[1].fFreq=pParas->m_fBaseFre;
    for(int i=2; i<MAX_HARM_COUNT; i++)
    {
        sprintf(chName, "%d��г����ֵ", i);
        sprintf(chID, "harm%dAmp", i);
        pHarmSerialize->xml_serialize(chName,chID,chUnit,"number",pHarm->Harm[i].fAmp);
        sprintf(chName, "%d��г����λ", i);
        sprintf(chID, "harm%dAng", i);
		pHarmSerialize->xml_serialize(chName,chID,"��","number",pHarm->Harm[i].fAngle);
		pHarm->Harm[i].fFreq=pParas->m_fBaseFre*i;
    }
    pHarmSerialize->xml_serialize("ֱ������","DC",chUnit,"number",pHarm->Harm[0].fAmp);
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
	pHarmSerialize->xml_serialize("������ֵ",chID,chUnit,"number",pHarm->Harm[1].fAmp);
	pHarmSerialize->xml_serialize("������λ",chID2,"��","number",pHarm->Harm[1].fAngle);
	pHarm->Harm[1].fFreq=pParas->m_fBaseFre;
	for(int i=2; i<MAX_HARM_COUNT; i++)
	{
		sprintf(chName, "%d��г����ֵ", i);
		sprintf(chID, "harm%dAmp", i);
		sprintf(chName2, "%d��г����λ", i);
		sprintf(chID2, "harm%dAng", i);

		if (stt_xml_serialize_is_write(pXmlSierialize) && bSel)
		{//�·�����
			if (!pHarm->Harm[i].m_bSelect)
			{
				pHarmSerialize->xml_serialize(chName,chID,chUnit,"number",fAmp);
				pHarmSerialize->xml_serialize(chName2,chID2,"��","number",fAngle);
			}
			else
			{
				pHarmSerialize->xml_serialize(chName,chID,chUnit,"number",pHarm->Harm[i].fAmp);
				pHarmSerialize->xml_serialize(chName2,chID2,"��","number",pHarm->Harm[i].fAngle);
			}
		}
		else
		{
			pHarmSerialize->xml_serialize(chName,chID,chUnit,"number",pHarm->Harm[i].fAmp);
			pHarmSerialize->xml_serialize(chName2,chID2,"��","number",pHarm->Harm[i].fAngle);
		}
		
		pHarm->Harm[i].fFreq=pParas->m_fBaseFre*i;
	}
}

void stt_xml_serialize_binary_in(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pBinSerialize =pXmlSierialize->xml_serialize("����������", "binset", "bin", stt_ParaGroupKey());
	if (pBinSerialize == NULL)
	{
		return;
	}
    pBinSerialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
//    pXmlSierialize->xml_serialize("�������ʱ��","_SureTime","s","number",&pParas->m_fStabTime);
    pBinSerialize->xml_serialize("����Aѡ��","_BinSelectA","","BOOL",pParas->m_binIn[0].nSelect);
    pBinSerialize->xml_serialize("����Bѡ��","_BinSelectB","","BOOL",pParas->m_binIn[1].nSelect);
    pBinSerialize->xml_serialize("����Cѡ��","_BinSelectC","","BOOL",pParas->m_binIn[2].nSelect);
    pBinSerialize->xml_serialize("����Rѡ��","_BinSelectR","","BOOL",pParas->m_binIn[3].nSelect);
    pBinSerialize->xml_serialize("����aѡ��","_BinSelecta","","BOOL",pParas->m_binIn[4].nSelect);
    pBinSerialize->xml_serialize("����bѡ��","_BinSelectb","","BOOL",pParas->m_binIn[5].nSelect);
    pBinSerialize->xml_serialize("����cѡ��","_BinSelectc","","BOOL",pParas->m_binIn[6].nSelect);
    pBinSerialize->xml_serialize("����rѡ��","_BinSelectr","","BOOL",pParas->m_binIn[7].nSelect);
}

void stt_xml_serialize_binary_out(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pBoutSerialize =pXmlSierialize->xml_serialize("����������", "boutset", "bout", stt_ParaGroupKey());
	if (pBoutSerialize == NULL)
	{
		return;
	}
    pBoutSerialize->xml_serialize("����1״̬","_Bout1","","DOutputState",pParas->m_binOut[0].nState);
    pBoutSerialize->xml_serialize("����2״̬","_Bout2","","DOutputState",pParas->m_binOut[1].nState);
    pBoutSerialize->xml_serialize("����3״̬","_Bout3","","DOutputState",pParas->m_binOut[2].nState);
    pBoutSerialize->xml_serialize("����4״̬","_Bout4","","DOutputState",pParas->m_binOut[3].nState);
    pBoutSerialize->xml_serialize("����5״̬","_Bout5","","DOutputState",pParas->m_binOut[4].nState);
    pBoutSerialize->xml_serialize("����6״̬","_Bout6","","DOutputState",pParas->m_binOut[5].nState);
    pBoutSerialize->xml_serialize("����7״̬","_Bout7","","DOutputState",pParas->m_binOut[6].nState);
    pBoutSerialize->xml_serialize("����8״̬","_Bout8","","DOutputState",pParas->m_binOut[7].nState);
}

void stt_xml_serialize_auto(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pAutoSerialize =pXmlSierialize->xml_serialize("�Զ��仯����", "autoset", "auto", stt_ParaGroupKey());
	if (pAutoSerialize == NULL)
	{
		return;
	}
    pAutoSerialize->xml_serialize("�Ƿ��Զ��仯","_bAutoChange","","BOOL",pParas->m_bAuto);
    pAutoSerialize->xml_serialize("�仯��ѡ��","_Variable","","PsuGradientChannel",pParas->m_nGradientChSelect);
    pAutoSerialize->xml_serialize("�仯����ѡ��","_VarType","","PsuGradientType",pParas->m_nGradientTpSelect);
    pAutoSerialize->xml_serialize("�仯г������","_HarmIndex","","number",pParas->m_oHarmGradient.nHarmIndex);
    pAutoSerialize->xml_serialize("�仯ʼֵ","_BeginVal","","number",pParas->m_oHarmGradient.fStart);
    pAutoSerialize->xml_serialize("�仯��ֵ","_EndVal","","number",pParas->m_oHarmGradient.fEnd);
    pAutoSerialize->xml_serialize("�仯����","_StepVal","","number",pParas->m_oHarmGradient.fStep);
    pAutoSerialize->xml_serialize("ÿ��ʱ��","_StepTime","s","number",pParas->m_oHarmGradient.fStepTime);
}

void stt_xml_serialize(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("�����ʱ","_TimeLimit","s","number",pParas->m_fOutPutTime);
    pXmlSierialize->xml_serialize("г����ʾ��ʽ","_HarmMode","","HarExpression",pParas->m_nHarmMode);
    pXmlSierialize->xml_serialize("����Ƶ��","_BaseFre","Hz","number",pParas->m_fBaseFre);
    pXmlSierialize->xml_serialize("�Ƿ�������������ֵ","_bLock","","BOOL",pParas->m_bLock);

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
	pXmlSierialize->xml_serialize("����Ƶ��","_BaseFre","Hz","number",pParas->m_fBaseFre);

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
    pXmlSierialize->xml_serialize("�������","TripFlag","","number", pResults->m_nTripFlag);
    pXmlSierialize->xml_serialize("����ʱ��","TripTime","s","number", pResults->m_fTripTime);
    pXmlSierialize->xml_serialize("����ֵ","ActValue","s","number", pResults->m_fActValue);
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
