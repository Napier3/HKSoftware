#include "AnalogCirBreakerParaset.h"
#include "../SttTestCntrFrameBase.h"

AnalogCirBreakerParaset::AnalogCirBreakerParaset(QWidget *parent)
	 : QParaSetBase(parent)
{
	m_pArrUICUR = NULL;
	m_pParaSetSttTestResource = NULL;
	m_MacroType = -1;
	m_bDC = false;
	InitUI();
}

AnalogCirBreakerParaset::~AnalogCirBreakerParaset()
{
	Release();
}

void AnalogCirBreakerParaset::Release()
{
	for (int i = 0; i< m_ICHannelTableList.size(); i++)
	{
		QChannelTable *p = m_ICHannelTableList.at(i);
		delete p;
		p = NULL;
	}
	m_ICHannelTableList.clear();
}
void AnalogCirBreakerParaset::InitUI()
{
	m_pIScrollArea = new QScrollArea(this);
	m_pIWidget = new QWidget(m_pIScrollArea);
	m_pIScrollArea->setWidget(m_pIWidget);
	m_pIGridLayout = new QGridLayout(m_pIWidget);

	m_pIGridLayout->setMargin(0);
	m_pIWidget->setLayout(m_pIGridLayout);
	m_pIScrollArea->setWidgetResizable(true);

	CString strText;
	m_pIGroupBox = new QGroupBox;
	strText = _T("电流设置");
	m_pIGroupBox->setTitle(strText);
	m_pIGroupBox->setFont(*g_pSttGlobalFont);
	QVBoxLayout *pGroupBoxLayout = new QVBoxLayout;
	pGroupBoxLayout->addWidget(m_pIScrollArea);
	m_pIGroupBox->setLayout(pGroupBoxLayout);

	m_pMainHBoxLayout = new QHBoxLayout;
	m_pMainHBoxLayout->addWidget(m_pIGroupBox);
}

void AnalogCirBreakerParaset::initUI(CSttTestResourceBase *pSttTestResource)
{
	Release();

	if (pSttTestResource != NULL)
	{
		m_pParaSetSttTestResource = pSttTestResource;
	}

	if (m_pParaSetSttTestResource == NULL)
	{
		return;
	}

	

	QChannelTable *pCurChTable = NULL;
	pCurChTable = new QChannelTable(Moudle_I,&m_pParaSetSttTestResource->m_oCurChRsListRef,m_pArrUICUR,m_pIWidget);
	pCurChTable->setFont(*g_pSttGlobalFont);
	pCurChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);

	if (pCurChTable)
	{
		pCurChTable->setMacroType(m_MacroType);
		pCurChTable->m_bDC = m_bDC;
		pCurChTable->initTable();
	}

	m_ICHannelTableList.append(pCurChTable);
	int nIWidgetHeight = 0;
	int nIWidgetWidth = 0;
	for (int i = 0; i<m_ICHannelTableList.size();i++)
	{
		nIWidgetWidth = m_ICHannelTableList[i]->getTableWidth();
		nIWidgetHeight += m_ICHannelTableList[i]->getTableHeight();
		m_pIGridLayout->addWidget(m_ICHannelTableList.at(i),i,0,1,1);
		connect(m_ICHannelTableList[i],SIGNAL(sig_ChannelValueChanged(MOUDLEType,int,int,float)),this,SLOT(slot_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)));
	}
	
	m_pIWidget->setMinimumHeight(nIWidgetHeight);	
}

void AnalogCirBreakerParaset::initData()
{
	if ((m_pParaSetSttTestResource == NULL)||(m_pArrUICUR == NULL))
	{
		return;
	}

	if (m_ICHannelTableList.size()>=1)
	{
		m_ICHannelTableList[0]->setTableData(m_pArrUICUR,true);
	}
}

void AnalogCirBreakerParaset::UpdateValidTableDatas()
{
	int nIndex = 0;
	QChannelTable *pCurrChTable = NULL;


	for (nIndex = 0; nIndex< m_ICHannelTableList.size(); nIndex++)
	{
		pCurrChTable = m_ICHannelTableList.at(nIndex);
		pCurrChTable->UpdateValidTableDatas();
	}
}

void AnalogCirBreakerParaset::setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
											,tmt_channel *pArrUICUR,bool bDC)
{
	ASSERT(pSttTestResource);
	ASSERT( pArrUICUR != NULL);

	m_type = type;
	m_pArrUICUR = pArrUICUR;

	m_pParaSetSttTestResource = pSttTestResource;
	m_bDC = bDC;

	initUI(pSttTestResource);
	initData();
}

void AnalogCirBreakerParaset::setData(tmt_channel *pArrUICUR)
{
	ASSERT( pArrUICUR != NULL);

	m_pArrUICUR = pArrUICUR;
}

void AnalogCirBreakerParaset::setMaxMinAndEDVal(bool bCanUpdateTable)
{
	setIAmpMaxMinValue(bCanUpdateTable);
	setIAmpEDValue(g_oSystemParas.m_fINom);
}


void AnalogCirBreakerParaset::setIAmpMaxMinValue(bool bCanUpdateTable)
{
	int num = 0;
	num = m_ICHannelTableList.size();
	for (int i =0; i<num; i++)
	{
		if (m_pArrUICUR[0].Harm[1].bDC)
		{
			m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fDC_CurMax ,0,bCanUpdateTable);
		}
		else
		{
// 			float fCurMax;
// 			if (g_oSystemParas.m_nHasWeek) //弱信号相电流21 零序4.2
// 			{
// 				fCurMax = 21;
// 				m_ICHannelTableList[i]->setAmpMaxMinValue(fCurMax,0);
// 			}
// 			else 
			{
				m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fAC_CurMax,0,bCanUpdateTable);
			}
		}
	}
}



void AnalogCirBreakerParaset::setIAmpEDValue(float fIEDVal)
{
	int num = 0;
	num = m_ICHannelTableList.size();

	for (int i =0; i<num; i++)
	{
		m_ICHannelTableList[i]->setAmpEDValue(fIEDVal);
	}
}


void AnalogCirBreakerParaset::startInit(bool bEnable)
{
	setDisabled(!bEnable);
}

void AnalogCirBreakerParaset::stopInit(bool bEnable)
{
	setDisabled(!bEnable);
}

void AnalogCirBreakerParaset::UpdateTables()
{
	int i = 0;

	for (i = 0; i< m_ICHannelTableList.size(); i++)
	{
		QChannelTable *p = m_ICHannelTableList.at(i);
		p->UpdateTable();
	}
}


void AnalogCirBreakerParaset::slot_ChannelValueChanged(MOUDLEType moudleType,int channelNum,int valueFlag,float datavalue)
{
	initData();
	emit sig_updataParas(channelNum,valueFlag,datavalue);
}


