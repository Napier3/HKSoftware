#include "TcpEdgeTestDataView_DeviceConfigReq.h"
#include "TcpEdgeTestCommonDlg.h"
#include "../TcpEdgeUIGlobalDef.h"
#include "../../TcpEdgeGlobalDef.h"

CTcpEdgeTestDataView_DeviceConfigReq::CTcpEdgeTestDataView_DeviceConfigReq(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_DeviceConfigReq::~CTcpEdgeTestDataView_DeviceConfigReq()
{

}

void CTcpEdgeTestDataView_DeviceConfigReq::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);

	connect(ui._Temperature_, SIGNAL(clicked()), this, SLOT(slot_editClicked()));
}

void CTcpEdgeTestDataView_DeviceConfigReq::slot_editClicked()
{
	CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_Temperature);
	CTcpEdgeTestCommonDlg dlg;
	dlg.m_pDevice = m_pDevice;
	dlg.InitUI(pDataset);
	if(dlg.exec("ÎÂ¶È¼à¿ØÐÅÏ¢±à¼­", pDataset) == QDialog::Accepted)
	{
		UIGetDataset(&dlg, pDataset);
		QString strText = QString("µÍÎÂãÐÖµ %1 & ¸ßÎÂãÐÖµ %2").arg(dlg.GetTemLow()).arg(dlg.GetTemHigh());
		ui._Temperature_->setText(strText);
	}
}

void CTcpEdgeTestDataView_DeviceConfigReq::RecordToDataset()
{
	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_DevName);
	if(pData)
	{
		pData->m_strValue = m_pDevice->m_oRecord.m_strDevName;
	}
	pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_CpuLmt);
	if(pData)
	{
		pData->m_strValue = m_pDevice->m_oRecord.m_strCpuLmt;
	}
	pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_MemLmt);
	if(pData)
	{
		pData->m_strValue = m_pDevice->m_oRecord.m_strMemLmt;
	}
	pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_DiskLmt);
	if(pData)
	{
		pData->m_strValue = m_pDevice->m_oRecord.m_strDiskLmt;
	}

	CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_Temperature);
	if(pDataset)
	{
		pData = (CDvmData*)pDataset->FindByID(PkgData_Node_TemHigh);
		if(pData)
		{
			pData->m_strValue = m_pDevice->m_oRecord.m_strTemHigh;
		}
		pData = (CDvmData*)pDataset->FindByID(PkgData_Node_TemLow);
		if(pData)
		{
			pData->m_strValue = m_pDevice->m_oRecord.m_strTemLow;
		}
	}
	QString strText = QString("µÍÎÂãÐÖµ %1 & ¸ßÎÂãÐÖµ %2").arg(m_pDevice->m_oRecord.m_strTemLow).arg(m_pDevice->m_oRecord.m_strTemHigh);
	ui._Temperature_->setText(strText);
}