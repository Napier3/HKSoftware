#pragma once

#include "../../../Module/BaseClass/ExBaseObject.h"
#include "../GuideBook/GuideBookInterface.h"
#include "../PpDeviceRefs.h"
#include "../AutoTestXMLRWKeys.h"

#define   MTTTASK_PROJECT_USETASKSPARA                   0
#define   MTTTASK_PROJECT_USEOWNPARA                     1
#define   MTTTASK_PROJECT_ONLYPOPEDIT                     2
#define   MTTTASK_PROJECT_POPEDITANDSAVETOTASK    3

class CTestRrptSnGenInterface : public CExBaseList
{
public:
	CTestRrptSnGenInterface(){};
	virtual ~CTestRrptSnGenInterface(){};

	CString m_strReportSN;

	virtual void SetReportSN(const CString &strReportSN) = 0;
	virtual CDvmDataset* GetDeviceAttr(BOOL bCreate=TRUE) = 0;

	virtual CString GetTemplateFile() {	return _T("");	}
	virtual CString GetPpDeviceFile() {	return _T("");	}
	virtual CString GetTestType() {	return _T("");	}
	virtual BOOL CanGenSN()	{	return TRUE;	}
};

class CErrTestItemRef : public CExBaseObject
{
public:
	CErrTestItemRef();
	virtual ~CErrTestItemRef();

	UINT GetClassID();
	virtual BSTR GetXmlElementKey();

	virtual CExBaseObject* Clone();
};

class CTestProject : public CTestRrptSnGenInterface/*2018-3-13  TestTask add SN*///CExBaseList
{
public:
	CTestProject();
	virtual ~CTestProject();

public:
	//Report SN Gen
	virtual void SetReportSN(const CString &strReportSN);
	virtual CDvmDataset* GetDeviceAttr(BOOL bCreate=TRUE);

	virtual CString GetTemplateFile()	{	return m_strTemplateFile;	}
	virtual CString GetPpDeviceFile()	{	return m_strPpDeviceFile;	}
	virtual CString GetTestType()		{	return m_strTestType;	}
	virtual BOOL CanGenSN()			{	return (m_nSelect != 0);	}

public:
	CString m_strLocalID;
	SYSTEMTIME m_tmPlanBegin;
	SYSTEMTIME m_tmPlanFinish;
	SYSTEMTIME m_tmTestBegin;
	SYSTEMTIME m_tmTestFinish;
	CString m_strTestType;
	CString m_strTestState;
	CString m_strTestRsltJdg;   //2018-11-12  厂家批量测试
	//CString m_strReportSN;
	long m_nCurrTestItemIndex;

	CString m_strPpDeviceFile;    //设备点表文件
	CString m_strReportMapFile;  //报告映射文件
	BOOL m_bNewProject;
	CString m_strPpEngineProgID;
	CString m_strEngineMode;  //shaolei  2023-11-2

	CWnd *m_pRefFrameWnd;
	long m_nSelect;

	//测试任务时，使用自己的测试参数
	long m_nTestParaEditMode;
	long m_nProjectID;  //2018-6-19  工程编号
	long m_nProjectIndex;  //2018-11-12 工程编号
	CExBaseObject *m_pTestControlRef;

private:
	CString m_strPpTemplateFile;  //规约模板文件
	CString m_strTemplateFile;    //作业指导书文件
	CString m_strLocation;


//公共接口
public:
	void SetTestParaEditMode(long nTestParaEditMode)	{	m_nTestParaEditMode = nTestParaEditMode;	}
	BOOL IsTestParaEditMode_UseOwn()	{	return m_nTestParaEditMode == MTTTASK_PROJECT_USEOWNPARA;	}
	BOOL IsTestParaEditMode_OnlyPopEdit()	{	return m_nTestParaEditMode == MTTTASK_PROJECT_ONLYPOPEDIT;	}
	BOOL IsTestParaEditMode_PopEditAndSave()	{	return m_nTestParaEditMode == MTTTASK_PROJECT_POPEDITANDSAVETOTASK;	}

