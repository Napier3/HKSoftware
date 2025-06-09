#ifndef DEFINE_H
#define DEFINE_H

#include<QVector>

//程序版本命名规则::<名称>_<主版本号>.<子版本号>_<日期版本号>
//完整的版本号存放在device类 m_strVersion变量
#define MAINVERSIONCODE 1
#define CHILDVERSIONCODE 1

extern int g_nVChannel[12];
extern int g_nIChannel[12];
extern int g_nDCIChannel[12];
extern int g_nDCVChannel[12];
extern int g_nIInnerVoltChannel[12];
extern int g_nVInnerVoltChannel[12];


typedef struct{
    unsigned int group;
    unsigned int nLen;
    unsigned char dat[1024];
}structFt3Send;

typedef struct{
    unsigned int module;
    unsigned int groupCnt;
    structFt3Send ft3[12];
}structFt3DataConfigItems;

typedef struct{
    unsigned int nModuleCount;
    structFt3DataConfigItems datModules[4];
}structStateFt3Item;


typedef struct{
       unsigned int module;   //模块编号
       int       dat[6];
}structDCParams;

typedef  struct{
       unsigned int        moduleCount;       //模块数
       structDCParams       param[4];
}structDC;

typedef struct{

       structDCParams       dcParams[4];

} structDCPara;

//abnormal
typedef struct{
    unsigned int	npoint;			//异常点号0～79
    unsigned short lost;	//丢帧  1为丢帧；0为正常
    unsigned short	jitter;	//抖动 0 不抖动 1为0.1us，250us写入2500
    int errcmpt;   //错序   -1999 到 2000 0为非错序
    unsigned int flypoint;//飞点使能
    int		 nflyPointVValue;		//飞点电压值
    int		 nflyPointIValue;		//飞点电流值
}svabnunit;
typedef struct
{
    unsigned int   nmodule ;//数字模块编号，默认
    unsigned int  ptCnt;     //异常点数
    svabnunit	smv_abnormal[80];	//每周波各点的异常设置  
    int  ngroup;//SMV组号 8bit有效，0无效 1使能 如 0011 则是第一第二组使能，其他无效。
    unsigned int   nabnormalcircle ;//异常周波数
    unsigned int   nnormalcircle;// 正常周波数
    unsigned int   nroopcount ;//循环个数

}structsmvabnormal;
typedef struct
{
    int ngoosemodule;
    int ngroup ;//goose group
    int ngooselen;
    char goosebuf[1520];//goose out buffer
    int nTimePos;

}structgooseabnormal;


typedef struct{
    unsigned int module;				//模块编号
    unsigned int reserved[3]; 			//占位数据，全部填0，用于驱动层填充报文头
    unsigned int smvset[2];			//SMV光口配置
    unsigned int gooseset[4];           //GOOSE光口配置，详见SV/GOOSE配置信息
}config;


//SMV发送配置信息
typedef struct{
    unsigned int module;				//模块编号
    unsigned int reserved[3];			//占位数据
    unsigned int sampleCount;			//采样计数和采样间隔
    unsigned int smvsamplebegin[4];				//采样计数器初值
}smvConfig;
//详细解释见FPGA寄存器协议 SMV发送配置信息
//goose发送配置信息
typedef struct{
    unsigned int module;				//模块编号
    unsigned int reserved[3];			//占位数据
    unsigned int GooseTime[4];
}gooseConfig;
//FT3发送配置信息
typedef struct{
    unsigned int module;				//模块编号
    unsigned int reserved[3];			//占位数据
    unsigned int sampleCnt;
    unsigned int baud;
    unsigned int dat[6];
}ft3Config;


