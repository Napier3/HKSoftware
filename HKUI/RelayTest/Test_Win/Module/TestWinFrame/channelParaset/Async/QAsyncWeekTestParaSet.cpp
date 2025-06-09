#include "QAsyncWeekTestParaSet.h"

QAsyncWeekTestParaSet::QAsyncWeekTestParaSet( tmt_async_modules *pModules,QWidget *parent /*= 0*/ )
			:QAsyncTestParaSetBase(pModules,parent)
{
// 	m_pAsyncModules = pModules;
// 
	initData();
	initUI();
}

QAsyncWeekTestParaSet::~QAsyncWeekTestParaSet(void)
{

}

void QAsyncWeekTestParaSet::initUI()
{
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

	for (int nIndex = 0; nIndex < m_LeftChannelTableList.count(); nIndex++) 
	{
		QWidget* containerWidget = new QWidget;
		QVBoxLayout* vLayout = new QVBoxLayout(containerWidget);

		QLabel* pLabel = m_ChTableLableList[nIndex];
		pLabel->setMinimumWidth(90);

		QAsyncChannelTable* pTable = m_LeftChannelTableList[nIndex];
		pTable->initTable();

		vLayout->addWidget(pLabel);
		vLayout->addWidget(pTable);
		vLayout->addStretch(1);
		vLayout->setSpacing(10); 

		m_pGridLayout->addWidget(containerWidget, nIndex, 0);
	}

	for (int nIndex = 0; nIndex < m_RightChannelTableList.count(); nIndex++) 
	{
		QWidget* containerWidget = new QWidget;
		QVBoxLayout* vLayout = new QVBoxLayout(containerWidget);

		QLabel* pLabel = new QLabel;
		pLabel->setFixedWidth(60);

		QAsyncChannelTable* pTable = m_RightChannelTableList[nIndex];
		pTable->initTable();

		vLayout->addWidget(pLabel);
		vLayout->addWidget(pTable);
		vLayout->addStretch(1);
		vLayout->setSpacing(10); 

		m_pGridLayout->addWidget(containerWidget, nIndex, 1);
	}
	m_pGridLayout->setHorizontalSpacing(0);

	m_pHLayout->addWidget(m_pMainScrollArea);

	for (int i = 0; i<m_RightChannelTableList.size();i++)
	{
		connect(m_RightChannelTableList[i],SIGNAL(sig_ChannelValueChanged()),this,SLOT(slot_ChannelValueChanged()));
	}
	for (int i = 0; i<m_LeftChannelTableList.size();i++)
	{
		connect(m_LeftChannelTableList[i],SIGNAL(sig_ChannelValueChanged()),this,SLOT(slot_ChannelValueChanged()));
	}

}

void QAsyncWeekTestParaSet::initData()
{
	if(!m_pAsyncModules)
	{
		return;
	}

	int nCurCount = 0, nVolCount = 0, nMaxCount = 0;
	tmt_async_module *pModule = NULL;

	m_RightChannelTableList.clear();
	m_LeftChannelTableList.clear();
	m_ChTableLableList.clear();

	for(int nIndex = 0;nIndex < m_pAsyncModules->m_nWeekCount; nIndex++)
	{			
		pModule = &m_pAsyncModules->m_oWeekModules[nIndex];
		if(pModule->m_nCurrChCount != 0 && pModule->m_nVolChCount==0)
		{
			int nBeginIndex = 0;
			int nChCount = 0;

			if(pModule->m_nCurrChCount >= 12)
			{
				nChCount = pModule->m_nCurrChCount/2;
			}
			QAsyncChannelTable *pTable1 = new QAsyncChannelTable(Moudle_I,pModule,nChCount,nBeginIndex,
				m_pAsyncModules->m_nDc[ASYNC_MODULE_TYPE_WEEK]);
			QAsyncChannelTable *pTable2 = new QAsyncChannelTable(Moudle_I,pModule,nChCount,nBeginIndex+nChCount,
				m_pAsyncModules->m_nDc[ASYNC_MODULE_TYPE_WEEK]);

			CString strLable;
			strLable.Format(_T("弱信号模块%d"),++nCurCount);
			QLabel *pLabel = new QLabel;
			pLabel->setText(strLable);

			m_LeftChannelTableList.append(pTable1);
			m_RightChannelTableList.append(pTable2);

			m_ChTableLableList.append(pLabel);

		}
		else if(pModule->m_nCurrChCount == 0 && pModule->m_nVolChCount!=0)
		{
			int nBeginIndex = 0;
			int nChCount = 0;

			if(pModule->m_nVolChCount >= 12)
			{
				nChCount = pModule->m_nVolChCount/2;
			}
			QAsyncChannelTable *pTable1 = new QAsyncChannelTable(Moudle_U,pModule,nChCount,nBeginIndex,
				m_pAsyncModules->m_nDc[ASYNC_MODULE_TYPE_WEEK]);
			QAsyncChannelTable *pTable2 = new QAsyncChannelTable(Moudle_U,pModule,nChCount,nBeginIndex+nChCount,
				m_pAsyncModules->m_nDc[ASYNC_MODULE_TYPE_WEEK]);

			CString strLable;
			strLable.Format(_T("弱信号模块%d"),++nCurCount);
			QLabel *pLabel = new QLabel;
			pLabel->setText(strLable);

			m_LeftChannelTableList.append(pTable1);
			m_RightChannelTableList.append(pTable2);

			m_ChTableLableList.append(pLabel);

		}
		else if(pModule->m_nCurrChCount != 0 && pModule->m_nVolChCount!=0)
		{
			QAsyncChannelTable *pITable = new QAsyncChannelTable(Moudle_I,pModule,pModule->m_nCurrChCount);
			QAsyncChannelTable *pUTable = new QAsyncChannelTable(Moudle_U,pModule,pModule->m_nVolChCount);

			CString strLable;
			strLable.Format(_T("弱信号模块%d"),++nCurCount);
			QLabel *pLabel = new QLabel;
			pLabel->setText(strLable);

			m_LeftChannelTableList.append(pITable);
			m_RightChannelTableList.append(pUTable);
			m_ChTableLableList.append(pLabel);
		}
	}
}

