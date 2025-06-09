#include "SttMacroParaEditViewRemote_ShakeTable.h"
#include <QHeaderView>
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/CommonMethod/commonMethod.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewRemote_ShakeTable::QSttMacroParaEditViewRemote_ShakeTable( QWidget *parent /*= 0*/ ): QScrollTableWidget(parent)

{
	m_pCurrKeyboardItem = NULL;
	m_pCheckBoxDelegateBase = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
	InitUI();
}

QSttMacroParaEditViewRemote_ShakeTable::~QSttMacroParaEditViewRemote_ShakeTable()
{
	
}

void QSttMacroParaEditViewRemote_ShakeTable::InitUI()
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

void QSttMacroParaEditViewRemote_ShakeTable::UpdateText( const QString &strText )
{

}


void QSttMacroParaEditViewRemote_ShakeTable::InitTable()
{
	QStringList  HStrList;
	HStrList<< _T("选择")<< _T("测试项") <<  _T("开出设置")<< _T("防抖时间(ms)")  << _T("分辨率(ms)");

	setColumnCount(5);
	setHorizontalHeaderLabels(HStrList);

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	this->setColumnWidth(0,180);
	this->setColumnWidth(1,180);
	this->setColumnWidth(2,180);
	this->setColumnWidth(3,180);
	this->setColumnWidth(3,180);


	m_pCheckBoxDelegateBase = new QExBaseListCheckBoxDelegate(this);
	this->setItemDelegateForColumn(0,m_pCheckBoxDelegateBase);

}


void QSttMacroParaEditViewRemote_ShakeTable::InitData( CDataGroup *pData )
{
	/*m_pShakeDataGroup->DeleteChildren();*/
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));

	clearContents();
	setRowCount(0);
	QTableWidgetItem *pItem = NULL; 
	long nCurrRowIndex = rowCount();
	CString strID,strText;
	int nCount = m_pShakeDataGroup->GetChildCount(DTMCLASSID_CDATAGROUP);
// 	for (int nIndex = 0; nIndex < nCount;nIndex++)
// 	{
// 		strID.Format(_T("TestItem%d"), nIndex+1);
// 		CDataGroup *pDataGroup = (CDataGroup *)m_pShakeDataGroup->FindByID(strID);
// 		if(pDataGroup)
// 		{
// 			pDataGroup->SetDataValue(_T("Select"),long(0));
// 		}
// 	}

	for (int i = 0; i < g_nBinCount; i++)
	{
		strID.Format(_T("Bout%d"),i+1);
		CDvmData *pCurrData = (CDvmData *)pData->FindByID(strID);		
		if (pCurrData == NULL || pCurrData->m_strValue.IsEmpty())
		{
			continue;
		}
		if (nCurrRowIndex >= rowCount())
		{
			setRowCount(nCurrRowIndex + 1);
		}

		pItem = new QTableWidgetItem;
		pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
		GetTableWidgetItemValue(m_pShakeDataGroup,nCurrRowIndex,pItem,_T("Select"),true);
		//pItem->setCheckState(Qt::Checked);
		setItem(nCurrRowIndex,0,pItem);

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
		
		//strText = CString("遥信%1").arg(nCurrRowIndex+1);
		//strText.Format(_T("遥信%d"),nCurrRowIndex+1);
		pItem->setText(strText);
		setItem(nCurrRowIndex,1,pItem);

		pItem = new QTableWidgetItem;
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
		pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		pItem->setText(pCurrData->m_strName);
		setItem(nCurrRowIndex,2,pItem);

		pItem = new QTableWidgetItem;
		//pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
		pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		GetTableWidgetItemValue(m_pShakeDataGroup,nCurrRowIndex,pItem,_T("Resolution"),false);
		setItem(nCurrRowIndex,4,pItem);

		pItem = new QTableWidgetItem;
		pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		GetTableWidgetItemValue(m_pShakeDataGroup,nCurrRowIndex,pItem,_T("AntiShakeTime"),false);
		/*pItem->setText(_T("40"));*/
		setItem(nCurrRowIndex,3,pItem);

		nCurrRowIndex ++;
		UpdateTable(pCurrData,nCurrRowIndex);
	}

	int nStartIndex = nCurrRowIndex * 2 ;
	for (int nIndex = nStartIndex; nIndex < nCount;nIndex++)
	{
		strID.Format(_T("TestItem%d"), nIndex+1);
		CDataGroup *pDataGroup = (CDataGroup *)m_pShakeDataGroup->FindByID(strID);
		if(pDataGroup)
 		{
 			pDataGroup->SetDataValue(_T("Select"),long(0));
 		}
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void QSttMacroParaEditViewRemote_ShakeTable::slot_OnCellChanged( int row,int col )
{
	if (row  <  0)
	{
		return;
	}
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));

	long nSelect = 0;
	CString strPulseWidth,strResolution;
	QTableWidgetItem  *pItem  = this->item(row,col);

	if (pItem == NULL)
	{
		return;
	} 
	bool bCheck = false;

	if(col == 0)
	{
		if (pItem->checkState() !=  Qt::Unchecked)
		{
			nSelect = 1;
		}
		else
		{
			nSelect = 0;
		}
		bCheck = true;
	}
	else
	{
		float fv =  pItem->text().toFloat();
		fv = setLimit(0,100000,fv);
		pItem->setText(QString::number(fv,'f',0));
	}
		
	long nCount = 0;
	int nStartIndex = row * 2 + 1;
	QTableWidgetItem  *pItem1  = this->item(row,3);
	QTableWidgetItem  *pItem2  = this->item(row,4);
	for (int i = nStartIndex; i < nStartIndex+2;i++)
	{
		CString strID;
		strID.Format(_T("TestItem%d"),i);
		CDataGroup *pCurrDataGroup = (CDataGroup *)m_pShakeDataGroup->FindByID(strID);
		if (pCurrDataGroup == NULL)
		{
			return;
		}
// 		if (!bCheck)
// 		{
// 			QTableWidgetItem  *pItem  = this->item(row,0);
// 			nSelect = (Qt::Checked == pItem->checkState());
// 		}
		if(bCheck)
		{
			pCurrDataGroup->SetDataValue(_T("Select"),nSelect);
		}


		float fPulseWidth = pItem1->text().toFloat();
		float fResolution = pItem2->text().toFloat();
		pCurrDataGroup->SetDataValue(_T("AntiShakeTime"),fPulseWidth);

		if (nCount == 0)
		{
			fPulseWidth = fPulseWidth - fResolution;
		}
		else
		{
			fPulseWidth = fPulseWidth + fResolution;
		}	
		pCurrDataGroup->SetDataValue(_T("Resolution"),fResolution);
		pCurrDataGroup->SetDataValue(_T("PulseWidth"),fPulseWidth);

		nCount++;
	}


	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void QSttMacroParaEditViewRemote_ShakeTable::GetTableWidgetItemValue(CDataGroup *pParas,long nIndex, QTableWidgetItem * pItem,const CString strID ,bool bCheck)
{
	long nItemCount = nIndex*2 + 1;
	CString strItemID;
	strItemID.Format(_T("TestItem%d"),nItemCount);

	CDataGroup *pCurrDataGroup = (CDataGroup *)pParas->FindByID(strItemID);
	if (pCurrDataGroup == NULL)
	{
		return;
	}
	if (bCheck)
	{
		long nIsSelected;
		stt_GetDataValueByID(pCurrDataGroup, strID, nIsSelected);

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
		float fValue = 0;
		stt_GetDataValueByID(pCurrDataGroup, strID, fValue);
// 		if (fValue == 0)
// 		{
// 			if (strID == _T("PulseWidth"))
// 			{
// 				fValue = 38;
// 			}
// 			else if (strID == _T("Resolution"))
// 			{
// 				fValue = 2;
// 			}
// 		}
// 		if (strID == _T("AntiShakeTime"))
// 		{
// 			QTableWidgetItem  *pItem  = this->item(nIndex,4);
// 			float fResolution = pItem->text().toFloat();
// 			if (nIndex % 2 == 0)
// 			{
// 				fValue = fValue - fResolution ;
// 			}
// 			else
// 			{
// 				fValue = fValue + fResolution ;
// 			}
// 		}
		
		pItem->setText(QString::number(fValue,'f',0));
	}
}

