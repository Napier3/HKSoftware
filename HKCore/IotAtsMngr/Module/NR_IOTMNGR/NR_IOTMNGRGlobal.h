//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//NR_IOTMNGRGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define IotCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define IotCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define IOTCLASSID_CIOT_DEPTS       (IotCLASSID_EXLISTCLASS + 0X00000000)
#define IOTCLASSID_CIOT_DEPT       (IotCLASSID_EXLISTCLASS + 0X00000001)
#define IOTCLASSID_CIOT_USERS       (IotCLASSID_EXLISTCLASS + 0X00000002)
#define IOTCLASSID_CIOT_USER       (IotCLASSID_BASECLASS + 0X00000003)
#define IOTCLASSID_CIOT_ROLES       (IotCLASSID_EXLISTCLASS + 0X00000004)
#define IOTCLASSID_CIOT_ROLE       (IotCLASSID_EXLISTCLASS + 0X00000005)
#define IOTCLASSID_CIOT_RIGHTS       (IotCLASSID_EXLISTCLASS + 0X00000006)
#define IOTCLASSID_CIOT_RIGHT       (IotCLASSID_BASECLASS + 0X00000007)
#define IOTCLASSID_CIOT_ROLERIGHTS       (IotCLASSID_EXLISTCLASS + 0X00000008)
#define IOTCLASSID_CIOT_ROLERIGHT       (IotCLASSID_BASECLASS + 0X00000009)
#define IOTCLASSID_CIOT_USERROLES       (IotCLASSID_EXLISTCLASS + 0X0000000A)
#define IOTCLASSID_CIOT_USERROLE       (IotCLASSID_BASECLASS + 0X0000000B)
#define IOTCLASSID_CIOT_DEVICECLASSIFYTYPES       (IotCLASSID_EXLISTCLASS + 0X0000000C)
#define IOTCLASSID_CIOT_DEVICECLASSIFYTYPE       (IotCLASSID_BASECLASS + 0X0000000D)
#define IOTCLASSID_CIOT_FACTORYS       (IotCLASSID_EXLISTCLASS + 0X0000000E)
#define IOTCLASSID_CIOT_FACTORY       (IotCLASSID_BASECLASS + 0X0000000F)
#define IOTCLASSID_CIOT_DEVICES       (IotCLASSID_EXLISTCLASS + 0X00000010)
#define IOTCLASSID_CIOT_DEVICE       (IotCLASSID_BASECLASS + 0X00000011)
#define IOTCLASSID_CIOT_TESTAPPS       (IotCLASSID_EXLISTCLASS + 0X00000012)
#define IOTCLASSID_CIOT_TESTAPP       (IotCLASSID_BASECLASS + 0X00000013)
#define IOTCLASSID_CIOT_ENGINES       (IotCLASSID_EXLISTCLASS + 0X00000014)
#define IOTCLASSID_CIOT_ENGINE       (IotCLASSID_BASECLASS + 0X00000015)
#define IOTCLASSID_CIOT_TEMPLATE       (IotCLASSID_EXLISTCLASS + 0X00000016)
#define IOTCLASSID_CIOT_TEMPLATEDOCEXS       (IotCLASSID_EXLISTCLASS + 0X00000017)
#define IOTCLASSID_CIOT_TEMPLATEDOCEX       (IotCLASSID_BASECLASS + 0X00000018)
#define IOTCLASSID_CIOT_DVMFILES       (IotCLASSID_EXLISTCLASS + 0X00000019)
#define IOTCLASSID_CIOT_DVMFILE       (IotCLASSID_BASECLASS + 0X0000001A)
#define IOTCLASSID_CIOT_ENGINE_DIRS       (IotCLASSID_EXLISTCLASS + 0X0000001B)
#define IOTCLASSID_CIOT_ENGINE_DIR       (IotCLASSID_EXLISTCLASS + 0X0000001C)
#define IOTCLASSID_CIOT_TEMPLATEFOLDERS       (IotCLASSID_EXLISTCLASS + 0X0000001D)
#define IOTCLASSID_CIOT_TEMPLATEFOLDER       (IotCLASSID_EXLISTCLASS + 0X0000001E)
#define IOTCLASSID_CIOT_BENCHS       (IotCLASSID_EXLISTCLASS + 0X0000001F)
#define IOTCLASSID_CIOT_BENCH       (IotCLASSID_EXLISTCLASS + 0X00000020)
#define IOTCLASSID_CIOT_BENCHTESTAPPS       (IotCLASSID_EXLISTCLASS + 0X00000021)
#define IOTCLASSID_CIOT_BENCHTESTAPP       (IotCLASSID_BASECLASS + 0X00000022)
#define IOTCLASSID_CIOT_TESTTASKDEVICES       (IotCLASSID_EXLISTCLASS + 0X00000023)
#define IOTCLASSID_CIOT_TESTTASKDEVICE       (IotCLASSID_BASECLASS + 0X00000024)
#define IOTCLASSID_CIOT_DEVICEITEMRSLTS       (IotCLASSID_EXLISTCLASS + 0X00000025)
#define IOTCLASSID_CIOT_DEVICEITEMRSLT       (IotCLASSID_BASECLASS + 0X00000026)
#define IOTCLASSID_CIOT_DEVICETESTS       (IotCLASSID_EXLISTCLASS + 0X00000027)
#define IOTCLASSID_CIOT_DEVICETEST       (IotCLASSID_BASECLASS + 0X00000028)
#define IOTCLASSID_CIOT_DEVICEREPORTEXS       (IotCLASSID_EXLISTCLASS + 0X00000029)
#define IOTCLASSID_CIOT_DEVICEREPORTEX       (IotCLASSID_BASECLASS + 0X0000002A)
#define IOTCLASSID_CIOT_DEVICE_CLASSIFY       (IotCLASSID_BASECLASS + 0X0000002B)
#define IOTCLASSID_CIOT_DEVICE_CLASSIFYS       (IotCLASSID_EXLISTCLASS + 0X0000002C)
#define IOTCLASSID_CIOT_TESTTASKTESTAPP       (IotCLASSID_BASECLASS + 0X0000002D)
#define IOTCLASSID_CIOT_TESTTASKTESTAPPS       (IotCLASSID_EXLISTCLASS + 0X0000002E)
#define IOTCLASSID_CIOT_DEVICEMODELDIRS       (IotCLASSID_EXLISTCLASS + 0X0000002F)
#define IOTCLASSID_CIOT_DEVICEMODELDIR       (IotCLASSID_BASECLASS + 0X00000030)
#define IOTCLASSID_CIOT_DEVICEMERGEREPORTS       (IotCLASSID_EXLISTCLASS + 0X00000031)
#define IOTCLASSID_CIOT_DEVICEMERGEREPORT       (IotCLASSID_BASECLASS + 0X00000032)
#define IOTCLASSID_CIOT_RTDEVICEDATA       (IotCLASSID_BASECLASS + 0X00000033)
#define IOTCLASSID_CIOT_RTDEVICEDATAS       (IotCLASSID_EXLISTCLASS + 0X00000034)
#define IOTCLASSID_CIOT_LOG       (IotCLASSID_BASECLASS + 0X00000035)
#define IOTCLASSID_CIOT_LOGS       (IotCLASSID_EXLISTCLASS + 0X00000036)
#define IOTCLASSID_CSYS_USERS       (IotCLASSID_EXLISTCLASS + 0X00000037)
#define IOTCLASSID_CSYS_USER       (IotCLASSID_BASECLASS + 0X00000038)

