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
	// position:左上坐标
	// width: 宽度
	// height: 高度
	//text:文本
	virtual ~QSttCustomRect();

public:// 获取和设置矩形的左上左边、宽度、高度、文本、线条和填充颜色
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

	QPointF getRightCenter() const;//右侧中心点的坐标
	QPointF getLeftCenter() const;//左侧中心点的坐标
	QPointF getTopCenter() const;//顶部中心点的坐标
	QPointF getBottomCenter() const;//底部中心点的坐标

	void setCenterText(bool bCenter);//文本是否居中显示
	void setRectGeometry(QPointF& position, qreal width, qreal height, const QString& text);//设置矩形的位置、大小和文本
	void setTextOffset(int offsetX, int offsetY);//设置文本显示的位置

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
	QColor m_fillColor; //填充颜色
	QColor m_lineColor; //线条颜色
	Qt::PenStyle m_lineStyle; // 虚实线样式
	bool m_bCenterText; // 控制文本是否居中显示
	
	int m_textOffsetX;
	int m_textOffsetY;

};

#endif