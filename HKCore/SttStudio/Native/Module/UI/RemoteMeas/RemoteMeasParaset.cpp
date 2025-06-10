#include "RemoteMeasParaset.h"
#include <QDebug>
extern QFont *g_pSttGlobalFont;

RemoteMeasParaSet::RemoteMeasParaSet(QWidget *parent)
	: QWidget(parent)
{
	m_pMainGridLayout = new QGridLayout(this);
	m_pUScrollArea = new QScrollArea(this);
	m_pIScrollArea = new QScrollArea(this);
	m_pRemoteMeasScrollArea = new QScrollArea(this);
	m_pUWidget = new QWidget(m_pUScrollArea);
	m_pIWidget = new QWidget(m_pIScrollArea);
	m_pRemoteMeasWidget = new QWidget(m_pRemoteMeasScrollArea);
	m_pUScrollArea->setWidget(m_pUWidget);
	m_pIScrollArea->setWidget(m_pIWidget);
	m_pRemoteMeasScrollArea->setWidget(m_pRemoteMeasWidget);
	m_pUVGridLayout = new QGridLayout(m_pUWidget);
	m_pIVGridLayout = new QGridLayout(m_pIWidget);
	m_pRemoteMeasGridLayout = new QGridLayout(m_pRemoteMeasWidget);

	m_pArrUIVOL = NULL;
	m_pArrUICUR = NULL;
	m_pParaSetSttTestResource = NULL;
	m_MacroType = -1;
	m_bDC = false;
}

RemoteMeasParaSet::~RemoteMeasParaSet()
{
	Release();
	delete m_pUVGridLayout;
	delete m_pIVGridLayout;
	delete m_pRemoteMeasGridLayout;
	delete m_pUWidget;
	delete m_pIWidget;
	delete m_pRemoteMeasWidget;
	delete m_pUScrollArea;
	delete m_pIScrollArea;
	delete m_pRemoteMeasScrollArea;
	delete m_pMainGridLayout;
}

void RemoteMeasParaSet::Release()
{
	for (int i = 0; i< m_UCHannelTableList.size(); i++)
	{
		QChannelTable *p = m_UCHannelTableList.at(i);
		delete p;
		p = NULL;
	}
	m_UCHannelTableList.clear();

	for (int i = 0; i< m_ICHannelTableList.size(); i++)
	{
		QChannelTable *p = m_ICHannelTableList.at(i);
		delete p;
		p = NULL;
	}
	m_ICHannelTableList.clear();

	for (int i = 0; i< m_RemoteMeasTableList.size(); i++)
	{
		QRemoteMeasTable *p = m_RemoteMeasTableList.at(i);
		delete p;
		p = NULL;
	}
	m_RemoteMeasTableList.clear();
}

