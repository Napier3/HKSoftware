//----------------------------------------------------------------------
//Fault计算组件参数结构体定义
//
//其中所引用的 enum 见 ..\TestMacroGlobalDefine.h
//           define 见 FaultDef.h, FaultDef_Struct.h
//
//2013-3-20: 增加 FaultCalc_Fault_Ex, FaultCalc_Shot_Ex 扩展的常规故障计算模型
//          增加 Ks_Mode 设置
//          Ks_Mode = 0 -- Ks 自由输入;
//                    1 -- Ks = KL;
//2013-7-18: 增加 FaultCalc_GPFault_Ex, FaultCalc_GPDistance_Ex 工频变化量短路计算模型
//          增加 CalcuMode 参数(南瑞继保和许继不同)
//          CalcuMode = 0 -- 南瑞继保公式;
//                      1 -- 许继公式;
//----------------------------------------------------------------------
//1. 命名规则: 
//   FaultStruct_ ...     -- 内部使用的公共结构体
//   FaultTest_ ...       -- 测试组件参数结构体
//   FaultCalc_ ...       -- 计算组件参数结构体
//   FaultResult_...      -- 结果结构体(测试结果)
//   FaultCalcResult_...  -- 结果结构体(计算结果)
//----------------------------------------------------------------------
//2. 计算组件使用的参数结构体 
//   FaultCalc_LoadState    -- 正常运行负荷状态计算
//   FaultCalc_Fault        -- 常规短路计算参数
//   FaultCalc_Fault_Ex     -- 常规短路计算参数: 扩展, 增加 Ks_Mode
//   FaultCalc_GPFault      -- 工频变化量短路计算参数
//   FaultCalc_GPFault_Ex   -- 工频变化量短路计算参数: 扩展, 增加 CalcuMode(南瑞继保和许继不同)
//   FaultCalc_ABCPP        -- ABC 相量 <--> 线分量
//   FaultCalc_ABC120       -- ABC 相量 <--> 序分量
//   FaultCalc_PQ           -- 三相功率计算, P,Q, cos;  
//
//   FaultCalc_Shot         -- 整组试验计算
//   FaultCalc_Shot_Ex      -- 整组试验计算: 扩展, 增加 Ks_Mode
//   FaultCalc_Distance     -- 距离保护定值校验计算
//   FaultCalc_GPDistance   -- 工频变化量阻抗定值校验计算
//   FaultCalc_GPDistance_Ex-- 工频变化量阻抗定值校验计算
//   FaultCalc_OverCurr     -- 过流保护定值校验计算
//   FaultCalc_ZeroSeqCurr  -- 零序过流保护定值校验计算
//   FaultCalc_NegSeqCurr   -- 负序过流保护定值校验计算
//
//   FaultCalc_Diff         -- 差动计算: 根据 Id,Ir 计算两侧所加电流 Iabc,Ixyz
//   FaultCalc_Diff_Shot    -- 差动计算: 差动整组
//   FaultCalc_Diff_IrId    -- 差动计算: 根据 6 路电流, 计算差流和制流
//   FaultCalc_Diff_KP      -- 差动计算: 补偿系数 KPH,M,L 辅助计算
//
//   FaultCalc_Diff5        -- 电铁差动: 根据 Id,Ir 计算两侧所加电流 Iabc,Ixy
//
//   FaultCalc_Osc          -- 功率振荡: 当前发电机角下, 保护安装处 K 点的电压电流有效值
//   FaultCalc_Osc_Zk       -- 功率振荡: 当前发电机角下, 保护安装处 K 点的测量阻抗

#if !defined(_FaultDEF_CALC)
#define _FaultDEF_CALC

