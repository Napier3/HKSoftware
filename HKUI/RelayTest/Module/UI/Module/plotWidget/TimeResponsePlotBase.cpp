#include "TimeResponsePlotBase.h"
#include "../../../Module/System/TickCount32.h"
#include <QMessageBox>

QColor g_arrCurveColor[MAX_COLOR_NUM]={Qt::yellow,Qt::green,Qt::red,Qt::magenta
										,Qt::blue,Qt::black,Qt::darkGray,Qt::cyan
										,Qt::white,Qt::darkRed,Qt::darkGreen,Qt::darkCyan
										,Qt::darkBlue,Qt::darkMagenta,Qt::darkYellow,Qt::gray};
QString GetCurveStyleSheetString(long nColorIndex)
{
	QString strRet = " QLabel{  background-color:black;color: yellow; }";

	switch (nColorIndex)
	{
	case 0:
		strRet = " QLabel{ color: yellow; }"; // background-color:black;
		break;
	case 1:
		strRet = " QLabel{ color: green; }";
		break;
	case 2:
		strRet = " QLabel{ color: red; }";
		break;
	case 3:
		strRet = " QLabel{ color: magenta; }";
		break;
	case 4:
		strRet = " QLabel{ color: blue; }";
		break;
	case 5:
		strRet = " QLabel{ color: black; }";
		break;
	case 6:
		strRet = " QLabel{ color: darkGray; }";
		break;
	case 7:
		strRet = " QLabel{ color: cyan; }";
		break;
	case 8:
		strRet = " QLabel{ color: white; }";
		break;
	case 9:
		strRet = " QLabel{ color: darkRed; }";
		break;
	case 10:
		strRet = " QLabel{ color: darkGreen; }";
		break;
	case 11:
		strRet = " QLabel{ color: darkCyan; }";
		break;
	case 12:
		strRet = " QLabel{ color: darkBlue; }";
		break;
	case 13:
		strRet = " QLabel{ color: darkMagenta; }";
		break;
	case 14:
		strRet = " QLabel{ color: darkYellow; }";
		break;
	case 15:
		strRet = " QLabel{ color: gray; }";
		break;
	default:
		break;
	}

	return strRet;
}

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
		QColor c( QColor( 167, 183, 165 ));
		QRectF r = canvasRect;
		painter->fillRect( r, c );
	}
};

CTimeResponsePlotBase::CTimeResponsePlotBase( QWidget *parent ):
QwtPlot( parent )
{
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

	d_picker = new QwtPlotPicker( QwtPlot::xBottom, QwtPlot::yLeft,
		QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
		this->canvas() );
	d_picker->setStateMachine( new QwtPickerDragPointMachine() );
	d_picker->setRubberBandPen( QColor( Qt::green ) );
	d_picker->setRubberBand( QwtPicker::CrossRubberBand );
	d_picker->setTrackerPen( QColor( Qt::black ) );

	QwtScaleWidget *wid = axisWidget( 0 );
	QFont ft;
	ft.setPointSize(7);
	wid->setFont(ft);

	wid = axisWidget(1);
	wid->setFont(ft);

	setAutoReplot( true );

	m_bFirst = true;
}

CTimeResponsePlotBase::~CTimeResponsePlotBase()
{
	clearCurvePlot();
}

void CTimeResponsePlotBase::clearCurvePlot()
{
	int nCnt = m_CurveList.size();
	for (int i = 0; i < nCnt;i++)
	{
		QwtPlotCurve *p = m_CurveList.at(i);
		delete p;
	}
	m_CurveList.clear();

	clearCurveData();
}

void CTimeResponsePlotBase::updateXTtile(QString str,long nFontSize)
{
	QwtText t(str);
	QFont font;
	font.setPointSize(nFontSize);
	t.setFont(font);

	setAxisTitle( QwtPlot::xBottom, t);
	replot();
}

