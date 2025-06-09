#include "qgooseparawidget.h"
#include <QGridLayout>
#include "GoosePubWidget.h"
#include "../../../Module/API/GlobalConfigApi.h"
//#include "../../SttTestCntrFrameBase.h"

extern long g_nLogDebugInfor;

QGooseParaWidget::QGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas ,bool bInitEditable)
{
	m_pCfgGoutDatas = pCfgGoutDatas;
	m_bInitEditable = bInitEditable;	
	m_tab_GoosePub = NULL;

	m_bGooseFlag = false;
	m_nRunState = -1;
	m_bGooseDisabled = false;
	m_bTestCheckBox_Visible = true;
}

QGooseParaWidget::~QGooseParaWidget()
{

}

void QGooseParaWidget::initUI()
{
	m_tab_GoosePub = new QTabWidget(this);
    
	QGridLayout* pLayout = new QGridLayout;
	pLayout->addWidget(m_tab_GoosePub);
	setLayout(pLayout);
}

void QGooseParaWidget::initGoosePubTable(CIecCfgGoutDatas* pCfgGoutDatas)
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

void QGooseParaWidget::initGoosePubTable( )
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
			GoosePubWidget *pGoosePub = new GoosePubWidget(this,m_tab_GoosePub);

			if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> >>>>>> begin initGoosePubTable- 1 >>");	}

			connect(pGoosePub, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()),Qt::DirectConnection);
			connect(pGoosePub, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_RepairDataChanged()));
			connect(pGoosePub, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
			m_tab_GoosePub->insertTab(nGoutIndex, pGoosePub, QString("G%1").arg(nGoutIndex+1));
			m_pGoosePubList.append(pGoosePub);
			initOneGooseBlockTable(pGoosePub,pCfgGoutData);
			nGoutIndex++;
		}

		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> >>>>>> end initGoosePubTable-  >>");	}
	}

	//2022-10-14 采用  g_pSttGlobalFont
	// 	QFont font1 = m_tab_GoosePub->font();
	// 	font1.setPointSize(20);
	// 	m_tab_GoosePub->setFont(font1);

	m_tab_GoosePub->setFont(*g_pSttGlobalFont);
}

void QGooseParaWidget::initOneGooseBlockTable( GoosePubWidget *p,CIecCfgGoutData *pCfgGoutData )
{
	p->initData(pCfgGoutData,m_bInitEditable);
}

void QGooseParaWidget::slot_GooseDataChanged()
{
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QGooseParaWidget::slot_GooseDataChanged."));
	emit sig_GooseDataChanged();
}

void QGooseParaWidget::slot_RepairDataChanged()
{
	emit sig_RepairDataChanged();
}

void QGooseParaWidget::slot_GoutMapChanged()
{
	emit sig_GoutMapChanged();
}

void QGooseParaWidget::SetRunState(int nRunState)
{
	m_nRunState = nRunState;

	if (m_tab_GoosePub != NULL)
	{
		SetRunState();
	}
}

void QGooseParaWidget::SetRunState()
{
	int num = m_pGoosePubList.size();

	for (int i =0; i < num; i++)
	{
		m_pGoosePubList[i]->SetRunState(m_nRunState);
	}
}

void QGooseParaWidget::SetTestCheckBox_Visible(BOOL bVisible)
{
	m_bTestCheckBox_Visible = bVisible;

	if (m_tab_GoosePub != NULL)
	{
		SetTestCheckBox_Visible();
	}
}

void QGooseParaWidget::SetTestCheckBox_Visible()
{
	int num = m_pGoosePubList.size();

	for (int i =0; i < num; i++)
	{
		m_pGoosePubList[i]->SetTestCheckBox_Visible(m_bTestCheckBox_Visible);
	}
}

void QGooseParaWidget::SetGooseDisabled( bool bFlag )
{
	m_bGooseDisabled = bFlag;

	if (m_tab_GoosePub != NULL)
	{
		SetGooseDisabled();
	}
}

void QGooseParaWidget::SetGooseDisabled()
{
	int num = m_pGoosePubList.size();

	for (int i =0; i < num; i++)
	{
		m_pGoosePubList[i]->chb_Invert->setDisabled(m_bGooseDisabled);
		m_pGoosePubList[i]->chb_Repair->setDisabled(m_bGooseDisabled);
		m_pGoosePubList[i]->m_pIecCfgGoutChsGrid->setDisabled(m_bGooseDisabled);
	}
}


void QGooseParaWidget::showEvent(QShowEvent *)
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
	SetTestCheckBox_Visible();//设置检修状态勾选框是否可见

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end QGooseParaWidget-  >>");	}
}

