#ifndef CSTTDEVICECOMM_H
#define CSTTDEVICECOMM_H

#include "IEC61850CfgMngr.h"
#include "../../../SttTestBase/SttTestBase.h"
#include "../../../SttTest/Common/tmt_system_config.h"
#include "../../../SttTest/Common/Adjust/SttAdjust_ModuleOutput.h"
#include "../../../SttTest/Common/SttSystemConfig.h"
#include "../../../Engine/SttServerTestCtrlCntr.h"
#include "../../SttDeviceStatus.h"
#include "../../SttDeviceBase.h"
#include "../PowerCtrl/SttPowerCtrlCom.h"
#include "../../../SttTest/Common/tmt_rtdata_def.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>	//SIGIO
#include<sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>

//ͳһ�������
#define DrvResult_TestStart			0x01
#define DrvResult_TestFinish		0x02
#define DrvResult_Output_Change		0x03
#define DrvResult_Light_TimeOut		0x04 //�����ʱ
#define DrvResult_GOOSE_Link		0x05
//���뿪���������
#define DrvResult_BO				0x101
#define DrvResult_BI				0x102
#define DrvResult_BI_LogicMatch		0x103
//״̬���з��ؽ������
#define DrvResult_State_StateChg	0x201
#define DrvResult_State_BO			0x202
#define DrvResult_State_Degress		0x203
#define DrvResult_State_DegressStop	0x204
#define DrvResult_State_BI_DI_REF	0x205
//�ݱ���Ϣ
#define DrvResult_Degress_Return		0x301
#define DrvResult_Degress_BfFault		0x302
#define DrvResult_Degress_Fault			0x303
//��ʵ��������
#define DrvResult_SwingType_Swing		0x401
#define DrvResult_SwingType_Fault		0x402
//SOE��Ϣ
#define DrvResult_BO_REFVAL			0x501
//PPS��Ϣ
#define DrvResult_PPS               0x601
#define DrvResult_STOP_BCODE        0x602
//ͬ��
#define DrvResult_Sync_Bin_Report		0x701
#define DrvResult_Sync_Bin_Syn			0x702
#define DrvResult_Sync_Bo_Flip			0x703
#define DrvResult_Sync_Degress			0x704
//Lt�ط�
#define DrvResult_LtReplay_WaveTrip		0x801
//Pcap�ط�
#define RESULT_TYPE_PcapReplay_Start	0x901
#define RESULT_TYPE_PcapReplay_Trip		0x902

typedef struct
{
	unsigned int nType;//1:����ǰ 2:������
	unsigned int nUtcH;
	unsigned int nUtcL;
	unsigned int nCurStep;
	unsigned int nCurState;
} Drv_DegressData;

typedef struct
{
	unsigned int nWriteCount;
	unsigned int nReadCount;
	Drv_DegressData oData[STT_DRV_RTDATA_MSG_MAX_COUNT];
} Drv_DegressMsg;

typedef struct
{
	unsigned int nAlgCnt;			//ģ���SMVģ������
	unsigned int nAlgTable[ALG_MODULE_MAX];
	unsigned int nBiCnt;			//����ģ������
	unsigned int nBiTable[BIO_MODULE_MAX];
	unsigned int nBoCnt;				//����ģ������
	unsigned int nBoTable[BIO_MODULE_MAX];
} Drv_ModulePara;

typedef struct
{
	unsigned int maxVaildCnt[ALG_MODULE_MAX];
} Drv_ModuleMaxVaildCnt;

typedef struct
{
	unsigned int nCnt;
	unsigned int nModule[ALG_MODULE_MAX];
	unsigned int maxVaildCnt[ALG_MODULE_MAX];
} Drv_WeekInitDA;

//����ֵ���ݽṹ
typedef struct
{
	unsigned int nVal1;
	unsigned int nVal2;//����ֵ
} structBoStatusItem;

//�������������ݽṹ
typedef struct
{
	structBoStatusItem item[BIO_MODULE_MAX];
} DrvComBoStatus;

typedef struct
{
	unsigned int nVal1;
	unsigned int nVal2;		//����ֵ
} structBIChangeItem;

//�����λ���ݽṹ
typedef struct
{
	structBIChangeItem item[BIO_MODULE_MAX];
} DrvBIChange;

typedef struct
{
	unsigned int 	nStep;			//״̬����״̬��ţ���״̬�������ģ��ʹ��
	unsigned int 	nDegressStep;		//�ݱ䲽���ţ��ݱ�ģ���״̬���еĵݱ䶼ʹ�ø�����ָʾ
	unsigned int 	nType;			//������ͣ������3-1
	unsigned int 	nSource;			//����Դ�������3-2
	unsigned int 	nSec;				//UTCʱ����ֵ
	unsigned int 	nNanoSec;			//UTCʱ������ֵ
	unsigned int    nGooseFlag;         //bit31-bit16 1:gse  0:bin  bit15-bit0 :SqNum
	DrvBIChange 	oBiChg;			//�����λֵ����sourceΪ�����λʱ����ֵ
	Drv_BIStatus	nBi;				//������ֵ
	DrvComBoStatus	nBo;				//������ֵ
	Drv_BIStatus	nDi;				//Goose������ֵ
} Drv_ResultItem;

