#include "PowerManualGridImp.h"


QPowerManualGridImp::QPowerManualGridImp(QWidget *parent)
	: QParaSetBase(parent)
{
	m_pMainGridLayout = new QGridLayout(this);
	m_pUScrollArea = new QScrollArea(this);
	m_pIScrollArea = new QScrollArea(this);
	m_pUWidget = new QWidget(m_pUScrollArea);
	m_pIWidget = new QWidget(m_pIScrollArea);
	m_pUWidget = new QWidget(this);
	m_pIWidget = new QWidget(this);
	m_pUScrollArea->setWidget(m_pUWidget);
	m_pIScrollArea->setWidget(m_pIWidget);
	m_pUVGridLayout = new QGridLayout(m_pUWidget);
	m_pIVGridLayout = new QGridLayout(m_pIWidget);
	m_pnHarmIndex = NULL;
	/*m_tabWidget = new QSttTabWidget(this);
	m_pMainGridLayout->addWidget(m_tabWidget);

	m_tabWidget->insertTab(0,m_pUWidget,_T("电压短时过量"));
	m_tabWidget->insertTab(1,m_pIWidget,_T("电流短时过量"));*/

	m_pArrUIVOL = NULL;
	m_pArrPOW = NULL;
	m_pArrPOW = NULL;
	m_pParaSetSttTestResource = NULL;
	m_MacroType = 0;
	m_type = P_Common;
}

QPowerManualGridImp::~QPowerManualGridImp()
{
	delete m_pUVGridLayout;
	delete m_pIVGridLayout;
	delete m_pUWidget;
	delete m_pIWidget;
	delete m_pMainGridLayout;
}

void QPowerManualGridImp::DCStateChanged(int type,bool bdc)
{
	if (type == m_type)
	{
		for (int i = 0; i<m_UCHannelTableList.size();i++)
		{
			m_UCHannelTableList[i]->setProperty(bdc);
			m_UCHannelTableList[i]->UpdateValidTableDatas();
		}
		for (int i = 0; i<m_ICHannelTableList.size();i++)
		{
			m_ICHannelTableList[i]->setProperty(bdc);
			m_ICHannelTableList[i]->UpdateValidTableDatas();
		}
	}
}

void QPowerManualGridImp::setUAmpMaxMinValue()
{
	int num = 0;
	num = m_UCHannelTableList.size();
	for (int i=0; i<num; i++)
	{
		if ( isCommon() || isHarm())
		{
			if((m_pArrUIVOL[0].Harm[1].bDC)&&
				((m_MacroType != MACROTYPE_ManualHarm)&&(m_MacroType != MACROTYPE_ManualSequence)&&(m_MacroType != MACROTYPE_ManualLineVol)))
			{
				m_UCHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fDC_VolMax,g_oLocalSysPara.m_fDC_VolMax*(-1));
			}
			else
			{
				m_UCHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fAC_VolMax,0);
			}
		}
	}
}

void QPowerManualGridImp::setIAmpMaxMinValue()
{
	//int num = 0;
	//num = m_ICHannelTableList.size();
	//for (int i =0; i<num; i++)
	//{
	//	if (isCommon()|| isHarm())
	//	{
	//		if ((m_pArrUIVOL[0].Harm[1].bDC)&&
	//			((m_MacroType != MACROTYPE_ManualHarm)&&(m_MacroType !=MACROTYPE_ManualSequence)&&(m_MacroType !=MACROTYPE_ManualLineVol)))
	//		{
	//			m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fDC_CurMax,g_oLocalSysPara.m_fDC_CurMax*(-1));
	//		}
	//		else
	//		{
	//			m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fAC_CurMax,0);
	//		}
	//	}
	//}
	//wangtao 20240612 功率最大值最小值设置
	m_ICHannelTableList[0]->setAmpMaxMinValue(g_oLocalSysPara.m_fDC_VolMax*g_oLocalSysPara.m_fAC_CurMax,g_oLocalSysPara.m_fDC_VolMax*g_oLocalSysPara.m_fAC_CurMax*(-1));
}

void QPowerManualGridImp::setUAmpEDValue(float fUEDVal)
{
	int num = 0;
	num = m_UCHannelTableList.size();

	for (int i =0; i<num; i++)
	{
		m_UCHannelTableList[i]->setAmpEDValue(fUEDVal);
	}
}

void QPowerManualGridImp::setIAmpEDValue(float fIEDVal)
{
	int num = 0;
	num = m_ICHannelTableList.size();

	for (int i =0; i<num; i++)
	{
		m_ICHannelTableList[i]->setAmpEDValue(fIEDVal);
	}
}

