#include "SttDevicePST200s.h"
#include "../../../../Module/API/GlobalConfigApi.h"


CSttDevicePST200s *CSttDevicePST200s::g_pSttDevicePST200s = NULL;
long CSttDevicePST200s::g_nSttDeviceRef = 0;

char pOnePointBuf[4];
BOOL bDownloadRTDS = FALSE;
BOOL bTestStarted = FALSE;
char pszBinBuf[12];
long nTimeZone = 8;

CSttDevicePST200s::CSttDevicePST200s()
{

}

CSttDevicePST200s::~CSttDevicePST200s()
{
    delete m_pSttPst200App;
    delete m_pDrvResults;
    delete m_pRtdsMapsMngr;
}

void CSttDevicePST200s::Create()
{
    g_nSttDeviceRef++;

    if (g_nSttDeviceRef == 1)
    {
        g_pSttDevicePST200s=new CSttDevicePST200s;
        g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePST200s;
    }
}

void CSttDevicePST200s::Release()
{
    g_nSttDeviceRef--;

    if (g_nSttDeviceRef == 0)
    {
        delete g_pSttDevicePST200s;
        g_pSttDevicePST200s = NULL;
    }
}

int CSttDevicePST200s::InitDevice(BOOL bHasAdjFile)
{
    //ignor SIGPIPE (send error after socket disconnect)
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGPIPE);
    sigprocmask(SIG_BLOCK,&set,NULL);

    m_pDrvResults = new unsigned char[1024*1024];

    m_oCIEC61850CfgMngr.InitDigitalModulesInfo();
    m_pSttPst200App = new CSttPst200App();
    m_pSttPst200App->InitSttPstApp(FALSE);
    g_pTheOwnIotDevice->SetSN(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strSN);
    g_pTheOwnIotDevice->SetModel(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strDeviceName);
    m_pSttPst200App->Connect();

    m_nCommfd=open("/dev/SttDriver_PST200s",O_RDWR);
    m_pRtdsReplayData = m_pSttPst200App->m_oRcdDataBufferMngr.FindRcdDataBuffer(RcdDataID_RTDS_OUT);

    stt_init_stt_device_status();
    m_bDevStaIsInit = TRUE;

    m_pRtdsMapsMngr = &((CSttSimulationPST200*)g_pSttSimulationBase)->m_oHdChRcdDataMapsMngr;
    m_pBinSampleData = &m_pSttPst200App->m_oRcdDataBufferMngr.m_oBinSample;
    m_p2MReplay = &m_pSttPst200App->m_oRcdDataBufferMngr.m_o2MPlay;
    g_p2MSample = &m_pSttPst200App->m_oRcdDataBufferMngr.m_o2MSample;
    m_pOutputMap = &m_pSttPst200App->m_oOutputMap;
    g_pSttSimulationBase->SetRtdsFiberOutputMap(m_pOutputMap);
    InitReplayModule();
    ioctl(m_nCommfd,0xA00,1);
    ioctl(m_nCommfd,0x103,0);
    ioctl(m_nCommfd,0x402,0);//禁止2M报文上送使能

    CalPower();
    return m_nCommfd;
}

void CSttDevicePST200s::SetTestPara(int nTestType, char *pszBuff)
{
    switch(nTestType)
    {
    case IECDataCfg:
    {
        ioctl(m_nCommfd,  0x320, 0);
        write(m_nCommfd, pszBuff,sizeof(Drv_IECConfig));
    }
        break;
    case SvCtrlCfg:
    {
        ioctl(m_nCommfd, 0x321, 1);//1：SMV发送配置
        write(m_nCommfd, pszBuff,sizeof(SendConfSV));
    }
        break;
    case GseCtrlCfg:
    {
        ioctl(m_nCommfd, 0x321, 2);//2：GOOSE发送配置3：FT3发送配置
        write(m_nCommfd, pszBuff,sizeof(SendConfGSE));
    }
        break;
    case Ft3CtrlCfg:
    {
        ioctl(m_nCommfd, 0x321, 3);//3：FT3发送配置
        write(m_nCommfd, pszBuff,sizeof(SendConfFT3));
    }
        break;
    case FiberCtrlCfg:
    {
        ioctl(m_nCommfd, 0x321, 0);//flag = 0:光口配置
        write(m_nCommfd, pszBuff,sizeof(FiberConf));
    }
        break;
    }
}

