#include "ImpedanceManuEstimateDlg.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "SttMacroParaEditViewImpedanceManu.h"
#include "../../XLangResource_Native.h"

#ifdef _PSX_QT_WINDOWS_	
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include "../SttTestCntrFrameBase.h"
#endif

ImpedanceEstimateGrid::ImpedanceEstimateGrid(int rows, int columns, QWidget* parent) : QScrollTableWidget(parent)	//QTableWidget(rows, columns, parent)//20240808 gongyiping
{
	//20240808 gongyiping
	setRowCount(rows);
	setColumnCount(columns);

	m_bRunning = FALSE;
	installEventFilter(this);
}

ImpedanceEstimateGrid::~ImpedanceEstimateGrid()
{

}

void ImpedanceEstimateGrid::InitGrid()
{
	CString strName, strErrorType, strRelError, strAbsError, strAbsErrorNeg, strSettingValue;
	xlang_GetLangStrByFile(strName, "sName");//名称
	xlang_GetLangStrByFile(strErrorType, "StateEstimate_ErrorType");//误差类型
	strRelError = g_sLangTxt_StateEstimate_RelError;//相对误差(%)
	strRelError += "(%)";
	xlang_GetLangStrByFile(strAbsError, "StateEstimate_AbsError");//绝对误差
	strAbsErrorNeg = g_sLangTxt_StateEstimate_AbsError;//绝对误差(-)
	strAbsErrorNeg += "(-)";
	xlang_GetLangStrByFile(strSettingValue, "State_SettingValue");//整定值

	setHorizontalHeaderLabels(QStringList() << strName << strSettingValue << strErrorType << strRelError << strAbsError << strAbsErrorNeg);

	//setHorizontalHeaderLabels(QStringList() << strName << strErrorType << strRelError << strAbsError << strAbsErrorNeg << strSettingValue);
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

	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); 
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
}

QComboBox* ImpedanceEstimateGrid::NewErrorType()
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

QComboBox* ImpedanceEstimateGrid::AbsErrorType()
{
	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
	return pCbbError;
}

void ImpedanceEstimateGrid::EnableRow(long nIndex, BOOL bEnabled)
{
	if(nIndex >= rowCount())
	{
		return;
	}

	QComboBox* pCbb = (QComboBox*)cellWidget(nIndex, 2);
	pCbb->setEnabled(bEnabled);
	if(bEnabled)
	{
	/*	QTableWidgetItem* pItem = pItem = item(nIndex, 3);
		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
		pItem = item(nIndex, 4);
		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
		pItem = item(nIndex, 5);
		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);*/
		SetItemEnable(nIndex, 3, TRUE);
		SetItemEnable(nIndex, 4, TRUE);
		SetItemEnable(nIndex, 5, TRUE);
	}
	else
	{
		/*QTableWidgetItem* pItem = pItem = item(nIndex, 3);
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
		pItem = item(nIndex, 4);
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
		pItem = item(nIndex, 5);
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);*/
		SetItemEnable(nIndex, 3, FALSE);
		SetItemEnable(nIndex, 4, FALSE);
		SetItemEnable(nIndex, 5, FALSE);
	}
}