//递变槽
void QPowerManualGridImp::setChannelTableItemValue_Sequence(QString str,float fstep,int valueFlag,int AddOrMinus)
{
	float fv;
	int nChIndex;
	bool bP = false;
	ASSERT(m_pParaSetSttTestResource != NULL);

	if (str.contains(_T("P")))
	{
		bP = true;
		nChIndex = m_pParaSetSttTestResource->GetChIndexPowerByChName(str,TRUE);
	}
	else if (str.contains(_T("Q")))
	{
		bP = false;
		nChIndex = m_pParaSetSttTestResource->GetChIndexPowerByChName(str,TRUE);
	}
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("递变通道名【%s】非法"),str);
		//Qt编译报错 sf 20220107
		return;
	}

	if (nChIndex !=3)
	{
		if (bP)
		{
			fv=m_ICHannelTableList[0]->getItemValue(nChIndex,1);
			if (fv<0)
			{
				fv = fv-fstep*AddOrMinus;
			}
			else
			{
                fv = fv+fstep*AddOrMinus;
			}
			m_ICHannelTableList[0]->setItemValue(nChIndex,1,fv);
		}
		else
		{
			fv =m_ICHannelTableList[0]->getItemValue(nChIndex,2);
			if (fv<0)
			{
				fv = fv-fstep*AddOrMinus;
			}
			else
			{
				fv = fv+fstep*AddOrMinus;
			}
			m_ICHannelTableList[0]->setItemValue(nChIndex,2,fv);
		}
	}
	else
	{
		for (int i = 0;i<3;i++)
		{
			if (bP)
			{
				fv=m_ICHannelTableList[0]->getItemValue(i,1);
				if (fv<0)
				{
					fv = fv-fstep*AddOrMinus/3;
				}
				else
				{
					fv = fv+fstep*AddOrMinus/3;
				}
				m_ICHannelTableList[0]->setItemValue(i,1,fv);
			}
			else
			{
				fv =m_ICHannelTableList[0]->getItemValue(i,2);

				if (fv<0)
				{
					fv = fv-fstep*AddOrMinus/3;
				}
				else
				{
					fv = fv+fstep*AddOrMinus/3;
				}
				m_ICHannelTableList[0]->setItemValue(i,2,fv);
			}
		}
	}
}

//递变槽
void QPowerManualGridImp::setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC)
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
				if (!bDC)
				{
					if (fv<=0)
					{
						fv = 0;
					}
				}
				m_UCHannelTableList[0]->setItemValue(nChIndex,1,fv);
			}
			else
			{
				fv =m_ICHannelTableList[0]->getItemValue(nChIndex,1);
				fv = fv+fstep*AddOrMinus;
				if (!bDC)
				{
					if (fv<=0)
					{
						fv = 0;
					}
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

void QPowerManualGridImp::initUI(CSttTestResourceBase *pSttTestResource)
{
	QParaSetBase::initUI(pSttTestResource);

	if (m_pParaSetSttTestResource == NULL)
	{
		return;
	};

	QChannelTable *pVolChTable = NULL;
	QChannelPowerTable	*pPowChTable = NULL;

#ifdef _PSX_QT_WINDOWS_
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	QFont oFont;
	oFont.setPixelSize(12);
#endif

	pVolChTable = new QChannelTable(Moudle_U,&m_pParaSetSttTestResource->m_oVolChRsListRef,m_pArrUIVOL,m_pUWidget);
	pPowChTable = new QChannelPowerTable(Moudle_I,&m_pParaSetSttTestResource->m_oCurChRsListRef,m_pArrPOW,m_pIWidget);//2023/12/1 wangjunsheng 改为IWidget
	pVolChTable->setHarmIndex(m_pnHarmIndex);
	pPowChTable->setHarmIndex(m_pnHarmIndex);
	pVolChTable->setFont(*g_pSttGlobalFont);
	pPowChTable->setFont(*g_pSttGlobalFont);
#ifdef _PSX_QT_WINDOWS_
	// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("当前屏幕宽度(%ld),高度(%ld)."),
	// 			rect.width(),rect.height());
	if (rect.width()<=1024)//20230712 suyang 适配6.4合并单元分辨率 1024X768
	{
		pVolChTable->horizontalHeader()->setFont(oFont);
		pPowChTable->horizontalHeader()->setFont(oFont);
	}
	else
	{
		pVolChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pPowChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	}
#else
		pVolChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pPowChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
#endif


	if (pVolChTable)
	{
		pVolChTable->setMacroType(m_MacroType);
		pVolChTable->m_bDC = m_bDC;
		pVolChTable->initTable();
	}

	if (pPowChTable)
	{
		pPowChTable->setMacroType(m_MacroType);
		pPowChTable->m_bDC = m_bDC;
		pPowChTable->initTable();
	}

	m_UCHannelTableList.append(pVolChTable);
	m_ICHannelTableList.append(pPowChTable);

	for (int i = 0; i<m_UCHannelTableList.size();i++)
	{
		connect(m_UCHannelTableList[i],SIGNAL(sig_ChannelValueChanged(MOUDLEType,int,int,float)),this,SLOT(slot_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)));
	}
	for (int i = 0; i<m_ICHannelTableList.size();i++)
	{
		connect(m_ICHannelTableList[i],SIGNAL(sig_ChannelValueChanged(MOUDLEType,int,int,float)),this,SLOT(slot_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)));
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

	m_pUScrollArea->setWidgetResizable(true);
	m_pUScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pUScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	if(m_UCHannelTableList.size() > 1)
	{
		m_pUVGridLayout->setRowStretch(m_UCHannelTableList.size(),1);
		m_pUScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);	
	}

	m_pIScrollArea->setWidgetResizable(true);
	m_pIScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pIScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	if(m_ICHannelTableList.size() > 1)
	{
		m_pIVGridLayout->setRowStretch(m_ICHannelTableList.size(),1);
		m_pIScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	}

	m_pMainGridLayout->addWidget(m_pUScrollArea,0,0);
	m_pMainGridLayout->addWidget(m_pIScrollArea,0,1);
}

