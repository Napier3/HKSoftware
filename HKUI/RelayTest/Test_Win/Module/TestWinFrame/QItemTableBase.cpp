#include "QItemTableBase.h"
#include <QHeaderView>
#include <QList>
#include <QDebug>
#include <QTextCodec>
#include <QMouseEvent>

//2021-9-16  lijunqing
#include "../SttXTestMngrBaseApp.h"

#include "../../../../AutoTest/Module/XLanguageResourceAts.h"
// #include "../ReportView/XLangResource_PowerTestWin.h"
#include "d:\WorkLiJQ\Source\SttStudio\Test_Win\Module\TestWinFrame\ReportView\XLangResource_PowerTestWin.h"

QItemTableBase::QItemTableBase(QWidget *parent)
	: QTableWidget(parent)
{
	InitUI();
	m_nCurRow = -1;
	m_pTestMngr = NULL;
	m_nPsuDiffRateTest = 0;
}

QItemTableBase::~QItemTableBase()
{

}
void QItemTableBase::InitUI()
{
	m_TestMenu = NULL;
	m_TestAddAction = NULL;
	m_TestDelAction = NULL;
	m_TestClearAction = NULL;
	m_TestClearResultAction = NULL;
	m_TestClearAllResultAction = NULL;
	m_TestSelectAllAction = NULL;
	m_TestUnSelectAllAction = NULL;

	QHeaderView* pTop = this->horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false);
	QHeaderView* pLeft = this->verticalHeader();
	pLeft->setDefaultSectionSize(25);
	pLeft->setVisible(false);

	this->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	this->setColumnCount(4);

	QFontMetrics fontMetrics = QFontMetrics(font());
	int nLabelWidth1 = fontMetrics.width(/*tr("序号")*/g_sLangTxt_SerNumber) + 20;
	int nLabelWidth2 = 220;
	int nLabelWidth3 = fontMetrics.width(/*tr("选择")*/g_sLangTxt_Select) + 30 ;
	QStringList headers;

	headers<</*tr("序号")*/g_sLangTxt_SerNumber<</*tr("测试项目")*/g_sLangTxt_TestItem<</*tr("选择")*/g_sLangTxt_Select<</*tr("试验结果")*/g_sLangTxt_Native_TestResult;
	this->setHorizontalHeaderLabels(headers);
	this->setColumnWidth(0,nLabelWidth1);
	this->setColumnWidth(1,nLabelWidth2);
	this->setColumnWidth(2,nLabelWidth3);
	this->setColumnWidth(3,330);

	m_TestMenu = new QMenu(this);

	m_TestAddAction = new QAction(/*tr("添加试验")*/g_sLangTxt_Gradient_AddExperiment,this);
	m_TestAddAction->setIcon (QPixmap( "./images/Add.png"));
	m_TestDelAction = new QAction(/*tr("删除试验")*/g_sLangTxt_Delet_Test,this);
	m_TestDelAction->setIcon (QPixmap( "./images/Delete.png"));
	m_TestClearAction = new QAction(/*tr("删除N-1")*/g_sLangTxt_Native_DelN1,this);
	m_TestClearAction->setIcon (QPixmap( "./images/clearAll.png"));
	m_TestClearResultAction = new QAction(/*tr("清除结果")*/g_sLangTxt_Clear_Results,this);
	m_TestClearResultAction->setIcon(QPixmap( "./images/standardbutton-delete.png"));
	m_TestClearAllResultAction = new QAction(/*tr("清除所有")*/g_sLangTxt_Clear_All,this);
	m_TestClearAllResultAction->setIcon(QPixmap( "./images/standardbutton-clear.png"));
	m_TestSelectAllAction = new QAction(/*tr("全选")*/g_sLangTxt_SelAll,this);
	m_TestUnSelectAllAction = new QAction(/*tr("全不选")*/g_sLangTxt_SelNone,this);
	m_TestMenu->addAction(m_TestAddAction);
	m_TestMenu->addAction(m_TestDelAction);
	m_TestMenu->addAction(m_TestClearAction);
	m_TestMenu->addAction(m_TestClearResultAction);
	m_TestMenu->addAction(m_TestClearAllResultAction);
	m_TestMenu->addAction(m_TestSelectAllAction);
	m_TestMenu->addAction(m_TestUnSelectAllAction);

	connect(this, SIGNAL(cellClicked ( int , int  )), this, SLOT(slot_Table_cellClicked ( int , int  )));
	connect(m_TestAddAction, SIGNAL(triggered()), this, SLOT(slot_ActionTestAddAfterClicked()));
	connect(m_TestDelAction, SIGNAL(triggered()), this, SLOT(slot_ActionTestDeleteCurrClicked()));
	connect(m_TestClearAction, SIGNAL(triggered()), this, SLOT(slot_ActionTestDelete_N_1_Clicked()));
	connect(m_TestClearResultAction, SIGNAL(triggered()), this, SLOT(slot_ActionTestClearResultClicked()));
	connect(m_TestClearAllResultAction, SIGNAL(triggered()), this, SLOT(slot_ActionTestClearAllResultClicked()));
	connect(m_TestSelectAllAction, SIGNAL(triggered()), this, SLOT(slot_ActionTestSelectAllClicked()));
	connect(m_TestUnSelectAllAction, SIGNAL(triggered()), this, SLOT(slot_ActionTestUnselectAllClicked()));
}

