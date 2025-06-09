#pragma once


#include "..\..\..\Module\BaseClass\ExBaseList.h"
#include "../AutoTestXMLRWKeys.h"
#include "..\..\..\Module\XfileMngrBase\XFolder.h"
#include "../GuideBook\GuideBook.h"
#include "../TaskMngr\TestTask.h"
#include "../TCtrlCntrDefine.h"
#include "../TaskMngr\TestGlobalDefine.h"
#include "..\..\..\Module\QRCode\QRCodeRead.h"

#include "../AtsRpc\AtsRpcServerGlobalApi.h"

//2023-3-26  lijunqing ͨ�Ų��֣�ʹ��ͨ�ŷ�����޸�
#include "../../../SttStudio/Module/SmartTestInterface/PpSttCommConfig.h"

#define use_AtsNewTestTool

class CDlgNewTestProjectExInterface
{
public:
	virtual void OnTvnSelchangedTreeGuidebook(CExBaseObject *pGbSel) = 0;
};

class CAtsNewTestTool : public CExBaseObject
{
private:
	CAtsNewTestTool();
	virtual ~CAtsNewTestTool();

	static CAtsNewTestTool* g_pAtsNewTestTool;
	static long g_nAtsNewTestToolRef;
	

public:
	static CAtsNewTestTool* Create();
	static void Release();

	void InitAtsNewTestTool(UINT nNewMode, CXFolder *pXCurrFolder, CTestTasks *pTestTasks = NULL);
	CString GetXTestDbGroupPath();
	DWORD GetReportType();
	BOOL IsUseQRCode();
	
public:
	CTestTypes *m_pTestTypes;
	//�����ݿ��ȡ�Ĳ�������
	CTestTasks m_oTasksFromXDb;
	CXFolder *m_pXCurrFolder;

	CString m_strEngineMode;   //shaolei 2023-11-2
	CString m_strPpEngineProgID;
	CString m_strDeviceFile;
	CString m_strPpTemplateFile;
	CString m_strTemplateFile;
	DWORD   m_dwTkID_Index;       //��ǰ�Ĳ�������
	CString m_strTestType;

	CGuideBook *m_pTempGuideBook;
	CString m_strPrevExpandFile;
	CDvmDataset m_oExpandDatas;
	UINT  m_nNewMode;

	CTestTask *m_pTestTask;
	CTestTasks *m_pTestTasks;
	BOOL m_bTestTasksAttach;

	DWORD m_dwReportType;
	CString m_strGuideBookFile;
	CString m_strTestProjectName;

	//MdvMgrp
	CTestGlobalDefine m_oTestGlobalDefine;
	CDvmDataset *m_pExpandDatas;
	CDvmDataset *m_pExpandDatasAutoSet;
	CDvmDataset *m_pReportSNGen;
	CDvmDataset *m_pTaskReportSNGen;
	CDvmDataset *m_pDeviceAttrsDefine;
	CDvmDataset *m_pTestAppDefine;
	CString m_strMacroFileID;

// 	CDvmDataset *m_pTestAppDefine;
	CDvmDataset *m_pTestApp;
	CDataGroup *m_pTestApps;  //ͨ�ò��������ö���
	CTestMacrosFile *m_pTestMacrosFile;
	CDvmDataset *m_pInspectionBases;  //�����׼  shaolei
	CDvmDataset *m_pTesters;  //������Ա  shaolei
	CDvmDataset *m_pGlobalDatas;  //ȫ������  shaolei

	//2021-1-6  lijunqing 
	CStringArray m_astrDvmFiles;  //ģ���ļ�
	BOOL m_bHasLink_TestApp;
	BOOL m_bHasLink_Device;
	CString m_strIP_TestApp, m_strIP_Device;
	CString m_strMsg_IP_Err;

public:
	BOOL IsAuthority();
	BOOL IsOfflineTestMode();
	void InitByGuideBookFile(const CString &strFile);
	void SetEngineProgID(const CString &strEngineProgID);
	void SetEngineMode(const CString &strEngineMode);
	void MdvMgrpTest_InsertDevices(const CString &strPpTemplateFile, const CString &strDevice, long nDvNum);