/***********�ֶ��ṹ��***********/
#define ALG_PARAM_MAX		3442 //ģ������Ҳ������� (DIGITAL_CHANNEL_MAX*3)*31=3441 + 1(ADMU)
//ģ�����ݺ����Ҳ����ṹ
typedef struct
{
	unsigned int nDWcnt;			//��Ч���ݸ�������32λΪ��λ
	long dat[ALG_PARAM_MAX];
} Drv_HarmParam;

typedef struct
{
	unsigned int nModuleCnt;
	unsigned int nModule[ALG_MODULE_MAX];//��Ч���ݸ�������32λΪ��λ
	Drv_HarmParam oHarmParam[ALG_MODULE_MAX];
} Drv_HarmADMUFT3;//ADMUFT3���Ҳ���

//�ֶ�ʵ�����ݶ���ṹ
typedef struct
{
	Drv_HarmParam	oDrv_HarmParam[ALG_MODULE_MAX];
	DrvComBoStatus  oDrvComBoSta;
	long nPPSDelayTime;//��ʱ��ʼǰ�ȴ�ʱ��
	long nReLoadFT3;
	long nFT3Module;
	unsigned int nAuxVolt;//����ֱ��
	Drv_HarmADMUFT3 oDrv_ADMUHarm;
} Drv_ManuData;
/***********�ֶ��ṹ��***********/

/***********���봥���ֶ��ṹ��***********/
//������Чλ���ݽṹ
typedef struct
{
	unsigned int nModule;
	unsigned int nVal1;
	unsigned int nVal2;		//��Чλ��ֵ
} structBIValidItem;
typedef struct
{
	unsigned int nModuleCount;
	structBIValidItem item[BIO_MODULE_MAX];
} structBIValid;
//���봥�����ݽṹ
typedef struct
{
	unsigned int nBiRef;			//0:��ת����	 1���½��ش���	2�������ش���
	unsigned int nBiLogic;		//0�������	1��������
	structBIValid oValid;			//��Чͨ��
} DrvBITrip;

//�ֶ�ʵ�鿪��������
//������Чλ���ݽṹ
//�������ݽṹ
typedef struct
{
	unsigned int nBinIsStop; //�������յ����Ƿ�ֹͣ
	unsigned int nMdelay; //�������յ����������ʱ��
	DrvBITrip oTrip; //����
} Drv_ManuBin;
/***********���봥���ֶ��ṹ��***********/

/***********״̬�ṹ��***********/
//������ת���ݽṹ
typedef struct
{
	DrvComBoStatus	boValue;		//������״ֵ̬(nTripMode==2)����Чλ(nTripMode==0,nTripMode==1)
	unsigned int 	nTripMode;		//0:ʱ�䴥�� 1�����봥��(��ʱ����,Ԥ��) 2:��״ֵ̬��� 3:����������
	unsigned int 	nPreTripTime;	//�Ա�״̬��ʼʱ����ʱ���,����ǰʱ��,��λ����(ʱ�䴥��)
	//nPreTripTime>=0��Ч,ʱ�������תһ��
	unsigned int 	nOutPutTime;	//�����󱣳�ʱ��,��λ����(ʱ�䴥��)
	//nOutPutTime>0��Ч,ʱ�������תһ��
} Drv_BoFlip;

//����ʵ�����ò�������ṹ
typedef struct
{
	unsigned int    nStateCount;			//״̬���� �̶�Ϊ8
	unsigned int	nFaultTime;		//������ʱ�� ms
	unsigned int 	nTripTime;		//�����բʱ�� ms
	unsigned int	nTransitionalTime; //ת��ʱ�� ms
	unsigned int 	bIsPermanent;        //�Ƿ����ù���    1�� ����  0 �� ˲ʱ����
	unsigned int	bIsTransitionalFault;//�Ƿ���ת������  1�� ��    0 �� ����
	unsigned int	nReclosingTime;		//�غ�բ��ֵ ms
	unsigned int 	nStopTime;			//ֹ̬ͣ����ʱ�� ms
	unsigned int	nIsLoop;				//�Ƿ�ѭ��
	unsigned int	nbiRefFirst;
	Drv_BIStatus	oGooseInit;			//goose�����ʼֵ
} Drv_CboperPara;

//���ò�������ṹ
typedef struct
{
	unsigned int nStateCount;			//״̬����
	unsigned int nIsLoop;				//�Ƿ�ѭ��
	unsigned int nbiRefFirst;
	unsigned int nIsSequence;			//Ĭ��0 ,1: ��ʾ˳�������Ҫ���⴦��
	Drv_BIStatus oGooseInit;			//goose�����ʼֵ
} Drv_StatePara;

