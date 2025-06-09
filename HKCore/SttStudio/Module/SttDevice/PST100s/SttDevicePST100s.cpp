#include "SttDevicePST100s.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../Module/Driver466/IEC/IEC2MComMngr.h"

CSttDevicePST100s *CSttDevicePST100s::g_pSttDevicePST100s = NULL;
long CSttDevicePST100s::g_nSttDeviceRef = 0;

CPstRcdDataBuffers *pRtdsSampleForThread;

BOOL bExitThread = FALSE;
int nRecordPkgType = 0;
long nRecordStartType = 1;//0-立即录波 1-等待有RTDS数据才录波
long nRecordStopDelayMs = 20000;//无切机命令条件下录波最大延时时间20000
long n2MTripDelayMs = 5000;//有故障信号后录波最大延时时间,超过5秒不算相继故障区间
BOOL bIsRecording = FALSE;

CSttDevicePST100s::CSttDevicePST100s()
{
}

CSttDevicePST100s::~CSttDevicePST100s()
{
    if(m_pSttPst100App != NULL)
    {
        delete m_pSttPst100App;
        m_pSttPst100App = NULL;
    }

    delete m_pDrvResults;
}

void CSttDevicePST100s::Create()
{
    g_nSttDeviceRef++;

    if(g_nSttDeviceRef == 1)
    {
        g_pSttDevicePST100s = new CSttDevicePST100s;
        g_pSttDeviceBase = (CSttDeviceBase *)g_pSttDevicePST100s;
    }
}

void CSttDevicePST100s::Release()
{
    bExitThread = TRUE;
    Sleep(50);
    g_nSttDeviceRef--;

    if(g_nSttDeviceRef == 0)
    {
        delete g_pSttDevicePST100s;
        g_pSttDevicePST100s = NULL;
    }

    if(g_pRecvStable2MBuf != NULL)
    {
        delete g_pRecvStable2MBuf;
        g_pRecvStable2MBuf = NULL;
    }
}

int CSttDevicePST100s::InitDevice(BOOL bHasAdjFile)
{
    //ignor SIGPIPE (send error after socket disconnect)
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGPIPE);
    sigprocmask(SIG_BLOCK, &set, NULL);
    m_pDrvResults = new unsigned char[8 * 1024 * 1024];
    m_pSttPst100App = new CSttPst100App();
    m_pSttPst100App->InitSttPstApp(FALSE);
    g_pTheOwnIotDevice->SetSN(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strSN);
    g_pTheOwnIotDevice->SetModel(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strDeviceName);
    m_pSttPst100App->Connect();
    m_pSttPst100App->m_oRcdDataBufferMngr.ResetRcdBuffers();
    m_nCommfd = open("/dev/SttDriver_PST100s", O_RDWR);
    pRtdsSampleForThread = &m_pSttPst100App->m_oRcdDataBufferMngr.m_oRtdsSample;
    g_p2MSample = &m_pSttPst100App->m_oRcdDataBufferMngr.m_o2MSample;
    m_p2MReplay = &m_pSttPst100App->m_oRcdDataBufferMngr.m_o2MPlay;
    m_pBoutReplay = &m_pSttPst100App->m_oRcdDataBufferMngr.m_oBout;
    memset(&m_oModuleDef, 0, sizeof(DrvModuleDef));
    m_nValidRtdsPorts = 0;//主口，备用口
	m_oModuleDef.n2MModulePos = 0;
	m_oModuleDef.nRTDS1Pos = 0;
	m_oModuleDef.nRTDS2Pos = 0;

	for(int i = 0;i < g_theDeviceSystemParameter->m_nModuleCount_D;i++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[i];
		if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_DIGITAL_0G8M)
		{
			//主口
			m_oModuleDef.nRTDS1Pos = pModule->m_oModuleAttr.m_nModuleIndex - 1;
			m_nValidRtdsPorts++;
		}
		else if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_DIGITAL_4G4M)
		{
			//备口
			m_oModuleDef.nRTDS2Pos = pModule->m_oModuleAttr.m_nModuleIndex - 1;
			m_nValidRtdsPorts++;
		}
	}

    if(m_nValidRtdsPorts == 0)
    {
        //默认配置
        m_nValidRtdsPorts = 1;
        m_oModuleDef.nRTDS1Pos = 2;//位置3
    }	

    if(g_theDeviceSystemParameter->m_nModuleCount_Stable2M > 0)
    {
        m_oModuleDef.n2MModulePos = g_theDeviceSystemParameter->m_oModules_Stable2M[0]->m_oModuleAttr.m_nModuleIndex - 1;
    }

    ioctl(m_nCommfd, 0x404, 0);
    write(m_nCommfd, &m_oModuleDef, sizeof(DrvModuleDef));
    ioctl(m_nCommfd, 0xA00, 1);
    ioctl(m_nCommfd, 0x103, 0);
    ioctl(m_nCommfd, 0x402, 0); //禁止2M报文上送使能
	ioctl(m_nCommfd, 0x409, 0); //设置RTDS采样率,0-不修改

    pthread_t nthreadid;
    pthread_create(&nthreadid, NULL, ProRtdsDataThread, (LPVOID)this);
    m_bDevStaIsInit = TRUE;
    return m_nCommfd;
}

