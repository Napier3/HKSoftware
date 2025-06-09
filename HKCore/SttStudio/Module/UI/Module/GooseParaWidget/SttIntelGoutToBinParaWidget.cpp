#include "SttIntelGoutToBinParaWidget.h"
#include <QGridLayout>
#include "GoosePubWidget.h"
#include "../../../Module/API/GlobalConfigApi.h"
extern long g_nLogDebugInfor;

QSttIntelGoutToBinParaWidget::QSttIntelGoutToBinParaWidget(CIecCfgGoutDatas* pCfgGoutDatas ,bool bInitEditable)
{
	m_pCfgGoutDatas = pCfgGoutDatas;
	m_bInitEditable = bInitEditable;	
	m_tab_GoosePub = NULL;

	m_bGooseFlag = false;
	m_nRunState = -1;
	m_bGooseDisabled = false;
	m_bTestCheckBox_Visible = true;
}

QSttIntelGoutToBinParaWidget::~QSttIntelGoutToBinParaWidget()
{

}

void QSttIntelGoutToBinParaWidget::initUI()
{
	m_tab_GoosePub = new QTabWidget(this);
    
	QGridLayout* pLayout = new QGridLayout;
	pLayout->addWidget(m_tab_GoosePub);
	setLayout(pLayout);
}

void QSttIntelGoutToBinParaWidget::initGoosePubTable(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (pCfgGoutDatas == NULL)
	{
		return;
	}

	m_pCfgGoutDatas = pCfgGoutDatas;

	if (m_tab_GoosePub != NULL)
	{
		initGoosePubTable();
	}
}	

void QSttIntelGoutToBinParaWidget::initGoosePubTable( )
{
	m_tab_GoosePub->clear();
	if (m_pGoosePubList.size() > 0)
	{
		for (int i =0; i < m_pGoosePubList.size(); i++)
		{
			delete m_pGoosePubList[i];
			m_pGoosePubList[i] = NULL;
		}
		m_pGoosePubList.clear();
	}

	CIecCfgGoutData* pCfgGoutData = NULL;
	long nGoutIndex = 0;
	POS pos = m_pCfgGoutDatas->GetHeadPosition();

	while(pos)
	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> >>>>>> begin initGoosePubTable-  >>");	}

		pCfgGoutData = (CIecCfgGoutData*)m_pCfgGoutDatas->GetNext(pos);

		if (pCfgGoutData->m_nUseFlag == 1)
		{
			QSttIntelGoutToBinPubWidget *pGoosePub = new QSttIntelGoutToBinPubWidget(this,m_tab_GoosePub);

			if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> >>>>>> begin initGoosePubTable- 1 >>");	}

			connect(pGoosePub, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()),Qt::DirectConnection);
			connect(pGoosePub, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_RepairDataChanged()));
			connect(pGoosePub, SIGNAL(sig_RevertData()), this, SLOT(slot_RevertData()));
			connect(pGoosePub, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
			connect(pGoosePub, SIGNAL(sig_GoutRowIndex(int)), this, SLOT(slot_GoutRowIndex(int)));
			m_tab_GoosePub->insertTab(nGoutIndex, pGoosePub, QString("G%1").arg(nGoutIndex+1));
			m_pGoosePubList.append(pGoosePub);
			initOneGooseBlockTable(pGoosePub,pCfgGoutData);
			nGoutIndex++;
		}

		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> >>>>>> end initGoosePubTable-  >>");	}
	}
	m_tab_GoosePub->setFont(*g_pSttGlobalFont);
}

void QSttIntelGoutToBinParaWidget::initOneGooseBlockTable( QSttIntelGoutToBinPubWidget *p,CIecCfgGoutData *pCfgGoutData )
{
	p->initData(pCfgGoutData,m_bInitEditable);
}

void QSttIntelGoutToBinParaWidget::slot_GooseDataChanged()
{
	emit sig_GooseDataChanged();
}

void QSttIntelGoutToBinParaWidget::slot_RepairDataChanged()
{
	emit sig_RepairDataChanged();
}

