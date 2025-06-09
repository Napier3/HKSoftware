#include "stdafx.h"
#include"SttTestForDebug.h"

CString CSttTestForDebug::m_strMacroName = "SttTestForDebug";
CString CSttTestForDebug::m_strMacroID = ("SttTestForDebug");
CString CSttTestForDebug::m_strFilePostFix = "sttdbg";
CString CSttTestForDebug::m_strMacroVer ="1.0";

CSttTestForDebug::CSttTestForDebug() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

long CSttTestForDebug::OnTimer(BOOL &bFinish, long nTimerLongMs)
{

	return true;
}

CSttTestForDebug::~CSttTestForDebug(void)
{
}

void CSttTestForDebug::AfterSetParameter()
{

}

BOOL CSttTestForDebug::EventProcess()
{
	return FALSE;
}

double CSttTestForDebug::GetTestTimeLong()
{
	float	fTime = 0.000;

	return fTime;
}

long CSttTestForDebug::CalReport(UINT nState)
{
	return 0;
}

void CSttTestForDebug::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

long CSttTestForDebug::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttTestForDebug::Stop()
{	
	
}

void CSttTestForDebug::StartTest()
{	
	CSttTestBase::StartTest();
}