void CSttDevicePST100s::AfterTestFinish()
{
    read(m_nCommfd, &m_o2MTripLog, 0x263);
    CDataGroup oDataGroup;
    m_pSttPst100App->EventTestFinish(&oDataGroup);
    bIsRecording = FALSE;

    if(m_o2MTripLog.oData[8].nEnable)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("Rtds Switch,sec = %d,Nsec = %d"),
                                   m_o2MTripLog.oData[8].nSec, m_o2MTripLog.oData[8].nNSec);
    }

    for(int j = 0; j < 8; j++)
    {
        if(m_o2MTripLog.oData[j].nEnable)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("2M-Index[%d] Switch,sec = %d,Nsec = %d"),
                                       j, m_o2MTripLog.oData[8].nSec, m_o2MTripLog.oData[8].nNSec);
        }
    }
}

void CSttDevicePST100s::EventProcessEx()
{
    //05 64 a3 03 00 00 00 30
    //e1 1a b9 57 00 4e b9 57 55 e5 78 81 0f 86 d1 0c
    //14 55 00 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 eb a8 33 17
    int ret = read(m_nCommfd, m_pDrvResults, 0x261);

    //    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ret = %d"),ret);
    if(ret > 0)
    {
        //判断当前数据类型
        nRecordPkgType = ioctl(m_nCommfd, 0x406, 0);

        switch(nRecordPkgType)
        {
            case 1:
            {
//            Drvfile.write((char*)m_pDrvResults,ret);
                //RTDS 光口1
                CSttHdChRcdObject *pHdChRcdObject = pRtdsSampleForThread->m_pRcdDataBuffers[0];
                pHdChRcdObject->m_oRingMemBuf.WriteBuf((char *)m_pDrvResults, ret);

                while(TRUE)
                {
                    if(pHdChRcdObject->RingBufToRcdBuf() == 0) //20221111 zhoulei
                    {
                        break;
                    }
                }
            }
            break;

            case 2:
            {
                //RTDS 光口2
                CSttHdChRcdObject *pHdChRcdObject = pRtdsSampleForThread->m_pRcdDataBuffers[1];
                pHdChRcdObject->m_oRingMemBuf.WriteBuf((char *)m_pDrvResults, ret);

                while(TRUE)
                {
                    if(pHdChRcdObject->RingBufToRcdBuf() == 0) //20221111 zhoulei
                    {
                        break;
                    }
                }
            }
            break;

            case 4:
                //2M
                g_pRecvStable2MBuf->WriteBuf((char *)m_pDrvResults, ret);
                break;
        }
    }

    ret = read(m_nCommfd, m_pDrvResults, 0x262);

    if(ret > 0)
    {
        long nDrvResItemLen = sizeof(DrvResultItem);

        for(int i = 0; i < ret / nDrvResItemLen; i++)
        {
            memcpy(&m_oResultItem, m_pDrvResults + i * nDrvResItemLen, nDrvResItemLen);

            //            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ntype = %d"),m_oResultItem.ntype);
            switch(m_oResultItem.ntype)
            {
                case 0:
                {
                    g_pSttSimulationBase->SetTestStarting(FALSE);
                    m_nReadRTDSPort = 0;
                    ioctl(m_nCommfd, 0x403, 0); //申请RTDS位置1数据
                }
                break;

                case 3:
                {
                    //RTDS READY
                    //时间触发时，RTDS有数即录波
                    if(g_pSttSimulationBase->GetTestStarting() && nRecordStartType == 1)
                    {
                        if(!bIsRecording)
                        {
                            ioctl(m_nCommfd, 0x103, 0x07);
                            bIsRecording = TRUE;
                        }
                    }
                }
                break;

                case 5:
                {
                    //RTDS光口1数据读取结束
                    if(m_nValidRtdsPorts > 1)
                    {
                        m_nReadRTDSPort = 1;//读取备用口
                        ioctl(m_nCommfd, 0x403, 1); //申请RTDS位置2数据
                    }
                    else
                    {
                        //测试结束
                        AfterTestFinish();
                    }
                }
                break;

                case 6:
                {
                    //RTDS光口2数据读取结束
                    AfterTestFinish();
//                g_pSttSimulationBase->SetRTDSDataDebug(pRtdsSampleForThread->m_pRcdDataBuffers[0]);
                }
                break;

                case 7:
                    ioctl(m_nCommfd, 0x403, m_nReadRTDSPort);
                    break;
            }
        }
    }
}

