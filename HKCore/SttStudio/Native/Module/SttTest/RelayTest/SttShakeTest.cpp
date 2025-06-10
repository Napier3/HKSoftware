#include "stdafx.h"
#include"SttShakeTest.h"
// #include<QtDebug>

#ifdef _PSX_IDE_QT_
#include"../../SttDevice/RelayTest/SttDriverOper.h"
#endif

CString CSttShakeTest::m_strMacroName = "振荡测试";
CString CSttShakeTest::m_strMacroID = ("SttShakeTest");
CString CSttShakeTest::m_strFilePostFix = "sttshktst";
CString CSttShakeTest::m_strMacroVer ="1.0";

CSttShakeTest::CSttShakeTest() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
    m_nOut = 0;
    Init();
}

void CSttShakeTest::Init()
{ 
    tmt_ShakeTest::init();
	CSttTestBase::Init();
}

long CSttShakeTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttShakeTest::~CSttShakeTest(void)
{
}

void CSttShakeTest::AfterSetParameter()
{
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;

    for(int i=0; i<8; i++)
    {
        m_nOut |= (m_oShakeParas.m_binOut[i].nState? 1:0)<<i;
    }
}

void CSttShakeTest::EventProcess()
{	
}

void CSttShakeTest::sendRealOutPut(structResult oItem)
{
	return;
}

void CSttShakeTest::sendRealDataChanged(structResult oItem)
{
	return;
}

double CSttShakeTest::GetTestTimeLong()
{
	float	fTime = 0.000;
//	for (int i=0;i<m_oStateParas.m_nStateNumbers;i++)
//	{
//		tmt_state_para *pSt = &m_oStateParas.m_paraState[i];
//		if (pSt->m_nTriggerCondition==TMT_MDSTATE_TIMETRIGGER || pSt->m_nTriggerCondition==TMT_MDSTATE_TIMEBINTRIGGER)
//			fTime += pSt->m_fTimeState+pSt->m_fTimeAfterTrigger+pSt->m_binOut[0].fTimeTrig;
//		else
//			fTime += TIME_MAX_WAITING+pSt->m_fTimeAfterTrigger+pSt->m_binOut[0].fTimeTrig;
//	}

//	fTime *= (m_oStateParas.m_nRepeatNumbers+1);

//	fTime += TIME_ONLINE_DELAY;		//等待时间过长，给10s缓冲

	return fTime;
}

long CSttShakeTest::CalReport(UINT nState)
{
	return 0;
}

void CSttShakeTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oShakeParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

long CSttShakeTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttShakeTest::Stop()
{	
//	m_Start=false;
    CSttTestBase::Stop();
}

void CSttShakeTest::StartTest()
{	
	CSttTestBase::StartTest();
	TtmToDrv();

#ifdef _PSX_IDE_QT_
    CSttDriverOper::SetBinaryOut(m_nOut);
    CSttDeviceBase::g_pSttDeviceBase->SetTestPara(ShakeTest, (char*)&m_oDrvShakeData , sizeof(drv_shake_test));// 设置为状态序列参数模式 // 写入参数
    CSttDeviceBase::g_pSttDeviceBase->SetTestStart(ShakeTest);
#endif	
//	m_Start=true;
}

void CSttShakeTest::TtmToDrv()
{
#ifdef _PSX_IDE_QT_
	tmt_to_drv(this,&m_oDrvShakeData);
#endif
}


