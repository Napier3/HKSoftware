#include "StateBinarySetDlg.h"
#include "../../Module/UI/Module/CommonMethod/commonMethod.h"
#include "SttMacroParaEditViewState.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
//#include "../SttTestCntrFrameBase.h"
#include "../Controls/SttCheckBox.h"
#include "../../Module/XLangResource_Native.h"

QStateBinarySetDlg::QStateBinarySetDlg(QWidget *parent)
: QDialog(parent)
{
	m_pStatePara = NULL;
	
	m_pBinBox = NULL;
	m_pBoutBox = NULL;

	//m_pTrigerHoldTime = NULL;
	m_pOutputHoldTime = NULL;
	
	//m_pTrigerHoldTimeEdit = NULL;
	m_pOutputHoldTimeEdit = NULL;

// 	m_pBin_A = NULL;
// 	m_pBin_B = NULL;
// 	m_pBin_C = NULL;
// 	m_pBin_D = NULL;
	m_pBin_E = NULL;
	m_pBin_F= NULL;
	m_pBin_G= NULL;
	m_pBin_H= NULL;
	m_pBin_I= NULL;
	m_pBin_J= NULL;

	m_pLogicOr= NULL;
	m_pLogicAnd= NULL;

	m_pBout_5= NULL;
	m_pBout_6= NULL;
	m_pBout_7= NULL;
	m_pBout_8= NULL;
	m_pBout_9= NULL;
	m_pBout_10= NULL;
	m_pChk_HoldTime = NULL;

	initUI();
	SetStateParaFont();
	initConnections();
}

QStateBinarySetDlg::~QStateBinarySetDlg()
{

}
void QStateBinarySetDlg::SetStateParaFont()
{
// 	m_pBin_A->setFont(*g_pSttGlobalFont);
// 	m_pBin_B->setFont(*g_pSttGlobalFont);
// 	m_pBin_C->setFont(*g_pSttGlobalFont);
// 	m_pBin_D->setFont(*g_pSttGlobalFont);
	m_pBin_E->setFont(*g_pSttGlobalFont);
	m_pBin_F->setFont(*g_pSttGlobalFont);
	m_pBin_G->setFont(*g_pSttGlobalFont);
	m_pBin_H->setFont(*g_pSttGlobalFont);
	m_pBin_I->setFont(*g_pSttGlobalFont);
	m_pBin_J->setFont(*g_pSttGlobalFont);
	
	m_pBout_5->setFont(*g_pSttGlobalFont);
	m_pBout_6->setFont(*g_pSttGlobalFont);
	m_pBout_7->setFont(*g_pSttGlobalFont);
	m_pBout_8->setFont(*g_pSttGlobalFont);
	m_pBout_9->setFont(*g_pSttGlobalFont);
	m_pBout_10->setFont(*g_pSttGlobalFont);

	m_pBinBox->setFont(*g_pSttGlobalFont);
	m_pBoutBox->setFont(*g_pSttGlobalFont);
	//m_pTrigerHoldTime->setFont(*g_pSttGlobalFont);
	m_pOutputHoldTime->setFont(*g_pSttGlobalFont);
	//m_pTrigerHoldTimeEdit->setFont(*g_pSttGlobalFont);
	m_pOutputHoldTimeEdit->setFont(*g_pSttGlobalFont);
	m_pLogicAnd->setFont(*g_pSttGlobalFont);
	m_pLogicOr->setFont(*g_pSttGlobalFont);

	m_pbn_Ok->setFont(*g_pSttGlobalFont);
	m_pbn_Cancel->setFont(*g_pSttGlobalFont);
}


