#ifndef DRV_DEFINE
#define DRV_DEFINE

#include "tmt_state_test.h"
#include "../../SttDevice/RelayTest/drv_define.h"


typedef struct
{
	unsigned int pos;
	unsigned int value;
	unsigned int group;
}drv_gsetestdata;

typedef struct
{
	unsigned int module;
	unsigned int nCount;
	drv_gsetestdata gs[16];
}drv_gsetestitem;

typedef struct
{
	unsigned int nCount;
	drv_gsetestitem dat[DIGITAL_MODULE_MAX];
}drv_gsetestitems;

typedef struct
{
	unsigned int nBoValue;   //0 open   1 close; 开出有效位
	unsigned int nreverse;   //0 unreverse 1reverse 2 是否开出状态翻转
	unsigned int ntrigerMode; //0 time  1 biChanged;
	unsigned int ntimeDelay; //开出状态翻转保持时间
	unsigned int nHoldTime;
}drv_analogbosetting;

//递变参数
typedef struct
{                                                
	unsigned int nIsChange;					//是否递变标志, 0:不递变			1：递变
	unsigned int nModule;					//模块编号
	unsigned int  nChangeCount;				//变化次数 电压递变次数
	unsigned int ndfcount;                  //频率递变次数
    long nChangeValue[CHANNEL_MAX*3*2+CHANNEL_MAX];     	//变化量  猜测准备对基波、选择的谐波、直流都兼容递变功能
	long nLastChangeValue[CHANNEL_MAX*3*2+CHANNEL_MAX];     	//最后一步变化量  猜测准备对基波、选择的谐波、直流都兼容递变功能
}drv_change;

typedef struct{
    unsigned int nIsChange;
    unsigned int nModule;
    unsigned int nChangeCount;
    unsigned int ndfcount;
    long		 nChangeValue[DIGITAL_CHANNEL_MAX * 3*2];
	long     nLastChangeValue[DIGITAL_CHANNEL_MAX * 3*2];     	//最后一步变化量
}drv_digitalchange;

//模拟量一次谐波及基波定义
typedef struct
{
	unsigned int nModule;						//模块编号
	//long nDc[CHANNEL_MAX];                      //直流分量
	unsigned int nclsPhase;                               //合闸角度
	unsigned int nexpconfig;                        //非周期分量设置
	long nexp[6];                                         //非周期分量
    long nData[4*CHANNEL_MAX];//直流加基波分量
    long nHarmData[3*CHANNEL_MAX];                //谐波分量(2~30次谐波中任意一次谐波分量值)
}drv_analogitem;

typedef struct
{
	drv_analogitem oModuledata[MODULE_MAX];
}drv_acanalogpara;

//数字量一次谐波及基波定义
typedef struct{
	unsigned int module;// 模块编号
	unsigned int nclsPhase;        //合闸角度
	unsigned int nexpconfig;                        //非周期分量设置
	long nexp[12];                 //非周期分量
	unsigned int dat[DIGITAL_CHANNEL_MAX * 3];
	unsigned int hrmDat[DIGITAL_CHANNEL_MAX * 3];
}drv_sindataitem;

//DigitalPara
typedef struct
{
	//unsigned int nBO;
	drv_sindataitem oModuledata[DIGITAL_MODULE_MAX];
}drv_digitalpara;

typedef struct 
{
	unsigned int nPos;
	unsigned int nCount;
	unsigned char dat[20];
}drv_chanelchanged;

typedef struct 
{
	unsigned int count;				//数据个数
	unsigned int group;				//数据组编号
	drv_chanelchanged dat[CHANELMAXCHANGED];
	unsigned int nUTCChanelCount;     //如果为0,不用打时标
	unsigned int UTCChanelPos[CHANELMAXCHANGED];  //需要打时标的位置
}drv_datchanged;

typedef struct
{
	unsigned int module;			//模块编号
	unsigned int group;				//组数总和
	drv_datchanged dat[16];				//数据信息，详见SV/GOOSE数据信息
}drv_gsechangeditem;

typedef struct
{
	unsigned int nModuleCount;    //模块数
	drv_gsechangeditem datModules[4];//状态序列每个状态预设的GOOSE变位参数
}drv_gsechangeditems;         

typedef struct
{
	unsigned int group;
	unsigned int nLen;
	unsigned char dat[1024];
}drv_f3send;

typedef struct
{
	unsigned int module;
	unsigned int groupCnt;
	drv_f3send ft3[12];
}drv_ft3dataconfigitem;

