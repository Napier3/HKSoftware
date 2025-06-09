#include "FT3Widget.h"
#include <QHeaderView>
#include "../../Define.h"
#include <QLabel>
#include "../../SttXTestMngrBaseApp.h"
FT3Widget::FT3Widget(QWidget *parent): QWidget(parent)
{
	m_pFT3Grid = NULL;
	InitUI();
}

FT3Widget::~FT3Widget()
{

}

void FT3Widget::InitUI()
{
	m_pFT3Grid=new FT3Grid(this);
	m_pFT3Grid->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); 
	m_pFT3Grid->InitGrid();

	m_pFT3Grid->setDisabled(g_theSttXTestMngrBaseApp->m_bFt3Flag);
	m_pMainLayout = new QVBoxLayout(this);

	m_pMainLayout->addWidget(m_pFT3Grid);
	setLayout(m_pMainLayout);
}

//void FT3Widget::InitData(CIecCfgDatasSMV* pIecCfgDatasSMV)
//{
// 	ASSERT(pIecCfgDatasSMV);
// 	CExBaseObject *pCurObj = NULL;
// 	CIecCfg6044CommonData *pIecCfg6044CommonData = NULL;
// 	POS pos1 = pIecCfgDatasSMV->GetHeadPosition();
// 	
// 	while(pos1)
// 	{
// 		pCurObj = pIecCfgDatasSMV->GetNext(pos1);
// 		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
// 		{
// 			pIecCfg6044CommonData = (CIecCfg6044CommonData *)pCurObj; 
// 			POS pos2=pIecCfg6044CommonData->GetHeadPosition();
// 			CIecCfg6044Chs *pIecCfg6044Chs=NULL;
// 			while (pos2)
// 			{
// 				pIecCfg6044Chs=(CIecCfg6044Chs*)pIecCfg6044CommonData->GetNext(pos2);
// 				if (pIecCfg6044Chs->GetClassID()==CFGCLASSID_CIECCFGCHS6044)
// 				{
// 					m_pFT3Grid->ShowDatas(pIecCfg6044Chs);
//  				}
//  			}		
// 		}	
// 	}
//}

void FT3Widget::InitData(CIecCfg6044CommonData *pIecCfg6044CommonData)
{	
	POS pos=pIecCfg6044CommonData->GetHeadPosition();
	CIecCfg6044Chs *pIecCfg6044Chs=NULL;
	while (pos)
	{
		pIecCfg6044Chs=(CIecCfg6044Chs*)pIecCfg6044CommonData->GetNext(pos);
		if (pIecCfg6044Chs->GetClassID()==CFGCLASSID_CIECCFGCHS6044)
		{
			m_pFT3Grid->ShowDatas(pIecCfg6044Chs);
			connect(m_pFT3Grid,SIGNAL(sig_Ft3Value_Changed()),this,SLOT(slot_dataChanged()));
		}
	}	
}

void FT3Widget::SetRunState(int nRunState)
{
	ASSERT(m_pFT3Grid);
	m_pFT3Grid->SetRunState(nRunState);
}


void FT3Widget::slot_dataChanged()
{
	Q_EMIT sig_FT3DataChanged();
}
