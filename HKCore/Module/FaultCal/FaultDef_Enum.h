//----------------------------------------------------------------------
//Fault 枚举变量, 供内部和二次开发使用
//命名规则: FaultEnum_... 
//----------------------------------------------------------------------
//   FaultEnum_Error -- 试验过程中的错误代码监视
//----------------------------------------------------
//   FaultEnum_DRTSMode -- 多机同步方式
//   FaultEnum_TestMode -- 批量测试模式
//   FaultEnum_TestState -- 当前测试状态
//   FaultEnum_Fault     -- 故障类型
//   FaultEnum_CalcuMode -- 短路计算模型
//   FaultEnum_KL_Mode   -- 零序补偿系数的设置模式
//   FaultEnum_TrigMode -- 触发方式(故障触发, 状态触发)
//   FaultEnum_UxMode -- Ux 输出方式(第4路电压)
//   FaultEnum_SynMode -- 测试仪运行方式
//   FaultEnum_UabcMode -- Uabc 系统输出方式
//   FaultEnum_IabcMode -- Iabc 系统输出方式
//----------------------------------------------------
//   FaultEnum_Diff_TestItem -- 差动试验: 测试项目
//   FaultEnum_Diff_FaultType -- 差动试验: 测试相别(故障类型)
//   FaultEnum_Diff_IdEquation -- 差动试验: 差动方程
//   FaultEnum_Diff_IrEquation_0 -- 差动试验: 制动方程
//   FaultEnum_Diff_IrEquation_1
//   FaultEnum_Diff_IrEquation_2
//   FaultEnum_Diff_IrEquation_3
//   FaultEnum_Diff_IrEquation_4
//   FaultEnum_Diff_ProtSort -- 差动试验: 差动保护类别
//   FaultEnum_Diff_TransWindType -- 差动试验: 变压器绕组数: 双绕组, 三绕组
//   FaultEnum_Diff_TransGroupMode_2Windings -- 差动试验: 接线组别(双绕组)Y/Y-12, Y/D-11, ...
//   FaultEnum_Diff_TransGroupMode_3Windings --                   (三绕组)Y/Y/Y-12, ... 
//   FaultEnum_Diff_AdoptWind -- 差动试验: 参与试验的绕组
//   FaultEnum_Diff_PhaseCompMode -- 差动试验: 相位补偿方式
//----------------------------------------------------
//   FaultEnum_Syn_TestItem -- 同期试验: 测试项目


//---------------------------------------------------------------------
#if !defined(_FaultDEF_ENUM)
#define _FaultDEF_ENUM

//多机同步方式: 多机同步盒, 电网时钟
enum FaultEnum_DRTSMode
{
	DRTSMODE_NO=-1,	DRTSMODE_SYNBOX,	DRTSMODE_GRIDPLL,	//无同步功能, 外接同步盒, 电网同步
};
//批量测试方式
enum FaultEnum_TestMode
{
	TESTMODE_SINGLE=0,  TESTMODE_BATCH,  TESTMODE_FROM,  TESTMODE_FAILED,
};
//当前测试状态
enum FaultEnum_TestState
{
	TESTSTATE_WAIT=-1,  TESTSTATE_FAIL,  TESTSTATE_SUCCESS,  TESTSTATE_TESTING
};

