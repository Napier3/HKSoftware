#pragma once

#include "SttGlobalDef_File.h"

//////////////////////////////////////////////
#define STT_PKG_INDEX_DATA		STT_PKG_HEAD_LEN

// #define STT_FILECMD_MAX_LEN	(STT_PKG_SEND_FILEDATA_MAXLEN+STT_PKG_HEAD_LEN)
#define STT_SOCKET_RECV_SIZE		STT_FILECMD_MAX_LEN

/////////////////////////////////////
//��������
#define STT_CMD_TYPE_SYSTEM		0x1
#define STT_CMD_TYPE_TEST		0x2
#define STT_CMD_TYPE_DEBUG		0x3
#define STT_CMD_TYPE_REMOTE		0x4
#define STT_CMD_TYPE_ATS		0x5
#define STT_CMD_TYPE_ASSIST		0x6
#define STT_CMD_TYPE_ADJUST		0x7
#define STT_CMD_TYPE_IOT		0x8
#define STT_CMD_TYPE_SYSSTATE	0x20
#define STT_CMD_TYPE_HEARTBEAT	0x80
#define STT_CMD_TYPE_TRIGGER    0x81

//���ϻط�����
#define STT_CMD_TYPE_COMTRADE		0xE1

#define STT_CMD_TYPE_COMTRADE_REQUESTDATA			0x00
#define STT_CMD_TYPE_COMTRADE_SENDDATAFINISH		0x01
#define STT_CMD_TYPE_COMTRADE_SENDDATASTART			0x02
#define STT_CMD_TYPE_COMTRADE_SENDDATASTART_ACK		0x03

#define STT_CMD_SYSSTATE_SYSTEM		_T("sys-cmd")
#define STT_CMD_SYSSTATE_TEST		_T("test-cmd")
#define STT_CMD_SYSSTATE_DEBUG		_T("dbg-cmd")
#define STT_CMD_SYSSTATE_REMOTE		_T("remote-cmd")
#define STT_CMD_SYSSTATE_ATS		_T("ats-cmd")
#define STT_CMD_SYSSTATE_ASSIST		_T("assist-cmd")
#define STT_CMD_SYSSTATE_ADJUST		_T("adj-cmd")
#define STT_CMD_SYSSTATE_IOT		_T("iot-cmd")

#define MQTT_CMD_ID_TestCmd   _T("TestCmd")
#define MQTT_CMD_ID_TestState  _T("TestState")
#define MQTT_CMD_ID_AtsCmd    _T("AtsCmd")
#define MQTT_CMD_ID_AtsState   _T("AtsState")
#define MQTT_CMD_ID_IotCmd    _T("IotCmd")
#define MQTT_CMD_ID_IotState   _T("IotState")

#define STT_CMD_TYPE_BINARY		0xFE

/***********Socket����**************/
#define STT_SOCKET_TYPE_OWN				1
#define STT_SOCKET_TYPE_LOCAL			2
#define STT_SOCKET_TYPE_REMOTE			3

//////////////////////////////////////////////
//Ȩ�޶���
//�����ǿ���
#define KEY_AUTHORITY_MODULE_Test  _T("test")
//������Զ�̿���
#define KEY_AUTHORITY_MODULE_ClientEngine  _T("clientEngine")
//�Զ����Կ���   �������ѻ��Զ����Գ���
#define KEY_AUTHORITY_MODULE_Ats  _T("ats")

//ͨѶ�������   Զ��Э��
#define KEY_AUTHORITY_MODULE_PpMmsEngine  _T("ppmmsengine")
//ͨѶ�������   Զ��Э��
#define KEY_AUTHORITY_MODULE_PpEngine  _T("ppengine")
//���Զ���������� Զ��Э��
#define KEY_AUTHORITY_MODULE_SttTestStudio  _T("sttteststudio")
//�����������   Զ��Э��
#define KEY_AUTHORITY_MODULE_SttTestCntr  _T("stttestcntr")
//���������ÿ���    Զ��Э��
#define KEY_AUTHORITY_MODULE_Iec61850Config  _T("iec61850config")
//ģ�ͱȽϳ������ Զ��Э��
#define KEY_AUTHORITY_MODULE_DvmTest  _T("dvmtest")   
//�Զ����Գ���   Զ��Э��
#define KEY_AUTHORITY_MODULE_SmartTest	_T("smarttest")

#define ID_AUTHORITY_MODULE_Test				0x1
#define ID_AUTHORITY_MODULE_ClientEngine		0x2
#define ID_AUTHORITY_MODULE_Ats					0x4

#define ID_AUTHORITY_MODULE_PpMmsEngine			0x8
#define ID_AUTHORITY_MODULE_PpEngine			0x10
#define ID_AUTHORITY_MODULE_SttTestStudio		0x20
#define ID_AUTHORITY_MODULE_SttTestCntr			0x40
#define ID_AUTHORITY_MODULE_Iec61850Config		0x80
#define ID_AUTHORITY_MODULE_DvmTest				0x100  
#define ID_AUTHORITY_MODULE_SmartTest			0x200

#define ID_AUTHORITY_MASK_TESTAPP	(ID_AUTHORITY_MODULE_Test | ID_AUTHORITY_MODULE_ClientEngine | ID_AUTHORITY_MODULE_Ats)
#define ID_AUTHORITY_MASK_ASSIST	(ID_AUTHORITY_MODULE_PpMmsEngine \
										| ID_AUTHORITY_MODULE_PpEngine \
										| ID_AUTHORITY_MODULE_SttTestStudio \
										| ID_AUTHORITY_MODULE_SttTestCntr \
										| ID_AUTHORITY_MODULE_Iec61850Config \
										| ID_AUTHORITY_MODULE_DvmTest \
										| ID_AUTHORITY_MODULE_SmartTest )

//////////////////////////////////////////////
//STT��¼�û�����:���������ء�Զ��
#define STT_TERMINAL_TYPE_NATIVE				_T("NATIVE")
#define STT_TERMINAL_TYPE_LOCAL					_T("LOCAL")
#define STT_TERMINAL_TYPE_REMOTE				_T("REMOTE")
#define STT_TERMINAL_TYPE_NATIVE_ATS			_T("NATIVE_ATS")
#define STT_TERMINAL_TYPE_NATIVE_TEST			_T("NATIVE_TEST")
#define STT_TERMINAL_TYPE_NATIVE_TESTCONTROL	_T("NATIVE_TESTCONTROL")

#define STT_SOFT_ID_ATS			        _T("ATS")
#define STT_SOFT_ID_TEST		        _T("TEST")
#define STT_SOFT_ID_IOT		          	_T("IOT")
#define STT_SOFT_ID_DEBUG	        	_T("DEBUG")
#define STT_SOFT_ID_RECORD		        _T("RECORD")
#define STT_SOFT_ID_COMTRADE	        _T("COMTRADE")
#define STT_SOFT_ID_COMTRADECONTRL  	_T("COMTRADECONTRL")//¼������

//STTע��ģʽ
#define STT_REGISTER_MODE_OWN		_T("OWN")
#define STT_REGISTER_MODE_TEST		_T("TEST")

//////////////////////////////////////////////
//STT�û����Զ���
#define ID_STT_USER_ATTR_os                _T("os")
#define ID_STT_USER_ATTR_id_soft           _T("id_soft")
#define ID_STT_USER_ATTR_ver_soft          _T("ver_soft")
#define ID_STT_USER_ATTR_ID_Terminal       _T("ID_Terminal")
#define ID_STT_USER_ATTR_SN_TestApp        _T("SN_TestApp")
#define ID_STT_USER_ATTR_Code_Register     _T("Code_Register")
#define ID_STT_USER_ATTR_Name_Cop          _T("Name_Cop")
#define ID_STT_USER_ATTR_Index_User        _T("Index_User")
#define ID_STT_USER_ATTR_Name_User         _T("Name_User")
#define ID_STT_USER_ATTR_IP_User           _T("IP_User")
// #define ID_STT_USER_ATTR_ID_Remote         _T("ID_Remote")
// #define ID_STT_USER_ATTR_ID_Local		   _T("ID_Local")

