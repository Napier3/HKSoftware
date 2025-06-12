#include "FreqFileWidget.h"
#include <QHeaderView>
#include "../SttTestCntrFrameBase.h"
#include "FreqNewFileDialog.h"
#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "../../../Module/OSInterface/QT/XMessageBox.h"
#ifdef _PSX_QT_LINUX_
#include "../Module/PopupDialog/SttPopupOpenDialog.h"
#include "../Module/PopupDialog/SttPopupSaveAsDialog.h"
#endif


QFreqFileWidget::QFreqFileWidget( QWidget *parent )
{
	m_pNewFileBtn = NULL;
	m_pImportFileBtn = NULL;
	m_pSaveFileBtn = NULL;
	m_pDeleteRowBtn = NULL;
	m_pFreqFileTableWidget = NULL;
	m_pInfoLineEdit = NULL;
	m_pTotalLineEdit = NULL;
	m_pSttProgDlg = NULL;
	m_pSttExportFileThread = NULL;
	m_bHasInitFinished = false;

	m_pCurScrollBar = NULL;
	m_nDataCount = 0;
}

QFreqFileWidget::~QFreqFileWidget()
{
	if (m_pSttProgDlg != NULL)
	{
		delete m_pSttProgDlg;
		m_pSttProgDlg = NULL;
	}
}

void QFreqFileWidget::InitUI()
{
	InitTable();

	CString strText;
	strText = _T("新建文件");
	m_pNewFileBtn = new QPushButton;
	m_pNewFileBtn->setText(strText);
	m_pNewFileBtn->setFont(*g_pSttGlobalFont);
	strText = _T("导入文件");
	m_pImportFileBtn = new QPushButton;
	m_pImportFileBtn->setText(strText);
	m_pImportFileBtn->setFont(*g_pSttGlobalFont);
	strText = _T("保存文件");
	m_pSaveFileBtn = new QPushButton;
	m_pSaveFileBtn->setText(strText);
	m_pSaveFileBtn->setFont(*g_pSttGlobalFont);
	
	QVBoxLayout *pFileBtnLayout = new QVBoxLayout;
	pFileBtnLayout->addWidget(m_pNewFileBtn);
	pFileBtnLayout->addWidget(m_pImportFileBtn);
	pFileBtnLayout->addWidget(m_pSaveFileBtn);

	strText = _T("删除行");
	m_pDeleteRowBtn = new QPushButton;
	m_pDeleteRowBtn->setText(strText);
	m_pDeleteRowBtn->setFont(*g_pSttGlobalFont);
	QLabel *lblInfo = new QLabel;
	strText = _T("第");
	lblInfo->setText(strText);
	lblInfo->setFont(*g_pSttGlobalFont);
	QLabel *lblTotal = new QLabel();
	strText = _T("共");
	lblTotal->setText(strText);
	lblTotal->setFont(*g_pSttGlobalFont);
	QLabel *lblItems = new QLabel();
	strText = _T("项");
	lblItems->setText(strText);
	lblItems->setFont(*g_pSttGlobalFont);
	QLabel *lblItems1 = new QLabel();
	lblItems1->setText(strText);
	lblItems1->setFont(*g_pSttGlobalFont);
	m_pInfoLineEdit = new QSttLineEdit;
	m_pInfoLineEdit->setFont(*g_pSttGlobalFont);
	m_pInfoLineEdit->setEnabled(false);
	m_pTotalLineEdit = new QSttLineEdit;
	m_pTotalLineEdit->setFont(*g_pSttGlobalFont);
	m_pTotalLineEdit->setEnabled(false);

	QHBoxLayout *pBottomLayout = new QHBoxLayout;
	pBottomLayout->addStretch(20);
	pBottomLayout->addWidget(m_pDeleteRowBtn);
	pBottomLayout->addSpacing(10);
	pBottomLayout->addWidget(lblInfo);
	pBottomLayout->addWidget(m_pInfoLineEdit);
	pBottomLayout->addWidget(lblItems);
	pBottomLayout->addWidget(lblTotal);
	pBottomLayout->addWidget(m_pTotalLineEdit);
	pBottomLayout->addWidget(lblItems1);
	pBottomLayout->setAlignment(Qt::AlignRight);


	QHBoxLayout *pMainLayout = new QHBoxLayout;
	pMainLayout->addLayout(pFileBtnLayout);
	pMainLayout->addSpacing(10);
	pMainLayout->addWidget(m_pFreqFileTableWidget);

	QVBoxLayout *pMainVBoxLayout = new QVBoxLayout(this);
	pMainVBoxLayout->addLayout(pMainLayout);
	pMainVBoxLayout->addLayout(pBottomLayout);
	setLayout(pMainVBoxLayout);

	setFocusPolicy(Qt::StrongFocus);

}

