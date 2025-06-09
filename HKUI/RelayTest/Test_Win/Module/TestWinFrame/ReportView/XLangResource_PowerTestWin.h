#ifndef _XLangResource_PowerTestWin_h__
#define _XLangResource_PowerTestWin_h__

#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../../Module/XLangResource_Native.h"

class CXLangResource_PowerTestWin : public CXLangResource_Native
{
public:
	CXLangResource_PowerTestWin();
	virtual ~CXLangResource_PowerTestWin();

private:
	CXLanguage m_oXLangRs_Test;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);
	virtual void InitLangRsByFile();

	virtual void RegisterLanguageResource();
	virtual void InitLangTxt();

public:



};


//LY 吕
extern CString g_sLangID_ActTime_Protect_TestTempFile;
extern CString g_sLangTxt_ActTime_Protect_TestTempFile;//动作时间保护试验模板文件
extern CString g_sLangID_ActionTime_test;
extern CString g_sLangTxt_ActionTime_test;//欢迎使用动作时间实验
extern CString g_sLangID_Native_PonovoActiontime;
extern CString g_sLangTxt_Native_PonovoActiontime;//Ponovo动作时间
extern CString g_sLangID_ActionTimeTest;
extern CString g_sLangTxt_ActionTimeTest;//动作时间测试
extern CString g_sLangID_Single_phaseGroundFault;
extern CString g_sLangTxt_Single_phaseGroundFault;//单相接地短路
extern CString g_sLangID_PhasetoPhase_ShortCircuit;
extern CString g_sLangTxt_PhasetoPhase_ShortCircuit;//相间短路
extern CString g_sLangID_Zero_SequenceCurrent;
extern CString g_sLangTxt_Zero_SequenceCurrent;//零序电流
extern CString g_sLangID_Negative_SequenceCurrent;
extern CString g_sLangTxt_Negative_SequenceCurrent;//负序电流
extern CString g_sLangID_ParaConnect_Three_PhaseCurrents;
extern CString g_sLangTxt_ParaConnect_Three_PhaseCurrents;//三相电流并联
extern CString g_sLangID_Single_PhaseFault;
extern CString g_sLangTxt_Single_PhaseFault;//单相故障

// 吕
extern CString g_sLangID_AutoSyn_TestTempFile;
extern CString g_sLangTxt_AutoSyn_TestTempFile;//自动准周期试验模板文件
extern CString g_sLangID_Wel_AutoSynTest;
extern CString g_sLangTxt_Wel_AutoSynTest;//欢迎使用自动准同期试验
extern CString g_sLangID_Ponovo_AutoSyn;
extern CString g_sLangTxt_Ponovo_AutoSyn;//Ponovo自动准同期
extern CString g_sLangID_AutoSyn;
extern CString g_sLangTxt_AutoSyn;//自动准同期


extern CString g_sLangID_System_Rated_FreqHZ;
extern CString g_sLangTxt_System_Rated_FreqHZ;//系统侧额定频率（Hz）
extern CString g_sLangID_System_Rated_Volt;
extern CString g_sLangTxt_System_Rated_Volt;//系统侧额定电压（V）

extern CString g_sLangID_Grid_VolV;
extern CString g_sLangTxt_Grid_VolV;//待并侧电压（V）
extern CString g_sLangID_Stepsize_Grid_volvariation;
extern CString g_sLangTxt_Stepsize_Grid_volvariation;//待并侧电压变化步长（V）

extern CString g_sLangID_Grid_Rated_VolV;
extern CString g_sLangTxt_Grid_Rated_VolV;//待并侧额定电压（V）



extern CString g_sLangID_VolDifference;
extern CString g_sLangTxt_VolDifference;//压差（V）

extern CString g_sLangID_Allow_VolDifV;
extern CString g_sLangTxt_Allow_VolDifV;//允许压差（V）

extern CString g_sLangID_FreqDifference;
extern CString g_sLangTxt_FreqDifference;//频差（HZ）

extern CString g_sLangID_Allow_FreqDifHZ;
extern CString g_sLangTxt_Allow_FreqDifHZ;//允许频差（Hz）



extern CString g_sLangID_AtleastOneTest;
extern CString g_sLangTxt_AtleastOneTest;//至少保留一个测试项!
extern CString g_sLangID_Vol_BoundValueTest;
extern CString g_sLangTxt_Vol_BoundValueTest;//电压边界值测试
extern CString g_sLangID_Volbound_trip_values;
extern CString g_sLangTxt_Volbound_trip_values;//电压边界值动作值（V）
extern CString g_sLangID_Freq_BoundValueTest;
extern CString g_sLangTxt_Freq_BoundValueTest;//频率边界值测试
extern CString g_sLangID_Auto_AdjustTest;
extern CString g_sLangTxt_Auto_AdjustTest;//自动调整试验
extern CString g_sLangID_Vol_ReguPeriodTest;
extern CString g_sLangTxt_Vol_ReguPeriodTest;//调压周期测试
extern CString g_sLangID_Freq_ReguPeriodTest;
extern CString g_sLangTxt_Freq_ReguPeriodTest;//调频周期测试
extern CString g_sLangID_Lead_AngleTime_Test;
extern CString g_sLangTxt_Lead_AngleTime_Test;//导前角及导前时间测试
extern CString g_sLangID_result;
extern CString g_sLangTxt_result;//结论
extern CString g_sLangID_Stepsize_Grid_freqvariation;
extern CString g_sLangTxt_Stepsize_Grid_freqvariation;//待并侧频率变化步长（HZ）
extern CString g_sLangID_Freqbound_trip_values;
extern CString g_sLangTxt_Freqbound_trip_values;//频率边界值动作值（HZ）
extern CString g_sLangID_Leading_Angle;
extern CString g_sLangTxt_Leading_Angle;//导前角（°）
extern CString g_sLangID_Leading_Time;
extern CString g_sLangTxt_Leading_Time;//导前时间（s）
extern CString g_sLangID_Native_dVzd;
extern CString g_sLangTxt_Native_dVzd;//允许压差整定值（V）
extern CString g_sLangID_Native_dFzd;
extern CString g_sLangTxt_Native_dFzd;//允许频差整定值（HZ）
extern CString g_sLangID_Native_Ut;
extern CString g_sLangTxt_Native_Ut;//调压周期整定值（s）
extern CString g_sLangID_AdjVolCycle;
extern CString g_sLangTxt_AdjVolCycle;//调压周期动作值（s）
extern CString g_sLangID_AdjVolWidth;
extern CString g_sLangTxt_AdjVolWidth;//调压脉宽（s）
extern CString g_sLangID_Native_Ft;
extern CString g_sLangTxt_Native_Ft;//调频周期整定值（s）
extern CString g_sLangID_AdjFreqCycle;
extern CString g_sLangTxt_AdjFreqCycle;//调频周期动作值（s）
extern CString g_sLangID_AdjFreqWidth;
extern CString g_sLangTxt_AdjFreqWidth;//调频脉宽（s）
extern CString g_sLangID_Native_System;
extern CString g_sLangTxt_Native_System;//系统
extern CString g_sLangID_waitgrid_connection;
extern CString g_sLangTxt_waitgrid_connection;//待并


extern CString g_sLangID_expression_error;
extern CString g_sLangTxt_expression_error;//表达式输出错误

extern CString g_sLangID_Out4_Time;
extern CString g_sLangTxt_Out4_Time;//开出4保持时间（s）

extern CString g_sLangID_Native_Bout;
extern CString g_sLangTxt_Native_Bout;//开出量
extern CString g_sLangID_protectexport_sign;
extern CString g_sLangTxt_protectexport_sign;//保护出口信号
extern CString g_sLangID_boost_sign;
extern CString g_sLangTxt_boost_sign;//增压信号
extern CString g_sLangID_reduce_sign;
extern CString g_sLangTxt_reduce_sign;//减压信号
extern CString g_sLangID_speed_sign;
extern CString g_sLangTxt_speed_sign;//增速信号
extern CString g_sLangID_slow_sign;
extern CString g_sLangTxt_slow_sign;//减速信号

extern CString g_sLangID_pulse;
extern CString g_sLangTxt_pulse;//脉冲
extern CString g_sLangID_continue;
extern CString g_sLangTxt_continue;//连续
extern CString g_sLangID_value;
extern CString g_sLangTxt_value;//值
// 吕
extern CString g_sLangID_lowfreqloadre_tempfile;
extern CString g_sLangTxt_lowfreqloadre_tempfile;//低周减载模板文件
extern CString g_sLangID_wel_lowfreqloadre;
extern CString g_sLangTxt_wel_lowfreqloadre;//欢迎使用低周减载
extern CString g_sLangID_Ponovo_lowfreqloadre;
extern CString g_sLangTxt_Ponovo_lowfreqloadre;//Ponovo 低周减载
extern CString g_sLangID_lowfreqloadre;
extern CString g_sLangTxt_lowfreqloadre;//低周减载
extern CString g_sLangID_Noselect_testitems;
extern CString g_sLangTxt_Noselect_testitems;//没有选择测试项
extern CString g_sLangID_Atleast1_5testitems;
extern CString g_sLangTxt_Atleast1_5testitems;//5种测试类型至少各保留一个测试项！
extern CString g_sLangID_Atleast1_Thistestitems;
extern CString g_sLangTxt_Atleast1_Thistestitems;//此测试类型至少保留一个测试项！
extern CString g_sLangID_Native_FreAction;
extern CString g_sLangTxt_Native_FreAction;//动作频率
extern CString g_sLangID_Native_sliptrip;
extern CString g_sLangTxt_Native_sliptrip;//滑差闭锁


extern CString g_sLangID_interlock_volselection;
extern CString g_sLangTxt_interlock_volselection;//闭锁电压选择
extern CString g_sLangID_FreAValue_Test;
extern CString g_sLangTxt_FreAValue_Test;//频率动作值测试
extern CString g_sLangID_Native_sliptripTest;
extern CString g_sLangTxt_Native_sliptripTest;//滑差闭锁值测试

extern CString g_sLangID_lowcur_lockout_test;
extern CString g_sLangTxt_lowcur_lockout_test;//低电流闭锁值测试
extern CString g_sLangID_Native_LowVoltLock_test;
extern CString g_sLangTxt_Native_LowVoltLock_test;//低电压闭锁值测试
extern CString g_sLangID_lowfreqloadre_Setting;
extern CString g_sLangTxt_lowfreqloadre_Setting;//低周减载动作值

extern CString g_sLangID_lowcur_lockout;
extern CString g_sLangTxt_lowcur_lockout;//低电流闭锁值

// extern CString g_sLangID_Voltage;
// extern CString g_sLangTxt_Voltage;//电压（V）
extern CString g_sLangID_lowVoltage;
extern CString g_sLangTxt_lowVoltage;//低压
extern CString g_sLangID_Negative_SeqVolU2;
extern CString g_sLangTxt_Negative_SeqVolU2;//负序电压(U2)
extern CString g_sLangID_Zero_SeqCur3U0;
extern CString g_sLangTxt_Zero_SeqCur3U0;//零序电压(3U0)
extern CString g_sLangID_Illegal_testitem;
extern CString g_sLangTxt_Illegal_testitem;//测试项类型非法.
extern CString g_sLangID_Native_OutOf_Range;
extern CString g_sLangTxt_Native_OutOf_Range;//超出变化范围
extern CString g_sLangID_action_freqvalue;
extern CString g_sLangTxt_action_freqvalue;//动作频率值
// 吕
extern CString g_sLangID_ITOTest_Tempfile;
extern CString g_sLangTxt_ITOTest_Tempfile;//电流反时限试验模板文件Inverse Time Overcurrent(ITO)
extern CString g_sLangID_Wel_ITOTest;
extern CString g_sLangTxt_Wel_ITOTest;//欢迎使用电流反时限试验.
extern CString g_sLangID_ITOTest;
extern CString g_sLangTxt_ITOTest;//电流反时限试验ITOTest
extern CString g_sLangID_Ponovo_ITOTest;
extern CString g_sLangTxt_Ponovo_ITOTest;//Ponovo 电流反时限试验
extern CString g_sLangID_Theoretical_ActionTime;
extern CString g_sLangTxt_Theoretical_ActionTime;//理论动作时间
extern CString g_sLangID_Native_ITO;
extern CString g_sLangTxt_Native_ITO;//电流反时限
extern CString g_sLangID_Single_PhaseGround_Fault;
extern CString g_sLangTxt_Single_PhaseGround_Fault;//单项接地故障
extern CString g_sLangID_Directional_LineSide;
extern CString g_sLangTxt_Directional_LineSide;//指向线路侧Directional_LineSide
extern CString g_sLangID_Directional_BusSide;
extern CString g_sLangTxt_Directional_BusSide;//指向母线侧
extern CString g_sLangID_Add_Series;
extern CString g_sLangTxt_Add_Series;//添加系列
extern CString g_sLangID_Delet_Test;
extern CString g_sLangTxt_Delet_Test;//删除试验
extern CString g_sLangID_Clear_Results;
extern CString g_sLangTxt_Clear_Results;//清除结果
extern CString g_sLangID_Clear_All;
extern CString g_sLangTxt_Clear_All;//清除所有
extern CString g_sLangID_Test_Parameters;
extern CString g_sLangTxt_Test_Parameters;//试验参数


//LowUTest_Trans 马
/*tr("低压减载试验模板文件")*/
extern CString g_sLangID_Native_LVLoadRedTemp;
extern CString g_sLangTxt_Native_LVLoadRedTemp;
/*_T("欢迎使用低压减载试验.")*/
extern CString g_sLangID_Native_WLULVLRTest;
extern CString g_sLangTxt_Native_WLULVLRTest;
/*tr("Ponovo 低压减载")*/
extern CString g_sLangID_Native_PLVLRTitle;
extern CString g_sLangTxt_Native_PLVLRTitle;
/*tr("低压减载")*/
extern CString g_sLangID_Native_LowVLoadRed;
extern CString g_sLangTxt_Native_LowVLoadRed;



/*tr("至少保留一个测试项!")*/
extern CString g_sLangID_Native_KeepOneTest;
extern CString g_sLangTxt_Native_KeepOneTest;


/*QObject::tr("程序已经在运行！")*/
extern CString g_sLangID_Native_ProgRunning;
extern CString g_sLangTxt_Native_ProgRunning;
/*"<h1>低压减载测试</h1>"*/
extern CString g_sLangID_Native_LVLRTesting;
extern CString g_sLangTxt_Native_LVLRTesting;
/*tr("低电压闭锁值")*/
extern CString g_sLangID_Native_LowVoltLock;
extern CString g_sLangTxt_Native_LowVoltLock;
/*tr("动作时间=%1s")*/
// extern CString g_sLangID_Native_ActTimeSym;
// extern CString g_sLangTxt_Native_ActTimeSym;
/*tr("电压滑差闭锁值")*/
extern CString g_sLangID_Native_VoltSlipLock;
extern CString g_sLangTxt_Native_VoltSlipLock;
/*tr("相电压变化步长(V):")*/
extern CString g_sLangID_Native_PhaseVoltStepV;
extern CString g_sLangTxt_Native_PhaseVoltStepV;
/*tr("相电压变化起始值(V):")*/
extern CString g_sLangID_Native_PhaseVoltStartV;
extern CString g_sLangTxt_Native_PhaseVoltStartV;
/*tr("相电压变化结束值(V):")*/
extern CString g_sLangID_Native_PhaseVoltEndV;
extern CString g_sLangTxt_Native_PhaseVoltEndV;
/*tr("线电压变化步长(V):")*/
extern CString g_sLangID_Native_LineVoltStepV;
extern CString g_sLangTxt_Native_LineVoltStepV;
/*tr("线电压变化起始值(V):")*/
extern CString g_sLangID_Native_LineVoltStartV;
extern CString g_sLangTxt_Native_LineVoltStartV;
/*tr("线电压变化结束值(V):")*/
extern CString g_sLangID_Native_LineVoltEndV;
extern CString g_sLangTxt_Native_LineVoltEndV;
/*tr("相电压变化始值(V):")*/
extern CString g_sLangID_Native_PhaseVoltBeginV;
extern CString g_sLangTxt_Native_PhaseVoltBeginV;
/*tr("相电压变化终值(V):")*/
extern CString g_sLangID_Native_PhaseVoltFinal;
extern CString g_sLangTxt_Native_PhaseVoltFinal;
/*tr("线电压变化终值(V):")*/
extern CString g_sLangID_Native_LineVoltFinal;
extern CString g_sLangTxt_Native_LineVoltFinal;
/*tr("相电压滑差变化步长(V/s):")*/
extern CString g_sLangID_Native_PhaseVSlipStep;
extern CString g_sLangTxt_Native_PhaseVSlipStep;
/*tr("线电压滑差变化步长(V/s):")*/
extern CString g_sLangID_Native_LineVSlipStep;
extern CString g_sLangTxt_Native_LineVSlipStep;
/*tr("相电压滑差变化始值(V/s):")*/
extern CString g_sLangID_Native_PhaseVSlipStart;
extern CString g_sLangTxt_Native_PhaseVSlipStart;
/*tr("线电压滑差变化始值(V/s):")*/
extern CString g_sLangID_Native_LineVSlipStart;
extern CString g_sLangTxt_Native_LineVSlipStart;
/*tr("相电压滑差变化终值(V/s):")*/
extern CString g_sLangID_Native_PhaseVSlipEnd;
extern CString g_sLangTxt_Native_PhaseVSlipEnd;
/*tr("线电压滑差变化终值(V/s):")*/
extern CString g_sLangID_Native_LineVSlipEnd;
extern CString g_sLangTxt_Native_LineVSlipEnd;
/*_T("表达式输入错误")*/
extern CString g_sLangID_Native_ExprInputErr;
extern CString g_sLangTxt_Native_ExprInputErr;
/*_T("超出范围")*/
extern CString g_sLangID_Native_OutOfRange;
extern CString g_sLangTxt_Native_OutOfRange;
/*_T("递变步数超过60，请重新输入！")*/
extern CString g_sLangID_Native_VarStepExceed60P;
extern CString g_sLangTxt_Native_VarStepExceed60P;






//PowerDirectionTest_Trans 马
/*tr("功率方向试验模板文件")*/
extern CString g_sLangID_Native_PowerDirTemp;
extern CString g_sLangTxt_Native_PowerDirTemp;
/*_T("欢迎使用功率方向.")*/
extern CString g_sLangID_Native_WelcomePD;
extern CString g_sLangTxt_Native_WelcomePD;
/*_T("获取实时数据绝对时间失败.")*/
extern CString g_sLangID_Native_GetRealTimeFail;
extern CString g_sLangTxt_Native_GetRealTimeFail;
/*_T("获取实时数据相对时间失败.")*/
extern CString g_sLangID_Native_GetRelTimeFail;
extern CString g_sLangTxt_Native_GetRelTimeFail;
/*tr("Ponovo 功率方向")*/
extern CString g_sLangID_Native_PonovoPower;
extern CString g_sLangTxt_Native_PonovoPower;
/*tr("功率方向")*/
extern CString g_sLangID_Native_PowerDir;
extern CString g_sLangTxt_Native_PowerDir;

/*tr("评估")*/
extern CString g_sLangID_Native_Assessment;
extern CString g_sLangTxt_Native_Assessment;
/*"<h1>功率方向测试</h1>"*/
extern CString g_sLangID_Native_PowerDirTest;
extern CString g_sLangTxt_Native_PowerDirTest;
/*"A相测试"*/
extern CString g_sLangID_Native_PhaseATest;
extern CString g_sLangTxt_Native_PhaseATest;
/*"B相测试"*/
extern CString g_sLangID_Native_PhaseBTest;
extern CString g_sLangTxt_Native_PhaseBTest;
/*"C相测试"*/
extern CString g_sLangID_Native_PhaseCTest;
extern CString g_sLangTxt_Native_PhaseCTest;
/*"零序测试"*/
extern CString g_sLangID_Native_PhaseZeroTest;
extern CString g_sLangTxt_Native_PhaseZeroTest;
/*"负序测试"*/
extern CString g_sLangID_Native_PhaseLossTest;
extern CString g_sLangTxt_Native_PhaseLossTest;
/*tr("边界角1")*/
// extern CString g_sLangID_Native_BoundAngle1;
// extern CString g_sLangTxt_Native_BoundAngle1;
/*tr("边界角2")*/
extern CString g_sLangID_Native_BoundAngle2;
extern CString g_sLangTxt_Native_BoundAngle2;
/*tr("电压超前电流为正角度")*/
extern CString g_sLangID_Native_VoltAheadPosAng;
extern CString g_sLangTxt_Native_VoltAheadPosAng;
/*tr("电流超前电压为正角度")*/
extern CString g_sLangID_Native_CurrAheadPosAng;
extern CString g_sLangTxt_Native_CurrAheadPosAng;
/*tr("0度接线")*/
extern CString g_sLangID_Native_Deg0Conn;
extern CString g_sLangTxt_Native_Deg0Conn;
/*tr("90度接线")*/
extern CString g_sLangID_Native_Deg90Conn;
extern CString g_sLangTxt_Native_Deg90Conn;
/*QObject::tr("通用参数设置")*/
extern CString g_sLangID_Native_GenParamSet;
extern CString g_sLangTxt_Native_GenParamSet;
//稳态时间(s):
extern CString g_sLangID_Native_SteadyStateTime;
extern CString g_sLangTxt_Native_SteadyStateTime;




