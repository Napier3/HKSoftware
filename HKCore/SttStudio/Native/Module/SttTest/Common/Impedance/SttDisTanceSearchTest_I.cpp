#include "stdafx.h"
#include "SttDisTanceSearchTest_I.h"
#include "../SttSystemConfig.h"
#include "../SttStateTest.h"

#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif


CString CSttDisTanceSearchTest_I::m_strMacroName = "���뱣�������迹����(���ʰ�)";
CString CSttDisTanceSearchTest_I::m_strMacroID = STT_MACRO_ID_DistanceSearch_I;
CString CSttDisTanceSearchTest_I::m_strFilePostFix = "odss";
CString CSttDisTanceSearchTest_I::m_strMacroVer ="1.0";

CSttDisTanceSearchTest_I::CSttDisTanceSearchTest_I() : CSttDisTanceTest_I()
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

void CSttDisTanceSearchTest_I::Init()
{ 
	CSttDisTanceTest::Init();
	m_oParas.init();
#ifndef USE_COMPLEX_SEARCH_MODE
	m_nRunSearchCount=1;
	m_bJudge1=m_bJudge2=FALSE;
	m_bTempResultJudge = FALSE;
#endif
    m_fMarginTime = 0;
	m_oDistanceSearchResults.init();
	m_oParas.m_fUNom = g_theSystemConfig->m_fVNom/SQRT3;//�����׼���ѹ,һ��57.735V
}

CSttDisTanceSearchTest_I::~CSttDisTanceSearchTest_I(void)
{

}

void CSttDisTanceSearchTest_I::AfterSetParameter()
{
	m_oParas.InitSearch();
	CSttDisTanceTest::AfterSetParameter();

#ifndef USE_COMPLEX_SEARCH_MODE
	Complex p1;
	m_fZEnd = m_fZEnd.polar(m_oParas.m_fScanTo,m_oParas.m_fScanToAngle);
	m_fZStart = m_fZStart.polar(m_oParas.m_fScanFrom,m_oParas.m_fScanFromAngle);
	m_fZStep = p1.polar(m_oParas.m_fStep,p1.arg(m_fZStart-m_fZEnd));
	m_fZCurrent = m_fZStart;
	m_nRunSearchCount=1;
	m_bJudge1=m_bJudge2=FALSE;

	m_oParas.m_fSearchBegin = m_oParas.m_fScanFrom;
	m_oParas.m_fSearchBeginAngle = m_oParas.m_fScanFromAngle;
	m_oParas.m_fCurrScanVal = m_oParas.m_fScanFrom;
	m_oParas.m_fCurrScanValAngle = m_oParas.m_fScanFromAngle;
	m_oParas.m_fSearchEnd = m_oParas.m_fScanTo;
	m_oParas.m_fSearchEndAngle = m_oParas.m_fScanToAngle;
	m_oParas.m_fSearchArea = (float)(m_fZStart-m_fZEnd).norm();
#endif
}

long CSttDisTanceSearchTest_I::CalReport(UINT nState)
{
    CSttDisTanceTest_I::CalReport(nState);

#ifdef USE_COMPLEX_SEARCH_MODE
	if (m_oParas.IsAct())
	{
		m_oDistanceSearchResults.m_fImp = m_oParas.GetActValue();

		if (m_oParas.IsBinarySearch())
		{
            m_oDistanceSearchResults.m_fImpAngle = m_oParas.GetActValueAngle();
		} 
		else
		{
			m_oDistanceSearchResults.m_fImpAngle = m_oParas.m_fCurrScanValAngle;
		}
		
		m_oDistanceSearchResults.m_nActZ = 1;
// 		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("CalReport(m_fImp=%f),(m_fImpAngle=%f)."),
// 			m_oDistanceSearchResults.m_fImp,m_oParas.m_fCurrScanValAngle);
	} 
	else
	{
		m_oDistanceSearchResults.m_fImp = 0;
		m_oDistanceSearchResults.m_fImpAngle = 0;
		m_oDistanceSearchResults.m_nActZ = 0;
	}
#endif

	return 0;
}