void CSttDevicePST200s::InitReplayModule()
{
    memset(&m_oModuleDef,0,sizeof(DrvModuleDef));
    DrvPIA48SZero oPIA48SZero;//下载小信号PIA48S的零漂补偿
    memset(&oPIA48SZero,0,sizeof(DrvPIA48SZero));

    if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
    {
        m_oModuleDef.nDModulePos = g_theDeviceSystemParameter->m_oModules_D[0]->m_oModuleAttr.m_nModuleIndex - 1;

        QMap<QString,int> oChanMap;
        oChanMap.clear();
        oChanMap.insert("Ud1_1",1);
        oChanMap.insert("Ud1_2",2);
        oChanMap.insert("Ud1_3",3);
        oChanMap.insert("Ud1_4",5);
        oChanMap.insert("Ud1_5",6);
        oChanMap.insert("Ud1_6",7);
        oChanMap.insert("Ud1_7",9);
        oChanMap.insert("Ud1_8",10);
        oChanMap.insert("Ud1_9",11);
        oChanMap.insert("Ud1_10",13);
        oChanMap.insert("Ud1_11",14);
        oChanMap.insert("Ud1_12",15);

        oChanMap.insert("Id1_1",17);
        oChanMap.insert("Id1_2",18);
        oChanMap.insert("Id1_3",19);
        oChanMap.insert("Id1_4",21);
        oChanMap.insert("Id1_5",22);
        oChanMap.insert("Id1_6",23);
        oChanMap.insert("Id1_7",25);
        oChanMap.insert("Id1_8",26);
        oChanMap.insert("Id1_9",27);
        oChanMap.insert("Id1_10",29);
        oChanMap.insert("Id1_11",30);
        oChanMap.insert("Id1_12",31);

        m_oCIEC61850CfgMngr.m_o92Mngr.SetChanelMap(oChanMap);//数字量Comtrade只支持24路回放
    }
    if(g_theDeviceSystemParameter->m_nModuleCount_S > 0)
    {
        m_oModuleDef.nSModulePos = g_theDeviceSystemParameter->m_oModules_S[0]->m_oModuleAttr.m_nModuleIndex - 1;
    }
    if(g_theDeviceSystemParameter->m_nModuleCount_WEEK > 0)
    {
        m_oModuleDef.nWModulePos = g_theDeviceSystemParameter->m_oModules_WEEK[0]->m_oModuleAttr.m_nModuleIndex - 1;
        oPIA48SZero.nModule = m_oModuleDef.nWModulePos;
        PSTT_MODULE pMODULE = g_theDeviceSystemParameter->m_oModules_WEEK[0];
        float fZero;
        for(int i = 0; i < pMODULE->m_oModuleAttr.m_nChannelNum;i++)
        {
            fZero = pMODULE->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[i].m_fDcZero[0];
            oPIA48SZero.nZero[i] = fZero/10.0*0x7fffffff;
        }
    }
    if(g_theDeviceSystemParameter->m_nModuleCount_Stable2M > 0)
    {
        m_oModuleDef.n2MModulePos = g_theDeviceSystemParameter->m_oModules_Stable2M[0]->m_oModuleAttr.m_nModuleIndex - 1;
    }

    ioctl(m_nCommfd,0x405,0);
    write(m_nCommfd,&oPIA48SZero,sizeof(DrvPIA48SZero));

    ioctl(m_nCommfd,0x404,0);
    write(m_nCommfd,&m_oModuleDef,sizeof(DrvModuleDef));
}

BOOL CSttDevicePST200s::OnTimer(BOOL bExec)
{
    m_nDeviceOnTimerCount++;
    if(m_nDeviceOnTimerCount*m_nOnTimerMs < m_nDeviceOnTimerMs)
    {
        return FALSE;
    }
    m_nDeviceOnTimerCount=0;

    if(!m_bDevStaIsInit)
        return FALSE;

#ifdef _PSX_QT_LINUX_
    memset(&m_oSysUtc,0,sizeof(Drv_SysUtc));
    int nSize = read(m_nCommfd,(char*)&m_oSysUtc,0x205);
    if(nSize != sizeof(Drv_SysUtc))
    {
        return FALSE;
    }

    g_theSttDeviceStatus->m_nSync = m_oSysUtc.tmFlag;
    g_theSttDeviceStatus->m_nUtc_s = m_oSysUtc.tm_h;
    g_theSttDeviceStatus->m_nUtc_ns = m_oSysUtc.tm_l;
    g_theSttDeviceStatus->m_nUser_s = g_theSttDeviceStatus->m_nUtc_s + nTimeZone*60*60;
#endif

	// short nYear, nMon, nDay, nHour, nMin, nSec;
	// CString strDate;
	// TransTimer_t(g_theSttDeviceStatus->m_nUser_s, nYear, nMon, nDay, nHour, nMin, nSec);
	// strDate.Format("%04d-%02d-%02d %02d:%02d:%02d", nYear, nMon, nDay, nHour, nMin, nSec);
	// qDebug()<< strDate;

    return TRUE;
}

Drv_SysUtc oSysUtc;
void CSttDevicePST200s::Load_RcdData()
{
    memset(&oSysUtc,0,sizeof(Drv_SysUtc));
    int nSize = read(CSttDeviceBase::g_pSttDeviceBase->GetDriverFd(),(char*)&oSysUtc,0x205);
    if(nSize == sizeof(Drv_SysUtc))
    {
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Finish %d,%d"),oSysUtc.tm_h,oSysUtc.tm_l);
    }

//#ifdef _PSX_QT_LINUX_
//        CDataGroup oDataGroup;
//        oDataGroup.AddNewData("Time",g_theSttDeviceStatus->m_nUtc_s);
//        CSttMqttTopicCmbn oTopicCmbn;
//        stt_mqtt_InitTopicCmbn(oTopicCmbn,SYS_STATE_RETTYPE_EVENT, "RecordRecvEnd");
//        stt_mqtt_GetParasBuffer(&oDataGroup, oTopicCmbn);
//        m_pSttPst200App->m_pMqttEngine->PublicTopic(oTopicCmbn);
//#endif

    qDebug()<<"Load_RcdData Started";
    //    g_pSttSimulationBase->GetRTDSDataDebug(m_pRtdsReplayData);
    ioctl(m_nCommfd,0x402,0);//禁止2M报文上送使能
    ioctl(m_nCommfd,0x505,0);//CLear 2M PlayData

    bDownloadRTDS = FALSE;
    bTestStarted = FALSE;
    g_pSttSimulationBase->ResetThreadPara();
    m_nRtdsChLength = m_pOutputMap->GetCount()*4;//单位：字节

    g_pSttSimulationBase->Send2MDataToDrv(m_p2MReplay,m_nCommfd);//下载2M报文到硬件
    SendConfToDevice();//下载小信号和开关量模块的回放配置

    bDownloadRTDS = TRUE;
    if(!m_pRtdsReplayData->CanRead(1))
    {
        //回放数据全部下载完毕，开始等待GPS触发实验
        CDataGroup oDataGroup;
        m_pSttPst200App->EventRcdDataLoadFinished(&oDataGroup);
        return;
    }

    //开始下载第一批回放数据
    m_nCurModule = 0;
    m_nPkgIndex = 0;

    switch(g_pSttSimulationBase->m_nOutputType)
    {
    case OutputType_WeekSwitch:
    {
        m_nCurModule = 1;
        SendDataToDevice_Week();
    }
        break;
    case OutputType_SmvGoose:
    {
        SendDataToDevice_Digital();
    }
        break;
    case OutputType_Ft3:
    {

    }
        break;
    }
}

