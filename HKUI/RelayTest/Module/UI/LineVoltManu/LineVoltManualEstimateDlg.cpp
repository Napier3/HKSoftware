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
// #include "../../XLangResource_Native.h"
#include <QApplication>
#include "../SttTestCntrFrameBase.h"

#ifdef _PSX_QT_WINDOWS_
//#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
//#include "../SttTestCntrFrameBase.h"
#endif

#define  LINEVOLTESTIMATEGRID_COL_NAME			0		//名称
#define  LINEVOLTESTIMATEGRID_COL_SETVALUE		1		//整定值
#define  LINEVOLTESTIMATEGRID_COL_ERRORTYPE		2		//误差类型
#define  LINEVOLTESTIMATEGRID_COL_RELERROR		3		//相对误差
#define  LINEVOLTESTIMATEGRID_COL_ABSERROR		4		//绝对误差
#define  LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR		5		//绝对误差(-)

LineVoltEstimateGrid::LineVoltEstimateGrid(int rows, int columns, QWidget* parent) : QScrollTableWidget(parent)	//QTableWidget(rows, columns, parent)//20240808 gongyiping
{
	//20240808 gongyiping
	setRowCount(rows);
	setColumnCount(columns);

	m_bRunning = FALSE;
	installEventFilter(this);
}

LineVoltEstimateGrid::~LineVoltEstimateGrid()
{

}

void LineVoltEstimateGrid::InitGrid()
{
	CString strName, strErrorType, strRelError, strAbsError, strSettingValue, strNegativeAbsError;
	xlang_GetLangStrByFile(strName, "sName");//名称
	xlang_GetLangStrByFile(strErrorType, "StateEstimate_ErrorType");//误差类型
	strRelError = g_sLangTxt_StateEstimate_RelError;//相对误差(%)
	strRelError += "(%)";
	xlang_GetLangStrByFile(strAbsError, "StateEstimate_AbsError");//绝对误差
	xlang_GetLangStrByFile(strSettingValue, "State_SettingValue");//整定值
	strNegativeAbsError = g_sLangTxt_StateEstimate_AbsError;
	strNegativeAbsError += "(-)";//绝对误差(-)

	setHorizontalHeaderLabels(QStringList() << strName << strSettingValue << strErrorType << strRelError << strAbsError << strNegativeAbsError);
//	setColumnWidth(0, 120);
//	setColumnWidth(1, 150);
//	setColumnWidth(4, 80);
    // 设置列宽策略为自适应
    //this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
	this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

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
	pCbbError->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
	return pCbbError;
}

QComboBox* LineVoltEstimateGrid::AbsErrorType()
{
	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(g_sLangTxt_StateEstimate_AbsError);	
	pCbbError->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
	return pCbbError;
}

void LineVoltEstimateGrid::EnableRow(long nIndex, BOOL bEnabled)
{
	if(nIndex >= rowCount())
	{
		return;
	}

	QComboBox* pCbb = (QComboBox*)cellWidget(nIndex, LINEVOLTESTIMATEGRID_COL_ERRORTYPE);
	pCbb->setEnabled(bEnabled);
	if(bEnabled)
	{
		QTableWidgetItem* pItem = pItem = item(nIndex, LINEVOLTESTIMATEGRID_COL_RELERROR);
		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
		pItem = item(nIndex, LINEVOLTESTIMATEGRID_COL_ABSERROR);
		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
	}
	else
	{
		QTableWidgetItem* pItem = pItem = item(nIndex, LINEVOLTESTIMATEGRID_COL_RELERROR);
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
		pItem = item(nIndex, LINEVOLTESTIMATEGRID_COL_ABSERROR);
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
	}
}

void LineVoltEstimateGrid::InitData(tmt_LinevoltManuParas* pParas)
{
	m_pParas=pParas;
	CString strText; 
	strText = /* "动作时间(s)" */g_sLangTxt_Native_ActionTime;
	setItem(0, LINEVOLTESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));
	strText = /* "电压动作值V)" */g_sLangTxt_Gradient_VActionValue;
	setItem(1, LINEVOLTESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));
	strText = /* "电流动作值(A)" */g_sLangTxt_Gradient_CActionValue;
	setItem(2, LINEVOLTESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));
	strText = /* "相位动作值(°) */g_sLangTxt_Gradient_PhaseAValue;
	setItem(3, LINEVOLTESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));

	QComboBox *pCbbError1 = NewErrorType();
	pCbbError1->setCurrentIndex(pParas->m_nTimeValue_ErrorLogic);
	QComboBox *pCbbError2 = NewErrorType();
	pCbbError2->setCurrentIndex(pParas->m_nUActVal_ErrorLogic);
	QComboBox *pCbbError3 = NewErrorType();
	pCbbError3->setCurrentIndex(pParas->m_nIActVal_ErrorLogic);
