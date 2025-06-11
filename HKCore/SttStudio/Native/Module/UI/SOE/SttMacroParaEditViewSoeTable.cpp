#include "SttMacroParaEditViewSoeTable.h"
#include <QHeaderView>
#include "../../XLangResource_Native.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTest/Common/tmt_test_paras_head.h"
#include "../Module/CommonMethod/commonMethod.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

#include <QApplication>
#include <QHeaderView>
#include "SttMacroParaEditViewSoeWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include <QDateTime>


QSttMacroParaEditViewSoeTable::QSttMacroParaEditViewSoeTable(int nTableType,QWidget *parent)
#ifdef _PSX_QT_LINUX_
: QScrollTableWidget(parent)
#else
: QTableWidget(parent)
#endif
{
	m_nTableType = nTableType;
	m_pSoeParas = NULL;
	m_pCurrKeyboardItem = NULL;
	m_pInitStateComboBox = NULL;
	m_pTestObjetcComboBox = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
	
	InitUI();
}

QSttMacroParaEditViewSoeTable::~QSttMacroParaEditViewSoeTable()
{

}

void QSttMacroParaEditViewSoeTable::InitUI()
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


void QSttMacroParaEditViewSoeTable::InitTable()
{
	QStringList  HStrList;
	if (m_nTableType == SOE_TABLE_First)
	{
		HStrList << _T("遥信通道") << _T("选择") <<  _T("开出通道")<< _T("初始状态")  << _T("测试对象")  << _T("闭合时长(ms)");
		setColumnCount(6);
		setHorizontalHeaderLabels(HStrList);
 		QFontMetrics fontMetrics = QFontMetrics(this->font());
		this->setColumnWidth(STT_SOE_FirstTABLE_COL_Index,120);
		this->setColumnWidth(STT_SOE_FirstTABLE_COL_Select,120);
		this->setColumnWidth(STT_SOE_FirstTABLE_COL_BoutChanal,140);
		this->setColumnWidth(STT_SOE_FirstTABLE_COL_State,140);
		this->setColumnWidth(STT_SOE_FirstTABLE_COL_Object,220);
		this->setColumnWidth(STT_SOE_FirstTABLE_COL_ClosedTime,120);


		m_pCheckBoxDelegateBase = new QExBaseListCheckBoxDelegate(this);
		setItemDelegateForColumn(STT_SOE_FirstTABLE_COL_Select,m_pCheckBoxDelegateBase);
	}
	else if (m_nTableType == SOE_TABLE_Second)
	{
		HStrList << _T("编号") <<  _T("间隔") << _T("YX通道") << _T("事件描述")<< _T("事件发生时间") ;
		setColumnCount(5);
		setHorizontalHeaderLabels(HStrList);
		QFontMetrics fontMetrics = QFontMetrics(this->font());
		this->setColumnWidth(STT_SOE_SecondTABLE_COL_Index,100);
		this->setColumnWidth(STT_SOE_SecondTABLE_COL_Internal,150);
		this->setColumnWidth(STT_SOE_SecondTABLE_COL_Chanal,200);
		this->setColumnWidth(STT_SOE_SecondTABLE_COL_EventDescribe,220);
		this->setColumnWidth(STT_SOE_SecondTABLE_COL_EventTime,200);
	}
}


void QSttMacroParaEditViewSoeTable::UpdateTestObjet( CExBaseList *pList )
{
	oObjectNameList.clear();
	oObjectIDList.clear();
	QStringList strObjectList,strObjectIDList;

	CDvmDataset *pDvmDatasetRef = (CDvmDataset *)pList->GetAt(long(0));
	if (pDvmDatasetRef != NULL)
	{
 		POS pos_dataset = pDvmDatasetRef->GetHeadPosition();
 		while(pos_dataset) 
 		{
			CExBaseObject *pCurObj = (CExBaseObject* )pDvmDatasetRef->GetNext(pos_dataset);
			if (pCurObj != NULL)
			{
				strObjectList.append(pCurObj->m_strName);
				strObjectIDList.append(pCurObj->m_strID);
			}
		}
	}

	for (int i=0; i<g_nBinCount; i++)
	{
		oObjectNameList.push_back(strObjectList);
		oObjectIDList.push_back(strObjectIDList);
		oObjectIDList[i].append(""); 
	}

	m_pTestObjetcComboBox->updateItems(oObjectNameList);
}

