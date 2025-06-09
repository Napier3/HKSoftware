#include "gradientparaset.h"
#include <QDebug>
extern CFont *g_pSttGlobalFont;

GradientParaSet::GradientParaSet(QWidget *parent)
	: QWidget(parent)
{
	m_pMainGridLayout = new QGridLayout(this);
	m_pUScrollArea = new QScrollArea(this);
	m_pUScrollArea->setFont(*g_pSttGlobalFont);
	m_pIScrollArea = new QScrollArea(this);
	m_pIScrollArea->setFont(*g_pSttGlobalFont);
	m_pUWidget = new QWidget(m_pUScrollArea);
	m_pUWidget->setFont(*g_pSttGlobalFont);
	m_pIWidget = new QWidget(m_pIScrollArea);
	m_pIWidget->setFont(*g_pSttGlobalFont);
	m_pUScrollArea->setWidget(m_pUWidget);
	m_pIScrollArea->setWidget(m_pIWidget);
	m_pUVGridLayout = new QGridLayout(m_pUWidget);
	m_pIVGridLayout = new QGridLayout(m_pIWidget);

	m_pArrUIVOL = NULL;
	m_pArrUICUR = NULL;
	m_pGradientParaSetSttTestResource = NULL;
}

GradientParaSet::~GradientParaSet()
{
	Release();
	delete m_pUVGridLayout;
	delete m_pIVGridLayout;
	delete m_pUWidget;
	delete m_pIWidget;
	delete m_pUScrollArea;
	delete m_pIScrollArea;
	delete m_pMainGridLayout;
}

void GradientParaSet::Release()
{
	for (int i = 0; i< m_UCHannelTableList.size(); i++)
	{
		GradientChannelTable *p = m_UCHannelTableList.at(i);
		delete p;
		p = NULL;
	}
	m_UCHannelTableList.clear();

	for (int i = 0; i< m_ICHannelTableList.size(); i++)
	{
		GradientChannelTable *p = m_ICHannelTableList.at(i);
		delete p;
		p = NULL;
	}
	m_ICHannelTableList.clear();
}

void GradientParaSet::initUI(CSttTestResourceBase *pSttTestResource)
{
	Release();

	if (pSttTestResource != NULL)
	{
		m_pGradientParaSetSttTestResource = pSttTestResource;
	}

	if (m_pGradientParaSetSttTestResource == NULL)
	{
		return;
	};

	GradientChannelTable *pVolChTable = NULL,*pCurChTable = NULL;

	int nGradientType = GRADIENT_TYPE_None;
	if(m_pStatePara->m_nRampTimeGrad > 1)
	{
		nGradientType = GRADIENT_TYPE_Step;
	}
	else
	{
		nGradientType = GRADIENT_TYPE_Linear;
	}

	if(m_nGradientObj == GRADIENT_AMP)
	{
		pVolChTable = new GradientChannelTable(Moudle_U,nGradientType,m_nGradientObj,&m_pGradientParaSetSttTestResource->m_oVolChRsListRef,m_pArrUIVOL/*,m_pUWidget*/);
		pCurChTable = new GradientChannelTable(Moudle_I,nGradientType,m_nGradientObj,&m_pGradientParaSetSttTestResource->m_oCurChRsListRef,m_pArrUICUR/*,m_pIWidget*/);
	}
	else if (m_nGradientObj == GRADIENT_ANG)
	{
		pVolChTable = new GradientChannelTable(Moudle_U,nGradientType,m_nGradientObj,&m_pGradientParaSetSttTestResource->m_oVolChRsListRef,m_pArrUIVOL/*,m_pUWidget*/);	
		pCurChTable = new GradientChannelTable(Moudle_I,nGradientType,m_nGradientObj,&m_pGradientParaSetSttTestResource->m_oCurChRsListRef,m_pArrUICUR/*,m_pIWidget*/);
	}
	else if (m_nGradientObj == GRADIENT_FRE)
	{
		pVolChTable = new GradientChannelTable(Moudle_U,nGradientType,m_nGradientObj,&m_pGradientParaSetSttTestResource->m_oVolChRsListRef,m_pArrUIVOL/*,m_pUWidget*/);	
		pCurChTable = new GradientChannelTable(Moudle_I,nGradientType,m_nGradientObj,&m_pGradientParaSetSttTestResource->m_oCurChRsListRef,m_pArrUICUR/*,m_pIWidget*/);
	}

	m_UCHannelTableList.append(pVolChTable);
	m_ICHannelTableList.append(pCurChTable);

	int nUWidgetHeight = 0;	
	int nUWidgetWidth = 0;
	for (int i = 0; i < m_UCHannelTableList.size(); i++)
	{
		nUWidgetWidth = m_UCHannelTableList[i]->getTableWidth();
		nUWidgetHeight += m_UCHannelTableList[i]->getTableHeight();
		m_pUVGridLayout->addWidget(m_UCHannelTableList.at(i),i,0,1,1);
	}
	
	m_pUWidget->setMinimumHeight(nUWidgetHeight);
	m_pUVGridLayout->setMargin(0);
	m_pUVGridLayout->setSpacing(0);
	m_pUWidget->setLayout(m_pUVGridLayout);

	int nIWidgetHeight = 0;
	int nIWidgetWidth = 0;
	for (int i = 0; i < m_ICHannelTableList.size(); i++)
	{
		nIWidgetWidth = m_ICHannelTableList[i]->getTableWidth();
		nIWidgetHeight += m_ICHannelTableList[i]->getTableHeight();
		m_pIVGridLayout->addWidget(m_ICHannelTableList.at(i),i,0,1,1);
	}

	m_pIWidget->setMinimumHeight(nIWidgetHeight);	
	m_pIVGridLayout->setMargin(0);
	m_pIVGridLayout->setSpacing(0);
	m_pIWidget->setLayout(m_pIVGridLayout);

	m_pUScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pUScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pIScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pIScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pUScrollArea->setWidgetResizable(true);
	m_pIScrollArea->setWidgetResizable(true);
	m_pMainGridLayout->addWidget(m_pUScrollArea,0,0);
	m_pMainGridLayout->addWidget(m_pIScrollArea,0,1);

	if(m_ICHannelTableList.size() > 1)
	{
		m_pIScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		m_pIVGridLayout->setRowStretch(m_ICHannelTableList.size(),1);
	}

	if(m_UCHannelTableList.size() > 1)
	{
		m_pUScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		m_pUVGridLayout->setRowStretch(m_UCHannelTableList.size(),1);
	}
}