//PowerFreqTest_Trans 马
/*tr("工频变化量距离试验模板文件")*/
extern CString g_sLangID_Native_FreqChgDistTemp;
extern CString g_sLangTxt_Native_FreqChgDistTemp;
/*_T("欢迎使用工频变化量距离试验.")*/
extern CString g_sLangID_Native_WelcFreqChgTest;
extern CString g_sLangTxt_Native_WelcFreqChgTest;
/*tr("Ponovo 工频变化量距离试验")*/
extern CString g_sLangID_Native_PonovoFreqChgDist;
extern CString g_sLangTxt_Native_PonovoFreqChgDist;
/*tr("工频变化量距离")*/
extern CString g_sLangID_Native_FreqChgDistance;
extern CString g_sLangTxt_Native_FreqChgDistance;
/*tr("阻抗特性图")*/
extern CString g_sLangID_Native_ImpedChart;
extern CString g_sLangTxt_Native_ImpedChart;


/*QObject::tr("A相接地,")*/
extern CString g_sLangID_Native_PhaseAGround;
extern CString g_sLangTxt_Native_PhaseAGround;
/*QObject::tr("B相接地,")*/
extern CString g_sLangID_Native_PhaseBGround;
extern CString g_sLangTxt_Native_PhaseBGround;
/*QObject::tr("C相接地,")*/
extern CString g_sLangID_Native_PhaseCGround;
extern CString g_sLangTxt_Native_PhaseCGround;
/*QObject::tr("AB短路,")*/
extern CString g_sLangID_Native_PhaseABShortCircuit;
extern CString g_sLangTxt_Native_PhaseABShortCircuit;
/*QObject::tr("BC短路,")*/
extern CString g_sLangID_Native_PhaseBCShortCircuit;
extern CString g_sLangTxt_Native_PhaseBCShortCircuit;
/*QObject::tr("CA短路,")*/
extern CString g_sLangID_Native_PhaseCAShortCircuit;
extern CString g_sLangTxt_Native_PhaseCAShortCircuit;
/*QObject::tr("瞬时,")*/
extern CString g_sLangID_Native_Instantaneous;
extern CString g_sLangTxt_Native_Instantaneous;
/*QObject::tr("永久,")*/
extern CString g_sLangID_Native_Permanently;
extern CString g_sLangTxt_Native_Permanently;
/*"<h1>工频变化量距离测试</h1>"*/
extern CString g_sLangID_Native_FreqChgDistTest;
extern CString g_sLangTxt_Native_FreqChgDistTest;
/*"工频变化量距离"*/
extern CString g_sLangID_Native_FreqChgDist;
extern CString g_sLangTxt_Native_FreqChgDist;
/*"<h3>正方向</h3>"*/
extern CString g_sLangID_Native_PosDirection;
extern CString g_sLangTxt_Native_PosDirection;
/*"<h3>反方向</h3>"*/
extern CString g_sLangID_Native_RevDirection;
extern CString g_sLangTxt_Native_RevDirection;
/*"确定取消"*/
extern CString g_sLangID_OKCancel;
extern CString g_sLangTxt_OKCancel;
/*QObject::tr("母线侧")*/
extern CString g_sLangID_Native_BusSide;
extern CString g_sLangTxt_Native_BusSide;
/*QObject::tr("线路侧")*/
extern CString g_sLangID_Native_LineSide;
extern CString g_sLangTxt_Native_LineSide;
/*QObject::tr("指向母线")*/
extern CString g_sLangID_Native_TowardBus;
extern CString g_sLangTxt_Native_TowardBus;
/*QObject::tr("指向线路")*/
extern CString g_sLangID_Native_TowardLine;
extern CString g_sLangTxt_Native_TowardLine;
/*QObject::tr("不模拟")*/
extern CString g_sLangID_Native_NoSimulation;
extern CString g_sLangTxt_Native_NoSimulation;
/*tr("反向")*/
extern CString g_sLangID_Native_OppositeDirection;
extern CString g_sLangTxt_Native_OppositeDirection;
/*tr("正向")*/
extern CString g_sLangID_Native_PositiveDirection;
extern CString g_sLangTxt_Native_PositiveDirection;
/*tr("瞬时")*/
extern CString g_sLangID_Native_Immediate;
extern CString g_sLangTxt_Native_Immediate;
/*tr("永久")*/
extern CString g_sLangID_Native_Permanent;
extern CString g_sLangTxt_Native_Permanent;
/*tr("跳三相=%1s,")*/
extern CString g_sLangID_Native_Trip3Phase;
extern CString g_sLangTxt_Native_Trip3Phase;
/*tr("跳A=%1s,")*/
extern CString g_sLangID_Native_TripPhaseA;
extern CString g_sLangTxt_Native_TripPhaseA;
/*tr("跳B=%1s,")*/
extern CString g_sLangID_Native_TripPhaseB;
extern CString g_sLangTxt_Native_TripPhaseB;
/*tr("跳C=%1s,")*/
extern CString g_sLangID_Native_TripPhaseC;
extern CString g_sLangTxt_Native_TripPhaseC;
/*tr("重合闸=%1s,")*/
extern CString g_sLangID_Native_ReclosingSy;
extern CString g_sLangTxt_Native_ReclosingSy;
/*tr("后加速=%1s,")*/
extern CString g_sLangID_Native_PostAccel;
extern CString g_sLangTxt_Native_PostAccel;
/*tr("返回时间=%1s,")*/
extern CString g_sLangID_Native_TimeofReturn;
extern CString g_sLangTxt_Native_TimeofReturn;
/*tr("返回时间A=%1s,")*/
extern CString g_sLangID_Native_TimeofReturnA;
extern CString g_sLangTxt_Native_TimeofReturnA;
/*tr("返回时间B=%1s,")*/
extern CString g_sLangID_Native_TimeofReturnB;
extern CString g_sLangTxt_Native_TimeofReturnB;
/*tr("返回时间C=%1s,")*/
extern CString g_sLangID_Native_TimeofReturnC;
extern CString g_sLangTxt_Native_TimeofReturnC;
/*tr("返回时间D=%1s,")*/
extern CString g_sLangID_Native_TimeofReturnD;
extern CString g_sLangTxt_Native_TimeofReturnD;
//TV安装位置
extern CString g_sLangID_Native_TVInstLoc;
extern CString g_sLangTxt_Native_TVInstLoc;
//TA正极性
extern CString g_sLangID_Native_PosPolTA;
extern CString g_sLangTxt_Native_PosPolTA;
//断路器模拟
extern CString g_sLangID_Native_CBsim;
extern CString g_sLangTxt_Native_CBsim;
//分闸时间
extern CString g_sLangID_Native_TripTime;
extern CString g_sLangTxt_Native_TripTime;
//合闸时间
extern CString g_sLangID_Native_CloseTime;
extern CString g_sLangTxt_Native_CloseTime;
//阻抗特性
extern CString g_sLangID_Native_ImpChar;
extern CString g_sLangTxt_Native_ImpChar;


//start XWD 许
//ULOCKOVERCURRENTTEST 
//复压闭锁保护试验模板文件
extern CString g_sLangID_Native_RLPtestTF;
extern CString g_sLangTxt_Native_RLPtestTF;
//欢迎使用复压闭锁保护试验
extern CString g_sLangID_Native_WelUseRLPT;
extern CString g_sLangTxt_Native_WelUseRLPT;
//获取实时数据绝对时间失败
extern CString g_sLangID_Native_AbsoluteTimeF;
extern CString g_sLangTxt_Native_AbsoluteTimeF;
//获取实时数据相对时间失败
extern CString g_sLangID_Native_RelativeTimeF;
extern CString g_sLangTxt_Native_RelativeTimeF;
//Ponovo复压闭锁
extern CString g_sLangID_Native_PonovoRLO;
extern CString g_sLangTxt_Native_PonovoRLO;
//复压闭锁实验
extern CString g_sLangID_Native_RLOtest;
extern CString g_sLangTxt_Native_RLOtest;
//低电压
extern CString g_sLangID_Native_LowVoltage;
extern CString g_sLangTxt_Native_LowVoltage;
//负序电压
extern CString g_sLangID_Native_NegSeqVol;
extern CString g_sLangTxt_Native_NegSeqVol;
//动作电流
extern CString g_sLangID_Native_ActCurrent;
extern CString g_sLangTxt_Native_ActCurrent;
//动作区大小
extern CString g_sLangID_Native_ActAreaSize;
extern CString g_sLangTxt_Native_ActAreaSize;

//低电压动作值
extern CString g_sLangID_Native_LowVolTriVal;
extern CString g_sLangTxt_Native_LowVolTriVal;
//负序电压动作值
extern CString g_sLangID_Native_NegSeqVolTriVal;
extern CString g_sLangTxt_Native_NegSeqVolTriVal;
//电流动作值（C相）
extern CString g_sLangID_Native_CurOperC;
extern CString g_sLangTxt_Native_CurOperC;
//电流动作值（B相）
extern CString g_sLangID_Native_CurOperB;
extern CString g_sLangTxt_Native_CurOperB;
//电流动作值（A相）
extern CString g_sLangID_Native_CurOperA;
extern CString g_sLangTxt_Native_CurOperA;
//程序已经在运行
extern CString g_sLangID_Native_Running;
extern CString g_sLangTxt_Native_Running;
//最大灵敏角测试
extern CString g_sLangID_Native_MaxSensAngTest;
extern CString g_sLangTxt_Native_MaxSensAngTest;
//电流动作值
extern CString g_sLangID_Native_CurOperVal;
extern CString g_sLangTxt_Native_CurOperVal;
//AB相短路
extern CString g_sLangID_Native_AnBShortCir;
extern CString g_sLangTxt_Native_AnBShortCir;
//BC相短路
extern CString g_sLangID_Native_BnCShortCir;
extern CString g_sLangTxt_Native_BnCShortCir;
//CA相短路
extern CString g_sLangID_Native_CnAShortCir;
extern CString g_sLangTxt_Native_CnAShortCir;
//BC相短路电压 A相电流
extern CString g_sLangID_Native_ShortBCVolAndACur;
extern CString g_sLangTxt_Native_ShortBCVolAndACur;
//CA相短路电压 B相电流
extern CString g_sLangID_Native_ShortCAVolAndBCur;
extern CString g_sLangTxt_Native_ShortCAVolAndBCur;
//AB相短路电压 C相电流
extern CString g_sLangID_Native_ShortABVolAndCCur;
extern CString g_sLangTxt_Native_ShortABVolAndCCur;
//ABC短路
extern CString g_sLangID_Native_ABCSC;
extern CString g_sLangTxt_Native_ABCSC;
//复压闭锁测试
extern CString g_sLangID_Native_RLOTestAno;
extern CString g_sLangTxt_Native_RLOTestAno;
//边界角
extern CString g_sLangID_Native_BoundaryAngle;
extern CString g_sLangTxt_Native_BoundaryAngle;

//阻抗角(°)：
extern CString g_sLangID_Native_ImpedanceAngle;
extern CString g_sLangTxt_Native_ImpedanceAngle;
//变化始值(V)：
extern CString g_sLangID_Native_InitofVarV;
extern CString g_sLangTxt_Native_InitofVarV;
//变化终值(V)：
extern CString g_sLangID_Native_FinalofVarV;
extern CString g_sLangTxt_Native_FinalofVarV;
//变化步长(V)：
extern CString g_sLangID_Native_StepofVarV;
extern CString g_sLangTxt_Native_StepofVarV;
//变化始值(A)：
extern CString g_sLangID_Native_InitofVarA;
extern CString g_sLangTxt_Native_InitofVarA;
//变化终值(A)：
extern CString g_sLangID_Native_FinalofVarA;
extern CString g_sLangTxt_Native_FinalofVarA;
//变化步长(A)：
extern CString g_sLangID_Native_StepofVarA;
extern CString g_sLangTxt_Native_StepofVarA;



//ZEROSEQUENCETEST 许
//零序保护试验模板文件
extern CString g_sLangID_Native_ZeroSeqTF;
extern CString g_sLangTxt_Native_ZeroSeqTF;
//欢迎使用零序保护试验
extern CString g_sLangID_Native_WelUseZeroSeq;
extern CString g_sLangTxt_Native_WelUseZeroSeq;
//Ponovo 零序保护试验
extern CString g_sLangID_Native_PonovoZS;
extern CString g_sLangTxt_Native_PonovoZS;
//零序试验
extern CString g_sLangID_Native_ZeroSeqTest;
extern CString g_sLangTxt_Native_ZeroSeqTest;
//零序I段
extern CString g_sLangID_Native_ZeroSeqStageI;
extern CString g_sLangTxt_Native_ZeroSeqStageI;
//零序II段
extern CString g_sLangID_Native_ZeroSeqStageII;
extern CString g_sLangTxt_Native_ZeroSeqStageII;
//零序III段
extern CString g_sLangID_Native_ZeroSeqStageIII;
extern CString g_sLangTxt_Native_ZeroSeqStageIII;
//零序IV段
extern CString g_sLangID_Native_ZeroSeqStageIV;
extern CString g_sLangTxt_Native_ZeroSeqStageIV;
//零序V段
extern CString g_sLangID_Native_ZeroSeqStageV;
extern CString g_sLangTxt_Native_ZeroSeqStageV;
//开关量设置中，开入H没有设置成重合闸，软件已经自动把该项设置成重合闸
extern CString g_sLangID_Native_ZeroSeqWrH;
extern CString g_sLangTxt_Native_ZeroSeqWrH;
//开关量设置中，开入D没有设置成重合闸，软件已经自动把该项设置成重合闸
extern CString g_sLangID_Native_ZeroSeqWrD;
extern CString g_sLangTxt_Native_ZeroSeqWrD;
//开关量设置中，开入D、开入H没有设置成重合闸，软件已经自动把该项设置成重合闸
extern CString g_sLangID_Native_ZeroSeqWrDH;
extern CString g_sLangTxt_Native_ZeroSeqWrDH;
//试验名称：零序保护定值测试
extern CString g_sLangID_Native_TestOFZeroSeq;
extern CString g_sLangTxt_Native_TestOFZeroSeq;
//保护定值测试
extern CString g_sLangID_Native_TestofProSet;
extern CString g_sLangTxt_Native_TestofProSet;
//跳三相=%1s
extern CString g_sLangID_Native_ThrPhaseJump;
extern CString g_sLangTxt_Native_ThrPhaseJump;
//重合闸
extern CString g_sLangID_Native_Reclosing;
extern CString g_sLangTxt_Native_Reclosing;
//后加速
extern CString g_sLangID_Native_PostAcceleration;
extern CString g_sLangTxt_Native_PostAcceleration;



//CBOPERATETEST 许
//整组保护试验模板文件
extern CString g_sLangID_Native_UnitProTF;
extern CString g_sLangTxt_Native_UnitProTF;
//Ponovo整组传动
extern CString g_sLangID_Native_PonovoGroupTra;
extern CString g_sLangTxt_Native_PonovoGroupTra;
//欢迎使用整组传动
extern CString g_sLangID_Native_WelUseGroTra;
extern CString g_sLangTxt_Native_WelUseGroTra;
//整组传动
extern CString g_sLangID_Native_GroupTra;
extern CString g_sLangTxt_Native_GroupTra;
//阻抗角(°)
extern CString g_sLangID_Native_ImpAng;
extern CString g_sLangTxt_Native_ImpAng;
//试验名称：整组试验
extern CString g_sLangID_Native_NameGroTest;
extern CString g_sLangTxt_Native_NameGroTest;
//试验参数
extern CString g_sLangID_Native_TestPara;
extern CString g_sLangTxt_Native_TestPara;
//取消
extern CString g_sLangID_Cancel;
extern CString g_sLangTxt_Cancel;
//初始
extern CString g_sLangID_Native_Initial;
extern CString g_sLangTxt_Native_Initial;
//选中
extern CString g_sLangID_Native_Selected;
extern CString g_sLangTxt_Native_Selected;
//试验结束
extern CString g_sLangID_Native_EndTest;
extern CString g_sLangTxt_Native_EndTest;
//名称
extern CString g_sLangID_AttrID_Name;
extern CString g_sLangTxt_AttrID_Name;



//转换时间
extern CString g_sLangID_Native_TransientTime;
extern CString g_sLangTxt_Native_TransientTime;
//转换故障方向
extern CString g_sLangID_Native_TransientMalfDir;
extern CString g_sLangTxt_Native_TransientMalfDir;
//重合闸及后加速保护试验模板文件
extern CString g_sLangID_Native_RPAProTestTF;
extern CString g_sLangTxt_Native_RPAProTestTF;
//故障-|Z|(Ω)表达式异常！
extern CString g_sLangID_Native_RPAWro1;
extern CString g_sLangTxt_Native_RPAWro1;
//故障-阻抗角表达式异常！
extern CString g_sLangID_Native_RPAWro2;
extern CString g_sLangTxt_Native_RPAWro2;
//重合后-|Z|(Ω)表达式异常！
extern CString g_sLangID_Native_RPAWro3;
extern CString g_sLangTxt_Native_RPAWro3;
//跳闸后抽取电压相位表达式异常！
extern CString g_sLangID_Native_RPAWro4;
extern CString g_sLangTxt_Native_RPAWro4;
//跳闸后抽取电压表达式异常！
extern CString g_sLangID_Native_RPAWro5;
extern CString g_sLangTxt_Native_RPAWro5;
//重合闸及后加速试验
extern CString g_sLangID_Native_RPATest;
extern CString g_sLangTxt_Native_RPATest;
//欢迎使用重合闸及后加速试验.
extern CString g_sLangID_Native_WelUseRPATest;
extern CString g_sLangTxt_Native_WelUseRPATest;

//重合闸时限
extern CString g_sLangID_Native_RCTimeLim;
extern CString g_sLangTxt_Native_RCTimeLim;
//检无压定值
extern CString g_sLangID_Native_ZeroVolThr;
extern CString g_sLangTxt_Native_ZeroVolThr;
//检有压定值
extern CString g_sLangID_Native_VolDetThr;
extern CString g_sLangTxt_Native_VolDetThr;
//检同期角度
extern CString g_sLangID_Native_SynAngDet;
extern CString g_sLangTxt_Native_SynAngDet;
//零序补偿计算方式
extern CString g_sLangID_Native_CalZeroSeq;
extern CString g_sLangTxt_Native_CalZeroSeq;
//中文或
extern CString g_sLangID_Native_ChinOr;
extern CString g_sLangTxt_Native_ChinOr;
//重合闸及后加速测试
extern CString g_sLangID_Native_TestRPA;
extern CString g_sLangTxt_Native_TestRPA;
//故障性质-永久性故障
extern CString g_sLangID_Native_PermanentFau;
extern CString g_sLangTxt_Native_PermanentFau;
//故障性质-瞬时性故障
extern CString g_sLangID_Native_TransientFau;
extern CString g_sLangTxt_Native_TransientFau;
//请务必选择故障类型！
extern CString g_sLangID_Native_MustCho;
extern CString g_sLangTxt_Native_MustCho;
//检同期
extern CString g_sLangID_Native_SyncCheck;
extern CString g_sLangTxt_Native_SyncCheck;
//检线无压母有压
extern CString g_sLangID_Native_LineNoVolParD;
extern CString g_sLangTxt_Native_LineNoVolParD;
//检线有压母无压
extern CString g_sLangID_Native_LineHasVolParN;
extern CString g_sLangTxt_Native_LineHasVolParN;
//检线无压母无压
extern CString g_sLangID_Native_LineNoVolParT;
extern CString g_sLangTxt_Native_LineNoVolParT;
//检线有压母有压
extern CString g_sLangID_Native_LineHasVolParT;
extern CString g_sLangTxt_Native_LineHasVolParT;
//无输出
extern CString g_sLangID_Native_NoOutput;
extern CString g_sLangTxt_Native_NoOutput;
//|K0|或Re(K0)
extern CString g_sLangID_Native_KOorReKO;
extern CString g_sLangTxt_Native_KOorReKO;
//Phi(K0)或Im(K0)
extern CString g_sLangID_Native_PhiOrIm;
extern CString g_sLangTxt_Native_PhiOrIm;




