#include "SttMacroParaEditViewRemoteWidget.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include <QGridLayout>
#include <QHeaderView>


QSttMacroParaEditViewRemoteWidget::QSttMacroParaEditViewRemoteWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pRemoteTable = NULL;
	m_pCheckBoxDelegateBase = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewRemoteWidget::~QSttMacroParaEditViewRemoteWidget()
{

}



void QSttMacroParaEditViewRemoteWidget::InitUI()
{
	CString strText;
	m_pGroupBox = new QSttCheckableGroupBox;
	strText = _T("遥控测试");
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);
	m_pRemoteTable = new QTableWidget;
	m_pRemoteTable->setFont(*g_pSttGlobalFont);
	m_pRemoteTable->horizontalHeader()->setFont(*g_pSttGlobalFont);

	InitTable();

	OpenBinBoutMapXml();

	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pRemoteTable);
	m_pGroupBox->setLayout(pVBoxLayout);
	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pGroupBox);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);

	connect(m_pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	connect(m_pRemoteTable,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}



void QSttMacroParaEditViewRemoteWidget::InitTable()
{
	QHeaderView* pLeft = m_pRemoteTable->verticalHeader();
	pLeft->setDefaultSectionSize(36);
	pLeft->setVisible(false);
	QHeaderView* pHeadTop = m_pRemoteTable->horizontalHeader();
	pHeadTop->setClickable(false);
	pHeadTop->setMovable(false);
	m_pRemoteTable->horizontalHeader()->setStretchLastSection(true); 
	m_pRemoteTable->setEditTriggers(QAbstractItemView::DoubleClicked);
	m_pRemoteTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pRemoteTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_pRemoteTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");

	m_pCheckBoxDelegateBase = new QExBaseListCheckBoxDelegate(this);
	m_pRemoteTable->setItemDelegateForColumn(0,m_pCheckBoxDelegateBase);

	QStringList  HStrList;
	HStrList<< _T("选择") << _T("测试项") <<  _T("测试回路")<< _T("测试点路")  << _T("备注");

	m_pRemoteTable->setColumnCount(5);
	m_pRemoteTable->setHorizontalHeaderLabels(HStrList);

	m_pRemoteTable->setColumnWidth(0,140);
	m_pRemoteTable->setColumnWidth(1,180);
	m_pRemoteTable->setColumnWidth(2,180);
	m_pRemoteTable->setColumnWidth(3,180);
	m_pRemoteTable->setColumnWidth(4,180);

}


BOOL QSttMacroParaEditViewRemoteWidget::OpenTestTestMngrFile( const CString& strParasFile )
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	CDataGroup* pDataGroup = g_theTestCntrFrame->GetTestMacroUI_Paras();

	if ((pDataGroup->GetCount()<=0)&&(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile.GetLength()>0))
	{
		stt_ui_OpenParasFile(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile,pDataGroup);
	}

	if (pDataGroup->GetCount()>0)
	{
		pDataGroup->CopyChildren(&m_pRemoteDataGroup);
	}
	return TRUE;
}


void QSttMacroParaEditViewRemoteWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath,strDatasetpathdsEna;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pRemoteDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);


	strDatasetpathdsEna = strDatasetpath;
	int pos = strDatasetpathdsEna.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpathdsEna = strDatasetpathdsEna.Left(pos+1);
		strDatasetpathdsEna = strDatasetpathdsEna + _T("dsEna");
		m_pRemoteDataGroup.SetDataValue(_T("datasetpathdsEna"),strDatasetpathdsEna);
	}
}

