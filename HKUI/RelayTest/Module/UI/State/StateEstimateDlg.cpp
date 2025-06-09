#include "StateEstimateDlg.h"

#include "../Module/CommonMethod/commonMethod.h"


#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"

#include <QApplication>
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>
#include "../Controls/SttCheckBox.h"
#include "../Controls/SettingCtrls/QSettingItem.h"
#include "../SttTestCntrFrameBase.h"

#ifdef _PSX_QT_WINDOWS_
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
//#include "../SttTestCntrFrameBase.h"
#endif

#define  STATEGRID_COL_NAME				0		//名称
#define  STATEGRID_COL_SETVALUE			1		//整定值
#define  STATEGRID_COL_ERRORTYPE		2		//误差类型
#define  STATEGRID_COL_START			3		//计时起点
#define  STATEGRID_COL_BIN1				4		//起点开入
#define  STATEGRID_COL_END				5		//计时终点
#define  STATEGRID_COL_BIN2				6		//终点开入
#define  STATEGRID_COL_RELERROR			7		//相对误差
#define  STATEGRID_COL_ABSERROR			8		//绝对误差
#define  STATEGRID_COL_NEGATIVEABSERROR		9		//绝对误差(-)

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240909 huangliang

StateEstimateGrid::StateEstimateGrid(int rows, int columns, QWidget* parent) : QTableWidget(rows, columns, parent)
{
	m_pParas = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
	m_SelStateList.clear();
}

StateEstimateGrid::~StateEstimateGrid()
{

}

void StateEstimateGrid::InitGrid()
{
	CString strSelect, strName, strStart, strEnd, strErrorType, strRelError, strAbsError, strSettingValue, strBin, strNegativeAbsError;

// 	xlang_GetLangStrByFile(strSelect, "sSelect");
	xlang_GetLangStrByFile(strName, "sName");
	xlang_GetLangStrByFile(strStart, "StateEstimate_Start");
	//xlang_GetLangStrByFile(strEnd, "StateEstimate_End");
	xlang_GetLangStrByFile(strErrorType, "StateEstimate_ErrorType");
	//xlang_GetLangStrByFile(strRelError, "Native_Name");
	//xlang_GetLangStrByFile(strAbsError, "Native_Choose");
	xlang_GetLangStrByFile(strSettingValue, "StateEstimate_SettingValue");
	xlang_GetLangStrByFile(strBin, "Native_BinX");

// 	strStart = "计时起点";
	strEnd = g_sLangTxt_StateEstimate_End;
// 	strErrorType = "误差类型";
 	strRelError = g_sLangTxt_StateEstimate_RelError;
	strRelError += "(%)";
	strAbsError = g_sLangTxt_StateEstimate_AbsError;
	//strAbsError += "(s)";//绝对误差标题无需单位
	strNegativeAbsError = g_sLangTxt_StateEstimate_AbsError;
	strNegativeAbsError += "(-)";//绝对误差(-)
// 	strSettingValue = "整定值(s)";
// 	strBin = "开入";
	setHorizontalHeaderLabels(QStringList()/* << strSelect */ << strName << strSettingValue << strErrorType << strStart << strBin << strEnd << strBin << strRelError << strAbsError << strNegativeAbsError);
//	setColumnWidth(0, 40);
//	setColumnWidth(3, 120);
//	setColumnWidth(5, 120);
//	setColumnWidth(6, 150);
//	setColumnWidth(7, 80);
//	setColumnWidth(8, 70);
//	setColumnWidth(9, 60);
    // 设置列宽策略为自适应
    //this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
	this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
	//this->verticalHeader()->setDefaultSectionSize(40);
}


