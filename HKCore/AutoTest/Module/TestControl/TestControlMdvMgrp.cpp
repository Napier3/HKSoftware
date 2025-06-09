#include "stdafx.h"
#include "TestControlMdvMgrp.h"
#include "TestControlWnd.h"
#include "../TCtrlCntrWorkSpace.h"
#include "TCtrlCntrBaseApp.h"
#include "../GuideBook\Script/GbScript_GlobalDefine.h"
#include "..\..\..\Module\KeyDb\XMatchToolBase.h"
#include <math.h>

#include "../XRecorderDlg.h"
#include "..\..\..\Module\EpotoInterface\EpotoInterface.h"
#include "..\..\..\Module\DataMngr\DatasetValid\DsvViewResultDialog.h"

#include "../XLanguageResourceAts_AutoTest.h"
#include "../GuideBook\GuideBookTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CMdvMgrpSpoDeviceTestControl
CMdvMgrpSpoDeviceTestControl::CMdvMgrpSpoDeviceTestControl()
{
	
}


//2017-3-18  测试控制部分，全部设置为虚函数，便于多测试的控制
//单一项目
long CMdvMgrpSpoDeviceTestControl::TestSingle(CGbItemBase* pGbItem)
{
	// for debug
	//return CTestControlBase::TestSingle(pGbItem);

	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->TestSingle(pGbItem);
}

long CMdvMgrpSpoDeviceTestControl::TestSingle(long nItemIndex)
{
	// for debug
	//return CTestControlBase::TestSingle(nItemIndex);

	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->TestSingle(nItemIndex);
}

//某个项目到结束
long CMdvMgrpSpoDeviceTestControl::TestFrom(CGbItemBase* pGbItem)
{
	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->TestFrom(pGbItem);
}

long CMdvMgrpSpoDeviceTestControl::TestFrom(long nItemIndex)
{
	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->TestFrom(nItemIndex);
}

CMdvMgrpSpoDeviceTestControl::~CMdvMgrpSpoDeviceTestControl()
{

}

//项目执行完毕后的处理，有CTestControlManyReport统一处理
void CMdvMgrpSpoDeviceTestControl::ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem)
{
	//执行测试
	CTestControlManyReport::ExcuteCommCmdOnDelayAfterFinish(pItem);
	
	if (pItem->IsCmdExecModeForMgbrpt_MainRpt())
	{//多报告模式下，如果只有主报告执行，则执行主装置的函数
		CMdvMgrpSpoDeviceMngrTestControl *pParent = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
		pParent->ExcuteCommCmdOnDelayAfterFinish(pItem);

		return;
	}
	
	if (IsTailItem(pItem))
	{//如果是最后一个项目，则调用主管理对象，执行下一个Device的测试
		CMdvMgrpSpoDeviceMngrTestControl *pParent = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
		pParent->ExcuteCommCmdOnDelayAfterFinish(pItem);
	}
	else
	{
		return; //不是最后一个项目，则继续测试
	}
}

BOOL CMdvMgrpSpoDeviceTestControl::ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem)
{
	if (IsTailItem(pItem))
	{//如果是最后一个项目，则调用主管理对象，执行下一个Device的测试
		CMdvMgrpSpoDeviceMngrTestControl *pParent = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
		return pParent->ExcuteCommCmdOnDelayAfterFinish_Repeat(pItem);
	}
	else
	{
		return FALSE; //不是最后一个项目，则继续测试
	}
}

//通讯前延时、通讯后延时有CTestControlManyReport统一处理
long CMdvMgrpSpoDeviceTestControl::GetDelayBeforeCmd(CCommCmd* pItem)
{
	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->GetDelayBeforeCmd(pItem);
}

long CMdvMgrpSpoDeviceTestControl::GetDelayAfterCmd(CCommCmd* pItem)
{
	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->GetDelayAfterCmd(pItem);
}

void CMdvMgrpSpoDeviceTestControl::InitItemsRsltExprScript(CCommCmd* pItem)
{

}

BOOL CMdvMgrpSpoDeviceTestControl::AfterFinishTestItemSafety(CSafety *pSafety)
{
	CTestControlMngrBase::AfterFinishTestItemSafety(pSafety);

	if (IsTailItem(pSafety))
	{//如果是最后一个项目，则调用主管理对象，执行下一个Device的测试
		CMdvMgrpSpoDeviceMngrTestControl *pParent = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
		pParent->AfterFinishTestItemSafety(pSafety);
		return FALSE;
	}
	else
	{
		return FALSE; //不是最后一个项目，则继续测试
	}

	return FALSE;
}

long CMdvMgrpSpoDeviceTestControl::FinishTestItemSysParaEdit(CSysParaEdit* pItem)
{
	return FinishTestControlSysParaEdit(pItem);
}

BOOL CMdvMgrpSpoDeviceTestControl::NeedTestNextDevice()
{
	return TRUE;
}

BOOL CMdvMgrpSpoDeviceTestControl::ContinueTestByItemsRsltExprScript(CCommCmd* pItem)
{
// 	if (m_pItemsRsltExprScript != NULL)
// 	{
// 		if (pItem->GetRsltJdg() == 0)
// 		{
// 			if (m_nItemsRsltExprScriptIndex < m_nItemsRsltExprScriptMaxRead)
// 			{
// 				return TRUE;
// 			}
// 		}
// 	}
// 
// 	return FALSE;

	if (m_pItemsRsltExprScript != NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


void CMdvMgrpSpoDeviceTestControl::AfterUpdateMacroTestReport(CMacroTest* pItem, long nMacroTestTimes)
{
	CReport *pReportSrc = pItem->GetReport(-1);
	CopyReportToTestControl(this, pItem, pReportSrc, TRUE);
	CMacroTest *pCurr = (CMacroTest*)GetItem(m_pGuideBook, pItem);
	CReport *pReportCurr = pCurr->GetReport(-1);
	FillReport(pReportCurr, nMacroTestTimes);

	CTestControlManyReport::AfterUpdateMacroTestReport(pItem, nMacroTestTimes);
}

void CMdvMgrpSpoDeviceTestControl::AfterCreateMtFinalReport(CMacroTest* pItem, long nMacroTestTimes)
{
	CReport *pReportSrc = pItem->GetReport(-1);
	CopyReportToTestControl(this, pItem, pReportSrc, TRUE);
	CMacroTest *pCurr = (CMacroTest*)GetItem(m_pGuideBook, pItem);
	CReport *pReportCurr = pCurr->GetReport(-1);
	FillReport(pReportCurr, nMacroTestTimes);

	CTestControlManyReport::AfterUpdateMacroTestReport(pItem, nMacroTestTimes);
}

void CMdvMgrpSpoDeviceTestControl::EditItemPara(CCommCmd *pCommCmd, CValue *pValue)
{
	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->EditItemPara(pCommCmd, pValue);
}

CReport* CMdvMgrpSpoDeviceTestControl::AddReport(CGbItemBase* pItem, long nRepeatTimes, long nTestIndex)
{
	return pItem->GetReport(-1);
}


BOOL CMdvMgrpSpoDeviceTestControl::ItemsRsltExprScriptTimeIgnore()
{
	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->ItemsRsltExprScriptTimeIgnore();
}


void CMdvMgrpSpoDeviceTestControl::SetTestItemSelectedState(CGbItemBase *pItem,long nSelect)
{
	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->SetTestItemSelectedState(pItem, nSelect);
}

BOOL CMdvMgrpSpoDeviceTestControl::GBS_CanBreakLoop(CGbItemBase *pItem)
{
	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->GBS_CanBreakLoop(pItem);
}


void CMdvMgrpSpoDeviceTestControl::GBS_ClearBreakLoopState(CGbItemBase *pItem)
{
	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->GBS_ClearBreakLoopState(pItem);
}


long CMdvMgrpSpoDeviceTestControl::GBS_RcdCmp_CopyStdFile(CTestControl *pTestControl, CString &strStdSrcFile, CString &strStdDestFile)
{
	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->GBS_RcdCmp_CopyStdFile(pTestControl, strStdSrcFile, strStdDestFile);
}

void CMdvMgrpSpoDeviceTestControl::EditItemPara(CMacroTest *pMacroTest, CShortData  *pData)
{
	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->EditItemPara(pMacroTest, pData);
}

long CMdvMgrpSpoDeviceTestControl::CopyChildDeviceTestControlReport(CMacroTest* pItem, CReport *pReportSrc)
{
	//MainTestControl
	CopyReportToTestControl(this, pItem, pReportSrc, FALSE);

	//ChildTestControls
	CopyChildrenTestControlReport(pItem, pReportSrc);

	return 0;
}

void CMdvMgrpSpoDeviceTestControl::TestMainItem(CGbItemBase *pItem)
{
	CGbItemBase *pMainItem = (CGbItemBase*)GetItem(m_pGuideBook, pItem);
	TestItem(pMainItem);
}

void CMdvMgrpSpoDeviceTestControl::InitTestItem(CGbItemBase *pCurrItem, CGbItemBase *pSubItem)
{
	m_pCurrTestItem = (CGbItemBase*)GetItem(m_pGuideBook, pCurrItem);
	m_pCurrSubTestItem = (CGbItemBase*)GetItem(m_pGuideBook, pSubItem);

	POS pos = GetHeadPosition();
	CTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControl *)GetNext(pos);
		p->m_pCurrTestItem = (CGbItemBase*)GetItem(p->m_pGuideBook, pCurrItem);
		p->m_pCurrSubTestItem = (CGbItemBase*)GetItem(p->m_pGuideBook, pSubItem);
	}
}

