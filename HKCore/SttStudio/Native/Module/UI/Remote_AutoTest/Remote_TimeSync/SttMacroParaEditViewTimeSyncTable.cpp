#include "SttMacroParaEditViewTimeSyncTable.h"
#include <QHeaderView>
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/CommonMethod/commonMethod.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewTimeSyncTable::QSttMacroParaEditViewTimeSyncTable( QWidget *parent /*= 0*/ ): QScrollTableWidget(parent)

{
	m_pCurrKeyboardItem = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
	InitUI();
}

QSttMacroParaEditViewTimeSyncTable::~QSttMacroParaEditViewTimeSyncTable()
{

}

void QSttMacroParaEditViewTimeSyncTable::InitUI()
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
	horizontalHeader()->setStretchLastSection(true); //���ó�������
	setEditTriggers(QAbstractItemView::DoubleClicked);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //���ñ�ͷ����ɫ

	QFontMetrics fontHeaderViewMe = QFontMetrics(font1);
	m_nHeaderViewHeight = fontHeaderViewMe.height() + 20;
	QFont font2 = this->font();
	font2.setPointSize(20);
	this->setFont(font2);
	QFontMetrics fontRowMe = QFontMetrics(font2);
	m_nRowHeight = fontRowMe.height() + 15;

	InitTable();
}

void QSttMacroParaEditViewTimeSyncTable::UpdateText( const QString &strText )
{

}


void QSttMacroParaEditViewTimeSyncTable::InitTable()
{
	QStringList  HStrList;
	HStrList<< _T("������") << _T("��ע");

	setColumnCount(2);
	setHorizontalHeaderLabels(HStrList);

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	this->setColumnWidth(0,400);
	this->setColumnWidth(1,400);
}


void QSttMacroParaEditViewTimeSyncTable::InitData( CDataGroup *pData )
{
	QTableWidgetItem *pItem = NULL; 
	setRowCount(2);

	pItem = new QTableWidgetItem;
	pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	pItem->setText(_T("ʱ��׼ȷ�Ȳ���"));
	setItem(0, 0, pItem);

	pItem = new QTableWidgetItem;
	pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	pItem->setText(_T("д��ϵͳʱ��"));
	setItem(0, 1, pItem);

	pItem = new QTableWidgetItem;
	pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	pItem->setText(_T("ʱ���ʽ��ȷ�Բ���"));
	setItem(1, 0, pItem);

	pItem = new QTableWidgetItem;
	pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	//pItem->setText(_T("2024��12��32��"));
	GetTableWidgetItemValue(pItem);
	setItem(1, 1, pItem);
}

void QSttMacroParaEditViewTimeSyncTable::GetTableWidgetItemValue(QTableWidgetItem * pItem )
{
	//CDataGroup *pCurrDataGroup = (CDataGroup *)m_pDualPositionDataGroup->FindByID(oList[nIndex]);
	CString strValue;
	stt_GetDataValueByID(m_pTimeSyncDataGroup, _T("IncorrectTimeFormat"), strValue);
	pItem->setText(strValue);
}