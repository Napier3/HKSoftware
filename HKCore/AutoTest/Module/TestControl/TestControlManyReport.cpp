#include "stdafx.h"
#include "TestControlManyReport.h"
#include "TestControlWnd.h"
#include "../TCtrlCntrWorkSpace.h"
#include "TCtrlCntrBaseApp.h"
#include "../GuideBook\Script/GbScript_GlobalDefine.h"
#include "..\..\..\Module\KeyDb\XMatchToolBase.h"
#include <math.h>

#include "../XRecorderDlg.h"
#include "..\..\..\Module\EpotoInterface\EpotoInterface.h"
#include "..\..\..\Module\DataMngr\DatasetValid\DsvViewResultDialog.h"

#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#define _debug_TestControlManyReport

//////////////////////////////////////////////////////////////////////////
//CTestControlManyReportChild
CTestControlManyReportChild::CTestControlManyReportChild()
{
	m_bSingleTestControl = FALSE;
}

CTestControlManyReportChild::~CTestControlManyReportChild()
{

}

//返回FALSE，表示通讯命令项目执行完毕，不进行下一步的项目执行
//而是有管理对象执行下一个项目的判断和执行
BOOL CTestControlManyReportChild::ProcessAfterCommCmdFinish(CCommCmd *pCommCmd)
{
	return FALSE;
}

void CTestControlManyReportChild::ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem)
{
#ifdef _debug_TestControlManyReport
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CTestControlManyReportChild::ExcuteCommCmdOnDelayBeforeFinish"));
#endif

	CTestControl::ExcuteCommCmdOnDelayBeforeFinish(pItem);
}


BOOL CTestControlManyReportChild::ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem)
{
	CTestControlManyReport *pMainDevice = (CTestControlManyReport*)GetParent();
	return pMainDevice->ExcuteCommCmdOnDelayAfterFinish_Repeat(pItem);
}

//项目执行完毕后的处理，有CTestControlManyReport统一处理
void CTestControlManyReportChild::ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem)
{
#ifdef _debug_TestControlManyReport
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CTestControlManyReportChild::ExcuteCommCmdOnDelayAfterFinish"));
#endif

	CTestControlManyReport *pMainDevice = (CTestControlManyReport*)GetParent();
	pMainDevice->ExcuteCommCmdOnDelayAfterFinish(pItem);
}

BOOL CTestControlManyReportChild::CreatePpEngineDevice(CCommCmd *pCmd)
{
#ifdef _debug_TestControlManyReport
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CreatePpEngineDevice"));
#endif
	return TRUE;
}

CPpDeviceRef* CTestControlManyReportChild::FindPpDeviceRef(WPARAM wParam)
{
	CTestControlManyReport *pMainDevice = (CTestControlManyReport*)GetParent();
	return pMainDevice->FindPpDeviceRef(wParam);
}


CProtocolDeviceInterface* CTestControlManyReportChild::FindPpDevice(WPARAM wParam)
{
	CTestControlManyReport *pMainDevice = (CTestControlManyReport*)GetParent();
	return pMainDevice->FindPpDevice(wParam);
}

long CTestControlManyReportChild::StopTestExtern(const CString &strMsg, BOOL bExtern)
{
	CTestControlManyReport *pMainDevice = (CTestControlManyReport*)GetParent();
	return pMainDevice->StopTestExtern(strMsg, bExtern);
}

long CTestControlManyReportChild::OnUpdateGbItem(CGbItemBase* pGbItem)
{
	CTestControlManyReport *pMainDevice = (CTestControlManyReport*)GetParent();
	return pMainDevice->OnUpdateGbItem(pGbItem);
}

void CTestControlManyReportChild::ContinueExecutePpEngineCmd(CTestControl *pTestControl)
{
	CTestControl::ContinueExecutePpEngineCmd(pTestControl);
	CTestControlManyReport *pMainDevice = (CTestControlManyReport*)GetParent();
	return pMainDevice->ContinueExecutePpEngineCmd(this);
}

