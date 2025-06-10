#include "SttDevicePIS2K.h"
#include "../../Engine/SttServerTestCtrlCntr.h"
#include "../../SttTest/Common/Adjust/SttAdjust_ModuleOutput.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>	//SIGIO
#include<sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "qthread.h"


CSttDevicePIS2K *CSttDevicePIS2K::g_pSttDevicePIS2K=NULL;
int DMARes[200000];
long CSttDevicePIS2K::g_nSttDeviceRef = 0;
float vlue_AD1;//ch1_ac_V
double vlue_AD2;//ch1_ac_I
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
#define PI 3.1415926
//#define DataLength 8192*4//250k  fhz
#define ADcou_Num 25000
#define count_DMA_Num 5
//float DMAtemp1[DataLength];
//float DMAtemp2[DataLength];
float ADtemp1[50000];
float ADtemp2[50000];
float fGearVal_V;
float fGearVal_I;
float fCoef_Gather_u[2];//电压采集幅值系数
float fZero_Gather_u[2];//电压采集零漂
float fCoef_Gather_i_500V[2];//电流采集幅值系数
float fZero_Gather_i_500V[2];//电流采集零漂
float fCoef_Gather_i_2500V[2];//电流采集幅值系数
float fZero_Gather_i_2500V[2];//电流采集零漂

float fCoef_Gather_i[2];//实际使用的电流采集幅值系数
float fZero_Gather_i[2];//实际使用的电流采集零漂

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

CSttDevicePIS2K::CSttDevicePIS2K()
{

}

void CSttDevicePIS2K::Create()
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
		g_pSttDevicePIS2K=new CSttDevicePIS2K;
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePIS2K;
	}
}

void CSttDevicePIS2K::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
		delete g_pSttDevicePIS2K;
		g_pSttDevicePIS2K = NULL;
	}
}

void CSttDevicePIS2K::InitCoef()
{
	fCoef_Gather_u[0] = 1;
	fZero_Gather_u[0] = 0;
	fCoef_Gather_u[1] = 1;
	fZero_Gather_u[1] = 0;
	/**************************电压采集部分**********************/
	//1-0-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
	float fGearVal_V = 500;
	PSTT_ADJUST_ITEM pMeasAdjItem=stt_adj_find_meas_u_item(fGearVal_V,1,0,0,0);  //该函数能根据输入参数，查找到的档位值

	if(pMeasAdjItem!=NULL)
	{
		fCoef_Gather_u[0]=pMeasAdjItem->m_fCoef;
		fZero_Gather_u[0]=pMeasAdjItem->m_fZero;
	}
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("------ fCoef_Gather_u[0] = %f ----- fZero_Gather_u[0] = %f ------"), fCoef_Gather_u[0], fZero_Gather_u[0]);

	fGearVal_V = 2500;
	pMeasAdjItem=stt_adj_find_meas_u_item(fGearVal_V,1,0,0,0);  //该函数能根据输入参数，查找到的档位值

	if(pMeasAdjItem!=NULL)
	{
		fCoef_Gather_u[1]=pMeasAdjItem->m_fCoef;
		fZero_Gather_u[1]=pMeasAdjItem->m_fZero;
	}
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("------ fCoef_Gather_u[1] = %f ----- fZero_Gather_u[1] = %f ------"), fCoef_Gather_u[1], fZero_Gather_u[1]);

    /***************************电流采集部分***********************/
    fCoef_Gather_i_500V[0]=1;//电流采集幅值系数
    fZero_Gather_i_500V[0]=0;//电流采集零漂

	fGearVal_I = 0.5;//mA
	//1-1-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
	pMeasAdjItem=stt_adj_find_meas_i_item(fGearVal_I,1,0,0,0);  //该函数能根据输入参数，查找到的档位值

	if(pMeasAdjItem!=NULL)
	{
        fCoef_Gather_i_500V[0]=pMeasAdjItem->m_fCoef;
        fZero_Gather_i_500V[0]=pMeasAdjItem->m_fZero;
	}
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("------ fCoef_Gather_i_500V[0] = %f ----- fZero_Gather_i_500V[0] = %f ------"), fCoef_Gather_i_500V[0], fZero_Gather_i_500V[0]);

    fCoef_Gather_i_500V[1]=1;//电流采集幅值系数
    fZero_Gather_i_500V[1]=0;//电流采集零漂

	fGearVal_I = 10;//mA
	//1-1-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
	pMeasAdjItem=stt_adj_find_meas_i_item(fGearVal_I,1,0,0,0);  //该函数能根据输入参数，查找到的档位值
	if(pMeasAdjItem!=NULL)
	{
        fCoef_Gather_i_500V[1]=pMeasAdjItem->m_fCoef;
        fZero_Gather_i_500V[1]=pMeasAdjItem->m_fZero;
	}

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("------ fCoef_Gather_i_500V[1] = %f ----- fZero_Gather_i_500V[1] = %f ------"), fCoef_Gather_i_500V[1], fZero_Gather_i_500V[1]);
    /***************************电流采集部分***********************/
    fCoef_Gather_i_2500V[0]=1;//电流采集幅值系数
    fZero_Gather_i_2500V[0]=0;//电流采集零漂

    fGearVal_I = 0.5;//mA
    //1-1-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
    pMeasAdjItem=stt_adj_find_meas_i_item(fGearVal_I,2,0,0,0);  //该函数能根据输入参数，查找到的档位值

    if(pMeasAdjItem!=NULL)
    {
        fCoef_Gather_i_2500V[0]=pMeasAdjItem->m_fCoef;
        fZero_Gather_i_2500V[0]=pMeasAdjItem->m_fZero;
    }
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("------ fCoef_Gather_i_2500V[0] = %f ----- fZero_Gather_i_2500V[0] = %f ------"), fCoef_Gather_i_2500V[0], fZero_Gather_i_2500V[0]);

    fCoef_Gather_i_2500V[1]=1;//电流采集幅值系数
    fZero_Gather_i_2500V[1]=0;//电流采集零漂

    fGearVal_I = 10;//mA
    //1-1-0-1:表示第一个模块（模块位置，第一个模块为1），第一个通道，第一个温区，基波
    pMeasAdjItem=stt_adj_find_meas_i_item(fGearVal_I,2,0,0,0);  //该函数能根据输入参数，查找到的档位值
    if(pMeasAdjItem!=NULL)
    {
        fCoef_Gather_i_2500V[1]=pMeasAdjItem->m_fCoef;
        fZero_Gather_i_2500V[1]=pMeasAdjItem->m_fZero;
    }

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("------ fCoef_Gather_i_2500V[1] = %f ----- fZero_Gather_i_2500V[1] = %f ------"), fCoef_Gather_i_2500V[1], fZero_Gather_i_2500V[1]);

}