void QSttMacroParaEditViewRemoteWidget::SaveParasXml()
{
	m_pRemoteDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pRemoteDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pRemoteDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pRemoteDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_Paras.xml");
	m_pRemoteDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewRemoteWidget::InitData( CDataGroup *pData )
{
	m_pRemoteTable->clearContents();
	m_pRemoteTable->setRowCount(0);
	CString strID,strText;


	QTableWidgetItem *pItem = NULL; 
 	long nCurrRowIndex = m_pRemoteTable->rowCount();
 	for (int i = 0; i < 2; i++)
 	{

		if (nCurrRowIndex >= m_pRemoteTable->rowCount())
		{
			m_pRemoteTable->setRowCount(nCurrRowIndex + 1);
		}

		pItem = new QTableWidgetItem;
		pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
		/*pItem->setCheckState(Qt::Checked);*/
		if (nCurrRowIndex == 0)
		{
			strID = _T("Accuracy_Check");
		}
		else
		{
			strID = _T("Abnormal_Check");
		}
		GetTableWidgetItemValue(pItem,strID);
		m_pRemoteTable->setItem(nCurrRowIndex,0,pItem);


		pItem = new QTableWidgetItem;
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
		pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		if (nCurrRowIndex == 0)
		{
			strText = _T("正确性测试");
		}
		else
		{
			strText = _T("异常自诊断");
		}
		pItem->setText(strText);
		m_pRemoteTable->setItem(nCurrRowIndex,1,pItem);

		pItem = new QTableWidgetItem;
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
		pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		if (nCurrRowIndex == 0)
		{
			strText = _T("回路1");
		}
		else
		{
			strText = _T("回路2");
		}
		pItem->setText(strText);
		m_pRemoteTable->setItem(nCurrRowIndex,2,pItem);


		pItem = new QTableWidgetItem;
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
		pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		if (nCurrRowIndex == 0)
		{
			strText = _T("合闸");
		}
		else
		{
			strText = _T("分闸");
		}
		pItem->setText(strText);
		m_pRemoteTable->setItem(nCurrRowIndex,3,pItem);


		pItem = new QTableWidgetItem;
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
		pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		if (nCurrRowIndex == 0)
		{
			strText = _T("预置-返校-执行");
		}
		else
		{
			strText = _T("预置-撤销-执行");
		}
		pItem->setText(strText);
		m_pRemoteTable->setItem(nCurrRowIndex,4,pItem);

		nCurrRowIndex ++;
	}
}



void QSttMacroParaEditViewRemoteWidget::slot_OnCellChanged( int row,int col )
{
	if (row  <  0)
	{
		return;
	}
	disconnect(m_pRemoteTable,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));

	QTableWidgetItem  *pItem  = m_pRemoteTable->item(row,col);

	if (pItem == NULL)
	{
		return;
	} 

	long nSelect = 0;
	CString strID;

	if(col == 0)
	{
		if (pItem->checkState() !=  Qt::Unchecked)
		{
			nSelect = 1;
		}
		else
		{
			nSelect = 0;
		}

		if (row == 0)
		{
			strID = _T("Accuracy_Check");
		}
		else
		{
			strID = _T("Abnormal_Check");
		}

		m_pRemoteDataGroup.SetDataValue(strID,nSelect);
	}

	connect(m_pRemoteTable,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);

}

void QSttMacroParaEditViewRemoteWidget::slot_GroupBoxtoggled( bool checked)
{
	m_pRemoteDataGroup.SetDataValue(_T("Remote_Check"),(long)checked);	
}

void QSttMacroParaEditViewRemoteWidget::GetTableWidgetItemValue( QTableWidgetItem * pItem,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)m_pRemoteDataGroup.FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	
	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
	if (nIsSelected)
	{
		pItem->setCheckState(Qt::Checked);
	}
	else
	{
		pItem->setCheckState(Qt::Unchecked);
	}
}


void QSttMacroParaEditViewRemoteWidget::OpenBinBoutMapXml()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("BinBoutCommMapConfig.xml");
	CDataGroup oDataGroup;
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	CString strID,strValue;
	for (int i = 0; i < 8 ;i++)
	{
		strID.Format(_T("Bout%d"), i+1);
		stt_GetDataValueByID(&oDataGroup, strID, strValue);

		if (strValue == _T("Din_1") || strValue == _T("1"))
		{
			oDataGroup.SetDataValue(strID, _T("Din_1"));  
		}
		else if (strValue == _T("Din_2") || strValue == _T("0"))
		{
			oDataGroup.SetDataValue(strID, _T("Din_2"));
		}
		else if (strValue == _T("Din_5") || strValue == _T("2"))
		{
			oDataGroup.SetDataValue(strID, _T("Din_5"));
		}
		else
		{
			oDataGroup.SetDataValue(strID, _T(""));  
		}
	}

	UpdateRemoteBoutData(&oDataGroup);
}

void QSttMacroParaEditViewRemoteWidget::OnViewTestStart()
{
	//SaveParasXml();

	m_pGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewRemoteWidget::OnViewTestStop()
{
	m_pGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewRemoteWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	m_pRemoteDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewRemoteWidget::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pRemoteDataGroup);	
	}
	CDvmData* pCurData = (CDvmData*)m_pRemoteDataGroup.FindByID(_T("Remote_Check"));
	if (pCurData)
	{
		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
		m_pGroupBox->setChecked(nIsSelected);
	}

	InitData(&m_pRemoteDataGroup);


	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}
