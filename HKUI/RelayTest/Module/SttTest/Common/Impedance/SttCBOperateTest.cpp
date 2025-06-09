#include "stdafx.h"
#include"SttCBOperateTest.h"
#include "../SttStateTest.h"
#include "../SttSystemConfig.h"

CString CSttCBOperateTest::m_strMacroName = "整组传动测试";
CString CSttCBOperateTest::m_strMacroID = STT_MACRO_ID_PsuCBOperate;
CString CSttCBOperateTest::m_strFilePostFix = "scbo";
CString CSttCBOperateTest::m_strMacroVer ="1.0";

CSttCBOperateTest::CSttCBOperateTest() : CSttImpBaseTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
	Init();
}

void CSttCBOperateTest::Init()
{ 
	CSttImpBaseTest::Init();
// 	m_pImpBaseParas->m_oStateParas.m_nStateNumbers = 8;
// 	m_pImpBaseParas->m_oStateParas.init(8);
	tmt_CBOperateParas::init();
	m_oResults.init();
	m_fUnom = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
}

CSttCBOperateTest::~CSttCBOperateTest(void)
{

}

void CSttCBOperateTest::AfterSetParameter()
{
	CSttImpBaseTest::AfterSetParameter();
	m_pImpBaseParas->m_bSearchNext = FALSE;
	m_pImpBaseParas->m_pStateParas->m_paraState[0].m_tGps = m_tGps;
}