void CSttDevicePIS2K::SetMeasDefault()
{
	nADCurrentState = 0;
	nADVoltageState = 0;
}

int CSttDevicePIS2K::InitDevice(BOOL bHasAdjFile)
{
    g_nNeedReportUTC = 0;
    g_nNeedReportRTDATA = 0;
    g_nNeedReportEvents = 0;
    g_nNeedReportDevExcept = 0;

	for(int i=0;i<g_theDeviceSystemParameter->m_nModuleCount;i++)
	{
		if(g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_DCVOLT)
		{
			pModule = &g_theDeviceSystemParameter->m_oModules[i];
			break;
		}
	}

	m_nCommfd=open("/dev/stt5000",O_RDWR);

	ioctl(m_nCommfd, 0x103, 1);//Start DMA
	//	qDebug()<<"m_nCommfd="<<QString::number(m_nCommfd);
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
			g_MeasDevice->oModules[i].nChanCount = 1;
			g_MeasDevice->oModules[i].oChannels[0].nHarmCount = 1;
			pMeasModule_Curr = &g_MeasDevice->oModules[i];
		}
	}

	StrModePara.PIS2KStateFlag =0;
	StrModePara.PIS2KStatesendbuffer = BIT5+BIT6;
	SENDAtoFPGA(0xAAAAA555,0x0052);
	SENDAtoFPGA(0,0x0051);
	SENDAtoFPGA(StrModePara.PIS2KStatesendbuffer,0x010B);
	return m_nCommfd;
}

void CSttDevicePIS2K::SetMeasModuleChanGear(int nModuleType,int nModulePos, int nChannel, int nGearId)
{
	SetMeasDefault();

	PSTT_MODULE pMeasModule = NULL;
	pMeasModule = stt_adj_find_module_byModulePos(g_theDeviceSystemParameter,nModulePos,nModuleType);
	if(pMeasModule != NULL)
	{
        if(pMeasModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_MEAS_CURRENT)
		{
			if(nGearId==0)//01
			{
				nADCurrentState = 0;
			}
			else
			{
				nADCurrentState = 1;
			}

            if(nModulePos == 1)
            {
                fCoef_Gather_i[0] = fCoef_Gather_i_500V[0];
                fCoef_Gather_i[1] = fCoef_Gather_i_500V[1];
                fZero_Gather_i[0] = fZero_Gather_i_500V[0];
                fZero_Gather_i[1] = fZero_Gather_i_500V[1];
            }
            else
            {
                fCoef_Gather_i[0] = fCoef_Gather_i_2500V[0];
                fCoef_Gather_i[1] = fCoef_Gather_i_2500V[1];
                fZero_Gather_i[0] = fZero_Gather_i_2500V[0];
                fZero_Gather_i[1] = fZero_Gather_i_2500V[1];
            }
		}
	}
}

void CSttDevicePIS2K::tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
{
	tmt_Pis2kTest oTmt_Pis2kTest;
	oTmt_Pis2kTest.m_oPis2kPara.init();
	oTmt_Pis2kTest.m_oPis2kPara.m_oDA.DA1_FZ=pTmt->m_oChannels[0].m_oVector.m_fMag;
	oTmt_Pis2kTest.m_oPis2kPara.m_oDA.DA1_ACrisetime=0.1f;
	oTmt_Pis2kTest.m_oPis2kPara.m_oDA.DA1_ACdowntime=1.0f;
	oTmt_Pis2kTest.m_oPis2kPara.m_oDA.DA1_ACmaxtime=999;

	tmt_to_drv_pis2k(&oTmt_Pis2kTest,FALSE);
}

