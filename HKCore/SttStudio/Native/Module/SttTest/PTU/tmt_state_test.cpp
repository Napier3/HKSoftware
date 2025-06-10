#include "stdafx.h"
#include "tmt_state_test.h"

void stt_init_paras(tmt_StateParas *pParas)
{
	memset(&pParas, 0, sizeof(MAX_STATE_COUNT));
	pParas->init();
}

void stt_init_results(tmt_StateResults *pResults)
{
	memset(&pResults, 0, sizeof(MAX_STATE_COUNT));
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
///
void stt_xml_serialize(tmt_ChannelHarm &oChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pChannel =pXmlSierialize->xml_serialize(pszID, pszID, "channel", stt_ParaGroupKey());

	if (pChannel == NULL)
	{
		return;
	}

	pChannel->xml_serialize("幅值", "mag", "", "float", oChannel.fAmp);
	pChannel->xml_serialize("相位", "ang", "", "float",  oChannel.fAngle);
	pChannel->xml_serialize("频率", "freq", "", "float", oChannel.fFreq);

	stt_xml_serialize_dc(oChannel, pChannel);
}

void stt_xml_serialize_dc(tmt_ChannelHarm &oChannel, CSttXmlSerializeBase *pXmlSierialize)
{
	int bDC = 0;
	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pXmlSierialize->xml_serialize("直流", "bDC", "", "BOOL", bDC);
		oChannel.bDC = bDC;
	}
	else
	{
		if (oChannel.bDC)
		{
			bDC = 1;
		}
		pXmlSierialize->xml_serialize("直流", "bDC", "", "BOOL", bDC);
	}
}

void stt_xml_serialize_binary_out(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("开出", "BOout", "BOUT", stt_ParaGroupKey());

	if (pStateSerialize == NULL)
	{
		return;
	}

    pStateSerialize->xml_serialize("开出翻转延时","BoutDelayT","s","number",oStatePara.m_binOut[0].fTimeTrig);

	CString strName,strID,strTemp;
	CString str1 = _T("开出");
	CString str2 = _T("状态");

	for(int nIndex = 0; nIndex < MAX_PARACOUNT_BINARY; nIndex++)
	{
		strTemp.Format(_T("%d"),nIndex+1);
		strName = str1 + strTemp + str2;
//		strName.Format(_T("开出%d状态"),nIndex+1);
		strID.Format("Bout%dState",(nIndex+1));
		pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","DOutputState",oStatePara.m_binOut[nIndex].nState);
	}
}

void stt_xml_serialize_binary_in(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("开入", "BIn", "BIN", stt_ParaGroupKey());

	if (pStateSerialize == NULL)
	{
		return;
	}

	pStateSerialize->xml_serialize("开入逻辑", "AndOr","","InPutLogic_Psu",oStatePara.m_nBinLogic);

	char pszBInName[20]="ABCDEFGH";
	CString strName,strID;
	CString str1 = _T("开入");
	CString str2 = _T("选择");

	int nCnt = MAX_PARACOUNT_BINARY;

	for(int nIndex = 0; nIndex < nCnt; nIndex++)
	{
		strName = str1 + pszBInName[nIndex] + str2;
//		strName.Format("开入%c选择",pszBInName[nIndex]);
		strID.Format("BIn%c",pszBInName[nIndex]);
		pStateSerialize->xml_serialize(strName.GetString()/*toUtf8().data()*/,strID.GetString(),"","BOOL",oStatePara.m_binIn[nIndex].nSelect);
	}
}

void stt_xml_serialize_gradient(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("递变", "Ramp", "RAMP", stt_ParaGroupKey());

    if (pStateSerialize == NULL)
    {
        return;
    }

    pStateSerialize->xml_serialize("递变类型选择","PsuSttRampType","","PsuSttRampType",oStatePara.m_nRampType);
    pStateSerialize->xml_serialize("递变通道选择","_GradientChSelect","","PsuGradientChannel",oStatePara.m_sttGradient.iVar);
    pStateSerialize->xml_serialize("df/dt","_dfdt","","number",oStatePara.m_sttGradient.fdfdt);
    pStateSerialize->xml_serialize("dv/dt","_dvdt","","number",oStatePara.m_sttGradient.fdvdt);
    pStateSerialize->xml_serialize("触发电压","_TrigerV","","number",oStatePara.m_sttGradient.fTrigerV);
    pStateSerialize->xml_serialize("终止电压","_EndV","","number",oStatePara.m_sttGradient.fEndV);
    pStateSerialize->xml_serialize("起始频率","_StartF","","number",oStatePara.m_sttGradient.fStartF);
    pStateSerialize->xml_serialize("终止频率","_EndF","","number",oStatePara.m_sttGradient.fEndF);
    pStateSerialize->xml_serialize("起始值","_Start","","number",oStatePara.m_sttGradient.fStart);
    pStateSerialize->xml_serialize("终止值","_End","","number",oStatePara.m_sttGradient.fEnd);
    pStateSerialize->xml_serialize("变化步长","_Step","","number",oStatePara.m_sttGradient.fStep);
    pStateSerialize->xml_serialize("每步时间","_StepTime","","number",oStatePara.m_sttGradient.fStepTime);	   
}