void RemoteMeasParaSet::initUI(CSttTestResourceBase *pSttTestResource)
{
	Release();

	if (pSttTestResource != NULL)
	{
		m_pParaSetSttTestResource = pSttTestResource;
	}

	if (m_pParaSetSttTestResource == NULL)
	{
		return;
	};

	QChannelTable *pVolChTable = NULL,*pCurChTable = NULL;
	QRemoteMeasTable *pTelemeterTable = NULL;

	pVolChTable = new QChannelTable(Moudle_U,&m_pParaSetSttTestResource->m_oVolChRsListRef,m_pArrUIVOL,m_pUWidget);
	pCurChTable = new QChannelTable(Moudle_I,&m_pParaSetSttTestResource->m_oCurChRsListRef,m_pArrUICUR,m_pUWidget);
	pTelemeterTable = new QRemoteMeasTable(&m_pParaSetSttTestResource->m_oVolChRsListRef,&m_pParaSetSttTestResource->m_oCurChRsListRef,
		m_pArrUIVOL,m_pArrUICUR,m_pRemoteMeasWidget);

	pVolChTable->setFont(*g_pSttGlobalFont);
	pCurChTable->setFont(*g_pSttGlobalFont);
	pTelemeterTable->setFont(*g_pSttGlobalFont);

	pVolChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	pCurChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	pTelemeterTable->horizontalHeader()->setFont(*g_pSttGlobalFont);

	if (pVolChTable)
	{
		pVolChTable->setMacroType(m_MacroType);
		pVolChTable->m_bDC = m_bDC;
		pVolChTable->initTable();
	}

	if (pCurChTable)
	{
		pCurChTable->setMacroType(m_MacroType);
		pCurChTable->m_bDC = m_bDC;
		pCurChTable->initTable();
	}

	if (pTelemeterTable)
	{
		pTelemeterTable->m_bDC = m_bDC;
		pTelemeterTable->InitTable();
	}

	m_UCHannelTableList.append(pVolChTable);
	m_ICHannelTableList.append(pCurChTable);
	m_RemoteMeasTableList.append(pTelemeterTable);

	for (int i = 0; i<m_UCHannelTableList.size();i++)
	{
		connect(m_UCHannelTableList[i],SIGNAL(sig_ChannelValueChanged(MOUDLEType,int,int,float)),this,SLOT(slot_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)));
	}
	for (int i = 0; i<m_ICHannelTableList.size();i++)
	{
		connect(m_ICHannelTableList[i],SIGNAL(sig_ChannelValueChanged(MOUDLEType,int,int,float)),this,SLOT(slot_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)));
	}
	for (int i = 0; i<m_RemoteMeasTableList.size();i++)
	{
		connect(m_RemoteMeasTableList[i],SIGNAL(sig_ChannelRemoteValueChanged(int,int,float)),this,SLOT(slot_ChannelRemoteValueChanged(int,int,float)));
	}

	//chenling20240314
	for (int i = 0; i<m_RemoteMeasTableList.size();i++)
	{
		connect(this,SIGNAL(sig_ChannelAmpValueChanged(int,float)),m_RemoteMeasTableList[i],SLOT(slot_ChannelAmpValueChanged(int,float)));
	}


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

	int nTWidgetHeight = 0;
	int nTWidgetWidth = 0;
	for (int i = 0; i < m_RemoteMeasTableList.size(); i++)
	{
		nTWidgetWidth = m_RemoteMeasTableList[i]->getTableWidth();
		nTWidgetHeight += m_RemoteMeasTableList[i]->getTableHeight();
		m_pRemoteMeasGridLayout->addWidget(m_RemoteMeasTableList.at(i),i,0,1,1);
	}

	m_pRemoteMeasWidget->setMinimumHeight(nTWidgetHeight);	
	m_pRemoteMeasGridLayout->setMargin(0);
	m_pRemoteMeasGridLayout->setSpacing(0);
	m_pRemoteMeasWidget->setLayout(m_pRemoteMeasGridLayout);

	m_pUScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pUScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pIScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pIScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pRemoteMeasScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pRemoteMeasScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	m_pUScrollArea->setWidgetResizable(true);
	m_pIScrollArea->setWidgetResizable(true);
	m_pRemoteMeasScrollArea->setWidgetResizable(true);

	m_pMainGridLayout->addWidget(m_pUScrollArea,0,0);
	m_pMainGridLayout->addWidget(m_pIScrollArea,1,0);
	m_pMainGridLayout->addWidget(m_pRemoteMeasScrollArea,0,1,2,1);

	if(m_RemoteMeasTableList.size() > 1)
	{
		m_pRemoteMeasScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		m_pRemoteMeasGridLayout->setRowStretch(m_RemoteMeasTableList.size(),1);
	}

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

void RemoteMeasParaSet::initData()
{
	if ((m_pParaSetSttTestResource == NULL)||(m_pArrUIVOL == NULL)||(m_pArrUICUR == NULL))
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

	if (m_RemoteMeasTableList.size()>=1)
	{
		m_RemoteMeasTableList[0]->setTableData(m_pArrUIVOL,m_pArrUICUR);
	}
}

void RemoteMeasParaSet::UpdateValidTableDatas()
{
	int nIndex = 0;
	QChannelTable *pCurrChTable = NULL;
	QRemoteMeasTable *pCurrTelTable = NULL;

	for (nIndex = 0; nIndex< m_UCHannelTableList.size(); nIndex++)
	{
		pCurrChTable = m_UCHannelTableList.at(nIndex);
		pCurrChTable->UpdateValidTableDatas();
	}

	for (nIndex = 0; nIndex< m_ICHannelTableList.size(); nIndex++)
	{
		pCurrChTable = m_ICHannelTableList.at(nIndex);
		pCurrChTable->UpdateValidTableDatas();
	}

	for (nIndex = 0; nIndex< m_RemoteMeasTableList.size(); nIndex++)
	{
		pCurrTelTable = m_RemoteMeasTableList.at(nIndex);
		pCurrTelTable->UpdateValidTableDatas();
	}
}

void RemoteMeasParaSet::setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
											,tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR,bool bDC)
{
	ASSERT(pSttTestResource);
	ASSERT( pArrUIVOL != NULL);
	ASSERT( pArrUICUR != NULL);

	m_type = type;
	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;

	m_pParaSetSttTestResource = pSttTestResource;
	m_bDC = bDC;

	initUI(pSttTestResource);
	initData();
}

void RemoteMeasParaSet::setData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR)
{
	ASSERT( pArrUIVOL != NULL);
	ASSERT( pArrUICUR != NULL);

	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;
}

void RemoteMeasParaSet::setMaxMinAndEDVal()
{
	setUAmpMaxMinValue();
	setIAmpMaxMinValue();

	setUAmpEDValue(g_oSystemParas.m_fVNom);
	setIAmpEDValue(g_oSystemParas.m_fINom);
}

void RemoteMeasParaSet::setUAmpMaxMinValue()
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
// 			float fVolMax;
// 			if (g_oSystemParas.m_nHasWeek) // 弱信号相电压4.2 零序8.3
// 			{
// 				fVolMax = 4.2;
// 				m_UCHannelTableList[i]->setAmpMaxMinValue(fVolMax,0);
// 			}
// 			else 
			{
			m_UCHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fAC_VolMax,0);
			}
		}
	}
}

