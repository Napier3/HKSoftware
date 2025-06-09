#include "SttDevicePIC200D.h"
#include "../../Engine/SttServerTestCtrlCntr.h"
#include "../../Engine/SttTestServerBase.h"
#include "../../SttTest/Common/Adjust/SttAdjust_ModuleOutput.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>	//SIGIO
#include<sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "qthread.h"

#define MODE_1A   0  //硬件档位 10mA,2A
#define MODE_250A 1  //硬件档位 50A,100A,250A

#define MeasVoltHG_10mV  0
#define MeasVoltHG_200mV 1
#define MeasVoltHG_1V    2
#define MeasVoltHG_5V    3

CSttDevicePIC200D *CSttDevicePIC200D::g_pSttDevicePIC200D=NULL;
int DMARes[200000];
long CSttDevicePIC200D::g_nSttDeviceRef = 0;
float vlue_AD1;//ch1_ac_V
float vlue_AD2;//ch1_ac_I
float vlue_R;//ch1_ac_r
float vlue_AD1SnedData;//ch1_ac_V
float vlue_AD2SnedData;//ch1_ac_I
float vlue_RSnedData;//ch1_ac_r
int CloseLoopCount = 0;
int count_DMA=0;

float m_fuzhi[30];//0表示直流的幅值,1表示交流的幅值,其他项是用于计算谐波畸变率时使用(肯定是交流的)
float m_xiangwei[30];//同上
float m_pinlv[30];//同上
int DMACount = 0;
int GetStateAutoCount = 0;
int vlue_AD1Flag = 0; //0 mv,1V.
int CloseLoopCountNum = 0;
int State1Value;
int DMA_FLAG = 0;
#define PI 3.1415926
#define DataLength 8192*4//250k  fhz
#define ADcou_Num 1000
#define count_DMA_Num 1
#define GetStateAutoCountNum 3
float DMAtemp1[DataLength];
float DMAtemp2[DataLength];
float ADtemp1[200000];
float ADtemp2[200000];

//数组标号随档位值由小到大,0代表第一个档
float fCoef_Out_1A;//1A档输出幅值系数
float fZero_Out_1A;//1A档输出零漂
float fCoef_Out_250A;//250A档输出幅值系数
float fZero_Out_250A;//250A档输出零漂

float fCoef_Gather_u[4];//电压采集幅值系数
float fZero_Gather_u[4];//电压采集零漂

float fCoef_Gather_1A[3];//1A档电流采集幅值系数
float fZero_Gather_1A[3];//1A档电流采集零漂
float fCoef_Gather_250A[3];//1A档电流采集幅值系数
float fZero_Gather_250A[3];//1A档电流采集零漂

int SendDataToPCCount=0;
int SendDataToPCCountFlag=0;
DCpbufferdata DCbuffer;
ACpbufferdata ACbuffer;
StructModePara StrModePara;
PSTT_MODULE pModule=NULL;

MEAS_MODULE *pMeasModule_Volt=NULL;
MEAS_MODULE *pMeasModule_Curr=NULL;
long nADCurrentState;
long nADVoltageState;

CSttDevicePIC200D::CSttDevicePIC200D()
{
    m_nOnTimerMs=10;
    m_nDeviceOnTimerMs=1000;
    SetMeasDefault();
}

void CSttDevicePIC200D::Create()
{
    g_nSttDeviceRef++;

    if (g_nSttDeviceRef == 1)
    {
        g_pSttDevicePIC200D=new CSttDevicePIC200D;
        g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePIC200D;
    }
}

void CSttDevicePIC200D::Release()
{
    g_nSttDeviceRef--;

    if (g_nSttDeviceRef == 0)
    {
        delete g_pSttDevicePIC200D;
        g_pSttDevicePIC200D = NULL;
    }
}

