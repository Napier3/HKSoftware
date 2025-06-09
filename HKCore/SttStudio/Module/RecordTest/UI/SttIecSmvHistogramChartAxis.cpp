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
	canvas()->setPalette(Qt::white); //设置绘图区域背景色
	m_pColumnSymbol = new QwtColumnSymbol(QwtColumnSymbol::Box);
	m_pMultiBar = new QSttIecSmvMultiBarChart();
	m_pMultiBar->setLayoutPolicy(QwtPlotMultiBarChart::AutoAdjustSamples);
    m_pMultiBar->setSpacing(2); //每组之间的间隔
	//m_pMultiBar->setLayoutHint(50);//柱宽度
	m_pMultiBar->setMargin(0);
	m_pMultiBar->attach(this);
	insertLegend(new QwtLegend());
	setAutoReplot(true);//自动缩放
}

QSttIecSmvAxisPlot::~QSttIecSmvAxisPlot()
{

}

//参数一为方向，二为每根柱子的值，三为每根柱子标签
void QSttIecSmvAxisPlot::InitBarChat(QVector<QVector<double> >series, QStringList Stringlist)
{
	m_pColumnSymbol->setLineWidth(1);
	m_pColumnSymbol->setFrameStyle(QwtColumnSymbol::Raised);
	m_pColumnSymbol->setPalette(QPalette(QColor(Qt::blue)));
	m_pMultiBar->setSymbol(0, m_pColumnSymbol);

	//设置每根柱子的值
	m_pMultiBar->m_pBarValue.clear();
	m_pMultiBar->m_pBarValue = series;//柱状图上方显示的值
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
// 	//绘制刻度线
// 
// 	QwtScaleDraw *scaleDraw1 = axisScaleDraw(axisX);
// 	scaleDraw1->enableComponent(QwtScaleDraw::Backbone, false);//刻度基线
// 	scaleDraw1->enableComponent(QwtScaleDraw::Ticks, false);  //刻度线
// 	QwtScaleDraw *scaleDraw2 = axisScaleDraw(axisY);
// 	scaleDraw2->enableComponent(QwtScaleDraw::Backbone, true);//刻度基线
// 	scaleDraw2->enableComponent(QwtScaleDraw::Ticks, true);  //刻度线
// 	//为指定的轴线设置排列画布到轴线比例尺
// 	plotLayout()->setAlignCanvasToScale(axisX, true);//设置画布靠近坐标轴设置画布和坐标轴对齐
// 	plotLayout()->setAlignCanvasToScale(axisY, false);
// 	plotLayout()->setCanvasMargin(0);
// 	replot();

	QwtPlot::Axis axisX, axisY;

	axisX = QwtPlot::xBottom;
	axisY = QwtPlot::yLeft;
	m_pMultiBar->setOrientation(Qt::Vertical);

	setAxisScale(axisX, 0, m_pMultiBar->dataSize() - 1, 1.0);
	//setAxisAutoScale(axisY);
	// 手动设置Y轴的刻度范围，确保包含所有标签
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
	setAxisScale(axisY, 0, maxYValue * 1.1); // 留出头部空间以显示标签

	setAxisScaleDraw(axisX, new QSttIecSmvHistogramChartAxis(Stringlist));
	setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignCenter | Qt::AlignBottom);
	//绘制刻度线

	QwtScaleDraw *scaleDraw1 = axisScaleDraw(axisX);
	scaleDraw1->enableComponent(QwtScaleDraw::Backbone, false);//刻度基线
	scaleDraw1->enableComponent(QwtScaleDraw::Ticks, false);  //刻度线
	QwtScaleDraw *scaleDraw2 = axisScaleDraw(axisY);
	scaleDraw2->enableComponent(QwtScaleDraw::Backbone, true);//刻度基线
	scaleDraw2->enableComponent(QwtScaleDraw::Ticks, true);  //刻度线
	//为指定的轴线设置排列画布到轴线比例尺
	plotLayout()->setAlignCanvasToScale(axisX, true);//设置画布靠近坐标轴设置画布和坐标轴对齐
	plotLayout()->setAlignCanvasToScale(axisY, false);
	plotLayout()->setCanvasMargin(0);
	replot();
}

QSttIecSmvHistogramChartAxis::QSttIecSmvHistogramChartAxis(const QStringList &labels):m_pLabel(labels)
{
	 //设置间距、中间刻度、主刻度
	setTickLength(QwtScaleDiv::MinorTick, 0);
	setTickLength(QwtScaleDiv::MediumTick, 0);
	setTickLength(QwtScaleDiv::MajorTick, 2);
	//设置旋转角度、对齐方式
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

void QSttIecSmvColumnSymbol::draw(QPainter *p, const QwtColumnRect &rect)const  //绘制柱形图,画矩形,添加标签
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