void QSttMacroParaEditViewSoeTable::InitData(tmt_SoeParas *pSoeParas)
{
	m_pSoeParas = pSoeParas;
	QTableWidgetItem *item = NULL; 

	for (int i=0; i<g_nBinCount; i++)
	{
		int nRows = i;
		insertRow(nRows);
		//序号
		item = new QTableWidgetItem();
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setText(QString("%1").arg(nRows+1));
		setItem(nRows, STT_SOE_FirstTABLE_COL_Index, item); 

		//选择
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));

		if (pSoeParas->m_binOut[i].isValid == 1)
		{
			item->setCheckState(Qt::Checked);
		}
		else
		{
			item->setCheckState(Qt::Unchecked);
		}

		setItem(nRows, STT_SOE_FirstTABLE_COL_Select, item); 

		//通道
		CString strChnnel;
		xlang_GetLangStrByFile(strChnnel, "Native_BoutX");
		strChnnel += QString::number(nRows+1);
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));
		item->setText(strChnnel);
		setItem(nRows, STT_SOE_FirstTABLE_COL_BoutChanal, item); 

		//初始状态
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		setInitStateComboxSoeDelegate(nRows,item,pSoeParas);

		//测试对象
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		m_pTestObjetcComboBox = new CComboBoxSoeDelegate(this);
		setItemDelegateForColumn(STT_SOE_FirstTABLE_COL_Object, m_pTestObjetcComboBox);
		UpdateDeviceData(nRows,STT_SOE_FirstTABLE_COL_Object,item);
		setItem(nRows, STT_SOE_FirstTABLE_COL_Object, item); 

		//闭合时长
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));
		item->setText(QString::number(pSoeParas->m_binOut[i].otmt_SoeState[1].time,'f',0));
		setItem(nRows, STT_SOE_FirstTABLE_COL_ClosedTime, item); 
	}	

	UpdateTestObjet(&g_pSoeTest->m_IntervalList);
	UpdateTable();
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(m_pInitStateComboBox,SIGNAL(commitData(QWidget*)),this,SLOT(slot_SoeCountChanged(QWidget*)),Qt::UniqueConnection);
	connect(m_pTestObjetcComboBox,SIGNAL(commitData(QWidget*)),this,SLOT(slot_TestObjectChanged(QWidget*)),Qt::UniqueConnection);
}

void QSttMacroParaEditViewSoeTable::UpdateDeviceData(int row,int col,QTableWidgetItem *pItem)
{
	if (pItem == NULL)
	{
		return;
	}

	CDvmDataset * pDvmDatasetRef = (CDvmDataset *)g_pSoeTest->m_IntervalList.GetAt(long(0));
	if (pDvmDatasetRef != NULL)
	{		
		POS pos_dataset = pDvmDatasetRef->GetHeadPosition();
		while(pos_dataset)
		{
			CExBaseObject *pCurObj = (CExBaseObject* )pDvmDatasetRef->GetAt(row);
			if (col == STT_SOE_FirstTABLE_COL_Object)
			{
			if (pCurObj != NULL)
			{
					pItem->setText(pCurObj->m_strName);	
					if(m_pSoeParas)
					{
						CString_to_char(pCurObj->m_strID,m_pSoeParas->m_binOut[row].m_strTestObject);
					}
				}
				else
				{
					pItem->setText(_T("空"));	
					if(m_pSoeParas)
					{
						CString_to_char(_T(""),m_pSoeParas->m_binOut[row].m_strTestObject);
					}
				}	
					return;
				}
			}
		}
}

