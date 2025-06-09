#include "SttMacroParaEditViewSoeTable.h"
#include <QHeaderView>
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTest/Common/tmt_test_paras_head.h"
#include "../Module/CommonMethod/commonMethod.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif



#include <QApplication>
#include <QHeaderView>

#define SOEColunmCount      9



QSttMacroParaEditViewSoeTable::QSttMacroParaEditViewSoeTable(QWidget *parent)
: QScrollTableWidget(parent)
{

	m_pSoeTest = NULL;
	m_pCurrKeyboardItem = NULL;
	m_pComboBox =NULL;

	m_nTime = 10000;
	m_nCnt = 1000; //SOE变位次数限制1000
	pLinedit = NULL;

	InitUI();

	m_bRunning = FALSE;
	installEventFilter(this);


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


void QSttMacroParaEditViewSoeTable::InitTable()
{

	QStringList  HStrList;
	CString strIndex, strSelect, strChanal, strState, strTimeBinAct, strTimeBinExAct, strTimeBoutAct, strCount,strHoldTime;//序号,选择,通道,初始状态，变位前时长，闭合时长，断开时长，变位次数

	xlang_GetLangStrByFile(strIndex, "sSerNumber"); //序号
	xlang_GetLangStrByFile(strSelect, "sSelect");//选择
	xlang_GetLangStrByFile(strChanal, "Native_Channel");//通道
 	xlang_GetLangStrByFile(strState, "Soe_state");
	xlang_GetLangStrByFile(strTimeBinAct, "Soe_ChangeBeforTime");
	xlang_GetLangStrByFile(strTimeBinExAct, "Soe_ShuttingTime");
	xlang_GetLangStrByFile(strTimeBoutAct, "Soe_DisconTimes");
	xlang_GetLangStrByFile(strCount, "Soe_Count");
	xlang_GetLangStrByFile(strHoldTime, "Soe_SustainTimes");

	HStrList << strIndex << strSelect << strChanal << strState << strTimeBinAct<< strTimeBinExAct << strTimeBoutAct << strCount<<strHoldTime;


	setColumnCount(SOEColunmCount);
	setHorizontalHeaderLabels(HStrList);

	QFontMetrics fontMetrics = QFontMetrics(this->font());

	// 	int nLabelWidth1 = fontMetrics.width(strIndex) + 40;
	// 	int nLabelWidth2 = fontMetrics.width(strSelect) + 20;
	// 	int nLabelWidth3 = fontMetrics.width(strChanal) + 10;
	// 	int nLabelWidth4 = fontMetrics.width(strStat) + 10 ;
	// 	int nLabelWidth5 = fontMetrics.width(strTimeBinAct) + 50;
	// 	int nLabelWidth6 = fontMetrics.width(strTimeBinExAct) + 50;
	// 	int nLabelWidth7 = fontMetrics.width(strTimeBoutAct) + 50;
	// 	int nLabelWidth8 = fontMetrics.width(strCount) + 10 ;
	// 
	// 
	// 	this->setColumnWidth(0,nLabelWidth1);
	// 	this->setColumnWidth(1,nLabelWidth2);
	// 	this->setColumnWidth(2,nLabelWidth3);
	// 	this->setColumnWidth(3,nLabelWidth4);
	// 	this->setColumnWidth(4,nLabelWidth5);
	// 	this->setColumnWidth(5,nLabelWidth6);
	// 	this->setColumnWidth(6,nLabelWidth7);
	// 	this->setColumnWidth(7,nLabelWidth8);

	this->setColumnWidth(STT_SOE_TABLE_COL_Index,50);
	this->setColumnWidth(STT_SOE_TABLE_COL_Select,70);
	this->setColumnWidth(STT_SOE_TABLE_COL_Chanal,90);
	this->setColumnWidth(STT_SOE_TABLE_COL_Stat,100);
	this->setColumnWidth(STT_SOE_TABLE_COL_TimeBinAct,140);
	this->setColumnWidth(STT_SOE_TABLE_COL_TimeBinExAct,140);
	this->setColumnWidth(STT_SOE_TABLE_COL_TimeBoutAct,140);
	this->setColumnWidth(STT_SOE_TABLE_COL_Count,120);
	this->setColumnWidth(STT_SOE_TABLE_COL_HoldTime,120);

	m_pCheckBoxDelegateBase = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(1,m_pCheckBoxDelegateBase);

}

// QScrollComboBox* QSttMacroParaEditViewSoeTable::NewStatType()
// {
// 	QScrollComboBox *pStateCombox = new QScrollComboBox(this);
// 	CString strText;
// 	strText = _T("断开");
// 	pStateCombox->addItem(strText);
// 
// 	strText = _T("闭合");
// 	pStateCombox->addItem(strText);
// 	pStateCombox->setEditable(true);
// 	pStateCombox->lineEdit()->setAlignment(Qt::AlignCenter);
// 	return pStateCombox;
// }

void QSttMacroParaEditViewSoeTable::SetData(tmt_soe_test *pChData)
{
	ASSERT(pChData);
	m_pSoeTest = pChData;

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
		setItem(nRows, 0, item); 

		//选择
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));
		for (int col  =  0;  col  <  SOEColunmCount;  col++)
		{
			if(col == STT_SOE_TABLE_COL_Select)
			{
				if (pChData->m_oSoeParas.m_binOut[i].isValid == 1)
				{
					item->setCheckState(Qt::Checked);
				}
				else
				{
					item->setCheckState(Qt::Unchecked);
				}
			}
		}

		setItem(nRows, 1, item); 

		//通道
		CString strChnnel;
		xlang_GetLangStrByFile(strChnnel, "Native_BoutX");
		strChnnel += QString::number(nRows+1);
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));
		item->setText(strChnnel);
		setItem(nRows, 2, item); 


		//初始状态
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);


		setComboxSoeDelegate(nRows,item,pChData);
		

		//m_pComboBox = NewStatType();

		// 		if (pChData->m_oSoeParas.m_binOut[i].otmt_SoeState[0].val == 0)
		// 		{
		// 			
		// 			//m_pComboBox->setCurrentIndex(0);
		// 		}
		// 		else
		// 		{
		// 			m_pComboBox->setCurrentIndex(1);
		// 		}
		// 		
		// 		setCellWidget(nRows, 3, m_pComboBox);


		//connect(m_pComboBox,SIGNAL(currentIndexChanged(int)),pLinedit,SLOT(slot_SetStateChanged(int)));


		//变位前时长	
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setText(QString::number(pChData->m_oSoeParas.m_binOut[i].otmt_SoeState[0].time,'f',1));
		setItem(nRows, 4, item); 

		//闭合时长
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setText(QString::number(pChData->m_oSoeParas.m_binOut[i].otmt_SoeState[1].time,'f',1));
		setItem(nRows, 5, item); 

		//断开时长
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setText(QString::number(pChData->m_oSoeParas.m_binOut[i].otmt_SoeState[2].time,'f',1));
		setItem(nRows, 6, item); 

		//变位次数
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

		item->setText(QString::number(pChData->m_oSoeParas.m_binOut[i].cnt,'f',0));
		setItem(nRows, 7, item); 

		//持续时间
		
		setHoldTimeData(nRows);
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));
		item->setText(QString::number(m_pSoeTest->m_oSoeParas.m_fHoldTime,'f',2));
		setItem(nRows, 8, item); 

	}

	GetMaxHoldTime();

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)),Qt::UniqueConnection);

}

