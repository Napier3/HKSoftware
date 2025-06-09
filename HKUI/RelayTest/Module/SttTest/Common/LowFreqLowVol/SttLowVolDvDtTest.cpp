#include "stdafx.h"
#include "SttLowVolDvDtTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLowVolDvDtTest::m_strMacroName = "��ѹ�����ֵ����";
CString CSttLowVolDvDtTest::m_strMacroID = STT_MACRO_ID_PsuLowVolDvdt;
CString CSttLowVolDvDtTest::m_strFilePostFix = "lvld";
CString CSttLowVolDvDtTest::m_strMacroVer ="1.0";

CSttLowVolDvDtTest::CSttLowVolDvDtTest() : CSttLowVolActTest()
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

void CSttLowVolDvDtTest::Init()
{ 
    CSttLowVolActTest::Init();
}

CSttLowVolDvDtTest::~CSttLowVolDvDtTest(void)
{

}

void CSttLowVolDvDtTest::AfterSetParameter()
{
    CSttStateTest::AfterSetParameter();
	m_nGradientCount = fabs(m_fDvdtStart-m_fDvdtEnd)/m_fDvdtStep/*+1*/;

	if (fabs((fabs(m_fDvdtStart-m_fDvdtEnd)-fabs(m_nGradientCount*m_fDvdtStep)))>0.0001)
    {
        m_nGradientCount++;
    }
}

long CSttLowVolDvDtTest::CalReport(UINT nState)
{
    m_oResults.m_nAct = 0;
    m_oResults.m_fDvdtAct = 0.0f;

	if (m_fDvdtStart>m_fDvdtEnd)
    {
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct > 0))
        {
            m_oResults.m_nAct = 1;
			m_oResults.m_fDvdtAct = m_fDvdtStart-(m_nRunSearchCount-1)*m_fDvdtStep;
    }
	} 
    else
    {
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct == 0)&&(m_nRunSearchCount>1))//20220722 zhouhj �ӵ�ֵ����ֵ����ʱ,���Ӳ�����������,�Ӷ�����������,���ٱ�֤����һ��
        {
            m_oResults.m_nAct = 1;
			m_oResults.m_fDvdtAct = m_fDvdtStart + (m_nRunSearchCount-1)*m_fDvdtStep;
        }
    }

	if ((m_oResults.m_nAct == 1)&&(m_nRunSearchCount>m_nGradientCount))
    {
        m_oResults.m_fDvdtAct = m_fDvdtEnd;
    }

	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("m_fDvdtStart=%f;m_fDvdtEnd=%f;m_fDvdtStep=%f;m_nRunSearchCount=%ld;m_oResults.m_fDvdtAct=%f;"),m_fDvdtStart,m_fDvdtEnd,m_fDvdtStep,m_nRunSearchCount
		,m_oResults.m_fDvdtAct);
    return 0;
}

void CSttLowVolDvDtTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_PsuLowVolDvDt(this,pXmlSerialize);

    //2020-4-6  lijq  ��ȡ����ģʽ�£���Ҫ���г�ʼ��
	if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//������������й���ת��

        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttLowVolDvDtTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PsuLowVolDvDt(&m_oResults, pXmlSerialize);
}

void CSttLowVolDvDtTest::TranslateToStateParas()
{
  	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//�����׼���ѹ,һ��57.735V
    m_pStateTest->m_oStateParas.m_fTao = 0;
	float fGradientTime = 0.0f,fLnDvDt = m_fDvdt ,fLnEndVol = m_fVend;
  
    //////////////////////////////////////////////////////////////////////////
    //����ǰ״̬
    Complex p1;
    Complex	oComplexUI[2][4];
   	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],fStdLN_Vol,0.0f);//�������ǰ�����ѹ
   	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1],1.2*m_fIAct,-78);//�������ǰ�������
   	m_oFaultCalculatTool.CalVzComplex(&oComplexUI[0][3],oComplexUI[0],0);
	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[0],oComplexUI[0],oComplexUI[1]);
   
    m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
    m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[0].m_binOut,m_binOut);
    m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
    m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
    //////////////////////////////////////////////////////////////////////////
    //����״̬
	m_pStateTest->m_oStateParas.m_paraState[1].m_nRampTimeGrad =  1;
	m_pStateTest->m_oStateParas.m_paraState[2].m_nRampTimeGrad =  1;

	if (m_nRunSearchCount > m_nGradientCount)
    {
        fLnDvDt = m_fDvdtEnd;
    }
	else if (m_fDvdtStart>m_fDvdtEnd)
    {
		fLnDvDt = m_fDvdtStart - (m_nRunSearchCount-1)*m_fDvdtStep;
	} 
    else
    {
		fLnDvDt = m_fDvdtStart + (m_nRunSearchCount-1)*m_fDvdtStep;
    }

	if (m_nUSetMode == 1)
    {
        fLnDvDt  /= SQRT3;
		fLnEndVol = m_fVend/SQRT3;
    }

    m_fCurrSearchDvdt = fLnDvDt;
	fGradientTime = fabs(fStdLN_Vol-fLnEndVol)/fLnDvDt;

	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[1],oComplexUI[0],oComplexUI[1]);

	for (int nIndex = 0;nIndex<3;nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fStep = fLnDvDt/1000;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fStepTime = 0.001f;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fEnd = fLnEndVol;
    }

	Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1],m_binIn,m_nBinLogic);
    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = fGradientTime + m_fHoldTime;
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOut,m_binOut);
 
 	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;
    }
 
    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
    m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;

    //////////////////////////////////////////////////////////////////////////
	//��ѹ�ݱ߻���ֵ̬

	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[2],oComplexUI[0],oComplexUI[1]);

	for (int nIndex = 0;nIndex<3;nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].fStep = fLnDvDt/1000;
        m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].fStepTime = 0.001f;

        m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Harm[1].fAmp = fLnEndVol;
        m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].fEnd = fStdLN_Vol;
    }

    m_pStateTest->m_oStateParas.m_paraState[2].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeState = fGradientTime + 0.5;
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[2].m_binOut,m_binOut);

	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[2].m_binOut[nBoutIndex].fTimeTrig = 0;
    }

    m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeAfterTrigger = 0;
    m_pStateTest->m_oStateParas.m_paraState[2].m_bDC = FALSE;

    //////////////////////////////////////////////////////////////////////////
}

BOOL CSttLowVolDvDtTest::IsGradientFinished()
{
	if (m_nGradientCount<=0)
    {
        return TRUE;
    }

	if (m_fDvdtStart>m_fDvdtEnd)
    {
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct == 0)&&(m_nRunSearchCount<=m_nGradientCount))
        {
            return FALSE;
        }

        return TRUE;
	} 
    else
    {
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct == 1)&&(m_nRunSearchCount<=m_nGradientCount))
        {
            return FALSE;
        }

        return TRUE;
    }
}