void QItemTableBase::SetData( TMT_PARAS_MNGR* pTestMngr )
{
	ASSERT(pTestMngr != NULL);

	m_pTestMngr = pTestMngr;
	InitData();
}

void QItemTableBase::InitData()
{
	QFontMetrics fontMetrics = QFontMetrics(this->font());

	int nRowHeight = fontMetrics.height()+10;
	setRowCount(0);

	if(m_pTestMngr == NULL)
	{
		return;
	}

	for(int i = 0;i < m_pTestMngr->m_nCount; i++)
	{
		insertRow(i);
		QTableWidgetItem* pitem = new QTableWidgetItem(QString::number(i+1));
		pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		setItem(i,0,pitem);

		CString strName = stt_get_test_item_name(m_pTestMngr->m_pParasBuffer[i]);
		if (strName.IsEmpty())
		{
			strName = QString(/*tr("试验")*/g_sLangTxt_SelNone)+ QString::number(i+1);
		}
		pitem = new QTableWidgetItem(strName);
		pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		setItem(i,1,pitem);

		pitem = new QTableWidgetItem();
		if(m_pTestMngr->m_pParasBuffer[i]->m_nSelected)
		{
			pitem->setCheckState(Qt::Checked);
			pitem->setIcon (QPixmap( "./images/circle_red.png"));
		}
		else{
			pitem->setCheckState(Qt::Unchecked);
			pitem->setIcon (QPixmap( "./images/circle_white.png"));
		}
		setItem(i,2,pitem);

		pitem = new QTableWidgetItem();
		setItem(i,3,pitem);
		if (m_pTestMngr->m_pParasBuffer[i]->m_nTestState == 0)
		{
			pitem->setText("");
			pitem->setIcon (QPixmap( ""));
		}
		else
		{
			UpdateItemResult(i);
		}
		setRowHeight(i,nRowHeight);
	}


	m_nPsuDiffRateTest = 0;
}

void QItemTableBase::UpdateItem( int nIndex )
{
	if(nIndex < 0 || nIndex > m_pTestMngr->m_nCount - 1)
		return;

	QTableWidgetItem* pitem;

	CString strName = stt_get_test_item_name(m_pTestMngr->m_pParasBuffer[nIndex]);
	if (strName.isEmpty())
	{
		strName = QString(/*tr("试验")*/g_sLangTxt_Experiment)+ QString::number(nIndex+1);
	}
	pitem = item(nIndex,1);
	pitem->setText(strName);

	pitem = item(nIndex,2);
	if(m_pTestMngr->m_pParasBuffer[nIndex]->m_nSelected)
	{
		pitem->setCheckState(Qt::Checked);
		pitem->setIcon (QPixmap( "./images/circle_red.png"));
	}
	else
	{
		pitem->setCheckState(Qt::Unchecked);
		pitem->setIcon (QPixmap( "./images/circle_white.png"));
	}
}

PTMT_PARAS_HEAD QItemTableBase::GetCurrentItem()
{
	if(m_pTestMngr == NULL)
	{
		return NULL;
	}
	
	if(m_nCurRow < 0 || m_nCurRow > m_pTestMngr->m_nCount - 1)
	{
		return NULL;
	}

	return m_pTestMngr->m_pParasBuffer[m_nCurRow];
}

void QItemTableBase::UpdateItemResult( int nIndex )
{
	if(nIndex < 0 || nIndex > m_pTestMngr->m_nCount - 1)
		return;

	//2021-9-16  lijunqing 更新绘图状态 放在这里，是方便统一调用
	g_theSttXTestMngrBaseApp->FinishTestPoint(nIndex);

	QTableWidgetItem* pitem = this->item(nIndex,3);
	if(!pitem)
	{
		return;
	}

	CString strResult;
	bool bResult;
	strResult = GetTestItemResultText(m_pTestMngr->m_pParasBuffer[nIndex]);
	bResult = GetTestItemResultJudge(m_pTestMngr->m_pParasBuffer[nIndex]);
/*
	if (strResult.IsEmpty())
		return;
*/
	if (bResult == true)
	{
		pitem->setIcon(QIcon( "./images/check.png"));
	}
	else
	{
		pitem->setIcon(QIcon( "./images/cross.png"));
	}

	pitem->setText(strResult);

	emit sig_Table_cellClicked(nIndex);
}