void CSttDevicePIC200D::InitCoef()
{
    /************************************************xishu********************************************************/
    /**********************电流输出部分***************************/
    //第一个0:表示第一个通道；第二个0:表示第一个模块
    //第三个参数：直流电流模块
    //返回值：硬件档位最大值
    //	float fVoltMax_channel_1=stt_adj_get_ac_max_GearVal(0,0,STT_MODULE_TYPE_DCCURRENT);//20A
    //	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("------ fVoltMax_channel_1 = %f "), fVoltMax_channel_1);
    //	float fVoltMax_channel_2=stt_adj_get_ac_max_GearVal(1,0,STT_MODULE_TYPE_DCCURRENT);//100A
    //	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("------ fVoltMax_channel_2 = %f "), fVoltMax_channel_2);
    //	float fVoltMax_channel_2=stt_adj_get_ac_max_GearVal(1,0,STT_MODULE_TYPE_DCCURRENT);//100A
    //	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("------ fVoltMax_channel_2 = %f "), fVoltMax_channel_2);
    //	float fVoltMax_channel_2=stt_adj_get_ac_max_GearVal(1,0,STT_MODULE_TYPE_DCCURRENT);//100A
    //	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("------ fVoltMax_channel_2 = %f "), fVoltMax_channel_2);
    //这个函数会根据下发的幅值，查找合适的档位
    //参数0-0-0-1:表示第一个模块，第一个通道，第一个温区，基波

    /*******************************************************************************************************************************/
    /**************************电压采集部分**********************/
    float fGearVal=0.01f;//预设置采集电压值
    //1-0-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
    PSTT_ADJUST_ITEM pMeasAdjItem=stt_adj_find_meas_u_item(fGearVal,1,0,0,0);  //该函数能根据输入参数，查找到的档位值
    if(pMeasAdjItem!=NULL)
    {
        fCoef_Gather_u[0]=pMeasAdjItem->m_fCoef;
        fZero_Gather_u[0]=pMeasAdjItem->m_fZero;
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("fCoef_Gather_u[0] = %f ----- fZero_Gather_u[0] = %f ------"), fCoef_Gather_u[0], fZero_Gather_u[0]);


    fGearVal=0.2f;//预设置采集电压值
    //1-0-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
    pMeasAdjItem=stt_adj_find_meas_u_item(fGearVal,1,0,0,0);  //该函数能根据输入参数，查找到的档位值
    if(pMeasAdjItem!=NULL)
    {
        fCoef_Gather_u[1]=pMeasAdjItem->m_fCoef;
        fZero_Gather_u[1]=pMeasAdjItem->m_fZero;
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("fCoef_Gather_u[1] = %f ----- fZero_Gather_u[1] = %f ------"), fCoef_Gather_u[1], fZero_Gather_u[1]);

    fGearVal=1.0f;//预设置采集电压值
    //1-0-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
    pMeasAdjItem=stt_adj_find_meas_u_item(fGearVal,1,0,0,0);  //该函数能根据输入参数，查找到的档位值
    //	fCoef_Gather_u=1;//电压采集幅值系数
    //	fZero_Gather_u=0;//电压采集零漂
    if(pMeasAdjItem!=NULL)
    {
        fCoef_Gather_u[2]=pMeasAdjItem->m_fCoef;
        fZero_Gather_u[2]=pMeasAdjItem->m_fZero;
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("fCoef_Gather_u[2] = %f ----- fZero_Gather_u[2] = %f ------"), fCoef_Gather_u[2], fZero_Gather_u[2]);

    fGearVal=5.0f;//预设置采集电压值
    //1-0-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
    pMeasAdjItem=stt_adj_find_meas_u_item(fGearVal,1,0,0,0);  //该函数能根据输入参数，查找到的档位值
    //	fCoef_Gather_u=1;//电压采集幅值系数
    //	fZero_Gather_u=0;//电压采集零漂
    if(pMeasAdjItem!=NULL)
    {
        fCoef_Gather_u[3]=pMeasAdjItem->m_fCoef;
        fZero_Gather_u[3]=pMeasAdjItem->m_fZero;
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("fCoef_Gather_u[3] = %f ----- fZero_Gather_u[3] = %f ------"), fCoef_Gather_u[3], fZero_Gather_u[3]);

    /***************************电流采集部分***********************/
    float fGearVal_channel = 0.1f;//对应小电流端子
    //1-0-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
    PSTT_ADJUST_ITEM pMeasAdjItem_channel_1=stt_adj_find_meas_i_item(fGearVal_channel,1,0,0,0);  //该函数能根据输入参数，查找到的档位值
    //	float fCoef_Gather_i=1;//电流采集幅值系数
    //	float fZero_Gather_i=0;//电流采集零漂
    if(pMeasAdjItem_channel_1!=NULL)
    {
        fCoef_Gather_1A[0]=pMeasAdjItem_channel_1->m_fCoef;
        fZero_Gather_1A[0]=pMeasAdjItem_channel_1->m_fZero;
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("fCoef_Gather_1A[0] = %f ----- fZero_Gather_1A[0] = %f ------"), fCoef_Gather_1A[0], fZero_Gather_1A[0]);

    fGearVal_channel=1.0f;
    pMeasAdjItem_channel_1=stt_adj_find_meas_i_item(fGearVal_channel,1,0,0,0);  //该函数能根据输入参数，查找到的档位值
    //	fCoef_Gather_i=1;//电流采集幅值系数
    //	fZero_Gather_i=0;//电流采集零漂
    if(pMeasAdjItem_channel_1!=NULL)
    {
        fCoef_Gather_1A[1]=pMeasAdjItem_channel_1->m_fCoef;
        fZero_Gather_1A[1]=pMeasAdjItem_channel_1->m_fZero;
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("fCoef_Gather_1A[1] = %f ----- fZero_Gather_1A[1] = %f ------"), fCoef_Gather_1A[1], fZero_Gather_1A[1]);

    fGearVal_channel=5.0f;
    pMeasAdjItem_channel_1=stt_adj_find_meas_i_item(fGearVal_channel,1,0,0,0);  //该函数能根据输入参数，查找到的档位值
    //	fCoef_Gather_i=1;//电流采集幅值系数
    //	fZero_Gather_i=0;//电流采集零漂
    if(pMeasAdjItem_channel_1!=NULL)
    {
        fCoef_Gather_1A[2]=pMeasAdjItem_channel_1->m_fCoef;
        fZero_Gather_1A[2]=pMeasAdjItem_channel_1->m_fZero;
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("fCoef_Gather_1A[2] = %f ----- fZero_Gather_1A[2] = %f ------"), fCoef_Gather_1A[2], fZero_Gather_1A[2]);

    fGearVal_channel=2.5f;
    //1-1-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
    PSTT_ADJUST_ITEM pMeasAdjItem_channel_2=stt_adj_find_meas_i_item(fGearVal_channel,1,1,0,0);  //该函数能根据输入参数，查找到的档位值
    //	fCoef_Gather_i=1;//电流采集幅值系数
    //	fZero_Gather_i=0;//电流采集零漂
    if(pMeasAdjItem_channel_2!=NULL)
    {
        fCoef_Gather_250A[0]=pMeasAdjItem_channel_2->m_fCoef;
        fZero_Gather_250A[0]=pMeasAdjItem_channel_2->m_fZero;
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("fCoef_Gather_250A[0] = %f ----- fZero_Gather_250A[0] = %f ------"), fCoef_Gather_250A[0], fZero_Gather_250A[0]);


    fGearVal_channel=15.0f;
    //1-1-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
    pMeasAdjItem_channel_2=stt_adj_find_meas_i_item(fGearVal_channel,1,1,0,0);  //该函数能根据输入参数，查找到的档位值
    //	fCoef_Gather_i=1;//电流采集幅值系数
    //	fZero_Gather_i=0;//电流采集零漂
    if(pMeasAdjItem_channel_2!=NULL)
    {
        fCoef_Gather_250A[1]=pMeasAdjItem_channel_2->m_fCoef;
        fZero_Gather_250A[1]=pMeasAdjItem_channel_2->m_fZero;
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("fCoef_Gather_250A[1] = %f ----- fZero_Gather_250A[1] = %f ------"), fCoef_Gather_250A[1], fZero_Gather_250A[1]);

    fGearVal_channel=200.0f;
    //1-1-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
    pMeasAdjItem_channel_2=stt_adj_find_meas_i_item(fGearVal_channel,1,1,0,0);  //该函数能根据输入参数，查找到的档位值
    //	fCoef_Gather_i=1;//电流采集幅值系数
    //	fZero_Gather_i=0;//电流采集零漂
    if(pMeasAdjItem_channel_2!=NULL)
    {
        fCoef_Gather_250A[2]=pMeasAdjItem_channel_2->m_fCoef;
        fZero_Gather_250A[2]=pMeasAdjItem_channel_2->m_fZero;
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("fCoef_Gather_250A[2] = %f ----- fZero_Gather_250A[2] = %f ------"), fCoef_Gather_250A[2], fZero_Gather_250A[2]);
    /**********************************************************************************************************/
}