long CSttCBOperateTest::CalReport(UINT nState)
{
	long nBeginIndex,nEndIndex;

	if (m_nBinSelect == 1)
	{
		nBeginIndex = 4;
	}
	else
	{
		nBeginIndex = 0;
	}

	nEndIndex = (nBeginIndex+4);
	
	long nTripIndex = 0;
	float fTransFaultActTime = 0.0f;
	float fTransTime[8] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	bool bHasMapReclose = false;

	for (int nIndex = nBeginIndex;nIndex<nEndIndex;nIndex++)
	{
		if (m_nDInputState[nIndex] == STT_IMPEDANCE_BIN_STATE_RECLOCE)
		{
			if(m_oImpBaseResults.m_resultState[2].m_nAct)
			{
				m_oResults.SetRecloseTime(m_oImpBaseResults.m_resultState[2].m_frTimeBinAct[nIndex][0]);
			}
			bHasMapReclose = true;
		} 
		else
		{
			if(m_oImpBaseResults.m_resultState[1].m_nAct)
			{
				m_oResults.SetFault1TripTime(nTripIndex,m_nDInputState[nIndex],m_oImpBaseResults.m_resultState[1].m_frTimeBinAct[nIndex][0],bHasMapReclose);
			}

			if (m_nFaultProperty == 0)//瞬时性故障
			{
				if(m_oImpBaseResults.m_resultState[3].m_nAct)
				{
					m_oResults.SetFault2TripTime(nTripIndex,m_nDInputState[nIndex],m_oImpBaseResults.m_resultState[3].m_frTimeBinAct[nIndex][0]);
				}
			}
			else
			{
				if(m_oImpBaseResults.m_resultState[4].m_nAct)
				{
					m_oResults.SetFault2TripTime(nTripIndex,m_nDInputState[nIndex],m_oImpBaseResults.m_resultState[4].m_frTimeBinAct[nIndex][0]);
				}
			}

			if (m_oImpBaseResults.m_resultState[5].m_frTimeBinAct[nIndex][0]>fTransFaultActTime)//判断转换故障态是否有动作时间
			{
				fTransFaultActTime = m_oImpBaseResults.m_resultState[5].m_frTimeBinAct[nIndex][0];
			}

			if(m_oImpBaseResults.m_resultState[1].m_nAct)
			{
				m_oResults.SetFaultTripTime(fTransTime,nTripIndex,m_nDInputState[nIndex],m_oImpBaseResults.m_resultState[1].m_frTimeBinAct[nIndex][0],bHasMapReclose);
			}
//			fTransTime[nTripIndex] = m_oImpBaseResults.m_resultState[5].m_frTimeBinAct[nIndex][0];
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("开入%ld,状态1动作时间(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[0].m_frTimeBinAct[nIndex][0],
// 			m_oImpBaseResults.m_resultState[0].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("开入%ld,状态2动作时间(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[1].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[1].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("开入%ld,状态3动作时间(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[2].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[2].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("开入%ld,状态4动作时间(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[3].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[3].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("开入%ld,状态5动作时间(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[4].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[4].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("开入%ld,状态6动作时间(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[5].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[5].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("开入%ld,状态7动作时间(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[6].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[6].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("开入%ld,状态8动作时间(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[7].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[7].m_frTimeBinAct[nIndex][1]);
			nTripIndex++;
		}
	}

	if ((fTransFaultActTime>PRECISION_COMPARE)&&(m_bTransFault))//如果大于最小精度值,说明转换故障态动作了  zhouhj 20220808
	{
		float fFirstTripTime = m_oResults.GetFirstTripTime();

		if (fFirstTripTime<PRECISION_COMPARE)//如果第一次跳闸时间为0,且已经发生转换故障,则在第一次故障时发生转换
		{
			for (int nPhaseIndex = 0;nPhaseIndex<3;nPhaseIndex++)
			{
				if (fTransTime[nPhaseIndex]>PRECISION_COMPARE)
				{
					m_oResults.m_fFirstTripTime[nPhaseIndex] = fTransTime[nPhaseIndex] + m_fTransTime;
				}
			}
		}
		else if (m_oResults.m_fSecondTripTime<PRECISION_COMPARE)//如果第二次跳闸时间为0,且已经发生转换故障,则在第二次故障时发生转换
		{
			if ((m_fTransTime-fFirstTripTime-m_oResults.m_fRecloseTime)>0)
			{
				m_oResults.m_fSecondTripTime = fTransFaultActTime + (m_fTransTime-fFirstTripTime-m_oResults.m_fRecloseTime);
			} 
			else
			{
				m_oResults.m_fSecondTripTime = fTransFaultActTime;
			}
		}

// 		if (m_oResults.m_fRecloseTime>PRECISION_COMPARE)//判断重合闸有没有动作,如果重合闸动作了,则为第二次故障发生的转换故障
// 		{
// 			m_oResults.m_fSecondTripTime += fTransFaultActTime;
// 		} 
// 		else
// 		{
// 			m_oResults.m_fFirstTripTime[0] += fTransTime[0];
// 			m_oResults.m_fFirstTripTime[1] += fTransTime[1];
// 			m_oResults.m_fFirstTripTime[2] += fTransTime[2];
// 		}
	}

	m_oResults.m_nActA = (m_oResults.m_fFirstTripTime[0]-0.0001) > 0 ? 1 : 0;
	m_oResults.m_nActB = (m_oResults.m_fFirstTripTime[1]-0.0001) > 0 ? 1 : 0;
	m_oResults.m_nActC = (m_oResults.m_fFirstTripTime[2]-0.0001) > 0 ? 1 : 0;
	m_oResults.m_nActD = (m_oResults.m_fRecloseTime-0.0001) > 0 ? 1 : 0;
	m_oResults.m_nActAcc = (m_oResults.m_fSecondTripTime-0.0001) > 0 ? 1 : 0;

	m_oResults.m_fTripTime = 0;

	for (int i=0;i<8;i++)
	{
		m_oResults.m_fTripTime = GetMaxValue(m_oResults.m_fTripTime,m_oResults.m_fFirstTripTime[i]);
	}

	m_oResults.m_fImp = m_fImpedance[0];
	m_oResults.m_fImpAngle = m_fImpAngle[0];
//	Global_AddSimulateBreakTimeToResults(this,&m_oResults);//zhouhj 20211105 在测试结果中增加模拟断路器的延时时间  20220615 zhouhj北京要求实际动作时间中去除模断时间的添加与老版PowerTest一致
	return 0;
}

void CSttCBOperateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_CBOperateParas*)this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttCBOperateTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
// 	stt_xml_serialize(&m_oImpBaseResults, m_pImpBaseParas->m_pStateParas->m_nRepeatNumbers,
// 		pXmlSerialize,m_pImpBaseParas->m_pStateParas->m_nBinTripRef);

	stt_xml_serialize(&m_oResults, pXmlSerialize);
}

long CSttCBOperateTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttCBOperateTest::TranslateToStateParas_TimeCtrl_Trans()
{
	float fStdLN_Vol = m_fUnom/*g_theSystemConfig->m_fVNom/SQRT3*/;//计算标准相电压,一般57.735V
	Complex p1;
	Complex	oComplexUI[2][4];
	float fCurTime_AfterFualt = 0;

	tmt_StatePara *pState1 = &m_pImpBaseParas->m_pStateParas->m_paraState[1];
	tmt_StatePara *pState2 = &m_pImpBaseParas->m_pStateParas->m_paraState[2];
	tmt_StatePara *pState3 = &m_pImpBaseParas->m_pStateParas->m_paraState[3];
	tmt_StatePara *pState4 = &m_pImpBaseParas->m_pStateParas->m_paraState[4];
	tmt_StatePara *pState5 = &m_pImpBaseParas->m_pStateParas->m_paraState[5];

	pState1->m_fTimeState = m_fMaxFaultTime;
	pState1->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	pState1->m_fTimeAfterTrigger = 0;

	if (m_bCBSimulation)
	{
		pState1->m_fTimeState += m_fCBTripTime;
	}

	fCurTime_AfterFualt = pState1->m_fTimeState;

	if (m_fMaxFaultTime>m_fTransTime)
	{
		pState1->m_fTimeState = m_fTransTime;
		//////////////////////////////////////////////////////////////////////////
		//状态3：转换故障
		SetStateParas_TransFault(pState2,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState2->m_fTimeState = m_fMaxFaultTime - m_fTransTime;
		pState2->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState2->m_fTimeAfterTrigger = 0;

		if (m_bCBSimulation)
		{
			pState2->m_fTimeState += m_fCBTripTime;
		}
		//////////////////////////////////////////////////////////////////////////
		//状态4：跳闸后,等待重合闸状态
		SetStateParas_AfterFirstTrip(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState = m_fPostFaultTime;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;

		if (m_bCBSimulation)
		{
			pState3->m_fTimeState += m_fCBCloseTime;
		}

		if (m_nRecloseMode == 2)//如果为不重合,则直接结束
		{
			m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 4;
			return;
		}
		//////////////////////////////////////////////////////////////////////////
		//状态5：重合后

		if (m_nFaultProperty == 0)//瞬时性故障
		{
			SetStateParas_AfterRecoseTransient(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
			pState4->m_fTimeState = m_fRecloseTime;
			pState4->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
			pState4->m_fTimeAfterTrigger = 0;
			m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 5;
			return;
		} 
		else//永久性故障
		{
			SetStateParas_TransFault(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);//因为之前已进入转换故障,故此时也为永久性故障
			pState4->m_fTimeState = m_fRecloseTime;
			pState4->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
			pState4->m_fTimeAfterTrigger = 0;

			if (m_bCBSimulation)
			{
				pState4->m_fTimeState += m_fCBTripTime;
			}

			//////////////////////////////////////////////////////////////////////////
			//状态6：加速后
			SetStateParas_AccTrip(pState5,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
			pState5->m_fTimeState = m_fTAfterAccTrig;
			m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 6;
		}
		//////////////////////////////////////////////////////////////////////////
		return;
	} 

	//////////////////////////////////////////////////////////////////////////
	//状态3：跳闸后,等待重合闸状态
	SetStateParas_AfterFirstTrip(pState2,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	pState2->m_fTimeState = m_fPostFaultTime;
	pState2->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;

	if (m_bCBSimulation)
	{
		pState2->m_fTimeState += m_fCBCloseTime;
	}

	fCurTime_AfterFualt += pState2->m_fTimeState;

	if (m_nRecloseMode == 2)//如果为不重合,则直接结束
	{
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 3;
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	//状态4：重合后

	if (fCurTime_AfterFualt>=m_fTransTime)//如果从故障开始后的时间大于转换时间,则目前已是转换故障态
	{
		//转换故障
		SetStateParas_TransFault(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState = m_fRecloseTime;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState3->m_fTimeAfterTrigger = 0;
		//////////////////////////////////////////////////////////////////////////
		//状态5：加速后
		SetStateParas_AccTrip(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState4->m_fTimeState = m_fTAfterAccTrig;
		pState4->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 5;
		return;
		//////////////////////////////////////////////////////////////////////////
	}
	else if ((m_fTransTime>=(fCurTime_AfterFualt+m_fRecloseTime))&&(m_nFaultProperty == 0))
	{
		//瞬时性故障-重合后-转换故障未来得及发生
		SetStateParas_AfterRecoseTransient(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState = m_fRecloseTime;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState3->m_fTimeAfterTrigger = 0;
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 4;
		return;
		//////////////////////////////////////////////////////////////////////////
	}
	else if ((m_fTransTime>=(fCurTime_AfterFualt+m_fRecloseTime))&&(m_nFaultProperty > 0))
	{
		///永久性故障-重合后-加速跳开前转换故障还未发生
		SetStateParas_AfterRecosePermanent(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState = m_fRecloseTime;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState3->m_fTimeAfterTrigger = 0;
		//////////////////////////////////////////////////////////////////////////
		//状态5：加速后
		SetStateParas_AccTrip(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState4->m_fTimeState = m_fTAfterAccTrig;
		pState4->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 5;
		return;
		//////////////////////////////////////////////////////////////////////////
	}

	//在重合时间段内发生转换故障

	if (m_nFaultProperty == 0)//瞬时性故障
	{
		SetStateParas_AfterRecoseTransient(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState = m_fTransTime - fCurTime_AfterFualt;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState3->m_fTimeAfterTrigger = 0;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//状态5-转换故障
		SetStateParas_TransFault(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState4->m_fTimeState = m_fRecloseTime - (m_fTransTime - fCurTime_AfterFualt);
		pState4->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState4->m_fTimeAfterTrigger = 0;
		//////////////////////////////////////////////////////////////////////////
		//状态6：加速后
		SetStateParas_AccTrip(pState5,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState5->m_fTimeState = m_fTAfterAccTrig;
		pState5->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 6;
		return;
		//////////////////////////////////////////////////////////////////////////
	} 
	else//永久性故障
	{
		///永久性故障-重合后-加速跳开前转换故障还未发生
		SetStateParas_AfterRecosePermanent(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState =  m_fTransTime - fCurTime_AfterFualt;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState3->m_fTimeAfterTrigger = 0;
		//////////////////////////////////////////////////////////////////////////
		//状态5-转换故障
		SetStateParas_TransFault(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState4->m_fTimeState = m_fRecloseTime - (m_fTransTime - fCurTime_AfterFualt);
		pState4->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState4->m_fTimeAfterTrigger = 0;
		//////////////////////////////////////////////////////////////////////////
		//状态6：加速后
		SetStateParas_AccTrip(pState5,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState5->m_fTimeState = m_fTAfterAccTrig;
		pState5->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 6;
		return;
	}

	//////////////////////////////////////////////////////////////////////////
}

void CSttCBOperateTest::TranslateToStateParas_TimeCtrl_NotTrans()
{
	tmt_StatePara *pState1 = &m_pImpBaseParas->m_pStateParas->m_paraState[1];
	tmt_StatePara *pState2 = &m_pImpBaseParas->m_pStateParas->m_paraState[2];
	tmt_StatePara *pState3 = &m_pImpBaseParas->m_pStateParas->m_paraState[3];
	tmt_StatePara *pState4 = &m_pImpBaseParas->m_pStateParas->m_paraState[4];
	tmt_StatePara *pState5 = &m_pImpBaseParas->m_pStateParas->m_paraState[5];

	float fStdLN_Vol = m_fUnom/*g_theSystemConfig->m_fVNom/SQRT3*/;//计算标准相电压,一般57.735V
	Complex p1;
	Complex	oComplexUI[2][4];
	pState1->m_fTimeState = m_fMaxFaultTime;
	pState1->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	pState1->m_fTimeAfterTrigger = 0;

	if (m_bCBSimulation)
	{
		pState1->m_fTimeState += m_fCBTripTime;
	}

	//////////////////////////////////////////////////////////////////////////
	//状态3：跳闸后,等待重合闸状态
	SetStateParas_AfterFirstTrip(pState2,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	pState2->m_fTimeState = m_fPostFaultTime;
	pState2->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;

	if (m_bCBSimulation)
	{
		pState2->m_fTimeState += m_fCBCloseTime;
	}

	if (m_nRecloseMode == 2)//如果为不重合,则直接结束
	{
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 3;
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	//状态4：重合后

	if (m_nFaultProperty == 0)//瞬时性故障
	{
		SetStateParas_AfterRecoseTransient(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState = m_fRecloseTime;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState3->m_fTimeAfterTrigger = 0;
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 4;
		return;
	} 
	else//永久性故障
	{
		SetStateParas_AfterRecosePermanent(pState3,
				this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState = m_fRecloseTime;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState3->m_fTimeAfterTrigger = 0;

		if (m_bCBSimulation)
		{
			pState3->m_fTimeState += m_fCBTripTime;
		}

		//////////////////////////////////////////////////////////////////////////
		//状态5：加速后
		SetStateParas_AccTrip(pState4,
				this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState4->m_fTimeState = m_fTAfterAccTrig;
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 5;
	}
	//////////////////////////////////////////////////////////////////////////
}

void CSttCBOperateTest::TranslateToStateParas()
{
	m_pImpBaseParas->m_fImpBaseFaultTime = m_fMaxFaultTime;
	m_pImpBaseParas->m_fImpBaseTripTime = m_fPostFaultTime;
	m_pImpBaseParas->m_fImpBaseTransTime = m_fTransTime;
	m_pImpBaseParas->m_bImpBaseIsPermanent = m_nFaultProperty;
	m_pImpBaseParas->m_bImpBaseTransFault = m_bTransFault;
	m_pImpBaseParas->m_fImpBaseReclosingTime = m_fRecloseTime;
	m_pImpBaseParas->m_fImpBaseStopTime = 1.0f;
	m_pImpBaseParas->m_pStateParas->m_bSequence = FALSE;

 	float fStdLN_Vol = m_fUnom/*g_theSystemConfig->m_fVNom/SQRT3*/;//计算标准相电压,一般57.735V
	m_pImpBaseParas->m_pStateParas->m_nPlusDC = m_bIPlusDC;
	m_pImpBaseParas->m_pStateParas->m_fTao = m_oFaultCalculatTool.CalImpPlusDC_Tao(m_fImpedance[0],m_fImpAngle[0]);

	tmt_StatePara *pState0 = &m_pImpBaseParas->m_pStateParas->m_paraState[0];
	tmt_StatePara *pState1 = &m_pImpBaseParas->m_pStateParas->m_paraState[1];
	tmt_StatePara *pState2 = &m_pImpBaseParas->m_pStateParas->m_paraState[2];
	tmt_StatePara *pState3 = &m_pImpBaseParas->m_pStateParas->m_paraState[3];
	tmt_StatePara *pState4 = &m_pImpBaseParas->m_pStateParas->m_paraState[4];
	tmt_StatePara *pState5 = &m_pImpBaseParas->m_pStateParas->m_paraState[5];
	tmt_StatePara *pState6 = &m_pImpBaseParas->m_pStateParas->m_paraState[6];
	tmt_StatePara *pState7 = &m_pImpBaseParas->m_pStateParas->m_paraState[7];
	TranslateToStateParas_FaultIncMode(this);
 	//////////////////////////////////////////////////////////////////////////
 	//状态1：故障前状态
 	Complex p1;
 	Complex	oComplexUI[2][4];
	SetStateParas_PreFault(pState0,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	Global_SetStateBoutPreFault(m_pImpBaseParas->m_pStateParas->m_paraState,m_nStateBOut,
                                m_nOutputSwitchMode,m_nBinSelect,m_fBoutTimeTrig,m_fBoutHoldTime);
 	//////////////////////////////////////////////////////////////////////////

 	//状态2：故障状态
	SetStateParas_FirstFault(pState1,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	m_oResults.m_fFaultVol = m_fSCVoltage[0];
	m_oResults.m_fFaultCurrent = m_fSCCurrent[0];

	if (m_nTestProcCtrlMode == STT_CB_OPERATE_PROC_CTRL_TIME)
	{
		m_pImpBaseParas->m_pStateParas->m_bSequence = TRUE;

		if (m_bTransFault)
		{
			TranslateToStateParas_TimeCtrl_Trans();
		} 
		else
		{
			TranslateToStateParas_TimeCtrl_NotTrans();
		}

		return;
	}

	//////////////////////////////////////////////////////////////////////////
	//状态3：跳闸后,等待重合闸状态
	SetStateParas_AfterFirstTrip(pState2,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	//////////////////////////////////////////////////////////////////////////
	//状态4：重合后(瞬时)
	SetStateParas_AfterRecoseTransient(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	//////////////////////////////////////////////////////////////////////////
	//状态5：重合后(永久)
	SetStateParas_AfterRecosePermanent(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	//////////////////////////////////////////////////////////////////////////
	//状态6：转换故障
	SetStateParas_TransFault(pState5,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	//////////////////////////////////////////////////////////////////////////
	//状态7：加速后
	SetStateParas_AccTrip(pState6,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	//////////////////////////////////////////////////////////////////////////
	//状态8：停止态
	SetStateParas_StopTest(pState7,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	//////////////////////////////////////////////////////////////////////////
}




