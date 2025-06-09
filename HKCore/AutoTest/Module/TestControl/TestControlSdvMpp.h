#pragma once

/*
	功能描述：测试控制对象；管理一个测试的全部过程
*/
#include "TestControlManyDevice.h"
// 
// class CTestControlSdvMppChild : public CTestControl
// {
// public:
// 	CTestControlSdvMppChild();
// 	virtual ~CTestControlSdvMppChild();
// 
// public:
// 	virtual BOOL ProcessAfterCommCmdFinish(CCommCmd *pCommCmd);
// 	virtual void ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem);
// 	virtual void ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem);
// 	virtual void CreatePpEngineDevice(CProtocolEngineInterface* &pEngine, CPpDeviceRef *pDevieceRef);
// 	virtual CPpDeviceRef* FindPpDeviceRef(WPARAM wParam);
// 	virtual CProtocolDeviceInterface* FindPpDevice(WPARAM wParam);
// 	virtual long StopTestExtern();  //外部停止测试：用户停止测试、由于异常停止测试
// 	virtual long OnUpdateGbItem(CGbItemBase* pGbItem);
// 
// 	virtual void ContinueExecutePpEngineCmd(CTestControl *pTestControl);
// 	virtual BOOL AfterFinishTestItemSafety(CSafety *pSafety);
// 
// };

class CTestControlSdvMpp : public CTestControlManyDevice
{
public:
	CTestControlSdvMpp();
	virtual ~CTestControlSdvMpp();

public:
	virtual long TestItemCommCmdEx(CCommCmd* pItem);

	virtual UINT GetTestControlMode()	{	return TESTCONTROLMODE_SDVMPP;	}
	virtual BOOL ProcessAfterCommCmdFinish(CCommCmd *pCommCmd);

	virtual void ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem);
	virtual void CreatePpEngineDevice(CProtocolEngineInterface* &pEngine, CPpDeviceRef *pDevieceRef);
	virtual CPpDeviceRef* FindPpDeviceRef(WPARAM wParam);
	virtual CProtocolDeviceInterface* FindPpDevice(WPARAM wParam);

	virtual long GetDelayBeforeCmd(CCommCmd* pItem);
	virtual long GetDelayAfterCmd(CCommCmd* pItem);

protected:
	virtual BOOL IsMutexWriteCmd(CCommCmd* pItem);
	virtual void AddReportToChildren(CCommCmd* pItem);
};

