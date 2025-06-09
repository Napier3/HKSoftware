﻿#ifndef STTMULTIMACROVOLINVERPARASDEFINE_H
#define STTMULTIMACROVOLINVERPARASDEFINE_H

//#define STT_MACRO_ID_VolInverseTime     "VolInverseTime"

#define VOLINVERSE_FAULT_TYPE_AE                                                 0//故障类型定义
#define VOLINVERSE_FAULT_TYPE_BE                                                 1
#define VOLINVERSE_FAULT_TYPE_CE                                                 2
#define VOLINVERSE_FAULT_TYPE_AB                                                 3
#define VOLINVERSE_FAULT_TYPE_BC                                                 4
#define VOLINVERSE_FAULT_TYPE_CA                                                 5
#define VOLINVERSE_FAULT_TYPE_ABC                                                6
#define VOLINVERSE_FAULT_TYPE_3U0                                                7
#define VOLINVERSE_FAULT_TYPE_U2                                                8
#define VOLINVERSE_FAULT_TYPE_A                                                9
#define VOLINVERSE_FAULT_TYPE_B                                                10
#define VOLINVERSE_FAULT_TYPE_C                                                11

//跟节点下,按故障类型进行分类创建文件夹
#define STT_MULTI_MACRO_VOLINVERSE_Items_ID_AE         "VolInverseTime-AE"
#define STT_MULTI_MACRO_VOLINVERSE_Items_ID_BE         "VolInverseTime-BE"
#define STT_MULTI_MACRO_VOLINVERSE_Items_ID_CE         "VolInverseTime-CE"
#define STT_MULTI_MACRO_VOLINVERSE_Items_ID_AB         "VolInverseTime-AB"
#define STT_MULTI_MACRO_VOLINVERSE_Items_ID_BC         "VolInverseTime-BC"
#define STT_MULTI_MACRO_VOLINVERSE_Items_ID_CA         "VolInverseTime-CA"
#define STT_MULTI_MACRO_VOLINVERSE_Items_ID_ABC        "VolInverseTime-ABC"
#define STT_MULTI_MACRO_VOLINVERSE_Items_ID_3U0        "VolInverseTime-3U0"
#define STT_MULTI_MACRO_VOLINVERSE_Items_ID_U2        "VolInverseTime-U2"

#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_CurrentChangeStart				"CurrentChangeStart"
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_CurrentChangeFinal				"CurrentChangeFinal"
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_CurrentChangeStep			"CurrentChangeStep"

//	功能参数页面
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTTYPE			"FaultType"			//故障类型
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTCURR			"FaultCurrent"			//短路电流
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_VOLTAGE			"FaultVolt"			//电压
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_ANG			"FaultAngle"			//故障态相位差
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultHZ			        "FaultFre"			//频率
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_TSETTING			"MaxFaultTime"			//动作时间
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_PLUS			"AbsErr_Plus"			//动作时间绝对正误差限
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_MINUS			"AbsErr_Minus"			//动作时间绝对负误差限
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_RelErr			"Ttrip_RelErr"			//相对误差
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_ErrorLogic				"Ttrip_ErrorLogic"

//通用参数页面
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_PreFaultTime			"_PreFaultTime"		//故障前时间
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_UPre				    "_UPre"			//故障前电压
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_IPre		            "_IPre"	   //故障前电流
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_PreAngle			    "PreAngle"			//故障前相位差
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_NORMHZ			"PreFaultFre"			//频率
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_CTPos				"CTPos"				//CT正极性
//#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_ErrorType				"ErrorType"				//误差类型
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultTime			"FaultTimeMargin"			//故障时间裕度
//
////m_pAddMultiItemSelectDlg 选择页面按键显示
//#define STT_MULTI_MACRO_VolInverTime_BTN_DELETESELITEM			_T("删除当前")
//#define STT_MULTI_MACRO_VolInverTime_BTN_DELETEALLITEM			_T("删除全部")
//#define STT_MULTI_MACRO_VolInverTime_BTN_CLEARSELRESULT		_T("清除当前")
//#define STT_MULTI_MACRO_VolInverTime_BTN_CLEARALLRESULT		_T("清除全部")

