//----------------------------------------------------------------------
//Fault内部使用的公共结构体定义, 仅供内部使用, 如 XML 解析后的数据储存 
//
//其中所需要引用的 enum 见 FaultDef_Enum.h
//               define 见 FaultDef.h
//
//----------------------------------------------------------------------
//1. 命名规则: 
//   FaultStruct_ ...     -- 内部使用的公共结构体
//   FaultTest_ ...       -- 测试组件参数结构体
//   FaultCalc_ ...       -- 计算组件参数结构体
//   FaultResult_...      -- 结果结构体(测试结果)
//   FaultCalcResult_...  -- 结果结构体(计算结果)
//----------------------------------------------------------------------
//2. 内部使用的公共结构体
//   FaultStruct_Phase    -- 相量(幅值,角度)
//   FaultStruec_UI       -- UI模拟量通道(是否直流,幅值,角度,频率)
//   FaultStruct_GPS      -- GPS 配置

//----------------------------------------------------------------------
#if !defined(_FaultDEF_STRUCT)
#define _FaultDEF_STRUCT

#include "FaultDef.h"
//----------------------------------------------------------------------
#define MAX_VOLT_NUMBER MAX_CHANNEL_COUNT 	// 16 路电压, 16 路电流
#define MAX_CURR_NUMBER MAX_CHANNEL_COUNT 
#define MAX_BIN_NUMBER  MAX_IO_COUNT 	    // 16 路开入, 16 路开出
#define MAX_BOUT_NUMBER MAX_IO_COUNT 

#define MAX_HARM_NUMBER 50			//谐波试验: 最大谐波次数
#define MAX_STATE_NUMBER 50			//状态序列: 最多允许有50个状态
#define MAX_TRIP_NUMBER 4			//整组试验: 最多允许跳闸次数
#define MAX_nStates_NUMBERS 20		//波形回放: 最多允许记录的开入接点状态翻转的次数


//----------------------------------------------------------------------
struct FaultStruct_LinkInfo	//Fault 联机信息
{
	UINT32		PcIP;		//PC机IP
	UINT32		DevIP;		//设备IP: 0xFFFFFFFF 为广播
	UINT16		PcPort;		//PC机Port
	UINT16		DevPort;	//设备Port
};

struct FaultStruct_Phase	//幅值,角度
{
	float Mag;	
	float Ang;	
};
struct FaultStruct_UI		//幅值,角度,频率,是否直流
{
	int bDC;
	float Mag;	
	float Ang;	
	float Fre;
};
struct FaultStruct_GPS		//GPS设置
{
	int GpsPos;		//0--内置GPS, 1--外接 GPS(测试仪), 2--外接 GPS(PC机)
	int BaudRate;	//BaudRate=9600;  GPS所接 COM 的波特率
	int Parity;		//Parity=0;       0--无校验, 1--奇校验, 2--偶校验
	int StopBits;	//StopBits=1;     停止位, 1, 或 2;
	int DataBits;	//DataBits=8;     数据位, 7, 或 8;
	int nComNo;		//GPS 所在的串口号, 1--COM1, 2--COM2, (外接 GPS 在 PC 机时有效)
};
struct FaultStruct_BinTime	//开入量动作时间定义
{
	float Bin[MAX_BIN_NUMBER];
};
typedef struct FaultStruct_BinTime FaultStruct_Bin;

