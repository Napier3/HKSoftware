#include "exswitchset.h"
#include "../../Module/SttTestSysGlobalPara.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

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

	CString strSelectAll;
	xlang_GetLangStrByFile(strSelectAll,"sSelAll");
//	ck_SelectAll->setText(tr(""));
	ck_SelectAll->setText(strSelectAll);
	QFont font1 = ck_SelectAll->font();
	font1.setPointSize(20);
    ck_SelectAll->setFont(font1);

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
		for (int i = 0; i < g_oLocalSysPara.m_nCHBinInExNum; i++)
		{
			m_bExVal[i] = m_pArrInEx[i].nSelect;
		}
	}
	else
	{
		for (int i = 0; i < g_oLocalSysPara.m_nCHBinOutExNum; i++)
		{
			m_bExVal[i] = m_pArrOutEx[i].nState;
		}
	}
	
	initTableData();
}	

void ExSwitchSet::updateData()
{
	if (m_eType == ExInput && m_pArrInEx == NULL
		|| m_eType == ExOutPut && m_pArrOutEx == NULL)
	{
		return;
	}

	if(m_eType == ExInput)
	{
		for (int i = 0; i < g_oLocalSysPara.m_nCHBinInExNum; i++)
		{
			m_bExVal[i] = m_pArrInEx[i].nSelect;
		}
	}
	else
	{
		for (int i = 0; i < g_oLocalSysPara.m_nCHBinOutExNum; i++)
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
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections
    pTop->setSectionsClickable(false);
    pTop->setSectionsMovable(false);
#else
    pTop->setClickable(false);
    pTop->setMovable(false);
#endif
	QHeaderView* pLeft = m_pTable->verticalHeader();
	pLeft->setDefaultSectionSize(25);
	pLeft->setVisible(false);

	m_pTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	QFont font1 = m_pTable->horizontalHeader()->font();
	font1.setBold(true);
	font1.setPointSize(20);
	m_pTable->horizontalHeader()->setFont(font1);
	m_pTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //~n
	m_pTable->setStyleSheet("selection-background-color: grey;selection-color: black");
//	m_pTable->horizontalHeader()->setStretchLastSection(true); 

	int nRows = 0,nColumns = 0; 
	QStringList headers;
	long nMaxRowIndex = 0,nMaxColIndex = 0,nTotalCounts = 0;
	GetMaxRowColIndex(nMaxRowIndex,nMaxColIndex,nTotalCounts);
	nRows = nMaxRowIndex+1;
	nColumns = nMaxColIndex+1;

	CString strName_In,strName_Out;
	xlang_GetLangStrByFile(strName_In,"Native_Bin");
	xlang_GetLangStrByFile(strName_Out,"Native_Bout");

	for (int i=0;i<nColumns;i++)
	{
		if (m_eType == ExInput)
		{
//			headers.append(QObject::tr(""));
			headers.append(strName_In);
		}
		else
		{
//			headers.append(QObject::tr(""));
			headers.append(strName_Out);
		}
	}

	m_pTable->setRowCount(nRows);
	m_pTable->setColumnCount(nColumns);
	m_pTable->setHorizontalHeaderLabels(headers);
 	QFontMetrics fontMetrics = QFontMetrics(font());

	CString strExBinSet;
	xlang_GetLangStrByFile(strExBinSet,"Native_ExBinSet");

	int nColumnWidth = fontMetrics.width(strExBinSet)+80;
	int nRowHeight = fontMetrics.height()+15;

	CString strName ="";
	CString strName_InEx,strName_OutEx;
	xlang_GetLangStrByFile(strName_InEx,"Native_BinEx");
	xlang_GetLangStrByFile(strName_OutEx,"Native_BoutEx");

	QTableWidgetItem* pitem;

	for (int i=0;i<nColumns;i++)
	{
		m_pTable->setColumnWidth(i,nColumnWidth);
	}

	for (int i=0;i<nRows;i++)
	{
		m_pTable->setRowHeight(i,nRowHeight);
	}

	for (int i = 0; i < nTotalCounts; i++)
	{
		if (m_eType == ExInput)
		{
			strName = strName_InEx;//tr("");
		}
		else
		{
			strName = strName_OutEx;//tr("");
		}

		QString str = strName + QString::number(i+1,10);

		pitem = new QTableWidgetItem(str);
		pitem->setCheckState(Qt::Unchecked);
		m_pTable->setItem(i%8,i/8,pitem);
	}

	QFont font2 = m_pTable->font();
	font2.setPointSize(20);
	m_pTable->setFont(font2);
}

void ExSwitchSet::initTableData()
{
	int nItems = 0;

	if(m_eType == ExInput)
	{
		nItems = g_oLocalSysPara.m_nCHBinInExNum;
	}
	else
	{
		nItems = g_oLocalSysPara.m_nCHBinOutExNum;
	}

	for (int i = 0; i < nItems; i++)
	{
		if (m_bExVal[i])
		{
			m_pTable->item(i%8,i/8)->setCheckState(Qt::Checked);
		}
		else
		{
			m_pTable->item(i%8,i/8)->setCheckState(Qt::Unchecked);
		}
	}
}

void ExSwitchSet::slot_ck_SelectAllChanged(int)
{
	if (ck_SelectAll->checkState() == Qt::Checked)
	{
		if (m_eType == ExInput)
		{
			for (int i = 0; i < g_oLocalSysPara.m_nCHBinInExNum; i++)
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
			for (int i = 0; i < g_oLocalSysPara.m_nCHBinOutExNum; i++)
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
			for (int i = 0; i < g_oLocalSysPara.m_nCHBinInExNum; i++)
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
			for (int i = 0; i < g_oLocalSysPara.m_nCHBinOutExNum; i++)
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
		nTotalCounts = g_oLocalSysPara.m_nCHBinInExNum;
	}
	else
	{
		nTotalCounts = g_oLocalSysPara.m_nCHBinOutExNum;
	}

	nMaxRowIndex = (nTotalCounts-1)%8;
	nMaxColIndex = (nTotalCounts-1)/8;

	if (nMaxColIndex>0)//1,8 Index7
	{
		nMaxRowIndex = 7;
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

	int nSwitchIndex = column*8+row;

	if (m_eType == ExInput && nSwitchIndex+1>g_oLocalSysPara.m_nCHBinInExNum
		|| m_eType == ExOutPut && nSwitchIndex+1>g_oLocalSysPara.m_nCHBinOutExNum)
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
