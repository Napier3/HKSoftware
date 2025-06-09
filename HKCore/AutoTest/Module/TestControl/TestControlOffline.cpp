#include "stdafx.h"
#include "TestControlOffline.h"
#include "TestControlWnd.h"
#include "TCtrlCntrBaseApp.h"
#include "../GuideBook\Script/GbScript_GlobalDefine.h"
#include "../GuideBook\GuideBookTool.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestControlOffline::CTestControlOffline()
{
	m_bSingleTestControl = FALSE;
	SetOfflineTestStep_Test();
}

CTestControlOffline::~CTestControlOffline()
{
	
}

void CTestControlOffline::InitOfflineTestStepByGuideBook()
{
	if (m_pGuideBook->IsOfflineTestMode_Test())
	{
		SetOfflineTestStep_Test();
	}
	else
	{
		SetOfflineTestStep_Report();
	}
}

BOOL CTestControlOffline::GetTestBeinEndTime(CString &strTestBeginTime, CString &strTestEndTime)
{
	if (m_pCurrSubTestItem == NULL)
	{
		return m_pCurrTestItem->GetTestTime(strTestBeginTime, strTestEndTime, FALSE);
	}
	
	if (m_pCurrSubTestItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		return FALSE;
	}

	return m_pCurrSubTestItem->GetTestTime(strTestBeginTime, strTestEndTime, TRUE);
}


void CTestControlOffline::InitEngineDataInterface(CCommCmd* pItem)
{
	if (IsOfflineTestStep_Test())
	{
		return;
	}

	CTestControl::InitEngineDataInterface(pItem);
	AddDataInterface_TestTime(pItem, FALSE);
}

CReport* CTestControlOffline::AddReport(CGbItemBase* pItem, long nRepeatTimes, long nTestIndex)
{
	if (IsOfflineTestStep_Test())
	{
		return pItem->AddReport(nRepeatTimes, nTestIndex);
	}

	CReport *pReport = pItem->GetReport(-1);
	return pReport;
}

void CTestControlOffline::SetTestEndTime(CGbItemBase *pItem)
{
	CReport *pReport = pItem->GetReport(-1);

	if (pReport != NULL)
	{
		CValues oValues;
		pReport = pItem->AddReport(&oValues);
		pReport->SetEndTime();
	}
}

void CTestControlOffline::AddDataInterface_TestTime(CCommCmd* pItem, BOOL bReset)
{
	CProtocolParasInterface* pParas = NULL;
	long nResult = 0;
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_PrtcEngineFalse/*L"��Լ�����豸���ݶ������"*/);
		return;
	}

	try
	{
		CProtocolParasInterface* pParas = oPpDevice->GetDataInterface();
		CString strTestBeginTime, strTestEndTime;
		CReport *pReport = pItem->GetReport(-1);
		strTestBeginTime = pReport->GetBeginTime();
		strTestEndTime = pReport->GetEndTime();
	
		if (pParas == NULL)
		{
			return;
		}

		if (bReset)
		{
			pParas->Reset();
		}

		pParas->AddData(g_strGbGlobalData_TestBeginTime, strTestBeginTime);
		pParas->AddData(g_strGbGlobalData_TestEndTime, strTestEndTime);
	}
	catch(...)
	{
	}
}


long CTestControlOffline::FillReportEx(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible)
{
	if (IsOfflineTestStep_Test())
	{
		return 0;
	}

	return CTestControl::FillReportEx(pReport, nRepeatIndex, nInsertDataLinkWhenEligible);
}


