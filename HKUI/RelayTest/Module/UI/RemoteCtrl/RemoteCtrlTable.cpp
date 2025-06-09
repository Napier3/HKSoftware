#include "RemoteCtrlTable.h"
#include <QHeaderView>
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTest/Common/tmt_test_paras_head.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "SttMacroParaEditViewRemoteCtrl.h"
#include "../SttTestCntrFrameAPI.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

#include <QApplication>
#include <QHeaderView>

#define RemoteCtrlColunmCount      7
#define RemoteCtrlColunmCountSec      6


QRemoteCtrlTable::QRemoteCtrlTable(int nTableType,QWidget *parent)
: QScrollTableWidget(parent)
{
	m_nTableType = nTableType;

	m_pCurrKeyboardItem = NULL;

	m_nTime = 10000;
	m_nCnt = 100000;
	pLinedit = NULL;

	InitUI();

	m_bRunning = FALSE;
	installEventFilter(this);


}

QRemoteCtrlTable::~QRemoteCtrlTable()
{

}

void QRemoteCtrlTable::InitUI()
{

	QHeaderView* pLeft = verticalHeader();
	pLeft->setDefaultSectionSize(36);
	pLeft->setVisible(false);

	QHeaderView* pHeadTop =horizontalHeader();
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections
    pHeadTop->setSectionsClickable(false);
    pHeadTop->setSectionsMovable(false);
#else
    pHeadTop->setClickable(false);
    pHeadTop->setMovable(false);
#endif

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


void QRemoteCtrlTable::InitTable()
{
	if(stt_Frame_IsTestStarted())
	{
		for (int i=0; i<g_nBinCount; i++)
		{
			int nRows = i;
			insertRow(nRows);
		}
	}

	QStringList  HStrList;

	if (m_nTableType == REMOTECTRL_TABLE_First)
	{
		CString strIndex, strInternal, strChanal, strOperation, strAct, strRecord, strTime;
		xlang_GetLangStrByFile(strIndex, "sIndex");
		xlang_GetLangStrByFile(strInternal, "RemoteCtrl_Internal");
		xlang_GetLangStrByFile(strChanal, "Native_Channel");
		xlang_GetLangStrByFile(strOperation, "RemoteCtrl_Operation");
		xlang_GetLangStrByFile(strAct, "sAct");
		xlang_GetLangStrByFile(strRecord, "RemoteCtrl_Record");
		xlang_GetLangStrByFile(strTime, "sTime");
		HStrList << strIndex << strInternal << strChanal << strOperation << strAct<< strRecord << strTime;

		setColumnCount(RemoteCtrlColunmCount);
		setHorizontalHeaderLabels(HStrList);

		QFontMetrics fontMetrics = QFontMetrics(this->font());

		this->setColumnWidth(STT_REMOTECTRL_TABLE_COL_Index,50);
		this->setColumnWidth(STT_REMOTECTRL_TABLE_COL_Internal,100);
		this->setColumnWidth(STT_REMOTECTRL_TABLE_COL_Chanal,200);
		this->setColumnWidth(STT_REMOTECTRL_TABLE_COL_Operation,100);
		this->setColumnWidth(STT_REMOTECTRL_TABLE_COL_Act,125);
		this->setColumnWidth(STT_REMOTECTRL_TABLE_COL_Record,125);
		this->setColumnWidth(STT_REMOTECTRL_TABLE_COL_Time,250);
	}
	else if (m_nTableType == REMOTECTRL_TABLE_Second)
	{
		CString strIndex, strInternal, strChanal, strEventType, strDeviceTime, strPCTime;
		xlang_GetLangStrByFile(strIndex, "sIndex");
		xlang_GetLangStrByFile(strInternal, "RemoteCtrl_Internal");
		xlang_GetLangStrByFile(strChanal, "Native_Channel");
		xlang_GetLangStrByFile(strEventType, "RemoteCtrl_EventType");
		xlang_GetLangStrByFile(strDeviceTime, "RemoteCtrl_DeviceTime");
		xlang_GetLangStrByFile(strPCTime, "RemoteCtrl_PCTime");
		HStrList << strIndex << strInternal << strChanal << strEventType << strDeviceTime<< strPCTime;

		setColumnCount(RemoteCtrlColunmCountSec);
		setHorizontalHeaderLabels(HStrList);

		QFontMetrics fontMetrics = QFontMetrics(this->font());

		this->setColumnWidth(STT_REMOTECTRL_SecondTABLE_COL_Index,50);
		this->setColumnWidth(STT_REMOTECTRL_SecondTABLE_COL_Internal,100);
		this->setColumnWidth(STT_REMOTECTRL_SecondTABLE_COL_Chanal,200);
		this->setColumnWidth(STT_REMOTECTRL_SecondTABLE_COL_EventType,100);
		this->setColumnWidth(STT_REMOTECTRL_SecondTABLE_COL_DeviceTime,250);
		this->setColumnWidth(STT_REMOTECTRL_SecondTABLE_COL_PCTime,250);
	}

	for (int row = 0;  row  <  this->rowCount();  row++)
	{
		for (int col  =  0;  col  <  this->columnCount();  col++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item->setFlags(Qt::NoItemFlags);
			setItem(row,col,item);
		}
	}
}

void QRemoteCtrlTable::SetData()
{
	//ASSERT(pChData);
	//m_pmanualtest = pChData;

	//QTableWidgetItem *item = NULL; 
	//for (int i=0; i<g_nBinCount; i++)
	//{
	//	int nRows = i;
	//	insertRow(nRows);
	//}	

	//connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	//connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)),Qt::UniqueConnection);

}

void QRemoteCtrlTable::UpdateTable(int row,int col)
{
		
}

void QRemoteCtrlTable::UpdateText(const QString &strText)
{
	if (m_pCurrKeyboardItem == NULL)
	{
		return;
	}

	long nRow = m_pCurrKeyboardItem->row();
	long nCol = m_pCurrKeyboardItem->column();
	m_pCurrKeyboardItem->setText(strText);
	slot_OnCellChanged(nRow,nCol);
	// 	emit sig_updataParas();
}

void QRemoteCtrlTable::slot_OnCellChanged(int row,int col)
{

}

void QRemoteCtrlTable::slot_OnItemDoubleClicked(QTableWidgetItem *pItem)
{
	int nRow = row(pItem);
	int nCol = column(pItem);

	if (nCol == 1 || nCol == 2 || nCol==3  )
	{
		return;
	}

	if(!(pItem->flags() & Qt::ItemIsEnabled))
	{
		return;
	}

	CString strValue = pItem->text();

	long nEditType = 4;//数字键盘


#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::Attach330Channel(this, nEditType);
#endif

	m_pCurrKeyboardItem = pItem;
}

bool QRemoteCtrlTable::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}

	return QScrollTableWidget::eventFilter(obj,event);

}