void CSttDevicePST200s::SetTestStart(int nStateIdx)
{
	m_pBinSampleData->ResetBuffer();
	long biValue_32 = 0;
	long nSec = 0;
	long nNSec = 0;
	memcpy(pszBinBuf,&nSec,4);
	memcpy(pszBinBuf+4,&nNSec,4);
	memcpy(pszBinBuf+8,&biValue_32,4);
	m_pBinSampleData->m_oRcdDataBuffer.AddBuffer(pszBinBuf,12);

    DrvReplayTrip oReplayTrip;
    //下载实验触发方式
	oReplayTrip.gpsSec = 0;
    oReplayTrip.usegps = m_pSttPst200App->m_oGPSPara.nUseGpsTrig;
	if(oReplayTrip.usegps)
	{
		GPSPara &oGPSPara = m_pSttPst200App->m_oGPSPara;
		short nYear, nMon, nDay, nHour, nMin, nSec;
		TransTimer_t(g_theSttDeviceStatus->m_nUser_s, nYear, nMon, nDay, nHour, nMin, nSec);
		nHour = oGPSPara.nGpsTime_Hour;
		nMin = oGPSPara.nGpsTime_Minute;
		nSec = oGPSPara.nGpsTime_Second;
		TransTimer_To_t(oReplayTrip.gpsSec, nYear, nMon, nDay, nHour, nMin, nSec);
		oReplayTrip.gpsSec -= nTimeZone*60*60;

		CString strDate;
		strDate.Format("%04d-%02d-%02d %02d:%02d:%02d", nYear, nMon, nDay, nHour, nMin, nSec);
		qDebug()<< strDate;
	}
    oReplayTrip.gpsnSec = 0;
    ioctl(m_nCommfd,0x308,2);
    write(m_nCommfd,(char*)&oReplayTrip,sizeof(DrvReplayTrip));
    //开始实验
    ioctl(m_nCommfd,0x103,6);
    bTestStarted = TRUE;
    //回放数据全部下载完毕，开始等待GPS触发实验
    CDataGroup oDataGroup;
    m_pSttPst200App->EventTestStarted(&oDataGroup);
}

void CSttDevicePST200s::SetTestStop(BOOL bIsSysDefaultOutput)
{
    g_pSttSimulationBase->SetTestStarting(FALSE);
	// g_pSttSimulationBase->SetRecvStopCmd(TRUE);20231227
    ioctl(m_nCommfd,0x103,0);
}

void dsp_fft(float* pindata, int lindata, float* poutdataR, float* poutdataI, float* phase_r, float *phase_i, int* pinv)
{
    int	is,N=lindata,v;
    float *xn=pindata, *XWR=poutdataR, *XWI=poutdataI;
    float	tmpXWR,tmpXWI;
    int		leni1,leni2,xui0,xui1,pxu,is1,is2;
    v = int(log(N) / log(2.0) + 0.5);

    for(is = 0; is < N;  is++)
    {
        XWR[is] = xn[pinv[is]];
        XWI[is] = 0.0;
    }

    tmpXWR=0.0;
    tmpXWI=0.0;
    xui0=0;
    xui1=0;
    for(is = 1; is <= v;  is++)
    {
        leni1 = (int) 1 << (v - is);
        for(is1 = 1; is1 <= leni1; is1++)
        {
            leni2 = (int) 1 << (is - 1);
            for(is2 = 1; is2 <= leni2;  is2++)
            {
                xui0  = (is1 - 1) * (leni2 << 1) + is2 - 1;
                xui1 = xui0 + leni2;
                pxu = (is2 - 1) << (v - is);
                tmpXWR = XWR[xui1];
                tmpXWI = XWI[xui1];
                XWR[xui1] = tmpXWR * phase_r[pxu] - tmpXWI * phase_i[pxu];
                XWI[xui1] = tmpXWR * phase_i[pxu] + tmpXWI * phase_r[pxu];
                tmpXWR = XWR[xui0];
                tmpXWI = XWI[xui0];
                XWR[xui0] = tmpXWR + XWR[xui1];
                XWI[xui0] = tmpXWI + XWI[xui1];
                XWR[xui1] = tmpXWR - XWR[xui1];
                XWI[xui1] = tmpXWI - XWI[xui1];
            }
        }
    }
}

