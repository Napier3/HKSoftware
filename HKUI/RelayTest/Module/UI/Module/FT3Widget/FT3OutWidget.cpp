#include "FT3OutWidget.h"
#include <QHeaderView>
#include "../SttUIDefine.h"
//#include "../../SttTestCntrFrameBase.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "FT3OutParaWidget.h"

extern long g_nLogDebugInfor;

FT3OutWidget::FT3OutWidget(QFT3OutParaWidget *pParaWidget,QWidget *parent)
: QWidget(parent)
{
	m_pIecCfgFT3OutGrid = NULL;
	m_pParent=pParaWidget;
	InitUI();
}

FT3OutWidget::~FT3OutWidget()
{

}

void FT3OutWidget::InitUI()
{
	m_pIecCfgFT3OutGrid=new IecCfgFT3OutGrid(this);
	m_pIecCfgFT3OutGrid->horizontalHeader()->setFont(*g_pSttGlobalFont); 
	m_pIecCfgFT3OutGrid->setFont(*g_pSttGlobalFont);
	m_pIecCfgFT3OutGrid->InitGrid();

	m_pIecCfgFT3OutGrid->setDisabled(m_pParent->m_bFt3Flag);
	m_pMainLayout = new QVBoxLayout(this);

	m_pMainLayout->addWidget(m_pIecCfgFT3OutGrid);
	setLayout(m_pMainLayout);
}


void FT3OutWidget::InitData(CIecCfg6044CommonData *pIecCfg6044CommonData,bool bInitEditable)
{
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> >>>>>>>>>> begin FT3OutWidget::initData   >>");	}

	if (bInitEditable)
	{
		m_pIecCfgFT3OutGrid->SetRunState(STT_UI_RUN_STATE_Stoped);
	}
	else
	{
		m_pIecCfgFT3OutGrid->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);
	}
	POS pos=pIecCfg6044CommonData->GetHeadPosition();
	CIecCfg6044Chs *pIecCfg6044Chs=NULL;
	while (pos)
	{
		pIecCfg6044Chs=(CIecCfg6044Chs*)pIecCfg6044CommonData->GetNext(pos);
		if (pIecCfg6044Chs->GetClassID()==CFGCLASSID_CIECCFGCHS6044)
		{
			m_pIecCfgFT3OutGrid->ShowDatas(pIecCfg6044Chs);
			connect(m_pIecCfgFT3OutGrid,SIGNAL(sig_Ft3Value_Changed()),this,SLOT(slot_dataChanged()));
		}
	}	
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> >>>>>>>>>> end FT3OutWidget::initData   >>");	}
}

void FT3OutWidget::SetRunState(int nRunState)
{
	ASSERT(m_pIecCfgFT3OutGrid);
	m_pIecCfgFT3OutGrid->SetRunState(nRunState);
}


void FT3OutWidget::slot_dataChanged()
{
	Q_EMIT sig_FT3DataChanged();
}
