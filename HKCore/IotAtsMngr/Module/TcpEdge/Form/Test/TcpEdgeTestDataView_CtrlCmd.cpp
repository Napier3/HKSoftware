#include "TcpEdgeTestDataView_CtrlCmd.h"
#include "../TcpEdgeUIGlobalDef.h"
#include <QFileDialog>

CTcpEdgeTestDataView_CtrlCmd::CTcpEdgeTestDataView_CtrlCmd(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_CtrlCmd::~CTcpEdgeTestDataView_CtrlCmd()
{

}

void CTcpEdgeTestDataView_CtrlCmd::RecordToDataset()
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

void CTcpEdgeTestDataView_CtrlCmd::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);

	connect(ui._DeviceId_, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slot_currentIndexChanged(const QString&)));
}

void CTcpEdgeTestDataView_CtrlCmd::slot_currentIndexChanged(const QString& strText)
{
	while (ui._DataRefer_->count())
	{
		ui._DataRefer_->removeItem(0);
	}

	CModelRecord* pRecord = m_pDevice->m_oRecord.FindModelByDeviceId(ui._DeviceId_->currentText());
	if(pRecord)
	{
		CDvmData* pServiceData = (CDvmData*)pRecord->m_datas.FindByID("control");
		if(pServiceData)
		{
			POS pos = pServiceData->GetHeadPosition();
			while (pos)
			{
				CDvmValue* pValue = (CDvmValue*)pServiceData->GetNext(pos);
				ui._DataRefer_->addItem(pValue->m_strID);
			}
		}
	}
}