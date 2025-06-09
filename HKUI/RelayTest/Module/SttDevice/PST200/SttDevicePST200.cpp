#include "SttDevicePST200.h"

CSttDevicePST200 *CSttDevicePST200::g_pSttDevicePST200=NULL;
long CSttDevicePST200::g_nSttDeviceRef = 0;
CRingMemBuf *g_pRecvStable2MBuf = NULL;
BOOL bExitStableThread = FALSE;
unsigned char pszPreBuf[MAX_2M_BLOCK_COUNT][MAX_2M_DATAIDX_VALUE][48];
long nReadPos = 0;
long n64ReadSizeTotal = 0;
long nOffLen = 0;
BOOL bThreadRun = TRUE;
long nPreSendSig[MAX_2M_BLOCK_COUNT][MAX_2M_DATAIDX_VALUE];
long nSubPkgIdxPos[MAX_2M_BLOCK_COUNT];
long nSubPkgLen[MAX_2M_BLOCK_COUNT];
long nSubPkgAddr[MAX_2M_BLOCK_COUNT];

CSttDevicePST200::CSttDevicePST200()
{

}

CSttDevicePST200::~CSttDevicePST200()
{

}

void CSttDevicePST200::Create()
{
    g_nSttDeviceRef++;

    if (g_nSttDeviceRef == 1)
    {
        g_pSttDevicePST200=new CSttDevicePST200;
        g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePST200;
    }
}

void CSttDevicePST200::Release()
{
    bExitStableThread = TRUE;
    Sleep(50);
    g_nSttDeviceRef--;

    if (g_nSttDeviceRef == 0)
    {
        delete g_pSttDevicePST200;
        g_pSttDevicePST200 = NULL;
    }

    if(g_pRecvStable2MBuf != NULL)
    {
        delete g_pRecvStable2MBuf;
        g_pRecvStable2MBuf = NULL;
    }
}

int CSttDevicePST200::InitDevice(BOOL bHasAdjFile)
{
    memset(nSubPkgIdxPos,0,MAX_2M_BLOCK_COUNT*4);
    memset(nSubPkgLen,0,MAX_2M_BLOCK_COUNT*4);
    memset(nSubPkgAddr,0,MAX_2M_BLOCK_COUNT*4);
    memset(nPreSendSig,0,MAX_2M_BLOCK_COUNT*MAX_2M_DATAIDX_VALUE*4);
    memset(pszPreBuf,0,MAX_2M_BLOCK_COUNT*MAX_2M_DATAIDX_VALUE*48);
    g_nSttRcdSocketUseZip = 0;
    g_pRecvStable2MBuf = new CRingMemBuf;
    g_pRecvStable2MBuf->Create(10240000);
    pthread_t nthreadid;
    pthread_create(&nthreadid,NULL,ProStableDataThread,(LPVOID)this);
    m_nCommfd=open("/dev/SttDriver_Pi1000",O_RDWR);
    m_pDegressMsg = (Drv_DegressMsg *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
#ifdef _PSX_QT_LINUX_
    qDebug()<<"Driver Mmap = "<<m_pDegressMsg;
#endif

    g_theSystemConfig->m_nHasWeek = 1;
    InitDApara(m_nCommfd,bHasAdjFile);

    //VOLT
    for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
    {
        PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nIndex];
        if(pModule==NULL)
            continue;

        CSttPowerCtrlBase *pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
        if(pCSttPowerCtrlBase==NULL)
        {
            pModule->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase*)(new CSttPowerCtrlV300_PI);
        }
    }
    //CURRENT
    for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
    {
        PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
        if(pModule==NULL)
            continue;

        CSttPowerCtrlBase *pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
        if(pCSttPowerCtrlBase==NULL)
            pModule->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase*)(new CSttPowerCtrlC20);
    }

    return m_nCommfd;
}