	//shaolei 20210911
	void MdvMgrpTest_InsertIotDevices(const CString &strTemplate, const CString &strDevice, long nDvNum);
	void MdvMgrpTest_InsertPpDevices(const CString &strTemplate, const CString &strDevice, long nDvNum);
	void MdvMgrpTest_InsertPpDevices(CTestTasks *pSrcTestTasks);
	void MdvMgrpTest_InsertMmsDevices(const CString &strDvmFile, long nDvNum);
	void MdvMgrpTest_InsertMmsDevices(CTestTasks *pTestTasks);
	CDvmData* TestApp_AddTestApp(CValues *pValues);
	CDvmData* TestApp_AddTestApp(CDvmDataset *pTestAppDef);
	CDvmData* TestApp_AddTestApp(CDvmData *pTestApp);
	CDvmData* TestApp_AddTestApp(CDataGroup *pTestApp);
	void BeforeCreate(const CString &strTestType);
	CString GetSrcDeviceModelFile();
	CString XPing_IP(const CString &strIP_TestApp, const CString &strIP_Device);
	//shaolei  20211022
	void UpdateTestDefine(CExBaseList *pList, CDvmDataset *pTestDef);

public:
	CTestTask* GetTestTask()		{	ASSERT (m_pTestTask != NULL);	return m_pTestTask;	}
	CTestTasks* GetTestTasks()	{	ASSERT (m_pTestTasks != NULL);	return m_pTestTasks;	};
	void SetTestType(const CString &strTestType);

	void InitExpandMode();
	void InitProjectName(CAtsTestDefineInterface *pAtsTestDefine=NULL);

	long GetExpandDataCount();
	BOOL IsMgbrptMode();
	CTestTypes* GetGbTestTypes();
	BOOL CanCreateMdTask(CString &strMsg);
	void SetGuideBookFile(const CString &strFile);
	CTestProject* InsertNewTestProject(CWnd *pWnd);
	BOOL OnBnClickedBtnDvmfile(CTestProject *pProject, CWnd *pWnd);
	BOOL OnBnClickedBtnImport(CWnd *pWnd);
	void OnBnClickedBtnExport(CWnd *pWnd);

	BOOL CanCreateSdvMppTask(CString &strMsg);
	CTestProject* SdvMppTest_OnBnClickedBtnInsert(CWnd *pWnd);
	BOOL SdvMppTest_OnBnClickedBtnImport(CWnd *pWnd);
	void SdvMppTest_OnBnClickedBtnExport(CWnd *pWnd);

	//////////////////////////////////////////////////////////////////////////
	BOOL MdvMgrpTest_InitExpandMode(const CString &strExpandFile);
	BOOL MdvMgrpTest_OnBnClickedBtnImport(CWnd *pWnd);
	void MdvMgrpTest_OnBnClickedBtnExport(CWnd *pWnd);

	void InsertPpDevicesCmmConfig(CDeviceCmmConfig *pCmmConfig);
	void InsertPpDevicesCmmConfig_Serial(CCmmSerialConfig *pCmmConfig);
	void InsertPpDevicesCmmConfig_Net(CCmmNetConfig *pCmmConfig);
	void InsertPpDevicesCmmConfig_Mms(CCmmMmsConfig *pCmmConfig);
	
	void AutoSetExpandDatas(CTestTask *pTestTask);
	void ReportSNGenClear();
	void ReportSNGen();
	void SetShowWordRpt(DWORD dwRptType);
	CTestTask* MdvMgrpTest_OnQRCodeInput();
	void MdvMgrpTest_OnBnClickedBtnDeleteall();
	void TestApp_InitExpandMode(CDvmDataset *pTestAppDefine);

public:
	void InitByAtsRpcTestDefine(CAtsTestDefineInterface *pAtsTestDefine, CXFolder *pFolder);

private:
	void InitByAtsRpcTestDef_AddTestApp(CAtsTestDefineInterface *pAtsTestDefine);
	void InitByAtsRpcTestDef_AddDevices(CAtsTestDefineInterface *pAtsTestDefine);
	void InitByAtsRpcTestDef_AddDevice_Attrs(CAtsTestDefineInterface *pAtsTestDefine);
	void InitByAtsRpcTestDef_AddDevice_Attrs(CDvmDataset *pDeviceAttrs, CDvmData *pAtsRpcDevice);
	void InitByAtsRpcTestDef_AddDevice_Attrs(CDvmDataset *pDeviceAttrs, CDataGroup *pAtsDevice);
	void InitByAtsRpcTestDef_AddDevice_Attr(CDvmDataset *pDeviceAttrs, CDvmValue *pAtsRpcAttr);

