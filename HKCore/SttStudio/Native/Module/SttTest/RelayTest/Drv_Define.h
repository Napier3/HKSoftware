#ifndef DRV_DEFINE
#define DRV_DEFINE


#define STATE_TYPE_START            0x01
#define STATE_TYPE_STOP             0x02
#define STATE_TYPE_CHANGE           0x03
#define STATE_TYPE_DI_CHANGE        0x04
#define STATE_TYPE_DGRESS_DI        0x05
#define STATE_TYPE_GS_CHANGE        0x06
#define STATE_TYPE_STATE_DEGRESS    0x07
#define STATE_TYPE_DO_CHANGE        0x08
#define STATE_TYPE_DEGRESS_START    0x09
#define STATE_TYPE_DEGRESS_STOP     0x0A


#define STATECOUNT 500
#define DIGITAL_MODULE_MAX		 4			//插件数
#define CHANNEL_MAX     6                        //通道数
#define DIGITAL_CHANNEL_MAX		37			//Ua,Ub,Uc,Ia,Ib,Ic...50个通道
#define MODULE_MAX      8                        //模块数
#define CHANELMAXCHANGED 256

#define STATE_RESULT_MAX  100

namespace DRV_STATE {

typedef struct
{
	unsigned int pos;
	unsigned int value;
	unsigned int gorup;
}DrvGseTestData;

typedef struct
{
	unsigned int module;
	unsigned int nCount;
	DrvGseTestData gs[16];
}DrvGseTestItem;

typedef struct
{
	unsigned int nCount;
	DrvGseTestItem dat[DIGITAL_MODULE_MAX];
}DrvGooseTestItems;

typedef struct
{
	unsigned int nBoValue;   //0 open   1 close; 开出有效位
	unsigned int nreverse;   //0 unreverse 1reverse 2 是否开出状态翻转
	unsigned int ntrigerMode; //0 time  1 biChanged;
	unsigned int ntimeDelay; //开出状态翻转保持时间
	unsigned int nHoldTime;
}DrvAnalogBoSetting;

typedef struct{                                                //递变参数
	unsigned int nIsChange;					//是否递变标志, 0:不递变			1：递变
	unsigned int nModule;					//模块编号
	unsigned int  nChangeCount;				//变化次数 电压递变次数
	unsigned int ndfcount;                  //频率递变次数
	long nChangeValue[CHANNEL_MAX*3*2+CHANNEL_MAX];     	//变化量
	long nLastChangeValue[CHANNEL_MAX*3*2+CHANNEL_MAX];     	//最后一步变化量
}DrvChange;

typedef struct{
	unsigned int isChange;
	unsigned int module;
	unsigned int count;
	unsigned int ndfcount;
	long		 changeValue[DIGITAL_CHANNEL_MAX * 3*2];
	long     nLastChangeValue[DIGITAL_CHANNEL_MAX * 3*2];     	//最后一步变化量
}DrvDigitalChange;

//模拟量一次谐波及基波定义
typedef struct{
	unsigned int nModule;						//模块编号
	//long nDc[CHANNEL_MAX];                      //直流分量
	unsigned int nclsPhase;                               //合闸角度
	unsigned int nexpconfig;                        //非周期分量设置
	long nexp[6];                                         //非周期分量
	long nData[4*CHANNEL_MAX];
	long nHarmData[3*CHANNEL_MAX];                //基波与一次谐波
}DrvAnalogItem;

typedef struct{

	DrvAnalogItem oModuledata[MODULE_MAX];
}DrvAcAnalogPara;

//数字量一次谐波及基波定义
typedef struct{
	unsigned int module;// 模块编号
	unsigned int nclsPhase;        //合闸角度
	unsigned int nexpconfig;                        //非周期分量设置
	long nexp[12];                 //非周期分量
	unsigned int dat[DIGITAL_CHANNEL_MAX * 3];
	unsigned int hrmDat[DIGITAL_CHANNEL_MAX * 3];
}DrvSinDataItem;
//ACDigitalPara
typedef struct
{
	//unsigned int nBO;
	DrvSinDataItem oModuledata[DIGITAL_MODULE_MAX];
}DrvAcDigitalPara;

typedef struct {
	unsigned int nPos;
	unsigned int nCount;
	unsigned char dat[20];
}DrvChanelChanged;

typedef struct {
	unsigned int count;				//数据个数
	unsigned int group;				//数据组编号
	DrvChanelChanged dat[CHANELMAXCHANGED];
	unsigned int nUTCChanelCount;     //如果为0,不用打时标
	unsigned int UTCChanelPos[CHANELMAXCHANGED];  //需要打时标的位置
}DrvDatChanged;

typedef struct{
	unsigned int module;			//模块编号
	unsigned int group;				//组数总和
	DrvDatChanged dat[16];				//数据信息，详见SV/GOOSE数据信息
}DrvGooseChangedItem;

typedef struct{
	unsigned int nModuleCount;    //模块数
	DrvGooseChangedItem datModules[4];
}DrvGooseChangedItems;         //状态序列每个状态预设的GOOSE变位参数

typedef struct{
	unsigned int group;
	unsigned int nLen;
	unsigned char dat[1024];
}DrvFt3Send;

typedef struct{
	unsigned int module;
	unsigned int groupCnt;
	DrvFt3Send ft3[12];
}DrvFt3DataConfigItem;

typedef struct{
	unsigned int nModuleCount;
	DrvFt3DataConfigItem datModules[4];
}DrvStateFt3Items;

//状态序列参数
typedef struct DrvParaUnit{
	unsigned long nStateNum;                                    //状态序列序号，0开始
	// 0 manual 1 time 2 gps 3 bin or 4 bin and
	unsigned long nTirpType[7];                                 //触发条件表，相应位置填写需要跳转到的状态
	unsigned long nReversal;                                    //开入翻转参考设置:
	//0：开入翻转触发wa
	//1：开入上升沿触发
	//2：开入下降沿触发
	unsigned long nAndValid;                                    //开入与触发有效位选择bit9~bit0对应通道9~通道0
	unsigned long nOrValid;                                     //开入或触发有效位选择bit9~bit0对应通道9~通道0

	unsigned long nParaTripLogic;                               //变量触发逻辑
	unsigned long nTripPara;                              //GOOSE开入或触发有效位选择bit31~bit0对应通道31~通道0

	unsigned long nGpsSec;                                      //GPS触发秒值
	unsigned long nGpsnSec;                                     //GPS触发纳秒值
	unsigned long nTimemSec;                                    //时间触发毫秒值
	unsigned long nDelay;                                       //开入触发延时时间，开入条件满足后延时多长时间触发
	unsigned long nChangemSec;                                  //按时间递变时，递变时间分度, 单位毫秒
	DrvAnalogBoSetting oBo;
	DrvChange stChange[MODULE_MAX];                          //递变参数
	DrvDigitalChange stDigitalChange[DIGITAL_MODULE_MAX];
	DrvAcAnalogPara acAnalog;                          //模拟参数
	DrvAcDigitalPara  acDigital;			//数字参数
	DrvGooseChangedItems GooseChangedItems;
	DrvStateFt3Items ft3ChangedItems;
	DrvGooseTestItems GooseTestItems;
}DrvState;

//状态序列设置总参数
typedef struct DrvStatePara{
	unsigned long nModuleCount;				//模拟模块
	unsigned long nStateModuleCount;        //数字模块
	unsigned int  nDcmodule;              //直流模块
	unsigned long nStateCount;				//状态总数
	unsigned long nSequence;				//是否为顺序状态序列，1：是		0：不是
	unsigned long nloop;
	unsigned long nReverRefence;                                //1 参考第一个状态 0参考上一个状态
	unsigned long noriginal;                //GOOSE init Value;
	DrvAnalogBoSetting oBo;
	DrvState stState[STATECOUNT];				//状态
	DrvStatePara()
	{
		oBo.nBoValue = 0xFFFFFFFF;
	}
}DrvStateParam;

typedef struct{
	unsigned int type;
	unsigned int source;
	unsigned int sec;
	unsigned int nSec;
	unsigned int biValue;
	unsigned int gsValue;
	unsigned int from;
	unsigned int to;
	unsigned int uiDo;
	unsigned int degressStep;
}DrvResultItem;

typedef struct{
	unsigned int cnt;
	DrvResultItem result[STATE_RESULT_MAX];
}DrvResultItems;
}


#endif // DRV_DEFINE

