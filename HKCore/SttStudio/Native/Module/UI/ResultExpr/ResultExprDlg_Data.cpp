#include "ResultExprDlg_Data.h"
#include "ui_ResultExprDlg_Data.h"
#include "ResultExprWidgetItem.h"
#include "ResultExprDlg_Reports.h"
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../../../../Module/DataMngr/DvmDataset.h"
#include "../../../../Module/DataMngr/DvmLogicDevice.h"
#include "../SttTestCntrFrameBase.h"
#include <QMenu>
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

#define REPORTGRID_COLS 3
extern CGbSmartGenWzd *g_theGbSmartGenWzd;

QResultExprDlg_DataGrid::QResultExprDlg_DataGrid(QWidget* pParent)
: QExBaseListGridBase(pParent)
{
	m_pTestMacros = NULL;
}

QResultExprDlg_DataGrid::~QResultExprDlg_DataGrid()
{

}

void QResultExprDlg_DataGrid::InitGrid()
{
	InitGridTitle();
	SetDefaultRowHeight(50);
	SetEditable(FALSE);
}

void QResultExprDlg_DataGrid::InitGridTitle()
{
	CString astrGridTitle[REPORTGRID_COLS] = {/*"数据名称"*/g_sLangTxt_DataName, /*"数据ID"*/g_sLangTxt_Native_dataid, /*"数值"*/g_sLangTxt_Value};
	int iGridWidth[REPORTGRID_COLS]={200, 200, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, REPORTGRID_COLS);
}

void QResultExprDlg_DataGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CString strMacroID;
	if(m_pCurSttItemBase->GetClassID() == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		strMacroID = ((CSttCommCmd*)m_pCurSttItemBase)->m_strCommCmdID;
	}
	else if(m_pCurSttItemBase->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		strMacroID = ((CSttMacroTest*)m_pCurSttItemBase)->m_strMacroID;
	}

	if(((CExBaseList*)pData)->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		CDvmValue* pValue = (CDvmValue*)pData;
		Show_StaticString(pData, nRow, 0, pValue->m_strName);
		if(!pValue->m_strName.GetLength())
		{
			CString strName = g_theTestCntrFrame->FindNameFromTestMacros(m_pTestMacros, strMacroID, pValue->m_strID);
			Show_StaticString(pData, nRow, 0, strName);
		}
		Show_StaticString(pData, nRow, 1, pValue->m_strID);
		Show_StaticString(pData, nRow, 2, pValue->m_strValue);
	}
	else if(((CExBaseList*)pData)->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		CDvmData* pValue = (CDvmData*)pData;
		Show_StaticString(pData, nRow, 0, pValue->m_strName);
		if(!pValue->m_strName.GetLength())
		{
			CString strName = g_theTestCntrFrame->FindNameFromTestMacros(m_pTestMacros, strMacroID, pValue->m_strID);
			Show_StaticString(pData, nRow, 0, strName);
		}
		Show_StaticString(pData, nRow, 1, pValue->m_strID);
		Show_StaticString(pData, nRow, 2, pValue->m_strValue);
	}
	
	nRow++;
}

QResultExprDlg_Data::QResultExprDlg_Data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QResultExprDlg_Data)
{
    ui->setupUi(this);
	m_pCurSttItemBase = NULL;
	m_pCurSelValue = NULL;
	m_pReports = NULL;
	m_pGuideBook = NULL;
	m_pTestMacros = NULL;
	m_pReportGrid = new QResultExprDlg_DataGrid(this);
	m_pReportGrid->InitGrid();
	InitLanguage();

	CString strTitle = /*"参数选择"*/g_sLangTxt_Native_paramselect;
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::Dialog);

	connect(ui->m_btnOK, SIGNAL(clicked(bool)), this, SLOT(slot_btnOK_Clicked(bool)));
	connect(ui->m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(slot_btnCancel_Clicked(bool)));
	connect(ui->m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slot_currentChanged(int)));
	connect(ui->m_btnChangeReport, SIGNAL(clicked()), this, SLOT(slot_btnChangeReport_Clicked()));
	connect(ui->m_treeDataset, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(slot_currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
}

QResultExprDlg_Data::~QResultExprDlg_Data()
{
    delete ui;
}

void QResultExprDlg_Data::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->tab,g_sLangTxt_DataSet,XLang_Ctrls_QTabWidget);
	xlang_SetLangStrToWidget_Txt(ui->tab_2,g_sLangTxt_SystemPara,XLang_Ctrls_QTabWidget);
	xlang_SetLangStrToWidget_Txt(ui->tab_3,g_sLangTxt_Native_globalparams,XLang_Ctrls_QTabWidget);
	xlang_SetLangStrToWidget_Txt(ui->tab_4,g_sLangTxt_Native_reportdata,XLang_Ctrls_QTabWidget);
	xlang_SetLangStrToWidget_Txt(ui->tab_5,g_sLangTxt_Value,XLang_Ctrls_QTabWidget);
	xlang_SetLangStrToWidget_Txt(ui->m_btnChangeReport,g_sLangTxt_Native_switchreport,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_txtPathLabel,g_sLangTxt_Path,XLang_Ctrls_QLabel);

}