//״̬����״̬����
//GPS��ʱ�������嶨��
typedef struct
{
	unsigned int nSec;			//GPS������ֵ
	unsigned int nNsec;			//GPS��������ֵ
	unsigned int nReserve;
} structGPS;
typedef struct
{
	unsigned int nMsec;				//ʱ�䴥������ֵ
	unsigned int nUsec;             //ʱ�䴥��΢��ֵ
	unsigned int nDelay;			//���봥����ʱʱ��,����
} structTime;
typedef union
{
	structGPS	oGps;				//GPS����
	structTime	oTime;				//ʱ�䴥��
} unionTm;

#define StateAcDataBufLen 336//48+48*3*2
#define StateDegressMinStep 0.0000009
//״̬����������ݽṹ
typedef struct
{
	unsigned int 	DWCount;			//��Ч���ݳ���
	unsigned int    nPhase;//��բ��
	unsigned int	nexpconfig;//�����ڷ�������
	long    nexp[12];//12·�����ڷ���
	long	nVal[StateAcDataBufLen];		//�������
} structACParamItem;

typedef struct
{
	structACParamItem item[ALG_MODULE_MAX];
} Drv_StateACPara;

//״̬���еݱ����ݽṹ
typedef struct
{
	unsigned int 	nIsChange;			//0:���ݱ�			1���ݱ�

	unsigned int 	nCount[StateAcDataBufLen];				//�ݱ����
	long			changeVal[StateAcDataBufLen];		//�ݱ�ֵ�����˵��
	long			lastVal[StateAcDataBufLen];			//��ֵֹ�����˵��
} Drv_StateDeg;

typedef struct
{
	unsigned int nModulesCnt;    //ģ����
	unsigned int nModule[ALG_MODULE_MAX];
	structACParamItem	oADMUACPara[ALG_MODULE_MAX];	//�����������
	Drv_StateDeg        oADMUStChange[ALG_MODULE_MAX];	//״̬���еݱ����
} Drv_StateADMUPara;

//״̬���д�������
#define State_Trig_Manual          0x001
#define State_Trig_Bin             0x002
#define State_Trig_TimeDelay       0x100
#define State_Trig_GPS             0x200
#define State_Trig_Bin_TimeDelay   0x102
#define State_Trig_GPS_TimeDelay   0x202
//˵����״̬���еݱ����ͬʱ�仯Ƶ�ʺͷ�ֵ��changVal��lastVal��������˳��Ϊ��
//ģ��ģ�飺6ֱ������+��Ƶ��+��ֵ��*��DWCount-6����
//SMVģ�飺��Ƶ��+��ֵ��*DWCount;
typedef struct
{
	unsigned int        nTirpType;			//����Դ���ã�����5-1
	DrvBITrip           obiTrip;				//���봥������
	unionTm             oTm;					//ʱ���GPS�����������
	unsigned int        nChangemSec;		//״̬���еݱ�ʱ��ֶȣ���λ����
	unsigned int		nBoType;			//0:Bo+Gse,1-Bo,2-Gse
	Drv_BoFlip          oStBo;				//��������
	Drv_StateDeg        oStChange[ALG_MODULE_MAX];		//״̬���еݱ����
	Drv_StateACPara 	oAcParam;			//ģ���������
	DrvGseChgParas      oGseChgParas;			//goose��λ��Ϣ
	unsigned int        nGseChgValid;       //1��Ч
	DrvFT3ChgParas      oFt3ChgParas;
	unsigned int        nFt3ChgValid;       //1��Ч
	Drv_GseTest         GooseTest;
	unsigned int        nAuxVolt;//����ֱ��

	Drv_AbnPara			oAbnPara;//�쳣ģ������ṹ
	Drv_StateADMUPara	oADMUPara;//Ft3������
} Drv_StateItem;

/***********״̬�ṹ��***********/

/***********���ϻطŽṹ��***********/

typedef struct
{
	unsigned int tripType;        //0 �޴��� 1 manu(�ֶ�)2 bi(����) 3GPS(GPS)
	DrvBITrip stBITrip;				//���봥������
	int tripLoopCount;          //ѭ������
	int modeAfterTrip;
	unsigned int tripgpsSec;      //GPS����
	unsigned int tripgpsnSec;
	unsigned int freq;           //����Ƶ��
	unsigned int moduleCount;	 //ģ������
	unsigned int module;	 //ģ��
	DrvComBoStatus  oDrvComBoSta;
} Drv_LtReplayParam;

typedef struct
{
	unsigned int module;
	unsigned int ch;
} Drv_ComReplayCh;

typedef struct
{
	unsigned int tripType;        //0 �޴��� 1 manu(�ֶ�)2 bi(����) 3GPS(GPS)
	DrvBITrip stBITrip;				//���봥������
	unsigned int tripgpsSec;      //GPS����
	unsigned int tripgpsnSec;
	Drv_ComReplayCh ch[ALG_MODULE_MAX];//ģ��ط�ͨ������
	unsigned int StopTime;      //ʵ�����ʱ��
	unsigned int freq;
	unsigned int loopCount;     //ѭ������
	unsigned int SOL1;//ѭ����ʼλ��
	unsigned int EOL1;//ѭ������λ��
} Drv_ComReplayParam;

/***********���ϻطŽṹ��***********/

