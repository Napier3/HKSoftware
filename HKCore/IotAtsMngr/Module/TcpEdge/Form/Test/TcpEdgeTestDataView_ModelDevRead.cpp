#include "TcpEdgeTestDataView_ModelDevRead.h"
#include "../TcpEdgeUIGlobalDef.h"
#include "../../TcpEdgeGlobalDef.h"

CTcpEdgeTestDataView_ModelDevRead::CTcpEdgeTestDataView_ModelDevRead(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_ModelDevRead::~CTcpEdgeTestDataView_ModelDevRead()
{

}

void CTcpEdgeTestDataView_ModelDevRead::RecordToDataset()
{
	POS pos = m_pDevice->m_oRecord.m_models.GetHeadPosition();
	while (pos)
	{
		CModelRecord* pRecord = (CModelRecord*)m_pDevice->m_oRecord.m_models.GetNext(pos);
		ui.cbbModels->addItem(pRecord->m_strModelName);
	}			
}

void CTcpEdgeTestDataView_ModelDevRead::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);

	ui._Models_->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);

	connect(ui.btnAdd, SIGNAL(clicked(bool)), this, SLOT(slot_addDevice(bool)));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(slot_deleteDevice(bool)));
	connect(ui.__Models__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbModels(int)));
}

void CTcpEdgeTestDataView_ModelDevRead::slot_addDevice(bool bChecked)
{
	ui._Models_->insertRow(ui._Models_->rowCount());
	long nRow = ui._Models_->rowCount() - 1;
	ui._Models_->setItem(nRow, 0, new QTableWidgetItem(	ui.cbbModels->currentText()));
}

void CTcpEdgeTestDataView_ModelDevRead::slot_deleteDevice(bool bChecked)
{
	long nRow = ui._Models_->currentRow();
	ui._Models_->removeRow(nRow);
}

void CTcpEdgeTestDataView_ModelDevRead::slot_cbModels(int nState)
{
	if(nState)
	{
		ui.btnAdd->setEnabled(true);
		ui.btnDelete->setEnabled(true);
	}
	else
	{
		ui.btnAdd->setEnabled(false);
		ui.btnDelete->setEnabled(false);
	}

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_Models);
	pData->m_dwItemData = (DWORD)(nState != 0);
}

void CTcpEdgeTestDataView_ModelDevRead::OnOK()
{
	UIGetDataset(this, m_pProducePkg);
	UpdateDataset(PkgData_Node_Models);
}