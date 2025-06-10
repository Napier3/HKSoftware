#include "stdafx.h"
#include "tmt_rtdata_def.h"
#include "tmt_result_def.h"
#include"../../SttCmd/SttTestCmd.h"
#include"../../../../Module/API/GlobalConfigApi.h"
#include "SttSystemConfig.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

void stt_xml_serialize(PSTT_RTDATA_EVENT_INFO pRtDataCh,const CString &strName,const CString &strID, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pChSerialize =pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "channel", stt_ParaGroupKey());

	if (pChSerialize == NULL)
	{
		return;
	}

	double fval=pRtDataCh->m_fMag*1.0;//保护pRtDataCh->m_fMag是float有效类型
#ifdef NOT_USE_XLANGUAGE
	pChSerialize->xml_serialize("幅值", "mag","","number",fval);
	fval=pRtDataCh->m_fAng*1.0;
	pChSerialize->xml_serialize("相位", "ang","","number",fval);
	fval=pRtDataCh->m_fFreq*1.0;
	pChSerialize->xml_serialize("频率", "freq","","number",fval);
#else
  pChSerialize->xml_serialize(/* "幅值" */ g_sLangTxt_Native_Amplitude.GetString(), "mag", "", "number", fval);
  fval = pRtDataCh->m_fAng * 1.0;
  pChSerialize->xml_serialize(/* "相位" */ g_sLangTxt_Native_Phase.GetString(), "ang", "", "number", fval);
  fval = pRtDataCh->m_fFreq * 1.0;
  pChSerialize->xml_serialize(/* "频率" */ g_sLangTxt_Native_Freq.GetString(), "freq", "", "number", fval);
#endif
}

void stt_xml_serialize_rtdata(PSTT_RTDATA_EVENT pRtData, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pXmlRtdata = pXmlSierialize->xml_serialize("Rtdata", "Rtdata", "Rtdata", stt_ParaGroupKey());

	if (pXmlRtdata == NULL)
	{
		return;
	}

#ifdef _PSX_QT_LINUX_
    double dTime = pRtData->oTime.dTime + g_theSystemConfig->m_nTimeZone*3600;
#else
	double dTime = pRtData->oTime.dTime;
#endif
#ifdef NOT_USE_XLANGUAGE
    pXmlRtdata->xml_serialize("绝对时间",TMT_RESULT_ID_Time,"","double",dTime);
	pXmlRtdata->xml_serialize("相对时间",TMT_RESULT_ID_RealTime,"","double",pRtData->oTime.dRealTime);
#else
  pXmlRtdata->xml_serialize(/* "绝对时间" */ g_sLangTxt_Native_AbsoluteTime.GetString(), TMT_RESULT_ID_Time, "", "double", dTime);
  pXmlRtdata->xml_serialize(/* "相对时间" */ g_sLangTxt_Native_RelativeTime.GetString(), TMT_RESULT_ID_RealTime, "", "double", pRtData->oTime.dRealTime);
#endif
	CString strName,strID;

	for(int nIndex=0;nIndex<pRtData->m_nCurChCount && nIndex<MAX_CURRENT_COUNT;nIndex++)
	{
		strName.Format(_T("I%ld"),pRtData->m_oCurCh[nIndex].m_nIndex+1);
		strID.Format(_T("I%ld"),pRtData->m_oCurCh[nIndex].m_nIndex+1);
		stt_xml_serialize(&pRtData->m_oCurCh[nIndex],strName,strID,pXmlRtdata);
	}

	for(int nIndex=0;nIndex<pRtData->m_nVolChCount && nIndex<MAX_VOLTAGE_COUNT;nIndex++)
	{
		strName.Format(_T("U%ld"),pRtData->m_oVolCh[nIndex].m_nIndex+1);
		strID.Format(_T("U%ld"),pRtData->m_oVolCh[nIndex].m_nIndex+1);
		stt_xml_serialize(&pRtData->m_oVolCh[nIndex],strName,strID,pXmlRtdata);
	}

	if(pRtData->m_nHasFaultVolCur)
	{
		stt_xml_serialize(&pRtData->m_oFaultVolCh,_T("Uf"),_T("Uf"),pXmlRtdata);
		stt_xml_serialize(&pRtData->m_oFaultCurCh,_T("If"),_T("If"),pXmlRtdata);
	}
}


void stt_xml_serialize_write_RtDataChs(long nCurChNum,long nVolChNum)
{
	STT_RTDATA_EVENT oRtDataChs;
	oRtDataChs.m_nCurChCount = nCurChNum;
	oRtDataChs.m_nVolChCount = nVolChNum;
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize_rtdata(&oRtDataChs, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("RtDataChs.xml");
	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
