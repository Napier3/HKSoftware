#ifndef _DRV_DEFINE_H__
#define _DRV_DEFINE_H__

#include "stt_drv_common_define.h"

// 2020-10-21  此部分定义移到stt_drv_common_define.h  各种硬件的公共定义
// 特殊硬件定义，放到相应的目录下
/*
#define TIME_MAX_WAITING		300			//最长触发等待时间
#define TIME_ONLINE_DELAY		  1			//联机延时

#define STATECOUNT              250
#define CHANELMAXCHANGED        256
#define STATE_RESULT_MAX        250

#define MODULE_MAX	              8    //模块数
#define DIGITAL_MODULE_MAX	      4	//插件数
#define MAX_DIGITAL_GROUP_NUM     4
#define DATA_MAX               1536
#define CHANNEL_MAX               6    //volt\current通道数

#define SYS_INFO_COUNT           11
#define STATERESULTMAX         1000
#define GOOSE_CHANGE_POS_MAX    256
#define CHARPARALeng            256
#define DIGITAL_CHANNEL_MAX      37
#define HARMONIC_MAX             31//总谐波次数

#define DIGITAL_CHANNEL_MARK      1//模块电压标记
#define VOL_CHANNEL_MARK          2//模块电压标记
#define CUR_CHANNEL_MARK          4//模块电流标记

#define SMV_MAX           8
#define GOOSE_MAX        16
#define FT3_MAX          12
#define GOOSESUB_MAX     32

//TestType
#define ManualTest      0
#define GradientTest    1
#define HarmTest        2
#define StateTest       3
#define ShakeTest       4
#define IECDataCfg      5
#define SvCtrlCfg       6
#define GseCtrlCfg      7
#define FiberCtrlCfg    8
#define AbnoramlTest    9
#define ReplayTest      10
#define ReplayTestCfg   11
#define ReplayTestData  12
#define Record          13

//ModuleType
#define VOLT             1
#define CURRENT          2
#define DIGITAL          3
#define DCCURRENT        4
#define DCVOLT           5
#define SWITCH           6
*/

union ConverStruct {
	unsigned char b[4];
	unsigned long l;
	float f;
};//4个字节，利用共用体，进行转换

#define CHANNEL_A     0
#define CHANNEL_B     1
#define CHANNEL_C     2

#define DrvPos_Ang    0
#define DrvPos_Fre    1
#define DrvPos_Amp    2

#define TmtPos_Amp    0
#define TmtPos_Ang    1
#define TmtPos_Fre    2

#define TMT_UA_POS    0
#define TMT_UB_POS    1
#define TMT_UC_POS    2
#define TMT_UA2_POS   3
#define TMT_UB2_POS   4
#define TMT_UC2_POS   5

#define TMT_IA_POS    0
#define TMT_IB_POS    1
#define TMT_IC_POS    2
#define TMT_IA2_POS   3
#define TMT_IB2_POS   4
#define TMT_IC2_POS   5

//振荡
#define NANOSECOND             1.0e9
#define SHAKE_ALG_PARA_CNT        24//6+6*3
#define SHAKE_DIG_PARA_CNT        75
#define SHAKE_MAX               5000

//递变相关
#define GRADIENT_MAX_COUNT			3000// 最大递变点数
#define GRADIENT_SMV_PARA_CNT	    111 //(37*3)
#define GRADIENT_ALG_PARA_CNT	    24 //6+6*3
#define GRADIENT_PARAM_MAX		    74 //(37*2)

#define GRADIENT_AMP      0
#define GRADIENT_ANG      1
#define GRADIENT_FRE      2

#define GRADIENT_UA               0
#define GRADIENT_UB               1
#define GRADIENT_UC               2
#define GRADIENT_UABC             3
#define GRADIENT_IA               4
#define GRADIENT_IB               5
#define GRADIENT_IC               6
#define GRADIENT_IABC             7
#define GRADIENT_UA2              8
#define GRADIENT_UB2              9
#define GRADIENT_UC2             10
#define GRADIENT_UABC2           11
#define GRADIENT_IA2             12
#define GRADIENT_IB2             13
#define GRADIENT_IC2             14
#define GRADIENT_IABC2           15
#define GRADIENT_UABC_UABC2      16
#define GRADIENT_IABC_IABC2      17
#define GRADIENT_UABC_IABC_1     18
#define GRADIENT_UABC_IABC_2     19
#define GRADIENT_UAB             20
#define GRADIENT_UBC             21
#define GRADIENT_UCA             22
#define GRADIENT_UAB2            23
#define GRADIENT_UBC2            24
#define GRADIENT_UCA2            25
#define GRADIENT_IAB             26
#define GRADIENT_IBC             27
#define GRADIENT_ICA             28
#define GRADIENT_IAB2            29
#define GRADIENT_IBC2            30
#define GRADIENT_ICA2            31

