#include "stdafx.h"
#include "SttDiffCurrHarmTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDiffCurrHarmTest::m_strMacroName = "�г���ƶ�����";
CString CSttDiffCurrHarmTest::m_strMacroID = STT_MACRO_ID_PsuDiffHarmTest;
CString CSttDiffCurrHarmTest::m_strFilePostFix = "pdffhtst";
CString CSttDiffCurrHarmTest::m_strMacroVer ="1.0";

CSttDiffCurrHarmTest::CSttDiffCurrHarmTest() : CSttDiffCurrThrTest()
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

CSttDiffCurrHarmTest::~CSttDiffCurrHarmTest(void)
{

}

long CSttDiffCurrHarmTest::CalReport(UINT nState)
{
	if (IsAct())
	{
		m_oResults.m_fIrCoef = GetActValue()/100;
		m_oResults.m_nActFlag = 1;
		ChannelUI_Diff *pDiffChs = m_oDiffCalTool.GetChannelCurrents();
		m_oResults.m_fIRbase[0] = pDiffChs[0].famptitude;
		m_oResults.m_fIRbase[1] = pDiffChs[1].famptitude;
		m_oResults.m_fIRbase[2] = pDiffChs[2].famptitude;

		m_oResults.m_fIharm[0] = pDiffChs[0].famptitude*m_oResults.m_fIrCoef;
		m_oResults.m_fIharm[1] = pDiffChs[1].famptitude*m_oResults.m_fIrCoef;
		m_oResults.m_fIharm[2] = pDiffChs[2].famptitude*m_oResults.m_fIrCoef;
	} 
	else
	{
		m_oResults.m_fIrCoef = 0.0f;
		m_oResults.m_nActFlag = 0;
	}

	return 0;
}

void CSttDiffCurrHarmTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_harm(this,pXmlSerialize);

	//2020-4-6  lijq  ��ȡ����ģʽ�£���Ҫ���г�ʼ��
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//������������й���ת��

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttDiffCurrHarmTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_harm(&m_oResults, pXmlSerialize);
}

void CSttDiffCurrHarmTest::AfterSetParameter()
{
	CSttDiffCurrThrTest::AfterSetParameter();
	m_pStateTest->m_oStateParas.init(2);
}

void CSttDiffCurrHarmTest::TranslateToStateParas()
{
	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//�����׼���ѹ,һ��57.735V
	m_pStateTest->m_oStateParas.m_fTao = 0;

	//////////////////////////////////////////////////////////////////////////
	//����ǰ״̬
	SetStatePreFault_6U6I();//�ڴ˺��������ù���ǰ��ѹ���������뿪����,�����ù���̬��ѹֵ
	//////////////////////////////////////////////////////////////////////////
	//����״̬
	m_oDiffCalTool.CurrentCal(&m_fIdiff,m_fIbias);
	SetResultValues_I1IeI2Ie();
	m_oResults.m_fIdiffSettingValue = m_fIdiff;
	ChannelUI_Diff *pChCurrents = m_oDiffCalTool.GetChannelCurrents();

	long nHarmIndex = m_nHarmIndex;
	BOOL bHarmValid = TRUE;

	if ((m_nHarmIndex<0)||(m_nHarmIndex>2))
	{
		bHarmValid = FALSE;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰг������(%ld)����."),m_nHarmIndex);
	}
	else if (m_nHarmIndex == 2)
	{
		nHarmIndex = 5;
	}
	else
		nHarmIndex += 2;

	for (int nIndex = 0;nIndex<DIFF_CURR_CAL_CHANNEL_MAX;nIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAmp = pChCurrents[nIndex].famptitude;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAngle = pChCurrents[nIndex].fphase;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;

		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[nHarmIndex].m_bSelect = TRUE;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[nHarmIndex].fAmp = pChCurrents[nIndex].famptitude*m_fCurrScanVal/100;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[nHarmIndex].fAngle = pChCurrents[nIndex].fphase;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[nHarmIndex].fFreq = g_theSystemConfig->m_fFNom*nHarmIndex;
	}

	Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1],m_binIn,m_nBinLogic);
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = m_fFaultTime;
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOut,m_binOut);

    for(int nBoutIndex = 0; nBoutIndex < MAX_BINARYOUT_COUNT; nBoutIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;
	}

	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
	m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;

	//////////////////////////////////////////////////////////////////////////
}



