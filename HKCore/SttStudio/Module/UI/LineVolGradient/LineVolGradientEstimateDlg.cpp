#include "LineVolGradientEstimateDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>
#include "../../XLangResource_Native.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../XLangResource_Native.h"
LineVolGradientEstimateGrid::LineVolGradientEstimateGrid(int rows, int columns, QWidget* parent) : QTableWidget(rows, columns, parent)
{

}

LineVolGradientEstimateGrid::~LineVolGradientEstimateGrid()
{

}

void LineVolGradientEstimateGrid::InitGrid()
{
	CString strName, strErrorType, strRelError, strAbsError, strSettingValue;
	xlang_GetLangStrByFile(strName, "sName");
	xlang_GetLangStrByFile(strErrorType, "StateEstimate_ErrorType");
	//strErrorType = "误差类型";
	strRelError = g_sLangTxt_StateEstimate_RelError;
	strRelError += "(%)";
	//strRelError = "相对误差(%)";
	//strAbsError = "绝对误差";
	//strSettingValue = "整定值";
	xlang_GetLangStrByFile(strAbsError, "StateEstimate_AbsError");
	xlang_GetLangStrByFile(strSettingValue, "sSetValue");

	setHorizontalHeaderLabels(QStringList() << strName << strErrorType << strRelError << strAbsError << strSettingValue);
	setColumnWidth(0, 120);
	setColumnWidth(1, 150);
	setColumnWidth(4, 80);
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
}

void LineVolGradientEstimateGrid::EnableRow(long nIndex, BOOL bEnabled)
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

QComboBox* LineVolGradientEstimateGrid::NewErrorType()
{
	CString strText;

	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"相对误差"*/g_sLangTxt_StateEstimate_RelError);

	strText = g_sLangTxt_StateEstimate_AbsError +"or"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"相对误差or绝对误差"*/strText);

	strText = g_sLangTxt_StateEstimate_AbsError +"&"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"相对误差&绝对误差"*/strText);
	//pCbbError->addItem("组合误差");
	return pCbbError;
}

QComboBox* LineVolGradientEstimateGrid::AbsErrorType()
{
	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
	return pCbbError;
}

void LineVolGradientEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
// 	QLineEdit *pLineEdit = new QLineEdit();
// 	pLineEdit->setReadOnly(true); 
// 	pLineEdit->setAlignment(Qt::AlignCenter);
// 	pCombox->setLineEdit(pLineEdit);
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);

}

void LineVolGradientEstimateGrid::CbbErrorType(int nIndex, CString strText)
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

void LineVolGradientEstimateGrid::slot_OnCellChanged(int row,int col)
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
	float fv = str.toFloat();

	if (col == 1)
	{
		pItem->setText(str);
	}

	if(col == 2)//相对误差
	{
		fv = setLimit(0,100,fv);
		pItem->setText(QString::number(fv));
	}

	if(col == 3)//绝对误差
	{
		fv = setLimit(0,200,fv);
		pItem->setText(QString::number(fv));
	}

	if (col == 4)
	{
		if (row == 0)
		{
			fv = setLimit(0, 120, fv);
			pItem->setText(QString::number(fv));
		}
		if (row == 1)
		{
			fv=setLimit(0,10,fv);
			pItem->setText(QString::number(fv));
		}
		if (row == 2)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));
		}
	}
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void LineVolGradientEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	int nRow = currentRow();
	CbbErrorType(nRow,strText);
}

void LineVolGradientEstimateGrid::InitData(tmt_LineVolGradientParasEx* pParas)
{
	QComboBox *pCbbError1 = NewErrorType();
	pCbbError1->setCurrentIndex(pParas->m_nUActVal_ErrorLogic);
	QComboBox *pCbbError2 = NewErrorType();
	pCbbError2->setCurrentIndex(pParas->m_nIActVal_ErrorLogic);

	CString strText =/* "电压动作值(V)"*/g_sLangTxt_Gradient_VActionValue;
	setItem(0, 0, new QTableWidgetItem(strText));
	strText = /*"电流动作值(A)"*/g_sLangTxt_Gradient_CActionValue;
	setItem(1, 0, new QTableWidgetItem(strText));

	setCellWidget(0, 1, pCbbError1);
	setCellWidget(1, 1, pCbbError2);
	
	ComboxModelStyle(pCbbError1);
	ComboxModelStyle(pCbbError2);

	setItem(0, 2, new QTableWidgetItem(QString::number(pParas->m_fUActVal_RelErr)));
	setItem(1, 2, new QTableWidgetItem(QString::number(pParas->m_fIActVal_RelErr)));

	setItem(0, 3, new QTableWidgetItem(QString::number(pParas->m_fUActVal_AbsErr)));
	setItem(1, 3, new QTableWidgetItem(QString::number(pParas->m_fIActVal_AbsErr)));

	setItem(0, 4, new QTableWidgetItem(QString::number(pParas->m_fUSet)));
	setItem(1, 4, new QTableWidgetItem(QString::number(pParas->m_fISet)));

	for (int i = 0 ;i < 5 ;i++)
	{
		if (i != 1)
		{
			item(0,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(1,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		}

	}
	for (int i = 0; i < 2; i++)
	{
		item(i, 0)->setFlags(item(i, 0)->flags() & ~Qt::ItemIsEditable);
		EnableRow(i, FALSE);
	}

	if(pParas->m_nType == 0)
	{
		//幅值
		if(pParas->m_nTestMode == 0)
		{
			//动作值
			if(pParas->m_nVarIndexType == 0)
			{
				//电流
				EnableRow(1);
			}
			else if(pParas->m_nVarIndexType == 1)
			{
				//电压
				EnableRow(0);
			}
		}
	
	}
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(pCbbError1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	CbbErrorType(0,pCbbError1->currentText());
	CbbErrorType(1,pCbbError2->currentText());
}

LineVolGradientEstimateDlg::LineVolGradientEstimateDlg(tmt_LineVolGradientParasEx* pParas, QWidget* parent) : QDialog(parent)
{
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
}

LineVolGradientEstimateDlg::~LineVolGradientEstimateDlg()
{

}

void LineVolGradientEstimateDlg::InitUI()
{
	CString strTitle = /*"结果评估"*/g_sLangTxt_StateEstimate_ResultEstimate;
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new LineVolGradientEstimateGrid(2, 5, this);
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

void LineVolGradientEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->m_fUActVal_RelErr = m_pGrid->item(0, 2)->text().toFloat();
	m_pParas->m_fIActVal_RelErr = m_pGrid->item(1, 2)->text().toFloat();
	m_pParas->m_fUActVal_AbsErr = m_pGrid->item(0, 3)->text().toFloat();
	m_pParas->m_fIActVal_AbsErr = m_pGrid->item(1, 3)->text().toFloat();
	m_pParas->m_nUActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(0, 1))->currentIndex();
	m_pParas->m_nIActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(1, 1))->currentIndex();
	m_pParas->m_fUSet = m_pGrid->item(0, 4)->text().toFloat();
	m_pParas->m_fISet = m_pGrid->item(1, 4)->text().toFloat();
	accept();
}

void LineVolGradientEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}
