#ifndef STTMULTIMACROLOWFREQPARASDEFINE_H
#define STTMULTIMACROLOWFREQPARASDEFINE_H

#define STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_ACTVALUE	        "LowFreqAct"
#define STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_ACTTIME	        "LowFreqTime"
#define STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_SLIPTRIP	        "LowFreqDfdt"
#define STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_VBLOCK	        "LowFreqULock"
#define STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_IBLOCK	        "LowFreqILock"
//QLOWFREQResultEstimateDlg	功能参数页面

//动作值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_ACTVALUE		"FAct"			//动作值测试项-动作值(整定值)
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_CUR			"Ilow"				//动作值测试项-电流
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_HOlDTIME		"HoldTime"			//动作值测试项-保持时间
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_RELERR		"HzActVal_RelErr"			//动作值测试项-相对误差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_ABSERR		"HzActVal_AbsErr"			//动作值测试项-绝对误差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_RSLTEVAL      "HzActVal_ErrorLogic"         //结果评估逻辑
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTART 	"Fstart"		//动作值测试项-频率起始值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQEND		"Fend"			//动作值测试项-频率结束值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTEP		"Fstep"			//动作值测试项-频率变化步长
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_DVDT			"dvdt"				//动作值测试项-频率滑差

//动作时间
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_TSETTING		"FActTime"			//动作时间测试项-动作时间定值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_CUR			"Ilow"				//动作时间测试项-电流
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_FSETTING		"FAct"			//动作时间测试项-频率动作值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_HOlDTIME		"HoldTime"			//动作时间测试项-保持时间
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_RELERR			"Ttrip_RelErr"			//动作时间测试项-相对误差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_ABSERRPOS		"Ttrip_AbsErrPos"			//动作时间测试项-正绝对误差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_ABSERRNEG	"Ttrip_AbsErrNeg"			//动作时间测试项-负绝对误差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_RSLTEVAL	    "Ttrip_ErrorLogic"          //结果评估逻辑
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_FREQEND		"Fend"			//动作时间测试项-频率结束值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_DFDT			"dvdt"				//动作时间测试项-频率滑差
//滑差闭锁值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSETTING		"DvdtClose"		//滑差闭锁值测试项-滑差定值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_CUR				"Ilow"				//滑差闭锁值测试项-电流
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_HOlDTIME			"HoldTime"			//滑差闭锁值测试项-保持时间
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_RELERR			"Dfdt_RelErr"			//滑差闭锁值测试项-相对误差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_ABSERR			"Dfdt_AbsErr"			//滑差闭锁值测试项-绝对误差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_RSLTEVAL		    "Dfdt_ErrorLogic"         //结果评估逻辑
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_FREQEND			"FreqEnd"			//滑差闭锁值测试项-频率变化终值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTART			"BeginVal"		//滑差闭锁值测试项-滑差变化始值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTEND			"EndVal"			//滑差闭锁值测试项-滑差变化终值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTEP			"Step"			//滑差闭锁值测试项-滑差变化步长

//低电压闭锁值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VBLOCKSETTING		"Ulow"		//低电压闭锁值测试项-低电压闭锁值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_CUR					"Ilow"				//低电压闭锁值测试项-电流
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_HOlDTIME			"HoldTime"			//低电压闭锁值测试项-保持时间
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VAR					"UVariable"				//低电压闭锁值测试项-电压变化量
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_RELERR				"Ulow_RelErr"				//低电压闭锁值测试项-相对误差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_ABSERR				"Ulow_AbsErr"				//低电压闭锁值测试项-绝对误差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_RSLTEVAL		    "Ulow_ErrorLogic"           //结果评估逻辑
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VSTART				"BeginVal"				//低电压闭锁值测试项-电压变化起始值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VEND				"EndVal"				//低电压闭锁值测试项-电压变化结束值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VSTEP				"Step"				//低电压闭锁值测试项-电压变化步长
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_DFDT				"Dfdt"				//低电压闭锁值测试项-频率滑差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_FREQEND				"RampTo"			//低电压闭锁值测试项-频率变化终值

//低电流闭锁值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IBLOCKSETTING		"Ilow"		//低电流闭锁值测试项-低电流闭锁值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_HOlDTIME			"HoldTime"			//低电流闭锁值测试项-保持时间
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_VAR					"IVariable"				//低电流闭锁值测试项-电流输出相
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_RELERR				"Ilow_RelErr"				//低电流闭锁值测试项-相对误差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ABSERR				"Ilow_AbsErr"				//低电流闭锁值测试项-绝对误差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_RSLTEVAL		    "Ilow_ErrorLogic"           //结果评估逻辑
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ISTART				"BeginVal"				//低电流闭锁值测试项-电流变化起始值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IEND				"EndVal"				//低电流闭锁值测试项-电流变化结束值
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ISTEP				"Step"				//低电流闭锁值测试项-电流变化步长
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_DFDT				"Dfdt"				//低电流闭锁值测试项-频率滑差
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_FREQEND				"RampTo"			//低电流闭锁值测试项-频率变化终值

//QLOWFREQCommonParasDlg	通用参数页面
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_HoldTime               "HoldTime"          //保持时间
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_PREFAULTTIME			"PreFaultTime"		//稳态时间
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_TIMEZERO				"DfdtTiming"			//计时起点
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_USETMODE				"USetMode"          //闭锁电压选择:区分线电压还是相电压

//QLOWFREQBinarysDlg		开入、开出页面
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B01						"_Bout1"			//开出1状态
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B02						"_Bout2"			//开出2状态
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B03						"_Bout3"			//开出3状态
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B04						"_Bout4"			//开出4状态
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B05						"_Bout5"			//开出5状态
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B06						"_Bout6"			//开出6状态
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B07						"_Bout7"			//开出7状态
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B08						"_Bout8"			//开出8状态
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_AndOr						"_AndOr"			//开入逻辑
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_A							"_BinSelectA"		//开入A选择
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_B							"_BinSelectB"		//开入B选择
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_C							"_BinSelectC"		//开入C选择
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_D							"_BinSelectR"		//开入R选择
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_E							"_BinSelecta"		//开入a选择
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_F							"_BinSelectb"		//开入b选择
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_G							"_BinSelectc"		//开入c选择
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_H							"_BinSelectr"		//开入r选择

//表格参数
#define STT_MULTI_MACRO_LOWFREQ_GRID_PARAS_ID_SELECT                 "Select"		//选择
#define STT_MULTI_MACRO_LOWFREQ_GRID_PARAS_ID_STATE					"State"			//状态
#define STT_MULTI_MACRO_LOWFREQ_GRID_PARAS_ID_TESTRSLT				"TestRslt"		//测试结果

typedef enum{
LOWFREQ_ID_PsuLowFreqAct = 0,   
LOWFREQ_ID_PsuLowFreqTime = 1,   
LOWFREQ_ID_PsuLowFreqDfdt = 2,  
LOWFREQ_ID_PsuLowFreqULock = 3,     
LOWFREQ_ID_PsuLowFreqILock = 4,       
}STT_MULTI_MACRO_LOWFREQTYPE;

typedef enum{
	LOWFREQ_ID_VType_Line = 0,   
	LOWFREQ_ID_VType_Phase = 1,  
}STT_MULTI_MACRO_VTYPE;

#endif // STTMULTIMACROLOWFREQPARASDEFINE_H