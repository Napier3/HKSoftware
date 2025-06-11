// D:\WorkPM\Source\PMTest\Module\SttSmartTestWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SttSmartTestWnd.h"
#include "SttSmartTest.h"
#ifndef _PSX_IDE_QT_
#include "../../../AutoTest/Module/TestMacroRptTemplate/RptTemplate_GenDocTool.h"
#include "../../../Module/EpotoInterface/EpotoInterface.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSttSmartTestWnd
CSttSmartTestWnd::CSttSmartTestWnd()
{
	m_pSmartTestMsgInterface = NULL;
	m_pMainTestControl = NULL;
}

CSttSmartTestWnd::~CSttSmartTestWnd()
{
}

BOOL CSttSmartTestWnd::CreateSttSmartTestWnd()
{
	return 0;
}

void CSttSmartTestWnd::SetTestControl(CExBaseObject *pTestControl)
{
	m_pMainTestControl = (CTestControlBase *)pTestControl;
}

LRESULT CSttSmartTestWnd::OnSttCreateTest(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestCtrl = (CTestControlBase *)wParam;
	CSttSmartTest *pSmartTest = (CSttSmartTest *)lParam;
	pTestCtrl->CreateReportFill(g_strReportFillProgID);
	pTestCtrl->CreateTestControlWnd();
	//CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(pTestCtrl);
	pTestCtrl->SetSafetyParentWnd(this);
	pSmartTest->m_bTestCreated = TRUE;
	return 0;
}

LRESULT CSttSmartTestWnd::OnSttCreateTestEx(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestCtrl = (CTestControlBase *)wParam;
	CDataGroup *pTestApps = (CDataGroup *)lParam;

	pTestCtrl->CreateTest(pTestApps);
	return 0;
}

LRESULT CSttSmartTestWnd::OnSttCreateTestByCmd(WPARAM wParam, LPARAM lParam)
{
	CSttSmartTest *pSttSmartTest = (CSttSmartTest*)wParam;
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)lParam;
	m_pMainTestControl = pSttSmartTest->GetTestControl();

	pSttSmartTest->On_Ats_CreateTest(pAtsCmd);

	if (m_pSmartTestMsgInterface != NULL)
	{
		m_pSmartTestMsgInterface->X_OnSttCreateTest(pSttSmartTest->GetTestControl(), pSttSmartTest);
	}

	//�������Ժ��Զ���ʼ����
	pSttSmartTest->StartTestAfterCreate();

	return 0;
}

LRESULT CSttSmartTestWnd::OnSttCloseTest(WPARAM wParam, LPARAM lParam)
{
#ifndef _PSX_IDE_QT_
	AfxGetApp()->PostThreadMessage(WM_QUIT, 0, 0);
#else
	CSttSmartTest *pSmartTest = (CSttSmartTest *)lParam;
	pSmartTest->FreeTestControlEx(true);
    CTickCount32 oTick;
    oTick.DoEvents(200);//�ȴ�tcp�̶߳���
    pSmartTest->InitTestControl(true);
#endif
	return 0;
}

LRESULT CSttSmartTestWnd::OnSttBegineTest(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestControl = (CTestControlBase*)wParam;

#ifndef _PSX_IDE_QT_
	//�ϲ���Ԫ���ԣ�ADMU���ԣ����ж�Ȩ��
	if (! IsMacroTest_CanUseAutoTest() )
	{
		if (! Encrypt_IsEncrypt_CanUseAutoTest())
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR, _T("��ʹ�õ�ϵͳû����Ȩ"));
			stt_Return_Ats_Event(pTestControl, NULL, SYS_STATE_EVENT_OnTestStoped);
			return FALSE;
		}
	}
#endif

	if (pTestControl->m_pTCtrlWnd == NULL)
	{
		pTestControl->CreateTestControlWnd();
	}

	pTestControl->TestFrom(-1);

	return 0;
}

LRESULT CSttSmartTestWnd::OnSttStopTest(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestControl = (CTestControlBase*)wParam;
	pTestControl->StopTestByOptr();

	if (g_nSmartTestMode == TEST_MODE_SINGLETEST)
	{
		//ֹͣ���Ժ��´ο�ʼ����ͷ��ʼ����   add by  shaolei  20220318
		pTestControl->m_nCurrTestItemIndex = 0;
		pTestControl->m_pGuideBook->m_nIndex = 0;
	}

	return 0;
}

LRESULT CSttSmartTestWnd::OnSttFinishInputData(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestControl = (CTestControlBase*)wParam;
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)lParam;
	CSttParas *pParas = pAtsCmd->GetSttParas();
	pTestControl->FinishCurrTestItem(pParas);
	pAtsCmd->Release();

	return 0;
}

