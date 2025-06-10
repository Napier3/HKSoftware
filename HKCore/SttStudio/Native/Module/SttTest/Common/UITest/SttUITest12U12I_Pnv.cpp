#include "stdafx.h"
#include"SttUITest12U12I_Pnv.h"
#include "../SttSystemConfig.h"

CString CSttUITest12U12I_Pnv::m_strMacroName = "电压电流试验(12U12I)(PNV)";
CString CSttUITest12U12I_Pnv::m_strMacroID = STT_MACRO_ID_UITest_12u12i;
CString CSttUITest12U12I_Pnv::m_strFilePostFix = "pui12";
CString CSttUITest12U12I_Pnv::m_strMacroVer ="1.0";

CSttUITest12U12I_Pnv::CSttUITest12U12I_Pnv() : CSttManuTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
}

CSttUITest12U12I_Pnv::~CSttUITest12U12I_Pnv(void)
{

}

void CSttUITest12U12I_Pnv::AfterSetParameter()
{
	CSttManuTest::AfterSetParameter();
}

long CSttUITest12U12I_Pnv::CalReport(UINT nState)
{
    return 0;
}

void CSttUITest12U12I_Pnv::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_12u12i_pnv(&m_pManualTest->m_oManuParas,pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

//2020-10-26  lijunqing
void CSttUITest12U12I_Pnv::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	CSttManuTest::Report_XmlSerialize(pXmlSerialize);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
