#include "paraset.h"
#include <QDebug>

ParaSet::ParaSet(QWidget *parent)
	: QWidget(parent)
{
	m_pMainGridLayout = new QGridLayout(this);
	m_pUScrollArea = new QScrollArea(this);
	m_pIScrollArea = new QScrollArea(this);
	m_pUWidget = new QWidget(m_pUScrollArea);
	m_pIWidget = new QWidget(m_pIScrollArea);
	m_pUScrollArea->setWidget(m_pUWidget);
	m_pIScrollArea->setWidget(m_pIWidget);
	m_pUVGridLayout = new QGridLayout(m_pUWidget);
	m_pIVGridLayout = new QGridLayout(m_pIWidget);

	m_pArrUIVOL = NULL;
	m_pArrUICUR = NULL;
	m_pSttTestResource = NULL;
}

ParaSet::~ParaSet()
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

void ParaSet::Release()
{
	for (int i = 0; i< m_UCHannelTableList.size(); i++)
	{
		CHannelTable *p = m_UCHannelTableList.at(i);
		delete p;
		p = NULL;
	}
	m_UCHannelTableList.clear();

	for (int i = 0; i< m_ICHannelTableList.size(); i++)
	{
		CHannelTable *p = m_ICHannelTableList.at(i);
		delete p;
		p = NULL;
	}
	m_ICHannelTableList.clear();
}

void ParaSet::initUI(CSttTestResourceBase *pSttTestResource)
{
	Release();

	if (pSttTestResource != NULL)
	{
		m_pSttTestResource = pSttTestResource;
	}

	if (m_pSttTestResource == NULL)
	{
		return;
	};

	CHannelTable *pVolChTable = NULL,*pCurChTable = NULL;

	if (isLowSignal())
	{
		pVolChTable = new CHannelLowSTable(Moudle_U,&m_pSttTestResource->m_oVolChRsListRef,m_pArrUIVOL,m_pUWidget);	
		pCurChTable = new CHannelLowSTable(Moudle_I,&m_pSttTestResource->m_oCurChRsListRef,m_pArrUICUR,m_pUWidget);
	}
	else
	{
		pVolChTable = new CHannelTable(Moudle_U,&m_pSttTestResource->m_oVolChRsListRef,m_pArrUIVOL,m_pUWidget);
		pCurChTable = new CHannelTable(Moudle_I,&m_pSttTestResource->m_oCurChRsListRef,m_pArrUICUR,m_pUWidget);
	}

	m_UCHannelTableList.append(pVolChTable);
	pVolChTable->setColumnNum(4);
	m_ICHannelTableList.append(pCurChTable);
	pCurChTable->setColumnNum(4);

// 	if (*m_pUModuleNum==m_pUModultChannelNumList->size())
// 	{
// 		for (int i = 0;i<*m_pUModuleNum;i++)
// 		{
// 			CHannelTable *p = NULL;
// 
// 			if (i == 0 )
// 			{
// 				if (isLowSignal())
// 				{
// 					p = new CHannelLowSTable(0,i+1,Moudle_U,i+1,m_pUModultChannelNumList->at(i),m_pArrUIVOL,m_pUWidget);
// 				}
// 				else
// 				{
// 					p = new CHannelTable(0,i+1,Moudle_U,i+1,m_pUModultChannelNumList->at(i),m_pArrUIVOL,m_pUWidget);
// 				}
// 			}
// 			else
// 			{
// 				int temp = 0;
// 				for (int j = 0; j< i; j++)
// 				{
// 					temp += m_pUModultChannelNumList->at(j);
// 				}
// 				int nnameNum = (int)(float(temp)/3.0);
// 				if (isLowSignal())
// 				{
// 					p = new CHannelLowSTable(nnameNum+1,i+1,Moudle_U,i+1,m_pUModultChannelNumList->at(i),m_pArrUIVOL+temp,m_pUWidget);
// 				}
// 				else
// 				{
// 					p = new CHannelTable(nnameNum+1,i+1,Moudle_U,i+1,m_pUModultChannelNumList->at(i),m_pArrUIVOL+temp,m_pUWidget);
// 				}
// 			}
// 			m_UCHannelTableList.append(p);
// 			p->setColumnNum(4);
// 		}
// 	}

// 	if (*m_pIModuleNum==m_pIModultChannelNumList->size())
// 	{
// 		for (int i = 0;i<*m_pIModuleNum;i++)
// 		{
// 			CHannelTable *p = NULL;
// 
// 			if (i == 0 )
// 			{
// 				if (isLowSignal())
// 				{
// 					p = new CHannelLowSTable(0,i+1,Moudle_I,i+1,m_pIModultChannelNumList->at(i),m_pArrUIVOL,m_pUWidget);
// 				}
// 				else
// 				{
// 					p = new CHannelTable(0,i+1,Moudle_I,i+1,m_pIModultChannelNumList->at(i),m_pArrUIVOL,m_pUWidget);
// 				}
// 			}
// 			else
// 			{
// 				int temp = 0;
// 				for (int j = 0; j< i; j++)
// 				{
// 					temp += m_pIModultChannelNumList->at(j);
// 				}
// 				int nnameNum = (int)(float(temp)/3.0);
// 				if (isLowSignal())
// 				{
// 					p = new CHannelLowSTable(nnameNum+1,i+1,Moudle_I,i+1,m_pIModultChannelNumList->at(i),m_pArrUIVOL+temp,m_pUWidget);
// 				}
// 				else
// 				{
// 					p = new CHannelTable(nnameNum+1,i+1,Moudle_I,i+1,m_pIModultChannelNumList->at(i),m_pArrUIVOL+temp,m_pUWidget);
// 				}
// 			}
// 			m_ICHannelTableList.append(p);
// 			p->setColumnNum(4);
// 		}
// 	}

	for (int i = 0; i<m_UCHannelTableList.size();i++)
	{
		connect(m_UCHannelTableList[i],SIGNAL(sig_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)),this,SLOT(slot_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)));
	}
	for (int i = 0; i<m_ICHannelTableList.size();i++)
	{
		connect(m_ICHannelTableList[i],SIGNAL(sig_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)),this,SLOT(slot_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)));
	}
	
	int nUWidgetHeight = 0;	
	int nUWidgetWidth = 0;
	for (int i = 0; i < m_UCHannelTableList.size(); i++)
	{
		nUWidgetWidth = m_UCHannelTableList[i]->getTableWidth();
		nUWidgetHeight += m_UCHannelTableList[i]->getTableHeight();
		m_pUVGridLayout->addWidget(m_UCHannelTableList.at(i),i,0,1,1);
	}
	
	m_pUWidget->setMinimumHeight(int(nUWidgetHeight));
	m_pUVGridLayout->setRowStretch(m_UCHannelTableList.size(),1);
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
	m_pIVGridLayout->setRowStretch(m_ICHannelTableList.size(),1);
	m_pIVGridLayout->setMargin(0);
	m_pIVGridLayout->setSpacing(0);
	m_pIWidget->setLayout(m_pIVGridLayout);

	m_pUScrollArea->setWidgetResizable(true);
	m_pIScrollArea->setWidgetResizable(true);
	m_pMainGridLayout->addWidget(m_pUScrollArea,0,0);
	m_pMainGridLayout->addWidget(m_pIScrollArea,0,1);
}

