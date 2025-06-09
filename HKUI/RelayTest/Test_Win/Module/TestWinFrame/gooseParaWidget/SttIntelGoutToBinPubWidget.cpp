#include "SttIntelGoutToBinPubWidget.h"
#include <QDebug>
#include <QSpacerItem>
#include "../../Define.h"
#include "../../SttXTestMngrBaseApp.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

#pragma execution_character_set("utf-8")
QSttIntelGoutToBinPubWidget::QSttIntelGoutToBinPubWidget(QWidget *parent)
	: QWidget(parent)
{

	m_pSttIntelGoutToBinGrid = NULL;
	initUI();
	m_pCfgGoutData = NULL;

	connect(chb_Repair, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_RepairStateChanged(int)));
	connect(pbn_Revert, SIGNAL(clicked ()), this, SLOT(slot_pbn_RevertClicked()));
	
}

QSttIntelGoutToBinPubWidget::~QSttIntelGoutToBinPubWidget()
{

}

void QSttIntelGoutToBinPubWidget::initUI()
{
	QGroupBox *groupBox;
	QGridLayout *gridLayout,*gridLayout_2;
	QHBoxLayout *horizontalLayout;
	QSpacerItem *horizontalSpacer;
	
	setObjectName(QString::fromUtf8("SttIntelGoutToBinPubWidget"));
	resize(295, 362);
		
	QFont font;
	font.setPointSize(10);
	setFont(font);

	gridLayout_2 = new QGridLayout(this);
	gridLayout_2->setSpacing(2);
	gridLayout_2->setContentsMargins(11, 11, 11, 11);
	gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
	gridLayout_2->setContentsMargins(-1, 2, -1, 2);

	m_pSttIntelGoutToBinGrid = new CSttIntelGoutToBinGrid(this);	
	m_pSttIntelGoutToBinGrid->InitGrid();

	gridLayout_2->addWidget(m_pSttIntelGoutToBinGrid, 2, 0, 1, 1);
	m_pSttIntelGoutToBinGrid->setDisabled(g_theSttXTestMngrBaseApp->m_bGooseFlag);//20211006 sf 开始之后表格置灰

	groupBox = new QGroupBox(this);
	groupBox->setObjectName(QString::fromUtf8("groupBox"));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
	groupBox->setSizePolicy(sizePolicy);
	QFont font1;
	font1.setPointSize(10);
	groupBox->setFont(font1);

	gridLayout = new QGridLayout(groupBox);
	gridLayout->setSpacing(6);
	gridLayout->setContentsMargins(11, 11, 11, 11);
	gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
	gridLayout->setHorizontalSpacing(2);
	gridLayout->setVerticalSpacing(1);
	gridLayout->setContentsMargins(4, 2, 4, 2);

	label_IEDName = new QLabel(groupBox);
	label_IEDName->setObjectName(QString::fromUtf8("label_IEDName"));
	label_IEDName->setText(/*tr("IED名称")*/g_sLangTxt_Native_IEDName);
	gridLayout->addWidget(label_IEDName, 0, 0, 1, 1);

	lne_IEDName = new QLineEdit(groupBox);
	lne_IEDName->setObjectName(QString::fromUtf8("lne_IEDName"));
	lne_IEDName->setEnabled(false);
	gridLayout->addWidget(lne_IEDName, 0, 1, 1, 1);

	label_APPID = new QLabel(groupBox);
	label_APPID->setObjectName(QString::fromUtf8("label_APPID"));
	label_APPID->setText(/*tr("应用标识(APPID)    0x")*/g_sLangTxt_Native_APPID);
	gridLayout->addWidget(label_APPID, 0, 2, 1, 1);

	lne_APPID = new QLineEdit(groupBox);
	lne_APPID->setObjectName(QString::fromUtf8("lne_APPID"));
	lne_APPID->setEnabled(false);
	gridLayout->addWidget(lne_APPID, 0, 3, 1, 1);

	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing(6);
	horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
	horizontalSpacer = new QSpacerItem(102, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	horizontalLayout->addItem(horizontalSpacer);

	chb_Repair = new QCheckBox(groupBox);
	chb_Repair->setObjectName(QString::fromUtf8("chb_Repair"));
	chb_Repair->setText(/*tr("置检修")*/g_sLangTxt_Native_Repair);
	horizontalLayout->addWidget(chb_Repair);
	chb_Repair->setDisabled(g_theSttXTestMngrBaseApp->m_bGooseFlag);//20210929 sf 开始之后置检修置灰
	
	lne_APPID->setAlignment(Qt::AlignRight);

	pbn_Revert = new  QPushButton (groupBox);
	pbn_Revert->setObjectName(QString::fromUtf8("pbn_Revert"));
	pbn_Revert->setText(/*(tr("复归")*/g_sLangTxt_Native_Revert);
	horizontalLayout->addWidget(pbn_Revert);
	pbn_Revert->setDisabled(g_theSttXTestMngrBaseApp->m_bGooseFlag);//20230914 gyp 开始之后复归置灰
	
	gridLayout->addLayout(horizontalLayout, 0, 4, 1, 1);
	gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);
}