//许文迪第二周
//故障回放试验模板文件
extern CString g_sLangID_Native_FaultReplayTF;
extern CString g_sLangTxt_Native_FaultReplayTF;
//当前模块只支持模拟量故障回放,强制设置为模拟量输出模式.
extern CString g_sLangID_Native_EnfSetAnalog;
extern CString g_sLangTxt_Native_EnfSetAnalog;
//欢迎使用故障回放试验.
extern CString g_sLangID_Native_WelUseFaultRe;
extern CString g_sLangTxt_Native_WelUseFaultRe;
//波形回放
extern CString g_sLangID_Native_WavePlayback;
extern CString g_sLangTxt_Native_WavePlayback;
//切换到上一页波形数据
extern CString g_sLangID_Native_PreWaveData;
extern CString g_sLangTxt_Native_PreWaveData;
//切换到下一页波形数据
extern CString g_sLangID_Native_NextWaveData;
extern CString g_sLangTxt_Native_NextWaveData;
//故障回放
extern CString g_sLangID_Native_MalfunctionRe;
extern CString g_sLangTxt_Native_MalfunctionRe;
//请打开录波文件
extern CString g_sLangID_Native_OpenWaveFile;
extern CString g_sLangTxt_Native_OpenWaveFile;
//正在下载波形数据...
extern CString g_sLangID_Native_DownloadWaveData;	 
extern CString g_sLangTxt_Native_DownloadWaveData;
//当前电压通道回放的最大电压值(%lf),大于测试仪最大输出电压(%f).
extern CString g_sLangID_Native_FaultReplayWr3;
extern CString g_sLangTxt_Native_FaultReplayWr3;
//当前电流通道回放的最大电流值(%lf),大于测试仪最大输出电流(%f).
extern CString g_sLangID_Native_FaultReplayWr4;
extern CString g_sLangTxt_Native_FaultReplayWr4;
//变比
extern CString g_sLangID_Native_TransfRatio;
extern CString g_sLangTxt_Native_TransfRatio;
//A通道描述查找出错(%s)(%ld).
extern CString g_sLangID_Native_AChannelDesError;
extern CString g_sLangTxt_Native_AChannelDesError;
//B通道描述查找出错(%s)(%ld).
extern CString g_sLangID_Native_BChannelDesError;
extern CString g_sLangTxt_Native_BChannelDesError;


//搜索阻抗边界试验模板文件
extern CString g_sLangID_Native_SITmpl;
extern CString g_sLangTxt_Native_SITmpl;
//欢迎使用搜索阻抗边界试验
extern CString g_sLangID_Native_SIWelcome;
extern CString g_sLangTxt_Native_SIWelcome;
//Ponovo 搜索阻抗边界
extern CString g_sLangID_Native_SIPonovo;
extern CString g_sLangTxt_Native_SIPonovo;
//搜索阻抗边界试验
extern CString g_sLangID_Native_SITest;
extern CString g_sLangTxt_Native_SITest;
//搜索阻抗边界
extern CString g_sLangID_Native_SISearch;
extern CString g_sLangTxt_Native_SISearch;
//配置文件：%s 不存在
extern CString g_sLangID_Native_ConfigFileNotExist;
extern CString g_sLangTxt_Native_ConfigFileNotExist;
//请选择故障类型
extern CString g_sLangID_Native_SelectFaultType;
extern CString g_sLangTxt_Native_SelectFaultType;
//阻抗角始值
extern CString g_sLangID_Native_ImpedanceAngleStart;
extern CString g_sLangTxt_Native_ImpedanceAngleStart;
//阻抗角终值
extern CString g_sLangID_Native_ImpedanceAngleEnd;
extern CString g_sLangTxt_Native_ImpedanceAngleEnd;
//角度改变步长
extern CString g_sLangID_Native_AngleChangeStep;
extern CString g_sLangTxt_Native_AngleChangeStep;

//欢迎使用状态序列
extern CString g_sLangID_Native_WelcomeSeq;
extern CString g_sLangTxt_Native_WelcomeSeq;
//状态序列
extern CString g_sLangID_Native_StateSeq;
extern CString g_sLangTxt_Native_StateSeq;

//次状态序列状态
extern CString g_sLangID_Native_StateSeqStatus;
extern CString g_sLangTxt_Native_StateSeqStatus;
//已选择状态数超过最大值
extern CString g_sLangID_Native_SelectedStateNumExceed;
extern CString g_sLangTxt_Native_SelectedStateNumExceed;

//出口
extern CString g_sLangID_Native_Exit;
extern CString g_sLangTxt_Native_Exit;
//触发时间(s)
extern CString g_sLangID_Native_TrigTimeS;
extern CString g_sLangTxt_Native_TrigTimeS;

//开出一状态
extern CString g_sLangID_Native_OutOneState;
extern CString g_sLangTxt_Native_OutOneState;
//开出二状态
extern CString g_sLangID_Native_OutTwoState;
extern CString g_sLangTxt_Native_OutTwoState;
//开出三状态
extern CString g_sLangID_Native_OutThreeState;
extern CString g_sLangTxt_Native_OutThreeState;
//开出四状态
extern CString g_sLangID_Native_OutFourState;
extern CString g_sLangTxt_Native_OutFourState;
//开出五状态
extern CString g_sLangID_Native_OutFiveState;
extern CString g_sLangTxt_Native_OutFiveState;
//开出六状态
extern CString g_sLangID_Native_OutSixState;
extern CString g_sLangTxt_Native_OutSixState;
//开出七状态
extern CString g_sLangID_Native_OutSevenState;
extern CString g_sLangTxt_Native_OutSevenState;
//开出八状态
extern CString g_sLangID_Native_OutEightState;
extern CString g_sLangTxt_Native_OutEightState;
//开入A动作时间(s)
extern CString g_sLangID_Native_InAActTime;
extern CString g_sLangTxt_Native_InAActTime;
//开入B动作时间(s)
extern CString g_sLangID_Native_InBActTime;
extern CString g_sLangTxt_Native_InBActTime;
//开入C动作时间(s)
extern CString g_sLangID_Native_InCActTime;
extern CString g_sLangTxt_Native_InCActTime;
//开入D动作时间(s)
extern CString g_sLangID_Native_InDActTime;
extern CString g_sLangTxt_Native_InDActTime;
//开入E动作时间(s)
extern CString g_sLangID_Native_InEActTime;
extern CString g_sLangTxt_Native_InEActTime;
//开入F动作时间(s)
extern CString g_sLangID_Native_InFActTime;
extern CString g_sLangTxt_Native_InFActTime;
//开入G动作时间(s)
extern CString g_sLangID_Native_InGActTime;
extern CString g_sLangTxt_Native_InGActTime;
//开入H动作时间(s)
extern CString g_sLangID_Native_InHActTime;
extern CString g_sLangTxt_Native_InHActTime;


//开出%d状态
extern CString g_sLangID_Native_OutputState;
extern CString g_sLangTxt_Native_OutputState;
//未知触发模式
extern CString g_sLangID_Native_UnknownTrigger;
extern CString g_sLangTxt_Native_UnknownTrigger;
//输入值%f超出范围(%f).
extern CString g_sLangID_Native_InputOutOfRange;
extern CString g_sLangTxt_Native_InputOutOfRange;
//试验列表
extern CString g_sLangID_Native_TestList;
extern CString g_sLangTxt_Native_TestList;
//试验结果
extern CString g_sLangID_Native_TestResult;
extern CString g_sLangTxt_Native_TestResult;
//添加状态
extern CString g_sLangID_Native_AddState;
extern CString g_sLangTxt_Native_AddState;
//删除状态
extern CString g_sLangID_Native_DelState;
extern CString g_sLangTxt_Native_DelState;
//删除N-1
extern CString g_sLangID_Native_DelN1;
extern CString g_sLangTxt_Native_DelN1;
//相角(°)
extern CString g_sLangID_Native_PhaseAngle;
extern CString g_sLangTxt_Native_PhaseAngle;
// SV异常模拟
extern CString g_sLangID_Native_SVAbnSim;
extern CString g_sLangTxt_Native_SVAbnSim;

//ManualTest_Trans 马嘉骅第二周
/*_T("欢迎使用通用试验.")*/
extern CString g_sLangID_Native_WelcomeGenTest;
extern CString g_sLangTxt_Native_WelcomeGenTest;
/*_T(" 通用试验")*/
extern CString g_sLangID_Native_blankGenTest;
extern CString g_sLangTxt_Native_blankGenTest;
/*tr("开入设置(扩展)")*/
extern CString g_sLangID_Native_InputSetExt;
extern CString g_sLangTxt_Native_InputSetExt;
/*tr("开出设置(扩展)")*/
extern CString g_sLangID_Native_OutputSetExt;
extern CString g_sLangTxt_Native_OutputSetExt;
/*tr("动作值(")*/
extern CString g_sLangID_Native_ActValuePar;
extern CString g_sLangTxt_Native_ActValuePar;
/*tr("):")*/
extern CString g_sLangID_Native_BrackColon;
extern CString g_sLangTxt_Native_BrackColon;
/*tr("返回值(")*/
extern CString g_sLangID_Native_ReturnValuePar;
extern CString g_sLangTxt_Native_ReturnValuePar;
/*tr("始值(")*/
extern CString g_sLangID_Native_InitialValPar;
extern CString g_sLangTxt_Native_InitialValPar;
/*tr("终值(")*/
extern CString g_sLangID_Native_EndValPar;
extern CString g_sLangTxt_Native_EndValPar;
/*tr("步长(")*/
extern CString g_sLangID_Native_StepSizePar;
extern CString g_sLangTxt_Native_StepSizePar;
//直流UAB
extern CString g_sLangID_Native_DCUAB;
extern CString g_sLangTxt_Native_DCUAB;
//开出设置及返回结果
extern CString g_sLangID_Native_OpenSett;
extern CString g_sLangTxt_Native_OpenSett;



//OscillationTest_Trans 马
/*tr("振荡试验模板文件")*/
extern CString g_sLangID_Native_OscilTestTemp;
extern CString g_sLangTxt_Native_OscilTestTemp;
/*_T("欢迎使用振荡试验.")*/
extern CString g_sLangID_Native_WelcomeOscTest;
extern CString g_sLangTxt_Native_WelcomeOscTest;
/*tr("Ponovo 振荡试验")*/
extern CString g_sLangID_Native_PonovoOscTest;
extern CString g_sLangTxt_Native_PonovoOscTest;
/*tr("振荡试验")*/
extern CString g_sLangID_Native_OscilTest;
extern CString g_sLangTxt_Native_OscilTest;

/*QObject::tr("功角振荡")*/
extern CString g_sLangID_Native_AngleOscil;
extern CString g_sLangTxt_Native_AngleOscil;
/*"振荡"*/
extern CString g_sLangID_Native_Oscillation;
extern CString g_sLangTxt_Native_Oscillation;
/*测试参数*/
extern CString g_sLangID_Native_TestParams;
extern CString g_sLangTxt_Native_TestParams;
/*功角始值(°)*/
extern CString g_sLangID_Native_AngleStartPar;
extern CString g_sLangTxt_Native_AngleStartPar;
/*功角终值(°)*/
extern CString g_sLangID_Native_AngleEndPar;
extern CString g_sLangTxt_Native_AngleEndPar;
/*振荡周期(s)*/
extern CString g_sLangID_Native_OscilPeriod;
extern CString g_sLangTxt_Native_OscilPeriod;
/*跳闸接点*/
extern CString g_sLangID_Native_TripContacts;
extern CString g_sLangTxt_Native_TripContacts;
/*振荡中再故障*/
extern CString g_sLangID_Native_OscilReFault;
extern CString g_sLangTxt_Native_OscilReFault;
/*使用阻抗滑差递变方式*/
extern CString g_sLangID_Native_ImpedSlipRamp;
extern CString g_sLangTxt_Native_ImpedSlipRamp;
/*往复振荡*/
extern CString g_sLangID_Native_RecipOsc;
extern CString g_sLangTxt_Native_RecipOsc;
/*增速振荡*/
extern CString g_sLangID_Native_AccelOsc;
extern CString g_sLangTxt_Native_AccelOsc;

/*故障发生时刻*/
extern CString g_sLangID_Native_FaultTime;
extern CString g_sLangTxt_Native_FaultTime;
/*结果名称*/
extern CString g_sLangID_Native_ResultName;
extern CString g_sLangTxt_Native_ResultName;
/*保护出口时间(s)*/
extern CString g_sLangID_Native_ProtRelayTime;
extern CString g_sLangTxt_Native_ProtRelayTime;
/*加速信号出口时间(s)*/
extern CString g_sLangID_Native_AccelSigOutTime;
extern CString g_sLangTxt_Native_AccelSigOutTime;
/*减速信号出口时间(s)*/
extern CString g_sLangID_Native_DecelSigOutTime;
extern CString g_sLangTxt_Native_DecelSigOutTime;
/*tr("保护出口时间=")*/
extern CString g_sLangID_Native_ProtOutTimePar;
extern CString g_sLangTxt_Native_ProtOutTimePar;
/*tr("加速信号时间=")*/
extern CString g_sLangID_Native_AccelTimePar;
extern CString g_sLangTxt_Native_AccelTimePar;
/*tr("减速信号时间=")*/
extern CString g_sLangID_Native_DecelTimePar;
extern CString g_sLangTxt_Native_DecelTimePar;

//发电机暂态电抗
extern CString g_sLangID_Native_GenTranReact;
extern CString g_sLangTxt_Native_GenTranReact;

//表达方式
extern CString g_sLangID_Native_ExprMethod;
extern CString g_sLangTxt_Native_ExprMethod;
//增速
extern CString g_sLangID_Native_RateIncr;
extern CString g_sLangTxt_Native_RateIncr;
//减速
extern CString g_sLangID_Native_Decel;
extern CString g_sLangTxt_Native_Decel;

//OverCurrentTest_Trans 马
/*tr("过流试验模板文件")*/
extern CString g_sLangID_Native_OvrCurrTestTemp;
extern CString g_sLangTxt_Native_OvrCurrTestTemp;
/*_T("欢迎使用过流测试.")*/
extern CString g_sLangID_Native_WelcomeOvrCurrTest;
extern CString g_sLangTxt_Native_WelcomeOvrCurrTest;
/*tr("过流")*/
extern CString g_sLangID_Native_OvrCurr;
extern CString g_sLangTxt_Native_OvrCurr;
/*tr("时间特性图")*/
extern CString g_sLangID_Native_TimeChart;
extern CString g_sLangTxt_Native_TimeChart;
/*_T("过流I段动作值")*/
extern CString g_sLangID_Native_OvrCurrIAct;
extern CString g_sLangTxt_Native_OvrCurrIAct;
/*_T("过流II段动作值")*/
extern CString g_sLangID_Native_OvrCurrIIAct;
extern CString g_sLangTxt_Native_OvrCurrIIAct;
/*_T("过流III段动作值")*/
extern CString g_sLangID_Native_OvrCurrIIIAct;
extern CString g_sLangTxt_Native_OvrCurrIIIAct;
/*_T("过流IV段动作值")*/
extern CString g_sLangID_Native_OvrCurrIVAct;
extern CString g_sLangTxt_Native_OvrCurrIVAct;
/*_T("过流V段动作值")*/
extern CString g_sLangID_Native_OvrCurrVAct;
extern CString g_sLangTxt_Native_OvrCurrVAct;
/*_T("过流I段动作时间")*/
extern CString g_sLangID_Native_OvrCurrITime;
extern CString g_sLangTxt_Native_OvrCurrITime;
/*_T("过流II段动作时间")*/
extern CString g_sLangID_Native_OvrCurrIITime;
extern CString g_sLangTxt_Native_OvrCurrIITime;
/*_T("过流III段动作时间")*/
extern CString g_sLangID_Native_OvrCurrIIITime;
extern CString g_sLangTxt_Native_OvrCurrIIITime;
/*_T("过流IV段动作时间")*/
extern CString g_sLangID_Native_OvrCurrIVTime;
extern CString g_sLangTxt_Native_OvrCurrIVTime;
/*_T("过流V段动作时间")*/
extern CString g_sLangID_Native_OvrCurrVTime;
extern CString g_sLangTxt_Native_OvrCurrVTime;

/*"<h1>试验名称：过流保护定值测试</h1>"*/
extern CString g_sLangID_Native_TestNameOvrCurr;
extern CString g_sLangTxt_Native_TestNameOvrCurr;
/*"过流I段保护定值测试"*/
extern CString g_sLangID_Native_OvrCurrIProtTest;
extern CString g_sLangTxt_Native_OvrCurrIProtTest;
/*"过流II段保护定值测试"*/
extern CString g_sLangID_Native_OvrCurrIIProtTest;
extern CString g_sLangTxt_Native_OvrCurrIIProtTest;
/*"过流III段保护定值测试"*/
extern CString g_sLangID_Native_OvrCurrIIIProtTest;
extern CString g_sLangTxt_Native_OvrCurrIIIProtTest;
/*"过流IV段保护定值测试"*/
extern CString g_sLangID_Native_OvrCurrIVProtTest;
extern CString g_sLangTxt_Native_OvrCurrIVProtTest;
/*"过流V段保护定值测试"*/
extern CString g_sLangID_Native_OvrCurrVProtTest;
extern CString g_sLangTxt_Native_OvrCurrVProtTest;
/*tr("默认值 = Iset1")*/
extern CString g_sLangID_Native_DefaultIset1;
extern CString g_sLangTxt_Native_DefaultIset1;
/*tr("默认值 = Iset2")*/
extern CString g_sLangID_Native_DefaultIset2;
extern CString g_sLangTxt_Native_DefaultIset2;
/*tr("默认值 = Iset3")*/
extern CString g_sLangID_Native_DefaultIset3;
extern CString g_sLangTxt_Native_DefaultIset3;
/*tr("默认值 = Iset4")*/
extern CString g_sLangID_Native_DefaultIset4;
extern CString g_sLangTxt_Native_DefaultIset4;
/*tr("默认值 = Iset5")*/
extern CString g_sLangID_Native_DefaultIset5;
extern CString g_sLangTxt_Native_DefaultIset5;
/*tr("默认值 = Tset1")*/
extern CString g_sLangID_Native_DefaultTset1;
extern CString g_sLangTxt_Native_DefaultTset1;
/*tr("默认值 = Tset2")*/
extern CString g_sLangID_Native_DefaultTset2;
extern CString g_sLangTxt_Native_DefaultTset2;
/*tr("默认值 = Tset3")*/
extern CString g_sLangID_Native_DefaultTset3;
extern CString g_sLangTxt_Native_DefaultTset3;
/*tr("默认值 = Tset4")*/
extern CString g_sLangID_Native_DefaultTset4;
extern CString g_sLangTxt_Native_DefaultTset4;
/*tr("默认值 = Tset5")*/
extern CString g_sLangID_Native_DefaultTset5;
extern CString g_sLangTxt_Native_DefaultTset5;
/*tr("ABC相")*/
extern CString g_sLangID_Native_PhaseABC;
extern CString g_sLangTxt_Native_PhaseABC;
/*tr("或")*/
extern CString g_sLangID_Native_Or;
extern CString g_sLangTxt_Native_Or;
/*tr("与")*/
extern CString g_sLangID_Native_And;
extern CString g_sLangTxt_Native_And;
//模拟PT断线
extern CString g_sLangID_Native_SimDisconn;
extern CString g_sLangTxt_Native_SimDisconn;

//PT断线相
extern CString g_sLangID_Native_OpenPh;
extern CString g_sLangTxt_Native_OpenPh;




