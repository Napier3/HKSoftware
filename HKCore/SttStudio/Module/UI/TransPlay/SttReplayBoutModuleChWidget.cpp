#include "SttReplayBoutModuleChWidget.h"
#include "SttMacroParaEditViewTransPlay.h"
// #include "../../CommonMethod/commonMethod.h"
#include "../Controls/SttCheckBox.h"

CSttReplayBoutModuleChWidget::CSttReplayBoutModuleChWidget( QWidget *pParent /*= 0*/, CSttModuleComtradeBind *pModuleInfo /*= NULL*/ )
{
	ui.setupUi(this);
	m_nBoutCount = pModuleInfo->GetCount();
	m_pModuleInfo = pModuleInfo;
	InitUI();
}

CSttReplayBoutModuleChWidget::~CSttReplayBoutModuleChWidget()
{

}

void CSttReplayBoutModuleChWidget::InitUI()
{

	setFont(*g_pSttGlobalFont);
	ui.m_btnClearMap->setFont(*g_pSttGlobalFont);
	ui.m_btnDisconnectAll->setFont(*g_pSttGlobalFont);
	ui.m_btnClearMap->setText(g_sLangTxt_Replay_ClearMap);
	QStringList header;  
	header << /*_T("开出通道")*/g_sLangTxt_Native_BoutChannel << /*_T("状态")*/g_sLangTxt_Status << /*_T("通道映射")*/g_sLangTxt_IEC_ChMaps;  
	ui.tableWidget->setHorizontalHeaderLabels(header);  
// 	ui.tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch); // 根据内容自动调整列宽度  
	ui.tableWidget->setRowCount(m_nBoutCount);  

	QStringList header1;  
	header1 << /*_T("开出通道")*/g_sLangTxt_Native_BoutChannel << /*_T("状态")*/g_sLangTxt_Status << /*_T("通道映射")*/g_sLangTxt_IEC_ChMaps;  
	ui.tableWidgetIns->setHorizontalHeaderLabels(header1);  
// 	ui.tableWidgetIns->horizontalHeader()->setResizeMode(QHeaderView::Stretch); // 根据内容自动调整列宽度  
	ui.tableWidgetIns->setRowCount(m_nBoutCount);  

	QString headerStyle = "QHeaderView::section { background-color: #00A2E8; color: black; }";  
	ui.tableWidget->horizontalHeader()->setStyleSheet(headerStyle);  
	ui.tableWidgetIns->horizontalHeader()->setStyleSheet(headerStyle);  

	ui.tableWidget->horizontalHeader()->setFont(QFont("song",16));
	ui.tableWidgetIns->horizontalHeader()->setFont(QFont("song",16));

	InitTableUI();

	QList<int> columnWidths;
	columnWidths << 120 << 120 << 200;
	for (int i = 0; i < columnWidths.size(); ++i) 
	{
		ui.tableWidgetIns->setColumnWidth(i, columnWidths[i]);
		ui.tableWidget->setColumnWidth(i, columnWidths[i]);
	}

	int nHeight = 35;
	for (int i = 0; i < ui.tableWidgetIns->rowCount(); ++i) {
		ui.tableWidgetIns->setRowHeight(i, nHeight);
	}

	for (int i = 0; i < ui.tableWidget->rowCount(); ++i) {
		ui.tableWidget->setRowHeight(i, nHeight);
	}

}

