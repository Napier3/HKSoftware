#ifndef QSTTCUSTOMARROWLINE_H
#define QSTTCUSTOMARROWLINE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPointF>
#include "../../../../../../Module/API/MathApi.h"


class QSttCustomArrowLine : public QObject, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)
public:
	 QSttCustomArrowLine(const QPointF& startPoint, const QPointF& endPoint, QGraphicsItem* parent = NULL);
	 // startPoint: 起点坐标
	 // endPoint: 终点坐标
	 // parent: 父图形项，默认为 NULL
	virtual ~QSttCustomArrowLine() ;

	virtual QRectF boundingRect() const ;// 返回图形项的边界矩形
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) ; // 绘制图形

	void setStartPoint(const QPointF& startPoint); // 设置起点坐标
	void setEndPoint(const QPointF& endPoint);   // 设置终点坐标
	void setLineColor(const QColor& color); // 设置线条颜色
	void setArrowSize(qreal size); // 设置箭头大小
	void setArrowAngle(qreal angle); // 设置箭头角度
	void setHoverColor(const QColor& color); // 设置鼠标悬停时的线条颜色
	
	QPointF getStartPoint() const; 
	QPointF getEndPoint() const;  
	QColor getLineColor() const;   
	qreal getArrowSize() const;  
	qreal getArrowAngle() const;
	QColor getHoverColor() const; // 获取鼠标悬停时的线条颜色

	void setHovered(bool hovered); // 设置是否悬停
	void setArrowLineGeometry(const QPointF& startPoint, const QPointF& endPointt);//设置位置
	
	bool bClicked(const QPointF& point);//chenling 20240104 在箭头线的附近就能emit arrowClicked 

signals:
	void itemSelected();
	void itemDeselected();
	void arrowClicked();


protected:
	virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value) ; // 重写父类的 itemChange() 函数，用于处理图形项的属性变化

	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) ;
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) ;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) ;

private:
	QPointF m_startPoint;
	QPointF m_endPoint;
	QColor m_lineColor;  // 线条颜色
	qreal m_arrowSize; // 箭头大小
	qreal m_arrowAngle; // 箭头角度

	QColor m_hoverColor; // 鼠标悬停时的线条颜色
	bool m_isHovered; // 是否鼠标悬停
};

#endif