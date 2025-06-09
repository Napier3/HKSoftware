#include "SttIntelBoutToGinParaWidget.h"
#include <QGridLayout>
#include "../../../Module/API/GlobalConfigApi.h"
#include "../Module/TestWinFrame/testwinbase.h"

QSttIntelBoutToGinParaWidget::QSttIntelBoutToGinParaWidget(CIecCfgGinDatas* pCfgGinDatas ,bool bInitEditable)
{
	initUI();
	initGoosePubTable(pCfgGinDatas);
	m_bInitEditable = bInitEditable;
	connect(chb_cbBinOut5, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_BinOut5StateChanged(int)));
	connect(chb_cbBinOut6, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_BinOut6StateChanged(int)));
	connect(chb_cbBinOut7, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_BinOut7StateChanged(int)));
	connect(chb_cbBinOut8, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_BinOut8StateChanged(int)));
}

QSttIntelBoutToGinParaWidget::~QSttIntelBoutToGinParaWidget()
{

}

void QSttIntelBoutToGinParaWidget::initUI()
{
	QGroupBox *groupBox;
	QGridLayout *gridLayout;
	QHBoxLayout *horizontalLayout;

	groupBox = new QGroupBox("快速开出");
	groupBox->setObjectName(QString::fromUtf8("groupBox"));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
	groupBox->setSizePolicy(sizePolicy);
	groupBox->setGeometry(QRect(300, 10, 400, 130));
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

	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing(6);
	horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
	/*horizontalSpacer = new QSpacerItem(102, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	horizontalLayout->addItem(horizontalSpacer);*/

	chb_cbBinOut5 = new QCheckBox(groupBox);
	chb_cbBinOut5->setObjectName(QString::fromUtf8("chb_cbBinOut5"));
	chb_cbBinOut5->setText(tr("开出5"));
	horizontalLayout->addWidget(chb_cbBinOut5);
	chb_cbBinOut5->setDisabled(g_theSttXTestMngrBaseApp->m_bGooseFlag);

	chb_cbBinOut6 = new QCheckBox(groupBox);
	chb_cbBinOut6->setObjectName(QString::fromUtf8("chb_cbBinOut6"));
	chb_cbBinOut6->setText(tr("开出6"));
	horizontalLayout->addWidget(chb_cbBinOut6);
	chb_cbBinOut6->setDisabled(g_theSttXTestMngrBaseApp->m_bGooseFlag);

	chb_cbBinOut7 = new QCheckBox(groupBox);
	chb_cbBinOut7->setObjectName(QString::fromUtf8("chb_cbBinOut7"));
	chb_cbBinOut7->setText(tr("开出7"));
	horizontalLayout->addWidget(chb_cbBinOut7);
	chb_cbBinOut7->setDisabled(g_theSttXTestMngrBaseApp->m_bGooseFlag);

	chb_cbBinOut8 = new QCheckBox(groupBox);
	chb_cbBinOut8->setObjectName(QString::fromUtf8("chb_cbBinOut8"));
	chb_cbBinOut8->setText(tr("开出8"));
	horizontalLayout->addWidget(chb_cbBinOut8);
	chb_cbBinOut8->setDisabled(g_theSttXTestMngrBaseApp->m_bGooseFlag);

	gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

	m_tab_GoosePub = new QTabWidget(this);

	QGridLayout* pLayout = new QGridLayout;
	//pLayout->addLayout(horizontalLayout, 0, 4, 1, 1);
	pLayout->addWidget(groupBox, 0, 0, 1, 1);
	pLayout->addWidget(m_tab_GoosePub,1,0,8,1);
	setLayout(pLayout);
}

