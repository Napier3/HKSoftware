#ifndef TMT_ADJUST_SYS_PARA_MODULE_DEF_H
#define TMT_ADJUST_SYS_PARA_MODULE_DEF_H

//ModuleType
#define STT_MODULE_TYPE_VOLT             0//������ѹ���
#define STT_MODULE_TYPE_CURRENT          1//�����������
#define STT_MODULE_TYPE_DIGITAL_0G8M     2//8�����׿����ְ�FPGA,9-2+ft3
#define STT_MODULE_TYPE_DIGITAL_2G6M     3//6�����׿�,2��ǧ�׿����ְ�FPGA,9-2+ft3
#define STT_MODULE_TYPE_DIGITAL_4G4M     4//4�����׿�,4��ǧ�׿����ְ�FPGA,9-2+ft3
#define STT_MODULE_TYPE_DCCURRENT        5//ֱ���������
#define STT_MODULE_TYPE_DCVOLT           6//ֱ����ѹ���
#define STT_MODULE_TYPE_SWITCH           7//��������չ��
#define STT_MODULE_TYPE_WEEK_EX          8//С�ź�ģ����
//#define STT_MODULE_TYPE_WEEK_MAIN        9//����С�ź� 20231023ͳһ��STT_MODULE_TYPE_WEEK_EX
#define STT_MODULE_TYPE_FT3				 10//��ֱFT3��,��ft3
// #define STT_MODULE_TYPE_PFC6A_VOLT		 11//PFC6A��ѹ���������һ������λ��
// #define STT_MODULE_TYPE_PFC6A_CURRENT	 12//PFC6A6ͨ�����ݰ�3U+3I����·���ģ��,����FPGA 6U/6I���·���ʽ
#define STT_MODULE_TYPE_VOLT_CURRENT	 11   //U��I��ϲ��
#define STT_MODULE_TYPE_MEAS_VOLT		 12   //�ɼ�ģ��,�������ģ�鹲��ģ��λ��
#define STT_MODULE_TYPE_MEAS_CURRENT	 13   //�ɼ�ģ��,�������ģ�鹲��ģ��λ��
//#define STT_MODULE_TYPE_WEEK_EX_48       14	//48·С�ź�ģ���� ͳһ��STT_MODULE_TYPE_WEEK_EX
#define STT_MODULE_TYPE_Stable2M         14 //�ȿ�2M
#define STT_MODULE_TYPE_ADMU			 15 //ADMU

#define STT_MODULE_TYPE_VOLT_ID             "VOLTAGE"   //ģ������ѹ���������"ͨ����" id="ChannelNum"���ԡ�
#define STT_MODULE_TYPE_CURRENT_ID          "CURRENT"   //ģ�����������
#define STT_MODULE_TYPE_DIGITAL_0G8M_ID		"DIGITAL_0G8M"   //������ 8���׹�ڲ��
#define STT_MODULE_TYPE_DIGITAL_2G6M_ID     "DIGITAL_2G6M"   //������ 6���׹��2ǧ�ײ��
#define STT_MODULE_TYPE_DIGITAL_4G4M_ID     "DIGITAL_4G4M"    //������ 4���׹��4ǧ�ײ��
#define STT_MODULE_TYPE_DCCURRENT_ID        "DCCURRENT"       //ģ����ֱ���������
#define STT_MODULE_TYPE_DCVOLT_ID           "DCVOLTAGE"       //ģ����ֱ����ѹ���
#define STT_MODULE_TYPE_SWITCH_ID           "BINARY"          //���������
#define STT_MODULE_TYPE_WEEK_EX_ID          "WEEK"           //���źŲ��
//#define STT_MODULE_TYPE_WEEK_MAIN_ID		"WEEK_MAIN"      //�������źŲ��   20231025 �Ժϲ���"WEEK"����
#define STT_MODULE_TYPE_FT3_ID				"FT3"            //������ FT3�źŲ��
#define STT_MODULE_TYPE_VOLT_CURRENT_ID		"VOLTAGE_CURRENT"  //ģ������ѹ������ϲ��
#define STT_MODULE_TYPE_MEAS_VOLT_ID		"MEAS_VOLTAGE"      //ģ����������ѹ���
#define STT_MODULE_TYPE_MEAS_CURRENT_ID		"MEAS_CURRENT"      //ģ���������������
//#define STT_MODULE_TYPE_WEEK_EX48_ID        "WEEK_48"          //48ͨ�����źŲ��
#define STT_MODULE_TYPE_Stable2M_ID         "Stable2M" //�ȿ�2M
#define STT_MODULE_TYPE_ADMU_ID				"ADMU" //ADMU

