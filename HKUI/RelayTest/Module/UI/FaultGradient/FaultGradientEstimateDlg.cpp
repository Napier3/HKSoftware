#include "FaultGradientEstimateDlg.h"
#include "ui_FaultGradientEstimateDlg.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../Controls/SettingCtrls/QSettingItem.h"
#include <QHeaderView>
#include "../Module/CommonMethod/commonMethod.h"
#include <QDesktopWidget>
#include <QRect>
#include "../SttTestCntrFrameBase.h"

#define  GRADIENTESTIMATE_COL_NAME			0		//名称
#define  GRADIENTESTIMATE_COL_SETVALUE		1		//整定值
#define  GRADIENTESTIMATE_COL_ERRORTYPE		2		//误差类型
#define  GRADIENTESTIMATE_COL_RELERROR		3		//相对误差
#define  GRADIENTESTIMATE_COL_ABSERROR		4		//绝对误差

QFaultGradientEstimateGrid::QFaultGradientEstimateGrid(QWidget *parent):QScrollTableWidget(parent)	//QTableWidget(parent)//20240808 gongyiping
{
	m_bRunning = FALSE;
	installEventFilter(this);
}

QFaultGradientEstimateGrid::~QFaultGradientEstimateGrid()
{
}

void QFaultGradientEstimateGrid::InitGrid()
{
	//设置tab 行列
	QStringList lstTabCol;
	lstTabCol << /*"名称"*/g_sLangTxt_Name << g_sLangTxt_State_SettingValue/*"整定值"*/ << /*"误差类型"*/g_sLangTxt_StateEstimate_ErrorType <</* "相对误差(%)"*/g_sLangTxt_StateEstimate_RelError + "(%)" << /*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError;
	setRowCount(FG_EstimateRow);
	setColumnCount(FG_EstimateCol);
	this->setHorizontalHeaderLabels(lstTabCol);

//	setColumnWidth(0, 150);
//	setColumnWidth(1, 150);
//	setColumnWidth(4, 120);
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

void QFaultGradientEstimateGrid::InitData(tmt_fault_gradient_test* pParas)
{
	if (pParas->m_oFaultGradientParas.m_nTestMode == FG_TestMode_ActValue)
	{
		int nFaultIndex = pParas->m_oFaultGradientParas.m_nFaultMode;
		int nChangIndex = pParas->m_oFaultGradientParas.m_nChangeValue;
		if (nFaultIndex >= FG_FaultMode_AB_C && nFaultIndex <= FG_FaultMode_CA_A)
		{
			if (nChangIndex == 0)
			{
				//SetUnit(nFaultIndex, nChangIndex, "V");
				EnableRow(0);
			}
			else if (nChangIndex == 1)
			{
				//SetUnit(nFaultIndex, nChangIndex, "A");
				EnableRow(1);
			}
			else if (nChangIndex == 2)
			{
				//SetUnit(nFaultIndex, nChangIndex, QString::fromLocal8Bit("°"));
				EnableRow(2);
			}
		}
		else if (nFaultIndex == FG_FaultMode_UF)
		{
			if (nChangIndex == FG_FM_Vaule_VM)
			{
				//SetUnit(nFaultIndex, nChangIndex, "V");
				EnableRow(0);
			}
			else if (nChangIndex == FG_FM_Vaule_HZ)
			{
				//SetUnit(nFaultIndex, nChangIndex, "Hz");
				EnableRow(4);
			}
		}
		else if (nFaultIndex == FG_FaultMode_I2I1)
		{
			//SetUnit(nFaultIndex, nChangIndex, "A");
			EnableRow(1);
		}
		else
		{
			if (nChangIndex == FG_FM_Vaule_ShortVM || nChangIndex == FG_FM_Vaule_PlusVM
				|| nChangIndex == FG_FM_Vaule_MinusVM || nChangIndex == FG_FM_Vaule_ZeroVM)
			{
				//SetUnit(nFaultIndex, nChangIndex, "V");
				EnableRow(0);
			}
			if (nChangIndex == FG_FM_Vaule_ShortVA)
			{
				//SetUnit(nFaultIndex, nChangIndex, "A");
				EnableRow(1);
			}
			if (nChangIndex == FG_FM_Vaule_ShortImpede)
			{
				//SetUnit(nFaultIndex, nChangIndex, QString::fromLocal8Bit("Ω"));
				EnableRow(3);
			}
			if (nChangIndex == FG_FM_Vaule_ImpedeAngle)
			{
				//SetUnit(nFaultIndex, nChangIndex, QString::fromLocal8Bit("°"));
				EnableRow(2);
			}
			if (nChangIndex == FG_FM_Vaule_Frequency)
			{
				//SetUnit(nFaultIndex, nChangIndex, "Hz");
				EnableRow(4);
			}
		}
	}
	else if (pParas->m_oFaultGradientParas.m_nTestMode == FG_TestMode_ReturnCoef)//返回系数
	{
		EnableRow(8);
	}
	else if (pParas->m_oFaultGradientParas.m_nTestMode == FG_TestMode_MaxAngle)//最大灵敏角
	{
		EnableRow(5);
		EnableRow(6);
		EnableRow(7);
	}
	else
	{

	}
	
}
void QFaultGradientEstimateGrid::EnableRow(long nIndex, BOOL bEnabled)
{
	if (nIndex >= rowCount())
	{
		return;
	}

	QComboBox* pCbb = (QComboBox*)cellWidget(nIndex, GRADIENTESTIMATE_COL_ERRORTYPE);
	pCbb->setEnabled(bEnabled);
	if (bEnabled)
	{
		SetItemEnable(nIndex, GRADIENTESTIMATE_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, GRADIENTESTIMATE_COL_ABSERROR, TRUE);
	}
	else
	{
		SetItemEnable(nIndex, GRADIENTESTIMATE_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, GRADIENTESTIMATE_COL_ABSERROR, FALSE);
	}
	CbbErrorType(nIndex, pCbb->currentText());
}

QComboBox* QFaultGradientEstimateGrid::NewErrorType()
{
	CString strText;
	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"相对误差"*/g_sLangTxt_StateEstimate_RelError);

	strText = g_sLangTxt_StateEstimate_AbsError +"or"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"相对误差or绝对误差"*/strText);

	strText = g_sLangTxt_StateEstimate_AbsError +"&"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"相对误差&绝对误差"*/strText);

	//pCbbError->addItem(/*"组合误差"*/g_sLangTxt_StateEstimate_CombinationError);
	pCbbError->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
	return pCbbError;
}