void QSttMacroParaEditViewSoeTable::setComboxSoeDelegate(int row,QTableWidgetItem *pItem,tmt_soe_test *pData)
{
	if (m_pComboBox == NULL)
	{
		m_pComboBox = new CComboBoxSoeDelegate(this);
		setItemDelegateForColumn(3,m_pComboBox);

	}

	//CString strText;

	if (pData->m_oSoeParas.m_binOut[row].otmt_SoeState[0].val == 0)
	{
		//strText =_T("断开");
		pItem->setText(g_sLangTxt_SOE_Break);
	}
	else
	{
		//strText =_T("闭合");
		pItem->setText(g_sLangTxt_SOE_Shutting);
	}

	setItem(row, 3, pItem); 

	
	connect(m_pComboBox,SIGNAL(commitData(QWidget*)),this,SLOT(slot_SoeCountChanged(QWidget*)),Qt::UniqueConnection);


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
		m_pSoeTest->m_oSoeParas.m_binOut[nRow].otmt_SoeState[0].val = 0;
		m_pSoeTest->m_oSoeParas.m_binOut[nRow].otmt_SoeState[1].val = 1;
	}
	else
	{
		m_pSoeTest->m_oSoeParas.m_binOut[nRow].otmt_SoeState[0].val = 1;
		m_pSoeTest->m_oSoeParas.m_binOut[nRow].otmt_SoeState[1].val = 0;
	}

	
}

