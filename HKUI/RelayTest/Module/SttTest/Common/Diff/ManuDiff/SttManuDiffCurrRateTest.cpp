#include "stdafx.h"
#include "SttManuDiffCurrRateTest.h"
#include "../../SttSystemConfig.h"
#include "../../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttManuDiffCurrRateTest::m_strMacroName = "������ƶ�����(�ֶ��ݱ�)";
CString CSttManuDiffCurrRateTest::m_strMacroID = STT_MACRO_ID_PsuManuDiffRateTest;
CString CSttManuDiffCurrRateTest::m_strFilePostFix = "pdffrtst";
CString CSttManuDiffCurrRateTest::m_strMacroVer ="1.0";

CSttManuDiffCurrRateTest::CSttManuDiffCurrRateTest() : CSttManuDiffCurrThrTest()
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

CSttManuDiffCurrRateTest::~CSttManuDiffCurrRateTest(void)
{

}

long CSttManuDiffCurrRateTest::CalReport(UINT nState)
{
	CSttManuDiffCurrThrTest::CalReport(nState);
	m_oResults.m_fIbiasValue = m_fIbias;

	if (m_oResults.m_nActFlag)
	{
		float fValue = m_oResults.m_fIdiffActValue;
		m_oDiffCalTool.CurrentCal(&fValue,m_fIbias);
		SetResultValues_I1IeI2Ie();
		
	}

	return 0;
}

void CSttManuDiffCurrRateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_rate(this,pXmlSerialize);

	//2020-4-6  lijq  ��ȡ����ģʽ�£���Ҫ���г�ʼ��
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//������������й���ת��

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttManuDiffCurrRateTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_rate(&m_oResults, pXmlSerialize);
}