void QFreqFileWidget::InitTable()
{
	m_pFreqFileTableWidget = new QTableWidget;
	m_pFreqFileTableWidget->setColumnCount(4);
	m_pFreqFileTableWidget->setFont(*g_pSttGlobalFont);
	m_pFreqFileTableWidget->horizontalHeader()->setFont(*g_pSttGlobalFont);
    m_pFreqFileTableWidget->horizontalHeader()->setSectionsClickable(false);
	m_pFreqFileTableWidget->verticalHeader()->setVisible(false);
	QStringList  HStrList;
	HStrList << _T("序号") << _T("持续时间(ms)") << _T("频率(Hz)") << _T("直流电流(mA)");
	m_pFreqFileTableWidget->setHorizontalHeaderLabels(HStrList); 
	m_pFreqFileTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	m_pFreqFileTableWidget->horizontalHeader()->setStretchLastSection(true); 
    m_pFreqFileTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_pFreqFileTableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
	m_pFreqFileTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pFreqFileTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}


void QFreqFileWidget::InitConnect()
{
	connect(m_pNewFileBtn, SIGNAL(clicked()), this, SLOT(slot_NewFileBtn_Clicked()));	
	connect(m_pImportFileBtn, SIGNAL(clicked()), this, SLOT(slot_ImportFileBtn_Clicked()));	
	connect(m_pSaveFileBtn, SIGNAL(clicked()), this, SLOT(slot_SaveFileBtn_Clicked()));	
	connect(m_pDeleteRowBtn, SIGNAL(clicked()), this, SLOT(slot_DeleteRowBtn_Clicked()));	
	connect(m_pFreqFileTableWidget, SIGNAL(cellChanged (int,int)), this, SLOT(slot_OnCellChanged(int,int)));
	connect(this,SIGNAL(sig_ExportFile()),this,SLOT(slot_ExportFile()),Qt::BlockingQueuedConnection);
	connect((QObject *)m_pCurScrollBar , SIGNAL(valueChanged (int)) , this , SLOT(getValue(int)));  
	connect(m_pFreqFileTableWidget->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(slot_OnSelectionChanged()));
}

void QFreqFileWidget::SetData( tmt_FreqOutputParas *pFreqOutputParas )
{
	m_pFreqOutputParas = pFreqOutputParas;

	if (m_pFreqFileTableWidget == NULL)
	{
		return;
	}

	m_pFreqFileTableWidget->setColumnHidden(2, false);
	m_pFreqFileTableWidget->setColumnHidden(3, false);

	if (m_pFreqOutputParas->m_nOutPutType == 0) // 电压电流
	{        
		m_pFreqFileTableWidget->setColumnHidden(3, true);
	}
	else if (m_pFreqOutputParas->m_nOutPutType == 1) // 直流信号源
	{
		m_pFreqFileTableWidget->setColumnHidden(2, true);
	}
	else // 其他情况
	{
		m_pFreqFileTableWidget->setColumnHidden(2, true);
		m_pFreqFileTableWidget->setColumnHidden(3, true);
	}
}

void QFreqFileWidget::CalTableRow()
{
	m_nDataCount = m_pFreqOutputParas->m_nStateCount;
	m_pTotalLineEdit->setText(QString::number(m_nDataCount));
	m_pFreqFileTableWidget->setRowCount(m_nDataCount);

	m_pCurScrollBar = m_pFreqFileTableWidget->verticalScrollBar();
	int row_Hei = m_pFreqFileTableWidget->rowHeight(1);                                      //每行的高度
	int scrollHeight = m_pFreqFileTableWidget->maximumViewportSize().height();               //获取滚动条的滚动范围
	float rowN = (float)scrollHeight/(float)row_Hei + 1;

	if (row_Hei == 0)
	{
		rowN = 1;
	}

	m_nTabPageRowN = (int)rowN;

	if (m_nDataCount > 0)
	{
		int a = 1 / m_nDataCount;

		if (rowN - m_nTabPageRowN >a )
		{
			m_nTabPageRowN++;
		}	
	}
}