void QResultExprDlg_Data::ShowDatas(CExBaseList* pList)
{
	ui->m_tabWidget->hide();
	ui->m_layoutTop->insertWidget(0, ui->m_btnChangeReport);
	ui->m_layoutTop->insertWidget(1, ui->m_txtPathLabel);
	ui->m_layoutTop->insertWidget(2, ui->m_txtPath);
	ui->m_layoutGrid->addWidget(m_pReportGrid);
	m_pReportGrid->ShowDatas(pList);
	m_pReportGrid->show();
}

void QResultExprDlg_Data::InitDlg(CSttItemBase* pCurSttItemBase, CSttReports* pReports, CSttGuideBook* pGuideBook, CTestMacros* pTestMacros)
{
	m_pCurSttItemBase = pCurSttItemBase;
	ui->m_txtPath->setText(pCurSttItemBase->m_strID);
	m_pGuideBook = pGuideBook;
	m_pReports = pReports;
	m_pTestMacros = pTestMacros;
	m_pReportGrid->m_pTestMacros = m_pTestMacros;
	m_pReportGrid->m_pCurSttItemBase = m_pCurSttItemBase;
	ui->m_tabWidget->setCurrentIndex(0);
	slot_currentChanged(0);
}

void QResultExprDlg_Data::slot_btnOK_Clicked(bool bCheck)
{
	if(ui->m_tabWidget->isVisible())
	{
		CString strText = ui->m_tabWidget->tabText(ui->m_tabWidget->currentIndex());
		if(strText == STR_VALUE)
		{
			//当前选中的是数值则解除之前选中的表格参数的绑定
			m_strCurValue = ui->m_editValue->text();
			m_pCurSelValue = NULL;
		}
		else
		{
			//存在绑定的表格参数则返回对应参数
			m_pCurSelValue = (CDvmValue*)m_pReportGrid->GetCurrSelData();
		}

		m_strCurType = ResultExpr_GetSelectExpr(strText);
	}
	else
	{
		m_pCurSelValue = (CDvmValue*)m_pReportGrid->GetCurrSelData();
		m_strCurType = EXPRTYPE_REPORT;
	}

	accept();
}	

void QResultExprDlg_Data::slot_btnCancel_Clicked(bool bCheck)
{
	reject();
}

void QResultExprDlg_Data::slot_btnChangeReport_Clicked()
{
	QResultExprDlg_Reports dlg(this);
	dlg.InitDlg(m_pCurSttItemBase, m_pGuideBook);
	if(dlg.exec() == QDialog::Accepted)
	{
		if(dlg.m_pReport)
		{
			m_pReportGrid->ShowDatas(dlg.m_pReport->m_pValues);
		}
		else
		{
			m_pReportGrid->ShowDatas(NULL);
		}
		ui->m_txtPath->setText(dlg.m_strCurrSelPath);
	}
}

