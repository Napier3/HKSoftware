#ifndef SCROLLWIDGETEX_H
#define SCROLLWIDGETEX_H

#include "ScrollExElement.h"

#include <QWidget>

class QScrollWidgetEx : public QWidget
{
private:
	enum QElementColor
	{
		CLR_BLAKE = 0,
		CLR_WHITE = 0xffffff
	};

public:
	QScrollWidgetEx(QWidget *parent=0);
	virtual ~QScrollWidgetEx();

public:
	virtual void SetPen(QPainter* painter, QElementColor clr, long nBorder);
	virtual void DrawLine(QPainter* painter, QPoint ptBegin, QPoint ptEnd, QElementColor clr = CLR_BLAKE, long nBorder = 1);
	virtual void DrawRect(QPainter* painter, QPoint ptLeftTop, QPoint ptRightBottom, QElementColor clr = CLR_BLAKE, long nBorder = 1);
	virtual void DrawRect(QPainter* painter, QRect rc, QElementColor clr = CLR_BLAKE, long nBorder = 1);
	virtual void DrawCircle(QPainter* painter, QPoint ptCenter, long nRadius, QElementColor clr = CLR_BLAKE, long nBorder = 1);
	virtual void DrawText(QPainter* painter, QRect rc, const CString& strText);
};




#endif//!SCROLLWIDGETEX_H