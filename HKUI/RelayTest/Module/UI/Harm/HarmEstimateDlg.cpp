#include "HarmEstimateDlg.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "SttMacroParaEditViewHarm.h"
#include "../../XLangResource_Native.h"

#ifdef _PSX_QT_WINDOWS_
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include "../SttTestCntrFrameBase.h"
#endif

#define  HARMESTIMATEGRID_COL_NAME			0		//名称
#define  HARMESTIMATEGRID_COL_SETVALUE		1		//整定值
#define  HARMESTIMATEGRID_COL_ERRORTYPE		2		//误差类型
#define  HARMESTIMATEGRID_COL_RELERROR		3		//相对误差
#define  HARMESTIMATEGRID_COL_ABSERROR		4		//绝对误差
#define  HARMESTIMATEGRID_COL_NEGATIVEABSERROR		5		//绝对误差(-)

#define HARMESTIMATEGRID_ROW_ACTIONTIME		0		//动作时间
#define HARMESTIMATEGRID_ROW_VOL			1		//电压动作值
#define HARMESTIMATEGRID_ROW_CUR			2		//电流动作值

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240909 huangliang

HarmEstimateGrid::HarmEstimateGrid(int rows, int columns, QWidget* parent) : QTableWidget(rows, columns, parent)
{
	m_bRunning = FALSE;
	installEventFilter(this);
}

HarmEstimateGrid::~HarmEstimateGrid()
{

}

void HarmEstimateGrid::InitGrid()
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

QComboBox* HarmEstimateGrid::NewErrorType()
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


void HarmEstimateGrid::EnableRow(long nIndex, BOOL bEnabled /* = TRUE */)
{
	if(nIndex >= rowCount())
	{
		return;
	}

	QComboBox* pCbb = (QComboBox*)cellWidget(nIndex, HARMESTIMATEGRID_COL_ERRORTYPE);
	pCbb->setEnabled(bEnabled);
	if(bEnabled)
	{
// 		QTableWidgetItem* pItem = pItem = item(nIndex, HARMESTIMATEGRID_COL_RELERROR);
// 		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
// 		pItem = item(nIndex, HARMESTIMATEGRID_COL_ABSERROR);
// 		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_ERRORTYPE, TRUE);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_ABSERROR, TRUE);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, TRUE);
	}
	else
	{
// 		QTableWidgetItem* pItem = pItem = item(nIndex, HARMESTIMATEGRID_COL_RELERROR);
// 		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
// 		pItem = item(nIndex, HARMESTIMATEGRID_COL_ABSERROR);
// 		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_ERRORTYPE, FALSE);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_ABSERROR, FALSE);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, FALSE);
	}
}

void HarmEstimateGrid::InitData(tmt_HarmParas* pParas)
{
	m_pParas=pParas;
	long nType=g_pHarmTest->m_pHarmWidget->m_pParaWidget->m_nHarmGradType;
	CString strText; 

	if (nType==0)
	{	
		strText = /* "电压动作值?(V)" */g_sLangTxt_Gradient_VActionValue;
		setItem(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));
		strText = /* "电流动作值(A)" */g_sLangTxt_Gradient_CActionValue;
		setItem(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));

	}
	else if (nType==1)
	{
		strText = /* "电压动作值?(%)" */g_sLangTxt_Native_VolactValue;
		setItem(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));
		strText = /* "电流动作值(%)" */g_sLangTxt_Native_CuractValue;
		setItem(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));

	}
	strText = /* "动作时间(s)" */g_sLangTxt_Native_ActionTime;
	setItem(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_NAME, new QTableWidgetItem(strText));

	item(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_NAME)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	item(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_NAME)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	item(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_NAME)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	QComboBox *pCbbError1 = NewErrorType();
	pCbbError1->setCurrentIndex(pParas->m_nUActVal_ErrorLogic);
	QComboBox *pCbbError2 = NewErrorType();
	pCbbError2->setCurrentIndex(pParas->m_nIActVal_ErrorLogic);
	QComboBox *pCbbError3 = NewErrorType();
	pCbbError3->setCurrentIndex(pParas->m_nTimeValue_ErrorLogic);


	setCellWidget(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_ERRORTYPE, pCbbError1);
	setCellWidget(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_ERRORTYPE, pCbbError2);
	setCellWidget(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_ERRORTYPE, pCbbError3);
	
	ComboxModelStyle(pCbbError1);
	ComboxModelStyle(pCbbError2);
	ComboxModelStyle(pCbbError3);

