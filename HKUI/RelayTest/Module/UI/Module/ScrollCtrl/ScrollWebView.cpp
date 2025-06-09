#include "ScrollWebView.h"

#ifdef QT_USE_WEBKIT
#include <QWebFrame>
#else
#endif

#ifdef QT_USE_WEBKIT
QScrollWebView::QScrollWebView(QWidget* pParent) : QWebView(pParent)
#else
QScrollWebView::QScrollWebView(QWidget* pParent) : QWidget(pParent)
#endif
{
	m_oAttri.m_tagSliderDir = VERI;
	m_oAttri.m_bIsMoving = false;
	m_oAttri.m_bIsPressed = false;
	m_oAttri.m_nScrollVal = 0;
	m_oAttri.m_nPreOffset = 0;
	m_oAttri.m_nCellIndex = 0;
	m_oAttri.m_nPreValSaved = 0;
}

QScrollWebView::~QScrollWebView()
{

}

void QScrollWebView::mousePressEvent(QMouseEvent *ev)
{
#ifdef QT_USE_WEBKIT
    QRect rcScroll = page()->mainFrame()->scrollBarGeometry(Qt::Vertical);
    m_oAttri.m_oPressedAxis = ev->pos();
    if(m_oAttri.m_oPressedAxis.x() < rcScroll.x())
    {
        m_oAttri.m_nScrollVal = page()->mainFrame()->scrollBarValue(Qt::Vertical);;
        m_oAttri.m_nPreOffset = 0;
        m_oAttri.m_bIsPressed = true;
    }
    QWebView::mousePressEvent( ev );
#else
    QWidget::mousePressEvent(ev);
#endif
}


void QScrollWebView::mouseMoveEvent(QMouseEvent *ev)
{
#ifdef QT_USE_WEBKIT
    if (!m_oAttri.m_bIsPressed)
	{
		// 未经过按下事件，不应到这里来
		QWebView::mouseMoveEvent( ev );
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
	nMax = page()->mainFrame()->scrollBarMaximum(Qt::Vertical);


	if ( m_oAttri.m_nPreOffset != nOffset )
	{
		int  curScrollBarVal = m_oAttri.m_nScrollVal-nOffset;
		if ( curScrollBarVal < 0 )
		{
			curScrollBarVal = 0;
		}
		else if ( curScrollBarVal > nMax )
		{
			curScrollBarVal = page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
		}
		page()->mainFrame()->setScrollBarValue(Qt::Vertical, curScrollBarVal);
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
#else
#endif
}

void QScrollWebView::mouseReleaseEvent(QMouseEvent *ev)
{
#ifdef QT_USE_WEBKIT
    if ( m_oAttri.m_bIsMoving == true )
	{
		m_oAttri.m_oPressedAxis = QPoint(0, 0);
		m_oAttri.m_nPreOffset = 0;
		m_oAttri.m_bIsMoving = false;
		m_oAttri.m_bIsPressed = false;
		return;
	}
	QWebView::mouseReleaseEvent( ev );
#else
#endif
}
