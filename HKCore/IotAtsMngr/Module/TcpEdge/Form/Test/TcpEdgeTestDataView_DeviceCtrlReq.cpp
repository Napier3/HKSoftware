#include "TcpEdgeTestDataView_DeviceCtrlReq.h"
#include "../TcpEdgeUIGlobalDef.h"

CTcpEdgeTestDataView_DeviceCtrlReq::CTcpEdgeTestDataView_DeviceCtrlReq(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_DeviceCtrlReq::~CTcpEdgeTestDataView_DeviceCtrlReq()
{

}

void CTcpEdgeTestDataView_DeviceCtrlReq::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);
}