#include "CommonValueDialogState.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../SttTestCntrFrameBase.h"

CommonValueDialogState::CommonValueDialogState(tmt_StateParas* pSateParas,QWidget *parent)
: QDialog(parent), ui(new Ui::CommonValueDialogState)
{
	ui->setupUi(this);
	ASSERT(pSateParas != NULL);
	m_pSateParas = pSateParas;
	m_nIsOK = 0;

	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Dialog);

	initUI();
	initBaseData();
	initConnections();

	initPara();
	SetCommonValueDialogStateFont();
}

CommonValueDialogState::~CommonValueDialogState()
{

}
void CommonValueDialogState::SetCommonValueDialogStateFont()
{	
	m_pCmb_JudgeCondition->setFont(*g_pSttGlobalFont);
	m_pCmb_DCOFFSET->setFont(*g_pSttGlobalFont);
}

void CommonValueDialogState::initUI()
{
	QGridLayout *gridLayout = NULL;
	QHBoxLayout *horizontalLayout = NULL;

#ifdef _PSX_QT_WINDOWS_
	resize(350, 250);
#else
	resize(233, 189);
#endif
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
	setSizePolicy(sizePolicy);

	//2022-10-14
// 	QFont font;
// 	font.setPointSize(20);
// 	setFont(font);
	setFont(*g_pSttGlobalFont);

	gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(6);

#ifdef _PSX_QT_WINDOWS_
	gridLayout->setContentsMargins(15, 15, 15, 15);
#else
	gridLayout->setContentsMargins(11, 11, 11, 11);
#endif // _PSX_QT_WINDOWS_
		
	m_pJudgeConditionLabel = new QLabel(tr("开入翻转参考状态:"),this);
	xlang_SetLangStrToWidget(m_pJudgeConditionLabel, "State_JudgeCondition", XLang_Ctrls_QLabel);
	gridLayout->addWidget(m_pJudgeConditionLabel, 0, 0, 1, 1);

	m_pCmb_JudgeCondition = new QScrollComboBox(this);
	gridLayout->addWidget(m_pCmb_JudgeCondition, 0, 1, 1, 1);

	m_pDCOFFSETLabel = new QLabel(tr("叠加衰减直流分量:"),this);
	xlang_SetLangStrToWidget(m_pDCOFFSETLabel, "State_DCOffSet", XLang_Ctrls_QLabel);
	gridLayout->addWidget(m_pDCOFFSETLabel, 1, 0, 1, 1);

	m_pCmb_DCOFFSET = new QScrollComboBox(this);
	QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(m_pCmb_DCOFFSET->sizePolicy().hasHeightForWidth());
	m_pCmb_DCOFFSET->setSizePolicy(sizePolicy1);
	gridLayout->addWidget(m_pCmb_DCOFFSET, 1, 1, 1, 1);

	m_pTouLabel = new QLabel(tr("衰减时间常数:"),this);
	xlang_SetLangStrToWidget(m_pTouLabel, "State_Tou", XLang_Ctrls_QLabel);
	gridLayout->addWidget(m_pTouLabel, 2, 0, 1, 1);

	m_pTouEdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pTouEdit, 2, 1, 1, 1);

	m_pRepeatTimeLabel = new QLabel(tr("循环次数:"),this);
	xlang_SetLangStrToWidget(m_pRepeatTimeLabel, "State_RepeatTimes", XLang_Ctrls_QLabel);
	gridLayout->addWidget(m_pRepeatTimeLabel, 3, 0, 1, 1);

	m_pRepeatTimeEdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pRepeatTimeEdit, 3, 1, 1, 1);

#ifdef _PSX_QT_WINDOWS_
	gridLayout->setVerticalSpacing(15);
	gridLayout->setHorizontalSpacing(20);