int xbanalysis(float *rz_fzh,float *rz_xxw,float *rz_plv,float *data, float Fre,int m_DataLength,int m_FFTCount)
{

    int	is, v, it, tmp, N = m_DataLength, *pinv, index = 0, *r_ind;
    float	*phase_r, *phase_i, *XWR, *XWI, *xn;
    float	*r_pha, *r_frq, *r_amp, *winfun;
    xn=data;
    r_pha=rz_xxw;
    r_frq=rz_plv;
    r_amp=rz_fzh;
    int nSizeFloat = sizeof(float);
    int nSizeInt = sizeof(int);

    v= int(log(N)/log(2.0)+0.5);
    r_ind=(int *)malloc(100*nSizeInt);
    pinv=(int *)malloc(N*nSizeInt);
    phase_r=(float *)malloc(N*nSizeFloat);
    phase_i=(float *)malloc(N*nSizeFloat);
    XWR=(float *)malloc(N*nSizeFloat);
    XWI=(float *)malloc(N*nSizeFloat);
    winfun=(float *)malloc(N*nSizeFloat);

    memset(r_ind,0,100*nSizeInt);
    memset(pinv,0,N*nSizeInt);

    memset(phase_r,0,N*nSizeFloat);
    memset(winfun,0,N*nSizeFloat);
    memset(phase_i,0,N*nSizeFloat);
    memset(XWR,0,N*nSizeFloat);
    memset(XWI,0,N*nSizeFloat);

    int N2 = N/2;
    float ftmpVal = 2.0 * 3.1415926 / N;
    for(is =0; is <N;  is++)
    {
        winfun[is] = 0.5 - 0.5 * cos(ftmpVal * is);
    }

    //DSP analysis
    pinv[0] = 0;
    pinv[1] = 1;
    for(is = 1; is  < v;  is++)
    {
        tmp = (int)1 << is;
        for(it = 0; it  < tmp;  it++)
        {
            pinv[it] = 2 * pinv[it];
            pinv[it+tmp] = pinv[it] + 1;
        }
    }

    for(is = 0; is < N;  is++)
    {
        phase_r[is] = (float)cos(-ftmpVal*is);
        phase_i[is] = (float)sin(-ftmpVal*is);

        xn[is] = winfun[is] * xn[is];
    }

    dsp_fft(xn, N, XWR, XWI, phase_r, phase_i, pinv);

    // 取800个点包括上面的相位；
    int is1, idtmp=0, width=4;
    float vmax=0.0, vm=0.0, vtmp=0.0;
    *(r_pha+index)=0.0;
    *(r_frq+index)=0.0;
    *(r_amp+index)=*(XWR+index)/N*2;
    index++;

    for(is=width; is<=N2; )
    {
        if(index >= m_FFTCount)
            break; //goto xend;
        vm=0.0;
        for(is1=0; is1<width*2; is1++)
        {
            // 取800个点包括上面的相位；XWR【】，XWI【】；
            vtmp = (float)sqrt(XWR[is + is1] * XWR[is+is1] + XWI[is+is1] * XWI[is+is1]);
            if(vm < vtmp)
            {
                vm=vtmp;
                idtmp=is+is1;
            }
        }
        if(vm>10*N/4.0)
        {
            vmax=0.0;
            for(is1=-width; is1<width; is1++)
            {
                vtmp=(float)sqrt(XWR[idtmp+is1]*XWR[idtmp+is1]+XWI[idtmp+is1]*XWI[idtmp+is1]);
                if(vmax<vtmp)
                    vmax=vtmp;
            }
            if(fabs(vmax-vm)<1e-4)
            {
                *(r_pha+index)=(float)atan2(XWI[idtmp],XWR[idtmp]);
                *(r_ind+index)=idtmp;
                *(r_amp+index)=vmax;
                index++;
            }
        }
        is=is+width*2;
    }

xend:
    float xsh=0.0, qv, hv, dfrq;
    for(is=1; is<index; is++)
    {
        idtmp=r_ind[is]-1;
        qv=(float)sqrt(XWR[idtmp]*XWR[idtmp]+XWI[idtmp]*XWI[idtmp]);
        idtmp=r_ind[is]+1;
        hv=(float)sqrt(XWR[idtmp]*XWR[idtmp]+XWI[idtmp]*XWI[idtmp]);
        if(qv>=hv)
        {
            xsh=qv/r_amp[is];
            dfrq=(float)((2.0*xsh-1.0)/(1.0+xsh));
        }
        else
        {
            xsh=hv/r_amp[is];
            dfrq=(float)((1.0-2.0*xsh)/(1.0+xsh));
        }
        qv=dfrq*dfrq;
        hv=qv*qv;
        xsh=hv*qv;
        qv=hv*hv;
        idtmp=r_ind[is];
        *(r_frq+is)=(float)((idtmp-dfrq)*Fre/N);
        *(r_amp+is)=(float)(*(r_amp+is)/(1.0-0.644934066848226*dfrq*dfrq+0.16680835843527*hv)/N*4);
        *(r_pha+is)=(float)((*(r_pha+is)/3.1415926+dfrq)*180.0);
    }
    free(r_ind);
    free(pinv);
    free(phase_r);
    free(phase_i);
    free(XWR);
    free(XWI);
    free(winfun);
    return index-1;
}

int FFTComputer(QVector<long double> &rz_fzh, QVector<long double> & rz_xxw\
                                   , QVector<long double> & rz_plv,QVector< double> &m_data\
                                   , long double Fre,int m_Total,int m_FXCount)
{
    float fzh[26]={0}, xxw[26]={0}, plv[26]={0};
    float data[1024];
    memset(data,0,sizeof(float)*1024);
    for(int i=0;i<m_Total;i++)
    {
        data[i]=m_data[i];
    }
    int t_R = xbanalysis(fzh, xxw, plv, data, Fre,m_Total,m_FXCount);
    rz_fzh.clear();
    rz_plv.clear();
    rz_xxw.clear();
    for (int j=0;j<m_FXCount;j++)
    {
        rz_fzh.push_back(fzh[j]);
        rz_plv.push_back(plv[j]);
        rz_xxw.push_back(xxw[j]);
    }

    return t_R;
}

void CSttDevicePST200s::CalPower()
{
    return;
    ConverStruct oTrans;
    m_nRtdsChLength = 24*4;
    long nRtdsChCount = 24;
    QFile file("/mnt/Stt/Bin/WaveData");
    char pDestBuf[4096];
    if(file.open(QIODevice::ReadOnly))
    {
        long nDataLen = file.read(pDestBuf,m_nRtdsChLength);
        while(nDataLen > 0)
        {
            if((m_pRtdsReplayData->m_nDataLength + nDataLen) < g_oPstRcdDataBufferLen.nRtdsBufLen)
            {
                m_pRtdsReplayData->AddBuffer(pDestBuf,nDataLen);
                nDataLen = file.read(pDestBuf,m_nRtdsChLength);
                if(nDataLen != m_nRtdsChLength)
                    break;
            }
        }

        file.flush();
        file.close();
    }

    long nBeginIdx = 9500/200;//计算起始点,至少256点,折算3个周波

    QVector<double> m_NeedData;
    while(TRUE)
    {
        if((m_pRtdsReplayData->m_nDataLength - m_nPkgIndex*m_nRtdsChLength) >= m_nRtdsChLength)
        {
            char* pszBuf = m_pRtdsReplayData->m_pBuffer + m_nPkgIndex*m_nRtdsChLength;

            for(int i = 0; i < nRtdsChCount;i++)
            {
                for(int j = 0;j < 4;j++)
                {
                    oTrans.b[3-j] = *(pszBuf + i*4 + j);
                }

                m_NeedData.append(oTrans.f);
                break;
            }
            m_nPkgIndex++;

            if(m_nPkgIndex > 512)
                break;
        }
        else
            break;
    }

    if(m_NeedData.size() < 512)
        return;

    QVector<long double> m_rzfzh,m_rzxxw,m_rzplv;
    FFTComputer(m_rzfzh, m_rzxxw, m_rzplv,m_NeedData,5000,400,2);
    qDebug() << (float)m_rzfzh[1];
    qDebug() << (float)m_rzxxw[1];
    qDebug() << (float)m_rzplv[1];
}

