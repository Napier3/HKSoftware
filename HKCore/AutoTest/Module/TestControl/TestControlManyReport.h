#pragma once

/*
	�������������Կ��ƶ��󣻹���һ�����Ե�ȫ������
*/
#include "TestControlMngrBase.h"


/*
SdvSpoMgrp����ģʽ
1����������Ŀ������TestControl����ִ�У���TestControl��������TestControlһ��
2����ʾ��Ϣ��ͬ��
3��ϵͳ�����༭��ͬ��
4��ͨѶ������Զ�����������TestControlͳһ���ȹ���
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

	//�滻�豸����ģ��
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

