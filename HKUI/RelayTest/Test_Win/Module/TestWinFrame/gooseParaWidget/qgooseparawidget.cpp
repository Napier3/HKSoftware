#include "qgooseparawidget.h"
#include <QGridLayout>
#include "GoosePubWidget.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../Module/TestWinFrame/testwinbase.h"

QGooseParaWidget::QGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas ,bool bInitEditable)
{
	initUI();
	initGoosePubTable(pCfgGoutDatas);
	m_bInitEditable = bInitEditable;
}

QGooseParaWidget::~QGooseParaWidget()
{

}

void QGooseParaWidget::initUI()
{
	m_tab_GoosePub = new QTabWidget(this);

	QGridLayout* pLayout = new QGridLayout;
	pLayout->addWidget(m_tab_GoosePub);
	setLayout(pLayout);
}

void QGooseParaWidget::initGoosePubTable(CIecCfgGoutDatas* pCfgGoutDatas)
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
			GoosePubWidget *pGoosePub = new GoosePubWidget(m_tab_GoosePub);

			connect(pGoosePub, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
			connect(pGoosePub, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_RepairDataChanged()));
			m_tab_GoosePub->insertTab(nGoutIndex, pGoosePub, QString("G%1").arg(nGoutIndex+1));
			m_pGoosePubList.append(pGoosePub);
			initOneGooseBlockTable(pGoosePub,pCfgGoutData);
			nGoutIndex++;
		}
	}
}	

void QGooseParaWidget::initOneGooseBlockTable( GoosePubWidget *p,CIecCfgGoutData *pCfgGoutData )
{
	p->initData(pCfgGoutData,m_bInitEditable);
}

void QGooseParaWidget::slot_GooseDataChanged()
{
	emit sig_GooseDataChanged();
}

void QGooseParaWidget::slot_RepairDataChanged()
{
	emit sig_RepairDataChanged();
}

void QGooseParaWidget::SetRunState(int nRunState)
{
	int num = m_pGoosePubList.size();
	for (int i =0; i < num; i++)
	{
		m_pGoosePubList[i]->SetRunState(nRunState);
	}
}

void QGooseParaWidget::SetGooseDisabled( bool bFlag )
{
	int num = m_pGoosePubList.size();
	for (int i =0; i < num; i++)
	{
		m_pGoosePubList[i]->chb_Invert->setDisabled(bFlag);
		m_pGoosePubList[i]->chb_Repair->setDisabled(bFlag);
		//m_pGoosePubList[i]->EnableInverseCol(!bFlag);		//sf 20211006 只能设置第四行不可编辑
		m_pGoosePubList[i]->m_pIecCfgGoutChsGrid->setDisabled(bFlag);
	}
	
//	m_tab_GoosePub->setDisabled(bFlag);
}

// void QGooseParaWidget::initDisabled(bool bedit)
// {
// 	int num = m_pGoosePubList.size();
// 	for (int i =0; i < num; i++)
// 	{
// 		m_pGoosePubList[i]->initDisabled(bedit);
// 	}
//}