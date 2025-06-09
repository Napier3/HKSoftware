#include "stdafx.h"
#include "TcpEdgeTestHeaderView.h"
#include "TcpEdgeUIGlobalDef.h"
#include "../TcpEdgeGlobalDef.h"

CTcpEdgeTestHeaderView::CTcpEdgeTestHeaderView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_pProducePkg = NULL;
}

CTcpEdgeTestHeaderView::~CTcpEdgeTestHeaderView()
{

}

void CTcpEdgeTestHeaderView::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);

	disconnect(ui.__Timestamp__, SIGNAL(stateChanged(int)), this, SLOT(slot_autoConnected(int)));
	connect(ui.__Timestamp__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbTimeStateChanged(int)));
	connect(ui.cbTime, SIGNAL(stateChanged(int)), this, SLOT(slot_cbTimeStateChanged(int)));

	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);
	ui._Timestamp_->setEnabled(false);
}

void CTcpEdgeTestHeaderView::slot_cbTimeStateChanged(int nState)
{
	bool bTime = ui.cbTime->isChecked();
	bool bTimeUsed = ui.__Timestamp__->isChecked();

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
		ui._Timestamp_->setEnabled(true);
	}
	else
	{
		ui._Timestamp_->setEnabled(false);
	}

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_Timestamp);
	pData->m_dwItemData = (DWORD)bTimeUsed;
}

void CTcpEdgeTestHeaderView::slot_autoConnected(int nState)
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