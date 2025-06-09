#pragma once
#include "..\..\..\SttStudio\Module\Engine\SttEngineInterface.h"
#include "..\..\..\Module\BaseClass\XObjectRefBase.h"
#include "..\..\..\SttStudio\Module\SttCmd\SttAtsCmd.h"
#include "..\..\..\AutoTest\Module\GuideBook\GuideBook.h"
#include "..\Iot_AtsMngrDB\Iot_TemplateItems.h"
#include "..\Iot_AtsMngrDB\Iot_TypeTask.h"
#include "..\Iot_AtsMngrDB\Iot_TypeTaskTest.h"
#include "..\Iot_AtsMngrDB\Iot_TypeTaskDevParas.h"
#include "..\Iot_AtsMngrDB\Iot_TypeTaskDevModel.h"
#include "..\Iot_AtsMngrDB\Iot_TestApp.h"
#include "..\Iot_AtsMngrDB\Iot_TypeTaskDev.h"

/*
测试模板服务，处理模板相关的事务（与自动测试控制无关的事务）：
新增模板
导入任务信息
导入样品信息
导出报告
*/

class CAtsSvr_TemplateService
{
public:
	CAtsSvr_TemplateService(void);
	virtual ~CAtsSvr_TemplateService(void);

public:
	//CParse_TaskInfo m_oTaskInfoParser;     //任务书（任务信息，word文件）解析对象
	//CParse_SampleInfo m_oSampleInfoParser;  //样品信息（样品列表、额定参数、点表信息，excel文件）解析对象


	virtual long Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Process_Cmd_SysState(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol);

	long Process_Cmd_Ats_UploadTemplate(CSttAtsCmd *pAtsCmd);
	long Process_Cmd_Ats_ImportTaskInfo(CSttAtsCmd *pAtsCmd);
	long Process_Cmd_Ats_ImportSampleInfo(CSttAtsCmd *pAtsCmd);
	long Process_Cmd_Ats_ExportReport(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);

	long Process_Cmd_SysState_TestAppEvent(CSttSysState *pSysState);
	long Process_Cmd_SysState_EngineEvent(CSttSysState *pSysState);
	long Process_Cmd_SysState_RTDATA(CSttSysState *pSysState);
	long Process_Cmd_SysState_RTDATA_TestApp(CSttSysState *pSysState, CIot_TestApp *pTestApp);
	long Process_Cmd_SysState_RTDATA_Dev(CSttSysState *pSysState, CIot_TypeTaskDev *pDev);

	BOOL Export_Report(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol, const CString &strDocRptFile, CIot_TypeTaskTests *pListTaskTests);
	BOOL Export_Report(const CString &strDocRptFile, CIot_TypeTaskTest *pTaskTest);

	//相关文件下载、上传
	BOOL DownLoadFile_Template_RptFile(const CString &strFileName, CString &strFileDownLoad);  //下载模板文件和报告模板文件，名返回下载的测试模板的全路径
	BOOL DownLoadFile_Template(CSttAtsCmd *pAtsCmd, CString &strFileDownLoad);
	BOOL DownLoadFile_TaskInfo(CSttAtsCmd *pAtsCmd, CString &strFileDownLoad);
	BOOL DownLoadFile_SampleInfo(CSttAtsCmd *pAtsCmd, CString &strFileDownLoad);
	BOOL UploadFile(const CString &strLocalFilePath, CString &strFile_s);
	BOOL UploadFile_DvmDevice(const CString &strFile, CString &strFile_s);
	BOOL UploadFile_RptFile(const CString &strFile, CString &strFile_s);

	BOOL OpenGbxmlFile(const CString &strFilePath, CExBaseList *pItemsList, CGuideBook *pGuideBook);
	BOOL SaveGbxmlFile_Items(const CString &strFileName, CGuideBook *pGuideBook, CExBaseList *pListItems);
	CDataGroup* ParseFile_TaskInfo(const CString &strTaskInfoFile);
	CDataGroup* ParseFile_SampleInfo(const CString &strSampleInfoFile);
	CString GenerateDevDvm(const CString &strTaskSN, CDataGroup *pRatedParameter, CDataGroup *pDevDvm);
	CString GenerateDevDvm(const CString &strTaskSN, CIot_TypeTaskDevParases *pRatedParas, CIot_TypeTaskDevModels *pDevDvm);

	//根据用户ID，查询用户名
	BOOL QueryUserByUserID(long nUser_ID, CString &strName_User);

	//测试模板大项、小项写入数据库
	BOOL DB_InsertTemplateItems(const CString &strFileName, CExBaseList *pListItems);  //模板项目分类表+模板项目分类子项表
 	CIot_TemplateItems* DB_InsertTemplateItems_Items(long nIndex_Template, CExBaseList *pItems);
 	CIot_TemplateItem* DB_InsertTemplateItems_Item(long nIndex_Template, long nIndex_Items, CExBaseList *pItem);
	BOOL DB_Insert_IotItems(CExBaseList *pListItems);    //项目分类总表
 
	//任务信息、任务检验依据信息写入数据库
	CIot_TypeTask* DB_InsertTypeTask(CDataGroup *pTaskBasicInfo, const CString &strTaskFileName, const CString &strTaskFile_s, const CString &strID_User);
	CIot_TypeTask* DB_UpdateTypeTask(long nIndex_TypeTask, CDataGroup *pTaskBasicInfo, const CString &strTaskFileName
	, const CString &strTaskFile_s);
	BOOL DB_InsertTypeTask_Standard(long nIndex_TypeTask, CDataGroup *pInspectionBases);

	//任务样品信息写入数据库
	BOOL DB_InsertTypeTask_Devs(long nIndex_TypeTask, CDataGroup *pSampleDevices);
	BOOL DB_InsertTypeTask_RatedParameter(long nIndex_TypeTask, CDataGroup *pRatedParameter);
	BOOL DB_InsertTypeTask_DevDvm(long nIndex_TypeTask, CDataGroup *pDevDvm);
	BOOL DB_InsertDeviceModel(const CString &strFile, const CString &strFile_s);
};
