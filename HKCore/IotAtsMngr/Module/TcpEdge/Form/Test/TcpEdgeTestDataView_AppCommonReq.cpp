#include "TcpEdgeTestDataView_AppCommonReq.h"
#include "../TcpEdgeUIGlobalDef.h"

CTcpEdgeTestDataView_AppCommonReq::CTcpEdgeTestDataView_AppCommonReq(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_AppCommonReq::~CTcpEdgeTestDataView_AppCommonReq()
{

}

void CTcpEdgeTestDataView_AppCommonReq::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);

	connect(ui._Container_, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slot_currentIndexChanged(const QString&)));
}

void CTcpEdgeTestDataView_AppCommonReq::RecordToDataset()
{
	POS pos = m_pDevice->m_oRecord.m_containers.GetHeadPosition();
	while (pos)
	{
		CContianerRecord* pRecord = (CContianerRecord*)m_pDevice->m_oRecord.m_containers.GetNext(pos);
		ui._Container_->addItem(pRecord->m_strContainer);
	}
}

void CTcpEdgeTestDataView_AppCommonReq::slot_currentIndexChanged(const QString& strText)
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