void QStateBinarySetDlg::initUI()
{
	CString strText;
	resize(600,400);
	this->setFixedWidth(600);
	this->setFixedHeight(400);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	xlang_GetLangStrByFile(strText, "Native_Switch");
	setWindowTitle(strText);

	strText=_T("开入量");
	m_pBinBox = new QSttGroupBox(strText);
	strText=_T("开出量");
	m_pBoutBox = new QSttGroupBox(strText);
	//m_pTrigerHoldTime = new QLabel(tr("触发后保持时间:"));
    strText=_T("保持时间");
	m_pOutputHoldTime = new QLabel(strText);
	//m_pTrigerHoldTimeEdit = new QSttLineEdit(this);
	m_pOutputHoldTimeEdit = new QSttLineEdit(this);
// 	strText = _T("A");
// 	m_pBin_A = new QSttCheckBox(strText);
// 	strText = _T("B");
// 	m_pBin_B = new QSttCheckBox(strText);
// 	strText = _T("C");
// 	m_pBin_C = new QSttCheckBox(strText);
// 	strText = _T("D");
// 	m_pBin_D = new QSttCheckBox(strText);
	strText = _T("E");
	m_pBin_E = new QSttCheckBox(strText);
	strText = _T("F");
	m_pBin_F= new QSttCheckBox(strText);
	strText = _T("G");
	m_pBin_G= new QSttCheckBox(strText);
	strText = _T("H");
	m_pBin_H= new QSttCheckBox(strText);
	strText = _T("I");
	m_pBin_I= new QSttCheckBox(strText);
	strText = _T("J");
	m_pBin_J= new QSttCheckBox(strText);

    strText = _T("逻辑或");
	m_pLogicOr= new QRadioButton(strText);
    strText = _T("逻辑与");
	m_pLogicAnd= new QRadioButton(strText);

    strText = _T("5");
	m_pBout_5= new QSttCheckBox(strText);
	strText = _T("6");
	m_pBout_6= new QSttCheckBox(strText);
	strText = _T("7");
	m_pBout_7= new QSttCheckBox(strText);
	strText = _T("8");
	m_pBout_8= new QSttCheckBox(strText);
	strText = _T("9");
	m_pBout_9= new QSttCheckBox(strText);
	strText = _T("10");
	m_pBout_10= new QSttCheckBox(strText);
	strText = _T("");
	m_pChk_HoldTime = new QSttCheckBox(strText);

	xlang_SetLangStrToWidget(m_pBinBox, "Native_Bin", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(m_pBoutBox, "Native_Bout", XLang_Ctrls_QGroupBox);
	//xlang_SetLangStrToWidget(m_pTrigerHoldTime, "State_TrigerHoldTime", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pOutputHoldTime, "State_HoldTime", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pLogicOr, "Native_LogicOr", XLang_Ctrls_QRadioButton);
	xlang_SetLangStrToWidget(m_pLogicAnd, "Native_LogicAnd", XLang_Ctrls_QRadioButton);
	

	QVBoxLayout* m_pMainLayout = new QVBoxLayout(this);
	m_pMainLayout->setSpacing(2);
	m_pMainLayout->setContentsMargins(2, 2, 2, 2);
	m_pMainLayout->setObjectName(QString::fromUtf8("gridLayout"));

	QGridLayout* pGridLayoutTop = new QGridLayout(m_pBinBox);
// 	pGridLayoutTop->addWidget(m_pBin_A,0,0);
// 	pGridLayoutTop->addWidget(m_pBin_B,0,1);
// 	pGridLayoutTop->addWidget(m_pBin_C,0,2);
// 	pGridLayoutTop->addWidget(m_pBin_D,0,3);
	pGridLayoutTop->addWidget(m_pBin_E,0,0);
	pGridLayoutTop->addWidget(m_pLogicOr,0,5);
	pGridLayoutTop->addWidget(m_pBin_F,0,1);
	pGridLayoutTop->addWidget(m_pBin_G,0,2);
	pGridLayoutTop->addWidget(m_pBin_H,0,3);
	pGridLayoutTop->addWidget(m_pBin_I,0,4);
	pGridLayoutTop->addWidget(m_pBin_J,1,0);
	pGridLayoutTop->addWidget(m_pLogicAnd,1,5);
	for (int i=0;i<6;i++)
	{
		pGridLayoutTop->setColumnStretch(i,1);
	}
	m_pMainLayout->addWidget(m_pBinBox);

	QVBoxLayout *pVerLayout = new QVBoxLayout(m_pBoutBox);
	QGridLayout* pGridLayoutbottom = new QGridLayout(m_pBoutBox);
	pVerLayout->addLayout(pGridLayoutbottom);

	pGridLayoutbottom->addWidget(m_pBout_5,0,0);
	pGridLayoutbottom->addWidget(m_pBout_6,0,1);
	pGridLayoutbottom->addWidget(m_pBout_7,0,2);
	pGridLayoutbottom->addWidget(m_pBout_8,0,3);
	pGridLayoutbottom->addWidget(m_pBout_9,0,4);
	pGridLayoutbottom->addWidget(m_pBout_10,0,5);
	for (int i=0;i<6;i++)
	{
		pGridLayoutbottom->setColumnStretch(i,1);
	}
    
//  	pGridLayoutbottom = new QGridLayout(m_pBoutBox);
//  	pVerLayout->addLayout(pGridLayoutbottom);
//      pGridLayoutbottom->addWidget(m_pOutputHoldTime,0,0);
// 	    pGridLayoutbottom->addWidget(m_pChk_HoldTime,0,	1);
//  	pGridLayoutbottom->addWidget(m_pOutputHoldTimeEdit,0,2);
 	

    QHBoxLayout *pHOutputHoldTime=new QHBoxLayout();
	pHOutputHoldTime->addWidget(m_pOutputHoldTime);
	pHOutputHoldTime->addWidget(m_pChk_HoldTime);
	pHOutputHoldTime->addWidget(m_pOutputHoldTimeEdit);
	if(xlang_IsCurrXLanguageChinese())
	{
	pHOutputHoldTime->addStretch(2);

	}
	pVerLayout->addLayout(pHOutputHoldTime);

    m_pMainLayout->addWidget(m_pBoutBox);

	m_pbn_Ok = new QPushButton(this);
	//strText = _T("确定");
	m_pbn_Ok->setText(g_sLangTxt_OK);//确定-LCQ
	m_pbn_Cancel = new QPushButton(this);
	//strText = _T("取消");
	m_pbn_Cancel->setText(g_sLangTxt_Cancel);//取消-LCQ

	QHBoxLayout* m_pOkCancel_HBoxLayout = new QHBoxLayout;
	m_pOkCancel_HBoxLayout->addStretch();
	m_pOkCancel_HBoxLayout->addWidget(m_pbn_Ok);
	m_pOkCancel_HBoxLayout->addSpacing(10);
	m_pOkCancel_HBoxLayout->addWidget(m_pbn_Cancel);
	m_pOkCancel_HBoxLayout->addStretch();
	m_pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);

	m_pMainLayout->addLayout(m_pOkCancel_HBoxLayout);

	setLayout(m_pMainLayout);	

}

