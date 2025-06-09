#include "SttIecSmvHistogramChartAxis.h"
#include <qwt_plot_canvas.h>
#include <qwt_plot_multi_barchart.h>
#include <qwt_column_symbol.h>
#include <qwt_legend.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_layout.h>

QSttIecSmvAxisPlot::QSttIecSmvAxisPlot(QWidget* parent)
	:QwtPlot(parent)
{
	setAutoFillBackground(true);
	canvas()->setPalette(Qt::white); //���û�ͼ���򱳾�ɫ
	m_pColumnSymbol = new QwtColumnSymbol(QwtColumnSymbol::Box);
	m_pMultiBar = new QSttIecSmvMultiBarChart();
	m_pMultiBar->setLayoutPolicy(QwtPlotMultiBarChart::AutoAdjustSamples);
    m_pMultiBar->setSpacing(2); //ÿ��֮��ļ��
	//m_pMultiBar->setLayoutHint(50);//�����
	m_pMultiBar->setMargin(0);
	m_pMultiBar->attach(this);
	insertLegend(new QwtLegend());
	setAutoReplot(true);//�Զ�����
}

QSttIecSmvAxisPlot::~QSttIecSmvAxisPlot()
{

}

//����һΪ���򣬶�Ϊÿ�����ӵ�ֵ����Ϊÿ�����ӱ�ǩ
void QSttIecSmvAxisPlot::InitBarChat(QVector<QVector<double> >series, QStringList Stringlist)
{
	m_pColumnSymbol->setLineWidth(1);
	m_pColumnSymbol->setFrameStyle(QwtColumnSymbol::Raised);
	m_pColumnSymbol->setPalette(QPalette(QColor(Qt::blue)));
	m_pMultiBar->setSymbol(0, m_pColumnSymbol);

	//����ÿ�����ӵ�ֵ
	m_pMultiBar->m_pBarValue.clear();
	m_pMultiBar->m_pBarValue = series;//��״ͼ�Ϸ���ʾ��ֵ
	m_pMultiBar->setSamples(series);
	setOrientation(Stringlist);
}

void QSttIecSmvAxisPlot::setOrientation(QStringList Stringlist)
{
// 	QwtPlot::Axis axisX, axisY;
// 	
// 	axisX = QwtPlot::xBottom;
// 	axisY = QwtPlot::yLeft;
// 	m_pMultiBar->setOrientation(Qt::Vertical);
// 	setAxisScale(axisX, 0, m_pMultiBar->dataSize() - 1, 1.0);
// 	setAxisAutoScale(axisY);
// 	setAxisScaleDraw(axisX, new QSttIecSmvHistogramChartAxis(Stringlist));
// 	setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignCenter | Qt::AlignBottom);
// 	//���ƿ̶���
// 
// 	QwtScaleDraw *scaleDraw1 = axisScaleDraw(axisX);
// 	scaleDraw1->enableComponent(QwtScaleDraw::Backbone, false);//�̶Ȼ���
// 	scaleDraw1->enableComponent(QwtScaleDraw::Ticks, false);  //�̶���
// 	QwtScaleDraw *scaleDraw2 = axisScaleDraw(axisY);
// 	scaleDraw2->enableComponent(QwtScaleDraw::Backbone, true);//�̶Ȼ���
// 	scaleDraw2->enableComponent(QwtScaleDraw::Ticks, true);  //�̶���
// 	//Ϊָ���������������л��������߱�����
// 	plotLayout()->setAlignCanvasToScale(axisX, true);//���û����������������û��������������
// 	plotLayout()->setAlignCanvasToScale(axisY, false);
// 	plotLayout()->setCanvasMargin(0);
// 	replot();

	QwtPlot::Axis axisX, axisY;

	axisX = QwtPlot::xBottom;
	axisY = QwtPlot::yLeft;
	m_pMultiBar->setOrientation(Qt::Vertical);

	setAxisScale(axisX, 0, m_pMultiBar->dataSize() - 1, 1.0);
	//setAxisAutoScale(axisY);
	// �ֶ�����Y��Ŀ̶ȷ�Χ��ȷ���������б�ǩ
	double maxYValue = 1;
	for (int i = 0; i < m_pMultiBar->m_pBarValue.size(); ++i) 
	{
		const QVector<double>& series = m_pMultiBar->m_pBarValue[i];
		for (int j = 0; j < series.size(); ++j) 
		{
			if (series[j] > maxYValue) 
			{
				maxYValue = series[j];
			}
		}
	}
	setAxisScale(axisY, 0, maxYValue * 1.1); // ����ͷ���ռ�����ʾ��ǩ

	setAxisScaleDraw(axisX, new QSttIecSmvHistogramChartAxis(Stringlist));
	setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignCenter | Qt::AlignBottom);
	//���ƿ̶���

	QwtScaleDraw *scaleDraw1 = axisScaleDraw(axisX);
	scaleDraw1->enableComponent(QwtScaleDraw::Backbone, false);//�̶Ȼ���
	scaleDraw1->enableComponent(QwtScaleDraw::Ticks, false);  //�̶���
	QwtScaleDraw *scaleDraw2 = axisScaleDraw(axisY);
	scaleDraw2->enableComponent(QwtScaleDraw::Backbone, true);//�̶Ȼ���
	scaleDraw2->enableComponent(QwtScaleDraw::Ticks, true);  //�̶���
	//Ϊָ���������������л��������߱�����
	plotLayout()->setAlignCanvasToScale(axisX, true);//���û����������������û��������������
	plotLayout()->setAlignCanvasToScale(axisY, false);
	plotLayout()->setCanvasMargin(0);
	replot();
}