void CSttDevicePST100s::SendStartToDrv()
{
    g_pSttSimulationBase->ResetThreadPara();
    //数据都已发送完毕
    //1、开始2M回放
    ioctl(m_nCommfd, 0x103, 5);
    //2、开启录波控制，驱动判断通过后上传RTDS和2M录波数据
    bIsRecording = FALSE;
    g_pSttSimulationBase->SetTestStarting(TRUE);
    CDataGroup oDataGroup;
    m_pSttPst100App->EventTestStarted(&oDataGroup);
	// g_pSttSimulationBase->SetRecvStopCmd(FALSE);
    m_nReadRTDSPort = 0;

    if(nRecordStartType == 0)
    {
        //时间触发时，RTDS有数即录波
        ioctl(m_nCommfd, 0x103, 0x07);
        bIsRecording = TRUE;
    }
    else
    {
        ioctl(m_nCommfd, 0x504, 0); //CLear RTDS RecordSignal
    }
}

void CSttDevicePST100s::SetReplayBout(int nTestType)
{
    ioctl(m_nCommfd, 0x506, 0); //清除开关量回放缓存

    long nSec, nNSec, nBiValue_32;
    char *pszBinBuf;
    long nPST200Count = m_pSttPst100App->m_oInputMap.GetCount();
	m_oReplayBout.cnt = nPST200Count;

	if(nTestType == 0)
	{
		for(int i = 0; i < nPST200Count; i++)
		{
			m_oReplayBout.pkg[i].data[0] = 0x05640564;
			m_oReplayBout.pkg[i].data[2] = 0x01;
			m_oReplayBout.pkg[i].data[3] = i + 1; //设备号
			m_oReplayBout.pkg[i].data[4] = 0x00; //开入默认断开
			m_oReplayBout.pkg[i].data[5] = 0x00;
			m_oReplayBout.pkg[i].data[6] = (1 + i) * 10000/20; //时间间隔默认10微妙
			m_oReplayBout.pkg[i].data[1] = 5;
			m_oReplayBout.pkg[i].length = m_oReplayBout.pkg[i].data[1] + 2;
		}
	}
	else
	{
		long nIndex = 0;
		//200开入量返回
		for(int i = 0; i < nPST200Count; i++)
		{		
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("PST200[%d] m_nDataLength = %d"),
									   i, m_pBoutReplay->m_pRcdDataBuffers[i]->m_oRcdDataBuffer.m_nDataLength);
			long nCount = m_pBoutReplay->m_pRcdDataBuffers[i]->m_oRcdDataBuffer.m_nDataLength / 12;

			for(int j = 0; j < nCount; j++)
			{
				pszBinBuf = m_pBoutReplay->m_pRcdDataBuffers[i]->m_oRcdDataBuffer.m_pBuffer + j * 12;
				memcpy(&nSec, pszBinBuf, 4);
				memcpy(&nNSec, pszBinBuf + 4, 4);
				memcpy(&nBiValue_32, pszBinBuf + 8, 4);		
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("PST200[%d],Log[%d] Value = %d"),
										   i, j, nBiValue_32);

				m_oReplayBout.pkg[nIndex].data[0] = 0x05640564;
				m_oReplayBout.pkg[nIndex].data[1] = 5;
				m_oReplayBout.pkg[nIndex].data[2] = 0x01;
				m_oReplayBout.pkg[nIndex].data[3] = i + 1; //设备号
				if(j == 0)
				{
					m_oReplayBout.pkg[nIndex].data[4] = 0x00; //开入默认断开
					m_oReplayBout.pkg[nIndex].data[5] = 0x00;
					m_oReplayBout.pkg[nIndex].data[6] = 0x00;
				}
				else
				{
					m_oReplayBout.pkg[nIndex].data[4] = nBiValue_32;
					m_oReplayBout.pkg[nIndex].data[5] = 0x00;
					m_oReplayBout.pkg[nIndex].data[6] = 100000000 / 20;
				}

				m_oReplayBout.pkg[nIndex].length = m_oReplayBout.pkg[nIndex].data[1] + 2;
				nIndex++;
			}
		}
		m_oReplayBout.cnt = nIndex;
	}

	// if(nTestType == 2)
	// {
	// 	long nIndex = 0;
	// 	m_oReplayBout.pkg[nIndex].data[0] = 0x05640564;
	// 	m_oReplayBout.pkg[nIndex].data[1] = 5;
	// 	m_oReplayBout.pkg[nIndex].data[2] = 0x01;
	// 	m_oReplayBout.pkg[nIndex].data[3] = 1; //设备号
	// 	m_oReplayBout.pkg[nIndex].data[4] = 0x00; //开入默认断开
	// 	m_oReplayBout.pkg[nIndex].data[5] = 0x00;
	// 	m_oReplayBout.pkg[nIndex].data[6] = 0x00;
	// 	m_oReplayBout.pkg[nIndex].length = m_oReplayBout.pkg[nIndex].data[1] + 2;
	// 	nIndex++;

	// 	m_oReplayBout.pkg[nIndex].data[0] = 0x05640564;
	// 	m_oReplayBout.pkg[nIndex].data[1] = 5;
	// 	m_oReplayBout.pkg[nIndex].data[2] = 0x01;
	// 	m_oReplayBout.pkg[nIndex].data[3] = 1; //设备号
	// 	m_oReplayBout.pkg[nIndex].data[4] = 0x03;
	// 	m_oReplayBout.pkg[nIndex].data[5] = 0x00;
	// 	m_oReplayBout.pkg[nIndex].data[6] = 7000000 / 20; //时间单位为20纳秒,共64位
	// 	m_oReplayBout.pkg[nIndex].length = m_oReplayBout.pkg[nIndex].data[1] + 2;
	// 	nIndex++;

	// 	m_oReplayBout.pkg[nIndex].data[0] = 0x05640564;
	// 	m_oReplayBout.pkg[nIndex].data[1] = 5;
	// 	m_oReplayBout.pkg[nIndex].data[2] = 0x01;
	// 	m_oReplayBout.pkg[nIndex].data[3] = 2; //设备号
	// 	m_oReplayBout.pkg[nIndex].data[4] = 0x00; //开入默认断开
	// 	m_oReplayBout.pkg[nIndex].data[5] = 0x00;
	// 	m_oReplayBout.pkg[nIndex].data[6] = 0x00;
	// 	m_oReplayBout.pkg[nIndex].length = m_oReplayBout.pkg[nIndex].data[1] + 2;
	// 	nIndex++;

	// 	m_oReplayBout.pkg[nIndex].data[0] = 0x05640564;
	// 	m_oReplayBout.pkg[nIndex].data[1] = 5;
	// 	m_oReplayBout.pkg[nIndex].data[2] = 0x01;
	// 	m_oReplayBout.pkg[nIndex].data[3] = 2; //设备号
	// 	m_oReplayBout.pkg[nIndex].data[4] = 0x07;
	// 	m_oReplayBout.pkg[nIndex].data[5] = 0x00;
	// 	m_oReplayBout.pkg[nIndex].data[6] = 8000000 / 20;
	// 	m_oReplayBout.pkg[nIndex].length = m_oReplayBout.pkg[nIndex].data[1] + 2;
	// 	nIndex++;

	// 	m_oReplayBout.cnt = nIndex;
	// }

    ioctl(m_nCommfd, 0x30A, 0);
    write(m_nCommfd, (char *)&m_oReplayBout, sizeof(DrvReplayDataBout));
}

