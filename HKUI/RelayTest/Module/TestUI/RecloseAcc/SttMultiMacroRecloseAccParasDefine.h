#ifndef STTMULTIMACRORECLOSEACCPARASDEFINE_H
#define STTMULTIMACRORECLOSEACCPARASDEFINE_H
#include"../SttMultiMacroParasDefine.h"

#define IMPEDANCE_FAULT_TYPE_AN                                                 0//阻抗类的故障类型定义
#define IMPEDANCE_FAULT_TYPE_BN                                                 1
#define IMPEDANCE_FAULT_TYPE_CN                                                 2
#define IMPEDANCE_FAULT_TYPE_AB                                                 3
#define IMPEDANCE_FAULT_TYPE_BC                                                 4
#define IMPEDANCE_FAULT_TYPE_CA                                                 5
#define IMPEDANCE_FAULT_TYPE_ABN                                                6
#define IMPEDANCE_FAULT_TYPE_BCN                                                7
#define IMPEDANCE_FAULT_TYPE_CAN                                                8
#define IMPEDANCE_FAULT_TYPE_ABC                                                9
#define IMPEDANCE_FAULT_TYPE_ONE                                                10

//距离跟节点下,按故障类型进行分类创建文件夹
#define STT_MULTI_MACRO_RECLOSEACC_FaultType_Items_ID_AN         "FaultType_AN"
#define STT_MULTI_MACRO_RECLOSEACC_FaultType_Items_ID_BN         "FaultType_BN"
#define STT_MULTI_MACRO_RECLOSEACC_FaultType_Items_ID_CN         "FaultType_CN"
#define STT_MULTI_MACRO_RECLOSEACC_FaultType_Items_ID_AB         "FaultType_AB"
#define STT_MULTI_MACRO_RECLOSEACC_FaultType_Items_ID_BC         "FaultType_BC"
#define STT_MULTI_MACRO_RECLOSEACC_FaultType_Items_ID_CA         "FaultType_CA"
#define STT_MULTI_MACRO_RECLOSEACC_FaultType_Items_ID_ABN        "FaultType_ABN"
#define STT_MULTI_MACRO_RECLOSEACC_FaultType_Items_ID_BCN        "FaultType_BCN"
#define STT_MULTI_MACRO_RECLOSEACC_FaultType_Items_ID_CAN        "FaultType_CAN"
#define STT_MULTI_MACRO_RECLOSEACC_FaultType_Items_ID_ABC        "FaultType_ABC"
#define STT_MULTI_MACRO_RECLOSEACC_FaultType_Items_ID_ONE        "FaultType_ONE"


//RecloseAccI_Grid.xml 表格参数
#define STT_MULTI_MACRO_RECLOSEACC_GRID_PARAS_ID_SELECT                 "Select"		//选择
#define STT_MULTI_MACRO_RECLOSEACC_GRID_PARAS_ID_STATE					"State"			//状态
#define STT_MULTI_MACRO_RECLOSEACC_GRID_PARAS_ID_TRIPTIME				"TripTime"		//跳闸时间(s)
#define STT_MULTI_MACRO_RECLOSEACC_GRID_PARAS_ID_TTRIPD					"TtripD"		//重合时间(s)
#define STT_MULTI_MACRO_RECLOSEACC_GRID_PARAS_ID_TTRIPACC				"TtripAcc"		//后加速时间(s)

