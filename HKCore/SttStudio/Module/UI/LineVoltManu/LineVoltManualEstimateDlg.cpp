#include "LineVoltManualEstimateDlg.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "SttMacroParaEditViewLineVoltManu.h"
#include "../../XLangResource_Native.h"

LineVoltEstimateGrid::LineVoltEstimateGrid(int rows, int columns, QWidget* parent) : QTableWidget(rows, columns, parent)
{
	m_bRunning = FALSE;
	installEventFilter(this);
}

LineVoltEstimateGrid::~LineVoltEstimateGrid()
{

}

void LineVoltEstimateGrid::InitGrid()
{
	CString strName, strErrorType, strRelError, strAbsError, strSettingValue;
	xlang_GetLangStrByFile(strName, "sName");//名称
	xlang_GetLangStrByFile(strErrorType, "StateEstimate_ErrorType");//误差类型
	strRelError = g_sLangTxt_StateEstimate_RelError;//相对误差(%)
	strRelError += "(%)";
	xlang_GetLangStrByFile(strAbsError, "StateEstimate_AbsError");//绝对误差
	xlang_GetLangStrByFile(strSettingValue, "sSetValue");//整定值

	setHorizontalHeaderLabels(QStringList() << strName << strErrorType << strRelError << strAbsError << strSettingValue);
	setColumnWidth(0, 120);
	setColumnWidth(1, 150);
	setColumnWidth(4, 80);
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); 
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
}

QComboBox* LineVoltEstimateGrid::NewErrorType()
{
	CString strText;

	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(g_sLangTxt_StateEstimate_RelError);

	strText = g_sLangTxt_StateEstimate_AbsError +"or"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(strText);

	strText = g_sLangTxt_StateEstimate_AbsError +"&"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(strText);

	pCbbError->addItem(g_sLangTxt_StateEstimate_CombinationError);

	return pCbbError;
}

QComboBox* LineVoltEstimateGrid::AbsErrorType()
{
	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(g_sLangTxt_StateEstimate_AbsError);
	return pCbbError;
}

void LineVoltEstimateGrid::EnableRow(long nIndex, BOOL bEnabled)
{
	if(nIndex >= rowCount())
	{
		return;
	}

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

void LineVoltEstimateGrid::InitData(tmt_LinevoltManuParas* pParas)
{
	m_pParas=pParas;
	CString strText; 
	strText = /* "动作时间(s)" */g_sLangTxt_Native_ActionTime;
	setItem(0, 0, new QTableWidgetItem(strText));
	strText = /* "电压动作值V)" */g_sLangTxt_Gradient_VActionValue;
	setItem(1, 0, new QTableWidgetItem(strText));
	strText = /* "电流动作值(A)" */g_sLangTxt_Gradient_CActionValue;
	setItem(2, 0, new QTableWidgetItem(strText));


	QComboBox *pCbbError1 = NewErrorType();
	pCbbError1->setCurrentIndex(pParas->m_nTimeValue_ErrorLogic);
	QComboBox *pCbbError2 = NewErrorType();
	pCbbError2->setCurrentIndex(pParas->m_nUActVal_ErrorLogic);
	QComboBox *pCbbError3 = NewErrorType();
	pCbbError3->setCurrentIndex(pParas->m_nIActVal_ErrorLogic);

	setCellWidget(0, 1, pCbbError1);
	setCellWidget(1, 1, pCbbError2);
	setCellWidget(2, 1, pCbbError3);

	ComboxModelStyle(pCbbError1);
	ComboxModelStyle(pCbbError2);
	ComboxModelStyle(pCbbError3);

	setItem(0, 2, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_RelErr)));
	setItem(1, 2, new QTableWidgetItem(QString::number(pParas->m_fUActVal_RelErr)));
	setItem(2, 2, new QTableWidgetItem(QString::number(pParas->m_fIActVal_RelErr)));

	setItem(0, 3, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_AbsErr)));
	setItem(1, 3, new QTableWidgetItem(QString::number(pParas->m_fUActVal_AbsErr)));
	setItem(2, 3, new QTableWidgetItem(QString::number(pParas->m_fIActVal_AbsErr)));

	setItem(0, 4, new QTableWidgetItem(QString::number(pParas->m_fTimeSet)));
	setItem(1, 4, new QTableWidgetItem(QString::number(pParas->m_fUSet)));
	setItem(2, 4, new QTableWidgetItem(QString::number(pParas->m_fISet)));

	for (int i = 0 ;i < 3 ;i++)
	{
		if (i != 1)
		{
			item(0,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(1,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(2,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);	
		}
	}

	for (int i = 0;i < 3; i++)
	{
		item(i, 0)->setFlags(item(i, 0)->flags() & ~Qt::ItemIsEditable);
		EnableRow(i, FALSE);
	}

	if (pParas->m_bAuto)//自动递变方式时，开放动作值、返回系数、相位动作值
	{
		if(pParas->m_nGradientTpSelect==0)//幅值
		{
			if (g_pLinevoltManuTest->m_pLinevoltManualWidget->m_nChanneType== 0)		
			{
				EnableRow(1);//电压
			}
			else if (g_pLinevoltManuTest->m_pLinevoltManualWidget->m_nChanneType== 1)
			{
				EnableRow(2);//电流
			}
		}
	}
	EnableRow(0);

	CbbErrorType(0,pCbbError1->currentText());
	CbbErrorType(1,pCbbError2->currentText());
	CbbErrorType(2,pCbbError3->currentText());

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(pCbbError1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));

}

