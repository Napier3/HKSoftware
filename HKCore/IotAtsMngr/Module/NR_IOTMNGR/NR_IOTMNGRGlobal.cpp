//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//NR_IOTMNGRGlobal.cpp

#include "stdafx.h"
#include "NR_IOTMNGRGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CNR_IOTMNGRXmlRWKeys

CNR_IOTMNGRXmlRWKeys* CNR_IOTMNGRXmlRWKeys::g_pXmlKeys = NULL;
long CNR_IOTMNGRXmlRWKeys::g_nIotRef = 0;


CNR_IOTMNGRXmlRWKeys::CNR_IOTMNGRXmlRWKeys()
{
	m_strCSys_UserKey = L"sys_user";
	m_strCSys_UsersKey = L"sys_users";
	m_strCIot_LogsKey = L"iot_logs";
	m_strCIot_LogKey = L"iot_log";
	m_strCIot_RtDeviceDatasKey = L"iot_rt_device_datas";
	m_strCIot_RtDeviceDataKey = L"iot_rt_device_data";
	m_strCIot_DeviceMergeReportKey = L"iot_device_merge_report";
	m_strCIot_DeviceMergeReportsKey = L"iot_device_merge_reports";
	m_strCIot_DeviceModelDirKey = L"iot_device_model_dir";
	m_strCIot_DeviceModelDirsKey = L"iot_device_model_dirs";
	m_strCIot_TestTaskTestappsKey = L"iot_test_task_testapps";
	m_strCIot_TestTaskTestappKey = L"iot_test_task_testapp";
	m_strCIot_Device_ClassifysKey = L"iot_device_classifys";
	m_strCIot_Device_ClassifyKey = L"iot_device_classify";
	m_strCIot_DeviceReportExKey = L"iot_device_reportex";
	m_strCIot_DeviceReportExsKey = L"iot_device_reportexs";
	m_strCIot_DeviceTestKey = L"iot_device_test";
	m_strCIot_DeviceTestsKey = L"iot_device_tests";
	m_strCIot_DeviceItemRsltKey = L"iot_device_item_rslt";
	m_strCIot_DeviceItemRsltsKey = L"iot_device_item_rslts";
	m_strCIot_TestTaskDeviceKey = L"iot_test_task_device";
	m_strCIot_TestTaskDevicesKey = L"iot_test_task_devices";
	m_strCIot_BenchTestAppKey = L"iot_bench_testapp";
	m_strCIot_BenchTestAppsKey = L"iot_bench_testapps";
	m_strCIot_BenchKey = L"iot_bench";
	m_strCIot_BenchsKey = L"iot_benchs";
	m_strCIot_TemplateFolderKey = L"iot_templatefolder";
	m_strCIot_TemplateFoldersKey = L"iot_templatefolders";
	m_strCIot_Engine_DirKey = L"iot_engine_dir";
	m_strCIot_Engine_DirsKey = L"iot_engine_dirs";
	m_strCIot_DvmFileKey = L"iot_dvmfile";
	m_strCIot_DvmFilesKey = L"iot_dvmfiles";
	m_strCIot_TemplateDocExKey = L"iot_template_doc_ex";
	m_strCIot_TemplateDocExsKey = L"iot_template_doc_exs";
	m_strCIot_TemplateKey = L"iot_template";
	m_strCIot_EngineKey = L"iot_engine";
	m_strCIot_EnginesKey = L"iot_engines";
	m_strCIot_TestAppKey = L"iot_testapp";
	m_strCIot_TestAppsKey = L"iot_testapps";
	m_strCIot_DeviceKey = L"iot_device";
	m_strCIot_DevicesKey = L"iot_devices";
	m_strCIot_FactoryKey = L"iot_factory";
	m_strCIot_FactorysKey = L"iot_factorys";
	m_strCIot_DeviceClassifyTypeKey = L"iot_device_classify_type";
	m_strCIot_DeviceClassifyTypesKey = L"iot_device_classify_types";
	m_strCIot_UserRoleKey = L"iot_userrole";
	m_strCIot_UserRolesKey = L"iot_userroles";
	m_strCIot_RoleRightKey = L"iot_roleright";
	m_strCIot_RoleRightsKey = L"iot_rolerights";
	m_strCIot_RightKey = L"iot_right";
	m_strCIot_RightsKey = L"iot_rights";
	m_strCIot_RoleKey = L"iot_role";
	m_strCIot_RolesKey = L"iot_roles";
	m_strCIot_UserKey = L"iot_user";
	m_strCIot_UsersKey = L"iot_users";
	m_strCIot_DeptKey = L"iot_dept";
	m_strCIot_DeptsKey = L"iot_depts";
	m_strIndex_DeptKey = L"index_dept";
	m_strIndex_Parent_DeptKey = L"index_parent_dept";
	m_strTypeKey = L"type";
	m_strIndex_UserKey = L"index_user";
	m_strName_LoginKey = L"name_login";
	m_strPsw_LoginKey = L"psw_login";
	m_strIndex_RoleKey = L"index_role";
	m_strDescriptionKey = L"description";
	m_strVal_RightKey = L"val_right";
	m_strIndex_RolerightKey = L"index_roleright";
	m_strIndex_UsrroleKey = L"index_usrrole";
	m_strIndex_Device_TypeKey = L"index_device_type";
	m_strDeviceclassifyKey = L"deviceclassify";
	m_strCodeKey = L"id";
	m_strIndex_Device_ClassifyKey = L"index_device_classify";
	m_strIndex_FactoryKey = L"index_factory";
	m_strIndex_DeviceKey = L"index_device";
	m_strIndex_DevicetypeKey = L"index_devicetype";
	m_strIndex_EngineKey = L"index_engine";
	m_strModelKey = L"model";
	m_strSnKey = L"sn";
	m_strPortKey = L"port";
	m_strIpKey = L"ip";
	m_strDvm_FileKey = L"dvm_file";
	m_strTest_StateKey = L"test_state";
	m_strIndex_Device_DirKey = L"index_device_dir";
	m_strDvm_File_SKey = L"dvm_file_s";
	m_strIndex_TestappKey = L"index_testapp";
	m_strIndex_Device_Classify_TypeKey = L"index_device_classify_type";
	m_strStateKey = L"state";
	m_strIndex_FolderKey = L"index_folder";
	m_strEngine_IdKey = L"engine_id";
	m_strRule_IdKey = L"rule_id";
	m_strProtocol_FileKey = L"protocol_file";
	m_strComm_TypeKey = L"comm_type";
	m_strIndex_Engine_DirKey = L"index_engine_dir";
	m_strProtocol_File_SKey = L"protocol_file_s";
	m_strCreate_TimeKey = L"create_time";
	m_strIndex_TemplateKey = L"index_template";
	m_strTemplate_FileKey = L"template_file";
	m_strIecfg_FileKey = L"iecfg_file";
	m_strGbxml_FileKey = L"gbxml_file";
	m_strDoc_FileKey = L"doc_file";
	m_strXml_FileKey = L"xml_file";
	m_strTm_UpdateKey = L"tm_update";
	m_strCnt_File_Doc_ExKey = L"cnt_file_doc_ex";
	m_strVersionKey = L"version";
	m_strFile_ReportKey = L"file_report";
	m_strTemplate_File_SKey = L"template_file_s";
	m_strIecfg_File_SKey = L"iecfg_file_s";
	m_strGbxml_File_SKey = L"gbxml_file_s";
	m_strDoc_File_SKey = L"doc_file_s";
	m_strXml_File_SKey = L"xml_file_s";
	m_strFile_Report_SKey = L"file_report_s";
	m_strIndex_Template_DocKey = L"index_template_doc";
	m_strDoc_RptfileKey = L"doc_rptfile";
	m_strDoc_Rptfile_SKey = L"doc_rptfile_s";
	m_strIndex_DvmfileKey = L"index_dvmfile";
	m_strParent_IndexKey = L"parent_index";
	m_strDir_NameKey = L"dir_name";
	m_strIndex_Parent_FolderKey = L"index_parent_folder";
	m_strTm_CreateKey = L"tm_create";
	m_strIndex_BenchKey = L"index_bench";
	m_strSn_BenchKey = L"sn_bench";
	m_strTest_TypeKey = L"test_type";
	m_strIndex_TesterKey = L"index_tester";
	m_strTime_Long_Total_TestKey = L"time_long_total_test";
	m_strTime_Long_UsedKey = L"time_long_used";
	m_strIndex_TestKey = L"index_test";
	m_strTm_BeginKey = L"tm_begin";
	m_strTm_EndKey = L"tm_end";
	m_strIndex_Bench_TestappKey = L"index_bench_testapp";
	m_strModel_TestappKey = L"model_testapp";
	m_strSn_TestappKey = L"sn_testapp";
	m_strIndex_Test_DeviceKey = L"index_test_device";
	m_strSn_DeviceKey = L"sn_device";
	m_strIndex_Test_TaskKey = L"index_test_task";
	m_strIndex_Item_RsltKey = L"Index_item_rslt";
	m_strName_Item_PathKey = L"name_item_path";
	m_strId_Item_PathKey = L"id_item_path";
	m_strIndex_ItemKey = L"index_item";
	m_strRsltjdgKey = L"rsltjdg";
	m_strRsltdscKey = L"rsltdsc";
	m_strFile_PkgsKey = L"file_pkgs";
	m_strSelect_StateKey = L"select_state";
	m_strFile_Pkgs_SKey = L"file_pkgs_s";
	m_strIndex_Device_TestKey = L"index_device_test";
	m_strPdf_FileKey = L"pdf_file";
	m_strGbrpt_FileKey = L"gbrpt_file";
	m_strRpt_Data_FileKey = L"rpt_data_file";
	m_strRpt_Data_File_FormatKey = L"rpt_data_file_format";
	m_strTestapp_UsedKey = L"testapp_used";
	m_strPcap_FileKey = L"pcap_file";
	m_strReport_ResultKey = L"report_result";
	m_strPdf_File_SKey = L"pdf_file_s";
	m_strGbrpt_File_SKey = L"gbrpt_file_s";
	m_strRpt_Data_File_SKey = L"rpt_data_file_s";
	m_strPcap_File_SKey = L"pcap_file_s";
	m_strIndex_RptexKey = L"index_rptex";
	m_strIndex_Test_TestappKey = L"index_test_testapp";
	m_strIndex_Model_DirKey = L"index_model_dir";
	m_strIndex_Merge_ReportKey = L"index_merge_report";
	m_strMerge_FileKey = L"merge_file";
	m_strMerge_File_SKey = L"merge_file_s";
	m_strMerge_IdsKey = L"merge_ids";
	m_strIndex_Device_DataKey = L"index_device_data";
	m_strData_FormatKey = L"data_format";
	m_strDataKey = L"data";
	m_strIs_WarningKey = L"is_warning";
	m_strIndex_LogKey = L"index_log";
	m_strTxt_LogKey = L"txt_log";
	m_strUser_IdKey = L"user_id";
	m_strDept_IdKey = L"dept_id";
	m_strUser_NameKey = L"user_name";
	m_strNick_NameKey = L"nick_name";
	m_strUser_TypeKey = L"user_type";
	m_strEmailKey = L"email";
	m_strPhonenumberKey = L"phonenumber";
	m_strSexKey = L"sex";
	m_strAvatarKey = L"avatar";
	m_strPasswordKey = L"password";
	m_strStatusKey = L"status";
	m_strDel_FlagKey = L"del_flag";
	m_strLogin_IpKey = L"login_ip";
	m_strLogin_DateKey = L"login_date";
	m_strCreate_ByKey = L"create_by";
	m_strUpdate_ByKey = L"update_by";
	m_strUpdate_TimeKey = L"update_time";
	m_strRemarkKey = L"remark";
}

CNR_IOTMNGRXmlRWKeys::~CNR_IOTMNGRXmlRWKeys()
{
}

CNR_IOTMNGRXmlRWKeys* CNR_IOTMNGRXmlRWKeys::Create()
{
	g_nIotRef++;

	if (g_nIotRef == 1)
	{
		g_pXmlKeys = new CNR_IOTMNGRXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CNR_IOTMNGRXmlRWKeys::Release()
{
	g_nIotRef--;

	if (g_nIotRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CNR_IOTMNGRConstGlobal

long CNR_IOTMNGRConstGlobal::g_nGlobalRef = 0;
CNR_IOTMNGRConstGlobal* CNR_IOTMNGRConstGlobal::g_pGlobal = NULL;


CNR_IOTMNGRConstGlobal::CNR_IOTMNGRConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CNR_IOTMNGRConstGlobal::~CNR_IOTMNGRConstGlobal()
{
}

CNR_IOTMNGRConstGlobal* CNR_IOTMNGRConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CNR_IOTMNGRConstGlobal();
	}

	return g_pGlobal;
}

void CNR_IOTMNGRConstGlobal::Release()
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
