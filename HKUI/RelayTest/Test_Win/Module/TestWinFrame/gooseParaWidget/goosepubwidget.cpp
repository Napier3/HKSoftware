#include "GoosePubWidget.h"
#include <QDebug>
#include <QSpacerItem>
#include "../../Define.h"
#include "../../SttXTestMngrBaseApp.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

#pragma execution_character_set("utf-8")
GoosePubWidget::GoosePubWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pIecCfgGoutChsGrid = NULL;
	initUI();
	m_pCfgGoutData = NULL;

	connect(chb_Invert, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InvertStateChanged(int)));
	connect(chb_Repair, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_RepairStateChanged(int)));
}

GoosePubWidget::~GoosePubWidget()
{

}

void GoosePubWidget::initUI()
{
	QGroupBox *groupBox;
	QGridLayout *gridLayout,*gridLayout_2;
	QHBoxLayout *horizontalLayout;
	QSpacerItem *horizontalSpacer;
	
	setObjectName(QString::fromUtf8("GoosePubWidget"));
	resize(295, 362);
		
	QFont font;
	font.setPointSize(10);
	setFont(font);

	gridLayout_2 = new QGridLayout(this);
	gridLayout_2->setSpacing(2);
	gridLayout_2->setContentsMargins(11, 11, 11, 11);
	gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
	gridLayout_2->setContentsMargins(-1, 2, -1, 2);

	m_pIecCfgGoutChsGrid = new CIecCfgGoutChsGrid(this);
	m_pIecCfgGoutChsGrid->InitGrid();
// 	m_pGoosePubTable = new QGooseTable(this);
// 	m_pGoosePubTable->setObjectName(QString::fromUtf8("table"));
	gridLayout_2->addWidget(m_pIecCfgGoutChsGrid, 2, 0, 1, 1);
	m_pIecCfgGoutChsGrid->setDisabled(g_theSttXTestMngrBaseApp->m_bGooseFlag);//20211006 sf 开始之后表格置灰

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

	chb_Invert = new QCheckBox(groupBox);
	chb_Invert->setObjectName(QString::fromUtf8("chb_Invert"));
	chb_Invert->setText(/*tr("取反")*/g_sLangTxt_Native_Reverse);
	horizontalLayout->addWidget(chb_Invert);
	chb_Invert->setDisabled(g_theSttXTestMngrBaseApp->m_bGooseFlag);//20210929 sf 开始之后取反置灰

	chb_Repair = new QCheckBox(groupBox);
	chb_Repair->setObjectName(QString::fromUtf8("chb_Repair"));
	chb_Repair->setText(/*tr("置检修")*/g_sLangTxt_Native_Repair);
	horizontalLayout->addWidget(chb_Repair);
	chb_Repair->setDisabled(g_theSttXTestMngrBaseApp->m_bGooseFlag);//20210929 sf 开始之后置检修置灰

	gridLayout->addLayout(horizontalLayout, 0, 4, 1, 1);
	gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);
}

void GoosePubWidget::initData( CIecCfgGoutData *pCfgGoutData, bool bInitEditable)
{
	m_pCfgGoutData = pCfgGoutData;
	CString str = m_pCfgGoutData->m_strIedRefDesc;
	
	lne_IEDName->setText(str);
	lne_APPID->setText(QString("%1").arg(m_pCfgGoutData->m_dwAppID,4,16,QChar('0')));
	ASSERT(pCfgGoutData->m_pCfgChs);
	
	if (bInitEditable)
	{
		m_pIecCfgGoutChsGrid->SetRunState(STT_UI_RUN_STATE_Stoped);
	}
	else
	{
		m_pIecCfgGoutChsGrid->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);
	}

	chb_Repair->setChecked(m_pCfgGoutData->m_bTest);//zhouhj20210917 初始化置检修状态

	m_pIecCfgGoutChsGrid->ShowDatas(pCfgGoutData->m_pCfgChs);
// 	m_pGoosePubTable->setGooseData(pCfgGoutData);
 	connect(m_pIecCfgGoutChsGrid,SIGNAL(sig_GoutValue_Changed()),this,SLOT(slot_dataChanged()));
}

void GoosePubWidget::slot_chb_InvertStateChanged( int nStateValue)
{
	ASSERT(m_pIecCfgGoutChsGrid);
	disconnect(m_pIecCfgGoutChsGrid,SIGNAL(sig_GoutValue_Changed()),this,SLOT(slot_dataChanged()));
	m_pIecCfgGoutChsGrid->UpdateData_AllValues(nStateValue);
	connect(m_pIecCfgGoutChsGrid,SIGNAL(sig_GoutValue_Changed()),this,SLOT(slot_dataChanged()));
	emit sig_GooseDataChanged();
// 	m_bAll = true;
// 	
// 	for (int i=0;i<m_pGoosePubTable->rowCount();i++)
// 	{
// 		if(m_pGoosePubTable->item(i,4) != NULL){
// 			if (m_pGoosePubTable->item(i,4)->flags() != Qt::NoItemFlags )
// 			{
// 				if (m_pGoosePubTable->item(i,4)->checkState() == Qt::Unchecked)
// 				{
// 					m_pGoosePubTable->item(i,4)->setCheckState(Qt::Checked);
// 				}
// 				else
// 				{
// 					m_pGoosePubTable->item(i,4)->setCheckState(Qt::Unchecked);
// 				}
// 			}
// 		}
// 	}
// 	connect(m_pGoosePubTable,SIGNAL(sigdatachanged()),this,SLOT(slot_dataChanged()));
// 	
// 	m_bAll = false;
// 	emit sig_GooseDataChanged();
}

void GoosePubWidget::slot_chb_RepairStateChanged( int )
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

void GoosePubWidget::slot_dataChanged()
{
	Q_EMIT sig_GooseDataChanged();
}

void GoosePubWidget::SetRunState(int nRunState)
{
	ASSERT(m_pIecCfgGoutChsGrid);
	m_pIecCfgGoutChsGrid->SetRunState(nRunState);
}

void GoosePubWidget::EnableInverseCol(BOOL bEnable)
{
	m_pIecCfgGoutChsGrid->EnableInverseCol(bEnable);
}

// void GoosePubWidget::initDisabled(bool bedit )
//{
//	m_pGoosePubTable->setEnableChangeValue(bedit);
//}