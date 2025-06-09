#include "QGooseOutCfgWidget.h"
#include "..\Module\ScrollCtrl\ScrollComboBox.h"

QGooseOutCfgWidget::QGooseOutCfgWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pSclStation = NULL;
	ui.setupUi(this);
	m_pIecGoutDataGrid = new CIecCfgGooseDataGrid(this);
	if (g_pSttGlobalFont != NULL)
	{
		m_pIecGoutDataGrid->setFont(*g_pSttGlobalFont);
		m_pIecGoutDataGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	}
	m_pIecGoutDataGrid->InitGrid();
	m_pIecGoutDataGrid->AttachDataViewOptrInterface(this);
	ui.m_VCbLayout->insertWidget(0,m_pIecGoutDataGrid);

	m_pIecCfgGOutChsGrid = new CIecCfgChsGrid(IECCFGGOUTCHSGRID,this);
	m_pIecCfgGOutChsGrid->InitGrid();
	ui.m_ChCfgLayout->addWidget(m_pIecCfgGOutChsGrid);
	bool ret = connect(m_pIecGoutDataGrid,SIGNAL(sig_Update_ChDatas(CExBaseList *)),
		this,SLOT(slot_UpdateCB_ChDatas(CExBaseList *)));
}

QGooseOutCfgWidget::~QGooseOutCfgWidget()
{

}

void QGooseOutCfgWidget::SetSCLStation(CSclStation *pSclStation)
{
	m_pSclStation = pSclStation;
}

void QGooseOutCfgWidget::initData(CIecCfgGoutDatas* IecCfgGoutDatas)
{
	ASSERT(IecCfgGoutDatas);
	m_pIecGoutDataGrid->ShowDatas(IecCfgGoutDatas);
	m_pIecGoutDataGrid->SelectRow(1);
}

void QGooseOutCfgWidget::OnDataSelChanged( QTableWidget *pGridCtrl, int nRow, int nCol )
{
	m_pIecGoutDataGrid->OnDataSelChanged(pGridCtrl, nRow, nCol);
}

void QGooseOutCfgWidget::slot_UpdateCB_ChDatas(CExBaseList *pCurrSelData)
{
	m_pIecCfgGOutChsGrid->UpdateChDatas(pCurrSelData);
}