//ModuleTypeID   2021-4-29  LIJUNQING  ���������˸���ModuleType���ModuleTypeID�ĺ���
//ModuleType�ı䣬���޸Ĵ˺�������������stt_get_module_id_by_type
#define STT_MODULETYPE_ID_ERROR    "err"
#define STT_MODULETYPE_ID_ANALOG   "analog"
#define STT_MODULETYPE_ID_DIGITAL   "digital"
#define STT_MODULETYPE_ID_WEEK      "week"
#define STT_MODULETYPE_ID_BINARY   "binary"

//ģ�������
#define STT_MODULETYPE_ID_ANALOG_CHAR   'A'
//���������
#define STT_MODULETYPE_ID_DIGITAL_CHAR   'D'
//С�źŲ��
#define STT_MODULETYPE_ID_WEEK_CHAR      'W'
//���������
#define STT_MODULETYPE_ID_BINARY_CHAR   'B'

//2021-4-30  lijunqing
//���۽����Ϊ���㽫���İ汾���䣬Ϊÿ��ͨ�������Ӷ�������������
//           �ɼ��������WorkMode��
//           ��ѹ����������EeType
//           ���ֵ��ChACMaxValue
//           ���ֵ��ChDCMaxValue
//Ϊ�˼������ϰ汾��Ϊģ�����Ӱ汾�ţ���ʾУ׼ϵ��ģʽ�İ汾
#define  STT_CH_WORK_MODE_OUTPUT   0
#define  STT_CH_WORK_MODE_INPUT      1

//ͨ���ĵ������ԣ��������ͣ�����ѹ��������������
#define  STT_CH_EETYPE_VOLTAGE          'U'
#define  STT_CH_EETYPE_CURRENT          'I'
#define  STT_CH_EETYPE_BINARY            'B'

//�����ڵײ��һ�����ɳ�ʼϵ������
//�������� "VOLTAGE" "CURRENT" ���
//PN PI ϵ��Ĭ��Ӳ������λ�ö�Ӧ��ϵ
const long VoltDrvPosComm[6]={4,5,2,3,0,1};
const long CurrentDrvPosComm[6]={3,5,1,4,0,2};
//PI V300
const long VoltDrvPos_PI_300V[6]={4,5,0,1,2,3};
//PTU200L
const long VoltDrvPos_PTU200L[6]={1,0,5,4,3,2};
const long CurrentDrvPos_PTU200L[6]={5,4,1,0,3,2};