QSttIecSmvHistogramChartAxis::QSttIecSmvHistogramChartAxis(const QStringList &labels):m_pLabel(labels)
{
	 //���ü�ࡢ�м�̶ȡ����̶�
	setTickLength(QwtScaleDiv::MinorTick, 0);
	setTickLength(QwtScaleDiv::MediumTick, 0);
	setTickLength(QwtScaleDiv::MajorTick, 2);
	//������ת�Ƕȡ����뷽ʽ
	setLabelRotation(0);
	setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	
}

QwtText QSttIecSmvHistogramChartAxis::label(double value) const
{
	CString text;
	int val = value;
	if (val >= 0 && val < m_pLabel.size())
	{
		text = m_pLabel[val];
	}
	return text;
}

QSttIecSmvColumnSymbol::QSttIecSmvColumnSymbol(double dValue, QColor color)
{
	m_pColor = color;
	m_dValue = dValue;
}

void QSttIecSmvColumnSymbol::draw(QPainter *p, const QwtColumnRect &rect)const  //��������ͼ,������,��ӱ�ǩ
{
// 	QRectF rect2 = rect.toRect();
// 	p->setBrush(m_pColor);
// 	p->setPen(m_pColor);
// 	p->drawRect(rect.toRect());
//     QColor tempColor = QColor(Qt::white);
// 	p->setPen(tempColor);
// 	QFont oFont;
// 	oFont.setPixelSize(10);
// 	p->setFont(oFont);
// 	int top = rect2.top();
// 	int height = rect2.height();
// 	Qt::Alignment alignment;
// 	alignment = Qt::AlignTop | Qt::AlignHCenter;
// 	p->drawText(QRect(rect2.left() + 1, top, rect2.width() + 2, height), alignment, QString::number(m_dValue,'d',3));
	QRectF rect2 = rect.toRect();
	p->setBrush(m_pColor);
	p->setPen(m_pColor);
	p->drawRect(rect2);

	QColor tempColor = QColor(Qt::black);
	p->setPen(tempColor);

	QString text = QString::number(m_dValue, 'd', 1);
	QFontMetrics fm(p->font());
	QRect textRect = fm.boundingRect(text);

	int top = rect2.top() - textRect.height();  
	int height = textRect.height();
	int width = textRect.width()+10;

	Qt::Alignment alignment = Qt::AlignHCenter | Qt::AlignTop;

	p->drawText(QRect(rect2.left() + (rect2.width() - width) / 2, top, width, height), alignment, text);
}

QSttIecSmvMultiBarChart::QSttIecSmvMultiBarChart()
{

}

QwtColumnSymbol* QSttIecSmvMultiBarChart::specialSymbol(int sampleIndex, int valueIndex)const
{
	QSttIecSmvColumnSymbol *pSymbol = new QSttIecSmvColumnSymbol(m_pBarValue[sampleIndex][valueIndex], QColor(Qt::blue));
	return pSymbol;
}
