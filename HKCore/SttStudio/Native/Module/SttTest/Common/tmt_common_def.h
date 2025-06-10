#pragma once

#include "../../Module/OSInterface/OSInterface.h"
#ifdef _PSX_QT_LINUX_
    #include "tmt_adjust_sys_parameter.h"
#endif
#include "tmt_test_paras_head.h"

#ifndef NOT_USE_XLANGUAGE
#include "../../XLangResource_Native.h"
#endif

#define MAX_HARM_COUNT			81
#define MAX_HARM_COUNT_UI			51
#define MAX_BINARYIN_COUNT		20
#define MAX_BINARYOUT_COUNT		20
#define MAX_VOLTAGE_COUNT		48
#define MAX_CURRENT_COUNT		MAX_VOLTAGE_COUNT
//zhouhj 2023.9.15 删除此宏,统一使用上面的开入或开出对应的宏,目前实际数量会大于10
//#define MAX_PARACOUNT_BINARY 	10//通常10个开入配置
#define MAX_MODULE_COUNT		12		//最大模块数
#define MAX_ExBINARY_COUNT		256//最大扩展开关量数量,软件资源开放256in,256out,最大8个扩展模块
#define BIBO_ACTCOUNT			64//开入开出事件每个硬件端子记录变位总次数
//根据硬件情况,16个点为一组
#define MAX_GOOSE_CHANNEL_COUNT	256
#define MAX_MODULES_GOOSEPUB_COUNT 16 //16*4
//Ft3
#define MAX_FT3_CHANNEL_COUNT	100
#define MAX_MODULES_FT3PUB_COUNT 18 //12(DRT400) + 6(9-2/FT3)
//稳控2M通道数量
#define MAX_2M_CHANNEL_COUNT    16
#define MAX_2M_BLOCK_COUNT      8
#define MAX_2M_DATAIDX_COUNT    16
#define MAX_2M_DATAIDX_VALUE    22
#define MAX_2M_CMDIDX_COUNT     2
#define MAX_2M_MODULE_COUNT     2
#define MAX_2M_BLOCKS_COUNT     MAX_2M_BLOCK_COUNT * MAX_2M_MODULE_COUNT


//异步模块类型数量  模拟量、弱信号、数字量
#define ASYNC_MODULE_TYPE_COUNT		3
#define ASYNC_MODULE_TYPE_ANALOG		0
#define ASYNC_MODULE_TYPE_WEEK			1
#define ASYNC_MODULE_TYPE_DIGITAL		2


#define DC_CURRENT_COMMON_FAULT_TYPE_I1_1                                                    0
#define DC_CURRENT_COMMON_FAULT_TYPE_I1_2                                                    1
#define DC_CURRENT_COMMON_FAULT_TYPE_I1_3                                                    2
#define DC_CURRENT_COMMON_FAULT_TYPE_I2_1                                                    3
#define DC_CURRENT_COMMON_FAULT_TYPE_I2_2                                                    4
#define DC_CURRENT_COMMON_FAULT_TYPE_I2_3                                                    5
#define DC_CURRENT_COMMON_FAULT_TYPE_I3_1                                                    6
#define DC_CURRENT_COMMON_FAULT_TYPE_I3_2                                                    7
#define DC_CURRENT_COMMON_FAULT_TYPE_I3_3                                                    8
#define DC_CURRENT_COMMON_FAULT_TYPE_I4_1                                                    9
#define DC_CURRENT_COMMON_FAULT_TYPE_I4_2                                                    10
#define DC_CURRENT_COMMON_FAULT_TYPE_I4_3                                                    11


#define EPSINON 0.000001//float保证精度的最小值
#define pi 3.14159265357979823846

//递变类型相关宏定义
#define GRADIENT_MAX_COUNT	  20000//最大递变步数
#define DGRESS_PARAM_MAX      74//每步递变参数字节数
#define GRADIENT_AMP		   0//幅值
#define GRADIENT_ANG           1//相位
#define GRADIENT_FRE           2//频率
#define GRADIENT_CHAN_COUNT    6//递变支持最大2组6路,6U6I

#define GRADIENT_TYPE_None	   0//无递变
#define GRADIENT_TYPE_Linear   1//线性变化
#define GRADIENT_TYPE_Step	   2//阶梯变化

#define STT_BOUT_REVERSAL_TRIG_MODE_TIME                          0   //开出翻转方式:开出参考值为上一态,时间触发,翻转时间为0立马翻转,否则按设置时间翻转;翻转保持时间设置为0则不会翻转
#define STT_BOUT_REVERSAL_TRIG_MODE_BIN                           1   //开出翻转方式:开入量触发
#define STT_BOUT_REVERSAL_TRIG_MODE_NOT                           2   //开出翻转方式:不翻转,按设置值输出,第一个状态固定为此值
#define STT_BOUT_REVERSAL_TRIG_MODE_LAST_STATE                    3   //不翻转保持上一态

#define STT_PT_IMIT_PHASE_A                          0  //PT断线相模拟  A相断线 .过流模块、电流动作值测试用到
#define STT_PT_IMIT_PHASE_B                          1
#define STT_PT_IMIT_PHASE_C                          2
#define STT_PT_IMIT_PHASE_AB                         3
#define STT_PT_IMIT_PHASE_BC                         4
#define STT_PT_IMIT_PHASE_CA                         5
#define STT_PT_IMIT_PHASE_ABC                        6

#define  TMT_BINLOGIC_AND 1//开入与
#define  TMT_BINLOGIC_OR  0//开入或

//状态序列（同步异步）共有宏
#define  TMT_MDSTATE_TIMETRIGGER                       0	    //0--时间触发
#define  TMT_MDSTATE_TIMEBINTRIGGER                1    	//1--时间+开入量触发
#define  TMT_MDSTATE_BINTRIGGER                          2		//2--开入量触发
#define  TMT_MDSTATE_MEARSURETRIGGER          3      //3--手动触发
#define  TMT_MDSTATE_GPSBTRIGGER                      4		//4--GPS/B码触发
#define  TMT_MDSTATE_LOWVOLTRIGGER                 5     //5--低电压触发
#define  MAX_STATE_NAME			128  //zhouhj 20211208 对于GOOSE异常模拟此状态序列名称中长度可能超过32字节 将其改为128
#define  MAX_STATE_ID           7 
#define STT_SINGLE_STATE_MAX_REPORT_COUNT         6   //dingxy 20240606 根据状态数加载不同报告
#define STT_STATE_REPORT_MAX_REPEAT_COUNT        10
#define STT_STATE_REPORT_TOTAL_STATE_NUM          20		 //dingxy 20240607 状态序列最大总个数(统计多次循环的总状态数)




#define STT_MACRO_ID_SystemConfig           "SystemConfig"
#define STT_MACRO_ID_UartConfig             "UartConfig"
#define STT_MACRO_ID_AuxDCOutput            "AuxDCOutput"//增加用于辅助直流输出设置  zhouhj 20211016 增加用于独立设置辅助直流
#define STT_MACRO_ID_ModulesGearSwitch      "ModulesGearSwitch"//增加用于档位切换//增加用于独立切换档位
#define STT_MACRO_ID_AppConfig              "AppConfig" //增加用于设置测试仪变比  该ID为兼容旧版接口 zhouhj 20221207
#define STT_MACRO_ID_ModuleOutput           "ModuleOutput"
#define STT_MACRO_ID_BinaryOutput           "BinaryOutput"
#define STT_MACRO_ID_BinaryExOutput         "BinaryExOutput"
#define STT_MACRO_ID_RegisterTest           "RegisterTest"
#define STT_MACRO_ID_BinMeas				"BinMeas"//开入采集
#define STT_MACRO_ID_SystemDefaultOutput    "SystemDefaultOutput"
#define STT_MACRO_ID_Iec61850Config     	"Iec61850Config"
#define STT_MACRO_ID_ChMapsConfig      		"ChMapsConfig"
#define STT_MACRO_ID_GradientTest      		"GradientTest"
#define STT_MACRO_ID_GradientMaxAngleTest   "GradientMaxAngleTest"
#define STT_MACRO_ID_GradientU				"GradientU"
#define STT_MACRO_ID_GradientI				"GradientI"

#define STT_MACRO_ID_ManualTest             "ManualTest"
#define STT_MACRO_ID_StateTest              "StateTest"
#define STT_MACRO_ID_HarmTest               "HarmTest"
#define STT_MACRO_ID_SoeTest                "SoeTest"
#define STT_MACRO_ID_SmvAbnTest				"SmvAbnTest"
#define STT_MACRO_ID_GseAbnTest				"GseAbnTest"

#define STT_MACRO_ID_SequenceManuTest       "SequenceManuTest"
#define STT_MACRO_ID_PowerManuTest          "PowerManuTest"
#define STT_MACRO_ID_LineVolManuTest        "LineVolManuTest"
#define STT_MACRO_ID_BinaryStateTest        "BinaryStateTest"//20230130 zhouhj 增加用于开关量状态序列
#define STT_MACRO_ID_BinaryManuTest         "BinaryManuTest"//开关量手动测试
#define STT_MACRO_ID_SequenceGradientTest    "SequenceGradientTest"
#define STT_MACRO_ID_ImpedManualTest             "ImpedManualTest"//2024.6.14 张焱琪
#define STT_MACRO_ID_PnvSCActValue   "SCActValue"

#define STT_MACRO_ID_FaultGradientTest    "FaultGradientTest" //2023-12-28 yuanting
#define STT_MACRO_ID_LineVolGradientTest     "LineVolGradientTest"
//兼容老版接口程序,新增MacroID  20221205 zhouhj
#define STT_MACRO_ID_State6U6I               "State6U6I"
#define STT_MACRO_ID_State4U3I               "State4U3I"
#define STT_MACRO_ID_UITest_12u12i            "UITest.12u12i"
#define STT_MACRO_ID_StateDiffCoef               "StateDiffCoef"
#define STT_MACRO_ID_PsuStateTest               "PsuStateTest"


