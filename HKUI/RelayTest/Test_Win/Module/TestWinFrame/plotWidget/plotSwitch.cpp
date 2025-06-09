#include "plotSwitch.h"
#include <QTime>
#include <qwt_picker_machine.h>
#include <qwt_scale_widget.h>
#include <QLayout>
#include <QFont>
#include "..\ReportView\XLangResource_PowerTestWin.h"

int SwitchY[LINENUM] = {-14,-20,-26,-32,-38,-44,-50,-56,-62,-68,-74,-80,-86,-92,-98,-104,-110,-116};
class Canvas: public QwtPlotCanvas
{
public:
	Canvas( QwtPlot *plot = NULL ):
	  QwtPlotCanvas( plot )
	  {
		  setPaintAttribute( QwtPlotCanvas::BackingStore, false );
		  setBorderRadius( 10 );

		  if ( QwtPainter::isX11GraphicsSystem() )
		  {
#if QT_VERSION < 0x050000
			  
			  setAttribute( Qt::WA_PaintOutsidePaintEvent, true );
#endif
			  if ( testPaintAttribute( QwtPlotCanvas::BackingStore ) )
			  {
				  setAttribute( Qt::WA_PaintOnScreen, true );
				  setAttribute( Qt::WA_NoSystemBackground, true );
			  }
		  }

		  setupPalette();
	  }

private:
	void setupPalette()
	{
		QPalette pal = palette();

#if QT_VERSION >= 0x040400
		QLinearGradient gradient;
		gradient.setCoordinateMode( QGradient::StretchToDeviceMode );
		gradient.setColorAt( 0.0, QColor( 0, 49, 110 ) );
		gradient.setColorAt( 1.0, QColor( 0, 87, 174 ) );

		pal.setBrush( QPalette::Window, QBrush( gradient ) );
#else
		pal.setBrush( QPalette::Window, QBrush( color ) );
#endif

		// QPalette::WindowText is used for the curve color
		pal.setColor( QPalette::WindowText, Qt::green );

		setPalette( pal );
	}
};

class Background: public QwtPlotItem
{
public:
	Background()
	{
		setZ( 0.0 );
	}

	virtual int rtti() const
	{
		return QwtPlotItem::Rtti_PlotUserItem;
	}

	virtual void draw( QPainter *painter,
		const QwtScaleMap &, const QwtScaleMap &yMap,
		const QRectF &canvasRect ) const
	{
		QColor c( Qt::white );
		QColor c2( Qt::black);
		QRectF r = canvasRect;

		if (r.bottom()>0)
		{
			r.setBottom( yMap.transform(0 ) );
			r.setTop( yMap.transform( 1000 ) );
			painter->fillRect( r, c );
		}
		else
		{
			r.setBottom( yMap.transform(-1000 ) );
			r.setTop( yMap.transform( 0 ) );
			painter->fillRect( r, c2 );
		}
	}
};

class YScaleDraw: public QwtScaleDraw        //自画坐标轴
{
public:
	YScaleDraw()
	{
	}
	virtual QwtText label( double v ) const  //重绘坐标轴 刻度值
	{
		if (v>=0 && v<=120)
		{
			return QwtText("  ");
		}
		else if ((fabs(v)-8) < EPSINON)
		{
			return QwtText( ("  ") );
		}
		else if ((fabs(v)-14) < EPSINON)
		{
			return QwtText( ("   A") );
		}
		else if ((fabs(v)-20) < EPSINON)
		{
			return QwtText( ("   B") );
		}
		else if ((fabs(v)-26) < EPSINON)
		{
			return QwtText( ("   C") );
		}
		else if ((fabs(v)-32) < EPSINON)
		{
			return QwtText( ("   D") );
		}
		else if ((fabs(v)-38) < EPSINON)
		{
			return QwtText( ("   E") );
		}
		else if ((fabs(v)-44) < EPSINON)
		{
			return QwtText( ("   F") );
		}
		else if ((fabs(v)-50) < EPSINON)
		{
			return QwtText( ("   G") );
		}
		else if ((fabs(v)-56) < EPSINON)
		{
			return QwtText( ("   H") );
		}
		else if ((fabs(v)-62) < EPSINON)
		{
			return QwtText( ("   1") );
		}
		else if ((fabs(v)-68) < EPSINON)
		{
			return QwtText( ("   2") );
		}
		else if ((fabs(v)-74) < EPSINON)
		{
			return QwtText( ("   3") );
		}
		else if ((fabs(v)-80) < EPSINON)
		{
			return QwtText( ("   4") );
		}
		else if ((fabs(v)-86) < EPSINON)
		{
			return QwtText( ("   5") );
		}
		else if ((fabs(v)-92) < EPSINON)
		{
			return QwtText( ("   6") );
		}
		else if ((fabs(v)-98) < EPSINON)
		{
			return QwtText( ("   7") );
		}
		else if ((fabs(v)-104) < EPSINON)
		{
			return QwtText( ("   8") );
		}
		else
		{
			return QwtText( "   " );
		}
	}
};

