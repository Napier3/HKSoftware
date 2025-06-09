#include "stdafx.h"
#include "TcpEdgeDeviceView.h"
#include "ui_TcpEdgeDeviceView.h"
#include "TcpEdgeUIGlobalDef.h"
#include "TcpEdgeUserEditDlg.h"

#include <QSplitter>
#include <QFileInfo>
#include <QDir>

CTcpEdgeDeviceView::CTcpEdgeDeviceView(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CTcpEdgeDeviceView)
{
	ui->setupUi(this);
	InitUI();
}

CTcpEdgeDeviceView::~CTcpEdgeDeviceView()
{
	delete ui;
	ExitSaving();
}

void CTcpEdgeDeviceView::ExitSaving()
{
	m_timer.stop();
	//如果当前正在缓存,等待
	CTickCount32 event;
	while (m_bPkgIsSaving)
	{
		event.DoEvents(50);
	}

	if(m_pDevice && m_pDevice->m_bSavePkg)
	{
		//如果存
		StartSavePkgThread();
		while (m_bPkgIsSaving)
		{
			event.DoEvents(50);
		}
	}
	else
	{
		//不存,删除
		QFileInfo file(m_pDevice->m_strLogFile);
		file.dir().remove(file.fileName());
	}

	if(m_pSavePkgThread)
	{
		delete m_pSavePkgThread;
		m_pSavePkgThread = NULL;
	}

	if(m_pDevice && m_pDevice->m_bSaveRpt)
	{
		//保存报告
		m_oRptWordTool.InitWordTool(m_pDevice->m_strRptFile);
		m_oRptWordTool.CreateNewWord();
	}
}

QTreeWidgetItem* CTcpEdgeDeviceView::FindTreeNode(QTreeWidgetItem* pNode, QString strFuncName)
{
	CDvmDataset* pDataset = (CDvmDataset*)pNode->data(0, Qt::UserRole).value<CExBaseObject*>();
	if(pDataset && pDataset->m_strID == strFuncName)
	{
		return pNode;
	}

	int nChildCount = pNode->childCount();
	for(int nIndex = 0; nIndex!= nChildCount; nIndex++)
	{
		QTreeWidgetItem* pItem = FindTreeNode(pNode->child(nIndex), strFuncName);
		if(pItem)
		{
			return pItem;
		}
	}

	return NULL;
}

void CTcpEdgeDeviceView::InitTree(QTreeWidgetItem* pParent, CExBaseList* pData, CDvmLogicDevice* pDevice)
{
	POS pos = pData->GetHeadPosition();
	while (pos)
	{
		CExBaseList* pChild = (CExBaseList*)pData->GetNext(pos);
		QTreeWidgetItem* pItem = new QTreeWidgetItem();
		pItem->setText(0, pChild->m_strName);
		pParent->addChild(pItem);

		if(CExBaseObject* pObj = pDevice->FindByID(pChild->m_strID))
		{
			pItem->setData(0, Qt::UserRole, QVariant::fromValue<CExBaseObject*>(pObj));
		}
		else
		{
			InitTree(pItem, pChild, pDevice);
		}
	}
}