bool QItemTableBase::GetTestItemResultJudge( PTMT_PARAS_HEAD pParas )
{
	bool bResult;

	if (pParas->m_nTestState == 1)
	{
		bResult = true;
	}
	else if (pParas->m_nTestState == 2)
	{
		bResult = false;
	}

	return bResult;
}

void QItemTableBase::UpdateCurrItemResult()
{
	UpdateItemResult(m_nCurRow);
}

void QItemTableBase::SetCurrentRow( int nRow )
{
	if(nRow <0 || nRow >= rowCount())
	{
		return;
	}

	setCurrentCell(nRow,0);

	m_nCurRow = nRow;
	emit sig_Table_cellClicked(nRow);
}

void QItemTableBase::slot_Table_cellClicked( int row, int column )
{
	if (row < 0)
	{
		return;
	}

	setCurrentCell(row,column);

	m_nCurRow = row;

	if (column == 2)
	{
		QTableWidgetItem *p2 = this->item(row, 2);
		if (p2->checkState() == Qt::Checked)
		{
			p2->setIcon (QPixmap( "./images/circle_red.png"));
			m_pTestMngr->m_pParasBuffer[row]->m_nSelected = true;
		}
		else
		{
			p2->setIcon (QPixmap( "./images/circle_white.png"));
			m_pTestMngr->m_pParasBuffer[row]->m_nSelected = false;
		}
		PTMT_PARAS_HEAD p = m_pTestMngr->m_pParasBuffer[row];
		emit sig_TableChooseChanged(p);
	}
	emit sig_Table_cellClicked(row);
}

void QItemTableBase::slot_customContextMenuRequested( QPoint &pos )
{
	m_TestMenu->exec(QCursor::pos());
}

void QItemTableBase::slot_ActionTestAddBeforeClicked()
{
	emit sig_AddItemBF();
}

void QItemTableBase::slot_ActionTestAddAfterClicked()
{
	emit sig_AddItemAF();
}

void QItemTableBase::slot_ActionTestDeleteCurrClicked()
{
	emit sig_DeleteCurr();
}

void QItemTableBase::slot_ActionTestDelete_N_1_Clicked()
{	
	emit sig_Delete_N_1();
}

void QItemTableBase::slot_ActionTestClearResultClicked()
{
	emit sig_ClearCurrResult();
}

void QItemTableBase::slot_ActionTestClearAllResultClicked()
{
	emit sig_ClearAllResult();
}

void QItemTableBase::slot_ActionTestSelectAllClicked()
{
	emit sig_SelectAll();
}

void QItemTableBase::slot_ActionTestUnselectAllClicked()
{
	emit sig_UnselectAll();
}

void QItemTableBase::keyPressEvent( QKeyEvent *event )
{
	int key = event->key();
	if (key == Qt::Key_Enter||key == Qt::Key_Return)
	{
	}

	else if ((key == Qt::Key_Up)||(key == Qt::Key_Down))
	{
		QTableWidget::keyPressEvent(event);
		int CurRow = currentRow();
		int CurCol = currentColumn();
		slot_Table_cellClicked(CurRow,CurCol);
	}
}

void QItemTableBase::mousePressEvent( QMouseEvent *event )
{
	if (event->button()==Qt::RightButton)
	{
		QTableWidget::mousePressEvent(event);
		slot_Table_cellClicked(this->currentRow(),0);

		QPoint point = event->pos();
		QTableWidgetItem* pItem = itemAt(point);

		if(pItem)
		{
			m_TestMenu->exec(QCursor::pos());
		}
	}
	else if (event->button()==Qt::LeftButton)
	{
		QTableWidget::mousePressEvent(event);
	}
}

void QItemTableBase::ClearItemResult( int nIndex )
{
	QTableWidgetItem* pitem = this->item(nIndex,3);
	if(!pitem)
	{
		return;
	}

	pitem->setText("");
	pitem->setIcon(QPixmap(""));
	emit sig_Table_cellClicked(m_nCurRow);
}

void QItemTableBase::ClearCurrItemResult()
{
	ClearItemResult(m_nCurRow);
}