int CSttDevicePIC200D::InitDevice(BOOL bHasAdjFile)
{
    g_nNeedReportUTC = 0;
    g_nNeedReportRTDATA = 0;
    g_nNeedReportEvents = 0;
    g_nNeedReportDevExcept = 0;

    for(int i=0;i<g_theDeviceSystemParameter->m_nModuleCount;i++)
    {
        if(g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_DCCURRENT)
        {
            pModule = &g_theDeviceSystemParameter->m_oModules[i];
            break;
        }
    }

    m_nCommfd=open("/dev/stt5000",O_RDWR);

    qDebug()<<"m_nCommfd="<<QString::number(m_nCommfd);
    ioctl(m_nCommfd, 0x103, 1);//Start DMA
    //	SENDAtoFPGA(1,0x103);

    MeasDev_Init();
    for(int i=0;i<g_MeasDevice->nModuleCnt;i++)
    {
        if(g_MeasDevice->oModules[i].nModuleType == STT_MODULE_TYPE_MEAS_VOLT)
        {
            g_MeasDevice->oModules[i].nChanCount = 1;
            g_MeasDevice->oModules[i].oChannels[0].nHarmCount = 1;
            pMeasModule_Volt = &g_MeasDevice->oModules[i];
        }
        else
        {
            g_MeasDevice->oModules[i].nChanCount = 2;
            g_MeasDevice->oModules[i].oChannels[0].nHarmCount = 1;
            g_MeasDevice->oModules[i].oChannels[1].nHarmCount = 1;
            pMeasModule_Curr = &g_MeasDevice->oModules[i];
        }
    }
    return m_nCommfd;
}

void CSttDevicePIC200D::SetMeasDefault()
{
    nADCurrentState = 2;
    nADVoltageState = MeasVoltHG_5V;
}

void CSttDevicePIC200D::SetMeasModuleChanGear(int nModuleType,int nModulePos, int nChannel, int nGearId)
{
    PSTT_MODULE pMeasModule = NULL;
    pMeasModule = stt_adj_find_module_byModulePos(g_theDeviceSystemParameter,nModulePos,nModuleType);
    if(pMeasModule != NULL)
    {
        if(pMeasModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_MEAS_VOLT)
        {
            if(nChannel == 0)
            {
                //电压采集档位设置
                if(nGearId==MeasVoltHG_10mV)
                {
                    nADVoltageState = MeasVoltHG_10mV;
                }
                else if(nGearId==MeasVoltHG_200mV)
                {
                    nADVoltageState = MeasVoltHG_200mV;
                }
                else if(nGearId==MeasVoltHG_1V)
                {
                    nADVoltageState = MeasVoltHG_1V;
                }
                else
                {
                    nADVoltageState = MeasVoltHG_5V;
                }
            }
        }
        else if(pMeasModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_MEAS_CURRENT)
        {
            if(nChannel == MODE_1A)
            {
                if(nGearId==0)//01
                {
                    nADCurrentState = 0;
                }
                else if(nGearId==1)
                {
                    nADCurrentState = 1;
                }
                else
                {
                    nADCurrentState = 2;
                }
            }
            else if(nChannel == MODE_250A)
            {
                nADCurrentState = 2;//250A档只能出40A以上电流，所以采集低档无意义
            }
        }

    }
    ioctl(m_nCommfd, 0x103, 2);//开DMA中断消息
    SetVoltMeasGear(nADVoltageState);
    SetCurrMeasGear(nADCurrentState);

}

void CSttDevicePIC200D::tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
{	
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("m_nModuleType=%d"),pTmt->m_nModuleType);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("m_nModuleIndex=%d"),pTmt->m_nModuleIndex);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("m_nFreqIndex=%d"),pTmt->m_nFreqIndex);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("m_nChannel=%d"),pTmt->m_nChannel);

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("m_fMag=%.3f"),pTmt->m_oChannels[pTmt->m_nChannel].m_oVector.m_fMag);
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("m_fAngle=%.3f"),pTmt->m_oChannels[pTmt->m_nChannel].m_oVector.m_fAngle);

    tmt_Pic200dTest oTmt_Pic200dTest;
    oTmt_Pic200dTest.m_oPic200dPara.init();

    if(pTmt->m_nChannel == 0)
    {
        oTmt_Pic200dTest.m_oPic200dPara.m_oSetting.PIC200DOUTStateFlag = MODE_1A;
    }
    else
    {
        oTmt_Pic200dTest.m_oPic200dPara.m_oSetting.PIC200DOUTStateFlag = MODE_250A;
    }

    oTmt_Pic200dTest.m_oPic200dPara.m_oDA.DA1_FZ=pTmt->m_oChannels[pTmt->m_nChannel].m_oVector.m_fMag;
    oTmt_Pic200dTest.m_oPic200dPara.m_oDA.DA1_ACrisetime=0.1f;
    oTmt_Pic200dTest.m_oPic200dPara.m_oDA.DA1_ACdowntime=1.0f;
    oTmt_Pic200dTest.m_oPic200dPara.m_oDA.DA1_ACholdtime=999;
    tmt_to_drv_pic200d(&oTmt_Pic200dTest,FALSE);
}

void CSttDevicePIC200D::SetVoltMeasGear(long nGear)
{
    SENDAtoFPGA(1<<4,0x010b);
    //电压采集档位设置
    if(nGear==MeasVoltHG_10mV)
    {
        StrModePara.PIC200DStatesendbuffer |= BIT6+BIT7;
        GetStateAutoCount = 0;

        SENDAtoFPGA(0,0x010b);
    }
    else if(nGear==MeasVoltHG_200mV)
    {
        StrModePara.PIC200DStatesendbuffer &= ~(BIT7);
        StrModePara.PIC200DStatesendbuffer |= BIT6;
        GetStateAutoCount = 0;
    }
    else if(nGear==MeasVoltHG_1V)
    {
        StrModePara.PIC200DStatesendbuffer &= ~(BIT6);
        StrModePara.PIC200DStatesendbuffer |= BIT7;
        GetStateAutoCount = 0;
    }
    else
    {
        //MeasVoltHG_5V
        StrModePara.PIC200DStatesendbuffer |= BIT6+BIT7;
        GetStateAutoCount = 0;
    }

    SENDAtoFPGA(StrModePara.PIC200DStatesendbuffer,0x010d);
}

