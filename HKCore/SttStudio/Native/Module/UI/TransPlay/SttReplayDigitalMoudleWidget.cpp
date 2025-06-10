#include "SttReplayDigitalMoudleWidget.h"
#include <QHBoxLayout>
#include "SttMacroParaEditViewTransPlay.h"


QSttReplayDigitalModuleWidget::QSttReplayDigitalModuleWidget(int nModuleIndex,CSttModuleComtradeBind *pChMapConfig,QWidget *parent)
:QWidget(parent)
{
	m_pTab = NULL;
	m_pModuleInfo = pChMapConfig;
	m_nModuleIndex = nModuleIndex;
	m_pParentWidget = parent;

	initUI();
	initData(m_pModuleInfo);

}

QSttReplayDigitalModuleWidget::~QSttReplayDigitalModuleWidget(void)
{
}

void QSttReplayDigitalModuleWidget::initUI()
{
	QHBoxLayout *p_HBoxLayout = new QHBoxLayout;
	m_pTab = new QTabWidget(this);	
	p_HBoxLayout->addWidget(m_pTab);
	this->setLayout(p_HBoxLayout);

	setFont(*g_pSttGlobalFont);
	m_pTab->setFont(*g_pSttGlobalFont);

#ifdef _PSX_QT_LINUX_ 
	m_pTab->setFixedSize(950, 480); // 设置固定大小,避免闪烁

#endif

// 	connect(m_pTab, SIGNAL(currentChanged(QWidget *)), this, SLOT(slot_TabChanged(QWidget *)));
}

void QSttReplayDigitalModuleWidget::initData(CSttModuleComtradeBind *pChMapConfig)
{
	if(!pChMapConfig)
	{
		return;
	}

	m_pModuleInfo = pChMapConfig;
	m_pTab->clear();

	CreateModules(m_pModuleInfo,6);
	CreatModuleChWidget();

}

void QSttReplayDigitalModuleWidget::CreatModuleChWidget()
{
	m_oModuleChWidgetList.clear();

	CSttReplayModuleChWidget *pModuleChWidget = NULL;
	CSttModuleComtradeBind *pModuleComtradeBind = NULL;
	CString strTabName;
	QMap<int,CSttModuleComtradeBind *>::iterator it;

	for (it = m_oDigitaModuleMap.begin(); it != m_oDigitaModuleMap.end(); ++it) 
	{
		strTabName.Format(_T("G%d"),it.key()+1);
		pModuleComtradeBind = it.value();

		pModuleChWidget = new CSttReplayModuleChWidget(m_nModuleIndex++,pModuleComtradeBind,this);
		m_oModuleChWidgetList.append(pModuleChWidget);
		m_pTab->addTab(pModuleChWidget,strTabName);

		connect(pModuleChWidget,SIGNAL(sig_ModuleChChanged(int,int)),g_pReplayTestMain,SLOT(slot_ModuleChChanged(int,int))/*,Qt::UniqueConnection*/);
		connect(pModuleChWidget,SIGNAL(sig_ModuleChRangeChanged()),g_pReplayTestMain,SLOT(slot_ModuleChRangeChanged())/*,Qt::UniqueConnection*/);  // slot_ModuleChChanged 用于更新波	
	}
}

void QSttReplayDigitalModuleWidget::initSignalSlots()
{
	CSttReplayModuleChWidget *pModuleChWidget = NULL;

	for(int nWidgetIndex = 0;nWidgetIndex < m_oModuleChWidgetList.size(); nWidgetIndex++)
	{
		pModuleChWidget = m_oModuleChWidgetList.at(nWidgetIndex);
		pModuleChWidget->initSignalSlots();
		connect(pModuleChWidget,SIGNAL(sig_ModuleChChanged(int,int)),g_pReplayTestMain,SLOT(slot_ModuleChChanged(int,int)));
		connect(pModuleChWidget,SIGNAL(sig_ModuleChRangeChanged()),g_pReplayTestMain,SLOT(slot_ModuleChRangeChanged()));  // slot_ModuleChChanged 用于更新波	

	}
}