void CSttDisTanceSearchTest_I::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_Search(&m_oParas,pXmlSerialize,g_nBinExCount,g_nBoutExCount);


	//2020-4-6  lijq  ��ȡ����ģʽ�£���Ҫ���г�ʼ��
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		m_oParas.CopyOwn(this);//���������ľ�����ز���������������
		AfterSetParameter();
		TranslateToStateParas();
		m_pImpBaseParas->m_bSearchNext = TRUE;
		m_pImpBaseParas->m_fImpBaseStopTime = 10;
		m_pImpBaseParas->m_pStateParas->m_paraState[0].m_fTimeState = m_fPrepareTime;

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttDisTanceSearchTest_I::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_SearchReport(&m_oParas, pXmlSerialize);
}

void CSttDisTanceSearchTest_I::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_Search(&m_oDistanceSearchResults, pXmlSerialize,g_nBinExCount,g_nBoutExCount);
}

long CSttDisTanceSearchTest_I::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttDisTanceSearchTest_I::TranslateToStateParas()
{
#ifdef USE_COMPLEX_SEARCH_MODE
	m_fImpedance[0] = m_oParas.m_fCurrScanVal;
	m_fImpAngle[0] = m_oParas.m_fCurrScanValAngle;

// 	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("TranslateToStateParas(m_fImp=%f),(m_fImpAngle=%f)."),
// 		m_oParas.m_fCurrScanVal,m_oParas.m_fCurrScanValAngle);

#else
	m_fImpedance[0] = (float)m_fZCurrent.norm();
	m_fImpAngle[0] = (float)m_fZCurrent.arg();
#endif
	CSttDisTanceTest::TranslateToStateParas();
    //״̬3����բ��,�ȴ��غ�բ״̬
    tmt_StatePara *pState2 = &m_pImpBaseParas->m_pStateParas->m_paraState[2];
    pState2->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    for (int i = 0;i<8;i++)
    {
        pState2->m_binIn[i].nSelect = m_oParas.m_nBinState[i];
    }
    pState2->m_nBinLogic = m_oParas.m_nBinLogic;

    m_oDistanceResults.m_fFaultVol = m_fSCVoltage[0];
    m_oDistanceResults.m_fFaultCurrent = m_fSCCurrent[0];
// 	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
// 	STT_TIME oTime;
// 	oTime.dRealTime = 0;
// 	oTime.dTime = 0;
// 	oTime.dBinActTime = -1;
// 	pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, 0);
}

void CSttDisTanceSearchTest_I::SetStateParas_StopTest(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol)
{
	m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,m_fUNom,0.0f);//�������ǰ�����ѹ
	m_oFaultCalculatTool.CalPreFaultComplex(pCur_Complex,pImpParas->m_fIfh,-pImpParas->m_fPowerAngle);//�������ǰ�������
	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	pStatePara->m_bDC = FALSE;
}

void CSttDisTanceSearchTest_I::ReturnTestStateEvent_SearchPoint(double dTime, double dRealTime, bool bWithEvent)
{
#ifdef USE_COMPLEX_SEARCH_MODE
	CSttDisTanceTest::CalReport(0);

	if (m_oDistanceResults.m_nActA || m_oDistanceResults.m_nActB || m_oDistanceResults.m_nActC)
	{
		m_oDistanceResults.CopyOwn(&m_oDistanceSearchResults);
	}
#else
	ActProcess(m_fPreFaultTime);
#endif

	if (!m_oParas.IsSearchFinished(m_oDistanceResults.m_nActA || m_oDistanceResults.m_nActB || m_oDistanceResults.m_nActC))
	{
#ifdef USE_COMPLEX_SEARCH_MODE
		m_oParas.SearchNext();

// 		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("ReturnTestStateEvent_TestFinish(m_fImp=%f),(m_fImpAngle=%f)."),
// 			m_oParas.m_fCurrScanVal,m_oParas.m_fCurrScanValAngle);

		CSttDisTanceTest::AfterSetParameter();
#else
		CalNext();
#endif
		TranslateToStateParas();

#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StateItem(m_pImpBaseParas->m_pStateParas);//������ʼ���Բ���
		int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
		
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(nFd,0x14A,0);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
		return;
	}

	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;

	CalReport();//zhouhj 20210613�ڷ��ز��Խ�����Ϣʱ,���㱨����ֵ

#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
#endif
	SetTestStarting(FALSE);

	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
	pTestServer->ReturnTestStateEvent(SttResult_Type_TestFinish, &oTime, bWithEvent);
}

