#include "TimeResponsePlotBase.h"
#include "../../../Module/System/TickCount32.h"

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

void CurveData::append( const QPointF &point )
{

	// 	if (point.x()>1000)
	// 	{
	// 		maxx++;
	// 	}

	d_samples.append(point);
	if(point.y()<=miny) miny = point.y();
	if(point.y()>=maxy) maxy = point.y();
	if(point.x()<=minx) minx = point.x();
	if(point.x()>=maxx) maxx = point.x();
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
	m_dRealTime = 0.0f;
	m_bUseTesterTime = FALSE;
	m_bNeedInit = false;
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
	if (m_bUseTesterTime && (!m_bNeedInit))
	{
		return;
	}

	int nCnt = m_oCurveList.size();
	for (int i = 0; i < nCnt;i++)
	{
		QwtPlotCurve *p = m_oCurveList.at(i);
		delete p;
	}
	m_oCurveList.clear();

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
		m_oYinterval.setMinValue(f1);
		m_oYinterval.setMaxValue(f2);
		setAxisScale( QwtPlot::yLeft, f1, f2 );
	}
	else
	{
		setAxisScale( QwtPlot::yRight, f1, f2 );
	}
	
	replot();
}

// void CTimeResponsePlotBase::updateXScale( float f1, float f2 )
// {
// 	m_oXinterval.setMinValue(f1);
// 	m_oXinterval.setMaxValue(f2);
// 	setAxisScale( QwtPlot::xBottom, f1, f2 );
// 	replot();
// }

void CTimeResponsePlotBase::setIntervalLength( double interval )
{
	if ( interval > 0.0 && interval != m_oXinterval.width() )
	{
		m_oXinterval.setMaxValue( m_oXinterval.minValue() + interval );
		setAxisScale( QwtPlot::xBottom, m_oXinterval.minValue(), m_oXinterval.maxValue() );

		replot();
	}
}

void CTimeResponsePlotBase::incrementInterval()
{
	m_oXinterval = QwtInterval( m_oXinterval.maxValue(),
		m_oXinterval.maxValue() + m_oXinterval.width() );

	QwtScaleDiv scaleDiv = axisScaleDiv( QwtPlot::xBottom );
	scaleDiv.setInterval( m_oXinterval );

	for ( int i = 0; i < QwtScaleDiv::NTickTypes; i++ )
	{
		QList<double> ticks = scaleDiv.ticks( i );
		for ( int j = 0; j < ticks.size(); j++ )
			ticks[j] += m_oXinterval.width();
		scaleDiv.setTicks( i, ticks );
	}
	setAxisScaleDiv( QwtPlot::xBottom, scaleDiv );

	replot();
}