#define STT_MACRO_ID_Distance               "Distance"//zhouhj 20210626 底层测试功能类中MacroID与上位机结构体共用MacroID
#define STT_MACRO_ID_Distance_I             "Distance_I"//
#define STT_MACRO_ID_DistanceSearch         "DistanceSearch"
#define STT_MACRO_ID_DistanceSearch_I         "DistanceSearch_I"
#define STT_MACRO_ID_RecloseAcc             "RecloseAcc"
#define STT_MACRO_ID_TURecloseAcc           "TURecloseAcc"//配网专用重合闸后加速模块
#define STT_MACRO_ID_StateRecloseAcc             "StateRecloseAcc"//Pnv新增
#define STT_MACRO_ID_PsuCBOperate           "PsuCBOperate"
#define STT_MACRO_ID_StateOverCurrent       "StateOverCurrent"
#define STT_MACRO_ID_OverCurrent            "OverCurrent"
#define STT_MACRO_ID_VoltageTest            "VoltageTest"
#define STT_MACRO_ID_StateI0Current         "StateI0Current"
#define STT_MACRO_ID_ZeroCurrent            "ZeroCurrent"
#define STT_MACRO_ID_DiffCBOp				"DiffCBOp"  //整组差动

#define STT_MACRO_ID_ULockOverCurrent       "ULockOverCurrent"
#define STT_MACRO_ID_PowerDirection         "PsuPowerDirection"
#define STT_MACRO_ID_PowerDirection_I         "PsuPowerDirection_I"
#define STT_MACRO_ID_PnvPowerDirection         "ActAngle"
#define STT_MACRO_ID_ActionTime             "ActionTime"
#define STT_MACRO_ID_CurrentInverseTime     "CurrentInverseTime"
#define STT_MACRO_ID_VoltageInverseTime     "VoltageInverseTime"
#define STT_MACRO_ID_VFInverseTime          "VFInverseTime"

#define STT_MACRO_ID_CurrentActValue        "CurrentActValue"
#define STT_MACRO_ID_VoltageActValue        "VoltageActValue"

#define STT_MACRO_ID_PnvCurrentActValue        "IActValue"
#define STT_MACRO_ID_PnvVoltageActValue        "UActValue"


#define STT_MACRO_ID_PsuLowFreqAct             "PsuLowFreqAct"
#define STT_MACRO_ID_PsuLowFreqTime            "PsuLowFreqTime"
#define STT_MACRO_ID_PsuLowFreqDfdt            "PsuLowFreqDfdt"
#define STT_MACRO_ID_PsuLowFreqILock           "PsuLowFreqILock"
#define STT_MACRO_ID_PsuLowFreqULock           "PsuLowFreqULock"

#define STT_MACRO_ID_PnvLowFreqTime            "LowFreqActTime"
#define STT_MACRO_ID_PnvLowFreqAct             "LowFreqActVal"
#define STT_MACRO_ID_PnvLowFreqDfdt            "LowFreqDfdt"

#define STT_MACRO_ID_PsuLowVolAct             "PsuLowVolAct"
#define STT_MACRO_ID_PsuLowVolTime            "PsuLowVolTime"
#define STT_MACRO_ID_PsuLowVolDvdt            "PsuLowVolDvdt"
#define STT_MACRO_ID_PsuLowVolILock              "PsuLowVolILock" 

#define STT_MACRO_ID_PnvLowVolAct             "LowVolActVal"
#define STT_MACRO_ID_PnvLowVolTime            "LowVolActTime"
#define STT_MACRO_ID_PnvLowVolDvdt            "LowVolDvdt"

#define STT_MACRO_ID_PsuPowerFreqDist          "PsuPowerFreqDist"//PsuVm中工频变化量的ID
#define STT_MACRO_ID_LFPGP                     "LFPGP"//PonovoVm中工频变化量的ID

#define STT_MACRO_ID_PsuSwing                "PsuSwingTest"

#define STT_MACRO_ID_SynActVoltageTest            "SynActVoltageTest"
#define STT_MACRO_ID_SynActFreqTest               "SynActFreqTest"
#define STT_MACRO_ID_SynLeadAngTest               "SynLeadAngTest"//导前角及导前时间测试
#define STT_MACRO_ID_SynAutoAdjTest               "SynAutoAdjTest"//、自调整试验  都用此
//#define STT_MACRO_ID_SynAdjCycleTest               "SynAdjCycleTest"//调压周期、调频周期,都用此测试
#define STT_MACRO_ID_SynAdjVolTest                "SynAdjVolTest"
#define STT_MACRO_ID_SynAdjFreqTest               "SynAdjFreqTest"


#define STT_MACRO_ID_PsuDiffTCurrTest             "PsuDiffTCurrTest" //常规差动相关MacroID
#define STT_MACRO_ID_PsuDiffRateTest              "PsuDiffRateTest"
#define STT_MACRO_ID_PsuDiffQuickTest             "PsuDiffQCurrTest"
#define STT_MACRO_ID_PsuDiffHarmTest              "PsuDiffHarmTest"
#define STT_MACRO_ID_PsuDiffTimeTest              "PsuDiffTimeTest"

#define STT_MACRO_ID_Diff6IRateRestrainSearchTest             "Diff6IRateRestrainSearch" //差动(6i)相关MacroID
#define STT_MACRO_ID_Diff6IRateRestrainTest             "Diff6IRateRestrain"
#define STT_MACRO_ID_Diff6IHarmRestrainSearchTest             "Diff6IHarmRestrainSearch"

#define STT_MACRO_ID_PsuManuDiffTCurrTest             "PsuManuDiffTCurrTest" //手动递变
#define STT_MACRO_ID_PsuManuDiffRateTest              "PsuManuDiffRateTest"
#define STT_MACRO_ID_PsuManuDiffQuickTest             "PsuManuDiffQCurrTest"
#define STT_MACRO_ID_PsuManuDiffHarmTest              "PsuManuDiffHarmTest"


#define STT_MACRO_ID_ElecRailwayDiffTest            "ElecRailwayDiffTest"//电铁牵引变相关MacroID
#define STT_MACRO_ID_ElecRailwayDiffRateTest        "ElecRailwayDiffRateTest"
#define STT_MACRO_ID_ElecRailwayDiffQuickTest       "ElecRailwayDiffQCurrTest"
#define STT_MACRO_ID_ElecRailwayDiffHarmTest        "ElecRailwayDiffHarmTest"
#define STT_MACRO_ID_ElecRailwayDiffTimeTest        "ElecRailwayDiffTimeTest"

#define STT_MACRO_ID_BP2DiffTCurrTest             "BP2DiffTCurrTest" //BP2差动相关MacroID
#define STT_MACRO_ID_BP2DiffRateTest              "BP2DiffRateTest"
#define STT_MACRO_ID_BP2CBOperateTest             "BP2CBOperateTest"

#define STT_MACRO_ID_DcIncrementTest              "DcIncrementTest"

#define STT_MACRO_ID_ReplayTest                   "ReplayTest"
#define STT_MACRO_ID_DigReplayTest                "DigReplayTest"
#define STT_MACRO_ID_Pid01Test              "Pid01Test"
#define STT_MACRO_ID_Pid16Test              "Pid16Test"

#define STT_MACRO_ID_IecDetect              "IecDetect"
#define STT_MACRO_ID_IecRecord              "IecRecord"

#define STT_MACRO_ID_UpdateFPGA              "UpdateFPGA"
#define STT_MACRO_ID_LcPowerTest			 "LcPowerTest"

#define STT_MACRO_ID_DCOverLoadTest     "DCOverLoadTest"  //cl过负荷(直流)
#define STT_MACRO_ID_OverLoadTest       "OverLoadTest"  //过负荷(交流)
#define STT_MACRO_ID_DCVoltageTest      "DCVoltageTest"//过压测试(直流)
#define STT_MACRO_ID_OverVoltageTest    "OverVoltageTest"//过压测试(交流)
#define STT_MACRO_ID_DCOverCurrentTest  "DCOverCurrentTest"//过流测试(直流)

#define STT_MACRO_ID_DCBreakTest              "DCBreakTest"//开关保护测试(直流)

#define STT_MACRO_ID_DCFailureProtTest               "DCFailTest"    //失灵保护测试(直流) //lichunqing 2023-11-16
#define STT_MACRO_ID_FailureProtActValue             "DCFailActValueTest"      //失灵保护测试项/1段动作值
#define STT_MACRO_ID_FailureProtActTime              "DCFailActTimeTest"       //失灵保护测试项/1段动作时间
#define STT_MACRO_ID_FailureProtDidtActValue         "DCFailDidtActValueTest"  //失灵保护测试项/2段动作值
#define STT_MACRO_ID_FailureProtDidtActTime          "DCFailDidtActTimeTest"   //失灵保护测试项/2段动作时间

#define STT_MACRO_ID_DCUnbalanceTest  "DCUnbalanceTest"//不平衡保护(直流)
#define STT_MACRO_ID_DCDifferCurrTest       "DCDifferCurrTest"     //纵差保护(启动电流)
#define STT_MACRO_ID_DCDifferRateTest       "DCDifferRateTest"     //纵差保护(比率制动系数)
#define STT_MACRO_ID_DCDifferTimeTest       "DCDifferTimeTest"     //纵差保护(动作时间)

