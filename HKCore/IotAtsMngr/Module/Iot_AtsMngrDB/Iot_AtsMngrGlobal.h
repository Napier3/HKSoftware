//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_AtsMngrGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define IotCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define IotCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define IOTCLASSID_CIOT_DEVICES       (IotCLASSID_EXLISTCLASS + 0X00000000)
#define IOTCLASSID_CIOT_DEVICE       (IotCLASSID_BASECLASS + 0X00000001)
#define IOTCLASSID_CIOT_ENGINE       (IotCLASSID_BASECLASS + 0X00000002)
#define IOTCLASSID_CIOT_BENCH       (IotCLASSID_EXLISTCLASS + 0X00000003)
#define IOTCLASSID_CIOT_TESTTASKDEVICES       (IotCLASSID_EXLISTCLASS + 0X00000004)
#define IOTCLASSID_CIOT_TESTTASKDEVICE       (IotCLASSID_BASECLASS + 0X00000005)
#define IOTCLASSID_CIOT_DEVICEMODEL       (IotCLASSID_BASECLASS + 0X00000006)
#define IOTCLASSID_CIOT_DEVICEMODELS       (IotCLASSID_EXLISTCLASS + 0X00000007)
#define IOTCLASSID_CIOT_DEVICEITEMRSLTS       (IotCLASSID_EXLISTCLASS + 0X00000008)
#define IOTCLASSID_CIOT_DEVICEITEMRSLT       (IotCLASSID_BASECLASS + 0X00000009)
#define IOTCLASSID_CIOT_RTDEVICEDATA       (IotCLASSID_BASECLASS + 0X0000000A)
#define IOTCLASSID_CIOTTESTTASK       (IotCLASSID_EXLISTCLASS + 0X0000000B)
#define IOTCLASSID_CIOT_TESTAPPS       (IotCLASSID_EXLISTCLASS + 0X0000000C)
#define IOTCLASSID_CIOT_TESTAPP       (IotCLASSID_BASECLASS + 0X0000000D)
#define IOTCLASSID_CSYS_USER       (IotCLASSID_BASECLASS + 0X0000000E)
#define IOTCLASSID_CIOT_DEVICEHISTESTS       (IotCLASSID_EXLISTCLASS + 0X0000000F)
#define IOTCLASSID_CIOT_DEVICEHISTEST       (IotCLASSID_BASECLASS + 0X00000010)
#define IOTCLASSID_CIOT_DEVICEREPORTEXS       (IotCLASSID_EXLISTCLASS + 0X00000010)
#define IOTCLASSID_CIOT_DEVICEREPORTEX       (IotCLASSID_BASECLASS + 0X00000011)
#define IOTCLASSID_CIOT_DEVICEOUTREPORTS       (IotCLASSID_EXLISTCLASS + 0X00000011)
#define IOTCLASSID_CIOT_DEVICEOUTREPORT       (IotCLASSID_BASECLASS + 0X00000012)
#define IOTCLASSID_CIOT_DEVICEOUTREPORTEXS       (IotCLASSID_EXLISTCLASS + 0X00000012)
#define IOTCLASSID_CIOT_DEVICEOUTREPORTEX       (IotCLASSID_BASECLASS + 0X00000013)
#define IOTCLASSID_CIOT_RTDEVICEHISDATA       (IotCLASSID_BASECLASS + 0X00000014)
#define IOTCLASSID_CIOT_RTDEVICEHISDATATITLE       (IotCLASSID_BASECLASS + 0X00000015)
#define IOTCLASSID_CIOT_RTDEVICEHISDATATITLES       (IotCLASSID_EXLISTCLASS + 0X00000016)
#define IOTCLASSID_CIOT_MONITOR       (IotCLASSID_BASECLASS + 0X00000017)
#define IOTCLASSID_CIOT_WARNING       (IotCLASSID_BASECLASS + 0X00000018)
#define IOTCLASSID_CIOT_MONITORS       (IotCLASSID_EXLISTCLASS + 0X00000019)

//南瑞传感器项目新增    ——cxa 23.05.26
#define IOTCLASSID_CIOT_TEMPLATEITEMS       (IotCLASSID_EXLISTCLASS + 0X0000001A)
#define IOTCLASSID_CIOT_TEMPLATEITEM       (IotCLASSID_BASECLASS + 0X0000001B)
#define IOTCLASSID_CIOT_TYPETASK       (IotCLASSID_BASECLASS + 0X0000001C)
#define IOTCLASSID_CIOT_TYPETASKDEV       (IotCLASSID_BASECLASS + 0X0000001D)
#define IOTCLASSID_CIOT_TYPETASKDEVPARAS       (IotCLASSID_BASECLASS + 0X0000001E)
#define IOTCLASSID_CIOT_TYPETASKRTITEMS       (IotCLASSID_BASECLASS + 0X0000001F)
#define IOTCLASSID_CIOT_TYPETASKTEST       (IotCLASSID_BASECLASS + 0X00000020)
#define IOTCLASSID_CIOT_TYPETASKTESTITEM       (IotCLASSID_BASECLASS + 0X00000021)
#define IOTCLASSID_CIOT_TYPETASKTESTITEMDATAS       (IotCLASSID_BASECLASS + 0X00000022)
#define IOTCLASSID_CIOT_TYPETASKTESTAPPS       (IotCLASSID_BASECLASS + 0X00000023)
#define IOTCLASSID_CIOT_TYPETASKSTANDARD       (IotCLASSID_BASECLASS + 0X00000024)
#define IOTCLASSID_CIOT_BENCHCOMMPORT       (IotCLASSID_BASECLASS + 0X00000025)
#define IOTCLASSID_CIOT_TEMPLATE       (IotCLASSID_BASECLASS + 0X00000026)
#define IOTCLASSID_CIOT_TEMPLATEEX       (IotCLASSID_BASECLASS + 0X00000027)
#define IOTCLASSID_CIOT_RULECLASSIFY       (IotCLASSID_BASECLASS + 0X00000028)
#define IOTCLASSID_CIOT_RULEENGINECONFIG       (IotCLASSID_BASECLASS + 0X00000029)
#define IOTCLASSID_CIOT_TESTSTANDARD       (IotCLASSID_BASECLASS + 0X0000002A)
#define IOTCLASSID_CIOT_TYPETASKDEVMODEL       (IotCLASSID_BASECLASS + 0X0000002B)


#define IOTCLASSID_CIOT_BENCHS       (IotCLASSID_EXLISTCLASS + 0X0000002C)   //shaolei   2023-5-24
#define IOTCLASSID_CIOT_TYPETASKTESTS       (IotCLASSID_EXLISTCLASS + 0X0000002D)

//chenxinan   2023.06.01
#define IOTCLASSID_CIOT_ITEMS       (IotCLASSID_BASECLASS + 0X0000002E)
#define IOTCLASSID_CIOT_ITEMGEN       (IotCLASSID_BASECLASS + 0X0000002F)
#define IOTCLASSID_CIOT_TYPETASKTESTITEMGEN       (IotCLASSID_BASECLASS + 0X00000030)
#define IOTCLASSID_CIOT_TYPETASKTESTITEMGENS       (IotCLASSID_EXLISTCLASS + 0X00000031)
#define IOTCLASSID_CIOT_TYPETASKDEVMODELS       (IotCLASSID_EXLISTCLASS + 0X00000032)
#define IOTCLASSID_CIOT_TYPETASKDEVPARASES       (IotCLASSID_EXLISTCLASS + 0X00000033)
#define IOTCLASSID_CIOT_TYPETASKSTANDARDS       (IotCLASSID_EXLISTCLASS + 0X00000034)
#define IOTCLASSID_CIOT_RTDATATITLE       (IotCLASSID_EXLISTCLASS + 0X00000035)
#define IOTCLASSID_CIOT_RTDATATESTAPP       (IotCLASSID_EXLISTCLASS + 0X00000036)
#define IOTCLASSID_CIOT_RTDATADEVICE       (IotCLASSID_EXLISTCLASS + 0X00000037)

class CIot_AtsMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CIot_AtsMngrXmlRWKeys();
	virtual ~CIot_AtsMngrXmlRWKeys();
	static long g_nIotRef;

