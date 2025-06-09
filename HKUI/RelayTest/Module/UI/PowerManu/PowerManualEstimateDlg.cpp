#include "PowerManualEstimateDlg.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "SttMacroParaEditViewPowerManu.h"
// #include "../../XLangResource_Native.h"
#include <QApplication>
#include "../SttTestCntrFrameBase.h"

#ifdef _PSX_QT_WINDOWS_
//#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
//#include "../SttTestCntrFrameBase.h"
#endif

#define  POWERESTIMATE_COL_NAME			0		//名称
#define  POWERESTIMATE_COL_SETVALUE		1		//整定值
#define  POWERESTIMATE_COL_ERRORTYPE		2		//误差类型
#define  POWERESTIMATE_COL_RELERROR		3		//相对误差
#define  POWERESTIMATE_COL_ABSERRORPOS		4		//绝对误差
#define  POWERESTIMATE_COL_ABSERRORNEG		5		//绝对误差-

PowerEstimateGrid::PowerEstimateGrid(int rows, int columns, QWidget* parent) : QScrollTableWidget(parent)	//QTableWidget(rows, columns, parent)//20240808 gongyiping
{
	//20240808 gongyiping
	setRowCount(rows);
	setColumnCount(columns);

	m_bRunning = FALSE;
	installEventFilter(this);
}

PowerEstimateGrid::~PowerEstimateGrid()
{

}

void PowerEstimateGrid::InitGrid()
{
	CString strName, strErrorType, strRelError, strAbsError, strSettingValue;
	xlang_GetLangStrByFile(strName, "sName");//名称
	xlang_GetLangStrByFile(strErrorType, "StateEstimate_ErrorType");//误差类型
	strRelError = g_sLangTxt_StateEstimate_RelError;//相对误差(%)
	strRelError += "(%)";
	xlang_GetLangStrByFile(strAbsError, "StateEstimate_AbsError");//绝对误差
	xlang_GetLangStrByFile(strSettingValue, "State_SettingValue");//整定值

	setHorizontalHeaderLabels(QStringList() << strName << strSettingValue << strErrorType << strRelError << strAbsError << strAbsError + "(-)");
    //setColumnWidth(0, 120);
    //setColumnWidth(1, 150);
    //setColumnWidth(4, 80);
    //this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
	this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); 
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
}
void PowerEstimateGrid::SetItemEnable(int nRow, int nCol, BOOL bEnable)
{
	QTableWidgetItem *pItem = item(nRow, nCol);
	if (!pItem)
	{
		return;
	}

	bool bCbbState = true;
	if (nCol == POWERESTIMATE_COL_RELERROR || nCol == POWERESTIMATE_COL_ABSERRORPOS || nCol == POWERESTIMATE_COL_ABSERRORNEG)
	{
		QComboBox* pCbb = (QComboBox*)cellWidget(nRow, POWERESTIMATE_COL_ERRORTYPE);
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
QComboBox* PowerEstimateGrid::NewErrorType()
{
	CString strText;

	QComboBox *pCbbError = new QComboBox(this);
	
	pCbbError->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"相对误差"*/g_sLangTxt_StateEstimate_RelError);

	strText = g_sLangTxt_StateEstimate_AbsError +"or"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"相对误差or绝对误差"*/strText);

	strText = g_sLangTxt_StateEstimate_AbsError +"&"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"相对误差&绝对误差"*/strText);

	pCbbError->addItem(/*"组合误差"*/g_sLangTxt_StateEstimate_CombinationError);
	pCbbError->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
	return pCbbError;
}

QComboBox* PowerEstimateGrid::AmpErrorType()
{
	CString strText;

	QComboBox *pCbbError = new QComboBox(this);

	pCbbError->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"相对误差"*/g_sLangTxt_StateEstimate_RelError);

	strText = g_sLangTxt_StateEstimate_AbsError + "or" + g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"相对误差or绝对误差"*/strText);

	strText = g_sLangTxt_StateEstimate_AbsError + "&" + g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"相对误差&绝对误差"*/strText);

	pCbbError->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
	return pCbbError;
}

void PowerEstimateGrid::EnableRow(long nIndex, BOOL bEnabled)
{
	if (nIndex >= rowCount())
	{
		return;
	}

	QComboBox* pCbb = (QComboBox*)cellWidget(nIndex, POWERESTIMATE_COL_ERRORTYPE);
	pCbb->setEnabled(bEnabled);
	if (bEnabled)
	{
		SetItemEnable(nIndex, POWERESTIMATE_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORPOS, TRUE);
		SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORNEG, TRUE);
	}
	else
	{
		SetItemEnable(nIndex, POWERESTIMATE_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORPOS, FALSE);
		SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORNEG, FALSE);
	}
}