class Y2ScaleDraw: public QwtScaleDraw        //自画坐标轴
{
public:
	Y2ScaleDraw()
	{
	}
	virtual QwtText label( double v ) const  //重绘坐标轴 刻度值
	{
		if (v>=0 && v<=120)
		{
			return QwtText("    ");
		}
		else if ((fabs(v)-8) < EPSINON)
		{
			return QwtText( ("   A") );
		}
		else if ((fabs(v)-14) < EPSINON)
		{
			return QwtText( ("   B") );
		}
		else if ((fabs(v)-20) < EPSINON)
		{
			return QwtText( ("   C") );
		}
		else if ((fabs(v)-26) < EPSINON)
		{
			return QwtText( ("   D") );
		}
		else if ((fabs(v)-32) < EPSINON)
		{
			return QwtText( ("   E") );
		}
		else if ((fabs(v)-38) < EPSINON)
		{
			return QwtText( ("   F") );
		}
		else if ((fabs(v)-44) < EPSINON)
		{
			return QwtText( ("   G") );
		}
		else if ((fabs(v)-50) < EPSINON)
		{
			return QwtText( ("   H") );
		}
// 		else if ((fabs(v)-56) < EPSINON)
// 		{
// 			return QwtText( ("   I") );
// 		}
// 		else if ((fabs(v)-62) < EPSINON)
// 		{
// 			return QwtText( ("   J") );
// 		}
		else if ((fabs(v)-56) < EPSINON)
		{
			return QwtText( ("   1") );
		}
		else if ((fabs(v)-62) < EPSINON)
		{
			return QwtText( ("   2") );
		}
		else if ((fabs(v)-68) < EPSINON)
		{
			return QwtText( ("   3") );
		}
		else if ((fabs(v)-74) < EPSINON)
		{
			return QwtText( ("   4") );
		}
		else if ((fabs(v)-80) < EPSINON)
		{
			return QwtText( ("   5") );
		}
		else if ((fabs(v)-86) < EPSINON)
		{
			return QwtText( ("   6") );
		}
		else if ((fabs(v)-92) < EPSINON)
		{
			return QwtText( ("   7") );
		}
		else if ((fabs(v)-98) < EPSINON)
		{
			return QwtText( ("   8") );
		}
		else
		{
			return QwtText( "    " );
		}
	}
};