LRESULT CSttSmartTestWnd::OnSttOpenGbrptFile(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestCtrl = (CTestControlBase *)wParam;
	CSttSmartTest *pSmartTest = (CSttSmartTest *)lParam;
	pSmartTest->m_bTestCreated = FALSE;

	CString strPath = pTestCtrl->GetProjectName();
	pTestCtrl->OpenBinaryFile(strPath, TRUE);
	pTestCtrl->InitAfterOpenBinaryFile();
	pSmartTest->m_bTestCreated = TRUE;

	return 0;
}

LRESULT CSttSmartTestWnd::OnSttAdjustMainWnd(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CSttSmartTestWnd::OnSttExportReport(WPARAM wParam, LPARAM lParam)
{
// 	CSttSmartTest *pSttSmartTest = (CSttSmartTest*)wParam;
// 	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)lParam;
// 	m_pMainTestControl = pSttSmartTest->GetTestControl();
// 
// 	pSttSmartTest->On_Ats_ExportReport(pAtsCmd);

	X_OnSttExportReport(wParam, lParam);
	return 0;
}

LRESULT CSttSmartTestWnd::OnSttFreeTestControl(WPARAM wParam, LPARAM lParam)
{
	CSttSmartTest *pSttSmartTest = (CSttSmartTest *)wParam;

	if (m_pMainTestControl == NULL)
	{
		pSttSmartTest->FreeTestControlEx(FALSE);
	}
	else
	{
		pSttSmartTest->FreeTestControlEx(TRUE);
	}

	if (lParam)
	{
		pSttSmartTest->SetTestControl(m_pMainTestControl);
	}

	return 0;
}

LRESULT CSttSmartTestWnd::OnSttTestPoint(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestCtrl = (CTestControlBase *)wParam;

#ifndef _PSX_IDE_QT_
	//�ϲ���Ԫ���ԣ�ADMU���ԣ����ж�Ȩ��
	if (! IsMacroTest_CanUseAutoTest() )
	{
		if (! Encrypt_IsEncrypt_CanUseAutoTest())
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR, _T("��ʹ�õ�ϵͳû����Ȩ"));
			stt_Return_Ats_Event(pTestCtrl, NULL, SYS_STATE_EVENT_OnTestStoped);
			return FALSE;
		}
	}
#endif

	if (pTestCtrl->m_pTCtrlWnd == NULL)
	{
		pTestCtrl->CreateTestControlWnd();
	}

	long nIndex = lParam;
	pTestCtrl->TestSingle(nIndex);

	return 0;
}

LRESULT CSttSmartTestWnd::OnSttTestBelow(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestCtrl = (CTestControlBase *)wParam;

#ifndef _PSX_IDE_QT_
	//�ϲ���Ԫ���ԣ�ADMU���ԣ����ж�Ȩ��
	if (! IsMacroTest_CanUseAutoTest() )
	{
		if (! Encrypt_IsEncrypt_CanUseAutoTest())
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR, _T("��ʹ�õ�ϵͳû����Ȩ"));
			stt_Return_Ats_Event(pTestCtrl, NULL, SYS_STATE_EVENT_OnTestStoped);
			return FALSE;
		}
	}
#endif

	if (pTestCtrl->m_pTCtrlWnd == NULL)
	{
		pTestCtrl->CreateTestControlWnd();
	}

	long nIndex = lParam;
	pTestCtrl->TestFrom(nIndex);

	return 0;
}

LRESULT CSttSmartTestWnd::OnSttTestAllInlegibleItems(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestCtrl = (CTestControlBase *)wParam;

	if (pTestCtrl->m_pTCtrlWnd == NULL)
	{
		pTestCtrl->CreateTestControlWnd();
	}

	pTestCtrl->OnTestAllInlegibleItems();

	return 0;
}

LRESULT CSttSmartTestWnd::OnSttAdjustReport(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestCtrl = (CTestControlBase *)wParam;

	if (lParam == 1)
	{
		//�˴�Ϊ��ʾ������Ϣ
// 		CAdjustMessageBoxDlg dlg;
// 		m_pAdjustThreadProgress = CThreadProgressBase::CreateTestCtrlThread(this);;
// 
// 		if (dlg.DoModal() == IDOK)
// 		{
// 			pTestCtrl->AdjustReport(m_pAdjustThreadProgress);
// 		}
// 
// 		m_pAdjustThreadProgress->Exit();
// 		m_pAdjustThreadProgress = NULL;

		pTestCtrl->AdjustReport(NULL);
		return 0;
	}

	pTestCtrl->AdjustReport(NULL);
	return 0;
}

LRESULT CSttSmartTestWnd::OnSttCreateDeviceRefs(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestCtrl = (CTestControlBase *)wParam;
	pTestCtrl->CreatePpDeviceRefs();
	return 0;
}

LRESULT CSttSmartTestWnd::OnSttSendTestCmd(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestCtrl = (CTestControlBase *)wParam;

	if (pTestCtrl->m_pTCtrlWnd == NULL)
	{
		pTestCtrl->CreateTestControlWnd();
	}

	CVmSttMacroTest* pInterface = (CVmSttMacroTest*)pTestCtrl->CreateMacroTestInterface(_T("Relay"), _T("SttTestEngine"));

	CSttTestCmd *pTestCmd = (CSttTestCmd *)lParam;
	pInterface->SendTestCmdEx(pTestCmd);
	delete pTestCmd;
	return 0;
}