void CSttReplayBoutModuleChWidget::InitTableUI()
{
	if (m_nBoutCount <= 0)
	{
		return;
	}

	QFont oFont,Font;
	oFont.setPixelSize(17);
	setFont(oFont);

	QTableWidgetItem *item = NULL;

	int rowCountTableWidget = m_nBoutCount / 2 + m_nBoutCount % 2;
	ui.tableWidget->setRowCount(rowCountTableWidget);

	int rowCountTableWidgetIns = m_nBoutCount / 2;
	ui.tableWidgetIns->setRowCount(rowCountTableWidgetIns);

	int rowCount = 1; // 行号从1开始

	for (int i = 0; i < m_nBoutCount; i++)
	{
		QString strBinOut = /*QString("开出%1").arg(i + 1)*/g_sLangTxt_Native_BoutX + QString::number(i + 1);

		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignCenter);
		item->setText(strBinOut);
		item->setFont(oFont);

		// 添加状态复选框到第二列
		QWidget* checkBoxWidget = new QWidget();
		QHBoxLayout* layout = new QHBoxLayout(checkBoxWidget);
		layout->setMargin(0);
		layout->setAlignment(Qt::AlignCenter);
		QCheckBox* checkBox = new QSttCheckBox(checkBoxWidget);
// 		checkBox->setFixedWidth(40);
// 		checkBox->setChecked(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryModuleParas.m_oChMap[i].m_nBinaryChSel == 1);
		layout->addWidget(checkBox);
		m_ChStateList.append(checkBox);
		checkBoxWidget->setLayout(layout);
		

		// 添加通道映射下拉框到第三列
		QScrollComboBox* comboBox = new QScrollComboBox();
		comboBox->addItem("--"); // 初始值为"--"
		m_ChSelList.append(comboBox);

		// 根据索引值选择将项目添加到ui.tableWidget或ui.tableWidgetIns中
		if (i < rowCountTableWidget)
		{
			ui.tableWidget->setItem(i, 0, item);
			ui.tableWidget->setCellWidget(i, BOUT_TABLE_CHSTATE, checkBoxWidget);
			ui.tableWidget->setCellWidget(i, BOUT_TABLE_CHSELECT, comboBox);
			ui.tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(rowCount++))); // 设置行号
		}
		else
		{
			int newIndex = i - rowCountTableWidget;
			ui.tableWidgetIns->setItem(newIndex, 0, item);
			ui.tableWidgetIns->setCellWidget(newIndex, BOUT_TABLE_CHSTATE, checkBoxWidget);
			ui.tableWidgetIns->setCellWidget(newIndex, BOUT_TABLE_CHSELECT, comboBox);
			ui.tableWidgetIns->setVerticalHeaderItem(newIndex, new QTableWidgetItem(QString::number(rowCount++))); // 设置行号
		}
	}

	QString cellSelectedStyle = "QTableWidget::item:selected { background-color: #E6E6E6; }";
	ui.tableWidget->setStyleSheet(cellSelectedStyle);
	ui.tableWidgetIns->setStyleSheet(cellSelectedStyle);

	UpdateChWidget();
	initSignalSlots();
	UpdateButtonEnable(FALSE);

	bool isChecked = ui.m_btnDisconnectAll->isChecked();
	QString strName;
	if(isChecked)
	{
		strName = /*_T("全部断开")*/g_sLangTxt_Native_DisConnectAll;
	}
	else
	{
		strName = /*_T("全部闭合")*/g_sLangTxt_Native_AllClosed;
	}

	ui.m_btnDisconnectAll->setText(strName);
}

void CSttReplayBoutModuleChWidget::UpdateButtonEnable(BOOL state)
{
	ui.m_btnClearMap->setEnabled(state);
	ui.m_btnDisconnectAll->setEnabled(state);
	ui.tableWidget->setEnabled(state);
	ui.tableWidgetIns->setEnabled(state);
}


void CSttReplayBoutModuleChWidget::InitBinaryOutSet()
{

	UpdateButtonEnable(TRUE);

	CExBaseList* pCurrentList = /*(CComtradeBinaryData *)*/g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_oSrcComtradeFile.GetBinarys();

	for (int i = 0; i < m_nBoutCount; i++)
	{
		QScrollComboBox* comboBox = qobject_cast<QScrollComboBox*>(ui.tableWidget->cellWidget(i, BOUT_TABLE_CHSELECT));
		QScrollComboBox* comboBoxIns = qobject_cast<QScrollComboBox*>(ui.tableWidgetIns->cellWidget(i, BOUT_TABLE_CHSELECT));

		if (comboBox && comboBoxIns)
		{
			comboBox->clear();
			comboBoxIns->clear();

			// 先添加初始值"---"
			comboBox->addItem("---");
			comboBoxIns->addItem("---");

			// 遍历pCurrentList中的所有数据，将其加入到下拉框中
			for (int j = 0; j < g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_oSrcComtradeFile.m_nBinarys; j++)
			{
				CComtradeBinaryData* pBinaryData = dynamic_cast<CComtradeBinaryData*>(pCurrentList->GetAt(j));

				if (pBinaryData)
				{
					QString strName = pBinaryData->m_strName;
					comboBox->addItem(strName);
					comboBoxIns->addItem(strName);
				}
			}
		}
	}
}