class CNR_IOTMNGRXmlRWKeys : public CXmlRWKeys
{
protected:
	CNR_IOTMNGRXmlRWKeys();
	virtual ~CNR_IOTMNGRXmlRWKeys();
	static long g_nIotRef;

public:
	static CNR_IOTMNGRXmlRWKeys* g_pXmlKeys;
	static CNR_IOTMNGRXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSys_UserKey; //sys_user
	BSTR m_strCSys_UsersKey; //sys_users
	BSTR m_strCIot_LogsKey; //iot_logs
	BSTR m_strCIot_LogKey; //iot_log
	BSTR m_strCIot_RtDeviceDatasKey; //iot_rt_device_datas
	BSTR m_strCIot_RtDeviceDataKey; //iot_rt_device_data
	BSTR m_strCIot_DeviceMergeReportKey; //iot_device_merge_report
	BSTR m_strCIot_DeviceMergeReportsKey; //iot_device_merge_reports
	BSTR m_strCIot_DeviceModelDirKey; //iot_device_model_dir
	BSTR m_strCIot_DeviceModelDirsKey; //iot_device_model_dirs
	BSTR m_strCIot_TestTaskTestappsKey; //iot_test_task_testapps
	BSTR m_strCIot_TestTaskTestappKey; //iot_test_task_testapp
	BSTR m_strCIot_Device_ClassifysKey; //iot_device_classifys
	BSTR m_strCIot_Device_ClassifyKey; //iot_device_classify
	BSTR m_strCIot_DeviceReportExKey; //iot_device_reportex
	BSTR m_strCIot_DeviceReportExsKey; //iot_device_reportexs
	BSTR m_strCIot_DeviceTestKey; //iot_device_test
	BSTR m_strCIot_DeviceTestsKey; //iot_device_tests
	BSTR m_strCIot_DeviceItemRsltKey; //iot_device_item_rslt
	BSTR m_strCIot_DeviceItemRsltsKey; //iot_device_item_rslts
	BSTR m_strCIot_TestTaskDeviceKey; //iot_test_task_device
	BSTR m_strCIot_TestTaskDevicesKey; //iot_test_task_devices
	BSTR m_strCIot_BenchTestAppKey; //iot_bench_testapp
	BSTR m_strCIot_BenchTestAppsKey; //iot_bench_testapps
	BSTR m_strCIot_BenchKey; //iot_bench
	BSTR m_strCIot_BenchsKey; //iot_benchs
	BSTR m_strCIot_TemplateFolderKey; //iot_templatefolder
	BSTR m_strCIot_TemplateFoldersKey; //iot_templatefolders
	BSTR m_strCIot_Engine_DirKey; //iot_engine_dir
	BSTR m_strCIot_Engine_DirsKey; //iot_engine_dirs
	BSTR m_strCIot_DvmFileKey; //iot_dvmfile
	BSTR m_strCIot_DvmFilesKey; //iot_dvmfiles
	BSTR m_strCIot_TemplateDocExKey; //iot_template_doc_ex
	BSTR m_strCIot_TemplateDocExsKey; //iot_template_doc_exs
	BSTR m_strCIot_TemplateKey; //iot_template
	BSTR m_strCIot_EngineKey; //iot_engine
	BSTR m_strCIot_EnginesKey; //iot_engines
	BSTR m_strCIot_TestAppKey; //iot_testapp
	BSTR m_strCIot_TestAppsKey; //iot_testapps
	BSTR m_strCIot_DeviceKey; //iot_device
	BSTR m_strCIot_DevicesKey; //iot_devices
	BSTR m_strCIot_FactoryKey; //iot_factory
	BSTR m_strCIot_FactorysKey; //iot_factorys
	BSTR m_strCIot_DeviceClassifyTypeKey; //iot_device_classify_type
	BSTR m_strCIot_DeviceClassifyTypesKey; //iot_device_classify_types
	BSTR m_strCIot_UserRoleKey; //iot_userrole
	BSTR m_strCIot_UserRolesKey; //iot_userroles
	BSTR m_strCIot_RoleRightKey; //iot_roleright
	BSTR m_strCIot_RoleRightsKey; //iot_rolerights
	BSTR m_strCIot_RightKey; //iot_right
	BSTR m_strCIot_RightsKey; //iot_rights
	BSTR m_strCIot_RoleKey; //iot_role
	BSTR m_strCIot_RolesKey; //iot_roles
	BSTR m_strCIot_UserKey; //iot_user
	BSTR m_strCIot_UsersKey; //iot_users
	BSTR m_strCIot_DeptKey; //iot_dept
	BSTR m_strCIot_DeptsKey; //iot_depts
	BSTR m_strIndex_DeptKey; //index_dept
	BSTR m_strIndex_Parent_DeptKey; //index_parent_dept
	BSTR m_strTypeKey; //type
	BSTR m_strIndex_UserKey; //index_user
	BSTR m_strName_LoginKey; //name_login
	BSTR m_strPsw_LoginKey; //psw_login
	BSTR m_strIndex_RoleKey; //index_role
	BSTR m_strDescriptionKey; //description
	BSTR m_strVal_RightKey; //val_right
	BSTR m_strIndex_RolerightKey; //index_roleright
	BSTR m_strIndex_UsrroleKey; //index_usrrole
	BSTR m_strIndex_Device_TypeKey; //index_device_type
	BSTR m_strDeviceclassifyKey; //deviceclassify
	BSTR m_strCodeKey; //id
	BSTR m_strIndex_Device_ClassifyKey; //index_device_classify
	BSTR m_strIndex_FactoryKey; //index_factory
	BSTR m_strIndex_DeviceKey; //index_device
	BSTR m_strIndex_DevicetypeKey; //index_devicetype
	BSTR m_strIndex_EngineKey; //index_engine
	BSTR m_strModelKey; //model
	BSTR m_strSnKey; //sn
	BSTR m_strPortKey; //port
	BSTR m_strIpKey; //ip
	BSTR m_strDvm_FileKey; //dvm_file
	BSTR m_strTest_StateKey; //test_state
	BSTR m_strIndex_Device_DirKey; //index_device_dir
	BSTR m_strDvm_File_SKey; //dvm_file_s
	BSTR m_strIndex_TestappKey; //index_testapp
	BSTR m_strIndex_Device_Classify_TypeKey; //index_device_classify_type
	BSTR m_strStateKey; //state
	BSTR m_strIndex_FolderKey; //index_folder
	BSTR m_strEngine_IdKey; //engine_id
	BSTR m_strRule_IdKey; //rule_id
	BSTR m_strProtocol_FileKey; //protocol_file
	BSTR m_strComm_TypeKey; //comm_type
	BSTR m_strIndex_Engine_DirKey; //index_engine_dir
	BSTR m_strProtocol_File_SKey; //protocol_file_s
	BSTR m_strCreate_TimeKey; //create_time
	BSTR m_strIndex_TemplateKey; //index_template
	BSTR m_strTemplate_FileKey; //template_file
	BSTR m_strIecfg_FileKey; //iecfg_file
	BSTR m_strGbxml_FileKey; //gbxml_file
	BSTR m_strDoc_FileKey; //doc_file
	BSTR m_strXml_FileKey; //xml_file
	BSTR m_strTm_UpdateKey; //tm_update
	BSTR m_strCnt_File_Doc_ExKey; //cnt_file_doc_ex
	BSTR m_strVersionKey; //version
	BSTR m_strFile_ReportKey; //file_report
	BSTR m_strTemplate_File_SKey; //template_file_s
	BSTR m_strIecfg_File_SKey; //iecfg_file_s
	BSTR m_strGbxml_File_SKey; //gbxml_file_s
	BSTR m_strDoc_File_SKey; //doc_file_s
	BSTR m_strXml_File_SKey; //xml_file_s
	BSTR m_strFile_Report_SKey; //file_report_s
	BSTR m_strIndex_Template_DocKey; //index_template_doc
	BSTR m_strDoc_RptfileKey; //doc_rptfile
	BSTR m_strDoc_Rptfile_SKey; //doc_rptfile_s
	BSTR m_strIndex_DvmfileKey; //index_dvmfile
	BSTR m_strParent_IndexKey; //parent_index
	BSTR m_strDir_NameKey; //dir_name
	BSTR m_strIndex_Parent_FolderKey; //index_parent_folder
	BSTR m_strTm_CreateKey; //tm_create
	BSTR m_strIndex_BenchKey; //index_bench
	BSTR m_strSn_BenchKey; //sn_bench
	BSTR m_strTest_TypeKey; //test_type
	BSTR m_strIndex_TesterKey; //index_tester
	BSTR m_strTime_Long_Total_TestKey; //time_long_total_test
	BSTR m_strTime_Long_UsedKey; //time_long_used
	BSTR m_strIndex_TestKey; //index_test
	BSTR m_strTm_BeginKey; //tm_begin
	BSTR m_strTm_EndKey; //tm_end
	BSTR m_strIndex_Bench_TestappKey; //index_bench_testapp
	BSTR m_strModel_TestappKey; //model_testapp
	BSTR m_strSn_TestappKey; //sn_testapp
	BSTR m_strIndex_Test_DeviceKey; //index_test_device
	BSTR m_strSn_DeviceKey; //sn_device
	BSTR m_strIndex_Test_TaskKey; //index_test_task
	BSTR m_strIndex_Item_RsltKey; //Index_item_rslt
	BSTR m_strName_Item_PathKey; //name_item_path
	BSTR m_strId_Item_PathKey; //id_item_path
	BSTR m_strIndex_ItemKey; //index_item
	BSTR m_strRsltjdgKey; //rsltjdg
	BSTR m_strRsltdscKey; //rsltdsc
	BSTR m_strFile_PkgsKey; //file_pkgs
	BSTR m_strSelect_StateKey; //select_state
	BSTR m_strFile_Pkgs_SKey; //file_pkgs_s
	BSTR m_strIndex_Device_TestKey; //index_device_test
	BSTR m_strPdf_FileKey; //pdf_file
	BSTR m_strGbrpt_FileKey; //gbrpt_file
	BSTR m_strRpt_Data_FileKey; //rpt_data_file
	BSTR m_strRpt_Data_File_FormatKey; //rpt_data_file_format
	BSTR m_strTestapp_UsedKey; //testapp_used
	BSTR m_strPcap_FileKey; //pcap_file
	BSTR m_strReport_ResultKey; //report_result
	BSTR m_strPdf_File_SKey; //pdf_file_s
	BSTR m_strGbrpt_File_SKey; //gbrpt_file_s
	BSTR m_strRpt_Data_File_SKey; //rpt_data_file_s
	BSTR m_strPcap_File_SKey; //pcap_file_s
	BSTR m_strIndex_RptexKey; //index_rptex
	BSTR m_strIndex_Test_TestappKey; //index_test_testapp
	BSTR m_strIndex_Model_DirKey; //index_model_dir
	BSTR m_strIndex_Merge_ReportKey; //index_merge_report
	BSTR m_strMerge_FileKey; //merge_file
	BSTR m_strMerge_File_SKey; //merge_file_s
	BSTR m_strMerge_IdsKey; //merge_ids
	BSTR m_strIndex_Device_DataKey; //index_device_data
	BSTR m_strData_FormatKey; //data_format
	BSTR m_strDataKey; //data
	BSTR m_strIs_WarningKey; //is_warning
	BSTR m_strIndex_LogKey; //index_log
	BSTR m_strTxt_LogKey; //txt_log
	BSTR m_strUser_IdKey; //user_id
	BSTR m_strDept_IdKey; //dept_id
	BSTR m_strUser_NameKey; //user_name
	BSTR m_strNick_NameKey; //nick_name
	BSTR m_strUser_TypeKey; //user_type
	BSTR m_strEmailKey; //email
	BSTR m_strPhonenumberKey; //phonenumber
	BSTR m_strSexKey; //sex
	BSTR m_strAvatarKey; //avatar
	BSTR m_strPasswordKey; //password
	BSTR m_strStatusKey; //status
	BSTR m_strDel_FlagKey; //del_flag
	BSTR m_strLogin_IpKey; //login_ip
	BSTR m_strLogin_DateKey; //login_date
	BSTR m_strCreate_ByKey; //create_by
	BSTR m_strUpdate_ByKey; //update_by
	BSTR m_strUpdate_TimeKey; //update_time
	BSTR m_strRemarkKey; //remark

public:
	static BSTR CSys_UserKey()  {   return g_pXmlKeys->m_strCSys_UserKey;  }
	static BSTR CSys_UsersKey()  {   return g_pXmlKeys->m_strCSys_UsersKey;  }
	static BSTR CIot_LogsKey()  {   return g_pXmlKeys->m_strCIot_LogsKey;  }
	static BSTR CIot_LogKey()  {   return g_pXmlKeys->m_strCIot_LogKey;  }
	static BSTR CIot_RtDeviceDatasKey()  {   return g_pXmlKeys->m_strCIot_RtDeviceDatasKey;  }
	static BSTR CIot_RtDeviceDataKey()  {   return g_pXmlKeys->m_strCIot_RtDeviceDataKey;  }
	static BSTR CIot_DeviceMergeReportKey()  {   return g_pXmlKeys->m_strCIot_DeviceMergeReportKey;  }
	static BSTR CIot_DeviceMergeReportsKey()  {   return g_pXmlKeys->m_strCIot_DeviceMergeReportsKey;  }
	static BSTR CIot_DeviceModelDirKey()  {   return g_pXmlKeys->m_strCIot_DeviceModelDirKey;  }
	static BSTR CIot_DeviceModelDirsKey()  {   return g_pXmlKeys->m_strCIot_DeviceModelDirsKey;  }
	static BSTR CIot_TestTaskTestappsKey()  {   return g_pXmlKeys->m_strCIot_TestTaskTestappsKey;  }
	static BSTR CIot_TestTaskTestappKey()  {   return g_pXmlKeys->m_strCIot_TestTaskTestappKey;  }
	static BSTR CIot_Device_ClassifysKey()  {   return g_pXmlKeys->m_strCIot_Device_ClassifysKey;  }
	static BSTR CIot_Device_ClassifyKey()  {   return g_pXmlKeys->m_strCIot_Device_ClassifyKey;  }
	static BSTR CIot_DeviceReportExKey()  {   return g_pXmlKeys->m_strCIot_DeviceReportExKey;  }
	static BSTR CIot_DeviceReportExsKey()  {   return g_pXmlKeys->m_strCIot_DeviceReportExsKey;  }
	static BSTR CIot_DeviceTestKey()  {   return g_pXmlKeys->m_strCIot_DeviceTestKey;  }
	static BSTR CIot_DeviceTestsKey()  {   return g_pXmlKeys->m_strCIot_DeviceTestsKey;  }
	static BSTR CIot_DeviceItemRsltKey()  {   return g_pXmlKeys->m_strCIot_DeviceItemRsltKey;  }
	static BSTR CIot_DeviceItemRsltsKey()  {   return g_pXmlKeys->m_strCIot_DeviceItemRsltsKey;  }
	static BSTR CIot_TestTaskDeviceKey()  {   return g_pXmlKeys->m_strCIot_TestTaskDeviceKey;  }
	static BSTR CIot_TestTaskDevicesKey()  {   return g_pXmlKeys->m_strCIot_TestTaskDevicesKey;  }
	static BSTR CIot_BenchTestAppKey()  {   return g_pXmlKeys->m_strCIot_BenchTestAppKey;  }
	static BSTR CIot_BenchTestAppsKey()  {   return g_pXmlKeys->m_strCIot_BenchTestAppsKey;  }
	static BSTR CIot_BenchKey()  {   return g_pXmlKeys->m_strCIot_BenchKey;  }
	static BSTR CIot_BenchsKey()  {   return g_pXmlKeys->m_strCIot_BenchsKey;  }
	static BSTR CIot_TemplateFolderKey()  {   return g_pXmlKeys->m_strCIot_TemplateFolderKey;  }
	static BSTR CIot_TemplateFoldersKey()  {   return g_pXmlKeys->m_strCIot_TemplateFoldersKey;  }
	static BSTR CIot_Engine_DirKey()  {   return g_pXmlKeys->m_strCIot_Engine_DirKey;  }
	static BSTR CIot_Engine_DirsKey()  {   return g_pXmlKeys->m_strCIot_Engine_DirsKey;  }
	static BSTR CIot_DvmFileKey()  {   return g_pXmlKeys->m_strCIot_DvmFileKey;  }
	static BSTR CIot_DvmFilesKey()  {   return g_pXmlKeys->m_strCIot_DvmFilesKey;  }
	static BSTR CIot_TemplateDocExKey()  {   return g_pXmlKeys->m_strCIot_TemplateDocExKey;  }
	static BSTR CIot_TemplateDocExsKey()  {   return g_pXmlKeys->m_strCIot_TemplateDocExsKey;  }
	static BSTR CIot_TemplateKey()  {   return g_pXmlKeys->m_strCIot_TemplateKey;  }
	static BSTR CIot_EngineKey()  {   return g_pXmlKeys->m_strCIot_EngineKey;  }
	static BSTR CIot_EnginesKey()  {   return g_pXmlKeys->m_strCIot_EnginesKey;  }
	static BSTR CIot_TestAppKey()  {   return g_pXmlKeys->m_strCIot_TestAppKey;  }
	static BSTR CIot_TestAppsKey()  {   return g_pXmlKeys->m_strCIot_TestAppsKey;  }
	static BSTR CIot_DeviceKey()  {   return g_pXmlKeys->m_strCIot_DeviceKey;  }
	static BSTR CIot_DevicesKey()  {   return g_pXmlKeys->m_strCIot_DevicesKey;  }
	static BSTR CIot_FactoryKey()  {   return g_pXmlKeys->m_strCIot_FactoryKey;  }
	static BSTR CIot_FactorysKey()  {   return g_pXmlKeys->m_strCIot_FactorysKey;  }
	static BSTR CIot_DeviceClassifyTypeKey()  {   return g_pXmlKeys->m_strCIot_DeviceClassifyTypeKey;  }
	static BSTR CIot_DeviceClassifyTypesKey()  {   return g_pXmlKeys->m_strCIot_DeviceClassifyTypesKey;  }
	static BSTR CIot_UserRoleKey()  {   return g_pXmlKeys->m_strCIot_UserRoleKey;  }
	static BSTR CIot_UserRolesKey()  {   return g_pXmlKeys->m_strCIot_UserRolesKey;  }
	static BSTR CIot_RoleRightKey()  {   return g_pXmlKeys->m_strCIot_RoleRightKey;  }
	static BSTR CIot_RoleRightsKey()  {   return g_pXmlKeys->m_strCIot_RoleRightsKey;  }
	static BSTR CIot_RightKey()  {   return g_pXmlKeys->m_strCIot_RightKey;  }
	static BSTR CIot_RightsKey()  {   return g_pXmlKeys->m_strCIot_RightsKey;  }
	static BSTR CIot_RoleKey()  {   return g_pXmlKeys->m_strCIot_RoleKey;  }
	static BSTR CIot_RolesKey()  {   return g_pXmlKeys->m_strCIot_RolesKey;  }
	static BSTR CIot_UserKey()  {   return g_pXmlKeys->m_strCIot_UserKey;  }
	static BSTR CIot_UsersKey()  {   return g_pXmlKeys->m_strCIot_UsersKey;  }
	static BSTR CIot_DeptKey()  {   return g_pXmlKeys->m_strCIot_DeptKey;  }
	static BSTR CIot_DeptsKey()  {   return g_pXmlKeys->m_strCIot_DeptsKey;  }
	static BSTR Index_DeptKey()  {   return g_pXmlKeys->m_strIndex_DeptKey;  }
	static BSTR Index_Parent_DeptKey()  {   return g_pXmlKeys->m_strIndex_Parent_DeptKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR Index_UserKey()  {   return g_pXmlKeys->m_strIndex_UserKey;  }
	static BSTR Name_LoginKey()  {   return g_pXmlKeys->m_strName_LoginKey;  }
	static BSTR Psw_LoginKey()  {   return g_pXmlKeys->m_strPsw_LoginKey;  }
	static BSTR Index_RoleKey()  {   return g_pXmlKeys->m_strIndex_RoleKey;  }
	static BSTR DescriptionKey()  {   return g_pXmlKeys->m_strDescriptionKey;  }
	static BSTR Val_RightKey()  {   return g_pXmlKeys->m_strVal_RightKey;  }
	static BSTR Index_RolerightKey()  {   return g_pXmlKeys->m_strIndex_RolerightKey;  }
	static BSTR Index_UsrroleKey()  {   return g_pXmlKeys->m_strIndex_UsrroleKey;  }
	static BSTR Index_Device_TypeKey()  {   return g_pXmlKeys->m_strIndex_Device_TypeKey;  }
	static BSTR DeviceclassifyKey()  {   return g_pXmlKeys->m_strDeviceclassifyKey;  }
	static BSTR CodeKey()  {   return g_pXmlKeys->m_strCodeKey;  }
	static BSTR Index_Device_ClassifyKey()  {   return g_pXmlKeys->m_strIndex_Device_ClassifyKey;  }
	static BSTR Index_FactoryKey()  {   return g_pXmlKeys->m_strIndex_FactoryKey;  }
	static BSTR Index_DeviceKey()  {   return g_pXmlKeys->m_strIndex_DeviceKey;  }
	static BSTR Index_DevicetypeKey()  {   return g_pXmlKeys->m_strIndex_DevicetypeKey;  }
	static BSTR Index_EngineKey()  {   return g_pXmlKeys->m_strIndex_EngineKey;  }
	static BSTR ModelKey()  {   return g_pXmlKeys->m_strModelKey;  }
	static BSTR SnKey()  {   return g_pXmlKeys->m_strSnKey;  }
	static BSTR PortKey()  {   return g_pXmlKeys->m_strPortKey;  }
	static BSTR IpKey()  {   return g_pXmlKeys->m_strIpKey;  }
	static BSTR Dvm_FileKey()  {   return g_pXmlKeys->m_strDvm_FileKey;  }
	static BSTR Test_StateKey()  {   return g_pXmlKeys->m_strTest_StateKey;  }
	static BSTR Index_Device_DirKey()  {   return g_pXmlKeys->m_strIndex_Device_DirKey;  }
	static BSTR Dvm_File_SKey()  {   return g_pXmlKeys->m_strDvm_File_SKey;  }
	static BSTR Index_TestappKey()  {   return g_pXmlKeys->m_strIndex_TestappKey;  }
	static BSTR Index_Device_Classify_TypeKey()  {   return g_pXmlKeys->m_strIndex_Device_Classify_TypeKey;  }
	static BSTR StateKey()  {   return g_pXmlKeys->m_strStateKey;  }
	static BSTR Index_FolderKey()  {   return g_pXmlKeys->m_strIndex_FolderKey;  }
	static BSTR Engine_IdKey()  {   return g_pXmlKeys->m_strEngine_IdKey;  }
	static BSTR Rule_IdKey()  {   return g_pXmlKeys->m_strRule_IdKey;  }
	static BSTR Protocol_FileKey()  {   return g_pXmlKeys->m_strProtocol_FileKey;  }
	static BSTR Comm_TypeKey()  {   return g_pXmlKeys->m_strComm_TypeKey;  }
	static BSTR Index_Engine_DirKey()  {   return g_pXmlKeys->m_strIndex_Engine_DirKey;  }
	static BSTR Protocol_File_SKey()  {   return g_pXmlKeys->m_strProtocol_File_SKey;  }
	static BSTR Create_TimeKey()  {   return g_pXmlKeys->m_strCreate_TimeKey;  }
	static BSTR Index_TemplateKey()  {   return g_pXmlKeys->m_strIndex_TemplateKey;  }
	static BSTR Template_FileKey()  {   return g_pXmlKeys->m_strTemplate_FileKey;  }
	static BSTR Iecfg_FileKey()  {   return g_pXmlKeys->m_strIecfg_FileKey;  }
	static BSTR Gbxml_FileKey()  {   return g_pXmlKeys->m_strGbxml_FileKey;  }
	static BSTR Doc_FileKey()  {   return g_pXmlKeys->m_strDoc_FileKey;  }
	static BSTR Xml_FileKey()  {   return g_pXmlKeys->m_strXml_FileKey;  }
	static BSTR Tm_UpdateKey()  {   return g_pXmlKeys->m_strTm_UpdateKey;  }
	static BSTR Cnt_File_Doc_ExKey()  {   return g_pXmlKeys->m_strCnt_File_Doc_ExKey;  }
	static BSTR VersionKey()  {   return g_pXmlKeys->m_strVersionKey;  }
	static BSTR File_ReportKey()  {   return g_pXmlKeys->m_strFile_ReportKey;  }
	static BSTR Template_File_SKey()  {   return g_pXmlKeys->m_strTemplate_File_SKey;  }
	static BSTR Iecfg_File_SKey()  {   return g_pXmlKeys->m_strIecfg_File_SKey;  }
	static BSTR Gbxml_File_SKey()  {   return g_pXmlKeys->m_strGbxml_File_SKey;  }
	static BSTR Doc_File_SKey()  {   return g_pXmlKeys->m_strDoc_File_SKey;  }
	static BSTR Xml_File_SKey()  {   return g_pXmlKeys->m_strXml_File_SKey;  }
	static BSTR File_Report_SKey()  {   return g_pXmlKeys->m_strFile_Report_SKey;  }
	static BSTR Index_Template_DocKey()  {   return g_pXmlKeys->m_strIndex_Template_DocKey;  }
	static BSTR Doc_RptfileKey()  {   return g_pXmlKeys->m_strDoc_RptfileKey;  }
	static BSTR Doc_Rptfile_SKey()  {   return g_pXmlKeys->m_strDoc_Rptfile_SKey;  }
	static BSTR Index_DvmfileKey()  {   return g_pXmlKeys->m_strIndex_DvmfileKey;  }
	static BSTR Parent_IndexKey()  {   return g_pXmlKeys->m_strParent_IndexKey;  }
	static BSTR Dir_NameKey()  {   return g_pXmlKeys->m_strDir_NameKey;  }
	static BSTR Index_Parent_FolderKey()  {   return g_pXmlKeys->m_strIndex_Parent_FolderKey;  }
	static BSTR Tm_CreateKey()  {   return g_pXmlKeys->m_strTm_CreateKey;  }
	static BSTR Index_BenchKey()  {   return g_pXmlKeys->m_strIndex_BenchKey;  }
	static BSTR Sn_BenchKey()  {   return g_pXmlKeys->m_strSn_BenchKey;  }
	static BSTR Test_TypeKey()  {   return g_pXmlKeys->m_strTest_TypeKey;  }
	static BSTR Index_TesterKey()  {   return g_pXmlKeys->m_strIndex_TesterKey;  }
	static BSTR Time_Long_Total_TestKey()  {   return g_pXmlKeys->m_strTime_Long_Total_TestKey;  }
	static BSTR Time_Long_UsedKey()  {   return g_pXmlKeys->m_strTime_Long_UsedKey;  }
	static BSTR Index_TestKey()  {   return g_pXmlKeys->m_strIndex_TestKey;  }
	static BSTR Tm_BeginKey()  {   return g_pXmlKeys->m_strTm_BeginKey;  }
	static BSTR Tm_EndKey()  {   return g_pXmlKeys->m_strTm_EndKey;  }
	static BSTR Index_Bench_TestappKey()  {   return g_pXmlKeys->m_strIndex_Bench_TestappKey;  }
	static BSTR Model_TestappKey()  {   return g_pXmlKeys->m_strModel_TestappKey;  }
	static BSTR Sn_TestappKey()  {   return g_pXmlKeys->m_strSn_TestappKey;  }
	static BSTR Index_Test_DeviceKey()  {   return g_pXmlKeys->m_strIndex_Test_DeviceKey;  }
	static BSTR Sn_DeviceKey()  {   return g_pXmlKeys->m_strSn_DeviceKey;  }
	static BSTR Index_Test_TaskKey()  {   return g_pXmlKeys->m_strIndex_Test_TaskKey;  }
	static BSTR Index_Item_RsltKey()  {   return g_pXmlKeys->m_strIndex_Item_RsltKey;  }
	static BSTR Name_Item_PathKey()  {   return g_pXmlKeys->m_strName_Item_PathKey;  }
	static BSTR Id_Item_PathKey()  {   return g_pXmlKeys->m_strId_Item_PathKey;  }
	static BSTR Index_ItemKey()  {   return g_pXmlKeys->m_strIndex_ItemKey;  }
	static BSTR RsltjdgKey()  {   return g_pXmlKeys->m_strRsltjdgKey;  }
	static BSTR RsltdscKey()  {   return g_pXmlKeys->m_strRsltdscKey;  }
	static BSTR File_PkgsKey()  {   return g_pXmlKeys->m_strFile_PkgsKey;  }
	static BSTR Select_StateKey()  {   return g_pXmlKeys->m_strSelect_StateKey;  }
	static BSTR File_Pkgs_SKey()  {   return g_pXmlKeys->m_strFile_Pkgs_SKey;  }
	static BSTR Index_Device_TestKey()  {   return g_pXmlKeys->m_strIndex_Device_TestKey;  }
	static BSTR Pdf_FileKey()  {   return g_pXmlKeys->m_strPdf_FileKey;  }
	static BSTR Gbrpt_FileKey()  {   return g_pXmlKeys->m_strGbrpt_FileKey;  }
	static BSTR Rpt_Data_FileKey()  {   return g_pXmlKeys->m_strRpt_Data_FileKey;  }
	static BSTR Rpt_Data_File_FormatKey()  {   return g_pXmlKeys->m_strRpt_Data_File_FormatKey;  }
	static BSTR Testapp_UsedKey()  {   return g_pXmlKeys->m_strTestapp_UsedKey;  }
	static BSTR Pcap_FileKey()  {   return g_pXmlKeys->m_strPcap_FileKey;  }
	static BSTR Report_ResultKey()  {   return g_pXmlKeys->m_strReport_ResultKey;  }
	static BSTR Pdf_File_SKey()  {   return g_pXmlKeys->m_strPdf_File_SKey;  }
	static BSTR Gbrpt_File_SKey()  {   return g_pXmlKeys->m_strGbrpt_File_SKey;  }
	static BSTR Rpt_Data_File_SKey()  {   return g_pXmlKeys->m_strRpt_Data_File_SKey;  }
	static BSTR Pcap_File_SKey()  {   return g_pXmlKeys->m_strPcap_File_SKey;  }
	static BSTR Index_RptexKey()  {   return g_pXmlKeys->m_strIndex_RptexKey;  }
	static BSTR Index_Test_TestappKey()  {   return g_pXmlKeys->m_strIndex_Test_TestappKey;  }
	static BSTR Index_Model_DirKey()  {   return g_pXmlKeys->m_strIndex_Model_DirKey;  }
	static BSTR Index_Merge_ReportKey()  {   return g_pXmlKeys->m_strIndex_Merge_ReportKey;  }
	static BSTR Merge_FileKey()  {   return g_pXmlKeys->m_strMerge_FileKey;  }
	static BSTR Merge_File_SKey()  {   return g_pXmlKeys->m_strMerge_File_SKey;  }
	static BSTR Merge_IdsKey()  {   return g_pXmlKeys->m_strMerge_IdsKey;  }
	static BSTR Index_Device_DataKey()  {   return g_pXmlKeys->m_strIndex_Device_DataKey;  }
	static BSTR Data_FormatKey()  {   return g_pXmlKeys->m_strData_FormatKey;  }
	static BSTR DataKey()  {   return g_pXmlKeys->m_strDataKey;  }
	static BSTR Is_WarningKey()  {   return g_pXmlKeys->m_strIs_WarningKey;  }
	static BSTR Index_LogKey()  {   return g_pXmlKeys->m_strIndex_LogKey;  }
	static BSTR Txt_LogKey()  {   return g_pXmlKeys->m_strTxt_LogKey;  }
	static BSTR User_IdKey()  {   return g_pXmlKeys->m_strUser_IdKey;  }
	static BSTR Dept_IdKey()  {   return g_pXmlKeys->m_strDept_IdKey;  }
	static BSTR User_NameKey()  {   return g_pXmlKeys->m_strUser_NameKey;  }
	static BSTR Nick_NameKey()  {   return g_pXmlKeys->m_strNick_NameKey;  }
	static BSTR User_TypeKey()  {   return g_pXmlKeys->m_strUser_TypeKey;  }
	static BSTR EmailKey()  {   return g_pXmlKeys->m_strEmailKey;  }
	static BSTR PhonenumberKey()  {   return g_pXmlKeys->m_strPhonenumberKey;  }
	static BSTR SexKey()  {   return g_pXmlKeys->m_strSexKey;  }
	static BSTR AvatarKey()  {   return g_pXmlKeys->m_strAvatarKey;  }
	static BSTR PasswordKey()  {   return g_pXmlKeys->m_strPasswordKey;  }
	static BSTR StatusKey()  {   return g_pXmlKeys->m_strStatusKey;  }
	static BSTR Del_FlagKey()  {   return g_pXmlKeys->m_strDel_FlagKey;  }
	static BSTR Login_IpKey()  {   return g_pXmlKeys->m_strLogin_IpKey;  }
	static BSTR Login_DateKey()  {   return g_pXmlKeys->m_strLogin_DateKey;  }
	static BSTR Create_ByKey()  {   return g_pXmlKeys->m_strCreate_ByKey;  }
	static BSTR Update_ByKey()  {   return g_pXmlKeys->m_strUpdate_ByKey;  }
	static BSTR Update_TimeKey()  {   return g_pXmlKeys->m_strUpdate_TimeKey;  }
	static BSTR RemarkKey()  {   return g_pXmlKeys->m_strRemarkKey;  }
};



class CNR_IOTMNGRConstGlobal
{
private:
	CNR_IOTMNGRConstGlobal();
	virtual ~CNR_IOTMNGRConstGlobal();

public:
	static CNR_IOTMNGRConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CNR_IOTMNGRConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