#define STT_MACRO_ID_ShortTimeOverTest		"ShortTimeOverTest"    //2023/11/30 wangjunsheng 添加短时过量输入模块
#define STT_MACRO_ID_VolTimeTypeSecTest  "VolTimeTypeSecTest"    //20240112 xueyangfan 电压时间型分段模式

#define STT_MACRO_ID_AnsyncStateTest  "AnsyncStateTest"			//异步状态序列
#define STT_MACRO_ID_AnsyncManualTest	"AnsyncManualTest"		//异步通用试验


typedef struct tmt_step_UI
{
public:
    void init()
    {
        for(int i = 0; i < 6; i++)
        {
            fU[i][0] = fU[i][1] = fU[i][2] =  fI[i][0] = fI[i][1] = fI[i][2] = 0;
        }
    }

    tmt_step_UI()
    {
        init();
    }

    float fU[6][3];	//12*(幅值+相位+fre)
    float fI[6][3];
} tmt_StepUI;

typedef struct tmt_binary_in
{
public:
    int		nSelect;
    int		nTrigMode;	//0-翻转触发 1-上升沿触发 2-下降沿触发

public:
    void init()
    {
        nSelect = 1;
        nTrigMode = 0;
#ifdef _PSX_QT_LINUX_
        nSelect = 0;
#endif
    }

    tmt_binary_in()
    {
        init();
    }
} tmt_BinaryIn;

typedef struct tmt_binary_out
{
public:
    int		nState;		//0-断开 1-闭合 >1-电平
    //zhouhj 20210616 增加 2-同上一个状态,用于距离等高级试验开出翻转设置
    int		nMode;		//翻转触发方式 0-时间触发 1-开入量触发 2-同上一个状态
    float	fTimeTrig;	//反转时间，0为不翻转
    float	fHoldTime;	//翻转保持时间

public:
    void init()
    {
        nState = 0;
        nMode = STT_BOUT_REVERSAL_TRIG_MODE_NOT;
        fTimeTrig = 0;
        fHoldTime = 0;
    }

    tmt_binary_out()
    {
        init();
    }
} tmt_BinaryOut;

typedef struct tmt_binary_config
{
    int				m_nBinLogic;			//0-或 1-与
    tmt_BinaryIn    m_binIn[MAX_BINARYIN_COUNT];//主板开关量
    tmt_BinaryOut	m_binOut[MAX_BINARYOUT_COUNT];//主板开关量
    tmt_BinaryIn    m_binInEx[MAX_ExBINARY_COUNT];//系统扩展开关量
    tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];//系统扩展开关量

    tmt_BinaryOut	m_binFaultOut[MAX_BINARYOUT_COUNT];//主板故障态开出
    tmt_BinaryOut	m_binFaultOutEx[MAX_ExBINARY_COUNT];//主板故障态扩展开出

    void init()
    {
        for(int j = 0; j < MAX_BINARYOUT_COUNT; j++)
        {
            m_binOut[j].nState = 0;
            m_binOut[j].nMode = 0;
            m_binOut[j].fTimeTrig = 0;
            m_binOut[j].fHoldTime = 0;
            m_binFaultOut[j].nState = 0;
            m_binFaultOut[j].nMode = 0;
            m_binFaultOut[j].fTimeTrig = 0;
            m_binFaultOut[j].fHoldTime = 0;
            m_binIn[j].nSelect = 0;
#ifndef _PSX_QT_LINUX_

            if(j < g_nBinCount)
            {
                m_binIn[j].nSelect = 1;
            }

#endif
            m_binIn[j].nTrigMode = 0;
        }

        for(int j = 0; j < g_nBinExCount && j < MAX_ExBINARY_COUNT; j++)
        {
            m_binInEx[j].nSelect = 0;//默认扩增开入不选中
            m_binInEx[j].nTrigMode = 0;
        }

        for(int j = 0; j < g_nBoutExCount && j < MAX_ExBINARY_COUNT; j++)
        {
            m_binOutEx[j].nState = 0;//默认扩增开出全断开
            m_binOutEx[j].nMode = 0;
            m_binOutEx[j].fTimeTrig = 0;
            m_binOutEx[j].fHoldTime = 0;
            m_binFaultOutEx[j].nState = 0;//默认扩增开出全断开
            m_binFaultOutEx[j].nMode = 0;
            m_binFaultOutEx[j].fTimeTrig = 0;
            m_binFaultOutEx[j].fHoldTime = 0;
        }

        m_nBinLogic = 0;
    }

    tmt_binary_config()
    {
        init();
    }
} tmt_BinaryConfig;

typedef struct tmt_channel_harm
{
public:
    BOOL	m_bSelect;//是否使能  2024-03-25 wuxinyi 上位机使用到该变量，bool无法兼容故此修改
    int		nSelectIndex;//-1-无效 1-30代表到30个谐波含量(zhouhj 2023.7.11 上位机用此标记当前次谐波是否被修改,在更新参数时,只更新修改的通道)
    int		nIndex;
    float	fContent;//含有率
    float	fAmp;
    float	fAngle;
    float	fFreq;
    bool	bDC;

public:
    void init()
    {
        m_bSelect = FALSE;
        nIndex = 0;
        fContent = 0;
        fAmp = fAngle = fFreq = 0;
        bDC = FALSE;
        nSelectIndex = -1;
    }

    tmt_channel_harm()
    {
        init();
    }
} tmt_ChannelHarm;

typedef struct tmt_channel_ramp
{
public:
    int		nIndex;	//递变谐波序号 -1-无递变 0-递变直流 1-递变基波 2~n-递变2~n次谐波
    //	int		nType;	//递变类型：0-幅值 1-相位 2-频率
    //	int		nMode;	//递变模式：0-阶梯递变	1-滑差
    //	float	fBegin;
    float	fEnd;
    float	fStep;
    float	fStepTime;
	BOOL    bSecondChan;//双变量递变通道

public:
    void init()
    {
        /*fBegin = */fEnd = fStep = fStepTime = 0;
        //		nMode = nType = 0;
        nIndex = -1;
		bSecondChan = FALSE;
    }

    tmt_channel_ramp()
    {
        init();
    }
} tmt_ChannelRamp;

typedef struct tmt_channel
{
public:
    tmt_ChannelHarm Harm[MAX_HARM_COUNT];
    tmt_ChannelHarm InterHarm;//间谐波
    tmt_ChannelRamp Ramp[3];//zhouhj 20210724 分别对应0-幅值、1-相位、2-频率的递变

public:
    void init()
    {
        for(int j = 0; j < MAX_HARM_COUNT; j++)
        {
            Harm[j].init();
        }

        InterHarm.init();

        for(int nIndex = 0; nIndex < 3; nIndex++)
        {
            Ramp[nIndex].init();
        }
    }

    void setSel(bool bSel)
    {
        for(int i = 2; i < MAX_HARM_COUNT; i++)
        {
            Harm[i].m_bSelect = bSel;
        }
    }

    void setDC(bool bDC)
    {
        for(int j = 0; j < MAX_HARM_COUNT; j++)
        {
            Harm[j].bDC = bDC;

            if(bDC)
            {
                Harm[j].fAngle = 0;
                Harm[j].fFreq = 0;
            }
        }
    }

    void init(bool bSel, float fAmp, float fAngle, float fFreq = 0)
    {
        Harm[0].fAmp = 0;
        Harm[1].m_bSelect = true;
        Harm[1].nIndex = 1;
        Harm[1].fAngle = fAngle;
        Harm[1].fAmp = fAmp;
        Harm[1].fContent = 100;

        if(fFreq >= 1)
        {
            Harm[1].fFreq = fFreq;
        }

        for(int i = 2; i < MAX_HARM_COUNT; i++)
        {
            Harm[i].m_bSelect = bSel;
            Harm[i].nIndex = i;
            Harm[i].fAngle = fAngle;
            Harm[i].fAmp = 0;
            Harm[i].fContent = 0;

            if(fFreq >= 1)
            {
                Harm[i].fFreq = i * fFreq;
            }
        }
    }

    void setContent(int nHarmIndex, float fVal)
    {
        if((fVal >= 0) && (fVal <= 100))
        {
            Harm[nHarmIndex].fContent = fVal;
            Harm[nHarmIndex].fAmp = (float)(Harm[1].fAmp * 0.01 * fVal);
        }
    }

    void setAmp(int nHarmIndex, float fVal, BOOL bHasAna)
    {
        float fBaseAmp = Harm[1].fAmp;

        if((fBaseAmp > EPSINON)/* && (fVal <= fBaseAmp)*/)
        {
            if(bHasAna && fVal > fBaseAmp)
            {
                return;
            }

            if(fVal > EPSINON)
            {
                Harm[nHarmIndex].fAmp = fVal;
            }
            else
            {
                Harm[nHarmIndex].fAmp = 0;
            }

            //这里应该用限制过后的值，而不是fVal sf 20220221
            Harm[nHarmIndex].fContent = Harm[nHarmIndex].fAmp/*fVal*/ * 100 / fBaseAmp;
        }
    }

    float getTotalVal()
    {
        float fTotal = 0;

        for(int i = 0; i < MAX_HARM_COUNT; i++)
        {
            if(Harm[i].m_bSelect)
            {
                fTotal += Harm[i].fAmp;
            }
        }

        return fTotal;
    }

    float getCurHarmAmp(int nHarmIndex)
    {
        float fVal = 0;

        if(Harm[nHarmIndex].m_bSelect)
        {
            fVal = Harm[nHarmIndex].fAmp;
        }

        return fVal;
    }

    tmt_channel()
    {
        init();
    }
} tmt_Channel;

