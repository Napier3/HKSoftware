#include "SttMacroParaEditViewDualPositionTable.h"
#include <QHeaderView>
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/CommonMethod/commonMethod.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewDualPositionTable::QSttMacroParaEditViewDualPositionTable( QWidget *parent /*= 0*/ ): QScrollTableWidget(parent)

{
	m_pCurrKeyboardItem = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
	InitUI();
}

QSttMacroParaEditViewDualPositionTable::~QSttMacroParaEditViewDualPositionTable()
{

}

void QSttMacroParaEditViewDualPositionTable::InitUI()
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

void QSttMacroParaEditViewDualPositionTable::UpdateText( const QString &strText )
{

}


void QSttMacroParaEditViewDualPositionTable::InitTable()
{
	QStringList  HStrList;
	HStrList<< _T("测试项") <<  _T("开出设置")<< _T("触发方式")  << _T("输出时间(s)");

	setColumnCount(4);
	setHorizontalHeaderLabels(HStrList);

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	this->setColumnWidth(0,200);
	this->setColumnWidth(1,200);
	this->setColumnWidth(2,200);
	this->setColumnWidth(3,200);
}


void QSttMacroParaEditViewDualPositionTable::InitData( CDataGroup *pData )
{
	//m_pDualPositionDataGroup->DeleteChildren();
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));

	m_pIDList.clear();
	QStringList  oList;
	oList<< _T("Onposition") <<  _T("Offposition")<< _T("Onpositionabn")  << _T("Offpositionabn");

	int nCount = m_pDualPositionDataGroup->GetChildCount(DTMCLASSID_CDATAGROUP);
	for (int i = 0; i < nCount;i++)
	{
		CDataGroup *pDataGroup = (CDataGroup *)m_pDualPositionDataGroup->FindByID(oList[i]);
		if(pDataGroup)
		{
			pDataGroup->SetDataValue(_T("Select"),long(0));
			pDataGroup->SetDataValue(_T("_B01"),long(0));
			pDataGroup->SetDataValue(_T("_B02"),long(0));
			pDataGroup->SetDataValue(_T("_B03"),long(0));
			pDataGroup->SetDataValue(_T("_B04"),long(0));
			pDataGroup->SetDataValue(_T("_B05"),long(0));
			pDataGroup->SetDataValue(_T("_B06"),long(0));
			pDataGroup->SetDataValue(_T("_B07"),long(0));
			pDataGroup->SetDataValue(_T("_B08"),long(0));
		}
	}
	clearContents();
	setRowCount(0);
	
	CDvmData* pData0 = NULL;
	CDvmData* pData1 = NULL;

	CString strID,strText;
	
	for (int i = 0; i<g_nBinCount; i++)
	{
		strID.Format(_T("Bout%d"),i+1);
		CDvmData *pCurrData = (CDvmData *)pData->FindByID(strID);		
		if (pCurrData)
		{
			if (pCurrData->m_strValue == _T("Din_1"))
			{
				 pData0 = pCurrData;
			}
			else if ( pCurrData->m_strValue == _T("Din_2"))
			{
				 pData1 = pCurrData;
			}
		}
	}


	if (pData0 && pData1)
	{
		strText = pData0->m_strName;
		AddRow(_T("合位"), strText);
		UpdataData(_T("Onposition"),pData0);

		strText = pData1->m_strName;
		AddRow(_T("分位"), strText);
		UpdataData(_T("Offposition"),pData1);
		
		QString strText = QString("%1%2").arg(pData0->m_strName).arg(pData1->m_strName);		
		AddRow(_T("合异常"), strText);
		UpdataData(_T("Onpositionabn"),NULL);

		AddRow(_T("分异常"), _T("---"));
		UpdataData(_T("Offpositionabn"),NULL);
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void QSttMacroParaEditViewDualPositionTable::AddRow( const CString &col0Text, const CString &col1Text )
{
	QTableWidgetItem *pItem = NULL; 

	CString strText;
	long nCurrRowIndex = rowCount();

	setRowCount(nCurrRowIndex + 1);

	pItem = new QTableWidgetItem;
	pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	pItem->setText(col0Text);
	setItem(nCurrRowIndex, 0, pItem);

	pItem = new QTableWidgetItem;
	pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	pItem->setText(col1Text);
	setItem(nCurrRowIndex, 1, pItem);

	pItem = new QTableWidgetItem;
	pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	strText = _T("时间触发");
	pItem->setText(strText);
	setItem(nCurrRowIndex, 2, pItem);

	pItem = new QTableWidgetItem;
	//pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
// 	strText.Format(_T("%d"), 5);
// 	pItem->setText(strText + _T("s"));
	GetTableWidgetItemValue(m_pDualPositionDataGroup,nCurrRowIndex,pItem);
	setItem(nCurrRowIndex, 3, pItem);

	nCurrRowIndex++;
}

void QSttMacroParaEditViewDualPositionTable::UpdataData(CString strID,CDvmData *pDvmData)
{
	CDataGroup *pDataGroup = (CDataGroup *)m_pDualPositionDataGroup->FindByID(strID);
	if (pDataGroup)
	{	
		CString strValueID;
		pDataGroup->SetDataValue(_T("Select"),long(1));

		if (pDvmData)
		{
			pDataGroup->SetDataValue(_T("TestObject"),pDvmData->m_strValue);
			strValueID = pDvmData->m_strID.Right(1);
			strValueID.Format(_T("_B0%s"), strValueID.GetString());
			m_pIDList.append(strValueID);
			pDataGroup->SetDataValue(strValueID,long(1));
		}
		else
		{
			pDataGroup->SetDataValue(_T("TestObject"),"");

			if (strID == _T("Onpositionabn"))
			{
				for (int i = 0; i < m_pIDList.size(); ++i) 
				{
					strValueID = m_pIDList[i];
					pDataGroup->SetDataValue(strValueID,long(1));
				}
			}
		}
	}
}

void QSttMacroParaEditViewDualPositionTable::GetTableWidgetItemValue( CDataGroup *pParas ,long nIndex,QTableWidgetItem * pItem )
{
	QStringList  oList;
	oList<< _T("Onposition") <<  _T("Offposition")<< _T("Onpositionabn")  << _T("Offpositionabn");

	CDataGroup *pCurrDataGroup = (CDataGroup *)pParas->FindByID(oList[nIndex]);
	float fValue;
	stt_GetDataValueByID(pCurrDataGroup, _T("PulseWidth"), fValue);
	pItem->setText(QString::number(fValue,'f',0));
}

void QSttMacroParaEditViewDualPositionTable::UpdateTable( CDataGroup *pParas )
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

void QSttMacroParaEditViewDualPositionTable::slot_OnCellChanged( int row,int col )
{
	if (row  <  0 || col < 0)
	{
		return;
	}
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	QTableWidgetItem  *pItem  = this->item(row,col);

	if (pItem == NULL)
	{
		return;
	} 
	QStringList  oList;
	oList<< _T("Onposition") <<  _T("Offposition")<< _T("Onpositionabn")  << _T("Onpositionabn");

	CDataGroup *pCurrDataGroup = (CDataGroup *)m_pDualPositionDataGroup->FindByID(oList[row]);
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
