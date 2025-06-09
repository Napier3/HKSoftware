#include "TcpEdgeTestDevServiceDlg.h"
#include "TcpEdgeTestDataDlg.h"
#include "../../TcpEdgeGlobalDef.h"

CTcpEdgeTestDevServiceDlg::CTcpEdgeTestDevServiceDlg(QWidget *parent)
	: CTcpEdgeFormUI(parent)
{
	ui.setupUi(this);
	m_bHasParameter = false;
	InitFormUI(this, ui.titleName);
}

CTcpEdgeTestDevServiceDlg::~CTcpEdgeTestDevServiceDlg()
{

}

void CTcpEdgeTestDevServiceDlg::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);

	connect(ui.btnAdd, SIGNAL(clicked(bool)), this, SLOT(slot_addData(bool)));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(slot_deleteData(bool)));
	connect(ui.__DataList__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbDataList(int)));

	ui._DataList_->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);

	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);
	CDvmData* pServiceId = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_ServiceId);
	ui._ServiceId_->lineEdit()->setText(pServiceId->m_strValue);
	//初始化DataList项目
	CDvmDatasetGroup* pGroup = (CDvmDatasetGroup*)m_pProducePkg->FindByID(PkgData_Node_DataList);
	if(pGroup)
	{
		POS pos = pGroup->GetHeadPosition();
		while (pos)
		{
			CDvmData* pData = (CDvmData*)pGroup->GetNext(pos);
			ui._DataList_->insertRow(ui._DataList_->rowCount());
			long nRow = ui._DataList_->rowCount() - 1;
			ui._DataList_->setItem(nRow, 0, new QTableWidgetItem(pData->m_strValue));
		}

		ui.btnAdd->setEnabled(pGroup->m_dwItemData);
		ui.btnDelete->setEnabled(pGroup->m_dwItemData);
		ui._DataList_->setEnabled(pGroup->m_dwItemData);
		ui.__DataList__->setChecked(pGroup->m_dwItemData);
	}

 	if(m_bHasParameter)
 	{
 		//ParaRead时ServiceId并不是默认的analog等,而是指定的Parameter
		while (ui._ServiceId_->count())
		{
			ui._ServiceId_->removeItem(0);
		}

		ui._ServiceId_->insertItem(0, "parameter (参数)");
		slot_currentIndexChanged("parameter");
 	}

	connect(ui._ServiceId_, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slot_currentIndexChanged(const QString&)));
	connect(ui.btnOK, SIGNAL(clicked(bool)), this, SLOT(slot_btnOK(bool)));
}

int CTcpEdgeTestDevServiceDlg::exec(const QString& strTitle, CExBaseList* pData)
{
	ui.titleName->setText(strTitle);
	return QDialog::exec();
}

void CTcpEdgeTestDevServiceDlg::slot_addData(bool bChecked)
{
	ui._DataList_->insertRow(ui._DataList_->rowCount());
	long nRow = ui._DataList_->rowCount() - 1;
	QString strText = ui.cbbDataList->currentText();
	ui._DataList_->setItem(nRow, 0, new QTableWidgetItem(strText));
}

void CTcpEdgeTestDevServiceDlg::slot_deleteData(bool bChecked)
{
	long nRow = ui._DataList_->currentRow();
	ui._DataList_->removeRow(nRow);
}

void CTcpEdgeTestDevServiceDlg::slot_cbDataList(int nState)
{
	if(nState)
	{
		ui.btnAdd->setEnabled(true);
		ui.btnDelete->setEnabled(true);
	}
	else
	{
		ui.btnAdd->setEnabled(false);
		ui.btnDelete->setEnabled(false);
	}

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_DataList);
	pData->m_dwItemData = (DWORD)(nState != 0);
}


void CTcpEdgeTestDevServiceDlg::slot_autoConnected(int nState)
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

void CTcpEdgeTestDevServiceDlg::slot_btnOK(bool bChecked)
{
	UIGetDataset(this, m_pProducePkg);

	CDvmDatasetGroup* pGroup = (CDvmDatasetGroup*)m_pProducePkg->FindByID(PkgData_Node_DataList);	
	if(pGroup)
	{
		pGroup->DeleteAll();
		for (int i = 0; i < ui._DataList_->rowCount(); i++)
		{
			CDvmData* pData = new CDvmData;
			pData->m_strID = pData->m_strName = pData->m_strValue = ui._DataList_->item(i, 0)->text();
			pGroup->AddNewChild(pData);
		}
	}

	accept();
}

void CTcpEdgeTestDevServiceDlg::slot_currentIndexChanged(const QString& strText)
{
	QString strType = strText;
	strType = strType.left(strType.indexOf(" "));

	while (ui.cbbDataList->count())
	{
		ui.cbbDataList->removeItem(0);
	}
	
	CModelRecord* pRecord = m_pDevice->m_oRecord.FindModelByDeviceId(m_strDeviceId);
	if(pRecord)
	{
		CDvmData* pServiceData = (CDvmData*)pRecord->m_datas.FindByID(strType);
		if(pServiceData)
		{
			POS pos = pServiceData->GetHeadPosition();
			while (pos)
			{
				CDvmValue* pValue = (CDvmValue*)pServiceData->GetNext(pos);
				ui.cbbDataList->addItem(pValue->m_strID);
			}
		}
	}
}