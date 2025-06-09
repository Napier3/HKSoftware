#ifndef STTMULTIMACRODIFFPARASDEFINE_H
#define STTMULTIMACRODIFFPARASDEFINE_H

#define STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_RATE	        "DiffCurrChar"       //差动曲线搜索/差动比率制动测试-PsuDiffRateTest
#define STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_TIME	        "ActTime"       //动作时间/差动6I动作时间测试-PsuDiffTimeTest
#define STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM	        "HarmRate"       //谐波制动搜索/差动6I谐波制动测试-PsuDiffHarmTest
//QDIFFResultEstimateDlg	功能参数页面

//差动曲线搜索
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE		"FaultType"			//差动曲线搜索-故障相别
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL			"EndVal"			//差动曲线搜索-搜索上限
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL			"BeginVal"			//差动曲线搜索-搜索下限
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_STEP				"Step"				//差动曲线搜索-测试精度
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FREQ				"Freq"				//差动曲线搜索-频率
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IR				"Ir"				//差动曲线搜索-制动电流
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING		"IdSetting"			//差动曲线搜索-差动电流整定值
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTIME		"FaultTime"			//差动曲线搜索-最大故障时间
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ABSERR			"Diff_AbsErr"			//差动曲线搜索-绝对误差
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_RELERR			"Diff_RelErr"			//差动曲线搜索-相对误差
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_RSLTEVAL			"Diff_ErrorLogic"           //结果评估逻辑

//动作时间
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FAULTTYPE		"FaultType"			//动作时间-故障相别
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_IR				"Ir"				//动作时间-制动电流
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ID				"Id"				//动作时间-差动电流Id
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_RELERR			"Ttrip_RelErr"			//动作时间-相对误差
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ABSERRPOS		"Ttrip_AbsErrPos"			//动作时间-正绝对误差
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ABSERRNEG		"Ttrip_AbsErrNeg"			//动作时间-负绝对误差
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FREQ				"Freq"				//动作时间-频率
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FAULTTIME		"FaultTime"			//动作时间-最大故障时间
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_RSLTEVAL			"Ttrip_ErrorLogic"           //结果评估逻辑

//谐波制动搜索
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_FAULTTYPE		"FaultType"			//谐波制动搜索-故障相别
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_HARMINDEX		"HarmIndex"			//谐波制动搜索-谐波次数
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ID				"Id"				//谐波制动搜索-差动电流
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_BEGINVAL			"BeginVal"			//谐波制动搜索-搜索始值
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ENDVAL			"EndVal"			//谐波制动搜索-搜索终值
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_STEP				"Step"				//谐波制动搜索-测试精度
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_OUTSIDE			"HarmOutSide"			//谐波制动搜索-谐波输出侧
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RATEHARMSET		"RateHarmSet"			//谐波制动搜索-谐波制动系数定值
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_FAULTTIME		"FaultTime"			//谐波制动搜索-最大故障时间
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RELERR			"Harm_RelErr"			//谐波制动搜索-相对误差
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ABSERRPOS		"Harm_AbsErrPos"		//谐波制动搜索-正绝对误差
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ABSERRNEG		"Harm_AbsErrNeg"		//谐波制动搜索-负绝对误差
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RSLTEVAL			"Harm_ErrorLogic"           //结果评估逻辑

