#include"PlotOscillogram.h"

//#include<Qtime>
#include <QDir>
#include<QMessageBox>

class CanvasEx :public QwtPlotCanvas
{
public:
	CanvasEx(QwtPlot *plot =NULL): QwtPlotCanvas(plot)
	{

		setPaintAttribute(QwtPlotCanvas::BackingStore,false);
		setBorderRadius(10);
		if(QwtPainter::isX11GraphicsSystem())
		{

#if QT_VERSION <0x050000
			setAttribute(Qt::WA_PaintOutsidePaintEvent,true);
#endif
			if(testPaintAttribute(QwtPlotCanvas::BackingStore))
			{

				setAttribute(Qt::WA_PaintOnScreen,true);
				setAttribute(Qt::WA_NoSystemBackground,true);
			}
		}
		setupPalette();
	}
private:
	void setupPalette()
	{
		QPalette pal=palette();

#if QT_VERSION>=0x040400
		QLinearGradient gradient;
		gradient.setCoordinateMode(QGradient::StretchToDeviceMode);
		gradient.setColorAt(0.0,QColor(0,0,0));
		gradient.setColorAt(1.0,QColor(0,0,0));
		pal.setBrush(QPalette::Window,QBrush(gradient));
#else
		pal.setBrush(QPalette::Window,QBrush(color));
#endif
		pal.setColor(QPalette::WindowText,Qt::green);
		setPalette(pal);

	}
};
class ZoomerEx:public QwtPlotZoomer//放缩
{
public:
	ZoomerEx(int xAxis,int yAxis,CanvasEx *canvas):QwtPlotZoomer(xAxis,yAxis,canvas)
	{
		setTrackerMode(QwtPicker::AlwaysOff);//追踪模式
		setRubberBand(QwtPicker::NoRubberBand);//橡皮筋（放缩）
		setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton,Qt::ControlModifier);
		setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton);//设置鼠标放缩模式
	}
};

PlotOscillogram::PlotOscillogram(SttHarmTableType type,QWidget *parent):QwtPlot(parent),
d_interval(0.0,4000.0)//设置区间
{
	d_directPainter = new QwtPlotDirectPainter();
	setAutoReplot(false);
	setCanvas(new CanvasEx());//设置画布
	plotLayout()->setAlignCanvasToScales(true);//为所有轴线设置排列画布到轴线比例尺flag
	setAxisScale(QwtPlot::xBottom,d_interval.minValue(),d_interval.maxValue());//轴线刻度
	enableAxis(QwtPlot::yLeft,true);
	enableAxis(QwtPlot::xBottom,false);//使能坐标轴
	QwtText t;
	QFont font;
	font.setBold(true);//粗体
	font.setPointSize(11);
	t.setFont(font);//设置字体

	if(type==TYPE_I)
	{
		setAxisScale(QwtPlot::yLeft, -11.0, 11.0 );
		t.setText("I(A)");
	}
	else if(type==TYPE_V)
	{
		setAxisScale(QwtPlot::yLeft, -250.0, 250.0 );
		t.setText("U(V)");

	}
	setAxisTitle(QwtPlot::yLeft,t);

	//202040428 suyang linux下不让拖动
#ifndef _PSX_QT_LINUX_			
	d_zoomer[0]=new ZoomerEx(QwtPlot::xBottom , QwtPlot::yLeft , (CanvasEx*)this->canvas());
	d_zoomer[0]->setRubberBand(QwtPicker::RectRubberBand);
	d_zoomer[0]->setRubberBandPen(QColor(Qt::green));
	d_zoomer[0]->setTrackerMode(QwtPicker::ActiveOnly);
	d_zoomer[0]->setTrackerPen(QColor(Qt::white));

	d_zoomer[1]=new ZoomerEx(QwtPlot::xTop ,QwtPlot::yRight, (CanvasEx*)this->canvas());
#endif
	QwtPlotGrid *grid = new QwtPlotGrid();//设置网格 
	grid->setPen(Qt::gray,0.0,Qt::DotLine);
	grid->enableX(true);
	grid->enableXMin(true);
	grid->enableY(true);
	grid->enableYMin(false);
	grid->attach(this);

	d_origin=new QwtPlotMarker();//标记
	d_origin->setLineStyle(QwtPlotMarker::Cross);
	d_origin->setValue(d_interval.minValue()+d_interval.width()/2.0, 0.0 );
	d_origin->setLinePen(Qt::gray,0.0,Qt::DashLine);
	d_origin->attach(this);

	d_picker=new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn, this->canvas() );
	//拾取光标所在位置信息
	d_picker->setRubberBandPen(QColor(Qt::green));
	d_picker->setRubberBand(QwtPicker::CrossRubberBand);
	d_picker->setTrackerPen(QColor(Qt::green));

	setAutoReplot(true);


}
PlotOscillogram::~PlotOscillogram()
{

}

void PlotOscillogram::insertCurve(const QString& title, QVector<double> &values, QColor color, bool show )//插入波形曲线
{
	QVector<QPointF>samples(values.size());
	int j = 0;
	for(int i=0;i<values.size();i++)
	{
		samples[j++] = QPointF(double(i),values[i]);
	}

	QwtPlotCurve *curve = new QwtPlotCurve(title);
	curve->setRenderHint(QwtPlotItem::RenderAntialiased);//反走样渲染
	curve->setStyle(QwtPlotCurve::Lines);
	curve->setLegendAttribute(QwtPlotCurve::LegendShowLine,true);//图例属性
	curve->setPen(QPen(color));
	curve->setSamples(samples);
	curve->attach(this);
	d_curves.append(curve);
	showCurve(curve,show);
	replot();

}

void PlotOscillogram::showCurve(QwtPlotItem *item, bool on)//显示单个曲线
{
	item->setVisible(on);
	replot();
}

void PlotOscillogram::showCurve( const QString& title, bool on )//显示多个曲线
{
	for(int i = 0; i<d_curves.size(); i++ )
	{
		if(d_curves.at(i)->title() == title)
		{
			showCurve(d_curves.at(i), on);
			return;
		}
	}
}

bool PlotOscillogram::existCurve( const QString& title)//判断曲线是否存在？
{
	for(int i = 0;i<d_curves.size();i++ )
	{
		if(d_curves.at(i)->title()== title)
		{
			return true;
		}
	}
	return false;
}

void PlotOscillogram::clearCurve()//清除所有曲线
{
	qDeleteAll(d_curves);
	d_curves.clear();
	replot();
}

void PlotOscillogram::resizeEvent( QResizeEvent * event)
{
	d_directPainter->reset();
	QwtPlot::resizeEvent(event);
}

void PlotOscillogram::showEvent( QShowEvent * )
{
	replot();
}

void PlotOscillogram::UpdateYInterval(float fv)
{
	setAxisScale(QwtPlot::yLeft,-fv,fv);
	replot();
}
