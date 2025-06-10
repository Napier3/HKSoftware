#include "SttIecSmvDiscretChartAxis.h"
#include <qwt_plot_canvas.h>
#include <qwt_plot_multi_barchart.h>
#include <qwt_column_symbol.h>
#include <qwt_legend.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_layout.h>


QSttIecSmvDiscretChartAxis::QSttIecSmvDiscretChartAxis(QWidget* parent)
	:QwtPlot(parent)
{
	setAutoFillBackground(true);
	/*setPalette(Qt::white); //���ò�������ɫ*/
	canvas()->setPalette(Qt::white); //���û�ͼ���򱳾�ɫ
	//insertLegend(new QwtLegend(), QwtPlot::RightLegend);�����ұ߱�ע
	m_pColumnSymbol = new QwtColumnSymbol(QwtColumnSymbol::Box);
	m_pMultiBar = new QSttIecSmvDiscretChartPlot();
	m_pMultiBar->setLayoutPolicy(QwtPlotMultiBarChart::AutoAdjustSamples);
	m_pMultiBar->setSpacing(30);
	m_pMultiBar->setMargin(0);
	m_pMultiBar->attach(this);
	insertLegend(new QwtLegend());
	setAutoReplot(true);//�Զ�����
}

QSttIecSmvDiscretChartAxis::~QSttIecSmvDiscretChartAxis()
{

}

//����һΪ���򣬶�Ϊÿ�����ӵ�ֵ����Ϊÿ�����ӱ�ǩ
void QSttIecSmvDiscretChartAxis::InitBarChat(int oritention, QVector<QVector<double> > series, QStringList m_list, CCapDevice92 *pCapDevice, int nPkgMaxNum)
{
// 	QList<QwtText> titles;
// 	for (int i = 0; i < 1; i++)
// 	{
// 		QString title("%1");
// 		titles += title.arg(i);
// 	}
// 	m_pMultiBar->setBarTitles(titles);

	for (int i = 0; i < 1; i++)
	{
		m_pColumnSymbol->setLineWidth(1);
		m_pColumnSymbol->setFrameStyle(QwtColumnSymbol::Raised);
		m_pColumnSymbol->setPalette(QPalette(QColor("blue")/*colors[i]*/));
		m_pMultiBar->setSymbol(i, m_pColumnSymbol);
	}
	//����ÿ�����ӵ�ֵ
	m_pMultiBar->m_pBarValue.clear();
	m_pMultiBar->m_pBarValue = series;//��״ͼ�Ϸ���ʾ��ֵ
	m_pMultiBar->setSamples(series);
	m_pMultiBar->m_nPkgMaxNumPlot = nPkgMaxNum;
	setOrientation(oritention, m_list, pCapDevice);
}

void QSttIecSmvDiscretChartAxis::setOrientation(int orientation, QStringList m_list, CCapDevice92 *pCapDevice)
{
	QwtPlot::Axis axis1, axis2;
	if (orientation == 0)
	{
		axis1 = QwtPlot::xBottom;
		axis2 = QwtPlot::yLeft;
		m_pMultiBar->setOrientation(Qt::Vertical);
	}
	else
	{
		axis1 = QwtPlot::yLeft;
		axis2 = QwtPlot::xBottom;
		m_pMultiBar->setOrientation(Qt::Horizontal);
	}
	
	QStringList d_distors = m_list;
	setAxisScale(axis1, 0, m_pMultiBar->dataSize() - 1, 1.0);
	if (pCapDevice->m_oAnalysisResults.nPkgNum == 0)//��δ�����Զ�ģ��ʱ������y����������Сֵ
	{
		setAxisScale(axis2, 0, m_pMultiBar->dataSize() - 1, 1.0);
	}
	else
	{
		setAxisAutoScale(axis2);
	}
	setAxisScaleDraw(axis1, new QSttIecSmvDiscretChartDraw((Qt::Orientation)orientation, d_distors));
	setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignCenter | Qt::AlignBottom);
	//���ƿ̶���

	QwtScaleDraw *scaleDraw1 = axisScaleDraw(axis1);
	scaleDraw1->enableComponent(QwtScaleDraw::Backbone, false);//�̶Ȼ���
	scaleDraw1->enableComponent(QwtScaleDraw::Ticks, false);  //�̶���
	QwtScaleDraw *scaleDraw2 = axisScaleDraw(axis2);
	scaleDraw2->enableComponent(QwtScaleDraw::Backbone, true);//�̶Ȼ���
	scaleDraw2->enableComponent(QwtScaleDraw::Ticks, true);  //�̶���
	//Ϊָ���������������л��������߱�����
	plotLayout()->setAlignCanvasToScale(axis1, true);//���û����������������û��������������
	plotLayout()->setAlignCanvasToScale(axis2, false);
	plotLayout()->setCanvasMargin(0);
	replot();
}

QSttIecSmvDiscretChartDraw::QSttIecSmvDiscretChartDraw(Qt::Orientation orientation, const QStringList &labels)
	:m_pLabel(labels)
{
	 //���ü�ࡢ�м�̶ȡ����̶�
	setTickLength(QwtScaleDiv::MinorTick, 0);
	setTickLength(QwtScaleDiv::MediumTick, 0);
	setTickLength(QwtScaleDiv::MajorTick, 2);
	//������ת�Ƕȡ����뷽ʽ
	setLabelRotation(0);
	setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	
}

QwtText QSttIecSmvDiscretChartDraw::label(double value) const
{
	CString text;
	int val = value;
	if (val >= 0 && val < m_pLabel.size())
	{
		text = m_pLabel[val];
	}
	return text;
}

QSttIecSmvDiscretChartColumnSymbol::QSttIecSmvDiscretChartColumnSymbol(double hit, QColor color, double Maxhit)
{
	m_pColor = color;
	m_nhit = hit;
	m_nMaxhit = Maxhit;
}

void QSttIecSmvDiscretChartColumnSymbol::draw(QPainter *p, const QwtColumnRect &rect)const
{
	QRectF rect2 = rect.toRect();
	p->setBrush(m_pColor);
	p->setPen(m_pColor);
	p->drawRect(rect.toRect());
	QColor tempColor;
	p->setPen(tempColor);
	int top = rect2.top();
	int height = rect2.height();
	Qt::Alignment alignment;
	alignment = Qt::AlignRight;
	if (m_nhit > (m_nMaxhit / 5))
	{
		tempColor = QColor("white");
		p->setPen(tempColor);
		p->drawText(QRect(rect2.left(), top, rect2.width(), height), alignment, QString::number(m_nhit));
	}
	else
	{
		tempColor = QColor("black");
		p->setPen(tempColor);
		p->drawText(QRect(rect2.left(), top, rect2.width() + 50, height), alignment, QString::number(m_nhit));
	}
}

QSttIecSmvDiscretChartPlot::QSttIecSmvDiscretChartPlot()
{

}

QwtColumnSymbol* QSttIecSmvDiscretChartPlot::specialSymbol(int sampleIndex, int valueIndex)const
{
	QSttIecSmvDiscretChartColumnSymbol *pSymbol = new QSttIecSmvDiscretChartColumnSymbol(m_pBarValue[sampleIndex][valueIndex],
		QColor("blue")/*colors[valueIndex]*/, m_nPkgMaxNumPlot);
	return pSymbol;
}
