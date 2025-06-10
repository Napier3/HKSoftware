#ifndef _SttTestCntrCmdDefine_H__
#define _SttTestCntrCmdDefine_H__

//UI command
#define STT_CNTR_CMD_Exit						"Exit"
#define STT_CNTR_CMD_Menu					"Menu"
#define STT_CNTR_CMD_StartTest				"StartTest"
#define STT_CNTR_CMD_TestThis				"TestThis"
#define STT_CNTR_CMD_ManuTriger			    "ManuTriger"
#define STT_CNTR_CMD_StopTest				"StopTest"
#define STT_CNTR_CMD_AddMacro			"AddMacro"
#define STT_CNTR_CMD_ItemList				"ItemList"
#define STT_CNTR_CMD_TemplateView		"TemplateView"
#define STT_CNTR_CMD_ReportView			"ReportView"
#define STT_CNTR_CMD_HardConfig			"HardConfig"
#define STT_CNTR_CMD_IECConfig				"IECConfig"
#define  STT_CNTR_CMD_AinDataMapConfig		"AinDataMapConfig" //2023/8/29 wjs
#define STT_CNTR_CMD_VectorDrawView	"VectorDrawView"
#define STT_CNTR_CMD_WaveDrawView		"WaveDrawView"
#define STT_CNTR_CMD_StateDrawView		"StateDrawView"
#define STT_CNTR_CMD_PowerDrawView		"PowerDrawView"
#define STT_CNTR_CMD_CharDrawView		"CharDrawView"
#define STT_CNTR_CMD_NewTest				"NewTest"
#define STT_CNTR_CMD_OpenTemplate		"OpenTemplate"
#define STT_CNTR_CMD_OpenTest		   "OpenTest"
#define STT_CNTR_CMD_SaveTemplate		"SaveTemplate"
#define STT_CNTR_CMD_SaveAsTemplate	"SaveAsTemplate"
#define STT_CNTR_CMD_SaveTest				"SaveTest"
#define STT_CNTR_CMD_SaveAsTest				"SaveAsTest"
#define STT_CNTR_CMD_SaveAsRpt				"SaveAsRpt"//20230607 zhouhj 单独存储报告
#define STT_CNTR_CMD_ExportWordRpt			"ExportWordRpt"//202306025  shaolei  导出XML及WORD报告
#define STT_CNTR_CMD_SystemParas		"SystemParas"
#define STT_CNTR_CMD_GeneralParas		"GeneralParas"
#define STT_CNTR_CMD_SwitchSet				"SwitchSet"
#define STT_CNTR_CMD_DcSet					"DcSet"
#define STT_CNTR_CMD_OutputPower		"OutputPower"
#define STT_CNTR_CMD_DeviceCom			"DeviceCom"
#define STT_CNTR_CMD_LangSetting			"LangSetting"
#define STT_CNTR_CMD_ReportSetting			"ReportSetting"    //20220214开会新增，设置报告头 sf 20220215
#define STT_CNTR_CMD_ChRsMaps				"ChRsMaps"
// #define STT_CNTR_CMD_TemplateView		"TemplateView"//202308014 suyang 重复删除
#define STT_CNTR_CMD_ItemListView			"ItemListView"
// #define STT_CNTR_CMD_ReportView			"ReportView"//202308014 suyang 重复删除
#define STT_CNTR_CMD_DeviceComView		"DeviceComView"
// #define STT_CNTR_CMD_VectorDrawView	"VectorDrawView"//20231108 suyang 重复删除
#define STT_CNTR_CMD_WaveDrawView		"WaveDrawView"
#define STT_CNTR_CMD_StateDrawView		"StateDrawView"
//#define STT_CNTR_CMD_CharaView			"CharaView" //20220803 zhouhj 重复删除
#define STT_CNTR_CMD_SequenceView		"SequenceView"
#define STT_CNTR_CMD_InfoView				"InfoView"
#define STT_CNTR_CMD_LogView				"LogView"
#define STT_CNTR_CMD_VersionInfo			"VersionInfo"
#define STT_CNTR_CMD_AuxIPSet 			"AuxIPSet"   //20220629 zhouhj 增加用于设置辅IP地址
#define STT_CNTR_CMD_Liveupdate			"Liveupdate"//在线升级
#define STT_CNTR_CMD_LiveupdateDevice	"LiveupdateDevice"
#define STT_CNTR_CMD_ULiveupdate			"ULiveupdate"//U盘升级
#define STT_CNTR_CMD_CloudConfig			"CloudConfig"
#define STT_CNTR_CMD_UpdateAdjCoef				"UpdateAdjCoef"
#define STT_CNTR_CMD_RegisterRemoteTest		"RegisterRemoteTest"
#define STT_CNTR_CMD_RemoteRegistAssist		"RemoteRegistAssist"
#define STT_CNTR_CMD_DownloadTestTemplate	"DownloadTestTemplate"
#define STT_CNTR_CMD_DownloadPpTemplate		"DownloadPpTemplate"
#define STT_CNTR_CMD_UploadingReport			"UploadingReport"
#define STT_CNTR_CMD_ConnectApp			"ConnectApp"
#define STT_CNTR_CMD_Debug			         "Debug"
#define STT_CNTR_CMD_FileMngr			         "FileMngr"//文件管理
#define STT_CNTR_CMD_AuxDCOutput				"AuxDCOutput"//辅助直流  zhangyq 20230227
#define STT_CNTR_CMD_LumPowerView       "LuminousPower"//光功率chenling
#define STT_CNTR_CMD_OutputDebug        "OutputDebug" //输出调试 lcq