typedef struct
{
	unsigned int nModuleCount;
	drv_ft3dataconfigitem datModules[4];
}drv_StateFt3Items;

//状态序列参数
typedef struct
{
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
	drv_analogbosetting oBo;
	drv_change stChange[MODULE_MAX];                          //递变参数
	drv_digitalchange stDigitalChange[DIGITAL_MODULE_MAX];
	drv_acanalogpara acAnalog;                          //模拟参数
	drv_digitalpara  Digital;			//数字参数
	drv_gsechangeditems GooseChangedItems;
	drv_StateFt3Items ft3ChangedItems;
	drv_gsetestitems GooseTestItems;
}drv_state;

//状态序列设置总参数
typedef struct
{
	unsigned long nModuleCount;				//模拟模块
	unsigned long nStateModuleCount;        //数字模块
	unsigned int  nDcmodule;              //直流模块
	unsigned long nStateCount;				//状态总数
	unsigned long nSequence;				//是否为顺序状态序列，1：是		0：不是
	unsigned long nloop;
	unsigned long nReverRefence;                                //1 参考第一个状态 0参考上一个状态
	unsigned long noriginal;                //GOOSE init Value;
	drv_analogbosetting oBo;
	drv_state stState[STATECOUNT];				//状态
}drv_state_test;




#define ALG_MODULE_MAX		12
#define BIO_MODULE_MAX		5
#define ALG_PARAM_MAX		3441
#define BIO_MODULE_MAX		5

//开入量模块数据结构
typedef struct{
	unsigned int nVal1;
	unsigned int nVal2;		//开入量值
}structBIStatusItem;

//开入量数据顶层数据结构
typedef struct{
		structBIStatusItem	item[BIO_MODULE_MAX];		//开入数据
}structBIStatus;

//开出值数据结构
typedef struct{
	unsigned int nVal1;
	unsigned int nVal2;		//开出值
}structBoStatusItem;


//开出量顶层数据结构
typedef struct{
	structBoStatusItem item[BIO_MODULE_MAX];
}structBoStatus;

typedef struct{
	unsigned int nVal1;
	unsigned int nVal2;		//开出值
}structBIChangeItem;

//开入变位数据结构
typedef struct{
structBIChangeItem item[BIO_MODULE_MAX];
}structBIChange;

//开出翻转数据结构
typedef struct{
	structBoStatus boStatus;		//开出量初始状态
	structBoStatus flipValid;			//开出量翻转有效位
	unsigned int 	nTrip;			//0:时间触发		1：开入触发
	unsigned int 	nTripDelay;		//时间触发时触发时间，单位毫秒
	unsigned int 	nHoldDelay;		//时间触发时保持时间，单位毫秒
}structBoFlip;

//配置参数顶层结构
typedef struct{
	unsigned int nStateCount;			//状态总数
	unsigned int nIsLoop;				//是否循环
	unsigned int nbiRef;				//0：开入量以第一态为参考1：以上一态为参考
	structBIStatus oGooseInit;			//goose开入初始值
	structBoFlip 	oBo;					//开出设置
}structStateParamNew;



typedef struct{
unsigned int nAlgCnt;			//模拟和SMV模块数量
unsigned int nAlgTable[ALG_MODULE_MAX];
unsigned int nbIntCnt;			//开入模块数量
unsigned int nbITable[BIO_MODULE_MAX];
unsigned int nBoCnt;				//开出模块数量
unsigned int nBoTable[BIO_MODULE_MAX];
}structModuleParam;

//状态序列状态数据
//GPS和时间联合体定义
typedef struct{
	unsigned int nSec;			//GPS触发秒值
	unsigned int nNsec;			//GPS触发纳秒值
}structGPS;
typedef struct{
	unsigned int nMsec;				//时间触发毫秒值
	unsigned int nDelay;			//开入触发延时时间
}structTime;
typedef union{
	structGPS	oGps;				//GPS触发
	structTime	oTime;				//时间触发
}unionTm;