//QDIFFCommonParasDlg	通用参数页面
#define STT_MULTI_MACRO_DIFF_PARAS_ID_PREPARETIME           "PrepareTime"       //准备时间(s)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_PREFAULTTIME			"PreFaultTime"		//故障前时间(s)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SETTINGTIME			"SettingTime"		//整定动作时间(s)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TIMEAFTER				"TimeAfter"         //动作后持续时间(s)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_KPSETMODE             "KPSetMode"			//各侧平衡系数
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SN					"Sn"				//变压器额定容量(MVA)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_HUN					"HUn"				//高压侧额定电压(kV)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_MUN					"MUn"				//中压侧额定电压(kV)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_LUN					"LUn"				//低压侧额定电压(kV)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CTPH					"CTPh"				//高压侧CT一次值(A)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CTPM					"CTPm"				//中压侧CT一次值(A)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CTPL					"CTPl"				//低压侧CT一次值(A)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CTSH					"CTSh"				//高压侧CT二次值(A)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CTSM					"CTSm"				//中压侧CT二次值(A)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CTSL					"CTSl"				//低压侧CT二次值(A)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_KPHSET				"KphSet"			//高压侧差动平衡系数
#define STT_MULTI_MACRO_DIFF_PARAS_ID_KPMSET				"KpmSet"			//中压侧差动平衡系数
#define STT_MULTI_MACRO_DIFF_PARAS_ID_KPLSET				"KplSet"			//低压侧差动平衡系数
#define STT_MULTI_MACRO_DIFF_PARAS_ID_WINDH					"WindH"				//高压侧绕组接线型式
#define STT_MULTI_MACRO_DIFF_PARAS_ID_WINDM					"WindM"				//中压侧绕组接线型式
#define STT_MULTI_MACRO_DIFF_PARAS_ID_WINDL					"WindL"				//低压侧绕组接线型式
#define STT_MULTI_MACRO_DIFF_PARAS_ID_PHCORRECTMODE			"PhCorrectMode"		//校正选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_ADOPTWIND				"AdoptWind"			//测试绕组
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE1		"TransGroupModeHM"	//高-中绕组钟点数
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE2		"TransGroupModeHL"	//高-低绕组钟点数
#define STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE		"TransGroupMode"	//测试绕组之间角差(钟点数)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_JXFACTOR				"JXFactor"			//平衡系数计算
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SEARCHMODE			"SearchMode"		//搜索方法
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CTPOINT				"CTPoint"			//CT极性
#define STT_MULTI_MACRO_DIFF_PARAS_ID_IREQUATION			"IrEquation"		//制动方程
#define STT_MULTI_MACRO_DIFF_PARAS_ID_K						"K"					//K1
#define STT_MULTI_MACRO_DIFF_PARAS_ID_K2					"K2"				//K2
#define STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE		"CombineFeature"	//组合特性
#define STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE      "ZeroSeqElimiType"  //零序消除方式
#define STT_MULTI_MACRO_DIFF_PARAS_ID_EARTHING				"Earthing"			//接地
#define STT_MULTI_MACRO_DIFF_PARAS_ID_STEP					"Step"				//测试精度
#define STT_MULTI_MACRO_DIFF_PARAS_ID_VG1					"Vg1"				//Ua、Ub、Uc(V)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_VG2					"Vg2"				//Ua2、Ub2、Uc2(V)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_INSEL					"InSel"             //基准电流选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_INSET					"InSet"				//基准电流设定值
#define STT_MULTI_MACRO_DIFF_PARAS_ID_IQUICK				"IQuick"			//差动速断电流
#define STT_MULTI_MACRO_DIFF_PARAS_ID_IDOOR					"IDoor"				//差动门槛电流
#define STT_MULTI_MACRO_DIFF_PARAS_ID_MINAXIS				"MinAxis"			//定值整定方式 
//QDIFFBinarysDlg		开入、开出页面
#define STT_MULTI_MACRO_DIFF_PARAS_ID__B01						"_Bout1"			//开出1状态
#define STT_MULTI_MACRO_DIFF_PARAS_ID__B02						"_Bout2"			//开出2状态
#define STT_MULTI_MACRO_DIFF_PARAS_ID__B03						"_Bout3"			//开出3状态
#define STT_MULTI_MACRO_DIFF_PARAS_ID__B04						"_Bout4"			//开出4状态
#define STT_MULTI_MACRO_DIFF_PARAS_ID__B05						"_Bout5"			//开出5状态
#define STT_MULTI_MACRO_DIFF_PARAS_ID__B06						"_Bout6"			//开出6状态
#define STT_MULTI_MACRO_DIFF_PARAS_ID__B07						"_Bout7"			//开出7状态
#define STT_MULTI_MACRO_DIFF_PARAS_ID__B08						"_Bout8"			//开出8状态
#define STT_MULTI_MACRO_DIFF_PARAS_ID_AndOr						"_AndOr"			//开入逻辑
#define STT_MULTI_MACRO_DIFF_PARAS_ID_A							"_BinSelectA"		//开入A选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_B							"_BinSelectB"		//开入B选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_C							"_BinSelectC"		//开入C选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_D							"_BinSelectR"		//开入R选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_E							"_BinSelecta"		//开入a选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_F							"_BinSelectb"		//开入b选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_G							"_BinSelectc"		//开入c选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_H							"_BinSelectr"		//开入r选择

//选择页面按键显示
#define STT_MULTI_MACRO_DIFF_PARAEDIT_BTN_ADDONE_SEARCHLINE			_T("添加搜索线")
#define STT_MULTI_MACRO_DIFF_PARAEDIT_BTN_ADDONE_MULTIITEM			_T("批量添加")
#define STT_MULTI_MACRO_DIFF_PARAEDIT_BTN_DELETESELITEM			_T("删除当前")
#define STT_MULTI_MACRO_DIFF_PARAEDIT_BTN_DELETEALLITEM			_T("删除全部")
#define STT_MULTI_MACRO_DIFF_PARAEDIT_BTN_CLEARSELRESULT		_T("清除当前")
#define STT_MULTI_MACRO_DIFF_PARAEDIT_BTN_CLEARALLRESULT		_T("清除全部")

//添加系列
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_BEGINVAL				"BeginVal"	//制动电流始值()
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_ENDVAL				"EndVal"	//制动电流终值()
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_STEP				"Step"	//变化步长()
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_TIME				"FaultTime"	//最大故障时间(s)
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_POINTS				"Points"	//测试点数

#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_RATE				"RateDiff_Check"	//功能选择-差动曲线搜索
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_HARM				"HarmRate_Check"	//功能选择-谐波制动搜索
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_TIME				"ActTime_Check"		//功能选择-动作时间
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_IR						"Ir"			//功能选择-比率制动制动电流
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_ID						"Id"			//功能选择-比率制动差动电流