//----------------------------------------------------------------------
//谐波试验
struct FaultStruct_HarmUI   //第n次谐波: 幅值,角度,是否选择输出
{
	int bSelect;
	float Mag;
	float Ang;
};
struct FaultStruct_HarmSet	//每一个 ui 通道的谐波叠加
{
	FaultStruct_HarmUI Harm[MAX_HARM_NUMBER+1];		//直流+20次谐波
};
struct FaultStruct_InterHarmSet
{
	int bSelect;
	float Mag;
	float Ang;
	float Fre;
};
//----------------------------------------------------------------------
//时间测量
struct FaultStruct_TimerSet	//每一个状态的参数
{
	//本状态下输出的电压电流
	FaultStruct_UI Up[MAX_VOLT_NUMBER];		//幅值, 角度, 频率, 是否直流
	FaultStruct_UI Ip[MAX_CURR_NUMBER];
};
//----------------------------------------------------------------------
//状态序列
struct FaultStruct_StateUI	//每一个 ui 通道的参数
{
	float Mag;  float Ang;  float Fre;  int bDC;
	int bDMag;  float dMag_dt;  float EndMag;
	int bDFre;  float dFre_dt;  float EndFre;
};
struct FaultStruct_StateSet	//每一个状态的参数
{
	//本状态下输出的电压电流
	FaultStruct_StateUI Up[MAX_VOLT_NUMBER];
	FaultStruct_StateUI Ip[MAX_CURR_NUMBER];
	//本状态下的开关量输出设置
	int OutputState[MAX_BOUT_NUMBER];
	float OutputDelayTime[MAX_BOUT_NUMBER];
	//本状态结束条件
	int EndMode;			//结束条件: 0--按键触发; 
							//			1--时间触发; 
							//			2--GPS分脉冲触发;  
							//			3--开入接点触发; 
							//			4--幅值触发; 
							//			5--频率触发;
							//          6--开入接点触发 + 最大限时;
	float EndDelayTime;		//结束条件满足后, 再增加一个延时后真正触发
	float MaxLastTime;		//1,6--时间触发有效
	int GPSPos;				//2--GPS触发: 0--接测试仪,内置GPS; 1--接测试仪,外置GPS; 2--接 PC 机, 外置GPS(开入c,r分别为PPS,PPM);
	int bAndOr;				//3,6--开入接点触发有效
	int bBinSelect[MAX_BIN_NUMBER];	
	int Mag_nGroup;		//4--幅值触发有效: 幅值组别, 0--相电压, 1--相电流, ...
	int Mag_nIndex; 	//                 组内索引号: 012, 345, ...	
	float Mag_Value;	//                 触发值
	int Fre_nGroup;		//5--频率触发有效: 频率组别, 0--相电压, 1--相电流, ...
	int Fre_nIndex; 	//                 组内索引号: 012, 345, ...	
	float Fre_Value;	//				   触发值
};
//----------------------------------------------------------------------
//波形回放
struct FaultStruct_WPChannel	//通道配置
{
	int ChIndex;		//Uabcxyz,Iabcxyz在配置中的通道索引号(-1无关联,0123...)
	float Factor;		//辅助调整比例(类似 PT/CT 变比, 原始录波数据/测试仪输出)
};
struct FaultStruct_WPSection	//重复区间定义
{
	int bSelect;
	float TimeFrom;		//ms, 起点
	float TimeLength;	//ms, 区间长度
	int RepeatNumbers;	//总输出次数
};

//----------------------------------------------------------------------
//深圳南瑞状态序列--允许叠加谐波(每通道1个谐波分量),
struct FaultStruct_SzNari_UI
{
	float TimeStart;
	float Mag;   float Ang; 
	float Harm_Mag;   float Harm_Ang;   float Harm_Fre;
};
struct FaultStruct_SzNari_Bout
{
	float TimeStart;
	int nState;
};
struct FaultStruct_SzNari_State
{
	FaultStruct_SzNari_UI Up[MAX_VOLT_NUMBER];
	FaultStruct_SzNari_UI Ip[MAX_CURR_NUMBER];
	FaultStruct_SzNari_Bout Bout[MAX_BOUT_NUMBER];
};
//----------------------------------------------------------------------
//开入开出装置: SOE 测试(开出)
struct FaultStruct_IO_SOE_BoutSet
{
	int bSelect;			//选择标志
	int Bout_0;				//起始状态
	float Bout_DelayTime;	//翻转延时(即翻转启动时刻): s
	float Bout_KeepTime;	//翻转后保持时间(即脉冲宽度): s
	int Bout_TripNumbers;	//翻转次数
};
//----------------------------------------------------------------------
//开入开出装置: 状态序列
struct FaultStruct_StateSet_IO	//每一个状态的参数
{
	//本状态下的开关量输出设置: 
	int Bout_State[MAX_IO_COUNT_EX];		//0--断开, 1--闭合
	float Bout_DelayTime[MAX_IO_COUNT_EX];	//延时
	//本状态结束条件
	int EndMode;			//结束条件: 0--按键触发; 
							//			1--时间触发; 
							//			2--GPS分脉冲触发;  
	float EndDelayTime;		//结束条件满足后, 再增加一个延时后真正触发
	float MaxLastTime;		//1,6--时间触发有效
	int GPSPos;				//2--GPS触发: 0--接测试仪,内置GPS; 1--接测试仪,外置GPS; 2--接 PC 机, 外置GPS(开入c,r分别为PPS,PPM);
};


#endif