PlotSwitch::PlotSwitch( QWidget *parent ):
QwtPlot( parent ),
d_interval( 0.0, 30.0 ),
d_Yinterval(-80,120),
d_timerId( -1 )
{
	m_bRecevied = false;
	m_TotCurNum = 0;
//	m_pSwitchStatus = NULL;

	for (int i=0;i<INPUT;i++)
	{
		m_SwitchIn[i] = -1;
	}

	for (int i=0;i<OUTPUT;i++)
	{
		m_SwitchOut[i] = -1;
	}

	this->plotLayout()->setAlignCanvasToScales( true ); 
	enableAxis( QwtPlot::xBottom,true);
	
	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->setPen( Qt::gray, 0.0, Qt::DotLine );

	grid->enableX( true );
	grid->enableY( true );
	grid->attach( this );

	QwtPlotCanvas *canvas = new QwtPlotCanvas();
	setCanvas( canvas );

	Background *bg = new Background();
	bg->attach( this );

	QString str  = /*tr("时间(s)")*/g_sLangTxt_Time+"(s)";
	QwtText t;
	t.setText(str);

	//设置字体
	QFont font;
	font.setPointSize(9);
	t.setFont(font);
	setAxisTitle( QwtPlot::xBottom, t);

	//msx begin
	t.setText(tr(" "));
	setAxisTitle( QwtPlot::yLeft, t);
	setAxisTitle(QwtPlot::yRight,t);
	//msx end

	enableAxis(QwtPlot::yRight,true);
	QList<double> YRigetTicks[QwtScaleDiv::NTickTypes];
	setAxisScale(QwtPlot::yRight,10,20);
	setAxisScaleDraw(QwtPlot::yRight,new Y2ScaleDraw());

	d_picker = new QwtPlotPicker( QwtPlot::xBottom, QwtPlot::yLeft,
		QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
		this->canvas() );
	d_picker->setStateMachine( new QwtPickerDragPointMachine() );
	d_picker->setRubberBandPen( QColor( Qt::green ) );
	d_picker->setRubberBand( QwtPicker::CrossRubberBand );
	d_picker->setTrackerPen( QColor( Qt::black ) );

	setAxisScale( QwtPlot::xBottom, d_interval.minValue(), d_interval.maxValue() );
	setAxisScale( QwtPlot::yLeft, d_Yinterval.minValue(), d_Yinterval.maxValue());

	QList<double> ticks[QwtScaleDiv::NTickTypes];
	ticks[QwtScaleDiv::MajorTick] /*<<-116<<-110*/<<-104<<-98<<-92<<-86<<-80<<-74<<-68<<-62<<-56<<-50<<-44<<-38<<-32<<-26<<-20<<-14<<-8;  //0和10处显示长刻度，坐标轴也只显示0与10 
	
	QwtScaleDiv scaleDiv(ticks[QwtScaleDiv::MajorTick].first(),ticks[QwtScaleDiv::MajorTick].last(),ticks );
	setAxisScaleDiv(QwtPlot::yLeft, scaleDiv);
	setAxisScaleDraw(QwtPlot::yLeft,new YScaleDraw());
	initSwitchCurve();

	QwtScaleWidget *wid = axisWidget( 0 );
	QFont ft;
	ft.setPointSize(7);
	wid->setFont(ft);

	wid = axisWidget(1);
	wid->setFont(ft);

	setAutoReplot( true );
}

PlotSwitch::~PlotSwitch()
{
	
}

void PlotSwitch::setData(CEventResult* pEvent)
{
	m_pEvent = pEvent;
}	

void PlotSwitch::setSwitchInData()
{
	if (m_pEvent == NULL)
	{
		return;
	}

	for (int i=0;i<INPUT;i++)
	{
		m_SwitchIn[i] = m_pEvent->m_BinIn[i];
	}
}

void PlotSwitch::setSwitchOutData()
{
	if (m_pEvent == NULL)
	{
		return;
	}

	for (int i=0;i<OUTPUT;i++)
	{
		m_SwitchOut[i] = m_pEvent->m_BinOut[i];
	}
}

void PlotSwitch::updatePlotSwitch()
{
	if (m_pEvent == NULL)
	{
		return;
	}

	setSwitchInData();
	setSwitchOutData();
}

void PlotSwitch::stop()
{
	killTimer(d_timerId);
	d_timerId = -1;
}

void PlotSwitch::start()
{
	clearCurveData();
	d_interval.setMinValue(0);
	d_interval.setMaxValue(30);
	setAxisScale( QwtPlot::xBottom, d_interval.minValue(), d_interval.maxValue() );
	d_timerId = startTimer( 200 );
}

void PlotSwitch::updateYTtile( QString str)
{
	setAxisTitle( QwtPlot::yLeft, str );
	replot();
}

void PlotSwitch::updateYScale( float f1,float f2 )
{
	setAxisScale( QwtPlot::yLeft, f1, f2 );
	replot();
}

void PlotSwitch::updateXScale( float f1, float f2 )
{
	setAxisScale( QwtPlot::xBottom, f1, f2 );
	replot();
}

