#include "stdafx.h"
#include "SttBP2DiffThrTest.h"
#include "../../SttSystemConfig.h"
#include "../../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttBP2DiffThrTest::m_strMacroName = "BP2�������������";
CString CSttBP2DiffThrTest::m_strMacroID = STT_MACRO_ID_BP2DiffTCurrTest;
CString CSttBP2DiffThrTest::m_strFilePostFix = "bpdfctt";
CString CSttBP2DiffThrTest::m_strMacroVer ="1.0";

CSttBP2DiffThrTest::CSttBP2DiffThrTest() : CSttStateTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
}

void CSttBP2DiffThrTest::Init()
{ 
	CSttStateTest::Init();
	m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
	m_pStateTest->m_oStateParas.m_bSearchNext = TRUE;
	m_pStateTest->m_oStateParas.init(2);
	m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//ʹ��ϵͳ���������Ƶ��
	tmt_BP2DiffParas::init();
	m_oResults.init();
}

CSttBP2DiffThrTest::~CSttBP2DiffThrTest(void)
{

}

void CSttBP2DiffThrTest::AfterSetParameter()
{
	CSttStateTest::AfterSetParameter();
	m_oDiffCalTool.Init();

	m_oDiffCalTool.InitSysParas(100,g_theSystemConfig->m_fFNom);//20231120 zhoulei ��Ӳ����Դȥ�ж�

 	m_oDiffCalTool.InitParas3I_BP2();
	InitSearch();
}

long CSttBP2DiffThrTest::CalReport(UINT nState)
{
	if (IsAct())
	{
		m_oResults.m_fIdiffActValue = GetActValue();
		m_oResults.m_nActFlag = 1;
	} 
	else
	{
		m_oResults.m_fIdiffActValue = 0.0f;
		m_oResults.m_nActFlag = 0;
	}

	return 0;
}

void CSttBP2DiffThrTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_thr(this,pXmlSerialize);

	//2020-4-6  lijq  ��ȡ����ģʽ�£���Ҫ���г�ʼ��
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//������������й���ת��

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttBP2DiffThrTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_thr(&m_oResults, pXmlSerialize);
}

long CSttBP2DiffThrTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttBP2DiffThrTest::SetResultValues_I1I2()
{
	ChannelUI_Diff *pDiffChs = m_oDiffCalTool.GetChannelCurrents();
	 m_oResults.m_fI1 = pDiffChs[0].famptitude;
	 m_oResults.m_fI2 = pDiffChs[3].famptitude;
}

void CSttBP2DiffThrTest::SetStatePreFault_3U3I()
{
	float fAngle[DIFF_CURR_CAL_CHANNEL_NUM_3I] = {0, -120.0, 120.0};

	for (int nIndex=0;nIndex<DIFF_CURR_CAL_CHANNEL_NUM_3I;nIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nIndex].Harm[1].fAmp = m_fUmag[nIndex];
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fAmp = m_fUmag[nIndex];
		
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nIndex].Harm[1].fAngle = m_fUang[nIndex];
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fAngle = m_fUang[nIndex];

		m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;

		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fAmp = 0;
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fAngle = fAngle[nIndex];

		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
	}

	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
	m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[0].m_binOut,m_binOut);
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
	m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
}

void CSttBP2DiffThrTest::TranslateToStateParas()
{
  	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//�����׼���ѹ,һ��57.735V
	m_pStateTest->m_oStateParas.m_fTao = 0;
  
   	//////////////////////////////////////////////////////////////////////////
   	//����ǰ״̬
	SetStatePreFault_3U3I();//�ڴ˺��������ù���ǰ��ѹ���������뿪����,�����ù���̬��ѹֵ
   	//////////////////////////////////////////////////////////////////////////
 	//����״̬
	m_oDiffCalTool.CurrentCal3I_BP2(&m_fCurrScanVal,m_fIr_Id);
	SetResultValues_I1I2();
	m_oResults.m_fIdiffSettingValue = m_fCurrScanVal;
	ChannelUI_Diff *pChCurrents = m_oDiffCalTool.GetChannelCurrents();

	m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[1].fAmp = pChCurrents[0].famptitude;
	m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[1].fAngle = pChCurrents[0].fphase;

	if (m_nDiffType)//С������ʱ,�õ�Iĸ(Ia)��ĸ��(Ib)( 0-������� 1-С������)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[1].fAmp = pChCurrents[3].famptitude;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[1].fAngle = pChCurrents[3].fphase;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[2].Harm[1].fAmp = 0.0f;
	} 
	else//�������ʱ,�õ�Iĸ(Ia)��ĸ��(Ib)��IIĸ(Ic)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[1].fAmp = pChCurrents[0].famptitude;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[1].fAngle = pChCurrents[0].fphase;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiCUR[1].Harm[1].fAmp = pChCurrents[3].famptitude;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiCUR[1].Harm[1].fAngle = pChCurrents[3].fphase;
	}

	Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1],m_binIn,m_nBinLogic);
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = m_fFaultTime;
    SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOut, m_binOut);

    for(int nBoutIndex = 0; nBoutIndex < MAX_BINARYOUT_COUNT; nBoutIndex++)
  	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;
  	}
  
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
	m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;

	//////////////////////////////////////////////////////////////////////////
}

void CSttBP2DiffThrTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;

	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();

	if (m_nStepIndex == 0)//ֻ�е�һ�����Ե�,��Ҫ�·���ʼ��������,�������Ե㲻��Ҫ
	{
		pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
	}

	pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
}

void CSttBP2DiffThrTest::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_diff_search_results(this,&m_oResults, pXmlSerialize);
}

void CSttBP2DiffThrTest::ReturnTestStateEvent_SearchPoint(double dTime, double dRealTime, bool bWithEvent)
{
// 	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("״̬2�������(%d),����A��λ����(%d),����ʱ��(%f)"),m_pStateTest->m_oStateResults.m_resultState[1].m_nAct,
// 		m_pStateTest->m_oStateResults.m_resultState[1].m_nrBinSwitchCount[0],m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[0]);
	if (!IsSearchFinished(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct))
   	{
   		CSttStateTest::AfterSetParameter();
		SearchNext();
   		TranslateToStateParas();
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StateItem(&m_pStateTest->m_oStateParas);//������ʼ���Բ���
		int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
		
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(nFd,0x14B,0);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
   		return;
   	}
 
 	STT_TIME oTime;
 	oTime.dRealTime = dRealTime;
 	oTime.dTime = dTime;
 	oTime.dBinActTime = -1;
 	CalReport();

#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
#endif
	SetTestStarting(FALSE);

 	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
 	pTestServer->ReturnTestStateEvent(SttResult_Type_TestFinish, &oTime, bWithEvent);
}