void QStateBinarySetDlg::initConnections()
{
	connect(m_pbn_Cancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(m_pbn_Ok,SIGNAL(clicked()), this, SLOT(slot_OkClicked()));

#ifdef _PSX_QT_LINUX_
    //connect(m_pTrigerHoldTimeEdit, SIGNAL(clicked()), this, SLOT(slot_lne_TrigerHoldTimeChanged()),Qt::UniqueConnection);
    connect(m_pOutputHoldTimeEdit, SIGNAL(clicked ()), this, SLOT(slot_lne_OutPutHoldTimeChanged()),Qt::UniqueConnection);
#endif
	connect(m_pChk_HoldTime, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPutHoldTimeStateChanged(int)),Qt::UniqueConnection);
	connect(m_pOutputHoldTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_OutPutHoldTimeChangedKeyBoard()),Qt::UniqueConnection);
    //connect(m_pTrigerHoldTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_TrigerHoldTimeChangedKeyBoard()));
}

void QStateBinarySetDlg::setData(tmt_StatePara* pStatePara)
{
	ASSERT(pStatePara != NULL);
	m_pStatePara = pStatePara;
	UpdateData();
	initConnections();
	UpdateInput();
	UpdateOutPut();
}

void QStateBinarySetDlg::UpdateData()
{
// 	if (m_pStatePara->m_fTimeAfterTrigger <= 0)
// 	{
// 		m_pTrigerHoldTimeEdit->setText("");
// 	}
// 	else
// 	{
// 		m_pTrigerHoldTimeEdit->setText(QString::number(m_pStatePara->m_fTimeAfterTrigger,'f',3));
// 	}

	if (m_pStatePara->m_fOutputHoldTime <=0 )
	{
		m_pOutputHoldTimeEdit->setText("");
		m_pOutputHoldTimeEdit->setDisabled(true);
		m_pChk_HoldTime->setChecked(false);
	}
	else
	{
		m_pOutputHoldTimeEdit->setText(QString::number(m_pStatePara->m_fOutputHoldTime,'f',3));
		m_pOutputHoldTimeEdit->setDisabled(false);
		m_pChk_HoldTime->setChecked(true);
	}

	UpdateInput();
	UpdateOutPut();
}