#define STT_CNTR_CMD_ScreenShot			    "ScreenShot"
#define STT_CNTR_CMD_SelSCLFile             "SelSCLFile"
#define STT_CNTR_CMD_SaveEdit             "SaveEdit"   //保存编辑   shaolei  2022-12-19
#define STT_CNTR_CMD_IecCapDialog         "IecCapDialog" //报文探测对话框
#define STT_CNTR_CMD_ClearReportRslts		"ClearReportRslts"  //清除报告数据  shaolei  2023-7-17
#define STT_CNTR_CMD_TransPcapFile         "TransPcapFile" //将Socket保存的转换生成Pcap文件  zhouhj 2023.8.4
#define STT_CNTR_CMD_ImportDvmFile         "ImportDvmFile" //导入模型文件，模型替换  shaolei 2023-8-14
#define STT_CNTR_CMD_Minimize				"Minimize"//最小化 zhouyangyong 2024-2-26

//2023-2-21  lijunqing 被测装置通信后台
#define STT_CNTR_CMD_PpIotEngineClient           "PpIotEngineClient" //装置通讯

//2023.11.15 lichao PNS331 新增
#define STT_CNTR_CMD_CommConfig			        "CommConfig"  //通讯配置
#define STT_CNTR_CMD_PkgMonitor			        "PkgMonitor"  //报文监听
#define STT_CNTR_CMD_PpXmlFileMngr			   "PpXmlFileMngr"  //规约模板管理
#define STT_CNTR_CMD_DvmFileMngr			   "DvmFileMngr"  //点表文件管理
#define STT_CNTR_CMD_RemoteCtrl			        "RemoteCtrl"  //显示遥控功能界面


//2023-3-5  lijunqing  设置IP地址，用于自动测试
#define STT_CNTR_CMD_NetworkConfig          "NetworkConfig"

