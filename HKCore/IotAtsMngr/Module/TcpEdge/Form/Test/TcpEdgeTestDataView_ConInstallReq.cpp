#include "TcpEdgeTestDataView_ConInstallReq.h"
#include "TcpEdgeTestCommonDlg.h"
#include "../TcpEdgeUIGlobalDef.h"
#include "../../TcpEdgeGlobalDef.h"

CTcpEdgeTestDataView_ConInstallReq::CTcpEdgeTestDataView_ConInstallReq(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_ConInstallReq::~CTcpEdgeTestDataView_ConInstallReq()
{

}

void CTcpEdgeTestDataView_ConInstallReq::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);

	if(m_strFunName == PkgData_ConInstallReq)
	{
		ui._Container_->setStyleSheet("QComboBox::drop-down" "border-style: none;"); 
	}
	else
	{
		connect(ui._Container_, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slot_currentIndexChanged(const QString&)));
	}

	ui._Port_->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	ui._Mount_->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	ui._Dev_->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);

	connect(ui._CfgCpu_, SIGNAL(clicked()), this, SLOT(slot_editCpuClicked()));
	connect(ui._CfgMem_, SIGNAL(clicked()), this, SLOT(slot_editMemClicked()));
	connect(ui._CfgDisk_, SIGNAL(clicked()), this, SLOT(slot_editDiskClicked()));

	connect(ui.btnAdd, SIGNAL(clicked(bool)), this, SLOT(slot_addPort(bool)));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(slot_deletePort(bool)));
	connect(ui.__Port__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbPort(int)));
	connect(ui.btnAdd2, SIGNAL(clicked(bool)), this, SLOT(slot_addMount(bool)));
	connect(ui.btnDelete2, SIGNAL(clicked(bool)), this, SLOT(slot_deleteMount(bool)));
	connect(ui.__Mount__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbMount(int)));
	connect(ui.btnAdd3, SIGNAL(clicked(bool)), this, SLOT(slot_addDev(bool)));
	connect(ui.btnDelete3, SIGNAL(clicked(bool)), this, SLOT(slot_deleteDev(bool)));
	connect(ui.__Dev__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbDev(int)));
}

void CTcpEdgeTestDataView_ConInstallReq::RecordToDataset()
{
	if(m_strFunName == PkgData_ConSetConfigReq)
	{
		POS pos = m_pDevice->m_oRecord.m_containers.GetHeadPosition();
		while (pos)
		{
			CContianerRecord* pRecord = (CContianerRecord*)m_pDevice->m_oRecord.m_containers.GetNext(pos);
			ui._Container_->addItem(pRecord->m_strContainer);
		}
	}
}

void CTcpEdgeTestDataView_ConInstallReq::slot_editCpuClicked()
{
	CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_CfgCpu);
	CTcpEdgeTestCommonDlg dlg;
	dlg.m_pDevice = m_pDevice;
	dlg.InitUI(pDataset);
	if(dlg.exec("CPU×ÊÔ´ÅäÖÃ±à¼­", pDataset) == QDialog::Accepted)
	{
 		UIGetDataset(&dlg, pDataset);
 		QString strText = QString("CPUºËÊý %1 & CPU¼à¿ØãÐÖµ %2").arg(dlg.GetCpus()).arg(dlg.GetCpuLmt());
 		ui._CfgCpu_->setText(strText);
	}
}

void CTcpEdgeTestDataView_ConInstallReq::slot_editMemClicked()
{
	CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_CfgMem);
	CTcpEdgeTestCommonDlg dlg;
	dlg.m_pDevice = m_pDevice;
	dlg.InitUI(pDataset);
	if(dlg.exec("ÄÚ´æ×ÊÔ´ÅäÖÃ±à¼­", pDataset) == QDialog::Accepted)
	{
		UIGetDataset(&dlg, pDataset);
		QString strText = QString("ÄÚ´æÏÞÖµ %1 & ÄÚ´æ¼à¿ØãÐÖµ %2").arg(dlg.GetMemory()).arg(dlg.GetMemLmt());
		ui._CfgMem_->setText(strText);
	}
}

void CTcpEdgeTestDataView_ConInstallReq::slot_editDiskClicked()
{
	CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_CfgDisk);
	CTcpEdgeTestCommonDlg dlg;
	dlg.m_pDevice = m_pDevice;
	dlg.InitUI(pDataset);
	if(dlg.exec("´ÅÅÌ×ÊÔ´ÅäÖÃ±à¼­", pDataset) == QDialog::Accepted)
	{
		UIGetDataset(&dlg, pDataset);
		QString strText = QString("Ó²ÅÌ´æ´¢ÏÞÖµ %1 & Ó²ÅÌ´æ´¢¼à¿ØãÐÖµ %2").arg(dlg.GetDisk()).arg(dlg.GetDiskLmt());
		ui._CfgDisk_->setText(strText);
	}
}