void QSttMacroParaEditViewSoeTable::setInitStateComboxSoeDelegate(int row,QTableWidgetItem *pItem,tmt_SoeParas *pSoeParas)
{
	if (m_pInitStateComboBox == NULL)
	{
		m_pInitStateComboBox = new CComboBoxSoeDelegate(this);
		setItemDelegateForColumn(STT_SOE_FirstTABLE_COL_State,m_pInitStateComboBox);
	}
	if (pSoeParas->m_binOut[row].otmt_SoeState[0].val == 0)
	{
		pItem->setText(g_sLangTxt_SOE_Break);
	}
	else
	{
		pItem->setText(g_sLangTxt_SOE_Shutting);
	}

	setItem(row, STT_SOE_FirstTABLE_COL_State, pItem); 
}

void QSttMacroParaEditViewSoeTable::slot_SoeCountChanged(QWidget* editor)
{
	if (editor == NULL)
	{
		return;
	}

	QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);
	CString strTemp;
	strTemp = pComboBox->currentText();
	int nRow = currentRow();

	if (strTemp == g_sLangTxt_SOE_Break)
	{
		m_pSoeParas->m_binOut[nRow].otmt_SoeState[0].val = 0;
		m_pSoeParas->m_binOut[nRow].otmt_SoeState[1].val = 1;
	}
	else
	{
		m_pSoeParas->m_binOut[nRow].otmt_SoeState[0].val = 1;
		m_pSoeParas->m_binOut[nRow].otmt_SoeState[1].val = 0;
	}
}

void QSttMacroParaEditViewSoeTable::slot_TestObjectChanged( QWidget* editor )
{
	if (editor == NULL)
	{
		return;
	}

	QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);
	if (pComboBox == NULL)
	{
		return;
	}
	QVariant varRow = pComboBox->property("row");
	if (!varRow.isValid())
	{
		return;
	}

	int nRow = varRow.toInt(); // 获取正确的行号
	/*int nRow = currentRow();*/
	if(nRow < 0 )
	{
		return;
	}
	QStringList strItemList = oObjectIDList[nRow];
	CString strText = pComboBox->currentText();
	int nIndex  = oObjectNameList[nRow].indexOf(strText);
	if (nIndex < 0)
	{
		nIndex = strItemList.size() - 1;
	}
	
	QString strValue = strItemList.at(nIndex);

	CString_to_char(strValue,m_pSoeParas->m_binOut[nRow].m_strTestObject);


	UpdateSelTestObject();
}

void QSttMacroParaEditViewSoeTable::slot_OnItemDoubleClicked(QTableWidgetItem *pItem)
{
	if(!(pItem->flags() & Qt::ItemIsEnabled))
	{
		return;
	}

	int nRow = row(pItem);
	int nCol = column(pItem);
	QString strValue = pItem->text();

	long nEditType = 4;
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::Attach330Channel(this, nEditType);
#endif

	m_pCurrKeyboardItem = pItem;
}

#ifdef _PSX_QT_LINUX_
//bool QSttMacroParaEditViewSoeTable::eventFilter(QObject *obj, QEvent *event)
//{
// 	if (event->type() == QEvent::MouseButtonDblClick)
// 	{
// 		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
// 		m_bRunning = TRUE;
//  		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
//  		m_bRunning = FALSE;
// 		return true;
// 	}

//	return QScrollTableWidget::eventFilter(obj,event);
//}
 
void QSttMacroParaEditViewSoeTable::mousePressEvent(QMouseEvent * event)
{
// 	if (m_bRunning)
// 	{
// 		QScrollTableWidget::mousePressEvent(event);
// 		return;
// 	}
// 
//  	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
//  	QApplication::postEvent(this,pEvent);

	QModelIndex index = indexAt(event->pos()); 
	if (index.isValid() && (index.column() == STT_SOE_FirstTABLE_COL_State || index.column() == STT_SOE_FirstTABLE_COL_Object)) 
	{
		this->edit(index);
		QWidget *editor = this->indexWidget(index);
		QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);

		if (pComboBox)
	{
			pComboBox->showPopup();
		}
	}
	else
	{
		QScrollTableWidget::mousePressEvent(event);
	}
}
#endif

