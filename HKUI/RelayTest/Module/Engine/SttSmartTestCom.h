#pragma once

#include "../SmartTestInterface/SttSmartTestSvrInterface.h"
#include "XSmartTestEventInterface.h"
#include "../../../Module/DialogBase/DynDialogEx.h"
#include "../../../AutoTest/Module/XSmartTestClient.h"
#include "../SttCmd/GuideBook/SttGuideBook.h"

class CSttSmartTestCom : public CSttSmartTestSvrInterface, public CXSmartTestEventInterface, public CDynDialogEx
{
	DECLARE_DYNCREATE(CSttSmartTestCom)

public:
	static CSttSmartTestCom * CreateSmartTestSinkWnd()
	{
		CSttSmartTestCom *pDlg;
		pDlg = new CSttSmartTestCom();
		pDlg->SetUseModeless(TRUE);
		pDlg->DoModal();
		pDlg->ModifyStyle(WS_POPUP | WS_CAPTION | WS_SYSMENU, WS_CHILD , 0);
		pDlg->ShowWindow(SW_HIDE);
		return pDlg;
	}

public:
    CSttSmartTestCom();
    virtual ~CSttSmartTestCom();

	CXSmartTestClient *m_pXSmartTestClient;
	CSttGuideBook *m_pGuideBook;
	void InitSmartTestCom();
	void ExitSmartTestCom();

public:
	//以下函数，返回0表示成功，返回非零值表示失败
    virtual long Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_StartTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_StopTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_CloseTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestFrom(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestAllFailedItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_GetItemReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_GetReportFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_GetSystemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_FinishInputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_SetItemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_InputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_ExportReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_SetItemsReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_QueryItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);

public:
	virtual long OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString& strItemID, const CString& strState);
	virtual long OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnExportRptFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnTestAppEvent(const CString& strDeviceID, const CString& strEvent);
	virtual long OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent);
	virtual long OnTestCreated(const CString& strDeviceID);
	virtual long OnOpenGbrptFileFailed(const CString& strDeviceID);

public:
};