//通讯前延时、通讯后延时有CTestControlManyReport统一处理
long CTestControlManyReportChild::GetDelayBeforeCmd(CCommCmd* pItem)
{
	CTestControlManyReport *pMainDevice = (CTestControlManyReport*)GetParent();
	return pMainDevice->GetDelayBeforeCmd(pItem);
}

long CTestControlManyReportChild::GetDelayAfterCmd(CCommCmd* pItem)
{
	CTestControlManyReport *pMainDevice = (CTestControlManyReport*)GetParent();
	return pMainDevice->GetDelayAfterCmd(pItem);
}


CProtocolDeviceInterface* CTestControlManyReportChild::GetDevicePtr(CCommCmd* pItem)
{
	CTestControlManyReport *pMainDevice = (CTestControlManyReport*)GetParent();
	return pMainDevice->GetDevicePtr(pItem);
}

CProtocolDeviceInterface* CTestControlManyReportChild::GetDevicePtr()
{
	CTestControlManyReport *pMainDevice = (CTestControlManyReport*)GetParent();
	return pMainDevice->GetDevicePtr();
}

//////////////////////////////////////////////////////////////////////////
//CTestControlManyReport
CTestControlManyReport::CTestControlManyReport()
{
	
}

CTestControlManyReport::~CTestControlManyReport()
{

}

CTestControl* CTestControlManyReport::CreateChildTest()
{
	return new CTestControlManyReportChild();
}

void CTestControlManyReport::SetTestItemState(CGbItemBase* pItem, UINT nState)
{
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);

	if (pGuideBook == m_pGuideBook)
	{
		return CTestControl::SetTestItemState(pItem, nState);
	}
	else
	{
		POS pos = GetHeadPosition();
		CTestControl *pTestControl = NULL;
		CGbItemBase *p = NULL;

		while (pos != NULL)
		{
			pTestControl = (CTestControl *)GetNext(pos);
			p = (CGbItemBase *)GetItem(pTestControl->m_pGuideBook, pItem);
			pTestControl->SetTestItemState(p, nState);
		}
	}
}

//1，根据TestTask创建任务
//2，根据扩展数据初始化测试
void CTestControlManyReport::InitByTask(CTestTask *pTestTask, BOOL bCreate)
{
	CTestControlMngrBase::InitByTask(pTestTask, bCreate);

// 	POS pos = pTestTask->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 	CDvmDataset *pExpandData = NULL;
// 	long nIndex = 0;
// 
// 	while (pos != NULL)
// 	{
// 		p = pTestTask->GetNext(pos);
// 
// 		if (p->GetClassID() == DVMCLASSID_CDVMDATASET)
// 		{
// 			pExpandData = (CDvmDataset *)p;
// 			break;
// 		}
// 	}

	if (bCreate)
	{
		CDvmDataset *pExpandData = pTestTask->GetCommCmdManyConfig();
		ImportExpandDatas(pExpandData);
	}
}

BOOL CTestControlManyReport::CreateTest()
{
	CString strCurrTask = CTCtrlCntrWorkSpace::s_GetLastTaskFile();

	OpenTaskFile(strCurrTask);

	return TRUE;
}

BOOL CTestControlManyReport::CreateTest(const CString &strGbBinaryFile, BOOL bFullPath)
{
	if (!bFullPath)
	{
		m_strGbBinaryFile = GetGuideBookBinaryFileName(strGbBinaryFile);
	}
	else
	{
		m_strGbBinaryFile = strGbBinaryFile;
	}

	OpenTaskFile(strGbBinaryFile);

	return TRUE;
}

