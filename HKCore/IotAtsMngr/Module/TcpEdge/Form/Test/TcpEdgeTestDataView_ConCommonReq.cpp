#include "TcpEdgeTestDataView_ConCommonReq.h"
#include "../TcpEdgeUIGlobalDef.h"

CTcpEdgeTestDataView_ConCommonReq::CTcpEdgeTestDataView_ConCommonReq(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_ConCommonReq::~CTcpEdgeTestDataView_ConCommonReq()
{

}

void CTcpEdgeTestDataView_ConCommonReq::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);
}

void CTcpEdgeTestDataView_ConCommonReq::RecordToDataset()
{
	POS pos = m_pDevice->m_oRecord.m_containers.GetHeadPosition();
	while (pos)
	{
		CContianerRecord* pRecord = (CContianerRecord*)m_pDevice->m_oRecord.m_containers.GetNext(pos);
		ui._Container_->addItem(pRecord->m_strContainer);
	}
}