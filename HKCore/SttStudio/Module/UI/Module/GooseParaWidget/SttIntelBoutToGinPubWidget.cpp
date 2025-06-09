#include "SttIntelBoutToGinPubWidget.h"
#include <QDebug>
#include <QSpacerItem>

#include "../SttUIDefine.h"
#include "../../Module/SttTestSysGlobalPara.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTestCntrFrameBase.h"
#include "../../Controls/SttCheckBox.h"
#include "SttIntelBoutToGinParaWidget.h"
#pragma execution_character_set("utf-8")
QSttIntelBoutToGinPubWidget::QSttIntelBoutToGinPubWidget(QSttIntelBoutToGinParaWidget *pParaWidget,QWidget *parent)
: QWidget(parent)
{
	m_pSttIntelBoutToGinGrid = NULL;
	m_pCfgGinData = NULL;
	initUI();
	SetGoosePubFont();
	connect(chb_cbBinOut1, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_BinOut1StateChanged(int)));
	connect(chb_cbBinOut2, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_BinOut2StateChanged(int)));
}

QSttIntelBoutToGinPubWidget::~QSttIntelBoutToGinPubWidget()
{

}
void QSttIntelBoutToGinPubWidget::SetGoosePubFont()
{
	label_IEDName->setFont(*g_pSttGlobalFont);
	lne_IEDName->setFont(*g_pSttGlobalFont);
	label_APPID->setFont(*g_pSttGlobalFont);
	lne_APPID->setFont(*g_pSttGlobalFont);
	chb_cbBinOut1->setFont(*g_pSttGlobalFont);
	chb_cbBinOut2->setFont(*g_pSttGlobalFont);
}
void QSttIntelBoutToGinPubWidget::initUI()
{
	QGroupBox *groupBox,*groupBox_2;
	QGridLayout *gridLayout,*gridLayout_2,*gridLayout_3;
	QHBoxLayout *horizontalLayout,*horizontalLayout_2;
	QSpacerItem *horizontalSpacer;
	
	setObjectName(QString::fromUtf8("SttIntelBoutToGinPubWidget"));
	resize(295, 362);
		
	/*QFont font;
	font.setPointSize(10);
	setFont(font);*/

	gridLayout_2 = new QGridLayout(this);
	gridLayout_2->setSpacing(2);
	gridLayout_2->setContentsMargins(11, 11, 11, 11);
	gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
	gridLayout_2->setContentsMargins(-1, 2, -1, 2);

	m_pSttIntelBoutToGinGrid = new CSttIntelBoutToGinGrid(this);	
	m_pSttIntelBoutToGinGrid->setFont(*g_pSttGlobalFont);
	m_pSttIntelBoutToGinGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pSttIntelBoutToGinGrid->InitGrid();

	gridLayout_2->addWidget(m_pSttIntelBoutToGinGrid, 2, 0, 1, 1);
	//m_pIecCfgGooseGinChsGrid->setDisabled(m_pParent->m_bGooseFlag);//20211006 sf 开始之后表格置灰

	groupBox = new QGroupBox(this);
	groupBox->setObjectName(QString::fromUtf8("groupBox"));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
	groupBox->setSizePolicy(sizePolicy);
	//groupBox->setFont(font);

	gridLayout = new QGridLayout(groupBox);
	gridLayout->setSpacing(6);
	gridLayout->setContentsMargins(11, 11, 11, 11);
	gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
	gridLayout->setHorizontalSpacing(2);
	gridLayout->setVerticalSpacing(1);
	gridLayout->setContentsMargins(4, 2, 4, 2);

	label_IEDName = new QLabel(groupBox);
	label_IEDName->setObjectName(QString::fromUtf8("label_IEDName"));
	label_IEDName->setText(tr("IED名称"));
	gridLayout->addWidget(label_IEDName, 0, 0, 1, 1);

	lne_IEDName = new QLineEdit(groupBox);
	lne_IEDName->setObjectName(QString::fromUtf8("lne_IEDName"));
	lne_IEDName->setEnabled(false);
	gridLayout->addWidget(lne_IEDName, 0, 1, 1, 1);

	label_APPID = new QLabel(groupBox);
	label_APPID->setObjectName(QString::fromUtf8("label_APPID"));
	label_APPID->setText(tr("应用标识(APPID)    0x"));
	gridLayout->addWidget(label_APPID, 0, 2, 1, 1);

	lne_APPID = new QLineEdit(groupBox);
	lne_APPID->setObjectName(QString::fromUtf8("lne_APPID"));
	lne_APPID->setEnabled(false);
	lne_APPID->setAlignment(Qt::AlignRight);
	gridLayout->addWidget(lne_APPID, 0, 3, 1, 1);

	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing(6);
	horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
	horizontalSpacer = new QSpacerItem(102, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	horizontalLayout->addItem(horizontalSpacer);

	groupBox_2 = new QGroupBox("快速开出");
	groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
	sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
	groupBox_2->setFont(*g_pSttGlobalFont);
	groupBox_2->setSizePolicy(sizePolicy);
	groupBox_2->setGeometry(QRect(300, 10, 400, 130));
	//groupBox_2->setFont(font);

	gridLayout_3 = new QGridLayout(groupBox_2);
	gridLayout_3->setSpacing(6);
	gridLayout_3->setContentsMargins(11, 11, 11, 11);
	gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
	gridLayout_3->setHorizontalSpacing(2);
	gridLayout_3->setVerticalSpacing(1);
	gridLayout_3->setContentsMargins(4, 2, 4, 2);

	horizontalLayout_2 = new QHBoxLayout();
	horizontalLayout_2->setSpacing(6);
	horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout"));

	chb_cbBinOut1 = new QSttCheckBox(groupBox_2);
	chb_cbBinOut1->setObjectName(QString::fromUtf8("chb_cbBinOut5"));
	chb_cbBinOut1->setText(tr("开出1"));
	horizontalLayout_2->addWidget(chb_cbBinOut1);
	//chb_cbBinOut1->setDisabled(m_pParent->m_bGooseFlag);

	chb_cbBinOut2 = new QSttCheckBox(groupBox_2);
	chb_cbBinOut2->setObjectName(QString::fromUtf8("chb_cbBinOut6"));
	chb_cbBinOut2->setText(tr("开出2"));
	horizontalLayout_2->addWidget(chb_cbBinOut2);
	//chb_cbBinOut2->setDisabled(m_pParent->m_bGooseFlag);

	gridLayout_3->addLayout(horizontalLayout_2, 0, 0, 1, 1);
	gridLayout->addLayout(horizontalLayout, 0, 4, 1, 1);
	gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);
	gridLayout->addWidget(groupBox_2, 0, 4, 1, 1);
}