void QSttReplayDigitalModuleWidget::uninitSignalSlots()
{
	CSttReplayModuleChWidget *pModuleChWidget = NULL;

	for(int nWidgetIndex = 0;nWidgetIndex < m_oModuleChWidgetList.size(); nWidgetIndex++)
	{
		pModuleChWidget = m_oModuleChWidgetList.at(nWidgetIndex);
		pModuleChWidget->uninitSignalSlots();
		disconnect(pModuleChWidget,SIGNAL(sig_ModuleChChanged(int,int)),g_pReplayTestMain,SLOT(slot_ModuleChChanged(int,int)));
		disconnect(pModuleChWidget,SIGNAL(sig_ModuleChRangeChanged()),g_pReplayTestMain,SLOT(slot_ModuleChRangeChanged()));  // slot_ModuleChChanged 用于更新波	

	}
}

void QSttReplayDigitalModuleWidget::startInit()
{

}

void QSttReplayDigitalModuleWidget::stopInit()
{

}

void QSttReplayDigitalModuleWidget::CreateModules( CSttModuleComtradeBind* m_pModuleInfo, int nGroupSize )
{
	m_oDigitaModuleMap.clear();

	POS pos = m_pModuleInfo->GetHeadPosition();
	CSttModuleChComtradeBind *pCh = NULL;
	int nModuleIndex = 0,nChIndex = 0;
	CSttModuleComtradeBind *pModuleComtradeBind = NULL;

	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetNext(pos);
		// 如果当前模块已满，创建一个新的模块
		if (nChIndex % nGroupSize == 0) 
		{
			pModuleComtradeBind = new CSttModuleComtradeBind();
			pModuleComtradeBind->m_strModuleID = m_pModuleInfo->m_strModuleID;
			pModuleComtradeBind->SetParent(m_pModuleInfo);
			m_oDigitaModuleMap.insert(nModuleIndex,pModuleComtradeBind);
			nModuleIndex++;
		}
		nChIndex++;
		pModuleComtradeBind->AddNewChild(pCh);
	}
}

void QSttReplayDigitalModuleWidget::InitDigitalModuleChList(const QStringList &oUChList,const QStringList &oIChList)
{
	CSttReplayModuleChWidget *pModuleChWidget = NULL;

	for (int nIndex=0; nIndex<m_oModuleChWidgetList.size(); nIndex++)
	{
		pModuleChWidget = m_oModuleChWidgetList.at(nIndex);
		pModuleChWidget->SetChSelectList(oUChList,oIChList);
	}
}

void QSttReplayDigitalModuleWidget::UpdateTwoCursorTimeValues( double dValueA,double dValueB )
{
	CSttReplayModuleChWidget *pModuleChWidget = NULL;

	for (int nIndex=0; nIndex<m_oModuleChWidgetList.size(); nIndex++)
	{
		pModuleChWidget = m_oModuleChWidgetList.at(nIndex);
		pModuleChWidget->UpdateTwoCursorTimeValues(dValueA,dValueB);
	}
}

void QSttReplayDigitalModuleWidget::setEnableStateUI( bool bEnable )
{
	CSttReplayModuleChWidget *pModuleChWidget = NULL;

	for (int nIndex=0; nIndex<m_oModuleChWidgetList.size(); nIndex++)
	{
		pModuleChWidget = m_oModuleChWidgetList.at(nIndex);
		pModuleChWidget->setEnableStateUI(bEnable);
	}
}

void QSttReplayDigitalModuleWidget::InitDigitalWidget()
{

}

CSttReplayModuleChWidget * QSttReplayDigitalModuleWidget::GetDigitalModuleChWidget( int nIndex )
{
	if(nIndex > GetDigitalModuleChWidgetCount())
	{
		return NULL;
	}
	return m_oModuleChWidgetList.at(nIndex);
}

int QSttReplayDigitalModuleWidget::GetDigitalModuleChWidgetCount()
{
	return m_oModuleChWidgetList.size();
}

