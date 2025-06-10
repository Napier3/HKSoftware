#include "FaultGradientEstimateDlg.h"
#include "ui_FaultGradientEstimateDlg.h"
#include "../../XLangResource_Native.h"
#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"

#include <QHeaderView>

QFaultGradientEstimateGrid::QFaultGradientEstimateGrid(QWidget *parent):QTableWidget(parent)
{
}

QFaultGradientEstimateGrid::~QFaultGradientEstimateGrid()
{
}

void QFaultGradientEstimateGrid::InitGrid()
{
	//����tab ����
	QStringList lstTabCol;
	lstTabCol << "����" << "�������" << "������(%)" << "�������" << "����ֵ";
	setRowCount(FG_EstimateRow);
	setColumnCount(FG_EstimateCol);
	this->setHorizontalHeaderLabels(lstTabCol);

	setColumnWidth(0, 150);
	setColumnWidth(1, 150);
	setColumnWidth(4, 120);
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //���ñ�ͷ����ɫ
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
}

void QFaultGradientEstimateGrid::EnableRow(long nIndex, BOOL bEnabled)
{
	if(nIndex >= rowCount()) return;

	QComboBox* pCbb = (QComboBox*)cellWidget(nIndex, 1);
	pCbb->setEnabled(bEnabled);
	if(bEnabled)
	{
		QTableWidgetItem* pItem = pItem = item(nIndex, 2);
		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
		pItem = item(nIndex, 3);
		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
	}
	else
	{
		QTableWidgetItem* pItem = pItem = item(nIndex, 2);
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
		pItem = item(nIndex, 3);
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
	}
}

QComboBox* QFaultGradientEstimateGrid::NewErrorType()
{
	CString strText;
	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(/*"�������"*/g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"������"*/g_sLangTxt_StateEstimate_RelError);

	strText = g_sLangTxt_StateEstimate_AbsError +"or"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"������or�������"*/strText);

	strText = g_sLangTxt_StateEstimate_AbsError +"&"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"������&�������"*/strText);
	return pCbbError;
}

QComboBox* QFaultGradientEstimateGrid::AbsErrorType()
{
	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(/*"�������"*/g_sLangTxt_StateEstimate_AbsError);
	return pCbbError;
}

void QFaultGradientEstimateGrid::addTabRow(int nRow,QString strValue,int nComType,long l1Value,float f2Value,float f3Value,float f4Value)
{
	setItem(nRow, 0, new QTableWidgetItem(strValue));
	item(nRow, 0)->setFlags((item(nRow, 0)->flags()) & ~Qt::ItemIsEditable);
	item(nRow,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	QComboBox *pCbbErrorType = NULL;
	if(nComType == 0)
	{
		pCbbErrorType = NewErrorType();
	}
	else if(nComType == 1)
	{
		pCbbErrorType = AbsErrorType();
	}
	SetTabComboxModelStyle(pCbbErrorType);
	setCellWidget(nRow, 1, pCbbErrorType);
	pCbbErrorType->setCurrentIndex(l1Value);

	setItem(nRow, 2, new QTableWidgetItem(QString::number(f2Value)));
	item(nRow,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	setItem(nRow, 3, new QTableWidgetItem(QString::number(f3Value)));
	item(nRow,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	setItem(nRow, 4, new QTableWidgetItem(QString::number(f4Value)));
	item(nRow,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	EnableRow(nRow, FALSE);
	
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	connect(pCbbErrorType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	CbbErrorType(nRow,pCbbErrorType->currentText());
}

void QFaultGradientEstimateGrid::SetTabComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void QFaultGradientEstimateGrid::CbbErrorType(int nIndex, CString strText)
{
	if (strText==g_sLangTxt_StateEstimate_AbsError)//�������
	{
		item(nIndex, 2)->setFlags(item(nIndex, 2)->flags() & ~Qt::ItemIsEditable);
		item(nIndex, 3)->setFlags(item(nIndex, 3)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
	}
	else if (strText==g_sLangTxt_StateEstimate_RelError)//������
	{
		item(nIndex, 2)->setFlags(item(nIndex, 2)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		item(nIndex, 3)->setFlags(item(nIndex, 3)->flags() & ~Qt::ItemIsEditable);
	}
	else
	{
		item(nIndex, 2)->setFlags(item(nIndex, 2)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		item(nIndex, 3)->setFlags(item(nIndex, 3)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
	}
}

void QFaultGradientEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	int nRow = currentRow();
	CbbErrorType(nRow,strText);
}

void QFaultGradientEstimateGrid::slot_OnCellChanged(int row,int col)
{
	if (row  <  0) return;
	
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	QTableWidgetItem  *pItem  = this->item(row,col);
	if (pItem == NULL)
	{
		return;
	} 
	QString str = pItem->text();
	float fv =str.toFloat();
	//����ҵ�� ToDo

	//////////////////////////////
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}
/////////////////////////////////Dlg
CFaultGradientEstimateDlg::CFaultGradientEstimateDlg(tmt_fault_gradient_test* pPara,QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::CFaultGradientEstimateDlg();
	ui->setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	m_pCurFGTest = pPara;
	initUI();
}

CFaultGradientEstimateDlg::~CFaultGradientEstimateDlg()
{
	delete ui;
}

void CFaultGradientEstimateDlg::initUI()
{
	CString strTitle = g_sLangTxt_StateEstimate_ResultEstimate; //lcq
	setWindowTitle(strTitle);
	initTab();	
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void CFaultGradientEstimateDlg::initTab()
{
	ui->tableWidget->InitGrid();
	
	//����
	ui->tableWidget->addTabRow(0,"����1",1,0,3.2,3.2,10);
	ui->tableWidget->addTabRow(1,"����2",1,0,3.2,3.2,10);
	ui->tableWidget->addTabRow(2,"����3",1,0,3.2,3.2,10);

	InitData();
}

void CFaultGradientEstimateDlg::InitData()
{
	///ͨ����ҵ���� ToDo

}

void CFaultGradientEstimateDlg::slot_btnOK_Clicked()
{
	//��������ֵ ToDo

	accept();
}

void CFaultGradientEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}