typedef struct tmt_time
{
public:
    int		nYear;
    int		nMonth;
    int		nDay;
    int		nHour;
    int		nMinutes;
    int		nSeconds;
    int		nMilliSeconds;

public:
    void init()
    {
        nYear = 0;
        nMonth = 0;
        nDay = 0;
        nHour = 0;
        nMinutes = 0;
        nSeconds = 0;
        nMilliSeconds = 0;
    }

    tmt_time()
    {
        init();
    }
} tmt_Time;

typedef struct
{
public:
    BOOL    m_bUChange[6][3];//mag   ph   fre
    BOOL    m_bIChange[6][3];
    tmt_StepUI m_uiStepData[GRADIENT_MAX_COUNT];	//递变数据
    int     m_nDiretionMode;//0-m_uiStepData[0]为始值  1-m_uiStepData[m_nStepCount-1]为始值
    int     m_nStepCount;
} tmt_GradientProcess;

typedef struct tmt_gradient_common
{
public:
    tmt_GradientProcess m_oGradientProcess;
public:
    tmt_gradient_common()
    {
        m_oGradientProcess.m_nStepCount = 0;
    }
} tmt_GradientCommon;

typedef struct tmt_system_default_output_paras
{
public:
    BOOL	m_bUseSysOutput;
    tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
    tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];

    void init()
    {
        m_bUseSysOutput = 0;
        float fAngle[3] = {0, -120.0, 120.0};

        for(int j = 0; j < MAX_HARM_COUNT; j++)
        {
            for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
            {
                m_uiVOL[i].Harm[j].fAmp = 0;
                m_uiVOL[i].Harm[1].fAngle = fAngle[i % 3];
                m_uiVOL[i].Harm[j].fFreq = 50;
            }

            for(int i = 0; i < MAX_CURRENT_COUNT; i++)
            {
                m_uiCUR[i].Harm[j].fAmp = 0;
                m_uiCUR[i].Harm[j].fAngle = fAngle[i % 3];
                m_uiCUR[i].Harm[j].fFreq = 50;
            }
        }

        for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
        {
            m_binOut[i].nState = 0;
        }
    }

    tmt_system_default_output_paras()
    {
        init();
    }
} TMT_SYSTEM_DEFAULT_OUTPUT_PARAS, *PTMT_SYSTEM_DEFAULT_OUTPUT_PARAS;

typedef struct tmt_goose_pub
{
    BOOL m_bUseFlag;//是否有变位
    BOOL m_bHasTest;//是否有检修位
    int m_nTest;// 是否置检修(0不置检修,1置检修)
    CString m_strChannel[MAX_GOOSE_CHANNEL_COUNT];

    void init()
    {
        m_bUseFlag = FALSE;
        m_bHasTest = FALSE;
        m_nTest = 0;

        for(int nIndex = 0; nIndex < MAX_GOOSE_CHANNEL_COUNT; nIndex++)
        {
            m_strChannel[nIndex] = "";
        }
    }

    void CopyOwn(tmt_goose_pub *pDest)
    {
        pDest->m_bUseFlag = m_bUseFlag;
        pDest->m_bHasTest = m_bHasTest;
        pDest->m_nTest = m_nTest;

        for(int nIndex = 0; nIndex < MAX_GOOSE_CHANNEL_COUNT; nIndex++)
        {
            pDest->m_strChannel[nIndex] = m_strChannel[nIndex];
        }
    }

    tmt_goose_pub()
    {
        init();
    }
} tmt_GoosePub;

typedef struct tmt_goose_pubs
{
    tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];
    void init()
    {
        for(int nIndex = 0; nIndex < MAX_MODULES_GOOSEPUB_COUNT; nIndex++)
        {
            m_oGoosePub[nIndex].init();
        }
    }

    tmt_goose_pubs()
    {
        init();
    }
} tmt_GoosePubs;

typedef struct tmt_ft3_pub
{
    BOOL m_bUseFlag;//是否有变位
    CString m_strChannel[MAX_FT3_CHANNEL_COUNT];

    void init()
    {
        m_bUseFlag = FALSE;

        for(int nIndex = 0; nIndex < MAX_FT3_CHANNEL_COUNT; nIndex++)
        {
            m_strChannel[nIndex] = "";
        }
    }

    void CopyOwn(tmt_ft3_pub *pDest)
    {
        pDest->m_bUseFlag = m_bUseFlag;

        for(int nIndex = 0; nIndex < MAX_FT3_CHANNEL_COUNT; nIndex++)
        {
            pDest->m_strChannel[nIndex] = m_strChannel[nIndex];
        }
    }

    tmt_ft3_pub()
    {
        init();
    }
} tmt_Ft3Pub;

typedef struct tmt_ft3_pubs
{
    tmt_Ft3Pub m_oFt3Pub[MAX_MODULES_FT3PUB_COUNT];
    void init()
    {
        for(int nIndex = 0; nIndex < MAX_MODULES_FT3PUB_COUNT; nIndex++)
        {
            m_oFt3Pub[nIndex].init();
        }
    }

    tmt_ft3_pubs()
    {
        init();
    }
} tmt_Ft3Pubs;

typedef struct tmt_stable2m_pub
{
    BOOL m_bBlockUseFlag;//是否有变位
    BOOL m_bChanUseFlag[MAX_2M_CHANNEL_COUNT];
    long m_nChanValue[MAX_2M_CHANNEL_COUNT];

    void init()
    {
        m_bBlockUseFlag = FALSE;

        for(int nIndex = 0; nIndex < MAX_2M_CHANNEL_COUNT; nIndex++)
        {
            m_bChanUseFlag[nIndex] = FALSE;
            m_nChanValue[nIndex] = 0;
        }
    }

    void CopyOwn(tmt_stable2m_pub *pDest)
    {
        pDest->m_bBlockUseFlag = m_bBlockUseFlag;

        for(int nIndex = 0; nIndex < MAX_2M_CHANNEL_COUNT; nIndex++)
        {
            pDest->m_nChanValue[nIndex] = m_nChanValue[nIndex];
        }
    }

    tmt_stable2m_pub()
    {
        init();
    }
} tmt_Stable2MPub;

typedef struct tmt_2m_OnePort_pub
{
    tmt_Stable2MPub m_oStable2M_DataPub[MAX_2M_DATAIDX_VALUE];
    tmt_Stable2MPub m_oStable2M_CmdPub[MAX_2M_CMDIDX_COUNT];
    void init()
    {
        for(int nIndex = 0; nIndex < MAX_2M_DATAIDX_VALUE; nIndex++)
        {
            m_oStable2M_DataPub[nIndex].init();
        }

        for(int nIndex = 0; nIndex < MAX_2M_CMDIDX_COUNT; nIndex++)
        {
            m_oStable2M_CmdPub[nIndex].init();
        }
    }

    tmt_2m_OnePort_pub()
    {
        init();
    }
} tmt_2MOnePortPub;

/**************异步模块**************/
typedef struct tmt_async_channel
{
public:
	tmt_ChannelHarm			m_oHarm;	//基波、选择、幅值、相位、频率
	tmt_ChannelRamp			m_oRamp;	//
	float m_fChACMax;					//通道交流最大值
	float m_fChDCMax;					//通道直流最大值

	void init()
	{
		m_oHarm.init();
		m_oRamp.init();
		m_fChACMax = m_fChDCMax = 0;
	}

	tmt_async_channel()
	{
		init();
	}

	void CopyOwn(tmt_async_channel &pChannel)
	{
		m_oHarm.m_bSelect = pChannel.m_oHarm.m_bSelect;
		m_oHarm.fAmp = pChannel.m_oHarm.fAmp;
		m_oHarm.fAngle = pChannel.m_oHarm.fAngle;
		m_oHarm.fFreq = pChannel.m_oHarm.fFreq;

		m_fChACMax = pChannel.m_fChACMax;
		m_fChDCMax = pChannel.m_fChDCMax;

	}

}tmt_AsyncChannel;

typedef struct tmt_async_module
{
public:
	long 					m_nModulePos;			//模块序号 
	long  					m_nCurrChCount;			//电流通道数量
	long  					m_nVolChCount;			//电压通道数量
	tmt_AsyncChannel 		* m_pCurrChannel;			//通道信息数组
	tmt_AsyncChannel 		* m_pVolChannel;			//通道信息数组

	void init()
	{
		m_nModulePos = 0;
		m_nCurrChCount = 0;
		m_nVolChCount = 0;
		m_pCurrChannel = NULL;
		m_pVolChannel = NULL;
	}

	void initChannel(long nCurrChNumbers, long nVolChNumbers)
	{
		if(m_nCurrChCount != nCurrChNumbers)
		{
			if(m_pCurrChannel != NULL)
			{
				delete []m_pCurrChannel;
				m_pCurrChannel = NULL;
			}
		}

		if(m_nVolChCount != nVolChNumbers)
		{
			if(m_pVolChannel != NULL)
			{
				delete []m_pVolChannel;
				m_pVolChannel = NULL;
			}
		}

		if (m_pCurrChannel == NULL && nCurrChNumbers > 0)
		{
			m_pCurrChannel = new tmt_AsyncChannel[nCurrChNumbers];
		}
		if(m_pVolChannel == NULL && nVolChNumbers > 0)
		{
			m_pVolChannel = new tmt_AsyncChannel[nVolChNumbers];
		}

		m_nCurrChCount = nCurrChNumbers;
		m_nVolChCount = nVolChNumbers;
	}

	tmt_async_module()
	{
		init();
	}

	void CopyOwn(tmt_async_module &pSrcModule)
	{
		m_nModulePos = pSrcModule.m_nModulePos;
		m_nCurrChCount = pSrcModule.m_nCurrChCount;
		m_nVolChCount = pSrcModule.m_nVolChCount;

		initChannel(m_nCurrChCount,m_nVolChCount);

		for(int i = 0;i<m_nCurrChCount;i++)
		{
			m_pCurrChannel[i].CopyOwn(pSrcModule.m_pCurrChannel[i]);
		}
		for(int i = 0;i<m_nVolChCount;i++)
		{
			m_pVolChannel[i].CopyOwn(pSrcModule.m_pVolChannel[i]);
		}

	}

}tmt_AsyncModule;

