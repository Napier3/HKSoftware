#include "QAsyncChannelTable.h"
#include <QFontMetrics>
#include <QScrollBar>
#include <cmath>
#include "../../../../Module/SttSystemConfig/SttSystemConfig.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"
#include "../../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"

#define GenHao3	1.7320508 //根号三

QAsyncChannelTable::QAsyncChannelTable( MOUDLEType moudleType, tmt_async_module * pAsyncModule,
									   int nChCount, int nBeginIndex/*= 0*/,bool bDc , QWidget *parent /*= 0*/ )
			: QTableWidget(parent)
{
	m_bUsekeyPressEventExec = false;
	m_bSendUpdateParas = true;
	m_bIsCurrentlyTesting = false;
	m_tableIndex = 0;
	m_moudleType = moudleType;
	m_pAsyncModule = pAsyncModule;
	m_bDCTest = bDc;
	m_ColorList<<QColor(240,240,240) <<QColor(205,205,205)<<QColor(167,183,181)<<QColor(168,169,171)<<QColor(240,240,240) <<QColor(205,205,205)<<QColor(167,183,181);
	m_ColumnNum = ASYNCTABLE_AC_COL_COUNT;

	m_fEDVal = 0;
	m_nChCount = nChCount;
	m_nBeginIndex = nBeginIndex;
	m_RowNum = GetChannelNum();
	m_nMinCoe = 0;

	init();
}

QAsyncChannelTable::~QAsyncChannelTable(void)
{

}

void QAsyncChannelTable::initTable()
{
	setColumnCount(m_ColumnNum);
	ASSERT(pAsyncModule);
	setRowCount(m_nChCount);
	
	QStringList headers;
	if (m_moudleType==Moudle_U)//U
	{
		if (m_ColumnNum == 4)
		{
			headers<<tr("选择")<</*tr("通道")*/g_sLangTxt_Native_Channel<</*tr("幅值(V)")*/g_sLangTxt_Native_amplitudeV<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase;
		}
		else
		{
			headers<<tr("选择")<</*tr("通道")*/g_sLangTxt_Native_Channel<</*tr("幅值(V)")*/g_sLangTxt_Native_amplitudeV<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase<</*tr("频率(Hz)")*/g_sLangTxt_Native_FreqHz;
		}
	}
	else
	{
		if (m_ColumnNum == 4)
		{
			headers<<tr("选择")<</*tr("通道")*/g_sLangTxt_Native_Channel<</*tr("幅值(A)")*/g_sLangTxt_Native_amplitudeA<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase;
		}
		else
		{
			headers<<tr("选择")<</*tr("通道")*/g_sLangTxt_Native_Channel<</*tr("幅值(A)")*/g_sLangTxt_Native_amplitudeA<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase<</*tr("频率(Hz)")*/g_sLangTxt_Native_FreqHz;
		}
	}

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	int nLabelWidth1 = fontMetrics.width(tr("选择"));
	int nLabelWidth2 = fontMetrics.width(/*tr("通道")*/g_sLangTxt_Native_Channel);
	int nLabelWidth3 = fontMetrics.width(tr("-57.735")) + 20;
	int nLabelWidth4 = fontMetrics.width(/*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase) + 10;


	this->setColumnWidth(0,nLabelWidth1);
	this->setColumnWidth(1,nLabelWidth2);
	this->setColumnWidth(2,nLabelWidth3);
	this->setColumnWidth(3,nLabelWidth4);

	if (m_ColumnNum > 4)
	{
		int nLabelWidth5 = fontMetrics.width(/*tr("频率(Hz)")*/g_sLangTxt_Native_FreqHz) + 20 ;
		this->setColumnWidth(5,nLabelWidth5);
	}

	setHorizontalHeaderLabels(headers);
	setIconSize(QSize(20,20));

	for (int row=0;row<GetChannelNum();row++)
	{
		for (int col=0;col<this->columnCount();col++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setTextAlignment(Qt::AlignCenter);

			if(col == ASYNCTABLE_SELECT)
			{
				QWidget* pWidget = new QWidget();
				QCheckBox *pCheck = new QCheckBox();
				QHBoxLayout* pLayout = new QHBoxLayout(pWidget);

				pLayout->addWidget(pCheck);
				pLayout->setAlignment(Qt::AlignCenter);
				pLayout->setContentsMargins(0, 0, 0, 0);
				pWidget->setLayout(pLayout);
// 				pWidget->setMinimumWidth(nLabelWidth1); // 设置 widget 的最小宽度为 100 像素
// 				pWidget->setMaximumWidth(nLabelWidth1+40); // 设置 widget 的最大宽度为 200 像素
				setCellWidget(row, col, pWidget);

// 				connect(pCheck,SIGNAL(stateChanged(int)),this,SLOT(slot_CheckStateChange(int)));

				m_CheckBoxList.append(pCheck);
			}
			if(col == ASYNCTABLE_CHNAME)
			{
				item->setFlags(item->flags()& ~ Qt::ItemIsEditable);
			}
			else
			{
				item->setFlags(item->flags()| Qt::ItemIsEditable);
			}
			setItem(row,col,item);
			setRowHeight(row,m_nRowHeight);
		}

	}

	int ntableHight = this->horizontalHeader()->height() + ((m_nRowHeight)*this->rowCount());

	setFixedHeight(ntableHight);
	creatTableMenu();
	changeTableColor();

	CSttDevConfig *pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

	if (pSttDevConfig->m_nDoubleClickEdit == 0)
	{
		setEditTriggers(QAbstractItemView::AllEditTriggers);
	}
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);

	initData();
	connect(this, SIGNAL(cellClicked(int, int)), this, SLOT(slot_tableCellClicked(int, int)));

}