void CSttReplayBoutModuleChWidget::UpdateStateEnabled(BOOL isLeftWidget,int nRow, int nCol)
{
	// 找到对应的行和列
	int row = nRow; // 获取当前单元格所在的行
	int column = nCol; // 获取当前单元格所在的列

	QTableWidget* CurWidget;
	if(isLeftWidget)
	{
		CurWidget = ui.tableWidget;
	}
	else
	{
		CurWidget = ui.tableWidgetIns;
	}

	// 获取当前单元格下拉框的索引
	QScrollComboBox* comboBox = qobject_cast<QScrollComboBox*>(CurWidget->cellWidget(nRow, nCol));
	int currentIndex = comboBox->currentIndex();
	QWidget* checkBoxWidget = CurWidget->cellWidget(row, BOUT_TABLE_CHSTATE);
	QCheckBox* checkBox = qobject_cast<QCheckBox*>(checkBoxWidget->layout()->itemAt(0)->widget());
	if(currentIndex == 0)
	{
		checkBox->setEnabled(false);
	}
	else
	{
		checkBox->setEnabled(true);
	}

	// 更新表格显示
	CurWidget->viewport()->update();
}



void CSttReplayBoutModuleChWidget::slot_btnDisconnectAll()
{

	bool isChecked = ui.m_btnDisconnectAll->isChecked();
	QString strName;
	if(isChecked)
	{
		strName = /*_T("全部断开")*/g_sLangTxt_Native_DisConnectAll;
	}
	else
	{
		strName = /*_T("全部闭合")*/g_sLangTxt_Native_AllClosed;
	}

	ui.m_btnDisconnectAll->setText(strName);

	int curIndex = 0;//记录当前所处列数
	for (int i = 0; i < m_nBoutCount; i++)
	{
		if(curIndex >= m_nBoutCount/2 )
		{
			curIndex = 0;
		}
		QWidget* checkBoxWidget = ui.tableWidget->cellWidget(curIndex, BOUT_TABLE_CHSTATE);
		QCheckBox* checkBox = qobject_cast<QCheckBox*>(checkBoxWidget->layout()->itemAt(0)->widget());

// 		if(checkBox->isEnabled())
// 		{
			checkBox->setChecked(isChecked);
// 		}

		QWidget* checkBoxWidgetIns = ui.tableWidgetIns->cellWidget(curIndex, BOUT_TABLE_CHSTATE);
		QCheckBox* checkBoxIns = qobject_cast<QCheckBox*>(checkBoxWidgetIns->layout()->itemAt(0)->widget());

// 		if(checkBoxIns->isEnabled())
// 		{
			checkBoxIns->setChecked(isChecked);
// 		}

		++curIndex;
	}
}


void CSttReplayBoutModuleChWidget::slot_btnClearMap()
{
	for (int nIndex = 0; nIndex < m_nBoutCount; nIndex++)
	{
		QScrollComboBox* comboBox = m_ChSelList[nIndex];
		if(comboBox)
		{
			comboBox->setCurrentIndex(0);
		}

	}

}


void CSttReplayBoutModuleChWidget::slot_tableCellClicked(int row, int column)
{
// 	// 判断是否点击了状态列
// 	if (column == BOUT_TABLE_CHSTATE) 
// 	{
// 		// 直接改变对应行的复选框状态
// 		m_ChStateList[row]->setChecked(!m_ChStateList[row]->isChecked());
// 	}
}

void CSttReplayBoutModuleChWidget::slot_tableInsCellClicked(int row, int column)
{
// 	// 判断是否点击了状态列
// 	if (column == BOUT_TABLE_CHSTATE) 
// 	{
// 		// 直接改变对应行的复选框状态
// 		row += ui.tableWidget->rowCount();
// 		m_ChStateList[row]->setChecked(!m_ChStateList[row]->isChecked());
// 	}
}