void CSttDevicePIC200D::SetCurrMeasGear(long nGear)
{
    if(nGear==0)//01
    {
        StrModePara.PIC200DStatesendbuffer &= ~(BIT9);
        StrModePara.PIC200DStatesendbuffer |= BIT8;
    }
    else if(nGear==1)
    {
        StrModePara.PIC200DStatesendbuffer &= ~(BIT8+BIT9);//00
    }
    else
    {
        StrModePara.PIC200DStatesendbuffer |= BIT8+BIT9;//11
    }
    SENDAtoFPGA(StrModePara.PIC200DStatesendbuffer,0x010d);
}

void CSttDevicePIC200D::tmt_to_drv_pic200d(tmt_Pic200dTest *pTmt,BOOL bUseGear)
{
    CLogPrint::LogString(XLOGLEVEL_DEBUG,_T("******* PIC200D  2022-07 *******"));

    InitCoef();
    SendDataToPCCount = 0;
    SendDataToPCCountFlag = 0;
    StrModePara.PIC200DStatesendbuffer=0;

    /************************************************************************************/
    //	 qDebug()<<"Start_PIC200D = ~~~~~~~~~~~~";
    StrModePara.VoltageAlarmMin = pTmt->m_oPic200dPara.m_oSetting.VoltageAlarmMin;
    StrModePara.VoltageAlarmMax = pTmt->m_oPic200dPara.m_oSetting.VoltageAlarmMax;
    StrModePara.CurrentAlarmMin = pTmt->m_oPic200dPara.m_oSetting.CurrentAlarmMin;
    StrModePara.CurrentAlarmMax = pTmt->m_oPic200dPara.m_oSetting.CurrentAlarmMax;
    StrModePara.PIC200DOUTStateFlag = pTmt->m_oPic200dPara.m_oSetting.PIC200DOUTStateFlag;

    qDebug()<< "PIC200DOUTStateFlag ="<<StrModePara.PIC200DOUTStateFlag;
    qDebug()<< "DA1_FZ ="<<pTmt->m_oPic200dPara.m_oDA.DA1_FZ;

    if(bUseGear)
    {
        StrModePara.PIC200DGetStateAutoFlag = pTmt->m_oPic200dPara.m_oSetting.PIC200DGetStateAutoFlag;
        if(StrModePara.PIC200DGetStateAutoFlag == 0)
        {
            nADVoltageState = pTmt->m_oPic200dPara.m_oSetting.ADVoltageState;
            nADCurrentState = pTmt->m_oPic200dPara.m_oSetting.ADCurrentState;
            if(StrModePara.PIC200DOUTStateFlag == MODE_250A)
            {
                nADCurrentState = 2;
            }
        }

        qDebug()<< "ADVoltageState ="<<nADVoltageState;
        SetVoltMeasGear(nADVoltageState);
    }
    else
    {
        StrModePara.PIC200DGetStateAutoFlag = 0;
    }


    /********************************************PIC200DSetting**************************************************/

    //	ADStart = 1;
    //		StrModePara.ADVoltageState = pTmt->m_oPic200dPara.m_oSetting.ADVoltageState;
    //	ADDCflag |= BIT3;
    //		StrModePara.ADVoltageState = pTmt->m_oPic200dPara.m_oSetting.ADVoltageState;
    //	DA1_FZ = 500;
    StrModePara.DA1_FZ = pTmt->m_oPic200dPara.m_oDA.DA1_FZ;
    //	DA1_Frequency = 200;
    StrModePara.DA1_Frequency = pTmt->m_oPic200dPara.m_oDA.DA1_Frequency;
    //	DA1_Phase = 0;
    StrModePara.DA1_Phase = pTmt->m_oPic200dPara.m_oDA.DA1_Phase;
    //	DA1_ACrisetime = 2;
    StrModePara.DA1_acrisetime = pTmt->m_oPic200dPara.m_oDA.DA1_ACrisetime;
    //	DA1_ACdowntime = 0.5;
    StrModePara.DA1_acdowntime = pTmt->m_oPic200dPara.m_oDA.DA1_ACdowntime;
    //	DA1_ACholdtime  = 30;
    StrModePara.DA1_acholdtime = pTmt->m_oPic200dPara.m_oDA.DA1_ACholdtime;
    StrModePara.AdjCloseLoopMode = pTmt->m_oPic200dPara.m_oDA.AdjCloseLoopMode;
    //	DA_bit8 = 0;
    //	AdjCloseLoopMode = 0;
    //		StrModePara.ADVoltageState = pTmt->m_oPic200dPara.m_oDA.ADVoltageState;
    /********************************************PIC200DValue**************************************************/
    float StrModePara_temp2;
    /********************************DA1********************************************/

    SENDAtoFPGA(BIT10,0x0051);
    SENDAtoFPGA(2,0x0500);

    if(StrModePara.PIC200DGetStateAutoFlag)
    {
        float fGearVal[2];
        //电流采集档位设置
        if(StrModePara.PIC200DOUTStateFlag == MODE_1A)//10A
        {
            fGearVal[0]=0.125;
            fGearVal[1]=1.25;
            if(StrModePara.DA1_FZ < fGearVal[0])
            {
                nADCurrentState=0;
            }
            else if((StrModePara.DA1_FZ>fGearVal[0]) && (StrModePara.DA1_FZ < fGearVal[1]))
            {
                nADCurrentState=1;
            }
            else
            {
                nADCurrentState=2;
            }
        }
        else//250A
        {
            nADCurrentState=2;
        }
    }

    if(bUseGear)
    {
        qDebug()<< "ADCurrentState ="<<nADCurrentState;
        SetCurrMeasGear(nADCurrentState);
    }

    //电流幅值设置
    if(StrModePara.PIC200DOUTStateFlag== MODE_1A)
    {
        float fGearVal=StrModePara.DA1_FZ;//预设置值
        PSTT_ADJUST_ITEM pAdjItem=NULL;
        if(pModule != NULL)
        {
            pAdjItem=stt_adj_find_adjust_item(g_theDeviceSystemParameter, pModule, 0, 0, 0,fGearVal);
        }

        if(pAdjItem!=NULL)
        {
            fCoef_Out_1A=pAdjItem->m_fCoef;
            fZero_Out_1A=pAdjItem->m_fZero;
        }
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("fCoef_Out_1A = %f ------ fZero_Out_1A = %f ------"), fCoef_Out_1A, fZero_Out_1A);
        /*******************************************************************************************************************************/

        StrModePara_temp2 = (StrModePara.DA1_FZ)*fCoef_Out_1A+fZero_Out_1A;

        if(StrModePara.DA1_FZ < (0.010 + 0.000001))
        {
            StrModePara_temp2 = StrModePara_temp2/2/0.012;
            StrModePara.PIC200DStatesendbuffer |= (BIT1+BIT2+BIT4+BIT5);
        }
        else
        {
            StrModePara_temp2 = StrModePara_temp2/2/2;
            StrModePara.PIC200DStatesendbuffer &= ~(BIT2);
            StrModePara.PIC200DStatesendbuffer |= (BIT1+BIT4+BIT5);
        }
    }
    else if(StrModePara.PIC200DOUTStateFlag== MODE_250A)
    {
        float fGearVal=StrModePara.DA1_FZ;
        PSTT_ADJUST_ITEM pAdjItem=NULL;
        if(pModule != NULL)
        {
            pAdjItem=stt_adj_find_adjust_item(g_theDeviceSystemParameter, pModule, 0, 1, 0, fGearVal);
        }

        if(pAdjItem!=NULL)
        {
            fCoef_Out_250A=pAdjItem->m_fCoef;
            fZero_Out_250A=pAdjItem->m_fZero;
        }
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("fCoef_Out_250A = %f ------ fZero_Out_250A = %f ------"), fCoef_Out_250A, fZero_Out_250A);

        StrModePara_temp2 = (StrModePara.DA1_FZ)*fCoef_Out_250A+fZero_Out_250A;
        if(StrModePara.DA1_FZ < (50 + 0.001))
        {
            StrModePara_temp2 = StrModePara_temp2/2/80;
            StrModePara.PIC200DStatesendbuffer |= BIT2+BIT4+BIT5;
            StrModePara.PIC200DStatesendbuffer &= ~(BIT1);
        }
        else if(StrModePara.DA1_FZ < (100 + 0.001))
        {
            StrModePara_temp2 = StrModePara_temp2/2/160;
            StrModePara.PIC200DStatesendbuffer |= BIT2+BIT5;
            StrModePara.PIC200DStatesendbuffer &= ~(BIT1+BIT4);
        }
        else// if(StrModePara.DA1_FZ>100)
        {
            StrModePara_temp2 = StrModePara_temp2/2/250;
            StrModePara.PIC200DStatesendbuffer |= BIT2;
            StrModePara.PIC200DStatesendbuffer &= ~(BIT1+BIT4+BIT5);
        }
    }

    StrModePara.AuotSetValue = StrModePara.DA1_FZ;
    StrModePara.PIC200DStatesendbuffer &= ~(BIT0+BIT3);
    SENDAtoFPGA(StrModePara.PIC200DStatesendbuffer,0x010d);

    //	SENDAtoFPGA(0,0x0112);
    //	SENDAtoFPGA(0,0x0113);

    StrModePara.DA1_acrisetime = 0.1;
    StrModePara.DA1_acdowntime = 0.1;
    ACbuffer.ACSendbuffer[0] = 0xffffff00;//bixu >65536
    ACbuffer.ACSendbuffer[1] = (quint32)(((StrModePara.DA1_acrisetime*1000*1000)/2.5)+1);
    ACbuffer.ACSendbuffer[2] = (((StrModePara_temp2)/(ACbuffer.ACSendbuffer[1]))*4294967296);

    ACbuffer.ACSendbuffer[3] = StrModePara_temp2*4294967296;//bixu >65536
    ACbuffer.ACSendbuffer[4] = (quint32)(((StrModePara.DA1_acdowntime*1000*1000)/2.5)+1);
    ACbuffer.ACSendbuffer[5] = (StrModePara_temp2/(ACbuffer.ACSendbuffer[4]))*4294967296;

    ACbuffer.ACSendbuffer[6] = (quint32)(StrModePara.DA1_acholdtime*1000);

    //sleep(10);
    SENDAtoFPGA(ACbuffer.ACSendbuffer[0],0x0300);
    SENDAtoFPGA(ACbuffer.ACSendbuffer[2],0x0301);
    SENDAtoFPGA(ACbuffer.ACSendbuffer[1],0x0302);
    SENDAtoFPGA(ACbuffer.ACSendbuffer[6],0x0303);
    SENDAtoFPGA(ACbuffer.ACSendbuffer[3],0x0304);


    SENDAtoFPGA(ACbuffer.ACSendbuffer[5],0x0305);
    SENDAtoFPGA(ACbuffer.ACSendbuffer[4],0x0306);
    SENDAtoFPGA(1,0x0002);
    ioctl(m_nCommfd,0x110,0);

    CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
    pSttTestBase->ReturnTestStateEvent_TestStart(0,0,FALSE);
    pSttTestBase->SetTestStarting(TRUE);

    ioctl(m_nCommfd, 0x103, 2);//开DMA中断消息
    //从pTmt取出上位机下发的参数
    //利用m_nCommfd给驱动下发参数,write(m_nCommfd,,)
}

