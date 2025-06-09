#include "QGooseInCfgWidget.h"
#include "..\Module\ScrollCtrl\ScrollComboBox.h"
#include "IecCfgGooseDataGrid.h"

QGooseInCfgWidget::QGooseInCfgWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pSclStation = NULL;
	ui.setupUi(this);
	m_pIecCfgGooseInDataGrid = new CIecCfgGooseDataGrid(this);
	if (g_pSttGlobalFont != NULL)
	{
		m_pIecCfgGooseInDataGrid->setFont(*g_pSttGlobalFont);
		m_pIecCfgGooseInDataGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	}
	m_pIecCfgGooseInDataGrid->InitGrid();
	m_pIecCfgGooseInDataGrid->AttachDataViewOptrInterface(this);
	ui.m_VCbLayout->insertWidget(0,m_pIecCfgGooseInDataGrid);

	m_pIecCfgGInChsGrid = new CIecCfgChsGrid(IECCFGGINCHSGRID, this);
	m_pIecCfgGInChsGrid->InitGrid();
	ui.m_ChCfgLayout->addWidget(m_pIecCfgGInChsGrid);
	bool ret = connect(m_pIecCfgGooseInDataGrid,SIGNAL(sig_Update_ChDatas(CExBaseList *)),
		this,SLOT(slot_UpdateCB_ChDatas(CExBaseList *)));
}

QGooseInCfgWidget::~QGooseInCfgWidget()
{

}

void QGooseInCfgWidget::SetSCLStation(CSclStation *pSclStation)
{
	m_pSclStation = pSclStation;
}

void QGooseInCfgWidget::initData(CIecCfgGinDatas* pIecCfgGinDatas)
{
	ASSERT(pIecCfgGinDatas);
	m_pIecCfgGooseInDataGrid->ShowDatas(pIecCfgGinDatas);
	m_pIecCfgGooseInDataGrid->SelectRow(1);
}

void QGooseInCfgWidget::OnDataSelChanged( QTableWidget *pGridCtrl, int nRow, int nCol )
{
	m_pIecCfgGooseInDataGrid->OnDataSelChanged(pGridCtrl, nRow, nCol);
}

void QGooseInCfgWidget::slot_UpdateCB_ChDatas( CExBaseList *pCurrSelData )
{
	m_pIecCfgGInChsGrid->UpdateChDatas(pCurrSelData);
}