void ImpedanceEstimateGrid::SetItemEnable(int nRow, int nCol, BOOL bEnable)
{
	QTableWidgetItem *pItem = item(nRow, nCol);
	if (!pItem)
	{
		return;
	}
	bool bCbbState = true;
	/*pItem->setFlags(bEnable ? pItem->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable
		: pItem->flags() & ~Qt::ItemIsEditable);*/
	
	
	if (nCol == 3 || nCol == 4 || nCol == 5)
	{
		QComboBox* pCbb = (QComboBox*)cellWidget(nRow, 2);
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

void ImpedanceEstimateGrid::InitData(tmt_ManualImpedParas* pParas)
{
	m_pParas=pParas;
	CString strText; 
	strText = /*"动作时间(s)"*/g_sLangTxt_Native_ActionTime;
	setItem(0, 0, new QTableWidgetItem(strText));
	strText = /*"电压动作值(V)"*/g_sLangTxt_Gradient_VActionValue;
	setItem(1, 0, new QTableWidgetItem(strText));
	strText = /*"电流动作值(A)"*/g_sLangTxt_Gradient_CActionValue;
// 	setItem(2, 0, new QTableWidgetItem(strText));
// 	strText = "频率动作值(Hz)";
	setItem(2, 0, new QTableWidgetItem(strText));
	strText = /*"阻抗动作值(Ω)"*/g_sLangTxt_Gradient_ImpAValue;
	setItem(3, 0, new QTableWidgetItem(strText));
	strText = /*"R(Ω)"*/"R(Ω)";
	setItem(4, 0, new QTableWidgetItem(strText));
	strText = /*"X(Ω)"*/"X(Ω)";
	setItem(5, 0, new QTableWidgetItem(strText));
	strText = /*"相位动作值(°)"*/g_sLangTxt_Gradient_PhaseAValue;
	setItem(6, 0, new QTableWidgetItem(strText));
	strText = /*"返回系数"*/g_sLangTxt_Gradient_ReCoefficient;
	setItem(7, 0, new QTableWidgetItem(strText));

	setItem(0, 1, new QTableWidgetItem(QString::number(pParas->m_fTimeSet)));
	setItem(1, 1, new QTableWidgetItem(QString::number(pParas->m_fUSet)));
	setItem(2, 1, new QTableWidgetItem(QString::number(pParas->m_fISet)));
	setItem(3, 1, new QTableWidgetItem(QString::number(pParas->m_fImpSet)));
	setItem(4, 1, new QTableWidgetItem(QString::number(pParas->m_fRSet)));
	setItem(5, 1, new QTableWidgetItem(QString::number(pParas->m_fXSet)));
	//setItem(3, 1, new QTableWidgetItem(QString::number(pParas->m_fHzSet)));
	setItem(6, 1, new QTableWidgetItem(QString::number(pParas->m_fAngleSet)));
	setItem(7, 1, new QTableWidgetItem(QString::number(pParas->m_fRetCoefSet)));

	QComboBox *pCbbError1 = NewErrorType();
	pCbbError1->setCurrentIndex(pParas->m_nTimeValue_ErrorLogic);
	QComboBox *pCbbError2 = NewErrorType();
	pCbbError2->setCurrentIndex(pParas->m_nUActVal_ErrorLogic);
	QComboBox *pCbbError3 = NewErrorType();
	pCbbError3->setCurrentIndex(pParas->m_nIActVal_ErrorLogic);
	QComboBox *pCbbError4 = NewErrorType();
	pCbbError4->setCurrentIndex(pParas->m_nImpValue_ErrorLogic);
	QComboBox *pCbbError5 = NewErrorType();
	pCbbError5->setCurrentIndex(pParas->m_nRValue_ErrorLogic);
	QComboBox *pCbbError6 = NewErrorType();
	pCbbError6->setCurrentIndex(pParas->m_nXValue_ErrorLogic);

	//QComboBox *pCbbError4 = AbsErrorType();
	//pCbbError4->setCurrentIndex(pParas->m_nHzActVal_ErrorLogic);
	//QComboBox *pCbbError4 = AbsErrorType();
	//pCbbError4->setCurrentIndex(pParas->m_nImpValue_ErrorLogic);
	QComboBox *pCbbError7 = AbsErrorType();
	pCbbError7->setCurrentIndex(pParas->m_nAngleActVal_ErrorLogic);
	QComboBox *pCbbError8 = AbsErrorType();
	pCbbError8->setCurrentIndex(pParas->m_nRetCoef_ErrorLogic);

	setCellWidget(0, 2, pCbbError1);
	setCellWidget(1, 2, pCbbError2);
	setCellWidget(2, 2, pCbbError3);
	setCellWidget(3, 2, pCbbError4);
	setCellWidget(4, 2, pCbbError5);
	setCellWidget(5, 2, pCbbError6);
	setCellWidget(6, 2, pCbbError7);
	setCellWidget(7, 2, pCbbError8);

	ComboxModelStyle(pCbbError1);
	ComboxModelStyle(pCbbError2);
	ComboxModelStyle(pCbbError3);
	ComboxModelStyle(pCbbError4);
	ComboxModelStyle(pCbbError5);
	ComboxModelStyle(pCbbError6);
	ComboxModelStyle(pCbbError7);
	ComboxModelStyle(pCbbError8);

	//setItem(0, 3, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_RelErr)));
	//setItem(1, 3, new QTableWidgetItem(QString::number(pParas->m_fUActVal_RelErr)));
	//setItem(2, 3, new QTableWidgetItem(QString::number(pParas->m_fIActVal_RelErr)));
	//setItem(3, 3, new QTableWidgetItem(QString::number(pParas->m_fImpValue_RelErr)));
	//setItem(4, 3, new QTableWidgetItem(QString::number(pParas->m_fRValue_RelErr)));
	//setItem(5, 3, new QTableWidgetItem(QString::number(pParas->m_fXValue_RelErr)));
	////setItem(3, 2, new QTableWidgetItem(QString::number(pParas->m_fHzActVal_RelErr)));
	//setItem(6, 3, new QTableWidgetItem(QString::number(pParas->m_fAngleActVal_RelErr)));
	//setItem(7, 3, new QTableWidgetItem(QString::number(pParas->m_fRetCoef_RelErr)));

	//setItem(0, 4, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_AbsErr)));
	//setItem(1, 4, new QTableWidgetItem(QString::number(pParas->m_fUActVal_AbsErr)));
	//setItem(2, 4, new QTableWidgetItem(QString::number(pParas->m_fIActVal_AbsErr)));
	//setItem(3, 4, new QTableWidgetItem(QString::number(pParas->m_fImpValue_AbsErr)));
	//setItem(4, 4, new QTableWidgetItem(QString::number(pParas->m_fRValue_AbsErr)));
	//setItem(5, 4, new QTableWidgetItem(QString::number(pParas->m_fXValue_AbsErr)));
	////setItem(3, 3, new QTableWidgetItem(QString::number(pParas->m_fHzActVal_AbsErr)));
	//setItem(6, 4, new QTableWidgetItem(QString::number(pParas->m_fAngleActVal_AbsErr)));
	//setItem(7, 4, new QTableWidgetItem(QString::number(pParas->m_fRetCoef_AbsErr)));

	strText = "——";
	//setItem(0, 5, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_AbsErrNeg)));
	setItem(1, 5, new QTableWidgetItem(strText));
	setItem(2, 5, new QTableWidgetItem(strText));
	setItem(3, 5, new QTableWidgetItem(strText));
	setItem(4, 5, new QTableWidgetItem(strText));
	setItem(5, 5, new QTableWidgetItem(strText));
	setItem(6, 5, new QTableWidgetItem(strText));
	setItem(7, 5, new QTableWidgetItem(strText));

	//20240805 gongyiping
	//创建定值关联控件
	setItem(0, 3, new QSettingItem(this));
	setItem(1, 3, new QSettingItem(this));
	setItem(2, 3, new QSettingItem(this));
	setItem(3, 3, new QSettingItem(this));
	setItem(4, 3, new QSettingItem(this));
	setItem(5, 3, new QSettingItem(this));
	setItem(6, 3, new QSettingItem(this));
	setItem(7, 3, new QSettingItem(this));

	((QSettingItem*)item(0, 3))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_RelErr));
	((QSettingItem*)item(1, 3))->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_RelErr));
	((QSettingItem*)item(2, 3))->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_RelErr));
	((QSettingItem*)item(3, 3))->UpdateStructText(CVariantDataAddress(&pParas->m_fImpValue_RelErr));
	((QSettingItem*)item(4, 3))->UpdateStructText(CVariantDataAddress(&pParas->m_fRValue_RelErr));
	((QSettingItem*)item(5, 3))->UpdateStructText(CVariantDataAddress(&pParas->m_fXValue_RelErr));
	((QSettingItem*)item(6, 3))->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleActVal_RelErr));
	((QSettingItem*)item(7, 3))->UpdateStructText(CVariantDataAddress(&pParas->m_fRetCoef_RelErr));

	setItem(0, 4, new QSettingItem(this));
	setItem(1, 4, new QSettingItem(this));
	setItem(2, 4, new QSettingItem(this));
	setItem(3, 4, new QSettingItem(this));
	setItem(4, 4, new QSettingItem(this));
	setItem(5, 4, new QSettingItem(this));
	setItem(6, 4, new QSettingItem(this));
	setItem(7, 4, new QSettingItem(this));

	((QSettingItem*)item(0, 4))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_AbsErr));
	((QSettingItem*)item(1, 4))->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_AbsErr));
	((QSettingItem*)item(2, 4))->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_AbsErr));
	((QSettingItem*)item(3, 4))->UpdateStructText(CVariantDataAddress(&pParas->m_fImpValue_AbsErr));
	((QSettingItem*)item(4, 4))->UpdateStructText(CVariantDataAddress(&pParas->m_fRValue_AbsErr));
	((QSettingItem*)item(5, 4))->UpdateStructText(CVariantDataAddress(&pParas->m_fXValue_AbsErr));
	((QSettingItem*)item(6, 4))->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleActVal_AbsErr));
	((QSettingItem*)item(7, 4))->UpdateStructText(CVariantDataAddress(&pParas->m_fRetCoef_AbsErr));

	setItem(0, 1, new QSettingItem(this));
	setItem(1, 1, new QSettingItem(this));
	setItem(2, 1, new QSettingItem(this));
	setItem(3, 1, new QSettingItem(this));
	setItem(4, 1, new QSettingItem(this));
	setItem(5, 1, new QSettingItem(this));
	setItem(6, 1, new QSettingItem(this));
	setItem(7, 1, new QSettingItem(this));

	((QSettingItem*)item(0, 1))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeSet));
	((QSettingItem*)item(1, 1))->UpdateStructText(CVariantDataAddress(&pParas->m_fUSet));
	((QSettingItem*)item(2, 1))->UpdateStructText(CVariantDataAddress(&pParas->m_fISet));
	((QSettingItem*)item(3, 1))->UpdateStructText(CVariantDataAddress(&pParas->m_fImpSet));
	((QSettingItem*)item(4, 1))->UpdateStructText(CVariantDataAddress(&pParas->m_fRSet));
	((QSettingItem*)item(5, 1))->UpdateStructText(CVariantDataAddress(&pParas->m_fXSet));
	((QSettingItem*)item(6, 1))->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleSet));
	((QSettingItem*)item(7, 1))->UpdateStructText(CVariantDataAddress(&pParas->m_fRetCoefSet));

	setItem(0, 5, new QSettingItem(this));
	((QSettingItem*)item(0, 5))->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_AbsErrNeg));

	for (int i = 0 ;i < 8 ;i++)
	{
		for (int j = 0; j < 6; j++)
	{
			if (j == 0)
		{
				item(0, j)->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
			}
			else if (j != 2)
			{
				item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			}
		}
	}

	for (int i = 0;i < 8; i++)
	{
		item(i, 0)->setFlags(item(i, 0)->flags() & ~Qt::ItemIsEditable);
		EnableRow(i, FALSE);
	}

	if (pParas->m_bAuto)//自动递变方式时，开放动作值、返回系数、相位动作值
	{
		if (pParas->m_nSecondMode == 0)//幅值
				{
			if (pParas->m_nFirstMode == 4)  //变量选择电压
				{
					EnableRow(1);//电压
				}
			else if (pParas->m_nFirstMode == 3) //变量选择电流
				{
					EnableRow(2);//电流
				}
			else if (pParas->m_nFirstMode == 0) //阻抗
				{
					EnableRow(3);//阻抗
				}
			else if (pParas->m_nFirstMode == 1)   //R
				{
					EnableRow(4);
				}
			else if (pParas->m_nFirstMode == 2)  //X
				{
					EnableRow(5);
				}
					}
		else if (pParas->m_nSecondMode == 1)//相位
		{
			EnableRow(6);
		}

		if (pParas->m_manuImpedGradient.nMode == 1)
		{
			EnableRow(7);
		}

	}

	EnableRow(0);//动作时间

	CbbErrorType(0,pCbbError1->currentText());
	CbbErrorType(1,pCbbError2->currentText());
	CbbErrorType(2,pCbbError3->currentText());
	CbbErrorType(3,pCbbError4->currentText());
	CbbErrorType(4,pCbbError5->currentText());
	CbbErrorType(5,pCbbError6->currentText());
	CbbErrorType(6,pCbbError7->currentText());
	CbbErrorType(7,pCbbError8->currentText());
	

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(pCbbError1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError4, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError5, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
    connect(pCbbError6, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError7, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError8, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
}

void ImpedanceEstimateGrid::CbbErrorType(int nIndex, CString strText)
{
	if (strText==g_sLangTxt_StateEstimate_AbsError)//绝对误差
	{
		/*item(nIndex, 3)->setFlags(item(nIndex, 3)->flags() & ~Qt::ItemIsEditable);
		item(nIndex, 4)->setFlags(item(nIndex, 4)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		item(nIndex, 5)->setFlags(item(nIndex, 5)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);*/
		SetItemEnable(nIndex, 3, FALSE);
		SetItemEnable(nIndex, 4, TRUE);
		SetItemEnable(nIndex, 5, TRUE);
	if (nIndex == 0)
		{
			SetItemEnable(nIndex, 5, TRUE);
		}
		else
		{
			SetItemEnable(nIndex, 5, FALSE);
		}
	}
	else if (strText==g_sLangTxt_StateEstimate_RelError)//相对误差
	{
		/*item(nIndex, 3)->setFlags(item(nIndex, 3)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		item(nIndex, 4)->setFlags(item(nIndex, 4)->flags() & ~Qt::ItemIsEditable);
		item(nIndex, 5)->setFlags(item(nIndex, 5)->flags() & ~Qt::ItemIsEditable);*/
		SetItemEnable(nIndex, 3, TRUE);
		SetItemEnable(nIndex, 4, FALSE);
		SetItemEnable(nIndex, 5, FALSE);
	}
	else if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		SetItemEnable(nIndex, 3, FALSE);
		SetItemEnable(nIndex, 4, FALSE);
		SetItemEnable(nIndex, 5, FALSE);
	}
	else
	{
		/*item(nIndex, 3)->setFlags(item(nIndex, 3)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		item(nIndex, 4)->setFlags(item(nIndex, 4)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		item(nIndex, 5)->setFlags(item(nIndex, 5)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);*/
		SetItemEnable(nIndex, 3, TRUE);
		SetItemEnable(nIndex, 4, TRUE);
		SetItemEnable(nIndex, 5, TRUE);
	}

	//if (nIndex != 0)
	//{
	//	/*item(nIndex, 5)->setFlags(item(nIndex, 5)->flags() & ~Qt::ItemIsEditable);*/
	//	SetItemEnable(nIndex, 5, FALSE);
	//}
}

void ImpedanceEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void ImpedanceEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	int nRow = currentRow();

	CbbErrorType(nRow,strText);
}

void ImpedanceEstimateGrid::slot_OnCellChanged(int row,int col)
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

	if(col==3)//相对误差
	{
		fv=setLimit(0,100,fv);
		pItem->setText(QString::number(fv));
	}

	if(col==4)//绝对误差
	{
		fv=setLimit(0,200,fv);
		pItem->setText(QString::number(fv));	
	}

	if (row == 0 && col == 5)//绝对误差负
	{
		fv = setLimit(0, 200, fv);
		pItem->setText(QString::number(fv));
	}

	if(col==1)//整定值
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
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));
		}
		if (row == 4)
		{
			fv = setLimit(0, 999, fv);
			pItem->setText(QString::number(fv));
		}
		if (row == 5)
		{
			fv = setLimit(0, 999, fv);
			pItem->setText(QString::number(fv));
		}
		if (row==6)
		{
			fv=setLimit(0,360,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==7)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));
		}
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

bool ImpedanceEstimateGrid::eventFilter(QObject *obj, QEvent *event)
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

void ImpedanceEstimateGrid::mousePressEvent(QMouseEvent * event)
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
ImpedanceManuEstimateDlg::ImpedanceManuEstimateDlg(tmt_ManualImpedParas* pParas, QWidget* parent) : QDialog(parent)
{
	Stt_Global_SettingParent(this);	//20240808 gongyipng
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
}

