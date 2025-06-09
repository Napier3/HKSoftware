#include "stdafx.h"
#include"SttState6U6I_Pnv.h"
#include "../SttSystemConfig.h"

CString CSttState6U6I_Pnv::m_strMacroName = "状态序列(六状态6U6I)(PNV)";
CString CSttState6U6I_Pnv::m_strMacroID = STT_MACRO_ID_State6U6I;
CString CSttState6U6I_Pnv::m_strFilePostFix = "state";
CString CSttState6U6I_Pnv::m_strMacroVer ="1.0";

CSttState6U6I_Pnv::CSttState6U6I_Pnv() : CSttStateTest()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime=0;

    m_pStateTest = stt_test_get_base_statetest_buff();
}

CSttState6U6I_Pnv::~CSttState6U6I_Pnv(void)
{

}

void CSttState6U6I_Pnv::AfterSetParameter()
{
	CSttStateTest::AfterSetParameter();
	long nBinLogic = 0;

	if (m_pStateTest->m_oStateParas.m_nRepeatNumbers>0)
	{
		m_pStateTest->m_oStateParas.m_nRepeatNumbers--;//重复1次代表不循环
	}

	for(int nIndex = 0;nIndex<m_pStateTest->m_oStateParas.m_nStateNumbers;nIndex++)
	{
		nBinLogic = (m_pStateTest->m_oStateParas.m_paraState[nIndex].m_nBinLogic == 0);//与或逻辑取反
		m_pStateTest->m_oStateParas.m_paraState[nIndex].m_nBinLogic = nBinLogic;
		switch (m_pStateTest->m_oStateParas.m_paraState[nIndex].m_nTriggerCondition)
		{
		case 0:		// 按键
			m_pStateTest->m_oStateParas.m_paraState[nIndex].m_nTriggerCondition = TMT_MDSTATE_MEARSURETRIGGER; 
			break;
		case 1:		// 时间
			m_pStateTest->m_oStateParas.m_paraState[nIndex].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER; 
			break;
		case 2:		// GPS
			m_pStateTest->m_oStateParas.m_paraState[nIndex].m_nTriggerCondition = TMT_MDSTATE_GPSBTRIGGER; 
			break;
		case 3:		// 开入接点
			m_pStateTest->m_oStateParas.m_paraState[nIndex].m_nTriggerCondition = TMT_MDSTATE_BINTRIGGER; 
			break;
		case 4:		// 低电压触发
			m_pStateTest->m_oStateParas.m_paraState[nIndex].m_nTriggerCondition = TMT_MDSTATE_LOWVOLTRIGGER; 
			break;		
		case 6:		// 开入量+时间
			m_pStateTest->m_oStateParas.m_paraState[nIndex].m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER; 
			break;
		default: 
			break;
		}
	}
}

long CSttState6U6I_Pnv::CalReport(UINT nState)
{
    return 0;
}

void CSttState6U6I_Pnv::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_statenUnI_pnv(&m_pStateTest->m_oStateParas,pXmlSerialize,STT_PNV_STATE_6U6I);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

//2020-10-26  lijunqing
void CSttState6U6I_Pnv::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_statenUnI_pnv(&m_pStateTest->m_oStateResults, &m_pStateTest->m_oStateParas, m_pStateTest->m_oStateParas.m_nStateNumbers,
                      pXmlSerialize,m_pStateTest->m_oStateParas.m_nBinTripRef);
}


//2020-10-26  lijunqing
void CSttState6U6I_Pnv::Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_statenUnI_pnv(&m_pStateTest->m_oStateParas,pXmlSerialize,STT_PNV_STATE_6U6I);
}

//2020-10-26  lijunqing
void CSttState6U6I_Pnv::Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_statenUnI_pnv(&m_pStateTest->m_oStateResults, &m_pStateTest->m_oStateParas, m_pStateTest->m_oStateParas.m_nStateNumbers,
                      pXmlSerialize,m_pStateTest->m_oStateParas.m_nBinTripRef);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
