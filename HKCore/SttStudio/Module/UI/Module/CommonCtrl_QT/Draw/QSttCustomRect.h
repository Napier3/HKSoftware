#ifndef QSTTCUSTOMRECT_H
#define QSTTCUSTOMRECT_H

#include <QPainter>
#include <QGraphicsItem>


class QSttCustomRect : public QObject ,public QGraphicsItem 
{
	 Q_OBJECT
	 Q_INTERFACES(QGraphicsItem)

public:
	QSttCustomRect(const QPointF& position, qreal width, qreal height, const QString& text, QGraphicsItem* parent = NULL);
	// position:��������
	// width: ���
	// height: �߶�
	//text:�ı�
	virtual ~QSttCustomRect();

public:// ��ȡ�����þ��ε�������ߡ���ȡ��߶ȡ��ı��������������ɫ
	virtual QRectF boundingRect() const ;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = NULL) ;

	QPointF getPosition() const;
	void setPosition(const QPointF& position);

	qreal getWidth() const;
	qreal getHeight() const;

	void setWidth(qreal width);
	void setHeight(qreal height);

	QString getText() const;
	void setText(const QString& text);

	QColor getFillColor() const;
	void setFillColor(const QColor& color);

	QColor getLineColor() const;
	void setLineColor(const QColor& color);

	Qt::PenStyle getLineStyle() const;
	void setLineStyle(Qt::PenStyle style);

	QPointF getRightCenter() const;//�Ҳ����ĵ������
	QPointF getLeftCenter() const;//������ĵ������
	QPointF getTopCenter() const;//�������ĵ������
	QPointF getBottomCenter() const;//�ײ����ĵ������

	void setCenterText(bool bCenter);//�ı��Ƿ������ʾ
	void setRectGeometry(QPointF& position, qreal width, qreal height, const QString& text);//���þ��ε�λ�á���С���ı�
	void setTextOffset(int offsetX, int offsetY);//�����ı���ʾ��λ��

signals:
	void itemSelected();
	void itemDeselected();

protected:
	virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value) ;

private:
	QPointF m_position;
	qreal m_width;
	qreal m_height;
	QString m_text;
	QColor m_fillColor; //�����ɫ
	QColor m_lineColor; //������ɫ
	Qt::PenStyle m_lineStyle; // ��ʵ����ʽ
	bool m_bCenterText; // �����ı��Ƿ������ʾ
	
	int m_textOffsetX;
	int m_textOffsetY;

};

#endif