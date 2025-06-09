#include "ScrollSlider.h"
#include <QMouseEvent>
#include <QStyle>
#include <QStyleOptionSlider>

ScrollSlider::ScrollSlider(QWidget *parent) : QSlider(Qt::Horizontal, parent) 
{

}

void ScrollSlider::paintEvent(QPaintEvent *event)
{
	QSlider::paintEvent(event);

	// 设置新的滑块大小
	int nSize = 120; // 新的滑块大小

	// 获取滑块矩形
	QStyleOptionSlider opt;
	initStyleOption(&opt);
	QRect handleRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

	// 设置自定义滑块大小
	handleRect.setSize(QSize(nSize, nSize));
}
void ScrollSlider::mousePressEvent(QMouseEvent *ev)
{
	if (ev->button() == Qt::LeftButton) 
	{
		// 获取当前点击的位置
		int nPos = ev->y();

		// 计算对应的值，以最下边为 1
		double fValue = minimum() + ((double)(maximum() - minimum()) * (height() - nPos) / height());

		// 使用 qRound 进行四舍五入，以确保值为整数
		int nValue = qRound(fValue);

		// 找到最近的刻度线位置
		int nTick = qRound((double)(nValue - minimum()) / tickInterval()) * tickInterval() + minimum();

		// 设置新的值，确保不超出范围
		if (nTick < minimum())
		{
			nTick = minimum();
		} 
		else if (nTick > maximum())
		{
			nTick = maximum();
		}

		// 检查是否需要翻转数值
		if (invertedAppearance())
		{
			nTick = maximum() - (nTick - minimum());
		}

		setValue(nTick);
	}

	// 记录鼠标按下时的位置
	m_lastMousePos = ev->pos();
}


void ScrollSlider::mouseMoveEvent(QMouseEvent *ev)
{
	if (ev->buttons() & Qt::LeftButton) 
	{
		// 获取当前滑块高度
		int nHeight = height();

		// 获取当前滑块的总刻度数
		int nSteps = maximum() - minimum();

		// 计算每个刻度的高度
		double fHeight = (double)nHeight / nSteps;

		// 计算鼠标当前位置对应的刻度值
		int nStep = qRound((double)(nHeight - ev->pos().y()) / fHeight);

		// 计算新值
		int nValue = minimum() + nStep;

		// 防止超出范围
		if (nValue < minimum()) 
		{
			nValue = minimum();
		} 
		else if (nValue > maximum()) 
		{
			nValue = maximum();
		}

		// 如果新值不同于当前值，则更新
		if (nValue != value()) 
		{
			setValue(nValue);
		}

		// 更新最后一次鼠标位置
		m_lastMousePos = ev->pos();
	}
}

void ScrollSlider::mouseReleaseEvent(QMouseEvent *ev)
{
	QSlider::mouseReleaseEvent(ev);

	// 清除之前记录的状态
	m_lastMousePos = QPoint();
}