/*电气量测试输出控制
long CTestControl::TestItemMacroTest(CMacroTest* pItem)
{
	//2019-4-28  李俊庆
	//2019-4-28：多装置模式下，主装置TestControl执行测试流程，子装置没有执行测试流程，所以m_pCurrTestItem==NULL
	if (m_pCurrTestItem == NULL)
	{
		m_pCurrTestItem = pItem;
	}
*/
long CMdvMgrpSpoDeviceTestControl::FinishTestItemMacroTest_Process(CMacroTest* pItem) //2019-4-27 MdvTestEach
{
	m_pCurrTestItem = NULL;   //对应上面 = NULL    

	if (pItem->IsMdvTestEach())
	{
		return CTestControlManyReport::FinishTestItemMacroTest_Process(pItem);
	}
	else
	{
		CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
		return pMainDevice->FinishTestItemMacroTest_Process(pItem);
	}
}

long CMdvMgrpSpoDeviceTestControl::StopTestExtern(const CString &strMsg, BOOL bExtern)
{
	CMdvMgrpSpoDeviceMngrTestControl *pMainDevice = (CMdvMgrpSpoDeviceMngrTestControl*)GetParent();
	return pMainDevice->StopTestExtern(strMsg, bExtern);
}

//////////////////////////////////////////////////////////////////////////
//CMdvMgrpSpoDeviceMngrTestControl
CMdvMgrpSpoDeviceMngrTestControl::CMdvMgrpSpoDeviceMngrTestControl()
{
	
}

CMdvMgrpSpoDeviceMngrTestControl::~CMdvMgrpSpoDeviceMngrTestControl()
{
	
}

CTestTasks* CMdvMgrpSpoDeviceMngrTestControl::GetTestTasks()
{
	return &m_oTestTasks;
}

long CMdvMgrpSpoDeviceMngrTestControl::FinishTestItemSysParaEdit(CSysParaEdit* pItem)
{
	FinishTestItemSysParaEdit_ProcessReport(pItem);

	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		FinishTestControlSysParaEdit(pTestControl, pItem);
	}

	pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CMdvMgrpSpoDeviceTestControl *pMdvMgrpSpoDeviceTestControl = NULL;

	while (pos != NULL)
	{
		pMdvMgrpSpoDeviceTestControl = (CMdvMgrpSpoDeviceTestControl *)m_listMdvMgrpTestControl.GetNext(pos);
		pMdvMgrpSpoDeviceTestControl->FinishTestItemSysParaEdit(pItem);
	}

	//保存到
	AddSysParasToTask(pItem);

	TestNextItem();

	return 0;
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::AfterFinishTestItemSafety_OneTime(CSafety *pSafety)
{
	CTestControlMngrBase::AfterFinishTestItemSafety_OneTime(pSafety);

	CMdvMgrpSpoDeviceTestControl *pTestControl = NULL;
	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		pTestControl = (CMdvMgrpSpoDeviceTestControl *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->AfterFinishTestItemSafety_OneTimeEx(pSafety);
	}

	return TRUE;
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::AfterFinishTestItemSafety(CSafety *pSafety)
{
	CTestControl *pTestControl = (CTestControl*)GetTestControl(pSafety);

	//处理单一测试模式
	if (pSafety->IsManyDeviceTestMode_OneTime())
	{
		ASSERT (pTestControl == this);
		AfterFinishTestItemSafety_OneTime(pSafety);
		return TRUE;
	}

	//其当前Control，则执行当前多组报告的处理
	if (TestOwn(pSafety))
	{
		return FALSE;
	}

	//其他装置传过来的调用处理
	if (IsMdvMgrpTailItem(pSafety))
	{//最后一个装置的测试：根据ItemExprScript判断，是否需要继续测试
		
	}
	else//不是最后一个装置的测试
	{
		//CMdvMgrpSpoDeviceTestControl:装置的最后一个项目
		if (tctrl_IsTailTestControlItem(pSafety))
		{
			//获取下一个CMdvMgrpSpoDeviceTestControl，进行测试
			CMdvMgrpSpoDeviceTestControl *pNextDevice = GetNextDevice(pSafety);

			if (pNextDevice != NULL)
			{
				pNextDevice->TestMainItem(pSafety);
				return FALSE;
			}
		}
		else
		{
			//继续当前CMdvMgrpSpoDeviceTestControl项目进行测试
			CMdvMgrpSpoDeviceTestControl *pCurrDevice = GetCurrDevice(pSafety);
			pCurrDevice->CTestControlManyReport::AfterFinishTestItemSafety(pSafety);
			return FALSE;
		}
	}

	//下一个项目的测试
	m_pTCtrlWnd->m_pTestControl = this;
	CGbItemBase *pMainItem = (CGbItemBase*)GetItem(m_pGuideBook, pSafety);

	//处理GotoItemEx  2017-11-23
	ProcessGotoItemEx();

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

	return FALSE;
}


BOOL CMdvMgrpSpoDeviceMngrTestControl::NeedTestNextDevice()
{
	return TRUE;
}


void CMdvMgrpSpoDeviceMngrTestControl::ClearSysRptFill(CGbItemBase *pItem)
{
	CTestControlMngrBase::ClearSysRptFill(pItem);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		p->ClearSysRptFill(pItem);
	}
}


void CMdvMgrpSpoDeviceMngrTestControl::ClearTestSubItem(BOOL bClearMain)
{
	CTestControlMngrBase::ClearTestSubItem(bClearMain);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		p->ClearTestSubItem(TRUE);
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::EditItemPara(CCommCmd *pCommCmd, CValue *pValue)
{
	CTestControlMngrBase::EditItemPara(pCommCmd, pValue);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		p->CTestControlMngrBase::EditItemPara(pCommCmd, pValue);
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::EditItemPara(CMacroTest *pMacroTest, CShortData  *pData)
{
	CTestControlMngrBase::EditItemPara(pMacroTest, pData);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		p->CTestControlMngrBase::EditItemPara(pMacroTest, pData);
	}
}


long CMdvMgrpSpoDeviceMngrTestControl::SelectAllTestControl(CExBaseList &listTestControl, BOOL bMainFirst)
{
	CTestControlMngrBase::SelectAllTestControl(listTestControl, bMainFirst);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		p->CTestControlMngrBase::SelectAllTestControl(listTestControl, bMainFirst);
	}

	return listTestControl.GetCount();
}