void QSttIntelBoutToGinPubWidget::initData( CIecCfgGinData *pCfgGinData, bool bInitEditable)
{
	m_pCfgGinData = pCfgGinData;
	CString str = m_pCfgGinData->m_strIedRefDesc;
	
	lne_IEDName->setText(str);
	lne_APPID->setText(QString("%1").arg(m_pCfgGinData->m_dwAppID,4,16,QChar('0')));
	ASSERT(pCfgGinData->m_pCfgChs);
	
	if (bInitEditable)
	{
		m_pSttIntelBoutToGinGrid->SetRunState(STT_UI_RUN_STATE_Stoped);
	}
	else
	{
		m_pSttIntelBoutToGinGrid->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);
	}
	m_pSttIntelBoutToGinGrid->ShowDatas(pCfgGinData->m_pCfgChs);
	connect(m_pSttIntelBoutToGinGrid,SIGNAL(sig_GoutValue_Changed()),this,SLOT(slot_dataChanged()));
	connect(m_pSttIntelBoutToGinGrid,SIGNAL(sig_GinRowIndex(int,float)),this,SLOT(slot_GinRowIndex(int,float)));
}

void QSttIntelBoutToGinPubWidget::slot_dataChanged()
{
	Q_EMIT sig_GooseDataChanged();
}

void QSttIntelBoutToGinPubWidget::slot_GinRowIndex(int nRowIndex,float fActTime)
{
	emit sig_GinRowIndex(nRowIndex,fActTime);
}

void QSttIntelBoutToGinPubWidget::SetRunState(int nRunState)
{	
	ASSERT(m_pSttIntelBoutToGinGrid);
	m_pSttIntelBoutToGinGrid->SetRunState(nRunState);	
}

void QSttIntelBoutToGinPubWidget::slot_chb_BinOut1StateChanged( int nStateValue)
{
	ASSERT(m_pSttIntelBoutToGinGrid);
	if (nStateValue==Qt::Checked)
	{
		emit sig_setBinOut(0,TRUE);
		m_pSttIntelBoutToGinGrid->UpdateState(nStateValue);
	}
	else
	{
		emit sig_setBinOut(0,FALSE);
	}
}
void QSttIntelBoutToGinPubWidget::slot_chb_BinOut2StateChanged( int nStateValue)
{
	ASSERT(m_pSttIntelBoutToGinGrid);
	if (nStateValue==Qt::Checked)
	{
		emit sig_setBinOut(1,TRUE);
		m_pSttIntelBoutToGinGrid->UpdateState(nStateValue);
	}
	else
	{
		emit sig_setBinOut(1,FALSE);
	}
}
void QSttIntelBoutToGinPubWidget::GridCellResultVlaues(float fResultTimeVlaue,char strCharacterIndex)
{
	m_pSttIntelBoutToGinGrid->GridCellResultVlaues(fResultTimeVlaue,strCharacterIndex);
}

void QSttIntelBoutToGinPubWidget::startInit()
{
	m_pSttIntelBoutToGinGrid->startInit();
}