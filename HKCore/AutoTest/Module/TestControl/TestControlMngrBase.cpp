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
#include "../GuideBook\GuideBookTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestControlChildBase::CTestControlChildBase()
{
	m_bSingleTestControl = FALSE;
}

CTestControlChildBase::~CTestControlChildBase()
{
	
}


//2017-3-18  测试控制部分，全部设置为虚函数，便于多测试的控制
//单一项目
long CTestControlChildBase::TestSingle(CGbItemBase* pGbItem)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->TestSingle(pGbItem);
}

long CTestControlChildBase::TestSingle(long nItemIndex)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->TestSingle(nItemIndex);
}

//某个项目到结束
long CTestControlChildBase::TestFrom(CGbItemBase* pGbItem)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->TestFrom(pGbItem);
}

long CTestControlChildBase::TestFrom(long nItemIndex)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->TestFrom(nItemIndex);
}

BOOL CTestControlChildBase::ProcessAfterCommCmdFinish(CCommCmd *pCommCmd)
{
	return FALSE;
}

void CTestControlChildBase::ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem)
{
	CTestControl::ExcuteCommCmdOnDelayBeforeFinish(pItem);
}


BOOL CTestControlChildBase::ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->ExcuteCommCmdOnDelayAfterFinish_Repeat(pItem);
}

void CTestControlChildBase::ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	pMainDevice->ExcuteCommCmdOnDelayAfterFinish(pItem);
}

void CTestControlChildBase::CreatePpEngineDevice(CProtocolEngineInterface* &pEngine, CPpDeviceRef *pDevieceRef)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	pMainDevice->CreatePpEngineDevice(pEngine, pDevieceRef);
}

CPpDeviceRef* CTestControlChildBase::FindPpDeviceRef(WPARAM wParam)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->FindPpDeviceRef(wParam);
}


CProtocolDeviceInterface* CTestControlChildBase::FindPpDevice(WPARAM wParam)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->FindPpDevice(wParam);
}

long CTestControlChildBase::StopTestExtern(const CString &strMsg, BOOL bExtern)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->StopTestExtern(strMsg, bExtern);
}

long CTestControlChildBase::OnUpdateGbItem(CGbItemBase* pGbItem)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->OnUpdateGbItem(pGbItem);
}

void CTestControlChildBase::ContinueExecutePpEngineCmd(CTestControl *pTestControl)
{
	CTestControl::ContinueExecutePpEngineCmd(pTestControl);
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->ContinueExecutePpEngineCmd(this);
}


BOOL CTestControlChildBase::AfterFinishTestItemSafety(CSafety *pSafety)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->AfterFinishTestItemSafety(pSafety);
}


long CTestControlChildBase::GetDelayBeforeCmd(CCommCmd* pItem)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->GetDelayBeforeCmd(pItem);
}

long CTestControlChildBase::GetDelayAfterCmd(CCommCmd* pItem)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->GetDelayAfterCmd(pItem);
}


BOOL CTestControlChildBase::ContinueTestByItemsRsltExprScript(CCommCmd* pItem)
{
	if (m_pItemsRsltExprScript != NULL)
	{
		if (pItem->GetRsltJdg() == 0)
		{
			if (m_nItemsRsltExprScriptIndex < m_nItemsRsltExprScriptMaxRead)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}


void CTestControlChildBase::EditItemPara(CCommCmd *pCommCmd, CValue *pValue)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->EditItemPara(pCommCmd, pValue);
}

BOOL CTestControlChildBase::ItemsRsltExprScriptTimeIgnore()
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->ItemsRsltExprScriptTimeIgnore();
}

void CTestControlChildBase::SetTestItemSelectedState(CGbItemBase *pItem,long nSelect)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->SetTestItemSelectedState(pItem, nSelect);
}

void CTestControlChildBase::EditItemPara(CMacroTest *pMacroTest, CShortData  *pData)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->EditItemPara(pMacroTest, pData);
}

BOOL CTestControlChildBase::GBS_CanBreakLoop(CGbItemBase *pItem)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->GBS_CanBreakLoop(pItem);
}

void CTestControlChildBase::GBS_ClearBreakLoopState(CGbItemBase *pItem)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->GBS_ClearBreakLoopState(pItem);
}


long CTestControlChildBase::GBS_RcdCmp_CopyStdFile(CTestControl *pTestControl, CString &strStdSrcFile, CString &strStdDestFile)
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->GBS_RcdCmp_CopyStdFile(pTestControl, strStdSrcFile, strStdDestFile);
}


long CTestControlChildBase::FinishTestItemMacroTest_Process(CMacroTest* pItem) //2019-4-27 MdvTestEach
{
	CTestControlMngrBase *pMainDevice = (CTestControlMngrBase*)GetParent();
	return pMainDevice->FinishTestItemMacroTest_Process(pItem);
}

//////////////////////////////////////////////////////////////////////////
//CTestControlMngrBase
CTestControlMngrBase::CTestControlMngrBase()
{
	m_pCurrTestControl = NULL;
	m_bAutoDeleteChild = FALSE;
}

CTestControlMngrBase::~CTestControlMngrBase()
{
	if (!m_bAutoDeleteChild)
	{
		RemoveAll();
	}
}

void CTestControlMngrBase::AddSysPara(const CString &strID, const CString &strValue)
{
	m_pGuideBook->AddSysPara(strID, strValue);

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pTestControl->m_pGuideBook->AddSysPara(strID, strValue);
	}
}

void CTestControlMngrBase::AddSysPara(const CString &strID, long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	AddSysPara(strID, strValue);
}

//2017-3-18  测试控制部分，全部设置为虚函数，便于多测试的控制
//单一项目
long CTestControlMngrBase::TestSingle(CGbItemBase* pGbItem)
{
	return CTestControl::TestSingle(pGbItem);
}

long CTestControlMngrBase::TestSingle(long nItemIndex)
{
	return CTestControl::TestSingle(nItemIndex);
}

//某个项目到结束
long CTestControlMngrBase::TestFrom(CGbItemBase* pGbItem)
{
	return CTestControl::TestFrom(pGbItem);
}

long CTestControlMngrBase::TestFrom(long nItemIndex)
{
	return CTestControl::TestFrom(nItemIndex);
}

BOOL CTestControlMngrBase::OpenTaskFile(const CString &strFile)
{
	m_strBinaryTaskFile = strFile;

	CBinarySerialBuffer oBuffer;
	Gb_InitGuideBookFileVersion(oBuffer);
	oBuffer.ResetVersion();

	oBuffer.OpenFromFile(strFile);

	oBuffer.SetReadMode();
	oBuffer.ReadVersion();

	if (oBuffer.m_dwVersion > 0)
	{
		oBuffer.SetVersionFindByID(g_dwDataMngrVersionID);
		m_oTask.DeleteAll();

		try
		{
			m_oTask.Serialize(oBuffer);
		}
		catch (...)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_FileRightError/*_T("文件【%s】版本错误！")*/, strFile);
		}

		InitByTask(&m_oTask, FALSE);

		return 0;
	}

	return OpenTaskFile_XML(strFile);
}