// 	QComboBox *pCbbError4 = AbsErrorType();
// 	pCbbError4->setCurrentIndex(pParas->m_nAngleActVal_ErrorLogic);

	QComboBox *pCbbError4 = AbsErrorType();
	if (pParas->m_nAngleActVal_ErrorLogic == 5)
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbError4->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError4,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
	pCbbError4->setCurrentIndex(pParas->m_nAngleActVal_ErrorLogic);
	}

	setCellWidget(0, LINEVOLTESTIMATEGRID_COL_ERRORTYPE, pCbbError1);
	setCellWidget(1, LINEVOLTESTIMATEGRID_COL_ERRORTYPE, pCbbError2);
	setCellWidget(2, LINEVOLTESTIMATEGRID_COL_ERRORTYPE, pCbbError3);
	setCellWidget(3, LINEVOLTESTIMATEGRID_COL_ERRORTYPE, pCbbError4);

	ComboxModelStyle(pCbbError1);
	ComboxModelStyle(pCbbError2);
	ComboxModelStyle(pCbbError3);
	ComboxModelStyle(pCbbError4);

	/*setItem(0, 2, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_RelErr)));
	setItem(1, 2, new QTableWidgetItem(QString::number(pParas->m_fUActVal_RelErr)));
	setItem(2, 2, new QTableWidgetItem(QString::number(pParas->m_fIActVal_RelErr)));

	setItem(0, 3, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_AbsErr)));
	setItem(1, 3, new QTableWidgetItem(QString::number(pParas->m_fUActVal_AbsErr)));
	setItem(2, 3, new QTableWidgetItem(QString::number(pParas->m_fIActVal_AbsErr)));

	setItem(0, 4, new QTableWidgetItem(QString::number(pParas->m_fTimeSet)));
	setItem(1, 4, new QTableWidgetItem(QString::number(pParas->m_fUSet)));
	setItem(2, 4, new QTableWidgetItem(QString::number(pParas->m_fISet)));*/

	//20240805 gongyiping
	//创建定值关联控件
	setItem(0, LINEVOLTESTIMATEGRID_COL_RELERROR, new QSettingItem(this));
	setItem(1, LINEVOLTESTIMATEGRID_COL_RELERROR, new QSettingItem(this));
	setItem(2, LINEVOLTESTIMATEGRID_COL_RELERROR, new QSettingItem(this));
	setItem(3, LINEVOLTESTIMATEGRID_COL_RELERROR, new QSettingItem(this));

	((QSettingItem*)item(0, LINEVOLTESTIMATEGRID_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_RelErr));
	((QSettingItem*)item(1, LINEVOLTESTIMATEGRID_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_RelErr));
	((QSettingItem*)item(2, LINEVOLTESTIMATEGRID_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_RelErr));
	((QSettingItem*)item(3, LINEVOLTESTIMATEGRID_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleActVal_RelErr));


	setItem(0, LINEVOLTESTIMATEGRID_COL_ABSERROR, new QSettingItem(this));
	setItem(1, LINEVOLTESTIMATEGRID_COL_ABSERROR, new QSettingItem(this));
	setItem(2, LINEVOLTESTIMATEGRID_COL_ABSERROR, new QSettingItem(this));
	setItem(3, LINEVOLTESTIMATEGRID_COL_ABSERROR, new QSettingItem(this));

	((QSettingItem*)item(0, LINEVOLTESTIMATEGRID_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_AbsErr));
	((QSettingItem*)item(1, LINEVOLTESTIMATEGRID_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_AbsErr));
	((QSettingItem*)item(2, LINEVOLTESTIMATEGRID_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_AbsErr));
	((QSettingItem*)item(3, LINEVOLTESTIMATEGRID_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleActVal_AbsErr));

	setItem(0, LINEVOLTESTIMATEGRID_COL_SETVALUE, new QSettingItem(this));
	setItem(1, LINEVOLTESTIMATEGRID_COL_SETVALUE, new QSettingItem(this));
	setItem(2, LINEVOLTESTIMATEGRID_COL_SETVALUE, new QSettingItem(this));
	setItem(3, LINEVOLTESTIMATEGRID_COL_SETVALUE, new QSettingItem(this));

	((QSettingItem*)item(0, LINEVOLTESTIMATEGRID_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeSet));
	((QSettingItem*)item(1, LINEVOLTESTIMATEGRID_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fUSet));
	((QSettingItem*)item(2, LINEVOLTESTIMATEGRID_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fISet));
	((QSettingItem*)item(3, LINEVOLTESTIMATEGRID_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleSet));

	setItem(0, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR, new QSettingItem(this));
	setItem(1, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR, new QSettingItem(this));
	setItem(2, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR, new QSettingItem(this));
	setItem(3, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR, new QSettingItem(this));

	strText = "——";
	((QSettingItem*)item(0, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_AbsErrNeg));
	((QSettingItem*)item(1, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR))->UpdateText(strText);
	((QSettingItem*)item(2, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR))->UpdateText(strText);
	((QSettingItem*)item(3, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR))->UpdateText(strText);

	for (int nRow = 0; nRow < rowCount(); nRow++)
	{
// 		if (i != LINEVOLTESTIMATEGRID_COL_ERRORTYPE)
// 		{
// 			item(0,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 			item(1,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 			item(2,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);	
// 		}
		for (int i = 0; i < columnCount(); i++)
	{
			if (i == LINEVOLTESTIMATEGRID_COL_NAME)
		{
				item(nRow, i)->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
				item(nRow, i)->setFlags(item(nRow, i)->flags() & ~Qt::ItemIsEditable);
			}
			else if (i != LINEVOLTESTIMATEGRID_COL_ERRORTYPE)
			{
				item(nRow, i)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
	}
		EnableRow(nRow, FALSE);
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
		else if (pParas->m_nGradientTpSelect == 1)//相位
		{
			EnableRow(3);
		}
	}
	EnableRow(0);

	CbbErrorType(0,pCbbError1->currentText());
	CbbErrorType(1,pCbbError2->currentText());
	CbbErrorType(2,pCbbError3->currentText());
	CbbErrorType(3, pCbbError4->currentText());

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(pCbbError1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError4, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));

}

