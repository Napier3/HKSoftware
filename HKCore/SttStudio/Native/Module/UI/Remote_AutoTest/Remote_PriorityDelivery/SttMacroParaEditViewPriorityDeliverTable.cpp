#include "SttMacroParaEditViewPriorityDeliverTable.h"
#include <QHeaderView>
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/CommonMethod/commonMethod.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewPriorityDeliverTable::QSttMacroParaEditViewPriorityDeliverTable( QWidget *parent /*= 0*/ ): QScrollTableWidget(parent)

{
	m_pCurrKeyboardItem = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
	InitUI();
}

QSttMacroParaEditViewPriorityDeliverTable::~QSttMacroParaEditViewPriorityDeliverTable()
{

}

void QSttMacroParaEditViewPriorityDeliverTable::InitUI()
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

void QSttMacroParaEditViewPriorityDeliverTable::UpdateText( const QString &strText )
{

}


void QSttMacroParaEditViewPriorityDeliverTable::InitTable()
{
	QStringList  HStrList;
	HStrList<< _T("测试项") <<  _T("Ia(A)")<<  _T("开出设置")<< _T("触发方式")  << _T("输出时间(s)");

	setColumnCount(5);
	setHorizontalHeaderLabels(HStrList);

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	this->setColumnWidth(0,160);
	this->setColumnWidth(1,160);
	this->setColumnWidth(2,160);
	this->setColumnWidth(3,160);
	this->setColumnWidth(3,160);
}