void CSttDevicePIS2K::tmt_to_drv_pis2k(tmt_Pis2kTest *pTmt,BOOL bUseGear)
{
	InitCoef();
	SendDataToPCCount = 0;
	SendDataToPCCountFlag = 0;

	/********************************DA2********************************************/
	StrModePara.PIS2KStatesendbuffer &= ~(BIT4);//DA2
	SENDAtoFPGA(StrModePara.PIS2KStatesendbuffer,0x010B);
	usleep(50000);
	StrModePara.PIS2KStatesendbuffer &= ~(BIT6);//DA2
	SENDAtoFPGA(StrModePara.PIS2KStatesendbuffer,0x010B);
	SENDAtoFPGA(BIT8,0x0051);

	float StrModePara_temp2;
	StrModePara_temp2 = pTmt->m_oPis2kPara.m_oDA.DA1_FZ;
	if(StrModePara_temp2<=0)
	{
		StrModePara_temp2 = 0;
	}
	DCbuffer.DCSendbuffer[0] = (int)(((StrModePara_temp2-954.5)/(2500-954.5))*255);

	DCbuffer.DCSendbuffer[2] = 1;
	DCbuffer.DCSendbuffer[1] = 0;
	int sendbuff = DCbuffer.DCSendbuffer[0] << 8;
	SENDAtoFPGA(0,0x0600);
	SENDAtoFPGA(0,0x0601);
	SENDAtoFPGA(sendbuff,0x0120);
	usleep(50000);
	/*
	 * 校准系数文件中，建立三个模块：直流电压模块和两个采集模块；
	 * 其中，采集模块是虚拟模块，位置号与直流电压模块位置号一致；
	 * 1)直流电压模块：
	 * 硬件档位为2500V；
	 * 软件校准系数档位信息建立在   温区1, 通道1, 基波；
	 *2)电压采集模块：
	 * 温区1, 通道1, 基波，为电压采集的档位信息；
	 * 3)电流采集模块：
	 * 温区1, 通道1, 基波，为电流采集的档位信息；
	 * /

	/**********************电压输出部分***************************/
	//第一个0:表示第一个通道；第二个0:表示第一个模块
	//第三个参数：直流电压模块
	//返回值：硬件档位最大值
	float DAVaule = pTmt->m_oPis2kPara.m_oDA.DA1_FZ;
	StrModePara.DA1_FZ = DAVaule;
	float fVoltMax = 0;
	//这个函数会根据下发的幅值，查找合适的档位
	//参数0-0-0-1:表示第一个模块，第一个通道，第一个温区，基波
	PSTT_ADJUST_ITEM pAdjItem=NULL;
	if(pModule != NULL)
	{
		fVoltMax = stt_adj_get_ac_max_GearVal(0,pModule,0);
		pAdjItem=stt_adj_find_adjust_item(g_theDeviceSystemParameter, pModule, 0, 0, 0, DAVaule);
	}

	float fCoef_Out=1;//输出幅值系数
	float fZero_Out=0;//输出零漂
	if(pAdjItem!=NULL)
	{
		fCoef_Out=pAdjItem->m_fCoef;
		fZero_Out=pAdjItem->m_fZero;
	}
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("------ fVoltMax = %f ----- fCoef_Out = %f ------ fZero_Out = %f ------"), fVoltMax, fCoef_Out, fZero_Out);

	DAVaule = DAVaule *fCoef_Out + fZero_Out;

	if(StrModePara.PIS2KStateFlag != 0)
		return;

	/***********************************************Setting***************************************************/
	StrModePara.ADCurrentState = pTmt->m_oPis2kPara.m_oSetting.ADCurrentState;
	StrModePara.PIS2KGetStateAutoFlag = pTmt->m_oPis2kPara.m_oSetting.AutoADChangeState;
	if(bUseGear)
	{
		if(StrModePara.PIS2KGetStateAutoFlag == 0)
		{
			nADCurrentState = StrModePara.ADCurrentState;
		}

        //非校准输出
        if(pTmt->m_oPis2kPara.m_oSetting.CurrentMeasPos == 1)
        {
            fCoef_Gather_i[0] = fCoef_Gather_i_500V[0];
            fCoef_Gather_i[1] = fCoef_Gather_i_500V[1];
            fZero_Gather_i[0] = fZero_Gather_i_500V[0];
            fZero_Gather_i[1] = fZero_Gather_i_500V[1];
        }
        else
        {
            fCoef_Gather_i[0] = fCoef_Gather_i_2500V[0];
            fCoef_Gather_i[1] = fCoef_Gather_i_2500V[1];
            fZero_Gather_i[0] = fZero_Gather_i_2500V[0];
            fZero_Gather_i[1] = fZero_Gather_i_2500V[1];
        }
	}

	if(nADCurrentState == 0)
	{
		StrModePara.PIS2KStatesendbuffer |= BIT5;
	}
	else
	{
		StrModePara.PIS2KStatesendbuffer &= ~BIT5;
	}

	pTmt->m_oPis2kPara.m_oDA.ACDCflag = 1;//DCout,中广核项目只需要输出直流。故写死
	StrModePara.ACDCModeFlag = pTmt->m_oPis2kPara.m_oDA.ACDCflag;
	if(StrModePara.ACDCModeFlag == 0)//ACOUT
	{
		StrModePara.PIS2KStatesendbuffer &= ~BIT3;
	}
	else if(StrModePara.ACDCModeFlag == 1)//DCOUT
	{
		StrModePara.PIS2KStatesendbuffer |= BIT3;
	}

	SENDAtoFPGA(StrModePara.PIS2KStatesendbuffer,0x010B);

	StrModePara.VoltageAlarmMin=pTmt->m_oPis2kPara.m_oSetting.VoltageAlarmMin;//da1频率
	StrModePara.VoltageAlarmMax=pTmt->m_oPis2kPara.m_oSetting.VoltageAlarmMax;//da1频率
	StrModePara.CurrentAlarmMin=pTmt->m_oPis2kPara.m_oSetting.CurrentAlarmMin;//da1频率
	StrModePara.CurrentAlarmMax=pTmt->m_oPis2kPara.m_oSetting.CurrentAlarmMax;//da1频率
	/***********************************************Setting***************************************************/
	/***********************************************StartTest***************************************************/

	StrModePara.DA1_Frequency=pTmt->m_oPis2kPara.m_oDA.DA1_Frequency;//da1频率
	StrModePara.DA1_Phase=pTmt->m_oPis2kPara.m_oDA.DA1_Phase;//da1相位
	StrModePara.DA1_acrisetime=pTmt->m_oPis2kPara.m_oDA.DA1_ACrisetime;
	StrModePara.DA1_acholdtime=pTmt->m_oPis2kPara.m_oDA.DA1_ACmaxtime;
	StrModePara.DA1_acdowntime=pTmt->m_oPis2kPara.m_oDA.DA1_ACdowntime;
	//	StrModePara.DA1_Frequency = 200;
	//    float ACtemp;
	float StrModePara_temp1;

	//			msleep(50);
	/********************************DA1********************************************/

	if(StrModePara.DA1_acrisetime<=0)
	{
		StrModePara.DA1_acrisetime = 0.02;
	}
	if(StrModePara.DA1_acdowntime<=0)
	{
		StrModePara.DA1_acdowntime = 0.02;
	}
	if(StrModePara.DA1_Frequency>50)
	{
		StrModePara.DA1_Frequency = 400;
	}
	if(StrModePara.DA1_Frequency<50)
	{
		StrModePara.DA1_Frequency = 50;
	}
	if(StrModePara.DA1_FZ>2500)
	{
		StrModePara.DA1_FZ = 2500;
	}
	StrModePara.DA1_Frequency=50;
	StrModePara_temp1 = 0;
	StrModePara_temp1 = StrModePara.DA1_Frequency/(50*8000)*(4294967296-1);
	SENDAtoFPGA(StrModePara_temp1,0x0112);
	StrModePara_temp1 = StrModePara.DA1_Phase/(360)*(4294967296-1);
	StrModePara_temp1 = 0;
	SENDAtoFPGA(StrModePara_temp1,0x0113);
	StrModePara_temp2 = DAVaule/360/7.07;

	ACbuffer.ACSendbuffer[0] = 65536;//bixu >65536
	ACbuffer.ACSendbuffer[1] = (quint32)(1);
	ACbuffer.ACSendbuffer[2] = (quint32)(((StrModePara_temp2)/((StrModePara.DA1_acrisetime*1000)/(ACbuffer.ACSendbuffer[1]*(1000/StrModePara.DA1_Frequency))))*4294967296);
	ACbuffer.ACSendbuffer[3] = (quint32)(((StrModePara.DA1_acrisetime*1000)/(ACbuffer.ACSendbuffer[1]*(1000/StrModePara.DA1_Frequency))));

	ACbuffer.ACSendbuffer[4] = StrModePara_temp2*4294967296;//bixu >65536
	ACbuffer.ACSendbuffer[5] = (quint32)(1);
	ACbuffer.ACSendbuffer[6] = (quint32)(((StrModePara_temp2)/((StrModePara.DA1_acdowntime*1000)/(ACbuffer.ACSendbuffer[1]*(1000/StrModePara.DA1_Frequency))))*4294967296);
	ACbuffer.ACSendbuffer[7] = (quint32)(((StrModePara.DA1_acdowntime*1000)/(ACbuffer.ACSendbuffer[1]*(1000/StrModePara.DA1_Frequency))));

	ACbuffer.ACSendbuffer[8] = (quint32)(StrModePara.DA1_acholdtime*1000);
	//        ACbuffer.ACSendbuffer[11] = (quint32)((StrModePara.VoltageAlarmMin/2800)*131071);
	//        ACbuffer.ACSendbuffer[12] = (quint32)((StrModePara.VoltageAlarmMax/2800)*131071);
	ACbuffer.ACSendbuffer[9] = (quint32)((StrModePara.DA1_FZ*0.5/2800)*131071);
	ACbuffer.ACSendbuffer[10] = (quint32)((StrModePara.DA1_FZ*1.5/2800)*131071);
	ACbuffer.ACSendbuffer[11] = (quint32)((StrModePara.CurrentAlarmMin/10)*131071);
	ACbuffer.ACSendbuffer[12] = (quint32)((StrModePara.CurrentAlarmMax/10)*131071);
	float Frequencytemp1 = StrModePara.DA1_Frequency;
	Frequencytemp1 = (Frequencytemp1/(50*8000))*4294967295;
	quint32 Frequencytemp = Frequencytemp1;
	SENDAtoFPGA(Frequencytemp,0x0112);
	SENDAtoFPGA(1,0x0501);
	SENDAtoFPGA(5,0x0500);
	SENDAtoFPGA(ACbuffer.ACSendbuffer[0],0x0300);
	SENDAtoFPGA(ACbuffer.ACSendbuffer[1],0x0301);
	SENDAtoFPGA(ACbuffer.ACSendbuffer[2],0x0302);
	SENDAtoFPGA(ACbuffer.ACSendbuffer[3],0x0303);

	SENDAtoFPGA(ACbuffer.ACSendbuffer[8],0x0304);

	SENDAtoFPGA(ACbuffer.ACSendbuffer[4],0x0305);
	SENDAtoFPGA(ACbuffer.ACSendbuffer[5],0x0306);
	SENDAtoFPGA(ACbuffer.ACSendbuffer[6],0x0307);
	SENDAtoFPGA(ACbuffer.ACSendbuffer[7],0x0308);
	SENDAtoFPGA(1,0x0002);
	ioctl(m_nCommfd,0x110,0);

	CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
	pSttTestBase->ReturnTestStateEvent_TestStart(0,0,FALSE);
	pSttTestBase->SetTestStarting(TRUE);
	ioctl(m_nCommfd, 0x103, 2);//开DMA中断消息

	StrModePara.PIS2KStateFlag =1;
}

