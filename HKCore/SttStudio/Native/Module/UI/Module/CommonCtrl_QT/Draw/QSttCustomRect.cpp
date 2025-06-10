#include "QSttCustomRect.h"
#include <QTextDocument>

QSttCustomRect::QSttCustomRect(const QPointF& position, qreal width, qreal height, const QString& text, QGraphicsItem* parent /*= NULL*/ )
: QGraphicsItem(parent), m_position(position),m_width(width),m_height(height),m_text(text),m_fillColor(Qt::cyan),
m_lineColor(Qt::black),m_lineStyle(Qt::SolidLine),m_bCenterText(true) // 默认情况下将文本显示居中
{
	setFlag(QGraphicsItem::ItemSendsGeometryChanges);
	setFlag(QGraphicsItem::ItemIsSelectable);
}

QSttCustomRect::~QSttCustomRect()
{

}

QRectF QSttCustomRect::boundingRect() const
{
	return QRectF(m_position, QSizeF(m_width, m_height));
}

void QSttCustomRect::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)

	// 绘制矩形
	painter->setPen(QPen(m_lineColor, 2, m_lineStyle));
	painter->setBrush(m_fillColor);
	painter->drawRect(boundingRect());

	// 绘制文本
	painter->setPen(QPen(m_lineColor));

	// 计算文本位置和对齐方式
	QRectF textRect = boundingRect();
	int x, y;
	Qt::Alignment alignment;

	if (m_bCenterText)
	{
		// 居中显示文本
		QPointF center = boundingRect().center();
		x = static_cast<int>(center.x() - textRect.width() / 2.0);
		y = static_cast<int>(center.y() - textRect.height() / 2.0);
		alignment = Qt::AlignHCenter | Qt::AlignVCenter;
	} 
	else 
	{
		// 指定文本位置
		x = static_cast<int>(textRect.left());
		y = static_cast<int>(textRect.top());
		alignment = Qt::AlignHCenter | Qt::AlignTop;
	}
	

	// 绘制文本，自动换行
	QTextOption textOption(alignment);
	textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere); // 设置自动换行模式
	QTextDocument textDocument;
	textDocument.setDefaultTextOption(textOption);
	textDocument.setPlainText(m_text);
	textDocument.setTextWidth(textRect.width());

	// 计算文本的大小
	QSizeF textSize = textDocument.size();
	int textX ,textY;
	if (m_bCenterText)
	{
	// 文本居中
		textX = static_cast<int>(x + (textRect.width() - textSize.width()) / 2.0);
		textY = static_cast<int>(y + (textRect.height() - textSize.height()) / 2.0);
	}
	else 
	{
		// 自定义文本位置
		textX = static_cast<int>(x + (textRect.width() - textSize.width()) / 2.0) + m_textOffsetX;
		textY = static_cast<int>(y - 20) + m_textOffsetY; // 偏移量调整为 m_textOffsetY
	}
	

	painter->translate(textX, textY);

	// 绘制文本
	textDocument.drawContents(painter);
}

QVariant QSttCustomRect::itemChange(GraphicsItemChange change, const QVariant& value) 
{
	if (change == QGraphicsItem::ItemSelectedChange && scene()) 
	{
		// 在图形项被选中或取消选中时触发信号
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

QPointF QSttCustomRect::getPosition() const
{
	return m_position;
}

void QSttCustomRect::setPosition(const QPointF& position)
{
	m_position = position;
}

qreal QSttCustomRect::getWidth() const
{
	return m_width;
}

qreal QSttCustomRect::getHeight() const
{
	return m_height;
}

void QSttCustomRect::setWidth(qreal width)
{
	m_width = width;
}

void QSttCustomRect::setHeight(qreal height)
{
	m_height = height;
}

QString QSttCustomRect::getText() const
{
	return m_text;
}

void QSttCustomRect::setText(const QString& text)
{
	m_text = text;
}

QColor QSttCustomRect::getFillColor() const
{
	return m_fillColor;
}

void QSttCustomRect::setFillColor(const QColor& color)
{
	m_fillColor = color;
}

QColor QSttCustomRect::getLineColor() const
{
	return m_lineColor;
}

void QSttCustomRect::setLineColor(const QColor& color)
{
	m_lineColor = color;
}

Qt::PenStyle QSttCustomRect::getLineStyle() const
{
	return m_lineStyle;
}

void QSttCustomRect::setLineStyle(Qt::PenStyle style)
{
	m_lineStyle = style;
}

QPointF QSttCustomRect::getTopCenter() const 
{
	QRectF rect = boundingRect();
	QPointF topCenter(rect.center().x(), rect.top());
	return topCenter;
}

QPointF QSttCustomRect::getRightCenter() const 
{
	QRectF rect = boundingRect();
	QPointF rightCenter(rect.right(), rect.center().y());
	return rightCenter;
}

QPointF QSttCustomRect::getLeftCenter() const
{
	QRectF rect = boundingRect();
	QPointF leftCenter(rect.left(), rect.center().y());
	return leftCenter;
}

QPointF QSttCustomRect::getBottomCenter() const
{
	QRectF rect = boundingRect();
	QPointF bottomCenter(rect.center().x(), rect.bottom());
	return bottomCenter;
}

void QSttCustomRect::setRectGeometry( QPointF& position, qreal width, qreal height, const QString& text )
{
	m_position = position;
	m_width = width;
	m_height = height;
	m_text = text;
}



void QSttCustomRect::setCenterText( bool bCenter )
{
	m_bCenterText = bCenter;
}

void QSttCustomRect::setTextOffset( int offsetX, int offsetY )
{
	m_textOffsetX = offsetX;
	m_textOffsetY = offsetY;
}



