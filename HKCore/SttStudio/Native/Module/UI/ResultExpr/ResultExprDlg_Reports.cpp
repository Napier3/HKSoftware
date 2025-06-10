#include "ResultExprDlg_Reports.h"
#include "ui_ResultExprDlg_Reports.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QResultExprDlg_Reports::QResultExprDlg_Reports(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QResultExprDlg_Reports)
{
    ui->setupUi(this);

	m_pCurItemBase = NULL;
	m_pGuideBook = NULL;
	m_pReport = NULL;
	InitLanguage();

	connect(ui->m_btnOK, SIGNAL(clicked(bool)), this, SLOT(slot_btnOK_Clicked(bool)));
	connect(ui->m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(slot_btnCancel_Clicked(bool)));
}

QResultExprDlg_Reports::~QResultExprDlg_Reports()
{
    delete ui;
}

void QResultExprDlg_Reports::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->m_btnOK,g_sLangTxt_OK,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnCancel,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);
}

void QResultExprDlg_Reports::slot_btnOK_Clicked(bool bCheck)
{
	QTreeWidgetItem* pItem = ui->m_treeReport->currentItem();
	CSttItemBase* pSttItemBase = (CSttItemBase*)pItem->data(0, Qt::UserRole).toInt();
	m_pCurItemBase->GetRefObjPath(pSttItemBase, m_strCurrSelPath);
	if(!m_strCurrSelPath.GetLength())
	{
		m_strCurrSelPath = m_pCurItemBase->m_strID;
	}
	if((CSttReport*)pSttItemBase->GetSttReports())
	{
		m_pReport = (CSttReport*)pSttItemBase->GetSttReports()->GetTail();
	}
	else
	{
		m_pReport = NULL;
	}
	accept();
}	

void QResultExprDlg_Reports::slot_btnCancel_Clicked(bool bCheck)
{
	reject();
}

void QResultExprDlg_Reports::InitDlg(CSttItemBase* pCurItemBase, CSttGuideBook* pGuideBook)
{
	m_pCurItemBase = pCurItemBase;
	m_pGuideBook = pGuideBook;
	CSttDevice* pDevice = (CSttDevice*)pGuideBook->GetDevice();
	POS pos = pDevice->GetHeadPosition();
	while(pos)
	{
		CSttItemBase* pItemBase = (CSttItemBase*)pDevice->GetNext(pos);

		QTreeWidgetItem* pItem = new QTreeWidgetItem(ui->m_treeReport);
		ui->m_treeReport->addTopLevelItem(pItem);
		pItem->setData(0, Qt::UserRole, QVariant::fromValue((long)pItemBase));
		pItem->setText(0, pItemBase->m_strName);

		InitTree(pItem, pItemBase);
		if(m_pCurItemBase == pItemBase)
		{
			ui->m_treeReport->expandItem(pItem);
			ui->m_treeReport->setCurrentItem(pItem);
		}
	}
}

void QResultExprDlg_Reports::InitTree(QTreeWidgetItem* pParent, CSttItemBase* pCurItemBase)
{
	POS pos = pCurItemBase->GetHeadPosition();
	while(pos)
	{
		CSttItemBase* pItemBase = (CSttItemBase*)pCurItemBase->GetNext(pos);

		if(pItemBase->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST
			|| pItemBase->GetClassID() == STTGBXMLCLASSID_CSTTCOMMCMD
			|| pItemBase->GetClassID() == STTGBXMLCLASSID_CSTTITEMS
			|| pItemBase->GetClassID() == STTGBXMLCLASSID_CSTTMACROCHARITEMS)
		{
			QTreeWidgetItem* pItem = new QTreeWidgetItem(pParent);
			pItem->addChild(pItem);
			pItem->setData(0, Qt::UserRole, QVariant::fromValue((long)pItemBase));
			pItem->setText(0, pItemBase->m_strName);

			InitTree(pItem, pItemBase);	
			if(m_pCurItemBase == pItemBase)
			{
				ui->m_treeReport->expandItem(pItem);
				ui->m_treeReport->setCurrentItem(pItem);
			}
		}
	}
}