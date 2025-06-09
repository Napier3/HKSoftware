#include "TcpEdgeTestSubServiceDlg.h"
#include "TcpEdgeTestDataDlg.h"
#include "../../Pkg/Pkg_DataSubs_SubsSvcDL.h"

CTcpEdgeTestSubServiceDlg::CTcpEdgeTestSubServiceDlg(QWidget *parent)
	: CTcpEdgeFormUI(parent)
{
	ui.setupUi(this);
	InitFormUI(this, ui.titleName);
}

CTcpEdgeTestSubServiceDlg::~CTcpEdgeTestSubServiceDlg()
{

}

void CTcpEdgeTestSubServiceDlg::RecordToDataset()
{
	CModelRecord* pRecord = (CModelRecord*)m_pDevice->m_oRecord.m_models.FindByID(m_strModelName);
	if(pRecord)
	{
		
		POS posDev = pRecord->m_devs.GetHeadPosition();
		while (posDev)
		{
			CModelDeviceRecord* pDev = (CModelDeviceRecord*)pRecord->m_devs.GetNext(posDev);
			ui.cb_DeviceList->addItem(pDev->m_strDeviceId);
		}
	}
}

void CTcpEdgeTestSubServiceDlg::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();

	connect(ui.btnAdd, SIGNAL(clicked(bool)), this, SLOT(slot_addDevice(bool)));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(slot_deleteDevice(bool)));
	connect(ui.__DeviceList__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbDeviceList(int)));
	connect(ui.btnAdd2, SIGNAL(clicked(bool)), this, SLOT(slot_addData(bool)));
	connect(ui.btnDelete2, SIGNAL(clicked(bool)), this, SLOT(slot_deleteData(bool)));
	connect(ui.__DataList__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbDataList(int)));

	ui._DeviceList_->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);

	ui._DataList_->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	ui._DataList_->setColumnWidth(1, 100);
	ui._DataList_->setEditTriggers(QAbstractItemView::NoEditTriggers);

	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);
	CDvmData* pServiceId = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_ServiceId);
	ui._ServiceId_->lineEdit()->setText(pServiceId->m_strValue);
	//初始化DeviceList项目
	CDvmDatasetGroup* pGroup = (CDvmDatasetGroup*)m_pProducePkg->FindByID(PkgData_Node_DeviceList);
	if(pGroup)
	{
		POS pos = pGroup->GetHeadPosition();
		while (pos)
		{
			CDvmData* pData = (CDvmData*)pGroup->GetNext(pos);
			ui._DeviceList_->insertRow(ui._DeviceList_->rowCount());
			long nRow = ui._DeviceList_->rowCount() - 1;
			ui._DeviceList_->setItem(nRow, 0, new QTableWidgetItem(pData->m_strValue));
		}

		ui.btnAdd->setEnabled(pGroup->m_dwItemData);
		ui.btnDelete->setEnabled(pGroup->m_dwItemData);
		ui._DeviceList_->setEnabled(pGroup->m_dwItemData);
		ui.__DeviceList__->setChecked(pGroup->m_dwItemData);
	}
	//初始化DataList
	pGroup = (CDvmDatasetGroup*)m_pProducePkg->FindByID(PkgData_Node_DataList);
	if(pGroup)
	{
		pGroup->CopyChildren(&m_oTempDataset);
		POS pos = m_oTempDataset.GetHeadPosition();
		while (pos)
		{
			CDvmDataset* pData = (CDvmDataset*)m_oTempDataset.GetNext(pos);
			ui._DataList_->insertRow(ui._DataList_->rowCount());
			long nRow = ui._DataList_->rowCount() - 1;
			ui._DataList_->setItem(nRow, 0, new QTableWidgetItem(pData->m_strName));
			QPushButton* pBtn = AddGridButton(ui._DataList_, nRow, 1, "编辑");
			pBtn->setProperty("Data", QVariant::fromValue(pData));
			connect(pBtn, SIGNAL(clicked(bool)), this, SLOT(slot_editData(bool)));
		}

		ui.btnAdd2->setEnabled(pGroup->m_dwItemData);
		ui.btnDelete2->setEnabled(pGroup->m_dwItemData);
		ui._DataList_->setEnabled(pGroup->m_dwItemData);
		ui.__DataList__->setChecked(pGroup->m_dwItemData);
	}

	connect(ui.btnOK, SIGNAL(clicked(bool)), this, SLOT(slot_btnOK(bool)));
}

void CTcpEdgeTestSubServiceDlg::HideDataUI()
{
	ui._Spont_->setVisible(false);
	ui.__Spont__->setVisible(false);
	ui.labelSpont->setVisible(false);
	ui._Period_->setVisible(false);
	ui.__Period__->setVisible(false);
	ui.labelPeriod->setVisible(false);
	ui.labelPeriod2->setVisible(false);
	ui._AllData_->setVisible(false);
	ui.__AllData__->setVisible(false);
	ui.labelAllData->setVisible(false);
	ui.widgetDataList->setVisible(false);
	ui._DataList_->setVisible(false);
	ui.__DataList__->setVisible(false);
}