BOOL CTestControlMngrBase::OpenTaskFile_XML(const CString &strFile)
{
	m_oTask.DeleteAll();
	BOOL bRet = m_oTask.OpenTaskFile(strFile);
	m_oTask.SavePoProjectFile();
	InitByTask(&m_oTask, FALSE);

	return bRet;
}

void CTestControlMngrBase::InitByOwnTask()
{
	InitByTask(&m_oTask, FALSE);
}

void CTestControlMngrBase::InitByTask(CTestTask *pTestTask, BOOL bCreate)
{
	m_bAutoDeleteChild = TRUE;
	POS pos = pTestTask->GetHeadPosition();
	CExBaseObject *p = NULL;
	long nIndex = 0;
	CTestProject *pProject = NULL;

	while (pos != NULL)
	{
		p = pTestTask->GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTPROJECT)
		{
			pProject = (CTestProject *)p;

			if (pProject->m_nSelect == 1)
			{
				CreateChildTest((CTestProject*)p, nIndex, bCreate);
				nIndex++;
			}
		}
	}
}

CTestTask* CTestControlMngrBase::CloneTask(CTestTask *pTestTask)
{
	m_oTask.DeleteAll();
	m_oTask.AppendClone(pTestTask);

	return &m_oTask;
}


void CTestControlMngrBase::UpdateTest_ReportSN(CGuideBook *pGuideBook, CTestProject *pProject)
{
	CDvmDataset *pShortDatas = pGuideBook->GetGlobalDatas();

	if (pShortDatas == NULL)
	{
		return;
	}

	CDvmData *pData = (CDvmData*)pShortDatas->FindByID(g_strGbGlobalData_ReportSN);

	if (pData == NULL)
	{
		pData = pShortDatas->AddNew2(g_strGbGlobalData_ReportSN,     g_strGbGlobalData_ReportSN,       _T(""), _T(""), _T(""), _T(""));
	}

	pData->m_strValue = pProject->m_strID;
}

void CTestControlMngrBase::UpdateTest_DeviceIndex(CGuideBook *pGuideBook, CTestProject *pProject)
{

}

void CTestControlMngrBase::UpdateTest_TestApp(CGuideBook *pGuideBook, CTestProject *pProject)
{

}

void CTestControlMngrBase::UpdateTest_DeviceAttr(CGuideBook *pGuideBook, CTestProject *pProject)
{

}

void CTestControlMngrBase::UpdateTest(CGuideBook *pGuideBook, CTestProject *pProject)
{
	//报告编号
	UpdateTest_ReportSN(pGuideBook, pProject);

	//测试仪器

	//装置属性

	//装置编号

	//规约模板文件
	pGuideBook->m_strPpTemplateFile = pProject->GetProtocalTemplate();
	//规约引擎模式：MQTT、COM、STT
	pGuideBook->m_strEngineMode = pProject->m_strEngineMode;
	//设备模型文件
	pGuideBook->m_strDeviceModelFile = pProject->m_strPpDeviceFile;
	//规约引擎ID
	pGuideBook->m_strPpEngineProgID = pProject->m_strPpEngineProgID;
}

CTestControl* CTestControlMngrBase::CreateChildTest(CTestProject *pProject, long nIndex, BOOL bUpdateTest)
{
	ASSERT (m_pGuideBook != NULL);
	pProject->ValidateLocation();
	m_pTestProjectRef = pProject;
	pProject->m_pTestControlRef = this;

	if (nIndex == 0)
	{
		ASSERT (m_pGuideBook != NULL);
		m_strName = pProject->m_strName;
		m_strGbBinaryFile = pProject->tsk_GetLocation();
		OpenBinaryFile(m_strGbBinaryFile, CTCtrlCntrConfig::Get_RWReportFileMode());
		InitGbBinaryFileName();

		if (bUpdateTest)
		{
			UpdateTest(m_pGuideBook, pProject);
		}

		InitAfterOpenBinaryFile();
		m_pGuideBook->SetParent(this);

		return this;
	}
	else
	{
		CTestControlChildBase *pControl = (CTestControlChildBase*)CreateChildTest();
		CGuideBook *pGuideBook = pControl->m_pGuideBook;
		ASSERT (pGuideBook != NULL);
		pControl->m_strName = pProject->m_strName;

		pControl->m_bSingleTestControl = FALSE;
		CString strLocation = pProject->tsk_GetLocation();
		pControl->SetBinaryFile(strLocation);
		pControl->OpenBinaryFile(strLocation, CTCtrlCntrConfig::Get_RWReportFileMode());
		pGuideBook->SetParent(pControl);
		pControl->InitGbBinaryFileName();

		UpdateTest(pGuideBook, pProject);

		pControl->InitAfterOpenBinaryFile();
		AddNewChild(pControl);

		return pControl;
	}
}

CTestControl* CTestControlMngrBase::CreateChildTest()
{
	return new CTestControlChildBase();
}

CTestTask* CTestControlMngrBase::GetTestTask()	
{
	return &m_oTask;	
}

CString CTestControlMngrBase::GetTestTaskFile()
{
	return m_oTask.GetTaskFile();
}

void CTestControlMngrBase::SaveTask()
{
	CBinarySerialBuffer oBuffer;
	Gb_InitGuideBookFileVersion(oBuffer);
	oBuffer.SetVersionFindByID(g_dwDataMngrVersionID);

	oBuffer.SetCalSizeMode();
	m_oTask.Serialize(oBuffer);
	oBuffer.WriteVersion();
	oBuffer.AllocBuffer(0);

	oBuffer.SetWriteMode();
	oBuffer.WriteVersion();
	m_oTask.Serialize(oBuffer);

	oBuffer.SaveToFile(m_strBinaryTaskFile);
}

void CTestControlMngrBase::SaveTask_XML()
{

}

CExBaseObject* CTestControlMngrBase::GetItem(CGuideBook *pGuideBook, CExBaseObject *pItem)
{
	return Gb_GetItem(pGuideBook, pItem);
}

CTestControl* CTestControlMngrBase::GetTestControl(CExBaseObject *pItem)
{
	return (CTestControl*)tctrl_GetTestControl(pItem);
}

