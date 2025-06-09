#include "ManualEstimateDlg.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "SttMacroParaEditViewManual.h"
#include "../../XLangResource_Native.h"
#include <QApplication>
#include "../SttTestCntrFrameBase.h"

#ifdef _PSX_QT_WINDOWS_
//#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
//#include "../SttTestCntrFrameBase.h"
#endif


#define  MANUALESTIMATE_COL_NAME				0		//名称
#define  MANUALESTIMATE_COL_SETVALUE			1		//整定值
#define  MANUALESTIMATE_COL_ERRORTYPE			2		//误差类型
#define  MANUALESTIMATE_COL_RELERROR			3		//相对误差
#define  MANUALESTIMATE_COL_ABSERROR			4		//绝对误差
#define  MANUALESTIMATE_COL_NEGATIVEABSERROR	5		//绝对误差(-)

ManualEstimateGrid::ManualEstimateGrid(int rows, int columns, QWidget* parent) : QScrollTableWidget(parent)	//QTableWidget(rows, columns, parent)//20240807 huangliang 
{
	//20240807 huangliang 
	setRowCount(rows);
	setColumnCount(columns);

	m_bRunning = FALSE;
	installEventFilter(this);
}

ManualEstimateGrid::~ManualEstimateGrid()
{

}

void ManualEstimateGrid::InitGrid()
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

QComboBox* ManualEstimateGrid::NewErrorType()
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