long CTestControlManyReport::FillReportEx(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible)
{
	CGuideBook *pGuideBook = (CGuideBook *)pReport->GetAncestor(GBCLASSID_GUIDEBOOK);

	if (pGuideBook == m_pGuideBook)
	{
		return CTestControl::FillReportEx(pReport, nRepeatIndex, nInsertDataLinkWhenEligible);
	}
	else
	{
		long nIndex = FindIndexByGuideBook(pGuideBook);

		if (nIndex == -1)
		{
			return 0;
		}

		CTestControl *pTestControl = (CTestControl*)GetAtIndex(nIndex);

		if (pTestControl != NULL)
		{
			pTestControl->FillReportEx(pReport, nRepeatIndex, nInsertDataLinkWhenEligible);
		}
	}

	return 0;
}

void CTestControlManyReport::ImportExpandDatas(CDvmDataset *pDataset)
{
	if (pDataset == NULL)
	{
		return;
	}

	long nIndex = 0;
	long nDeviceID = 0;
	m_pGuideBook->ImportExpandDatas(pDataset);
	nDeviceID = GetDvmID(this, DATAID_LDEVICEID, nIndex);
	m_pGuideBook->m_strID = GetLdName(pDataset, nDeviceID);//nIndex);

	POS pos = GetHeadPosition();
	CTestControl *p = NULL;
	nIndex++;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		p->m_pGuideBook->ImportExpandDatas(pDataset);
		nDeviceID = GetDvmID(p, DATAID_LDEVICEID, nIndex);
		p->m_pGuideBook->m_strID = GetLdName(pDataset, nDeviceID);//nIndex);
		nIndex++;
	}
}

long CTestControlManyReport::GetDvmID(CTestControl *pTestControl, const CString &strDvmDataID, long nDefaultID)
{
	CDevice *pDevice = pTestControl->m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return nDefaultID;
	}

	CSysParas *pSysParas = pDevice->GetSysParas();
	CDataObj *pData = (CDataObj*)pSysParas->FindByID(strDvmDataID);

	if (pData == NULL)
	{
		return nDefaultID;
	}

	long nDvmDataID = CString_To_long(pData->m_strValue);

	if (nDvmDataID < 0)
	{
		return nDefaultID;
	}
	else
	{
		return nDvmDataID;
	}
}

CString CTestControlManyReport::GetLdName(CDvmDataset *pExpandDataset, long nIndex)
{
	POS pos = pExpandDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	long nTemp = 0;
	CString strName;

	while (pos != NULL)
	{
		pDvmData = (CDvmData *)pExpandDataset->GetNext(pos);

		if (pDvmData->m_strValue == _T("1"))
		{
			if (nIndex == nTemp)
			{
				strName = pDvmData->m_strFormat;
				break;
			}

			nTemp++;
		}
	}

	return strName;
}

long CTestControlManyReport::FindDatas(CDvmDataset *pSrc, CDvmDataset *pDest, const CString &strID)
{
	POS pos = pSrc->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pSrc->GetNext(pos);

		if (pData->m_strFormat == strID)
		{
			pDest->AddTail(pData);
		}
	}

	return pDest->GetCount();
}