//STT�û�ע�����Զ���
#define ID_STT_REGISTER_ATTR_Model_TestApp		_T("Model_TestApp")
#define ID_STT_REGISTER_ATTR_Model_Dv			_T("Model_Dv")
#define ID_STT_REGISTER_ATTR_Description		_T("Description")
#define ID_STT_REGISTER_ATTR_Ver_PpMmsEngine	_T("Ver_PpMmsEngine")
#define ID_STT_REGISTER_ATTR_Ver_PpEngine		_T("Ver_PpEngine")
#define ID_STT_REGISTER_ATTR_Ver_SttTestStudio	_T("Ver_SttTestStudio")
#define ID_STT_REGISTER_ATTR_Ver_SttTestCntr	_T("Ver_SttTestCntr")
#define ID_STT_REGISTER_ATTR_Ver_Iec61850Config	_T("Ver_Iec61850Config")
#define ID_STT_REGISTER_ATTR_Ver_DvmTest		_T("Ver_DvmTest")
#define ID_STT_REGISTER_ATTR_Ver_SmartTest		_T("Ver_SmartTest")
#define ID_STT_REGISTER_ATTR_Ver_TestServer		_T("Ver_TestServer")

//����Ӧ��testor
#define STT_CMD_TESTOR			_T("testor")
#define STT_SYSSTATE_TESTOR		_T("mater-host")
#define STT_SYSSTATE_RET_CMDTYPE		_T("id-cmd")
#define STT_SYSSTATE_RET_TYPE		_T("ret-type")

//ϵͳ����
#define STT_CMD_TYPE_SYSTEM_SetSysConfig	_T("SetSysConfig")
#define STT_CMD_TYPE_SYSTEM_GetSysConfig	_T("GetSysConfig")
#define STT_CMD_TYPE_SYSTEM_Login			_T("Login")
#define STT_CMD_TYPE_SYSTEM_Logout			_T("Logout")
#define STT_CMD_TYPE_SYSTEM_Request			_T("Request")
#define STT_CMD_TYPE_SYSTEM_GetDirs			_T("GetDirs")
#define STT_CMD_TYPE_SYSTEM_DownFile		_T("DownFile")
#define STT_CMD_TYPE_SYSTEM_DeleteFile		_T("DeleteFile")
#define STT_CMD_TYPE_SYSTEM_DownFolder		_T("DownFolder")
#define STT_CMD_TYPE_SYSTEM_DeleteFolder	_T("DeleteFolder")
#define STT_CMD_TYPE_SYSTEM_CreateFolder	_T("CreateFolder")
#define STT_CMD_TYPE_SYSTEM_LiveUpdate		_T("LiveUpdate")
#define STT_CMD_TYPE_SYSTEM_Authority		_T("Authority")
#define STT_CMD_TYPE_SYSTEM_NativeAuthority	_T("NativeAuthority")
#define STT_CMD_TYPE_SYSTEM_CloudTest _T("CloudTest")
#define STT_CMD_TYPE_SYSTEM_ReadMeas		_T("ReadMeas")
#define STT_CMD_TYPE_SYSTEM_GetSystemState	_T("GetSystemState")

//���Կ�������
#define STT_CMD_TYPE_TEST_SetParameter		_T("SetParameter")
#define STT_CMD_TYPE_TEST_UpdateParameter	_T("UpdateParameter")
#define STT_CMD_TYPE_TEST_StartTest			_T("StartTest")
#define STT_CMD_TYPE_TEST_StopTest			_T("StopTest")
#define STT_CMD_TYPE_TEST_GetReport			_T("GetReport")
#define STT_CMD_TYPE_TEST_CloseDevice		_T("CloseDevice")
#define STT_CMD_TYPE_TEST_SysDefaultOutput	_T("SystemDefaultOutput")
#define STT_CMD_TYPE_TEST_TriggerTest	_T("TriggerTest")

//2021-9-4  lijunqing
#define STT_CMD_TYPE_TEST_CreateDevice	_T("CreateDevice")
#define STT_CMD_TYPE_TEST_ConfigDevice	_T("ConfigDevice")
#define STT_CMD_TYPE_TEST_ConnectDevice	_T("ConnectDevice")
#define STT_CMD_TYPE_TEST_GetDataset	_T("GetDataset")
#define STT_CMD_TYPE_TEST_SetDataset	_T("SetDataset")

//2022-8-1  lijunqing  for Record
#define STT_CMD_TYPE_TEST_Record	_T("Record")
#define STT_CMD_TYPE_TEST_RecordBegin	_T("Begin")
#define STT_CMD_TYPE_TEST_RecordFinish	_T("Finish")
#define STT_CMD_TYPE_TEST_RecordCancel	_T("Cancel")
#define STT_CMD_TYPE_TEST_RecordData	_T("Data")
#define STT_CMD_TYPE_TEST_RecordCall	_T("Call")
//2022-8-1  lijunqing
#define STT_CMD_TYPE_TEST_HeartBeat	_T("HeartBeat")
#define STT_CMD_TYPE_TEST_QueryFile	_T("QueryFile")
#define STT_CMD_TYPE_TEST_QueryDevice	_T("QueryDevice")
//2022-8-5 lijunqing
#define STT_CMD_TYPE_TEST_Record_Send	_T("Send")
#define STT_CMD_TYPE_TEST_Record_StopSend	_T("StopSend")

//xxy ���������ǽӿ�
#define STT_CMD_TYPE_TEST_QueryDeviceState	_T("QueryDeviceState")
#define STT_CMD_TYPE_TEST_SendSensorModel	_T("SendSensorModel")
#define STT_CMD_TYPE_TEST_GetTestMacros		_T("GetTestMacros")
#define STT_CMD_TYPE_TEST_GetTopo			_T("GetTopo")

//У׼����
#define STT_CMD_TYPE_ADJUST_Adjust				_T("Adjust")
#define STT_CMD_TYPE_ADJUST_ReadDeviceParameter	_T("ReadDeviceParameter")
#define STT_CMD_TYPE_ADJUST_WriteFile		_T("WriteFile")

//ϵͳ����  shaolei 20211028
#define STT_CMD_TYPE_ADJUST_ChMapsConfig		_T("ChMapsConfig")

//shaolei  2022-01-08
#define STT_CMD_TYPE_SYSTEM_IECConfig		_T("Iec61850Config")
#define STT_CMD_TYPE_SYSTEM_SystemConfig		_T("SystemConfig")

#define STT_CMD_ATS_MACRO_ID_GradientTest           _T("GradientTest")   //�ݱ����
#define STT_CMD_ATS_MACRO_ID_GradientMaxAngleTest   _T("GradientMaxAngleTest") //�ݱ���ԣ����������
#define STT_CMD_ATS_MACRO_ID_StateTest           _T("StateTest")   //״̬����
#define STT_CMD_ATS_MACRO_ID_ReplayTest             _T("ReplayTest")   //���ϻط�
#define STT_CMD_ATS_MACRO_ID_ManualTest           _T("ManualTest")   //�ֶ����飨ͨ�����飩
#define STT_CMD_ATS_MACRO_ID_SequenceManuTest           _T("SequenceManuTest")   //ͨ������(�����)
#define STT_CMD_ATS_MACRO_ID_HarmTest          _T("HarmTest")   //г������
#define STT_CMD_ATS_MACRO_ID_SequenceGradientTest          _T("SequenceGradientTest")   //�ݱ�-�����
#define STT_CMD_ATS_MACRO_ID_LineVolGradientTest         _T("LineVolGradientTest")   //�ݱ�-�ߵ�ѹ
#define STT_CMD_ATS_MACRO_ID_LineVolManuTest         _T("LineVolManuTest")   //ͨ��ʵ��-�ߵ�ѹ
#define STT_CMD_ATS_MACRO_ID_LowVolTest          _T("LowVolTest")   //��ѹ����
#define STT_CMD_ATS_MACRO_ID_LowFreqTest          _T("LowFreqTest")   //���ܼ���

//�ڲ���������
#define STT_CMD_TYPE_DEBUG_GetProcessState	_T("GetProcessState")
#define STT_CMD_TYPE_DEBUG_GetMemState		_T("GetMemState")
#define STT_CMD_TYPE_DEBUG_GetTestParas		_T("GetTestParas")
#define STT_CMD_TYPE_DEBUG_GetTestReports		_T("GetTestReports")
#define STT_CMD_TYPE_DEBUG_GetBasicTestParas	_T("GetBasicTestParas")
#define STT_CMD_TYPE_DEBUG_GetBasicReportData	_T("GetBasicReportData")
#define STT_CMD_TYPE_DEBUG_GetDrvTestData	_T("GetDrvTestData")
#define STT_CMD_TYPE_DEBUG_GetDrvReportData	_T("GetDrvReportData")
#define STT_CMD_TYPE_DEBUG_GetFpgaData		_T("GetFpgaData")
#define STT_CMD_TYPE_DEBUG_GetSocketConnect	_T("GetSocketConnect")
#define STT_CMD_TYPE_DEBUG_ConfigDebug		_T("ConfigDebug")

