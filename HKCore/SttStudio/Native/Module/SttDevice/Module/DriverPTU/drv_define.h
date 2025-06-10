#ifndef _DRV_DEFINE_H__
#define _DRV_DEFINE_H__

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

//typedef struct{
//	unsigned int rms[8][2];		//采集有效值8路，每路2个32位值
//	unsigned int inst[8];			//瞬时值8路，每路1个32位值
//	long dc[3];					//直流电压、电流、纹波
//	unsigned int sec;
//	unsigned int nsec;
//}Drv_SysInfo;

typedef struct{
	unsigned int module;							//模块编号，0：电压	1：电流
	long dat[1500];			//数据，数据格式和PN466A相同
}structAnalogPara;

typedef struct{
	unsigned int moduleCount;				//模块总数
	unsigned int sample;						//采样速率，sample = 40000/F, F为交流频率
	unsigned int waveCount[8]; 				//每个模块每个通道最大波形个数，同PN466A
	structAnalogPara stAlg[8];				//模拟数据结构
}structACPara;

typedef struct{
	unsigned int type;					//类型，见PN466A
	unsigned int step;					//指示状态序列的第几个状态，手动实验填0
	unsigned int source;					//状态序列触发值，0：手动触发，1：时间触发 2：GPS触发3：开入量触发
	unsigned int sec;						//UTC sec
	unsigned int nSec;					//UTC nSec
	unsigned int biValue;					//开关量的值
	unsigned int boValue;
}structResultItem;

typedef struct{
	unsigned int cnt;
	structResultItem result[1000];
}structResult;						//返回结果

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
	unsigned int module;			//模块编号
	unsigned int cnt;
	long dat[12+12*3];				//模拟数据6个通道直流值加六个通道相位、幅值、频率
}structStateAnalog;
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
	structStateAnalog dat[8];		//模拟数据
}structState;
typedef struct{
	unsigned int stateCount;			//状态数
	unsigned int moduleCount;		//模块数
	unsigned int isLoop;				//是否循环
	structState state[500];
}structStateParam;
#endif // _DRV_DEFINE_H__

