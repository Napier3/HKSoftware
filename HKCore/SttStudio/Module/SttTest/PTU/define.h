#ifndef DEFINE_H
#define DEFINE_H


#define NANOSECOND 1.0e9
#define HRM_MAX      31                    //总谐波次数
#define CHANNEL_MAX     6                        //通道数
#define MODULE_MAX      8                        //模块数
#define STATECOUNT 500
#define DGRESS_MAX 3000

#define RESULT_START          1
#define RESULT_STOP           2
#define RESULT_BI_CHANGE      6
#define RESULT_STATE_CHANGE   7

/***
typedef struct{
	unsigned int module;							//模块编号，0：电压	1：电流
	long nDc[6];
	long dat[558];			//数据，数据格式和PN466A相同
}Drv_ManuAnalogPara;
***/

typedef struct{
	unsigned int module;							//模块编号，0：电压	1：电流
	long dat[1500];			//数据，数据格式和PN466A相同
}Drv_ManuAnalogPara;

typedef struct{
	unsigned int moduleCount;				//模块总数
	unsigned int sample;						//采样速率，sample = 40000/F, F为交流频率
	unsigned int waveCount[8]; 				//每个模块每个通道最大波形个数，同PN466A
	Drv_ManuAnalogPara stAlg[8];				//模拟数据结构
}Drv_ManuPara;



/*放大器电压设置，同PN466A*/
typedef struct{
    unsigned int voltAmp;
    unsigned int currentAmp;
}ampPower;

typedef struct{	
	unsigned int type;					//1:start  2:stop  6:开入变位
    unsigned int step;					//指示状态序列的第几个状态，手动实验填0
    unsigned int source;					//状态序列触发值，0：手动触发，1：时间触发 2：GPS触发3：开入量触发
	unsigned int nSec;						//UTC sec
	unsigned int nNanoSec;					//UTC nSec
    unsigned int biValue;					//开关量的值
}Drv_ResultItem;

typedef struct{
	unsigned int nCount;
	Drv_ResultItem stResult[500];
}Drv_Result;   //返回结果


typedef struct{
    unsigned int acInMode;		//开入模式
    unsigned int acInStall1;		//档位1
    unsigned int acInStall2;		//档位2
}structACinSet;					//设置采集档位见FPGA 0x70004070，0x70004074，0x70000407C
typedef struct{
    unsigned int rms[8][2];		//采集有效值8路，每路2个32位值
    unsigned int inst[8];			//瞬时值8路，每路1个32位值
    long dc[3];					//直流电压、电流、纹波
    unsigned int sec;
    unsigned int nsec;
}structSmp;								//采集值

typedef struct{
    unsigned int dat[12];
}structAmp;							//放大器监控电压，见FPGA电压电流放大器监控电压

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

/***
typedef struct{
	unsigned int module;			//模块编号
	long nDc[6];
	long dat[18];				//模拟数据6个通道直流值加六个通道相位、幅值、频率
}Drv_StateAnalogPara;
***/

typedef struct{
	unsigned int module;			//模块编号
	unsigned int cnt;
	long dat[6+3*6*2];				//模拟数据6个通道直流值加六个通道相位、幅值、频率
}Drv_StateAnalogPara;

typedef struct{
	unsigned int state;			//状态号
	unsigned int trip;				//触发类型	0：手动1：时间2：GPS	3:	开入量
	union {						//触发参数，见上面三个结构体
		structBITrip	bi;
		structGPSTrip 	gps;
		structTmTrip	tm;
	}tripData;
	unsigned int mdelay;			//开入触发有延时时的延时时间毫秒值
	unsigned int BO;				//开出量值
	Drv_StateAnalogPara dat[8];		//模拟数据
}Drv_StatePara;
typedef struct{
	unsigned int stateCount;			//状态数
	unsigned int moduleCount;		//模块数
	unsigned int isLoop;				//是否循环
	Drv_StatePara state[500];
}Drv_StateParas;
//~~~~~~~~~~~~~~~ soe
typedef struct{
      unsigned int val;            //开出值             0：断开            1：闭合
      unsigned int sec;            //持续时间秒值
      unsigned int nSec;            //持续时间纳秒值
}Drv_SoeState;

typedef struct{
      unsigned int isValid;            //该通道是否有效            1；有效            0：无效
      unsigned int cnt;                  //循环次数
	  Drv_SoeState state[3];
}Drv_ChanState;

typedef struct{
      unsigned int type;            //0:立即实验      1:GPS触发实验开始
      unsigned int tm_h;            //GPS time Sec
      unsigned int tm_l;            //GPS time nSec
	  Drv_ChanState st[8];
}Drv_SOETest;

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
    unsigned int pos[50];
    //通道位置
    long nData[50];               		 //通道值
}structRampDigitalUnit;

typedef struct RampPara
{
    structRampAlgUnit AnalogRamp[MODULE_MAX];
}RAMPPARA;

typedef struct
{
    long dat[24];
}structDegAlg;

typedef struct
{
    long dat[75];
}structDegSMV;

typedef struct
{
    structDegAlg alg[MODULE_MAX];
}structDegNormal;



typedef struct
{
    unsigned int nModuleCount;					//模拟模块总数 重要 如果是0会导致不输出
    unsigned int nRampCount;							//递变个数
    unsigned int nReturnStop;								//开关量是否触发返回
    unsigned int nInputRef;						//开关量参考，0：反转	1：上升沿    2：下降沿
    unsigned int nLogic;						//开关逻辑，0：开入与	1：开入或
    unsigned int nEffective;						//有效通道
    unsigned int diMsDelay;        //新增，开入触发后延时时间
    unsigned int nTimeSize;					//递变时间分度
    unsigned int timeBfChg;        //递变前时间，单位毫秒
    structDegNormal bfChange;  //递变前参数
    unsigned int timeBfFault;       //故障前时长，单位毫秒
    structDegNormal bfFault;        //故障前的值
    RAMPPARA stAlg[DGRESS_MAX];			//递变数据，最大3000个递变
}structRamp;

typedef struct{
    unsigned int nStep;		//当前处于第几次递变
    unsigned int nType;		//1:start  2:stop  3:状态变化  4:开入变位  5:start to return 6:递变故障前
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

#endif // DEFINE_H