/***********�ݱ�ʵ������ṹ��***********/
typedef struct
{
	unsigned int nDWcnt;			//��Ч���ݸ�������32λΪ��λ
	long bfChangedat[ALG_PARAM_MAX];//�仯ǰ����
	long bfFaultdat[ALG_PARAM_MAX];//����ǰ����
	long FaultBegindat[ALG_PARAM_MAX];//���Ͽ�ʼ����

	//Amp Ang Freֻ��һ�ֵݱ�
	long nFaultChangVal[ALG_PARAM_MAX];//���ϵݱ�����
	long nFaultLastVal[ALG_PARAM_MAX];//�������һ���ݱ�����
} DrvDataItem;

typedef struct
{
	unsigned int nModuleCnt;
	unsigned int nModule[ALG_MODULE_MAX];
	DrvDataItem para[ALG_MODULE_MAX];
} Drv_ADMUACPara;

typedef struct
{
	DrvDataItem para[ALG_MODULE_MAX];
	Drv_ADMUACPara ADMUPara;
} Drv_ACPara;

typedef struct
{
	unsigned int	posCnt;
	unsigned int	pos[21];//4U3I 7*3
	long 			dat[21];
} Drv_DegDataUnit;

typedef struct
{
	unsigned int nModuleCnt;
	unsigned int nModule[ALG_MODULE_MAX];
	Drv_DegDataUnit unit[ALG_MODULE_MAX];
} Drv_ADMUDegData;

typedef struct
{
	Drv_DegDataUnit unit[ALG_MODULE_MAX];
	Drv_ADMUDegData oADMUDegData;
} Drv_DegData;

typedef struct
{
	unsigned int 		cnt;						//�ݱ����
	unsigned int        mode;						//0-��Եݱ�  1-����ֵ�ݱ�
	unsigned int 		isReturn;					//0���յ�������������	1���յ�����������ݱ�
	DrvBITrip			trip;						//���봥������
	unsigned int 		timeDiv;					//�ݱ�ʱ��ֶȣ���λ����
	unsigned int 		timeBfChg;					//�仯ǰʱ�����ֵ
	DrvComBoStatus		boBfChange;					//�仯ǰ����״̬����
	unsigned int 		timeBfFault;				//����ǰʱ�����ֵ
	DrvComBoStatus		boBfFault;					//����ǰ����״̬����
	DrvComBoStatus		boFault;					//����̬����״̬����
	unsigned int 		boFaultFlipSec;				//������תʱ����ֵ
	unsigned int 		boFaultFlipnSec;			//������תʱ������ֵ
	Drv_ACPara		    AcPara;						//����ģʽ����������
	Drv_DegData			DegData[GRADIENT_MAX_COUNT];//������ģʽ����������
} DrvDegressPara;
/***********�ݱ�ʵ������ṹ��***********/

/***********��ʵ������ṹ��***********/
#define SHAKE_MAX		1000

typedef struct
{
	unsigned int 	nCnt;
	long 			dat[111];//37*3
} Drv_ShakeData;

typedef struct
{
	Drv_ShakeData	stData[ALG_MODULE_MAX];
} Drv_ShakePara;

typedef struct
{
	unsigned int 	shakeCount;					//�𵴲���
	unsigned int 	isRecip;					//1��������	0����������
	unsigned int 	timeDiv;					//�仯ʱ����΢��ֵ
	unsigned int 	timeBfShake;				//��ǰʱ�����
	unsigned int 	shakeMax;					//�𵴲���
	unsigned int 	faultMax;					//���ϲ���
	DrvBITrip		stBITrip;					//���봥������
	Drv_ShakePara	bfShake;					//��ǰ����
	Drv_ShakePara	shake[SHAKE_MAX];			//������
	Drv_ShakePara	fault[SHAKE_MAX];			//��������
	DrvComBoStatus  oDrvComBoSta;
} Drv_Swing;
/***********��ʵ������ṹ��***********/

/***********ͬ��ʵ������ṹ��***********/
typedef struct
{
	unsigned int DWCount;
	long Begindat[111]; //��ʼ����
	long StepAmp[111]; //0 ����
	long StepFre[111]; //1 ����
} Drv_SyncUnit;

typedef struct
{
	Drv_SyncUnit SyncUnit[ALG_MODULE_MAX];
} Drv_SyncAcData;

typedef struct
{
	unsigned int syn;
	unsigned int incA;//0
	unsigned int decA;//1
	unsigned int incF;//2
	unsigned int decF;//3
} structTripDI;

typedef struct
{
	unsigned int RefBeginAmp;
	unsigned int RefMaxAmp;
	unsigned int RefMinAmp;
	unsigned int RefStepAmp;//uV
	unsigned int RefBeginFre;
	unsigned int RefMaxFre;
	unsigned int RefMinFre;
	unsigned int RefStepFre;//uHz
	unsigned int RefNormalFre;//uHz
} Drv_ParaRef;

typedef struct
{
	unsigned int    nBout;
	unsigned int    nB4Bit;//0~7
	unsigned int    nB4FlipTime;//ms
	unsigned int    nB4FlipType;
} structSyncBo;

