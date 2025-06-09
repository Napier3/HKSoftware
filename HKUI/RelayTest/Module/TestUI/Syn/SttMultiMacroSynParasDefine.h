#ifndef STTMULTIMACROSYNPARASDEFINE_H
#define STTMULTIMACROSYNPARASDEFINE_H

#define STT_MULTI_MACRO_SYN_PARAS_GRID_ID_VOLTAGETEST	        "VoltageActValue"
#define STT_MULTI_MACRO_SYN_PARAS_GRID_ID_FREQTEST	        "FreqtageActValue"
#define STT_MULTI_MACRO_SYN_PARAS_GRID_ID_LEADANG	        "LeadAngTime"
#define STT_MULTI_MACRO_SYN_PARAS_GRID_ID_AUTOADJ	        "AutoAdjTest"
#define STT_MULTI_MACRO_SYN_PARAS_GRID_ID_ADJVOL	        "AdjVolTest"
#define STT_MULTI_MACRO_SYN_PARAS_GRID_ID_ADJFREQ	        "AdjFreqTest"

//快速添加
#define STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_UPlus			"UPlus"	
#define STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_UMinus			"UMinus"	
#define STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_FPlus			"FPlus"	
#define STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_FMinus			"FMinus"

//功能参数页面
//电压边界值
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_DVzd		"dVzd"			//允许压差
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_ABSERR			"dVzd_AbsErr"				//绝对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_RELERR		"dVzd_RelErr"			//相对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGSTART		"UgStart"			//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGSTART		"FgStart"			//待并侧频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGMAGSTEP 	"UgMagStep"		//待并侧电压变化步长
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UT		"Ut"			//调压周期
//频率边界值
#define STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_DFzd		"dFzd"			//允许频差
#define STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_ABSERR			"dFzd_AbsErr"				//绝对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_RELERR		"dFzd_RelErr"			//相对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_UGSTART		"UgStart"			//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FGSTART			"FgStart"			//待并侧频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_UGFREQSTEP		"UgFreqStep"			//待并侧频率变化步长
#define STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FT		"Ft"			//调频周期
//导前角和导前时间
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LANGLE		"LAngle"		//导前角
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LTIME				"LTime"				//导前时间
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_ABSERR			"LeaderAngle_AbsErr"			//绝对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_RELERR			"LeaderAngle_RelErr"			//相对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_UGSTART			"UgStart"			//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_FGSTART			"FgStart"			//待并侧频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_DFDT			"DfDt"		//频率滑差
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_DVDT			"DvDt"			//电压滑差
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_UGMAGSTEP			"UgMagStep"			//待并侧电压变化步长
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_UGFREQSTEP		    "UgFreqStep"    //待并侧频率变化步长
//自调整试验
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_LANGLE		"LAngle"		//导前角
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_LTIME					"LTime"				//导前时间
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_UT				"Ut"			//调压周期
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_FT		    "Ft"                   //调频周期
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_ABSERR			"AutoAdj_AbsErr"			//绝对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_RELERR					"AutoAdj_RelErr"				//相对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_UGSTART				"UgStart"				//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_FGSTART				"FgStart"				//待并侧频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_DFDT				"DfDt"				//频率滑差
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_DVDT				"DvDt"				//电压滑差
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_UGMAGSTEP				"UgMagStep"				//待并侧电压变化步长
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_UGFREQSTEP				"UgFreqStep"				//待并侧频率变化步长
//调压周期
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_UT		"Ut"		//调压周期
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_PLUS			"Ut_AbsErr_Pos"			//绝对误差正
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_MINUS					"Ut_AbsErr_Neg"				//绝对误差负
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_RELERR				"Ut_RelErr"				//相对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_UGSTART				"UgStart"				//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_FGSTART				"FgStart"				//待并侧频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_UGMAGSTEP				"UgMagStep"				//待并侧电压变化步长
//调频周期
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_FT		"Ft"		//调频周期
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_PLUS			"Ft_AbsErr_Pos"			//绝对误差正
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_MINUS					"Ft_AbsErr_Neg"				//绝对误差负
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_RELERR				"Ft_RelErr"				//相对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_UGSTART				"UgStart"				//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_FGSTART				"FgStart"				//待并侧频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_UGFREQSTEP				"UgFreqStep"				//待并侧频率变化步长