//����ModuleType���ModuleTypeID�ĺ���
inline char* stt_get_module_id_by_type(unsigned int nModuleType)
{
	//ModuleType
	switch (nModuleType)
	{
	case STT_MODULE_TYPE_VOLT://             0//������ѹ���
		return STT_MODULETYPE_ID_ANALOG;

	case STT_MODULE_TYPE_CURRENT://          1//�����������
		return STT_MODULETYPE_ID_ANALOG;

	case STT_MODULE_TYPE_DIGITAL_0G8M://     2//8�����׿����ְ�FPGA,9-2+ft3
		return STT_MODULETYPE_ID_DIGITAL;

	case STT_MODULE_TYPE_DIGITAL_2G6M://     3//6�����׿�,2��ǧ�׿����ְ�FPGA,9-2+ft3
		return STT_MODULETYPE_ID_DIGITAL;

	case STT_MODULE_TYPE_DIGITAL_4G4M://     4//4�����׿�,4��ǧ�׿����ְ�FPGA,9-2+ft3
		return STT_MODULETYPE_ID_DIGITAL;

	case STT_MODULE_TYPE_DCCURRENT://        5//ֱ���������
		return STT_MODULETYPE_ID_ANALOG;

	case STT_MODULE_TYPE_DCVOLT://           6//ֱ����ѹ���
		return STT_MODULETYPE_ID_ANALOG;

	case STT_MODULE_TYPE_SWITCH://           7//��������չ��
		return STT_MODULETYPE_ID_BINARY;

	case STT_MODULE_TYPE_WEEK_EX://          8//С�ź�ģ����
		return STT_MODULETYPE_ID_WEEK;

//20231023 ͳһ��STT_MODULE_TYPE_WEEK_EX
//	case STT_MODULE_TYPE_WEEK_MAIN://        9//����С�ź�
//		return STT_MODULETYPE_ID_WEEK;

	case STT_MODULE_TYPE_FT3://				 10//��ֱFT3��,��ft3
		return STT_MODULETYPE_ID_DIGITAL;

	case STT_MODULE_TYPE_VOLT_CURRENT:  //U��I��ϲ��
		return STT_MODULETYPE_ID_ANALOG;

//	case STT_MODULE_TYPE_WEEK_EX_48://          14//С�ź�ģ����
//		return STT_MODULETYPE_ID_WEEK;

	case STT_MODULE_TYPE_ADMU://				 15//ADMU
		return STT_MODULETYPE_ID_WEEK;
	}

	return STT_MODULETYPE_ID_ERROR;
}

#define STT_ADJ_DATA_TYPE_Device				_T("Device")
#define STT_ADJ_DATA_TYPE_DeviceAttrs		_T("DeviceAttrs")

//��������ֵͨ����   lijunqing  2020-10-17
#define STT_ADJ_DATA_TYPE_BoutTrunOnValueDef		_T("BoutTrunOnValueDef")
#define STT_ADJ_DATA_TYPE_Module			_T("Module")
#define STT_ADJ_DATA_TYPE_ModuleAttrs		_T("ModuleAttrs")
#define STT_ADJ_DATA_TYPE_ChMapDef		_T("ChMapDef")
//2021-5-3  lijunqing  ChMaps,ChMapȥ��������Ӳ��ͨ������ChDefine��Ӳ��ͨ��HdCh
#define STT_ADJ_DATA_TYPE_ChDefine			_T("ChDefine")
#define STT_ADJ_DATA_TYPE_HdCh				_T("HdCh")
#define STT_ADJ_DATA_TYPE_ChGroups			_T("ChGroups")
#define STT_ADJ_DATA_TYPE_ChGroup			_T("ChGroup")
#define STT_ADJ_DATA_TYPE_HdGears			_T("HdGears")
#define STT_ADJ_DATA_TYPE_HdGear			_T("HdGear")
#define STT_ADJ_DATA_TYPE_AdjustParas		_T("AdjustParas")
#define STT_ADJ_DATA_TYPE_TRange			_T("T_Range")
#define STT_ADJ_DATA_TYPE_ChannelAdj		_T("ChannelAdj")
#define STT_ADJ_DATA_TYPE_ChWaveAdj		_T("ChWaveAdj")
#define STT_ADJ_DATA_TYPE_GearAdjust		_T("GearAdjust")
#define STT_ADJ_DATA_TYPE_AdjustItem		_T("AdjustItem")
#define STT_ADJ_DATA_TYPE_Channel		_T("Channel")
#define STT_ADJ_DATA_TYPE_Vector		_T("Vector")
#define STT_ADJ_DATA_TYPE_ChDrvPos		_T("ChDrvPos")
#define STT_ADJ_DATA_TYPE_SttModel		_T("SttModel")                           //2020-10-11 mym 
#define STT_ADJ_DATA_TYPE_SttModuleType		_T("SttModuleType")			//2020-10-11 mym 
#define STT_ADJ_DATA_TYPE_SttModuleClass		_T("SttModuleClass")	//2020-10-11 mym 

