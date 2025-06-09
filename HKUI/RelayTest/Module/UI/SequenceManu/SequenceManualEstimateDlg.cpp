#include "SequenceManualEstimateDlg.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "SttMacroParaEditViewSequenceManu.h"
#include "../../XLangResource_Native.h"
#include <QApplication>
#include "../SttTestCntrFrameBase.h"

#ifdef _PSX_QT_WINDOWS_
//#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
//#include "../SttTestCntrFrameBase.h"
#endif

#define  SEQUENCEESTIMATEGRID_COL_NAME				0		//名称
#define  SEQUENCEESTIMATEGRID_COL_SETVALUE			1		//整定值
#define  SEQUENCEESTIMATEGRID_COL_ERRORTYPE			2		//误差类型
#define  SEQUENCEESTIMATEGRID_COL_RELERROR			3		//相对误差
#define  SEQUENCEESTIMATEGRID_COL_ABSERROR			4		//绝对误差
#define  SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR	5		//绝对误差(-)

SequenceEstimateGrid::SequenceEstimateGrid(int rows, int columns, QWidget* parent) :QScrollTableWidget(parent)	//QTableWidget(rows, columns, parent)//20240808 gongyiping
{
	//20240808 gongyiping
	setRowCount(rows);
	setColumnCount(columns);

	m_bRunning = FALSE;
	installEventFilter(this);

}

SequenceEstimateGrid::~SequenceEstimateGrid()
{

}

void SequenceEstimateGrid::InitGrid()
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

QComboBox* SequenceEstimateGrid::NewErrorType()
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

QComboBox* SequenceEstimateGrid::AbsErrorType()
{
	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
	return pCbbError;
}

void SequenceEstimateGrid::EnableRow(long nIndex, BOOL bEnabled)
{
	if(nIndex >= rowCount())
	{
		return;
	}

	QComboBox* pCbb = (QComboBox*)cellWidget(nIndex, SEQUENCEESTIMATEGRID_COL_ERRORTYPE);
	pCbb->setEnabled(bEnabled);
	if(bEnabled)
	{
// 		QTableWidgetItem* pItem = pItem = item(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR);
// 		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
// 		pItem = item(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR);
// 		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR, TRUE);
	}
	else
	{
// 		QTableWidgetItem* pItem = pItem = item(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR);
// 		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
// 		pItem = item(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR);
// 		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR, TRUE);
	}
}

void SequenceEstimateGrid::InitData(tmt_SequenceManuParas* pParas)
{
	m_pParas=pParas;
	CString strText; 
	strText = /*"动作时间(s)"*/g_sLangTxt_Native_ActionTime;
	setItem(0, SEQUENCEESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));
	strText = /*"电压动作值(V)"*/g_sLangTxt_Gradient_VActionValue;
	setItem(1, SEQUENCEESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));
	strText = /*"电流动作值(A)"*/g_sLangTxt_Gradient_CActionValue;
	setItem(2, SEQUENCEESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));
// 	strText = /* "频率动作值?(Hz)" */g_sLangTxt_Gradient_FreAValue;
// 	setItem(3, SEQUENCEESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));
	strText = /*"相位动作值(°)"*/g_sLangTxt_Gradient_PhaseAValue;
	setItem(3, SEQUENCEESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));
	strText = /*"返回系数"*/g_sLangTxt_Gradient_ReCoefficient;
	setItem(4, SEQUENCEESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));

	QComboBox *pCbbError1 = NewErrorType();
	pCbbError1->setCurrentIndex(pParas->m_nTimeValue_ErrorLogic);
	QComboBox *pCbbError2 = NewErrorType();
	pCbbError2->setCurrentIndex(pParas->m_nUActVal_ErrorLogic);
	QComboBox *pCbbError3 = NewErrorType();
	pCbbError3->setCurrentIndex(pParas->m_nIActVal_ErrorLogic);

