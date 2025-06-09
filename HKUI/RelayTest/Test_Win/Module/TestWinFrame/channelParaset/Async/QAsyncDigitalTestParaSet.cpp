#include "QAsyncDigitalTestParaSet.h"

QAsyncDigitalTestParaSet::QAsyncDigitalTestParaSet( tmt_async_modules *pModules,QWidget *parent /*= 0*/ )
			:QAsyncTestParaSetBase(pModules,parent)
{
// 	m_pMainWin = NULL;
// 	m_pUScrollArea = NULL;
// 	m_pIScrollArea = NULL;
// 	m_pUWidget = NULL;
// 	m_pIWidget = NULL;
// 	m_pScrollWidget = NULL;
// 	m_pVScrollLayout = NULL;
// 	m_pHLayout = NULL;
// 	m_bDc = false;
// 	m_pUTable = NULL;
// 	m_pITable = NULL;
// 	m_pAsyncModules = pModules;


	initData();
	initUI();
}

QAsyncDigitalTestParaSet::~QAsyncDigitalTestParaSet(void)
{
}

void QAsyncDigitalTestParaSet::initUI()
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
	m_pGridLayout->setContentsMargins(10, 10, 5, 10);

	// 初始化水平布局并设置为当前窗体的布局
	m_pMainLayout = new QHBoxLayout;
	this->setLayout(m_pMainLayout);

	CString strLableName = _T("数字模块1");
	m_pLabel = new QLabel;
	m_pLabel->setText(strLableName);
	m_pLabel->setMinimumWidth(90);
	m_pGridLayout->addWidget(m_pLabel,0,0);
	m_pGridLayout->setHorizontalSpacing(0);


	m_pHLayout = new QHBoxLayout();
	m_pHLayout->addWidget(m_pITable);
	m_pHLayout->addWidget(m_pUTable);
	m_pHLayout->setSpacing(25);
	m_pMainWin = new QWidget;
	m_pMainWin->setLayout(m_pHLayout);
	m_pGridLayout->addWidget(m_pMainWin,1,0);

	m_pMainLayout->addWidget(m_pMainScrollArea);
	m_pGridLayout->setHorizontalSpacing(0);



}

void QAsyncDigitalTestParaSet::initData()
{
	if(!m_pAsyncModules)
	{
		return;
	}

	int nCurCount = 0, nVolCount = 0, nMaxCount = 0;
	tmt_async_module *pModule = &m_pAsyncModules->m_oDigitalModules;

	m_pUTable = new QAsyncChannelTable(Moudle_U, pModule, pModule->m_nVolChCount);
	m_pITable = new QAsyncChannelTable(Moudle_I, pModule, pModule->m_nCurrChCount);

	m_pUTable->initTable();
	m_pITable->initTable();

	connect(m_pUTable,SIGNAL(sig_ChannelValueChanged()),this,SLOT(slot_ChannelValueChanged()));
	connect(m_pITable,SIGNAL(sig_ChannelValueChanged()),this,SLOT(slot_ChannelValueChanged()));


}

void QAsyncDigitalTestParaSet::DCStateChanged( bool bDc )
{
	m_bDc = bDc;

	int nAmpMinCoe = 0; 

	m_pUTable->setAmpMinCoe(nAmpMinCoe);
	m_pITable->setAmpMinCoe(nAmpMinCoe);

	m_pUTable->setProperty(bDc);
	m_pITable->setProperty(bDc);
	m_pUTable->UpdateValidTableDatas();
	m_pITable->UpdateValidTableDatas();

}

void QAsyncDigitalTestParaSet::setData( tmt_async_modules *pModules )
{
	if(!pModules)
	{
		return;
	}
	m_pAsyncModules = pModules;
}

void QAsyncDigitalTestParaSet::UpdateTableData()
{
	if(!m_pAsyncModules)
	{
		return;
	}
	tmt_async_module *pModule = &m_pAsyncModules->m_oDigitalModules;
	m_pUTable->setTableData(pModule,pModule->m_nVolChCount);
	m_pITable->setTableData(pModule,pModule->m_nCurrChCount);

}

void QAsyncDigitalTestParaSet::slot_ChannelValueChanged()
{
	emit sig_updataParas();
}

void QAsyncDigitalTestParaSet::UpdateModulesData( tmt_async_modules *pModules )
{
	if(!pModules)
	{
		return;
	}
	m_pAsyncModules = pModules;

	UpdateTableData();
}

void QAsyncDigitalTestParaSet::startInit()
{
// 	m_pUTable->setDisabled(true);
// 	m_pITable->setDisabled(true);
	IsTestInProgress(true);
}

void QAsyncDigitalTestParaSet::stopInit()
{
// 	m_pUTable->setDisabled(FALSE);
// 	m_pITable->setDisabled(FALSE);
	IsTestInProgress(false);
}

void QAsyncDigitalTestParaSet::setChannelTableItemValue( int nMouleIndex,MOUDLEType type,int nChIndex,float fstep,int valueFlag,int AddOrMinus,bool bDC )
{
	float fv;
	QAsyncChannelTable *pTable = NULL;
	int nType = -1;
	
	switch (valueFlag)
	{
	case 0:
		nType = ASYNCTABLE_AMP;
		break;
	case 1:
		nType = ASYNCTABLE_ANGLE;
		break;
	case 2:
		nType = ASYNCTABLE_FREQ;
		break;
	}

	if(type == Moudle_I)
	{
		pTable = m_pITable;
	}
	else if(type == Moudle_U)
	{
		pTable = m_pUTable;
	}

	if(nType == -1 || pTable == NULL)
	{
		return;
	}

	tmt_async_channel *pCh = m_pITable->GetChFromIndex(nChIndex);

	switch (valueFlag)
	{					
	case amplitude_type:	
		{
			fv = pTable->getItemValue(nChIndex,nType);
			fv = fv+fstep*AddOrMinus;
			if (!bDC)
			{
				if (fv<=0)
				{
					fv = 0;
				}
			}
			pTable->setItemValue(nChIndex,nType,fv);
		}
		break;
	case phasor_type:
		{
			fv =pTable->getItemValue(nChIndex,nType);
			fv = fv+fstep*AddOrMinus;
			pTable->setItemValue(nChIndex,nType,fv);
		}
		break;
	case fre_type:
		{
			fv =pTable->getItemValue(nChIndex,nType);
			fv = fv+fstep*AddOrMinus;
			if (fv<0)
			{
				fv = 0;
			}
			pTable->setItemValue(nChIndex,nType,fv);
		}
		break;
	default:
		break;
	}
}

void QAsyncDigitalTestParaSet::IsTestInProgress( bool b )
{
	m_pUTable->IsTestInProgress(b);
	m_pITable->IsTestInProgress(b);
}