void CSttDevicePIC200D::tmt_to_drv_pic200d(void *pVoidTmt)
{
    SetMeasDefault();
    tmt_Pic200dTest *pTmt=(tmt_Pic200dTest *)pVoidTmt;
    tmt_to_drv_pic200d(pTmt,TRUE);
}

void CSttDevicePIC200D::EventProcessEx()
{
    CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
    if(pSttTestBase != NULL)
    {
        if(pSttTestBase->GetTestStarting())
            return;
    }

    int inter_flag =ioctl(m_nCommfd,0x110,0);
    if(inter_flag==0)
        return;

    if(inter_flag&0x01 > 0)
    {
        CalculateDMA();
    }
}

void CSttDevicePIC200D::ProPic200dDrvResult(void *pVoidTmt)
{
    tmt_Pic200dTest *pTmt=(tmt_Pic200dTest *)pVoidTmt;
    int inter_flag =ioctl(m_nCommfd,0x110,0);
    if(inter_flag==0)
        return;

    //	qDebug()<<"----inter_flag-----"<<QString::number(inter_flag);
    if(inter_flag&0x01 > 0)
    {
        CalculateDMA();
    }

    if((inter_flag>>13)&0x01 > 0)
    {
        qDebug()<<"TEST Rise";
        SendDataToPCCount = 0;
        SendDataToPCCountFlag = 0;
    }

    if((inter_flag>>14)&0x01 > 0)
    {
        qDebug()<<"TEST Hold";
        SendDataToPCCount = 0;
        SendDataToPCCountFlag = 1;
    }

    if((inter_flag>>15)&0x01 > 0)
    {
        qDebug()<<"TEST Down";
    }

    if((inter_flag>>12)&0x01 > 0)
    {
        qDebug()<<"TEST stop";

        close_pic200d();
        {
            if(pTmt != NULL)
            {
                pTmt->m_oPic200dResult.m_fMeasU=vlue_AD1SnedData;
                pTmt->m_oPic200dResult.m_fMeasI=vlue_AD2SnedData;
                pTmt->m_oPic200dResult.m_fMeasR=vlue_RSnedData;
                pTmt->m_oPic200dResult.m_fTemp1=StrModePara.temp1;
                pTmt->m_oPic200dResult.m_fTemp2=StrModePara.temp2;
                pTmt->m_oPic200dResult.m_fTemp3=StrModePara.temp3;
                CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
                pSttTestBase->ReturnTestStateEvent_TestFinish(0,0,FALSE);
                ReturnTestEvents_MEAS();
            }
        }
    }

}