typedef struct
{
	unsigned int 	RunType;	//0:�߽�ֵ����	1����ѹ����   2����Ƶ����  3:�Ե���
	unsigned int 	StepType; //RunType == 0,0��1��2��3
	unsigned int 	StepTime; //RunType == 0
	structSyncBo    stBo;
	structTripDI 	trip;
	Drv_SyncAcData	stData;
	Drv_ParaRef   stParaRef;
} Drv_SyncParam;

/***********ͬ��ʵ������ṹ��***********/

/***********��չ��������SOEʵ������ṹ��***********/
typedef struct
{
	unsigned int nTmHigh;				//�ߵ�ƽʱ�䳤�Ⱥ���
	unsigned int nTmLow;				//�͵�ƽʱ�䳤�Ⱥ���
	unsigned int nflipCnt;				//��ת����
} Drv_BoPara;

typedef struct
{
	unsigned int nModule;			//ģ����
	unsigned int nBinOut[2];				//������ʼֵ
	unsigned int nType[2];			//ʵ������ 0������1ΪSOEʵ��
	Drv_BoPara param[64];
	unsigned int nDelayTime;//����ǰʱ��
	unsigned int nBeginTime[64];//���ʱ��
} Drv_SoeExItem;

typedef struct
{
	unsigned int nTripType;//0: �������� 1: GPS ����
	unsigned int nModuleCnt;//ģ����
	unsigned int nMode;//0-MainBoard  1-ExBoard  2-Goose
	unsigned int nUseBiRes;//0-No 1-Yes
	unsigned int nGPS_Sec;//GPS ����ʱ����ֵ
	unsigned int nGPS_Nsec;//GPS ����ʱ������ֵ
	unsigned int nHoldTime;//����ʱ����ֵ
	Drv_SoeExItem item[BIO_MODULE_MAX];
} Drv_SoeExPara;

#define SOE_MAX		10000
typedef struct
{
	unsigned int nStepCnt;
	unsigned int nDiffTime[SOE_MAX];
	unsigned int nBo[SOE_MAX];
} Drv_SoePara;//MainBoard

typedef struct
{
	unsigned int nMsTime;
	unsigned int nBo;
} Tmt_SoeStep;

typedef struct
{
	unsigned int nStepCnt;
	Tmt_SoeStep oStep[1005];
} Tmt_SoePara;

typedef struct
{
	Tmt_SoePara oTmt_SoePara[8];//8������
} Tmt_SoeParas;

/***********��չ��������SOEʵ������ṹ��***********/

typedef struct
{
	double dTime; //����ʱ��
	double dLastBinTime; //��ǰ����̬���һ�������¼��ľ���ʱ��
	int nStep;
} GradientStep_Info;

typedef struct
{
	tmt_BinaryOut   m_binOut[MAX_BINARYOUT_COUNT];
	tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];
	void init()
	{
		for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
		{
			m_binOut[i].init();
		}

		for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binOutEx[i].init();
		}
	}
} tmt_BinaryOuts;

typedef struct
{
	tmt_BinaryIn	m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn	m_binInEx[MAX_ExBINARY_COUNT];
	void init()
	{
		for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			m_binIn[i].nSelect = 0;
		}

		for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binInEx[i].nSelect = 0;
		}
	}
} tmt_BinaryIns;

class CSttDeviceComm
{
public:
	CSttDeviceComm();
	~CSttDeviceComm();

	int m_nfd;
	//SttDriver
public:
	CIEC61850CfgMngr m_oCIEC61850CfgMngr;
	Drv_BIStatus m_oPreBiStatus;
	Drv_BIStatus m_oStateFirstBi;
	Drv_BIStatus m_oStateFirstDi;
	DrvComBoStatus	m_oPreBoStatus;
	DrvComBoStatus	m_oGradientBo_BfFault;
	DrvComBoStatus	m_oGradientBo_Fault;
	tmt_BinaryIns  *m_pCurBins;
	tmt_GoosePub m_oPreGoosePub[MAX_MODULES_GOOSEPUB_COUNT];
	tmt_Ft3Pub m_oPreFt3Pub[MAX_MODULES_FT3PUB_COUNT];
	tmt_GoosePubs *m_pStateGoosePub;
	tmt_Ft3Pubs *m_pStateFt3Pub;
	Drv_BoardVersion m_oBoardinfo;
	GradientStep_Info m_oStepInfo;
	double m_nCurStateRealTime;
	long m_nDCTap;
	Drv_IECConfig_2M m_o2MChgParas;
	tmt_Stable2MList m_oPreStable2MList[MAX_2M_MODULE_COUNT][MAX_2M_BLOCK_COUNT];

	Drv_ModuleMaxVaildCnt m_oModuleMaxVaildCnt;
	Drv_DegressMsg *m_pDegressMsg;
	char *m_pMmapBuf;
	QList<Drv_DegressData> m_oRtDataList;
	BOOL m_bRdDegRtData;
	void InitBuff();
	void ProVoltCurRtData();
	virtual void GetRtData();
public:
	void SetBISetting();
	void SetManualBI(char *pszBuff, int nLen);