//吕洋第二周 Gradient
extern CString g_sLangID_Native_DistProtect_TempFile;
extern CString g_sLangTxt_Native_DistProtect_TempFile;//距离保护模板文件
extern CString g_sLangID_Native_Wel_DisProtect;
extern CString g_sLangTxt_Native_Wel_DisProtect;//欢迎使用距离保护.
extern CString g_sLangID_Native_PonovoDisProtect;
extern CString g_sLangTxt_Native_PonovoDisProtect;//Ponovo 距离保护
extern CString g_sLangID_Native_DisProtect;
extern CString g_sLangTxt_Native_DisProtect;//距离保护
extern CString g_sLangID_Native_DisProt_SetTest;
extern CString g_sLangTxt_Native_DisProt_SetTest;//距离保护定值测试
extern CString g_sLangID_Native_multiple;
extern CString g_sLangTxt_Native_multiple;//倍,R=
extern CString g_sLangID_Native_Para;
extern CString g_sLangTxt_Native_Para;//段
extern CString g_sLangID_Native_GroundFaultI;
extern CString g_sLangTxt_Native_GroundFaultI;
extern CString g_sLangID_Native_GroundFaultII;
extern CString g_sLangTxt_Native_GroundFaultII;
extern CString g_sLangID_Native_GroundFaultIII;
extern CString g_sLangTxt_Native_GroundFaultIII;
extern CString g_sLangID_Native_GroundFaultIV;
extern CString g_sLangTxt_Native_GroundFaultIV;
extern CString g_sLangID_Native_GroundFaultV;
extern CString g_sLangTxt_Native_GroundFaultV;//接地故障1-5段
extern CString g_sLangID_Native_PhaseFaultI;
extern CString g_sLangTxt_Native_PhaseFaultI;
extern CString g_sLangID_Native_PhaseFaultII;
extern CString g_sLangTxt_Native_PhaseFaultII;
extern CString g_sLangID_Native_PhaseFaultIII;
extern CString g_sLangTxt_Native_PhaseFaultIII;
extern CString g_sLangID_Native_PhaseFaultIV;
extern CString g_sLangTxt_Native_PhaseFaultIV;
extern CString g_sLangID_Native_PhaseFaultV;
extern CString g_sLangTxt_Native_PhaseFaultV;//相间故障1-5段
extern CString g_sLangID_Native_Wel_IncreExper;
extern CString g_sLangTxt_Native_Wel_IncreExper;//欢迎使用递变测试.
extern CString g_sLangID_Native_ImpedanceSet;
extern CString g_sLangTxt_Native_ImpedanceSet;//阻抗定值(Ω):
extern CString g_sLangID_Native_PonovoIncre;
extern CString g_sLangTxt_Native_PonovoIncre;//Ponovo递变
extern CString g_sLangID_Native_IncreExper;
extern CString g_sLangTxt_Native_IncreExper;//递变实验
extern CString g_sLangID_Native_PrepareTime;
extern CString g_sLangTxt_Native_PrepareTime;  // 变化前时间(s)

extern CString g_sLangID_Native_PreCurrent;
extern CString g_sLangTxt_Native_PreCurrent;  // 变化前电流幅值(A)
extern CString g_sLangID_Native_PreAngle;
extern CString g_sLangTxt_Native_PreAngle;  // 故障前电压电流相角(°)
extern CString g_sLangID_TestItem1;
extern CString g_sLangTxt_TestItem1;//测试项—
extern CString g_sLangID_Native_InputAction;
extern CString g_sLangTxt_Native_InputAction;  // 开入%1，动作值：%2
extern CString g_sLangID_Native_ExInputAction;
extern CString g_sLangTxt_Native_ExInputAction;  // 扩展开入%1，动作值：%2
//extern CString g_sLangID_SettingActionValue;
//extern CString g_sLangTxt_SettingActionValue;  // 整定动作值

extern CString g_sLangID_Native_NormalOutpExSet;
extern CString g_sLangTxt_Native_NormalOutpExSet;//常态开出设置（扩展）
extern CString g_sLangID_Native_FaultOutpExSet;
extern CString g_sLangTxt_Native_FaultOutpExSet;//故障态开出设置(扩展)
extern CString g_sLangID_Native_All;
extern CString g_sLangTxt_Native_All;//全部
extern CString g_sLangID_Experiment;
extern CString g_sLangTxt_Experiment;  // 试验

extern CString g_sLangID_Native_InitofVarP;
extern CString g_sLangTxt_Native_InitofVarP;//变化始值(°)：
extern CString g_sLangID_Native_FinalofVarP;
extern CString g_sLangTxt_Native_FinalofVarP;//变化终值(°)：
extern CString g_sLangID_Native_StepofVarP;
extern CString g_sLangTxt_Native_StepofVarP;//变化步长(°)：
extern CString g_sLangID_Native_InitofVarF;
extern CString g_sLangTxt_Native_InitofVarF;//变化始值(Hz)：
extern CString g_sLangID_Native_FinalofVarF;
extern CString g_sLangTxt_Native_FinalofVarF;//变化终值(Hz)：
extern CString g_sLangID_Native_StepofVarF;
extern CString g_sLangTxt_Native_StepofVarF;//变化步长(Hz)：

//xwd 第三周
//牵引变差动试验模板文件
extern CString g_sLangID_Native_TracVarTestTpl;
extern CString g_sLangTxt_Native_TracVarTestTpl;
//欢迎使用牵引变差动测试
extern CString g_sLangID_Native_WelcTracVarTest;
extern CString g_sLangTxt_Native_WelcTracVarTest;
//Ponovo 牵引变差动
extern CString g_sLangID_Native_PonTracVar;
extern CString g_sLangTxt_Native_PonTracVar;

//牵引变差动
extern CString g_sLangID_Native_TracVar;
extern CString g_sLangTxt_Native_TracVar;

//故障时间(s)
extern CString g_sLangID_Native_FaultTimes;
extern CString g_sLangTxt_Native_FaultTimes;
//高低压测CT极性定义
extern CString g_sLangID_Native_HLCTPolarDef;
extern CString g_sLangTxt_Native_HLCTPolarDef;

//定值名称
extern CString g_sLangID_Native_SetValueName;
extern CString g_sLangTxt_Native_SetValueName;
//差动速断电流定值(ln)
extern CString g_sLangID_Native_DiffQBrkCurrSetValue;
extern CString g_sLangTxt_Native_DiffQBrkCurrSetValue;
//差动动作电流门槛值(ln)
extern CString g_sLangID_Native_DiffActCurrThresh;
extern CString g_sLangTxt_Native_DiffActCurrThresh;
//比率制动特性拐点数1电流(ln)
extern CString g_sLangID_Native_RatioBrkInflect1Curr;
extern CString g_sLangTxt_Native_RatioBrkInflect1Curr;
//比率制动特性拐点数2电流(ln)
extern CString g_sLangID_Native_RatioBrkInflect2Curr;
extern CString g_sLangTxt_Native_RatioBrkInflect2Curr;
//整定方式
extern CString g_sLangID_Native_SettingMode;
extern CString g_sLangTxt_Native_SettingMode;
//高压侧CT极性定义
extern CString g_sLangID_Native_HvCTPolarity;
extern CString g_sLangTxt_Native_HvCTPolarity;

//变化前时间(s):
extern CString g_sLangID_Native_PreChangeTime;
extern CString g_sLangTxt_Native_PreChangeTime;
//故障前时间(s):
extern CString g_sLangID_Native_PreFaultTimes;
extern CString g_sLangTxt_Native_PreFaultTimes;
//常态电压幅值(V):
extern CString g_sLangID_Native_NormalVoltAmp;
extern CString g_sLangTxt_Native_NormalVoltAmp;
//常态电压相序:
extern CString g_sLangID_Native_NormalVoltPhase;
extern CString g_sLangTxt_Native_NormalVoltPhase;
//常态电流幅值(A):
extern CString g_sLangID_Native_NormalCurrAmp;
extern CString g_sLangTxt_Native_NormalCurrAmp;
//常态电流相序:
extern CString g_sLangID_Native_NormalCurrPhase;
extern CString g_sLangTxt_Native_NormalCurrPhase;
//常态相角(U-I)
extern CString g_sLangID_Native_NormalPhaseAngle;
extern CString g_sLangTxt_Native_NormalPhaseAngle;
//故障模式：
extern CString g_sLangID_Native_FaultMode;
extern CString g_sLangTxt_Native_FaultMode;
//变化量：
extern CString g_sLangID_Native_ChangeAmount;
extern CString g_sLangTxt_Native_ChangeAmount;
//短路电压(V)：
// extern CString g_sLangID_Native_ShortCircuitVs;
// extern CString g_sLangTxt_Native_ShortCircuitVs;
//短路电流(A)：
extern CString g_sLangID_Native_ShortCircuitAs;
extern CString g_sLangTxt_Native_ShortCircuitAs;
//频率(Hz)：
extern CString g_sLangID_Native_FrequencyHz;
extern CString g_sLangTxt_Native_FrequencyHz;
//记录量：
extern CString g_sLangID_Native_RecordQty;
extern CString g_sLangTxt_Native_RecordQty;
//步长时间(s)：
extern CString g_sLangID_Native_StepTimeS;
extern CString g_sLangTxt_Native_StepTimeS;

//整定值(A)
extern CString g_sLangID_Native_SetValueA;
extern CString g_sLangTxt_Native_SetValueA;
//整定动作时间(s)
extern CString g_sLangID_Native_SetActTimeS;
extern CString g_sLangTxt_Native_SetActTimeS;

//Ⅰ段
extern CString g_sLangID_Native_SectionI;
extern CString g_sLangTxt_Native_SectionI;
//Ⅱ段
extern CString g_sLangID_Native_SectionII;
extern CString g_sLangTxt_Native_SectionII;
//Ⅲ段
extern CString g_sLangID_Native_SectionIII;
extern CString g_sLangTxt_Native_SectionIII;
//Ⅳ段
extern CString g_sLangID_Native_SectionIV;
extern CString g_sLangTxt_Native_SectionIV;
//Ⅴ段
extern CString g_sLangID_Native_SectionV;
extern CString g_sLangTxt_Native_SectionV;
//故障方向:
extern CString g_sLangID_Native_FaultDir;
extern CString g_sLangTxt_Native_FaultDir;

//确  认
extern CString g_sLangID_Native_Confirm;
extern CString g_sLangTxt_Native_Confirm;
//名称：
extern CString g_sLangID_Native_Name;
extern CString g_sLangTxt_Native_Name;
//零序电流定值(A):
extern CString g_sLangID_Native_ZeroSeqCurr;
extern CString g_sLangTxt_Native_ZeroSeqCurr;
//故障触发时刻:
extern CString g_sLangID_Native_FaultTriggerTime;
extern CString g_sLangTxt_Native_FaultTriggerTime;
//倍数:
extern CString g_sLangID_Native_Multiples;
extern CString g_sLangTxt_Native_Multiples;
//整定动作时间(s):
extern CString g_sLangID_Native_SetActTime;
extern CString g_sLangTxt_Native_SetActTime;
//负荷电流(A)
extern CString g_sLangID_Native_LoadCurrent;
extern CString g_sLangTxt_Native_LoadCurrent;
//负荷功角(°)
extern CString g_sLangID_Native_LoadPowerAngle;
extern CString g_sLangTxt_Native_LoadPowerAngle;
//最大故障时间(s)
extern CString g_sLangID_Native_MaxFaultTime;
extern CString g_sLangTxt_Native_MaxFaultTime;
//转换性故障
extern CString g_sLangID_Native_TransFault;
extern CString g_sLangTxt_Native_TransFault;
//转换时间(s)
extern CString g_sLangID_Native_TransTime;
extern CString g_sLangTxt_Native_TransTime;
//故障触发时刻
extern CString g_sLangID_Native_FaultTriggerTimes;
extern CString g_sLangTxt_Native_FaultTriggerTimes;
//接地距离定值
extern CString g_sLangID_Native_GrdDistFixed;
extern CString g_sLangTxt_Native_GrdDistFixed;
//相间距离定值
extern CString g_sLangID_Native_DistValue;
extern CString g_sLangTxt_Native_DistValue;
//短路阻抗/整定阻抗    
extern CString g_sLangID_Native_Impedance;
extern CString g_sLangTxt_Native_Impedance;
//接地整定时间(s)
extern CString g_sLangID_Native_GrdSetTime;
extern CString g_sLangTxt_Native_GrdSetTime;
//相间整定时间(s)
extern CString g_sLangID_Native_PhaseSetTime;
extern CString g_sLangTxt_Native_PhaseSetTime;
//I段阻抗(Ω):
extern CString g_sLangID_Native_Impedance1;
extern CString g_sLangTxt_Native_Impedance1;
//II段阻抗(Ω):
extern CString g_sLangID_Native_Impedance2;
extern CString g_sLangTxt_Native_Impedance2;
//III段阻抗(Ω):
extern CString g_sLangID_Native_Impedance3;
extern CString g_sLangTxt_Native_Impedance3;
//IV段阻抗(Ω):
extern CString g_sLangID_Native_Impedance4;
extern CString g_sLangTxt_Native_Impedance4;
//V段阻抗(Ω):
extern CString g_sLangID_Native_Impedance5;
extern CString g_sLangTxt_Native_Impedance5;
//反方向
extern CString g_sLangID_Native_ReverseDir;
extern CString g_sLangTxt_Native_ReverseDir;
//误差范围(%):
extern CString g_sLangID_Native_ErrorRange;
extern CString g_sLangTxt_Native_ErrorRange;
//取  消
extern CString g_sLangID_Native_Cancel;
extern CString g_sLangTxt_Native_Cancel;
//重合后
extern CString g_sLangID_Native_AfterOverlap;
extern CString g_sLangTxt_Native_AfterOverlap;
//频率(Hz)
extern CString g_sLangID_Native_FreqHz;
extern CString g_sLangTxt_Native_FreqHz;
//抽取电压选择
extern CString g_sLangID_Native_VoltSelect;
extern CString g_sLangTxt_Native_VoltSelect;
//跳闸后抽取电压（V）
extern CString g_sLangID_Native_VoltAfterTrip;
extern CString g_sLangTxt_Native_VoltAfterTrip;
//跳闸后抽取电压相位°
extern CString g_sLangID_Native_VoltPhaseAfterTrip;
extern CString g_sLangTxt_Native_VoltPhaseAfterTrip;
//变化始值：
extern CString g_sLangID_Native_ChangeStartVal;
extern CString g_sLangTxt_Native_ChangeStartVal;
//变化终值：
extern CString g_sLangID_Native_ChangeEndVal;
extern CString g_sLangTxt_Native_ChangeEndVal;
//变化步长：
extern CString g_sLangID_Native_ChangeStep;
extern CString g_sLangTxt_Native_ChangeStep;
//测试点：
extern CString g_sLangID_Native_TestPoint;
extern CString g_sLangTxt_Native_TestPoint;
//故障时间(s)：
extern CString g_sLangID_Native_FaultTimeS;
extern CString g_sLangTxt_Native_FaultTimeS;
//整定方式：
extern CString g_sLangID_Native_SettingModes;
extern CString g_sLangTxt_Native_SettingModes;
//基准电流(A)：
extern CString g_sLangID_Native_BaseCurrent;
extern CString g_sLangTxt_Native_BaseCurrent;
//搜索方法：
extern CString g_sLangID_Native_SearchMethod;
extern CString g_sLangTxt_Native_SearchMethod;
// 高低压测CT极性定义：
extern CString g_sLangID_Native_CTPolarityDef;
extern CString g_sLangTxt_Native_CTPolarityDef;
//制动方程：
extern CString g_sLangID_Native_BrakeEquation;
extern CString g_sLangTxt_Native_BrakeEquation;
// 测试相：
extern CString g_sLangID_Native_TestPhase;
extern CString g_sLangTxt_Native_TestPhase;
// 测试精度：
extern CString g_sLangID_Native_TestAccuracy;
extern CString g_sLangTxt_Native_TestAccuracy;
//变压器接线形式：
extern CString g_sLangID_Native_TransConnType;
extern CString g_sLangTxt_Native_TransConnType;
//差动电流(A):
extern CString g_sLangID_Native_DiffCurrent;
extern CString g_sLangTxt_Native_DiffCurrent;
//制动电流(A):
extern CString g_sLangID_Native_BrakeCurrent;
extern CString g_sLangTxt_Native_BrakeCurrent;
//手动递变差流
extern CString g_sLangID_Native_ManualDiff;
extern CString g_sLangTxt_Native_ManualDiff;
//手动加+
extern CString g_sLangID_Native_ManualAdd;
extern CString g_sLangTxt_Native_ManualAdd;
//手动减-
extern CString g_sLangID_Native_ManualSub;
extern CString g_sLangTxt_Native_ManualSub;
//制动电流In:
extern CString g_sLangID_Native_BrakeCurrIn;
extern CString g_sLangTxt_Native_BrakeCurrIn;
//测试类型:
extern CString g_sLangID_Native_TestType;
extern CString g_sLangTxt_Native_TestType;
//测试精度In:
extern CString g_sLangID_Native_TestAccIn;
extern CString g_sLangTxt_Native_TestAccIn;
//搜索上限:
extern CString g_sLangID_Native_SearchUpperLimits;
extern CString g_sLangTxt_Native_SearchUpperLimits;
//搜索下限:
extern CString g_sLangID_Native_SearchLowerLimits;
extern CString g_sLangTxt_Native_SearchLowerLimits;
//差动电流Id:
extern CString g_sLangID_Native_DiffCurrentId;
extern CString g_sLangTxt_Native_DiffCurrentId;
//搜索始值(%):
extern CString g_sLangID_Native_SearchStartValue;
extern CString g_sLangTxt_Native_SearchStartValue;
//搜索终值(%):
extern CString g_sLangID_Native_SearchEndValue;
extern CString g_sLangTxt_Native_SearchEndValue;
//评估：
extern CString g_sLangID_Native_Evaluation;
extern CString g_sLangTxt_Native_Evaluation;
//表达式
extern CString g_sLangID_Native_Expression;
extern CString g_sLangTxt_Native_Expression;
//结果：
extern CString g_sLangID_Native_Result;
extern CString g_sLangTxt_Native_Result;
//差动电流
extern CString g_sLangID_Native_DiffCurrents;
extern CString g_sLangTxt_Native_DiffCurrents;
//误  差  (%)   <
extern CString g_sLangID_Native_ErrorLessThan;
extern CString g_sLangTxt_Native_ErrorLessThan;


// 相对误差(%)<
extern CString g_sLangID_Native_RelativeErrorLessThan;
extern CString g_sLangTxt_Native_RelativeErrorLessThan;
// 绝对误差<
extern CString g_sLangID_Native_AbsoluteErrorLessThan;
extern CString g_sLangTxt_Native_AbsoluteErrorLessThan;




//Harmtest 吕第三周
extern CString g_sLangID_Native_HarmonicTest;
extern CString g_sLangTxt_Native_HarmonicTest;//谐波试验
extern CString g_sLangID_Native_Wel_HarmModTest;
extern CString g_sLangTxt_Native_Wel_HarmModTest;//欢迎使用谐波模块试验
extern CString g_sLangID_Native_Choose_HtesttempFile;
extern CString g_sLangTxt_Native_Choose_HtesttempFile;//选择谐波试验模板文件
extern CString g_sLangID_Native_saveSuccess;
extern CString g_sLangTxt_Native_saveSuccess;//文件保存成功！
extern CString g_sLangID_Native_harmTestTempSaveS;
extern CString g_sLangTxt_Native_harmTestTempSaveS;// 谐波试验默认模板[%1]保存成功.
extern CString g_sLangID_Native_harmTestTempSaveF;
extern CString g_sLangTxt_Native_harmTestTempSaveF;// 谐波试验默认模板[%1]保存失败.
extern CString g_sLangID_Native_saveFail;
extern CString g_sLangTxt_Native_saveFail;  // 文件保存失败！
extern CString g_sLangID_Native_createMFileFail;
extern CString g_sLangTxt_Native_createMFileFail;  // 创建测试模板文件路径失败
extern CString g_sLangID_Native_saveAsSuccess;
extern CString g_sLangTxt_Native_saveAsSuccess;  // 模板另存为[%1]成功.
extern CString g_sLangID_Native_saveAsFail;
extern CString g_sLangTxt_Native_saveAsFail;  // 模板另存为[%1]失败.
extern CString g_sLangID_Native_testName_Harmonic;
extern CString g_sLangTxt_Native_testName_Harmonic;  // 试验名称：谐波

extern CString g_sLangID_Native_secondHarmonicAmp;
extern CString g_sLangTxt_Native_secondHarmonicAmp;  // 二次谐波幅值