void CSttDevicePIS2K::tmt_to_drv_pis2k(void *pVoidTmt)
{
	SetMeasDefault();
	tmt_Pis2kTest *pTmt=(tmt_Pis2kTest *)pVoidTmt;
	tmt_to_drv_pis2k(pTmt,TRUE);
}

void CSttDevicePIS2K::EventProcessEx()
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
        CalculateDMA(NULL);
	}
}

void CSttDevicePIS2K::ProPis2kDrvResult(void *pVoidTmt)
{
	tmt_Pis2kTest *pTmt=(tmt_Pis2kTest *)pVoidTmt;
	int AlarmTemp;
	int inter_flag =ioctl(m_nCommfd,0x110,0);

	if(inter_flag==0)
		return;

	if(inter_flag&0x01 > 0)
	{
        CalculateDMA(pVoidTmt);
	}

	if((inter_flag>>11)&0x01 > 0)
	{
		//PIS2K?????? StrModePara.PIS2KStateFlag ???0:READY???1???RUN???2???PASS???3???FAIL,
		//4:Remote,5:RUN-Ready,6:Rise,7:Hold,8:Down,9:guo re,10:overload,11:stop
		AlarmTemp =   SENDAtoFPGA(0x0209,22);
		qDebug()<<"-----AlarmTemp-----"<<QString::number(StrModePara.PIS2KStateFlag);
		if((StrModePara.PIS2KStateFlag ==6) && (StrModePara.PIS2KStateFlag ==7))
		{
			if((AlarmTemp &= BIT1) == BIT1) //overheated  1 YOUXIAO  0bian1
			{
				StrModePara.PIS2KStateFlag = 9;
				Refresh_state(StrModePara.PIS2KStateFlag);
			}
			else if((AlarmTemp &= BIT0) == 0)//overload 0 YOUXIAO 1bian3
			{
				StrModePara.PIS2KStateFlag = 10;
				Refresh_state(StrModePara.PIS2KStateFlag);
			}
		}
	}
	if((inter_flag>>13)&0x01 > 0)
	{
		//TEST rise
		StrModePara.PIS2KStateFlag = 6;
		SENDAtoFPGA(InitXS,0x030e);//SET AC
		//		Refresh_state(StrModePara.PIS2KStateFlag);
	}
	if((inter_flag>>14)&0x01 > 0)
	{
		//TEST hold
		StrModePara.PIS2KStateFlag = 7;
		SendDataToPCCountFlag = 1;
		//		Refresh_state(StrModePara.PIS2KStateFlag);
	}
	if((inter_flag>>15)&0x01 > 0)
	{
		//TEST down
		StrModePara.PIS2KStateFlag = 8;
		SENDAtoFPGA(InitXS,0x030e);//SET AC
		//		Refresh_state(StrModePara.PIS2KStateFlag);
		//        StrModePara.PIS2KStateFlag = 11;
	}

	if((inter_flag>>12)&0x01 > 0)
	{
		//TEST stop
		SENDAtoFPGA(0,0x109);//stop RUN LED
		StrModePara.PIS2KStateFlag = 0;

		//		Refresh_state(StrModePara.PIS2KStateFlag);

		close_pis2k();
		{
			//		 qDebug()<<"--------vlue_AD1SnedData------------"<<vlue_AD1SnedData;
			//		 qDebug()<<"--------vlue_AD2SnedData------------"<<vlue_AD2SnedData;
			//		 qDebug()<<"--------vlue_RSnedData------------"<<vlue_RSnedData;
            if(pTmt != NULL)
            {
                pTmt->m_oPis2kResult.m_fMeasU=vlue_AD1SnedData;
                pTmt->m_oPis2kResult.m_fMeasI=vlue_AD2SnedData;
                pTmt->m_oPis2kResult.m_fMeasR=vlue_RSnedData;
                pTmt->m_oPis2kResult.m_fTemp1=StrModePara.temp1;
                pTmt->m_oPis2kResult.m_fTemp2=StrModePara.temp2;
                pTmt->m_oPis2kResult.m_fTemp3=StrModePara.temp3;
                CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
                pSttTestBase->ReturnTestStateEvent_TestFinish(0,0,FALSE);
            }
		}
		qDebug()<<"###############TestFinish###############";
	}
}

