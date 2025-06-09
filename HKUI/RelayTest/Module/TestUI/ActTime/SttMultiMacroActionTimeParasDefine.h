#ifndef STTMULTIMACROACTIONTIMEPARASDEFINE_H
#define STTMULTIMACROACTIONTIMEPARASDEFINE_H

#define IMPEDANCE_FAULT_TYPE_AN                                                 0//阻抗类的故障类型定义
#define IMPEDANCE_FAULT_TYPE_BN                                                 1
#define IMPEDANCE_FAULT_TYPE_CN                                                 2
#define IMPEDANCE_FAULT_TYPE_AB                                                 3
#define IMPEDANCE_FAULT_TYPE_BC                                                 4
#define IMPEDANCE_FAULT_TYPE_CA                                                 5
#define IMPEDANCE_FAULT_TYPE_ThreePhase                                         6
#define IMPEDANCE_FAULT_TYPE_ZeroCurr                                           7
#define IMPEDANCE_FAULT_TYPE_NegCurr                                            8
#define IMPEDANCE_FAULT_TYPE_ThreeParallel                                      9

//动作时间根节点下,按故障类型进行分类创建文件夹
#define STT_MULTI_MACRO_ACTIONTIME_FaultType_Items_ID_AN					 "FaultType_AN"
#define STT_MULTI_MACRO_ACTIONTIME_FaultType_Items_ID_BN					 "FaultType_BN"
#define STT_MULTI_MACRO_ACTIONTIME_FaultType_Items_ID_CN					 "FaultType_CN"
#define STT_MULTI_MACRO_ACTIONTIME_FaultType_Items_ID_AB					 "FaultType_AB"
#define STT_MULTI_MACRO_ACTIONTIME_FaultType_Items_ID_BC					 "FaultType_BC"
#define STT_MULTI_MACRO_ACTIONTIME_FaultType_Items_ID_CA					 "FaultType_CA"
#define STT_MULTI_MACRO_ACTIONTIME_FaultType_Items_ID_ThreePhase			 "FaultType_ThreePhase"
#define STT_MULTI_MACRO_ACTIONTIME_FaultType_Items_ID_ZeroCurr				 "FaultType_ZeroCurr"
#define STT_MULTI_MACRO_ACTIONTIME_FaultType_Items_ID_NegCurr				 "FaultType_NegCurr"
#define STT_MULTI_MACRO_ACTIONTIME_FaultType_Items_ID_ThreeParallel			 "FaultType_ThreeParallel"

//ActionTimeI_Grid.xml 表格参数
#define STT_MULTI_MACRO_ACTIONTIME_GRID_PARAS_ID_SELECT                 "Select"		//选择
#define STT_MULTI_MACRO_ACTIONTIME_GRID_PARAS_ID_STATE					"State"			//状态
#define STT_MULTI_MACRO_ACTIONTIME_GRID_PARAS_ID_TESTRSLT				"TestRslt"		//测试结果
#define STT_MULTI_MACRO_ACTIONTIME_GRID_PARAS_ID_TTRIP_ERRORLOGIC		"Ttrip_ErrorLogic"		//误差类型

//QActionTimeItemParaEditWidget	功能参数页面
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTTYPE				"FaultType"			//故障类型
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTVOLTYPE			"FaultVolType"		//故障电压类型
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_SETTINGTIME				"SettingTime"		//动作时间定值
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTVOLT               "FaultVolt"         //故障电压
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTCURRENT			"FaultCurrent"		//故障电流
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTANGLE				"FaultAngle"		//故障态相位差
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTFRE				"FaultFre"			//故障态频率
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_RELERR					"Ttrip_RelErr"		//相对误差
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_TTRIP_ABSERR_POS		"Ttrip_AbsErr_Pos"	//绝对误差正
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_TTRIP_ABSERR_NEG		"Ttrip_AbsErr_Neg"	//绝对误差负