extern CString g_sLangID_Native_contentRatio;
extern CString g_sLangTxt_Native_contentRatio;  // 含有率/%
extern CString g_sLangID_Native_rmsValueV;
extern CString g_sLangTxt_Native_rmsValueV;  // 有效值/V
extern CString g_sLangID_Native_rmsValueA;
extern CString g_sLangTxt_Native_rmsValueA;  // 有效值/A
extern CString g_sLangID_Native_phaseAngle;
extern CString g_sLangTxt_Native_phaseAngle;  // 相	位/°
extern CString g_sLangID_Native_totalRmsValue;
extern CString g_sLangTxt_Native_totalRmsValue;  // 总有效值
extern CString g_sLangID_Native_actionValueA;
extern CString g_sLangTxt_Native_actionValueA;  // 动作值(A)
extern CString g_sLangID_Native_InitofVar;
extern CString g_sLangTxt_Native_InitofVar;//变化始值(
extern CString g_sLangID_Native_FinalofVar;
extern CString g_sLangTxt_Native_FinalofVar;//变化终值(
extern CString g_sLangID_Native_StepofVar;
extern CString g_sLangTxt_Native_StepofVar;//变化步长(
extern CString g_sLangID_Native_channelAmp;
extern CString g_sLangTxt_Native_channelAmp;//通道幅值
extern CString g_sLangID_Native_groupNumber;
extern CString g_sLangTxt_Native_groupNumber; // 第%1组
extern CString g_sLangID_Native_harmonicLimitExceeded;
extern CString g_sLangTxt_Native_harmonicLimitExceeded;// 你总计只能选择31次谐波，假如想选择当前次谐波，需要取消勾选一行！
extern CString g_sLangID_Native_harmonicExceedsMax;
extern CString g_sLangTxt_Native_harmonicExceedsMax;// 选择的谐波次数大于最大值49次！
extern CString g_sLangID_Native_variaPointExceedsLimit;
extern CString g_sLangTxt_Native_variaPointExceedsLimit;   // 递变点数超过3000点，请重新输入！

//ui1
extern CString g_sLangID_Native_faultTimeMargin;
extern CString g_sLangTxt_Native_faultTimeMargin;   // 故障时间裕度(s):


//ui2
extern CString g_sLangID_Native_volDefinition;
extern CString g_sLangTxt_Native_volDefinition;// 电压定义:
extern CString g_sLangID_Native_referenceItem;
extern CString g_sLangTxt_Native_referenceItem;   // 参考项:
extern CString g_sLangID_Native_transConnection;
extern CString g_sLangTxt_Native_transConnection;   // 变压器接线方式:


//ui3

extern CString g_sLangID_Native_Freq_Deviation;
extern CString g_sLangTxt_Native_Freq_Deviation;//频率滑差df/dt(Hz/s):
extern CString g_sLangID_Native_initialFreq;
extern CString g_sLangTxt_Native_initialFreq;//频率起始值(Hz):
extern CString g_sLangID_Native_FreqChange_step;
extern CString g_sLangTxt_Native_FreqChange_step;//频率变化步长(Hz):
extern CString g_sLangID_Native_endFreq;
extern CString g_sLangTxt_Native_endFreq;//频率结束值(Hz):
extern CString g_sLangID_Native_finalFreq;
extern CString g_sLangTxt_Native_finalFreq;//频率变化终值(Hz):
extern CString g_sLangID_Native_initialFreq_deviation;
extern CString g_sLangTxt_Native_initialFreq_deviation;//频率滑差变化始值(Hz/s):
extern CString g_sLangID_Native_Freq_deviationstep;
extern CString g_sLangTxt_Native_Freq_deviationstep;//频率滑差变化步长(Hz/s):
extern CString g_sLangID_Native_finalFreq_deviation;
extern CString g_sLangTxt_Native_finalFreq_deviation;//频率滑差变化终值(Hz/s):
extern CString g_sLangID_Native_initialCur;
extern CString g_sLangTxt_Native_initialCur;//电流变化始值(A):
extern CString g_sLangID_Native_final_cur;
extern CString g_sLangTxt_Native_final_cur;//电流变化终值(A):
extern CString g_sLangID_Native_Curchange_step;
extern CString g_sLangTxt_Native_Curchange_step;//电流变化步长(A):
extern CString g_sLangID_Native_CurPhase_output;
extern CString g_sLangTxt_Native_CurPhase_output;//电流输出相：
extern CString g_sLangID_Native_initial_linevolchange;
extern CString g_sLangTxt_Native_initial_linevolchange;//线电压变化始值(V):
extern CString g_sLangID_Native_final_linevolchange;
extern CString g_sLangTxt_Native_final_linevolchange;//线电压变化终值(V):
extern CString g_sLangID_Native_linevol_changestep;
extern CString g_sLangTxt_Native_linevol_changestep;//线电压变化步长(V):
extern CString g_sLangID_Native_vol_change;
extern CString g_sLangTxt_Native_vol_change;//电压变化量：









//马嘉骅 第三周
//OverVoltInverseTime_Trans 马
/*tr("电压反时限试验模板文件")*/
extern CString g_sLangID_Native_VoltIDMTTestTemp;
extern CString g_sLangTxt_Native_VoltIDMTTestTemp;
/*tr("Ponovo电压反时限试验")*/
extern CString g_sLangID_Native_PonVoltIDMT;
extern CString g_sLangTxt_Native_PonVoltIDMT;
/*_T("欢迎使用电压反时限试验.")*/
extern CString g_sLangID_Native_WelVoltIDMT;
extern CString g_sLangTxt_Native_WelVoltIDMT;
/*tr("Ponovo 电压反时限试验")*/
extern CString g_sLangID_Native_PonBlaVoltIDMT;
extern CString g_sLangTxt_Native_PonBlaVoltIDMT;
/*tr("电压反时限试验")*/
extern CString g_sLangID_Native_VolReTiLimTe;
extern CString g_sLangTxt_Native_VolReTiLimTe;
/*"<h1>电压反时限</h1>"*/
extern CString g_sLangID_Native_VoltIDMT;
extern CString g_sLangTxt_Native_VoltIDMT;
/*"三相故障"*/
extern CString g_sLangID_Native_3PhFault;
extern CString g_sLangTxt_Native_3PhFaultT;
/*"零序电压"*/
extern CString g_sLangID_Native_ZeroSeqVolt;
extern CString g_sLangTxt_Native_ZeroSeqVolt;
/*"三相故障"*/
extern CString g_sLangID_Native_3PhFault;
extern CString g_sLangTxt_Native_3PhFault;
/*tr("始值-终值")*/
extern CString g_sLangID_Native_Start_End;
extern CString g_sLangTxt_Native_Start_End;
/*tr("始值-终值-始值")*/
extern CString g_sLangID_Native_Start_End_Start;
extern CString g_sLangTxt_Native_Start_End_Start;
//动作时间=%1s,
extern CString g_sLangID_Native_ActTimeSymSy;
extern CString g_sLangTxt_Native_ActTimeSymSy;
//故障前状态
extern CString g_sLangID_Native_PreFaultSt;
extern CString g_sLangTxt_Native_PreFaultSt;
//故障状态
extern CString g_sLangID_Native_FaultSt;
extern CString g_sLangTxt_Native_FaultSt;



//故障持续时间
extern CString g_sLangID_Native_FaultDur;
extern CString g_sLangTxt_Native_FaultDur;
//特性曲线
extern CString g_sLangID_Native_CharCurve;
extern CString g_sLangTxt_Native_CharCurve;
//相电压
extern CString g_sLangID_Native_PhVolt;
extern CString g_sLangTxt_Native_PhVolt;



//第四周许
//xwd 4
//速断电流=%1A
extern CString g_sLangID_Native_QuickBreakCurrent;
extern CString g_sLangTxt_Native_QuickBreakCurrent;
//速断电流=%1In
extern CString g_sLangID_Native_QuickBreakCurrentIn;
extern CString g_sLangTxt_Native_QuickBreakCurrentIn;
//中心点阻抗(Ω):
extern CString g_sLangID_Native_CenterPointImpedance;
extern CString g_sLangTxt_Native_CenterPointImpedance;
//中心点阻抗角(°):
extern CString g_sLangID_Native_CenterPointImpedanceAngle;
extern CString g_sLangTxt_Native_CenterPointImpedanceAngle;
//搜索半径(Ω):
extern CString g_sLangID_Native_SearchRadius;
extern CString g_sLangTxt_Native_SearchRadius;
//阻抗角始值(°):
extern CString g_sLangID_Native_ImpedanceAngleStartValue;
extern CString g_sLangTxt_Native_ImpedanceAngleStartValue;
//阻抗角终值(°):
extern CString g_sLangID_Native_ImpedanceAngleEndValue;
extern CString g_sLangTxt_Native_ImpedanceAngleEndValue;
//角度改变步长(°):
extern CString g_sLangID_Native_AngleChangeSteps;
extern CString g_sLangTxt_Native_AngleChangeSteps;
//阻抗改变步长(Ω):
extern CString g_sLangID_Native_ImpedanceChangeStep;
extern CString g_sLangTxt_Native_ImpedanceChangeStep;
//最大故障时间(s):
extern CString g_sLangID_Native_MaxFaultTimes;
extern CString g_sLangTxt_Native_MaxFaultTimes;
//末端阻抗(Ω)：
extern CString g_sLangID_Native_EndImpedance;
extern CString g_sLangTxt_Native_EndImpedance;
//末端阻抗角(°)：
extern CString g_sLangID_Native_EndImpAngle;
extern CString g_sLangTxt_Native_EndImpAngle;
//首端阻抗(Ω)：
extern CString g_sLangID_Native_StartImpedance;
extern CString g_sLangTxt_Native_StartImpedance;
//首端阻抗角(°)：
extern CString g_sLangID_Native_StartImpAngle;
extern CString g_sLangTxt_Native_StartImpAngle;
//阻抗步长(Ω)：
extern CString g_sLangID_Native_ImpStep;
extern CString g_sLangTxt_Native_ImpStep;






//丢帧测试
extern CString g_sLangID_Native_FrameDrop;
extern CString g_sLangTxt_Native_FrameDrop;
//飞点测试
extern CString g_sLangID_Native_FlyDot;
extern CString g_sLangTxt_Native_FlyDot;


//开入翻转参考状态：
extern CString g_sLangID_Native_RefState;
extern CString g_sLangTxt_Native_RefState;
//叠加衰减直流分量：
extern CString g_sLangID_Native_DcComp;
extern CString g_sLangTxt_Native_DcComp;
//衰减时间常数：
extern CString g_sLangID_Native_DecayTime;
extern CString g_sLangTxt_Native_DecayTime;
//循环次数：
extern CString g_sLangID_Native_LoopCount;
extern CString g_sLangTxt_Native_LoopCount;
//辅助直流设置(V)
extern CString g_sLangID_Native_AuxDCSet;
extern CString g_sLangTxt_Native_AuxDCSet;
//零序补偿系数：
extern CString g_sLangID_Native_ZeroSeqComp;
extern CString g_sLangTxt_Native_ZeroSeqComp;

//输出总时
extern CString g_sLangID_Native_OutTotalTime;
extern CString g_sLangTxt_Native_OutTotalTime;
//变位时刻(ms)
extern CString g_sLangID_Native_ShiftMoment;
extern CString g_sLangTxt_Native_ShiftMoment;
//闭合时间(ms)
extern CString g_sLangID_Native_CloseTimes;
extern CString g_sLangTxt_Native_CloseTimes;
//断开时间(ms)
extern CString g_sLangID_Native_BreakTime;
extern CString g_sLangTxt_Native_BreakTime;

//SOE测试
extern CString g_sLangID_Native_SOETest;
extern CString g_sLangTxt_Native_SOETest;
//保存配置
extern CString g_sLangID_Native_SaveConfig;
extern CString g_sLangTxt_Native_SaveConfig;
//保存目前配置参数
extern CString g_sLangID_Native_SaveCurrConfig;
extern CString g_sLangTxt_Native_SaveCurrConfig;
//开始时触发
extern CString g_sLangID_Native_StartTrigger;
extern CString g_sLangTxt_Native_StartTrigger;
//开始实验失败'
extern CString g_sLangID_Native_StartExpFail;
extern CString g_sLangTxt_Native_StartExpFail;
//实验停止失败
extern CString g_sLangID_Native_StopExpFail;
extern CString g_sLangTxt_Native_StopExpFail;

//常态开出设置
extern CString g_sLangID_Native_NormOutputSet;
extern CString g_sLangTxt_Native_NormOutputSet;
//故障态开出设置
extern CString g_sLangID_Native_FaultOutputSet;
extern CString g_sLangTxt_Native_FaultOutputSet;
//开入、开出量设置
extern CString g_sLangID_Native_IOSet;
extern CString g_sLangTxt_Native_IOSet;
//开入选择
extern CString g_sLangID_Native_InputSelect;
extern CString g_sLangTxt_Native_InputSelect;
//开出翻转启动方式
extern CString g_sLangID_Native_OutputFlipStart;
extern CString g_sLangTxt_Native_OutputFlipStart;
//开出保持时间(s)
extern CString g_sLangID_Native_OutputHoldTime;
extern CString g_sLangTxt_Native_OutputHoldTime;
//开出翻转时刻(s)
extern CString g_sLangID_Native_OutputFlipMoment;
extern CString g_sLangTxt_Native_OutputFlipMoment;
//单跳
extern CString g_sLangID_Native_SingleJump;
extern CString g_sLangTxt_Native_SingleJump;
//三跳
extern CString g_sLangID_Native_TripleJump;
extern CString g_sLangTxt_Native_TripleJump;
//重合
extern CString g_sLangID_Native_Reincidence;
extern CString g_sLangTxt_Native_Reincidence;
//时间启动
extern CString g_sLangID_Native_TimeStart;
extern CString g_sLangTxt_Native_TimeStart;
//开入量启动
extern CString g_sLangID_Native_InputStart;
extern CString g_sLangTxt_Native_InputStart;
//开入A-B-C-D
extern CString g_sLangID_Native_InputABCD;
extern CString g_sLangTxt_Native_InputABCD;
//开入E-F-G-H
extern CString g_sLangID_Native_InputEFGH;
extern CString g_sLangTxt_Native_InputEFGH;
//开出A-B-C-D
extern CString g_sLangID_Native_OutputABCD;
extern CString g_sLangTxt_Native_OutputABCD;
//开出E-F-G-H
extern CString g_sLangID_Native_OutputEFGH;
extern CString g_sLangTxt_Native_OutputEFGH;
//开入操作
extern CString g_sLangID_Native_InputOper;
extern CString g_sLangTxt_Native_InputOper;
//开出操作
extern CString g_sLangID_Native_OutputOper;
extern CString g_sLangTxt_Native_OutputOper;
//缺少跳闸或重合闸开入选择
extern CString g_sLangID_Native_InSel;
extern CString g_sLangTxt_Native_InSel;
//开入操作:
extern CString g_sLangID_Native_InputOpers;
extern CString g_sLangTxt_Native_InputOpers;
//开出操作;
extern CString g_sLangID_Native_OutputOpers;
extern CString g_sLangTxt_Native_OutputOpers;
//开出A
extern CString g_sLangID_Native_OutputA;
extern CString g_sLangTxt_Native_OutputA;
//开出B
extern CString g_sLangID_Native_OutputB;
extern CString g_sLangTxt_Native_OutputB;
//开出C
extern CString g_sLangID_Native_OutputC;
extern CString g_sLangTxt_Native_OutputC;
//开出D
extern CString g_sLangID_Native_OutputD;
extern CString g_sLangTxt_Native_OutputD;
//开出E
extern CString g_sLangID_Native_OutputE;
extern CString g_sLangTxt_Native_OutputE;
//开出F
extern CString g_sLangID_Native_OutputF;
extern CString g_sLangTxt_Native_OutputF;
//开出G
extern CString g_sLangID_Native_OutputG;
extern CString g_sLangTxt_Native_OutputG;
//开出H
extern CString g_sLangID_Native_OutputH;
extern CString g_sLangTxt_Native_OutputH;

//开出翻转时刻
extern CString g_sLangID_Native_OutputFlipMomentS;
extern CString g_sLangTxt_Native_OutputFlipMomentS;
//选择通道映射文件
extern CString g_sLangID_Native_SelMapFile;
extern CString g_sLangTxt_Native_SelMapFile;
//通道映射文件另存为
extern CString g_sLangID_Native_SaveMapFile;
extern CString g_sLangTxt_Native_SaveMapFile;
//导出通道映射文件[%s]成功.
extern CString g_sLangID_Native_ExpMapSucc;
extern CString g_sLangTxt_Native_ExpMapSucc;
//导出通道映射文件[%s]失败.
extern CString g_sLangID_Native_ExpMapFail;
extern CString g_sLangTxt_Native_ExpMapFail;
//通道映射密码
extern CString g_sLangID_Native_MapPass;
extern CString g_sLangTxt_Native_MapPass;
//密码:
extern CString g_sLangID_Native_Pass;
extern CString g_sLangTxt_Native_Pass;
//密码为空,请重新输入.
extern CString g_sLangID_Native_EmptyPass;
extern CString g_sLangTxt_Native_EmptyPass;
//密码错误,请重新输入.
extern CString g_sLangID_Native_WrongPass;
extern CString g_sLangTxt_Native_WrongPass;
//额定电压(V):
extern CString g_sLangID_Native_RatedVolt;
extern CString g_sLangTxt_Native_RatedVolt;
//额定电流(A):
extern CString g_sLangID_Native_RatedCurr;
extern CString g_sLangTxt_Native_RatedCurr;
//额定频率(Hz):
extern CString g_sLangID_Native_RatedFreq;
extern CString g_sLangTxt_Native_RatedFreq;
//防抖时间(ms):
extern CString g_sLangID_Native_DebTime;
extern CString g_sLangTxt_Native_DebTime;
//端口号:
extern CString g_sLangID_Native_PortNum;
extern CString g_sLangTxt_Native_PortNum;
//网络配置
extern CString g_sLangID_Native_NetConfig;
extern CString g_sLangTxt_Native_NetConfig;
//IP和端口号输入不合法
extern CString g_sLangID_Native_InvalidIPPort;
extern CString g_sLangTxt_Native_InvalidIPPort;
//总组数: 00
extern CString g_sLangID_Native_TotalGroups;
extern CString g_sLangTxt_Native_TotalGroups;
//总组数: %1
extern CString g_sLangID_Native_TotalGroupsParam;
extern CString g_sLangTxt_Native_TotalGroupsParam;
//当前组: %1
extern CString g_sLangID_Native_CurrentGroupParam;
extern CString g_sLangTxt_Native_CurrentGroupParam;
//  ←:上一组
extern CString g_sLangID_Native_PrevGroups;
extern CString g_sLangTxt_Native_PrevGroups;
//  →:下一组
extern CString g_sLangID_Native_NextGroups;
extern CString g_sLangTxt_Native_NextGroups;
//当前程序版本(%s).
extern CString g_sLangID_Native_CurrentVersionParam;
extern CString g_sLangTxt_Native_CurrentVersionParam;
//试验视图
extern CString g_sLangID_Native_TestView;
extern CString g_sLangTxt_Native_TestView;
//报告视图
extern CString g_sLangID_Native_ReportView;
extern CString g_sLangTxt_Native_ReportView;
//状态历史记录
extern CString g_sLangID_Native_StateHistory;
extern CString g_sLangTxt_Native_StateHistory;
//状态灯显示
extern CString g_sLangID_Native_StatusLight;
extern CString g_sLangTxt_Native_StatusLight;
//开始测试(F2)
extern CString g_sLangID_Native_StartTestF2;
extern CString g_sLangTxt_Native_StartTestF2;
//停止测试(Esc)
extern CString g_sLangID_Native_StopTestEsc;
extern CString g_sLangTxt_Native_StopTestEsc;
//打开模板文件
extern CString g_sLangID_Native_OpenTempFile;
extern CString g_sLangTxt_Native_OpenTempFile;
//保存模板文件
extern CString g_sLangID_Native_SaveTempFile;
extern CString g_sLangTxt_Native_SaveTempFile;
//型号参数配置
extern CString g_sLangID_Native_ModelParamConfig;
extern CString g_sLangTxt_Native_ModelParamConfig;
//通用参数设置对话框
extern CString g_sLangID_Native_GenParamSetDlg;
extern CString g_sLangTxt_Native_GenParamSetDlg;
//整定值参数设置对话框
extern CString g_sLangID_Native_SetValueParamSetDlg;
extern CString g_sLangTxt_Native_SetValueParamSetDlg;