#define STT_MULTI_MACRO_DIFF_PARAS_ID_StartCurrPointNum              _T("StartCurrPointNum")
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef1PointNum              _T("RateCoef1PointNum")   
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef2PointNum              _T("RateCoef2PointNum")   
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef3PointNum              _T("RateCoef3PointNum")   
#define STT_MULTI_MACRO_DIFF_PARAS_ID_QuickCurrPointNum              _T("QuickCurrPointNum")   

#define STT_MULTI_MACRO_DIFF_PARAS_ID_StartCurrErrorBand              _T("StartCurrErrorBand")
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef1ErrorBand              _T("RateCoef1ErrorBand")
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef2ErrorBand              _T("RateCoef2ErrorBand")
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef3ErrorBand              _T("RateCoef3ErrorBand")
#define STT_MULTI_MACRO_DIFF_PARAS_ID_QuickCurrErrorBand              _T("QuickCurrErrorBand")

#define STT_MULTI_MACRO_DIFF_PARAS_ID_StartCurr_Check              _T("StartCurr_Check")//启动电流选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef1_Check              _T("RateCoef1_Check")//比率指定系数1选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef2_Check              _T("RateCoef2_Check")//比率指定系数2选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef3_Check              _T("RateCoef3_Check")//比率指定系数3选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_QuickCurr_Check              _T("QuickCurr_Check")//差动速断选择

#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_AN				"FaultTypeAE_Check"	//故障选择-A-E
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_BN				"FaultTypeBE_Check"	//故障选择-B-E
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_CN				"FaultTypeCE_Check"	//故障选择-C-E
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_AB				"FaultTypeAB_Check"	//故障选择-A-B
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_BC				"FaultTypeBC_Check"	//故障选择-B-C
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_CA				"FaultTypeCA_Check"	//故障选择-C-A
#define STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_ABC				"FaultTypeABC_Check"	//故障选择-ABC

//结果评估
#define STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_ABSERR				"Diff_AbsErr"	//差动搜索值绝对误差限
#define STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_RELERR				"Diff_RelErr"	//差动搜索值相对误差限
#define STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_RSLTEVAL			"Diff_ErrorLogic"	//差动搜索值误差逻辑判断
#define STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_ABSERRPOS			"HarmRate_AbsErrPos"	//谐波制动搜索值正绝对误差限
#define STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_ABSERRNEG		"HarmRate_AbsErrNeg"	//谐波制动搜索值负绝对误差限
#define STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_RELERR				"HarmRate_RelErr"	//谐波制动搜索值相对误差限
#define STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_RSLTEVAL				"HarmRate_ErrorLogic"	//谐波制动搜索值误差逻辑判断
#define STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_ABSERRPOS			"ActTime_AbsErrPos"	//比率制动动作时间正绝对误差限
#define STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_ABSERRNEG		"ActTime_AbsErrNeg"	//比率制动动作时间负绝对误差限
#define STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_RELERR				"ActTime_RelErr"	//比率制动动作时间相对误差限
#define STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_RSLTEVAL			"ActTime_ErrorLogic"	//比率制动动作时间误差逻判断

//曲线编辑设置参数
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_MINAXIS				"MinAxis"		//定值整定方式
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_INSEL				"InSel"			//基准电流选择
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_INSET				"InSet"			//基准电流设定值
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_IQUICK				"IQuick"		//差动速断电流
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_IDOOR				"IDoor"			//差动门槛电流
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KNEEPOINTS			"KneePoints"	//比率制动拐点数
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_LIMP1				"Limp1"			//比率制动拐点1电流
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_LIMP2				"Limp2"			//比率制动拐点2电流
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_LIMP3				"Limp3"			//比率制动拐点3电流
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KID0					"Kid0"			//启动段斜率
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KID1					"Kid1"			//基波比率制动特性斜率1
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KID2					"Kid2"			//基波比率制动特性斜率2
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KID3					"Kid3"			//基波比率制动特性斜率3
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_CUSTOMCHAR			"_bCustomChar"	//是否自定义曲线
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_RATEHARM				"RateHarm"			//谐波制动搜索-谐波制动系数定值
#define STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_TIMEAFTER			"AfterFaultTime"         //动作后持续时间(s)

//DiffTestI_Grid.xml 表格参数
#define STT_MULTI_MACRO_DIFF_GRID_PARAS_ID_SELECT                 "Select"		//选择
#define STT_MULTI_MACRO_DIFF_GRID_PARAS_ID_STATE					"State"			//状态
#define STT_MULTI_MACRO_DIFF_GRID_PARAS_ID_TESTRSLT				"TestRslt"		//测试结果

#define STT_MULTI_MACRO_DIFF_PARAS_ID_DEFAULT			"0"			//缺省值

typedef enum{
DIFF_ID_PSUDIFFRATE = 0,   
DIFF_ID_PSUDIFFTIME = 1,   
DIFF_ID_PSUDIFFHARM = 2,      
}STT_MULTI_MACRO_DIFFTYPE;
#endif // STTMULTIMACRODIFFPARASDEFINE_H