#include "FaultDef.h"
#include "..\TestMacroGlobalDefine.h"
#include "FaultDef_Struct.h"
//----------------------------------------------------------------------
//计算功能编码 nCalcID
//----------------------------------------------------------------------
#define CALCID_LOADSTATE	0	//正常运行负荷状态计算
#define	CALCID_FAULT		1	//计算短路: 常规计算模型
#define CALCID_GPFAULT		2	//计算短路: 工频变化量计算模型
#define CALCID_ABCTOPP		3	//线分量计算: ABC -> PP
#define CALCID_PPTOABC		4	//            PP -> ABC
#define CALCID_ABCTO120		5	//序分量计算: ABC -> 120
#define CALCID_120TOABC		6	//            120 -> ABC
#define CALCID_ABCTOPQ		7	//计算三相功率
//
#define CALCID_SHOT			100		//整组试验计算: 根据界面参数计算3个状态下的电压电流(三相UI)
#define CALCID_DISTANCE		101		//距离保护定值校验计算
#define CALCID_GPDISTANCE	102		//工频变化量阻抗保护定值校验计算
#define CALCID_OVERCURR		103		//过流保护定值校验计算
#define CALCID_NEGSEQCURR	104		//负序过流保护定值校验计算
#define CALCID_ZEROSEQCURR	105		//零序过流保护定值校验计算
//
#define CALCID_DIFF			120		//差动计算: 根据 Id,Ir 计算两侧所加电流 Iabc,Ixyz
#define CALCID_DIFF_KP		121		//差动计算: 补偿系数 KP123 辅助计算
#define CALCID_DIFF_SHOT	122		//差动计算: 差动整组
#define CALCID_DIFF_IRID	123		//差动计算: 根据 I1[3], I2[3] 计算三相差流和制流
//
#define CALCID_DIFF5		130		//电铁差动: 根据 Id,Ir 计算两侧所加电流 Iabc,Ixy
//
#define CALCID_OSC			140		//功率振荡: 当前发电机角下, 保护安装处 K 点的电压电流有效值
#define CALCID_OSC_ZK		141		//功率振荡: 当前发电机角下, 保护安装处 K 点的测量阻抗
//
#define	CALCID_FAULT_EX			200		//计算短路: 常规计算模型, 扩展, 增加 Ks_Mode
#define CALCID_SHOT_EX			201		//整组试验计算: 扩展, 增加 Ks_Mode
#define CALCID_GPFAULT_EX		202		//工频变化量计算: 扩展, 增加 CalcuMode
#define CALCID_GPDISTANCE_EX	203		//工频变化量阻抗保护定值校验计算: 扩展, 增加 CalcuMode

//----------------------------------------------------------------------
struct FaultCalcResult_UpIp
{
	FaultStruct_Phase Up[3];
	FaultStruct_Phase Ip[3];
};
struct FaultCalcResult_Up
{
	FaultStruct_Phase Up[3]; 
};
struct FaultCalcResult_Ip
{
	FaultStruct_Phase Ip[3]; 
};
struct FaultCalcResult_PQ
{
	float P;
	float Q;
	float COS;
};

struct FaultCalcResult_Shot
{
	FaultStruct_Phase Up_PreFault[3];	//故障前电压电流: 3U, 3I
	FaultStruct_Phase Ip_PreFault[3];
	//
	FaultStruct_Phase Up_Fault[3];		//故障电压电流: 3U, 3I
	FaultStruct_Phase Ip_Fault[3];
	//
	FaultStruct_Phase Up_TransFault[3];	//故障转换后电压电流: 3U, 3I
	FaultStruct_Phase Ip_TransFault[3];
};

struct FaultCalcResult_Diff
{
	FaultStruct_Phase Ip[6];		//基波电流: [012]--I1侧abc, [345]--I2侧abc
	//
	FaultStruct_Phase Ip_Harm[6];	//谐波制动: 叠加谐波电流
	//
	float GapAng[6];				//间断角制动: 间断角
};
struct FaultCalcResult_Diff_KP
{
	float KPH;			//高压侧补偿系数
	float KPM;			//中压侧补偿系数
	float KPL;			//低压侧补偿系数
};

struct FaultCalcResult_Diff_IrId
{
	float Id[3];	//三相差流
	float Ir[3];	//三相制流
};