void PlotSwitch::setIntervalLength( double interval )
{
	if ( interval > 0.0 && interval != d_interval.width() )
	{
		d_interval.setMaxValue( d_interval.minValue() + interval );
		setAxisScale( QwtPlot::xBottom, d_interval.minValue(), d_interval.maxValue() );

		replot();
	}
}

void PlotSwitch::updateCurve(double fv)
{
	for(int i=0;i<INPUT;i++)			
	{
		QPointF pt;		
		if(m_curveDataIn[i].size() >= 4000)
		{			
			m_curveDataIn[i].pop_front();
		}

		pt.setX(fv);

		if (m_SwitchIn[i]==1)
		{
			pt.setY(SwitchY[i]+SPACE);
		}
		else
		{
			pt.setY(SwitchY[i]);
		}

		m_curveDataIn[i].append(pt);
		d_curveIn[i]->setSamples(m_curveDataIn[i]);
	}

	for(int i=0;i<OUTPUT;i++)
	{
		QPointF pt;		
		if(m_curveDataOut[i].size() >= 4000)
		{			
			m_curveDataOut[i].pop_front();
		}

		pt.setX(fv);
		
		if (m_SwitchOut[i] == 1)
		{
			pt.setY(SwitchY[i+INPUT]+SPACE);
		}
		else
		{
			pt.setY(SwitchY[i+INPUT]);
		}
		
		m_curveDataOut[i].append(pt);
		d_curveOut[i]->setSamples(m_curveDataOut[i]);
	}

	replot();
}

void PlotSwitch::incrementInterval()
{
	d_interval = QwtInterval( d_interval.maxValue(),
		d_interval.maxValue() + d_interval.width() );

	QwtScaleDiv scaleDiv = axisScaleDiv( QwtPlot::xBottom );
	scaleDiv.setInterval( d_interval );

	for ( int i = 0; i < QwtScaleDiv::NTickTypes; i++ )
	{
		QList<double> ticks = scaleDiv.ticks( i );
		for ( int j = 0; j < ticks.size(); j++ )
			ticks[j] += d_interval.width();
		scaleDiv.setTicks( i, ticks );
	}
	setAxisScaleDiv( QwtPlot::xBottom, scaleDiv );

	replot();
}

void PlotSwitch::timerEvent( QTimerEvent *event )
{
	if ( event->timerId() == d_timerId )
	{
		QPointF point;
		if (m_curveDataIn[0].count()>0)
		{
			point = m_curveDataIn[0].last();
		}
		else
		{
			point.setX(0);
		}

		updateCurve(point.x() + 0.2);
		if ( (point.x() + 0.2) > d_interval.maxValue() )
			incrementInterval();
	}

	QwtPlot::timerEvent( event );
}

void PlotSwitch::initSwitchCurve()
{
	for (int i=0;i<INPUT;i++)
	{
		d_curveIn[i] = new QwtPlotCurve();
		d_curveIn[i]->setStyle( QwtPlotCurve::Steps );
		d_curveIn[i]->setPen( Qt::darkGreen, 2),
		d_curveIn[i]->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		d_curveIn[i]->setLegendIconSize( QSize( 6, 1.5) );
		QPointF pt(0,SwitchY[i]);
		m_curveDataIn[i].append(pt);
		d_curveIn[i]->setSamples(m_curveDataIn[i]);
		d_curveIn[i]->attach( this );
	}

	for (int i=0;i<OUTPUT;i++)
	{
		d_curveOut[i] = new QwtPlotCurve();
		d_curveOut[i]->setTitle(QString("%1").arg(i+1));
		d_curveOut[i]->setStyle( QwtPlotCurve::Steps );
		d_curveOut[i]->setPen( Qt::blue, 2),
		d_curveOut[i]->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		d_curveOut[i]->setLegendIconSize( QSize( 6, 1.5) );
		QPointF pt(0,SwitchY[10+i]);
		m_curveDataOut[i].append(pt);
		d_curveOut[i]->setSamples(m_curveDataOut[i]);
		d_curveOut[i]->attach( this );
	}
}

void PlotSwitch::clearCurveData()
{
	for (int i=0;i<INPUT;i++)
	{
		m_curveDataIn[i].clear();
	}

	for (int i=0;i<OUTPUT;i++)
	{
		m_curveDataOut[i].clear();
	}
}