void PowerEstimateGrid::InitData(tmt_PowerManuParas* pParas)
{
	//20240805 gongyiping 通用功率只需要动作时间和功率动作值
	m_pParas=pParas;
	CString strText; 
	strText = /*"动作时间(s)"*/g_sLangTxt_Native_ActionTime;
	setItem(0, POWERESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	strText = /*"功率动作值"*/g_sLangTxt_PowerManu_PowerAct;
	setItem(1, POWERESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	//strText = "P(W)";
	//setItem(2, POWERESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	//strText = "Q(Var)";
	//setItem(3, POWERESTIMATE_COL_NAME, new QTableWidgetItem(strText));

	strText = "——";
	setItem(1, POWERESTIMATE_COL_ABSERRORNEG, new QTableWidgetItem(strText));
	//setItem(2, POWERESTIMATE_COL_ABSERRORNEG, new QTableWidgetItem(strText));
	//setItem(3, POWERESTIMATE_COL_ABSERRORNEG, new QTableWidgetItem(strText));

	QComboBox *pCbbError1 = NewErrorType();
	pCbbError1->setCurrentIndex(pParas->m_nTimeValue_ErrorLogic);
	QComboBox *pCbbError2 = AmpErrorType();
	if (pParas->m_nSpowerValue_ErrorLogic == 5)//不评估
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbError2->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError2,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
	pCbbError2->setCurrentIndex(pParas->m_nSpowerValue_ErrorLogic);
	}
	//QComboBox *pCbbError3 = AmpErrorType();
	//pCbbError3->setCurrentIndex(pParas->m_nPpowerValue_ErrorLogic);
	//QComboBox *pCbbError4 = AmpErrorType();
	//pCbbError4->setCurrentIndex(pParas->m_nQpowerValue_ErrorLogic);

	pCbbError1->setObjectName("0");
	pCbbError2->setObjectName("1");

	setCellWidget(0, POWERESTIMATE_COL_ERRORTYPE, pCbbError1);
	setCellWidget(1, POWERESTIMATE_COL_ERRORTYPE, pCbbError2);
	//setCellWidget(2, POWERESTIMATE_COL_ERRORTYPE, pCbbError3);
	//setCellWidget(3, POWERESTIMATE_COL_ERRORTYPE, pCbbError4);

	ComboxModelStyle(pCbbError1);
	ComboxModelStyle(pCbbError2);
	//ComboxModelStyle(pCbbError3);
	//ComboxModelStyle(pCbbError4);

	//setItem(0, 2, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_RelErr)));
	//setItem(1, 2, new QTableWidgetItem(QString::number(pParas->m_fUActVal_RelErr)));
	//setItem(2, 2, new QTableWidgetItem(QString::number(pParas->m_fPActVal_RelErr)));
	//setItem(3, 2, new QTableWidgetItem(QString::number(pParas->m_fRetCoef_RelErr)));

	//setItem(0, 3, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_AbsErr)));
	//setItem(1, 3, new QTableWidgetItem(QString::number(pParas->m_fUActVal_AbsErr)));
	//setItem(2, 3, new QTableWidgetItem(QString::number(pParas->m_fPActVal_AbsErr)));
	//setItem(3, 3, new QTableWidgetItem(QString::number(pParas->m_fRetCoef_AbsErr)));

	//setItem(0, 4, new QTableWidgetItem(QString::number(pParas->m_fTimeSet)));
	//setItem(1, 4, new QTableWidgetItem(QString::number(pParas->m_fUSet)));
	//setItem(2, 4, new QTableWidgetItem(QString::number(pParas->m_fPSet)));
	//setItem(3, 4, new QTableWidgetItem(QString::number(pParas->m_fRetCoefSet)));

	//20240805 gongyiping
	//创建定值关联控件
	setItem(0, POWERESTIMATE_COL_RELERROR, new QSettingItem(this));
	setItem(1, POWERESTIMATE_COL_RELERROR, new QSettingItem(this));
	//setItem(2, POWERESTIMATE_COL_RELERROR, new QSettingItem(this));
	//setItem(3, POWERESTIMATE_COL_RELERROR, new QSettingItem(this));

	((QSettingItem*)item(0, POWERESTIMATE_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_RelErr));
	((QSettingItem*)item(1, POWERESTIMATE_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fSpowerValue_RelErr));
	//((QSettingItem*)item(2, POWERESTIMATE_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fPpowerValue_RelErr));
	//((QSettingItem*)item(3, POWERESTIMATE_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fQpowerValue_RelErr));

	setItem(0, POWERESTIMATE_COL_ABSERRORPOS, new QSettingItem(this));
	setItem(1, POWERESTIMATE_COL_ABSERRORPOS, new QSettingItem(this));
	//setItem(2, POWERESTIMATE_COL_ABSERRORPOS, new QSettingItem(this));
	//setItem(3, POWERESTIMATE_COL_ABSERRORPOS, new QSettingItem(this));

	((QSettingItem*)item(0, POWERESTIMATE_COL_ABSERRORPOS))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_AbsErrPos));
	((QSettingItem*)item(1, POWERESTIMATE_COL_ABSERRORPOS))->UpdateStructText(CVariantDataAddress(&pParas->m_fSpowerValue_AbsErr));
	//((QSettingItem*)item(2, POWERESTIMATE_COL_ABSERRORPOS))->UpdateStructText(CVariantDataAddress(&pParas->m_fPpowerValue_AbsErr));
	//((QSettingItem*)item(3, POWERESTIMATE_COL_ABSERRORPOS))->UpdateStructText(CVariantDataAddress(&pParas->m_fQpowerValue_AbsErr));

	setItem(0, POWERESTIMATE_COL_ABSERRORNEG, new QSettingItem(this));
	((QSettingItem*)item(0, POWERESTIMATE_COL_ABSERRORNEG))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_AbsErrNeg));

	setItem(0, POWERESTIMATE_COL_SETVALUE, new QSettingItem(this));
	setItem(1, POWERESTIMATE_COL_SETVALUE, new QSettingItem(this));
	//setItem(2, POWERESTIMATE_COL_SETVALUE, new QSettingItem(this));
	//setItem(3, POWERESTIMATE_COL_SETVALUE, new QSettingItem(this));

	((QSettingItem*)item(0, POWERESTIMATE_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeSet));
	((QSettingItem*)item(1, POWERESTIMATE_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fSpowerSet));
	//((QSettingItem*)item(2, POWERESTIMATE_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fPpowerSet));
	//((QSettingItem*)item(3, POWERESTIMATE_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fQpowerSet));


	for (int i = 0 ;i < 6 ;i++)
	{
		if (i != POWERESTIMATE_COL_ERRORTYPE)
		{
			item(0,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(1,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			//item(2,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			//item(3,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		}
	}

	for (int i = 0;i < 2; i++)
	{
		item(i, POWERESTIMATE_COL_NAME)->setFlags(item(i, POWERESTIMATE_COL_NAME)->flags() & ~Qt::ItemIsEditable);
		EnableRow(i, FALSE);

		//item(i, 2)->setFlags(item(i, 2)->flags() & ~Qt::ItemIsEditable);
		//item(i, 3)->setFlags(item(i, 3)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
	}

	if (pParas->m_bAuto)//自动递变方式时，开放视在功率、有功功率、无功功率
	{
			if (g_pPowerManuTest->m_pPowerManualWidget->m_nChanneType== 0)		
			{
			EnableRow(1);//视在功率
			}
		//else if (g_pPowerManuTest->m_pPowerManualWidget->m_nChanneType== 1)
		//{
		//	EnableRow(2);//有功功率
		//}
		//else
		//{
		//	EnableRow(3);//无功功率
		//}
	}
	EnableRow(0);

	CbbErrorType(0,pCbbError1->currentText());
	CbbErrorType(1,pCbbError2->currentText());
	//CbbErrorType(2,pCbbError3->currentText());
	//CbbErrorType(3,pCbbError4->currentText());



	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(pCbbError1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	/*connect(pCbbError3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError4, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));*/
}

void PowerEstimateGrid::CbbErrorType(int nIndex, CString strText)
{
	if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		//item(nIndex, POWERESTIMATE_COL_RELERROR)->setFlags(item(nIndex, POWERESTIMATE_COL_RELERROR)->flags() & ~Qt::ItemIsEditable);
		//item(nIndex, POWERESTIMATE_COL_ABSERRORPOS)->setFlags(item(nIndex, POWERESTIMATE_COL_ABSERRORPOS)->flags() & ~Qt::ItemIsEditable);
		//if (nIndex == 0)
		//{
		//	item(nIndex, POWERESTIMATE_COL_ABSERRORNEG)->setFlags(item(nIndex, POWERESTIMATE_COL_ABSERRORNEG)->flags() & ~Qt::ItemIsEditable);
		//}
		SetItemEnable(nIndex, POWERESTIMATE_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORPOS, FALSE);
		if (nIndex == 0)
		{
			SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORNEG, FALSE);
		}
	}
	else if (strText==g_sLangTxt_StateEstimate_AbsError)//绝对误差
	{

		//item(nIndex, POWERESTIMATE_COL_RELERROR)->setFlags(item(nIndex, POWERESTIMATE_COL_RELERROR)->flags() & ~Qt::ItemIsEditable);
		//item(nIndex, POWERESTIMATE_COL_ABSERRORPOS)->setFlags(item(nIndex, POWERESTIMATE_COL_ABSERRORPOS)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		//if (nIndex == 0)
		//{
		//	item(nIndex, POWERESTIMATE_COL_ABSERRORNEG)->setFlags(item(nIndex, POWERESTIMATE_COL_ABSERRORNEG)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		//}
		SetItemEnable(nIndex, POWERESTIMATE_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORPOS, TRUE);
		if (nIndex == 0)
		{
			SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORNEG, TRUE);
		}
	}
	else if (strText==g_sLangTxt_StateEstimate_RelError)//相对误差
	{
		//item(nIndex, POWERESTIMATE_COL_RELERROR)->setFlags(item(nIndex, POWERESTIMATE_COL_RELERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		//item(nIndex, POWERESTIMATE_COL_ABSERRORPOS)->setFlags(item(nIndex, POWERESTIMATE_COL_ABSERRORPOS)->flags() & ~Qt::ItemIsEditable);
		//if (nIndex == 0)
		//{
		//	item(nIndex, POWERESTIMATE_COL_ABSERRORNEG)->setFlags(item(nIndex, POWERESTIMATE_COL_ABSERRORNEG)->flags() & ~Qt::ItemIsEditable);
		//}

		SetItemEnable(nIndex, POWERESTIMATE_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORPOS, FALSE);
		if (nIndex == 0)
		{
			SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORNEG, FALSE);
		}
	}
	else
	{
		/*item(nIndex, POWERESTIMATE_COL_RELERROR)->setFlags(item(nIndex, POWERESTIMATE_COL_RELERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		item(nIndex, POWERESTIMATE_COL_ABSERRORPOS)->setFlags(item(nIndex, POWERESTIMATE_COL_ABSERRORPOS)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		if (nIndex == 0)
		{
			item(nIndex, POWERESTIMATE_COL_ABSERRORNEG)->setFlags(item(nIndex, POWERESTIMATE_COL_ABSERRORNEG)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		}*/
		SetItemEnable(nIndex, POWERESTIMATE_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORPOS, TRUE);
		if (nIndex == 0)
		{
			SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORNEG, TRUE);
		}
	}
	if (nIndex != 0)
	{
		SetItemEnable(nIndex, POWERESTIMATE_COL_ABSERRORNEG, FALSE);
	}
}

void PowerEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void PowerEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	QObject *senderObj = sender();
	CString strName;
	if (senderObj) 
	{
		strName = senderObj->objectName();
	}
	CbbErrorType(strName.toInt(), strText);
}

void PowerEstimateGrid::slot_OnCellChanged(int row,int col)
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

	if (col == POWERESTIMATE_COL_RELERROR)//相对误差
	{
		fv=setLimit(0,100,fv);
		pItem->setText(QString::number(fv));
	}

	if (col == POWERESTIMATE_COL_ABSERRORPOS)//绝对误差
	{
		fv=setLimit(0,200,fv);
		pItem->setText(QString::number(fv));	
	}

	if (col == POWERESTIMATE_COL_SETVALUE)//整定值
	{
		if (row==0)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==1)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==2)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));
		}
		
		if (row == 3)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));

		}
		if (row==4)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));
		}
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

bool PowerEstimateGrid::eventFilter(QObject *obj, QEvent *event)
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

void PowerEstimateGrid::mousePressEvent(QMouseEvent * event)
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

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240808 
PowerManualEstimateDlg::PowerManualEstimateDlg(tmt_PowerManuParas* pParas, QWidget* parent) : QDialog(parent)
{
	Stt_Global_SettingParent(this);	//20240808 gongyipng
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
}

