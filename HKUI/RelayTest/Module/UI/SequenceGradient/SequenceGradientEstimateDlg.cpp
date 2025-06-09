#include "SequenceGradientEstimateDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>
#include "../../XLangResource_Native.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Controls/SettingCtrls/QSettingItem.h"
#include <QApplication>
#include "../SttTestCntrFrameBase.h"

#ifdef _PSX_QT_WINDOWS_	
//#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
//#include "../SttTestCntrFrameBase.h"
#endif

#define  SEQGRADIENTGRID_COL_NAME			0		//名称
#define  SEQGRADIENTGRID_COL_SETVALUE		1		//整定值
#define  SEQGRADIENTGRID_COL_ERRORTYPE		2		//误差类型
#define  SEQGRADIENTGRID_COL_RELERROR		3		//相对误差
#define  SEQGRADIENTGRID_COL_ABSERROR		4		//绝对误差

SequenceGradientEstimateGrid::SequenceGradientEstimateGrid(int rows, int columns, QWidget* parent) : QScrollTableWidget( parent)
{
	setRowCount(rows);
	setColumnCount(columns);

	m_bRunning = FALSE;
	installEventFilter(this);
}

SequenceGradientEstimateGrid::~SequenceGradientEstimateGrid()
{

}

void SequenceGradientEstimateGrid::InitGrid()
{
	CString strName, strErrorType, strRelError, strAbsError, strSettingValue;
	xlang_GetLangStrByFile(strName, "sName");//名称
	xlang_GetLangStrByFile(strErrorType, "StateEstimate_ErrorType");//误差类型
	strRelError = g_sLangTxt_StateEstimate_RelError;//strRelError = "相对误差(%)"
	strRelError += "(%)";
	xlang_GetLangStrByFile(strAbsError, "StateEstimate_AbsError");//strAbsError = "绝对误差"
	xlang_GetLangStrByFile(strSettingValue, "State_SettingValue");//strSettingValue = "整定值"

	setHorizontalHeaderLabels(QStringList() << strName << strSettingValue << strErrorType << strRelError << strAbsError);
    //setColumnWidth(0, 120);
    //setColumnWidth(1, 150);
    //setColumnWidth(4, 80);
    // 设置列宽策略为自适应
    //this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
	this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
}

void SequenceGradientEstimateGrid::EnableRow(long nIndex, BOOL bEnabled)
{
	if(nIndex >= rowCount())
	{
		return;
	}

	QComboBox* pCbb = (QComboBox*)cellWidget(nIndex, SEQGRADIENTGRID_COL_ERRORTYPE);
	pCbb->setEnabled(bEnabled);
	if(bEnabled)
	{
// 		QTableWidgetItem* pItem = pItem = item(nIndex, SEQGRADIENTGRID_COL_RELERROR);
// 		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
// 		pItem = item(nIndex, SEQGRADIENTGRID_COL_ABSERROR);
// 		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);

		SetItemEnable(nIndex, SEQGRADIENTGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, SEQGRADIENTGRID_COL_ABSERROR, TRUE);
	}
	else
	{
// 		QTableWidgetItem* pItem = pItem = item(nIndex, SEQGRADIENTGRID_COL_RELERROR);
// 		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
// 		pItem = item(nIndex, SEQGRADIENTGRID_COL_ABSERROR);
// 		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);

		SetItemEnable(nIndex, SEQGRADIENTGRID_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, SEQGRADIENTGRID_COL_ABSERROR, FALSE);
	}

}
void SequenceGradientEstimateGrid::InitData(tmt_GradientParasEx* pParas)
{
	m_pParas=pParas;
	QComboBox *pCbbError1 = NewErrorType();
// 	pCbbError1->setCurrentIndex(pParas->m_nUActVal_ErrorLogic);
	QComboBox *pCbbError2 = NewErrorType();
//	pCbbError2->setCurrentIndex(pParas->m_nIActVal_ErrorLogic);

	if (pParas->m_nUActVal_ErrorLogic == 5)
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbError1->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError1,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
		pCbbError1->setCurrentIndex(pParas->m_nUActVal_ErrorLogic);
	}

	if (pParas->m_nIActVal_ErrorLogic == 5)
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbError2->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError2,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
		pCbbError2->setCurrentIndex(pParas->m_nIActVal_ErrorLogic);
	}


	CString strText; 
	//strText = "电压动作值(V)";
	strText = g_sLangTxt_Gradient_VActionValue;//lcq
	setItem(0, SEQGRADIENTGRID_COL_NAME, new QTableWidgetItem(strText));
	//strText = "电流动作值(A)";
	strText = g_sLangTxt_Gradient_CActionValue;
	setItem(1, SEQGRADIENTGRID_COL_NAME, new QTableWidgetItem(strText));
	
	setCellWidget(0, SEQGRADIENTGRID_COL_ERRORTYPE, pCbbError1);//将pCbbError添加到0行1列(误差类型)
	setCellWidget(1, SEQGRADIENTGRID_COL_ERRORTYPE, pCbbError2);

	ComboxModelStyle(pCbbError1);
	ComboxModelStyle(pCbbError2);


