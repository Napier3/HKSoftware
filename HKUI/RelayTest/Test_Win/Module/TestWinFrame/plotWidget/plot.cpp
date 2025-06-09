#include "plot.h"
#include <QTime>
#include <qwt_picker_machine.h>
#include <qwt_scale_widget.h>
#include <QLayout>
#include <QFont>
#include "..\ReportView\XLangResource_PowerTestWin.h"

QColor CurveColor[6] = {Qt::yellow,Qt::green,Qt::red,Qt::magenta,Qt::white,Qt::black};
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
			  // Even if not liked by the Qt development, Qt::WA_PaintOutsidePaintEvent
			  // works on X11. This has a nice effect on the performance.

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
		QColor c( /*Qt::white*/QColor( 167, 183, 165 ) );
		QRectF r = canvasRect;
		painter->fillRect( r, c );
		
	}
};

class VScaleDraw: public QwtScaleDraw        //自画坐标轴
{
public:
	VScaleDraw()
	{
	}
	virtual QwtText label( double v ) const  //重绘坐标轴 刻度值
	{
		return QwtText(QString::number( v) );
	}
};

Plot::Plot( QWidget *parent ):
QwtPlot( parent ),
d_interval( 0.0, 30.0 ),
d_Yinterval(-80,120),
d_timerId( -1 )
{
	bYScaleFlag = false;

	m_pVOL = NULL;
	m_pCUR = NULL;
	this->plotLayout()->setAlignCanvasToScales( true ); 

	enableAxis( QwtPlot::xBottom,true);

	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->setPen( Qt::darkGray, 0.0, Qt::DotLine );
	grid->enableX( true );
	grid->enableY( true );
	grid->attach( this );

	QwtPlotCanvas *canvas = new QwtPlotCanvas();
	setCanvas( canvas );

	Background *bg = new Background();
	bg->attach( this );

	QwtText t;
	t.setText(/*tr("电压(V)")*/g_sLangTxt_Native_Voltage+"(V)");
	QFont font;
	font.setPointSize(9);
	t.setFont(font);
	setAxisTitle( QwtPlot::yLeft,t);
	t.setText(/*tr("电流(A)")*/g_sLangTxt_Native_Current+"(A)");
	setAxisTitle( QwtPlot::yRight,t);

	d_picker = new QwtPlotPicker( QwtPlot::xBottom, QwtPlot::yLeft,
		QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
		this->canvas() );
	d_picker->setStateMachine( new QwtPickerDragPointMachine() );
	d_picker->setRubberBandPen( QColor( Qt::green ) );
	d_picker->setRubberBand( QwtPicker::CrossRubberBand );
	d_picker->setTrackerPen( QColor( Qt::black ) );

	QFont fonttTemp = this->font();
	QFontMetrics fontMetrics = QFontMetrics(fonttTemp);
	int nHeight = fontMetrics.height() + 6;
	m_PlotLabelText = new QLabel(this->canvas());
	m_PlotLabelText->setStyleSheet("QLabel{  background-color:black;color: rgb(85, 255, 0); }");
	int width = this->canvas()->width()+300;
	m_labYellow = new QLabel(this->canvas());
	m_labYellow->setStyleSheet(" QLabel{  background-color:black;color: yellow; }");
	m_labYellow->setText(/*QObject::tr("— A相")*/"— "+g_sLangTxt_Aphase);
	m_labGreen = new QLabel(this->canvas());
	m_labGreen->setStyleSheet(" QLabel{  background-color:black;color: green; }");
	m_labGreen->setText(/*QObject::tr("— B相")*/"— "+g_sLangTxt_Bphase);
	m_labRed = new QLabel(this->canvas());
	m_labRed->setStyleSheet(" QLabel{  background-color:black;color:red; }");
	m_labRed->setText(/*QObject::tr("— C相")*/"— "+g_sLangTxt_Cphase);
	m_labPurple = new QLabel(this->canvas());
	m_labPurple->setStyleSheet(" QLabel{  background-color:black;color:purple; }");
	m_labPurple->setText(/*QObject::tr("— Z相")*/"— "+g_sLangTxt_Native_Zphase);
	m_labWhite = new QLabel(this->canvas());
	m_labWhite->setStyleSheet(" QLabel{  background-color:black;color:white; }");
	m_labWhite->setText(/*QObject::tr("— 0相")*/"— "+g_sLangTxt_Native_PhaseO);

	m_PlotLabelText->setGeometry(2,1,40,nHeight);
	m_labYellow->setGeometry(42,1,80,nHeight);
	m_labGreen->setGeometry(122,1,80,nHeight);
	m_labRed->setGeometry(202,1,width,nHeight);
	m_labPurple->setGeometry(282,1,width,nHeight);
	m_labWhite->setGeometry(362,1,width,nHeight);

	setAxisScale( QwtPlot::xBottom, d_interval.minValue(), d_interval.maxValue() );
	setAxisScale( QwtPlot::yLeft, d_Yinterval.minValue(), d_Yinterval.maxValue());
	enableAxis(QwtPlot::yRight,true);

	QList<double> ticks[QwtScaleDiv::NTickTypes];
	ticks[QwtScaleDiv::MajorTick] <<0<<20<<40<<60<<80<<100<<120<<140<<160<<180<<200<<220<<240<<260<<280<<300;  //0和10处显示长刻度，坐标轴也只显示0与10 

	QwtScaleDiv scaleDiv(ticks[QwtScaleDiv::MajorTick].first(),ticks[QwtScaleDiv::MajorTick].last(),ticks );
	setAxisScaleDiv(QwtPlot::yLeft, scaleDiv);
	setAxisScaleDraw(QwtPlot::yLeft,new VScaleDraw());
	
	QList<double> ticks1[QwtScaleDiv::NTickTypes];
	ticks1[QwtScaleDiv::MajorTick]<< 0 <<4<<8<<12<<16<<20<<24;  //0和10处显示长刻度，坐标轴也只显示0与10
	QwtScaleDiv scaleDiv1(ticks1[QwtScaleDiv::MajorTick].first(),ticks1[QwtScaleDiv::MajorTick].last(),ticks1 );
	setAxisScaleDiv(QwtPlot::yRight, scaleDiv1);
	setAxisScaleDraw(QwtPlot::yRight,new VScaleDraw());

	QwtScaleWidget *wid = axisWidget( 0 );
	QFont ft;
	ft.setPointSize(7);
	wid->setFont(ft);

	wid = axisWidget(1);
	wid->setFont(ft);

	QwtScaleWidget *widx = axisWidget( 2 );
	QFont ftx;
	ftx.setPointSize(1);
	widx->setFont(ftx);
	
	setAutoReplot( true );
}

