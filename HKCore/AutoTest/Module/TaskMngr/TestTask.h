#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"
#include "TestProject.h"
#include "../TCtrlCntrDefine.h"

#ifndef _PSX_QT_LINUX_			//yyj
#include "../../../Module/Office/msword9.h"
#include "../../../Module/Office/WPS.h"
#include "../../../Module/MfcCtrlEx/ThreadProgrssDlg.h"
#endif

#ifndef GUIDEBOOK_DEV_MODE
#include "../../../Protocol/Module/Engine/DeviceModel/DeviceCmmConfig.h"
#endif

class CTestWzdDefine;
class CTestGlobalDefine;

class CTestTask : public CTestRrptSnGenInterface/*2018-3-13  TestTask add SN*///CExBaseList
{
public:
	CTestTask(void);
	virtual ~CTestTask(void);

public:
	CString m_strLocalID;	//在本地创建任务时，设置此变量
	SYSTEMTIME m_tmPlanBegin;
	SYSTEMTIME m_tmPlanFinish;
	SYSTEMTIME m_tmTestBegin;
	SYSTEMTIME m_tmTestFinish;
	CString m_strLocation;
	CString m_strTestType;
	CString m_strTestState;
	long m_nTestTimeLong;

	CString m_strDeviceFile;
	CString m_strPpEngineProgID;
	CString m_strEngineMode;  //shaolei 2023-11-2

	BOOL m_bDatasetChanged;
	CExBaseList m_listCmmCfg;
	CString m_strMaxMgrpID;
	
	CString m_strDvmTestState;  //模型规范性测试
	CString m_strProtocolTestState;//规约规范性测试

	long m_nSelect;

private:
	CString m_strTemplateFile;
	CString m_strPpTemplateFile;

public:
	//Report SN Gen
	virtual void SetReportSN(const CString &strReportSN);
	virtual CDvmDataset* GetDeviceAttr(BOOL bCreate=TRUE);

public:
	//基本方法
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID()	{		return CLASSID_TESTTASK;	}
	//串行化
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey();

	//WriteXml
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

	//编辑
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();
	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);


	void SetAllSelect(long nSel);
public:
	virtual BOOL OpenTaskFile();
	virtual BOOL OpenTaskFile(const CString &strTaskFile);
	virtual BOOL SaveAs(const CString &strTaskFile);
	virtual BOOL Save(BOOL bPostMsg=FALSE);
	virtual BOOL SaveAs2(const CString &strTaskPath);

protected:
	CString m_strTaskFile;
	CTestProject  *m_pCurrTestProject;
	CDvmDataset *m_pSysParas;   //整个任务的系统参数
	CDvmDataset *m_pCommCmdManyConfig;   //多测试报告的配置

public:
	CDvmDataset *m_pDeviceAttr;   //被测装置的属性

#ifndef GUIDEBOOK_DEV_MODE
	CDeviceCmmConfig* m_pDeviceCmmConfig;
#endif

	BOOL m_bCanTestSysParaEditItem;
	CString m_strTaskType;

	void InitTaskType(const CString &strFile);

public:
	void SetTaskType(const CString &strType);
	CString GetTaskType();

	void AddErrTestItem(CExBaseObject *pItem);
	CTestProject* AddProject(const CString &strFile);
	CTestProject* GetCurrProject()	{	return m_pCurrTestProject;	}
	CTestProject* GetNextProject();
	void SetCurrProject(CTestProject *p)	{	m_pCurrTestProject = p;	}
	CString GetTaskFile()					{	return m_strTaskFile;	}
	void SetCurrProject(const CString &strGbFile);

	CDvmDataset* GetTaskSysParas(BOOL bCreate=TRUE);
	BOOL CanTestSysParaEditItem()	{	return m_bCanTestSysParaEditItem;	}
	void ResetTestSysParaEditItem()	{	m_bCanTestSysParaEditItem = TRUE;	}
	void SetTestSysParaEditItem()	{	m_bCanTestSysParaEditItem = FALSE;	}

#ifndef _not_use_autotest_
	void ExportWordReport(MSWord::_Application &WordApp);
#endif

	void InitAllProject();
	long FindProjectIndex(CTestProject *pProject);
	CTestProject* FindByGbrptFile(const CString &strGbrptFile);
	CTestProject* FindByGbrptFileName(const CString &strGbrptFileName);
	CTestProject* GetTestProjectAtIndex(long nIndex);
	CString GetTaskPath();

#ifndef GUIDEBOOK_DEV_MODE
	CDeviceCmmConfig* GetDeviceCmmConfig();
	void InitDeviceCmmConfig(CDeviceCmmConfig *pSrcCmmConfig);