void QFreqFileWidget::ShowData()
{
	long nMaxRowNum = m_nTabPageRowN;

	if (nMaxRowNum > m_pFreqOutputParas->m_nStateCount)
	{
		nMaxRowNum = m_pFreqOutputParas->m_nStateCount;
	}

	for (int i = 0 ; i < nMaxRowNum ; i++)
	{	
		UpdateData(i);
	}
}

void QFreqFileWidget::UpdateData(int nRow)
{
	QTableWidgetItem *item = NULL; 
	
	//序号
	item = new QTableWidgetItem();
	item->setFlags(item->flags() & (~Qt::ItemIsEditable));
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setText(QString("%1").arg(nRow+1));
	m_pFreqFileTableWidget->setItem(nRow, 0, item); 

	//持续时间
	item = new QTableWidgetItem();
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setFlags(item->flags() | Qt::ItemIsEditable);
	item->setText(QString::number(m_pFreqOutputParas->m_oFreqOutputPara[nRow].m_fHoldTime,'f',0));
	m_pFreqFileTableWidget->setItem(nRow, 1, item); 

	//频率
	item = new QTableWidgetItem();
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setFlags(item->flags() | Qt::ItemIsEditable);
	item->setText(QString::number(m_pFreqOutputParas->m_oFreqOutputPara[nRow].m_fFrequency,'f',4));
	m_pFreqFileTableWidget->setItem(nRow, 2, item); 


	//直流电流
	item = new QTableWidgetItem();
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setFlags(item->flags() | Qt::ItemIsEditable);
	item->setText(QString::number(m_pFreqOutputParas->m_oFreqOutputPara[nRow].m_fDCCurrent,'f',4));
	m_pFreqFileTableWidget->setItem(nRow, 3, item); 
}

void QFreqFileWidget::slot_UpdateTable()
{
	//StartProgDlg(_T("新建文件进度条"));

	tmt_FreqOutputNewFile *oFreqOutputNewFile = &m_pFreqOutputParas->m_oFreqOutputNewFile;
	int nCount = 0;
	if (oFreqOutputNewFile->m_nSetType == 0)
	{
		nCount = oFreqOutputNewFile->m_nRowCount;
		
		for(int i = 0; i < nCount && i<FreqChange_Max_Count ; i++)
		{
			m_pFreqOutputParas->m_oFreqOutputPara[i].m_fHoldTime = oFreqOutputNewFile->m_fOutPutTime;
			m_pFreqOutputParas->m_oFreqOutputPara[i].m_fFrequency = oFreqOutputNewFile->m_fFrequency;
			m_pFreqOutputParas->m_oFreqOutputPara[i].m_fDCCurrent = oFreqOutputNewFile->m_fDCCurrent;
		}
	}
	else if (oFreqOutputNewFile->m_nSetType == 1)
	{
		float fSatrt = oFreqOutputNewFile->m_fStartFreq;
		float fEnd = oFreqOutputNewFile->m_fEndFreq;
		float fStep = oFreqOutputNewFile->m_fStepFreq/1000.0f;
		nCount = static_cast<int>((fEnd - fSatrt) / fStep) + 1;
		
		for(int i = 0; i < nCount && i<FreqChange_Max_Count ; i++)
		{
			float fFreq = fSatrt + i * fStep;
			m_pFreqOutputParas->m_oFreqOutputPara[i].m_fHoldTime = oFreqOutputNewFile->m_fFreqOutPutTime;
			m_pFreqOutputParas->m_oFreqOutputPara[i].m_fFrequency = fFreq;
			m_pFreqOutputParas->m_oFreqOutputPara[i].m_fDCCurrent = 12.0f;
		}
	}
	else if (oFreqOutputNewFile->m_nSetType == 2)
	{
		float fSatrt = oFreqOutputNewFile->m_fStartCurrent;
		float fEnd = oFreqOutputNewFile->m_fEndCurrent;
		float fStep = oFreqOutputNewFile->m_fStepCurrent;
		nCount = static_cast<int>((fEnd - fSatrt) / fStep) + 1;

		for(int i = 0; i < nCount && i<FreqChange_Max_Count ; i++)
		{
			float fDCCurrent = fSatrt + i * fStep;
			m_pFreqOutputParas->m_oFreqOutputPara[i].m_fHoldTime = oFreqOutputNewFile->m_fCurrentOutPutTime;
			m_pFreqOutputParas->m_oFreqOutputPara[i].m_fFrequency = 50.0f;
			m_pFreqOutputParas->m_oFreqOutputPara[i].m_fDCCurrent = fDCCurrent;
		}
	}
	m_pFreqOutputParas->m_nStateCount = nCount;

	m_pFreqFileTableWidget->clearContents();  
	m_pFreqFileTableWidget->setRowCount(0);
	
	m_nDataCount = m_pFreqOutputParas->m_nStateCount;
	m_pTotalLineEdit->setText(QString::number(m_nDataCount));
	m_pFreqFileTableWidget->setRowCount(m_nDataCount);
	ShowData();
}