typedef struct tmt_async_modules
{
	long 	m_nAnalogCount;		//模拟量中模块数量
	long 	m_nWeekCount;		//弱信号中模块数量

	tmt_AsyncModule  m_oAnalogModules[MAX_MODULE_COUNT];		//模拟量模块
	tmt_AsyncModule  m_oWeekModules[MAX_MODULE_COUNT];		//弱信号模块
	tmt_AsyncModule  m_oDigitalModules;						//数字量模块
	int m_nDc[ASYNC_MODULE_TYPE_COUNT];		//对应直流勾选状态

	void init()
	{
		m_nAnalogCount = 0;
		m_nWeekCount = 0;
		m_oDigitalModules.init();

		for(int nIndex = 0; nIndex < ASYNC_MODULE_TYPE_COUNT ; nIndex++)
		{
			m_nDc[nIndex] = 0;
		}
		
		for(int nIndex = 0; nIndex < MAX_MODULE_COUNT ; nIndex++)
		{
			m_oAnalogModules[nIndex].init(); // 初始化数组元素
			m_oWeekModules[nIndex].init(); // 初始化数组元素
		}
	}


	tmt_async_modules()
	{
		init();
	}

	void CopyOwn(tmt_async_modules &pSrcModule)
	{
		m_nAnalogCount = pSrcModule.m_nAnalogCount;
		m_nWeekCount= pSrcModule.m_nWeekCount;

		for(int i = 0; i < ASYNC_MODULE_TYPE_COUNT; i++)
		{
			m_nDc[i] = pSrcModule.m_nDc[i];
		}

		for(int i = 0;i<m_nAnalogCount;i++)
		{
			m_oAnalogModules[i].CopyOwn(pSrcModule.m_oAnalogModules[i]);
		}
		for(int i = 0;i<m_nWeekCount;i++)
		{
			m_oWeekModules[i].CopyOwn(pSrcModule.m_oWeekModules[i]);

		}
		m_oDigitalModules.CopyOwn(pSrcModule.m_oDigitalModules);


	}

}tmt_AsyncModules;

/**************故障回放**************/

/**************LtReplay**************/
#define COMTRADE_REPLAY_PKG_POINTS					600
#define LT_REPLAY_FRAME_PKG_CNT						3600 //600*6
//定义最大 循环 A B 缓存大小
#define LT_REPLAY_MAX_LOOP_PKG_CNT                  12
#define LT_REPLAY_MAX_A_PKG_CNT                     120
#define LT_REPLAY_MAX_B_PKG_CNT                     LT_REPLAY_MAX_A_PKG_CNT

typedef struct
{
    unsigned int 	module;
    unsigned int	title;
    unsigned int	length;
    unsigned int	cmd;
    long			data[LT_REPLAY_FRAME_PKG_CNT];
} Drv_BlockPkg;

typedef struct
{
    Drv_BlockPkg bufferLoop[LT_REPLAY_MAX_LOOP_PKG_CNT];
    Drv_BlockPkg bufferA[LT_REPLAY_MAX_A_PKG_CNT];
    Drv_BlockPkg bufferB[LT_REPLAY_MAX_B_PKG_CNT];
} Drv_LtReplayBuffer;

/**************ComReplay**************/
typedef struct
{
    unsigned int lenth;
    long dat[2560000];//参考COMTRADE_ABBUF_SIZE 10240000/4
} DrvComReplayData;

typedef struct
{
    unsigned int module;
    unsigned int pkglen;
    DrvComReplayData oData;
} Drv_ComReplayBuffer;

typedef struct ReplayCoefItem
{
    float fCoef;//幅值系数
    float fZero;//交流零漂
    float fTmtCoef;//小信号变比
    float fMaxValue; // 直流最大值 有效值*1.414
    int   nCh;
    float fReverse;// +1 -1
	int   nSampleLen;//FT3采样长度
    ReplayCoefItem()
    {
        fCoef = 1.0;
        fZero = 0;
        fTmtCoef = 1.0;//一般变比120:7.07,最小1:1，判断时按大于0.5算有效
        fMaxValue = 100;
        nCh = 0;
        fReverse = 1.0;
		nSampleLen = 2;
    }
} Drv_ReplayCoefItem;

typedef struct ReplayCoefItems
{
    int nChCnt;//回放模块的FPGA通道信号数量，6或12
    int nCode;//分辨率，16位或32位 2^(32-1)-1
    ReplayCoefItem Item[48];//20220511 zhoulei 支持48路小信号回放
} Drv_ReplayCoefItems;

typedef struct ReplayCoef
{
    ReplayCoefItems Items[16];//0-11对应位置1-12，15对应主板小信号或330
} Drv_ReplayCoef;


//2022-8-25  lijunqing
typedef struct _Replay_HdCh_RcdData_Map_
{
    int   nHdCh;   //硬件通道编号

    //对应的录波数据的位置   2022-8-24 lijunqing
    //故障回放时:对应的波形数据的编号，没有配置，则为-1
    //模式1:如果通道没有配置，则不需要下载波形数据；
    //模式2:通道没有配置，依然下载通道数据，此时数据为0
    int  nRcdDataIndex;
    double fCoef;

    void init()
    {
        nHdCh = 0;
        nRcdDataIndex = -1;
        fCoef = 1.0f;
    }
} REPLAY_HDCH_RCDDATA_MAP;

typedef struct _Replay_HdCh_RcdData_Maps_
{
    int nModuleIndex;   //映射模块编号
    int nMapCount;  //映射通道数量
    REPLAY_HDCH_RCDDATA_MAP oHdChRcdDataMaps[48];  //是否定义为宏定义

    void init()
    {
        nModuleIndex = -1;
        nMapCount = 0;

        for(int k = 0; k < 48; k++)
        {
            oHdChRcdDataMaps[k].init();
        }
    }
} REPLAY_HDCH_RCDDATA_MAPS;

typedef struct _Replay_HdCh_RcdData_Maps_Mngr_
{
    int nModuleCount;
    REPLAY_HDCH_RCDDATA_MAPS oModules [16];  //是否定义为宏定义

    void init()
    {
        nModuleCount = 0;

        for(int k = 0; k < 16; k++)
        {
            oModules[k].init();
        }
    }
} REPLAY_HDCH_RCDDATA_MAPS_MNGR;

inline int get_xml_serialize_binary_count(CSttXmlSerializeBase *pXmlSierialize)
{
    int nCnt = 0;

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        nCnt = MAX_BINARYIN_COUNT;
    }
    else
    {
        nCnt = g_nBinCount;

        if(nCnt > MAX_BINARYIN_COUNT)
        {
            nCnt = MAX_BINARYIN_COUNT;
        }
        else
        {
            if(nCnt < 8)
            {
                nCnt = 8;//GOOSE开入映射D1-D8
            }
        }
    }

    return nCnt;
}

inline int get_xml_serialize_binary_out_count(CSttXmlSerializeBase *pXmlSierialize)
{
    int nCnt = 0;

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        nCnt = MAX_BINARYOUT_COUNT;
    }
    else
    {
        nCnt = g_nBoutCount;

        if(nCnt > MAX_BINARYOUT_COUNT)
        {
            nCnt = MAX_BINARYOUT_COUNT;
        }
        else
        {
            if(nCnt < 8)
            {
                nCnt = 8;//GOOSE开出映射D1-D8
            }
        }
    }

    return nCnt;
}

inline void stt_xml_serialize_binary_in(tmt_BinaryIn *pbin, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("开入A选择", "_BinSelectA", "", "BOOL", pbin[0].nSelect);
    pXmlSierialize->xml_serialize("开入B选择", "_BinSelectB", "", "BOOL", pbin[1].nSelect);
    pXmlSierialize->xml_serialize("开入C选择", "_BinSelectC", "", "BOOL", pbin[2].nSelect);
    pXmlSierialize->xml_serialize("开入R选择", "_BinSelectR", "", "BOOL", pbin[3].nSelect);
    pXmlSierialize->xml_serialize("开入a选择", "_BinSelecta", "", "BOOL", pbin[4].nSelect);
    pXmlSierialize->xml_serialize("开入b选择", "_BinSelectb", "", "BOOL", pbin[5].nSelect);
    pXmlSierialize->xml_serialize("开入c选择", "_BinSelectc", "", "BOOL", pbin[6].nSelect);
    pXmlSierialize->xml_serialize("开入r选择", "_BinSelectr", "", "BOOL", pbin[7].nSelect);
    pXmlSierialize->xml_serialize("开入I选择", "_BinSelectI", "", "BOOL", pbin[8].nSelect);
    pXmlSierialize->xml_serialize("开入J选择", "_BinSelectJ", "", "BOOL", pbin[9].nSelect);
    pXmlSierialize->xml_serialize("开入K选择", "_BinSelectK", "", "BOOL", pbin[10].nSelect);
    pXmlSierialize->xml_serialize("开入L选择", "_BinSelectL", "", "BOOL", pbin[11].nSelect);
    pXmlSierialize->xml_serialize("开入M选择", "_BinSelectM", "", "BOOL", pbin[12].nSelect);
    pXmlSierialize->xml_serialize("开入N选择", "_BinSelectN", "", "BOOL", pbin[13].nSelect);
    pXmlSierialize->xml_serialize("开入O选择", "_BinSelectO", "", "BOOL", pbin[14].nSelect);
    pXmlSierialize->xml_serialize("开入P选择", "_BinSelectP", "", "BOOL", pbin[15].nSelect);
}