void QAsyncChannelTable::init()
{

	setFocusPolicy(Qt::NoFocus);
	setContextMenuPolicy (Qt::CustomContextMenu);

	QHeaderView* pLeft = this->verticalHeader();
	pLeft->setDefaultSectionSize(25);
	pLeft->setClickable(false);
	pLeft->setVisible(false);

	QFont font1 = this->horizontalHeader()->font();
	font1.setBold(true);

	this->horizontalHeader()->setFont(font1);
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
	QFontMetrics fontHeaderViewMe = QFontMetrics(font1);
	m_nHeaderViewHeight = fontHeaderViewMe.height() + 20;
	QFont font2 = this->font();
	font2.setPointSize(9);
	this->setFont(font2);
	QFontMetrics fontRowMe = QFontMetrics(font2);
	m_nRowHeight = fontRowMe.height() + 20;

	this->horizontalScrollBar()->setEnabled(true);
	this->verticalScrollBar()->setEnabled(false);

	QDesktopWidget *pDeskTop = QApplication::desktop();
	QRect rcScreen = pDeskTop->screenGeometry();
	// 	if(rcScreen.width()<=1024 || rcScreen.height()<=768) //20220511 在1024*768时,4通道时显示不出来故注释掉
	// 	{
	// 		this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	//         this->horizontalHeader()->setStretchLastSection(true);
	// 	}
	// 	else
	{
		this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		this->horizontalHeader()->setResizeMode(QHeaderView::Stretch); 
	}

	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void QAsyncChannelTable::setColumnNum( int num )
{
	m_ColumnNum = num;
	initTable();
}

void QAsyncChannelTable::setProperty( bool bDCTest )
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	bool bTempDc = m_bDCTest;
	m_bDCTest = bDCTest;
	FloatAsyncTempChData *pData = NULL;

	tmt_async_channel *pCh = GetChannel();
	if (m_bDCTest)
	{
		setColumnHidden(ASYNCTABLE_ANGLE, true);
		setColumnHidden(ASYNCTABLE_FREQ, true);

		for (int i=0;i<GetChannelNum();i++)
		{
			if (item(i,0) == NULL)
			{
				break;
			}
			item(i,ASYNCTABLE_ANGLE)->setFlags(Qt::NoItemFlags);
			item(i,ASYNCTABLE_ANGLE)->setBackground(Qt::gray);
			item(i,ASYNCTABLE_FREQ)->setFlags(Qt::NoItemFlags);
			item(i,ASYNCTABLE_FREQ)->setBackground(Qt::gray);

			pCh[i].m_oHarm.bDC = 1;
		}
	}
	else
	{
		setColumnHidden(ASYNCTABLE_ANGLE, false);
		setColumnHidden(ASYNCTABLE_FREQ, false);

		for (int i=0;i<GetChannelNum();i++)
		{

			if(bDCTest != bTempDc)
			{
				pData = m_oTempSaveDataMap.value(i);
				pCh[i].m_oHarm.fAngle = pData->fAngle;
				pCh[i].m_oHarm.fFreq = pData->fHz;
			}

			if (item(i,0) == NULL)
			{
				break;
			}
			item(i,ASYNCTABLE_ANGLE)->setFlags(item(i,ASYNCTABLE_AMP)->flags());
			item(i,ASYNCTABLE_ANGLE)->setBackground(item(i,ASYNCTABLE_AMP)->background());
			item(i,ASYNCTABLE_FREQ)->setFlags(item(i,ASYNCTABLE_AMP)->flags());
			item(i,ASYNCTABLE_FREQ)->setBackground(item(i,ASYNCTABLE_AMP)->background());

			item(i,ASYNCTABLE_FREQ)->setText(QString::number(pCh[i].m_oHarm.fFreq,'f',3));
			item(i,ASYNCTABLE_ANGLE)->setText(QString::number(pCh[i].m_oHarm.fAngle,'f',2));//zhouhj相位精度改为2位  20220901

			pCh[i].m_oHarm.bDC = 0;
		}
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	
	if(m_moudleType == Moudle_I)
	{
		setAmpEDValue(g_oSystemParas.m_fINom);
	}
	else
	{
		setAmpEDValue(g_oSystemParas.m_fVNom);
	}

}

void QAsyncChannelTable::setItemValue( int row,int col,float fv )
{
	if (row<rowCount()&&col<columnCount())
	{
		if (col>0&&col<columnCount())
		{
			QString strTmp;

			if (col==ASYNCTABLE_ANGLE)
			{
				strTmp = QString::number(fv,'f',2);
				item(row,col)->setText(strTmp);//zhouhj相位精度改为2位  20220901
			}
			else
			{
				strTmp = QString::number(fv,'f',3);
				item(row,col)->setText(strTmp);
			}
		}
	}
}

void QAsyncChannelTable::UpdateTable()
{
	ASSERT(m_pAsyncModule);

	tmt_async_channel *pCh = GetChannel();
	QTableWidgetItem *pTableWidgetItem = NULL;
	m_oTempSaveDataMap.clear();


	for(int nRow = 0;nRow < GetChannelNum();nRow++)
	{
		for(int nCol = 0; nCol < m_ColumnNum; nCol++)
		{
			pTableWidgetItem = item(nRow,0);
			if (pTableWidgetItem == NULL)
			{
				break;
			}

			QCheckBox *pCheckBox = m_CheckBoxList[nRow];
			pCheckBox->setChecked(pCh[nRow].m_oHarm.m_bSelect);
			item(nRow,ASYNCTABLE_CHNAME)->setText(GetChName(m_moudleType,nRow));
			item(nRow,ASYNCTABLE_AMP)->setText(QString::number(pCh[nRow].m_oHarm.fAmp,'f',3));
			item(nRow,ASYNCTABLE_ANGLE)->setText(QString::number(pCh[nRow].m_oHarm.fAngle,'f',2));//zhouhj相位精度改为2位  20220901
			item(nRow,ASYNCTABLE_FREQ)->setText(QString::number(pCh[nRow].m_oHarm.fFreq,'f',3));

		}			
			FloatAsyncTempChData *ptempData = new FloatAsyncTempChData;
			ptempData->fAngle = pCh[nRow].m_oHarm.fAngle;
			ptempData->fHz = pCh[nRow].m_oHarm.fFreq;
			m_oTempSaveDataMap.insert(nRow,ptempData);
	}

	if(m_moudleType == Moudle_I)
	{
		setAmpEDValue(g_oSystemParas.m_fINom);
	}
	else
	{
		setAmpEDValue(g_oSystemParas.m_fVNom);
	}

	changeTableColor();

}

void QAsyncChannelTable::setTableData( tmt_async_module *pModule,int nChCount,int nBeginIndex/*= 0*/ )
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));

	m_pAsyncModule = pModule;
	m_nChCount = nChCount;
	m_nBeginIndex = nBeginIndex;
	UpdateTable();

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);

}

