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

//统一结果类型
#define DrvResult_TestStart			0x01
#define DrvResult_TestFinish		0x02
#define DrvResult_Output_Change		0x03
#define DrvResult_Light_TimeOut		0x04 //电机超时
#define DrvResult_GOOSE_Link		0x05
//开入开出结果类型
#define DrvResult_BO				0x101
#define DrvResult_BI				0x102
#define DrvResult_BI_LogicMatch		0x103
//状态序列返回结果类型
#define DrvResult_State_StateChg	0x201
#define DrvResult_State_BO			0x202
#define DrvResult_State_Degress		0x203
#define DrvResult_State_DegressStop	0x204
#define DrvResult_State_BI_DI_REF	0x205
//递变消息
#define DrvResult_Degress_Return		0x301
#define DrvResult_Degress_BfFault		0x302
#define DrvResult_Degress_Fault			0x303
//振荡实验结果类型
#define DrvResult_SwingType_Swing		0x401
#define DrvResult_SwingType_Fault		0x402
//SOE消息
#define DrvResult_BO_REFVAL			0x501
//PPS消息
#define DrvResult_PPS               0x601
#define DrvResult_STOP_BCODE        0x602
//同期
#define DrvResult_Sync_Bin_Report		0x701
#define DrvResult_Sync_Bin_Syn			0x702
#define DrvResult_Sync_Bo_Flip			0x703
#define DrvResult_Sync_Degress			0x704
//Lt回放
#define DrvResult_LtReplay_WaveTrip		0x801
//Pcap回放
#define RESULT_TYPE_PcapReplay_Start	0x901
#define RESULT_TYPE_PcapReplay_Trip		0x902

