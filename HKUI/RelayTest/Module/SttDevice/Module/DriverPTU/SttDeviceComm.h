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

//״̬���
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


//״̬���д�������
#define State_Trig_Manual          0x001
#define State_Trig_Bin             0x002
#define State_Trig_TimeDelay       0x100
#define State_Trig_GPS             0x200
#define State_Trig_Bin_TimeDelay   0x102
#define State_Trig_GPS_TimeDelay   0x202

/***PTUͨ��ӳ��ο�
int g_nVChannel[6] = {4,5,0,1,3,2};
int g_nIChannel[6] = {3,5,0,2,1,4};
***/

//��Ӧ���type
#define PTU_Result_Type_TestStart       1//��ʼʵ��
#define PTU_Result_Type_TestFinish      2//ʵ�����
#define PTU_Result_Type_ANALG_CHANGE    3
#define PTU_Result_Type_DIG_CHANGE      4
#define PTU_Result_Type_DO_CHANGE       5
#define PTU_Result_Type_DI_CHANGE       6
#define PTU_Result_Type_StateChange     7//״̬�л�


#define PTU_MAX_MODULE_COUNT 8
typedef struct{
	unsigned int nmodule;//ģ���ţ�0����ѹ	1������
	unsigned int nCnt;//��Ч���ݳ���
	long dat[1500];
}DrvManuAnalog;

typedef struct{
	unsigned int moduleCount;				//ģ������
	unsigned int sample;					//�������ʣ�sample = 40000/F, FΪ����Ƶ��,�ֶ�ʵ���ѹ�زɱջ�����
	DrvManuAnalog module[PTU_MAX_MODULE_COUNT];//ģ�����ݽṹ
}DrvManuPara;

typedef struct{
	unsigned int type;					//���ͣ���PN466A
	unsigned int step;					//ָʾ״̬���еĵڼ���״̬���ֶ�ʵ����0
	unsigned int source;					//״̬���д���ֵ��0���ֶ�������1��ʱ�䴥�� 2��GPS����3������������
	unsigned int sec;						//UTC sec
	unsigned int nSec;					//UTC nSec
	unsigned int biValue;					//��������ֵ
	unsigned int boValue;
}DrvResultItem;

typedef struct{
	unsigned int cnt;
	DrvResultItem result[1000];
}DrvResult;						//���ؽ��

//~~~~~~~~~~~~~~~~~~~~~~~~~~~` state
typedef struct{
	unsigned int ref;			//0:��ת	1:�ߵ�ƽ	2:�͵�ƽ
	unsigned int logic;		//0:�봥��	1:�򴥷�
	unsigned int valid;		//bit9~bit0��Ӧ����10������1
}structBITrip;

typedef struct{
	unsigned int sec;						//GPS��ֵ
	unsigned int nSec;					//GPS����ֵ
	unsigned int reserve;					//����
}structGPSTrip;

typedef struct{
	unsigned int mSec;					//ʱ�䴥������ֵ
	unsigned int reserve[2];				//����
}structTmTrip;

typedef struct{
	unsigned int nmodule;			//ģ����
	unsigned int cnt;
	long dat[12+12*3];				//����С�ź�12·
}DrvStateAnalog;

typedef struct{
	unsigned int state;			//״̬��
	unsigned int trip;				//��������	0���ֶ� 1��ʱ�� 2��GPS	3:������
	union {						//���������������������ṹ��
		structBITrip	bi;
		structGPSTrip 	gps;
		structTmTrip	tm;
	}tripData;
	unsigned int mdelay;			//���봥������ʱʱ����ʱʱ�����ֵ
	unsigned int BO;				//������ֵ
	DrvStateAnalog module[PTU_MAX_MODULE_COUNT];		//ģ������
}DrvStateItem;

typedef struct{
	unsigned int stateCount;			//״̬��
	unsigned int moduleCount;		//ģ����
	unsigned int isLoop;				//�Ƿ�ѭ��
	DrvStateItem item[500];
}DrvStatePara;

//г����֧�ִ����,ֻ���ֶ�֧����ѹ��

class CSttDeviceComm
{
public:
	CSttDeviceComm();
	~CSttDeviceComm();

	int m_nfd;
	int m_oPreBiStatus;	
	Drv_BoardVersion m_oBoardinfo;
	int m_nTestTap;//��ѹ����ͨ��Ӳ���л���ʶ�����ʶ�ı䣬��Ҫ��ǰֹͣʵ��
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
