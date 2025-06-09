#include "TcpEdgeTestHisServiceDlg.h"

CTcpEdgeTestHisServiceDlg::CTcpEdgeTestHisServiceDlg(QWidget *parent)
	: CTcpEdgeFormUI(parent)
{
	ui.setupUi(this);
	InitFormUI(this, ui.titleName);
}

CTcpEdgeTestHisServiceDlg::~CTcpEdgeTestHisServiceDlg()
{

}

void CTcpEdgeTestHisServiceDlg::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);
	CDvmData* pServiceId = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_ServiceId);
	ui._ServiceId_->lineEdit()->setText(pServiceId->m_strValue);

	QDateTime date = QDateTime::currentDateTime();
	ui._StartTime_->setDateTime(date);
	ui._EndTime_->setDateTime(date);

	connect(ui.btnOK, SIGNAL(clicked(bool)), this, SLOT(slot_btnOK(bool)));
}

int CTcpEdgeTestHisServiceDlg::exec(const QString& strTitle, CExBaseList* pData)
{
	ui.titleName->setText(strTitle);
	return QDialog::exec();
}

void CTcpEdgeTestHisServiceDlg::slot_autoConnected(int nState)
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

void CTcpEdgeTestHisServiceDlg::slot_btnOK(bool bChecked)
{
	UIGetDataset(this, m_pProducePkg);
	accept();
}