void QRemoteCtrlTable::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QScrollTableWidget::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QScrollTableWidget::mousePressEvent(event);

}


void QRemoteCtrlTable::UpdateTableData( EventStruct* pEventStruct ,long nIndex )
{
	if (pEventStruct == NULL)
	{
		return;
	}

	setRowCount(nIndex);

	QTableWidgetItem *item = NULL; 
	//编号
	item =new QTableWidgetItem;
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setText(QString::number(nIndex));
	setItem(nIndex-1,STT_REMOTECTRL_TABLE_COL_Index,item);

	//间隔
	item =new QTableWidgetItem;
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setText(pEventStruct->strInterSelectName);
	setItem(nIndex-1,STT_REMOTECTRL_TABLE_COL_Internal,item);

	//通道
	item =new QTableWidgetItem;
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setText(pEventStruct->strChannelSelectName);
	setItem(nIndex-1,STT_REMOTECTRL_TABLE_COL_Chanal,item);

	//操作
	item =new QTableWidgetItem;
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setText(pEventStruct->strOperationSelectName);
	setItem(nIndex-1,STT_REMOTECTRL_TABLE_COL_Operation,item);

	//动作
	item =new QTableWidgetItem;
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setText(pEventStruct->strActionName);
	setItem(nIndex-1,STT_REMOTECTRL_TABLE_COL_Act,item);

	//记录
	item =new QTableWidgetItem;
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setText(pEventStruct->strRecord);
	setItem(nIndex-1,STT_REMOTECTRL_TABLE_COL_Record,item);

	//时间
	item =new QTableWidgetItem;
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	//QString strTime = pEventStruct->Recordtime.toString("yyyy-MM-dd hh:mm:ss.zzz");
	item->setText(pEventStruct->strRecordtime);
	setItem(nIndex-1,STT_REMOTECTRL_TABLE_COL_Time,item);
}

CString QRemoteCtrlTable::GetSoeAttrValue(CDvmData *pCurrData,const CString &strSearchID)
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

