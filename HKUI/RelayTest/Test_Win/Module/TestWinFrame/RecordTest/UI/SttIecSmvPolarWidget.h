#ifndef QSttIecSmvPolarWidget_H
#define QSttIecSmvPolarWidget_H

#include <QWidget>

#include "../../../../Module/Axis/PolarAxis.h"

//////////////////////////////////////////////////////////////////////////
class QSttIecSmvPolarWidget : public QWidget
{//矢量图绘图
public:
	QSttIecSmvPolarWidget(QWidget* parent=0);

	virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *);

	CPolarAxis m_oPolarAxis;
	POLAR_VECTORS_MNGR *m_pArrVectors;

	void DrawTheVectors(POLAR_VECTORS_MNGR *pArrVectors);
};

#endif

