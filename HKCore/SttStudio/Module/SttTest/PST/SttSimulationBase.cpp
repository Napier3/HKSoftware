#include "stdafx.h"
#include"SttSimulationBase.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/Module/Driver466/IEC/IEC2MComMngr.h"
#endif

CString CSttSimulationBase::m_strMacroName = "仿真回放测试";
CString CSttSimulationBase::m_strMacroID = ("SimulationTest");
CString CSttSimulationBase::m_strFilePostFix = "sttptt";
CString CSttSimulationBase::m_strMacroVer ="1.0";
CSttSimulationBase* g_pSttSimulationBase = NULL;
CRingMemBuf* g_pRecvStable2MBuf = NULL;
CPstRcdDataBuffers* g_p2MSample = NULL;

BOOL bExit2MThread = FALSE;
long nReadPos = 0;
long n64ReadSizeTotal = 0;
long nOffLen = 0;
unsigned char pszBuf[1024000];
unsigned char pszTempBuf[1024000];
unsigned char pszPreAddBuf[8][960];//64*15,缓存15帧，缩小2M报文MQTT发送的帧数
long nPreAddBufLen[8];
long nPacketSize = 64;//最小回放单帧报文长度
unsigned char pszZeroBuf[64];


CSttSimulationBase::CSttSimulationBase()
{
    for(int i = 0;i < 48;i++)
    {
        m_fCoefWeek[i] = 1;
        m_fCoefSmv[i] = 1;
    }
    memset(pszZeroBuf,0,64);
}

void CSttSimulationBase::Init()
{
    g_pRecvStable2MBuf = new CRingMemBuf;
    g_pRecvStable2MBuf->Create(1024000);
    pthread_t nthreadid;
    pthread_create(&nthreadid,NULL,Pro2MRecordDataThread,(LPVOID)this);
}

CSttSimulationBase::~CSttSimulationBase(void)
{
    bExit2MThread = TRUE;
    Sleep(20);
}

void CSttSimulationBase::Stop()
{
    SetRecvStopCmd(TRUE);
    CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
}

void CSttSimulationBase::StartTest(long nStateIdx)
{
    SetRecvStopCmd(FALSE);
}

void CSttSimulationBase::ResetThreadPara()
{
    memset(nPreAddBufLen,0,4*8);
    nOffLen = 0;
    nReadPos = 0;
    n64ReadSizeTotal = 0;
    g_pRecvStable2MBuf->Reset();
}