void QFreqFileWidget::showEvent( QShowEvent *event )
{
	if (!m_bHasInitFinished)
	{
		InitUI();
		CalTableRow();
		ShowData();
		InitConnect();
		m_bHasInitFinished = true;
	}
	QWidget::showEvent(event);
}

#ifdef _PSX_QT_LINUX_
void* QFreqFileWidget::SttExportFileThread( LPVOID pParam )
#else
UINT QFreqFileWidget::SttExportFileThread( LPVOID pParam )
#endif
{
	QFreqFileWidget *pFreqFileWidget = (QFreqFileWidget*)pParam; 
	pFreqFileWidget->ParseData(pFreqFileWidget->m_strFilePath);
	emit pFreqFileWidget->sig_ExportFile();
	pFreqFileWidget->m_pSttExportFileThread = NULL;
#ifndef _PSX_QT_LINUX_
	return 1;
#endif
}

void QFreqFileWidget::slot_NewFileBtn_Clicked()
{
	QFreqNewFileDialog dlg(m_pFreqOutputParas,this);
	connect(&dlg, SIGNAL(sig_UpdateTable()),this,SLOT(slot_UpdateTable()));

	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
	disconnect(&dlg, SIGNAL(sig_UpdateTable()),this,SLOT(slot_UpdateTable()));
}


void QFreqFileWidget::slot_SaveFileBtn_Clicked()
{
	CString strFilePath;

#ifdef _PSX_QT_LINUX_
	CString strFolderPath;
	QStringList astrPostfix;
	strFolderPath = _P_GetWorkspacePath();
	astrPostfix<<"*.csv";
	QSttPopupSaveAsDialog dlg(strFolderPath, astrPostfix,"", this);
	dlg.InitUI();
	dlg.InitTitle(_T("保存 CSV 文件"));
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		dlg.resize(850,500);
		dlg.setFixedHeight(500);
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg,Keyboard::CHINESE);

	if (dlg.exec() != QDialog::Accepted)
	{
		QSoftKeyBoard::ReAttachObj();
		return;
	}
	QSoftKeyBoard::ReAttachObj();
#else
	if (dlg.exec() != QDialog::Accepted)
	{
		return;
	}
#endif
	strFilePath = dlg.GetFilePath();
#else		
	strFilePath = QFileDialog::getSaveFileName(NULL, "保存CSV文件", _P_GetWorkspacePath(), "CSV文件(*.csv)");
#endif

	if (!strFilePath.isEmpty()) 
	{
// 		CString strProgTitle;
// 		strProgTitle = _T("保存文件进度条");
// 		StartProgDlg(strProgTitle);

		QFile file(strFilePath);
#ifdef _PSX_QT_LINUX_
		QTextCodec *pOldTextCodec = NULL;
        InitLocalCodec_BeforeReadWrite(strFilePath,&pOldTextCodec);
#endif
		BOOL bRet = file.open(QIODevice::WriteOnly | QIODevice::Text);

#ifdef _PSX_QT_LINUX_
		ResetLocalCodec(pOldTextCodec);
#endif
		if (bRet)
		{
			//保存csv文件代码
			QTextStream out(&file);
			out.setCodec("UTF-8"); 
			int rowCount = m_pFreqFileTableWidget->rowCount();
			int columnCount = m_pFreqFileTableWidget->columnCount();

			  // 获取表头信息
			QStringList headerLabels;
			for (int col = 0; col < columnCount; ++col)
			{
				headerLabels << m_pFreqFileTableWidget->horizontalHeaderItem(col)->text();
			}
			out << headerLabels.join(",") << "\n";// 写入 CSV 表头
			// 写入表格内容
			for (int row = 0; row < rowCount; ++row) 
			{
				QStringList rowContents;
				for (int col = 0; col < columnCount; ++col) 
				{
					QTableWidgetItem* item = m_pFreqFileTableWidget->item(row, col);
					QString cellText = item ? item->text() : "";  // 如果单元格为空，设置为空字符串
					rowContents << cellText;
				}
				out << rowContents.join(",") << "\n";
			}

			file.close();
// 			setEnabled(true);
// 			m_pSttProgDlg->Stop();
			
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("文件%s保存成功."),strFilePath.GetString());  
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("无法打开文件%s."),strFilePath.GetString());  
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("文件%s保存失败."),strFilePath.GetString());  
	}


