#include "SttMacroParaEditViewZeroTable.h"
#include <QHeaderView>
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/CommonMethod/commonMethod.h"

#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewZeroTable::QSttMacroParaEditViewZeroTable( int rows, int columns,QWidget *parent ): QTableWidget(rows, columns,parent)
{
	m_pCheckBoxDelegateBase = NULL;
	m_pCurrKeyboardItem = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);

	InitUI();
}

QSttMacroParaEditViewZeroTable::~QSttMacroParaEditViewZeroTable()
{

}


void QSttMacroParaEditViewZeroTable::InitUI()
{
	QHeaderView* pLeft = verticalHeader();
	pLeft->setDefaultSectionSize(36);
	pLeft->setVisible(false);
	QHeaderView* pHeadTop =horizontalHeader();
	pHeadTop->setClickable(false);
	pHeadTop->setMovable(false);
	QFont font1 = this->horizontalHeader()->font();
	font1.setBold(true);
	this->horizontalHeader()->setFont(font1);
	horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	setEditTriggers(QAbstractItemView::DoubleClicked);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

	QFontMetrics fontHeaderViewMe = QFontMetrics(font1);
	m_nHeaderViewHeight = fontHeaderViewMe.height() + 20;
	QFont font2 = this->font();
	font2.setPointSize(20);
	this->setFont(font2);
	QFontMetrics fontRowMe = QFontMetrics(font2);
	m_nRowHeight = fontRowMe.height() + 15;

	InitTable();
}

void QSttMacroParaEditViewZeroTable::InitTable()
{
	setHorizontalHeaderLabels(QStringList()<< _T("选择") <<  _T("区段")<< _T("整定值(A)")  << _T("整定时间(s)")  << _T("0.95倍(A)") << _T("1.05倍(A)"));
	QFontMetrics fontMetrics = QFontMetrics(this->font());
	this->setColumnWidth(0,140);
	this->setColumnWidth(1,140);
	this->setColumnWidth(2,140);
	this->setColumnWidth(3,150);
	this->setColumnWidth(4,150);
	this->setColumnWidth(5,150);

	m_pCheckBoxDelegateBase = new QExBaseListCheckBoxDelegate(this);
	this->setItemDelegateForColumn(0,m_pCheckBoxDelegateBase);
	
	//setColumnHidden(4, true);//0.95倍暂时用不到，先隐藏
}

void QSttMacroParaEditViewZeroTable::slot_OnCellChanged( int row,int col )
{
	QStringList zoneCheckItems ,iSetingItems ,tSetingItems; 
	zoneCheckItems << _T("Zone1_Check") <<  _T("Zone2_Check") ;
	iSetingItems << _T("ISetingZone1") <<  _T("ISetingZone2");
	tSetingItems << _T("TSetingZone1")<< _T("TSetingZone2");

	CString strID;
	if (row  <  0)
	{
		return;
	}
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));

	QTableWidgetItem  *pItem  = this->item(row,col);

	if (pItem == NULL)
	{
		return;
	} 
	float fValue = pItem->text().toFloat();
	if (col == 0)
	{
		strID = zoneCheckItems.at(row);

		if (pItem->checkState() !=  Qt::Unchecked)
		{
			m_pData->SetDataValue(strID,(long)1);
		}
		else
		{
			m_pData->SetDataValue(strID,(long)0);
		}
	}
	else if (col == 2)
	{
		strID = iSetingItems.at(row);
		fValue = setLimit(0,100,fValue);
		pItem->setText(QString::number(fValue));
		m_pData->SetDataValue(strID,fValue);

		UpdateTable();
	}
	else if (col == 3)
	{
		strID = tSetingItems.at(row);
		fValue = setLimit(0,100,fValue);
		pItem->setText(QString::number(fValue));
		m_pData->SetDataValue(strID,fValue);
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
}

void QSttMacroParaEditViewZeroTable::InitData( CDataGroup *pData )
{
	m_pData = pData;
	CString strText; 
	QTableWidgetItem *pItem = NULL; 

	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	//GetTableWidgetItemValue(pItem,_T("Zone1_Check"),true);
	setItem(0, 0, pItem); 
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	//GetTableWidgetItemValue(pItem,_T("Zone2_Check"),true);
	setItem(1, 0, pItem); 
	

	strText = _T("I段");
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setText(strText);
	setItem(0, 1, pItem);
	strText = _T("II段");
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setText(strText);
	setItem(1, 1, pItem);


	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	//GetTableWidgetItemValue(pItem,_T("ISetingZone1"),false);
	setItem(0, 2, pItem);
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	//GetTableWidgetItemValue(pItem,_T("ISetingZone2"),false);
	setItem(1, 2, pItem);


	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	//GetTableWidgetItemValue(pItem,_T("TSetingZone1"),false);
	setItem(0, 3, pItem);
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	//GetTableWidgetItemValue(pItem,_T("TSetingZone2"),false);
	setItem(1, 3, pItem);


	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	setItem(0, 4, pItem);
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	setItem(1, 4, pItem);


	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	setItem(0, 5, pItem);
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	setItem(1, 5, pItem);


	UpdateTable();

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}


void QSttMacroParaEditViewZeroTable::GetTableWidgetItemValue( QTableWidgetItem * pItem,const CString strID ,bool bCheck)
{
	CDvmData* pCurData = (CDvmData*)m_pData->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	if (bCheck)
	{
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
	else
	{
		float fValue = pCurData->m_strValue.toFloat();
		pItem->setText(QString::number(fValue));
	}
}

void QSttMacroParaEditViewZeroTable::UpdateTable()
{
	QTableWidgetItem *pItem = NULL;
	CString strItemId;
	for (int nRow = 0; nRow < this->rowCount(); nRow++)
	{
		for (int nCol = 0; nCol < this->columnCount(); nCol++)
		{
			pItem = item(nRow, nCol);
			if (pItem == NULL)
			{
				continue;
			}

			if (nCol == 0)
			{
				strItemId.Format(_T("Zone%d_Check"), nRow + 1);
				GetTableWidgetItemValue(pItem, strItemId, true);
			}
			else if (nCol == 2)
			{
				strItemId.Format(_T("ISetingZone%d"), nRow + 1);
				GetTableWidgetItemValue(pItem, strItemId, false);
			}
			else if (nCol == 3)
			{
				strItemId.Format(_T("TSetingZone%d"), nRow + 1);
				GetTableWidgetItemValue(pItem, strItemId, false);
			}
		}
		pItem = item(nRow,2);
		if (pItem == NULL)
		{
			return;
		}

		float fValue = pItem->text().toFloat();
		item(nRow,4)->setText(QString::number(fValue * 0.95,'f',2));
		item(nRow,5)->setText(QString::number(fValue * 1.05,'f',2));
	}
}