QComboBox* ManualEstimateGrid::AbsErrorType()
{
	QComboBox *pCbbError = new QComboBox(this);
	
	pCbbError->addItem(g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
	return pCbbError;
}

void ManualEstimateGrid::EnableRow(long nIndex, BOOL bEnabled)
{
	if (nIndex >= rowCount())
	{
		return;
	}

	QComboBox* pCbb = (QComboBox*)cellWidget(nIndex, MANUALESTIMATE_COL_ERRORTYPE);
	pCbb->setEnabled(bEnabled);
	if (bEnabled)
	{
// 		QTableWidgetItem* pItem = pItem = item(nIndex, MANUALESTIMATE_COL_RELERROR);
// 		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
// 		pItem = item(nIndex, MANUALESTIMATE_COL_ABSERROR);
// 		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
// 		pItem->setForeground(Qt::black);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_ABSERROR, TRUE);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_NEGATIVEABSERROR, TRUE);
	}
	else
	{
// 		QTableWidgetItem* pItem = pItem = item(nIndex, MANUALESTIMATE_COL_RELERROR);
// 		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
// 		pItem = item(nIndex, MANUALESTIMATE_COL_ABSERROR);
// 		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
// 		pItem->setForeground(Qt::gray);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_ABSERROR, FALSE);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_NEGATIVEABSERROR, FALSE);
	}
}

void ManualEstimateGrid::SetItemEnable(int nRow, int nCol, BOOL bEnable)
{
	QTableWidgetItem *pItem = item(nRow, nCol);
	if (!pItem)
	{
		return;
	}

	bool bCbbState = true;
	if (nCol == MANUALESTIMATE_COL_RELERROR || nCol == MANUALESTIMATE_COL_ABSERROR || nCol == MANUALESTIMATE_COL_NEGATIVEABSERROR)
	{
		QComboBox* pCbb = (QComboBox*)cellWidget(nRow, MANUALESTIMATE_COL_ERRORTYPE);
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

void ManualEstimateGrid::InitData(tmt_ManualParas* pParas)
{
	m_pParas=pParas;
	CString strText; 
	strText = /* "动作时间s)" */g_sLangTxt_Native_ActionTime;
	setItem(0, MANUALESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	strText = /* "电压动作值?(V)" */g_sLangTxt_Gradient_VActionValue;
	setItem(1, MANUALESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	strText = /* "电流动作值(A)" */g_sLangTxt_Gradient_CActionValue;
	setItem(2, MANUALESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	strText = /* "频率动作值?(Hz)" */g_sLangTxt_Gradient_FreAValue;
	setItem(3, MANUALESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	strText = /* "相位动作值(°) */g_sLangTxt_Gradient_PhaseAValue;
	setItem(4, MANUALESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	strText = /* "返回系数" */g_sLangTxt_Gradient_ReCoefficient;
	setItem(5, MANUALESTIMATE_COL_NAME, new QTableWidgetItem(strText));

	QComboBox *pCbbError1 = NewErrorType();
	pCbbError1->setCurrentIndex(pParas->m_nTimeValue_ErrorLogic);
	QComboBox *pCbbError2 = NewErrorType();
	pCbbError2->setCurrentIndex(pParas->m_nUActVal_ErrorLogic);
	QComboBox *pCbbError3 = NewErrorType();
	pCbbError3->setCurrentIndex(pParas->m_nIActVal_ErrorLogic);

	QComboBox *pCbbError4 = AbsErrorType();
	if (pParas->m_nHzActVal_ErrorLogic == 5)
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbError4->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError4,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
	pCbbError4->setCurrentIndex(pParas->m_nHzActVal_ErrorLogic);
	}

	QComboBox *pCbbError5 = AbsErrorType();
	if (pParas->m_nAngleActVal_ErrorLogic == 5)
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbError5->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError5,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
	pCbbError5->setCurrentIndex(pParas->m_nAngleActVal_ErrorLogic);
	}

	QComboBox *pCbbError6 = AbsErrorType();
	if (pParas->m_nRetCoef_ErrorLogic == 5)
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbError6->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError6,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
	pCbbError6->setCurrentIndex(pParas->m_nRetCoef_ErrorLogic);
	}
	
	setCellWidget(0, MANUALESTIMATE_COL_ERRORTYPE, pCbbError1);
	setCellWidget(1, MANUALESTIMATE_COL_ERRORTYPE, pCbbError2);
	setCellWidget(2, MANUALESTIMATE_COL_ERRORTYPE, pCbbError3);
	setCellWidget(3, MANUALESTIMATE_COL_ERRORTYPE, pCbbError4);
	setCellWidget(4, MANUALESTIMATE_COL_ERRORTYPE, pCbbError5);
	setCellWidget(5, MANUALESTIMATE_COL_ERRORTYPE, pCbbError6);

	ComboxModelStyle(pCbbError1);
	ComboxModelStyle(pCbbError2);
	ComboxModelStyle(pCbbError3);
	ComboxModelStyle(pCbbError4);
	ComboxModelStyle(pCbbError5);
	ComboxModelStyle(pCbbError6);

 	//setItem(0, 2, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_RelErr)));
 	//setItem(1, 2, new QTableWidgetItem(QString::number(pParas->m_fUActVal_RelErr)));
 	//setItem(2, 2, new QTableWidgetItem(QString::number(pParas->m_fIActVal_RelErr)));
 	//setItem(3, 2, new QTableWidgetItem(QString::number(pParas->m_fHzActVal_RelErr)));
 	//setItem(4, 2, new QTableWidgetItem(QString::number(pParas->m_fAngleActVal_RelErr)));
 	//setItem(5, 2, new QTableWidgetItem(QString::number(pParas->m_fRetCoef_RelErr)));
 	//
 	//setItem(0, 3, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_AbsErr)));
 	//setItem(1, 3, new QTableWidgetItem(QString::number(pParas->m_fUActVal_AbsErr)));
 	//setItem(2, 3, new QTableWidgetItem(QString::number(pParas->m_fIActVal_AbsErr)));
 	//setItem(3, 3, new QTableWidgetItem(QString::number(pParas->m_fHzActVal_AbsErr)));
 	//setItem(4, 3, new QTableWidgetItem(QString::number(pParas->m_fAngleActVal_AbsErr)));
 	//setItem(5, 3, new QTableWidgetItem(QString::number(pParas->m_fRetCoef_AbsErr)));
 	
 	//setItem(0, 4, new QTableWidgetItem(QString::number(pParas->m_fTimeSet)));
 	//setItem(1, 4, new QTableWidgetItem(QString::number(pParas->m_fUSet)));
 	//setItem(2, 4, new QTableWidgetItem(QString::number(pParas->m_fISet)));
 	//setItem(3, 4, new QTableWidgetItem(QString::number(pParas->m_fHzSet)));
 	//setItem(4, 4, new QTableWidgetItem(QString::number(pParas->m_fAngleSet)));
 	//setItem(5, 4, new QTableWidgetItem(QString::number(pParas->m_fRetCoefSet)));

	//20240807 huangliang 
	strText = "——";
	setItem(0, MANUALESTIMATE_COL_RELERROR, new QSettingItem(this));
	((QSettingItem*)item(0, MANUALESTIMATE_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_RelErr));
	setItem(1, MANUALESTIMATE_COL_RELERROR, new QSettingItem(this));
	((QSettingItem*)item(1, MANUALESTIMATE_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_RelErr));
	setItem(2, MANUALESTIMATE_COL_RELERROR, new QSettingItem(this));
	((QSettingItem*)item(2, MANUALESTIMATE_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_RelErr));
	setItem(3, MANUALESTIMATE_COL_RELERROR, new QSettingItem(this));
	((QSettingItem*)item(3, MANUALESTIMATE_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fHzActVal_RelErr));
	setItem(4, MANUALESTIMATE_COL_RELERROR, new QSettingItem(this));
	((QSettingItem*)item(4, MANUALESTIMATE_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleActVal_RelErr));
	setItem(5, MANUALESTIMATE_COL_RELERROR, new QSettingItem(this));
	((QSettingItem*)item(5, MANUALESTIMATE_COL_RELERROR))->UpdateText(strText);
	//((QSettingItem*)item(5, MANUALESTIMATE_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fRetCoef_RelErr));

	setItem(0, MANUALESTIMATE_COL_ABSERROR, new QSettingItem(this));
	((QSettingItem*)item(0, MANUALESTIMATE_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_AbsErr));
	setItem(1, MANUALESTIMATE_COL_ABSERROR, new QSettingItem(this));
	((QSettingItem*)item(1, MANUALESTIMATE_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_AbsErr));
	setItem(2, MANUALESTIMATE_COL_ABSERROR, new QSettingItem(this));
	((QSettingItem*)item(2, MANUALESTIMATE_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_AbsErr));
	setItem(3, MANUALESTIMATE_COL_ABSERROR, new QSettingItem(this));
	((QSettingItem*)item(3, MANUALESTIMATE_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fHzActVal_AbsErr));
	setItem(4, MANUALESTIMATE_COL_ABSERROR, new QSettingItem(this));
	((QSettingItem*)item(4, MANUALESTIMATE_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleActVal_AbsErr));
	setItem(5, MANUALESTIMATE_COL_ABSERROR, new QSettingItem(this));
	((QSettingItem*)item(5, MANUALESTIMATE_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fRetCoef_AbsErr));

	setItem(0, MANUALESTIMATE_COL_SETVALUE, new QSettingItem(this));
	((QSettingItem*)item(0, MANUALESTIMATE_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeSet));
	setItem(1, MANUALESTIMATE_COL_SETVALUE, new QSettingItem(this));
	((QSettingItem*)item(1, MANUALESTIMATE_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fUSet));
	setItem(2, MANUALESTIMATE_COL_SETVALUE, new QSettingItem(this));
	((QSettingItem*)item(2, MANUALESTIMATE_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fISet));
	setItem(3, MANUALESTIMATE_COL_SETVALUE, new QSettingItem(this));
	((QSettingItem*)item(3, MANUALESTIMATE_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fHzSet));
	setItem(4, MANUALESTIMATE_COL_SETVALUE, new QSettingItem(this));
	((QSettingItem*)item(4, MANUALESTIMATE_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleSet));
	setItem(5, MANUALESTIMATE_COL_SETVALUE, new QSettingItem(this));
	((QSettingItem*)item(5, MANUALESTIMATE_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fRetCoefSet));

	//绝对误差(-)
	setItem(0, MANUALESTIMATE_COL_NEGATIVEABSERROR, new QSettingItem(this));
	((QSettingItem*)item(0, MANUALESTIMATE_COL_NEGATIVEABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_AbsErrNeg));
	setItem(1, MANUALESTIMATE_COL_NEGATIVEABSERROR, new QSettingItem(this));
	((QSettingItem*)item(1, MANUALESTIMATE_COL_NEGATIVEABSERROR))->UpdateText(strText);
	setItem(2, MANUALESTIMATE_COL_NEGATIVEABSERROR, new QSettingItem(this));
	((QSettingItem*)item(2, MANUALESTIMATE_COL_NEGATIVEABSERROR))->UpdateText(strText);
	setItem(3, MANUALESTIMATE_COL_NEGATIVEABSERROR, new QSettingItem(this));
	((QSettingItem*)item(3, MANUALESTIMATE_COL_NEGATIVEABSERROR))->UpdateText(strText);
	setItem(4, MANUALESTIMATE_COL_NEGATIVEABSERROR, new QSettingItem(this));
	((QSettingItem*)item(4, MANUALESTIMATE_COL_NEGATIVEABSERROR))->UpdateText(strText);
	setItem(5, MANUALESTIMATE_COL_NEGATIVEABSERROR, new QSettingItem(this));
	((QSettingItem*)item(5, MANUALESTIMATE_COL_NEGATIVEABSERROR))->UpdateText(strText);
 
	for (int nRow = 0; nRow < rowCount(); nRow++)
	{
		for (int i = 0; i < columnCount(); i++)
		{
			if (i == MANUALESTIMATE_COL_NAME)
			{
				item(nRow, i)->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
			}
			else if (i != MANUALESTIMATE_COL_ERRORTYPE)
			{
				item(nRow, i)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			}
		}
	}
	

	for (int i = 0;i < rowCount(); i++)
	{
		item(i, MANUALESTIMATE_COL_NAME)->setFlags(item(i, MANUALESTIMATE_COL_NAME)->flags() & ~Qt::ItemIsEditable);
		EnableRow(i, FALSE);
	}

	if (pParas->m_bAuto)//自动递变方式时，开放动作值、返回系数、相位动作值
	{
		if(pParas->m_nGradientTpSelect==0)//幅值
		{
			if (g_pManualTest->m_strCbbChannel.Find(_T("U")) == 0)		
			{
				EnableRow(1);//电压
			}
			else if (g_pManualTest->m_strCbbChannel.Find(_T("I")) == 0)
			{
				EnableRow(2);//电流
			}
		}

		else if (pParas->m_nGradientTpSelect==1)//相位
		{
			EnableRow(4);
		}
		else if (pParas->m_nGradientTpSelect==2)//频率
		{
			EnableRow(3);
		}
		
		if (pParas->m_manuGradient.nMode==1)
		{
			EnableRow(5);//返回系数
		}
	}
	EnableRow(0);//动作时间

	CbbErrorType(0,pCbbError1->currentText());
	CbbErrorType(1,pCbbError2->currentText());
	CbbErrorType(2,pCbbError3->currentText());
	CbbErrorType(3,pCbbError4->currentText());
	CbbErrorType(4,pCbbError5->currentText());
	CbbErrorType(5,pCbbError6->currentText());
	

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(pCbbError1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError4, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError5, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError6, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
}

void ManualEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}


void ManualEstimateGrid::CbbErrorType(int nIndex, CString strText)
{
	if (strText==g_sLangTxt_StateEstimate_AbsError)//绝对误差
	{
// 		item(nIndex, MANUALESTIMATE_COL_RELERROR)->setFlags(item(nIndex, 2)->flags() & ~Qt::ItemIsEditable);
// 		item(nIndex, MANUALESTIMATE_COL_ABSERROR)->setFlags(item(nIndex, MANUALESTIMATE_COL_ABSERROR)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_ABSERROR, TRUE);
		if (nIndex == 0)
		{
			SetItemEnable(nIndex, MANUALESTIMATE_COL_NEGATIVEABSERROR, TRUE);
		}
		else
		{
			SetItemEnable(nIndex, MANUALESTIMATE_COL_NEGATIVEABSERROR, FALSE);
		}
	}
	else if (strText==g_sLangTxt_StateEstimate_RelError)//相对误差
	{
// 		item(nIndex, MANUALESTIMATE_COL_RELERROR)->setFlags(item(nIndex, MANUALESTIMATE_COL_RELERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
// 		item(nIndex, MANUALESTIMATE_COL_ABSERROR)->setFlags(item(nIndex, MANUALESTIMATE_COL_ABSERROR)->flags() & ~Qt::ItemIsEditable);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_ABSERROR, FALSE);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_NEGATIVEABSERROR, FALSE);
	}
	else if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
// 		item(nIndex, MANUALESTIMATE_COL_RELERROR)->setFlags(item(nIndex, MANUALESTIMATE_COL_RELERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
// 		item(nIndex, MANUALESTIMATE_COL_ABSERROR)->setFlags(item(nIndex, MANUALESTIMATE_COL_ABSERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_ABSERROR, FALSE);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_NEGATIVEABSERROR, FALSE);
	}
	else
	{
		SetItemEnable(nIndex, MANUALESTIMATE_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, MANUALESTIMATE_COL_ABSERROR, TRUE);
		if (nIndex == 0)
		{
		SetItemEnable(nIndex, MANUALESTIMATE_COL_NEGATIVEABSERROR, TRUE);
	}
		else
		{
			SetItemEnable(nIndex, MANUALESTIMATE_COL_NEGATIVEABSERROR, FALSE);
		}
	}
}
void ManualEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	int nRow = currentRow();
	CbbErrorType(nRow,strText);
}

void ManualEstimateGrid::slot_OnCellChanged(int row,int col)
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

	if(col==MANUALESTIMATE_COL_RELERROR)//相对误差
	{
		fv=setLimit(0,100,fv);
		pItem->setText(QString::number(fv));
	}

	if(col==MANUALESTIMATE_COL_ABSERROR)//绝对误差
	{
		fv=setLimit(0,200,fv);
		pItem->setText(QString::number(fv));
	}

	if (row == 0 && col == MANUALESTIMATE_COL_NEGATIVEABSERROR)//绝对误差（-）
	{
		fv = setLimit(0, 200, fv);
		pItem->setText(QString::number(fv));
	}

	if(col==MANUALESTIMATE_COL_SETVALUE)//整定值
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
		if (row==3)
		{
			fv=setLimit(0,1550,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==4)
		{
			fv=setLimit(0,360,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==5)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));
		}
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

bool ManualEstimateGrid::eventFilter(QObject *obj, QEvent *event)
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

void ManualEstimateGrid::mousePressEvent(QMouseEvent * event)
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

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240807 huangliang 
ManualEstimateDlg::ManualEstimateDlg(tmt_ManualParas* pParas, QWidget* parent) : QDialog(parent)
{
	Stt_Global_SettingParent(this);	//20240807 huangliang 
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
}

ManualEstimateDlg::~ManualEstimateDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
}

void ManualEstimateDlg::InitUI()
{
	CString strTitle = g_sLangTxt_StateEstimate_ResultEstimate; 
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new ManualEstimateGrid(6, 6, this);
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
	//2024-8-1 wuxinyi 在2880*1800分辨率显示不全
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

void ManualEstimateDlg::slot_btnOK_Clicked()
{
	//20240807 huangliang 结构体数据在序列化保存时保存了定值关联，待测试
	if (!((QSettingItem*)m_pGrid->item(0, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fTimeValue_RelErr = m_pGrid->item(0, MANUALESTIMATE_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fUActVal_RelErr = m_pGrid->item(1, MANUALESTIMATE_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(2, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fIActVal_RelErr = m_pGrid->item(2, MANUALESTIMATE_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fHzActVal_RelErr = m_pGrid->item(3, MANUALESTIMATE_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(4, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fAngleActVal_RelErr = m_pGrid->item(4, MANUALESTIMATE_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(5, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fRetCoef_RelErr = m_pGrid->item(5, MANUALESTIMATE_COL_RELERROR)->text().toFloat();

	if (!((QSettingItem*)m_pGrid->item(0, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fTimeValue_AbsErr = m_pGrid->item(0, MANUALESTIMATE_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fUActVal_AbsErr = m_pGrid->item(1, MANUALESTIMATE_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(2, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fIActVal_AbsErr = m_pGrid->item(2, MANUALESTIMATE_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fHzActVal_AbsErr = m_pGrid->item(3, MANUALESTIMATE_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(4, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fAngleActVal_AbsErr = m_pGrid->item(4, MANUALESTIMATE_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(5, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fRetCoef_AbsErr = m_pGrid->item(5, MANUALESTIMATE_COL_ABSERROR)->text().toFloat();
	

	if (!((QSettingItem*)m_pGrid->item(0, MANUALESTIMATE_COL_NEGATIVEABSERROR))->IsSetting())
		m_pParas->m_fTimeValue_AbsErrNeg = m_pGrid->item(0, MANUALESTIMATE_COL_NEGATIVEABSERROR)->text().toFloat();

	
	m_pParas->m_nTimeValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(0, MANUALESTIMATE_COL_ERRORTYPE))->currentIndex();
	m_pParas->m_nUActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(1, MANUALESTIMATE_COL_ERRORTYPE))->currentIndex();
	m_pParas->m_nIActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(2, MANUALESTIMATE_COL_ERRORTYPE))->currentIndex();
// 	m_pParas->m_nHzActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(3, MANUALESTIMATE_COL_ERRORTYPE))->currentIndex();
// 	m_pParas->m_nAngleActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(4, MANUALESTIMATE_COL_ERRORTYPE))->currentIndex();
// 	m_pParas->m_nRetCoef_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(5, MANUALESTIMATE_COL_ERRORTYPE))->currentIndex();

	CString strText;
	strText = ((QComboBox*)m_pGrid->cellWidget(3, MANUALESTIMATE_COL_ERRORTYPE))->currentText();
	if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		m_pParas->m_nHzActVal_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nHzActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(3, MANUALESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	strText = ((QComboBox*)m_pGrid->cellWidget(4, MANUALESTIMATE_COL_ERRORTYPE))->currentText();
	if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		m_pParas->m_nAngleActVal_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nAngleActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(4, MANUALESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	strText = ((QComboBox*)m_pGrid->cellWidget(5, MANUALESTIMATE_COL_ERRORTYPE))->currentText();
	if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		m_pParas->m_nRetCoef_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nRetCoef_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(5, MANUALESTIMATE_COL_ERRORTYPE))->currentIndex();
	}


	if (!((QSettingItem*)m_pGrid->item(0, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fTimeSet = m_pGrid->item(0, MANUALESTIMATE_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fUSet = m_pGrid->item(1, MANUALESTIMATE_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(2, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fISet = m_pGrid->item(2, MANUALESTIMATE_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fHzSet = m_pGrid->item(3, MANUALESTIMATE_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(4, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fAngleSet = m_pGrid->item(4, MANUALESTIMATE_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(5, MANUALESTIMATE_COL_RELERROR))->IsSetting())
	m_pParas->m_fRetCoefSet = m_pGrid->item(5, MANUALESTIMATE_COL_SETVALUE)->text().toFloat();

	accept();
}

void ManualEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}
