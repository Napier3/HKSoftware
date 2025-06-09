#include "GradientEstimateDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>
#include "../../XLangResource_Native.h"
#include "../Module/CommonMethod/commonMethod.h"
#include <QApplication>
extern void  Stt_Global_SettingParent(QWidget *parent);		//20240802 huangliang 

#include <QDesktopWidget>
#include <QRect>
#include "../SttTestCntrFrameBase.h"

#define  GRADIENTESTIMATE_COL_NAME			0		//名称
#define  GRADIENTESTIMATE_COL_SETVALUE		1		//整定值
#define  GRADIENTESTIMATE_COL_ERRORTYPE		2		//误差类型
#define  GRADIENTESTIMATE_COL_RELERROR		3		//相对误差
#define  GRADIENTESTIMATE_COL_ABSERROR		4		//绝对误差

GradientEstimateGrid::GradientEstimateGrid(int rows, int columns, QWidget* parent) : QTableWidget(rows, columns, parent)
{
	m_bRunning = FALSE;
	installEventFilter(this);
}

GradientEstimateGrid::~GradientEstimateGrid()
{

}

void GradientEstimateGrid::InitGrid()
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
	xlang_GetLangStrByFile(strSettingValue, "State_SettingValue");

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

void GradientEstimateGrid::EnableRow(long nIndex, BOOL bEnabled)
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
}
void GradientEstimateGrid::SetItemEnable(int nRow, int nCol, BOOL bEnable)
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
QComboBox* GradientEstimateGrid::NewErrorType()//电气量幅值、阻抗类误差类型
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

QComboBox* GradientEstimateGrid::AbsErrorType()
{
	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
	return pCbbError;
}