void QStateBinarySetDlg::UpdateInput()
{
	if (m_pStatePara == NULL)
	{
		return;
	}
	Global_CheckBinSelect(m_pStatePara->m_binIn,g_nBinCount, m_pStatePara->m_nBinLogic);
// 	GlobalSetQcheckState_BinaryIn(m_pBin_A,m_pStatePara->m_binIn,0);
// 	GlobalSetQcheckState_BinaryIn(m_pBin_B,m_pStatePara->m_binIn,1);
// 	GlobalSetQcheckState_BinaryIn(m_pBin_C,m_pStatePara->m_binIn,2);
// 	GlobalSetQcheckState_BinaryIn(m_pBin_D,m_pStatePara->m_binIn,3);
	GlobalSetQcheckState_BinaryIn(m_pBin_E,m_pStatePara->m_binIn,4);
	GlobalSetQcheckState_BinaryIn(m_pBin_F,m_pStatePara->m_binIn,5);
	GlobalSetQcheckState_BinaryIn(m_pBin_G,m_pStatePara->m_binIn,6);
	GlobalSetQcheckState_BinaryIn(m_pBin_H,m_pStatePara->m_binIn,7);
	GlobalSetQcheckState_BinaryIn(m_pBin_I,m_pStatePara->m_binIn,8);
	GlobalSetQcheckState_BinaryIn(m_pBin_J,m_pStatePara->m_binIn,9);

	if (m_pStatePara->m_nBinLogic)
	{
		m_pLogicAnd->setChecked(true);
	}
	else
	{
		m_pLogicOr->setChecked(true);
	}
}

void QStateBinarySetDlg::UpdateOutPut()
{

	if (m_pStatePara == NULL)
	{
		return;
	}
	GlobalSetQcheckState_BinaryOut(m_pBout_5,m_pStatePara->m_binOut,4);
	GlobalSetQcheckState_BinaryOut(m_pBout_6,m_pStatePara->m_binOut,5);
	GlobalSetQcheckState_BinaryOut(m_pBout_7,m_pStatePara->m_binOut,6);
	GlobalSetQcheckState_BinaryOut(m_pBout_8,m_pStatePara->m_binOut,7);
	GlobalSetQcheckState_BinaryOut(m_pBout_9,m_pStatePara->m_binOut,8);
	GlobalSetQcheckState_BinaryOut(m_pBout_10,m_pStatePara->m_binOut,9);

	if (m_pStatePara->m_nTriggerCondition == TMT_MDSTATE_TIMETRIGGER)	//时间触发
	{
		//m_pTrigerHoldTimeEdit->setDisabled(true);
		SetBinaryInEnable(false);
	}
	else if (m_pStatePara->m_nTriggerCondition == TMT_MDSTATE_TIMEBINTRIGGER)//时间+开入量
	{
		//m_pTrigerHoldTimeEdit->setDisabled(false);
		SetBinaryInEnable(true);
// 		if (m_pTrigerHoldTimeEdit->text().isEmpty())
// 		{
// 			m_pTrigerHoldTimeEdit->setText("0.000");
// 		}
	}
	else if (m_pStatePara->m_nTriggerCondition == TMT_MDSTATE_BINTRIGGER)//开入量触发
	{
		//m_pTrigerHoldTimeEdit->setDisabled(false);
		SetBinaryInEnable(true);
// 		if (m_pTrigerHoldTimeEdit->text().isEmpty())
// 		{
// 			m_pTrigerHoldTimeEdit->setText("0.000");
// 		}
	}
	else if (m_pStatePara->m_nTriggerCondition == TMT_MDSTATE_MEARSURETRIGGER)  //手动触发
	{
		//m_pTrigerHoldTimeEdit->setDisabled(true);
		SetBinaryInEnable(false);
	}
	else if (m_pStatePara->m_nTriggerCondition == TMT_MDSTATE_GPSBTRIGGER)//GPS/B码触发
	{
		//m_pTrigerHoldTimeEdit->setDisabled(true);
		SetBinaryInEnable(false);
	}
}