inline void stt_xml_serialize_Exbinary_in(tmt_BinaryIn *pbinEx, CSttXmlSerializeBase *pXmlSierialize)
{
    CString strName, strID, strTemp;
    CString str1 = _T("扩展开入");
    CString str2 = _T("选择");
    CSttXmlSerializeBase *pExBinSerialize = NULL;

    if(stt_xml_serialize_is_write(pXmlSierialize))	//下发
    {
        if(g_nBinExCount <= 0)
        {
            return;
        }

        pExBinSerialize = pXmlSierialize->xml_serialize("扩展开入", "BinEx", "BinEx", stt_ParaGroupKey());

        if(pExBinSerialize == NULL)
        {
            return;
        }

        for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
        {
            strTemp.Format(_T("%d"), nIndex + 1);
            strName = str1 + strTemp + str2;
            strID.Format("BinEx%dSelect", (nIndex + 1));
            pExBinSerialize->xml_serialize(strName.GetString(), strID.GetString(), "", "BOOL", pbinEx[nIndex].nSelect);
        }

        return;
    }

    pExBinSerialize = pXmlSierialize->xml_serialize("扩展开入", "BinEx", "BinEx", stt_ParaGroupKey());

    if(pExBinSerialize == NULL)
    {
        if(stt_xml_serialize_is_read(pXmlSierialize))
        {
            //20220426 南瑞稳控STT接口调用
            pExBinSerialize = pXmlSierialize;
        }
        else
        {
            return;
        }
    }

    for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);
        strName = str1 + strTemp + str2;
        strID.Format("BinEx%dSelect", (nIndex + 1));
        pExBinSerialize->xml_serialize(strName.GetString(), strID.GetString(), "", "BOOL", pbinEx[nIndex].nSelect);
    }
}

inline void stt_xml_serialize_binary_out(tmt_BinaryOut *pbOut, CSttXmlSerializeBase *pXmlSierialize)
{
//    pXmlSierialize->xml_serialize("开出1状态", "_Bout1", "", "DOutputState", pbOut[0].nState);
//    pXmlSierialize->xml_serialize("开出2状态", "_Bout2", "", "DOutputState", pbOut[1].nState);
//    pXmlSierialize->xml_serialize("开出3状态", "_Bout3", "", "DOutputState", pbOut[2].nState);
//    pXmlSierialize->xml_serialize("开出4状态", "_Bout4", "", "DOutputState", pbOut[3].nState);
//    pXmlSierialize->xml_serialize("开出5状态", "_Bout5", "", "DOutputState", pbOut[4].nState);
//    pXmlSierialize->xml_serialize("开出6状态", "_Bout6", "", "DOutputState", pbOut[5].nState);
//    pXmlSierialize->xml_serialize("开出7状态", "_Bout7", "", "DOutputState", pbOut[6].nState);
//    pXmlSierialize->xml_serialize("开出8状态", "_Bout8", "", "DOutputState", pbOut[7].nState);
    CString strName, strID, strTemp;
    CString str1 = _T("开出");
    CString str2 = _T("状态");
    long nBoSize = get_xml_serialize_binary_out_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nBoSize; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);
        strName = str1 + strTemp + str2;
        strID.Format("_Bout%d", nIndex + 1);
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "", "DOutputState", pbOut[nIndex].nState);
    }
}

inline void stt_xml_serialize_Exbinary_out(tmt_BinaryOut *pbOutEx, CSttXmlSerializeBase *pXmlSierialize)
{
    CString strName, strID, strTemp;
    CString str1 = _T("扩展开出");
    CString str2 = _T("状态");
    CSttXmlSerializeBase *pExBoutSerialize = NULL;

    if(stt_xml_serialize_is_write(pXmlSierialize))	//下发
    {
        if(g_nBoutExCount <= 0)
        {
            return;
        }

        pExBoutSerialize = pXmlSierialize->xml_serialize("扩展开出", "BoutEx", "BoutEx", stt_ParaGroupKey());

        if(pExBoutSerialize == NULL)
        {
            return;
        }

        for(int nIndex = 0; nIndex < g_nBoutExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
        {
            strTemp.Format(_T("%d"), nIndex + 1);
            strName = str1 + strTemp + str2;
            strID.Format("BoutEx%dState", nIndex + 1);
            pExBoutSerialize->xml_serialize(strName.GetString(), strID.GetString(), "", "DOutputState", pbOutEx[nIndex].nState);
        }

        return;
    }

    pExBoutSerialize = pXmlSierialize->xml_serialize("扩展开出", "BoutEx", "BoutEx", stt_ParaGroupKey());

    if(pExBoutSerialize == NULL)
    {
        if(stt_xml_serialize_is_read(pXmlSierialize))
        {
            //20220426 南瑞稳控STT接口调用
            pExBoutSerialize = pXmlSierialize;
        }
        else
        {
            return;
        }
    }

    for(int nIndex = 0; nIndex < g_nBoutExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);
        strName = str1 + strTemp + str2;
        strID.Format("BoutEx%dState", nIndex + 1);
        pExBoutSerialize->xml_serialize(strName.GetString(), strID.GetString(), "", "DOutputState", pbOutEx[nIndex].nState);
    }
}

inline void stt_xml_serialize(tmt_GoosePub *pGoosePub, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pGOOSEPubXml = pXmlSierialize->xml_serialize("", "GOOSEPubs", "GOOSEPubs", stt_ParaGroupKey());

    if(pGOOSEPubXml != NULL)
    {
        for(int nIndex = 0; nIndex < MAX_MODULES_GOOSEPUB_COUNT; nIndex++)
        {
            CSttXmlSerializeBase *pGooseSerialize = pGOOSEPubXml->xml_serialize("GOOSE发布控制块", "GOOSEPub", nIndex + 1, "GOOSEPub", stt_ParaGroupKey());

            if(pGooseSerialize)
            {
                pGoosePub[nIndex].m_bUseFlag = TRUE;
                BOOL bRet;
                bRet = pGooseSerialize->xml_serialize("检修", "CheckStatus", "", "number", pGoosePub[nIndex].m_nTest);

                if(bRet)
                {
                    pGoosePub[nIndex].m_bHasTest = TRUE;
                }

                CString strVal = _T("GooseChannel");
                CString strChannelID;

                for(int nChanIndex = 0; nChanIndex < MAX_GOOSE_CHANNEL_COUNT; nChanIndex++)
                {
                    strChannelID.Format(_T("%d"), nChanIndex + 1);
                    strChannelID = strVal + strChannelID;
                    pGooseSerialize->xml_serialize("GOOSE通道", strChannelID.GetString(), " ", "string", pGoosePub[nIndex].m_strChannel[nChanIndex]);
                }
            }
        }
    }
}

inline void stt_xml_serialize(tmt_Ft3Pub *pFt3Pub, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pFt3PubsXml = pXmlSierialize->xml_serialize("", "FT3Pubs", "FT3Pubs", stt_ParaGroupKey());

    if(pFt3PubsXml != NULL)
    {
        for(int nIndex = 0; nIndex < MAX_MODULES_FT3PUB_COUNT; nIndex++)
        {
            CSttXmlSerializeBase *pFt3PubXml = pFt3PubsXml->xml_serialize("FT3发布控制块", "FT3Pub", nIndex + 1, "FT3Pub", stt_ParaGroupKey());

            if(pFt3PubXml)
            {
                pFt3Pub[nIndex].m_bUseFlag = TRUE;
                CString strVal = _T("FT3Channel");
                CString strChannelID;

                for(int nChanIndex = 0; nChanIndex < MAX_FT3_CHANNEL_COUNT; nChanIndex++)
                {
                    strChannelID.Format(_T("%d"), nChanIndex + 1);
                    strChannelID = strVal + strChannelID;
                    pFt3PubXml->xml_serialize("FT3通道", strChannelID.GetString(), " ", "string", pFt3Pub[nIndex].m_strChannel[nChanIndex]);
                }
            }
        }
    }
}