void CSttSimulationBase::ConnectTo2M_BeforeTest(CPstPort2mMaps *pPst2mMaps,StPST100Para *pStPST100Para,int nCommfd)
{
#ifdef _PSX_QT_LINUX_
    CString strInitPkg[PST_PORT2M_MAX_COUNT];
    long nDataLen[PST_PORT2M_MAX_COUNT];
    for(int i = 0;i < PST_PORT2M_MAX_COUNT;i++)
    {
        strInitPkg[i] = "";
        nDataLen[i] = 0;
    }
    CPstPort2mMap *pPort2mMap = NULL;

    POS pos = pPst2mMaps->GetHeadPosition();
    while (pos != NULL)
    {
        pPort2mMap = (CPstPort2mMap *)pPst2mMaps->GetNext(pos);

        if (! pPort2mMap->IsPort2mUsed())
        {//PST100的光口，是否被使用
            continue;
        }

        if (pPort2mMap->m_strType != PSX_PORT_TYPE_OUTPUT)
        {
            continue;
        }

        CString strId = pPort2mMap->m_strID;
        strId = strId.trimmed();
        strId.Replace(RcdDataID_PST100_2M_OUT,"");
        long nIndex = strId.toInt() - 1;
        if(nIndex >= 0 && nIndex < PST_PORT2M_MAX_COUNT)
        {
            strInitPkg[nIndex] = pPort2mMap->m_strInit_Pkg.trimmed();
            strInitPkg[nIndex].Replace(" ","");
            qDebug()<<strInitPkg[nIndex];
            if(strInitPkg[nIndex].GetLength()%2 == 1)
            {
                strInitPkg[nIndex] = "";
            }
            else
            {
                strInitPkg[nIndex] = strInitPkg[nIndex];
            }
        }
    }

    unsigned char pszHandCheck[PST_PORT2M_MAX_COUNT][48];
    bool bTrans;
    for(int i = 0;i < PST_PORT2M_MAX_COUNT;i++)
    {
        nDataLen[i] = 0;
        memset(pszHandCheck[i],0,48);
        if(strInitPkg[i].GetLength() > 0)
        {
            nDataLen[i] = strInitPkg[i].GetLength()/2;
            if(nDataLen[i] > 44)
                nDataLen[i] = 44;

            for(int j = 0;j < nDataLen[i];j++)
            {
                pszHandCheck[i][j] = strInitPkg[i].mid(j*2,2).toInt(&bTrans,16);
            }

            unsigned short nSum = SumCheck(pszHandCheck[i],nDataLen[i]);
            pszHandCheck[i][22] = nSum & 0xFF;
            pszHandCheck[i][23] = (nSum >> 8) & 0xFF;

            unsigned short nCRC = CRC16(pszHandCheck[i],nDataLen[i] + 2,0xffff,0x1021,0xffff,true,true);
            pszHandCheck[i][24] = nCRC & 0xFF;
            pszHandCheck[i][25] = (nCRC >> 8) & 0xFF;
            nDataLen[i] += 4;
        }
    }

    //2M握手数据
    //17 55 00 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 e8 a8 xx xx
//    unsigned char pszHandCheck[48] = {0x17,0x55,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//                                      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe8,0xa8,
//                                      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//                                      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    DrvReplayPkg2M oReplayPkg2M;
    m_oReplayData2M.cnt = 0;

    long nNSec = 0;
    long nNSecPort = 0;
    long nSec = 0;
    for(int i = 0;i< 72000;i++)//按120秒进行初始化
    {
        if(nNSec > 1000000000)
        {
            nNSec -= 1000000000;
            nSec++;
        }

        oReplayPkg2M.sqnum[0] = 0x0;
        oReplayPkg2M.sqnum[1] = 0x0;
        oReplayPkg2M.sqnum[2] = (i >> 24)&0xFF;
        oReplayPkg2M.sqnum[3] = (i >> 16)&0xFF;
        oReplayPkg2M.sqnum[4] = (i >> 8)&0xFF;
        oReplayPkg2M.sqnum[5] = i&0xFF;
        oReplayPkg2M.utch[0] = (nSec >> 24)&0xFF;
        oReplayPkg2M.utch[1] = (nSec >> 16)&0xFF;
        oReplayPkg2M.utch[2] = (nSec >> 8)&0xFF;
        oReplayPkg2M.utch[3] = nSec&0xFF;
        nNSecPort = nNSec;
        nNSec += 1667000;

        nNSecPort = nNSecPort*0.001;
        nNSecPort = nNSecPort*1000;

        for(int j = 0;j < PST_PORT2M_MAX_COUNT;j++)
        {
            if(nDataLen[j] == 0)
                continue;

            switch(j)
            {
            case 0:
                oReplayPkg2M.port = 0xe1;
                break;
            case 1:
                oReplayPkg2M.port = 0xe2;
                break;
            case 2:
                oReplayPkg2M.port = 0xe3;
                break;
            case 3:
                oReplayPkg2M.port = 0xe4;
                break;
            case 4:
                oReplayPkg2M.port = 0xe5;
                break;
            case 5:
                oReplayPkg2M.port = 0xe6;
                break;
            case 6:
                oReplayPkg2M.port = 0xe7;
                break;
            case 7:
                oReplayPkg2M.port = 0xe8;
                break;
            }

            oReplayPkg2M.framelen = nDataLen[j];
            oReplayPkg2M.utcl[0] = (nNSecPort >> 24)&0xFF;
            oReplayPkg2M.utcl[1] = (nNSecPort >> 16)&0xFF;
            oReplayPkg2M.utcl[2] = (nNSecPort >> 8)&0xFF;
            oReplayPkg2M.utcl[3] = nNSecPort&0xFF;
            nNSecPort += 50000;//间隔50微秒，不然硬件反应不过来

            memcpy(oReplayPkg2M.framedata,pszHandCheck[j],48);
            memcpy(&m_oReplayData2M.pkg[m_oReplayData2M.cnt],&oReplayPkg2M,64);
            m_oReplayData2M.cnt++;

            if(m_oReplayData2M.cnt == 20000)
            {
                pStPST100Para->n2MReplayTripPosition[0] += m_oReplayData2M.cnt;
                ioctl(nCommfd,0x309,0);
                write(nCommfd,(char*)&m_oReplayData2M,sizeof(DrvReplayData2M));
                m_oReplayData2M.cnt = 0;
            }
        }
    }

    if(m_oReplayData2M.cnt > 0)
    {
        pStPST100Para->n2MReplayTripPosition[0] += m_oReplayData2M.cnt;
        ioctl(nCommfd,0x309,0);
        write(nCommfd,(char*)&m_oReplayData2M,sizeof(DrvReplayData2M));
    }

#endif
}