void QSttMacroParaEditViewSoeTable::UpdateText( const QString &strText )
{

}

void QSttMacroParaEditViewSoeTable::UpdateTable()
{
	float fTime = g_pSoeTest->m_pPulseWidth_Edit->text().toFloat();
	float fSoeTime = g_pSoeTest->m_pSOE_Edit->text().toFloat();
	int nTime = 20,nIndex = 0;
	for (int i = 0; i<g_nBinCount; i++)
	{
		QTableWidgetItem *pItem = item(i,STT_SOE_FirstTABLE_COL_Select);
		if (pItem == NULL)
		{
			return;
		}

		if (pItem->checkState() !=  Qt::Unchecked)
		{
			m_pSoeParas->m_binOut[i].otmt_SoeState[1].time = fTime;	
			item(i,STT_SOE_FirstTABLE_COL_ClosedTime)->setText(QString::number(m_pSoeParas->m_binOut[i].otmt_SoeState[1].time));

			m_pSoeParas->m_binOut[i].otmt_SoeState[0].time = nTime + fSoeTime*nIndex; //变位前时长
			nIndex++;
		}
	}
}


void QSttMacroParaEditViewSoeTable::slot_InterChanged(int nIndex)
{
	CDvmDataset *pDvmDatasetRef = NULL;
	CExBaseObject *pCurObj = NULL;
	QStringList objectNames,oObjectID;

	pDvmDatasetRef = (CDvmDataset *)g_pSoeTest->m_IntervalList.GetAt(nIndex);
	if (pDvmDatasetRef != NULL)
	{
		POS pos_dataset = pDvmDatasetRef->GetHeadPosition();
		while(pos_dataset)
		{
			pCurObj = (CExBaseObject* ) pDvmDatasetRef->GetNext(pos_dataset);
			if (pCurObj != NULL)
			{
				objectNames.append(pCurObj->m_strName);
				oObjectID.append(pCurObj->m_strID);
			}
		}
	}

	if(m_pTestObjetcComboBox)
	{
		oObjectIDList.clear(); 
		oObjectNameList.clear();
		for (int i=0; i<g_nBinCount; i++)
		{
			oObjectNameList.push_back(objectNames);
			oObjectIDList.push_back(oObjectID);
		}
		m_pTestObjetcComboBox->updateItems(oObjectNameList);
	}

	UpdateDeviceData(currentRow(),STT_SOE_FirstTABLE_COL_Object,item(currentRow(), STT_SOE_FirstTABLE_COL_Object));
}


void QSttMacroParaEditViewSoeTable::AddShowSoeReports(CDvmDataset *pSoeRptDataset)
{
	if (pSoeRptDataset == NULL)
	{
		return;
	}


	long nCurrRowIndex = rowCount();

	QTableWidgetItem *item = NULL; 
	POS pos = pSoeRptDataset->GetHeadPosition();
	CDvmData *pCurrData = NULL;
	CString strTmpString;

	while(pos)
	{
		pCurrData = (CDvmData*)pSoeRptDataset->GetNext(pos); 

		if (pCurrData == NULL)
		{
			continue;
		}

		if (g_pSoeTest->m_SelectTestObjetcList.contains(pCurrData->m_strID))
		{
			if (nCurrRowIndex >= rowCount())
			{
				setRowCount(nCurrRowIndex + 1);
			}

		//编号
		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setText(QString::number(nCurrRowIndex+1));
		setItem(nCurrRowIndex,STT_SOE_SecondTABLE_COL_Index,item);

		//间隔
		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		CDvmDataset *pCurrDataset = (CDvmDataset*)g_pSoeTest->m_pInterSelect_ComboBox->GetCurrSelObject();
		if (pCurrDataset)
		{
			strTmpString = pCurrDataset->m_strName;
		}
		else
		{
			strTmpString = "---";
		}

		item->setText(pCurrDataset->m_strName);
			setItem(nCurrRowIndex,STT_SOE_SecondTABLE_COL_Internal,item);

		//YX通道
		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		if (pCurrData->m_strName.IsEmpty())
		{
			item->setText(pCurrData->m_strID);
		}
		else
		{
		item->setText(pCurrData->m_strName);
		}
		setItem(nCurrRowIndex,STT_SOE_SecondTABLE_COL_Chanal,item);

		//事件描述
		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		strTmpString = _T("遥信值:");
		strTmpString = strTmpString + pCurrData->m_strValue;

		if (pCurrData->m_strName.IsEmpty())
		{
			strTmpString = strTmpString + _T("(")+ pCurrData->m_strID + _T(")");
		}
		else
		{
		strTmpString = strTmpString + _T("(")+ pCurrData->m_strName + _T(")");
		}
		item->setText(strTmpString);
		setItem(nCurrRowIndex,STT_SOE_SecondTABLE_COL_EventDescribe,item);

		//事件发生时间
		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		strTmpString = GetSoeAttrValue(pCurrData,"$t");
// #ifdef _PSX_QT_LINUX_			
// 			QDateTime dateTime = QDateTime::fromString(strTmpString, "yyyy-MM-dd HH:mm:ss.zzz");
// 			dateTime.setTimeSpec(Qt::UTC);
// 			dateTime = dateTime.addSecs(g_oSystemParas.m_nTimeZone * 3600); 
// 			strTmpString = dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
// #endif
		item->setText(strTmpString);
		setItem(nCurrRowIndex,STT_SOE_SecondTABLE_COL_EventTime,item);

		nCurrRowIndex++;
	}
	}
}

