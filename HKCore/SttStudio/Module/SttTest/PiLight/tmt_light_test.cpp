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

	pHarmSerialize->xml_serialize("������ֵ",chID,chUnit,"number",pHarm->Harm[1].fAmp);
	pHarmSerialize->xml_serialize("������λ",chID2,"��","number",pHarm->Harm[1].fAngle);

	pHarm->Harm[1].nSelectIndex = 0;
	pHarm->Harm[1].fFreq   =  pPara->m_fBaseFre;
	int nSelectIndex = 1;
	for(int i  =  2;  i  <  32;  i++)
	{
		sprintf(chName,   "%d��г����λ",   i);
		sprintf(chID,   "harm%dAng",   i);
		BOOL bRet = pHarmSerialize->xml_serialize(chName,chID,   "��",   "number",   pHarm->Harm[i].fAngle);
		if (!bRet)
		{
			pHarm->Harm[i].nSelectIndex = -1;//����SttDeviceBase����г��ʱ����
			continue;
		}

		sprintf(chName, "%d��г����ֵ",   i);
		sprintf(chID, "harm%dAmp",   i);
		pHarmSerialize->xml_serialize(chName,   chID,   chUnit,   "number",   pHarm->Harm[i].fAmp);

		pHarm->Harm[i].nSelectIndex = nSelectIndex++;//��2��г����ʼ����ѡ�еĵ��Ӳ���
		pHarm->Harm[i].fFreq    =    pPara->m_fBaseFre   *   i;
	}

	pHarmSerialize->xml_serialize("ֱ������",   "DC",   chUnit,   "number",   pHarm->Harm[0].fAmp);
}

void stt_xml_serialize(tmt_LightPara *pPara, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("��Դ����ӳ�俪����,1-8:����1-8","UseBi","","number",pPara->m_nUseBi);
	pXmlSierialize->xml_serialize("��Դ��������ʱ���ϵ 0:������ǰ 1:��Դ��ǰ","DelayType","","number",pPara->m_nDelayType);
	pXmlSierialize->xml_serialize("��ǰʱ�� ����","DelayTime","","number",pPara->m_fDelayTime);

	pXmlSierialize->xml_serialize("ģʽѡ��,0-��Ծ,1-����","Mode","","number",pPara->m_nMode);
	pXmlSierialize->xml_serialize("����ʱ��,��λms","Time","","number",pPara->m_nTime);
	pXmlSierialize->xml_serialize("��Դѡ��,0-�Ϲ�,1-�׹�","Type","","number",pPara->m_nType);
	pXmlSierialize->xml_serialize("�Ϲ��ǿ","Data0","","number",pPara->m_nData0);
	pXmlSierialize->xml_serialize("�׹��ǿ","Data1","","number",pPara->m_nData1);
	pXmlSierialize->xml_serialize("����Ƶ��","_BaseFre","Hz","number",pPara->m_fBaseFre);

	CString strID;
	for(int nIndex=0;nIndex<6;nIndex++)
	{
		strID.Format(_T("I%d"),nIndex+1);
		stt_xml_serialize("", strID, nIndex, pPara, pXmlSierialize);
	}

	pXmlSierialize->xml_serialize("�����λ��,0-��ֹͣʵ��,1-ֹͣʵ��","BinStop","","number",pPara->m_nBinStop);
	pXmlSierialize->xml_serialize("�����߼�,0:�����,1:������","_AndOr","","InPutLogic_Psu",pPara->m_nBinLogic);
	stt_xml_serialize_binary_in(pPara->m_binIn,pXmlSierialize);
	stt_xml_serialize_binary_out(pPara->m_binOut, pXmlSierialize);
}

void stt_xml_serialize_act_rcd(tmt_LightResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//������¼,���64��,����ʵ�ʶ������,�����ܵĶ�����Ϣ
{
	CSttXmlSerializeBase *pXmlActRcddata = pXmlSierialize->xml_serialize("ActRcd", "ActRcd", "ActRcd", stt_ParaGroupKey());

	if (pXmlActRcddata == NULL)
	{
		return;
	}

	CString strName,strID,strTemp,strTmp2;
	CString str1 = _T("����");
	CString str2 = _T("��");
	CString str3 = _T("�ζ���ʱ��");

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
	pXmlSierialize->xml_serialize("�������","TripFlag","","number",pResults->m_nTripFlag);
	pXmlSierialize->xml_serialize("����ʱ��","TripTime","","number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("����ֵ","ActValue","","number",pResults->m_fActValue);

	CString strName,strID,strTemp;
	CString str1 = _T("����");
	CString str2 = _T("���״̬");

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