void CSttDevicePST200::AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,int nModuleType)
{
    CSttDeviceBase::AnalysisDrvSysInfo(oDrv_FeedBack,nModulePos,nModuleType);
    //466插件暂不考虑以下指标
    int nItemIndex=0;
    for(unsigned int i=0;i<g_theSttDeviceStatus->m_nAnalogCount;i++)
    {
        if(g_theSttDeviceStatus->m_oModule[i].m_nModulePos==nModulePos)
        {
            nItemIndex=i;
            break;
        }
    }
    STT_MODULE_STATUS &oModuleStatus=g_theSttDeviceStatus->m_oModule[nItemIndex];

    oModuleStatus.m_nIsVoltHot = 0;//电压过热
    oModuleStatus.m_nIsDCHot = 0;//直流过热
    oModuleStatus.m_nIsVoltWarining = 0;//电压告警
    oModuleStatus.m_nIsMissWarining = 0;//失地告警
}

void CSttDevicePST200::GetVoltCurRtData()
{
    CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
    if(pSttTestBase == NULL)
        return;

    GetRtData();
}

void CSttDevicePST200::EventProcessEx()
{
    char *pDrvResults=stt_test_get_drvresult_buff();
    int ret=read(m_nCommfd,pDrvResults,0x261);

    if(ret>0)
    {
        g_pRecvStable2MBuf->WriteBuf(pDrvResults,ret);
    }
}

void CSttDevicePST200::PreStartTestPro()
{
    memset(nSubPkgIdxPos,0,MAX_2M_BLOCK_COUNT*4);
    memset(nSubPkgLen,0,MAX_2M_BLOCK_COUNT*4);
    memset(nSubPkgAddr,0,MAX_2M_BLOCK_COUNT*4);
    tmt_Stable2MList *pStable2MList;
    for(int index = 0;index < MAX_2M_BLOCK_COUNT;index++)
    {
        pStable2MList = &m_oCIEC61850CfgMngr.m_oStable2MMngr.m_oStable2MSubList[0][index];
        for(int i = 0;i < pStable2MList->m_nDataPkgCount;i++)
        {
            nSubPkgAddr[index] = pStable2MList->m_oDataPkg[0].m_nAddr;
            nSubPkgLen[index] = pStable2MList->m_oDataPkg[0].m_nPkgLen;
            nSubPkgIdxPos[index] = pStable2MList->m_oDataPkg[0].m_nIdxMapChan;
            break;
        }
    }

    memset(nPreSendSig,0,MAX_2M_BLOCK_COUNT*MAX_2M_DATAIDX_VALUE*4);
    memset(pszPreBuf,0,MAX_2M_BLOCK_COUNT*MAX_2M_DATAIDX_VALUE*48);
    g_pRecvStable2MBuf->Init();
    nReadPos = 0;
    n64ReadSizeTotal = 0;
    nOffLen = 0;
    bThreadRun = TRUE;
}

void CSttDevicePST200::AfterTestFinishedPro()
{
    bThreadRun = FALSE;
}