void StateEstimateGrid::slot_StateBinChanged(const QString& strText)
{
	QComboBox* pCbb = (QComboBox*)sender();
	long nRow = rowAt(pCbb->pos().y());
	long nCol = columnAt(pCbb->pos().x());
	CString strName;
    CString strText2;
    strText2 = strText;

	tmt_StatePara* pPara = NULL;
	for (int i = 0; i < m_pParas->m_nStateNumbers; i++)
	{
		pPara = &m_pParas->m_paraState[i];

		xlang_GetLangStrByFile(strName, "sState");
		strName += QString::number(i + 1);

// 		CString strName = pPara->m_strName;
        if(strName == strText2)
		{
			break;
		}
	}

	pCbb = (QComboBox*)cellWidget(nRow, nCol + 1);
	pCbb->clear();
	if(strText != /*"开入触发"*/g_sLangTxt_StateEstimate_BinTrigger)
	{
		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			if(pPara->m_binIn[i].nSelect)
			{
				char ch = 'A' + i;
				CString strText = /*"开入"*/g_sLangTxt_Native_BinX;
				strText += ch;
				pCbb->addItem(strText + " 0->1");
				pCbb->addItem(strText + " 1->0");
			}
		}
	}
	pCbb->addItem("--");
}

void StateEstimateGrid::InitStateBin(CString strStateName, long nRow, long nCol)
{
	QComboBox* pCbbStatesBin = new QComboBox(this);

	CString strName;
	if (strStateName != /*"开入触发"*/g_sLangTxt_StateEstimate_BinTrigger)
	{
		tmt_StatePara* pPara = NULL;
		for (int i = 0; i < m_pParas->m_nStateNumbers; i++)
		{
			pPara = &m_pParas->m_paraState[i];

// 			xlang_GetLangStrByFile(strName, "sState");
// 			strName += QString::number(i + 1);
//			CString strName = pPara->m_strName;

			if (pPara->m_strName == strStateName)
			{
				break;
			}
		}

		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			if (pPara->m_binIn[i].nSelect)
			{
				char ch = 'A' + i;
				CString strText = /*"开入"*/g_sLangTxt_Native_BinX;
				strText += ch;
				pCbbStatesBin->addItem(strText + " 0->1");
				pCbbStatesBin->addItem(strText + " 1->0");
			}
		}
		
	}
		pCbbStatesBin->addItem("--");


		CString strText;
		if (nCol == STATEGRID_COL_BIN1)
		{
			strText = m_pParas->m_paraEstimates[nRow].m_strTtripBegin_Bin;
		}
		else if (nCol == STATEGRID_COL_BIN2)
		{
			strText = m_pParas->m_paraEstimates[nRow].m_strTtripEnd_Bin;
		}

		if(strText == "")
		{
			strText = "--";
		}
		else
		{
			CString strBin = strText.Mid(0, strText.Find("$"));
			CString strTemp = strText.Mid(strText.GetLength() - 1);
			long nCh = CString_To_long(strBin.Mid(strBin.Find("_") + 1));
			char ch = 'A' + nCh;
			if (strTemp == "0")
			{
				strText = /*"开入"*/g_sLangTxt_Native_BinX;
				strText += ch;
				strText += " 1->0";
			}
			else
			{
				strText = /*"开入"*/g_sLangTxt_Native_BinX;
				strText += ch;
				strText +=" 0->1";
			}
		}

		long nIndex = pCbbStatesBin->findText(strText);
		if(nIndex == -1)
		{
			nIndex = 0;
		}
		pCbbStatesBin->setCurrentIndex(nIndex);
	
	setCellWidget(nRow, nCol, pCbbStatesBin);

	ComboxModelStyle(pCbbStatesBin);
}

void StateEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void StateEstimateGrid::InitStateData(long nIndexEstimate)
{
	m_SelStateList.clear();
	QComboBox* pCbbStatesStart_State = new QComboBox(this);
	QComboBox* pCbbStatesEnd_State = new QComboBox(this);
	for(int i = 0; i < m_pParas->m_nStateNumbers; i++)
	{
		tmt_StatePara* pPara = &m_pParas->m_paraState[i];
		if(pPara->m_bSelected)
		{
			CString strName = pPara->m_strName;
			if(strName.GetLength())
			{
				m_SelStateList.append(i);
				pCbbStatesStart_State->addItem(strName);
				pCbbStatesEnd_State->addItem(strName);
			}
			else
			{
				xlang_GetLangStrByFile(strName, "sState");
				strName += QString::number(i + 1);
				pCbbStatesStart_State->addItem(strName);
				pCbbStatesEnd_State->addItem(strName);
				//strcpy(pPara->m_strName, strName.GetString());//20230911 suyang 给结构体赋值会导致在插入时状态序号重复
			}
		}
	}
	pCbbStatesStart_State->addItem(/*"开入触发"*/g_sLangTxt_StateEstimate_BinTrigger);
	pCbbStatesEnd_State->addItem(/*"开入触发"*/g_sLangTxt_StateEstimate_BinTrigger);

	CString strText = m_pParas->m_paraEstimates[nIndexEstimate].m_strTtripBegin_State;
	int nStateIndex = CString_To_long(strText.Mid(6));
	long nIndex = 0;

	if(strText == "BinTrig")
	{
		strText = /*"开入触发"*/g_sLangTxt_StateEstimate_BinTrigger;
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbStatesStart_State->setCurrentText(strText);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbStatesStart_State,strText);
#endif
	}
 	else
 	{
		strText.Format("状态%d", CString_To_long(strText.Mid(6)) + 1);	
		
	for (int nListIndex = 0; nListIndex < m_SelStateList.size(); nListIndex++)
	{
		if (nStateIndex == m_SelStateList[nListIndex])
	{
			nIndex = nListIndex;
		}
	}
		if (nIndex == -1)
	{
		nIndex = 0;
	}
	pCbbStatesStart_State->setCurrentIndex(nIndex);
 	}
	
	InitStateBin(pCbbStatesStart_State->currentText(), nIndexEstimate, STATEGRID_COL_BIN1);

	strText = m_pParas->m_paraEstimates[nIndexEstimate].m_strTtripEnd_State;
	nStateIndex = CString_To_long(strText.Mid(6));
	if(strText == "BinTrig")
	{
		strText = /*"开入触发"*/g_sLangTxt_StateEstimate_BinTrigger;
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		pCbbStatesEnd_State->setCurrentText(strText);
#else
		Stt_Global_SetComboBoxIndexByText(pCbbStatesEnd_State,strText);
#endif
	}
	else
	{
// 		strText.Format("状态%d", CString_To_long(strText.Mid(6)) + 1);	
	nIndex = pCbbStatesEnd_State->findText(strText);
	for (int nListIndex = 0; nListIndex < m_SelStateList.size(); nListIndex++)
	{
		if (nStateIndex == m_SelStateList[nListIndex])
	{
			nIndex = nListIndex;
	}
	}
	if (nIndex == -1)
	{
		nIndex = 0;
	}
	pCbbStatesEnd_State->setCurrentIndex(nIndex);
	}

	InitStateBin(pCbbStatesEnd_State->currentText(), nIndexEstimate, STATEGRID_COL_BIN2);

	setCellWidget(nIndexEstimate, STATEGRID_COL_START, pCbbStatesStart_State);
	setCellWidget(nIndexEstimate, STATEGRID_COL_END, pCbbStatesEnd_State);

	connect(pCbbStatesStart_State, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_StateBinChanged(const QString &)));
	connect(pCbbStatesEnd_State, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_StateBinChanged(const QString &)));

	ComboxModelStyle(pCbbStatesStart_State);
	ComboxModelStyle(pCbbStatesEnd_State);
}