void CMdvMgrpSpoDeviceMngrTestControl::SetTestEndTime()
{
	CTestControlMngrBase::SetTestEndTime();

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		p->SetTestTime(m_pGuideBook->GetTestBeginTime(), m_pGuideBook->GetTestEndTime());
	}
}


CReport* CMdvMgrpSpoDeviceMngrTestControl::AddReport(CGbItemBase* pItem, long nRepeatTimes, long nTestIndex)
{
// 	if (pItem->GetClassID() != GBCLASSID_MACROTEST)
// 	{
// 		return CTestControl::AddReport(pItem, nRepeatTimes, nTestIndex);
// 	}

	CReport *pReport = CTestControlManyReport::AddReport(pItem, nRepeatTimes, nTestIndex);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		p->CTestControlMngrBase::AddReport(pItem, nRepeatTimes, nTestIndex);
	}

	return pReport;
}


BOOL CMdvMgrpSpoDeviceMngrTestControl::ItemsRsltExprScriptTimeIgnore()
{
	return CTestControl::ItemsRsltExprScriptTimeIgnore();
}


long CMdvMgrpSpoDeviceMngrTestControl::FillParentItemsReport(CGbItemBase *pItems)
{
	if (!Gb_IsItemsTestFinished(pItems))
	{
		return 0;
	}

	CTestControlMngrBase::FillParentItemsReport(pItems);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CMdvMgrpSpoDeviceTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CMdvMgrpSpoDeviceTestControl *)m_listMdvMgrpTestControl.GetNext(pos);
		p->CTestControlMngrBase::FillParentItemsReport(pItems);
	}

	return 0;
}

void CMdvMgrpSpoDeviceMngrTestControl::SetTestItemSelectedState(CGbItemBase *pItem,long nSelect)
{
	CTestControlMngrBase::SetTestItemSelectedState(pItem, nSelect);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CMdvMgrpSpoDeviceTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CMdvMgrpSpoDeviceTestControl *)m_listMdvMgrpTestControl.GetNext(pos);
		p->CTestControlMngrBase::SetTestItemSelectedState(pItem, nSelect);
	}
}

long CMdvMgrpSpoDeviceMngrTestControl::CopyChildDeviceTestControlReport(CMacroTest* pItem, CReport *pReportSrc)
{
	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CMdvMgrpSpoDeviceTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CMdvMgrpSpoDeviceTestControl *)m_listMdvMgrpTestControl.GetNext(pos);
		p->m_nMacroTestTimes = m_nMacroTestTimes;
		p->CopyChildDeviceTestControlReport(pItem, pReportSrc);
	}

	return 0;
}

void CMdvMgrpSpoDeviceMngrTestControl::CombineTestParaDatas(CString &strDestParaDatas, const CString &strSrcDatas, const CString &strParaID)
{
	CString strParaBegin;
	strParaBegin.Format(_T("%s="), strParaID);
	long nPos = strDestParaDatas.Find(strParaBegin);
	long nPos2 = strSrcDatas.Find(strParaBegin);
	long nPosEnd2 = 0, nPosEnd = 0, nCount=0;
	CString strData, strData2;

	if (nPos2 < 0 || nPos < 0)
	{
		return;
	}

	nPosEnd2 = strSrcDatas.Find(';', nPos2);
	ASSERT (nPosEnd2 > 0);
	nPos2 += strParaBegin.GetLength();
	strData2 = strSrcDatas.Mid(nPos2, nPosEnd2 - nPos2); //获取“***=”后面的数据

	nPosEnd = strDestParaDatas.Find(';', nPos);
	ASSERT (nPosEnd > 0);
	nCount = nPosEnd - nPos;
	strData = strDestParaDatas.Mid(nPos, nCount); //获取“***=##”格式的数据，不包括“;”
	strDestParaDatas.Delete(nPos, nCount+1);//删除“***=##;”格式的数据

	//去掉引号，完成参数拼接
	strData = strData.Left(strData.GetLength() - 1);
	strData2 = strData2.Mid(1);
	strDestParaDatas.AppendFormat(_T("%s%s;"), strData, strData2);
}

void CMdvMgrpSpoDeviceMngrTestControl::CombineTestParaDatas(CString &strDestParaDatas, const CString &strSrcDatas)
{
	CombineTestParaDatas(strDestParaDatas, strSrcDatas, g_strBinaryParaID_Boutputs);
}

void CMdvMgrpSpoDeviceMngrTestControl::GetMacroTestParaDatas(CMacroTestPara* pTestPara, CString &strParaDatas)
{
	if (!m_bUseBinaryOffset)
	{
		return CTestControl::GetMacroTestParaDatas(pTestPara, strParaDatas);
	}

	CTestControl::GetMacroTestParaDatas(pTestPara, strParaDatas);
	
	if (!CGuideBookTool::HasBinaryTestParas(strParaDatas))
	{
		return;
	}

	CString strParaTemp;
	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CMacroTest *pMacroTest = (CMacroTest*)pTestPara->GetParent();
	CMacroTest *pFind = NULL;
	CMacroTestPara *pTestPara2 = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)m_listMdvMgrpTestControl.GetNext(pos);
		pFind = (CMacroTest*)GetItem(pTestControl->m_pGuideBook, pMacroTest);
		pTestPara2 = pFind->GetMacroTestPara();
		pTestControl->GetMacroTestParaDatas(pTestPara2, strParaTemp);
		CGuideBookTool::CombineTestParaDatas(strParaDatas, strParaTemp);
	}
}

long CMdvMgrpSpoDeviceMngrTestControl::UpdateStateAfterFinishTestItem_MdvEach(CGbItemBase* pItem)
{
	CTestControl *pTestControl = (CTestControl*)tctrl_GetTestControl(pItem);

	long nRet = pTestControl->CTestControl::UpdateStateAfterFinishTestItem(pItem);

	//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
	//因此单独执行
	pTestControl->CTestControl::WriteItemTempFile(pItem);

	return nRet;
}

long CMdvMgrpSpoDeviceMngrTestControl::UpdateStateAfterFinishTestItem(CGbItemBase* pItem, BOOL bNeedFireMsg)
{
	if (pItem->IsMdvTestEach())
	{
		return UpdateStateAfterFinishTestItem_MdvEach(pItem);
	}
	
	else
	{
		long nRet = CTestControl::UpdateStateAfterFinishTestItem(pItem, bNeedFireMsg);

		return nRet;
	}	
}

//获得项目对应的TestControl，
long CMdvMgrpSpoDeviceMngrTestControl::TestItemMacroTest_MdvEach(CMacroTest* pItem)
{
	CTestControl *pTestControl = (CTestControl*)tctrl_GetTestControl(pItem);

	return pTestControl->CTestControl::TestItemMacroTest(pItem);
}

long CMdvMgrpSpoDeviceMngrTestControl::TestItemMacroTest(CMacroTest* pItem)
{
	if (pItem->IsMdvTestEach())
	{
		return TestItemMacroTest_MdvEach(pItem);
	}

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

	CopyChildDeviceTestControlReport(pItem, pReportSrc);

	//测试子项目
	TestFirstSubItems();

	return 0;
}


CReport* CMdvMgrpSpoDeviceMngrTestControl::UpdateMacroTestReport(CMacroTest* pItem)
{
	//主TestControl，为pItem创建报告，从测试仪接口程序获取数据，为子TestControl添加报告
	CReport *pReport = CTestControlManyReport::UpdateMacroTestReport(pItem);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CMdvMgrpSpoDeviceTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CMdvMgrpSpoDeviceTestControl *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->CTestControlMngrBase::UpdateMacroTestReport(pTestControl->m_pGuideBook, pItem, pReport);
	}

	return pReport;
}