#endif

	void InitDeviceAttr(CDvmDataset *pSrcDeviceAttrsDef);
	void InitDeviceAttrValue(CDvmDataset *pSrcDeviceAttrsDef);
	void InitDeviceAttrValueEx(CDvmDataset *pSrcDeviceAttrsDef);
	BOOL IsDeviceAttrSame(CDvmDataset *pDeviceAttr);
	BOOL IsDeviceAttrEmpty();
	void EmptyDeviceAttr();

	CDvmDataset* GetCommCmdManyConfig();
	void InitCommCmdManyConfig(CDvmDataset *pDsExpand);
	void InitProjectByCommCmdManyConfig(const CString &strDestPath);
	void InitCommCmdManyConfigValue(const CString &strValue);
	void SetCommCmdManyConfigValue(const CString &strMaxID);
	void DeleteAllProject();
	void SelectAllTestProject(CExBaseList &listProject, BOOL bMainFirst=TRUE);
	void InitProjectID();
	void InitProjectIndex(long &nPrjIndex);
	CTestProject* FindProjectByPrjIndex(long nPrjIndex);

//检测中心模式
public:
#ifndef _not_use_autotest_
	void CreateTask_AllTestType(CGuideBook *pGuideBook, const CString &strRptFile, const CString &strTaskPath);
	CTestProject* CreateProject(CTestType *pTestType, CGuideBook *pGuideBook, const CString &strRptFile, const CString &strTaskPath);
	CTestProject* CreateProject(const CString &strTestType, const CString &strProjectName, CGuideBook *pGuideBook, const CString &strRptFile, const CString &strTaskPath);
#endif

#ifndef _not_use_autotest_
public:	
	void StitchWordReport(CWnd *pParentWnd, MSWord::_Application &WordApp);
	BOOL CanStitchWordReport();

private:
	UINT StitchWordReportThread(MSWord::_Application &WordApp);

	CThreadProgressBase *m_pThreadProgressBase;
	CWinThread *m_pStitchWordReportThread;

	CString GetStitchWordReportFile();
#endif

public:
	void SelectCmmCfgChannel(CExBaseList &listCmmCfgChannel);
	void WritePpMmsEngineConfig();

	void ValidateSystemPath(const CString &strFrom, const CString &strTo);
	BOOL HasAllProjectCreated();

	void SetDeviceFile(const CString &strFile);
	void SetTestType(const CString &strTestTask);

	void SavePoProjectFile();
	CString GetPoProjectFile();
	BOOL IsTestEligible();
	BOOL IsTestState_Finish();
	void SetGlobalDatas_DeviceAttr();

private:
	void SavePoProjectFile_MmsEngine();
	void SavePoProjectFile_PpEngine();

public:
	CString tsk_GetGbxmlFile(BOOL bFullPath=TRUE);
	void tsk_SetGbxmlFile(const CString &strFile);
	CString tsk_GetPpxmlFile(BOOL bFullPath=TRUE);
	void tsk_SetPpxmlFile(const CString &strFile, BOOL bUpdateAllProject=FALSE);

	void GetByDvmObj(CDvmData *pDvmData);

public:
	//2019-4-28  lijunqing  调试四方多装置、项目组每台装置独立执行
	void Debug_AddTaskBinBoutOffset(long nBinffset=128, long nBoutOffset=128);

	//2020-12-31  lijunqing
	void SetTestState(const CString &strState);

	//2021-1-18  lijunqing
	BOOL HasTestProjectSelected();

	//2021-10-01  lijunqing
	void SetEngineProgID(const CString &strEngineProgID);

	//shaolei 2023-11-2
	void SetEngineMode(const CString &strEngineMode);
	void SetDvmFile(const CString &strDvmFile);
	void SetPpTemplateFile(const CString &strPpXmlFile);
};

//////////////////////////////////////////////////////////////////////////
//CTestTasks
class CTestTasks : public CExBaseList
{
public:
	CTestTasks();
	virtual ~CTestTasks();

	CString m_strTasksParentPath;
	CString m_strTasksPath;
	CString m_strTasksFile;
	CString m_strTestType;

	CDvmDataset *m_pTestApp;   //被测装置的属性
	CDvmDataset *m_pExpandDatas;
	CDvmDataset *m_pExpandDatasAutoSet;
	CTestGlobalDefine *m_pTestGlobalDefine;
	CDvmDataset *m_pDeviceAttrsDefine;
	CDvmDataset *m_pTestAppDefine;
	CExBaseList m_listCmmCfgChannel;

	CString m_strEngineMode;   //shaolei 2023-11-2
	CString m_strPpEngineProgID;
	CString m_strReportFillClassID;
	BOOL m_bPingState;
	CString m_strSystemPath;
	CString m_strDeviceFile;
	CString m_strMacroFile;
	CString m_strTestState;

	//根据任务创建的组路径
	CString m_strXTestDbGroupPath;
	long m_dwAtsRptType;

// private:
	CString m_strTemplateFile;
	CString m_strPpTemplateFile;

public:
	//基本方法
	virtual void Init();
	virtual void InitAfterRead();

	virtual UINT GetClassID()	{		return CLASSID_TESTTASKS;	}

	//串行化
	virtual BSTR GetXmlElementKey()	{		return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrKey;	}

