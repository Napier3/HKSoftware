#include "exswitchset.h"
#include "../Module/Define.h"
#include "../../../../Module/SttTest/Common/tmt_test_paras_head.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

ExSwitchSet::ExSwitchSet(ExSwitchType etype,QWidget *parent)
	: QWidget(parent)
{
	initUI();
	m_eType = etype;

	for (int i = 0; i < MAX_ExBINARY_COUNT; i++)
	{
		m_bExVal[i] = false;
	}

	m_pArrInEx = NULL;
	m_pArrOutEx = NULL;
	
	initTable();

	connect(m_pTable, SIGNAL(cellClicked ( int , int  )), this, SLOT(slot_Table_cellClicked ( int , int  )));
	connect(ck_SelectAll, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_SelectAllChanged(int)));
}

ExSwitchSet::~ExSwitchSet()
{

}

void ExSwitchSet::initUI()
{
	QHBoxLayout *horizontalLayout;
	QSpacerItem *horizontalSpacer;
	
	QWidget *widget;
	QGridLayout *gridLayout,*gridLayout_2;

	setObjectName(QString::fromUtf8("ExSwitchSet"));
	resize(400, 300);

	gridLayout_2 = new QGridLayout(this);
	gridLayout_2->setSpacing(6);
	gridLayout_2->setContentsMargins(0, 0, 0, 0);
	gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
	gridLayout_2->setVerticalSpacing(0);
	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing(6);
	horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
	horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	horizontalLayout->addItem(horizontalSpacer);

	ck_SelectAll = new QCheckBox(this);
	ck_SelectAll->setObjectName(QString::fromUtf8("ck_SelectAll"));
	ck_SelectAll->setText(tr("全选"));
	horizontalLayout->addWidget(ck_SelectAll);

	gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

	widget = new QWidget(this);
	widget->setObjectName(QString::fromUtf8("widget"));
	gridLayout = new QGridLayout(widget);
	gridLayout->setSpacing(6);
	gridLayout->setContentsMargins(0, 0, 0, 0);
	gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
	gridLayout->setHorizontalSpacing(0);
	frame = new QFrame(widget);
	frame->setObjectName(QString::fromUtf8("frame"));
	frame->setFrameShape(QFrame::StyledPanel);
	frame->setFrameShadow(QFrame::Raised);

	gridLayout->addWidget(frame, 0, 0, 1, 1);

	gridLayout_2->addWidget(widget, 1, 0, 1, 1);
	gridLayout_2->setRowStretch(0, 1);
	gridLayout_2->setRowStretch(1, 15);
}

void ExSwitchSet::setData(tmt_BinaryIn *pArrInEx,tmt_BinaryOut *pArrOutEx)
{
	if ((m_eType == ExInput) && (pArrInEx == NULL) )
	{
		return;
	}

	if((m_eType == ExOutPut) && (pArrOutEx == NULL))
	{
		return;
	}

	m_pArrInEx = pArrInEx;
	m_pArrOutEx = pArrOutEx;

	if(m_eType == ExInput)
	{
		for (int i = 0; i < g_nBinExCount; i++)
		{
			m_bExVal[i] = m_pArrInEx[i].nSelect;
		}
	}
	else
	{
		for (int i = 0; i < g_nBoutExCount; i++)
		{
			m_bExVal[i] = m_pArrOutEx[i].nState;
		}
	}
	
	initTableData();
}	

void ExSwitchSet::initTable()
{
	QGridLayout *pLayout = new QGridLayout(frame);

	m_pTable = new QTableWidget(frame);
	pLayout->addWidget(m_pTable);
	
	QHeaderView* pTop = m_pTable->horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false);
	QHeaderView* pLeft = m_pTable->verticalHeader();
	pLeft->setDefaultSectionSize(25);
	pLeft->setVisible(false);

	m_pTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	QFont font1 = m_pTable->horizontalHeader()->font();
	font1.setBold(true);
	m_pTable->horizontalHeader()->setFont(font1);
	m_pTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	m_pTable->setStyleSheet("selection-background-color: grey;selection-color: black");
	m_pTable->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度

	int nRows = 0,nColumns = 0; 
	QStringList headers;
	long nMaxRowIndex = 0,nMaxColIndex = 0,nTotalCounts = 0;
	GetMaxRowColIndex(nMaxRowIndex,nMaxColIndex,nTotalCounts);
	nRows = nMaxRowIndex+1;
	nColumns = nMaxColIndex+1;

	for (int i=0;i<nColumns;i++)
	{
		if (m_eType == ExInput)
		{
			headers.append(/*QObject::tr("开入量")*/g_sLangTxt_Native_Bin);
		}
		else
		{
			headers.append(/*QObject::tr("开出量")*/g_sLangTxt_Native_Bout);
		}
	}

	m_pTable->setRowCount(nRows);
	m_pTable->setColumnCount(nColumns);
	m_pTable->setHorizontalHeaderLabels(headers);
 	QFontMetrics fontMetrics = QFontMetrics(font());
 	int nColumnWidth = fontMetrics.width(/*tr(" 扩展开入量_20 ")*/g_sLangTxt_Native_BinEx20) +40;
	QString strName ="";
	QTableWidgetItem* pitem;

	for (int i=0;i<nColumns;i++)
	{
		m_pTable->setColumnWidth(i,nColumnWidth);
	}

	for (int i = 0; i < nTotalCounts; i++)
	{
		if (m_eType == ExInput)
		{
			strName = /*tr("扩展开入")*/g_sLangTxt_Native_BinEx;
		}
		else
		{
			strName = /*tr("扩展开出")*/g_sLangTxt_Native_BoutEx;
		}

		QString str = strName + QString::number(i+1,10);

		pitem = new QTableWidgetItem(str);
		pitem->setCheckState(Qt::Unchecked);
		m_pTable->setItem(i%24,i/24,pitem);
	}
}

