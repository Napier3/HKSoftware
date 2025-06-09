#pragma once

/*
	功能描述：测试控制对象；管理一个测试的全部过程
*/
#include "TestControlMngrBase.h"


/*
SdvSpoMgrp测试模式
1）电气量项目：有主TestControl控制执行，子TestControl设置与主TestControl一致
2）提示信息：同上
3）系统参数编辑：同上
4）通讯命令：各自独立处理，有主TestControl统一调度管理
*/

//////////////////////////////////////////////////////////////////////////
//
class CTestControlManyReportChild : public CTestControlChildBase
{
public:
	CTestControlManyReportChild();
	virtual ~CTestControlManyReportChild();

public:
	virtual BOOL ProcessAfterCommCmdFinish(CCommCmd *pCommCmd);
	virtual void ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem);
	virtual void ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem);
	virtual BOOL ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem);
	virtual BOOL CreatePpEngineDevice(CCommCmd *pCmd);
	virtual CPpDeviceRef* FindPpDeviceRef(WPARAM wParam);
	virtual CProtocolDeviceInterface* FindPpDevice(WPARAM wParam);
	virtual long StopTestExtern(const CString &strMsg = _T(""), BOOL bExtern=FALSE); 
	virtual long OnUpdateGbItem(CGbItemBase* pGbItem);

	virtual void ContinueExecutePpEngineCmd(CTestControl *pTestControl);

	virtual long GetDelayBeforeCmd(CCommCmd* pItem);
	virtual long GetDelayAfterCmd(CCommCmd* pItem);

	virtual CProtocolDeviceInterface* GetDevicePtr(CCommCmd* pItem);
	virtual CProtocolDeviceInterface* GetDevicePtr();

};


//////////////////////////////////////////////////////////////////////////
//
class CTestControlManyReport : public CTestControlMngrBase
{
public:
	CTestControlManyReport();
	virtual ~CTestControlManyReport();

	CString m_strCmbdDocFile;

	virtual CTestControl* CreateChildTest();
	virtual void InitByTask(CTestTask *pTestTask, BOOL bCreate);
	virtual void SetTestItemState(CGbItemBase* pItem, UINT nState);

	virtual BOOL CreateTest();
	virtual BOOL CreateTest(const CString &strGbBinaryFile, BOOL bFullPath=FALSE);
	void SetAutoDeleteChild(BOOL b)	{	m_bAutoDeleteChild = b;	}

public:
	void InitCommCmdManyConfig(CCpus *pCpus);

public:
	virtual UINT GetTestControlMode()	{	return TESTCONTROLMODE_MGBRPT;	}
	virtual long FillReportEx(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible);

	virtual BOOL ProcessAfterCommCmdFinish(CCommCmd *pCommCmd);
	virtual void ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem);
	virtual void ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem);
	virtual BOOL ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem);
	virtual long GetDelayBeforeCmd(CCommCmd* pItem);
	virtual long GetDelayAfterCmd(CCommCmd* pItem);

	virtual CProtocolDeviceInterface* GetDevicePtr(CCommCmd* pItem);
	virtual CProtocolDeviceInterface* GetDevicePtr();
	virtual BOOL IsAllItemQualified(CCommCmd* pItem);
	virtual void UpdateDvmLdeviceID();
	virtual void GetReportFiles(CDataGroup *pDataGroup);

protected:
	virtual long ProcessFinishCommCmdReadSOE(CCommCmd* pItem,CDvmDataset *pDataset);
	virtual double GBS_GetDsDataValueEx(CGbItemBase *pItem, long nDeviceIndex, const char* pszID);
	virtual CDataObj* GBS_GetDsDataObj(CGbItemBase *pItem, long nDeviceIndex, const char* pszID);

	virtual BOOL TestNextReport(CTestControl *pTestControl, CCommCmd* pItem);
	virtual BOOL TestByItemsRsltExprScript(CCommCmd* pItem);
	virtual void CloneCommCmdReportToSubReports(CCommCmd* pItem);

	CString GetLdName(CDvmDataset *pExpandDataset, long nIndex);
	long FindDatas(CDvmDataset *pSrc, CDvmDataset *pDest, const CString &strID);
	long GetDvmID(CTestControl *pTestControl, const CString &strDvmDataID, long nDefaultID);

protected:
	void ImportExpandDatas(CDvmDataset *pDataset);

	//替换设备数据模型
	CString m_strSrcLDevice;
	CString m_strDestLDevice;
	BOOL EditCommCmdDatasetPath(CItems* pItems);
	BOOL EditCommCmdDatasetPath(CCommCmd* pItem);
	BOOL EditCommCmdDatasetPath(CExBaseList *pList);
	BOOL EditCommCmdDatasetPath(CGuideBook *pGuideBook);
	BOOL EditCommCmdDatasetPath(CDevice *pDevice);

	long GetLdIndex(const CString &strLdevice);
	CDvmLogicDevice* FindByLdIndex(CDvmDevice *pDevice, long nLdIndex);
	void UpdateDvmLdeviceID(CTestControl *pTestControl, CCpu *pCpu0, CDvmLogicDevice *pLd0, CDvmLogicDevice *pLdCurr);
	CCpu* FindCpu0();

public:
	void EditCommCmdDatasetPath(const CString &strSrcLDevice);

	void InitPpDevicesByTestTask(CTestTask *pTestTask);
};

