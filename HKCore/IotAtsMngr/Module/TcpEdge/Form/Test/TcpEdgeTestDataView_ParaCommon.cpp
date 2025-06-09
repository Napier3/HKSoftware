#include "TcpEdgeTestDataView_ParaCommon.h"
#include "../TcpEdgeUIGlobalDef.h"
#include "../../TcpEdgeGlobalDef.h"

CTcpEdgeTestDataView_ParaCommon::CTcpEdgeTestDataView_ParaCommon(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_ParaCommon::~CTcpEdgeTestDataView_ParaCommon()
{

}

void CTcpEdgeTestDataView_ParaCommon::RecordToDataset()
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

void CTcpEdgeTestDataView_ParaCommon::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();

	connect(ui.btnAdd, SIGNAL(clicked(bool)), this, SLOT(slot_addParaList(bool)));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(slot_deleteParaList(bool)));
	connect(ui.__ParaList__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbParaList(int)));
	connect(ui._DeviceId_, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slot_cbbParaList(const QString&)));

	ui._ParaList_->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);

	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);

	if(!m_pProducePkg->FindByID(PkgData_Node_ParaList))
	{
		ui._ParaList_->setVisible(false);
		ui.__ParaList__->setVisible(false);
		ui.cbbParaList->setVisible(false);
		ui.widgetParaList->setVisible(false);
		ui.btnAdd->setVisible(false);
		ui.btnDelete->setVisible(false);
	}
}

void CTcpEdgeTestDataView_ParaCommon::slot_addParaList(bool bChecked)
{
	ui._ParaList_->insertRow(ui._ParaList_->rowCount());
	long nRow = ui._ParaList_->rowCount() - 1;
	QString strText = ui.cbbParaList->currentText();
	ui._ParaList_->setItem(nRow, 0, new QTableWidgetItem(strText));
	ui._ParaList_->setItem(nRow, 1, new QTableWidgetItem());
}

void CTcpEdgeTestDataView_ParaCommon::slot_deleteParaList(bool bChecked)
{
	long nRow = ui._ParaList_->currentRow();
	ui._ParaList_->removeRow(nRow);
}

void CTcpEdgeTestDataView_ParaCommon::slot_cbParaList(int nState)
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

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_ParaList);
	if(pData)
	{
		pData->m_dwItemData = (DWORD)(nState != 0);
	}
}

void CTcpEdgeTestDataView_ParaCommon::slot_cbbParaList(const QString& strText)
{
	while (ui.cbbParaList->count())
	{
		ui.cbbParaList->removeItem(0);
	}

	CModelRecord* pRecord = m_pDevice->m_oRecord.FindModelByDeviceId(ui._DeviceId_->currentText());
	if(pRecord)
	{
		CDvmData* pServiceData = (CDvmData*)pRecord->m_datas.FindByID("parameter");
		if(pServiceData)
		{
			POS pos = pServiceData->GetHeadPosition();
			while (pos)
			{
				CDvmValue* pValue = (CDvmValue*)pServiceData->GetNext(pos);
				ui.cbbParaList->addItem(pValue->m_strID);
			}
		}
	}
}

void CTcpEdgeTestDataView_ParaCommon::OnOK()
{
	UIGetDataset(this, m_pProducePkg);

	QString strItemID = PkgData_Node_ParaList;
	QTableWidget* pObj = (QTableWidget*)findChild<QObject*>("_" + strItemID + "_");
	CDvmDatasetGroup* pGroup = (CDvmDatasetGroup*)m_pProducePkg->FindByID(strItemID);	
	if(pGroup)
	{
		pGroup->DeleteAll();
		for (int i = 0; i < pObj->rowCount(); i++)
		{
			CDvmDataset* pDataset = new CDvmDataset;
			CDvmData* pData = new CDvmData;
			pDataset->AddNewChild(pData);
			pData->m_dwItemData = 1;
			pData->m_dwReserved = 1;
			pData->m_strID = pData->m_strName = pObj->item(i, 0)->text();
			pData->m_strValue = pObj->item(i, 1)->text();
			pGroup->AddNewChild(pDataset);
		}
	}
}