//Զ�̿�������
#define STT_CMD_TYPE_REMOTE_Register		_T("Register")
#define STT_CMD_TYPE_REMOTE_UnRegister		_T("UnRegister")
#define STT_CMD_TYPE_REMOTE_Query			_T("Query")
#define STT_CMD_TYPE_REMOTE_Bind			_T("Bind")

//�Զ���������
#define STT_CMD_TYPE_ATS_CreateTest			_T("CreateTest")
#define STT_CMD_TYPE_ATS_StartTest			_T("StartTest")
#define STT_CMD_TYPE_ATS_StopTest			_T("StopTest")
#define STT_CMD_TYPE_ATS_CloseTest			_T("CloseTest")
#define STT_CMD_TYPE_ATS_SetItemState		_T("SetItemState")
#define STT_CMD_TYPE_ATS_TestItem			_T("TestItem")
#define STT_CMD_TYPE_ATS_TestFrom			_T("TestFrom")
#define STT_CMD_TYPE_ATS_TestAllFailedItems	_T("TestAllFailedItems")
#define STT_CMD_TYPE_ATS_GetItemReport		_T("GetItemReport")
#define STT_CMD_TYPE_ATS_GetReportFile		_T("GetReportFile")
#define STT_CMD_TYPE_ATS_GetSystemState		_T("GetSystemState")
#define STT_CMD_TYPE_ATS_CreateDevice		_T("CreateDevice")
#define STT_CMD_TYPE_ATS_ConnectDevice		_T("ConnectDevice")
#define STT_CMD_TYPE_ATS_ConfigDevice		_T("ConfigDevice")
#define STT_CMD_TYPE_ATS_GetDataset			_T("GetDataset")
#define STT_CMD_TYPE_ATS_SetDataset			_T("SetDataset")
#define STT_CMD_TYPE_ATS_RunProcedure		_T("RunProcedure")
#define STT_CMD_TYPE_ATS_CloseDevice		_T("CloseDevice")
#define STT_CMD_TYPE_ATS_ConfigEngine		_T("ConfigEngine")
#define STT_CMD_TYPE_ATS_InputData			_T("InputData")
#define STT_CMD_TYPE_ATS_FinishInputData	_T("FinishInputData")
#define STT_CMD_TYPE_ATS_ManuTriger			_T("ManuTriger")	//yyj �ֶ������ź� 20220224
#define STT_CMD_TYPE_ATS_OpenGbrptFile		_T("OpenGbrptFile") //shaolei �򿪲��Լ�¼  20220716
#define STT_CMD_TYPE_ATS_AdjustMainWnd		_T("AdjustMainWnd") //shaolei ��������������  20220718
#define STT_CMD_TYPE_ATS_QueryItem		    _T("QueryItem") //shaolei ��ȡ������Ŀ�Ĳ�������  20220913
#define STT_CMD_TYPE_ATS_UpdateItem  		_T("UpdateItem") //shaolei ���²�����Ŀ�Ĳ�������  20220913
#define STT_CMD_TYPE_ATS_AdjustReport		_T("AdjustReport")   //shaolei ��������  20230505
#define STT_CMD_TYPE_ATS_ClearReportsRslts  _T("ClearReportsRslts")   //shaolei ����������� 2023-7-17

//lijunqing 2023-9-12  ����FLowģʽ��FlowSetBentch��StartTest��CloseTest���һ�����̲��裬�������̽���ʹ��ExitTest
#define STT_CMD_TYPE_ATS_ExitTest  _T("ExitTest")

//2020-12-01  lijunqing
#define STT_CMD_TYPE_ATS_QueryAtsFile	_T("QueryAtsFile")
//2021-07-26  shaolei
#define STT_CMD_TYPE_ATS_ExportReport		_T("ExportReport")
#define STT_CMD_TYPE_ATS_SetItemsReport		_T("SetItemsReport")
#define STT_CMD_TYPE_ATS_QueryItems	        _T("QueryItems")
//2021-7-26  lijunqing
#define STT_CMD_TYPE_ATS_FlowSetBench	        _T("FlowSetBench")
#define STT_CMD_TYPE_ATS_ConfigAtsService	        _T("ConfigAtsService")
//2021-8-14  lijunqing
#define STT_CMD_TYPE_ATS_ConfigTest	        _T("ConfigTest")
//shaolei 20210927
#define STT_CMD_TYPE_ATS_UploadReportFinished	_T("UploadReportFinished")
//shaolei 20211031
#define STT_CMD_TYPE_ATS_QueryTestPara	        _T("QueryTestPara")
#define STT_CMD_TYPE_ATS_SetTestPara	        _T("SetTestPara")

//shaolei 2023-5-24
#define STT_CMD_TYPE_ATS_UploadTemplate         _T("UploadTemplate")   //����ģ��
#define STT_CMD_TYPE_ATS_ImportTaskInfo         _T("ImportTaskInfo")   //����������Ϣ
#define STT_CMD_TYPE_ATS_ImportSampleInfo       _T("ImportSampleInfo")   //������Ʒ��Ϣ����Ʒ�б�����������
#define STT_CMD_TYPE_ATS_CreateTask             _T("CreateTask")   //��������

//shaolei 2022-01-07
#define STT_CMD_TYPE_ATS_GenerateTemplate       _T("GenerateTemplate")
#define STT_CMD_TYPE_ATS_GenerateItems          _T("GenerateItems")
#define STT_CMD_TYPE_ATS_SetItemPara            _T("SetItemPara")
//shaolei  2023-4-8  ��ӵ�������Ŀ��������Ӷ������
#define STT_CMD_TYPE_ATS_GenerateMacroTest          _T("GenerateMacroTest")
//2022-3-23  lijunqing
#define STT_CMD_TYPE_ATS_SaveTemplate            _T("SaveTemplate")
#define STT_CMD_TYPE_ATS_SaveTest            _T("SaveTest")
#define STT_CMD_TYPE_ATS_OpenTemplate            _T("OpenTemplate")
//shaolei  2023-6-25 
#define STT_CMD_TYPE_ATS_ExportWordRpt            _T("ExportWordRpt")

//2022-12-25  lijunqing
#define STT_CMD_TYPE_ATS_BeginRecord            _T("BeginRecord")
#define STT_CMD_TYPE_ATS_StartDetect            _T("StartDetect")

//������Լ����  20210619  xxy
#define STT_CMD_TYPE_IOT_PkgParse			_T("PkgParse")
#define STT_CMD_TYPE_IOT_PkgProduce			_T("PkgProduce")
#define STT_CMD_TYPE_IOT_RunProcedure		_T("RunProcedure")
#define STT_CMD_TYPE_IOT_GetDataset			_T("GetDataset")
#define STT_CMD_TYPE_IOT_SetDataset			_T("SetDataset")
#define STT_CMD_TYPE_IOT_CreateDevice		_T("CreateDevice")
#define STT_CMD_TYPE_IOT_ConfigDevice		_T("ConfigDevice")
#define STT_CMD_TYPE_IOT_CloseDevice		_T("CloseDevice")
#define STT_CMD_TYPE_IOT_UpdateDataset      _T("UpdateDataset")


//Զ��Э������
#define STT_CMD_TYPE_ASSIST_GetTestParas	_T("GetTestParas")
#define STT_CMD_TYPE_ASSIST_SetTestParas	_T("SetTestParas")
#define STT_CMD_TYPE_ASSIST_StartTest		_T("StartTest")
#define STT_CMD_TYPE_ASSIST_StopTest		_T("StopTest")
#define STT_CMD_TYPE_ASSIST_SelectTestMacro	_T("SelectTestMacro")
#define STT_CMD_TYPE_ASSIST_RunExe			_T("RunExe")
#define STT_CMD_TYPE_ASSIST_ImportDvmFile	_T("ImportDvmFile")
#define STT_CMD_TYPE_ASSIST_ReadDataset		_T("ReadDataset")
#define STT_CMD_TYPE_ASSIST_ReadCmdRslt		_T("ReadCmdRslt")
#define STT_CMD_TYPE_ASSIST_WriteDataset	_T("WriteDataset")
#define STT_CMD_TYPE_ASSIST_Reset			_T("Reset")
#define STT_CMD_TYPE_ASSIST_ReadSetZone		_T("ReadSetZone")
#define STT_CMD_TYPE_ASSIST_WriteSetZone	_T("WriteSetZone")
#define STT_CMD_TYPE_ASSIST_StartReport		_T("StartReport")
#define STT_CMD_TYPE_ASSIST_StopReport		_T("StopReport")
#define STT_CMD_TYPE_ASSIST_CreateDevcie	_T("CreateDevice")
#define STT_CMD_TYPE_ASSIST_EnumDevice		_T("EnumDevice")
#define STT_CMD_TYPE_ASSIST_EnumLdevice		_T("EnumLdevice")
#define STT_CMD_TYPE_ASSIST_EnumDataset		_T("EnumDataset")
#define STT_CMD_TYPE_ASSIST_SelectDvmNode	_T("SelectDvmNode")

