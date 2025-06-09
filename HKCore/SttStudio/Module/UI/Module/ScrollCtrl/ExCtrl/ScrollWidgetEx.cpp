#include "ScrollWidgetEx.h"

#include <QPen>
#include <QPainter>

QScrollWidgetEx::QScrollWidgetEx(QWidget *parent) : QWidget(parent)
{

}

QScrollWidgetEx::~QScrollWidgetEx()
{

}

void QScrollWidgetEx::SetPen(QPainter* painter, QElementColor clr, long nBorder)
{
	QPen pen;
	pen.setColor(clr);
	pen.setWidth(nBorder);
	painter->setPen(pen);
}

void QScrollWidgetEx::DrawLine(QPainter* painter, QPoint ptBegin, QPoint ptEnd, QElementColor clr, long nBorder)
{
	SetPen(painter, clr, nBorder);
	painter->drawLine(ptBegin, ptEnd);
}

void QScrollWidgetEx::DrawRect(QPainter* painter, QPoint ptLeftTop, QPoint ptRightBottom, QElementColor clr, long nBorder)
{
	SetPen(painter, clr, nBorder);
	painter->drawRect(ptLeftTop.x(), ptLeftTop.y(), ptRightBottom.x(), ptRightBottom.y());
}

void QScrollWidgetEx::DrawRect(QPainter* painter, QRect rc, QElementColor clr, long nBorder)
{
	SetPen(painter, clr, nBorder);
	painter->drawRect(rc);
}

void QScrollWidgetEx::DrawCircle(QPainter* painter, QPoint ptCenter, long nRadius, QElementColor clr, long nBorder)
{
	SetPen(painter, clr, nBorder);
	painter->drawEllipse(ptCenter, nRadius, nRadius);
}

void QScrollWidgetEx::DrawText(QPainter* painter, QRect rc, const CString& strText)
{
	painter->drawText(rc, Qt::AlignHCenter | Qt::AlignVCenter, strText);
}