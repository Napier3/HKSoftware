#include "ScrollTextEdit.h"
#ifndef _PSX_QT_LINUX_
#include <QApplication>
#include <QClipboard>
#include "../../../../../Module\XLanguage\XLanguageResource.h"

#endif

QScrollTextEdit::QScrollTextEdit(QWidget* pParent) : QTextEdit(pParent)
{
#ifdef _PSX_QT_LINUX_
	m_oAttri.m_pCurScrollBar = this->verticalScrollBar();
	m_oAttri.m_tagSliderDir = DEFAULT;
	m_oAttri.m_bIsMoving = false;
	m_oAttri.m_bIsPressed = false;
	m_oAttri.m_nScrollVal = 0;
	m_oAttri.m_nPreOffset = 0;
	m_oAttri.m_nCellIndex = 0;
	m_oAttri.m_nPreValSaved = 0;

	SetSliderDir(VERI);
	setTextInteractionFlags(Qt::NoTextInteraction);
#endif

#ifndef _PSX_QT_LINUX_
	CreateLogOptrMenu();
	setContextMenuPolicy (Qt::CustomContextMenu);

	connect(this, SIGNAL(customContextMenuRequested ( const QPoint & )), this, SLOT(slot_LogShowMenu(QPoint)));
#endif
}

QScrollTextEdit::~QScrollTextEdit()
{

}

#ifdef _PSX_QT_LINUX_
void QScrollTextEdit::SetSliderDir(tagSliderDir tagDir)
{
	m_oAttri.m_tagSliderDir = tagDir;
	// 区分横向或纵向，不同时支持横向纵向
	if (m_oAttri.m_tagSliderDir == VERI)
	{
		m_oAttri.m_pCurScrollBar = this->verticalScrollBar();
	}
	else
	{
		m_oAttri.m_pCurScrollBar = this->horizontalScrollBar();
	}
}

void QScrollTextEdit::mousePressEvent(QMouseEvent *ev)
{
	m_oAttri.m_nScrollVal = m_oAttri.m_pCurScrollBar->value();
	m_oAttri.m_oPressedAxis = ev->pos();
	m_oAttri.m_nPreOffset = 0;
	m_oAttri.m_bIsPressed = true;
	QAbstractScrollArea::mousePressEvent( ev );
}


void QScrollTextEdit::mouseMoveEvent(QMouseEvent *ev)
{
	if (!m_oAttri.m_bIsPressed)
	{
		// 未经过按下事件，不应到这里来
		QAbstractScrollArea::mouseMoveEvent( ev );
		return;
	}

	int nCurXPos = ev->x(), nCurYPos = ev->y();
	int nMax = 0, nOffset = 0;
	if (m_oAttri.m_tagSliderDir == VERI)
	{
		nOffset = nCurYPos - m_oAttri.m_oPressedAxis.y();
	}
	else
	{
		nOffset = nCurXPos - m_oAttri.m_oPressedAxis.x();
	}
	nMax = m_oAttri.m_pCurScrollBar->maximum();


	if ( m_oAttri.m_nPreOffset != nOffset )
	{
		int  curScrollBarVal = m_oAttri.m_nScrollVal-nOffset;
		if ( curScrollBarVal < 0 )
		{
			curScrollBarVal = 0;
		}
		else if ( curScrollBarVal > nMax )
		{
			curScrollBarVal = m_oAttri.m_pCurScrollBar->maximum();
		}
		m_oAttri.m_pCurScrollBar->setValue(curScrollBarVal);
		m_oAttri.m_nPreOffset = nOffset;
	}

	//滑动超过10个像素才视为已经滑动
	int tmpDiffPosX = nCurXPos-m_oAttri.m_oPressedAxis.x();
	int tmpDiffPosY = nCurYPos-m_oAttri.m_oPressedAxis.y();
	tmpDiffPosX = (tmpDiffPosX>0) ? tmpDiffPosX : (0-tmpDiffPosX);
	tmpDiffPosY = (tmpDiffPosY>0) ? tmpDiffPosY : (0-tmpDiffPosY);
	if ( tmpDiffPosX > 10 || tmpDiffPosY > 10 )
	{
		m_oAttri.m_bIsMoving = true;
	}
}

void QScrollTextEdit::mouseReleaseEvent(QMouseEvent *ev)
{
	if ( m_oAttri.m_bIsMoving == true )
	{
		m_oAttri.m_oPressedAxis = QPoint(0, 0);
		m_oAttri.m_nPreOffset = 0;
		m_oAttri.m_bIsPressed = false;
		m_oAttri.m_bIsMoving = false;
		return;
	}

	QAbstractScrollArea::mouseReleaseEvent( ev );
}
#endif

#ifndef _PSX_QT_LINUX_
void QScrollTextEdit::CreateLogOptrMenu()
{
	m_MenuLogOptr = new QMenu(this);
	m_ActCopyLog = new QAction(/*tr("拷贝")*/g_sLangTxt_Copy,this); //lcq
	m_ActClearLog = new QAction(/*tr("清除")*/g_sLangTxt_Clear,this);  //lcq
	m_MenuLogOptr->addAction(m_ActCopyLog);
	m_MenuLogOptr->addAction(m_ActClearLog);

	connect(m_ActCopyLog,SIGNAL(triggered()),this,SLOT(slot_OnCopyLog()));
	connect(m_ActClearLog,SIGNAL(triggered()),this,SLOT(slot_OnClearLog()));
}

void QScrollTextEdit::slot_OnCopyLog()
{
	QClipboard *clipboard = QApplication::clipboard();
	QString originalText = toPlainText();
	selectAll();
	clipboard->setText(originalText);
}

void QScrollTextEdit::slot_OnClearLog()
{
	setText("");
}

void QScrollTextEdit::slot_LogShowMenu(QPoint pos)
{
	m_ActClearLog->setVisible(true);
	m_ActCopyLog->setVisible(true);

	QString strText;
	strText = toPlainText();

	if (strText.isEmpty())
	{
		m_ActClearLog->setDisabled(true);
		m_ActCopyLog->setDisabled(true);
	}
	else
	{
		m_ActClearLog->setDisabled(false);
		m_ActCopyLog->setDisabled(false);
	}

	m_MenuLogOptr->move(cursor().pos()); 
	m_MenuLogOptr->show(); 
}
#endif