void CSttDevicePIS2K::close_pis2k()
{
	ioctl(m_nCommfd, 0x103, 3);//关DMA中断消息

	//	qDebug()<<"close_pis2k = ";
	//	if((StrModePara.PIS2KStateFlag !=11) ||(StrModePara.PIS2KStateFlag !=0))
	//	if((StrModePara.PIS2KStateFlag !=0))
	//	{
	StrModePara.PIS2KStateFlag =0;
	qDebug()<<"close_pis2k = 1111111";
	StrModePara.PIS2KStatesendbuffer |= BIT4+BIT6;
	SENDAtoFPGA(StrModePara.PIS2KStatesendbuffer,0x010B);

	SENDAtoFPGA(0,0x0051);
	//		StrModePara.PIS2KStateFlag = 1;
	Refresh_state(StrModePara.PIS2KStateFlag );
	// SENDAtoFPGA(0,0x0501);
	SENDAtoFPGA(0,0x0002);

	CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
	if(pSttTestBase==NULL)
		return;
	pSttTestBase->SetTestStarting(FALSE);
	ioctl(m_nCommfd,0x110,0);

}

void CSttDevicePIS2K::CalculateDMA(void *pVoidTmt)
{
	int AD_Count=0;
	float ADtemp1[200000];
	float ADtemp2[200000];
	float fDMA;

	int nLen = read(m_nCommfd,DMARes,200000);
	for(int i=0;i<200000;i++)//per 2000.
	{
		quint32 DMAchannelflag1 = DMARes[i] >> 18;
		quint32 DMAchannelflag2 = DMARes[i+1] >> 18;
		quint32 DMAchannelflag3 = DMARes[i+2] >> 18;
		quint32 DMAchannelflag4 = DMARes[i+3] >> 18;
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
			fDMA = DMARestemp;
			ADtemp1[AD_Count] = fDMA/131071.0;
			DMARestemp = DMARes[i+1] & 0x3FFFF;
			if(DMARestemp<=131071)
			{
				DMARestemp = DMARestemp;
			}
			else
			{
				DMARestemp = DMARestemp-262143;
			}
			fDMA = DMARestemp;
			ADtemp2[AD_Count] =fDMA/131071.0;
			AD_Count++;
		}
	}

	float vlue_temp;
	float AD_TEMP2=0;
	for(int x =0;x<AD_Count;x++)
	{
		AD_TEMP2 = ADtemp1[x]+AD_TEMP2;
	}
	vlue_temp = AD_TEMP2/AD_Count;
//	float fADTemp[200000];
//	int nCount = AD_Count/8;
//	for(int j=0;j < AD_Count;j++)
//	{
//		fADTemp[j] = ADtemp1[0];
//		for(int i =0;i < AD_Count;i++)
//		{
//			if(fADTemp[j] > ADtemp1[i])
//			{
//				fADTemp[j] = ADtemp1[i];
//				break;
//			}
//		}
//	}

