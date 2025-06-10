#include "stdafx.h"
#include"SttPIC200DIOTest.h"
#include "../../SttDevice/SttDeviceBase.h"

CString CSttPic200dIoTest::m_strMacroName = "PIC200DIO测试";
CString CSttPic200dIoTest::m_strMacroID = ("SttPic200dIoTest");
CString CSttPic200dIoTest::m_strFilePostFix = "sttptt";
CString CSttPic200dIoTest::m_strMacroVer ="1.0";

CSttPic200dIoTest::CSttPic200dIoTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttPic200dIoTest::Init()
{
    tmt_Pic200dIoTest::init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

long CSttPic200dIoTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttPic200dIoTest::~CSttPic200dIoTest(void)
{

}

void CSttPic200dIoTest::AfterSetParameter()
{	

}

long CSttPic200dIoTest::CalReport(UINT nState)
{

	return 0;
}

long CSttPic200dIoTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttPic200dIoTest::StartTest()
{
	CSttTestBase::StartTest();
    CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttPic200dIoTest::DataDownload Finished");
	TtmToDrv();
}

void CSttPic200dIoTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
    //IO低电平有效
    long nVal = 0xffffffff;
    for(int i =0 ;i<8;i++)
    {
        if(m_nIO1[i] == 0)
        {
            nVal &= ~(1<<i);
        }
    }
    ioctl(CSttDeviceBase::g_pSttDeviceBase->m_nCommfd,0x010b,nVal);
    nVal = 0xffffffff;
    for(int i =0 ;i<16;i++)
    {
        if(m_nIO2[i] == 0)
        {
            nVal &= ~(1<<i);
        }
    }
    ioctl(CSttDeviceBase::g_pSttDeviceBase->m_nCommfd,0x010d,nVal);
    nVal = 0xffffffff;
    for(int i =0 ;i<8;i++)
    {
        if(m_nIO3[i] == 0)
        {
            nVal &= ~(1<<i);
        }
    }
    ioctl(CSttDeviceBase::g_pSttDeviceBase->m_nCommfd,0x010f,nVal);
#endif
}

void CSttPic200dIoTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(this,pXmlSerialize);
}
