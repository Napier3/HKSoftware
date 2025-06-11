#include "SttIntelBoutToGinParaWidget.h"
#include <QGridLayout>
#include "../../../Module/API/GlobalConfigApi.h"

QSttIntelBoutToGinParaWidget::QSttIntelBoutToGinParaWidget(CIecCfgGinDatas* pCfgGinDatas ,bool bInitEditable)
{
	m_bGooseFlag = false;
	initUI();
	initGoosePubTable(pCfgGinDatas);
}

QSttIntelBoutToGinParaWidget::~QSttIntelBoutToGinParaWidget()
{

}

void QSttIntelBoutToGinParaWidget::initUI()
{
	m_tab_GoosePub = new QTabWidget(this);

	QGridLayout* pLayout = new QGridLayout;
	pLayout->addWidget(m_tab_GoosePub,1,0,5,2);
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
			QSttIntelBoutToGinPubWidget *pGoosePub = new QSttIntelBoutToGinPubWidget(this,m_tab_GoosePub);
			connect(pGoosePub, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
			connect(pGoosePub, SIGNAL(sig_setBinOut(int,bool)), this, SLOT(slot_setBinOut(int,bool)));
			connect(pGoosePub,SIGNAL(sig_GinRowIndex(int,float)),this,SLOT(slot_GinRowIndex(int,float)));
			m_tab_GoosePub->insertTab(nGoutIndex, pGoosePub, QString("G%1").arg(nGoutIndex+1));
			m_pGoosePubList.append(pGoosePub);
			initOneGooseBlockTable(pGoosePub,pCfgGinData);
			nGoutIndex++;
		}
	}
	m_tab_GoosePub->setFont(*g_pSttGlobalFont);
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

void QSttIntelBoutToGinParaWidget::slot_setBinOut(int nbout ,bool bStateChanged)
{
	emit sig_setBinOut(nbout,bStateChanged);
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
	m_bGooseFlag=bFlag;
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