//	QComboBox *pCbbError4 = AbsErrorType();
//	if (pParas->m_nHzActVal_ErrorLogic == 5)
//	{
//#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//		pCbbError4->setCurrentText(g_sLangTxt_Distance_ErrorNot);
//#else
//		Stt_Global_SetComboBoxIndexByText(pCbbError4,g_sLangTxt_Distance_ErrorNot);
//#endif
//	}
//	else
//	{
//	pCbbError4->setCurrentIndex(pParas->m_nHzActVal_ErrorLogic);
//	}

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
		pCbbError5->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError5,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
	pCbbError6->setCurrentIndex(pParas->m_nRetCoef_ErrorLogic);
	}

	setCellWidget(0, SEQUENCEESTIMATEGRID_COL_ERRORTYPE, pCbbError1);
	setCellWidget(1, SEQUENCEESTIMATEGRID_COL_ERRORTYPE, pCbbError2);
	setCellWidget(2, SEQUENCEESTIMATEGRID_COL_ERRORTYPE, pCbbError3);
// 	setCellWidget(3, SEQUENCEESTIMATEGRID_COL_ERRORTYPE, pCbbError4);
	setCellWidget(3, SEQUENCEESTIMATEGRID_COL_ERRORTYPE, pCbbError5);
	setCellWidget(4, SEQUENCEESTIMATEGRID_COL_ERRORTYPE, pCbbError6);

	ComboxModelStyle(pCbbError1);
	ComboxModelStyle(pCbbError2);
	ComboxModelStyle(pCbbError3);
// 	ComboxModelStyle(pCbbError4);
	ComboxModelStyle(pCbbError5);
	ComboxModelStyle(pCbbError6);

	//setItem(0, 2, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_RelErr)));
	//setItem(1, 2, new QTableWidgetItem(QString::number(pParas->m_fUActVal_RelErr)));
	//setItem(2, 2, new QTableWidgetItem(QString::number(pParas->m_fIActVal_RelErr)));
	////setItem(3, 2, new QTableWidgetItem(QString::number(pParas->m_fHzActVal_RelErr)));
	//setItem(3, 2, new QTableWidgetItem(QString::number(pParas->m_fAngleActVal_RelErr)));
	//setItem(4, 2, new QTableWidgetItem(QString::number(pParas->m_fRetCoef_RelErr)));

	//setItem(0, 3, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_AbsErr)));
	//setItem(1, 3, new QTableWidgetItem(QString::number(pParas->m_fUActVal_AbsErr)));
	//setItem(2, 3, new QTableWidgetItem(QString::number(pParas->m_fIActVal_AbsErr)));
	////setItem(3, 3, new QTableWidgetItem(QString::number(pParas->m_fHzActVal_AbsErr)));
	//setItem(3, 3, new QTableWidgetItem(QString::number(pParas->m_fAngleActVal_AbsErr)));
	//setItem(4, 3, new QTableWidgetItem(QString::number(pParas->m_fRetCoef_AbsErr)));

	//setItem(0, 4, new QTableWidgetItem(QString::number(pParas->m_fTimeSet)));
	//setItem(1, 4, new QTableWidgetItem(QString::number(pParas->m_fUSet)));
	//setItem(2, 4, new QTableWidgetItem(QString::number(pParas->m_fISet)));
	////setItem(3, 4, new QTableWidgetItem(QString::number(pParas->m_fHzSet)));
	//setItem(3, 4, new QTableWidgetItem(QString::number(pParas->m_fAngleSet)));
	//setItem(4, 4, new QTableWidgetItem(QString::number(pParas->m_fRetCoefSet)));

	//20240802 gongyiping
	//创建定值关联控件
	setItem(0, SEQUENCEESTIMATEGRID_COL_RELERROR, new QSettingItem(this));
	setItem(1, SEQUENCEESTIMATEGRID_COL_RELERROR, new QSettingItem(this));
	setItem(2, SEQUENCEESTIMATEGRID_COL_RELERROR, new QSettingItem(this));
// 	setItem(3, SEQUENCEESTIMATEGRID_COL_RELERROR, new QSettingItem(this));
	setItem(3, SEQUENCEESTIMATEGRID_COL_RELERROR, new QSettingItem(this));
	setItem(4, SEQUENCEESTIMATEGRID_COL_RELERROR, new QSettingItem(this));

	strText = "——";
	((QSettingItem*)item(0, SEQUENCEESTIMATEGRID_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_RelErr));
	((QSettingItem*)item(1, SEQUENCEESTIMATEGRID_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_RelErr));
	((QSettingItem*)item(2, SEQUENCEESTIMATEGRID_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_RelErr));