void QSttMacroParaEditViewSoeTable::UpdateTable(int row,int col)
{
	if (row  <  0)
	{
		return;
	}
	QTableWidgetItem  *pItem  = this->item(row,col);

	if (pItem == NULL)
	{
		return;
	} 


	if(col == STT_SOE_TABLE_COL_Select)
	{
		if (m_pSoeTest->m_oSoeParas.m_binOut[row].isValid == 1)
		{
			pItem->setCheckState(Qt::Checked);
		}
		else
		{
			pItem->setCheckState(Qt::Unchecked);
		}

		return;
	}

	if (col == STT_SOE_TABLE_COL_TimeBinAct)
	{
		pItem->setText(QString::number(m_pSoeTest->m_oSoeParas.m_binOut[row].otmt_SoeState[0].time,'f',1));

	}
	else if (col == STT_SOE_TABLE_COL_TimeBinExAct)
	{
		pItem->setText(QString::number(m_pSoeTest->m_oSoeParas.m_binOut[row].otmt_SoeState[1].time,'f',1));
	}
	else if (col == STT_SOE_TABLE_COL_TimeBoutAct)
	{
		pItem->setText(QString::number(m_pSoeTest->m_oSoeParas.m_binOut[row].otmt_SoeState[2].time,'f',1));
	}
	//判断当前选中的是变位次数
	else if (col == STT_SOE_TABLE_COL_Count)
	{
		pItem->setText(QString::number(m_pSoeTest->m_oSoeParas.m_binOut[row].cnt,'f',0));
	}

	else if (col == STT_SOE_TABLE_COL_HoldTime)
	{
		setHoldTimeData(row);

		pItem->setText(QString::number(m_pSoeTest->m_oSoeParas.m_fHoldTime,'f',2));
	}
	else if (col ==  STT_SOE_TABLE_COL_Stat)
	{
		pItem = this->item(row,STT_SOE_TABLE_COL_HoldTime);
		setHoldTimeData(row);
		pItem->setText(QString::number(m_pSoeTest->m_oSoeParas.m_fHoldTime,'f',2));
	}


	GetMaxHoldTime();
}


void QSttMacroParaEditViewSoeTable::slot_SetStateChanged(int index)
{
	ASSERT(m_pSoeTest);

	QComboBox *pComboBox = (QComboBox *)sender();
	int x = pComboBox->frameGeometry().x();
	int y  = pComboBox->frameGeometry().y();
	QModelIndex nIndex = indexAt(QPoint(x,y));
	int nRow = nIndex.row();

	if (index == 0)
	{
		m_pSoeTest->m_oSoeParas.m_binOut[nRow].otmt_SoeState[0].val = 0;
		m_pSoeTest->m_oSoeParas.m_binOut[nRow].otmt_SoeState[1].val = 1;
	}
	else
	{
		m_pSoeTest->m_oSoeParas.m_binOut[nRow].otmt_SoeState[0].val = 1;
		m_pSoeTest->m_oSoeParas.m_binOut[nRow].otmt_SoeState[1].val = 0;
	}
}


void QSttMacroParaEditViewSoeTable::UpdateText(const QString &strText)
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

