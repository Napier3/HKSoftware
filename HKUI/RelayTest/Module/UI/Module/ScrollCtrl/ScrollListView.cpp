#include "ScrollListView.h"

QScrollListView::QScrollListView(QWidget* pParent) : QListView(pParent)
{
	m_oAttri.m_pCurScrollBar = this->verticalScrollBar();
	m_oAttri.m_tagSliderDir = VERI;
	m_oAttri.m_bIsMoving = false;
	m_oAttri.m_bIsPressed = false;
	m_oAttri.m_nScrollVal = 0;
	m_oAttri.m_nPreOffset = 0;

#ifdef _PSX_QT_LINUX_
	QFont Font = this->font();
	Font.setPixelSize(20);
	setFont(Font);
#endif

	setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

	installEventFilter(this);
}

QScrollListView::~QScrollListView()
{

}

void QScrollListView::mousePressEvent(QMouseEvent *ev)
{
	m_oAttri.m_nScrollVal = m_oAttri.m_pCurScrollBar->value();
	m_oAttri.m_oPressedAxis = ev->pos();
	m_oAttri.m_nPreOffset = 0;
	m_oAttri.m_bIsPressed = true;

	QListView::mousePressEvent( ev );
}


void QScrollListView::mouseMoveEvent(QMouseEvent *ev)
{
	if (!m_oAttri.m_bIsPressed)
	{
		// 未经过按下事件，不应到这里来
		QListView::mouseMoveEvent( ev );
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

void QScrollListView::mouseReleaseEvent(QMouseEvent *ev)
{
	if ( m_oAttri.m_bIsMoving == true )
	{
		m_oAttri.m_oPressedAxis = QPoint(0, 0);
		m_oAttri.m_nPreOffset = 0;
		m_oAttri.m_bIsMoving = false;
		m_oAttri.m_bIsPressed = false;
		return;
	}

	QListView::mouseReleaseEvent( ev );
}
