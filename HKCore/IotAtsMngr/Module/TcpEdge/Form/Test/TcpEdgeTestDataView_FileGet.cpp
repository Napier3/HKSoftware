#include "TcpEdgeTestDataView_FileGet.h"
#include "../TcpEdgeUIGlobalDef.h"
#include "../../TcpEdgeGlobalDef.h"
#include <QFileDialog>

CTcpEdgeTestDataView_FileGet::CTcpEdgeTestDataView_FileGet(QWidget *parent)
	: CTcpEdgeTestDataView(parent)
{
	ui.setupUi(this);
}

CTcpEdgeTestDataView_FileGet::~CTcpEdgeTestDataView_FileGet()
{

}

void CTcpEdgeTestDataView_FileGet::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
	UIAutoConnect(this);
	RecordToDataset();
	UIAutoInitValue(this);
	UISetDataset(this, m_pProducePkg);

	if(m_strRelFunName != PkgData_FileGet)
	{
		ui.rdMngrChannel->setVisible(false);
		ui.rdDataChannel->setVisible(false);
		ui.labelChannel->setVisible(false);
	}

	connect(ui.rdMngrChannel, SIGNAL(clicked(bool)), this, SLOT(slot_clicked(bool)));
	connect(ui.rdDataChannel, SIGNAL(clicked(bool)), this, SLOT(slot_clicked(bool)));
}

void CTcpEdgeTestDataView_FileGet::RecordToDataset()
{
	if(m_strFunName == "FileModelGet")
	{
		POS pos = m_pDevice->m_oRecord.m_models.GetHeadPosition();
		while (pos)
		{
			CModelRecord* pRecord = (CModelRecord*)m_pDevice->m_oRecord.m_models.GetNext(pos);
			ui._FullPathFileName_->addItem(pRecord->m_strFullPathFileName);
		}
	}
	else if (m_strFunName == "FileTopoGet")
	{
		for (int i = 0; i < m_pDevice->m_oRecord.m_strTopofiles.count(); i++)
		{
			ui._FullPathFileName_->addItem(m_pDevice->m_oRecord.m_strTopofiles.at(i));
		}
	}
	else if (m_strFunName == "FileMessageGet")
	{
		for (int i = 0; i < m_pDevice->m_oRecord.m_strMessagefiles.count(); i++)
		{
			ui._FullPathFileName_->addItem(m_pDevice->m_oRecord.m_strMessagefiles.at(i));
		}
	}

	m_strFunName = PkgData_FileGet;
}

void CTcpEdgeTestDataView_FileGet::slot_clicked(bool bChecked)
{
	if(sender() == ui.rdMngrChannel)
	{
		m_bIsMngrCh = true;
	}
	else
	{
		m_bIsMngrCh = false;
	}
}