void LineVoltEstimateGrid::CbbErrorType(int nIndex, CString strText)
{
	if (strText==g_sLangTxt_StateEstimate_AbsError)//绝对误差
	{
// 		item(nIndex, LINEVOLTESTIMATEGRID_COL_RELERROR)->setFlags(item(nIndex, LINEVOLTESTIMATEGRID_COL_RELERROR)->flags() & ~Qt::ItemIsEditable);
// 		item(nIndex, LINEVOLTESTIMATEGRID_COL_ABSERROR)->setFlags(item(nIndex, LINEVOLTESTIMATEGRID_COL_ABSERROR)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		SetItemEnable(nIndex,LINEVOLTESTIMATEGRID_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_ABSERROR, TRUE);
		if (nIndex == 0)
		{
			SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR, TRUE);
		}
		else
		{
			SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR, FALSE);
		}
	}
	else if (strText==g_sLangTxt_StateEstimate_RelError)//相对误差
	{
		SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_ABSERROR, FALSE);
		SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR, FALSE);
	}
	else if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_ABSERROR, FALSE);
		SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR, FALSE);
	}
	else
	{
		SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_ABSERROR, TRUE);
		if (nIndex == 0)
		{
		SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR, TRUE);
	}
		else
		{
			SetItemEnable(nIndex, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR, FALSE);
		}
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

	if(col==LINEVOLTESTIMATEGRID_COL_RELERROR)//相对误差
	{
		fv=setLimit(0,100,fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if(col==LINEVOLTESTIMATEGRID_COL_ABSERROR)//绝对误差
	{
		fv=setLimit(0,200,fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if (row == 0 && col == LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR)//绝对误差（-）
	{
		fv = setLimit(0, 200, fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if(col==LINEVOLTESTIMATEGRID_COL_SETVALUE)//整定值
	{
		if (row==0)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		if (row==1)
		{
			fv=setLimit(0,120,fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		if (row==LINEVOLTESTIMATEGRID_COL_RELERROR)
		{
			fv=setLimit(0,10,fv);
			pItem->setText(QString::number(fv, 'f', 3));
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

	return QTableWidget::eventFilter(obj, event);
}

void LineVoltEstimateGrid::mousePressEvent(QMouseEvent * event)
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

void LineVoltEstimateGrid::SetItemEnable(int nRow, int nCol, BOOL bEnable)
{
	QTableWidgetItem *pItem = item(nRow, nCol);
	if (!pItem)
	{
		return;
	}


	bool bCbbState = true;
	if (nCol == LINEVOLTESTIMATEGRID_COL_RELERROR || nCol == LINEVOLTESTIMATEGRID_COL_ABSERROR || nCol == LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR)
	{
		QComboBox* pCbb = (QComboBox*)cellWidget(nRow, LINEVOLTESTIMATEGRID_COL_ERRORTYPE);
		if (pCbb)
		{
			bCbbState = pCbb->isEnabled();
		}

		if (bCbbState == FALSE)
		{
			bEnable = FALSE;
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

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240808 
LineVoltManualEstimateDlg::LineVoltManualEstimateDlg(tmt_LinevoltManuParas* pParas, QWidget* parent) : QDialog(parent)
{
	Stt_Global_SettingParent(this);	//20240808 gongyipng
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
}

LineVoltManualEstimateDlg::~LineVoltManualEstimateDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
}

void LineVoltManualEstimateDlg::InitUI()
{
	CString strTitle = g_sLangTxt_StateEstimate_ResultEstimate; 
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new LineVoltEstimateGrid(4, 6, this);
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

// 	resize(600, 400);
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
#endif
}

void LineVoltManualEstimateDlg::slot_btnOK_Clicked()
{
//20240808 gongyiping 结构体数据在序列化保存时保存了定值关联，待测试
	if (!((QSettingItem*)m_pGrid->item(0, LINEVOLTESTIMATEGRID_COL_RELERROR))->IsSetting())
	m_pParas->m_fTimeValue_RelErr = m_pGrid->item(0, LINEVOLTESTIMATEGRID_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, LINEVOLTESTIMATEGRID_COL_RELERROR))->IsSetting())
	m_pParas->m_fUActVal_RelErr = m_pGrid->item(1, LINEVOLTESTIMATEGRID_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(2, LINEVOLTESTIMATEGRID_COL_RELERROR))->IsSetting())
	m_pParas->m_fIActVal_RelErr = m_pGrid->item(2, LINEVOLTESTIMATEGRID_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3, LINEVOLTESTIMATEGRID_COL_RELERROR))->IsSetting())
		m_pParas->m_fAngleActVal_RelErr = m_pGrid->item(3, LINEVOLTESTIMATEGRID_COL_RELERROR)->text().toFloat();

	if (!((QSettingItem*)m_pGrid->item(0, LINEVOLTESTIMATEGRID_COL_ABSERROR))->IsSetting())
	m_pParas->m_fTimeValue_AbsErr = m_pGrid->item(0, LINEVOLTESTIMATEGRID_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, LINEVOLTESTIMATEGRID_COL_ABSERROR))->IsSetting())
	m_pParas->m_fUActVal_AbsErr = m_pGrid->item(1, LINEVOLTESTIMATEGRID_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(2, LINEVOLTESTIMATEGRID_COL_ABSERROR))->IsSetting())
	m_pParas->m_fIActVal_AbsErr = m_pGrid->item(2, LINEVOLTESTIMATEGRID_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3, LINEVOLTESTIMATEGRID_COL_ABSERROR))->IsSetting())
		m_pParas->m_fAngleActVal_AbsErr = m_pGrid->item(3, LINEVOLTESTIMATEGRID_COL_ABSERROR)->text().toFloat();

	if (!((QSettingItem*)m_pGrid->item(0, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR))->IsSetting())
		m_pParas->m_fTimeValue_AbsErrNeg = m_pGrid->item(0, LINEVOLTESTIMATEGRID_COL_NEGATIVEABSERROR)->text().toFloat();

	m_pParas->m_nTimeValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(0, LINEVOLTESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
	m_pParas->m_nUActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(1, LINEVOLTESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
	m_pParas->m_nIActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(2, LINEVOLTESTIMATEGRID_COL_ERRORTYPE))->currentIndex();

	CString strText = ((QComboBox*)m_pGrid->cellWidget(3, LINEVOLTESTIMATEGRID_COL_ERRORTYPE))->currentText();
	if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		m_pParas->m_nAngleActVal_ErrorLogic = 5;
	}
	else
	{
		m_pParas->m_nAngleActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(3, LINEVOLTESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
	}

	if (!((QSettingItem*)m_pGrid->item(0, LINEVOLTESTIMATEGRID_COL_SETVALUE))->IsSetting())
	m_pParas->m_fTimeSet = m_pGrid->item(0, LINEVOLTESTIMATEGRID_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, LINEVOLTESTIMATEGRID_COL_SETVALUE))->IsSetting())
	m_pParas->m_fUSet = m_pGrid->item(1, LINEVOLTESTIMATEGRID_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(2, LINEVOLTESTIMATEGRID_COL_SETVALUE))->IsSetting())
	m_pParas->m_fISet = m_pGrid->item(2, LINEVOLTESTIMATEGRID_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3, LINEVOLTESTIMATEGRID_COL_SETVALUE))->IsSetting())
		m_pParas->m_fAngleSet = m_pGrid->item(3, LINEVOLTESTIMATEGRID_COL_SETVALUE)->text().toFloat();

	accept();
}

void LineVoltManualEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}