enum FaultEnum_FaultType
{
	FAULT_FREESET=-1,		//自定义故障
	FAULT_A,				//单相接地
	FAULT_B,
	FAULT_C,
	FAULT_AB,				//两相相间
	FAULT_BC,
	FAULT_CA,
	FAULT_ABE,				//两相接地
	FAULT_BCE,
	FAULT_CAE,
	FAULT_ABC,				//三相短路
};
enum FaultEnum_CalcuMode
{
	CALCUMODE_IF=0,			//0--短路电流 If 恒定
	CALCUMODE_UF,			//1--短路电压 Uf 恒定
	CALCUMODE_ZS,			//2--电源阻抗 Zs 恒定
};
enum FaultEnum_KL_Mode
{
	KL=0,					//0--圆形 KL 方式, KL=(Z0-Z1)/3Z1
	KR_KX,					//1--四边形 KR, KX 方式, KR=(R0-R1)/3R1, KX=(X0-X1)/3X1
};
enum FaultEnum_TrigMode
{
	TRIGMODE_PRESSKEY=0,		//0--按键触发
	TRIGMODE_TIMER,				//1--时间触发
	TRIGMODE_GPS,				//2--GPS触发
	TRIGMODE_BIN,				//3--开入接点翻转触发
	TRIGMODE_MAG,				//4--幅值触发
	TRIGMODE_FRE,				//5--频率触发
	TRIGMODE_BIN_TIMER,			//6--开入接点翻转触发 + 最大限时
};
enum FaultEnum_UabcMode
{
	UABC_MAPTO_ABC=0,	//0--abc
	UABC_MAPTO_XYZ,		//1--xyz
	UABC_MAPTO_UVW,		//2--uvw
	UABC_MAPTO_RST,		//3--rst
};
enum FaultEnum_IabcMode
{
	IABC_MAPTO_ABC=0,	//0--abc
	IABC_MAPTO_XYZ,		//1--xyz
	IABC_MAPTO_UVW,		//2--uvw
	IABC_MAPTO_RST,		//3--rst
	IABC_MAPTO_GROUP12_PARALLEL,	//4--12组并联
	IABC_MAPTO_GROUP123_PARALLEL,	//5--123组并联
};
enum FaultEnum_UxMode
{
	UX_NONEED=-1,		//不需要第 4 路电压 Ux;
	UX_3U0=0,			//+3U0
	UX_3U0_NEG,			//-3U0
	UX_3U0_ROOT3,		//+√3 * 3Uo
	UX_3U0_ROOT3_NEG,	//-√3 * 3Uo
	UX_SYN_A,		//检同期A
	UX_SYN_B,		//检同期B
	UX_SYN_C,		//检同期C
	UX_SYN_AB,		//检同期AB
	UX_SYN_BC,		//检同期BC
	UX_SYN_CA,		//检同期CA
};
enum FaultEnum_SynMode		//测试仪运行方式
{
	SYNMODE_NO,			//0--无同步, 单机运行
	SYNMODE_GPS,		//1--GPS 同步
	SYNMODE_GRIDPLL,	//2--电网同步
};

