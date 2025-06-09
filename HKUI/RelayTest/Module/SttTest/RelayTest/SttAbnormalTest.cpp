#include "stdafx.h"
#include "SttAbnormalTest.h"

#ifdef _PSX_IDE_QT_
#include"../../SttDevice/RelayTest/SttDriverOper.h"
#endif

CString CSttAbnormalTest::m_strMacroName = "异常测试";
CString CSttAbnormalTest::m_strMacroID = ("SttAbnormalTest");
CString CSttAbnormalTest::m_strFilePostFix = "sttabntst";
// #include<QtDebug>
#define MAX_PARACOUNT_UI	4
#define MAX_PARACOUNT_BINARY 8
#define MAX_STATETEST_COUNT	6


CSttAbnormalTest::CSttAbnormalTest() : CSttTestBase()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    Init(MAX_STATETEST_COUNT);
}

void CSttAbnormalTest::Init(long nStateNums)
{
     CSttTestBase::Init();
     m_nCurStateIndex = -1;
}

long CSttAbnormalTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommReadResult(CSttStateTest)") );

#ifdef _PSX_IDE_QT_
	int nRet =CSttDeviceBase::g_pSttDeviceBase->GetTestResult(StateResult,(char*)&m_oDrvResults);
    if(nRet == -1)
        return false;

    if(m_oDrvResults.nCount<=0)//结果数量为空时，直接返回
    {
        qDebug()<<("CommReadResult(m_oDrvResults.cnt<=0)");
        return 0;
    }

    UINT nBinOrg=0xFF;

    for (int n=0; n<m_oDrvResults.nCount; n++)
    {
        int nSec=m_oDrvResults.stResult[n].nSec;
        int nNanoSec=m_oDrvResults.stResult[n].nNanoSec;

        if(m_oDrvResults.stResult[n].currentIndex >= m_oDrvStateAbnormalData.nStateCount)//当前状态号大于设置的总状态数时，返回
        {
            qDebug()<<("CommReadResult(m_oDrvResults.result[n].from >= m_nStateNumbers)");
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
            qDebug()<<("CommReadResult(type == STATE_TYPE_CHANGE)");
        }
            break;
        case STATE_RESULT_DI_CHANGE:
        {//开入变位时，记录所有的产生变位的结果记录
            int nBin = nBinOrg^m_oDrvResults.stResult[n].nInput;//取异或
            qDebug()<<("CommReadResult(type == STATE_TYPE_DI_CHANGE)");

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
            qDebug()<<("CommReadResult(type == STATE_TYPE_STOP)");
            bFinish = true;
        }
            break;
        }
    }
#endif

    return true;
}

void CSttAbnormalTest::EventProcess()
{
#ifdef _PSX_IDE_QT_
    int nret =CSttDeviceBase::g_pSttDeviceBase->GetTestResult(StateResult,(char*)&m_oDrvResults);

    if(nret <=0 ||nret<sizeof(structResult)+4)
    {
        return;
    }

    if(!m_Start)
        return;

    structResultItem* pResult = &m_oDrvResults;
    for(int i=0;i<pResult->nCount;i++)
    {
        structResult oItem = pResult->stResult[i];
        qDebug()<<"Result["<<i<<"].currentIndex="<<oItem.currentIndex;
        qDebug()<<"Result["<<i<<"].nType="<<oItem.nType;
        qDebug()<<"Result["<<i<<"].nSec="<<oItem.nSec;
        qDebug()<<"Result["<<i<<"].nNanoSec="<<oItem.nNanoSec;
    }
#endif
}

CSttAbnormalTest::~CSttAbnormalTest(void)
{
}

void CSttAbnormalTest::AfterSetParameter()
{
    m_nCurStateIndex = 0;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
}

double CSttAbnormalTest::GetTestTimeLong()
{
    float	fTime = 0.000 + 10;

    fTime += TIME_ONLINE_DELAY;		//等待时间过长，给10s缓冲

    return fTime;
}

long CSttAbnormalTest::CalReport(UINT nState)
{
    return 0;
}

void CSttAbnormalTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oAbnSimulationParas,pXmlSerialize);
}

long CSttAbnormalTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttAbnormalTest::Stop()
{
    m_Start = false;
    CSttTestBase::Stop();
}

void CSttAbnormalTest::StartTest()
{
    #define START_SEND_ABN				0x09
 
	CSttTestBase::StartTest();
#ifdef _PSX_IDE_QT_
    TtmToDrv();
    int nDownloadSize = 44 + sizeof(drv_abnstate)*m_oDrvStateAbnormalData.nStateCount;

    CSttDeviceBase::g_pSttDeviceBase->SetTestPara(AbnoramlTest, (char*)&m_oDrvStateAbnormalData , nDownloadSize);// 设置为状态序列参数模式 // 写入参数
    CSttDeviceBase::g_pSttDeviceBase->SetTestStart(AbnoramlTest);
#endif

    m_Start = true;
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSttAbnormalTest::DataDownload Finished") );
}

void CSttAbnormalTest::TtmToDrv()
{
#ifdef _PSX_IDE_QT_
	tmt_to_drv(this,&m_oDrvStateAbnormalData);
#endif
}