//QSynCommonParasDlg	通用参数页面
#define STT_MULTI_MACRO_SYN_PARAS_ID_Us				"Us"		//系统侧额定电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_Fs				"Fs"			//系统侧额定频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_Ug					"Ug"             //待并侧额定电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_UgConnectDef					"UgConnectDef"             //电压定义
#define STT_MULTI_MACRO_SYN_PARAS_ID_Vref					"Vref"             //参考相
//#define STT_MULTI_MACRO_SYN_PARAS_ID_TansConnect					"TansConnect"             //变压器接线方式
//#define STT_MULTI_MACRO_SYN_PARAS_ID_TansConnect_2					"TansConnect_2"             //待并测接线方式
#define STT_MULTI_MACRO_SYN_PARAS_ID_PointNum					"WindAngs"             //钟点数
#define STT_MULTI_MACRO_SYN_PARAS_ID_Angle					"PhaseDiff"             //两侧相位差
#define STT_MULTI_MACRO_SYN_PARAS_ID_Tmax					"Tmax"             //最大同步时间

//
//QSynBinarysDlg		开入、开出页面
#define STT_MULTI_MACRO_SYN_PARAS_ID_KStart				"KStart"	//开出4输出方式
#define STT_MULTI_MACRO_SYN_PARAS_ID_CloseTime			  "CloseTime"			//开出4保持时间
#define STT_MULTI_MACRO_SYN_PARAS_ID_Bout1				"_Bout1"			//开出1状态
#define STT_MULTI_MACRO_SYN_PARAS_ID_Bout2				"_Bout2"			//开出2状态
#define STT_MULTI_MACRO_SYN_PARAS_ID_Bout3				"_Bout3"			//开出3状态
#define STT_MULTI_MACRO_SYN_PARAS_ID_BinSyn				"_BinSyn"			//同期信号
#define STT_MULTI_MACRO_SYN_PARAS_ID_BinIncV			"_BinIncV"			//增压信号
#define STT_MULTI_MACRO_SYN_PARAS_ID_BinDecV			"_BinDecV"			//减压信号
#define STT_MULTI_MACRO_SYN_PARAS_ID_BinIncF			"_BinIncF"			//增频信号
#define STT_MULTI_MACRO_SYN_PARAS_ID_BinDecF			"_BinDecF"		//减频信号

#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Us				"Us"		//系统侧额定电压
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Fs				"Fs"			//系统侧额定频率
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Ug					"Ug"             //待并侧额定电压
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_UgConnectDef					"UgConnectDef"             //电压定义
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Vref					"Vref"             //参考相
//#define STT_MULTI_MACRO_SYN_PARAS_ID_TansConnect					"TansConnect"             //变压器接线方式
//#define STT_MULTI_MACRO_SYN_PARAS_ID_TansConnect_2					"TansConnect_2"             //待并测接线方式
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_PointNum					"WindAngs"             //钟点数
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Angle					"PhaseDiff"             //两侧相位差
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Tmax					"Tmax"             //最大同步时间

#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_KStart				"KStart"	//开出4输出方式
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_CloseTime			  "CloseTime"			//开出4保持时间
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Bout1				"_Bout1"			//开出1状态
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Bout2				"_Bout2"			//开出2状态
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Bout3				"_Bout3"			//开出3状态
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_BinSyn				"_BinSyn"			//同期信号
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_BinIncV			"_BinIncV"			//增压信号
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_BinDecV			"_BinDecV"			//减压信号
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_BinIncF			"_BinIncF"			//增频信号
#define STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_BinDecF			"_BinDecF"		//减频信号