void QSttIntelGoutToBinPubWidget::initData( CIecCfgGoutData *pCfgGoutData, bool bInitEditable)
{
	m_pCfgGoutData = pCfgGoutData;
	CString str = m_pCfgGoutData->m_strIedRefDesc;
	
	lne_IEDName->setText(str);
	lne_APPID->setText(QString("%1").arg(m_pCfgGoutData->m_dwAppID,4,16,QChar('0')));
	ASSERT(pCfgGoutData->m_pCfgChs);
	
	if (bInitEditable)
	{
		m_pSttIntelGoutToBinGrid->SetRunState(STT_UI_RUN_STATE_Stoped);	
	}
	else
	{
		m_pSttIntelGoutToBinGrid->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);
	}

	chb_Repair->setChecked(m_pCfgGoutData->m_bTest);//zhouhj20210917 初始化置检修状态
	
	//chb_Invert->setChecked(FALSE);// 初始化取反状态
	m_pSttIntelGoutToBinGrid->ShowDatas(pCfgGoutData->m_pCfgChs);
	connect(m_pSttIntelGoutToBinGrid,SIGNAL(sig_GoutValue_Changed()),this,SLOT(slot_dataChanged()));
	connect(m_pSttIntelGoutToBinGrid,SIGNAL(sig_GoutRowIndex(int)),this,SLOT(slot_GoutRowIndex(int)));
}

void QSttIntelGoutToBinPubWidget::slot_chb_RepairStateChanged( int )
{
	if (m_pCfgGoutData == NULL)
	{
		return;
	}

	if (chb_Repair->isChecked())
	{
		m_pCfgGoutData->m_bTest = 1;
	}
	else
	{
		m_pCfgGoutData->m_bTest = 0;
	}
	emit sig_GooseDataChanged();
}

void QSttIntelGoutToBinPubWidget::slot_pbn_RevertClicked()
{
	emit sig_RevertData();
	m_pSttIntelGoutToBinGrid->UpdateDatas_Revert();	
}

void QSttIntelGoutToBinPubWidget::slot_dataChanged()
{
	Q_EMIT sig_GooseDataChanged();
}
void QSttIntelGoutToBinPubWidget::slot_GoutRowIndex(int nRowIndex)
{
	emit sig_GoutRowIndex(nRowIndex);
}

void QSttIntelGoutToBinPubWidget::SetRunState(int nRunState)
{
	ASSERT(m_pSttIntelGoutToBinGrid);
	m_pSttIntelGoutToBinGrid->SetRunState(nRunState);
}

void QSttIntelGoutToBinPubWidget::EnableInverseCol(BOOL bEnable)
{
	m_pSttIntelGoutToBinGrid->EnableInverseCol(bEnable);
}

void QSttIntelGoutToBinPubWidget::GridCellResultVlaues(float fResultTimeVlaue,char strCharacterIndex)
{
	m_pSttIntelGoutToBinGrid->GridCellResultVlaues(fResultTimeVlaue,strCharacterIndex);
}

void QSttIntelGoutToBinPubWidget::setGooseResultVlaues()
{
	m_pSttIntelGoutToBinGrid->setGooseResultVlaues();
}

void QSttIntelGoutToBinPubWidget::startInit()
{
	m_pSttIntelGoutToBinGrid->startInit();
}