public:
	static CIot_AtsMngrXmlRWKeys* g_pXmlKeys;
	static CIot_AtsMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCIot_DeviceOutReportExKey; //iot_device_out_reportex
	BSTR m_strCIot_DeviceOutReportExsKey; //iot_device_out_reportexs
	BSTR m_strCIot_DeviceOutReportKey; //iot_device_out_report
	BSTR m_strCIot_DeviceOutReportsKey; //iot_device_out_reports
	BSTR m_strCIot_DeviceReportExKey; //iot_device_reportex
	BSTR m_strCIot_DeviceReportExsKey; //iot_device_reportexs
	BSTR m_strCIot_DeviceHisTestKey; //iot_device_histest
	BSTR m_strCIot_DeviceHisTestsKey; //iot_device_histests
	BSTR m_strCSys_UserKey; //sys_user
	BSTR m_strCIot_TestAppKey; //iot_testapp
	BSTR m_strCIot_TestAppsKey; //iot_testapps
	BSTR m_strCIotTestTaskKey; //iot_test_task
	BSTR m_strCIot_RTDeviceDataKey; //iot_rt_device_data
	BSTR m_strCIot_DeviceItemRsltKey; //iot_device_item_rslt
	BSTR m_strCIot_DeviceItemRsltsKey; //iot_device_item_rslts
	BSTR m_strCIot_DeviceModelsKey; //iot_device_models
	BSTR m_strCIot_DeviceModelKey; //iot_device_model
	BSTR m_strCIot_TestTaskDeviceKey; //iot_test_task_device
	BSTR m_strCIot_TestTaskDevicesKey; //iot_test_task_devices
	BSTR m_strCIot_BenchKey; //iot_bench
	BSTR m_strCIot_BenchsKey; //iot_benchs     //shaolei  2023-5-24
	BSTR m_strCIot_EngineKey; //iot_engine
	BSTR m_strCIot_DeviceKey; //iot_device
	BSTR m_strCIot_DevicesKey; //iot_devices
	BSTR m_strIndex_DeviceKey; //index_device
	BSTR m_strIndex_Device_ClassifyKey; //index_device_classify
	BSTR m_strIndex_Device_TypeKey; //index_device_type
	BSTR m_strIndex_FactoryKey; //index_factory
	BSTR m_strIndex_DeptKey; //index_dept
	BSTR m_strModelKey; //model
	BSTR m_strSnKey; //sn
	BSTR m_strIpKey; //ip
	BSTR m_strPortKey; //port
	BSTR m_strIndex_EngineKey; //index_engine
	BSTR m_strIndex_ModelKey; //index_model
	BSTR m_strIndex_Device_DirKey; //index_device_dir
	BSTR m_strTest_StateKey; //test_state
	BSTR m_strConnect_StateKey; //connect_state
	BSTR m_strTask_StateKey; //task_state
	BSTR m_strTask_Rpt_StateKey; //task_rpt_state
	BSTR m_strCreate_TimeKey; //create_time
	BSTR m_strIndex_FolderKey; //index_folder
	BSTR m_strEngine_IdKey; //engine_id
	BSTR m_strRule_IdKey; //rule_id
	BSTR m_strFile_NameKey; //file_name
	BSTR m_strPath_Protocol_FileKey; //path_protocol_file
	BSTR m_strComm_TypeKey; //comm_type
	BSTR m_strRemarkKey; //remark
	BSTR m_strIndex_Engine_DirKey; //index_engine_dir
	BSTR m_strIndex_BenchKey; //index_bench
	BSTR m_strCodeKey; //code
	BSTR m_strStatusKey; //status
	BSTR m_strIndex_Test_DeviceKey; //index_test_device
	BSTR m_strIndex_Test_TaskKey; //index_test_task
	BSTR m_strIndex_Model_DirKey; //index_model_dir
	BSTR m_strIndex_Item_RsltKey; //index_item_rslt
	BSTR m_strName_Item_PathKey; //name_item_path
	BSTR m_strId_Item_PathKey; //id_item_path
	BSTR m_strStateKey; //state
	BSTR m_strRsltjdgKey; //rsltjdg
	BSTR m_strRsltdscKey; //rsltdsc
	BSTR m_strFile_ReportKey; //file_report
	BSTR m_strFile_Report_SKey; //file_report_s
	BSTR m_strFile_PkgsKey; //file_pkgs
	BSTR m_strFile_Pkgs_SKey; //file_pkgs_s
	BSTR m_strSelect_StateKey; //select_state
	BSTR m_strIndex_ItemKey; //index_item
	BSTR m_strIndex_Device_DataKey; //index_device_data
	BSTR m_strData_FormatKey; //data_format
	BSTR m_strDataKey; //data
	BSTR m_strTm_UpdateKey; //tm_update
	BSTR m_strIs_WarningKey; //is_warning
	BSTR m_strIndex_TemplateKey; //index_template
	BSTR m_strTm_BeginKey; //tm_begin
	BSTR m_strTm_EndKey; //tm_end
	BSTR m_strIndex_TesterKey; //index_tester
	BSTR m_strTime_Long_Total_TestKey; //time_long_total_test
	BSTR m_strIndex_TestappKey; //index_testapp
	BSTR m_strUser_IdKey; //user_id
	BSTR m_strDept_IdKey; //dept_id
	BSTR m_strUser_NameKey; //user_name
	BSTR m_strNick_NameKey; //nick_name
	BSTR m_strPasswordKey; //password
	BSTR m_strIndex_Device_HistestKey; //index_device_histest
	BSTR m_strIndex_UserKey; //index_user
	BSTR m_strDoc_FileKey; //doc_file
	BSTR m_strDoc_File_SKey; //doc_file_s
	BSTR m_strPdf_FileKey; //pdf_file
	BSTR m_strPdf_File_SKey; //pdf_file_s
	BSTR m_strGbrpt_FileKey; //gbrpt_file
	BSTR m_strGbrpt_File_SKey; //gbrpt_file_s
	BSTR m_strPcap_FileKey; //pcap_file
	BSTR m_strPcap_File_SKey; //pcap_file_s
	BSTR m_strRpt_Data_FileKey; //rpt_data_file
	BSTR m_strRpt_Data_File_SKey; //rpt_data_file_s
	BSTR m_strRpt_Data_File_FormatKey; //rpt_data_file_format
	BSTR m_strReport_ResultKey; //report_result
	BSTR m_strTest_TypeKey; //test_type
	BSTR m_strSn_DeviceKey;  //sn_device
	BSTR m_strDevice_StateKey; //devicestate
	BSTR m_strTotalItemsKey;  //totalitems
	BSTR m_strCurrItemKey;   //curritem;
	BSTR m_strTotalTimeKey;  //totaltime
	BSTR m_strRemainTimeKey;  //remaintime
	BSTR m_strTestRsltKey;  //test_rslt
	BSTR m_strIndexRptExKey;  //index_rptex
	BSTR m_strIndexRptKey;  //index_rpt
	BSTR m_strTotalItemsProtocolKey;  //totalitems_protocol
	BSTR m_strTotalItemsFunctionKey;  //totalitems_function

	BSTR m_strCIot_RTDeviceHisDataKey; //iot_rt_device_his_data
	BSTR m_strIndex_His_DataKey; //index_his_data
	BSTR m_strValue1Key;   //value1
	BSTR m_strValue2Key;   //value2
	BSTR m_strValue3Key;   //value3
	BSTR m_strValue4Key;   //value4
	BSTR m_strValue5Key;   //value5
	BSTR m_strValue6Key;   //value6
	BSTR m_strValue7Key;   //value7
	BSTR m_strValue8Key;   //value8
	BSTR m_strValue9Key;   //value9
	BSTR m_strValue10Key;   //value10
	BSTR m_strCIot_RTDeviceHisDataTitleKey;  //iot_rt_device_his_data_title
	BSTR m_strCIot_RTDeviceHisDataTitlesKey;  //iot_rt_device_his_data_titles
	BSTR m_strIndex_His_Data_TitleKey; //index_his_data_title
	BSTR m_strDataNameKey;  //data_name
	BSTR m_strDataIdKey;   //data_id
	BSTR m_strCIot_MonitorKey;  //iot_monitor
	BSTR m_strCIot_MonitorsKey;  //iot_monitors
	BSTR m_strIndex_Monitor_DataKey;  //index_monitor_data
	BSTR m_strValueKey;   //value
	BSTR m_strUnitKey;   //unit
	BSTR m_strCIot_WarningKey;   //iot_warning
	BSTR m_strIndex_WarningKey;  //index_warning
	BSTR m_strTm_WarningKey; //tm_warning
	BSTR m_strVal_WarningKey;   //val_warning
	BSTR m_strEventKey;   //event
	BSTR m_strDeviceTypeKey;  //device_type
	BSTR m_strUseDaysKey; //use_days
	BSTR m_strUseDaysAllKey;   //use_days_all
	BSTR m_strUseCountsKey;   //use_counts
	BSTR m_strIsUpdateKey;  //isupdate

	BSTR m_strIndex_SubDeptKey; //index_dept

	//南瑞传感器项目新增    ——cxa 23.05.26
	BSTR m_strCIot_TestStandardKey; //iot_test_standard
	BSTR m_strCIot_RuleEngineConfigKey; //iot_rule_engine_config
	BSTR m_strCIot_RuleClassifyKey; //iot_rule_classify
	BSTR m_strCIot_TemplateExKey; //iot_template_ex
	BSTR m_strCIot_TemplateKey; //iot_template
	BSTR m_strCIot_BenchCommPortKey; //iot_bench_comm_port
	BSTR m_strCIot_TypeTaskStandardKey; //iot_type_task_standard
	BSTR m_strCIot_TypeTaskStandardsKey; //iot_type_task_standards
	BSTR m_strCIot_TypeTaskTestAppsKey; //iot_type_task_test_apps
	BSTR m_strCIot_TypeTaskTestItemDatasKey; //iot_type_task_test_item_datas
	BSTR m_strCIot_TypeTaskTestItemKey; //iot_type_task_test_item
	BSTR m_strCIot_TypeTaskTestKey; //iot_type_task_test
	BSTR m_strCIot_TypeTaskTestsKey; //iot_type_task_tests
	BSTR m_strCIot_TypeTaskRtItemsKey; //iot_type_task_rt_items
	BSTR m_strCIot_TypeTaskDevParasKey; //iot_type_task_dev_paras
	BSTR m_strCIot_TypeTaskDevParasesKey; //iot_type_task_dev_parases
	BSTR m_strCIot_TypeTaskDevModelKey; //iot_type_task_dev_model
	BSTR m_strCIot_TypeTaskDevModelsKey; //iot_type_task_dev_models
	BSTR m_strCIot_TypeTaskDevKey; //iot_type_task_dev
	BSTR m_strCIot_TypeTaskKey; //iot_type_task
	BSTR m_strCIot_TemplateItemKey; //iot_template_item
	BSTR m_strCIot_TemplateItemsKey; //iot_template_items
	BSTR m_strIndex_ItemsKey; //index_items
	BSTR m_strnIdKey;   //id;   //以前有些表，是id作为主键，数据类型是long
	BSTR m_strTypeKey; //type
	BSTR m_strIndex_TaskKey; //index_task
	BSTR m_strId_UserKey; //id_user
	BSTR m_strState_CreateKey; //state_create
	BSTR m_strSn_SampleKey; //sn_sample
	BSTR m_strName_SampleKey; //name_sample
	BSTR m_strModel_SampleKey; //model_sample
	BSTR m_strCnt_SampleKey; //cnt_sample
	BSTR m_strName_ClientKey; //name_client
	BSTR m_strName_ManufactorKey; //name_manufactor
	BSTR m_strAddress_ClientKey; //address_client
	BSTR m_strAddress_ManufactorKey; //address_manufactor
	BSTR m_strName_TemplateKey; //name_template
	BSTR m_strPic_FileKey; //pic_file
	BSTR m_strPic_File_SKey; //pic_file_s
	BSTR m_strTask_FileKey; //task_file
	BSTR m_strTask_File_SKey; //task_file_s
	BSTR m_strDvm_FileKey; //dvm_file
	BSTR m_strDvm_File_SKey; //dvm_file_s
	BSTR m_strId_MaininspectionKey; //id_maininspection
	BSTR m_strId_CheckerKey; //id_checker
	BSTR m_strId_ProofreaderKey; //id_proofreader
	BSTR m_strInspection_TypeKey; //inspection_type
	BSTR m_strIndex_DevKey; //index_dev
	BSTR m_strSn_Sample_DevKey; //sn_sample_dev
	BSTR m_strNumber_Sample_DevKey; //number_sample_dev
	BSTR m_strIndex_ParasKey; //index_paras
	BSTR m_strId_DevKey; //id_dev
	BSTR m_strData_TypeKey; //data_type
	BSTR m_strIndex_DataKey; //index_data
	BSTR m_strCnt_Test_RecordKey; //cnt_test_record
	BSTR m_strIndex_TestKey; //index_test
	BSTR m_strSn_ItemsKey; //sn_items
	BSTR m_strRpt_FileKey; //rpt_file
	BSTR m_strRpt_File_SKey; //rpt_file_s
	BSTR m_strFinal_ReportKey; //final_report
	BSTR m_strTime_Test_StartKey; //time_test_start
	BSTR m_strTime_Test_EndKey; //time_test_end
	BSTR m_strTm_TestKey; //tm_test
	BSTR m_strTempretureKey; //tempreture
	BSTR m_strHumidityKey; //humidity
	BSTR m_strType_ItemKey; //type_item
	BSTR m_strIndex_Item_DataKey; //index_item_data
	BSTR m_strIndex_Test_RecordKey; //index_test_record
	BSTR m_strIndex_SampleKey; //index_sample
	BSTR m_strSn_TestappKey; //sn_testapp
	BSTR m_strName_TestappKey; //name_testapp
	BSTR m_strStandard_NameKey; //standard_name
	BSTR m_strIndex_CommKey; //index_comm
	BSTR m_strIndex_Template_DirKey; //index_template_dir
	BSTR m_strTemplate_FileKey; //template_file
	BSTR m_strProtocol_FileKey; //protocol_file
	BSTR m_strIecfg_FileKey; //iecfg_file
	BSTR m_strGbxml_FileKey; //gbxml_file
	BSTR m_strXml_FileKey; //xml_file
	BSTR m_strUpload_TimeKey; //upload_time
	BSTR m_strCnt_File_Doc_ExKey; //cnt_file_doc_ex
	BSTR m_strVersionKey; //version
	BSTR m_strSvr_Relate_PathKey; //svr_relate_path
	BSTR m_strIndex_Template_ExKey; //index_template_ex
	BSTR m_strDoc_RptfileKey; //doc_rptfile
	BSTR m_strDoc_Rptfile_SKey; //doc_rptfile_s
	BSTR m_strDevice_Classify_IdKey; //device_classify_id
	BSTR m_strSuffix_FileKey; //suffix_file
	BSTR m_strDataUnitKey; //data_unit
	BSTR m_strName_Template_FileKey; //name_template_file
	
	//chenxinan 23.06.01
	BSTR m_strCIot_TypeTaskTestItemGenKey; //iot_type_task_test_item_gen
	BSTR m_strCIot_TypeTaskTestItemGensKey; //iot_type_task_test_item_gens
	BSTR m_strCIot_ItemGenKey; //iot_item_gen
	BSTR m_strCIot_ItemsKey; //iot_items
	BSTR m_strItem_Gen_FileKey; //item_gen_file
	BSTR m_strItem_Gen_File_SKey; //item_gen_file_s
	BSTR m_strIndex_GenKey; //index_gen
	BSTR m_strId_ItemsKey; //id_items
	BSTR m_strPara1_NameKey; //para1_name
	BSTR m_strPara1_IdKey; //para1_id
	BSTR m_strPara1_ValueKey; //para1_value
	BSTR m_strPara2_NameKey; //para2_name
	BSTR m_strPara2_IdKey; //para2_id
	BSTR m_strPara2_ValueKey; //para2_value
	BSTR m_strPara3_NameKey; //para3_name
	BSTR m_strPara3_IdKey; //para3_id
	BSTR m_strPara3_ValueKey; //para3_value
	BSTR m_strPara4_NameKey; //para4_name
	BSTR m_strPara4_IdKey; //para4_id
	BSTR m_strPara4_ValueKey; //para4_value
	BSTR m_strSelectKey;  //select
	
	//chenxinan 23.06.30
	BSTR m_strCIot_RtDataDeviceKey; //iot_rt_data_device
	BSTR m_strCIot_RtDataTestAppKey; //iot_rt_data_testapp
	BSTR m_strCIot_RtDataTitleKey; //iot_rt_data_title
	BSTR m_strIndex_Data_DefinitionKey; //index_data_definition
	BSTR m_strName_DataKey; //name_data
	BSTR m_strUnit_DataKey; //unit_data
	BSTR m_strIndex_Testapp_DataKey; //index_testapp_data
	BSTR m_strTimeKey; //time
	BSTR m_strIndex_Data1Key; //index_data1
	BSTR m_strValue_Data1Key; //value_data1
	BSTR m_strIndex_Data2Key; //index_data2
	BSTR m_strValue_Data2Key; //value_data2
	BSTR m_strIndex_Data3Key; //index_data3
	BSTR m_strValue_Data3Key; //value_data3
	BSTR m_strIndex_Data4Key; //index_data4
	BSTR m_strValue_Data4Key; //value_data4
	BSTR m_strIndex_Data5Key; //index_data5
	BSTR m_strValue_Data5Key; //value_data5
	BSTR m_strIndex_Data6Key; //index_data6
	BSTR m_strValue_Data6Key; //value_data6
	BSTR m_strIndex_Data7Key; //index_data7
	BSTR m_strValue_Data7Key; //value_data7
	BSTR m_strIndex_Data8Key; //index_data8
	BSTR m_strValue_Data8Key; //value_data8
	BSTR m_strIndex_Data9Key; //index_data9
	BSTR m_strValue_Data9Key; //value_data9
	BSTR m_strIndex_Data10Key; //index_data10
	BSTR m_strValue_Data10Key; //value_data10
	BSTR m_strIndex_Data11Key; //index_data11
	BSTR m_strValue_Data11Key; //value_data11
	BSTR m_strIndex_Data12Key; //index_data12
	BSTR m_strValue_Data12Key; //value_data12
	BSTR m_strIndex_Data13Key; //index_data13
	BSTR m_strValue_Data13Key; //value_data13
	BSTR m_strIndex_Data14Key; //index_data14
	BSTR m_strValue_Data14Key; //value_data14
	BSTR m_strIndex_Data15Key; //index_data15
	BSTR m_strValue_Data15Key; //value_data15
	BSTR m_strIndex_Data16Key; //index_data16
	BSTR m_strValue_Data16Key; //value_data16
	BSTR m_strIndex_Data17Key; //index_data17
	BSTR m_strValue_Data17Key; //value_data17
	BSTR m_strIndex_Data18Key; //index_data18
	BSTR m_strValue_Data18Key; //value_data18
	BSTR m_strIndex_Data19Key; //index_data19
	BSTR m_strValue_Data19Key; //value_data19
	BSTR m_strIndex_Data20Key; //index_data20
	BSTR m_strValue_Data20Key; //value_data20
	BSTR m_strIndex_Sample_DataKey; //index_sample_data
	BSTR m_strIndex_Data21Key; //index_data21
	BSTR m_strValue_Data21Key; //value_data21
	BSTR m_strIndex_Data22Key; //index_data22
	BSTR m_strValue_Data22Key; //value_data22
	BSTR m_strIndex_Data23Key; //index_data23
	BSTR m_strValue_Data23Key; //value_data23
	BSTR m_strIndex_Data24Key; //index_data24
	BSTR m_strValue_Data24Key; //value_data24
	BSTR m_strIndex_Data25Key; //index_data25
	BSTR m_strValue_Data25Key; //value_data25
	BSTR m_strIndex_Data26Key; //index_data26
	BSTR m_strValue_Data26Key; //value_data26
	BSTR m_strIndex_Data27Key; //index_data27
	BSTR m_strValue_Data27Key; //value_data27
	BSTR m_strIndex_Data28Key; //index_data28
	BSTR m_strValue_Data28Key; //value_data28
	BSTR m_strIndex_Data29Key; //index_data29
	BSTR m_strValue_Data29Key; //value_data29
	BSTR m_strIndex_Data30Key; //index_data30
	BSTR m_strValue_Data30Key; //value_data30

