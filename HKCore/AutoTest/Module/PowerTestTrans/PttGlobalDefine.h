//PttGlobalDefine.h 

#pragma once

#define PTT_KEY_TestObject		_T("TestObject")

//基本单元：以<ProtectionRelayBegin>开始，<ProtectionRelayEnd>结束
#define PTT_KEY_ProtectionRelay		_T("ProtectionRelay")

//通用参数：从<CommonParameterBegin>开始，至<CommonParameterEnd>结束
#define PTT_KEY_CommonParameter	_T("CommonParameter")

//整定值：从<SettingBegin>开始，至<SettingEnd>结束
#define PTT_KEY_Setting		_T("Setting")

//整定值：从<GolbalSettingBegin>开始，至<GolbalSettingEnd>结束
#define PTT_KEY_GlobalSetting		_T("GlobalSetting")

//测试仪配置：从<CFGBegin>开始，至<CFGEnd>结束
#define PTT_KEY_CFG		_T("CFG")
#define PTT_KEY_IECParameter		_T("IECParameter")

//开关量：从<BinaryBegin>，开始<BinaryEnd>
#define PTT_KEY_Binary		_T("Binary")

//文本输入项：从<TextInputBegin>开始，至<ReportEnd>结束
#define PTT_KEY_TextInput		_T("TextInput")

//特性曲线：从<CharacterBegin>开始，至<CharacterEnd>结束
#define PTT_KEY_Character		_T("Character")

//报告参数：从<ReportBegin>开始，至<ReportEnd>结束
#define PTT_KEY_Report		_T("Report")

//测试点：从<TestPointBegin>开始，至<TestPointEnd>结束
#define PTT_KEY_TestPoint		_T("TestPoint")

//测试分项：从<TestItemBegin>开始，至<TestItemEnd>结束
#define PTT_KEY_TestItem		_T("TestItem")

#define PTT_KEY_CalculatorExp		_T("CalculatorExp")

#define PTT_KEY_DeviceName		_T("DeviceName")
#define PTT_KEY_DeviceType		_T("DeviceType")
#define PTT_KEY_Manufacturer		_T("Manufacturer")
#define PTT_KEY_ProtectiveRelayName		_T("ProtectiveRelayName")
#define PTT_KEY_Property		_T("Property")
#define PTT_KEY_WordReportName		_T("WordReportName")
#define PTT_KEY_Update		_T("Update")

#define PTT_KEY_TestComName2		_T("TestComName2")
#define PTT_KEY_HINT						_T("HINT")
#define PTT_KEY_HINTSELECT			_T("HINTSELECT")
#define PTT_KEY_TESTNAME				_T("TESTNAME")

#define PTT_KEY_ASSESS				_T("ASSESS")

#define PTT_SETTING_ISET1_          _T("Iset1")
#define PTT_SETTING_ISET2_          _T("Iset2")
#define PTT_SETTING_ISET3_          _T("Iset3")

/*
N1=故障前时间;L1=3;U1=秒;T1=Edit;V1=0.500;ID1=PreFaultTime;RE1=0;RT1=0;RN1=0;
N2=故障时间;L2=3;U2=秒;T2=Edit;V2=0.500;ID2=FaultTime;RE2=0;RT2=0;RN2=0;
N3=断路器模拟;T3=ComboBox;Num3=2;V3=0;S31=不模拟;S32=模拟;ID3=BCSIMULATION;RE3=0;RT3=0;RN3=0;
*/
#define PTT_KEY_DATA_ATTR_N		_T("N")
#define PTT_KEY_DATA_ATTR_NUM		_T("Num")
#define PTT_KEY_DATA_ATTR_L		_T("L")
#define PTT_KEY_DATA_ATTR_U		_T("U")
#define PTT_KEY_DATA_ATTR_T		_T("T")
#define PTT_KEY_DATA_ATTR_V		_T("V")
#define PTT_KEY_DATA_ATTR_ID		_T("ID")
#define PTT_KEY_DATA_ATTR_RE		_T("RE")
#define PTT_KEY_DATA_ATTR_RT		_T("RT")
#define PTT_KEY_DATA_ATTR_RN		_T("RN")

#define PTT_KEY_DATA_TYPE_COMBOBOX	_T("ComboBox")
//#define PTT_VALUE_DATA_TYPE_COMBOBOX	0x15151515
//#define PTT_VALUE_DATA_TYPE_OTHERS  	0x00000000

BOOL ptt_PopOpenPowerTestTplFileDlg(CString &strPath);
