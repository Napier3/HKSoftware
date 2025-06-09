#include "ScrollListWidget.h"

QScrollListWidget::QScrollListWidget(QWidget* pParent) : QListWidget(pParent)
{
	m_oAttri.m_pCurScrollBar = this->horizontalScrollBar();
	m_oAttri.m_tagSliderDir = HORI;
	m_oAttri.m_bIsMoving = false;
	m_oAttri.m_bIsPressed = false;
	m_oAttri.m_nScrollVal = 0;
	m_oAttri.m_nPreOffset = 0;
	m_oAttri.m_nCellIndex = 0;
	m_oAttri.m_nPreValSaved = 0;
}

QScrollListWidget::~QScrollListWidget()
{

}

void QScrollListWidget::mousePressEvent(QMouseEvent *ev)
{
	m_oAttri.m_nScrollVal = m_oAttri.m_pCurScrollBar->value();
	m_oAttri.m_oPressedAxis = ev->pos();
	m_oAttri.m_nPreOffset = 0;
	m_oAttri.m_bIsPressed = true;
	QListWidget::mousePressEvent( ev );
}


void QScrollListWidget::mouseMoveEvent(QMouseEvent *ev)
{
	if (!m_oAttri.m_bIsPressed)
	{
		// 未经过按下事件，不应到这里来
		QListWidget::mouseMoveEvent( ev );
		return;
	}

	int nCurXPos = ev->x(), nCurYPos = ev->y();
	int nOffset = nCurXPos - m_oAttri.m_oPressedAxis.x();
	int nMax = m_oAttri.m_pCurScrollBar->maximum();

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

void QScrollListWidget::mouseReleaseEvent(QMouseEvent *ev)
{
	if ( m_oAttri.m_bIsMoving == true )
	{
		setCurrentItem(NULL);
		m_oAttri.m_oPressedAxis = QPoint(0, 0);
		m_oAttri.m_nPreOffset = 0;
		m_oAttri.m_bIsPressed = false;
		m_oAttri.m_bIsMoving = false;
		return;
	}

	QListWidget::mouseReleaseEvent( ev );
}