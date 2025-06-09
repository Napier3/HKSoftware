#include "TcpEdgeTestDataView_AppSetConfigReq.h"
#include "TcpEdgeTestCommonDlg.h"
#include "../TcpEdgeUIGlobalDef.h"
#include "../../TcpEdgeGlobalDef.h"

CTcpEdgeTestDataView_AppSetConfigReq::CTcpEdgeTestDataView_AppSetConfigReq(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_AppSetConfigReq::~CTcpEdgeTestDataView_AppSetConfigReq()
{

}

void CTcpEdgeTestDataView_AppSetConfigReq::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);

	connect(ui._CfgCpu_, SIGNAL(clicked()), this, SLOT(slot_editCpuClicked()));
	connect(ui._CfgMem_, SIGNAL(clicked()), this, SLOT(slot_editMemClicked()));
	connect(ui._Container_, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slot_currentIndexConChanged(const QString&)));
	connect(ui._App_, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slot_currentIndexAppChanged(const QString&)));
}

void CTcpEdgeTestDataView_AppSetConfigReq::slot_editCpuClicked()
{
	CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_CfgCpu);
	CTcpEdgeTestCommonDlg dlg;
	dlg.m_pDevice = m_pDevice;
	dlg.InitUI(pDataset);
	if(dlg.exec("CPU资源配置编辑", pDataset) == QDialog::Accepted)
	{
		UIGetDataset(&dlg, pDataset);
		QString strText = QString("CPU核数 %1 & CPU监控阈值 %2").arg(dlg.GetCpus()).arg(dlg.GetCpuLmt());
		ui._CfgCpu_->setText(strText);
	}
}

void CTcpEdgeTestDataView_AppSetConfigReq::slot_editMemClicked()
{
	CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_CfgMem);
	CTcpEdgeTestCommonDlg dlg;
	dlg.m_pDevice = m_pDevice;
	dlg.InitUI(pDataset);
	if(dlg.exec("内存资源配置编辑", pDataset) == QDialog::Accepted)
	{
		UIGetDataset(&dlg, pDataset);
		QString strText = QString("内存限值 %1 & 内存监控阈值 %2").arg(dlg.GetMemory()).arg(dlg.GetMemLmt());
		ui._CfgMem_->setText(strText);
	}
}

void CTcpEdgeTestDataView_AppSetConfigReq::RecordToDataset()
{
	POS pos = m_pDevice->m_oRecord.m_containers.GetHeadPosition();
	while (pos)
	{
		CContianerRecord* pRecord = (CContianerRecord*)m_pDevice->m_oRecord.m_containers.GetNext(pos);
		ui._Container_->addItem(pRecord->m_strContainer);
	}
}

void CTcpEdgeTestDataView_AppSetConfigReq::slot_currentIndexConChanged(const QString& strText)
{
	ui._App_->clear();
	CContianerRecord* pRecord = (CContianerRecord*)m_pDevice->m_oRecord.m_containers.FindByID(strText);
	if(pRecord)
	{
		POS pos = pRecord->m_apps.GetHeadPosition();
		while (pos)
		{
			CAppRecord* pAppRecord = (CAppRecord*)pRecord->m_apps.GetNext(pos);
			ui._App_->addItem(pAppRecord->m_strApp);
		}
	}
}

void CTcpEdgeTestDataView_AppSetConfigReq::slot_currentIndexAppChanged(const QString& strText)
{
	QString strConName = ui._Container_->currentText();
	CContianerRecord* pRecord = (CContianerRecord*)m_pDevice->m_oRecord.m_containers.FindByID(strConName);
	if(pRecord)
	{
		CAppRecord* pAppRecord = (CAppRecord*)pRecord->m_apps.FindByID(strText);
		if(pAppRecord)
		{
			CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_CfgCpu);
			if(pDataset)
			{
				CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_Cpus);
				if(pData)
				{
					pData->m_strValue = pAppRecord->m_strCpus;
				}
				pData = (CDvmData*)pDataset->FindByID(PkgData_Node_CpuLmt);
				if(pData)
				{
					pData->m_strValue = pAppRecord->m_strCpuLmt;
				}
				QString strText = QString("CPU核数 %1 & CPU监控阈值 %2").arg(pAppRecord->m_strCpus).arg(pAppRecord->m_strCpuLmt);
				ui._CfgCpu_->setText(strText);
			}

			pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_CfgMem);
			if(pDataset)
			{
				CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_Memory);
				if(pData)
				{
					pData->m_strValue = pAppRecord->m_strMemory;
				}
				pData = (CDvmData*)pDataset->FindByID(PkgData_Node_MemLmt);
				if(pData)
				{
					pData->m_strValue = pAppRecord->m_strMemLmt;
				}
				QString strText = QString("内存限值 %1 & 内存监控阈值 %2").arg(pAppRecord->m_strMemory).arg(pAppRecord->m_strMemLmt);
				ui._CfgMem_->setText(strText);
			}
		}
	}
}