//�����������������
long CTestControlOffline::TestItemMacroTest(CMacroTest* pItem)
{
// 	if (IsOfflineTestStep_Report())
// 	{
// 		m_pTCtrlWnd->PostMessage(WM_ELECTRIC_TEST, MTMSG_TestFinished, MTMSG_TestFinished);
// 		return 0;
// 	}
// 
// 	return  CTestControlBase::TestItemMacroTest(pItem);
	m_pCurrTestItem = pItem;

	CTestControlBase*pTestControl =  (CTestControlBase*)tctrl_GetTestControl(pItem);

	if (pItem->m_nRepeatTimes > 1)
	{
		if (m_nMacroTestTimes == 0)
		{
			pItem->ClearReport();
		}

		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, g_sLangTxt_ItemTestTimeD.GetString()/*L"------��Ŀ[%s]��%d�β��ԣ���%d��"*/
			, pItem->m_strName.GetString(), m_nMacroTestTimes+1, GetMaxRepeatTimes(pItem->m_nRepeatTimes)+1);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, g_sLangTxt_ItemTestTimeD2.GetString()/*L"------��Ŀ[%s]��1�β��ԣ���1��"*/, pItem->m_strName.GetString());
	}

	//�����ӿ�
	CreateMacroTestInterface(m_pGuideBook->m_pTestMacros, pItem->GetTestMacroID());

	if (m_pMacroTestInterface == NULL)
	{//����ʧ�ܣ�����ֹ����
		StopTestExtern();
		return -1;
	}

	CMacroTest* pMacroTest = pItem;
	CMacroTestPara* pTestPara;
	CString strTestPara;
	CString strMacroID;

	if(m_pMacroTestInterface != NULL)
	{
		try
		{
			m_pMacroTestInterface->SetWndMsg((long)m_pTCtrlWnd->GetSafeHwnd(), WM_ELECTRIC_TEST);
		}
		catch(...)
		{
		}
	}
	else
	{
		return -1;
	}

	pTestPara = pMacroTest->GetMacroTestPara();
	strMacroID = pTestPara->GetMacroID();
	GetMacroTestParaDatas(pTestPara, strTestPara);

	//�������
	DWORD nRet = 	0;

	try
	{
		g_theSmartTestBaseApp->InitMacroTestEngineShowSpyWnd();
	
		if (IsOfflineTestStep_Test())
		{//����ģʽ���������
			nRet = m_pMacroTestInterface->Test(strMacroID,strTestPara); 
		}
	}
	catch(...)
	{
	}

	//���������Ŀ���ȴ������棬���һ�ȡ��������
	//CExBaseList *pList = pItem->GetSubGbItems();
	//if (pList->GetCount() > 0)
	CReport *pReport = AddReport(pItem, pItem->m_nRepeatTimes, m_nMacroTestTimes);

	//2020-07-25  lijunqing  ���ο�ʼǰ��ȡ����Ĳ�����ֱ��ʹ�ò��Բ�����Ϊ��������
	AddMacroTestReport(pItem, strTestPara);  //2017.05.17
	InitFillReport(pItem);
	SetTestItemState(pItem, TEST_STATE_TESTING);

	//������ӳɹ������������е���Ŀ
	if ( (nRet & 0xF0000000) == 0)
	{
		m_bMacroTestFinished = FALSE;
		if (CanTestFirstSubItems())
		{
			TestFirstSubItems_MacroTest(FALSE);
		}

		if (IsOfflineTestStep_Report())
		{//��д���棬ִ�н���
			m_pTCtrlWnd->PostMessage(WM_ELECTRIC_TEST, MTMSG_TestFinished, MTMSG_TestFinished);
		}

		return 0;
	}
	else
	{
		if (m_pCurrTestItem != NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("MacroTest error{%s}={%08X}"), m_pCurrTestItem->m_strName.GetString(), nRet);
		}

		StopTest(TEST_STATE_TEST_ERROR);
		return -1;
	}
}

CReport* CTestControlOffline::UpdateMacroTestReport(CMacroTest* pItem)
{
	if (IsOfflineTestStep_Report())
	{
		CReport *pReport = (CReport*)pItem->GetReport(-1);
		m_listMacroTestResults.DeleteAll();
		return pReport;
	}

	CReport *pReport =   CTestControl::UpdateMacroTestReport(pItem);
	pReport->SetEndTime();
	return pReport;
}

long CTestControlOffline::TestItemSysParaEdit_Test(CSysParaEdit* pItem)
{
	if (IsOfflineTestStep_Report())
	{
		CTestControl::FinishTestItemSysParaEdit(pItem);
		SetTestEndTime(pItem);
		return 0;
	}

	return  CTestControl::TestItemSysParaEdit_Test(pItem);
}

