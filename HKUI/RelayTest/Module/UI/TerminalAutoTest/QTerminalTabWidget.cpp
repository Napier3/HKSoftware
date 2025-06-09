#include "QTerminalTabWidget.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include "../SttTestCntrFrameBase.h"

QTerminalTabWidget::QTerminalTabWidget(QWidget *parent):QWidget(parent)
{	
	m_pTabWidget = NULL;
	m_MuGooseBinGrid = NULL;
	m_MuBoutGooseGrid = NULL;
	m_SOEBoutGooseGrid = NULL;
	m_SOEGooseBinGrid = NULL;

	m_MuSoeWidget = NULL;
	m_nBoutIndex = 0;
	m_nBinIndex = 0;

	InitUI();
}

QTerminalTabWidget::~QTerminalTabWidget()
{
	m_oGooseBinList.RemoveAll();
	m_oBoutGooseList.RemoveAll();
	m_oSOEGooseBinList.RemoveAll();
	m_oSOEBoutGooseList.RemoveAll();
}

void QTerminalTabWidget::InitUI()
{
	m_pTabWidget = new QTabWidget(this);
	m_pTabWidget->setFont(*g_pSttGlobalFont);
	m_MuGooseBinGrid = new QTerminalGooseGrid(this);
	m_MuGooseBinGrid->setFont(*g_pSttGlobalFont);
	m_MuGooseBinGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_MuGooseBinGrid->InitGrid();

	m_MuBoutGooseGrid = new QTerminalGooseGrid(this);
	m_MuBoutGooseGrid->setFont(*g_pSttGlobalFont);
	m_MuBoutGooseGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_MuBoutGooseGrid->InitGrid();

	m_pTabWidget->insertTab(MU_TAB_TYPE_GOOSETOBIN,m_MuBoutGooseGrid,_T("GOOSE转开入"));
	m_pTabWidget->insertTab(MU_TAB_TYPE_BOUTTOGOOSE,m_MuGooseBinGrid,_T("开出转GOOSE"));


	QVBoxLayout *pMainLayout = new QVBoxLayout(this);
	CString strText;
	strText	=_T("SOE(开出转GOOSE):");
	QLabel *pLabel1 = new QLabel;
	pLabel1->setFont(*g_pSttGlobalFont);
	pLabel1->setText(strText);
	strText	=_T("SOE(GOOSE转开入):");
	QLabel *pLabel2 = new QLabel;
	pLabel2->setFont(*g_pSttGlobalFont);
	pLabel2->setText(strText);
	m_SOEBoutGooseGrid = new QTerminalGooseGrid(this);
	m_SOEBoutGooseGrid->setFont(*g_pSttGlobalFont);
	m_SOEBoutGooseGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_SOEBoutGooseGrid->InitGrid();
	m_SOEGooseBinGrid = new QTerminalGooseGrid(this);
	m_SOEGooseBinGrid->setFont(*g_pSttGlobalFont);
	m_SOEGooseBinGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_SOEGooseBinGrid->InitGrid();
	QVBoxLayout *pLayout1 = new QVBoxLayout;
	pLayout1->addWidget(pLabel1);
	pLayout1->addWidget(m_SOEGooseBinGrid);
	QVBoxLayout *pLayout2 = new QVBoxLayout;
	pLayout2->addWidget(pLabel2);
	pLayout2->addWidget(m_SOEBoutGooseGrid);
	pMainLayout->addLayout(pLayout2); //SOE表格顺序调整
	pMainLayout->addLayout(pLayout1);
	m_MuSoeWidget = new QWidget(this);
	m_MuSoeWidget->setLayout(pMainLayout);

	m_pTabWidget->insertTab(MU_TAB_TYPE_SOE,m_MuSoeWidget,_T("SOE测试"));

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(m_pTabWidget);
	setLayout(layout);
}


