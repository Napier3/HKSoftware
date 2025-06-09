#include "TcpEdgeTestDataView_StatusReq.h"
#include "../TcpEdgeUIGlobalDef.h"

CTcpEdgeTestDataView_StatusReq::CTcpEdgeTestDataView_StatusReq(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_StatusReq::~CTcpEdgeTestDataView_StatusReq()
{

}

void CTcpEdgeTestDataView_StatusReq::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);
}