long CTestControlManyReport::ProcessFinishCommCmdReadSOE(CCommCmd* pItem,CDvmDataset *pDataset)
{
	CDvmDataset oDataset;

	//主测试的报告数据
	if (GetCount() == 0)
	{
		oDataset.Append(pDataset);
	}
	else if (m_pGuideBook->m_strID.GetLength() == 0)
	{
		oDataset.Append(pDataset);
	}
	else
	{
		if (pItem->IsCmdExecModeForMgbrpt_MainRpt())
		{
			oDataset.Append(pDataset);
		}
		else
		{
			FindDatas(pDataset, &oDataset,  m_pGuideBook->m_strID);
		}

		if (pDataset->GetCount() > 0 && oDataset.GetCount() == 0)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s[%s] find no soe")
				, GetGbBinaryFileNameShort(), m_pGuideBook->m_strID);
		}
	}

	CTestControl::ProcessFinishCommCmdReadSOE(pItem, &oDataset);

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CCommCmd* pItemFind = NULL;

	//各子测试的报告数据
	while (pos != NULL)
	{
		oDataset.RemoveAll();
		pTestControl = (CTestControl *)GetNext(pos);

		if (pItem->IsCmdExecModeForMgbrpt_MainRpt())
		{
			oDataset.Append(pDataset);
		}
		else
		{
			FindDatas(pDataset, &oDataset, pTestControl->m_pGuideBook->m_strID);
		}

		if (pDataset->GetCount() > 0 && oDataset.GetCount() == 0)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s[%s] find no soe")
				, GetGbBinaryFileNameShort(), m_pGuideBook->m_strID);
		}

		pItemFind = (CCommCmd*)GetItem(pTestControl->m_pGuideBook, pItem);

		if (pItemFind != NULL)
		{
			pTestControl->CTestControl::ProcessFinishCommCmdReadSOE(pItemFind, &oDataset);
			pTestControl->CTestControl::UpdateStateAfterFinishTestItem(pItemFind);

			//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
			//因此单独执行
			pTestControl->CTestControl::WriteItemTempFile(pItemFind);

		}
	}

	oDataset.RemoveAll();

	return 0;
}

CDataObj* CTestControlManyReport::GBS_GetDsDataObj(CGbItemBase *pItem, long nDeviceIndex, const char* pszID)
{
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CDevice *pDevice = pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return 0;
	}

	CString strID ;
	strID = pszID;

	strID.Replace(m_pGuideBook->m_strID, pGuideBook->m_strID);

	CDataObj *pData = pDevice->FindDataObjByID(strID, nDeviceIndex);

	return pData;
}

double CTestControlManyReport::GBS_GetDsDataValueEx(CGbItemBase *pItem, long nDeviceIndex, const char* pszID)
{
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CDevice *pDevice = pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return 0;
	}

	CString strID ;
	strID = pszID;

	strID.Replace(m_pGuideBook->m_strID, pGuideBook->m_strID);

	CExBaseList *pData = pDevice->FindDataObjByID(strID, nDeviceIndex);
	CString strValue;
	
	if (pData->GetClassID() == GBCLASSID_DATAOBJ_VALUE)
	{
		CDataObjValue *pVale = (CDataObjValue *)pData;
		strValue = pVale->m_strValue;
	}
	else
	{
		CDataObj *pDataObj = (CDataObj *)pData;
		strValue = pDataObj->m_strValue;
	}

	double dValue = 1;

	if (pData != NULL)
	{
#ifdef _UNICODE
		dValue = _wtof(strValue);
#else
		dValue = atof(strValue);
#endif
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_DataIDUnext/*L"数据ID(%s)不存在"*/, (CString)pszID);
	}

	return dValue;
}

long CTestControlManyReport::GetDelayBeforeCmd(CCommCmd* pItem)
{
	CTestControl *pTestControl = GetTestControl(pItem);

	if (pTestControl == this)
	{
		CCmd *pCmd = pItem->GetCmd();
		return pCmd->GetDelayBeforeCmd();
	}
	else
	{
		return 0;
	}
}

long CTestControlManyReport::GetDelayAfterCmd(CCommCmd* pItem)
{
	CTestControl *pTestControl = GetTestControl(pItem);

	if (pTestControl == GetTail())
	{
		CCmd *pCmd = pItem->GetCmd();
		return pCmd->GetDelayAfterCmd();
	}
	else
	{
		return 0;
	}
}

CProtocolDeviceInterface* CTestControlManyReport::GetDevicePtr(CCommCmd* pItem)
{
	CTestControl *pTestControl = GetTestControl(pItem);

	if (pTestControl == this)
	{
		return CTestControl::GetDevicePtr(pItem);
	}
	else
	{
		return CTestControl::GetDevicePtr(pItem);
	}
}

CProtocolDeviceInterface* CTestControlManyReport::GetDevicePtr()
{
	return CTestControl::GetDevicePtr();
}