// 	((QSettingItem*)item(3, SEQUENCEESTIMATEGRID_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fHzActVal_RelErr));
	((QSettingItem*)item(3, SEQUENCEESTIMATEGRID_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleActVal_RelErr));
// 	((QSettingItem*)item(5, SEQUENCEESTIMATEGRID_COL_RELERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fRetCoef_RelErr));
 	((QSettingItem*)item(4, SEQUENCEESTIMATEGRID_COL_RELERROR))->UpdateText(strText);


	setItem(0, SEQUENCEESTIMATEGRID_COL_ABSERROR, new QSettingItem(this));
	setItem(1, SEQUENCEESTIMATEGRID_COL_ABSERROR, new QSettingItem(this));
	setItem(2, SEQUENCEESTIMATEGRID_COL_ABSERROR, new QSettingItem(this));
// 	setItem(3, SEQUENCEESTIMATEGRID_COL_ABSERROR, new QSettingItem(this));
	setItem(3, SEQUENCEESTIMATEGRID_COL_ABSERROR, new QSettingItem(this));
	setItem(4, SEQUENCEESTIMATEGRID_COL_ABSERROR, new QSettingItem(this));

	((QSettingItem*)item(0, SEQUENCEESTIMATEGRID_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_AbsErr));
	((QSettingItem*)item(1, SEQUENCEESTIMATEGRID_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_AbsErr));
	((QSettingItem*)item(2, SEQUENCEESTIMATEGRID_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_AbsErr));
// 	((QSettingItem*)item(3, SEQUENCEESTIMATEGRID_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fHzActVal_AbsErr));
	((QSettingItem*)item(3, SEQUENCEESTIMATEGRID_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleActVal_AbsErr));
	((QSettingItem*)item(4, SEQUENCEESTIMATEGRID_COL_ABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fRetCoef_AbsErr));

	setItem(0, SEQUENCEESTIMATEGRID_COL_SETVALUE, new QSettingItem(this));
	setItem(1, SEQUENCEESTIMATEGRID_COL_SETVALUE, new QSettingItem(this));
	setItem(2, SEQUENCEESTIMATEGRID_COL_SETVALUE, new QSettingItem(this));
// 	setItem(3, SEQUENCEESTIMATEGRID_COL_SETVALUE, new QSettingItem(this));
	setItem(3, SEQUENCEESTIMATEGRID_COL_SETVALUE, new QSettingItem(this));
	setItem(4, SEQUENCEESTIMATEGRID_COL_SETVALUE, new QSettingItem(this));

	((QSettingItem*)item(0, SEQUENCEESTIMATEGRID_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeSet));
	((QSettingItem*)item(1, SEQUENCEESTIMATEGRID_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fUSet));
	((QSettingItem*)item(2, SEQUENCEESTIMATEGRID_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fISet));
// 	((QSettingItem*)item(3, SEQUENCEESTIMATEGRID_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fHzSet));
	((QSettingItem*)item(3, SEQUENCEESTIMATEGRID_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleSet));
	((QSettingItem*)item(4, SEQUENCEESTIMATEGRID_COL_SETVALUE))->UpdateStructText(CVariantDataAddress(&pParas->m_fRetCoefSet));

	setItem(0, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR, new QSettingItem(this));
	setItem(1, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR, new QSettingItem(this));
	setItem(2, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR, new QSettingItem(this));
// 	setItem(3, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR, new QSettingItem(this));
	setItem(3, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR, new QSettingItem(this));
	setItem(4, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR, new QSettingItem(this));

	((QSettingItem*)item(0, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_AbsErrNeg));
	((QSettingItem*)item(1, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR))->UpdateText(strText);
	((QSettingItem*)item(2, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR))->UpdateText(strText);
