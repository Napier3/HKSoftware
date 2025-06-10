#include "stdafx.h"
#include "tmt_dig_replay_test.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

long tmt_dig_replay_para::GetUseFiberNum()
{
	long nUseFiberNum = 0;
	long nFiberUse[DIG_REPLAY_FIBER_MAX_NUM];
	memset(nFiberUse,0,sizeof(long)*DIG_REPLAY_FIBER_MAX_NUM);

	for (int nCBIndex = 0;nCBIndex<DIG_REPLAY_CB_MAX_NUM;nCBIndex++)
	{
		if ((nCBIndex < m_nCBNum_SV92)&&(m_oCB_SV92[nCBIndex].m_nSelCB))//�ڿ��ƿ�������Χ��,���Ҹÿ��ƿ鱻ѡ��
		{
			for (int nFiberIndex = 0;nFiberIndex<m_oCB_SV92[nCBIndex].m_nFiberNum;nFiberIndex++)
			{
				nFiberUse[m_oCB_SV92[nCBIndex].m_oFiberIndex[nFiberIndex]] = 1;
			}
		}

		if ((nCBIndex<m_nCBNum_GOOSE)&&(m_oCB_GOOSE[nCBIndex].m_nSelCB))//�ڿ��ƿ�������Χ��,���Ҹÿ��ƿ鱻ѡ��
		{
			for (int nFiberIndex = 0;nFiberIndex<m_oCB_GOOSE[nCBIndex].m_nFiberNum;nFiberIndex++)
			{
				nFiberUse[m_oCB_GOOSE[nCBIndex].m_oFiberIndex[nFiberIndex]] = 1;
			}
		}
	}

	for (int nFiberIndex = 0;nFiberIndex<DIG_REPLAY_FIBER_MAX_NUM;nFiberIndex++)
	{
		if (nFiberUse[nFiberIndex])
		{
			nUseFiberNum++;
		}
	}

	return nUseFiberNum;
}

long tmt_dig_replay_para::GetTotalPkgNum(long nFiberPortIndex)
{
	long nTotalPkgNum = 0;

	for (int nCBIndex = 0;nCBIndex<DIG_REPLAY_CB_MAX_NUM;nCBIndex++)
	{
		if ((nCBIndex < m_nCBNum_SV92)&&(m_oCB_SV92[nCBIndex].m_nSelCB))//�ڿ��ƿ�������Χ��,���Ҹÿ��ƿ鱻ѡ��
		{
			for (int nFiberIndex = 0;nFiberIndex<m_oCB_SV92[nCBIndex].m_nFiberNum;nFiberIndex++)
			{
				if (nFiberPortIndex == m_oCB_SV92[nCBIndex].m_oFiberIndex[nFiberIndex])
				{
					if (m_oCB_SV92[nCBIndex].m_nBeginFrameIndex>0)
					{
						nTotalPkgNum += (m_oCB_SV92[nCBIndex].m_nEndFrameIndex - m_oCB_SV92[nCBIndex].m_nBeginFrameIndex + 1);
					}

					break;
				}
			}
		}

		if ((nCBIndex<m_nCBNum_GOOSE)&&(m_oCB_GOOSE[nCBIndex].m_nSelCB))//�ڿ��ƿ�������Χ��,���Ҹÿ��ƿ鱻ѡ��
		{
			for (int nFiberIndex = 0;nFiberIndex<m_oCB_GOOSE[nCBIndex].m_nFiberNum;nFiberIndex++)
			{
				if (nFiberPortIndex == m_oCB_GOOSE[nCBIndex].m_oFiberIndex[nFiberIndex])
				{
					if (m_oCB_GOOSE[nCBIndex].m_nBeginFrameIndex>0)
					{
						nTotalPkgNum += (m_oCB_GOOSE[nCBIndex].m_nEndFrameIndex - m_oCB_GOOSE[nCBIndex].m_nBeginFrameIndex + 1);
					}

					break;
				}
			}
		}
	}

	return nTotalPkgNum;
}


