#include "QSttCustomArrowLine.h"
#include "qmath.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

#define CursorOffset 25
#define CheckBoundWidth		 20		//��Ӧ�ķ�Χ���

QSttCustomArrowLine::QSttCustomArrowLine(const QPointF& startPoint, const QPointF& endPoint, QGraphicsItem* parent)
: QObject(), QGraphicsItem(parent), m_startPoint(startPoint), m_endPoint(endPoint),
m_lineColor(Qt::black), m_arrowSize(10), m_arrowAngle(_PI / 6), m_hoverColor(Qt::red), m_isHovered(false)
{
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setAcceptHoverEvents(true); // �����������¼�

	// ����б����
	calculateLineBoundingBox(m_startPoint,m_endPoint,CheckBoundWidth);//2024-9-20 wuxinyi QSttCustomArrowLine��Ӧ�ľ��Σ����������ε��µķ�Χ����
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

QPainterPath QSttCustomArrowLine::shape() const
{
	// ����һ��QPainterPath������߶�
	QPainterPath path;
	QLineF line(m_startPoint, m_endPoint);
	path.moveTo(line.p1());
	path.lineTo(line.p2());

	// ʹ��QPainterPathStroker����չ·���Ŀ�ȣ���������ͣ���ķ�Χ
	QPainterPathStroker stroker;
	stroker.setWidth(CheckBoundWidth);  // ���ü�ⷶΧ�Ŀ��
	QPainterPath widePath = stroker.createStroke(path);

	return widePath;  // ������չ���·������Ϊ
}

void QSttCustomArrowLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	// �����ͷ�ĽǶ��Լ���������
	qreal angle = ::acos((m_endPoint.x() - m_startPoint.x()) / QLineF(m_startPoint, m_endPoint).length());
	if (m_endPoint.y() >= m_startPoint.y())
	{
		angle = (_PI  * 2) - angle;
	}
	QPointF arrowP1 = m_endPoint + QPointF(sin(angle - _PI  / 3) * m_arrowSize, cos(angle - _PI  / 3) * m_arrowSize);
	QPointF arrowP2 = m_endPoint + QPointF(sin(angle - _PI  + _PI  / 3) * m_arrowSize, cos(angle - _PI  + _PI  / 3) * m_arrowSize);

	// ������ͷ·��
	QPainterPath arrowPath;
	arrowPath.moveTo(m_startPoint);
	arrowPath.lineTo(m_endPoint);
	arrowPath.lineTo(arrowP1);
	arrowPath.lineTo(m_endPoint);
	arrowPath.lineTo(arrowP2);
	arrowPath.lineTo(m_endPoint);

	// ��������������ɫ
	QColor lineColor = (m_isHovered) ? m_hoverColor : m_lineColor;

	// ���Ƽ�ͷ
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
// 	m_isHovered = true;
// 	update();// �����ػ��¼����Ը��¼�ͷ��ɫ����״
// 
// 	QCursor cursor(Qt::SplitVCursor);
// 	if (scene() && scene()->views().size() > 0) 
// 	{
// 		scene()->views().first()->setCursor(cursor);  
// 	}	
// 	QGraphicsItem::hoverEnterEvent(event);
	QPointF mousePos = mapToScene(event->pos());  // ��ȡ��굱ǰλ��

	// ����������߶εľ�����һ����Χ�ڣ���Ϊ�����ͣ�ڸ��߶���
	if (m_boundingPolygon.containsPoint(mousePos, Qt::OddEvenFill))
	{
		m_isHovered = true;  // ������ͣ��־
		update();  // �����ػ�
	QCursor cursor(Qt::SplitVCursor);
	if (scene() && scene()->views().size() > 0) 
	{
		scene()->views().first()->setCursor(cursor);  
	}	
	}
	else
	{
		m_isHovered = false;
		update();
	}
	QGraphicsItem::hoverEnterEvent(event);

}

void QSttCustomArrowLine::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	m_isHovered = false;
	update();
	// �ָ������������ʽ
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
	update(); // ����ͼ��������ػ�
}

void QSttCustomArrowLine::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
	QGraphicsItem::mousePressEvent(event);  // ���ȵ��û����mousePressEvent������ȷ����������Ĭ����Ϊ

	emit arrowClicked();  // ������ΪarrowClicked���ź�	
	
	QCursor cursor(Qt::SplitVCursor);// �������ָ����״
	if (scene() && scene()->views().size() > 0) 
	{
		scene()->views().first()->setCursor(cursor);  // �ڴ˼��賡��ֻ��һ����ͼ������ж����ͼ����Ҫ����ʵ��������ö�Ӧ����ͼ�����ָ����״
	}
}

bool QSttCustomArrowLine::bClicked( const QPointF& point )
{
	//2024-9-20 wuxinyi �޸ĵ�QSttCustomArrowLineΪб��ʱ�������Χ�����µ����׼ȷ
// 	QRectF rc = boundingRect();
// 	if(point.x() >= rc.left() 
// 		&& point.x() <= rc.right()
// 		&& (point.y() >= (rc.top() - CursorOffset)) 
// 		&& (point.y() <= (rc.bottom() + CursorOffset)))
// 	{
// 		emit arrowClicked();
// 		m_isHovered = true;
// 		update();
// 		return true;
// 	}
// 
// 	m_isHovered = false;
// 	update();
	
	if (m_boundingPolygon.containsPoint(point, Qt::OddEvenFill))
	{
		emit arrowClicked();
		m_isHovered = true;  // ������ͣ��־
		update();  // �����ػ�
		return true;	
	}

	m_isHovered = false;
	update();
	return false;
}

void QSttCustomArrowLine::visualizeBoundingBox()
{
	// ��ȡ��ǰ����
	QGraphicsScene* scene = this->scene();  // ��ͼ�����ȡ����ָ��
	if (!scene) return;

	// ����һ�� QGraphicsPolygonItem ����ʾ��Χ
	QGraphicsPolygonItem* polygonItem = new QGraphicsPolygonItem(m_boundingPolygon);

	// ���ÿ��ӻ�����ʽ
	QPen pen(Qt::DashLine);  // ʹ�����߱߿�
	pen.setColor(Qt::red);   // ����Ϊ��ɫ
	polygonItem->setPen(pen);

	QBrush brush(Qt::transparent);  // �������Ϊ͸��
	polygonItem->setBrush(brush);

	// ���������ӵ�������
	scene->addItem(polygonItem);
}

void QSttCustomArrowLine::calculateLineBoundingBox(const QPointF& startPoint, const QPointF& endPoint, qreal width)
{
	// ���ֲ�����ӳ�䵽��������
	QPointF startScenePos = mapToScene(startPoint);
	QPointF endScenePos = mapToScene(endPoint);

	// �ڳ�������ϵ�м������
	qreal dx = endScenePos.x() - startScenePos.x();
	qreal dy = endScenePos.y() - startScenePos.y();
	qreal length = sqrt(dx * dx + dy * dy);
	qreal nx = -dy / length;
	qreal ny = dx / length;

	// ����б���εĶ���
	QPointF A1 = startScenePos + QPointF(nx * width, ny * width);
	QPointF A2 = startScenePos - QPointF(nx * width, ny * width);
	QPointF B1 = endScenePos + QPointF(nx * width, ny * width);
	QPointF B2 = endScenePos - QPointF(nx * width, ny * width);

	// ����б���β������� m_boundingPolygon ��
	m_boundingPolygon.clear();
	m_boundingPolygon << A1 << B1 << B2 << A2;
}