// 	((QSettingItem*)item(3, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR))->UpdateText(strText);
	((QSettingItem*)item(3, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR))->UpdateText(strText);
	((QSettingItem*)item(4, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR))->UpdateText(strText);

	for (int nRow = 0; nRow < rowCount(); nRow++)
	{
// 		if (i != SEQUENCEESTIMATEGRID_COL_ERRORTYPE)
// 		{
// 			item(0,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 			item(1,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 			item(2,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 			item(3,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 			item(4,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 		}
		for (int i = 0; i < columnCount(); i++)
		{
			if (i == SEQUENCEESTIMATEGRID_COL_NAME)
			{
				item(nRow, i)->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
			}
			else if (i != SEQUENCEESTIMATEGRID_COL_ERRORTYPE)
			{
				item(nRow, i)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			}
		}

	}

	for (int i = 0; i <rowCount(); i++)
	{
		item(i, SEQUENCEESTIMATEGRID_COL_NAME)->setFlags(item(i, SEQUENCEESTIMATEGRID_COL_NAME)->flags() & ~Qt::ItemIsEditable);
		EnableRow(i, FALSE);

		//item(i, 2)->setFlags(item(i, 2)->flags() & ~Qt::ItemIsEditable);
		//item(i, 3)->setFlags(item(i, 3)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
	}

	if (pParas->m_bAuto)//自动递变方式时，开放动作值、返回系数、相位动作值
	{
		if(pParas->m_nGradientTpSelect==0)//幅值
		{
			if (g_pSequenceManuTest->m_pSequenceManualWidget->m_nChanneType== 0)		
			{
				EnableRow(1);//电压
			}
			else if (g_pSequenceManuTest->m_pSequenceManualWidget->m_nChanneType== 1)
			{
				EnableRow(2);//电流
			}
		}

		else if (pParas->m_nGradientTpSelect==1)//相位
		{
			EnableRow(3);
		}
// 		else if (pParas->m_nGradientTpSelect == 2)//频率
// 		{
// 			EnableRow(3);
// 		}

	
		if (pParas->m_oSequenceGradient.nMode==1)
		{
			EnableRow(4);
		}
	}
	EnableRow(0);

	CbbErrorType(0,pCbbError1->currentText());
	CbbErrorType(1,pCbbError2->currentText());
	CbbErrorType(2,pCbbError3->currentText());
//  	CbbErrorType(3,pCbbError4->currentText());
	CbbErrorType(3,pCbbError5->currentText());
	CbbErrorType(4, pCbbError6->currentText());

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(pCbbError1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
// 	connect(pCbbError4, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError5, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError6, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));

}

void SequenceEstimateGrid::CbbErrorType(int nIndex, CString strText)
{
	if (strText==g_sLangTxt_StateEstimate_AbsError)//绝对误差
	{
// 		item(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR)->setFlags(item(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR)->flags() & ~Qt::ItemIsEditable);
// 		item(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR)->setFlags(item(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR, TRUE);
		if (nIndex == 0)
		{
			SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR, TRUE);
		}
		else
		{
			SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR, FALSE);
		}
	}
	else if (strText==g_sLangTxt_StateEstimate_RelError)//相对误差
	{
// 		item(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR)->setFlags(item(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
// 		item(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR)->setFlags(item(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR)->flags() & ~Qt::ItemIsEditable);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR, FALSE);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR, FALSE);
	}
	else if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR, FALSE);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR, FALSE);
	}
	else
	{
// 		item(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR)->setFlags(item(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
// 		item(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR)->setFlags(item(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_ABSERROR, TRUE);
		if (nIndex == 0)
		{
		SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR, TRUE);
	}
		else
		{
			SetItemEnable(nIndex, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR, FALSE);
		}
	}
}

void SequenceEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void SequenceEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	int nRow = currentRow();

	CbbErrorType(nRow,strText);
}

