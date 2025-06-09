#include "QAsyncAnalogTestParaSet.h"


QAsyncAnalogTestParaSet::QAsyncAnalogTestParaSet( tmt_async_modules *pModules,QWidget *parent /*= 0*/ )
			:QAsyncTestParaSetBase(pModules,parent)
{
	initData();
	initUI();
}

QAsyncAnalogTestParaSet::~QAsyncAnalogTestParaSet(void)
{
}

void QAsyncAnalogTestParaSet::initUI()
{
	// 初始化滚动区域和它的配置
	m_pMainScrollArea = new QScrollArea(this);
	m_pScrollWidget = new QWidget; // 滚动区域的子部件
	m_pMainScrollArea->setWidget(m_pScrollWidget);
	m_pMainScrollArea->setWidgetResizable(true);
	m_pMainScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	m_pMainScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// 设置滚动区域的子部件的布局为网格布局
	m_pGridLayout = new QGridLayout(m_pScrollWidget); // 应用于滚动区域的子部件
	m_pGridLayout->setContentsMargins(5, 0, 5, 10);

	// 初始化水平布局并设置为当前窗体的布局
	m_pHLayout = new QHBoxLayout;
	this->setLayout(m_pHLayout);

	for (int nIndex = 0; nIndex < m_ICHannelTableList.count(); nIndex++) 
	{
		QWidget* containerWidget = new QWidget;
		QVBoxLayout* vLayout = new QVBoxLayout(containerWidget);

		QLabel* pLabel = m_IChTableLableList[nIndex];
		pLabel->setMinimumWidth(90);

		QAsyncChannelTable* pTable = m_ICHannelTableList[nIndex];
		pTable->initTable();

		vLayout->addWidget(pLabel);
		vLayout->addWidget(pTable);
		vLayout->addStretch(1);
		vLayout->setSpacing(10); 

		m_pGridLayout->addWidget(containerWidget, nIndex, 0);
	}

	for (int nIndex = 0; nIndex < m_UCHannelTableList.count(); nIndex++) 
	{
		QWidget* containerWidget = new QWidget;
		QVBoxLayout* vLayout = new QVBoxLayout(containerWidget);

		QLabel* pLabel = m_UChTableLableList[nIndex];
		pLabel->setMinimumWidth(90);

		QAsyncChannelTable* pTable = m_UCHannelTableList[nIndex];
		pTable->initTable();

		vLayout->addWidget(pLabel);
		vLayout->addWidget(pTable);
		vLayout->addStretch(1);
		vLayout->setSpacing(10); 

		m_pGridLayout->addWidget(containerWidget, nIndex, 1);
	}

	m_pGridLayout->setHorizontalSpacing(0);
	m_pHLayout->addWidget(m_pMainScrollArea);

	for (int i = 0; i<m_UCHannelTableList.size();i++)
	{
		connect(m_UCHannelTableList[i],SIGNAL(sig_ChannelValueChanged()),this,SLOT(slot_ChannelValueChanged()));
	}
	for (int i = 0; i<m_ICHannelTableList.size();i++)
	{
		connect(m_ICHannelTableList[i],SIGNAL(sig_ChannelValueChanged()),this,SLOT(slot_ChannelValueChanged()));
	}
}

void QAsyncAnalogTestParaSet::initData()
{
	if(!m_pAsyncModules)
	{
		return;
	}

	m_UCHannelTableList.clear();
	m_UChTableLableList.clear();
	m_ICHannelTableList.clear();
	m_IChTableLableList.clear();

	int nCurCount = 0, nVolCount = 0, nMaxCount = 0;
	tmt_async_module *pModule = NULL;
	

	for(int nIndex = 0;nIndex < m_pAsyncModules->m_nAnalogCount; nIndex++)
	{
		pModule = &m_pAsyncModules->m_oAnalogModules[nIndex];
		if(pModule->m_nCurrChCount != 0 && pModule->m_nVolChCount==0)
		{
			QAsyncChannelTable *pTable = new QAsyncChannelTable(Moudle_I,pModule,pModule->m_nCurrChCount);
			CString strLable;
			strLable.Format(_T("电流模块%d"),++nCurCount);
			QLabel *pLabel = new QLabel;
			pLabel->setText(strLable);

			m_ICHannelTableList.append(pTable);
			m_IChTableLableList.append(pLabel);

		}
		else if(pModule->m_nCurrChCount == 0 && pModule->m_nVolChCount!=0)
		{
			QAsyncChannelTable *pTable = new QAsyncChannelTable(Moudle_U,pModule,pModule->m_nVolChCount);
			CString strLable;
			strLable.Format(_T("电压模块%d"),++nVolCount);

			QLabel *pLabel = new QLabel;
			pLabel->setText(strLable);

			m_UCHannelTableList.append(pTable);
			m_UChTableLableList.append(pLabel);

		}
		else if(pModule->m_nCurrChCount != 0 && pModule->m_nVolChCount!=0)
		{
			QAsyncChannelTable *pITable = new QAsyncChannelTable(Moudle_I,pModule,pModule->m_nCurrChCount);
			QAsyncChannelTable *pUTable = new QAsyncChannelTable(Moudle_U,pModule,pModule->m_nVolChCount);

			QLabel *pILabel = new QLabel;
			QLabel *pULabel = new QLabel;

			CString strLable;
			strLable.Format(_T("混合模块%d"),++nMaxCount);
			
			pILabel->setText(strLable);
			pULabel->setText(strLable);

			m_UCHannelTableList.append(pUTable);
			m_UChTableLableList.append(pULabel);
			m_ICHannelTableList.append(pITable);
			m_IChTableLableList.append(pILabel);

		}
	}

}

