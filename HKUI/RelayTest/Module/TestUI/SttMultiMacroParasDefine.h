#ifndef STTMULTIMACROPARASDEFINE_H
#define STTMULTIMACROPARASDEFINE_H

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE			"ZoneType"			//区段选择
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING			"TSetting"			//时间定值
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG				"ZAng"				//阻抗角
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE			"FaultType"			//故障类型
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC			"Zone_ErrorLogic"		//动作时间误差逻辑判断

#define STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemZone			"SystemZone"		//曲线故障类型对应区段下拉框显示数据id 前缀
#define STT_MULTI_MACRO_PARAS_DATATYPE_ID_RltErrorLogic_Time			"RltErrorLogic_Time"		//时间误差类别对应区段下拉框显示数据id 前缀
#define STT_MULTI_MACRO_PARAS_DATATYPE_ID_RltErrorLogic_TimeEx		"RltErrorLogic_TimeEx"//时间误差类别-含不动作
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS		"Zone_AbsErr_p"		//动作时间绝对正误差限
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS		"Zone_AbsErr_n"		//动作时间绝对负误差限
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR			"Zone_RelErr"		//动作时间相对误差限

#define STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE			"ZoneType"			//区段选择
#define STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING			"TSetting"			//时间定值
#define STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE			"FaultType"			//故障类型
#define STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC			"CurveErr_ErrorLogic"		//动作时间误差逻辑判断
#define STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR			"CurveErr_RelErr"	//相对误差
#define STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR			"CurveErr_AbsErr"	//绝对误差

#define STT_MULTI_MACRO_PARAS_RelErrorMaxValue 100//20240929 luozibing 设置相对误差绝对误差取值范围
#define STT_MULTI_MACRO_PARAS_RelErrorMinValue 0
#define STT_MULTI_MACRO_PARAS_AbsErrorMaxValue 200
#define STT_MULTI_MACRO_PARAS_AbsErrorMinValue 0

#define STT_MULTI_MACRO_ANGMAX	360
#define STT_MULTI_MACRO_ANGMIN	-360

#define STT_MULTI_MACRO_ZONELine	0//线路长度
#define STT_MULTI_MACRO_ZONEAll		1//所有区域

#endif // STTMULTIMACROPARASDEFINE_H