//Original Test Macro
#define  STT_ORG_MACRO_ManualTest               "ManualTest"
#define  STT_ORG_MACRO_StateTest                "StateTest"
#define  STT_ORG_MACRO_GradientTest             "GradientTest"
#define  STT_ORG_MACRO_HarmTest                 "HarmTest"
#define  STT_ORG_MACRO_ReplayTest               "ReplayTest"
#define  STT_ORG_MACRO_IecCapTest               "IecCapTest"
#define  STT_ORG_MACRO_SmvAbnTest                "SmvAbnTest"
#define  STT_ORG_MACRO_GseAbnTest                "GseAbnTest"
#define  STT_ORG_MACRO_DiffCurr6ITest            "DiffCurr6ITest"
#define  STT_ORG_MACRO_ElecRailwayDiffTest       "ElecRailwayDiffTest"
#define  STT_ORG_MACRO_LineDiffCurr6ITest        "LineDiffCurr6ITest"
#define  STT_ORG_MACRO_BusDiffCurr6ITest        "BusDiffCurr6ITest"
#define  STT_ORG_MACRO_CurrInverseTimeTest       "CurrInverseTimeTest"
#define  STT_ORG_MACRO_VolInverseTimeTest       "VolInverseTimeTest"
#define  STT_ORG_MACRO_UFInverseTimeTest        "UFInverseTimeTest"
#define  STT_ORG_MACRO_SequenceManuTest         "SequenceManuTest"
#define  STT_ORG_MACRO_PowerManuTest         "PowerManuTest"//wangtao 20240607 功率
#define  STT_ORG_MACRO_LineVolManuTest         "LineVolManuTest"
#define  STT_ORG_MACRO_DistanceTest            "DistanceTest"

#define  STT_ORG_MACRO_DistanceTest_I            "DistanceTest_I"//国际版-距离保护

#define  STT_ORG_MACRO_DistanceSearchTest       "DistanceSearchTest"
#define  STT_ORG_MACRO_DistSearchOneTest       "DistSearchOneTest"
#define  STT_ORG_MACRO_SoeTest                  "SoeTest"
#define  STT_ORG_MACRO_SequenceGradientTest       "SequenceGradientTest"
#define  STT_ORG_MACRO_FaultGradientTest       "FaultGradientTest" //yuanting 2023-12-28

#define  STT_ORG_MACRO_LineVolGradientTest        "LineVolGradientTest"
#define  STT_ORG_MACRO_RemoteMeasTest               "RemoteMeasTest"//遥测 zhangyq 2023.11.20
#define  STT_ORG_MACRO_RemoteCtrlTest               "RemoteCtrlTest"//遥控
#define STT_ORG_MACRO_ShortTimeOverTest			"ShortTimeOverTest"

#define  STT_ORG_MACRO_VolTimeTypeSecTest			"VolTimeTypeSecTest"  // 电压时间型分段模式  xueyangfan  2024.01.22  
#define STT_CNTR_CMD_FAParasSetDialog       "FAParasSetDialog"   //FA参数设置  xueyangfan 2024-01-22
#define  STT_ORG_MACRO_AntiShakeTimeTest            "AntiShakeTimeTest"   //防抖时间测试         xueyangfan  2024.03.05

#define  STT_ORG_MACRO_BinaryManuTest               "BinaryManuTest"

#define  STT_ORG_MACRO_MUAccuracyTest             "MUAccuracyTest"
//#define  STT_ORG_MACRO_MUZeroDriftTest            "MUZeroDriftTest"
#define  STT_ORG_MACRO_MUTimingAccurTest          "MUTimingAccurTest"
#define  STT_ORG_MACRO_MUPunctAccurTest           "MUPunctAccurTest"
#define  STT_ORG_MACRO_MUFirstCycleTest           "MUFirstCycleTest"
#define  STT_ORG_MACRO_MUMaxPeakErrorTest         "MUMaxPeakErrorTest"
#define  STT_ORG_MACRO_MUAttenConstantTest        "MUAttenConstantTest"
#define  STT_ORG_MACRO_MUAccurAutoTest             "MUAccurAutoTest"
#define  STT_ORG_MACRO_MUAutoTest                   "MUAutoTest" //2023-10-24 lcq
#define  STT_ORG_MACRO_TerminalAutoTest            "TerminalAutoTest" //20231120chenling智能终端自动测试
#define  STT_ORG_MACRO_IntelligentTest         "IntelligentTest"//20231125gongyiping智能终端测试

#define  STT_ORG_MACRO_ImpedanceManuTest               "ImpedanceManuTest" //2024.6.11 zhangyq通用试验（阻抗）
#define  STT_ORG_MACRO_CBOperateTest          "CBOperateTest" 

//2022-10-3  shaolei
#define  STT_ORG_MACRO_Iec61850Config       "Iec61850Config"
#define  STT_ORG_MACRO_SystemConfig         "SystemConfig"
#define  STT_ORG_MACRO_ChMapsConfig         "ChMapsConfig"