void QAsyncAnalogTestParaSet::DCStateChanged( bool bDc )
{
	m_bDc = bDc;

	int nAmpMinCoe = 0; 
	if(m_bDc)
	{
		nAmpMinCoe = -1;
	}

	for (int i = 0; i<m_UCHannelTableList.size();i++)
	{
		m_UCHannelTableList[i]->setAmpMinCoe(nAmpMinCoe);
		m_UCHannelTableList[i]->setProperty(bDc);
	}
	for (int i = 0; i<m_ICHannelTableList.size();i++)
	{
		m_ICHannelTableList[i]->setAmpMinCoe(nAmpMinCoe);
		m_ICHannelTableList[i]->setProperty(bDc);
	}

	for (int i = 0; i<m_UCHannelTableList.size();i++)
	{
		m_UCHannelTableList[i]->UpdateValidTableDatas();
	}
	for (int i = 0; i<m_ICHannelTableList.size();i++)
	{
		m_ICHannelTableList[i]->UpdateValidTableDatas();
	}
}

void QAsyncAnalogTestParaSet::setData( tmt_async_modules *pModules )
{
	if(!pModules)
	{
		return;
	}
	m_pAsyncModules = pModules;

	initData();
	UpdateTableData();
}


void QAsyncAnalogTestParaSet::UpdateModulesData( tmt_async_modules *pModules )
{
	if(!pModules)
	{
		return;
	}
	m_pAsyncModules = pModules;

	UpdateTableData();
}

void QAsyncAnalogTestParaSet::UpdateTableData()
{
	tmt_async_module *pModule = NULL;
	int nUIndex = 0, nIIndex = 0;

	for(int nIndex = 0;nIndex < m_pAsyncModules->m_nAnalogCount; nIndex++)
	{
		pModule = &m_pAsyncModules->m_oAnalogModules[nIndex];
		if(pModule->m_nCurrChCount != 0 && pModule->m_nVolChCount==0)
		{
			QAsyncChannelTable *p = m_ICHannelTableList.at(nIIndex);
			p->setTableData(pModule/*->m_pCurrChannel*/,pModule->m_nCurrChCount);
			nIIndex++;
		}
		else if(pModule->m_nCurrChCount == 0 && pModule->m_nVolChCount!=0)
		{
			QAsyncChannelTable *p = m_UCHannelTableList.at(nUIndex);
			p->setTableData(pModule/*->m_pVolChannel*/,pModule->m_nVolChCount);
			nUIndex++;
		}
		else if(pModule->m_nCurrChCount != 0 && pModule->m_nVolChCount!=0)
		{
			QAsyncChannelTable *pITable = m_ICHannelTableList.at(nIIndex);
			QAsyncChannelTable *pUTable = m_UCHannelTableList.at(nUIndex);

			pITable->setTableData(pModule/*->m_pCurrChannel*/,pModule->m_nCurrChCount);
			pUTable->setTableData(pModule/*->m_pVolChannel*/,pModule->m_nVolChCount);
			nIIndex++;
			nUIndex++;
		}

	}

// 	initData();

}

void QAsyncAnalogTestParaSet::slot_ChannelValueChanged()
{
	emit sig_updataParas();
}

void QAsyncAnalogTestParaSet::startInit()
{
// 	for(int nIndex = 0;nIndex < m_UCHannelTableList.size(); nIndex++)
// 	{
// 		m_UCHannelTableList[nIndex]->setDisabled(true);
// 	}
// 	for(int nIndex = 0;nIndex < m_ICHannelTableList.size(); nIndex++)
// 	{
// 		m_ICHannelTableList[nIndex]->setDisabled(true);
// 	}
	
	IsTestInProgress(true);
}

void QAsyncAnalogTestParaSet::stopInit()
{
// 	for(int nIndex = 0;nIndex < m_UCHannelTableList.size(); nIndex++)
// 	{
// 		m_UCHannelTableList[nIndex]->setDisabled(FALSE);
// 	}
// 	for(int nIndex = 0;nIndex < m_ICHannelTableList.size(); nIndex++)
// 	{
// 		m_ICHannelTableList[nIndex]->setDisabled(FALSE);
// 	}
	IsTestInProgress(false);
}

void QAsyncAnalogTestParaSet::IsTestInProgress( bool b )
{
	for(int nIndex = 0;nIndex < m_UCHannelTableList.size(); nIndex++)
	{
		m_UCHannelTableList[nIndex]->IsTestInProgress(b);
	}
	for(int nIndex = 0;nIndex < m_ICHannelTableList.size(); nIndex++)
	{
		m_ICHannelTableList[nIndex]->IsTestInProgress(b);
	}
}