//QRecloseAccItemParaEditWidget	功能参数页面
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTYPE1				"FaultType1"		//第一次故障类型
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1						"Z1"				//第一次阻抗
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1PH					"Z1Ph"				//第一次阻抗角
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ISET1					"ISet1"				//第一次短路电流
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTYPE2				"FaultType2"		//第二次故障类型
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z2						"Z2"				//第二次阻抗
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z2PH					"Z2Ph"				//第二次阻抗角
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ISET2					"ISet2"				//第二次短路电流
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FRE						"Fre"				//频率
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_K0MODE					"K0Mode"			//零序补偿系数计算方法
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_KLKR					"KlKr"			//K0
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ANGKX					"AngKx"			//Phi
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TSET1					"TSet1"		//第一次动作时间
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TSET2					"TSet2"		//第二次动作时间
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_RECLOSEACCTIME			"RecloseTime"			//重合时间
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTPERMANENT			"FaultPermanent" //故障性质
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXMODE					"UxMode"		//抽取电压选择
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTFRE				"VZFreq"			//抽取电压频率
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTMAG				"UxInputMag"			//跳闸后抽取电压
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTANG				"UxInputAng"			//跳闸后抽取电压相位
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_RELERR					"Ttrip_RelErr"		//动作时间相对误差
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ABSERR_POS              "Ttrip_AbsErr_Pos"	//动作时间绝对误差正
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ABSERR_NEG              "Ttrip_AbsErr_Neg"	//动作时间绝对误差负
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ERRTYPE                 "Ttrip_ErrorLogic"	//动作时间误差类型
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_RELERR			"TtripD_RelErr"		//重合闸时间相对误差
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_ABSERR_POS        "TtripD_AbsErr_Pos"	//重合闸时间绝对误差正
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_ABSERR_NEG        "TtripD_AbsErr_Neg"	//重合闸时间绝对误差负
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_ERRTYPE           "TtripD_ErrorLogic"	//重合闸时间误差类型
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPACC_RELERR			"TtripAcc_RelErr"		//后加速时间相对误差
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPACC_ABSERR_POS      "TtripAcc_AbsErr_Pos"	//后加速时间绝对误差正
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPACC_ABSERR_NEG      "TtripAcc_AbsErr_Neg"	//后加速时间绝对误差负
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPACC_ERRTYPE         "TtripAcc_ErrorLogic"	//后加速时间误差类型


#define STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_K0						"|K0|:"
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_PHI_K0					"Phi(K0):"
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_RERL					"RE/RL:"
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_XEXL					"XE/XL:"
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_Z0Z1					"|Z0/Z1|:"
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_PHI_Z0Z1				"Phi(Z0/Z1):"

#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_DEFAULT			"0"			//缺省值

#define STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_SYSTEMFAULT            "SystemFault"		//故障类型数据类型
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_FAULTCHARACTER         "FaultCharacter"		//故障性质数据类型
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_UXMODE                 "UxMode"		//故障性质数据类型

#define Z1_MAX 999.999
#define Z1_MIN 0
#define Z1PH_MAX 360
#define Z1PH_MIN -360
#define R1_MAX 999.999
#define R1_MIN -999.999
#define X1_MAX 999.999
#define X1_MIN -999.999
#define ISET1_MAX 20
#define ISET1_MIN 0
#define FRE_MAX 999.999
#define FRE_MIN 0
#define KLKR_MAX 999.999
#define KLKR_MIN 0
#define ANGKX_MAX 360
#define ANGKX_MIN -360
#define TSET1_MAX 999.999
#define TSET1_MIN 0
#define RECLOSEACCTIME_MAX 999.999
#define RECLOSEACCTIME_MIN 0
#define UXINPUTFRE_MAX 999.999 
#define UXINPUTFRE_MIN 0
#define UXINPUTMAG_MAX 130
#define UXINPUTMAG_MIN 0
#define UXINPUTANG_MAX 360
#define UXINPUTANG_MIN -360
//zhouhj 2024.10.1 各模块公共宏定义移到公共位置,其它宏定义各模块负责人自己处理
//#define STT_MULTI_MACRO_PARAS_RelErrorMaxValue 100
//#define STT_MULTI_MACRO_PARAS_RelErrorMinValue 0
//#define STT_MULTI_MACRO_PARAS_AbsErrorMaxValue 200
//#define STT_MULTI_MACRO_PARAS_AbsErrorMinValue 0

