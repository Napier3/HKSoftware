#ifndef QSTTCUSTOMARROWLINE_H
#define QSTTCUSTOMARROWLINE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPointF>
#include "../../../../../../Module/API/MathApi.h"
#include <QGraphicsPolygonItem>
#include <QPolygonF>

class QSttCustomArrowLine : public QObject, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)
public:
	 QSttCustomArrowLine(const QPointF& startPoint, const QPointF& endPoint, QGraphicsItem* parent = NULL);
	 // startPoint: �������
	 // endPoint: �յ�����
	 // parent: ��ͼ���Ĭ��Ϊ NULL
	virtual ~QSttCustomArrowLine() ;

	virtual QRectF boundingRect() const ;// ����ͼ����ı߽����
	virtual QPainterPath shape()const;//2024-9-18 wuxinyi ��꽻���������
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) ; // ����ͼ��

	void setStartPoint(const QPointF& startPoint); // �����������
	void setEndPoint(const QPointF& endPoint);   // �����յ�����
	void setLineColor(const QColor& color); // ����������ɫ
	void setArrowSize(qreal size); // ���ü�ͷ��С
	void setArrowAngle(qreal angle); // ���ü�ͷ�Ƕ�
	void setHoverColor(const QColor& color); // ���������ͣʱ��������ɫ
	
	QPointF getStartPoint() const; 
	QPointF getEndPoint() const;  
	QColor getLineColor() const;   
	qreal getArrowSize() const;  
	qreal getArrowAngle() const;
	QColor getHoverColor() const; // ��ȡ�����ͣʱ��������ɫ

	void setHovered(bool hovered); // �����Ƿ���ͣ
	void setArrowLineGeometry(const QPointF& startPoint, const QPointF& endPointt);//����λ��
	
	bool bClicked(const QPointF& point);//chenling 20240104 �ڼ�ͷ�ߵĸ�������emit arrowClicked 
	void visualizeBoundingBox();//���ӻ�m_boundingPolygon
	void calculateLineBoundingBox(const QPointF& startPoint, const QPointF& endPoint, qreal width);

signals:
	void itemSelected();
	void itemDeselected();
	void arrowClicked();


protected:
	virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value) ; // ��д����� itemChange() ���������ڴ���ͼ��������Ա仯

	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) ;
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) ;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) ;

private:
	QPointF m_startPoint;
	QPointF m_endPoint;
	QColor m_lineColor;  // ������ɫ
	qreal m_arrowSize; // ��ͷ��С
	qreal m_arrowAngle; // ��ͷ�Ƕ�

	QColor m_hoverColor; // �����ͣʱ��������ɫ
	bool m_isHovered; // �Ƿ������ͣ

	QPolygonF m_boundingPolygon;  // �����߶η�Χ��Ӧ����
};

#endif