#ifdef _PSX_QT_LINUX_  
	system("sync");
#endif
}

void QFreqFileWidget::slot_ImportFileBtn_Clicked()
{
	CString strFilePath;
#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;
	CString strFolderPath;
	strFolderPath = _P_GetWorkspacePath();
	astrPostfix<<"*.csv";	
	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
	oOpenDlg.setFont(font());
	oOpenDlg.InitUI();

	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		oOpenDlg.resize(850,500);
		oOpenDlg.setFixedHeight(500);
	}

	if (oOpenDlg.exec() != QDialog::Accepted)
		return;

	if (!oOpenDlg.GetFilePath(strFilePath))
	{
		return;
	}
#else		
	strFilePath = QFileDialog::getOpenFileName(this, "导入CSV文件", _P_GetWorkspacePath(), "CSV文件(*.csv)");
	if(strFilePath.IsEmpty())
	{
		return;
	}
#endif
	m_strFilePath = strFilePath;

#ifdef _PSX_QT_LINUX_
	pthread_create(&m_pSttExportFileThread,NULL,SttExportFileThread,(LPVOID)this );
#else
	m_pSttExportFileThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttExportFileThread,(LPVOID)this,0,NULL);
#endif

	/*StartProgDlg(_T("导入文件进度条"));*/
}

void QFreqFileWidget::ParseData( CString &strFilePath )
{
	//解析CSV文件
	QFile file(strFilePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("无法打开文件 %s."), strFilePath.GetString());  
		return;
	}

	QTextStream in(&file);
	in.setCodec("UTF-8"); 

	int rowIndex = 0;
	int count = 0; // 记录有效数据条数
	m_headerLabels.clear();

	while (!in.atEnd()) 
	{
		QString line = in.readLine().trimmed();
		QStringList fields = line.split(',');

		if (rowIndex == 0) 
		{  // 第一行是表头
			m_headerLabels = fields;
// 			m_pFreqFileTableWidget->setColumnCount(fields.size());
// 			m_pFreqFileTableWidget->setHorizontalHeaderLabels(fields);
		} 
		else 
		{
			// 解析数据并存储到结构体
			if (fields.size() >= 4  && count < FreqChange_Max_Count) 
			{ 
				m_pFreqOutputParas->m_oFreqOutputPara[count].m_fHoldTime = fields[1].toFloat();  // 持续时间
				m_pFreqOutputParas->m_oFreqOutputPara[count].m_fFrequency = fields[2].toFloat(); // 频率
				m_pFreqOutputParas->m_oFreqOutputPara[count].m_fDCCurrent = fields[3].toFloat(); // 直流电流
				count++;
			}
		}
		rowIndex++;
	}
	file.close();
	m_pFreqOutputParas->m_nStateCount = count;
}


void QFreqFileWidget::slot_ExportFile()
{
	m_pFreqFileTableWidget->clear();  // 清除现有表格内容
	m_pFreqFileTableWidget->setRowCount(0);
	m_pFreqFileTableWidget->setColumnCount(m_headerLabels.size());
	m_pFreqFileTableWidget->setHorizontalHeaderLabels(m_headerLabels);
	
	m_nDataCount = m_pFreqOutputParas->m_nStateCount;
	m_pTotalLineEdit->setText(QString::number(m_nDataCount));
	m_pFreqFileTableWidget->setRowCount(m_nDataCount);
	ShowData();
}


void QFreqFileWidget::getValue( int val )
{
	int realRowN = val;  //获取tableWidget的行号
	int rowNchanged = 0;

	if (val  > m_nDataCount || val == 0)
	{
		return;
	}


	if(m_nDataCount - realRowN < m_nTabPageRowN )
	{
		rowNchanged = m_nDataCount - realRowN;
	}


	for (int i = 0 ; i < m_nTabPageRowN ; i++)
	{
		if( i == rowNchanged && i + realRowN == m_pFreqFileTableWidget->rowCount())   //最后一板面时不List范围溢出
		{
			break;
		}

		UpdateData(i + realRowN);
	}
}

