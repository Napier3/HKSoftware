#include "TcpEdgeTestDeviceDlg.h"
#include "TcpEdgeTestDevServiceDlg.h"
#include "TcpEdgeTestHisServiceDlg.h"
#include "../../Pkg/Pkg_DataReadDevSvc.h"
#include "../../Pkg/Pkg_GetHisData_DevSvc.h"

CTcpEdgeTestDeviceDlg::CTcpEdgeTestDeviceDlg(QWidget *parent)
	: CTcpEdgeFormUI(parent)
{
	ui.setupUi(this);
	InitFormUI(this, ui.titleName);
}

CTcpEdgeTestDeviceDlg::~CTcpEdgeTestDeviceDlg()
{

}

void CTcpEdgeTestDeviceDlg::RecordToDataset()
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

void CTcpEdgeTestDeviceDlg::InitUI(CDvmDataset* pDataset, const QString& strType)
{
	m_oTempDataset.m_strID = strType;
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();

	connect(ui.btnAdd, SIGNAL(clicked(bool)), this, SLOT(slot_addService(bool)));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(slot_deleteService(bool)));
	connect(ui.__Services__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbServices(int)));

	ui._Services_->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	ui._Services_->setColumnWidth(1, 100);
	ui._Services_->setEditTriggers(QAbstractItemView::NoEditTriggers);

	UISetDataset(this, m_pProducePkg);
	CDvmData* pDeviceId = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_DeviceID);
	ui._DeviceId_->lineEdit()->setText(pDeviceId->m_strValue);
	//初始化Services
	CDvmDatasetGroup* pGroup = (CDvmDatasetGroup*)m_pProducePkg->FindByID(PkgData_Node_Services);
	if(pGroup)
	{
		pGroup->CopyChildren(&m_oTempDataset);
		POS pos = m_oTempDataset.GetHeadPosition();
		while (pos)
		{
			CDvmDataset* pService = (CDvmDataset*)m_oTempDataset.GetNext(pos);
			ui._Services_->insertRow(ui._Services_->rowCount());
			long nRow = ui._Services_->rowCount() - 1;
			ui._Services_->setItem(nRow, 0, new QTableWidgetItem(pService->m_strName));
			QPushButton* pBtn = AddGridButton(ui._Services_, nRow, 1, "编辑");
			pBtn->setProperty("Service", QVariant::fromValue(pService));
			connect(pBtn, SIGNAL(clicked(bool)), this, SLOT(slot_editService(bool)));
		}

		ui.btnAdd->setEnabled(pGroup->m_dwItemData);
		ui.btnDelete->setEnabled(pGroup->m_dwItemData);
		ui._Services_->setEnabled(pGroup->m_dwItemData);
		ui.__Services__->setChecked(pGroup->m_dwItemData);
	}
	
	connect(ui.btnOK, SIGNAL(clicked(bool)), this, SLOT(slot_btnOK(bool)));
}

int CTcpEdgeTestDeviceDlg::exec(const QString& strTitle, CExBaseList* pData)
{
	ui.titleName->setText(strTitle);
	return QDialog::exec();
}

void CTcpEdgeTestDeviceDlg::slot_addService(bool bChecked)
{
	ui._Services_->insertRow(ui._Services_->rowCount());
	long nRow = ui._Services_->rowCount() - 1;
	ui._Services_->setItem(nRow, 0, new QTableWidgetItem());
	QPushButton* pBtn = AddGridButton(ui._Services_, nRow, 1, "编辑");
	connect(pBtn, SIGNAL(clicked(bool)), this, SLOT(slot_editService(bool)));

	CDvmDataset* pService = NULL;
	if (m_oTempDataset.m_strID == PkgData_GetHisData)
	{
		pService = CPkg_GetHisData_DevSvc::ToDataset();
	}
	else
	{
		pService = CPkg_DataReadDevSvc::ToDataset();
	}

	m_oTempDataset.AddNewChild(pService);
	pBtn->setProperty("Service", QVariant::fromValue(pService));
}

void CTcpEdgeTestDeviceDlg::slot_deleteService(bool bChecked)
{
	long nRow = ui._Services_->currentRow();
	ui._Services_->removeRow(nRow);
	if(nRow >= 0)
	{
		m_oTempDataset.Delete(nRow);
	}
}

void CTcpEdgeTestDeviceDlg::slot_editService(bool bChecked)
{
	QPushButton* pBtn = (QPushButton*)sender();
	QTableWidgetItem* pItem = pBtn->property("GridButtonRow").value<QTableWidgetItem*>();
	ui._Services_->selectRow(pItem->row());
	CDvmDataset* pDataset = pBtn->property("Service").value<CDvmDataset*>();

	if (m_oTempDataset.m_strID == PkgData_GetHisData)
	{
		CTcpEdgeTestHisServiceDlg dlg;
		dlg.m_pDevice = m_pDevice;
		dlg.InitUI(pDataset);
		if(dlg.exec("历史数据查询 - Device - Service", NULL) == QDialog::Accepted)
		{
			CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_ServiceId);
			pDataset->m_strName = pData->m_strValue;
			if(pData->m_dwItemData)
			{
				pItem->setText(pData->m_strValue);
			}
		}
	}
	else
	{
		CTcpEdgeTestDevServiceDlg dlg;
		dlg.m_strDeviceId = ui._DeviceId_->currentText();
		dlg.m_pDevice = m_pDevice;
		dlg.InitUI(pDataset);
		if(dlg.exec("数据查询 - Device - Service", NULL) == QDialog::Accepted)
		{
			CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_ServiceId);
			pDataset->m_strName = pData->m_strValue;
			if(pData->m_dwItemData)
			{
				pItem->setText(pData->m_strValue);
			}
		}
	}
}

void CTcpEdgeTestDeviceDlg::slot_cbServices(int nState)
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

void CTcpEdgeTestDeviceDlg::slot_autoConnected(int nState)
{
	QObject* pObj = sender();
	QString strName = pObj->objectName();
	long nStart = strName.indexOf("__") + 2;
	long nEnd = strName.lastIndexOf("__");
	QString strTempName = strName.mid(nStart, nEnd - nStart);
	QWidget* pTempObj = (QWidget*)findChild<QWidget*>("_" + strTempName + "_");

	if(!nState)
	{
		pTempObj->setEnabled(false);
	}
	else
	{
		pTempObj->setEnabled(true);
	}

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(strTempName);
	pData->m_dwItemData = (DWORD)(nState != 0);
}

void CTcpEdgeTestDeviceDlg::slot_btnOK(bool bChecked)
{
	UIGetDataset(this, m_pProducePkg);
	CDvmDatasetGroup* pGroup = (CDvmDatasetGroup*)m_pProducePkg->FindByID(PkgData_Node_Services);
	if(pGroup)
	{
		pGroup->DeleteAll();
		m_oTempDataset.CopyChildren(pGroup);
	}
	accept();
}