Plot::~Plot()
{
	killTimer(d_timerId);
	d_timerId=-1;
}

void Plot::stop()
{
	killTimer(d_timerId);
	d_timerId = -1;
}

void Plot::start()
{
	bYScaleFlag = 0;
	clearCurveData();
	d_interval.setMinValue(0);
	d_interval.setMaxValue(30);
	setAxisScale( QwtPlot::xBottom, d_interval.minValue(), d_interval.maxValue() );
	d_clock.start();
	d_timerId = startTimer( 200 );
}

void Plot::updateYTtile( QString str)
{
	setAxisTitle( QwtPlot::yLeft, str );
	replot();
}

void Plot::updateYScale(float f1,float f2 )
{
	setAxisScale( QwtPlot::yLeft, f1, f2 );
	replot();
}

void Plot::updateXScale( float f1, float f2 )
{
	setAxisScale( QwtPlot::xBottom, f1, f2 );
	replot();
}

void Plot::setIntervalLength( double interval )
{
	if ( interval > 0.0 && interval != d_interval.width() )
	{
		d_interval.setMaxValue( d_interval.minValue() + interval );
		setAxisScale( QwtPlot::xBottom,
			d_interval.minValue(), d_interval.maxValue() );

		replot();
	}
}

void Plot::updateCurve(double fv)
{	
	float fy;
	
	if (m_nUModuleNum>0)
	{
		for (int i = 0; i < m_nUCHNum; i++)
		{
			fy = m_pVOL[i].Harm[1].fAmp;
			if (fy<0)
			{
				bYScaleFlag = 1;
			}

			QPointF point(fv,fy);
			if (m_CurveDataList[i].size()>=4000)
			{
				m_CurveDataList[i].pop_front();
			}
			m_CurveDataList[i].append(point);
			m_CurveList[i]->setSamples(m_CurveDataList[i]);
		}
	}

	if (m_nIModuleNum > 0 )
	{
		for (int i = 0; i < m_nICHNum; i++)
		{
			fy = m_pCUR[i].Harm[1].fAmp;
			if (fy<0)
			{
				bYScaleFlag = 1;
			}
				
			QPointF point(fv,fy);
			if (m_CurveDataList[i+m_nUCHNum].size()>=4000)
			{
				m_CurveDataList[i+m_nUCHNum].pop_front();
			}
			m_CurveDataList[i+m_nUCHNum].append(point);
			m_CurveList[i+m_nUCHNum]->setSamples(m_CurveDataList[i+m_nUCHNum]);
		}
	}
	
	if (bYScaleFlag)
	{
		QList<double> ticks[QwtScaleDiv::NTickTypes];
		QList<double> ticks1[QwtScaleDiv::NTickTypes];
		ticks[QwtScaleDiv::MajorTick] <<-180<<-150<<-120<<-90<<-60<<-30<<0<<30<<60<<90<<120<<150<<180;
		ticks1[QwtScaleDiv::MajorTick]<<-12<<-10<<-8<< -6 <<-4<<-2<<0<<2<<4<<6<<8<<10<<12;
	
		QwtScaleDiv scaleDiv(ticks[QwtScaleDiv::MajorTick].first(),ticks[QwtScaleDiv::MajorTick].last(),ticks );
		setAxisScaleDiv(QwtPlot::yLeft, scaleDiv);
		setAxisScaleDraw(QwtPlot::yLeft,new VScaleDraw());

		QwtScaleDiv scaleDiv1(ticks1[QwtScaleDiv::MajorTick].first(),ticks1[QwtScaleDiv::MajorTick].last(),ticks1 );
		setAxisScaleDiv(QwtPlot::yRight, scaleDiv1);
		setAxisScaleDraw(QwtPlot::yRight,new VScaleDraw());
	}
	else
	{			
		QList<double> ticks[QwtScaleDiv::NTickTypes];
		ticks[QwtScaleDiv::MajorTick] <<0<<20<<40<<60<<80<<100<<120<<140<<160<<180<<200<<220<<240<<260<<280<<300;   

		QwtScaleDiv scaleDiv(ticks[QwtScaleDiv::MajorTick].first(),ticks[QwtScaleDiv::MajorTick].last(),ticks );
		setAxisScaleDiv(QwtPlot::yLeft, scaleDiv);
		setAxisScaleDraw(QwtPlot::yLeft,new VScaleDraw());

		QList<double> ticks1[QwtScaleDiv::NTickTypes];
		ticks1[QwtScaleDiv::MajorTick]<< 0 <<3<<6<<9<<12<<15<<18<<21<<24<<27<<30;  
		
		QwtScaleDiv scaleDiv1(ticks1[QwtScaleDiv::MajorTick].first(),ticks1[QwtScaleDiv::MajorTick].last(),ticks1 );
		setAxisScaleDiv(QwtPlot::yRight, scaleDiv1);

		setAxisScaleDraw(QwtPlot::yRight,new VScaleDraw());
	}

	replot();
}