int CTcpEdgeTestSubServiceDlg::exec(const QString& strTitle, CExBaseList* pData)
{
	ui.titleName->setText(strTitle);
	return QDialog::exec();
}

void CTcpEdgeTestSubServiceDlg::slot_addDevice(bool bChecked)
{
	ui._DeviceList_->insertRow(ui._DeviceList_->rowCount());
	long nRow = ui._DeviceList_->rowCount() - 1;
	ui._DeviceList_->setItem(nRow, 0, new QTableWidgetItem());
	QString strTemp = ui.cb_DeviceList->currentText();
	QTableWidget *pObj = (QTableWidget*)ui._DeviceList_;
	pObj->item(nRow, 0)->setText(strTemp);

}

void CTcpEdgeTestSubServiceDlg::slot_deleteDevice(bool bChecked)
{
	long nRow = ui._DeviceList_->currentRow();
	ui._DeviceList_->removeRow(nRow);
}

void CTcpEdgeTestSubServiceDlg::slot_cbDeviceList(int nState)
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

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_DeviceList);
	pData->m_dwItemData = (DWORD)(nState != 0);
}

void CTcpEdgeTestSubServiceDlg::slot_addData(bool bChecked)
{
	ui._DataList_->insertRow(ui._DataList_->rowCount());
	long nRow = ui._DataList_->rowCount() - 1;
	ui._DataList_->setItem(nRow, 0, new QTableWidgetItem());
	QPushButton* pBtn = AddGridButton(ui._DataList_, nRow, 1, "编辑");
	connect(pBtn, SIGNAL(clicked(bool)), this, SLOT(slot_editData(bool)));

	CDvmDataset* pDataList = CPkg_DataSubs_SubsSvcDL::ToDataset();
	m_oTempDataset.AddNewChild(pDataList);
	pBtn->setProperty("Data", QVariant::fromValue(pDataList));
}

void CTcpEdgeTestSubServiceDlg::slot_deleteData(bool bChecked)
{
	long nRow = ui._DataList_->currentRow();
	ui._DataList_->removeRow(nRow);
	if(nRow >= 0)
	{
		m_oTempDataset.Delete(nRow);
	}
}

void CTcpEdgeTestSubServiceDlg::slot_editData(bool bChecked)
{
	QPushButton* pBtn = (QPushButton*)sender();
	QTableWidgetItem* pItem = pBtn->property("GridButtonRow").value<QTableWidgetItem*>();
	ui._DataList_->selectRow(pItem->row());
	CDvmDataset* pDataset = pBtn->property("Data").value<CDvmDataset*>();
	QString strType = ui._ServiceId_->currentText();
	CTcpEdgeTestDataDlg dlg;
	dlg.m_strType = strType.left(strType.indexOf(" "));
	dlg.m_strModelName = m_strModelName;
	dlg.m_pDevice = m_pDevice;
	dlg.InitUI(pDataset);
	if(dlg.exec("数据订阅 - Sub - Service - Data", NULL) == QDialog::Accepted)
	{
		UIGetDataset(&dlg, pDataset);
		CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_DataRefer);
		pDataset->m_strName = pData->m_strValue;
		if(pData->m_dwItemData)
		{
			pItem->setText(pData->m_strValue);
		}
	}
}

void CTcpEdgeTestSubServiceDlg::slot_cbDataList(int nState)
{
	if(nState)
	{
		ui.btnAdd2->setEnabled(true);
		ui.btnDelete2->setEnabled(true);
	}
	else
	{
		ui.btnAdd2->setEnabled(false);
		ui.btnDelete2->setEnabled(false);
	}

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_DataList);
	pData->m_dwItemData = (DWORD)(nState != 0);
}

void CTcpEdgeTestSubServiceDlg::slot_autoConnected(int nState)
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

void CTcpEdgeTestSubServiceDlg::slot_btnOK(bool bChecked)
{
	UIGetDataset(this, m_pProducePkg);

	CDvmDatasetGroup* pGroup = (CDvmDatasetGroup*)m_pProducePkg->FindByID(PkgData_Node_DeviceList);	
	if(pGroup)
	{
		pGroup->DeleteAll();
		for (int i = 0; i < ui._DeviceList_->rowCount(); i++)
		{
			CDvmData* pData = new CDvmData;
			pData->m_strID = pData->m_strName = pData->m_strValue = ui._DeviceList_->item(i, 0)->text();
			pGroup->AddNewChild(pData);
		}
	}

	pGroup = (CDvmDatasetGroup*)m_pProducePkg->FindByID(PkgData_Node_DataList);	
	if(pGroup)
	{
		pGroup->DeleteAll();
		m_oTempDataset.CopyChildren(pGroup);
	}
	accept();
}