void CMdvMgrpSpoDeviceMngrTestControl::AfterUpdateMacroTestReport(CMacroTest* pItem, long nMacroTestTimes)
{
	CTestControlMngrBase::AfterUpdateMacroTestReport(pItem, nMacroTestTimes);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CMdvMgrpSpoDeviceTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CMdvMgrpSpoDeviceTestControl *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->AfterUpdateMacroTestReport(pItem, nMacroTestTimes);
	}

	//2018-12-24  李俊庆
	//对于一个开关量测试仪对应多台装置的测试，开出传动测试，需要对开入节点进行切分提取
	//最后切分提取主装置的部分
	if (m_bUseBinaryOffset)
	{
		CReport *pReport = (CReport*)pItem->GetReport(-1);
		CGuideBookTool::ExtractBinputsResult(pReport->m_pValues, m_nBinRngBegin, m_nBinRngEnd, m_pGuideBook->m_nBinOffset);
		CString strSyntax;
		pItem->RunResultScript(strSyntax);
		FillReport(pReport, m_nMacroTestTimes);
	}

}

void CMdvMgrpSpoDeviceMngrTestControl::AfterCreateMtFinalReport(CMacroTest* pItem, long nMacroTestTimes)
{
	CTestControlMngrBase::AfterCreateMtFinalReport(pItem, nMacroTestTimes);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CMdvMgrpSpoDeviceTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CMdvMgrpSpoDeviceTestControl *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->AfterCreateMtFinalReport(pItem, nMacroTestTimes);
	}
}

// long CMdvMgrpSpoDeviceMngrTestControl::FinishTestItemMacroTest_Only(CMacroTest* pItem)
// {
// 	FinishTestItemMacroTest_Report(pItem);
// 
// 	return CTestControl::FinishTestItemMacroTest_Process(pItem);
// }

void CMdvMgrpSpoDeviceMngrTestControl::InitGuideBook()
{
	m_pItemContainer = (CItemContainer*)m_pGuideBook->GetItemContainer();
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pTestControl->m_pGuideBook->InitGuideBook();
		m_pItemContainer->AddMdvGuideBook(pTestControl->m_pGuideBook);
	}

	CMdvMgrpSpoDeviceTestControl *pSubDv = NULL;
	POS posDv = m_listMdvMgrpTestControl.GetHeadPosition();

	while (posDv != NULL)
	{
		pSubDv = (CMdvMgrpSpoDeviceTestControl *)m_listMdvMgrpTestControl.GetNext(posDv);
		pSubDv->m_pGuideBook->InitGuideBook();
		m_pItemContainer->AddMdvGuideBook(pSubDv->m_pGuideBook);
		pos = pSubDv->GetHeadPosition();

		while (pos != NULL)
		{
			pTestControl = (CTestControl *)pSubDv->GetNext(pos);
			pTestControl->m_pGuideBook->InitGuideBook();
			m_pItemContainer->AddMdvGuideBook(pTestControl->m_pGuideBook);
		}
	}

	m_pItemContainer->SetGuideBook(m_pGuideBook);
}

long CMdvMgrpSpoDeviceMngrTestControl::FindTestControlIndex(CTestControl *pTestControl)
{
	return m_listMdvMgrpTestControl.FindIndex(pTestControl);
}

void CMdvMgrpSpoDeviceMngrTestControl::SetTestItemState(CGbItemBase* pItem, UINT nState)
{
	CTestControlManyReport::SetTestItemState(pItem, nState);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		p->SetTestItemState(pItem, nState);
	}
}

//////////////////////////////////////////////////////////////////////////
//通讯命令处理
void CMdvMgrpSpoDeviceMngrTestControl::AttachTestControlWnd(CTestControlWnd *pWndRef)
{
	CTestControlMngrBase::AttachTestControlWnd(pWndRef);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		p->AttachTestControlWnd(pWndRef);
	}
}


long CMdvMgrpSpoDeviceMngrTestControl::CreatemUICommCmdViewDlg(LPVOID pUIViewDlg)
{
	CUICommCmdViewDlg *pUICommCmdViewDlg = (CUICommCmdViewDlg*)pUIViewDlg;

	CTestControlMngrBase::CreatemUICommCmdViewDlg(NULL);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		p->CreatemUICommCmdViewDlg(m_pUICommCmdViewDlg);
	}

	return 0;
}


void CMdvMgrpSpoDeviceMngrTestControl::InitItemsRsltExprScript(CCommCmd* pItem)
{
	CTestControlMngrBase::InitItemsRsltExprScript(pItem);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *pTestControl = NULL;
	CCommCmd *pMainItem = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		pMainItem = (CCommCmd*)GetItem(pTestControl->m_pGuideBook, pItem);
		pTestControl->CTestControlMngrBase::InitItemsRsltExprScript(pMainItem);
	}
}

long CMdvMgrpSpoDeviceMngrTestControl::GetDelayBeforeCmd(CCommCmd* pItem)
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