void stt_xml_serialize(tmt_GoosePub &oGoosePub, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pGooseSerialize =pXmlSierialize->xml_serialize("GOOSE发布控制块", "GOOSE", nIndex, "GOOSE", stt_ParaGroupKey());
	if (pGooseSerialize)
	{
		pGooseSerialize->xml_serialize("置检修","_Test","","BOOL",oGoosePub.m_bTest);

		CSttXmlSerializeBase *pChannelsSerialize =pGooseSerialize->xml_serialize("GOOSE发布控制块", "channels", nIndex, "Channels", stt_ParaGroupKey());
		CString strChannelID;

		for(int nIndex=0;nIndex<MAX_GOOSE_CHANNEL_COUNT;nIndex++)
		{
			strChannelID.Format(_T("channel%d"),nIndex);
			pChannelsSerialize->xml_serialize("GOOSE通道", strChannelID.GetString()," ","string",oGoosePub.m_strChannel[nIndex]);
		}
	}
}

void stt_xml_serialize(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("状态", "state", nIndex, "State", stt_ParaGroupKey());

	if (pStateSerialize == NULL)
	{
		return;
	}

	pStateSerialize->xml_serialize("触发方式", "EndMode","","StateEndMode_PSU",oStatePara.m_nTriggerCondition);
	pStateSerialize->xml_serialize("输出时间", "LastT","s","number",oStatePara.m_fTimeState);
	pStateSerialize->xml_serialize("触发后保持时间", "EndDelayT","s","number",oStatePara.m_fTimeAfterTrigger);
	pStateSerialize->xml_serialize("开出量保持时间", "OutputHoldT","s","number",oStatePara.m_fOutputHoldTime);

    pStateSerialize->xml_serialize("是否直流", "bDC","","BOOL",oStatePara.m_bDC);
    pStateSerialize->xml_serialize("辅助直流电压","VdcAux","V","number",oStatePara.m_fVolAux);
    pStateSerialize->xml_serialize("辅助直流电流","IdcAux","mA","number",oStatePara.m_fCurAux);
	pStateSerialize->xml_serialize("是否检修模式", "bTest","","BOOL",oStatePara.m_bTestMode);
	
	pStateSerialize->xml_serialize("GPS触发时刻（时）", "GpsH"," ","number",oStatePara.m_tGps.nHour);
	pStateSerialize->xml_serialize("GPS触发时刻（分）", "GpsM"," ","number",oStatePara.m_tGps.nMinutes);
	pStateSerialize->xml_serialize("GPS触发时刻（秒）", "GpsS"," ","number",oStatePara.m_tGps.nSeconds);

	stt_xml_serialize(oStatePara.m_uiVOL[0].Harm[1], "Ua",pStateSerialize);
	stt_xml_serialize(oStatePara.m_uiVOL[1].Harm[1], "Ub", pStateSerialize);
	stt_xml_serialize(oStatePara.m_uiVOL[2].Harm[1], "Uc", pStateSerialize);
	stt_xml_serialize(oStatePara.m_uiVOL[3].Harm[1], "Uz", pStateSerialize);

	stt_xml_serialize(oStatePara.m_uiCUR[0].Harm[1], "Ia",pStateSerialize);
	stt_xml_serialize(oStatePara.m_uiCUR[1].Harm[1], "Ib", pStateSerialize);
	stt_xml_serialize(oStatePara.m_uiCUR[2].Harm[1], "Ic", pStateSerialize);
	stt_xml_serialize(oStatePara.m_uiCUR[3].Harm[1], "I0", pStateSerialize);
/*
    for(int nIndex = 0;nIndex<MAX_GOOSEPUB_COUNT;nIndex++)
    {
        stt_xml_serialize(oStatePara.m_oGoosePub[nIndex],nIndex,pStateSerialize);
    }
*/
	stt_xml_serialize_binary_in(oStatePara, pStateSerialize);
	stt_xml_serialize_binary_out(oStatePara, pStateSerialize);
    stt_xml_serialize_gradient(oStatePara, pStateSerialize);
}

void stt_xml_serialize(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("开入量翻转判别条件", "_BinTripRef"," ","StateBinTripRef",pParas->m_nBinTripRef);
    pXmlSierialize->xml_serialize("是否为顺序状态序列", "_bSequence"," ","BOOL",pParas->m_bSequence);
    pXmlSierialize->xml_serialize("是否叠加直流分量","FaultId","s","BOOL",pParas->m_bPlusDC);
    pXmlSierialize->xml_serialize("直流分量的衰减时间常数", "_Tao","s","number",pParas->m_fTao);
	pXmlSierialize->xml_serialize("重复次数", "_RepeatNumbers"," ","number",pParas->m_nRepeatNumbers);
	pXmlSierialize->xml_serialize("状态数","StateCount","","number",pParas->m_nStateNumbers);

	long nIndex = 0;

	for (nIndex=0; nIndex<pParas->m_nStateNumbers; nIndex++)
	{
		stt_xml_serialize(pParas->m_paraState[nIndex], nIndex, pXmlSierialize);
	}
}

