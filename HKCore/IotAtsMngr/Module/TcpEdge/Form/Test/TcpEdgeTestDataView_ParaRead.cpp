#include "TcpEdgeTestDataView_ParaRead.h"
#include "TcpEdgeTestDevServiceDlg.h"
#include "../../Pkg/Pkg_ParaReadSvc.h"



CTcpEdgeTestDataView_ParaRead::CTcpEdgeTestDataView_ParaRead(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_ParaRead::~CTcpEdgeTestDataView_ParaRead()
{

}

void CTcpEdgeTestDataView_ParaRead::RecordToDataset()
{
	POS pos = m_pDevice->m_oRecord.m_models.GetHeadPosition();
	while (pos)
	{
		CModelRecord* pRecord = (CModelRecord*)m_pDevice->m_oRecord.m_models.GetNext(pos);
		POS posDev = pRecord->m_devs.GetHeadPosition();
		while (posDev)
		{
			CModelDeviceRecord* pDev = (CModelDeviceRecord*)pRecord->m_devs.GetNext(posDev);
			ui._DeviceId_->addItem(pDev->m_strDeviceId);
		}
	}			
}

void CTcpEdgeTestDataView_ParaRead::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();

	connect(ui.btnAdd, SIGNAL(clicked(bool)), this, SLOT(slot_addService(bool)));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(slot_deleteService(bool)));
	connect(ui.__Services__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbServices(int)));

	ui._Services_->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	ui._Services_->setColumnWidth(1, 100);
	ui._Services_->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QRect rc = geometry();
	setFixedSize(rc.width(), rc.height());

	UISetDataset(this, m_pProducePkg);
}

void CTcpEdgeTestDataView_ParaRead::slot_addService(bool bChecked)
{
	ui._Services_->insertRow(ui._Services_->rowCount());
	long nRow = ui._Services_->rowCount() - 1;
	ui._Services_->setItem(nRow, 0, new QTableWidgetItem());
	QPushButton* pBtn = AddGridButton(ui._Services_, nRow, 1, "编辑");
	connect(pBtn, SIGNAL(clicked(bool)), this, SLOT(slot_editService(bool)));

	CDvmDataset* pService = CPkg_ParaReadSvc::ToDataset();
	m_oTempDataset.AddNewChild(pService);
	pBtn->setProperty("Service", QVariant::fromValue(pService));
}

void CTcpEdgeTestDataView_ParaRead::slot_deleteService(bool bChecked)
{
	long nRow = ui._Services_->currentRow();
	ui._Services_->removeRow(nRow);
	if(nRow >= 0)
	{
		m_oTempDataset.Delete(nRow);
	}
}

void CTcpEdgeTestDataView_ParaRead::slot_editService(bool bChecked)
{
	QPushButton* pBtn = (QPushButton*)sender();
	QTableWidgetItem* pItem = pBtn->property("GridButtonRow").value<QTableWidgetItem*>();
	ui._Services_->selectRow(pItem->row());
	CDvmDataset* pDataset = pBtn->property("Service").value<CDvmDataset*>();
	CTcpEdgeTestDevServiceDlg dlg;
	dlg.m_strDeviceId = ui._DeviceId_->currentText();
	dlg.m_bHasParameter = true;
	dlg.m_pDevice = m_pDevice;
	dlg.InitUI(pDataset);
	if(dlg.exec("定值参数查询 - Service", NULL) == QDialog::Accepted)
	{
		CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_ServiceId);
		pDataset->m_strName = pData->m_strValue;
		if(pData->m_dwItemData)
		{
			pItem->setText(pData->m_strValue);
		}
	}
}

void CTcpEdgeTestDataView_ParaRead::slot_cbServices(int nState)
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

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_Services);
	pData->m_dwItemData = (DWORD)(nState != 0);
}

void CTcpEdgeTestDataView_ParaRead::OnOK()
{
	UIGetDataset(this, m_pProducePkg);
	UpdateDatasetGroup(PkgData_Node_Services);
}