ImpedanceManuEstimateDlg::~ImpedanceManuEstimateDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
}

void ImpedanceManuEstimateDlg::InitUI()
{
	CString strTitle = g_sLangTxt_StateEstimate_ResultEstimate; 
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	//m_pGrid = new ImpedanceEstimateGrid(6, 5, this);
	m_pGrid = new ImpedanceEstimateGrid(8, 6, this);

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
#endif // _PSX_QT_WINDOWS_


}

void ImpedanceManuEstimateDlg::slot_btnOK_Clicked()
{
//20240808 gongyiping 结构体数据在序列化保存时保存了定值关联，待测试
	if (!((QSettingItem*)m_pGrid->item(0, 3))->IsSetting())
	m_pParas->m_fTimeValue_RelErr = m_pGrid->item(0, 3)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, 3))->IsSetting())
	m_pParas->m_fUActVal_RelErr = m_pGrid->item(1, 3)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(2, 3))->IsSetting())
	m_pParas->m_fIActVal_RelErr = m_pGrid->item(2, 3)->text().toFloat();
	//m_pParas->m_fHzActVal_RelErr = m_pGrid->item(3, 3)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3, 3))->IsSetting())
    m_pParas->m_fImpValue_RelErr = m_pGrid->item(3, 3)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(4, 3))->IsSetting())
		m_pParas->m_fRValue_RelErr = m_pGrid->item(4, 3)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(5, 3))->IsSetting())
		m_pParas->m_fXValue_RelErr = m_pGrid->item(5, 3)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(6, 3))->IsSetting())
	m_pParas->m_fAngleActVal_RelErr = m_pGrid->item(6, 3)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(7, 3))->IsSetting())
	m_pParas->m_fRetCoef_RelErr = m_pGrid->item(7, 3)->text().toFloat();

	if (!((QSettingItem*)m_pGrid->item(0, 4))->IsSetting())
	m_pParas->m_fTimeValue_AbsErr = m_pGrid->item(0, 4)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, 4))->IsSetting())
	m_pParas->m_fUActVal_AbsErr = m_pGrid->item(1, 4)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(2, 4))->IsSetting())
	m_pParas->m_fIActVal_AbsErr = m_pGrid->item(2, 4)->text().toFloat();
	//m_pParas->m_fHzActVal_AbsErr = m_pGrid->item(3, 4)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3, 4))->IsSetting())
	m_pParas->m_fImpValue_AbsErr = m_pGrid->item(3, 4)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(4, 4))->IsSetting())
		m_pParas->m_fRValue_AbsErr = m_pGrid->item(4, 4)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(5, 4))->IsSetting())
		m_pParas->m_fXValue_AbsErr = m_pGrid->item(5, 4)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(6, 4))->IsSetting())
	m_pParas->m_fAngleActVal_AbsErr = m_pGrid->item(6, 4)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(7, 4))->IsSetting())
	m_pParas->m_fRetCoef_AbsErr = m_pGrid->item(7, 4)->text().toFloat();

	if (!((QSettingItem*)m_pGrid->item(0, 5))->IsSetting())
	m_pParas->m_fTimeValue_AbsErrNeg = m_pGrid->item(0, 5)->text().toFloat();
	

	m_pParas->m_nTimeValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(0, 2))->currentIndex();
	m_pParas->m_nUActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(1, 2))->currentIndex();
	m_pParas->m_nIActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(2, 2))->currentIndex();
	//m_pParas->m_nHzActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(3, 2))->currentIndex();
	m_pParas->m_nImpValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(3, 2))->currentIndex();
	m_pParas->m_nRValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(4, 2))->currentIndex();
	m_pParas->m_nXValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(5, 2))->currentIndex();
	m_pParas->m_nAngleActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(6, 2))->currentIndex();
	m_pParas->m_nRetCoef_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(7, 2))->currentIndex();

	if (!((QSettingItem*)m_pGrid->item(0, 1))->IsSetting())
	m_pParas->m_fTimeSet = m_pGrid->item(0, 1)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(1, 1))->IsSetting())
	m_pParas->m_fUSet = m_pGrid->item(1, 1)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(2, 1))->IsSetting())
	m_pParas->m_fISet = m_pGrid->item(2, 1)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(3 ,1))->IsSetting())
	m_pParas->m_fImpSet = m_pGrid->item(3, 1)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(4, 1))->IsSetting())
		m_pParas->m_fRSet = m_pGrid->item(4, 1)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(5, 1))->IsSetting())
		m_pParas->m_fXSet = m_pGrid->item(5, 1)->text().toFloat();
	//m_pParas->m_fHzSet = m_pGrid->item(3, 1)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(6, 1))->IsSetting())
	m_pParas->m_fAngleSet = m_pGrid->item(6, 1)->text().toFloat();
	if (!((QSettingItem*)m_pGrid->item(7, 1))->IsSetting())
	m_pParas->m_fRetCoefSet = m_pGrid->item(7, 1)->text().toFloat();

	accept();
}

void ImpedanceManuEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}