#define STT_ADJ_HD_GEAR_ID_IDC		_T("HdIdcGears")
#define STT_ADJ_HD_GEAR_ID_UDC		_T("HdUdcGears")
#define STT_ADJ_HD_GEAR_ID_MODULE		_T("HdGears")
#define STT_ADJ_HD_GEAR_DATA_TYPE		_T("GearAdjust")

#define STT_ADJ_ID_ChMapDef		_T("ChMapDef")
// #define STT_ADJ_ID_ChMaps		_T("ChMaps")
// #define STT_ADJ_ID_ChGroups		_T("ChGroups")
#define STT_ADJ_ID_ChDefine		_T("ChDefine")
#define STT_ADJ_ID_ChDrvPos		_T("ChDrvPos")										  //2020-10-10 mym 


#define STT_ADJ_ID_Ch_Idc			_T("Idc")
#define STT_ADJ_ID_Ch_Udc			_T("Udc")
#define STT_ADJ_ID_Ch_1_3			_T("Ch1_3")
#define STT_ADJ_ID_Ch_4_6			_T("Ch4_6")
#define STT_ADJ_ID_Ch0_Module	_T("Ch0")
#define STT_ADJ_ID_Ch_Module		_T("Ch")

#define STT_ADJ_ID_Ch_Wave_DC			_T("DC")
#define STT_ADJ_ID_Ch_Wave_Base		_T("Base")
#define STT_ADJ_ID_Ch_Wave_Harm			_T("H")

#define STT_ADJ_ID_ModuleCount		_T("ModuleCount")
#define STT_ADJ_ID_ChMapsCount		_T("ChMapsCount")
#define STT_ADJ_ID_ChGroupCount	_T("ChGroupCount")
#define STT_ADJ_ID_HdGearCount		_T("HdGearCount")
#define STT_ADJ_ID_HarmCount		_T("HarmCount")
#define STT_ADJ_ID_TRangeCount		_T("TRangeCount")
#define STT_ADJ_ID_GearCount			_T("GearCount")



#define STT_ADJ_ID_ModuleType			_T("ModuleType")
#define STT_ADJ_ID_ModulePos			    _T("ModulePos")
#define STT_ADJ_ID_ModuleIndex			_T("ModuleIndex")
#define STT_ADJ_ID_ChannelNum			_T("ChannelNum")
#define STT_ADJ_ID_FreqIndex			_T("FreqIndex")
#define STT_ADJ_ID_FreqSel			_T("FreqSel")
#define STT_ADJ_ID_SwitchMode			_T("SwitchMode")

#define STT_ADJ_ID_Model         		_T("Model")
#define STT_ADJ_ID_SN         		_T("SN")
#define STT_ADJ_ID_FACTORY         		_T("Factory")
#define STT_ADJ_ID_DATEFAC         		_T("DateFac")
#define STT_ADJ_ID_StateCount         		_T("StateCount")//zhouhj 20220401 ���豸Ӳ����Ϣ�ļ��л�ȡ״̬�������忪��\��������
#define STT_ADJ_ID_BinCount         		_T("BinCount")
#define STT_ADJ_ID_BoutCount         		_T("BoutCount")
#define STT_ADJ_ID_STModeSet         		_T("STModeSet")//2023-11-28 suyang ��Ӳ����Ϣ�ļ��л�ȡST��ģʽʹ��
#define STT_ADJ_ID_UartCount       _T("UartCount") //chenling 2024.5.8

#define STT_ADJ_ID_ADJ_MODEL         		_T("Adj_Model")
#define STT_ADJ_ID_ADJ_DEVICE         		_T("Adj_Device")

