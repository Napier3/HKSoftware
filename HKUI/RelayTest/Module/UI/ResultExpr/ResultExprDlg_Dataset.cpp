#include "ResultExprDlg_Dataset.h"
#include "ui_ResultExprDlg_Dataset.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

#define REPORTGRID_COLS 1

QResultExprDlg_DatasetGrid::QResultExprDlg_DatasetGrid(QWidget* pParent)
: QExBaseListGridBase(pParent)
{
	
}

QResultExprDlg_DatasetGrid::~QResultExprDlg_DatasetGrid()
{

}

void QResultExprDlg_DatasetGrid::InitGrid()
{
	InitGridTitle();
	SetDefaultRowHeight(50);
	SetEditable(FALSE);
}

void QResultExprDlg_DatasetGrid::InitGridTitle()
{
	CString astrGridTitle[REPORTGRID_COLS] = {/*"报告数据名称"*/g_sLangTxt_Native_reportdataname};
	int iGridWidth[REPORTGRID_COLS]={100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, REPORTGRID_COLS);
}

void QResultExprDlg_DatasetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmValue* pValue = (CDvmValue*)pData;

	Show_StaticString(pData, nRow, 0, pValue->m_strID);

	nRow++;
}

QResultExprDlg_Dataset::QResultExprDlg_Dataset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QResultExprDlg_Dataset)
{
    ui->setupUi(this);
	m_pCurSelValue = NULL;
	m_pReportGrid = new QResultExprDlg_DatasetGrid(this);
	ui->m_layoutGrid->addWidget(m_pReportGrid);
	m_pReportGrid->InitGrid();
	InitLanguage();

	connect(ui->m_btnOK, SIGNAL(clicked(bool)), this, SLOT(slot_btnOK_Clicked(bool)));
	connect(ui->m_btnCancel, SIGNAL(clicked(bool)), this, SLOT(slot_btnCancel_Clicked(bool)));
}

QResultExprDlg_Dataset::~QResultExprDlg_Dataset()
{
    delete ui;
}

void QResultExprDlg_Dataset::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->m_btnOK,g_sLangTxt_OK,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnCancel,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);
}

void QResultExprDlg_Dataset::ShowDatas(CExBaseList* pList)
{
	m_pReportGrid->ShowDatas(pList);
}

void QResultExprDlg_Dataset::slot_btnOK_Clicked(bool bCheck)
{
	m_pCurSelValue = (CDvmValue*)m_pReportGrid->GetCurrSelData();
	accept();
}	

void QResultExprDlg_Dataset::slot_btnCancel_Clicked(bool bCheck)
{
	reject();
}