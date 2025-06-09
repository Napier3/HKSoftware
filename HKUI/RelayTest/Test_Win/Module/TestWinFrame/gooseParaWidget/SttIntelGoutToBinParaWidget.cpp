#include "SttIntelGoutToBinParaWidget.h"
#include <QGridLayout>
//#include "GoosePubWidget.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../Module/TestWinFrame/testwinbase.h"


QSttIntelGoutToBinParaWidget::QSttIntelGoutToBinParaWidget(CIecCfgGoutDatas* pCfgGoutDatas ,bool bInitEditable)
{
	initUI();
	initGoosePubTable(pCfgGoutDatas);
	m_bInitEditable = bInitEditable;
}

QSttIntelGoutToBinParaWidget::~QSttIntelGoutToBinParaWidget()
{

}

void QSttIntelGoutToBinParaWidget::initUI()
{
	m_tab_GoosePub = new QTabWidget(this);

	QGridLayout* pLayout = new QGridLayout;
	pLayout->addWidget(m_tab_GoosePub);
	setLayout(pLayout);
}

void QSttIntelGoutToBinParaWidget::initGoosePubTable(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (pCfgGoutDatas == NULL)
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

	CIecCfgGoutData* pCfgGoutData = NULL;
	long nGoutIndex = 0;
	POS pos = pCfgGoutDatas->GetHeadPosition();

	while(pos)
	{
		pCfgGoutData = (CIecCfgGoutData*)pCfgGoutDatas->GetNext(pos);

		if (pCfgGoutData->m_nUseFlag == 1)
		{
			QSttIntelGoutToBinPubWidget *pGoosePub = new QSttIntelGoutToBinPubWidget(m_tab_GoosePub);
			connect(pGoosePub, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
			connect(pGoosePub, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_RepairDataChanged()));
			connect(pGoosePub, SIGNAL(sig_RevertData()), this, SLOT(slot_RevertData()));	
			connect(pGoosePub,SIGNAL(sig_GoutRowIndex(int)),this,SLOT(slot_GoutRowIndex(int)));
			m_tab_GoosePub->insertTab(nGoutIndex, pGoosePub, QString("G%1").arg(nGoutIndex+1));
			m_pGoosePubList.append(pGoosePub);
			initOneGooseBlockTable(pGoosePub,pCfgGoutData);
			nGoutIndex++;
		}
	}
}	

void QSttIntelGoutToBinParaWidget::SetCurrentIndex( int nIndex )
{
	m_tab_GoosePub->setCurrentIndex(nIndex);
	emit sig_TabChanged(nIndex);
}

void QSttIntelGoutToBinParaWidget::initOneGooseBlockTable( QSttIntelGoutToBinPubWidget *p,CIecCfgGoutData *pCfgGoutData )
{
	p->initData(pCfgGoutData,m_bInitEditable);
}

void QSttIntelGoutToBinParaWidget::slot_GooseDataChanged()
{
	emit sig_GooseDataChanged();
}

void QSttIntelGoutToBinParaWidget::slot_RepairDataChanged()
{
	emit sig_RepairDataChanged();
}

void QSttIntelGoutToBinParaWidget::slot_RevertData()
{
	emit sig_RevertData();
}
void QSttIntelGoutToBinParaWidget::slot_GoutRowIndex(int nRowIndex)
{
	emit sig_GoutRowIndex(nRowIndex);
}

void QSttIntelGoutToBinParaWidget::SetRunState(int nRunState)
{
	int num = m_pGoosePubList.size();
	for (int i =0; i < num; i++)
	{
		m_pGoosePubList[i]->SetRunState(nRunState);
	}
}

void QSttIntelGoutToBinParaWidget::SetGooseDisabled( bool bFlag )
{
	int num = m_pGoosePubList.size();
	int index=m_tab_GoosePub->currentIndex();
	for (int i =0; i < num; i++)
	{	
		m_pGoosePubList[i]->pbn_Revert->setDisabled(bFlag);
		if (index==i)
		{
			m_tab_GoosePub->setTabEnabled(i,bFlag);
		}
		else
		{
			m_tab_GoosePub->setTabEnabled(i,!bFlag);
		}
         m_pGoosePubList[i]->EnableInverseCol(bFlag);
		m_pGoosePubList[i]->chb_Repair->setDisabled(bFlag);
	
	}
}
void QSttIntelGoutToBinParaWidget::setGooseTabEnable( bool bFlag )
{
	for (int i =0; i < m_pGoosePubList.size(); i++)
	{
		m_tab_GoosePub->setTabEnabled(i,bFlag);
	}
}

void QSttIntelGoutToBinParaWidget::setGooseResultVlaues( )
{
	for (int i =0; i < m_pGoosePubList.size(); i++)
	{
		m_pGoosePubList[i]->setGooseResultVlaues();
	}
}
void QSttIntelGoutToBinParaWidget::startInit( )
{
	m_pGoosePubList[m_tab_GoosePub->currentIndex()]->startInit();
}