// 	setItem(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_RELERROR, new QTableWidgetItem(QString::number(pParas->m_fUActVal_RelErr)));
// 	setItem(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_RELERROR, new QTableWidgetItem(QString::number(pParas->m_fIActVal_RelErr)));
// 	setItem(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_RELERROR, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_RelErr)));

	QSettingItem *iSettem20 = new QSettingItem(this);
	QSettingItem *iSettem21 = new QSettingItem(this);
	QSettingItem *iSettem22 = new QSettingItem(this);
	setItem(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_RELERROR, iSettem20);
	setItem(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_RELERROR, iSettem21);
	setItem(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_RELERROR, iSettem22);
	iSettem20->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_RelErr), 3);
	iSettem21->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_RelErr), 3);
	iSettem22->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_RelErr), 3);

	item(HARMESTIMATEGRID_ROW_VOL,HARMESTIMATEGRID_COL_RELERROR)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item(HARMESTIMATEGRID_ROW_CUR,HARMESTIMATEGRID_COL_RELERROR)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item(HARMESTIMATEGRID_ROW_ACTIONTIME,HARMESTIMATEGRID_COL_RELERROR)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	
// 	setItem(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_ABSERROR, new QTableWidgetItem(QString::number(pParas->m_fUActVal_AbsErr)));
// 	setItem(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_ABSERROR, new QTableWidgetItem(QString::number(pParas->m_fIActVal_AbsErr)));
// 	setItem(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_ABSERROR, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_AbsErr)));

	QSettingItem *iSettem30 = new QSettingItem(this);
	QSettingItem *iSettem31 = new QSettingItem(this);
	QSettingItem *iSettem32 = new QSettingItem(this);
	setItem(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_ABSERROR, iSettem30);
	setItem(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_ABSERROR, iSettem31);
	setItem(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_ABSERROR, iSettem32);
	iSettem30->UpdateStructText(CVariantDataAddress(&pParas->m_fUActVal_AbsErr), 3);
	iSettem31->UpdateStructText(CVariantDataAddress(&pParas->m_fIActVal_AbsErr), 3);
	iSettem32->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_AbsErr), 3);

	item(HARMESTIMATEGRID_ROW_VOL,HARMESTIMATEGRID_COL_ABSERROR)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item(HARMESTIMATEGRID_ROW_CUR,HARMESTIMATEGRID_COL_ABSERROR)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item(HARMESTIMATEGRID_ROW_ACTIONTIME,HARMESTIMATEGRID_COL_ABSERROR)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

// 	setItem(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_SETVALUE, new QTableWidgetItem(QString::number(pParas->m_fUSet)));
// 	setItem(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_SETVALUE, new QTableWidgetItem(QString::number(pParas->m_fISet)));
// 	setItem(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_SETVALUE, new QTableWidgetItem(QString::number(pParas->m_fTimeSet)));
	QSettingItem *iSettem40 = new QSettingItem(this);
	QSettingItem *iSettem41 = new QSettingItem(this);
	QSettingItem *iSettem42 = new QSettingItem(this);
	setItem(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_SETVALUE, iSettem40);
	setItem(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_SETVALUE, iSettem41);
	setItem(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_SETVALUE, iSettem42);
	iSettem40->UpdateStructText(CVariantDataAddress(&pParas->m_fUSet), 3);
	iSettem41->UpdateStructText(CVariantDataAddress(&pParas->m_fISet), 3);
	iSettem42->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeSet), 3);

	item(HARMESTIMATEGRID_ROW_VOL,HARMESTIMATEGRID_COL_SETVALUE)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item(HARMESTIMATEGRID_ROW_CUR,HARMESTIMATEGRID_COL_SETVALUE)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item(HARMESTIMATEGRID_ROW_ACTIONTIME,HARMESTIMATEGRID_COL_SETVALUE)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	strText = "——";
