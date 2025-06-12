#include "SttMacroParaEditViewRemote_AccuracyTable.h"
#include <QHeaderView>
#include "../../../XLangResource_Native.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/CommonMethod/commonMethod.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewRemote_AccuracyTable::QSttMacroParaEditViewRemote_AccuracyTable( QWidget *parent /*= 0*/ ): QScrollTableWidget(parent)

{
	m_pCurrKeyboardItem = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
	InitUI();
}

QSttMacroParaEditViewRemote_AccuracyTable::~QSttMacroParaEditViewRemote_AccuracyTable()
{

}

void QSttMacroParaEditViewRemote_AccuracyTable::InitUI()
{
	QHeaderView* pLeft = verticalHeader();
	pLeft->setDefaultSectionSize(36);
	pLeft->setVisible(false);
	QHeaderView* pHeadTop =horizontalHeader();
    pHeadTop->setSectionsClickable(false);
    pHeadTop->setSectionsMovable(false);
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

void QSttMacroParaEditViewRemote_AccuracyTable::UpdateText( const QString &strText )
{

}


void QSttMacroParaEditViewRemote_AccuracyTable::InitTable()
{
	QStringList  HStrList;
	HStrList<< _T("测试项") <<  _T("开出设置")<< _T("触发方式")  << _T("输出时间(ms)");

	setColumnCount(4);
	setHorizontalHeaderLabels(HStrList);

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	this->setColumnWidth(0,200);
	this->setColumnWidth(1,200);
	this->setColumnWidth(2,200);
	this->setColumnWidth(3,200);

}


void QSttMacroParaEditViewRemote_AccuracyTable::InitData( CDataGroup *pData,CDataGroup *pAccuracyDataGroup)
{
// 	CExBaseObject *pObj = NULL;
// 	POS pos = m_pAccuracyDataGroup->GetHeadPosition();
// 	while(pos)
// 	{
// 		pObj = (CExBaseObject *)m_pAccuracyDataGroup->GetNext(pos);
// 		if (pObj->GetClassID() == DTMCLASSID_CDATAGROUP && pObj)
// 		{
// 			m_pAccuracyDataGroup->Remove(pObj);
// 		}
// 	}
	m_pAccuracyDataGroup = pAccuracyDataGroup;

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
			if (!pCurrData->m_strValue.IsEmpty())
			{
				if (nCurrRowIndex >= rowCount())
				{
					setRowCount(nCurrRowIndex + 1);
				}
				pItem = new QTableWidgetItem;
				pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
				pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
				if ( pCurrData->m_strValue == _T("Din_1"))
				{
					strText = CString(_T("合位"));
				}
				else if (pCurrData->m_strValue == _T("Din_2"))
				{
					strText = CString(_T("分位"));
				}
				else if (pCurrData->m_strValue == _T("Din_5"))
				{
					strText = CString(_T("未储能"));
				}
				//strText.Format(_T("遥信%d"),nCurrRowIndex+1);
				pItem->setText(strText);
				setItem(nCurrRowIndex,0,pItem);

				pItem = new QTableWidgetItem;
				pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
				pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
				strText = pCurrData->m_strName;
				pItem->setText(strText);
				setItem(nCurrRowIndex,1,pItem);

				pItem = new QTableWidgetItem;
				pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
				pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
				strText = _T("时间触发");
				pItem->setText(strText);
				setItem(nCurrRowIndex,2,pItem);

				pItem = new QTableWidgetItem;
				//pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
				pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 				strText.Format(_T("%d"),5);
// 				pItem->setText(strText + _T("s"));
				GetTableWidgetItemValue(pAccuracyDataGroup,nCurrRowIndex,pItem);
				setItem(nCurrRowIndex,3,pItem);

				nCurrRowIndex ++;
				UpdataData(pCurrData,nCurrRowIndex);
			}
		}
	}

	int nCount = m_pAccuracyDataGroup->GetChildCount(DTMCLASSID_CDATAGROUP);
	for (int nIndex = nCurrRowIndex; nIndex < nCount;nIndex++)
	{
		strID.Format(_T("TestItem%d"), nIndex+1);
		CDataGroup *pDataGroup = (CDataGroup *)m_pAccuracyDataGroup->FindByID(strID);
		if(pDataGroup)
		{
			pDataGroup->SetDataValue(_T("Select"),long(0));
		}
	}


	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void QSttMacroParaEditViewRemote_AccuracyTable::UpdataData(CDvmData *pDvmData,long nIndex)
{
	CString strID,strName;
	strID.Format(_T("TestItem%d"),nIndex);
	strName.Format(_T("遥信%d"),nIndex);
	CDataGroup *pDataGroup = (CDataGroup *)m_pAccuracyDataGroup->FindByID(strID);
	if (pDataGroup == NULL)
	{
		CDataGroup* pCurDataGroup = m_pAccuracyDataGroup->AddNewGroup(strName,strID,"");
		pCurDataGroup->AddNewData( _T("选择"),_T("Select"),_T("long"),_T("1"));
		pCurDataGroup->AddNewData( _T("开出设置"),_T("BoutSet"),_T("long"),pDvmData->m_strName.Right(1));
		pCurDataGroup->AddNewData( _T("测试对象"),_T("TestObject"),_T("string"),pDvmData->m_strValue);
		pCurDataGroup->AddNewData( _T("输出时间"),_T("PulseWidth"),_T("float"),_T("5000"));
	}
	else
	{
		pDataGroup->SetDataValue(_T("Select"),long(1));
		pDataGroup->SetDataValue(_T("BoutSet"),pDvmData->m_strName.Right(1));
		pDataGroup->SetDataValue(_T("TestObject"),pDvmData->m_strValue);
	}
}	

void QSttMacroParaEditViewRemote_AccuracyTable::GetTableWidgetItemValue(CDataGroup *pParas,long nIndex,QTableWidgetItem * pItem)
{
	CString strID;
	strID.Format(_T("TestItem%d"),nIndex+1);
	CDataGroup *pCurrDataGroup = (CDataGroup *)pParas->FindByID(strID);
	float fValue;
	stt_GetDataValueByID(pCurrDataGroup, _T("PulseWidth"), fValue);
	pItem->setText(QString::number(fValue,'f',0));
}

void QSttMacroParaEditViewRemote_AccuracyTable::UpdateTable(CDataGroup *pParas)
{
	QTableWidgetItem *pItem = NULL;
	for (int nRow = 0; nRow < this->rowCount(); nRow++)
	{
		pItem = item(nRow, 3);
		if (pItem == NULL)
		{
			continue;
		}
		GetTableWidgetItemValue(pParas,nRow,pItem);
	}
}

void QSttMacroParaEditViewRemote_AccuracyTable::slot_OnCellChanged( int row,int col )
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
	CDataGroup *pCurrDataGroup = (CDataGroup *)m_pAccuracyDataGroup->FindByID(strID);
	if (pCurrDataGroup == NULL)
	{
		return;
	}

	if (col == 3)
	{
		float fv =  pItem->text().toFloat();
		fv = setLimit(0,100000,fv);
		pCurrDataGroup->SetDataValue(_T("PulseWidth"),fv);
		pItem->setText(pItem->text());
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}