//bSel=true,则
void stt_xml_serialize_ex(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,bool bSel)
{
	pXmlSierialize->xml_serialize("开入量翻转判别条件", "_BinTripRef"," ","StateBinTripRef",pParas->m_nBinTripRef);
	pXmlSierialize->xml_serialize("是否为顺序状态序列", "_bSequence"," ","BOOL",pParas->m_bSequence);
	pXmlSierialize->xml_serialize("是否叠加直流分量","FaultId","s","BOOL",pParas->m_bPlusDC);
	pXmlSierialize->xml_serialize("直流分量的衰减时间常数", "_Tao","s","number",pParas->m_fTao);
	pXmlSierialize->xml_serialize("重复次数", "_RepeatNumbers"," ","number",pParas->m_nRepeatNumbers);

	if (stt_xml_serialize_is_write(pXmlSierialize) && bSel)
	{//下发命令时
		int nSelCnt = pParas->GetSelCount();
		pXmlSierialize->xml_serialize("状态数","StateCount","","number",nSelCnt);
	}
	else
	{
		pXmlSierialize->xml_serialize("状态数","StateCount","","number",pParas->m_nStateNumbers);
		if (stt_xml_serialize_is_read(pXmlSierialize))
		{
			pParas->init(pParas->m_nStateNumbers);
		}
	}

	long nIndex = 0;
	for (int i=0; i<pParas->m_nStateNumbers; i++)
	{
		if (bSel)
		{
			if (pParas->m_paraState[i].m_bSelected)
			{
				stt_xml_serialize(pParas->m_paraState[i], nIndex, pXmlSierialize);
				nIndex++;
			}
		}
		else
		{
			stt_xml_serialize(pParas->m_paraState[i], nIndex, pXmlSierialize);
			nIndex++;
		}		
	}
}

void stt_xml_serialize(tmt_StateResult &oStateResult, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pStateSerialize =pXmlSierialize->xml_serialize("状态", "state", nIndex, "State", stt_ParaGroupKey());

	if (pStateSerialize == NULL)
	{
		return;
	}

	CString strName,strID;
	for(int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
	{
		strName.Format(_T("开入%d翻转时刻"),nIndex+1);
		strID.Format("TtripBin%d",(nIndex+1));
		pStateSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",oStateResult.m_frTimeBinAct[nIndex][0]);
	}
}

void stt_xml_serialize(tmt_StateResults *pResults,int nStateNums, CSttXmlSerializeBase *pXmlSierialize)
{
	for (int nIndex=0; nIndex<nStateNums; nIndex++)
	{
		stt_xml_serialize(pResults->m_resultState[nIndex], nIndex, pXmlSierialize);
	}
}

#include"../../SttCmd/SttTestCmd.h"
#include"tmt_state_test.h"
#include"../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_StateTest()
{
	tmt_StateTest oStateTest;
	oStateTest.init(10);
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oStateTest.m_oStateParas, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("StateTestDemo.xml");
	//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}


//////////////////////////////////////////////////////////////////////////
//

tmt_StatePara* stt_state_paras_insert_after(tmt_StateParas *pParas, tmt_StatePara *pSrc, int nAfter)
{
	if (nAfter >= pParas->m_nStateNumbers || nAfter < 0)
	{
		return NULL;
	}

	if (pParas->m_nStateNumbers >= MAX_STATE_COUNT)
	{
		return NULL;
	}

	int nIndex = 0;

	for (nIndex=pParas->m_nStateNumbers; nIndex > nAfter+1; nIndex--)
	{
		pParas->m_paraState[nIndex] = pParas->m_paraState[nIndex-1];
	}

	if (pSrc != NULL)
	{
		pParas->m_paraState[nAfter+1] = *pSrc;
	}

	pParas->m_nStateNumbers++;

	return &pParas->m_paraState[nAfter+1];
}

tmt_StatePara* stt_state_paras_insert_before(tmt_StateParas *pParas, tmt_StatePara *pSrc, int nBefore)
{
	if (nBefore >= pParas->m_nStateNumbers || nBefore < 0)
	{
		return NULL;
	}

	if (pParas->m_nStateNumbers >= MAX_STATE_COUNT)
	{
		return NULL;
	}

	int nIndex = 0;

	for (nIndex=pParas->m_nStateNumbers; nIndex > nBefore; nIndex--)
	{
		pParas->m_paraState[nIndex] = pParas->m_paraState[nIndex-1];
	}

	if (pSrc != NULL)
	{
		pParas->m_paraState[nBefore] = *pSrc;
	}

	pParas->m_nStateNumbers++;

	return &pParas->m_paraState[nBefore];
}

void stt_state_paras_delete(tmt_StateParas *pParas, int nIndex)
{
	if (nIndex >= pParas->m_nStateNumbers || nIndex < 0)
	{
		return;
	}

	for (int i=nIndex+1; i<pParas->m_nStateNumbers; i++)
	{
		pParas->m_paraState[i-1] = pParas->m_paraState[i];
	}

	pParas->m_nStateNumbers--;
}