void SequenceEstimateGrid::slot_OnCellChanged(int row,int col)
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

	if(col==SEQUENCEESTIMATEGRID_COL_RELERROR)//相对误差
	{
		fv=setLimit(0,100,fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if(col==SEQUENCEESTIMATEGRID_COL_ABSERROR)//绝对误差
	{
		fv=setLimit(0,200,fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if (row == 0 && col == SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR)//绝对误差（-）
	{
		fv = setLimit(0, 200, fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if(col==SEQUENCEESTIMATEGRID_COL_SETVALUE)//整定值
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
		if (row==2)
		{
			fv=setLimit(0,10,fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
		
		if (row==3)
		{
			fv=setLimit(0,360,fv);
			pItem->setText(QString::number(fv, 'f', 3));

		}
		if (row==4)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv, 'f', 3));
		}
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

bool SequenceEstimateGrid::eventFilter(QObject *obj, QEvent *event)
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

void SequenceEstimateGrid::mousePressEvent(QMouseEvent * event)
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

void SequenceEstimateGrid::SetItemEnable(int nRow, int nCol, BOOL bEnable)
{
	QTableWidgetItem *pItem = item(nRow, nCol);
	if (!pItem)
	{
		return;
	}

	bool bCbbState = true;
	if (nCol == SEQUENCEESTIMATEGRID_COL_RELERROR || nCol == SEQUENCEESTIMATEGRID_COL_ABSERROR || nCol == SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR)
	{
		QComboBox* pCbb = (QComboBox*)cellWidget(nRow, SEQUENCEESTIMATEGRID_COL_ERRORTYPE);
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

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240808 gongyipng
SequenceManualEstimateDlg::SequenceManualEstimateDlg(tmt_SequenceManuParas* pParas, QWidget* parent) : QDialog(parent)
{
	Stt_Global_SettingParent(this);	//20240808 gongyipng
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
}

SequenceManualEstimateDlg::~SequenceManualEstimateDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
}

void SequenceManualEstimateDlg::InitUI()
{
	CString strTitle = g_sLangTxt_StateEstimate_ResultEstimate; 
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new SequenceEstimateGrid(5, 6, this);
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

void SequenceManualEstimateDlg::slot_btnOK_Clicked()
{
	//20240808 gongyiping 结构体数据在序列化保存时保存了定值关联，待测试
	if (!((QSettingItem*)m_pGrid->item(0, SEQUENCEESTIMATEGRID_COL_RELERROR))->IsSetting())
		m_pParas->m_fTimeValue_RelErr = m_pGrid->item(0, SEQUENCEESTIMATEGRID_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, SEQUENCEESTIMATEGRID_COL_RELERROR))->IsSetting())
		m_pParas->m_fUActVal_RelErr = m_pGrid->item(1, SEQUENCEESTIMATEGRID_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(2, SEQUENCEESTIMATEGRID_COL_RELERROR))->IsSetting())
		m_pParas->m_fIActVal_RelErr = m_pGrid->item(2, SEQUENCEESTIMATEGRID_COL_RELERROR)->text().toFloat();
// 	if (!((QSettingItem*)m_pGrid->item(3, SEQUENCEESTIMATEGRID_COL_RELERROR))->IsSetting())
// 		m_pParas->m_fHzActVal_RelErr = m_pGrid->item(3, SEQUENCEESTIMATEGRID_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3, SEQUENCEESTIMATEGRID_COL_RELERROR))->IsSetting())
		m_pParas->m_fAngleActVal_RelErr = m_pGrid->item(3, SEQUENCEESTIMATEGRID_COL_RELERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(4, SEQUENCEESTIMATEGRID_COL_RELERROR))->IsSetting())
		m_pParas->m_fRetCoef_RelErr = m_pGrid->item(4, SEQUENCEESTIMATEGRID_COL_RELERROR)->text().toFloat();

	if (!((QSettingItem*)m_pGrid->item(0, SEQUENCEESTIMATEGRID_COL_ABSERROR))->IsSetting())
		m_pParas->m_fTimeValue_AbsErr = m_pGrid->item(0,SEQUENCEESTIMATEGRID_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, SEQUENCEESTIMATEGRID_COL_ABSERROR))->IsSetting())
		m_pParas->m_fUActVal_AbsErr = m_pGrid->item(1, SEQUENCEESTIMATEGRID_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(2, SEQUENCEESTIMATEGRID_COL_ABSERROR))->IsSetting())
		m_pParas->m_fIActVal_AbsErr = m_pGrid->item(2, SEQUENCEESTIMATEGRID_COL_ABSERROR)->text().toFloat();
// 	if (!((QSettingItem*)m_pGrid->item(3, SEQUENCEESTIMATEGRID_COL_ABSERROR))->IsSetting())
// 		m_pParas->m_fHzActVal_AbsErr = m_pGrid->item(3, SEQUENCEESTIMATEGRID_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3, SEQUENCEESTIMATEGRID_COL_ABSERROR))->IsSetting())
		m_pParas->m_fAngleActVal_AbsErr = m_pGrid->item(3, SEQUENCEESTIMATEGRID_COL_ABSERROR)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(4, SEQUENCEESTIMATEGRID_COL_ABSERROR))->IsSetting())
		m_pParas->m_fRetCoef_AbsErr = m_pGrid->item(4, SEQUENCEESTIMATEGRID_COL_ABSERROR)->text().toFloat();

	//动作时间负绝对误差
	if (!((QSettingItem*)m_pGrid->item(0, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR))->IsSetting())
		m_pParas->m_fTimeValue_AbsErrNeg = m_pGrid->item(0, SEQUENCEESTIMATEGRID_COL_NEGATIVEABSERROR)->text().toFloat();

	m_pParas->m_nTimeValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(0, SEQUENCEESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
	m_pParas->m_nUActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(1, SEQUENCEESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
	m_pParas->m_nIActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(2, SEQUENCEESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
// 	m_pParas->m_nHzActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(3, SEQUENCEESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
// 	m_pParas->m_nAngleActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(4, SEQUENCEESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
// 	m_pParas->m_nRetCoef_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(5, SEQUENCEESTIMATEGRID_COL_ERRORTYPE))->currentIndex();

	CString strText;
// 	strText = ((QComboBox*)m_pGrid->cellWidget(3, SEQUENCEESTIMATEGRID_COL_ERRORTYPE))->currentText();
// 	if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
// 	{
// 		m_pParas->m_nHzActVal_ErrorLogic = 5;
// 	}
// 	else
// 	{
// 	m_pParas->m_nHzActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(3, SEQUENCEESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
// 	}

	strText = ((QComboBox*)m_pGrid->cellWidget(3, SEQUENCEESTIMATEGRID_COL_ERRORTYPE))->currentText();
	if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		m_pParas->m_nAngleActVal_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nAngleActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(3, SEQUENCEESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
	}

	strText = ((QComboBox*)m_pGrid->cellWidget(4, SEQUENCEESTIMATEGRID_COL_ERRORTYPE))->currentText();
	if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		m_pParas->m_nRetCoef_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nRetCoef_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(4, SEQUENCEESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
	}

	if (!((QSettingItem*)m_pGrid->item(0, SEQUENCEESTIMATEGRID_COL_SETVALUE))->IsSetting())
	m_pParas->m_fTimeSet = m_pGrid->item(0, SEQUENCEESTIMATEGRID_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, SEQUENCEESTIMATEGRID_COL_SETVALUE))->IsSetting())
	m_pParas->m_fUSet = m_pGrid->item(1, SEQUENCEESTIMATEGRID_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(2, SEQUENCEESTIMATEGRID_COL_SETVALUE))->IsSetting())
	m_pParas->m_fISet = m_pGrid->item(2, SEQUENCEESTIMATEGRID_COL_SETVALUE)->text().toFloat();
// 	if (!((QSettingItem*)m_pGrid->item(3, SEQUENCEESTIMATEGRID_COL_SETVALUE))->IsSetting())
// 		m_pParas->m_fHzSet = m_pGrid->item(3, SEQUENCEESTIMATEGRID_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3, SEQUENCEESTIMATEGRID_COL_SETVALUE))->IsSetting())
	m_pParas->m_fAngleSet = m_pGrid->item(3, SEQUENCEESTIMATEGRID_COL_SETVALUE)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(4, SEQUENCEESTIMATEGRID_COL_SETVALUE))->IsSetting())
	m_pParas->m_fRetCoefSet = m_pGrid->item(4, SEQUENCEESTIMATEGRID_COL_SETVALUE)->text().toFloat();
	

	accept();
}

void SequenceManualEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}