BOOL CTestControlManyReport::ProcessAfterCommCmdFinish(CCommCmd *pCommCmd)
{
	return FALSE;
}

void CTestControlManyReport::ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem)
{
	//CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);

	return CTestControl::ExcuteCommCmdOnDelayBeforeFinish(pItem);
}

BOOL CTestControlManyReport::ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem)
{
	ASSERT (FALSE);
	return CTestControl::ExcuteCommCmdOnDelayAfterFinish_Repeat(pItem);
}

BOOL CTestControlManyReport::TestNextReport(CTestControl *pTestControl, CCommCmd* pItem)
{
	if (pTestControl == this)
	{
		pTestControl = (CTestControl *)GetHead();
	}
	else
	{
		long nIndex = FindIndex(pTestControl) + 1;
		pTestControl = (CTestControl*)GetAt(nIndex);
	}

	pTestControl->m_nItemsRsltExprScriptIndex = m_nItemsRsltExprScriptIndex;
	m_pTCtrlWnd->m_pTestControl = pTestControl;
	CCommCmd *pCurrItem = (CCommCmd*)GetItem(pTestControl->m_pGuideBook, pItem);
	//pTestControl->TestItemCommCmdEx(pCurrItem);
	m_pUICommCmdViewDlg->InitTestItem(pCurrItem, pTestControl->GetGbBinaryFileNameShort());
	pTestControl->ExcuteCommCmdOnDelayBeforeFinish(pCurrItem);

	return TRUE;
}

BOOL CTestControlManyReport::TestByItemsRsltExprScript(CCommCmd* pItem)
{
	if (m_pItemsRsltExprScript == NULL)
	{	
		return FALSE;
	}

	CCommCmd* pMainItem =  (CCommCmd*)GetItem(m_pGuideBook, pItem);

	if (!IsAllItemQualified(pMainItem))
	{
		if (m_nItemsRsltExprScriptIndex < m_nItemsRsltExprScriptMaxRead)
		{
			if (!pMainItem->IsReadSoe())
			{
				CCmd *pCmd = pMainItem->GetCmd();
				CReport *pReport = AddReport(pMainItem, pCmd->m_nRepeatTimes, m_nCommCmdTestTimes);//2017.05.17
			}

			pMainItem->SetState(TEST_STATE_TESTING);
			Gb_UpdateGbItemParentTestState(pMainItem);
			m_pTCtrlWnd->m_pTestControl = this;
			m_pUICommCmdViewDlg->InitTestItem(pMainItem, m_strGbBinaryFileName);
			m_pUICommCmdViewDlg->InitTestItem(m_nItemsRsltExprScriptMaxRead, m_nItemsRsltExprScriptIndex+1, m_nItemsRsltExprScriptTimerLong);
			m_pUICommCmdViewDlg->ShowCommMessage(_T("通讯中......."), TRUE);
			m_pTCtrlWnd->SetTimer(TIMER_DELAY_CMM_CMD_ITEMSEXPR, m_nItemsRsltExprScriptTimerLong, NULL);
			return TRUE;
		}
	}

	return FALSE;
}