long CTestControlMngrBase::TestItem(CGbItemBase* pItem)
{
	//执行当前项目
	m_pCurrTestControl = this;
	m_pTCtrlWnd->m_pTestControl = this;
	long nState = CTestControl::TestItem(pItem);  //测试

	if (m_pCurrTestItem == NULL)
	{
		return nState;
	}

	//遍历每一个CTestControl子对象，设置当前项目和当前子项目
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CGbItemBase *pCurr = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pCurr = (CGbItemBase*)GetItem(pTestControl->m_pGuideBook, m_pCurrTestItem);
		pTestControl->m_pCurrTestItem = pCurr;

		if (m_pCurrSubTestItem != NULL)
		{
			pCurr = (CCommCmd*)GetItem(pTestControl->m_pGuideBook, m_pCurrSubTestItem);
			pTestControl->m_pCurrSubTestItem = pCurr;
		}
	}

	return nState;
}

long CTestControlMngrBase::TestItemCommCmdEx(CCommCmd* pItem)
{
	CTestControl *pTestCtrol = GetTestControl(pItem);
	ASSERT (pTestCtrol != NULL);

	if (pTestCtrol == this)
	{
		return CTestControl::TestItemCommCmdEx(pItem);
	}
	else
	{
		return pTestCtrol->TestItemCommCmdEx(pItem);
	}
}

long CTestControlMngrBase::StopTestExtern(const CString &strMsg, BOOL bExtern)
{
	long nState = CTestControl::StopTestExtern(strMsg, bExtern);

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CGbItemBase *pCurr = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pTestControl->CTestControl::StopTestExtern(strMsg, bExtern);
	}

	return 0;
}

BOOL CTestControlMngrBase::NeedTestNextDevice()
{
	return FALSE;
}

CReport* CTestControlMngrBase::UpdateMacroTestReport(CGuideBook *pGuideBook, CMacroTest* pItem)
{
	CMacroTest *pCurr = (CMacroTest*)GetItem(pGuideBook, pItem);

	if (pCurr == NULL)
	{
		return NULL;
	}

	CReport *pReport = CTestControl::UpdateMacroTestReport(pCurr);

	return pReport;
}

CReport* CTestControlMngrBase::UpdateMacroTestReport(CGuideBook *pGuideBook, CMacroTest* pItem, CReport *pSrcReport)
{
	CMacroTest *pCurr = (CMacroTest*)GetItem(pGuideBook, pItem);

	if (pCurr == NULL)
	{
		return NULL;
	}

	CTestControl::UpdateMacroTestReport(pCurr, pSrcReport);

	return pSrcReport;
}

CReport* CTestControlMngrBase::UpdateMacroTestReport(CMacroTest* pItem)
{
	//主GuideBook
	CReport *pReport = CTestControl::UpdateMacroTestReport(pItem);

	//遍历每一个guidebook，执行同样的操作
	POS pos = GetHeadPosition();
	CTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		UpdateMacroTestReport(p->m_pGuideBook, pItem);
	}

	return pReport;
}

long CTestControlMngrBase::ProcessFinishCommCmd(CGuideBook *pGuideBook, CCommCmd* pItem)
{
	CCommCmd *pCurr = (CCommCmd*)GetItem(pGuideBook, pItem);

	if (pCurr == NULL)
	{
		return NULL;
	}

	CTestControl::ProcessFinishCommCmd(pCurr);

	return 0;
}


long CTestControlMngrBase::ProcessFinishCommCmd(CCommCmd* pItem)
{
	return CTestControl::ProcessFinishCommCmd(pItem);;
}

long CTestControlMngrBase::FindIndexByGuideBook(CGuideBook *pGuideBook)
{
	POS pos = GetHeadPosition();
	CTestControl *p = NULL;
	long nIndex = 0;
	long nIndexFind = -1;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);

		if (p->m_pGuideBook == pGuideBook)
		{
			nIndexFind = nIndex;
			break;
		}

		nIndex++;
	}

	return nIndexFind;
}

CGuideBook* CTestControlMngrBase::FindGuideBookByIndex(long nIndex)
{
	CTestControl *pTestControl = (CTestControl*)GetAtIndex(nIndex);

	return pTestControl->m_pGuideBook;
}

BOOL CTestControlMngrBase::IsTailItem(CExBaseObject *pItem)
{
	CTestControl* pTestControl = GetTestControl(pItem);

	if (GetCount() == 0)
	{
		return TRUE;
	}

	if (pTestControl == GetTail())
	{
		return TRUE;
	}

	if (pItem->GetClassID() == GBCLASSID_COMMCMD)
	{
		CCommCmd *pCommCmd = (CCommCmd*)pItem;

		if (pCommCmd->IsCmdRptDataset() && pCommCmd->IsRead())
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CTestControlMngrBase::SetItemsRsltExprScriptIndex(long nIndex, DWORD dwIndex)
{
	if (m_pItemsRsltExprScript == NULL)
	{
		return;
	}

	m_nItemsRsltExprScriptIndex = nIndex;
	m_pItemsRsltExprScript->m_dwReserved = dwIndex;

	POS pos = GetHeadPosition();
	CTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		p->m_nItemsRsltExprScriptIndex = nIndex;
		p->m_pItemsRsltExprScript->m_dwReserved = dwIndex;
	}
}

long CTestControlMngrBase::FillReportEx(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible)
{
	return CTestControl::FillReportEx(pReport, nRepeatIndex, nInsertDataLinkWhenEligible);
}

void CTestControlMngrBase::SaveReport()
{
	CTestControl::SaveReport();

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pTestControl->SaveReport();
	}
}

long CTestControlMngrBase::LocateReport(CGbItemBase* pItem, long nIndex)
{
	CTestControl *pTestControl = GetTestControl(pItem);
	CGbItemBase *pMainItem = NULL;

	if (this == pTestControl)
	{
		pMainItem = pItem;
	}
	else
	{
		pMainItem = (CGbItemBase*)GetItem(m_pGuideBook, pItem);
	}
	
	CTestControl::LocateReport(pMainItem, nIndex);

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pItem = (CGbItemBase*)GetItem(m_pGuideBook, pMainItem);
		pTestControl->LocateReport(pItem, nIndex);
	}

	return 0;
}

BOOL CTestControlMngrBase::CanRunCommCmdFinalResultScript(CCommCmd* pItem)
{
	return m_bCanRunCommCmdFinalResultScript;
}

