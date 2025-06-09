#pragma once

/*
	�������������Կ��ƶ��󣻹���һ�����Ե�ȫ������
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
// 	virtual long StopTestExtern();  //�ⲿֹͣ���ԣ��û�ֹͣ���ԡ������쳣ֹͣ����
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