void CTimeResponsePlotBase::onTimerEvent( QTimerEvent *event )
{
	if (m_bUseTesterTime)
	{
		return;
	}

	QPointF point(0,0);

	if(m_oUpdateList.size()==0)
	{
		return;
	}

	if (m_oUpdateList[0].size() > 0)
	{
		point = m_oUpdateList[0].last();
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
	
	if ((point.x() + 0.2) > m_oXinterval.maxValue())
	{
		incrementInterval();
	}
}

void CTimeResponsePlotBase::UpdateCurves()
{
	//开始绘制
	for (int i = 0; i < m_oPreUpdateList.size(); i++)
	{
		m_oUpdateList[i] += m_oPreUpdateList[i];
	}

	QVector<QPointF> oQPointF_Vector;
	//完成绘制后删除更新列表
	for(int i = 0; i < m_oUpdateList.size(); i++)
	{
		oQPointF_Vector = m_oUpdateList.at(i);
		UpdateCurve(i, oQPointF_Vector);
		m_oUpdateList[i].clear();
	}

	replot();

	for (int i = 0; i < m_oPreUpdateList.size(); i++)
	{
		while(m_oPreUpdateList[i].size())
		{
			m_oPreUpdateList[i].pop_back();
		}
	}
}

void CTimeResponsePlotBase::UpdateCurve(long nIndex, const QVector<QPointF>& points)
{
	QwtPlotCurve* pCurve = m_oCurveList.at(nIndex);
	CurveData* pCurvePoints = static_cast<CurveData*>(pCurve->data());

	long nFrom = (long)pCurvePoints->size();
	if(points.size())
	{
		for (int i = 0; i < points.size(); i++)
		{
			QPointF pt = points.at(i);
			pCurvePoints->append(pt);
		}
	}
	else
	{
		long nSize = pCurvePoints->size() - 1;
		if(nSize < 0)
		{
			return;
		}
		QPointF pt = pCurvePoints->sample(nSize);
		//避免连续测试时starttest的绝对时间超过gps对时
		if(pt.x() < m_dLastTime)
		{
			pt.setX(m_dLastTime);
			pCurvePoints->append(pt);
		}
	}

	if(pCurvePoints->maxx > m_oXinterval.maxValue())
	{
		m_oXinterval.setMinValue(m_oXinterval.minValue() + 30);
		m_oXinterval.setMaxValue(m_oXinterval.maxValue() + 30);
		setAxisScale(QwtPlot::xBottom, m_oXinterval.minValue(), m_oXinterval.maxValue());
	}
}

void CTimeResponsePlotBase::UpdateXScale(float f1, float f2)
{
	m_oXinterval.setMinValue(f1);
	m_oXinterval.setMaxValue(f2);
	setAxisScale( QwtPlot::xBottom, f1, f2 );
}

void CTimeResponsePlotBase::AddStopPoint()
{
	for (int i = 0; i < m_oPreUpdateList.size(); i++)
	{
		QwtPlotCurve* pCurve = m_oCurveList.at(i);
		CurveData* pCurvePoints = static_cast<CurveData*>(pCurve->data());
		QPointF pt;
		if(m_oPreUpdateList[i].size())
		{
			pt = m_oPreUpdateList[i].last();
		}
		else
		{
			long nSize = pCurvePoints->size() - 1;
			if(nSize < 0)
			{
				continue;
			}
			pt = pCurvePoints->sample(nSize);
		}
		pt.setX(m_dLastTime);
		m_oPreUpdateList[i].append(pt);
	}
}

void CTimeResponsePlotBase::clearCurveData()
{
	int nSize = m_oUpdateList.size();
	for (int i = 0; i < nSize;i++)
	{
		if (m_bUseTesterTime)
		{
			m_oPreUpdateList[i].clear();
		}

		m_oUpdateList[i].clear();	
	}

	if (m_bUseTesterTime)
	{
		for (int i = 0; i < m_oCurveList.size(); i++)
		{
			//CurveData内都是QPointF对象而非指针,可直接clear
			CurveData* pData = static_cast<CurveData*>(m_oCurveList[i]->data());
			pData->maxx = pData->maxy = pData->minx = pData->miny = 0;
			pData->clear();
		}
	}
	else
	{
		m_oUpdateList.clear();
	}

#ifndef _GRADIENT_PLOT_
	m_dLastTime = 0;
#endif
	m_dRealTime = 0;

	if (m_bUseTesterTime)
	{
		m_oXinterval.setMinValue(0);
		m_oXinterval.setMaxValue(30);
		setAxisScale(QwtPlot::xBottom, m_oXinterval.minValue(), m_oXinterval.maxValue());
	}

	replot();
}

void CTimeResponsePlotBase::reflushDataList(double fLastTime)
{
	if (m_bUseTesterTime)
	{
		return;
	}

	int nSize = m_oUpdateList.size();
	if (nSize <= 0)
	{
		return;
	}

	while(m_oUpdateList[0].last().rx() >= fLastTime)
	{
		for (int i = 0; i < nSize;i++)
		{
			m_oUpdateList[i].pop_back();
		}
	}
}