void CSttSimulationBase::Send2MDataToDrv(CPstRcdDataBuffers* p2MReplay,int nCommfd)
{
#ifdef _PSX_QT_LINUX_

    m_oReplayData2M.cnt = 0;
    long nIndex[8];
    for(int i = 0;i < 8;i++)
    {
        if(p2MReplay->m_pRcdDataBuffers[i]->m_oRcdDataBuffer.CanRead(1))
        {
            nIndex[i] = 0;
        }
        else
        {
            nIndex[i] = -1;
        }
    }
    double dPreTime = 0;
    double dTime;
    long nMinIdx;
    ConverStruct oTrans;
    BOOL bHasDataToDrv = FALSE;

    while(TRUE)
    {
        dTime = 0;
        nMinIdx = -1;
        for(int i = 0;i < 8;i++)
        {
            CPstRcdDataBuffer* pRcdDataBuffer = &p2MReplay->m_pRcdDataBuffers[i]->m_oRcdDataBuffer;

            if(nIndex[i] >= 0)
            {
                if((pRcdDataBuffer->m_nDataLength - nIndex[i]*64) >= 64)
                {
                    char* pszBuf = pRcdDataBuffer->m_pBuffer + nIndex[i]*64;
                    oTrans.b[0] = pszBuf[11];
                    oTrans.b[1] = pszBuf[10];
                    oTrans.b[2] = pszBuf[9];
                    oTrans.b[3] = pszBuf[8];
                    double d2MTime = oTrans.l;
                    oTrans.b[0] = pszBuf[15];
                    oTrans.b[1] = pszBuf[14];
                    oTrans.b[2] = pszBuf[13];
                    oTrans.b[3] = pszBuf[12];
                    oTrans.l = oTrans.l*0.001;
                    oTrans.l = oTrans.l*1000 + (i + 1)*100;//防止出现时间相同的报文，硬件允许1微秒误差
                    d2MTime += oTrans.l*0.000000001;

                    if(dTime < 1)
                    {
                        dTime = d2MTime;
                        nMinIdx = i;
                    }
                    else
                    {
                        if(d2MTime < dTime)
                        {
                            dTime = d2MTime;
                            nMinIdx = i;
                        }
                    }
                }
            }
        }

        if(nMinIdx < 0)
            break;

        CPstRcdDataBuffer* pRcdDataBuffer = &p2MReplay->m_pRcdDataBuffers[nMinIdx]->m_oRcdDataBuffer;
        memcpy(&m_oReplayData2M.pkg[m_oReplayData2M.cnt],pRcdDataBuffer->m_pBuffer + nIndex[nMinIdx]*64,64);
        switch(nMinIdx)
        {
        case 0:
            m_oReplayData2M.pkg[m_oReplayData2M.cnt].port = 0xe1;
            break;
        case 1:
            m_oReplayData2M.pkg[m_oReplayData2M.cnt].port = 0xe2;
            break;
        case 2:
            m_oReplayData2M.pkg[m_oReplayData2M.cnt].port = 0xe3;
            break;
        case 3:
            m_oReplayData2M.pkg[m_oReplayData2M.cnt].port = 0xe4;
            break;
        case 4:
            m_oReplayData2M.pkg[m_oReplayData2M.cnt].port = 0xe5;
            break;
        case 5:
            m_oReplayData2M.pkg[m_oReplayData2M.cnt].port = 0xe6;
            break;
        case 6:
            m_oReplayData2M.pkg[m_oReplayData2M.cnt].port = 0xe7;
            break;
        case 7:
            m_oReplayData2M.pkg[m_oReplayData2M.cnt].port = 0xe8;
            break;
        }


        oTrans.b[0] = m_oReplayData2M.pkg[m_oReplayData2M.cnt].utch[3];
        oTrans.b[1] = m_oReplayData2M.pkg[m_oReplayData2M.cnt].utch[2];
        oTrans.b[2] = m_oReplayData2M.pkg[m_oReplayData2M.cnt].utch[1];
        oTrans.b[3] = m_oReplayData2M.pkg[m_oReplayData2M.cnt].utch[0];
        double dTimeCurPoint = oTrans.l;
        oTrans.b[0] = m_oReplayData2M.pkg[m_oReplayData2M.cnt].utcl[3];
        oTrans.b[1] = m_oReplayData2M.pkg[m_oReplayData2M.cnt].utcl[2];
        oTrans.b[2] = m_oReplayData2M.pkg[m_oReplayData2M.cnt].utcl[1];
        oTrans.b[3] = m_oReplayData2M.pkg[m_oReplayData2M.cnt].utcl[0];
        dTimeCurPoint += oTrans.l*0.000000001;

        if(dPreTime > 1)
        {
            double dDiff = dTimeCurPoint - dPreTime;
            if(dDiff < 0.000005)
            {
                dTimeCurPoint = dPreTime + 0.000005;
                oTrans.l = (long)dTimeCurPoint;
                m_oReplayData2M.pkg[m_oReplayData2M.cnt].utch[3] = oTrans.b[0];
                m_oReplayData2M.pkg[m_oReplayData2M.cnt].utch[2] = oTrans.b[1];
                m_oReplayData2M.pkg[m_oReplayData2M.cnt].utch[1] = oTrans.b[2];
                m_oReplayData2M.pkg[m_oReplayData2M.cnt].utch[0] = oTrans.b[3];

                oTrans.l = (dTimeCurPoint - oTrans.l)*1000000000;
                m_oReplayData2M.pkg[m_oReplayData2M.cnt].utcl[3] = oTrans.b[0];
                m_oReplayData2M.pkg[m_oReplayData2M.cnt].utcl[2] = oTrans.b[1];
                m_oReplayData2M.pkg[m_oReplayData2M.cnt].utcl[1] = oTrans.b[2];
                m_oReplayData2M.pkg[m_oReplayData2M.cnt].utcl[0] = oTrans.b[3];
            }
        }
        dPreTime = dTimeCurPoint;//记录前一个点的播放时间

        nIndex[nMinIdx]++;
        m_oReplayData2M.cnt++;
        bHasDataToDrv = TRUE;

        if(m_oReplayData2M.cnt == 20000)
        {
            ioctl(nCommfd,0x309,0);
            write(nCommfd,(char*)&m_oReplayData2M,sizeof(DrvReplayData2M));
            bHasDataToDrv = FALSE;
            m_oReplayData2M.cnt = 0;
        }
    }

    if(bHasDataToDrv)
    {
        ioctl(nCommfd,0x309,0);
        write(nCommfd,(char*)&m_oReplayData2M,sizeof(DrvReplayData2M));
    }

#endif
}