void QStateBinarySetDlg::startInit()
{
	m_pBinBox->setDisabled(true);
	m_pBoutBox->setDisabled(true);
}

void QStateBinarySetDlg::stopInit()
{
	m_pBinBox->setDisabled(false);
	m_pBoutBox->setDisabled(false);
}


void QStateBinarySetDlg::SetBinaryInEnable(bool bFlag)
{
// 	GlobalSetQcheckEnable_Binary(m_pBin_A,0,g_nBinCount,bFlag);
// 	GlobalSetQcheckEnable_Binary(m_pBin_B,1,g_nBinCount,bFlag);
// 	GlobalSetQcheckEnable_Binary(m_pBin_C,2,g_nBinCount,bFlag);
// 	GlobalSetQcheckEnable_Binary(m_pBin_D,3,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_E,4,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_F,5,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_G,6,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_H,7,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_I,8,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_J,9,g_nBinCount,bFlag);

	m_pLogicAnd->setEnabled(bFlag);
	m_pLogicOr->setEnabled(bFlag);
}

void QStateBinarySetDlg::slot_OkClicked()
{

// 	if (m_pBin_A->checkState() == Qt::Checked)
// 	{
// 		m_pStatePara->m_binIn[0].nSelect = 1;
// 	}
// 	else
// 	{
// 		m_pStatePara->m_binIn[0].nSelect = 0;
// 	}
// 
// 	if (m_pBin_B->checkState() == Qt::Checked)
// 	{
// 		m_pStatePara->m_binIn[1].nSelect = 1;
// 	}
// 	else
// 	{
// 		m_pStatePara->m_binIn[1].nSelect = 0;
// 	}
// 
// 	if (m_pBin_C->checkState() == Qt::Checked)
// 	{
// 		m_pStatePara->m_binIn[2].nSelect = 1;
// 	}
// 	else
// 	{
// 		m_pStatePara->m_binIn[2].nSelect = 0;
// 	}
// 
// 	if (m_pBin_D->checkState() == Qt::Checked)
// 	{
// 		m_pStatePara->m_binIn[3].nSelect = 1;
// 	}
// 	else
// 	{
// 		m_pStatePara->m_binIn[3].nSelect = 0;
// 	}

	if (m_pBin_E->checkState() == Qt::Checked)
	{
		m_pStatePara->m_binIn[4].nSelect = 1;
	}
	else
	{
		m_pStatePara->m_binIn[4].nSelect = 0;
	}

	if (m_pBin_F->checkState() == Qt::Checked)
	{
		m_pStatePara->m_binIn[5].nSelect = 1;
	}
	else
	{
		m_pStatePara->m_binIn[5].nSelect = 0;
	}

	if (m_pBin_G->checkState() == Qt::Checked)
	{
		m_pStatePara->m_binIn[6].nSelect = 1;
	}
	else
	{
		m_pStatePara->m_binIn[6].nSelect = 0;
	}

	if (m_pBin_H->checkState() == Qt::Checked)
	{
		m_pStatePara->m_binIn[7].nSelect = 1;
	}
	else
	{
		m_pStatePara->m_binIn[7].nSelect = 0;
	}

	if (m_pBin_I->checkState() == Qt::Checked)
	{
		m_pStatePara->m_binIn[8].nSelect = 1;
	}
	else
	{
		m_pStatePara->m_binIn[8].nSelect = 0;
	}

	if (m_pBin_J->checkState() == Qt::Checked)
	{
		m_pStatePara->m_binIn[9].nSelect = 1;
	}
	else
	{
		m_pStatePara->m_binIn[9].nSelect = 0;
	}


	if (m_pLogicAnd->isChecked())
	{
	    m_pStatePara->m_nBinLogic = 1;	
	}

	if (m_pLogicOr->isChecked())
	{
	    m_pStatePara->m_nBinLogic = 0;
	}
		

	if(m_pBout_5->checkState()==Qt::Checked)
	{
		m_pStatePara->m_binOut[4].nState = 1;
	}
	else
	{
		m_pStatePara->m_binOut[4].nState = 0;
	}

	if(m_pBout_6->checkState()==Qt::Checked)
	{
		m_pStatePara->m_binOut[5].nState = 1;
	}
	else
	{
		m_pStatePara->m_binOut[5].nState = 0;
	}

	if(m_pBout_7->checkState()==Qt::Checked)
	{
		m_pStatePara->m_binOut[6].nState = 1;
	}
	else
	{
		m_pStatePara->m_binOut[6].nState = 0;
	}

	if(m_pBout_8->checkState()==Qt::Checked)
	{
		m_pStatePara->m_binOut[7].nState = 1;
	}
	else
	{
		m_pStatePara->m_binOut[7].nState = 0;
	}

	if(m_pBout_9->checkState()==Qt::Checked)
	{
		m_pStatePara->m_binOut[8].nState = 1;
	}
	else
	{
		m_pStatePara->m_binOut[8].nState = 0;
	}
	if(m_pBout_10->checkState()==Qt::Checked)
	{
		m_pStatePara->m_binOut[9].nState = 1;
	}
	else
	{
		m_pStatePara->m_binOut[9].nState = 0;
	}
	
	//2024-8-10 wuxinyi 点击确认触发accept
	//close();
	this->accept();
}

