#include "stdafx.h"
#include "XLangResource_PowerTestWin.h"

CString g_strXLangRs_PowerTestWin = _T("Lang_PowerTestWin");


CXLangResource_PowerTestWin::CXLangResource_PowerTestWin()
{
	m_pXLangRsExe = &m_oXLangRs_Test;
	m_oXLangRs_Test.m_strID = g_strXLangRs_PowerTestWin;
	m_oXLangRs_Test.m_strName = g_strXLangRs_PowerTestWin;
}

CXLangResource_PowerTestWin::~CXLangResource_PowerTestWin()
{
	m_oXLangRs_Test.RemoveAll();
}


CXLangItem* CXLangResource_PowerTestWin::rs_AddString(const CString &strID, CString *pstrString)
{
	CXLangItem *p = CXLanguage::AddString(strID, pstrString);

	m_oXLangRs_Test.AddTail(p);

	return p;
}


void CXLangResource_PowerTestWin::InitLangRsByFile()
{
	CXLangResource_Native::InitLangRsByFile();

	InitLangRsByFileEx(&m_oXLangRs_Test, g_strXLangRs_PowerTestWin);
}



void CXLangResource_PowerTestWin::RegisterLanguageResource()
{
	CXLangResource_Native::RegisterLanguageResource();

	// LY 吕
	rs_AddString(g_sLangID_ActTime_Protect_TestTempFile, &g_sLangTxt_ActTime_Protect_TestTempFile);		  // 动作时间保护试验模板文件
	rs_AddString(g_sLangID_ActionTime_test, &g_sLangTxt_ActionTime_test);								  // 欢迎使用动作时间实验
	rs_AddString(g_sLangID_Native_PonovoActiontime, &g_sLangTxt_Native_PonovoActiontime);				  // Ponovo动作时间
	rs_AddString(g_sLangID_ActionTimeTest, &g_sLangTxt_ActionTimeTest);									  // 动作时间测试
	rs_AddString(g_sLangID_Single_phaseGroundFault, &g_sLangTxt_Single_phaseGroundFault);				  // 单相接地短路
	rs_AddString(g_sLangID_PhasetoPhase_ShortCircuit, &g_sLangTxt_PhasetoPhase_ShortCircuit);			  // 相间短路
	rs_AddString(g_sLangID_Zero_SequenceCurrent, &g_sLangTxt_Zero_SequenceCurrent);						  // 零序电流
	rs_AddString(g_sLangID_Negative_SequenceCurrent, &g_sLangTxt_Negative_SequenceCurrent);				  // 负序电流
	rs_AddString(g_sLangID_ParaConnect_Three_PhaseCurrents, &g_sLangTxt_ParaConnect_Three_PhaseCurrents); // 三相电流并联
	rs_AddString(g_sLangID_Single_PhaseFault, &g_sLangTxt_Single_PhaseFault);							  // 单相故障
	// 吕
	rs_AddString(g_sLangID_AutoSyn_TestTempFile, &g_sLangTxt_AutoSyn_TestTempFile);				  // 自动准周期试验模板文件
	rs_AddString(g_sLangID_Wel_AutoSynTest, &g_sLangTxt_Wel_AutoSynTest);						  // 欢迎使用自动准同期试验
	rs_AddString(g_sLangID_Ponovo_AutoSyn, &g_sLangTxt_Ponovo_AutoSyn);							  // Ponovo自动准同期
	rs_AddString(g_sLangID_AutoSyn, &g_sLangTxt_AutoSyn);										  // 自动准同期
	rs_AddString(g_sLangID_System_Rated_FreqHZ, &g_sLangTxt_System_Rated_FreqHZ);				  ////系统侧额定频率（Hz）
	rs_AddString(g_sLangID_System_Rated_Volt, &g_sLangTxt_System_Rated_Volt);				  ////系统侧额定电压（V）
	rs_AddString(g_sLangID_Grid_VolV, &g_sLangTxt_Grid_VolV);									  // 待并侧电压（V）
	rs_AddString(g_sLangID_Stepsize_Grid_volvariation, &g_sLangTxt_Stepsize_Grid_volvariation);	  ////待并侧电压变化步长（V）
	rs_AddString(g_sLangID_Grid_Rated_VolV, &g_sLangTxt_Grid_Rated_VolV);						  // 待并侧额定电压（V）
	rs_AddString(g_sLangID_VolDifference, &g_sLangTxt_VolDifference);							  // 压差（V）
	rs_AddString(g_sLangID_Allow_VolDifV, &g_sLangTxt_Allow_VolDifV);							  // 允许压差（V）
	rs_AddString(g_sLangID_FreqDifference, &g_sLangTxt_FreqDifference);							  // 频差（HZ）
	rs_AddString(g_sLangID_Allow_FreqDifHZ, &g_sLangTxt_Allow_FreqDifHZ);						  // 允许频差（Hz）
	rs_AddString(g_sLangID_AtleastOneTest, &g_sLangTxt_AtleastOneTest);							  // 至少保留一个测试项
	rs_AddString(g_sLangID_Vol_BoundValueTest, &g_sLangTxt_Vol_BoundValueTest);					  // 电压边界值测试
	rs_AddString(g_sLangID_Volbound_trip_values, &g_sLangTxt_Volbound_trip_values);				  // 电压边界值动作值（V）
	rs_AddString(g_sLangID_Freq_BoundValueTest, &g_sLangTxt_Freq_BoundValueTest);				  // 频率边界值测试
	rs_AddString(g_sLangID_Auto_AdjustTest, &g_sLangTxt_Auto_AdjustTest);						  // 自调整试验
	rs_AddString(g_sLangID_Vol_ReguPeriodTest, &g_sLangTxt_Vol_ReguPeriodTest);					  // 调压周期测试
	rs_AddString(g_sLangID_Freq_ReguPeriodTest, &g_sLangTxt_Freq_ReguPeriodTest);				  // 调频周期测试
	rs_AddString(g_sLangID_Lead_AngleTime_Test, &g_sLangTxt_Lead_AngleTime_Test);				  // 导前角及导前时间测试
	rs_AddString(g_sLangID_result, &g_sLangTxt_result);											  // 结论
	rs_AddString(g_sLangID_Stepsize_Grid_freqvariation, &g_sLangTxt_Stepsize_Grid_freqvariation); // 待并侧频率变化步长（HZ）
	rs_AddString(g_sLangID_Freqbound_trip_values, &g_sLangTxt_Freqbound_trip_values);			  // 频率边界值动作值（HZ）
	rs_AddString(g_sLangID_Leading_Angle, &g_sLangTxt_Leading_Angle);							  // 导前角（°）
	rs_AddString(g_sLangID_Leading_Time, &g_sLangTxt_Leading_Time);								  // 导前时间（s）
	rs_AddString(g_sLangID_Native_dVzd, &g_sLangTxt_Native_dVzd);								  // 允许压差整定值（V）
	rs_AddString(g_sLangID_Native_dFzd, &g_sLangTxt_Native_dFzd);								  // 允许频差整定值（HZ）
	rs_AddString(g_sLangID_Native_Ut, &g_sLangTxt_Native_Ut);									  // 调压周期整定值（s）
	rs_AddString(g_sLangID_AdjVolCycle, &g_sLangTxt_AdjVolCycle);								  // 调压周期动作值（s）
	rs_AddString(g_sLangID_AdjVolWidth, &g_sLangTxt_AdjVolWidth);								  // 调压脉宽（s）
	rs_AddString(g_sLangID_Native_Ft, &g_sLangTxt_Native_Ft);									  // 调频周期整定值（s）
	rs_AddString(g_sLangID_AdjFreqCycle, &g_sLangTxt_AdjFreqCycle);								  // 调频周期动作值（s）
	rs_AddString(g_sLangID_AdjFreqWidth, &g_sLangTxt_AdjFreqWidth);								  // 调频脉宽（s）
	rs_AddString(g_sLangID_Native_System, &g_sLangTxt_Native_System);							  // 系统
	rs_AddString(g_sLangID_waitgrid_connection, &g_sLangTxt_waitgrid_connection);				  // 待并
	rs_AddString(g_sLangID_expression_error, &g_sLangTxt_expression_error);						  // 表达式输出错误
	rs_AddString(g_sLangID_Out4_Time, &g_sLangTxt_Out4_Time);									  // 开出4保持时间（s）

	rs_AddString(g_sLangID_Native_Bout, &g_sLangTxt_Native_Bout);				// 开出量
	rs_AddString(g_sLangID_protectexport_sign, &g_sLangTxt_protectexport_sign); // 保护出口信号
	rs_AddString(g_sLangID_boost_sign, &g_sLangTxt_boost_sign);					// 增压信号
	rs_AddString(g_sLangID_reduce_sign, &g_sLangTxt_reduce_sign);				// 减压信号
	rs_AddString(g_sLangID_speed_sign, &g_sLangTxt_speed_sign);					// 增速信号
	rs_AddString(g_sLangID_slow_sign, &g_sLangTxt_slow_sign);					// 减速信号

	rs_AddString(g_sLangID_pulse, &g_sLangTxt_pulse);		// 脉冲
	rs_AddString(g_sLangID_continue, &g_sLangTxt_continue); // 连续
	rs_AddString(g_sLangID_value, &g_sLangTxt_value);		// 值
	// 吕
	rs_AddString(g_sLangID_lowfreqloadre_tempfile, &g_sLangTxt_lowfreqloadre_tempfile);	  // 低周减载模板文件
	rs_AddString(g_sLangID_wel_lowfreqloadre, &g_sLangTxt_wel_lowfreqloadre);			  // 欢迎使用低周减载
	rs_AddString(g_sLangID_Ponovo_lowfreqloadre, &g_sLangTxt_Ponovo_lowfreqloadre);		  // Ponovo 低周减载
	rs_AddString(g_sLangID_lowfreqloadre, &g_sLangTxt_lowfreqloadre);					  // 低周减载
	rs_AddString(g_sLangID_Noselect_testitems, &g_sLangTxt_Noselect_testitems);			  // 没有选择测试项
	rs_AddString(g_sLangID_Atleast1_5testitems, &g_sLangTxt_Atleast1_5testitems);		  // 5种测试类型至少各保留一个测试项！
	rs_AddString(g_sLangID_Atleast1_Thistestitems, &g_sLangTxt_Atleast1_Thistestitems);	  // 此测试类型至少保留一个测试项！
	rs_AddString(g_sLangID_Native_FreAction, &g_sLangTxt_Native_FreAction);				  // 动作频率
	rs_AddString(g_sLangID_Native_sliptrip, &g_sLangTxt_Native_sliptrip);				  // 滑差闭锁
	rs_AddString(g_sLangID_interlock_volselection, &g_sLangTxt_interlock_volselection);	  // 闭锁电压选择
	rs_AddString(g_sLangID_FreAValue_Test, &g_sLangTxt_FreAValue_Test);					  // 频率动作值测试
	rs_AddString(g_sLangID_Native_sliptripTest, &g_sLangTxt_Native_sliptripTest);		  // 滑差闭锁值测试
	rs_AddString(g_sLangID_lowcur_lockout_test, &g_sLangTxt_lowcur_lockout_test);		  // 低电流闭锁值测试
	rs_AddString(g_sLangID_Native_LowVoltLock_test, &g_sLangTxt_Native_LowVoltLock_test); // 低电压闭锁值测试
	rs_AddString(g_sLangID_lowfreqloadre_Setting, &g_sLangTxt_lowfreqloadre_Setting);	  // 低周减载动作值
	rs_AddString(g_sLangID_lowcur_lockout, &g_sLangTxt_lowcur_lockout);					  // 低电流闭锁值
// 	rs_AddString(g_sLangID_Voltage, &g_sLangTxt_Voltage);								  // 电压（V）
	rs_AddString(g_sLangID_lowVoltage, &g_sLangTxt_lowVoltage);							  // 低压
	rs_AddString(g_sLangID_Negative_SeqVolU2, &g_sLangTxt_Negative_SeqVolU2);			  // 负序电压(U2)
	rs_AddString(g_sLangID_Zero_SeqCur3U0, &g_sLangTxt_Zero_SeqCur3U0);					  // 零序电压(3U0)
	rs_AddString(g_sLangID_Illegal_testitem, &g_sLangTxt_Illegal_testitem);				  // 测试项类型非法
	rs_AddString(g_sLangID_Native_OutOf_Range, &g_sLangTxt_Native_OutOf_Range);			  // 超出变化范围
	rs_AddString(g_sLangID_action_freqvalue, &g_sLangTxt_action_freqvalue);				  // 动作频率值

	// LowUTest_Trans 马
	rs_AddString(g_sLangID_Native_LVLoadRedTemp, &g_sLangTxt_Native_LVLoadRedTemp);						/*tr("低压减载试验模板文件")*/
	rs_AddString(g_sLangID_Native_WLULVLRTest, &g_sLangTxt_Native_WLULVLRTest);							/*_T("欢迎使用低压减载试验.")*/
	rs_AddString(g_sLangID_Native_PLVLRTitle, &g_sLangTxt_Native_PLVLRTitle);							/*tr("Ponovo 低压减载")*/
	rs_AddString(g_sLangID_Native_LowVLoadRed, &g_sLangTxt_Native_LowVLoadRed);							/*tr("低压减载")*/
	rs_AddString(g_sLangID_Native_LowVRateLock, &g_sLangTxt_Native_LowVRateLock);						/*_T("低压变化率闭锁值")*/
	rs_AddString(g_sLangID_Native_KeepOneTest, &g_sLangTxt_Native_KeepOneTest);							/*tr("至少保留一个测试项!")*/
	rs_AddString(g_sLangID_Native_LVLRActionVal, &g_sLangTxt_Native_LVLRActionVal);						/*QString::tr("低压减载动作值")*/
	rs_AddString(g_sLangID_Native_ProgRunning, &g_sLangTxt_Native_ProgRunning);							/*QObject::tr("程序已经在运行！")*/
	rs_AddString(g_sLangID_Native_LVLRTesting, &g_sLangTxt_Native_LVLRTesting);							/*"<h1>低压减载测试</h1>"*/
	rs_AddString(g_sLangID_Native_LowVoltLock, &g_sLangTxt_Native_LowVoltLock);							/*tr("低电压闭锁值")*/
// 	rs_AddString(g_sLangID_Native_ActTimeSym, &g_sLangTxt_Native_ActTimeSym);							/*tr("动作时间=")*/
	rs_AddString(g_sLangID_Native_VoltSlipLock, &g_sLangTxt_Native_VoltSlipLock);						/*tr("电压滑差闭锁值")*/
	rs_AddString(g_sLangID_Native_PhaseVoltStepV, &g_sLangTxt_Native_PhaseVoltStepV);					/*tr("相电压变化步长(V):")*/
	rs_AddString(g_sLangID_Native_PhaseVoltStartV, &g_sLangTxt_Native_PhaseVoltStartV);					/*tr("相电压变化起始值(V):")*/
	rs_AddString(g_sLangID_Native_PhaseVoltEndV, &g_sLangTxt_Native_PhaseVoltEndV);						/*tr("相电压变化结束值(V):")*/
	rs_AddString(g_sLangID_Native_LineVoltStepV, &g_sLangTxt_Native_LineVoltStepV);						/*tr("线电压变化步长(V):")*/
	rs_AddString(g_sLangID_Native_LineVoltStartV, &g_sLangTxt_Native_LineVoltStartV);					/*tr("线电压变化起始值(V):")*/
	rs_AddString(g_sLangID_Native_LineVoltEndV, &g_sLangTxt_Native_LineVoltEndV);						/*tr("线电压变化结束值(V):")*/	
	rs_AddString(g_sLangID_Native_PhaseVoltBeginV, &g_sLangTxt_Native_PhaseVoltBeginV);					/*tr("相电压变化起始值(V):")*/
	rs_AddString(g_sLangID_Native_PhaseVoltFinal, &g_sLangTxt_Native_PhaseVoltFinal);					/*tr("相电压变化终值(V):")*/
	rs_AddString(g_sLangID_Native_LineVoltFinal, &g_sLangTxt_Native_LineVoltFinal);						/*tr("线电压变化终值(V):")*/
	rs_AddString(g_sLangID_Native_PhaseVSlipStep, &g_sLangTxt_Native_PhaseVSlipStep);					/*tr("相电压滑差变化步长(V/s):")*/
	rs_AddString(g_sLangID_Native_LineVSlipStep, &g_sLangTxt_Native_LineVSlipStep);						/*tr("线电压滑差变化步长(V/s):")*/
	rs_AddString(g_sLangID_Native_PhaseVSlipStart, &g_sLangTxt_Native_PhaseVSlipStart);					/*tr("相电压滑差变化始值(V/s):")*/
	rs_AddString(g_sLangID_Native_LineVSlipStart, &g_sLangTxt_Native_LineVSlipStart);					/*tr("线电压滑差变化始值(V/s):")*/
	rs_AddString(g_sLangID_Native_PhaseVSlipEnd, &g_sLangTxt_Native_PhaseVSlipEnd);						/*tr("相电压滑差变化终值(V/s):")*/
	rs_AddString(g_sLangID_Native_LineVSlipEnd, &g_sLangTxt_Native_LineVSlipEnd);						/*tr("线电压滑差变化终值(V/s):")*/
	rs_AddString(g_sLangID_Native_ExprInputErr, &g_sLangTxt_Native_ExprInputErr);						/*_T("表达式输入错误")*/
	rs_AddString(g_sLangID_Native_OutOfRange, &g_sLangTxt_Native_OutOfRange);							/*_T("超出范围")*/
	rs_AddString(g_sLangID_Native_VarStepExceed60P, &g_sLangTxt_Native_VarStepExceed60P);				/*_T("递变步数超过60，请重新输入！")*/
	rs_AddString(g_sLangID_Native_SteadyStateTime, &g_sLangTxt_Native_SteadyStateTime);					// 稳态时间(s):

	

	// PowerDirectionTest_Trans 马
	rs_AddString(g_sLangID_Native_PowerDirTemp, &g_sLangTxt_Native_PowerDirTemp);		/*tr("功率方向试验模板文件")*/
	rs_AddString(g_sLangID_Native_WelcomePD, &g_sLangTxt_Native_WelcomePD);				/*_T("欢迎使用功率方向.")*/
	rs_AddString(g_sLangID_Native_GetRealTimeFail, &g_sLangTxt_Native_GetRealTimeFail); /*_T("获取实时数据绝对时间失败.")*/
	rs_AddString(g_sLangID_Native_GetRelTimeFail, &g_sLangTxt_Native_GetRelTimeFail);	/*_T("获取实时数据相对时间失败.")*/
	rs_AddString(g_sLangID_Native_PonovoPower, &g_sLangTxt_Native_PonovoPower);			/*tr("Ponovo 功率方向")*/
	rs_AddString(g_sLangID_Native_PowerDir, &g_sLangTxt_Native_PowerDir);				/*tr("功率方向")*/
	rs_AddString(g_sLangID_Native_Assessment, &g_sLangTxt_Native_Assessment);			/*tr("评估")*/
	rs_AddString(g_sLangID_Native_PowerDirTest, &g_sLangTxt_Native_PowerDirTest);		/*"<h1>功率方向测试</h1>"*/
	rs_AddString(g_sLangID_Native_PhaseATest, &g_sLangTxt_Native_PhaseATest);			/*"A相测试"*/
	rs_AddString(g_sLangID_Native_PhaseBTest, &g_sLangTxt_Native_PhaseBTest);			/*"B相测试"*/
	rs_AddString(g_sLangID_Native_PhaseCTest, &g_sLangTxt_Native_PhaseCTest);			/*"C相测试"*/
	rs_AddString(g_sLangID_Native_PhaseZeroTest, &g_sLangTxt_Native_PhaseZeroTest);		/*"零序测试"*/
	rs_AddString(g_sLangID_Native_PhaseLossTest, &g_sLangTxt_Native_PhaseLossTest);		/*"负序测试"*/
	rs_AddString(g_sLangID_Native_VoltAheadPosAng, &g_sLangTxt_Native_VoltAheadPosAng); /*tr("电压超前电流为正角度")*/
	rs_AddString(g_sLangID_Native_CurrAheadPosAng, &g_sLangTxt_Native_CurrAheadPosAng); /*tr("电流超前电压为正角度")*/
	rs_AddString(g_sLangID_Native_Deg0Conn, &g_sLangTxt_Native_Deg0Conn);				/*tr("0度接线")*/
	rs_AddString(g_sLangID_Native_Deg90Conn, &g_sLangTxt_Native_Deg90Conn);				/*tr("90度接线")*/
	rs_AddString(g_sLangID_Native_GenParamSet, &g_sLangTxt_Native_GenParamSet);			/*QObject::tr("通用参数设置")*/

	// PowerFreqTest_Trans 马
	rs_AddString(g_sLangID_Native_FreqChgDistTemp, &g_sLangTxt_Native_FreqChgDistTemp);			/*tr("工频变化量距离试验模板文件")*/
	rs_AddString(g_sLangID_Native_WelcFreqChgTest, &g_sLangTxt_Native_WelcFreqChgTest);			/*_T("欢迎使用工频变化量距离试验.")*/
	rs_AddString(g_sLangID_Native_PonovoFreqChgDist, &g_sLangTxt_Native_PonovoFreqChgDist);		/*tr("Ponovo 工频变化量距离试验")*/
	rs_AddString(g_sLangID_Native_FreqChgDistance, &g_sLangTxt_Native_FreqChgDistance);			/*tr("工频变化量距离")*/
	rs_AddString(g_sLangID_Native_ImpedChart, &g_sLangTxt_Native_ImpedChart);					/*tr("阻抗特性图")*/
	rs_AddString(g_sLangID_Native_PhaseAGround, &g_sLangTxt_Native_PhaseAGround);				/*QObject::tr("A相接地,")*/
	rs_AddString(g_sLangID_Native_PhaseBGround, &g_sLangTxt_Native_PhaseBGround);				/*QObject::tr("B相接地,")*/
	rs_AddString(g_sLangID_Native_PhaseCGround, &g_sLangTxt_Native_PhaseCGround);				/*QObject::tr("C相接地,")*/
	rs_AddString(g_sLangID_Native_PhaseABShortCircuit, &g_sLangTxt_Native_PhaseABShortCircuit); /*QObject::tr("AB短路,")*/
	rs_AddString(g_sLangID_Native_PhaseBCShortCircuit, &g_sLangTxt_Native_PhaseBCShortCircuit); /*QObject::tr("BC短路,")*/
	rs_AddString(g_sLangID_Native_PhaseCAShortCircuit, &g_sLangTxt_Native_PhaseCAShortCircuit); /*QObject::tr("CA短路,")*/
	rs_AddString(g_sLangID_Native_Instantaneous, &g_sLangTxt_Native_Instantaneous);				/*QObject::tr("瞬时,")*/
	rs_AddString(g_sLangID_Native_Permanently, &g_sLangTxt_Native_Permanently);					/*QObject::tr("永久,")*/
	rs_AddString(g_sLangID_Native_FreqChgDistTest, &g_sLangTxt_Native_FreqChgDistTest);			/*"<h1>工频变化量距离测试</h1>"*/
	rs_AddString(g_sLangID_Native_FreqChgDist, &g_sLangTxt_Native_FreqChgDist);					/*"工频变化量距离"*/
	rs_AddString(g_sLangID_Native_PosDirection, &g_sLangTxt_Native_PosDirection);				/*"<h3>正方向</h3>"*/
	rs_AddString(g_sLangID_Native_RevDirection, &g_sLangTxt_Native_RevDirection);				/*"<h3>反方向</h3>"*/
	rs_AddString(g_sLangID_OKCancel, &g_sLangTxt_OKCancel);										/*"确定取消"*/
	rs_AddString(g_sLangID_Native_BusSide, &g_sLangTxt_Native_BusSide);							/*QObject::tr("母线侧")*/
	rs_AddString(g_sLangID_Native_LineSide, &g_sLangTxt_Native_LineSide);						/*QObject::tr("线路侧")*/
	rs_AddString(g_sLangID_Native_TowardBus, &g_sLangTxt_Native_TowardBus);						/*QObject::tr("指向母线")*/
	rs_AddString(g_sLangID_Native_TowardLine, &g_sLangTxt_Native_TowardLine);					/*QObject::tr("指向线路")*/
	rs_AddString(g_sLangID_Native_NoSimulation, &g_sLangTxt_Native_NoSimulation);				/*QObject::tr("不模拟")*/
	rs_AddString(g_sLangID_Native_OppositeDirection, &g_sLangTxt_Native_OppositeDirection);		/*tr("反向")*/
	rs_AddString(g_sLangID_Native_PositiveDirection, &g_sLangTxt_Native_PositiveDirection);		/*tr("正向")*/
	rs_AddString(g_sLangID_Native_Immediate, &g_sLangTxt_Native_Immediate);						/*tr("瞬时")*/
	rs_AddString(g_sLangID_Native_Permanent, &g_sLangTxt_Native_Permanent);						/*tr("永久")*/
	rs_AddString(g_sLangID_Native_Trip3Phase, &g_sLangTxt_Native_Trip3Phase);					/*tr("跳三相=%1s,")*/
	rs_AddString(g_sLangID_Native_TripPhaseA, &g_sLangTxt_Native_TripPhaseA);					/*tr("跳A=%1s,")*/
	rs_AddString(g_sLangID_Native_TripPhaseB, &g_sLangTxt_Native_TripPhaseB);					/*tr("跳B=%1s,")*/
	rs_AddString(g_sLangID_Native_TripPhaseC, &g_sLangTxt_Native_TripPhaseC);					/*tr("跳C=%1s,")*/
	rs_AddString(g_sLangID_Native_ReclosingSy, &g_sLangTxt_Native_ReclosingSy);					/*tr("重合闸=%1s,")*/
	rs_AddString(g_sLangID_Native_PostAccel, &g_sLangTxt_Native_PostAccel);						/*tr("后加速=%1s,")*/
	rs_AddString(g_sLangID_Native_TimeofReturn, &g_sLangTxt_Native_TimeofReturn);				/*tr("返回时间=%1s,")*/
	rs_AddString(g_sLangID_Native_TimeofReturnA, &g_sLangTxt_Native_TimeofReturnA);				/*tr("返回时间A=%1s,")*/
	rs_AddString(g_sLangID_Native_TimeofReturnB, &g_sLangTxt_Native_TimeofReturnB);				/*tr("返回时间B=%1s,")*/
	rs_AddString(g_sLangID_Native_TimeofReturnC, &g_sLangTxt_Native_TimeofReturnC);				/*tr("返回时间C=%1s,")*/
	rs_AddString(g_sLangID_Native_TimeofReturnD, &g_sLangTxt_Native_TimeofReturnD);				/*tr("返回时间D=%1s,")*/
	rs_AddString(g_sLangID_Native_TVInstLoc, &g_sLangTxt_Native_TVInstLoc);						// TV安装位置
	rs_AddString(g_sLangID_Native_PosPolTA, &g_sLangTxt_Native_PosPolTA);						// TA正极性
	rs_AddString(g_sLangID_Native_CBsim, &g_sLangTxt_Native_CBsim);								// 断路器模拟
	rs_AddString(g_sLangID_Native_TripTime, &g_sLangTxt_Native_TripTime);						// 分闸时间
	rs_AddString(g_sLangID_Native_CloseTime, &g_sLangTxt_Native_CloseTime);						// 合闸时间
	rs_AddString(g_sLangID_Native_ImpChar, &g_sLangTxt_Native_ImpChar);							// 阻抗特性

	// start XWD
	rs_AddString(g_sLangID_Native_RLPtestTF, &g_sLangTxt_Native_RLPtestTF);
	rs_AddString(g_sLangID_Native_WelUseRLPT, &g_sLangTxt_Native_WelUseRLPT);
	rs_AddString(g_sLangID_Native_AbsoluteTimeF, &g_sLangTxt_Native_AbsoluteTimeF);
	rs_AddString(g_sLangID_Native_RelativeTimeF, &g_sLangTxt_Native_RelativeTimeF);
	rs_AddString(g_sLangID_Native_NegativeSeq, &g_sLangTxt_Native_NegativeSeq);
	rs_AddString(g_sLangID_Native_PonovoRLO, &g_sLangTxt_Native_PonovoRLO);
	rs_AddString(g_sLangID_Native_RLOtest, &g_sLangTxt_Native_RLOtest);
	rs_AddString(g_sLangID_Native_LowVoltage, &g_sLangTxt_Native_LowVoltage);
	rs_AddString(g_sLangID_Native_NegSeqVol, &g_sLangTxt_Native_NegSeqVol);
	rs_AddString(g_sLangID_Native_ActCurrent, &g_sLangTxt_Native_ActCurrent);
	rs_AddString(g_sLangID_Native_ActAreaSize, &g_sLangTxt_Native_ActAreaSize);

	rs_AddString(g_sLangID_Native_LowVolTriVal, &g_sLangTxt_Native_LowVolTriVal);
	rs_AddString(g_sLangID_Native_NegSeqVolTriVal, &g_sLangTxt_Native_NegSeqVolTriVal);
	rs_AddString(g_sLangID_Native_CurOperC, &g_sLangTxt_Native_CurOperC);
	rs_AddString(g_sLangID_Native_CurOperB, &g_sLangTxt_Native_CurOperB);
	rs_AddString(g_sLangID_Native_CurOperA, &g_sLangTxt_Native_CurOperA);
	rs_AddString(g_sLangID_Native_MaxSensAngTest, &g_sLangTxt_Native_MaxSensAngTest);
	rs_AddString(g_sLangID_Native_CurOperVal, &g_sLangTxt_Native_CurOperVal);
	rs_AddString(g_sLangID_Native_AnBShortCir, &g_sLangTxt_Native_AnBShortCir);
	rs_AddString(g_sLangID_Native_BnCShortCir, &g_sLangTxt_Native_BnCShortCir);
	rs_AddString(g_sLangID_Native_CnAShortCir, &g_sLangTxt_Native_CnAShortCir);
	rs_AddString(g_sLangID_Native_ShortBCVolAndACur, &g_sLangTxt_Native_ShortBCVolAndACur);
	rs_AddString(g_sLangID_Native_ShortCAVolAndBCur, &g_sLangTxt_Native_ShortCAVolAndBCur);
	rs_AddString(g_sLangID_Native_ShortABVolAndCCur, &g_sLangTxt_Native_ShortABVolAndCCur);
	rs_AddString(g_sLangID_Native_ABCSC, &g_sLangTxt_Native_ABCSC);
	rs_AddString(g_sLangID_Native_RLOTestAno, &g_sLangTxt_Native_RLOTestAno);
	rs_AddString(g_sLangID_Native_BoundaryAngle, &g_sLangTxt_Native_BoundaryAngle);

	rs_AddString(g_sLangID_Native_ImpedanceAngle, &g_sLangTxt_Native_ImpedanceAngle);
	rs_AddString(g_sLangID_Native_InitofVarV, &g_sLangTxt_Native_InitofVarV);
	rs_AddString(g_sLangID_Native_FinalofVarV, &g_sLangTxt_Native_FinalofVarV);
	rs_AddString(g_sLangID_Native_StepofVarV, &g_sLangTxt_Native_StepofVarV);
	rs_AddString(g_sLangID_Native_InitofVarA, &g_sLangTxt_Native_InitofVarA);
	rs_AddString(g_sLangID_Native_FinalofVarA, &g_sLangTxt_Native_FinalofVarA);
	rs_AddString(g_sLangID_Native_StepofVarA, &g_sLangTxt_Native_StepofVarA);
	rs_AddString(g_sLangID_Native_ShortCircuitV, &g_sLangTxt_Native_ShortCircuitV);

	// zero
	rs_AddString(g_sLangID_Native_ZeroSeqTF, &g_sLangTxt_Native_ZeroSeqTF);
	rs_AddString(g_sLangID_Native_WelUseZeroSeq, &g_sLangTxt_Native_WelUseZeroSeq);
	rs_AddString(g_sLangID_Native_PonovoZS, &g_sLangTxt_Native_PonovoZS);
	rs_AddString(g_sLangID_Native_ZeroSeqTest, &g_sLangTxt_Native_ZeroSeqTest);
	rs_AddString(g_sLangID_Native_ZeroSeqStageI, &g_sLangTxt_Native_ZeroSeqStageI);
	rs_AddString(g_sLangID_Native_ZeroSeqStageII, &g_sLangTxt_Native_ZeroSeqStageII);
	rs_AddString(g_sLangID_Native_ZeroSeqStageIII, &g_sLangTxt_Native_ZeroSeqStageIII);
	rs_AddString(g_sLangID_Native_ZeroSeqStageIV, &g_sLangTxt_Native_ZeroSeqStageIV);
	rs_AddString(g_sLangID_Native_ZeroSeqStageV, &g_sLangTxt_Native_ZeroSeqStageV);
	rs_AddString(g_sLangID_Native_ZeroSeqWrH, &g_sLangTxt_Native_ZeroSeqWrH);
	rs_AddString(g_sLangID_Native_ZeroSeqWrD, &g_sLangTxt_Native_ZeroSeqWrD);
	rs_AddString(g_sLangID_Native_ZeroSeqWrDH, &g_sLangTxt_Native_ZeroSeqWrDH);
	rs_AddString(g_sLangID_Native_TestOFZeroSeq, &g_sLangTxt_Native_TestOFZeroSeq);
	rs_AddString(g_sLangID_Native_TestofProSet, &g_sLangTxt_Native_TestofProSet);
	rs_AddString(g_sLangID_Native_ThrPhaseJump, &g_sLangTxt_Native_ThrPhaseJump);
	rs_AddString(g_sLangID_Native_Reclosing, &g_sLangTxt_Native_Reclosing);
	rs_AddString(g_sLangID_Native_PostAcceleration, &g_sLangTxt_Native_PostAcceleration);

	// CBO
	rs_AddString(g_sLangID_Native_UnitProTF, &g_sLangTxt_Native_UnitProTF);
	rs_AddString(g_sLangID_Native_PonovoGroupTra, &g_sLangTxt_Native_PonovoGroupTra);
	rs_AddString(g_sLangID_Native_WelUseGroTra, &g_sLangTxt_Native_WelUseGroTra);
	rs_AddString(g_sLangID_Native_GroupTra, &g_sLangTxt_Native_GroupTra);
	rs_AddString(g_sLangID_Native_ImpAng, &g_sLangTxt_Native_ImpAng);
	rs_AddString(g_sLangID_Native_NameGroTest, &g_sLangTxt_Native_NameGroTest);
	rs_AddString(g_sLangID_Native_TestPara, &g_sLangTxt_Native_TestPara);
	rs_AddString(g_sLangID_Native_Initial, &g_sLangTxt_Native_Initial);
	rs_AddString(g_sLangID_Native_Selected, &g_sLangTxt_Native_Selected);
	rs_AddString(g_sLangID_Native_EndTest, &g_sLangTxt_Native_EndTest);

	rs_AddString(g_sLangID_Native_TransientTime, &g_sLangTxt_Native_TransientTime);
	rs_AddString(g_sLangID_Native_TransientMalfDir, &g_sLangTxt_Native_TransientMalfDir);

	rs_AddString(g_sLangID_Native_RPAProTestTF, &g_sLangTxt_Native_RPAProTestTF);
	rs_AddString(g_sLangID_Native_RPAWro1, &g_sLangTxt_Native_RPAWro1);
	rs_AddString(g_sLangID_Native_RPAWro2, &g_sLangTxt_Native_RPAWro2);
	rs_AddString(g_sLangID_Native_RPAWro3, &g_sLangTxt_Native_RPAWro3);
	rs_AddString(g_sLangID_Native_RPAWro4, &g_sLangTxt_Native_RPAWro4);
	rs_AddString(g_sLangID_Native_RPAWro5, &g_sLangTxt_Native_RPAWro5);
	rs_AddString(g_sLangID_Native_RPATest, &g_sLangTxt_Native_RPATest);
	rs_AddString(g_sLangID_Native_WelUseRPATest, &g_sLangTxt_Native_WelUseRPATest);

	rs_AddString(g_sLangID_Native_RCTimeLim, &g_sLangTxt_Native_RCTimeLim);
	rs_AddString(g_sLangID_Native_ZeroVolThr, &g_sLangTxt_Native_ZeroVolThr);
	rs_AddString(g_sLangID_Native_VolDetThr, &g_sLangTxt_Native_VolDetThr);
	rs_AddString(g_sLangID_Native_SynAngDet, &g_sLangTxt_Native_SynAngDet);
	rs_AddString(g_sLangID_Native_CalZeroSeq, &g_sLangTxt_Native_CalZeroSeq);
	rs_AddString(g_sLangID_Native_ChinOr, &g_sLangTxt_Native_ChinOr);
	rs_AddString(g_sLangID_Native_TestRPA, &g_sLangTxt_Native_TestRPA);
	rs_AddString(g_sLangID_Native_PermanentFau, &g_sLangTxt_Native_PermanentFau);
	rs_AddString(g_sLangID_Native_TransientFau, &g_sLangTxt_Native_TransientFau);
	rs_AddString(g_sLangID_Native_MustCho, &g_sLangTxt_Native_MustCho);
	rs_AddString(g_sLangID_Native_SyncCheck, &g_sLangTxt_Native_SyncCheck);
	rs_AddString(g_sLangID_Native_LineNoVolParD, &g_sLangTxt_Native_LineNoVolParD);
	rs_AddString(g_sLangID_Native_LineHasVolParN, &g_sLangTxt_Native_LineHasVolParN);
	rs_AddString(g_sLangID_Native_LineNoVolParT, &g_sLangTxt_Native_LineNoVolParT);
	rs_AddString(g_sLangID_Native_LineHasVolParT, &g_sLangTxt_Native_LineHasVolParT);
	rs_AddString(g_sLangID_Native_NoOutput, &g_sLangTxt_Native_NoOutput);
	rs_AddString(g_sLangID_Native_KOorReKO, &g_sLangTxt_Native_KOorReKO);
	rs_AddString(g_sLangID_Native_PhiOrIm, &g_sLangTxt_Native_PhiOrIm);
	// 许文迪第二周
	rs_AddString(g_sLangID_Native_FaultReplayTF, &g_sLangTxt_Native_FaultReplayTF);
	rs_AddString(g_sLangID_Native_EnfSetAnalog, &g_sLangTxt_Native_EnfSetAnalog);
	rs_AddString(g_sLangID_Native_WelUseFaultRe, &g_sLangTxt_Native_WelUseFaultRe);
	rs_AddString(g_sLangID_Native_WavePlayback, &g_sLangTxt_Native_WavePlayback);
	rs_AddString(g_sLangID_Native_PreWaveData, &g_sLangTxt_Native_PreWaveData);
	rs_AddString(g_sLangID_Native_NextWaveData, &g_sLangTxt_Native_NextWaveData);
	rs_AddString(g_sLangID_Native_MalfunctionRe, &g_sLangTxt_Native_MalfunctionRe);
	rs_AddString(g_sLangID_Native_OpenWaveFile, &g_sLangTxt_Native_OpenWaveFile);
	rs_AddString(g_sLangID_Native_DownloadWaveData, &g_sLangTxt_Native_DownloadWaveData);
	rs_AddString(g_sLangID_Native_FaultReplayWr3, &g_sLangTxt_Native_FaultReplayWr3);
	rs_AddString(g_sLangID_Native_FaultReplayWr4, &g_sLangTxt_Native_FaultReplayWr4);
	rs_AddString(g_sLangID_Native_TransfRatio, &g_sLangTxt_Native_TransfRatio);
	rs_AddString(g_sLangID_Native_AChannelDesError, &g_sLangTxt_Native_AChannelDesError);
	rs_AddString(g_sLangID_Native_BChannelDesError, &g_sLangTxt_Native_BChannelDesError);

	rs_AddString(g_sLangID_Native_SITmpl, &g_sLangTxt_Native_SITmpl);
	rs_AddString(g_sLangID_Native_SIWelcome, &g_sLangTxt_Native_SIWelcome);
	rs_AddString(g_sLangID_Native_SIPonovo, &g_sLangTxt_Native_SIPonovo);
	rs_AddString(g_sLangID_Native_SITest, &g_sLangTxt_Native_SITest);
	rs_AddString(g_sLangID_Native_SISearch, &g_sLangTxt_Native_SISearch);
	rs_AddString(g_sLangID_Native_ConfigFileNotExist, &g_sLangTxt_Native_ConfigFileNotExist);
	rs_AddString(g_sLangID_Native_SelectFaultType, &g_sLangTxt_Native_SelectFaultType);
	rs_AddString(g_sLangID_Native_ImpedanceAngleStart, &g_sLangTxt_Native_ImpedanceAngleStart);
	rs_AddString(g_sLangID_Native_ImpedanceAngleEnd, &g_sLangTxt_Native_ImpedanceAngleEnd);
	rs_AddString(g_sLangID_Native_AngleChangeStep, &g_sLangTxt_Native_AngleChangeStep);
	rs_AddString(g_sLangID_Native_WelcomeSeq, &g_sLangTxt_Native_WelcomeSeq);
	rs_AddString(g_sLangID_Native_StateSeq, &g_sLangTxt_Native_StateSeq);

	rs_AddString(g_sLangID_Native_StateSeqStatus, &g_sLangTxt_Native_StateSeqStatus);
	rs_AddString(g_sLangID_Native_SelectedStateNumExceed, &g_sLangTxt_Native_SelectedStateNumExceed);

	rs_AddString(g_sLangID_Native_Exit, &g_sLangTxt_Native_Exit);
	rs_AddString(g_sLangID_Native_TrigTimeS, &g_sLangTxt_Native_TrigTimeS);

	rs_AddString(g_sLangID_Native_OutOneState, &g_sLangTxt_Native_OutOneState);
	rs_AddString(g_sLangID_Native_OutTwoState, &g_sLangTxt_Native_OutTwoState);
	rs_AddString(g_sLangID_Native_OutThreeState, &g_sLangTxt_Native_OutThreeState);
	rs_AddString(g_sLangID_Native_OutFourState, &g_sLangTxt_Native_OutFourState);
	rs_AddString(g_sLangID_Native_OutFiveState, &g_sLangTxt_Native_OutFiveState);
	rs_AddString(g_sLangID_Native_OutSixState, &g_sLangTxt_Native_OutSixState);
	rs_AddString(g_sLangID_Native_OutSevenState, &g_sLangTxt_Native_OutSevenState);
	rs_AddString(g_sLangID_Native_OutEightState, &g_sLangTxt_Native_OutEightState);
	rs_AddString(g_sLangID_Native_InAActTime, &g_sLangTxt_Native_InAActTime);
	rs_AddString(g_sLangID_Native_InBActTime, &g_sLangTxt_Native_InBActTime);
	rs_AddString(g_sLangID_Native_InCActTime, &g_sLangTxt_Native_InCActTime);
	rs_AddString(g_sLangID_Native_InDActTime, &g_sLangTxt_Native_InDActTime);
	rs_AddString(g_sLangID_Native_InEActTime, &g_sLangTxt_Native_InEActTime);
	rs_AddString(g_sLangID_Native_InFActTime, &g_sLangTxt_Native_InFActTime);
	rs_AddString(g_sLangID_Native_InGActTime, &g_sLangTxt_Native_InGActTime);
	rs_AddString(g_sLangID_Native_InHActTime, &g_sLangTxt_Native_InHActTime);

	rs_AddString(g_sLangID_Native_OutputState, &g_sLangTxt_Native_OutputState);
	rs_AddString(g_sLangID_Native_UnknownTrigger, &g_sLangTxt_Native_UnknownTrigger);
	rs_AddString(g_sLangID_Native_InputOutOfRange, &g_sLangTxt_Native_InputOutOfRange);
	rs_AddString(g_sLangID_Native_TestList, &g_sLangTxt_Native_TestList);
	rs_AddString(g_sLangID_Native_TestResult, &g_sLangTxt_Native_TestResult);
	rs_AddString(g_sLangID_Native_AddState, &g_sLangTxt_Native_AddState);
	rs_AddString(g_sLangID_Native_DelState, &g_sLangTxt_Native_DelState);
	rs_AddString(g_sLangID_Native_DelN1, &g_sLangTxt_Native_DelN1);
	rs_AddString(g_sLangID_Native_PhaseAngle, &g_sLangTxt_Native_PhaseAngle);
	rs_AddString(g_sLangID_Native_SVAbnSim, &g_sLangTxt_Native_SVAbnSim);

	// ManualTest_Trans 马嘉骅第二周
	rs_AddString(g_sLangID_Native_WelcomeGenTest, &g_sLangTxt_Native_WelcomeGenTest); /*_T("欢迎使用通用试验.")*/
	rs_AddString(g_sLangID_Native_blankGenTest, &g_sLangTxt_Native_blankGenTest);	  /*_T(" 通用试验")*/
	rs_AddString(g_sLangID_Native_InputSetExt, &g_sLangTxt_Native_InputSetExt);		  /*tr("开入设置(扩展)")*/
	rs_AddString(g_sLangID_Native_OutputSetExt, &g_sLangTxt_Native_OutputSetExt);	  /*tr("开出设置(扩展)")*/
	rs_AddString(g_sLangID_Native_ActValuePar, &g_sLangTxt_Native_ActValuePar);		  /*tr("动作值(")*/
	rs_AddString(g_sLangID_Native_BrackColon, &g_sLangTxt_Native_BrackColon);		  /*tr("):")*/
	rs_AddString(g_sLangID_Native_ReturnValuePar, &g_sLangTxt_Native_ReturnValuePar); /*tr("返回值(")*/
	rs_AddString(g_sLangID_Native_InitialValPar, &g_sLangTxt_Native_InitialValPar);	  /*tr("始值(")*/
	rs_AddString(g_sLangID_Native_EndValPar, &g_sLangTxt_Native_EndValPar);			  /*tr("终值(")*/
	rs_AddString(g_sLangID_Native_StepSizePar, &g_sLangTxt_Native_StepSizePar);		  /*tr("步长(")*/
	rs_AddString(g_sLangID_Native_OpenSett, &g_sLangTxt_Native_OpenSett);			  // 开出设置及返回结果
	rs_AddString(g_sLangID_Native_DCUAB, &g_sLangTxt_Native_DCUAB);					  // 直流UAB

	// OscillationTest_Trans 马
	rs_AddString(g_sLangID_Native_OscilTestTemp, &g_sLangTxt_Native_OscilTestTemp);	  /*tr("振荡试验模板文件")*/
	rs_AddString(g_sLangID_Native_WelcomeOscTest, &g_sLangTxt_Native_WelcomeOscTest); /*_T("欢迎使用振荡试验.")*/
	rs_AddString(g_sLangID_Native_PonovoOscTest, &g_sLangTxt_Native_PonovoOscTest);	  /*tr("Ponovo 振荡试验")*/
	rs_AddString(g_sLangID_Native_OscilTest, &g_sLangTxt_Native_OscilTest);			  /*tr("振荡试验")*/
	rs_AddString(g_sLangID_Native_AngleOscil, &g_sLangTxt_Native_AngleOscil);		  /*QObject::tr("功角振荡")*/
	rs_AddString(g_sLangID_Native_Oscillation, &g_sLangTxt_Native_Oscillation);		  /*"振荡"*/
	rs_AddString(g_sLangID_Native_TestParams, &g_sLangTxt_Native_TestParams);		  /*测试参数*/
	rs_AddString(g_sLangID_Native_AngleStartPar, &g_sLangTxt_Native_AngleStartPar);	  /*功角始值(°)*/
	rs_AddString(g_sLangID_Native_AngleEndPar, &g_sLangTxt_Native_AngleEndPar);		  /*功角终值(°)*/
	rs_AddString(g_sLangID_Native_OscilPeriod, &g_sLangTxt_Native_OscilPeriod);		  /*振荡周期(s)*/
	rs_AddString(g_sLangID_Native_TripContacts, &g_sLangTxt_Native_TripContacts);	  /*跳闸接点*/
	rs_AddString(g_sLangID_Native_OscilReFault, &g_sLangTxt_Native_OscilReFault);	  /*振荡中再故障*/
	rs_AddString(g_sLangID_Native_ImpedSlipRamp, &g_sLangTxt_Native_ImpedSlipRamp);	  /*使用阻抗滑差递变方式*/
	rs_AddString(g_sLangID_Native_RecipOsc, &g_sLangTxt_Native_RecipOsc);			  /*往复振荡*/
	rs_AddString(g_sLangID_Native_AccelOsc, &g_sLangTxt_Native_AccelOsc);			  /*增速振荡*/

	rs_AddString(g_sLangID_Native_FaultTime, &g_sLangTxt_Native_FaultTime);				/*故障发生时刻*/
	rs_AddString(g_sLangID_Native_ResultName, &g_sLangTxt_Native_ResultName);			/*结果名称*/
	rs_AddString(g_sLangID_Native_ProtRelayTime, &g_sLangTxt_Native_ProtRelayTime);		/*保护出口时间(s)*/
	rs_AddString(g_sLangID_Native_AccelSigOutTime, &g_sLangTxt_Native_AccelSigOutTime); /*加速信号出口时间(s)*/
	rs_AddString(g_sLangID_Native_DecelSigOutTime, &g_sLangTxt_Native_DecelSigOutTime); /*减速信号出口时间(s)*/
	rs_AddString(g_sLangID_Native_ProtOutTimePar, &g_sLangTxt_Native_ProtOutTimePar);	/*tr("保护出口时间=")*/
	rs_AddString(g_sLangID_Native_AccelTimePar, &g_sLangTxt_Native_AccelTimePar);		/*tr("加速信号时间=")*/
	rs_AddString(g_sLangID_Native_DecelTimePar, &g_sLangTxt_Native_DecelTimePar);		/*tr("减速信号时间=")*/
	rs_AddString(g_sLangID_Native_GenTranReact, &g_sLangTxt_Native_GenTranReact);		// 发电机暂态电抗
	rs_AddString(g_sLangID_Native_ExprMethod, &g_sLangTxt_Native_ExprMethod);			// 表达方式
	rs_AddString(g_sLangID_Native_RateIncr, &g_sLangTxt_Native_RateIncr);				// 增速
	rs_AddString(g_sLangID_Native_Decel, &g_sLangTxt_Native_Decel);						// 减速

	// OverCurrentTest_Trans 马
	rs_AddString(g_sLangID_Native_OvrCurrTestTemp, &g_sLangTxt_Native_OvrCurrTestTemp);		  /*tr("过流试验模板文件")*/
	rs_AddString(g_sLangID_Native_WelcomeOvrCurrTest, &g_sLangTxt_Native_WelcomeOvrCurrTest); /*_T("欢迎使用过流测试.")*/
	rs_AddString(g_sLangID_Native_OvrCurr, &g_sLangTxt_Native_OvrCurr);						  /*tr("过流")*/
	rs_AddString(g_sLangID_Native_TimeChart, &g_sLangTxt_Native_TimeChart);					  /*tr("时间特性图")*/
	rs_AddString(g_sLangID_Native_OvrCurrIAct, &g_sLangTxt_Native_OvrCurrIAct);				  /*_T("过流I段动作值")*/
	rs_AddString(g_sLangID_Native_OvrCurrIIAct, &g_sLangTxt_Native_OvrCurrIIAct);			  /*_T("过流II段动作值")*/
	rs_AddString(g_sLangID_Native_OvrCurrIIIAct, &g_sLangTxt_Native_OvrCurrIIIAct);			  /*_T("过流III段动作值")*/
	rs_AddString(g_sLangID_Native_OvrCurrIVAct, &g_sLangTxt_Native_OvrCurrIVAct);			  /*_T("过流IV段动作值")*/
	rs_AddString(g_sLangID_Native_OvrCurrVAct, &g_sLangTxt_Native_OvrCurrVAct);				  /*_T("过流V段动作值")*/
	rs_AddString(g_sLangID_Native_OvrCurrITime, &g_sLangTxt_Native_OvrCurrITime);			  /*_T("过流I段动作时间")*/
	rs_AddString(g_sLangID_Native_OvrCurrIITime, &g_sLangTxt_Native_OvrCurrIITime);			  /*_T("过流II段动作时间")*/
	rs_AddString(g_sLangID_Native_OvrCurrIIITime, &g_sLangTxt_Native_OvrCurrIIITime);		  /*_T("过流III段动作时间")*/
	rs_AddString(g_sLangID_Native_OvrCurrIVTime, &g_sLangTxt_Native_OvrCurrIVTime);			  /*_T("过流IV段动作时间")*/
	rs_AddString(g_sLangID_Native_OvrCurrVTime, &g_sLangTxt_Native_OvrCurrVTime);			  /*_T("过流V段动作时间")*/

	rs_AddString(g_sLangID_Native_TestNameOvrCurr, &g_sLangTxt_Native_TestNameOvrCurr);		  /*"<h1>试验名称：过流保护定值测试</h1>"*/
	rs_AddString(g_sLangID_Native_OvrCurrIProtTest, &g_sLangTxt_Native_OvrCurrIProtTest);	  /*"过流I段保护定值测试"*/
	rs_AddString(g_sLangID_Native_OvrCurrIIProtTest, &g_sLangTxt_Native_OvrCurrIIProtTest);	  /*"过流II段保护定值测试"*/
	rs_AddString(g_sLangID_Native_OvrCurrIIIProtTest, &g_sLangTxt_Native_OvrCurrIIIProtTest); /*"过流III段保护定值测试"*/
	rs_AddString(g_sLangID_Native_OvrCurrIVProtTest, &g_sLangTxt_Native_OvrCurrIVProtTest);	  /*"过流IV段保护定值测试"*/
	rs_AddString(g_sLangID_Native_OvrCurrVProtTest, &g_sLangTxt_Native_OvrCurrVProtTest);	  /*"过流V段保护定值测试"*/
	rs_AddString(g_sLangID_Native_DefaultIset1, &g_sLangTxt_Native_DefaultIset1);			  /*tr("默认值 = Iset1")*/
	rs_AddString(g_sLangID_Native_DefaultIset2, &g_sLangTxt_Native_DefaultIset2);			  /*tr("默认值 = Iset2")*/
	rs_AddString(g_sLangID_Native_DefaultIset3, &g_sLangTxt_Native_DefaultIset3);			  /*tr("默认值 = Iset3")*/
	rs_AddString(g_sLangID_Native_DefaultIset4, &g_sLangTxt_Native_DefaultIset4);			  /*tr("默认值 = Iset4")*/
	rs_AddString(g_sLangID_Native_DefaultIset5, &g_sLangTxt_Native_DefaultIset5);			  /*tr("默认值 = Iset5")*/
	rs_AddString(g_sLangID_Native_DefaultTset1, &g_sLangTxt_Native_DefaultTset1);			  /*tr("默认值 = Tset1")*/
	rs_AddString(g_sLangID_Native_DefaultTset2, &g_sLangTxt_Native_DefaultTset2);			  /*tr("默认值 = Tset2")*/
	rs_AddString(g_sLangID_Native_DefaultTset3, &g_sLangTxt_Native_DefaultTset3);			  /*tr("默认值 = Tset3")*/
	rs_AddString(g_sLangID_Native_DefaultTset4, &g_sLangTxt_Native_DefaultTset4);			  /*tr("默认值 = Tset4")*/
	rs_AddString(g_sLangID_Native_DefaultTset5, &g_sLangTxt_Native_DefaultTset5);			  /*tr("默认值 = Tset5")*/
	rs_AddString(g_sLangID_Native_PhaseABC, &g_sLangTxt_Native_PhaseABC);					  /*tr("ABC相")*/
	rs_AddString(g_sLangID_Native_Or, &g_sLangTxt_Native_Or);								  /*tr("或")*/
	rs_AddString(g_sLangID_Native_And, &g_sLangTxt_Native_And);								  /*tr("与")*/
	rs_AddString(g_sLangID_Native_SimDisconn, &g_sLangTxt_Native_SimDisconn);				  // 模拟PT断线

	rs_AddString(g_sLangID_Native_OpenPh, &g_sLangTxt_Native_OpenPh); // PT断线相

	// Gradient 吕洋第二周
	//  吕
	rs_AddString(g_sLangID_Native_DistProtect_TempFile, &g_sLangTxt_Native_DistProtect_TempFile); // 距离保护模板文件
	rs_AddString(g_sLangID_Native_Wel_DisProtect, &g_sLangTxt_Native_Wel_DisProtect);			  // 欢迎使用距离保护.
	rs_AddString(g_sLangID_Native_PonovoDisProtect, &g_sLangTxt_Native_PonovoDisProtect);		  // Ponovo 距离保护
	rs_AddString(g_sLangID_Native_DisProtect, &g_sLangTxt_Native_DisProtect);					  // 距离保护
	rs_AddString(g_sLangID_Native_multiple, &g_sLangTxt_Native_multiple);						  // 倍,R=
	rs_AddString(g_sLangID_Native_Para, &g_sLangTxt_Native_Para);								  // 段
	rs_AddString(g_sLangID_Native_GroundFaultI, &g_sLangTxt_Native_GroundFaultI);
	rs_AddString(g_sLangID_Native_GroundFaultII, &g_sLangTxt_Native_GroundFaultII);
	rs_AddString(g_sLangID_Native_GroundFaultIII, &g_sLangTxt_Native_GroundFaultIII);
	rs_AddString(g_sLangID_Native_GroundFaultIV, &g_sLangTxt_Native_GroundFaultIV);
	rs_AddString(g_sLangID_Native_GroundFaultV, &g_sLangTxt_Native_GroundFaultV); // 接地故障1-5段
	rs_AddString(g_sLangID_Native_PhaseFaultI, &g_sLangTxt_Native_PhaseFaultI);
	rs_AddString(g_sLangID_Native_PhaseFaultII, &g_sLangTxt_Native_PhaseFaultII);
	rs_AddString(g_sLangID_Native_PhaseFaultIII, &g_sLangTxt_Native_PhaseFaultIII);
	rs_AddString(g_sLangID_Native_PhaseFaultIV, &g_sLangTxt_Native_PhaseFaultIV);
	rs_AddString(g_sLangID_Native_PhaseFaultV, &g_sLangTxt_Native_PhaseFaultV);				// 相间故障1-5段
	rs_AddString(g_sLangID_Native_DisProt_SetTest, &g_sLangTxt_Native_DisProt_SetTest);		// 距离保护定值测试
	rs_AddString(g_sLangID_ITOTest_Tempfile, &g_sLangTxt_ITOTest_Tempfile);					// 电流反时限试验模板文件
	rs_AddString(g_sLangID_Wel_ITOTest, &g_sLangTxt_Wel_ITOTest);							// 欢迎使用电流反时限试验
	rs_AddString(g_sLangID_ITOTest, &g_sLangTxt_ITOTest);									// 电流反时限试验
	rs_AddString(g_sLangID_Ponovo_ITOTest, &g_sLangTxt_Ponovo_ITOTest);						// Ponovo 电流反时限试验
	rs_AddString(g_sLangID_Theoretical_ActionTime, &g_sLangTxt_Theoretical_ActionTime);		// 理论动作时间
	rs_AddString(g_sLangID_Native_ITO, &g_sLangTxt_Native_ITO);								// 电流反时限
	rs_AddString(g_sLangID_Single_PhaseGround_Fault, &g_sLangTxt_Single_PhaseGround_Fault); // 单项接地故障
	rs_AddString(g_sLangID_Directional_LineSide, &g_sLangTxt_Directional_LineSide);			// 指向线路侧
	rs_AddString(g_sLangID_Directional_BusSide, &g_sLangTxt_Directional_BusSide);			// 指向母线侧
	rs_AddString(g_sLangID_Add_Series, &g_sLangTxt_Add_Series);								// 添加系列
	rs_AddString(g_sLangID_Delet_Test, &g_sLangTxt_Delet_Test);								// 删除试验
	rs_AddString(g_sLangID_Clear_Results, &g_sLangTxt_Clear_Results);						// 清除结果
	rs_AddString(g_sLangID_Clear_All, &g_sLangTxt_Clear_All);								// 清除所有
	rs_AddString(g_sLangID_Test_Parameters, &g_sLangTxt_Test_Parameters);					// 试验参数

	rs_AddString(g_sLangID_Native_Wel_IncreExper, &g_sLangTxt_Native_Wel_IncreExper); // 欢迎使用递变测试.
	rs_AddString(g_sLangID_Native_PonovoIncre, &g_sLangTxt_Native_PonovoIncre);		  // Ponovo递变
	rs_AddString(g_sLangID_Native_IncreExper, &g_sLangTxt_Native_IncreExper);		  // 递变实验
	rs_AddString(g_sLangID_Native_ImpedanceSet, &g_sLangTxt_Native_ImpedanceSet);	  // 阻抗定值(Ω)：
	rs_AddString(g_sLangID_Native_PrepareTime, &g_sLangTxt_Native_PrepareTime);	  // 变化前时间(s)

	rs_AddString(g_sLangID_Native_PreCurrent, &g_sLangTxt_Native_PreCurrent);		// 变化前电流幅值(A)
	rs_AddString(g_sLangID_Native_PreAngle, &g_sLangTxt_Native_PreAngle);			// 故障前电压电流相角(°)
	rs_AddString(g_sLangID_TestItem1, &g_sLangTxt_TestItem1);						// 测试项一
	rs_AddString(g_sLangID_Native_InputAction, &g_sLangTxt_Native_InputAction);		// 开入%1，动作值：%2
	rs_AddString(g_sLangID_Native_ExInputAction, &g_sLangTxt_Native_ExInputAction); // 扩展开入%1，动作值：%2

	rs_AddString(g_sLangID_Native_NormalOutpExSet, &g_sLangTxt_Native_NormalOutpExSet); // 常态开出设置（扩展）
	rs_AddString(g_sLangID_Native_FaultOutpExSet, &g_sLangTxt_Native_FaultOutpExSet);	// 故障态开出设置(扩展)
	rs_AddString(g_sLangID_Native_All, &g_sLangTxt_Native_All);							// 全部
	rs_AddString(g_sLangID_Experiment, &g_sLangTxt_Experiment);							// 试验
	rs_AddString(g_sLangID_Native_InitofVarP, &g_sLangTxt_Native_InitofVarP);			// 变化始值(°):
	rs_AddString(g_sLangID_Native_FinalofVarP, &g_sLangTxt_Native_FinalofVarP);			// 变化终值(°)：
	rs_AddString(g_sLangID_Native_StepofVarP, &g_sLangTxt_Native_StepofVarP);			// 变化步长(°)：
	rs_AddString(g_sLangID_Native_InitofVarF, &g_sLangTxt_Native_InitofVarF);			// 变化始值(Hz):
	rs_AddString(g_sLangID_Native_FinalofVarF, &g_sLangTxt_Native_FinalofVarF);			// 变化终值(Hz)：
	rs_AddString(g_sLangID_Native_StepofVarF, &g_sLangTxt_Native_StepofVarF);			// 变化步长(Hz)：

	// xwd 第三周
	rs_AddString(g_sLangID_Native_TracVarTestTpl, &g_sLangTxt_Native_TracVarTestTpl);
	rs_AddString(g_sLangID_Native_WelcTracVarTest, &g_sLangTxt_Native_WelcTracVarTest);
	rs_AddString(g_sLangID_Native_PonTracVar, &g_sLangTxt_Native_PonTracVar);
	rs_AddString(g_sLangID_Native_TracVar, &g_sLangTxt_Native_TracVar);
	rs_AddString(g_sLangID_Native_FaultTimes, &g_sLangTxt_Native_FaultTimes);
	rs_AddString(g_sLangID_Native_HLCTPolarDef, &g_sLangTxt_Native_HLCTPolarDef);

	rs_AddString(g_sLangID_Native_SetValueName, &g_sLangTxt_Native_SetValueName);
	rs_AddString(g_sLangID_Native_DiffQBrkCurrSetValue, &g_sLangTxt_Native_DiffQBrkCurrSetValue);
	rs_AddString(g_sLangID_Native_DiffActCurrThresh, &g_sLangTxt_Native_DiffActCurrThresh);
	rs_AddString(g_sLangID_Native_RatioBrkInflect1Curr, &g_sLangTxt_Native_RatioBrkInflect1Curr);
	rs_AddString(g_sLangID_Native_RatioBrkInflect2Curr, &g_sLangTxt_Native_RatioBrkInflect2Curr);
	rs_AddString(g_sLangID_Native_SettingMode, &g_sLangTxt_Native_SettingMode);
	rs_AddString(g_sLangID_Native_HvCTPolarity, &g_sLangTxt_Native_HvCTPolarity);

	rs_AddString(g_sLangID_Native_PreChangeTime, &g_sLangTxt_Native_PreChangeTime);
	rs_AddString(g_sLangID_Native_PreFaultTimes, &g_sLangTxt_Native_PreFaultTimes);
	rs_AddString(g_sLangID_Native_NormalVoltAmp, &g_sLangTxt_Native_NormalVoltAmp);
	rs_AddString(g_sLangID_Native_NormalVoltPhase, &g_sLangTxt_Native_NormalVoltPhase);
	rs_AddString(g_sLangID_Native_NormalCurrAmp, &g_sLangTxt_Native_NormalCurrAmp);
	rs_AddString(g_sLangID_Native_NormalCurrPhase, &g_sLangTxt_Native_NormalCurrPhase);
	rs_AddString(g_sLangID_Native_NormalPhaseAngle, &g_sLangTxt_Native_NormalPhaseAngle);
	rs_AddString(g_sLangID_Native_FaultMode, &g_sLangTxt_Native_FaultMode);
	rs_AddString(g_sLangID_Native_ChangeAmount, &g_sLangTxt_Native_ChangeAmount);

	rs_AddString(g_sLangID_Native_ShortCircuitAs, &g_sLangTxt_Native_ShortCircuitAs);
	rs_AddString(g_sLangID_Native_FrequencyHz, &g_sLangTxt_Native_FrequencyHz);
	rs_AddString(g_sLangID_Native_RecordQty, &g_sLangTxt_Native_RecordQty);
	rs_AddString(g_sLangID_Native_StepTimeS, &g_sLangTxt_Native_StepTimeS);
	rs_AddString(g_sLangID_Native_SetValueA, &g_sLangTxt_Native_SetValueA);
	rs_AddString(g_sLangID_Native_SetActTimeS, &g_sLangTxt_Native_SetActTimeS);

	rs_AddString(g_sLangID_Native_SectionI, &g_sLangTxt_Native_SectionI);
	rs_AddString(g_sLangID_Native_SectionII, &g_sLangTxt_Native_SectionII);
	rs_AddString(g_sLangID_Native_SectionIII, &g_sLangTxt_Native_SectionIII);
	rs_AddString(g_sLangID_Native_SectionIV, &g_sLangTxt_Native_SectionIV);
	rs_AddString(g_sLangID_Native_SectionV, &g_sLangTxt_Native_SectionV);
	rs_AddString(g_sLangID_Native_FaultDir, &g_sLangTxt_Native_FaultDir);
	rs_AddString(g_sLangID_Native_Confirm, &g_sLangTxt_Native_Confirm);
	rs_AddString(g_sLangID_Native_Name, &g_sLangTxt_Native_Name);
	rs_AddString(g_sLangID_Native_ZeroSeqCurr, &g_sLangTxt_Native_ZeroSeqCurr);
	rs_AddString(g_sLangID_Native_FaultTriggerTime, &g_sLangTxt_Native_FaultTriggerTime);
	rs_AddString(g_sLangID_Native_Multiples, &g_sLangTxt_Native_Multiples);
	rs_AddString(g_sLangID_Native_SetActTime, &g_sLangTxt_Native_SetActTime);
	rs_AddString(g_sLangID_Native_LoadCurrent, &g_sLangTxt_Native_LoadCurrent);
	rs_AddString(g_sLangID_Native_LoadPowerAngle, &g_sLangTxt_Native_LoadPowerAngle);
	rs_AddString(g_sLangID_Native_MaxFaultTime, &g_sLangTxt_Native_MaxFaultTime);
	rs_AddString(g_sLangID_Native_TransFault, &g_sLangTxt_Native_TransFault);
	rs_AddString(g_sLangID_Native_TransTime, &g_sLangTxt_Native_TransTime);
	rs_AddString(g_sLangID_Native_FaultTriggerTimes, &g_sLangTxt_Native_FaultTriggerTimes);
	rs_AddString(g_sLangID_Native_GrdDistFixed, &g_sLangTxt_Native_GrdDistFixed);
	rs_AddString(g_sLangID_Native_DistValue, &g_sLangTxt_Native_DistValue);
	rs_AddString(g_sLangID_Native_Impedance, &g_sLangTxt_Native_Impedance);
	rs_AddString(g_sLangID_Native_GrdSetTime, &g_sLangTxt_Native_GrdSetTime);
	rs_AddString(g_sLangID_Native_PhaseSetTime, &g_sLangTxt_Native_PhaseSetTime);
	rs_AddString(g_sLangID_Native_Impedance1, &g_sLangTxt_Native_Impedance1);
	rs_AddString(g_sLangID_Native_Impedance2, &g_sLangTxt_Native_Impedance2);
	rs_AddString(g_sLangID_Native_Impedance3, &g_sLangTxt_Native_Impedance3);
	rs_AddString(g_sLangID_Native_Impedance4, &g_sLangTxt_Native_Impedance4);
	rs_AddString(g_sLangID_Native_Impedance5, &g_sLangTxt_Native_Impedance5);
	rs_AddString(g_sLangID_Native_ReverseDir, &g_sLangTxt_Native_ReverseDir);
	rs_AddString(g_sLangID_Native_ErrorRange, &g_sLangTxt_Native_ErrorRange);
	rs_AddString(g_sLangID_Native_Cancel, &g_sLangTxt_Native_Cancel);
	rs_AddString(g_sLangID_Native_AfterOverlap, &g_sLangTxt_Native_AfterOverlap);
	rs_AddString(g_sLangID_Native_FreqHz, &g_sLangTxt_Native_FreqHz);
	rs_AddString(g_sLangID_Native_VoltSelect, &g_sLangTxt_Native_VoltSelect);
	rs_AddString(g_sLangID_Native_VoltAfterTrip, &g_sLangTxt_Native_VoltAfterTrip);
	rs_AddString(g_sLangID_Native_VoltPhaseAfterTrip, &g_sLangTxt_Native_VoltPhaseAfterTrip);
	rs_AddString(g_sLangID_Native_ChangeStartVal, &g_sLangTxt_Native_ChangeStartVal);
	rs_AddString(g_sLangID_Native_ChangeEndVal, &g_sLangTxt_Native_ChangeEndVal);
	rs_AddString(g_sLangID_Native_ChangeStep, &g_sLangTxt_Native_ChangeStep);
	rs_AddString(g_sLangID_Native_TestPoint, &g_sLangTxt_Native_TestPoint);
	rs_AddString(g_sLangID_Native_FaultTimeS, &g_sLangTxt_Native_FaultTimeS);
	rs_AddString(g_sLangID_Native_SettingModes, &g_sLangTxt_Native_SettingModes);
	rs_AddString(g_sLangID_Native_BaseCurrent, &g_sLangTxt_Native_BaseCurrent);
	rs_AddString(g_sLangID_Native_SearchMethod, &g_sLangTxt_Native_SearchMethod);
	rs_AddString(g_sLangID_Native_CTPolarityDef, &g_sLangTxt_Native_CTPolarityDef);
	rs_AddString(g_sLangID_Native_BrakeEquation, &g_sLangTxt_Native_BrakeEquation);
	rs_AddString(g_sLangID_Native_TestPhase, &g_sLangTxt_Native_TestPhase);
	rs_AddString(g_sLangID_Native_TestAccuracy, &g_sLangTxt_Native_TestAccuracy);
	rs_AddString(g_sLangID_Native_TransConnType, &g_sLangTxt_Native_TransConnType);
	rs_AddString(g_sLangID_Native_DiffCurrent, &g_sLangTxt_Native_DiffCurrent);
	rs_AddString(g_sLangID_Native_BrakeCurrent, &g_sLangTxt_Native_BrakeCurrent);
	rs_AddString(g_sLangID_Native_ManualDiff, &g_sLangTxt_Native_ManualDiff);
	rs_AddString(g_sLangID_Native_ManualAdd, &g_sLangTxt_Native_ManualAdd);
	rs_AddString(g_sLangID_Native_ManualSub, &g_sLangTxt_Native_ManualSub);
	rs_AddString(g_sLangID_Native_BrakeCurrIn, &g_sLangTxt_Native_BrakeCurrIn);
	rs_AddString(g_sLangID_Native_TestType, &g_sLangTxt_Native_TestType);
	rs_AddString(g_sLangID_Native_TestAccIn, &g_sLangTxt_Native_TestAccIn);
	rs_AddString(g_sLangID_Native_SearchUpperLimits, &g_sLangTxt_Native_SearchUpperLimits);
	rs_AddString(g_sLangID_Native_SearchLowerLimits, &g_sLangTxt_Native_SearchLowerLimits);
	rs_AddString(g_sLangID_Native_DiffCurrentId, &g_sLangTxt_Native_DiffCurrentId);
	rs_AddString(g_sLangID_Native_SearchStartValue, &g_sLangTxt_Native_SearchStartValue);
	rs_AddString(g_sLangID_Native_SearchEndValue, &g_sLangTxt_Native_SearchEndValue);
	rs_AddString(g_sLangID_Native_Evaluation, &g_sLangTxt_Native_Evaluation);
	rs_AddString(g_sLangID_Native_Expression, &g_sLangTxt_Native_Expression);
	rs_AddString(g_sLangID_Native_Result, &g_sLangTxt_Native_Result);
	rs_AddString(g_sLangID_Native_DiffCurrents, &g_sLangTxt_Native_DiffCurrents);
	rs_AddString(g_sLangID_Native_ErrorLessThan, &g_sLangTxt_Native_ErrorLessThan);
	rs_AddString(g_sLangID_Native_RelativeErrorLessThan, &g_sLangTxt_Native_RelativeErrorLessThan);
	rs_AddString(g_sLangID_Native_AbsoluteErrorLessThan, &g_sLangTxt_Native_AbsoluteErrorLessThan);

	// Harmtest 吕 第三周
	rs_AddString(g_sLangID_Native_HarmonicTest, &g_sLangTxt_Native_HarmonicTest);				  // 谐波试验
	rs_AddString(g_sLangID_Native_Wel_HarmModTest, &g_sLangTxt_Native_Wel_HarmModTest);			  // 欢迎使用谐波模块试验
	rs_AddString(g_sLangID_Native_Choose_HtesttempFile, &g_sLangTxt_Native_Choose_HtesttempFile); // 选择谐波试验模板文件
	rs_AddString(g_sLangID_Native_saveSuccess, &g_sLangTxt_Native_saveSuccess);					  // 文件保存成功
	rs_AddString(g_sLangID_Native_harmTestTempSaveS, &g_sLangTxt_Native_harmTestTempSaveS);		  // 谐波试验默认模板[%1]保存成功.
	rs_AddString(g_sLangID_Native_harmTestTempSaveF, &g_sLangTxt_Native_harmTestTempSaveF);		  // 谐波试验默认模板[%1]保存失败.
	rs_AddString(g_sLangID_Native_saveFail, &g_sLangTxt_Native_saveFail);						  // 文件保存失败
	rs_AddString(g_sLangID_Native_createMFileFail, &g_sLangTxt_Native_createMFileFail);			  // 创建测试模板文件路径失败
	rs_AddString(g_sLangID_Native_saveAsSuccess, &g_sLangTxt_Native_saveAsSuccess);				  // 模板另存为[%1]成功.
	rs_AddString(g_sLangID_Native_saveAsFail, &g_sLangTxt_Native_saveAsFail);					  // 模板另存为[%1]失败.
	rs_AddString(g_sLangID_Native_testName_Harmonic, &g_sLangTxt_Native_testName_Harmonic);		  // 试验名称：谐波

	rs_AddString(g_sLangID_Native_secondHarmonicAmp, &g_sLangTxt_Native_secondHarmonicAmp); // 二次谐波幅值

	rs_AddString(g_sLangID_Native_contentRatio, &g_sLangTxt_Native_contentRatio);					  // 含有率/%
	rs_AddString(g_sLangID_Native_rmsValueV, &g_sLangTxt_Native_rmsValueV);							  // 有效值/V
	rs_AddString(g_sLangID_Native_rmsValueA, &g_sLangTxt_Native_rmsValueA);							  // 有效值/A
	rs_AddString(g_sLangID_Native_phaseAngle, &g_sLangTxt_Native_phaseAngle);						  // 相 位/°
	rs_AddString(g_sLangID_Native_totalRmsValue, &g_sLangTxt_Native_totalRmsValue);					  // 总有效值
	rs_AddString(g_sLangID_Native_actionValueA, &g_sLangTxt_Native_actionValueA);					  // 动作值(A)
	rs_AddString(g_sLangID_Native_InitofVar, &g_sLangTxt_Native_InitofVar);							  // 变化始值(
	rs_AddString(g_sLangID_Native_FinalofVar, &g_sLangTxt_Native_FinalofVar);						  // 变化终值(
	rs_AddString(g_sLangID_Native_StepofVar, &g_sLangTxt_Native_StepofVar);							  // 变化步长(
	rs_AddString(g_sLangID_Native_channelAmp, &g_sLangTxt_Native_channelAmp);						  // 通道幅值(
	rs_AddString(g_sLangID_Native_groupNumber, &g_sLangTxt_Native_groupNumber);						  // 第%1组
	rs_AddString(g_sLangID_Native_harmonicLimitExceeded, &g_sLangTxt_Native_harmonicLimitExceeded);	  // 你总计只能选择31次谐波，假如想选择当前次谐波，需要取消勾选一行！
	rs_AddString(g_sLangID_Native_harmonicExceedsMax, &g_sLangTxt_Native_harmonicExceedsMax);		  // 选择的谐波次数大于最大值49次！
	rs_AddString(g_sLangID_Native_variaPointExceedsLimit, &g_sLangTxt_Native_variaPointExceedsLimit); // 递变点数超过3000点，请重新输入！

	// ui1
	rs_AddString(g_sLangID_Native_faultTimeMargin, &g_sLangTxt_Native_faultTimeMargin); // 故障时间裕度(s):

	// ui2
	rs_AddString(g_sLangID_Native_volDefinition, &g_sLangTxt_Native_volDefinition);		// 电压定义:
	rs_AddString(g_sLangID_Native_referenceItem, &g_sLangTxt_Native_referenceItem);		// 参考项
	rs_AddString(g_sLangID_Native_transConnection, &g_sLangTxt_Native_transConnection); // 变压器接线方式

	// ui3
	rs_AddString(g_sLangID_Native_Freq_Deviation, &g_sLangTxt_Native_Freq_Deviation);				// 频率滑差df/dt(Hz/s):
	rs_AddString(g_sLangID_Native_initialFreq, &g_sLangTxt_Native_initialFreq);						// 频率起始值(Hz):
	rs_AddString(g_sLangID_Native_FreqChange_step, &g_sLangTxt_Native_FreqChange_step);				// 频率变化步长(Hz):
	rs_AddString(g_sLangID_Native_endFreq, &g_sLangTxt_Native_endFreq);								// 频率结束值(Hz):
	rs_AddString(g_sLangID_Native_finalFreq, &g_sLangTxt_Native_finalFreq);							// 频率变化终值(Hz):
	rs_AddString(g_sLangID_Native_initialFreq_deviation, &g_sLangTxt_Native_initialFreq_deviation); // 频率滑差变化始值(Hz/s):
	rs_AddString(g_sLangID_Native_Freq_deviationstep, &g_sLangTxt_Native_Freq_deviationstep);		// 频率滑差变化步长(Hz/s):
	rs_AddString(g_sLangID_Native_finalFreq_deviation, &g_sLangTxt_Native_finalFreq_deviation);		// 频率滑差变化终值(Hz/s):
	rs_AddString(g_sLangID_Native_initialCur, &g_sLangTxt_Native_initialCur);						// 电流变化始值(A):
	rs_AddString(g_sLangID_Native_final_cur, &g_sLangTxt_Native_final_cur);							// 电流变化终值(A):
	rs_AddString(g_sLangID_Native_Curchange_step, &g_sLangTxt_Native_Curchange_step);				// 电流变化步长(A):
	rs_AddString(g_sLangID_Native_CurPhase_output, &g_sLangTxt_Native_CurPhase_output);				// 电流输出相：
	rs_AddString(g_sLangID_Native_initial_linevolchange, &g_sLangTxt_Native_initial_linevolchange); // 线电压变化始值(V):
	rs_AddString(g_sLangID_Native_final_linevolchange, &g_sLangTxt_Native_final_linevolchange);		// 线电压变化终值(V):
	rs_AddString(g_sLangID_Native_linevol_changestep, &g_sLangTxt_Native_linevol_changestep);		// 线电压变化步长(V):
	rs_AddString(g_sLangID_Native_vol_change, &g_sLangTxt_Native_vol_change);						// 电压变化量：

	// 马嘉骅第三周
	// OverVoltInverseTime_Trans 马
	rs_AddString(g_sLangID_Native_VoltIDMTTestTemp, &g_sLangTxt_Native_VoltIDMTTestTemp); /*tr("电压反时限试验模板文件")*/
	rs_AddString(g_sLangID_Native_PonVoltIDMT, &g_sLangTxt_Native_PonVoltIDMT);			  /*tr("Ponovo电压反时限试验")*/
	rs_AddString(g_sLangID_Native_WelVoltIDMT, &g_sLangTxt_Native_WelVoltIDMT);			  /*_T("欢迎使用电压反时限试验.")*/
	rs_AddString(g_sLangID_Native_PonBlaVoltIDMT, &g_sLangTxt_Native_PonBlaVoltIDMT);	  /*tr("Ponovo 电压反时限试验")*/
	rs_AddString(g_sLangID_Native_VolReTiLimTe, &g_sLangTxt_Native_VolReTiLimTe);		  /*tr("电压反时限试验")*/
	rs_AddString(g_sLangID_Native_VoltIDMT, &g_sLangTxt_Native_VoltIDMT);				  /*"电压反时限"*/
	rs_AddString(g_sLangID_Native_3PhFault, &g_sLangID_Native_3PhFault);				  /*"三相故障"*/
	rs_AddString(g_sLangID_Native_ZeroSeqVolt, &g_sLangTxt_Native_ZeroSeqVolt);			  /*"零序电压"*/
	rs_AddString(g_sLangID_Native_Start_End, &g_sLangTxt_Native_Start_End);				  /*tr("始值-终值")*/
	rs_AddString(g_sLangID_Native_Start_End_Start, &g_sLangTxt_Native_Start_End_Start);	  /*tr("始值-终值-始值")*/
	rs_AddString(g_sLangID_Native_ActTimeSymSy, &g_sLangTxt_Native_ActTimeSymSy);		  // 动作时间=%1s,
	rs_AddString(g_sLangID_Native_PreFaultSt, &g_sLangTxt_Native_PreFaultSt);			  // 故障前状态
	rs_AddString(g_sLangID_Native_FaultSt, &g_sLangTxt_Native_FaultSt);					  // 故障状态
	rs_AddString(g_sLangID_Native_FaultDur, &g_sLangTxt_Native_FaultDur);				  // 故障持续时间
	rs_AddString(g_sLangID_Native_CharCurve, &g_sLangTxt_Native_CharCurve);				  // 特性曲线
	rs_AddString(g_sLangID_Native_PhVolt, &g_sLangTxt_Native_PhVolt);					  // 相电压

	// 第四周许
	rs_AddString(g_sLangID_Native_QuickBreakCurrent, &g_sLangTxt_Native_QuickBreakCurrent);
	rs_AddString(g_sLangID_Native_QuickBreakCurrentIn, &g_sLangTxt_Native_QuickBreakCurrentIn);
	rs_AddString(g_sLangID_Native_CenterPointImpedance, &g_sLangTxt_Native_CenterPointImpedance);
	rs_AddString(g_sLangID_Native_CenterPointImpedanceAngle, &g_sLangTxt_Native_CenterPointImpedanceAngle);
	rs_AddString(g_sLangID_Native_SearchRadius, &g_sLangTxt_Native_SearchRadius);
	rs_AddString(g_sLangID_Native_ImpedanceAngleStartValue, &g_sLangTxt_Native_ImpedanceAngleStartValue);
	rs_AddString(g_sLangID_Native_ImpedanceAngleEndValue, &g_sLangTxt_Native_ImpedanceAngleEndValue);
	rs_AddString(g_sLangID_Native_AngleChangeSteps, &g_sLangTxt_Native_AngleChangeSteps);
	rs_AddString(g_sLangID_Native_ImpedanceChangeStep, &g_sLangTxt_Native_ImpedanceChangeStep);
	rs_AddString(g_sLangID_Native_MaxFaultTimes, &g_sLangTxt_Native_MaxFaultTimes);
	rs_AddString(g_sLangID_Native_EndImpedance, &g_sLangTxt_Native_EndImpedance);
	rs_AddString(g_sLangID_Native_EndImpAngle, &g_sLangTxt_Native_EndImpAngle);
	rs_AddString(g_sLangID_Native_StartImpedance, &g_sLangTxt_Native_StartImpedance);
	rs_AddString(g_sLangID_Native_StartImpAngle, &g_sLangTxt_Native_StartImpAngle);
	rs_AddString(g_sLangID_Native_ImpStep, &g_sLangTxt_Native_ImpStep);

	rs_AddString(g_sLangID_Native_RefState, &g_sLangTxt_Native_RefState);
	rs_AddString(g_sLangID_Native_DcComp, &g_sLangTxt_Native_DcComp);
	rs_AddString(g_sLangID_Native_DecayTime, &g_sLangTxt_Native_DecayTime);
	rs_AddString(g_sLangID_Native_LoopCount, &g_sLangTxt_Native_LoopCount);
	rs_AddString(g_sLangID_Native_AuxDCSet, &g_sLangTxt_Native_AuxDCSet);
	rs_AddString(g_sLangID_Native_ZeroSeqComp, &g_sLangTxt_Native_ZeroSeqComp);

	rs_AddString(g_sLangID_Native_OutTotalTime, &g_sLangTxt_Native_OutTotalTime);
	rs_AddString(g_sLangID_Native_ShiftMoment, &g_sLangTxt_Native_ShiftMoment);
	rs_AddString(g_sLangID_Native_CloseTimes, &g_sLangTxt_Native_CloseTimes);
	rs_AddString(g_sLangID_Native_BreakTime, &g_sLangTxt_Native_BreakTime);

	rs_AddString(g_sLangID_Native_SOETest, &g_sLangTxt_Native_SOETest);
	rs_AddString(g_sLangID_Native_SaveConfig, &g_sLangTxt_Native_SaveConfig);
	rs_AddString(g_sLangID_Native_SaveCurrConfig, &g_sLangTxt_Native_SaveCurrConfig);
	rs_AddString(g_sLangID_Native_StartTrigger, &g_sLangTxt_Native_StartTrigger);
	rs_AddString(g_sLangID_Native_StartExpFail, &g_sLangTxt_Native_StartExpFail);
	rs_AddString(g_sLangID_Native_StopExpFail, &g_sLangTxt_Native_StopExpFail);

	rs_AddString(g_sLangID_Native_NormOutputSet, &g_sLangTxt_Native_NormOutputSet);
	rs_AddString(g_sLangID_Native_FaultOutputSet, &g_sLangTxt_Native_FaultOutputSet);
	rs_AddString(g_sLangID_Native_IOSet, &g_sLangTxt_Native_IOSet);
	rs_AddString(g_sLangID_Native_InputSelect, &g_sLangTxt_Native_InputSelect);
	rs_AddString(g_sLangID_Native_OutputFlipStart, &g_sLangTxt_Native_OutputFlipStart);
	rs_AddString(g_sLangID_Native_OutputHoldTime, &g_sLangTxt_Native_OutputHoldTime);
	rs_AddString(g_sLangID_Native_OutputFlipMoment, &g_sLangTxt_Native_OutputFlipMoment);
	rs_AddString(g_sLangID_Native_SingleJump, &g_sLangTxt_Native_SingleJump);
	rs_AddString(g_sLangID_Native_TripleJump, &g_sLangTxt_Native_TripleJump);
	rs_AddString(g_sLangID_Native_Reincidence, &g_sLangTxt_Native_Reincidence);
	rs_AddString(g_sLangID_Native_TimeStart, &g_sLangTxt_Native_TimeStart);
	rs_AddString(g_sLangID_Native_InputStart, &g_sLangTxt_Native_InputStart);
	rs_AddString(g_sLangID_Native_InputABCD, &g_sLangTxt_Native_InputABCD);
	rs_AddString(g_sLangID_Native_InputEFGH, &g_sLangTxt_Native_InputEFGH);
	rs_AddString(g_sLangID_Native_OutputABCD, &g_sLangTxt_Native_OutputABCD);
	rs_AddString(g_sLangID_Native_OutputEFGH, &g_sLangTxt_Native_OutputEFGH);
	rs_AddString(g_sLangID_Native_InputOper, &g_sLangTxt_Native_InputOper);
	rs_AddString(g_sLangID_Native_OutputOper, &g_sLangTxt_Native_OutputOper);
	rs_AddString(g_sLangID_Native_InSel, &g_sLangTxt_Native_InSel);
	rs_AddString(g_sLangID_Native_InputOpers, &g_sLangTxt_Native_InputOpers);
	rs_AddString(g_sLangID_Native_OutputOpers, &g_sLangTxt_Native_OutputOpers);
	rs_AddString(g_sLangID_Native_OutputA, &g_sLangTxt_Native_OutputA);
	rs_AddString(g_sLangID_Native_OutputB, &g_sLangTxt_Native_OutputB);
	rs_AddString(g_sLangID_Native_OutputC, &g_sLangTxt_Native_OutputC);
	rs_AddString(g_sLangID_Native_OutputD, &g_sLangTxt_Native_OutputD);
	rs_AddString(g_sLangID_Native_OutputE, &g_sLangTxt_Native_OutputE);
	rs_AddString(g_sLangID_Native_OutputF, &g_sLangTxt_Native_OutputF);
	rs_AddString(g_sLangID_Native_OutputG, &g_sLangTxt_Native_OutputG);
	rs_AddString(g_sLangID_Native_OutputH, &g_sLangTxt_Native_OutputH);

	rs_AddString(g_sLangID_Native_OutputFlipMomentS, &g_sLangTxt_Native_OutputFlipMomentS);
	rs_AddString(g_sLangID_Native_SelMapFile, &g_sLangTxt_Native_SelMapFile);
	rs_AddString(g_sLangID_Native_SaveMapFile, &g_sLangTxt_Native_SaveMapFile);
	rs_AddString(g_sLangID_Native_ExpMapSucc, &g_sLangTxt_Native_ExpMapSucc);
	rs_AddString(g_sLangID_Native_ExpMapFail, &g_sLangTxt_Native_ExpMapFail);
	rs_AddString(g_sLangID_Native_MapPass, &g_sLangTxt_Native_MapPass);
	rs_AddString(g_sLangID_Native_Pass, &g_sLangTxt_Native_Pass);
	rs_AddString(g_sLangID_Native_EmptyPass, &g_sLangTxt_Native_EmptyPass);
	rs_AddString(g_sLangID_Native_WrongPass, &g_sLangTxt_Native_WrongPass);
	rs_AddString(g_sLangID_Native_RatedVolt, &g_sLangTxt_Native_RatedVolt);
	rs_AddString(g_sLangID_Native_RatedCurr, &g_sLangTxt_Native_RatedCurr);
	rs_AddString(g_sLangID_Native_RatedFreq, &g_sLangTxt_Native_RatedFreq);
	rs_AddString(g_sLangID_Native_DebTime, &g_sLangTxt_Native_DebTime);
	rs_AddString(g_sLangID_Native_PortNum, &g_sLangTxt_Native_PortNum);
	rs_AddString(g_sLangID_Native_NetConfig, &g_sLangTxt_Native_NetConfig);
	rs_AddString(g_sLangID_Native_InvalidIPPort, &g_sLangTxt_Native_InvalidIPPort);
	rs_AddString(g_sLangID_Native_TotalGroups, &g_sLangTxt_Native_TotalGroups);
	rs_AddString(g_sLangID_Native_TotalGroupsParam, &g_sLangTxt_Native_TotalGroupsParam);
	rs_AddString(g_sLangID_Native_CurrentGroupParam, &g_sLangTxt_Native_CurrentGroupParam);
	rs_AddString(g_sLangID_Native_PrevGroups, &g_sLangTxt_Native_PrevGroups);
	rs_AddString(g_sLangID_Native_NextGroups, &g_sLangTxt_Native_NextGroups);
	rs_AddString(g_sLangID_Native_CurrentVersionParam, &g_sLangTxt_Native_CurrentVersionParam);
	rs_AddString(g_sLangID_Native_TestView, &g_sLangTxt_Native_TestView);
	rs_AddString(g_sLangID_Native_ReportView, &g_sLangTxt_Native_ReportView);
	rs_AddString(g_sLangID_Native_StateHistory, &g_sLangTxt_Native_StateHistory);
	rs_AddString(g_sLangID_Native_StatusLight, &g_sLangTxt_Native_StatusLight);
	rs_AddString(g_sLangID_Native_StartTestF2, &g_sLangTxt_Native_StartTestF2);
	rs_AddString(g_sLangID_Native_StopTestEsc, &g_sLangTxt_Native_StopTestEsc);
	rs_AddString(g_sLangID_Native_OpenTempFile, &g_sLangTxt_Native_OpenTempFile);
	rs_AddString(g_sLangID_Native_SaveTempFile, &g_sLangTxt_Native_SaveTempFile);
	rs_AddString(g_sLangID_Native_ModelParamConfig, &g_sLangTxt_Native_ModelParamConfig);
	rs_AddString(g_sLangID_Native_GenParamSetDlg, &g_sLangTxt_Native_GenParamSetDlg);
	rs_AddString(g_sLangID_Native_SetValueParamSetDlg, &g_sLangTxt_Native_SetValueParamSetDlg);

	rs_AddString(g_sLangID_Native_SwitchValSetDlg, &g_sLangTxt_Native_SwitchValSetDlg);
	rs_AddString(g_sLangID_Native_NetConnect, &g_sLangTxt_Native_NetConnect);
	rs_AddString(g_sLangID_Native_NetConnectDlg, &g_sLangTxt_Native_NetConnectDlg);
	rs_AddString(g_sLangID_Native_ChResMapDlg, &g_sLangTxt_Native_ChResMapDlg);
	rs_AddString(g_sLangID_Native_DCSet, &g_sLangTxt_Native_DCSet);
	rs_AddString(g_sLangID_Native_AuxDCSetDlg, &g_sLangTxt_Native_AuxDCSetDlg);
	rs_AddString(g_sLangID_Native_OutputPower, &g_sLangTxt_Native_OutputPower);
	rs_AddString(g_sLangID_Native_OutputPowerSetDlg, &g_sLangTxt_Native_OutputPowerSetDlg);
	rs_AddString(g_sLangID_Native_SteadyOutput, &g_sLangTxt_Native_SteadyOutput);
	rs_AddString(g_sLangID_Native_ACDCSteadyOutput, &g_sLangTxt_Native_ACDCSteadyOutput);
	rs_AddString(g_sLangID_Native_ReportSet, &g_sLangTxt_Native_ReportSet);
	rs_AddString(g_sLangID_Native_ReportParamSet, &g_sLangTxt_Native_ReportParamSet);
	rs_AddString(g_sLangID_Native_ShowTestView, &g_sLangTxt_Native_ShowTestView);
	rs_AddString(g_sLangID_Native_ShowReportView, &g_sLangTxt_Native_ShowReportView);
	rs_AddString(g_sLangID_Native_StateLightView, &g_sLangTxt_Native_StateLightView);
	rs_AddString(g_sLangID_Native_ShowStateLightView, &g_sLangTxt_Native_ShowStateLightView);
	rs_AddString(g_sLangID_Native_StateHistoryView, &g_sLangTxt_Native_StateHistoryView);
	rs_AddString(g_sLangID_Native_ShowStateHistoryView, &g_sLangTxt_Native_ShowStateHistoryView);
	rs_AddString(g_sLangID_Native_CurrentTesterVersionInfo, &g_sLangTxt_Native_CurrentTesterVersionInfo);
	rs_AddString(g_sLangID_Native_UpdateSoftwares, &g_sLangTxt_Native_UpdateSoftwares);
	rs_AddString(g_sLangID_Native_UpdateHostSoftware, &g_sLangTxt_Native_UpdateHostSoftware);
	rs_AddString(g_sLangID_Native_UpdateLowerLayer, &g_sLangTxt_Native_UpdateLowerLayer);
	rs_AddString(g_sLangID_Native_UpdateTesterLowerProgram, &g_sLangTxt_Native_UpdateTesterLowerProgram);
	rs_AddString(g_sLangID_Native_MessageDetection, &g_sLangTxt_Native_MessageDetection);
	rs_AddString(g_sLangID_Native_Report, &g_sLangTxt_Native_Report);
	rs_AddString(g_sLangID_Native_Start, &g_sLangTxt_Native_Start);
	rs_AddString(g_sLangID_Native_SysParamConfigDialog, &g_sLangTxt_Native_SysParamConfigDialog);
	rs_AddString(g_sLangID_Native_OfflineSelection, &g_sLangTxt_Native_OfflineSelection);
	rs_AddString(g_sLangID_Native_OfflineSelectTesterModelSN, &g_sLangTxt_Native_OfflineSelectTesterModelSN);
	rs_AddString(g_sLangID_Native_Date1970, &g_sLangTxt_Native_Date1970);
	rs_AddString(g_sLangID_Native_ConnectionStatus, &g_sLangTxt_Native_ConnectionStatus);
	rs_AddString(g_sLangID_Native_SyncTime, &g_sLangTxt_Native_SyncTime);
	rs_AddString(g_sLangID_Native_FileSaveSuccess, &g_sLangTxt_Native_FileSaveSuccess);
	rs_AddString(g_sLangID_Native_FileSaveFail, &g_sLangTxt_Native_FileSaveFail);
	rs_AddString(g_sLangID_Native_DefParamFileSaveSuccess, &g_sLangTxt_Native_DefParamFileSaveSuccess);
	rs_AddString(g_sLangID_Native_DefParamFileSaveFail, &g_sLangTxt_Native_DefParamFileSaveFail);
	rs_AddString(g_sLangID_Native_HarmonicExceedValue, &g_sLangTxt_Native_HarmonicExceedValue);
	rs_AddString(g_sLangID_Native_OutputMaxExceedDesign, &g_sLangTxt_Native_OutputMaxExceedDesign);
	rs_AddString(g_sLangID_Native_ReModifyHarmonicValue, &g_sLangTxt_Native_ReModifyHarmonicValue);
	rs_AddString(g_sLangID_Native_LastTestCannotContinue, &g_sLangTxt_Native_LastTestCannotContinue);
	rs_AddString(g_sLangID_Native_SystemParamSetComplete, &g_sLangTxt_Native_SystemParamSetComplete);
	rs_AddString(g_sLangID_Native_SystemParamSetFailed, &g_sLangTxt_Native_SystemParamSetFailed);
	rs_AddString(g_sLangID_Native_TestStopped, &g_sLangTxt_Native_TestStopped);
	rs_AddString(g_sLangID_Native_StopCommandFailed, &g_sLangTxt_Native_StopCommandFailed);
	rs_AddString(g_sLangID_Native_ConnectionFailed, &g_sLangTxt_Native_ConnectionFailed);
	rs_AddString(g_sLangID_Native_ModuleSwitchDone, &g_sLangTxt_Native_ModuleSwitchDone);
	rs_AddString(g_sLangID_Native_ModuleSwitchFail, &g_sLangTxt_Native_ModuleSwitchFail);
	rs_AddString(g_sLangID_Native_AuxDCOutDone, &g_sLangTxt_Native_AuxDCOutDone);
	rs_AddString(g_sLangID_Native_AuxDCOutFail, &g_sLangTxt_Native_AuxDCOutFail);
//	rs_AddString(g_sLangID_Native_ConnectFail, &g_sLangTxt_Native_ConnectFail);
	rs_AddString(g_sLangID_Native_StartSteadyOut, &g_sLangTxt_Native_StartSteadyOut);
	rs_AddString(g_sLangID_Native_StopSteadyOut, &g_sLangTxt_Native_StopSteadyOut);
	
	rs_AddString(g_sLangID_Native_StopSOETest, &g_sLangTxt_Native_StopSOETest);
	rs_AddString(g_sLangID_Native_ExportWord, &g_sLangTxt_Native_ExportWord);
	rs_AddString(g_sLangID_Native_ReportTypes, &g_sLangTxt_Native_ReportTypes);
	rs_AddString(g_sLangID_Native_SaveReportSuccess, &g_sLangTxt_Native_SaveReportSuccess);
	rs_AddString(g_sLangID_Native_SavePDFSuccess, &g_sLangTxt_Native_SavePDFSuccess);
	rs_AddString(g_sLangID_Native_SavePDFFailure, &g_sLangTxt_Native_SavePDFFailure);
	rs_AddString(g_sLangID_Native_SaveWordSuccess, &g_sLangTxt_Native_SaveWordSuccess);
	rs_AddString(g_sLangID_Native_SaveWordFailure, &g_sLangTxt_Native_SaveWordFailure);
	rs_AddString(g_sLangID_Native_TestRunning, &g_sLangTxt_Native_TestRunning);
	rs_AddString(g_sLangID_Native_UnsavedTemplate, &g_sLangTxt_Native_UnsavedTemplate);
	rs_AddString(g_sLangID_Native_DeleteAll, &g_sLangTxt_Native_DeleteAll);
	rs_AddString(g_sLangID_Native_VarName, &g_sLangTxt_Native_VarName);

	// 第四周吕
	rs_AddString(g_sLangID_Native_voltagev, &g_sLangTxt_Native_voltagev);			  // 电压（V）：
	rs_AddString(g_sLangID_Native_currentc, &g_sLangTxt_Native_currentc);			  // 电流(A):
	rs_AddString(g_sLangID_Native_phasep, &g_sLangTxt_Native_phasep);				  // 相位差(°):
	rs_AddString(g_sLangID_Native_initialCurrent, &g_sLangTxt_Native_initialCurrent); // 电流变化始值(I*):
	rs_AddString(g_sLangID_Native_finalCurrent, &g_sLangTxt_Native_finalCurrent);	  // 电流变化终值(I*):
	rs_AddString(g_sLangID_Native_CurstepSize, &g_sLangTxt_Native_CurstepSize);		  // 电流变化步长(I*):
	rs_AddString(g_sLangID_Native_currentcI, &g_sLangTxt_Native_currentcI);			  // 电流(I*):
	rs_AddString(g_sLangID_Native_referenceValue, &g_sLangTxt_Native_referenceValue); // 基准值:
	rs_AddString(g_sLangID_Native_ctPolarityDef, &g_sLangTxt_Native_ctPolarityDef);	  // CT正极性定义:
	rs_AddString(g_sLangID_Native_charaDef, &g_sLangTxt_Native_charaDef);			  // 特性定义
	rs_AddString(g_sLangID_Native_timerLimit1, &g_sLangTxt_Native_timerLimit1);		  // 1段定时限
	rs_AddString(g_sLangID_Native_timerLimit2, &g_sLangTxt_Native_timerLimit2);		  // 2段定时限
	rs_AddString(g_sLangID_Native_timerLimit3, &g_sLangTxt_Native_timerLimit3);		  // 3段定时限

	// ui5
	rs_AddString(g_sLangID_Native_singleP, &g_sLangTxt_Native_singleP);						  // 单相
	rs_AddString(g_sLangID_Native_impedanceSelection, &g_sLangTxt_Native_impedanceSelection); // 阻抗选择:
	rs_AddString(g_sLangID_Native_times, &g_sLangTxt_Native_times);							  // 倍
	rs_AddString(g_sLangID_Native_impedanceRepresent, &g_sLangTxt_Native_impedanceRepresent); // 阻抗表示方式:
	rs_AddString(g_sLangID_Native_timeConstant, &g_sLangTxt_Native_timeConstant);			  // 时间定值(s):
	rs_AddString(g_sLangID_Native_triggerTiming, &g_sLangTxt_Native_triggerTiming);			  // 触发时刻:
	rs_AddString(g_sLangID_Native_h, &g_sLangTxt_Native_h);									  // 时
	rs_AddString(g_sLangID_Native_m, &g_sLangTxt_Native_m);									  // 分
	rs_AddString(g_sLangID_Native_s, &g_sLangTxt_Native_s);									  // 秒

	// ui6
	rs_AddString(g_sLangID_Native_PreChangeVol, &g_sLangTxt_Native_PreChangeVol);	// 变化前电压(V):
	rs_AddString(g_sLangID_Native_PreChangeCur, &g_sLangTxt_Native_PreChangeCur);	// 变化前电流(A)：
	rs_AddString(g_sLangID_Native_PreChangeFreq, &g_sLangTxt_Native_PreChangeFreq); // 变化前频率(HZ)：
	rs_AddString(g_sLangID_Native_variableType, &g_sLangTxt_Native_variableType);	// 变量类型:
	rs_AddString(g_sLangID_Native_variable0, &g_sLangTxt_Native_variable0);			// 变量:
	rs_AddString(g_sLangID_Native_directChange, &g_sLangTxt_Native_directChange);	// 递变方向：

	rs_AddString(g_sLangID_Native_currentG1, &g_sLangTxt_Native_currentG1);		// 电流(G1)(A)：
	rs_AddString(g_sLangID_Native_currentG2, &g_sLangTxt_Native_currentG2);		// 电流(G2)(A)：
	rs_AddString(g_sLangID_Native_voltageG1, &g_sLangTxt_Native_voltageG1);		// 电压(G1)(V)：
	rs_AddString(g_sLangID_Native_voltageG2, &g_sLangTxt_Native_voltageG2);		// 电压(G2)(V)：
	rs_AddString(g_sLangID_Native_currentDif, &g_sLangTxt_Native_currentDif);	// 电流相差(G1,G2)(°):
	rs_AddString(g_sLangID_Native_normalState, &g_sLangTxt_Native_normalState); // 常态:
	rs_AddString(g_sLangID_Native_faultState, &g_sLangTxt_Native_faultState);	// 故障态:

	rs_AddString(g_sLangID_Native_relativeErrorl, &g_sLangTxt_Native_relativeErrorl);		  // 相对误差<
	rs_AddString(g_sLangID_Native_returnCoefficientb, &g_sLangTxt_Native_returnCoefficientb); // 返回系数>
	rs_AddString(g_sLangID_Native_judgmentCondition, &g_sLangTxt_Native_judgmentCondition);	  // 判定条件
	rs_AddString(g_sLangID_Native_express, &g_sLangTxt_Native_express);						  // 表达式

	// ui7
	rs_AddString(g_sLangID_Native_clear0, &g_sLangTxt_Native_clear0);					  // 清零
	rs_AddString(g_sLangID_Native_changeSettings, &g_sLangTxt_Native_changeSettings);	  // 变化设置:
	rs_AddString(g_sLangID_Native_changeTime, &g_sLangTxt_Native_changeTime);			  // 变化时间(s):
	rs_AddString(g_sLangID_Native_baseFrequency, &g_sLangTxt_Native_baseFrequency);		  // 基波频率(Hz):
	rs_AddString(g_sLangID_Native_openSettings, &g_sLangTxt_Native_openSettings);		  // 开出设置:
	rs_AddString(g_sLangID_Native_harmDataBatchSet, &g_sLangTxt_Native_harmDataBatchSet); // 谐波数据批量设置:
	rs_AddString(g_sLangID_Native_channelContain, &g_sLangTxt_Native_channelContain);	  // 通道含有率(%):
	rs_AddString(g_sLangID_Native_channelPhase, &g_sLangTxt_Native_channelPhase);		  // 通道相位(°):

	// goose
	rs_AddString(g_sLangID_Native_forceNumberOutput, &g_sLangTxt_Native_forceNumberOutput);		// 当前模块需要支持数字量输出功能,强制设置为数字量输出模式.
	rs_AddString(g_sLangID_Native_notSupportNumOutput, &g_sLangTxt_Native_notSupportNumOutput); // 当前测试仪不支持数字量输出功能,无法使用GOOSE异常模拟试验.
	rs_AddString(g_sLangID_Native_PonovogooseSim, &g_sLangTxt_Native_PonovogooseSim);			// Ponovo GOOSE异常模拟
	rs_AddString(g_sLangID_Native_welgooseSim, &g_sLangTxt_Native_welgooseSim);					// 欢迎使用GOOSE异常模拟试验.
	rs_AddString(g_sLangID_Native_JumpA, &g_sLangTxt_Native_JumpA);								// 跳A
	rs_AddString(g_sLangID_Native_JumpB, &g_sLangTxt_Native_JumpB);								// 跳B
	rs_AddString(g_sLangID_Native_JumpC, &g_sLangTxt_Native_JumpC);								// 跳C
	rs_AddString(g_sLangID_Native_JumpD, &g_sLangTxt_Native_JumpD);								// 跳D
	rs_AddString(g_sLangID_Native_JumpE, &g_sLangTxt_Native_JumpE);								// 跳E
	rs_AddString(g_sLangID_Native_JumpF, &g_sLangTxt_Native_JumpF);								// 跳F
	rs_AddString(g_sLangID_Native_JumpG, &g_sLangTxt_Native_JumpG);								// 跳G
	rs_AddString(g_sLangID_Native_JumpH, &g_sLangTxt_Native_JumpH);								// 跳H
	rs_AddString(g_sLangID_Native_JumpI, &g_sLangTxt_Native_JumpI);								// 跳I
	rs_AddString(g_sLangID_Native_JumpJ, &g_sLangTxt_Native_JumpJ);								// 跳J
	rs_AddString(g_sLangID_Native_STSS1234, &g_sLangTxt_Native_STSS1234);						// 状态%1,输出时间=%2,StNum=%3,SqNum=%4

	// channelParaset
	rs_AddString(g_sLangID_Native_amplitudeV, &g_sLangTxt_Native_amplitudeV);			// 幅值(V)
	rs_AddString(g_sLangID_Native_amplitudeKV, &g_sLangTxt_Native_amplitudeKV);			// 幅值(KV)
	rs_AddString(g_sLangID_Native_amplitudeA, &g_sLangTxt_Native_amplitudeA);			// 幅值(A)
	rs_AddString(g_sLangID_Native_overflowV, &g_sLangTxt_Native_overflowV);				// 谐波设置值%f(%d,%d)与基波的叠加超出范围(%fV).
	rs_AddString(g_sLangID_Native_overflowA, &g_sLangTxt_Native_overflowA);				// 谐波设置值%f(%d,%d)与基波的叠加超出范围(%fA).
	rs_AddString(g_sLangID_Native_input_overrange, &g_sLangTxt_Native_input_overrange); // 输入值%f(%d,%d)超出范围(%f).
	rs_AddString(g_sLangID_Native_flowoverV, &g_sLangTxt_Native_flowoverV);				// 基波设置值%f(%d,%d)与谐波的叠加超出范围(%fV).
	rs_AddString(g_sLangID_Native_flowoverA, &g_sLangTxt_Native_flowoverA);				// 基波设置值%f(%d,%d)与谐波的叠加超出范围(%fA).
	rs_AddString(g_sLangID_Native_all_frequencies, &g_sLangTxt_Native_all_frequencies); // 等全部频率
	rs_AddString(g_sLangID_Native_smallsignal, &g_sLangTxt_Native_smallsignal);			// 小信号
	rs_AddString(g_sLangID_Native_illchannelname, &g_sLangTxt_Native_illchannelname);	// 递变通道名【%s】非法

	// 第四周马
	// DifferTest_Trans 马
	rs_AddString(g_sLangID_Native_DifTestTempFile, &g_sLangTxt_Native_DifTestTempFile);				/*tr("差动试验模板文件")*/
	rs_AddString(g_sLangID_Native_WelToDiffTest, &g_sLangTxt_Native_WelToDiffTest);					/*_T("欢迎使用差动测试.")*/
	rs_AddString(g_sLangID_Native_PonovoDiff, &g_sLangTxt_Native_PonovoDiff);						/*tr("Ponovo 差动")*/
	rs_AddString(g_sLangID_Native_Differential, &g_sLangTxt_Native_Differential);					/*tr("差动")*/
	rs_AddString(g_sLangID_Native_CurveGraph, &g_sLangTxt_Native_CurveGraph);						/*tr("特征曲线图")*/
	rs_AddString(g_sLangID_Native_WireDiagram, &g_sLangTxt_Native_WireDiagram);						/*tr("接线图")*/
	rs_AddString(g_sLangID_Native_NoTgtDelItem, &g_sLangTxt_Native_NoTgtDelItem);					/*tr("没有选择目标删除项!")*/
	rs_AddString(g_sLangID_Native_AtLeast1Test, &g_sLangTxt_Native_AtLeast1Test);					/*tr("此测试类型至少保留一个测试项！")*/
	rs_AddString(g_sLangID_Native_OnlineFailSy, &g_sLangTxt_Native_OnlineFailSy);					/*_T("联机失败[%s][%ld].")*/
	rs_AddString(g_sLangID_Native_ChnlMapFileDone, &g_sLangTxt_Native_ChnlMapFileDone);				/*tr("通道映射文件下发完成")*/
	rs_AddString(g_sLangID_Native_ChMapFileErr, &g_sLangTxt_Native_ChMapFileErr);					/*tr("通道映射文件下发失败")*/
	rs_AddString(g_sLangID_Native_SysParamSetDone, &g_sLangTxt_Native_SysParamSetDone);				/*tr("系统参数设置下发完成")*/
	rs_AddString(g_sLangID_Native_SysParamErr, &g_sLangTxt_Native_SysParamErr);						/*tr("系统参数设置下发失败")*/
	rs_AddString(g_sLangID_Native_IECParamSetDone, &g_sLangTxt_Native_IECParamSetDone);				/*tr("IEC参数设置下发完成")*/
	rs_AddString(g_sLangID_Native_IECParamTimeout, &g_sLangTxt_Native_IECParamTimeout);				/*tr("IEC参数设置执行超时")*/
	rs_AddString(g_sLangID_Native_IECParamFail, &g_sLangTxt_Native_IECParamFail);					/*tr("IEC参数设置执行失败")*/
	rs_AddString(g_sLangID_Native_StartTestSy, &g_sLangTxt_Native_StartTestSy);						/*tr("开始测试.")*/
	rs_AddString(g_sLangID_Native_StartTestCmdFail, &g_sLangTxt_Native_StartTestCmdFail);			/*tr("开始测试命令下发失败.")*/
	rs_AddString(g_sLangID_Native_NoTestItemSy, &g_sLangTxt_Native_NoTestItemSy);					/*tr("没有选择测试项.")*/
	rs_AddString(g_sLangID_Native_SetTestItemCurrent, &g_sLangTxt_Native_SetTestItemCurrent);		/*tr("在Id-Ir平面上双击鼠标，设置测试项的制动电流值")*/
	rs_AddString(g_sLangID_Native_RefCurrentOther, &g_sLangTxt_Native_RefCurrentOther);				/*_T("基准电流(其它)")*/
	rs_AddString(g_sLangID_Native_DfRelayCurrSet, &g_sLangTxt_Native_DfRelayCurrSet);				/*_T("差动速断电流定值")*/
	rs_AddString(g_sLangID_Native_DfActThresh, &g_sLangTxt_Native_DfActThresh);						/*_T("差动动作电流门槛值")*/
	rs_AddString(g_sLangID_Native_RatioBrkPntCnt, &g_sLangTxt_Native_RatioBrkPntCnt);				/*_T("比率制动特性拐点数")*/
	rs_AddString(g_sLangID_Native_RatioBrkPt1Curr, &g_sLangTxt_Native_RatioBrkPt1Curr);				/*_T("比率制动特性拐点1电流")*/
	rs_AddString(g_sLangID_Native_RatioBrkPt2Curr, &g_sLangTxt_Native_RatioBrkPt2Curr);				/*_T("比率制动特性拐点2电流")*/
	rs_AddString(g_sLangID_Native_RatioBrkPt3Curr, &g_sLangTxt_Native_RatioBrkPt3Curr);				/*_T("比率制动特性拐点3电流")*/
	rs_AddString(g_sLangID_Native_DiffCurrExceedsLimit, &g_sLangTxt_Native_DiffCurrExceedsLimit);	/*_T("差动电流值(%f),超越上限")*/
	rs_AddString(g_sLangID_Native_ParamsUpdated, &g_sLangTxt_Native_ParamsUpdated);					/*tr("参数更新成功.")*/
	rs_AddString(g_sLangID_Native_ParamsUpdateFailed, &g_sLangTxt_Native_ParamsUpdateFailed);		/*tr("参数更新失败.")*/
	rs_AddString(g_sLangID_Native_DiffCurrReducedToZero, &g_sLangTxt_Native_DiffCurrReducedToZero); /*_T("差动电流值已降低为0,无法再减小")*/
	rs_AddString(g_sLangID_Native_RatioBrkCoef1, &g_sLangTxt_Native_RatioBrkCoef1);					/*QObject::tr("比率制动系数一")*/
	rs_AddString(g_sLangID_Native_RatioBrkCoef2, &g_sLangTxt_Native_RatioBrkCoef2);					/*QObject::tr("比率制动系数二")*/
	rs_AddString(g_sLangID_Native_RatioBrkCoef3, &g_sLangTxt_Native_RatioBrkCoef3);					/*QObject::tr("比率制动系数三")*/

					  /*QObject::tr("5次谐波制动系数")*/
	rs_AddString(g_sLangID_Native_ManInBalCoeffNoHi, &g_sLangTxt_Native_ManInBalCoeffNoHi);				  /*_T("手动计算输入平衡系数方式时如果整定值选择标幺值，则基准电流不可选择高侧二次额定电流.")*/
	rs_AddString(g_sLangID_Native_ManInBalCoeffNoBe, &g_sLangTxt_Native_ManInBalCoeffNoBe);				  /*_T("手动计算输入平衡系数方式时如果整定值选择标幺值，则基准电流不可选择各侧二次额定电流.")*/
	rs_AddString(g_sLangID_Native_DiffCurrentTheory, &g_sLangTxt_Native_DiffCurrentTheory);				  /*"差流理论值"*/
	rs_AddString(g_sLangID_Native_Diff6I, &g_sLangTxt_Native_Diff6I);									  /*"<h1>差动6I</h1>"*/
	rs_AddString(g_sLangID_Native_TestResultSy, &g_sLangTxt_Native_TestResultSy);						  /*"<h2>测试结果</h2>"*/
	rs_AddString(g_sLangID_Native_UnkCat, &g_sLangTxt_Native_UnkCat);									  /*"未知类别"*/
	rs_AddString(g_sLangID_Native_AutoCalc, &g_sLangTxt_Native_AutoCalc);								  /*"自动计算"*/
	rs_AddString(g_sLangID_Native_ManCalcInput, &g_sLangTxt_Native_ManCalcInput);						  /*"手动计算并输入"*/
	rs_AddString(g_sLangID_Native_HighLow, &g_sLangTxt_Native_HighLow);									  /*"高-低"*/
	rs_AddString(g_sLangID_Native_HighMid, &g_sLangTxt_Native_HighMid);									  /*"高-中"*/
	rs_AddString(g_sLangID_Native_MidLow, &g_sLangTxt_Native_MidLow);									  /*"中-低"*/
	rs_AddString(g_sLangID_Native_BinSearch, &g_sLangTxt_Native_BinSearch);								  /*"二分法"*/
	rs_AddString(g_sLangID_Native_StepApprox, &g_sLangTxt_Native_StepApprox);							  /*"单步逼近"*/
	rs_AddString(g_sLangID_Native_NameValue, &g_sLangTxt_Native_NameValue);								  /*"有名值"*/
	rs_AddString(g_sLangID_Native_PerUnitVal, &g_sLangTxt_Native_PerUnitVal);							  /*"标幺值"*/
	rs_AddString(g_sLangID_Native_HighSideSecRatedCurr, &g_sLangTxt_Native_HighSideSecRatedCurr);		  /*"高侧二次额定电流"*/
	rs_AddString(g_sLangID_Native_BeSideSecRatedCurr, &g_sLangTxt_Native_BeSideSecRatedCurr);			  /*"各侧二次额定电流"*/
	rs_AddString(g_sLangID_Native_Setpt, &g_sLangTxt_Native_Setpt);										  /*"设定值"*/
	rs_AddString(g_sLangID_Native_OneTurnPoint, &g_sLangTxt_Native_OneTurnPoint);						  /*"一个拐点"*/
	rs_AddString(g_sLangID_Native_TwoTurnPoint, &g_sLangTxt_Native_TwoTurnPoint);						  /*"二个拐点"*/
	rs_AddString(g_sLangID_Native_ThreeTurnPoint, &g_sLangTxt_Native_ThreeTurnPoint);					  /*"三个拐点"*/
	rs_AddString(g_sLangID_Native_InitValChange, &g_sLangTxt_Native_InitValChange);						  /*tr("变化始值(In):")*/
	rs_AddString(g_sLangID_Native_EndValChange, &g_sLangTxt_Native_EndValChange);						  /*tr("变化终值(In):")*/
	rs_AddString(g_sLangID_Native_ChgStep, &g_sLangTxt_Native_ChgStep);									  /*tr("变化步长(In):")*/
	rs_AddString(g_sLangID_Native_SglSideBalCoeff, &g_sLangTxt_Native_SglSideBalCoeff);					  /*tr("Ⅰ侧平衡系数")*/
	rs_AddString(g_sLangID_Native_TwoSideBalCoeff, &g_sLangTxt_Native_TwoSideBalCoeff);					  /*tr("Ⅱ侧平衡系数")*/
	rs_AddString(g_sLangID_Native_ThreeSideBalCoeff, &g_sLangTxt_Native_ThreeSideBalCoeff);				  /*tr("Ⅲ侧平衡系数")*/
	rs_AddString(g_sLangID_Native_WiringCoeff, &g_sLangTxt_Native_WiringCoeff);							  /*tr("接线系数")*/
	rs_AddString(g_sLangID_Native_RefCurr, &g_sLangTxt_Native_RefCurr);									  /*tr("基准电流")*/
	rs_AddString(g_sLangID_Native_HighVoltSide, &g_sLangTxt_Native_HighVoltSide);						  /*tr("   高压侧   ")*/
	rs_AddString(g_sLangID_Native_MedVoltSide, &g_sLangTxt_Native_MedVoltSide);							  /*tr("   中压侧   ")*/
	rs_AddString(g_sLangID_Native_LowVoltSide, &g_sLangTxt_Native_LowVoltSide);							  /*tr("   低压侧   ")*/
	rs_AddString(g_sLangID_Native_DiffProtCurrTerm, &g_sLangTxt_Native_DiffProtCurrTerm);				  /*tr("差动保护电流端子")*/
	rs_AddString(g_sLangID_Native_RelayTest, &g_sLangTxt_Native_RelayTest);								  /*tr("继电保护测试仪")*/
	rs_AddString(g_sLangID_Native_BrakeCurrSy, &g_sLangTxt_Native_BrakeCurrSy);							  /*tr("制动电流=%1A,")*/
	rs_AddString(g_sLangID_Native_DiffCurrSy, &g_sLangTxt_Native_DiffCurrSy);							  /*tr("差动电流=%1A,")*/
	rs_AddString(g_sLangID_Native_PropBrakeCoeffSy, &g_sLangTxt_Native_PropBrakeCoeffSy);				  /*tr("比例制动系数=%1")*/
	rs_AddString(g_sLangID_Native_BrakeCurrSyy, &g_sLangTxt_Native_BrakeCurrSyy);						  /*tr("制动电流=%1In,")*/
	rs_AddString(g_sLangID_Native_DiffCurrSyy, &g_sLangTxt_Native_DiffCurrSyy);							  /*tr("差动电流=%1In,")*/
	rs_AddString(g_sLangID_Native_TestProcMonView, &g_sLangTxt_Native_TestProcMonView);					  /*tr("测试过程监视图")*/
	rs_AddString(g_sLangID_Native_VecGraphics, &g_sLangTxt_Native_VecGraphics);							  /*tr("矢量图")*/
	rs_AddString(g_sLangID_Native_LineVolt, &g_sLangTxt_Native_LineVolt);								  /*tr("线电压")*/
	rs_AddString(g_sLangID_Native_InfoChart, &g_sLangTxt_Native_InfoChart);								  /*tr("信息图")*/
	rs_AddString(g_sLangID_Native_PowerChart, &g_sLangTxt_Native_PowerChart);							  /*tr("功率图")*/
	rs_AddString(g_sLangID_Native_CharactCurve, &g_sLangTxt_Native_CharactCurve);						  /*tr("动作特性曲线")*/
	rs_AddString(g_sLangID_Native_SearchUpperLimit, &g_sLangTxt_Native_SearchUpperLimit);				  /*tr("搜索上限(A)")*/
	rs_AddString(g_sLangID_Native_SearchLowerLimit, &g_sLangTxt_Native_SearchLowerLimit);				  /*tr("搜索下限(A)")*/
	rs_AddString(g_sLangID_Native_EnterValidNumber, &g_sLangTxt_Native_EnterValidNumber);				  /*tr("请输入有效数字！")*/
	rs_AddString(g_sLangID_Native_InputBrakeCurrOutOfRange, &g_sLangTxt_Native_InputBrakeCurrOutOfRange); /*_T("输入制动电流值[%f]不在有效范围.")*/
	rs_AddString(g_sLangID_Native_PrepTime, &g_sLangTxt_Native_PrepTime);								  /*tr("准备时间(S)")*/

	rs_AddString(g_sLangID_Native_BalanceCoeffEachSide, &g_sLangTxt_Native_BalanceCoeffEachSide);					/*tr("各侧平衡系数")*/
	rs_AddString(g_sLangID_Native_TestWinding, &g_sLangTxt_Native_TestWinding);										/*tr("测试绕组")*/

	rs_AddString(g_sLangID_Native_HVSDiffBalCoeff, &g_sLangTxt_Native_HVSDiffBalCoeff); /*tr("高压侧差动平衡系数")*/
	rs_AddString(g_sLangID_Native_MVSDiffBalCoeff, &g_sLangTxt_Native_MVSDiffBalCoeff); /*tr("中压侧差动平衡系数")*/
	rs_AddString(g_sLangID_Native_LVSDiffBalCoeff, &g_sLangTxt_Native_LVSDiffBalCoeff); /*tr("低压侧差动平衡系数")*/
	rs_AddString(g_sLangID_Native_InsSeries, &g_sLangTxt_Native_InsSeries);				// 插入系列
	rs_AddString(g_sLangID_Native_TestResEval, &g_sLangTxt_Native_TestResEval);			// 试验结果及评估
	rs_AddString(g_sLangID_Native_ErrBlank, &g_sLangTxt_Native_ErrBlank);				// 误  差
	rs_AddString(g_sLangID_Native_BrkCurrBlank, &g_sLangTxt_Native_BrkCurrBlank);		// 制  动  电  流

	// 第五周许
	// xwd 5
	rs_AddString(g_sLangID_Native_BrakingCurrent, &g_sLangTxt_Native_BrakingCurrent);
	rs_AddString(g_sLangID_Native_SearchUpper, &g_sLangTxt_Native_SearchUpper);
	rs_AddString(g_sLangID_Native_SearchLower, &g_sLangTxt_Native_SearchLower);
	rs_AddString(g_sLangID_Native_TestPrecision, &g_sLangTxt_Native_TestPrecisionA);
	rs_AddString(g_sLangID_Native_TestPrecisionIn, &g_sLangTxt_Native_TestPrecisionIn);
	rs_AddString(g_sLangID_Native_StartCurrent, &g_sLangTxt_Native_StartCurrent);
	rs_AddString(g_sLangID_Native_StartCurrentIn, &g_sLangTxt_Native_StartCurrentIn);
	rs_AddString(g_sLangID_Native_DiffCurrentIn, &g_sLangTxt_Native_DiffCurrentIn);
	rs_AddString(g_sLangID_Native_BrkCur, &g_sLangTxt_Native_BrkCur);
	rs_AddString(g_sLangID_Native_BrkCurIn, &g_sLangTxt_Native_BrkCurIn);
	rs_AddString(g_sLangID_Native_SrchUpLimA, &g_sLangTxt_Native_SrchUpLimA);
	rs_AddString(g_sLangID_Native_SrchLowLimA, &g_sLangTxt_Native_SrchLowLimA);
	rs_AddString(g_sLangID_Native_ValidNum, &g_sLangTxt_Native_ValidNum);

	// 第五周吕
	// exswitchset
	rs_AddString(g_sLangID_Native_BinEx20, &g_sLangTxt_Native_BinEx20); // 扩展开入量_20

	// OffLineDlg
	rs_AddString(g_sLangID_Native_TestModelTypeSelect, &g_sLangTxt_Native_TestModelTypeSelect); // 测试仪型号类型选择

	rs_AddString(g_sLangID_Native_tester_type, &g_sLangTxt_Native_tester_type);					   // 测试仪类型
	rs_AddString(g_sLangID_Native_digital_signal, &g_sLangTxt_Native_digital_signal);			   // 数字量
	rs_AddString(g_sLangID_Native_curmodule_set, &g_sLangTxt_Native_curmodule_set);				   // 电流模块设定
	rs_AddString(g_sLangID_Native_acrange_set, &g_sLangTxt_Native_acrange_set);					   // 交流电流档位设置
	rs_AddString(g_sLangID_Native_acmaxportvol_set, &g_sLangTxt_Native_acmaxportvol_set);		   // 交流电流最大端口电压设置
	rs_AddString(g_sLangID_Native_debounce_time, &g_sLangTxt_Native_debounce_time);				   // 防抖时间(S)：
	rs_AddString(g_sLangID_Native_highcurterm_Isoutput, &g_sLangTxt_Native_highcurterml_Isoutput); // 使用大电流端子Is输出
	rs_AddString(g_sLangID_Native_6Ito3I_output, &g_sLangTxt_Native_6Ito3I_output);				   // 电流6I合并成3I输出

	// dcSetdlg
	rs_AddString(g_sLangID_Native_auxiliary_DCvol, &g_sLangTxt_Native_auxiliary_DCvol);				  // 辅助直流电压(V)
	rs_AddString(g_sLangID_Native_start_DC_output, &g_sLangTxt_Native_start_DC_output);				  // 开始直流输出
	rs_AddString(g_sLangID_Native_stop_DC_output, &g_sLangTxt_Native_stop_DC_output);				  // 停止直流输出
	rs_AddString(g_sLangID_Native_start_steadyoutput, &g_sLangTxt_Native_start_steadyoutput);		  // 开始稳态量输出
	rs_AddString(g_sLangID_Native_stop_steadyoutput, &g_sLangTxt_Native_stop_steadyoutput);			  // 停止稳态量输出
	rs_AddString(g_sLangID_Native_AC_DC_steadyoutput, &g_sLangTxt_Native_AC_DC_steadyoutput);		  // 交直流稳态输出
	rs_AddString(g_sLangID_Native_auxiDC_output_notempty, &g_sLangTxt_Native_auxiDC_output_notempty); // 辅助直流输出不可为空
	rs_AddString(g_sLangID_Native_auxiDC_output_positive, &g_sLangTxt_Native_auxiDC_output_positive); // 要求：辅助直流输出>0

	// commonparasDlg
	rs_AddString(g_sLangID_Native_extractvol_outputdef, &g_sLangTxt_Native_extractvol_outputdef);	  // 抽取电压输出定义：
	rs_AddString(g_sLangID_Native_extractvol_refphasedef, &g_sLangTxt_Native_extractvol_refphasedef); // 抽取电压参考相定义:
	rs_AddString(g_sLangID_Native_extractvol_phaseangle, &g_sLangTxt_Native_extractvol_phaseangle);	  // 抽取电压相角：

	rs_AddString(g_sLangID_Native_coincidence_mode, &g_sLangTxt_Native_coincidence_mode);				  // 重合方式:
	rs_AddString(g_sLangID_Native_duration_afterjump, &g_sLangTxt_Native_duration_afterjump);			  // 开关跳后持续时间(s):
	rs_AddString(g_sLangID_Native_duration_coincidence, &g_sLangTxt_Native_duration_coincidence);		  // 重合持续时间(s):
	rs_AddString(g_sLangID_Native_postaccelerat_duration, &g_sLangTxt_Native_postaccelerat_duration);	  // 后加速开关跳开后持续时间(s):
	rs_AddString(g_sLangID_Native_impedance_refmode, &g_sLangTxt_Native_impedance_refmode);				  // 阻抗参考方式:
	rs_AddString(g_sLangID_Native_zeroseq_comp_calculat, &g_sLangTxt_Native_zeroseq_comp_calculat);		  // 零序补偿系数计算方式:
	rs_AddString(g_sLangID_Native_system_impedance, &g_sLangTxt_Native_system_impedance);				  // 系统阻抗(Ω):
	rs_AddString(g_sLangID_Native_system_impedance_angle, &g_sLangTxt_Native_system_impedance_angle);	  // 系统阻抗角(°):
	rs_AddString(g_sLangID_Native_closingangle_select, &g_sLangTxt_Native_closingangle_select);			  // 合闸角选择:
	rs_AddString(g_sLangID_Native_closingangle, &g_sLangTxt_Native_closingangle);						  // 合闸角(°):
	rs_AddString(g_sLangID_Native_closingangle_way, &g_sLangTxt_Native_closingangle_way);				  // 合闸角方式:
	rs_AddString(g_sLangID_Native_superimposed_nonperiodic, &g_sLangTxt_Native_superimposed_nonperiodic); // 叠加非周期分量(°):
	rs_AddString(g_sLangID_Native_search_mode, &g_sLangTxt_Native_search_mode);							  // 搜索方式:

	rs_AddString(g_sLangID_Native_testprocess_control, &g_sLangTxt_Native_testprocess_control);		// 试验过程控制方式:
	rs_AddString(g_sLangID_Native_faultphase_definition, &g_sLangTxt_Native_faultphase_definition); // 故障相定义:

	// debugCfgDlg
	rs_AddString(g_sLangID_Native_bottominfo_printset, &g_sLangTxt_Native_bottominfo_printset);			  // 底层信息打印设置
	rs_AddString(g_sLangID_Native_bottomloginfo_printornot, &g_sLangTxt_Native_bottomloginfo_printornot); // 是否打印底层日志信息
	rs_AddString(g_sLangID_Native_bottomtestinfo_saveornot, &g_sLangTxt_Native_bottomtestinfo_saveornot); // 是否保存底层测试信息

	// DifferCharacWidget
	rs_AddString(g_sLangID_Native_StartIr, &g_sLangTxt_Native_StartIr);					  // 启动Ir
	rs_AddString(g_sLangID_Native_RatioCoefficient, &g_sLangTxt_Native_RatioCoefficient); // 比率系数
	rs_AddString(g_sLangID_Native_AddTestPoint, &g_sLangTxt_Native_AddTestPoint);		  // 添加测试点

	rs_AddString(g_sLangID_Native_BreakoffIr, &g_sLangTxt_Native_BreakoffIr);	  // 速断Ir
	rs_AddString(g_sLangID_Native_HarmCountId2, &g_sLangTxt_Native_HarmCountId2); // 2次谐波Id
	rs_AddString(g_sLangID_Native_HarmCountId3, &g_sLangTxt_Native_HarmCountId3); // 3次谐波Id
	rs_AddString(g_sLangID_Native_HarmCountId5, &g_sLangTxt_Native_HarmCountId5); // 5次谐波Id

	// goose
	rs_AddString(g_sLangID_Native_statusName, &g_sLangTxt_Native_statusName); // 状态名称：
	rs_AddString(g_sLangID_Native_outputTime, &g_sLangTxt_Native_outputTime); // 输出时间(s):

	// 第五周马
	// partparawidget_trans

	rs_AddString(g_sLangID_Native_ExprOutOfRange, &g_sLangTxt_Native_ExprOutOfRange); // 表达式超出范围
	rs_AddString(g_sLangID_Native_ABCTP, &g_sLangTxt_Native_ABCTP);					  // ABC三相
	rs_AddString(g_sLangID_Native_Zphase, &g_sLangTxt_Native_Zphase);				  // Z相
	rs_AddString(g_sLangID_Native_ActPower, &g_sLangTxt_Native_ActPower);			  // 有功功率
	rs_AddString(g_sLangID_Native_ReacPower, &g_sLangTxt_Native_ReacPower);			  // 无功功率
	rs_AddString(g_sLangID_Native_AppPower, &g_sLangTxt_Native_AppPower);

	// QScanLanTesterDlg_trans
	rs_AddString(g_sLangID_Native_SubMask, &g_sLangTxt_Native_SubMask);								// 子网掩码
	rs_AddString(g_sLangID_Native_LST, &g_sLangTxt_Native_LST);										// 扫描局域网测试仪
	rs_AddString(g_sLangID_Native_NetAdptSelect, &g_sLangTxt_Native_NetAdptSelect);					// 网卡选择
	rs_AddString(g_sLangID_Native_ModTesterIP, &g_sLangTxt_Native_ModTesterIP);						// 修改测试仪IP
	rs_AddString(g_sLangID_Native_IPAddr, &g_sLangTxt_Native_IPAddr);								// IP地址
	rs_AddString(g_sLangID_Native_FailToRetrieveNetAddr, &g_sLangTxt_Native_FailToRetrieveNetAddr); // 获取本地IP地址失败,当前值为空.
	rs_AddString(g_sLangID_Native_FailToRetDevInfo, &g_sLangTxt_Native_FailToRetDevInfo);			// 取得设备信息失败
	rs_AddString(g_sLangID_Native_AddrNotInSameSubnet, &g_sLangTxt_Native_AddrNotInSameSubnet);		// 测试仪IP地址(%1)与当前网卡IP不在同一网段,是否修改?
	rs_AddString(g_sLangID_Native_CurrSelNetAdptEmpty, &g_sLangTxt_Native_CurrSelNetAdptEmpty);		// 当前选择的网卡为空.
	rs_AddString(g_sLangID_Native_Unknown, &g_sLangTxt_Native_Unknown);								// 未知
	rs_AddString(g_sLangID_Native_TestDevInfo, &g_sLangTxt_Native_TestDevInfo);						// 被测装置信息
	rs_AddString(g_sLangID_Native_PhAVoltage, &g_sLangTxt_Native_PhAVoltage);						// A相电压
	rs_AddString(g_sLangID_Native_PhBVoltage, &g_sLangTxt_Native_PhBVoltage);						// B相电压
	rs_AddString(g_sLangID_Native_PhCVoltage, &g_sLangTxt_Native_PhCVoltage);						// C相电压
	rs_AddString(g_sLangID_Native_PhABCVoltage, &g_sLangTxt_Native_PhABCVoltage);					// ABC相电压
	rs_AddString(g_sLangID_Native_TDITrigger, &g_sLangTxt_Native_TDITrigger);						// 时间+开入量触发
	rs_AddString(g_sLangID_Native_Overlay, &g_sLangTxt_Native_Overlay);								// 叠加
	rs_AddString(g_sLangID_Native_NoOverlay, &g_sLangTxt_Native_NoOverlay);							// 不叠加
	rs_AddString(g_sLangID_Native_Random, &g_sLangTxt_Native_Random);								// 随机

	rs_AddString(g_sLangID_Native_TestNameGenTest, &g_sLangTxt_Native_TestNameGenTest);

	rs_AddString(g_sLangID_Native_BalanceCoeff, &g_sLangTxt_Native_BalanceCoeff);
	rs_AddString(g_sLangID_Native_DiffFastCur, &g_sLangTxt_Native_DiffFastCur);
	rs_AddString(g_sLangID_Native_DiffActCur, &g_sLangTxt_Native_DiffActCur);
	rs_AddString(g_sLangID_Native_RatioBreakPt1, &g_sLangTxt_Native_RatioBreakPt1);
	rs_AddString(g_sLangID_Native_RatioBreakPt2, &g_sLangTxt_Native_RatioBreakPt2);
	rs_AddString(g_sLangID_Native_BaseRatioSlope1, &g_sLangTxt_Native_BaseRatioSlope1);
	rs_AddString(g_sLangID_Native_BaseRatioSlope2, &g_sLangTxt_Native_BaseRatioSlope2);
	rs_AddString(g_sLangID_Native_SecondHarmBrakeCoef, &g_sLangTxt_Native_SecondHarmBrakeCoef);
	rs_AddString(g_sLangID_Native_ThirdHarmBrakeCoef, &g_sLangTxt_Native_ThirdHarmBrakeCoef);
	rs_AddString(g_sLangID_Native_FifthHarmBrakeCoef, &g_sLangTxt_Native_FifthHarmBrakeCoef);

	// 第六周许

	rs_AddString(g_sLangID_Native_BulkWaveImport, &g_sLangTxt_Native_BulkWaveImport);
	rs_AddString(g_sLangID_Native_BulkWaveFileImport, &g_sLangTxt_Native_BulkWaveFileImport);
	rs_AddString(g_sLangID_Native_OpeningWaveFile, &g_sLangTxt_Native_OpeningWaveFile);
	rs_AddString(g_sLangID_Native_SelectFolder, &g_sLangTxt_Native_SelectFolder);
	rs_AddString(g_sLangID_Native_NoWaveFiles, &g_sLangTxt_Native_NoWaveFiles);
	rs_AddString(g_sLangID_Native_WaveExceedMax, &g_sLangTxt_Native_WaveExceedMax);
	rs_AddString(g_sLangID_Native_ApplyAllCh, &g_sLangTxt_Native_ApplyAllCh);
	rs_AddString(g_sLangID_Native_ApplyAllRatio, &g_sLangTxt_Native_ApplyAllRatio);
	rs_AddString(g_sLangID_Native_AllCycleCount, &g_sLangTxt_Native_AllCycleCount);
	rs_AddString(g_sLangID_Native_ManualCtrl, &g_sLangTxt_Native_ManualCtrl);
	rs_AddString(g_sLangID_Native_SelectWave, &g_sLangTxt_Native_SelectWave);
	rs_AddString(g_sLangID_Native_PlayPrev, &g_sLangTxt_Native_PlayPrev);
	rs_AddString(g_sLangID_Native_PlayNext, &g_sLangTxt_Native_PlayNext);
	rs_AddString(g_sLangID_Native_StopTestOut, &g_sLangTxt_Native_StopTestOut);
	rs_AddString(g_sLangID_Native_DiffCurve, &g_sLangTxt_Native_DiffCurve);
	rs_AddString(g_sLangID_Native_HarmBrakeCurve, &g_sLangTxt_Native_HarmBrakeCurve);
	rs_AddString(g_sLangID_Native_ActionTimeCurve, &g_sLangTxt_Native_ActionTimeCurve);
	rs_AddString(g_sLangID_Native_SOETestParamFileNotExist, &g_sLangTxt_Native_SOETestParamFileNotExist);
	rs_AddString(g_sLangID_Native_SOETestParamFileParseFail, &g_sLangTxt_Native_SOETestParamFileParseFail);

	// 第六周吕
	// 吕Overload Test
	rs_AddString(g_sLangID_Native_overloadACTestTempFile, &g_sLangTxt_Native_overloadACTestTempFile); // 过负荷(交流)试验模板文件
	rs_AddString(g_sLangID_Native_Wel_overloadACTest, &g_sLangTxt_Native_Wel_overloadACTest);		  // 欢迎使用过负荷(交流)试验.
	rs_AddString(g_sLangID_Native_Ponovo_overloadACTest, &g_sLangTxt_Native_Ponovo_overloadACTest);	  // Ponovo 过负荷(交流)试验
	rs_AddString(g_sLangID_Native_overloadACTest, &g_sLangTxt_Native_overloadACTest);				  // 过负荷(交流)试验

	rs_AddString(g_sLangID_Native_overloadCurrentChannel, &g_sLangTxt_Native_overloadCurrentChannel); // 过负荷电流通道
	rs_AddString(g_sLangID_Native_overloadCurChannel, &g_sLangTxt_Native_overloadCurChannel);		  // 过负荷电流通道:
	rs_AddString(g_sLangID_Native_overloadAC, &g_sLangTxt_Native_overloadAC);						  // 过负荷(交流)
	rs_AddString(g_sLangID_Native_overloadCurrentIA, &g_sLangTxt_Native_overloadCurrentIA);			  // 过负荷电流I(A):
	rs_AddString(g_sLangID_Native_NormTimeS, &g_sLangTxt_Native_NormTimeS);							  // 常态时间(s):

	// 第六周马
	rs_AddString(g_sLangID_Native_OverloadCurrTestTemplate, &g_sLangTxt_Native_OverloadCurrTestTemplate);	  /*tr("过负荷(电流)试验模板文件")*/
	rs_AddString(g_sLangID_Native_WelcomeToOverloadDCTest, &g_sLangTxt_Native_WelcomeToOverloadDCTest);		  /*_T("欢迎使用过负荷(直流)试验.")*/
	rs_AddString(g_sLangID_Native_OverloadDCTest, &g_sLangTxt_Native_OverloadDCTest);						  /*tr("Ponovo 过负荷(直流)试验")*/
	rs_AddString(g_sLangID_Native_ThermalOverloadTripSetting, &g_sLangTxt_Native_ThermalOverloadTripSetting); /*_T("热过负荷动作定值k")*/
	rs_AddString(g_sLangID_Native_ThermalOverloadRefCurr, &g_sLangTxt_Native_ThermalOverloadRefCurr);		  /*_T("热过负荷基准电流IB")*/
	rs_AddString(g_sLangID_Native_ThermalOverloadTimeConst, &g_sLangTxt_Native_ThermalOverloadTimeConst);	  /*_T("热过负荷时间常数τ")*/
	rs_AddString(g_sLangID_Native_RedefineToChar, &g_sLangTxt_Native_RedefineToChar);						  /*_T("输出参数导致动作时间定值为负数，未修改成功，请根据动作特性方程重新修改!")*/

	rs_AddString(g_sLangID_Native_OverloadDC, &g_sLangTxt_Native_OverloadDC);					/*"<h1>过负荷(直流)</h1>"*/
	rs_AddString(g_sLangID_Native_CurrChannelNotFound, &g_sLangTxt_Native_CurrChannelNotFound); /*_T("当前选择的电流通道(Index=%d)未查找到.")*/
	rs_AddString(g_sLangID_Native_ProtCharEquation, &g_sLangTxt_Native_ProtCharEquation);		/*QObject::tr("动作特性方程:")*/
	rs_AddString(g_sLangID_Native_OverloadCurr, &g_sLangTxt_Native_OverloadCurr);				// 过负荷电流

	rs_AddString(g_sLangID_Native_TotalMsgs, &g_sLangTxt_Native_TotalMsgs);			// 报文总数
	rs_AddString(g_sLangID_Native_PktLossCount, &g_sLangTxt_Native_PktLossCount);	// 丢包数
	rs_AddString(g_sLangID_Native_MaxTimeDiff, &g_sLangTxt_Native_MaxTimeDiff);		// 最大时间差
	rs_AddString(g_sLangID_Native_StopWriteFile, &g_sLangTxt_Native_StopWriteFile); // 停止写文件

	// 第七周吕
	// ovt
	rs_AddString(g_sLangID_Native_OVtempfile, &g_sLangTxt_Native_OVtempfile);					  // 过压试验模板文件
	rs_AddString(g_sLangID_Native_wel_OVtest, &g_sLangTxt_Native_wel_OVtest);					  // 欢迎使用过压测试.
	rs_AddString(g_sLangID_Native_OVprotect, &g_sLangTxt_Native_OVprotect);						  // 过电压保护
	rs_AddString(g_sLangID_Native_OverValtage, &g_sLangTxt_Native_OverValtage);					  // 过压
	rs_AddString(g_sLangID_Native_OVprotect_Actvalue, &g_sLangTxt_Native_OVprotect_Actvalue);	  // 过压保护动作值
	rs_AddString(g_sLangID_Native_OV_ActTimelim, &g_sLangTxt_Native_OV_ActTimelim);				  // 过电压动作时限
	rs_AddString(g_sLangID_Native_ActVNega_Error, &g_sLangTxt_Native_ActVNega_Error);			  // 当前动作电压为负，修改不成功.
	rs_AddString(g_sLangID_Native_ActTNega_Error, &g_sLangTxt_Native_ActTNega_Error);			  // 当前动作时间为负，修改不成功.
	rs_AddString(g_sLangID_Native_Name_OVprotectTest, &g_sLangTxt_Native_Name_OVprotectTest);	  // 试验名称：过压保护定值测试
	rs_AddString(g_sLangID_Native_OVprotectTest, &g_sLangTxt_Native_OVprotectTest);				  // 过压保护定值测试
	rs_AddString(g_sLangID_Native_1ErrorType_and_Times, &g_sLangTxt_Native_1ErrorType_and_Times); // 请务必至少选择一个故障类型以及倍数！
	rs_AddString(g_sLangID_Native_SetValueV, &g_sLangTxt_Native_SetValueV);						  // 整定值(V)
	rs_AddString(g_sLangID_Native_AddTestDig, &g_sLangTxt_Native_AddTestDig);					  // 添加测试项

	// 第七周马
	rs_AddString(g_sLangID_Native_VoltProtTestTplFile, &g_sLangTxt_Native_VoltProtTestTplFile);	  /*tr("电压保护试验模板文件")*/
	rs_AddString(g_sLangID_Native_WelcomeVoltProtTest, &g_sLangTxt_Native_WelcomeVoltProtTest);	  /*_T("欢迎使用电压保护测试.")*/
	rs_AddString(g_sLangID_Native_VoltProtection, &g_sLangTxt_Native_VoltProtection);			  /*tr("电压保护")*/
	rs_AddString(g_sLangID_Native_VIStagePickVal, &g_sLangTxt_Native_VIStagePickVal);			  /*_T("电压I段动作值")*/
	rs_AddString(g_sLangID_Native_VIIStagePickVal, &g_sLangTxt_Native_VIIStagePickVal);			  /*_T("电压II段动作值")*/
	rs_AddString(g_sLangID_Native_VIIIStagePickVal, &g_sLangTxt_Native_VIIIStagePickVal);		  /*_T("电压III段动作值")*/
	rs_AddString(g_sLangID_Native_VIVStagePickVal, &g_sLangTxt_Native_VIVStagePickVal);			  /*_T("电压IV段动作值")*/
	rs_AddString(g_sLangID_Native_VIPickTime, &g_sLangTxt_Native_VIPickTime);					  /*_T("电压I段动作时间")*/
	rs_AddString(g_sLangID_Native_VIIPickTime, &g_sLangTxt_Native_VIIPickTime);					  /*_T("电压II段动作时间")*/
	rs_AddString(g_sLangID_Native_VIIIPickTime, &g_sLangTxt_Native_VIIIPickTime);				  /*_T("电压III段动作时间")*/
	rs_AddString(g_sLangID_Native_VIVPickTime, &g_sLangTxt_Native_VIVPickTime);					  /*_T("电压IV段动作时间")*/
	rs_AddString(g_sLangID_Native_CurrPickNegModUnsucc, &g_sLangTxt_Native_CurrPickNegModUnsucc); /*_T("当前动作值为负，修改不成功.")*/
	rs_AddString(g_sLangID_Native_Ovltg, &g_sLangTxt_Native_Ovltg);								  /*_T("过电压")*/
	rs_AddString(g_sLangID_Native_OvltgProtSetTest, &g_sLangTxt_Native_OvltgProtSetTest);		  /*试验名称：过压保护定值测试*/
	rs_AddString(g_sLangID_Native_OvltgIProtSetTest, &g_sLangTxt_Native_OvltgIProtSetTest);		  /*"过压I段保护定值测试"*/
	rs_AddString(g_sLangID_Native_OvltgIIProtSetTest, &g_sLangTxt_Native_OvltgIIProtSetTest);	  /*"过压II段保护定值测试"*/
	rs_AddString(g_sLangID_Native_OvltgIIIProtSetTest, &g_sLangTxt_Native_OvltgIIIProtSetTest);	  /*"过压III段保护定值测试"*/
	rs_AddString(g_sLangID_Native_OvltgIVProtSetTest, &g_sLangTxt_Native_OvltgIVProtSetTest);	  /*"过压IV段保护定值测试"*/
	rs_AddString(g_sLangID_Native_OvltgVProtSetTest, &g_sLangTxt_Native_OvltgVProtSetTest);		  /*"过压V段保护定值测试"*/
	rs_AddString(g_sLangID_Native_PreFaultOut, &g_sLangTxt_Native_PreFaultOut);					  /*tr("故障前输出")*/

	rs_AddString(g_sLangID_Native_PreFaultTimeMargin, &g_sLangTxt_Native_PreFaultTimeMargin);				/*tr("故障前时间裕度")*/
	rs_AddString(g_sLangID_Native_CSVLessMinModUnsucc, &g_sLangTxt_Native_CSVLessMinModUnsucc);				/*_T("当前设置值(%f)小于最小值(0.000000),修改不成功")*/
	rs_AddString(g_sLangID_Native_CSVGreaterMaxForceSetMax, &g_sLangTxt_Native_CSVGreaterMaxForceSetMax);	/*_T("当前设置值(%f)大于最大值(%f),强制设置为最大值")*/
	rs_AddString(g_sLangID_Native_CSVGreaterMaxForceSetMax9, &g_sLangTxt_Native_CSVGreaterMaxForceSetMax9); /*_T("当前设置值(%f)大于最大值(999.000000),强制设置为最大值")*/
}

void CXLangResource_PowerTestWin::InitLangTxt()
{
	CXLangResource_Native::InitLangTxt();

	// LY 吕
	g_sLangID_ActTime_Protect_TestTempFile = _T("ActTime_Protect_TestTempFile");
	g_sLangTxt_ActTime_Protect_TestTempFile = _T("动作时间保护试验模板文件");
	g_sLangID_ActionTime_test = _T("ActionTime_test");
	g_sLangTxt_ActionTime_test = _T("欢迎使用动作时间实验");
	g_sLangID_Native_PonovoActiontime = _T("Native_PonovoActiontime");
	g_sLangTxt_Native_PonovoActiontime = _T("Ponovo动作时间");
	g_sLangID_ActionTimeTest = _T("ActionTimeTest");
	g_sLangTxt_ActionTimeTest = _T("动作时间测试");
	g_sLangID_Single_phaseGroundFault = _T("Single_phaseGroundFault");
	g_sLangTxt_Single_phaseGroundFault = _T("单相接地短路");
	g_sLangID_PhasetoPhase_ShortCircuit = _T("PhasetoPhase_ShortCircuit");
	g_sLangTxt_PhasetoPhase_ShortCircuit = _T("相间短路");
	g_sLangID_Zero_SequenceCurrent = _T("Zero_SequenceCurrent");
	g_sLangTxt_Zero_SequenceCurrent = _T("零序电流");
	g_sLangID_Negative_SequenceCurrent = _T("Negative_SequenceCurrent");
	g_sLangTxt_Negative_SequenceCurrent = _T("负序电流");
	g_sLangID_ParaConnect_Three_PhaseCurrents = _T("ParaConnect_Three_PhaseCurrents");
	g_sLangTxt_ParaConnect_Three_PhaseCurrents = _T("三相电流并联");
	g_sLangID_Single_PhaseFault = _T("Single_PhaseFault");
	g_sLangTxt_Single_PhaseFault = _T("单相故障");
	// 吕
	g_sLangID_AutoSyn_TestTempFile = _T("AutoSyn_TestTempFile");
	g_sLangTxt_AutoSyn_TestTempFile = _T("自动准周期试验模板文件");
	g_sLangID_Wel_AutoSynTest = _T("Wel_AutoSynTest");
	g_sLangTxt_Wel_AutoSynTest = _T("欢迎使用自动准同期试验");
	g_sLangID_Ponovo_AutoSyn = _T("Ponovo_AutoSyn");
	g_sLangTxt_Ponovo_AutoSyn = _T("Ponovo自动准同期");
	g_sLangID_AutoSyn = _T("AutoSyn");
	g_sLangTxt_AutoSyn = _T("自动准同期");


	g_sLangID_System_Rated_FreqHZ = _T("System_Rated_FreqHZ");
	g_sLangTxt_System_Rated_FreqHZ = _T("系统侧额定频率（Hz）");
	g_sLangID_System_Rated_Volt = _T("System_Rated_Volt");
	g_sLangTxt_System_Rated_Volt = _T("系统侧额定电压（V）");
	g_sLangID_Grid_VolV = _T("Grid_VolV");
	g_sLangTxt_Grid_VolV = _T("待并侧电压（V）");
	g_sLangID_Stepsize_Grid_volvariation = _T("Stepsize_Grid_volvariation");
	g_sLangTxt_Stepsize_Grid_volvariation = _T("待并侧电压变化步长（V）");


	g_sLangID_Grid_Rated_VolV = _T("Grid_Rated_VolV");
	g_sLangTxt_Grid_Rated_VolV = _T("待并侧额定电压（V）");




	g_sLangID_VolDifference = _T("VolDifference");
	g_sLangTxt_VolDifference = _T("压差（V）");


	g_sLangID_Allow_VolDifV = _T("Allow_VolDifV");
	g_sLangTxt_Allow_VolDifV = _T("允许压差（V）");
	g_sLangID_FreqDifference = _T("FreqDifference");
	g_sLangTxt_FreqDifference = _T("频差（HZ）");


	g_sLangID_Allow_FreqDifHZ = _T("Allow_FreqDifHZ");
	g_sLangTxt_Allow_FreqDifHZ = _T("允许频差（Hz）");
	g_sLangID_Vol_ReguPeriod = _T("Vol_ReguPeriod");

	g_sLangID_Vol_BoundValueTest = _T("Vol_BoundValueTest");
	g_sLangTxt_Vol_BoundValueTest = _T("电压边界值测试");
	g_sLangID_Volbound_trip_values = _T("Volbound_trip_values");
	g_sLangTxt_Volbound_trip_values = _T("电压边界值动作值（V）");
	g_sLangID_Freq_BoundValueTest = _T("Freq_BoundValueTest");
	g_sLangTxt_Freq_BoundValueTest = _T("频率边界值测试");
	g_sLangID_Auto_AdjustTest = _T("Auto_AdjustTest");
	g_sLangTxt_Auto_AdjustTest = _T("自动调整试验");
	g_sLangID_Vol_ReguPeriodTest = _T("Vol_ReguPeriodTest");
	g_sLangTxt_Vol_ReguPeriodTest = _T("调压周期测试");
	g_sLangID_Freq_ReguPeriodTest = _T("Freq_ReguPeriodTest");
	g_sLangTxt_Freq_ReguPeriodTest = _T("调频周期测试");
	g_sLangID_Lead_AngleTime_Test = _T("Lead_AngleTime_Test");
	g_sLangTxt_Lead_AngleTime_Test = _T("导前角及导前时间测试");
	g_sLangID_result = _T("result");
	g_sLangTxt_result = _T("结论");
	g_sLangID_Stepsize_Grid_freqvariation = _T("Stepsize_Grid_freqvariation");
	g_sLangTxt_Stepsize_Grid_freqvariation = _T("待并侧频率变化步长（HZ）");
	g_sLangID_Freqbound_trip_values = _T("Freqbound_trip_values");
	g_sLangTxt_Freqbound_trip_values = _T("频率边界值动作值（HZ）");
	g_sLangID_Leading_Angle = _T("Leading_Angle");
	g_sLangTxt_Leading_Angle = _T("导前角（°）");
	g_sLangID_Leading_Time = _T("Leading_Time");
	g_sLangTxt_Leading_Time = _T("导前时间（s）");
	g_sLangID_Native_dVzd = _T("Native_dVzd");
	g_sLangTxt_Native_dVzd = _T("允许压差整定值（V）");
	g_sLangID_Native_dFzd = _T("Native_dFzd");
	g_sLangTxt_Native_dFzd = _T("允许频差整定值（HZ）");
	g_sLangID_Native_Ut = _T("Native_Ut");
	g_sLangTxt_Native_Ut = _T("调压周期整定值（s）");
	g_sLangID_AdjVolCycle = _T("AdjVolCycle");
	g_sLangTxt_AdjVolCycle = _T("调压周期动作值（s）");
	g_sLangID_AdjVolWidth = _T("AdjVolWidth");
	g_sLangTxt_AdjVolWidth = _T("调压脉宽（s）");
	g_sLangID_Native_Ft = _T("Native_Ft");
	g_sLangTxt_Native_Ft = _T("调频周期整定值（s）");
	g_sLangID_AdjFreqCycle = _T("AdjFreqCycle");
	g_sLangTxt_AdjFreqCycle = _T("调频周期动作值（s）");
	g_sLangID_AdjFreqWidth = _T("AdjFreqWidth");
	g_sLangTxt_AdjFreqWidth = _T("调频脉宽（s）");
	g_sLangID_Native_System = _T("Native_System");
	g_sLangTxt_Native_System = _T("系统");
	g_sLangID_waitgrid_connection = _T("waitgrid_connection");
	g_sLangTxt_waitgrid_connection = _T("待并");


	g_sLangID_expression_error = _T("expression_error");
	g_sLangTxt_expression_error = _T("表达式输出错误");

	g_sLangID_Out4_Time = _T("Out4_Time");
	g_sLangTxt_Out4_Time = _T("开出4保持时间（s）");

	g_sLangID_protectexport_sign = _T("protectexport_sign");
	g_sLangTxt_protectexport_sign = _T("保护出口信号");
	g_sLangID_boost_sign = _T("boost_sign");
	g_sLangTxt_boost_sign = _T("增压信号");
	g_sLangID_reduce_sign = _T("reduce_sign");
	g_sLangTxt_reduce_sign = _T("减压信号");
	g_sLangID_speed_sign = _T("speed_sign");
	g_sLangTxt_speed_sign = _T("增速信号");
	g_sLangID_slow_sign = _T("slow_sign");
	g_sLangTxt_slow_sign = _T("减速信号");

	g_sLangID_pulse = _T("pulse");
	g_sLangTxt_pulse = _T("脉冲");
	g_sLangID_continue = _T("continue");
	g_sLangTxt_continue = _T("连续");
	g_sLangID_value = _T("value");
	g_sLangTxt_value = _T("值");
	// 吕
	g_sLangID_lowfreqloadre_tempfile = _T("lowfreqloadre_tempfile");
	g_sLangTxt_lowfreqloadre_tempfile = _T("低周减载模板文件");
	g_sLangID_wel_lowfreqloadre = _T("wel_lowfreqloadre");
	g_sLangTxt_wel_lowfreqloadre = _T("欢迎使用低周减载");
	g_sLangID_Ponovo_lowfreqloadre = _T("Ponovo_lowfreqloadre");
	g_sLangTxt_Ponovo_lowfreqloadre = _T("Ponovo 低周减载");
	g_sLangID_lowfreqloadre = _T("lowfreqloadre");
	g_sLangTxt_lowfreqloadre = _T("低周减载");
	g_sLangID_Noselect_testitems = _T("Noselect_testitems");
	g_sLangTxt_Noselect_testitems = _T("没有选择测试项");
	g_sLangID_Atleast1_5testitems = _T("Atleast1_5testitems");
	g_sLangTxt_Atleast1_5testitems = _T("5种测试类型至少各保留一个测试项!");
	g_sLangID_Atleast1_Thistestitems = _T("Atleast1_Thistestitems");
	g_sLangTxt_Atleast1_Thistestitems = _T("此测试类型至少保留一个测试项!");
	g_sLangID_Native_FreAction = _T("Native_FreAction");
	g_sLangTxt_Native_FreAction = _T("动作频率");
	g_sLangID_Native_sliptrip = _T("Native_sliptrip");
	g_sLangTxt_Native_sliptrip = _T("滑差闭锁");
// 	g_sLangID_Voltage = _T("Voltage");
// 	g_sLangTxt_Voltage = _T("电压（V）");
	g_sLangID_lowVoltage = _T("lowVoltage");
	g_sLangTxt_lowVoltage = _T("低压");
	g_sLangID_interlock_volselection = _T("interlock_volselection");
	g_sLangTxt_interlock_volselection = _T("闭锁电压选择");
	g_sLangID_FreAValue_Test = _T("FreAValue_Test");
	g_sLangTxt_FreAValue_Test = _T("频率动作值测试");
	g_sLangID_Native_sliptripTest = _T("Native_sliptripTest");
	g_sLangTxt_Native_sliptripTest = _T("滑差闭锁值测试");
	g_sLangID_lowcur_lockout_test = _T("lowcur_lockout_test");
	g_sLangTxt_lowcur_lockout_test = _T("低电流闭锁值测试");
	g_sLangID_Native_LowVoltLock_test = _T("Native_LowVoltLock_test");
	g_sLangTxt_Native_LowVoltLock_test = _T("低电压闭锁值测试");
	g_sLangID_lowfreqloadre_Setting = _T("lowfreqloadre_Setting");
	g_sLangTxt_lowfreqloadre_Setting = _T("低周减载动作值");

	g_sLangID_lowcur_lockout = _T("lowcur_lockout");
	g_sLangTxt_lowcur_lockout = _T("低电流闭锁值");

	g_sLangID_Negative_SeqVolU2 = _T("Negative_SeqVolU2");
	g_sLangTxt_Negative_SeqVolU2 = _T("负序电压(U2)");
	g_sLangID_Zero_SeqCur3U0 = _T("Zero_SeqCur3U0");
	g_sLangTxt_Zero_SeqCur3U0 = _T("零序电压(3U0)");
	g_sLangID_Illegal_testitem = _T("Illegal_testitem");
	g_sLangTxt_Illegal_testitem = _T("测试项类型非法.");
	g_sLangID_Native_OutOf_Range = _T("Native_OutOf_Range");
	g_sLangTxt_Native_OutOf_Range = _T("超出变化范围");
	g_sLangID_action_freqvalue = _T("action_freqvalue");
	g_sLangTxt_action_freqvalue = _T("动作频率值");


	// LowUTest_Trans 马
	g_sLangID_Native_LVLoadRedTemp = _T("Native_LVLoadRedTemp");
	g_sLangTxt_Native_LVLoadRedTemp = _T("低压减载试验模板文件");
	g_sLangID_Native_WLULVLRTest = _T("Native_WLULVLRTest");
	g_sLangTxt_Native_WLULVLRTest = _T("欢迎使用低压减载试验.");
	g_sLangID_Native_PLVLRTitle = _T("Native_PLVLRTitle");
	g_sLangTxt_Native_PLVLRTitle = _T("Ponovo 低压减载");
	g_sLangID_Native_LowVLoadRed = _T("Native_LowVLoadRed");
	g_sLangTxt_Native_LowVLoadRed = _T("低压减载");


	g_sLangID_Native_KeepOneTest = _T("Native_KeepOneTest");
	g_sLangTxt_Native_KeepOneTest = _T("至少保留一个测试项!");


	g_sLangID_Native_ProgRunning = _T("Native_ProgRunning");
	g_sLangTxt_Native_ProgRunning = _T("程序已经在运行！");
	g_sLangID_Native_LVLRTesting = _T("Native_LVLRTesting");
	g_sLangTxt_Native_LVLRTesting = _T("低压减载测试");
	g_sLangID_Native_LowVoltLock = _T("Native_LowVoltLock");
	g_sLangTxt_Native_LowVoltLock = _T("低电压闭锁值");
// 	g_sLangID_Native_ActTimeSym = _T("Native_ActTimeSym");
// 	g_sLangTxt_Native_ActTimeSym = _T("动作时间=%1s");
	g_sLangID_Native_VoltSlipLock = _T("Native_VoltSlipLock");
	g_sLangTxt_Native_VoltSlipLock = _T("电压滑差闭锁值=%1V/s");
	g_sLangID_Native_PhaseVoltStepV = _T("Native_PhaseVoltStepV");
	g_sLangTxt_Native_PhaseVoltStepV = _T("相电压变化步长(V):");
	g_sLangID_Native_PhaseVoltBeginV = _T("Native_PhaseVoltBeginV");
	g_sLangTxt_Native_PhaseVoltBeginV = _T("相电压变化始值(V):");
	g_sLangID_Native_PhaseVoltStartV = _T("Native_PhaseVoltStartV");
	g_sLangTxt_Native_PhaseVoltStartV = _T("相电压变化起始值(V):");
	g_sLangID_Native_PhaseVoltEndV = _T("Native_PhaseVoltEndV");
	g_sLangTxt_Native_PhaseVoltEndV = _T("相电压变化结束值(V):");
	g_sLangID_Native_LineVoltStepV = _T("Native_LineVoltStepV");
	g_sLangTxt_Native_LineVoltStepV = _T("线电压变化步长(V):");
	g_sLangID_Native_LineVoltStartV = _T("Native_LineVoltStartV");
	g_sLangTxt_Native_LineVoltStartV = _T("线电压变化起始值(V):");
	g_sLangID_Native_LineVoltEndV = _T("Native_LineVoltEndV");
	g_sLangTxt_Native_LineVoltEndV = _T("线电压变化结束值(V):");
	g_sLangID_Native_PhaseVoltFinal = _T("Native_PhaseVoltFinal");
	g_sLangTxt_Native_PhaseVoltFinal = _T("相电压变化终值(V):");
	g_sLangID_Native_LineVoltFinal = _T("Native_LineVoltFinal");
	g_sLangTxt_Native_LineVoltFinal = _T("线电压变化终值(V):");
	g_sLangID_Native_PhaseVSlipStep = _T("Native_PhaseVSlipStep");
	g_sLangTxt_Native_PhaseVSlipStep = _T("相电压滑差变化步长(V/s):");
	g_sLangID_Native_LineVSlipStep = _T("Native_LineVSlipStep");
	g_sLangTxt_Native_LineVSlipStep = _T("线电压滑差变化步长(V/s):");
	g_sLangID_Native_PhaseVSlipStart = _T("Native_PhaseVSlipStart");
	g_sLangTxt_Native_PhaseVSlipStart = _T("相电压滑差变化始值(V/s):");
	g_sLangID_Native_LineVSlipStart = _T("Native_LineVSlipStart");
	g_sLangTxt_Native_LineVSlipStart = _T("线电压滑差变化始值(V/s):");
	g_sLangID_Native_PhaseVSlipEnd = _T("Native_PhaseVSlipEnd");
	g_sLangTxt_Native_PhaseVSlipEnd = _T("相电压滑差变化终值(V/s):");
	g_sLangID_Native_LineVSlipEnd = _T("Native_LineVSlipEnd");
	g_sLangTxt_Native_LineVSlipEnd = _T("线电压滑差变化终值(V/s):");
	g_sLangID_Native_ExprInputErr = _T("Native_ExprInputErr");
	g_sLangTxt_Native_ExprInputErr = _T("表达式输入错误");
	g_sLangID_Native_OutOfRange = _T("Native_OutOfRange");
	g_sLangTxt_Native_OutOfRange = _T("超出范围");
	g_sLangID_Native_VarStepExceed60P = _T("Native_VarStepExceed60P");
	g_sLangTxt_Native_VarStepExceed60P = _T("递变步数超过60，请重新输入！");
	g_sLangID_Native_SteadyStateTime = _T("Native_SteadyStateTime");
	g_sLangTxt_Native_SteadyStateTime = _T("稳态时间(s):");





	// PowerDirectionTest_Trans 马
	g_sLangID_Native_PowerDirTemp = _T("Native_PowerDirTemp");
	g_sLangTxt_Native_PowerDirTemp = _T("功率方向试验模板文件");
	g_sLangID_Native_WelcomePD = _T("Native_WelcomePD");
	g_sLangTxt_Native_WelcomePD = _T("欢迎使用功率方向.");
	g_sLangID_Native_GetRealTimeFail = _T("Native_GetRealTimeFail");
	g_sLangTxt_Native_GetRealTimeFail = _T("获取实时数据绝对时间失败.");
	g_sLangID_Native_GetRelTimeFail = _T("Native_GetRelTimeFail");
	g_sLangTxt_Native_GetRelTimeFail = _T("获取实时数据相对时间失败.");
	g_sLangID_Native_PonovoPower = _T("Native_PonovoPower");
	g_sLangTxt_Native_PonovoPower = _T("Ponovo 功率方向");
	g_sLangID_Native_PowerDir = _T("Native_PowerDir");
	g_sLangTxt_Native_PowerDir = _T("功率方向");

	g_sLangID_Native_Assessment = _T("Native_Assessment");
	g_sLangTxt_Native_Assessment = _T("评估");
	g_sLangID_Native_PowerDirTest = _T("Native_PowerDirTest");
	g_sLangTxt_Native_PowerDirTest = _T("功率方向测试");
	g_sLangID_Native_PhaseATest = _T("Native_PhaseATest");
	g_sLangTxt_Native_PhaseATest = _T("A相测试");
	g_sLangID_Native_PhaseBTest = _T("Native_PhaseBTest");
	g_sLangTxt_Native_PhaseBTest = _T("B相测试");
	g_sLangID_Native_PhaseCTest = _T("Native_PhaseCTest");
	g_sLangTxt_Native_PhaseCTest = _T("C相测试");
	g_sLangID_Native_PhaseZeroTest = _T("Native_PhaseZeroTest");
	g_sLangTxt_Native_PhaseZeroTest = _T("零序测试");
	g_sLangID_Native_PhaseLossTest = _T("Native_PhaseLossTest");
	g_sLangTxt_Native_PhaseLossTest = _T("负序测试");
	g_sLangID_Native_VoltAheadPosAng = _T("Native_VoltAheadPosAng");
	g_sLangTxt_Native_VoltAheadPosAng = _T("电压超前电流为正角度");
	g_sLangID_Native_CurrAheadPosAng = _T("Native_CurrAheadPosAng");
	g_sLangTxt_Native_CurrAheadPosAng = _T("电流超前电压为正角度");
	g_sLangID_Native_Deg0Conn = _T("Native_Deg0Conn");
	g_sLangTxt_Native_Deg0Conn = _T("0度接线");
	g_sLangID_Native_Deg90Conn = _T("Native_Deg90Conn");
	g_sLangTxt_Native_Deg90Conn = _T("90度接线");
	g_sLangID_Native_GenParamSet = _T("Native_GenParamSet");
	g_sLangTxt_Native_GenParamSet = _T("通用参数设置");

	// PowerFreqTest_Trans 马
	g_sLangID_Native_FreqChgDistTemp = _T("Native_FreqChgDistTemp");
	g_sLangTxt_Native_FreqChgDistTemp = _T("工频变化量距离试验模板文件");
	g_sLangID_Native_WelcFreqChgTest = _T("Native_WelcFreqChgTest");
	g_sLangTxt_Native_WelcFreqChgTest = _T("欢迎使用工频变化量距离试验.");
	g_sLangID_Native_PonovoFreqChgDist = _T("Native_PonovoFreqChgDist");
	g_sLangTxt_Native_PonovoFreqChgDist = _T("Ponovo 工频变化量距离");
	g_sLangID_Native_FreqChgDistance = _T("Native_FreqChgDistance");
	g_sLangTxt_Native_FreqChgDistance = _T("工频变化量距离");
	g_sLangID_Native_ImpedChart = _T("Native_ImpedChart");
	g_sLangTxt_Native_ImpedChart = _T("阻抗特性图");

	
	g_sLangID_Native_PhaseAGround = _T("Native_PhaseAGround");
	g_sLangTxt_Native_PhaseAGround = _T("A相接地,");
	g_sLangID_Native_PhaseBGround = _T("Native_PhaseBGround");
	g_sLangTxt_Native_PhaseBGround = _T("B相接地,");
	g_sLangID_Native_PhaseCGround = _T("Native_PhaseCGround");
	g_sLangTxt_Native_PhaseCGround = _T("C相接地,");
	g_sLangID_Native_PhaseABShortCircuit = _T("Native_PhaseABShortCircuit");
	g_sLangTxt_Native_PhaseABShortCircuit = _T("AB短路,");
	g_sLangID_Native_PhaseBCShortCircuit = _T("Native_PhaseBCShortCircuit");
	g_sLangTxt_Native_PhaseBCShortCircuit = _T("BC短路,");
	g_sLangID_Native_PhaseCAShortCircuit = _T("Native_PhaseCAShortCircuit");
	g_sLangTxt_Native_PhaseCAShortCircuit = _T("CA短路,");
	g_sLangID_Native_Instantaneous = _T("Native_Instantaneous");
	g_sLangTxt_Native_Instantaneous = _T("瞬时,");
	g_sLangID_Native_Permanently = _T("Native_Permanently");
	g_sLangTxt_Native_Permanently = _T("永久,");
	g_sLangID_Native_FreqChgDistTest = _T("Native_FreqChgDistTest");
	g_sLangTxt_Native_FreqChgDistTest = _T("<h1>工频变化量距离测试</h1>");
	g_sLangID_Native_FreqChgDist = _T("Native_FreqChgDist");
	g_sLangTxt_Native_FreqChgDist = _T("工频变化量距离");
	g_sLangID_Native_PosDirection = _T("Native_PosDirection");
	g_sLangTxt_Native_PosDirection = _T("正方向");
	g_sLangID_Native_RevDirection = _T("Native_RevDirection");
	g_sLangTxt_Native_RevDirection = _T("反方向");
	g_sLangID_OKCancel = _T("Native_ConfirmCancel");
	g_sLangTxt_OKCancel = _T("确定取消");
	g_sLangID_Native_BusSide = _T("Native_BusSide");
	g_sLangTxt_Native_BusSide = _T("母线侧");
	g_sLangID_Native_LineSide = _T("Native_LineSide");
	g_sLangTxt_Native_LineSide = _T("线路侧");
	g_sLangID_Native_TowardBus = _T("Native_TowardBus");
	g_sLangTxt_Native_TowardBus = _T("指向母线");
	g_sLangID_Native_TowardLine = _T("Native_TowardLine");
	g_sLangTxt_Native_TowardLine = _T("指向线路");
	g_sLangID_Native_NoSimulation = _T("Native_NoSimulation");
	g_sLangTxt_Native_NoSimulation = _T("不模拟");
	g_sLangID_Native_OppositeDirection = _T("Native_OppositeDirection");
	g_sLangTxt_Native_OppositeDirection = _T("反向");
	g_sLangID_Native_PositiveDirection = _T("Native_PositiveDirection");
	g_sLangTxt_Native_PositiveDirection = _T("正向");
	g_sLangID_Native_Immediate = _T("Native_Immediate");
	g_sLangTxt_Native_Immediate = _T("瞬时");
	g_sLangID_Native_Permanent = _T("Native_Permanent");
	g_sLangTxt_Native_Permanent = _T("永久");
	g_sLangID_Native_Trip3Phase = _T("Native_Trip3Phase");
	g_sLangTxt_Native_Trip3Phase = _T("跳三相=%1s,");
	g_sLangID_Native_TripPhaseA = _T("Native_TripPhaseA");
	g_sLangTxt_Native_TripPhaseA = _T("跳A=%1s,");
	g_sLangID_Native_TripPhaseB = _T("Native_TripPhaseB");
	g_sLangTxt_Native_TripPhaseB = _T("跳B=%1s,");
	g_sLangID_Native_TripPhaseC = _T("Native_TripPhaseC");
	g_sLangTxt_Native_TripPhaseC = _T("跳C=%1s,");
	g_sLangID_Native_ReclosingSy = _T("Native_ReclosingSy");
	g_sLangTxt_Native_ReclosingSy = _T("重合闸=%1s,");
	g_sLangID_Native_PostAccel = _T("Native_PostAccel");
	g_sLangTxt_Native_PostAccel = _T("后加速=%1s,");
	g_sLangID_Native_TimeofReturn = _T("Native_TimeofReturn");
	g_sLangTxt_Native_TimeofReturn = _T("返回时间=%1s,");
	g_sLangID_Native_TimeofReturnA = _T("Native_TimeofReturnA");
	g_sLangTxt_Native_TimeofReturnA = _T("返回时间A=%1s,");
	g_sLangID_Native_TimeofReturnB = _T("Native_TimeofReturnB");
	g_sLangTxt_Native_TimeofReturnB = _T("返回时间B=%1s,");
	g_sLangID_Native_TimeofReturnC = _T("Native_TimeofReturnC");
	g_sLangTxt_Native_TimeofReturnC = _T("返回时间C=%1s,");
	g_sLangID_Native_TimeofReturnD = _T("Native_TimeofReturnD");
	g_sLangTxt_Native_TimeofReturnD = _T("返回时间D=%1s,");
	g_sLangID_Native_TVInstLoc = _T("Native_TVInstLoc");
	g_sLangTxt_Native_TVInstLoc = _T("TV安装位置");
	g_sLangID_Native_PosPolTA = _T("Native_PosPolTA");
	g_sLangTxt_Native_PosPolTA = _T("TA正极性");
	g_sLangID_Native_CBsim = _T("Native_CBsim");
	g_sLangTxt_Native_CBsim = _T("断路器模拟");
	g_sLangID_Native_TripTime = _T("Native_TripTime");
	g_sLangTxt_Native_TripTime = _T("分闸时间");
	g_sLangID_Native_CloseTime = _T("Native_CloseTime");
	g_sLangTxt_Native_CloseTime = _T("合闸时间");
	g_sLangID_Native_ImpChar = _T("Native_ImpChar");
	g_sLangTxt_Native_ImpChar = _T("阻抗特性");


	// start XWD
	g_sLangID_Native_RLPtestTF = _T("Native_RLPtestTF");
	g_sLangTxt_Native_RLPtestTF = _T("复压闭锁保护试验模板文件");
	g_sLangID_Native_WelUseRLPT = _T("Native_WelUseRLPT");
	g_sLangTxt_Native_WelUseRLPT = _T("欢迎使用复压闭锁保护试验");
	g_sLangID_Native_AbsoluteTimeF = _T("Native_AbsoluteTimeF");
	g_sLangTxt_Native_AbsoluteTimeF = _T("获取实时数据绝对时间失败");
	g_sLangID_Native_RelativeTimeF = _T("Native_RelativeTimeF");
	g_sLangTxt_Native_RelativeTimeF = _T("获取实时数据相对时间失败");
	g_sLangID_Native_PonovoRLO = _T("Native_PonovoRLO");
	g_sLangTxt_Native_PonovoRLO = _T("Ponovo复压闭锁");
	g_sLangID_Native_RLOtest = _T("Native_RLOtest");
	g_sLangTxt_Native_RLOtest = _T("复压闭锁实验");
	g_sLangID_Native_LowVoltage = _T("Native_LowVoltage");
	g_sLangTxt_Native_LowVoltage = _T("低电压");
	g_sLangID_Native_NegSeqVol = _T("Native_NegSeqVol");
	g_sLangTxt_Native_NegSeqVol = _T("负序电压");
	g_sLangID_Native_ActCurrent = _T("Native_ActCurrent");
	g_sLangTxt_Native_ActCurrent = _T("动作电流");
	g_sLangID_Native_ActAreaSize = _T("Native_ActAreaSize");
	g_sLangTxt_Native_ActAreaSize = _T("动作区大小");

	g_sLangID_Native_LowVolTriVal = _T("Native_LowVolTriVal");
	g_sLangTxt_Native_LowVolTriVal = _T("低电压动作值");
	g_sLangID_Native_NegSeqVolTriVal = _T("Native_NegSeqVolTriVal");
	g_sLangTxt_Native_NegSeqVolTriVal = _T("负序电压动作值");
	g_sLangID_Native_CurOperC = _T("Native_CurOperC");
	g_sLangTxt_Native_CurOperC = _T("电流动作值（C相）");
	g_sLangID_Native_CurOperB = _T("Native_CurOperB");
	g_sLangTxt_Native_CurOperB = _T("电流动作值（B相）");
	g_sLangID_Native_CurOperA = _T("Native_CurOperA");
	g_sLangTxt_Native_CurOperA = _T("电流动作值（A相）");
	g_sLangID_Native_MaxSensAngTest = _T("Native_MaxSensAngTest");
	g_sLangTxt_Native_MaxSensAngTest = _T("最大灵敏角测试");
	g_sLangID_Native_CurOperVal = _T("Native_CurOperVal");
	g_sLangTxt_Native_CurOperVal = _T("电流动作值");
	g_sLangID_Native_AnBShortCir = _T("Native_AnBShortCir");
	g_sLangTxt_Native_AnBShortCir = _T("AB相短路");
	g_sLangID_Native_BnCShortCir = _T("Native_BncShortCir");
	g_sLangTxt_Native_BnCShortCir = _T("BC相短路");
	g_sLangID_Native_CnAShortCir = _T("Native_CnAShortCir");
	g_sLangTxt_Native_CnAShortCir = _T("CA相短路");
	g_sLangID_Native_ShortBCVolAndACur = _T("Native_BCSCVolAndACur");
	g_sLangTxt_Native_ShortBCVolAndACur = _T("BC相短路电压 A相电流");
	g_sLangID_Native_ShortCAVolAndBCur = _T("Native_CASCVolAndBCur");
	g_sLangTxt_Native_ShortCAVolAndBCur = _T("CA相短路电压 B相电流");
	g_sLangID_Native_ShortABVolAndCCur = _T("Native_ABSCVolAndCCur");
	g_sLangTxt_Native_ShortABVolAndCCur = _T("AB相短路电压 C相电流");
	g_sLangID_Native_ABCSC = _T("Native_ABCSC");
	g_sLangTxt_Native_ABCSC = _T("ABC短路");
	g_sLangID_Native_RLOTestAno = _T("Native_RLOTestAno");
	g_sLangTxt_Native_RLOTestAno = _T("复压闭锁测试");
	g_sLangID_Native_BoundaryAngle = _T("Native_BoundaryAngle");
	g_sLangTxt_Native_BoundaryAngle = _T("边界角");

	g_sLangID_Native_ImpedanceAngle = _T("Native_ImpedanceAngle");
	g_sLangTxt_Native_ImpedanceAngle = _T("阻抗角(°)：");
	g_sLangID_Native_InitofVarV = _T("Native_InitofVarV");
	g_sLangTxt_Native_InitofVarV = _T("变化始值(V)：");
	g_sLangID_Native_FinalofVarV = _T("Native_FinalofVarV");
	g_sLangTxt_Native_FinalofVarV = _T("变化终值(V)：");
	g_sLangID_Native_StepofVarV = _T("Native_StepofVarV");
	g_sLangTxt_Native_StepofVarV = _T("变化步长(V)：");
	g_sLangID_Native_InitofVarA = _T("Native_InitofVarA");
	g_sLangTxt_Native_InitofVarA = _T("变化始值(A)：");
	g_sLangID_Native_FinalofVarA = _T("Native_FinalofVarA");
	g_sLangTxt_Native_FinalofVarA = _T("变化终值(A)：");
	g_sLangID_Native_StepofVarA = _T("Native_StepofVarA");
	g_sLangTxt_Native_StepofVarA = _T("变化步长(A)：");

	g_sLangID_Native_ZeroSeqTF = _T("Native_ZeroSeqTF");
	g_sLangTxt_Native_ZeroSeqTF = _T("零序保护试验模板文件");
	g_sLangID_Native_WelUseZeroSeq = _T("Native_WelUseZeroSeq");
	g_sLangTxt_Native_WelUseZeroSeq = _T("欢迎使用零序保护试验");
	g_sLangID_Native_PonovoZS = _T("Native_PonovoZS");
	g_sLangTxt_Native_PonovoZS = _T("Ponovo 零序保护试验");
	g_sLangID_Native_ZeroSeqTest = _T("Native_ZeroSeqTest");
	g_sLangTxt_Native_ZeroSeqTest = _T("零序试验");
	g_sLangID_Native_ZeroSeqStageI = _T("Native_ZeroSeqStageI");
	g_sLangTxt_Native_ZeroSeqStageI = _T("零序I段");
	g_sLangID_Native_ZeroSeqStageII = _T("Native_ZeroSeqStageII");
	g_sLangTxt_Native_ZeroSeqStageII = _T("零序II段");
	g_sLangID_Native_ZeroSeqStageIII = _T("Native_ZeroSeqStageIII");
	g_sLangTxt_Native_ZeroSeqStageIII = _T("零序III段");
	g_sLangID_Native_ZeroSeqStageIV = _T("Native_ZeroSeqStageIV");
	g_sLangTxt_Native_ZeroSeqStageIV = _T("零序IV段");
	g_sLangID_Native_ZeroSeqStageV = _T("Native_ZeroSeqStageV");
	g_sLangTxt_Native_ZeroSeqStageV = _T("零序V段");
	g_sLangID_Native_ZeroSeqWrH = _T("Native_ZeroSeqWrH");
	g_sLangTxt_Native_ZeroSeqWrH = _T("开关量设置中，开入H没有设置成重合闸，软件已经自动把该项设置成重合闸");
	g_sLangID_Native_ZeroSeqWrD = _T("Native_ZeroSeqWrD");
	g_sLangTxt_Native_ZeroSeqWrD = _T("开关量设置中，开入D没有设置成重合闸，软件已经自动把该项设置成重合闸");
	g_sLangID_Native_ZeroSeqWrDH = _T("Native_ZeroSeqWrDH");
	g_sLangTxt_Native_ZeroSeqWrDH = _T("开关量设置中，开入D、开入H没有设置成重合闸，软件已经自动把该项设置成重合闸");
	g_sLangID_Native_TestOFZeroSeq = _T("Native_TestOFZeroSeq");
	g_sLangTxt_Native_TestOFZeroSeq = _T("实验名称：零序保护定值测试");
	g_sLangID_Native_TestofProSet = _T("Native_TestofProSet");
	g_sLangTxt_Native_TestofProSet = _T("保护定值测试");
	g_sLangID_Native_ThrPhaseJump = _T("Native_ThrPhaseJump");
	g_sLangTxt_Native_ThrPhaseJump = _T("跳三相=%1s");
	g_sLangID_Native_Reclosing = _T("Native_Reclosing");
	g_sLangTxt_Native_Reclosing = _T("重合闸");
	g_sLangID_Native_PostAcceleration = _T("Native_PostAcceleration");
	g_sLangTxt_Native_PostAcceleration = _T("后加速");

	g_sLangID_Native_UnitProTF = _T("Native_UnitProTF");
	g_sLangTxt_Native_UnitProTF = _T("整组保护试验模板文件");
	g_sLangID_Native_PonovoGroupTra = _T("Native_PonovoGroupTra");
	g_sLangTxt_Native_PonovoGroupTra = _T("Ponovo整组传动");
	g_sLangID_Native_WelUseGroTra = _T("Native_WelUseGroTra");
	g_sLangTxt_Native_WelUseGroTra = _T("欢迎使用整组传动");
	g_sLangID_Native_GroupTra = _T("Native_GroupTra");
	g_sLangTxt_Native_GroupTra = _T("整组传动");
	g_sLangID_Native_ImpAng = _T("Native_ImpAng");
	g_sLangTxt_Native_ImpAng = _T("阻抗角(°)");
	g_sLangID_Native_NameGroTest = _T("Native_NameGroTest");
	g_sLangTxt_Native_NameGroTest = _T("试验名称：整组试验");
	g_sLangID_Native_TestPara = _T("Native_TestPara");
	g_sLangTxt_Native_TestPara = _T("试验参数");
	g_sLangID_Native_Initial = _T("Native_Initial");
	g_sLangTxt_Native_Initial = _T("初始");
	g_sLangID_Native_Selected = _T("Native_Selected");
	g_sLangTxt_Native_Selected = _T("选中");
	g_sLangID_Native_EndTest = _T("Native_EndTest");
	g_sLangTxt_Native_EndTest = _T("试验结束");

	g_sLangID_Native_TransientTime = _T("Native_TransientTime");
	g_sLangTxt_Native_TransientTime = _T("转换时间");
	g_sLangID_Native_TransientMalfDir = _T("Native_TransientMalfDir");
	g_sLangTxt_Native_TransientMalfDir = _T("转换故障方向");

	g_sLangID_Native_RPAProTestTF = _T("Native_RPAProTestTF");
	g_sLangTxt_Native_RPAProTestTF = _T("重合闸及后加速保护试验模板文件");
	g_sLangID_Native_RPAWro1 = _T("Native_RPAWro1");
	g_sLangTxt_Native_RPAWro1 = _T("故障-|Z|(Ω)表达式异常！");
	g_sLangID_Native_RPAWro2 = _T("Native_RPAWro2");
	g_sLangTxt_Native_RPAWro2 = _T("故障-阻抗角表达式异常！");
	g_sLangID_Native_RPAWro3 = _T("Native_RPAWro3");
	g_sLangTxt_Native_RPAWro3 = _T("重合后-|Z|(Ω)表达式异常！");
	g_sLangID_Native_RPAWro4 = _T("Native_RPAWro4");
	g_sLangTxt_Native_RPAWro4 = _T("跳闸后抽取电压相位表达式异常！");
	g_sLangID_Native_RPAWro5 = _T("Native_RPAWro5");
	g_sLangTxt_Native_RPAWro5 = _T("跳闸后抽取电压表达式异常！");
	g_sLangID_Native_RPATest = _T("Native_RPATest");
	g_sLangTxt_Native_RPATest = _T("重合闸及后加速试验");
	g_sLangID_Native_WelUseRPATest = _T("Native_WelUseRPATest");
	g_sLangTxt_Native_WelUseRPATest = _T("欢迎使用重合闸及后加速试验.");

	g_sLangID_Native_RCTimeLim = _T("Native_RCTimeLim");
	g_sLangTxt_Native_RCTimeLim = _T("重合闸时限");
	g_sLangID_Native_ZeroVolThr = _T("Native_ZeroVolThr");
	g_sLangTxt_Native_ZeroVolThr = _T("检无压定值");
	g_sLangID_Native_VolDetThr = _T("Native_VolDetThr");
	g_sLangTxt_Native_VolDetThr = _T("检有压定值");
	g_sLangID_Native_SynAngDet = _T("Native_SynAngDet");
	g_sLangTxt_Native_SynAngDet = _T("检同期角度");
	g_sLangID_Native_CalZeroSeq = _T("Native_CalZeroSeq");
	g_sLangTxt_Native_CalZeroSeq = _T("零序补偿计算方式");
	g_sLangID_Native_ChinOr = _T("Native_ChinOr");
	g_sLangTxt_Native_ChinOr = _T("中文或");
	g_sLangID_Native_TestRPA = _T("Native_TestRPA");
	g_sLangTxt_Native_TestRPA = _T("重合闸及后加速测试");
	g_sLangID_Native_PermanentFau = _T("Native_PermanentFau");
	g_sLangTxt_Native_PermanentFau = _T("故障性质-永久性故障");
	g_sLangID_Native_TransientFau = _T("Native_TransientFau");
	g_sLangTxt_Native_TransientFau = _T("故障性质-瞬时性故障");
	g_sLangID_Native_MustCho = _T("Native_MustCho");
	g_sLangTxt_Native_MustCho = _T("请务必选择故障类型！");
	g_sLangID_Native_SyncCheck = _T("Native_SyncCheck");
	g_sLangTxt_Native_SyncCheck = _T("检同期");
	g_sLangID_Native_LineNoVolParD = _T("Native_LineNoVolParD");
	g_sLangTxt_Native_LineNoVolParD = _T("检线无压母有压");
	g_sLangID_Native_LineHasVolParN = _T("Native_LineHasVolParN");
	g_sLangTxt_Native_LineHasVolParN = _T("检线有压母无压");
	g_sLangID_Native_LineNoVolParT = _T("Native_LineNoVolParT");
	g_sLangTxt_Native_LineNoVolParT = _T("检线无压母无压");
	g_sLangID_Native_LineHasVolParT = _T("Native_LineHasVolParT");
	g_sLangTxt_Native_LineHasVolParT = _T("检线有压母有压");
	g_sLangID_Native_NoOutput = _T("Native_NoOutput");
	g_sLangTxt_Native_NoOutput = _T("无输出");
	g_sLangID_Native_KOorReKO = _T("Native_KOorReKO");
	g_sLangTxt_Native_KOorReKO = _T("|K0|或Re(K0)");
	g_sLangID_Native_PhiOrIm = _T("Native_PhiOrIm");
	g_sLangTxt_Native_PhiOrIm = _T("Phi(K0)或Im(K0)");

	g_sLangID_Native_FaultReplayTF = _T("Native_FaultReplayTF");
	g_sLangTxt_Native_FaultReplayTF = _T("故障回放试验模板文件");

	// 许文迪第二周
	g_sLangID_Native_FaultReplayTF = _T("Native_FaultReplayTF");
	g_sLangTxt_Native_FaultReplayTF = _T("故障回放试验模板文件");
	g_sLangID_Native_EnfSetAnalog = _T("Native_EnfSetAnalog");
	g_sLangTxt_Native_EnfSetAnalog = _T("当前模块只支持模拟量故障回放,强制设置为模拟量输出模式.");
	g_sLangID_Native_WelUseFaultRe = _T("Native_WelUseFaultRe");
	g_sLangTxt_Native_WelUseFaultRe = _T("欢迎使用故障回放试验.");
	g_sLangID_Native_WavePlayback = _T("Native_WavePlayback");
	g_sLangTxt_Native_WavePlayback = _T("波形回放");
	g_sLangID_Native_PreWaveData = _T("Native_PreWaveData");
	g_sLangTxt_Native_PreWaveData = _T("切换到上一页波形数据");
	g_sLangID_Native_NextWaveData = _T("Native_NextWaveData");
	g_sLangTxt_Native_NextWaveData = _T("切换到下一页波形数据");
	g_sLangID_Native_MalfunctionRe = _T("Native_MalfunctionRe");
	g_sLangTxt_Native_MalfunctionRe = _T("故障回放");
	g_sLangID_Native_OpenWaveFile = _T("Native_OpenWaveFile");
	g_sLangTxt_Native_OpenWaveFile = _T("请打开录波文件");
	g_sLangID_Native_DownloadWaveData = _T("Native_DownloadWaveData");
	g_sLangTxt_Native_DownloadWaveData = _T("正在下载波形数据...");
	g_sLangID_Native_FaultReplayWr3 = _T("Native_FaultReplayWr3");
	g_sLangTxt_Native_FaultReplayWr3 = _T("当前电压通道回放的最大电压值(%lf),大于测试仪最大输出电压(%f).");
	g_sLangID_Native_FaultReplayWr4 = _T("Native_FaultReplayWr4");
	g_sLangTxt_Native_FaultReplayWr4 = _T("当前电流通道回放的最大电流值(%lf),大于测试仪最大输出电流(%f).");
	g_sLangID_Native_TransfRatio = _T("Native_TransfRatio");
	g_sLangTxt_Native_TransfRatio = _T("变比");
	g_sLangID_Native_AChannelDesError = _T("Native_AChannelDesError");
	g_sLangTxt_Native_AChannelDesError = _T("A通道描述查找出错(%s)(%ld).");
	g_sLangID_Native_BChannelDesError = _T("Native_BChannelDesError");
	g_sLangTxt_Native_BChannelDesError = _T("B通道描述查找出错(%s)(%ld).");

	g_sLangID_Native_SITmpl = _T("Native_SITmpl");
	g_sLangTxt_Native_SITmpl = _T("搜索阻抗边界试验模板文件");
	g_sLangID_Native_SIWelcome = _T("Native_SIWelcome");
	g_sLangTxt_Native_SIWelcome = _T("欢迎使用搜索阻抗边界试验");
	g_sLangID_Native_SIPonovo = _T("Native_SIPonovo");
	g_sLangTxt_Native_SIPonovo = _T("Ponovo 搜索阻抗边界");
	g_sLangID_Native_SITest = _T("Native_SITest");
	g_sLangTxt_Native_SITest = _T("搜索阻抗边界试验");
	g_sLangID_Native_SISearch = _T("Native_SISearch");
	g_sLangTxt_Native_SISearch = _T("搜索阻抗边界");
	g_sLangID_Native_ConfigFileNotExist = _T("Native_ConfigFileNotExist");
	g_sLangTxt_Native_ConfigFileNotExist = _T("配置文件：%s 不存在");
	g_sLangID_Native_SelectFaultType = _T("Native_SelectFaultType");
	g_sLangTxt_Native_SelectFaultType = _T("请选择故障类型");
	g_sLangID_Native_ImpedanceAngleStart = _T("Native_ImpedanceAngleStart");
	g_sLangTxt_Native_ImpedanceAngleStart = _T("阻抗角始值");
	g_sLangID_Native_ImpedanceAngleEnd = _T("Native_ImpedanceAngleEnd");
	g_sLangTxt_Native_ImpedanceAngleEnd = _T("阻抗角终值");
	g_sLangID_Native_AngleChangeStep = _T("Native_AngleChangeStep");
	g_sLangTxt_Native_AngleChangeStep = _T("角度改变步长");
	g_sLangID_Native_WelcomeSeq = _T("Native_WelcomeSeq");
	g_sLangTxt_Native_WelcomeSeq = _T("欢迎使用状态序列");
	g_sLangID_Native_StateSeq = _T("Native_StateSeq");
	g_sLangTxt_Native_StateSeq = _T("状态序列");

	g_sLangID_Native_StateSeqStatus = _T("Native_StateSeqStatus");
	g_sLangTxt_Native_StateSeqStatus = _T("次状态序列状态");
	g_sLangID_Native_SelectedStateNumExceed = _T("Native_SelectedStateNumExceed");
	g_sLangTxt_Native_SelectedStateNumExceed = _T("已选择状态数超过最大值");

	g_sLangID_Native_Exit = _T("Native_Exit");
	g_sLangTxt_Native_Exit = _T("出口");
	g_sLangID_Native_TrigTimeS = _T("Native_TrigTimeS");
	g_sLangTxt_Native_TrigTimeS = _T("触发时间(s)");

	g_sLangID_Native_OutOneState = _T("Native_OutOneState");
	g_sLangTxt_Native_OutOneState = _T("开出一状态");
	g_sLangID_Native_OutTwoState = _T("Native_OutTwoState");
	g_sLangTxt_Native_OutTwoState = _T("开出二状态");
	g_sLangID_Native_OutThreeState = _T("Native_OutThreeState");
	g_sLangTxt_Native_OutThreeState = _T("开出三状态");
	g_sLangID_Native_OutFourState = _T("Native_OutFourState");
	g_sLangTxt_Native_OutFourState = _T("开出四状态");
	g_sLangID_Native_OutFiveState = _T("Native_OutFiveState");
	g_sLangTxt_Native_OutFiveState = _T("开出五状态");
	g_sLangID_Native_OutSixState = _T("Native_OutSixState");
	g_sLangTxt_Native_OutSixState = _T("开出六状态");
	g_sLangID_Native_OutSevenState = _T("Native_OutSevenState");
	g_sLangTxt_Native_OutSevenState = _T("开出七状态");
	g_sLangID_Native_OutEightState = _T("Native_OutEightState");
	g_sLangTxt_Native_OutEightState = _T("开出八状态");
	g_sLangID_Native_InAActTime = _T("Native_InAActTime");
	g_sLangTxt_Native_InAActTime = _T("开入A动作时间(s)");
	g_sLangID_Native_InBActTime = _T("Native_InBActTime");
	g_sLangTxt_Native_InBActTime = _T("开入B动作时间(s)");
	g_sLangID_Native_InCActTime = _T("Native_InCActTime");
	g_sLangTxt_Native_InCActTime = _T("开入C动作时间(s)");
	g_sLangID_Native_InDActTime = _T("Native_InDActTime");
	g_sLangTxt_Native_InDActTime = _T("开入D动作时间(s)");
	g_sLangID_Native_InEActTime = _T("Native_InEActTime");
	g_sLangTxt_Native_InEActTime = _T("开入E动作时间(s)");
	g_sLangID_Native_InFActTime = _T("Native_InFActTime");
	g_sLangTxt_Native_InFActTime = _T("开入F动作时间(s)");
	g_sLangID_Native_InGActTime = _T("Native_InGActTime");
	g_sLangTxt_Native_InGActTime = _T("开入G动作时间(s)");
	g_sLangID_Native_InHActTime = _T("Native_InHActTime");
	g_sLangTxt_Native_InHActTime = _T("开入H动作时间(s)");

	g_sLangID_Native_OutputState = _T("Native_OutputState");
	g_sLangTxt_Native_OutputState = _T("开出%d状态");
	g_sLangID_Native_UnknownTrigger = _T("Native_UnkwnTrig");
	g_sLangTxt_Native_UnknownTrigger = _T("未知触发模式");
	g_sLangID_Native_InputOutOfRange = _T("Native_InputOutOfRange");
	g_sLangTxt_Native_InputOutOfRange = _T("输入值%f超出范围(%f).");
	g_sLangID_Native_TestList = _T("Native_TestList");
	g_sLangTxt_Native_TestList = _T("试验列表");
	g_sLangID_Native_TestResult = _T("Native_TestResult");
	g_sLangTxt_Native_TestResult = _T("试验结果");
	g_sLangID_Native_AddState = _T("Native_AddState");
	g_sLangTxt_Native_AddState = _T("添加状态");
	g_sLangID_Native_DelState = _T("Native_DelState");
	g_sLangTxt_Native_DelState = _T("删除状态");
	g_sLangID_Native_DelN1 = _T("Native_DelN1");
	g_sLangTxt_Native_DelN1 = _T("删除N-1");
	g_sLangID_Native_PhaseAngle = _T("Native_PhaseAngle");
	g_sLangTxt_Native_PhaseAngle = _T("相角(°)");
	g_sLangID_Native_SVAbnSim = _T("Native_SVAbnSim");
	g_sLangTxt_Native_SVAbnSim = _T(" SV异常模拟");

	// ManualTest_Trans 马嘉骅第二周
	g_sLangID_Native_WelcomeGenTest = _T("Native_WelcomeGenTest");
	g_sLangTxt_Native_WelcomeGenTest = _T("欢迎使用通用试验.");
	g_sLangID_Native_blankGenTest = _T("Native_blankGenTest");
	g_sLangTxt_Native_blankGenTest = _T(" 通用试验");
	g_sLangID_Native_InputSetExt = _T("Native_InputSetExt");
	g_sLangTxt_Native_InputSetExt = _T("开入设置(扩展)");
	g_sLangID_Native_OutputSetExt = _T("Native_OutputSetExt");
	g_sLangTxt_Native_OutputSetExt = _T("开出设置(扩展)");
	g_sLangID_Native_ActValuePar = _T("Native_ActValuePar");
	g_sLangTxt_Native_ActValuePar = _T("动作值(");
	g_sLangID_Native_BrackColon = _T("Native_BrackColon");
	g_sLangTxt_Native_BrackColon = _T("):");
	g_sLangID_Native_ReturnValuePar = _T("Native_ReturnValuePar");
	g_sLangTxt_Native_ReturnValuePar = _T("返回值(");
	g_sLangID_Native_InitialValPar = _T("Native_InitialValPar");
	g_sLangTxt_Native_InitialValPar = _T("始值(");
	g_sLangID_Native_EndValPar = _T("Native_EndValPar");
	g_sLangTxt_Native_EndValPar = _T("终值(");
	g_sLangID_Native_StepSizePar = _T("Native_StepSizePar");
	g_sLangTxt_Native_StepSizePar = _T("步长(");
	g_sLangID_Native_OpenSett = _T("Native_OpenSett");
	g_sLangTxt_Native_OpenSett = _T("开出设置及返回结果");
	g_sLangID_Native_DCUAB = _T("Native_DCUAB");
	g_sLangTxt_Native_DCUAB = _T("直流UAB");

	// OscillationTest_Trans 马
	g_sLangID_Native_OscilTestTemp = _T("Native_OscilTestTemp");
	g_sLangTxt_Native_OscilTestTemp = _T("振荡试验模板文件");
	g_sLangID_Native_WelcomeOscTest = _T("Native_WelcomeOscTest");
	g_sLangTxt_Native_WelcomeOscTest = _T("欢迎使用振荡试验.");
	g_sLangID_Native_PonovoOscTest = _T("Native_PonovoOscTest");
	g_sLangTxt_Native_PonovoOscTest = _T("Ponovo 振荡试验");
	g_sLangID_Native_OscilTest = _T("Native_OscilTest");
	g_sLangTxt_Native_OscilTest = _T("振荡试验");

	g_sLangID_Native_AngleOscil = _T("Native_AngleOscil");
	g_sLangTxt_Native_AngleOscil = _T("功角振荡");
	g_sLangID_Native_Oscillation = _T("Native_Oscillation");
	g_sLangTxt_Native_Oscillation = _T("振荡");
	g_sLangID_Native_TestParams = _T("Native_TestParams");
	g_sLangTxt_Native_TestParams = _T("测试参数");
	g_sLangID_Native_AngleStartPar = _T("Native_AngleStartPar");
	g_sLangTxt_Native_AngleStartPar = _T("功角始值(°)");
	g_sLangID_Native_AngleEndPar = _T("Native_AngleEndPar");
	g_sLangTxt_Native_AngleEndPar = _T("功角终值(°)");
	g_sLangID_Native_OscilPeriod = _T("Native_OscilPeriod");
	g_sLangTxt_Native_OscilPeriod = _T("振荡周期(s)");
	g_sLangID_Native_TripContacts = _T("Native_TripContacts");
	g_sLangTxt_Native_TripContacts = _T("跳闸接点");
	g_sLangID_Native_OscilReFault = _T("Native_OscilReFault");
	g_sLangTxt_Native_OscilReFault = _T("振荡中再故障");
	g_sLangID_Native_ImpedSlipRamp = _T("Native_ImpedSlipRamp");
	g_sLangTxt_Native_ImpedSlipRamp = _T("使用阻抗滑差递变方式");
	g_sLangID_Native_RecipOsc = _T("Native_RecipOsc");
	g_sLangTxt_Native_RecipOsc = _T("往复振荡");
	g_sLangID_Native_AccelOsc = _T("Native_AccelOsc");
	g_sLangTxt_Native_AccelOsc = _T("增速振荡");

	g_sLangID_Native_FaultTime = _T("Native_FaultTime");
	g_sLangTxt_Native_FaultTime = _T("故障发生时刻");
	g_sLangID_Native_ResultName = _T("Native_ResultName");
	g_sLangTxt_Native_ResultName = _T("结果名称");
	g_sLangID_Native_ProtRelayTime = _T("Native_ProtRelayTime");
	g_sLangTxt_Native_ProtRelayTime = _T("保护出口时间(s)");
	g_sLangID_Native_AccelSigOutTime = _T("Native_AccelSigOutTime");
	g_sLangTxt_Native_AccelSigOutTime = _T("加速信号出口时间(s)");
	g_sLangID_Native_DecelSigOutTime = _T("Native_DecelSigOutTime");
	g_sLangTxt_Native_DecelSigOutTime = _T("减速信号出口时间(s)");
	g_sLangID_Native_ProtOutTimePar = _T("Native_ProtOutTimePar");
	g_sLangTxt_Native_ProtOutTimePar = _T("保护出口时间=");
	g_sLangID_Native_AccelTimePar = _T("Native_AccelTimePar");
	g_sLangTxt_Native_AccelTimePar = _T("加速信号时间=");
	g_sLangID_Native_DecelTimePar = _T("Native_DecelTimePar");
	g_sLangTxt_Native_DecelTimePar = _T("减速信号时间=");


	g_sLangID_Native_GenTranReact = _T("Native_GenTranReact");
	g_sLangTxt_Native_GenTranReact = _T("发电机暂态电抗");

	g_sLangID_Native_ExprMethod = _T("Native_ExprMethod");
	g_sLangTxt_Native_ExprMethod = _T("表达方式");
	g_sLangID_Native_RateIncr = _T("Native_RateIncr");
	g_sLangTxt_Native_RateIncr = _T("增速");
	g_sLangID_Native_Decel = _T("Native_Decel");
	g_sLangTxt_Native_Decel = _T("减速");

	// OverCurrentTest_Trans 马
	g_sLangID_Native_OvrCurrTestTemp = _T("Native_OvrCurrTestTemp");
	g_sLangTxt_Native_OvrCurrTestTemp = _T("过流试验模板文件");
	g_sLangID_Native_WelcomeOvrCurrTest = _T("Native_WelcomeOvrCurrTest");
	g_sLangTxt_Native_WelcomeOvrCurrTest = _T("欢迎使用过流测试.");
	g_sLangID_Native_OvrCurr = _T("Native_OvrCurr");
	g_sLangTxt_Native_OvrCurr = _T("过流保护");
	g_sLangID_Native_TimeChart = _T("Native_TimeChart");
	g_sLangTxt_Native_TimeChart = _T("时间特性图");
	g_sLangID_Native_OvrCurrIAct = _T("Native_OvrCurrIAct");
	g_sLangTxt_Native_OvrCurrIAct = _T("过流I段动作值");
	g_sLangID_Native_OvrCurrIIAct = _T("Native_OvrCurrIIAct");
	g_sLangTxt_Native_OvrCurrIIAct = _T("过流II段动作值");
	g_sLangID_Native_OvrCurrIIIAct = _T("Native_OvrCurrIIIAct");
	g_sLangTxt_Native_OvrCurrIIIAct = _T("过流III段动作值");
	g_sLangID_Native_OvrCurrIVAct = _T("Native_OvrCurrIVAct");
	g_sLangTxt_Native_OvrCurrIVAct = _T("过流IV段动作值");
	g_sLangID_Native_OvrCurrVAct = _T("Native_OvrCurrVAct");
	g_sLangTxt_Native_OvrCurrVAct = _T("过流V段动作值");
	g_sLangID_Native_OvrCurrITime = _T("Native_OvrCurrITime");
	g_sLangTxt_Native_OvrCurrITime = _T("过流I段动作时间");
	g_sLangID_Native_OvrCurrIITime = _T("Native_OvrCurrIITime");
	g_sLangTxt_Native_OvrCurrIITime = _T("过流II段动作时间");
	g_sLangID_Native_OvrCurrIIITime = _T("Native_OvrCurrIIITime");
	g_sLangTxt_Native_OvrCurrIIITime = _T("过流III段动作时间");
	g_sLangID_Native_OvrCurrIVTime = _T("Native_OvrCurrIVTime");
	g_sLangTxt_Native_OvrCurrIVTime = _T("过流IV段动作时间");
	g_sLangID_Native_OvrCurrVTime = _T("Native_OvrCurrVTime");
	g_sLangTxt_Native_OvrCurrVTime = _T("过流V段动作时间");

	g_sLangID_Native_TestNameOvrCurr = _T("Native_TestNameOvrCurr");
	g_sLangTxt_Native_TestNameOvrCurr = _T("试验名称：过流保护定值测试");
	g_sLangID_Native_OvrCurrIProtTest = _T("Native_OvrCurrIProtTest");
	g_sLangTxt_Native_OvrCurrIProtTest = _T("过流I段保护定值测试");
	g_sLangID_Native_OvrCurrIIProtTest = _T("Native_OvrCurrIIProtTest");
	g_sLangTxt_Native_OvrCurrIIProtTest = _T("过流II段保护定值测试");
	g_sLangID_Native_OvrCurrIIIProtTest = _T("Native_OvrCurrIIIProtTest");
	g_sLangTxt_Native_OvrCurrIIIProtTest = _T("过流III段保护定值测试");
	g_sLangID_Native_OvrCurrIVProtTest = _T("Native_OvrCurrIVProtTest");
	g_sLangTxt_Native_OvrCurrIVProtTest = _T("过流IV段保护定值测试");
	g_sLangID_Native_OvrCurrVProtTest = _T("Native_OvrCurrVProtTest");
	g_sLangTxt_Native_OvrCurrVProtTest = _T("过流V段保护定值测试");
	g_sLangID_Native_DefaultIset1 = _T("Native_DefaultIset1");
	g_sLangTxt_Native_DefaultIset1 = _T("默认值 = Iset1");
	g_sLangID_Native_DefaultIset2 = _T("Native_DefaultIset2");
	g_sLangTxt_Native_DefaultIset2 = _T("默认值 = Iset2");
	g_sLangID_Native_DefaultIset3 = _T("Native_DefaultIset3");
	g_sLangTxt_Native_DefaultIset3 = _T("默认值 = Iset3");
	g_sLangID_Native_DefaultIset4 = _T("Native_DefaultIset4");
	g_sLangTxt_Native_DefaultIset4 = _T("默认值 = Iset4");
	g_sLangID_Native_DefaultIset5 = _T("Native_DefaultIset5");
	g_sLangTxt_Native_DefaultIset5 = _T("默认值 = Iset5");
	g_sLangID_Native_DefaultTset1 = _T("Native_DefaultTset1");
	g_sLangTxt_Native_DefaultTset1 = _T("默认值 = Tset1");
	g_sLangID_Native_DefaultTset2 = _T("Native_DefaultTset2");
	g_sLangTxt_Native_DefaultTset2 = _T("默认值 = Tset2");
	g_sLangID_Native_DefaultTset3 = _T("Native_DefaultTset3");
	g_sLangTxt_Native_DefaultTset3 = _T("默认值 = Tset3");
	g_sLangID_Native_DefaultTset4 = _T("Native_DefaultTset4");
	g_sLangTxt_Native_DefaultTset4 = _T("默认值 = Tset4");
	g_sLangID_Native_DefaultTset5 = _T("Native_DefaultTset5");
	g_sLangTxt_Native_DefaultTset5 = _T("默认值 = Tset5");
	g_sLangID_Native_PhaseABC = _T("Native_PhaseABC");
	g_sLangTxt_Native_PhaseABC = _T("ABC相");
	g_sLangID_Native_Or = _T("Native_Or");
	g_sLangTxt_Native_Or = _T("或");
	g_sLangID_Native_And = _T("Native_And");
	g_sLangTxt_Native_And = _T("与");
	g_sLangID_Native_SimDisconn = _T("Native_SimDisconn");
	g_sLangTxt_Native_SimDisconn = _T("模拟PT断线");

	g_sLangID_Native_OpenPh = _T("Native_OpenPh");
	g_sLangTxt_Native_OpenPh = _T("PT断线相");

	// Gradient吕洋第二周
	//  吕
	g_sLangID_Native_DistProtect_TempFile = _T("Native_DistProtect_TempFile");
	g_sLangTxt_Native_DistProtect_TempFile = _T("距离保护模板文件");
	g_sLangID_Native_Wel_DisProtect = _T("Native_Wel_DisProtect");
	g_sLangTxt_Native_Wel_DisProtect = _T("欢迎使用距离保护");
	g_sLangID_Native_PonovoDisProtect = _T("Native_PonovoDisProtect");
	g_sLangTxt_Native_PonovoDisProtect = _T("Ponovo 距离保护");
	g_sLangID_Native_DisProtect = _T("Native_DisProtect");
	g_sLangTxt_Native_DisProtect = _T("距离保护");
	g_sLangID_Native_multiple = _T("Native_multiple");
	g_sLangTxt_Native_multiple = _T("倍,R=");
	g_sLangID_Native_DisProt_SetTest = _T("Native_DisProt_SetTest");
	g_sLangTxt_Native_DisProt_SetTest = _T("距离保护定值测试"); //
	g_sLangID_Native_GroundFaultI = _T("Native_GroundFaultI");
	g_sLangTxt_Native_GroundFaultI = _T("接地故障I段");
	g_sLangID_Native_GroundFaultII = _T("Native_GroundFaultII");
	g_sLangTxt_Native_GroundFaultII = _T("接地故障II段");
	g_sLangID_Native_GroundFaultIII = _T("Native_GroundFaultIII");
	g_sLangTxt_Native_GroundFaultIII = _T("接地故障III段");
	g_sLangID_Native_GroundFaultIV = _T("Native_GroundFaultIV");
	g_sLangTxt_Native_GroundFaultIV = _T("接地故障IV段");
	g_sLangID_Native_GroundFaultV = _T("Native_GroundFaultV");
	g_sLangTxt_Native_GroundFaultV = _T("接地故障V段"); // 接地故障1-5段
	g_sLangID_Native_PhaseFaultI = _T("Native_PhaseFaultI");
	g_sLangTxt_Native_PhaseFaultI = _T("相间故障I段");
	g_sLangID_Native_PhaseFaultII = _T("Native_PhaseFaultII");
	g_sLangTxt_Native_PhaseFaultII = _T("相间故障II段");
	g_sLangID_Native_PhaseFaultIII = _T("Native_PhaseFaultIII");
	g_sLangTxt_Native_PhaseFaultIII = _T("相间故障III段");
	g_sLangID_Native_PhaseFaultIV = _T("Native_PhaseFaultIV");
	g_sLangTxt_Native_PhaseFaultIV = _T("相间故障IV段");
	g_sLangID_Native_PhaseFaultV = _T("Native_PhaseFaultV");
	g_sLangTxt_Native_PhaseFaultV = _T("相间故障V段"); // 相间故障1-5段
	g_sLangID_Native_Para = _T("Native_Para");
	g_sLangTxt_Native_Para = _T("段"); // 段
	g_sLangID_ITOTest_Tempfile = _T("ITOTest_Tempfile");
	g_sLangTxt_ITOTest_Tempfile = _T("电流反时限试验模板文件");
	g_sLangID_Wel_ITOTest = _T("Wel_ITOTest");
	g_sLangTxt_Wel_ITOTest = _T("欢迎使用电流反时限试验");
	g_sLangID_ITOTest = _T("ITOTest");
	g_sLangTxt_ITOTest = _T("电流反时限试验");
	g_sLangID_Ponovo_ITOTest = _T("Ponovo_ITOTest");
	g_sLangTxt_Ponovo_ITOTest = _T("Ponovo 电流反时限试验");
	g_sLangID_Theoretical_ActionTime = _T("Theoretical_ActionTime");
	g_sLangTxt_Theoretical_ActionTime = _T("理论动作时间");
	g_sLangID_Native_ITO = _T("Native_ITO");
	g_sLangTxt_Native_ITO = _T("电流反时限");
	g_sLangID_Single_PhaseGround_Fault = _T("Single_PhaseGround_Fault");
	g_sLangTxt_Single_PhaseGround_Fault = _T("单项接地故障");
	g_sLangID_Directional_LineSide = _T("Directional_LineSide");
	g_sLangTxt_Directional_LineSide = _T("指向线路侧");
	g_sLangID_Directional_BusSide = _T("Directional_BusSide");
	g_sLangTxt_Directional_BusSide = _T("指向母线侧");
	g_sLangID_Add_Series = _T("Add_Series");
	g_sLangTxt_Add_Series = _T("添加系列");
	g_sLangID_Delet_Test = _T("Delet_Test");
	g_sLangTxt_Delet_Test = _T("删除试验");
	g_sLangID_Clear_Results = _T("Clear_Results");
	g_sLangTxt_Clear_Results = _T("清除结果");
	g_sLangID_Clear_All = _T("Clear_All");
	g_sLangTxt_Clear_All = _T("清除所有");
	g_sLangID_Test_Parameters = _T("Test_Parameters");
	g_sLangTxt_Test_Parameters = _T("试验参数");

	g_sLangID_Native_ImpedanceSet = _T("Native_ImpedanceSet");
	g_sLangTxt_Native_ImpedanceSet = _T("阻抗定值(Ω):");
	g_sLangID_Native_Wel_IncreExper = _T("Native_Wel_IncreExper");
	g_sLangTxt_Native_Wel_IncreExper = _T("欢迎使用递变测试.");
	g_sLangID_Native_PonovoIncre = _T("Native_PonovoIncre");
	g_sLangTxt_Native_PonovoIncre = _T("Ponovo递变");
	g_sLangID_Native_IncreExper = _T("Native_IncreExper");
	g_sLangTxt_Native_IncreExper = _T("递变实验");
	g_sLangID_Native_PrepareTime = _T("Native_PrepareTime");
	g_sLangTxt_Native_PrepareTime = _T("变化前时间(s)");

	g_sLangID_Native_PreCurrent = _T("Native_PreCurrent");
	g_sLangTxt_Native_PreCurrent = _T("变化前电流幅值(A)");
	g_sLangID_Native_PreAngle = _T("Native_PreAngle");
	g_sLangTxt_Native_PreAngle = _T("故障前电压电流相角(°)");
	g_sLangID_TestItem1 = _T("TestItem1");
	g_sLangTxt_TestItem1 = _T("测试项一");
	g_sLangID_Native_InputAction = _T("Native_InputAction");
	g_sLangTxt_Native_InputAction = _T("开入%1，动作值：%2");
	g_sLangID_Native_ExInputAction = _T("Native_ExInputAction");
	g_sLangTxt_Native_ExInputAction = _T("扩展开入%1，动作值：%2");

	g_sLangID_Native_NormalOutpExSet = _T("Native_NormalOutpExSet");
	g_sLangTxt_Native_NormalOutpExSet = _T("常态开出设置（扩展）");
	g_sLangID_Native_FaultOutpExSet = _T("Native_FaultOutpExSet");
	g_sLangTxt_Native_FaultOutpExSet = _T("故障态开出设置（扩展）");
	g_sLangID_Native_All = _T("Native_All");
	g_sLangTxt_Native_All = _T("全部");
	g_sLangID_Experiment = _T("Experiment");
	g_sLangTxt_Experiment = _T("试验");

	g_sLangID_Native_InitofVarP = _T("Native_InitofVarP");
	g_sLangTxt_Native_InitofVarP = _T("变化始值(°)：");
	g_sLangID_Native_FinalofVarP = _T("Native_FinalofVarP");
	g_sLangTxt_Native_FinalofVarP = _T("变化终值(°)：");
	g_sLangID_Native_StepofVarP = _T("Native_StepofVarP");
	g_sLangTxt_Native_StepofVarP = _T("变化步长(°)：");
	g_sLangID_Native_InitofVarF = _T("Native_InitofVarF");
	g_sLangTxt_Native_InitofVarF = _T("变化始值(Hz)：");
	g_sLangID_Native_FinalofVarF = _T("Native_FinalofVarF");
	g_sLangTxt_Native_FinalofVarF = _T("变化终值(Hz)：");
	g_sLangID_Native_StepofVarF = _T("Native_StepofVarF");
	g_sLangTxt_Native_StepofVarF = _T("变化步长(Hz)：");

	// xwd 第三周
	g_sLangID_Native_TracVarTestTpl = _T("Native_TracVarTestTpl");
	g_sLangTxt_Native_TracVarTestTpl = _T("牵引变差动试验模板文件");
	g_sLangID_Native_WelcTracVarTest = _T("Native_WelcTracVarTest");
	g_sLangTxt_Native_WelcTracVarTest = _T("欢迎使用牵引变差动测试");
	g_sLangID_Native_PonTracVar = _T("Native_PonTracVar");
	g_sLangTxt_Native_PonTracVar = _T("Ponovo 牵引变差动");

	g_sLangID_Native_TracVar = _T("Native_TracVar");
	g_sLangTxt_Native_TracVar = _T("牵引变差动");

	g_sLangID_Native_FaultTimes = _T("Native_FaultTime");
	g_sLangTxt_Native_FaultTimes = _T("故障时间(s)");
	g_sLangID_Native_HLCTPolarDef = _T("Native_HLCTPolarDef");
	g_sLangTxt_Native_HLCTPolarDef = _T("高低压测CT极性定义");

	g_sLangID_Native_SetValueName = _T("Native_SetValueName");
	g_sLangTxt_Native_SetValueName = _T("定值名称");
	g_sLangID_Native_DiffQBrkCurrSetValue = _T("Native_DiffQBrkCurrSetValue");
	g_sLangTxt_Native_DiffQBrkCurrSetValue = _T("差动速断电流定值(ln)");
	g_sLangID_Native_DiffActCurrThresh = _T("Native_DiffActCurrThresh");
	g_sLangTxt_Native_DiffActCurrThresh = _T("差动动作电流门槛值(ln)");
	g_sLangID_Native_RatioBrkInflect1Curr = _T("Native_RatioBrkInflect1Curr");
	g_sLangTxt_Native_RatioBrkInflect1Curr = _T("比率制动特性拐点数1电流(ln)");
	g_sLangID_Native_RatioBrkInflect2Curr = _T("Native_RatioBrkInflect2Curr");
	g_sLangTxt_Native_RatioBrkInflect2Curr = _T("比率制动特性拐点数2电流(ln)");
	g_sLangID_Native_SettingMode = _T("Native_SettingMode");
	g_sLangTxt_Native_SettingMode = _T("整定方式");
	g_sLangID_Native_HvCTPolarity = _T("Native_HvCTPolarity");
	g_sLangTxt_Native_HvCTPolarity = _T("高压侧CT极性定义");

	g_sLangID_Native_PreChangeTime = _T("Native_PreChangeTime");
	g_sLangTxt_Native_PreChangeTime = _T("变化前时间(s):");
	g_sLangID_Native_PreFaultTimes = _T("Native_PreFaultTimes");
	g_sLangTxt_Native_PreFaultTimes = _T("故障前时间(s):");
	g_sLangID_Native_NormalVoltAmp = _T("Native_NormalVoltAmp");
	g_sLangTxt_Native_NormalVoltAmp = _T("常态电压幅值(V):");
	g_sLangID_Native_NormalVoltPhase = _T("Native_NormalVoltPhase");
	g_sLangTxt_Native_NormalVoltPhase = _T("常态电压相序:");
	g_sLangID_Native_NormalCurrAmp = _T("Native_NormalCurrAmp");
	g_sLangTxt_Native_NormalCurrAmp = _T("常态电流幅值(A):");
	g_sLangID_Native_NormalCurrPhase = _T("Native_NormalCurrPhase");
	g_sLangTxt_Native_NormalCurrPhase = _T("常态电流相序:");
	g_sLangID_Native_NormalPhaseAngle = _T("Native_NormalPhaseAngle");
	g_sLangTxt_Native_NormalPhaseAngle = _T("常态相角(U-I)");
	g_sLangID_Native_FaultMode = _T("Native_FaultMode");
	g_sLangTxt_Native_FaultMode = _T("故障模式:");
	g_sLangID_Native_ChangeAmount = _T("Native_ChangeAmount");
	g_sLangTxt_Native_ChangeAmount = _T("变化量:");
// 	g_sLangID_Native_ShortCircuitVs = _T("Native_ShortCircuitVs");
// 	g_sLangTxt_Native_ShortCircuitVs = _T("短路电压(V):");
	g_sLangID_Native_ShortCircuitAs = _T("Native_ShortCircuitAs");
	g_sLangTxt_Native_ShortCircuitAs = _T("短路电流(A):");
	g_sLangID_Native_FrequencyHz = _T("Native_FrequencyHz");
	g_sLangTxt_Native_FrequencyHz = _T("频率(Hz):");
	g_sLangID_Native_RecordQty = _T("Native_RecordQty");
	g_sLangTxt_Native_RecordQty = _T("记录量:");
	g_sLangID_Native_StepTimeS = _T("Native_StepTimeS");
	g_sLangTxt_Native_StepTimeS = _T("步长时间(s):");
	g_sLangID_Native_SetValueA = _T("Native_SetValueA");
	g_sLangTxt_Native_SetValueA = _T("整定值(A)");
	g_sLangID_Native_SetActTimeS = _T("Native_SetActTimeS");
	g_sLangTxt_Native_SetActTimeS = _T("整定动作时间(s)");

	g_sLangID_Native_SectionI = _T("Native_SectionI");
	g_sLangTxt_Native_SectionI = _T("Ⅰ段");
	g_sLangID_Native_SectionII = _T("Native_SectionII");
	g_sLangTxt_Native_SectionII = _T("Ⅱ段");
	g_sLangID_Native_SectionIII = _T("Native_SectionIII");
	g_sLangTxt_Native_SectionIII = _T("Ⅲ段");
	g_sLangID_Native_SectionIV = _T("Native_SectionIV");
	g_sLangTxt_Native_SectionIV = _T("Ⅳ段");
	g_sLangID_Native_SectionV = _T("Native_SectionV");
	g_sLangTxt_Native_SectionV = _T("Ⅴ段");
	g_sLangID_Native_FaultDir = _T("Native_FaultDir");
	g_sLangTxt_Native_FaultDir = _T("故障方向:");

	g_sLangID_Native_Confirm = _T("Native_Confirm");
	g_sLangTxt_Native_Confirm = _T("确  认");
	g_sLangID_Native_Name = _T("Native_Name");
	g_sLangTxt_Native_Name = _T("名称：");
	g_sLangID_Native_ZeroSeqCurr = _T("Native_ZeroSeqCurr");
	g_sLangTxt_Native_ZeroSeqCurr = _T("零序电流定值(A):");
	g_sLangID_Native_FaultTriggerTime = _T("Native_FaultTriggerTime");
	g_sLangTxt_Native_FaultTriggerTime = _T("故障触发时刻:");
	g_sLangID_Native_Multiples = _T("Native_Multiples");
	g_sLangTxt_Native_Multiples = _T("倍数:");
	g_sLangID_Native_SetActTime = _T("Native_SetActTime");
	g_sLangTxt_Native_SetActTime = _T("整定动作时间(s):");
	g_sLangID_Native_LoadCurrent = _T("Native_LoadCurrent");
	g_sLangTxt_Native_LoadCurrent = _T("负荷电流(A)");
	g_sLangID_Native_LoadPowerAngle = _T("Native_LoadPowerAngle");
	g_sLangTxt_Native_LoadPowerAngle = _T("负荷功角(°)");
	g_sLangID_Native_MaxFaultTime = _T("Native_MaxFaultTime");
	g_sLangTxt_Native_MaxFaultTime = _T("最大故障时间(s)");
	g_sLangID_Native_TransFault = _T("Native_TransFault");
	g_sLangTxt_Native_TransFault = _T("转换性故障");
	g_sLangID_Native_TransTime = _T("Native_TransTime");
	g_sLangTxt_Native_TransTime = _T("转换时间(s)");
	g_sLangID_Native_FaultTriggerTimes = _T("Native_FaultTrigTimes");
	g_sLangTxt_Native_FaultTriggerTimes = _T("故障触发时刻");
	g_sLangID_Native_ImpChar = _T("Native_ImpChar");
	g_sLangTxt_Native_ImpChar = _T("阻抗特性");
	g_sLangID_Native_GrdDistFixed = _T("Native_GrdDistFixed");
	g_sLangTxt_Native_GrdDistFixed = _T("接地距离定值");
	g_sLangID_Native_DistValue = _T("Native_DistValue");
	g_sLangTxt_Native_DistValue = _T("相间距离定值");
	g_sLangID_Native_Impedance = _T("Native_Impedance");
	g_sLangTxt_Native_Impedance = _T("短路阻抗/整定阻抗");
	g_sLangID_Native_GrdSetTime = _T("Native_GrdSetTime");
	g_sLangTxt_Native_GrdSetTime = _T("接地整定时间(s)");
	g_sLangID_Native_PhaseSetTime = _T("Native_PhaseSetTime");
	g_sLangTxt_Native_PhaseSetTime = _T("相间整定时间(s)");
	g_sLangID_Native_Impedance1 = _T("Native_Impedance1");
	g_sLangTxt_Native_Impedance1 = _T("I段阻抗(Ω):");
	g_sLangID_Native_Impedance2 = _T("Native_Impedance2");
	g_sLangTxt_Native_Impedance2 = _T("II段阻抗(Ω):");
	g_sLangID_Native_Impedance3 = _T("Native_Impedance3");
	g_sLangTxt_Native_Impedance3 = _T("III段阻抗(Ω):");
	g_sLangID_Native_Impedance4 = _T("Native_Impedance4");
	g_sLangTxt_Native_Impedance4 = _T("IV段阻抗(Ω):");
	g_sLangID_Native_Impedance5 = _T("Native_Impedance5");
	g_sLangTxt_Native_Impedance5 = _T("V段阻抗(Ω):");
	g_sLangID_Native_ReverseDir = _T("Native_ReverseDir");
	g_sLangTxt_Native_ReverseDir = _T("反方向");
	g_sLangID_Native_ErrorRange = _T("Native_ErrorRange");
	g_sLangTxt_Native_ErrorRange = _T("误差范围(%):");
	g_sLangID_Native_Cancel = _T("Native_Cancel");
	g_sLangTxt_Native_Cancel = _T("取  消");
	g_sLangID_Native_AfterOverlap = _T("Native_AfterOverlap");
	g_sLangTxt_Native_AfterOverlap = _T("重合后");
	g_sLangID_Native_FreqHz = _T("Native_FreqHz");
	g_sLangTxt_Native_FreqHz = _T("频率(Hz)");
	g_sLangID_Native_VoltSelect = _T("Native_VoltSelect");
	g_sLangTxt_Native_VoltSelect = _T("抽取电压选择");
	g_sLangID_Native_VoltAfterTrip = _T("Native_VoltAfterTrip");
	g_sLangTxt_Native_VoltAfterTrip = _T("跳闸后抽取电压（V）");
	g_sLangID_Native_VoltPhaseAfterTrip = _T("Native_VoltPhaseAfterTrip");
	g_sLangTxt_Native_VoltPhaseAfterTrip = _T("跳闸后抽取电压相位°");
	g_sLangID_Native_ChangeStartVal = _T("Native_ChangeStartVal");
	g_sLangTxt_Native_ChangeStartVal = _T("变化始值：");
	g_sLangID_Native_ChangeEndVal = _T("Native_ChangeEndVal");
	g_sLangTxt_Native_ChangeEndVal = _T("变化终值：");
	g_sLangID_Native_ChangeStep = _T("Native_ChangeStep");
	g_sLangTxt_Native_ChangeStep = _T("变化步长：");
	g_sLangID_Native_TestPoint = _T("Native_TestPoint");
	g_sLangTxt_Native_TestPoint = _T("测试点：");
	g_sLangID_Native_FaultTimeS = _T("Native_FaultTimeS");
	g_sLangTxt_Native_FaultTimeS = _T("故障时间(s)：");
	g_sLangID_Native_SettingModes = _T("Native_SettingModes");
	g_sLangTxt_Native_SettingModes = _T("整定方式：");
	g_sLangID_Native_BaseCurrent = _T("Native_BaseCurrent");
	g_sLangTxt_Native_BaseCurrent = _T("基准电流(A)：");
	g_sLangID_Native_SearchMethod = _T("Native_SearchMethod");
	g_sLangTxt_Native_SearchMethod = _T("搜索方法：");
	g_sLangID_Native_CTPolarityDef = _T("Native_CTPolarityDef");
	g_sLangTxt_Native_CTPolarityDef = _T("高低压测CT极性定义：");
	g_sLangID_Native_BrakeEquation = _T("Native_BrakeEquation");
	g_sLangTxt_Native_BrakeEquation = _T("制动方程：");
	g_sLangID_Native_TestPhase = _T("Native_TestPhase");
	g_sLangTxt_Native_TestPhase = _T("测试相：");
	g_sLangID_Native_TestAccuracy = _T("Native_TestAccuracy");
	g_sLangTxt_Native_TestAccuracy = _T("测试精度：");
	g_sLangID_Native_TransConnType = _T("Native_TransConnType");
	g_sLangTxt_Native_TransConnType = _T("变压器接线形式：");
	g_sLangID_Native_DiffCurrent = _T("Native_DiffCurrent");
	g_sLangTxt_Native_DiffCurrent = _T("差动电流(A):");
	g_sLangID_Native_BrakeCurrent = _T("Native_BrakeCurrent");
	g_sLangTxt_Native_BrakeCurrent = _T("制动电流(A):");
	g_sLangID_Native_ManualDiff = _T("Native_ManualDiff");
	g_sLangTxt_Native_ManualDiff = _T("手动递变差流");
	g_sLangID_Native_ManualAdd = _T("Native_ManualAdd");
	g_sLangTxt_Native_ManualAdd = _T("手动加+");
	g_sLangID_Native_ManualSub = _T("Native_ManualSub");
	g_sLangTxt_Native_ManualSub = _T("手动减-");
	g_sLangID_Native_BrakeCurrIn = _T("Native_BrakeCurrIn");
	g_sLangTxt_Native_BrakeCurrIn = _T("制动电流In:");
	g_sLangID_Native_TestType = _T("Native_TestType");
	g_sLangTxt_Native_TestType = _T("测试类型:");
	g_sLangID_Native_TestAccIn = _T("Native_TestAccIn");
	g_sLangTxt_Native_TestAccIn = _T("测试精度In:");
	g_sLangID_Native_SearchUpperLimits = _T("Native_SearchUpperLimits");
	g_sLangTxt_Native_SearchUpperLimits = _T("搜索上限:");
	g_sLangID_Native_SearchLowerLimits = _T("Native_SearchLowerLimits");
	g_sLangTxt_Native_SearchLowerLimits = _T("搜索下限:");
	g_sLangID_Native_DiffCurrentId = _T("Native_DiffCurrentId");
	g_sLangTxt_Native_DiffCurrentId = _T("差动电流Id:");
	g_sLangID_Native_SearchStartValue = _T("Native_SearchStartValue");
	g_sLangTxt_Native_SearchStartValue = _T("搜索始值(%):");
	g_sLangID_Native_SearchEndValue = _T("Native_SearchEndValue");
	g_sLangTxt_Native_SearchEndValue = _T("搜索终值(%):");
	g_sLangID_Native_Evaluation = _T("Native_Evaluation");
	g_sLangTxt_Native_Evaluation = _T("评估：");
	g_sLangID_Native_Expression = _T("Native_Expression");
	g_sLangTxt_Native_Expression = _T("表达式");
	g_sLangID_Native_Result = _T("Native_Result");
	g_sLangTxt_Native_Result = _T("结果：");
	g_sLangID_Native_DiffCurrents = _T("Native_DiffCurrents");
	g_sLangTxt_Native_DiffCurrents = _T("差动电流");
	g_sLangID_Native_ErrorLessThan = _T("Native_ErrorLessThan");
	g_sLangTxt_Native_ErrorLessThan = _T("误差 (%) <");


	g_sLangID_Native_RelativeErrorLessThan = _T("Native_RelativeErrorLessThan");
	g_sLangTxt_Native_RelativeErrorLessThan = _T("相对误差(%)<");
	g_sLangID_Native_AbsoluteErrorLessThan = _T("Native_AbsoluteErrorLessThan");
	g_sLangTxt_Native_AbsoluteErrorLessThan = _T("绝对误差<");

	// Harmtest 吕 第三周
	g_sLangID_Native_HarmonicTest = _T("Native_HarmonicTest");
	g_sLangTxt_Native_HarmonicTest = _T("谐波试验");
	g_sLangID_Native_Wel_HarmModTest = _T("Wel_HarmModTest");
	g_sLangTxt_Native_Wel_HarmModTest = _T("欢迎使用谐波模块试验");
	g_sLangID_Native_Choose_HtesttempFile = _T("Native_Choose_HtesttempFile");
	g_sLangTxt_Native_Choose_HtesttempFile = _T("选择谐波试验模板文件");
	g_sLangID_Native_saveSuccess = _T("Native_saveSuccess");
	g_sLangTxt_Native_saveSuccess = _T("文件保存成功！");
	g_sLangID_Native_harmTestTempSaveS = _T("Native_harmTestTempSaveS");
	g_sLangTxt_Native_harmTestTempSaveS = _T("谐波试验默认模板[%1]保存成功.");
	g_sLangID_Native_harmTestTempSaveF = _T("Native_harmTestTempSaveF");
	g_sLangTxt_Native_harmTestTempSaveF = _T("谐波试验默认模板[%1]保存失败.");
	g_sLangID_Native_saveFail = _T("Native_saveFail");
	g_sLangTxt_Native_saveFail = _T("文件保存失败！");
	g_sLangID_Native_createMFileFail = _T("Native_createMFileFail");
	g_sLangTxt_Native_createMFileFail = _T("创建测试模板文件路径失败");
	g_sLangID_Native_saveAsSuccess = _T("Native_saveAsSuccess");
	g_sLangTxt_Native_saveAsSuccess = _T("模板另存为[%1]成功.");
	g_sLangID_Native_saveAsFail = _T("Native_saveAsFail");
	g_sLangTxt_Native_saveAsFail = _T("模板另存为[%1]失败.");
	g_sLangID_Native_testName_Harmonic = _T("Native_testName_Harmonic");
	g_sLangTxt_Native_testName_Harmonic = _T("试验名称：谐波");

	g_sLangID_Native_secondHarmonicAmp = _T("Native_secondHarmonicAmp");
	g_sLangTxt_Native_secondHarmonicAmp = _T("二次谐波幅值");

	g_sLangID_Native_contentRatio = _T("Native_contentRatio");
	g_sLangTxt_Native_contentRatio = _T("含有率/%");
	g_sLangID_Native_rmsValueV = _T("Native_rmsValueV");
	g_sLangTxt_Native_rmsValueV = _T("有效值/V");
	g_sLangID_Native_rmsValueA = _T("Native_rmsValueA");
	g_sLangTxt_Native_rmsValueA = _T("有效值/A");
	g_sLangID_Native_phaseAngle = _T("Native_phaseAngle");
	g_sLangTxt_Native_phaseAngle = _T("相 位/°");
	g_sLangID_Native_totalRmsValue = _T("Native_totalRmsValue");
	g_sLangTxt_Native_totalRmsValue = _T("总有效值");
	g_sLangID_Native_actionValueA = _T("Native_actionValueA");
	g_sLangTxt_Native_actionValueA = _T("动作值(A)");
	g_sLangID_Native_InitofVar = _T("Native_InitofVar");
	g_sLangTxt_Native_InitofVar = _T("变化始值(");
	g_sLangID_Native_FinalofVar = _T("Native_FinalofVar");
	g_sLangTxt_Native_FinalofVar = _T("变化终值(");
	g_sLangID_Native_StepofVar = _T("Native_StepofVar");
	g_sLangTxt_Native_StepofVar = _T("变化步长(");
	g_sLangID_Native_channelAmp = _T("Native_channelAmp");
	g_sLangTxt_Native_channelAmp = _T("通道幅值");
	g_sLangID_Native_groupNumber = _T("Native_groupNumber");
	g_sLangTxt_Native_groupNumber = _T("第%1组");
	g_sLangID_Native_harmonicLimitExceeded = _T("Native_harmonicLimitExceeded");
	g_sLangTxt_Native_harmonicLimitExceeded = _T("你总计只能选择31次谐波，假如想选择当前次谐波，需要取消勾选一行！");
	g_sLangID_Native_harmonicExceedsMax = _T("Native_harmonicExceedsMax");
	g_sLangTxt_Native_harmonicExceedsMax = _T("选择的谐波次数大于最大值49次！");
	g_sLangID_Native_variaPointExceedsLimit = _T("Native_variaPointExceedsLimit");
	g_sLangTxt_Native_variaPointExceedsLimit = _T("递变点数超过3000点，请重新输入！");

	// ui1
	g_sLangID_Native_faultTimeMargin = _T("Native_faultTimeMargin");
	g_sLangTxt_Native_faultTimeMargin = _T("故障时间裕度(s)");

	// ui2
	g_sLangID_Native_volDefinition = _T("Native_volDefinition");
	g_sLangTxt_Native_volDefinition = _T("电压定义:");
	g_sLangID_Native_referenceItem = _T("Native_referenceItem");
	g_sLangTxt_Native_referenceItem = _T("参考项:");
	g_sLangID_Native_transConnection = _T("Native_transConnection");
	g_sLangTxt_Native_transConnection = _T("变压器接线方式:");

	// ui3
	g_sLangID_Native_Freq_Deviation = _T("Freq_Deviation");
	g_sLangTxt_Native_Freq_Deviation = _T("频率滑差df/dt(Hz/s):");
	g_sLangID_Native_initialFreq = _T("initialFreq");
	g_sLangTxt_Native_initialFreq = _T("频率起始值(Hz):");
	g_sLangID_Native_FreqChange_step = _T("FreqChange_step");
	g_sLangTxt_Native_FreqChange_step = _T("频率变化步长(Hz):");
	g_sLangID_Native_endFreq = _T("endFreq");
	g_sLangTxt_Native_endFreq = _T("频率结束值(Hz):");
	g_sLangID_Native_finalFreq = _T("finalFreq");
	g_sLangTxt_Native_finalFreq = _T("频率变化终值(Hz):");
	g_sLangID_Native_initialFreq_deviation = _T("initialFreq_deviation");
	g_sLangTxt_Native_initialFreq_deviation = _T("频率滑差变化始值(Hz/s):");
	g_sLangID_Native_Freq_deviationstep = _T("Freq_deviationstep");
	g_sLangTxt_Native_Freq_deviationstep = _T("频率滑差变化步长(Hz/s):");
	g_sLangID_Native_finalFreq_deviation = _T("finalFreq_deviation");
	g_sLangTxt_Native_finalFreq_deviation = _T("频率滑差变化终值(Hz/s):");
	g_sLangID_Native_initialCur = _T("initialCur");
	g_sLangTxt_Native_initialCur = _T("电流变化始值(A):");
	g_sLangID_Native_final_cur = _T("final_cur");
	g_sLangTxt_Native_final_cur = _T("电流变化终值(A):");
	g_sLangID_Native_Curchange_step = _T("Curchange_step");
	g_sLangTxt_Native_Curchange_step = _T("电流变化步长(A):");
	g_sLangID_Native_CurPhase_output = _T("CurPhase_output");
	g_sLangTxt_Native_CurPhase_output = _T("电流输出相：");
	g_sLangID_Native_initial_linevolchange = _T("initial_linevolchange");
	g_sLangTxt_Native_initial_linevolchange = _T("线电压变化始值(V):");
	g_sLangID_Native_final_linevolchange = _T("final_linevolchange");
	g_sLangTxt_Native_final_linevolchange = _T("线电压变化终值(V):");
	g_sLangID_Native_linevol_changestep = _T("linevol_changestep");
	g_sLangTxt_Native_linevol_changestep = _T("线电压变化步长(V):");
	g_sLangID_Native_vol_change = _T("vol_change");
	g_sLangTxt_Native_vol_change = _T("电压变化量：");

	// 马嘉骅第三周、
	// OverVoltInverseTime_Trans 马
	g_sLangID_Native_VoltIDMTTestTemp = _T("Native_VoltIDMTTestTemp");
	g_sLangTxt_Native_VoltIDMTTestTemp = _T("电压反时限试验模板文件");
	g_sLangID_Native_PonVoltIDMT = _T("Native_PonVoltIDMT");
	g_sLangTxt_Native_PonVoltIDMT = _T("Ponovo电压反时限试验");
	g_sLangID_Native_WelVoltIDMT = _T("Native_WelVoltIDMT");
	g_sLangTxt_Native_WelVoltIDMT = _T("欢迎使用电压反时限试验.");
	g_sLangID_Native_PonBlaVoltIDMT = _T("Native_PonBlaVoltIDMT");
	g_sLangTxt_Native_PonBlaVoltIDMT = _T("Ponovo 电压反时限试验");
	g_sLangID_Native_VolReTiLimTe = _T("Native_VolReTiLimTe");
	g_sLangTxt_Native_VolReTiLimTe = _T("电压反时限试验");
	g_sLangID_Native_VoltIDMT = _T("Native_VoltIDMT");
	g_sLangTxt_Native_VoltIDMT = _T("电压反时限");
	g_sLangID_Native_3PhFault = _T("Native_3PhFault");
	g_sLangTxt_Native_3PhFault = _T("三相故障");
	g_sLangID_Native_ZeroSeqVolt = _T("Native_ZeroSeqVolt");
	g_sLangTxt_Native_ZeroSeqVolt = _T("零序电压");
	g_sLangID_Native_Start_End = _T("Native_Start_End");
	g_sLangTxt_Native_Start_End = _T("始值-终值");
	g_sLangID_Native_Start_End_Start = _T("Native_Start_End_Start");
	g_sLangTxt_Native_Start_End_Start = _T("始值-终值-始值");
	g_sLangID_Native_ActTimeSymSy = _T("Native_ActTimeSymSy");
	g_sLangTxt_Native_ActTimeSymSy = _T("动作时间=%1s,");
	g_sLangID_Native_PreFaultSt = _T("Native_PreFaultSt");
	g_sLangTxt_Native_PreFaultSt = _T("故障前状态");
	g_sLangID_Native_FaultSt = _T("Native_FaultSt");
	g_sLangTxt_Native_FaultSt = _T("故障状态");


	g_sLangID_Native_HVSDiffBalCoeff = _T("Native_HVSDiffBalCoeff");
	g_sLangTxt_Native_HVSDiffBalCoeff = _T("高压侧差动平衡系数");
	g_sLangID_Native_MVSDiffBalCoeff = _T("Native_MVSDiffBalCoeff");
	g_sLangTxt_Native_MVSDiffBalCoeff = _T("中压侧差动平衡系数");
	g_sLangID_Native_LVSDiffBalCoeff = _T("Native_LVSDiffBalCoeff");
	g_sLangTxt_Native_LVSDiffBalCoeff = _T("低压侧差动平衡系数");
	g_sLangID_Native_FaultDur = _T("Native_FaultDur");
	g_sLangTxt_Native_FaultDur = _T("故障持续时间");
	g_sLangID_Native_CharCurve = _T("Native_CharCurve");
	g_sLangTxt_Native_CharCurve = _T("特性曲线");
	g_sLangID_Native_PhVolt = _T("Native_PhVolt");
	g_sLangTxt_Native_PhVolt = _T("相电压");

	// 第四周许
	g_sLangID_Native_QuickBreakCurrent = _T("Native_QuickBreakCurrent");
	g_sLangTxt_Native_QuickBreakCurrent = _T("速断电流=%1A");
	g_sLangID_Native_QuickBreakCurrentIn = _T("Native_QuickBreakCurrentIn");
	g_sLangTxt_Native_QuickBreakCurrentIn = _T("速断电流=%1In");
	g_sLangID_Native_CenterPointImpedance = _T("Native_CenterPointImpedance");
	g_sLangTxt_Native_CenterPointImpedance = _T("中心点阻抗(Ω):");
	g_sLangID_Native_CenterPointImpedanceAngle = _T("Native_CenterPointImpedanceAngle");
	g_sLangTxt_Native_CenterPointImpedanceAngle = _T("中心点阻抗角(°):");
	g_sLangID_Native_SearchRadius = _T("Native_SearchRadius");
	g_sLangTxt_Native_SearchRadius = _T("搜索半径(Ω):");
	g_sLangID_Native_ImpedanceAngleStartValue = _T("Native_ImpedanceAngleStartValue");
	g_sLangTxt_Native_ImpedanceAngleStartValue = _T("阻抗角始值(°):");
	g_sLangID_Native_ImpedanceAngleEndValue = _T("Native_ImpedanceAngleEndValue");
	g_sLangTxt_Native_ImpedanceAngleEndValue = _T("阻抗角终值(°):");
	g_sLangID_Native_AngleChangeSteps = _T("Native_AngleChangeSteps");
	g_sLangTxt_Native_AngleChangeSteps = _T("角度改变步长(°):");
	g_sLangID_Native_ImpedanceChangeStep = _T("Native_ImpedanceChangeStep");
	g_sLangTxt_Native_ImpedanceChangeStep = _T("阻抗改变步长(Ω):");
	g_sLangID_Native_MaxFaultTimes = _T("Native_MaxFaultTimes");
	g_sLangTxt_Native_MaxFaultTimes = _T("最大故障时间(s):");
	g_sLangID_Native_EndImpedance = _T("Native_EndImpedance");
	g_sLangTxt_Native_EndImpedance = _T("末端阻抗(Ω):");
	g_sLangID_Native_EndImpAngle = _T("Native_EndImpAngle");
	g_sLangTxt_Native_EndImpAngle = _T("末端阻抗角(°):");
	g_sLangID_Native_StartImpedance = _T("Native_StartImpedance");
	g_sLangTxt_Native_StartImpedance = _T("首端阻抗(Ω):");
	g_sLangID_Native_StartImpAngle = _T("Native_StartImpAngle");
	g_sLangTxt_Native_StartImpAngle = _T("首端阻抗角(°):");
	g_sLangID_Native_ImpStep = _T("Native_ImpStep");
	g_sLangTxt_Native_ImpStep = _T("阻抗步长(Ω):");

	g_sLangID_Native_RefState = _T("Native_RefState");
	g_sLangTxt_Native_RefState = _T("开入翻转参考状态：");
	g_sLangID_Native_DcComp = _T("Native_DcComp");
	g_sLangTxt_Native_DcComp = _T("叠加衰减直流分量：");
	g_sLangID_Native_DecayTime = _T("Native_DecayTime");
	g_sLangTxt_Native_DecayTime = _T("衰减时间常数：");
	g_sLangID_Native_LoopCount = _T("Native_LoopCount");
	g_sLangTxt_Native_LoopCount = _T("循环次数：");
	g_sLangID_Native_AuxDCSet = _T("Native_AuxDCSet");
	g_sLangTxt_Native_AuxDCSet = _T("辅助直流设置(V)");
	g_sLangID_Native_ZeroSeqComp = _T("Native_ZeroSeqComp");
	g_sLangTxt_Native_ZeroSeqComp = _T("零序补偿系数：");

	g_sLangID_Native_OutTotalTime = _T("Native_OutTotalTime");
	g_sLangTxt_Native_OutTotalTime = _T("输出总时");
	g_sLangID_Native_ShiftMoment = _T("Native_ShiftMoment");
	g_sLangTxt_Native_ShiftMoment = _T("变位时刻(ms)");
	g_sLangID_Native_CloseTimes = _T("Native_CloseTimes");
	g_sLangTxt_Native_CloseTimes = _T("闭合时间(ms)");
	g_sLangID_Native_BreakTime = _T("Native_BreakTime");
	g_sLangTxt_Native_BreakTime = _T("断开时间(ms)");

	g_sLangID_Native_SOETest = _T("Native_SOETest");
	g_sLangTxt_Native_SOETest = _T("SOE测试");
	g_sLangID_Native_SaveConfig = _T("Native_SaveConfig");
	g_sLangTxt_Native_SaveConfig = _T("保存配置");
	g_sLangID_Native_SaveCurrConfig = _T("Native_SaveCurrConfig");
	g_sLangTxt_Native_SaveCurrConfig = _T("保存目前配置参数");
	g_sLangID_Native_StartTrigger = _T("Native_StartTrigger");
	g_sLangTxt_Native_StartTrigger = _T("开始时触发");
	g_sLangID_Native_StartExpFail = _T("Native_StartExpFail");
	g_sLangTxt_Native_StartExpFail = _T("开始实验失败");
	g_sLangID_Native_StopExpFail = _T("Native_StopExpFail");
	g_sLangTxt_Native_StopExpFail = _T("实验停止失败");

	g_sLangID_Native_NormOutputSet = _T("Native_NormOutputSet");
	g_sLangTxt_Native_NormOutputSet = _T("常态开出设置");
	g_sLangID_Native_FaultOutputSet = _T("Native_FaultOutputSet");
	g_sLangTxt_Native_FaultOutputSet = _T("故障态开出设置");
	g_sLangID_Native_IOSet = _T("Native_IOSet");
	g_sLangTxt_Native_IOSet = _T("开入、开出量设置");
	g_sLangID_Native_InputSelect = _T("Native_InputSelect");
	g_sLangTxt_Native_InputSelect = _T("开入选择");
	g_sLangID_Native_OutputFlipStart = _T("Native_OutputFlipStart");
	g_sLangTxt_Native_OutputFlipStart = _T("开出翻转启动方式");
	g_sLangID_Native_OutputHoldTime = _T("Native_OutputHoldTime");
	g_sLangTxt_Native_OutputHoldTime = _T("开出保持时间(s)");
	g_sLangID_Native_OutputFlipMoment = _T("Native_OutputFlipMoment");
	g_sLangTxt_Native_OutputFlipMoment = _T("开出翻转时刻(s)");
	g_sLangID_Native_SingleJump = _T("Native_SingleJump");
	g_sLangTxt_Native_SingleJump = _T("单跳");
	g_sLangID_Native_TripleJump = _T("Native_TripleJump");
	g_sLangTxt_Native_TripleJump = _T("三跳");
	g_sLangID_Native_Reincidence = _T("Native_Reincidence");
	g_sLangTxt_Native_Reincidence = _T("重合");
	g_sLangID_Native_TimeStart = _T("Native_TimeStart");
	g_sLangTxt_Native_TimeStart = _T("时间启动");
	g_sLangID_Native_InputStart = _T("Native_InputStart");
	g_sLangTxt_Native_InputStart = _T("开入量启动");
	g_sLangID_Native_InputABCD = _T("Native_InputABCD");
	g_sLangTxt_Native_InputABCD = _T("开入A-B-C-D");
	g_sLangID_Native_InputEFGH = _T("Native_InputEFGH");
	g_sLangTxt_Native_InputEFGH = _T("开入E-F-G-H");
	g_sLangID_Native_OutputABCD = _T("Native_OutputABCD");
	g_sLangTxt_Native_OutputABCD = _T("开出A-B-C-D");
	g_sLangID_Native_OutputEFGH = _T("Native_OutputEFGH");
	g_sLangTxt_Native_OutputEFGH = _T("开出E-F-G-H");
	g_sLangID_Native_InputOper = _T("Native_InputOper");
	g_sLangTxt_Native_InputOper = _T("开入操作");
	g_sLangID_Native_OutputOper = _T("Native_OutputOper");
	g_sLangTxt_Native_OutputOper = _T("开出操作");
	g_sLangID_Native_InSel = _T("Native_InSel");
	g_sLangTxt_Native_InSel = _T("缺少跳闸或重合闸开入选择");
	g_sLangID_Native_InputOpers = _T("Native_InputOpers");
	g_sLangTxt_Native_InputOpers = _T("开入操作:");
	g_sLangID_Native_OutputOpers = _T("Native_OutputOpers");
	g_sLangTxt_Native_OutputOpers = _T("开出操作:");
	g_sLangID_Native_OutputA = _T("Native_OutputA");
	g_sLangTxt_Native_OutputA = _T("开出A");
	g_sLangID_Native_OutputB = _T("Native_OutputB");
	g_sLangTxt_Native_OutputB = _T("开出B");
	g_sLangID_Native_OutputC = _T("Native_OutputC");
	g_sLangTxt_Native_OutputC = _T("开出C");
	g_sLangID_Native_OutputD = _T("Native_OutputD");
	g_sLangTxt_Native_OutputD = _T("开出D");
	g_sLangID_Native_OutputE = _T("Native_OutputE");
	g_sLangTxt_Native_OutputE = _T("开出E");
	g_sLangID_Native_OutputF = _T("Native_OutputF");
	g_sLangTxt_Native_OutputF = _T("开出F");
	g_sLangID_Native_OutputG = _T("Native_OutputG");
	g_sLangTxt_Native_OutputG = _T("开出G");
	g_sLangID_Native_OutputH = _T("Native_OutputH");
	g_sLangTxt_Native_OutputH = _T("开出H");

	g_sLangID_Native_OutputFlipMomentS = _T("Native_OutputFlipMomentS");
	g_sLangTxt_Native_OutputFlipMomentS = _T("开出翻转时刻");
	g_sLangID_Native_SelMapFile = _T("Native_SelMapFile");
	g_sLangTxt_Native_SelMapFile = _T("选择通道映射文件");
	g_sLangID_Native_SaveMapFile = _T("Native_SaveMapFile");
	g_sLangTxt_Native_SaveMapFile = _T("通道映射文件另存为");
	g_sLangID_Native_ExpMapSucc = _T("Native_ExpMapSucc");
	g_sLangTxt_Native_ExpMapSucc = _T("导出通道映射文件[%s]成功.");
	g_sLangID_Native_ExpMapFail = _T("Native_ExpMapFail");
	g_sLangTxt_Native_ExpMapFail = _T("导出通道映射文件[%s]失败.");
	g_sLangID_Native_MapPass = _T("Native_MapPass");
	g_sLangTxt_Native_MapPass = _T("通道映射密码");
	g_sLangID_Native_Pass = _T("Native_Pass");
	g_sLangTxt_Native_Pass = _T("密码:");
	g_sLangID_Native_EmptyPass = _T("Native_EmptyPass");
	g_sLangTxt_Native_EmptyPass = _T("密码为空,请重新输入.");
	g_sLangID_Native_WrongPass = _T("Native_WrongPass");
	g_sLangTxt_Native_WrongPass = _T("密码错误,请重新输入.");
	g_sLangID_Native_RatedVolt = _T("Native_RatedVolt");
	g_sLangTxt_Native_RatedVolt = _T("额定电压(V):");
	g_sLangID_Native_RatedCurr = _T("Native_RatedCurr");
	g_sLangTxt_Native_RatedCurr = _T("额定电流(A):");
	g_sLangID_Native_RatedFreq = _T("Native_RatedFreq");
	g_sLangTxt_Native_RatedFreq = _T("额定频率(Hz):");
	g_sLangID_Native_DebTime = _T("Native_DebTime");
	g_sLangTxt_Native_DebTime = _T("防抖时间(ms):");
	g_sLangID_Native_PortNum = _T("Native_PortNum");
	g_sLangTxt_Native_PortNum = _T("端口号:");
	g_sLangID_Native_NetConfig = _T("Native_NetConfig");
	g_sLangTxt_Native_NetConfig = _T("网络配置");
	g_sLangID_Native_InvalidIPPort = _T("Native_InvalidIPPort");
	g_sLangTxt_Native_InvalidIPPort = _T("IP和端口号输入不合法");
	g_sLangID_Native_TotalGroups = _T("Native_TotalGroups");
	g_sLangTxt_Native_TotalGroups = _T("总组数: 00");
	g_sLangID_Native_TotalGroupsParam = _T("Native_TotalGroupsParam");
	g_sLangTxt_Native_TotalGroupsParam = _T("总组数: %1");
	g_sLangID_Native_CurrentGroupParam = _T("Native_CurrentGroupParam");
	g_sLangTxt_Native_CurrentGroupParam = _T("当前组: %1");
	g_sLangID_Native_PrevGroups = _T("Native_PrevGroups");
	g_sLangTxt_Native_PrevGroups = _T("←:上一组");
	g_sLangID_Native_NextGroups = _T("Native_NextGroups");
	g_sLangTxt_Native_NextGroups = _T("→:下一组");
	g_sLangID_Native_CurrentVersionParam = _T("Native_CurrentVersionParam");
	g_sLangTxt_Native_CurrentVersionParam = _T("当前程序版本(%s).");
	g_sLangID_Native_TestView = _T("Native_TestView");
	g_sLangTxt_Native_TestView = _T("试验视图");
	g_sLangID_Native_ReportView = _T("Native_ReportView");
	g_sLangTxt_Native_ReportView = _T("报告视图");
	g_sLangID_Native_StateHistory = _T("Native_StateHistory");
	g_sLangTxt_Native_StateHistory = _T("状态历史记录");
	g_sLangID_Native_StatusLight = _T("Native_StatusLight");
	g_sLangTxt_Native_StatusLight = _T("状态灯显示");
	g_sLangID_Native_StartTestF2 = _T("Native_StartTestF2");
	g_sLangTxt_Native_StartTestF2 = _T("开始测试(F2)");
	g_sLangID_Native_StopTestEsc = _T("Native_StopTestEsc");
	g_sLangTxt_Native_StopTestEsc = _T("停止测试(Esc)");
	g_sLangID_Native_OpenTempFile = _T("Native_OpenTempFile");
	g_sLangTxt_Native_OpenTempFile = _T("打开模板文件");
	g_sLangID_Native_SaveTempFile = _T("Native_SaveTempFile");
	g_sLangTxt_Native_SaveTempFile = _T("保存模板文件");
	g_sLangID_Native_ModelParamConfig = _T("Native_ModelParamConfig");
	g_sLangTxt_Native_ModelParamConfig = _T("型号参数配置");
	g_sLangID_Native_GenParamSetDlg = _T("Native_GenParamSetDlg");
	g_sLangTxt_Native_GenParamSetDlg = _T("通用参数设置对话框");
	g_sLangID_Native_SetValueParamSetDlg = _T("Native_SetValueParamSetDlg");
	g_sLangTxt_Native_SetValueParamSetDlg = _T("整定值参数设置对话框");

	g_sLangID_Native_SwitchValSetDlg = _T("Native_SwitchValSetDlg");
	g_sLangTxt_Native_SwitchValSetDlg = _T("开关量设置对话框");
	g_sLangID_Native_NetConnect = _T("Native_NetConnect");
	g_sLangTxt_Native_NetConnect = _T("网络连接");
	g_sLangID_Native_NetConnectDlg = _T("Native_NetConnectDlg");
	g_sLangTxt_Native_NetConnectDlg = _T("网络连接对话框");
	g_sLangID_Native_ChResMapDlg = _T("Native_ChResMapDlg");
	g_sLangTxt_Native_ChResMapDlg = _T("通道资源映射对话框");
	g_sLangID_Native_DCSet = _T("Native_DCSet");
	g_sLangTxt_Native_DCSet = _T("直流设置");
	g_sLangID_Native_AuxDCSetDlg = _T("Native_AuxDCSetDlg");
	g_sLangTxt_Native_AuxDCSetDlg = _T("辅助直流设置对话框");
	g_sLangID_Native_OutputPower = _T("Native_OutputPower");
	g_sLangTxt_Native_OutputPower = _T("输出功率");
	g_sLangID_Native_OutputPowerSetDlg = _T("Native_OutputPowerSetDlg");
	g_sLangTxt_Native_OutputPowerSetDlg = _T("输出功率设置对话框");
	g_sLangID_Native_SteadyOutput = _T("Native_SteadyOutput");
	g_sLangTxt_Native_SteadyOutput = _T("稳态输出");
	g_sLangID_Native_ACDCSteadyOutput = _T("Native_ACDCSteadyOutput");
	g_sLangTxt_Native_ACDCSteadyOutput = _T("交直流稳态输出");
	g_sLangID_Native_ReportSet = _T("Native_ReportSet");
	g_sLangTxt_Native_ReportSet = _T("报告设置");
	g_sLangID_Native_ReportParamSet = _T("Native_ReportParamSet");
	g_sLangTxt_Native_ReportParamSet = _T("报告参数设置");
	g_sLangID_Native_ShowTestView = _T("Native_ShowTestView");
	g_sLangTxt_Native_ShowTestView = _T("显示试验视图");
	g_sLangID_Native_ShowReportView = _T("Native_ShowReportView");
	g_sLangTxt_Native_ShowReportView = _T("显示报告视图");
	g_sLangID_Native_StateLightView = _T("Native_StateLightView");
	g_sLangTxt_Native_StateLightView = _T("状态灯视图");
	g_sLangID_Native_ShowStateLightView = _T("Native_ShowStateLightView");
	g_sLangTxt_Native_ShowStateLightView = _T("显示状态灯视图");
	g_sLangID_Native_StateHistoryView = _T("Native_StateHistoryView");
	g_sLangTxt_Native_StateHistoryView = _T("状态历史视图");
	g_sLangID_Native_ShowStateHistoryView = _T("Native_ShowStateHistoryView");
	g_sLangTxt_Native_ShowStateHistoryView = _T("显示状态历史视图");
	g_sLangID_Native_CurrentTesterVersionInfo = _T("Native_CurrentTesterVersionInfo");
	g_sLangTxt_Native_CurrentTesterVersionInfo = _T("当前测试仪版本信息");
	g_sLangID_Native_UpdateSoftwares = _T("Native_UpdateSoftware");
	g_sLangTxt_Native_UpdateSoftwares = _T("更新软件");
	g_sLangID_Native_UpdateHostSoftware = _T("Native_UpdateHostSoftware");
	g_sLangTxt_Native_UpdateHostSoftware = _T("更新上位机软件");
	g_sLangID_Native_UpdateLowerLayer = _T("Native_UpdateLowerLayer");
	g_sLangTxt_Native_UpdateLowerLayer = _T("更新底层");
	g_sLangID_Native_UpdateTesterLowerProgram = _T("Native_UpdateTesterLowerProgram");
	g_sLangTxt_Native_UpdateTesterLowerProgram = _T("更新测试仪底层程序");
	g_sLangID_Native_MessageDetection = _T("Native_MessageDetection");
	g_sLangTxt_Native_MessageDetection = _T("报文探测");
	g_sLangID_Native_Report = _T("Native_Report");
	g_sLangTxt_Native_Report = _T("报告");
	g_sLangID_Native_Start = _T("Native_Start");
	g_sLangTxt_Native_Start = _T("开始");
	g_sLangID_Native_SysParamConfigDialog = _T("Native_SysParamConfigDialog");
	g_sLangTxt_Native_SysParamConfigDialog = _T("系统参数配置对话框");
	g_sLangID_Native_OfflineSelection = _T("Native_OfflineSelection");
	g_sLangTxt_Native_OfflineSelection = _T("脱机选择");
	g_sLangID_Native_OfflineSelectTesterModelSN = _T("Native_OfflineSelectTesterModelSN");
	g_sLangTxt_Native_OfflineSelectTesterModelSN = _T("脱机选择测试仪型号、SN");
	g_sLangID_Native_Date1970 = _T("Native_Date1970");
	g_sLangTxt_Native_Date1970 = _T("1970年1月1日 00:00:00");
	g_sLangID_Native_ConnectionStatus = _T("Native_ConnectionStatus");
	g_sLangTxt_Native_ConnectionStatus = _T("连接状态：");
	g_sLangID_Native_SyncTime = _T("Native_SyncTime");
	g_sLangTxt_Native_SyncTime = _T("对时");
	g_sLangID_Native_FileSaveSuccess = _T("Native_FileSaveSuccess");
	g_sLangTxt_Native_FileSaveSuccess = _T("文件[%1]保存成功.");
	g_sLangID_Native_FileSaveFail = _T("Native_FileSaveFail");
	g_sLangTxt_Native_FileSaveFail = _T("文件[%1]保存失败.");
	g_sLangID_Native_DefParamFileSaveSuccess = _T("Native_DefParamFileSaveSuccess");
	g_sLangTxt_Native_DefParamFileSaveSuccess = _T("默认参数文件[%1]保存成功.");
	g_sLangID_Native_DefParamFileSaveFail = _T("Native_DefParamFileSaveFail");
	g_sLangTxt_Native_DefParamFileSaveFail = _T("默认参数文件[%1]保存失败.");
	g_sLangID_Native_HarmonicExceedValue = _T("Native_HarmonicExceedValue");
	g_sLangTxt_Native_HarmonicExceedValue = _T("谐波含量超约定值");
	g_sLangID_Native_OutputMaxExceedDesign = _T("Native_OutputMaxExceedDesign");
	g_sLangTxt_Native_OutputMaxExceedDesign = _T("输出最大值超设计");
	g_sLangID_Native_ReModifyHarmonicValue = _T("Native_ReModifyHarmonicValue");
	g_sLangTxt_Native_ReModifyHarmonicValue = _T("请重新修改谐波含量的值！");
	g_sLangID_Native_LastTestCannotContinue = _T("Native_LastTestCannotContinue");
	g_sLangTxt_Native_LastTestCannotContinue = _T("当前已经是最后一个测试下,无法继续测试.");
	g_sLangID_Native_SystemParamSetComplete = _T("Native_SystemParamSetComplete");
	g_sLangTxt_Native_SystemParamSetComplete = _T("系统参数设置下发完成");
	g_sLangID_Native_SystemParamSetFailed = _T("Native_SystemParamSetFailed");
	g_sLangTxt_Native_SystemParamSetFailed = _T("系统参数设置下发失败");
	g_sLangID_Native_TestStopped = _T("Native_TestStopped");
	g_sLangTxt_Native_TestStopped = _T("测试停止");
	g_sLangID_Native_StopCommandFailed = _T("Native_StopCommandFailed");
	g_sLangTxt_Native_StopCommandFailed = _T("停止命令下发失败");
	g_sLangID_Native_ConnectionFailed = _T("Native_ConnectionFailed");
	g_sLangTxt_Native_ConnectionFailed = _T("联机失败,无法下发系统参数.");
	g_sLangID_Native_ModuleSwitchDone = _T("Native_ModuleSwitchDone");
	g_sLangTxt_Native_ModuleSwitchDone = _T("模块档位切换命令下发完成");
	g_sLangID_Native_ModuleSwitchFail = _T("Native_ModuleSwitchFail");
	g_sLangTxt_Native_ModuleSwitchFail = _T("模块档位切换命令下发失败");
	g_sLangID_Native_AuxDCOutDone = _T("Native_AuxDCOutDone");
	g_sLangTxt_Native_AuxDCOutDone = _T("辅助直流输出命令下发完成");
	g_sLangID_Native_AuxDCOutFail = _T("Native_AuxDCOutFail");
	g_sLangTxt_Native_AuxDCOutFail = _T("辅助直流输出命令下发失败");
// 	g_sLangID_Native_ConnectFail = _T("Native_ConnectFail");
// 	g_sLangTxt_Native_ConnectFail = _T("与当前测试仪建立连接失败(%s).");
	g_sLangID_Native_StartSteadyOut = _T("Native_StartSteadyOut");
	g_sLangTxt_Native_StartSteadyOut = _T("开始稳态量输出");
	g_sLangID_Native_StopSteadyOut = _T("Native_StopSteadyOut");
	g_sLangTxt_Native_StopSteadyOut = _T("停止稳态量输出");
	
	g_sLangID_Native_StopSOETest = _T("Native_StopSOETest");
	g_sLangTxt_Native_StopSOETest = _T("停止SOE测试输出");
	g_sLangID_Native_ExportWord = _T("Native_ExportWord");
	g_sLangTxt_Native_ExportWord = _T("导出word文件");
	g_sLangID_Native_ReportTypes = _T("Native_ReportTypes");
	g_sLangTxt_Native_ReportTypes = _T("Word97-2003报告(*.doc);;Word报告(*.docx);;HTML报告(*.html);;PDF报告(*.pdf)");
	g_sLangID_Native_SaveReportSuccess = _T("Native_SaveReportSuccess");
	g_sLangTxt_Native_SaveReportSuccess = _T("网页报告(%s)保存成功.");
	g_sLangID_Native_SavePDFSuccess = _T("Native_SavePDFSuccess");
	g_sLangTxt_Native_SavePDFSuccess = _T("PDF报告文件(%s)保存成功.");
	g_sLangID_Native_SavePDFFailure = _T("Native_SavePDFFailure");
	g_sLangTxt_Native_SavePDFFailure = _T("PDF报告文件(%s)保存失败.");
	g_sLangID_Native_SaveWordSuccess = _T("Native_SaveWordSuccess");
	g_sLangTxt_Native_SaveWordSuccess = _T("WORD报告文件(%s)保存成功.");
	g_sLangID_Native_SaveWordFailure = _T("Native_SaveWordFailure");
	g_sLangTxt_Native_SaveWordFailure = _T("WORD报告文件(%s)保存失败.");
	g_sLangID_Native_TestRunning = _T("Native_TestRunning");
	g_sLangTxt_Native_TestRunning = _T("正在运行中,是否停止测试?");
	g_sLangID_Native_UnsavedTemplate = _T("Native_UnsavedTemplate");
	g_sLangTxt_Native_UnsavedTemplate = _T("测试模板未保存,是否保存?");
	g_sLangID_Native_DeleteAll = _T("Native_DeleteAll");
	g_sLangTxt_Native_DeleteAll = _T("删除全部");
	g_sLangID_Native_VarName = _T("Native_VarName");
	g_sLangTxt_Native_VarName = _T("变量名称");

	// 第四周吕
	g_sLangID_Native_voltagev = _T("Native_voltagev");
	g_sLangTxt_Native_voltagev = _T("电压（V）：");
	g_sLangID_Native_currentc = _T("Native_currentc");
	g_sLangTxt_Native_currentc = _T(" 电流(A):");
	g_sLangID_Native_phasep = _T("Native_phasep");
	g_sLangTxt_Native_phasep = _T("相位差(°):");
	g_sLangID_Native_initialCurrent = _T("Native_initialCurrent");
	g_sLangTxt_Native_initialCurrent = _T("电流变化始值(I*):");
	g_sLangID_Native_finalCurrent = _T("Native_finalCurrent");
	g_sLangTxt_Native_finalCurrent = _T("电流变化终值(I*):");
	g_sLangID_Native_CurstepSize = _T("Native_CurstepSize");
	g_sLangTxt_Native_CurstepSize = _T("电流变化步长(I*):");
	g_sLangID_Native_currentcI = _T("Native_currentcI");
	g_sLangTxt_Native_currentcI = _T(" 电流(I*):");
	g_sLangID_Native_referenceValue = _T("Native_referenceValue");
	g_sLangTxt_Native_referenceValue = _T("基准值:");
	g_sLangID_Native_ctPolarityDef = _T("Native_ctPolarityDef");
	g_sLangTxt_Native_ctPolarityDef = _T("CT正极性定义:");
	g_sLangID_Native_charaDef = _T("Native_charaDef");
	g_sLangTxt_Native_charaDef = _T("特性定义");
	g_sLangID_Native_timerLimit1 = _T("Native_timerLimit1");
	g_sLangTxt_Native_timerLimit1 = _T("1段定时限:");
	g_sLangID_Native_timerLimit2 = _T("Native_timerLimit2");
	g_sLangTxt_Native_timerLimit2 = _T("2段定时限:");
	g_sLangID_Native_timerLimit3 = _T("Native_timerLimit3");
	g_sLangTxt_Native_timerLimit3 = _T("3段定时限:");

	// ui5
	g_sLangID_Native_singleP = _T("Native_singleP");
	g_sLangTxt_Native_singleP = _T("单相");
	g_sLangID_Native_impedanceSelection = _T("Native_impedanceSelection");
	g_sLangTxt_Native_impedanceSelection = _T("阻抗选择:");
	g_sLangID_Native_times = _T("Native_times");
	g_sLangTxt_Native_times = _T("倍");
	g_sLangID_Native_impedanceRepresent = _T("Native_impedanceRepresent");
	g_sLangTxt_Native_impedanceRepresent = _T("阻抗表示方式:");
	g_sLangID_Native_timeConstant = _T("Native_timeConstant");
	g_sLangTxt_Native_timeConstant = _T("时间定值(s):");
	g_sLangID_Native_triggerTiming = _T("Native_triggerTiming");
	g_sLangTxt_Native_triggerTiming = _T("触发时刻:");
	g_sLangID_Native_h = _T("Native_h");
	g_sLangTxt_Native_h = _T("时");
	g_sLangID_Native_m = _T("Native_m");
	g_sLangTxt_Native_m = _T("分");
	g_sLangID_Native_s = _T("Native_s");
	g_sLangTxt_Native_s = _T("秒");

	// ui6
	g_sLangID_Native_PreChangeVol = _T("Native_PreChangeVol");
	g_sLangTxt_Native_PreChangeVol = _T("变化前电压(V):");
	g_sLangID_Native_PreChangeCur = _T("Native_PreChangeCur");
	g_sLangTxt_Native_PreChangeCur = _T("变化前电流(A):");
	g_sLangID_Native_PreChangeFreq = _T("Native_PreChangeFreq");
	g_sLangTxt_Native_PreChangeFreq = _T("变化前频率(HZ):");
	g_sLangID_Native_variableType = _T("Native_variableType");
	g_sLangTxt_Native_variableType = _T("变量类型:");
	g_sLangID_Native_variable0 = _T("Native_variable0");
	g_sLangTxt_Native_variable0 = _T("变量类型:");
	g_sLangID_Native_directChange = _T("Native_directChange");
	g_sLangTxt_Native_directChange = _T("递变方向：");

	g_sLangID_Native_currentG1 = _T("Native_currentG1");
	g_sLangTxt_Native_currentG1 = _T("电流(G1)(A)：");
	g_sLangID_Native_currentG2 = _T("Native_currentG2");
	g_sLangTxt_Native_currentG2 = _T("电流(G2)(A)：");
	g_sLangID_Native_voltageG1 = _T("Native_voltagetG1");
	g_sLangTxt_Native_voltageG1 = _T("电压(G1)(V)：");
	g_sLangID_Native_voltageG2 = _T("Native_voltagetG2");
	g_sLangTxt_Native_voltageG2 = _T("电压(G2)(V)：");
	g_sLangID_Native_currentDif = _T("Native_currentDif");
	g_sLangTxt_Native_currentDif = _T("电流相差(G1,G2)(°):");

	g_sLangID_Native_relativeErrorl = _T("Native_relativeErrorl");
	g_sLangTxt_Native_relativeErrorl = _T("相对误差<");
	g_sLangID_Native_returnCoefficientb = _T("Native_returnCoefficientb");
	g_sLangTxt_Native_returnCoefficientb = _T("返回系数>");
	g_sLangID_Native_normalState = _T("Native_normalState");
	g_sLangTxt_Native_normalState = _T("常态:");
	g_sLangID_Native_faultState = _T("Native_faultState");
	g_sLangTxt_Native_faultState = _T("故障态:");

	g_sLangID_Native_judgmentCondition = _T("Native_judgmentCondition");
	g_sLangTxt_Native_judgmentCondition = _T("判定条件");
	g_sLangID_Native_express = _T("Native_express");
	g_sLangTxt_Native_express = _T("表达式");

	// ui7
	g_sLangID_Native_clear0 = _T("Native_clear0");
	g_sLangTxt_Native_clear0 = _T("清零");
	g_sLangID_Native_changeSettings = _T("Native_changeSettings");
	g_sLangTxt_Native_changeSettings = _T("变化设置:");
	g_sLangID_Native_changeTime = _T("Native_changeTime");
	g_sLangTxt_Native_changeTime = _T("变化时间(s):");
	g_sLangID_Native_baseFrequency = _T("Native_baseFrequency");
	g_sLangTxt_Native_baseFrequency = _T("基波频率(Hz):");
	g_sLangID_Native_openSettings = _T("Native_openSettings");
	g_sLangTxt_Native_openSettings = _T("开出设置:");
	g_sLangID_Native_harmDataBatchSet = _T("Native_harmDataBatchSet");
	g_sLangTxt_Native_harmDataBatchSet = _T("谐波数据批量设置");
	g_sLangID_Native_channelContain = _T("Native_channelContain");
	g_sLangTxt_Native_channelContain = _T("通道含有率(%):");
	g_sLangID_Native_channelPhase = _T("Native_channelPhase");
	g_sLangTxt_Native_channelPhase = _T("通道相位(°):");

	// goose

	g_sLangID_Native_forceNumberOutput = _T("Native_forceNumberOutput");
	g_sLangTxt_Native_forceNumberOutput = _T("当前模块需要支持数字量输出功能,强制设置为数字量输出模式.");
	g_sLangID_Native_notSupportNumOutput = _T("Native_notSupportNumOutput");
	g_sLangTxt_Native_notSupportNumOutput = _T("不支持数字量输出功能");
	g_sLangID_Native_PonovogooseSim = _T("Native_PonovogooseSim");
	g_sLangTxt_Native_PonovogooseSim = _T("Ponovo GOOSE异常模拟");
	g_sLangID_Native_welgooseSim = _T("Native_welgooseSim");
	g_sLangTxt_Native_welgooseSim = _T("欢迎使用GOOSE异常模拟试验.");
	g_sLangID_Native_JumpA = _T("Native_JumpA");
	g_sLangTxt_Native_JumpA = _T("跳A");
	g_sLangID_Native_JumpB = _T("Native_JumpB");
	g_sLangTxt_Native_JumpB = _T("跳B");
	g_sLangID_Native_JumpC = _T("Native_JumpC");
	g_sLangTxt_Native_JumpC = _T("跳C");
	g_sLangID_Native_JumpD = _T("Native_JumpD");
	g_sLangTxt_Native_JumpD = _T("跳D");
	g_sLangID_Native_JumpE = _T("Native_JumpE");
	g_sLangTxt_Native_JumpE = _T("跳E");
	g_sLangID_Native_JumpF = _T("Native_JumpF");
	g_sLangTxt_Native_JumpF = _T("跳F");
	g_sLangID_Native_JumpG = _T("Native_JumpG");
	g_sLangTxt_Native_JumpG = _T("跳G");
	g_sLangID_Native_JumpH = _T("Native_JumpH");
	g_sLangTxt_Native_JumpH = _T("跳H");
	g_sLangID_Native_JumpI = _T("Native_JumpI");
	g_sLangTxt_Native_JumpI = _T("跳I");
	g_sLangID_Native_JumpJ = _T("Native_JumpJ");
	g_sLangTxt_Native_JumpJ = _T("跳J");
	g_sLangID_Native_STSS1234 = _T("Native_STSS1234");
	g_sLangTxt_Native_STSS1234 = _T("状态%1,输出时间=%2,StNum=%3,SqNum=%4");

	// channelParaset
	g_sLangID_Native_amplitudeV = _T("Native_amplitudeV");
	g_sLangTxt_Native_amplitudeV = _T("幅值(V)");
	g_sLangID_Native_amplitudeKV = _T("Native_amplitudeKV");
	g_sLangTxt_Native_amplitudeKV = _T("幅值(KV)");
	g_sLangID_Native_amplitudeA = _T("Native_amplitudeA");
	g_sLangTxt_Native_amplitudeA = _T("幅值(A)");
	g_sLangID_Native_overflowV = _T("Native_overflowV");
	g_sLangTxt_Native_overflowV = _T("谐波设置值%f(%d,%d)与基波的叠加超出范围(%fV).");
	g_sLangID_Native_overflowA = _T("Native_overflowA");
	g_sLangTxt_Native_overflowA = _T("谐波设置值%f(%d,%d)与基波的叠加超出范围(%fA).");
	g_sLangID_Native_input_overrange = _T("Native_input_overrange");
	g_sLangTxt_Native_input_overrange = _T("输入值%f(%d,%d)超出范围(%f).");
	g_sLangID_Native_flowoverV = _T("Native_flowoverV");
	g_sLangTxt_Native_flowoverV = _T("基波设置值%f(%d,%d)与谐波的叠加超出范围(%fV).");
	g_sLangID_Native_flowoverA = _T("Native_flowoverA");
	g_sLangTxt_Native_flowoverA = _T("基波设置值%f(%d,%d)与谐波的叠加超出范围(%fA).");
	g_sLangID_Native_all_frequencies = _T("Native_all_frequencies");
	g_sLangTxt_Native_all_frequencies = _T("等全部频率");
	g_sLangID_Native_smallsignal = _T("Native_smallsignal");
	g_sLangTxt_Native_smallsignal = _T("小信号");
	g_sLangID_Native_illchannelname = _T("Native_illchannelname");
	g_sLangTxt_Native_illchannelname = _T("递变通道名【%s】非法");

	// 第四周马
	// DifferTest_Trans 马
	g_sLangID_Native_DifTestTempFile = _T("Native_DifTestTempFile");
	g_sLangTxt_Native_DifTestTempFile = _T("差动试验模板文件");
	g_sLangID_Native_WelToDiffTest = _T("Native_WelToDiffTest");
	g_sLangTxt_Native_WelToDiffTest = _T("欢迎使用差动测试.");
	g_sLangID_Native_PonovoDiff = _T("Native_PonovoDiff");
	g_sLangTxt_Native_PonovoDiff = _T("Ponovo 差动");
	g_sLangID_Native_Differential = _T("Native_Differential");
	g_sLangTxt_Native_Differential = _T("差动");
	g_sLangID_Native_CurveGraph = _T("Native_CurveGraph");
	g_sLangTxt_Native_CurveGraph = _T("特征曲线图");
	g_sLangID_Native_WireDiagram = _T("Native_WireDiagram");
	g_sLangTxt_Native_WireDiagram = _T("接线图");
	g_sLangID_Native_NoTgtDelItem = _T("Native_NoTgtDelItem");
	g_sLangTxt_Native_NoTgtDelItem = _T("没有选择目标删除项!");
	g_sLangID_Native_AtLeast1Test = _T("Native_AtLeast1Test");
	g_sLangTxt_Native_AtLeast1Test = _T("此测试类型至少保留一个测试项！");
	g_sLangID_Native_OnlineFailSy = _T("Native_OnlineFailSy");
	g_sLangTxt_Native_OnlineFailSy = _T("联机失败[%s][%ld].");
	g_sLangID_Native_ChnlMapFileDone = _T("Native_ChnlMapFileDone");
	g_sLangTxt_Native_ChnlMapFileDone = _T("通道映射文件下发完成");
	g_sLangID_Native_ChMapFileErr = _T("Native_ChMapFileErr");
	g_sLangTxt_Native_ChMapFileErr = _T("通道映射文件下发失败");
	g_sLangID_Native_SysParamSetDone = _T("Native_SysParamSetDone");
	g_sLangTxt_Native_SysParamSetDone = _T("系统参数设置下发完成");
	g_sLangID_Native_SysParamErr = _T("Native_SysParamErr");
	g_sLangTxt_Native_SysParamErr = _T("系统参数设置下发失败");
	g_sLangID_Native_IECParamSetDone = _T("Native_IECParamSetDone");
	g_sLangTxt_Native_IECParamSetDone = _T("IEC参数设置下发完成");
	g_sLangID_Native_IECParamTimeout = _T("Native_IECParamTimeout");
	g_sLangTxt_Native_IECParamTimeout = _T("IEC参数设置执行超时");
	g_sLangID_Native_IECParamFail = _T("Native_IECParamFail");
	g_sLangTxt_Native_IECParamFail = _T("IEC参数设置执行失败");
	g_sLangID_Native_StartTestSy = _T("Native_StartTest");
	g_sLangTxt_Native_StartTestSy = _T("开始测试.");
	g_sLangID_Native_StartTestCmdFail = _T("Native_StartTestCmdFail");
	g_sLangTxt_Native_StartTestCmdFail = _T("开始测试命令下发失败.");
	g_sLangID_Native_NoTestItemSy = _T("Native_NoTestItemSy");
	g_sLangTxt_Native_NoTestItemSy = _T("没有选择测试项.");
	g_sLangID_Native_SetTestItemCurrent = _T("Native_SetTestItemCurrent");
	g_sLangTxt_Native_SetTestItemCurrent = _T("在Id-Ir平面上双击鼠标，设置测试项的制动电流值");

	g_sLangID_Native_RefCurrentOther = _T("Native_RefCurrentOther");
	g_sLangTxt_Native_RefCurrentOther = _T("基准电流(其它)");
	g_sLangID_Native_DfRelayCurrSet = _T("Native_DfRelayCurrSet");
	g_sLangTxt_Native_DfRelayCurrSet = _T("差动速断电流定值");
	g_sLangID_Native_DfActThresh = _T("Native_DfActThresh");
	g_sLangTxt_Native_DfActThresh = _T("差动动作电流门槛值");
	g_sLangID_Native_RatioBrkPntCnt = _T("Native_RatioBrkPntCnt");
	g_sLangTxt_Native_RatioBrkPntCnt = _T("比率制动特性拐点数");
	g_sLangID_Native_RatioBrkPt1Curr = _T("Native_RatioBrkPt1Curr");
	g_sLangTxt_Native_RatioBrkPt1Curr = _T("比率制动特性拐点1电流");
	g_sLangID_Native_RatioBrkPt2Curr = _T("Native_RatioBrkPt2Curr");
	g_sLangTxt_Native_RatioBrkPt2Curr = _T("比率制动特性拐点2电流");
	g_sLangID_Native_RatioBrkPt3Curr = _T("Native_RatioBrkPt3Curr");
	g_sLangTxt_Native_RatioBrkPt3Curr = _T("比率制动特性拐点3电流");

	g_sLangID_Native_DiffCurrExceedsLimit = _T("Native_DiffCurrExceedsLimit");
	g_sLangTxt_Native_DiffCurrExceedsLimit = _T("差动电流值(%f),超越上限");
	g_sLangID_Native_ParamsUpdated = _T("Native_ParamsUpdated");
	g_sLangTxt_Native_ParamsUpdated = _T("参数更新成功.");
	g_sLangID_Native_ParamsUpdateFailed = _T("Native_ParamsUpdateFailed");
	g_sLangTxt_Native_ParamsUpdateFailed = _T("参数更新失败.");
	g_sLangID_Native_DiffCurrReducedToZero = _T("Native_DiffCurrReducedToZero");
	g_sLangTxt_Native_DiffCurrReducedToZero = _T("差动电流值已降低为0,无法再减小");
	g_sLangID_Native_RatioBrkCoef1 = _T("Native_RatioBrkCoef1");
	g_sLangTxt_Native_RatioBrkCoef1 = _T("比率制动系数一");
	g_sLangID_Native_RatioBrkCoef2 = _T("Native_RatioBrkCoef2");
	g_sLangTxt_Native_RatioBrkCoef2 = _T("比率制动系数二");
	g_sLangID_Native_RatioBrkCoef3 = _T("Native_RatioBrkCoef3");
	g_sLangTxt_Native_RatioBrkCoef3 = _T("比率制动系数三");

	
	g_sLangID_Native_ManInBalCoeffNoHi = _T("Native_ManInBalCoeffNoHi");
	g_sLangTxt_Native_ManInBalCoeffNoHi = _T("手动计算输入平衡系数方式时如果整定值选择标幺值，则基准电流不可选择高侧二次额定电流.");
	g_sLangID_Native_ManInBalCoeffNoBe = _T("Native_ManInBalCoeffNoBe");
	g_sLangTxt_Native_ManInBalCoeffNoBe = _T("手动计算输入平衡系数方式时如果整定值选择标幺值，则基准电流不可选择各侧二次额定电流.");
	g_sLangID_Native_DiffCurrentTheory = _T("Native_DiffCurrentTheory");
	g_sLangTxt_Native_DiffCurrentTheory = _T("差流理论值");
	g_sLangID_Native_Diff6I = _T("Native_Diff6I");
	g_sLangTxt_Native_Diff6I = _T("<h1>差动6I</h1>");
	g_sLangID_Native_TestResultSy = _T("Native_TestResultSy");
	g_sLangTxt_Native_TestResultSy = _T("<h2>测试结果</h2>");
	g_sLangID_Native_UnkCat = _T("Native_UnkCat");
	g_sLangTxt_Native_UnkCat = _T("未知类别");
	g_sLangID_Native_AutoCalc = _T("Native_AutoCalc");
	g_sLangTxt_Native_AutoCalc = _T("自动计算");
	g_sLangID_Native_ManCalcInput = _T("Native_ManCalcInput");
	g_sLangTxt_Native_ManCalcInput = _T("手动计算并输入");
	g_sLangID_Native_HighLow = _T("Native_HighLowt");
	g_sLangTxt_Native_HighLow = _T("高-低");
	g_sLangID_Native_HighMid = _T("Native_HighMid");
	g_sLangTxt_Native_HighMid = _T("高-中");
	g_sLangID_Native_MidLow = _T("Native_MidLow");
	g_sLangTxt_Native_MidLow = _T("中-低");
	g_sLangID_Native_BinSearch = _T("Native_BinSearch");
	g_sLangTxt_Native_BinSearch = _T("二分法");
	g_sLangID_Native_StepApprox = _T("Native_StepApprox");
	g_sLangTxt_Native_StepApprox = _T("单步逼近");
	g_sLangID_Native_NameValue = _T("Native_NameValue");
	g_sLangTxt_Native_NameValue = _T("有名值");
	g_sLangID_Native_PerUnitVal = _T("Native_PerUnitVal");
	g_sLangTxt_Native_PerUnitVal = _T("标幺值");
	g_sLangID_Native_HighSideSecRatedCurr = _T("Native_HighSideSecRatedCurr");
	g_sLangTxt_Native_HighSideSecRatedCurr = _T("高侧额定二次电流");
	g_sLangID_Native_BeSideSecRatedCurr = _T("Native_BeSideSecRatedCurr");
	g_sLangTxt_Native_BeSideSecRatedCurr = _T("各侧二次额定电流");
	g_sLangID_Native_Setpt = _T("Native_Setpt");
	g_sLangTxt_Native_Setpt = _T("设定值");
	g_sLangID_Native_OneTurnPoint = _T("Native_OneTurnPoint");
	g_sLangTxt_Native_OneTurnPoint = _T("一个拐点");
	g_sLangID_Native_TwoTurnPoint = _T("Native_TwoTurnPoint");
	g_sLangTxt_Native_TwoTurnPoint = _T("二个拐点");
	g_sLangID_Native_ThreeTurnPoint = _T("Native_ThreeTurnPoint");
	g_sLangTxt_Native_ThreeTurnPoint = _T("三个拐点");
	g_sLangID_Native_InitValChange = _T("Native_InitValChange");
	g_sLangTxt_Native_InitValChange = _T("变化始值(In):");
	g_sLangID_Native_EndValChange = _T("Native_EndValChange");
	g_sLangTxt_Native_EndValChange = _T("变化终值(In):");
	g_sLangID_Native_ChgStep = _T("Native_ChgStep");
	g_sLangTxt_Native_ChgStep = _T("变化步长(In):");
	g_sLangID_Native_SglSideBalCoeff = _T("Native_SglSideBalCoeff");
	g_sLangTxt_Native_SglSideBalCoeff = _T("Ⅰ侧平衡系数");
	g_sLangID_Native_TwoSideBalCoeff = _T("Native_TwoSideBalCoeff");
	g_sLangTxt_Native_TwoSideBalCoeff = _T("Ⅱ侧平衡系数");
	g_sLangID_Native_ThreeSideBalCoeff = _T("Native_ThreeSideBalCoeff");
	g_sLangTxt_Native_ThreeSideBalCoeff = _T("Ⅲ侧平衡系数");
	g_sLangID_Native_WiringCoeff = _T("Native_WiringCoeff");
	g_sLangTxt_Native_WiringCoeff = _T("接线系数");
	g_sLangID_Native_RefCurr = _T("Native_RefCurr");
	g_sLangTxt_Native_RefCurr = _T("基准电流");
	g_sLangID_Native_HighVoltSide = _T("Native_HighVoltSide");
	g_sLangTxt_Native_HighVoltSide = _T("高压侧");
	g_sLangID_Native_MedVoltSide = _T("Native_MedVoltSide");
	g_sLangTxt_Native_MedVoltSide = _T("中压侧");
	g_sLangID_Native_LowVoltSide = _T("Native_LowVoltSide");
	g_sLangTxt_Native_LowVoltSide = _T("低压侧");
	g_sLangID_Native_DiffProtCurrTerm = _T("Native_DiffProtCurrTerm");
	g_sLangTxt_Native_DiffProtCurrTerm = _T("差动保护电流端子");
	g_sLangID_Native_RelayTest = _T("Native_RelayTest");
	g_sLangTxt_Native_RelayTest = _T("继电保护测试仪");
	g_sLangID_Native_BrakeCurrSy = _T("Native_BrakeCurrSy");
	g_sLangTxt_Native_BrakeCurrSy = _T("制动电流=%1A,");
	g_sLangID_Native_DiffCurrSy = _T("Native_DiffCurrSy");
	g_sLangTxt_Native_DiffCurrSy = _T("差动电流=%1A,");
	g_sLangID_Native_PropBrakeCoeffSy = _T("Native_PropBrakeCoeffSy");
	g_sLangTxt_Native_PropBrakeCoeffSy = _T("比例制动系数=%1");
	g_sLangID_Native_BrakeCurrSyy = _T("Native_BrakeCurrSyy");
	g_sLangTxt_Native_BrakeCurrSyy = _T("制动电流=%1In,");
	g_sLangID_Native_DiffCurrSyy = _T("Native_DiffCurrSyy");
	g_sLangTxt_Native_DiffCurrSyy = _T("差动电流=%1In,");
	g_sLangID_Native_TestProcMonView = _T("Native_TestProcMonView");
	g_sLangTxt_Native_TestProcMonView = _T("测试过程监视图");
	g_sLangID_Native_VecGraphics = _T("Native_VecGraphics");
	g_sLangTxt_Native_VecGraphics = _T("矢量图");
	g_sLangID_Native_LineVolt = _T("Native_LineVolt");
	g_sLangTxt_Native_LineVolt = _T("线电压");
	g_sLangID_Native_InfoChart = _T("Native_InfoChart");
	g_sLangTxt_Native_InfoChart = _T("信息图");
	g_sLangID_Native_PowerChart = _T("Native_PowerChart");
	g_sLangTxt_Native_PowerChart = _T("功率图");
	g_sLangID_Native_CharactCurve = _T("Native_CharactCurve");
	g_sLangTxt_Native_CharactCurve = _T("动作特性曲线");
	g_sLangID_Native_SearchUpperLimit = _T("Native_SearchUpperLimit");
	g_sLangTxt_Native_SearchUpperLimit = _T("搜索上限");
	g_sLangID_Native_SearchLowerLimit = _T("Native_SearchLowerLimit");
	g_sLangTxt_Native_SearchLowerLimit = _T("搜索下限");
	g_sLangID_Native_EnterValidNumber = _T("Native_EnterValidNumber");
	g_sLangTxt_Native_EnterValidNumber = _T("请输入有效数字！");
	g_sLangID_Native_InputBrakeCurrOutOfRange = _T("Native_InputBrakeCurrOutOfRange");
	g_sLangTxt_Native_InputBrakeCurrOutOfRange = _T("输入制动电流值[%f]不在有效范围.");
	g_sLangID_Native_PrepTime = _T("Native_PrepTime");
	g_sLangTxt_Native_PrepTime = _T("准备时间");

	g_sLangID_Native_BalanceCoeffEachSide = _T("Native_BalanceCoeffEachSide");
	g_sLangTxt_Native_BalanceCoeffEachSide = _T("各侧平衡系数");

	g_sLangID_Native_TestWinding = _T("Native_TestWinding");
	g_sLangTxt_Native_TestWinding = _T("测试绕组");


	

	g_sLangID_Native_InsSeries = _T("Native_InsSeries");
	g_sLangTxt_Native_InsSeries = _T("插入系列");
	g_sLangID_Native_TestResEval = _T("Native_TestResEval");
	g_sLangTxt_Native_TestResEval = _T("试验结果及评估");
	g_sLangID_Native_ErrBlank = _T("Native_ErrBlank");
	g_sLangTxt_Native_ErrBlank = _T("误  差");
	g_sLangID_Native_BrkCurrBlank = _T("Native_BrkCurrBlank");
	g_sLangTxt_Native_BrkCurrBlank = _T("制  动  电  流");

	// 第五周许
	// xwd5
	g_sLangID_Native_BrakingCurrent = _T("Native_BrakingCurrent");
	g_sLangTxt_Native_BrakingCurrent = _T("制动电流(In)");
	g_sLangID_Native_SearchUpper = _T("Native_SearchUpper");
	g_sLangTxt_Native_SearchUpper = _T("搜索上限(In)");
	g_sLangID_Native_SearchLower = _T("Native_SearchLower");
	g_sLangTxt_Native_SearchLower = _T("搜索下限(In)");
	g_sLangID_Native_TestPrecisionA = _T("Native_TestPrecisionA");
	g_sLangTxt_Native_TestPrecisionA = _T("测试精度(A)");
	g_sLangID_Native_TestPrecisionIn = _T("Native_TestPrecisionIn");
	g_sLangTxt_Native_TestPrecisionIn = _T("测试精度(In)");
	g_sLangID_Native_StartCurrent = _T("Native_StartCurrent");
	g_sLangTxt_Native_StartCurrent = _T("启动电流(A)");
	g_sLangID_Native_StartCurrentIn = _T("Native_StartCurrentIn");
	g_sLangTxt_Native_StartCurrentIn = _T("启动电流(In)");
	g_sLangID_Native_DiffCurrentIn = _T("Native_DiffCurrentIn");
	g_sLangTxt_Native_DiffCurrentIn = _T("差动电流(In)");
	g_sLangID_Native_BrkCur = _T("Native_BrkCur");
	g_sLangTxt_Native_BrkCur = _T("速断电流(A)");
	g_sLangID_Native_BrkCurIn = _T("Native_BrkCurIn");
	g_sLangTxt_Native_BrkCurIn = _T("速断电流(In)");
	g_sLangID_Native_SrchUpLimA = _T("Native_SrchUpLimA");
	g_sLangTxt_Native_SrchUpLimA = _T("搜索上限(A)");
	g_sLangID_Native_SrchLowLimA = _T("Native_SrchLowLimA");
	g_sLangTxt_Native_SrchLowLimA = _T("搜索下限(A)");
	g_sLangID_Native_ValidNum = _T("Native_ValidNum");
	g_sLangTxt_Native_ValidNum = _T("请输入有效数字！");

	// 第五周吕
	// exswitchset
	g_sLangID_Native_BinEx20 = _T("Native_BinEx20");
	g_sLangTxt_Native_BinEx20 = _T("扩展开入量_20");

	// OffLineDlg
	g_sLangID_Native_TestModelTypeSelect = _T("Native_TestModelTypeSelect");
	g_sLangTxt_Native_TestModelTypeSelect = _T("测试仪型号类型选择");

	// daSetdlg
	g_sLangID_Native_tester_type = _T("Native_tester_type");
	g_sLangTxt_Native_tester_type = _T("测试仪类型");
	g_sLangID_Native_digital_signal = _T("Native_digital_signal");
	g_sLangTxt_Native_digital_signal = _T("数字量");
	g_sLangID_Native_curmodule_set = _T("Native_curmodule_set");
	g_sLangTxt_Native_curmodule_set = _T("电流模块设定");
	g_sLangID_Native_acrange_set = _T("Native_acrange_set");
	g_sLangTxt_Native_acrange_set = _T("交流电流档位设置");
	g_sLangID_Native_acmaxportvol_set = _T("Native_acmaxportvol_set");
	g_sLangTxt_Native_acmaxportvol_set = _T("交流电流最大端口电压设置");
	g_sLangID_Native_debounce_time = _T("Native_debounce_time");
	g_sLangTxt_Native_debounce_time = _T("防抖时间(S)：");
	g_sLangID_Native_highcurterm_Isoutput = _T("Native_highcurterm_Isoutput");
	g_sLangTxt_Native_highcurterml_Isoutput = _T("使用大电流端子Is输出");
	g_sLangID_Native_6Ito3I_output = _T("Native_6Ito3I_output");
	g_sLangTxt_Native_6Ito3I_output = _T("电流6I合并成3I输出");

	// dcSetdlg
	g_sLangID_Native_auxiliary_DCvol = _T("Native_auxiliary_DCvol");
	g_sLangTxt_Native_auxiliary_DCvol = _T("辅助直流电压(V)");
	g_sLangID_Native_start_DC_output = _T("Native_start_DC_output");
	g_sLangTxt_Native_start_DC_output = _T("开始直流输出");
	g_sLangID_Native_stop_DC_output = _T("Native_stop_DC_output");
	g_sLangTxt_Native_stop_DC_output = _T("停止直流输出");
	g_sLangID_Native_start_steadyoutput = _T("Native_start_steadyoutput");
	g_sLangTxt_Native_start_steadyoutput = _T("开始稳态量输出");
	g_sLangID_Native_stop_steadyoutput = _T("Native_stop_steadyoutput");
	g_sLangTxt_Native_stop_steadyoutput = _T("停止稳态量输出");
	g_sLangID_Native_AC_DC_steadyoutput = _T("Native_AC_DC_steadyoutput");
	g_sLangTxt_Native_AC_DC_steadyoutput = _T("交直流稳态输出");
	g_sLangID_Native_auxiDC_output_notempty = _T("Native_auxiDC_output_notempty");
	g_sLangTxt_Native_auxiDC_output_notempty = _T("辅助直流输出不可为空");
	g_sLangID_Native_auxiDC_output_positive = _T("Native_auxiDC_output_positive");
	g_sLangTxt_Native_auxiDC_output_positive = _T("要求：辅助直流输出>0");

	// commonparasDlg
	g_sLangID_Native_extractvol_outputdef = _T("Native_extractvol_outputdef");
	g_sLangTxt_Native_extractvol_outputdef = _T("抽取电压输出定义：");
	g_sLangID_Native_extractvol_refphasedef = _T("Native_extractvol_refphasedef");
	g_sLangTxt_Native_extractvol_refphasedef = _T("抽取电压参考相定义：");
	g_sLangID_Native_extractvol_phaseangle = _T("Native_extractvol_phaseangle");
	g_sLangTxt_Native_extractvol_phaseangle = _T("抽取电压相角(相对参考相)：");

	g_sLangID_Native_coincidence_mode = _T("Native_coincidence_mode");
	g_sLangTxt_Native_coincidence_mode = _T("重合方式:");
	g_sLangID_Native_duration_afterjump = _T("Native_duration_afterjump");
	g_sLangTxt_Native_duration_afterjump = _T("开关跳后持续时间(s):");
	g_sLangID_Native_duration_coincidence = _T("Native_duration_coincidence");
	g_sLangTxt_Native_duration_coincidence = _T("重合持续时间(s):");
	g_sLangID_Native_postaccelerat_duration = _T("Native_postaccelerat_duration");
	g_sLangTxt_Native_postaccelerat_duration = _T("后加速开关跳开后持续时间(s):");
	g_sLangID_Native_impedance_refmode = _T("Native_impedance_refmode");
	g_sLangTxt_Native_impedance_refmode = _T("阻抗参考方式:");
	g_sLangID_Native_zeroseq_comp_calculat = _T("Native_zeroseq_comp_calculat");
	g_sLangTxt_Native_zeroseq_comp_calculat = _T("零序补偿系数计算方式:");
	g_sLangID_Native_system_impedance = _T("Native_system_impedance");
	g_sLangTxt_Native_system_impedance = _T("系统阻抗(Ω):");
	g_sLangID_Native_system_impedance_angle = _T("Native_system_impedance_angle");
	g_sLangTxt_Native_system_impedance_angle = _T("系统阻抗角(°):");
	g_sLangID_Native_closingangle_select = _T("Native_closingangle_select");
	g_sLangTxt_Native_closingangle_select = _T("合闸角选择:");
	g_sLangID_Native_closingangle = _T("Native_closingangle");
	g_sLangTxt_Native_closingangle = _T("合闸角(°):");
	g_sLangID_Native_closingangle_way = _T("Native_closingangle_way");
	g_sLangTxt_Native_closingangle_way = _T("合闸角方式:");
	g_sLangID_Native_superimposed_nonperiodic = _T("Native_superimposed_nonperiodic");
	g_sLangTxt_Native_superimposed_nonperiodic = _T("叠加非周期分量(°):");
	g_sLangID_Native_search_mode = _T("Native_search_mode");
	g_sLangTxt_Native_search_mode = _T("搜索方式:");

	g_sLangID_Native_testprocess_control = _T("Native_testprocess_control");
	g_sLangTxt_Native_testprocess_control = _T("试验过程控制方式:");
	g_sLangID_Native_faultphase_definition = _T("Native_faultphase_definition");
	g_sLangTxt_Native_faultphase_definition = _T("故障相定义:");
	g_sLangID_Native_bottominfo_printset = _T("Native_bottominfo_printset");
	g_sLangTxt_Native_bottominfo_printset = _T("底层信息打印设置");
	g_sLangID_Native_bottomloginfo_printornot = _T("Native_bottomloginfo_printornot");
	g_sLangTxt_Native_bottomloginfo_printornot = _T("是否打印底层日志信息");
	g_sLangID_Native_bottomtestinfo_saveornot = _T("Native_bottomtestinfo_saveornot");
	g_sLangTxt_Native_bottomtestinfo_saveornot = _T("是否保存底层测试信息");

	//
	g_sLangID_Native_StartIr = _T("Native_StartIr");
	g_sLangTxt_Native_StartIr = _T("启动Ir");
	g_sLangID_Native_RatioCoefficient = _T("Native_RatioCoefficient");
	g_sLangTxt_Native_RatioCoefficient = _T("比率系数");
	g_sLangID_Native_AddTestPoint = _T("Native_AddTestPoint");
	g_sLangTxt_Native_AddTestPoint = _T("添加测试点");

	g_sLangID_Native_BreakoffIr = _T("Native_BreakoffIr");
	g_sLangTxt_Native_BreakoffIr = _T("速断Ir");
	g_sLangID_Native_HarmCountId2 = _T("Native_HarmCountId2");
	g_sLangTxt_Native_HarmCountId2 = _T("2次谐波Id");
	g_sLangID_Native_HarmCountId3 = _T("Native_HarmCountId3");
	g_sLangTxt_Native_HarmCountId3 = _T("3次谐波Id");
	g_sLangID_Native_HarmCountId5 = _T("Native_HarmCountId5");
	g_sLangTxt_Native_HarmCountId5 = _T("5次谐波Id");

	// goose
	g_sLangID_Native_statusName = _T("Native_statusName");
	g_sLangTxt_Native_statusName = _T("状态名称：");
	g_sLangID_Native_outputTime = _T("Native_outputTime");
	g_sLangTxt_Native_outputTime = _T("输出时间(s):");

	// 第五周马
	// partparawidget_trans

	g_sLangID_Native_ExprOutOfRange = _T("Native_ExprOutOfRange");
	g_sLangTxt_Native_ExprOutOfRange = _T("表达式超出范围");
	g_sLangID_Native_ABCTP = _T("Native_ABCTP");
	g_sLangTxt_Native_ABCTP = _T("ABC三相");
	g_sLangID_Native_Zphase = _T("Native_ZphaseP");
	g_sLangTxt_Native_Zphase = _T("Z相");
	g_sLangID_Native_ActPower = _T("Native_ActPower");
	g_sLangTxt_Native_ActPower = _T("有功功率");
	g_sLangID_Native_ReacPower = _T("Native_ReacPower");
	g_sLangTxt_Native_ReacPower = _T("无功功率");
	g_sLangID_Native_AppPower = _T("Native_AppPower");
	g_sLangTxt_Native_AppPower = _T("视在功率");

	// QScanLanTesterDlg_trans
	g_sLangID_Native_SubMask = _T("Native_SubMask");
	g_sLangTxt_Native_SubMask = _T("子网掩码");
	g_sLangID_Native_LST = _T("Native_LST");
	g_sLangTxt_Native_LST = _T("扫描局域网测试仪");
	g_sLangID_Native_NetAdptSelect = _T("Native_NetAdptSelect");
	g_sLangTxt_Native_NetAdptSelect = _T("网卡选择");
	g_sLangID_Native_ModTesterIP = _T("Native_ModTesterIP");
	g_sLangTxt_Native_ModTesterIP = _T("修改测试仪IP");
	g_sLangID_Native_IPAddr = _T("Native_IPAddr");
	g_sLangTxt_Native_IPAddr = _T("IP地址");
	g_sLangID_Native_FailToRetrieveNetAddr = _T("Native_FailToRetrieveNetAddr");
	g_sLangTxt_Native_FailToRetrieveNetAddr = _T("获取本地IP地址失败,当前值为空.");
	g_sLangID_Native_FailToRetDevInfo = _T("Native_FailToRetDevInfo");
	g_sLangTxt_Native_FailToRetDevInfo = _T("取得设备信息失败");
	g_sLangID_Native_AddrNotInSameSubnet = _T("Native_AddrNotInSameSubnet");
	g_sLangTxt_Native_AddrNotInSameSubnet = _T("测试仪IP地址(%1)与当前网卡IP不在同一网段,是否修改?");
	g_sLangID_Native_CurrSelNetAdptEmpty = _T("Native_CurrSelNetAdptEmpty");
	g_sLangTxt_Native_CurrSelNetAdptEmpty = _T("当前选择的网卡为空.");
	g_sLangID_Native_Unknown = _T("Native_Unknown");
	g_sLangTxt_Native_Unknown = _T("未知");
	g_sLangID_Native_TestDevInfo = _T("Native_TestDevInfo");
	g_sLangTxt_Native_TestDevInfo = _T("被测装置信息");
	g_sLangID_Native_PhAVoltage = _T("Native_PhAVoltage");
	g_sLangTxt_Native_PhAVoltage = _T("A相电压");
	g_sLangID_Native_PhBVoltage = _T("Native_PhBVoltage");
	g_sLangTxt_Native_PhBVoltage = _T("B相电压");
	g_sLangID_Native_PhCVoltage = _T("Native_PhCVoltage");
	g_sLangTxt_Native_PhCVoltage = _T("C相电压");
	g_sLangID_Native_PhABCVoltage = _T("Native_PhABCVoltage");
	g_sLangTxt_Native_PhABCVoltage = _T("ABC相电压");
	g_sLangID_Native_TDITrigger = _T("Native_TDITrigger");
	g_sLangTxt_Native_TDITrigger = _T("时间+开入量触发");
	g_sLangID_Native_Overlay = _T("Native_Overlay");
	g_sLangTxt_Native_Overlay = _T("叠加");
	g_sLangID_Native_NoOverlay = _T("Native_NoOverlay");
	g_sLangTxt_Native_NoOverlay = _T("不叠加");
	g_sLangID_Native_Random = _T("Native_Random");
	g_sLangTxt_Native_Random = _T("随机");

	g_sLangID_Native_BalanceCoeff = _T("Native_BalanceCoeff");
	g_sLangTxt_Native_BalanceCoeff = _T("平衡系数：");
	g_sLangID_Native_DiffFastCur = _T("Native_DiffFastCur");
	g_sLangTxt_Native_DiffFastCur = _T("差动速断电流定值(A)：");
	g_sLangID_Native_DiffActCur = _T("Native_DiffActCur");
	g_sLangTxt_Native_DiffActCur = _T("差动动作电流定值(A)：");
	g_sLangID_Native_RatioBreakPt1 = _T("Native_RatioBreakPt1");
	g_sLangTxt_Native_RatioBreakPt1 = _T("比率制动特性拐点1电流(A)：");
	g_sLangID_Native_RatioBreakPt2 = _T("Native_RatioBreakPt2");
	g_sLangTxt_Native_RatioBreakPt2 = _T("比率制动特性拐点2电流(A)：");
	g_sLangID_Native_BaseRatioSlope1 = _T("Native_BaseRatioSlope1");
	g_sLangTxt_Native_BaseRatioSlope1 = _T("基波比率制动特性斜率1：");
	g_sLangID_Native_BaseRatioSlope2 = _T("Native_BaseRatioSlope2");
	g_sLangTxt_Native_BaseRatioSlope2 = _T("基波比率制动特性斜率2：");
	g_sLangID_Native_SecondHarmBrakeCoef = _T("Native_SecondHarmBrakeCoef");
	g_sLangTxt_Native_SecondHarmBrakeCoef = _T("二次谐波制动系数：");
	g_sLangID_Native_ThirdHarmBrakeCoef = _T("Native_ThirdHarmBrakeCoef");
	g_sLangTxt_Native_ThirdHarmBrakeCoef = _T("三次谐波制动系数：");
	g_sLangID_Native_FifthHarmBrakeCoef = _T("Native_FifthHarmBrakeCoef");
	g_sLangTxt_Native_FifthHarmBrakeCoef = _T("五次谐波制动系数：");

	// 第六周许
	g_sLangID_Native_BulkWaveImport = _T("Native_BulkWaveImport");
	g_sLangTxt_Native_BulkWaveImport = _T("批量导入波形");
	g_sLangID_Native_BulkWaveFileImport = _T("Native_BulkWaveFileImport");
	g_sLangTxt_Native_BulkWaveFileImport = _T("批量导入波形文件");
	g_sLangID_Native_OpeningWaveFile = _T("Native_OpeningWaveFile");
	g_sLangTxt_Native_OpeningWaveFile = _T("正在打开录波文件...");
	g_sLangID_Native_SelectFolder = _T("Native_SelectFolder");
	g_sLangTxt_Native_SelectFolder = _T("请选择文件夹");
	g_sLangID_Native_NoWaveFiles = _T("Native_NoWaveFiles");
	g_sLangTxt_Native_NoWaveFiles = _T("该文件夹下没有录波文件！");
	g_sLangID_Native_WaveExceedMax = _T("Native_WaveExceedMax");
	g_sLangTxt_Native_WaveExceedMax = _T("当前导入波形大于100，超出最大导入波形个数！");
	g_sLangID_Native_ApplyAllCh = _T("Native_ApplyAllCh");
	g_sLangTxt_Native_ApplyAllCh = _T("全部应用通道");
	g_sLangID_Native_ApplyAllRatio = _T("Native_ApplyAllRatio");
	g_sLangTxt_Native_ApplyAllRatio = _T("全部应用变比");
	g_sLangID_Native_AllCycleCount = _T("Native_AllCycleCount");
	g_sLangTxt_Native_AllCycleCount = _T("全部循环次数：");
	g_sLangID_Native_ManualCtrl = _T("Native_ManualCtrl");
	g_sLangTxt_Native_ManualCtrl = _T("  手动控制  ：");
	g_sLangID_Native_SelectWave = _T("Native_SelectWave");
	g_sLangTxt_Native_SelectWave = _T("请选择播放波形");
	g_sLangID_Native_PlayPrev = _T("Native_PlayPrev");
	g_sLangTxt_Native_PlayPrev = _T("播放上一个");
	g_sLangID_Native_PlayNext = _T("Native_PlayNext");
	g_sLangTxt_Native_PlayNext = _T("播放下一个");
	g_sLangID_Native_StopTestOut = _T("Native_StopTestOut");
	g_sLangTxt_Native_StopTestOut = _T("停止测试仪输出");
	g_sLangID_Native_DiffCurve = _T("Native_DiffCurve");
	g_sLangTxt_Native_DiffCurve = _T("差动特征曲线图");
	g_sLangID_Native_HarmBrakeCurve = _T("Native_HarmBrakeCurve");
	g_sLangTxt_Native_HarmBrakeCurve = _T("谐波制动特征曲线图");
	g_sLangID_Native_ActionTimeCurve = _T("Native_ActionTimeCurve");
	g_sLangTxt_Native_ActionTimeCurve = _T("动作时间特征曲线图");
	g_sLangID_Native_SOETestParamFileNotExist = _T("Native_SOETestParamFileNotExist");
	g_sLangTxt_Native_SOETestParamFileNotExist = _T("Soe测试参数文件【%s】不存在");
	g_sLangID_Native_SOETestParamFileParseFail = _T("Native_SOETestParamFileParseFail");
	g_sLangTxt_Native_SOETestParamFileParseFail = _T("解析Soe测试参数文件失败【%s】");

	// 第六周吕
	// 吕Overload Test
	g_sLangID_Native_overloadACTestTempFile = _T("Native_overloadACTestTempFile");
	g_sLangTxt_Native_overloadACTestTempFile = _T("过负荷(交流)试验模板文件");
	g_sLangID_Native_Wel_overloadACTest = _T("Native_Wel_overloadACTest");
	g_sLangTxt_Native_Wel_overloadACTest = _T("欢迎使用过负荷(交流)试验.");
	g_sLangID_Native_Ponovo_overloadACTest = _T("Native_Ponovo_overloadACTest");
	g_sLangTxt_Native_Ponovo_overloadACTest = _T("Ponovo 过负荷(交流)试验");
	g_sLangID_Native_overloadACTest = _T("Native_overloadACTest");
	g_sLangTxt_Native_overloadACTest = _T("过负荷(交流)试验");

	g_sLangID_Native_overloadCurrentChannel = _T("Native_overloadCurrentChannel");
	g_sLangTxt_Native_overloadCurrentChannel = _T("过负荷电流通道");
	g_sLangID_Native_overloadCurChannel = _T("Native_overloadCurChannel");
	g_sLangTxt_Native_overloadCurChannel = _T("过负荷电流通道:");
	g_sLangID_Native_overloadAC = _T("Native_overloadAC");
	g_sLangTxt_Native_overloadAC = _T("过负荷(交流)");
	g_sLangID_Native_overloadCurrentIA = _T("Native_overloadCurrentIA");
	g_sLangTxt_Native_overloadCurrentIA = _T("过负荷电流I(A):");
	g_sLangID_Native_NormTimeS = _T("Native_NormTime");
	g_sLangTxt_Native_NormTimeS = _T("常态时间(s):");

	// IEC

	// 第六周马
	g_sLangID_Native_OverloadCurrTestTemplate = _T("Native_OverloadCurrTestTemplate");
	g_sLangTxt_Native_OverloadCurrTestTemplate = _T("过负荷(电流)试验模板文件");
	g_sLangID_Native_WelcomeToOverloadDCTest = _T("Native_WelcomeToOverloadDCTest");
	g_sLangTxt_Native_WelcomeToOverloadDCTest = _T("欢迎使用过负荷(直流)试验.");
	g_sLangID_Native_OverloadDCTest = _T("Native_OverloadDCTest");
	g_sLangTxt_Native_OverloadDCTest = _T("过负荷(直流)试验");
	g_sLangID_Native_ThermalOverloadTripSetting = _T("Native_ThermalOverloadTripSetting");
	g_sLangTxt_Native_ThermalOverloadTripSetting = _T("热过负荷动作定值k");
	g_sLangID_Native_ThermalOverloadRefCurr = _T("Native_ThermalOverloadRefCurr");
	g_sLangTxt_Native_ThermalOverloadRefCurr = _T("热过负荷基准电流IB");
	g_sLangID_Native_ThermalOverloadTimeConst = _T("Native_ThermalOverloadTimeConst");
	g_sLangTxt_Native_ThermalOverloadTimeConst = _T("热过负荷时间常数τ");
	g_sLangID_Native_RedefineToChar = _T("Native_RedefineToChar");
	g_sLangTxt_Native_RedefineToChar = _T("输出参数导致动作时间定值为负数，未修改成功，请根据动作特性方程重新修改!");

	g_sLangID_Native_OverloadDC = _T("Native_OverloadDC");
	g_sLangTxt_Native_OverloadDC = _T("<h1>过负荷(直流)</h1>");
	g_sLangID_Native_CurrChannelNotFound = _T("Native_CurrChannelNotFound");
	g_sLangTxt_Native_CurrChannelNotFound = _T("当前选择的电流通道(Index=%d)未查找到.");
	g_sLangID_Native_ProtCharEquation = _T("Native_ProtCharEquation");
	g_sLangTxt_Native_ProtCharEquation = _T("动作特性方程");
	g_sLangID_Native_OverloadCurr = _T("Native_OverloadCurr");
	g_sLangTxt_Native_OverloadCurr = _T("过负荷电流I(A)");

	g_sLangID_Native_TotalMsgs = _T("Native_TotalMsgs");
	g_sLangTxt_Native_TotalMsgs = _T("报文总数");
	g_sLangID_Native_PktLossCount = _T("Native_PktLossCount");
	g_sLangTxt_Native_PktLossCount = _T("丢包数");
	g_sLangID_Native_MaxTimeDiff = _T("Native_MaxTimeDiff");
	g_sLangTxt_Native_MaxTimeDiff = _T("最大时间差");
	g_sLangID_Native_StopWriteFile = _T("Native_StopWriteFile");
	g_sLangTxt_Native_StopWriteFile = _T("停止写文件");

	// 第七周吕
	// overvaltage
	g_sLangID_Native_OVtempfile = _T("Native_OVtempfile");
	g_sLangTxt_Native_OVtempfile = _T("过压试验模板文件");
	g_sLangID_Native_wel_OVtest = _T("Native_wel_OVtest");
	g_sLangTxt_Native_wel_OVtest = _T("欢迎使用过压测试.");
	g_sLangID_Native_OVprotect = _T("Native_OVprotect");
	g_sLangTxt_Native_OVprotect = _T("过电压保护");
	g_sLangID_Native_OverValtage = _T("Native_OverValtage");
	g_sLangTxt_Native_OverValtage = _T("过压");
	g_sLangID_Native_OVprotect_Actvalue = _T("Native_OVprotect_Actvalue");
	g_sLangTxt_Native_OVprotect_Actvalue = _T("过压保护动作值");
	g_sLangID_Native_OV_ActTimelim = _T("Native_OV_ActTimelim");
	g_sLangTxt_Native_OV_ActTimelim = _T("过电压动作时限");
	g_sLangID_Native_ActVNega_Error = _T("Native_ActVNega_Error");
	g_sLangTxt_Native_ActVNega_Error = _T("当前动作电压为负，修改不成功.");
	g_sLangID_Native_ActTNega_Error = _T("Native_ActTNega_Error");
	g_sLangTxt_Native_ActTNega_Error = _T("当前动作时间为负，修改不成功.");
	g_sLangID_Native_Name_OVprotectTest = _T("Native_Name_OVprotectTest");
	g_sLangTxt_Native_Name_OVprotectTest = _T("试验名称：过压保护定值测试");
	g_sLangID_Native_OVprotectTest = _T("Native_OVprotectTest");
	g_sLangTxt_Native_OVprotectTest = _T("过压保护定值测试");
	g_sLangID_Native_1ErrorType_and_Times = _T("Native_1ErrorType_and_Times");
	g_sLangTxt_Native_1ErrorType_and_Times = _T("请务必至少选择一个故障类型以及倍数！");
	g_sLangID_Native_SetValueV = _T("Native_SetValueV");
	g_sLangTxt_Native_SetValueV = _T("整定值(V)");
	g_sLangID_Native_AddTestDig = _T("Native_AddTestDig");
	g_sLangTxt_Native_AddTestDig = _T("添加测试项");

	// 第七周马
	g_sLangID_Native_VoltProtTestTplFile = _T("Native_VoltProtTestTplFile");
	g_sLangTxt_Native_VoltProtTestTplFile = _T("电压保护试验模板文件");
	g_sLangID_Native_WelcomeVoltProtTest = _T("Native_WelcomeVoltProtTest");
	g_sLangTxt_Native_WelcomeVoltProtTest = _T("欢迎使用电压保护测试.");
	g_sLangID_Native_VoltProtection = _T("Native_VoltProtection");
	g_sLangTxt_Native_VoltProtection = _T("电压保护");
	g_sLangID_Native_VIStagePickVal = _T("Native_VIStagePickVal");
	g_sLangTxt_Native_VIStagePickVal = _T("电压I段动作值");
	g_sLangID_Native_VIIStagePickVal = _T("Native_VIIStagePickVal");
	g_sLangTxt_Native_VIIStagePickVal = _T("电压II段动作值");
	g_sLangID_Native_VIIIStagePickVal = _T("Native_VIIIStagePickVal");
	g_sLangTxt_Native_VIIIStagePickVal = _T("电压III段动作值");
	g_sLangID_Native_VIVStagePickVal = _T("Native_VIVStagePickVal");
	g_sLangTxt_Native_VIVStagePickVal = _T("电压IV段动作值");
	g_sLangID_Native_VIPickTime = _T("Native_VIPickTime");
	g_sLangTxt_Native_VIPickTime = _T("电压I段动作时间");
	g_sLangID_Native_VIIPickTime = _T("Native_VIIPickTime");
	g_sLangTxt_Native_VIIPickTime = _T("电压II段动作时间");
	g_sLangID_Native_VIIIPickTime = _T("Native_VIIIPickTime");
	g_sLangTxt_Native_VIIIPickTime = _T("电压III段动作时间");
	g_sLangID_Native_VIVPickTime = _T("Native_VIVPickTime");
	g_sLangTxt_Native_VIVPickTime = _T("电压IV段动作时间");
	g_sLangID_Native_CurrPickNegModUnsucc = _T("Native_CurrPickNegModUnsucc");
	g_sLangTxt_Native_CurrPickNegModUnsucc = _T("当前动作值为负，修改不成功.");
	g_sLangID_Native_Ovltg = _T("Native_Ovltg");
	g_sLangTxt_Native_Ovltg = _T("过电压");
	g_sLangID_Native_OvltgProtSetTest = _T("Native_OvltgProtSetTest");
	g_sLangTxt_Native_OvltgProtSetTest = _T("试验名称：过压保护定值测试");
	g_sLangID_Native_OvltgIProtSetTest = _T("Native_OvltgIProtSetTest");
	g_sLangTxt_Native_OvltgIProtSetTest = _T("过压I段保护定值测试");
	g_sLangID_Native_OvltgIIProtSetTest = _T("Native_OvltgIIProtSetTest");
	g_sLangTxt_Native_OvltgIIProtSetTest = _T("过压II段保护定值测试");
	g_sLangID_Native_OvltgIIIProtSetTest = _T("Native_OvltgIIIProtSetTest");
	g_sLangTxt_Native_OvltgIIIProtSetTest = _T("过压III段保护定值测试");
	g_sLangID_Native_OvltgIVProtSetTest = _T("Native_OvltgIVProtSetTest");
	g_sLangTxt_Native_OvltgIVProtSetTest = _T("过压IV段保护定值测试");
	g_sLangID_Native_OvltgVProtSetTest = _T("Native_OvltgVProtSetTest");
	g_sLangTxt_Native_OvltgVProtSetTest = _T("过压V段保护定值测试");
	g_sLangID_Native_PreFaultOut = _T("Native_PreFaultOut");
	g_sLangTxt_Native_PreFaultOut = _T("故障前输出");

	g_sLangID_Native_PreFaultTimeMargin = _T("Native_PreFaultTimeMargin");
	g_sLangTxt_Native_PreFaultTimeMargin = _T("故障前时间裕度");
	g_sLangID_Native_CSVLessMinModUnsucc = _T("Native_CSVLessMinModUnsucc");
	g_sLangTxt_Native_CSVLessMinModUnsucc = _T("当前设置值(%f)小于最小值(0.000000),修改不成功");
	g_sLangID_Native_CSVGreaterMaxForceSetMax = _T("Native_CSVGreaterMaxForceSetMax");
	g_sLangTxt_Native_CSVGreaterMaxForceSetMax = _T("当前设置值(%f)大于最大值(%f),强制设置为最大值");
	g_sLangID_Native_CSVGreaterMaxForceSetMax9 = _T("Native_CSVGreaterMaxForceSetMax9");
	g_sLangTxt_Native_CSVGreaterMaxForceSetMax9 = _T("当前设置值(%f)大于最大值(999.000000),强制设置为最大值");
}

// LY 吕
CString g_sLangID_ActTime_Protect_TestTempFile;		//= _T("ActTime_Protect_TestTempFile");
CString g_sLangTxt_ActTime_Protect_TestTempFile;	//=  _T("动作时间保护试验模板文件");
CString g_sLangID_ActionTime_test;					//= _T("ActionTime_test");
CString g_sLangTxt_ActionTime_test;					//=  _T("欢迎使用动作时间实验");
CString g_sLangID_Native_PonovoActiontime;			//= _T("Native_PonovoActiontime");
CString g_sLangTxt_Native_PonovoActiontime;			//=  _T("Ponovo动作时间");
CString g_sLangID_ActionTimeTest;					//= _T("ActionTimeTest");
CString g_sLangTxt_ActionTimeTest;					//=  _T("动作时间测试");
CString g_sLangID_Single_phaseGroundFault;			//= _T("Single_phaseGroundFault");
CString g_sLangTxt_Single_phaseGroundFault;			//=  _T("单相接地短路");
CString g_sLangID_PhasetoPhase_ShortCircuit;		//= _T("PhasetoPhase_ShortCircuit");
CString g_sLangTxt_PhasetoPhase_ShortCircuit;		//=  _T("相间短路");
CString g_sLangID_Zero_SequenceCurrent;				//= _T("Zero_SequenceCurrent");
CString g_sLangTxt_Zero_SequenceCurrent;			//=  _T("零序电流");
CString g_sLangID_Negative_SequenceCurrent;			//= _T("Negative_SequenceCurrent");
CString g_sLangTxt_Negative_SequenceCurrent;		//=  _T("负序电流");
CString g_sLangID_ParaConnect_Three_PhaseCurrents;	//= _T("ParaConnect_Three_PhaseCurrents");
CString g_sLangTxt_ParaConnect_Three_PhaseCurrents; //=  _T("三相电流并联");
CString g_sLangID_Single_PhaseFault;				//= _T("Single_PhaseFault");
CString g_sLangTxt_Single_PhaseFault;				//=  _T("单相故障");
// 吕
CString g_sLangID_AutoSyn_TestTempFile;
CString g_sLangTxt_AutoSyn_TestTempFile;
CString g_sLangID_Wel_AutoSynTest;
CString g_sLangTxt_Wel_AutoSynTest;
CString g_sLangID_Ponovo_AutoSyn;
CString g_sLangTxt_Ponovo_AutoSyn;
CString g_sLangID_AutoSyn;
CString g_sLangTxt_AutoSyn;


CString g_sLangID_System_Rated_FreqHZ;
CString g_sLangTxt_System_Rated_FreqHZ;
CString g_sLangID_System_Rated_Volt;
CString g_sLangTxt_System_Rated_Volt;
CString g_sLangID_Grid_VolV;
CString g_sLangTxt_Grid_VolV;
CString g_sLangID_Stepsize_Grid_volvariation;
CString g_sLangTxt_Stepsize_Grid_volvariation;

CString g_sLangID_Grid_Rated_VolV;
CString g_sLangTxt_Grid_Rated_VolV;


CString g_sLangID_VolDifference;
CString g_sLangTxt_VolDifference;

CString g_sLangID_Allow_VolDifV;
CString g_sLangTxt_Allow_VolDifV;
CString g_sLangID_FreqDifference;
CString g_sLangTxt_FreqDifference;

CString g_sLangID_Allow_FreqDifHZ;
CString g_sLangTxt_Allow_FreqDifHZ;

CString g_sLangID_AtleastOneTest;
CString g_sLangTxt_AtleastOneTest;
CString g_sLangID_Vol_BoundValueTest;
CString g_sLangTxt_Vol_BoundValueTest;
CString g_sLangID_Volbound_trip_values;
CString g_sLangTxt_Volbound_trip_values;
CString g_sLangID_Freq_BoundValueTest;
CString g_sLangTxt_Freq_BoundValueTest;
CString g_sLangID_Auto_AdjustTest;
CString g_sLangTxt_Auto_AdjustTest;
CString g_sLangID_Vol_ReguPeriodTest;
CString g_sLangTxt_Vol_ReguPeriodTest;
CString g_sLangID_Freq_ReguPeriodTest;
CString g_sLangTxt_Freq_ReguPeriodTest;
CString g_sLangID_Lead_AngleTime_Test;
CString g_sLangTxt_Lead_AngleTime_Test;
CString g_sLangID_result;
CString g_sLangTxt_result;
CString g_sLangID_Stepsize_Grid_freqvariation;
CString g_sLangTxt_Stepsize_Grid_freqvariation;
CString g_sLangID_Freqbound_trip_values;
CString g_sLangTxt_Freqbound_trip_values;
CString g_sLangID_Leading_Angle;
CString g_sLangTxt_Leading_Angle;
CString g_sLangID_Leading_Time;
CString g_sLangTxt_Leading_Time;
CString g_sLangID_Native_dVzd;
CString g_sLangTxt_Native_dVzd;
CString g_sLangID_Native_dFzd;
CString g_sLangTxt_Native_dFzd;
CString g_sLangID_Native_Ut;
CString g_sLangTxt_Native_Ut;
CString g_sLangID_AdjVolCycle;
CString g_sLangTxt_AdjVolCycle;
CString g_sLangID_AdjVolWidth;
CString g_sLangTxt_AdjVolWidth;
CString g_sLangID_Native_Ft;
CString g_sLangTxt_Native_Ft;
CString g_sLangID_AdjFreqCycle;
CString g_sLangTxt_AdjFreqCycle;
CString g_sLangID_AdjFreqWidth;
CString g_sLangTxt_AdjFreqWidth;
CString g_sLangID_Native_System;
CString g_sLangTxt_Native_System; // 系统
CString g_sLangID_waitgrid_connection;
CString g_sLangTxt_waitgrid_connection; // 待并




CString g_sLangID_expression_error;
CString g_sLangTxt_expression_error; // 表达式输出错误

CString g_sLangID_Out4_Time;
CString g_sLangTxt_Out4_Time; // 开出4保持时间（s）
CString g_sLangID_protectexport_sign;
CString g_sLangTxt_protectexport_sign; // 保护出口信号
CString g_sLangID_boost_sign;
CString g_sLangTxt_boost_sign; // 增压信号
CString g_sLangID_reduce_sign;
CString g_sLangTxt_reduce_sign; // 减压信号
CString g_sLangID_speed_sign;
CString g_sLangTxt_speed_sign; // 增速信号
CString g_sLangID_slow_sign;
CString g_sLangTxt_slow_sign; // 减速信号
CString g_sLangID_pulse;
CString g_sLangTxt_pulse; // 脉冲
CString g_sLangID_continue;
CString g_sLangTxt_continue; // 连续
CString g_sLangID_value;
CString g_sLangTxt_value; // 值
// 吕
CString g_sLangID_lowfreqloadre_tempfile;
CString g_sLangTxt_lowfreqloadre_tempfile; // 低周减载模板文件
CString g_sLangID_wel_lowfreqloadre;
CString g_sLangTxt_wel_lowfreqloadre; // 欢迎使用低周减载
CString g_sLangID_Ponovo_lowfreqloadre;
CString g_sLangTxt_Ponovo_lowfreqloadre; // Ponovo 低周减载
CString g_sLangID_lowfreqloadre;
CString g_sLangTxt_lowfreqloadre; // 低周减载
CString g_sLangID_Noselect_testitems;
CString g_sLangTxt_Noselect_testitems; // 没有选择测试项
CString g_sLangID_Atleast1_5testitems;
CString g_sLangTxt_Atleast1_5testitems; // 5种测试类型至少各保留一个测试项！
CString g_sLangID_Atleast1_Thistestitems;
CString g_sLangTxt_Atleast1_Thistestitems; // 此测试类型至少保留一个测试项！
CString g_sLangID_Native_FreAction;
CString g_sLangTxt_Native_FreAction; // 动作频率
CString g_sLangID_Native_sliptrip;
CString g_sLangTxt_Native_sliptrip; // 滑差闭锁

CString g_sLangID_interlock_volselection;
CString g_sLangTxt_interlock_volselection; // 闭锁电压选择
CString g_sLangID_FreAValue_Test;
CString g_sLangTxt_FreAValue_Test; // 频率动作值测试
CString g_sLangID_Native_sliptripTest;
CString g_sLangTxt_Native_sliptripTest; // 滑差闭锁值测试

CString g_sLangID_lowcur_lockout_test;
CString g_sLangTxt_lowcur_lockout_test; // 低电流闭锁值测试
CString g_sLangID_Native_LowVoltLock_test;
CString g_sLangTxt_Native_LowVoltLock_test; // 低电压闭锁值测试
CString g_sLangID_lowfreqloadre_Setting;
CString g_sLangTxt_lowfreqloadre_Setting; // 低周减载动作值

CString g_sLangID_lowcur_lockout;
CString g_sLangTxt_lowcur_lockout; // 低电流闭锁值
// CString g_sLangID_Voltage;
// CString g_sLangTxt_Voltage; // 电压（V）
CString g_sLangID_lowVoltage;
CString g_sLangTxt_lowVoltage; // 低压
CString g_sLangID_Negative_SeqVolU2;
CString g_sLangTxt_Negative_SeqVolU2; // 负序电压(U2)
CString g_sLangID_Zero_SeqCur3U0;
CString g_sLangTxt_Zero_SeqCur3U0; // 零序电压(3U0)
CString g_sLangID_Illegal_testitem;
CString g_sLangTxt_Illegal_testitem; // 测试项类型非法.
CString g_sLangID_Native_OutOf_Range;
CString g_sLangTxt_Native_OutOf_Range; // 超出变化范围
CString g_sLangID_action_freqvalue;
CString g_sLangTxt_action_freqvalue; // 动作频率值

// LowUTest_Trans 马
/*tr("低压减载试验模板文件")*/
CString g_sLangID_Native_LVLoadRedTemp;
CString g_sLangTxt_Native_LVLoadRedTemp;
/*_T("欢迎使用低压减载试验.")*/
CString g_sLangID_Native_WLULVLRTest;
CString g_sLangTxt_Native_WLULVLRTest;
/*tr("Ponovo 低压减载")*/
CString g_sLangID_Native_PLVLRTitle;
CString g_sLangTxt_Native_PLVLRTitle;
/*tr("低压减载")*/
CString g_sLangID_Native_LowVLoadRed;
CString g_sLangTxt_Native_LowVLoadRed;



/*tr("至少保留一个测试项!")*/
CString g_sLangID_Native_KeepOneTest;
CString g_sLangTxt_Native_KeepOneTest;

/*QObject::tr("程序已经在运行！")*/
CString g_sLangID_Native_ProgRunning;
CString g_sLangTxt_Native_ProgRunning;
/*"<h1>低压减载测试</h1>"*/
CString g_sLangID_Native_LVLRTesting;
CString g_sLangTxt_Native_LVLRTesting;
/*tr("低电压闭锁值")*/
CString g_sLangID_Native_LowVoltLock;
CString g_sLangTxt_Native_LowVoltLock;
// /*tr("动作时间=%1s")*/
// CString g_sLangID_Native_ActTimeSym;
// CString g_sLangTxt_Native_ActTimeSym;
/*tr("电压滑差闭锁值")*/
CString g_sLangID_Native_VoltSlipLock;
CString g_sLangTxt_Native_VoltSlipLock;
/*tr("相电压变化步长(V):")*/
CString g_sLangID_Native_PhaseVoltStepV;
CString g_sLangTxt_Native_PhaseVoltStepV;
/*tr("相电压变化起始值(V):")*/
CString g_sLangID_Native_PhaseVoltStartV;
CString g_sLangTxt_Native_PhaseVoltStartV;
/*tr("相电压变化结束值(V):")*/
CString g_sLangID_Native_PhaseVoltEndV;
CString g_sLangTxt_Native_PhaseVoltEndV;
/*tr("线电压变化步长(V):")*/
CString g_sLangID_Native_LineVoltStepV;
CString g_sLangTxt_Native_LineVoltStepV;
/*tr("线电压变化起始值(V):")*/
CString g_sLangID_Native_LineVoltStartV;
CString g_sLangTxt_Native_LineVoltStartV;
/*tr("线电压变化结束值(V):")*/
CString g_sLangID_Native_LineVoltEndV;
CString g_sLangTxt_Native_LineVoltEndV;
/*tr("相电压变化始值(V):")*/
CString g_sLangID_Native_PhaseVoltBeginV;
CString g_sLangTxt_Native_PhaseVoltBeginV;
/*tr("相电压变化终值(V):")*/
CString g_sLangID_Native_PhaseVoltFinal;
CString g_sLangTxt_Native_PhaseVoltFinal;
/*tr("线电压变化终值(V):")*/
CString g_sLangID_Native_LineVoltFinal;
CString g_sLangTxt_Native_LineVoltFinal;
/*tr("相电压滑差变化步长(V/s):")*/
CString g_sLangID_Native_PhaseVSlipStep;
CString g_sLangTxt_Native_PhaseVSlipStep;
/*tr("线电压滑差变化步长(V/s):")*/
CString g_sLangID_Native_LineVSlipStep;
CString g_sLangTxt_Native_LineVSlipStep;
/*tr("相电压滑差变化始值(V/s):")*/
CString g_sLangID_Native_PhaseVSlipStart;
CString g_sLangTxt_Native_PhaseVSlipStart;
/*tr("线电压滑差变化始值(V/s):")*/
CString g_sLangID_Native_LineVSlipStart;
CString g_sLangTxt_Native_LineVSlipStart;
/*tr("相电压滑差变化终值(V/s):")*/
CString g_sLangID_Native_PhaseVSlipEnd;
CString g_sLangTxt_Native_PhaseVSlipEnd;
/*tr("线电压滑差变化终值(V/s):")*/
CString g_sLangID_Native_LineVSlipEnd;
CString g_sLangTxt_Native_LineVSlipEnd;
/*_T("表达式输入错误")*/
CString g_sLangID_Native_ExprInputErr;
CString g_sLangTxt_Native_ExprInputErr;
/*_T("超出范围")*/
CString g_sLangID_Native_OutOfRange;
CString g_sLangTxt_Native_OutOfRange;
/*_T("递变步数超过60，请重新输入！")*/
CString g_sLangID_Native_VarStepExceed60P;
CString g_sLangTxt_Native_VarStepExceed60P;
// 稳态时间(s):
CString g_sLangID_Native_SteadyStateTime;
CString g_sLangTxt_Native_SteadyStateTime;



// PowerDirectionTest_Trans 马
/*tr("功率方向试验模板文件")*/
CString g_sLangID_Native_PowerDirTemp;
CString g_sLangTxt_Native_PowerDirTemp;
/*_T("欢迎使用功率方向.")*/
CString g_sLangID_Native_WelcomePD;
CString g_sLangTxt_Native_WelcomePD;
/*_T("获取实时数据绝对时间失败.")*/
CString g_sLangID_Native_GetRealTimeFail;
CString g_sLangTxt_Native_GetRealTimeFail;
/*_T("获取实时数据相对时间失败.")*/
CString g_sLangID_Native_GetRelTimeFail;
CString g_sLangTxt_Native_GetRelTimeFail;
/*tr("Ponovo 功率方向")*/
CString g_sLangID_Native_PonovoPower;
CString g_sLangTxt_Native_PonovoPower;
/*tr("功率方向")*/
CString g_sLangID_Native_PowerDir;
CString g_sLangTxt_Native_PowerDir;

/*tr("评估")*/
CString g_sLangID_Native_Assessment;
CString g_sLangTxt_Native_Assessment;
/*"<h1>功率方向测试</h1>"*/
CString g_sLangID_Native_PowerDirTest;
CString g_sLangTxt_Native_PowerDirTest;
/*"A相测试"*/
CString g_sLangID_Native_PhaseATest;
CString g_sLangTxt_Native_PhaseATest;
/*"B相测试"*/
CString g_sLangID_Native_PhaseBTest;
CString g_sLangTxt_Native_PhaseBTest;
/*"C相测试"*/
CString g_sLangID_Native_PhaseCTest;
CString g_sLangTxt_Native_PhaseCTest;
/*"零序测试"*/
CString g_sLangID_Native_PhaseZeroTest;
CString g_sLangTxt_Native_PhaseZeroTest;
/*"负序测试"*/
CString g_sLangID_Native_PhaseLossTest;
CString g_sLangTxt_Native_PhaseLossTest;
/*tr("电压超前电流为正角度")*/
CString g_sLangID_Native_VoltAheadPosAng;
CString g_sLangTxt_Native_VoltAheadPosAng;
/*tr("电流超前电压为正角度")*/
CString g_sLangID_Native_CurrAheadPosAng;
CString g_sLangTxt_Native_CurrAheadPosAng;
/*tr("0度接线")*/
CString g_sLangID_Native_Deg0Conn;
CString g_sLangTxt_Native_Deg0Conn;
/*tr("90度接线")*/
CString g_sLangID_Native_Deg90Conn;
CString g_sLangTxt_Native_Deg90Conn;
/*QObject::tr("通用参数设置")*/
CString g_sLangID_Native_GenParamSet;
CString g_sLangTxt_Native_GenParamSet;

// PowerFreqTest_Trans 马
/*tr("工频变化量距离试验模板文件")*/
CString g_sLangID_Native_FreqChgDistTemp;
CString g_sLangTxt_Native_FreqChgDistTemp;
/*_T("欢迎使用工频变化量距离试验.")*/
CString g_sLangID_Native_WelcFreqChgTest;
CString g_sLangTxt_Native_WelcFreqChgTest;
/*tr("Ponovo 工频变化量距离试验")*/
CString g_sLangID_Native_PonovoFreqChgDist;
CString g_sLangTxt_Native_PonovoFreqChgDist;
/*tr("工频变化量距离")*/
CString g_sLangID_Native_FreqChgDistance;
CString g_sLangTxt_Native_FreqChgDistance;
/*tr("阻抗特性图")*/
CString g_sLangID_Native_ImpedChart;
CString g_sLangTxt_Native_ImpedChart;


/*QObject::tr("A相接地,")*/
CString g_sLangID_Native_PhaseAGround;
CString g_sLangTxt_Native_PhaseAGround;
/*QObject::tr("B相接地,")*/
CString g_sLangID_Native_PhaseBGround;
CString g_sLangTxt_Native_PhaseBGround;
/*QObject::tr("C相接地,")*/
CString g_sLangID_Native_PhaseCGround;
CString g_sLangTxt_Native_PhaseCGround;
/*QObject::tr("AB短路,")*/
CString g_sLangID_Native_PhaseABShortCircuit;
CString g_sLangTxt_Native_PhaseABShortCircuit;
/*QObject::tr("BC短路,")*/
CString g_sLangID_Native_PhaseBCShortCircuit;
CString g_sLangTxt_Native_PhaseBCShortCircuit;
/*QObject::tr("CA短路,")*/
CString g_sLangID_Native_PhaseCAShortCircuit;
CString g_sLangTxt_Native_PhaseCAShortCircuit;
/*QObject::tr("瞬时,")*/
CString g_sLangID_Native_Instantaneous;
CString g_sLangTxt_Native_Instantaneous;
/*QObject::tr("永久,")*/
CString g_sLangID_Native_Permanently;
CString g_sLangTxt_Native_Permanently;
/*"<h1>工频变化量距离测试</h1>"*/
CString g_sLangID_Native_FreqChgDistTest;
CString g_sLangTxt_Native_FreqChgDistTest;
/*"工频变化量距离"*/
CString g_sLangID_Native_FreqChgDist;
CString g_sLangTxt_Native_FreqChgDist;
/*"<h3>正方向</h3>"*/
CString g_sLangID_Native_PosDirection;
CString g_sLangTxt_Native_PosDirection;
/*"<h3>反方向</h3>"*/
CString g_sLangID_Native_RevDirection;
CString g_sLangTxt_Native_RevDirection;
/*"确定取消"*/
CString g_sLangID_OKCancel;
CString g_sLangTxt_OKCancel;
/*QObject::tr("母线侧")*/
CString g_sLangID_Native_BusSide;
CString g_sLangTxt_Native_BusSide;
/*QObject::tr("线路侧")*/
CString g_sLangID_Native_LineSide;
CString g_sLangTxt_Native_LineSide;
/*QObject::tr("指向母线")*/
CString g_sLangID_Native_TowardBus;
CString g_sLangTxt_Native_TowardBus;
/*QObject::tr("指向线路")*/
CString g_sLangID_Native_TowardLine;
CString g_sLangTxt_Native_TowardLine;
/*QObject::tr("不模拟")*/
CString g_sLangID_Native_NoSimulation;
CString g_sLangTxt_Native_NoSimulation;
/*tr("反向")*/
CString g_sLangID_Native_OppositeDirection;
CString g_sLangTxt_Native_OppositeDirection;
/*tr("正向")*/
CString g_sLangID_Native_PositiveDirection;
CString g_sLangTxt_Native_PositiveDirection;
/*tr("瞬时")*/
CString g_sLangID_Native_Immediate;
CString g_sLangTxt_Native_Immediate;
/*tr("永久")*/
CString g_sLangID_Native_Permanent;
CString g_sLangTxt_Native_Permanent;
/*tr("跳三相=%1s,")*/
CString g_sLangID_Native_Trip3Phase;
CString g_sLangTxt_Native_Trip3Phase;
/*tr("跳A=%1s,")*/
CString g_sLangID_Native_TripPhaseA;
CString g_sLangTxt_Native_TripPhaseA;
/*tr("跳B=%1s,")*/
CString g_sLangID_Native_TripPhaseB;
CString g_sLangTxt_Native_TripPhaseB;
/*tr("跳C=%1s,")*/
CString g_sLangID_Native_TripPhaseC;
CString g_sLangTxt_Native_TripPhaseC;
/*tr("重合闸=%1s,")*/
CString g_sLangID_Native_ReclosingSy;
CString g_sLangTxt_Native_ReclosingSy;
/*tr("后加速=%1s,")*/
CString g_sLangID_Native_PostAccel;
CString g_sLangTxt_Native_PostAccel;
/*tr("返回时间=%1s,")*/
CString g_sLangID_Native_TimeofReturn;
CString g_sLangTxt_Native_TimeofReturn;
/*tr("返回时间A=%1s,")*/
CString g_sLangID_Native_TimeofReturnA;
CString g_sLangTxt_Native_TimeofReturnA;
/*tr("返回时间B=%1s,")*/
CString g_sLangID_Native_TimeofReturnB;
CString g_sLangTxt_Native_TimeofReturnB;
/*tr("返回时间C=%1s,")*/
CString g_sLangID_Native_TimeofReturnC;
CString g_sLangTxt_Native_TimeofReturnC;
/*tr("返回时间D=%1s,")*/
CString g_sLangID_Native_TimeofReturnD;
CString g_sLangTxt_Native_TimeofReturnD;
// TV安装位置
CString g_sLangID_Native_TVInstLoc;
CString g_sLangTxt_Native_TVInstLoc;
// TA正极性
CString g_sLangID_Native_PosPolTA;
CString g_sLangTxt_Native_PosPolTA;
// 断路器模拟
CString g_sLangID_Native_CBsim;
CString g_sLangTxt_Native_CBsim;
// 分闸时间
CString g_sLangID_Native_TripTime;
CString g_sLangTxt_Native_TripTime;
// 合闸时间
CString g_sLangID_Native_CloseTime;
CString g_sLangTxt_Native_CloseTime;
// 阻抗特性
CString g_sLangID_Native_ImpChar;
CString g_sLangTxt_Native_ImpChar;


// start XWD
CString g_sLangID_Native_RLPtestTF;			 //=_T("Native_RLPtestTF");
CString g_sLangTxt_Native_RLPtestTF;		 //=_T("复压闭锁保护试验模板文件");
CString g_sLangID_Native_WelUseRLPT;		 //=_T("Native_WelUseRLPT");
CString g_sLangTxt_Native_WelUseRLPT;		 //=_T("欢迎使用复压闭锁保护试验");
CString g_sLangID_Native_AbsoluteTimeF;		 //=_T("Native_AbsoluteTimeF");
CString g_sLangTxt_Native_AbsoluteTimeF;	 //=_T("获取实时数据绝对时间失败");
CString g_sLangID_Native_RelativeTimeF;		 //=_T("Native_RelativeTimeF");
CString g_sLangTxt_Native_RelativeTimeF;	 //=_T("获取实时数据相对时间失败");
CString g_sLangID_Native_PonovoRLO;			 //=_T("Native_PonovoRLO");
CString g_sLangTxt_Native_PonovoRLO;		 //=_T("Ponovo复压闭锁");
CString g_sLangID_Native_RLOtest;			 //=_T("Native_RLOtest");
CString g_sLangTxt_Native_RLOtest;			 //=_T("复压闭锁实验");
CString g_sLangID_Native_LowVoltage;		 //=_T("Native_LowVoltage");
CString g_sLangTxt_Native_LowVoltage;		 //=_T("低电压");
CString g_sLangID_Native_NegSeqVol;			 //=_T("Native_NegSeqVol");
CString g_sLangTxt_Native_NegSeqVol;		 //=_T("负序电压");
CString g_sLangID_Native_ActCurrent;		 //=_T("Native_ActCurrent");
CString g_sLangTxt_Native_ActCurrent;		 //=_T("动作电流");
CString g_sLangID_Native_ActAreaSize;		 //=_T("Native_ActAreaSize");
CString g_sLangTxt_Native_ActAreaSize;		 //=_T("动作区大小");

CString g_sLangID_Native_LowVolTriVal;		 //=_T("Native_LowVolTriVal");
CString g_sLangTxt_Native_LowVolTriVal;		 //=_T("低电压动作值");
CString g_sLangID_Native_NegSeqVolTriVal;	 //=_T("Native_NegSeqVolTriVal");
CString g_sLangTxt_Native_NegSeqVolTriVal;	 //=_T("负序电压动作值");
CString g_sLangID_Native_CurOperC;			 //=_T("Native_CurOperC");
CString g_sLangTxt_Native_CurOperC;			 //=_T("电流动作值（C相）");
CString g_sLangID_Native_CurOperB;			 //=_T("Native_CurOperB");
CString g_sLangTxt_Native_CurOperB;			 //=_T("电流动作值（B相）");
CString g_sLangID_Native_CurOperA;			 //=_T("Native_CurOperA");
CString g_sLangTxt_Native_CurOperA;			 //=_T("电流动作值（A相）");
CString g_sLangID_Native_MaxSensAngTest;	 //=_T("Native_MaxSensAngTest");
CString g_sLangTxt_Native_MaxSensAngTest;	 //=_T("最大灵敏角测试");
CString g_sLangID_Native_CurOperVal;		 //=_T("Native_CurOperVal");
CString g_sLangTxt_Native_CurOperVal;		 //=_T("电流动作值");
CString g_sLangID_Native_AnBShortCir;		 //=_T("Native_AnBShortCir");
CString g_sLangTxt_Native_AnBShortCir;		 //=_T("AB相短路");
CString g_sLangID_Native_BnCShortCir;		 //=_T("Native_BncShortCir");
CString g_sLangTxt_Native_BnCShortCir;		 //=_T("BC相短路");
CString g_sLangID_Native_CnAShortCir;		 //=_T("Native_CnAShortCir");
CString g_sLangTxt_Native_CnAShortCir;		 //=_T("CA相短路");
CString g_sLangID_Native_ShortBCVolAndACur;	 //=_T("Native_BCSCVolAndACur");
CString g_sLangTxt_Native_ShortBCVolAndACur; //=_T("BC相短路电压 A相电流");
CString g_sLangID_Native_ShortCAVolAndBCur;	 //=_T("Native_CASCVolAndBCur");
CString g_sLangTxt_Native_ShortCAVolAndBCur; //=_T("CA相短路电压 B相电流");
CString g_sLangID_Native_ShortABVolAndCCur;	 //=_T("Native_ABSCVolAndCCur");
CString g_sLangTxt_Native_ShortABVolAndCCur; //=_T("AB相短路电压 C相电流");
CString g_sLangID_Native_ABCSC;				 //=_T("Native_ABCSC");
CString g_sLangTxt_Native_ABCSC;			 //=_T("ABC短路");
CString g_sLangID_Native_RLOTestAno;		 //=_T("Native_RLOTestAno");
CString g_sLangTxt_Native_RLOTestAno;		 //=_T("<h1>复压闭锁测试</h1>");
CString g_sLangID_Native_BoundaryAngle;		 //=_T("Native_BoundaryAngle");
CString g_sLangTxt_Native_BoundaryAngle;	 //=_T("边界角");

CString g_sLangID_Native_ImpedanceAngle;  //=_T("Native_ImpedanceAngle");
CString g_sLangTxt_Native_ImpedanceAngle; //=_T("阻抗角(°)：");
CString g_sLangID_Native_InitofVarV;	  //=_T("Native_InitofVarV");
CString g_sLangTxt_Native_InitofVarV;	  //=_T("变化始值(V)：");
CString g_sLangID_Native_FinalofVarV;	  //=_T("Native_FinalofVarV");
CString g_sLangTxt_Native_FinalofVarV;	  //=_T("变化终值(V)：");
CString g_sLangID_Native_StepofVarV;	  //=_T("Native_StepofVarV");
CString g_sLangTxt_Native_StepofVarV;	  //=_T("变化步长(V)：");
CString g_sLangID_Native_InitofVarA;	  //=_T("Native_InitofVarA");
CString g_sLangTxt_Native_InitofVarA;	  //=_T("变化始值(A)：");
CString g_sLangID_Native_FinalofVarA;	  //=_T("Native_FinalofVarA");
CString g_sLangTxt_Native_FinalofVarA;	  //=_T("变化终值(A)：");
CString g_sLangID_Native_StepofVarA;	  //=_T("Native_StepofVarA");
CString g_sLangTxt_Native_StepofVarA;	  //=_T("变化步长(A)：");

CString g_sLangID_Native_ZeroSeqTF;			//=_T("Native_ZeroSeqTF");
CString g_sLangTxt_Native_ZeroSeqTF;		//=_T("零序保护试验模板文件");
CString g_sLangID_Native_WelUseZeroSeq;		//=_T("Native_WelUseZeroSeq");
CString g_sLangTxt_Native_WelUseZeroSeq;	//=_T("欢迎使用零序保护试验");
CString g_sLangID_Native_PonovoZS;			//=_T("Native_PonovoZS");
CString g_sLangTxt_Native_PonovoZS;			//=_T("Ponovo 零序保护试验");
CString g_sLangID_Native_ZeroSeqTest;		//=_T("Native_ZeroSeqTest");
CString g_sLangTxt_Native_ZeroSeqTest;		//=_T("零序试验");
CString g_sLangID_Native_ZeroSeqStageI;		//=_T("Native_ZeroSeqStageI");
CString g_sLangTxt_Native_ZeroSeqStageI;	//=_T("零序I段");
CString g_sLangID_Native_ZeroSeqStageII;	//=_T("Native_ZeroSeqStageII");
CString g_sLangTxt_Native_ZeroSeqStageII;	//=_T("零序II段");
CString g_sLangID_Native_ZeroSeqStageIII;	//=_T("Native_ZeroSeqStageIII");
CString g_sLangTxt_Native_ZeroSeqStageIII;	//=_T("零序III段");
CString g_sLangID_Native_ZeroSeqStageIV;	//=_T("Native_ZeroSeqStageIV");
CString g_sLangTxt_Native_ZeroSeqStageIV;	//=_T("零序IV段");
CString g_sLangID_Native_ZeroSeqStageV;		//=_T("Native_ZeroSeqStageV");
CString g_sLangTxt_Native_ZeroSeqStageV;	//=_T("零序V段");
CString g_sLangID_Native_ZeroSeqWrH;		//=_T("Native_ZeroSeqWrH");
CString g_sLangTxt_Native_ZeroSeqWrH;		//=_T("开关量设置中，开入H没有设置成重合闸，软件已经自动把该项设置成重合闸");
CString g_sLangID_Native_ZeroSeqWrD;		//=_T("Native_ZeroSeqWrD");
CString g_sLangTxt_Native_ZeroSeqWrD;		//=_T("开关量设置中，开入D没有设置成重合闸，软件已经自动把该项设置成重合闸");
CString g_sLangID_Native_ZeroSeqWrDH;		//=_T("Native_ZeroSeqWrDH");
CString g_sLangTxt_Native_ZeroSeqWrDH;		//=_T("开关量设置中，开入D、开入H没有设置成重合闸，软件已经自动把该项设置成重合闸");
CString g_sLangID_Native_TestOFZeroSeq;		//=_T("Native_TestOFZeroSeq");
CString g_sLangTxt_Native_TestOFZeroSeq;	//=_T("<h1>试验名称：零序保护定值测试</h1>");
CString g_sLangID_Native_TestofProSet;		//=_T("Native_TestofProSet");
CString g_sLangTxt_Native_TestofProSet;		//=_T("保护定值测试");
CString g_sLangID_Native_ThrPhaseJump;		//=_T("Native_ThrPhaseJump");
CString g_sLangTxt_Native_ThrPhaseJump;		//=_T("跳三相=%1s");
CString g_sLangID_Native_Reclosing;			//=_T("Native_Reclosing");
CString g_sLangTxt_Native_Reclosing;		//=_T("重合闸");
CString g_sLangID_Native_PostAcceleration;	//=_T("Native_PostAcceleration");
CString g_sLangTxt_Native_PostAcceleration; //=_T("后加速");

CString g_sLangID_Native_UnitProTF;		  //=_T("Native_UnitProTF");
CString g_sLangTxt_Native_UnitProTF;	  //=_T("整组保护试验模板文件");
CString g_sLangID_Native_PonovoGroupTra;  //=_T("Native_PonovoGroupTra");
CString g_sLangTxt_Native_PonovoGroupTra; //=_T("Ponovo整组传动");
CString g_sLangID_Native_WelUseGroTra;	  //=_T("Native_WelUseGroTra");
CString g_sLangTxt_Native_WelUseGroTra;	  //=_T("欢迎使用整组传动");
CString g_sLangID_Native_GroupTra;		  //=_T("Native_GroupTra");
CString g_sLangTxt_Native_GroupTra;		  //=_T("整组传动");
CString g_sLangID_Native_ImpAng;		  //=_T("Native_ImpAng");
CString g_sLangTxt_Native_ImpAng;		  //=_T("阻抗角(°)");
CString g_sLangID_Native_NameGroTest;	  //=_T("Native_NameGroTest");
CString g_sLangTxt_Native_NameGroTest;	  //=_T("试验名称：整组试验");
CString g_sLangID_Native_TestPara;		  //=_T("Native_TestPara");
CString g_sLangTxt_Native_TestPara;		  //=_T("试验参数");
CString g_sLangID_Native_Initial;		  //=_T("Native_Initial");
CString g_sLangTxt_Native_Initial;		  //=_T("初始");
CString g_sLangID_Native_Selected;		  //=_T("Native_Selected");
CString g_sLangTxt_Native_Selected;		  //=_T("选中");
CString g_sLangID_Native_EndTest;		  //=_T("Native_EndTest");
CString g_sLangTxt_Native_EndTest;		  //=_T("试验结束");

CString g_sLangID_Native_TransientTime;		//=_T("Native_TransientTime");
CString g_sLangTxt_Native_TransientTime;	//=_T("转换时间");
CString g_sLangID_Native_TransientMalfDir;	//=_T("Native_TransientMalfDir");
CString g_sLangTxt_Native_TransientMalfDir; //=_T("转换故障方向");

CString g_sLangID_Native_RPAProTestTF;	 //=_T("Native_RPAProTestTF");
CString g_sLangTxt_Native_RPAProTestTF;	 //=_T("重合闸及后加速保护试验模板文件");
CString g_sLangID_Native_RPAWro1;		 //=_T("Native_RPAWro1");
CString g_sLangTxt_Native_RPAWro1;		 //=_T("故障-|Z|(Ω)表达式异常！");
CString g_sLangID_Native_RPAWro2;		 //=_T("Native_RPAWro2");
CString g_sLangTxt_Native_RPAWro2;		 //=_T("故障-阻抗角表达式异常！");
CString g_sLangID_Native_RPAWro3;		 //=_T("Native_RPAWro3");
CString g_sLangTxt_Native_RPAWro3;		 //=_T("重合后-|Z|(Ω)表达式异常！");
CString g_sLangID_Native_RPAWro4;		 //=_T("Native_RPAWro4");
CString g_sLangTxt_Native_RPAWro4;		 //=_T("跳闸后抽取电压相位表达式异常！");
CString g_sLangID_Native_RPAWro5;		 //=_T("Native_RPAWro5");
CString g_sLangTxt_Native_RPAWro5;		 //=_T("跳闸后抽取电压表达式异常！");
CString g_sLangID_Native_RPATest;		 //=_T("Native_RPATest");
CString g_sLangTxt_Native_RPATest;		 //=_T("重合闸及后加速试验");
CString g_sLangID_Native_WelUseRPATest;	 //=_T("Native_WelUseRPATest");
CString g_sLangTxt_Native_WelUseRPATest; //=_T("欢迎使用重合闸及后加速试验.");

CString g_sLangID_Native_RCTimeLim;		  //=_T("Native_RCTimeLim");
CString g_sLangTxt_Native_RCTimeLim;	  //=_T("重合闸时限");
CString g_sLangID_Native_ZeroVolThr;	  //=_T("Native_ZeroVolThr");
CString g_sLangTxt_Native_ZeroVolThr;	  //=_T("检无压定值");
CString g_sLangID_Native_VolDetThr;		  //=_T("Native_VolDetThr");
CString g_sLangTxt_Native_VolDetThr;	  //=_T("检有压定值");
CString g_sLangID_Native_SynAngDet;		  //=_T("Native_SynAngDet");
CString g_sLangTxt_Native_SynAngDet;	  //=_T("检同期角度");
CString g_sLangID_Native_CalZeroSeq;	  //=_T("Native_CalZeroSeq");
CString g_sLangTxt_Native_CalZeroSeq;	  //=_T("零序补偿计算方式");
CString g_sLangID_Native_ChinOr;		  //=_T("Native_ChinOr");
CString g_sLangTxt_Native_ChinOr;		  //=_T("中文或");
CString g_sLangID_Native_TestRPA;		  //=_T("Native_TestRPA");
CString g_sLangTxt_Native_TestRPA;		  //=_T("重合闸及后加速测试");
CString g_sLangID_Native_PermanentFau;	  //=_T("Native_PermanentFau");
CString g_sLangTxt_Native_PermanentFau;	  //=_T("故障性质-永久性故障");
CString g_sLangID_Native_TransientFau;	  //=_T("Native_TransientFau");
CString g_sLangTxt_Native_TransientFau;	  //=_T("故障性质-瞬时性故障");
CString g_sLangID_Native_MustCho;		  //=_T("Native_MustCho");
CString g_sLangTxt_Native_MustCho;		  //=_T("请务必选择故障类型！");
CString g_sLangID_Native_SyncCheck;		  //=_T("Native_SyncCheck");
CString g_sLangTxt_Native_SyncCheck;	  //=_T("检同期");
CString g_sLangID_Native_LineNoVolParD;	  //=_T("Native_LineNoVolParD");
CString g_sLangTxt_Native_LineNoVolParD;  //=_T("检线无压母有压");
CString g_sLangID_Native_LineHasVolParN;  //=_T("Native_LineHasVolParN");
CString g_sLangTxt_Native_LineHasVolParN; //=_T("检线有压母无压");
CString g_sLangID_Native_LineNoVolParT;	  //=_T("Native_LineNoVolParT");
CString g_sLangTxt_Native_LineNoVolParT;  //=_T("检线无压母无压");
CString g_sLangID_Native_LineHasVolParT;  //=_T("Native_LineHasVolParT");
CString g_sLangTxt_Native_LineHasVolParT; //=_T("检线有压母有压");
CString g_sLangID_Native_NoOutput;		  //=_T("Native_NoOutput");
CString g_sLangTxt_Native_NoOutput;		  //=_T("无输出");
CString g_sLangID_Native_KOorReKO;		  //=_T("Native_KOorReKO");
CString g_sLangTxt_Native_KOorReKO;		  //=_T("|K0|或Re(K0)");
CString g_sLangID_Native_PhiOrIm;		  //=_T("Native_PhiOrIm");
CString g_sLangTxt_Native_PhiOrIm;		  //=_T("Phi(K0)或Im(K0)");

// 许文迪第二周
CString g_sLangID_Native_FaultReplayTF;		//=_T("Native_FaultReplayTF");
CString g_sLangTxt_Native_FaultReplayTF;	//=_T("故障回放试验模板文件");
CString g_sLangID_Native_EnfSetAnalog;		//=_T("Native_EnfSetAnalog");
CString g_sLangTxt_Native_EnfSetAnalog;		//=_T("当前模块只支持模拟量故障回放,强制设置为模拟量输出模式.");
CString g_sLangID_Native_WelUseFaultRe;		//=_T("Native_WelUseFaultRe");
CString g_sLangTxt_Native_WelUseFaultRe;	//=_T("欢迎使用故障回放试验.");
CString g_sLangID_Native_WavePlayback;		//=_T("Native_WavePlayback");
CString g_sLangTxt_Native_WavePlayback;		//=_T("波形回放");
CString g_sLangID_Native_PreWaveData;		//=_T("Native_PreWaveData");
CString g_sLangTxt_Native_PreWaveData;		//=_T("切换到上一页波形数据");
CString g_sLangID_Native_NextWaveData;		//=_T("Native_NextWaveData");
CString g_sLangTxt_Native_NextWaveData;		//=_T("切换到下一页波形数据");
CString g_sLangID_Native_MalfunctionRe;		//=_T("Native_MalfunctionRe");
CString g_sLangTxt_Native_MalfunctionRe;	//=_T("故障回放");
CString g_sLangID_Native_OpenWaveFile;		//=_T("Native_OpenWaveFile");
CString g_sLangTxt_Native_OpenWaveFile;		//=_T("请打开录波文件");
CString g_sLangID_Native_DownloadWaveData;	//=_T("Native_DownloadWaveData");
CString g_sLangTxt_Native_DownloadWaveData; //=_T("正在下载波形数据...");
CString g_sLangID_Native_FaultReplayWr3;	//=_T("Native_FaultReplayWr3");
CString g_sLangTxt_Native_FaultReplayWr3;	//=_T("当前电压通道回放的最大电压值(%lf),大于测试仪最大输出电压(%f).");
CString g_sLangID_Native_FaultReplayWr4;	//=_T("Native_FaultReplayWr4");
CString g_sLangTxt_Native_FaultReplayWr4;	//=_T("当前电流通道回放的最大电流值(%lf),大于测试仪最大输出电流(%f).");
CString g_sLangID_Native_TransfRatio;		//=_T("Native_TransfRatio");
CString g_sLangTxt_Native_TransfRatio;		//=_T("变比");
CString g_sLangID_Native_AChannelDesError;	//=_T("Native_AChannelDesError");
CString g_sLangTxt_Native_AChannelDesError; //=_T("A通道描述查找出错(%s)(%ld).");
CString g_sLangID_Native_BChannelDesError;	//=_T("Native_BChannelDesError");
CString g_sLangTxt_Native_BChannelDesError; //=_T("B通道描述查找出错(%s)(%ld).");

CString g_sLangID_Native_SITmpl;			   // = _T("Native_SITmpl")
CString g_sLangTxt_Native_SITmpl;			   // = _T("搜索阻抗边界试验模板文件")
CString g_sLangID_Native_SIWelcome;			   // = _T("Native_SIWelcome")
CString g_sLangTxt_Native_SIWelcome;		   // = _T("欢迎使用搜索阻抗边界试验")
CString g_sLangID_Native_SIPonovo;			   // = _T("Native_SIPonovo")
CString g_sLangTxt_Native_SIPonovo;			   // = _T("Ponovo 搜索阻抗边界")
CString g_sLangID_Native_SITest;			   // = _T("Native_SITest")
CString g_sLangTxt_Native_SITest;			   // = _T("搜索阻抗边界试验")
CString g_sLangID_Native_SISearch;			   // = _T("Native_SISearch")
CString g_sLangTxt_Native_SISearch;			   // = _T("搜索阻抗边界")
CString g_sLangID_Native_ConfigFileNotExist;   // = _T("Native_ConfigFileNotExist")
CString g_sLangTxt_Native_ConfigFileNotExist;  // = _T("配置文件：%s 不存在")
CString g_sLangID_Native_SelectFaultType;	   // = _T("Native_SelectFaultType")
CString g_sLangTxt_Native_SelectFaultType;	   // = _T("请选择故障类型")
CString g_sLangID_Native_ImpedanceAngleStart;  // = _T("Native_ImpedanceAngleStart")
CString g_sLangTxt_Native_ImpedanceAngleStart; // = _T("阻抗角始值")
CString g_sLangID_Native_ImpedanceAngleEnd;	   // = _T("Native_ImpedanceAngleEnd")
CString g_sLangTxt_Native_ImpedanceAngleEnd;   // = _T("阻抗角终值")
CString g_sLangID_Native_AngleChangeStep;	   // = _T("Native_AngleChangeStep")
CString g_sLangTxt_Native_AngleChangeStep;	   // = _T("角度改变步长")
CString g_sLangID_Native_WelcomeSeq;		   // = _T("Native_WelcomeSeq")
CString g_sLangTxt_Native_WelcomeSeq;		   // = _T("欢迎使用状态序列")
CString g_sLangID_Native_StateSeq;			   // = _T("Native_StateSeq")
CString g_sLangTxt_Native_StateSeq;			   // = _T("状态序列")

CString g_sLangID_Native_StateSeqStatus;		  // = _T("Native_StateSeqStatus")
CString g_sLangTxt_Native_StateSeqStatus;		  // = _T("次状态序列状态")
CString g_sLangID_Native_SelectedStateNumExceed;  // = _T("Native_SelectedStateNumExceed")
CString g_sLangTxt_Native_SelectedStateNumExceed; // = _T("已选择状态数超过最大值")

CString g_sLangID_Native_Exit;		 // = _T("Native_Exit")
CString g_sLangTxt_Native_Exit;		 // = _T("出口")
CString g_sLangID_Native_TrigTimeS;	 // = _T("Native_TrigTimeS")
CString g_sLangTxt_Native_TrigTimeS; // = _T("触发时间(s)")

CString g_sLangID_Native_OutOneState;	 // = _T("Native_OutOneState")
CString g_sLangTxt_Native_OutOneState;	 // = _T("开出一状态")
CString g_sLangID_Native_OutTwoState;	 // = _T("Native_OutTwoState")
CString g_sLangTxt_Native_OutTwoState;	 // = _T("开出二状态")
CString g_sLangID_Native_OutThreeState;	 // = _T("Native_OutThreeState")
CString g_sLangTxt_Native_OutThreeState; // = _T("开出三状态")
CString g_sLangID_Native_OutFourState;	 // = _T("Native_OutFourState")
CString g_sLangTxt_Native_OutFourState;	 // = _T("开出四状态")
CString g_sLangID_Native_OutFiveState;	 // = _T("Native_OutFiveState")
CString g_sLangTxt_Native_OutFiveState;	 // = _T("开出五状态")
CString g_sLangID_Native_OutSixState;	 // = _T("Native_OutSixState")
CString g_sLangTxt_Native_OutSixState;	 // = _T("开出六状态")
CString g_sLangID_Native_OutSevenState;	 // = _T("Native_OutSevenState")
CString g_sLangTxt_Native_OutSevenState; // = _T("开出七状态")
CString g_sLangID_Native_OutEightState;	 // = _T("Native_OutEightState")
CString g_sLangTxt_Native_OutEightState; // = _T("开出八状态")
CString g_sLangID_Native_InAActTime;	 // = _T("Native_InAActTime")
CString g_sLangTxt_Native_InAActTime;	 // = _T("开入A动作时间(s)")
CString g_sLangID_Native_InBActTime;	 // = _T("Native_InBActTime")
CString g_sLangTxt_Native_InBActTime;	 // = _T("开入B动作时间(s)")
CString g_sLangID_Native_InCActTime;	 // = _T("Native_InCActTime")
CString g_sLangTxt_Native_InCActTime;	 // = _T("开入C动作时间(s)")
CString g_sLangID_Native_InDActTime;	 // = _T("Native_InDActTime")
CString g_sLangTxt_Native_InDActTime;	 // = _T("开入D动作时间(s)")
CString g_sLangID_Native_InEActTime;	 // = _T("Native_InEActTime")
CString g_sLangTxt_Native_InEActTime;	 // = _T("开入E动作时间(s)")
CString g_sLangID_Native_InFActTime;	 // = _T("Native_InFActTime")
CString g_sLangTxt_Native_InFActTime;	 // = _T("开入F动作时间(s)")
CString g_sLangID_Native_InGActTime;	 // = _T("Native_InGActTime")
CString g_sLangTxt_Native_InGActTime;	 // = _T("开入G动作时间(s)")
CString g_sLangID_Native_InHActTime;	 // = _T("Native_InHActTime")
CString g_sLangTxt_Native_InHActTime;	 // = _T("开入H动作时间(s)")

CString g_sLangID_Native_OutputState;	   // = _T("Native_OutputState")
CString g_sLangTxt_Native_OutputState;	   // = _T("开出%d状态")
CString g_sLangID_Native_UnknownTrigger;   // = _T("Native_UnkwnTrig")
CString g_sLangTxt_Native_UnknownTrigger;  // = _T("未知触发模式")
CString g_sLangID_Native_InputOutOfRange;  // = _T("Native_InputOutOfRange")
CString g_sLangTxt_Native_InputOutOfRange; // = _T("输入值%f超出范围(%f).")
CString g_sLangID_Native_TestList;		   // = _T("Native_TestList")
CString g_sLangTxt_Native_TestList;		   // = _T("试验列表")
CString g_sLangID_Native_TestResult;	   // = _T("Native_TestResult")
CString g_sLangTxt_Native_TestResult;	   // = _T("试验结果")
CString g_sLangID_Native_AddState;		   // = _T("Native_AddState")
CString g_sLangTxt_Native_AddState;		   // = _T("添加状态")
CString g_sLangID_Native_DelState;		   // = _T("Native_DelState")
CString g_sLangTxt_Native_DelState;		   // = _T("删除状态")
CString g_sLangID_Native_DelN1;			   // = _T("Native_DelN1")
CString g_sLangTxt_Native_DelN1;		   // = _T("删除N-1")
CString g_sLangID_Native_PhaseAngle;	   // = _T("Native_PhaseAngle")
CString g_sLangTxt_Native_PhaseAngle;	   // = _T("相角(°)")
CString g_sLangID_Native_SVAbnSim;		   // = _T("Native_SVAbnSim")
CString g_sLangTxt_Native_SVAbnSim;		   // = _T(" SV异常模拟")

// ManualTest_Trans 马嘉骅第二周
/*_T("欢迎使用通用试验.")*/
CString g_sLangID_Native_WelcomeGenTest;
CString g_sLangTxt_Native_WelcomeGenTest;
/*_T(" 通用试验")*/
CString g_sLangID_Native_blankGenTest;
CString g_sLangTxt_Native_blankGenTest;
/*tr("开入设置(扩展)")*/
CString g_sLangID_Native_InputSetExt;
CString g_sLangTxt_Native_InputSetExt;
/*tr("开出设置(扩展)")*/
CString g_sLangID_Native_OutputSetExt;
CString g_sLangTxt_Native_OutputSetExt;
/*tr("动作值(")*/
CString g_sLangID_Native_ActValuePar;
CString g_sLangTxt_Native_ActValuePar;
/*tr("):")*/
CString g_sLangID_Native_BrackColon;
CString g_sLangTxt_Native_BrackColon;
/*tr("返回值(")*/
CString g_sLangID_Native_ReturnValuePar;
CString g_sLangTxt_Native_ReturnValuePar;
/*tr("始值(")*/
CString g_sLangID_Native_InitialValPar;
CString g_sLangTxt_Native_InitialValPar;
/*tr("终值(")*/
CString g_sLangID_Native_EndValPar;
CString g_sLangTxt_Native_EndValPar;
/*tr("步长(")*/
CString g_sLangID_Native_StepSizePar;
CString g_sLangTxt_Native_StepSizePar;
// 开出设置及返回结果
CString g_sLangID_Native_OpenSett;
CString g_sLangTxt_Native_OpenSett;
// 直流UAB
CString g_sLangID_Native_DCUAB;
CString g_sLangTxt_Native_DCUAB;
// 辐值
CString g_sLangID_Native_RadVal;
CString g_sLangTxt_Native_RadVal;

// OscillationTest_Trans 马
/*tr("振荡试验模板文件")*/
CString g_sLangID_Native_OscilTestTemp;
CString g_sLangTxt_Native_OscilTestTemp;
/*_T("欢迎使用振荡试验.")*/
CString g_sLangID_Native_WelcomeOscTest;
CString g_sLangTxt_Native_WelcomeOscTest;
/*tr("Ponovo 振荡试验")*/
CString g_sLangID_Native_PonovoOscTest;
CString g_sLangTxt_Native_PonovoOscTest;
/*tr("振荡试验")*/
CString g_sLangID_Native_OscilTest;
CString g_sLangTxt_Native_OscilTest;

/*QObject::tr("功角振荡")*/
CString g_sLangID_Native_AngleOscil;
CString g_sLangTxt_Native_AngleOscil;
/*"振荡"*/
CString g_sLangID_Native_Oscillation;
CString g_sLangTxt_Native_Oscillation;
/*测试参数*/
CString g_sLangID_Native_TestParams;
CString g_sLangTxt_Native_TestParams;
/*功角始值(°)*/
CString g_sLangID_Native_AngleStartPar;
CString g_sLangTxt_Native_AngleStartPar;
/*功角终值(°)*/
CString g_sLangID_Native_AngleEndPar;
CString g_sLangTxt_Native_AngleEndPar;
/*振荡周期(s)*/
CString g_sLangID_Native_OscilPeriod;
CString g_sLangTxt_Native_OscilPeriod;
/*跳闸接点*/
CString g_sLangID_Native_TripContacts;
CString g_sLangTxt_Native_TripContacts;
/*振荡中再故障*/
CString g_sLangID_Native_OscilReFault;
CString g_sLangTxt_Native_OscilReFault;
/*使用阻抗滑差递变方式*/
CString g_sLangID_Native_ImpedSlipRamp;
CString g_sLangTxt_Native_ImpedSlipRamp;
/*往复振荡*/
CString g_sLangID_Native_RecipOsc;
CString g_sLangTxt_Native_RecipOsc;
/*增速振荡*/
CString g_sLangID_Native_AccelOsc;
CString g_sLangTxt_Native_AccelOsc;

/*故障发生时刻*/
CString g_sLangID_Native_FaultTime;
CString g_sLangTxt_Native_FaultTime;
/*结果名称*/
CString g_sLangID_Native_ResultName;
CString g_sLangTxt_Native_ResultName;
/*保护出口时间(s)*/
CString g_sLangID_Native_ProtRelayTime;
CString g_sLangTxt_Native_ProtRelayTime;
/*加速信号出口时间(s)*/
CString g_sLangID_Native_AccelSigOutTime;
CString g_sLangTxt_Native_AccelSigOutTime;
/*减速信号出口时间(s)*/
CString g_sLangID_Native_DecelSigOutTime;
CString g_sLangTxt_Native_DecelSigOutTime;
/*tr("保护出口时间=")*/
CString g_sLangID_Native_ProtOutTimePar;
CString g_sLangTxt_Native_ProtOutTimePar;
/*tr("加速信号时间=")*/
CString g_sLangID_Native_AccelTimePar;
CString g_sLangTxt_Native_AccelTimePar;
/*tr("减速信号时间=")*/
CString g_sLangID_Native_DecelTimePar;
CString g_sLangTxt_Native_DecelTimePar;

// 发电机暂态电抗
CString g_sLangID_Native_GenTranReact;
CString g_sLangTxt_Native_GenTranReact;

// 表达方式
CString g_sLangID_Native_ExprMethod;
CString g_sLangTxt_Native_ExprMethod;
// 增速
CString g_sLangID_Native_RateIncr;
CString g_sLangTxt_Native_RateIncr;
// 减速
CString g_sLangID_Native_Decel;
CString g_sLangTxt_Native_Decel;

// OverCurrentTest_Trans 马
/*tr("过流试验模板文件")*/
CString g_sLangID_Native_OvrCurrTestTemp;
CString g_sLangTxt_Native_OvrCurrTestTemp;
/*_T("欢迎使用过流测试.")*/
CString g_sLangID_Native_WelcomeOvrCurrTest;
CString g_sLangTxt_Native_WelcomeOvrCurrTest;
/*tr("过流")*/
CString g_sLangID_Native_OvrCurr;
CString g_sLangTxt_Native_OvrCurr;
/*tr("时间特性图")*/
CString g_sLangID_Native_TimeChart;
CString g_sLangTxt_Native_TimeChart;
/*_T("过流I段动作值")*/
CString g_sLangID_Native_OvrCurrIAct;
CString g_sLangTxt_Native_OvrCurrIAct;
/*_T("过流II段动作值")*/
CString g_sLangID_Native_OvrCurrIIAct;
CString g_sLangTxt_Native_OvrCurrIIAct;
/*_T("过流III段动作值")*/
CString g_sLangID_Native_OvrCurrIIIAct;
CString g_sLangTxt_Native_OvrCurrIIIAct;
/*_T("过流IV段动作值")*/
CString g_sLangID_Native_OvrCurrIVAct;
CString g_sLangTxt_Native_OvrCurrIVAct;
/*_T("过流V段动作值")*/
CString g_sLangID_Native_OvrCurrVAct;
CString g_sLangTxt_Native_OvrCurrVAct;
/*_T("过流I段动作时间")*/
CString g_sLangID_Native_OvrCurrITime;
CString g_sLangTxt_Native_OvrCurrITime;
/*_T("过流II段动作时间")*/
CString g_sLangID_Native_OvrCurrIITime;
CString g_sLangTxt_Native_OvrCurrIITime;
/*_T("过流III段动作时间")*/
CString g_sLangID_Native_OvrCurrIIITime;
CString g_sLangTxt_Native_OvrCurrIIITime;
/*_T("过流IV段动作时间")*/
CString g_sLangID_Native_OvrCurrIVTime;
CString g_sLangTxt_Native_OvrCurrIVTime;
/*_T("过流V段动作时间")*/
CString g_sLangID_Native_OvrCurrVTime;
CString g_sLangTxt_Native_OvrCurrVTime;

/*"<h1>试验名称：过流保护定值测试</h1>"*/
CString g_sLangID_Native_TestNameOvrCurr;
CString g_sLangTxt_Native_TestNameOvrCurr;
/*"过流I段保护定值测试"*/
CString g_sLangID_Native_OvrCurrIProtTest;
CString g_sLangTxt_Native_OvrCurrIProtTest;
/*"过流II段保护定值测试"*/
CString g_sLangID_Native_OvrCurrIIProtTest;
CString g_sLangTxt_Native_OvrCurrIIProtTest;
/*"过流III段保护定值测试"*/
CString g_sLangID_Native_OvrCurrIIIProtTest;
CString g_sLangTxt_Native_OvrCurrIIIProtTest;
/*"过流IV段保护定值测试"*/
CString g_sLangID_Native_OvrCurrIVProtTest;
CString g_sLangTxt_Native_OvrCurrIVProtTest;
/*"过流V段保护定值测试"*/
CString g_sLangID_Native_OvrCurrVProtTest;
CString g_sLangTxt_Native_OvrCurrVProtTest;
/*tr("默认值 = Iset1")*/
CString g_sLangID_Native_DefaultIset1;
CString g_sLangTxt_Native_DefaultIset1;
/*tr("默认值 = Iset2")*/
CString g_sLangID_Native_DefaultIset2;
CString g_sLangTxt_Native_DefaultIset2;
/*tr("默认值 = Iset3")*/
CString g_sLangID_Native_DefaultIset3;
CString g_sLangTxt_Native_DefaultIset3;
/*tr("默认值 = Iset4")*/
CString g_sLangID_Native_DefaultIset4;
CString g_sLangTxt_Native_DefaultIset4;
/*tr("默认值 = Iset5")*/
CString g_sLangID_Native_DefaultIset5;
CString g_sLangTxt_Native_DefaultIset5;
/*tr("默认值 = Tset1")*/
CString g_sLangID_Native_DefaultTset1;
CString g_sLangTxt_Native_DefaultTset1;
/*tr("默认值 = Tset2")*/
CString g_sLangID_Native_DefaultTset2;
CString g_sLangTxt_Native_DefaultTset2;
/*tr("默认值 = Tset3")*/
CString g_sLangID_Native_DefaultTset3;
CString g_sLangTxt_Native_DefaultTset3;
/*tr("默认值 = Tset4")*/
CString g_sLangID_Native_DefaultTset4;
CString g_sLangTxt_Native_DefaultTset4;
/*tr("默认值 = Tset5")*/
CString g_sLangID_Native_DefaultTset5;
CString g_sLangTxt_Native_DefaultTset5;
/*tr("ABC相")*/
CString g_sLangID_Native_PhaseABC;
CString g_sLangTxt_Native_PhaseABC;
/*tr("或")*/
CString g_sLangID_Native_Or;
CString g_sLangTxt_Native_Or;
/*tr("与")*/
CString g_sLangID_Native_And;
CString g_sLangTxt_Native_And;
// 模拟PT断线
CString g_sLangID_Native_SimDisconn;
CString g_sLangTxt_Native_SimDisconn;

// PT断线相
CString g_sLangID_Native_OpenPh;
CString g_sLangTxt_Native_OpenPh;

// Gradient 吕洋第二周
//  吕
CString g_sLangID_Native_DistProtect_TempFile;
CString g_sLangTxt_Native_DistProtect_TempFile; // 距离保护模板文件
CString g_sLangID_Native_Wel_DisProtect;
CString g_sLangTxt_Native_Wel_DisProtect; // 欢迎使用距离保护.
CString g_sLangID_Native_PonovoDisProtect;
CString g_sLangTxt_Native_PonovoDisProtect; // Ponovo 距离保护
CString g_sLangID_Native_DisProtect;
CString g_sLangTxt_Native_DisProtect; // 距离保护
CString g_sLangID_Native_multiple;
CString g_sLangTxt_Native_multiple; // 倍,R=
CString g_sLangID_Native_DisProt_SetTest;
CString g_sLangTxt_Native_DisProt_SetTest; // 距离保护定值测试
CString g_sLangID_Native_GroundFaultI;
CString g_sLangTxt_Native_GroundFaultI;
CString g_sLangID_Native_GroundFaultII;
CString g_sLangTxt_Native_GroundFaultII;
CString g_sLangID_Native_GroundFaultIII;
CString g_sLangTxt_Native_GroundFaultIII;
CString g_sLangID_Native_GroundFaultIV;
CString g_sLangTxt_Native_GroundFaultIV;
CString g_sLangID_Native_GroundFaultV;
CString g_sLangTxt_Native_GroundFaultV; // 接地故障1-5段
CString g_sLangID_Native_PhaseFaultI;
CString g_sLangTxt_Native_PhaseFaultI;
CString g_sLangID_Native_PhaseFaultII;
CString g_sLangTxt_Native_PhaseFaultII;
CString g_sLangID_Native_PhaseFaultIII;
CString g_sLangTxt_Native_PhaseFaultIII;
CString g_sLangID_Native_PhaseFaultIV;
CString g_sLangTxt_Native_PhaseFaultIV;
CString g_sLangID_Native_PhaseFaultV;
CString g_sLangTxt_Native_PhaseFaultV; // 相间故障1-5段
CString g_sLangID_Native_Para;
CString g_sLangTxt_Native_Para; // 段
CString g_sLangID_ITOTest_Tempfile;
CString g_sLangTxt_ITOTest_Tempfile; // 电流反时限试验模板文件Inverse Time Overcurrent(ITO)
CString g_sLangID_Wel_ITOTest;
CString g_sLangTxt_Wel_ITOTest; // 欢迎使用电流反时限试验.
CString g_sLangID_ITOTest;
CString g_sLangTxt_ITOTest; // 电流反时限试验ITOTest
CString g_sLangID_Ponovo_ITOTest;
CString g_sLangTxt_Ponovo_ITOTest; // Ponovo 电流反时限试验
CString g_sLangID_Theoretical_ActionTime;
CString g_sLangTxt_Theoretical_ActionTime; // 理论动作时间
CString g_sLangID_Native_ITO;
CString g_sLangTxt_Native_ITO; // 电流反时限
CString g_sLangID_Single_PhaseGround_Fault;
CString g_sLangTxt_Single_PhaseGround_Fault; // 单项接地故障
CString g_sLangID_Directional_LineSide;
CString g_sLangTxt_Directional_LineSide; // 指向线路侧Directional_LineSide
CString g_sLangID_Directional_BusSide;
CString g_sLangTxt_Directional_BusSide; // 指向母线侧
CString g_sLangID_Add_Series;
CString g_sLangTxt_Add_Series; // 添加系列
CString g_sLangID_Delet_Test;
CString g_sLangTxt_Delet_Test; // 删除试验
CString g_sLangID_Clear_Results;
CString g_sLangTxt_Clear_Results; // 清除结果
CString g_sLangID_Clear_All;
CString g_sLangTxt_Clear_All; // 清除所有
CString g_sLangID_Test_Parameters;
CString g_sLangTxt_Test_Parameters; // 试验参数

CString g_sLangID_Native_Wel_IncreExper;
CString g_sLangTxt_Native_Wel_IncreExper; // 欢迎使用递变测试.
CString g_sLangID_Native_PonovoIncre;
CString g_sLangTxt_Native_PonovoIncre; // Ponovo递变
CString g_sLangID_Native_IncreExper;
CString g_sLangTxt_Native_IncreExper; // 递变实验
CString g_sLangID_Native_ImpedanceSet;
CString g_sLangTxt_Native_ImpedanceSet; // 阻抗定值(Ω):
CString g_sLangID_Native_PrepareTime;
CString g_sLangTxt_Native_PrepareTime; // 变化前时间(s)

CString g_sLangID_Native_PreCurrent;
CString g_sLangTxt_Native_PreCurrent; // 变化前电流幅值(A)
CString g_sLangID_Native_PreAngle;
CString g_sLangTxt_Native_PreAngle; // 故障前电压电流相角(°)
CString g_sLangID_TestItem1;
CString g_sLangTxt_TestItem1; // 测试项一
CString g_sLangID_Native_InputAction;
CString g_sLangTxt_Native_InputAction; // 开入%1，动作值：%2
CString g_sLangID_Native_ExInputAction;
CString g_sLangTxt_Native_ExInputAction; // 扩展开入%1，动作值：%2

CString g_sLangID_Native_NormalOutpExSet;
CString g_sLangTxt_Native_NormalOutpExSet; // 常态开出设置（扩展）
CString g_sLangID_Native_FaultOutpExSet;
CString g_sLangTxt_Native_FaultOutpExSet; // 故障态开出设置(扩展)
CString g_sLangID_Native_All;
CString g_sLangTxt_Native_All; // 全部
CString g_sLangID_Experiment;
CString g_sLangTxt_Experiment; // 试验
CString g_sLangID_Native_InitofVarP;
CString g_sLangTxt_Native_InitofVarP; // 变化始值(°)：
CString g_sLangID_Native_FinalofVarP;
CString g_sLangTxt_Native_FinalofVarP; // 变化终值(°)：
CString g_sLangID_Native_StepofVarP;
CString g_sLangTxt_Native_StepofVarP; // 变化步长(°)：
CString g_sLangID_Native_InitofVarF;
CString g_sLangTxt_Native_InitofVarF; // 变化始值(Hz)：
CString g_sLangID_Native_FinalofVarF;
CString g_sLangTxt_Native_FinalofVarF; // 变化终值(Hz)：
CString g_sLangID_Native_StepofVarF;
CString g_sLangTxt_Native_StepofVarF; // 变化步长(Hz)：

// xwd 第三周
CString g_sLangID_Native_TracVarTestTpl;		// = _T("Native_TracVarTestTpl")
CString g_sLangTxt_Native_TracVarTestTpl;		// = _T("牵引变差动试验模板文件")
CString g_sLangID_Native_WelcTracVarTest;		// = _T("Native_WelcTracVarTest")
CString g_sLangTxt_Native_WelcTracVarTest;		// = _T("欢迎使用牵引变差动测试")
CString g_sLangID_Native_PonTracVar;			// = _T("Native_PonTracVar")
CString g_sLangTxt_Native_PonTracVar;			// = _T("Ponovo 牵引变差动")

CString g_sLangID_Native_TracVar;				// = _T("Native_TracVar")
CString g_sLangTxt_Native_TracVar;				// = _T("牵引变差动")

CString g_sLangID_Native_FaultTimes;			// = _T("Native_FaultTime")
CString g_sLangTxt_Native_FaultTimes;			// = _T("故障时间(s)")
CString g_sLangID_Native_HLCTPolarDef;			// = _T("Native_HLCTPolarDef")
CString g_sLangTxt_Native_HLCTPolarDef;			// = _T("高低压测CT极性定义")
CString g_sLangID_Native_SetValueName;			// = _T("Native_SetValueName")
CString g_sLangTxt_Native_SetValueName;			// = _T("定值名称")
CString g_sLangID_Native_DiffQBrkCurrSetValue;	// = _T("Native_DiffQBrkCurrSetValue")
CString g_sLangTxt_Native_DiffQBrkCurrSetValue; // = _T("差动速断电流定值(ln)")
CString g_sLangID_Native_DiffActCurrThresh;		// = _T("Native_DiffActCurrThresh")
CString g_sLangTxt_Native_DiffActCurrThresh;	// = _T("差动动作电流门槛值(ln)")
CString g_sLangID_Native_RatioBrkInflect1Curr;	// = _T("Native_RatioBrkInflect1Curr")
CString g_sLangTxt_Native_RatioBrkInflect1Curr; // = _T("比率制动特性拐点数1电流(ln)")
CString g_sLangID_Native_RatioBrkInflect2Curr;	// = _T("Native_RatioBrkInflect2Curr")
CString g_sLangTxt_Native_RatioBrkInflect2Curr; // = _T("比率制动特性拐点数2电流(ln)")
CString g_sLangID_Native_SettingMode;			// = _T("Native_SettingMode")
CString g_sLangTxt_Native_SettingMode;			// = _T("整定方式")
CString g_sLangID_Native_HvCTPolarity;			// = _T("Native_HvCTPolarity")
CString g_sLangTxt_Native_HvCTPolarity;			// = _T("高压侧CT极性定义")
CString g_sLangID_Native_PreChangeTime;			// = _T("Native_PreChangeTime")
CString g_sLangTxt_Native_PreChangeTime;		// = _T("变化前时间(s):")
CString g_sLangID_Native_PreFaultTimes;			// = _T("Native_PreFaultTimes")
CString g_sLangTxt_Native_PreFaultTimes;		// = _T("故障前时间(s):")
CString g_sLangID_Native_NormalVoltAmp;			// = _T("Native_NormalVoltAmp")
CString g_sLangTxt_Native_NormalVoltAmp;		// = _T("常态电压幅值(V):")
CString g_sLangID_Native_NormalVoltPhase;		// = _T("Native_NormalVoltPhase")
CString g_sLangTxt_Native_NormalVoltPhase;		// = _T("常态电压相序:")
CString g_sLangID_Native_NormalCurrAmp;			// = _T("Native_NormalCurrAmp")
CString g_sLangTxt_Native_NormalCurrAmp;		// = _T("常态电流幅值(A):")
CString g_sLangID_Native_NormalCurrPhase;		// = _T("Native_NormalCurrPhase")
CString g_sLangTxt_Native_NormalCurrPhase;		// = _T("常态电流相序:")
CString g_sLangID_Native_NormalPhaseAngle;		// = _T("Native_NormalPhaseAngle")
CString g_sLangTxt_Native_NormalPhaseAngle;		// = _T("常态相角(U-I)")
CString g_sLangID_Native_FaultMode;				// = _T("Native_FaultMode")
CString g_sLangTxt_Native_FaultMode;			// = _T("故障模式:")
CString g_sLangID_Native_ChangeAmount;			// = _T("Native_ChangeAmount")
CString g_sLangTxt_Native_ChangeAmount;			// = _T("变化量:")
// CString g_sLangID_Native_ShortCircuitVs;		// = _T("Native_ShortCircuitVs")
// CString g_sLangTxt_Native_ShortCircuitVs;		// = _T("短路电压(V):")
CString g_sLangID_Native_ShortCircuitAs;		// = _T("Native_ShortCircuitAs")
CString g_sLangTxt_Native_ShortCircuitAs;		// = _T("短路电流(A):")
CString g_sLangID_Native_FrequencyHz;			// = _T("Native_FrequencyHz")
CString g_sLangTxt_Native_FrequencyHz;			// = _T("频率(Hz):")
CString g_sLangID_Native_RecordQty;				// = _T("Native_RecordQty")
CString g_sLangTxt_Native_RecordQty;			// = _T("记录量:")
CString g_sLangID_Native_StepTimeS;				// = _T("Native_StepTimeS")
CString g_sLangTxt_Native_StepTimeS;			// = _T("步长时间(s):")
CString g_sLangID_Native_SetValueA;				// = _T("Native_SetValueA")
CString g_sLangTxt_Native_SetValueA;			// = _T("整定值(A)")
CString g_sLangID_Native_SetActTimeS;			// = _T("Native_SetActTimeS")
CString g_sLangTxt_Native_SetActTimeS;			// = _T("整定动作时间(s)")

CString g_sLangID_Native_SectionI;					 // = _T("Native_SectionI")
CString g_sLangTxt_Native_SectionI;					 // = _T("Ⅰ段")
CString g_sLangID_Native_SectionII;					 // = _T("Native_SectionII")
CString g_sLangTxt_Native_SectionII;				 // = _T("Ⅱ段")
CString g_sLangID_Native_SectionIII;				 // = _T("Native_SectionIII")
CString g_sLangTxt_Native_SectionIII;				 // = _T("Ⅲ段")
CString g_sLangID_Native_SectionIV;					 // = _T("Native_SectionIV")
CString g_sLangTxt_Native_SectionIV;				 // = _T("Ⅳ段")
CString g_sLangID_Native_SectionV;					 // = _T("Native_SectionV")
CString g_sLangTxt_Native_SectionV;					 // = _T("Ⅴ段")
CString g_sLangID_Native_FaultDir;					 // = _T("Native_FaultDir")
CString g_sLangTxt_Native_FaultDir;					 // = _T("故障方向:")

CString g_sLangID_Native_Confirm;					 // = _T("Native_Confirm")
CString g_sLangTxt_Native_Confirm;					 // = _T("确  认")
CString g_sLangID_Native_Name;						 // = _T("Native_Name")
CString g_sLangTxt_Native_Name;						 // = _T("名称：")
CString g_sLangID_Native_ZeroSeqCurr;				 // = _T("Native_ZeroSeqCurr")
CString g_sLangTxt_Native_ZeroSeqCurr;				 // = _T("零序电流定值(A):")
CString g_sLangID_Native_FaultTriggerTime;			 // = _T("Native_FaultTriggerTime")
CString g_sLangTxt_Native_FaultTriggerTime;			 // = _T("故障触发时刻:")
CString g_sLangID_Native_Multiples;					 // = _T("Native_Multiples")
CString g_sLangTxt_Native_Multiples;				 // = _T("倍数:")
CString g_sLangID_Native_SetActTime;				 // = _T("Native_SetActTime")
CString g_sLangTxt_Native_SetActTime;				 // = _T("整定动作时间(s):")
CString g_sLangID_Native_LoadCurrent;				 // = _T("Native_LoadCurrent")
CString g_sLangTxt_Native_LoadCurrent;				 // = _T("负荷电流(A)")
CString g_sLangID_Native_LoadPowerAngle;			 // = _T("Native_LoadPowerAngle")
CString g_sLangTxt_Native_LoadPowerAngle;			 // = _T("负荷功角(°)")
CString g_sLangID_Native_MaxFaultTime;				 // = _T("Native_MaxFaultTime")
CString g_sLangTxt_Native_MaxFaultTime;				 // = _T("最大故障时间(s)")
CString g_sLangID_Native_TransFault;				 // = _T("Native_TransFault")
CString g_sLangTxt_Native_TransFault;				 // = _T("转换性故障")
CString g_sLangID_Native_TransTime;					 // = _T("Native_TransTime")
CString g_sLangTxt_Native_TransTime;				 // = _T("转换时间(s)")
CString g_sLangID_Native_FaultTriggerTimes;			 // = _T("Native_FaultTrigTimes")
CString g_sLangTxt_Native_FaultTriggerTimes;		 // = _T("故障触发时刻")
CString g_sLangID_Native_GrdDistFixed;				 // = _T("Native_GrdDistFixed")
CString g_sLangTxt_Native_GrdDistFixed;				 // = _T("接地距离定值")
CString g_sLangID_Native_DistValue;					 // = _T("Native_DistValue")
CString g_sLangTxt_Native_DistValue;				 // = _T("相间距离定值")
CString g_sLangID_Native_Impedance;					 // = _T("Native_Impedance")
CString g_sLangTxt_Native_Impedance;				 // = _T("短路阻抗/整定阻抗")
CString g_sLangID_Native_GrdSetTime;				 // = _T("Native_GrdSetTime")
CString g_sLangTxt_Native_GrdSetTime;				 // = _T("接地整定时间(s)")
CString g_sLangID_Native_PhaseSetTime;				 // = _T("Native_PhaseSetTime")
CString g_sLangTxt_Native_PhaseSetTime;				 // = _T("相间整定时间(s)")
CString g_sLangID_Native_Impedance1;				 // = _T("Native_Impedance1")
CString g_sLangTxt_Native_Impedance1;				 // = _T("I段阻抗(Ω):")
CString g_sLangID_Native_Impedance2;				 // = _T("Native_Impedance2")
CString g_sLangTxt_Native_Impedance2;				 // = _T("II段阻抗(Ω):")
CString g_sLangID_Native_Impedance3;				 // = _T("Native_Impedance3")
CString g_sLangTxt_Native_Impedance3;				 // = _T("III段阻抗(Ω):")
CString g_sLangID_Native_Impedance4;				 // = _T("Native_Impedance4")
CString g_sLangTxt_Native_Impedance4;				 // = _T("IV段阻抗(Ω):")
CString g_sLangID_Native_Impedance5;				 // = _T("Native_Impedance5")
CString g_sLangTxt_Native_Impedance5;				 // = _T("V段阻抗(Ω):")
CString g_sLangID_Native_ReverseDir;				 // = _T("Native_ReverseDir")
CString g_sLangTxt_Native_ReverseDir;				 // = _T("反方向")
CString g_sLangID_Native_ErrorRange;				 // = _T("Native_ErrorRange")
CString g_sLangTxt_Native_ErrorRange;				 // = _T("误差范围(%):")
CString g_sLangID_Native_Cancel;					 // = _T("Native_Cancel")
CString g_sLangTxt_Native_Cancel;					 // = _T("取  消")
CString g_sLangID_Native_AfterOverlap;				 // = _T("Native_AfterOverlap")
CString g_sLangTxt_Native_AfterOverlap;				 // = _T("重合后")
CString g_sLangID_Native_FreqHz;					 // = _T("Native_FreqHz")
CString g_sLangTxt_Native_FreqHz;					 // = _T("频率(Hz)")
CString g_sLangID_Native_VoltSelect;				 // = _T("Native_VoltSelect")
CString g_sLangTxt_Native_VoltSelect;				 // = _T("抽取电压选择")
CString g_sLangID_Native_VoltAfterTrip;				 // = _T("Native_VoltAfterTrip")
CString g_sLangTxt_Native_VoltAfterTrip;			 // = _T("跳闸后抽取电压（V）")
CString g_sLangID_Native_VoltPhaseAfterTrip;		 // = _T("Native_VoltPhaseAfterTrip")
CString g_sLangTxt_Native_VoltPhaseAfterTrip;		 // = _T("跳闸后抽取电压相位°")
CString g_sLangID_Native_ChangeStartVal;			 // = _T("Native_ChangeStartVal")
CString g_sLangTxt_Native_ChangeStartVal;			 // = _T("变化始值：")
CString g_sLangID_Native_ChangeEndVal;				 // = _T("Native_ChangeEndVal")
CString g_sLangTxt_Native_ChangeEndVal;				 // = _T("变化终值：")
CString g_sLangID_Native_ChangeStep;				 // = _T("Native_ChangeStep")
CString g_sLangTxt_Native_ChangeStep;				 // = _T("变化步长：")
CString g_sLangID_Native_TestPoint;					 // = _T("Native_TestPoint")
CString g_sLangTxt_Native_TestPoint;				 // = _T("测试点：")
CString g_sLangID_Native_FaultTimeS;				 // = _T("Native_FaultTimeS")
CString g_sLangTxt_Native_FaultTimeS;				 // = _T("故障时间(s)：")
CString g_sLangID_Native_SettingModes;				 // = _T("Native_SettingModes")
CString g_sLangTxt_Native_SettingModes;				 // = _T("整定方式：")
CString g_sLangID_Native_BaseCurrent;				 // = _T("Native_BaseCurrent")
CString g_sLangTxt_Native_BaseCurrent;				 // = _T("基准电流(A)：")
CString g_sLangID_Native_SearchMethod;				 // = _T("Native_SearchMethod")
CString g_sLangTxt_Native_SearchMethod;				 // = _T("搜索方法：")
CString g_sLangID_Native_CTPolarityDef;				 // = _T("Native_CTPolarityDef")
CString g_sLangTxt_Native_CTPolarityDef;			 // = _T("高低压测CT极性定义：")
CString g_sLangID_Native_BrakeEquation;				 // = _T("Native_BrakeEquation")
CString g_sLangTxt_Native_BrakeEquation;			 // = _T("制动方程：")
CString g_sLangID_Native_TestPhase;					 // = _T("Native_TestPhase")
CString g_sLangTxt_Native_TestPhase;				 // = _T("测试相：")
CString g_sLangID_Native_TestAccuracy;				 // = _T("Native_TestAccuracy")
CString g_sLangTxt_Native_TestAccuracy;				 // = _T("测试精度：")
CString g_sLangID_Native_TransConnType;				 // = _T("Native_TransConnType")
CString g_sLangTxt_Native_TransConnType;			 // = _T("变压器接线形式：")
CString g_sLangID_Native_DiffCurrent;				 // = _T("Native_DiffCurrent")
CString g_sLangTxt_Native_DiffCurrent;				 // = _T("差动电流(A):")
CString g_sLangID_Native_BrakeCurrent;				 // = _T("Native_BrakeCurrent")
CString g_sLangTxt_Native_BrakeCurrent;				 // = _T("制动电流(A):")
CString g_sLangID_Native_ManualDiff;				 // = _T("Native_ManualDiff")
CString g_sLangTxt_Native_ManualDiff;				 // = _T("手动递变差流")
CString g_sLangID_Native_ManualAdd;					 // = _T("Native_ManualAdd")
CString g_sLangTxt_Native_ManualAdd;				 // = _T("手动加+")
CString g_sLangID_Native_ManualSub;					 // = _T("Native_ManualSub")
CString g_sLangTxt_Native_ManualSub;				 // = _T("手动减-")
CString g_sLangID_Native_BrakeCurrIn;				 // = _T("Native_BrakeCurrIn")
CString g_sLangTxt_Native_BrakeCurrIn;				 // = _T("制动电流In:")
CString g_sLangID_Native_TestType;					 // = _T("Native_TestType")
CString g_sLangTxt_Native_TestType;					 // = _T("测试类型:")
CString g_sLangID_Native_TestAccIn;					 // = _T("Native_TestAccIn")
CString g_sLangTxt_Native_TestAccIn;				 // = _T("测试精度In:")
CString g_sLangID_Native_SearchUpperLimits;			 // = _T("Native_SearchUpperLimits")
CString g_sLangTxt_Native_SearchUpperLimits;		 // = _T("搜索上限:")
CString g_sLangID_Native_SearchLowerLimits;			 // = _T("Native_SearchLowerLimits")
CString g_sLangTxt_Native_SearchLowerLimits;		 // = _T("搜索下限:")
CString g_sLangID_Native_DiffCurrentId;				 // = _T("Native_DiffCurrentId")
CString g_sLangTxt_Native_DiffCurrentId;			 // = _T("差动电流Id:")
CString g_sLangID_Native_SearchStartValue;			 // = _T("Native_SearchStartValue")
CString g_sLangTxt_Native_SearchStartValue;			 // = _T("搜索始值(%):")
CString g_sLangID_Native_SearchEndValue;			 // = _T("Native_SearchEndValue")
CString g_sLangTxt_Native_SearchEndValue;			 // = _T("搜索终值(%):")
CString g_sLangID_Native_Evaluation;				 // = _T("Native_Evaluation")
CString g_sLangTxt_Native_Evaluation;				 // = _T("评估：")
CString g_sLangID_Native_Expression;				 // = _T("Native_Expression")
CString g_sLangTxt_Native_Expression;				 // = _T("表达式")
CString g_sLangID_Native_Result;					 // = _T("Native_Result")
CString g_sLangTxt_Native_Result;					 // = _T("结果：")
CString g_sLangID_Native_DiffCurrents;				 // = _T("Native_DiffCurrents")
CString g_sLangTxt_Native_DiffCurrents;				 // = _T("差动电流")
CString g_sLangID_Native_ErrorLessThan;				 // = _T("Native_ErrorLessThan")
CString g_sLangTxt_Native_ErrorLessThan;			 // = _T("误差 (%) <")


CString g_sLangID_Native_RelativeErrorLessThan;		 // = _T("Native_RelativeErrorLessThan")
CString g_sLangTxt_Native_RelativeErrorLessThan;	 // = _T("相对误差(%)<")
CString g_sLangID_Native_AbsoluteErrorLessThan;		 // = _T("Native_AbsoluteErrorLessThan")
CString g_sLangTxt_Native_AbsoluteErrorLessThan;	 // = _T("绝对误差<")

// Harmtest 吕第三周
CString g_sLangID_Native_HarmonicTest;
CString g_sLangTxt_Native_HarmonicTest; // 谐波试验
CString g_sLangID_Native_Wel_HarmModTest;
CString g_sLangTxt_Native_Wel_HarmModTest; // 欢迎使用谐波模块试验
CString g_sLangID_Native_Choose_HtesttempFile;
CString g_sLangTxt_Native_Choose_HtesttempFile; // 选择谐波试验模板文件
CString g_sLangID_Native_saveSuccess;
CString g_sLangTxt_Native_saveSuccess; // 文件保存成功！
CString g_sLangID_Native_harmTestTempSaveS;
CString g_sLangTxt_Native_harmTestTempSaveS; // 谐波试验默认模板[%1]保存成功.
CString g_sLangID_Native_harmTestTempSaveF;
CString g_sLangTxt_Native_harmTestTempSaveF; // 谐波试验默认模板[%1]保存失败.
CString g_sLangID_Native_saveFail;
CString g_sLangTxt_Native_saveFail; // 文件保存失败！
CString g_sLangID_Native_createMFileFail;
CString g_sLangTxt_Native_createMFileFail; // 创建测试模板文件路径失败
CString g_sLangID_Native_saveAsSuccess;
CString g_sLangTxt_Native_saveAsSuccess; // 模板另存为[%1]成功.
CString g_sLangID_Native_saveAsFail;
CString g_sLangTxt_Native_saveAsFail; // 模板另存为[%1]失败.
CString g_sLangID_Native_testName_Harmonic;
CString g_sLangTxt_Native_testName_Harmonic; // 试验名称：谐波

CString g_sLangID_Native_secondHarmonicAmp;
CString g_sLangTxt_Native_secondHarmonicAmp; // 二次谐波幅值

CString g_sLangID_Native_contentRatio;
CString g_sLangTxt_Native_contentRatio; // 含有率/%
CString g_sLangID_Native_rmsValueV;
CString g_sLangTxt_Native_rmsValueV; // 有效值/V
CString g_sLangID_Native_rmsValueA;
CString g_sLangTxt_Native_rmsValueA; // 有效值/A
CString g_sLangID_Native_phaseAngle;
CString g_sLangTxt_Native_phaseAngle; // 相	位/°
CString g_sLangID_Native_totalRmsValue;
CString g_sLangTxt_Native_totalRmsValue; // 总有效值
CString g_sLangID_Native_actionValueA;
CString g_sLangTxt_Native_actionValueA; // 动作值(A)
CString g_sLangID_Native_InitofVar;
CString g_sLangTxt_Native_InitofVar; // 变化始值(
CString g_sLangID_Native_FinalofVar;
CString g_sLangTxt_Native_FinalofVar; // 变化终值(
CString g_sLangID_Native_StepofVar;
CString g_sLangTxt_Native_StepofVar; // 变化步长(
CString g_sLangID_Native_channelAmp;
CString g_sLangTxt_Native_channelAmp; // 通道幅值
CString g_sLangID_Native_groupNumber;
CString g_sLangTxt_Native_groupNumber; // 第%1组
CString g_sLangID_Native_harmonicLimitExceeded;
CString g_sLangTxt_Native_harmonicLimitExceeded; // 你总计只能选择31次谐波，假如想选择当前次谐波，需要取消勾选一行！
CString g_sLangID_Native_harmonicExceedsMax;
CString g_sLangTxt_Native_harmonicExceedsMax; // 选择的谐波次数大于最大值49次！
CString g_sLangID_Native_variaPointExceedsLimit;
CString g_sLangTxt_Native_variaPointExceedsLimit; // 递变点数超过3000点，请重新输入！

// ui1
CString g_sLangID_Native_faultTimeMargin;
CString g_sLangTxt_Native_faultTimeMargin; // 故障时间裕度(s):

// ui2
CString g_sLangID_Native_volDefinition;
CString g_sLangTxt_Native_volDefinition; // 电压定义：
CString g_sLangID_Native_referenceItem;
CString g_sLangTxt_Native_referenceItem; // 参考项：
CString g_sLangID_Native_transConnection;
CString g_sLangTxt_Native_transConnection; // 变压器接线方式：


// ui3

CString g_sLangID_Native_Freq_Deviation;
CString g_sLangTxt_Native_Freq_Deviation; // 频率滑差df/dt(Hz/s):
CString g_sLangID_Native_initialFreq;
CString g_sLangTxt_Native_initialFreq; // 频率起始值(Hz):
CString g_sLangID_Native_FreqChange_step;
CString g_sLangTxt_Native_FreqChange_step; // 频率变化步长(Hz):
CString g_sLangID_Native_endFreq;
CString g_sLangTxt_Native_endFreq; // 频率结束值(Hz):
CString g_sLangID_Native_finalFreq;
CString g_sLangTxt_Native_finalFreq; // 频率变化终值(Hz):
CString g_sLangID_Native_initialFreq_deviation;
CString g_sLangTxt_Native_initialFreq_deviation; // 频率滑差变化始值(Hz/s):
CString g_sLangID_Native_Freq_deviationstep;
CString g_sLangTxt_Native_Freq_deviationstep; // 频率滑差变化步长(Hz/s
CString g_sLangID_Native_finalFreq_deviation;
CString g_sLangTxt_Native_finalFreq_deviation; // 频率滑差变化终值(Hz/s):
CString g_sLangID_Native_initialCur;
CString g_sLangTxt_Native_initialCur; // 电流变化始值(A):
CString g_sLangID_Native_final_cur;
CString g_sLangTxt_Native_final_cur; // 电流变化终值(A):
CString g_sLangID_Native_Curchange_step;
CString g_sLangTxt_Native_Curchange_step; // 电流变化步长(A):
CString g_sLangID_Native_CurPhase_output;
CString g_sLangTxt_Native_CurPhase_output; // 电流输出相：
CString g_sLangID_Native_initial_linevolchange;
CString g_sLangTxt_Native_initial_linevolchange; // 线电压变化始值(V):
CString g_sLangID_Native_final_linevolchange;
CString g_sLangTxt_Native_final_linevolchange; // 线电压变化终值(V):
CString g_sLangID_Native_linevol_changestep;
CString g_sLangTxt_Native_linevol_changestep; // 线电压变化步长(V):
CString g_sLangID_Native_vol_change;
CString g_sLangTxt_Native_vol_change; // 电压变化量：

// 马嘉骅第三周
// OverVoltInverseTime_Trans 马
/*tr("电压反时限试验模板文件")*/
CString g_sLangID_Native_VoltIDMTTestTemp;
CString g_sLangTxt_Native_VoltIDMTTestTemp;
/*tr("Ponovo电压反时限试验")*/
CString g_sLangID_Native_PonVoltIDMT;
CString g_sLangTxt_Native_PonVoltIDMT;
/*_T("欢迎使用电压反时限试验.")*/
CString g_sLangID_Native_WelVoltIDMT;
CString g_sLangTxt_Native_WelVoltIDMT;
/*tr("Ponovo ")*/
CString g_sLangID_Native_PonBlaVoltIDMT;
CString g_sLangTxt_Native_PonBlaVoltIDMT;
/*tr("电压反时限试验")*/
CString g_sLangID_Native_VolReTiLimTe;
CString g_sLangTxt_Native_VolReTiLimTe;
/*"电压反时限"*/
CString g_sLangID_Native_VoltIDMT;
CString g_sLangTxt_Native_VoltIDMT;
/*"三相故障"*/
CString g_sLangID_Native_3PhFault;
CString g_sLangTxt_Native_3PhFault;
/*"零序电压"*/
CString g_sLangID_Native_ZeroSeqVolt;
CString g_sLangTxt_Native_ZeroSeqVolt;
/*tr("始值-终值")*/
CString g_sLangID_Native_Start_End;
CString g_sLangTxt_Native_Start_End;
/*tr("始值-终值-始值")*/
CString g_sLangID_Native_Start_End_Start;
CString g_sLangTxt_Native_Start_End_Start;
// 动作时间=%1s,
CString g_sLangID_Native_ActTimeSymSy;
CString g_sLangTxt_Native_ActTimeSymSy;
// 故障前状态
CString g_sLangID_Native_PreFaultSt;
CString g_sLangTxt_Native_PreFaultSt;
// 故障状态
CString g_sLangID_Native_FaultSt;
CString g_sLangTxt_Native_FaultSt;



// 故障持续时间
CString g_sLangID_Native_FaultDur;
CString g_sLangTxt_Native_FaultDur;
// 特性曲线
CString g_sLangID_Native_CharCurve;
CString g_sLangTxt_Native_CharCurve;
// 相电压
CString g_sLangID_Native_PhVolt;
CString g_sLangTxt_Native_PhVolt;

// 第四周许
CString g_sLangID_Native_QuickBreakCurrent;			 // = _T("Native_QuickBreakCurrent")
CString g_sLangTxt_Native_QuickBreakCurrent;		 // = _T("速断电流=%1A")
CString g_sLangID_Native_QuickBreakCurrentIn;		 // = _T("Native_QuickBreakCurrentIn")
CString g_sLangTxt_Native_QuickBreakCurrentIn;		 // = _T("速断电流=%1In")
CString g_sLangID_Native_CenterPointImpedance;		 // = _T("Native_CenterPointImpedance")
CString g_sLangTxt_Native_CenterPointImpedance;		 // = _T("中心点阻抗(Ω):")
CString g_sLangID_Native_CenterPointImpedanceAngle;	 // = _T("Native_CenterPointImpedanceAngle")
CString g_sLangTxt_Native_CenterPointImpedanceAngle; // = _T("中心点阻抗角(°):")
CString g_sLangID_Native_SearchRadius;				 // = _T("Native_SearchRadius")
CString g_sLangTxt_Native_SearchRadius;				 // = _T("搜索半径(Ω):")
CString g_sLangID_Native_ImpedanceAngleStartValue;	 // = _T("Native_ImpedanceAngleStartValue")
CString g_sLangTxt_Native_ImpedanceAngleStartValue;	 // = _T("阻抗角始值(°):")
CString g_sLangID_Native_ImpedanceAngleEndValue;	 // = _T("Native_ImpedanceAngleEndValue")
CString g_sLangTxt_Native_ImpedanceAngleEndValue;	 // = _T("阻抗角终值(°):")
CString g_sLangID_Native_AngleChangeSteps;			 // = _T("Native_AngleChangeSteps")
CString g_sLangTxt_Native_AngleChangeSteps;			 // = _T("角度改变步长(°):")
CString g_sLangID_Native_ImpedanceChangeStep;		 // = _T("Native_ImpedanceChangeStep")
CString g_sLangTxt_Native_ImpedanceChangeStep;		 // = _T("阻抗改变步长(Ω):")
CString g_sLangID_Native_MaxFaultTimes;				 // = _T("Native_MaxFaultTimes")
CString g_sLangTxt_Native_MaxFaultTimes;			 // = _T("最大故障时间(s):")
CString g_sLangID_Native_EndImpedance;				 // = _T("Native_EndImpedance")
CString g_sLangTxt_Native_EndImpedance;				 // = _T("末端阻抗(Ω):")
CString g_sLangID_Native_EndImpAngle;				 // = _T("Native_EndImpAngle")
CString g_sLangTxt_Native_EndImpAngle;				 // = _T("末端阻抗角(°):")
CString g_sLangID_Native_StartImpedance;			 // = _T("Native_StartImpedance")
CString g_sLangTxt_Native_StartImpedance;			 // = _T("首端阻抗(Ω):")
CString g_sLangID_Native_StartImpAngle;				 // = _T("Native_StartImpAngle")
CString g_sLangTxt_Native_StartImpAngle;			 // = _T("首端阻抗角(°):")
CString g_sLangID_Native_ImpStep;					 // = _T("Native_ImpStep")
CString g_sLangTxt_Native_ImpStep;					 // = _T("阻抗步长(Ω):")

CString g_sLangID_Native_RefState;	   // = _T("Native_RefState")
CString g_sLangTxt_Native_RefState;	   // = _T("开入翻转参考状态：")
CString g_sLangID_Native_DcComp;	   // = _T("Native_DcComp")
CString g_sLangTxt_Native_DcComp;	   // = _T("叠加衰减直流分量：")
CString g_sLangID_Native_DecayTime;	   // = _T("Native_DecayTime")
CString g_sLangTxt_Native_DecayTime;   // = _T("衰减时间常数：")
CString g_sLangID_Native_LoopCount;	   // = _T("Native_LoopCount")
CString g_sLangTxt_Native_LoopCount;   // = _T("循环次数：")
CString g_sLangID_Native_AuxDCSet;	   // = _T("Native_AuxDCSet")
CString g_sLangTxt_Native_AuxDCSet;	   // = _T("辅助直流设置(V)")
CString g_sLangID_Native_ZeroSeqComp;  // = _T("Native_ZeroSeqComp")
CString g_sLangTxt_Native_ZeroSeqComp; // = _T("零序补偿系数：")

CString g_sLangID_Native_OutTotalTime;	// = _T("Native_OutTotalTime")
CString g_sLangTxt_Native_OutTotalTime; // = _T("输出总时")
CString g_sLangID_Native_ShiftMoment;	// = _T("Native_ShiftMoment")
CString g_sLangTxt_Native_ShiftMoment;	// = _T("变位时刻(ms)")
CString g_sLangID_Native_CloseTimes;	// = _T("Native_CloseTime")
CString g_sLangTxt_Native_CloseTimes;	// = _T("闭合时间(ms)")
CString g_sLangID_Native_BreakTime;		// = _T("Native_BreakTime")
CString g_sLangTxt_Native_BreakTime;	// = _T("断开时间(ms)")

CString g_sLangID_Native_SOETest;		  // = _T("Native_SOETest")
CString g_sLangTxt_Native_SOETest;		  // = _T("SOE测试")
CString g_sLangID_Native_SaveConfig;	  // = _T("Native_SaveConfig")
CString g_sLangTxt_Native_SaveConfig;	  // = _T("保存配置")
CString g_sLangID_Native_SaveCurrConfig;  // = _T("Native_SaveCurrConfig")
CString g_sLangTxt_Native_SaveCurrConfig; // = _T("保存目前配置参数")
CString g_sLangID_Native_StartTrigger;	  // = _T("Native_StartTrigger")
CString g_sLangTxt_Native_StartTrigger;	  // = _T("开始时触发")
CString g_sLangID_Native_StartExpFail;	  // = _T("Native_StartExpFail")
CString g_sLangTxt_Native_StartExpFail;	  // = _T("开始实验失败")
CString g_sLangID_Native_StopExpFail;	  // = _T("Native_StopExpFail")
CString g_sLangTxt_Native_StopExpFail;	  // = _T("实验停止失败")

CString g_sLangID_Native_NormOutputSet;		// = _T("Native_NormOutputSet")
CString g_sLangTxt_Native_NormOutputSet;	// = _T("常态开出设置")
CString g_sLangID_Native_FaultOutputSet;	// = _T("Native_FaultOutputSet")
CString g_sLangTxt_Native_FaultOutputSet;	// = _T("故障态开出设置")
CString g_sLangID_Native_IOSet;				// = _T("Native_IOSet")
CString g_sLangTxt_Native_IOSet;			// = _T("开入、开出量设置")
CString g_sLangID_Native_InputSelect;		// = _T("Native_InputSelect")
CString g_sLangTxt_Native_InputSelect;		// = _T("开入选择")
CString g_sLangID_Native_OutputFlipStart;	// = _T("Native_OutputFlipStart")
CString g_sLangTxt_Native_OutputFlipStart;	// = _T("开出翻转启动方式")
CString g_sLangID_Native_OutputHoldTime;	// = _T("Native_OutputHoldTime")
CString g_sLangTxt_Native_OutputHoldTime;	// = _T("开出保持时间(s)")
CString g_sLangID_Native_OutputFlipMoment;	// = _T("Native_OutputFlipMoment")
CString g_sLangTxt_Native_OutputFlipMoment; // = _T("开出翻转时刻(s)")
CString g_sLangID_Native_SingleJump;		// = _T("Native_SingleJump")
CString g_sLangTxt_Native_SingleJump;		// = _T("单跳")
CString g_sLangID_Native_TripleJump;		// = _T("Native_TripleJump")
CString g_sLangTxt_Native_TripleJump;		// = _T("三跳")
CString g_sLangID_Native_Reincidence;		// = _T("Native_Reincidence")
CString g_sLangTxt_Native_Reincidence;		// = _T("重合")
CString g_sLangID_Native_TimeStart;			// = _T("Native_TimeStart")
CString g_sLangTxt_Native_TimeStart;		// = _T("时间启动")
CString g_sLangID_Native_InputStart;		// = _T("Native_InputStart")
CString g_sLangTxt_Native_InputStart;		// = _T("开入量启动")
CString g_sLangID_Native_InputABCD;			// = _T("Native_InputABCD")
CString g_sLangTxt_Native_InputABCD;		// = _T("开入A-B-C-D")
CString g_sLangID_Native_InputEFGH;			// = _T("Native_InputEFGH")
CString g_sLangTxt_Native_InputEFGH;		// = _T("开入E-F-G-H")
CString g_sLangID_Native_OutputABCD;		// = _T("Native_OutputABCD")
CString g_sLangTxt_Native_OutputABCD;		// = _T("开出A-B-C-D")
CString g_sLangID_Native_OutputEFGH;		// = _T("Native_OutputEFGH")
CString g_sLangTxt_Native_OutputEFGH;		// = _T("开出E-F-G-H")
CString g_sLangID_Native_InputOper;			// = _T("Native_InputOper")
CString g_sLangTxt_Native_InputOper;		// = _T("开入操作")
CString g_sLangID_Native_OutputOper;		// = _T("Native_OutputOper")
CString g_sLangTxt_Native_OutputOper;		// = _T("开出操作")
CString g_sLangID_Native_InSel;				// = _T("Native_InSel")
CString g_sLangTxt_Native_InSel;			// = _T("缺少跳闸或重合闸开入选择")
CString g_sLangID_Native_InputOpers;		// = _T("Native_InputOpers")
CString g_sLangTxt_Native_InputOpers;		// = _T("开入操作:")
CString g_sLangID_Native_OutputOpers;		// = _T("Native_OutputOpers")
CString g_sLangTxt_Native_OutputOpers;		// = _T("开出操作:")
CString g_sLangID_Native_OutputA;			//= _T("Native_OutputA");
CString g_sLangTxt_Native_OutputA;			//= _T("开出A");
CString g_sLangID_Native_OutputB;			//= _T("Native_OutputB");
CString g_sLangTxt_Native_OutputB;			//= _T("开出B");
CString g_sLangID_Native_OutputC;			// = _T("Native_OutputC");
CString g_sLangTxt_Native_OutputC;			//= _T("开出C");
CString g_sLangID_Native_OutputD;			//= _T("Native_OutputD");
CString g_sLangTxt_Native_OutputD;			//= _T("开出D");
CString g_sLangID_Native_OutputE;			//= _T("Native_OutputE");
CString g_sLangTxt_Native_OutputE;			//= _T("开出E");
CString g_sLangID_Native_OutputF;			//= _T("Native_OutputF");
CString g_sLangTxt_Native_OutputF;			//= _T("开出F");
CString g_sLangID_Native_OutputG;			//= _T("Native_OutputG");
CString g_sLangTxt_Native_OutputG;			//= _T("开出G");
CString g_sLangID_Native_OutputH;			//= _T("Native_OutputH");
CString g_sLangTxt_Native_OutputH;			//= _T("开出H");

CString g_sLangID_Native_OutputFlipMomentS;			  // = _T("Native_OutputFlipMomentS")
CString g_sLangTxt_Native_OutputFlipMomentS;		  // = _T("开出翻转时刻")
CString g_sLangID_Native_SelMapFile;				  // = _T("Native_SelMapFile")
CString g_sLangTxt_Native_SelMapFile;				  // = _T("选择通道映射文件")
CString g_sLangID_Native_SaveMapFile;				  // = _T("Native_SaveMapFile")
CString g_sLangTxt_Native_SaveMapFile;				  // = _T("通道映射文件另存为")
CString g_sLangID_Native_ExpMapSucc;				  // = _T("Native_ExpMapSucc")
CString g_sLangTxt_Native_ExpMapSucc;				  // = _T("导出通道映射文件[%s]成功.")
CString g_sLangID_Native_ExpMapFail;				  // = _T("Native_ExpMapFail")
CString g_sLangTxt_Native_ExpMapFail;				  // = _T("导出通道映射文件[%s]失败.")
CString g_sLangID_Native_MapPass;					  // = _T("Native_MapPass")
CString g_sLangTxt_Native_MapPass;					  // = _T("通道映射密码")
CString g_sLangID_Native_Pass;						  // = _T("Native_Pass")
CString g_sLangTxt_Native_Pass;						  // = _T("密码:")
CString g_sLangID_Native_EmptyPass;					  // = _T("Native_EmptyPass")
CString g_sLangTxt_Native_EmptyPass;				  // = _T("密码为空,请重新输入.")
CString g_sLangID_Native_WrongPass;					  // = _T("Native_WrongPass")
CString g_sLangTxt_Native_WrongPass;				  // = _T("密码错误,请重新输入.")
CString g_sLangID_Native_RatedVolt;					  // = _T("Native_RatedVolt")
CString g_sLangTxt_Native_RatedVolt;				  // = _T("额定电压(V):")
CString g_sLangID_Native_RatedCurr;					  // = _T("Native_RatedCurr")
CString g_sLangTxt_Native_RatedCurr;				  // = _T("额定电流(A):")
CString g_sLangID_Native_RatedFreq;					  // = _T("Native_RatedFreq")
CString g_sLangTxt_Native_RatedFreq;				  // = _T("额定频率(Hz):")
CString g_sLangID_Native_DebTime;					  // = _T("Native_DebTime")
CString g_sLangTxt_Native_DebTime;					  // = _T("防抖时间(ms):")
CString g_sLangID_Native_PortNum;					  // = _T("Native_PortNum")
CString g_sLangTxt_Native_PortNum;					  // = _T("端口号:")
CString g_sLangID_Native_NetConfig;					  // = _T("Native_NetConfig")
CString g_sLangTxt_Native_NetConfig;				  // = _T("网络配置")
CString g_sLangID_Native_InvalidIPPort;				  // = _T("Native_InvalidIPPort")
CString g_sLangTxt_Native_InvalidIPPort;			  // = _T("IP和端口号输入不合法")
CString g_sLangID_Native_TotalGroups;				  // = _T("Native_TotalGroups")
CString g_sLangTxt_Native_TotalGroups;				  // = _T("总组数: 00")
CString g_sLangID_Native_TotalGroupsParam;			  // = _T("Native_TotalGroupsParam")
CString g_sLangTxt_Native_TotalGroupsParam;			  // = _T("总组数: %1")
CString g_sLangID_Native_CurrentGroupParam;			  // = _T("Native_CurrentGroupParam")
CString g_sLangTxt_Native_CurrentGroupParam;		  // = _T("当前组: %1")
CString g_sLangID_Native_PrevGroups;				  // = _T("Native_PrevGroups")
CString g_sLangTxt_Native_PrevGroups;				  // = _T("←:上一组")
CString g_sLangID_Native_NextGroups;				  // = _T("Native_NextGroups")
CString g_sLangTxt_Native_NextGroups;				  // = _T("→:下一组")
CString g_sLangID_Native_CurrentVersionParam;		  // = _T("Native_CurrentVersionParam")
CString g_sLangTxt_Native_CurrentVersionParam;		  // = _T("当前程序版本(%s).")
CString g_sLangID_Native_TestView;					  // = _T("Native_TestView")
CString g_sLangTxt_Native_TestView;					  // = _T("试验视图")
CString g_sLangID_Native_ReportView;				  // = _T("Native_ReportView")
CString g_sLangTxt_Native_ReportView;				  // = _T("报告视图")
CString g_sLangID_Native_StateHistory;				  // = _T("Native_StateHistory")
CString g_sLangTxt_Native_StateHistory;				  // = _T("状态历史记录")
CString g_sLangID_Native_StatusLight;				  // = _T("Native_StatusLight")
CString g_sLangTxt_Native_StatusLight;				  // = _T("状态灯显示")
CString g_sLangID_Native_StartTestF2;				  // = _T("Native_StartTestF2")
CString g_sLangTxt_Native_StartTestF2;				  // = _T("开始测试(F2)")
CString g_sLangID_Native_StopTestEsc;				  // = _T("Native_StopTestEsc")
CString g_sLangTxt_Native_StopTestEsc;				  // = _T("停止测试(Esc)")
CString g_sLangID_Native_OpenTempFile;				  // = _T("Native_OpenTempFile")
CString g_sLangTxt_Native_OpenTempFile;				  // = _T("打开模板文件")
CString g_sLangID_Native_SaveTempFile;				  // = _T("Native_SaveTempFile")
CString g_sLangTxt_Native_SaveTempFile;				  // = _T("保存模板文件")
CString g_sLangID_Native_ModelParamConfig;			  // = _T("Native_ModelParamConfig")
CString g_sLangTxt_Native_ModelParamConfig;			  // = _T("型号参数配置")
CString g_sLangID_Native_GenParamSetDlg;			  // = _T("Native_GenParamSetDlg")
CString g_sLangTxt_Native_GenParamSetDlg;			  // = _T("通用参数设置对话框")
CString g_sLangID_Native_SetValueParamSetDlg;		  // = _T("Native_SetValueParamSetDlg")
CString g_sLangTxt_Native_SetValueParamSetDlg;		  // = _T("整定值参数设置对话框")
CString g_sLangID_Native_SwitchValSetDlg;			  // = _T("Native_SwitchValSetDlg")
CString g_sLangTxt_Native_SwitchValSetDlg;			  // = _T("开关量设置对话框")
CString g_sLangID_Native_NetConnect;				  // = _T("Native_NetConnect")
CString g_sLangTxt_Native_NetConnect;				  // = _T("网络连接")
CString g_sLangID_Native_NetConnectDlg;				  // = _T("Native_NetConnectDlg")
CString g_sLangTxt_Native_NetConnectDlg;			  // = _T("网络连接对话框")
CString g_sLangID_Native_ChResMapDlg;				  // = _T("Native_ChResMapDlg")
CString g_sLangTxt_Native_ChResMapDlg;				  // = _T("通道资源映射对话框")
CString g_sLangID_Native_DCSet;						  // = _T("Native_DCSet")
CString g_sLangTxt_Native_DCSet;					  // = _T("直流设置")
CString g_sLangID_Native_AuxDCSetDlg;				  // = _T("Native_AuxDCSetDlg")
CString g_sLangTxt_Native_AuxDCSetDlg;				  // = _T("辅助直流设置对话框")
CString g_sLangID_Native_OutputPower;				  // = _T("Native_OutputPower")
CString g_sLangTxt_Native_OutputPower;				  // = _T("输出功率")
CString g_sLangID_Native_OutputPowerSetDlg;			  // = _T("Native_OutputPowerSetDlg")
CString g_sLangTxt_Native_OutputPowerSetDlg;		  // = _T("输出功率设置对话框")
CString g_sLangID_Native_SteadyOutput;				  // = _T("Native_SteadyOutput")
CString g_sLangTxt_Native_SteadyOutput;				  // = _T("稳态输出")
CString g_sLangID_Native_ACDCSteadyOutput;			  // = _T("Native_ACDCSteadyOutput")
CString g_sLangTxt_Native_ACDCSteadyOutput;			  // = _T("交直流稳态输出")
CString g_sLangID_Native_ReportSet;					  // = _T("Native_ReportSet")
CString g_sLangTxt_Native_ReportSet;				  // = _T("报告设置")
CString g_sLangID_Native_ReportParamSet;			  // = _T("Native_ReportParamSet")
CString g_sLangTxt_Native_ReportParamSet;			  // = _T("报告参数设置")
CString g_sLangID_Native_ShowTestView;				  // = _T("Native_ShowTestView")
CString g_sLangTxt_Native_ShowTestView;				  // = _T("显示试验视图")
CString g_sLangID_Native_ShowReportView;			  // = _T("Native_ShowReportView")
CString g_sLangTxt_Native_ShowReportView;			  // = _T("显示报告视图")
CString g_sLangID_Native_StateLightView;			  // = _T("Native_StateLightView")
CString g_sLangTxt_Native_StateLightView;			  // = _T("状态灯视图")
CString g_sLangID_Native_ShowStateLightView;		  // = _T("Native_ShowStateLightView")
CString g_sLangTxt_Native_ShowStateLightView;		  // = _T("显示状态灯视图")
CString g_sLangID_Native_StateHistoryView;			  // = _T("Native_StateHistoryView")
CString g_sLangTxt_Native_StateHistoryView;			  // = _T("状态历史视图")
CString g_sLangID_Native_ShowStateHistoryView;		  // = _T("Native_ShowStateHistoryView")
CString g_sLangTxt_Native_ShowStateHistoryView;		  // = _T("显示状态历史视图")
CString g_sLangID_Native_CurrentTesterVersionInfo;	  // = _T("Native_CurrentTesterVersionInfo")
CString g_sLangTxt_Native_CurrentTesterVersionInfo;	  // = _T("当前测试仪版本信息")
CString g_sLangID_Native_UpdateSoftwares;			  // = _T("Native_UpdateSoftware")
CString g_sLangTxt_Native_UpdateSoftwares;			  // = _T("更新软件")
CString g_sLangID_Native_UpdateHostSoftware;		  // = _T("Native_UpdateHostSoftware")
CString g_sLangTxt_Native_UpdateHostSoftware;		  // = _T("更新上位机软件")
CString g_sLangID_Native_UpdateLowerLayer;			  // = _T("Native_UpdateLowerLayer")
CString g_sLangTxt_Native_UpdateLowerLayer;			  // = _T("更新底层")
CString g_sLangID_Native_UpdateTesterLowerProgram;	  // = _T("Native_UpdateTesterLowerProgram")
CString g_sLangTxt_Native_UpdateTesterLowerProgram;	  // = _T("更新测试仪底层程序")
CString g_sLangID_Native_MessageDetection;			  // = _T("Native_MessageDetection")
CString g_sLangTxt_Native_MessageDetection;			  // = _T("报文探测")
CString g_sLangID_Native_Report;					  // = _T("Native_Report")
CString g_sLangTxt_Native_Report;					  // = _T("报告")
CString g_sLangID_Native_Start;						  // = _T("Native_Start")
CString g_sLangTxt_Native_Start;					  // = _T("开始")
CString g_sLangID_Native_SysParamConfigDialog;		  // = _T("Native_SysParamConfigDialog")
CString g_sLangTxt_Native_SysParamConfigDialog;		  // = _T("系统参数配置对话框")
CString g_sLangID_Native_OfflineSelection;			  // = _T("Native_OfflineSelection")
CString g_sLangTxt_Native_OfflineSelection;			  // = _T("脱机选择")
CString g_sLangID_Native_OfflineSelectTesterModelSN;  // = _T("Native_OfflineSelectTesterModelSN")
CString g_sLangTxt_Native_OfflineSelectTesterModelSN; // = _T("脱机选择测试仪型号、SN")
CString g_sLangID_Native_Date1970;					  // = _T("Native_Date1970")
CString g_sLangTxt_Native_Date1970;					  // = _T("1970年1月1日 00:00:00")
CString g_sLangID_Native_ConnectionStatus;			  // = _T("Native_ConnectionStatus")
CString g_sLangTxt_Native_ConnectionStatus;			  // = _T("连接状态：")
CString g_sLangID_Native_SyncTime;					  // = _T("Native_SyncTime")
CString g_sLangTxt_Native_SyncTime;					  // = _T("对时")
CString g_sLangID_Native_FileSaveSuccess;			  // = _T("Native_FileSaveSuccess")
CString g_sLangTxt_Native_FileSaveSuccess;			  // = _T("文件[%1]保存成功.")
CString g_sLangID_Native_FileSaveFail;				  // = _T("Native_FileSaveFail")
CString g_sLangTxt_Native_FileSaveFail;				  // = _T("文件[%1]保存失败.")
CString g_sLangID_Native_DefParamFileSaveSuccess;	  // = _T("Native_DefParamFileSaveSuccess")
CString g_sLangTxt_Native_DefParamFileSaveSuccess;	  // = _T("默认参数文件[%1]保存成功.")
CString g_sLangID_Native_DefParamFileSaveFail;		  // = _T("Native_DefParamFileSaveFail")
CString g_sLangTxt_Native_DefParamFileSaveFail;		  // = _T("默认参数文件[%1]保存失败.")
CString g_sLangID_Native_OutputMaxExceedDesign;		  // = _T("Native_OutputMaxExceedDesign")
CString g_sLangTxt_Native_OutputMaxExceedDesign;	  // = _T("输出最大值超设计")
CString g_sLangID_Native_ReModifyHarmonicValue;		  // = _T("Native_ReModifyHarmonicValue")
CString g_sLangTxt_Native_ReModifyHarmonicValue;	  // = _T("请重新修改谐波含量的值！")
CString g_sLangID_Native_LastTestCannotContinue;	  // = _T("Native_LastTestCannotContinue")
CString g_sLangTxt_Native_LastTestCannotContinue;	  // = _T("当前已经是最后一个测试下,无法继续测试.")
CString g_sLangID_Native_SystemParamSetComplete;	  // = _T("Native_SystemParamSetComplete")
CString g_sLangTxt_Native_SystemParamSetComplete;	  // = _T("系统参数设置下发完成")
CString g_sLangID_Native_SystemParamSetFailed;		  // = _T("Native_SystemParamSetFailed")
CString g_sLangTxt_Native_SystemParamSetFailed;		  // = _T("系统参数设置下发失败")
CString g_sLangID_Native_TestStopped;				  // = _T("Native_TestStopped")
CString g_sLangTxt_Native_TestStopped;				  // = _T("测试停止")
CString g_sLangID_Native_StopCommandFailed;			  // = _T("Native_StopCommandFailed")
CString g_sLangTxt_Native_StopCommandFailed;		  // = _T("停止命令下发失败")
CString g_sLangID_Native_ConnectionFailed;			  // = _T("Native_ConnectionFailed")
CString g_sLangTxt_Native_ConnectionFailed;			  // = _T("联机失败,无法下发系统参数.")
CString g_sLangID_Native_ModuleSwitchDone;			  // = _T("Native_ModuleSwitchDone")
CString g_sLangTxt_Native_ModuleSwitchDone;			  // = _T("模块档位切换命令下发完成")
CString g_sLangID_Native_ModuleSwitchFail;			  // = _T("Native_ModuleSwitchFail")
CString g_sLangTxt_Native_ModuleSwitchFail;			  // = _T("模块档位切换命令下发失败")
CString g_sLangID_Native_AuxDCOutDone;				  // = _T("Native_AuxDCOutDone")
CString g_sLangTxt_Native_AuxDCOutDone;				  // = _T("辅助直流输出命令下发完成")
CString g_sLangID_Native_AuxDCOutFail;				  // = _T("Native_AuxDCOutFail")
CString g_sLangTxt_Native_AuxDCOutFail;				  // = _T("辅助直流输出命令下发失败")
// CString g_sLangID_Native_ConnectFail;				  // = _T("Native_ConnectFail")
// CString g_sLangTxt_Native_ConnectFail;				  // = _T("与当前测试仪建立连接失败(%s).")
CString g_sLangID_Native_StartSteadyOut;			  // = _T("Native_StartSteadyOut")
CString g_sLangTxt_Native_StartSteadyOut;			  // = _T("开始稳态量输出")
CString g_sLangID_Native_StopSteadyOut;				  // = _T("Native_StopSteadyOut")
CString g_sLangTxt_Native_StopSteadyOut;			  // = _T("停止稳态量输出")

CString g_sLangID_Native_StopSOETest;				  // = _T("Native_StopSOETest")
CString g_sLangTxt_Native_StopSOETest;				  // = _T("停止SOE测试输出")
CString g_sLangID_Native_ExportWord;				  // = _T("Native_ExportWord")
CString g_sLangTxt_Native_ExportWord;				  // = _T("导出word文件")
CString g_sLangID_Native_ReportTypes;				  // = _T("Native_ReportTypes")
CString g_sLangTxt_Native_ReportTypes;				  // = _T("Word97-2003报告(*.doc);;Word报告(*.docx);;HTML报告(*.html);;PDF报告(*.pdf)")
CString g_sLangID_Native_SaveReportSuccess;			  // = _T("Native_SaveReportSuccess")
CString g_sLangTxt_Native_SaveReportSuccess;		  // = _T("网页报告(%s)保存成功.")
CString g_sLangID_Native_SavePDFSuccess;			  // = _T("Native_SavePDFSuccess")
CString g_sLangTxt_Native_SavePDFSuccess;			  // = _T("PDF报告文件(%s)保存成功.")
CString g_sLangID_Native_SavePDFFailure;			  // = _T("Native_SavePDFFailure")
CString g_sLangTxt_Native_SavePDFFailure;			  // = _T("PDF报告文件(%s)保存失败.")
CString g_sLangID_Native_SaveWordSuccess;			  // = _T("Native_SaveWordSuccess")
CString g_sLangTxt_Native_SaveWordSuccess;			  // = _T("WORD报告文件(%s)保存成功.")
CString g_sLangID_Native_SaveWordFailure;			  // = _T("Native_SaveWordFailure")
CString g_sLangTxt_Native_SaveWordFailure;			  // = _T("WORD报告文件(%s)保存失败.")
CString g_sLangID_Native_TestRunning;				  // = _T("Native_TestRunning")
CString g_sLangTxt_Native_TestRunning;				  // = _T("正在运行中,是否停止测试?")
CString g_sLangID_Native_UnsavedTemplate;			  // = _T("Native_UnsavedTemplate")
CString g_sLangTxt_Native_UnsavedTemplate;			  // = _T("测试模板未保存,是否保存?")
CString g_sLangID_Native_HarmonicExceedValue;		  // = _T("Native_HarmonicExceedValue")
CString g_sLangTxt_Native_HarmonicExceedValue;		  // = _T("谐波含量超约定值")
CString g_sLangID_Native_DeleteAll;					  // = _T("Native_DeleteAll")
CString g_sLangTxt_Native_DeleteAll;				  // = _T("删除全部")
CString g_sLangID_Native_VarName;					  // = _T("Native_VarName")
CString g_sLangTxt_Native_VarName;					  // = _T("变量名称")

// 第四周吕
CString g_sLangID_Native_voltagev;
CString g_sLangTxt_Native_voltagev; // 电压（V）：
CString g_sLangID_Native_currentc;
CString g_sLangTxt_Native_currentc; // 电流(A):
CString g_sLangID_Native_phasep;
CString g_sLangTxt_Native_phasep; // 相位差(°):
CString g_sLangID_Native_initialCurrent;
CString g_sLangTxt_Native_initialCurrent; // 电流变化始值(I*):
CString g_sLangID_Native_finalCurrent;
CString g_sLangTxt_Native_finalCurrent; // 电流变化终值(I*):
CString g_sLangID_Native_CurstepSize;
CString g_sLangTxt_Native_CurstepSize; // 电流变化步长(I*):
CString g_sLangID_Native_currentcI;
CString g_sLangTxt_Native_currentcI; // 电流(I*):
CString g_sLangID_Native_referenceValue;
CString g_sLangTxt_Native_referenceValue; // 基准值:
CString g_sLangID_Native_ctPolarityDef;
CString g_sLangTxt_Native_ctPolarityDef; // CT正极性定义:
CString g_sLangID_Native_charaDef;
CString g_sLangTxt_Native_charaDef; // 特性定义
CString g_sLangID_Native_timerLimit1;
CString g_sLangTxt_Native_timerLimit1; // 1段定时限:
CString g_sLangID_Native_timerLimit2;
CString g_sLangTxt_Native_timerLimit2; // 2段定时限:
CString g_sLangID_Native_timerLimit3;
CString g_sLangTxt_Native_timerLimit3; // 3段定时限:

// ui5
CString g_sLangID_Native_singleP;
CString g_sLangTxt_Native_singleP; // 单相
CString g_sLangID_Native_impedanceSelection;
CString g_sLangTxt_Native_impedanceSelection; // 阻抗选择:
CString g_sLangID_Native_times;
CString g_sLangTxt_Native_times; // 倍
CString g_sLangID_Native_impedanceRepresent;
CString g_sLangTxt_Native_impedanceRepresent; // 阻抗表示方式:
CString g_sLangID_Native_timeConstant;
CString g_sLangTxt_Native_timeConstant; // 时间定值(s):
CString g_sLangID_Native_triggerTiming;
CString g_sLangTxt_Native_triggerTiming; // 触发时刻:
CString g_sLangID_Native_h;
CString g_sLangTxt_Native_h; // 时
CString g_sLangID_Native_m;
CString g_sLangTxt_Native_m; // 分
CString g_sLangID_Native_s;
CString g_sLangTxt_Native_s; // 秒

// ui6
CString g_sLangID_Native_PreChangeVol;
CString g_sLangTxt_Native_PreChangeVol; // 变化前电压(V):
CString g_sLangID_Native_PreChangeCur;
CString g_sLangTxt_Native_PreChangeCur; // 变化前电流(A)：
CString g_sLangID_Native_PreChangeFreq;
CString g_sLangTxt_Native_PreChangeFreq; // 变化前频率(HZ)：
CString g_sLangID_Native_variableType;
CString g_sLangTxt_Native_variableType; //
CString g_sLangID_Native_variable0;
CString g_sLangTxt_Native_variable0; //

CString g_sLangID_Native_currentG1;
CString g_sLangTxt_Native_currentG1; // 电流(G1)(A)：
CString g_sLangID_Native_currentG2;
CString g_sLangTxt_Native_currentG2; // 电流(G2)(A)：
CString g_sLangID_Native_voltageG1;
CString g_sLangTxt_Native_voltageG1; // 电压(G1)(V)：
CString g_sLangID_Native_voltageG2;
CString g_sLangTxt_Native_voltageG2; // 电压(G2)(V)：
CString g_sLangID_Native_currentDif;
CString g_sLangTxt_Native_currentDif; // 电流相差(G1,G2)(°):

CString g_sLangID_Native_normalState;
CString g_sLangTxt_Native_normalState; // 常态:
CString g_sLangID_Native_faultState;
CString g_sLangTxt_Native_faultState; // 故障态:

CString g_sLangID_Native_directChange;
CString g_sLangTxt_Native_directChange; // 递变方向：

CString g_sLangID_Native_relativeErrorl;
CString g_sLangTxt_Native_relativeErrorl; // 相对误差<
CString g_sLangID_Native_returnCoefficientb;
CString g_sLangTxt_Native_returnCoefficientb; // 返回系数>
CString g_sLangID_Native_judgmentCondition;
CString g_sLangTxt_Native_judgmentCondition; // 判定条件
CString g_sLangID_Native_express;
CString g_sLangTxt_Native_express; // 表达式：

// ui7
CString g_sLangID_Native_clear0;
CString g_sLangTxt_Native_clear0;
CString g_sLangID_Native_changeSettings;
CString g_sLangTxt_Native_changeSettings;
CString g_sLangID_Native_changeTime;
CString g_sLangTxt_Native_changeTime;
CString g_sLangID_Native_baseFrequency;
CString g_sLangTxt_Native_baseFrequency; // 基波频率(Hz):
CString g_sLangID_Native_openSettings;
CString g_sLangTxt_Native_openSettings;
CString g_sLangID_Native_harmDataBatchSet;
CString g_sLangTxt_Native_harmDataBatchSet; // 谐波数据批量设置:
CString g_sLangID_Native_channelContain;
CString g_sLangTxt_Native_channelContain; // 通道含有率(%):
CString g_sLangID_Native_channelPhase;
CString g_sLangTxt_Native_channelPhase; // 通道相位(°):

// goose
CString g_sLangID_Native_forceNumberOutput;
CString g_sLangTxt_Native_forceNumberOutput; // 当前模块需要支持数字量输出功能,强制设置为数字量输出模式.
CString g_sLangID_Native_notSupportNumOutput;
CString g_sLangTxt_Native_notSupportNumOutput; // 当前测试仪不支持数字量输出功能,无法使用GOOSE异常模拟试验.
CString g_sLangID_Native_PonovogooseSim;
CString g_sLangTxt_Native_PonovogooseSim; // Ponovo GOOSE异常模拟
CString g_sLangID_Native_welgooseSim;
CString g_sLangTxt_Native_welgooseSim; // 欢迎使用GOOSE异常模拟试验.
CString g_sLangID_Native_JumpA;
CString g_sLangTxt_Native_JumpA; // 跳A
CString g_sLangID_Native_JumpB;
CString g_sLangTxt_Native_JumpB; // 跳B
CString g_sLangID_Native_JumpC;
CString g_sLangTxt_Native_JumpC; // 跳C
CString g_sLangID_Native_JumpD;
CString g_sLangTxt_Native_JumpD; // 跳D
CString g_sLangID_Native_JumpE;
CString g_sLangTxt_Native_JumpE; // 跳E
CString g_sLangID_Native_JumpF;
CString g_sLangTxt_Native_JumpF; // 跳F
CString g_sLangID_Native_JumpG;
CString g_sLangTxt_Native_JumpG; // 跳G
CString g_sLangID_Native_JumpH;
CString g_sLangTxt_Native_JumpH; // 跳H
CString g_sLangID_Native_JumpI;
CString g_sLangTxt_Native_JumpI; // 跳I
CString g_sLangID_Native_JumpJ;
CString g_sLangTxt_Native_JumpJ; // 跳J
CString g_sLangID_Native_STSS1234;
CString g_sLangTxt_Native_STSS1234; // 状态%1,输出时间=%2,StNum=%3,SqNum=%4

// channelParaset
CString g_sLangID_Native_amplitudeV;
CString g_sLangTxt_Native_amplitudeV; // 幅值(V)
CString g_sLangID_Native_amplitudeKV;
CString g_sLangTxt_Native_amplitudeKV; // 幅值(KV)
CString g_sLangID_Native_amplitudeA;
CString g_sLangTxt_Native_amplitudeA; // 幅值(A)
CString g_sLangID_Native_overflowV;
CString g_sLangTxt_Native_overflowV; // 谐波设置值%f(%d,%d)与基波的叠加超出范围(%fV).
CString g_sLangID_Native_overflowA;
CString g_sLangTxt_Native_overflowA; // 谐波设置值%f(%d,%d)与基波的叠加超出范围(%fA).
CString g_sLangID_Native_input_overrange;
CString g_sLangTxt_Native_input_overrange; // 输入值%f(%d,%d)超出范围(%f).
CString g_sLangID_Native_flowoverV;
CString g_sLangTxt_Native_flowoverV; // 基波设置值%f(%d,%d)与谐波的叠加超出范围(%fV).
CString g_sLangID_Native_flowoverA;
CString g_sLangTxt_Native_flowoverA; // 基波设置值%f(%d,%d)与谐波的叠加超出范围(%fA).
CString g_sLangID_Native_all_frequencies;
CString g_sLangTxt_Native_all_frequencies; // 等全部频率
CString g_sLangID_Native_smallsignal;
CString g_sLangTxt_Native_smallsignal; // 小信号
CString g_sLangID_Native_illchannelname;
CString g_sLangTxt_Native_illchannelname; // 递变通道名【%s】非法

// 第四周马
// DifferTest_Trans 马
/*tr("差动试验模板文件")*/
CString g_sLangID_Native_DifTestTempFile;
CString g_sLangTxt_Native_DifTestTempFile;
/*_T("欢迎使用差动测试.")*/
CString g_sLangID_Native_WelToDiffTest;
CString g_sLangTxt_Native_WelToDiffTest;
/*tr("Ponovo 差动")*/
CString g_sLangID_Native_PonovoDiff;
CString g_sLangTxt_Native_PonovoDiff;
/*tr("差动")*/
CString g_sLangID_Native_Differential;
CString g_sLangTxt_Native_Differential;
/*tr("特征曲线图")*/
CString g_sLangID_Native_CurveGraph;
CString g_sLangTxt_Native_CurveGraph;
/*tr("接线图")*/
CString g_sLangID_Native_WireDiagram;
CString g_sLangTxt_Native_WireDiagram;
/*tr("没有选择目标删除项!")*/
CString g_sLangID_Native_NoTgtDelItem;
CString g_sLangTxt_Native_NoTgtDelItem;
/*tr("此测试类型至少保留一个测试项！")*/
CString g_sLangID_Native_AtLeast1Test;
CString g_sLangTxt_Native_AtLeast1Test;
/*_T("联机失败[%s][%ld].")*/
CString g_sLangID_Native_OnlineFailSy;
CString g_sLangTxt_Native_OnlineFailSy;
/*tr("通道映射文件下发完成")*/
CString g_sLangID_Native_ChnlMapFileDone;
CString g_sLangTxt_Native_ChnlMapFileDone;
/*tr("通道映射文件下发失败")*/
CString g_sLangID_Native_ChMapFileErr;
CString g_sLangTxt_Native_ChMapFileErr;
/*tr("系统参数设置下发完成")*/
CString g_sLangID_Native_SysParamSetDone;
CString g_sLangTxt_Native_SysParamSetDone;
/*tr("系统参数设置下发失败")*/
CString g_sLangID_Native_SysParamErr;
CString g_sLangTxt_Native_SysParamErr;
/*tr("IEC参数设置下发完成")*/
CString g_sLangID_Native_IECParamSetDone;
CString g_sLangTxt_Native_IECParamSetDone;
/*tr("IEC参数设置执行超时")*/
CString g_sLangID_Native_IECParamTimeout;
CString g_sLangTxt_Native_IECParamTimeout;
/*tr("IEC参数设置执行失败")*/
CString g_sLangID_Native_IECParamFail;
CString g_sLangTxt_Native_IECParamFail;
/*tr("开始测试.")*/
CString g_sLangID_Native_StartTestSy;
CString g_sLangTxt_Native_StartTestSy;
/*tr("开始测试命令下发失败.")*/
CString g_sLangID_Native_StartTestCmdFail;
CString g_sLangTxt_Native_StartTestCmdFail;
/*tr("没有选择测试项.")*/
CString g_sLangID_Native_NoTestItemSy;
CString g_sLangTxt_Native_NoTestItemSy;
/*tr("在Id-Ir平面上双击鼠标，设置测试项的制动电流值")*/
CString g_sLangID_Native_SetTestItemCurrent;
CString g_sLangTxt_Native_SetTestItemCurrent;

/*_T("基准电流(其它)")*/
CString g_sLangID_Native_RefCurrentOther;
CString g_sLangTxt_Native_RefCurrentOther;
/*_T("差动速断电流定值")*/
CString g_sLangID_Native_DfRelayCurrSet;
CString g_sLangTxt_Native_DfRelayCurrSet;
/*_T("差动动作电流门槛值")*/
CString g_sLangID_Native_DfActThresh;
CString g_sLangTxt_Native_DfActThresh;
/*_T("比率制动特性拐点数")*/
CString g_sLangID_Native_RatioBrkPntCnt;
CString g_sLangTxt_Native_RatioBrkPntCnt;
/*_T("比率制动特性拐点1电流")*/
CString g_sLangID_Native_RatioBrkPt1Curr;
CString g_sLangTxt_Native_RatioBrkPt1Curr;
/*_T("比率制动特性拐点2电流")*/
CString g_sLangID_Native_RatioBrkPt2Curr;
CString g_sLangTxt_Native_RatioBrkPt2Curr;
/*_T("比率制动特性拐点3电流")*/
CString g_sLangID_Native_RatioBrkPt3Curr;
CString g_sLangTxt_Native_RatioBrkPt3Curr;

/*_T("差动电流值(%f),超越上限")*/
CString g_sLangID_Native_DiffCurrExceedsLimit;
CString g_sLangTxt_Native_DiffCurrExceedsLimit;
/*tr("参数更新成功.")*/
CString g_sLangID_Native_ParamsUpdated;
CString g_sLangTxt_Native_ParamsUpdated;
/*tr("参数更新失败.")*/
CString g_sLangID_Native_ParamsUpdateFailed;
CString g_sLangTxt_Native_ParamsUpdateFailed;
/*_T("差动电流值已降低为0,无法再减小")*/
CString g_sLangID_Native_DiffCurrReducedToZero;
CString g_sLangTxt_Native_DiffCurrReducedToZero;
/*QObject::tr("比率制动系数一")*/
CString g_sLangID_Native_RatioBrkCoef1;
CString g_sLangTxt_Native_RatioBrkCoef1;
/*QObject::tr("比率制动系数二")*/
CString g_sLangID_Native_RatioBrkCoef2;
CString g_sLangTxt_Native_RatioBrkCoef2;
/*QObject::tr("比率制动系数三")*/
CString g_sLangID_Native_RatioBrkCoef3;
CString g_sLangTxt_Native_RatioBrkCoef3;


/*_T("手动计算输入平衡系数方式时如果整定值选择标幺值，则基准电流不可选择高侧二次额定电流.")*/
CString g_sLangID_Native_ManInBalCoeffNoHi;
CString g_sLangTxt_Native_ManInBalCoeffNoHi;
/*_T("手动计算输入平衡系数方式时如果整定值选择标幺值，则基准电流不可选择各侧二次额定电流.")*/
CString g_sLangID_Native_ManInBalCoeffNoBe;
CString g_sLangTxt_Native_ManInBalCoeffNoBe;
/*"差流理论值"*/
CString g_sLangID_Native_DiffCurrentTheory;
CString g_sLangTxt_Native_DiffCurrentTheory;
/*"<h1>差动6I</h1>"*/
CString g_sLangID_Native_Diff6I;
CString g_sLangTxt_Native_Diff6I;
/*"<h2>测试结果</h2>"*/
CString g_sLangID_Native_TestResultSy;
CString g_sLangTxt_Native_TestResultSy;
/*"未知类别"*/
CString g_sLangID_Native_UnkCat;
CString g_sLangTxt_Native_UnkCat;
/*"自动计算"*/
CString g_sLangID_Native_AutoCalc;
CString g_sLangTxt_Native_AutoCalc;
/*"手动计算并输入"*/
CString g_sLangID_Native_ManCalcInput;
CString g_sLangTxt_Native_ManCalcInput;
/*"高-低"*/
CString g_sLangID_Native_HighLow;
CString g_sLangTxt_Native_HighLow;
/*"高-中"*/
CString g_sLangID_Native_HighMid;
CString g_sLangTxt_Native_HighMid;
/*"中-低"*/
CString g_sLangID_Native_MidLow;
CString g_sLangTxt_Native_MidLow;
/*"二分法"*/
CString g_sLangID_Native_BinSearch;
CString g_sLangTxt_Native_BinSearch;
/*"单步逼近"*/
CString g_sLangID_Native_StepApprox;
CString g_sLangTxt_Native_StepApprox;
/*"有名值"*/
CString g_sLangID_Native_NameValue;
CString g_sLangTxt_Native_NameValue;
/*"标幺值"*/
CString g_sLangID_Native_PerUnitVal;
CString g_sLangTxt_Native_PerUnitVal;
/*"高侧二次额定电流"*/
CString g_sLangID_Native_HighSideSecRatedCurr;
CString g_sLangTxt_Native_HighSideSecRatedCurr;
/*"各侧二次额定电流"*/
CString g_sLangID_Native_BeSideSecRatedCurr;
CString g_sLangTxt_Native_BeSideSecRatedCurr;
/*"设定值"*/
CString g_sLangID_Native_Setpt;
CString g_sLangTxt_Native_Setpt;
/*"一个拐点"*/
CString g_sLangID_Native_OneTurnPoint;
CString g_sLangTxt_Native_OneTurnPoint;
/*"二个拐点"*/
CString g_sLangID_Native_TwoTurnPoint;
CString g_sLangTxt_Native_TwoTurnPoint;
/*"三个拐点"*/
CString g_sLangID_Native_ThreeTurnPoint;
CString g_sLangTxt_Native_ThreeTurnPoint;
/*tr("变化始值(In):")*/
CString g_sLangID_Native_InitValChange;
CString g_sLangTxt_Native_InitValChange;
/*tr("变化终值(In):")*/
CString g_sLangID_Native_EndValChange;
CString g_sLangTxt_Native_EndValChange;
/*tr("变化步长(In):")*/
CString g_sLangID_Native_ChgStep;
CString g_sLangTxt_Native_ChgStep;
/*tr("Ⅰ侧平衡系数")*/
CString g_sLangID_Native_SglSideBalCoeff;
CString g_sLangTxt_Native_SglSideBalCoeff;
/*tr("Ⅱ侧平衡系数")*/
CString g_sLangID_Native_TwoSideBalCoeff;
CString g_sLangTxt_Native_TwoSideBalCoeff;
/*tr("Ⅲ侧平衡系数")*/
CString g_sLangID_Native_ThreeSideBalCoeff;
CString g_sLangTxt_Native_ThreeSideBalCoeff;
/*tr("接线系数")*/
CString g_sLangID_Native_WiringCoeff;
CString g_sLangTxt_Native_WiringCoeff;
/*tr("基准电流")*/
CString g_sLangID_Native_RefCurr;
CString g_sLangTxt_Native_RefCurr;
/*tr("   高压侧   ")*/
CString g_sLangID_Native_HighVoltSide;
CString g_sLangTxt_Native_HighVoltSide;
/*tr("   中压侧   ")*/
CString g_sLangID_Native_MedVoltSide;
CString g_sLangTxt_Native_MedVoltSide;
/*tr("   低压侧   ")*/
CString g_sLangID_Native_LowVoltSide;
CString g_sLangTxt_Native_LowVoltSide;
/*tr("差动保护电流端子")*/
CString g_sLangID_Native_DiffProtCurrTerm;
CString g_sLangTxt_Native_DiffProtCurrTerm;
/*tr("继电保护测试仪")*/
CString g_sLangID_Native_RelayTest;
CString g_sLangTxt_Native_RelayTest;
/*tr("制动电流=%1A,")*/
CString g_sLangID_Native_BrakeCurrSy;
CString g_sLangTxt_Native_BrakeCurrSy;
/*tr("差动电流=%1A,")*/
CString g_sLangID_Native_DiffCurrSy;
CString g_sLangTxt_Native_DiffCurrSy;
/*tr("比例制动系数=%1")*/
CString g_sLangID_Native_PropBrakeCoeffSy;
CString g_sLangTxt_Native_PropBrakeCoeffSy;
/*tr("制动电流=%1In,")*/
CString g_sLangID_Native_BrakeCurrSyy;
CString g_sLangTxt_Native_BrakeCurrSyy;
/*tr("差动电流=%1In,")*/
CString g_sLangID_Native_DiffCurrSyy;
CString g_sLangTxt_Native_DiffCurrSyy;
/*tr("测试过程监视图")*/
CString g_sLangID_Native_TestProcMonView;
CString g_sLangTxt_Native_TestProcMonView;
/*tr("矢量图")*/
CString g_sLangID_Native_VecGraphics;
CString g_sLangTxt_Native_VecGraphics;
/*tr("线电压")*/
CString g_sLangID_Native_LineVolt;
CString g_sLangTxt_Native_LineVolt;
/*tr("信息图")*/
CString g_sLangID_Native_InfoChart;
CString g_sLangTxt_Native_InfoChart;
/*tr("功率图")*/
CString g_sLangID_Native_PowerChart;
CString g_sLangTxt_Native_PowerChart;
/*tr("动作特性曲线")*/
CString g_sLangID_Native_CharactCurve;
CString g_sLangTxt_Native_CharactCurve;
/*tr("搜索上限(A)")*/
CString g_sLangID_Native_SearchUpperLimit;
CString g_sLangTxt_Native_SearchUpperLimit;
/*tr("搜索下限(A)")*/
CString g_sLangID_Native_SearchLowerLimit;
CString g_sLangTxt_Native_SearchLowerLimit;
/*tr("请输入有效数字！")*/
CString g_sLangID_Native_EnterValidNumber;
CString g_sLangTxt_Native_EnterValidNumber;
/*_T("输入制动电流值[%f]不在有效范围.")*/
CString g_sLangID_Native_InputBrakeCurrOutOfRange;
CString g_sLangTxt_Native_InputBrakeCurrOutOfRange;
/*tr("准备时间(S)")*/
CString g_sLangID_Native_PrepTime;
CString g_sLangTxt_Native_PrepTime;

/*tr("各侧平衡系数")*/
CString g_sLangID_Native_BalanceCoeffEachSide;
CString g_sLangTxt_Native_BalanceCoeffEachSide;

/*tr("测试绕组")*/
CString g_sLangID_Native_TestWinding;
CString g_sLangTxt_Native_TestWinding;




// 插入系列
CString g_sLangID_Native_InsSeries;
CString g_sLangTxt_Native_InsSeries;
// 试验结果及评估
CString g_sLangID_Native_TestResEval;
CString g_sLangTxt_Native_TestResEval;
// 误  差
CString g_sLangID_Native_ErrBlank;
CString g_sLangTxt_Native_ErrBlank;
// 制  动  电  流
CString g_sLangID_Native_BrkCurrBlank;
CString g_sLangTxt_Native_BrkCurrBlank;

// 第五周许
// xwd 5
CString g_sLangID_Native_BrakingCurrent;   // = _T("Native_BrakingCurrent")
CString g_sLangTxt_Native_BrakingCurrent;  // = _T("制动电流(In)")
CString g_sLangID_Native_SearchUpper;	   // = _T("Native_SearchUpper")
CString g_sLangTxt_Native_SearchUpper;	   // = _T("搜索上限(In)")
CString g_sLangID_Native_SearchLower;	   // = _T("Native_SearchLower")
CString g_sLangTxt_Native_SearchLower;	   // = _T("搜索下限(In)")
CString g_sLangID_Native_TestPrecisionA;   // = _T("Native_TestPrecisionA")
CString g_sLangTxt_Native_TestPrecisionA;  // = _T("测试精度(A)")
CString g_sLangID_Native_TestPrecisionIn;  // = _T("Native_TestPrecisionIn")
CString g_sLangTxt_Native_TestPrecisionIn; // = _T("测试精度(In)")
CString g_sLangID_Native_StartCurrent;	   // = _T("Native_StartCurrent")
CString g_sLangTxt_Native_StartCurrent;	   // = _T("启动电流(A)")
CString g_sLangID_Native_StartCurrentIn;   // = _T("Native_StartCurrentIn")
CString g_sLangTxt_Native_StartCurrentIn;  // = _T("启动电流(In)")
CString g_sLangID_Native_DiffCurrentIn;	   //= _T("Native_DiffCurrentIn");
CString g_sLangTxt_Native_DiffCurrentIn;   //= _T("差动电流(In)");
CString g_sLangID_Native_BrkCur;		   // = _T("Native_BrkCur")
CString g_sLangTxt_Native_BrkCur;		   // = _T("速断电流(A)")
CString g_sLangID_Native_BrkCurIn;		   // = _T("Native_BrkCurIn")
CString g_sLangTxt_Native_BrkCurIn;		   // = _T("速断电流(In)")
CString g_sLangID_Native_SrchUpLimA;	   // = _T("Native_SrchUpLimA")
CString g_sLangTxt_Native_SrchUpLimA;	   // = _T("搜索上限(A)")
CString g_sLangID_Native_SrchLowLimA;	   // = _T("Native_SrchLowLimA")
CString g_sLangTxt_Native_SrchLowLimA;	   // = _T("搜索下限(A)")
CString g_sLangID_Native_ValidNum;		   // = _T("Native_ValidNum")
CString g_sLangTxt_Native_ValidNum;		   // = _T("请输入有效数字！")

// 第五周吕
// exswitchset
CString g_sLangID_Native_BinEx20;
CString g_sLangTxt_Native_BinEx20; // 扩展开入量_20

// OffLineDlg
CString g_sLangID_Native_TestModelTypeSelect;
CString g_sLangTxt_Native_TestModelTypeSelect; // 测试仪型号类型选择

// daSetdlg
CString g_sLangID_Native_tester_type;
CString g_sLangTxt_Native_tester_type; // 测试仪类型
CString g_sLangID_Native_digital_signal;
CString g_sLangTxt_Native_digital_signal; // 数字量
CString g_sLangID_Native_curmodule_set;
CString g_sLangTxt_Native_curmodule_set; // 电流模块设定
CString g_sLangID_Native_acrange_set;
CString g_sLangTxt_Native_acrange_set; // 交流电流档位设置
CString g_sLangID_Native_acmaxportvol_set;
CString g_sLangTxt_Native_acmaxportvol_set; // 交流电流最大端口电压设置
CString g_sLangID_Native_debounce_time;
CString g_sLangTxt_Native_debounce_time; // 防抖时间(S)：
CString g_sLangID_Native_highcurterm_Isoutput;
CString g_sLangTxt_Native_highcurterml_Isoutput; // 使用大电流端子Is输出
CString g_sLangID_Native_6Ito3I_output;
CString g_sLangTxt_Native_6Ito3I_output; // 电流6I合并成3I输出

// dcSetdlg
CString g_sLangID_Native_auxiliary_DCvol;
CString g_sLangTxt_Native_auxiliary_DCvol; // 辅助直流电压(V)
CString g_sLangID_Native_start_DC_output;
CString g_sLangTxt_Native_start_DC_output; // 开始直流输出
CString g_sLangID_Native_stop_DC_output;
CString g_sLangTxt_Native_stop_DC_output; // 停止直流输出
CString g_sLangID_Native_start_steadyoutput;
CString g_sLangTxt_Native_start_steadyoutput; // 开始稳态量输出
CString g_sLangID_Native_stop_steadyoutput;
CString g_sLangTxt_Native_stop_steadyoutput; // 停止稳态量输出
CString g_sLangID_Native_AC_DC_steadyoutput;
CString g_sLangTxt_Native_AC_DC_steadyoutput; // 交直流稳态输出
CString g_sLangID_Native_auxiDC_output_notempty;
CString g_sLangTxt_Native_auxiDC_output_notempty; // 辅助直流输出不可为空
CString g_sLangID_Native_auxiDC_output_positive;
CString g_sLangTxt_Native_auxiDC_output_positive; // 要求：辅助直流输出>0

// commonparasDlg
CString g_sLangID_Native_extractvol_outputdef;
CString g_sLangTxt_Native_extractvol_outputdef; // 抽取电压输出定义：
CString g_sLangID_Native_extractvol_refphasedef;
CString g_sLangTxt_Native_extractvol_refphasedef; // 抽取电压参考相定义：
CString g_sLangID_Native_extractvol_phaseangle;
CString g_sLangTxt_Native_extractvol_phaseangle; // 抽取电压相角：
CString g_sLangID_Native_coincidence_mode;
CString g_sLangTxt_Native_coincidence_mode; // 重合方式:
CString g_sLangID_Native_duration_afterjump;
CString g_sLangTxt_Native_duration_afterjump; // 开关跳后持续时间(s):
CString g_sLangID_Native_duration_coincidence;
CString g_sLangTxt_Native_duration_coincidence; // 重合持续时间(s):
CString g_sLangID_Native_postaccelerat_duration;
CString g_sLangTxt_Native_postaccelerat_duration; // 后加速开关跳开后持续时间(s):
CString g_sLangID_Native_impedance_refmode;
CString g_sLangTxt_Native_impedance_refmode; // 阻抗参考方式:
CString g_sLangID_Native_zeroseq_comp_calculat;
CString g_sLangTxt_Native_zeroseq_comp_calculat; // 零序补偿系数计算方式:
CString g_sLangID_Native_system_impedance;
CString g_sLangTxt_Native_system_impedance; // 系统阻抗(Ω):
CString g_sLangID_Native_system_impedance_angle;
CString g_sLangTxt_Native_system_impedance_angle; // 系统阻抗角(°):
CString g_sLangID_Native_closingangle_select;
CString g_sLangTxt_Native_closingangle_select; // 合闸角选择:
CString g_sLangID_Native_closingangle;
CString g_sLangTxt_Native_closingangle; // 合闸角(°):
CString g_sLangID_Native_closingangle_way;
CString g_sLangTxt_Native_closingangle_way; // 合闸角方式:
CString g_sLangID_Native_superimposed_nonperiodic;
CString g_sLangTxt_Native_superimposed_nonperiodic; // 叠加非周期分量(°):
CString g_sLangID_Native_search_mode;
CString g_sLangTxt_Native_search_mode; // 搜索方式:
CString g_sLangID_Native_testprocess_control;
CString g_sLangTxt_Native_testprocess_control; // 试验过程控制方式:
CString g_sLangID_Native_faultphase_definition;
CString g_sLangTxt_Native_faultphase_definition; // 故障相定义:

// debugCfgDlg
CString g_sLangID_Native_bottominfo_printset;
CString g_sLangTxt_Native_bottominfo_printset; // 底层信息打印设置
CString g_sLangID_Native_bottomloginfo_printornot;
CString g_sLangTxt_Native_bottomloginfo_printornot; // 是否打印底层日志信息
CString g_sLangID_Native_bottomtestinfo_saveornot;
CString g_sLangTxt_Native_bottomtestinfo_saveornot; // 是否保存底层测试信息

// DifferCharacWidget
CString g_sLangID_Native_StartIr;
CString g_sLangTxt_Native_StartIr; // 启动Ir
CString g_sLangID_Native_RatioCoefficient;
CString g_sLangTxt_Native_RatioCoefficient; // 比率系数
CString g_sLangID_Native_AddTestPoint;
CString g_sLangTxt_Native_AddTestPoint; // 添加测试点

CString g_sLangID_Native_BreakoffIr;
CString g_sLangTxt_Native_BreakoffIr; // 速断Ir
CString g_sLangID_Native_HarmCountId2;
CString g_sLangTxt_Native_HarmCountId2; // 2次谐波Id
CString g_sLangID_Native_HarmCountId3;
CString g_sLangTxt_Native_HarmCountId3; // 3次谐波Id
CString g_sLangID_Native_HarmCountId5;
CString g_sLangTxt_Native_HarmCountId5; // 5次谐波Id

// goose
CString g_sLangID_Native_statusName;
CString g_sLangTxt_Native_statusName; // 状态名称
CString g_sLangID_Native_outputTime;
CString g_sLangTxt_Native_outputTime; // 输出时间(s):

// 第五周马
// partparawidget_trans

// 表达式超出范围
CString g_sLangID_Native_ExprOutOfRange;
CString g_sLangTxt_Native_ExprOutOfRange;
// ABC三相
CString g_sLangID_Native_ABCTP;
CString g_sLangTxt_Native_ABCTP;
// Z相
CString g_sLangID_Native_Zphase;
CString g_sLangTxt_Native_Zphase;
// 有功功率
CString g_sLangID_Native_ActPower;
CString g_sLangTxt_Native_ActPower;
// 无功功率
CString g_sLangID_Native_ReacPower;
CString g_sLangTxt_Native_ReacPower;
// 视在功率
CString g_sLangID_Native_AppPower;
CString g_sLangTxt_Native_AppPower;

// QScanLanTesterDlg_trans
// 子网掩码
CString g_sLangID_Native_SubMask;
CString g_sLangTxt_Native_SubMask;
// 扫描局域网测试仪
CString g_sLangID_Native_LST;
CString g_sLangTxt_Native_LST;
// 网卡选择
CString g_sLangID_Native_NetAdptSelect;
CString g_sLangTxt_Native_NetAdptSelect;
// 修改测试仪IP
CString g_sLangID_Native_ModTesterIP;
CString g_sLangTxt_Native_ModTesterIP;
// IP地址
CString g_sLangID_Native_IPAddr;
CString g_sLangTxt_Native_IPAddr;
// 获取本地IP地址失败,当前值为空.
CString g_sLangID_Native_FailToRetrieveNetAddr;
CString g_sLangTxt_Native_FailToRetrieveNetAddr;
// 取得设备信息失败
CString g_sLangID_Native_FailToRetDevInfo;
CString g_sLangTxt_Native_FailToRetDevInfo;
// 测试仪IP地址(%1)与当前网卡IP不在同一网段,是否修改?
CString g_sLangID_Native_AddrNotInSameSubnet;
CString g_sLangTxt_Native_AddrNotInSameSubnet;
// 当前选择的网卡为空.
CString g_sLangID_Native_CurrSelNetAdptEmpty;
CString g_sLangTxt_Native_CurrSelNetAdptEmpty;
// 未知
CString g_sLangID_Native_Unknown;
CString g_sLangTxt_Native_Unknown;
// 被测装置信息
CString g_sLangID_Native_TestDevInfo;
CString g_sLangTxt_Native_TestDevInfo;
// A相电压
CString g_sLangID_Native_PhAVoltage;
CString g_sLangTxt_Native_PhAVoltage;
// B相电压
CString g_sLangID_Native_PhBVoltage;
CString g_sLangTxt_Native_PhBVoltage;
// C相电压
CString g_sLangID_Native_PhCVoltage;
CString g_sLangTxt_Native_PhCVoltage;
// ABC相电压
CString g_sLangID_Native_PhABCVoltage;
CString g_sLangTxt_Native_PhABCVoltage;
// 时间+开入量触发
CString g_sLangID_Native_TDITrigger;
CString g_sLangTxt_Native_TDITrigger;
// 叠加
CString g_sLangID_Native_Overlay;
CString g_sLangTxt_Native_Overlay;
// 不叠加
CString g_sLangID_Native_NoOverlay;
CString g_sLangTxt_Native_NoOverlay;
// 随机
CString g_sLangID_Native_Random;
CString g_sLangTxt_Native_Random;

CString g_sLangID_Native_TestNameGenTest;
CString g_sLangTxt_Native_TestNameGenTest;

CString g_sLangID_Native_BalanceCoeff;		   // = _T("Native_BalanceCoeff")
CString g_sLangTxt_Native_BalanceCoeff;		   // = _T("平衡系数：")
CString g_sLangID_Native_DiffFastCur;		   // = _T("Native_DiffFastCur")
CString g_sLangTxt_Native_DiffFastCur;		   // = _T("差动速断电流定值(A)：")
CString g_sLangID_Native_DiffActCur;		   // = _T("Native_DiffActCur")
CString g_sLangTxt_Native_DiffActCur;		   // = _T("差动动作电流定值(A)：")
CString g_sLangID_Native_RatioBreakPt1;		   // = _T("Native_RatioBreakPt1")
CString g_sLangTxt_Native_RatioBreakPt1;	   // = _T("比率制动特性拐点1电流(A)：")
CString g_sLangID_Native_RatioBreakPt2;		   // = _T("Native_RatioBreakPt2")
CString g_sLangTxt_Native_RatioBreakPt2;	   // = _T("比率制动特性拐点2电流(A)：")
CString g_sLangID_Native_BaseRatioSlope1;	   // = _T("Native_BaseRatioSlope1")
CString g_sLangTxt_Native_BaseRatioSlope1;	   // = _T("基波比率制动特性斜率1：")
CString g_sLangID_Native_BaseRatioSlope2;	   // = _T("Native_BaseRatioSlope2")
CString g_sLangTxt_Native_BaseRatioSlope2;	   // = _T("基波比率制动特性斜率2：")
CString g_sLangID_Native_SecondHarmBrakeCoef;  // = _T("Native_SecondHarmBrakeCoef")
CString g_sLangTxt_Native_SecondHarmBrakeCoef; // = _T("二次谐波制动系数：")
CString g_sLangID_Native_ThirdHarmBrakeCoef;   // = _T("Native_ThirdHarmBrakeCoef")
CString g_sLangTxt_Native_ThirdHarmBrakeCoef;  // = _T("三次谐波制动系数：")
CString g_sLangID_Native_FifthHarmBrakeCoef;   // = _T("Native_FifthHarmBrakeCoef")
CString g_sLangTxt_Native_FifthHarmBrakeCoef;  // = _T("五次谐波制动系数：")


// 第六周许

CString g_sLangID_Native_BulkWaveImport;			 // = _T("Native_BulkWaveImport")
CString g_sLangTxt_Native_BulkWaveImport;			 // = _T("批量导入波形")
CString g_sLangID_Native_BulkWaveFileImport;		 // = _T("Native_BulkWaveFileImport")
CString g_sLangTxt_Native_BulkWaveFileImport;		 // = _T("批量导入波形文件")
CString g_sLangID_Native_OpeningWaveFile;			 // = _T("Native_OpeningWaveFile")
CString g_sLangTxt_Native_OpeningWaveFile;			 // = _T("正在打开录波文件...")
CString g_sLangID_Native_SelectFolder;				 // = _T("Native_SelectFolder")
CString g_sLangTxt_Native_SelectFolder;				 // = _T("请选择文件夹")
CString g_sLangID_Native_NoWaveFiles;				 // = _T("Native_NoWaveFiles")
CString g_sLangTxt_Native_NoWaveFiles;				 // = _T("该文件夹下没有录波文件！")
CString g_sLangID_Native_WaveExceedMax;				 // = _T("Native_WaveExceedMax")
CString g_sLangTxt_Native_WaveExceedMax;			 // = _T("当前导入波形大于100，超出最大导入波形个数！")
CString g_sLangID_Native_ApplyAllCh;				 // = _T("Native_ApplyAllCh")
CString g_sLangTxt_Native_ApplyAllCh;				 // = _T("全部应用通道")
CString g_sLangID_Native_ApplyAllRatio;				 // = _T("Native_ApplyAllRatio")
CString g_sLangTxt_Native_ApplyAllRatio;			 // = _T("全部应用变比")
CString g_sLangID_Native_AllCycleCount;				 // = _T("Native_AllCycleCount")
CString g_sLangTxt_Native_AllCycleCount;			 // = _T("全部循环次数：")
CString g_sLangID_Native_ManualCtrl;				 // = _T("Native_ManualCtrl")
CString g_sLangTxt_Native_ManualCtrl;				 // = _T("  手动控制  ：")
CString g_sLangID_Native_SelectWave;				 // = _T("Native_SelectWave")
CString g_sLangTxt_Native_SelectWave;				 // = _T("请选择播放波形")
CString g_sLangID_Native_PlayPrev;					 // = _T("Native_PlayPrev")
CString g_sLangTxt_Native_PlayPrev;					 // = _T("播放上一个")
CString g_sLangID_Native_PlayNext;					 // = _T("Native_PlayNext")
CString g_sLangTxt_Native_PlayNext;					 // = _T("播放下一个")
CString g_sLangID_Native_StopTestOut;				 // = _T("Native_StopTestOut")
CString g_sLangTxt_Native_StopTestOut;				 // = _T("停止测试仪输出")
CString g_sLangID_Native_DiffCurve;					 // = _T("Native_DiffCurve")
CString g_sLangTxt_Native_DiffCurve;				 // = _T("差动特征曲线图")
CString g_sLangID_Native_HarmBrakeCurve;			 // = _T("Native_HarmBrakeCurve")
CString g_sLangTxt_Native_HarmBrakeCurve;			 // = _T("谐波制动特征曲线图")
CString g_sLangID_Native_ActionTimeCurve;			 // = _T("Native_ActionTimeCurve")
CString g_sLangTxt_Native_ActionTimeCurve;			 // = _T("动作时间特征曲线图")
CString g_sLangID_Native_SOETestParamFileNotExist;	 // = _T("Native_SOETestParamFileNotExist")
CString g_sLangTxt_Native_SOETestParamFileNotExist;	 // = _T("Soe测试参数文件【%s】不存在")
CString g_sLangID_Native_SOETestParamFileParseFail;	 // = _T("Native_SOETestParamFileParseFail")
CString g_sLangTxt_Native_SOETestParamFileParseFail; // = _T("解析Soe测试参数文件失败【%s】")

// 第六周吕

// 吕Overload Test
CString g_sLangID_Native_overloadACTestTempFile;
CString g_sLangTxt_Native_overloadACTestTempFile; // 过负荷(交流)试验模板文件
CString g_sLangID_Native_Wel_overloadACTest;
CString g_sLangTxt_Native_Wel_overloadACTest; // 欢迎使用过负荷(交流)试验.
CString g_sLangID_Native_Ponovo_overloadACTest;
CString g_sLangTxt_Native_Ponovo_overloadACTest; // Ponovo 过负荷(交流)试验
CString g_sLangID_Native_overloadACTest;
CString g_sLangTxt_Native_overloadACTest; // 过负荷(交流)试验

CString g_sLangID_Native_overloadCurrentChannel;
CString g_sLangTxt_Native_overloadCurrentChannel; // 过负荷电流通道
CString g_sLangID_Native_overloadCurChannel;
CString g_sLangTxt_Native_overloadCurChannel; // 过负荷电流通道:
CString g_sLangID_Native_overloadAC;
CString g_sLangTxt_Native_overloadAC; // 过负荷(交流)
CString g_sLangID_Native_overloadCurrentIA;
CString g_sLangTxt_Native_overloadCurrentIA; // 过负荷电流I(A):
CString g_sLangID_Native_NormTimeS;
CString g_sLangTxt_Native_NormTimeS; // 常态时间(s):

// IEC

// 第六周马
/*tr("过负荷(电流)试验模板文件")*/
CString g_sLangID_Native_OverloadCurrTestTemplate;
CString g_sLangTxt_Native_OverloadCurrTestTemplate;
/*_T("欢迎使用过负荷(直流)试验.")*/
CString g_sLangID_Native_WelcomeToOverloadDCTest;
CString g_sLangTxt_Native_WelcomeToOverloadDCTest;
/*tr("Ponovo 过负荷(直流)试验")*/
CString g_sLangID_Native_OverloadDCTest;
CString g_sLangTxt_Native_OverloadDCTest;
/*_T("热过负荷动作定值k")*/
CString g_sLangID_Native_ThermalOverloadTripSetting;
CString g_sLangTxt_Native_ThermalOverloadTripSetting;
/*_T("热过负荷基准电流IB")*/
CString g_sLangID_Native_ThermalOverloadRefCurr;
CString g_sLangTxt_Native_ThermalOverloadRefCurr;
/*_T("热过负荷时间常数τ")*/
CString g_sLangID_Native_ThermalOverloadTimeConst;
CString g_sLangTxt_Native_ThermalOverloadTimeConst;
/*_T("输出参数导致动作时间定值为负数，未修改成功，请根据动作特性方程重新修改!")*/
CString g_sLangID_Native_RedefineToChar;
CString g_sLangTxt_Native_RedefineToChar;

/*"<h1>过负荷(直流)</h1>"*/
CString g_sLangID_Native_OverloadDC;
CString g_sLangTxt_Native_OverloadDC;
/*_T("当前选择的电流通道(Index=%d)未查找到.")*/
CString g_sLangID_Native_CurrChannelNotFound;
CString g_sLangTxt_Native_CurrChannelNotFound;
/*QObject::tr("动作特性方程:")*/
CString g_sLangID_Native_ProtCharEquation;
CString g_sLangTxt_Native_ProtCharEquation;
// 过负荷电流
CString g_sLangID_Native_OverloadCurr;
CString g_sLangTxt_Native_OverloadCurr;

// 报文总数
CString g_sLangID_Native_TotalMsgs;
CString g_sLangTxt_Native_TotalMsgs;
// 丢包数
CString g_sLangID_Native_PktLossCount;
CString g_sLangTxt_Native_PktLossCount;
// 最大时间差
CString g_sLangID_Native_MaxTimeDiff;
CString g_sLangTxt_Native_MaxTimeDiff;
// 停止写文件
CString g_sLangID_Native_StopWriteFile;
CString g_sLangTxt_Native_StopWriteFile;

// 第七周吕
// ovt
CString g_sLangID_Native_OVtempfile;
CString g_sLangTxt_Native_OVtempfile; // 过压试验模板文件
CString g_sLangID_Native_wel_OVtest;
CString g_sLangTxt_Native_wel_OVtest; // 欢迎使用过压测试.
CString g_sLangID_Native_OVprotect;
CString g_sLangTxt_Native_OVprotect; // 过电压保护
CString g_sLangID_Native_OverValtage;
CString g_sLangTxt_Native_OverValtage; // 过压
CString g_sLangID_Native_OVprotect_Actvalue;
CString g_sLangTxt_Native_OVprotect_Actvalue; // 过压保护动作值
CString g_sLangID_Native_OV_ActTimelim;
CString g_sLangTxt_Native_OV_ActTimelim; // 过电压动作时限
CString g_sLangID_Native_ActVNega_Error;
CString g_sLangTxt_Native_ActVNega_Error; // 当前动作电压为负，修改不成功.
CString g_sLangID_Native_ActTNega_Error;
CString g_sLangTxt_Native_ActTNega_Error; // 当前动作时间为负，修改不成功.
CString g_sLangID_Native_Name_OVprotectTest;
CString g_sLangTxt_Native_Name_OVprotectTest; // 试验名称：过压保护定值测试
CString g_sLangID_Native_OVprotectTest;
CString g_sLangTxt_Native_OVprotectTest; // 过压保护定值测试
CString g_sLangID_Native_1ErrorType_and_Times;
CString g_sLangTxt_Native_1ErrorType_and_Times; // 请务必至少选择一个故障类型以及倍数！
CString g_sLangID_Native_SetValueV;
CString g_sLangTxt_Native_SetValueV; // 整定值(V)
CString g_sLangID_Native_AddTestDig;
CString g_sLangTxt_Native_AddTestDig; // 添加测试项

// 第七周马
/*tr("电压保护试验模板文件")*/
CString g_sLangID_Native_VoltProtTestTplFile;
CString g_sLangTxt_Native_VoltProtTestTplFile;
/*_T("欢迎使用电压保护测试.")*/
CString g_sLangID_Native_WelcomeVoltProtTest;
CString g_sLangTxt_Native_WelcomeVoltProtTest;
/*tr("电压保护")*/
CString g_sLangID_Native_VoltProtection;
CString g_sLangTxt_Native_VoltProtection;
/*_T("电压I段动作值")*/
CString g_sLangID_Native_VIStagePickVal;
CString g_sLangTxt_Native_VIStagePickVal;
/*_T("电压II段动作值")*/
CString g_sLangID_Native_VIIStagePickVal;
CString g_sLangTxt_Native_VIIStagePickVal;
/*_T("电压III段动作值")*/
CString g_sLangID_Native_VIIIStagePickVal;
CString g_sLangTxt_Native_VIIIStagePickVal;
/*_T("电压IV段动作值")*/
CString g_sLangID_Native_VIVStagePickVal;
CString g_sLangTxt_Native_VIVStagePickVal;
/*_T("电压I段动作时间")*/
CString g_sLangID_Native_VIPickTime;
CString g_sLangTxt_Native_VIPickTime;
/*_T("电压II段动作时间")*/
CString g_sLangID_Native_VIIPickTime;
CString g_sLangTxt_Native_VIIPickTime;
/*_T("电压III段动作时间")*/
CString g_sLangID_Native_VIIIPickTime;
CString g_sLangTxt_Native_VIIIPickTime;
/*_T("电压IV段动作时间")*/
CString g_sLangID_Native_VIVPickTime;
CString g_sLangTxt_Native_VIVPickTime;
/*_T("当前动作值为负，修改不成功.")*/
CString g_sLangID_Native_CurrPickNegModUnsucc;
CString g_sLangTxt_Native_CurrPickNegModUnsucc;
/*_T("过电压")*/
CString g_sLangID_Native_Ovltg;
CString g_sLangTxt_Native_Ovltg;
/*试验名称：过压保护定值测试*/
CString g_sLangID_Native_OvltgProtSetTest;
CString g_sLangTxt_Native_OvltgProtSetTest;
/*"过压I段保护定值测试"*/
CString g_sLangID_Native_OvltgIProtSetTest;
CString g_sLangTxt_Native_OvltgIProtSetTest;
/*"过压II段保护定值测试"*/
CString g_sLangID_Native_OvltgIIProtSetTest;
CString g_sLangTxt_Native_OvltgIIProtSetTest;
/*"过压III段保护定值测试"*/
CString g_sLangID_Native_OvltgIIIProtSetTest;
CString g_sLangTxt_Native_OvltgIIIProtSetTest;
/*"过压IV段保护定值测试"*/
CString g_sLangID_Native_OvltgIVProtSetTest;
CString g_sLangTxt_Native_OvltgIVProtSetTest;
/*"过压V段保护定值测试"*/
CString g_sLangID_Native_OvltgVProtSetTest;
CString g_sLangTxt_Native_OvltgVProtSetTest;
/*tr("故障前输出")*/
CString g_sLangID_Native_PreFaultOut;
CString g_sLangTxt_Native_PreFaultOut;

/*tr("故障前时间裕度")*/
CString g_sLangID_Native_PreFaultTimeMargin;
CString g_sLangTxt_Native_PreFaultTimeMargin;
/*_T("当前设置值(%f)小于最小值(0.000000),修改不成功")*/
CString g_sLangID_Native_CSVLessMinModUnsucc;
CString g_sLangTxt_Native_CSVLessMinModUnsucc;
/*_T("当前设置值(%f)大于最大值(%f),强制设置为最大值")*/
CString g_sLangID_Native_CSVGreaterMaxForceSetMax;
CString g_sLangTxt_Native_CSVGreaterMaxForceSetMax;
/*_T("当前设置值(%f)大于最大值(999.000000),强制设置为最大值")*/
CString g_sLangID_Native_CSVGreaterMaxForceSetMax9;
CString g_sLangTxt_Native_CSVGreaterMaxForceSetMax9;
/*tr("高压侧差动平衡系数")*/
CString g_sLangID_Native_HVSDiffBalCoeff;
CString g_sLangTxt_Native_HVSDiffBalCoeff;
/*tr("中压侧差动平衡系数")*/
CString g_sLangID_Native_MVSDiffBalCoeff;
CString g_sLangTxt_Native_MVSDiffBalCoeff;
/*tr("低压侧差动平衡系数")*/
CString g_sLangID_Native_LVSDiffBalCoeff;
CString g_sLangTxt_Native_LVSDiffBalCoeff;

// extern CString