void QSttMacroParaEditViewPriorityDeliverTable::InitData( CDataGroup *pData,CDataGroup *pParas)
{
// 	CExBaseObject *pObj = NULL;
// 	POS pos = m_pDeliverDataGroup->GetHeadPosition();
// 	while(pos)
// 	{
// 		pObj = (CExBaseObject *)m_pDeliverDataGroup->GetNext(pos);
// 		if (pObj->GetClassID() == DTMCLASSID_CDATAGROUP && pObj)
// 		{
// 			m_pDeliverDataGroup->Remove(pObj);
// 		}
// 	}

	m_pDeliverDataGroup = pParas;
	clearContents();
	setRowCount(0);
	QTableWidgetItem *pItem = NULL; 
	long nCurrRowIndex = rowCount();

	CString strID,strText;
	
	for (int i = 0; i<g_nBinCount; i++)
	{
		strID.Format(_T("Bout%d"),i+1);
		CDvmData *pCurrData = (CDvmData *)pData->FindByID(strID);		
		if (pCurrData)
		{
			if (pCurrData->m_strValue == _T("Din_1"))
			{
				if (nCurrRowIndex >= rowCount())
				{
					setRowCount(nCurrRowIndex + 1);
				}

				pItem = new QTableWidgetItem;
				pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
				pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
				strText = _T("遥信优先上送");
				pItem->setText(strText);
				setItem(nCurrRowIndex,0,pItem);

				pItem = new QTableWidgetItem;
//				pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
				pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 				strText.Format(_T("%0.1f"), 0.5);
// 				pItem->setText(strText + _T("A"));
				GetTableWidgetItemValue(pParas,nCurrRowIndex,1,pItem,_T("I1"));

				setItem(nCurrRowIndex,1,pItem);

				pItem = new QTableWidgetItem;
				pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
				pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
				strText = pCurrData->m_strID.Right(1);
				strText = _T("开出") + strText;
				pItem->setText(strText);
				setItem(nCurrRowIndex,2,pItem);

				pItem = new QTableWidgetItem;
				pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
				pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
				strText = _T("时间触发");
				pItem->setText(strText);
				setItem(nCurrRowIndex,3,pItem);

				pItem = new QTableWidgetItem;
//				pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
				pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 				strText.Format(_T("%d"),5);
// 				pItem->setText(strText + _T("s"));
				GetTableWidgetItemValue(pParas,nCurrRowIndex,0,pItem,_T("PulseWidth"));
				setItem(nCurrRowIndex,4,pItem);
				nCurrRowIndex ++;
				UpdataData(pCurrData,nCurrRowIndex);
			}
		}
	}


	int nCount = m_pDeliverDataGroup->GetChildCount(DTMCLASSID_CDATAGROUP);
	for (int nIndex = nCurrRowIndex; nIndex < nCount;nIndex++)
	{
		strID.Format(_T("TestItem%d"), nIndex+1);
		CDataGroup *pDataGroup = (CDataGroup *)m_pDeliverDataGroup->FindByID(strID);
		if(pDataGroup)
		{
			pDataGroup->SetDataValue(_T("Select"),long(0));
		}
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void QSttMacroParaEditViewPriorityDeliverTable::slot_OnCellChanged( int row,int col )
{
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


	CString strID;
	strID.Format(_T("TestItem%d"),row+1);
	CDataGroup *pCurrDataGroup = (CDataGroup *)m_pDeliverDataGroup->FindByID(strID);
	if (pCurrDataGroup == NULL)
	{
		return;
	}

	if (col == 1)
	{
		pCurrDataGroup->SetDataValue(_T("I1"),pItem->text());
	}
	else if (col == 4)
	{
		pCurrDataGroup->SetDataValue(_T("PulseWidth"),pItem->text());
	}
	pItem->setText(pItem->text());

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void QSttMacroParaEditViewPriorityDeliverTable::UpdataData( CDvmData *pDvmData,long nIndex )
{
	CString strID,strName;
	strName.Format(_T("遥信%d"),nIndex);
	strID.Format(_T("TestItem%d"),nIndex);
	CDataGroup *pDataGroup = (CDataGroup *)m_pDeliverDataGroup->FindByID(strID);

	if (pDataGroup == NULL)
	{
		CDataGroup* pCurDataGroup = m_pDeliverDataGroup->AddNewGroup(strName,strID,"");
		pCurDataGroup->AddNewData( _T("选择"),_T("Select"),_T("long"),_T("1"));
		pCurDataGroup->AddNewData( _T("模拟量设置"),_T("I1"),_T("float"),_T("0.5"));
		pCurDataGroup->AddNewData( _T("开出设置"),_T("BoutSet"),_T("long"),pDvmData->m_strName.Right(1));
		pCurDataGroup->AddNewData( _T("测试对象"),_T("TestObject"),_T("string"),pDvmData->m_strValue);
		pCurDataGroup->AddNewData( _T("输出时间"),_T("PulseWidth"),_T("float"),_T("5"));
	}
	else
	{
		pDataGroup->SetDataValue(_T("Select"),long(1));
		pDataGroup->SetDataValue(_T("BoutSet"),pDvmData->m_strName.Right(1));
		pDataGroup->SetDataValue(_T("TestObject"),pDvmData->m_strValue);
	}
}

void QSttMacroParaEditViewPriorityDeliverTable::GetTableWidgetItemValue(CDataGroup *pParas, long nIndex,long nDecimal,QTableWidgetItem * pItem,const CString strID )
{
	CString strTestID;
	strTestID.Format(_T("TestItem%d"),nIndex+1);
	CDataGroup *pCurrDataGroup = (CDataGroup *)pParas->FindByID(strTestID);
	float fValue;
	stt_GetDataValueByID(pCurrDataGroup, strID, fValue);
	pItem->setText(QString::number(fValue,'f',nDecimal));
}

void QSttMacroParaEditViewPriorityDeliverTable::UpdateTable( CDataGroup *pParas )
{
	QTableWidgetItem *pItem = NULL;
	for (int nRow = 0; nRow < this->rowCount(); nRow++)
	{
		pItem = item(nRow, 1);
		if (pItem)
		{
			GetTableWidgetItemValue(pParas,nRow,1,pItem,_T("I1"));
		}
		pItem = item(nRow, 4);
		if (pItem)
		{
			GetTableWidgetItemValue(pParas,nRow,0,pItem,_T("PulseWidth"));
		}
	}
}