// 	setItem(0, SEQGRADIENTGRID_COL_RELERROR, new QTableWidgetItem(QString::number(pParas->m_fUActVal_RelErr)));
// 	setItem(1, SEQGRADIENTGRID_COL_RELERROR, new QTableWidgetItem(QString::number(pParas->m_fIActVal_RelErr)));
// 
// 	setItem(0, SEQGRADIENTGRID_COL_ABSERROR, new QTableWidgetItem(QString::number(pParas->m_fUActVal_AbsErr)));
// 	setItem(1, SEQGRADIENTGRID_COL_ABSERROR, new QTableWidgetItem(QString::number(pParas->m_fIActVal_AbsErr)));
// 
// 	setItem(0, SEQGRADIENTGRID_COL_SETVALUE, new QTableWidgetItem(QString::number(pParas->m_fUSet)));
// 	setItem(1, SEQGRADIENTGRID_COL_SETVALUE, new QTableWidgetItem(QString::number(pParas->m_fISet)));

	setItem(0, SEQGRADIENTGRID_COL_RELERROR, new QSettingItem(this));
	((QSettingItem*)item(0, SEQGRADIENTGRID_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_RelErr));
	setItem(1, SEQGRADIENTGRID_COL_RELERROR, new QSettingItem(this));
	((QSettingItem*)item(1, SEQGRADIENTGRID_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_RelErr));

	setItem(0, SEQGRADIENTGRID_COL_ABSERROR, new QSettingItem(this));
	((QSettingItem*)item(0, SEQGRADIENTGRID_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_AbsErr));
	setItem(1, SEQGRADIENTGRID_COL_ABSERROR, new QSettingItem(this));
	((QSettingItem*)item(1, SEQGRADIENTGRID_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_AbsErr));

	setItem(0, SEQGRADIENTGRID_COL_SETVALUE, new QSettingItem(this));
	((QSettingItem*)item(0, SEQGRADIENTGRID_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fUSet));
	setItem(1, SEQGRADIENTGRID_COL_SETVALUE, new QSettingItem(this));
	((QSettingItem*)item(1, SEQGRADIENTGRID_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fISet));

	for (int i = 0 ;i < 5 ;i++)
	{
		if (i != SEQGRADIENTGRID_COL_ERRORTYPE)
		{
			item(0,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(1,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		}

	}
	for (int i = 0; i < 2; i++)
	{
		item(i, SEQGRADIENTGRID_COL_NAME)->setFlags(item(i, SEQGRADIENTGRID_COL_NAME)->flags() & ~Qt::ItemIsEditable);
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
				//电压
				EnableRow(1);
			}
			else if(pParas->m_nVarIndexType == 1)
			{
				//电流
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

QComboBox* SequenceGradientEstimateGrid::NewErrorType()
{
	CString strText;

	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"相对误差"*/g_sLangTxt_StateEstimate_RelError);

	strText = g_sLangTxt_StateEstimate_AbsError +"or"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"相对误差or绝对误差"*/strText);

	strText = g_sLangTxt_StateEstimate_AbsError +"&"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"相对误差&绝对误差"*/strText);
	pCbbError->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
	return pCbbError;

}

QComboBox* SequenceGradientEstimateGrid::AbsErrorType()
{
	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
	return pCbbError;
}

void SequenceGradientEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void SequenceGradientEstimateGrid::CbbErrorType(int nIndex, CString strText)
{
	if (strText==g_sLangTxt_StateEstimate_AbsError)//绝对误差
	{
		SetItemEnable(nIndex, SEQGRADIENTGRID_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, SEQGRADIENTGRID_COL_ABSERROR, TRUE);
	}
	else if (strText==g_sLangTxt_StateEstimate_RelError)//相对误差
	{
// 		item(nIndex, SEQGRADIENTGRID_COL_RELERROR)->setFlags(item(nIndex, SEQGRADIENTGRID_COL_RELERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
// 		item(nIndex, SEQGRADIENTGRID_COL_ABSERROR)->setFlags(item(nIndex, SEQGRADIENTGRID_COL_ABSERROR)->flags() & ~Qt::ItemIsEditable);
		SetItemEnable(nIndex, SEQGRADIENTGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, SEQGRADIENTGRID_COL_ABSERROR, FALSE);
	}
	else if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		SetItemEnable(nIndex, SEQGRADIENTGRID_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, SEQGRADIENTGRID_COL_ABSERROR, FALSE);
	}
	else
	{
// 		item(nIndex, SEQGRADIENTGRID_COL_RELERROR)->setFlags(item(nIndex, SEQGRADIENTGRID_COL_RELERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
// 		item(nIndex, SEQGRADIENTGRID_COL_ABSERROR)->setFlags(item(nIndex, SEQGRADIENTGRID_COL_ABSERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		SetItemEnable(nIndex, SEQGRADIENTGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, SEQGRADIENTGRID_COL_ABSERROR, TRUE);
	}

}

void SequenceGradientEstimateGrid::SetItemEnable(int nRow, int nCol, BOOL bEnable)
{
	QTableWidgetItem *pItem = item(nRow, nCol);
	if (!pItem)
	{
		return;
	}

	bool bCbbState = true;
	if (nCol == SEQGRADIENTGRID_COL_RELERROR || nCol ==SEQGRADIENTGRID_COL_ABSERROR )
	{
		QComboBox* pCbb = (QComboBox*)cellWidget(nRow, SEQGRADIENTGRID_COL_ERRORTYPE);
		if (pCbb)
		{
			bCbbState = pCbb->isEnabled();
		}		
		
		if (bCbbState == FALSE)
		{
			bEnable = bCbbState;
		}
	}

	pItem->setFlags(bEnable ? pItem->flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable
		: pItem->flags() & ~Qt::ItemIsEditable &~Qt::ItemIsEnabled &~Qt::ItemIsSelectable);


	if (bCbbState && bEnable)
	{
		pItem->setForeground(Qt::black);  // 黑色背景
	}
	else
	{
		pItem->setForeground(Qt::gray);  // 灰色背景
	}
}

bool SequenceGradientEstimateGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return true;
	}

	return QTableWidget::eventFilter(obj, event);
}