TMT_DIG_REPLAY_CB* tmt_dig_replay_para::FindTotalPkgCtrl_SV(long nAppID)
{
	TMT_DIG_REPLAY_CB *pReplayCB_SV  = NULL ;

	for (int nCBIndex = 0;nCBIndex<DIG_REPLAY_CB_MAX_NUM;nCBIndex++)
	{
		if (nCBIndex < m_nCBNum_SV92)//SV���ƿ飬����ID���Ҷ�Ӧ�Ŀ��ƿ�
		{
			if(m_oCB_SV92[nCBIndex].m_nAppID == nAppID)
			{
				pReplayCB_SV = &m_oCB_SV92[nCBIndex];
				break;

			}
		}

	}

	return pReplayCB_SV;
}

TMT_DIG_REPLAY_CB* tmt_dig_replay_para::FindTotalPkgCtrl_GOOSE(long nAppID)
{
	TMT_DIG_REPLAY_CB *pReplayCB_GOOSE  = NULL ;

	for (int nCBIndex = 0;nCBIndex<DIG_REPLAY_CB_MAX_NUM;nCBIndex++)
	{
		if (nCBIndex<m_nCBNum_GOOSE)//�ڿ��ƿ�������Χ��,���Ҹÿ��ƿ鱻ѡ��
		{
			if(m_oCB_GOOSE[nCBIndex].m_nAppID == nAppID)
			{
				pReplayCB_GOOSE = &m_oCB_GOOSE[nCBIndex];
				break;

			}
		}
	}

	return pReplayCB_GOOSE;
}