	void SetSystemConfig();
	void InitDApara(int fd, BOOL bHasAdjFile);

	void SetTestStart(int nTestType);
	void SetTestStop(BOOL bIsSysDefaultOutput = FALSE);
	void SetTestPara(int nTestType, char *pszBuff);

	void tmt_to_drv_record(tmt_RecordTest *pTmt);

	void SetGooseSub(char *pszBuff);
	void SetBoMap(char *pszBuff);
	void SetFT3SubMap(char *pszBuff);

	void SetBinaryOutTurnOnVaule(int nValue);
	void SetBinaryOut(BOOL bOpen = FALSE);
	void Set_BO_ENABLE(bool bEnable);
	void Set_BI_ENABLE(bool bEnable);
	void Set_Goose_BO_ENABLE(bool bEnable);
	void Set_Goose_BI_ENABLE(bool bEnable);

	BOOL TranslateDigitalVoltCurrentBuffer(tmt_channel *pVChannel, tmt_channel *pIChannel, long *pBuff, PSTT_MODULE pModule, int nHarm, BOOL bIsFT3 = FALSE);
	void TranslateDigitalVoltCurrentBuffer_Gradient(tmt_channel *pVChannel, tmt_channel *pIChannel, Drv_StateDeg *pDrvStateDeg, PSTT_MODULE pModule, BOOL bIsFT3 = FALSE);
	void TransDigitalChannelToDrv(float fAmp, float fAng, float fFre, int nGroupIndex, long *pDrvData, int nType, PSTT_MODULE pModule, BOOL bIsFT3 = FALSE, int nFT3ChannelTypePos = 0);
	long TransDigitalChannelAmp(float fValue, int nGroup, bool bDC, int nType, BOOL bIsFT3, int nFT3ChannelTypePos = 0);
	long TranslateDigitalFre(float fFre, BOOL bIsFT3 = FALSE);

	long TranslateACFre(float fFre);

	//ģ����������ý���λ�ó�ֱ��ʱ����Ҫ���ظ�����ֱ����Ư
	//volt
	void TransAnalogDCVolToDrv(float fAmp, int nChannel, int nModuleUIndex, long *pDrvData, BOOL bUseDcZero = TRUE);
	long TranslateACVoltAmp(float fAmp, int nChannel, int nModuleUIndex, int nHarm);
	void TransAnalogVolToDrv(float fAmp, float fAng, float fFre, int nChannel, int nModuleUIndex, long *pnDrvData);
	//current
	void TransAnalogDCCurToDrv(float fAmp, int nChannel, int nModuleIIndex, long *pDrvData, BOOL bUseDcZero = TRUE);
	long TranslateACCurrentAmp(float fAmp, int nChannel, int nModuleIIndex, int nHarm);
	void TransAnalogCurToDrv(float fAmp, float fAng, float fFre, int nChannel, int nModuleIIndex, long *pnDrvData);
	//UI
	void TransAnalogDCUIToDrv_Volt(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero = TRUE);
	void TransAnalogDCUIToDrv_Current(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero = TRUE);
	long TranslateACUIAmp_Volt(float fAmp, int nChannel, int nModuleIndex, int nHarm);
	long TranslateACUIAmp_Current(float fAmp, int nChannel, int nModuleIndex, int nHarm);
	void TransAnalogUIToDrv_Volt(float fAmp, float fAng, float fFre, int nChannel, int nModuleIndex, long *pnDrvData);
	void TransAnalogUIToDrv_Current(float fAmp, float fAng, float fFre, int nChannel, int nModuleIndex, long *pnDrvData);

