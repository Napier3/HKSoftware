//PttGlobalDefine.h 

#pragma once

#define PTT_KEY_TestObject		_T("TestObject")

//������Ԫ����<ProtectionRelayBegin>��ʼ��<ProtectionRelayEnd>����
#define PTT_KEY_ProtectionRelay		_T("ProtectionRelay")

//ͨ�ò�������<CommonParameterBegin>��ʼ����<CommonParameterEnd>����
#define PTT_KEY_CommonParameter	_T("CommonParameter")

//����ֵ����<SettingBegin>��ʼ����<SettingEnd>����
#define PTT_KEY_Setting		_T("Setting")

//����ֵ����<GolbalSettingBegin>��ʼ����<GolbalSettingEnd>����
#define PTT_KEY_GlobalSetting		_T("GlobalSetting")

//���������ã���<CFGBegin>��ʼ����<CFGEnd>����
#define PTT_KEY_CFG		_T("CFG")
#define PTT_KEY_IECParameter		_T("IECParameter")

//����������<BinaryBegin>����ʼ<BinaryEnd>
#define PTT_KEY_Binary		_T("Binary")

//�ı��������<TextInputBegin>��ʼ����<ReportEnd>����
#define PTT_KEY_TextInput		_T("TextInput")

//�������ߣ���<CharacterBegin>��ʼ����<CharacterEnd>����
#define PTT_KEY_Character		_T("Character")

//�����������<ReportBegin>��ʼ����<ReportEnd>����
#define PTT_KEY_Report		_T("Report")

//���Ե㣺��<TestPointBegin>��ʼ����<TestPointEnd>����
#define PTT_KEY_TestPoint		_T("TestPoint")

//���Է����<TestItemBegin>��ʼ����<TestItemEnd>����
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
N1=����ǰʱ��;L1=3;U1=��;T1=Edit;V1=0.500;ID1=PreFaultTime;RE1=0;RT1=0;RN1=0;
N2=����ʱ��;L2=3;U2=��;T2=Edit;V2=0.500;ID2=FaultTime;RE2=0;RT2=0;RN2=0;
N3=��·��ģ��;T3=ComboBox;Num3=2;V3=0;S31=��ģ��;S32=ģ��;ID3=BCSIMULATION;RE3=0;RT3=0;RN3=0;
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
