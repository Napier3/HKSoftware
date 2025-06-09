#include "TcpEdgeTestDataView_DataSubs.h"
#include "TcpEdgeTestSubDlg.h"
#include "../../Pkg/Pkg_DatSubs_Sub.h"

CTcpEdgeTestDataView_DataSubs::CTcpEdgeTestDataView_DataSubs(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_DataSubs::~CTcpEdgeTestDataView_DataSubs()
{

}

void CTcpEdgeTestDataView_DataSubs::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);

	connect(ui.btnAdd, SIGNAL(clicked(bool)), this, SLOT(slot_addSub(bool)));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(slot_deleteSub(bool)));
	connect(ui.__Subs__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbSubs(int)));

	ui._Subs_->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	ui._Subs_->setColumnWidth(1, 100);
	ui._Subs_->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QRect rc = geometry();
	setFixedSize(rc.width(), rc.height());

	UISetDataset(this, m_pProducePkg);
}

void CTcpEdgeTestDataView_DataSubs::slot_addSub(bool bChecked)
{
	ui._Subs_->insertRow(ui._Subs_->rowCount());
	long nRow = ui._Subs_->rowCount() - 1;
	ui._Subs_->setItem(nRow, 0, new QTableWidgetItem());
	QPushButton* pBtn = AddGridButton(ui._Subs_, nRow, 1, "±à¼­");
	connect(pBtn, SIGNAL(clicked(bool)), this, SLOT(slot_editSub(bool)));

	CDvmDataset* pSub = CPkg_DatSubs_Sub::ToDataset();
	m_oTempDataset.AddNewChild(pSub);
	pBtn->setProperty("Sub", QVariant::fromValue(pSub));
}

void CTcpEdgeTestDataView_DataSubs::slot_deleteSub(bool bChecked)
{
	long nRow = ui._Subs_->currentRow();
	ui._Subs_->removeRow(nRow);
	if(nRow >= 0)
	{
		m_oTempDataset.Delete(nRow);
	}
}

void CTcpEdgeTestDataView_DataSubs::slot_editSub(bool bChecked)
{
	QPushButton* pBtn = (QPushButton*)sender();
	QTableWidgetItem* pItem = pBtn->property("GridButtonRow").value<QTableWidgetItem*>();
	ui._Subs_->selectRow(pItem->row());
	CDvmDataset* pDataset = pBtn->property("Sub").value<CDvmDataset*>();
	CTcpEdgeTestSubDlg dlg;
	dlg.m_pDevice = m_pDevice;
	dlg.InitUI(pDataset, PkgData_DataSubs);
	if(dlg.exec("Êý¾Ý¶©ÔÄ - Sub", NULL) == QDialog::Accepted)
	{
		CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_Model);
		pDataset->m_strName = pData->m_strValue;
		if(pData->m_dwItemData)
		{
			pItem->setText(pData->m_strValue);
		}
	}
}

void CTcpEdgeTestDataView_DataSubs::slot_cbSubs(int nState)
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

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(PkgData_Node_Subs);
	pData->m_dwItemData = (DWORD)(nState != 0);
}

void CTcpEdgeTestDataView_DataSubs::OnOK()
{
	UIGetDataset(this, m_pProducePkg);
	UpdateDatasetGroup(PkgData_Node_Subs);
}