long CTestControlOffline::FinishTestItemSysParaEdit_ProcessReport(CSysParaEdit* pItem)
{
	if (IsOfflineTestStep_Test())
	{
		CTestControl::FinishTestItemSysParaEdit_ProcessReport(pItem);
		SetTestEndTime(pItem);
		return 0;
	}

	CReport *pReport = pItem->GetReport(-1);//AddReport(pItem, -1, -1); ////2017.05.17

	//��д����
	FillReport(pReport, 0);

	return 0;
}


long CTestControlOffline::TestItemSafety(CSafety* pItem)
{
	if (IsOfflineTestStep_Test())
	{
		CTestControl::TestItemSafety(pItem);
		SetTestEndTime(pItem);
		return 0;
	}

	CReport *pReport = pItem->GetReport(-1);//AddReport(pItem, -1, -1); ////2017.05.17

	//��д����
	FillReport(pReport, 0);

	return 0;
}


long CTestControlOffline::FinishTestItemSafety(CSafety* pItem)
{
	if (IsOfflineTestStep_Test())
	{
		CTestControl::FinishTestItemSafety(pItem);
		SetTestEndTime(pItem);
		return 0;
	}

	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);

	//��ӱ���
	CReport *pReport = pItem->GetReport(-1);//AddReport(pItem, -1, -1); //2017.05.17

	//ִ�н���жϽű�
	CString strSyntax;
	m_pCurrReport = pReport;
	pItem->RunResultScript(strSyntax);
	m_pCurrReport = NULL;

	//��д����
	FillReport(pReport, 0);

	//2021-1-3  lijunqing ��װ��ģʽ�£����������״̬���ͷ������ݣ����º�����װ�ò���ȡ������
	UpdateStateAfterFinishTestItem(pItem);

	//��Ϊ����Ŀ����������Ŀ
	if (pItem->m_bIsSubItem)
	{
		if (m_pCurrSubTestItem == pItem)
		{
			TestNextSubItem(pItem);
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_TestStop4.GetString() /*_T("    ������Ŀʱ�������󣬲���ֹͣ")*/);
			StopTest();
		}
	}
	else//����Ϊ����Ŀ��������һ����Ŀ
	{
		TestNextItem();
	}

	return 0;
}

//ִ�й���
BOOL CTestControlOffline::RunProcedure(const CString &bstrProcedureID, const CString & bstrDatasetPath
									   , WPARAM wParam, LPARAM lParam, UINT nProcedureType, HWND hMsgRcvWnd)
{
	if (IsOfflineTestStep_Test())
	{
		m_pTCtrlWnd->PostMessage(WM_COMM_COMMAND, 0, engineCommFinish);
		return TRUE;
	}

	return CTestControl::RunProcedure(bstrProcedureID, bstrDatasetPath, wParam, lParam, nProcedureType, hMsgRcvWnd);
}

long CTestControlOffline::ProcessFinishCommCmd(CCommCmd* pItem)
{
	if (IsOfflineTestStep_Test())
	{
		SetTestEndTime(pItem);
		pItem->SetRsltJdg(1);
		pItem->SetState(TEST_STATE_ELIGIBLE);
		return 0;
	}

	return CTestControl::ProcessFinishCommCmd(pItem);
}

BOOL CTestControlOffline::WriteItemTempFile(CGbItemBase* pItem)
{
	if (IsOfflineTestStep_Test())
	{
		return TRUE;
	}

	return CTestControl::WriteItemTempFile(pItem);
}

long CTestControlOffline::GetDelayBeforeCmd(CCommCmd* pItem)
{
	if (IsOfflineTestStep_Test())
	{
		return CTestControl::GetDelayBeforeCmd(pItem);
	}
	else
	{
		return 0;
	}
}

long CTestControlOffline::GetDelayAfterCmd(CCommCmd* pItem)
{
	if (IsOfflineTestStep_Test())
	{
		return CTestControl::GetDelayAfterCmd(pItem);
	}
	else
	{
		return 0;
	}
}