//2021-5-4  lijunqing
#define STT_ADJ_ID_WorkMode			_T("WorkMode")
#define STT_ADJ_ID_WorkMode_Output		_T("Output")
#define STT_ADJ_ID_WorkMode_MEAS		_T("MEAS")

#define STT_ADJ_ID_EeType			_T("EeType")
#define STT_ADJ_ID_EeType_Voltage			_T("Voltage")
#define STT_ADJ_ID_EeType_Current			_T("Current")
#define STT_ADJ_ID_EeType_Binary			_T("Binary")

//2021-5-5  lijunqing   ���豸����û��У׼ϵ���ļ����豸
#define  STT_ADJ_ID_EmptyDevice  _T("EmptyDevice")
#define STT_ADJ_SYS_FILE_NAME  _T("DeviceSystemParas.xml")

//20210717 shaolei  ����ģ������ģ�����Բ���ʾ
#define STT_ADJ_ID_UdcMax         		_T("UdcMax")
#define STT_ADJ_ID_IdcMax         		_T("IdcMax")
#define STT_ADJ_ID_ChMax         		_T("ChMax")
#define STT_ADJ_ID_ChDcMax         		_T("ChDcMax")
#define STT_ADJ_ID_FreCoef         		_T("FreCoef")
#define STT_ADJ_ID_ModulePower          _T("ModulePower")
#define STT_ADJ_ID_ChMergeMode        	_T("ChMergeMode")
#define STT_ADJ_ID_fDigitalDelay       	_T("fDigitalDelay")

//zhouhj 2023.11.13 ���º�ʵ��δ�õ�,ȥ��
// //zhouhj 20220424 ��ѹ������ϲ�� ���ӵ������Ա�ʶ��ѹͨ�����ֵ������ͨ�����ֵ
// #define STT_ADJ_ID_VolChMaxValueAC         		_T("VolChMaxValueAC")
// #define STT_ADJ_ID_VolChMaxValueDC         		_T("VolChMaxValueDC")
// #define STT_ADJ_ID_CurChMaxValueAC         		_T("CurChMaxValueAC")
// #define STT_ADJ_ID_CurChMaxValueDC         		_T("CurChMaxValueDC")

//20231025  ��������Ͷ���
#define  STT_MODULE_POWER_UNKNOWN   0//"δ����"
#define  STT_MODULE_VOLT_V130_130	1//"130����ѹģ��"
#define  STT_MODULE_VOLT_V248_248	2//"248����ѹģ��"
#define  STT_MODULE_VOLT_V270_270	3//"270����ѹģ��,����ѹ��"
#define  STT_MODULE_VOLT_V270_380	4//"270����ѹģ��,����ѹ��"
#define  STT_MODULE_VOLT_V300_300	5//"300����ѹģ��,����ѹ��"
#define  STT_MODULE_VOLT_V300_440	6//"300����ѹģ��,����ѹ��"

#define  STT_MODULE_CURRENT_C12_5		1000//"12.5������ģ��"
#define  STT_MODULE_CURRENT_C20			1001//"20������ģ��"
#define  STT_MODULE_CURRENT_C32			1002//"32������ģ��"