void CSttSimulationBase::Replay2MDataLog(CPstRcdDataBuffers* p2MReplay)
{
    QFile file("/mnt/Stt/Bin/Replay2MData");
    if(file.open(QIODevice::WriteOnly))
    {
        char pDestBuf[4096000];
        long nDataLen = p2MReplay->m_pRcdDataBuffers[0]->m_oRcdDataBuffer.m_nDataLength;
        while(nDataLen > 0)
        {
            long nRdLen = p2MReplay->m_pRcdDataBuffers[0]->m_oRcdDataBuffer.ReadBuffer(pDestBuf,4096000);
            nDataLen -=nRdLen;
            file.write(pDestBuf,nRdLen);
        }

        file.flush();
        file.close();
        system("sync");
    }
    p2MReplay->m_pRcdDataBuffers[0]->m_oRcdDataBuffer.ResetRead();
}

void CSttSimulationBase::Record2MDataLog(CPstRcdDataBuffers* p2MSample)
{
    QFile file("/mnt/Stt/Bin/Record2MData");
    if(file.open(QIODevice::WriteOnly))
    {
        char pDestBuf[4096000];
        long nDataLen = p2MSample->m_pRcdDataBuffers[0]->m_oRcdDataBuffer.m_nDataLength;
        while(nDataLen > 0)
        {
            long nRdLen = p2MSample->m_pRcdDataBuffers[0]->m_oRcdDataBuffer.ReadBuffer(pDestBuf,4096000);
            nDataLen -=nRdLen;
            file.write(pDestBuf,nRdLen);
        }

        file.flush();
        file.close();
        system("sync");
    }
    p2MSample->m_pRcdDataBuffers[0]->m_oRcdDataBuffer.ResetRead();
}

