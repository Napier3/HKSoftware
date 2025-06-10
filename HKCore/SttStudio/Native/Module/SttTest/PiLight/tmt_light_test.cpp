#include "stdafx.h"
#include "tmt_light_test.h"
#include "../../../../Module/API/StringApi.h"

void stt_init_paras(tmt_LightPara *pPara)
{
	memset(&pPara, 0, sizeof(tmt_LightPara));
	pPara->init();
}

void stt_xml_serialize(CString strName, CString strID, int nIndex,  tmt_LightPara *pPara, CSttXmlSerializeBase *pXmlSierialize)
{
	char chName[MAX_PATH],chID[MAX_PATH], chID2[MAX_PATH], chUnit[MAX_PATH];
	CString_to_char(strName, chName);
	CString_to_char(strID, chID);
	CSttXmlSerializeBase *pHarmSerialize =pXmlSierialize->xml_serialize(chName, chID, "harm", stt_ParaGroupKey());

	if (pHarmSerialize == NULL)
	{
		return;
	}

	tmt_channel *pHarm = &pPara->m_uiCUR[nIndex];

	sprintf(chID, "%s", "I0Amp");
	sprintf(chID2, "%s", "I0Ang");
	sprintf(chUnit, "%s", "A");

	pHarmSerialize->xml_serialize("基波幅值",chID,chUnit,"number",pHarm->Harm[1].fAmp);
	pHarmSerialize->xml_serialize("基波相位",chID2,"°","number",pHarm->Harm[1].fAngle);

	pHarm->Harm[1].nSelectIndex = 0;
	pHarm->Harm[1].fFreq   =  pPara->m_fBaseFre;
	int nSelectIndex = 1;
	for(int i  =  2;  i  <  32;  i++)
	{
		sprintf(chName,   "%d次谐波相位",   i);
		sprintf(chID,   "harm%dAng",   i);
		BOOL bRet = pHarmSerialize->xml_serialize(chName,chID,   "°",   "number",   pHarm->Harm[i].fAngle);
		if (!bRet)
		{
			pHarm->Harm[i].nSelectIndex = -1;//用于SttDeviceBase叠加谐波时过滤
			continue;
		}

		sprintf(chName, "%d次谐波幅值",   i);
		sprintf(chID, "harm%dAmp",   i);
		pHarmSerialize->xml_serialize(chName,   chID,   chUnit,   "number",   pHarm->Harm[i].fAmp);

		pHarm->Harm[i].nSelectIndex = nSelectIndex++;//从2次谐波开始计数选中的叠加波形
		pHarm->Harm[i].fFreq    =    pPara->m_fBaseFre   *   i;
	}

	pHarmSerialize->xml_serialize("直流分量",   "DC",   chUnit,   "number",   pHarm->Harm[0].fAmp);
}

void stt_xml_serialize(tmt_LightPara *pPara, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("光源启动映射开关量,1-8:开入1-8","UseBi","","number",pPara->m_nUseBi);
	pXmlSierialize->xml_serialize("光源与电流输出时间关系 0:电流超前 1:光源超前","DelayType","","number",pPara->m_nDelayType);
	pXmlSierialize->xml_serialize("超前时间 毫秒","DelayTime","","number",pPara->m_fDelayTime);

	pXmlSierialize->xml_serialize("模式选择,0-阶跃,1-脉冲","Mode","","number",pPara->m_nMode);
	pXmlSierialize->xml_serialize("脉冲时间,单位ms","Time","","number",pPara->m_nTime);
	pXmlSierialize->xml_serialize("光源选择,0-紫光,1-白光","Type","","number",pPara->m_nType);
	pXmlSierialize->xml_serialize("紫光光强","Data0","","number",pPara->m_nData0);
	pXmlSierialize->xml_serialize("白光光强","Data1","","number",pPara->m_nData1);
	pXmlSierialize->xml_serialize("基波频率","_BaseFre","Hz","number",pPara->m_fBaseFre);

	CString strID;
	for(int nIndex=0;nIndex<6;nIndex++)
	{
		strID.Format(_T("I%d"),nIndex+1);
		stt_xml_serialize("", strID, nIndex, pPara, pXmlSierialize);
	}

	pXmlSierialize->xml_serialize("开入变位后,0-不停止实验,1-停止实验","BinStop","","number",pPara->m_nBinStop);
	pXmlSierialize->xml_serialize("开入逻辑,0:开入或,1:开入与","_AndOr","","InPutLogic_Psu",pPara->m_nBinLogic);
	stt_xml_serialize_binary_in(pPara->m_binIn,pXmlSierialize);
	stt_xml_serialize_binary_out(pPara->m_binOut, pXmlSierialize);
}

void stt_xml_serialize_act_rcd(tmt_LightResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//动作记录,最大64次,根据实际动作情况,上送总的动作信息
{
	CSttXmlSerializeBase *pXmlActRcddata = pXmlSierialize->xml_serialize("ActRcd", "ActRcd", "ActRcd", stt_ParaGroupKey());

	if (pXmlActRcddata == NULL)
	{
		return;
	}

	CString strName,strID,strTemp,strTmp2;
	CString str1 = _T("开入");
	CString str2 = _T("第");
	CString str3 = _T("次动作时间");

	for(int nIndex = 0;nIndex<8;nIndex++)
	{
		strTemp.Format(_T("%d"),nIndex+1);

		for (int nIndexAct = 0;((nIndexAct<64)&&(nIndexAct<pResults->m_nrBinSwitchCount[nIndex]));nIndexAct++)
		{
			strTmp2.Format(_T("%d"),nIndexAct+1);
			strName = str1 + strTemp + str2 + strTmp2 + str3;
			strID.Format("Bin%dActCount%d",(nIndex+1),(nIndexAct+1));
			pXmlActRcddata->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResults->m_frTimeBinAct[nIndex][nIndexAct]);
		}
	}
}

void stt_xml_serialize(tmt_LightResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("动作标记","TripFlag","","number",pResults->m_nTripFlag);
	pXmlSierialize->xml_serialize("动作时间","TripTime","","number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("动作值","ActValue","","number",pResults->m_fActValue);

	CString strName,strID,strTemp;
	CString str1 = _T("开入");
	CString str2 = _T("结果状态");

	for(int nIndex = 0;nIndex<8;nIndex++)
	{
		strTemp.Format(_T("%d"),nIndex+1);
		strName = str1 + strTemp + str2;

		strID.Format("StateBin%d",(nIndex+1));
		pXmlSierialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResults->m_nrBinSwitchCount[nIndex]);
	}

	stt_xml_serialize_act_rcd(pResults,pXmlSierialize);
}

#include "../../SttCmd/SttTestCmd.h"
#include "../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_LightTest()
{
	tmt_LightTest otmt_LightTest;
	otmt_LightTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
//	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&otmt_LightTest.m_oLightPara, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("LightTest.xml");
	//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