void QSttIntelGoutToBinParaWidget::slot_GoutMapChanged()
{
	emit sig_GoutMapChanged();
}

void QSttIntelGoutToBinParaWidget::slot_RevertData()
{
	emit sig_RevertData();
}

void QSttIntelGoutToBinParaWidget::slot_GoutRowIndex(int nRowIndex)
{
	emit sig_GoutRowIndex(nRowIndex);
}

void QSttIntelGoutToBinParaWidget::SetRunState(int nRunState)
{
	m_nRunState = nRunState;

	if (m_tab_GoosePub != NULL)
	{
		SetRunState();
	}
}

void QSttIntelGoutToBinParaWidget::SetRunState()
{
	int num = m_pGoosePubList.size();

	for (int i =0; i < num; i++)
	{
		m_pGoosePubList[i]->SetRunState(m_nRunState);
	}
}

//void QSttIntelGoutToBinParaWidget::SetTestCheckBox_Visible(BOOL bVisible)
//{
//	m_bTestCheckBox_Visible = bVisible;
//
//	if (m_tab_GoosePub != NULL)
//	{
//		SetTestCheckBox_Visible();
//	}
//}
//
//void QSttIntelGoutToBinParaWidget::SetTestCheckBox_Visible()
//{
//	int num = m_pGoosePubList.size();
//
//	for (int i =0; i < num; i++)
//	{
//		m_pGoosePubList[i]->SetTestCheckBox_Visible(m_bTestCheckBox_Visible);
//	}
//}

void QSttIntelGoutToBinParaWidget::SetGooseDisabled( bool bFlag )
{
	m_bGooseDisabled = bFlag;

	if (m_tab_GoosePub != NULL)
	{
		SetGooseDisabled();
	}
}

void QSttIntelGoutToBinParaWidget::SetGooseDisabled()
{
	for (int i =0; i < m_pGoosePubList.size(); i++)
	{
		if (i==m_tab_GoosePub->currentIndex())
		{
			m_tab_GoosePub->setTabEnabled(i,m_bGooseDisabled);
		}
		else
		{
			m_tab_GoosePub->setTabEnabled(i,!m_bGooseDisabled);
		}
		m_pGoosePubList[i]->pbn_Revert->setDisabled(m_bGooseDisabled);
		m_pGoosePubList[i]->chb_Repair->setDisabled(m_bGooseDisabled);
		m_pGoosePubList[i]->EnableInverseCol(m_bGooseDisabled);	
	}
}
void QSttIntelGoutToBinParaWidget::setGooseTabEnable()
{
	for (int i =0; i < m_pGoosePubList.size(); i++)
	{
		setGooseTabEnable(m_bTestCheckBox_Visible);
	}
}

void QSttIntelGoutToBinParaWidget::setGooseTabEnable( bool bFlag )
{
	for (int i =0; i < m_pGoosePubList.size(); i++)
	{
		m_tab_GoosePub->setTabEnabled(i,bFlag);
	}
}


void QSttIntelGoutToBinParaWidget::showEvent(QShowEvent *)
{
	if (m_tab_GoosePub != NULL)
	{
		return;
	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin QGooseParaWidget-  >>");	}


	initUI();

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> ------ QGooseParaWidget-  1  >>");	}
	
	initGoosePubTable(m_pCfgGoutDatas);
	SetRunState();
	SetGooseDisabled();
	setGooseTabEnable();
	//SetTestCheckBox_Visible();//ÉèÖÃ¼ìÐÞ×´Ì¬¹´Ñ¡¿òÊÇ·ñ¿É¼û

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end QGooseParaWidget-  >>");	}
}

void QSttIntelGoutToBinParaWidget::setGooseResultVlaues( )
{
	for (int i =0; i < m_pGoosePubList.size(); i++)
	{
		m_pGoosePubList[i]->setGooseResultVlaues();
	}
}

void QSttIntelGoutToBinParaWidget::startInit( )
{
	m_pGoosePubList[m_tab_GoosePub->currentIndex()]->startInit();
}