void QStateBinarySetDlg::slot_CancelClicked()
{
	ExitHideKeyboardWidget();
	close();
}


// void QStateBinarySetDlg::slot_lne_TrigerHoldTimeChangedKeyBoard()
// {
// 	if (m_pStatePara == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (m_pTrigerHoldTimeEdit->text().isEmpty())
// 	{
// 		m_pTrigerHoldTimeEdit->setText("0.000");
// 	}
// 
// 	QString str = m_pTrigerHoldTimeEdit->text();
// 	if (str.right(1).contains("."))
// 	{
// 		str.append("000");
// 	}
// 
// 	float fv= str.toFloat();
// 	fv = setLimit(0,999.999,fv);
// 
// 	m_pTrigerHoldTimeEdit->setText(QString::number(fv,'f',3));
// 
// 	if (fv != m_pStatePara->m_fTimeAfterTrigger)
// 	{
// 		m_pStatePara->m_fTimeAfterTrigger = fv;
// 		//*m_pbTmtParaChanged = TRUE;
// 	}
// }

void QStateBinarySetDlg::slot_lne_OutPutHoldTimeChangedKeyBoard()
{
	if (m_pOutputHoldTimeEdit->text().isEmpty())
	{
		m_pOutputHoldTimeEdit->setText("0.000");
	}

	QString str = m_pOutputHoldTimeEdit->text();
	
	if (str.right(1).contains("."))
	{
		str.append("000");
	}
	float fv = str.toFloat();
	fv = setLimit(0,999.999,fv);

	m_pOutputHoldTimeEdit->setText(QString::number(fv,'f',3));

	if (m_pStatePara != NULL)
	{
		m_pStatePara->m_fOutputHoldTime = fv;
		//*m_pbTmtParaChanged = TRUE;
	}
}

// void QStateBinarySetDlg::slot_lne_TrigerHoldTimeChanged()
// {
// 	if (m_pStatePara == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (m_pTrigerHoldTimeEdit->text().isEmpty())
// 	{
// 		m_pTrigerHoldTimeEdit->setText("0.000");
// 	}
// 
// 	QString str = m_pTrigerHoldTimeEdit->text();
// 	GetWidgetBoard_DigitData(4,str,m_pTrigerHoldTimeEdit,this);
// }


void QStateBinarySetDlg::slot_lne_OutPutHoldTimeChanged()
{
	if (m_pOutputHoldTimeEdit->text().isEmpty())
	{
		m_pOutputHoldTimeEdit->setText("0.000");
	}

	QString str = m_pOutputHoldTimeEdit->text();
	GetWidgetBoard_DigitData(4,str,m_pOutputHoldTimeEdit,this);
}

void QStateBinarySetDlg::slot_chb_OutPutHoldTimeStateChanged(int )
{
	if (m_pChk_HoldTime->isChecked())
	{
		m_pOutputHoldTimeEdit->setDisabled(false);
	}
	else
	{
		m_pOutputHoldTimeEdit->setDisabled(true);
		if (m_pStatePara != NULL)
		{
			m_pStatePara->m_fOutputHoldTime = 0;
			m_pOutputHoldTimeEdit->setText("0");
			//*m_pbTmtParaChanged = TRUE;
		}
	}
}