void LineVoltEstimateGrid::CbbErrorType(int nIndex, CString strText)
{
	if (strText==g_sLangTxt_StateEstimate_AbsError)//绝对误差
	{
		item(nIndex, 2)->setFlags(item(nIndex, 2)->flags() & ~Qt::ItemIsEditable);
		item(nIndex, 3)->setFlags(item(nIndex, 3)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
	}
	else if (strText==g_sLangTxt_StateEstimate_RelError)//相对误差
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

void LineVoltEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void LineVoltEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	int nRow = currentRow();

	CbbErrorType(nRow,strText);
}

void LineVoltEstimateGrid::slot_OnCellChanged(int row,int col)
{
	if (row  <  0)
	{
		return;
	}

	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));

	QTableWidgetItem  *pItem  = this->item(row,col);

	if (pItem == NULL)
	{
		return;
	} 

	QString str = pItem->text();
	float fv =str.toFloat();

	if(col==2)//相对误差
	{
		fv=setLimit(0,100,fv);
		pItem->setText(QString::number(fv));
	}

	if(col==3)//绝对误差
	{
		fv=setLimit(0,200,fv);
		pItem->setText(QString::number(fv));	
	}

	if(col==4)//整定值
	{
		if (row==0)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==1)
		{
			fv=setLimit(0,120,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==2)
		{
			fv=setLimit(0,10,fv);
			pItem->setText(QString::number(fv));
		}	
		
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}


bool LineVoltEstimateGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return true;
	}

	return QTableWidget::eventFilter(obj,event);
}

void LineVoltEstimateGrid::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QTableWidget::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QTableWidget::mousePressEvent(event);
}

LineVoltManualEstimateDlg::LineVoltManualEstimateDlg(tmt_LinevoltManuParas* pParas, QWidget* parent) : QDialog(parent)
{
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
}

LineVoltManualEstimateDlg::~LineVoltManualEstimateDlg()
{

}

void LineVoltManualEstimateDlg::InitUI()
{
	CString strTitle = g_sLangTxt_StateEstimate_ResultEstimate; 
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new LineVoltEstimateGrid(3, 5, this);
	m_pGrid->InitGrid();
	m_pGrid->InitData(m_pParas);
	pHLayout->addWidget(m_pGrid);
	pVLayout->addLayout(pHLayout);

	CString strText;
	pHLayout = new QHBoxLayout(this);
	pHLayout->addStretch();
	QPushButton* pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sOK");
	pBtn->setText(strText);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	pHLayout->addWidget(pBtn);
	pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sCancel");
	pBtn->setText(strText);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
	pHLayout->addWidget(pBtn);
	pHLayout->addStretch();
	pVLayout->addLayout(pHLayout);

	resize(600, 400);
}

void LineVoltManualEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->m_fTimeValue_RelErr = m_pGrid->item(0, 2)->text().toFloat();
	m_pParas->m_fUActVal_RelErr = m_pGrid->item(1, 2)->text().toFloat();
	m_pParas->m_fIActVal_RelErr = m_pGrid->item(2, 2)->text().toFloat();

	m_pParas->m_fTimeValue_AbsErr = m_pGrid->item(0, 3)->text().toFloat();
	m_pParas->m_fUActVal_AbsErr = m_pGrid->item(1, 3)->text().toFloat();
	m_pParas->m_fIActVal_AbsErr = m_pGrid->item(2, 3)->text().toFloat();

	m_pParas->m_nTimeValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(0, 1))->currentIndex();
	m_pParas->m_nUActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(1, 1))->currentIndex();
	m_pParas->m_nIActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(2, 1))->currentIndex();

	m_pParas->m_fTimeSet = m_pGrid->item(0, 4)->text().toFloat();
	m_pParas->m_fUSet = m_pGrid->item(1, 4)->text().toFloat();
	m_pParas->m_fISet = m_pGrid->item(2, 4)->text().toFloat();

	accept();
}

void LineVoltManualEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}