void CTestControlManyReport::CloneCommCmdReportToSubReports(CCommCmd* pItem)
{
	CReport *pReportSrc = pItem->GetReport(-1);
	CGbItemBase *pNewForRptDB = NULL;

	if (m_pGuideBook->IsSaveRptToDB() || g_theTCtrlCntrApp->IsSaveRptToDB())
	{
		CString strTempFilePath = ats_GetBinaryTempFilePath(pItem);
		CString strTempFileName = ats_GetBinaryTempFile(strTempFilePath, pItem);
		pNewForRptDB = pItem->CloneForTempFile();
		pNewForRptDB->SetParent(pItem->GetParent());
		pNewForRptDB->OpenBinaryTempFile(strTempFileName);
		pReportSrc = pNewForRptDB->GetReport(-1);
	}

	CReport *pReportDst = NULL;
	ASSERT (pReportSrc != NULL);

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CCommCmd *pCommCmd = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pCommCmd = (CCommCmd *)Gb_GetItem(pTestControl->m_pGuideBook, pItem);
		ASSERT (pCommCmd != NULL);

		if (pCommCmd == NULL)
		{
			continue;
		}

		pReportDst = (CReport*)pCommCmd->GetReport(-1);
		pReportSrc->CopyOwn(pReportDst);
		pTestControl->UpdateStateAfterFinishTestItem(pCommCmd);

		//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
		//因此单独执行
		WriteItemTempFile(pCommCmd);

	}

	if (pNewForRptDB != NULL)
	{
		delete pNewForRptDB;
	}
}

void CTestControlManyReport::ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem)
{
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();

	if (pTestControl == this)
	{//主测试报告
		CTestControl::ExcuteCommCmdOnDelayAfterFinish(pItem);
	}
	else
	{
		pTestControl->CTestControl::ExcuteCommCmdOnDelayAfterFinish(pItem);
	}

	/*以下处理的多报告*/
	if (pItem->IsCmdExecModeForMgbrpt_MainRpt())
	{//多报告测试，克隆报告，继续下一个项目的测试
		CloneCommCmdReportToSubReports(pItem);
	}
	else
	{
		if (!IsTailItem(pItem))
		{	//不是最后一个，继续下一个报告的测试
			TestNextReport(pTestControl, pItem);
			return;
		}
	}
	/*以上处理的多报告*/

	if (NeedTestNextDevice())
	{
		return;
	}

	//ItemsRsltExprScript处理，如果全部合格，则结束，判断是否到了最大次数
	if (TestByItemsRsltExprScript(pItem))
	{
		return;
	}

	//下一个项目的测试
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
			TestNextSubItem(pMainItem);
		}
	}
	else
	{
		TestNextItem();
	}
}

BOOL CTestControlManyReport::IsAllItemQualified(CCommCmd* pItem)
{
	CCommCmd *pFind = (CCommCmd *)GetItem(m_pGuideBook, pItem);;

	if (pFind->GetRsltJdg() == 0)
	{
		return FALSE;
	}

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);

		pFind = (CCommCmd *)GetItem(pTestControl->m_pGuideBook, pItem);

		if (pFind != NULL)
		{
			if (pFind->GetRsltJdg() == 0)
			{
				bTrue = FALSE;
				break;
			}
		}
	}

	return bTrue;
}


long CTestControlManyReport::GetLdIndex(const CString &strLdevice)
{
	long nPos = strLdevice.GetLength() - 1;
	long nLastPos = nPos;

	if (nPos <= 0)
	{
		return -1;
	}

	long nIndex = -1;
	char ch = 0;
	BOOL bFind = FALSE;

	while (TRUE)
	{
		ch = strLdevice[nPos];

		if ('0' <= ch && ch <= '9')
		{
			nLastPos = nPos;
			bFind = TRUE;
			nPos--;
		}
		else
		{
			break;
		}
	}

	if (bFind)
	{
		CString strIndex = strLdevice.Mid(nLastPos);
		nIndex = CString_To_long(strIndex);
	}

	return nIndex;
}


CDvmLogicDevice* CTestControlManyReport::FindByLdIndex(CDvmDevice *pDevice, long nLdIndex)
{
	POS pos = pDevice->GetHeadPosition();
	CDvmLogicDevice *p = NULL, *pFind = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = (CDvmLogicDevice *)pDevice->GetNext(pos);
		nIndex = GetLdIndex(p->m_strID);

		if (nIndex == nLdIndex)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CCpu* CTestControlManyReport::FindCpu0()
{
	CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return NULL;
	}

	CCpus *pCpus = pDevice->GetCpus();
	POS pos = pCpus->GetHeadPosition();
	CCpu *pCpu = NULL;

	while (pos != NULL)
	{
		pCpu = (CCpu *)pCpus->GetNext(pos);

		if (GetLdIndex(pCpu->m_strID) == 0)
		{
			return pCpu;
		}
	}

	return NULL;
}

