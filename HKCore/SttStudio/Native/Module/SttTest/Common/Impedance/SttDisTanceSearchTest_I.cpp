#include "stdafx.h"
#include "SttDisTanceSearchTest_I.h"
#include "../SttSystemConfig.h"
#include "../SttStateTest.h"

#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif


CString CSttDisTanceSearchTest_I::m_strMacroName = "距离保护动作阻抗搜索(国际版)";
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
	m_oParas.m_fUNom = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
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


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		m_oParas.CopyOwn(this);//将解析到的距离相关参数拷贝到基类中
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
    //状态3：跳闸后,等待重合闸状态
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
	m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,m_fUNom,0.0f);//计算故障前三相电压
	m_oFaultCalculatTool.CalPreFaultComplex(pCur_Complex,pImpParas->m_fIfh,-pImpParas->m_fPowerAngle);//计算故障前三相电流
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
		CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StateItem(m_pImpBaseParas->m_pStateParas);//后续开始测试操作
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

	CalReport();//zhouhj 20210613在返回测试结束消息时,计算报告结果值

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
	if (m_oParas.m_nStepIndex == 0)//只有第一个测试点,需要下发开始测试命令,后续测试点不需要
#else
	if (m_nRunSearchCount == 1)//只有第一个测试点,需要下发开始测试命令,后续测试点不需要
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

	// CCCC 获取动作时间
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

	if(m_oParas.IsBinarySearch())//二分法
	{
		//对于二分法,搜索边界必定在起始点与当前点之间,当测试2次以上后,且当前剩余搜索长度小于单个步长时,无法继续进行搜索,则结束测试
		if(p1.norm(m_fZCurrent-m_fZStart)<m_oParas.m_fStep && m_nRunSearchCount>2)//当前点与起始点之间的步长小于单个步长的长度,且不是第一次测试
		{
// 			m_oParas.m_fActValue = (float)m_fZCurrent.norm();//当前阻抗即为动作阻抗
// 			m_oParas.m_fActValueAngle = (float)m_fZCurrent.arg();
			bFinished = TRUE;//整个测试结束
			m_oParas.m_nActFlag = ACTFLAG_ACT;		//动作
			m_oDistanceSearchResults.m_nActZ = TRUE;//
			m_oParas.m_nActFlag = TRUE;
		}
		else
		{
			if(m_nRunSearchCount == 2)//当前为第二次测试,即结束阻抗值
			{
				m_bJudge2=m_bTempResultJudge;

				if(m_bJudge1==FALSE&&m_bJudge2==FALSE||m_bJudge1==TRUE&&m_bJudge2==TRUE)//如果第一次和第二次都没动作.或者都动作,则说明当前测试范围内无法找到测试边界
				{
					m_oParas.m_fActValue = 0;
					m_oParas.m_fActValueAngle = 0;
					bFinished = TRUE;
					m_oParas.m_nActFlag = ACTFLAG_FINISH;		//没有做出动作
// 					Result.m_fFirstTripTime[0]=Result.m_fFirstTripTime[1]=Result.m_fFirstTripTime[2]=0.000;
// 					Result.m_nActA = Result.m_nActB = Result.m_nActC = FALSE;
				}
			}
		}
	}
	else//单步逼近法
	{
		if(m_nRunSearchCount>1)//如果是第一个测试点,不需要做任何处理
		{
			m_bJudge2 = m_bTempResultJudge;

			//如果当前动作结果和前一次相同：1)如果剩余的长度小于单个步长的1.1倍,则认为搜索结束,未找到边界;2）否则继续后续搜索;
			//如果当前动作结果和前一次不同:则找到边界,结束测试
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

	if(m_oParas.m_nSearchMode == SEARCHMODE_BINARY_SEARCH)//二分法
	{
		if(m_nRunSearchCount==1)//如果为第一次测试,将是否动作的结果传递给m_bJudge1,将下一次测试点设置为结束点阻抗
		{
			m_bJudge1=m_bTempResultJudge;
			m_fZCurrent = m_fZEnd;
		}
		else
		{
			if(m_nRunSearchCount==2)//如果是第二次,取当前测试点为,开始点、结束点中间值
			{
				if(m_bJudge1==FALSE)//如果第一次未动作,则第二次一定动作了,将第二次(结束点)点作为新的起始点,实际边界点,一定在起始点与当前点之间
				{
					m_fZCurrent = m_fZStart;
					m_fZStart = m_fZEnd;
					m_fZEnd = m_fZCurrent;
				}

				p2=p3.polar(0.5,0.0);
				m_fZCurrent = p2*m_fZStart+p2*m_fZEnd;//当前值设置为中间点值
			}
			else if(m_nRunSearchCount>2)//如果是第二次以后的测试点
			{
				//上一次的起始点一定是动作点,结束点一定是未动作点,如果当前点动作了,则边界必定是在当前点与结束点之间,则将当前点设置为起始点,如果当前点未动作,则边界必定在当前点与起始点之间,则将当前点设置为结束点
				if(m_bTempResultJudge)//如果当前点动作了,把当前点设置为起始点
				{
					m_fZStart = m_fZCurrent;
				}
				else//如果当前点未动作,把当前点设置为结束点
				{
					m_fZEnd = m_fZCurrent;
				}

				p2=p3.polar(0.5,0.0);
				m_fZCurrent = p2*m_fZStart+p2*m_fZEnd;//下一个测试点,为起始点与终止点的中间值
			}
		}

		m_nRunSearchCount++;
	}
	else//单步逼近法
	{
		if(m_nRunSearchCount==1)//如果当前搜索的是第一个点,则将结果赋值给m_bJudge1,下一个测试点,为当前测试点减去一个步长
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