BOOL CTestControlMngrBase::AfterFinishTestItemSafety_OneTime(CTestControl *pTestControl, CSafety *pSafety)
{
	CReport *pSrc = pSafety->GetReport(-1);
	CGuideBook *pGuideBook = NULL;
	CSafety *pCurr = NULL;
	pGuideBook = pTestControl->m_pGuideBook;
	pCurr = (CSafety*)GetItem(pGuideBook, pSafety);
	pTestControl->m_pCurrTestItem = pCurr;

	if (pCurr != NULL)
	{
		CReport *pReport = pCurr->GetReport(-1);//AddReport(pCurr, -1, -1); //2017.0518
		pReport->m_pValues->DeleteAll();
		pReport->m_pValues->AppendCloneEx(*pSrc->m_pValues);
		pReport->AddRptDvmDataset(*pSrc->m_pRptDvmDataset);
		pCurr->AddQRCodeValues(pReport->m_pValues);

		//执行结果判断脚本
		CString strSyntax;
		m_pCurrReport = pReport;
		pCurr->RunResultScript(strSyntax);
		m_pCurrReport = NULL;

		//填写报告
		pTestControl->FillReport(pReport, 0);

		UpdateStateAfterFinishTestItem(pCurr);

		//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
		//因此单独执行
		WriteItemTempFile(pCurr);

	}

	pTestControl->m_pCurrTestItem = NULL;

	return TRUE;
}

BOOL CTestControlMngrBase::AfterFinishTestItemSafety_OneTimeEx(CSafety *pSafety)
{
	AfterFinishTestItemSafety_OneTime(this, pSafety);

	CTestControlMngrBase::AfterFinishTestItemSafety_OneTime(pSafety);

	return TRUE;
}

BOOL CTestControlMngrBase::AfterFinishTestItemSafety_OneTime(CSafety *pSafety)
{
	CReport *pSrc = pSafety->GetReport(-1);

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CGuideBook *pGuideBook = NULL;
	CSafety *pCurr = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		AfterFinishTestItemSafety_OneTime(pTestControl, pSafety);
	}

	return TRUE;
}

BOOL CTestControlMngrBase::AfterFinishTestItemSafety_ManyTime(CSafety *pSafety)
{
	return TRUE;
}


BOOL CTestControlMngrBase::AfterFinishTestItemSafety(CSafety *pSafety)
{
	CGuideBook *pGuideBook = (CGuideBook *)pSafety->GetAncestor(GBCLASSID_GUIDEBOOK);
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();

	if (pTestControl == this)
	{
		if (pSafety->IsManyDeviceTestMode_OneTime())
		{
			AfterFinishTestItemSafety_OneTime(pSafety);
			return TRUE;
		}
		
		pTestControl = (CTestControl *)GetHead();
	}
	else
	{
		long nIndex = FindIndex(pTestControl);

		if (nIndex == GetCount() - 1)
		{
			return TRUE;
		}
		
		pTestControl = (CTestControl *)GetAtIndex(nIndex+1);
	}

	if (pTestControl == NULL)
	{
		return TRUE;
	}

	m_pCurrTestControl = pTestControl;
	m_pTCtrlWnd->m_pTestControl = m_pCurrTestControl;
	CSafety *pItem = (CSafety*)GetItem(pTestControl->m_pGuideBook, pSafety);
	pTestControl->TestItem(pItem);

	return FALSE;
}

long CTestControlMngrBase::TestNextItem()
{
	return CTestControl::TestNextItem();
}

long CTestControlMngrBase::FinishTestControlSysParaEdit(CTestControl *pDestTestControl, CSysParaEdit* pItem)
{
	CGuideBook *pGuideBook = NULL;
	CSysParaEdit *pCurrItem = NULL;
	long nTotalCount = 0;
	CExBaseList *pListCurr = NULL;

	pGuideBook = pDestTestControl->m_pGuideBook;
	pCurrItem = (CSysParaEdit*)GetItem(pGuideBook, pItem);
	CExBaseList *pListSrc = &pItem->m_oListDataTotal;//GetSysParaEditDataObjList();

	if (pCurrItem == NULL)
	{
		return 0;
	}

	pCurrItem->m_pParas->SetValuesByDatas(pItem->m_pParas);
	pCurrItem->InitDataList(nTotalCount);
	pListCurr = &pCurrItem->m_oListDataTotal;

	POS posData = pListSrc->GetHeadPosition();
	CDataObj *p1 = NULL;
	CDataObj *p2 = NULL;

	while (posData != NULL)
	{
		p1 = (CDataObj*)pListSrc->GetNext(posData);

		if (pItem->IsDeviceIndexPara(p1->m_strID))
		{
			continue;
		}

		p2 = (CDataObj*)pListCurr->FindByID(p1->m_strID);

		if (p2 != NULL)
		{
			p2->m_strValue = p1->m_strValue;
		}
	}

	//添加报告
	CReport *pReport = pCurrItem->GetReport(-1);//AddReport(pCurrItem, -1, -1);//2017.06.02
	pReport->SetReportValues(pListCurr);

	//执行结果判断脚本
	CString strSyntax;
	m_pCurrReport = pReport;
	pCurrItem->RunResultScript(strSyntax);
	m_pCurrReport = NULL;

	if (pCurrItem->m_strDatasetPath == g_strwSysPara)
	{
		CDevice *pDevice = (CDevice*)pCurrItem->GetAncestor(GBCLASSID_DEVICE);
		pListCurr = pDevice->GetSysParas();
		pReport->AppendReportValues(pListCurr);
	}
	else
	{
		pReport->AppendReportValues(pListCurr);
	}

	//填写报告
	pDestTestControl->FillReport(pReport, 0);

	pDestTestControl->UpdateStateAfterFinishTestItem(pCurrItem);

	//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
	//因此单独执行
	pDestTestControl->WriteItemTempFile(pCurrItem);

	return 0;
}

long CTestControlMngrBase::FinishTestControlSysParaEdit(CSysParaEdit* pItem)
{
	FinishTestControlSysParaEdit(this, pItem);
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		FinishTestControlSysParaEdit(pTestControl, pItem);
	}

	return 0;
}

long CTestControlMngrBase::FinishTestItemSysParaEdit(CSysParaEdit* pItem)
{
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
// 	CGuideBook *pGuideBook = NULL;
// 	CSysParaEdit *pCurr = NULL;
// 	CExBaseList *pList = &pItem->m_oListDataTotal;//GetSysParaEditDataObjList();
// 	long nTotalCount = 0;
// 	CExBaseList *pListCurr = NULL;
	
	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		FinishTestControlSysParaEdit(pTestControl, pItem);
	}

	return CTestControl::FinishTestItemSysParaEdit(pItem);
}

BOOL CTestControlMngrBase::ProcessAfterCommCmdFinish(CCommCmd *pCommCmd)
{
	return FALSE;
}

