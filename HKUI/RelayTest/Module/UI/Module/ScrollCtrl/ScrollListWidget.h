#ifndef ScrollListWidget_H
#define ScrollListWidget_H

#include "ScrollDef.h"
#include <QListWidget>

class QScrollListWidget : public QListWidget
{
	Q_OBJECT

public:
	explicit QScrollListWidget(QWidget* pParent = NULL);
	virtual ~QScrollListWidget();
protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);

private:
	tagSliderAttri m_oAttri;
};

#endif//!ScrollListWidget_H