#define  STT_MODULE_UI_PFC6A		2000//"PFC-6Aģ��"
#define  STT_MODULE_UI_V130_C20		2001//"130��20�����ģ��"
#define  STT_MODULE_WEEK_PIA12DS	2002//"12·ֱ�����ģ��"
#define  STT_MODULE_WEEK_PIA48S	    2003//"48·С�ź�ģ��"
#define  STT_MODULE_UI_PNS330		2004//"PNS330��ѹ����ģ��"
#define  STT_MODULE_WEEK_EVTECT	    2005//"EVTECTС�ź�ģ��"
#define  STT_MODULE_WEEK_EVTECT_Ex1	2006//"EVTECTС�ź�ģ�����1"
#define  STT_MODULE_WEEK_DC6U10V	2007//"6·10��ֱ��С�ź�ģ��"
#define  STT_MODULE_WEEK_DC6I20mA	2008//"6·20����ֱ��С�ź�ģ��"
#define  STT_MODULE_UI_PNS331		2009//"PNS331��ѹ����ģ��"
#define  STT_MODULE_WEEK_PNS331     2010//"PNS331С�ź�ģ��"
#define  STT_MODULE_WEEK_PN_DC6U6I  2011//"PN6U6Iֱ��С�ź�ģ��"
#define  STT_MODULE_UI_V310_C60		2012//"310��60�����ģ��"
#define  STT_MODULE_WEEK_PN_MAIN	2013//"PN����С�ź�ģ��"
#define  STT_MODULE_WEEK_L336D		2014//"L336DС�ź�ģ��"
#define  STT_MODULE_UI_PIA0103		2015//"30��0.1�����ģ��"
#define  STT_MODULE_UI_PNS330_H		2016//"PNS330_H��ѹ����ģ��"
#define  STT_MODULE_UI_PNS330_ABC_20	2017//"PNS330ģ�����ͬ��20A"
#define  STT_MODULE_UI_PNS330_6		2018//"PNS330_6ģ��"

#define STT_MODULE_POWER_UNKNOWN_ID		   "unKnown"
#define STT_MODULE_VOLT_V130_130_ID        "V130"
#define STT_MODULE_VOLT_V248_248_ID        "V248"
#define STT_MODULE_VOLT_V270_270_ID        "V270"
#define STT_MODULE_VOLT_V270_380_ID        "V270_380"
#define STT_MODULE_VOLT_V300_300_ID        "V300"
#define STT_MODULE_VOLT_V300_440_ID        "V300_440"

#define STT_MODULE_CURRENT_C12_5_ID        "C12_5"
#define STT_MODULE_CURRENT_C20_ID		   "C20"
#define STT_MODULE_CURRENT_C32_ID          "C32"

#define  STT_MODULE_UI_V130_C20_ID         "V130C20"
#define  STT_MODULE_UI_PFC6A_ID			   "PFC_6A"
#define  STT_MODULE_UI_PNS330_ID		   "PNS330"
#define  STT_MODULE_UI_PNS331_ID		   "PNS331"
#define  STT_MODULE_WEEK_PIA12DS_ID        "PIA12DS"
#define  STT_MODULE_WEEK_PIA48S_ID         "PIA48S"
#define  STT_MODULE_WEEK_EVTECT_ID         "EVTECT"
#define  STT_MODULE_WEEK_EVTECT_Ex1_ID     "EVTECT_Ex1"
#define  STT_MODULE_WEEK_DC6U10V_ID        "DC6U_10V"
#define  STT_MODULE_WEEK_DC6I20mA_ID       "DC6I_20mA"
#define  STT_MODULE_WEEK_PN_DC6U6I_ID      "PN_DC6U6I"
#define  STT_MODULE_UI_V310_C60_ID         "V310C60"
#define  STT_MODULE_WEEK_PN_MAIN_ID		   "PN_Main"
#define  STT_MODULE_WEEK_L336D_ID          "L336D"
#define  STT_MODULE_UI_PIA0103_ID          "PIA0103"
#define  STT_MODULE_UI_PNS330_H_ID         "PNS330_H"
#define  STT_MODULE_UI_PNS330_ABC_20_ID	   "PNS330_Iabc_20"
#define  STT_MODULE_UI_PNS330_6_ID		   "PNS330_6"

#define STT_CURRENT_ChMergeMode_No         0
#define STT_CURRENT_ChMergeMode_1Ch        1
#define STT_CURRENT_ChMergeMode_3Ch        2
#define STT_CURRENT_ChMergeMode_3Ch_Fixed  3
#define STT_CURRENT_ChMergeMode_1Ch_Fixed  4

#endif // TMT_ADJUST_SYS_PARA_MODULE_DEF_H