void CTestControlMngrBase::ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem)
{
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();

	ASSERT (m_pCurrTestControl == pTestControl);

	if (pTestControl == this)
	{
		return CTestControl::ExcuteCommCmdOnDelayBeforeFinish(pItem);
	}
	else
	{
		return m_pCurrTestControl->ExcuteCommCmdOnDelayBeforeFinish(pItem);
	}
}

BOOL CTestControlMngrBase::ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem)
{
	ASSERT (FALSE);
	return CTestControl::ExcuteCommCmdOnDelayAfterFinish_Repeat(pItem);
}

void CTestControlMngrBase::ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem)
{
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();

	ASSERT (m_pCurrTestControl == pTestControl);

	if (pTestControl == this)
	{
		CTestControl::ExcuteCommCmdOnDelayAfterFinish(pItem);
	}
	else
	{
		m_pCurrTestControl->CTestControl::ExcuteCommCmdOnDelayAfterFinish(pItem);
	}

	//最后一个
	if (m_pCurrTestControl == GetTail())
	{
		//多装置处理前的判断
		if (NeedTestNextDevice())
		{
			return;
		}

		m_pTCtrlWnd->m_pTestControl = this;
		CGbItemBase *pMainItem = (CGbItemBase*)GetItem(m_pGuideBook, pItem);

		if (pMainItem->m_bIsSubItem)
		{
			if (m_pCurrSubTestItem == NULL)
			{
				TestNextItem();
			}
			else
			{
				TestNextSubItem(pItem);
			}
		}
		else
		{
			TestNextItem();
		}
	}
	else
	{
		if (m_pCurrTestControl == this)
		{
			pTestControl = (CTestControl *)GetHead();
		}
		else
		{
			long nIndex = FindIndex(m_pCurrTestControl) + 1;
			pTestControl = (CTestControl*)GetAt(nIndex);
		}

		m_pCurrTestControl = pTestControl;
		m_pTCtrlWnd->m_pTestControl = m_pCurrTestControl;
		pItem = (CCommCmd*)GetItem(pTestControl->m_pGuideBook, pItem);
		pTestControl->TestItemCommCmdEx(pItem);
	}
}


void CTestControlMngrBase::CreatePpEngineDevice(CProtocolEngineInterface* &pEngine, CPpDeviceRef *pDevieceRef)
{
	CTestControl::CreatePpEngineDevice(pEngine, pDevieceRef);
}


CPpDeviceRef* CTestControlMngrBase::FindPpDeviceRef(WPARAM wParam)
{
	return (CPpDeviceRef*)m_oDeviceRefs.GetHead();
}


CProtocolDeviceInterface* CTestControlMngrBase::FindPpDevice(WPARAM wParam)
{
	CPpDeviceRef *p = (CPpDeviceRef*)m_oDeviceRefs.GetHead();
	CProtocolDeviceInterface* oPpDevice = NULL;

	if (p != NULL)
	{
		oPpDevice = p->m_oPpDevice;
	}

	return oPpDevice;
}


long CTestControlMngrBase::OnUpdateGbItem(CGbItemBase* pGbItem)
{
	CGuideBook *pGuideBook = (CGuideBook *)pGbItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CString strGbFile = pGuideBook->m_strGbXmlFile;

	if (!::IsFileExist(strGbFile))
	{
		strGbFile.Empty();
	}

	if (strGbFile.GetLength() <= 5)
	{
		CWnd *pWnd = AfxGetMainWnd();
		strGbFile = Gb_GetOpenGuideBookFile(g_strGbFileFilter, pWnd);

		if (strGbFile.GetLength() <= 5)
		{
			return -1;
		}
	}

	pGuideBook = new CGuideBook();

	if (!pGuideBook->OpenXMLFile(strGbFile))
	{
		delete pGuideBook;
		return -1;
	}

	CExBaseObject *pScrItemFind = Gb_GetItem(pGuideBook, pGbItem);

	if (pScrItemFind == NULL)
	{
		delete pGuideBook;
		return -1;
	}

	CTestControl::UpdateGbItem(strGbFile, (CGbItemBase *)pScrItemFind);
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl*)GetNext(pos);
		pTestControl->UpdateGbItem(strGbFile, (CGbItemBase *)pScrItemFind);
	}

	delete pGuideBook;
	return 0;
}

void CTestControlMngrBase::ContinueExecutePpEngineCmd(CTestControl *pTestControl)
{
	CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;

	if (pTestControl == this)
	{
		pTestControl = (CTestControl*)GetHead();
		pTestControl->Out_RunProcedure(pApp->GetPpEngineCmdID(), pApp->GetPpEngineCmdPara(), 0, 0, ProcedureType_EngineCmd);
	}
	else
	{
		long nIndex = FindIndex(pTestControl);

		if (nIndex == GetCount() - 1)
		{
			CTestControl::ContinueExecutePpEngineCmd(pTestControl);
			pApp->ResetPpEngineCmd();
		}
		else
		{
			pTestControl = (CTestControl*)GetAtIndex(nIndex+1);
			pTestControl->Out_RunProcedure(pApp->GetPpEngineCmdID(), pApp->GetPpEngineCmdPara(), 0, 0, ProcedureType_EngineCmd);
		}
	}
}


long CTestControlMngrBase::GetDelayBeforeCmd(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();
	return pCmd->GetDelayBeforeCmd();
}

long CTestControlMngrBase::GetDelayAfterCmd(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();
	return pCmd->GetDelayAfterCmd();
}

long CTestControlMngrBase::TestItemMacroTest(CMacroTest* pItem)
{
	//执行主视图测试项目的执行
	long nRet = CTestControl::TestItemMacroTest(pItem);

	//如果测试失败，则返回
	if (nRet < 0)
	{
		return nRet;
	}

	BOOL bHasSubItems = pItem->GetSubGbItemsCount() > 0;
	CReport *pReportSrc = NULL;
	
	//如果有子项目，则创建临时报告
	if (bHasSubItems)
	{
		pReportSrc = pItem->GetReport(-1);
	}

	CopyChildrenTestControlReport(pItem, pReportSrc);

// 	POS pos = GetHeadPosition();
// 	CTestControl *pTestControl = NULL;
// 	CGuideBook *pGuideBook = NULL;
// 	CMacroTest *pCurr = NULL;
// 	CReports *pReports = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pTestControl = (CTestControl *)GetNext(pos);
// 		pGuideBook = pTestControl->m_pGuideBook;
// 		pCurr = (CMacroTest*)GetItem(pGuideBook, pItem);
// 
// 		if (pCurr != NULL)
// 		{
// 			//包含子项目，则克隆报告数据对象
// 			if (bHasSubItems)
// 			{
// 				//pReports = pCurr->GetReports();
// 				//CReport *pReport = (CReport*)pReportSrc->Clone();
// 				CReport *pReport = pCurr->GetReport(-1);
// 				pReport->m_pValues->DeleteAll();
// 				pReportSrc->m_pValues->CopyChildren(pReport->m_pValues);
// 				pReports->AddNewChild(pReport);
// 			}
// 
// 			//设置测试状态，更新界面
// 			pCurr->SetState(TEST_STATE_TESTING);
// 			pTestControl->m_oTCtrlMsgRcv.OnCurrItemStateChanged(pCurr);
// 		}
// 	}

	//测试子项目
	TestFirstSubItems();

	return 0;
}