#else	
	m_pVerticalSpacer = new QSpacerItem(178, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);
	gridLayout->addItem(m_pVerticalSpacer, 5, 0, 1, 2);

	m_pLine = new QFrame(this);
	m_pLine->setFrameShape(QFrame::HLine);
	m_pLine->setFrameShadow(QFrame::Sunken);
	gridLayout->addWidget(m_pLine, 4, 0, 1, 2);
#endif


	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing(6);
	
	m_pbn_Ok = new QPushButton(tr("确定"),this);
	m_pbn_Ok->setFocusPolicy(Qt::NoFocus);

	m_pbn_Cancel = new QPushButton(tr("取消"),this);
	m_pbn_Cancel->setFocusPolicy(Qt::NoFocus);

	xlang_SetLangStrToWidget(m_pbn_Ok, "sOK", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pbn_Cancel, "sCancel", XLang_Ctrls_QPushButton);


#ifdef _PSX_QT_WINDOWS_
	gridLayout->addWidget(m_pbn_Ok, 5, 0, 1, 1);
	gridLayout->addWidget(m_pbn_Cancel, 5, 1, 1, 1);

	gridLayout->setColumnStretch(0, 1); // 第一行伸缩因子为1
	gridLayout->setColumnStretch(1, 1); // 第二行伸缩因子为1
#else	
	
	horizontalLayout->addWidget(m_pbn_Ok);
	horizontalLayout->addWidget(m_pbn_Cancel);
	gridLayout->addLayout(horizontalLayout, 6, 0, 1, 2);
#endif // _PSX_QT_WINDOWS_

	this->setLayout(gridLayout);

    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"sGeneralParameter");
	setWindowTitle(strTitle);

	Qt::WindowFlags flags= this->windowFlags();
	setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);

}

void CommonValueDialogState::initConnections()
{
	connect(m_pbn_Ok, SIGNAL(clicked()), this, SLOT(slot_OkClicked()));
	connect(m_pbn_Cancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(m_pCmb_DCOFFSET, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_cmb_DCOFFSETChanged(int)));
	connect(m_pTouEdit,SIGNAL(editingFinished()),this,SLOT(slot_lne_TouKeyBoard()));
	connect(m_pRepeatTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_lne_RepeatTimeKeyBoard()));
	connect(this, SIGNAL(sig_DcCoffsetStateChanged()), g_pStateTest, SLOT(slot_DcCoffsetStateChanged()));

#ifdef _PSX_QT_LINUX_
	connect(m_pTouEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TouChanged()));
	connect(m_pRepeatTimeEdit,SIGNAL(clicked()),this,SLOT(slot_lne_RepeatTimeChanged()));
#endif
}

void CommonValueDialogState::initBaseData()
{
	m_listJudgeConditions.clear();

    CString strItem1,strItem2,strItem3;
//	m_listJudgeConditions<<tr("上一个状态")<<tr("第一个状态");

	xlang_GetLangStrByFile(strItem1, "State_LastState");
	xlang_GetLangStrByFile(strItem2, "State_FirstState");
	m_listJudgeConditions << strItem1 << strItem2;

	m_pCmb_JudgeCondition->addItems(m_listJudgeConditions);

	m_listDcOffSets.clear();
//	m_listDcOffSets<<tr("否")<<tr("是");

	xlang_GetLangStrByFile(strItem1, "State_No");
	xlang_GetLangStrByFile(strItem2, "State_Yes");
	xlang_GetLangStrByFile(strItem3, "State_StackByState");
	m_listDcOffSets << strItem1 << strItem2 << strItem3;
	m_pCmb_DCOFFSET->addItems(m_listDcOffSets);

	initMaxPositiveEdit(m_pTouEdit);
	initMaxPositiveEdit(m_pRepeatTimeEdit);
}

void CommonValueDialogState::initPara()
{
	m_pCmb_JudgeCondition->setCurrentIndex(m_pSateParas->m_nBinTripRef);
	m_pCmb_DCOFFSET->setCurrentIndex(m_pSateParas->m_nPlusDC);
	slot_cmb_DCOFFSETChanged(m_pSateParas->m_nPlusDC);

	m_pTouEdit->setText(QString::number(m_pSateParas->m_fTao,'f',3));
	m_pRepeatTimeEdit->setText(QString("%1").arg(m_pSateParas->m_nRepeatNumbers));
}

