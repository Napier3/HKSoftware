#include "stdafx.h"
#include"SttStateTest.h"
//#include<QtDebug>

CString CSttStateTest::m_strMacroName = "状态序列测试";
CString CSttStateTest::m_strMacroID = ("SttStateTest");
CString CSttStateTest::m_strFilePostFix = "stttst";
CString CSttStateTest::m_strMacroVer ="1.0";

CSttStateTest::CSttStateTest() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	Init(MAX_STATETEST_COUNT);
	m_Start=FALSE;
}

void CSttStateTest::Init(long nStateNums)
{ 
	tmt_StateTest::init(nStateNums);
	CSttTestBase::Init();
	m_nCurStateIndex = -1;
}

long CSttStateTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	//qDebug()<<("CommReadResult(CSttStateTest)");
	//lijq 2020-3-28
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommReadResult(CSttStateTest)") );

#ifdef _PSX_IDE_QT_
	int nRet =CSttDeviceBase::g_pSttDeviceBase->GetTestResult(StateResult,(char*)&m_oDrvResults);
	if(nRet == -1)
		return false;
#endif

	if(m_oDrvResults.nCount<=0)//结果数量为空时，直接返回
	{
		//qDebug()<<("CommReadResult(m_oDrvResults.cnt<=0)");
		//lijq 2020-3-28
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommReadResult(m_oDrvResults.cnt<=0)") );
		return 0;
	}

	UINT nBinOrg=0xFF;

	for (int n=0; n<m_oDrvResults.nCount; n++)
	{
		int nSec=m_oDrvResults.stResult[n].nSec;
		int nNanoSec=m_oDrvResults.stResult[n].nNanoSec;

		if(m_oDrvResults.stResult[n].currentIndex >= m_oStateParas.m_nStateNumbers)//当前状态号大于设置的总状态数时，返回
		{
			//qDebug()<<("CommReadResult(m_oDrvResults.result[n].from >= m_nStateNumbers)");
			//lijq 2020-3-28
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommReadResult(m_oDrvResults.result[n].from >= m_nStateNumbers)") );
			Stop();
			break;
		}

		switch(m_oDrvResults.stResult[n].nType)
		{
		case STATE_RESULT_START:
		{//开始测试时，初始化开始测试时间，状态号，开入量
			m_uStartTimeS = nSec;
			m_uStartTimeNS = nNanoSec;
			m_oStateResults.m_resultState[0].m_frTimeStateBegin  = 0;
			m_nCurStateIndex = 0;
			nBinOrg = m_oDrvResults.stResult[n].nInput;
		}
			break;
		case STATE_RESULT_CHANGE:
		{//状态改变时记录状态号，相对第一个状态的相对时间
			m_nCurStateIndex = m_oDrvResults.stResult[n].nObjective;
			m_oStateResults.m_resultState[m_nCurStateIndex].m_frTimeStateBegin = GetTimeFromLong(m_oDrvResults.stResult[n].nSec-m_uStartTimeS,m_oDrvResults.stResult[n].nNanoSec-m_uStartTimeNS);
			nBinOrg = m_oDrvResults.stResult[n].nInput;
			//qDebug()<<("CommReadResult(type == STATE_TYPE_CHANGE)");
			//lijq 2020-3-28
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("") );

		}
			break;
		case STATE_RESULT_DI_CHANGE:
		{//开入变位时，记录所有的产生变位的结果记录
			int nBin = nBinOrg^m_oDrvResults.stResult[n].nInput;//取异或
			//qDebug()<<("CommReadResult(type == STATE_TYPE_DI_CHANGE)");
			//lijq 2020-3-28
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommReadResult(type == STATE_TYPE_DI_CHANGE)") );

			for (int i=0;i<MAX_BINARYIN_COUNT;i++)
			{
				if (((nBin>>i)&0x01) > 0)
				{
					m_oStateResults.m_resultState[m_nCurStateIndex].m_frTimeBinAct[i][m_oStateResults.m_resultState[m_nCurStateIndex].m_nrBinSwitchCount[i]] =
							GetTimeFromLong((nSec-m_uStartTimeS),(nNanoSec-m_uStartTimeNS))-m_oStateResults.m_resultState[m_nCurStateIndex].m_frTimeStateBegin;//xupf 20190717 修改纳秒级的计算
					m_oStateResults.m_resultState[m_nCurStateIndex].m_nrBinSwitchCount[i]++;
				}
			}

			nBinOrg = m_oDrvResults.stResult[n].nInput;
		}
			break;
		case STATE_RESULT_STOP:
		{
			//StopTest();
			//qDebug()<<("CommReadResult(type == STATE_TYPE_STOP)");
			//lijq 2020-3-28
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommReadResult(type == STATE_TYPE_STOP)") );

			bFinish = true;
		}
			break;
		}
	}

	return true;
}