#define STT_MULTI_MACRO_ACTIONTIME_PARAS_DATATYPE_ID_FAULTTYPE			"ActionTimeFault"			//故障类型数据类型
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_DATATYPE_ID_ERRORTYPE			"RltErrorLogic_Time"		//误差类型数据类型

#define SETTINGTIME_MIN 0
#define SETTINGTIME_MAX 999.999
#define FAULTTIME_MIN 0
#define FAULTTIME_MAX 999.999
#define FAULTCUR_MIN 0
#define FAULTCUR_MAX 20
#define FAULTANGLE_MIN -360
#define FAULTANGLE_MAX 360
#define FAULTFRE_MIN 1
#define FAULTFRE_MAX 1000
#define TTRIPRELERR_MIN 0
#define TTRIPRELERR_MAX 100
#define TTRIPABSERR_MIN 0
#define TTRIPABSERR_MAX 200

#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_DEFAULT			"0"			//缺省值

//QActionTimeCommonParasDlg	通用参数页面
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFAULTTIME		"_PreFaultTime"	//常量时间
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_UPRE				"_UPre"			//常量电压
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_IPRE				"_IPre"			//常量电流
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREANGLE			"PreAngle"		//常量相位差
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFRE				"PreFre"		//常量频率
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTTIME			"FaultTime"		//故障时间裕度

#define PREFAULTTIME_MIN 0
#define PREFAULTTIME_MAX 999.999
#define UPRE_MIN 0
#define UPRE_MAX 130
#define IPRE_MIN 0
#define IPRE_MAX 20
#define PREANGLE_MIN -360
#define PREANGLE_MAX 360
#define PREFRE_MIN 0
#define PREFRE_MAX 1500

//QActionTimeBinarySignalDlg		开入、开出页面
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_A						"_BinSelectA"			//开入A
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B						"_BinSelectB"			//开入B
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_C						"_BinSelectC"			//开入C
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_D						"_BinSelectR"			//开入D
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_E						"_BinSelecta"			//开入E
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_F						"_BinSelectb"			//开入F
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_G						"_BinSelectc"			//开入G
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_H						"_BinSelectr"			//开入H
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_ANDOR					"_AndOr"			//开入逻辑
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B01					"_Bout01"		//常态开出1状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B02					"_Bout02"		//常态开出2状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B03					"_Bout03"		//常态开出3状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B04					"_Bout04"		//常态开出4状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B05					"_Bout05"		//常态开出5状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B06					"_Bout06"		//常态开出6状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B07					"_Bout07"		//常态开出7状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B08					"_Bout08"		//常态开出8状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B1						"_Bout1"		//故障态开出1状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B2						"_Bout2"		//故障态开出2状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B3						"_Bout3"		//故障态开出3状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B4						"_Bout4"		//故障态开出4状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B5						"_Bout5"		//故障态开出5状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B6						"_Bout6"		//故障态开出6状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B7						"_Bout7"		//故障态开出7状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B8						"_Bout8"		//故障态开出8状态

#define STT_MULTI_MACRO_ACTIONTIME_PARAS_FILENAME_MULT			_T("atsgen/ActionTime_Paras.xml")

//QActionTimeAddMultDlg 添加系列界面
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LN_CHECK                    "LN_Check"   //单相接地短路测试
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LL_CHECK                    "LL_Check"   //相间短路测试
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_THREEPHASE_CHECK            "ThreePhase_Check"  //三相短路测试
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_ZEROCURR_CHECK              "ZeroCurr_Check"  //零序电流测试
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_NEGCURR_CHECK               "NegCurr_Check" //负序电流测试
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_THREEPARALLEL_CHECK         "ThreeParallel_Check"   //三相电流并联测试
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTVOL                  "LNFaultVol" //单相接地短路故障电压值
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTVOLTYPE_RADIO       "LNFaultVolType_Radio"  //单相接地短路电压类别 0短路电压 3零序电压
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTVOL                 "LLFaultVol" //相间短路故障电压值
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTVOLTYPE_RADIO       "LLFaultVolType_Radio"   //相间短路电压类别 0短路电压 2负序电压
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTTYPEAN_CHECK       "LNFaultTypeAN_Check"  //单相接地短路故障选择_A
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTTYPEBN_CHECK       "LNFaultTypeBN_Check" //单相接地短路故障选择_B
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTTYPECN_CHECK       "LNFaultTypeCN_Check" //单相接地短路故障选择_C
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTTYPEAB_CHECK       "LLFaultTypeAB_Check" //相间短路故障选择_AB
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTTYPEBC_CHECK       "LLFaultTypeBC_Check" //相间短路故障选择_BC
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTTYPECA_CHECK       "LLFaultTypeCA_Check" //相间短路故障选择_CA