//--------------------------------------------------------------------------------
//正常运行负荷状态计算
struct FaultCalc_LoadState
{
	float Us;			//额定电压
	float ILoad_Mag;	//负荷电流
	float ILoad_Ang;	//负荷电流角度(相对于对应相的电压, +为超前)
	//
	FaultCalcResult_UpIp Result;
};

//常规短路计算参数(单机对无穷大)
struct FaultCalc_Fault
{
	float Us;				//额定电压
	float ILoad_Mag;		//负荷电流
	float ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//
	int FaultType;			//故障类型: 见 FaultEnum_FaultType
	int FaultDirection;		//故障方向: 0--正方向, 1--反方向
	float FaultUf;			//短路电压(计算模型为定电压时有效)
	float FaultIf;			//短路电流(计算模型为定电流时有效)
	float FaultZf_Mag;		//短路阻抗
	float FaultZf_Ang;
	//
	int CalcuMode;			//短路计算模型: 详见 FaultEnum_CalcuMode
	float Zs_Mag;			//电源侧阻抗(定Zs模型有效)
	float Zs_Ang;
	float Ks_Mag;			//电源侧阻抗的零序补偿系数(幅值,角度)
	float Ks_Ang;
	int KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	float KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	float KL_Ang;
	float KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
	float KL_KX;
	//
	FaultCalcResult_UpIp Result;
};

//常规短路计算参数(单机对无穷大): 扩展, 增加 Ks_Mode
struct FaultCalc_Fault_Ex
{
	float Us;				//额定电压
	float ILoad_Mag;		//负荷电流
	float ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//
	int FaultType;			//故障类型: 见 FaultEnum_FaultType
	int FaultDirection;		//故障方向: 0--正方向, 1--反方向
	float FaultUf;			//短路电压(计算模型为定电压时有效)
	float FaultIf;			//短路电流(计算模型为定电流时有效)
	float FaultZf_Mag;		//短路阻抗
	float FaultZf_Ang;
	//
	int CalcuMode;			//短路计算模型: 详见 FaultEnum_CalcuMode
	float Zs_Mag;			//电源侧阻抗(定Zs模型有效)
	float Zs_Ang;
	//
	int Ks_Mode;			//电源阻抗的零序补偿系数设置方式: 0--Ks 输入, 1--Ks=KL;
	float Ks_Mag;			//电源侧阻抗的零序补偿系数(幅值,角度)
	float Ks_Ang;
	//
	int KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	float KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	float KL_Ang;
	float KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
	float KL_KX;
	//
	FaultCalcResult_UpIp Result;
};

//工频变化量短路计算参数
struct FaultCalc_GPFault
{
	float Zzd_Mag;			//整定阻抗
	float Zzd_Ang;
	float m;				//校验点: m=0.9, 1.1, ...
	float FaultIf;			//短路电流(计算模型为定电流时有效)
	int FaultType;			//故障类型: 见 FaultEnum_FaultType
	int FaultDirection;		//故障方向: 0--正方向, 1--反方向
	//
	float Us;				//额定电压
	float ILoad_Mag;		//负荷电流
	float ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//
	int KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	float KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	float KL_Ang;
	float KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
	float KL_KX;
	//
	FaultCalcResult_UpIp Result;
};

//工频变化量短路计算参数: 扩展, 增加 CalcuMode;
struct FaultCalc_GPFault_Ex
{
	int CalcuMode;			//0--南瑞继保公式,  1--许继公式
	//
	float Zzd_Mag;			//整定阻抗
	float Zzd_Ang;
	float m;				//校验点: m=0.9, 1.1, ...
	float FaultIf;			//短路电流(计算模型为定电流时有效)
	int FaultType;			//故障类型: 见 FaultEnum_FaultType
	int FaultDirection;		//故障方向: 0--正方向, 1--反方向
	//
	float Us;				//额定电压
	float ILoad_Mag;		//负荷电流
	float ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//
	int KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	float KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	float KL_Ang;
	float KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
	float KL_KX;
	//
	FaultCalcResult_UpIp Result;
};

//ABC 相量 <-> 线分量 转换计算
struct FaultCalc_ABCPP
{
	FaultStruct_Phase Up[3]; 
	FaultCalcResult_Up Result;
};