void CTestControlManyReport::UpdateDvmLdeviceID()
{
	if (m_pGuideBook->m_strPpEngineProgID != g_strPpEngineProgIDMms)
	{
		return;
	}

	CDvmDevice oDvmDevice;
	CProtocolDeviceInterface* oPoDevice = m_oDeviceRefs.Find(0, 0);
	_bstr_t strLdXml = oPoDevice->GetXmlDataLD();
	oDvmDevice.SetXml(strLdXml, CDataMngrXmlRWKeys::g_pXmlKeys);

	if (oDvmDevice.GetCount() == 0)
	{
		return;
	}

	CDvmLogicDevice *pLdevice = NULL;
	CDvmLogicDevice *pLdevice0 = FindByLdIndex(&oDvmDevice, 0);
	CCpu *pCpu0 = FindCpu0();

	if (pCpu0 != NULL && pLdevice0 != NULL)
	{
		if (pCpu0->m_strID == pLdevice0->m_strID)
		{
			return;
		}
	}

	long nLdIndex = 0;
	nLdIndex = GetLdIndex(m_pGuideBook->m_strID);

	if (nLdIndex != -1)
	{
		pLdevice = FindByLdIndex(&oDvmDevice, nLdIndex);

		if (pLdevice != NULL)
		{
			UpdateDvmLdeviceID(this, pCpu0, pLdevice0, pLdevice);
		}
	}

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl*)GetNext(pos);
		nLdIndex = GetLdIndex(pTestControl->m_pGuideBook->m_strID);

		if (nLdIndex == -1)
		{
			continue;
		}

		pLdevice = FindByLdIndex(&oDvmDevice, nLdIndex);

		if (pLdevice != NULL)
		{
			UpdateDvmLdeviceID(pTestControl, pCpu0, pLdevice0, pLdevice);
		}
	}
}

BOOL CTestControlManyReport::EditCommCmdDatasetPath(CItems* pItems)
{
	CItemsRsltExprScript *pItemsRsltExprScript = pItems->GetItemsRsltExprScript(FALSE);
	
	if (pItemsRsltExprScript != NULL)
	{
		pItemsRsltExprScript->m_strDatasetID.Replace(m_strSrcLDevice, m_strDestLDevice);
	}

	EditCommCmdDatasetPath((CExBaseList*)pItems);

	return TRUE;
}

BOOL CTestControlManyReport::EditCommCmdDatasetPath(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();
	pCmd->m_strDatasetPath.Replace(m_strSrcLDevice, m_strDestLDevice);

	return TRUE;
}

BOOL CTestControlManyReport::EditCommCmdDatasetPath(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			EditCommCmdDatasetPath((CItems*)p);
		}
		else if (nClassID == GBCLASSID_MACROTEST)
		{
			EditCommCmdDatasetPath((CExBaseList*)p);
		}
		else if (nClassID == GBCLASSID_COMMCMD)
		{
			EditCommCmdDatasetPath((CCommCmd*)p);
		}
	}

	return TRUE;
}

BOOL CTestControlManyReport::EditCommCmdDatasetPath(CGuideBook *pGuideBook)
{
	POS pos = pGuideBook->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pGuideBook->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_DEVICE)
		{
			EditCommCmdDatasetPath((CDevice*)p);
		}
	}

	return TRUE;
}