#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_THREEPHASEFAULTVOL      "ThreePhaseFaultVol" //三相短路故障电压
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_ZEROCURRFAULTVOL        "ZeroCurrFaultVol" //零序电流故障电压
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_NEGCURRFAULTVOL         "NegCurrFaultVol" //负序电流故障电压

#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_SETTINGTIME        "SettingTime" //动作时间定值
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_FAULTCURRENT       "FaultCurrent" //故障电流
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_FAULTANGLE         "FaultAngle" //故障态相位差
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_ERRORLOGIC    "Ttrip_ErrorLogic"    //误差类型
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_RELERR        "Ttrip_RelErr"  //相对误差
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_ABSERR_POS    "Ttrip_AbsErr_Pos"    //绝对误差正
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_ABSERR_NEG    "Ttrip_AbsErr_Neg"   //绝对误差负

#define FAULTVOL_MIN 0
#define FAULTVOL_MAX 130

#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_FAULTFRE                "FaultFre"			//故障态频率
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_PREFAULTTIME            "_PreFaultTime"	//常量时间
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_UPRE                    "_UPre"			//常量电压
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_IPRE                    "_IPre"			//常量电流
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_PREANGLE                "PreAngle"		//常量相位差
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_PREFRE                  "PreFre"		//常量频率
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_FAULTTIME               "FaultTime"		//故障时间裕度
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_A						"_BinSelectA"			//开入A
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B						"_BinSelectB"			//开入B
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_C						"_BinSelectC"			//开入C
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_D						"_BinSelectD"			//开入D
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_E						"_BinSelectE"			//开入E
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_F						"_BinSelectF"			//开入F
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_G						"_BinSelectG"			//开入G
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_H						"_BinSelectH"			//开入H
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_ANDOR					"_AndOr"			//开入逻辑
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B01                     "_Bout01"		//常态开出1状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B02                     "_Bout02"		//常态开出2状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B03                     "_Bout03"		//常态开出3状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B04                     "_Bout04"		//常态开出4状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B05                     "_Bout05"		//常态开出5状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B06                     "_Bout06"		//常态开出6状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B07                     "_Bout07"		//常态开出7状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B08                     "_Bout08"		//常态开出8状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B1						"_Bout1"		//故障态开出1状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B2						"_Bout2"		//故障态开出2状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B3						"_Bout3"		//故障态开出3状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B4						"_Bout4"		//故障态开出4状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B5						"_Bout5"		//故障态开出5状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B6						"_Bout6"		//故障态开出6状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B7						"_Bout7"		//故障态开出7状态
#define STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B8						"_Bout8"		//故障态开出8状态

//选择页面按键显示
//#define STT_MULTI_MACRO_ACTIONTIME_PARAEDIT_BTN_DELETESELITEM		_T("删除当前")
//#define STT_MULTI_MACRO_ACTIONTIME_PARAEDIT_BTN_DELETEALLITEM		_T("删除全部")
//#define STT_MULTI_MACRO_ACTIONTIME_PARAEDIT_BTN_CLEARSELRESULT		_T("清除当前")
//#define STT_MULTI_MACRO_ACTIONTIME_PARAEDIT_BTN_CLEARALLRESULT		_T("清除全部")


#endif // STTMULTIMACROACTIONTIMEPARASDEFINE_H
