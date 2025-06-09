#ifndef STTMULTIMACROPOWERDIRPARASDEFINE_H
#define STTMULTIMACROPOWERDIRPARASDEFINE_H
#include"../SttMultiMacroParasDefine.h"

#define TESTPHASE_AN                                                 0//测试相定义
#define TESTPHASE_BN                                                 1
#define TESTPHASE_CN                                                 2
#define TESTPHASE_ZEROTEST                                           3
#define TESTPHASE_NEGTEST                                            4
#define TESTPHASE_AB                                                 5
#define TESTPHASE_BC                                                 6
#define TESTPHASE_CA                                                 7
#define TESTPHASE_ABC												 8


#define TESTPHASE_AN_SHOW                                                 0//测试相下拉框显示定义
#define TESTPHASE_BN_SHOW                                                 1
#define TESTPHASE_CN_SHOW                                                 2
#define TESTPHASE_AB_SHOW                                                 3
#define TESTPHASE_BC_SHOW                                                 4
#define TESTPHASE_CA_SHOW                                                 5
#define TESTPHASE_ABC_SHOW												  6
#define TESTPHASE_ZEROTEST_SHOW                                           7
#define TESTPHASE_NEGTEST_SHOW                                            8

//功率方向根节点下,按测试相进行分类创建文件夹
#define STT_MULTI_MACRO_POWERDIR_TestPhase_Items_ID_AN					 "TestPhase_AN"
#define STT_MULTI_MACRO_POWERDIR_TestPhase_Items_ID_BN					 "TestPhase_BN"
#define STT_MULTI_MACRO_POWERDIR_TestPhase_Items_ID_CN					 "TestPhase_CN"
#define STT_MULTI_MACRO_POWERDIR_TestPhase_Items_ID_AB					 "TestPhase_AB"
#define STT_MULTI_MACRO_POWERDIR_TestPhase_Items_ID_BC					 "TestPhase_BC"
#define STT_MULTI_MACRO_POWERDIR_TestPhase_Items_ID_CA					 "TestPhase_CA"
#define STT_MULTI_MACRO_POWERDIR_TestPhase_Items_ID_ABC					 "TestPhase_ABC"
#define STT_MULTI_MACRO_POWERDIR_TestPhase_Items_ID_ZeroTest			 "TestPhase_ZeroCurr"
#define STT_MULTI_MACRO_POWERDIR_TestPhase_Items_ID_NegTest				 "TestPhase_NegCurr"

//PowerDirectionI_Grid.xml 表格参数
#define STT_MULTI_MACRO_POWERDIR_GRID_PARAS_ID_SELECT               "Select"              //选择
#define STT_MULTI_MACRO_POWERDIR_GRID_PARAS_ID_STATE				"State"               //状态
#define STT_MULTI_MACRO_POWERDIR_GRID_PARAS_ID_TTRIP_ERRORTYPE		"ErrorType"           //误差类型
#define STT_MULTI_MACRO_POWERDIR_GRID_PARAS_ID_ANGLEF               "AngleF"              //边界1(°)
#define STT_MULTI_MACRO_POWERDIR_GRID_PARAS_ID_ANGLES				"AngleS"              //边界2(°)
#define STT_MULTI_MACRO_POWERDIR_GRID_PARAS_ID_TTRIP_MAXANGLE       "MaxAngle"            //最大灵敏角实测值(°)

//QPowerDirItemParaEditWidget	功能参数页面
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_TESTPHASE					"TestPhase"			//测试相
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTPHASE				"FaultPhase"		//故障相
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTVOLT					"FaultVolt"         //故障电压
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTCURRENT				"FaultCurrent"		//故障电流
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTTIME					"FaultTime"			//故障时间
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_MTA						"MTA"               //最大灵敏角
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ACTIONAREARANGE			"AngleRange"		//动作区范围
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_STEPVALUE					"StepValue"         //变化步长
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_MAXANGLE_ABSERR			"MaxAngle_AbsErr"	//最大灵敏角绝对误差限
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANGLEF_ABSERR				"AngleF_AbsErr"     //边界角1绝对误差
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANGLES_RELERR				"AngleS_AbsErr"		//边界角2相对误差
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABSERR					"MaxAngle_AbsErr"	//绝对误差
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_RELERR					"MaxAngle_RelErr"	//相对误差

//故障相下拉框内容
#define STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_AN		_T("AN")
#define STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_BN		_T("BN")
#define STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_CN		_T("CN")
#define STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_AB		_T("AB")
#define STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_BC		_T("BC")
#define STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_CA		_T("CA")
#define STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_ABC		_T("ABC")
//#define STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_ZERO	_T("零序电流")
//#define STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_NEG	_T("负序电流")