void CTestControlMngrBase::CopyChildrenTestControlReport(CMacroTest *pMacroTestSrc, CReport *pReportSrc)
{
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pTestControl->m_nMacroTestTimes = m_nMacroTestTimes;
		CopyReportToTestControl(pTestControl, pMacroTestSrc, pReportSrc, FALSE);
	}
}

void CTestControlMngrBase::CopyReportToTestControl(CTestControl *pTestControlDest, CMacroTest *pMacroTestSrc, CReport *pReportSrc, BOOL bIsFinisTest)
{
	CMacroTest  *pCurr = (CMacroTest*)GetItem(pTestControlDest->m_pGuideBook, pMacroTestSrc);

	if (pCurr == NULL)
	{
		return;
	}

	CMacroTestPara *pCurrPara = pCurr->GetMacroTestPara();
	CMacroTestPara *pSrcPara = pMacroTestSrc->GetMacroTestPara();

	pCurrPara->InitTestParaDatas(FALSE);
	pCurrPara->m_pValuesForCal->DeleteAll();

	if (pSrcPara->m_pValuesForCal != NULL)
	{
		pCurrPara->m_pValuesForCal->AppendCloneEx(*(pSrcPara->m_pValuesForCal));
	}

	//包含子项目，则克隆报告数据对象
	CReport *pReport = pCurr->GetReport(-1);

	if (pReportSrc != NULL)
	{
		pReport->m_pValues->DeleteAll();
		pReportSrc->m_pValues->CopyChildren(pReport->m_pValues);
		pTestControlDest->InitFillReport(pReport);
	}
	else
	{
		pTestControlDest->InitFillReport(pCurr);
	}

	//2018-12-23   处理开入偏移
	if (m_bUseBinaryOffset && bIsFinisTest)
	{
		CGuideBookTool::ExtractBinputsResult(pReport->m_pValues, m_nBinRngBegin, m_nBinRngEnd, m_pGuideBook->m_nBinOffset);
		CString strSyntax;
		pCurr->RunResultScript(strSyntax);
	}
	else
	{
		//设置测试状态，更新界面
		//2021-1-5  lijunqing  电气量项目的状态，改为由子项目的状态决定。
		//修改原因：圣普自动测试项目，主项目有子项目不合格，导致后续的其他装置测试的电气量都不合格
		if (pMacroTestSrc->m_oSubGbItems.GetCount() > 0)
		{
			//CString strSyntax;
			//pCurr->RunResultScript(strSyntax);
			Gb_UpdateMacroTestItemTestStateByChildren(pCurr);
		}
		else
		{
			pCurr->SetState(pMacroTestSrc->GetState());
		}
	}

	pTestControlDest->m_oTCtrlMsgRcv.OnCurrItemStateChanged(pCurr);

	//多台装置测试，电气量测试功能，第二台及后续装置如果不合格，发送项目错误消息
	CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;
	pApp->FireTestItemErrorMsg(pCurr, FALSE);
}

long CTestControlMngrBase::FillParentItemsReport(CGbItemBase *pItems)
{
	if (!Gb_IsItemsTestFinished(pItems))
	{
		return 0;
	}

	CGuideBook *pGuideBook = (CGuideBook*)pItems->GetAncestor(GBCLASSID_GUIDEBOOK);
	CGbItemBase *pCurr = NULL;

	//此种模式下，作为单装置或者是主装置测试
	if (pGuideBook == m_pGuideBook)
	{
		CTestControl::FillParentItemsReport(pItems);
	}
	else
	{//从装置测试
		pCurr = (CGbItemBase*)GetItem(m_pGuideBook, pItems);
		CTestControl::FillParentItemsReport(pCurr);
	}

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pGuideBook = pTestControl->m_pGuideBook;
		pCurr = (CGbItemBase*)GetItem(pGuideBook, pItems);
		pTestControl->FillParentItemsReport(pCurr);
	}

	return 0;
}

void CTestControlMngrBase::SetTestItemSelectedState(CGbItemBase *pItem,long nSelect)
{
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CGbItemBase *pCurr = NULL;

	//此种模式下，作为单装置或者是主装置测试
	if (pGuideBook == m_pGuideBook)
	{
		CTestControl::SetTestItemSelectedState(pItem, nSelect);
	}
	else
	{//从装置测试
		pCurr = (CGbItemBase*)GetItem(m_pGuideBook, pItem);
		CTestControl::SetTestItemSelectedState(pCurr, nSelect);
	}

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pCurr = (CGbItemBase*)GetItem(pTestControl->m_pGuideBook, pItem);
		pTestControl->CTestControl::SetTestItemSelectedState(pCurr, nSelect);
	}
}

void CTestControlMngrBase::SetCommCmdRepeatTimes(long nTimes)
{
	m_nCommCmdTestTimes = nTimes;

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pTestControl->m_nCommCmdTestTimes = nTimes;
	}
}


BOOL CTestControlMngrBase::GBS_CanBreakLoop(CGbItemBase *pItem)
{
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	BOOL bAllBreakLoop = TRUE;

	if (GetBreakLoopState() == 0)
	{
		bAllBreakLoop = FALSE;
	}

	//主设备的子报告
	while (pos != NULL)
	{
		pTestControl = (CTestControl*)GetNext(pos);

		if (pTestControl->GetBreakLoopState() == 0)
		{
			bAllBreakLoop = FALSE;
			break;
		}
	}

	return bAllBreakLoop;
}


void CTestControlMngrBase::GBS_ClearBreakLoopState(CGbItemBase *pItem)
{
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CGbItemBase *pCurrItem = (CGbItemBase*)Gb_GetItem(m_pGuideBook, pItem);

	if (pCurrItem != NULL)
	{
		pCurrItem->m_nBreakLoopState = 0;
	}

	//主设备的子报告
	while (pos != NULL)
	{
		pTestControl = (CTestControl*)GetNext(pos);
		pCurrItem = (CGbItemBase*)Gb_GetItem(pTestControl->m_pGuideBook, pItem);

		if (pCurrItem != NULL)
		{
			pCurrItem->m_nBreakLoopState = 0;
		}
	}
}

