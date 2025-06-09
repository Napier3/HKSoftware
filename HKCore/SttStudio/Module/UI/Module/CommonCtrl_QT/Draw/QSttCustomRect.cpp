#include "QSttCustomRect.h"
#include <QTextDocument>

QSttCustomRect::QSttCustomRect(const QPointF& position, qreal width, qreal height, const QString& text, QGraphicsItem* parent /*= NULL*/ )
: QGraphicsItem(parent), m_position(position),m_width(width),m_height(height),m_text(text),m_fillColor(Qt::cyan),
m_lineColor(Qt::black),m_lineStyle(Qt::SolidLine),m_bCenterText(true) // Ĭ������½��ı���ʾ����
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

	// ���ƾ���
	painter->setPen(QPen(m_lineColor, 2, m_lineStyle));
	painter->setBrush(m_fillColor);
	painter->drawRect(boundingRect());

	// �����ı�
	painter->setPen(QPen(m_lineColor));

	// �����ı�λ�úͶ��뷽ʽ
	QRectF textRect = boundingRect();
	int x, y;
	Qt::Alignment alignment;

	if (m_bCenterText)
	{
		// ������ʾ�ı�
		QPointF center = boundingRect().center();
		x = static_cast<int>(center.x() - textRect.width() / 2.0);
		y = static_cast<int>(center.y() - textRect.height() / 2.0);
		alignment = Qt::AlignHCenter | Qt::AlignVCenter;
	} 
	else 
	{
		// ָ���ı�λ��
		x = static_cast<int>(textRect.left());
		y = static_cast<int>(textRect.top());
		alignment = Qt::AlignHCenter | Qt::AlignTop;
	}
	

	// �����ı����Զ�����
	QTextOption textOption(alignment);
	textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere); // �����Զ�����ģʽ
	QTextDocument textDocument;
	textDocument.setDefaultTextOption(textOption);
	textDocument.setPlainText(m_text);
	textDocument.setTextWidth(textRect.width());

	// �����ı��Ĵ�С
	QSizeF textSize = textDocument.size();
	int textX ,textY;
	if (m_bCenterText)
	{
	// �ı�����
		textX = static_cast<int>(x + (textRect.width() - textSize.width()) / 2.0);
		textY = static_cast<int>(y + (textRect.height() - textSize.height()) / 2.0);
	}
	else 
	{
		// �Զ����ı�λ��
		textX = static_cast<int>(x + (textRect.width() - textSize.width()) / 2.0) + m_textOffsetX;
		textY = static_cast<int>(y - 20) + m_textOffsetY; // ƫ��������Ϊ m_textOffsetY
	}
	

	painter->translate(textX, textY);

	// �����ı�
	textDocument.drawContents(painter);
}

QVariant QSttCustomRect::itemChange(GraphicsItemChange change, const QVariant& value) 
{
	if (change == QGraphicsItem::ItemSelectedChange && scene()) 
	{
		// ��ͼ���ѡ�л�ȡ��ѡ��ʱ�����ź�
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



