#include "TcpEdgeTestCommonDlg.h"
#include "../../TcpEdgeGlobalDef.h"

CTcpEdgeTestCommonDlg::CTcpEdgeTestCommonDlg(QWidget *parent)
	: CTcpEdgeFormUI(parent)
{
	ui.setupUi(this);
	InitFormUI(this, ui.titleName);
}

CTcpEdgeTestCommonDlg::~CTcpEdgeTestCommonDlg()
{

}

void CTcpEdgeTestCommonDlg::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);

	ui.labelDisk->setVisible(false);
	ui.labelDisk_2->setVisible(false);
	ui.labelDisk_3->setVisible(false);
	ui.labelDisk_4->setVisible(false);
	ui._Disk_->setVisible(false);
	ui._DiskLmt_->setVisible(false);
	ui.__Disk__->setVisible(false);
	ui.__DiskLmt__->setVisible(false);
	ui.labelMem->setVisible(false);
	ui.labelMem_2->setVisible(false);
	ui.labelMem_3->setVisible(false);
	ui.labelMem_4->setVisible(false);
	ui._MemLmt_->setVisible(false);
	ui._Memory_->setVisible(false);
	ui.__MemLmt__->setVisible(false);
	ui.__Memory__->setVisible(false);
	ui.labelCpu->setVisible(false);
	ui.labelCpu_2->setVisible(false);
	ui.labelCpu_3->setVisible(false);
	ui._Cpus_->setVisible(false);
	ui._CpuLmt_->setVisible(false);
	ui.__Cpus__->setVisible(false);
	ui.__CpuLmt__->setVisible(false);
	ui.labelTem->setVisible(false);
	ui.labelTem_2->setVisible(false);
	ui._TemHigh_->setVisible(false);
	ui._TemLow_->setVisible(false);
	ui.__TemHigh__->setVisible(false);
	ui.__TemLow__->setVisible(false);

	if(m_pProducePkg->m_strID == PkgData_Node_Temperature)
	{
		ui.labelTem->setVisible(true);
		ui.labelTem_2->setVisible(true);
		ui._TemHigh_->setVisible(true);
		ui._TemLow_->setVisible(true);
		ui.__TemHigh__->setVisible(true);
		ui.__TemLow__->setVisible(true);
	}
	else if(m_pProducePkg->m_strID == PkgData_Node_CfgCpu)
	{
		ui.labelCpu->setVisible(true);
		ui.labelCpu_2->setVisible(true);
		ui.labelCpu_3->setVisible(true);
		ui._Cpus_->setVisible(true);
		ui._CpuLmt_->setVisible(true);
		ui.__Cpus__->setVisible(true);
		ui.__CpuLmt__->setVisible(true);
	}
	else if(m_pProducePkg->m_strID == PkgData_Node_CfgMem)
	{
		ui.labelMem->setVisible(true);
		ui.labelMem_2->setVisible(true);
		ui.labelMem_3->setVisible(true);
		ui.labelMem_4->setVisible(true);
		ui._MemLmt_->setVisible(true);
		ui._Memory_->setVisible(true);
		ui.__MemLmt__->setVisible(true);
		ui.__Memory__->setVisible(true);
	}
	else if(m_pProducePkg->m_strID == PkgData_Node_CfgDisk)
	{
		ui.labelDisk->setVisible(true);
		ui.labelDisk_2->setVisible(true);
		ui.labelDisk_3->setVisible(true);
		ui.labelDisk_4->setVisible(true);
		ui._Disk_->setVisible(true);
		ui._DiskLmt_->setVisible(true);
		ui.__Disk__->setVisible(true);
		ui.__DiskLmt__->setVisible(true);
	}

	adjustSize();
}

int CTcpEdgeTestCommonDlg::exec(const QString& strTitle, CExBaseList* pData)
{
	ui.titleName->setText(strTitle);
	return QDialog::exec();
}

QString CTcpEdgeTestCommonDlg::GetCpus()
{
	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_Cpus);
	if(pData)
	{
		return pData->m_strValue;
	}
	return "#err";
}

QString CTcpEdgeTestCommonDlg::GetCpuLmt()
{
	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_CpuLmt);
	if(pData)
	{
		return pData->m_strValue;
	}
	return "#err";
}

QString CTcpEdgeTestCommonDlg::GetMemory()
{
	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_Memory);
	if(pData)
	{
		return pData->m_strValue;
	}
	return "#err";
}

QString CTcpEdgeTestCommonDlg::GetMemLmt()
{
	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_MemLmt);
	if(pData)
	{
		return pData->m_strValue;
	}
	return "#err";
}

QString CTcpEdgeTestCommonDlg::GetDisk()
{
	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_Disk);
	if(pData)
	{
		return pData->m_strValue;
	}
	return "#err";
}

QString CTcpEdgeTestCommonDlg::GetDiskLmt()
{
	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_DiskLmt);
	if(pData)
	{
		return pData->m_strValue;
	}
	return "#err";
}

QString CTcpEdgeTestCommonDlg::GetTemLow()
{
	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_TemLow);
	if(pData)
	{
		return pData->m_strValue;
	}
	return "#err";
}

QString CTcpEdgeTestCommonDlg::GetTemHigh()
{
	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_TemHigh);
	if(pData)
	{
		return pData->m_strValue;
	}
	return "#err";
}

void CTcpEdgeTestCommonDlg::slot_autoConnected(int nState)
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