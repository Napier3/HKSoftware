#include "QSttCustomArrowLine.h"
#include "qmath.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

#define CursorOffset 25

QSttCustomArrowLine::QSttCustomArrowLine(const QPointF& startPoint, const QPointF& endPoint, QGraphicsItem* parent)
: QObject(), QGraphicsItem(parent), m_startPoint(startPoint), m_endPoint(endPoint),
m_lineColor(Qt::black), m_arrowSize(10), m_arrowAngle(_PI / 6), m_hoverColor(Qt::red), m_isHovered(false)
{
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setAcceptHoverEvents(true); // 允许接收鼠标事件
}


QSttCustomArrowLine::~QSttCustomArrowLine()
{

}

QRectF QSttCustomArrowLine::boundingRect() const
{
	qreal minX = qMin(m_startPoint.x(), m_endPoint.x());
	qreal minY = qMin(m_startPoint.y(), m_endPoint.y());
	qreal maxX = qMax(m_startPoint.x(), m_endPoint.x());
	qreal maxY = qMax(m_startPoint.y(), m_endPoint.y());

	return QRectF(minX, minY, maxX - minX, maxY - minY);
}

void QSttCustomArrowLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	// 计算箭头的角度以及顶点坐标
	qreal angle = ::acos((m_endPoint.x() - m_startPoint.x()) / QLineF(m_startPoint, m_endPoint).length());
	if (m_endPoint.y() >= m_startPoint.y())
	{
		angle = (_PI  * 2) - angle;
	}
	QPointF arrowP1 = m_endPoint + QPointF(sin(angle - _PI  / 3) * m_arrowSize, cos(angle - _PI  / 3) * m_arrowSize);
	QPointF arrowP2 = m_endPoint + QPointF(sin(angle - _PI  + _PI  / 3) * m_arrowSize, cos(angle - _PI  + _PI  / 3) * m_arrowSize);

	// 创建箭头路径
	QPainterPath arrowPath;
	arrowPath.moveTo(m_startPoint);
	arrowPath.lineTo(m_endPoint);
	arrowPath.lineTo(arrowP1);
	arrowPath.lineTo(m_endPoint);
	arrowPath.lineTo(arrowP2);
	arrowPath.lineTo(m_endPoint);

	// 设置轮廓线条颜色
	QColor lineColor = (m_isHovered) ? m_hoverColor : m_lineColor;

	// 绘制箭头
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setPen(QPen(lineColor, 2));
	painter->setBrush(lineColor);
	painter->drawPath(arrowPath);
}


void QSttCustomArrowLine::setStartPoint(const QPointF& startPoint)
{
	m_startPoint = startPoint;
}

void QSttCustomArrowLine::setEndPoint(const QPointF& endPoint)
{
	m_endPoint = endPoint;
}

void QSttCustomArrowLine::setHoverColor( const QColor& color )
{
	m_hoverColor = color;
}


void QSttCustomArrowLine::setLineColor(const QColor& color)
{
	m_lineColor = color;
}

void QSttCustomArrowLine::setArrowSize(qreal size)
{
	m_arrowSize = size;
}

void QSttCustomArrowLine::setArrowAngle(qreal angle)
{
	m_arrowAngle = angle;
}

QPointF QSttCustomArrowLine::getStartPoint() const
{
	return m_startPoint;
}

QColor QSttCustomArrowLine::getHoverColor() const
{
	return m_hoverColor;
}

QPointF QSttCustomArrowLine::getEndPoint() const
{
	return m_endPoint;
}

QColor QSttCustomArrowLine::getLineColor() const
{
	return m_lineColor;
}

qreal QSttCustomArrowLine::getArrowSize() const
{
	return m_arrowSize;
}

qreal QSttCustomArrowLine::getArrowAngle() const
{
	return m_arrowAngle;
}

QVariant QSttCustomArrowLine::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if (change == QGraphicsItem::ItemSelectedChange) 
	{
		if (value.toBool()) 
		{
			emit itemSelected();
		} 
		else 
		{
			emit itemDeselected();
		}
	}

	return QGraphicsItem::itemChange(change, value);
}


void QSttCustomArrowLine::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	m_isHovered = true;
	update();// 触发重绘事件，以更新箭头颜色和形状

	QCursor cursor(Qt::SplitVCursor);
	if (scene() && scene()->views().size() > 0) 
	{
		scene()->views().first()->setCursor(cursor);  
	}	
	QGraphicsItem::hoverEnterEvent(event);
}

void QSttCustomArrowLine::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	m_isHovered = false;
	update();
	// 恢复正常的鼠标样式
	if (scene() && scene()->views().size() > 0) 
	{
		scene()->views().first()->unsetCursor();
	}

	QGraphicsItem::hoverLeaveEvent(event);
}

void QSttCustomArrowLine::setArrowLineGeometry( const QPointF& startPoint, const QPointF& endPointt )
{
	m_startPoint = startPoint;
	m_endPoint = endPointt;
}

void QSttCustomArrowLine::setHovered( bool hovered )
{
	m_isHovered = hovered;
	update(); // 更新图形项，触发重绘
}

void QSttCustomArrowLine::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
	QGraphicsItem::mousePressEvent(event);  // 首先调用基类的mousePressEvent方法，确保处理基类的默认行为

	emit arrowClicked();  // 发射名为arrowClicked的信号	
	
	QCursor cursor(Qt::SplitVCursor);// 更改鼠标指针形状
	if (scene() && scene()->views().size() > 0) 
	{
		scene()->views().first()->setCursor(cursor);  // 在此假设场景只有一个视图，如果有多个视图，需要根据实际情况设置对应的视图的鼠标指针形状
	}
}

bool QSttCustomArrowLine::bClicked( const QPointF& point )
{
	QRectF rc = boundingRect();
	if(point.x() >= rc.left() 
		&& point.x() <= rc.right()
		&& (point.y() >= (rc.top() - CursorOffset)) 
		&& (point.y() <= (rc.bottom() + CursorOffset)))
	{
		emit arrowClicked();
		m_isHovered = true;
		update();
		return true;
	}

	m_isHovered = false;
	update();

	return false;
}