void CTimeResponsePlotBase::updateYTtile(QString str,long nFontSize,BOOL bLeft)
{
	QwtText t(str);
	QFont font;
	font.setPointSize(nFontSize);
	t.setFont(font);

	if (bLeft)
	{
		setAxisTitle( QwtPlot::yLeft, t );
	}
	else
	{
		setAxisTitle( QwtPlot::yRight, t );
	}
	
	replot();
}

void CTimeResponsePlotBase::updateYScale( float f1,float f2 ,BOOL bLeft)
{
	if (bLeft)
	{
		m_Yinterval.setMinValue(f1);
		m_Yinterval.setMaxValue(f2);
		setAxisScale( QwtPlot::yLeft, f1, f2 );
	}
	else
	{
		setAxisScale( QwtPlot::yRight, f1, f2 );
	}
	
	replot();
}

void CTimeResponsePlotBase::updateXScale( float f1, float f2 )
{
	m_Xinterval.setMinValue(f1);
	m_Xinterval.setMaxValue(f2);
	setAxisScale( QwtPlot::xBottom, f1, f2 );
	replot();
}

void CTimeResponsePlotBase::setIntervalLength( double interval )
{
	if ( interval > 0.0 && interval != m_Xinterval.width() )
	{
		m_Xinterval.setMaxValue( m_Xinterval.minValue() + interval );
		setAxisScale( QwtPlot::xBottom, m_Xinterval.minValue(), m_Xinterval.maxValue() );

		replot();
	}
}

void CTimeResponsePlotBase::incrementInterval()
{
	int nIncVal = 30;

#ifndef _PSX_QT_LINUX_
	m_Xinterval = QwtInterval(m_Xinterval.maxValue(),
		m_Xinterval.maxValue()+m_Xinterval.width());
#else
    double dMinValue = m_Xinterval.maxValue();
	m_Xinterval.setMinValue(dMinValue);
	m_Xinterval.setMaxValue(dMinValue + nIncVal);
#endif

	QwtScaleDiv scaleDiv = axisScaleDiv( QwtPlot::xBottom );
	scaleDiv.setInterval( m_Xinterval );

	for ( int i = 0; i < QwtScaleDiv::NTickTypes; i++ )
	{
		QList<double> ticks = scaleDiv.ticks( i );
		for ( int j = 0; j < ticks.size(); j++ )
#ifndef _PSX_QT_LINUX_
			ticks[j] += m_Xinterval.width();
#else
			ticks[j] += nIncVal;		
#endif
		scaleDiv.setTicks( i, ticks );
	}

	setAxisScaleDiv( QwtPlot::xBottom, scaleDiv );

	replot();
}

void CTimeResponsePlotBase::onTimerEvent( QTimerEvent *event )
{
	QPointF point(0,0);

	if(m_CurveDataList.size()==0)
	{
		return;
	}

	if (m_CurveDataList[0].size() > 0)
	{
		point = m_CurveDataList[0].last();
	}
	
	if (m_bFirst)
	{
		updateCurve(0);
		m_bFirst = false;
	}
	else
	{
		updateCurve(point.x() + 0.2);
	}
	
	if ((point.x() + 0.2) > m_Xinterval.maxValue())
	{
		incrementInterval();
	}
}

void CTimeResponsePlotBase::clearCurveData()
{
	int nSize = m_CurveDataList.size();
	for (int i = 0; i < nSize;i++)
	{
		m_CurveDataList[i].clear();	
	}

	m_CurveDataList.clear();

	replot();
}

void CTimeResponsePlotBase::reflushDataList(double fLastTime)
{
	int nSize = m_CurveDataList.size();
	if (nSize <= 0)
	{
		return;
	}

	while(m_CurveDataList[0].last().rx() >= fLastTime)
	{
		for (int i = 0; i < nSize;i++)
		{
			m_CurveDataList[i].pop_back();
		}
	}
}