void QAsyncChannelTable::setHeaderOfTable( QStringList strheader )
{
	QString str = strheader.at(1);
	if (str.contains(tr("A")))
	{
		m_ActIAmp1->setText(tr("1A"));
		m_ActIAmp5->setText(tr("5A"));
	}

	if (str.contains(tr("V")))
	{
		if (str.contains(tr("KV")))
		{
// 			m_dispmode = V_Primary;
		}
		else
		{
// 			m_dispmode = V_Secondary;
		}
	}


	setHorizontalHeaderLabels(strheader);
}

void QAsyncChannelTable::creatTableMenu()
{
	m_MenuAmp = new QMenu(this);
	m_MenuPhase = new QMenu(this);
	m_MenuFre = new QMenu(this);
	m_MenuSelect = new QMenu(this);

	if (m_moudleType==Moudle_U)//电压模块
	{
		m_ActUAmpED = new QAction(/*tr("额定相电压")*/g_sLangTxt_Native_EDPhaseV,this);
		m_ActUZero = new QAction(/*tr("零")*/g_sLangTxt_Native_Zero,this);
		m_ActUEqualAmp = new QAction(/*tr("等幅值")*/g_sLangTxt_Native_EqualAmp,this);
		connect (m_ActUAmpED,SIGNAL(triggered()),this,SLOT(slot_ActUAmpEDClicked())); 
		connect (m_ActUZero,SIGNAL(triggered()),this,SLOT(slot_ActUZeroClicked()));
		connect (m_ActUEqualAmp,SIGNAL(triggered()),this,SLOT(slot_ActUEqualAmpClicked())); 
		m_MenuAmp->addAction(m_ActUAmpED); 
		m_MenuAmp->addAction(m_ActUZero);
		m_MenuAmp->addAction(m_ActUEqualAmp);
	}
	else//电流模块
	{
		m_ActIAmp1 = new QAction(tr("1A"),this);
		m_ActIAmp5 = new QAction(tr("5A"),this);
		m_ActIAmp0 = new QAction(/*tr("零")*/g_sLangTxt_Native_Zero,this);
		m_ActIqualAmp = new QAction(/*tr("等幅值")*/g_sLangTxt_Native_EqualAmp,this);
		m_ActIAmpED = new QAction(/*tr("额定电流")*/g_sLangTxt_Native_EDCurrent,this);

		connect (m_ActIAmp1,SIGNAL(triggered()),this,SLOT(slot_ActIAmp1Clicked())); 
		connect (m_ActIAmp5,SIGNAL(triggered()),this,SLOT(slot_ActIAmp5Clicked()));
		connect (m_ActIAmp0,SIGNAL(triggered()),this,SLOT(slot_ActIAmp0Clicked())); 
		connect (m_ActIqualAmp,SIGNAL(triggered()),this,SLOT(slot_ActIqualAmpClicked())); 
		connect (m_ActIAmpED,SIGNAL(triggered()),this,SLOT(slot_ActIAmpEDClicked())); 

		m_MenuAmp->addAction(m_ActIAmp1);
		m_MenuAmp->addAction(m_ActIAmp5); 
		m_MenuAmp->addAction(m_ActIAmp0); 
		m_MenuAmp->addAction(m_ActIqualAmp); 
		m_MenuAmp->addAction(m_ActIAmpED);
	}

	QAction *m_ActUPhaseP = new QAction(/*tr("正序")*/g_sLangTxt_Native_PositiveSeq,this);
	QAction *m_ActUPhaseN = new QAction(/*tr("负序")*/g_sLangTxt_Native_NegativeSeq,this);
	QAction *m_ActUPhaseZ = new QAction(/*tr("零序")*/g_sLangTxt_Native_ZeroSeq,this);
	connect (m_ActUPhaseP,SIGNAL(triggered()),this,SLOT(slot_ActPhasePClicked())); 
	connect (m_ActUPhaseN,SIGNAL(triggered()),this,SLOT(slot_ActPhaseNClicked()));
	connect (m_ActUPhaseZ,SIGNAL(triggered()),this,SLOT(slot_ActPhaseZClicked())); 
	m_MenuPhase->addAction(m_ActUPhaseP);
	m_MenuPhase->addAction(m_ActUPhaseN); 
	m_MenuPhase->addAction(m_ActUPhaseZ); 

	QAction *m_ActIHz50 = new QAction(tr("50Hz"),this);
	QAction *m_ActIHz60 = new QAction(tr("60Hz"),this);
	QAction *m_ActIHzEqual = new QAction(/*tr("等频率")*/g_sLangTxt_Native_EqualFreq,this);
	QAction *m_ActIHzEqualAll = new QAction(/*tr("等全部频率")*/g_sLangTxt_Native_all_frequencies,this);

	connect (m_ActIHz50,SIGNAL(triggered()),this,SLOT(slot_ActHz50Clicked())); 
	connect (m_ActIHz60,SIGNAL(triggered()),this,SLOT(slot_ActHz60Clicked()));
	connect (m_ActIHzEqual,SIGNAL(triggered()),this,SLOT(slot_ActHzEqualClicked()));
	connect (m_ActIHzEqualAll,SIGNAL(triggered()),this,SLOT(slot_ActHzEqualAllClicked()));

	m_MenuFre->addAction(m_ActIHz50);
	m_MenuFre->addAction(m_ActIHz60); 
	m_MenuFre->addAction(m_ActIHzEqual); 
	m_MenuFre->addAction(m_ActIHzEqualAll); 

	m_ActSelectAll = new QAction(tr("全选"),this);
	m_ActUnSelectAll= new QAction(tr("全不选"),this);
	m_ActToggleAll = new QAction(tr("反选"),this);

	connect (m_ActSelectAll,SIGNAL(triggered()),this,SLOT(slot_ActSelAll())); 
	connect (m_ActUnSelectAll,SIGNAL(triggered()),this,SLOT(slot_ActUnselAll()));
	connect (m_ActToggleAll,SIGNAL(triggered()),this,SLOT(slot_ActToggleAll()));

	m_MenuSelect->addAction(m_ActSelectAll);
	m_MenuSelect->addAction(m_ActUnSelectAll); 
	m_MenuSelect->addAction(m_ActToggleAll); 

	connect(this, SIGNAL(customContextMenuRequested ( const QPoint & )), this, SLOT(slot_TableShowMent(QPoint)));

}

void QAsyncChannelTable::slot_ActUAmpEDClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	Act_setUIAmpValue(pItem,m_fEDVal / GenHao3,FALSE);
}

