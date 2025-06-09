#include "CommonValueDialogState.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../SttTestCntrFrameBase.h"
#include "../../Module/SttTest/Common/PrimFreq/tmt_prim_freq_state_test.h"

CommonValueDialogState::CommonValueDialogState(tmt_StateParas* pSateParas,QWidget *parent, bool bFrimFreqModel)
: QDialog(parent), ui(new Ui::CommonValueDialogState)
{
	ui->setupUi(this);
	ASSERT(pSateParas != NULL);
	m_pSateParas = pSateParas;
	m_nIsOK = 0;

	m_pCmb_DCOFFSET = NULL;
	m_pCmb_JudgeCondition = NULL;
	m_pDCOFFSETLabel = NULL;
	m_pJudgeConditionLabel = NULL;
	m_pRepeatTimeLabel = NULL;
	m_pTouLabel = NULL;
	m_pRepeatTimeEdit = NULL;
	m_pTouEdit = NULL;
	m_pVerticalSpacer = NULL;
	m_pLine = NULL;
	m_pbn_Ok = NULL;
	m_pbn_Cancel = NULL;

	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Dialog);

	initUI(bFrimFreqModel);
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
	if(m_pCmb_JudgeCondition)
	m_pCmb_JudgeCondition->setFont(*g_pSttGlobalFont);

	if(m_pCmb_DCOFFSET)
	m_pCmb_DCOFFSET->setFont(*g_pSttGlobalFont);
}

void CommonValueDialogState::initUI(bool bFrimFreqModel)
{
	QGridLayout *gridLayout = NULL;
	QHBoxLayout *horizontalLayout = NULL;

	if(bFrimFreqModel)
	{
		resize(233, 140);
	}
	else
	{
	resize(233, 189);
	}
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
	gridLayout->setContentsMargins(11, 11, 11, 11);
		
	m_pJudgeConditionLabel = new QLabel(tr("���뷭ת�ο�״̬:"),this);
	xlang_SetLangStrToWidget(m_pJudgeConditionLabel, "State_JudgeCondition", XLang_Ctrls_QLabel);
	gridLayout->addWidget(m_pJudgeConditionLabel, 0, 0, 1, 1);

	m_pCmb_JudgeCondition = new QScrollComboBox(this);
	gridLayout->addWidget(m_pCmb_JudgeCondition, 0, 1, 1, 1);

	if(!bFrimFreqModel)
	{
	m_pDCOFFSETLabel = new QLabel(tr("����˥��ֱ������:"),this);
	xlang_SetLangStrToWidget(m_pDCOFFSETLabel, "State_DCOffSet", XLang_Ctrls_QLabel);
	gridLayout->addWidget(m_pDCOFFSETLabel, 1, 0, 1, 1);

	m_pCmb_DCOFFSET = new QScrollComboBox(this);
	QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(m_pCmb_DCOFFSET->sizePolicy().hasHeightForWidth());
	m_pCmb_DCOFFSET->setSizePolicy(sizePolicy1);
	gridLayout->addWidget(m_pCmb_DCOFFSET, 1, 1, 1, 1);

	m_pTouLabel = new QLabel(tr("˥��ʱ�䳣��:"),this);
	xlang_SetLangStrToWidget(m_pTouLabel, "State_Tou", XLang_Ctrls_QLabel);
	gridLayout->addWidget(m_pTouLabel, 2, 0, 1, 1);

	m_pTouEdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pTouEdit, 2, 1, 1, 1);
	}



	m_pRepeatTimeLabel = new QLabel(tr("ѭ������:"),this);
	xlang_SetLangStrToWidget(m_pRepeatTimeLabel, "State_RepeatTimes", XLang_Ctrls_QLabel);
	gridLayout->addWidget(m_pRepeatTimeLabel, 3, 0, 1, 1);

	m_pRepeatTimeEdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pRepeatTimeEdit, 3, 1, 1, 1);

	m_pVerticalSpacer = new QSpacerItem(178, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);
	gridLayout->addItem(m_pVerticalSpacer, 5, 0, 1, 2);

	m_pLine = new QFrame(this);
	m_pLine->setFrameShape(QFrame::HLine);
	m_pLine->setFrameShadow(QFrame::Sunken);
	gridLayout->addWidget(m_pLine, 4, 0, 1, 2);

	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing(6);
	
	m_pbn_Ok = new QPushButton(tr("ȷ��"),this);
	m_pbn_Ok->setFocusPolicy(Qt::NoFocus);

	m_pbn_Cancel = new QPushButton(tr("ȡ��"),this);
	m_pbn_Cancel->setFocusPolicy(Qt::NoFocus);

	xlang_SetLangStrToWidget(m_pbn_Ok, "sOK", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pbn_Cancel, "sCancel", XLang_Ctrls_QPushButton);

	horizontalLayout->addWidget(m_pbn_Ok);
	horizontalLayout->addWidget(m_pbn_Cancel);

	gridLayout->addLayout(horizontalLayout, 6, 0, 1, 2);

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
	if(m_pCmb_DCOFFSET)
	connect(m_pCmb_DCOFFSET, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_cmb_DCOFFSETChanged(int)));
	if(m_pTouEdit)
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
//	m_listJudgeConditions<<tr("��һ��״̬")<<tr("��һ��״̬");

	xlang_GetLangStrByFile(strItem1, "State_LastState");
	xlang_GetLangStrByFile(strItem2, "State_FirstState");
	m_listJudgeConditions << strItem1 << strItem2;

	m_pCmb_JudgeCondition->addItems(m_listJudgeConditions);

	m_listDcOffSets.clear();
