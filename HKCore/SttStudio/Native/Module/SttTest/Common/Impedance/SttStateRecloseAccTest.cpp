#include "stdafx.h"
#include"SttStateRecloseAccTest.h"
#include "../SttSystemConfig.h"

CString CSttStateRecloseAccTest::m_strMacroName = "状态序列重合闸及后加速";
CString CSttStateRecloseAccTest::m_strMacroID = STT_MACRO_ID_StateRecloseAcc;
CString CSttStateRecloseAccTest::m_strFilePostFix = "osrcs";
CString CSttStateRecloseAccTest::m_strMacroVer ="1.0";

CSttStateRecloseAccTest::CSttStateRecloseAccTest() : CSttRecloseAccTest()
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

CSttStateRecloseAccTest::~CSttStateRecloseAccTest(void)
{

}

void CSttStateRecloseAccTest::AfterSetParameter()
{
    CSttStateTest::AfterSetParameter();
    m_pStateTest->m_oStateParas.m_paraState[0].m_tGps = m_tGps;

    int oState1BOut = m_nState1BOut;
    int oState2BOut = m_nState2BOut;
    int oState3BOut = m_nState3BOut;
    int oState4BOut = m_nState4BOut;
    for(int i=0;i<4;i++)
    {
        m_pStateTest->m_oStateParas.m_paraState[0].m_binOut[i].nState = oState1BOut %10;
        oState1BOut /=10;
        m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[i].nState = oState2BOut %10;
        oState2BOut /=10;
        m_pStateTest->m_oStateParas.m_paraState[2].m_binOut[i].nState = oState3BOut %10;
        oState3BOut /=10;
        m_pStateTest->m_oStateParas.m_paraState[3].m_binOut[i].nState = oState4BOut %10;
        oState4BOut /=10;
    }
}

void CSttStateRecloseAccTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_pnv((tmt_RecloseAccParas*)this,pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();

        Gouts_XmlSerialize(pXmlSerialize);
    }
}