void RemoteMeasParaSet::setIAmpMaxMinValue()
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
// 			float fCurMax;
// 			if (g_oSystemParas.m_nHasWeek) //弱信号相电流21 零序4.2
// 			{
// 				fCurMax = 21;
// 				m_ICHannelTableList[i]->setAmpMaxMinValue(fCurMax,0);
// 			}
// 			else 
			{
			m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fAC_CurMax,0);
			}
		}
	}
}

void RemoteMeasParaSet::setUAmpEDValue(float fUEDVal)
{
	int num = 0;
	num = m_UCHannelTableList.size();

	for (int i =0; i<num; i++)
	{
		m_UCHannelTableList[i]->setAmpEDValue(fUEDVal);
	}
}

void RemoteMeasParaSet::setIAmpEDValue(float fIEDVal)
{
	int num = 0;
	num = m_ICHannelTableList.size();

	for (int i =0; i<num; i++)
	{
		m_ICHannelTableList[i]->setAmpEDValue(fIEDVal);
	}
}

void RemoteMeasParaSet::setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus)
{
	float fv;
	int nChIndex;
	bool bU = false;
	ASSERT(m_pParaSetSttTestResource != NULL);

	if (str.contains(_T("U")))
	{
		bU = true;
		nChIndex = m_pParaSetSttTestResource->m_oVolChRsListRef.FindIndexByName(str);

	}
	else if (str.contains(_T("I")))
	{
		bU = false;
		nChIndex = m_pParaSetSttTestResource->m_oCurChRsListRef.FindIndexByName(str);

	}
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("递变通道名【%s】非法"),str);
		//Qt编译报错 sf 20220107
		return;
	}

	switch (valueFlag)
	{					
	case amplitude_type:	
		{
			if (bU)
			{
				fv=m_UCHannelTableList[0]->getItemValue(nChIndex,1);
				fv = fv+fstep*AddOrMinus;
				
				if (fv<=0)
				{
					fv = 0;
				}
				m_UCHannelTableList[0]->setItemValue(nChIndex,1,fv);
			}
			else
			{
				fv =m_ICHannelTableList[0]->getItemValue(nChIndex,1);
				fv = fv+fstep*AddOrMinus;
				
				if (fv<=0)
				{
					fv = 0;
				}
				m_ICHannelTableList[0]->setItemValue(nChIndex,1,fv);
			}
		}
		break;
	case phasor_type:
		{
			if (bU)
			{
				fv =m_UCHannelTableList[0]->getItemValue(nChIndex,2);
				fv = fv+fstep*AddOrMinus;
				m_UCHannelTableList[0]->setItemValue(nChIndex,2,fv);
			}
			else
			{
				fv =m_ICHannelTableList[0]->getItemValue(nChIndex,2);
				fv = fv+fstep*AddOrMinus;
				m_ICHannelTableList[0]->setItemValue(nChIndex,2,fv);
			}
		}
		break;
	case fre_type:
		{
			if (bU)
			{
				fv =m_UCHannelTableList[0]->getItemValue(nChIndex,3);
				fv = fv+fstep*AddOrMinus;
				if (fv<0)
				{
					fv = 0;
				}
				m_UCHannelTableList[0]->setItemValue(nChIndex,3,fv);
			}
			else
			{
				fv =m_ICHannelTableList[0]->getItemValue(nChIndex,3);
				fv = fv+fstep*AddOrMinus;
				if (fv<0)
				{
					fv = 0;
				}
				m_ICHannelTableList[0]->setItemValue(nChIndex,3,fv);
			}
		}
		break;
	default:
		break;
	}
}

void RemoteMeasParaSet::UpdateTables()
{
	int i = 0;
	for (i = 0; i< m_UCHannelTableList.size(); i++)
	{
		QChannelTable *p = m_UCHannelTableList.at(i);
		p->UpdateTable();
	}

	for (i = 0; i< m_ICHannelTableList.size(); i++)
	{
		QChannelTable *p = m_ICHannelTableList.at(i);
		p->UpdateTable();
	}

	for (i = 0; i< m_RemoteMeasTableList.size(); i++)
	{
		QRemoteMeasTable *p = m_RemoteMeasTableList.at(i);
		p->UpdateTable();
	}
}

void RemoteMeasParaSet::startInit(bool bEnable)
{
	setDisabled(!bEnable);
}

void RemoteMeasParaSet::stopInit(bool bEnable)
{
	setDisabled(!bEnable);
}

void RemoteMeasParaSet::slot_ChannelValueChanged(MOUDLEType moudleType,int channelNum,int valueFlag,float datavalue)
{
	initData();
	Send_UpdataParas();
	if (moudleType == Moudle_U) 
	{
		if(channelNum == 0 || channelNum == 2)
		{
		emit sig_ChannelAmpValueChanged(channelNum,datavalue);
		}
	}
	
}

void RemoteMeasParaSet::slot_ChannelRemoteValueChanged(int channelNum,int valueFlag,float datavalue)
{
	Send_UpdataParas();
}

void RemoteMeasParaSet::Send_UpdataParas()
{
	emit sig_updataParas();
}