void CSttDevicePST200s::CalPower(CSttParas *pParas)
{
    CDvmData *pData1 = pParas->AddNewData("","LN1","");
    CDvmValue *pValueA = pData1->AddValue("A","");
    CDvmValue *pValueA_U = pValueA->AddValue("U","");
    pValueA_U->AddValue("mag","50");
    pValueA_U->AddValue("ang","0");
    CDvmValue *pValueA_I = pValueA->AddValue("I","");
    pValueA_I->AddValue("mag","1");
    pValueA_I->AddValue("ang","0");
    CDvmValue *pValueA_P = pValueA->AddValue("P","");
    pValueA_P->m_strValue = "100";
    CDvmValue *pValueA_Q = pValueA->AddValue("Q","");
    pValueA_Q->m_strValue = "0";
    CDvmValue *pValueB = pData1->AddValue("B","");
    CDvmValue *pValueB_U = pValueB->AddValue("U","");
    pValueB_U->AddValue("mag","60");
    pValueB_U->AddValue("ang","0");
    CDvmValue *pValueB_I = pValueB->AddValue("I","");
    pValueB_I->AddValue("mag","2");
    pValueB_I->AddValue("ang","0");
    CDvmValue *pValueB_P = pValueB->AddValue("P","");
    pValueB_P->m_strValue = "110";
    CDvmValue *pValueB_Q = pValueB->AddValue("Q","");
    pValueB_Q->m_strValue = "1";
    CDvmValue *pValueC = pData1->AddValue("C","");
    CDvmValue *pValueC_U = pValueC->AddValue("U","");
    pValueC_U->AddValue("mag","70");
    pValueC_U->AddValue("ang","0");
    CDvmValue *pValueC_I = pValueC->AddValue("I","");
    pValueC_I->AddValue("mag","3");
    pValueC_I->AddValue("ang","0");
    CDvmValue *pValueC_P = pValueC->AddValue("P","");
    pValueC_P->m_strValue = "120";
    CDvmValue *pValueC_Q = pValueC->AddValue("Q","");
    pValueC_Q->m_strValue = "2";

    CDvmValue *pValueS = pData1->AddValue("S","");
    CDvmValue *pValueS_P = pValueS->AddValue("3P","");
    pValueS_P->m_strValue = "111";
    CDvmValue *pValueS_Q = pValueS->AddValue("3Q","");
    pValueS_Q->m_strValue = "22";
}

void CSttDevicePST200s::EventProcessEx()
{
    if(!bDownloadRTDS)
        return;

    long nRet = ioctl(m_nCommfd, 0x501, 0);
    if(nRet == 1)
    {
        //继续下载后续回放数据
        if(m_nCurModule == 0)
        {
            SendDataToDevice_Digital();
        }
        else if(m_nCurModule == 1)
        {
            SendDataToDevice_Week();
        }
        else if(m_nCurModule == 2)
        {
            SendDataToDevice_Switch();
        }
    }
    else if(nRet == 2)
    {
        //实验结束中断
        ioctl(m_nCommfd,0x103,0);

		//读取开入量变位
		int nRet2 = read(m_nCommfd,m_pDrvResults,0x262);
		if(nRet2 > 0)
		{
			long nDrvResItemLen = sizeof(DrvResultItem);
			for(int i=0;i<nRet2/nDrvResItemLen;i++)
			{
				memcpy(&m_oResultItem,m_pDrvResults+i*nDrvResItemLen,nDrvResItemLen);
				if(m_oResultItem.ntype == 2)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("bi=%08x"),m_oResultItem.biValue_32);
					memcpy(pszBinBuf,&m_oResultItem.sec,4);
					memcpy(pszBinBuf+4,&m_oResultItem.nSec,4);
					memcpy(pszBinBuf+8,&m_oResultItem.biValue_32,4);
					m_pBinSampleData->m_oRcdDataBuffer.AddBuffer(pszBinBuf,12);
				}
			}
		}

        //test
		// if(1)
		// {
		// 	long nSec,nNSec;
		// 	unsigned int biValue_32;

		// 	biValue_32 = 1;
		// 	nSec = 11;
		// 	nNSec = 0;
		// 	memcpy(pszBinBuf,&nSec,4);
		// 	memcpy(pszBinBuf+4,&nNSec,4);
		// 	memcpy(pszBinBuf+8,&biValue_32,4);
		// 	m_pBinSampleData->m_oRcdDataBuffer.AddBuffer(pszBinBuf,12);

		// 	biValue_32 = 3;
		// 	nSec = 11;
		// 	nNSec = 500000000;
		// 	memcpy(pszBinBuf,&nSec,4);
		// 	memcpy(pszBinBuf+4,&nNSec,4);
		// 	memcpy(pszBinBuf+8,&biValue_32,4);
		// 	m_pBinSampleData->m_oRcdDataBuffer.AddBuffer(pszBinBuf,12);
		// }

        //test
        CSttParas oBinParas;
        long nCnt = m_pBinSampleData->m_oRcdDataBuffer.m_nDataLength/12;
        char *pDataBuf = m_pBinSampleData->m_oRcdDataBuffer.m_pBuffer;
        unsigned int nBinRefStatus = 0;
        for(int i = 0;i < nCnt;i++)
        {
            CDataGroup *pDataGroup = oBinParas.AddNewGroup("",SYS_STATE_XEVENT_EVENTID_BIN,SYS_STATE_RETTYPE_EVENT,FALSE);
            long nTime;
            unsigned int nStatus;
            double dTime;
            memcpy(&nTime,pDataBuf,4);
            dTime = nTime;
            pDataBuf += 4;

            memcpy(&nTime,pDataBuf,4);
            dTime += nTime*0.000000001;
            pDataGroup->AddNewData("RealTime",dTime);
            pDataBuf += 4;

            memcpy(&nStatus,pDataBuf,4);
            CString strID;
            long nBinVal = 1;
            for(int j = 0;j < 32;j++)
            {
                if(((nStatus>>j)&0x1) == ((nBinRefStatus>>j)&0x1))
                {

                }
                else
                {
                    if((nStatus>>j)&0x1)
                    {
                        strID.Format(_T("B%d"),j+1);
                        pDataGroup->AddNewData(strID.GetString(),nBinVal);
                    }
                }
            }
            nBinRefStatus = nStatus;
            pDataBuf += 4;

        }
        m_pSttPst200App->RTDATA((CDataGroup*)&oBinParas);
        CSttParas oPowerParas;
        CalPower(&oPowerParas);
        m_pSttPst200App->EventTestFinish((CDataGroup*)&oPowerParas);
        bDownloadRTDS = FALSE;
        bTestStarted = FALSE;
        m_pSttPst200App->m_bReStartStage = FALSE;
    }

    //读取2M RecordData
    nRet = read(m_nCommfd,m_pDrvResults,0x261);
    if(nRet > 0)
    {
        g_pRecvStable2MBuf->WriteBuf((char*)m_pDrvResults,nRet);
    }

    if(!bTestStarted)
		return;	
}