void QResultExprDlg_Data::slot_SelectReport(bool bCheck)
{
	QAction* pAction = (QAction*)sender();
	CSttItemBase* pItem = (CSttItemBase*)pAction->data().toInt();

	CString strCurrSelPath;
	m_pCurSttItemBase->GetRefObjPath(pItem, strCurrSelPath);
	ui->m_txtPath->setText(strCurrSelPath);
	if(!strCurrSelPath.GetLength())
	{
		ui->m_txtPath->setText(m_pCurSttItemBase->m_strID);
	}

	CSttMacroTest* pMacroTest = (CSttMacroTest*)pItem->FindByClassID(STTGBXMLCLASSID_CSTTMACROTEST);
	if(pMacroTest)
	{
		CSttReports* pReports = (CSttReports*)pMacroTest->GetSttReports();
		CSttReport* pReport = (CSttReport*)pReports->GetTail();
		m_pReportGrid->ShowDatas(pReport->m_pValues);
	}
	else
	{
		m_pReportGrid->ShowDatas(NULL);
	}
}

void QResultExprDlg_Data::ShowDatasetTree()
{
	if(ui->m_treeDataset->topLevelItemCount())
	{
		if(ui->m_treeDataset->currentItem())
		{
			QVariant var = ui->m_treeDataset->currentItem()->data(0, Qt::UserRole);
			CDvmDataset* pDataset = (CDvmDataset*)var.toInt();
			if(pDataset)
			{
				m_pReportGrid->ShowDatas(pDataset);
				return;
			}
		}

		m_pReportGrid->ShowDatas(NULL);
		return;
	}

	CDvmDevice* pDevice = g_theGbSmartGenWzd->m_pDvmDevice;
	POS pos = pDevice->GetHeadPosition();
	while(pos)
	{
		CDvmLogicDevice* pLogicDevice = (CDvmLogicDevice*)pDevice->GetNext(pos);
		QTreeWidgetItem* pItem = new QTreeWidgetItem(ui->m_treeDataset);
		pItem->setText(0, pLogicDevice->m_strName);
		ui->m_treeDataset->addTopLevelItem(pItem);

		POS childPos = pLogicDevice->GetHeadPosition();
		while(childPos)
		{
			CDvmDataset* pDataset = (CDvmDataset*)pLogicDevice->GetNext(childPos);
			QTreeWidgetItem* pChildItem = new QTreeWidgetItem(pItem);
			pChildItem->setText(0, pDataset->m_strName);
			pChildItem->setData(0, Qt::UserRole, QVariant::fromValue((long)pDataset));
		}
	}
}

void QResultExprDlg_Data::slot_currentChanged(int nIndex)
{
	QGridLayout* pLayout = (QGridLayout*)ui->m_tabWidget->currentWidget()->layout();
	pLayout->addWidget(m_pReportGrid);

	m_pReportGrid->show();
	CString strText = ui->m_tabWidget->tabText(ui->m_tabWidget->currentIndex());
	if(strText == STR_DATASET)
	{
		ShowDatasetTree();
	}
	else if(strText == STR_SYSPARAS)
	{
		CSttDevice* pDevice = m_pGuideBook->GetDevice();
		m_pReportGrid->ShowDatas(pDevice->GetSysPara(FALSE));
	}
	else if(strText == STR_GLOBALPARAS)
	{
		m_pReportGrid->ShowDatas(m_pGuideBook->GetGlobalDatas());
	}
	else if(strText == STR_RPTDATA)
	{
		if(m_pReports)
		{
			CSttReport* pReport = (CSttReport*)m_pReports->GetTail();
			m_pReportGrid->ShowDatas(pReport->m_pValues);
		}
		else
		{
			m_pReportGrid->ShowDatas(NULL);
		}
	}
	else if(strText == STR_VALUE)
	{
		ui->m_editValue->setText(m_strCurValue);
		m_pReportGrid->hide();
	}
	else if(strText == STR_CAL)
	{
		m_pReportGrid->hide();
	}
}

void QResultExprDlg_Data::slot_currentItemChanged(QTreeWidgetItem* pCurItem, QTreeWidgetItem* pPrevItem)
{
	QVariant var = pCurItem->data(0, Qt::UserRole);
	CDvmDataset* pDataset = (CDvmDataset*)var.toInt();
	if(pDataset)
	{
		m_pReportGrid->ShowDatas(pDataset);
	}
}