#define STT_CMD_TYPE_ALL_Reply	_T("Reply")

//////////////////////////////////////////////////////////////////////////
//��������
//�ļ��������
#define STT_CMD_PARA_FILE_PATH             _T("file-path")
#define STT_CMD_PARA_FILE_STATE           _T("file-state")
#define STT_CMD_PARA_FILE_PERMISSION   _T("permission")
#define STT_CMD_PARA_FILE_NAME             _T("file-name")
//2022-3-23  lijunqing
#define STT_CMD_PARA_FILE_RootPath             _T("RootPath")
#define STT_CMD_PARA_FILE_GetSubDirs             _T("GetSubDirs")
#define STT_CMD_PARA_FILE_GetFiles             _T("GetFiles")
#define STT_CMD_PARA_FILE_FileTypes            _T("FileTypes")
#define STT_CMD_PARA_FILE_FileType            _T("FileType")


//���Զ�ID
#define STT_CMD_PARA_IDTESTER  _T("id-tester")
#define STT_CMD_PARA_Test_ID  _T("TestID")
#define STT_CMD_PARA_DeviceID  _T("DeviceID")
#define STT_CMD_PARA_ItemID  _T("ItemID")
#define STT_CMD_PARA_ItemName  _T("ItemName")
#define STT_CMD_PARA_CommConfig  _T("comm-config")
#define STT_CMD_PARA_CommConfigs  _T("comm-configs")
#define STT_CMD_PARA_ItemPath  _T("ItemPath")
#define STT_CMD_PARA_ItemType  _T("ItemType")
#define STT_CMD_PARA_MacroID  _T("MacroID")
#define STT_CMD_PARA_ItemIndex  _T("ItemIndex")
#define STT_CMD_PARA_DeviceIndex  _T("DeviceIndex")
#define STT_CMD_PARA_ReportIndex  _T("ReportIndex")
#define STT_CMD_PARA_Select  _T("Select")
#define STT_CMD_PARA_Enable  _T("Enable")
#define STT_CMD_PARA_Show  _T("Show")
#define STT_CMD_PARA_State  _T("State")
#define STT_CMD_PARA_DatasetPath  _T("dataset-path")
#define STT_CMD_PARA_DestPath  _T("dest-path")
#define STT_CMD_PARA_ProcedureID  _T("id-procedure")
#define STT_CMD_PARA_RecordMode  _T("RecordMode")
#define STT_CMD_PARA_TestTotalTimeLong _T("Test_Total_Time_Long")
#define STT_CMD_PARA_DelayBeforeCmd  _T("delaybeforecmd")
#define STT_CMD_PARA_DelayAfterCmd  _T("delayaftercmd")
#define STT_CMD_PARA_RepeatTimes  _T("testcount")
#define STT_CMD_PARA_RptCalMode   _T("rptcalmode")
#define STT_CMD_PARA_ItemsSel  _T("ItemsSel")
#define STT_CMD_PARA_ItemSel  _T("ItemSel")
#define STT_CMD_PARA_LogInTime  _T("LogInTime")//���ݵ�¼ʱ��

#define STT_CMD_PARA_LogDataBind  _T("log-data-bind")
#define STT_CMD_PARA_LogPkgDataInfo  _T("log-pkg-data-infor")
#define STT_CMD_PARA_LogPkg  _T("log-pkg")
#define STT_CMD_PARA_LogProtocolDebugInfor  _T("log-protocol-debug-infor")
#define STT_CMD_PARA_LogServerDebugInfor  _T("log-server-debug-infor")
#define STT_CMD_PARA_NoChangeWhenSame  _T("no-change-when-same")
#define STT_CMD_PARA_LogDebugInfor  _T("log-debug-infor")
#define STT_CMD_PARA_LogServerSpyAllCmd  _T("spy-all-cmd")
#define STT_CMD_PARA_LogServerSpyAllCmd  _T("spy-all-cmd")
#define STT_CMD_PARA_CloseTestWhenDisconnect  _T("close-test-when-disconnect")
#define STT_CMD_PARA_TestItemCount _T("TestItemCount")
#define STT_CMD_PARA_OnlySelect _T("OnlySelect")
#define STT_CMD_PARA_LoopTest _T("LoopTest")

//2021-7-26  lijunqing
#define STT_CMD_PARA_BenchID  _T("BenchID")

//20210727 shaolei
#define STT_CMD_PARA_EventID  _T("EventID")
//����ID��ָ�������ĸ������ǡ�
//����ID��ָ�������ĸ��ӿڳ������磺IotVm.Engine��PonovoVm.Engine
#define STT_CMD_PARA_EngineProgID _T("EngineProgID")
//2023-8-17  lijunqing  Ϊ�Զ���������ͨ������ģʽ
#define STT_CMD_PARA_EngineMode            _T("EngineMode")
#define STT_CMD_PARA_EngineMode_COM    _T("COM")
#define STT_CMD_PARA_EngineMode_STT     _T("STT")
#define STT_CMD_PARA_EngineMode_MQTT  _T("MQTT")

//������IDһ�µ�����£�������ͬ�Ĳ�����ͨѶ�������磺IotVm.XLDL��IotVm.Simpac
#define STT_CMD_PARA_ProtocolID _T("ProtocolID") 
#define STT_CMD_PARA_MacroFile _T("MacroFile")
//2021-8-2  lijunqing
#define STT_CMD_PARA_BenchSN  _T("BenchSN")
#define STT_CMD_PARA_DeviceSN  _T("DeviceSN")
//2021-8-3 shaolei
#define STT_CMD_PARA_TotalItems  _T("TotalItems")
#define STT_CMD_PARA_CurrItem  _T("CurrItem")
#define STT_CMD_PARA_TotalTime  _T("TotalTime")
#define STT_CMD_PARA_RemainTime  _T("RemainTime")
#define STT_CMD_PARA_DeviceState  _T("DeviceState")
#define STT_CMD_PARA_CurrDevice  _T("CurrDevice")
#define STT_CMD_PARA_TotalDevices  _T("TotalDevices")
#define STT_CMD_PARA_CurrItemName  _T("CurrItemName")
#define STT_CMD_PARA_NextItemName  _T("NextItemName")

//2021-10-28 shaolei
#define STT_CMD_PARA_ChMapConfig_File  _T("_ChMapConfig_File")
#define STT_CMD_PARA_IecCfg_File  _T("_IecCfgFile")
//2023-5-10 shaolei
#define STT_CMD_PARA_Record_File_Name  _T("RecordFileName")

//liveupdate para
#define STT_CMD_PARA_LIVEUPDATE_IP			 _T("ip")
#define STT_CMD_PARA_LIVEUPDATE_PORT		 _T("port")
#define STT_CMD_PARA_LIVEUPDATE_IPCLOUD		 _T("ip_cloud")
#define STT_CMD_PARA_LIVEUPDATE_PORTCLOUD	 _T("port_cloud")
#define STT_CMD_PARA_LIVEUPDATE_FTPPORTCLOUD _T("ftpport_cloud")
#define STT_CMD_PARA_LIVEUPDATE_SYSID		 _T("sysid")
#define STT_CMD_PARA_LIVEUPDATE_SYSINDEX	 _T("sysindex")
#define STT_CMD_PARA_LIVEUPDATE_VERID		 _T("verid")
#define STT_CMD_PARA_LIVEUPDATE_VERINDEX	 _T("verindex")
#define STT_CMD_PARA_LIVEUPDATE_PREVERID	 _T("preverid")
#define STT_CMD_PARA_LIVEUPDATE_PREVERINDEX	 _T("preverindex")
#define STT_CMD_PARA_LIVEUPDATE_VERFILE		 _T("verfile")
#define STT_CMD_PARA_LIVEUPDATE_UNZIPPATH	 _T("unzippath")
#define STT_CMD_PARA_LIVEUPDATE_STOP		 _T("stop")			//���в���
#define STT_CMD_PARA_LIVEUPDATE_FILEOVER	 _T("fileover")		//���в���
#define STT_CMD_PARA_LIVEUPDATE_REPLY		 _T("reply")		//����״̬����
#define STT_CMD_PARA_LIVEUPDATE_UPDATEINFO	 _T("updateinfo")	//����״̬����
#define STT_CMD_PARA_LIVEUPDATE_RESULT		 _T("result")		//����״̬������0-ʧ�ܣ�1-�ɹ�

//lijunqing 2020-9-18
#define STT_CMD_PARA_AutoSendSocket  _T("auto-send-socket")
#define STT_CMD_PARA_AutoSendTest  _T("auto-send-test")
#define STT_CMD_PARA_AutoSendDMP  _T("auto-send-dmp")

//lijunqing 2020-10-22  for Adjust : ReadDeviceParameter
#define STT_CMD_PARA_DeviceAttrs  _T("DeviceAttrs")
#define STT_CMD_PARA_BoutTrunOnValueDef  _T("BoutTrunOnValueDef")
#define STT_CMD_PARA_ModuleAttrs  _T("ModuleAttrs")
#define STT_CMD_PARA_ChMapDef  _T("ChMapDef")
#define STT_CMD_PARA_HdGears  _T("HdGears")
#define STT_CMD_PARA_AdjustParas  _T("AdjustParas")

//lijunqing 2020-10-22  for Test/ATS : GetSystemState
#define STT_CMD_PARA_DeviceStatus  _T("DeviceStatus")
#define STT_CMD_PARA_TestStatus  _T("TestStatus")
#define STT_CMD_PARA_AtsStatus  _T("AtsStatus")
#define STT_CMD_PARA_LiveUpdateStatus  _T("LiveUpdateStatus")

#define STT_SYS_DATA_ID_Sync    _T("Sync")
#define STT_SYS_DATA_ID_Utc_s    _T("Utc_s")
#define STT_SYS_DATA_ID_Utc_ns    _T("Utc_ns")
#define STT_SYS_DATA_ID_StopByHighT    _T("StopByHighT")
#define STT_SYS_DATA_ID_usezip		_T("use-zip")
#define STT_SYS_DATA_ID_verzip		_T("ver-zip")
#define STT_SYS_DATA_ID_IP			_T("IP")
#define STT_SYS_DATA_ID_mask		_T("mask")
#define STT_SYS_DATA_ID_GateWay		_T("GateWay")
#define STT_SYS_DATA_ID_SubIP		_T("SubIP")
#define STT_SYS_DATA_ID_SubIP1		_T("SubIP1")
#define STT_SYS_DATA_ID_DeviceIP	_T("DeviceIP")
#define STT_SYS_DATA_ID_Metric		_T("Metric")


//shaolei  2022-01-07
#define STT_CMD_PARA_TtRetMode        _T("TtRetMode")    //ģ�巵��ģʽ
#define STT_CMD_PARA_TestMacroUI      _T("test-macro-ui")
#define STT_CMD_PARA_MacroUIParas     _T("macro-ui-paras")
#define STT_CMD_PARA_TestMacroUI_ID   _T("TestMacroUI")
#define STT_CMD_PARA_GenFile          _T("gen-file")
#define STT_CMD_PARA_GridFile          _T("grid-file")
#define STT_CMD_PARA_UIFile           _T("ui-file")
#define STT_CMD_PARA_UIParaFile       _T("ui-para-file")
#define STT_CMD_PARA_ReportFile       _T("report-file")
#define STT_CMD_PARA_ParentItemsPath  _T("ParentItemsPath")
#define STT_CMD_PARA_ItemParas        _T("item-paras")
#define STT_CMD_PARA_TestMacroParas   _T("test-macro-paras")
#define STT_CMD_PARA_HasDigital     _T("HasDigital")
#define STT_CMD_PARA_HdRsFile     _T("hd-rs-file")
#define STT_CMD_PARA_ContentsParas        _T("contents-paras")
#define STT_CMD_PARA_Characteristic     _T("characteristic")
#define STT_CMD_PARA_CharLibFile          _T("charlib-file")
#define STT_CMD_PARA_UI_ID              _T("ui-id")
#define STT_CMD_PARA_CommCmd            _T("comm-cmd")
#define STT_CMD_PARA_Before_Test        _T("_BeforeTest_")
#define STT_CMD_PARA_After_Test         _T("_AfterTest_")
#define STT_CMD_PARA_DS_PATH            _T("ds-path")
#define STT_CMD_PARA_MACRO_NAME         _T("macro-name")
//2023-2-1 shaolei
#define STT_CMD_PARA_SrcParentItemsPath  _T("SrcParentItemsPath")
#define STT_CMD_PARA_SrcItemsID           _T("SrcItemsID")
#define STT_CMD_PARA_RsltEpxr       _T("rslt-expr")

//2023-3-10
#define STT_CMD_PARA_GlobalDatas   _T("GlobalDatas")   //ȫ������
#define STT_CMD_PARA_SysPara   _T("sys-para")   //���Բ���
//2023-7-19
#define STT_CMD_PARA_SafetyDatas            _T("safety-datas")

//2022-3-29  lijunqing 
#define STT_CMD_PARA_generate_items  _T("generate-items")
#define STT_CMD_PARA_ItemsID           _T("ItemsID")
#define STT_CMD_PARA_generate_items_create             _T("create")
#define STT_CMD_PARA_generate_items_new             _T("new")
#define STT_CMD_PARA_generate_items_delete           _T("delete")
#define STT_CMD_PARA_generate_items_edit			   _T("edit")
#define STT_CMD_PARA_generate_items_move            _T("move")
#define STT_CMD_PARA_generate_items_cmd_wzd		   _T("cmd-wzd")
#define STT_CMD_PARA_generate_items_cmd_add		   _T("cmd-add")
#define STT_CMD_PARA_generate_items_macro_add		   _T("macro-add")
#define STT_CMD_PARA_generate_items_move_up		   _T("move-up")
#define STT_CMD_PARA_generate_items_move_down		   _T("move-down")
#define STT_CMD_PARA_generate_items_paste		   _T("item-paste")
#define STT_CMD_PARA_generate_items_insert_after    _T("insert-after")
#define STT_CMD_PARA_generate_items_insert_before  _T("insert-before")
#define STT_CMD_PARA_generate_items_insert_head    _T("insert-head")
#define STT_CMD_PARA_generate_items_insert_tail       _T("insert-tail")
#define STT_CMD_PARA_generate_items_insert_tail       _T("insert-tail")
#define STT_CMD_PARA_generate_items_items       _T("items")
#define STT_CMD_PARA_generate_items_ItemsName     _T("ItemsName")
#define STT_CMD_PARA_generate_items_ItemsID    STT_CMD_PARA_ItemsID
#define STT_CMD_PARA_generate_items_RepeatTimes    _T("repeat-times")
#define STT_CMD_PARA_generate_items_MacroParas    _T("macro-paras")
#define STT_CMD_PARA_generate_items_MacroID    _T("macroid")
#define STT_CMD_PARA_generate_items_RptTitle    _T("rpt-title")
#define STT_CMD_PARA_generate_items_TitleLevel    _T("title-level")
#define STT_CMD_PARA_generate_items_AinDataMapCfg    _T("AinDataMapCfg")
#define STT_CMD_PARA_generate_items_AinRatios    _T("AinRatios")
//2023-7-19
#define STT_CMD_PARA_generate_items_safety_add		   _T("safety-add")
//2023-8-11
#define STT_CMD_PARA_generate_items_cmd_add_grp		   _T("cmd-add-grp")
//2023-8-14
#define STT_CMD_PARA_generate_items_import_dvm_file		   _T("import-dvm-file")
//2023-8-28
#define STT_CMD_PARA_generate_items_ain_data_map		   _T("ain-data-map")
//2023-10-23  ����word����ʹ��
#define STT_CMD_PARA_items_tecs   _T("items-tecs")  //�޸ĵġ�����Ҫ��+ ���������ݱ���С��λ����
#define STT_CMD_PARA_items_tec    _T("items-tec")
//2023-12-6
#define STT_CMD_PARA_DevMeas    _T("DevMeas")  //װ�ò�����Ϣ����һ��ֵ���Ƕ���ֵ��1|2
#define STT_CMD_PARA_PtPrimary    _T("PtPrimary")  //PTһ��ֵ
#define STT_CMD_PARA_PtSecondary    _T("PtSecondary")  //PT����ֵ
#define STT_CMD_PARA_CtPrimary    _T("CtPrimary")   //CTһ��ֵ
#define STT_CMD_PARA_CtSecondary    _T("CtSecondary")   //CT����ֵ

#define XPARA_ID_AftUseDevReset   _T("aft-use-devreset")
#define XPARA_ID_AddCommCmd  _T("add-commcmd")
#define XPARA_ID_IsDvmMap   _T("is-dvm-map")

#define STT_CMD_PARA_VarType           _T("VarType")
#define STT_CMD_PARA_VaryMode           _T("VaryMode")
#define STT_CMD_PARA_DvmFile          _T("dvm-file")
#define STT_CMD_PARA_TestClass          _T("test-class")
#define STT_CMD_PARA_MoveTimes          _T("move-times")