void QSttMacroParaEditViewSoeTable::slot_OnCellChanged(int row,int col)
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

	if(col == STT_SOE_TABLE_COL_Select)
	{
		if (pItem->checkState() !=  Qt::Unchecked)
		{
			m_pSoeTest->m_oSoeParas.m_binOut[row].isValid = 1;
		}
		else
		{
			m_pSoeTest->m_oSoeParas.m_binOut[row].isValid = 0;
		}
	}

	if(col == STT_SOE_TABLE_COL_Stat)
	{
		if (str == _T("断开"))
		{
			m_pSoeTest->m_oSoeParas.m_binOut[row].otmt_SoeState[0].val = 0;
		}
		else
		{
			m_pSoeTest->m_oSoeParas.m_binOut[row].otmt_SoeState[0].val = 1;
		}
	}

	if (col == STT_SOE_TABLE_COL_TimeBinAct)
	{
		float nSum = str.toFloat();


		if (nSum < 20)
		{
			nSum = 20;
		}

		if (nSum > m_nTime)
		{
			nSum = m_nTime;
		}

		m_pSoeTest->m_oSoeParas.m_binOut[row].otmt_SoeState[0].time = nSum;
	}
	else if (col == STT_SOE_TABLE_COL_TimeBinExAct)
	{
		float nSum = str.toFloat();

		if (nSum < 20)
		{
			nSum = 20;
		}

		if (nSum > m_nTime)
		{
			nSum = m_nTime;
		}


		m_pSoeTest->m_oSoeParas.m_binOut[row].otmt_SoeState[1].time = nSum;
	}
	else if (col == STT_SOE_TABLE_COL_TimeBoutAct)
	{
		float nSum = str.toFloat();

		if (nSum < 20)
		{
			nSum = 20;
		}

		if (nSum > m_nTime)
		{
			nSum = m_nTime;
		}


		m_pSoeTest->m_oSoeParas.m_binOut[row].otmt_SoeState[2].time = nSum;
	}
	//判断当前选中的是变位次数
	else if (col == STT_SOE_TABLE_COL_Count)
	{
		float nSum = str.toFloat();

		if (nSum < 1)
		{
			nSum = 1;
		}

		if (nSum > m_nCnt)
		{
			nSum = m_nCnt;
		}

		m_pSoeTest->m_oSoeParas.m_binOut[row].cnt = nSum;
	}

	UpdateTable(row,col);
	UpdateTable(row,8);

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);

}

void QSttMacroParaEditViewSoeTable::slot_OnItemDoubleClicked(QTableWidgetItem *pItem)
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

bool QSttMacroParaEditViewSoeTable::eventFilter(QObject *obj, QEvent *event)
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

void QSttMacroParaEditViewSoeTable::mousePressEvent(QMouseEvent * event)
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

void QSttMacroParaEditViewSoeTable::SetSelState_SelectAll()
{
	for (int i=0; i<g_nBinCount; i++)
	{
		int nRows = i;

		for (int col  =  0;  col  <  SOEColunmCount;  col++)
		{
			if(col == STT_SOE_TABLE_COL_Select)
			{
				m_pSoeTest->m_oSoeParas.m_binOut[nRows].isValid = 1;
				UpdateTable(nRows,col);
			}
		}
	}

}

void QSttMacroParaEditViewSoeTable::SetSelState_UnSelectAll()
{

	for (int i=0; i<g_nBinCount; i++)
	{
		int nRows = i;

		for (int col  =  0;  col  <  SOEColunmCount;  col++)
		{
			if(col == STT_SOE_TABLE_COL_Select)
			{
				m_pSoeTest->m_oSoeParas.m_binOut[nRows].isValid = 0;
				UpdateTable(nRows,col);
			}
		}
	}
}

void QSttMacroParaEditViewSoeTable::SetSelState_InitialAll()
{

	for (int i=0; i<g_nBinCount; i++)
	{
		int nRows = i;

		for (int col  =  0;  col  <  SOEColunmCount;  col++)
		{
			if(col == STT_SOE_TABLE_COL_Stat)
			{
				QTableWidgetItem *pItem = new QTableWidgetItem();
				m_pSoeTest->m_oSoeParas.m_binOut[nRows].otmt_SoeState[0].val = 1;
				//m_pSoeTest->m_oSoeParas.m_binOut[nRows].otmt_SoeState[1].val = 0;
				
				pItem->setText(g_sLangTxt_SOE_Shutting);
				
				setItem(nRows, col, pItem); 
			}
		}
	}

}