//----------------------------------------------------------------------
enum FaultEnum_Diff_TestItem
{
	BIASED_DIFFERENTIAL=0,	    //0--比率制动
	HARMONIC_RESTRAIN,			//1--谐波制动
	DEADANG_RESTRAIN,			//2--间断角制动
};
enum FaultEnum_Diff_FaultType
{
	DIFF_A=0,
	DIFF_B,
	DIFF_C,
	DIFF_AB,
	DIFF_BC,
	DIFF_CA,
	DIFF_ABC,
};
enum FaultEnum_Diff_IdEquation	//差流方程 Id
{
	ID0 = 0,	//0-- Id= I1
	ID1,		//1-- Id=|I1'+I2'|
	ID2,		//2-- Id=|I1'-I2'|
	ID3,		//3-- Id=|I1'+I2'|^2
	ID4,		//4-- Id=|I1'-I2'|^2
};
enum FaultEnum_Diff_IrEquation_0	//制流方程 Ir, IdEquation=0
{
	IR0_ID0 = 0,		//0-- Ir= I2
};
enum FaultEnum_Diff_IrEquation_1	//制流方程 Ir, IdEquation=1
{
	IR0_ID1 = 0,		//0-- Ir = |I1'-I2'|/K
	IR1_ID1,			//1-- Ir = Max(|I1'|,|I2'|)*K
	IR2_ID1,			//2-- Ir = |I2'|
	IR3_ID1,			//3-- Ir = |Id-|I1'|-|I2'||
	IR4_ID1,			//4-- Ir = (|I1'|+|I2'|)/K
	IR5_ID1,			//5-- Ir = |Imax'-∑Ii'|/K, Ii'≠Imax'
	IR6_ID1,			//6-- Ir = √(|I1'×I2'| * cosθ)
};
enum FaultEnum_Diff_IrEquation_2	//制流方程 Ir, IdEquation=2
{
	IR0_ID2 = 0,		//0-- Ir = |I1'+I2'|/K
	IR1_ID2,			//1-- Ir = Max(|I1'|,|I2'|)*K
	IR2_ID2,			//2-- Ir = |I2'|
	IR3_ID2,			//3-- Ir = |Id-|I1'|-|I2'||
	IR4_ID2,			//4-- Ir = (|I1'|+|I2'|)/K
	IR5_ID2,			//5-- Ir = |Imax'+∑Ii'|/K, Ii'≠Imax'
	IR6_ID2,			//6-- Ir = √(|I1'×I2'| * cosθ)
};
enum FaultEnum_Diff_IrEquation_3	//制流方程 Ir, IdEquation=3
{
	IR0_ID3 = 0,		//Ir = -|I1'×I2'| * cosθ
};
enum FaultEnum_Diff_IrEquation_4	//制流方程 Ir, IdEquation=4
{
	IR0_ID4 = 0,		//Ir = |I1'×I2'| * cosθ
};

enum FaultEnum_Diff_ProtSort
{
	PROT_TRANS=0,	//0--变压器
	PROT_GENTRANS,	//1--发变组
	PROT_GEN,		//2--发电机
	PROT_BUS,		//3--母差
};
enum FaultEnum_Diff_TransWindType
{
	TWO_WINDINGS=0,		//0--双绕组
	THREE_WINDINGS,		//1--三绕组
};
enum FaultEnum_Diff_TransGroupMode_2Windings	//双绕变接线组别
{
	YY_12=0,
	YD_11,
	YD_1,
	YD_3,
	YD_5,   
	YD_7,
	YD_9,
	YY_2,
	YY_4,
	YY_6,
	YY_8, 
	YY_10,
};
enum FaultEnum_Diff_TransGroupMode_3Windings	//三绕变接线组别
{
	YYY_12=0, 
	YYD_11,
	YYD_1,
	YDD_11,
	YDD_1,
};
enum FaultEnum_Diff_AdoptWind	//参与试验的变压器绕组
{
	H_L=0,		//0--高-低
	H_M,		//1--高-中
	M_L,		//2--中-低
};
enum FaultEnum_Diff_PhaseCompMode	//保护内部相位校正方式
{
	PHASECOMP_NO=0,			//0--无校正
	PHASECOMP_Y,			//1--Y侧校正
	PHASECOMP_D,			//2--d侧校正
};
enum FaultEnum_Diff5_TransGroupMode	//电铁变压器组别(类别)
{
	DIFF5_BALANCE_Z=0,		//0-- 平衡变压器 -- 阻抗匹配
	DIFF5_YD11,				//1-- Y/△-11 变压器
	DIFF5_VV,				//2-- V/V 变压器
	DIFF5_BALANCE_SCOTT,	//3-- 平衡变压器 -- SCOTT
	DIFF5_YDD,				//4-- Y/△/△-11变压器
	DIFF5_VX,				//5-- V/X 变压器
	DIFF5_SINGLEPHASE,		//6-- 单相变压器
};

enum FaultEnum_Syn_TestType		//同期试验: 测试项目类别
{
	SYN_CHECK=0,			//0--合闸类测试: 点测, 是否合闸(记录导前角, 计算导前时间)
	SYN_ADJUSTV,			//1--调压脉宽
	SYN_ADJUSTFRE,			//2--调频脉宽
	SYN_ADJUSTAUTO,			//3--自动调整试验
};

#endif