void CSttDevicePST200s::SendConfToDevice()
{
    //1-digital 2-switch 3-2M 4-week
	memset(&oReplayPara,0,sizeof(DrvReplayPara));

	long nFre = m_pSttPst200App->m_nFre;
	while(1)
	{		
		if(nFre >= 250)
		{
			break;
		}

		nFre += m_pSttPst200App->m_nFre;
	}
	if(nFre > 250)
		nFre -= m_pSttPst200App->m_nFre;

	float fSample = 1000000.0/nFre;

	oReplayPara.freq = 100000000.0/fSample;//5KHz
    oReplayPara.mSec = 20000;//默认20秒回放
    long nRtdsChCount = m_pOutputMap->GetCount();
    if(m_pRtdsReplayData->CanRead(1) && nRtdsChCount > 0)
    {
        long nRtdsPointCount = m_pRtdsReplayData->m_nDataLength/(nRtdsChCount*4);
		oReplayPara.mSec = nRtdsPointCount*1000/fSample;
    }
    oReplayPara.mSec -= 100;//防止回放结尾数据跳变，提前结束
    if(g_pSttSimulationBase->m_nOutputType == OutputType_WeekSwitch)
    {
        //小信号模块
        oReplayPara.module = 1 << m_oModuleDef.nWModulePos;
        //    oReplayPara.data[0] = 0x01020304;//小信号48通道默认映射
        //    oReplayPara.data[1] = 0x05060708;
        //    oReplayPara.data[2] = 0x090a0b0c;
        //    oReplayPara.data[3] = 0x0d0e0f10;
        //    oReplayPara.data[4] = 0x11121314;
        //    oReplayPara.data[5] = 0x15161718;
        //    oReplayPara.data[6] = 0x191a1b1c;
        //    oReplayPara.data[7] = 0x1d1e1f20;
        //    oReplayPara.data[8] = 0x21222324;
        //    oReplayPara.data[9] = 0x25262728;
        //    oReplayPara.data[10] = 0x292a2b2c;
        //    oReplayPara.data[11] = 0x2d2e2f30;
        //        REPLAY_HDCH_RCDDATA_MAPS *pMaps = &m_pRtdsMapsMngr->oModules[0];  //只取第一个
        //        for (int i=0; i<pMaps->nMapCount; i++)
        //        {
        //            long nRTDSIdx = pMaps->oHdChRcdDataMaps[i].nRcdDataIndex;
        //            if (nRTDSIdx > -1)
        //            {
        //                long nHdIdx = pMaps->oHdChRcdDataMaps[i].nHdCh;
        //                long nIndex = nRTDSIdx%4;
        //                long nDataIndex = nRTDSIdx/4;
        //                if(nIndex == 0)
        //                {
        //                    oReplayPara.data[nDataIndex] += (nHdIdx + 1)<<24;
        //                }
        //                else if(nIndex == 1)
        //                {
        //                    oReplayPara.data[nDataIndex] += (nHdIdx + 1)<<16;
        //                }
        //                else if(nIndex == 2)
        //                {
        //                    oReplayPara.data[nDataIndex] += (nHdIdx + 1)<<8;
        //                }
        //                else
        //                {
        //                    oReplayPara.data[nDataIndex] += (nHdIdx + 1);
        //                }
        //                oReplayPara.ch++;//回放实际通道数量
        //            }
        //        }

		long nIndex = 0;
		long nDataIndex = 0;
        for(int i = 0 ;i < nRtdsChCount;i++)
        {
            if(g_pSttSimulationBase->m_pszRtdsMapType[i]>>24 == 1)
            {                
                long nChIdx = g_pSttSimulationBase->m_pszRtdsMapType[i]&0xFF;
                if(nIndex == 0)
                {
                    oReplayPara.data[nDataIndex] += nChIdx<<24;
                }
                else if(nIndex == 1)
                {
                    oReplayPara.data[nDataIndex] += nChIdx<<16;
                }
                else if(nIndex == 2)
                {
                    oReplayPara.data[nDataIndex] += nChIdx<<8;
                }
                else
                {
                    oReplayPara.data[nDataIndex] += nChIdx;
                }
				nIndex++;
				if(nIndex == 4)
				{
					nDataIndex++;
					nIndex = 0;
				}
            }
        }

        oReplayPara.ch = g_pSttSimulationBase->m_nReplayChCntWeek;//回放实际通道数量
        for(int i = 0; i < 12; i++)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReplayChan[%02d] %08x"),i,oReplayPara.data[i]);
        }

        for(int i = 0;i < nRtdsChCount;i++)
        {
            //            fWeek = GetCoefByRcdDataMaps(i);
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Ch%d,Coef=%f"),i,g_pSttSimulationBase->m_fCoefWeek[i]);
        }

        //开关量模块
        oReplayPara.module |= 1 << m_oModuleDef.nSModulePos;
    }
    else if(g_pSttSimulationBase->m_nOutputType == OutputType_SmvGoose)
    {
        oReplayPara.module = 1 << m_oModuleDef.nDModulePos;
        oReplayPara.ch = g_pSttSimulationBase->m_nReplayChCntSmv;//回放实际通道数量

        for(int i = 0;i < nRtdsChCount;i++)
        {
            if(g_pSttSimulationBase->m_pszRtdsMapType[i]>>24 == 3)
            {
                long nIndex = i%4;
                long nDataIndex = i/4;
                long nChIdx = 0;
                long nType = (g_pSttSimulationBase->m_pszRtdsMapType[i]>>16)&0xFF;
                long nIdx = g_pSttSimulationBase->m_pszRtdsMapType[i]&0xFF;
                if(nType == 1)
                {
                    //U
                    switch(nIdx)
                    {
                    case 1:
                        nChIdx = 1;
                        break;
                    case 2:
                        nChIdx = 2;
                        break;
                    case 3:
                        nChIdx = 3;
                        break;
                    case 4:
                        nChIdx = 5;
                        break;
                    case 5:
                        nChIdx = 6;
                        break;
                    case 6:
                        nChIdx = 7;
                        break;
                    case 7:
                        nChIdx = 8;
                        break;
                    case 8:
                        nChIdx = 9;
                        break;
                    case 9:
                        nChIdx = 10;
                        break;
                    case 10:
                        nChIdx = 11;
                        break;
                    case 11:
                        nChIdx = 12;
                        break;
                    case 12:
                        nChIdx = 13;
                        break;
                    }
                }
                else if(nType == 2)
                {
                    //I
                    switch(nIdx)
                    {
                    case 1:
                        nChIdx = 14;
                        break;
                    case 2:
                        nChIdx = 15;
                        break;
                    case 3:
                        nChIdx = 16;
                        break;
                    case 4:
                        nChIdx = 17;
                        break;
                    case 5:
                        nChIdx = 18;
                        break;
                    case 6:
                        nChIdx = 19;
                        break;
                    case 7:
                        nChIdx = 20;
                        break;
                    case 8:
                        nChIdx = 21;
                        break;
                    case 9:
                        nChIdx = 22;
                        break;
                    case 10:
                        nChIdx = 23;
                        break;
                    case 11:
                        nChIdx = 24;
                        break;
                    case 12:
                        nChIdx = 25;
                        break;
                    }
                }

                if(nIndex == 0)
                {
                    oReplayPara.data[nDataIndex] += nChIdx<<24;
                }
                else if(nIndex == 1)
                {
                    oReplayPara.data[nDataIndex] += nChIdx<<16;
                }
                else if(nIndex == 2)
                {
                    oReplayPara.data[nDataIndex] += nChIdx<<8;
                }
                else
                {
                    oReplayPara.data[nDataIndex] += nChIdx;
                }
            }
        }

        for(int i = 0;i < nRtdsChCount;i++)
        {
            //            fWeek = GetCoefByRcdDataMaps(i);
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Ch%d,Coef=%f"),i,g_pSttSimulationBase->m_fCoefSmv[i]);
        }
    }

    ioctl(m_nCommfd,0x308,0);
    write(m_nCommfd,(char*)&oReplayPara,sizeof(DrvReplayPara));
}

