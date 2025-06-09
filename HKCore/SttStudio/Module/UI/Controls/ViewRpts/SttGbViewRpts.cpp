#include "SttGbViewRpts.h"
#include "ui_SttGbViewRpts.h"
#include "..\..\..\SttCmd\GuideBook\SttMacroTest.h"
#include "../../../XLangResource_Native.h"
#include "../../../SttCmd/GuideBook/SttDevice.h"
void QSttGbViewRpts::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	
}

BOOL QSttGbViewRpts::OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar)
{
	return TRUE;
}

QSttGbViewRpts::QSttGbViewRpts(CSttItemBase *pSttItemBase, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttGbViewRpts)
{
    ui->setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);

	m_pSttItemBase = pSttItemBase;

	m_tabRpts = new QTabWidget();
	ui->horizontalLayout->addWidget(m_tabRpts);

	m_pGridValues_RsltExpr = new CSttGbRptGrid_Values(this);
	m_pGridValues_RsltExpr->InitGrid();
	m_pGridValues_RsltExpr->AttachDataViewOptrInterface(this);

	m_pGridValues_All = new CSttGbRptGrid_Values(this);
	m_pGridValues_All->InitGrid();
	m_pGridValues_All->AttachDataViewOptrInterface(this);

	m_pGridDataset = new CSttGbRptGrid_Dataset(this);
	m_pGridDataset->InitGrid();
	m_pGridDataset->AttachDataViewOptrInterface(this);

	CString strTitle; 
	strTitle = /*_T("项目结果")*/g_sLangTxt_Native_ProjResults;
	m_tabRpts->addTab(m_pGridValues_RsltExpr, strTitle);

	strTitle = /*_T("全部报告数据")*/g_sLangTxt_Native_AllRptData;
	m_tabRpts->addTab(m_pGridValues_All, strTitle);

	strTitle = /*_T("报告数据-数据集")*/g_sLangTxt_Native_RptDataDataset;
	m_tabRpts->addTab(m_pGridDataset, strTitle);

	m_tabRpts->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	InitShowReports(m_pSttItemBase, &m_oListReports);
	TestCountComboBox_Init(ui->m_cmbTestCount);

	if (m_pSttItemBase != NULL)
	{
		long nTestCount = m_pSttItemBase->GetItemTestCount();

		if (nTestCount > m_oListReports.GetCount())
		{
			//ui->m_cmbTestCount->setDisabled(true);
		}
	}
	//ShowRpts();
	SetWindowTitle();
}

QSttGbViewRpts::~QSttGbViewRpts()
{
	m_oListReports.RemoveAll();
    delete ui;
}

void QSttGbViewRpts::ShowRpts(long nIndex)
{
	if (m_pSttItemBase == NULL)
	{
		m_pGridDataset->ShowDatas(NULL);
		m_pGridValues_All->ShowDatas(NULL);
		m_pGridValues_RsltExpr->ShowDatas(NULL);
		return;
	}

	if (m_oListReports.GetCount() == 0)
	{
		m_pGridDataset->ShowDatas(NULL);
		m_pGridValues_All->ShowDatas(NULL);
		m_pGridValues_RsltExpr->ShowDatas(NULL);
		return;
	}

	CSttReport *pReport = (CSttReport *)m_oListReports.GetAtIndex(nIndex);

	if (pReport == NULL)
	{
		m_pGridDataset->ShowDatas(NULL);
		m_pGridValues_All->ShowDatas(NULL);
		m_pGridValues_RsltExpr->ShowDatas(NULL);
		return;
	}

	m_pGridDataset->ShowDatas(pReport->m_pRptDvmDataset);
	m_pGridValues_All->ShowDatas(pReport->m_pValues);

	m_oListRsltExpr.DeleteAll();
	CDvmValue *pRsltDsc = (CDvmValue *)pReport->m_pValues->FindByID(_T("RsltDsc"));
	CDvmValue *pNew = (CDvmValue *)pRsltDsc->Clone();
	pNew->m_strName = /*_T("测试结论")*/g_sLangTxt_Native_TestConcl;
	m_oListRsltExpr.AddNewChild(pNew);

	CExBaseList oListXExprValues; //临时链表，存放相对项目路径的CXExprValue对象
	m_pSttItemBase->GetRsltExprValues(&m_oListRsltExpr, pReport->m_pValues, &oListXExprValues);

	if (oListXExprValues.GetCount() > 0)
	{
		GetRsltExprValues_RelPath(&m_oListRsltExpr, &oListXExprValues, nIndex);
		oListXExprValues.RemoveAll();
	}

	m_pGridValues_RsltExpr->ShowDatas(&m_oListRsltExpr);

	if (pReport->m_pRptDvmDataset->GetCount() == 0)
	{
		m_tabRpts->removeTab(2);
	}

	if (m_oListRsltExpr.GetCount() == 1)
	{
		//固定有一个结果描述，因此用 1  来判断
		m_tabRpts->removeTab(0);
	}
}

void QSttGbViewRpts::SetWindowTitle()
{
	CString strTitle;

	if (m_pSttItemBase == NULL)
	{
		strTitle = /*_T("查看报告")*/g_sLangTxt_Native_ViewRpt;
	}
	else
	{
		strTitle = m_pSttItemBase->GetNamePathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	}
	
	setWindowTitle(strTitle);
}