void GradientEstimateGrid::InitData(tmt_GradientParasEx* pParas)
{
	m_pParas=pParas;
	QComboBox *pCbbError1 = NewErrorType();
	if (pParas->m_nUActVal_ErrorLogic == 5)//不评估
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
	QComboBox *pCbbError2 = NewErrorType();
	if (pParas->m_nIActVal_ErrorLogic == 5)//不评估
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
	QComboBox *pCbbError3 = AbsErrorType();
	if (pParas->m_nAngleActVal_ErrorLogic == 5)//不评估
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbError3->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError3,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
	pCbbError3->setCurrentIndex(pParas->m_nAngleActVal_ErrorLogic);
	}
	QComboBox *pCbbError4 = AbsErrorType();
	if (pParas->m_nHzActVal_ErrorLogic == 5)//不评估
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
	QComboBox *pCbbError5 = NewErrorType();
	if (pParas->m_nAngleF_ErrorLogic == 5)//不评估
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbError5->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError5,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
	pCbbError5->setCurrentIndex(pParas->m_nAngleF_ErrorLogic);
	}
	QComboBox *pCbbError6 = NewErrorType();
	if (pParas->m_nAngleS_ErrorLogic == 5)//不评估
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbError6->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError6,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
	pCbbError6->setCurrentIndex(pParas->m_nAngleS_ErrorLogic);
	}
	QComboBox *pCbbError7 = NewErrorType();
	if (pParas->m_nMaxAngle_ErrorLogic == 5)//不评估
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbError7->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError7,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
	pCbbError7->setCurrentIndex(pParas->m_nMaxAngle_ErrorLogic);
	}
	QComboBox *pCbbError8 = AbsErrorType();
	if (pParas->m_nRetCoef_ErrorLogic == 5)//不评估
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbError8->setCurrentText(g_sLangTxt_Distance_ErrorNot);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbError8,g_sLangTxt_Distance_ErrorNot);
#endif
	}
	else
	{
	pCbbError8->setCurrentIndex(pParas->m_nRetCoef_ErrorLogic);
	}

	pCbbError1->setObjectName("0");
	pCbbError2->setObjectName("1");
	pCbbError3->setObjectName("2");
	pCbbError4->setObjectName("3");
	pCbbError5->setObjectName("4");
	pCbbError6->setObjectName("5");
	pCbbError7->setObjectName("6");
	pCbbError8->setObjectName("7");

	CString strText; 
	//strText = "电压动作值(V)";
	strText = g_sLangTxt_Gradient_VActionValue;//lcq
	setItem(0, GRADIENTESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	//strText = "电流动作值(A)";
	strText = g_sLangTxt_Gradient_CActionValue;
	setItem(1, GRADIENTESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	//strText = "相位动作值(°)";
	strText = g_sLangTxt_Gradient_PhaseAValue;
	setItem(2, GRADIENTESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	//strText = "频率动作值(Hz)";
	strText = g_sLangTxt_Gradient_FreAValue;
	setItem(3, GRADIENTESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	//strText = "边界角1(°)";
	strText = g_sLangTxt_Gradient_FirBoundAngle;
	setItem(4, GRADIENTESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	//strText = "边界角2(°)";
	strText = g_sLangTxt_Gradient_SecBoundAngle;
	setItem(5, GRADIENTESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	//strText = "最大灵敏角(°)";
	strText = g_sLangTxt_Gradient_MaxSenAngle;
	setItem(6, GRADIENTESTIMATE_COL_NAME, new QTableWidgetItem(strText));
	//strText = "返回系数";
	strText = g_sLangTxt_Gradient_ReCoefficient;
	setItem(7, GRADIENTESTIMATE_COL_NAME, new QTableWidgetItem(strText));

	setCellWidget(0, GRADIENTESTIMATE_COL_ERRORTYPE, pCbbError1);
	setCellWidget(1, GRADIENTESTIMATE_COL_ERRORTYPE, pCbbError2);
	setCellWidget(2, GRADIENTESTIMATE_COL_ERRORTYPE, pCbbError3);
	setCellWidget(3, GRADIENTESTIMATE_COL_ERRORTYPE, pCbbError4);
	setCellWidget(4, GRADIENTESTIMATE_COL_ERRORTYPE, pCbbError5);
	setCellWidget(5, GRADIENTESTIMATE_COL_ERRORTYPE, pCbbError6);
	setCellWidget(6, GRADIENTESTIMATE_COL_ERRORTYPE, pCbbError7);
	setCellWidget(7, GRADIENTESTIMATE_COL_ERRORTYPE, pCbbError8);

	ComboxModelStyle(pCbbError1);
	ComboxModelStyle(pCbbError2);
	ComboxModelStyle(pCbbError3);
	ComboxModelStyle(pCbbError4);
	ComboxModelStyle(pCbbError5);
	ComboxModelStyle(pCbbError6);
	ComboxModelStyle(pCbbError7);
	ComboxModelStyle(pCbbError8);

	/*setItem(0, 2, new QTableWidgetItem(QString::number(pParas->m_fUActVal_RelErr)));
	setItem(1, 2, new QTableWidgetItem(QString::number(pParas->m_fIActVal_RelErr)));
	setItem(2, 2, new QTableWidgetItem(QString::number(pParas->m_fRetCoef_RelErr)));
	setItem(3, 2, new QTableWidgetItem(QString::number(pParas->m_fAngleF_RelErr)));
	setItem(4, 2, new QTableWidgetItem(QString::number(pParas->m_fAngleS_RelErr)));
	setItem(5, 2, new QTableWidgetItem(QString::number(pParas->m_fMaxAngle_RelErr)));
	setItem(6, 2, new QTableWidgetItem(QString::number(pParas->m_fHzActVal_RelErr)));
	setItem(7, 2, new QTableWidgetItem(QString::number(pParas->m_fAngleActVal_RelErr)));
	setItem(0, 3, new QTableWidgetItem(QString::number(pParas->m_fUActVal_AbsErr)));
	setItem(1, 3, new QTableWidgetItem(QString::number(pParas->m_fIActVal_AbsErr)));
	setItem(2, 3, new QTableWidgetItem(QString::number(pParas->m_fRetCoef_AbsErr)));
	setItem(3, 3, new QTableWidgetItem(QString::number(pParas->m_fAngleF_AbsErr)));
	setItem(4, 3, new QTableWidgetItem(QString::number(pParas->m_fAngleS_AbsErr)));
	setItem(5, 3, new QTableWidgetItem(QString::number(pParas->m_fMaxAngle_AbsErr)));
	setItem(6, 3, new QTableWidgetItem(QString::number(pParas->m_fHzActVal_AbsErr)));
	setItem(7, 3, new QTableWidgetItem(QString::number(pParas->m_fAngleActVal_AbsErr)));
	setItem(0, 4, new QTableWidgetItem(QString::number(pParas->m_fUSet)));
	setItem(1, 4, new QTableWidgetItem(QString::number(pParas->m_fISet)));
	setItem(2, 4, new QTableWidgetItem(QString::number(pParas->m_fRetCoefSet)));
	setItem(3, 4, new QTableWidgetItem(QString::number(pParas->m_fAngleFSet)));
	setItem(4, 4, new QTableWidgetItem(QString::number(pParas->m_fAngleSSet)));
	setItem(5, 4, new QTableWidgetItem(QString::number(pParas->m_fMaxAngleSet)));
	setItem(6, 4, new QTableWidgetItem(QString::number(pParas->m_fHzSet)));
	setItem(7, 4, new QTableWidgetItem(QString::number(pParas->m_fAngleSet)));*/

	QSettingItem *pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_RelErr), 3);
	setItem(0, GRADIENTESTIMATE_COL_RELERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_RelErr), 3);
	setItem(1, GRADIENTESTIMATE_COL_RELERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleActVal_RelErr), 3);
	setItem(2, GRADIENTESTIMATE_COL_RELERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fHzActVal_RelErr), 3);
	setItem(3, GRADIENTESTIMATE_COL_RELERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleF_RelErr), 3);
	setItem(4, GRADIENTESTIMATE_COL_RELERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleS_RelErr), 3);
	setItem(5, GRADIENTESTIMATE_COL_RELERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fMaxAngle_RelErr), 3);
	setItem(6, GRADIENTESTIMATE_COL_RELERROR, pSettingItem);

	//pSettingItem = new QSettingItem(this);
	//pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fRetCoef_RelErr), 3);
	//setItem(7, GRADIENTESTIMATE_COL_RELERROR, pSettingItem);
	setItem(7, GRADIENTESTIMATE_COL_RELERROR, new QTableWidgetItem(CString("——")));


	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_AbsErr), 3);
	setItem(0, GRADIENTESTIMATE_COL_ABSERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_AbsErr), 3);
	setItem(1, GRADIENTESTIMATE_COL_ABSERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleActVal_AbsErr), 3);
	setItem(2, GRADIENTESTIMATE_COL_ABSERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fHzActVal_AbsErr), 3);
	setItem(3, GRADIENTESTIMATE_COL_ABSERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleF_AbsErr), 3);
	setItem(4, GRADIENTESTIMATE_COL_ABSERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleS_AbsErr), 3);
	setItem(5, GRADIENTESTIMATE_COL_ABSERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fMaxAngle_AbsErr), 3);
	setItem(6, GRADIENTESTIMATE_COL_ABSERROR, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fRetCoef_AbsErr), 3);
	setItem(7, GRADIENTESTIMATE_COL_ABSERROR, pSettingItem);


	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fUSet), 3);
	setItem(0, GRADIENTESTIMATE_COL_SETVALUE, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fISet), 3);
	setItem(1, GRADIENTESTIMATE_COL_SETVALUE, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleSet), 3);
	setItem(2, GRADIENTESTIMATE_COL_SETVALUE, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fHzSet), 3);
	setItem(3, GRADIENTESTIMATE_COL_SETVALUE, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleFSet), 3);
	setItem(4, GRADIENTESTIMATE_COL_SETVALUE, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fAngleSSet), 3);
	setItem(5, GRADIENTESTIMATE_COL_SETVALUE, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fMaxAngleSet), 3);
	setItem(6, GRADIENTESTIMATE_COL_SETVALUE, pSettingItem);

	pSettingItem = new QSettingItem(this);
	pSettingItem->UpdateStructText(CVariantDataAddress(&pParas->m_fRetCoefSet), 3);
	setItem(7, GRADIENTESTIMATE_COL_SETVALUE, pSettingItem);

	for (int i = 0 ;i < 5 ;i++)
	{
		if (i != GRADIENTESTIMATE_COL_ERRORTYPE)
		{
			item(0,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(1,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(2,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(3,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(4,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(5,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(6,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(7,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		}
		
	}

	for (int i = 0; i < 8; i++)
	{
		item(i, GRADIENTESTIMATE_COL_NAME)->setFlags(item(i, GRADIENTESTIMATE_COL_NAME)->flags() & ~Qt::ItemIsEditable);
		EnableRow(i, FALSE);
	}

	if (pParas->m_nType == 0 || pParas->m_nType2 == 0)
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
		else if(pParas->m_nTestMode == 1)
		{
			//返回系数
			EnableRow(7);
		}
	}
	if (pParas->m_nType == 1 || pParas->m_nType2 == 1)
	{
		//相位
		if(pParas->m_nTestMode == 0)
		{
			//动作值
			EnableRow(2);
		}
		else if(pParas->m_nTestMode == 1)
		{
			//返回系数
			EnableRow(7);
		}
		else if(pParas->m_nTestMode == 2)
		{
			//最大灵敏角
			EnableRow(4);
			EnableRow(5);
			EnableRow(6);
		}
	}
	if (pParas->m_nType == 2 || pParas->m_nType2 == 2)
	{
		//频率
		EnableRow(3);
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(pCbbError1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError4, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError5, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError6, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError7, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError8, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));


	CbbErrorType(0,pCbbError1->currentText());
	CbbErrorType(1,pCbbError2->currentText());
	CbbErrorType(2,pCbbError3->currentText());
	CbbErrorType(3,pCbbError4->currentText());
	CbbErrorType(4,pCbbError5->currentText());
	CbbErrorType(5,pCbbError6->currentText());
	CbbErrorType(6,pCbbError7->currentText());
	CbbErrorType(7,pCbbError8->currentText());
}

void GradientEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}



void GradientEstimateGrid::CbbErrorType(int nIndex, CString strText)
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

void GradientEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	QObject *senderObj = sender();
	CString strName;
	if (senderObj)
	{
		strName = senderObj->objectName();
	}
	CbbErrorType(strName.toInt(), strText);
}

void GradientEstimateGrid::slot_OnCellChanged(int row,int col)
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

	if (col == GRADIENTESTIMATE_COL_ERRORTYPE)
	{
		pItem->setText(str);
	}

	if (col == GRADIENTESTIMATE_COL_RELERROR)//相对误差
	{
		if (row == 7)
		{
			return;
		}
		fv=setLimit(0,100,fv);
		pItem->setText(QString::number(fv));
	}

	if (col == GRADIENTESTIMATE_COL_ABSERROR)//绝对误差
	{
		fv=setLimit(0,200,fv);
		pItem->setText(QString::number(fv));
	}

	if (col == GRADIENTESTIMATE_COL_SETVALUE)//整定值
	{
		if (row == 0)
		{
			fv=setLimit(0,120,fv);
			pItem->setText(QString::number(fv));
		}
		if (row == 1)
		{
			fv=setLimit(0,10,fv);
			pItem->setText(QString::number(fv));
		}
		if (row == 2)
		{
			fv = setLimit(0, 360, fv);
			pItem->setText(QString::number(fv));
		}
		if (row == 3)
		{
			fv = setLimit(0, 1550, fv);
			pItem->setText(QString::number(fv));
		}
		if (row == 4)
		{
			fv = setLimit(0, 360, fv);
			pItem->setText(QString::number(fv));
		}
		if (row == 5)
		{
			fv = setLimit(0, 360, fv);
			pItem->setText(QString::number(fv));
		}
		if (row == 6)
		{
			fv = setLimit(0, 360, fv);
			pItem->setText(QString::number(fv));
		}
		if (row == 7)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));
		}
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

bool GradientEstimateGrid::eventFilter(QObject *obj, QEvent *event)
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

void GradientEstimateGrid::mousePressEvent(QMouseEvent * event)
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

GradientEstimateDlg::GradientEstimateDlg(tmt_GradientParasEx* pParas, QWidget* parent) : QDialog(parent)
{
	Stt_Global_SettingParent(this);	//20240909 huangliang 
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
}

GradientEstimateDlg::~GradientEstimateDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
}

void GradientEstimateDlg::InitUI()
{
	//CString strTitle = "结果评估";
	CString strTitle = g_sLangTxt_StateEstimate_ResultEstimate; //lcq
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new GradientEstimateGrid(8, 5, this);
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

	//2024-8-1 wuxinyi 在2880*1800分辨率显示不全
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

void GradientEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->m_fUActVal_RelErr = m_pGrid->item(0, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pParas->m_fIActVal_RelErr = m_pGrid->item(1, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pParas->m_fAngleActVal_RelErr = m_pGrid->item(2, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pParas->m_fHzActVal_RelErr = m_pGrid->item(3, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pParas->m_fAngleF_RelErr = m_pGrid->item(4, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pParas->m_fAngleS_RelErr = m_pGrid->item(5, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pParas->m_fMaxAngle_RelErr = m_pGrid->item(6, GRADIENTESTIMATE_COL_RELERROR)->text().toFloat();
	m_pParas->m_fRetCoef_RelErr = 0.0f;
	m_pParas->m_fUActVal_AbsErr = m_pGrid->item(0, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pParas->m_fIActVal_AbsErr = m_pGrid->item(1, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pParas->m_fAngleActVal_AbsErr = m_pGrid->item(2, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pParas->m_fHzActVal_AbsErr = m_pGrid->item(3, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pParas->m_fAngleF_AbsErr = m_pGrid->item(4, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pParas->m_fAngleS_AbsErr = m_pGrid->item(5, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pParas->m_fMaxAngle_AbsErr = m_pGrid->item(6, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();
	m_pParas->m_fRetCoef_AbsErr = m_pGrid->item(7, GRADIENTESTIMATE_COL_ABSERROR)->text().toFloat();

	if (((QComboBox*)m_pGrid->cellWidget(0, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pParas->m_nUActVal_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nUActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(0, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)m_pGrid->cellWidget(1, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pParas->m_nIActVal_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nIActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(1, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)m_pGrid->cellWidget(2, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pParas->m_nAngleActVal_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nAngleActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(2, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)m_pGrid->cellWidget(3, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pParas->m_nHzActVal_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nHzActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(3, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)m_pGrid->cellWidget(4, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pParas->m_nAngleF_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nAngleF_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(4, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)m_pGrid->cellWidget(5, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pParas->m_nAngleS_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nAngleS_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(5, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)m_pGrid->cellWidget(6, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pParas->m_nMaxAngle_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nMaxAngle_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(6, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}

	if (((QComboBox*)m_pGrid->cellWidget(7, GRADIENTESTIMATE_COL_ERRORTYPE))->currentText() == g_sLangTxt_Distance_ErrorNot)//选中的是不评估，发送的值为5
	{
		m_pParas->m_nRetCoef_ErrorLogic = 5;
	}
	else
	{
	m_pParas->m_nRetCoef_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(7, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	}
	//m_pParas->m_nUActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(0, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	//m_pParas->m_nIActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(1, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	//m_pParas->m_nAngleActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(2, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	//m_pParas->m_nHzActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(3, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	//m_pParas->m_nAngleF_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(4, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	//m_pParas->m_nAngleS_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(5, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	//m_pParas->m_nMaxAngle_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(6, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	//m_pParas->m_nRetCoef_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(7, GRADIENTESTIMATE_COL_ERRORTYPE))->currentIndex();
	m_pParas->m_fUSet = m_pGrid->item(0, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pParas->m_fISet = m_pGrid->item(1, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pParas->m_fAngleSet = m_pGrid->item(2, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pParas->m_fHzSet = m_pGrid->item(3, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pParas->m_fAngleFSet = m_pGrid->item(4, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pParas->m_fAngleSSet = m_pGrid->item(5, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pParas->m_fMaxAngleSet = m_pGrid->item(6, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	m_pParas->m_fRetCoefSet = m_pGrid->item(7, GRADIENTESTIMATE_COL_SETVALUE)->text().toFloat();
	accept();
}

void GradientEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}