void QAsyncChannelTable::slot_ActUEqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	float fVal = pItem->text().toFloat();

 	Act_setUIAmpValue(pItem,fVal);
}

void QAsyncChannelTable::slot_ActIAmp1Clicked()
{
	tmt_AsyncChannel *pChs = GetChannel();
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem)
	{
		if(pChs[pItem->row()].m_oHarm.m_bSelect)
		{
		pItem->setText(QString::number(1,'f',3));
	}
	}
}

void QAsyncChannelTable::slot_ActIAmp5Clicked()
{
	tmt_AsyncChannel *pChs = GetChannel();
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem)
	{
		if(pChs[pItem->row()].m_oHarm.m_bSelect)
		{
		pItem->setText(QString::number(5,'f',3));
	}
	}
}

void QAsyncChannelTable::slot_ActIAmp0Clicked()
{
	tmt_AsyncChannel *pChs = GetChannel();
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem)
	{
		if(pChs[pItem->row()].m_oHarm.m_bSelect)
		{
		pItem->setText(QString::number(0,'f',3));
	}
	}
}

void QAsyncChannelTable::slot_ActIqualAmpClicked()
{
	tmt_AsyncChannel *pChs = GetChannel();
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	float fVal = pItem->text().toFloat();
	Act_setUIAmpValue(pItem,fVal);
}

void QAsyncChannelTable::slot_ActIAmpEDClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	Act_setUIAmpValue(pItem,m_fEDVal,FALSE);
}

void QAsyncChannelTable::Act_setPrasePValue(int nSwitch,int nOffset,float fv)
{
	float fVal1 = 0,fVal2 = 0;
	long nMaxCount = rowCount();

	switch(nSwitch)
	{
	case 0:
		fVal1 = fv-120;
		fVal2 = fv+120;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);

		if ((nOffset+2)<nMaxCount)
		{
			if (m_CheckBoxList[nOffset + 1]->checkState() == Qt::Checked)
			{
				item(nOffset + 1, ASYNCTABLE_ANGLE)->setText(QString::number(fVal1, 'f', 2));
			}
			if (m_CheckBoxList[nOffset + 2]->checkState() == Qt::Checked)
			{
				item(nOffset + 2, ASYNCTABLE_ANGLE)->setText(QString::number(fVal2, 'f', 2));
			}
		}
		else if ((nOffset+1)<nMaxCount)
		{
			if (m_CheckBoxList[nOffset + 1]->checkState() == Qt::Checked)
			{
				item(nOffset + 1, ASYNCTABLE_ANGLE)->setText(QString::number(fVal1, 'f', 2));
			}
		}

		break;
	case 1:
		fVal1 = fv+120;
		fVal2 = fv+240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		if (m_CheckBoxList[nOffset]->checkState() == Qt::Checked)
		{
			item(nOffset, ASYNCTABLE_ANGLE)->setText(QString::number(fVal1, 'f', 2));
		}

		if ((nOffset + 2) < nMaxCount)
		{
			if (m_CheckBoxList[nOffset + 1]->checkState() == Qt::Checked)
		{
				item(nOffset + 2, ASYNCTABLE_ANGLE)->setText(QString::number(fVal2, 'f', 2));
			}
		}

		break;
	case 2:
		fVal1 = fv-120;
		fVal2 = fv-240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		if (m_CheckBoxList[nOffset]->checkState() == Qt::Checked)
		{
			item(nOffset, ASYNCTABLE_ANGLE)->setText(QString::number(fVal1, 'f', 2));
		}
		if (m_CheckBoxList[nOffset + 1]->checkState() == Qt::Checked)
		{
			item(nOffset + 1, ASYNCTABLE_ANGLE)->setText(QString::number(fVal2, 'f', 2));
		}
		break;
	default:
		break;
	}
}

void QAsyncChannelTable::Act_setPraseNValue(int nSwitch,int nOffset,float fv)
{
	float fVal1 = 0,fVal2 = 0;
	long nMaxCount = rowCount();

	switch(nSwitch)
	{
	case 0:
		fVal1 = fv+120;
		fVal2 = fv-120;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);

		if ((nOffset+2)<nMaxCount)
		{
			if (m_CheckBoxList[nOffset + 1]->checkState() == Qt::Checked)
			{
				item(nOffset + 1, ASYNCTABLE_ANGLE)->setText(QString::number(fVal1, 'f', 2));
			}
			if (m_CheckBoxList[nOffset + 2]->checkState() == Qt::Checked)
			{
				item(nOffset + 2, ASYNCTABLE_ANGLE)->setText(QString::number(fVal2, 'f', 2));
			}
		}
		else if ((nOffset+1)<nMaxCount)
		{
			if (m_CheckBoxList[nOffset + 1]->checkState() == Qt::Checked)
			{
				item(nOffset + 1, ASYNCTABLE_ANGLE)->setText(QString::number(fVal1, 'f', 2));
			}
		}

		break;
	case 1:
		fVal1 = fv-120;
		fVal2 = fv-240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		if (m_CheckBoxList[nOffset]->checkState() == Qt::Checked)
		{
			item(nOffset, ASYNCTABLE_ANGLE)->setText(QString::number(fVal1, 'f', 2));
		}

		if ((nOffset+2)<nMaxCount)
		{
			if (m_CheckBoxList[nOffset + 1]->checkState() == Qt::Checked)
			{
				item(nOffset + 2, ASYNCTABLE_ANGLE)->setText(QString::number(fVal2, 'f', 2));
			}
		}

		break;
	case 2:
		fVal1 = fv+120;
		fVal2 = fv+240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);

		if (m_CheckBoxList[nOffset]->checkState() == Qt::Checked)
		{
			item(nOffset, ASYNCTABLE_ANGLE)->setText(QString::number(fVal1, 'f', 2));
		}

		if (m_CheckBoxList[nOffset + 1]->checkState() == Qt::Checked)
		{
			item(nOffset + 1, ASYNCTABLE_ANGLE)->setText(QString::number(fVal2, 'f', 2));
		}
		break;
	default:
		break;
	}
}

void QAsyncChannelTable::slot_ActPhasePClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	int row = pItem->row();
	float fv = pItem->text().toFloat();