typedef struct stateParaUnitAbnormal{
        unsigned long nStateNum;                                    //状态序列序号，0开始
        // 0 manual 1 time 2 gps 3 bin or 4 bin and
        unsigned long nTirpType;                                 //触发条件表，相应位置填写需要跳转到的状态
        unsigned long nReversal;                                    //开入翻转参考设置:
            //0：开入翻转触发wa
            //1：开入上升沿触发
            //2：开入下降沿触发
        unsigned long  nOrValid;               //开入或触发有效位
        unsigned long nAndValid;                                    //开入与触发有效位选择bit9~bit0对应通道9~通道0 
        unsigned long nGpsSec;                                      //GPS触发秒值
        unsigned long nGpsnSec;                                     //GPS触发纳秒值
        unsigned long nTimemSec;                                    //时间触发毫秒值
        unsigned long nDelay;                                       //开入触发延时时间，开入条件满足后延时多长时间触发
        ANALOGBOSETTING oBo;

        ACANALOGPARA acAnalog;                          //模拟参数
        ACDIGITALPARA  acDigital;			//数字参数
        int abnormaltype;           //0 zhengchang smv abnormal1  goose abnormal 2
        stateGooseChangedItem GooseChangedItem;// abnormaltype=0 valid
        datAbnormalConfigs oabnormalcomfig;

        structsmvabnormal osmvabnormal;//abnormaltype=1 valid
        structgooseabnormal ogooseabnormal;//abnormaltype=2 valid
        int nsendconfig;
        smvConfig oconfig;
        stateParaUnitAbnormal()
        {
            oBo.nBoValue = 0xFFFFFFFF;
            nStateNum = 0;
            nTirpType = 0;
            nReversal = 0;
            nAndValid = 0;

            nGpsSec = 0;
            nGpsnSec = 0;
            nTimemSec = 0;
            nDelay = 0;
            memset(&oBo,0,sizeof(ANALOGBOSETTING));
            memset(&acAnalog,0,sizeof(ACANALOGPARA));
            memset(&acDigital,0,sizeof(ACDIGITALPARA));
            memset(&GooseChangedItem,0,sizeof(stateGooseChangedItem));
        }
}structStateAbnormal;
typedef struct structStateAbnormalParam{
        unsigned long nModuleCount;				//模块总数
        unsigned long nStateModuleCount;        //数字模块
        unsigned long nStateCount;				//状态总数
        unsigned long nloop;
        unsigned long nReverRefence;                                //0 参考第一个状态 1参考上一个状态
        unsigned long noriginal;                //GOOSE init Value;
        ANALOGBOSETTING oBo;
        structStateAbnormal stState[STATECOUNT];				//状态
        structStateAbnormalParam()
        {
            oBo.nBoValue = 0xFFFFFFFF;
        }
}structStateAbnormalParam;
//状态序列结果参数



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//模拟量手动输出谐波定义
typedef struct{
        unsigned int nModule;						//模块编号
        unsigned int nWave;						//模块编号
        long nData[HRM_MAX*3*CHANNEL_MAX+CHANNEL_MAX];                //基波与谐波
}structAnalogHarm;

typedef struct AnalogHarmPara
{
    unsigned int nCount;            //模块数
    unsigned int nAnalogBO;
    structAnalogHarm oAnalogHarm[MODULE_MAX];
}ANALOGHARMPARA;

//数字量多次谐波及基波
typedef struct{
    unsigned int module;// 模块编号
    unsigned int ncount;// 模块编号
    unsigned int hrmDat[HRM_MAX*DIGITAL_CHANNEL_MAX * 3];
}structSinDataHarmItem;

typedef struct DigitalHarmPara
{
    unsigned int nCount;            //模块数
    structSinDataHarmItem oHarm[DIGITAL_MODULE_MAX];
}DIGITALHARMPARA;

typedef struct BIInSetting
{
    unsigned int nIsStop;                                       //开入量进来是否停止
    unsigned int nDelay;                                        //开入量进来延时时间后停止
    unsigned int nIsSend0whenStop;
    unsigned long nReversal;                                    //开入翻转参考设置:
        //0：开入翻转触发wa
        //1：开入上升沿触发
        //2：开入下降沿触发
    unsigned long nAndValid;                                    //开入与触发有效位选择bit9~bit0对应通道9~通道0
    unsigned long nOrValid;                                     //开入或触发有效位选择bit9~bit0对应通道9~通道0

    unsigned long nDigitalAndValid;                             //GOOSE开入与触发有效位选择bit31~bit0对应通道31~通道0
    unsigned long nDititalOrValid;                              //GOOSE开入或触发有效位选择bit31~bit0对应通道31~通道0
}BIINSETTING;


typedef struct{
        unsigned int nModule;					 //模块编号
        unsigned int nPosCount;
        unsigned int pos[18];
        //通道位置
        long nData[18];               		 //通道值
}structRampAlgUnit;
typedef struct {
    unsigned int nModule;					 //模块编号
    unsigned int nPosCount;
    unsigned int pos[74];
    //通道位置
    long nData[74];               		 //通道值
}structRampDigitalUnit;

typedef struct RampPara
{
    structRampAlgUnit AnalogRamp[MODULE_MAX];
    structRampDigitalUnit DigitalRamp[DIGITAL_MODULE_MAX];
}RAMPPARA;



typedef struct{
    unsigned int nStep;		//当前处于第几次递变
    unsigned int nType;		//1:start  2:stop  3:状态变化  4:开入变位  5:start to return 6:递变故障前 7 切换到振荡态 8切换到故障
    unsigned int nSec;		//时间秒值
    unsigned int nNanoSec;		//时间毫秒值
    unsigned int nInput;			//开入值
    unsigned int nGoose;            //GOOSE bi;
    unsigned int nSource;       //变位bit
}structRampResult;