public:
	static BSTR CIot_DeviceOutReportExKey()  {   return g_pXmlKeys->m_strCIot_DeviceOutReportExKey;  }
	static BSTR CIot_DeviceOutReportExsKey()  {   return g_pXmlKeys->m_strCIot_DeviceOutReportExsKey;  }
	static BSTR CIot_DeviceOutReportKey()  {   return g_pXmlKeys->m_strCIot_DeviceOutReportKey;  }
	static BSTR CIot_DeviceOutReportsKey()  {   return g_pXmlKeys->m_strCIot_DeviceOutReportsKey;  }
	static BSTR CIot_DeviceReportExKey()  {   return g_pXmlKeys->m_strCIot_DeviceReportExKey;  }
	static BSTR CIot_DeviceReportExsKey()  {   return g_pXmlKeys->m_strCIot_DeviceReportExsKey;  }
	static BSTR CIot_DeviceHisTestKey()  {   return g_pXmlKeys->m_strCIot_DeviceHisTestKey;  }
	static BSTR CIot_DeviceHisTestsKey()  {   return g_pXmlKeys->m_strCIot_DeviceHisTestsKey;  }
	static BSTR CSys_UserKey()  {   return g_pXmlKeys->m_strCSys_UserKey;  }
	static BSTR CIot_TestAppKey()  {   return g_pXmlKeys->m_strCIot_TestAppKey;  }
	static BSTR CIot_TestAppsKey()  {   return g_pXmlKeys->m_strCIot_TestAppsKey;  }
	static BSTR CIotTestTaskKey()  {   return g_pXmlKeys->m_strCIotTestTaskKey;  }
	static BSTR CIot_RTDeviceDataKey()  {   return g_pXmlKeys->m_strCIot_RTDeviceDataKey;  }
	static BSTR CIot_DeviceItemRsltKey()  {   return g_pXmlKeys->m_strCIot_DeviceItemRsltKey;  }
	static BSTR CIot_DeviceItemRsltsKey()  {   return g_pXmlKeys->m_strCIot_DeviceItemRsltsKey;  }
	static BSTR CIot_DeviceModelsKey()  {   return g_pXmlKeys->m_strCIot_DeviceModelsKey;  }
	static BSTR CIot_DeviceModelKey()  {   return g_pXmlKeys->m_strCIot_DeviceModelKey;  }
	static BSTR CIot_TestTaskDeviceKey()  {   return g_pXmlKeys->m_strCIot_TestTaskDeviceKey;  }
	static BSTR CIot_TestTaskDevicesKey()  {   return g_pXmlKeys->m_strCIot_TestTaskDevicesKey;  }
	static BSTR CIot_BenchKey()  {   return g_pXmlKeys->m_strCIot_BenchKey;  }
	static BSTR CIot_BenchsKey()  {   return g_pXmlKeys->m_strCIot_BenchsKey;  }   //shaolei  2023-5-24
	static BSTR CIot_EngineKey()  {   return g_pXmlKeys->m_strCIot_EngineKey;  }
	static BSTR CIot_DeviceKey()  {   return g_pXmlKeys->m_strCIot_DeviceKey;  }
	static BSTR CIot_DevicesKey()  {   return g_pXmlKeys->m_strCIot_DevicesKey;  }
	static BSTR Index_DeviceKey()  {   return g_pXmlKeys->m_strIndex_DeviceKey;  }
	static BSTR Index_Device_ClassifyKey()  {   return g_pXmlKeys->m_strIndex_Device_ClassifyKey;  }
	static BSTR Index_Device_TypeKey()  {   return g_pXmlKeys->m_strIndex_Device_TypeKey;  }
	static BSTR Index_FactoryKey()  {   return g_pXmlKeys->m_strIndex_FactoryKey;  }
	static BSTR Index_DeptKey()  {   return g_pXmlKeys->m_strIndex_DeptKey;  }
	static BSTR ModelKey()  {   return g_pXmlKeys->m_strModelKey;  }
	static BSTR SnKey()  {   return g_pXmlKeys->m_strSnKey;  }
	static BSTR IpKey()  {   return g_pXmlKeys->m_strIpKey;  }
	static BSTR PortKey()  {   return g_pXmlKeys->m_strPortKey;  }
	static BSTR Index_EngineKey()  {   return g_pXmlKeys->m_strIndex_EngineKey;  }
	static BSTR Index_ModelKey()  {   return g_pXmlKeys->m_strIndex_ModelKey;  }
	static BSTR Index_Device_DirKey()  {   return g_pXmlKeys->m_strIndex_Device_DirKey;  }
	static BSTR Test_StateKey()  {   return g_pXmlKeys->m_strTest_StateKey;  }
	static BSTR Connect_StateKey()  {   return g_pXmlKeys->m_strConnect_StateKey;  }
	static BSTR Task_StateKey()  {   return g_pXmlKeys->m_strTask_StateKey;  }
	static BSTR Task_Rpt_StateKey()  {   return g_pXmlKeys->m_strTask_Rpt_StateKey;  }
	static BSTR Create_TimeKey()  {   return g_pXmlKeys->m_strCreate_TimeKey;  }
	static BSTR Index_FolderKey()  {   return g_pXmlKeys->m_strIndex_FolderKey;  }
	static BSTR Engine_IdKey()  {   return g_pXmlKeys->m_strEngine_IdKey;  }
	static BSTR Rule_IdKey()  {   return g_pXmlKeys->m_strRule_IdKey;  }
	static BSTR File_NameKey()  {   return g_pXmlKeys->m_strFile_NameKey;  }
	static BSTR Path_Protocol_FileKey()  {   return g_pXmlKeys->m_strPath_Protocol_FileKey;  }
	static BSTR Comm_TypeKey()  {   return g_pXmlKeys->m_strComm_TypeKey;  }
	static BSTR RemarkKey()  {   return g_pXmlKeys->m_strRemarkKey;  }
	static BSTR Index_Engine_DirKey()  {   return g_pXmlKeys->m_strIndex_Engine_DirKey;  }
	static BSTR Index_BenchKey()  {   return g_pXmlKeys->m_strIndex_BenchKey;  }
	static BSTR CodeKey()  {   return g_pXmlKeys->m_strCodeKey;  }
	static BSTR StatusKey()  {   return g_pXmlKeys->m_strStatusKey;  }
	static BSTR Index_Test_DeviceKey()  {   return g_pXmlKeys->m_strIndex_Test_DeviceKey;  }
	static BSTR Index_Test_TaskKey()  {   return g_pXmlKeys->m_strIndex_Test_TaskKey;  }
	static BSTR Index_Model_DirKey()  {   return g_pXmlKeys->m_strIndex_Model_DirKey;  }
	static BSTR Index_Item_RsltKey()  {   return g_pXmlKeys->m_strIndex_Item_RsltKey;  }
	static BSTR Name_Item_PathKey()  {   return g_pXmlKeys->m_strName_Item_PathKey;  }
	static BSTR Id_Item_PathKey()  {   return g_pXmlKeys->m_strId_Item_PathKey;  }
	static BSTR StateKey()  {   return g_pXmlKeys->m_strStateKey;  }
	static BSTR RsltjdgKey()  {   return g_pXmlKeys->m_strRsltjdgKey;  }
	static BSTR RsltdscKey()  {   return g_pXmlKeys->m_strRsltdscKey;  }
	static BSTR File_ReportKey()  {   return g_pXmlKeys->m_strFile_ReportKey;  }
	static BSTR File_Report_SKey()  {   return g_pXmlKeys->m_strFile_Report_SKey;  }
	static BSTR File_PkgsKey()  {   return g_pXmlKeys->m_strFile_PkgsKey;  }
	static BSTR File_Pkgs_SKey()  {   return g_pXmlKeys->m_strFile_Pkgs_SKey;  }
	static BSTR Select_StateKey()  {   return g_pXmlKeys->m_strSelect_StateKey;  }
	static BSTR Index_ItemKey()  {   return g_pXmlKeys->m_strIndex_ItemKey;  }
	static BSTR Index_Device_DataKey()  {   return g_pXmlKeys->m_strIndex_Device_DataKey;  }
	static BSTR Data_FormatKey()  {   return g_pXmlKeys->m_strData_FormatKey;  }
	static BSTR DataKey()  {   return g_pXmlKeys->m_strDataKey;  }
	static BSTR Tm_UpdateKey()  {   return g_pXmlKeys->m_strTm_UpdateKey;  }
	static BSTR Is_WarningKey()  {   return g_pXmlKeys->m_strIs_WarningKey;  }
	static BSTR Index_TemplateKey()  {   return g_pXmlKeys->m_strIndex_TemplateKey;  }
	static BSTR Tm_BeginKey()  {   return g_pXmlKeys->m_strTm_BeginKey;  }
	static BSTR Tm_EndKey()  {   return g_pXmlKeys->m_strTm_EndKey;  }
	static BSTR Index_TesterKey()  {   return g_pXmlKeys->m_strIndex_TesterKey;  }
	static BSTR Time_Long_Total_TestKey()  {   return g_pXmlKeys->m_strTime_Long_Total_TestKey;  }
	static BSTR Index_TestappKey()  {   return g_pXmlKeys->m_strIndex_TestappKey;  }
	static BSTR User_IdKey()  {   return g_pXmlKeys->m_strUser_IdKey;  }
	static BSTR Dept_IdKey()  {   return g_pXmlKeys->m_strDept_IdKey;  }
	static BSTR User_NameKey()  {   return g_pXmlKeys->m_strUser_NameKey;  }
	static BSTR Nick_NameKey()  {   return g_pXmlKeys->m_strNick_NameKey;  }
	static BSTR PasswordKey()  {   return g_pXmlKeys->m_strPasswordKey;  }
	static BSTR Index_Device_HistestKey()  {   return g_pXmlKeys->m_strIndex_Device_HistestKey;  }
	static BSTR Index_UserKey()  {   return g_pXmlKeys->m_strIndex_UserKey;  }
	static BSTR Doc_FileKey()  {   return g_pXmlKeys->m_strDoc_FileKey;  }
	static BSTR Doc_File_SKey()  {   return g_pXmlKeys->m_strDoc_File_SKey;  }
	static BSTR Pdf_FileKey()  {   return g_pXmlKeys->m_strPdf_FileKey;  }
	static BSTR Pdf_File_SKey()  {   return g_pXmlKeys->m_strPdf_File_SKey;  }
	static BSTR Gbrpt_FileKey()  {   return g_pXmlKeys->m_strGbrpt_FileKey;  }
	static BSTR Gbrpt_File_SKey()  {   return g_pXmlKeys->m_strGbrpt_File_SKey;  }
	static BSTR Pcap_FileKey()  {   return g_pXmlKeys->m_strPcap_FileKey;  }
	static BSTR Pcap_File_SKey()  {   return g_pXmlKeys->m_strPcap_File_SKey;  }
	static BSTR Rpt_Data_FileKey()  {   return g_pXmlKeys->m_strRpt_Data_FileKey;  }
	static BSTR Rpt_Data_File_SKey()  {   return g_pXmlKeys->m_strRpt_Data_File_SKey;  }
	static BSTR Rpt_Data_File_FormatKey()  {   return g_pXmlKeys->m_strRpt_Data_File_FormatKey;  }
	static BSTR Report_ResultKey()  {   return g_pXmlKeys->m_strReport_ResultKey;  }
	static BSTR Test_TypeKey()  {   return g_pXmlKeys->m_strTest_TypeKey;  }
	static BSTR Sn_DeviceKey()  {   return g_pXmlKeys->m_strSn_DeviceKey;  }
	static BSTR Device_StateKey()  {   return g_pXmlKeys->m_strDevice_StateKey;  }
	static BSTR TotalItemsKey()  {   return g_pXmlKeys->m_strTotalItemsKey;  }
	static BSTR CurrItemKey()  {   return g_pXmlKeys->m_strCurrItemKey;  }
	static BSTR TotalTimeKey()  {   return g_pXmlKeys->m_strTotalTimeKey;  }
	static BSTR RemainTimeKey()  {   return g_pXmlKeys->m_strRemainTimeKey;  }
	static BSTR TestRsltKey()  {   return g_pXmlKeys->m_strTestRsltKey;  }
	static BSTR IndexRptExKey()  {   return g_pXmlKeys->m_strIndexRptExKey;  }
	static BSTR IndexRptKey()  {   return g_pXmlKeys->m_strIndexRptKey;  }
	static BSTR TotalItemsProtocolKey()  {   return g_pXmlKeys->m_strTotalItemsProtocolKey;  }
	static BSTR TotalItemsFunctionKey()  {   return g_pXmlKeys->m_strTotalItemsFunctionKey;  }

	static BSTR CIot_RTDeviceHisDataKey()  {   return g_pXmlKeys->m_strCIot_RTDeviceHisDataKey;  }
	static BSTR Index_His_DataKey()  {   return g_pXmlKeys->m_strIndex_His_DataKey;  }
	static BSTR Value1Key()  {   return g_pXmlKeys->m_strValue1Key;  }
	static BSTR Value2Key()  {   return g_pXmlKeys->m_strValue2Key;  }
	static BSTR Value3Key()  {   return g_pXmlKeys->m_strValue3Key;  }
	static BSTR Value4Key()  {   return g_pXmlKeys->m_strValue4Key;  }
	static BSTR Value5Key()  {   return g_pXmlKeys->m_strValue5Key;  }
	static BSTR Value6Key()  {   return g_pXmlKeys->m_strValue6Key;  }
	static BSTR Value7Key()  {   return g_pXmlKeys->m_strValue7Key;  }
	static BSTR Value8Key()  {   return g_pXmlKeys->m_strValue8Key;  }
	static BSTR Value9Key()  {   return g_pXmlKeys->m_strValue9Key;  }
	static BSTR Value10Key()  {   return g_pXmlKeys->m_strValue10Key;  }
	static BSTR CIot_RTDeviceHisDataTitlesKey()	{	return g_pXmlKeys->m_strCIot_RTDeviceHisDataTitlesKey;	}
	static BSTR CIot_RTDeviceHisDataTitleKey()	{	return g_pXmlKeys->m_strCIot_RTDeviceHisDataTitleKey;	}
	static BSTR Index_His_Data_TitleKey()  {   return g_pXmlKeys->m_strIndex_His_Data_TitleKey;  }
	static BSTR CDataNameKey()	{	return g_pXmlKeys->m_strDataNameKey;	}
	static BSTR CDataIdKey()	{	return g_pXmlKeys->m_strDataIdKey;	}
	static BSTR CIot_MonitorKey()	{	return g_pXmlKeys->m_strCIot_MonitorKey;	}
	static BSTR CIot_MonitorsKey()  {   return g_pXmlKeys->m_strCIot_MonitorsKey;  }
	static BSTR Index_Monitor_Data_Key()	{	return g_pXmlKeys->m_strIndex_Monitor_DataKey;	}
	static BSTR ValueKey()	{	return g_pXmlKeys->m_strValueKey;	}
	static BSTR UnitKey()	{	return g_pXmlKeys->m_strUnitKey;	}
	static BSTR CIot_WarningKey()	{	return g_pXmlKeys->m_strCIot_WarningKey;	}
	static BSTR Index_WarningKey()	{	return g_pXmlKeys->m_strIndex_WarningKey;	}
	static BSTR Tm_WarningKey()	{	return g_pXmlKeys->m_strTm_WarningKey;	}
	static BSTR Val_WarningKey()	{	return g_pXmlKeys->m_strVal_WarningKey;	}
	static BSTR EventKey()	{	return g_pXmlKeys->m_strEventKey;	}
	static BSTR Device_TypeKey()	{	return g_pXmlKeys->m_strDeviceTypeKey;	}
	static BSTR UseDaysKey()	{	return g_pXmlKeys->m_strUseDaysKey;	}
	static BSTR UseDaysAllKey()	{	return g_pXmlKeys->m_strUseDaysAllKey;	}
	static BSTR UseCountsKey()	{	return g_pXmlKeys->m_strUseCountsKey;	}
	static BSTR IsUpdateKey()	{	return g_pXmlKeys->m_strIsUpdateKey;	}
	
	static BSTR IndexSubDeptKey()	{	return g_pXmlKeys->m_strIndex_SubDeptKey;	}
	
	//南瑞传感器项目新增    ——cxa 23.05.26
	static BSTR CIot_TestStandardKey()  {   return g_pXmlKeys->m_strCIot_TestStandardKey;  }
	static BSTR CIot_RuleEngineConfigKey()  {   return g_pXmlKeys->m_strCIot_RuleEngineConfigKey;  }
	static BSTR CIot_RuleClassifyKey()  {   return g_pXmlKeys->m_strCIot_RuleClassifyKey;  }
	static BSTR CIot_TemplateExKey()  {   return g_pXmlKeys->m_strCIot_TemplateExKey;  }
	static BSTR CIot_TemplateKey()  {   return g_pXmlKeys->m_strCIot_TemplateKey;  }
	static BSTR CIot_BenchCommPortKey()  {   return g_pXmlKeys->m_strCIot_BenchCommPortKey;  }
	static BSTR CIot_TypeTaskStandardKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskStandardKey;  }
	static BSTR CIot_TypeTaskStandardsKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskStandardsKey;  }
	static BSTR CIot_TypeTaskTestAppsKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskTestAppsKey;  }
	static BSTR CIot_TypeTaskTestItemDatasKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskTestItemDatasKey;  }
	static BSTR CIot_TypeTaskTestItemKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskTestItemKey;  }
	static BSTR CIot_TypeTaskTestKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskTestKey;  }
	static BSTR CIot_TypeTaskTestsKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskTestsKey;  }
	static BSTR CIot_TypeTaskRtItemsKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskRtItemsKey;  }
	static BSTR CIot_TypeTaskDevParasKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskDevParasKey;  }
	static BSTR CIot_TypeTaskDevParasesKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskDevParasesKey;  }
	static BSTR CIot_TypeTaskDevModelKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskDevModelKey;  }
	static BSTR CIot_TypeTaskDevModelsKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskDevModelsKey;  }
	static BSTR CIot_TypeTaskDevKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskDevKey;  }
	static BSTR CIot_TypeTaskKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskKey;  }
	static BSTR CIot_TemplateItemKey()  {   return g_pXmlKeys->m_strCIot_TemplateItemKey;  }
	static BSTR CIot_TemplateItemsKey()  {   return g_pXmlKeys->m_strCIot_TemplateItemsKey;  }
	static BSTR Index_ItemsKey()  {   return g_pXmlKeys->m_strIndex_ItemsKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR Index_TaskKey()  {   return g_pXmlKeys->m_strIndex_TaskKey;  }
	static BSTR Id_UserKey()  {   return g_pXmlKeys->m_strId_UserKey;  }
	static BSTR State_CreateKey()  {   return g_pXmlKeys->m_strState_CreateKey;  }
	static BSTR Sn_SampleKey()  {   return g_pXmlKeys->m_strSn_SampleKey;  }
	static BSTR Name_SampleKey()  {   return g_pXmlKeys->m_strName_SampleKey;  }
	static BSTR Model_SampleKey()  {   return g_pXmlKeys->m_strModel_SampleKey;  }
	static BSTR Cnt_SampleKey()  {   return g_pXmlKeys->m_strCnt_SampleKey;  }
	static BSTR Name_ClientKey()  {   return g_pXmlKeys->m_strName_ClientKey;  }
	static BSTR Name_ManufactorKey()  {   return g_pXmlKeys->m_strName_ManufactorKey;  }
	static BSTR Address_ClientKey()  {   return g_pXmlKeys->m_strAddress_ClientKey;  }
	static BSTR Address_ManufactorKey()  {   return g_pXmlKeys->m_strAddress_ManufactorKey;  }
	static BSTR Name_TemplateKey()  {   return g_pXmlKeys->m_strName_TemplateKey;  }
	static BSTR Pic_FileKey()  {   return g_pXmlKeys->m_strPic_FileKey;  }
	static BSTR Pic_File_SKey()  {   return g_pXmlKeys->m_strPic_File_SKey;  }
	static BSTR Task_FileKey()  {   return g_pXmlKeys->m_strTask_FileKey;  }
	static BSTR Task_File_SKey()  {   return g_pXmlKeys->m_strTask_File_SKey;  }
	static BSTR Dvm_FileKey()  {   return g_pXmlKeys->m_strDvm_FileKey;  }
	static BSTR Dvm_File_SKey()  {   return g_pXmlKeys->m_strDvm_File_SKey;  }
	static BSTR Id_MaininspectionKey()  {   return g_pXmlKeys->m_strId_MaininspectionKey;  }
	static BSTR Id_CheckerKey()  {   return g_pXmlKeys->m_strId_CheckerKey;  }
	static BSTR Id_ProofreaderKey()  {   return g_pXmlKeys->m_strId_ProofreaderKey;  }
	static BSTR Inspection_TypeKey()  {   return g_pXmlKeys->m_strInspection_TypeKey;  }
	static BSTR Index_DevKey()  {   return g_pXmlKeys->m_strIndex_DevKey;  }
	static BSTR Sn_Sample_DevKey()  {   return g_pXmlKeys->m_strSn_Sample_DevKey;  }
	static BSTR Number_Sample_DevKey()  {   return g_pXmlKeys->m_strNumber_Sample_DevKey;  }
	static BSTR Index_ParasKey()  {   return g_pXmlKeys->m_strIndex_ParasKey;  }
	static BSTR Id_DevKey()  {   return g_pXmlKeys->m_strId_DevKey;  }
	static BSTR Data_TypeKey()  {   return g_pXmlKeys->m_strData_TypeKey;  }
	static BSTR Index_DataKey()  {   return g_pXmlKeys->m_strIndex_DataKey;  }
	static BSTR Cnt_Test_RecordKey()  {   return g_pXmlKeys->m_strCnt_Test_RecordKey;  }
	static BSTR Index_TestKey()  {   return g_pXmlKeys->m_strIndex_TestKey;  }
	static BSTR Sn_ItemsKey()  {   return g_pXmlKeys->m_strSn_ItemsKey;  }
	static BSTR Rpt_FileKey()  {   return g_pXmlKeys->m_strRpt_FileKey;  }
	static BSTR Rpt_File_SKey()  {   return g_pXmlKeys->m_strRpt_File_SKey;  }
	static BSTR Final_ReportKey()  {   return g_pXmlKeys->m_strFinal_ReportKey;  }
	static BSTR Time_Test_StartKey()  {   return g_pXmlKeys->m_strTime_Test_StartKey;  }
	static BSTR Time_Test_EndKey()  {   return g_pXmlKeys->m_strTime_Test_EndKey;  }
	static BSTR Tm_TestKey()  {   return g_pXmlKeys->m_strTm_TestKey;  }
	static BSTR TemperatureKey()  {   return g_pXmlKeys->m_strTempretureKey;  }
	static BSTR HumidityKey()  {   return g_pXmlKeys->m_strHumidityKey;  }
	static BSTR Type_ItemKey()  {   return g_pXmlKeys->m_strType_ItemKey;  }
	static BSTR Index_Item_DataKey()  {   return g_pXmlKeys->m_strIndex_Item_DataKey;  }
	static BSTR Index_Test_RecordKey()  {   return g_pXmlKeys->m_strIndex_Test_RecordKey;  }
	static BSTR Index_SampleKey()  {   return g_pXmlKeys->m_strIndex_SampleKey;  }
	static BSTR Sn_TestappKey()  {   return g_pXmlKeys->m_strSn_TestappKey;  }
	static BSTR Name_TestappKey()  {   return g_pXmlKeys->m_strName_TestappKey;  }
	static BSTR Standard_NameKey()  {   return g_pXmlKeys->m_strStandard_NameKey;  }
	static BSTR Index_CommKey()  {   return g_pXmlKeys->m_strIndex_CommKey;  }
	static BSTR Index_Template_DirKey()  {   return g_pXmlKeys->m_strIndex_Template_DirKey;  }
	static BSTR Template_FileKey()  {   return g_pXmlKeys->m_strTemplate_FileKey;  }
	static BSTR Protocol_FileKey()  {   return g_pXmlKeys->m_strProtocol_FileKey;  }
	static BSTR Iecfg_FileKey()  {   return g_pXmlKeys->m_strIecfg_FileKey;  }
	static BSTR Gbxml_FileKey()  {   return g_pXmlKeys->m_strGbxml_FileKey;  }
	static BSTR Xml_FileKey()  {   return g_pXmlKeys->m_strXml_FileKey;  }
	static BSTR Upload_TimeKey()  {   return g_pXmlKeys->m_strUpload_TimeKey;  }
	static BSTR Cnt_File_Doc_ExKey()  {   return g_pXmlKeys->m_strCnt_File_Doc_ExKey;  }
	static BSTR VersionKey()  {   return g_pXmlKeys->m_strVersionKey;  }
	static BSTR Svr_Relate_PathKey()  {   return g_pXmlKeys->m_strSvr_Relate_PathKey;  }
	static BSTR Index_Template_ExKey()  {   return g_pXmlKeys->m_strIndex_Template_ExKey;  }
	static BSTR Doc_RptfileKey()  {   return g_pXmlKeys->m_strDoc_RptfileKey;  }
	static BSTR Doc_Rptfile_SKey()  {   return g_pXmlKeys->m_strDoc_Rptfile_SKey;  }
	static BSTR Device_Classify_IdKey()  {   return g_pXmlKeys->m_strDevice_Classify_IdKey;  }
	static BSTR Suffix_FileKey()  {   return g_pXmlKeys->m_strSuffix_FileKey;  }
	static BSTR DataUnitKey()  {   return g_pXmlKeys->m_strDataUnitKey;  }
	static BSTR Index_ItermsKey()  {   return g_pXmlKeys->m_strIndex_ItemsKey;  }
	static BSTR Name_Template_FileKey()  {   return g_pXmlKeys->m_strName_Template_FileKey;  }
	static BSTR nIdKey()	{	return g_pXmlKeys->m_strnIdKey;		}
	
	//chenxinan 23.06.01
	static BSTR CIot_TypeTaskTestItemGenKey()  {   return g_pXmlKeys->m_strCIot_TypeTaskTestItemGenKey;  }
	static BSTR CIot_TypeTaskTestItemGensKey()	{	return g_pXmlKeys->m_strCIot_TypeTaskTestItemGensKey;  }
	static BSTR CIot_ItemGenKey()  {   return g_pXmlKeys->m_strCIot_ItemGenKey;  }
	static BSTR CIot_ItemsKey()  {   return g_pXmlKeys->m_strCIot_ItemsKey;  }
	static BSTR Item_Gen_FileKey()  {   return g_pXmlKeys->m_strItem_Gen_FileKey;  }
	static BSTR Item_Gen_File_SKey()  {   return g_pXmlKeys->m_strItem_Gen_File_SKey;  }
	static BSTR Index_GenKey()  {   return g_pXmlKeys->m_strIndex_GenKey;  }
	static BSTR Id_ItemsKey()  {   return g_pXmlKeys->m_strId_ItemsKey;  }
	static BSTR Para1_NameKey()  {   return g_pXmlKeys->m_strPara1_NameKey;  }
	static BSTR Para1_IdKey()  {   return g_pXmlKeys->m_strPara1_IdKey;  }
	static BSTR Para1_ValueKey()  {   return g_pXmlKeys->m_strPara1_ValueKey;  }
	static BSTR Para2_NameKey()  {   return g_pXmlKeys->m_strPara2_NameKey;  }
	static BSTR Para2_IdKey()  {   return g_pXmlKeys->m_strPara2_IdKey;  }
	static BSTR Para2_ValueKey()  {   return g_pXmlKeys->m_strPara2_ValueKey;  }
	static BSTR Para3_NameKey()  {   return g_pXmlKeys->m_strPara3_NameKey;  }
	static BSTR Para3_IdKey()  {   return g_pXmlKeys->m_strPara3_IdKey;  }
	static BSTR Para3_ValueKey()  {   return g_pXmlKeys->m_strPara3_ValueKey;  }
	static BSTR Para4_NameKey()  {   return g_pXmlKeys->m_strPara4_NameKey;  }
	static BSTR Para4_IdKey()  {   return g_pXmlKeys->m_strPara4_IdKey;  }
	static BSTR Para4_ValueKey()  {   return g_pXmlKeys->m_strPara4_ValueKey;  }
	static BSTR SelectKey()  {   return g_pXmlKeys->m_strSelectKey;  }
	
	//chenxinan 23.06.30
	static BSTR CIot_RtDataDeviceKey()  {   return g_pXmlKeys->m_strCIot_RtDataDeviceKey;  }
	static BSTR CIot_RtDataTestAppKey()  {   return g_pXmlKeys->m_strCIot_RtDataTestAppKey;  }
	static BSTR CIot_RtDataTitleKey()  {   return g_pXmlKeys->m_strCIot_RtDataTitleKey;  }
	static BSTR Index_Data_DefinitionKey()  {   return g_pXmlKeys->m_strIndex_Data_DefinitionKey;  }
	static BSTR Name_DataKey()  {   return g_pXmlKeys->m_strName_DataKey;  }
	static BSTR Unit_DataKey()  {   return g_pXmlKeys->m_strUnit_DataKey;  }
	static BSTR Index_Testapp_DataKey()  {   return g_pXmlKeys->m_strIndex_Testapp_DataKey;  }
	static BSTR TimeKey()  {   return g_pXmlKeys->m_strTimeKey;  }
	static BSTR Index_Data1Key()  {   return g_pXmlKeys->m_strIndex_Data1Key;  }
	static BSTR Value_Data1Key()  {   return g_pXmlKeys->m_strValue_Data1Key;  }
	static BSTR Index_Data2Key()  {   return g_pXmlKeys->m_strIndex_Data2Key;  }
	static BSTR Value_Data2Key()  {   return g_pXmlKeys->m_strValue_Data2Key;  }
	static BSTR Index_Data3Key()  {   return g_pXmlKeys->m_strIndex_Data3Key;  }
	static BSTR Value_Data3Key()  {   return g_pXmlKeys->m_strValue_Data3Key;  }
	static BSTR Index_Data4Key()  {   return g_pXmlKeys->m_strIndex_Data4Key;  }
	static BSTR Value_Data4Key()  {   return g_pXmlKeys->m_strValue_Data4Key;  }
	static BSTR Index_Data5Key()  {   return g_pXmlKeys->m_strIndex_Data5Key;  }
	static BSTR Value_Data5Key()  {   return g_pXmlKeys->m_strValue_Data5Key;  }
	static BSTR Index_Data6Key()  {   return g_pXmlKeys->m_strIndex_Data6Key;  }
	static BSTR Value_Data6Key()  {   return g_pXmlKeys->m_strValue_Data6Key;  }
	static BSTR Index_Data7Key()  {   return g_pXmlKeys->m_strIndex_Data7Key;  }
	static BSTR Value_Data7Key()  {   return g_pXmlKeys->m_strValue_Data7Key;  }
	static BSTR Index_Data8Key()  {   return g_pXmlKeys->m_strIndex_Data8Key;  }
	static BSTR Value_Data8Key()  {   return g_pXmlKeys->m_strValue_Data8Key;  }
	static BSTR Index_Data9Key()  {   return g_pXmlKeys->m_strIndex_Data9Key;  }
	static BSTR Value_Data9Key()  {   return g_pXmlKeys->m_strValue_Data9Key;  }
	static BSTR Index_Data10Key()  {   return g_pXmlKeys->m_strIndex_Data10Key;  }
	static BSTR Value_Data10Key()  {   return g_pXmlKeys->m_strValue_Data10Key;  }
	static BSTR Index_Data11Key()  {   return g_pXmlKeys->m_strIndex_Data11Key;  }
	static BSTR Value_Data11Key()  {   return g_pXmlKeys->m_strValue_Data11Key;  }
	static BSTR Index_Data12Key()  {   return g_pXmlKeys->m_strIndex_Data12Key;  }
	static BSTR Value_Data12Key()  {   return g_pXmlKeys->m_strValue_Data12Key;  }
	static BSTR Index_Data13Key()  {   return g_pXmlKeys->m_strIndex_Data13Key;  }
	static BSTR Value_Data13Key()  {   return g_pXmlKeys->m_strValue_Data13Key;  }
	static BSTR Index_Data14Key()  {   return g_pXmlKeys->m_strIndex_Data14Key;  }
	static BSTR Value_Data14Key()  {   return g_pXmlKeys->m_strValue_Data14Key;  }
	static BSTR Index_Data15Key()  {   return g_pXmlKeys->m_strIndex_Data15Key;  }
	static BSTR Value_Data15Key()  {   return g_pXmlKeys->m_strValue_Data15Key;  }
	static BSTR Index_Data16Key()  {   return g_pXmlKeys->m_strIndex_Data16Key;  }
	static BSTR Value_Data16Key()  {   return g_pXmlKeys->m_strValue_Data16Key;  }
	static BSTR Index_Data17Key()  {   return g_pXmlKeys->m_strIndex_Data17Key;  }
	static BSTR Value_Data17Key()  {   return g_pXmlKeys->m_strValue_Data17Key;  }
	static BSTR Index_Data18Key()  {   return g_pXmlKeys->m_strIndex_Data18Key;  }
	static BSTR Value_Data18Key()  {   return g_pXmlKeys->m_strValue_Data18Key;  }
	static BSTR Index_Data19Key()  {   return g_pXmlKeys->m_strIndex_Data19Key;  }
	static BSTR Value_Data19Key()  {   return g_pXmlKeys->m_strValue_Data19Key;  }
	static BSTR Index_Data20Key()  {   return g_pXmlKeys->m_strIndex_Data20Key;  }
	static BSTR Value_Data20Key()  {   return g_pXmlKeys->m_strValue_Data20Key;  }
	static BSTR Index_Sample_DataKey()  {   return g_pXmlKeys->m_strIndex_Sample_DataKey;  }
	static BSTR Index_Data21Key()  {   return g_pXmlKeys->m_strIndex_Data21Key;  }
	static BSTR Value_Data21Key()  {   return g_pXmlKeys->m_strValue_Data21Key;  }
	static BSTR Index_Data22Key()  {   return g_pXmlKeys->m_strIndex_Data22Key;  }
	static BSTR Value_Data22Key()  {   return g_pXmlKeys->m_strValue_Data22Key;  }
	static BSTR Index_Data23Key()  {   return g_pXmlKeys->m_strIndex_Data23Key;  }
	static BSTR Value_Data23Key()  {   return g_pXmlKeys->m_strValue_Data23Key;  }
	static BSTR Index_Data24Key()  {   return g_pXmlKeys->m_strIndex_Data24Key;  }
	static BSTR Value_Data24Key()  {   return g_pXmlKeys->m_strValue_Data24Key;  }
	static BSTR Index_Data25Key()  {   return g_pXmlKeys->m_strIndex_Data25Key;  }
	static BSTR Value_Data25Key()  {   return g_pXmlKeys->m_strValue_Data25Key;  }
	static BSTR Index_Data26Key()  {   return g_pXmlKeys->m_strIndex_Data26Key;  }
	static BSTR Value_Data26Key()  {   return g_pXmlKeys->m_strValue_Data26Key;  }
	static BSTR Index_Data27Key()  {   return g_pXmlKeys->m_strIndex_Data27Key;  }
	static BSTR Value_Data27Key()  {   return g_pXmlKeys->m_strValue_Data27Key;  }
	static BSTR Index_Data28Key()  {   return g_pXmlKeys->m_strIndex_Data28Key;  }
	static BSTR Value_Data28Key()  {   return g_pXmlKeys->m_strValue_Data28Key;  }
	static BSTR Index_Data29Key()  {   return g_pXmlKeys->m_strIndex_Data29Key;  }
	static BSTR Value_Data29Key()  {   return g_pXmlKeys->m_strValue_Data29Key;  }
	static BSTR Index_Data30Key()  {   return g_pXmlKeys->m_strIndex_Data30Key;  }
	static BSTR Value_Data30Key()  {   return g_pXmlKeys->m_strValue_Data30Key;  }
};