void CSttReplayBoutModuleChWidget::SetChSelectList( const QStringList &oBinaryChList )
{
	QStringList oBinaryListNew;
	oBinaryListNew = oBinaryChList;
	oBinaryListNew.insert(0,_T("--"));

	uninitSignalSlots();

	QScrollComboBox *pBinaryChSel = NULL;
	CSttModuleBinaryChComtradeBind *pCh = NULL;
	CDvmData *pChData = NULL;

	int nChNum = ui.tableWidget->rowCount();
	int nChNum2 = ui.tableWidgetIns->rowCount();
	long nValue = 0;
	long nChIndex = 0;
	int nInsTableIndex = 0;
// 	tmt_replay_para *pTest = (tmt_replay_para *)g_pReplayTestMain->m_TestTable->GetCurrentItem();
// 	tmt_replay_module_Binary *pBinaryModule = &g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryModuleParas;

	for(int nIndex=0; nIndex<m_nBoutCount; nIndex++)
	{
		pCh = (CSttModuleBinaryChComtradeBind *)m_pModuleInfo->GetAt(nIndex);	
		if(!pCh)
		{
			return;
		}
		if(nIndex < nChNum)
		{
			pBinaryChSel = qobject_cast<QScrollComboBox*>(ui.tableWidget->cellWidget(nIndex, BOUT_TABLE_CHSELECT));
		}
		else if(nIndex >= nChNum && nIndex < m_nBoutCount)
		{
			pBinaryChSel = qobject_cast<QScrollComboBox*>(ui.tableWidgetIns->cellWidget(nInsTableIndex++, BOUT_TABLE_CHSELECT));
		}
		if (pBinaryChSel)
		{
			pBinaryChSel->clear();
		}
		pBinaryChSel->addItems(oBinaryListNew);
		nChIndex = oBinaryListNew.indexOf(pCh->m_strComtradeBinaryCh);

		CString strIndexId = oBinaryListNew[pCh->m_nBinaryCh_Index];
		nChIndex = oBinaryListNew.indexOf(strIndexId);

		if(nChIndex < 0)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("开出通道描述查找出错(%ld)."),nChIndex);
			nChIndex = 0;
		}
		pBinaryChSel->setCurrentIndex(nChIndex);
	}

	initSignalSlots();

}

void CSttReplayBoutModuleChWidget::uninitSignalSlots()
{
	disconnect(ui.tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(slot_tableCellClicked(int, int)));
	disconnect(ui.tableWidgetIns, SIGNAL(cellClicked(int, int)), this, SLOT(slot_tableInsCellClicked(int, int)));

	disconnect(ui.m_btnDisconnectAll, SIGNAL(clicked()), this, SLOT(slot_btnDisconnectAll()));
	disconnect(ui.m_btnClearMap, SIGNAL(clicked()), this, SLOT(slot_btnClearMap()));

	// 连接ui.tableWidget中所有下拉框的currentIndexChanged信号到slot_comboBoxIndexChanged槽函数
	int nChNum = m_ChSelList.size();

	for(int i=0; i<nChNum; i++)
	{ 
		disconnect(m_ChStateList.at(i),SIGNAL(stateChanged(int)),this,SLOT(slot_ChStateChanged(int)));
		disconnect(m_ChSelList.at(i),SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChannelMapChanged(int)));
	}

}

void CSttReplayBoutModuleChWidget::initSignalSlots()
{
	connect(ui.tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(slot_tableCellClicked(int, int)));
	connect(ui.tableWidgetIns, SIGNAL(cellClicked(int, int)), this, SLOT(slot_tableInsCellClicked(int, int)));

	connect(ui.m_btnDisconnectAll, SIGNAL(clicked()), this, SLOT(slot_btnDisconnectAll()));
	connect(ui.m_btnClearMap, SIGNAL(clicked()), this, SLOT(slot_btnClearMap()));
	int nChNum = m_ChSelList.size();

	for(int i=0; i<nChNum; i++)
	{
		connect(m_ChStateList.at(i),SIGNAL(stateChanged(int)),this,SLOT(slot_ChStateChanged(int)));
		connect(m_ChSelList.at(i),SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChannelMapChanged(int)));
	}

}
void CSttReplayBoutModuleChWidget::slot_ChannelMapChanged(int index)
{
	// 获取发送信号的下拉框对象
	QScrollComboBox* comboBox = qobject_cast<QScrollComboBox*>(sender());
	if(!comboBox)
	{
		return;
	}
	UpdateChannelMapChanged(comboBox, index);
}