#define GRADIENT_RESULT_START	         1
#define GRADIENT_RESULT_STOP	         2
#define GRADIENT_RESULT_CHANGE	         3
#define GRADIENT_RESULT_DI_CHANGE	     4
#define GRADIENT_RESULT_RETURN	         5
#define GRADIENT_RESULT_GO_FAULT	     6
#define GRADIENT_RESULT_SHAKE	         7
#define GRADIENT_RESULT_SHAKE_FAULT	     8
typedef struct{
	unsigned int nStep;		//当前处于第几次递变
	unsigned int nType;		//1:start  2:stop  3:状态变化  4:开入变位  5:start to return 6:递变故障前 7 切换到振荡态 8切换到故障
	unsigned int nSec;		//时间秒值
	unsigned int nNanoSec;		//时间毫秒值
	unsigned int nInput;			//开入值
	unsigned int nGoose;            //GOOSE bi;
	unsigned int nSource;       //变位bit
}structRampResult;

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
//typedef struct _structResult{
//	unsigned int nType;					//结果类型，
////1：开始实验	2：实验结束	3：状态切换	4：开入变位 5: 递变 6:goose changed 7递变值 8开出变位
//	unsigned int nSource;			//当type为开入变位，为变位的开入通道，bit9~bit0对应开入9~0
//									//当type为状态切换时，为状态切换触发条件，
//									//bit12:手动触发	bit11：时间触发	bit10：GPS触发
//									//bit9~bit0:对应开关量9~0
//	unsigned int nSec;						//产生结果的时间秒值
//	unsigned int nNanoSec;					//产生结果的时间纳秒值
//	unsigned int nInput;					//产生结果时开入量的值
//	unsigned int nGooseValue;               //
//	unsigned int currentIndex;				//当前状态索引号
//	unsigned int nObjective;				//要跳转的状态索引号
//	unsigned int nOutput;					//开出状态
//	unsigned int nstep;                     //递变值
////    structAnalog  stAnalog[8];		//当前输出模拟量数据

//}structResult;

//typedef struct _structResultItem{
//	unsigned int nCount;						//结果计数,最大1000个
//	structResult  stResult[STATERESULTMAX];
//}structResultItem;

typedef struct
{
	unsigned int dat[SYS_INFO_COUNT];
}StructFeedBack;

typedef struct
{
	unsigned int tmFlag;        //bit; 0 GPS   1 BCode
	unsigned int tm_h;          //秒
	unsigned int tm_l;          //纳秒
	StructFeedBack stBack[8]/*MODULE_MAX]*/;//module 8 1,2,4,8,16,32,64,128
}StructSysInfo;



//zhoulei 2020-10-04
#define ALG_MODULE_MAX		12
#define BIO_MODULE_MAX		5
#define ALG_PARAM_MAX		3441

//状态序列触发类型
#define State_Trig_Manual          0x001
#define State_Trig_Bin             0x002
#define State_Trig_TimeDelay       0x100
#define State_Trig_GPS             0x200
#define State_Trig_Bin_TimeDelay   0x102
#define State_Trig_GPS_TimeDelay   0x202

typedef struct{
unsigned int nAlgCnt;			//模拟和SMV模块数量
unsigned int nAlgTable[ALG_MODULE_MAX];
unsigned int nBiCnt;			//开入模块数量
unsigned int nBiTable[BIO_MODULE_MAX];
unsigned int nBoCnt;				//开出模块数量
unsigned int nBoTable[BIO_MODULE_MAX];
}Drv_ModulePara;


//
//
//开入量模块数据结构
typedef struct{
	unsigned int nVal1;
	unsigned int nVal2;		//开入量值
}structBIStatusItem;

//开入量数据顶层数据结构
typedef struct{
		structBIStatusItem	item[BIO_MODULE_MAX];		//开入数据
}Drv_BIStatus;

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

typedef struct{
	unsigned int 	nStep;			//状态序列状态编号，仅状态序列相关模块使用
	unsigned int 	nDegressStep;		//递变步骤编号，递变模块和状态序列的递变都使用该数据指示
	unsigned int 	nType;			//结果类型，详见表3-1
	unsigned int 	nSource;			//触发源，详见表3-2
	unsigned int 	nSec;				//UTC时间秒值
	unsigned int 	nNanoSec;			//UTC时间纳秒值
	structBIChange 	oBiChg;			//开入变位值，在source为开入变位时读该值
	Drv_BIStatus	nBi;				//开入量值
	structBoStatus	nBo;				//开出量值
}Drv_ResultItem;

typedef struct{
	Drv_ResultItem oItem[100];
}Drv_Results;

/******structDegUnit
		 xw   pl   fz
Ua1      0    1    2
Ub1      1*3  4    5
Uc1      2*3  7    8

Uz       3*3  10   11

Ua2      4*3  13   14
Ub2      5*3  16   17
Uc2      6*3  19   20
Ua3      7*3
Ub3      8*3
Uc3      9*3
Ua4      10*3
Ub4      11*3
Uc4      12*3

Ia1      13*3 40   41
Ib1      14*3 43   44
Ic1      15*3 46   47
Ia2      16*3 49   50
Ib2      17*3 52   53
Ic2      18*3 55   56
Ia3      19*3
Ib3      20*3
Ic3      21*3
Ia4      22*3
Ib4      23*3
Ic4      24*3 73   74

Ua5      25*3 76   77
Ub5      26*3 79   80
Uc5      27*3 82   83
Ua6      28*3 85   86
Ub6      29*3 88   89
Uc6      30*3 91   92

Ia5      31*3
Ib5      32*3
Ic5      33*3
Ia6      34*3
Ib6      35*3
Ic6      36*3
*****/
#endif // _DRV_DEFINE_H__