void QSttGbViewRpts::TestCountComboBox_Init(QComboBox *pComboBox)
{
	pComboBox->clear();

	long nTestCount = m_pSttItemBase->GetItemTestCount();
	long nMacroTestRepeatTimes = -1;

	if (m_pSttItemBase->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		//对于电气量项目，此处还要处理电气量项目本身的重复次数
		CSttMacroTest *pMacroTest = (CSttMacroTest *)m_pSttItemBase;
		nMacroTestRepeatTimes = pMacroTest->m_nRepeatTimes;
	}

	CString strText = /*_T("次测试")*/g_sLangTxt_Native_TestRun;
	CString strAdd = /*_T("第")*/g_sLangTxt_Native_Number;
	CString strIndex;
	long nCal = 1;
	CString strCal = /*_T("次计算结果")*/g_sLangTxt_Native_CalcResult;

	for (int nIndex=1; nIndex<=nTestCount; nIndex++)
	{
		strIndex.Format(_T("%d"), nIndex);
		strIndex = strAdd + strIndex;
		pComboBox->addItem(strIndex + strText);

		if (nMacroTestRepeatTimes > 1)
		{
			if (nIndex % nMacroTestRepeatTimes == 0)
			{
				strIndex.Format(_T("%d"), nCal);
				strIndex = strAdd + strIndex;
				pComboBox->addItem(strIndex + strCal);
				nCal++;
			}
		}
	}
}

void QSttGbViewRpts::InitShowReports(CSttItemBase *pSttItemBase, CExBaseList *pListReports)
{
	pListReports->RemoveAll();

	if (pSttItemBase == NULL)
	{
		return;
	}

	long nTestCount = pSttItemBase->GetItemTestCount();
	CSttReports *pRpts = pSttItemBase->GetSttReports();

	if (pRpts == NULL)
	{
		return;
	}

	if (pRpts->GetCount() == 0 )
	{
		return;
	}

// 	if (pRpts->GetCount() < nTestCount)
// 	{
// 		//说明报告数量与测试次数对应不起来，只取最后一次
// 		pListReports->AddTail(pRpts->GetTail());
// 		return;
// 	}

	UINT nClassID = pSttItemBase->GetClassID();
	
	if (nClassID == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		//对于电气量项目，此处还要处理电气量项目本身的重复次数
		CSttMacroTest *pMacroTest = (CSttMacroTest *)pSttItemBase;
		long nMacroTestRepeatTimes = pMacroTest->m_nRepeatTimes;

		if (nMacroTestRepeatTimes > 1)
		{
			nTestCount += nTestCount/nMacroTestRepeatTimes;  //对于电气量自己重复测试的部分，应当加上计算的报告数量
		}
	}

	POS pos = pRpts->GetTailPosition();
	
	while(nTestCount > 0 && pos != NULL)
	{
		CSttReport *pRpt = (CSttReport *)pRpts->GetPrev(pos);

		if (pRpts->GetCount() > 1 && pRpt->m_strID == _T("_Init_"))
		{
			//当已经测试时，跳过初始化报告
			continue;
		}
		pListReports->AddTail(pRpt);
		pListReports->BringToHead(pRpt);
		nTestCount--;
	}
}

void QSttGbViewRpts::GetRsltExprValues_RelPath(CExBaseList *pRlstExprValues, CExBaseList *pListXExprValues, long nRptIndex)
{
	if (m_pSttItemBase == NULL)
	{
		return;
	}

	POS pos = pListXExprValues->GetHeadPosition();
	CSttDevice *pDevice = (CSttDevice*)m_pSttItemBase->GetAncestor(STTGBXMLCLASSID_CSTTDEVICE);

	while (pos != NULL)
	{
		CXExprValue *pExprValue = (CXExprValue *)pListXExprValues->GetNext(pos);
		CSttItemBase *pRelItem = GetRelItem(pExprValue->m_strItemPath);

		if (pRelItem == NULL)
		{
			continue;
		}

		CSttReports oRpts;
		InitShowReports(pRelItem, &oRpts);

		if (oRpts.GetCount() == 0)
		{
			continue;
		}

		if (oRpts.GetCount() < nRptIndex + 1)
		{
			nRptIndex = 0;
		}

		CSttReport *pReport = (CSttReport *)oRpts.GetAtIndex(nRptIndex);

		if (pReport == NULL)
		{
			oRpts.RemoveAll();
			continue;
		}

		pExprValue->GetRsltExprValues_RelPath(pRelItem, pReport->m_pValues, pDevice, pRlstExprValues);
		oRpts.RemoveAll();
	}
}

CSttItemBase* QSttGbViewRpts::GetRelItem(const CString &strItemPath)
{
	if (m_pSttItemBase == NULL)
	{
		return NULL;
	}

	CExBaseList oDestList;
	m_pSttItemBase->SelectItems(strItemPath, oDestList);
	long nCount = oDestList.GetCount();

	if (nCount != 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("项目【%s】查找结果不唯一！找到【%d】个目标项目"), strItemPath.GetString(), nCount);
		oDestList.RemoveAll();
		return NULL;
	}

	CSttItemBase *pDestItem = (CSttItemBase *)oDestList.GetHead();
	oDestList.RemoveAll();
	return pDestItem;
}

void QSttGbViewRpts::on_m_cmbTestCount_currentIndexChanged(int index)
{
	ShowRpts(index);
}