void ParaSet::initData()
{
	if ((m_pSttTestResource == NULL)||(m_pArrUIVOL == NULL)||(m_pArrUICUR == NULL))
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

void ParaSet::setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource,
								   tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR)
{
	ASSERT(pSttTestResource);
	ASSERT( pArrUIVOL != NULL);
	ASSERT( pArrUICUR != NULL);

	m_type = type;
	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;
	m_pSttTestResource = pSttTestResource;

	initUI(pSttTestResource);
	initData();
}

void ParaSet::setData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR)
{
	ASSERT( pArrUIVOL != NULL);
	ASSERT( pArrUICUR != NULL);

	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;
}

void ParaSet::setMaxMinAndEDVal()
{
	setUAmpMaxMinValue();
	setIAmpMaxMinValue();

	setUAmpEDValue(g_oSystemParas.m_fVNom);
	setIAmpEDValue(g_oSystemParas.m_fINom);
}

void ParaSet::DCStateChanged(int type,bool bdc)
{
	if (type == m_type)
	{
		for (int i = 0; i<m_UCHannelTableList.size();i++)
		{
			m_UCHannelTableList[i]->setProperty(bdc);
		}
		for (int i = 0; i<m_ICHannelTableList.size();i++)
		{
			m_ICHannelTableList[i]->setProperty(bdc);
		}
	}
}

void ParaSet::startInit(bool bEnable)
{
	setDisabled(!bEnable);
}

void ParaSet::stopInit(bool bEnable)
{
	setDisabled(!bEnable);
}

