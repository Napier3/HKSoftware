#include "TcpEdgeTestHisDeviceDlg.h"

CTcpEdgeTestHisDeviceDlg::CTcpEdgeTestHisDeviceDlg(QWidget *parent)
	: CTcpEdgeFormUI(parent)
{
	ui.setupUi(this);
	InitFormUI(this, ui.titleName);
}

CTcpEdgeTestHisDeviceDlg::~CTcpEdgeTestHisDeviceDlg()
{

}

void CTcpEdgeTestHisDeviceDlg::RecordToDataset()
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

void CTcpEdgeTestHisDeviceDlg::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);

	QDateTime date = QDateTime::currentDateTime();
	ui._StartTime_->setDateTime(date);
	ui._EndTime_->setDateTime(date);

	connect(ui.btnOK, SIGNAL(clicked(bool)), this, SLOT(slot_btnOK(bool)));
}

int CTcpEdgeTestHisDeviceDlg::exec(const QString& strTitle, CExBaseList* pData)
{
	ui.titleName->setText(strTitle);
	return QDialog::exec();
}

void CTcpEdgeTestHisDeviceDlg::slot_autoConnected(int nState)
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

void CTcpEdgeTestHisDeviceDlg::slot_btnOK(bool bChecked)
{
	UIGetDataset(this, m_pProducePkg);
	accept();
}