typedef struct
{
	unsigned int nType;//1:故障前 2:故障中
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
	unsigned int nAlgCnt;			//模拟和SMV模块数量
	unsigned int nAlgTable[ALG_MODULE_MAX];
	unsigned int nBiCnt;			//开入模块数量
	unsigned int nBiTable[BIO_MODULE_MAX];
	unsigned int nBoCnt;				//开出模块数量
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

//开出值数据结构
typedef struct
{
	unsigned int nVal1;
	unsigned int nVal2;//开出值
} structBoStatusItem;

//开出量顶层数据结构
typedef struct
{
	structBoStatusItem item[BIO_MODULE_MAX];
} DrvComBoStatus;

typedef struct
{
	unsigned int nVal1;
	unsigned int nVal2;		//开出值
} structBIChangeItem;

//开入变位数据结构
typedef struct
{
	structBIChangeItem item[BIO_MODULE_MAX];
} DrvBIChange;

typedef struct
{
	unsigned int 	nStep;			//状态序列状态编号，仅状态序列相关模块使用
	unsigned int 	nDegressStep;		//递变步骤编号，递变模块和状态序列的递变都使用该数据指示
	unsigned int 	nType;			//结果类型，详见表3-1
	unsigned int 	nSource;			//触发源，详见表3-2
	unsigned int 	nSec;				//UTC时间秒值
	unsigned int 	nNanoSec;			//UTC时间纳秒值
	unsigned int    nGooseFlag;         //bit31-bit16 1:gse  0:bin  bit15-bit0 :SqNum
	DrvBIChange 	oBiChg;			//开入变位值，在source为开入变位时读该值
	Drv_BIStatus	nBi;				//开入量值
	DrvComBoStatus	nBo;				//开出量值
	Drv_BIStatus	nDi;				//Goose开入量值
} Drv_ResultItem;

/***********手动结构体***********/
#define ALG_PARAM_MAX		3442 //模拟或正弦参数数据 (DIGITAL_CHANNEL_MAX*3)*31=3441 + 1(ADMU)
//模拟数据和正弦参数结构
typedef struct
{
	unsigned int nDWcnt;			//有效数据个数，以32位为单位
	long dat[ALG_PARAM_MAX];
} Drv_HarmParam;

typedef struct
{
	unsigned int nModuleCnt;
	unsigned int nModule[ALG_MODULE_MAX];//有效数据个数，以32位为单位
	Drv_HarmParam oHarmParam[ALG_MODULE_MAX];
} Drv_HarmADMUFT3;//ADMUFT3正弦参数

//手动实验数据顶层结构
typedef struct
{
	Drv_HarmParam	oDrv_HarmParam[ALG_MODULE_MAX];
	DrvComBoStatus  oDrvComBoSta;
	long nPPSDelayTime;//守时开始前等待时间
	long nReLoadFT3;
	long nFT3Module;
	unsigned int nAuxVolt;//辅助直流
	Drv_HarmADMUFT3 oDrv_ADMUHarm;
} Drv_ManuData;
/***********手动结构体***********/

/***********开入触发手动结构体***********/
//开入有效位数据结构
typedef struct
{
	unsigned int nModule;
	unsigned int nVal1;
	unsigned int nVal2;		//有效位的值
} structBIValidItem;
typedef struct
{
	unsigned int nModuleCount;
	structBIValidItem item[BIO_MODULE_MAX];
} structBIValid;
//开入触发数据结构
typedef struct
{
	unsigned int nBiRef;			//0:翻转触发	 1：下降沿触发	2：上升沿触发
	unsigned int nBiLogic;		//0：开入或	1：开入与
	structBIValid oValid;			//有效通道
} DrvBITrip;

//手动实验开入量配置
//开入有效位数据结构
//顶层数据结构
typedef struct
{
	unsigned int nBinIsStop; //开入量收到后是否停止
	unsigned int nMdelay; //开入量收到后输出保持时间
	DrvBITrip oTrip; //触发
} Drv_ManuBin;
/***********开入触发手动结构体***********/

/***********状态结构体***********/
//开出翻转数据结构
typedef struct
{
	DrvComBoStatus	boValue;		//开出量状态值(nTripMode==2)或有效位(nTripMode==0,nTripMode==1)
	unsigned int 	nTripMode;		//0:时间触发 1：开入触发(暂时不用,预留) 2:按状态值输出 3:开出不动作
	unsigned int 	nPreTripTime;	//以本状态开始时做计时起点,触发前时间,单位毫秒(时间触发)
	//nPreTripTime>=0有效,时间结束翻转一次
	unsigned int 	nOutPutTime;	//触发后保持时间,单位毫秒(时间触发)
	//nOutPutTime>0有效,时间结束翻转一次
} Drv_BoFlip;

//整组实验配置参数顶层结构
typedef struct
{
	unsigned int    nStateCount;			//状态总数 固定为8
	unsigned int	nFaultTime;		//最大故障时间 ms
	unsigned int 	nTripTime;		//最大跳闸时间 ms
	unsigned int	nTransitionalTime; //转换时间 ms
	unsigned int 	bIsPermanent;        //是否永久故障    1： 永久  0 ： 瞬时故障
	unsigned int	bIsTransitionalFault;//是否是转换故障  1： 是    0 ： 不是
	unsigned int	nReclosingTime;		//重合闸定值 ms
	unsigned int 	nStopTime;			//停止态持续时间 ms
	unsigned int	nIsLoop;				//是否循环
	unsigned int	nbiRefFirst;
	Drv_BIStatus	oGooseInit;			//goose开入初始值
} Drv_CboperPara;

//配置参数顶层结构
typedef struct
{
	unsigned int nStateCount;			//状态总数
	unsigned int nIsLoop;				//是否循环
	unsigned int nbiRefFirst;
	unsigned int nIsSequence;			//默认0 ,1: 表示顺序控制需要特殊处理
	Drv_BIStatus oGooseInit;			//goose开入初始值
} Drv_StatePara;

//状态序列状态数据
//GPS和时间联合体定义
typedef struct
{
	unsigned int nSec;			//GPS触发秒值
	unsigned int nNsec;			//GPS触发纳秒值
	unsigned int nReserve;
} structGPS;
typedef struct
{
	unsigned int nMsec;				//时间触发毫秒值
	unsigned int nUsec;             //时间触发微秒值
	unsigned int nDelay;			//开入触发延时时间,毫秒
} structTime;
typedef union
{
	structGPS	oGps;				//GPS触发
	structTime	oTime;				//时间触发
} unionTm;

#define StateAcDataBufLen 336//48+48*3*2
#define StateDegressMinStep 0.0000009
//状态序列输出数据结构
typedef struct
{
	unsigned int 	DWCount;			//有效数据长度
	unsigned int    nPhase;//合闸角
	unsigned int	nexpconfig;//非周期分量设置
	long    nexp[12];//12路非周期分量
	long	nVal[StateAcDataBufLen];		//输出数据
} structACParamItem;

typedef struct
{
	structACParamItem item[ALG_MODULE_MAX];
} Drv_StateACPara;

//状态序列递变数据结构
typedef struct
{
	unsigned int 	nIsChange;			//0:不递变			1：递变

	unsigned int 	nCount[StateAcDataBufLen];				//递变次数
	long			changeVal[StateAcDataBufLen];		//递变值，详见说明
	long			lastVal[StateAcDataBufLen];			//终止值，详见说明
} Drv_StateDeg;

typedef struct
{
	unsigned int nModulesCnt;    //模块数
	unsigned int nModule[ALG_MODULE_MAX];
	structACParamItem	oADMUACPara[ALG_MODULE_MAX];	//正弦输出参数
	Drv_StateDeg        oADMUStChange[ALG_MODULE_MAX];	//状态序列递变参数
} Drv_StateADMUPara;

//状态序列触发类型
#define State_Trig_Manual          0x001
#define State_Trig_Bin             0x002
#define State_Trig_TimeDelay       0x100
#define State_Trig_GPS             0x200
#define State_Trig_Bin_TimeDelay   0x102
#define State_Trig_GPS_TimeDelay   0x202
//说明：状态序列递变可以同时变化频率和幅值，changVal和lastVal数据排列顺序为：
//模拟模块：6直流分量+（频率+幅值）*（DWCount-6）；
//SMV模块：（频率+幅值）*DWCount;
typedef struct
{
	unsigned int        nTirpType;			//触发源设置，见表5-1
	DrvBITrip           obiTrip;				//开入触发设置
	unionTm             oTm;					//时间和GPS触发相关数据
	unsigned int        nChangemSec;		//状态序列递变时间分度，单位毫秒
	unsigned int		nBoType;			//0:Bo+Gse,1-Bo,2-Gse
	Drv_BoFlip          oStBo;				//开出参数
	Drv_StateDeg        oStChange[ALG_MODULE_MAX];		//状态序列递变参数
	Drv_StateACPara 	oAcParam;			//模拟输出参数
	DrvGseChgParas      oGseChgParas;			//goose变位信息
	unsigned int        nGseChgValid;       //1有效
	DrvFT3ChgParas      oFt3ChgParas;
	unsigned int        nFt3ChgValid;       //1有效
	Drv_GseTest         GooseTest;
	unsigned int        nAuxVolt;//辅助直流

	Drv_AbnPara			oAbnPara;//异常模拟参数结构
	Drv_StateADMUPara	oADMUPara;//Ft3正弦量
} Drv_StateItem;

/***********状态结构体***********/

/***********故障回放结构体***********/

typedef struct
{
	unsigned int tripType;        //0 无触发 1 manu(手动)2 bi(开入) 3GPS(GPS)
	DrvBITrip stBITrip;				//开入触发配置
	int tripLoopCount;          //循环次数
	int modeAfterTrip;
	unsigned int tripgpsSec;      //GPS触发
	unsigned int tripgpsnSec;
	unsigned int freq;           //播放频率
	unsigned int moduleCount;	 //模块数量
	unsigned int module;	 //模块
	DrvComBoStatus  oDrvComBoSta;
} Drv_LtReplayParam;

typedef struct
{
	unsigned int module;
	unsigned int ch;
} Drv_ComReplayCh;

typedef struct
{
	unsigned int tripType;        //0 无触发 1 manu(手动)2 bi(开入) 3GPS(GPS)
	DrvBITrip stBITrip;				//开入触发配置
	unsigned int tripgpsSec;      //GPS触发
	unsigned int tripgpsnSec;
	Drv_ComReplayCh ch[ALG_MODULE_MAX];//模块回放通道设置
	unsigned int StopTime;      //实验结束时间
	unsigned int freq;
	unsigned int loopCount;     //循环次数
	unsigned int SOL1;//循环开始位置
	unsigned int EOL1;//循环结束位置
} Drv_ComReplayParam;

/***********故障回放结构体***********/

/***********递变实验参数结构体***********/
typedef struct
{
	unsigned int nDWcnt;			//有效数据个数，以32位为单位
	long bfChangedat[ALG_PARAM_MAX];//变化前数据
	long bfFaultdat[ALG_PARAM_MAX];//故障前数据
	long FaultBegindat[ALG_PARAM_MAX];//故障开始数据

	//Amp Ang Fre只有一种递变
	long nFaultChangVal[ALG_PARAM_MAX];//故障递变数据
	long nFaultLastVal[ALG_PARAM_MAX];//故障最后一步递变数据
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
	unsigned int 		cnt;						//递变次数
	unsigned int        mode;						//0-相对递变  1-绝对值递变
	unsigned int 		isReturn;					//0：收到开关量不返回	1：收到开关量反向递变
	DrvBITrip			trip;						//开入触发参数
	unsigned int 		timeDiv;					//递变时间分度，单位毫秒
	unsigned int 		timeBfChg;					//变化前时间毫秒值
	DrvComBoStatus		boBfChange;					//变化前开出状态数据
	unsigned int 		timeBfFault;				//故障前时间毫秒值
	DrvComBoStatus		boBfFault;					//故障前开出状态数据
	DrvComBoStatus		boFault;					//故障态开出状态数据
	unsigned int 		boFaultFlipSec;				//开出翻转时间秒值
	unsigned int 		boFaultFlipnSec;			//开出翻转时间纳秒值
	Drv_ACPara		    AcPara;						//线性模式电气量数据
	Drv_DegData			DegData[GRADIENT_MAX_COUNT];//非线性模式电气量数据
} DrvDegressPara;
/***********递变实验参数结构体***********/

/***********振荡实验参数结构体***********/
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
	unsigned int 	shakeCount;					//震荡步数
	unsigned int 	isRecip;					//1：往复震荡	0：非往复震荡
	unsigned int 	timeDiv;					//变化时间间隔微秒值
	unsigned int 	timeBfShake;				//震荡前时间毫秒
	unsigned int 	shakeMax;					//震荡步数
	unsigned int 	faultMax;					//故障步数
	DrvBITrip		stBITrip;					//开入触发条件
	Drv_ShakePara	bfShake;					//震荡前参数
	Drv_ShakePara	shake[SHAKE_MAX];			//震荡数据
	Drv_ShakePara	fault[SHAKE_MAX];			//故障数据
	DrvComBoStatus  oDrvComBoSta;
} Drv_Swing;
/***********振荡实验参数结构体***********/