void QSttMacroParaEditViewRemote_ShakeTable::UpdateTable( CDvmData *pDvmData,long nIndex )
{
	CString strID;
	long nCount = 0;
	QTableWidgetItem  *pCheckItem  = this->item(nIndex-1,0);
	QTableWidgetItem  *pItem  = this->item(nIndex-1,3);
	QTableWidgetItem  *pItem1  = this->item(nIndex-1,4);

	int nStartIndex = nIndex * 2 - 1;

	for (int i = nStartIndex; i < nStartIndex+2;i++)
	{
		strID.Format(_T("TestItem%d"),i);
		CDataGroup *pDataGroup = (CDataGroup *)m_pShakeDataGroup->FindByID(strID);
		if (pDataGroup)
		{
			//pDataGroup->SetDataValue(_T("Select"),long(1));
			pDataGroup->SetDataValue(_T("TestObject"),pDvmData->m_strValue);
			pDataGroup->SetDataValue(_T("BoutSet"),pDvmData->m_strName.Right(1));

			pCheckItem->setCheckState(Qt::Checked);

			float fPulseWidth = pItem->text().toFloat();
			float fResolution = pItem1->text().toFloat();

			if (nCount == 0)
			{
				fPulseWidth = fPulseWidth - fResolution;
			}
			else
			{
				fPulseWidth = fPulseWidth + fResolution;
			}	
			pDataGroup->SetDataValue(_T("PulseWidth"),fPulseWidth);

			nCount++;
		}
	}
}

void QSttMacroParaEditViewRemote_ShakeTable::UpdateTable( CDataGroup *pParas )
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));

	QTableWidgetItem *pItem = NULL;
	for (int nRow = 0; nRow < this->rowCount(); nRow++)
	{
		pItem = item(nRow, 0);
		if (pItem)
		{
			GetTableWidgetItemValue(pParas,nRow,pItem,_T("Select"),true);
		}

		pItem = item(nRow, 4);
		if (pItem)
		{
			GetTableWidgetItemValue(pParas,nRow,pItem,_T("Resolution"),false);
		}
		pItem = item(nRow, 3);
		if (pItem)
		{
			GetTableWidgetItemValue(pParas,nRow,pItem,_T("AntiShakeTime"),false);
		}
	}
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

