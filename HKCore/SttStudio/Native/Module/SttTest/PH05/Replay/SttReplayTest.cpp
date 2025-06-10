#include "stdafx.h"
#include"SttReplayTest.h"
// #include<QtDebug>
#ifdef _PSX_IDE_QT_
#include <unistd.h>
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttReplayTest::m_strMacroName = "故障重放测试";
CString CSttReplayTest::m_strMacroID = ("ReplayTest");
CString CSttReplayTest::m_strFilePostFix = "replaytst";
CString CSttReplayTest::m_strMacroVer ="1.0";

CSttReplayTest::CSttReplayTest() : CSttTestBase()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;

    m_nCurrReqIndex = 0;	//当前需要请求ABBuf Index
    m_nCurrPlayIndex = 1;	//播放Index

    m_nChSelCount = 0;
    m_nModuleSelCount = 0;

    m_pOnceProcessBuf = CSttDeviceBase::g_pSttDeviceBase->m_pReplayChsBuf;
    m_pProcessBuf = NULL;
    Init();

    m_pComReplayBuffer = (Drv_ComReplayBuffer*)stt_test_get_drvparas_buff();
}

void CSttReplayTest::Init()
{ 
    tmt_ReplayParas::init();
    CSttTestBase::Init();
}

long CSttReplayTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    return 0;
}

CSttReplayTest::~CSttReplayTest(void)
{

}

void CSttReplayTest::AfterSetParameter()
{
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
}

void CSttReplayTest::SendDataToDevice(long nMdIndex)
{
    CComtradeDataBuffer* pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex);
    if (!pComtradeBuf->CanRead())
    {
        return;
    }
    float* pszSrcBuf = pComtradeBuf->GetBuffer();
    long nDataLen = pComtradeBuf->GetDataLen();
    long nPointLen = m_nChSelCount*4;
    long nPointsCnt = nDataLen/nPointLen;

    long nOffset = 0;
    long nModule = 0;
    long nUsedMdIdx = 0;
    TMT_REPLAY_MODULE *pModule = NULL;
    for (int nModuleIndex=0; nModuleIndex<m_nModuleCount; nModuleIndex++)
    {
        if (m_oModule[nModuleIndex].m_nSel == 0)
        {
            continue;
        }

        if(nUsedMdIdx == nMdIndex)
        {
            for (int n=0; n<nModuleIndex; n++)
            {
                if (m_oModule[n].m_nSel)
                {
                    for (int j = 0; j < m_oModule[n].m_nChUseCount; j++)
                    {
                        if(m_oModule[n].m_oChMap[j].m_nChSel)
                        {
                            nOffset++;
                        }
                    }
                }
            }
            pModule = &m_oModule[nModuleIndex];
            break;
        }

        nUsedMdIdx++;
    }

    if(pModule == NULL)
        return;

    long nChanCnt = pModule->m_nChUseCount;
    m_pComReplayBuffer->module = ModuleIndexTransToDrv(pModule->m_nIndex);
    m_pComReplayBuffer->pkglen = 0;
    m_pComReplayBuffer->oData.lenth = nPointsCnt*nChanCnt;
    for (int j = 0; j < nChanCnt; j++)
    {
        if(pModule->m_oChMap[j].m_nChSel)
        {
            m_pComReplayBuffer->pkglen += 4;
        }
    }

    Drv_ReplayCoefItems *pCoefItems = &m_oReplayConf.Items[nModule - 1];
    int nCode = 0x7fffffff;
    if(pCoefItems->nCode == 16)
    {
        nCode = 0x7fff;
    }
    int nReplayDataLen = 6;//FPGA播放数据长度

    float fvalue;
    for(int nPoint = 0;nPoint < nPointsCnt;nPoint++)
    {
        float* pszPointBuf = pszSrcBuf + nPoint*m_nChSelCount + nOffset;
        int nChanIdx = 0;
        long nChReplayData[48];
        memset(nChReplayData,0,48*4);
        for(int i = 0;i < nChanCnt;i++)
        {            
            if(pModule->m_oChMap[i].m_nChSel == 0)
            {
                continue;
            }

            fvalue = pszPointBuf[nChanIdx++];
            fvalue = fvalue * pCoefItems->Item[i].fCoef + pCoefItems->Item[i].fZero;
            fvalue = fvalue/pCoefItems->Item[i].fMaxValue;
            if(fabs(fvalue) > 0.999999) //限制幅值
            {
                if(fvalue > 0)
                {
                    fvalue = 0.999999;
                }
                else
                {
                    fvalue = -0.999999;
                }
            }
            fvalue = fvalue * pCoefItems->Item[i].fReverse;
            nChReplayData[pCoefItems->Item[i].nCh] = nCode*fvalue;
        }

        long nPointIndex = nPoint*nReplayDataLen;
        if(pCoefItems->nChCnt == 6)
        {
            for(int j = 0; j < 6; j++)
            {
                m_pComReplayBuffer->oData.dat[nPointIndex + j] = nChReplayData[j];
            }
        }
        else if(pCoefItems->nChCnt == 12)
        {
            long nTemp;

            for(int j = 0; j < 6; j++)
            {
                nTemp = nChReplayData[j * 2];
                if(nTemp < 0)
                {
                    nTemp = nTemp * (-1);
                    nTemp = nTemp << 16;
                    nTemp = nTemp * (-1);
                }
                else
                {
                    nTemp = nTemp << 16;
                }
                nTemp &= 0xffff0000;
                m_pComReplayBuffer->oData.dat[nPointIndex + j] |= nTemp;

                nTemp = nChReplayData[j * 2 + 1];
                if(nTemp < 0)
                {
                    nTemp = nTemp * (-1);
                    nTemp = nTemp << 16;
                    nTemp = nTemp * (-1);
                    nTemp = nTemp >> 16;
                }
                nTemp &= 0xffff;
                m_pComReplayBuffer->oData.dat[nPointIndex + j] |= nTemp;
            }
        }
    }
}