CSttStateTest::~CSttStateTest(void)
{
}

void CSttStateTest::AfterSetParameter()
{
	for(int nIndex = 0;nIndex<m_oStateParas.m_nStateNumbers;nIndex++)
	{
		m_oStateResults.m_resultState[nIndex].init();
	}

	m_nCurStateIndex = 0;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

void CSttStateTest::EventProcess()
{
#ifdef _PSX_IDE_QT_
	int nret =CSttDeviceBase::g_pSttDeviceBase->GetTestResult(StateResult,(char*)&m_oDrvResults);

	if(nret <=0 ||nret<sizeof(structResult)+4)
	{
		return;
	}
#endif

	if(!m_Start)
		return;

	structResultItem* pResult = &m_oDrvResults;
	for(int i=0;i<pResult->nCount;i++)
	{
		structResult oItem = pResult->stResult[i];
		//qDebug()<<"Result["<<i<<"].currentIndex="<<oItem.currentIndex;
		//qDebug()<<"Result["<<i<<"].nType="<<oItem.nType;
		//qDebug()<<"Result["<<i<<"].nSec="<<oItem.nSec;
		//qDebug()<<"Result["<<i<<"].nNanoSec="<<oItem.nNanoSec;
		//lijq 2020-3-28
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Result[%d].currentIndex=%d"), i,  oItem.currentIndex);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Result[%d].nType=%d"), i,  oItem.nType);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Result[%d].nSec=%d"), i,  oItem.nSec);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Result[%d].nNanoSec=%d"), i,  oItem.nNanoSec);

		switch(oItem.nType)
		{
		case 1:
		case 3:
			//参数变化
			sendRealDataChanged(oItem);
			break;
		case 2:
			//stop
			m_Start=false;
			break;
		case 7:
		case 10:
			//递变值
			sendRealOutPut(oItem);
			break;
		}
	}
}

void CSttStateTest::sendRealOutPut(structResult oItem)
{
	return;
}

void CSttStateTest::sendRealDataChanged(structResult oItem)
{
	return;
}

double CSttStateTest::GetTestTimeLong()
{
	float	fTime = 0.000;
	for (int i=0;i<m_oStateParas.m_nStateNumbers;i++)
	{
		tmt_state_para *pSt = &m_oStateParas.m_paraState[i];
		if (pSt->m_nTriggerCondition==TMT_MDSTATE_TIMETRIGGER || pSt->m_nTriggerCondition==TMT_MDSTATE_TIMEBINTRIGGER)
			fTime += pSt->m_fTimeState+pSt->m_fTimeAfterTrigger+pSt->m_binOut[0].fTimeTrig;
		else
			fTime += TIME_MAX_WAITING+pSt->m_fTimeAfterTrigger+pSt->m_binOut[0].fTimeTrig;
	}

	fTime *= (m_oStateParas.m_nRepeatNumbers+1);

	fTime += TIME_ONLINE_DELAY;		//等待时间过长，给10s缓冲

	return fTime;
}

long CSttStateTest::CalReport(UINT nState)
{
	return 0;
}

void CSttStateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oStateParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

long CSttStateTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttStateTest::Stop()
{	
	CSttTestBase::Stop();
}

void CSttStateTest::Triger()
{
#ifdef _PSX_IDE_QT_
	CSttDeviceBase::g_pSttDeviceBase->SetStateTriger();
#endif
}

void CSttStateTest::StartTest()
{	
	CSttTestBase::StartTest();

#ifdef _PSX_IDE_QT_
	TtmToDrv();
	//long nDownloadSize = 52 + sizeof(drv_state)*m_oStateParas.m_nStateNumbers;
	//CSttDeviceBase::g_pSttDeviceBase->SetTestPara(StateTest,(char*)&m_oDrvStateData , nDownloadSize);
	CSttDeviceBase::g_pSttDeviceBase->SetTestStart(StateTest);
#endif

	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttStateTest::DataDownload Finished");
}

void CSttStateTest::TtmToDrv()
{
#ifdef _PSX_IDE_QT_
	tmt_to_drv(this,&m_oDrvStateData);
#endif
}