class CIot_AtsMngrConstGlobal
{
private:
	CIot_AtsMngrConstGlobal();
	virtual ~CIot_AtsMngrConstGlobal();

public:
	static CIot_AtsMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CIot_AtsMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

//业务测试，协议一致性测试，MQTT测试
#define DEVICE_TEST_STATE_IDLE				0
#define DEVICE_TEST_STATE_SvrTesting		1		
#define DEVICE_TEST_STATE_IotTesting		2
#define DEVICE_TEST_STATE_MqttTesting		3
#define DEVICE_TEST_STATE_Standby    		4  //待机：导出报告完成，但未关闭测试

#define DEVICE_TEST_STATE_NORMAL		0   //未测试
#define DEVICE_TEST_STATE_ELIGIBLE		1	//测试合格	
#define DEVICE_TEST_STATE_INLEGIBLE  	2   //测试不合格

//测试模板大项的类型：ats（自动测试）、manual（人工测试）
#define TEMPLATE_ITEMS_TYPE_ATS      _T("ats")
#define TEMPLATE_ITEMS_TYPE_MANUAL   _T("manual")

inline long GetTestRsltByDeviceState(const CString& strDeviceState)
{
	if (strDeviceState == _T("合格"))
	{
		return DEVICE_TEST_STATE_ELIGIBLE;
	}

	if (strDeviceState == _T("不合格"))
	{
		return DEVICE_TEST_STATE_INLEGIBLE;
	}

	return DEVICE_TEST_STATE_NORMAL;
}

//测试状态：适用于测试仪（iot_testapp）、被测设备（iot_type_task_dev）
#define  DEV_TEST_STATE_NOMAL     0   //未测试
#define  DEV_TEST_STATE_TESTING   1   //测试中

//测试状态：适用于：1、测试记录（iot_type_task_test）；2、任务大项（iot_type_task_rt_items）；
//3、委托任务（任务状态，iot_type_task）；4、 测试记录子项（iot_type_task_test_item）
//0-待测试；1-测试异常；2-测试中断；3-测试中；4-测试完成-不合格；5-测试完成-合格；
#define TYPE_TASK_STATE_NORMAL       0   
#define TYPE_TASK_STATE_EXCEPTION    1
#define TYPE_TASK_STATE_TESTSTOPED   2
#define TYPE_TASK_STATE_TESTINIG     3
#define TYPE_TASK_STATE_ELIGIBLE     4
#define TYPE_TASK_STATE_INLEGIBLE    5

//任务报告状态：适用于 委托任务（iot_type_task）
#define TYPE_TASK_RPT_STATE_NORMAL     0    //未导出
#define TYPE_TASK_RPT_STATE_EXPORTED   1    //已导出

//连接状态：适用于测试仪（iot_testapp）、被测设备（iot_type_task_dev）
#define DEV_CONNECT_STATE_OFF     0   //未连接
#define DEV_CONNECT_STATE_ON      1   //已连接

//测试台状态
#define TEST_BENCH_STATE_NORMAL 0			//空闲
#define TEST_BENCH_STATE_TESTCREATED 1		//未测试【被占用】
#define TEST_BENCH_STATE_TESTING 2		//测试中
#define TEST_BENCH_STATE_STOPED 3		//测试中断
#define TEST_BENCH_STATE_FINISHED 4		//测试完成