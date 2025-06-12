#include "SttMacroParaEditViewResolutionTable.h"
#include <QHeaderView>
#include "../../../XLangResource_Native.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/CommonMethod/commonMethod.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewResolutionTable::QSttMacroParaEditViewResolutionTable( QWidget *parent /*= 0*/ ): QScrollTableWidget(parent)

{
	m_pCurrKeyboardItem = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
	InitUI();
}

QSttMacroParaEditViewResolutionTable::~QSttMacroParaEditViewResolutionTable()
{

}

void QSttMacroParaEditViewResolutionTable::InitUI()
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

void QSttMacroParaEditViewResolutionTable::UpdateText( const QString &strText )
{

}


void QSttMacroParaEditViewResolutionTable::InitTable()
{
	QStringList  HStrList;
	HStrList<< _T("测试项") <<  _T("开出设置")<< _T("分辨率设置(ms)")  << _T("脉冲宽度(ms)");

	setColumnCount(4);
	setHorizontalHeaderLabels(HStrList);

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	this->setColumnWidth(0,200);
	this->setColumnWidth(1,200);
	this->setColumnWidth(2,200);
	this->setColumnWidth(3,200);
}


void QSttMacroParaEditViewResolutionTable::InitData( CDataGroup *pData )
{
	//m_pResolutionDataGroup->DeleteChildren();
	clearContents();
	setRowCount(0);
	
	CDvmData* pData0 = NULL;
	CDvmData* pData1 = NULL;
	CString strID,strText;
	
	for (int i = 0; i<8; i++)
	{
		strID.Format(_T("Bout%d"),i+1);
		CDataGroup *pDataGroup = (CDataGroup *)m_pResolutionDataGroup->FindByID(strID);
		pDataGroup->SetDataValue(_T("isValid"),long(0));

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
		AddRow(strText);
		UpdataData(pData0,0);
		
		strText = pData1->m_strName;
		AddRow(strText);
		UpdataData(pData1,1);
	}


	long nSelCount = 0;
	CString strSelTestObject ;
	for (int nIndex = 0; nIndex < 8;nIndex++)
	{
		strSelTestObject.Format(_T("SelTestObject%d"), nIndex);
		strID.Format(_T("Bout%d"), nIndex+1);
		m_pResolutionDataGroup->SetDataValue(strSelTestObject,"");

		if (pData0 && pData1)
		{
			if (strID == pData0->m_strID) 
			{			
				strSelTestObject.Format(_T("SelTestObject%d"), nSelCount++);
				m_pResolutionDataGroup->SetDataValue(strSelTestObject,pData0->m_strValue);
			}
			else if (strID == pData1->m_strID)
			{
				strSelTestObject.Format(_T("SelTestObject%d"), nSelCount++);
				m_pResolutionDataGroup->SetDataValue(strSelTestObject,pData1->m_strValue);
			}
		}
	}
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void QSttMacroParaEditViewResolutionTable::AddRow( const CString &colText )
{
	QTableWidgetItem *pItem = NULL; 

	CString strText;
	long nCurrRowIndex = rowCount();

	setRowCount(nCurrRowIndex + 1);

	pItem = new QTableWidgetItem;
	pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	strText = _T("分辨率测试");
	pItem->setText(strText);
	setItem(nCurrRowIndex, 0, pItem);

	pItem = new QTableWidgetItem;
	pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	pItem->setText(colText);
	setItem(nCurrRowIndex, 1, pItem);

	pItem = new QTableWidgetItem;
	//pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
// 	strText.Format(_T("%d"), 2);
// 	pItem->setText(strText + _T("ms"));
	GetTableWidgetItemValue(m_pResolutionDataGroup,pItem,_T("SoeResolution"));
	setItem(nCurrRowIndex, 2, pItem);


	pItem = new QTableWidgetItem;
	//pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
// 	strText.Format(_T("%d"), 500);
// 	pItem->setText(strText + _T("ms"));
	GetTableWidgetItemValue(m_pResolutionDataGroup,pItem,_T("KeepTime1"));
	setItem(nCurrRowIndex, 3, pItem);

	nCurrRowIndex++;

	// 合并单元格
	if (nCurrRowIndex > 1)
	{
		setSpan(0, 0, nCurrRowIndex, 1); 
		setSpan(0, 2, nCurrRowIndex, 1); 
		setSpan(0, 3, nCurrRowIndex, 1); 
	}
}

void QSttMacroParaEditViewResolutionTable::GetTableWidgetItemValue(CDataGroup *pParas,QTableWidgetItem * pItem,CString strID)
{	
	float fValue;
	stt_GetDataValueByID(pParas, strID, fValue);
	pItem->setText(QString::number(fValue,'f',0));
}


void QSttMacroParaEditViewResolutionTable::UpdataData(CDvmData *pDvmData ,long nIndex)
{
	float nTime = 2000,fSoeTime;
	stt_GetDataValueByID(m_pResolutionDataGroup, _T("SoeResolution"), fSoeTime);
	float nKeepTime0 = nTime + fSoeTime*nIndex;
	CDataGroup *pDataGroup = (CDataGroup *)m_pResolutionDataGroup->FindByID(pDvmData->m_strID);
	if (pDataGroup)
	{
		pDataGroup->SetDataValue(_T("isValid"),long(1));
		pDataGroup->SetDataValue(_T("TestObject"),pDvmData->m_strValue);
		pDataGroup->SetDataValue(_T("KeepTime0"),nKeepTime0);
	}
}


void QSttMacroParaEditViewResolutionTable::slot_OnCellChanged( int row,int col )
{
	if (row < 0 || col < 0) 
	{
		return;
	}
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	QTableWidgetItem  *pItem  = this->item(row,col);

	if (pItem == NULL)
	{
		return;
	} 

	int rowSpan = this->rowSpan(row, col);
	int colSpan = this->columnSpan(row, col);

	bool isTopLeftOfSpan = (rowSpan > 1 || colSpan > 1) && (this->item(row, col) != NULL);
	
	if (isTopLeftOfSpan) 
	{
		float fv =  pItem->text().toFloat();
		fv = setLimit(0,100000,fv);

		if (col == 2)
		{
			m_pResolutionDataGroup->SetDataValue(_T("SoeResolution"),fv);

			UpdateKeepTime();
		}
		else if (col == 3)
		{
			m_pResolutionDataGroup->SetDataValue(_T("KeepTime1"),fv);
		}
		pItem->setText(pItem->text());
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void QSttMacroParaEditViewResolutionTable::UpdateKeepTime()
{
	float nTime = 2000,fSoeTime;
	CString strID;
	long nisValid = 0,nIndex = 0;
	stt_GetDataValueByID(m_pResolutionDataGroup, _T("SoeResolution"), fSoeTime);
	for (int i = 0; i<8; i++)
	{
		strID.Format(_T("Bout%d"), i+1);
		CDataGroup *pDataGroup = (CDataGroup *)m_pResolutionDataGroup->FindByID(strID);
		stt_GetDataValueByID(pDataGroup, _T("isValid"), nisValid);
		if (nisValid == 1)
		{
			float nKeepTime0 = nTime + fSoeTime*nIndex;
			pDataGroup->SetDataValue(_T("KeepTime0"),nKeepTime0);
			nIndex++;
		}
	}
}

void QSttMacroParaEditViewResolutionTable::UpdateTable( CDataGroup *pParas )
{
	QTableWidgetItem *pItem = NULL;
	int nRow =  this->rowCount();
	if (nRow > 1)
	{
		pItem = item(0, 2);
		if (pItem )
		{
			GetTableWidgetItemValue(pParas,pItem,_T("SoeResolution"));
		}
		pItem = item(0, 3);
		if (pItem)
		{
			GetTableWidgetItemValue(pParas,pItem,_T("KeepTime1"));
		}
	}
}
