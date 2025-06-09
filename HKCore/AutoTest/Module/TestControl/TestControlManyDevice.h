#pragma once

/*
	功能描述：测试控制对象；管理一个测试的全部过程
*/
#include "TestControlMngrBase.h"
#include "../TaskMngr\TestTask.h"

class CTestControlManyDeviceChild : public CTestControlChildBase
{
public:
	CTestControlManyDeviceChild();
	virtual ~CTestControlManyDeviceChild();

public:
	virtual BOOL ProcessAfterCommCmdFinish(CCommCmd *pCommCmd);
	virtual void ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem);
	virtual void ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem);
	virtual void CreatePpEngineDevice(CProtocolEngineInterface* &pEngine, CPpDeviceRef *pDevieceRef);
	virtual CPpDeviceRef* FindPpDeviceRef(WPARAM wParam);
	virtual CProtocolDeviceInterface* FindPpDevice(WPARAM wParam);
	virtual long StopTestExtern(const CString &strMsg = _T(""), BOOL bExtern=FALSE);  //外部停止测试：用户停止测试、由于异常停止测试
	virtual long OnUpdateGbItem(CGbItemBase* pGbItem);

	virtual void ContinueExecutePpEngineCmd(CTestControl *pTestControl);
	virtual BOOL AfterFinishTestItemSafety(CSafety *pSafety);

};

class CTestControlManyDevice : public CTestControlMngrBase
{
public:
	CTestControlManyDevice();
	virtual ~CTestControlManyDevice();

	virtual CTestControl* CreateChildTest();

public:
	virtual UINT GetTestControlMode()	{	return TESTCONTROLMODE_MDGBRPT;	}

};