//	float vlue_temp;
//	float AD_TEMP2=0;
//	for(int x =nCount*2;x<AD_Count-nCount*2;x++)
//	{
//		AD_TEMP2 += fADTemp[x];
//	}
//	vlue_temp = AD_TEMP2/(nCount*4);


    qDebug()<<"V AD_TEMP2 ="<<AD_TEMP2;
    qDebug()<<"V AD_Count ="<<AD_Count;
    qDebug()<<"V vlue_temp ="<<vlue_temp;
	vlue_temp = (vlue_temp)*10*260;
	if(StrModePara.DA1_FZ < 500.001)
	{
		vlue_temp = vlue_temp *fCoef_Gather_u[0] + fZero_Gather_u[0];
	}
	else
	{
		vlue_temp = vlue_temp *fCoef_Gather_u[1] + fZero_Gather_u[1];
	}	
	vlue_AD1 = vlue_temp;//V
	pMeasModule_Volt->oChannels[0].oVector[0].fAmp = vlue_AD1;//V

	AD_TEMP2 = 0;
	for(int x =0;x<AD_Count;x++)
	{
		AD_TEMP2 = ADtemp2[x]+AD_TEMP2;
	}

//	AD_TEMP2 = 0;
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
//	AD_TEMP2=0;
//	for(int x =nCount*2;x<AD_Count-nCount*2;x++)
//	{
//		AD_TEMP2 += fADTemp[x];
//	}
//	vlue_temp = AD_TEMP2/(nCount*4);

	vlue_temp = AD_TEMP2/AD_Count;
    qDebug()<<"I AD_TEMP2 ="<<AD_TEMP2;
    qDebug()<<"I AD_Count ="<<AD_Count;
    qDebug()<<"I vlue_temp ="<<vlue_temp;
    qDebug()<<"I nADCurrentState ="<<nADCurrentState;

	if(nADCurrentState == 0)
    {
        vlue_AD2 = (vlue_temp)*511.77;
        vlue_AD2 = vlue_AD2*fCoef_Gather_i[0]+fZero_Gather_i[0];
	}
	else
    {
        vlue_AD2 = (vlue_temp)*10*1000;
        vlue_AD2 = vlue_AD2*fCoef_Gather_i[1]+fZero_Gather_i[1];
	}

    vlue_AD2 = vlue_AD2*0.000001;//A
	pMeasModule_Curr->oChannels[0].oVector[0].fAmp = vlue_AD2;

    vlue_R = vlue_AD1/vlue_AD2;//欧
	count_DMA = 0;

    if(vlue_temp > 0.9)
    {
        qDebug()<<"############### Warning MeasI ###############";
        SENDAtoFPGA(0,0x109);//stop RUN LED
        StrModePara.PIS2KStateFlag = 0;

        close_pis2k();
        {
            if(pVoidTmt != NULL)
            {
                tmt_Pis2kTest *pTmt=(tmt_Pis2kTest *)pVoidTmt;
                pTmt->m_oPis2kResult.m_fMeasU=vlue_AD1;
                pTmt->m_oPis2kResult.m_fMeasI=vlue_AD2;
                pTmt->m_oPis2kResult.m_fMeasR=vlue_R;
                pTmt->m_oPis2kResult.m_fTemp1=StrModePara.temp1;
                pTmt->m_oPis2kResult.m_fTemp2=StrModePara.temp2;
                pTmt->m_oPis2kResult.m_fTemp3=StrModePara.temp3;
                CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
                pSttTestBase->ReturnTestStateEvent_TestFinish(0,0,FALSE);
            }
        }
        qDebug()<<"###############TestFinish###############";
    }
}

#include "../../Engine/SttTestServerBase.h"

void CSttDevicePIS2K::stt_xml_serialize_meas_datas(CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pSerializeGroup =pXmlSerialize->xml_serialize("DA", "DA", "channel", stt_ParaGroupKey());
	pSerializeGroup->xml_serialize("","V_AD1","","long", vlue_AD1);
	pSerializeGroup->xml_serialize("","V_AD2","","long", vlue_AD2);
	pSerializeGroup->xml_serialize("","V_R","","long", vlue_R);

	pSerializeGroup =pXmlSerialize->xml_serialize("temp", "temp", "channel", stt_ParaGroupKey());
	pSerializeGroup->xml_serialize("","temp1","","long", StrModePara.temp1);
	pSerializeGroup->xml_serialize("","temp2","","long", StrModePara.temp2);
	pSerializeGroup->xml_serialize("","temp3","","long", StrModePara.temp3);
}

BOOL CSttDevicePIS2K::OnTimer(BOOL bExec)
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
		//		 qDebug()<<"--------SendDataToPCCount------------";
		SendDataToPCCount = 0;
		vlue_AD1SnedData = vlue_AD1;//ch1_ac_V
		vlue_AD2SnedData =vlue_AD2;//ch1_ac_I
		vlue_RSnedData =vlue_R;//ch1_ac_r
	}
//	ReturnTestEvents_MEAS();
	//	//系统秒定时器处理入口
	return FALSE;
}

void CSttDevicePIS2K::ReturnTestEvents_MEAS()
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

int CSttDevicePIS2K::SENDAtoFPGA(int VALUE,int ADDR)
{
	int VALUEtemp[1];
	VALUEtemp[0] = VALUE;
	write(m_nCommfd,VALUEtemp,ADDR);
	//    VALUE = chPara[0]+chPara[1]*256+chPara[2]*256*256;
	return VALUEtemp[0];

	//    usleep(500);
}