long CTestControlMngrBase::GBS_RcdCmp_CopyStdFile(CTestControl *pTestControl, CString &strStdSrcFile, CString &strStdDestFile)
{
	ASSERT (FALSE);
	return FALSE;
}

long CTestControlMngrBase::TestFirstSubItems()
{
	long nRet = CTestControl::TestFirstSubItems();

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CMacroTest *pCurr = NULL;
	CGuideBook *pGuideBook = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pGuideBook = pTestControl->m_pGuideBook;

		if (m_pCurrSubTestItem != NULL)
		{
			pCurr = (CMacroTest*)GetItem(pGuideBook, m_pCurrSubTestItem);
			pTestControl->m_pCurrSubTestItem = pCurr;
		}
		else
		{
			pTestControl->m_pCurrSubTestItem = NULL;
		}
	}

	return 0;
}

CGbItemBase* CTestControlMngrBase::GetNextTestSubItem()
{
	CGbItemBase *pNext = CTestControl::GetNextTestSubItem();

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CMacroTest *pCurr = NULL;
	CGuideBook *pGuideBook = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pGuideBook = pTestControl->m_pGuideBook;

		if (m_pCurrSubTestItem != NULL)
		{
			pCurr = (CMacroTest*)GetItem(pGuideBook, m_pCurrSubTestItem);
			pTestControl->m_pCurrSubTestItem = pCurr;
		}
		else
		{
			pTestControl->m_pCurrSubTestItem = NULL;
		}
	}

	return pNext;
}

BOOL CTestControlMngrBase::CanTestFirstSubItems()
{
	return FALSE;
}

long CTestControlMngrBase::CreatemUICommCmdViewDlg(LPVOID pUIViewDlg)
{
	CUICommCmdViewDlg *pUICommCmdViewDlg = (CUICommCmdViewDlg*)pUIViewDlg;
	CTestControl::CreatemUICommCmdViewDlg(pUICommCmdViewDlg);

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	if (pUICommCmdViewDlg == NULL)
	{
		pUICommCmdViewDlg = m_pUICommCmdViewDlg;
	}

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pTestControl->CreatemUICommCmdViewDlg(pUICommCmdViewDlg);
	}

	return 0;
}

void CTestControlMngrBase::InitItemsRsltExprScript(CCommCmd* pItem)
{
	CTestControl::InitItemsRsltExprScript(pItem);

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CCommCmd *pCurr = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pCurr = (CCommCmd*)GetItem(pTestControl->m_pGuideBook, pItem);
		pTestControl->InitItemsRsltExprScript(pCurr);
	}
}

void CTestControlMngrBase::AttachTestControlWnd(CTestControlWnd *pWndRef)
{
	if (m_pTCtrlWnd == NULL)
	{
		CreateTestControlWnd(pWndRef);
	}

	POS pos = GetHeadPosition();
	CTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		p->CreateTestControlWnd(pWndRef);
	}
}

BOOL CTestControlMngrBase::ContinueTestByItemsRsltExprScript(CCommCmd* pItem)
{
	return CTestControl::ContinueTestByItemsRsltExprScript(pItem);
}

long CTestControlMngrBase::FinishTestItemMacroTest_OnlyEx(CTestControl *pTestControl, CMacroTest* pItem)
{
	CReport *pReportSrc = pItem->GetReport(-1);
	CGuideBook *pGuideBook = NULL;
	CMacroTest *pCurr = NULL;
	CReports *pReports = NULL;
	CReport *pReport = NULL;
	BOOL bHasSubItems = pItem->GetSubGbItemsCount() > 0;

	pGuideBook = pTestControl->m_pGuideBook;
	pCurr = (CMacroTest*)GetItem(pGuideBook, pItem);

	if (pCurr == NULL)
	{
		return 0;
	}

	pReports = pCurr->GetReports();

	//有子项目，则复制数据
	if (bHasSubItems)
	{
		pReport = (CReport *)pReports->GetTail();
		pReportSrc->Copy(pReport);
	}
	else
	{
		//没有子项目，则克隆报告数据
		//pReport = (CReport*)pReportSrc->Clone();
		//pReports->AddNewChild(pReport);
		pReport = pCurr->GetReport(-1);
		pReport->m_pValues->DeleteAll();
		pReportSrc->m_pValues->CopyChildren(pReport->m_pValues);
	}

	pTestControl->UpdateStateAfterFinishTestItem(pCurr);
	pTestControl->FillReport(pReport, m_nMacroTestTimes);

	//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
	//因此单独执行
	pTestControl->WriteItemTempFile(pCurr);


	return 0;
}

void CTestControlMngrBase::ClearSysRptFill(CGbItemBase *pItem)
{
	CGbItemBase *pCurrItem = NULL;
	pCurrItem = (CGbItemBase*)GetItem(m_pGuideBook, pItem);
	CTestControl::ClearSysRptFill(pCurrItem);

	POS pos = GetHeadPosition();
	CTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		pCurrItem = (CGbItemBase*)GetItem(p->m_pGuideBook, pItem);
		p->ClearSysRptFill(pCurrItem);
	}
}

void CTestControlMngrBase::ClearTestSubItem(BOOL bClearMain)
{
	if (bClearMain)
	{
		m_pCurrSubTestItem = NULL;
	}

	POS pos = GetHeadPosition();
	CTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		p->m_pCurrSubTestItem = NULL;
	}
}

void CTestControlMngrBase::EditItemPara(CCommCmd *pCommCmd, CValue *pValue)
{
	CCommCmd *pFind = (CCommCmd*)GetItem(m_pGuideBook, pCommCmd);
	EditCommCmdPara(pFind, pValue);

	POS pos = GetHeadPosition();
	CTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		pFind = (CCommCmd*)GetItem(p->m_pGuideBook, pCommCmd);
		p->EditCommCmdPara(pFind, pValue);
	}
}

long CTestControlMngrBase::SelectAllTestControl(CExBaseList &listTestControl, BOOL bMainFirst)
{
	POS pos = GetHeadPosition();
	CTestControl *p = NULL;

	if (bMainFirst)
	{
		listTestControl.AddTail(this);
	}

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		listTestControl.AddTail(p);
	}

	if (!bMainFirst)
	{
		listTestControl.AddTail(this);
	}

	return listTestControl.GetCount();
}

void CTestControlMngrBase::SetTestEndTime()
{
	CTestControl::SetTestEndTime();

	POS pos = GetHeadPosition();
	CTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		p->SetTestTime(m_pGuideBook->GetTestBeginTime(), m_pGuideBook->GetTestEndTime());
	}
}

