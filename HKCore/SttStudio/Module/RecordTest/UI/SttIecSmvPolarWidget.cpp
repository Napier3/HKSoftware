#include "SttIecSmvPolarWidget.h"

//////////////////////////////////////////////////////////////////////////
QSttIecSmvPolarWidget::QSttIecSmvPolarWidget(QWidget* parent)
	: QWidget(parent)
{
	m_pArrVectors = NULL;
}


void QSttIecSmvPolarWidget::paintEvent(QPaintEvent *event)
{
	CDC oDC(this);
	oDC.begin(this);
	
	m_oPolarAxis.DrawAxis(&oDC);

	if (m_pArrVectors != NULL)
	{
		m_oPolarAxis.DrawTheVector(&oDC, m_pArrVectors);
	}

	oDC.end();
	updateGeometry();
}

void QSttIecSmvPolarWidget::resizeEvent(QResizeEvent *pReSizeEvent)
{
	QRect rc = 	geometry();
	//QSize sz = pReSizeEvent->size();
	m_oPolarAxis.SetBorder(0, 0, rc.width(), rc.height());
// 	UICreate(this);
// 	CViewAnalyse::OnSizeEx(0, 0, 0);
// 	DrawAnalyse();
}

void QSttIecSmvPolarWidget::DrawTheVectors(POLAR_VECTORS_MNGR *pArrVectors)
{
	m_pArrVectors = pArrVectors;
	update();
}