void CSttReplayBoutModuleChWidget::UpdateChannelMapChanged( QScrollComboBox *comboBox, int index )
{
	int nChIndex = m_ChSelList.indexOf(comboBox);
	QCheckBox* pCheckBox = m_ChStateList[nChIndex];

	if(!pCheckBox)
	{
		return;
	}

	CSttModuleBinaryChComtradeBind *pCh = (CSttModuleBinaryChComtradeBind *)m_pModuleInfo->GetAt(nChIndex);
	ASSERT(pCh != NULL);

// 	pCh->m_nChState = 0;
	pCh->InitBinaryCh(g_pReplayTestMain->m_ParaSetWidget->GetComtradeBinary(index - 1));
	pCh->m_nBinaryCh_Index = m_ChSelList[nChIndex]->findText(pCh->m_strComtradeBinaryCh);

	if(pCh->m_nBinaryCh_Index < 0)
	{
		pCh->m_nBinaryCh_Index = 0;
	}
	if (pCh->m_nBinaryCh_Index > 0)
	{
		pCheckBox->setEnabled(false);
		pCheckBox->setChecked(false);
	}
	else
	{
		pCheckBox->setEnabled(true);
	}
	OnBinaryModuleChChanged(m_pModuleInfo);
}

void CSttReplayBoutModuleChWidget::slot_ChStateChanged( int index )
{
	// 获取发送信号的下拉框对象
	QCheckBox* pCheckBox = qobject_cast<QCheckBox*>(sender());
	int nChIndex = m_ChStateList.indexOf(pCheckBox);
	QScrollComboBox *pComboBox = m_ChSelList[nChIndex];
	if(!pComboBox || !pCheckBox )
	{
		return;
	}

	CSttModuleBinaryChComtradeBind *pCh = (CSttModuleBinaryChComtradeBind *)m_pModuleInfo->GetAt(nChIndex);
	ASSERT(pCh != NULL);
	if (pCheckBox->isChecked())
	{
		pCh->m_nChState = 1;		
		pComboBox->setCurrentIndex(0);
	}
	else
	{
		pCh->m_nChState = 0;
	}

	OnBinaryModuleChChanged(m_pModuleInfo);
}

void CSttReplayBoutModuleChWidget::OnBinaryModuleChChanged( CSttModuleComtradeBind *pBinaryModule)
{ 
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.UpdateBinaryChReplayBuf(pBinaryModule);
}

void CSttReplayBoutModuleChWidget::UpdateChWidget()
{
	long nCount = m_ChSelList.size();
	QScrollComboBox *pComboBox = NULL;
	QCheckBox *pCheckBox = NULL;
	CSttModuleBinaryChComtradeBind *pCh = NULL;
	long nCmbIndex= 0;
	CString strIndexData;

	for(int nIndex = 0; nIndex < m_nBoutCount; nIndex++)
	{
		pComboBox = m_ChSelList.at(nIndex);
		pCheckBox = m_ChStateList.at(nIndex);

		pCh = (CSttModuleBinaryChComtradeBind *)m_pModuleInfo->GetAt(nIndex);
		nCmbIndex = pComboBox->findText(pCh->m_strComtradeBinaryCh);
		if(nCmbIndex < 0)
		{
			nCmbIndex = 0;
		}

// 		UpdateChannelMapChanged(pComboBox, nCmbIndex);

		pComboBox->setCurrentIndex(nCmbIndex);

		if(nCmbIndex > 0)
		{
			pCheckBox->setEnabled(false);
		}
		pCheckBox->setChecked(pCh->m_nChState);
	}
}