//	m_listDcOffSets<<tr("��")<<tr("��");

	if(m_pCmb_DCOFFSET)
	{
	xlang_GetLangStrByFile(strItem1, "State_No");
	xlang_GetLangStrByFile(strItem2, "State_Yes");
	xlang_GetLangStrByFile(strItem3, "State_StackByState");
	m_listDcOffSets << strItem1 << strItem2 << strItem3;
	m_pCmb_DCOFFSET->addItems(m_listDcOffSets);

	}

	if(m_pTouEdit)
	initMaxPositiveEdit(m_pTouEdit);

	initMaxPositiveEdit(m_pRepeatTimeEdit);
}

void CommonValueDialogState::initPara()
{
	m_pCmb_JudgeCondition->setCurrentIndex(m_pSateParas->m_nBinTripRef);
	if(m_pCmb_DCOFFSET)
	m_pCmb_DCOFFSET->setCurrentIndex(m_pSateParas->m_nPlusDC);

	slot_cmb_DCOFFSETChanged(m_pSateParas->m_nPlusDC);

	if(m_pTouEdit)
	m_pTouEdit->setText(QString::number(m_pSateParas->m_fTao,'f',3));
	m_pRepeatTimeEdit->setText(QString("%1").arg(m_pSateParas->m_nRepeatNumbers));
}

void CommonValueDialogState::slot_OkClicked()
{
	ExitHideKeyboardWidget();
	m_pSateParas->m_nBinTripRef = m_pCmb_JudgeCondition->currentIndex();
	//m_pSateParas->m_bPlusDC = m_pCmb_DCOFFSET->currentIndex();
	if(m_pTouEdit)
	{
	m_pSateParas->m_fTao = m_pTouEdit->text().toFloat();
	}
	if(m_pCmb_DCOFFSET)
	{
	int nIndex = m_pCmb_DCOFFSET->currentIndex();
	if (m_pSateParas->m_nPlusDC != nIndex)
	{
		m_pSateParas->m_nPlusDC = nIndex;
		emit sig_DcCoffsetStateChanged();
	}
	}

	int temp = m_pRepeatTimeEdit->text().toInt();

	m_pSateParas->m_nRepeatNumbers = temp; //ѭ������
	
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
	if(m_pCmb_DCOFFSET == NULL)
	{
		return;
	}
	if(m_pCmb_DCOFFSET->IsScrolling())
	{
		return;
	}

	if(index == 0) //ѡ���
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
	if(m_pTouEdit == NULL)
	{
		return;
	}
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