	void FormatFlashData(PSTT_MODULE pModule, BYTE *pszBuf, long &nLen);
	void tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt);

	void ProCommDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime);
	void InitDrvResult();
	void Gradient_Manu_Harm(char *pszDrv, tmt_GradientParas &oGradientParas, int nGradientHarm = 1, int nHarmCnt = 1);
	void tmt_to_drv_manu(tmt_ManualTest *pTmt, BOOL bIsStartTest);

	void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt);

	void tmt_to_drv_harm(tmt_HarmTest *pTmt, BOOL bIsStartTest);

	void tmt_to_drv_MUTest(tmt_ManualTest *pTmt, BOOL bIsStartTest);

	void SetStateTriger();
	void tmt_to_drv_StatePara(tmt_StateParas *pTmt);
	void DealSmvAbn(structSVabnPara  *pSVabn, tmt_StateAbnormalSMV oTmtAbnPara);
	BOOL tmt_to_drv_SmvAbn(Drv_AbnPara *pAbnPara, tmt_StateAbnormalSMV oTmtAbnPara, BOOL bIsUseDefault);
	BOOL tmt_to_drv_GseAbn(Drv_AbnPara *pAbnPara, tmt_StatePara  *pTmt_paraState, tmt_StatePara  *pTmt_paraPreState);
	void tmt_to_drv_StateItem(tmt_StateParas *pTmt, long nAbnType = ABN_TYPE_NONE);
	void ProStateDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime);

	void tmt_to_drv_BinaryManu(tmt_ManualTest *pTmt, BOOL bIsStartTest);
	void tmt_to_drv_BinaryStateItem(tmt_StateParas *pTmt);

	void tmt_to_drv_CboperPara(tmt_ImpBaseParas *pTmt);
	void tmt_to_drv_AbnPara(tmt_StateParas *pTmt, long nAbnType);

	void tmt_to_drv_SwingTestPara(tmt_SwingParas *pTmt, int nStepCnt, char *pszDrv);
	void tmt_to_drv_SwingAcPara(tmt_StepUI *pTmt, char *pszDrv, int nStep, int nType);
	void SetSwingPara(char *pszDrv);
	void ProSwingDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime);

	void tmt_to_drv_SynPara(tmt_SynParas *pTmt);
	void SynPara_VolDeg(tmt_SynParas *pTmt, Drv_SyncAcData *pDrv);
	void SynPara_FreqDeg(tmt_SynParas *pTmt, Drv_SyncAcData *pDrv);
	void Syn_NormalPara(tmt_SynParas *pTmt, Drv_SyncParam *pDrv);
	void Syn_volt(tmt_channel *pTmt_channel, Drv_SyncAcData *pDrv, int nModuleUIndex);
	void Syn_UI(tmt_channel *pTmt_channel, Drv_SyncAcData *pDrv, int nModuleIndex);
	void Syn_volt_Digital92(tmt_channel *pTmt_channel, Drv_SyncUnit *pSyncUnit, PSTT_MODULE pModule);
	void ProSynDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime);

	int SetModuleFlash(PSTT_MODULE pModule, BYTE *pszBuf, int nLen);
	BOOL GetModuleFlash(PSTT_MODULE pModule, BYTE *pszBuf, int &nOffset);
	void GetModulesFPGAInfo();

	void tmt_to_drv_soe(tmt_SoeTest *pTmt);
	void ProSoeDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime);

	void SetRising(int nRising);
	void SetPPSTestStart();
	void SetPPSTestStop();
	void SetADMUChannel(tmt_ManualTest *pTmt);
	//IEC61850
public:
	void *GetIecCfgDatasMngr();
	void SetIEC61850Para();
	void SetGooseValue_StateTest(tmt_StateParas *pStateParas, int nIndex, Drv_StateItem *pDrvState, BOOL bHasGseAbn);
	void SetGooseValue_ManuTest(tmt_GoosePub *pCurGoosePub, BOOL bIsStartTest);
	BOOL SetGooseValue_Com(tmt_GoosePub *pCurGoosePub, tmt_goose *ptmt_goose,
						   DrvGseChgParas *pGseChgParas, tmt_GoosePub *pPreGoosePub, BOOL bIsCompare);
	void CloseAngle(Drv_StateItem *pDrv_StateItem, float fAngle, float fCurAngle, int nChanel);
	void Acyclic_Analog(Drv_StateItem *pDrv_StateItem, tmt_StatePara  oTmt_paraState, int nT);
	void Acyclic_Digital(Drv_StateItem *pDrv_StateItem, tmt_StatePara  oTmt_paraState, int nT);
	//Ft3
public:
	void SetFt3Value_StateTest(tmt_StateParas *pStateParas, int nIndex, Drv_StateItem *pDrvState);
	void SetFt3Value_ManuTest(tmt_Ft3Pub *pCurFt3Pub, BOOL bIsStartTest);
	BOOL SetFt3Value_Com(tmt_Ft3Pub *pCurFt3Pub, tmt_ft3_6044 *ptmt_ft3_6044,
						 DrvFT3ChgParas *pFt3ChgParas, tmt_Ft3Pub *pPreFt3Pub, BOOL bIsCompare);
	//2M
public:
	void UpdateStable2MValue_ManuTest(tmt_Stable2MList &oStable2MList, tmt_2MOnePortPub oOnePortPub);
	void SetStable2MValue_ManuTest(tmt_2MOnePortPub *p2MOnePortPub, BOOL bIsStartTest);

	//LtReplay
public:
	void ProLtReplayDAPara(DeviceDAPara *pDAPara, tmt_ReplayParas *pTmt);
	void tmt_to_drv_LtReplay(tmt_ReplayParas *pTmt, char *pszReplayCoef);
	BOOL getLtReplayBufferAFlag();
	BOOL getLtReplayBufferBFlag();
	void setLtReplayBufferABLoop(unsigned int size, char *pszDrv, unsigned int ntype);

	//ComReplay
public:
	void tmt_to_drv_ComReplay(tmt_ReplayParas *pTmt, char *pszReplayCoef);

	//Gradient
public:
	virtual void tmt_to_drv_Gradient(tmt_GradientParas *pParas, int nMode = 0);
	virtual void tmt_to_drv_Gradient_NeedStepsValue(tmt_GradientParas *pParas);
	void Gradient_NormalPara(Drv_ACPara *pDrv, tmt_Channel *puData, tmt_Channel *piData, int nHarm, int nStatus);
	void Gradient_NormalVolt(tmt_channel *pTmt_channel, Drv_ACPara *pszDrv, int nHarm, int nModuleUIndex, BOOL bIsDc, int nStatus);
	void Gradient_NormalCurrent(tmt_channel *pTmt_channel, Drv_ACPara *pszDrv, int nHarm, int nModuleIIndex, BOOL bIsDc, int nStatus);
	void Gradient_NormalUI(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
						   BOOL bIsDc, int nStatus);
	void Gradient_FaultCalc(DrvDegressPara *pDrvData, tmt_GradientParas &oGradientParas, int nMode = 0);

