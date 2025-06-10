#include "stdafx.h"
#include"SttState4U3I_Pnv.h"
#include "../SttSystemConfig.h"

CString CSttState4U3I_Pnv::m_strMacroName = "状态序列(4U3I)(PNV)";
CString CSttState4U3I_Pnv::m_strMacroID = STT_MACRO_ID_State4U3I;
CString CSttState4U3I_Pnv::m_strFilePostFix = "pnvst43";
CString CSttState4U3I_Pnv::m_strMacroVer ="1.0";

CSttState4U3I_Pnv::CSttState4U3I_Pnv() : CSttState6U6I_Pnv()
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

CSttState4U3I_Pnv::~CSttState4U3I_Pnv(void)
{

}

void CSttState4U3I_Pnv::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_statenUnI_pnv(&m_pStateTest->m_oStateParas,pXmlSerialize,STT_PNV_STATE_4U3I);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

//2020-10-26  lijunqing
void CSttState4U3I_Pnv::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_statenUnI_pnv(&m_pStateTest->m_oStateResults, &m_pStateTest->m_oStateParas, m_pStateTest->m_oStateParas.m_nStateNumbers,
                      pXmlSerialize,m_pStateTest->m_oStateParas.m_nBinTripRef);
}


//2020-10-26  lijunqing
void CSttState4U3I_Pnv::Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_statenUnI_pnv(&m_pStateTest->m_oStateParas,pXmlSerialize,STT_PNV_STATE_4U3I);
}

//2020-10-26  lijunqing
void CSttState4U3I_Pnv::Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_statenUnI_pnv(&m_pStateTest->m_oStateResults, &m_pStateTest->m_oStateParas, m_pStateTest->m_oStateParas.m_nStateNumbers,
                      pXmlSerialize,m_pStateTest->m_oStateParas.m_nBinTripRef);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