void CSttDevicePIS2K::Refresh_state(int State1Value)
{
	int pis2krunstate = State1Value;
	QString str;
	QByteArray ba;
	char send_buf[20];
	switch(pis2krunstate)//PIS2K状态 StrModePara.PIS2KStateFlag ，0:READY，1：RUN，2：PASS，3：FAIL,
		//4:Remote,5:RUN-Ready,6:Rise,7:Hold,8:Down,9:guo re,10:overload,11:stop
	{
	case 0 ://C9 CF C9 FD



		break;
	case 4 ://C9 CF C9 FD



		break;

		/*5A A5 13 82 0020 0002 0003 FFFF 0014 0064 004c 0028 FF00 //rise
		  5A A5 09 82 0027 00b0 0028 FF00                          //hold
		  5A A5 09 82 0029 00f0 0064 FF00*/                        //down
	case 6 ://C9 CF C9 FD
		//		str = "Rise";
		//		ba = str.toLatin1();
		//		strcpy(send_buf, ba.data());
		//		interface::g_interface->SendTxtToScreen(send_buf,0x2000,11);
		//		send_buf[0] = 0xF8;
		//		send_buf[1] = 0x00;
		//		interface::g_interface->SendTxtToScreen(send_buf,0x1003,8);//red FAIL

		break;
	case 7 ://B1 A3 B3 D6

		//		str = "Hold";
		//		ba = str.toLatin1();
		//		strcpy(send_buf, ba.data());
		//		interface::g_interface->SendTxtToScreen(send_buf,0x2000,11);
		//		send_buf[0] = 0xF8;
		//		send_buf[1] = 0x00;
		//		interface::g_interface->SendTxtToScreen(send_buf,0x1003,8);//red FAIL
		break;
	case 8 ://CF C2 BD B5
		//		str = "Down";
		//		ba = str.toLatin1();
		//		strcpy(send_buf, ba.data());
		//		interface::g_interface->SendTxtToScreen(send_buf,0x2000,11);
		//		send_buf[0] = 0xcf;
		//		send_buf[1] = 0xd7;
		//		interface::g_interface->SendTxtToScreen(send_buf,0x1003,8);//red FAIL

		// qDebug()<<"--StrModePara.Qualified_resistance-----------"<<QString::number(StrModePara.Qualified_resistance);



		//       if(StrModePara.PIS2KStateFlag==0)
		//       {
		//           str = "RETURN";
		//          ba = str.toLatin1();
		//          strcpy(send_buf, ba.data());
		//          interface::g_interface->SendTxtToScreen(send_buf,0x6A00,11);
		//          send_buf[0] = 0x2A;
		//          send_buf[1] = 0x4A;
		//          interface::g_interface->SendTxtToScreen(send_buf,0x6b53,8);//red FAIL


		//}

		// pis2kdaout::g_pis2kdaout->close_pis2k();
		break;
	case 9 ://overheated
		//		qDebug()<<"-----overheated-----";
		//		StrModePara.PIS2KStatesendbuffer |= BIT4+BIT6;
		//		 SENDAtoFPGA(StrModePara.PIS2KStatesendbuffer,0x010B);
		//		 SENDAtoFPGA(BIT11,0x0051);
		break;
	case 10 ://overload
		qDebug()<<"-----overload-----";

		//		if(pis2kinitflag == 1)
		//		{
		//			StrModePara.PIS2KStatesendbuffer |= BIT4+BIT6;
		//			 SENDAtoFPGA(StrModePara.PIS2KStatesendbuffer,0x010B);
		//			 SENDAtoFPGA(BIT11,0x0051);
		//		}

		//		if(pis2kinitflag == 2)
		//		{
		//			pis2kinitflag = 1;
		//		}
		break;
	case 11 ://CD A3 D6 B9
		SENDAtoFPGA(0,0x0002);

		//		str = "Stop";
		//		ba = str.toLatin1();
		//		strcpy(send_buf, ba.data());
		//		interface::g_interface->SendTxtToScreen(send_buf,0x2000,11);
		//		send_buf[0] = 0xcf;
		//		send_buf[1] = 0xd7;
		//		interface::g_interface->SendTxtToScreen(send_buf,0x1003,8);//red FAIL

		if(StrModePara.WorkModeFlag==0)
		{
			//            qDebug()<<"--vlue_R-----------"<<QString::number(vlue_R);
			//            qDebug()<<"--StrModePara.Qualified_resistance-----------"<<QString::number(StrModePara.Qualified_resistance);
			if(vlue_R<StrModePara.Qualified_resistance)
			{//pass50 41 53 53 20  ;
				////                StrModePara.PIS2KStateFlag = 2;
				//				str = "Pass";
				//				ba = str.toLatin1();
				//				strcpy(send_buf, ba.data());
				//				//           send_buf[0] = 0x50;
				//				//           send_buf[1] = 0x41;
				//				//           send_buf[2] = 0x53;
				//				//           send_buf[3] = 0x53;
				//				//           send_buf[4] = 0x20;
				//				interface::g_interface->SendTxtToScreen(send_buf,0x2000,11);
				//				send_buf[0] = 0xcf;
				//				send_buf[1] = 0xd7;
				//				interface::g_interface->SendTxtToScreen(send_buf,0x1003,8);//red FAIL
			}
			else if(vlue_R>StrModePara.Qualified_resistance)
			{//FAIL46 41 49 4C 20
				////                StrModePara.PIS2KStateFlag = 3;
				//				str = "Fail";
				//				ba = str.toLatin1();
				//				strcpy(send_buf, ba.data());
				//				//           send_buf[0] = 0x46;
				//				//           send_buf[1] = 0x41;
				//				//           send_buf[2] = 0x49;
				//				//           send_buf[3] = 0x4c;
				//				//           send_buf[4] = 0x20;
				//				interface::g_interface->SendTxtToScreen(send_buf,0x2000,11);
				//				send_buf[0] = 0xf8;
				//				send_buf[1] = 0x00;
				//				interface::g_interface->SendTxtToScreen(send_buf,0x1003,8);//red FAIL
				//				 SENDAtoFPGA(BIT10,0x0051);
			}
		}
		else
		{
			if(vlue_AD2<StrModePara.Leakage_Current)
			{//pass50 41 53 53 20  ;
				////                StrModePara.PIS2KStateFlag = 2;
				//				str = "Pass";
				//				ba = str.toLatin1();
				//				strcpy(send_buf, ba.data());
				//				//           send_buf[0] = 0x50;
				//				//           send_buf[1] = 0x41;
				//				//           send_buf[2] = 0x53;
				//				//           send_buf[3] = 0x53;
				//				//           send_buf[4] = 0x20;
				//				interface::g_interface->SendTxtToScreen(send_buf,0x2000,11);
				//				send_buf[0] = 0xcf;
				//				send_buf[1] = 0xd7;
				//				interface::g_interface->SendTxtToScreen(send_buf,0x1003,8);//red FAIL
				//				 SENDAtoFPGA(BIT9,0x0051);
			}
			else if(vlue_R>=StrModePara.Leakage_Current)
			{//FAIL46 41 49 4C 20
				////                StrModePara.PIS2KStateFlag = 3;
				//				str = "Fail";
				//				ba = str.toLatin1();
				//				strcpy(send_buf, ba.data());
				//				//           send_buf[0] = 0x46;
				//				//           send_buf[1] = 0x41;
				//				//           send_buf[2] = 0x49;
				//				//           send_buf[3] = 0x4c;
				//				//           send_buf[4] = 0x20;
				//				interface::g_interface->SendTxtToScreen(send_buf,0x2000,11);
				//				send_buf[0] = 0xf8;
				//				send_buf[1] = 0x00;
				//				interface::g_interface->SendTxtToScreen(send_buf,0x1003,8);//red FAIL
			}
		}

		if(StrModePara.LocalRemoteFlag == 0)
		{
			//			str = "DIS-CHAN";
			//			ba = str.toLatin1();
			//			strcpy(send_buf, ba.data());
			//			interface::g_interface->SendTxtToScreen(send_buf,0x6900,11);
			//			send_buf[0] = 0x04;
			//			send_buf[1] = 0x18;
			//			interface::g_interface->SendTxtToScreen(send_buf,0x6953,8);//red FAIL
		}

		//             SENDAtoFPGA(0,0x109);//stop RUN LED
		//        if(StrModePara.LocalRemoteFlag == 1)
		//        {StrModePara.PIS2KStateFlag = 0;}
		break;
	default:
		break;
	}
}

