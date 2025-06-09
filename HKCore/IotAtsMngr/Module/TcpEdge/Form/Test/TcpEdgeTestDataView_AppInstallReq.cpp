#include "TcpEdgeTestDataView_AppInstallReq.h"
#include "TcpEdgeTestCommonDlg.h"
#include "../TcpEdgeUIGlobalDef.h"
#include "../../TcpEdgeGlobalDef.h"
#include <QFileDialog>

CTcpEdgeTestDataView_AppInstallReq::CTcpEdgeTestDataView_AppInstallReq(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_AppInstallReq::~CTcpEdgeTestDataView_AppInstallReq()
{

}

void CTcpEdgeTestDataView_AppInstallReq::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);

	connect(ui._CfgCpu_, SIGNAL(clicked()), this, SLOT(slot_editCpuClicked()));
	connect(ui._CfgMem_, SIGNAL(clicked()), this, SLOT(slot_editMemClicked()));

	disconnect(ui.__Name__, SIGNAL(stateChanged(int)), this, SLOT(slot_autoConnected(int)));
	disconnect(ui.__FileType__, SIGNAL(stateChanged(int)), this, SLOT(slot_autoConnected(int)));
	disconnect(ui.__Size__, SIGNAL(stateChanged(int)), this, SLOT(slot_autoConnected(int)));
	disconnect(ui.__Path__, SIGNAL(stateChanged(int)), this, SLOT(slot_autoConnected(int)));
	connect(ui.__Name__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbNameStateChanged(int)));
	connect(ui.__FileType__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbFileStateChanged(int)));
	connect(ui.__Size__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbFileStateChanged(int)));
	connect(ui.__Path__, SIGNAL(stateChanged(int)), this, SLOT(slot_cbFileStateChanged(int)));
	connect(ui.btnName, SIGNAL(clicked(bool)), this, SLOT(slot_btnNameClicked(bool)));
	connect(ui._File_, SIGNAL(clicked(bool)), this, SLOT(slot_groupFileClicked(bool)));
}

void CTcpEdgeTestDataView_AppInstallReq::RecordToDataset()
{
	POS pos = m_pDevice->m_oRecord.m_containers.GetHeadPosition();
	while (pos)
	{
		CContianerRecord* pRecord = (CContianerRecord*)m_pDevice->m_oRecord.m_containers.GetNext(pos);
		ui._Container_->addItem(pRecord->m_strContainer);
	}
}

void CTcpEdgeTestDataView_AppInstallReq::slot_editCpuClicked()
{
	CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_CfgCpu);
	CTcpEdgeTestCommonDlg dlg;
	dlg.m_pDevice = m_pDevice;
	dlg.InitUI(pDataset);
	if(dlg.exec("CPU资源配置编辑", pDataset) == QDialog::Accepted)
	{
 		UIGetDataset(&dlg, pDataset);
 		QString strText = QString("CPU核数 %1 & CPU监控阈值 %2").arg(dlg.GetCpus()).arg(dlg.GetCpuLmt());
 		ui._CfgCpu_->setText(strText);
	}
}

void CTcpEdgeTestDataView_AppInstallReq::slot_editMemClicked()
{
	CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_CfgMem);
	CTcpEdgeTestCommonDlg dlg;
	dlg.m_pDevice = m_pDevice;
	dlg.InitUI(pDataset);
	if(dlg.exec("内存资源配置编辑", pDataset) == QDialog::Accepted)
	{
		UIGetDataset(&dlg, pDataset);
		QString strText = QString("内存限值 %1 & 内存监控阈值 %2").arg(dlg.GetMemory()).arg(dlg.GetMemLmt());
		ui._CfgMem_->setText(strText);
	}
}

void CTcpEdgeTestDataView_AppInstallReq::slot_cbNameStateChanged(int nState)
{
	if(nState)
	{
		ui._Name_->setEnabled(true);
		ui.btnName->setEnabled(true);
	}
	else
	{
		ui._Name_->setEnabled(false);
		ui.btnName->setEnabled(false);
	}

	CDvmDataset* pFile= (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_File);
	CDvmData* pData = (CDvmData*)pFile->FindByID(PkgData_Node_Name);
	pData->m_dwItemData = (DWORD)(nState != 0);
}

void CTcpEdgeTestDataView_AppInstallReq::slot_cbFileStateChanged(int nState)
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

	CDvmDataset* pFile= (CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_File);
	CDvmData* pData = (CDvmData*)pFile->FindByID(strTempName);
	pData->m_dwItemData = (DWORD)(nState != 0);
}

void CTcpEdgeTestDataView_AppInstallReq::slot_btnNameClicked(bool bChecked)
{
	QString strFileName = QFileDialog::getOpenFileName(this, "选择文件", ".", "文件(*.*)");
	QFileInfo file(strFileName);
	ui._Name_->setText(file.baseName());
	ui._FileType_->setText(file.completeSuffix());
	ui._Path_->setText(strFileName);
	QString strSize = QString("%1").arg(file.size());
	ui._Size_->setText(strSize);
}

void CTcpEdgeTestDataView_AppInstallReq::slot_groupFileClicked(bool bChecked)
{
	QWidget* pWidget = (QWidget*)sender();
	QList<QCheckBox*>list = pWidget->findChildren<QCheckBox*>();
	for (int i = 0; i < list.size(); i++)
	{
		QString strObjName = list[i]->objectName();
		if(strObjName.indexOf("__") == 0)
		{
			list[i]->setChecked(bChecked);
		}
	}

	QString strName = pWidget->objectName();
	long nStart = strName.indexOf("_") + 1;
	long nEnd = strName.lastIndexOf("_");
	QString strTempName = strName.mid(nStart, nEnd - nStart);
	CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(strTempName);
	pDataset->m_dwItemData = bChecked == true;
}