//状态序列输出数据结构
typedef struct{
	unsigned int 	DWCount;			//有效数据长度
	unsigned int    nPhase;
	unsigned int    sss[13];
	unsigned int	nVal[2*37*3];		//输出数据
}structACParamItem;
typedef struct{
	structACParamItem item[ALG_MODULE_MAX];
}structACPara;
//状态序列递变数据结构
typedef struct{
	unsigned int 	nIsChange;			//0:不递变			1：递变
	unsigned int    nOffset;            //数字模块为0，	模拟模块为6
	unsigned int 	nAmpCount;				//幅值递变次数
	unsigned int 	nFreCount;				//频率递变次数
	unsigned int 	nDWCount;			//有效数据个数
	unsigned int 	changeVal[2*37*2];		//递变值，详见说明
	unsigned int	lastVal[2*37*2];			//终止值，详见说明
}structChangeNew;
//开入有效位数据结构
typedef struct
{
	unsigned int nModule;
	unsigned int nVal1;
	unsigned int nVal2;		//有效位的值
}structBIValidItem;
typedef struct{
	unsigned int nModuleCount;
	structBIValidItem item[BIO_MODULE_MAX];
}structBIValid;
//开入触发数据结构
typedef struct{
	unsigned int nBiRef;			//0:翻转触发	 1：下降沿触发	2：上升沿触发
	unsigned int nBiLogic;		//0：开入与	1：开入或
	structBIValid oValid;			//有效通道
}structBITrip;

typedef struct googsechanelChanged{
	unsigned int nPos;
	unsigned int nCount;
	unsigned char dat[20];
	googsechanelChanged()
	{
		nPos = 0;
		nCount = 0;
	}
}GOOGSECHANELCHANGED;

typedef struct datConfigChanged{
	unsigned int count;				//数据个数
	unsigned int group;				//数据组编号
	googsechanelChanged dat[CHANELMAXCHANGED];

	unsigned int nUTCChanelCount;     //如果为0,不用打时标
	unsigned int UTCChanelPos[CHANELMAXCHANGED];  //需要打时标的位置
	datConfigChanged()
	{
		count = 0;
		group = 0;
		nUTCChanelCount = 0;
	}
}DATCONFIGCHANGED;

typedef struct{
	unsigned int module;			//模块编号
	unsigned int group;				//组数总和
	datConfigChanged dat[16];				//数据信息，详见SV/GOOSE数据信息
}datConfigChangedItems;

typedef struct{
	unsigned int nModuleCount;    //模块数
	datConfigChangedItems datModules[4];
}stateGooseChangedItem;         //状态序列每个状态预设的GOOSE变位参数

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

typedef struct
{
	unsigned int pos;
	unsigned int value;
	unsigned int gorup;
}structGSTestMdUnit;
typedef struct
{
	unsigned int module;
	unsigned int nCount;
	structGSTestMdUnit gs[16];
}structGSTestData;
typedef struct
{
	unsigned int nCount;
	structGSTestData dat[DIGITAL_MODULE_MAX];
}structGooseTest;

//说明：状态序列递变可以同时变化频率和幅值，changVal和lastVal数据排列顺序为：
//模拟模块：6直流分量+（频率+幅值）*（DWCount-6）；
//SMV模块：（频率+幅值）*DWCount;
typedef struct{
	unsigned int	nStateNum;			//状态编号
	unsigned int	nTirpType;			//触发源设置，见表5-1
	structBITrip	obiTrip;				//开入触发设置
	unionTm         oTm;					//时间和GPS触发相关数据
	unsigned int	nChangemSec;		//状态序列递变时间分度，单位毫秒
	structBoFlip	oStBo;				//开出参数
	structChangeNew 	oStChange[ALG_MODULE_MAX];		//状态序列递变参数
	structACPara 	oAcParam;			//模拟输出参数
	stateGooseChangedItem GooseChangedItem;			//goose变位信息
	structStateFt3Item		ft3ChangedItem;
	structGooseTest GooseTest;
}structStateItem;

typedef struct{
	unsigned int 	nStep;			//状态序列状态编号，仅状态序列相关模块使用
	unsigned int 	nDegressStep;		//递变步骤编号，递变模块和状态序列的递变都使								//用该数据指示
	unsigned int 	nType;			//结果类型，详见表3-1
	unsigned int 	nSource;			//触发源，详见表3-2
	unsigned int 	nSec;				//UTC时间秒值
	unsigned int 	nNanoSec;			//UTC时间纳秒值
	structBIChange 	oBiChg;			//开入变位值，在source为开入变位时读该值
	structBIStatus	nBi;				//开入量值
	structBoStatus	nBo;				//开出量值
}structResultItemNew;

typedef struct{
	structResultItemNew result[100];
}structResultNew;

void tmt_to_drv(tmt_StateTest *pTmt, drv_state_test *pDrv);
#endif // DRV_DEFINE