void CSttDevicePST100s::SetTestStart(int nTestType)
{
	long nPoint = 0;
	long nFre = m_pSttPst100App->m_nFre;
	while(1)
	{
		nFre += m_pSttPst100App->m_nFre;
		if(nFre >= 250)
		{
			break;
		}

		nPoint++;
	}
	ioctl(m_nCommfd, 0x409, nPoint); //设置RTDS采样率

    m_pSttPst100App->m_oRcdDataBufferMngr.m_oRtdsSample.ResetBuffer();
    m_pSttPst100App->m_oRcdDataBufferMngr.m_o2MSample.ResetBuffer();
    ioctl(m_nCommfd, 0x402, 0); //禁止2M报文上送使能
    ioctl(m_nCommfd, 0x505, 0); //CLear 2M PlayData
    memset(&m_oPST100Para, 0, sizeof(StPST100Para));
    g_pSttSimulationBase->ConnectTo2M_BeforeTest(
        m_pSttPst100App->m_oPstDevicesMapConfig.m_pPst2mMaps, &m_oPST100Para, m_nCommfd);

    if(nTestType > 0)
    {
        //2M录波数据
        g_pSttSimulationBase->Send2MDataToDrv(m_p2MReplay, m_nCommfd);
        m_oPST100Para.n2MReplayTripCount = 1;
    }

    SetReplayBout(nTestType);
    m_oPST100Para.nTimeDelayMs = nRecordStopDelayMs;
    m_oPST100Para.n2MDelayMs = n2MTripDelayMs;
    ioctl(m_nCommfd, 0x307, 0);
    write(m_nCommfd, (char *)&m_oPST100Para, sizeof(StPST100Para));
    SendStartToDrv();
}

