#ifndef CSTTDEVICECOMM_H
#define CSTTDEVICECOMM_H

#include "stdafx.h"
#include "../../../SttTestBase/SttTestBase.h"
#include "../../../SttTest/Common/tmt_system_config.h"
#include "../../../SttTest/Common/Adjust/SttAdjust_ModuleOutput.h"
#include "../../../SttTest/Common/SttSystemConfig.h"
#include "../../../Engine/SttServerTestCtrlCntr.h"
#include "../../SttDeviceStatus.h"
#include "../../SttDeviceBase.h"

//状态相关
#define STATE_RAMP_TYPE_NULL         0
#define STATE_RAMP_TYPE_SLIP_VAL     1
#define STATE_RAMP_TYPE_SLIP_FRE     2
#define STATE_RAMP_TYPE_NORMAL       3

#define STATE_RESULT_START                 1
#define STATE_RESULT_STOP                  2
#define STATE_RESULT_CHANGE                3
#define STATE_RESULT_DI_CHANGE             4
#define STATE_RESULT_GRADIENT              5
#define STATE_RESULT_GOOSE_CHANGED         6
#define STATE_RESULT_GRADIENTVALUE         7
#define STATE_RESULT_BOCHANGED             8
#define STATE_RESULT_GRADIENTEND          10


//状态序列触发类型
#define State_Trig_Manual          0x001
#define State_Trig_Bin             0x002
#define State_Trig_TimeDelay       0x100
#define State_Trig_GPS             0x200
#define State_Trig_Bin_TimeDelay   0x102
#define State_Trig_GPS_TimeDelay   0x202

/***PTU通道映射参考
int g_nVChannel[6] = {4,5,0,1,3,2};
int g_nIChannel[6] = {3,5,0,2,1,4};
***/

//对应结果type
#define PTU_Result_Type_TestStart       1//开始实验
#define PTU_Result_Type_TestFinish      2//实验结束
#define PTU_Result_Type_ANALG_CHANGE    3
#define PTU_Result_Type_DIG_CHANGE      4
#define PTU_Result_Type_DO_CHANGE       5
#define PTU_Result_Type_DI_CHANGE       6
#define PTU_Result_Type_StateChange     7//状态切换


#define PTU_MAX_MODULE_COUNT 8
typedef struct{
	unsigned int nmodule;//模块编号，0：电压	1：电流
	unsigned int nCnt;//有效数据长度
	long dat[1500];
}DrvManuAnalog;

typedef struct{
	unsigned int moduleCount;				//模块总数
	unsigned int sample;					//采样速率，sample = 40000/F, F为交流频率,手动实验高压回采闭环调节
	DrvManuAnalog module[PTU_MAX_MODULE_COUNT];//模拟数据结构
}DrvManuPara;

typedef struct{
	unsigned int type;					//类型，见PN466A
	unsigned int step;					//指示状态序列的第几个状态，手动实验填0
	unsigned int source;					//状态序列触发值，0：手动触发，1：时间触发 2：GPS触发3：开入量触发
	unsigned int sec;						//UTC sec
	unsigned int nSec;					//UTC nSec
	unsigned int biValue;					//开关量的值
	unsigned int boValue;
}DrvResultItem;

typedef struct{
	unsigned int cnt;
	DrvResultItem result[1000];
}DrvResult;						//返回结果

//~~~~~~~~~~~~~~~~~~~~~~~~~~~` state
typedef struct{
	unsigned int ref;			//0:翻转	1:高电平	2:低电平
	unsigned int logic;		//0:与触发	1:或触发
	unsigned int valid;		//bit9~bit0对应开入10～开入1
}structBITrip;

typedef struct{
	unsigned int sec;						//GPS秒值
	unsigned int nSec;					//GPS纳秒值
	unsigned int reserve;					//保留
}structGPSTrip;

typedef struct{
	unsigned int mSec;					//时间触发毫秒值
	unsigned int reserve[2];				//保留
}structTmTrip;

typedef struct{
	unsigned int nmodule;			//模块编号
	unsigned int cnt;
	long dat[12+12*3];				//兼容小信号12路
}DrvStateAnalog;

typedef struct{
	unsigned int state;			//状态号
	unsigned int trip;				//触发类型	0：手动 1：时间 2：GPS	3:开入量
	union {						//触发参数，见上面三个结构体
		structBITrip	bi;
		structGPSTrip 	gps;
		structTmTrip	tm;
	}tripData;
	unsigned int mdelay;			//开入触发有延时时的延时时间毫秒值
	unsigned int BO;				//开出量值
	DrvStateAnalog module[PTU_MAX_MODULE_COUNT];		//模拟数据
}DrvStateItem;

typedef struct{
	unsigned int stateCount;			//状态数
	unsigned int moduleCount;		//模块数
	unsigned int isLoop;				//是否循环
	DrvStateItem item[500];
}DrvStatePara;

//谐波不支持大电流,只有手动支持升压器

class CSttDeviceComm
{
public:
	CSttDeviceComm();
	~CSttDeviceComm();

	int m_nfd;
	int m_oPreBiStatus;	
	Drv_BoardVersion m_oBoardinfo;
	int m_nTestTap;//电压电流通道硬件切换标识，如标识改变，需要提前停止实验
	BOOL m_bSysOutPutRunning;


	//SttDriver
	unsigned int *g_start;
	int g_nmaplen;

public:
	void SetBISetting();
	void SetManualBI(char* pszBuff,int nLen);

	void SetTestTap(int nTestTap);
	void SetSystemConfig();
	void InitDApara(int fd);

	void tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt);
	void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt);
	void tmt_to_drv_manu(tmt_ManualTest *pTmt);
	void tmt_to_drv_harm(tmt_HarmTest *pTmt);
	void tmt_to_drv_StatePara(tmt_StateTest *pTmt);
	void ProManuDrvResult();
	void ProStateDrvResult();
	void SetTestStart(int nTestType);
	void SetTestStop(BOOL bIsSysDefaultOutput);

	long TranslateACFre(float fFre);
	//volt
	void TransAnalogDCVolToDrv(float fAmp,int nChannel,int nModuleUIndex,long *pDrvData);
	long TranslateACVoltAmp(float fAmp,int nChannel,int nModuleUIndex,int nHarm);
	void TransAnalogVolToDrv(float fAmp,float fAng,float fFre,int nChannel,int nModuleUIndex,long *pnDrvData);
	//current
	void TransAnalogDCCurToDrv(float fAmp,int nChannel,int nModuleIIndex,long *pDrvData);
	long TranslateACCurrentAmp(float fAmp,int nChannel,int nModuleIIndex,int nHarm);
	void TransAnalogCurToDrv(float fAmp,float fAng,float fFre,int nChannel,int nModuleIIndex,long *pnDrvData);

	void SetStateTriger();

public:
	void Manual_Volt(tmt_channel *pTmt_channel,long *pDrvData,int nHarm,
					 long nModuleUIndex,BOOL bIsDc=FALSE,BOOL bIsModuleOutput=FALSE);
	void Manual_Current(tmt_channel *pTmt_channel,long *pDrvData,int nHarm,
						long nModuleIIndex,BOOL bIsDc=FALSE,BOOL bIsModuleOutput=FALSE);

	void GetBoardInfo();
//	void AnalysisDrvSysInfo(DeviceParaState oDeviceParaState,BOOL bIsVolt=FALSE);
};

#endif // CSTTDEVICECOMM_H