//开关量设置对话框
extern CString g_sLangID_Native_SwitchValSetDlg;
extern CString g_sLangTxt_Native_SwitchValSetDlg;
//网络连接
extern CString g_sLangID_Native_NetConnect;
extern CString g_sLangTxt_Native_NetConnect;
//网络连接对话框
extern CString g_sLangID_Native_NetConnectDlg;
extern CString g_sLangTxt_Native_NetConnectDlg;
//通道资源映射对话框
extern CString g_sLangID_Native_ChResMapDlg;
extern CString g_sLangTxt_Native_ChResMapDlg;
//直流设置
extern CString g_sLangID_Native_DCSet;
extern CString g_sLangTxt_Native_DCSet;
//辅助直流设置对话框
extern CString g_sLangID_Native_AuxDCSetDlg;
extern CString g_sLangTxt_Native_AuxDCSetDlg;
//输出功率
extern CString g_sLangID_Native_OutputPower;
extern CString g_sLangTxt_Native_OutputPower;
//输出功率设置对话框
extern CString g_sLangID_Native_OutputPowerSetDlg;
extern CString g_sLangTxt_Native_OutputPowerSetDlg;
//稳态输出
extern CString g_sLangID_Native_SteadyOutput;
extern CString g_sLangTxt_Native_SteadyOutput;
//交直流稳态输出
extern CString g_sLangID_Native_ACDCSteadyOutput;
extern CString g_sLangTxt_Native_ACDCSteadyOutput;
//报告设置
extern CString g_sLangID_Native_ReportSet;
extern CString g_sLangTxt_Native_ReportSet;
//报告参数设置
extern CString g_sLangID_Native_ReportParamSet;
extern CString g_sLangTxt_Native_ReportParamSet;
//显示试验视图
extern CString g_sLangID_Native_ShowTestView;
extern CString g_sLangTxt_Native_ShowTestView;
//显示报告视图
extern CString g_sLangID_Native_ShowReportView;
extern CString g_sLangTxt_Native_ShowReportView;
//状态灯视图
extern CString g_sLangID_Native_StateLightView;
extern CString g_sLangTxt_Native_StateLightView;
//显示状态灯视图
extern CString g_sLangID_Native_ShowStateLightView;
extern CString g_sLangTxt_Native_ShowStateLightView;
//状态历史视图
extern CString g_sLangID_Native_StateHistoryView;
extern CString g_sLangTxt_Native_StateHistoryView;
//显示状态历史视图
extern CString g_sLangID_Native_ShowStateHistoryView;
extern CString g_sLangTxt_Native_ShowStateHistoryView;
//当前测试仪版本信息
extern CString g_sLangID_Native_CurrentTesterVersionInfo;
extern CString g_sLangTxt_Native_CurrentTesterVersionInfo;
//更新软件
extern CString g_sLangID_Native_UpdateSoftwares;
extern CString g_sLangTxt_Native_UpdateSoftwares;
//更新上位机软件
extern CString g_sLangID_Native_UpdateHostSoftware;
extern CString g_sLangTxt_Native_UpdateHostSoftware;
//更新底层
extern CString g_sLangID_Native_UpdateLowerLayer;
extern CString g_sLangTxt_Native_UpdateLowerLayer;
//更新测试仪底层程序
extern CString g_sLangID_Native_UpdateTesterLowerProgram;
extern CString g_sLangTxt_Native_UpdateTesterLowerProgram;
//报文探测
extern CString g_sLangID_Native_MessageDetection;
extern CString g_sLangTxt_Native_MessageDetection;
//报告
extern CString g_sLangID_Native_Report;
extern CString g_sLangTxt_Native_Report;
//开始
extern CString g_sLangID_Native_Start;
extern CString g_sLangTxt_Native_Start;
//系统参数配置对话框
extern CString g_sLangID_Native_SysParamConfigDialog;
extern CString g_sLangTxt_Native_SysParamConfigDialog;
//脱机选择
extern CString g_sLangID_Native_OfflineSelection;
extern CString g_sLangTxt_Native_OfflineSelection;
//脱机选择测试仪型号、SN
extern CString g_sLangID_Native_OfflineSelectTesterModelSN;
extern CString g_sLangTxt_Native_OfflineSelectTesterModelSN;
//1970年1月1日 00:00:00
extern CString g_sLangID_Native_Date1970;
extern CString g_sLangTxt_Native_Date1970;
//连接状态：
extern CString g_sLangID_Native_ConnectionStatus;
extern CString g_sLangTxt_Native_ConnectionStatus;
//对时
extern CString g_sLangID_Native_SyncTime;
extern CString g_sLangTxt_Native_SyncTime;
//文件[%1]保存成功.
extern CString g_sLangID_Native_FileSaveSuccess;
extern CString g_sLangTxt_Native_FileSaveSuccess;
//文件[%1]保存失败.
extern CString g_sLangID_Native_FileSaveFail;
extern CString g_sLangTxt_Native_FileSaveFail;
//默认参数文件[%1]保存成功.
extern CString g_sLangID_Native_DefParamFileSaveSuccess;
extern CString g_sLangTxt_Native_DefParamFileSaveSuccess;
//默认参数文件[%1]保存失败.
extern CString g_sLangID_Native_DefParamFileSaveFail;
extern CString g_sLangTxt_Native_DefParamFileSaveFail;
//谐波含量超约定值
extern CString g_sLangID_Native_HarmonicExceedValue;
extern CString g_sLangTxt_Native_HarmonicExceedValue;
//输出最大值超设计
extern CString g_sLangID_Native_OutputMaxExceedDesign;
extern CString g_sLangTxt_Native_OutputMaxExceedDesign;
//，请重新修改谐波含量的值！
extern CString g_sLangID_Native_ReModifyHarmonicValue;
extern CString g_sLangTxt_Native_ReModifyHarmonicValue;
//当前已经是最后一个测试下,无法继续测试.
extern CString g_sLangID_Native_LastTestCannotContinue;
extern CString g_sLangTxt_Native_LastTestCannotContinue;
//系统参数设置下发完成
extern CString g_sLangID_Native_SystemParamSetComplete;
extern CString g_sLangTxt_Native_SystemParamSetComplete;
//系统参数设置下发失败
extern CString g_sLangID_Native_SystemParamSetFailed;
extern CString g_sLangTxt_Native_SystemParamSetFailed;
//测试停止
extern CString g_sLangID_Native_TestStopped;
extern CString g_sLangTxt_Native_TestStopped;
//停止命令下发失败
extern CString g_sLangID_Native_StopCommandFailed;
extern CString g_sLangTxt_Native_StopCommandFailed;
//联机失败,无法下发系统参数.
extern CString g_sLangID_Native_ConnectionFailed;
extern CString g_sLangTxt_Native_ConnectionFailed;
//模块档位切换命令下发完成
extern CString g_sLangID_Native_ModuleSwitchDone;
extern CString g_sLangTxt_Native_ModuleSwitchDone;
//模块档位切换命令下发失败
extern CString g_sLangID_Native_ModuleSwitchFail;
extern CString g_sLangTxt_Native_ModuleSwitchFail;
//辅助直流输出命令下发完成
extern CString g_sLangID_Native_AuxDCOutDone;
extern CString g_sLangTxt_Native_AuxDCOutDone;
//辅助直流输出命令下发失败
extern CString g_sLangID_Native_AuxDCOutFail;
extern CString g_sLangTxt_Native_AuxDCOutFail;
//开始稳态量输出
extern CString g_sLangID_Native_StartSteadyOut;
extern CString g_sLangTxt_Native_StartSteadyOut;
//停止稳态量输出
extern CString g_sLangID_Native_StopSteadyOut;
extern CString g_sLangTxt_Native_StopSteadyOut;

//停止SOE测试输出
extern CString g_sLangID_Native_StopSOETest;
extern CString g_sLangTxt_Native_StopSOETest;
//导出word文件
extern CString g_sLangID_Native_ExportWord;
extern CString g_sLangTxt_Native_ExportWord;
//Word97-2003报告(*.doc);;Word报告(*.docx);;HTML报告(*.html);;PDF报告(*.pdf)
extern CString g_sLangID_Native_ReportTypes;
extern CString g_sLangTxt_Native_ReportTypes;
//网页报告(%s)保存成功.
extern CString g_sLangID_Native_SaveReportSuccess;
extern CString g_sLangTxt_Native_SaveReportSuccess;
//PDF报告文件(%s)保存成功.
extern CString g_sLangID_Native_SavePDFSuccess;
extern CString g_sLangTxt_Native_SavePDFSuccess;
//PDF报告文件(%s)保存失败.
extern CString g_sLangID_Native_SavePDFFailure;
extern CString g_sLangTxt_Native_SavePDFFailure;
//WORD报告文件(%s)保存成功.
extern CString g_sLangID_Native_SaveWordSuccess;
extern CString g_sLangTxt_Native_SaveWordSuccess;
//WORD报告文件(%s)保存失败.
extern CString g_sLangID_Native_SaveWordFailure;
extern CString g_sLangTxt_Native_SaveWordFailure;
//正在运行中,是否停止测试?
extern CString g_sLangID_Native_TestRunning;
extern CString g_sLangTxt_Native_TestRunning;
//测试模板未保存,是否保存?
extern CString g_sLangID_Native_UnsavedTemplate;
extern CString g_sLangTxt_Native_UnsavedTemplate;
//删除全部
extern CString g_sLangID_Native_DeleteAll;
extern CString g_sLangTxt_Native_DeleteAll;
//变量名称
extern CString g_sLangID_Native_VarName;
extern CString g_sLangTxt_Native_VarName;

//第四周吕
//ui4
extern CString g_sLangID_Native_voltagev;
extern CString g_sLangTxt_Native_voltagev; // 电压（V）：
extern CString g_sLangID_Native_currentc;
extern CString g_sLangTxt_Native_currentc; // 电流(A):
extern CString g_sLangID_Native_phasep;
extern CString g_sLangTxt_Native_phasep; // 相位差(°):
extern CString g_sLangID_Native_initialCurrent;
extern CString g_sLangTxt_Native_initialCurrent; // 电流变化始值(I*):
extern CString g_sLangID_Native_finalCurrent;
extern CString g_sLangTxt_Native_finalCurrent; // 电流变化终值(I*):
extern CString g_sLangID_Native_CurstepSize;
extern CString g_sLangTxt_Native_CurstepSize; // 电流变化步长(I*):
extern CString g_sLangID_Native_currentcI;
extern CString g_sLangTxt_Native_currentcI; // 电流(I*):
extern CString g_sLangID_Native_referenceValue;
extern CString g_sLangTxt_Native_referenceValue; // 基准值:
extern CString g_sLangID_Native_ctPolarityDef;
extern CString g_sLangTxt_Native_ctPolarityDef; // CT正极性定义:
extern CString g_sLangID_Native_charaDef;
extern CString g_sLangTxt_Native_charaDef; // 特性定义
extern CString g_sLangID_Native_timerLimit1;
extern CString g_sLangTxt_Native_timerLimit1; // 1段定时限:
extern CString g_sLangID_Native_timerLimit2;
extern CString g_sLangTxt_Native_timerLimit2; // 2段定时限:
extern CString g_sLangID_Native_timerLimit3;
extern CString g_sLangTxt_Native_timerLimit3; // 3段定时限:

//ui5
extern CString g_sLangID_Native_singleP;
extern CString g_sLangTxt_Native_singleP; // 单相
extern CString g_sLangID_Native_impedanceSelection;
extern CString g_sLangTxt_Native_impedanceSelection; // 阻抗选择:
extern CString g_sLangID_Native_times;
extern CString g_sLangTxt_Native_times; // 倍
extern CString g_sLangID_Native_impedanceRepresent;
extern CString g_sLangTxt_Native_impedanceRepresent; // 阻抗表示方式:
extern CString g_sLangID_Native_timeConstant;
extern CString g_sLangTxt_Native_timeConstant; // 时间定值(s):
extern CString g_sLangID_Native_triggerTiming;
extern CString g_sLangTxt_Native_triggerTiming; // 触发时刻:
extern CString g_sLangID_Native_h;
extern CString g_sLangTxt_Native_h; //时
extern CString g_sLangID_Native_m;
extern CString g_sLangTxt_Native_m; //分
extern CString g_sLangID_Native_s;
extern CString g_sLangTxt_Native_s; //秒


//ui6
extern CString g_sLangID_Native_PreChangeVol;
extern CString g_sLangTxt_Native_PreChangeVol; // 变化前电压(V):
extern CString g_sLangID_Native_PreChangeCur;
extern CString g_sLangTxt_Native_PreChangeCur; //变化前电流(A)：
extern CString g_sLangID_Native_PreChangeFreq;
extern CString g_sLangTxt_Native_PreChangeFreq;//变化前频率(HZ)：
extern CString g_sLangID_Native_variableType;
extern CString g_sLangTxt_Native_variableType; // 变量类型:
extern CString g_sLangID_Native_variable0;
extern CString g_sLangTxt_Native_variable0; // 变量:
extern CString g_sLangID_Native_directChange;
extern CString g_sLangTxt_Native_directChange; // 递变方向：

extern CString g_sLangID_Native_currentG1;
extern CString g_sLangTxt_Native_currentG1; // 电流(G1)(A)：
extern CString g_sLangID_Native_currentG2;
extern CString g_sLangTxt_Native_currentG2; // 电流(G2)(A)：
extern CString g_sLangID_Native_voltageG1;
extern CString g_sLangTxt_Native_voltageG1; // 电压(G1)(V)：
extern CString g_sLangID_Native_voltageG2;
extern CString g_sLangTxt_Native_voltageG2; // 电压(G2)(V)：
extern CString g_sLangID_Native_currentDif;
extern CString g_sLangTxt_Native_currentDif; // 电流相差(G1,G2)(°):

extern CString g_sLangID_Native_normalState;
extern CString g_sLangTxt_Native_normalState; // 常态:
extern CString g_sLangID_Native_faultState;
extern CString g_sLangTxt_Native_faultState; // 故障态:

extern CString g_sLangID_Native_relativeErrorl;
extern CString g_sLangTxt_Native_relativeErrorl; //相对误差<
extern CString g_sLangID_Native_returnCoefficientb;
extern CString g_sLangTxt_Native_returnCoefficientb; //返回系数>
extern CString g_sLangID_Native_judgmentCondition;
extern CString g_sLangTxt_Native_judgmentCondition; // 判定条件
extern CString g_sLangID_Native_express;
extern CString g_sLangTxt_Native_express; // 表达式：

//ui7
extern CString g_sLangID_Native_clear0;
extern CString g_sLangTxt_Native_clear0; // 清零
extern CString g_sLangID_Native_changeSettings;
extern CString g_sLangTxt_Native_changeSettings; // 变化设置:
extern CString g_sLangID_Native_changeTime;
extern CString g_sLangTxt_Native_changeTime; // 变化时间(s):
extern CString g_sLangID_Native_baseFrequency;
extern CString g_sLangTxt_Native_baseFrequency; // 基波频率(Hz):
extern CString g_sLangID_Native_openSettings;
extern CString g_sLangTxt_Native_openSettings; // 开出设置:
extern CString g_sLangID_Native_harmDataBatchSet;
extern CString g_sLangTxt_Native_harmDataBatchSet; // 谐波数据批量设置:
extern CString g_sLangID_Native_channelContain;
extern CString g_sLangTxt_Native_channelContain; // 通道含有率(%):
extern CString g_sLangID_Native_channelPhase;
extern CString g_sLangTxt_Native_channelPhase; // 通道相位(°):

//goose
extern CString g_sLangID_Native_forceNumberOutput;
extern CString g_sLangTxt_Native_forceNumberOutput; //当前模块需要支持数字量输出功能,强制设置为数字量输出模式.
extern CString g_sLangID_Native_notSupportNumOutput;
extern CString g_sLangTxt_Native_notSupportNumOutput; //当前测试仪不支持数字量输出功能,无法使用GOOSE异常模拟试验.
extern CString g_sLangID_Native_PonovogooseSim;
extern CString g_sLangTxt_Native_PonovogooseSim; //Ponovo GOOSE异常模拟
extern CString g_sLangID_Native_welgooseSim;
extern CString g_sLangTxt_Native_welgooseSim; //欢迎使用GOOSE异常模拟试验.
extern CString g_sLangID_Native_JumpA;
extern CString g_sLangTxt_Native_JumpA; //跳A
extern CString g_sLangID_Native_JumpB;
extern CString g_sLangTxt_Native_JumpB; //跳B
extern CString g_sLangID_Native_JumpC;
extern CString g_sLangTxt_Native_JumpC; //跳C
extern CString g_sLangID_Native_JumpD;
extern CString g_sLangTxt_Native_JumpD; //跳D
extern CString g_sLangID_Native_JumpE;
extern CString g_sLangTxt_Native_JumpE; //跳E
extern CString g_sLangID_Native_JumpF;
extern CString g_sLangTxt_Native_JumpF; //跳F
extern CString g_sLangID_Native_JumpG;
extern CString g_sLangTxt_Native_JumpG; //跳G
extern CString g_sLangID_Native_JumpH;
extern CString g_sLangTxt_Native_JumpH; //跳H
extern CString g_sLangID_Native_JumpI;
extern CString g_sLangTxt_Native_JumpI; //跳I
extern CString g_sLangID_Native_JumpJ;
extern CString g_sLangTxt_Native_JumpJ; //跳J
extern CString g_sLangID_Native_STSS1234;
extern CString g_sLangTxt_Native_STSS1234;//状态%1,输出时间=%2,StNum=%3,SqNum=%4

//channelParaset
extern CString g_sLangID_Native_amplitudeV;
extern CString g_sLangTxt_Native_amplitudeV;  // 幅值(V)
extern CString g_sLangID_Native_amplitudeKV;
extern CString g_sLangTxt_Native_amplitudeKV;  // 幅值(KV)
extern CString g_sLangID_Native_amplitudeA;
extern CString g_sLangTxt_Native_amplitudeA;  // 幅值(A)
extern CString g_sLangID_Native_overflowV;
extern CString g_sLangTxt_Native_overflowV;  // 谐波设置值%f(%d,%d)与基波的叠加超出范围(%fV).
extern CString g_sLangID_Native_overflowA;
extern CString g_sLangTxt_Native_overflowA;  // 谐波设置值%f(%d,%d)与基波的叠加超出范围(%fA).
extern CString g_sLangID_Native_input_overrange;
extern CString g_sLangTxt_Native_input_overrange;  // 输入值%f(%d,%d)超出范围(%f).
extern CString g_sLangID_Native_flowoverV;
extern CString g_sLangTxt_Native_flowoverV;//基波设置值%f(%d,%d)与谐波的叠加超出范围(%fV).
extern CString g_sLangID_Native_flowoverA;
extern CString g_sLangTxt_Native_flowoverA;//基波设置值%f(%d,%d)与谐波的叠加超出范围(%fA).
extern CString g_sLangID_Native_all_frequencies;
extern CString g_sLangTxt_Native_all_frequencies;  // 等全部频率
extern CString g_sLangID_Native_smallsignal;
extern CString g_sLangTxt_Native_smallsignal;  // 小信号
extern CString g_sLangID_Native_illchannelname;
extern CString g_sLangTxt_Native_illchannelname;  // 递变通道名【%s】非法



//第四周马
//DifferTest_Trans 马
/*tr("差动试验模板文件")*/
extern CString g_sLangID_Native_DifTestTempFile;
extern CString g_sLangTxt_Native_DifTestTempFile;
/*_T("欢迎使用差动测试.")*/
extern CString g_sLangID_Native_WelToDiffTest;
extern CString g_sLangTxt_Native_WelToDiffTest;
/*tr("Ponovo 差动")*/
extern CString g_sLangID_Native_PonovoDiff;
extern CString g_sLangTxt_Native_PonovoDiff;
/*tr("差动")*/
extern CString g_sLangID_Native_Differential;
extern CString g_sLangTxt_Native_Differential;
/*tr("特征曲线图")*/
extern CString g_sLangID_Native_CurveGraph;
extern CString g_sLangTxt_Native_CurveGraph;
/*tr("接线图")*/
extern CString g_sLangID_Native_WireDiagram;
extern CString g_sLangTxt_Native_WireDiagram;
/*tr("没有选择目标删除项!")*/
extern CString g_sLangID_Native_NoTgtDelItem;
extern CString g_sLangTxt_Native_NoTgtDelItem;
/*tr("此测试类型至少保留一个测试项！")*/
extern CString g_sLangID_Native_AtLeast1Test;
extern CString g_sLangTxt_Native_AtLeast1Test;
/*_T("联机失败[%s][%ld].")*/
extern CString g_sLangID_Native_OnlineFailSy;
extern CString g_sLangTxt_Native_OnlineFailSy;
/*tr("通道映射文件下发完成")*/
extern CString g_sLangID_Native_ChnlMapFileDone;
extern CString g_sLangTxt_Native_ChnlMapFileDone;
/*tr("通道映射文件下发失败")*/
extern CString g_sLangID_Native_ChMapFileErr;
extern CString g_sLangTxt_Native_ChMapFileErr;
/*tr("系统参数设置下发完成")*/
extern CString g_sLangID_Native_SysParamSetDone;
extern CString g_sLangTxt_Native_SysParamSetDone;
/*tr("系统参数设置下发失败")*/
extern CString g_sLangID_Native_SysParamErr;
extern CString g_sLangTxt_Native_SysParamErr;
/*tr("IEC参数设置下发完成")*/
extern CString g_sLangID_Native_IECParamSetDone;
extern CString g_sLangTxt_Native_IECParamSetDone;
/*tr("IEC参数设置执行超时")*/
extern CString g_sLangID_Native_IECParamTimeout;
extern CString g_sLangTxt_Native_IECParamTimeout;
/*tr("IEC参数设置执行失败")*/
extern CString g_sLangID_Native_IECParamFail;
extern CString g_sLangTxt_Native_IECParamFail;
/*tr("开始测试.")*/
extern CString g_sLangID_Native_StartTestSy;
extern CString g_sLangTxt_Native_StartTestSy;
/*tr("开始测试命令下发失败.")*/
extern CString g_sLangID_Native_StartTestCmdFail;
extern CString g_sLangTxt_Native_StartTestCmdFail;
/*tr("没有选择测试项.")*/
extern CString g_sLangID_Native_NoTestItemSy;
extern CString g_sLangTxt_Native_NoTestItemSy;
/*tr("在Id-Ir平面上双击鼠标，设置测试项的制动电流值")*/
extern CString g_sLangID_Native_SetTestItemCurrent;
extern CString g_sLangTxt_Native_SetTestItemCurrent;