PowerManualEstimateDlg::~PowerManualEstimateDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
}

void PowerManualEstimateDlg::InitUI()
{
	CString strTitle = g_sLangTxt_StateEstimate_ResultEstimate; 
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new PowerEstimateGrid(2, 6, this);
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
		resize(850, 450);
	}
	else
	{
	resize(850, 200);
	}
#else
	resize(850, 200);
#endif
}

void PowerManualEstimateDlg::slot_btnOK_Clicked()
{
//20240808 gongyiping 结构体数据在序列化保存时保存了定值关联，待测试
	if (!((QSettingItem*)m_pGrid->item(0, POWERESTIMATE_COL_RELERROR))->IsSetting())
		m_pParas->m_fTimeValue_RelErr = m_pGrid->item(0, POWERESTIMATE_COL_RELERROR)->text().toFloat();
		
	if (!((QSettingItem*)m_pGrid->item(1, POWERESTIMATE_COL_RELERROR))->IsSetting())
		m_pParas->m_fSpowerValue_RelErr = m_pGrid->item(1, POWERESTIMATE_COL_RELERROR)->text().toFloat();
		
	/*if (!((QSettingItem*)m_pGrid->item(2, POWERESTIMATE_COL_RELERROR))->IsSetting())
		m_pParas->m_fSpowerValue_RelErr = m_pGrid->item(1, POWERESTIMATE_COL_RELERROR)->text().toFloat();
		
	if (!((QSettingItem*)m_pGrid->item(3, POWERESTIMATE_COL_RELERROR))->IsSetting())
		m_pParas->m_fSpowerValue_RelErr = m_pGrid->item(1, POWERESTIMATE_COL_RELERROR)->text().toFloat();*/
	
	if (!((QSettingItem*)m_pGrid->item(0, POWERESTIMATE_COL_ABSERRORPOS))->IsSetting())
		m_pParas->m_fTimeValue_AbsErrPos = m_pGrid->item(0, POWERESTIMATE_COL_ABSERRORPOS)->text().toFloat();
	
	if (!((QSettingItem*)m_pGrid->item(1, POWERESTIMATE_COL_ABSERRORPOS))->IsSetting())
		m_pParas->m_fSpowerValue_AbsErr = m_pGrid->item(1, POWERESTIMATE_COL_ABSERRORPOS)->text().toFloat();

	/*if (!((QSettingItem*)m_pGrid->item(2, POWERESTIMATE_COL_ABSERRORPOS))->IsSetting())
		m_pParas->m_fPpowerValue_AbsErr = m_pGrid->item(2, POWERESTIMATE_COL_ABSERRORPOS)->text().toFloat();

	if (!((QSettingItem*)m_pGrid->item(3, POWERESTIMATE_COL_ABSERRORPOS))->IsSetting())
		m_pParas->m_fQpowerValue_AbsErr = m_pGrid->item(3, POWERESTIMATE_COL_ABSERRORPOS)->text().toFloat();
*/
	if (!((QSettingItem*)m_pGrid->item(0, POWERESTIMATE_COL_ABSERRORNEG))->IsSetting())
		m_pParas->m_fTimeValue_AbsErrNeg = m_pGrid->item(0, POWERESTIMATE_COL_ABSERRORNEG)->text().toFloat();

	m_pParas->m_nTimeValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(0, POWERESTIMATE_COL_ERRORTYPE))->currentIndex();

	if (((QComboBox*)m_pGrid->cellWidget(1, POWERESTIMATE_COL_ERRORTYPE))->currentIndex() == 4)//选中的是不评估，发送的值为5
	{
		m_pParas->m_nSpowerValue_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nSpowerValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(1, POWERESTIMATE_COL_ERRORTYPE))->currentIndex();
	}
	/*m_pParas->m_nPpowerValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(2, POWERESTIMATE_COL_ERRORTYPE))->currentIndex();
	m_pParas->m_nQpowerValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(3, POWERESTIMATE_COL_ERRORTYPE))->currentIndex();*/

	if (!((QSettingItem*)m_pGrid->item(0, POWERESTIMATE_COL_SETVALUE))->IsSetting())
		m_pParas->m_fTimeSet = m_pGrid->item(0, POWERESTIMATE_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, POWERESTIMATE_COL_SETVALUE))->IsSetting())
		m_pParas->m_fSpowerSet = m_pGrid->item(1, POWERESTIMATE_COL_SETVALUE)->text().toFloat();
	/*if (!((QSettingItem*)m_pGrid->item(2, POWERESTIMATE_COL_SETVALUE))->IsSetting())
		m_pParas->m_fPpowerSet = m_pGrid->item(2, POWERESTIMATE_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3, POWERESTIMATE_COL_SETVALUE))->IsSetting())
		m_pParas->m_fQpowerSet = m_pGrid->item(3, POWERESTIMATE_COL_SETVALUE)->text().toFloat();*/

	accept();
}

void PowerManualEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}