void CSttDisTanceSearchTest_I::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;

	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();

#ifdef USE_COMPLEX_SEARCH_MODE
	if (m_oParas.m_nStepIndex == 0)//ֻ�е�һ�����Ե�,��Ҫ�·���ʼ��������,�������Ե㲻��Ҫ
#else
	if (m_nRunSearchCount == 1)//ֻ�е�һ�����Ե�,��Ҫ�·���ʼ��������,�������Ե㲻��Ҫ
#endif
	{
		pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
	}

	pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
}

#ifndef USE_COMPLEX_SEARCH_MODE
BOOL CSttDisTanceSearchTest_I::ActProcess(float fTime)
{
	m_fPreFaultTime = fTime;
	Complex p1,p2,p3;

	// CCCC ��ȡ����ʱ��
	CSttDisTanceTest::CalReport(0);

	if (m_oDistanceResults.m_nActA || m_oDistanceResults.m_nActB || m_oDistanceResults.m_nActC)
	{
		m_oDistanceResults.CopyOwn(&m_oDistanceSearchResults);
		m_bTempResultJudge = TRUE;
	}
	else
	{
		m_bTempResultJudge = FALSE;
	}
	
	BOOL bFinished = FALSE;

	if(m_oParas.IsBinarySearch())//���ַ�
	{
		//���ڶ��ַ�,�����߽�ض�����ʼ���뵱ǰ��֮��,������2�����Ϻ�,�ҵ�ǰʣ����������С�ڵ�������ʱ,�޷�������������,���������
		if(p1.norm(m_fZCurrent-m_fZStart)<m_oParas.m_fStep && m_nRunSearchCount>2)//��ǰ������ʼ��֮��Ĳ���С�ڵ��������ĳ���,�Ҳ��ǵ�һ�β���
		{
// 			m_oParas.m_fActValue = (float)m_fZCurrent.norm();//��ǰ�迹��Ϊ�����迹
// 			m_oParas.m_fActValueAngle = (float)m_fZCurrent.arg();
			bFinished = TRUE;//�������Խ���
			m_oParas.m_nActFlag = ACTFLAG_ACT;		//����
			m_oDistanceSearchResults.m_nActZ = TRUE;//
			m_oParas.m_nActFlag = TRUE;
		}
		else
		{
			if(m_nRunSearchCount == 2)//��ǰΪ�ڶ��β���,�������迹ֵ
			{
				m_bJudge2=m_bTempResultJudge;

				if(m_bJudge1==FALSE&&m_bJudge2==FALSE||m_bJudge1==TRUE&&m_bJudge2==TRUE)//�����һ�κ͵ڶ��ζ�û����.���߶�����,��˵����ǰ���Է�Χ���޷��ҵ����Ա߽�
				{
					m_oParas.m_fActValue = 0;
					m_oParas.m_fActValueAngle = 0;
					bFinished = TRUE;
					m_oParas.m_nActFlag = ACTFLAG_FINISH;		//û����������
// 					Result.m_fFirstTripTime[0]=Result.m_fFirstTripTime[1]=Result.m_fFirstTripTime[2]=0.000;
// 					Result.m_nActA = Result.m_nActB = Result.m_nActC = FALSE;
				}
			}
		}
	}
	else//�����ƽ���
	{
		if(m_nRunSearchCount>1)//����ǵ�һ�����Ե�,����Ҫ���κδ���
		{
			m_bJudge2 = m_bTempResultJudge;

			//�����ǰ���������ǰһ����ͬ��1)���ʣ��ĳ���С�ڵ���������1.1��,����Ϊ��������,δ�ҵ��߽�;2�����������������;
			//�����ǰ���������ǰһ�β�ͬ:���ҵ��߽�,��������
			if(m_bJudge1==FALSE&&m_bJudge2==FALSE||m_bJudge1==TRUE&&m_bJudge2==TRUE)
			{
				if(p1.norm(m_fZCurrent-m_fZEnd)<1.1*p2.norm(m_fZStep))
				{
					m_oParas.m_fActValue = 0;
					m_oParas.m_fActValueAngle = 0;
					bFinished = TRUE;
					m_oParas.m_nActFlag = ACTFLAG_FINISH;
				}
			}
			else 
			{
// 				m_oParas.m_fActValue = (float)m_fZCurrent.norm();
// 				m_oParas.m_fActValueAngle = (float)m_fZCurrent.arg();
				bFinished = TRUE;
				m_oDistanceSearchResults.m_nActZ = TRUE;//
				m_oParas.m_nActFlag = ACTFLAG_ACT;
			}
		}
	}

	return bFinished;
}