// 	ASSERT(m_pChDatas);

	if (m_moudleType==Moudle_U)	//电压模块
	{
		if (GetChannelNum()==4)
		{
			Act_setPrasePValue(row,0,fv);
		}
		else/* if ((m_pChDatas->GetCount() % 3) == 0)*///zhouhj 20210624  需要考虑不为3的整数倍的情况
		{
			int imin = (int(row/3))*3;
			Act_setPrasePValue(row%3,imin,fv);
		}
	}
	else						//电流模块
	{
		int imin = (int(row/3))*3;
		Act_setPrasePValue(row%3,imin,fv);
	}
}

void QAsyncChannelTable::slot_ActPhaseNClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	int row = pItem->row();
	float fv = pItem->text().toFloat();
	ASSERT(m_pChDatas);

	if (m_moudleType==Moudle_U)
	{
		if (m_pAsyncModule->m_nVolChCount==4)
		{
			Act_setPraseNValue(row,0,fv);
		}
		else /*if ((m_pChDatas->GetCount() % 3) == 0)*/
		{
			int imin = (int(row/3))*3;
			Act_setPraseNValue(row%3,imin,fv);
		}
	}
	else
	{
		int imin = (int(row/3))*3;
		Act_setPraseNValue(row%3,imin,fv);
	}
}

void QAsyncChannelTable::Act_setPraseZValue(int nStart,int nEnd)
{
	QString strVal = QString::number(0,'f',2);//zhouhj相位精度改为2位  20220901
	long nMaxCount = rowCount();
	tmt_AsyncChannel *pChs = GetChannel();

	if (nEnd>=nMaxCount)
	{
		nEnd = (nMaxCount-1);
	}

	for (int i=nStart; i<=nEnd; i++)
	{
		if(pChs[i].m_oHarm.m_bSelect)
		{
		item(i,ASYNCTABLE_ANGLE)->setText(strVal);
	}
	}
}

void QAsyncChannelTable::slot_ActPhaseZClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	int row = pItem->row();
	ASSERT(m_pChDatas);

	if (m_moudleType==Moudle_U)//电压模块
	{
		if (GetChannelNum()==4)
		{
			Act_setPraseZValue(0,3);
		}
		else/* if ((m_pChDatas->GetCount() % 3) == 0)*/
		{
			int imin = (int(row/3))*3;
			Act_setPraseZValue(imin,imin+2);
		}
	}
	else
	{
		int imin = (int(row/3))*3;
		Act_setPraseZValue(imin,imin+2);
	}
}
void QAsyncChannelTable::slot_ActHz50Clicked()
{
	tmt_AsyncChannel *pChs = GetChannel();

	if (m_bDCTest==false)
	{
		QTableWidgetItem *pItem = this->currentItem();
		if (pItem)
		{
			if(pChs[pItem->row()].m_oHarm.m_bSelect)
			{
				pItem->setText(QString::number(50,'f',3));	
			}
		}
	}
}

void QAsyncChannelTable::slot_ActHz60Clicked()
{
	tmt_AsyncChannel *pChs = GetChannel();

	if (m_bDCTest==false)
	{
		QTableWidgetItem *pItem = this->currentItem();
		if (pItem)
		{
			if(pChs[pItem->row()].m_oHarm.m_bSelect)
			{
			pItem->setText(QString::number(60,'f',3));
		}
		}
	}	
}

void QAsyncChannelTable::Act_setHzEqualValue(int nStart,int nEnd,float fv)
{
	QString strVal = QString::number(fv,'f',3);
	tmt_AsyncChannel *pChs = GetChannel();

	for (int i=nStart; i<=nEnd; i++)
	{
		if(i>GetChannelNum()-1)
		{
			break;
		}
		if(pChs[i].m_oHarm.m_bSelect)
		{
		item(i,ASYNCTABLE_FREQ)->setText(strVal);
	}
	}
}

void QAsyncChannelTable::slot_ActHzEqualClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	ASSERT(m_pChDatas);
	int row = pItem->row();
	float fv = pItem->text().toFloat();

	if (GetChannelNum()==4)
	{
		Act_setHzEqualValue(0,3,fv);
	}
	else
	{
		int imin = (int(row/3))*3;
		int imax = imin +2;
		Act_setHzEqualValue(imin,imax,fv);
	}
}

void QAsyncChannelTable::slot_ActHzEqualAllClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	ASSERT(m_pChDatas);
	int row = pItem->row();
	float fv = pItem->text().toFloat();
	if (GetChannelNum()==4)
	{
		Act_setHzEqualValue(0,3,fv);
	}
	else
	{
		int imin = 0;
		int imax = GetChannelNum();
		Act_setHzEqualValue(imin,imax,fv);
	}
}

void QAsyncChannelTable::slot_ActSelAll()
{
// 	tmt_AsyncChannel *pCh = GetChannel();
	QCheckBox *pCheckBox = NULL;
	for(int i = 0;i<m_CheckBoxList.size();i++)
	{
		pCheckBox = m_CheckBoxList[i];
		pCheckBox->setChecked(TRUE);
	}
}

void QAsyncChannelTable::slot_ActUnselAll()
{
	QCheckBox *pCheckBox = NULL;
	for(int i = 0;i<m_CheckBoxList.size();i++)
	{
		pCheckBox = m_CheckBoxList[i];
		pCheckBox->setChecked(FALSE);
	}
}

void QAsyncChannelTable::slot_ActToggleAll()
{
	QCheckBox *pCheckBox = NULL;
	for(int i = 0; i < m_CheckBoxList.size(); i++)
	{
		pCheckBox = m_CheckBoxList[i];
		pCheckBox->setChecked(!pCheckBox->isChecked());
	}
}

void QAsyncChannelTable::slot_OnCellChanged( int row,int col )
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	QTableWidgetItem  *pItem  = this->item(row,col);
	QString str = pItem->text();
	QString strInfo;
	float fv;
	QString strText;
	bool bChg = false;

	tmt_AsyncChannel *pCurChList = GetChannel();
	if(!pCurChList)
	{
		return;
	}
	tmt_AsyncChannel *pCurCh = &pCurChList[row];

	float fAcAmpMax = pCurCh->m_fChACMax;
	float fDcAmpMax = pCurCh->m_fChDCMax;
	
	float fAcAmpMin = m_nMinCoe * pCurCh->m_fChACMax;
	float fDcAmpMin = m_nMinCoe * pCurCh->m_fChDCMax;
