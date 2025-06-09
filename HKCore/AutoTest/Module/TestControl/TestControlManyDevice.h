#pragma once

/*
	�������������Կ��ƶ��󣻹���һ�����Ե�ȫ������
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
	virtual long StopTestExtern(const CString &strMsg = _T(""), BOOL bExtern=FALSE);  //�ⲿֹͣ���ԣ��û�ֹͣ���ԡ������쳣ֹͣ����
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