void Plot::incrementInterval()
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

void Plot::timerEvent( QTimerEvent *event )
{
// 	if ( event->timerId() == d_timerId)////??????????????????????????????????????????????????zhouhj 联机后此处会导致崩溃
// 	{
// 		QPointF point(0,0);
// 		if (m_CurveDataList[0].size() > 0)
// 		{
// 			point = m_CurveDataList[0].last();
// 		}
// 
// 		updateCurve(point.x() + 0.2);
// 		if ((point.x() +0.2) > d_interval.maxValue())
// 		{
// 			incrementInterval();
// 		}
// 	}

	QwtPlot::timerEvent( event );
}

void Plot::initCurve()
{
	m_CurveList.clear();
	m_CurveDataList.clear();
	
	m_nUCHNum = 0;
	m_nICHNum = 0;
	
	if (m_nUModuleNum > 0)
	{
		for (int i = 0; i<m_UModultChannelNumList.size();i++)
		{
			m_nUCHNum += m_UModultChannelNumList[i];
		}
	}
	else
	{
		m_nUCHNum = 0;
	}

	if (m_nIModuleNum > 0)
	{
		for (int i = 0; i<m_IModultChannelNumList.size();i++)
		{
			m_nICHNum += m_IModultChannelNumList[i];
		}
	}
	else
	{
		m_nICHNum = 0;
	}

	QVector<QPointF> points;
	QwtPlotCurve *pCurve = NULL;
	int nChNum = 0;

	//电压波形初始化
	if (m_nUModuleNum > 0)
	{
		nChNum = m_UModultChannelNumList[0];
		for (int i = 0; i<m_nUCHNum;i++)
		{
			pCurve = new QwtPlotCurve();
			pCurve->setTitle(tr("A"));
			if(nChNum<=4)	
			{
				pCurve->setPen(CurveColor[i%nChNum],2.5);
			}
			else
			{
				pCurve->setPen(CurveColor[i%3],2.5);
			}
			pCurve->setYAxis(QwtPlot::yLeft);
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pCurve->setSamples( points );
			pCurve->attach( this );
			m_CurveList.append(pCurve);
			m_CurveDataList.append(points);
		}
	}
	
	//电流波形初始化
	if (m_nIModuleNum>0)
	{
		nChNum = m_IModultChannelNumList[0];
		for (int i = 0; i<m_nICHNum;i++)
		{
			pCurve = new QwtPlotCurve();
			pCurve->setTitle(tr("A"));
			if(nChNum<=4)	
			{
				pCurve->setPen(CurveColor[i%nChNum],1.3);
				if(i%nChNum==3)
				{
					pCurve->setPen(CurveColor[4],1.3);
				}
			}
			else
			{
				pCurve->setPen(CurveColor[i%3],1.3);
			}
			pCurve->setYAxis(QwtPlot::yRight);
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pCurve->setSamples( points );
			pCurve->attach( this );
			m_CurveList.append(pCurve);
			m_CurveDataList.append(points);
		}
	}
}

void Plot::clearCurveData()
{
	for (int i = 0; i < m_CurveDataList.size();i++)
	{
		m_CurveDataList[i].clear();
		m_CurveList[i]->setSamples(m_CurveDataList[i]);
	}
	replot();
}

void Plot::setData(tmt_channel* pVOL,tmt_channel* pCUR)
{
    m_pVOL = pVOL;
	m_pCUR = pCUR;
}

void Plot::setPropertyofPlot(plugin_type type,int UModuleNum,int IModuleNum,QList<int> UModultChannelNumList,QList<int> IModultChannelNumList)
{
	m_type = type;
	m_nUModuleNum = UModuleNum;
	m_nIModuleNum = IModuleNum;
	m_UModultChannelNumList = UModultChannelNumList;
	m_IModultChannelNumList = IModultChannelNumList;

	initCurve();
}