void CTestControlManyReport::UpdateDvmLdeviceID(CTestControl *pTestControl, CCpu *pCpu0, CDvmLogicDevice *pLd0, CDvmLogicDevice *pLdCurr)
{
	if (pLdCurr->m_strID == pTestControl->m_pGuideBook->m_strID)
	{
		return;
	}

	//逻辑设备
	m_strSrcLDevice = pTestControl->m_pGuideBook->m_strID;
	m_strDestLDevice = pLdCurr->m_strID;
	EditCommCmdDatasetPath(pTestControl->m_pGuideBook);
	pTestControl->m_pGuideBook->m_strID = pLdCurr->m_strID;
	
	//逻辑设备0
	if (pCpu0 != NULL && pLd0 != NULL)
	{
		m_strSrcLDevice = pCpu0->m_strID;
		m_strDestLDevice = pLd0->m_strID;
		EditCommCmdDatasetPath(pTestControl->m_pGuideBook);
	}

	Gb_SetGbModifiedFlag(pTestControl->m_pGuideBook, TRUE);
	pTestControl->SaveBinaryFile();
}

BOOL CTestControlManyReport::EditCommCmdDatasetPath(CDevice *pDevice)
{
	CCpus *pCpus = pDevice->GetCpus();
	CCpu  *pCpu  = (CCpu*)pCpus->FindByID(m_strDestLDevice);

	if (pCpu == NULL)
	{
		pCpu = (CCpu*)pCpus->FindByID(m_strSrcLDevice);

		if (pCpu == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE
				, _T("Device model error: logic device [%s] not exist!")
				, m_strSrcLDevice);
		}
		else
		{
			pCpu->m_strID = m_strDestLDevice;
			pCpu->m_strName = m_strDestLDevice;
		}		
	}

	EditCommCmdDatasetPath((CExBaseList*)pDevice);

	return TRUE;
}

void CTestControlManyReport::EditCommCmdDatasetPath(const CString &strSrcLDevice)
{
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	if (strSrcLDevice.GetLength() == 0)
	{
		m_strSrcLDevice = m_pGuideBook->m_strID;
	}
	else
	{
		m_strSrcLDevice = strSrcLDevice;
	}

	if (m_strSrcLDevice != m_pGuideBook->m_strID)
	{
		m_strDestLDevice = m_pGuideBook->m_strID;
		EditCommCmdDatasetPath(m_pGuideBook);
		Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);
		SaveBinaryFile();
	}

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		m_strDestLDevice = pTestControl->m_pGuideBook->m_strID;
		EditCommCmdDatasetPath(pTestControl->m_pGuideBook);
		Gb_SetGbModifiedFlag(pTestControl->m_pGuideBook, TRUE);
		pTestControl->SaveBinaryFile();
	}
}

	//设置装置引用的ID
void CTestControlManyReport::InitPpDevicesByTestTask(CTestTask *pTestTask)
{
	POS pos = m_oDeviceRefs.GetHeadPosition();
	CPpDeviceRef *p = NULL;
	long nIndex = 1;

	if (pos == NULL)
	{
		return;
	}

	p = (CPpDeviceRef *)m_oDeviceRefs.GetNext(pos);
	p->m_strID = pTestTask->m_strID;

	while (pos != NULL)
	{
		p = (CPpDeviceRef *)m_oDeviceRefs.GetNext(pos);
		p->m_strID.Format(_T("%s_%d"), pTestTask->m_strID, nIndex);
	}
}

void CTestControlManyReport::GetReportFiles(CDataGroup *pDataGroup)
{
	if (m_strCmbdDocFile.GetLength() > 0)
	{
		pDataGroup->AddNewData(XPARA_ID_DOCFILE, m_strCmbdDocFile);
	}
	else
	{
		CString strFile = GetGbBinaryFile();
		pDataGroup->AddNewData(XPARA_ID_GBRPTFILE, strFile);
		strFile = ChangeFilePostfix(strFile, g_strDocFilePostfix);
		pDataGroup->AddNewData(XPARA_ID_DOCFILE, strFile);
		strFile = ChangeFilePostfix(strFile, _T("xml"));
		pDataGroup->AddNewData(XPARA_ID_XMLRPTFILE, strFile);
	}
}