void CSttDevicePIC200D::close_pic200d()
{
    ioctl(m_nCommfd, 0x103, 3);//关DMA中断消息

    SENDAtoFPGA(0,0x0051);
    StrModePara.PIC200DStatesendbuffer |= 0x3f;
    StrModePara.PIC200DStatesendbuffer |= BIT0+BIT3;
    SENDAtoFPGA(StrModePara.PIC200DStatesendbuffer,0x010d);

    SENDAtoFPGA(0,0x0501);
    SENDAtoFPGA(0,0x0002);

    CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
    if(pSttTestBase==NULL)
        return;
    pSttTestBase->SetTestStarting(FALSE);
    ioctl(m_nCommfd,0x110,0);
}

void CSttDevicePIC200D::CalculateDMA()
{
    int AD_Count=0;
    int nLen = read(m_nCommfd,DMARes,200000);
    for(int i=0;i<200000;i++)//per 2000.
    {
        int DMAchannelflag1 = DMARes[i] >> 18;
        int DMAchannelflag2 = DMARes[i+1] >> 18;
        int DMAchannelflag3 = DMARes[i+2] >> 18;
        int DMAchannelflag4 = DMARes[i+3] >> 18;
        if((DMAchannelflag1 == 1) && (DMAchannelflag2 == 2) && (DMAchannelflag3 == 3) && (DMAchannelflag4 == 4))
        {
            int DMARestemp = DMARes[i] & 0x3FFFF;
            if(DMARestemp<=131071)
            {
                DMARestemp = DMARestemp;
            }
            else
            {
                DMARestemp = DMARestemp -262143;
            }
            ADtemp1[AD_Count] = (float)DMARestemp/131071.0;
            DMARestemp = DMARes[i+1] & 0x3FFFF;
            if(DMARestemp<=131071)
            {
                DMARestemp = DMARestemp;
            }
            else
            {
                DMARestemp = DMARestemp-262143;
            }
            ADtemp2[AD_Count] =(float)DMARestemp/131071.0;
            AD_Count++;
        }
    }

    float vlue_temp;
    float AD_TEMP2=0;
    for(int x =0;x<AD_Count;x++)
    {
        AD_TEMP2 += ADtemp1[x];
    }
    vlue_temp = AD_TEMP2/AD_Count;

    if(nADVoltageState==MeasVoltHG_5V)
    {
        vlue_temp = vlue_temp*5;
        vlue_AD1 = (vlue_temp)*fCoef_Gather_u[3]+fZero_Gather_u[3];
    }
    else if(nADVoltageState==MeasVoltHG_1V)
    {
        vlue_temp = vlue_temp*1;
        vlue_AD1 = (vlue_temp)*fCoef_Gather_u[2]+fZero_Gather_u[2];
    }
    else if(nADVoltageState==MeasVoltHG_200mV)
    {
        vlue_temp = vlue_temp*0.200;
        vlue_AD1 = (vlue_temp)*fCoef_Gather_u[1]+fZero_Gather_u[1];
    }
    else if(nADVoltageState==MeasVoltHG_10mV)
    {
        vlue_temp = vlue_temp*0.010;
        vlue_AD1 = (vlue_temp)*fCoef_Gather_u[0]+fZero_Gather_u[0];
    }

    pMeasModule_Volt->oChannels[0].oVector[0].fAmp = vlue_AD1;//V


    //	for(int j=0;j < AD_Count;j++)
    //	{
    //		fADTemp[j] = ADtemp2[0];
    //		for(int i =0;i < AD_Count;i++)
    //		{
    //			if(fADTemp[j] > ADtemp2[i])
    //			{
    //				fADTemp[j] = ADtemp2[i];
    //				break;
    //			}
    //		}
    //	}
    AD_TEMP2=0;
    for(int x =0;x<AD_Count;x++)
    {
        AD_TEMP2 += ADtemp2[x];
    }
    vlue_temp = AD_TEMP2/AD_Count;

    if(StrModePara.PIC200DOUTStateFlag==MODE_1A)
    {
        if(nADCurrentState==2)
        {
            vlue_temp = vlue_temp*20;
            vlue_AD2 = (vlue_temp)*fCoef_Gather_1A[2]+fZero_Gather_1A[2];
        }
        else if(nADCurrentState==1)
        {
            vlue_temp = vlue_temp*3.0;
            vlue_AD2 = (vlue_temp)*fCoef_Gather_1A[1]+fZero_Gather_1A[1];
        }
        else if(nADCurrentState==0)
        {
            vlue_temp = vlue_temp*0.1;
            vlue_AD2 = (vlue_temp)*fCoef_Gather_1A[0]+fZero_Gather_1A[0];
        }

        pMeasModule_Curr->oChannels[0].oVector[0].fAmp = vlue_AD2;
    }
    else
    {
        vlue_temp = vlue_temp*250;
        vlue_AD2 = (vlue_temp)*fCoef_Gather_250A[2]+fZero_Gather_250A[2];

        pMeasModule_Curr->oChannels[1].oVector[0].fAmp = vlue_AD2;
    }

    if(vlue_AD2 < EPSINON)
    {
        vlue_AD2 = 0;
        vlue_R = 1000000000;//以1000兆欧代表阻值无穷大
    }
    else
    {
        vlue_R = vlue_AD1*1000/vlue_AD2;//毫欧
        vlue_R = vlue_R*0.001;//欧
    }

    //	QString str=QString("%1").arg(vlue_AD1,0,'G',6); //保留四位有效数字，会进行四舍五入
    //	vlue_AD1 = str.toFloat();
    //	vlue_AD1 = vlue_AD1*1000;//V

    //	if(nADVoltageState==2)
    //	{
    //		str = QString::number(vlue_AD1, 'f', 4);
    //	}
    //	else
    //	{
    //		str = QString::number(vlue_AD1, 'f', 4);
    //	}
    //	vlue_AD1 = str.toFloat();
    //	str = QString::number(vlue_R, 'f', 3);
    //	vlue_R = str.toFloat();
    count_DMA = 0;

}