	//编辑
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();
	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//工作区
	BOOL SaveTasksFile();
	BOOL SaveTasksFile(const CString &strFile);
	BOOL InitTasksFileByParentPath(BOOL bCreatePath=FALSE);
	BOOL SaveTasksFileByParentPath();
	BOOL OpenTasksFile(const CString &strFile);

	void SetTasksNameAndID(const CString &strName, const CString &strID);

	CDvmDataset* GetTestApp();
	CDvmData* AddTestApp(CValues *pValues, CDvmDataset *pTestAppDef);
	CDvmData* AddTestApp(CDvmData *pTestApp);
	void InitTestAppAfterAdd(CDvmData *pTestApp);
	void DeleteTestApp(CDvmData *pTestApp);

	void DeleteTestTasks();
	void InitTasksByTestWzdDefine(CTestWzdDefine  *pTestWzdDefine, BOOL bCreateChild);
	void DeleteAllTestTask();

	void SetTestType(const CString &strTestTask);
	void SetAllSelect(long nSel);

	BOOL IsTestState_Finish();
	void SetGlobalDatas_DeviceAttr();

public:
	BOOL HasTestTask();
	long SelectAllTestTask(CExBaseList &listTask);
	long SelectAllTestProject(CExBaseList &listProject, BOOL bMainFirst=TRUE);
	void InitAllCmdCfgChannels();

	void SavePoProjectFile();
	CString GetPoProjectFile();
	CTestTask* FindTestTask(CDvmDataset *pDeviceAttr);
	CTestTask* FindTestTaskByEmptyDeviceAttr();
	void EmptyDeviceAttr();
	CTestTask* FindTestTask(long nIndex);

	void InitProjectByCommCmdManyConfig();
	void InitProjectByCommCmdManyConfig(CTestTask *pTestTask);

	void ReportSNGenClear();
	void ReportSNGen(CDvmDataset *pReportSNGen, const CString &strMacroFileID);
	void TaskReportSNGen(CDvmDataset *pReportSNGen, const CString &strMacroFileID);
	void InitProjectID();
	void InitProjectIndex();
	CTestProject* FindProjectByPrjIndex(long nPrjIndex);

	void InitSystemPath();
	void ValidateSystemPath();
	CTestTask* AddTestTask(CDvmDataset *pDeviceAttrsDefine);
	CTestTask* NewTestTask(CDvmDataset *pDeviceAttrsDefine);
	BOOL HasAllProjectCreated();
	void DeleteTestTask(CTestTask *pTestTask);

	long SelectAllDeviceAttrs(CExBaseList &listDvmAttrs);

private:
	void SavePoProjectFile_MmsEngine();
	void SavePoProjectFile_PpEngine();

	void AutoSetExpandDatas(CTestTask *pTestTask);
#ifndef GUIDEBOOK_DEV_MODE
	void InsertPpDevicesCmmConfig(CDeviceCmmConfig *pCmmConfig);
	void InsertPpDevicesCmmConfig_Serial(CCmmSerialConfig *pCmmConfig);
	void InsertPpDevicesCmmConfig_Net(CCmmNetConfig *pCmmConfig);
	void InsertPpDevicesCmmConfig_Mms(CCmmMmsConfig *pCmmConfig);

public:
	void InsertPpDevicesCmmConfig_Serial(CDeviceCmmConfig *pTestDefine);
	void InsertPpDevicesCmmConfig_Net(CDeviceCmmConfig *pTestDefine);
	void InsertPpDevicesCmmConfig_Mms(CDeviceCmmConfig *pTestDefine);

#endif

public:
#ifndef _not_use_autotest_
	CString ExportWordReport_Summary(MSWord::_Application &WordApp);
	CString ExportWordReport_Summary(WPS::_Application &WPSApp);
#endif

public:
	CString tsk_GetGbxmlFile(BOOL bFullPath=TRUE);
	void tsk_SetGbxmlFile(const CString &strFile);
	CString tsk_GetPpxmlFile(BOOL bFullPath=TRUE);
	void tsk_SetPpxmlFile(const CString &strFile, BOOL bUpdateAllTasks=FALSE);  //2021-3-14  lijunqing add BOOL bUpdateAllTasks
	CString tsk_GetDvmFile();
	void tsk_SetDvmFile(const CString &strFile, BOOL bUpdateAllTasks=FALSE);
	CString tsk_GetLocation();

	void GetByDvmObj(CDvmDataset *pDvmDataset);

public:
	//2019-4-28  lijunqing  调试四方多装置、项目组每台装置独立执行
	//void Debug_AddTaskBinBoutOffset(long nBinffset=128, long nBoutOffset=128);
	void SetRptViewByMrpt();
	void SetRptViewByMrpt(DWORD dwRptType);

	//2020-12-31  lijunqing
	void SetTestState(const CString &strState);

	//2021-10-01  lijunqing
	void SetEngineProgID(const CString &strEngineProgID);

	//shaolei 2023-11-2
	void SetEngineMode(const CString &strEngineMode);
};