void CSttDevicePST100s::SetTestStop(BOOL bIsSysDefaultOutput)
{
    g_pSttSimulationBase->SetTestStarting(FALSE);
	// g_pSttSimulationBase->SetRecvStopCmd(TRUE);
    ioctl(m_nCommfd, 0x103, 0);
}

BOOL CSttDevicePST100s::OnTimer(BOOL bExec)
{
    m_nDeviceOnTimerCount++;

    if(m_nDeviceOnTimerCount * m_nOnTimerMs < m_nDeviceOnTimerMs)
    {
        return FALSE;
    }

    m_nDeviceOnTimerCount = 0;

    if(!m_bDevStaIsInit)
    {
        return FALSE;
    }

#ifdef _PSX_QT_LINUX_
    memset(&m_oSysUtc, 0, sizeof(Drv_SysUtc));
    int nSize = read(m_nCommfd, (char *)&m_oSysUtc, 0x205);

    if(nSize != sizeof(Drv_SysUtc))
    {
        return FALSE;
    }

    g_theSttDeviceStatus->m_nSync = m_oSysUtc.tmFlag;
    g_theSttDeviceStatus->m_nUtc_s = m_oSysUtc.tm_h;
    g_theSttDeviceStatus->m_nUtc_ns = m_oSysUtc.tm_l;
#endif
    return TRUE;
}

void *ProRtdsDataThread(LPVOID pParam)
{
    CLogPrint::LogString(XLOGLEVEL_INFOR, _T(">>>>>>Create ProRtdsDataThread"));

    while(1)
    {
        usleep(10);//保证100M带宽的RTDS数据及时消化

        if(bExitThread)
        {
            break;
        }

        //        if(nRecordPkgType == 1 || nRecordPkgType == 2)
        //            pRtdsSampleForThread->RingBufToRcdBuf();
    }

    pthread_exit(0);
}