void StateEstimateGrid::InitData(tmt_StateParas* pParas)
{
	m_pParas = pParas;
	//获取状态数
	for (int i = 0; i < 10; i++)
	{
		InitStateData(i);

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

		CString strActTime;
		xlang_GetLangStrByFile(strActTime, "Native_ActionTime");

		//cl20230726 QSttCheckBox居中
// 		QWidget *UserWidget = new QWidget();
// 		QHBoxLayout *UserLayout = new QHBoxLayout();
// 		QSttCheckBox* pCbUser = new QSttCheckBox(this);
// 		UserLayout->addWidget(pCbUser);
// 		UserLayout->setMargin(0);
// 		UserLayout->setAlignment(pCbUser, Qt::AlignCenter);  
// 		UserWidget->setLayout(UserLayout);
// 		setCellWidget(i, 0, UserWidget);
		
		setItem(i, STATEGRID_COL_NAME, new QTableWidgetItem(strActTime));
		item(i, STATEGRID_COL_NAME)->setFlags(item(i, STATEGRID_COL_NAME)->flags() & ~Qt::ItemIsEditable);

		setCellWidget(i, STATEGRID_COL_ERRORTYPE, pCbbError);
/*		pCbUser->setChecked(pParas->m_paraEstimates[i].m_bUseError);*/
		pCbbError->setCurrentIndex(pParas->m_paraEstimates[i].m_nErrorLogic);

		//20240909  huangliang 
		//setItem(i, STATEGRID_COL_RELERROR, new QTableWidgetItem(QString::number(pParas->m_paraEstimates[i].m_fActT_RelErr)));
		//setItem(i, STATEGRID_COL_ABSERROR, new QTableWidgetItem(QString::number(pParas->m_paraEstimates[i].m_fActT_AbsErr)));
		//setItem(i, STATEGRID_COL_NEGATIVEABSERROR, new QTableWidgetItem(QString::number(pParas->m_paraEstimates[i].m_fActT_AbsErrNeg)));
		//setItem(i, STATEGRID_COL_SETVALUE, new QTableWidgetItem(QString::number(pParas->m_paraEstimates[i].m_fTset)));
		//setItem(i, STATEGRID_COL_SETVALUE, new QTableWidgetItem(QString::number(pParas->m_paraEstimates[i].m_fTset)));
		QSettingItem *iSettemRelErr = new QSettingItem(this);
		QSettingItem *iSettemAbsErr = new QSettingItem(this);
		QSettingItem *iSettemAbsErrNeg = new QSettingItem(this);
		QSettingItem *iSettemTset = new QSettingItem(this);
		setItem(i, STATEGRID_COL_RELERROR, iSettemRelErr);
		setItem(i, STATEGRID_COL_ABSERROR, iSettemAbsErr);
		setItem(i, STATEGRID_COL_NEGATIVEABSERROR, iSettemAbsErrNeg);
		setItem(i, STATEGRID_COL_SETVALUE, iSettemTset);
		iSettemRelErr->UpdateStructText(CVariantDataAddress(&pParas->m_paraEstimates[i].m_fActT_RelErr), 3);
		iSettemAbsErr->UpdateStructText(CVariantDataAddress(&pParas->m_paraEstimates[i].m_fActT_AbsErr), 3);
		iSettemAbsErrNeg->UpdateStructText(CVariantDataAddress(&pParas->m_paraEstimates[i].m_fActT_AbsErrNeg), 3);
		iSettemTset->UpdateStructText(CVariantDataAddress(&pParas->m_paraEstimates[i].m_fTset), 3);

		item(i,STATEGRID_COL_NAME)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item(i, STATEGRID_COL_RELERROR)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		item(i, STATEGRID_COL_ABSERROR)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		item(i, STATEGRID_COL_NEGATIVEABSERROR)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		item(i, STATEGRID_COL_SETVALUE)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		
		ComboxModelStyle(pCbbError);

 		QString str = pCbbError->currentText();	
		CbbErrorType(i,str);

		connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
		connect(pCbbError, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	}
}

void StateEstimateGrid::CbbErrorType(int nIndex, CString strText)
{
	if (strText==g_sLangTxt_StateEstimate_AbsError)
	{
// 		item(nIndex, 7)->setFlags(item(nIndex, 7)->flags() & ~Qt::ItemIsEditable);
// 		item(nIndex, 8)->setFlags(item(nIndex, 8)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		SetItemEnable(nIndex, STATEGRID_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, STATEGRID_COL_ABSERROR, TRUE);
		SetItemEnable(nIndex, STATEGRID_COL_NEGATIVEABSERROR, TRUE);
	}
	else if (strText==g_sLangTxt_StateEstimate_RelError)
	{
// 		item(nIndex, 7)->setFlags(item(nIndex, 7)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
// 		item(nIndex, 8)->setFlags(item(nIndex, 8)->flags() & ~Qt::ItemIsEditable);
		SetItemEnable(nIndex, STATEGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, STATEGRID_COL_ABSERROR, FALSE);
		SetItemEnable(nIndex, STATEGRID_COL_NEGATIVEABSERROR, FALSE);
	}
	else if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		SetItemEnable(nIndex, STATEGRID_COL_RELERROR, FALSE);
		SetItemEnable(nIndex, STATEGRID_COL_ABSERROR, FALSE);
		SetItemEnable(nIndex, STATEGRID_COL_NEGATIVEABSERROR, FALSE);
	}
	else
	{
// 		item(nIndex, 7)->setFlags(item(nIndex, 7)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
// 		item(nIndex, 8)->setFlags(item(nIndex, 8)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		SetItemEnable(nIndex, STATEGRID_COL_RELERROR, TRUE);
		SetItemEnable(nIndex, STATEGRID_COL_ABSERROR, TRUE);
		SetItemEnable(nIndex, STATEGRID_COL_NEGATIVEABSERROR, TRUE);
	}
}

void StateEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
// 	int nRow = currentRow();
	QComboBox* pCbb = (QComboBox*)sender();
	int nRow = rowAt(pCbb->pos().y());

	CbbErrorType(nRow,strText);
}

void StateEstimateGrid::slot_OnCellChanged(int row,int col)
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

	if(col==STATEGRID_COL_RELERROR)//相对误差
	{
		fv=setLimit(0,100,fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if (col == STATEGRID_COL_ABSERROR)//绝对误差
	{
		fv=setLimit(0,200,fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if (col == STATEGRID_COL_NEGATIVEABSERROR)//绝对误差
	{
		fv = setLimit(0, 200, fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if(col==STATEGRID_COL_SETVALUE)//整定值
	{		
		fv=setLimit(0,999,fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

bool StateEstimateGrid::eventFilter(QObject *obj, QEvent *event)
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

void StateEstimateGrid::mousePressEvent(QMouseEvent * event)
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


void StateEstimateGrid::SetItemEnable(int nRow, int nCol, BOOL bEnable)
{
	QTableWidgetItem *pItem = item(nRow, nCol);
	if (!pItem)
	{
		return;
	}

	pItem->setFlags(bEnable ? pItem->flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable
		: pItem->flags() & ~Qt::ItemIsEditable &~Qt::ItemIsEnabled &~Qt::ItemIsSelectable);

	bool bCbbState = true;
	if (nCol == STATEGRID_COL_RELERROR || nCol == STATEGRID_COL_ABSERROR)
	{
		QComboBox* pCbb = (QComboBox*)cellWidget(nRow, STATEGRID_COL_ERRORTYPE);
		if (pCbb)
		{
			bCbbState = pCbb->isEnabled();
		}
	}

	if (bCbbState && bEnable)
	{
		pItem->setForeground(Qt::black);  // 黑色背景
	}
	else
	{
		pItem->setForeground(Qt::gray);  // 灰色背景
	}
}

StateEstimateDlg::StateEstimateDlg(tmt_StateParas* pParas, QWidget* parent) : QDialog(parent)
{
	Stt_Global_SettingParent(this);	//20240909 huangliang
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
}

StateEstimateDlg::~StateEstimateDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
}

void StateEstimateDlg::InitUI()
{
	CString strTitle = /*"结果评估"*/g_sLangTxt_StateEstimate_ResultEstimate;
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new StateEstimateGrid(10, 10, this);
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

	this->setLayout(pVLayout);

	//resize(1000, 520);
#ifdef _PSX_QT_WINDOWS_		
	//2024-8-1 wuxinyi 在2880*1800分辨率显示不全
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect rect = desktopWidget->screenGeometry();
	float fWidth = rect.width() * g_dUIShowCoef;

	if (fWidth >= 2280)
	{
		resize(1850, 900);
	}
	else
	{
		resize(1250, 520);
	}
#else
	resize(1000, 520);
#endif

}

CString StateEstimateDlg::SaveState(long nRow, long nCol)
{
	QComboBox* pCbbState = (QComboBox*)m_pGrid->cellWidget(nRow, nCol);
	long nIndex = pCbbState->currentIndex();
	CString strText;
	if(nIndex == pCbbState->count() - 1)
	{
		if (nCol == STATEGRID_COL_START)
		{
			strText = strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripBegin_State, "BinTrig");
		}
		else
		{
			strText = strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripEnd_State, "BinTrig");
		}
	}
	else
	{
		//strText = "state_" + QString::number(nIndex);
		int nCurIndex = m_pGrid->m_SelStateList.at(nIndex);
		strText = "state_" + QString::number(nCurIndex);

		//strText = pCbbState->currentText();
		if (nCol == STATEGRID_COL_START)
		{
			strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripBegin_State, strText.GetString());
		}
		else
		{
			strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripEnd_State, strText.GetString());
		}
	}
	return strText;
}

CString StateEstimateDlg::SaveStateBin(long nRow, long nCol)
{
	QComboBox* pCbbBin = (QComboBox*)m_pGrid->cellWidget(nRow, nCol);
	CString strBin = pCbbBin->currentText();
	if(strBin.GetLength())
	{
		if(strBin == "--")
		{
			if (nCol == STATEGRID_COL_BIN1)
			{
				strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripBegin_Bin, "");
			}
			else
			{
				strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripEnd_Bin, "");
			}
			return "";
		}

		strBin = strBin.Mid(2);

		int i = 0;
		for (; i < MAX_BINARYIN_COUNT; i++)
		{
			char ch = 'A' + i;
			CString strTemp;
			strTemp += ch;
			if(strTemp == strBin.Mid(0, 1))
			{
				break;
			}
		}

		CString str1;
		str1.Format("ActBin_%d", i);
		CString str2 = "$" + strBin.Mid(strBin.GetLength() - 1);
		CString strText = str1 + str2;
		if (nCol == STATEGRID_COL_BIN1)
		{
			strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripBegin_Bin, strText.GetString());
		}
		else
		{
			strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripEnd_Bin, strText.GetString());
		}

		return strText;
	}
	else
	{
		if (nCol == STATEGRID_COL_BIN1)
		{
			strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripBegin_Bin, "");
		}
		else
		{
			strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripEnd_Bin, "");
		}
	}
	return "";
};