void CSttDevicePIS2K::CloseLoop()
{
	/***********************************CloseLoop****************************************************/
	//CloseLoopFZtemp = (StrModePara.DA1_FZ-para_buf[1])*para_buf[2];
	/*闭环要做一些限制。条件
  1：满足保持阶段 5包DMA数据后开始
  2：满足是在闭环模式下
  3：系数如果大于1.5小于0.5不做校准
  4：系数如果满足1.005~0.995不做校准
  5：系数如果0.9~1.1，首先*0.9校准*/
	//	qDebug()<<"--StrModePara.PIS2KStateFlag"<<StrModePara.PIS2KStateFlag;
	if(StrModePara.PIS2KStateFlag == 7)
	{
		float CloseLoopXS = 1;
		if(StrModePara.AdjCloseLoopModeflag == 0)
		{
			//			qDebug()<<"--CloseLoopCount"<<QString::number(CloseLoopCount);
			CloseLoopCount++;
			//            if((CloseLoopCount > (StrModePara.DA1_FZ/100+1)))
			if(CloseLoopCount > 4)
				//        if(StrModePara.AdjCloseLoopModeflag == 0)
			{
				/*********************************close loop******************************************/
				// qDebug()<<"--CloseLoopCount"<<QString::number(CloseLoopCount);
				CloseLoopCount = 0;

				//CloseLoopFZtemp = (CloseLoopFZtemp-vlue_AD1)*0.9+CloseLoopFZtemp;
				CloseLoopXS = StrModePara.DA1_FZ/vlue_AD1;
				//				qDebug()<<"--StrModePara.DA1_FZ"<<QString::number(StrModePara.DA1_FZ);
				//				qDebug()<<"--vlue_AD1"<<QString::number(vlue_AD1);
				if(((CloseLoopXS>1.005) || (CloseLoopXS<0.995)) && (CloseLoopXS<1.3) && (CloseLoopXS>0.5))
				{
					//qDebug()<<"--CloseLoopXS"<<QString::number(CloseLoopXS);
					if((CloseLoopXS>1.1) || (CloseLoopXS<0.9))
					{CloseLoopXS = CloseLoopXS*0.950000;}
					//    qDebug()<<"--CloseLoopXS"<<QString::number(CloseLoopXS);
					//                qDebug()<<"--------------------------------------------";
					quint32 LoopXStemp = (quint32)(CloseLoopXS*1073741824);
					//                            qDebug()<<"--LoopXStemp"<<QString::number(LoopXStemp);
					//                         SENDAtoFPGA(LoopXStemp,0x030e);//SET AC
					SENDAtoFPGA(LoopXStemp,0x030e);//SET AC
				}

				/*********************************close loop******************************************/
			}
		}
	}

	/***********************************************************************************************************/
}

void CSttDevicePIS2K::AutoCurrentState()
{
	/***********************************AutoCurrentState****************************************************/
	if((StrModePara.PIS2KStateFlag == 7) && (StrModePara.PIS2KGetStateAutoFlag == 1))
	{
		if(vlue_AD2<=490)
		{
			StrModePara.ADCurrentState = 0;
			StrModePara.PIS2KStatesendbuffer |= BIT5;
			SENDAtoFPGA(StrModePara.PIS2KStatesendbuffer,0x010B);
		}
		else if(vlue_AD2>520)
		{
			StrModePara.ADCurrentState = 1;
			StrModePara.PIS2KStatesendbuffer &= ~BIT5;
			SENDAtoFPGA(StrModePara.PIS2KStatesendbuffer,0x010B);
		}
	}
	/***********************************AutoCurrentState****************************************************/

}

void CSttDevicePIS2K::SetTestStop(BOOL bIsSysDefaultOutput)
{
	qDebug()<<"############CSttDevicePIS2K::StopTest################";
	close_pis2k();
}
