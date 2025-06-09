#ifndef STTMULTIMACROLOWVOLPARASDEFINE_H
#define STTMULTIMACROLOWVOLPARASDEFINE_H

#define STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_ACTVALUE	        "LowVolAct"
#define STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_ACTTIME	        "LowVolTime"
#define STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_SLIPTRIP	        "LowVolDvdt"
#define STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_IBLOCK				"LowVolILock"
//QLOWVOLResultEstimateDlg	功能参数页面

//动作值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ACTVALUE		"UAct"			//动作值测试项-动作值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_CUR			"IAct"				//动作值测试项-电流
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_HOlDTIME		"HoldTime"			//动作值测试项-保持时间
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RELERR		"TripVol_RelErr"			//动作值测试项-相对误差
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ABSERR		"TripVol_AbsErr"			//动作值测试项-绝对误差
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTART 	"Vstart"		//动作值测试项-线电压变化起始值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VEND		"Vend"			//动作值测试项-线电压变化结束值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTEP		"Vstep"			//动作值测试项-线电压变化步长
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_DVDT			"dvdt"				//动作值测试项-电压滑差
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VAR		 "FaultType"				 //动作值测试项-电压变化量
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RSLTEVAL      "TripVol_ErrorLogic"        //结果评估逻辑
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_UVARIABLE      "UVariable"        //电压变化量

//动作时间
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_TSETTING		"UActTime"			//动作时间测试项-动作时间定值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_CUR				"IAct"				//动作时间测试项-电流
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_FSETTING		"UAct"			//动作时间测试项-电压动作值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_HOlDTIME		"HoldTime"			//动作时间测试项-保持时间
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RELERR			"Ttrip_RelErr"			//动作时间测试项-相对误差
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRPOS		"Ttrip_AbsErrPos"			//动作时间测试项-正绝对误差
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRNEG		"Ttrip_AbsErrNeg"			//动作时间测试项-负绝对误差
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_VEND			"Vend"					//动作时间测试项-电压变化终值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_DVDT			"dvdt"				//动作时间测试项-线电压滑差
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RSLTEVAL	    "Ttrip_ErrorLogic"           //结果评估逻辑
//滑差闭锁值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSETTING		"DvdtClose"		//滑差闭锁值测试项-滑差定值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_CUR				"IAct"				//滑差闭锁值测试项-电流
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_HOlDTIME			"HoldTime"			//滑差闭锁值测试项-保持时间
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RELERR			"TripDvdt_RelErr"			//滑差闭锁值测试项-相对误差
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_ABSERR			"TripDvdt_AbsErr"			//滑差闭锁值测试项-绝对误差
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VEND			"Vend"			//滑差闭锁值测试项-电压变化终值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VSTEP			"Step"		//滑差闭锁值测试项-滑差变化步长
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSTART			"BeginVal"			//滑差闭锁值测试项-滑差变化始值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTEND			"EndVal"			//滑差闭锁值测试项-滑差变化终值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RSLTEVAL		    "TripDvdt_ErrorLogic"       //结果评估逻辑
//低电流闭锁值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IBLOCKSETTING		"IAct"		//低电流闭锁值测试项-低电流闭锁值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_HOlDTIME			"HoldTime"			//低电流闭锁值测试项-保持时间
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_VAR					"IVariable"				//低电流闭锁值测试项-电流输出相
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RELERR				"Ilow_RelErr"				//低电流闭锁值测试项-相对误差
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ABSERR				"Ilow_AbsErr"				//低电流闭锁值测试项-绝对误差
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ISTART				"BeginVal"				//低电流闭锁值测试项-电流变化起始值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IEND				"EndVal"				//低电流闭锁值测试项-电流变化结束值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ISTEP				"Step"				//低电流闭锁值测试项-电流变化步长
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_VEND				"Vend"				//低电流闭锁值测试项-电压变化终值
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_DVDT				"dvdt"				//低电流闭锁值测试项-电压滑差
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RSLTEVAL		    "Ilow_ErrorLogic"           //结果评估逻辑

//QLOWVOLCommonParasDlg	通用参数页面
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_HoldTime               "HoldTime"          //保持时间
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_PREFAULTTIME			"PreFaultTime"		//稳态时间
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IPRETIME				"IAct"				//稳态电流
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_TIMEZERO				"DvdtTiming"			//计时起点
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_USETMODE				"USetMode"          //闭锁电压选择:区分线电压还是相电压

//QLOWVOLBinarysDlg		开入、开出页面
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B01						"_Bout1"			//开出1状态
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B02						"_Bout2"			//开出2状态
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B03						"_Bout3"			//开出3状态
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B04						"_Bout4"			//开出4状态
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B05						"_Bout5"			//开出5状态
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B06						"_Bout6"			//开出6状态
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B07						"_Bout7"			//开出7状态
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B08						"_Bout8"			//开出8状态
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_AndOr						"_AndOr"			//开入逻辑
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_A							"_BinSelectA"		//开入A选择
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_B							"_BinSelectB"		//开入B选择
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_C							"_BinSelectC"		//开入C选择
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_D							"_BinSelectR"		//开入R选择
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_E							"_BinSelecta"		//开入a选择
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_F							"_BinSelectb"		//开入b选择
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_G							"_BinSelectc"		//开入c选择
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_H							"_BinSelectr"		//开入r选择

//表格参数
#define STT_MULTI_MACRO_LOWVOL_GRID_PARAS_ID_SELECT                 "Select"		//选择
#define STT_MULTI_MACRO_LOWVOL_GRID_PARAS_ID_STATE					"State"			//状态
#define STT_MULTI_MACRO_LOWVOL_GRID_PARAS_ID_TESTRSLT				"TestRslt"		//测试结果
typedef enum{
	LOWVOL_ID_PsuLowVolAct = 0,   
	LOWVOL_ID_PsuLowVolTime = 1,   
	LOWVOL_ID_PsuLowVolDfdt = 2,    
	LOWVOL_ID_PsuLowVolILock = 3,       
}STT_MULTI_MACRO_LOWVOLTYPE;

typedef enum{
	LOWVOL_ID_VType_Line = 0,   
	LOWVOL_ID_VType_Phase = 1,  
}STT_MULTI_MACRO_LOWVOLVTYPE;
#endif // STTMULTIMACROLOWVOLPARASDEFINE_H