// 	setItem(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, new QTableWidgetItem(QString::number(pParas->m_fTimeValue_AbsErrNeg)));
// 	setItem(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, new QTableWidgetItem(strText));
// 	setItem(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, new QTableWidgetItem(strText));

	QSettingItem *iSettem50 = new QSettingItem(this);
	QSettingItem *iSettem51 = new QSettingItem(this);
	QSettingItem *iSettem52 = new QSettingItem(this);
	setItem(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, iSettem50);
	setItem(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, iSettem51);
	setItem(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, iSettem52);
	iSettem52->UpdateStructText(CVariantDataAddress(&pParas->m_fTimeValue_AbsErrNeg), 3);
	iSettem50->UpdateText(strText);
	iSettem51->UpdateText(strText);

	item(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_SETVALUE)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_SETVALUE)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_SETVALUE)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	item(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_NEGATIVEABSERROR)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_NEGATIVEABSERROR)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_NEGATIVEABSERROR)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);


	for (int i = 0;i < 3; i++)
	{
		item(i, HARMESTIMATEGRID_COL_NAME)->setFlags(item(i, HARMESTIMATEGRID_COL_NAME)->flags() & ~Qt::ItemIsEditable);
		EnableRow(i, FALSE);

// 		item(i, HARMESTIMATEGRID_COL_RELERROR)->setFlags(item(i, HARMESTIMATEGRID_COL_RELERROR)->flags() & ~Qt::ItemIsEditable);
// 		item(i, HARMESTIMATEGRID_COL_ABSERROR)->setFlags(item(i, HARMESTIMATEGRID_COL_ABSERROR)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
	}

	CString str=g_pHarmTest->m_pHarmWidget->m_pParaWidget->m_strChanelText;

	if (pParas->m_bAuto)
	{
		if (str.Find(_T("U")) == 0 )		
		{
			EnableRow(HARMESTIMATEGRID_ROW_VOL);//电压
		}
		else if(str.Find(_T("I")) == 0)
		{
			EnableRow(HARMESTIMATEGRID_ROW_CUR);//电压
		}
	}
	
	EnableRow(HARMESTIMATEGRID_ROW_ACTIONTIME);//动作时间

	CbbErrorType(HARMESTIMATEGRID_ROW_VOL, pCbbError1->currentText());
	CbbErrorType(HARMESTIMATEGRID_ROW_CUR, pCbbError2->currentText());
	CbbErrorType(HARMESTIMATEGRID_ROW_ACTIONTIME, pCbbError3->currentText());

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(pCbbError1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
}

void HarmEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void HarmEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	int nRow = currentRow();
	CbbErrorType(nRow, strText);

}

void HarmEstimateGrid::slot_OnCellChanged(int row,int col)
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

	if(col==HARMESTIMATEGRID_COL_RELERROR)//相对误差
	{		
		fv=setLimit(0,100,fv);
		pItem->setText(QString::number(fv));
	}

	if(col==HARMESTIMATEGRID_COL_ABSERROR)//绝对误差
	{
		fv=setLimit(0,200,fv);
		pItem->setText(QString::number(fv));
	}


	if(col==HARMESTIMATEGRID_COL_SETVALUE)//整定值
	{		
		if (row==HARMESTIMATEGRID_ROW_VOL)
		{
			fv=setLimit(0,120,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==HARMESTIMATEGRID_ROW_CUR)
		{
			fv=setLimit(0,10,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==HARMESTIMATEGRID_ROW_ACTIONTIME)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));
		}
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

