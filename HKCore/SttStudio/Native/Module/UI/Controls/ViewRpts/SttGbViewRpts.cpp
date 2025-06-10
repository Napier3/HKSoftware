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
	strTitle = /*_T("��Ŀ���")*/g_sLangTxt_Native_ProjResults;
	m_tabRpts->addTab(m_pGridValues_RsltExpr, strTitle);

	strTitle = /*_T("ȫ����������")*/g_sLangTxt_Native_AllRptData;
	m_tabRpts->addTab(m_pGridValues_All, strTitle);

	strTitle = /*_T("��������-���ݼ�")*/g_sLangTxt_Native_RptDataDataset;
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
	pNew->m_strName = /*_T("���Խ���")*/g_sLangTxt_Native_TestConcl;
	m_oListRsltExpr.AddNewChild(pNew);

	CExBaseList oListXExprValues; //��ʱ������������Ŀ·����CXExprValue����
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
		//�̶���һ���������������� 1  ���ж�
		m_tabRpts->removeTab(0);
	}
}

void QSttGbViewRpts::SetWindowTitle()
{
	CString strTitle;

	if (m_pSttItemBase == NULL)
	{
		strTitle = /*_T("�鿴����")*/g_sLangTxt_Native_ViewRpt;
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
		//���ڵ�������Ŀ���˴���Ҫ�����������Ŀ������ظ�����
		CSttMacroTest *pMacroTest = (CSttMacroTest *)m_pSttItemBase;
		nMacroTestRepeatTimes = pMacroTest->m_nRepeatTimes;
	}

	CString strText = /*_T("�β���")*/g_sLangTxt_Native_TestRun;
	CString strAdd = /*_T("��")*/g_sLangTxt_Native_Number;
	CString strIndex;
	long nCal = 1;
	CString strCal = /*_T("�μ�����")*/g_sLangTxt_Native_CalcResult;

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
// 		//˵��������������Դ�����Ӧ��������ֻȡ���һ��
// 		pListReports->AddTail(pRpts->GetTail());
// 		return;
// 	}

	UINT nClassID = pSttItemBase->GetClassID();
	
	if (nClassID == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		//���ڵ�������Ŀ���˴���Ҫ�����������Ŀ������ظ�����
		CSttMacroTest *pMacroTest = (CSttMacroTest *)pSttItemBase;
		long nMacroTestRepeatTimes = pMacroTest->m_nRepeatTimes;

		if (nMacroTestRepeatTimes > 1)
		{
			nTestCount += nTestCount/nMacroTestRepeatTimes;  //���ڵ������Լ��ظ����ԵĲ��֣�Ӧ�����ϼ���ı�������
		}
	}

	POS pos = pRpts->GetTailPosition();
	
	while(nTestCount > 0 && pos != NULL)
	{
		CSttReport *pRpt = (CSttReport *)pRpts->GetPrev(pos);

		if (pRpts->GetCount() > 1 && pRpt->m_strID == _T("_Init_"))
		{
			//���Ѿ�����ʱ��������ʼ������
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
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("��Ŀ��%s�����ҽ����Ψһ���ҵ���%d����Ŀ����Ŀ"), strItemPath.GetString(), nCount);
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