void QRemoteCtrlTable::AddShowSoeReports(CExBaseList *pSoeRptList)
{
	if (pSoeRptList == NULL)
	{
		return;
	}

	long nCurrRowIndex = rowCount();
	long nRowCount = nCurrRowIndex + pSoeRptList->GetCount();
	setRowCount(nRowCount);

	QTableWidgetItem *item = NULL; 
	POS pos = pSoeRptList->GetHeadPosition();
	CDvmData *pCurrData = NULL;
	CString strTmpString;

	while(pos)
	{
		bool bFoundData = false; 
		pCurrData = (CDvmData*)pSoeRptList->GetNext(pos); 
		//编号
		item =new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setText(QString::number(nCurrRowIndex+1));
		setItem(nCurrRowIndex,STT_REMOTECTRL_SecondTABLE_COL_Index,item);

		strTmpString = GetSoeAttrValue(pCurrData,"$q");
		long nIndex = CString_To_long(strTmpString);
        CDvmDevice* pDvmDevice = (CDvmDevice*)stt_Frame_GetDvmDevice();
		if(pDvmDevice == NULL)
		{
			return;
		}
		CDvmDataset *pDvmDatasetRef = NULL;
		CDvmData *pDvmData = NULL;
		CExBaseList *pCurObj = NULL;
		POS posDvmDevice = pDvmDevice->GetHeadPosition();
		while(posDvmDevice)
		{
			pCurObj = (CExBaseList*)pDvmDevice->GetNext(posDvmDevice);
			POS pos_dataset = pCurObj->GetHeadPosition();
			while(pos_dataset)
		{
				pDvmDatasetRef = (CDvmDataset *)pDvmDevice->GetNext(pos_dataset);
			if (pDvmDatasetRef->m_strID == "dsDin")
			{
					POS pos_data = pDvmDatasetRef->GetHeadPosition();
					while(pos_data)
					{
						pDvmData = (CDvmData *)pDvmDatasetRef->GetNext(pos_data);
						if (pDvmData->m_nIndex == nIndex)
						{
							bFoundData = true;

		//间隔
		item =new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
						if (pCurObj->m_strName.IsEmpty())
						{
							item->setText(pCurObj->m_strID);
						} 
						else
						{
							item->setText(pCurObj->m_strName);
						}
		setItem(nCurrRowIndex,STT_REMOTECTRL_SecondTABLE_COL_Internal,item);

		//通道
		item =new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		
							if (pDvmData->m_strName.IsEmpty())
		{
								item->setText(pDvmData->m_strID);
		} 
		else
		{
								item->setText(pDvmData->m_strName);
		}
		setItem(nCurrRowIndex,STT_REMOTECTRL_SecondTABLE_COL_Chanal,item);
							break;
						}
					}
				}
			}
		}

		if(!bFoundData)
		{
			item =new QTableWidgetItem;
			item->setFlags(item->flags() & ~Qt::ItemIsEditable);
			item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item->setText("---"); 
			setItem(nCurrRowIndex,STT_REMOTECTRL_SecondTABLE_COL_Internal,item);

			item = new QTableWidgetItem;
			item->setFlags(item->flags() & ~Qt::ItemIsEditable);
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			item->setText("---"); 
			setItem(nCurrRowIndex, STT_REMOTECTRL_SecondTABLE_COL_Chanal, item);
		}

// 		//间隔
// 		item =new QTableWidgetItem;
// 		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
// 		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 		item->setText("---");
// 		setItem(nCurrRowIndex,STT_REMOTECTRL_SecondTABLE_COL_Internal,item);

// 		//通道
// 		item =new QTableWidgetItem;
// 		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
// 		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 
// 		if (pCurrData->m_strName.IsEmpty())
// 		{
// 			item->setText(pCurrData->m_strID);
// 		} 
// 		else
// 		{
// 			item->setText(pCurrData->m_strName);
// 		}
// 		setItem(nCurrRowIndex,STT_REMOTECTRL_SecondTABLE_COL_Chanal,item);

		//事件类型
		item =new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

		if (CString_To_long(pCurrData->m_strValue)>0)
		{
			strTmpString = "合闸";
		} 
		else
		{
			strTmpString = "分闸";
		}
		
		item->setText(strTmpString);
		setItem(nCurrRowIndex,STT_REMOTECTRL_SecondTABLE_COL_EventType,item);

		//装置时间
		item =new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		strTmpString = GetSoeAttrValue(pCurrData,"$t");
		item->setText(strTmpString);
		setItem(nCurrRowIndex,STT_REMOTECTRL_SecondTABLE_COL_DeviceTime,item);

		//PC时间
		item =new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		strTmpString = GetSoeAttrValue(pCurrData,"$systime");
		item->setText(strTmpString);
		setItem(nCurrRowIndex,STT_REMOTECTRL_SecondTABLE_COL_PCTime,item);
		nCurrRowIndex++;
	}
}

void QRemoteCtrlTable::UpdateExcRlt(long nErrorInfor)
{
	long nRow = rowCount();
	QTableWidgetItem *pCurrItem = item(nRow - 1,STT_REMOTECTRL_TABLE_COL_Record);

	if (pCurrItem == NULL)
	{
		return;
	}

	CString strRcdText;

	if (nErrorInfor>0)
	{
		strRcdText = "失败";
	} 
	else
	{
		strRcdText = "成功";
	}

	pCurrItem->setText(strRcdText);
}