inline void stt_xml_serialize(tmt_2MOnePortPub *p2MOnePortPub, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pStable2MSerialize;
    CSttXmlSerializeBase *pStable2MCmd;
    CSttXmlSerializeBase *pStable2MData;
    tmt_Stable2MPub *pStable2MPub;
    CString strVal = _T("Channel");
    CString strChannelID;
    BOOL bRet;

    for(int nIndex = 0; nIndex < MAX_2M_BLOCKS_COUNT; nIndex++)
    {
        pStable2MSerialize = pXmlSierialize->xml_serialize("稳控2M发送", "Stable2MPubPort", nIndex + 1, "Stable2MPubPort", stt_ParaGroupKey());

        if(pStable2MSerialize != NULL)
        {
            for(int nCmdIndex = 0; nCmdIndex < MAX_2M_CMDIDX_COUNT; nCmdIndex++)
            {
                p2MOnePortPub[nIndex].m_oStable2M_CmdPub[nCmdIndex].m_bBlockUseFlag = 0;
                pStable2MCmd = pStable2MSerialize->xml_serialize("命令报文", "CmdIdx", nCmdIndex, "CmdPacket", stt_ParaGroupKey());

                if(pStable2MCmd != NULL)
                {
                    pStable2MPub = &p2MOnePortPub[nIndex].m_oStable2M_CmdPub[nCmdIndex];

                    for(int nChanIndex = 0; nChanIndex < MAX_2M_CHANNEL_COUNT; nChanIndex++)
                    {
                        strChannelID.Format(_T("%d"), nChanIndex + 1);
                        strChannelID = strVal + strChannelID;
                        bRet = pStable2MCmd->xml_serialize("稳控2M通道", strChannelID.GetString(), " ", "long", pStable2MPub->m_nChanValue[nChanIndex]);

                        if(bRet)
                        {
                            pStable2MPub->m_bBlockUseFlag = 1;
                            pStable2MPub->m_bChanUseFlag[nChanIndex] = TRUE;
                        }
                        else
                        {
                            pStable2MPub->m_bChanUseFlag[nChanIndex] = FALSE;
                        }
                    }
                }
            }

            for(int nDataIndex = 0; nDataIndex < MAX_2M_DATAIDX_VALUE; nDataIndex++)
            {
                p2MOnePortPub[nIndex].m_oStable2M_DataPub[nDataIndex].m_bBlockUseFlag = 0;
                pStable2MData = pStable2MSerialize->xml_serialize("数据报文", "DataIdx", nDataIndex, "DataPacket", stt_ParaGroupKey());

                if(pStable2MData != NULL)
                {
                    pStable2MPub = &p2MOnePortPub[nIndex].m_oStable2M_DataPub[nDataIndex];

                    for(int nChanIndex = 0; nChanIndex < MAX_2M_CHANNEL_COUNT; nChanIndex++)
                    {
                        strChannelID.Format(_T("%d"), nChanIndex + 1);
                        strChannelID = strVal + strChannelID;
                        bRet = pStable2MData->xml_serialize("稳控2M通道", strChannelID.GetString(), " ", "long", pStable2MPub->m_nChanValue[nChanIndex]);

                        if(bRet)
                        {
                            pStable2MPub->m_bBlockUseFlag = 1;
                            pStable2MPub->m_bChanUseFlag[nChanIndex] = TRUE;
                        }
                        else
                        {
                            pStable2MPub->m_bChanUseFlag[nChanIndex] = FALSE;
                        }
                    }
                }
            }
        }
    }
}

