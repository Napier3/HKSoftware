#include "SttMacroParaEditViewParaRecallTable.h"
#include <QHeaderView>
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/CommonMethod/commonMethod.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewParaRecallTable::QSttMacroParaEditViewParaRecallTable( QWidget *parent /*= 0*/ ): QScrollTableWidget(parent)

{
	m_pCurrKeyboardItem = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
	InitUI();
}

QSttMacroParaEditViewParaRecallTable::~QSttMacroParaEditViewParaRecallTable()
{

}

void QSttMacroParaEditViewParaRecallTable::InitUI()
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

void QSttMacroParaEditViewParaRecallTable::UpdateText( const QString &strText )
{

}


void QSttMacroParaEditViewParaRecallTable::InitTable()
{
	QStringList  HStrList;
	HStrList<< _T("测试项") << _T("要求说明") << _T("备注");

	setColumnCount(3);
	setHorizontalHeaderLabels(HStrList);

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	this->setColumnWidth(0,300);
	this->setColumnWidth(1,300);
	this->setColumnWidth(2,300);
}


void QSttMacroParaEditViewParaRecallTable::InitData( CDataGroup *pData )
{
	QTableWidgetItem *pItem = NULL; 
	setRowCount(1);

	pItem = new QTableWidgetItem;
	pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	pItem->setText(_T("固有参数调阅"));
	setItem(0, 0, pItem);

	pItem = new QTableWidgetItem;
	pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	pItem->setText(_T("读取终端固有参数"));
	setItem(0, 1, pItem);

	pItem = new QTableWidgetItem;
	pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	//GetTableWidgetItemValue(pItem);
	//setItem(0, 2, pItem);
}

void QSttMacroParaEditViewParaRecallTable::GetTableWidgetItemValue(QTableWidgetItem * pItem )
{
	CString strValue;
	stt_GetDataValueByID(m_pParaRecallDataGroup, _T("IncorrectTimeFormat"), strValue);
	pItem->setText(strValue);
}