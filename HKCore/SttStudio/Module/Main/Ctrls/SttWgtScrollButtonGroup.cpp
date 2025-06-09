#include "SttWgtScrollButtonGroup.h"

#include <QDebug>

QSttWgtScrollButtonGroup::QSttWgtScrollButtonGroup(QWidget* pParent)
{
	setObjectName("SttWgtScrollButtonGroup");
	m_pParent = pParent;
	setParent(pParent);
	m_pBtnGroup = new QSttWgtButtonGroup(this);
	setWidget(m_pBtnGroup);
	SetSliderDir(HORI);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setStyleSheet(QString::fromUtf8("#SttWgtScrollButtonGroup{ border:1px solid white }"));
}

QSttWgtScrollButtonGroup::~QSttWgtScrollButtonGroup()
{
	if(m_pBtnGroup)
	{
		delete m_pBtnGroup;
		m_pBtnGroup = NULL;
	}
}

void QSttWgtScrollButtonGroup::InitUIOwn(CExBaseObject *pSttXuiData)
{
	if(pSttXuiData)
	{
		CSttXuiDataBase* pData = (CSttXuiDataBase*)pSttXuiData;
		if(pData->GetClassID() == MNGRCLASSID_CSTTXUIDATATESTBTNSGROUP)
		{
			m_pBtnGroup->InitTestBtnsGroup(pSttXuiData);
			CSttXuiDataTestBtnsGroup* pData = (CSttXuiDataTestBtnsGroup*)pSttXuiData;
			setGeometry(pData->m_nX, pData->m_nY, pData->m_nCx, pData->m_nCy);
		}
		else
		{
			m_pBtnGroup->InitBtnsGroup(pSttXuiData);
			CSttXuiDataBtnsGroup* pData = (CSttXuiDataBtnsGroup*)pSttXuiData;
			setGeometry(pData->m_nX, pData->m_nY, pData->m_nCx, pData->m_nCy);
		}
	}
}

void QSttWgtScrollButtonGroup::InitUIChildren(CExBaseObject *pSttXuiData)
{
	if(pSttXuiData)
	{
		CSttXuiDataBase* pData = (CSttXuiDataBase*)pSttXuiData;
		if(pData->GetClassID() == MNGRCLASSID_CSTTXUIDATATESTBTNSGROUP)
		{
			m_pBtnGroup->InitTestBtnsGroupChildren(pSttXuiData, this);
		}
		else
		{
			m_pBtnGroup->InitBtnsGroupChildren(pSttXuiData, this);
		}
	}
}

void QSttWgtScrollButtonGroup::mousePressEvent(QMouseEvent *ev, long nX)
{
	m_oAttri.m_nScrollVal = m_oAttri.m_pCurScrollBar->value();
	m_oAttri.m_oPressedAxis = QPoint(nX, ev->y());
	m_oAttri.m_nPreOffset = 0;
	m_oAttri.m_bIsPressed = true;

	QWidget::mousePressEvent( ev );
}

void QSttWgtScrollButtonGroup::mouseMoveEvent(QMouseEvent *ev, long nX)
{
	if (!m_oAttri.m_bIsPressed)
	{
		// 未经过按下事件，不应到这里来
		QWidget::mouseMoveEvent( ev );
		return;
	}

	int nCurXPos = nX, nCurYPos = ev->y();
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

bool QSttWgtScrollButtonGroup::eventFilter(QObject *target, QEvent *event)
{
	if(target != m_pBtnGroup)
	{
		QMouseEvent* e = static_cast<QMouseEvent*>(event);
		QWidget* pWidget = (QWidget*)target;
		QPoint pt = pWidget->pos();
		if(e->type() == QEvent::MouseButtonPress)
		{
			mousePressEvent(e, e->pos().x() +  pt.x());
		}
		else if(e->type() == QEvent::MouseMove)
		{
			mouseMoveEvent(e, e->pos().x() +  pt.x());
		}
		else if(e->type() == QEvent::MouseButtonRelease)
		{
			if(IsMoving())
			{
				mouseReleaseEvent(e);
				return true;
			}
		}
	}
	return false;
}
