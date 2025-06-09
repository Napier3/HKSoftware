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
����ģ����񣬴���ģ����ص��������Զ����Կ����޹ص����񣩣�
����ģ��
����������Ϣ
������Ʒ��Ϣ
��������
*/

class CAtsSvr_TemplateService
{
public:
	CAtsSvr_TemplateService(void);
	virtual ~CAtsSvr_TemplateService(void);

public:
	//CParse_TaskInfo m_oTaskInfoParser;     //�����飨������Ϣ��word�ļ�����������
	//CParse_SampleInfo m_oSampleInfoParser;  //��Ʒ��Ϣ����Ʒ�б�������������Ϣ��excel�ļ�����������


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

	//����ļ����ء��ϴ�
	BOOL DownLoadFile_Template_RptFile(const CString &strFileName, CString &strFileDownLoad);  //����ģ���ļ��ͱ���ģ���ļ������������صĲ���ģ���ȫ·��
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

	//�����û�ID����ѯ�û���
	BOOL QueryUserByUserID(long nUser_ID, CString &strName_User);

	//����ģ����С��д�����ݿ�
	BOOL DB_InsertTemplateItems(const CString &strFileName, CExBaseList *pListItems);  //ģ����Ŀ�����+ģ����Ŀ���������
 	CIot_TemplateItems* DB_InsertTemplateItems_Items(long nIndex_Template, CExBaseList *pItems);
 	CIot_TemplateItem* DB_InsertTemplateItems_Item(long nIndex_Template, long nIndex_Items, CExBaseList *pItem);
	BOOL DB_Insert_IotItems(CExBaseList *pListItems);    //��Ŀ�����ܱ�
 
	//������Ϣ���������������Ϣд�����ݿ�
	CIot_TypeTask* DB_InsertTypeTask(CDataGroup *pTaskBasicInfo, const CString &strTaskFileName, const CString &strTaskFile_s, const CString &strID_User);
	CIot_TypeTask* DB_UpdateTypeTask(long nIndex_TypeTask, CDataGroup *pTaskBasicInfo, const CString &strTaskFileName
	, const CString &strTaskFile_s);
	BOOL DB_InsertTypeTask_Standard(long nIndex_TypeTask, CDataGroup *pInspectionBases);

	//������Ʒ��Ϣд�����ݿ�
	BOOL DB_InsertTypeTask_Devs(long nIndex_TypeTask, CDataGroup *pSampleDevices);
	BOOL DB_InsertTypeTask_RatedParameter(long nIndex_TypeTask, CDataGroup *pRatedParameter);
	BOOL DB_InsertTypeTask_DevDvm(long nIndex_TypeTask, CDataGroup *pDevDvm);
	BOOL DB_InsertDeviceModel(const CString &strFile, const CString &strFile_s);
};