void CTcpEdgeTestDataView_ConInstallReq::slot_addPort(bool bChecked)
{
	ui._Port_->insertRow(ui._Port_->rowCount());
	long nRow = ui._Port_->rowCount() - 1;
	ui._Port_->setItem(nRow, 0, new QTableWidgetItem());
}

void CTcpEdgeTestDataView_ConInstallReq::slot_deletePort(bool bChecked)
{
	long nRow = ui._Port_->currentRow();
	ui._Port_->removeRow(nRow);
}

void CTcpEdgeTestDataView_ConInstallReq::slot_cbPort(int nState)
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

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_Port);
	pData->m_dwItemData = (DWORD)(nState != 0);
}

void CTcpEdgeTestDataView_ConInstallReq::slot_addMount(bool bChecked)
{
	ui._Mount_->insertRow(ui._Mount_->rowCount());
	long nRow = ui._Mount_->rowCount() - 1;
	ui._Mount_->setItem(nRow, 0, new QTableWidgetItem());
}

void CTcpEdgeTestDataView_ConInstallReq::slot_deleteMount(bool bChecked)
{
	long nRow = ui._Mount_->currentRow();
	ui._Mount_->removeRow(nRow);
}

void CTcpEdgeTestDataView_ConInstallReq::slot_cbMount(int nState)
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

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_Mount);
	pData->m_dwItemData = (DWORD)(nState != 0);
}

void CTcpEdgeTestDataView_ConInstallReq::slot_addDev(bool bChecked)
{
	ui._Dev_->insertRow(ui._Dev_->rowCount());
	long nRow = ui._Dev_->rowCount() - 1;
	ui._Dev_->setItem(nRow, 0, new QTableWidgetItem());
}

void CTcpEdgeTestDataView_ConInstallReq::slot_deleteDev(bool bChecked)
{
	long nRow = ui._Dev_->currentRow();
	ui._Dev_->removeRow(nRow);
}

void CTcpEdgeTestDataView_ConInstallReq::slot_cbDev(int nState)
{
	if(nState)
	{
		ui.btnAdd3->setEnabled(true);
		ui.btnDelete3->setEnabled(true);
	}
	else
	{
		ui.btnAdd3->setEnabled(false);
		ui.btnDelete3->setEnabled(false);
	}

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_Dev);
	pData->m_dwItemData = (DWORD)(nState != 0);
}

void CTcpEdgeTestDataView_ConInstallReq::OnOK()
{
	UIGetDataset(this, m_pProducePkg);
	UpdateDataset(PkgData_Node_Port);
	UpdateDataset(PkgData_Node_Mount);
	UpdateDataset(PkgData_Node_Dev);
}

void CTcpEdgeTestDataView_ConInstallReq::slot_currentIndexChanged(const QString& strText)
{
	CContianerRecord* pRecord = (CContianerRecord*)m_pDevice->m_oRecord.m_containers.FindByID(strText);
	if(pRecord)
	{
		CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_CfgCpu);
		if(pDataset)
		{
			CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_Cpus);
			if(pData)
			{
				pData->m_strValue = pRecord->m_strCpus;
			}
			pData = (CDvmData*)pDataset->FindByID(PkgData_Node_CpuLmt);
			if(pData)
			{
				pData->m_strValue = pRecord->m_strCpuLmt;
			}
			QString strText = QString("CPUºËÊý %1 & CPU¼à¿ØãÐÖµ %2").arg(pRecord->m_strCpus).arg(pRecord->m_strCpuLmt);
			ui._CfgCpu_->setText(strText);
		}

		pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_CfgMem);
		if(pDataset)
		{
			CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_Memory);
			if(pData)
			{
				pData->m_strValue = pRecord->m_strMemory;
			}
			pData = (CDvmData*)pDataset->FindByID(PkgData_Node_MemLmt);
			if(pData)
			{
				pData->m_strValue = pRecord->m_strMemLmt;
			}
			QString strText = QString("ÄÚ´æÏÞÖµ %1 & ÄÚ´æ¼à¿ØãÐÖµ %2").arg(pRecord->m_strMemory).arg(pRecord->m_strMemLmt);
			ui._CfgMem_->setText(strText);
		}

		pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_CfgDisk);
		if(pDataset)
		{
			CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_Disk);
			if(pData)
			{
				pData->m_strValue = pRecord->m_strDisk;
			}
			pData = (CDvmData*)pDataset->FindByID(PkgData_Node_DiskLmt);
			if(pData)
			{
				pData->m_strValue = pRecord->m_strDiskLmt;
			}
			QString strText = QString("Ó²ÅÌ´æ´¢ÏÞÖµ %1 & Ó²ÅÌ´æ´¢¼à¿ØãÐÖµ %2").arg(pRecord->m_strDisk).arg(pRecord->m_strDiskLmt);
			ui._CfgDisk_->setText(strText);
		}

		UpdateUI(PkgData_Node_Port, ui._Port_, pRecord->m_strPorts);
		UpdateUI(PkgData_Node_Mount, ui._Mount_, pRecord->m_strMounts);
		UpdateUI(PkgData_Node_Dev, ui._Dev_, pRecord->m_strDevs);
	}
}