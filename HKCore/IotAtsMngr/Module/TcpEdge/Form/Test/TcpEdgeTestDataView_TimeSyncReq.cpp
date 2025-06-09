#include "TcpEdgeTestDataView_TimeSyncReq.h"
#include "../TcpEdgeUIGlobalDef.h"
#include "../../TcpEdgeGlobalDef.h"

CTcpEdgeTestDataView_TimeSyncReq::CTcpEdgeTestDataView_TimeSyncReq(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_TimeSyncReq::~CTcpEdgeTestDataView_TimeSyncReq()
{

}

void CTcpEdgeTestDataView_TimeSyncReq::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);

	disconnect(ui.__Time__, SIGNAL(stateChanged(int)), this, SLOT(slot_autoConnected(int)));
	connect(ui.__Time__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbTimeStateChanged(int)));
	connect(ui.cbTime, SIGNAL(stateChanged(int)), this, SLOT(slot_cbTimeStateChanged(int)));

	UISetDataset(this, m_pProducePkg);

	ui._Time_->setEnabled(false);

	QDateTime date = QDateTime::currentDateTime();
	ui._Time_->setDateTime(date);
}

void CTcpEdgeTestDataView_TimeSyncReq::slot_cbTimeStateChanged(int nState)
{
	bool bTime = ui.cbTime->isChecked();
	bool bTimeUsed = ui.__Time__->isChecked();

	if(bTimeUsed)
	{
		ui.cbTime->setEnabled(true);
	}
	else
	{
		ui.cbTime->setEnabled(false);
	}

	if(bTimeUsed && !bTime)
	{
		ui._Time_->setEnabled(true);
	}
	else
	{
		ui._Time_->setEnabled(false);
	}

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_Time);
	pData->m_dwItemData = (DWORD)bTimeUsed;
}