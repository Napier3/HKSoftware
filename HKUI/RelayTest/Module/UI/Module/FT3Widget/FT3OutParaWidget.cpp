#include "FT3OutParaWidget.h"
#include <QGridLayout>
//#include "../../SttTestCntrFrameBase.h"

extern long g_nLogDebugInfor;

QFT3OutParaWidget::QFT3OutParaWidget(CIecCfgDatasSMV *pIecCfgDatasSMV,bool bInitEditable)
{
	initUI();
	m_bFt3Flag=false;
	m_bFt3Disabled=false;
	m_nRunState = -1;
	m_bInitEditable=bInitEditable;

	InitFT3Table(pIecCfgDatasSMV);
	SetRunState();
	SetGooseDisabled();
}

QFT3OutParaWidget::~QFT3OutParaWidget()
{

}

void QFT3OutParaWidget::initUI()
{
	m_tab_FT3Pub = new QTabWidget(this);
	QGridLayout* pLayout = new QGridLayout;
	pLayout->addWidget(m_tab_FT3Pub);
	setLayout(pLayout);
}

void QFT3OutParaWidget::InitFT3Table(CIecCfgDatasSMV *pIecCfgDatasSMV)
{
	if (pIecCfgDatasSMV == NULL)
	{
		return;
	}
	m_tab_FT3Pub->clear();
	if (m_pFT3WidgetList.size() > 0)
	{
		for (int i =0; i < m_pFT3WidgetList.size(); i++)
		{
			delete m_pFT3WidgetList[i];
			m_pFT3WidgetList[i] = NULL;
		}
		m_pFT3WidgetList.clear();
	}
	CIecCfg6044CommonData* pIecCfg6044CommonData = NULL;
	CExBaseObject *pCurObj = NULL;
	long nIndex = 0;
	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	while(pos)
	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> >>>>>> begin InitFT3Table-  >>");	}

		pCurObj=pIecCfgDatasSMV->GetNext(pos);
		if (pCurObj->GetClassID()==CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			pIecCfg6044CommonData=(CIecCfg6044CommonData*)pCurObj;
			
			if (pIecCfg6044CommonData->m_nUseFlag == 1)
			{
				FT3OutWidget *pFT3OutWidget=new FT3OutWidget(this,m_tab_FT3Pub);
				pFT3OutWidget->SetRunState(STT_UI_RUN_STATE_StateTested_NotEditable);
				connect(pFT3OutWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
				m_tab_FT3Pub->insertTab(nIndex, pFT3OutWidget, QString("G%1").arg(nIndex+1));
				m_pFT3WidgetList.append(pFT3OutWidget);
				initOneFT3BlockTable(pFT3OutWidget,pIecCfg6044CommonData);
				nIndex++;
			}						
		}
	
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> >>>>>> end InitFT3Table-  >>");	}
	}
	m_tab_FT3Pub->setFont(*g_pSttGlobalFont);
}

void QFT3OutParaWidget::initOneFT3BlockTable(FT3OutWidget *p,CIecCfg6044CommonData* pCfg6044CommonData)
{
	p->InitData(pCfg6044CommonData,m_bInitEditable);
}

void QFT3OutParaWidget::slot_FT3DataChanged()
{
	emit sig_FT3DataChanged();
}

void QFT3OutParaWidget::SetRunState(int nRunState)
{
	m_nRunState = nRunState;

	if (m_tab_FT3Pub != NULL)
	{
		SetRunState();
	}
}

void QFT3OutParaWidget::SetRunState()
{
	int num = m_pFT3WidgetList.size();
	for (int i =0; i < num; i++)
	{
		m_pFT3WidgetList[i]->SetRunState(m_nRunState);
	}
}

void QFT3OutParaWidget::SetGooseDisabled(bool bFlag)
{
	m_bFt3Disabled=bFlag;
	if (m_tab_FT3Pub != NULL)
	{
		SetGooseDisabled();
	}
}

void QFT3OutParaWidget::SetGooseDisabled()
{
 	int num = m_pFT3WidgetList.size();
 	for (int i =0; i < num; i++)
 	{
 		m_pFT3WidgetList[i]->m_pIecCfgFT3OutGrid->setDisabled(m_bFt3Disabled);
 	}
}