void CTcpEdgeDeviceView::InitUI()
{
	m_pDevice = NULL;
	m_bPkgIsSaving = false;
	m_pSavePkgThread = NULL;

	CString strFile = _P_GetLibraryPath();
	m_oDvmDevice.OpenXmlFile(strFile + "边缘网关数据模型V1.xml", CDataMngrXmlRWKeys::g_pXmlKeys);
	CDvmLogicDevice* pDevice = (CDvmLogicDevice*)m_oDvmDevice.GetHead();
	m_treeGroup.OpenXmlFile(strFile + "边缘网关数据模型结构V1.xml", CDataMngrXmlRWKeys::g_pXmlKeys);

	QTreeWidgetItem* pRoot = new QTreeWidgetItem();
	pRoot->setText(0, "数据集合");
	ui->m_treeDataset->addTopLevelItem(pRoot);
	InitTree(pRoot, &m_treeGroup, pDevice);
	ui->m_treeDataset->expandItem(pRoot);

	//分割窗口
	QSplitter* pHorz = new QSplitter(Qt::Horizontal, 0);
	pHorz->addWidget(ui->m_treeDataset);
	QSplitter* pVert = new QSplitter(Qt::Vertical, pHorz);
	pVert->addWidget(ui->m_gridDataset);
	pVert->addWidget(ui->tabDeviceBoxWidget);
	pVert->setStretchFactor(0, 2);
	pVert->setStretchFactor(1, 1);
	pHorz->addWidget(pVert);
	pHorz->setStretchFactor(0, 1);
	pHorz->setStretchFactor(1, 4);
	ui->tab_2->layout()->addWidget(pHorz);

	ui->m_gridDataset->setColumnWidth(0, 200);
	ui->m_gridDataset->setColumnWidth(1, 60);
	ui->m_gridDataset->setColumnWidth(2, 60);
	ui->m_gridDataset->setColumnWidth(3, 150);
	ui->m_gridDataset->setColumnWidth(4, 150);
	ui->m_gridDataset->setColumnWidth(5, 500);
	ui->m_gridDataset->setColumnWidth(6, 150);
	//ui->m_gridDataset->horizontalHeader()->setResizeMode(4, QHeaderView::Stretch);
	//ui->m_gridDataset->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	ui->m_gridDataset->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(ui->m_treeDataset, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(slot_currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
	connect(ui->m_gridDataset, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(slot_gridLButtonDblClk(QTableWidgetItem*)));

	ui->tabDeviceWidget->setCurrentIndex(0);

	m_timer.start(500);
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(slot_timeout()));
}

void CTcpEdgeDeviceView::SetDevice(CTcpEdgeDevice* pDevice, QString strSetupTime)
{
	//确认连接设备
	m_pDevice = pDevice;
	pDevice->m_pWordTool = &m_oRptWordTool;
	m_pDevice->m_strSetupTime = strSetupTime;

	CString strFile = _P_GetBinPath();
	strFile += "..\\FileRecv\\";
	strFile += strSetupTime;
	strFile += "\\";
	m_pDevice->m_strRecvFilePath = strFile;
}

CTcpEdgeDevice* CTcpEdgeDeviceView::GetDevice()
{
	return m_pDevice;
}

void CTcpEdgeDeviceView::StartSavePkgThread()
{
	m_bPkgIsSaving = true;
	m_pSavePkgThread = new CTcpEdgeSavePkgThread();
	m_pSavePkgThread->m_pParam = (void*)&m_bPkgIsSaving;
	m_pSavePkgThread->m_strFullFileName = m_pDevice->m_strLogFile;
	m_pSavePkgThread->m_vecBuffer = m_tempPkgBuffer;
	m_pSavePkgThread->start();
	m_tempPkgBuffer.clear();
}

void CTcpEdgeDeviceView::UpdatePkg(QString strPkg, long nType)
{
	QMutexLocker lock(&m_oTimerLocker);
	tagDeviceTimer tag;
	tag.m_strPkg = strPkg;
	tag.m_nType = nType;
	m_vecTimer.push_back(tag);
}

void CTcpEdgeDeviceView::ChangeRowColor(long nRow, QColor clr)
{
	for (int i = 0; i < ui->m_gridDataset->columnCount(); i++)
	{
		QTableWidgetItem* pItem = ui->m_gridDataset->item(nRow, i);
		pItem->setBackgroundColor(clr);
	}
}

void CTcpEdgeDeviceView::JumpToFuncGrid(QString strFuncName)
{
	long nParentNodeCount = ui->m_treeDataset->topLevelItemCount();
	for(int nIndex = 0; nIndex != nParentNodeCount; nIndex++)
	{
		QTreeWidgetItem* pItem = FindTreeNode(ui->m_treeDataset->topLevelItem(nIndex), strFuncName);
		if(pItem)
		{
			ui->m_treeDataset->setCurrentItem(pItem);
			break;
		}
	}	
}