#define STT_CMD_PARA_ZoneIndex         _T("zone-index")   //��ֵ����
#define STT_CMD_PARA_TrgOps_4          _T("TrgOps_4")   //��������
#define STT_CMD_PARA_TrgOps_2          _T("TrgOps_2")   //Ʒ������
#define STT_CMD_PARA_TrgOps_1          _T("TrgOps_1")    //�仯����
#define STT_CMD_PARA_IntgPd            _T("IntgPd")    //��������ʱ��

//����ֶ�ͳһΪ   item-paras
// #define STT_CMD_PARA_ItemPara            _T("item-para")

//lijunqing 2022-9-12 ����������
#define STT_CMD_PARA_CmdGenParas         _T("cmd-gen-paras")
#define STT_CMD_PARA_CmdGenCfg            _T("cmd-gen-cfg")
#define STT_CMD_PARA_CMDSINGLE            _T("cmd-single")
#define STT_CMD_PARA_CMDBFT                _T("cmd-bft")
#define STT_CMD_PARA_CMDAFT                _T("cmd-aft")
#define STT_CMD_PARA_GBITEMSTREE        _T("gb-items-tree")


//����������صĲ���ID
#define STT_CMD_PARA_XB     _T("x-b")
#define STT_CMD_PARA_YB     _T("y-b")
#define STT_CMD_PARA_XE     _T("x-e")
#define STT_CMD_PARA_YE     _T("y-e")
#define STT_CMD_PARA_XSET   _T("x-set")
#define STT_CMD_PARA_YSET   _T("y-set")
#define STT_CMD_PARA_XACT   _T("x-act")
#define STT_CMD_PARA_YACT   _T("y-act")
#define STT_CMD_PARA_FLAGACT       _T("flag-act")
#define STT_CMD_PARA_SEARCH_XB     _T("search-x-b")
#define STT_CMD_PARA_SEARCH_YB     _T("search-y-b")
#define STT_CMD_PARA_SEARCH_ACTB   _T("search-actb")
#define STT_CMD_PARA_SEARCH_XE     _T("search-x-e")
#define STT_CMD_PARA_SEARCH_YE     _T("search-y-e")
#define STT_CMD_PARA_SEARCH_ACTE   _T("search-acte")
#define STT_CMD_PARA_SEARCH_XC     _T("search-x-c")
#define STT_CMD_PARA_SEARCH_YC     _T("search-y-c")
#define STT_CMD_PARA_SEARCH_LINE   _T("SearchLine")

#define STT_CMD_PARA_TtRetMode_GBXML  _T("gbxml")    //ģ�巵��ģʽ��ȫģ��
#define STT_CMD_PARA_TtRetMode_DSCXML _T("dscxml")    //ģ�巵��ģʽ��ģ���Ҫ��Ϣ
#define STT_CMD_PATA_TestMode         _T("test-mode")  //����ģʽ��1-�Զ����ԣ�0-��������
//2022-3-14  lijunqing
#define STT_CMD_PARA_GenForDebug     _T("gen-for-debug")

//2022-8-4  lijunqing  Record ��ز���
#define STT_CMD_PARA_RcdDataID _T("RcdDataID")  
#define STT_CMD_PARA_TotalSize    _T("TotalSize")  
#define STT_CMD_PARA_DataCount    _T("DataCount")  
#define STT_CMD_PARA_PkgSize      _T("PkgSize")  
#define STT_CMD_PARA_Zip            _T("Zip")  
#define STT_CMD_PARA_UnZip        _T("UnZip")  

//���ļ������  shaolei 2023-12-22
#define STT_CMD_PARA_Time	        _T("Time")
#define STT_CMD_PARA_Pkg	        _T("Pkg")
#define STT_CMD_PARA_Type	        _T("Type")
#define STT_CMD_PARA_Dir	        _T("Dir")

//ϵͳ�ļ�����
#define  STT_MACRO_UI_MNGR_RELAYTEST   _T("SttMacroUIMngr-RelayTest.xml")      //���Թ��ܽ�������ļ�


/*
6.2.1ͨ������
���Զ��������֮��ͳһ����TCP/IPЭ�����ͨ�š�����ϵͳ��Ʒ����Ҫ�󣬲����ǵײ�Ĳ��Կ��Ʋ��֡��Զ�������Ϊ��ͬ�ķ���ˡ�
�����ǵײ���Է��񣺶˿ںŶ�Ϊ19814��1+1998+2014����
�����ǵײ��Զ����Է��񣺶˿ںŶ�Ϊ19815��
��ƽ̨Զ�̿��Ʒ��񣺶˿ں�Ϊ19816��
��ƽ̨�������񼴱��������������񣺶˿ں�Ϊ19817��
ͨѶ��Լ���棺PpEngine�˿ں�Ϊ19818��
ͨѶ��Լ���棺MmsEngine�˿ں�Ϊ19819��
ͨѶ��Լ���棺DltEngine�˿ں�Ϊ19820��
ͨѶ��Լ���棺��������˿ں�Ϊ19821������IEC������
*/
#define STT_PORT_COMTRADE_SERVER       19813
#define STT_PORT_TEST_SERVER           19814
#define STT_PORT_NATIVE_SERVER         19815
#define STT_PORT_CLOUD_SERVER          19816
#define STT_PORT_LOCAL_UPDATE          19817
#define STT_PORT_PROTOCOL_PP_SERVER    19818   
#define STT_PORT_PROTOCOL_MMS_SERVER   19819
#define STT_PORT_PROTOCOL_DLT_SERVER   19820
#define STT_PORT_PROTOCOL_MEAS_SERVER  19821

//����ADMU��RS485����ת��
#define STT_PORT_UART_1  19001
#define STT_PORT_UART_2  19002
#define STT_PORT_UART_3  19003
#define STT_PORT_UART_4  19004

#define  STT_Multicast_IP   "234.5.6.7"
#define  STT_Multicast_Port   8089

#define  STT_PROCESS_PUDA            "PUDA"
#define  STT_PROCESS_TESTSERVER      "SttTestServer"
#define  STT_PROCESS_LIVEUPDATE      "SttLiveUpdate"
#define  STT_PROCESS_TESTMAINCORE    "SttTestMainCore"

//////////////////////////////
#define XPARA_ID_GBXMLFILE  _T("gbxml-file")
#define XPARA_ID_XTESTDB_TASKS  _T("xtest-db-task")
#define XPARA_ID_DEVICE_ATTR  _T("device-attr")
#define XPARA_ID_GBRPTFILE  _T("gbrpt-file")
#define XPARA_ID_DVMFILE    _T("dvm-file")
#define XPARA_ID_DVMFILE_DST    _T("dvm-file-dst")
#define XPARA_ID_DVMFILES    _T("dvm-files")
#define XPARA_ID_PPXMLFILE   _T("ppxml-file")
#define XPARA_ID_TscdFile    _T("tscd-file")
#define XPARA_ID_IecfgFile   _T("iecfg-file")
#define XPARA_ID_DvmMapFile  _T("dvmmap-file")
#define XPARA_ID_CommCfgFile  _T("cmm-cfg-file")
#define XPARA_ID_XmlRptFile  _T("xmlrpt-file")
#define XPARA_ID_Path  _T("path")
#define XPARA_ID_Src_Path  _T("src-path")
//shaolei 20210926
#define XPARA_ID_DOCRPTFILE_EX    _T("doc-ex-file")
#define XPARA_ID_DOCRPTFILE_EX_S  _T("doc-ex-file_s")
#define XPARA_ID_PDFFILE    _T("pdf_file")
#define XPARA_ID_PDFFILE_S  _T("pdf_file_s")
#define XPARA_ID_TOTALITEMS  _T("total-items")
#define XPARA_ID_ELIGIBLEITEMS    _T("eligible-items")
#define XPARA_ID_INLEGIBLEITEMS  _T("inlegible-items")
//2023-9-13  lijunqing  ���������ģʽ
#define XPARA_ID_Export_Mode  _T("ExportMode")
#define XPARA_Val_Export_Mode_single  _T("single")
#define XPARA_Val_Export_Mode_gbrpts  _T("gbrpts")
#define XPARA_Val_Export_Mode_docs     _T("docs")
#define XPARA_Val_Export_Para_doc       _T("doc")
#define XPARA_Val_Export_Para_RptFiles  _T("rpt-files")
#define XPARA_Val_Export_Para_RptFile    _T("rpt-file")
#define XPARA_Val_Export_Para_gbrpts    _T("gbrpts")
#define XPARA_Val_Export_Para_gbrpt     _T("gbrpt")
#define XPARA_ID_Export_DestPath  _T("DestPath")