void QFreqFileWidget::slot_DeleteRowBtn_Clicked()
{
	QDeleteRowDialog dlg(m_pFreqFileTableWidget->rowCount(),this);
	connect(&dlg, SIGNAL(sig_DelRow(int,int)),this,SLOT(slot_DelRow(int,int)));
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
	disconnect(&dlg, SIGNAL(sig_DelRow(int,int)),this,SLOT(slot_DelRow(int,int)));
}

void QFreqFileWidget::StartProgDlg(const CString &strTitle)
{
// 	if (m_pSttProgDlg == NULL)
// 	{
// 		m_pSttProgDlg = new QSttProgDlg(NULL);
// 		m_pSttProgDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
// 		m_pSttProgDlg->initUI(_T("文件进度条..."));
// 		m_pSttProgDlg->setModal(false);
// 		m_pSttProgDlg->move((this->width() - m_pSttProgDlg->width())/2,
// 			(this->height() - m_pSttProgDlg->height())/2);
// 	}
// 
// 	m_pSttProgDlg->setWindowTitle(strTitle);
// 	m_pSttProgDlg->Start();
// 	m_pSttProgDlg->show();
// 	setEnabled(false);
}


void QFreqFileWidget::slot_OnSelectionChanged()
{
	int row = m_pFreqFileTableWidget->currentRow();
	if (row >= 0)
	{
		m_pInfoLineEdit->setText(QString::number(row + 1));
	}
}

void QFreqFileWidget::slot_OnCellChanged( int row,int col )
{
	if (row  <  0)
	{
		return;
	}
 	disconnect(m_pFreqFileTableWidget, SIGNAL(cellChanged (int,int)), this, SLOT(slot_OnCellChanged(int,int)));

	QTableWidgetItem  *pItem  = m_pFreqFileTableWidget->item(row,col);
	//m_pInfoLineEdit->setText(QString::number(row+1));

	float fMax,fMin;
	long nUnit = 0;

	if (pItem == NULL)
	{
		return;
	} 
	float fv = pItem->text().toFloat();
	if(col == 1)
	{
		nUnit = 0;
		fMax = 3600;
		fv = setLimit(0,fMax,fv);
		m_pFreqOutputParas->m_oFreqOutputPara[row].m_fHoldTime = fv;
	}
	else if (col == 2)
	{
		nUnit = 4;
		fMax = 55;
		fMin = 45;
		fv = setLimit(fMin,fMax,fv);
		m_pFreqOutputParas->m_oFreqOutputPara[row].m_fFrequency = fv;

	}
	else if (col == 3)
	{
		nUnit = 4;
		fMax = 20;
		fv = setLimit(0,fMax,fv);
		m_pFreqOutputParas->m_oFreqOutputPara[row].m_fDCCurrent = fv;
	}
	pItem->setText(QString::number(fv,'f',nUnit));
	connect(m_pFreqFileTableWidget, SIGNAL(cellChanged (int,int)), this, SLOT(slot_OnCellChanged(int,int)));
}

void QFreqFileWidget::slot_DelRow( int nStartRow,int nEndRow)
{
	if (!m_pFreqFileTableWidget) return;
	int rowCount = m_pFreqFileTableWidget->rowCount();

	if (nStartRow < 0 || nEndRow >= rowCount || nStartRow > nEndRow) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("删除%d行-%d行范围无效"), nStartRow,nEndRow);
		return;
	}

	for (int row = nEndRow; row >= nStartRow; --row)
	{
		stt_state_paras_delete(m_pFreqOutputParas,row);
		m_pFreqFileTableWidget->removeRow(row);
	}
	m_pTotalLineEdit->setText(QString::number(m_pFreqOutputParas->m_nStateCount));

	m_nDataCount = m_pFreqFileTableWidget->rowCount();
	for (int i = 0; i < m_nDataCount; ++i)
	{
		QTableWidgetItem *item = m_pFreqFileTableWidget->item(i, 0);
		if (item)
		{
			item->setText(QString::number(i + 1)); 
		}
	}
}

