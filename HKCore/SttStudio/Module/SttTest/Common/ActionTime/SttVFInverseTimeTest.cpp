#include "stdafx.h"
#include "SttVFInverseTimeTest.h"
#include "../SttSystemConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttVFInverseTimeTest::m_strMacroName = "过励磁试验";
CString CSttVFInverseTimeTest::m_strMacroID = STT_MACRO_ID_VFInverseTime;
CString CSttVFInverseTimeTest::m_strFilePostFix = "vfactt";
CString CSttVFInverseTimeTest::m_strMacroVer ="1.0";

CSttVFInverseTimeTest::CSttVFInverseTimeTest() : CSttStateTest()
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

void CSttVFInverseTimeTest::Init()
{ 
	CSttStateTest::Init();
	m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
	m_pStateTest->m_oStateParas.init(2);
	m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
	tmt_VFInverseTimeParas::init();
	m_oVFInverseResults.init();
}

CSttVFInverseTimeTest::~CSttVFInverseTimeTest(void)
{

}

void CSttVFInverseTimeTest::AfterSetParameter()
{
	CSttStateTest::AfterSetParameter();
}

long CSttVFInverseTimeTest::CalReport(UINT nState)
{
	m_oVFInverseResults.m_fTripTime = 0.0f;

	if (m_nBinLogic == 0)//zhouhj 如果逻辑或
	{
        for(int nIndex = 0; nIndex < MAX_BINARYIN_COUNT; nIndex++) //任意一个选择的开入动作即为跳闸时间
		{
			if (m_binIn[nIndex].nSelect)
			{
				m_oVFInverseResults.m_fTripTime = GetMaxValue(m_oVFInverseResults.m_fTripTime,
															   m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[nIndex][0]);
			}
		}

		m_oVFInverseResults.m_nAct = (m_oVFInverseResults.m_fTripTime-0.0001) > 0 ? 1 : 0;//跳闸时间大于0即保护动作了
		return 0;
	}

    for(int nIndex = 0; nIndex < MAX_BINARYIN_COUNT; nIndex++) //对于开入与逻辑处理
	{
		if (m_binIn[nIndex].nSelect)//只看选择的开入
		{
			if (m_pStateTest->m_oStateResults.m_resultState[1].m_nrBinSwitchCount[nIndex] <= 0)//任意一个选择的开入未动作则未能成功动作
			{
				m_oVFInverseResults.m_fTripTime = 0.0f;
				break;
			}

			m_oVFInverseResults.m_fTripTime = GetMaxValue(m_oVFInverseResults.m_fTripTime,
														   m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[nIndex][0]);//取全部开入中最大的一个动作时间
		}
	}

	m_oVFInverseResults.m_nAct = (m_oVFInverseResults.m_fTripTime-0.0001) > 0 ? 1 : 0;
	return 0;
}

void CSttVFInverseTimeTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_VFInverseTimeParas*)this,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();//在读取完参数后进行参数设置,在此步骤后进行参数转换
		TranslateToStateParas();//参数设置完进行故障转换
		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttVFInverseTimeTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oVFInverseResults, pXmlSerialize);
}

long CSttVFInverseTimeTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttVFInverseTimeTest::TranslateToStateParas()
{
   	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	m_pStateTest->m_oStateParas.m_nPlusDC = 0;
	m_pStateTest->m_oStateParas.m_fTao = 0;
	m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);
  
   	//////////////////////////////////////////////////////////////////////////
   	//故障前状态
   	Complex	oComplexUI[2][4];
   	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],fStdLN_Vol,0.0f);//计算故障前三相电压
   	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1],0,0);//计算故障前三相电流
   	m_oFaultCalculatTool.CalVzComplex(&oComplexUI[0][3],oComplexUI[0],14);//无输出
	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[0],oComplexUI[0],oComplexUI[1]);
   
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
	m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);

    for(int nIndex = 0; nIndex < MAX_BINARYOUT_COUNT; nIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[0].m_binOut[nIndex].nState = m_binOut[0][nIndex].nState;
	}

	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
	m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
  	//////////////////////////////////////////////////////////////////////////
 	//故障状态
	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[1],oComplexUI[0],oComplexUI[1]);

	if (m_nGradMode == VF_INVERSE_GRADMODE_ChangeVol)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Harm[1].fAmp = m_fKuf*g_theSystemConfig->m_fFNom;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Harm[1].fAmp = m_fKuf*g_theSystemConfig->m_fFNom;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Harm[1].fAmp = m_fKuf*g_theSystemConfig->m_fFNom;
	} 
	else
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Harm[1].fFreq = fStdLN_Vol/m_fKuf;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Harm[1].fFreq = fStdLN_Vol/m_fKuf;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Harm[1].fFreq = fStdLN_Vol/m_fKuf;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[1].fFreq = fStdLN_Vol/m_fKuf;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[1].fFreq = fStdLN_Vol/m_fKuf;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[1].fFreq = fStdLN_Vol/m_fKuf;
	}
   
 	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = m_fSettingFaultTime + m_fFaultTimeMargin;
 	m_pStateTest->m_oStateParas.m_paraState[1].m_nBinLogic = m_nBinLogic;
 	m_pStateTest->m_oStateParas.m_paraState[1].m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;

    for(int nIndex = 0; nIndex < MAX_BINARYIN_COUNT; nIndex++)
  	{
 		m_pStateTest->m_oStateParas.m_paraState[1].m_binIn[nIndex].nSelect = m_binIn[nIndex].nSelect;
    }

    for(int nIndex = 0; nIndex < MAX_BINARYOUT_COUNT; nIndex++)
    {
 		m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nIndex].nState = m_binOut[1][nIndex].nState;
 	}
  
 	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
 	m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;
// 
// 	//////////////////////////////////////////////////////////////////////////
}