long CMdvMgrpSpoDeviceMngrTestControl::GetDelayAfterCmd(CCommCmd* pItem)
{
	if (m_listMdvMgrpTestControl.GetCount() == 0)
	{
		if (GetCount() == 0)
		{
			CCmd *pCmd = pItem->GetCmd();
			return pCmd->GetDelayAfterCmd();
		}
		else
		{
			CTestControl *pTestControl = GetTestControl(pItem);

			//2019-3-19
			if (pItem->IsCmdExecModeForMgbrpt_MainRpt())
			{
				CCmd *pCmd = pItem->GetCmd();
				return pCmd->GetDelayAfterCmd();
			}
			else
			{
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
		}
	}
	else
	{
		CTestControlMngrBase *pMngr = tctrl_GetTestControlMngr(pItem);

		//2019-3-19
		if (pMngr == m_listMdvMgrpTestControl.GetTail())
		{
			if (pItem->IsCmdExecModeForMgbrpt_MainRpt())
			{
				CCmd *pCmd = pItem->GetCmd();
				return pCmd->GetDelayAfterCmd();
			}
			else
			{
				if (pMngr->IsTailItem(pItem))
				{
					CCmd *pCmd = pItem->GetCmd();
					return pCmd->GetDelayAfterCmd();
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			return 0;
		}
	}

}

long CMdvMgrpSpoDeviceMngrTestControl::StopTestExtern(const CString &strMsg, BOOL bExtern)
{
	CTestControlMngrBase::StopTestExtern(strMsg, bExtern);

	CTestControlMngrBase *p = NULL;
	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		p->CTestControlMngrBase::StopTestExtern(strMsg, bExtern);
	}

	return 0;
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::TestOwn(CCommCmd* pItem)
{
	CTestControl *pTestControl = (CTestControl*)GetTestControl(pItem);

	//其当前Control，则执行当前多组报告的处理
	if (pTestControl == this)
	{
		CTestControlManyReport::ExcuteCommCmdOnDelayAfterFinish(pItem);

		if (pItem->IsCmdExecModeForMgbrpt_MainRpt())
		{//多报告模式下，如果是主报告执行模式，则不执行子报告的测试
			return FALSE;
		}

		if (!IsTailItem(pItem))
		{
			//继续测试其他的组别
			return TRUE;
		}
	}
	else
	{
		//排除CMdvMgrpSpoDeviceTestControl对象，因为CMdvMgrpSpoDeviceTestControl的父对象为this
		//此种方式，子对象CMdvMgrpSpoDeviceTestControl只有一份报告
		if (pTestControl->IsTestControlMngr())
		{
			return FALSE;
		}

		//还是当前装置的测试
		if (pTestControl->GetParent() == this)
		{
			if (pItem->IsReadSoe())
			{//如果是读SOE，则有主报告数据对象进行处理
				return FALSE;
			}

			CTestControlManyReport::ExcuteCommCmdOnDelayAfterFinish(pItem);

			if (!IsTailItem(pItem))
			{
				//继续测试其他的组别
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::TestOwn(CSafety* pItem)
{
	CTestControl *pTestControl = (CTestControl*)GetTestControl(pItem);

	//其当前Control，则执行当前多组报告的处理
	if (pTestControl == this)
	{
		CTestControlManyReport::AfterFinishTestItemSafety(pItem);

		if (!IsTailItem(pItem))
		{
			//继续测试其他的组别
			return TRUE;
		}
	}
	else
	{
		//排除CMdvMgrpSpoDeviceTestControl对象，因为CMdvMgrpSpoDeviceTestControl的父对象为this
		//此种方式，子对象CMdvMgrpSpoDeviceTestControl只有一份报告
		if (pTestControl->IsTestControlMngr())
		{
			return FALSE;
		}

		//还是当前装置的测试
		if (pTestControl->GetParent() == this)
		{
			CTestControlManyReport::AfterFinishTestItemSafety(pItem);

			if (!IsTailItem(pItem))
			{
				//继续测试其他的组别
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::IsMdvMgrpTailItem(CExBaseObject *pItem)
{
	CTestControl *pTestControl = (CTestControl*)GetTestControl(pItem);

	//最后一个装置的测试对象
	CTestControlManyReport *pTail = (CTestControlManyReport*)m_listMdvMgrpTestControl.GetTail();

	if (pTail == NULL)
	{
		return TRUE;
	}

	return pTail->GetTail() == pTestControl;
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::ContinueTestByItemsExpr(CCommCmd* pItem)
{
// 	CTestControl *pTestControl = (CTestControl*)GetTestControl(pItem);
// 
// 	CTestControlManyReport *pTail = (CTestControlManyReport*)m_listMdvMgrpTestControl.GetTail();

	//最后一个装置的测试
	//if (pTail->GetTail() == pTestControl)

	if (m_pItemsRsltExprScript != NULL)
	{
		CCommCmd* pMainItem =  (CCommCmd*)GetItem(m_pGuideBook, pItem);

		if (!IsAllItemQualified(pMainItem))
		{
			//如果还有不合格的项目，则继续测试
			//？？？？？？？？？：获取下一个不合格的报告进行测试？

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
	}

	return FALSE;
}

CMdvMgrpSpoDeviceTestControl* CMdvMgrpSpoDeviceMngrTestControl::GetNextDevice(CExBaseObject *pItem)
{
	CTestControlMngrBase *pMngr = tctrl_GetTestControlMngr(pItem);
	//CTestControl *pTestControl = (CTestControl*)GetTestControl(pItem);
	//CMdvMgrpSpoDeviceTestControl *pMain = (CMdvMgrpSpoDeviceTestControl*)pTestControl->GetParent();
	POS pos = m_listMdvMgrpTestControl.Find(pMngr);

	if (pos == NULL)
	{
		pos = m_listMdvMgrpTestControl.GetHeadPosition();
	}
	else
	{
		m_listMdvMgrpTestControl.GetNext(pos);
		//ASSERT (pos != NULL);
	}

	if (pos == NULL)
	{
		return NULL;
	}
	else
	{
		return (CMdvMgrpSpoDeviceTestControl*)m_listMdvMgrpTestControl.GetAt(pos);
	}
}

CMdvMgrpSpoDeviceTestControl* CMdvMgrpSpoDeviceMngrTestControl::GetCurrDevice(CExBaseObject *pItem)
{
	CMdvMgrpSpoDeviceTestControl *pMngr = (CMdvMgrpSpoDeviceTestControl*)tctrl_GetTestControlMngr(pItem);

	return pMngr;
}

void CMdvMgrpSpoDeviceMngrTestControl::SetCommCmdRepeatTimes(long nTimes)
{
	CTestControlManyReport::SetCommCmdRepeatTimes(m_nCommCmdTestTimes);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CMdvMgrpSpoDeviceTestControl *p = NULL;

	while (pos != NULL)
	{
		p = (CMdvMgrpSpoDeviceTestControl *)m_listMdvMgrpTestControl.GetNext(pos);
		p->SetCommCmdRepeatTimes(nTimes);
	}
}


BOOL CMdvMgrpSpoDeviceMngrTestControl::GBS_CanBreakLoop(CGbItemBase *pItem)
{
	BOOL bAllBreakLoop = CTestControlMngrBase::GBS_CanBreakLoop(pItem);

	if (!bAllBreakLoop)
	{
		return bAllBreakLoop;
	}

	//从设备
	POS posMngr = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *pMngr = NULL;

	while (posMngr != NULL)
	{
		pMngr = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(posMngr);

		//从设备报告
		if (!pMngr->CTestControlMngrBase::GBS_CanBreakLoop(pItem))
		{
			bAllBreakLoop = FALSE;
			break;
		}
	}

	return bAllBreakLoop;
}


void CMdvMgrpSpoDeviceMngrTestControl::GBS_ClearBreakLoopState(CGbItemBase *pItem)
{
	CTestControlMngrBase::GBS_ClearBreakLoopState(pItem);

	//从设备
	POS posMngr = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *pMngr = NULL;

	while (posMngr != NULL)
	{
		pMngr = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(posMngr);

		//从设备报告
		pMngr->CTestControlMngrBase::GBS_ClearBreakLoopState(pItem);
	}
}

long CMdvMgrpSpoDeviceMngrTestControl::GBS_RcdCmp_CopyStdFile(CTestControl *pTestControl, CString &strStdSrcFile, CString &strStdDestFile)
{
	if (pTestControl == this)
	{
		m_strStdDestFile = GetPathFileNameFromFilePathName(strStdDestFile);
	}
	else
	{
		strStdDestFile = GetPathFromFilePathName(strStdDestFile);
		strStdDestFile += m_strStdDestFile;
	}

	CTestControl::GBS_RcdCmp_CopyStdFile(pTestControl, strStdSrcFile, strStdDestFile);

	return 0;
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem)
{
// 	if (CTestControl::ExcuteCommCmdOnDelayAfterFinish_Repeat(pItem))
// 	{
// 		return TRUE;
// 	}

	return FALSE;
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::ExcuteCommCmdOnDelayAfterFinish_RepeatEx(CCommCmd* pItem)
{
	//处理BreakLoop
// 	ProcessBreakLoopByAllRpt();

	if (CTestControl::ExcuteCommCmdOnDelayAfterFinish_Repeat(pItem))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::TestNextDeviceMainItem(CCommCmd* pItem)
{
	//获取下一个CMdvMgrpSpoDeviceTestControl，进行测试
	CMdvMgrpSpoDeviceTestControl *pNextDevice = GetNextDevice(pItem);

	if (pNextDevice != NULL)
	{
		pNextDevice->InitTestItem(m_pCurrTestItem, m_pCurrSubTestItem);
		pNextDevice->TestMainItem(pItem);
		return TRUE;
	}

	return FALSE;
}

void CMdvMgrpSpoDeviceMngrTestControl::ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem)
{
	//如果是读SOE/Reset
	if (pItem->IsReadSoe() || pItem->IsReset())
	{
		g_theTCtrlCntrApp->StopProtocolParseForReadSoe(TRUE);
	}

	CTestControl *pTestControl = (CTestControl*)GetTestControl(pItem);

	if (TestOwn(pItem))
	{	//其当前Control，则执行当前多组报告的处理
		return;
	}

	//其他装置传过来的调用处理
	if (IsMdvMgrpTailItem(pItem))
	{//最后一个装置的测试：根据ItemExprScript判断，是否需要继续测试
		if (ContinueTestByItemsExpr(pItem))
		{
			return;
		}
	}
	else//不是最后一个装置的测试
	{
		if (pItem->IsCmdExecModeForMgbrpt_MainRpt())
		{
			if (TestNextDeviceMainItem(pItem))
			{
				return;
			}
		}
		else
		{
			//CMdvMgrpSpoDeviceTestControl:装置的最后一个项目
			if (tctrl_IsTailTestControlItem(pItem) || pItem->IsReadSoe())
			{
				//获取下一个CMdvMgrpSpoDeviceTestControl，进行测试
				if (TestNextDeviceMainItem(pItem))
				{
					return;
				}
			}
			else
			{
				//继续当前CMdvMgrpSpoDeviceTestControl项目进行测试
				CMdvMgrpSpoDeviceTestControl *pCurrDevice = GetCurrDevice(pItem);
				pCurrDevice->CTestControlManyReport::ExcuteCommCmdOnDelayAfterFinish(pItem);
				return;
			}

		}
	}

	//如果是读SOE/Reset
	if (pItem->IsReadSoe() || pItem->IsReset())
	{
		g_theTCtrlCntrApp->StopProtocolParseForReadSoe(FALSE);
	}

	CGbItemBase *pMainItem = (CGbItemBase*)GetItem(m_pGuideBook, pItem);
	m_pTCtrlWnd->m_pTestControl = this;

	//处理重复测试  2017-11-19  lijq
	if (ExcuteCommCmdOnDelayAfterFinish_RepeatEx((CCommCmd*)pMainItem))
	{
		SetCommCmdRepeatTimes(m_nCommCmdTestTimes);
		return;
	}

	//处理GotoItemEx  2017-11-23
	ProcessGotoItemEx();

	//处理GotoItemEx  2017-11-23
// 	ProcessBreakLoopByAllRpt();

	//下一个项目的测试
	if (pMainItem->m_bIsSubItem)
	{
		if (m_pCurrSubTestItem == NULL)
		{
			ClearTestSubItem(TRUE);
			TestNextItem();
		}
		else
		{
			if (!HasNextSubItem(pMainItem))
			{
				ClearTestSubItem(FALSE);
			}
			//else  此处不能注释，当没有下一个子项目时，需要结束父项目
			{
				TestNextSubItem(pMainItem);
			}
		}
	}
	else
	{
		ClearTestSubItem(TRUE);
		TestNextItem();
	}
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::IsAllItemQualified(CCommCmd* pItem)
{
	if (!CTestControlManyReport::IsAllItemQualified(pItem))
	{
		return FALSE;
	}

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlManyReport *pTestCtrol = NULL;

	while (pos != NULL)
	{
		pTestCtrol = (CTestControlManyReport *)m_listMdvMgrpTestControl.GetNext(pos);

		if (!pTestCtrol->IsAllItemQualified(pItem))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::ContinueTestByItemsRsltExprScript(CCommCmd* pItem)
{
	DWORD dwItemsRsltExprScriptIndex = m_nItemsRsltExprScriptIndex;
	BOOL bRet = FALSE;

	if (m_pItemsRsltExprScript != NULL)
	{
		if (!IsAllItemQualified(pItem))
		{
			m_nItemsRsltExprScriptIndex++;

			if (m_nItemsRsltExprScriptIndex < m_nItemsRsltExprScriptMaxRead)
			{
				bRet = TRUE;
			}
		}
	}

	SetItemsRsltExprScriptIndex(m_nItemsRsltExprScriptIndex, dwItemsRsltExprScriptIndex);
	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);
		p->SetItemsRsltExprScriptIndex(m_nItemsRsltExprScriptIndex, dwItemsRsltExprScriptIndex);
	}

	return bRet;
}

//////////////////////////////////////////////////////////////////////////
//
void CMdvMgrpSpoDeviceMngrTestControl::CreateAllFilesByTasks(CTestTasks *pSrcTasks)
{
	CString strReportFile;

	//兼容从主界面程序打开没有创建报告的情况  2017-7-2
	if (pSrcTasks != &m_oTestTasks)
	{
		m_oTestTasks.m_strTestType = pSrcTasks->m_strTestType;
		m_oTestTasks.m_strName = pSrcTasks->m_strName;
		m_oTestTasks.m_strID = pSrcTasks->m_strID;
		m_oTestTasks.tsk_SetGbxmlFile(pSrcTasks->tsk_GetGbxmlFile());
		m_oTestTasks.m_strEngineMode = pSrcTasks->m_strEngineMode;  //shaolei 2023-11-2
		m_oTestTasks.m_strPpEngineProgID = pSrcTasks->m_strPpEngineProgID;
		m_oTestTasks.m_strTasksParentPath = pSrcTasks->m_strTasksParentPath;
		m_oTestTasks.m_strTasksFile = pSrcTasks->m_strTasksFile;
		m_oTestTasks.m_strTasksPath = pSrcTasks->m_strTasksPath;
		m_oTestTasks.DeleteAll();
		m_oTestTasks.AppendEx(*pSrcTasks);
		m_oTestTasks.InitAfterRead();
		pSrcTasks->RemoveAll();
		m_oTestTasks.m_dwAtsRptType = pSrcTasks->m_dwAtsRptType;
	}

	if (m_oTestTasks.HasAllProjectCreated())
	{
		return;
	}

	CGuideBook *pGuideBook = new CGuideBook();
	long nRet = pGuideBook->OpenXMLFile(m_oTestTasks.tsk_GetGbxmlFile());
	//CAtsNewTestTool::InitGuideBookAttrs(pGuideBook);  //2021-10-1  lijunqing
	pGuideBook->m_strPpEngineProgID = m_oTestTasks.m_strPpEngineProgID;

	if (nRet)
	{
		pGuideBook->AdjustByTkIDIndex(m_oTestTasks.m_strTestType, CTCtrlCntrConfig::IsAdjustByTkIDMode_Delete());
		strReportFile = m_oTestTasks.tsk_GetGbxmlFile();
		strReportFile = ChangeFilePostfix(strReportFile, g_strDocFilePostfix);
		CreateByTasks(pGuideBook, strReportFile);

		DWORD dwTkIDIndex = 0x0FFFFFFF;
		long nIndex = 1;
		CString strTemp, strNewMSWordFileName;

		strReportFile = m_oTestTasks.tsk_GetGbxmlFile();
		strReportFile = ChangeFilePostfix(strReportFile, g_strDocFilePostfix);

		delete pGuideBook;
		m_oTestTasks.SaveTasksFile();
	}
	else
	{
		delete pGuideBook;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("File [%s] not exist!"), m_oTestTasks.tsk_GetGbxmlFile());
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::CreateEnginePoProject()
{
	CString strFile = m_oTestTasks.GetPoProjectFile();

	try
	{
		//shaolei 2023-11-2 修改第一个形参传值为m_oTestTasks.m_strEngineMode
		CProtocolEngineInterface* oEngine = g_theSmartTestBaseApp->GetPpEngine(/*_T("")*/m_oTestTasks.m_strEngineMode, m_oTestTasks.m_strPpEngineProgID);

		if (oEngine != NULL)
		{
			oEngine->CreateProject(strFile);
		}
	}
	catch (...)
	{
		
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::CreateByTasks(CGuideBook *pGuideBook, const CString &strDocFile)
{
	g_theSmartTestBaseApp->ReleasePpEngine();
	CreateByTasks(&m_oTestTasks, pGuideBook, strDocFile);	
	m_oTestTasks.SavePoProjectFile();
	CreateEnginePoProject();
}

void CMdvMgrpSpoDeviceMngrTestControl::CreateByTasks(CTestTasks *pSrcTasks, CGuideBook *pGuideBook, const CString &strDocFile)
{
	POS pos = pSrcTasks->GetHeadPosition();
	CExBaseObject *p = NULL;

	pSrcTasks->InitTasksFileByParentPath();
	::CreateAllDirectories(pSrcTasks->m_strTasksPath);
	pSrcTasks->SaveTasksFileByParentPath();

	CDvmDataset *pTestApp = pSrcTasks->GetTestApp();
	pGuideBook->SetGlobalDatas_TestApp(pTestApp);
	long nTaskIndex = 0;

	while (pos != NULL)
	{
		p = pSrcTasks->GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			CreateByTask(pGuideBook, strDocFile, (CTestTask*)p, nTaskIndex);
			nTaskIndex++;
		}
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::CreateByTask(CGuideBook *pGuideBook, const CString &strDocFile, CTestTask *pTestTask, long nTaskIndex)
{
	//2021-1-18  lijunqing 没有选中的Project
	if (!pTestTask->HasTestProjectSelected())
	{
		return;
	}

	CString strTaskPath;
	strTaskPath.Format(_T("%s%s\\"), m_oTestTasks.m_strTasksPath, pTestTask->m_strLocalID);
	::CreateAllDirectories(strTaskPath);
	CString strTaskFile = strTaskPath;
	CString strTmBegin;
	strTmBegin.Format(_T("%04d%02d%02d%02d%02d%02d"), pTestTask->m_tmPlanBegin.wYear, pTestTask->m_tmPlanBegin.wMonth, pTestTask->m_tmPlanBegin.wDay
		, pTestTask->m_tmPlanBegin.wHour, pTestTask->m_tmPlanBegin.wMinute, pTestTask->m_tmPlanBegin.wSecond);
	strTaskFile.AppendFormat(_T("%s(_%s).%s"), pTestTask->m_strLocalID, strTmBegin, g_strGuideBookBinaryPostfix_SdvSpoMgrp);
	pTestTask->SaveAs(strTaskFile);

	POS pos = pTestTask->GetHeadPosition();
	CTestProject *pProject = NULL;
	CExBaseObject *p = NULL;
	CDvmDataset *pCommCmdManyConfig = pTestTask->GetCommCmdManyConfig();
	CDvmDataset *pDevcieAttr = pTestTask->GetDeviceAttr();
	long nIndex = 0;
	CDvmData *pData1 = (CDvmData*)pCommCmdManyConfig->GetHead();
	CDvmData *pData = NULL;
	CString strReportFile;
	CString strDataID;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		pProject = (CTestProject *)p;

		if (pProject->m_nSelect == 0)
		{
			continue;
		}
		
		//设置装置属性、测试仪定义
		pGuideBook->SetGlobalDatas(pProject->m_strID
			, pDevcieAttr
			, NULL);

		pGuideBook->m_strPpTemplateFile =pProject->tsk_GetPpxmlFile(FALSE);
		pGuideBook->m_strDeviceModelFile = pProject->m_strPpDeviceFile;
		pGuideBook->m_strPpEngineProgID = pProject->m_strPpEngineProgID;
		pProject->InitLocationEx(strTaskPath);
		Gb_SetGbModifiedFlag(pGuideBook, TRUE);

		//装置的ID
		strDataID.Format(_T("%d"), nTaskIndex);
		pGuideBook->AddSysPara(DATAID_DEVICEID, strDataID);

		//报告的ID == 通道的ID
		strDataID.Format(_T("%d"), pProject->m_nProjectID);
		pGuideBook->AddSysPara(DATAID_LDEVICEID, strDataID);

		//2018-12-22  开入开出通道偏移
		pGuideBook->OffsetBinary();
		strReportFile = pProject->tsk_GetLocation();
		pGuideBook->SaveBinaryFile(strReportFile, CTCtrlCntrConfig::Get_RWReportFileMode());
	
		strReportFile = ChangeFilePostfix(strReportFile, g_strDocFilePostfix);

		if( !X_CopyFile(strDocFile,strReportFile,FALSE) )
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR
				, g_sLangTxt_FileUnExistS/*L"文件\"%s\"不存在"*/
				, strDocFile);
		}
		else
		{
			ClearFileReadOnlyAttr(strReportFile);
		}
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::OpenTasksFile(const CString &strTasksFile)
{
	m_oTestTasks.OpenTasksFile(strTasksFile);
}

CTestTask* CMdvMgrpSpoDeviceMngrTestControl::GetSelectTestTask(CExBaseList &listTask, POS &posCurr)
{
	CTestTask *p = NULL, *pFind = NULL;

	while (posCurr != NULL)
	{
		p = (CTestTask *)listTask.GetNext(posCurr);

		if (p->m_nSelect == 1)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CMdvMgrpSpoDeviceMngrTestControl::InitBinRng()
{
	if (!m_bUseBinaryOffset)
	{
		return;
	}

	long nBinOffset = 0, nBoutOffset = 0;
	long nBinBeginPos = 0;
	m_pGuideBook->GetOffsetBinary(nBinOffset, nBoutOffset);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CTestControl *pPrev = this;
	nBinBeginPos = nBinOffset;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->m_pGuideBook->GetOffsetBinary(nBinOffset, nBoutOffset);
		pPrev->m_nBinRngBegin = nBinBeginPos;
		pPrev->m_nBinRngEnd = nBinOffset;
		nBinBeginPos = nBinOffset;
		pPrev = pTestControl;
	}

	pPrev->m_nBinRngBegin = nBinBeginPos;
	//pPrev->m_nBinRngEnd = 65536; //缺省值
}

void CMdvMgrpSpoDeviceMngrTestControl::CreateTestControls(BOOL bCreate)
{
	CExBaseList listTask;
	m_oTestTasks.SelectAllTestTask(listTask);

	POS pos = listTask.GetHeadPosition();
	ASSERT (pos != NULL);

	if (pos == NULL)
	{
		return;
	}

	//CTestTask *pTestTask = (CTestTask*)listTask.GetNext(pos);
	CTestTask *pTestTask = GetSelectTestTask(listTask, pos);
	ASSERT(pTestTask != NULL);

	if (pTestTask == NULL)
	{
		return;
	}

	long nTaskIndex = 0;
	CreateMainTestControls(pTestTask, nTaskIndex, bCreate);
	InitPpDevicesByTestTask(pTestTask);

	while (TRUE)
	{
		nTaskIndex++;
		//pTestTask = (CTestTask *)listTask.GetNext(pos);
		pTestTask = GetSelectTestTask(listTask, pos);

		if (pTestTask == NULL)
		{
			break;
		}

		CreateSubMgrpTestControls(pTestTask, nTaskIndex, bCreate);
	}

	listTask.RemoveAll();
}

void CMdvMgrpSpoDeviceMngrTestControl::CreateMainTestControls(CTestTask *pTestTask, long nTaskIndex, BOOL bCreate)
{
	InitByTask(pTestTask, bCreate);

	if (!bCreate)
	{
		return;
	}

	EditCommCmdDatasetPath(_T(""));

	CDvmDataset *pDeviceAttr = pTestTask->GetDeviceAttr();
	CDvmDataset *pCommCmdManyConfig = pTestTask->GetCommCmdManyConfig();
	CDvmDataset *pTestApp = m_oTestTasks.GetTestApp();
}

void CMdvMgrpSpoDeviceMngrTestControl::CreateSubMgrpTestControls(CTestTask *pTestTask, long nTaskIndex, BOOL bCreate)
{
	if (! pTestTask->HasTestProjectSelected())
	{
		return;
	}

	CMdvMgrpSpoDeviceTestControl *pNew = new CMdvMgrpSpoDeviceTestControl();
	pNew->SetParent(this);
	m_listMdvMgrpTestControl.AddTail(pNew);

	CDvmDataset *pDeviceAttr = pTestTask->GetDeviceAttr();
	CDvmDataset *pCommCmdManyConfig = pTestTask->GetCommCmdManyConfig();
	CDvmDataset *pTestApp = m_oTestTasks.GetTestApp();

	pNew->InitByTask(pTestTask, bCreate);
	pNew->EditCommCmdDatasetPath(_T(""));
	
	//装置编号:第nTaskIndex台装置
	if (bCreate)
	{
		pNew->AddSysPara(DATAID_DEVICEID, nTaskIndex);
	}

	pNew->InitPpDevicesByTestTask(pTestTask);
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::ProcessGotoItemEx()
{
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	BOOL bGotoItemTrue = FALSE;
	CGbItemBase *pItemGotoItemEx = NULL;
	long nGotoItemCount = 0;
	long nGotoItemTotal = 1;
	long nGotoItemLogic = 0;
	CGbItemBase *pItemGotoItemEx_Curr = NULL;
	CString strGotoItemExPath;

	nGotoItemCount += JudgeItemGotoItemEx(&pItemGotoItemEx_Curr, strGotoItemExPath, nGotoItemLogic);

	//主设备的子报告
	while (pos != NULL)
	{
		pTestControl = (CTestControl*)GetNext(pos);
		nGotoItemCount += pTestControl->JudgeItemGotoItemEx(&pItemGotoItemEx_Curr, strGotoItemExPath, nGotoItemLogic);
		nGotoItemTotal++;
	}

	//从设备
	POS posMngr = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *pMngr = NULL;

	while (posMngr != NULL)
	{
		pMngr = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(posMngr);
	
		//从设备报告
		nGotoItemCount += pMngr->JudgeItemGotoItemEx(&pItemGotoItemEx_Curr, strGotoItemExPath, nGotoItemLogic);
		nGotoItemTotal++;

		//从设备的子报告
		pos = pMngr->GetHeadPosition();

		while (pos != NULL)
		{
			pTestControl = (CTestControl *)pMngr->GetNext(pos);
			nGotoItemCount += pTestControl->JudgeItemGotoItemEx(&pItemGotoItemEx_Curr, strGotoItemExPath, nGotoItemLogic);
			nGotoItemTotal++;
		}
	}

	if (pItemGotoItemEx_Curr == NULL || strGotoItemExPath.GetLength() == 0)
	{
		return FALSE;
	}

	CGbItemBase *pMainItemCurr = (CGbItemBase*)GetItem(m_pGuideBook, pItemGotoItemEx_Curr);
	CGbItemBase *pMainItemGoto = pMainItemCurr->SelectItem(strGotoItemExPath);

	if (pMainItemGoto == NULL)
	{
		return FALSE;
	}

	if (nGotoItemLogic == 1)
	{
		if (nGotoItemTotal == nGotoItemCount)
		{
			bGotoItemTrue = TRUE;
			GotoItem(pMainItemGoto);
		}
	}
	else
	{
		if (nGotoItemCount > 0)
		{
			bGotoItemTrue = TRUE;
			GotoItem(pMainItemGoto);
		}
	}

	return bGotoItemTrue;
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::ProcessBreakLoopByAllRpt()
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

	if (!bAllBreakLoop)
	{
		return bAllBreakLoop;
	}

	//从设备
	POS posMngr = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *pMngr = NULL;

	while (posMngr != NULL)
	{
		pMngr = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(posMngr);

		//从设备报告
		if (pMngr->GetBreakLoopState() == 0)
		{
			bAllBreakLoop = FALSE;
			break;
		}

		//从设备的子报告
		pos = pMngr->GetHeadPosition();

		while (pos != NULL)
		{
			pTestControl = (CTestControl *)pMngr->GetNext(pos);

			if (pTestControl->GetBreakLoopState() == 0)
			{
				bAllBreakLoop = FALSE;
				break;
			}
		}

		if (!bAllBreakLoop)
		{
			break;
		}
	}

	if (bAllBreakLoop)
	{
		if (m_pCurrSubTestItem != NULL)
		{
			m_pCurrSubTestItem->m_nBreakLoopState = 1;
		}

		m_pCurrTestItem->m_nBreakLoopState = 1;
	}

	return bAllBreakLoop;
}

long CMdvMgrpSpoDeviceMngrTestControl::FinishTestItemMacroTest_Process(CMacroTest* pItem) //2019-4-27 MdvTestEach
{
	return CTestControl::FinishTestItemMacroTest_Process(pItem);
}

CTestControl* CMdvMgrpSpoDeviceMngrTestControl::GetTestControlByIndex(long nIndex)
{
	if (nIndex == 0)
	{
		return this;
	}

	if (nIndex < GetCount())
	{
		return (CTestControl*)GetAtIndex(nIndex-1);
	}

	nIndex--;
	nIndex -= GetCount();

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlMngrBase *pMngr = NULL;

	while (pos != NULL)
	{
		pMngr = (CTestControlMngrBase *)m_listMdvMgrpTestControl.GetNext(pos);

		if (nIndex == 0)
		{
			return pMngr;
		}

		if (nIndex < pMngr->GetCount())
		{
			return (CTestControl*)pMngr->GetAtIndex(nIndex-1);
		}

		nIndex--;
		nIndex-= pMngr->GetCount();
	}

	return NULL;
}


void CMdvMgrpSpoDeviceMngrTestControl::ReleaseMacroTestInterface(BOOL bRelease)
{
	//删除自身
	CTestControl::ReleaseMacroTestInterface(TRUE);

	//清空自身子对象
	CTestControlMngrBase::ReleaseMacroTestInterface(FALSE);

	//删除子装置
	POS pos = GetHeadPosition();
	CTestControlMngrBase *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControlMngrBase *)GetNext(pos);
		pTestControl->ReleaseMacroTestInterface(FALSE);
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::SaveFinalXMLReport()
{
	CTestControlBase::SaveFinalXMLReport();

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		CTestControlBase *pTestControl = (CTestControlBase *)m_listMdvMgrpTestControl.GetNext(pos);

		pTestControl->SaveFinalXMLReport();
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::UploadRptFiles(CString &strFiles)
{
	CDataGroup oGroup;
	CDataGroup *pGroup = oGroup.AddNewGroup(m_strName, m_strID, _T(""));
	CTestControlBase::UploadRptFiles(pGroup);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		CTestControlBase *pTestControl = (CTestControlBase *)m_listMdvMgrpTestControl.GetNext(pos);
		pGroup = oGroup.AddNewGroup(pTestControl->m_strName, pTestControl->m_strID, _T(""));
		pTestControl->UploadRptFiles(pGroup);
	}

	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	oGroup.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strFiles);
	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
}

void CMdvMgrpSpoDeviceMngrTestControl::AdjustReport(CThreadProgressInterface *pProgress)
{
	CTestControlBase::AdjustReport(pProgress);

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		CTestControlBase *pTestControl = (CTestControlBase *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->CTestControlBase::AdjustReport(pProgress);
	}
}

BOOL CMdvMgrpSpoDeviceMngrTestControl::SetItemState(CDataGroup *pParas)
{
	BOOL bRet1 = CTestControlBase::SetItemState(pParas);
	BOOL bRet2 = FALSE;
	BOOL bRet = TRUE;

	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		CTestControlBase *pTestControl = (CTestControlBase *)m_listMdvMgrpTestControl.GetNext(pos);
		bRet2 = pTestControl->CTestControlBase::SetItemState(pParas);

		if (!bRet2)
		{
			bRet = FALSE;
		}
	}

	return bRet && bRet1;
}

void CMdvMgrpSpoDeviceMngrTestControl::ResetTestControl()
{
	CTestControlBase::ResetTestControl();
	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		CTestControlBase *pTestControl = (CTestControlBase *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->CTestControlBase::ResetTestControl();
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::AddTCtrlMsgRcvInterface(CTCtrlMsgRcvInterface *pInterface)
{
	CTestControlBase::AddTCtrlMsgRcvInterface(pInterface);
	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		CTestControlBase *pTestControl = (CTestControlBase *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->CTestControlBase::AddTCtrlMsgRcvInterface(pInterface);
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::OnTestItemCount_TCtrlMsg(long nItemCount)
{
	CTestControlBase::OnTestItemCount_TCtrlMsg(nItemCount);
	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		CTestControlBase *pTestControl = (CTestControlBase *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->CTestControlBase::OnTestItemCount_TCtrlMsg(nItemCount);
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::OnTestBegin_TCtrlMsg()
{
	CTestControlBase::OnTestBegin_TCtrlMsg();
	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		CTestControlBase *pTestControl = (CTestControlBase *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->CTestControlBase::OnTestBegin_TCtrlMsg();
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::OnStopTest_TCtrlMsg(long nType)
{
	CTestControlBase::OnStopTest_TCtrlMsg(nType);
	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		CTestControlBase *pTestControl = (CTestControlBase *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->CTestControlBase::OnStopTest_TCtrlMsg(nType);
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::OnException_TCtrlMsg(long nEvent, const CString &strError)
{
	CTestControlBase::OnException_TCtrlMsg(nEvent, strError);
	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		CTestControlBase *pTestControl = (CTestControlBase *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->CTestControlBase::OnException_TCtrlMsg(nEvent, strError);
	}
}

void CMdvMgrpSpoDeviceMngrTestControl::OnConnectSuccess_TCtrlMsg()
{
	CTestControlBase::OnConnectSuccess_TCtrlMsg();
	POS pos = m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		CTestControlBase *pTestControl = (CTestControlBase *)m_listMdvMgrpTestControl.GetNext(pos);
		pTestControl->CTestControlBase::OnConnectSuccess_TCtrlMsg();
	}
}