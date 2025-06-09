#include "TcpEdgeTestDataView.h"
#include "TcpEdgeUIGlobalDef.h"
#include <QHBoxLayout>
#include <QGraphicsBlurEffect>
#include <QLineEdit>

CTcpEdgeTestDataView::CTcpEdgeTestDataView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_pProducePkg = NULL;
	m_pDevice = NULL;
	m_bIsMngrCh = true;
}

CTcpEdgeTestDataView::~CTcpEdgeTestDataView()
{

}

void CTcpEdgeTestDataView::InitUI(CDvmDataset* pDataset)
{
	m_pProducePkg = pDataset;
}

void CTcpEdgeTestDataView::UpdateDataset(const QString& strID)
{
	QTableWidget* pObj = (QTableWidget*)findChild<QObject*>("_" + strID + "_");
	CDvmDatasetGroup* pGroup = (CDvmDatasetGroup*)m_pProducePkg->FindByID(strID);	
	if(pGroup)
	{
		pGroup->DeleteAll();
		for (int i = 0; i < pObj->rowCount(); i++)
		{
			CDvmData* pData = new CDvmData;
			pData->m_dwItemData = 1;
			//lmy,20230920ÐÞ¸Ä
			//pData->m_dwReserved = 1;
			pData->m_dwReserved = 0;
			pData->m_strID = pData->m_strName = pData->m_strValue = pObj->item(i, 0)->text();
			pGroup->AddNewChild(pData);
		}
	}
}

void CTcpEdgeTestDataView::CopyItemData(CExBaseList* pDest, CExBaseList* pSrc)
{
	for (int i = 0; i < pSrc->GetCount(); i++)
	{
		CExBaseList* pDestChild = (CExBaseList*)pDest->GetAt(i);
		CExBaseList* pSrcChild = (CExBaseList*)pSrc->GetAt(i);
		pDestChild->m_dwItemData = pSrcChild->m_dwItemData;
		if(pSrcChild->GetCount())
		{
			CopyItemData(pDestChild, pSrcChild);
		}
	}
}

void CTcpEdgeTestDataView::UpdateDatasetGroup(const QString& strID)
{
	CDvmDatasetGroup* pGroup = (CDvmDatasetGroup*)m_pProducePkg->FindByID(strID);
	if(pGroup)
	{
		pGroup->DeleteAll();
		m_oTempDataset.CopyChildren(pGroup);
		CopyItemData(pGroup, &m_oTempDataset);
	}
}

void CTcpEdgeTestDataView::OnOK()
{
	UIGetDataset(this, m_pProducePkg);
}

QPushButton* CTcpEdgeTestDataView::AddGridButton(QTableWidget* pTable, long nRow, long nCol, const QString& strName)
{
	QWidget* pWidget = pTable->cellWidget(nRow, nCol);
	if(pWidget)
	{
		QPushButton* pChild = pWidget->findChild<QPushButton*>("GridButton");
		return pChild;
	}

	pWidget = new QWidget(pTable);
	QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
	pWidget->setLayout(pLayout);
	QPushButton* pButton = new QPushButton(pWidget);
	pButton->setObjectName("GridButton");
	QTableWidgetItem* pItem = pTable->item(nRow, 0);
	pButton->setProperty("GridButtonRow", QVariant::fromValue(pItem));
	pButton->setProperty("GridButtonColumn", QVariant::fromValue(nCol));
	pButton->setText(strName);
	pLayout->setSpacing(0);
	pLayout->setMargin(0);
	pLayout->addWidget(pButton);
	pLayout->setAlignment(pButton, Qt::AlignCenter);
	pTable->setCellWidget(nRow, nCol, pWidget);

	emit sig_adjustSize();

	return pButton;
}

void CTcpEdgeTestDataView::EnableBlur(bool bEnabled)
{
	if(bEnabled)
	{
		QGraphicsBlurEffect* blur = (QGraphicsBlurEffect*)parentWidget()->graphicsEffect();
		if(!blur)
		{
			blur = new QGraphicsBlurEffect;
			blur->setBlurRadius(50);
			parentWidget()->setGraphicsEffect(blur);
		}
	}
	else
	{
		QGraphicsBlurEffect* blur = (QGraphicsBlurEffect*)parentWidget()->graphicsEffect();
		delete blur;
		parentWidget()->setGraphicsEffect(NULL);
	}
}

void CTcpEdgeTestDataView::RecordToDataset()
{

}

void CTcpEdgeTestDataView::slot_autoConnected(int nState)
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
	if(pData)
	{
		pData->m_dwItemData = (DWORD)(nState != 0);
	}
}

void CTcpEdgeTestDataView::UpdateUI(const QString& strID, QTableWidget* pWidget, QStringList list)
{
	CDvmDatasetGroup* pDatasetGroup = (CDvmDatasetGroup*)m_pProducePkg->FindByID(strID);
	if(pDatasetGroup)
	{
		pDatasetGroup->DeleteAll();
		for (int i = 0; i < list.count(); i++)
		{
			CDvmData* pData = new CDvmData;
			pData->m_dwItemData = 1;
			pData->m_strID = pData->m_strName = pData->m_strValue = list.at(i);
			pDatasetGroup->AddNewChild(pData);
		}

		pWidget->clear();
		pWidget->setRowCount(0);
		POS pos = pDatasetGroup->GetHeadPosition();
		while (pos)
		{
			CDvmData* pData = (CDvmData*)pDatasetGroup->GetNext(pos);
			pWidget->insertRow(pWidget->rowCount());
			long nRow = pWidget->rowCount() - 1;
			pWidget->setItem(nRow, 0, new QTableWidgetItem(pData->m_strValue));
		}
	}
}