//begin ���¶��壬����PAL
#define XPARA_Val_Export_Para_TestInfo  _T("TestInfo")
#define XPARA_Val_Export_Para_TaskInfo  _T("TaskInfo")
#define XPARA_Val_Export_Para_ReportFile  _T("ReportFile")
#define XPARA_Val_Export_Para_SampleInfo  _T("SampleInfo")
#define XPARA_Val_Export_Para_TestAppInfo  _T("TestAppInfo")
#define XPARA_ID_SamplePic  _T("SamplePic")
#define XPARA_ID_TestApps   _T("TestApps")
//end

//2021-8-1  lijunqing
#define XPARA_ID_Remote_ip  _T("remote-ip")
#define XPARA_ID_Remote_port  _T("remote-port")
//2023-3-26  shaolei
#define XPARA_ID_Time_unit_ms  _T("time-unit-ms")
#define XPARA_ID_AddDevReset   _T("add-devreset")

//2021-8-1 shaolei
#define XPARA_ID_GBXMLFILE_S  _T("gbxml-file_s")
#define XPARA_ID_DVMFILE_S    _T("dvm-file_s")
#define XPARA_ID_PPXMLFILE_S   _T("ppxml-file_s")
#define XPARA_ID_DOCRPTFILE_S  _T("doc-file_s")
#define XPARA_ID_GBRPTFILE_S  _T("gbrpt-file_s")
#define XPARA_ID_DOCFILE    _T("doc-file")
#define XPARA_ID_XMLRPTFILE    _T("xml-file")
#define XPARA_ID_XMLRPTFILE_S    _T("xml-file_s")
//2021-8-11 shaolei
#define XPARA_ID_IECFGFILE    _T("iecfg-file")
#define XPARA_ID_IECFGFILE_S    _T("iecfg-file_s")
#define XPARA_ID_bin_for_start  _T("bin-for-start")

//shaolei 2023-5-25
#define XPARA_ID_TASKFILE   _T("TaskFile")
#define XPARA_ID_TASKFILE_S   _T("TaskFile_s")
#define XPARA_ID_BASICINFO   _T("BasicInfo")    //������Ϣ�Ļ�����Ϣ
#define XPARA_ID_InspectionBases   _T("InspectionBases")    //������Ϣ�ļ���������Ϣ
#define XPARA_ID_SampleDevices   _T("SampleDevices")    //��Ʒ�б�
#define XPARA_ID_RatedParameter   _T("RatedParameter")    //��Ʒ�Ķ����
#define XPARA_ID_DevDvm   _T("DevDvm")    //��Ʒ�ĵ�����
#define XPARA_ID_TaskSN   _T("TaskSN")    //����ID
#define XPARA_ID_TaskTestSN   _T("TaskTestSN")   //���Լ�¼ID
#define XPARA_ID_TestType  _T("TestType")   //��������
#define XPARA_ID_SampleSN  _T("SampleSN")   //��Ʒ���
#define XPARA_ID_SampleModel  _T("SampleModel")   //��Ʒ�ͺ�
#define XPARA_ID_SampleName  _T("SampleName")   //��Ʒ����
#define XPARA_ID_ClientName  _T("ClientName")   //ί�е�λ����
#define XPARA_ID_ClientAddress  _T("ClientAddress")   //ί�е�λ��ַ
#define XPARA_ID_ManufactorName  _T("ManufactorName")   //���쵥λ����
#define XPARA_ID_ManufactorAddress  _T("ManufactorAddress")   //���쵥λ��ַ
#define XPARA_ID_CURRENTINDEX    _T("CurrIndex")   //��ǰ���
#define XPARA_ID_TOTALCUOUNT    _T("TotalCount")   //����
#define XPARA_ID_ItemsSN    _T("ItemsSN")   //���Դ���ID
#define XPARA_ID_USER_NAME   _T("user_name")  //�û�����
#define XPARA_ID_Humidity    _T("Humidity")   //ʪ��
#define XPARA_ID_Tempreture   _T("Tempreture")  //�¶�

//shaolei 2023-2-21 �Զ���������ģʽ
#define XPARA_ID_SmartTestRunMode  _T("smart-test-run-mode")
#define SmartTest_Run_Mode_Local  _T("local")
#define SmartTest_Run_Mode_Server  _T("server")
////////////////////////////////

#define MQTT_DATA_FORMAT_JSON	_T("JSON")
#define MQTT_DATA_FORMAT_XML	_T("XML")

#define MQTT_SYSSTATE_TYPE_REPLY		_T("REPLY")
#define MQTT_SYSSTATE_TYPE_EVENT		_T("EVENT")
#define MQTT_SYSSTATE_TYPE_REPORT		_T("REPORT")
#define MQTT_SYSSTATE_TYPE_EXCEPTION	_T("EXCEPTION")

//�����¼�
#define RUNPROCEDURE_EVENT_ConnectDeviceFailed			_T("ConnectDeviceFailed")
#define RUNPROCEDURE_EVENT_ConnectDeviceSuccessful		_T("ConnectDeviceSuccessful")
#define RUNPROCEDURE_EVENT_CommError					_T("CommError")
#define RUNPROCEDURE_EVENT_CommFinish					_T("CommFinish")
#define RUNPROCEDURE_EVENT_CommCmdError					_T("CommCmdError")
#define RUNPROCEDURE_EVENT_Exception					_T("Exception")
#define RUNPROCEDURE_EVENT_CommOverTime					_T("CommOverTime")

//2021-8-4  lijunqing
#define XPARA_ID_devices      _T("devices")
#define XPARA_ID_device      _T("device")
#define XPARA_ID_test_apps   _T("test-apps")
#define XPARA_ID_test_app   _T("test-app")
#define XPARA_ID_devices_one_test      _T("one-test")
#define XPARA_ID_devices_multi_test      _T("multi-test")


//2021-9-1  lijunqing  ���������豸�ĵ�ַ
#define XPARA_ID_Address  _T("address")

//2021-11-04 sf
#define XPARA_ID_Remote_Comm  _T("remote-Comm")
#define XPARA_ID_Remote_Rate  _T("remote-Rate")
#define XPARA_ID_Remote_DataBit  _T("remote-DataBit")
#define XPARA_ID_Remote_StopBit  _T("remote-StopBit")
#define XPARA_ID_Remote_Parity  _T("remote-Parity")

//2022-4-9  lijunqing IEC����
#define XPARA_ID_IEC_CB _T("IEC_CB")
#define XPARA_ID_Type _T("Type")
#define XPARA_ID_Port _T("Port")
#define XPARA_ID_CRC _T("CRC")
#define XPARA_ID_APPID _T("APPID")
#define XPARA_ID_PkgDetect _T("PkgDetect")
#define XPARA_ID_DestMac _T("DestMac")
#define XPARA_ID_BaudRate _T("BaudRate")
#define XPARA_ID_SampleRate _T("SampleRate")
#define XPARA_ID_OnePkgLen _T("OnePkgLen")
#define XPARA_ID_STMode _T("STMode")
//2022-6-11  lijunqing  ̽�ⷵ��ͨ����
#define XPARA_ID_ChCount _T("ChCount")

#define XPARA_ID_TYPE_SMV92  _T("SMV92")
#define XPARA_ID_TYPE_SMV91  _T("SMV91")
#define XPARA_ID_TYPE_FT3        _T("FT3")
#define XPARA_ID_TYPE_GOOSE    _T("GOOSE") 


#define XPARA_ID_MainWnd  _T("main-wnd")
#define XPARA_ID_LogWnd  _T("log-wnd")
#define XPARA_ID_ADJUSTREPORT_ShowWnd  _T("adjust-report-show-wnd")

#define XPARA_ID_TestName  _T("TestName")

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//from SttSysState.h   2022-8-1  lijunqing