void CTcpEdgeDeviceView::UpdateDataset()
{
	QTreeWidgetItem* pItem = ui->m_treeDataset->currentItem();
	if(m_pDevice && pItem)
	{
		CDvmDataset* pDataset = (CDvmDataset*)pItem->data(0, Qt::UserRole).value<CExBaseObject*>();
		if(pDataset)
		{
			CDvmDataset* pDevDataset = (CDvmDataset*)m_pDevice->FindDatasetByID(pDataset->m_strID);		
			if(pDevDataset)
			{
				//数据集总共的报文数(error不算在内)
				long nIndex = pDevDataset->m_nIndex;
				long nRow = ui->m_gridDataset->rowCount();
				for (int i = nRow + 1; i < nIndex; i++)
				{
					for (int n = 0; n < pDevDataset->GetCount(); n++)
					{
						CDvmData* pData = (CDvmData*)pDevDataset->GetAt(n);
						CDvmValue* pValue = (CDvmValue*)pData->FindByID(QString("%1").arg(i));
						if(pValue)
						{
							ui->m_gridDataset->insertRow(nRow);
							ui->m_gridDataset->setItem(nRow, 0, new QTableWidgetItem(pValue->m_strName));
							ui->m_gridDataset->setItem(nRow, 1, new QTableWidgetItem(QString("%1").arg(pValue->m_dwReserved)));
							if(pValue->m_dwItemData == 1)
							{
								ui->m_gridDataset->setItem(nRow, 2, new QTableWidgetItem("上行"));
							}
							else
							{
								ui->m_gridDataset->setItem(nRow, 2, new QTableWidgetItem("下行"));
							}
							ui->m_gridDataset->setItem(nRow, 3, new QTableWidgetItem(pData->m_strName));
							ui->m_gridDataset->setItem(nRow, 4, new QTableWidgetItem(pData->m_strID));
							QString strValue = pValue->m_strValue;
							strValue.replace("\n", "");
							strValue.replace("\t", "");
							ui->m_gridDataset->setItem(nRow, 5, new QTableWidgetItem(strValue));
							ui->m_gridDataset->setItem(nRow, 6, new QTableWidgetItem(pValue->m_strDataType));

							if(pValue->m_dwItemData == 1)
							{
								ChangeRowColor(nRow, QColor(221,243,152));
							}
							else
							{
								ChangeRowColor(nRow, QColor(185,230,240));
							}

							break;
						}
					}
					nRow++;
				}
			}
		}
	}
}

void CTcpEdgeDeviceView::slot_gridLButtonDblClk(QTableWidgetItem* pItem)
{
 	long nRow = ui->m_gridDataset->currentRow();
 	QString strPkg = ui->m_gridDataset->item(nRow, 5)->text();
	QString strError = ui->m_gridDataset->item(nRow, 6)->text();
	CTcpEdgeUserEditDlg dlg(strPkg, strError);
	dlg.exec();
}

void CTcpEdgeDeviceView::slot_currentItemChanged(QTreeWidgetItem* pCur, QTreeWidgetItem* pPrev)
{
	while(ui->m_gridDataset->rowCount() > 0)
	{
		ui->m_gridDataset->removeRow(0);
	}
}

void CTcpEdgeDeviceView::slot_timeout()
{
	QMutexLocker lock(&m_oTimerLocker);

	for (int i = 0; i < m_vecTimer.size(); i++)
	{
		long nType = m_vecTimer[i].m_nType;
		QString strPkg = m_vecTimer[i].m_strPkg;

		if (nType == -1)
		{
			nType = XLOGLEVEL_EDGE_PKG_DOWN;
		}
		else if (nType == 1)
		{
			nType = XLOGLEVEL_EDGE_PKG_UP;
		}
		else if (nType == 0)
		{
			nType = XLOGLEVEL_EDGE_PKG_RSLT;
		}

		QString strLog;
		if (nType == XLOGLEVEL_EDGE_PKG_DOWN
			|| nType == XLOGLEVEL_EDGE_PKG_UP)
		{
			strLog = ui->m_boxPkg->LogString(nType, strPkg);
		}
		//分发打印错误信息
		else if (nType == XERRTYPE_LACKNECESSITY
			|| nType == XERRTYPE_RETURNFALSE
			|| nType == XERRTYPE_TIMEOUT
			|| nType == XERRTYPE_RANGEOUT
			|| nType == XERRTYPE_NECESSITYERR
			|| nType == XERRTYPE_COMMON)
		{
			strLog = ui->m_boxErr->LogString(nType, strPkg);
		}
		else
		{
			strLog = ui->m_boxInfo->LogString(nType, strPkg);
		}

		m_tempPkgBuffer.append(strLog);
		if(m_tempPkgBuffer.size() > 1000 && !m_bPkgIsSaving)
		{
			StartSavePkgThread();
		}
	}

	m_vecTimer.clear();
	UpdateDataset();
}