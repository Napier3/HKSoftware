#include "ShortTimeOverGridImp.h"

QShortTimeOverGridImp::QShortTimeOverGridImp(QWidget *parent)
	: QParaSetBase(parent)
{
	m_pMainGridLayout = new QGridLayout(this);
	m_pUWidget = new QWidget(this);
	m_pIWidget = new QWidget(this);
	m_pUVGridLayout = new QGridLayout(m_pUWidget);
	m_pIVGridLayout = new QGridLayout(m_pIWidget);
	m_pnHarmIndex = NULL;
	m_tabWidget = new QSttTabWidget(this);
	m_pMainGridLayout->addWidget(m_tabWidget);

	m_tabWidget->insertTab(0,m_pUWidget,_T("电压短时过量"));
	m_tabWidget->insertTab(1,m_pIWidget,_T("电流短时过量"));
}

QShortTimeOverGridImp::~QShortTimeOverGridImp()
{
	delete m_pUVGridLayout;
	delete m_pIVGridLayout;
	delete m_pUWidget;
	delete m_pIWidget;
	delete m_pMainGridLayout;
}

void QShortTimeOverGridImp::DCStateChanged(int type,bool bdc)
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

void QShortTimeOverGridImp::setUAmpMaxMinValue()
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

void QShortTimeOverGridImp::setIAmpMaxMinValue()
{
	int num = 0;
	num = m_ICHannelTableList.size();
	for (int i =0; i<num; i++)
	{
		if (isCommon()|| isHarm())
		{
			if ((m_pArrUIVOL[0].Harm[1].bDC)&&
				((m_MacroType != MACROTYPE_ManualHarm)&&(m_MacroType !=MACROTYPE_ManualSequence)&&(m_MacroType !=MACROTYPE_ManualLineVol)))
			{
				m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fDC_CurMax,g_oLocalSysPara.m_fDC_CurMax*(-1));
			}
			else
			{
				m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fAC_CurMax,0);
			}
		}
	}
}

void QShortTimeOverGridImp::setUAmpEDValue(float fUEDVal)
{
	int num = 0;
	num = m_UCHannelTableList.size();

	for (int i =0; i<num; i++)
	{
		m_UCHannelTableList[i]->setAmpEDValue(fUEDVal);
	}
}

void QShortTimeOverGridImp::setIAmpEDValue(float fIEDVal)
{
	int num = 0;
	num = m_ICHannelTableList.size();

	for (int i =0; i<num; i++)
	{
		m_ICHannelTableList[i]->setAmpEDValue(fIEDVal);
	}
}

//递变槽
void QShortTimeOverGridImp::setChannelTableItemValue_Sequence(QString str,float fstep,int valueFlag,int AddOrMinus)
{
	float fv;
	int nChIndex;
	bool bU = false;
	ASSERT(m_pParaSetSttTestResource != NULL);

	if (str.contains(_T("U")))
	{
		bU = true;
		if(m_MacroType ==MACROTYPE_ManualLineVol)
		{
			nChIndex = m_pParaSetSttTestResource->GetChIndexLinevoltByChName(str,TRUE);//线电压的通道序号
		}
		else
			nChIndex = m_pParaSetSttTestResource->GetChIndexSequenceByChName(str,TRUE);
	}
	else if (str.contains(_T("I")))
	{
		bU = false;
		if(m_MacroType ==MACROTYPE_ManualLineVol)
		{
			nChIndex = m_pParaSetSttTestResource->GetChIndexLinevoltByChName(str,FALSE);
		}
		else
			nChIndex = m_pParaSetSttTestResource->GetChIndexSequenceByChName(str,FALSE);
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

//递变槽
void QShortTimeOverGridImp::setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC)
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

void QShortTimeOverGridImp::initUI(CSttTestResourceBase *pSttTestResource)
{
	QParaSetBase::initUI(pSttTestResource);

	if (m_pParaSetSttTestResource == NULL)
	{
		return;
	};

	QChannelTable *pVolChTable = NULL,*pCurChTable = NULL;
#ifdef _PSX_QT_WINDOWS_
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	QFont oFont;
	oFont.setPixelSize(12);
#endif

	pVolChTable = new QChannelTable(Moudle_U,&m_pParaSetSttTestResource->m_oVolChRsListRef,m_pArrUIVOL,m_pUWidget);
	pCurChTable = new QChannelTable(Moudle_I,&m_pParaSetSttTestResource->m_oCurChRsListRef,m_pArrUICUR,m_pIWidget);//2023/12/1 wangjunsheng 改为IWidget
	pVolChTable->setHarmIndex(m_pnHarmIndex);
	pCurChTable->setHarmIndex(m_pnHarmIndex);
	pVolChTable->setFont(*g_pSttGlobalFont);
	pCurChTable->setFont(*g_pSttGlobalFont);
#ifdef _PSX_QT_WINDOWS_
	// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("当前屏幕宽度(%ld),高度(%ld)."),
	// 			rect.width(),rect.height());
	if (rect.width()<=1024)//20230712 suyang 适配6.4合并单元分辨率 1024X768
	{
		pVolChTable->horizontalHeader()->setFont(oFont);
		pCurChTable->horizontalHeader()->setFont(oFont);
	}
	else
	{
		pVolChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pCurChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	}
#else
		pVolChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pCurChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
#endif


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

	m_UCHannelTableList.append(pVolChTable);
	m_ICHannelTableList.append(pCurChTable);

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

	if(m_UCHannelTableList.size() > 1)
	{
		m_pUVGridLayout->setRowStretch(m_UCHannelTableList.size(),1);
	}

	if(m_ICHannelTableList.size() > 1)
	{
		m_pIVGridLayout->setRowStretch(m_ICHannelTableList.size(),1);
	}

	/*m_pMainGridLayout->addWidget(m_pUScrollArea,0,0);
	m_pMainGridLayout->addWidget(m_pIScrollArea,0,1);*/
}

void QShortTimeOverGridImp::initData()
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
}

void QShortTimeOverGridImp::Release()
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
}

void QShortTimeOverGridImp::UpdateTables()
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
}

void QShortTimeOverGridImp::UpdateValidTableDatas()
{
	int nIndex = 0;
	QChannelTable *pCurrChTable = NULL;

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
}

void QShortTimeOverGridImp::setHarmIndex(int *pnHarmIndex)
{
	m_pnHarmIndex = pnHarmIndex;
	int nIndex = 0;
	QChannelTable *pCurrChTable = NULL;

	for (nIndex = 0; nIndex< m_UCHannelTableList.size(); nIndex++)
	{
		pCurrChTable = m_UCHannelTableList.at(nIndex);
		pCurrChTable->setHarmIndex(pnHarmIndex);
	}

	for (nIndex = 0; nIndex< m_ICHannelTableList.size(); nIndex++)
	{
		pCurrChTable = m_ICHannelTableList.at(nIndex);
		pCurrChTable->setHarmIndex(pnHarmIndex);
	}
}