void QSttReplayDigitalModuleWidget::UpdateABChSel()
{
// 	CSttReplayModuleChWidget *pModuleChWidget = NULL;
// 
// 	for (int nIndex=0; nIndex<m_oModuleChWidgetList.size(); nIndex++)
// 	{
// 		pModuleChWidget = m_oModuleChWidgetList.at(nIndex);
// 		pModuleChWidget->UpdateABChSel();
// 	}
}

void QSttReplayDigitalModuleWidget::UpdateUIMax( double fUMax,double fIMax )
{
	CSttReplayModuleChWidget *pWidget = NULL;
	for(int nIndex = 0; nIndex < m_oModuleChWidgetList.size(); nIndex++)
	{
		pWidget = m_oModuleChWidgetList.at(nIndex);
		if(pWidget)
		{
			pWidget->UpdateUIMax(fUMax, fIMax);
		}
	}
}

void QSttReplayDigitalModuleWidget::UpdateUIMax()
{
	CSttReplayModuleChWidget *pSttReplayModuleChWidget = NULL;
	double fUMax,fIMax;

	g_theBigComtradeTransPlay->m_oComtradePlayConfig.GetReplayChMaxValue(fUMax,fIMax,REPLAY_MODULE_TYPE_DIGITAL);
	UpdateUIMax(fUMax,fIMax);

}

int QSttReplayDigitalModuleWidget::GetIndexByID( CString ChStrID )
{
	if (m_pModuleInfo == NULL)
	{
		return -1;
	}

	CSttModuleChComtradeBind *pCh = NULL;
	POS pos = m_pModuleInfo->GetHeadPosition();
	long nCount = 0;

	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetNext(pos);
		if(pCh->m_strID == ChStrID)
		{
			return nCount;
		}
		nCount++;
	}

	return -1;
}

QWidget* QSttReplayDigitalModuleWidget::GetParaSetWidget()
{
	return m_pParentWidget;
}

void QSttReplayDigitalModuleWidget::SetChSelectList( const QStringList &oUChList,const QStringList &oIChList )
{
	if(oUChList.isEmpty() || oIChList.isEmpty())
	{
		return;
	}

	for(int nModuleIndex = 0; nModuleIndex < m_oModuleChWidgetList.size(); nModuleIndex++)
	{
		CSttReplayModuleChWidget *pWidget = m_oModuleChWidgetList.at(nModuleIndex);
		pWidget->SetChSelectList(oUChList,oIChList);
	}
}

void QSttReplayDigitalModuleWidget::clearTab()
{
	m_pTab->clear();

	CSttReplayModuleChWidget *pSttReplayModuleChWidget = NULL;
	for (int i=0; i<m_oModuleChWidgetList.size(); i++)
	{
		pSttReplayModuleChWidget = m_oModuleChWidgetList.at(i);
		delete pSttReplayModuleChWidget;
	}
}

void QSttReplayDigitalModuleWidget::slot_TabChanged( QWidget *pCurWidget )
{
// 	CSttReplayModuleChWidget *pSttReplayModuleChWidget = NULL;
// 	BOOL bHasFind = FALSE;
// 
// 	for (int nIndex =0; nIndex<m_oModuleChWidgetList.size(); nIndex++)
// 	{
// 		pSttReplayModuleChWidget = m_oModuleChWidgetList.at(nIndex);
// 
// 		if (pSttReplayModuleChWidget == pCurWidget)
// 		{
// 			bHasFind = TRUE;
// // 			pSttReplayModuleChWidget->UpdatePT_CT_Rates();
// 			break;
// 		}
// 	}
// 
// 	if (bHasFind)
// 	{
// 		pSttReplayModuleChWidget->SetDefaultFocusCtrl();
// 	}

	if(!pCurWidget)
	{
		return;
	}

    pCurWidget->setWindowFlags(pCurWidget->windowFlags() | Qt::WindowStaysOnTopHint);

}