// 	if(m_moudleType == )
	FloatAsyncTempChData *pTempChData = m_oTempSaveDataMap.value(row);

	switch (col)
	{
	case ASYNCTABLE_AMP:
		{
			fv = str.toFloat();
			if (m_bDCTest)
			{
				if (fabs(fv) > fDcAmpMax)
				{
					if (fv > 0)
					{
						fv = fDcAmpMax;
					}
					else
					{
						fv = -fDcAmpMax;
					}

					CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("输入值%f(%d,%d)超出范围(%f).")*/g_sLangTxt_Native_input_overrange.GetString(),fv,row,col,pCurCh->m_fChDCMax);
				}
				else if (fv<fDcAmpMin)
				{
					fv = 0;
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("输入值%f(%d,%d)超出范围(%f).")*/g_sLangTxt_Native_input_overrange.GetString(),fv,row,col,0);
				}

				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}
			else 
			{
				if (isPosiDigitstr(str))
				{
/*					str = initMaxAcV(str);*/

					fv = str.toFloat();

					if(fv - fAcAmpMax > 0)
					{						
						CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("输入值%f超出范围(%f).")*/g_sLangTxt_Native_InputOutOfRange.GetString(),fv,fAcAmpMax);			
						fv = fAcAmpMax;
					}
					if (fv < fAcAmpMin)
					{
						CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("输入值%f(%d,%d)超出范围(%f).")*/g_sLangTxt_Native_input_overrange.GetString(),fv,row,col,0);
						fv = fAcAmpMin;
					}
					pItem->setText(QString::number(fv,'f',3));
				}
				else
				{
					CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("输入值含有非法字符.")*/g_sLangTxt_State_IlleInputCharac.GetString());

					fv = pCurCh->m_oHarm.fAmp;
					if (fv > fAcAmpMax)
					{
						fv = fAcAmpMax;
					}

					if (fv < fAcAmpMin)
					{
						fv = fAcAmpMin;
					}

					strText.setNum(fv,'f',3);
					pItem->setText(strText);
				}
			}

			if(pCurCh->m_oHarm.fAmp != fv)
			{
				pCurCh->m_oHarm.fAmp = fv;
				bChg = true;
			}

		}
		break;
	case ASYNCTABLE_ANGLE:
		{
			fv = str.toFloat();
			float f1 = fv - (int)fv;
			int f2 = ((int)fv)%360;
			fv = f1+f2;

			if (m_bDCTest)//zhouhj 20211031 在直流的模式下,相位固定为0
			{
				fv = 0;
				CString strText = pItem->text();
				pTempChData->fAngle = strText.toFloat();
			}

			strText.setNum(fv,'f',2); //zhouhj相位精度改为2位  20220901
			pItem->setText(strText);

			if(pCurCh->m_oHarm.fAngle != fv)
			{
				pCurCh->m_oHarm.fAngle = fv;
				bChg = true;
			}

		}
		break;	
	case ASYNCTABLE_FREQ:
		{
			if (isPosiDigitstr(str))
			{
				str = initMaxHz(str);
				fv = str.toFloat();

				if (m_bDCTest)
				{
					CString strText = pItem->text();
					pTempChData->fHz = strText.toFloat();
					//					if (fv < 0)  //zhouhj 20211031 在直流的模式下,频率固定为0
					{
						fv = 0;
					}
				}
				else
				{
					if (fv < 0.001)
					{
						fv = 0;
					}
				}

				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}
			else
			{
				fv = pCurCh->m_oHarm.fFreq;
				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}

			if(pCurCh->m_oHarm.fFreq != fv)
			{
				pCurCh->m_oHarm.fFreq = fv;
				bChg = true;
			}
		}
		break;
	default:
		break;
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);

	if (col > 0 && bChg && m_bSendUpdateParas)
	{
		emit sig_ChannelValueChanged();
	}

}

void QAsyncChannelTable::slot_TableShowMent( QPoint pos )
{
	//获得鼠标点击的x，y坐标点 
	int x = pos.x(); 
	int y = pos.y(); 
	QModelIndex index = this->indexAt(QPoint(x,y)); 
	int col = index.column();//获得QTableWidget列表点击的行数 
	int row = index.row();//获得QTableWidget列表点击的行数 
	tmt_AsyncChannel *pCh = GetChannel();

	//不选择时不可右键
	if(!pCh[row].m_oHarm.m_bSelect)
	{
		return;
	}

	switch(col)
	{
	case ASYNCTABLE_SELECT:
		{
			m_MenuSelect->move(cursor().pos()); 
			m_MenuSelect->show(); 
		}
		break;
	case ASYNCTABLE_AMP:
		{
			m_MenuAmp->move(cursor().pos()); 
			m_MenuAmp->show(); 
		}
		break;
	case ASYNCTABLE_ANGLE:
		{
			int row = index.row();
			ASSERT(m_pChDatas);
			m_MenuPhase->move(cursor().pos()); 
			m_MenuPhase->show(); 
		}
		break;
	case ASYNCTABLE_FREQ:
		{
			m_MenuFre->move(cursor().pos()); 
			m_MenuFre->show(); 
		}
		break;
	default:
		break;
	}
}

void QAsyncChannelTable::slot_ActUZeroClicked()
{
	tmt_AsyncChannel *pChs = GetChannel();

	QTableWidgetItem *pItem = this->currentItem();
	if (pItem)
	{
		if(pChs[pItem->row()].m_oHarm.m_bSelect)
		{
		pItem->setText(QString::number(0,'f',3));
	}
	}
}