typedef struct
{
    float famptitude;//fuzhi
    float fphase;
    float ffre;
}oChannel;


struct structVersion{
   unsigned int flag;
   unsigned int version[10];
};

#define SHAKE_ALG_PARA_CNT    24
#define SHAKE_DIG_PARA_CNT    75
#define SHAKE_MAX                5000

typedef struct{
    long dat[SHAKE_ALG_PARA_CNT];
}structShakeAlg;

typedef struct{
    unsigned int dat[SHAKE_DIG_PARA_CNT];
}structShakeSMV;

typedef struct{
    structShakeAlg alg[MODULE_MAX];
    structShakeSMV smv[DIGITAL_MODULE_MAX];
}structShakePara;

typedef struct{
    unsigned int algCount;                    //模拟模块数量
    unsigned int digCount;                    //数字模块数量
    unsigned int shakeCount;                //振荡步骤数
    unsigned int nBinaryInput;
    unsigned int isRecip;                    //是否往复振荡
    unsigned int timeDiv;                    //变化时间间隔 namiao
    unsigned int timeBfShake;                //振荡前时长 haomiao
    unsigned int timeShake;                //故障前振荡时长 buchang
    unsigned int timeFault;                //故障态时长  buchang
    unsigned int algModule[MODULE_MAX];    //模拟模块选择
    unsigned int digModule[DIGITAL_MODULE_MAX];    //数字模块选择
    structShakePara bfShake;                //振荡前数据
    structShakePara shake[SHAKE_MAX];        //振荡数据
    structShakePara falut[SHAKE_MAX];        //故障态
}structShake;


typedef struct{
    unsigned int nTmHigh;				//高电平时间长度毫秒
    unsigned int nTmLow;				//低电平时间长度毫秒
    unsigned int nflipCnt;				//翻转次数
}structSoeParam;

typedef struct{
    unsigned int nModule;			//模块编号
    unsigned int nBinOut[2];				//开出初始值
    unsigned int nType[2];			//实验类型 0其它，1为SOE实验
    structSoeParam param[64];
}structSoeItem;

typedef struct{
    unsigned int nModuleCnt;		//模块数
    unsigned int tm_h;		//持续时间秒值
    unsigned int tm_l;		//持续时间纳秒值
    structSoeItem item[4];
}structSoe;


typedef struct{
    unsigned int module;			//模块编号
    unsigned int bo[2];				//开出值
    unsigned int bi[2];				//开入值
}structSoeResultItem;


typedef struct{
    unsigned int nType;			//结果类型 1：开始   2：停止	3：开出变位	4：开入变位
    unsigned int nModuleCnt;
    unsigned int tm_h;			//时间秒
    unsigned int tm_l;			//时间纳秒
    structSoeResultItem item[4];
}structSoeResult;



typedef struct{
    unsigned int module;
    long dc[CHANNEL_MAX];
    long ac[3 * CHANNEL_MAX];
}structAlg;

typedef struct{
    unsigned int module;
    long ac[3 * DIGITAL_CHANNEL_MAX];
}structDig;

typedef struct{
    unsigned int nalgCnt;
    unsigned int ndigCnt;
    structAlg alg[MODULE_MAX];
    structDig dig[DIGITAL_MODULE_MAX];
}structData;

typedef struct{
    unsigned int tm_h;
    unsigned int tm_l;
    unsigned int temp1;
    unsigned int temp2;
}structTripTime;
typedef struct{
    unsigned int nIncAmp;
    unsigned int nIncFre;
    unsigned int nSubAmp;
    unsigned int nSubFre;
}structTripDI;

typedef union{
    structTripTime  stTm;
    structTripDI	stDi;
}unionTrip;
typedef struct{
    unsigned int type;			//0:时间触发	1：开入量触发
    unsigned int nTripTime;
    unsigned int stopDI;
    unionTrip trip;				//
    structData	stInit;			//初始值
    structData	stIncAmp;			//增速值
    structData  stIncFre;
    structData	stSubAmp;			//减速值
    structData  stSubFre;
}structSyncParam;

typedef struct{
    long algPhase[MODULE_MAX][CHANNEL_MAX];
    long digPhase[DIGITAL_MODULE_MAX][DIGITAL_CHANNEL_MAX];
}structPhase;

typedef struct{
    unsigned int type;	//1:开始	2:停止	3:增速	4:减速
    unsigned int tm_h;
    unsigned int tm_l;
    unsigned int bi;
    unsigned int bo;
    structPhase	stPhase;
}structSyncResult;



#endif // DEFINE

