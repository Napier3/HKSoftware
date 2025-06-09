#ifndef DRV_DEFINE
#define DRV_DEFINE

#include "tmt_state_test.h"
#include "../../SttDevice/drv_define.h"
#include "drv_manu_test.h"

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
	Drv_BIStatus oGooseInit;			//goose开入初始值
	structBoFlip 	oBo;					//开出设置
}Drv_StatePara;



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
	long    sss[13];
	long	nVal[2*37*3];		//输出数据
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
	long 	changeVal[2*37*2];		//递变值，详见说明
	long	lastVal[2*37*2];			//终止值，详见说明
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
}Drv_StateItem;

void tmt_to_drv_StatePara(tmt_StateTest *pTmt, Drv_StatePara *pDrv);
void tmt_to_drv_StateItem(tmt_StateTest *pTmt, Drv_StateItem *pDrv_StateItem, char *pBuf,int &nBufLen);
#endif // DRV_DEFINE