void GradientParaSet::initData()
{
	if ((m_pGradientParaSetSttTestResource == NULL)||(m_pArrUIVOL == NULL)||(m_pArrUICUR == NULL))
	{
		return;
	}

	if (m_UCHannelTableList.size()>=1)
	{
		m_UCHannelTableList[0]->setTableData(m_pArrUIVOL);
	}

	if (m_ICHannelTableList.size()>=1)
	{
		m_ICHannelTableList[0]->setTableData(m_pArrUICUR);
	}
}

void GradientParaSet::setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource, tmt_StatePara *pStatePara, int nGradientObj)
{
	ASSERT(pSttTestResource);
	ASSERT( pArrUIVOL != NULL);
	ASSERT( pArrUICUR != NULL);

	
	m_pGradientParaSetSttTestResource = pSttTestResource;
	m_pStatePara = pStatePara;
	m_pArrUIVOL = m_pStatePara->m_uiVOL;
	m_pArrUICUR = m_pStatePara->m_uiCUR;
	m_nGradientObj = nGradientObj;

	initUI(pSttTestResource);
	initData();
}

void GradientParaSet::setData(tmt_StatePara *pStatePara)
{
	ASSERT( pStatePara != NULL);

	m_pArrUIVOL = m_pStatePara->m_uiVOL;
	m_pArrUICUR = m_pStatePara->m_uiCUR;
}

void GradientParaSet::setMaxMinVal()
{
	if(m_nGradientObj == GRADIENT_AMP)
	{
		setUAmpMaxMinValue();
		setIAmpMaxMinValue();
	}
	else if (m_nGradientObj == GRADIENT_FRE)
	{
		setUIFreMaxMinValue();
	}
}

void GradientParaSet::setUAmpMaxMinValue()
{
	int num = 0;
	num = m_UCHannelTableList.size();
	for (int i=0; i<num; i++)
	{
		if(m_pArrUIVOL[0].Harm[1].bDC)
		{
			m_UCHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fDC_VolMax,0);
		}
		else
		{
			m_UCHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fAC_VolMax,0);
		}
	}
}

void GradientParaSet::setIAmpMaxMinValue()
{
	int num = 0;
	num = m_ICHannelTableList.size();
	for (int i =0; i<num; i++)
	{
		if (m_pArrUIVOL[0].Harm[1].bDC)
		{
			m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fDC_CurMax ,0);
		}
		else
		{
			m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fAC_CurMax,0);
		}
	}
}

void GradientParaSet::setUIFreMaxMinValue()
{
	int num = m_UCHannelTableList.size();
	for (int i=0; i<num; i++)
	{
		m_UCHannelTableList[i]->setAmpMaxMinValue(Global_GetMaxFreq(),0);
	}

	num = m_ICHannelTableList.size();
	for (int i =0; i<num; i++)
	{
		m_ICHannelTableList[i]->setAmpMaxMinValue(Global_GetMaxFreq(),0);
	}
}

void GradientParaSet::saveData()
{
	int num = m_UCHannelTableList.size();
	for (int i=0; i<num; i++)
	{
		m_UCHannelTableList[i]->saveTable();
	}

	num = m_ICHannelTableList.size();
	for (int i=0; i<num; i++)
	{
		m_ICHannelTableList[i]->saveTable();
	}
}

void GradientParaSet::updateGradientType(int nType)
{
	int num = m_UCHannelTableList.size();
	for (int i=0; i<num; i++)
	{
		m_UCHannelTableList[i]->m_nGradientType = nType;
		m_UCHannelTableList[i]->initTable();
		m_UCHannelTableList[i]->UpdateTable();
	}

	num = m_ICHannelTableList.size();
	for (int i=0; i<num; i++)
	{
		m_ICHannelTableList[i]->m_nGradientType = nType;
		m_ICHannelTableList[i]->initTable();
		m_ICHannelTableList[i]->UpdateTable();
	}
}

void GradientParaSet::InitLinearStepGradient()
{
	int num = m_UCHannelTableList.size();
	for (int i=0; i<num; i++)
	{
		m_UCHannelTableList[i]->InitLinearStepGradient();
	}

	num = m_ICHannelTableList.size();

	for (int i=0; i<num; i++)
	{
		m_ICHannelTableList[i]->InitLinearStepGradient();
	}
}