//添加系列
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_VolBordValue_CHECK			"VolBordValue_Check"			//电压边界值测试
#define STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FreqBordValue_CHECK		"FreqBordValue_Check"//频率边界值测试
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LeaderAngleLeaderTime_CHECK			"LeaderAngleLeaderTime_Check"			//导前角及导前时间
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_SelfAdjusting_CHECK		"SelfAdjusting_Check"//自调整试验
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_Ut_CHECK			"Ut_Check"			//调压周期测试
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_Ft_CHECK			"Ft_Check"			//调频周期测试

//#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_DVzd		"dVzd"			//允许压差
//#define STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_DFzd		"dFzd"			//允许频差(Hz)
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LAngle		"LAngle"			//导前角(°)
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_LTime	"LTime"			//导前时间(s)
//#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_UT		"Ut"			//调压周期
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_Ft		"Ft"			//调频周期(s)
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGSTART0		"UgStart0"			//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGSTART0		"FgStart0"			//待并侧频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_UGSTART1		"UgStart1"			//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FGSTART1		"FgStart1"			//待并侧频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_UGSTART2		"UgStart2"			//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_FGSTART2		"FgStart2"			//待并侧频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_UGSTART3		"UgStart3"			//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_FGSTART3		"FgStart3"			//待并侧频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_UGSTART4		"UgStart4"			//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_FGSTART4		"FgStart4"			//待并侧频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_UGSTART5		"UgStart5"			//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_FGSTART5		"FgStart5"			//待并侧频率
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGSTART6		"UgStart6"			//待并侧电压
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGSTART6		"FgStart6"			//待并侧频率

//#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGMAGSTEP 	"UgMagStep"		//待并侧电压变化步长
#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGMAGSTEP 	"FgMagStep"		//频率变化步长(Hz)

#define STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_ERRORLOGIC		"dVzd_ErrorLogic"
#define STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_ERRORLOGIC		"dFzd_ErrorLogic"
#define STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_ERRORLOGIC		"LeaderAngle_ErrorLogic"
#define STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_ERRORLOGIC		"LeaderTime_ErrorLogic"			//误差判断逻辑
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_ERRORLOGIC		"Ut_ErrorLogic"			//误差判断逻辑
#define STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_ERRORLOGIC		"Ft_ErrorLogic"			//误差判断逻辑


//#define STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_VOLTTEST_ABSERR			"dVzd_AbsErr"				//绝对误差
//#define STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_VOLTTEST_RELERR		"dVzd_RelErr"			//相对误差
//#define STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_FREQTEST_ABSERR			"dFzd_AbsErr"				//绝对误差
//#define STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_FREQTEST_RELERR		"dFzd_RelErr"			//相对误差
//#define STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_LEADANG_ABSERR			"LeaderAngle_AbsErr"			//绝对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_LEADANG_RELERR			"LeaderAngle_RelErr"			//相对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_LEADTIME_ABSERR			"LeaderTime_AbsErr"			//绝对误差
#define STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_LEADTIME_RELERR					"LeaderTime_RelErr"	//相对误差
//#define STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_ADJVOL_ABSERR					"Ut_AbsErr"				//绝对误差
//#define STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_ADJVOL_RELERR				"Ut_RelErr"				//相对误差
//#define STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_ADJFREQ_ABSERR					"Ft_AbsErr"				//绝对误差
//#define STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_ADJFREQ_RELERR				"Ft_RelErr"				//相对误差

#define STT_MULTI_MACRO_SYN_PARAS_ID_DEFAULT					"0"

typedef enum{
Syn_ID_SynActVoltageTest = 0,   
Syn_ID_SynActFreqTest = 1,   
Syn_ID_SynLeadAngTest = 2,  
Syn_ID_SynAutoAdjTest = 3,     
Syn_ID_SynAdjVolTest = 4, 
Syn_ID_SynAdjFreqTest = 5,
}STT_MULTI_MACRO_SYNTYPE;

#endif // STTMULTIMACROSYNPARASDEFINE_H