void CSttSimulationBase::GetRTDSDataDebug(CPstRcdDataBuffer* pRtdsReplayData)
{
#ifdef _PSX_QT_LINUX_

    QFile file("/mnt/Stt/Bin/WaveData");
    pRtdsReplayData->ResetWrite();
    pRtdsReplayData->ResetDatas();
    pRtdsReplayData->ResetRead();
    char pDestBuf[4096];
    if(file.open(QIODevice::ReadOnly))
    {
        long nDataLen = file.read(pDestBuf,4096);
        while(nDataLen > 0)
        {
            if((pRtdsReplayData->m_nDataLength + nDataLen) < g_oPstRcdDataBufferLen.nRtdsBufLen)
            {
                pRtdsReplayData->AddBuffer(pDestBuf,nDataLen);
                nDataLen = file.read(pDestBuf,4096);
            }
        }

        file.flush();
        file.close();
    }

#endif
}

void CSttSimulationBase::SetRTDSDataDebug(CSttHdChRcdObject* pRtdsSampleRcdObject)
{
#ifdef _PSX_QT_LINUX_

    QFile file("/mnt/Stt/Bin/WaveData");
    pRtdsSampleRcdObject->m_oRcdDataBuffer.ResetWrite();
    pRtdsSampleRcdObject->m_oRcdDataBuffer.ResetDatas();
    pRtdsSampleRcdObject->m_oRcdDataBuffer.ResetRead();
    long nLen = pRtdsSampleRcdObject->m_nLenEachWrite;
    CPstRcdDataBuffer *pRcdDataBuffer = &pRtdsSampleRcdObject->m_oRcdDataBuffer;
    char pDestBuf[nLen];
    if(file.open(QIODevice::ReadOnly))
    {
        long nDataLen = file.read(pDestBuf,nLen);
        while(nDataLen > 0)
        {
            if((pRcdDataBuffer->m_nDataLength + nDataLen) < g_oPstRcdDataBufferLen.nRtdsBufLen)
            {
                pRcdDataBuffer->AddBuffer(pDestBuf,nDataLen);
                nDataLen = file.read(pDestBuf,nLen);
                if(nDataLen != nLen)
                    break;
            }
        }

        file.flush();
        file.close();
    }

#endif
}