void QPowerManualGridImp::initData()
{
	if ((m_pParaSetSttTestResource == NULL)||(m_pArrUIVOL == NULL)||(m_pArrPOW == NULL))
	{
		return;
	}

	if (m_UCHannelTableList.size()>=1)
	{
		m_UCHannelTableList[0]->setTableData(m_pArrUIVOL);
	}

	if (m_ICHannelTableList.size()>=1)
	{
		m_ICHannelTableList[0]->setTableData(m_pArrPOW);
	}
}

void QPowerManualGridImp::Release()
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
		QChannelPowerTable *p = m_ICHannelTableList.at(i);
		delete p;
		p = NULL;
	}
	m_ICHannelTableList.clear();
}

void QPowerManualGridImp::UpdateTables()
{
	int i = 0;
	for (i = 0; i< m_UCHannelTableList.size(); i++)
	{
		QChannelTable *p = m_UCHannelTableList.at(i);
		p->UpdateTable();
	}

	for (i = 0; i< m_ICHannelTableList.size(); i++)
	{
		QChannelPowerTable *p = m_ICHannelTableList.at(i);
		p->UpdateTable();
	}
}

void QPowerManualGridImp::UpdateValidTableDatas()
{
	int nIndex = 0;
	QChannelTable *pUChTable = NULL;
	 QChannelPowerTable *pPowerChTable = NULL;

	for (nIndex = 0; nIndex< m_UCHannelTableList.size(); nIndex++)
	{
		pUChTable = m_UCHannelTableList.at(nIndex);
		pUChTable->UpdateValidTableDatas();
	}

	for (nIndex = 0; nIndex< m_ICHannelTableList.size(); nIndex++)
	{
		pPowerChTable = m_ICHannelTableList.at(nIndex);
		pPowerChTable->UpdateValidTableDatas();
	}
}

void QPowerManualGridImp::setHarmIndex(int *pnHarmIndex)
{
	m_pnHarmIndex = pnHarmIndex;
	int nIndex = 0;
	QChannelTable *pUChTable = NULL;
    QChannelPowerTable *pPowerChTable = NULL;

	for (nIndex = 0; nIndex< m_UCHannelTableList.size(); nIndex++)
	{
		pUChTable = m_UCHannelTableList.at(nIndex);
		pUChTable->setHarmIndex(pnHarmIndex);
	}

	for (nIndex = 0; nIndex< m_ICHannelTableList.size(); nIndex++)
	{
		pPowerChTable = m_ICHannelTableList.at(nIndex);
		pPowerChTable->setHarmIndex(pnHarmIndex);
	}
}

void QPowerManualGridImp::setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource,
										tmt_channel *pArrUIVOL,tmt_ChannelPower *pArrPOW,bool bDC)
{
	ASSERT(pSttTestResource);
	ASSERT( pArrUIVOL != NULL);
	ASSERT( pArrPOW != NULL);

	m_type = type;
	m_pArrUIVOL = pArrUIVOL;
	m_pArrPOW = pArrPOW;
	m_pParaSetSttTestResource = pSttTestResource;
	m_bDC = bDC;

	initUI(pSttTestResource);
	initData();
}