void QAsyncChannelTable::initData()
{

	if(!m_pAsyncModule)
	{
		return;
	}

	QTableWidgetItem *pItem = NULL;
	tmt_AsyncChannel* pChannelList = GetChannel();

	for(int nRow = 0; nRow < GetChannelNum(); nRow++)
	{
		tmt_AsyncChannel* pChannle = &pChannelList[nRow];

		// 设置复选框列（ASYNCTABLE_SELECT）
		QCheckBox* pCheckBox = m_CheckBoxList[nRow];
		pCheckBox->setChecked(pChannle->m_oHarm.m_bSelect);
		connect(pCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slot_CheckStateChange(int)));

		// 设置其他列
		for(int nCol = ASYNCTABLE_CHNAME; nCol < m_ColumnNum; nCol++)
		{
			QTableWidgetItem* pItem = item(nRow, nCol);

			if(pItem)
			{
				// 设置通道名称列（ASYNCTABLE_CHNAME）
				if(nCol == ASYNCTABLE_CHNAME)
				{
					pItem->setText(GetChName(m_moudleType, nRow));
				}

				// 设置幅值列（ASYNCTABLE_AMP）和相位列（ASYNCTABLE_ANGLE）
				if(nCol == ASYNCTABLE_AMP || nCol == ASYNCTABLE_ANGLE)
				{
					QString text;
					if(nCol == ASYNCTABLE_AMP)
					{
						text = QString::number(pChannle->m_oHarm.fAmp, 'f', 3);
					}
					else if(nCol == ASYNCTABLE_ANGLE)
					{
						text = QString::number(pChannle->m_oHarm.fAngle, 'f', 2);
					}
					pItem->setText(text);
					pItem->setFlags(pChannle->m_oHarm.m_bSelect ? pItem->flags() | Qt::ItemIsEditable
						: pItem->flags() & ~Qt::ItemIsEditable);
				}

				// 设置频率列（ASYNCTABLE_FREQ）
				if(nCol == ASYNCTABLE_FREQ && m_ColumnNum > 4)
				{
					QString text = QString::number(pChannle->m_oHarm.fFreq, 'f', 3);
					pItem->setText(text);
					pItem->setFlags(pChannle->m_oHarm.m_bSelect ? pItem->flags() | Qt::ItemIsEditable
						: pItem->flags() & ~Qt::ItemIsEditable);
				}					
				pChannle->m_oHarm.m_bSelect ? pItem->setForeground(Qt::black)
				: pItem->setForeground(Qt::gray);
			}
		}

		FloatAsyncTempChData *ptempData = new FloatAsyncTempChData;
		ptempData->fAngle = pChannle[nRow].m_oHarm.fAngle;
		ptempData->fHz = pChannle[nRow].m_oHarm.fFreq;
		m_oTempSaveDataMap.insert(nRow,ptempData);
	}
	setProperty(m_bDCTest);

}

tmt_AsyncChannel* QAsyncChannelTable::GetChannel()
{
	if(m_moudleType == Moudle_I)
	{
		return m_pAsyncModule->m_pCurrChannel;
	}
	else if(m_moudleType == Moudle_U)
	{
		return m_pAsyncModule->m_pVolChannel;
	}

	return NULL;
}

int QAsyncChannelTable::GetChannelNum()
{
	if(m_moudleType == Moudle_I)
	{
		return m_pAsyncModule->m_nCurrChCount;
	}
	else if(m_moudleType == Moudle_U)
	{
		return m_pAsyncModule->m_nVolChCount;
	}
	return 0;
}

void QAsyncChannelTable::UpdateValidTableDatas()
{
	for (int i=0;i<rowCount();i++)
	{
		for (int j=0;j<columnCount();j++)
		{
			slot_OnCellChanged(i,j);
		}
	}
}

void QAsyncChannelTable::setAmpMinCoe( int nMinCoe )
{
	m_nMinCoe = nMinCoe;
}

void QAsyncChannelTable::mousePressEvent( QMouseEvent *ev )
{
	if (ev->button() == Qt::RightButton)
	{
		QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,ev->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
		QApplication::postEvent(this,pEvent);
	}

	QTableWidget::mousePressEvent( ev );
}

void QAsyncChannelTable::mouseReleaseEvent( QMouseEvent *ev )
{
	QList<QLineEdit*> oList = findChildren<QLineEdit*>();
	for (int i = 0; i < oList.size(); i++)
	{
		oList[i]->setContextMenuPolicy(Qt::NoContextMenu);
		oList[i]->installEventFilter(this);
	}

	QTableWidget::mouseReleaseEvent( ev );
}

void QAsyncChannelTable::Act_setUIAmpValue( QTableWidgetItem *pItem,float fVal,bool bAll/*=TRUE*/ )
{
	if (pItem == NULL)
	{
		return;
	}

	QString strVal = QString::number(fVal,'f',3);

	if (!bAll)
	{
		pItem->setText(strVal);
		return;
	}

	int nChCount = GetChannelNum();
	tmt_AsyncChannel *pChs = GetChannel();

	if (nChCount==4)
	{
		for (int i=0;i<rowCount();i++)
		{
			if(pChs[i].m_oHarm.m_bSelect)
			{
			item(i,ASYNCTABLE_AMP)->setText(strVal);
		}
	}
	}
	else
	{
		int row = pItem->row();
		int imin = (int(row/3))*3;
		int imax = (int(row/3))*3 +2;
		if (imax>=rowCount())
		{
			imax = rowCount()-1;
		}
		for (int i=imin; i<=imax;i++)
		{
			if(pChs[i].m_oHarm.m_bSelect)
			{
			item(i,ASYNCTABLE_AMP)->setText(strVal);
		}
	}
	}
}

float QAsyncChannelTable::getItemValue( int row,int col )
{
	float fv;
	if (row<rowCount()&&col<columnCount())
	{
		if (col>0&&col<columnCount())
		{
			fv = item(row,col)->text().toFloat(); 
		}
	}
	return fv;
}

QString QAsyncChannelTable::initMaxHz( QString str )
{
	if (str.toFloat()- MAXHZ > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("输入值%f超出范围(%d).")*/g_sLangTxt_State_EnterTheValueoutofRange.GetString(),str.toFloat(),MAXHZ);
		return QString("%1").arg(MAXHZ);
	}
	else
	{
		return str;
	}
}

