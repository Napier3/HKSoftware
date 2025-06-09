#include "stdafx.h"
#include "TestControlManyDevice.h"
#include "TestControlWnd.h"
#include "../TCtrlCntrWorkSpace.h"
#include "TCtrlCntrBaseApp.h"
#include "../GuideBook\Script/GbScript_GlobalDefine.h"
#include "..\..\..\Module\KeyDb\XMatchToolBase.h"
#include <math.h>

#include "../XRecorderDlg.h"
#include "..\..\..\Module\EpotoInterface\EpotoInterface.h"
#include "..\..\..\Module\DataMngr\DatasetValid\DsvViewResultDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestControlManyDeviceChild::CTestControlManyDeviceChild()
{
	m_bSingleTestControl = FALSE;
}

CTestControlManyDeviceChild::~CTestControlManyDeviceChild()
{
	
}


BOOL CTestControlManyDeviceChild::ProcessAfterCommCmdFinish(CCommCmd *pCommCmd)
{
	return FALSE;
}

void CTestControlManyDeviceChild::ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem)
{
	CTestControl::ExcuteCommCmdOnDelayBeforeFinish(pItem);
}

void CTestControlManyDeviceChild::ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem)
{
	CTestControlManyDevice *pMainDevice = (CTestControlManyDevice*)GetParent();
	pMainDevice->ExcuteCommCmdOnDelayAfterFinish(pItem);
}

void CTestControlManyDeviceChild::CreatePpEngineDevice(CProtocolEngineInterface* &pEngine, CPpDeviceRef *pDevieceRef)
{
	CTestControl::CreatePpEngineDevice(pEngine, pDevieceRef);
}

CPpDeviceRef* CTestControlManyDeviceChild::FindPpDeviceRef(WPARAM wParam)
{
	return (CPpDeviceRef*)m_oDeviceRefs.GetHead();
}


CProtocolDeviceInterface* CTestControlManyDeviceChild::FindPpDevice(WPARAM wParam)
{
	CPpDeviceRef *p = (CPpDeviceRef*)m_oDeviceRefs.GetHead();
	CProtocolDeviceInterface* oPpDevice = NULL;

	if (p != NULL)
	{
		oPpDevice = p->m_oPpDevice;
	}

	return oPpDevice;
}

long CTestControlManyDeviceChild::StopTestExtern(const CString &strMsg, BOOL bExtern)
{
	CTestControlManyDevice *pMainDevice = (CTestControlManyDevice*)GetParent();
	return pMainDevice->StopTestExtern(strMsg, bExtern);
}

long CTestControlManyDeviceChild::OnUpdateGbItem(CGbItemBase* pGbItem)
{
	CTestControlManyDevice *pMainDevice = (CTestControlManyDevice*)GetParent();
	return pMainDevice->OnUpdateGbItem(pGbItem);
}

void CTestControlManyDeviceChild::ContinueExecutePpEngineCmd(CTestControl *pTestControl)
{
	CTestControl::ContinueExecutePpEngineCmd(pTestControl);
	CTestControlManyDevice *pMainDevice = (CTestControlManyDevice*)GetParent();
	return pMainDevice->ContinueExecutePpEngineCmd(this);
}


BOOL CTestControlManyDeviceChild::AfterFinishTestItemSafety(CSafety *pSafety)
{
	CTestControlManyDevice *pMainDevice = (CTestControlManyDevice*)GetParent();
	return pMainDevice->AfterFinishTestItemSafety(pSafety);
}

//////////////////////////////////////////////////////////////////////////
//CTestControlManyDevice
CTestControlManyDevice::CTestControlManyDevice()
{
}

CTestControlManyDevice::~CTestControlManyDevice()
{
}

CTestControl* CTestControlManyDevice::CreateChildTest()
{
	return new CTestControlManyDeviceChild();
}