void CSttSimulationBase::SaveRTDSDataDebug(CSttHdChRcdObject* pRtdsSampleRcdObject)
{
#ifdef _PSX_QT_LINUX_

    QFile file("/mnt/Stt/Bin/WaveData");
    long nLen = pRtdsSampleRcdObject->m_nLenEachWrite;
    CPstRcdDataBuffer *pRcdDataBuffer = &pRtdsSampleRcdObject->m_oRcdDataBuffer;
    char pDestBuf[nLen];
    if(file.open(QIODevice::WriteOnly))
    {
        while(TRUE)
        {
            long nReadLen = pRcdDataBuffer->ReadBuffer(pDestBuf,nLen);
            if(nReadLen == nLen)
            {
                file.write(pDestBuf,nLen);
            }
            else
                break;
        }

        file.flush();
        file.close();
    }

    pRtdsSampleRcdObject->m_oRcdDataBuffer.ResetRead();
#endif
}

void CSttSimulationBase::SaveRTDSDataDebug(CPstRcdDataBuffer* pRtdsReplayData)
{
#ifdef _PSX_QT_LINUX_

    QFile file("/mnt/Stt/Bin/WaveData");
    char pDestBuf[1024];
    if(file.open(QIODevice::WriteOnly))
    {
        while(TRUE)
        {
            long nReadLen = pRtdsReplayData->ReadBuffer(pDestBuf,1024);
            if(nReadLen == 1024)
            {
                file.write(pDestBuf,1024);
            }
            else
                break;
        }

        file.flush();
        file.close();
    }

    pRtdsReplayData->ResetRead();
#endif
}

void Pro2MPkg()
{
    //05 64 a3 03 00 00 00 30
    //e1 1a 90 dd 00 0e 6f 37 55 e5 62 46 26 a2 38 40
    //14 55 00 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 eb a8 33 17 00 00 00 00 00 00

    long nReadLen = g_pRecvStable2MBuf->ReadBuf((char*)(pszBuf + nOffLen),nReadPos,n64ReadSizeTotal,1008000);
    n64ReadSizeTotal += nReadLen;
    if(nReadLen == 0)
        return;

    nReadLen += nOffLen;
L:
    if(nReadLen >= 72)
    {
        if(pszBuf[0] == 0x05 && pszBuf[1] == 0x64 && (pszBuf[2]&0xF0) == 0xA0)
        {
            long nPacketLen = pszBuf[7];
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

            memcpy(pszPreAddBuf[nPort] + nPreAddBufLen[nPort],pszBuf+8,nPacketLen);
            nPreAddBufLen[nPort] += nPacketLen;
            memcpy(pszPreAddBuf[nPort] + nPreAddBufLen[nPort],pszZeroBuf,64 - nPacketLen);
            nPreAddBufLen[nPort] += 64 - nPacketLen;

            if(nPreAddBufLen[nPort] == 960)
            {
                g_p2MSample->m_pRcdDataBuffers[nPort]->m_oRcdDataBuffer.AddBuffer((char*)pszPreAddBuf[nPort],960);
                nPreAddBufLen[nPort] = 0;
            }

            long nLeftLen = nReadLen - (nPacketLen + 8);
            memcpy(pszTempBuf,pszBuf + (nPacketLen + 8),nLeftLen);
            memcpy(pszBuf,pszTempBuf,nLeftLen);
            nReadLen = nLeftLen;
        }
        else
        {
            long nLeftLen = nReadLen - 1;
            memcpy(pszTempBuf,pszBuf + 1,nLeftLen);
            memcpy(pszBuf,pszTempBuf,nLeftLen);
            nReadLen = nLeftLen;
        }
        goto L;
    }
    else
    {
        nOffLen = nReadLen;
    }
}

void *Pro2MRecordDataThread(LPVOID pParam)
{
    CLogPrint::LogString(XLOGLEVEL_INFOR,_T(">>>>>>Create Pro2MRecordDataThread"));
    while(1)
    {
        Sleep(5);

        if(bExit2MThread)
            break;

        Pro2MPkg();
    }

    pthread_exit(0);
}