QDeleteRowDialog::QDeleteRowDialog( int nRow ,QWidget* parent /*= NULL*/ ): QDialog(parent)
{
	setWindowTitle(_T("删除行"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(350, 200);
	setFixedSize(350,200);
	m_nMaxRow = nRow;
	InitUI();
}



QDeleteRowDialog::~QDeleteRowDialog()
{

}

void QDeleteRowDialog::InitUI()
{
	CString strText;
	QLabel *pStartRowLabel = new QLabel;
	pStartRowLabel->setFont(*g_pSttGlobalFont);
	strText = _T("起始行");
	pStartRowLabel->setText(strText);
	m_pStartRowEdit = new QSttLineEdit;
	m_pStartRowEdit->setFont(*g_pSttGlobalFont);
	QLabel *pEndRowLabel = new QLabel;
	pEndRowLabel->setFont(*g_pSttGlobalFont);
	strText = _T("终止行");
	pEndRowLabel->setText(strText);
	m_pEndRowEdit = new QSttLineEdit;
	m_pEndRowEdit->setFont(*g_pSttGlobalFont);
	QHBoxLayout* pRowHBoxLayout = new QHBoxLayout;
	pRowHBoxLayout->addStretch();
	pRowHBoxLayout->addWidget(pStartRowLabel);
	pRowHBoxLayout->addWidget(m_pStartRowEdit);
	pRowHBoxLayout->addSpacing(10);
	pRowHBoxLayout->addWidget(pEndRowLabel);
	pRowHBoxLayout->addWidget(m_pEndRowEdit);
	pRowHBoxLayout->addStretch();


	QPushButton* pOKBtn = new QPushButton(this);
	strText = _T("确定删除");
	pOKBtn->setFont(*g_pSttGlobalFont);
	pOKBtn->setText(strText);
	QPushButton* pCancelBtn = new QPushButton(this);
	strText = _T("取消");
	pCancelBtn->setFont(*g_pSttGlobalFont);
	pCancelBtn->setText(strText);
	QHBoxLayout* pOkCancel_HBoxLayout = new QHBoxLayout;
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->addWidget(pOKBtn);
	pOkCancel_HBoxLayout->addSpacing(10);
	pOkCancel_HBoxLayout->addWidget(pCancelBtn);
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addLayout(pRowHBoxLayout);
	pMainLayout->addLayout(pOkCancel_HBoxLayout);

	setLayout(pMainLayout);

	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));

	connect(m_pStartRowEdit, SIGNAL(editingFinished()), this, SLOT(slot_StartRowEditFinished()));
	connect(m_pEndRowEdit, SIGNAL(editingFinished()), this, SLOT(slot_EndRowEditFinished()));

}

void QDeleteRowDialog::slot_btnOK_Clicked()
{
	bool bStartOk, bEndOk;
	int nSatrtRow = m_pStartRowEdit->text().toInt(&bStartOk) - 1 ;
	int nEndRow = m_pEndRowEdit->text().toInt(&bEndOk) -1 ;

	// 确保输入是有效数字
	if (!bStartOk || !bEndOk) 
	{
		close();
		return;
	}

	emit sig_DelRow(nSatrtRow,nEndRow);
	accept();
}

void QDeleteRowDialog::slot_btnCancel_Clicked()
{
	close();
}

void QDeleteRowDialog::slot_StartRowEditFinished()
{
	int nSatrtRow = m_pStartRowEdit->text().toInt();
	int nEndRow = m_pEndRowEdit->text().toInt();

	  // 起始行号不能小于 1
	if (nSatrtRow < 1)
	{
		nSatrtRow = 1;
	}

	// 确保起始行号不会超过结束行号
	if (nSatrtRow > nEndRow)
	{
		nEndRow = nSatrtRow + 1;
		m_pEndRowEdit->setText(QString::number(nEndRow,'f',0));
	}

	m_pStartRowEdit->setText(QString::number(nSatrtRow,'f',0));

}

void QDeleteRowDialog::slot_EndRowEditFinished()
{
	int nSatrtRow = m_pStartRowEdit->text().toInt();
	int nEndRow = m_pEndRowEdit->text().toInt();

	// 结束行不能小于起始行
	if (nEndRow < nSatrtRow) 
	{
		nEndRow = nSatrtRow;
	}

	if (nEndRow > m_nMaxRow)
	{
		nEndRow = m_nMaxRow - 1;
	}

	m_pEndRowEdit->setText(QString::number(nEndRow,'f',0));
}