void QAsyncChannelTable::changeTableColor()
{
	tmt_AsyncChannel *pCh = GetChannel();
	if(!pCh)
	{
		return;
	}

	//	if (m_moudleType==Moudle_U)//电压  zhouhj 20210828  经比较电流与电压通道的代码完全相同,无需分成两份
	{
		switch (GetChannelNum())
		{
		case 3:
		case 4:
			{
				for (int i=0;i<rowCount();i++)
				{
					for (int j = 0;j<columnCount();j++)
					{
						QTableWidgetItem *item = this->item(i,j);
						if (item)
						{
							const QColor color = QColor(240,240,240);
							item->setBackgroundColor(color);
						}
					}
				}
			}
			break;
		case 6:
			{
				int Static=0;

				for (int i = 0;i < rowCount();i++)  
				{
					if (i/3 <= Static)  
					{  
						for (int j = 0;j < columnCount();j++)  
						{  
							QTableWidgetItem *item = this->item(i,j);  
							if (item)  
							{  
								item->setBackgroundColor(m_ColorList.at(Static));  
							}  
						}  
					}  

					if (i%3 == 2)
					{
						Static++;
					}
				} 
			}
			break;
		case 12:
			{
				int Static=0;

				for (int i = 0;i < rowCount();i++)  
				{
					if (i/3 <= Static)  
					{  
						for (int j = 0;j < columnCount();j++)  
						{  
							QTableWidgetItem *item = this->item(i,j);  
							if (item)  
							{  
								item->setBackgroundColor(m_ColorList.at(Static));  
							}  
						}  
					} 

					if (i%3 == 2)
					{
						Static++;
					}
				} 
			}
			break;
		case 18:
		default:
			{
				int Static=0;
				QColor oCurColor;

				for (int i = 0;i < rowCount();i++)  
				{
					if (i/3 <= Static)  
					{  
						for (int j = 0;j < columnCount();j++)  
						{  
							QTableWidgetItem *item = this->item(i,j);  

							if (item)  
							{  
								if (Static<m_ColorList.size())//zhouhj 20210828 必须保证当前取的数据,不能大于容器中的总数量
								{
									oCurColor = m_ColorList.at(Static);
								} 

								item->setBackgroundColor(oCurColor);  
							}  
						}  
					}  
					if (i%3 == 2)
					{
						Static++;
					}
				} 
			}
			break;
		}
	}
}

CString QAsyncChannelTable::GetChName( MOUDLEType type,int nChIndex )
{
	CString strType = _T("U");
	char pszName[3] = {'a','b','c'};

	if(type == Moudle_I)
	{
		strType = _T("I");
	}

	int nChNameIndex = nChIndex % 3;
	int nChGroupNumber = nChIndex / 3 + 1;

	QString chName = QString("%1%2%3").arg(strType).arg(QChar(pszName[nChNameIndex])).arg(nChGroupNumber);
	return chName;
}

void QAsyncChannelTable::slot_CheckStateChange( int nState )
{
	if(m_bIsCurrentlyTesting)//正在测试过程中不可编辑
	{
		return;
	}

	QCheckBox* pCheckBox = qobject_cast<QCheckBox*>(sender());
	int nChIndex = m_CheckBoxList.indexOf(pCheckBox);

	tmt_AsyncChannel *pCh = GetChannel();

	if(!pCh || nChIndex< 0 )
	{
		return;
	}

	bool b;

	switch(nState)
	{
	case Qt::Checked:
		b = true;
		break;
	case Qt::Unchecked:
		b = false;
		break;
	}

	pCh[nChIndex].m_oHarm.m_bSelect = b;


	for (int col = 0; col < columnCount(); ++col) 
	{
		QTableWidgetItem *item = this->item(nChIndex, col); // 获取该单元格的QTableWidgetItem
		if (item) 
		{
			if (nState == Qt::Checked) 
			{
// 				pCh[nChIndex].m_oHarm.m_bSelect = 1;
				if(col != ASYNCTABLE_CHNAME)
				{
					item->setFlags(item->flags() |Qt::ItemIsEditable);		
				}
				item->setForeground(Qt::black); // 设置前景色为黑色
			} 
			else if (nState == Qt::Unchecked) 
			{
// 				pCh[nChIndex].m_oHarm.m_bSelect = 0;
				if(col != ASYNCTABLE_CHNAME)
				{
					item->setFlags(item->flags()& ~ Qt::ItemIsEditable); 					
				}
				item->setForeground(Qt::gray); // 设置前景色为灰色
			}
		}
	}



}

void QAsyncChannelTable::slot_tableCellClicked( int row, int column )
{
 	// 判断是否点击了状态列
 	if (column == ASYNCTABLE_SELECT && !m_bIsCurrentlyTesting) 
 	{
 		// 直接改变对应行的复选框状态
 		m_CheckBoxList[row]->setChecked(!m_CheckBoxList[row]->isChecked());
 	}
}

MOUDLEType QAsyncChannelTable::GetModuleType()
{
	return m_moudleType;
}

tmt_AsyncChannel* QAsyncChannelTable::GetChFromName( CString strChName )
{
	int nCount = GetChannelNum();
	if(nCount <= 0)
	{
		return NULL;
	}

	tmt_AsyncChannel* chList = GetChannel();

	QList<QTableWidgetItem *> items = this->findItems(strChName, Qt::MatchContains);

	if (!items.isEmpty()) 
	{
		int row = items.at(0)->row();
		tmt_AsyncChannel* channel = &chList[row];
		return channel;
	}

	return NULL;
}

tmt_AsyncChannel* QAsyncChannelTable::GetChFromIndex( int nIndex )
{
	if(nIndex < 0)
	{
		return NULL;
	}

	tmt_AsyncChannel* chList = GetChannel();
	tmt_AsyncChannel* channel = &chList[nIndex];
	return channel;
}

int QAsyncChannelTable::getRowIndexByChName( const CString & strChName )
{
	int nCount = GetChannelNum();
	if(nCount <= 0)
	{
		return NULL;
	}

	tmt_AsyncChannel* chList = GetChannel();

	QList<QTableWidgetItem *> items = this->findItems(strChName, Qt::MatchContains);

	if (!items.isEmpty()) 
	{
		int row = items.at(0)->row();
		return row;
	}

	return -1;
}

void QAsyncChannelTable::setAmpEDValue( float fEDValue )
{
	m_fEDVal = fEDValue;
}

void QAsyncChannelTable::IsTestInProgress( bool b )
{
	m_bIsCurrentlyTesting = b;
	ChangeCheckEnable(!b);//开始测试过程中勾选框不可编辑
}

void QAsyncChannelTable::ChangeCheckEnable( bool b )
{
	for (int nRow = 0; nRow < GetChannelNum(); ++nRow) 
	{
		QTableWidgetItem *item = this->item(nRow, ASYNCTABLE_SELECT); // 获取该单元格的QTableWidgetItem
		if (item) 
		{
			if (b) 
			{
				m_CheckBoxList[nRow]->setEnabled(TRUE);
				item->setFlags(item->flags() |Qt::ItemIsEditable);		
				item->setForeground(Qt::black); // 设置前景色为黑色
			} 
			else
			{
				m_CheckBoxList[nRow]->setDisabled(true);
				item->setFlags(item->flags() & ~Qt::ItemIsEditable); // 移除可编辑标志
				item->setForeground(Qt::gray); // 设置前景色为灰色

			}
		}
	}

}