void QTerminalTabWidget::InitGoutData(CExBaseObject *pData)
{
	if (pData == NULL)
	{
		m_oBoutGooseList.RemoveAll();
		m_oSOEBoutGooseList.RemoveAll();
		m_nBoutIndex = 0;
		m_MuBoutGooseGrid->ShowDatas(&m_oBoutGooseList);
		m_SOEBoutGooseGrid->ShowDatas(&m_oSOEBoutGooseList);

		return;
	}
	CIecCfgGoutCh *pIecCfgGoutCh = NULL;

	if (pData->GetClassID() == CFGCLASSID_CIECCFGCHSGOUT)
	{
		m_oBoutGooseList.RemoveAll();
		m_oSOEBoutGooseList.RemoveAll();
		m_nBoutIndex = 0;
		CIecCfgGoutChs *pIecCfgGoutChs = (CIecCfgGoutChs*)pData;
		POS pos = pIecCfgGoutChs->GetHeadPosition();
		while(pos)
		{
			pIecCfgGoutCh = (CIecCfgGoutCh *)pIecCfgGoutChs->GetNext(pos);
			if (pIecCfgGoutCh->m_strDevChID.Find(_T("bin")) >= 0)
			{
				m_oBoutGooseList.AddNewChild(pIecCfgGoutCh);
				if(m_nBoutIndex < 3)
				{
					m_oSOEBoutGooseList.AddNewChild(pIecCfgGoutCh);
				}
				m_nBoutIndex ++;
			}
		}

		m_MuBoutGooseGrid->ShowDatas(&m_oBoutGooseList);

		if (m_nBoutIndex < 3)
		{
			m_SOEBoutGooseGrid->clearContents();
			m_SOEBoutGooseGrid->setRowCount(0);
		}
		else
		{
			m_SOEBoutGooseGrid->ShowDatas(&m_oSOEBoutGooseList);
		}
	}
}


void QTerminalTabWidget::InitGinData(CExBaseObject *pData)
{
	if (pData == NULL)
	{
		m_oGooseBinList.RemoveAll();
		m_oSOEGooseBinList.RemoveAll();
		m_nBinIndex = 0;
		m_MuGooseBinGrid->ShowDatas(&m_oGooseBinList);	
		m_SOEGooseBinGrid->ShowDatas(&m_oSOEGooseBinList);
		return;
	}
	CIecCfgGinCh *pIecCfgGinCh = NULL;

	if(pData->GetClassID() == CFGCLASSID_CIECCFGCHSGIN)
	{
		m_oGooseBinList.RemoveAll();
		m_oSOEGooseBinList.RemoveAll();
		m_nBinIndex = 0;
		CIecCfgGinChs *pIecCfgGinChs = (CIecCfgGinChs*)pData;
		POS pos = pIecCfgGinChs->GetHeadPosition();
		while(pos)
		{
			pIecCfgGinCh = (CIecCfgGinCh *)pIecCfgGinChs->GetNext(pos);

			if (pIecCfgGinCh->m_strDevChID.Find(_T("bout")) >= 0)
			{
				m_oGooseBinList.AddNewChild(pIecCfgGinCh);
				
				if(m_nBinIndex < 3)
				{
					m_oSOEGooseBinList.AddNewChild(pIecCfgGinCh);
				}
				m_nBinIndex ++ ;
			}
		}
		
		m_MuGooseBinGrid->ShowDatas(&m_oGooseBinList);	

		if (m_nBinIndex < 3)
		{
			m_SOEBoutGooseGrid->clearContents();
			m_SOEBoutGooseGrid->setRowCount(0);
		}
		else
		{
			m_SOEGooseBinGrid->ShowDatas(&m_oSOEGooseBinList);
		}
	}	
}


void QTerminalTabWidget::StartInit()
{
	m_MuGooseBinGrid->setDisabled(true);
	m_MuBoutGooseGrid->setDisabled(true);
	m_SOEGooseBinGrid->setDisabled(true);
	m_SOEBoutGooseGrid->setDisabled(true);
}

void QTerminalTabWidget::StopInit()
{
	m_MuGooseBinGrid->setDisabled(false);
	m_MuBoutGooseGrid->setDisabled(false);
	m_SOEGooseBinGrid->setDisabled(false);
	m_SOEBoutGooseGrid->setDisabled(false);
}