/***********同期实验参数结构体***********/
typedef struct
{
	unsigned int DWCount;
	long Begindat[111]; //开始数据
	long StepAmp[111]; //0 步长
	long StepFre[111]; //1 步长
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
	unsigned int 	RunType;	//0:边界值测试	1：调压周期   2：调频周期  3:自调整
	unsigned int 	StepType; //RunType == 0,0、1、2、3
	unsigned int 	StepTime; //RunType == 0
	structSyncBo    stBo;
	structTripDI 	trip;
	Drv_SyncAcData	stData;
	Drv_ParaRef   stParaRef;
} Drv_SyncParam;

/***********同期实验参数结构体***********/

/***********扩展开关量板SOE实验参数结构体***********/
typedef struct
{
	unsigned int nTmHigh;				//高电平时间长度毫秒
	unsigned int nTmLow;				//低电平时间长度毫秒
	unsigned int nflipCnt;				//翻转次数
} Drv_BoPara;

typedef struct
{
	unsigned int nModule;			//模块编号
	unsigned int nBinOut[2];				//开出初始值
	unsigned int nType[2];			//实验类型 0其它，1为SOE实验
	Drv_BoPara param[64];
	unsigned int nDelayTime;//故障前时间
	unsigned int nBeginTime[64];//间隔时间
} Drv_SoeExItem;

typedef struct
{
	unsigned int nTripType;//0: 立即触发 1: GPS 触发
	unsigned int nModuleCnt;//模块数
	unsigned int nMode;//0-MainBoard  1-ExBoard  2-Goose
	unsigned int nUseBiRes;//0-No 1-Yes
	unsigned int nGPS_Sec;//GPS 触发时间秒值
	unsigned int nGPS_Nsec;//GPS 触发时间纳秒值
	unsigned int nHoldTime;//持续时间秒值
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
	Tmt_SoePara oTmt_SoePara[8];//8个开出
} Tmt_SoeParas;

/***********扩展开关量板SOE实验参数结构体***********/

typedef struct
{
	double dTime; //绝对时刻
	double dLastBinTime; //当前故障态最后一个开入事件的绝对时刻
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

	//模拟量插件在用交流位置出直流时不需要再重复计算直流零漂
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
		//停止实验后重置秒同步配置
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