bool HarmEstimateGrid::eventFilter(QObject *obj, QEvent *event)
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

void HarmEstimateGrid::mousePressEvent(QMouseEvent * event)
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


void HarmEstimateGrid::SetItemEnable(int nRow, int nCol, BOOL bEnable)
{
	QTableWidgetItem *pItem = item(nRow, nCol);
	if (!pItem)
	{
		return;
	}


	bool bCbbState = true;
	if (nCol == HARMESTIMATEGRID_COL_RELERROR || nCol == HARMESTIMATEGRID_COL_ABSERROR || nCol == HARMESTIMATEGRID_COL_NEGATIVEABSERROR)
	{
		QComboBox* pCbb = (QComboBox*)cellWidget(nRow, HARMESTIMATEGRID_COL_ERRORTYPE);
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

void HarmEstimateGrid::CbbErrorType(int nIndex, CString strText)
{

	if (strText == g_sLangTxt_StateEstimate_AbsError)//绝对误差
	{
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_ABSERROR, TRUE);
		if (nIndex == HARMESTIMATEGRID_ROW_ACTIONTIME)
		{
			SetItemEnable(nIndex, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, TRUE);
		}
		else
		{
			SetItemEnable(nIndex, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, FALSE);
		}
	}
	else if (strText == g_sLangTxt_StateEstimate_RelError)//相对误差
	{
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_ABSERROR, FALSE);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, FALSE);
	}
	else if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_ABSERROR, FALSE);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, FALSE);
	}
	else
	{
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_ABSERROR, TRUE);
		SetItemEnable(nIndex, HARMESTIMATEGRID_COL_NEGATIVEABSERROR, TRUE);
	}
}

HarmEstimateDlg::HarmEstimateDlg(tmt_HarmParas* pParas, QWidget* parent) : QDialog(parent)
{
	Stt_Global_SettingParent(this);	//20240909 huangliang
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
}

HarmEstimateDlg::~HarmEstimateDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
}

void HarmEstimateDlg::InitUI()
{
	CString strTitle = g_sLangTxt_StateEstimate_ResultEstimate; 
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new HarmEstimateGrid(3, 6, this);
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
#endif

}

void HarmEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->m_fUActVal_RelErr = m_pGrid->item(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_RELERROR)->text().toFloat();
	m_pParas->m_fIActVal_RelErr = m_pGrid->item(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_RELERROR)->text().toFloat();
	m_pParas->m_fTimeValue_RelErr = m_pGrid->item(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_RELERROR)->text().toFloat();

	m_pParas->m_fUActVal_AbsErr = m_pGrid->item(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_ABSERROR)->text().toFloat();
	m_pParas->m_fIActVal_AbsErr = m_pGrid->item(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_ABSERROR)->text().toFloat();
	m_pParas->m_fTimeValue_AbsErr = m_pGrid->item(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_ABSERROR)->text().toFloat();
	m_pParas->m_fTimeValue_AbsErrNeg = m_pGrid->item(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_NEGATIVEABSERROR)->text().toFloat();

	m_pParas->m_nUActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
	m_pParas->m_nIActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_ERRORTYPE))->currentIndex();
	m_pParas->m_nTimeValue_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_ERRORTYPE))->currentIndex();

	m_pParas->m_fUSet = m_pGrid->item(HARMESTIMATEGRID_ROW_VOL, HARMESTIMATEGRID_COL_SETVALUE)->text().toFloat();
	m_pParas->m_fISet = m_pGrid->item(HARMESTIMATEGRID_ROW_CUR, HARMESTIMATEGRID_COL_SETVALUE)->text().toFloat();
	m_pParas->m_fTimeSet = m_pGrid->item(HARMESTIMATEGRID_ROW_ACTIONTIME, HARMESTIMATEGRID_COL_SETVALUE)->text().toFloat();

	accept();
}

void HarmEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}