public:
	float getDigitalPhRatio(PSTT_MODULE pModule);
	void Manual_volt(tmt_channel *pTmt_channel, char *pszDrv, int nHarm, int nIndex, BOOL bIsDc = FALSE, BOOL bIsModuleOutput = FALSE);
	void Manual_current(tmt_channel *pTmt_channel, char *pszDrv, int nHarm, int nIndex, BOOL bIsDc = FALSE, BOOL bIsModuleOutput = FALSE);
	void Manual_UI(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex, BOOL bIsDc = FALSE);
	void State_volt(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nModuleUIndex);
	void State_volt_Gradient(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nModuleUIndex);
	void State_current(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nModuleIIndex);
	void State_current_Gradient(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nModuleIIndex);
	void State_UI(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nModuleIndex);
	void State_UI_Gradient(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nModuleIndex);
	void setTriger(tmt_StatePara  oTmt_paraState, Drv_StateItem *oDrv_StateItem, int nIndex);
	virtual void GetBoardInfo(BOOL bHasAdjFile);
	void setBCodeTime(unsigned int nYear, unsigned int nMonth, unsigned int nday, unsigned int nhour, unsigned int nmin, unsigned int nsecond);
	virtual void SetDrvMoudlePara();
	void InitWeekOutputDAData();
	virtual long TransAuxDcVolt(float fUdc);
	virtual void SetAuxDcVolt(float fUdc);
	void SetManuOrStateAuxVolt(unsigned int &pDrv_Aux, float fUdc);
	void ProCommBinEvent_forGooseLink(Drv_ResultItem oResultItem, long &nRealTimeEventCount, double dTime1, double dTime2);
	void ProStartBinEvent(Drv_BIStatus oBiStatus, long &nRealTimeEventCount, int nCurStateIndex, int nStep, double dTime1);
	void ProCommBinEvent(Drv_ResultItem oResultItem, long &nRealTimeEventCount, int nCurStateIndex, int nStep, double dTime1, double dTime2, BOOL bCalcBinAct = TRUE);
	void ProCommRtDatasEvent(tmt_channel *pVolt, tmt_channel *pCurrent, double dTime1, double dTime2);
	void ProCommBoutEvent(DrvComBoStatus oBoStatus, long &nRealTimeEventCount,
						  int nCurStateIndex, int nStep, double dTime1, double dTime2, BOOL bIsStartTest = TRUE);
	void ProGradientResult(int nStep, double dTime1);

	void SetTestCommBi(DrvBITrip &oTrip, BOOL bBinLogic, tmt_BinaryIn *pBi, tmt_BinaryIn *pBiEx, int nStateIndex = 0);
	void SetTestCommBo(DrvComBoStatus &oBoStatus, tmt_BinaryOut *pBo, tmt_BinaryOut *pBoEx);
	void Swing_volt(tmt_StepUI *pTmt, Drv_ShakePara *pszDrv, int nModuleUIndex);
	void Swing_current(tmt_StepUI *pTmt, Drv_ShakePara *pszDrv, int nModuleIIndex);
	void Swing_UI(tmt_StepUI *pTmt, Drv_ShakePara *pszDrv, int nModuleIndex);
	void TranslateDigitalVoltCurrentBuffer_Swing(tmt_StepUI *pTmt, long *pBuff, int ndigmoduleindex, int nType);
public:
	int m_nTmtChanNum;
	int m_nTmtPos;
	int m_nDrvResItemLen;
	Drv_ResultItem m_oDrvResItem;
	tmt_RtDataChs m_oTmtRtDatas;
	unsigned int m_nSmvAbnDelayOffset;
	Drv_StateItem *m_pDrv_StateItem;
	BOOL m_bRampFreq;

public:
	virtual void PreStartTestPro() {}
	virtual void SetPeripheral() {}
	virtual void AfterTestFinishedPro()
	{
		//ֹͣʵ���������ͬ������
		g_oDrvMutex.lock();
		if(g_theSystemConfig->m_bSyncSecond)
		{
			ioctl(m_nfd, 0x110, 1);
		}
		else
		{
			ioctl(m_nfd, 0x110, 0);
		}
		g_oDrvMutex.unlock();

		PowerDAMngr *pPowerDAMngr = &CSttDeviceBase::g_pSttDeviceBase->m_oPowerDAMngr;
		pPowerDAMngr->nUse = 0;
		pPowerDAMngr->nTickCnt = 0;
		pPowerDAMngr->nTickTotal = 0;
	}
	virtual void ProStateDAPara(DeviceDAPara *pDAPara, float fAuxMax, tmt_StatePara  &oTmt_FirstState);
};

#endif // CSTTDEVICECOMM_H