void ParaSet::setDispMode(int dispmode)
{
	m_dispMode = dispmode;

	QStringList strheader;
	int num;
	strheader.clear();
	if (m_dispMode == V_Primary)//一次值
	{
		strheader<<tr("通道")<<tr("幅值(KV)")<<tr("相位(°)")<<tr("频率(Hz)");
		num = m_UCHannelTableList.size();
		for (int i =0; i<num; i++)
		{
			m_UCHannelTableList[i]->setHeaderOfTable(strheader);
		}
	}
	else
	{
		strheader<<tr("通道")<<tr("幅值(V)")<<tr("相位(°)")<<tr("频率(Hz)");
		num = m_UCHannelTableList.size();
		for (int i =0; i<num; i++)
		{
			m_UCHannelTableList[i]->setHeaderOfTable(strheader);
		}
	}

	strheader.clear();
	strheader<<tr("通道")<<tr("幅值(A)")<<tr("相位(°)")<<tr("频率(Hz)");
	num = m_ICHannelTableList.size();
	for (int i =0; i<num; i++)
	{
		m_ICHannelTableList[i]->setHeaderOfTable(strheader);
	}
}

void ParaSet::setUAmpMaxMinValue()
{
	int num = 0;
	num = m_UCHannelTableList.size();
	for (int i=0; i<num; i++)
	{
		if (isAnalog() || isCommon())
		{
			if(m_pArrUIVOL[0].Harm[1].bDC)
			{
				m_UCHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fDC_CurMax,0);
			}
			else
			{
				m_UCHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fAC_VolMax,0);
			}
		}
		else if (isDigital())
		{
			m_UCHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fDigVMax,0);
		}
		else if (isLowSignal())
		{
			((CHannelLowSTable*)m_UCHannelTableList[i])->setAmpMaxMinValue(g_oLocalSysPara.m_fWeakVolMax,0);
			((CHannelLowSTable*)m_UCHannelTableList[i])->setAmpMaxMinValueZero(g_oLocalSysPara.m_fWeakVolMax,0);
		}
	}
}

void ParaSet::setIAmpMaxMinValue()
{
	int num = 0;
	num = m_ICHannelTableList.size();
	for (int i =0; i<num; i++)
	{
		if (isAnalog() || isCommon())
		{
			if (m_pArrUIVOL[0].Harm[1].bDC)
			{
				m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fDC_CurMax  /*AnaDcIMaxList[i]*/,0);
			}
			else
			{
				m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fAC_CurMax/*AnaAcIMaxList[i]*/,0/*g_oLocalSysPara.AnaAcVMinList[i]*/);
			}
		}
		else if (isDigital())
		{
			m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fDigIMax,0);
		}
		else if (isLowSignal())
		{
			((CHannelLowSTable*)m_ICHannelTableList[i])->setAmpMaxMinValue(g_oLocalSysPara.m_fWeakCurrMax/*LowSCurrCT1MaxList[i]*/,0/*g_oLocalSysPara.LowSCurrCT1MinList[i]*/);
			((CHannelLowSTable*)m_ICHannelTableList[i])->setAmpMaxMinValueZero(g_oLocalSysPara.m_fWeakCurrMax/*LowSZeroCurrCT1MaxList[i]*/,0/*g_oLocalSysPara.LowSZeroCurrCT1MinList[i]*/);
		}
	}
}

void ParaSet::setUAmpEDValue(float fUEDVal)
{
	int num = 0;
	num = m_UCHannelTableList.size();
	for (int i =0; i<num; i++)
	{
		m_UCHannelTableList[i]->setAmpEDValue(fUEDVal);
	}
}

void ParaSet::setIAmpEDValue(float fIEDVal)
{
	int num = 0;
	num = m_ICHannelTableList.size();
	for (int i =0; i<num; i++)
	{
		m_ICHannelTableList[i]->setAmpEDValue(fIEDVal);
	}
}

void ParaSet::setUAmpMaxMinValueZero(float fmax,float fmin)
{
	int num = 0;
	num = m_UCHannelTableList.size();
	for (int i =0; i<num; i++)
	{
		((CHannelLowSTable*)m_UCHannelTableList[i])->setAmpMaxMinValueZero(fmax,fmin);
	}
}

void ParaSet::setIAmpMaxMinValueZero(float fmax,float fmin)
{
	int num = 0;
	num = m_ICHannelTableList.size();
	for (int i =0; i<num; i++)
	{
		((CHannelLowSTable*)m_ICHannelTableList[i])->setAmpMaxMinValueZero(fmax,fmin);
	}
}

//递变槽
void ParaSet::setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC)
{
	float fv;
	int nChIndex;
	bool bU = false;
	ASSERT(m_pSttTestResource != NULL);

	if (str.contains(_T("U")))
	{
		bU = true;
		nChIndex = m_pSttTestResource->m_oVolChRsListRef.FindIndexByName(str);
	}
	else if (str.contains(_T("I")))
	{
		bU = false;
		nChIndex = m_pSttTestResource->m_oCurChRsListRef.FindIndexByName(str);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("递变通道名【%s】非法"),str);
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

void ParaSet::slot_ChannelValueChanged(MOUDLEType moudleType,/*int moudleID,*/int channelNum,int valueFlag,float datavalue)
{
	emit sig_updataParas();
}