#define FAULTVOLT_MAX 130
#define FAULTVOLT_MIN 0
#define FAULTCUR_MAX 20
#define FAULTCUR_MIN 0
#define FAULTTIME_MAX 999.999
#define FAULTTIME_MIN 0
#define MTA_MAX 360
#define MTA_MIN -360
#define STEPVALUE_MAX 360
#define STEPVALUE_MIN -360
//#define STT_MULTI_MACRO_PARAS_AbsErrorMaxValue 200//zhouhj 2024.10.1 各模块公共宏定义移到公共位置,其它宏定义各模块负责人自己处理
//#define STT_MULTI_MACRO_PARAS_AbsErrorMinValue 0
//#define STT_MULTI_MACRO_PARAS_RelErrorMaxValue 100
//#define STT_MULTI_MACRO_PARAS_RelErrorMinValue 0

#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_DEFAULT			"0"			//缺省值

//QPowerDirCommonParasDlg	通用参数页面
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_PREPARETIME		"_PrepareTime"		//变化前时间
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_PREFAULTTIME		"_PreFaultTime"		//故障前时间
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_UPRE				"_UPre"				//常量电压幅值
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_UPHSET			"_UPhSet"			//常量电压相序
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_IPRE				"_IPre"				//常量电流幅值
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_IPHSET			"_IPhSet"			//常量电流相序
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_PREANGLE			"PreAngle"			//常量相角(U-I)
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANGLEMODE			"AngleMode"			//角度定义
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_CONNECTMODE		"ConnectMode"		//接线方式
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANGLEMARGIN		"AngleMargin"		//角度裕度

#define STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_PHASESET                 "PhaseSet"		//相序设置数据类型
#define STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_PSUPDANGLEMODE			"PsuPDAngleMode"		//角度定义数据类型
#define STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_CONNECTTYPE              "ConnectType"		//接线方式数据类型

#define PREPARETIME_MAX 999.999
#define PREPARETIME_MIN 0
#define PREFAULTTIME_MAX 999.999
#define PREFAULTTIME_MIN 0
#define UPRE_MAX 130
#define UPRE_MIN 0
#define IPRE_MAX 20
#define IPRE_MIN 0
#define PREANGLE_MAX 360
#define PREANGLE_MIN -360
#define ANGLEMARGIN_MAX 360
#define ANGLEMARGIN_MIN -360
#define FAULTTIMEMARGIN_MAX 999.999
#define FAULTTIMEMARGIN_MIN 0


//QPowerDirBinarySignalDlg		开入、开出页面
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_A						"_BinSelectA"			//开入A
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B						"_BinSelectB"			//开入B
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_C						"_BinSelectC"			//开入C
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_D						"_BinSelectR"			//开入D
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_E						"_BinSelecta"			//开入E
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_F						"_BinSelectb"			//开入F
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_G						"_BinSelectc"			//开入G
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_H						"_BinSelectr"			//开入H
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANDOR					"_AndOr"			//开入逻辑
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B01					"_Bout01"		//常态开出1状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B02					"_Bout02"		//常态开出2状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B03					"_Bout03"		//常态开出3状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B04					"_Bout04"		//常态开出4状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B05					"_Bout05"		//常态开出5状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B06					"_Bout06"		//常态开出6状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B07					"_Bout07"		//常态开出7状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B08					"_Bout08"		//常态开出8状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B1						"_Bout1"		//故障态开出1状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B2						"_Bout2"		//故障态开出2状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B3						"_Bout3"		//故障态开出3状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B4						"_Bout4"		//故障态开出4状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B5						"_Bout5"		//故障态开出5状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B6						"_Bout6"		//故障态开出6状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B7						"_Bout7"		//故障态开出7状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_B8						"_Bout8"		//故障态开出8状态

#define STT_MULTI_MACRO_POWERDIR_PARAS_FILENAME_MULT			_T("atsgen/PowerDirectionI_Paras.xml")