void CommonValueDialogState::slot_OkClicked()
{
	ExitHideKeyboardWidget();
	m_pSateParas->m_nBinTripRef = m_pCmb_JudgeCondition->currentIndex();
	//m_pSateParas->m_bPlusDC = m_pCmb_DCOFFSET->currentIndex();
	m_pSateParas->m_fTao = m_pTouEdit->text().toFloat();
	int nIndex = m_pCmb_DCOFFSET->currentIndex();
	if (m_pSateParas->m_nPlusDC != nIndex)
	{
		m_pSateParas->m_nPlusDC = nIndex;
		emit sig_DcCoffsetStateChanged();
	}

	int temp = m_pRepeatTimeEdit->text().toInt();

	m_pSateParas->m_nRepeatNumbers = temp; //循环次数
	
	close();
	m_nIsOK = 1;
}

void CommonValueDialogState::slot_CancelClicked()
{
	ExitHideKeyboardWidget();
	close();
	m_nIsOK = 2;
}

void CommonValueDialogState::slot_cmb_DCOFFSETChanged(int index)
{
	if(m_pCmb_DCOFFSET->IsScrolling())
	{
		return;
	}

	if(index == 0) //选择否
	{
		m_pTouEdit->setDisabled(true);
		m_pTouLabel->setDisabled(true);
	}
	else
	{
		if (index == 2)
		{
			m_pTouEdit->setDisabled(true);
			m_pTouLabel->setDisabled(true);
	}
	else
	{
		m_pTouEdit->setDisabled(false);
			m_pTouLabel->setDisabled(false);
		}
	}
}

void CommonValueDialogState::slot_lne_TouChanged()
{
	QString strValue = m_pTouEdit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pTouEdit,g_theTestCntrFrame);

// 	if (strValue.right(1).contains("."))
// 	{
// 		strValue.append(000);
// 	}
// 
// 	float tou= strValue.toFloat();
// 	if (tou>0.1)
// 	{
// 		tou = 0.1;
// 	}
// 	else if (tou<0)
// 	{
// 		tou = 0;
// 	}
// 
// 	m_pTouEdit->setText(QString::number(tou,'f',3));
}

void CommonValueDialogState::slot_lne_TouKeyBoard()
{
 	QString strValue = m_pTouEdit->text();
// 	GetWidgetBoard_DigitData(4,strValue,g_theTestCntrFrame);

	if (strValue.right(1).contains("."))
	{
		strValue.append(000);
	}

	float tou= strValue.toFloat();
	if (tou>0.1)
	{
		tou = 0.1;
	}
	else if (tou<0)
	{
		tou = 0;
	}

	m_pTouEdit->setText(QString::number(tou,'f',3));
}
void CommonValueDialogState::slot_lne_RepeatTimeChanged()
{
	QString strValue = m_pRepeatTimeEdit->text();

	GetWidgetBoard_DigitData(4,strValue,m_pRepeatTimeEdit,g_theTestCntrFrame);

// 	float fv = strValue.toFloat();
// 	fv = setLimit(0,100000,fv);
// 	
// 	m_pRepeatTimeEdit->setText(QString::number(fv,'f',0));
}

void CommonValueDialogState::slot_lne_RepeatTimeKeyBoard()
{
	QString strValue = m_pRepeatTimeEdit->text();

// 	GetWidgetBoard_DigitData(4,strValue,g_theTestCntrFrame);

	float fv = strValue.toFloat();
	fv = setLimit(0,100000,fv);

	m_pRepeatTimeEdit->setText(QString::number(fv,'f',0));
}

void CommonValueDialogState::closeEvent( QCloseEvent *event )
{
	m_nIsOK = 2;
}