CString QSttMacroParaEditViewSoeTable::GetSoeAttrValue( CDvmData *pCurrData,const CString &strSearchID )
{
	CString strText;
	strText = "---";
	POS pos = pCurrData->GetHeadPosition();
	CDvmValue *pCurrValue = NULL;

	while(pos)
	{
		pCurrValue = (CDvmValue*)pCurrData->GetNext(pos);

		if (pCurrValue->m_strID.Find(strSearchID) != -1)
		{
			strText = pCurrValue->m_strValue;
			break;
		}
	}

	return strText;
}

void QSttMacroParaEditViewSoeTable::slot_OnCellChanged( int row,int col )
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
	QString str = pItem->text();

	if(col == STT_SOE_FirstTABLE_COL_Select)
	{
		if (pItem->checkState() !=  Qt::Unchecked)
		{
			m_pSoeParas->m_binOut[row].isValid = 1;
		}
		else
		{
			m_pSoeParas->m_binOut[row].isValid = 0;
		}

		UpdateTable();	
		UpdateSelTestObject();
	}
	if(col == STT_SOE_FirstTABLE_COL_State)
	{
		if (str == _T("断开"))
		{
			m_pSoeParas->m_binOut[row].otmt_SoeState[0].val = 0;
		}
		else
		{
			m_pSoeParas->m_binOut[row].otmt_SoeState[0].val = 1;
		}
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void QSttMacroParaEditViewSoeTable::UpdateSelTestObject()
{
	int nSelCount = 0;
	for (int i=0; i<g_nBinCount; i++)
	{
		if (m_pSoeParas->m_binOut[i].isValid == 1)
		{
			CString strValue = m_pSoeParas->m_binOut[i].m_strTestObject;
			CString_to_char(strValue,m_pSoeParas->m_strSelTestObject[nSelCount]);
			nSelCount++;
		}
		else
		{
			CString_to_char(_T(""),m_pSoeParas->m_strSelTestObject[nSelCount]);
		}
	}
}


CComboBoxSoeDelegate::CComboBoxSoeDelegate(QObject *parent):QItemDelegate (parent)
{
	
}

CComboBoxSoeDelegate::~CComboBoxSoeDelegate()
{

}

QWidget *CComboBoxSoeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, 
											const QModelIndex &index) const
{
	QVariant variant = index.data();

	QScrollComboBox *pComboBox = new QScrollComboBox(parent,false);

#ifdef _PSX_QT_LINUX_//linux下需要特殊处理下
	pComboBox->SetIgnoreFirstHidePopup(true);
#endif
	return pComboBox;
}


void CComboBoxSoeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString strItem = index.model()->data(index,Qt::EditRole).toString();
	QStringList strItemList;
	
	if (index.column() == STT_SOE_FirstTABLE_COL_State)
	{
		strItemList<<g_sLangTxt_SOE_Break<<g_sLangTxt_SOE_Shutting;
	}
	else if (index.column() == STT_SOE_FirstTABLE_COL_Object)
	{
		strItemList = m_ObjectIndexList[index.row()];
	}

	QSet<QString> usedItems;
	const QAbstractItemModel *model = index.model();
	int rowCount = model->rowCount();
	int columnCount = model->columnCount();

	for (int row = 0; row < rowCount; ++row)
	{
		if (row == index.row()) 
			continue;

		for (int col = 0; col < columnCount; ++col)
		{
			if (col == STT_SOE_FirstTABLE_COL_Object) 
			{
				QModelIndex idx = model->index(row, col);
				QString item = model->data(idx, Qt::EditRole).toString();
				usedItems.insert(item);
			}
		}
	}

	QScrollComboBox *pComboBox = qobject_cast<QScrollComboBox *>(editor);
	if (!pComboBox) 
		return;
	pComboBox->clear();
	pComboBox->setProperty("row", index.row());//将行号绑定到 QComboBox 上
	int id = 0;
	for (int i=0; i<strItemList.size(); i++)
	{
		QString strValue = strItemList.at(i);
		if (!usedItems.contains(strValue) || strValue == strItem) 
		{
			pComboBox->addItem(strValue);

		if (strValue == strItem)
		{
				id = pComboBox->count() - 1;
		}
		}
	}

	if (index.column() == STT_SOE_FirstTABLE_COL_Object)
	{
	pComboBox->addItem(_T("空")); 
		if (strItem == _T("空"))
		{
			id = pComboBox->count() - 1;  
		}
	}
	if (id >= 0)
	{
	pComboBox->setCurrentIndex(id);
	}

	if (pComboBox->isHidden())
	{
		pComboBox->showPopup();
	}
	connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(commitAndCloseEditor()));
}

void CComboBoxSoeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, 
										const QModelIndex &index) const
{
	QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);
	model->setData(index,pComboBox->currentText(),Qt::EditRole);
}

void CComboBoxSoeDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
												const QModelIndex &/*index*/) const
{
	editor->setGeometry(option.rect);
}

// 鼠标单击单元格的时候，重绘事件触发
void CComboBoxSoeDelegate::paint(QPainter * painter,
								 const QStyleOptionViewItem & option,
								 const QModelIndex & index) const
{  
	QProxyStyle oProxyStyle;
	QStyleOptionComboBox oStyleOptionComboBox;
	oStyleOptionComboBox.state = QStyle::State_On;
	oStyleOptionComboBox.rect = option.rect;
	QPalette oPalette;
	QSttMacroParaEditViewSoeTable *pParent = (QSttMacroParaEditViewSoeTable*)parent();

	if (pParent != NULL)
	{
		QTableWidgetItem *pTableWidgetItem = pParent->item(index.row(),index.column());

		if (pTableWidgetItem != NULL)
		{
			oStyleOptionComboBox.editable = true;
			oStyleOptionComboBox.frame = false;
			oStyleOptionComboBox.currentText = pTableWidgetItem->text();
		}
	}

	oProxyStyle.drawComplexControl(QStyle::CC_ComboBox,&oStyleOptionComboBox, painter);
	oProxyStyle.drawItemText(painter,option.rect,Qt::AlignCenter,oPalette,true,oStyleOptionComboBox.currentText);
}

void CComboBoxSoeDelegate::commitAndCloseEditor()
{
	QComboBox* editor = qobject_cast<QComboBox*>(sender());
	if (editor) 
	{
		emit commitData(editor);
		emit closeEditor(editor);
	}
}

void CComboBoxSoeDelegate::updateItems( const QVector<QStringList> ObjectIndexList )
{
	m_ObjectIndexList = ObjectIndexList;
}



