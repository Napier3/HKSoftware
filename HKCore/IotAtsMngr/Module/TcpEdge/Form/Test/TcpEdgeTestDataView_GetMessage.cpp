#include "TcpEdgeTestDataView_GetMessage.h"
#include "../TcpEdgeUIGlobalDef.h"
#include "../../TcpEdgeGlobalDef.h"

CTcpEdgeTestDataView_GetMessage::CTcpEdgeTestDataView_GetMessage(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_GetMessage::~CTcpEdgeTestDataView_GetMessage()
{

}

void CTcpEdgeTestDataView_GetMessage::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);

	disconnect(ui.__StartTime__, SIGNAL(stateChanged(int)), this, SLOT(slot_autoConnected(int)));
	connect(ui.__StartTime__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbStartTimeStateChanged(int)));
	connect(ui.cbStartTime, SIGNAL(stateChanged(int)), this, SLOT(slot_cbStartTimeStateChanged(int)));

	disconnect(ui.__EndTime__, SIGNAL(stateChanged(int)), this, SLOT(slot_autoConnected(int)));
	connect(ui.__EndTime__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbEndTimeStateChanged(int)));
	connect(ui.cbEndTime, SIGNAL(stateChanged(int)), this, SLOT(slot_cbEndTimeStateChanged(int)));

	UISetDataset(this, m_pProducePkg);

	QDateTime date = QDateTime::currentDateTime();
	ui._StartTime_->setDateTime(date);
	ui._EndTime_->setDateTime(date);
}

void CTcpEdgeTestDataView_GetMessage::slot_cbStartTimeStateChanged(int nState)
{
	bool bTime = ui.cbStartTime->isChecked();
	bool bTimeUsed = ui.__StartTime__->isChecked();

	if(bTimeUsed)
	{
		ui.cbStartTime->setEnabled(true);
	}
	else
	{
		ui.cbStartTime->setEnabled(false);
	}

	if(bTimeUsed && !bTime)
	{
		ui._StartTime_->setEnabled(true);
	}
	else
	{
		ui._StartTime_->setEnabled(false);
	}

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_StartTime);
	pData->m_dwItemData = (DWORD)bTimeUsed;
}

void CTcpEdgeTestDataView_GetMessage::slot_cbEndTimeStateChanged(int nState)
{
	bool bTime = ui.cbEndTime->isChecked();
	bool bTimeUsed = ui.__EndTime__->isChecked();

	if(bTimeUsed)
	{
		ui.cbEndTime->setEnabled(true);
	}
	else
	{
		ui.cbEndTime->setEnabled(false);
	}

	if(bTimeUsed && !bTime)
	{
		ui._EndTime_->setEnabled(true);
	}
	else
	{
		ui._EndTime_->setEnabled(false);
	}

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_EndTime);
	pData->m_dwItemData = (DWORD)bTimeUsed;
}