BOOL CSttDevicePIC200D::OnTimer(BOOL bExec)
{
    if(!bExec)
    {
        m_nDeviceOnTimerCount++;
        if(m_nDeviceOnTimerCount*m_nOnTimerMs < m_nDeviceOnTimerMs)
        {
            return FALSE;
        }
        m_nDeviceOnTimerCount=0;
    }

    if(SendDataToPCCountFlag)
    {
        SendDataToPCCount++;
    }

    if(SendDataToPCCount>=4)
    {
        SendDataToPCCountFlag = 0;
        SendDataToPCCount = 0;

        vlue_AD1SnedData = vlue_AD1;//ch1_ac_V
        vlue_AD2SnedData =vlue_AD2;//ch1_ac_I
        vlue_RSnedData =vlue_R;//ch1_ac_r
    }
    //	//系统秒定时器处理入口
    //	ReturnTestEvents_MEAS();
    return FALSE;
}

int CSttDevicePIC200D::SENDAtoFPGA(int VALUE,int ADDR)
{
    int VALUEtemp[1];
    VALUEtemp[0] = VALUE;
    write(m_nCommfd,VALUEtemp,ADDR);
    //    VALUE = chPara[0]+chPara[1]*256+chPara[2]*256*256;
    return VALUEtemp[0];
}

void CSttDevicePIC200D::Refresh_state(int State1Value)
{
    float CloseLoopFZtemp;
    int pis2krunstate = State1Value;
    float CloseLoopXS = 1;

    QString str;
    QByteArray ba;
    char send_buf[20];
    switch(pis2krunstate)//PIC200D状态，0:READY，1：RUN，2：rise，3：hold,4:down,5:stop,6:pass,7:fail.8:Remote.
    {
    //    case 5 ://CD A3 D6 B9
    //            SENDAtoFPGA(0,0x109);//stop RUN LED
    //        break;

    /*5A A5 13 82 0020 0002 0003 FFFF 0014 0064 004c 0028 FF00 //rise
          5A A5 09 82 0027 00b0 0028 FF00                          //hold
          5A A5 09 82 0029 00f0 0064 FF00*/                        //down
    case 2 ://C9 CF C9 FD
        //		str = "Rise";
        //		ba = str.toLatin1();
        //		strcpy(send_buf, ba.data());
        //		interface::g_interface->SendTxtToScreen(send_buf,0x2000,11);
        //		send_buf[0] = 0xF8;
        //		send_buf[1] = 0x00;
        //		interface::g_interface->SendTxtToScreen(send_buf,0x1003,8);//red FAIL

        break;
    case 3 ://B1 A3 B3 D6


        break;
    case 4 ://CF C2 BD B5
        break;
    case 5 ://CF C2 BD B5

        break;
    case 9 ://overload
        break;
    case 10 ://overheated
        break;
    default:
        break;
    }
}

