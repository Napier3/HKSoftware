#include "stdafx.h"
#include"SttCBOperateTest.h"
#include "../SttStateTest.h"
#include "../SttSystemConfig.h"

CString CSttCBOperateTest::m_strMacroName = "���鴫������";
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
	m_fUnom = g_theSystemConfig->m_fVNom/SQRT3;//�����׼���ѹ,һ��57.735V
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

			if (m_nFaultProperty == 0)//˲ʱ�Թ���
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

			if (m_oImpBaseResults.m_resultState[5].m_frTimeBinAct[nIndex][0]>fTransFaultActTime)//�ж�ת������̬�Ƿ��ж���ʱ��
			{
				fTransFaultActTime = m_oImpBaseResults.m_resultState[5].m_frTimeBinAct[nIndex][0];
			}

			if(m_oImpBaseResults.m_resultState[1].m_nAct)
			{
				m_oResults.SetFaultTripTime(fTransTime,nTripIndex,m_nDInputState[nIndex],m_oImpBaseResults.m_resultState[1].m_frTimeBinAct[nIndex][0],bHasMapReclose);
			}
//			fTransTime[nTripIndex] = m_oImpBaseResults.m_resultState[5].m_frTimeBinAct[nIndex][0];
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("����%ld,״̬1����ʱ��(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[0].m_frTimeBinAct[nIndex][0],
// 			m_oImpBaseResults.m_resultState[0].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("����%ld,״̬2����ʱ��(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[1].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[1].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("����%ld,״̬3����ʱ��(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[2].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[2].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("����%ld,״̬4����ʱ��(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[3].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[3].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("����%ld,״̬5����ʱ��(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[4].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[4].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("����%ld,״̬6����ʱ��(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[5].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[5].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("����%ld,״̬7����ʱ��(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[6].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[6].m_frTimeBinAct[nIndex][1]);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("����%ld,״̬8����ʱ��(%f)(%f)."),nTripIndex,m_oImpBaseResults.m_resultState[7].m_frTimeBinAct[nIndex][0],
// 				m_oImpBaseResults.m_resultState[7].m_frTimeBinAct[nIndex][1]);
			nTripIndex++;
		}
	}

	if ((fTransFaultActTime>PRECISION_COMPARE)&&(m_bTransFault))//���������С����ֵ,˵��ת������̬������  zhouhj 20220808
	{
		float fFirstTripTime = m_oResults.GetFirstTripTime();

		if (fFirstTripTime<PRECISION_COMPARE)//�����һ����բʱ��Ϊ0,���Ѿ�����ת������,���ڵ�һ�ι���ʱ����ת��
		{
			for (int nPhaseIndex = 0;nPhaseIndex<3;nPhaseIndex++)
			{
				if (fTransTime[nPhaseIndex]>PRECISION_COMPARE)
				{
					m_oResults.m_fFirstTripTime[nPhaseIndex] = fTransTime[nPhaseIndex] + m_fTransTime;
				}
			}
		}
		else if (m_oResults.m_fSecondTripTime<PRECISION_COMPARE)//����ڶ�����բʱ��Ϊ0,���Ѿ�����ת������,���ڵڶ��ι���ʱ����ת��
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

// 		if (m_oResults.m_fRecloseTime>PRECISION_COMPARE)//�ж��غ�բ��û�ж���,����غ�բ������,��Ϊ�ڶ��ι��Ϸ�����ת������
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
//	Global_AddSimulateBreakTimeToResults(this,&m_oResults);//zhouhj 20211105 �ڲ��Խ��������ģ���·������ʱʱ��  20220615 zhouhj����Ҫ��ʵ�ʶ���ʱ����ȥ��ģ��ʱ���������ϰ�PowerTestһ��
	return 0;
}

void CSttCBOperateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_CBOperateParas*)this,pXmlSerialize);

	//2020-4-6  lijq  ��ȡ����ģʽ�£���Ҫ���г�ʼ��
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
	float fStdLN_Vol = m_fUnom/*g_theSystemConfig->m_fVNom/SQRT3*/;//�����׼���ѹ,һ��57.735V
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
		//״̬3��ת������
		SetStateParas_TransFault(pState2,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState2->m_fTimeState = m_fMaxFaultTime - m_fTransTime;
		pState2->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState2->m_fTimeAfterTrigger = 0;

		if (m_bCBSimulation)
		{
			pState2->m_fTimeState += m_fCBTripTime;
		}
		//////////////////////////////////////////////////////////////////////////
		//״̬4����բ��,�ȴ��غ�բ״̬
		SetStateParas_AfterFirstTrip(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState = m_fPostFaultTime;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;

		if (m_bCBSimulation)
		{
			pState3->m_fTimeState += m_fCBCloseTime;
		}

		if (m_nRecloseMode == 2)//���Ϊ���غ�,��ֱ�ӽ���
		{
			m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 4;
			return;
		}
		//////////////////////////////////////////////////////////////////////////
		//״̬5���غϺ�

		if (m_nFaultProperty == 0)//˲ʱ�Թ���
		{
			SetStateParas_AfterRecoseTransient(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
			pState4->m_fTimeState = m_fRecloseTime;
			pState4->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
			pState4->m_fTimeAfterTrigger = 0;
			m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 5;
			return;
		} 
		else//�����Թ���
		{
			SetStateParas_TransFault(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);//��Ϊ֮ǰ�ѽ���ת������,�ʴ�ʱҲΪ�����Թ���
			pState4->m_fTimeState = m_fRecloseTime;
			pState4->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
			pState4->m_fTimeAfterTrigger = 0;

			if (m_bCBSimulation)
			{
				pState4->m_fTimeState += m_fCBTripTime;
			}

			//////////////////////////////////////////////////////////////////////////
			//״̬6�����ٺ�
			SetStateParas_AccTrip(pState5,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
			pState5->m_fTimeState = m_fTAfterAccTrig;
			m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 6;
		}
		//////////////////////////////////////////////////////////////////////////
		return;
	} 

	//////////////////////////////////////////////////////////////////////////
	//״̬3����բ��,�ȴ��غ�բ״̬
	SetStateParas_AfterFirstTrip(pState2,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	pState2->m_fTimeState = m_fPostFaultTime;
	pState2->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;

	if (m_bCBSimulation)
	{
		pState2->m_fTimeState += m_fCBCloseTime;
	}

	fCurTime_AfterFualt += pState2->m_fTimeState;

	if (m_nRecloseMode == 2)//���Ϊ���غ�,��ֱ�ӽ���
	{
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 3;
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	//״̬4���غϺ�

	if (fCurTime_AfterFualt>=m_fTransTime)//����ӹ��Ͽ�ʼ���ʱ�����ת��ʱ��,��Ŀǰ����ת������̬
	{
		//ת������
		SetStateParas_TransFault(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState = m_fRecloseTime;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState3->m_fTimeAfterTrigger = 0;
		//////////////////////////////////////////////////////////////////////////
		//״̬5�����ٺ�
		SetStateParas_AccTrip(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState4->m_fTimeState = m_fTAfterAccTrig;
		pState4->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 5;
		return;
		//////////////////////////////////////////////////////////////////////////
	}
	else if ((m_fTransTime>=(fCurTime_AfterFualt+m_fRecloseTime))&&(m_nFaultProperty == 0))
	{
		//˲ʱ�Թ���-�غϺ�-ת������δ���ü�����
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
		///�����Թ���-�غϺ�-��������ǰת�����ϻ�δ����
		SetStateParas_AfterRecosePermanent(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState = m_fRecloseTime;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState3->m_fTimeAfterTrigger = 0;
		//////////////////////////////////////////////////////////////////////////
		//״̬5�����ٺ�
		SetStateParas_AccTrip(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState4->m_fTimeState = m_fTAfterAccTrig;
		pState4->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 5;
		return;
		//////////////////////////////////////////////////////////////////////////
	}

	//���غ�ʱ����ڷ���ת������

	if (m_nFaultProperty == 0)//˲ʱ�Թ���
	{
		SetStateParas_AfterRecoseTransient(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState = m_fTransTime - fCurTime_AfterFualt;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState3->m_fTimeAfterTrigger = 0;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//״̬5-ת������
		SetStateParas_TransFault(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState4->m_fTimeState = m_fRecloseTime - (m_fTransTime - fCurTime_AfterFualt);
		pState4->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState4->m_fTimeAfterTrigger = 0;
		//////////////////////////////////////////////////////////////////////////
		//״̬6�����ٺ�
		SetStateParas_AccTrip(pState5,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState5->m_fTimeState = m_fTAfterAccTrig;
		pState5->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 6;
		return;
		//////////////////////////////////////////////////////////////////////////
	} 
	else//�����Թ���
	{
		///�����Թ���-�غϺ�-��������ǰת�����ϻ�δ����
		SetStateParas_AfterRecosePermanent(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState =  m_fTransTime - fCurTime_AfterFualt;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState3->m_fTimeAfterTrigger = 0;
		//////////////////////////////////////////////////////////////////////////
		//״̬5-ת������
		SetStateParas_TransFault(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState4->m_fTimeState = m_fRecloseTime - (m_fTransTime - fCurTime_AfterFualt);
		pState4->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState4->m_fTimeAfterTrigger = 0;
		//////////////////////////////////////////////////////////////////////////
		//״̬6�����ٺ�
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

	float fStdLN_Vol = m_fUnom/*g_theSystemConfig->m_fVNom/SQRT3*/;//�����׼���ѹ,һ��57.735V
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
	//״̬3����բ��,�ȴ��غ�բ״̬
	SetStateParas_AfterFirstTrip(pState2,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	pState2->m_fTimeState = m_fPostFaultTime;
	pState2->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;

	if (m_bCBSimulation)
	{
		pState2->m_fTimeState += m_fCBCloseTime;
	}

	if (m_nRecloseMode == 2)//���Ϊ���غ�,��ֱ�ӽ���
	{
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 3;
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	//״̬4���غϺ�

	if (m_nFaultProperty == 0)//˲ʱ�Թ���
	{
		SetStateParas_AfterRecoseTransient(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
		pState3->m_fTimeState = m_fRecloseTime;
		pState3->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		pState3->m_fTimeAfterTrigger = 0;
		m_pImpBaseParas->m_pStateParas->m_nStateNumbers = 4;
		return;
	} 
	else//�����Թ���
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
		//״̬5�����ٺ�
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

 	float fStdLN_Vol = m_fUnom/*g_theSystemConfig->m_fVNom/SQRT3*/;//�����׼���ѹ,һ��57.735V
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
 	//״̬1������ǰ״̬
 	Complex p1;
 	Complex	oComplexUI[2][4];
	SetStateParas_PreFault(pState0,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	Global_SetStateBoutPreFault(m_pImpBaseParas->m_pStateParas->m_paraState,m_nStateBOut,
                                m_nOutputSwitchMode,m_nBinSelect,m_fBoutTimeTrig,m_fBoutHoldTime);
 	//////////////////////////////////////////////////////////////////////////

 	//״̬2������״̬
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
	//״̬3����բ��,�ȴ��غ�բ״̬
	SetStateParas_AfterFirstTrip(pState2,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	//////////////////////////////////////////////////////////////////////////
	//״̬4���غϺ�(˲ʱ)
	SetStateParas_AfterRecoseTransient(pState3,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	//////////////////////////////////////////////////////////////////////////
	//״̬5���غϺ�(����)
	SetStateParas_AfterRecosePermanent(pState4,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	//////////////////////////////////////////////////////////////////////////
	//״̬6��ת������
	SetStateParas_TransFault(pState5,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	//////////////////////////////////////////////////////////////////////////
	//״̬7�����ٺ�
	SetStateParas_AccTrip(pState6,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	//////////////////////////////////////////////////////////////////////////
	//״̬8��ֹ̬ͣ
	SetStateParas_StopTest(pState7,this,oComplexUI[0],oComplexUI[1],fStdLN_Vol);
	//////////////////////////////////////////////////////////////////////////
}