void SequenceGradientEstimateGrid::mousePressEvent(QMouseEvent *event)
{
	if (m_bRunning)
	{
		QTableWidget::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick, event->pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QApplication::postEvent(this, pEvent);
	QTableWidget::mousePressEvent(event);
}

void SequenceGradientEstimateGrid::slot_OnCellChanged(int row,int col)
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

	if (col == SEQGRADIENTGRID_COL_ERRORTYPE)
	{
		pItem->setText(str);
	}

	if(col == SEQGRADIENTGRID_COL_RELERROR)//相对误差
	{
		fv = setLimit(0,100,fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if(col == SEQGRADIENTGRID_COL_ABSERROR)//绝对误差
	{
		fv = setLimit(0,200,fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if (col == SEQGRADIENTGRID_COL_SETVALUE)
	{
		if (row == 0)
		{
			fv = setLimit(0, 120, fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		if (row == 1)
		{
			fv=setLimit(0,10,fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		if (row == 2)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
	}
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void SequenceGradientEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	QComboBox* pCbb = (QComboBox*)sender();
	int nRow = rowAt(pCbb->pos().y());

	CbbErrorType(nRow,strText);
}
extern void  Stt_Global_SettingParent(QWidget *parent);

SequenceGradientEstimateDlg::SequenceGradientEstimateDlg(tmt_GradientParasEx* pParas, QWidget* parent)
	:QDialog(parent)
{
	Stt_Global_SettingParent(this);	
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
	
}

SequenceGradientEstimateDlg::~SequenceGradientEstimateDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
}

void SequenceGradientEstimateDlg::InitUI()
{
	CString strTitle = g_sLangTxt_StateEstimate_ResultEstimate;//结果评估
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new SequenceGradientEstimateGrid(2, 5, this);
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
	//resize(600, 400);

#ifdef _PSX_QT_WINDOWS_	
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect rect = desktopWidget->screenGeometry();
	float fWidth = rect.width() * g_dUIShowCoef;

	if (fWidth >= 2880)
	{
		resize(1000, 750);
	}
	else if (fWidth >= 2280)
	{
		resize(800, 450);
	}
	else
	{
	resize(600, 400);
	}
#else
	resize(600, 400);
#endif // _PSX_QT_WINDOWS_

}

void SequenceGradientEstimateDlg::slot_btnOK_Clicked()
{
// 	m_pParas->m_fUActVal_RelErr = m_pGrid->item(0, SEQGRADIENTGRID_COL_RELERROR)->text().toFloat();
// 	m_pParas->m_fIActVal_RelErr = m_pGrid->item(1, SEQGRADIENTGRID_COL_RELERROR)->text().toFloat();
// 	m_pParas->m_fUActVal_AbsErr = m_pGrid->item(0, SEQGRADIENTGRID_COL_ABSERROR)->text().toFloat();
// 	m_pParas->m_fIActVal_AbsErr = m_pGrid->item(1, SEQGRADIENTGRID_COL_ABSERROR)->text().toFloat();

	if (!((QSettingItem*)m_pGrid->item(0, SEQGRADIENTGRID_COL_RELERROR))->IsSetting())
	m_pParas->m_fUActVal_RelErr = m_pGrid->item(0, SEQGRADIENTGRID_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, SEQGRADIENTGRID_COL_RELERROR))->IsSetting())
	m_pParas->m_fIActVal_RelErr = m_pGrid->item(1, SEQGRADIENTGRID_COL_RELERROR)->text().toFloat();

	if (!((QSettingItem*)m_pGrid->item(0, SEQGRADIENTGRID_COL_ABSERROR))->IsSetting())
	m_pParas->m_fUActVal_AbsErr = m_pGrid->item(0, SEQGRADIENTGRID_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, SEQGRADIENTGRID_COL_ABSERROR))->IsSetting())
	m_pParas->m_fIActVal_AbsErr = m_pGrid->item(1, SEQGRADIENTGRID_COL_ABSERROR)->text().toFloat();


	CString strText;
	strText = ((QComboBox*)m_pGrid->cellWidget(0, SEQGRADIENTGRID_COL_ERRORTYPE))->currentText();
	if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		m_pParas->m_nUActVal_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nUActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(0, SEQGRADIENTGRID_COL_ERRORTYPE))->currentIndex();
	}

	strText = ((QComboBox*)m_pGrid->cellWidget(1, SEQGRADIENTGRID_COL_ERRORTYPE))->currentText();
	if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		m_pParas->m_nIActVal_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nIActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(1, SEQGRADIENTGRID_COL_ERRORTYPE))->currentIndex();
	}

// 	m_pParas->m_nUActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(0, SEQGRADIENTGRID_COL_ERRORTYPE))->currentIndex();
// 	m_pParas->m_nIActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(1, SEQGRADIENTGRID_COL_ERRORTYPE))->currentIndex();
	
// 	m_pParas->m_fUSet = m_pGrid->item(0, SEQGRADIENTGRID_COL_SETVALUE)->text().toFloat();
// 	m_pParas->m_fISet = m_pGrid->item(1, SEQGRADIENTGRID_COL_SETVALUE)->text().toFloat();

	if (!((QSettingItem*)m_pGrid->item(0, SEQGRADIENTGRID_COL_SETVALUE))->IsSetting())
	m_pParas->m_fUSet = m_pGrid->item(0, SEQGRADIENTGRID_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, SEQGRADIENTGRID_COL_SETVALUE))->IsSetting())
	m_pParas->m_fISet = m_pGrid->item(1, SEQGRADIENTGRID_COL_SETVALUE)->text().toFloat();

	
	accept();
}

void SequenceGradientEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}