inline void stt_xml_serialize(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("是否保持输出", "_bUseSysOutput", "", "BOOL", pParas->m_bUseSysOutput);
    pXmlSierialize->xml_serialize("Ua幅值", "Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua相位", "UaPh", "°", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ua频率", "UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ub幅值", "Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub相位", "UbPh", "°", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub频率", "UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Uc幅值", "Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc相位", "UcPh", "°", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc频率", "UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Uap幅值", "Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uap相位", "UapPh", "°", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uap频率", "UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ubp幅值", "Ubp", "V", "number", pParas->m_uiVOL[4].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ubp相位", "UbpPh", "°", "number", pParas->m_uiVOL[4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ubp频率", "UbpFre", "Hz", "number", pParas->m_uiVOL[4].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ucp幅值", "Ucp", "V", "number", pParas->m_uiVOL[5].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ucp相位", "UcpPh", "°", "number", pParas->m_uiVOL[5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ucp频率", "UcpFre", "Hz", "number", pParas->m_uiVOL[5].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ia幅值", "Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia相位", "IaPh", "°", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ia频率", "IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ib幅值", "Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib相位", "IbPh", "°", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib频率", "IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ic幅值", "Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic相位", "IcPh", "°", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic频率", "IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Iap幅值", "Iap", "A", "number", pParas->m_uiCUR[3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Iap相位", "IapPh", "°", "number", pParas->m_uiCUR[3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Iap频率", "IapFre", "Hz", "number", pParas->m_uiCUR[3].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ibp幅值", "Ibp", "A", "number", pParas->m_uiCUR[4].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ibp相位", "IbpPh", "°", "number", pParas->m_uiCUR[4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ibp频率", "IbpFre", "Hz", "number", pParas->m_uiCUR[4].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Icp幅值", "Icp", "A", "number", pParas->m_uiCUR[5].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Icp相位", "IcpPh", "°", "number", pParas->m_uiCUR[5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Icp频率", "IcpFre", "Hz", "number", pParas->m_uiCUR[5].Harm[1].fFreq);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
}

inline void stt_xml_serialize_Gradient_Exbinary_out(tmt_BinaryOut *pbOutEx, CSttXmlSerializeBase *pXmlSierialize, BOOL bIsFault)
{
    CString strName, strID, strTemp;
    CString str1 = _T("扩展开出");
    CString str2 = _T("状态");
    CString str3;

    if(bIsFault)
    {
        str3 = _T("故障态");
        strID = _T("Fault");
    }
    else
    {
        str3 = _T("常态");
        strID = _T("PreFault");
    }

    strName = str3 + str1;
    strID += _T("BoutEx");
    CSttXmlSerializeBase *pExBoutSerialize = pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "BoutEx", stt_ParaGroupKey());

    if(pExBoutSerialize == NULL)
    {
        return;
    }

    for(int nIndex = 0; nIndex < g_nBoutExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);
        strName = str1 + strTemp + str2;
        strID.Format("BoutEx%dState", nIndex + 1);
        pExBoutSerialize->xml_serialize(strName.GetString(), strID.GetString(), "", "DOutputState", pbOutEx[nIndex].nState);
    }
}

inline void stt_xml_serialize_Channel(tmt_async_channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pChannelXmlSerializeBase =pXmlSierialize->xml_serialize(pszID, pszID, "channel", stt_ParaGroupKey());
	if (pChannelXmlSerializeBase == NULL)
	{
		return;
	}

#ifdef NOT_USE_XLANGUAGE
	pChannelXmlSerializeBase->xml_serialize("选择", "bSelect", "", "BOOL", pChannel->m_oHarm.m_bSelect);
	pChannelXmlSerializeBase->xml_serialize("幅值", "mag", "", "float", pChannel->m_oHarm.fAmp);
	pChannelXmlSerializeBase->xml_serialize("相位", "ang", "", "float", pChannel->m_oHarm.fAngle);
	pChannelXmlSerializeBase->xml_serialize("频率", "freq", "", "float", pChannel->m_oHarm.fFreq);

	pChannelXmlSerializeBase->xml_serialize( "通道交流最大值", "ChACMax", "", "float", pChannel->m_fChACMax);
	pChannelXmlSerializeBase->xml_serialize( "通道直流最大值" , "ChDCMax", "", "float", pChannel->m_fChDCMax);
#else
	pChannelXmlSerializeBase->xml_serialize("选择", "bSelect", "", "BOOL", pChannel->m_oHarm.m_bSelect);
	pChannelXmlSerializeBase->xml_serialize(/* "幅值" */ g_sLangTxt_Native_Amplitude.GetString(), "mag", "", "float", pChannel->m_oHarm.fAmp);
	pChannelXmlSerializeBase->xml_serialize(/* "相位" */ g_sLangTxt_Native_Phase.GetString(), "ang", "", "float", pChannel->m_oHarm.fAngle);
	pChannelXmlSerializeBase->xml_serialize(/* "频率" */ g_sLangTxt_Native_Freq.GetString(), "freq", "", "float", pChannel->m_oHarm.fFreq);

	pChannelXmlSerializeBase->xml_serialize( "通道交流最大值", "ChACMax", "", "float", pChannel->m_fChACMax);
	pChannelXmlSerializeBase->xml_serialize( "通道直流最大值" , "ChDCMax", "", "float", pChannel->m_fChDCMax);
#endif
}

inline void stt_xml_serialize_Analog(tmt_async_module *pModule, int nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
	char chName[MAX_PATH],chID[MAX_PATH];

	sprintf(chName, "模拟量模块%d", nIndex+1);
	sprintf(chID, "AnalogModule%d", nIndex+1);

	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize(chName, chID, "Module", stt_ParaGroupKey());
	if (pSerialize == NULL)
	{
		return;
	}
	pSerialize->xml_serialize("模块序号","ModulePos","","number",pModule->m_nModulePos);
	pSerialize->xml_serialize("电流通道数量","CurrChCount","","number",pModule->m_nCurrChCount);
	pSerialize->xml_serialize("电压通道数量","VolChCount","","number",pModule->m_nVolChCount);
	CString strID;

	if(pModule->m_nCurrChCount != 0)
	{
		CSttXmlSerializeBase *pCurrSerialize =pSerialize->xml_serialize("电流通道信息", "CurrChannel", "CurrChannel", stt_ParaGroupKey());
		if(pCurrSerialize)
		{

			if(stt_xml_serialize_is_read(pXmlSierialize))
			{
				pModule->initChannel(pModule->m_nCurrChCount,pModule->m_nVolChCount);
			}

			for(int nIndex = 0; nIndex < pModule->m_nCurrChCount; nIndex++)
			{
				strID.Format(_T("I%d"),nIndex+1);
				if(!pModule->m_pCurrChannel)
				{
					return;
				}
				if (stt_xml_serialize_is_write(pCurrSerialize) && !pModule->m_pCurrChannel[nIndex].m_oHarm.m_bSelect)
				{
					continue;
				}
				stt_xml_serialize_Channel(&pModule->m_pCurrChannel[nIndex], strID.GetString(), pCurrSerialize);
			}
		}
	}

	if(pModule->m_nVolChCount != 0)
	{
		CSttXmlSerializeBase *pVolSerialize =pSerialize->xml_serialize("电压通道信息", "VolChannel", "VolChannel", stt_ParaGroupKey());
		if(pVolSerialize)
		{
			if(stt_xml_serialize_is_read(pXmlSierialize))
			{
				pModule->initChannel(pModule->m_nCurrChCount,pModule->m_nVolChCount);
			}
			for(int nIndex = 0; nIndex < pModule->m_nVolChCount; nIndex++)
			{
				strID.Format(_T("U%d"),nIndex+1);
				if(!pModule->m_pVolChannel)
				{
					return;
				}
				if (stt_xml_serialize_is_write(pVolSerialize) && !pModule->m_pVolChannel[nIndex].m_oHarm.m_bSelect)
				{
					continue;
				}
				stt_xml_serialize_Channel(&pModule->m_pVolChannel[nIndex], strID.GetString(), pVolSerialize);
			}
		}
	}
}

inline void stt_xml_serialize_Week(tmt_async_module *pModule, int nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
	char chName[MAX_PATH],chID[MAX_PATH];

	sprintf(chName, "弱信号模块%d", nIndex+1);
	sprintf(chID, "WeekModule%d", nIndex+1);

	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize(chName, chID, "Module", stt_ParaGroupKey());
	if (pSerialize == NULL)
	{
		return;
	}
	pSerialize->xml_serialize("模块序号","ModulePos","","number",pModule->m_nModulePos);
	pSerialize->xml_serialize("电流通道数量","CurrChCount","","number",pModule->m_nCurrChCount);
	pSerialize->xml_serialize("电压通道数量","VolChCount","","number",pModule->m_nVolChCount);
	CString strID;

	if(pModule->m_nCurrChCount != 0)
	{
		CSttXmlSerializeBase *pCurrSerialize =pSerialize->xml_serialize("电流通道信息", "CurrChannel", "CurrChannel", stt_ParaGroupKey());
		if(pCurrSerialize)
		{

			if(stt_xml_serialize_is_read(pXmlSierialize))
			{
				pModule->initChannel(pModule->m_nCurrChCount,pModule->m_nVolChCount);
			}

			for(int nIndex = 0; nIndex < pModule->m_nCurrChCount; nIndex++)
			{
				strID.Format(_T("I%d"),nIndex+1);
				if(!pModule->m_pCurrChannel)
				{
					return;
				}
				if (stt_xml_serialize_is_write(pCurrSerialize) && !pModule->m_pCurrChannel[nIndex].m_oHarm.m_bSelect)
				{
					continue;
				}
				stt_xml_serialize_Channel(&pModule->m_pCurrChannel[nIndex], strID.GetString(), pCurrSerialize);
			}
		}
	}

	if(pModule->m_nVolChCount != 0)
	{
		CSttXmlSerializeBase *pVolSerialize =pSerialize->xml_serialize("电压通道信息", "VolChannel", "VolChannel", stt_ParaGroupKey());
		if(pVolSerialize)
		{
			if(stt_xml_serialize_is_read(pXmlSierialize))
			{
				pModule->initChannel(pModule->m_nCurrChCount,pModule->m_nVolChCount);
			}
			for(int nIndex = 0; nIndex < pModule->m_nVolChCount; nIndex++)
			{
				strID.Format(_T("U%d"),nIndex+1);
				if(!pModule->m_pVolChannel)
				{
					return;
				}
				if (stt_xml_serialize_is_write(pVolSerialize) && !pModule->m_pVolChannel[nIndex].m_oHarm.m_bSelect)
				{
					continue;
				}
				stt_xml_serialize_Channel(&pModule->m_pVolChannel[nIndex], strID.GetString(), pVolSerialize);
			}
		}
	}
}

inline void stt_xml_serialize_Digital(tmt_async_module *pModule, CSttXmlSerializeBase *pXmlSierialize)
{
	char chName[MAX_PATH],chID[MAX_PATH];

	sprintf(chName, "数字量模块");
	sprintf(chID, "DigitalModule");

	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize(chName, chID, "Module", stt_ParaGroupKey());
	if (pSerialize == NULL)
	{
		return;
	}
	pSerialize->xml_serialize("模块序号","ModulePos","","number",pModule->m_nModulePos);
	pSerialize->xml_serialize("电流通道数量","CurrChCount","","number",pModule->m_nCurrChCount);
	pSerialize->xml_serialize("电压通道数量","VolChCount","","number",pModule->m_nVolChCount);
	CString strID;

	if(pModule->m_nCurrChCount != 0)
	{
		CSttXmlSerializeBase *pCurrSerialize =pSerialize->xml_serialize("电流通道信息", "CurrChannel", "CurrChannel", stt_ParaGroupKey());

		if(pCurrSerialize)
		{

			if(stt_xml_serialize_is_read(pXmlSierialize))
			{
				pModule->initChannel(pModule->m_nCurrChCount,pModule->m_nVolChCount);
			}

			for(int nIndex = 0; nIndex < pModule->m_nCurrChCount; nIndex++)
			{
				strID.Format(_T("I%d"),nIndex+1);
				if(!pModule->m_pCurrChannel)
				{
					return;
				}
				if (stt_xml_serialize_is_write(pCurrSerialize) && !pModule->m_pCurrChannel[nIndex].m_oHarm.m_bSelect)
				{
					continue;
				}
				stt_xml_serialize_Channel(&pModule->m_pCurrChannel[nIndex], strID.GetString(), pCurrSerialize);
			}
		}
	}

	if(pModule->m_nVolChCount != 0)
	{
		CSttXmlSerializeBase *pVolSerialize =pSerialize->xml_serialize("电压通道信息", "VolChannel", "VolChannel", stt_ParaGroupKey());
		if(pVolSerialize)
		{
			if(stt_xml_serialize_is_read(pXmlSierialize))
			{
				pModule->initChannel(pModule->m_nCurrChCount,pModule->m_nVolChCount);
			}
			for(int nIndex = 0; nIndex < pModule->m_nVolChCount; nIndex++)
			{
				strID.Format(_T("U%d"),nIndex+1);
				if(!pModule->m_pVolChannel)
				{
					return;
				}
				if (stt_xml_serialize_is_write(pVolSerialize) && !pModule->m_pVolChannel[nIndex].m_oHarm.m_bSelect)
				{
					continue;
				}
				stt_xml_serialize_Channel(&pModule->m_pVolChannel[nIndex], strID.GetString(), pVolSerialize);			
			}
		}
	}
}

inline bool Global_CheckBinSelect(tmt_BinaryIn *pBinIn, int nMaxBinNum, bool bLogicAnd) //zhouhj 20220421 检查开入量勾选状态,保证至少勾选一个开入
{
	if(bLogicAnd)
	{
		int nCount = 0;
		for(int nIndex = 0; nIndex < nMaxBinNum; nIndex++)
		{
			if(pBinIn[nIndex].nSelect)
			{
				nCount++;
				if(nCount == 2)
				{
					return true;
				}
			}
		}

		if(nCount == 1 && pBinIn[0].nSelect == 0)
		{
			pBinIn[0].nSelect = 1;
			return false;
		}
		else if(nCount == 1 && pBinIn[0].nSelect == 1)
		{
			pBinIn[1].nSelect = 1;
			return false;
		}
	}

	for(int nIndex = 0; nIndex < nMaxBinNum; nIndex++)
	{
		if(pBinIn[nIndex].nSelect)
		{
			return true;
		}
	}

	pBinIn[0].nSelect = 1;
	return false;
}

static short Leap_year[2][12] =
{
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

inline void TransTimer_t(unsigned int ntime_t,
                         short &nYear, short &nMon, short &nDay, short &nHour, short &nMin, short &nSec)
{
    nYear = 1970;
    nMon = 1;
    nDay = 1;
    nHour = nMin = nSec = 0;

    while(TRUE)
    {
        int nIsLeap = 0;

        if((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
        {
            nIsLeap = 1;
        }

        int nDiff = nIsLeap ? 366 : 365;

        if(ntime_t >= nDiff * 24 * 60 * 60)
        {
            nYear += 1;
            ntime_t -= nDiff * 24 * 60 * 60;
        }
        else
        {
            break;
        }
    }

    while(TRUE)
    {
        int nIsLeap = 0;

        if((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
        {
            nIsLeap = 1;
        }

        int nLastDay = Leap_year[nIsLeap][nMon - 1];

        if(ntime_t >= nLastDay * 24 * 60 * 60)
        {
            nMon += 1;
            ntime_t -= nLastDay * 24 * 60 * 60;
        }
        else
        {
            break;
        }
    }

    while(TRUE)
    {
        if(ntime_t >= 24 * 60 * 60)
        {
            nDay += 1;
            ntime_t -= 24 * 60 * 60;
        }
        else
        {
            break;
        }
    }

    while(TRUE)
    {
        if(ntime_t >= 60 * 60)
        {
            nHour += 1;
            ntime_t -= 60 * 60;
        }
        else
        {
            break;
        }
    }

    while(TRUE)
    {
        if(ntime_t >= 60)
        {
            nMin += 1;
            ntime_t -= 60;
        }
        else
        {
            break;
        }
    }

    nSec = ntime_t;
}

inline void TransTimer_To_t(unsigned int &ntime_t,
                            short nYear, short nMon, short nDay, short nHour, short nMin, short nSec)
{
    ntime_t = 0;
    int nYearRef = 1970;

    while(TRUE)
    {
        int nDiffYear = nYear - nYearRef;

        if(nDiffYear == 0)
        {
            break;
        }

        int nIsLeap = 0;

        if((nYearRef % 4 == 0 && nYearRef % 100 != 0) || nYearRef % 400 == 0)
        {
            nIsLeap = 1;
        }

        int nDays = nIsLeap ? 366 : 365;
        ntime_t += nDays * 24 * 60 * 60;
        nYearRef++;
    }

    int nIsLeap = 0;

    if((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
    {
        nIsLeap = 1;
    }

    int nMonRef = 1;

    while(TRUE)
    {
        int nDiffMon = nMon - nMonRef;

        if(nDiffMon == 0)
        {
            break;
        }

        int nLastDay = Leap_year[nIsLeap][nMonRef - 1];
        ntime_t += nLastDay * 24 * 60 * 60;
        nMonRef++;
    }

    ntime_t += (nDay - 1) * 24 * 60 * 60;
    ntime_t += nHour * 60 * 60;
    ntime_t += nMin * 60;
    ntime_t += nSec;
}