//QRecloseCommonParasDlg	通用参数页面
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PREFAULTTIME			"PreFaultTime"			//故障前时间
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTIME				"FaultTime"				//故障时间裕度
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ACTIONTIME              "ActionTime"            //最小动作时间
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTRIGMODE			"FaultTrigMode"			//故障触发方式
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PTPOS					"PTPos"					//TV安装位置
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_CTPOS					"CTPos"					//TA正极性
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOAD					"ILoad"					//负荷电流
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOADPH					"ILoadPh"				//负荷功角
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_SIMULATEBREAKERDELAY	"SimulateBreakerDelay"	//断路器模拟
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKBREAKTIME			"BrkBreakTime"			//分闸时间
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKCLOSETIME			"BrkCloseTime"			//合闸时间

#define STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_FAULTTRIGMODEPNV   "FaultTrigModePnv"		//故障触发方式数据类型
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_PTPOSITION			"PTPosition"			//TV安装位置数据类型
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_CTPOS              "CTPos"                 //TA正极性数据类型
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_CBSIMULSEL			"CBSimulSel"			//断路器模拟数据类型

#define PREFAULTTIME_MAX 999.999
#define PREFAULTTIME_MIN 0
#define FAULTTIME_MAX 999.999
#define FAULTTIME_MIN 0
#define ACTIONTIME_MAX 999.999
#define ACTIONTIME_MIN 0
#define ILOAD_MAX 999
#define ILOAD_MIN 0
#define ILOADPH_MAX 360
#define ILOADPH_MIN -360
#define BRKBREAKTIME_MAX 999999
#define BRKBREAKTIME_MIN 0
#define BRKCLOSETIME_MAX 999999
#define BRKCLOSETIME_MIN 0

//QRecloseAccBinarySignalDlg		开入、开出页面
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BINSELECT				"BinSelect"				//开入选择
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_A						"A"			//开入A
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B						"B"			//开入B
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_C						"C"			//开入C
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_D						"R"			//开入D
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_E						"E"			//开入E
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_F						"F"			//开入F
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_G						"G"			//开入G
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_H						"H"			//开入H
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B01						"_B01"		//开出1状态
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B02						"_B02"		//开出2状态
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B03						"_B03"		//开出3状态
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B04						"_B04"		//开出4状态
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B05						"_B05"		//开出5状态
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B06						"_B06"		//开出6状态
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B07						"_B07"		//开出7状态
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B08						"_B08"		//开出8状态
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTSWITCHMODE		"_OutputSwitchMode"		//开出翻转启动方式
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTKEEPTIME			"_OutputKeepTime"		//开出保持时间
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTDELAYTIME			"_OutputDelayTime"		//开出翻转时刻

#define STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DINPUTSTATE          "DInputState"		//输入开关量状态数据类型
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOUTPUTSTATE         "DOutputState"		//输出开关量状态数据类型
#define STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOutStartMode        "DOutStartMode"		//开出启动方式数据类型

#define STT_MULTI_MACRO_RECLOSEACC_PARAS_FILENAME_MULT			_T("atsgen/RecloseAcc_Paras.xml")

#define OUTPUTKEEPTIME_MAX 999999
#define OUTPUTKEEPTIME_MIN 0
#define OUTPUTDELAYTIME_MAX 999999
#define OUTPUTDELAYTIME_MIN 0

#define STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_ERRTYPE   "RltErrorLogic_TimeEx"		//误差类型数据类型

//选择页面按键显示
//#define STT_MULTI_MACRO_RECLOSEACC_PARAEDIT_BTN_DELETESELITEM		_T("删除当前")
//#define STT_MULTI_MACRO_RECLOSEACC_PARAEDIT_BTN_DELETEALLITEM		_T("删除全部")
//#define STT_MULTI_MACRO_RECLOSEACC_PARAEDIT_BTN_CLEARSELRESULT		_T("清除当前")
//#define STT_MULTI_MACRO_RECLOSEACC_PARAEDIT_BTN_CLEARALLRESULT		_T("清除全部")

typedef enum{
	DELETEITEM_DLG   = 0,//删除测试项目
	CLEARSELRESULT   = 1//清除测试结果
}SELECTDLG_STATE;


#endif // STTMULTIMACRORECLOSEACCPARASDEFINE_H