BOOL tmt_dig_replay_para::HasPcapSendDatas()
{
	for (int nCBIndex = 0;nCBIndex<DIG_REPLAY_CB_MAX_NUM;nCBIndex++)
	{
		if ((nCBIndex < m_nCBNum_SV92)&&(m_oCB_SV92[nCBIndex].m_nSelCB))//�ڿ��ƿ�������Χ��,���Ҹÿ��ƿ鱻ѡ��
		{
			if ((m_oCB_SV92[nCBIndex].m_nFiberNum>0)&&(m_oCB_SV92[nCBIndex].m_nBeginFrameIndex>0))
			{
				return TRUE;
			}
		}

		if ((nCBIndex<m_nCBNum_GOOSE)&&(m_oCB_GOOSE[nCBIndex].m_nSelCB))//�ڿ��ƿ�������Χ��,���Ҹÿ��ƿ鱻ѡ��
		{
			if ((m_oCB_GOOSE[nCBIndex].m_nFiberNum>0)&&(m_oCB_GOOSE[nCBIndex].m_nBeginFrameIndex>0))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

long tmt_dig_replay_para::GetCurSelCtrlNum_SVGOOSE()
{
	long nMaxCtrlNum = m_nCBNum_SV92;

	if (nMaxCtrlNum<m_nCBNum_GOOSE)
	{
		nMaxCtrlNum = m_nCBNum_GOOSE;
	}

	long nCurrSelCtrlNum = 0;

	for (int nCBIndex = 0;nCBIndex<nMaxCtrlNum;nCBIndex++)
	{
		if ((nCBIndex < m_nCBNum_SV92)&&(m_oCB_SV92[nCBIndex].HasSendDatas()))//�ڿ��ƿ�������Χ��,���Ҹÿ��ƿ鱻ѡ��
		{
			nCurrSelCtrlNum++;
		}

		if ((nCBIndex<m_nCBNum_GOOSE)&&(m_oCB_GOOSE[nCBIndex].HasSendDatas()))//�ڿ��ƿ�������Χ��,���Ҹÿ��ƿ鱻ѡ��
		{
			nCurrSelCtrlNum++;
		}
	}

	return nCurrSelCtrlNum;
}

void tmt_dig_replay_para::InitAllCB_TotalFrames()
{
	//��ʼ�����п��ƿ����ʼ֡�ͽ���֡ 
	for (int nCBIndex = 0; nCBIndex<m_nCBNum_GOOSE;nCBIndex++ )
	{
		m_oCB_GOOSE[nCBIndex].m_nBeginFrameIndex = -1;
		m_oCB_GOOSE[nCBIndex].m_nEndFrameIndex = -1;
	}

	for (int nCBIndex = 0; nCBIndex<m_nCBNum_SV92;nCBIndex++ )
	{
		m_oCB_SV92[nCBIndex].m_nBeginFrameIndex = -1;
		m_oCB_SV92[nCBIndex].m_nEndFrameIndex = -1;
	}
}

void stt_xml_serialize_CB(TMT_DIG_REPLAY_CB *pDigReplayCB, int nIndex,const char *pGroupID,CSttXmlSerializeBase *pXmlSierialize)
{
	char chName[MAX_PATH],chID[MAX_PATH];
	sprintf(chName, "%s%d",pGroupID, nIndex+1);
	sprintf(chID, "%s%d", pGroupID,nIndex+1);

	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize(chName, chID, "CB", stt_ParaGroupKey());

	if (pSerialize == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pSerialize->xml_serialize("����(ѡ��ÿ��ƿ�)","Select","","number",pDigReplayCB->m_nSelCB);
	pSerialize->xml_serialize("���ƿ�����������","FiberNum","","number",pDigReplayCB->m_nFiberNum);
	pSerialize->xml_serialize("���ƿ�AppID","AppID","","number",pDigReplayCB->m_nAppID);
	pSerialize->xml_serialize("���ƿ������֡��","TotalFrames","","number",pDigReplayCB->m_nTotalFrames);
	pSerialize->xml_serialize("���ƿ������ʼ֡��(�����ƿ�������)","BeginFrameIndex","","number",pDigReplayCB->m_nBeginFrameIndex);
	pSerialize->xml_serialize("���ƿ��������֡��(�����ƿ�������)","EndFrameIndex","","number",pDigReplayCB->m_nEndFrameIndex);
	pSerialize->xml_serialize("���ƿ���ʱ����ֵ(��λ:us)","OffsetTime","","number",pDigReplayCB->m_fOffsetTime);
#else
	pSerialize->xml_serialize(/*"����(ѡ��ÿ��ƿ�)"*/g_sLangTxt_Native_SelCtrlBlock.GetString(),"Select","","number",pDigReplayCB->m_nSelCB);
	pSerialize->xml_serialize(/*"���ƿ�����������"*/g_sLangTxt_Native_CtrlBlkOutOptPortsCnt.GetString(),"FiberNum","","number",pDigReplayCB->m_nFiberNum);
	pSerialize->xml_serialize(/*"���ƿ�AppID"*/g_sLangTxt_Native_CtrlBlkAppID.GetString(),"AppID","","number",pDigReplayCB->m_nAppID);
	pSerialize->xml_serialize(/*"���ƿ������֡��"*/g_sLangTxt_Native_CtrlBlkOutTotalFrames.GetString(),"TotalFrames","","number",pDigReplayCB->m_nTotalFrames);
	pSerialize->xml_serialize(/*"���ƿ������ʼ֡��(�����ƿ�������)"*/g_sLangTxt_Native_CtrlBlkOutStartFrmNum.GetString(),"BeginFrameIndex","","number",pDigReplayCB->m_nBeginFrameIndex);
	pSerialize->xml_serialize(/*"���ƿ��������֡��(�����ƿ�������)"*/g_sLangTxt_Native_CtrlBlkOutEndFrmNum.GetString(),"EndFrameIndex","","number",pDigReplayCB->m_nEndFrameIndex);
	pSerialize->xml_serialize(/*"���ƿ���ʱ����ֵ(��λ:us)"*/g_sLangTxt_Native_CtrlBlkDelayCompValue.GetString(),"OffsetTime","","number",pDigReplayCB->m_fOffsetTime);
#endif
 	for (int nIndex=0; nIndex<pDigReplayCB->m_nFiberNum; nIndex++)
 	{
 		sprintf(chName, "Fiber%dIndex", nIndex+1);
		sprintf(chID, "Fiber%dIndex", nIndex+1);
 		pSerialize->xml_serialize(chName,chID,"","number",pDigReplayCB->m_oFiberIndex[nIndex]);
 	}
}

void stt_xml_serialize(tmt_DigReplayParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ֵ���ƿ�����","SV92_CBNum","","number",pParas->m_nCBNum_SV92);
	pXmlSierialize->xml_serialize("GOOSE���ƿ�����","GOOSE_CBNum","","number",pParas->m_nCBNum_GOOSE);
#else
	pXmlSierialize->xml_serialize(/*"����ֵ���ƿ�����"*/g_sLangTxt_Native_NumOfSVCBs.GetString(),"SV92_CBNum","","number",pParas->m_nCBNum_SV92);
	pXmlSierialize->xml_serialize(/*"GOOSE���ƿ�����"*/g_sLangTxt_Native_NumOfGCBs.GetString(),"GOOSE_CBNum","","number",pParas->m_nCBNum_GOOSE);
#endif

	int nIndex = 0;
	char chName[MAX_PATH],chID[MAX_PATH];

	for (nIndex=0; nIndex<pParas->m_nCBNum_SV92; nIndex++)
	{
		stt_xml_serialize_CB(&pParas->m_oCB_SV92[nIndex],nIndex,"SmpValue",pXmlSierialize);
	}

	for (nIndex=0; nIndex<pParas->m_nCBNum_GOOSE; nIndex++)
	{
		stt_xml_serialize_CB(&pParas->m_oCB_GOOSE[nIndex],nIndex,"GOOSE",pXmlSierialize);
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��������","TriggerType","","number",pParas->m_nTripType);
	pXmlSierialize->xml_serialize("SV�ط�ģʽ(0:��ʱ����,1:�ȼ��,2:�Զ���)","ReplayMode_SV","","number",pParas->m_nReplayMode_SV);
	pXmlSierialize->xml_serialize("GOOSE�ط�ģʽ(0:��ʱ����,1:�ȼ��)","ReplayMode_GOOSE","","number",pParas->m_nReplayMode_GOOSE);
	pXmlSierialize->xml_serialize("SV�ȼ���طż��ʱ��(us)","EqualIntervalTimeSV","","number",pParas->m_fEqualIntervalTimeSV);
	pXmlSierialize->xml_serialize("GOOSE�ȼ���طż��ʱ��(us)","EqualIntervalTimeGOOSE","","number",pParas->m_fEqualIntervalTimeGOOSE);
	pXmlSierialize->xml_serialize("�Զ���طŶ���ֵ(us)","ShakeValue","","number",pParas->m_fShakeValue);
	pXmlSierialize->xml_serialize("�Ƿ�ѭ��(0��ѭ��,1ѭ��)","IsLoop","","number",pParas->m_nIsLoop);
	pXmlSierialize->xml_serialize("ѭ������","LoopNum","","number",pParas->m_nLoopNum);
	pXmlSierialize->xml_serialize("�ط�������������(0ȫ���ط�,1���ֻط�)","ReplayIntervalType","","number",pParas->m_nReplayIntervalType);

	pXmlSierialize->xml_serialize("�����ʼ֡��(ȫ�����ƿ�����)","TotalFrameBeginIndex","","number",pParas->m_nTotalFrameBeginIndex);
	pXmlSierialize->xml_serialize("�������֡��(ȫ�����ƿ�����)","TotalFrameEndIndex","","number",pParas->m_nTotalFrameEndIndex);

	pXmlSierialize->xml_serialize("GPS����ʱ�̣�ʱ��", "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣��֣�", "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize("GPS����ʱ�̣��룩", "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);
	pXmlSierialize->xml_serialize("���ʱ��(s)","OutPutTime","","number",pParas->m_fOutPutTime);


	pXmlSierialize->xml_serialize("�����߼�", "AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/*"��������"*/g_sLangTxt_State_TrigerCondition.GetString(),"TriggerType","","number",pParas->m_nTripType);
	pXmlSierialize->xml_serialize(/*"SV�ط�ģʽ(0:��ʱ����,1:�ȼ��,2:�Զ���)"*/g_sLangTxt_Native_SVReplayMode.GetString(),"ReplayMode_SV","","number",pParas->m_nReplayMode_SV);
	pXmlSierialize->xml_serialize(/*"GOOSE�ط�ģʽ(0:��ʱ����,1:�ȼ��)"*/g_sLangTxt_Native_GOOSEReplayMode.GetString(),"ReplayMode_GOOSE","","number",pParas->m_nReplayMode_GOOSE);
	pXmlSierialize->xml_serialize(/*"SV�ȼ���طż��ʱ��(us)"*/g_sLangTxt_Native_SVEqReplayIntervalTime_us.GetString(),"EqualIntervalTimeSV","","number",pParas->m_fEqualIntervalTimeSV);
	pXmlSierialize->xml_serialize(/*"GOOSE�ȼ���طż��ʱ��(us)"*/g_sLangTxt_Native_GOOSEEqReplayIntervalTime_us.GetString(),"EqualIntervalTimeGOOSE","","number",pParas->m_fEqualIntervalTimeGOOSE);
	pXmlSierialize->xml_serialize(/*"�Զ���طŶ���ֵ(us)"*/g_sLangTxt_Native_CustomReplayJitter_us.GetString(),"ShakeValue","","number",pParas->m_fShakeValue);
	pXmlSierialize->xml_serialize(/*"�Ƿ�ѭ��(0��ѭ��,1ѭ��)"*/g_sLangTxt_Native_LoopingFlag.GetString(),"IsLoop","","number",pParas->m_nIsLoop);
	pXmlSierialize->xml_serialize(/*"ѭ������"*/g_sLangTxt_State_RepeatTimes.GetString(),"LoopNum","","number",pParas->m_nLoopNum);
	pXmlSierialize->xml_serialize(/*"�ط�������������(0ȫ���ط�,1���ֻط�)"*/g_sLangTxt_Native_ReplayIntervalType.GetString(),"ReplayIntervalType","","number",pParas->m_nReplayIntervalType);

	pXmlSierialize->xml_serialize(/*"�����ʼ֡��(ȫ�����ƿ�����)"*/g_sLangTxt_Native_StartFrameNum.GetString(),"TotalFrameBeginIndex","","number",pParas->m_nTotalFrameBeginIndex);
	pXmlSierialize->xml_serialize(/*"�������֡��(ȫ�����ƿ�����)"*/g_sLangTxt_Native_EndFrameNum.GetString(),"TotalFrameEndIndex","","number",pParas->m_nTotalFrameEndIndex);

	pXmlSierialize->xml_serialize(/*"GPS����ʱ��(ʱ)"*/g_sLangTxt_Native_GPSTriggerTime_hr.GetString(), "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize(/*"GPS����ʱ��(��)"*/g_sLangTxt_Native_GPSTriggerTime_min.GetString(), "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize(/*"GPS����ʱ��(��)"*/g_sLangTxt_Native_GPSTriggerTime_sec.GetString(), "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);
	pXmlSierialize->xml_serialize(/*"���ʱ��(s)"*/g_sLangTxt_Native_OutputDuration_sec.GetString(),"OutPutTime","","number",pParas->m_fOutPutTime);


	pXmlSierialize->xml_serialize(/*"�����߼�"*/g_sLangTxt_Native_InLogic.GetString(), "AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#endif

    char pszBInName[MAX_BINARYIN_COUNT] = "ABCDEFGHIJKLMNOP";
    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(nIndex = 0; nIndex < nCnt; nIndex++)
	{
#ifdef NOT_USE_XLANGUAGE
		sprintf(chName, "����%cѡ��", pszBInName[nIndex]);
#else
		sprintf(chName, /*"����%cѡ��"*/g_sLangTxt_Native_InputSelection.GetString(), pszBInName[nIndex]);
#endif
		sprintf(chID, "BIn%c", pszBInName[nIndex]);
		pXmlSierialize->xml_serialize(chName,chID,"","BOOL",pParas->m_binIn[nIndex].nSelect);
	}

	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DigReplayTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		stt_xml_serialize(&(pTests->m_oReplayParas),  pXmlParas);	//�ļ��Ķ�д
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
//		stt_xml_serialize(&pTests->m_oReplayResults,  pXmlResults);
	}

	return pXmlParas;
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_DigReplayTest()
{
    tmt_DigReplayParas oReplayTest;
	oReplayTest.m_nCBNum_SV92 = 2;
	oReplayTest.m_nCBNum_GOOSE = 2;
	oReplayTest.m_oCB_SV92[0].m_nFiberNum = 6;
	oReplayTest.m_oCB_GOOSE[1].m_nFiberNum = 6;
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oReplayTest, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("DigReplayTest.xml");
    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