void QSttIntelBoutToGinParaWidget::initGoosePubTable(CIecCfgGinDatas* pCfgGinDatas)
{
	if (pCfgGinDatas == NULL)
	{
		return;
	}

	m_tab_GoosePub->clear();
	if (m_pGoosePubList.size() > 0)
	{
		for (int i =0; i < m_pGoosePubList.size(); i++)
		{
			delete m_pGoosePubList[i];
			m_pGoosePubList[i] = NULL;
		}
		m_pGoosePubList.clear();
	}

	CIecCfgGinData* pCfgGinData = NULL;
	long nGoutIndex = 0;
	POS pos = pCfgGinDatas->GetHeadPosition();
	while(pos)
	{
		pCfgGinData = (CIecCfgGinData*)pCfgGinDatas->GetNext(pos);

		if (pCfgGinData->m_nUseFlag == 1)
		{
			QSttIntelBoutToGinPubWidget *pGoosePub = new QSttIntelBoutToGinPubWidget(m_tab_GoosePub);
			connect(pGoosePub, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
			connect(pGoosePub,SIGNAL(sig_GinRowIndex(int,float)),this,SLOT(slot_GinRowIndex(int,float)));
			m_tab_GoosePub->insertTab(nGoutIndex, pGoosePub, QString("G%1").arg(nGoutIndex+1));
			m_pGoosePubList.append(pGoosePub);
			initOneGooseBlockTable(pGoosePub,pCfgGinData);
			nGoutIndex++;
	
		}
	}
}	

void QSttIntelBoutToGinParaWidget::initOneGooseBlockTable( QSttIntelBoutToGinPubWidget *p,CIecCfgGinData *pCfgGinData )
{
	p->initData(pCfgGinData,m_bInitEditable);
}

void QSttIntelBoutToGinParaWidget::slot_GooseDataChanged()
{
	emit sig_GooseDataChanged();
}

void QSttIntelBoutToGinParaWidget::slot_GinRowIndex(int nRowIndex,float fActTime)
{
	emit sig_GinRowIndex(nRowIndex,fActTime);
}

void QSttIntelBoutToGinParaWidget::slot_chb_BinOut5StateChanged( int nStateValue)
{
	ASSERT(m_pGoosePubList[m_tab_GoosePub->currentIndex()]->m_pSttIntelBoutToGinGrid);
	if (nStateValue==Qt::Checked)
	{
		emit sig_setBinOut(4,TRUE);	
		if (g_theSttXTestMngrBaseApp->m_bGooseFlag)
	{
		m_pGoosePubList[m_tab_GoosePub->currentIndex()]->UpdateState(nStateValue);
	}
}
	else
	{
		emit sig_setBinOut(4,FALSE);
	}
}
void QSttIntelBoutToGinParaWidget::slot_chb_BinOut6StateChanged( int nStateValue)
{
	ASSERT(m_pGoosePubList[m_tab_GoosePub->currentIndex()]->m_pSttIntelBoutToGinGrid);
	if (nStateValue==Qt::Checked)
	{
		emit sig_setBinOut(5,TRUE);
		if (g_theSttXTestMngrBaseApp->m_bGooseFlag)
	{
		m_pGoosePubList[m_tab_GoosePub->currentIndex()]->UpdateState(nStateValue);
	}
}
	else
	{
		emit sig_setBinOut(5,FALSE);
	}
}
void QSttIntelBoutToGinParaWidget::slot_chb_BinOut7StateChanged( int nStateValue)
{
	ASSERT(m_pGoosePubList[m_tab_GoosePub->currentIndex()]->m_pSttIntelBoutToGinGrid);
	if (nStateValue==Qt::Checked)
	{
		emit sig_setBinOut(6,TRUE);
		if (g_theSttXTestMngrBaseApp->m_bGooseFlag)
	{
		m_pGoosePubList[m_tab_GoosePub->currentIndex()]->UpdateState(nStateValue);
	}
}
	else
	{
		emit sig_setBinOut(6,FALSE);
	}
}
void QSttIntelBoutToGinParaWidget::slot_chb_BinOut8StateChanged( int nStateValue)
{
	ASSERT(m_pGoosePubList[m_tab_GoosePub->currentIndex()]->m_pSttIntelBoutToGinGrid);
	if (nStateValue==Qt::Checked)
	{
		emit sig_setBinOut(7,TRUE);
		if (g_theSttXTestMngrBaseApp->m_bGooseFlag)
	{
		m_pGoosePubList[m_tab_GoosePub->currentIndex()]->UpdateState(nStateValue);
	}
}
	else
	{
		emit sig_setBinOut(7,FALSE);
	}
}

void QSttIntelBoutToGinParaWidget::SetRunState(int nRunState)
{
	int num = m_pGoosePubList.size();
	for (int i =0; i < num; i++)
	{
		m_pGoosePubList[i]->SetRunState(nRunState);
	}
}

void QSttIntelBoutToGinParaWidget::SetGooseDisabled( bool bFlag )
{
	for (int i =0; i < m_pGoosePubList.size(); i++)
	{
		if (i==m_tab_GoosePub->currentIndex())
		{
			m_tab_GoosePub->setTabEnabled(i,bFlag);
		}
		else
		{
			m_tab_GoosePub->setTabEnabled(i,!bFlag);
		}
	}
}

void QSttIntelBoutToGinParaWidget::setGooseTabEnable( bool bFlag )
{
	for (int i =0; i < m_pGoosePubList.size(); i++)
	{
		m_tab_GoosePub->setTabEnabled(i,bFlag);
	}
}
void QSttIntelBoutToGinParaWidget::startInit( )
{
	m_pGoosePubList[m_tab_GoosePub->currentIndex()]->startInit();
}
