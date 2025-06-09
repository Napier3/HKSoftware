#include "FT3ParaWidget.h"
#include <QGridLayout>

QFT3ParaWidget::QFT3ParaWidget(CIecCfgDatasSMV *pIecCfgDatasSMV)
{
	initUI();
	InitFT3Table(pIecCfgDatasSMV);
}

QFT3ParaWidget::~QFT3ParaWidget()
{

}

void QFT3ParaWidget::initUI()
{
	m_tab_FT3Pub = new QTabWidget(this);
	QGridLayout* pLayout = new QGridLayout;
	pLayout->addWidget(m_tab_FT3Pub);
	setLayout(pLayout);
}

void QFT3ParaWidget::InitFT3Table(CIecCfgDatasSMV *pIecCfgDatasSMV)
{
	if (pIecCfgDatasSMV == NULL)
	{
		return;
	}
	m_tab_FT3Pub->clear();
	if (m_pFT3WidgetList.size() > 0)
	{
		for (int i =0; i < m_pFT3WidgetList.size(); i++)
		{
			delete m_pFT3WidgetList[i];
			m_pFT3WidgetList[i] = NULL;
		}
		m_pFT3WidgetList.clear();
	}
	CIecCfg6044CommonData* pIecCfg6044CommonData = NULL;
	CExBaseObject *pCurObj = NULL;
	long nIndex = 0;
	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	while(pos)
	{
		pCurObj=pIecCfgDatasSMV->GetNext(pos);
		if (pCurObj->GetClassID()==CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			pIecCfg6044CommonData=(CIecCfg6044CommonData*)pCurObj;
			
			if (pIecCfg6044CommonData->m_nUseFlag == 1)
			{
				FT3Widget *pFT3Widget=new FT3Widget(m_tab_FT3Pub);

				connect(pFT3Widget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
				m_tab_FT3Pub->insertTab(nIndex, pFT3Widget, QString("G%1").arg(nIndex+1));
				m_pFT3WidgetList.append(pFT3Widget);
				initOneFT3BlockTable(pFT3Widget,pIecCfg6044CommonData);
				nIndex++;
			}						
		}
	}
}

void QFT3ParaWidget::initOneFT3BlockTable(FT3Widget *p,CIecCfg6044CommonData* pCfg6044CommonData)
{
	p->InitData(pCfg6044CommonData);
}

void QFT3ParaWidget::slot_FT3DataChanged()
{
	emit sig_FT3DataChanged();
}


void QFT3ParaWidget::SetRunState(int nRunState)
{
	int num = m_pFT3WidgetList.size();
	for (int i =0; i < num; i++)
	{
		m_pFT3WidgetList[i]->SetRunState(nRunState);
	}
}

void QFT3ParaWidget::SetGooseDisabled(bool bFlag)
{
	int num = m_pFT3WidgetList.size();
	for (int i =0; i < num; i++)
	{
		m_pFT3WidgetList[i]->m_pFT3Grid->setDisabled(bFlag);
	}
}