//QPowerDirAddMultDlg		添加系列
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANTest_CHECK				"ANTest_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNTest_CHECK			"BNTest_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNTest_CHECK			"CNTest_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABTest_CHECK				"ABTest_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_BCTest_CHECK			"BCTest_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_CATest_CHECK			"CATest_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZeroTest_CHECK			"ZeroTest_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegTest_CHECK		"NegTest_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeA_CHECK						"ANFaultTypeA_Check"			
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeAB_CHECK						"ANFaultTypeAB_Check"			
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeCA_CHECK						"ANFaultTypeCA_Check"			
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeABC_CHECK						"ANFaultTypeABC_Check"		
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeB_CHECK						"BNFaultTypeB_Check"		
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeAB_CHECK						"BNFaultTypeAB_Check"	
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeBC_CHECK					"BNFaultTypeBC_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeABC_CHECK						"BNFaultTypeABC_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeC_CHECK						"CNFaultTypeC_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeBC_CHECK					"CNFaultTypeBC_Check"	
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeCA_CHECK					"CNFaultTypeCA_Check"	
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeABC_CHECK						"CNFaultTypeABC_Check"		
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABFaultTypeAB_CHECK					"ABFaultTypeAB_Check"	
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_BCFaultTypeBC_CHECK					"BCFaultTypeBC_Check"	
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_CAFaultTypeCA_CHECK						"CAFaultTypeCA_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeZero_CHECK						"ZerFaultTypeZero_Check"	
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeA_CHECK					"ZerFaultTypeA_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeB_CHECK						"ZerFaultTypeB_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeC_CHECK						"ZerFaultTypeC_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeNegative_CHECK					"NegFaultTypeNegative_Check"	
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeA_Check_CHECK					"NegFaultTypeA_Check"	
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeB_CHECK					"NegFaultTypeB_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeC_CHECK						"NegFaultTypeC_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeAB_CHECK						"NegFaultTypeAB_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeBC_CHECK					"NegFaultTypeBC_Check"	
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeCA_CHECK					"NegFaultTypeCA_Check"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ADDMULT_FAULTVOL					"FaultVol"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ADDMULT_FAULTCUR					"FaultCur"
#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_ADDMULT_ERRTYPE					"MaxAngle_ErrorLogic"

#define STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_ERRORTYPE				"RltErrorLogic_Time"

//paras.xml中定义的id
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_PREPARETIME		"_PrepareTime"		//变化前时间
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_PREFAULTTIME		"_PreFaultTime"		//故障前时间
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_UPRE				"_UPre"				//常量电压幅值
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_UPHSET			"_UPhSet"			//常量电压相序
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_IPRE				"_IPre"				//常量电流幅值
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_IPHSET			"_IPhSet"			//常量电流相序
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_PREANGLE			"PreAngle"			//常量相角(U-I)
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_ANGLEMODE			"AngleMode"			//角度定义
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_CONNECTMODE		"ConnectMode"		//接线方式
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_ANGLEMARGIN		"AngleMargin"		//角度裕度
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_A						"_BinSelectA"			//开入A
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B						"_BinSelectB"			//开入B
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_C						"_BinSelectC"			//开入C
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_D						"_BinSelectD"			//开入D
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_E						"_BinSelectE"			//开入E
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_F						"_BinSelectF"			//开入F
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_G						"_BinSelectG"			//开入G
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_H						"_BinSelectH"			//开入H
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_ANDOR					"_AndOr"			//开入逻辑
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B01					"_Bout01"		//常态开出1状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B02					"_Bout02"		//常态开出2状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B03					"_Bout03"		//常态开出3状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B04					"_Bout04"		//常态开出4状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B05					"_Bout05"		//常态开出5状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B06					"_Bout06"		//常态开出6状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B07					"_Bout07"		//常态开出7状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B08					"_Bout08"		//常态开出8状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B1						"_Bout1"		//故障态开出1状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B2						"_Bout2"		//故障态开出2状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B3						"_Bout3"		//故障态开出3状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B4						"_Bout4"		//故障态开出4状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B5						"_Bout5"		//故障态开出5状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B6						"_Bout6"		//故障态开出6状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B7						"_Bout7"		//故障态开出7状态
#define STT_MULTI_MACRO_POWERDIR_PARAS_ADDMULT_ID_B8						"_Bout8"		//故障态开出8状态

#define STT_MULTI_MACRO_POWERDIR_PARAS_ID_DEFAULT					"0"
//选择页面按键显示
//#define STT_MULTI_MACRO_POWERDIR_PARAEDIT_BTN_DELETESELITEM		_T("删除当前")
//#define STT_MULTI_MACRO_POWERDIR_PARAEDIT_BTN_DELETEALLITEM		_T("删除全部")
//#define STT_MULTI_MACRO_POWERDIR_PARAEDIT_BTN_CLEARSELRESULT		_T("清除当前")
//#define STT_MULTI_MACRO_POWERDIR_PARAEDIT_BTN_CLEARALLRESULT		_T("清除全部")


#endif // STTMULTIMACROPOWERDIRPARASDEFINE_H