//ABC 相量 <-> 序分量 转换计算
struct FaultCalc_ABC120
{
	FaultStruct_Phase Up[3]; 
	FaultCalcResult_Up Result;
};

//三相功率计算
struct FaultCalc_PQ
{
	int CalcuMode;					//0--三表计法, 1--两表计法
	FaultStruct_Phase Up[3];		//三相电压: 幅值, 角度
	FaultStruct_Phase Ip[3];		//三相电流: 幅值, 角度
	FaultCalcResult_PQ Result;
};

//整组试验计算: 根据界面参数计算3个状态下的电压电流(三相UI)
struct FaultCalc_Shot
{
	//故障前
	float Us;				//额定电压
	float ILoad_Mag;		//负荷电流
	float ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//故障
	int FaultType;			//故障类型: 见 FaultEnum_FaultType
	int FaultDirection;		//故障方向: 0--正方向, 1--反方向
	float FaultUf;			//短路电压(计算模型为定电压时有效)
	float FaultIf;			//短路电流(计算模型为定电流时有效)
	float FaultZf_Mag;		//短路阻抗
	float FaultZf_Ang;
	//故障转换
	int bFaultTrans;			//是否发生故障转换: 0--否, 1--是;
	int TransFaultType;			//故障类型: 见 FaultEnum_FaultType
	int TransFaultDirection;	//故障方向: 0--正方向, 1--反方向
	float TransFaultUf;			//短路电压(计算模型为定电压时有效)
	float TransFaultIf;			//短路电流(计算模型为定电流时有效)
	float TransFaultZf_Mag;		//短路阻抗
	float TransFaultZf_Ang;
	//
	int CalcuMode;			//短路计算模型: 详见 FaultEnum_CalcuMode
	float Zs_Mag;			//电源侧阻抗(定Zs模型有效)
	float Zs_Ang;
	float Ks_Mag;			//电源侧阻抗的零序补偿系数(幅值,角度)
	float Ks_Ang;
	int KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	float KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	float KL_Ang;
	float KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//整组试验计算: 根据界面参数计算3个状态下的电压电流(三相UI): 扩展, 增加 Ks_Mode
struct FaultCalc_Shot_Ex
{
	//故障前
	float Us;				//额定电压
	float ILoad_Mag;		//负荷电流
	float ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//故障
	int FaultType;			//故障类型: 见 FaultEnum_FaultType
	int FaultDirection;		//故障方向: 0--正方向, 1--反方向
	float FaultUf;			//短路电压(计算模型为定电压时有效)
	float FaultIf;			//短路电流(计算模型为定电流时有效)
	float FaultZf_Mag;		//短路阻抗
	float FaultZf_Ang;
	//故障转换
	int bFaultTrans;			//是否发生故障转换: 0--否, 1--是;
	int TransFaultType;			//故障类型: 见 FaultEnum_FaultType
	int TransFaultDirection;	//故障方向: 0--正方向, 1--反方向
	float TransFaultUf;			//短路电压(计算模型为定电压时有效)
	float TransFaultIf;			//短路电流(计算模型为定电流时有效)
	float TransFaultZf_Mag;		//短路阻抗
	float TransFaultZf_Ang;
	//
	int CalcuMode;			//短路计算模型: 详见 FaultEnum_CalcuMode
	float Zs_Mag;			//电源侧阻抗(定Zs模型有效)
	float Zs_Ang;
	//
	int Ks_Mode;			//电源阻抗的零序补偿系数设置方式: 0--Ks 输入, 1--Ks=KL;
	float Ks_Mag;			//电源侧阻抗的零序补偿系数(幅值,角度)
	float Ks_Ang;
	//
	int KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	float KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	float KL_Ang;
	float KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//距离保护定值校验计算(不考虑故障转换): 根据界面参数计算 2 个状态下的电压电流(三相UI)
//计算模型: 固定为定电流
struct FaultCalc_Distance
{
	float Zzd_Mag;			//阻抗定值
	float Zzd_Ang;
	float Zf_Ratio;			//短路阻抗: 倍数
	float FaultIf;			//短路电流(计算模型: 定电流)
	int FaultType;			//故障类型: 见 FaultEnum_FaultType
	int FaultDirection;		//故障方向: 0--正方向, 1--反方向
	//
	float Us;				//额定电压
	float ILoad_Mag;		//负荷电流
	float ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//
	int KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	float KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	float KL_Ang;
	float KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//工频变化量阻抗保护定值校验计算(不考虑故障转换): 根据界面参数计算 2 个状态下的电压电流(三相UI)
struct FaultCalc_GPDistance
{
	float Zzd_Mag;			//整定阻抗
	float Zzd_Ang;
	float m;				//校验点: m=0.9, 1.1, ...
	float FaultIf;			//短路电流(计算模型: 定电流)
	int FaultType;			//故障类型: 见 FaultEnum_FaultType
	int FaultDirection;		//故障方向: 0--正方向, 1--反方向
	//
	float Us;				//额定电压
	float ILoad_Mag;		//负荷电流
	float ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//
	int KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	float KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	float KL_Ang;
	float KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//工频变化量阻抗保护定值校验计算(不考虑故障转换): 根据界面参数计算 2 个状态下的电压电流(三相UI)
struct FaultCalc_GPDistance_Ex
{
	int CalcuMode;			//0--南瑞继保公式,  1--许继公式
	//
	float Zzd_Mag;			//整定阻抗
	float Zzd_Ang;
	float m;				//校验点: m=0.9, 1.1, ...
	float FaultIf;			//短路电流(计算模型: 定电流)
	int FaultType;			//故障类型: 见 FaultEnum_FaultType
	int FaultDirection;		//故障方向: 0--正方向, 1--反方向
	//
	float Us;				//额定电压
	float ILoad_Mag;		//负荷电流
	float ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//
	int KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	float KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	float KL_Ang;
	float KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//过流保护定值校验计算(不考虑故障转换): 根据界面参数计算 2 个状态下的电压电流(三相UI)
//计算模型: 固定为定电流
struct FaultCalc_OverCurr
{
	float Izd;				//电流定值
	float If_Ratio;			//短路电流: 倍数
	float Zf_Mag;			//短路阻抗: 幅值, 灵敏角 (计算模型: 定电流)
	float Zf_Ang;
	int FaultType;			//故障类型: 见 FaultEnum_FaultType
	int FaultDirection;		//故障方向: 0--正方向, 1--反方向
	//
	float Us;				//额定电压
	float ILoad_Mag;		//负荷电流
	float ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//
	int KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	float KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	float KL_Ang;
	float KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//负序过流保护定值校验计算(不考虑故障转换): 根据界面参数计算 2 个状态下的电压电流(三相UI)
//计算模型: 固定为定电流
struct FaultCalc_NegSeqCurr
{
	float Izd;				//负序电流 I2 定值
	float If_Ratio;			//短路电流: 倍数
	float Zf_Mag;			//短路阻抗: 幅值, 灵敏角 (计算模型: 定电流)
	float Zf_Ang;
	int FaultType;			//故障类型: 见 FaultEnum_FaultType
	int FaultDirection;		//故障方向: 0--正方向, 1--反方向
	//
	float Us;				//额定电压
	float ILoad_Mag;		//负荷电流
	float ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//
	int KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	float KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	float KL_Ang;
	float KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//零序过流保护定值校验计算(不考虑故障转换): 根据界面参数计算 2 个状态下的电压电流(三相UI)
//计算模型: 固定为定电流
struct FaultCalc_ZeroSeqCurr
{
	float Izd;				//零序电流 3I0 定值
	float If_Ratio;			//短路电流: 倍数
	float Zf_Mag;			//短路阻抗: 幅值, 灵敏角 (计算模型: 定电流)
	float Zf_Ang;
	int FaultType;			//故障类型: 见 FaultEnum_FaultType
	int FaultDirection;		//故障方向: 0--正方向, 1--反方向
	//
	float Us;				//额定电压
	float ILoad_Mag;		//负荷电流
	float ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//
	int KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	float KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	float KL_Ang;
	float KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//差动计算: 根据 Id,Ir 计算两侧所加电流 Iabc,Ixyz
struct FaultCalc_Diff
{
	int TestItem;			//测试项目：见 FaultEnum_Diff_TestItem
	int FaultType;			//测试相别: 见 FaultEnum_Diff_FaultType, 012--ABC,  345--AB,BC,CA;  6--ABC
	float Ir;				//计算用的 (Ir, Id), (Id, Harm), (Id, GapAng)
	float Id;
	float Harm;				//谐波含量: 百分比, 如 0.2(即 20%)
	int Harm_Num;			//谐波次数
	int Harm_Pos;			//谐波施加侧: 0--I1侧, 1--I2侧;
	float GapAng;			//间断角: 度
	int GapAng_Pos;			//间断角施加侧: 0--I1侧, 1--I2侧;
	//
	int IdEquation;		//Id 动作方程索引号: 0,12,34; 见 FaultEnum_Diff_IdEquation
	int IrEquation;		//Ir 制动方程索引号: ..., 见 FaultEnum_Diff_IrEquation
	float K;
	float KP1;			//I1, I2侧的CT变比补偿系数(按三相对称状态计算)	
	float KP2;
	float I1_Ang;
	float I2_Ang;		//测试仪第12组电流基准相位;
	//
	//根据以下参数, 结合 FaultType 计算实际使用的 K1, K2 修正系数, 及 I1,I2 角度
	//
	int ProtSort;			//保护分类: 见 FaultEnum_ProtSort
	int TransWindType;		//变压器绕组数: 见 FaultEnum_TransWindType
	int TransGroupMode;		//变压器接线组别: 见 FaultEnum_TransGroupMode_TwoWindings, ThreeWindings
	int AdoptWind;			//参与试验的绕组: 见 FaultEnum_AdoptWind 
	int PhaseCompMode;		//保护内部相位校正方式: 见 FaultEnum_PhaseCompMode
	int Y0CompMode;			//保护内部零序修正方式: 0--无校正; 1-- Y 侧做 I0 校正
	//
	FaultCalcResult_Diff Result;
};

//差动计算: 差动整组
struct FaultCalc_Diff_Shot
{
	//变压器接线(保护设置), 用于确定变压器钟点 m_nClock
	int ProtSort;			//保护分类: 见 FaultEnum_ProtSort
	int TransWindType;		//变压器绕组数: 见 FaultEnum_TransWindType
	int TransGroupMode;		//变压器接线组别: 见 FaultEnum_TransGroupMode_TwoWindings, ThreeWindings
	int AdoptWind;			//参与试验的绕组: 见 FaultEnum_AdoptWind 
	//
	int I1_bY0;			//1--Y0; 0--Y,d
	int I2_bY0;	
	int PowerPos;		//电源位置: 0--I1侧, 1--I2侧;
	int FaultPos;		//故障点位置: 0--I1侧,     1--I2侧
	int FaultArea;		//            0--区内故障; 1--区外故障
	int FaultType;		//故障类型: 见 FaultEnum_Diff_FaultType, 012--ABC,  345--AB,BC,CA;  6--ABC
	float FaultIp;		//故障电流: CT 二次侧值
	int DirectionMode;	//电流正方向设置: 0--元件内部故障为正;  1--元件外部故障为正
	//
	FaultCalcResult_Diff Result;	//只需要其中的 6 路基波电流
};

//差动计算: 根据 6 路电流, 计算差流和制流
struct FaultCalc_Diff_IrId
{
	FaultStruct_Phase I1[3];	//I1: ABC
	FaultStruct_Phase I2[3];	//I2: abc
	//
	int IdEquation;		//Id 动作方程索引号: 0,12,34; 见 FaultEnum_Diff_IdEquation
	int IrEquation;		//Ir 制动方程索引号: ..., 见 FaultEnum_Diff_IrEquation
	float K;
	float KP1;				//I1, I2侧的CT变比补偿系数(按三相对称状态计算)	
	float KP2;
	//
	//变压器接线(保护设置), 用于确定变压器钟点 m_nClock
	int ProtSort;			//保护分类: 见 FaultEnum_ProtSort
	int TransWindType;		//变压器绕组数: 见 FaultEnum_TransWindType
	int TransGroupMode;		//变压器接线组别: 见 FaultEnum_TransGroupMode_TwoWindings, ThreeWindings
	int AdoptWind;			//参与试验的绕组: 见 FaultEnum_AdoptWind 
	//
	int PhaseCompMode;		//保护内部相位校正方式: 见 FaultEnum_PhaseCompMode
	int Y0CompMode;			//保护内部零序修正方式: 0--无校正; 1-- Y 侧做 I0 校正
	//
	FaultCalcResult_Diff_IrId Result;	
};

//差动计算: 补偿系数 KPH,M,L 辅助计算(三相对称)
struct FaultCalc_Diff_KP
{
	//保护设置
	int ProtSort;			//保护分类: 见 FaultEnum_ProtSort
	//计算模式
	int CalcuMode;			//电流补偿系数计算方式: 0--根据额定电压和CT变比归算至高压侧
	//                      1--根据额定电流In'归算至高压侧
	//                      2--标么值计算(RCS-978, 额定电流In'的倒数)
	float Sn;			//变压器额定容量(标准)
	float Un[3];		//变压器三侧额定电压(012--高中低)
	float CT[3];		//变压器三侧 CT 变比;
	float In[3];		//变压器三侧额定电流(归算至各 CT 的二次侧)
	//计算结果
	FaultCalcResult_Diff_KP Result;
};

//电铁差动: 根据 Id,Ir 计算两侧所加电流 Iabc,Ixy
struct FaultCalc_Diff5
{
	int TestItem;			//测试项目：见 FaultEnum_Diff_TestItem
	int FaultType;			//测试相别: 见 FaultEnum_Diff_FaultType, 012--ABC,  345--AB,BC,CA;  6--ABC
	float Ir;				//计算用的 (Ir, Id), (Id, Harm), (Id, GapAng)
	float Id;
	float Harm;				//谐波含量: 百分比, 如 0.2(即 20%)
	int Harm_Num;			//谐波次数
	int Harm_Pos;			//谐波施加侧: 0--I1侧, 1--I2侧;
	float GapAng;			//间断角: 度
	int GapAng_Pos;			//间断角施加侧: 0--I1侧, 1--I2侧;
	//
	int IdEquation;		//Id 动作方程索引号: 0,12,34; 见 FaultEnum_Diff5_IdEquation
	int IrEquation;		//Ir 制动方程索引号: ..., 见 FaultEnum_Diff5_IrEquation
	float K;
	float KP1;			//I1, I2侧的CT变比补偿系数(按三相对称状态计算)	
	float KP2;
	float I1_Ang;
	float I2_Ang;		//测试仪第12组电流基准相位;
	//
	//根据以下参数, 结合 FaultType 计算实际使用的 K1, K2 修正系数, 及 I1,I2 角度
	//
	int ProtSort;			//保护分类: 见 FaultEnum_ProtSort
	int TransWindType;		//变压器绕组数: 见 FaultEnum_TransWindType
	int TransGroupMode;		//变压器接线组别: 见 FaultEnum_TransGroupMode_TwoWindings, ThreeWindings
	int AdoptWind;			//参与试验的绕组: 见 FaultEnum_AdoptWind 
	int PhaseCompMode;		//保护内部相位校正方式: 见 FaultEnum_PhaseCompMode
	int Y0CompMode;			//保护内部零序修正方式: 0--无校正; 1-- Y 侧做 I0 校正
	//
	FaultCalcResult_Diff Result;
};

//功率振荡: 当前发电机角下, 保护安装处 K 点的电压电流有效值
struct FaultCalc_Osc
{
};
//功率振荡: 当前发电机角下, 保护安装处 K 点的测量阻抗
struct FaultCalc_Osc_Zk
{
};

#endif