double CSttDevicePST200s::GetCoefByRcdDataMaps(long nRcdDataIndex)
{
    REPLAY_HDCH_RCDDATA_MAPS *pMaps = &m_pRtdsMapsMngr->oModules[0];  //只取第一个
    for(int i = 0;i < pMaps->nMapCount;i++)
    {
        if(nRcdDataIndex == pMaps->oHdChRcdDataMaps[i].nRcdDataIndex)
        {
            return pMaps->oHdChRcdDataMaps[i].fCoef;
        }
    }

    return -1;
}

//DDR回放需要多写2秒的数据，防止读取溢出
void CSttDevicePST200s::SendDataToDevice_Week()
{
    long nReadTotalLen = 0;
    long nPos = 0;
    long nNeedReadLen = oReplayPara.ch * 4;
    long nRtdsChCount = m_pOutputMap->GetCount();
    oReplayDatas.oData.lenth = 0;
    oReplayDatas.module = 1 << m_oModuleDef.nWModulePos;
    oReplayDatas.pkglen = nNeedReadLen;

    //    double fWeek[48];
    //    for(int i = 0;i < oReplayPara.ch; i++)
    //    {
    //        fWeek[i] = GetCoefByRcdDataMaps(i);
    //    }
    double fWeek;
    BOOL bWriteData = FALSE;
    ConverStruct oTrans;
    float fAmp;
    long nCode;

    while(TRUE)
    {
        if((m_pRtdsReplayData->m_nDataLength - m_nPkgIndex*m_nRtdsChLength) >= m_nRtdsChLength)
        {
            if((nReadTotalLen + nNeedReadLen) > 4000000*4)
            {
                break;
            }

            char* pszBuf = m_pRtdsReplayData->m_pBuffer + m_nPkgIndex*m_nRtdsChLength;
            for(int i = 0; i < nRtdsChCount;i++)
            {
                if(g_pSttSimulationBase->m_pszRtdsMapType[i]>>24 == 1)
                {
                    fWeek = g_pSttSimulationBase->m_fCoefWeek[i];
                    if(fWeek > 0.9)
                    {
                        for(int j = 0;j < 4;j++)
                        {
                            oTrans.b[3-j] = *(pszBuf + i*4 + j);
                        }

                        fAmp = oTrans.f/fWeek;
                        nCode = fAmp*0.1*0x7fffffff;
                        oReplayDatas.oData.dat[nPos] = nCode;
                    }
                    else
                    {
                        oReplayDatas.oData.dat[nPos] = 0;
                    }

                    nPos++;
                    bWriteData = TRUE;
                }
            }

            nReadTotalLen += nNeedReadLen;
            m_nPkgIndex++;

            oReplayDatas.oData.lenth = nReadTotalLen/4;
        }
        else
            break;
    }

    if(bWriteData)
    {
        ioctl(m_nCommfd,0x308,1);
        write(m_nCommfd,(char*)&oReplayDatas,sizeof(DrvReplayDatas));
    }
    else
    {
		m_nCurModule = 2;
		m_nPkgIndex = 0;

		SendDataToDevice_Switch();
    }
}