void QAsyncWeekTestParaSet::DCStateChanged( bool bDc )
{
	m_bDc = bDc;

	int nAmpMinCoe = 0; 


	for (int i = 0; i<m_LeftChannelTableList.size();i++)
	{
		m_LeftChannelTableList[i]->setAmpMinCoe(nAmpMinCoe);
		m_LeftChannelTableList[i]->setProperty(bDc);
	}
	for (int i = 0; i<m_RightChannelTableList.size();i++)
	{
		m_RightChannelTableList[i]->setAmpMinCoe(nAmpMinCoe);
		m_RightChannelTableList[i]->setProperty(bDc);
	}

	for (int i = 0; i<m_LeftChannelTableList.size();i++)
	{
		m_LeftChannelTableList[i]->UpdateValidTableDatas();
	}
	for (int i = 0; i<m_RightChannelTableList.size();i++)
	{
		m_RightChannelTableList[i]->UpdateValidTableDatas();
	}
}

void QAsyncWeekTestParaSet::setData( tmt_async_modules *pModules )
{
	if(!pModules)
	{
		return;
	}
	m_pAsyncModules = pModules;
// 	UpdateTableData();
}

void QAsyncWeekTestParaSet::UpdateTableData()
{
	tmt_async_module *pModule = NULL;
	int nLeftIndex = 0, nRightIndex = 0;

	for(int nIndex = 0;nIndex < m_pAsyncModules->m_nWeekCount; nIndex++)
	{		
		pModule = &m_pAsyncModules->m_oWeekModules[nIndex];


		if(pModule->m_nCurrChCount != 0 && pModule->m_nVolChCount==0)
		{	
			int nBeginIndex = 0;
			int nChCount = 0;

			if(pModule->m_nCurrChCount >= 12)
			{
				nChCount = pModule->m_nCurrChCount/2;
			}
			QAsyncChannelTable *pLeftTable = m_LeftChannelTableList.at(nLeftIndex);
			QAsyncChannelTable *pRightTable = m_RightChannelTableList.at(nRightIndex);

			nLeftIndex++;
			nRightIndex++;

			pLeftTable->setTableData(pModule,nChCount,nBeginIndex);
			pRightTable->setTableData(pModule,nChCount,nBeginIndex+nChCount);

		}
		else if(pModule->m_nCurrChCount == 0 && pModule->m_nVolChCount!=0)
		{
			int nBeginIndex = 0;
			int nChCount = 0;

			if(pModule->m_nVolChCount >= 12)
			{
				nChCount = pModule->m_nVolChCount/2;
			}
			QAsyncChannelTable *pLeftTable = m_LeftChannelTableList.at(nLeftIndex);
			QAsyncChannelTable *pRightTable = m_RightChannelTableList.at(nRightIndex);

			nLeftIndex++;
			nRightIndex++;

			pLeftTable->setTableData(pModule,nChCount,nBeginIndex);
			pRightTable->setTableData(pModule,nChCount,nBeginIndex+nChCount);

		}
		else if(pModule->m_nCurrChCount != 0 && pModule->m_nVolChCount!=0)
		{
			QAsyncChannelTable *pITable = m_LeftChannelTableList.at(nLeftIndex);
			QAsyncChannelTable *pUTable = m_RightChannelTableList.at(nRightIndex);

			nLeftIndex++;
			nRightIndex++;

			pITable->setTableData(pModule,pModule->m_nCurrChCount);
			pUTable->setTableData(pModule,pModule->m_nVolChCount);
			

		}

	}
}

void QAsyncWeekTestParaSet::slot_ChannelValueChanged()
{
	emit sig_updataParas();
}

void QAsyncWeekTestParaSet::UpdateModulesData( tmt_async_modules *pModules )
{
	if(!pModules)
	{
		return;
	}
	m_pAsyncModules = pModules;

	UpdateTableData();
}

void QAsyncWeekTestParaSet::startInit()
{
// 	for(int nIndex = 0;nIndex < m_RightChannelTableList.size(); nIndex++)
// 	{
// 		m_RightChannelTableList[nIndex]->setDisabled(true);
// 	}
// 	for(int nIndex = 0;nIndex < m_LeftChannelTableList.size(); nIndex++)
// 	{
// 		m_LeftChannelTableList[nIndex]->setDisabled(true);
// 	}
	IsTestInProgress(true);
}

void QAsyncWeekTestParaSet::stopInit()
{
// 	for(int nIndex = 0;nIndex < m_RightChannelTableList.size(); nIndex++)
// 	{
// 		m_RightChannelTableList[nIndex]->setDisabled(FALSE);
// 	}
// 	for(int nIndex = 0;nIndex < m_LeftChannelTableList.size(); nIndex++)
// 	{
// 		m_LeftChannelTableList[nIndex]->setDisabled(FALSE);
// 	}
	IsTestInProgress(false);
}

void QAsyncWeekTestParaSet::IsTestInProgress( bool b )
{
	for(int nIndex = 0;nIndex < m_RightChannelTableList.size(); nIndex++)
	{
		m_RightChannelTableList[nIndex]->IsTestInProgress(b);
	}
	for(int nIndex = 0;nIndex < m_LeftChannelTableList.size(); nIndex++)
	{
		m_LeftChannelTableList[nIndex]->IsTestInProgress(b);
	}
}