void CTestControlMngrBase::SetTestTime(CDvmData *pTestBeginTime, CDvmData *pTestEndTime)
{
	if (pTestBeginTime == NULL)
	{
		pTestBeginTime = m_pGuideBook->GetTestBeginTime();
	}

	if (pTestEndTime == NULL)
	{
		pTestEndTime = m_pGuideBook->GetTestEndTime();
	}

	CTestControl::SetTestTime(pTestBeginTime, pTestEndTime);

	POS pos = GetHeadPosition();
	CTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		p->SetTestTime(pTestBeginTime, pTestEndTime);
	}
}


CReport* CTestControlMngrBase::AddReport(CGbItemBase* pItem, long nRepeatTimes, long nTestIndex)
{
// 	if (pItem->GetClassID() != GBCLASSID_MACROTEST)
// 	{
// 		return CTestControl::AddReport(pItem, nRepeatTimes, nTestIndex);
// 	}
// 
	CGbItemBase *pCurrItem = NULL;
	pCurrItem = (CGbItemBase*)GetItem(m_pGuideBook, pItem);

	CReport *pReport = CTestControl::AddReport(pCurrItem, nRepeatTimes, nTestIndex);
	POS pos = GetHeadPosition();
	CTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		pCurrItem = (CGbItemBase*)GetItem(p->m_pGuideBook, pItem);
		p->AddReport(pCurrItem, nRepeatTimes, nTestIndex);
	}

	return pReport;
}

BOOL CTestControlMngrBase::ItemsRsltExprScriptTimeIgnore()
{
	return CTestControl::ItemsRsltExprScriptTimeIgnore();
}

void CTestControlMngrBase::EditItemPara(CMacroTest *pMacroTest, CShortData  *pData)
{
	CMacroTest *pFind = (CMacroTest*)GetItem(m_pGuideBook, pMacroTest);
	EditMacroTestPara(pFind, pData);

	POS pos = GetHeadPosition();
	CTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		pFind = (CMacroTest*)GetItem(p->m_pGuideBook, pMacroTest);
		p->EditMacroTestPara(pFind, pData);
	}
}

void CTestControlMngrBase::AfterUpdateMacroTestReport(CMacroTest* pItem, long nMacroTestTimes)
{
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CReport *pReport = pItem->GetReport(-1);

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		CopyReportToTestControl(pTestControl, pItem, pReport, TRUE);
		CMacroTest *pCurr = (CMacroTest*)GetItem(pTestControl->m_pGuideBook, pItem);
		CReport *pReportCurr = pCurr->GetReport(-1);
		pTestControl->FillReport(pReportCurr, nMacroTestTimes);
	}
}

void CTestControlMngrBase::AfterCreateMtFinalReport(CMacroTest* pItem, long nMacroTestTimes)
{
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CReport *pReport = pItem->GetReport(-1);

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		CopyReportToTestControl(pTestControl, pItem, pReport, TRUE);
		CMacroTest *pCurr = (CMacroTest*)GetItem(pTestControl->m_pGuideBook, pItem);
		CReport *pReportCurr = pCurr->GetReport(-1);
		pTestControl->FillReport(pReportCurr, nMacroTestTimes);
	}
}

// long CTestControlMngrBase::FinishTestItemMacroTest_Only(CMacroTest* pItem)
// {
// 	FinishTestItemMacroTest_Report(pItem);
// 
// 	return CTestControl::FinishTestItemMacroTest_Process(pItem);
// }


LRESULT CTestControlMngrBase::OnElectricTestAppMsg(WPARAM wPara,LPARAM lPara)
{
	return CTestControl::OnElectricTestAppMsg(wPara, lPara);
}

LRESULT CTestControlMngrBase::OnElectricTestMsg(WPARAM wPara,LPARAM lPara)
{
	return CTestControl::OnElectricTestMsg(wPara, lPara);
}

LRESULT CTestControlMngrBase::OnCommCommandMsg(WPARAM wPara,LPARAM lPara)
{
	ASSERT (m_pCurrTestControl != NULL);

	if (m_pCurrTestControl == this)
	{
		return CTestControl::OnCommCommandMsg(wPara, lPara);
	}
	else
	{
		return m_pCurrTestControl->OnCommCommandMsg(wPara, lPara);
	}
}

LRESULT CTestControlMngrBase::OnSafetyTestFinished(WPARAM wPara,LPARAM lPara)
{
	return CTestControl::OnSafetyTestFinished(wPara, lPara);
}

LRESULT CTestControlMngrBase::OnSysParaEditTestFinished(WPARAM wPara,LPARAM lPara)
{
	return CTestControl::OnSysParaEditTestFinished(wPara, lPara);
}

LRESULT CTestControlMngrBase::OnCommCmdMamualTestFinished(WPARAM wPara,LPARAM lPara)
{
	return CTestControl::OnCommCmdMamualTestFinished(wPara, lPara);
}

LRESULT CTestControlMngrBase::OnManualTestMsg(WPARAM wPara,LPARAM lPara)
{
	return CTestControl::OnManualTestMsg(wPara, lPara);
}

LRESULT CTestControlMngrBase::OnEngineSystemMessage(WPARAM wParam, LPARAM lParam)
{
	ASSERT (m_pCurrTestControl != NULL);

	if (m_pCurrTestControl == this)
	{
		return CTestControl::OnEngineSystemMessage(wParam, lParam);
	}
	else
	{
		return m_pCurrTestControl->OnEngineSystemMessage(wParam, lParam);
	}
}


long CTestControlMngrBase::FinishTestItemMacroTest_Process(CMacroTest* pItem) //2019-4-27 MdvTestEach
{
	return CTestControl::FinishTestItemMacroTest_Process(pItem);
}

void CTestControlMngrBase::ReleaseMacroTestInterface(BOOL bRelease)
{
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pTestControl->ReleaseMacroTestInterface(bRelease);
	}
}

//////////////////////////////////////////////////////////////////////////
//
CTestControlMngrBase* tctrl_GetTestControlMngr(CExBaseObject *pItem)
{
	CTestControl *pTestControl = (CTestControl*)tctrl_GetTestControl(pItem);

	if (pTestControl->IsTestControlMngr())
	{
		return (CTestControlMngrBase*)pTestControl;
	}
	else
	{
		pTestControl = (CTestControl *)pTestControl->GetParent();
		return  (CTestControlMngrBase*)pTestControl;
	}
}

BOOL tctrl_IsTailTestControlItem(CExBaseObject *pItem)
{
	CTestControlMngrBase *pMngr = tctrl_GetTestControlMngr(pItem);
	CTestControl *pTestControl = (CTestControl*)tctrl_GetTestControl(pItem);

	if (pMngr->GetCount() == 0)
	{
		return TRUE;
	}

	return (pMngr->GetTail() == pTestControl);
}
