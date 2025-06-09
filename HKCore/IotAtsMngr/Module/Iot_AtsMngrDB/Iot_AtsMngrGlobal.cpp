//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_AtsMngrGlobal.cpp

#include "stdafx.h"
#include "Iot_AtsMngrGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CIot_AtsMngrXmlRWKeys

CIot_AtsMngrXmlRWKeys* CIot_AtsMngrXmlRWKeys::g_pXmlKeys = NULL;
long CIot_AtsMngrXmlRWKeys::g_nIotRef = 0;


CIot_AtsMngrXmlRWKeys::CIot_AtsMngrXmlRWKeys()
{
	m_strCIot_DeviceOutReportExKey = L"iot_device_out_reportex";
	m_strCIot_DeviceOutReportExsKey = L"iot_device_out_reportexs";
	m_strCIot_DeviceOutReportKey = L"iot_device_out_report";
	m_strCIot_DeviceOutReportsKey = L"iot_device_out_reports";
	m_strCIot_DeviceReportExKey = L"iot_device_reportex";
	m_strCIot_DeviceReportExsKey = L"iot_device_reportexs";
	m_strCIot_DeviceHisTestKey = L"iot_device_histest";
	m_strCIot_DeviceHisTestsKey = L"iot_device_histests";
	m_strCSys_UserKey = L"sys_user";
	m_strCIot_TestAppKey = L"iot_testapp";
	m_strCIot_TestAppsKey = L"iot_testapps";
	m_strCIotTestTaskKey = L"iot_test_task";
	m_strCIot_RTDeviceDataKey = L"iot_rt_device_data";
	m_strCIot_DeviceItemRsltKey = L"iot_device_item_rslt";
	m_strCIot_DeviceItemRsltsKey = L"iot_device_item_rslts";
	m_strCIot_DeviceModelsKey = L"iot_device_models";
	m_strCIot_DeviceModelKey = L"iot_device_model";
	m_strCIot_TestTaskDeviceKey = L"iot_test_task_device";
	m_strCIot_TestTaskDevicesKey = L"iot_test_task_devices";
	m_strCIot_BenchKey = L"iot_bench";
	m_strCIot_BenchsKey = L"iot_benchs";
	m_strCIot_EngineKey = L"iot_engine";
	m_strCIot_DeviceKey = L"iot_device";
	m_strCIot_DevicesKey = L"iot_devices";
	m_strIndex_DeviceKey = L"index_device";
	m_strIndex_Device_ClassifyKey = L"index_device_classify";
	m_strIndex_Device_TypeKey = L"index_device_type";
	m_strIndex_FactoryKey = L"index_factory";
	m_strIndex_DeptKey = L"index_dept";
	m_strModelKey = L"model";
	m_strSnKey = L"sn";
	m_strIpKey = L"ip";
	m_strPortKey = L"port";
	m_strIndex_EngineKey = L"index_engine";
	m_strIndex_ModelKey = L"index_model";
	m_strIndex_Device_DirKey = L"index_device_dir";
	m_strTest_StateKey = L"test_state";
	m_strConnect_StateKey = L"connect_state";
	m_strTask_StateKey = L"task_state";
	m_strTask_Rpt_StateKey = L"task_rpt_state";
	m_strCreate_TimeKey = L"create_time";
	m_strIndex_FolderKey = L"index_folder";
	m_strEngine_IdKey = L"engine_id";
	m_strRule_IdKey = L"rule_id";
	m_strFile_NameKey = L"file_name";
	m_strPath_Protocol_FileKey = L"path_protocol_file";
	m_strComm_TypeKey = L"comm_type";
	m_strRemarkKey = L"remark";
	m_strIndex_Engine_DirKey = L"index_engine_dir";
	m_strIndex_BenchKey = L"index_bench";
	m_strCodeKey = L"code";
	m_strStatusKey = L"status";
	m_strIndex_Test_DeviceKey = L"index_test_device";
	m_strIndex_Test_TaskKey = L"index_test_task";
	m_strIndex_Model_DirKey = L"index_model_dir";
	m_strIndex_Item_RsltKey = L"index_item_rslt";
	m_strName_Item_PathKey = L"name_item_path";
	m_strId_Item_PathKey = L"id_item_path";
	m_strStateKey = L"state";
	m_strRsltjdgKey = L"rsltjdg";
	m_strRsltdscKey = L"rsltdsc";
	m_strFile_ReportKey = L"file_report";
	m_strFile_Report_SKey = L"file_report_s";
	m_strFile_PkgsKey = L"file_pkgs";
	m_strFile_Pkgs_SKey = L"file_pkgs_s";
	m_strSelect_StateKey = L"select_state";
	m_strIndex_ItemKey = L"index_item";
	m_strIndex_Device_DataKey = L"index_device_data";
	m_strData_FormatKey = L"data_format";
	m_strDataKey = L"data";
	m_strTm_UpdateKey = L"tm_update";
	m_strIs_WarningKey = L"is_warning";
	m_strIndex_TemplateKey = L"index_template";
	m_strTm_BeginKey = L"tm_begin";
	m_strTm_EndKey = L"tm_end";
	m_strIndex_TesterKey = L"index_tester";
	m_strTime_Long_Total_TestKey = L"time_long_total_test";
	m_strIndex_TestappKey = L"index_testapp";
	m_strUser_IdKey = L"user_id";
	m_strDept_IdKey = L"dept_id";
	m_strUser_NameKey = L"user_name";
	m_strNick_NameKey = L"nick_name";
	m_strPasswordKey = L"password";
	m_strIndex_Device_HistestKey = L"index_device_histest";
	m_strIndex_UserKey = L"index_user";
	m_strDoc_FileKey = L"doc_file";
	m_strDoc_File_SKey = L"doc_file_s";
	m_strPdf_FileKey = L"pdf_file";
	m_strPdf_File_SKey = L"pdf_file_s";
	m_strGbrpt_FileKey = L"gbrpt_file";
	m_strGbrpt_File_SKey = L"gbrpt_file_s";
	m_strPcap_FileKey = L"pcap_file";
	m_strPcap_File_SKey = L"pcap_file_s";
	m_strRpt_Data_FileKey = L"rpt_data_file";
	m_strRpt_Data_File_SKey = L"rpt_data_file_s";
	m_strRpt_Data_File_FormatKey = L"rpt_data_file_format";
	m_strReport_ResultKey = L"report_result";
	m_strTest_TypeKey = L"test_type";
	m_strSn_DeviceKey = L"sn_device";
	m_strDevice_StateKey = L"devicestate";
	m_strTotalItemsKey = L"totalitems";
	m_strCurrItemKey = L"curritem";;
	m_strTotalTimeKey = L"totaltime";
	m_strRemainTimeKey = L"remaintime";
	m_strTestRsltKey = L"test_rslt";
	m_strIndexRptExKey = L"index_rptex";
	m_strIndexRptKey = L"index_rpt";
	m_strTotalItemsProtocolKey = L"totalitems_protocol";
	m_strTotalItemsFunctionKey= L"totalitems_function";

	m_strCIot_RTDeviceHisDataKey = L"iot_rt_device_his_data";
	m_strIndex_His_DataKey = L"index_his_data";
	m_strValue1Key = L"value1";
	m_strValue2Key = L"value2";
	m_strValue3Key = L"value3";
	m_strValue4Key = L"value4";
	m_strValue5Key = L"value5";
	m_strValue6Key = L"value6";
	m_strValue7Key = L"value7";
	m_strValue8Key = L"value8";
	m_strValue9Key = L"value9";
	m_strValue10Key = L"value10";
	m_strCIot_RTDeviceHisDataTitleKey = L"iot_rt_device_his_data_title";
	m_strCIot_RTDeviceHisDataTitlesKey = L"iot_rt_device_his_data_titles";
	m_strIndex_His_Data_TitleKey = L"index_his_data_title";
	m_strDataNameKey = L"data_name";
	m_strDataIdKey = L"data_id";
	m_strCIot_MonitorKey = L"iot_monitor";
	m_strCIot_MonitorsKey = L"iot_monitors";
	m_strIndex_Monitor_DataKey = L"index_monitor_data";
	m_strValueKey = L"value";
	m_strUnitKey = L"unit";
	m_strCIot_WarningKey = L"iot_warning";
	m_strIndex_WarningKey = L"index_warning";
	m_strTm_WarningKey = L"tm_warning";
	m_strVal_WarningKey = L"val_warning";
	m_strEventKey = L"event";
	m_strDeviceTypeKey = L"device_type";
	m_strUseDaysKey = L"use_days";
	m_strUseDaysAllKey = L"use_days_all";
	m_strUseCountsKey = L"use_counts";
	m_strIsUpdateKey = L"isupdate";

	m_strIndex_SubDeptKey = L"index_subdept";
	
	//南瑞传感器项目新增    ——cxa 23.05.26
	m_strCIot_TestStandardKey = L"iot_test_standard";
	m_strCIot_RuleEngineConfigKey = L"iot_rule_engine_config";
	m_strCIot_RuleClassifyKey = L"iot_rule_classify";
	m_strCIot_TemplateExKey = L"iot_template_ex";
	m_strCIot_TemplateKey = L"iot_template";
	m_strCIot_BenchCommPortKey = L"iot_bench_comm_port";
	m_strCIot_TypeTaskStandardKey = L"iot_type_task_standard";
	m_strCIot_TypeTaskStandardsKey = L"iot_type_task_standards";
	m_strCIot_TypeTaskTestAppsKey = L"iot_type_task_test_apps";
	m_strCIot_TypeTaskTestItemDatasKey = L"iot_type_task_test_item_datas";
	m_strCIot_TypeTaskTestItemKey = L"iot_type_task_test_item";
	m_strCIot_TypeTaskTestKey = L"iot_type_task_test";
	m_strCIot_TypeTaskTestsKey = L"iot_type_task_tests";
	m_strCIot_TypeTaskRtItemsKey = L"iot_type_task_rt_items";
	m_strCIot_TypeTaskDevParasKey = L"iot_type_task_dev_paras";
	m_strCIot_TypeTaskDevParasesKey = L"iot_type_task_dev_parases";
	m_strCIot_TypeTaskDevModelKey = L"iot_type_task_dev_model";
	m_strCIot_TypeTaskDevModelsKey = L"iot_type_task_dev_models";
	m_strCIot_TypeTaskDevKey = L"iot_type_task_dev";
	m_strCIot_TypeTaskKey = L"iot_type_task";
	m_strCIot_TemplateItemKey = L"iot_template_item";
	m_strCIot_TemplateItemsKey = L"iot_template_items";
	m_strIndex_ItemsKey = L"index_items";
	m_strnIdKey = L"id";   //以前有些表，是id作为主键，数据类型是long
	m_strTypeKey = L"type";
	m_strIndex_TaskKey = L"index_task";
	m_strId_UserKey = L"id_user";
	m_strState_CreateKey = L"state_create";
	m_strSn_SampleKey = L"sn_sample";
	m_strName_SampleKey = L"name_sample";
	m_strModel_SampleKey = L"model_sample";
	m_strCnt_SampleKey = L"cnt_sample";
	m_strName_ClientKey = L"name_client";
	m_strName_ManufactorKey = L"name_manufactor";
	m_strAddress_ClientKey = L"address_client";
	m_strAddress_ManufactorKey = L"address_manufactor";
	m_strName_TemplateKey = L"name_template";
	m_strPic_FileKey = L"pic_file";
	m_strPic_File_SKey = L"pic_file_s";
	m_strTask_FileKey = L"task_file";
	m_strTask_File_SKey = L"task_file_s";
	m_strDvm_FileKey = L"dvm_file";
	m_strDvm_File_SKey = L"dvm_file_s";
	m_strId_MaininspectionKey = L"id_maininspection";
	m_strId_CheckerKey = L"id_checker";
	m_strId_ProofreaderKey = L"id_proofreader";
	m_strInspection_TypeKey = L"inspection_type";
	m_strIndex_DevKey = L"index_dev";
	m_strSn_Sample_DevKey = L"sn_sample_dev";
	m_strNumber_Sample_DevKey = L"number_sample_dev";
	m_strIndex_ParasKey = L"index_paras";
	m_strId_DevKey = L"id_dev";
	m_strData_TypeKey = L"data_type";
	m_strIndex_DataKey = L"index_data";
	m_strCnt_Test_RecordKey = L"cnt_test_record";
	m_strIndex_TestKey = L"index_test";
	m_strSn_ItemsKey = L"sn_items";
	m_strRpt_FileKey = L"rpt_file";
	m_strRpt_File_SKey = L"rpt_file_s";
	m_strFinal_ReportKey = L"final_report";
	m_strTime_Test_StartKey = L"time_test_start";
	m_strTime_Test_EndKey = L"time_test_end";
	m_strTm_TestKey = L"tm_test";
	m_strTempretureKey = L"tempreture";
	m_strHumidityKey = L"humidity";
	m_strType_ItemKey = L"type_item";
	m_strIndex_Item_DataKey = L"index_item_data";
	m_strIndex_Test_RecordKey = L"index_test_record";
	m_strIndex_SampleKey = L"index_sample";
	m_strSn_TestappKey = L"sn_testapp";
	m_strName_TestappKey = L"name_testapp";
	m_strStandard_NameKey = L"standard_name";
	m_strIndex_CommKey = L"index_comm";
	m_strIndex_Template_DirKey = L"index_template_dir";
	m_strTemplate_FileKey = L"template_file";
	m_strProtocol_FileKey = L"protocol_file";
	m_strIecfg_FileKey = L"iecfg_file";
	m_strGbxml_FileKey = L"gbxml_file";
	m_strXml_FileKey = L"xml_file";
	m_strUpload_TimeKey = L"upload_time";
	m_strCnt_File_Doc_ExKey = L"cnt_file_doc_ex";
	m_strVersionKey = L"version";
	m_strSvr_Relate_PathKey = L"svr_relate_path";
	m_strIndex_Template_ExKey = L"index_template_ex";
	m_strDoc_RptfileKey = L"doc_rptfile";
	m_strDoc_Rptfile_SKey = L"doc_rptfile_s";
	m_strDevice_Classify_IdKey = L"device_classify_id";
	m_strSuffix_FileKey = L"suffix_file";
	m_strDataUnitKey = L"data_unit";
	m_strName_Template_FileKey = L"name_template_file";
	
	//chenxinan 23.06.01
	m_strCIot_TypeTaskTestItemGenKey = L"iot_type_task_test_item_gen";
	m_strCIot_TypeTaskTestItemGensKey = L"iot_type_task_test_item_gens";
	m_strCIot_ItemGenKey = L"iot_item_gen";
	m_strCIot_ItemsKey = L"iot_items";
	m_strItem_Gen_FileKey = L"item_gen_file";
	m_strItem_Gen_File_SKey = L"item_gen_file_s";
	m_strIndex_GenKey = L"index_gen";
	m_strId_ItemsKey = L"id_items";
	m_strPara1_NameKey = L"para1_name";
	m_strPara1_IdKey = L"para1_id";
	m_strPara1_ValueKey = L"para1_value";
	m_strPara2_NameKey = L"para2_name";
	m_strPara2_IdKey = L"para2_id";
	m_strPara2_ValueKey = L"para2_value";
	m_strPara3_NameKey = L"para3_name";
	m_strPara3_IdKey = L"para3_id";
	m_strPara3_ValueKey = L"para3_value";
	m_strPara4_NameKey = L"para4_name";
	m_strPara4_IdKey = L"para4_id";
	m_strPara4_ValueKey = L"para4_value";
	m_strSelectKey = L"select";
	
	//chenxinan 23.06.30
	m_strCIot_RtDataDeviceKey = L"iot_rt_data_device";
	m_strCIot_RtDataTestAppKey = L"iot_rt_data_testapp";
	m_strCIot_RtDataTitleKey = L"iot_rt_data_title";
	m_strIndex_Data_DefinitionKey = L"index_data_definition";
	m_strName_DataKey = L"name_data";
	m_strUnit_DataKey = L"unit_data";
	m_strIndex_Testapp_DataKey = L"index_testapp_data";
	m_strTimeKey = L"time";
	m_strIndex_Data1Key = L"index_data1";
	m_strValue_Data1Key = L"value_data1";
	m_strIndex_Data2Key = L"index_data2";
	m_strValue_Data2Key = L"value_data2";
	m_strIndex_Data3Key = L"index_data3";
	m_strValue_Data3Key = L"value_data3";
	m_strIndex_Data4Key = L"index_data4";
	m_strValue_Data4Key = L"value_data4";
	m_strIndex_Data5Key = L"index_data5";
	m_strValue_Data5Key = L"value_data5";
	m_strIndex_Data6Key = L"index_data6";
	m_strValue_Data6Key = L"value_data6";
	m_strIndex_Data7Key = L"index_data7";
	m_strValue_Data7Key = L"value_data7";
	m_strIndex_Data8Key = L"index_data8";
	m_strValue_Data8Key = L"value_data8";
	m_strIndex_Data9Key = L"index_data9";
	m_strValue_Data9Key = L"value_data9";
	m_strIndex_Data10Key = L"index_data10";
	m_strValue_Data10Key = L"value_data10";
	m_strIndex_Data11Key = L"index_data11";
	m_strValue_Data11Key = L"value_data11";
	m_strIndex_Data12Key = L"index_data12";
	m_strValue_Data12Key = L"value_data12";
	m_strIndex_Data13Key = L"index_data13";
	m_strValue_Data13Key = L"value_data13";
	m_strIndex_Data14Key = L"index_data14";
	m_strValue_Data14Key = L"value_data14";
	m_strIndex_Data15Key = L"index_data15";
	m_strValue_Data15Key = L"value_data15";
	m_strIndex_Data16Key = L"index_data16";
	m_strValue_Data16Key = L"value_data16";
	m_strIndex_Data17Key = L"index_data17";
	m_strValue_Data17Key = L"value_data17";
	m_strIndex_Data18Key = L"index_data18";
	m_strValue_Data18Key = L"value_data18";
	m_strIndex_Data19Key = L"index_data19";
	m_strValue_Data19Key = L"value_data19";
	m_strIndex_Data20Key = L"index_data20";
	m_strValue_Data20Key = L"value_data20";
	m_strIndex_Sample_DataKey = L"index_sample_data";
	m_strIndex_Data21Key = L"index_data21";
	m_strValue_Data21Key = L"value_data21";
	m_strIndex_Data22Key = L"index_data22";
	m_strValue_Data22Key = L"value_data22";
	m_strIndex_Data23Key = L"index_data23";
	m_strValue_Data23Key = L"value_data23";
	m_strIndex_Data24Key = L"index_data24";
	m_strValue_Data24Key = L"value_data24";
	m_strIndex_Data25Key = L"index_data25";
	m_strValue_Data25Key = L"value_data25";
	m_strIndex_Data26Key = L"index_data26";
	m_strValue_Data26Key = L"value_data26";
	m_strIndex_Data27Key = L"index_data27";
	m_strValue_Data27Key = L"value_data27";
	m_strIndex_Data28Key = L"index_data28";
	m_strValue_Data28Key = L"value_data28";
	m_strIndex_Data29Key = L"index_data29";
	m_strValue_Data29Key = L"value_data29";
	m_strIndex_Data30Key = L"index_data30";
	m_strValue_Data30Key = L"value_data30";
}

CIot_AtsMngrXmlRWKeys::~CIot_AtsMngrXmlRWKeys()
{
}

CIot_AtsMngrXmlRWKeys* CIot_AtsMngrXmlRWKeys::Create()
{
	g_nIotRef++;

	if (g_nIotRef == 1)
	{
		g_pXmlKeys = new CIot_AtsMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CIot_AtsMngrXmlRWKeys::Release()
{
	g_nIotRef--;

	if (g_nIotRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CIot_AtsMngrConstGlobal

long CIot_AtsMngrConstGlobal::g_nGlobalRef = 0;
CIot_AtsMngrConstGlobal* CIot_AtsMngrConstGlobal::g_pGlobal = NULL;


CIot_AtsMngrConstGlobal::CIot_AtsMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CIot_AtsMngrConstGlobal::~CIot_AtsMngrConstGlobal()
{
}

CIot_AtsMngrConstGlobal* CIot_AtsMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CIot_AtsMngrConstGlobal();
	}

	return g_pGlobal;
}

void CIot_AtsMngrConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;