void StateEstimateDlg::slot_btnOK_Clicked()
{
	CString strCbbText;
	for (int i = 0; i < 10; i++)
	{
// 		QWidget* pUseWidget = (QWidget*)m_pGrid->cellWidget(i, 0);
// 		QSttCheckBox* pCbUse = (QSttCheckBox*)pUseWidget->children().at(1); //cl20230808
		QComboBox* pUseWidget = (QComboBox*)m_pGrid->cellWidget(i, STATEGRID_COL_ERRORTYPE);
		CString strCbbText = pUseWidget->currentText();
		//不评估与m_bUseError选择无关，故注释
// 		if (strCbbText == g_sLangTxt_Distance_ErrorNot)
// 			m_pParas->m_paraEstimates[i].m_bUseError = FALSE;
// 		else
// 			m_pParas->m_paraEstimates[i].m_bUseError = TRUE;

		SaveState(i, STATEGRID_COL_START);
		SaveStateBin(i, STATEGRID_COL_BIN1);
		SaveState(i, STATEGRID_COL_END);
		SaveStateBin(i, STATEGRID_COL_BIN2);

		QComboBox* pCbbErrorType = (QComboBox*)m_pGrid->cellWidget(i, STATEGRID_COL_ERRORTYPE);
		m_pParas->m_paraEstimates[i].m_nErrorLogic = pCbbErrorType->currentIndex();

		m_pParas->m_paraEstimates[i].m_fActT_RelErr = m_pGrid->item(i, STATEGRID_COL_RELERROR)->text().toFloat();
		m_pParas->m_paraEstimates[i].m_fActT_AbsErr = m_pGrid->item(i, STATEGRID_COL_ABSERROR)->text().toFloat();
		m_pParas->m_paraEstimates[i].m_fTset = m_pGrid->item(i, STATEGRID_COL_SETVALUE)->text().toFloat();
		m_pParas->m_paraEstimates[i].m_fActT_AbsErrNeg = m_pGrid->item(i, STATEGRID_COL_NEGATIVEABSERROR)->text().toFloat();

	}

	accept();
}

void StateEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}