void CSttReplayTest::SendConfToDevice(long nMdIndex)
{

}

BOOL CSttReplayTest::EventProcess()
{
    BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
    int nfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
    long nRet = ioctl(nfd, 0x501, 0);
    if(nRet == 1)
    {
        //继续下载后续回放数据
        m_nCurrMdIndex++;
        if(m_nCurrMdIndex < m_nModuleCount)
            SendDataToDevice(m_nCurrMdIndex);
        else
        {
            if(m_bSendFinish)
            {
                for (int nModuleIndex=0; nModuleIndex<m_nModuleCount; nModuleIndex++)
                {
                    if (m_oModule[nModuleIndex].m_nSel == 0)
                    {
                        continue;
                    }

                    SendConfToDevice(nModuleIndex);
                }

                //开始回放
                CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("StartEventThread  ReplayTest"));
                CSttDeviceBase::g_pSttDeviceBase->SetTestStart(LtReplayTest);
            }
            else
            {
                CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
                ASSERT(pServerEngine != NULL);
                pServerEngine->Comtrade_SendRequestData(m_nCurrReqIndex);
            }
        }
    }
    else if(nRet == 2)
    {
        //实验结束中断
        ioctl(nfd,0x103,0);
        bTestFinished = TRUE;
    }
#endif
    return bTestFinished;
}

void CSttReplayTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(this,pXmlSerialize);

    if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

void CSttReplayTest::Stop()
{	
    SetTestStarting(FALSE);
    CSttTestBase::Stop();
}

void CSttReplayTest::Triger()
{
    //收到手动触发命令
    CSttDeviceBase::g_pSttDeviceBase->SetStateTriger();
    //通知驱动手动触发
}

void CSttReplayTest::OnSendDataFinish(int nIndex,int nSendNum)
{//Comtrade数据发送完成命令
    UINT nSendIndex = (UINT)nIndex & 0x7FFFFFFF;
    if (nSendIndex != 0)
    {
        m_bSendFinish = ((UINT)nIndex) >> 31;
    }

    m_nCurrReqIndex++;

    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnSendDataFinish:nIndex=%d,nSendNum=%d,m_nCurrReqIndex=%d"),nSendIndex,nSendNum,m_nCurrReqIndex);

    //通知接收线程数据已发送完成
    g_oSttComtradeRcvSocket.OnSendDataFinish(nSendIndex,nSendNum);
}

void CSttReplayTest::OnSendDataStart(int nIndex,int nSendNum)
{
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnSendDataStart:nIndex=%d,nSendNum=%d"),nIndex,nSendNum);

    //通知接收线程数据已发送完成
    g_oSttComtradeRcvSocket.OnSendDataStart(nIndex,nSendNum);
}

void CSttReplayTest::OnAfterMoveToComtradeBuf(int nIndex,int nDataLen)
{
    CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
    ASSERT(pServerEngine != NULL);

    if (nIndex == 0)
    {//之前请求的是LoopBuf数据，再请求ABuf数据
        pServerEngine->Comtrade_SendRequestData(1);
    }
    else
    {
        m_nCurrMdIndex = 0;
        SendDataToDevice(m_nCurrMdIndex);
    }
}

#define REPLAY_FLAG_WRITE_FINISH        0x01
#define REPLAY_FLAG_TEST_FINISH			0x02
#define REPLAY_FLAG_TEST_TRIP           0x03

void CSttReplayTest::StartTest()
{	
    if(GetTestStarting())
    {
        return;
    }

    SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
    CSttTestBase::StartTest();

    //重新初始化AB缓存
    CComtradeBufMngr::g_pComtradeBufMngr->ResetBuf();
    g_oSttComtradeRcvSocket.ResetRcvLen();
    m_nCurrReqIndex = 0;
    m_nCurrPlayIndex = 1;

    m_nChSelCount = GetChSelCount();
    m_nModuleSelCount = GetModuleSelCount();

    TtmToDrv();

    //收到开始测试命令后，根据配置参数请求数据
    CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
    ASSERT(pServerEngine != NULL);

    if (IsLoop())
    {//需要循环数据
        m_nCurrReqIndex = 0;
    }
    else
    {//无循环数据
        m_nCurrReqIndex = 1;
    }
    pServerEngine->Comtrade_SendRequestData(m_nCurrReqIndex);
}

void CSttReplayTest::TtmToDrv()
{
#ifdef _PSX_IDE_QT_
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_ComReplay(this,(char*)&m_oReplayConf);
#endif
}