void ExSwitchSet::initTableData()
{
	int nItems = 0;

	if(m_eType == ExInput)
	{
		nItems = g_nBinExCount;
	}
	else
	{
		nItems = g_nBoutExCount;
	}

	for (int i = 0; i < nItems; i++)
	{
		if (m_bExVal[i])
		{
			m_pTable->item(i%24,i/24)->setCheckState(Qt::Checked);
		}
		else
		{
			m_pTable->item(i%24,i/24)->setCheckState(Qt::Unchecked);
		}
	}
}

void ExSwitchSet::slot_ck_SelectAllChanged(int)
{
	if (ck_SelectAll->checkState() == Qt::Checked)
	{
		if (m_eType == ExInput)
		{
			for (int i = 0; i < g_nBinExCount; i++)
			{
				m_bExVal[i] = true;
				if (m_pArrInEx)
				{
					m_pArrInEx[i].nSelect = true;
				}
			}
		}
		else
		{
			for (int i = 0; i < g_nBoutExCount; i++)
			{
				m_bExVal[i] = true;
				if (m_pArrOutEx)
				{
					m_pArrOutEx[i].nState = 1;
				}
			}
		}
	}
	else
	{
		if (m_eType == ExInput)
		{
			for (int i = 0; i < g_nBinExCount; i++)
			{
				m_bExVal[i] = false;
				if (m_pArrInEx)
				{
					m_pArrInEx[i].nSelect = false;
				}
			}
		}
		else
		{
			for (int i = 0; i < g_nBoutExCount; i++)
			{
				m_bExVal[i] = false;
				if (m_pArrOutEx)
				{
					m_pArrOutEx[i].nState = 0;
				}
			}
		}
	}

	initTableData();

	emit sig_ExSwitchChanged();
}

void ExSwitchSet::GetMaxRowColIndex(long &nMaxRowIndex,long &nMaxColIndex,long &nTotalCounts)
{
	if(m_eType == ExInput)
	{
		nTotalCounts = g_nBinExCount;
	}
	else
	{
		nTotalCounts = g_nBoutExCount;
	}

	nMaxRowIndex = (nTotalCounts-1)%24;
	nMaxColIndex = (nTotalCounts-1)/24;

	if (nMaxColIndex>0)//如果当前列数大于1,则行数最大为24 对应的Index最大为23
	{
		nMaxRowIndex = 23;
	}
}

void ExSwitchSet::slot_Table_cellClicked ( int row, int column)
{
	long nMaxRowIndex = 0,nMaxColIndex = 0,nTotalCounts = 0;
	GetMaxRowColIndex(nMaxRowIndex,nMaxColIndex,nTotalCounts);

	if (row>nMaxRowIndex)
	{
		return;
	}

	if (column>nMaxColIndex)
	{
		return;
	}

	int nSwitchIndex = column*24+row;

	if (m_eType == ExInput && nSwitchIndex+1>g_nBinExCount
		|| m_eType == ExOutPut && nSwitchIndex+1>g_nBoutExCount)
	{
		return;
	}

	BOOL bValue = FALSE;

	if (m_pTable->item(row,column)->checkState() == Qt::Checked)
	{
		bValue = TRUE;
	}

	m_bExVal[nSwitchIndex] = bValue;

	if((m_eType == ExInput)&&(m_pArrInEx != NULL))
	{
		m_pArrInEx[nSwitchIndex].nSelect = bValue;
		emit sig_ExSwitchChanged();
	}
	else if((m_eType == ExOutPut)&&(m_pArrOutEx != NULL))
	{
		m_pArrOutEx[nSwitchIndex].nState = bValue;
		emit sig_ExSwitchChanged();
	}
}