/*_T("基准电流(其它)")*/
extern CString g_sLangID_Native_RefCurrentOther;
extern CString g_sLangTxt_Native_RefCurrentOther;
/*_T("差动速断电流定值")*/
extern CString g_sLangID_Native_DfRelayCurrSet;
extern CString g_sLangTxt_Native_DfRelayCurrSet;
/*_T("差动动作电流门槛值")*/
extern CString g_sLangID_Native_DfActThresh;
extern CString g_sLangTxt_Native_DfActThresh;
/*_T("比率制动特性拐点数")*/
extern CString g_sLangID_Native_RatioBrkPntCnt;
extern CString g_sLangTxt_Native_RatioBrkPntCnt;
/*_T("比率制动特性拐点1电流")*/
extern CString g_sLangID_Native_RatioBrkPt1Curr;
extern CString g_sLangTxt_Native_RatioBrkPt1Curr;
/*_T("比率制动特性拐点2电流")*/
extern CString g_sLangID_Native_RatioBrkPt2Curr;
extern CString g_sLangTxt_Native_RatioBrkPt2Curr;
/*_T("比率制动特性拐点3电流")*/
extern CString g_sLangID_Native_RatioBrkPt3Curr;
extern CString g_sLangTxt_Native_RatioBrkPt3Curr;

/*_T("差动电流值(%f),超越上限")*/
extern CString g_sLangID_Native_DiffCurrExceedsLimit;
extern CString g_sLangTxt_Native_DiffCurrExceedsLimit;
/*tr("参数更新成功.")*/
extern CString g_sLangID_Native_ParamsUpdated;
extern CString g_sLangTxt_Native_ParamsUpdated;
/*tr("参数更新失败.")*/
extern CString g_sLangID_Native_ParamsUpdateFailed;
extern CString g_sLangTxt_Native_ParamsUpdateFailed;
/*_T("差动电流值已降低为0,无法再减小")*/
extern CString g_sLangID_Native_DiffCurrReducedToZero;
extern CString g_sLangTxt_Native_DiffCurrReducedToZero;
/*QObject::tr("比率制动系数一")*/
extern CString g_sLangID_Native_RatioBrkCoef1;
extern CString g_sLangTxt_Native_RatioBrkCoef1;
/*QObject::tr("比率制动系数二")*/
extern CString g_sLangID_Native_RatioBrkCoef2;
extern CString g_sLangTxt_Native_RatioBrkCoef2;
/*QObject::tr("比率制动系数三")*/
extern CString g_sLangID_Native_RatioBrkCoef3;
extern CString g_sLangTxt_Native_RatioBrkCoef3;


/*_T("手动计算输入平衡系数方式时如果整定值选择标幺值，则基准电流不可选择高侧二次额定电流.")*/
extern CString g_sLangID_Native_ManInBalCoeffNoHi;
extern CString g_sLangTxt_Native_ManInBalCoeffNoHi;
/*_T("手动计算输入平衡系数方式时如果整定值选择标幺值，则基准电流不可选择各侧二次额定电流.")*/
extern CString g_sLangID_Native_ManInBalCoeffNoBe;
extern CString g_sLangTxt_Native_ManInBalCoeffNoBe;
/*"差流理论值"*/
extern CString g_sLangID_Native_DiffCurrentTheory;
extern CString g_sLangTxt_Native_DiffCurrentTheory;
/*"<h1>差动6I</h1>"*/
extern CString g_sLangID_Native_Diff6I;
extern CString g_sLangTxt_Native_Diff6I;
/*"<h2>测试结果</h2>"*/
extern CString g_sLangID_Native_TestResultSy;
extern CString g_sLangTxt_Native_TestResultSy;
/*"未知类别"*/
extern CString g_sLangID_Native_UnkCat;
extern CString g_sLangTxt_Native_UnkCat;
/*"自动计算"*/
extern CString g_sLangID_Native_AutoCalc;
extern CString g_sLangTxt_Native_AutoCalc;
/*"手动计算并输入"*/
extern CString g_sLangID_Native_ManCalcInput;
extern CString g_sLangTxt_Native_ManCalcInput;
/*"高-低"*/
extern CString g_sLangID_Native_HighLow;
extern CString g_sLangTxt_Native_HighLow;
/*"高-中"*/
extern CString g_sLangID_Native_HighMid;
extern CString g_sLangTxt_Native_HighMid;
/*"中-低"*/
extern CString g_sLangID_Native_MidLow;
extern CString g_sLangTxt_Native_MidLow;
/*"二分法"*/
extern CString g_sLangID_Native_BinSearch;
extern CString g_sLangTxt_Native_BinSearch;
/*"单步逼近"*/
extern CString g_sLangID_Native_StepApprox;
extern CString g_sLangTxt_Native_StepApprox;
/*"有名值"*/
extern CString g_sLangID_Native_NameValue;
extern CString g_sLangTxt_Native_NameValue;
/*"标幺值"*/
extern CString g_sLangID_Native_PerUnitVal;
extern CString g_sLangTxt_Native_PerUnitVal;
/*"高侧二次额定电流"*/
extern CString g_sLangID_Native_HighSideSecRatedCurr;
extern CString g_sLangTxt_Native_HighSideSecRatedCurr;
/*"各侧二次额定电流"*/
extern CString g_sLangID_Native_BeSideSecRatedCurr;
extern CString g_sLangTxt_Native_BeSideSecRatedCurr;
/*"设定值"*/
extern CString g_sLangID_Native_Setpt;
extern CString g_sLangTxt_Native_Setpt;
/*"一个拐点"*/
extern CString g_sLangID_Native_OneTurnPoint;
extern CString g_sLangTxt_Native_OneTurnPoint;
/*"二个拐点"*/
extern CString g_sLangID_Native_TwoTurnPoint;
extern CString g_sLangTxt_Native_TwoTurnPoint;
/*"三个拐点"*/
extern CString g_sLangID_Native_ThreeTurnPoint;
extern CString g_sLangTxt_Native_ThreeTurnPoint;
/*tr("变化始值(In):")*/
extern CString g_sLangID_Native_InitValChange;
extern CString g_sLangTxt_Native_InitValChange;
/*tr("变化终值(In):")*/
extern CString g_sLangID_Native_EndValChange;
extern CString g_sLangTxt_Native_EndValChange;
/*tr("变化步长(In):")*/
extern CString g_sLangID_Native_ChgStep;
extern CString g_sLangTxt_Native_ChgStep;
/*tr("Ⅰ侧平衡系数")*/
extern CString g_sLangID_Native_SglSideBalCoeff;
extern CString g_sLangTxt_Native_SglSideBalCoeff;
/*tr("Ⅱ侧平衡系数")*/
extern CString g_sLangID_Native_TwoSideBalCoeff;
extern CString g_sLangTxt_Native_TwoSideBalCoeff;
/*tr("Ⅲ侧平衡系数")*/
extern CString g_sLangID_Native_ThreeSideBalCoeff;
extern CString g_sLangTxt_Native_ThreeSideBalCoeff;
/*tr("接线系数")*/
extern CString g_sLangID_Native_WiringCoeff;
extern CString g_sLangTxt_Native_WiringCoeff;
/*tr("基准电流")*/
extern CString g_sLangID_Native_RefCurr;
extern CString g_sLangTxt_Native_RefCurr;
/*tr("   高压侧   ")*/
extern CString g_sLangID_Native_HighVoltSide;
extern CString g_sLangTxt_Native_HighVoltSide;
/*tr("   中压侧   ")*/
extern CString g_sLangID_Native_MedVoltSide;
extern CString g_sLangTxt_Native_MedVoltSide;
/*tr("   低压侧   ")*/
extern CString g_sLangID_Native_LowVoltSide;
extern CString g_sLangTxt_Native_LowVoltSide;
/*tr("差动保护电流端子")*/
extern CString g_sLangID_Native_DiffProtCurrTerm;
extern CString g_sLangTxt_Native_DiffProtCurrTerm;
/*tr("继电保护测试仪")*/
extern CString g_sLangID_Native_RelayTest;
extern CString g_sLangTxt_Native_RelayTest;
/*tr("制动电流=%1A,")*/
extern CString g_sLangID_Native_BrakeCurrSy;
extern CString g_sLangTxt_Native_BrakeCurrSy;
/*tr("差动电流=%1A,")*/
extern CString g_sLangID_Native_DiffCurrSy;
extern CString g_sLangTxt_Native_DiffCurrSy;
/*tr("比例制动系数=%1")*/
extern CString g_sLangID_Native_PropBrakeCoeffSy;
extern CString g_sLangTxt_Native_PropBrakeCoeffSy;
/*tr("制动电流=%1In,")*/
extern CString g_sLangID_Native_BrakeCurrSyy;
extern CString g_sLangTxt_Native_BrakeCurrSyy;
/*tr("差动电流=%1In,")*/
extern CString g_sLangID_Native_DiffCurrSyy;
extern CString g_sLangTxt_Native_DiffCurrSyy;
/*tr("测试过程监视图")*/
extern CString g_sLangID_Native_TestProcMonView;
extern CString g_sLangTxt_Native_TestProcMonView;
/*tr("矢量图")*/
extern CString g_sLangID_Native_VecGraphics;
extern CString g_sLangTxt_Native_VecGraphics;
 /*tr("线电压")*/
extern CString g_sLangID_Native_LineVolt;
extern CString g_sLangTxt_Native_LineVolt;
/*tr("信息图")*/
extern CString g_sLangID_Native_InfoChart;
extern CString g_sLangTxt_Native_InfoChart;
/*tr("功率图")*/
extern CString g_sLangID_Native_PowerChart;
extern CString g_sLangTxt_Native_PowerChart;
/*tr("动作特性曲线")*/
extern CString g_sLangID_Native_CharactCurve;
extern CString g_sLangTxt_Native_CharactCurve;
/*tr("搜索上限(A)")*/
extern CString g_sLangID_Native_SearchUpperLimit;
extern CString g_sLangTxt_Native_SearchUpperLimit;
/*tr("搜索下限(A)")*/
extern CString g_sLangID_Native_SearchLowerLimit;
extern CString g_sLangTxt_Native_SearchLowerLimit;
/*tr("请输入有效数字！")*/
extern CString g_sLangID_Native_EnterValidNumber;
extern CString g_sLangTxt_Native_EnterValidNumber;
/*_T("输入制动电流值[%f]不在有效范围.")*/
extern CString g_sLangID_Native_InputBrakeCurrOutOfRange;
extern CString g_sLangTxt_Native_InputBrakeCurrOutOfRange;
/*tr("准备时间(S)")*/
extern CString g_sLangID_Native_PrepTime;
extern CString g_sLangTxt_Native_PrepTime;

/*tr("各侧平衡系数")*/
extern CString g_sLangID_Native_BalanceCoeffEachSide;
extern CString g_sLangTxt_Native_BalanceCoeffEachSide;

/*tr("测试绕组")*/
extern CString g_sLangID_Native_TestWinding;
extern CString g_sLangTxt_Native_TestWinding;




/*tr("高压侧差动平衡系数")*/
extern CString g_sLangID_Native_HVSDiffBalCoeff;
extern CString g_sLangTxt_Native_HVSDiffBalCoeff;
/*tr("中压侧差动平衡系数")*/
extern CString g_sLangID_Native_MVSDiffBalCoeff;
extern CString g_sLangTxt_Native_MVSDiffBalCoeff;
/*tr("低压侧差动平衡系数")*/
extern CString g_sLangID_Native_LVSDiffBalCoeff;
extern CString g_sLangTxt_Native_LVSDiffBalCoeff;
//插入系列
extern CString g_sLangID_Native_InsSeries;
extern CString g_sLangTxt_Native_InsSeries;
//试验结果及评估
extern CString g_sLangID_Native_TestResEval;
extern CString g_sLangTxt_Native_TestResEval;
//误  差
extern CString g_sLangID_Native_ErrBlank;
extern CString g_sLangTxt_Native_ErrBlank;
//制  动  电  流
extern CString g_sLangID_Native_BrkCurrBlank;
extern CString g_sLangTxt_Native_BrkCurrBlank;






//第五周许
//xwd 5
//制动电流(In)
extern CString g_sLangID_Native_BrakingCurrent;
extern CString g_sLangTxt_Native_BrakingCurrent;
//搜索上限(In)
extern CString g_sLangID_Native_SearchUpper;
extern CString g_sLangTxt_Native_SearchUpper;
//搜索下限(In)
extern CString g_sLangID_Native_SearchLower;
extern CString g_sLangTxt_Native_SearchLower;
//测试精度(A)
extern CString g_sLangID_Native_TestPrecisionA;
extern CString g_sLangTxt_Native_TestPrecisionA;
//测试精度(In)
extern CString g_sLangID_Native_TestPrecisionIn;
extern CString g_sLangTxt_Native_TestPrecisionIn;
//启动电流(A)
extern CString g_sLangID_Native_StartCurrent;
extern CString g_sLangTxt_Native_StartCurrent;
//启动电流(In)
extern CString g_sLangID_Native_StartCurrentIn;
extern CString g_sLangTxt_Native_StartCurrentIn;
//差动电流(In)
extern CString g_sLangID_Native_DiffCurrentIn;
extern CString g_sLangTxt_Native_DiffCurrentIn;
//速断电流(A)
extern CString g_sLangID_Native_BrkCur;
extern CString g_sLangTxt_Native_BrkCur;
//速断电流(In)
extern CString g_sLangID_Native_BrkCurIn;
extern CString g_sLangTxt_Native_BrkCurIn;
//搜索上限(A)
extern CString g_sLangID_Native_SrchUpLimA;
extern CString g_sLangTxt_Native_SrchUpLimA;
//搜索下限(A)

extern CString g_sLangID_Native_SrchLowLimA;
extern CString g_sLangTxt_Native_SrchLowLimA;
//请输入有效数字！
extern CString g_sLangID_Native_ValidNum;
extern CString g_sLangTxt_Native_ValidNum;



//第五周吕
//exswitchset
extern CString g_sLangID_Native_BinEx20;
extern CString g_sLangTxt_Native_BinEx20;  // 扩展开入量_20

//OffLineDlg
extern CString g_sLangID_Native_TestModelTypeSelect;
extern CString g_sLangTxt_Native_TestModelTypeSelect;  //测试仪型号类型选择

//daSetdlg
extern CString g_sLangID_Native_tester_type;
extern CString g_sLangTxt_Native_tester_type;  // 测试仪类型
extern CString g_sLangID_Native_digital_signal;
extern CString g_sLangTxt_Native_digital_signal;  // 数字量
extern CString g_sLangID_Native_curmodule_set;
extern CString g_sLangTxt_Native_curmodule_set;  // 电流模块设定
extern CString g_sLangID_Native_acrange_set;
extern CString g_sLangTxt_Native_acrange_set;  // 交流电流档位设置
extern CString g_sLangID_Native_acmaxportvol_set;
extern CString g_sLangTxt_Native_acmaxportvol_set;  // 交流电流最大端口电压设置
extern CString g_sLangID_Native_debounce_time;
extern CString g_sLangTxt_Native_debounce_time;  // 防抖时间(S)：
extern CString g_sLangID_Native_highcurterm_Isoutput;
extern CString g_sLangTxt_Native_highcurterml_Isoutput;  //使用大电流端子Is输出
extern CString g_sLangID_Native_6Ito3I_output;
extern CString g_sLangTxt_Native_6Ito3I_output;  // 电流6I合并成3I输出

//dcSetdlg
extern CString g_sLangID_Native_auxiliary_DCvol;
extern CString g_sLangTxt_Native_auxiliary_DCvol;  // 辅助直流电压(V)
extern CString g_sLangID_Native_start_DC_output;
extern CString g_sLangTxt_Native_start_DC_output;  // 开始直流输出
extern CString g_sLangID_Native_stop_DC_output;
extern CString g_sLangTxt_Native_stop_DC_output;  // 停止直流输出
extern CString g_sLangID_Native_start_steadyoutput;
extern CString g_sLangTxt_Native_start_steadyoutput;  // 开始稳态量输出
extern CString g_sLangID_Native_stop_steadyoutput;
extern CString g_sLangTxt_Native_stop_steadyoutput;  // 停止稳态量输出
extern CString g_sLangID_Native_AC_DC_steadyoutput;
extern CString g_sLangTxt_Native_AC_DC_steadyoutput;  // 交直流稳态输出
extern CString g_sLangID_Native_auxiDC_output_notempty;
extern CString g_sLangTxt_Native_auxiDC_output_notempty;  // 辅助直流输出不可为空
extern CString g_sLangID_Native_auxiDC_output_positive;
extern CString g_sLangTxt_Native_auxiDC_output_positive;  // 要求：辅助直流输出>0

//commonparasDlg
extern CString g_sLangID_Native_extractvol_outputdef;
extern CString g_sLangTxt_Native_extractvol_outputdef;  // 抽取电压输出定义：
extern CString g_sLangID_Native_extractvol_refphasedef;
extern CString g_sLangTxt_Native_extractvol_refphasedef;  // 抽取电压参考相定义：
extern CString g_sLangID_Native_extractvol_phaseangle;
extern CString g_sLangTxt_Native_extractvol_phaseangle;  // 抽取电压相角：

extern CString g_sLangID_Native_coincidence_mode;
extern CString g_sLangTxt_Native_coincidence_mode;  // 重合方式:
extern CString g_sLangID_Native_duration_afterjump;
extern CString g_sLangTxt_Native_duration_afterjump;  // 开关跳后持续时间(s):
extern CString g_sLangID_Native_duration_coincidence;
extern CString g_sLangTxt_Native_duration_coincidence;  // 重合持续时间(s):
extern CString g_sLangID_Native_postaccelerat_duration;
extern CString g_sLangTxt_Native_postaccelerat_duration;  // 后加速开关跳开后持续时间(s):
extern CString g_sLangID_Native_impedance_refmode;
extern CString g_sLangTxt_Native_impedance_refmode;  // 阻抗参考方式:
extern CString g_sLangID_Native_zeroseq_comp_calculat;
extern CString g_sLangTxt_Native_zeroseq_comp_calculat;  // 零序补偿系数计算方式:
extern CString g_sLangID_Native_system_impedance;
extern CString g_sLangTxt_Native_system_impedance;  // 系统阻抗(Ω):
extern CString g_sLangID_Native_system_impedance_angle;
extern CString g_sLangTxt_Native_system_impedance_angle;  // 系统阻抗角(°):
extern CString g_sLangID_Native_closingangle_select;
extern CString g_sLangTxt_Native_closingangle_select;  // 合闸角选择:
extern CString g_sLangID_Native_closingangle;
extern CString g_sLangTxt_Native_closingangle;  // 合闸角(°):
extern CString g_sLangID_Native_closingangle_way;
extern CString g_sLangTxt_Native_closingangle_way;  // 合闸角方式:
extern CString g_sLangID_Native_superimposed_nonperiodic;
extern CString g_sLangTxt_Native_superimposed_nonperiodic;  // 叠加非周期分量(°):
extern CString g_sLangID_Native_search_mode;
extern CString g_sLangTxt_Native_search_mode;  // 搜索方式:

extern CString g_sLangID_Native_testprocess_control;
extern CString g_sLangTxt_Native_testprocess_control;  // 试验过程控制方式:
extern CString g_sLangID_Native_faultphase_definition;
extern CString g_sLangTxt_Native_faultphase_definition;  // 故障相定义:

//debugCfgDlg
extern CString g_sLangID_Native_bottominfo_printset;
extern CString g_sLangTxt_Native_bottominfo_printset;  // 底层信息打印设置
extern CString g_sLangID_Native_bottomloginfo_printornot;
extern CString g_sLangTxt_Native_bottomloginfo_printornot;  // 是否打印底层日志信息
extern CString g_sLangID_Native_bottomtestinfo_saveornot;
extern CString g_sLangTxt_Native_bottomtestinfo_saveornot;  // 是否保存底层测试信息

//DifferCharacWidget
extern CString g_sLangID_Native_StartIr;
extern CString g_sLangTxt_Native_StartIr;  // 启动Ir
extern CString g_sLangID_Native_RatioCoefficient;
extern CString g_sLangTxt_Native_RatioCoefficient;  // 比率系数
extern CString g_sLangID_Native_AddTestPoint;
extern CString g_sLangTxt_Native_AddTestPoint;  // 添加测试点

extern CString g_sLangID_Native_BreakoffIr;
extern CString g_sLangTxt_Native_BreakoffIr;  // 速断Ir
extern CString g_sLangID_Native_HarmCountId2;
extern CString g_sLangTxt_Native_HarmCountId2; //2次谐波Id
extern CString g_sLangID_Native_HarmCountId3;
extern CString g_sLangTxt_Native_HarmCountId3; //3次谐波Id
extern CString g_sLangID_Native_HarmCountId5;
extern CString g_sLangTxt_Native_HarmCountId5; //5次谐波Id

//goose
extern CString g_sLangID_Native_statusName;
extern CString g_sLangTxt_Native_statusName;//状态名称：
extern CString g_sLangID_Native_outputTime;
extern CString g_sLangTxt_Native_outputTime; //输出时间(s):


//第五周马
//partparawidget_trans

//表达式超出范围
extern CString g_sLangID_Native_ExprOutOfRange;
extern CString g_sLangTxt_Native_ExprOutOfRange;
//ABC三相
extern CString g_sLangID_Native_ABCTP;
extern CString g_sLangTxt_Native_ABCTP;
//Z相
extern CString g_sLangID_Native_Zphase;
extern CString g_sLangTxt_Native_Zphase;
//有功功率
extern CString g_sLangID_Native_ActPower;
extern CString g_sLangTxt_Native_ActPower;
//无功功率
extern CString g_sLangID_Native_ReacPower;
extern CString g_sLangTxt_Native_ReacPower;
//视在功率
extern CString g_sLangID_Native_AppPower;
extern CString g_sLangTxt_Native_AppPower;


//QScanLanTesterDlg_trans
//子网掩码
extern CString g_sLangID_Native_SubMask;
extern CString g_sLangTxt_Native_SubMask;
//扫描局域网测试仪
extern CString g_sLangID_Native_LST;
extern CString g_sLangTxt_Native_LST;
//网卡选择
extern CString g_sLangID_Native_NetAdptSelect;
extern CString g_sLangTxt_Native_NetAdptSelect;
//修改测试仪IP
extern CString g_sLangID_Native_ModTesterIP;
extern CString g_sLangTxt_Native_ModTesterIP;
//IP地址
extern CString g_sLangID_Native_IPAddr;
extern CString g_sLangTxt_Native_IPAddr;
//获取本地IP地址失败,当前值为空.
extern CString g_sLangID_Native_FailToRetrieveNetAddr;
extern CString g_sLangTxt_Native_FailToRetrieveNetAddr;
//取得设备信息失败
extern CString g_sLangID_Native_FailToRetDevInfo;
extern CString g_sLangTxt_Native_FailToRetDevInfo;
//测试仪IP地址(%1)与当前网卡IP不在同一网段,是否修改?
extern CString g_sLangID_Native_AddrNotInSameSubnet;
extern CString g_sLangTxt_Native_AddrNotInSameSubnet;
//当前选择的网卡为空.
extern CString g_sLangID_Native_CurrSelNetAdptEmpty;
extern CString g_sLangTxt_Native_CurrSelNetAdptEmpty;
//未知
extern CString g_sLangID_Native_Unknown;
extern CString g_sLangTxt_Native_Unknown;
//被测装置信息
extern CString g_sLangID_Native_TestDevInfo;
extern CString g_sLangTxt_Native_TestDevInfo;
//A相电压
extern CString g_sLangID_Native_PhAVoltage;
extern CString g_sLangTxt_Native_PhAVoltage;
//B相电压
extern CString g_sLangID_Native_PhBVoltage;
extern CString g_sLangTxt_Native_PhBVoltage;
//C相电压
extern CString g_sLangID_Native_PhCVoltage;
extern CString g_sLangTxt_Native_PhCVoltage;
//ABC相电压
extern CString g_sLangID_Native_PhABCVoltage;
extern CString g_sLangTxt_Native_PhABCVoltage;
//时间+开入量触发
extern CString g_sLangID_Native_TDITrigger;
extern CString g_sLangTxt_Native_TDITrigger;
//叠加
extern CString g_sLangID_Native_Overlay;
extern CString g_sLangTxt_Native_Overlay;
//不叠加
extern CString g_sLangID_Native_NoOverlay;
extern CString g_sLangTxt_Native_NoOverlay;
//随机
extern CString g_sLangID_Native_Random;
extern CString g_sLangTxt_Native_Random;

extern CString g_sLangID_Native_TestNameGenTest;
extern CString g_sLangTxt_Native_TestNameGenTest;


//平衡系数：
extern CString g_sLangID_Native_BalanceCoeff;
extern CString g_sLangTxt_Native_BalanceCoeff;
//差动速断电流定值(A)：
extern CString g_sLangID_Native_DiffFastCur;
extern CString g_sLangTxt_Native_DiffFastCur;
//差动动作电流定值(A)：
extern CString g_sLangID_Native_DiffActCur;
extern CString g_sLangTxt_Native_DiffActCur;
//比率制动特性拐点1电流(A)：
extern CString g_sLangID_Native_RatioBreakPt1;
extern CString g_sLangTxt_Native_RatioBreakPt1;
//比率制动特性拐点2电流(A)：
extern CString g_sLangID_Native_RatioBreakPt2;
extern CString g_sLangTxt_Native_RatioBreakPt2;
//基波比率制动特性斜率1：
extern CString g_sLangID_Native_BaseRatioSlope1;
extern CString g_sLangTxt_Native_BaseRatioSlope1;
//基波比率制动特性斜率2：
extern CString g_sLangID_Native_BaseRatioSlope2;
extern CString g_sLangTxt_Native_BaseRatioSlope2;
//二次谐波制动系数：
extern CString g_sLangID_Native_SecondHarmBrakeCoef;
extern CString g_sLangTxt_Native_SecondHarmBrakeCoef;
//三次谐波制动系数：

extern CString g_sLangID_Native_ThirdHarmBrakeCoef;
extern CString g_sLangTxt_Native_ThirdHarmBrakeCoef;
//五次谐波制动系数：
extern CString g_sLangID_Native_FifthHarmBrakeCoef;
extern CString g_sLangTxt_Native_FifthHarmBrakeCoef;

//第六周许

//new xwd
//批量导入波形
extern CString g_sLangID_Native_BulkWaveImport;
extern CString g_sLangTxt_Native_BulkWaveImport;
//批量导入波形文件
extern CString g_sLangID_Native_BulkWaveFileImport;
extern CString g_sLangTxt_Native_BulkWaveFileImport;
//正在打开录波文件...
extern CString g_sLangID_Native_OpeningWaveFile;
extern CString g_sLangTxt_Native_OpeningWaveFile;
//请选择文件夹
extern CString g_sLangID_Native_SelectFolder;
extern CString g_sLangTxt_Native_SelectFolder;
//该文件夹下没有录波文件！
extern CString g_sLangID_Native_NoWaveFiles;
extern CString g_sLangTxt_Native_NoWaveFiles;
//当前导入波形大于100，超出最大导入波形个数！
extern CString g_sLangID_Native_WaveExceedMax;
extern CString g_sLangTxt_Native_WaveExceedMax;
//全部应用通道
extern CString g_sLangID_Native_ApplyAllCh;
extern CString g_sLangTxt_Native_ApplyAllCh;
//全部应用变比
extern CString g_sLangID_Native_ApplyAllRatio;
extern CString g_sLangTxt_Native_ApplyAllRatio;
//全部循环次数：
extern CString g_sLangID_Native_AllCycleCount;
extern CString g_sLangTxt_Native_AllCycleCount;
//  手动控制  ：
extern CString g_sLangID_Native_ManualCtrl;
extern CString g_sLangTxt_Native_ManualCtrl;
//请选择播放波形
extern CString g_sLangID_Native_SelectWave;
extern CString g_sLangTxt_Native_SelectWave;
//播放上一个
extern CString g_sLangID_Native_PlayPrev;
extern CString g_sLangTxt_Native_PlayPrev;
//播放下一个
extern CString g_sLangID_Native_PlayNext;
extern CString g_sLangTxt_Native_PlayNext;
//停止测试仪输出
extern CString g_sLangID_Native_StopTestOut;
extern CString g_sLangTxt_Native_StopTestOut;
//差动特征曲线图
extern CString g_sLangID_Native_DiffCurve;
extern CString g_sLangTxt_Native_DiffCurve;
//谐波制动特征曲线图
extern CString g_sLangID_Native_HarmBrakeCurve;
extern CString g_sLangTxt_Native_HarmBrakeCurve;

//动作时间特征曲线图
extern CString g_sLangID_Native_ActionTimeCurve;
extern CString g_sLangTxt_Native_ActionTimeCurve;
//Soe测试参数文件【%s】不存在
extern CString g_sLangID_Native_SOETestParamFileNotExist;
extern CString g_sLangTxt_Native_SOETestParamFileNotExist;
//解析Soe测试参数文件失败【%s】
extern CString g_sLangID_Native_SOETestParamFileParseFail;
extern CString g_sLangTxt_Native_SOETestParamFileParseFail;

//第六周吕

//吕Overload Test
extern CString g_sLangID_Native_overloadACTestTempFile;
extern CString g_sLangTxt_Native_overloadACTestTempFile; //过负荷(交流)试验模板文件
extern CString g_sLangID_Native_Wel_overloadACTest;
extern CString g_sLangTxt_Native_Wel_overloadACTest; //欢迎使用过负荷(交流)试验.
extern CString g_sLangID_Native_Ponovo_overloadACTest;
extern CString g_sLangTxt_Native_Ponovo_overloadACTest; //Ponovo 过负荷(交流)试验
extern CString g_sLangID_Native_overloadACTest;
extern CString g_sLangTxt_Native_overloadACTest; //过负荷(交流)试验

extern CString g_sLangID_Native_overloadCurrentChannel;
extern CString g_sLangTxt_Native_overloadCurrentChannel; //过负荷电流通道
extern CString g_sLangID_Native_overloadCurChannel;
extern CString g_sLangTxt_Native_overloadCurChannel; //过负荷电流通道:
extern CString g_sLangID_Native_overloadAC;
extern CString g_sLangTxt_Native_overloadAC; //过负荷(交流)
extern CString g_sLangID_Native_overloadCurrentIA;
extern CString g_sLangTxt_Native_overloadCurrentIA; //过负荷电流I(A):
extern CString g_sLangID_Native_NormTimeS;
extern CString g_sLangTxt_Native_NormTimeS; //常态时间(s):


//

//第六周马
/*tr("过负荷(电流)试验模板文件")*/
extern CString g_sLangID_Native_OverloadCurrTestTemplate;
extern CString g_sLangTxt_Native_OverloadCurrTestTemplate;
/*_T("欢迎使用过负荷(直流)试验.")*/
extern CString g_sLangID_Native_WelcomeToOverloadDCTest;
extern CString g_sLangTxt_Native_WelcomeToOverloadDCTest;
/*tr("Ponovo 过负荷(直流)试验")*/
extern CString g_sLangID_Native_OverloadDCTest;
extern CString g_sLangTxt_Native_OverloadDCTest;
/*_T("热过负荷动作定值k")*/
extern CString g_sLangID_Native_ThermalOverloadTripSetting;
extern CString g_sLangTxt_Native_ThermalOverloadTripSetting;
/*_T("热过负荷基准电流IB")*/
extern CString g_sLangID_Native_ThermalOverloadRefCurr;
extern CString g_sLangTxt_Native_ThermalOverloadRefCurr;
/*_T("热过负荷时间常数τ")*/
extern CString g_sLangID_Native_ThermalOverloadTimeConst;
extern CString g_sLangTxt_Native_ThermalOverloadTimeConst;
/*_T("输出参数导致动作时间定值为负数，未修改成功，请根据动作特性方程重新修改!")*/
extern CString g_sLangID_Native_RedefineToChar;
extern CString g_sLangTxt_Native_RedefineToChar;

/*"<h1>过负荷(直流)</h1>"*/
extern CString g_sLangID_Native_OverloadDC;
extern CString g_sLangTxt_Native_OverloadDC;
/*_T("当前选择的电流通道(Index=%d)未查找到.")*/
extern CString g_sLangID_Native_CurrChannelNotFound;
extern CString g_sLangTxt_Native_CurrChannelNotFound;
/*QObject::tr("动作特性方程:")*/
extern CString g_sLangID_Native_ProtCharEquation;
extern CString g_sLangTxt_Native_ProtCharEquation;
//过负荷电流
extern CString g_sLangID_Native_OverloadCurr;
extern CString g_sLangTxt_Native_OverloadCurr;

//报文总数
extern CString g_sLangID_Native_TotalMsgs;
extern CString g_sLangTxt_Native_TotalMsgs;
//丢包数
extern CString g_sLangID_Native_PktLossCount;
extern CString g_sLangTxt_Native_PktLossCount;
//最大时间差
extern CString g_sLangID_Native_MaxTimeDiff;
extern CString g_sLangTxt_Native_MaxTimeDiff;
//停止写文件
extern CString g_sLangID_Native_StopWriteFile;
extern CString g_sLangTxt_Native_StopWriteFile;




//第七周吕
//ovt
extern CString g_sLangID_Native_OVtempfile;
extern CString g_sLangTxt_Native_OVtempfile;//过压试验模板文件
extern CString g_sLangID_Native_wel_OVtest;
extern CString g_sLangTxt_Native_wel_OVtest;//欢迎使用过压测试.
extern CString g_sLangID_Native_OVprotect;
extern CString g_sLangTxt_Native_OVprotect;//过电压保护
extern CString g_sLangID_Native_OverValtage;
extern CString g_sLangTxt_Native_OverValtage;//过压
extern CString g_sLangID_Native_OVprotect_Actvalue;
extern CString g_sLangTxt_Native_OVprotect_Actvalue;//过压保护动作值
extern CString g_sLangID_Native_OV_ActTimelim;
extern CString g_sLangTxt_Native_OV_ActTimelim;//过电压动作时限
extern CString g_sLangID_Native_ActVNega_Error;
extern CString g_sLangTxt_Native_ActVNega_Error;//当前动作电压为负，修改不成功.
extern CString g_sLangID_Native_ActTNega_Error;
extern CString g_sLangTxt_Native_ActTNega_Error;//当前动作时间为负，修改不成功.
extern CString g_sLangID_Native_Name_OVprotectTest;
extern CString g_sLangTxt_Native_Name_OVprotectTest;//试验名称：过压保护定值测试
extern CString g_sLangID_Native_OVprotectTest;
extern CString g_sLangTxt_Native_OVprotectTest;//过压保护定值测试
extern CString g_sLangID_Native_1ErrorType_and_Times;
extern CString g_sLangTxt_Native_1ErrorType_and_Times;//请务必至少选择一个故障类型以及倍数！
extern CString g_sLangID_Native_SetValueV;
extern CString g_sLangTxt_Native_SetValueV;//整定值(V)
extern CString g_sLangID_Native_AddTestDig;
extern CString g_sLangTxt_Native_AddTestDig;//添加测试项


//第七周马
/*tr("电压保护试验模板文件")*/
extern CString g_sLangID_Native_VoltProtTestTplFile;
extern CString g_sLangTxt_Native_VoltProtTestTplFile;
/*_T("欢迎使用电压保护测试.")*/
extern CString g_sLangID_Native_WelcomeVoltProtTest;
extern CString g_sLangTxt_Native_WelcomeVoltProtTest;
/*tr("电压保护")*/
extern CString g_sLangID_Native_VoltProtection;
extern CString g_sLangTxt_Native_VoltProtection;
/*_T("电压I段动作值")*/
extern CString g_sLangID_Native_VIStagePickVal;
extern CString g_sLangTxt_Native_VIStagePickVal;
/*_T("电压II段动作值")*/
extern CString g_sLangID_Native_VIIStagePickVal;
extern CString g_sLangTxt_Native_VIIStagePickVal;
/*_T("电压III段动作值")*/
extern CString g_sLangID_Native_VIIIStagePickVal;
extern CString g_sLangTxt_Native_VIIIStagePickVal;
/*_T("电压IV段动作值")*/
extern CString g_sLangID_Native_VIVStagePickVal;
extern CString g_sLangTxt_Native_VIVStagePickVal;
/*_T("电压I段动作时间")*/
extern CString g_sLangID_Native_VIPickTime;
extern CString g_sLangTxt_Native_VIPickTime;
/*_T("电压II段动作时间")*/
extern CString g_sLangID_Native_VIIPickTime;
extern CString g_sLangTxt_Native_VIIPickTime;
/*_T("电压III段动作时间")*/
extern CString g_sLangID_Native_VIIIPickTime;
extern CString g_sLangTxt_Native_VIIIPickTime;
/*_T("电压IV段动作时间")*/
extern CString g_sLangID_Native_VIVPickTime;
extern CString g_sLangTxt_Native_VIVPickTime;
/*_T("当前动作值为负，修改不成功.")*/
extern CString g_sLangID_Native_CurrPickNegModUnsucc;
extern CString g_sLangTxt_Native_CurrPickNegModUnsucc;
/*_T("过电压")*/
extern CString g_sLangID_Native_Ovltg;
extern CString g_sLangTxt_Native_Ovltg;
/*试验名称：过压保护定值测试*/
extern CString g_sLangID_Native_OvltgProtSetTest;
extern CString g_sLangTxt_Native_OvltgProtSetTest;
/*"过压I段保护定值测试"*/
extern CString g_sLangID_Native_OvltgIProtSetTest;
extern CString g_sLangTxt_Native_OvltgIProtSetTest;
/*"过压II段保护定值测试"*/
extern CString g_sLangID_Native_OvltgIIProtSetTest;
extern CString g_sLangTxt_Native_OvltgIIProtSetTest;
/*"过压III段保护定值测试"*/
extern CString g_sLangID_Native_OvltgIIIProtSetTest;
extern CString g_sLangTxt_Native_OvltgIIIProtSetTest;
/*"过压IV段保护定值测试"*/
extern CString g_sLangID_Native_OvltgIVProtSetTest;
extern CString g_sLangTxt_Native_OvltgIVProtSetTest;
/*"过压V段保护定值测试"*/
extern CString g_sLangID_Native_OvltgVProtSetTest;
extern CString g_sLangTxt_Native_OvltgVProtSetTest;
/*tr("故障前输出")*/
extern CString g_sLangID_Native_PreFaultOut;
extern CString g_sLangTxt_Native_PreFaultOut;


/*tr("故障前时间裕度")*/
extern CString g_sLangID_Native_PreFaultTimeMargin;
extern CString g_sLangTxt_Native_PreFaultTimeMargin;
/*_T("当前设置值(%f)小于最小值(0.000000),修改不成功")*/
extern CString g_sLangID_Native_CSVLessMinModUnsucc;
extern CString g_sLangTxt_Native_CSVLessMinModUnsucc;
/*_T("当前设置值(%f)大于最大值(%f),强制设置为最大值")*/
extern CString g_sLangID_Native_CSVGreaterMaxForceSetMax;
extern CString g_sLangTxt_Native_CSVGreaterMaxForceSetMax;
/*_T("当前设置值(%f)大于最大值(999.000000),强制设置为最大值")*/
extern CString g_sLangID_Native_CSVGreaterMaxForceSetMax9;
extern CString g_sLangTxt_Native_CSVGreaterMaxForceSetMax9;














#endif // _XLangResource_PowerTestWin_h__