void *ProStableDataThread(LPVOID pParam)
{
    CLogPrint::LogString(XLOGLEVEL_INFOR,_T(">>>>>>Create ProStableDataThread"));
    unsigned char pszBuf[1024000];
    unsigned char pszTempBuf[1024000];

    long nReadLen;
    long nPkgLen = 0;
    long nStable2MPkgCnt = 0;

    while(1)
    {
        Sleep(5);

        if(bExitStableThread)
            break;

        if(!bThreadRun)
        {
            continue;
        }

        nReadLen = g_pRecvStable2MBuf->ReadBuf((char*)(pszBuf + nOffLen),nReadPos,n64ReadSizeTotal,10240000);
        n64ReadSizeTotal += nReadLen;
        if(nReadLen == 0)
            continue;

L:
        if(pszBuf[0] == 0x05 && pszBuf[1] == 0x64 && pszBuf[2] == 0x05 && pszBuf[3] == 0x64)
        {
            nPkgLen = pszBuf[7];
            nPkgLen |= pszBuf[6] << 8;
            nPkgLen |= pszBuf[5] << 16;
            nPkgLen |= pszBuf[4] << 24;
            nPkgLen &= 0xFFFF;//改为Short类型

            if(nReadLen >= (nPkgLen*4 + 4))
            {
                long nLeftLen = nReadLen - (nPkgLen*4 + 4);
                memcpy(pszTempBuf,pszBuf + nPkgLen*4 + 4,nLeftLen);
                memcpy(pszBuf,pszTempBuf,nLeftLen);
                nReadLen = nLeftLen;
                nOffLen = 0;
            }
            else
            {
                nOffLen = nPkgLen*4 + 4;
                continue;
            }
        }

        if(pszBuf[0] == 0x05 && pszBuf[1] == 0x65 && pszBuf[2] == 0x05 && pszBuf[3] == 0x65)
        {
            if(nStable2MPkgCnt > 1800)
            {
                for(int i = 0; i < MAX_2M_BLOCK_COUNT;i++)
                {
                    for(int j = 0; j < MAX_2M_DATAIDX_VALUE;j++)
                    {
                        nPreSendSig[i][j]++;
                    }
                }

                nStable2MPkgCnt = 0;
            }
            nPkgLen = pszBuf[7];
            nPkgLen |= pszBuf[6] << 8;
            nPkgLen |= pszBuf[5] << 16;
            nPkgLen |= pszBuf[4] << 24;
            nPkgLen &= 0xFFFF;//改为Short类型

            if(nReadLen >= (nPkgLen*4 + 4))
            {
                //解报文内容
                long nPort = 0;
                switch(pszBuf[8])
                {
                case 0xE1:
                    nPort = 0;
                    break;
                case 0xE2:
                    nPort = 1;
                    break;
                case 0xE3:
                    nPort = 2;
                    break;
                case 0xE4:
                    nPort = 3;
                    break;
                case 0xE5:
                    nPort = 4;
                    break;
                case 0xE6:
                    nPort = 5;
                    break;
                case 0xE7:
                    nPort = 6;
                    break;
                case 0xE8:
                    nPort = 7;
                    break;
                }
                long nCmdType = pszBuf[25];
                long nIdx = 0;

                if(nCmdType == 0x99)
                {
                    g_oSttRcdSendSocket.WriteRecordBuf((char*)pszBuf,nPkgLen*4 + 4);
                }
                else
                {
                    if(pszBuf[9] != nSubPkgLen[nPort])
                    {
                        goto M;//报文长度不符合
                    }

                    if(pszBuf[24] != nSubPkgAddr[nPort])
                    {
                        goto M;//报文地址不符合
                    }

                    if(nSubPkgIdxPos[nPort] == 0)
                    {
                        nIdx = 0;
                    }
                    else
                    {
                        long nOffset = nSubPkgIdxPos[nPort];
                        if(nOffset < nSubPkgLen[nPort])
                        {
                            nIdx = pszBuf[24 + nOffset];
                            if(nIdx >= MAX_2M_DATAIDX_VALUE)
                            {
                                goto M;
                            }
                        }
                        else
                        {
                            goto M;
                        }
                    }

                    BOOL bRet = TRUE;
                    for(int i = 0;i< pszBuf[9];i++)
                    {
                        if(pszPreBuf[nPort][nIdx][i] != pszBuf[24 + i])
                        {
                            memcpy(pszPreBuf[nPort][nIdx],&pszBuf[24],pszBuf[9]);
                            g_oSttRcdSendSocket.WriteRecordBuf((char*)pszBuf,nPkgLen*4 + 4);
                            bRet = FALSE;

                            break;
                        }
                    }

                    if(bRet)
                    {
                        if(nPreSendSig[nPort][nIdx] > 0)
                        {
                            g_oSttRcdSendSocket.WriteRecordBuf((char*)pszBuf,nPkgLen*4 + 4);
                            nPreSendSig[nPort][nIdx] = 0;
                        }
                    }
                }
                nStable2MPkgCnt++;

M:
                long nLeftLen = nReadLen - (nPkgLen*4 + 4);
                memcpy(pszTempBuf,pszBuf + nPkgLen*4 + 4,nLeftLen);
                memcpy(pszBuf,pszTempBuf,nLeftLen);
                nReadLen = nLeftLen;
                nOffLen = 0;
                goto L;
            }
            else
            {
                nOffLen = nPkgLen*4 + 4;
                continue;
            }
        }
    }

    pthread_exit(0);
}
