#include "TcpEdgeTestDataDlg.h"

CTcpEdgeTestDataDlg::CTcpEdgeTestDataDlg(QWidget *parent)
	: CTcpEdgeFormUI(parent)
{
	ui.setupUi(this);
	InitFormUI(this, ui.titleName);
}

CTcpEdgeTestDataDlg::~CTcpEdgeTestDataDlg()
{

}

void CTcpEdgeTestDataDlg::RecordToDataset()
{
	CModelRecord* pRecord = (CModelRecord*)m_pDevice->m_oRecord.m_models.FindByID(m_strModelName);
	if(pRecord)
	{
		CDvmData* pServiceData = (CDvmData*)pRecord->m_datas.FindByID(m_strType);
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

void CTcpEdgeTestDataDlg::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);
	CDvmData* pDataRefer = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_DataRefer);
	ui._DataRefer_->lineEdit()->setText(pDataRefer->m_strValue);
}

int CTcpEdgeTestDataDlg::exec(const QString& strTitle, CExBaseList* pData)
{
	ui.titleName->setText(strTitle);
	return QDialog::exec();
}

void CTcpEdgeTestDataDlg::slot_autoConnected(int nState)
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