void CSttDevicePST200s::SendDataToDevice_Digital()
{
    long nReadTotalLen = 0;
    long nPos = 0;
    long nNeedReadLen = g_pSttSimulationBase->m_nReplayChCntSmv * 4;
    long nRtdsChCount = m_pOutputMap->GetCount();
    oReplayDatas.oData.lenth = 0;
    oReplayDatas.module = 1 << m_oModuleDef.nDModulePos;
    oReplayDatas.pkglen = nNeedReadLen;

    //    double fWeek[48];
    //    for(int i = 0;i < oReplayPara.ch; i++)
    //    {
    //        fWeek[i] = GetCoefByRcdDataMaps(i);
    //    }
    double fWeek;
    BOOL bWriteData = FALSE;
    ConverStruct oTrans;

    while(TRUE)
    {
        if((m_pRtdsReplayData->m_nDataLength - m_nPkgIndex*m_nRtdsChLength) >= m_nRtdsChLength)
        {
            if((nReadTotalLen + nNeedReadLen) > 4000000*4)
            {
                break;
            }

            char* pszBuf = m_pRtdsReplayData->m_pBuffer + m_nPkgIndex*m_nRtdsChLength;
            for(int i = 0; i < nRtdsChCount;i++)
            {
                if(g_pSttSimulationBase->m_pszRtdsMapType[i]>>24 == 3)
                {
                    fWeek = g_pSttSimulationBase->m_fCoefSmv[i];
                    if(fWeek > 0.0001)
                    {
                        for(int j = 0;j < 4;j++)
                        {
                            oTrans.b[3-j] = *(pszBuf + i*4 + j);
                        }

                        oReplayDatas.oData.dat[nPos] = oTrans.f/fWeek;
                        nPos++;
                        bWriteData = TRUE;
                    }
                }
            }

            nReadTotalLen += nNeedReadLen;
            m_nPkgIndex++;

            oReplayDatas.oData.lenth = nReadTotalLen/4;
        }
        else
            break;
    }

    if(bWriteData)
    {
        ioctl(m_nCommfd,0x308,1);
        write(m_nCommfd,(char*)&oReplayDatas,sizeof(DrvReplayDatas));
    }
    else
    {
        if(m_pSttPst200App->m_bReStartStage)
        {
            SetTestStart(0);
        }
        else
        {
            CDataGroup oDataGroup;
            m_pSttPst200App->EventRcdDataLoadFinished(&oDataGroup);
        }
    }
}

void CSttDevicePST200s::SendDataToDevice_Switch()
{
    long nRtdsChCount = m_pOutputMap->GetCount();
    long nReadTotalLen = 0;
    long nNeedReadLen = 4;
    oReplayDatas.oData.lenth = 0;
    oReplayDatas.module = 1 << m_oModuleDef.nSModulePos;
    oReplayDatas.pkglen = nNeedReadLen;
    long nPos = 0;
	unsigned int nReplayBout;
    BOOL bWriteData = FALSE;
    long nBoutIdx = 0;
    long nBoutData = 0;

    while(TRUE)
    {
        if((m_pRtdsReplayData->m_nDataLength - m_nPkgIndex*m_nRtdsChLength) >= m_nRtdsChLength)
        {
            if((nReadTotalLen + nNeedReadLen) > 4000000*4)
            {
                break;
            }

            char* pszBuf = m_pRtdsReplayData->m_pBuffer + m_nPkgIndex*m_nRtdsChLength;
            nReplayBout = 0xFFFFFFFF;
			for(int i = 0; i < nRtdsChCount;i++)
			{
				if((g_pSttSimulationBase->m_pszRtdsMapType[i]>>24) == 2)
				{
					nBoutIdx = g_pSttSimulationBase->m_pszRtdsMapType[i]&0xFF;
					nBoutData = *(pszBuf + i*4 + 3);
					if(nBoutData)
					{
						nReplayBout &= ~(1<<(nBoutIdx - 1));
					}

					bWriteData = TRUE;
				}
			}

			oReplayDatas.oData.dat[nPos] = nReplayBout;
            nPos++;

            nReadTotalLen += 4;
            m_nPkgIndex++;

            oReplayDatas.oData.lenth = nReadTotalLen/4;
        }
        else
        {
            break;
        }
    }

    if(bWriteData)
    {
        ioctl(m_nCommfd,0x308,1);
        write(m_nCommfd,(char*)&oReplayDatas,sizeof(DrvReplayDatas));
    }
    else
    {
        if(m_pSttPst200App->m_bReStartStage)
        {
            SetTestStart(0);
        }
        else
        {
            CDataGroup oDataGroup;
            m_pSttPst200App->EventRcdDataLoadFinished(&oDataGroup);
        }
    }
}