BOOL CSttDisTanceSearchTest_I::CalNext()
{
	CSttDisTanceTest::AfterSetParameter();
	m_oParas.SearchNext();

	BOOL bFinished = FALSE;
	Complex p1,p2,p3;

	if(m_oParas.m_nSearchMode == SEARCHMODE_BINARY_SEARCH)//���ַ�
	{
		if(m_nRunSearchCount==1)//���Ϊ��һ�β���,���Ƿ����Ľ�����ݸ�m_bJudge1,����һ�β��Ե�����Ϊ�������迹
		{
			m_bJudge1=m_bTempResultJudge;
			m_fZCurrent = m_fZEnd;
		}
		else
		{
			if(m_nRunSearchCount==2)//����ǵڶ���,ȡ��ǰ���Ե�Ϊ,��ʼ�㡢�������м�ֵ
			{
				if(m_bJudge1==FALSE)//�����һ��δ����,��ڶ���һ��������,���ڶ���(������)����Ϊ�µ���ʼ��,ʵ�ʱ߽��,һ������ʼ���뵱ǰ��֮��
				{
					m_fZCurrent = m_fZStart;
					m_fZStart = m_fZEnd;
					m_fZEnd = m_fZCurrent;
				}

				p2=p3.polar(0.5,0.0);
				m_fZCurrent = p2*m_fZStart+p2*m_fZEnd;//��ǰֵ����Ϊ�м��ֵ
			}
			else if(m_nRunSearchCount>2)//����ǵڶ����Ժ�Ĳ��Ե�
			{
				//��һ�ε���ʼ��һ���Ƕ�����,������һ����δ������,�����ǰ�㶯����,��߽�ض����ڵ�ǰ���������֮��,�򽫵�ǰ������Ϊ��ʼ��,�����ǰ��δ����,��߽�ض��ڵ�ǰ������ʼ��֮��,�򽫵�ǰ������Ϊ������
				if(m_bTempResultJudge)//�����ǰ�㶯����,�ѵ�ǰ������Ϊ��ʼ��
				{
					m_fZStart = m_fZCurrent;
				}
				else//�����ǰ��δ����,�ѵ�ǰ������Ϊ������
				{
					m_fZEnd = m_fZCurrent;
				}

				p2=p3.polar(0.5,0.0);
				m_fZCurrent = p2*m_fZStart+p2*m_fZEnd;//��һ�����Ե�,Ϊ��ʼ������ֹ����м�ֵ
			}
		}

		m_nRunSearchCount++;
	}
	else//�����ƽ���
	{
		if(m_nRunSearchCount==1)//�����ǰ�������ǵ�һ����,�򽫽����ֵ��m_bJudge1,��һ�����Ե�,Ϊ��ǰ���Ե��ȥһ������
		{
			m_bJudge1=m_bTempResultJudge;
			m_fZCurrent = m_fZCurrent-m_fZStep;
		}
		else
		{
			m_bJudge2=m_bTempResultJudge;
			m_fZCurrent = m_fZCurrent-m_fZStep;
		}
		
		m_nRunSearchCount++;
	}

	m_oParas.m_fSearchBegin = (float)m_fZStart.norm();
	m_oParas.m_fSearchBeginAngle = (float)m_fZStart.arg();
	m_oParas.m_fCurrScanVal = (float)m_fZCurrent.norm();
	m_oParas.m_fCurrScanValAngle = (float)m_fZCurrent.arg();
	m_oParas.m_fSearchEnd = (float)m_fZEnd.norm();
	m_oParas.m_fSearchEndAngle = (float)m_fZEnd.norm();
	m_oParas.m_fSearchArea = (float)(m_fZStart-m_fZEnd).norm();
	m_oDistanceResults.m_fZshort = m_fImpedance[0] = m_oParas.m_fActValue;
	m_oDistanceResults.m_fIShortAngle = m_fImpAngle[0] = m_oParas.m_fActValueAngle;
	return TRUE;
}
#endif