	void InitByAtsRpcTestDef_AddDevices_MMS(CAtsTestDefineInterface *pAtsTestDefine);
	//shaolei 2023-11-3
	void MdvMgrpTest_InitDvm_Ppxml(CAtsTestDefineInterface *pAtsTestDefine);

	void InitByAtsRpcTestDef_InitCmmConfig_MMS(CDeviceCmmConfig *pCmmConfig, CDvmData *pData);
	void InitByAtsRpcTestDef_InitCmmConfig_MMS(CDeviceCmmConfig *pCmmConfig, CDataGroup *pDataGroup);

	void InitByAtsRpcTestDef_AddDevices_PP(CAtsTestDefineInterface *pAtsTestDefine);
	void InitByAtsRpcTestDef_AddDevices_PP_Net(CAtsTestDefineInterface *pAtsTestDefine, CExBaseList &listTask);
	void InitByAtsRpcTestDef_AddDevices_PP_Serial(CAtsTestDefineInterface *pAtsTestDefine, CExBaseList &listTask);
	void InitAtsRpcTestTaskName(CAtsTestDefineInterface *pAtsTestDefine, CExBaseList &listTask);
	void InitByAtsRpcTestDef_AddDevices_Iot(CAtsTestDefineInterface *pAtsTestDefine);
	//shaolei  20210911
	void InitByAtsRpcTestDef_AddDevices_Iot(CAtsTestDefineInterface *pAtsTestDefine, CExBaseList &listTask);

	//shaolei 20211015
	void InitByAtsRpcTestDef_AddInspectionBases(CAtsTestDefineInterface *pAtsTestDefine);   //��Ӽ����׼
	void InitByAtsRpcTestDef_AddTesters(CAtsTestDefineInterface *pAtsTestDefine);   //��Ӽ���Ա
	void InitByAtsRpcTestDef_AddGlobalDatas(CAtsTestDefineInterface *pAtsTestDefine);   //�������ȫ������	
	void InitByAtsRpcTestDef_AddGlobalDatas(CDataGroup *pGroupDatas);

//2021-4-4  lijunqing  
public:
	BOOL HasLogic();

public:
	//2021-10-1  lijunqing
	static void InitGuideBookAttrs(CGuideBook *pGuideBook);
	static void InitTasksPpEngineProgID();
	static void InitTasksEngineMode();  //shaolei 2023-11-2

//2023-3-26  lijunqing ͨ�Ų��֣�ʹ��ͨ�ŷ�����޸�
//ͨ�����ö���ʹ��CPpSttCommConfig����װ��ģʽ�£���Ա����m_oCommConfig
//��װ��ģʽ�£�Tool��ΪCExBaseList���Ӷ���ΪCPpSttCommConfig����
public:
	CPpSttCommConfig *m_pCommConfig;   //ȫ�ֵ�װ�ö���

	void SetCommConfig(CPpSttCommConfig *pCommConfig);
	void InitCommConfigEngineByProgID();

	//2023-6-17 lijunqing ��ʼ��APP������󣬴������ļ���ȡ
	void InitTestApps();

};

void sdvmpp_UpdateProjectName(CTestProject *pTestProject);

extern CAtsNewTestTool *g_theAtsNewTestTool;

//2021-3-14  lijunqing  
void MdvMgrpTest_UpdateTasksByDvmFile(CTestTasks *pTestTask, const CString &strDvmFile);

//2021-7-31  lijunqing
BOOL Encrypt_CanUseGuideBook(CGuideBook *pGuideBook);
