#ifndef STTMULTIMACRODIFFCBOPDEFINE_H
#define STTMULTIMACRODIFFCBOPDEFINE_H

#define STT_MULTI_MACRO_DIFFCBOP_PARAS_GRID_ID 	        "DiffCBOp-Grid"

#define DIFFCBOP_FAULT_TYPE_AN                                                 0//阻抗类的故障类型定义
#define DIFFCBOP_FAULT_TYPE_BN                                                 1
#define DIFFCBOP_FAULT_TYPE_CN                                                 2
#define DIFFCBOP_FAULT_TYPE_ABN                                                3
#define DIFFCBOP_FAULT_TYPE_BCN                                                4
#define DIFFCBOP_FAULT_TYPE_CAN                                                5
#define DIFFCBOP_FAULT_TYPE_ABC                                                6


#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_AN         "FaultType_AN"
#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_BN         "FaultType_BN"
#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_CN         "FaultType_CN"
#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_ABN        "FaultType_ABN"
#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_BCN        "FaultType_BCN"
#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_CAN        "FaultType_CAN"
#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_ABC        "FaultType_ABC"


//QDistanceResultEstimateDlg	功能参数编辑页面
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTYPE					"FaultType"			//故障类型
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTLOCATION				"FaultLocation"		//故障点位置
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CURENT					"Current"			//电流(A)
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FREP						"Freq"				//频率(Hz)
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_KCAL						"Kcal"				//是否设置平衡系数
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVKPH				"Kph"				//变压器高压侧平衡系数
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVVOL				"Uh"				//变压器高压侧额定电压
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVCUR				"Inh"				//变压器高压侧额定电流
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVCT				"CTh"				//变压器高压侧CT变比
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVKVA				"SN"				//变压器额定容量
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVKPM				"Kpm"				//变压器中压侧平衡系数
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVVOL				"Um"				//变压器中压侧额定电压
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVCUR				"Inm"				//变压器中压侧额定电流
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVCT				"CTm"				//变压器中压侧CT变比
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVKPL				"Kpl"				//变压器低压侧平衡系数
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVVOL				"Ul"				//变压器低压侧额定电压
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVCUR				"Inl"				//变压器低压侧额定电流
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVCT				"CTl"				//变压器低压侧CT变比
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_SETTING					"Setting"			//整定值
//#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRSUM					"AbsErrSum"			//绝对误差(S) +
//#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRREDUCE				"AbsErrReduce"		//绝对误差(S) -
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRSUM					"Trip_AbsErrPos"	//绝对误差(S) +
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRREDUCE				"Trip_AbsErrNeg"		//绝对误差(S) -
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRRELERR				"RelErr"			//相对误差
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ERRORTYPE					"ErrorType"			//误差类型
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_DEFAULT					"0"					//缺省值

//QDiffProtectionParasDlg	通用参数页面
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PREPARETIME			"PrepareTime"			//准备时间
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PREFAULTTIME			"PreFaultTime"			//故障前时间
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTIME				"FaultTime"				//故障时间
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTIMEMARGIN		"FaultTimeMargin"		//故障时间裕度
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ACTIONHOLDTIME		"ActionHoldTime"		//动作后保持时间
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDH					"WindH"					//高压侧绕组接线型式
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDM					"WindM"					//中压侧绕组接线型式
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDL					"WindL"					//低压侧绕组接线型式
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PHCORRECTMODE			"PhCorrectMode"			//矫正选择
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ADOPTWIND				"AdoptWind"				//测试绕组
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_INSEL					"InSel"					//基准电流
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_INSET					"InSet"					//设定值
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_STEP					"Step"					//测试精度
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_VG1					"Vg1"					//Ua1、Ub1、Uc1
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_VG2					"Vg2"					//Ua2、Ub2、Uc2
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_AROUNDCLOCKNUMHM		"AroundClockNumHM"		//高-中绕组钟点数
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_AROUNDCLOCKNUMHL		"AroundClockNumHL"		//高-低绕组钟点数
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSGROUPMODE		"TransGroupMode"		//测试绕组之间角差(钟点数)
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BALANCETERMS			"BalanceTerms"			//平衡系数计算
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CT					"CTStarPoint"			//CT极性
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ILOADPH				"IbiasCal"				//制动方程
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K1					"Factor1"				//K1
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K2					"Factor2"				//K2
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COMBINEFEATURE		"ComBineFeature"		//组合特性/复合特性
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ZEROSEQELIMITYPE		"ZeroSeqElimiType"		//零序消除方式
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_EARTHING				"Earthing"				//中性点是否接地
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBSIMULATION			"CBSimulation"			//断路器模拟
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBTRIPTIME			"CBTripTime"			//分闸时间
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBCLOSETIME			"CBCloseTime"			//合闸时间
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COORDINATE			"Coordinate"			//坐标

//QDiffCBOpBinarysDlg		开入、开出页面
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_A						"A"			//开入A
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B						"B"			//开入B
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_C						"C"			//开入C
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_D						"R"			//开入D
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_E						"E"			//开入E
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_F						"F"			//开入F
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_G						"G"			//开入G
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_H						"H"			//开入H
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B01					"_B01"		//常态开出1状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B02					"_B02"		//常态开出2状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B03					"_B03"		//常态开出3状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B04					"_B04"		//常态开出4状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B05					"_B05"		//常态开出5状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B06					"_B06"		//常态开出6状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B07					"_B07"		//常态开出7状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B08					"_B08"		//常态开出8状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB01					"_FaultB01"	//故障态开出1状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB02					"_FaultB02"	//故障态开出2状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB03					"_FaultB03"	//故障态开出3状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB04					"_FaultB04"	//故障态开出4状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB05					"_FaultB05"	//故障态开出5状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB06					"_FaultB06"	//故障态开出6状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB07					"_FaultB07"	//故障态开出7状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB08					"_FaultB08"	//故障态开出8状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BINLOGIC				"_AndOr"	//开入逻辑

#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_SELECT				"Select"	//选择
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_STATE					"State"		//状态
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TESTRSLT				"TestRslt"	//测试结果
typedef enum{
	DIFF_ID_DELETEITEM_DLG = 0,//删除测试项目
	DIFF_ID_CLEARSELRESULT = 1//清除测试结果
}STT_MULTI_MACRO_DIFFCBOPTYPE;

#endif
