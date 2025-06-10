#include"SttDiff6IRateTest_Pnv.h"
#include "stdafx.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDiff6IRatePnvTest::m_strMacroName = "�(6I)-�����ƶ�����(PNV)";
CString CSttDiff6IRatePnvTest::m_strMacroID = STT_MACRO_ID_Diff6IRateRestrainSearchTest;
CString CSttDiff6IRatePnvTest::m_strFilePostFix = "pdff6itst";
CString CSttDiff6IRatePnvTest::m_strMacroVer = "1.0";

CSttDiff6IRatePnvTest::CSttDiff6IRatePnvTest() : CSttDiffCurrRateTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime = 0;
}

CSttDiff6IRatePnvTest::~CSttDiff6IRatePnvTest(void)
{
}
void CSttDiff6IRatePnvTest::AfterSetParameter()
{
    switch (m_nWindSide)
    {
    case 1://���в�
        m_fKpm = m_fKpl;
        break;
    case 2://�еͲ�
        m_fKpm = m_fKph;
        break;
    }
    CSttDiffCurrRateTest::AfterSetParameter();
}
void CSttDiff6IRatePnvTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_6i_rate_pnv(this, pXmlSerialize);

    //2020-4-6  lijq  ��ȡ����ģʽ�£���Ҫ���г�ʼ��
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//������������й���ת��
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttDiff6IRatePnvTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_6i_rate_pnv(&m_oResults, pXmlSerialize);
}