//		开入、开出页面
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_AndOr				"_AndOr"	//开入逻辑
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_A						"_BinSelectA"			//开入A
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_B						"_BinSelectB"			//开入B
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_C						"_BinSelectC"			//开入C
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_D						"_BinSelectR"			//开入D
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_E						"_BinSelecta"			//开入E
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_F						"_BinSelectb"			//开入F
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_G						"_BinSelectc"			//开入G
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_H						"_BinSelectr"			//开入H
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B01					"_Bout01"		//常态开出1状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B02					"_Bout02"		//常态开出2状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B03					"_Bout03"		//常态开出3状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B04					"_Bout04"		//常态开出4状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B05					"_Bout05"		//常态开出5状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B06					"_Bout06"		//常态开出6状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B07					"_Bout07"		//常态开出7状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B08					"_Bout08"		//常态开出8状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B1					"_Bout1"		//故障态开出1状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B2					"_Bout2"		//故障态开出2状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B3					"_Bout3"		//故障态开出3状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B4					"_Bout4"		//故障态开出4状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B5					"_Bout5"		//故障态开出5状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B6					"_Bout6"		//故障态开出6状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B7					"_Bout7"		//故障态开出7状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID__B8					"_Bout8"		//故障态开出8状态

#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_A_CHECK						"FaultTypeA_Check"			
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_B_CHECK						"FaultTypeB_Check"			
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_C_CHECK						"FaultTypeC_Check"			
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_AB_CHECK						"FaultTypeAB_Check"		
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_BC_CHECK						"FaultTypeBC_Check"		
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_CA_CHECK						"FaultTypeCA_Check"	
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_3U0_CHECK						"FaultType3U0_Check"
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_U2_CHECK					"FaultTypeU2_Check"	
#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABC_CHECK					"FaultTypeABC_Check"

#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_PreFaultTime			"_PreFaultTime"		//故障前时间
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_UPre				    "_UPre"			//故障前电压
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_IPre		            "_IPre"	   //故障前电流
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_PreAngle			    "PreAngle"			//故障前相位差
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_NORMHZ			"PreFaultFre"			//频率
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_CTPos				"CTPos"				//CT正极性
//#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_ErrorType				"ErrorType"				//误差类型
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_FaultTime			"FaultTimeMargin"			//故障时间裕度
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_A						"_BinSelectA"			//开入A
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B						"_BinSelectB"			//开入B
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_C						"_BinSelectC"			//开入C
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_D						"_BinSelectD"			//开入D
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_E						"_BinSelectE"			//开入E
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_F						"_BinSelectF"			//开入F
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_G						"_BinSelectG"			//开入G
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_H						"_BinSelectH"			//开入H
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_ANDOR					"_AndOr"			//开入逻辑
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B01                     "_Bout01"		//常态开出1状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B02                     "_Bout02"		//常态开出2状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B03                     "_Bout03"		//常态开出3状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B04                     "_Bout04"		//常态开出4状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B05                     "_Bout05"		//常态开出5状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B06                     "_Bout06"		//常态开出6状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B07                     "_Bout07"		//常态开出7状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B08                     "_Bout08"		//常态开出8状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B1						"_Bout1"		//故障态开出1状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B2						"_Bout2"		//故障态开出2状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B3						"_Bout3"		//故障态开出3状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B4						"_Bout4"		//故障态开出4状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B5						"_Bout5"		//故障态开出5状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B6						"_Bout6"		//故障态开出6状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B7						"_Bout7"		//故障态开出7状态
#define STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B8						"_Bout8"		//故障态开出8状态

//特性曲线
#define STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_VP						"Vpset"			//特性曲线参数(Vp)
#define STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_D							"xD"			//特性曲线参数(D)
#define STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_K							"xK"			//特性曲线参数(K)
#define STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_A							"Td"			//特性曲线参数(A)
#define STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_B							"xB"			//特性曲线参数(B)
#define STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_C							"xC"			//特性曲线参数(C)
#define STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_E							"xE"			//特性曲线参数(E)
#define STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_P							"xP"			//特性曲线参数(P)
//#define STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_M						"xm"			//特性曲线参数(M)
#define STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_DownU						"xDownU"		//特性曲线参数(低电压)
#define STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_OverU						"xOverU"		//特性曲线参数(过电压)

#define STT_MULTI_MACRO_VolInverTime_PARAS_ID_DEFAULT					"0"

#endif // STTMULTIMACRODISTANCEPARASDEFINE_H