#define  STT_GB_ITEMID_HdConfig				"HdConfig"
#define  STT_GB_ITEMID_IEC61850Config       "IEC61850Config"
#define  STT_GB_ITEMID_SystemConfig			"SystemConfig"

#define  STT_HTML_MACRO_ZeroTest               "ZeroTest"   //zhouhj 增加用到手动触发的模块的测试功能ID
#define  STT_HTML_MACRO_DistanceTest           "DistanceTest"
#define  STT_HTML_MACRO_OverCurrentTest        "OverCurrentTest"
#define  STT_HTML_MACRO_RecloseAccTest         "RecloseAccTest"
//#define  STT_HTML_MACRO_CBOperateTest         "CBOperateTest"  zhouhj 2024.6.20 该功能已改为原生界面


//从主界面进入,在测试控制程序打开对话框界面的对话框的ID
// #define STT_OPENDIALOG_ID_OnlineUpdate            "OnlineUpdate"//在线升级 //部分已在上面定义,改为统一定义
// #define STT_OPENDIALOG_ID_OfflineUpdate           "OfflineUpdate"//离线升级
//#define STT_OPENDIALOG_ID_OutputPower             "OutputPower"//输出功率
// #define STT_OPENDIALOG_ID_HardwareSet             "HardwareSet"//硬件设置
// #define STT_OPENDIALOG_ID_VersionInfor            "VersionInfor"//版本信息
// #define STT_OPENDIALOG_ID_FileMngr                 "FileMngr"//文件管理
// #define STT_OPENDIALOG_ID_LanguageSet             "LanguageSet"//语言设置




//debug
#define STT_DEBUG_SetDatas     "debugSetDatas"
#define STT_DEBUG_SetDatasFile1     "debugSetDatasFile1"
#define STT_DEBUG_SetDatasFile2     "debugSetDatasFile2"
#define STT_DEBUG_SaveDatasFile     "debugSaveDatasFile"
#define STT_DEBUG_GetDatas     "debugGetDatas"
#define STT_DEBUG_UpdateReport     "debugUpdateReport"
#define STT_DEBUG_FillReport     "debugGetFillReport"
#define STT_DEBUG_ItemStateChanged     "debugItemStateChanged"
#define STT_DEBUG_OutPutWidget     "debugOutPutWidget"
#define STT_DEBUG_StartTest     "debugStartTest"
#define STT_DEBUG_StopTest     "debugStopTest"
#define STT_DEBUG_SaveTest     "debugSaveTest"
#define STT_DEBUG_GenForDebug     "debugGenForDebug"
#define STT_DEBUG_GenTemplate     "debugGenTemplate"
#define STT_DEBUG_SaveAsSysFiles     "debugSaveAsSysFiles"

//2022-1-21  lijunqing
#define STT_TEST_STATE_TESTTING	    "Testing"
#define STT_TEST_STATE_TEST_STOPED    "TestStoped"
#define STT_TEST_STATE_TEST_FINISHED    "TestFinished"

//2022-4-10  lijunqing  IecDetect,IecRecord  保留用
#define STT_CNTR_CMD_IecDetect			"IecDetect"
#define STT_CNTR_CMD_IecRecord			"IecRecord"
#define STT_CNTR_CMD_IecCap			    "IecCap"

#define STT_CNTR_CMD_IecCapWriteFile			    "IecCapWriteFile"
#define STT_CNTR_CMD_IecCapDebugHead			    "IecCapDebugHead"

#define STT_CNTR_CMD_CustomSet                  "CustomSet"   //自定义设置按钮

//2022-12-02  lijunqing  测试助手
#define STT_CNTR_CMD_Assist     "Assist"

//主框架程序发送给助手的事件定义
#define Event_ID_IecAddCb			"IecAddCb"
#define Event_ID_OnTestStarted		"OnTestStarted"
#define Event_ID_OnTestFinished		"OnTestFinished"
#define Event_ID_IecSelCb				"IecSelCb"

#endif // _SttTestCntrCmdDefine_H__
