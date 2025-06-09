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

	// �����µĻ����С
	int nSize = 120; // �µĻ����С

	// ��ȡ�������
	QStyleOptionSlider opt;
	initStyleOption(&opt);
	QRect handleRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

	// �����Զ��廬���С
	handleRect.setSize(QSize(nSize, nSize));
}
void ScrollSlider::mousePressEvent(QMouseEvent *ev)
{
	if (ev->button() == Qt::LeftButton) 
	{
		// ��ȡ��ǰ�����λ��
		int nPos = ev->y();

		// �����Ӧ��ֵ�������±�Ϊ 1
		double fValue = minimum() + ((double)(maximum() - minimum()) * (height() - nPos) / height());

		// ʹ�� qRound �����������룬��ȷ��ֵΪ����
		int nValue = qRound(fValue);

		// �ҵ�����Ŀ̶���λ��
		int nTick = qRound((double)(nValue - minimum()) / tickInterval()) * tickInterval() + minimum();

		// �����µ�ֵ��ȷ����������Χ
		if (nTick < minimum())
		{
			nTick = minimum();
		} 
		else if (nTick > maximum())
		{
			nTick = maximum();
		}

		// ����Ƿ���Ҫ��ת��ֵ
		if (invertedAppearance())
		{
			nTick = maximum() - (nTick - minimum());
		}

		setValue(nTick);
	}

	// ��¼��갴��ʱ��λ��
	m_lastMousePos = ev->pos();
}


void ScrollSlider::mouseMoveEvent(QMouseEvent *ev)
{
	if (ev->buttons() & Qt::LeftButton) 
	{
		// ��ȡ��ǰ����߶�
		int nHeight = height();

		// ��ȡ��ǰ������̶ܿ���
		int nSteps = maximum() - minimum();

		// ����ÿ���̶ȵĸ߶�
		double fHeight = (double)nHeight / nSteps;

		// ������굱ǰλ�ö�Ӧ�Ŀ̶�ֵ
		int nStep = qRound((double)(nHeight - ev->pos().y()) / fHeight);

		// ������ֵ
		int nValue = minimum() + nStep;

		// ��ֹ������Χ
		if (nValue < minimum()) 
		{
			nValue = minimum();
		} 
		else if (nValue > maximum()) 
		{
			nValue = maximum();
		}

		// �����ֵ��ͬ�ڵ�ǰֵ�������
		if (nValue != value()) 
		{
			setValue(nValue);
		}

		// �������һ�����λ��
		m_lastMousePos = ev->pos();
	}
}

void ScrollSlider::mouseReleaseEvent(QMouseEvent *ev)
{
	QSlider::mouseReleaseEvent(ev);

	// ���֮ǰ��¼��״̬
	m_lastMousePos = QPoint();
}