QComboBox* QFaultGradientEstimateGrid::AbsErrorType()
{
	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
	return pCbbError;
}

void QFaultGradientEstimateGrid::addTabRow(int nRow,QString strValue,int nComType,long l1Value,float f2Value,float f3Value,float f4Value)
{
	setItem(nRow, GRADIENTESTIMATE_COL_NAME, new QTableWidgetItem(strValue));
	item(nRow, GRADIENTESTIMATE_COL_NAME)->setFlags((item(nRow, GRADIENTESTIMATE_COL_NAME)->flags()) & ~Qt::ItemIsEditable);
	item(nRow, GRADIENTESTIMATE_COL_NAME)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	QComboBox *pCbbErrorType = NULL;
	if(nComType == 0)
	{
		pCbbErrorType = NewErrorType();
	}
	else if (nComType == 1)
	{
		pCbbErrorType = AbsErrorType();
	}
	pCbbErrorType->setObjectName(QString::number(nRow));
	SetTabComboxModelStyle(pCbbErrorType);
	setCellWidget(nRow, GRADIENTESTIMATE_COL_ERRORTYPE, pCbbErrorType);
	if (l1Value == 5)//不评估
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbErrorType->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbErrorType,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
	pCbbErrorType->setCurrentIndex(l1Value);
	}
	setItem(nRow, GRADIENTESTIMATE_COL_RELERROR, new QSettingItem(this));
	f2Value = QString::number(f2Value, 'f', 2).toFloat();
	((QSettingItem*)item(nRow, GRADIENTESTIMATE_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&f2Value));
	item(nRow, GRADIENTESTIMATE_COL_RELERROR)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	setItem(nRow, GRADIENTESTIMATE_COL_ABSERROR, new QSettingItem(this));
	f3Value = QString::number(f3Value, 'f', 3).toFloat();
	((QSettingItem*)item(nRow, GRADIENTESTIMATE_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&f3Value));
	item(nRow, GRADIENTESTIMATE_COL_ABSERROR)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	//20240808 gongyiping 创建定值关联控件 
	//setItem(nRow, 4, new QTableWidgetItem(QString::number(f4Value)));
	setItem(nRow, GRADIENTESTIMATE_COL_SETVALUE, new QSettingItem(this));
	f4Value = QString::number(f4Value, 'f', 3).toFloat();
	((QSettingItem*)item(nRow, GRADIENTESTIMATE_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&f4Value));
	item(nRow, GRADIENTESTIMATE_COL_SETVALUE)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	
	EnableRow(nRow, FALSE);

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	connect(pCbbErrorType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	//CbbErrorType(nRow,pCbbErrorType->currentText());
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
void QFaultGradientEstimateGrid::SetItemEnable(int nRow, int nCol, BOOL bEnable)
{
	QTableWidgetItem *pItem = item(nRow, nCol);
	if (!pItem)
	{
		return;
	}

	bool bCbbState = true;
	if (nCol == GRADIENTESTIMATE_COL_RELERROR || nCol == GRADIENTESTIMATE_COL_ABSERROR)
	{
		QComboBox* pCbb = (QComboBox*)cellWidget(nRow, GRADIENTESTIMATE_COL_ERRORTYPE);
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
void QFaultGradientEstimateGrid::CbbErrorType(int nIndex, CString strText)
{
	if (strText==g_sLangTxt_StateEstimate_AbsError)//绝对误差
	{
		//item(nIndex, GRADIENTESTIMATE_COL_RELERROR)->setFlags(item(nIndex, GRADIENTESTIMATE_COL_RELERROR)->flags() & ~Qt::ItemIsEditable);
		//item(nIndex, GRADIENTESTIMATE_COL_ABSERROR)->setFlags(item(nIndex, GRADIENTESTIMATE_COL_ABSERROR)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		SetItemEnable(nIndex, GRADIENTESTIMATE_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, GRADIENTESTIMATE_COL_ABSERROR, TRUE);
	}
	else if (strText==g_sLangTxt_StateEstimate_RelError)//相对误差
	{
		//item(nIndex, GRADIENTESTIMATE_COL_RELERROR)->setFlags(item(nIndex, GRADIENTESTIMATE_COL_RELERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		//item(nIndex, GRADIENTESTIMATE_COL_ABSERROR)->setFlags(item(nIndex, GRADIENTESTIMATE_COL_ABSERROR)->flags() & ~Qt::ItemIsEditable);
		SetItemEnable(nIndex, GRADIENTESTIMATE_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, GRADIENTESTIMATE_COL_ABSERROR, FALSE);
	}
	else if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		SetItemEnable(nIndex, GRADIENTESTIMATE_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, GRADIENTESTIMATE_COL_ABSERROR, FALSE);
	}
	else
	{
		//item(nIndex, GRADIENTESTIMATE_COL_RELERROR)->setFlags(item(nIndex, GRADIENTESTIMATE_COL_RELERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		//item(nIndex, GRADIENTESTIMATE_COL_ABSERROR)->setFlags(item(nIndex, GRADIENTESTIMATE_COL_ABSERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		SetItemEnable(nIndex, GRADIENTESTIMATE_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, GRADIENTESTIMATE_COL_ABSERROR, TRUE);
	}
}

void QFaultGradientEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	QObject *senderObj = sender();
	CString strName;
	if (senderObj)
	{
		strName = senderObj->objectName();
	}
	CbbErrorType(strName.toInt(), strText);
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
	//处理业务 ToDo
	if (col == GRADIENTESTIMATE_COL_ERRORTYPE)
	{
		pItem->setText(str);
	}

	if (col == GRADIENTESTIMATE_COL_RELERROR)//相对误差
	{
		if (row == 8)
		{
			return;
		}
		fv = setLimit(0, 100, fv);
		pItem->setText(QString::number(fv, 'f', 2));
	}

	if (col == GRADIENTESTIMATE_COL_ABSERROR)//绝对误差
	{
		fv = setLimit(0, 200, fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if (col == GRADIENTESTIMATE_COL_SETVALUE)//整定值
	{
		if (row == 0)
		{
			fv = setLimit(0, 120, fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		if (row == 1)
		{
			fv = setLimit(0, 10, fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		if (row == 2)
		{
			fv = setLimit(0, 360, fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		if (row == 3)
		{
			fv = setLimit(0, 1550, fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		if (row == 4)
		{
			fv = setLimit(0, 1550, fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		if (row == 5)
		{
			fv = setLimit(0, 360, fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		if (row == 6)
		{
			fv = setLimit(0, 360, fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		if (row == 7)
		{
			fv = setLimit(0, 360, fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		if (row == 8)
		{
			fv = setLimit(0, 999, fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
	}
	//////////////////////////////
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

bool QFaultGradientEstimateGrid::eventFilter(QObject *obj, QEvent *event)
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

void QFaultGradientEstimateGrid::mousePressEvent(QMouseEvent * event)
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

/////////////////////////////////Dlg

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240808 
CFaultGradientEstimateDlg::CFaultGradientEstimateDlg(tmt_fault_gradient_test* pPara,QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::CFaultGradientEstimateDlg();
	ui->setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	Stt_Global_SettingParent(this);	//20240808 gongyipng
	m_pCurFGTest = pPara;
	initUI();
}


CFaultGradientEstimateDlg::~CFaultGradientEstimateDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
	delete ui;
}

void CFaultGradientEstimateDlg::initUI()
{
	CString strTitle = g_sLangTxt_StateEstimate_ResultEstimate; //lcq
	setWindowTitle(strTitle);
	initTab();	
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));

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
		resize(800, 400);
	}
#else
	resize(800, 400);
#endif // _PSX_QT_WINDOWS_
}

void CFaultGradientEstimateDlg::initTab()
{
	ui->tableWidget->InitGrid();


	xlang_SetLangStrToWidget(ui->btnOk, "sOK", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(ui->btnCancel, "sCancel", XLang_Ctrls_QPushButton);
	//测试
	ui->tableWidget->addTabRow(0,/*"电压动作值(V)"*/g_sLangTxt_Gradient_VActionValue, 0, m_pCurFGTest->m_oFaultGradientParas.m_nUActVal_ErrorLogic, m_pCurFGTest->m_oFaultGradientParas.m_fUActVal_RelErr, m_pCurFGTest->m_oFaultGradientParas.m_fUActVal_AbsErr, m_pCurFGTest->m_oFaultGradientParas.m_fUSet);
	ui->tableWidget->addTabRow(1,/*"电流动作值(A)"*/g_sLangTxt_Gradient_CActionValue, 0, m_pCurFGTest->m_oFaultGradientParas.m_nIActVal_ErrorLogic, m_pCurFGTest->m_oFaultGradientParas.m_fIActVal_RelErr, m_pCurFGTest->m_oFaultGradientParas.m_fIActVal_AbsErr, m_pCurFGTest->m_oFaultGradientParas.m_fISet);
	CString strText = g_sLangTxt_Gradient_ImpAngle;
	if (strText.contains(":"))
	{
		strText.remove(":");
	}
	ui->tableWidget->addTabRow(2,/*"阻抗角(°)"*/strText, 0, m_pCurFGTest->m_oFaultGradientParas.m_nImpAngleActVal_ErrorLogic, m_pCurFGTest->m_oFaultGradientParas.m_fImpAngleActVal_RelErr, m_pCurFGTest->m_oFaultGradientParas.m_fImpAngleActVal_AbsErr, m_pCurFGTest->m_oFaultGradientParas.m_fImpAngleSet);
	strText = g_sLangTxt_Swing_Impedance;
	if (strText.contains(":"))
	{
		strText.remove(":");
	}
	ui->tableWidget->addTabRow(3,/*"短路阻抗(Ω)"*/strText, 0, m_pCurFGTest->m_oFaultGradientParas.m_nShortZImpActVal_ErrorLogic, m_pCurFGTest->m_oFaultGradientParas.m_fShortZImpActVal_RelErr, m_pCurFGTest->m_oFaultGradientParas.m_fShortZImpActVal_AbsErr, m_pCurFGTest->m_oFaultGradientParas.m_fShortZImp);
	ui->tableWidget->addTabRow(4,/*"频率动作值(Hz)"*/g_sLangTxt_Gradient_FreAValue, 1, m_pCurFGTest->m_oFaultGradientParas.m_nHzActVal_ErrorLogic, m_pCurFGTest->m_oFaultGradientParas.m_fHzActVal_RelErr, m_pCurFGTest->m_oFaultGradientParas.m_fHzActVal_AbsErr, m_pCurFGTest->m_oFaultGradientParas.m_fHzSet);
	ui->tableWidget->addTabRow(5,/*"边界角1(°)"*/g_sLangTxt_Gradient_FirBoundAngle, 0, m_pCurFGTest->m_oFaultGradientParas.m_nAngleF_ErrorLogic, m_pCurFGTest->m_oFaultGradientParas.m_fAngleF_RelErr, m_pCurFGTest->m_oFaultGradientParas.m_fAngleF_AbsErr, m_pCurFGTest->m_oFaultGradientParas.m_fAngleFSet);
	ui->tableWidget->addTabRow(6,/*"边界角2(°)"*/g_sLangTxt_Gradient_SecBoundAngle, 0, m_pCurFGTest->m_oFaultGradientParas.m_nAngleS_ErrorLogic, m_pCurFGTest->m_oFaultGradientParas.m_fAngleS_RelErr, m_pCurFGTest->m_oFaultGradientParas.m_fAngleS_AbsErr, m_pCurFGTest->m_oFaultGradientParas.m_fAngleSSet);
	ui->tableWidget->addTabRow(7,/*"最大灵敏角(°)"*/g_sLangTxt_Gradient_MaxSenAngle, 0, m_pCurFGTest->m_oFaultGradientParas.m_nMaxAngle_ErrorLogic, m_pCurFGTest->m_oFaultGradientParas.m_fMaxAngle_RelErr, m_pCurFGTest->m_oFaultGradientParas.m_fMaxAngle_AbsErr, m_pCurFGTest->m_oFaultGradientParas.m_fMaxAngleSet);
	ui->tableWidget->addTabRow(8,/*"返回系数"*/g_sLangTxt_Gradient_ReCoefficient, 1, m_pCurFGTest->m_oFaultGradientParas.m_nRetCoef_ErrorLogic, m_pCurFGTest->m_oFaultGradientParas.m_fRetCoef_RelErr, m_pCurFGTest->m_oFaultGradientParas.m_fRetCoef_AbsErr, m_pCurFGTest->m_oFaultGradientParas.m_fRetCoefSet);
	ui->tableWidget->InitData(m_pCurFGTest);
}

void CFaultGradientEstimateDlg::slot_btnOK_Clicked()
{
	//保存具体的值
	m_pCurFGTest->m_oFaultGradientParas.m_fUActVal_RelErr = ui->tableWidget->item(0, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fIActVal_RelErr = ui->tableWidget->item(1, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fImpAngleActVal_RelErr = ui->tableWidget->item(2, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fShortZImpActVal_RelErr = ui->tableWidget->item(3, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fHzActVal_RelErr = ui->tableWidget->item(4, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fAngleF_RelErr = ui->tableWidget->item(5, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fAngleS_RelErr = ui->tableWidget->item(6, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fMaxAngle_RelErr = ui->tableWidget->item(7, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fRetCoef_RelErr = 0.0f;

	m_pCurFGTest->m_oFaultGradientParas.m_fUActVal_AbsErr = ui->tableWidget->item(0, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fIActVal_AbsErr = ui->tableWidget->item(1, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fImpAngleActVal_AbsErr = ui->tableWidget->item(2, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fShortZImpActVal_AbsErr = ui->tableWidget->item(3, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fHzActVal_AbsErr = ui->tableWidget->item(4, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fAngleF_AbsErr = ui->tableWidget->item(5, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fAngleS_AbsErr = ui->tableWidget->item(6, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fMaxAngle_AbsErr = ui->tableWidget->item(7, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fRetCoef_AbsErr = ui->tableWidget->item(8, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();



	if (((QComboBox*)ui->tableWidget->cellWidget(0, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nUActVal_ErrorLogic = 5;
	}
	else
	{
	m_pCurFGTest->m_oFaultGradientParas.m_nUActVal_ErrorLogic = ((QComboBox*)ui->tableWidget->cellWidget(0, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)ui->tableWidget->cellWidget(1, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nIActVal_ErrorLogic = 5;
	}
	else
	{
	m_pCurFGTest->m_oFaultGradientParas.m_nIActVal_ErrorLogic = ((QComboBox*)ui->tableWidget->cellWidget(1, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}
	
	if (((QComboBox*)ui->tableWidget->cellWidget(2, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nImpAngleActVal_ErrorLogic = 5;
	}
	else
	{
	m_pCurFGTest->m_oFaultGradientParas.m_nImpAngleActVal_ErrorLogic = ((QComboBox*)ui->tableWidget->cellWidget(2, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)ui->tableWidget->cellWidget(3, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nShortZImpActVal_ErrorLogic = 5;
	}
	else
	{
	m_pCurFGTest->m_oFaultGradientParas.m_nShortZImpActVal_ErrorLogic = ((QComboBox*)ui->tableWidget->cellWidget(3, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)ui->tableWidget->cellWidget(4, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nHzActVal_ErrorLogic = 5;
	}
	else
	{
	m_pCurFGTest->m_oFaultGradientParas.m_nHzActVal_ErrorLogic = ((QComboBox*)ui->tableWidget->cellWidget(4, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)ui->tableWidget->cellWidget(5, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nAngleF_ErrorLogic = 5;
	}
	else
	{
	m_pCurFGTest->m_oFaultGradientParas.m_nAngleF_ErrorLogic = ((QComboBox*)ui->tableWidget->cellWidget(5, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)ui->tableWidget->cellWidget(6, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nAngleS_ErrorLogic = 5;
	}
	else
	{
	m_pCurFGTest->m_oFaultGradientParas.m_nAngleS_ErrorLogic = ((QComboBox*)ui->tableWidget->cellWidget(6, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)ui->tableWidget->cellWidget(7, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nMaxAngle_ErrorLogic = 5;
	}
	else
	{
	m_pCurFGTest->m_oFaultGradientParas.m_nMaxAngle_ErrorLogic = ((QComboBox*)ui->tableWidget->cellWidget(7, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)ui->tableWidget->cellWidget(8, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nRetCoef_ErrorLogic = 5;
	}
	else
	{
	m_pCurFGTest->m_oFaultGradientParas.m_nRetCoef_ErrorLogic = ((QComboBox*)ui->tableWidget->cellWidget(8, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	m_pCurFGTest->m_oFaultGradientParas.m_fUSet = ui->tableWidget->item(0, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fISet = ui->tableWidget->item(1, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fImpAngleSet = ui->tableWidget->item(2, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fShortZImp = ui->tableWidget->item(3, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fHzSet = ui->tableWidget->item(4, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fAngleFSet = ui->tableWidget->item(5, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fAngleSSet = ui->tableWidget->item(6, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fMaxAngleSet = ui->tableWidget->item(7, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pCurFGTest->m_oFaultGradientParas.m_fRetCoefSet = ui->tableWidget->item(8, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	accept();
}

void CFaultGradientEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}
