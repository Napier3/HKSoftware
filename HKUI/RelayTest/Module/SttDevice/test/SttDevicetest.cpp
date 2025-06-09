#include "SttDevicetest.h"
#include "QDir"

CSttDevicetest *CSttDevicetest::g_pSttDevicePNS330 = NULL;
long CSttDevicetest::g_nSttDeviceRef = 0;
long n4GTimeOutTickCnt = -1;
QList<float> fBatList;
float fAverBat = 0;//平均电压


CSttDevicetest::CSttDevicetest()
{
}

CSttDevicetest::~CSttDevicetest()
{
}

void CSttDevicetest::Create()
{
    g_nSttDeviceRef++;

    if(g_nSttDeviceRef == 1)
    {
        g_pSttDevicePNS330 = new CSttDevicetest;
        g_pSttDeviceBase = (CSttDeviceBase *)g_pSttDevicePNS330;
    }
}

void CSttDevicetest::Release()
{
    g_nSttDeviceRef--;

    if(g_nSttDeviceRef == 0)
    {
        delete g_pSttDevicePNS330;
        g_pSttDevicePNS330 = NULL;
    }
}

int CSttDevicetest::InitDevice(BOOL bHasAdjFile)
{
    m_nTestStopTick = -1;
    m_nBatCalcCnt = 0;
    m_nModuleDIndex = 15;//bit30数字信号
    //PNS330只有一个bit31的模拟信号和一个bit30数字信号
    g_theDeviceSystemParameter->m_nModuleCount_U = 0;
    g_theDeviceSystemParameter->m_nModuleCount_I = 0;
    g_theDeviceSystemParameter->m_nModuleCount_UI = 0;
    g_theDeviceSystemParameter->m_nModuleCount_D = 1;
    PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[0];

    if(pModule != NULL)
    {
        pModule->m_oModuleAttr.m_nModuleIndex = m_nModuleDIndex;
        pModule->m_oModuleAttr.m_nFiberPortNum_LC = 4;
    }

    g_theDeviceSystemParameter->m_nModuleCount_WEEK = 0;
    g_theDeviceSystemParameter->m_nModuleCount_FT3 = 0;
    g_theDeviceSystemParameter->m_nModuleCount_S = 0;
    g_theSystemConfig->m_oPeripheral.m_b4G = 0;
    g_theSystemConfig->m_oPeripheral.m_bBle = 1;
    g_theSystemConfig->m_oPeripheral.m_bNetRj45 = 1;
    g_theSystemConfig->m_oPeripheral.m_bNetWifi = 0;
    g_theSystemConfig->m_oPeripheral.m_nLcdTimes = 0;
    m_nCommfd = open("/dev/SttDriver_test", O_RDWR);
    m_nTouchfd = open("/dev/exc7200dev", O_RDWR);
    m_nRegCtrlDigital = 0;
    m_nRegCtrlDigital |= 1 << 0;
    ioctl(m_nCommfd, PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
    g_theSttDeviceStatus->m_b4G = 0;
    g_theSttDeviceStatus->m_bBle = 1;
    g_theSttDeviceStatus->m_bWifi = 0;
    m_nRegCtrlAnalog = 0;
    //Uart0
    SetRegisterValue(0xe0000018, 62); //4G
    SetRegisterValue(0xe0000034, 6);
    n4GTimeOutTickCnt = 0;
    //便于开机的时候获取一次电池 4G 蓝牙的状态,用于第一次进实验的图标显示
    g_nGetSystemStateTickCnt = 1;
    //主板ST口模式设置，330默认RX2是B码
    ioctl(m_nCommfd, 0x102, 0b0010); //00-BCode 01:FT3 10:PPS
    g_theDeviceSystemParameter->m_oDeviceAttrs.m_nSTModeSet = 0;
    return m_nCommfd;
}

void ResetPeripheralRtData()
{
    PSTT_MODULE_STATUS pParaV = &g_theSttDeviceStatus->m_oModule[0];
    long nValue;
    //复选效果为 有线网卡
    g_theSttDeviceStatus->m_bWifi = 0;

    if(g_theSystemConfig->m_oPeripheral.m_bNetRj45)
    {
    }
    else if(g_theSystemConfig->m_oPeripheral.m_bNetWifi)
    {
        g_theSttDeviceStatus->m_bWifi = 1;
    }

    //复选效果为 蓝牙
    nValue = (pParaV->m_nWarningVal >> 3) & 0x01;

    if(nValue)
    {
        g_theSttDeviceStatus->m_bBle = 0;
    }
    else
    {
        g_theSttDeviceStatus->m_bBle = 1;
    }

    g_theSttDeviceStatus->m_b4G = 0;

    if(g_theSystemConfig->m_oPeripheral.m_b4G)
    {
        if(g_theSystemConfig->m_oPeripheral.m_bBle)
        {
        }
        else
        {
            g_theSttDeviceStatus->m_bBle = 0;
            nValue = (pParaV->m_nWarningVal >> 1) & 0x01;

            if(nValue)
            {
                g_theSttDeviceStatus->m_b4G = 0;
            }
            else
            {
                g_theSttDeviceStatus->m_b4G = 1;
            }
        }
    }
}

void GetAverageBat()
{
    if(fBatList.count() == 0)
    {
        return;
    }

    float fBat[10];

    while(fBatList.count() > 5)
    {
        fBatList.removeFirst();
    }

    long nCount = fBatList.count();
    long nLastIdx = nCount - 1;
    float fTotal = 0;

    for(int i = 0; i < nCount; i++)
    {
        fBat[i] = fBatList.at(nLastIdx - i);
        fTotal += fBat[i];
    }

    float fRet = fTotal / nCount;
    fRet = ((int)(fRet * 100)) * 0.01;
    fAverBat = fRet;
}

BOOL CSttDevicetest::OnTimer(BOOL bExec)
{
    GetVoltCurRtData();

    if(!bExec)
    {
        m_nDeviceOnTimerCount++;

        if(m_nDeviceOnTimerCount * m_nOnTimerMs < m_nDeviceOnTimerMs)
        {
            return FALSE;
        }

        m_nDeviceOnTimerCount = 0;
    }

    stt_init_stt_device_status();
    g_theSttDeviceStatus->m_nUdc = g_fAuxVolt > 0.001 ? 1 : 0;
#ifdef _PSX_QT_LINUX_
    memset(&m_oSysUtc, 0, sizeof(Drv_SysUtc));
    int nSize = read(m_nCommfd, (char *)&m_oSysUtc, 0x205);

    if(nSize != sizeof(Drv_SysUtc))
    {
        return FALSE;
    }

    g_theSttDeviceStatus->m_nUtc_s = m_oSysUtc.tm_h; //默认B码与GPS保持一致，统一为0时区
    g_theSttDeviceStatus->m_nUtc_ns = m_oSysUtc.tm_l;
    g_theSttDeviceStatus->m_nUser_s = g_theSttDeviceStatus->m_nUtc_s
                                      + g_theSttDeviceStatus->m_nTimeZone * 3600;

    if(m_oSysUtc.tmFlag != 0)
    {
        g_theSttDeviceStatus->m_nSync = m_oSysUtc.tmFlag;
    }

    memset(&m_oSysInfo, 0, sizeof(Drv_SysInfo));
    nSize = read(m_nCommfd, (char *)&m_oSysInfo, 0x204);

    if(nSize != sizeof(Drv_SysInfo))
    {
        return FALSE;
    }

    if(g_nGetSystemStateTickCnt > 0)
    {
        m_nBatCalcCnt = 21;
        g_nGetSystemStateTickCnt--;
    }

    if(m_nBatCalcCnt > 20)
    {
        if((m_nRegCtrlDigital >> 6) & 0x01)
        {
        }
        else
        {
            m_nRegCtrlDigital |= 1 << 6; //ON/OFF_KIO
            ioctl(m_nCommfd, PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
            Sleep(50);
        }
    }

    m_nBatCalcCnt++;
//    AnalysisDrvSysInfo(m_oSysInfo.stBack[1], 0, STT_MODULE_TYPE_VOLT);
//    AnalysisDrvSysInfo(m_oSysInfo.stBack[0], 1, STT_MODULE_TYPE_CURRENT);
#endif
    QDir oDir_0("/mnt/Stt/Usb/sda");
    QDir oDir_1("/mnt/Stt/Usb/sda1");

    if(oDir_0.exists() || oDir_1.exists())
    {
        g_theSttDeviceStatus->m_bUSB = 1;
    }
    else
    {
        g_theSttDeviceStatus->m_bUSB = 0;
    }

    int nValue = g_theSttDeviceStatus->m_oModule[0].m_nWarningVal & 0x01;

    if(nValue)
    {
        g_theSttDeviceStatus->m_bPowerAC = 0;
    }
    else
    {
        g_theSttDeviceStatus->m_bPowerAC = 1;
    }

    if((m_nRegCtrlDigital >> 6) & 0x01)
    {
        if(fAverBat > 10)
        {
            float fBat = fAverBat;
            fBat = fBat * 0.994;

            if(fBat > 12.5)
            {
                fBat = 12.5;
            }

            int nBatCap;

            if(fBat < 10.47)
            {
                //8
                //                nBatCap = 8.0*fBat/(10.47 - 10.26) - 390.8;
                if(fBat > 10.38)
                {
                    nBatCap = 5;
                }
                else
                {
                    nBatCap = 0;
                }
            }
            else if(fBat < 10.60)
            {
                //16
                //                nBatCap = 8.0*fBat/(10.60 - 10.47) - 636.0;
                if(fBat > 10.57)
                {
                    nBatCap = 15;
                }
                else
                {
                    nBatCap = 10;
                }
            }
            else if(fBat < 10.67)
            {
                //24
                //                nBatCap = 8.0*fBat/(10.67 - 10.60) - 1195.4;
                if(fBat > 10.63)
                {
                    nBatCap = 25;
                }
                else
                {
                    nBatCap = 20;
                }
            }
            else if(fBat < 10.73)
            {
                //32
                //                nBatCap = 8.0*fBat/(10.73 - 10.67) - 1398.6;
                if(fBat > 10.70)
                {
                    nBatCap = 30;
                }
                else
                {
                    nBatCap = 28;
                }
            }
            else if(fBat < 10.80)
            {
                //40
                //                nBatCap = 8.0*fBat/(10.80 - 10.73) - 1194.2;
                if(fBat > 10.77)
                {
                    nBatCap = 35;
                }
                else
                {
                    nBatCap = 32;
                }
            }
            else if(fBat < 10.88)
            {
                //48
                //                nBatCap = 8.0*fBat/(10.88 - 10.80) - 1040.0;
                if(fBat > 10.84)
                {
                    nBatCap = 40;
                }
                else
                {
                    nBatCap = 38;
                }
            }
            else if(fBat < 11.0)
            {
                //56
                //                nBatCap = 8.0*fBat/(11.0 - 10.88) - 677.3;
                if(fBat > 10.98)
                {
                    nBatCap = 50;
                }
                else
                {
                    nBatCap = 45;
                }
            }
            else if(fBat < 11.2)
            {
                //64
                //                nBatCap = 8.0*fBat/(11.2 - 11.0) - 384;
                if(fBat > 11.10)
                {
                    nBatCap = 60;
                }
                else
                {
                    nBatCap = 55;
                }
            }
            else if(fBat < 11.4)
            {
                //72
                //                nBatCap = 8.0*fBat/(11.4 - 11.2) - 384;
                if(fBat > 11.30)
                {
                    nBatCap = 70;
                }
                else
                {
                    nBatCap = 65;
                }
            }
            else if(fBat < 11.95)
            {
                //80
                //                nBatCap = 8.0*fBat/(11.95 - 11.4) - 93.8;
                if(fBat > 11.70)
                {
                    nBatCap = 80;
                }
                else
                {
                    nBatCap = 75;
                }
            }
            else if(fBat < 12.15)
            {
                //88
                //                nBatCap = 8.0*fBat/(12.15 - 11.95) - 398;
                if(fBat > 12.05)
                {
                    nBatCap = 90;
                }
                else
                {
                    nBatCap = 85;
                }
            }
            else
            {
                //100
                //                nBatCap = 8.0*fBat/(12.5 - 12.15) - 185.7;
                if(fBat > 12.37)
                {
                    nBatCap = 100;
                }
                else
                {
                    nBatCap = 95;
                }
            }

            g_theSttDeviceStatus->m_nBatCap = nBatCap;
        }
        else
        {
            g_theSttDeviceStatus->m_nBatCap = 0;
        }
    }

    BOOL bSetRegCtrlDigital = FALSE;

    if(m_nBatCalcCnt > 26)
    {
        if((m_nRegCtrlDigital >> 6) & 0x01)
        {
            m_nRegCtrlDigital &= ~(1 << 6); //ON/OFF_KIO
            bSetRegCtrlDigital = TRUE;
            m_nBatCalcCnt = 0;
        }
    }

    if(bSetRegCtrlDigital)
    {
        ioctl(m_nCommfd, PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
    }

    ResetPeripheralRtData();
    return TRUE;
}

float BatTemp_trans(float fVdc)
{
    //V(mv)=1324.0 - 8.194(T-30) - 0.00262(T-30)^2
    //262T^2 + 803680T +V*10^5 - 156746200 = 0
    float a, b, c, s, x1, x2;
    a = 262;
    b = 803680;
    c = fVdc * 100000 - 156746200;
    s = b * b - 4 * a * c;
    x1 = 0;
    x2 = 0;

    if(s < 0)
    {
        return 0;
    }
    else if(s == 0)
    {
        x1 = -b / (2 * a);
        x2 = x1;
    }
    else
    {
        x1 = (-b + sqrt(s)) / (2 * a);
        x2 = (-b - sqrt(s)) / (2 * a);
    }

    if(x1 > -5 && x1 < 60)
    {
        return x1;
    }
    else if(x2 > -5 && x2 < 60)
    {
        return x2;
    }
    else
    {
        return 0;
    }
}

void CSttDevicetest::SetIEC61850Para()
{
    CIecCfgDatasMngr *poIecCfgDatasMngr = &m_oCIEC61850CfgMngr.m_oIecCfgDatasMngr;
    CIECGooseMngr *pGooseMngr = &m_oCIEC61850CfgMngr.m_oGooseMngr;
    pGooseMngr->Init();
    int nGseCnt = poIecCfgDatasMngr->GetGOUTCount();

    if(poIecCfgDatasMngr->GetGoutMngr()->m_nDatasUse == 0)
    {
        nGseCnt = 0;
    }

    for(int index = 0; index < nGseCnt; index++)
    {
        CIecCfgGooseDataBase *pGoose = (CIecCfgGooseDataBase *)poIecCfgDatasMngr->GetGoutCfgData(index);
        pGooseMngr->CreateGooseTmtStruct(pGoose);
    }

    GooseCfg oGooseCfg;
    oGooseCfg.T0 = pGooseMngr->m_nT[0] * 50000;
    oGooseCfg.T1 = pGooseMngr->m_nT[1] * 50000;
    oGooseCfg.T2 = pGooseMngr->m_nT[2] * 50000;
    oGooseCfg.T3 = pGooseMngr->m_nT[3] * 50000;
    ioctl(m_nCommfd, 0x301, 0);//GOOSE发送配置
    write(m_nCommfd, (char *)&oGooseCfg, sizeof(GooseCfg));
    CIecCfgSysParas *pSysParasMngr = poIecCfgDatasMngr->GetSysParasMngr();

    if(pSysParasMngr != NULL)
    {
        CIecCfgFiberParas *pFiberParas = pSysParasMngr->GetFiberParas();

        if(pFiberParas != NULL)
        {
            CString strID;
            CIecCfgFiberPara *pFiberPara;
            int nLCFiberPort = 0xff; //默认全百兆

            for(int nIndex = 0; nIndex < MAX_SV_FiberPort_NUM; nIndex++)
            {
                strID.Format(_T("LC%d"), nIndex + 1);
                pFiberPara = (CIecCfgFiberPara *)pFiberParas->FindByID(strID);

                if(pFiberPara != NULL)
                {
                    if(pFiberPara->m_ntype == _IECCFG_SYSPARAS_LC_PORT_TYPE_1000M_)
                    {
                        nLCFiberPort &= ~(1 << nIndex);
                    }
                }
            }

            g_theSystemConfig->m_nFiberType = nLCFiberPort;
            ioctl(m_nCommfd, 0x122, g_theSystemConfig->m_nFiberType);
        }
    }

    memset(&m_oGooseItems, 0, sizeof(GooseItems));
    QByteArray ba;
    int GsIndex = 0;

    for(int index = 0; index < pGooseMngr->data_gseout.count(); index++)
    {
        ba.clear();
        tmt_goose &m_tmt_goose = pGooseMngr->data_gseout[index];
        CString t_AppID = m_tmt_goose.m_AppID;
        t_AppID = Get0String(4 - t_AppID.length()) + t_AppID;

        if((m_tmt_goose.port < 0) || (m_tmt_goose.port > 3))
        {
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("GOOSE AppId=0x%s 光口配置超过硬件光口总数,配置无效"), t_AppID.GetString());
            continue;
        }

        pGooseMngr->CreateGooseByteArray(ba, m_tmt_goose);

        if(ba.size() > 500)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("GOOSE AppId=0x%s 报文总长度超过500字节,配置无效"), t_AppID.GetString());
            continue;
        }

        if(GsIndex == 50)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("GOOSE数量已达上限%d,AppId=0x%s被忽略"), 50, t_AppID.GetString());
            break;
        }

        m_oGooseItems.gs[GsIndex].datCnt = ba.size();
        memcpy(m_oGooseItems.gs[GsIndex].dat, ba.constData(), ba.size());
        m_oGooseItems.gs[GsIndex].valid = 1;
        m_oGooseItems.gs[GsIndex].index = index;
        GsIndex++;

        for(int nChan = 0; nChan < m_tmt_goose.m_ChanNum; nChan++)
        {
            QString strDevCh = m_tmt_goose.vChanelInfo.at(nChan).strDevCh;
            QList<QString> oDevChList = strDevCh.split(";");

            if(oDevChList.count() == 2)
            {
                int nStart = oDevChList.at(0).toInt();
                int nEnd = oDevChList.at(1).toInt();
            }
        }
    }

    ioctl(m_nCommfd, 0x302, 0);//GOOSE
    write(m_nCommfd, (char *)&m_oGooseItems, sizeof(GooseItems));

    for(int index = 0; index < pGooseMngr->data_gseout.count(); index++)
    {
        tmt_goose otmt_goose = pGooseMngr->data_gseout.at(index);

        for(int chanid = 0; chanid < otmt_goose.vChanelInfo.size(); chanid++)
        {
            if(chanid < 20)
            {
                ChanelInfo oChanelInfo = otmt_goose.vChanelInfo.at(chanid);
                m_oPreGoosePub[index].m_strChannel[chanid] = oChanelInfo.firstvalue;
            }
        }
    }
}