//////////////////////////////////////////////////////////////////////////
////ϵͳ״̬ͨ������
//��������	IOverLoad	
#define STT_SYS_STATE_ID_IOverLoad  _T("IOverLoad")
//��ѹ����	UOverLoad	
#define STT_SYS_STATE_ID_UOverLoad  _T("UOverLoad")
//����	OverHeat	
#define STT_SYS_STATE_ID_OverHeat  _T("OverHeat")
//������·	IBreak	
#define STT_SYS_STATE_ID_IBreak  _T("IBreak")
//��ѹ��·	UShort	
#define STT_SYS_STATE_ID_UShort  _T("UShort")
//����ִ��״̬	ExecStatus	0=ִ��ʧ��  1=ִ�гɹ�
#define STT_SYS_STATE_ID_ExecStatus  _T("ExecStatus")
//ͨѶ״̬	ConnectState	0=������ 1=���ӳɹ� ����=�Զ���
#define STT_SYS_STATE_ID_ConnectState  _T("ConnectState")
//���״̬	OutputState	0=����   1=�ѿ�ʼ  2=�����
#define STT_SYS_STATE_ID_OutputState  _T("OutputState")
//����״̬	CurrStateIndex	0=����  1=״̬1�ѿ�ʼ   2=״̬2�ѿ�ʼ  ����
#define STT_SYS_STATE_ID_CurrStateIndex  _T("CurrStateIndex")
#define STT_SYS_STATE_ID_CurrentStepIndex  _T("CurrStepIndex")
//���������	ErrCmd	���������ID
#define STT_SYS_STATE_ID_ErrCmd  _T("ErrCmd")
//���󲻴���	DataNotExist	�����ڵ����ݣ������ļ�����ĿID��
#define STT_SYS_STATE_ID_DataNotExist  _T("DataNotExist")
//�Ƿ�ɹ�	IsSuccess	0=ʧ��    1=�ɹ�
#define STT_SYS_STATE_ID_IsSuccess  _T("IsSuccess")
//����ʱ���ܳ�	TestTimeLong	������ĿԤ�Ʋ���ʱ�䳤��
#define STT_SYS_STATE_ID_TestTimeLong  _T("TestTimeLong")
//����״̬	TestState	0=����  1=�ѿ�ʼ 2=����ɣ�������
#define STT_SYS_STATE_ID_TestState  _T("TestState")
//״̬�л����
#define STT_SYS_STATE_ID_StateChange	_T("StateChange")
//ֱ��
#define STT_SYS_STATE_ID_Udc	_T("Udc")
//�ݱ䷵��
#define STT_SYS_STATE_ID_GadientIndex	_T("GadientIndex")
//�ݱ�״̬
#define STT_SYS_STATE_ID_CurrStepIndex	_T("CurrentStepIndex")		//add by yyj for gradient
//�ݱ����
#define STT_SYS_STATE_ID_GadientEnd	_T("GadientEnd")
/*
<sys-state name="" id="" mater-host="" testor="" id-cmd="" ret-type="">
	<macro type="" id="" state="">
		<results name="" id="">	
			<data id="" value="" />
		</results >
		<paras name="" id="">	
			<data id="" value="" />
		</paras>
	</macro>
	<paras name="" id="">	
		<data id="" value="" />
        <dataset id="" data-type=""/>    2020-5-19  lijunqing
	</paras>
<sys-state>
*/

//Ӧ��=0  �����ϱ�   1
#define SYS_STATE_RETTYPE_REPLY                  _T("REPLY")
#define SYS_STATE_RETTYPE_REPORT                _T("REPORT")
#define SYS_STATE_RETTYPE_USERMNGR            _T("USERMNGR")
#define SYS_STATE_RETTYPE_EXCEPTION           _T("EXCEPTION")
#define SYS_STATE_RETTYPE_STATE                  _T("STATE")
#define SYS_STATE_RETTYPE_SEARCH_REPORT    _T("SEARCH_REPORT")
#define SYS_STATE_RETTYPE_LOG    _T("LOG")
#define SYS_STATE_RETTYPE_EVENT    _T("EVENT")
#define SYS_STATE_RETTYPE_RTDATA   _T("RTDATA")
#define SYS_STATE_RETTYPE_PACKAGE    _T("PACKAGE")
#define SYS_STATE_RETTYPE_UPDATE    _T("UPDATE")
#define SYS_STATE_RETTYPE_MEAS   _T("MEAS")
#define SYS_STATE_RETTYPE_STOP_AUTOTEST   _T("STOP_AUTOTEST")

#define SYS_STATE_EVENT_OnItemStateChanged		_T("ItemStateChanged")
#define SYS_STATE_EVENT_OnTestFinished			_T("TestFinished")
#define SYS_STATE_EVENT_OnTestStarted			_T("TestStarted")
#define SYS_STATE_EVENT_OnTestStoped			_T("TestStoped")
#define SYS_STATE_EVENT_OnTestCloseded			_T("TestClosed")
#define SYS_STATE_EVENT_OnTestExited			_T("TestExited")
#define SYS_STATE_EVENT_OnExportRptFinished		_T("ExportRptFinished")
#define SYS_STATE_EVENT_OnTestAppEvent			_T("TestAppEvent")
#define SYS_STATE_EVENT_OnTestCreated			_T("TestCreated")
#define SYS_STATE_EVENT_OnOpenGbrptFileFailed   _T("OpenGbrptFileFailed")
#define SYS_STATE_EVENT_OnEngineEvent			_T("EngineEvent")
#define SYS_STATE_EVENT_OnEngineReport			_T("EngineReport")
#define SYS_STATE_EVENT_OnSearchPointReport		_T("SearchPointReport")
#define SYS_STATE_EVENT_OnTestItemCount	        _T("TestItemCount")
#define SYS_STATE_EVENT_OnRcdDataLoadFinished   _T("RcdDataLoadFinished")//20221206 zhoulei
//�ز����   ���Բ��ϸ������  shaolei 2022-11-15
#define SYS_STATE_EVENT_OnReTestFinished			_T("ReTestFinished")
#define SYS_STATE_EVENT_OnRTDATA	        _T("OnRTDATA")
#define SYS_STATE_EVENT_OnReprot	        _T("OnReprot")
#define SYS_STATE_EVENT_ExportReport	        _T("ExportReport")
//���ļ���  shaolei 2023-12-22
#define SYS_STATE_EVENT_PkgSpy	        _T("PkgSpy")

//shaolei 20210727
#define SYS_STATE_EVENT_ExportReport          _T("ExportReport")
#define SYS_STATE_XEVENT_EVENTID_ExportBegin    _T("ExportBegin")
#define SYS_STATE_XEVENT_EVENTID_ExportFinish    _T("ExportFinish")
#define SYS_STATE_XEVENT_EVENTID_ExportProcess    _T("ExportProcess")
//shaolei 20210803
#define SYS_STATE_EVENT_OnTestProcess		_T("TestProcess")
#define SYS_STATE_REPORT_OnStateChanged		_T("StateChanged")
//yyj 20210806
#define SYS_STATE_REPORT_OnSwichInChanged		_T("SwichInChanged")
#define SYS_STATE_REPORT_OnSwichOutChanged		_T("SwichOutChanged")
//yyj 20210806
#define SYS_STATE_REPORT_OnUdcChanged		_T("UdcChanged")
#define SYS_STATE_EXCEPTION					_T("Exception")
#define SYS_STATE_UNEXCEPTION					_T("Unexception")
//#define SYS_STATE_REPORT_OnStepChanged		_T("StepChanged")

//TestAppEvent  EngineEvent  DataID  <data name="EventID" id="EventID" value="ConnectSuccess" />
#define SYS_STATE_XEVENT_EVENTID  _T("EventID")
#define SYS_STATE_XEVENT_EVENTID_ConnectSuccess           _T("ConnectSuccess")
#define SYS_STATE_XEVENT_EVENTID_ConnectFailed            _T("ConnectFailed")
#define SYS_STATE_XEVENT_EVENTID_CommError                _T("CommError")
#define SYS_STATE_XEVENT_EVENTID_ConnectDeviceSuccessful  _T("ConnectDeviceSuccessful")
#define SYS_STATE_XEVENT_EVENTID_ConnectDeviceFailed      _T("ConnectDeviceFailed")

//yyj 20210806
#define SYS_STATE_XEVENT_EVENTID_BIN	_T("Event_Bin")
#define SYS_STATE_XEVENT_EVENTID_BOUT   _T("Event_Bout")
#define SYS_STATE_XEVENT_EVENTID_SYNCTIME   _T("SyncTime")
//yyj 20210806
//2022-10-6  lijunqing 
#define SYS_STATE_XEVENT_EVENTID_RtData   _T("Rtdata")

//shaolei 20210926
#define SYS_STATE_EVENT_OnExternTestFinished			_T("ExternTestFinished")
#define SYS_STATE_EVENT_UploadReportFinished		_T("UploadReportFinished")

//����ִ��״̬	ExecStatus	0=δ����  1=ACK 2=ִ��ʧ�ܣ�3=ִ�гɹ�
#define STT_CMD_ExecStatus_NULL		0
#define STT_CMD_ExecStatus_ACK		1
#define STT_CMD_ExecStatus_FAILURE	2
#define STT_CMD_ExecStatus_SUCCESS	3
#define STT_CMD_ExecStatus_TIMEOUT	4
#define STT_CMD_ExecStatus_SocketClose	5

#define STT_LOGIN_TEST_ID_USE_RandomNum