void CSttDevicePIC200D::CloseLoop()
{
    float CloseLoopXS = 0;
    //CloseLoopFZtemp = (StrModePara.DA1_FZ-para_buf[1])*para_buf[2];
    /*闭环要做一些限制。条件
              1：满足保持阶段 5包DMA数据后开始
              2：满足是在闭环模式下
              3：系数如果大于1.5小于0.5不做校准
              4：系数如果满足1.005~0.995不做校准
              5：系数如果0.9~1.1，首先*0.9校准*/

    //qDebug()<<"--CloseLoopFZtemp"<<QString::number(((int)CloseLoopFZtemp/500+1));
    if((StrModePara.PIC200DStateFlag == 3) && (StrModePara.AdjCloseLoopMode == 0))
        //        if(0)
    {

        CloseLoopCount++;
        //            if((CloseLoopCount > (StrModePara.DA1_FZ/100+1)))
        if(CloseLoopCount >=2)
            //        if(StrModePara.AdjCloseLoopModeflag == 0)
        {
            CloseLoopCountNum++;
            CloseLoopCount = 0;
            CloseLoopXS = vlue_AD2 - StrModePara.DA1_FZ;
            //                    XStemp = vlue_AD2/StrModePara.DA1_FZ;

            //                    if(((CloseLoopXS>1.005) || (CloseLoopXS<0.995)) && (CloseLoopXS<1.5) && (CloseLoopXS>0.5))
            //                    if(((abs(CloseLoopXS))>0.03) && ((abs(CloseLoopXS))<5))

            CloseLoopXS = CloseLoopXS*0.9000;

            if((StrModePara.PIC200DOUTStateFlag== MODE_1A) && (((vlue_AD2/StrModePara.DA1_FZ)<0.999) || ((vlue_AD2/StrModePara.DA1_FZ)>1.001)))
            {
                if((CloseLoopXS<0.2) && (CloseLoopXS>-0.2))
                {
                    if(StrModePara.DA1_FZ<1.5)
                    {CloseLoopXS = CloseLoopXS*0.8000;}
                    //
                    StrModePara.AuotSetValue = StrModePara.AuotSetValue-CloseLoopXS;
                    CloseLoopXS = (StrModePara.AuotSetValue)*fCoef_Out_1A+fZero_Out_1A;
                    CloseLoopXS = -CloseLoopXS/2/20*4294967296;
                    int LoopXStemp = (int)(CloseLoopXS);
                    SENDAtoFPGA(LoopXStemp,0x030f);//SET AC
                    SENDAtoFPGA(0x40000000,0x030e);//SET AC
                    LoopXStemp = 0;
                }
            }
            else if((StrModePara.PIC200DOUTStateFlag== MODE_250A) && (((vlue_AD2/StrModePara.DA1_FZ)<0.999) || ((vlue_AD2/StrModePara.DA1_FZ)>1.001)))
            {
                if((StrModePara.DA1_FZ>=20) && (StrModePara.DA1_FZ<=50))
                {
                    if((CloseLoopXS<1.5) && (CloseLoopXS>-1.5))
                    {
                        StrModePara.AuotSetValue = StrModePara.AuotSetValue-CloseLoopXS;
                        CloseLoopXS = (StrModePara.AuotSetValue)*fCoef_Out_250A+fZero_Out_250A;
                        CloseLoopXS = -CloseLoopXS/2/80*4294967296;
                        int LoopXStemp = (int)(CloseLoopXS);
                        SENDAtoFPGA(LoopXStemp,0x030f);//SET AC
                        SENDAtoFPGA(0x40000000,0x030e);//SET AC
                        LoopXStemp = 0;
                    }
                }
                else if((StrModePara.DA1_FZ>50) && (StrModePara.DA1_FZ<=100))
                {
                    if((CloseLoopXS<2) && (CloseLoopXS>-2))
                    {
                        StrModePara.AuotSetValue = StrModePara.AuotSetValue-CloseLoopXS;
                        CloseLoopXS = (StrModePara.AuotSetValue)*fCoef_Out_250A+fZero_Out_250A;
                        CloseLoopXS = -CloseLoopXS/2/160*4294967296;
                        int LoopXStemp = (int)(CloseLoopXS);
                        SENDAtoFPGA(LoopXStemp,0x030f);//SET AC
                        SENDAtoFPGA(0x40000000,0x030e);//SET AC
                        LoopXStemp = 0;
                    }
                }
                else if(StrModePara.DA1_FZ>100)
                {
                    if((CloseLoopXS<4) && (CloseLoopXS>-4))
                    {
                        StrModePara.AuotSetValue = StrModePara.AuotSetValue-CloseLoopXS;
                        //                            qDebug()<<"--CloseLoopXS"<<QString::number(CloseLoopXS);
                        //                            qDebug()<<"--StrModePara.AuotSetValue"<<QString::number(StrModePara.AuotSetValue);
                        CloseLoopXS = (StrModePara.AuotSetValue)*fCoef_Out_250A+fZero_Out_250A;
                        CloseLoopXS = -CloseLoopXS/2/250*4294967296;
                        int LoopXStemp = (int)(CloseLoopXS);
                        //                            qDebug()<<"--CloseLoopXS--------"<<QString::number(CloseLoopXS);
                        SENDAtoFPGA(LoopXStemp,0x030f);//SET AC
                        SENDAtoFPGA(0x40000000,0x030e);//SET AC
                        LoopXStemp = 0;
                    }
                }
            }

        }
    }
    /*********************************close loop******************************************/
    /***********************************************************************************************************/
}

void CSttDevicePIC200D::AutoCurrentState()
{

    /***********************************AutoCurrentState****************************************************/

}

int CSttDevicePIC200D::Send_To_Fpga(char* pbuff,int nLen,int nMode)
{
    //    qDebug()<<"--buffer.Sendbuffer[0]------"<<QString::number(buffer.Sendbuffer[0]);
    //    qDebug()<<"---buffer.Sendbuffer[1]-----"<<QString::number(buffer.Sendbuffer[1]);
    //    qDebug()<<"---buffer.Sendbuffer[2]-----"<<QString::number(buffer.Sendbuffer[2]);
    //    qDebug()<<"---nMode-----"<<QString::number(nMode);
    //      qDebug()<<"-----------------"<<QString("Send_To_Fpga");
    ioctl(m_nCommfd,0x201,nMode);
    write(m_nCommfd,pbuff,nLen);
}

void CSttDevicePIC200D::SetTestStop(BOOL bIsSysDefaultOutput)
{
    close_pic200d();
}

void CSttDevicePIC200D::ReturnTestEvents_MEAS()
{
    CSttTestServerBase*pSttTestServerBase=CSttTestServerBase:: GetServerEngine();
    CSttXmlSerializeTool oSttXmlRegister;
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead( &pSttTestServerBase->m_oSttTestCmd);
    oSysState.SetRetType(SYS_STATE_RETTYPE_MEAS);
    oSysState.GetSttParas();
    oSttXmlRegister.CreateXmlSerializeRegister(&oSysState);
    CSttXmlSerializeBase *pParasRegister = oSttXmlRegister.GetParas();
    stt_xml_serialize_meas_datas(pParasRegister);
    char *pszPkgBuffer = NULL;
    long nLen = oSttXmlRegister.Stt_GetXml(&pszPkgBuffer, STT_PKG_HEAD_LEN);
    oSysState.m_nDataLen = nLen - STT_PKG_HEAD_LEN;
    oSysState.ProducePkgHead((BYTE*)pszPkgBuffer);
    pSttTestServerBase->SendBufferToChildren(NULL,(BYTE*)pszPkgBuffer,nLen);
}

void CSttDevicePIC200D::stt_xml_serialize_meas_datas(CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pSerializeGroup =pXmlSerialize->xml_serialize("DA", "DA", "channel", stt_ParaGroupKey());
    pSerializeGroup->xml_serialize("","V_AD1","","long", vlue_AD1SnedData);
    pSerializeGroup->xml_serialize("","V_AD2","","long", vlue_AD2SnedData);
    pSerializeGroup->xml_serialize("","V_R","","long", vlue_RSnedData);

    pSerializeGroup =pXmlSerialize->xml_serialize("temp", "temp", "channel", stt_ParaGroupKey());
    pSerializeGroup->xml_serialize("","temp1","","long", StrModePara.temp1);
    pSerializeGroup->xml_serialize("","temp2","","long", StrModePara.temp1);
    pSerializeGroup->xml_serialize("","temp3","","long", StrModePara.temp1);
}
