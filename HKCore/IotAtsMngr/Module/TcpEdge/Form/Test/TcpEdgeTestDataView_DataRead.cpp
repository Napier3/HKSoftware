#include "TcpEdgeTestDataView_DataRead.h"
#include "TcpEdgeTestDeviceDlg.h"
#include "../../Pkg/Pkg_DataReadDev.h"

CTcpEdgeTestDataView_DataRead::CTcpEdgeTestDataView_DataRead(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_DataRead::~CTcpEdgeTestDataView_DataRead()
{

}

void CTcpEdgeTestDataView_DataRead::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);

	connect(ui.btnAdd, SIGNAL(clicked(bool)), this, SLOT(slot_addDevice(bool)));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(slot_deleteDevice(bool)));
	connect(ui.__Devices__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbDevices(int)));

	ui._Devices_->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	ui._Devices_->setColumnWidth(1, 100);
	ui._Devices_->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QRect rc = geometry();
	setFixedSize(rc.width(), rc.height());

	UISetDataset(this, m_pProducePkg);
}

void CTcpEdgeTestDataView_DataRead::slot_addDevice(bool bChecked)
{
	ui._Devices_->insertRow(ui._Devices_->rowCount());
	long nRow = ui._Devices_->rowCount() - 1;
	ui._Devices_->setItem(nRow, 0, new QTableWidgetItem());
	QPushButton* pBtn = AddGridButton(ui._Devices_, nRow, 1, "±à¼­");
	connect(pBtn, SIGNAL(clicked(bool)), this, SLOT(slot_editDevice(bool)));

	CDvmDataset* pDev = CPkg_DataReadDev::ToDataset();
	m_oTempDataset.AddNewChild(pDev);
	pBtn->setProperty("Device", QVariant::fromValue(pDev));
}

void CTcpEdgeTestDataView_DataRead::slot_deleteDevice(bool bChecked)
{
	long nRow = ui._Devices_->currentRow();
	ui._Devices_->removeRow(nRow);
	if(nRow >= 0)
	{
		m_oTempDataset.Delete(nRow);
	}
}

void CTcpEdgeTestDataView_DataRead::slot_editDevice(bool bChecked)
{
	QPushButton* pBtn = (QPushButton*)sender();
	QTableWidgetItem* pItem = pBtn->property("GridButtonRow").value<QTableWidgetItem*>();
	ui._Devices_->selectRow(pItem->row());
	CDvmDataset* pDataset = pBtn->property("Device").value<CDvmDataset*>();
	CTcpEdgeTestDeviceDlg dlg;
	dlg.m_pDevice = m_pDevice;
	dlg.InitUI(pDataset, PkgData_DataRead);
	if(dlg.exec("Êý¾Ý²éÑ¯ - Device", NULL) == QDialog::Accepted)
	{
		CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_DeviceId);
		pDataset->m_strName = pData->m_strValue;
		if(pData->m_dwItemData)
		{
			pItem->setText(pData->m_strValue);
		}
	}
}

void CTcpEdgeTestDataView_DataRead::slot_cbDevices(int nState)
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

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_Devices);
	pData->m_dwItemData = (DWORD)(nState != 0);
}

void CTcpEdgeTestDataView_DataRead::OnOK()
{
	UIGetDataset(this, m_pProducePkg);
	UpdateDatasetGroup(PkgData_Node_Devices);
}