LRESULT CSttSmartTestWnd::OnSttGenWordReport(WPARAM wParam, LPARAM lParam)
{
#ifndef _PSX_IDE_QT_
	CRptTemplate_GenDocTool *pTool = (CRptTemplate_GenDocTool *)lParam;
	pTool->GenRpt_Word();
#endif
	return 0;
}

LRESULT CSttSmartTestWnd::OnSttClearReportsRslts(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestCtrl = (CTestControlBase *)wParam;
	CGuideBook *pGuideBook = pTestCtrl->m_pGuideBook;
	CDevice *pDevice = pGuideBook->GetDevice();
	BOOL bOnlySelect = (BOOL)lParam;

	pGuideBook->CGbItemBase::ClearReport(FALSE);
	pGuideBook->CGbItemBase::SetState(TEST_STATE_NORMAL);
	Gb_EmptyReportDatas(pDevice, bOnlySelect);
	return 0;
}

LRESULT CSttSmartTestWnd::OnExportReport(WPARAM wParam, LPARAM lParam)
{
	X_OnExportReport(wParam, lParam);
	
	return 0;
}

LRESULT CSttSmartTestWnd::OnCreateTest(WPARAM wParam, LPARAM lParam)
{
	X_OnSttCreateTest(wParam, lParam);
	return 0;
}

LRESULT CSttSmartTestWnd::OnSttReleasePpEngine(WPARAM wParam, LPARAM lParam)
{
	CTestControlBase *pTestCtrl = (CTestControlBase *)wParam;
	CSttSmartTest *pSmartTest = (CSttSmartTest *)lParam;
	pSmartTest->m_bPpEngineReleased = FALSE;
	pTestCtrl->ReleasePpEngine();
	pSmartTest->m_bPpEngineReleased = TRUE;
	return 0;
}

LRESULT CSttSmartTestWnd::OnConnectSttServer_19814(WPARAM wParam, LPARAM lParam)
{
    CSttSmartTest *pSmartTest = (CSttSmartTest *)lParam;
    pSmartTest->ConnectSttServer_WhenInit();
    return 0;
}

long CSttSmartTestWnd::X_OnSttCreateTest(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

long CSttSmartTestWnd::X_OnSttCreateTestEx(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttCreateTestByCmd(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttCloseTest(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttBegineTest(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttStopTest(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttFinishInputData(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttOpenGbrptFile(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttAdjustMainWnd(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttExportReport(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttFreeTestControl(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttTestPoint(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttTestBelow(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttTestAllInlegibleItems(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttAdjustReport(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttCreateDeviceRefs(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttSendTestCmd(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttGenWordReport(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


long CSttSmartTestWnd::X_OnSttClearReportsRslts(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

long CSttSmartTestWnd::X_OnExportReport(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

extern CString *g_strMacroID;
extern CValues *g_pMacrosCfg;
// BOOL IsMuTest()
// {
// 	if (g_strMacroID == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	if ((*g_strMacroID == MARCO_ID_MACRO_MUAccuracyTest)||
// 		(*g_strMacroID == MARCO_ID_MACRO_MUTimingAccurTest)||
// 		(*g_strMacroID == MARCO_ID_MACRO_MUPunctAccurTest)||
// 		(*g_strMacroID == MARCO_ID_MACRO_MUFirstCycleTest)||
// 		(*g_strMacroID == MARCO_ID_MACRO_MUAccurAutoTest) ||
// 		(*g_strMacroID == MARCO_ID_MACRO_MUAutoTest))
// 	{
// 		return TRUE;
// 	}
// 
// 	return FALSE;
// }

BOOL IsMacroTest_CanUseAutoTest()
{
	if (g_strMacroID == NULL)
	{
		return FALSE;
	}

	CString strCfgFile;
	strCfgFile = _P_GetConfigPath();
	strCfgFile += _T("MacroIDCfgs.xml");

	//�ļ������ڣ���ֱ���ж���Ȩ��
	if (!IsFileExist(strCfgFile))
	{
		return FALSE;
	}

	if (g_pMacrosCfg == NULL)
	{
		g_pMacrosCfg = new CValues();
	}

	if (g_pMacrosCfg->GetCount() == 0)
	{
		g_pMacrosCfg->OpenXmlFile(strCfgFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	}

	POS pos = g_pMacrosCfg->GetHeadPosition();

	while (pos != NULL)
	{
		CValue *pCfg = (CValue *)g_pMacrosCfg->GetNext(pos);

		if (pCfg->m_strValue == *g_strMacroID)
		{
			return TRUE;
		}
	}

	return FALSE;
}