void QSttMacroParaEditViewSoeTable::SetSelState_UnInitialAll()
{

	for (int i=0; i<g_nBinCount; i++)
	{
		int nRows = i;

		for (int col  =  0;  col  <  SOEColunmCount;  col++)
		{
			if(col == STT_SOE_TABLE_COL_Stat)
			{


				QTableWidgetItem *pItem = new QTableWidgetItem();
				m_pSoeTest->m_oSoeParas.m_binOut[nRows].otmt_SoeState[0].val = 0;
				//m_pSoeTest->m_oSoeParas.m_binOut[nRows].otmt_SoeState[1].val = 1;

				pItem->setText(g_sLangTxt_SOE_Break);

				setItem(nRows, col, pItem); 

// 				m_pComboBox = (QScrollComboBox *)cellWidget(nRows,col);
// 				m_pSoeTest->m_oSoeParas.m_binOut[nRows].otmt_SoeState[0].val = 0;
// 				m_pSoeTest->m_oSoeParas.m_binOut[nRows].otmt_SoeState[1].val = 1;
// 				m_pComboBox->setCurrentIndex(0);

			}
		} 
	}
}



void QSttMacroParaEditViewSoeTable::setHoldTimeData(int nRow)
{
	float a = 0.0f, b = 0.0f, c = 0.0f, ntime = 0.0f;
	a= m_pSoeTest->m_oSoeParas.m_binOut[nRow].otmt_SoeState[0].time;
	b= m_pSoeTest->m_oSoeParas.m_binOut[nRow].otmt_SoeState[1].time;
	c= m_pSoeTest->m_oSoeParas.m_binOut[nRow].otmt_SoeState[2].time;

	int cnt = m_pSoeTest->m_oSoeParas.m_binOut[nRow].cnt;

	if (m_pSoeTest->m_oSoeParas.m_binOut[nRow].otmt_SoeState[0].val == 0)
	{
		ntime =(a + (b+c)*(cnt/2) + b*(cnt%2))/1000;
	}
	else
	{
		ntime =(a + (b+c)*(cnt/2) + c*(cnt%2))/1000;
	}
	//ntime =( a+(b+c)*cnt)/1000;

	m_pSoeTest->m_oSoeParas.m_fHoldTime  = ntime;
}

void QSttMacroParaEditViewSoeTable::GetMaxHoldTime()
{
	float fMaxHoldTime = 0 ,fCurrentHoldTime = 0; 
	for (int i=0; i<g_nBinCount; i++)
	{
		int nRows = i;

		for (int col  =  0;  col  <  SOEColunmCount;  col++)
		{	
			if(col == STT_SOE_TABLE_COL_Select)
			{
				if (m_pSoeTest->m_oSoeParas.m_binOut[nRows].isValid == 1)
				{
					 fCurrentHoldTime = item(nRows,STT_SOE_TABLE_COL_HoldTime)->text().toFloat();

					 if(fCurrentHoldTime > fMaxHoldTime)
					 {
						 fMaxHoldTime = fCurrentHoldTime;
					 }
				}
			}
		}
	}
	
	m_pSoeTest->m_oSoeParas.m_fHoldTime = fMaxHoldTime + 1; 
}




/////////////////////////////////////////////////////////////////////////

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

	QScrollComboBox *pComboBox = new QScrollComboBox(parent);

#ifdef _PSX_QT_LINUX_//linux下需要特殊处理下
	pComboBox->SetIgnoreFirstHidePopup(true);
#endif
	return pComboBox;


}


void CComboBoxSoeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString strItem = index.model()->data(index,Qt::EditRole).toString();
	QStringList strItemList;

// 	CString strText,strTemp;
// 	strText = _T("闭合");
// 	strTemp =_T("断开");
	strItemList<<g_sLangTxt_SOE_Break<<g_sLangTxt_SOE_Shutting;


	QScrollComboBox *pComboBox = qobject_cast<QScrollComboBox *>(editor);
	pComboBox->clear();
	int id = 0;
	for (int i=0; i<strItemList.size(); i++)
	{
		QString strValue = strItemList.at(i);
		if (strValue == strItem)
		{
			id = i;
		}
		pComboBox->addItem(strValue);
	}
	pComboBox->setCurrentIndex(id);

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
	//	QTableWidgetItem* pCurItem = GetCurrItem(index);
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