	CString GetLocalID()									{		return m_strLocalID;		}
	void SetLocalID(CString strLocalID)						{		m_strLocalID = strLocalID;		}
	CString GetLocation()									{		return m_strLocation;		}
	void SetLocation(CString strLocation)					{		m_strLocation = strLocation;		}
	//CString GetTestType()									{		return m_strTestType;		}
	void SetTestType(CString strTestType)					{		m_strTestType = strTestType;		}
	CString GetProtocalTemplate()							{		return m_strPpTemplateFile;		}
	void SetProtocalTemplate(CString strProtocalTemplate)	{		m_strPpTemplateFile = strProtocalTemplate;		}
	CString GetPpEngineProgID()								{		return m_strPpEngineProgID;		}
	void SetPpEngineProgID(CString strPpEngineProgID)		{		m_strPpEngineProgID = strPpEngineProgID;		}
	CString GetTestState()									{		return m_strTestState;		}
	void SetTestState(CString strTestState)					{		m_strTestState = strTestState;		}
	long GetCurrTestItemIndex()								{		return m_nCurrTestItemIndex;		}
	void SetCurrTestItemIndex(long nCurrIndex)				{		m_nCurrTestItemIndex = nCurrIndex;		}
	CString GetTestStateDesc();
	void UpdateTestRsltJdg(); //2021-1-1  lijunqing

	void SetTestState_Stop();//		{	SetTestState(g_strTestStop);		}
	void SetTestState_Testting();//	{	SetTestState(g_strTesting);			}
	void SetTestState_Finish();//		{	SetTestState(g_strTestFinished);	}
	void SetTestState_Normal();
	void SetTestState_Archiving();//		{	SetTestState(g_strTestArchiving);	}
	
	BOOL IsTestState_Normal();//		{	return m_strTestState == g_strNormal;		}
	BOOL IsTestState_Stop();//			{	return m_strTestState == g_strTestStop;		}
	BOOL IsTestState_Testting();//		{	return m_strTestState == g_strTesting;		}
	BOOL IsTestState_Finish();//		{	return m_strTestState == g_strTestFinished;	}
	BOOL IsTestState_Archiving();//		{	return m_strTestState == g_strTestArchiving;	}

	void SetGlobalDatas_DeviceAttr(CDvmDataset *pDeviceAttr);

public:
	virtual BOOL Init();
	virtual long InitAfterSerialize();
	virtual UINT GetClassID();

	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey();

	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();
	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);


	CExBaseObject* AddErrTestItem(CExBaseObject *pItem);
	DWORD RemoveErrTestItem(CExBaseObject *pItem);
	void InitLocation(const CString &strTaskPath);
	void InitLocationEx(const CString &strTaskPath);

public:
	void ValidateSystemPath(const CString &strFrom, const CString &strTo);
	void SetDeviceFile(const CString &strFile);
	void ValidateLocation();
	void ChangeID(const CString &strID, BOOL bUseRptIndex);

public:
	CString tsk_GetGbxmlFile(BOOL bFullPath=TRUE);
	void tsk_SetGbxmlFile(const CString &strFile);
	CString tsk_GetPpxmlFile(BOOL bFullPath=TRUE);
	void tsk_SetPpxmlFile(const CString &strFile);
	CString tsk_GetLocation(BOOL bFullPath=TRUE);
	void tsk_SetLocation(const CString &strLocation);
};

CString tskapi_GetGbxmlFile(const CString &strTemplateFile, BOOL bFullPath=TRUE);
void tskapi_SetGbxmlFile(const CString &strFile, CString &strTemplateFile);
CString tskapi_GetPpxmlFile(const CString &strPpTemplateFile, BOOL bFullPath=TRUE);
void tskapi_SetPpxmlFile(const CString &strFile, CString &strPpTemplateFile);
CString tskapi_GetDvmFile(const CString &strDvmFile, BOOL bFullPath=TRUE);
